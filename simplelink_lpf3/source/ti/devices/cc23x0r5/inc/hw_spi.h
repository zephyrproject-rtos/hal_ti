/******************************************************************************
*  Filename:       hw_spi_h
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

#ifndef __HW_SPI_H__
#define __HW_SPI_H__

//*****************************************************************************
//
// This section defines the register offsets of
// SPI component
//
//*****************************************************************************
// Module Description
#define SPI_O_DESC                                                  0x00000000U

// Interrupt mask
#define SPI_O_IMASK                                                 0x00000044U

// Raw interrupt status
#define SPI_O_RIS                                                   0x00000048U

// Masked interrupt status
#define SPI_O_MIS                                                   0x0000004CU

// Interrupt set
#define SPI_O_ISET                                                  0x00000050U

// Interrupt clear
#define SPI_O_ICLR                                                  0x00000054U

// Interrupt mask set
#define SPI_O_IMSET                                                 0x00000058U

// Interrupt mask clear
#define SPI_O_IMCLR                                                 0x0000005CU

// Emulation
#define SPI_O_EMU                                                   0x00000060U

// Control 0
#define SPI_O_CTL0                                                  0x00000100U

// Control 1
#define SPI_O_CTL1                                                  0x00000104U

// Clock configuration 0
#define SPI_O_CLKCFG0                                               0x00000108U

// Clock configuration 1
#define SPI_O_CLKCFG1                                               0x0000010CU

// Interrupt FIFO Level Select
#define SPI_O_IFLS                                                  0x00000110U

// DMA control
#define SPI_O_DMACR                                                 0x00000114U

// Receive CRC
#define SPI_O_RXCRC                                                 0x00000118U

// Transmit CRC
#define SPI_O_TXCRC                                                 0x0000011CU

// Header write for 32bits
#define SPI_O_TXFHDR32                                              0x00000120U

// Header write for 24bits
#define SPI_O_TXFHDR24                                              0x00000124U

// Header write for 16bits
#define SPI_O_TXFHDR16                                              0x00000128U

// Header write for 8bits
#define SPI_O_TXFHDR8                                               0x0000012CU

// Atomic header control
#define SPI_O_TXFHDRC                                               0x00000130U

// Receive data
#define SPI_O_RXDATA                                                0x00000140U

// Transmit data
#define SPI_O_TXDATA                                                0x00000150U

// Status
#define SPI_O_STA                                                   0x00000160U

//*****************************************************************************
//
// Register: SPI_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define SPI_DESC_MODID_W                                                    16U
#define SPI_DESC_MODID_M                                            0xFFFF0000U
#define SPI_DESC_MODID_S                                                    16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
//
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define SPI_DESC_STDIPOFF_W                                                  4U
#define SPI_DESC_STDIPOFF_M                                         0x0000F000U
#define SPI_DESC_STDIPOFF_S                                                 12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define SPI_DESC_INSTIDX_W                                                   4U
#define SPI_DESC_INSTIDX_M                                          0x00000F00U
#define SPI_DESC_INSTIDX_S                                                   8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define SPI_DESC_MAJREV_W                                                    4U
#define SPI_DESC_MAJREV_M                                           0x000000F0U
#define SPI_DESC_MAJREV_S                                                    4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define SPI_DESC_MINREV_W                                                    4U
#define SPI_DESC_MINREV_M                                           0x0000000FU
#define SPI_DESC_MINREV_S                                                    0U

//*****************************************************************************
//
// Register: SPI_O_IMASK
//
//*****************************************************************************
// Field:     [8] DMATX
//
// DMA Done TX event mask.
// ENUMs:
// SET                      Set Interrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_DMATX                                             0x00000100U
#define SPI_IMASK_DMATX_M                                           0x00000100U
#define SPI_IMASK_DMATX_S                                                    8U
#define SPI_IMASK_DMATX_SET                                         0x00000100U
#define SPI_IMASK_DMATX_CLR                                         0x00000000U

// Field:     [7] DMARX
//
// DMA Done RX event mask.
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_DMARX                                             0x00000080U
#define SPI_IMASK_DMARX_M                                           0x00000080U
#define SPI_IMASK_DMARX_S                                                    7U
#define SPI_IMASK_DMARX_SET                                         0x00000080U
#define SPI_IMASK_DMARX_CLR                                         0x00000000U

// Field:     [6] IDLE
//
// SPI Idle event mask.
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_IDLE                                              0x00000040U
#define SPI_IMASK_IDLE_M                                            0x00000040U
#define SPI_IMASK_IDLE_S                                                     6U
#define SPI_IMASK_IDLE_SET                                          0x00000040U
#define SPI_IMASK_IDLE_CLR                                          0x00000000U

// Field:     [5] TXEMPTY
//
// Transmit FIFO Empty event mask.
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_TXEMPTY                                           0x00000020U
#define SPI_IMASK_TXEMPTY_M                                         0x00000020U
#define SPI_IMASK_TXEMPTY_S                                                  5U
#define SPI_IMASK_TXEMPTY_SET                                       0x00000020U
#define SPI_IMASK_TXEMPTY_CLR                                       0x00000000U

// Field:     [4] TX
//
// Transmit FIFO event mask.
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_TX                                                0x00000010U
#define SPI_IMASK_TX_M                                              0x00000010U
#define SPI_IMASK_TX_S                                                       4U
#define SPI_IMASK_TX_SET                                            0x00000010U
#define SPI_IMASK_TX_CLR                                            0x00000000U

// Field:     [3] RX
//
// Receive FIFO event.
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_RX                                                0x00000008U
#define SPI_IMASK_RX_M                                              0x00000008U
#define SPI_IMASK_RX_S                                                       3U
#define SPI_IMASK_RX_SET                                            0x00000008U
#define SPI_IMASK_RX_CLR                                            0x00000000U

// Field:     [2] RTOUT
//
//  SPI Receive Time-Out event mask.
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_RTOUT                                             0x00000004U
#define SPI_IMASK_RTOUT_M                                           0x00000004U
#define SPI_IMASK_RTOUT_S                                                    2U
#define SPI_IMASK_RTOUT_SET                                         0x00000004U
#define SPI_IMASK_RTOUT_CLR                                         0x00000000U

// Field:     [1] PER
//
// Parity error event mask.
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_PER                                               0x00000002U
#define SPI_IMASK_PER_M                                             0x00000002U
#define SPI_IMASK_PER_S                                                      1U
#define SPI_IMASK_PER_SET                                           0x00000002U
#define SPI_IMASK_PER_CLR                                           0x00000000U

// Field:     [0] RXOVF
//
// RXFIFO overflow event mask.
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define SPI_IMASK_RXOVF                                             0x00000001U
#define SPI_IMASK_RXOVF_M                                           0x00000001U
#define SPI_IMASK_RXOVF_S                                                    0U
#define SPI_IMASK_RXOVF_SET                                         0x00000001U
#define SPI_IMASK_RXOVF_CLR                                         0x00000000U

//*****************************************************************************
//
// Register: SPI_O_RIS
//
//*****************************************************************************
// Field:     [8] DMATX
//
// DMA Done event for TX. This interrupt is set if the TX DMA channel sends the
// DONE signal. This allows the handling of the TX DMA event inside SPI.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_DMATX                                               0x00000100U
#define SPI_RIS_DMATX_M                                             0x00000100U
#define SPI_RIS_DMATX_S                                                      8U
#define SPI_RIS_DMATX_SET                                           0x00000100U
#define SPI_RIS_DMATX_CLR                                           0x00000000U

// Field:     [7] DMARX
//
// DMA Done event for RX. This interrupt is set if the RX DMA channel sends the
// DONE signal. This allows handling of the DMA RX event inside SPI.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_DMARX                                               0x00000080U
#define SPI_RIS_DMARX_M                                             0x00000080U
#define SPI_RIS_DMARX_S                                                      7U
#define SPI_RIS_DMARX_SET                                           0x00000080U
#define SPI_RIS_DMARX_CLR                                           0x00000000U

// Field:     [6] IDLE
//
// SPI has completed transfers and moved to IDLE mode. This bit is set when
// STA.BUSY goes low.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_IDLE                                                0x00000040U
#define SPI_RIS_IDLE_M                                              0x00000040U
#define SPI_RIS_IDLE_S                                                       6U
#define SPI_RIS_IDLE_SET                                            0x00000040U
#define SPI_RIS_IDLE_CLR                                            0x00000000U

// Field:     [5] TXEMPTY
//
// Transmit FIFO Empty interrupt mask. This interrupt is set when all data in
// the Transmit FIFO has been moved to the shift register.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_TXEMPTY                                             0x00000020U
#define SPI_RIS_TXEMPTY_M                                           0x00000020U
#define SPI_RIS_TXEMPTY_S                                                    5U
#define SPI_RIS_TXEMPTY_SET                                         0x00000020U
#define SPI_RIS_TXEMPTY_CLR                                         0x00000000U

// Field:     [4] TX
//
// Transmit FIFO event. This interrupt is set if the selected Transmit FIFO
// level has been reached.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_TX                                                  0x00000010U
#define SPI_RIS_TX_M                                                0x00000010U
#define SPI_RIS_TX_S                                                         4U
#define SPI_RIS_TX_SET                                              0x00000010U
#define SPI_RIS_TX_CLR                                              0x00000000U

// Field:     [3] RX
//
// Receive FIFO event. This interrupt is set if the selected Receive FIFO level
// has been reached
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_RX                                                  0x00000008U
#define SPI_RIS_RX_M                                                0x00000008U
#define SPI_RIS_RX_S                                                         3U
#define SPI_RIS_RX_SET                                              0x00000008U
#define SPI_RIS_RX_CLR                                              0x00000000U

// Field:     [2] RTOUT
//
// SPI Receive Time-Out event. This interrupt is set if no activity is detected
// on the input clock line within the time period dictated by CTL1.RTOUT value.
// This is applicable only in peripheral mode.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_RTOUT                                               0x00000004U
#define SPI_RIS_RTOUT_M                                             0x00000004U
#define SPI_RIS_RTOUT_S                                                      2U
#define SPI_RIS_RTOUT_SET                                           0x00000004U
#define SPI_RIS_RTOUT_CLR                                           0x00000000U

// Field:     [1] PER
//
// Parity error event. This bit is set if a Parity error has been detected
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_PER                                                 0x00000002U
#define SPI_RIS_PER_M                                               0x00000002U
#define SPI_RIS_PER_S                                                        1U
#define SPI_RIS_PER_SET                                             0x00000002U
#define SPI_RIS_PER_CLR                                             0x00000000U

// Field:     [0] RXOVF
//
// RXFIFO overflow event. This interrupt is set if an RX FIFO overflow has been
// detected.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_RIS_RXOVF                                               0x00000001U
#define SPI_RIS_RXOVF_M                                             0x00000001U
#define SPI_RIS_RXOVF_S                                                      0U
#define SPI_RIS_RXOVF_SET                                           0x00000001U
#define SPI_RIS_RXOVF_CLR                                           0x00000000U

//*****************************************************************************
//
// Register: SPI_O_MIS
//
//*****************************************************************************
// Field:     [8] DMATX
//
// Masked DMA Done event for TX.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_DMATX                                               0x00000100U
#define SPI_MIS_DMATX_M                                             0x00000100U
#define SPI_MIS_DMATX_S                                                      8U
#define SPI_MIS_DMATX_SET                                           0x00000100U
#define SPI_MIS_DMATX_CLR                                           0x00000000U

// Field:     [7] DMARX
//
// Masked DMA Done event for RX.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_DMARX                                               0x00000080U
#define SPI_MIS_DMARX_M                                             0x00000080U
#define SPI_MIS_DMARX_S                                                      7U
#define SPI_MIS_DMARX_SET                                           0x00000080U
#define SPI_MIS_DMARX_CLR                                           0x00000000U

// Field:     [6] IDLE
//
// Masked SPI IDLE event.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_IDLE                                                0x00000040U
#define SPI_MIS_IDLE_M                                              0x00000040U
#define SPI_MIS_IDLE_S                                                       6U
#define SPI_MIS_IDLE_SET                                            0x00000040U
#define SPI_MIS_IDLE_CLR                                            0x00000000U

// Field:     [5] TXEMPTY
//
// Masked Transmit FIFO Empty event.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_TXEMPTY                                             0x00000020U
#define SPI_MIS_TXEMPTY_M                                           0x00000020U
#define SPI_MIS_TXEMPTY_S                                                    5U
#define SPI_MIS_TXEMPTY_SET                                         0x00000020U
#define SPI_MIS_TXEMPTY_CLR                                         0x00000000U

// Field:     [4] TX
//
// Masked Transmit FIFO event.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_TX                                                  0x00000010U
#define SPI_MIS_TX_M                                                0x00000010U
#define SPI_MIS_TX_S                                                         4U
#define SPI_MIS_TX_SET                                              0x00000010U
#define SPI_MIS_TX_CLR                                              0x00000000U

// Field:     [3] RX
//
// Masked Receive FIFO event.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_RX                                                  0x00000008U
#define SPI_MIS_RX_M                                                0x00000008U
#define SPI_MIS_RX_S                                                         3U
#define SPI_MIS_RX_SET                                              0x00000008U
#define SPI_MIS_RX_CLR                                              0x00000000U

// Field:     [2] RTOUT
//
// Masked SPI Receive Time-Out event.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_RTOUT                                               0x00000004U
#define SPI_MIS_RTOUT_M                                             0x00000004U
#define SPI_MIS_RTOUT_S                                                      2U
#define SPI_MIS_RTOUT_SET                                           0x00000004U
#define SPI_MIS_RTOUT_CLR                                           0x00000000U

// Field:     [1] PER
//
// Masked Parity error event.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_PER                                                 0x00000002U
#define SPI_MIS_PER_M                                               0x00000002U
#define SPI_MIS_PER_S                                                        1U
#define SPI_MIS_PER_SET                                             0x00000002U
#define SPI_MIS_PER_CLR                                             0x00000000U

// Field:     [0] RXOVF
//
// Masked RXFIFO overflow event.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define SPI_MIS_RXOVF                                               0x00000001U
#define SPI_MIS_RXOVF_M                                             0x00000001U
#define SPI_MIS_RXOVF_S                                                      0U
#define SPI_MIS_RXOVF_SET                                           0x00000001U
#define SPI_MIS_RXOVF_CLR                                           0x00000000U

//*****************************************************************************
//
// Register: SPI_O_ISET
//
//*****************************************************************************
// Field:     [8] DMATX
//
// Set DMA Done event for TX.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_DMATX                                              0x00000100U
#define SPI_ISET_DMATX_M                                            0x00000100U
#define SPI_ISET_DMATX_S                                                     8U
#define SPI_ISET_DMATX_SET                                          0x00000100U
#define SPI_ISET_DMATX_NOEFF                                        0x00000000U

// Field:     [7] DMARX
//
// Set DMA Done event for RX.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_DMARX                                              0x00000080U
#define SPI_ISET_DMARX_M                                            0x00000080U
#define SPI_ISET_DMARX_S                                                     7U
#define SPI_ISET_DMARX_SET                                          0x00000080U
#define SPI_ISET_DMARX_NOEFF                                        0x00000000U

// Field:     [6] IDLE
//
// Set SPI IDLE event.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_IDLE                                               0x00000040U
#define SPI_ISET_IDLE_M                                             0x00000040U
#define SPI_ISET_IDLE_S                                                      6U
#define SPI_ISET_IDLE_SET                                           0x00000040U
#define SPI_ISET_IDLE_NOEFF                                         0x00000000U

// Field:     [5] TXEMPTY
//
// Set Transmit FIFO Empty event.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_TXEMPTY                                            0x00000020U
#define SPI_ISET_TXEMPTY_M                                          0x00000020U
#define SPI_ISET_TXEMPTY_S                                                   5U
#define SPI_ISET_TXEMPTY_SET                                        0x00000020U
#define SPI_ISET_TXEMPTY_NOEFF                                      0x00000000U

// Field:     [4] TX
//
// Set Transmit FIFO event.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_TX                                                 0x00000010U
#define SPI_ISET_TX_M                                               0x00000010U
#define SPI_ISET_TX_S                                                        4U
#define SPI_ISET_TX_SET                                             0x00000010U
#define SPI_ISET_TX_NOEFF                                           0x00000000U

// Field:     [3] RX
//
// Set Receive FIFO event.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_RX                                                 0x00000008U
#define SPI_ISET_RX_M                                               0x00000008U
#define SPI_ISET_RX_S                                                        3U
#define SPI_ISET_RX_SET                                             0x00000008U
#define SPI_ISET_RX_NOEFF                                           0x00000000U

// Field:     [2] RTOUT
//
// Set SPI Receive Time-Out Event.
// ENUMs:
// SET                      Set Interrupt Mask
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_RTOUT                                              0x00000004U
#define SPI_ISET_RTOUT_M                                            0x00000004U
#define SPI_ISET_RTOUT_S                                                     2U
#define SPI_ISET_RTOUT_SET                                          0x00000004U
#define SPI_ISET_RTOUT_NOEFF                                        0x00000000U

// Field:     [1] PER
//
// Set Parity error event.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_PER                                                0x00000002U
#define SPI_ISET_PER_M                                              0x00000002U
#define SPI_ISET_PER_S                                                       1U
#define SPI_ISET_PER_SET                                            0x00000002U
#define SPI_ISET_PER_NOEFF                                          0x00000000U

// Field:     [0] RXOVF
//
// Set RXFIFO overflow event.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ISET_RXOVF                                              0x00000001U
#define SPI_ISET_RXOVF_M                                            0x00000001U
#define SPI_ISET_RXOVF_S                                                     0U
#define SPI_ISET_RXOVF_SET                                          0x00000001U
#define SPI_ISET_RXOVF_NOEFF                                        0x00000000U

//*****************************************************************************
//
// Register: SPI_O_ICLR
//
//*****************************************************************************
// Field:     [8] DMATX
//
// Clear DMA Done event for TX.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_DMATX                                              0x00000100U
#define SPI_ICLR_DMATX_M                                            0x00000100U
#define SPI_ICLR_DMATX_S                                                     8U
#define SPI_ICLR_DMATX_CLR                                          0x00000100U
#define SPI_ICLR_DMATX_NOEFF                                        0x00000000U

// Field:     [7] DMARX
//
// Clear DMA Done event for RX.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_DMARX                                              0x00000080U
#define SPI_ICLR_DMARX_M                                            0x00000080U
#define SPI_ICLR_DMARX_S                                                     7U
#define SPI_ICLR_DMARX_CLR                                          0x00000080U
#define SPI_ICLR_DMARX_NOEFF                                        0x00000000U

// Field:     [6] IDLE
//
// Clear SPI IDLE event.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_IDLE                                               0x00000040U
#define SPI_ICLR_IDLE_M                                             0x00000040U
#define SPI_ICLR_IDLE_S                                                      6U
#define SPI_ICLR_IDLE_CLR                                           0x00000040U
#define SPI_ICLR_IDLE_NOEFF                                         0x00000000U

// Field:     [5] TXEMPTY
//
// Clear Transmit FIFO Empty event.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_TXEMPTY                                            0x00000020U
#define SPI_ICLR_TXEMPTY_M                                          0x00000020U
#define SPI_ICLR_TXEMPTY_S                                                   5U
#define SPI_ICLR_TXEMPTY_CLR                                        0x00000020U
#define SPI_ICLR_TXEMPTY_NOEFF                                      0x00000000U

// Field:     [4] TX
//
// Clear Transmit FIFO event.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_TX                                                 0x00000010U
#define SPI_ICLR_TX_M                                               0x00000010U
#define SPI_ICLR_TX_S                                                        4U
#define SPI_ICLR_TX_CLR                                             0x00000010U
#define SPI_ICLR_TX_NOEFF                                           0x00000000U

// Field:     [3] RX
//
// Clear Receive FIFO event.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_RX                                                 0x00000008U
#define SPI_ICLR_RX_M                                               0x00000008U
#define SPI_ICLR_RX_S                                                        3U
#define SPI_ICLR_RX_CLR                                             0x00000008U
#define SPI_ICLR_RX_NOEFF                                           0x00000000U

// Field:     [2] RTOUT
//
// Clear SPI Receive Time-Out Event.
// ENUMs:
// CLR                      Set Interrupt Mask
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_RTOUT                                              0x00000004U
#define SPI_ICLR_RTOUT_M                                            0x00000004U
#define SPI_ICLR_RTOUT_S                                                     2U
#define SPI_ICLR_RTOUT_CLR                                          0x00000004U
#define SPI_ICLR_RTOUT_NOEFF                                        0x00000000U

// Field:     [1] PER
//
// Clear Parity error event.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_PER                                                0x00000002U
#define SPI_ICLR_PER_M                                              0x00000002U
#define SPI_ICLR_PER_S                                                       1U
#define SPI_ICLR_PER_CLR                                            0x00000002U
#define SPI_ICLR_PER_NOEFF                                          0x00000000U

// Field:     [0] RXOVF
//
// Clear RXFIFO overflow event.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SPI_ICLR_RXOVF                                              0x00000001U
#define SPI_ICLR_RXOVF_M                                            0x00000001U
#define SPI_ICLR_RXOVF_S                                                     0U
#define SPI_ICLR_RXOVF_CLR                                          0x00000001U
#define SPI_ICLR_RXOVF_NOEFF                                        0x00000000U

//*****************************************************************************
//
// Register: SPI_O_IMSET
//
//*****************************************************************************
// Field:     [8] DMATX
//
// Set DMA Done for TX event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_DMATX                                             0x00000100U
#define SPI_IMSET_DMATX_M                                           0x00000100U
#define SPI_IMSET_DMATX_S                                                    8U
#define SPI_IMSET_DMATX_SET                                         0x00000100U
#define SPI_IMSET_DMATX_NOEFF                                       0x00000000U

// Field:     [7] DMARX
//
// Set DMA Done for RX event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_DMARX                                             0x00000080U
#define SPI_IMSET_DMARX_M                                           0x00000080U
#define SPI_IMSET_DMARX_S                                                    7U
#define SPI_IMSET_DMARX_SET                                         0x00000080U
#define SPI_IMSET_DMARX_NOEFF                                       0x00000000U

// Field:     [6] IDLE
//
// Set SPI IDLE event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_IDLE                                              0x00000040U
#define SPI_IMSET_IDLE_M                                            0x00000040U
#define SPI_IMSET_IDLE_S                                                     6U
#define SPI_IMSET_IDLE_SET                                          0x00000040U
#define SPI_IMSET_IDLE_NOEFF                                        0x00000000U

// Field:     [5] TXEMPTY
//
// Set Transmit FIFO Empty event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_TXEMPTY                                           0x00000020U
#define SPI_IMSET_TXEMPTY_M                                         0x00000020U
#define SPI_IMSET_TXEMPTY_S                                                  5U
#define SPI_IMSET_TXEMPTY_SET                                       0x00000020U
#define SPI_IMSET_TXEMPTY_NOEFF                                     0x00000000U

// Field:     [4] TX
//
// Set Transmit FIFO event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_TX                                                0x00000010U
#define SPI_IMSET_TX_M                                              0x00000010U
#define SPI_IMSET_TX_S                                                       4U
#define SPI_IMSET_TX_SET                                            0x00000010U
#define SPI_IMSET_TX_NOEFF                                          0x00000000U

// Field:     [3] RX
//
// Set Receive FIFO event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_RX                                                0x00000008U
#define SPI_IMSET_RX_M                                              0x00000008U
#define SPI_IMSET_RX_S                                                       3U
#define SPI_IMSET_RX_SET                                            0x00000008U
#define SPI_IMSET_RX_NOEFF                                          0x00000000U

// Field:     [2] RTOUT
//
// Set SPI Receive Time-Out event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_RTOUT                                             0x00000004U
#define SPI_IMSET_RTOUT_M                                           0x00000004U
#define SPI_IMSET_RTOUT_S                                                    2U
#define SPI_IMSET_RTOUT_SET                                         0x00000004U
#define SPI_IMSET_RTOUT_NOEFF                                       0x00000000U

// Field:     [1] PER
//
// Set Parity error event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_PER                                               0x00000002U
#define SPI_IMSET_PER_M                                             0x00000002U
#define SPI_IMSET_PER_S                                                      1U
#define SPI_IMSET_PER_SET                                           0x00000002U
#define SPI_IMSET_PER_NOEFF                                         0x00000000U

// Field:     [0] RXOVF
//
// Set RXFIFO overflow event mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMSET_RXOVF                                             0x00000001U
#define SPI_IMSET_RXOVF_M                                           0x00000001U
#define SPI_IMSET_RXOVF_S                                                    0U
#define SPI_IMSET_RXOVF_SET                                         0x00000001U
#define SPI_IMSET_RXOVF_NOEFF                                       0x00000000U

//*****************************************************************************
//
// Register: SPI_O_IMCLR
//
//*****************************************************************************
// Field:     [8] DMATX
//
// Clear DMA Done for TX event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_DMATX                                             0x00000100U
#define SPI_IMCLR_DMATX_M                                           0x00000100U
#define SPI_IMCLR_DMATX_S                                                    8U
#define SPI_IMCLR_DMATX_CLR                                         0x00000100U
#define SPI_IMCLR_DMATX_NOEFF                                       0x00000000U

// Field:     [7] DMARX
//
// Clear DMA Done for RX event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_DMARX                                             0x00000080U
#define SPI_IMCLR_DMARX_M                                           0x00000080U
#define SPI_IMCLR_DMARX_S                                                    7U
#define SPI_IMCLR_DMARX_CLR                                         0x00000080U
#define SPI_IMCLR_DMARX_NOEFF                                       0x00000000U

// Field:     [6] IDLE
//
// Clear SPI IDLE event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_IDLE                                              0x00000040U
#define SPI_IMCLR_IDLE_M                                            0x00000040U
#define SPI_IMCLR_IDLE_S                                                     6U
#define SPI_IMCLR_IDLE_CLR                                          0x00000040U
#define SPI_IMCLR_IDLE_NOEFF                                        0x00000000U

// Field:     [5] TXEMPTY
//
// Clear Transmit FIFO Empty event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_TXEMPTY                                           0x00000020U
#define SPI_IMCLR_TXEMPTY_M                                         0x00000020U
#define SPI_IMCLR_TXEMPTY_S                                                  5U
#define SPI_IMCLR_TXEMPTY_CLR                                       0x00000020U
#define SPI_IMCLR_TXEMPTY_NOEFF                                     0x00000000U

// Field:     [4] TX
//
// Clear Transmit FIFO event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_TX                                                0x00000010U
#define SPI_IMCLR_TX_M                                              0x00000010U
#define SPI_IMCLR_TX_S                                                       4U
#define SPI_IMCLR_TX_CLR                                            0x00000010U
#define SPI_IMCLR_TX_NOEFF                                          0x00000000U

// Field:     [3] RX
//
// Clear Receive FIFO event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_RX                                                0x00000008U
#define SPI_IMCLR_RX_M                                              0x00000008U
#define SPI_IMCLR_RX_S                                                       3U
#define SPI_IMCLR_RX_CLR                                            0x00000008U
#define SPI_IMCLR_RX_NOEFF                                          0x00000000U

// Field:     [2] RTOUT
//
// Clear SPI Receive Time-Out event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_RTOUT                                             0x00000004U
#define SPI_IMCLR_RTOUT_M                                           0x00000004U
#define SPI_IMCLR_RTOUT_S                                                    2U
#define SPI_IMCLR_RTOUT_CLR                                         0x00000004U
#define SPI_IMCLR_RTOUT_NOEFF                                       0x00000000U

// Field:     [1] PER
//
// Clear Parity error event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_PER                                               0x00000002U
#define SPI_IMCLR_PER_M                                             0x00000002U
#define SPI_IMCLR_PER_S                                                      1U
#define SPI_IMCLR_PER_CLR                                           0x00000002U
#define SPI_IMCLR_PER_NOEFF                                         0x00000000U

// Field:     [0] RXOVF
//
// Clear RXFIFO overflow event mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SPI_IMCLR_RXOVF                                             0x00000001U
#define SPI_IMCLR_RXOVF_M                                           0x00000001U
#define SPI_IMCLR_RXOVF_S                                                    0U
#define SPI_IMCLR_RXOVF_CLR                                         0x00000001U
#define SPI_IMCLR_RXOVF_NOEFF                                       0x00000000U

//*****************************************************************************
//
// Register: SPI_O_EMU
//
//*****************************************************************************
// Field:     [0] HALT
//
// Halt control
// ENUMs:
// STOP                      Freeze option. The IP freezes functionality when
//                          the core halted input is asserted, and resumes
//                          when it is deasserted. The freeze can either be
//                          immediate or after the IP has reached a
//                          boundary (end of word boundary, based on DSS
//                          configuration) from where it can resume without
//                          corruption.
// RUN                      Free run option. The IP ignores the state of the
//                          core halted input.
#define SPI_EMU_HALT                                                0x00000001U
#define SPI_EMU_HALT_M                                              0x00000001U
#define SPI_EMU_HALT_S                                                       0U
#define SPI_EMU_HALT_STOP                                           0x00000001U
#define SPI_EMU_HALT_RUN                                            0x00000000U

//*****************************************************************************
//
// Register: SPI_O_CTL0
//
//*****************************************************************************
// Field:    [17] IDLEPOCI
//
// The Idle value of POCI - when TXFIFO is empty and before data is written
// into TXFIFO - can be controlled by this field.
// ENUMs:
// IDLE_ONE                 POCI outputs idle value of '1'
// IDLE_ZERO                POCI output idle value of '0'
#define SPI_CTL0_IDLEPOCI                                           0x00020000U
#define SPI_CTL0_IDLEPOCI_M                                         0x00020000U
#define SPI_CTL0_IDLEPOCI_S                                                 17U
#define SPI_CTL0_IDLEPOCI_IDLE_ONE                                  0x00020000U
#define SPI_CTL0_IDLEPOCI_IDLE_ZERO                                 0x00000000U

// Field:    [16] GPCRCEN
//
// General purpose CRC enable. This bit enables transmit side CRC unit for
// general purpose use by software when SPI is disabled (CTL1.EN = 0). This bit
// must be 0 when SPI is enabled.
// ENUMs:
// EN                       Transmit side CRC unit is available for general
//                          purpose software use
// DIS                      Transmit side CRC unit is not available for
//                          general purpose software use
#define SPI_CTL0_GPCRCEN                                            0x00010000U
#define SPI_CTL0_GPCRCEN_M                                          0x00010000U
#define SPI_CTL0_GPCRCEN_S                                                  16U
#define SPI_CTL0_GPCRCEN_EN                                         0x00010000U
#define SPI_CTL0_GPCRCEN_DIS                                        0x00000000U

// Field:    [15] CRCPOLY
//
// CRC polynomial selection.
// ENUMs:
// SIZE16BIT                Selects 16-bit CCITT CRC polynomial
// SIZE8BIT                 Selects 8-bit CCITT CRC polynomial
#define SPI_CTL0_CRCPOLY                                            0x00008000U
#define SPI_CTL0_CRCPOLY_M                                          0x00008000U
#define SPI_CTL0_CRCPOLY_S                                                  15U
#define SPI_CTL0_CRCPOLY_SIZE16BIT                                  0x00008000U
#define SPI_CTL0_CRCPOLY_SIZE8BIT                                   0x00000000U

// Field:    [14] AUTOCRC
//
// Auto insert CRC
// ENUMs:
// EN                       Insert CRC into TXFIFO upon TXFIFO underflow
// DIS                      Do not insert CRC into TXFIFO upon TXFIFO
//                          underflow
#define SPI_CTL0_AUTOCRC                                            0x00004000U
#define SPI_CTL0_AUTOCRC_M                                          0x00004000U
#define SPI_CTL0_AUTOCRC_S                                                  14U
#define SPI_CTL0_AUTOCRC_EN                                         0x00004000U
#define SPI_CTL0_AUTOCRC_DIS                                        0x00000000U

// Field:    [13] CRCEND
//
// CRC16 Endianness
// ENUMs:
// CRC_END_LSB              Auto-insertion of CRC16 is least-significant byte
//                          first
// CRC_END_MSB              Auto-insertion of CRC16 is most-significant byte
//                          first
#define SPI_CTL0_CRCEND                                             0x00002000U
#define SPI_CTL0_CRCEND_M                                           0x00002000U
#define SPI_CTL0_CRCEND_S                                                   13U
#define SPI_CTL0_CRCEND_CRC_END_LSB                                 0x00002000U
#define SPI_CTL0_CRCEND_CRC_END_MSB                                 0x00000000U

// Field:    [12] CSCLR
//
// Clear shift register counter on CS inactive.
// This bit is relevant only in the peripheral mode, when CTL1.MS=0.
// ENUMs:
// EN                       Enable automatic clear of shift register when CS
//                          goes inactive.
// DIS                      Disable automatic clear of shift register when CS
//                          goes inactive.
#define SPI_CTL0_CSCLR                                              0x00001000U
#define SPI_CTL0_CSCLR_M                                            0x00001000U
#define SPI_CTL0_CSCLR_S                                                    12U
#define SPI_CTL0_CSCLR_EN                                           0x00001000U
#define SPI_CTL0_CSCLR_DIS                                          0x00000000U

// Field:    [11] FIFORST
//
// This bit is used to reset transmit and receive FIFO pointers. This bit is
// auto cleared once the FIFO pointer reset operation is completed.
// ENUMs:
// RST_TRIG                 Trigger FIFO pointers reset when written to 1.
// RST_DONE                 FIFO pointers reset completed when 0 is read
#define SPI_CTL0_FIFORST                                            0x00000800U
#define SPI_CTL0_FIFORST_M                                          0x00000800U
#define SPI_CTL0_FIFORST_S                                                  11U
#define SPI_CTL0_FIFORST_RST_TRIG                                   0x00000800U
#define SPI_CTL0_FIFORST_RST_DONE                                   0x00000000U

// Field:    [10] HWCSN
//
// Hardware controlled chip select (CS) value. When set CS is zero till TX FIFO
// is empty, as in -
// a.	CS is de-asserted
// b.	All data bytes are transmitted
// c.	CS is asserted
// ENUMs:
// EN                       HWCSN Enable
// DIS                      HWCSN Disable
#define SPI_CTL0_HWCSN                                              0x00000400U
#define SPI_CTL0_HWCSN_M                                            0x00000400U
#define SPI_CTL0_HWCSN_S                                                    10U
#define SPI_CTL0_HWCSN_EN                                           0x00000400U
#define SPI_CTL0_HWCSN_DIS                                          0x00000000U

// Field:     [9] SPH
//
// SCLK phase (Motorola SPI frame format only).
// This bit selects the clock edge that captures data and enables it to change
// state.
// It has the most impact on the first bit transmitted by either permitting or
// not permitting a clock transition before the first data capture clock edge.
// ENUMs:
// SECOND                   Data is captured on the second clock edge
//                          transition.
// FIRST                    Data is captured on the first clock edge
//                          transition.
#define SPI_CTL0_SPH                                                0x00000200U
#define SPI_CTL0_SPH_M                                              0x00000200U
#define SPI_CTL0_SPH_S                                                       9U
#define SPI_CTL0_SPH_SECOND                                         0x00000200U
#define SPI_CTL0_SPH_FIRST                                          0x00000000U

// Field:     [8] SPO
//
// SCLK polarity (Motorola SPI frame format only).
// ENUMs:
// HI                       SPI produces a steady state HI value on the SCLK
// LO                       SPI produces a steady state LO value on the SCLK
#define SPI_CTL0_SPO                                                0x00000100U
#define SPI_CTL0_SPO_M                                              0x00000100U
#define SPI_CTL0_SPO_S                                                       8U
#define SPI_CTL0_SPO_HI                                             0x00000100U
#define SPI_CTL0_SPO_LO                                             0x00000000U

// Field:   [6:5] FRF
//
// Frame format select
// ENUMs:
// MICROWIRE                MICROWIRE frame format
// TI_SYNC                  TI synchronous serial frame format
// MOTOROLA_4WIRE           Motorola SPI frame format (4-wire mode)
// MOTOROLA_3WIRE           Motorola SPI frame format (3-wire mode)
#define SPI_CTL0_FRF_W                                                       2U
#define SPI_CTL0_FRF_M                                              0x00000060U
#define SPI_CTL0_FRF_S                                                       5U
#define SPI_CTL0_FRF_MICROWIRE                                      0x00000060U
#define SPI_CTL0_FRF_TI_SYNC                                        0x00000040U
#define SPI_CTL0_FRF_MOTOROLA_4WIRE                                 0x00000020U
#define SPI_CTL0_FRF_MOTOROLA_3WIRE                                 0x00000000U

// Field:   [3:0] DSS
//
// Data size select. The applicable DSS values for controller mode operation
// are 0x3 to 0xF and for peripheral mode operation are 0x6 to 0xF. DSS values
// 0x0 to 0x2 are reserved and must not be used.
// ENUMs:
// BITS_16                  16-bits data size
// BITS_15                  15-bits data size
// BITS_14                  14-bits data size
// BITS_13                  13-bits data size
// BITS_12                  12-bits data size
// BITS_11                  11-bits data size
// BITS_10                  10-bits data size
// BITS_9                   9-bits data size
// BITS_8                   8-bits data size
// BITS_7                   7-bits data size
// BITS_6                   6-bits data size
// BITS_5                   5-bits data size
// BITS_4                   4-bits data size
#define SPI_CTL0_DSS_W                                                       4U
#define SPI_CTL0_DSS_M                                              0x0000000FU
#define SPI_CTL0_DSS_S                                                       0U
#define SPI_CTL0_DSS_BITS_16                                        0x0000000FU
#define SPI_CTL0_DSS_BITS_15                                        0x0000000EU
#define SPI_CTL0_DSS_BITS_14                                        0x0000000DU
#define SPI_CTL0_DSS_BITS_13                                        0x0000000CU
#define SPI_CTL0_DSS_BITS_12                                        0x0000000BU
#define SPI_CTL0_DSS_BITS_11                                        0x0000000AU
#define SPI_CTL0_DSS_BITS_10                                        0x00000009U
#define SPI_CTL0_DSS_BITS_9                                         0x00000008U
#define SPI_CTL0_DSS_BITS_8                                         0x00000007U
#define SPI_CTL0_DSS_BITS_7                                         0x00000006U
#define SPI_CTL0_DSS_BITS_6                                         0x00000005U
#define SPI_CTL0_DSS_BITS_5                                         0x00000004U
#define SPI_CTL0_DSS_BITS_4                                         0x00000003U

//*****************************************************************************
//
// Register: SPI_O_CTL1
//
//*****************************************************************************
// Field: [29:24] RTOUT
//
// Receive Timeout (only for Peripheral mode)
// Defines the number of  CLKSVT clock cycles after which the Receive Timeout
// flag RIS.RTOUT is set.
// A value of 0 disables this function.
#define SPI_CTL1_RTOUT_W                                                     6U
#define SPI_CTL1_RTOUT_M                                            0x3F000000U
#define SPI_CTL1_RTOUT_S                                                    24U

// Field: [23:16] REPTX
//
// Counter to repeat last transfer (only in controller mode)
// 0: repeat last transfer is disabled.
// x: repeat the last transfer with the provided value.
// The transfer will be started with writing a data into the TX FIFO. Sending
// the data will be repeated REPTX number of times, so the data will be
// transferred x+1 times in total.
// It can be used to clean a transfer or to pull a certain amount of data by a
// peripheral.
// ENUMs:
// DIS                      REPTX disable
#define SPI_CTL1_REPTX_W                                                     8U
#define SPI_CTL1_REPTX_M                                            0x00FF0000U
#define SPI_CTL1_REPTX_S                                                    16U
#define SPI_CTL1_REPTX_DIS                                          0x00000000U

// Field: [15:12] CDMODE
//
// Command Data Mode. This bit field value determines the behavior of C/D or CS
// signal when CDEN = 1. CS pin held low indicates command phase and CS pin
// held high indicates data phase.
// When CDMODE = 0x0, the CS pin is always held high during transfer indicating
// data phase only operation (manual mode).
// When CDMODE = 0xF, the CS pin is always held low during transfer indicating
// command phase only operation (manual mode).
// When CDMODE = 0x1 to 0xE, the CS pin is held low for the number of bytes
// indicated by CDMODE value for the command phase and held high for the
// remaining transfers in the data phase (automatic mode).
// When CDMODE is set to value 0x1 to 0xE, reading CDMODE during operation
// indicates the remaining bytes to be transferred in the command phase.
// ENUMs:
// COMMAND                  Manual mode: Command
// DATA                     Manual mode: Data
#define SPI_CTL1_CDMODE_W                                                    4U
#define SPI_CTL1_CDMODE_M                                           0x0000F000U
#define SPI_CTL1_CDMODE_S                                                   12U
#define SPI_CTL1_CDMODE_COMMAND                                     0x0000F000U
#define SPI_CTL1_CDMODE_DATA                                        0x00000000U

// Field:    [11] CDEN
//
// Command/Data mode enable. This feature is applicable only in controller mode
// and for 8-bit transfers (CTL0.DSS = 7). The chip select pin is used for
// command/data signaling in Motorola SPI frame format (3-wire) operation.
// ENUMs:
// EN                       C/D Mode Enable
// DIS                      C/D Mode Disable
#define SPI_CTL1_CDEN                                               0x00000800U
#define SPI_CTL1_CDEN_M                                             0x00000800U
#define SPI_CTL1_CDEN_S                                                     11U
#define SPI_CTL1_CDEN_EN                                            0x00000800U
#define SPI_CTL1_CDEN_DIS                                           0x00000000U

// Field:     [7] PBS
//
// Parity bit select
// ENUMs:
// BIT1                     Bit 1 is used for Parity, Bit 0 is ignored
// BIT0                     Bit 0 is used for Parity
#define SPI_CTL1_PBS                                                0x00000080U
#define SPI_CTL1_PBS_M                                              0x00000080U
#define SPI_CTL1_PBS_S                                                       7U
#define SPI_CTL1_PBS_BIT1                                           0x00000080U
#define SPI_CTL1_PBS_BIT0                                           0x00000000U

// Field:     [6] PES
//
// Even parity select.
// ENUMs:
// EVEN                     Even Parity mode
// ODD                      Odd Parity mode
#define SPI_CTL1_PES                                                0x00000040U
#define SPI_CTL1_PES_M                                              0x00000040U
#define SPI_CTL1_PES_S                                                       6U
#define SPI_CTL1_PES_EVEN                                           0x00000040U
#define SPI_CTL1_PES_ODD                                            0x00000000U

// Field:     [5] PEN
//
// Parity enable. If enabled the last bit will be used as parity to evaluate
// the correct reception of the previous bits.
// In case of parity mismatch the parity error flag RIS.PER will be set. This
// feature is available only in SPI controller mode.
// ENUMs:
// EN                       Enable Parity function
// DIS                      Disable Parity function
#define SPI_CTL1_PEN                                                0x00000020U
#define SPI_CTL1_PEN_M                                              0x00000020U
#define SPI_CTL1_PEN_S                                                       5U
#define SPI_CTL1_PEN_EN                                             0x00000020U
#define SPI_CTL1_PEN_DIS                                            0x00000000U

// Field:     [4] MSB
//
// MSB first select. Controls the direction of receive and transmit shift
// register. MSB first configuration (MSB = 1) must be selected when CRC
// feature is used for SPI communication.
// ENUMs:
// MSB                      MSB first
// LSB                      LSB first
#define SPI_CTL1_MSB                                                0x00000010U
#define SPI_CTL1_MSB_M                                              0x00000010U
#define SPI_CTL1_MSB_S                                                       4U
#define SPI_CTL1_MSB_MSB                                            0x00000010U
#define SPI_CTL1_MSB_LSB                                            0x00000000U

// Field:     [3] POD
//
// Peripheral data output disable.
// This bit is relevant only in the peripheral mode, MS=1. In
// multiple-peripheral systems, it is possible for a SPI controller to
// broadcast a message to all peripherals in the system while ensuring that
// only one peripheral drives data onto its serial output line. In such systems
// the POCI lines from multiple peripherals could be tied together. To operate
// in such systems, this bit field can be set if the SPI peripheral is not
// supposed to drive the POCI output.
// ENUMs:
// EN                       SPI cannot drive the POCI output in peripheral
//                          mode.
// DIS                      SPI can drive the POCI output in peripheral mode.
#define SPI_CTL1_POD                                                0x00000008U
#define SPI_CTL1_POD_M                                              0x00000008U
#define SPI_CTL1_POD_S                                                       3U
#define SPI_CTL1_POD_EN                                             0x00000008U
#define SPI_CTL1_POD_DIS                                            0x00000000U

// Field:     [2] MS
//
// Controller or peripheral mode select. This bit can be modified only when SPI
// is disabled, CTL1.EN=0.
// ENUMs:
// CONTROLLER               Select Controller mode
// PERIPHERAL               Select Peripheral mode
#define SPI_CTL1_MS                                                 0x00000004U
#define SPI_CTL1_MS_M                                               0x00000004U
#define SPI_CTL1_MS_S                                                        2U
#define SPI_CTL1_MS_CONTROLLER                                      0x00000004U
#define SPI_CTL1_MS_PERIPHERAL                                      0x00000000U

// Field:     [1] LBM
//
// Loop back mode control
// ENUMs:
// EN                       Enable loopback mode. Output of transmit serial
//                          shifter is connected to input of receive serial
//                          shifter internally.
// DIS                      Disable loopback mode. Normal serial port
//                          operation enabled.
#define SPI_CTL1_LBM                                                0x00000002U
#define SPI_CTL1_LBM_M                                              0x00000002U
#define SPI_CTL1_LBM_S                                                       1U
#define SPI_CTL1_LBM_EN                                             0x00000002U
#define SPI_CTL1_LBM_DIS                                            0x00000000U

// Field:     [0] EN
//
// SPI enable.
// NOTE: This bit field must be set to 1 using a separate write access, after
// the other bit fields have been configured.
// ENUMs:
// EN                       SPI Enabled and released for operation.
// DIS                      SPI is disabled
#define SPI_CTL1_EN                                                 0x00000001U
#define SPI_CTL1_EN_M                                               0x00000001U
#define SPI_CTL1_EN_S                                                        0U
#define SPI_CTL1_EN_EN                                              0x00000001U
#define SPI_CTL1_EN_DIS                                             0x00000000U

//*****************************************************************************
//
// Register: SPI_O_CLKCFG0
//
//*****************************************************************************
// Field:   [2:0] PRESC
//
// Prescaler configuration
// ENUMs:
// DIV_BY_8                 Divide clock source by 8
// DIV_BY_7                 Divide clock source by 7
// DIV_BY_6                 Divide clock source by 6
// DIV_BY_5                 Divide clock source by 5
// DIV_BY_4                 Divide clock source by 4
// DIV_BY_3                 Divide clock source by 3
// DIV_BY_2                 Divide clock source by 2
// DIV_BY_1                 Do not divide clock source
#define SPI_CLKCFG0_PRESC_W                                                  3U
#define SPI_CLKCFG0_PRESC_M                                         0x00000007U
#define SPI_CLKCFG0_PRESC_S                                                  0U
#define SPI_CLKCFG0_PRESC_DIV_BY_8                                  0x00000007U
#define SPI_CLKCFG0_PRESC_DIV_BY_7                                  0x00000006U
#define SPI_CLKCFG0_PRESC_DIV_BY_6                                  0x00000005U
#define SPI_CLKCFG0_PRESC_DIV_BY_5                                  0x00000004U
#define SPI_CLKCFG0_PRESC_DIV_BY_4                                  0x00000003U
#define SPI_CLKCFG0_PRESC_DIV_BY_3                                  0x00000002U
#define SPI_CLKCFG0_PRESC_DIV_BY_2                                  0x00000001U
#define SPI_CLKCFG0_PRESC_DIV_BY_1                                  0x00000000U

//*****************************************************************************
//
// Register: SPI_O_CLKCFG1
//
//*****************************************************************************
// Field: [19:16] DSAMPLE
//
// Delayed sampling. In controller mode the data on the POCI pin will be
// delayed sampled by the defined CLKSVT clock cycles. DSAMPLE values can range
// from 0 to SCR+1. Typically, values of 1 or 2 would suffice.
#define SPI_CLKCFG1_DSAMPLE_W                                                4U
#define SPI_CLKCFG1_DSAMPLE_M                                       0x000F0000U
#define SPI_CLKCFG1_DSAMPLE_S                                               16U

// Field:   [9:0] SCR
//
// Serial clock divider. This is used to generate the transmit and receive bit
// rate of the SPI.
// The SPI bit rate: (SPI functional clock frequency)/((SCR+1)*PRESC). SCR
// value can be from 0 to 1023.
#define SPI_CLKCFG1_SCR_W                                                   10U
#define SPI_CLKCFG1_SCR_M                                           0x000003FFU
#define SPI_CLKCFG1_SCR_S                                                    0U

//*****************************************************************************
//
// Register: SPI_O_IFLS
//
//*****************************************************************************
// Field:  [10:8] RXSEL
//
// Receive FIFO Level Select. The trigger points for the receive interrupt are
// as follows:
// ENUMs:
// LEVEL_1                  Trigger when RX FIFO contains >= 1 byte
// LVL_RES6                 Reserved
// LVL_FULL                 RX FIFO is full
// LVL_RES4                 Reserved
// LVL_3_4                  RX FIFO >= 3/4 full
// LVL_1_2                  RX FIFO >= 1/2 full (default)
// LVL_1_4                  RX FIFO >= 1/4 full
// LVL_OFF                  Reserved
#define SPI_IFLS_RXSEL_W                                                     3U
#define SPI_IFLS_RXSEL_M                                            0x00000700U
#define SPI_IFLS_RXSEL_S                                                     8U
#define SPI_IFLS_RXSEL_LEVEL_1                                      0x00000700U
#define SPI_IFLS_RXSEL_LVL_RES6                                     0x00000600U
#define SPI_IFLS_RXSEL_LVL_FULL                                     0x00000500U
#define SPI_IFLS_RXSEL_LVL_RES4                                     0x00000400U
#define SPI_IFLS_RXSEL_LVL_3_4                                      0x00000300U
#define SPI_IFLS_RXSEL_LVL_1_2                                      0x00000200U
#define SPI_IFLS_RXSEL_LVL_1_4                                      0x00000100U
#define SPI_IFLS_RXSEL_LVL_OFF                                      0x00000000U

// Field:   [2:0] TXSEL
//
// Transmit FIFO Level Select. The trigger points for the transmit interrupt
// are as follows:
// ENUMs:
// LEVEL_1                  Trigger when TX FIFO has >= 1 byte free
// LVL_RES6                 Reserved
// LVL_EMPTY                TX FIFO is empty
// LVL_RES4                 Reserved
// LVL_1_4                  TX FIFO <= 1/4 empty
// LVL_1_2                  TX FIFO <= 1/2 empty (default)
// LVL_3_4                  TX FIFO <= 3/4 empty
// LVL_OFF                  Reserved
#define SPI_IFLS_TXSEL_W                                                     3U
#define SPI_IFLS_TXSEL_M                                            0x00000007U
#define SPI_IFLS_TXSEL_S                                                     0U
#define SPI_IFLS_TXSEL_LEVEL_1                                      0x00000007U
#define SPI_IFLS_TXSEL_LVL_RES6                                     0x00000006U
#define SPI_IFLS_TXSEL_LVL_EMPTY                                    0x00000005U
#define SPI_IFLS_TXSEL_LVL_RES4                                     0x00000004U
#define SPI_IFLS_TXSEL_LVL_1_4                                      0x00000003U
#define SPI_IFLS_TXSEL_LVL_1_2                                      0x00000002U
#define SPI_IFLS_TXSEL_LVL_3_4                                      0x00000001U
#define SPI_IFLS_TXSEL_LVL_OFF                                      0x00000000U

//*****************************************************************************
//
// Register: SPI_O_DMACR
//
//*****************************************************************************
// Field:     [8] TXEN
//
// Transmit DMA enable. If this bit is set to 1, DMA for the transmit FIFO is
// enabled.
// ENUMs:
// EN                       Enable TX DMA
// DIS                      Disable TX DMA
#define SPI_DMACR_TXEN                                              0x00000100U
#define SPI_DMACR_TXEN_M                                            0x00000100U
#define SPI_DMACR_TXEN_S                                                     8U
#define SPI_DMACR_TXEN_EN                                           0x00000100U
#define SPI_DMACR_TXEN_DIS                                          0x00000000U

// Field:     [0] RXEN
//
// Receive DMA enable. If this bit is set to 1, DMA for the receive FIFO is
// enabled.
// ENUMs:
// EN                       Enable RX DMA
// DIS                      Disable RX DMA
#define SPI_DMACR_RXEN                                              0x00000001U
#define SPI_DMACR_RXEN_M                                            0x00000001U
#define SPI_DMACR_RXEN_S                                                     0U
#define SPI_DMACR_RXEN_EN                                           0x00000001U
#define SPI_DMACR_RXEN_DIS                                          0x00000000U

//*****************************************************************************
//
// Register: SPI_O_RXCRC
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// CRC value
// SW should read RXCRC register at the end of data transmission to
// reinitialize the seed value to all ones
#define SPI_RXCRC_DATA_W                                                    16U
#define SPI_RXCRC_DATA_M                                            0x0000FFFFU
#define SPI_RXCRC_DATA_S                                                     0U

//*****************************************************************************
//
// Register: SPI_O_TXCRC
//
//*****************************************************************************
// Field:    [31] AUTOCRCINS
//
// Status to indicate if Auto CRC has been inserted into TXFIFO.
// This is applicable only if CTL0.AUTOCRC enable bit is set.
// SW should read TXCRC register to clear auto inserted CRC at the end of the
// transfer.
// ENUMs:
// INS                      Auto CRC inserted
// NOTINS                   Auto CRC not yet inserted
#define SPI_TXCRC_AUTOCRCINS                                        0x80000000U
#define SPI_TXCRC_AUTOCRCINS_M                                      0x80000000U
#define SPI_TXCRC_AUTOCRCINS_S                                              31U
#define SPI_TXCRC_AUTOCRCINS_INS                                    0x80000000U
#define SPI_TXCRC_AUTOCRCINS_NOTINS                                 0x00000000U

// Field:  [15:0] DATA
//
// CRC value
#define SPI_TXCRC_DATA_W                                                    16U
#define SPI_TXCRC_DATA_M                                            0x0000FFFFU
#define SPI_TXCRC_DATA_S                                                     0U

//*****************************************************************************
//
// Register: SPI_O_TXFHDR32
//
//*****************************************************************************
// Field:  [31:0] DATA
//
// This field can be used to write four bytes of header data into the TXFIFO
#define SPI_TXFHDR32_DATA_W                                                 32U
#define SPI_TXFHDR32_DATA_M                                         0xFFFFFFFFU
#define SPI_TXFHDR32_DATA_S                                                  0U

//*****************************************************************************
//
// Register: SPI_O_TXFHDR24
//
//*****************************************************************************
// Field:  [31:0] DATA
//
// This field can be used to write three bytes of header data into the TXFIFO.
#define SPI_TXFHDR24_DATA_W                                                 32U
#define SPI_TXFHDR24_DATA_M                                         0xFFFFFFFFU
#define SPI_TXFHDR24_DATA_S                                                  0U

//*****************************************************************************
//
// Register: SPI_O_TXFHDR16
//
//*****************************************************************************
// Field:  [31:0] DATA
//
// This field can be used to write two bytes of header data into the TXFIFO.
#define SPI_TXFHDR16_DATA_W                                                 32U
#define SPI_TXFHDR16_DATA_M                                         0xFFFFFFFFU
#define SPI_TXFHDR16_DATA_S                                                  0U

//*****************************************************************************
//
// Register: SPI_O_TXFHDR8
//
//*****************************************************************************
// Field:  [31:0] DATA
//
// This field can be used to write one byte of header data into the TXFIFO.
#define SPI_TXFHDR8_DATA_W                                                  32U
#define SPI_TXFHDR8_DATA_M                                          0xFFFFFFFFU
#define SPI_TXFHDR8_DATA_S                                                   0U

//*****************************************************************************
//
// Register: SPI_O_TXFHDRC
//
//*****************************************************************************
// Field:     [3] CSGATE
//
// Chip Select Gating control register. If this bit is set, header update
// register writes are blocked when chip select (CS) is active low, and HDRIGN
// bit is set.
// This bit resets to 0.
// ENUMs:
// BLK                      Header update register writes are blocked when CS
//                          is active (low)
// UNBLK                    The first header update register write is not
//                          blocked based on CS active status (low).
//                          If no header update
//                          occurred when CS was high (inactive), the first
//                          header update is allowed when CS is low
//                          (active), and the HDRCMT bit is set. The use
//                          case is for the external controller to ensure
//                          that the SCLK is not driven during this header
//                          update.
//                          If the header is already
//                          updated when CS is high and inactive, HDRCMT is
//                          set immediately when CS drops to active low
//                          state, and header writes when CS is low are
//                          ignored even if this UNBLK bit is set.
#define SPI_TXFHDRC_CSGATE                                          0x00000008U
#define SPI_TXFHDRC_CSGATE_M                                        0x00000008U
#define SPI_TXFHDRC_CSGATE_S                                                 3U
#define SPI_TXFHDRC_CSGATE_BLK                                      0x00000008U
#define SPI_TXFHDRC_CSGATE_UNBLK                                    0x00000000U

// Field:     [2] HDRCMT
//
// Header Committed field. This bit is set when the HDREN bit is set and CS is
// sampled low. This bit remains 0 otherwise. When set, this bit can be written
// to a value of 0 to clear.
// ENUMs:
// SET                      Header update is committed
// CLR                      Header update is not committed
#define SPI_TXFHDRC_HDRCMT                                          0x00000004U
#define SPI_TXFHDRC_HDRCMT_M                                        0x00000004U
#define SPI_TXFHDRC_HDRCMT_S                                                 2U
#define SPI_TXFHDRC_HDRCMT_SET                                      0x00000004U
#define SPI_TXFHDRC_HDRCMT_CLR                                      0x00000000U

// Field:     [1] HDRIGN
//
// Header Ignored field. When CSGATE is set to BLK, this bit is set when the
// last Header update register TXFHDRn is written when CS is low or HDRCMT is
// already set. When CSGATE is set to UNBLK, this bit is set only when the
// header update register is written when HDRCMT is already set. This bit
// remains 0 otherwise. When set, this bit can be written to a value of 0 to
// clear.
// ENUMs:
// SET                      Header update is ignored
// CLR                      Header update is not ignored
#define SPI_TXFHDRC_HDRIGN                                          0x00000002U
#define SPI_TXFHDRC_HDRIGN_M                                        0x00000002U
#define SPI_TXFHDRC_HDRIGN_S                                                 1U
#define SPI_TXFHDRC_HDRIGN_SET                                      0x00000002U
#define SPI_TXFHDRC_HDRIGN_CLR                                      0x00000000U

// Field:     [0] HDREN
//
// Header enable field. When CSGATE is set to BLK, this bit has to be set by
// software to enable atomic header feature. When CSGATE is set to UNBLK, this
// field is set automatically whenever a write to header update registers
// TXFHDRn occurs.
// ENUMs:
// EN                       Atomic header update feature enable
// DIS                      Atomic header update feature disable
#define SPI_TXFHDRC_HDREN                                           0x00000001U
#define SPI_TXFHDRC_HDREN_M                                         0x00000001U
#define SPI_TXFHDRC_HDREN_S                                                  0U
#define SPI_TXFHDRC_HDREN_EN                                        0x00000001U
#define SPI_TXFHDRC_HDREN_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: SPI_O_RXDATA
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// Received Data. When read, the entry in the receive FIFO, pointed to by the
// current FIFO read pointer is accessed. As data values are read by the
// receive logic from the incoming data frame, they are placed into the entry
// in the receive FIFO, pointed to by the current RX FIFO write pointer.
// Received data less than 16 bits is automatically right-justified in the
// receive buffer.
#define SPI_RXDATA_DATA_W                                                   16U
#define SPI_RXDATA_DATA_M                                           0x0000FFFFU
#define SPI_RXDATA_DATA_S                                                    0U

//*****************************************************************************
//
// Register: SPI_O_TXDATA
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// Transmit Data. When read, the last entry in the transmit FIFO, pointed to by
// the current FIFO write pointer is accessed.
// When written, the entry in the TX FIFO pointed to by the write pointer, is
// written to. Data values are read from the transmit FIFO by the transmit
// logic. It is loaded into the transmit serial shifter, then serially shifted
// out onto the output pin at the programmed bit rate.
// When a data size of less than 16 bits is selected, the user must
// right-justify data written to the transmit FIFO. The transmit logic ignores
// the unused bits.
#define SPI_TXDATA_DATA_W                                                   16U
#define SPI_TXDATA_DATA_M                                           0x0000FFFFU
#define SPI_TXDATA_DATA_S                                                    0U

//*****************************************************************************
//
// Register: SPI_O_STA
//
//*****************************************************************************
// Field:  [13:8] TXFIFOLVL
//
// Indicates how many locations of TXFIFO are currently filled with data
#define SPI_STA_TXFIFOLVL_W                                                  6U
#define SPI_STA_TXFIFOLVL_M                                         0x00003F00U
#define SPI_STA_TXFIFOLVL_S                                                  8U

// Field:     [6] TXDONE
//
// Transmit done. Indicates whether the last bit has left the Shift register
// after a transmission
// ENUMs:
// TX_DONE                  Last bit has been shifted out, and the
//                          transmission is done
// TX_ONGOING               Last bit has not yet left the Shift register, and
//                          the transmission is ongoing.
#define SPI_STA_TXDONE                                              0x00000040U
#define SPI_STA_TXDONE_M                                            0x00000040U
#define SPI_STA_TXDONE_S                                                     6U
#define SPI_STA_TXDONE_TX_DONE                                      0x00000040U
#define SPI_STA_TXDONE_TX_ONGOING                                   0x00000000U

// Field:     [5] CSD
//
// Detection of CS deassertion in the middle of a data frame transmission
// results in this error being set. This feature is only available in the
// peripheral mode.
// ENUMs:
// ERR                      An error is generated when CS posedge
//                          (deassertion) is detected before the entire
//                          data frame is transmitted.
// NOERR                    No CS posedge is detected before the entire data
//                          frame has been transmitted.
#define SPI_STA_CSD                                                 0x00000020U
#define SPI_STA_CSD_M                                               0x00000020U
#define SPI_STA_CSD_S                                                        5U
#define SPI_STA_CSD_ERR                                             0x00000020U
#define SPI_STA_CSD_NOERR                                           0x00000000U

// Field:     [4] BUSY
//
// SPI Busy status
// ENUMs:
// ACTIVE                   SPI is currently transmitting and/or receiving
//                          data, or transmit FIFO is not empty.
// IDLE                     SPI is in idle mode.
#define SPI_STA_BUSY                                                0x00000010U
#define SPI_STA_BUSY_M                                              0x00000010U
#define SPI_STA_BUSY_S                                                       4U
#define SPI_STA_BUSY_ACTIVE                                         0x00000010U
#define SPI_STA_BUSY_IDLE                                           0x00000000U

// Field:     [3] RNF
//
// Receive FIFO not full status.
// ENUMs:
// NOT_FULL                 Receive FIFO is not full.
// FULL                     Receive FIFO is full.
#define SPI_STA_RNF                                                 0x00000008U
#define SPI_STA_RNF_M                                               0x00000008U
#define SPI_STA_RNF_S                                                        3U
#define SPI_STA_RNF_NOT_FULL                                        0x00000008U
#define SPI_STA_RNF_FULL                                            0x00000000U

// Field:     [2] RFE
//
// Receive FIFO empty status.
// ENUMs:
// EMPTY                    Receive FIFO is empty.
// NOT_EMPTY                Receive FIFO is not empty.
#define SPI_STA_RFE                                                 0x00000004U
#define SPI_STA_RFE_M                                               0x00000004U
#define SPI_STA_RFE_S                                                        2U
#define SPI_STA_RFE_EMPTY                                           0x00000004U
#define SPI_STA_RFE_NOT_EMPTY                                       0x00000000U

// Field:     [1] TNF
//
// Transmit FIFO not full status.
// ENUMs:
// NOT_FULL                 Transmit FIFO is not full.
// FULL                     Transmit FIFO is full.
#define SPI_STA_TNF                                                 0x00000002U
#define SPI_STA_TNF_M                                               0x00000002U
#define SPI_STA_TNF_S                                                        1U
#define SPI_STA_TNF_NOT_FULL                                        0x00000002U
#define SPI_STA_TNF_FULL                                            0x00000000U

// Field:     [0] TFE
//
// Transmit FIFO empty status.
// ENUMs:
// EMPTY                    Transmit FIFO is empty.
// NOT_EMPTY                Transmit FIFO is not empty.
#define SPI_STA_TFE                                                 0x00000001U
#define SPI_STA_TFE_M                                               0x00000001U
#define SPI_STA_TFE_S                                                        0U
#define SPI_STA_TFE_EMPTY                                           0x00000001U
#define SPI_STA_TFE_NOT_EMPTY                                       0x00000000U


#endif // __SPI__
