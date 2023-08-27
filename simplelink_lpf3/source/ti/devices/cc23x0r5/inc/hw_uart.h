/******************************************************************************
*  Filename:       hw_uart_h
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

#ifndef __HW_UART_H__
#define __HW_UART_H__

//*****************************************************************************
//
// This section defines the register offsets of
// UART component
//
//*****************************************************************************
// Data
#define UART_O_DR                                                   0x00000000U

// Status
#define UART_O_RSR_ECR                                              0x00000004U

// Flag
#define UART_O_FR                                                   0x00000018U

// IrDA Low-Power Counter Register
#define UART_O_UARTILPR                                             0x00000020U

// Integer Baud-Rate Divisor
#define UART_O_IBRD                                                 0x00000024U

// Fractional Baud-Rate Divisor
#define UART_O_FBRD                                                 0x00000028U

// Line Control
#define UART_O_LCRH                                                 0x0000002CU

// Control
#define UART_O_CTL                                                  0x00000030U

// Interrupt FIFO Level Select
#define UART_O_IFLS                                                 0x00000034U

// Interrupt Mask Set/Clear
#define UART_O_IMSC                                                 0x00000038U

// Raw Interrupt Status
#define UART_O_RIS                                                  0x0000003CU

// Masked Interrupt Status
#define UART_O_MIS                                                  0x00000040U

// Interrupt Clear
#define UART_O_ICR                                                  0x00000044U

// DMA Control
#define UART_O_DMACTL                                               0x00000048U

//*****************************************************************************
//
// Register: UART_O_DR
//
//*****************************************************************************
// Field:    [11] OE
//
// UART Overrun Error:
// This bit is set to 1 if data is received and the receive FIFO is already
// full. The FIFO contents remain valid because no more data is written when
// the FIFO is full, only the contents of the shift register are overwritten.
// This is cleared to 0 once there is an empty space in the FIFO and a new
// character can be written to it.
#define UART_DR_OE                                                  0x00000800U
#define UART_DR_OE_M                                                0x00000800U
#define UART_DR_OE_S                                                        11U

// Field:    [10] BE
//
// UART Break Error:
// This bit is set to 1 if a break condition was detected, indicating that the
// received data input (UARTRXD input pin) was held LOW for longer than a
// full-word transmission time (defined as start, data, parity and stop bits).
// In FIFO mode, this error is associated with the character at the top of the
// FIFO (i.e., the oldest received data character since last read). When a
// break occurs, a 0 character is loaded into the FIFO. The next character is
// enabled after the receive data input (UARTRXD input pin) goes to a 1
// (marking state), and the next valid start bit is received.
#define UART_DR_BE                                                  0x00000400U
#define UART_DR_BE_M                                                0x00000400U
#define UART_DR_BE_S                                                        10U

// Field:     [9] PE
//
// UART Parity Error:
// When set to 1, it indicates that the parity of the received data character
// does not match the parity that the LCRH.EPS and LCRH.SPS select.
// In FIFO mode, this error is associated with the character at the top of the
// FIFO (i.e., the oldest received data character since last read).
#define UART_DR_PE                                                  0x00000200U
#define UART_DR_PE_M                                                0x00000200U
#define UART_DR_PE_S                                                         9U

// Field:     [8] FE
//
// UART Framing Error:
// When set to 1, it indicates that the received character did not have a valid
// stop bit (a valid stop bit is 1).
// In FIFO mode, this error is associated with the character at the top of the
// FIFO (i.e., the oldest received data character since last read).
#define UART_DR_FE                                                  0x00000100U
#define UART_DR_FE_M                                                0x00000100U
#define UART_DR_FE_S                                                         8U

// Field:   [7:0] DATA
//
// Data transmitted or received:
// On writes, the transmit data character is pushed into the FIFO.
// On reads, the oldest received data character since the last read is
// returned.
#define UART_DR_DATA_W                                                       8U
#define UART_DR_DATA_M                                              0x000000FFU
#define UART_DR_DATA_S                                                       0U

//*****************************************************************************
//
// Register: UART_O_RSR_ECR
//
//*****************************************************************************
// Field:     [3] OE
//
// UART Overrun Error:
// This bit is set to 1 if data is received and the receive FIFO is already
// full. The FIFO contents remain valid because no more data is written when
// the FIFO is full, only the contents of the shift register are overwritten.
// This is cleared to 0 once there is an empty space in the FIFO and a new
// character can be written to it.
// ENUMs:
// CLEAR_ERROR_1            Clears error flag if error is set. Write value is
//                          not important.
// ERROR_NOTSET             Error flag is not set
#define UART_RSR_ECR_OE                                             0x00000008U
#define UART_RSR_ECR_OE_M                                           0x00000008U
#define UART_RSR_ECR_OE_S                                                    3U
#define UART_RSR_ECR_OE_CLEAR_ERROR_1                               0x00000008U
#define UART_RSR_ECR_OE_ERROR_NOTSET                                0x00000000U

// Field:     [2] BE
//
// UART Break Error:
// This bit is set to 1 if a break condition was detected, indicating that the
// received data input (UARTRXD input pin) was held LOW for longer than a
// full-word transmission time (defined as start, data, parity and stop bits).
// When a break occurs, a 0 character is loaded into the FIFO. The next
// character is enabled after the receive data input (UARTRXD input pin) goes
// to a 1 (marking state), and the next valid start bit is received.
// ENUMs:
// CLEAR_ERROR_1            Clears error flag if error is set. Write value is
//                          not important.
// ERROR_NOTSET             Error flag is not set
#define UART_RSR_ECR_BE                                             0x00000004U
#define UART_RSR_ECR_BE_M                                           0x00000004U
#define UART_RSR_ECR_BE_S                                                    2U
#define UART_RSR_ECR_BE_CLEAR_ERROR_1                               0x00000004U
#define UART_RSR_ECR_BE_ERROR_NOTSET                                0x00000000U

// Field:     [1] PE
//
// UART Parity Error:
// When set to 1, it indicates that the parity of the received data character
// does not match the parity that the LCRH.EPS and LCRH.SPS select.
// ENUMs:
// CLEAR_ERROR_1            Clears error flag if error is set. Write value is
//                          not important.
// ERROR_NOTSET             Error flag is not set
#define UART_RSR_ECR_PE                                             0x00000002U
#define UART_RSR_ECR_PE_M                                           0x00000002U
#define UART_RSR_ECR_PE_S                                                    1U
#define UART_RSR_ECR_PE_CLEAR_ERROR_1                               0x00000002U
#define UART_RSR_ECR_PE_ERROR_NOTSET                                0x00000000U

// Field:     [0] FE
//
// UART Framing Error:
// When set to 1, it indicates that the received character did not have a valid
// stop bit (a valid stop bit is 1).
// ENUMs:
// CLEAR_ERROR_1            Clears error flag if error is set. Write value is
//                          not important.
// ERROR_NOTSET             Error flag is not set
#define UART_RSR_ECR_FE                                             0x00000001U
#define UART_RSR_ECR_FE_M                                           0x00000001U
#define UART_RSR_ECR_FE_S                                                    0U
#define UART_RSR_ECR_FE_CLEAR_ERROR_1                               0x00000001U
#define UART_RSR_ECR_FE_ERROR_NOTSET                                0x00000000U

//*****************************************************************************
//
// Register: UART_O_FR
//
//*****************************************************************************
// Field:     [7] TXFE
//
// UART Transmit FIFO Empty:
// The meaning of this bit depends on the state of LCRH.FEN .
//   - If the FIFO is disabled, this bit is set when the transmit holding
// register is empty.
//   - If the FIFO is enabled, this bit is set when the transmit FIFO is empty.
// This bit does not indicate if there is data in the transmit shift register.
#define UART_FR_TXFE                                                0x00000080U
#define UART_FR_TXFE_M                                              0x00000080U
#define UART_FR_TXFE_S                                                       7U

// Field:     [6] RXFF
//
// UART Receive FIFO Full:
// The meaning of this bit depends on the state of LCRH.FEN.
//   - If the FIFO is disabled, this bit is set when the receive holding
// register is full.
//   - If the FIFO is enabled, this bit is set when the receive FIFO is full.
#define UART_FR_RXFF                                                0x00000040U
#define UART_FR_RXFF_M                                              0x00000040U
#define UART_FR_RXFF_S                                                       6U

// Field:     [5] TXFF
//
// UART Transmit FIFO Full:
// Transmit FIFO full. The meaning of this bit depends on the state of
// LCRH.FEN.
//   - If the FIFO is disabled, this bit is set when the transmit holding
// register is full.
//   - If the FIFO is enabled, this bit is set when the transmit FIFO is full.
#define UART_FR_TXFF                                                0x00000020U
#define UART_FR_TXFF_M                                              0x00000020U
#define UART_FR_TXFF_S                                                       5U

// Field:     [4] RXFE
//
// UART Receive FIFO Empty:
// Receive FIFO empty. The meaning of this bit depends on the state of
// LCRH.FEN.
//   - If the FIFO is disabled, this bit is set when the receive holding
// register is empty.
//   - If the FIFO is enabled, this bit is set when the receive FIFO is empty.
#define UART_FR_RXFE                                                0x00000010U
#define UART_FR_RXFE_M                                              0x00000010U
#define UART_FR_RXFE_S                                                       4U

// Field:     [3] BUSY
//
// UART Busy:
// If this bit is set to 1, the UART is busy transmitting data. This bit
// remains set until the complete byte, including all the stop bits, has been
// sent from the shift register.
// This bit is set as soon as the transmit FIFO becomes non-empty, regardless
// of whether the UART is enabled or not.
#define UART_FR_BUSY                                                0x00000008U
#define UART_FR_BUSY_M                                              0x00000008U
#define UART_FR_BUSY_S                                                       3U

// Field:     [0] CTS
//
// Clear To Send:
// This bit is the complement of the active-low UART CTS input pin.
// That is, the bit is 1 when CTS input pin is LOW.
#define UART_FR_CTS                                                 0x00000001U
#define UART_FR_CTS_M                                               0x00000001U
#define UART_FR_CTS_S                                                        0U

//*****************************************************************************
//
// Register: UART_O_UARTILPR
//
//*****************************************************************************
// Field:   [7:0] ILPDVSR
//
// 8 bit low-power divisor value. In low-power IrDA mode the UART rejects
// random noise on the received serial data
// input by ignoring SIRIN pulses that are less than 3 periods of IrLPBaud16.
#define UART_UARTILPR_ILPDVSR_W                                              8U
#define UART_UARTILPR_ILPDVSR_M                                     0x000000FFU
#define UART_UARTILPR_ILPDVSR_S                                              0U

//*****************************************************************************
//
// Register: UART_O_IBRD
//
//*****************************************************************************
// Field:  [15:0] DIVINT
//
// The integer baud rate divisor:
// The baud rate divisor is calculated using the formula below:
// Baud rate divisor = (UART reference clock frequency) / (16 * Baud rate)
// Baud rate divisor must be minimum 1 and maximum 65535.
// That is, DIVINT=0 does not give a valid baud rate.
// Similarly, if DIVINT=0xFFFF, any non-zero values in FBRD.DIVFRAC will be
// illegal.
// Refer to Section 19.1.5 for an example calculation.
// A valid value must be written to this field before the UART can be used for
// RX or TX operations.
#define UART_IBRD_DIVINT_W                                                  16U
#define UART_IBRD_DIVINT_M                                          0x0000FFFFU
#define UART_IBRD_DIVINT_S                                                   0U

//*****************************************************************************
//
// Register: UART_O_FBRD
//
//*****************************************************************************
// Field:   [5:0] DIVFRAC
//
// Fractional Baud-Rate Divisor:
// The baud rate divisor is calculated using the formula below:
// Baud rate divisor = (UART reference clock frequency) / (16 * Baud rate)
// Baud rate divisor must be minimum 1 and maximum 65535.
// That is, IBRD.DIVINT=0 does not give a valid baud rate.
// Similarly, if IBRD.DIVINT=0xFFFF, any non-zero values in DIVFRAC will be
// illegal.
// Refer to Section 19.1.5 for an example calculation.
// A valid value must be written to this field before the UART can be used for
// RX or TX operations.
#define UART_FBRD_DIVFRAC_W                                                  6U
#define UART_FBRD_DIVFRAC_M                                         0x0000003FU
#define UART_FBRD_DIVFRAC_S                                                  0U

//*****************************************************************************
//
// Register: UART_O_LCRH
//
//*****************************************************************************
// Field:     [7] SPS
//
// UART Stick Parity Select:
//
// 0: Stick parity is disabled
// 1: The parity bit is transmitted and checked as invert of EPS field (i.e.
// the parity bit is transmitted and checked as 1 when EPS = 0).
//
// This bit has no effect when PEN disables parity checking and generation.
#define UART_LCRH_SPS                                               0x00000080U
#define UART_LCRH_SPS_M                                             0x00000080U
#define UART_LCRH_SPS_S                                                      7U

// Field:   [6:5] WLEN
//
// UART Word Length:
// These bits indicate the number of data bits transmitted or received in a
// frame.
// ENUMs:
// BITL8                    Word Length 8 bits
// BITL7                    Word Length 7 bits
// BITL6                    Word Length 6 bits
// BITL5                    Word Length 5 bits
#define UART_LCRH_WLEN_W                                                     2U
#define UART_LCRH_WLEN_M                                            0x00000060U
#define UART_LCRH_WLEN_S                                                     5U
#define UART_LCRH_WLEN_BITL8                                        0x00000060U
#define UART_LCRH_WLEN_BITL7                                        0x00000040U
#define UART_LCRH_WLEN_BITL6                                        0x00000020U
#define UART_LCRH_WLEN_BITL5                                        0x00000000U

// Field:     [4] FEN
//
// UART Enable FIFOs
// ENUMs:
// EN                       Transmit and receive FIFO buffers are enabled
//                          (FIFO mode)
// DIS                      FIFOs are disabled (character mode) that is, the
//                          FIFOs become 1-byte-deep holding registers.
#define UART_LCRH_FEN                                               0x00000010U
#define UART_LCRH_FEN_M                                             0x00000010U
#define UART_LCRH_FEN_S                                                      4U
#define UART_LCRH_FEN_EN                                            0x00000010U
#define UART_LCRH_FEN_DIS                                           0x00000000U

// Field:     [3] STP2
//
// UART Two Stop Bits Select:
// If this bit is set to 1, two stop bits are transmitted at the end of the
// frame. The receive logic does not check for two stop bits being received.
#define UART_LCRH_STP2                                              0x00000008U
#define UART_LCRH_STP2_M                                            0x00000008U
#define UART_LCRH_STP2_S                                                     3U

// Field:     [2] EPS
//
// UART Even Parity Select
// ENUMs:
// EVEN                     Even parity: The UART generates or checks for an
//                          even number of 1s in the data and parity bits.
// ODD                      Odd parity: The UART generates or checks for an
//                          odd number of 1s in the data and parity bits.
#define UART_LCRH_EPS                                               0x00000004U
#define UART_LCRH_EPS_M                                             0x00000004U
#define UART_LCRH_EPS_S                                                      2U
#define UART_LCRH_EPS_EVEN                                          0x00000004U
#define UART_LCRH_EPS_ODD                                           0x00000000U

// Field:     [1] PEN
//
// UART Parity Enable
// This bit controls generation and checking of parity bit.
// ENUMs:
// EN                       Parity checking and generation is enabled.
// DIS                      Parity is disabled and no parity bit is added to
//                          the data frame
#define UART_LCRH_PEN                                               0x00000002U
#define UART_LCRH_PEN_M                                             0x00000002U
#define UART_LCRH_PEN_S                                                      1U
#define UART_LCRH_PEN_EN                                            0x00000002U
#define UART_LCRH_PEN_DIS                                           0x00000000U

// Field:     [0] BRK
//
// UART Send Break
// If this bit is set to 1, a low-level is continually output on the UARTTXD
// output pin, after completing transmission of the current character. For the
// proper execution of the break command, the
// software must set this bit for at least two complete frames. For normal use,
// this bit must be cleared to 0.
#define UART_LCRH_BRK                                               0x00000001U
#define UART_LCRH_BRK_M                                             0x00000001U
#define UART_LCRH_BRK_S                                                      0U

//*****************************************************************************
//
// Register: UART_O_CTL
//
//*****************************************************************************
// Field:    [15] CTSEN
//
// CTS hardware flow control enable
// ENUMs:
// EN                       CTS hardware flow control enabled
// DIS                      CTS hardware flow control disabled
#define UART_CTL_CTSEN                                              0x00008000U
#define UART_CTL_CTSEN_M                                            0x00008000U
#define UART_CTL_CTSEN_S                                                    15U
#define UART_CTL_CTSEN_EN                                           0x00008000U
#define UART_CTL_CTSEN_DIS                                          0x00000000U

// Field:    [14] RTSEN
//
// RTS hardware flow control enable
// ENUMs:
// EN                       RTS hardware flow control enabled
// DIS                      RTS hardware flow control disabled
#define UART_CTL_RTSEN                                              0x00004000U
#define UART_CTL_RTSEN_M                                            0x00004000U
#define UART_CTL_RTSEN_S                                                    14U
#define UART_CTL_RTSEN_EN                                           0x00004000U
#define UART_CTL_RTSEN_DIS                                          0x00000000U

// Field:    [11] RTS
//
// Request to Send
// This bit is the complement of the active-low UART RTS output. That is, when
// the bit is programmed to a 1 then RTS output on the pins is LOW.
#define UART_CTL_RTS                                                0x00000800U
#define UART_CTL_RTS_M                                              0x00000800U
#define UART_CTL_RTS_S                                                      11U

// Field:     [9] RXE
//
// UART Receive Enable
// If the UART is disabled in the middle of reception, it completes the current
// character before stopping.
// ENUMs:
// EN                       UART Receive enabled
// DIS                      UART Receive disabled
#define UART_CTL_RXE                                                0x00000200U
#define UART_CTL_RXE_M                                              0x00000200U
#define UART_CTL_RXE_S                                                       9U
#define UART_CTL_RXE_EN                                             0x00000200U
#define UART_CTL_RXE_DIS                                            0x00000000U

// Field:     [8] TXE
//
// UART Transmit Enable
// If the UART is disabled in the middle of transmission, it completes the
// current character before stopping.
// ENUMs:
// EN                       UART Transmit enabled
// DIS                      UART Transmit disabled
#define UART_CTL_TXE                                                0x00000100U
#define UART_CTL_TXE_M                                              0x00000100U
#define UART_CTL_TXE_S                                                       8U
#define UART_CTL_TXE_EN                                             0x00000100U
#define UART_CTL_TXE_DIS                                            0x00000000U

// Field:     [7] LBE
//
// UART Loop Back Enable
// Enabling the loop-back mode connects the UARTTXD output from the UART to
// UARTRXD input of the UART.
// ENUMs:
// EN                       Loop Back enabled
// DIS                      Loop Back disabled
#define UART_CTL_LBE                                                0x00000080U
#define UART_CTL_LBE_M                                              0x00000080U
#define UART_CTL_LBE_S                                                       7U
#define UART_CTL_LBE_EN                                             0x00000080U
#define UART_CTL_LBE_DIS                                            0x00000000U

// Field:     [6] FCEN
//
// UART FIFO Concatenation Enable
// Enabling the FIFO concatenation in TX mode resulting in 16 TX buffers.
// ENUMs:
// EN                       UART FIFO Concatenation  enabled
// DIS                      UART FIFO Concatenation  disabled
#define UART_CTL_FCEN                                               0x00000040U
#define UART_CTL_FCEN_M                                             0x00000040U
#define UART_CTL_FCEN_S                                                      6U
#define UART_CTL_FCEN_EN                                            0x00000040U
#define UART_CTL_FCEN_DIS                                           0x00000000U

// Field:     [2] SIRLP
//
// SIR low power IrDA mode
// This bit selects the IrDA encoding mode
// ENUMs:
// EN                       Low-level bits are transmitted with a pulse width
//                          of 3 times the period of IrLPBaud16(which has a
//                          frequency of (UARTCLK
//                          frequency)/UARTILP.ILPDVSR), regardless of the
//                          selected bit rate.
//                          In low-power IrDA mode
//                          the UART rejects random noise on the received
//                          serial data
//                          input by ignoring SIRIN
//                          pulses that are less than 3 periods of
//                          IrLPBaud16.
// DIS                      Low-level bits are transmitted as active high with
//                          a 3/16th period width,
#define UART_CTL_SIRLP                                              0x00000004U
#define UART_CTL_SIRLP_M                                            0x00000004U
#define UART_CTL_SIRLP_S                                                     2U
#define UART_CTL_SIRLP_EN                                           0x00000004U
#define UART_CTL_SIRLP_DIS                                          0x00000000U

// Field:     [1] SIREN
//
// SIR Enable
// This bit has no effect if UARTEN bit disables the UART.
// ENUMs:
// EN                       IrDA SIR ENDEC is enabled. Data is transmitted and
//                          received via nSIROUT and SIRIN.
// DIS                      IrDA SIR ENDEC is disabled
#define UART_CTL_SIREN                                              0x00000002U
#define UART_CTL_SIREN_M                                            0x00000002U
#define UART_CTL_SIREN_S                                                     1U
#define UART_CTL_SIREN_EN                                           0x00000002U
#define UART_CTL_SIREN_DIS                                          0x00000000U

// Field:     [0] UARTEN
//
// UART Enable
// ENUMs:
// EN                       UART enabled
// DIS                      UART disabled
#define UART_CTL_UARTEN                                             0x00000001U
#define UART_CTL_UARTEN_M                                           0x00000001U
#define UART_CTL_UARTEN_S                                                    0U
#define UART_CTL_UARTEN_EN                                          0x00000001U
#define UART_CTL_UARTEN_DIS                                         0x00000000U

//*****************************************************************************
//
// Register: UART_O_IFLS
//
//*****************************************************************************
// Field:   [5:3] RXSEL
//
// Receive interrupt FIFO level select:
// This field sets the trigger points for the receive interrupt. Values
// 0b101-0b111 are reserved.
// ENUMs:
// THREEQU                  Receive FIFO becomes >= 3/4 full
// HALF                     Receive FIFO becomes >= 1/2 full
// QUARTER                  Receive FIFO becomes >= 1/4 full
#define UART_IFLS_RXSEL_W                                                    3U
#define UART_IFLS_RXSEL_M                                           0x00000038U
#define UART_IFLS_RXSEL_S                                                    3U
#define UART_IFLS_RXSEL_THREEQU                                     0x00000018U
#define UART_IFLS_RXSEL_HALF                                        0x00000010U
#define UART_IFLS_RXSEL_QUARTER                                     0x00000008U

// Field:   [2:0] TXSEL
//
// Transmit interrupt FIFO level select:
// This field sets the trigger points for the transmit interrupt. Values
// 0b101-0b111 are reserved.
// ENUMs:
// THREEQU                  Transmit FIFO becomes <= 3/4 full
// HALF                     Transmit FIFO becomes <= 1/2 full
// QUARTER                  Transmit FIFO becomes <= 1/4 full
#define UART_IFLS_TXSEL_W                                                    3U
#define UART_IFLS_TXSEL_M                                           0x00000007U
#define UART_IFLS_TXSEL_S                                                    0U
#define UART_IFLS_TXSEL_THREEQU                                     0x00000003U
#define UART_IFLS_TXSEL_HALF                                        0x00000002U
#define UART_IFLS_TXSEL_QUARTER                                     0x00000001U

//*****************************************************************************
//
// Register: UART_O_IMSC
//
//*****************************************************************************
// Field:    [13] RXDMADONE
//
// RX DMA done interrupt mask. A read returns the current mask for UART's
// RXDMADONE interrupt. On a write of 1, the mask of the RXDMADONE interrupt is
// set which means the interrupt state will be reflected in MIS.RXDMADONE. A
// write of 0 clears the mask which means MIS.RXDMADONE will not reflect the
// interrupt.
#define UART_IMSC_RXDMADONE                                         0x00002000U
#define UART_IMSC_RXDMADONE_M                                       0x00002000U
#define UART_IMSC_RXDMADONE_S                                               13U

// Field:    [12] TXDMADONE
//
// TX DMA done interrupt mask. A read returns the current mask for UART's
// TXDMADONE interrupt. On a write of 1, the mask of the TXDMADONE interrupt is
// set which means the interrupt state will be reflected in MIS.TXDMADONE. A
// write of 0 clears the mask which means MIS.TXDMADONE will not reflect the
// interrupt.
#define UART_IMSC_TXDMADONE                                         0x00001000U
#define UART_IMSC_TXDMADONE_M                                       0x00001000U
#define UART_IMSC_TXDMADONE_S                                               12U

// Field:    [11] EOT
//
// End of Transmission interrupt mask. A read returns the current mask for
// UART's EoT interrupt. On a write of 1, the mask of the EoT interrupt is set
// which means the interrupt state will be reflected in MIS.EOT. A write of 0
// clears the mask which means MIS.EOT will not reflect the interrupt.
#define UART_IMSC_EOT                                               0x00000800U
#define UART_IMSC_EOT_M                                             0x00000800U
#define UART_IMSC_EOT_S                                                     11U

// Field:    [10] OE
//
// Overrun error interrupt mask. A read returns the current mask for UART's
// overrun error interrupt. On a write of 1, the mask of the overrun error
// interrupt is set which means the interrupt state will be reflected in
// MIS.OE. A write of 0 clears the mask which means MIS.OE will not reflect the
// interrupt.
#define UART_IMSC_OE                                                0x00000400U
#define UART_IMSC_OE_M                                              0x00000400U
#define UART_IMSC_OE_S                                                      10U

// Field:     [9] BE
//
// Break error interrupt mask. A read returns the current mask for UART's break
// error interrupt. On a write of 1, the mask of the overrun error interrupt is
// set which means the interrupt state will be reflected in MIS.BE. A write of
// 0 clears the mask which means MIS.BE will not reflect the interrupt.
#define UART_IMSC_BE                                                0x00000200U
#define UART_IMSC_BE_M                                              0x00000200U
#define UART_IMSC_BE_S                                                       9U

// Field:     [8] PE
//
// Parity error interrupt mask. A read returns the current mask for UART's
// parity error interrupt. On a write of 1, the mask of the overrun error
// interrupt is set which means the interrupt state will be reflected in
// MIS.PE. A write of 0 clears the mask which means MIS.PE will not reflect the
// interrupt.
#define UART_IMSC_PE                                                0x00000100U
#define UART_IMSC_PE_M                                              0x00000100U
#define UART_IMSC_PE_S                                                       8U

// Field:     [7] FE
//
// Framing error interrupt mask. A read returns the current mask for UART's
// framing error interrupt. On a write of 1, the mask of the overrun error
// interrupt is set which means the interrupt state will be reflected in
// MIS.FE. A write of 0 clears the mask which means MIS.FE will not reflect the
// interrupt.
#define UART_IMSC_FE                                                0x00000080U
#define UART_IMSC_FE_M                                              0x00000080U
#define UART_IMSC_FE_S                                                       7U

// Field:     [6] RT
//
// Receive timeout interrupt mask. A read returns the current mask for UART's
// receive timeout interrupt. On a write of 1, the mask of the overrun error
// interrupt is set which means the interrupt state will be reflected in
// MIS.RT. A write of 0 clears the mask which means this bitfield will not
// reflect the interrupt.
// The raw interrupt for receive timeout RIS.RT cannot be set unless the mask
// is set (RT = 1). This is because the mask acts as an enable for power
// saving. That is, the same status can be read from MIS.RT and RIS.RT.
#define UART_IMSC_RT                                                0x00000040U
#define UART_IMSC_RT_M                                              0x00000040U
#define UART_IMSC_RT_S                                                       6U

// Field:     [5] TX
//
// Transmit interrupt mask. A read returns the current mask for UART's transmit
// interrupt. On a write of 1, the mask of the overrun error interrupt is set
// which means the interrupt state will be reflected in MIS.TX. A write of 0
// clears the mask which means MIS.TX will not reflect the interrupt.
#define UART_IMSC_TX                                                0x00000020U
#define UART_IMSC_TX_M                                              0x00000020U
#define UART_IMSC_TX_S                                                       5U

// Field:     [4] RX
//
// Receive interrupt mask. A read returns the current mask for UART's receive
// interrupt. On a write of 1, the mask of the overrun error interrupt is set
// which means the interrupt state will be reflected in MIS.RX. A write of 0
// clears the mask which means MIS.RX will not reflect the interrupt.
#define UART_IMSC_RX                                                0x00000010U
#define UART_IMSC_RX_M                                              0x00000010U
#define UART_IMSC_RX_S                                                       4U

// Field:     [1] CTSM
//
// Clear to Send (CTS) modem interrupt mask. A read returns the current mask
// for UART's clear to send interrupt. On a write of 1, the mask of the overrun
// error interrupt is set which means the interrupt state will be reflected in
// MIS.CTSM. A write of 0 clears the mask which means MIS.CTSM will not reflect
// the interrupt.
#define UART_IMSC_CTSM                                              0x00000002U
#define UART_IMSC_CTSM_M                                            0x00000002U
#define UART_IMSC_CTSM_S                                                     1U

//*****************************************************************************
//
// Register: UART_O_RIS
//
//*****************************************************************************
// Field:    [13] RXDMADONE
//
// RX DMA done interrupt status:
// This field returns the raw interrupt state of UART's RX DMA done interrupt.
// RX DMA done flag is set when you recieve RX DMA done status from dma module.
#define UART_RIS_RXDMADONE                                          0x00002000U
#define UART_RIS_RXDMADONE_M                                        0x00002000U
#define UART_RIS_RXDMADONE_S                                                13U

// Field:    [12] TXDMADONE
//
// TX DMA done interrupt status:
// This field returns the raw interrupt state of UART's TX DMA done interrupt.
// TX DMA done flag is set when you recieve TX DMA done status from dma module.
#define UART_RIS_TXDMADONE                                          0x00001000U
#define UART_RIS_TXDMADONE_M                                        0x00001000U
#define UART_RIS_TXDMADONE_S                                                12U

// Field:    [11] EOT
//
// End of Transmission interrupt status:
// This field returns the raw interrupt state of UART's end of transmission
// interrupt. End of transmission flag is set when all the Transmit data in the
// FIFO and on the TX Line is tranmitted.
#define UART_RIS_EOT                                                0x00000800U
#define UART_RIS_EOT_M                                              0x00000800U
#define UART_RIS_EOT_S                                                      11U

// Field:    [10] OE
//
// Overrun error interrupt status:
// This field returns the raw interrupt state of UART's overrun error
// interrupt. Overrun error occurs if data is received and the receive FIFO is
// full.
#define UART_RIS_OE                                                 0x00000400U
#define UART_RIS_OE_M                                               0x00000400U
#define UART_RIS_OE_S                                                       10U

// Field:     [9] BE
//
// Break error interrupt status:
// This field returns the raw interrupt state of UART's break error interrupt.
// Break error is set when a break condition is detected, indicating that the
// received data input (UARTRXD input pin) was held LOW for longer than a
// full-word transmission time (defined as start, data, parity and stop bits).
#define UART_RIS_BE                                                 0x00000200U
#define UART_RIS_BE_M                                               0x00000200U
#define UART_RIS_BE_S                                                        9U

// Field:     [8] PE
//
// Parity error interrupt status:
// This field returns the raw interrupt state of UART's parity error interrupt.
// Parity error is set if the parity of the received data character does not
// match the parity that the LCRH.EPS and LCRH.SPS select.
#define UART_RIS_PE                                                 0x00000100U
#define UART_RIS_PE_M                                               0x00000100U
#define UART_RIS_PE_S                                                        8U

// Field:     [7] FE
//
// Framing error interrupt status:
// This field returns the raw interrupt state of UART's framing error
// interrupt. Framing error is set if the received character does not have a
// valid stop bit (a valid stop bit is 1).
#define UART_RIS_FE                                                 0x00000080U
#define UART_RIS_FE_M                                               0x00000080U
#define UART_RIS_FE_S                                                        7U

// Field:     [6] RT
//
// Receive timeout interrupt status:
// This field returns the raw interrupt state of UART's receive timeout
// interrupt. The receive timeout interrupt is asserted when the receive FIFO
// is not empty, and no more data is received during a 32-bit period. The
// receive timeout interrupt is cleared either when the FIFO becomes empty
// through reading all the data, or when a 1 is written to ICR.RT.
// The raw interrupt for receive timeout cannot be set unless the mask is set
// (IMSC.RT = 1). This is because the mask acts as an enable for power saving.
// That is, the same status can be read from MIS.RT and RT.
#define UART_RIS_RT                                                 0x00000040U
#define UART_RIS_RT_M                                               0x00000040U
#define UART_RIS_RT_S                                                        6U

// Field:     [5] TX
//
// Transmit interrupt status:
// This field returns the raw interrupt state of UART's transmit interrupt.
// When FIFOs are enabled (LCRH.FEN = 1), the transmit interrupt is asserted if
// the number of bytes in transmit FIFO is equal to or lower than the
// programmed trigger level (IFLS.TXSEL). The transmit interrupt is cleared by
// writing data to the transmit FIFO until it becomes greater than the trigger
// level, or by clearing the interrupt through ICR.TX.
// When FIFOs are disabled (LCRH.FEN = 0), that is they have a depth of one
// location, the transmit interrupt is asserted if there is no data present in
// the transmitters single location. It is cleared by performing a single write
// to the transmit FIFO, or by clearing the interrupt through ICR.TX.
#define UART_RIS_TX                                                 0x00000020U
#define UART_RIS_TX_M                                               0x00000020U
#define UART_RIS_TX_S                                                        5U

// Field:     [4] RX
//
// Receive interrupt status:
// This field returns the raw interrupt state of UART's receive interrupt.
// When FIFOs are enabled (LCRH.FEN = 1), the receive interrupt is asserted if
// the receive FIFO reaches the programmed trigger
// level (IFLS.RXSEL). The receive interrupt is cleared by reading data from
// the receive FIFO until it becomes less than the trigger level, or by
// clearing the interrupt through ICR.RX.
// When FIFOs are disabled (LCRH.FEN = 0), that is they have a depth of one
// location, the receive interrupt is asserted if data is received
// thereby filling the location. The receive interrupt is cleared by performing
// a single read of the receive FIFO, or by clearing the interrupt through
// ICR.RX.
#define UART_RIS_RX                                                 0x00000010U
#define UART_RIS_RX_M                                               0x00000010U
#define UART_RIS_RX_S                                                        4U

// Field:     [1] CTSM
//
// Clear to Send (CTS) modem interrupt status:
// This field returns the raw interrupt state of UART's clear to send
// interrupt.
#define UART_RIS_CTSM                                               0x00000002U
#define UART_RIS_CTSM_M                                             0x00000002U
#define UART_RIS_CTSM_S                                                      1U

//*****************************************************************************
//
// Register: UART_O_MIS
//
//*****************************************************************************
// Field:    [13] RXDMADONE
//
// RX DMA done interrupt status:
// This field returns the masked interrupt state of the RX DMA done interrupt
// which is the bitiwse AND product of raw interrupt state RIS.RXDMADONE and
// the mask setting IMSC.RXDMADONE.
#define UART_MIS_RXDMADONE                                          0x00002000U
#define UART_MIS_RXDMADONE_M                                        0x00002000U
#define UART_MIS_RXDMADONE_S                                                13U

// Field:    [12] TXDMADONE
//
// TX DMA done interrupt status:
// This field returns the masked interrupt state of the TX DMA done interrupt
// which is the bitwise AND product of raw interrupt state RIS.TXDMADONE and
// the mask setting IMSC.TXDMADONE.
#define UART_MIS_TXDMADONE                                          0x00001000U
#define UART_MIS_TXDMADONE_M                                        0x00001000U
#define UART_MIS_TXDMADONE_S                                                12U

// Field:    [11] EOT
//
// End of Transmission interrupt status:
// This field returns the masked interrupt state of the End of transmission
// interrupt which is the bitwise AND product of raw interrupt state RIS.EOT
// and the mask setting IMSC.EOT.
#define UART_MIS_EOT                                                0x00000800U
#define UART_MIS_EOT_M                                              0x00000800U
#define UART_MIS_EOT_S                                                      11U

// Field:    [10] OE
//
// Overrun error masked interrupt status:
// This field returns the masked interrupt state of the overrun interrupt which
// is the bitwise AND product of raw interrupt state RIS.OE and the mask
// setting IMSC.OE.
#define UART_MIS_OE                                                 0x00000400U
#define UART_MIS_OE_M                                               0x00000400U
#define UART_MIS_OE_S                                                       10U

// Field:     [9] BE
//
// Break error masked interrupt status:
// This field returns the masked interrupt state of the break error interrupt
// which is the bitiwse AND product of raw interrupt state RIS.BE and the mask
// setting IMSC.BE.
#define UART_MIS_BE                                                 0x00000200U
#define UART_MIS_BE_M                                               0x00000200U
#define UART_MIS_BE_S                                                        9U

// Field:     [8] PE
//
// Parity error masked interrupt status:
// This field returns the masked interrupt state of the parity error interrupt
// which is the bitiwise AND product of raw interrupt state RIS.PE and the mask
// setting IMSC.PE.
#define UART_MIS_PE                                                 0x00000100U
#define UART_MIS_PE_M                                               0x00000100U
#define UART_MIS_PE_S                                                        8U

// Field:     [7] FE
//
// Framing error masked interrupt status: Returns the masked interrupt state of
// the framing error interrupt which is the bitiwse AND product of raw
// interrupt state RIS.FE and the mask setting IMSC.FE.
#define UART_MIS_FE                                                 0x00000080U
#define UART_MIS_FE_M                                               0x00000080U
#define UART_MIS_FE_S                                                        7U

// Field:     [6] RT
//
// Receive timeout masked interrupt status:
// Returns the masked interrupt state of the receive timeout interrupt.
// The raw interrupt for receive timeout cannot be set unless the mask is set
// (IMSC.RT = 1). This is because the mask acts as an enable for power saving.
// That is, the same status can be read from MIS.RT and RIS.RT.
#define UART_MIS_RT                                                 0x00000040U
#define UART_MIS_RT_M                                               0x00000040U
#define UART_MIS_RT_S                                                        6U

// Field:     [5] TX
//
// Transmit masked interrupt status:
// This field returns the masked interrupt state of the transmit interrupt
// which is the bitiwse AND product of raw interrupt state RIS.TX and the mask
// setting IMSC.TX.
#define UART_MIS_TX                                                 0x00000020U
#define UART_MIS_TX_M                                               0x00000020U
#define UART_MIS_TX_S                                                        5U

// Field:     [4] RX
//
// Receive masked interrupt status:
// This field returns the masked interrupt state of the receive interrupt
// which is the bitwise AND product of raw interrupt state RIS.RX and the mask
// setting IMSC.RX.
#define UART_MIS_RX                                                 0x00000010U
#define UART_MIS_RX_M                                               0x00000010U
#define UART_MIS_RX_S                                                        4U

// Field:     [1] CTSM
//
// Clear to Send (CTS) modem masked interrupt status:
// This field returns the masked interrupt state of the clear to send interrupt
// which is the bitwise AND product of raw interrupt state RIS.CTS and the mask
// setting IMSC.CTS.
#define UART_MIS_CTSM                                               0x00000002U
#define UART_MIS_CTSM_M                                             0x00000002U
#define UART_MIS_CTSM_S                                                      1U

//*****************************************************************************
//
// Register: UART_O_ICR
//
//*****************************************************************************
// Field:    [13] RXDMADONE
//
// RX DMA Done interrupt clear:
// Writing 1 to this field clears the RX DMA done interrupt (RIS.RXDMADONE).
// Writing 0 has no effect.
#define UART_ICR_RXDMADONE                                          0x00002000U
#define UART_ICR_RXDMADONE_M                                        0x00002000U
#define UART_ICR_RXDMADONE_S                                                13U

// Field:    [12] TXDMADONE
//
// TX DMA Done interrupt clear:
// Writing 1 to this field clears the TX DMA done interrupt (RIS.TXDMADONE).
// Writing 0 has no effect.
#define UART_ICR_TXDMADONE                                          0x00001000U
#define UART_ICR_TXDMADONE_M                                        0x00001000U
#define UART_ICR_TXDMADONE_S                                                12U

// Field:    [11] EOT
//
// End of Transmission interrupt clear:
// Writing 1 to this field clears the End of Transmission interrupt (RIS.EOT).
// Writing 0 has no effect.
#define UART_ICR_EOT                                                0x00000800U
#define UART_ICR_EOT_M                                              0x00000800U
#define UART_ICR_EOT_S                                                      11U

// Field:    [10] OE
//
// Overrun error interrupt clear:
// Writing 1 to this field clears the overrun error interrupt (RIS.OE). Writing
// 0 has no effect.
#define UART_ICR_OE                                                 0x00000400U
#define UART_ICR_OE_M                                               0x00000400U
#define UART_ICR_OE_S                                                       10U

// Field:     [9] BE
//
// Break error interrupt clear:
// Writing 1 to this field clears the break error interrupt (RIS.BE). Writing 0
// has no effect.
#define UART_ICR_BE                                                 0x00000200U
#define UART_ICR_BE_M                                               0x00000200U
#define UART_ICR_BE_S                                                        9U

// Field:     [8] PE
//
// Parity error interrupt clear:
// Writing 1 to this field clears the parity error interrupt (RIS.PE). Writing
// 0 has no effect.
#define UART_ICR_PE                                                 0x00000100U
#define UART_ICR_PE_M                                               0x00000100U
#define UART_ICR_PE_S                                                        8U

// Field:     [7] FE
//
// Framing error interrupt clear:
// Writing 1 to this field clears the framing error interrupt (RIS.FE). Writing
// 0 has no effect.
#define UART_ICR_FE                                                 0x00000080U
#define UART_ICR_FE_M                                               0x00000080U
#define UART_ICR_FE_S                                                        7U

// Field:     [6] RT
//
// Receive timeout interrupt clear:
// Writing 1 to this field clears the receive timeout interrupt (RIS.RT).
// Writing 0 has no effect.
#define UART_ICR_RT                                                 0x00000040U
#define UART_ICR_RT_M                                               0x00000040U
#define UART_ICR_RT_S                                                        6U

// Field:     [5] TX
//
// Transmit interrupt clear:
// Writing 1 to this field clears the transmit interrupt (RIS.TX). Writing 0
// has no effect.
#define UART_ICR_TX                                                 0x00000020U
#define UART_ICR_TX_M                                               0x00000020U
#define UART_ICR_TX_S                                                        5U

// Field:     [4] RX
//
// Receive interrupt clear:
// Writing 1 to this field clears the receive interrupt (RIS.RX). Writing 0 has
// no effect.
#define UART_ICR_RX                                                 0x00000010U
#define UART_ICR_RX_M                                               0x00000010U
#define UART_ICR_RX_S                                                        4U

// Field:     [1] CTSM
//
// Clear to Send (CTS) modem interrupt clear:
// Writing 1 to this field clears the clear to send interrupt (RIS.CTS).
// Writing 0 has no effect.
#define UART_ICR_CTSM                                               0x00000002U
#define UART_ICR_CTSM_M                                             0x00000002U
#define UART_ICR_CTSM_S                                                      1U

//*****************************************************************************
//
// Register: UART_O_DMACTL
//
//*****************************************************************************
// Field:     [2] DMAONERR
//
// DMA on error. If this bit is set to 1, the DMA receive request outputs (for
// single and burst requests) are disabled when the UART error interrupt is
// asserted (more specifically if any of the error interrupts RIS.PERIS,
// RIS.BERIS, RIS.FERIS or RIS.OERIS are asserted).
#define UART_DMACTL_DMAONERR                                        0x00000004U
#define UART_DMACTL_DMAONERR_M                                      0x00000004U
#define UART_DMACTL_DMAONERR_S                                               2U

// Field:     [1] TXDMAE
//
// Transmit DMA enable. If this bit is set to 1, DMA for the transmit FIFO is
// enabled.
#define UART_DMACTL_TXDMAE                                          0x00000002U
#define UART_DMACTL_TXDMAE_M                                        0x00000002U
#define UART_DMACTL_TXDMAE_S                                                 1U

// Field:     [0] RXDMAE
//
// Receive DMA enable. If this bit is set to 1, DMA for the receive FIFO is
// enabled.
#define UART_DMACTL_RXDMAE                                          0x00000001U
#define UART_DMACTL_RXDMAE_M                                        0x00000001U
#define UART_DMACTL_RXDMAE_S                                                 0U


#endif // __UART__
