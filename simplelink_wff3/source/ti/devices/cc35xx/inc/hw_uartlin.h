/******************************************************************************
*  Filename:       hw_uartlin.h
*
*  Description:    Defines and prototypes for the UARTLIN peripheral.
*
*  Copyright (c) 2023, Texas Instruments Incorporated
*  All rights reserved.
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
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
*
******************************************************************************/
#ifndef __HW_UARTLIN_H__
#define __HW_UARTLIN_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the UARTLIN component

--------------------------------------------------------------------------------- */

//Data
#define UARTLIN_O_DR                                                 0x00000000U

//Status
#define UARTLIN_O_RSRECR                                             0x00000004U

//Flag
#define UARTLIN_O_FR                                                 0x00000018U

//IrDA <Low-Power Counter Register
#define UARTLIN_O_UARTILPR                                           0x00000020U

//Integer Baud-Rate Divisor
#define UARTLIN_O_IBRD                                               0x00000024U

//Fractional Baud-Rate Divisor
#define UARTLIN_O_FBRD                                               0x00000028U

//Line Control
#define UARTLIN_O_LCRH                                               0x0000002CU

//Control
#define UARTLIN_O_CTL                                                0x00000030U

//Interrupt **FIFO** Level Select
#define UARTLIN_O_IFLS                                               0x00000034U

//Interrupt Mask Set/Clear
#define UARTLIN_O_IMSC                                               0x00000038U

//Raw Interrupt Status
#define UARTLIN_O_RIS                                                0x0000003CU

//Masked Interrupt Status
#define UARTLIN_O_MIS                                                0x00000040U

//Interrupt Clear
#define UARTLIN_O_ICR                                                0x00000044U

//DMA Control
#define UARTLIN_O_DMACTL                                             0x00000048U

//Test Control
#define UARTLIN_O_TCR                                                0x00000080U

//Integration Test Input
#define UARTLIN_O_ITIP                                               0x00000084U

//Integration Test Output
#define UARTLIN_O_ITOP                                               0x00000088U

//Test Data
#define UARTLIN_O_TDR                                                0x0000008CU

//Peripheral Identification 0
#define UARTLIN_O_PERIPHID0                                          0x00000FE0U

//Peripheral Identification 1
#define UARTLIN_O_PERIPHID1                                          0x00000FE4U

//Peripheral Identification 2
#define UARTLIN_O_PERIPHID2                                          0x00000FE8U

//Peripheral Identification 3
#define UARTLIN_O_PERIPHID3                                          0x00000FECU

//PrimeCell Identification 0
#define UARTLIN_O_PCELLID0                                           0x00000FF0U

//PrimeCell Identification 1
#define UARTLIN_O_PCELLID1                                           0x00000FF4U

//PrimeCell Identification 2
#define UARTLIN_O_PCELLID2                                           0x00000FF8U

//PrimeCell Identification 3
#define UARTLIN_O_PCELLID3                                           0x00000FFCU

//This register enable or disables the bus clock *uartlin*
#define UARTLIN_O_CLKCFG                                             0x00001000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       DR
    Offset name:         UARTLIN_O_DR
    Relative address:    0x0
    Description:         Data
                        For words to be transmitted:
                          - if the **FIFO**s are enabled ([LCRH.FEN] = 1), data written to this location is pushed onto the transmit **FIFO**
                          - if the **FIFO**s are not enabled ([LCRH.FEN] = 0), data is stored in the transmitter holding register (the bottom word of the transmit **FIFO**).
                        The write operation initiates transmission from the **UART**. The data is prefixed with a start bit, appended with the appropriate parity bit (if parity is enabled), and a stop bit.
                        The resultant word is then transmitted.
                        For received words:
                          - if the **FIFO**s are enabled ([LCRH.FEN] = 1), the data byte and the 4-bit status (break, frame, parity, and overrun) is pushed onto the 12-bit wide receive **FIFO**
                          - if the **FIFO**s are not enabled ([LCRH.FEN] = 0), the data byte and status are stored in the receiving holding register (the bottom word of the receive **FIFO**).
                        The received data byte is read by performing reads from this register along with the corresponding status information. The status information can also be read by a read of the [RSR.*] register.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data transmitted or received:
                         On writes, the transmit data character is pushed into the **FIFO**.
                         On reads, the oldest received data character since the last read is returned.

*/
#define UARTLIN_DR_DATA_W                                            8U
#define UARTLIN_DR_DATA_M                                            0x000000FFU
#define UARTLIN_DR_DATA_S                                            0U
/*

        Field:           FE
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Framing Error:
                         When set to 1, it indicates that the received character did not have a valid stop bit (a valid stop bit is 1).
                         In **FIFO** mode, this error is associated with the character at the top of the **FIFO** (i.e., the oldest received data character since last read).

*/
#define UARTLIN_DR_FE                                                0x00000100U
#define UARTLIN_DR_FE_M                                              0x00000100U
#define UARTLIN_DR_FE_S                                              8U
/*

        Field:           PE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Parity Error:
                         When set to 1, it indicates that the parity of the received data character does not match the parity that the [LCRH.EPS] and [LCRH.SPS] select.
                         In **FIFO** mode, this error is associated with the character at the top of the **FIFO** (i.e., the oldest received data character since last read).

*/
#define UARTLIN_DR_PE                                                0x00000200U
#define UARTLIN_DR_PE_M                                              0x00000200U
#define UARTLIN_DR_PE_S                                              9U
/*

        Field:           BE
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Break Error:
                         This bit is set to 1 if a break condition was detected, indicating that the received data input (**UARTRXD** input pin) was held LOW for longer than a full-word transmission time (defined as start, data, parity and stop bits).
                         In **FIFO** mode, this error is associated with the character at the top of the **FIFO** (i.e., the oldest received data character since last read). When a break occurs, a 0 character is loaded into the **FIFO**. The next character is enabled after the receive data input (**UARTRXD** input pin) goes to a 1 (marking state), and the next valid start bit is received.

*/
#define UARTLIN_DR_BE                                                0x00000400U
#define UARTLIN_DR_BE_M                                              0x00000400U
#define UARTLIN_DR_BE_S                                              10U
/*

        Field:           OE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Overrun Error:
                         This bit is set to 1 if data is received and the receive **FIFO** is already full. The **FIFO** contents remain valid because no more data is written when the **FIFO** is full, , only the contents of the shift register are overwritten.
                         This is cleared to 0 once there is an empty space in the **FIFO** and a new character can be written to it.

*/
#define UARTLIN_DR_OE                                                0x00000800U
#define UARTLIN_DR_OE_M                                              0x00000800U
#define UARTLIN_DR_OE_S                                              11U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSRECR
    Offset name:         UARTLIN_O_RSRECR
    Relative address:    0x4
    Description:         Status
                        This register is mapped to the same address as [ECR.*] register.  Reads from this address are associated with [RSR_ECR.*] register and return the receive status. Writes to this address are associated with [ECR.*] register and clear the receive status flags (framing, parity, break, and overrun errors).
                        If the status is read from this register, then the status information for break, framing and parity corresponds to the data character read from the Data Register, [DR.*] prior to reading the [RSR_ECR.*]. The status information for overrun is set immediately when an overrun condition occurs.
    Default Value:       0x00000000

        Field:           FE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Framing Error:
                         When set to 1, it indicates that the received character did not have a valid stop bit (a valid stop bit is 1).

        ENUMs:
            ERROR_SET:                   Error flag is set
            CLEAR_ERROR_0:               Clears error flag if error is set. Write value is not important.
            CLEAR_ERROR_1:               Clears error flag if error is set. Write value is not important.
            ERROR_NOTSET:                Error flag is not set
*/
#define UARTLIN_RSRECR_FE                                            0x00000001U
#define UARTLIN_RSRECR_FE_M                                          0x00000001U
#define UARTLIN_RSRECR_FE_S                                          0U
#define UARTLIN_RSRECR_FE_ERROR_SET                                  0x00000001U
#define UARTLIN_RSRECR_FE_CLEAR_ERROR_0                              0x00000000U
#define UARTLIN_RSRECR_FE_CLEAR_ERROR_1                              0x00000001U
#define UARTLIN_RSRECR_FE_ERROR_NOTSET                               0x00000000U
/*

        Field:           PE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Parity Error:
                         When set to 1, it indicates that the parity of the received data character does not match the parity that the [LCRH.EPS] and [LCRH.SPS] select.

        ENUMs:
            CLEAR_ERROR_0:               Clears error flag if error is set. Write value is not important.
            ERROR_NOTSET:                Error flag is not set
            ERROR_SET:                   Error flag is set
            CLEAR_ERROR_1:               Clears error flag if error is set. Write value is not important.
*/
#define UARTLIN_RSRECR_PE                                            0x00000002U
#define UARTLIN_RSRECR_PE_M                                          0x00000002U
#define UARTLIN_RSRECR_PE_S                                          1U
#define UARTLIN_RSRECR_PE_CLEAR_ERROR_0                              0x00000000U
#define UARTLIN_RSRECR_PE_ERROR_NOTSET                               0x00000000U
#define UARTLIN_RSRECR_PE_ERROR_SET                                  0x00000002U
#define UARTLIN_RSRECR_PE_CLEAR_ERROR_1                              0x00000002U
/*

        Field:           BE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Break Error:
                         This bit is set to 1 if a break condition was detected, indicating that the received data input (**UARTRXD** input pin) was held LOW for longer than a full-word transmission time (defined as start, data, parity and stop bits).
                         When a break occurs, a 0 character is loaded into the **FIFO**. The next character is enabled after the receive data input (**UARTRXD** input pin) goes to a 1 (marking state), and the next valid start bit is received.

        ENUMs:
            CLEAR_ERROR_0:               Clears error flag if error is set. Write value is not important.
            ERROR_NOTSET:                Error flag is not set
            ERROR_SET:                   Error flag is set
            CLEAR_ERROR_1:               Clears error flag if error is set. Write value is not important.
*/
#define UARTLIN_RSRECR_BE                                            0x00000004U
#define UARTLIN_RSRECR_BE_M                                          0x00000004U
#define UARTLIN_RSRECR_BE_S                                          2U
#define UARTLIN_RSRECR_BE_CLEAR_ERROR_0                              0x00000000U
#define UARTLIN_RSRECR_BE_ERROR_NOTSET                               0x00000000U
#define UARTLIN_RSRECR_BE_ERROR_SET                                  0x00000004U
#define UARTLIN_RSRECR_BE_CLEAR_ERROR_1                              0x00000004U
/*

        Field:           OE
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Overrun Error:
                         This bit is set to 1 if data is received and the receive **FIFO** is already full. The **FIFO** contents remain valid because no more data is written when the **FIFO** is full, , only the contents of the shift register are overwritten.
                         This is cleared to 0 once there is an empty space in the **FIFO** and a new character can be written to it.

        ENUMs:
            CLEAR_ERROR_0:               Clears error flag if error is set. Write value is not important.
            ERROR_NOTSET:                Error flag is not set
            ERROR_SET:                   Error flag is set
            CLEAR_ERROR_1:               Clears error flag if error is set. Write value is not important.
*/
#define UARTLIN_RSRECR_OE                                            0x00000008U
#define UARTLIN_RSRECR_OE_M                                          0x00000008U
#define UARTLIN_RSRECR_OE_S                                          3U
#define UARTLIN_RSRECR_OE_CLEAR_ERROR_0                              0x00000000U
#define UARTLIN_RSRECR_OE_ERROR_NOTSET                               0x00000000U
#define UARTLIN_RSRECR_OE_ERROR_SET                                  0x00000008U
#define UARTLIN_RSRECR_OE_CLEAR_ERROR_1                              0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FR
    Offset name:         UARTLIN_O_FR
    Relative address:    0x18
    Description:         Flag
                        Reads from this register return the **UART** flags.
    Default Value:       0x00000000

        Field:           CTS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Clear To Send:
                         This bit is the complement of the active-low **UART** **CTS** input pin.
                         That is, the bit is 1 when **CTS** input pin is LOW.

*/
#define UARTLIN_FR_CTS                                               0x00000001U
#define UARTLIN_FR_CTS_M                                             0x00000001U
#define UARTLIN_FR_CTS_S                                             0U
/*

        Field:           BUSY
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Busy:
                         If this bit is set to 1, the **UART** is busy transmitting data. This bit remains set until the complete byte, including all the stop bits, has been sent from the shift register.
                         This bit is set as soon as the transmit **FIFO** becomes non-empty, regardless of whether the **UART** is enabled or not.

*/
#define UARTLIN_FR_BUSY                                              0x00000008U
#define UARTLIN_FR_BUSY_M                                            0x00000008U
#define UARTLIN_FR_BUSY_S                                            3U
/*

        Field:           RXFE
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Receive **FIFO** Empty:
                         Receive **FIFO** empty. The meaning of this bit depends on the state of [LCRH.FEN].
                           - If the **FIFO** is disabled, this bit is set when the receive holding register is empty.
                           - If the **FIFO** is enabled, this bit is set when the receive **FIFO** is empty.

*/
#define UARTLIN_FR_RXFE                                              0x00000010U
#define UARTLIN_FR_RXFE_M                                            0x00000010U
#define UARTLIN_FR_RXFE_S                                            4U
/*

        Field:           TXFF
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Transmit **FIFO** Full:
                         Transmit **FIFO** full. The meaning of this bit depends on the state of [LCRH.FEN].
                           - If the **FIFO** is disabled, this bit is set when the transmit holding register is full.
                           - If the **FIFO** is enabled, this bit is set when the transmit **FIFO** is full.

*/
#define UARTLIN_FR_TXFF                                              0x00000020U
#define UARTLIN_FR_TXFF_M                                            0x00000020U
#define UARTLIN_FR_TXFF_S                                            5U
/*

        Field:           RXFF
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Receive **FIFO** Full:
                         The meaning of this bit depends on the state of [LCRH.FEN].
                           - If the **FIFO** is disabled, this bit is set when the receive holding register is full.
                           - If the **FIFO** is enabled, this bit is set when the receive **FIFO** is full.

*/
#define UARTLIN_FR_RXFF                                              0x00000040U
#define UARTLIN_FR_RXFF_M                                            0x00000040U
#define UARTLIN_FR_RXFF_S                                            6U
/*

        Field:           TXFE
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART Transmit **FIFO** Empty:
                         The meaning of this bit depends on the state of [LCRH.FEN] .
                           - If the **FIFO** is disabled, this bit is set when the transmit holding register is empty.
                           - If the **FIFO** is enabled, this bit is set when the transmit **FIFO** is empty.
                         This bit does not indicate if there is data in the transmit shift register.

*/
#define UARTLIN_FR_TXFE                                              0x00000080U
#define UARTLIN_FR_TXFE_M                                            0x00000080U
#define UARTLIN_FR_TXFE_S                                            7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UARTILPR
    Offset name:         UARTLIN_O_UARTILPR
    Relative address:    0x20
    Description:         IrDA <Low-Power Counter Register
    Default Value:       0x00000000

        Field:           ILPDVSR
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     8 bit low-power divisor value

*/
#define UARTLIN_UARTILPR_ILPDVSR_W                                   8U
#define UARTLIN_UARTILPR_ILPDVSR_M                                   0x000000FFU
#define UARTLIN_UARTILPR_ILPDVSR_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IBRD
    Offset name:         UARTLIN_O_IBRD
    Relative address:    0x24
    Description:         Integer Baud-Rate Divisor
                        If this register is modified while transmission or reception is on-going, the baudrate will not be updated until transmission or reception of the current character is complete.
    Default Value:       0x00000000

        Field:           DIVINT
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The integer baud rate divisor:
                         The baud rate divisor is calculated using the formula below:
                         Baud rate divisor = (UART reference clock frequency) / (16 * Baud rate)
                         Baud rate divisor must be minimum 1 and maximum 65535.
                         That is, [DIVINT]=0 does not give a valid baud rate.
                         Similarly, if [DIVINT]=0xFFFF, any non-zero values in [FBRD.DIVFRAC] will be illegal.
                         A valid value must be written to this field before the **UART** can be used for **RX** or **TX** operations.
                         INTERNAL_NOTE
                         The calculator below can be used to find the register values:
                         [Baud-rate calculator](https://spsemea.itg.ti.com/sites/lpw/proj/CC26xx/Modules/UART/UART_baudrate_calculator.xlsx)

*/
#define UARTLIN_IBRD_DIVINT_W                                        16U
#define UARTLIN_IBRD_DIVINT_M                                        0x0000FFFFU
#define UARTLIN_IBRD_DIVINT_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FBRD
    Offset name:         UARTLIN_O_FBRD
    Relative address:    0x28
    Description:         Fractional Baud-Rate Divisor
                        If this register is modified while transmission or reception is on-going, the baudrate will not be updated until transmission or reception of the current character is complete.
    Default Value:       0x00000000

        Field:           DIVFRAC
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Fractional Baud-Rate Divisor:
                         The baud rate divisor is calculated using the formula below:
                         Baud rate divisor = (UART reference clock frequency) / (16 * Baud rate)
                         Baud rate divisor must be minimum 1 and maximum 65535.
                         That is, [IBRD.DIVINT]=0 does not give a valid baud rate.
                         Similarly, if [IBRD.DIVINT]=0xFFFF, any non-zero values in [DIVFRAC] will be illegal.
                         A valid value must be written to this field before the **UART** can be used for **RX** or **TX** operations.
                         INTERNAL_NOTE
                         The calculator below can be used to find the register values:
                         [Baud-rate calculator](https://spsemea.itg.ti.com/sites/lpw/proj/CC26xx/Modules/UART/UART_baudrate_calculator.xlsx)

*/
#define UARTLIN_FBRD_DIVFRAC_W                                       6U
#define UARTLIN_FBRD_DIVFRAC_M                                       0x0000003FU
#define UARTLIN_FBRD_DIVFRAC_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LCRH
    Offset name:         UARTLIN_O_LCRH
    Relative address:    0x2C
    Description:         Line Control
    Default Value:       0x00000000

        Field:           BRK
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Send Break
                         If this bit is set to 1, a low-level is continually output on the **UARTTXD** output pin, after completing transmission of the current character. For the proper execution of the break command, the
                         software must set this bit for at least two complete frames. For normal use, this bit must be cleared to 0.

*/
#define UARTLIN_LCRH_BRK                                             0x00000001U
#define UARTLIN_LCRH_BRK_M                                           0x00000001U
#define UARTLIN_LCRH_BRK_S                                           0U
/*

        Field:           PEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Parity Enable
                         This bit controls generation and checking of parity bit.
                         INTERNAL_NOTE
                         See [Parity truth table](https://spsemea.itg.ti.com/sites/lpw/proj/CC26xx/Modules/UART/parity.png) for details.

        ENUMs:
            DIS:                         Parity is disabled and no parity bit is added to the data frame
            EN:                          Parity checking and generation is enabled.
*/
#define UARTLIN_LCRH_PEN                                             0x00000002U
#define UARTLIN_LCRH_PEN_M                                           0x00000002U
#define UARTLIN_LCRH_PEN_S                                           1U
#define UARTLIN_LCRH_PEN_DIS                                         0x00000000U
#define UARTLIN_LCRH_PEN_EN                                          0x00000002U
/*

        Field:           EPS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Even Parity Select

        ENUMs:
            ODD:                         Odd parity: The **UART** generates or checks for an odd number of 1s in the data and parity bits.
            EVEN:                        Even parity: The **UART** generates or checks for an even number of 1s in the data and parity bits.
*/
#define UARTLIN_LCRH_EPS                                             0x00000004U
#define UARTLIN_LCRH_EPS_M                                           0x00000004U
#define UARTLIN_LCRH_EPS_S                                           2U
#define UARTLIN_LCRH_EPS_ODD                                         0x00000000U
#define UARTLIN_LCRH_EPS_EVEN                                        0x00000004U
/*

        Field:           STP2
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Two Stop Bits Select:
                         If this bit is set to 1, two stop bits are transmitted at the end of the frame. The receive logic does not check for two stop bits being received.

*/
#define UARTLIN_LCRH_STP2                                            0x00000008U
#define UARTLIN_LCRH_STP2_M                                          0x00000008U
#define UARTLIN_LCRH_STP2_S                                          3U
/*

        Field:           FEN
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Enable **FIFO**s

        ENUMs:
            DIS:                         **FIFO**s are disabled (character mode) that is, the **FIFO**s become 1-byte-deep holding registers.
            EN:                          Transmit and receive **FIFO** buffers are enabled (**FIFO** mode)
*/
#define UARTLIN_LCRH_FEN                                             0x00000010U
#define UARTLIN_LCRH_FEN_M                                           0x00000010U
#define UARTLIN_LCRH_FEN_S                                           4U
#define UARTLIN_LCRH_FEN_DIS                                         0x00000000U
#define UARTLIN_LCRH_FEN_EN                                          0x00000010U
/*

        Field:           WLEN
        From..to bits:   5...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Word Length:
                         These bits indicate the number of data bits transmitted or received in a frame.

        ENUMs:
            BITL5:                       Word Length 5 bits
            BITL6:                       Word Length 6 bits
            BITL7:                       Word Length 7 bits
            BITL8:                       Word Length 8 bits
*/
#define UARTLIN_LCRH_WLEN_W                                          2U
#define UARTLIN_LCRH_WLEN_M                                          0x00000060U
#define UARTLIN_LCRH_WLEN_S                                          5U
#define UARTLIN_LCRH_WLEN_BITL5                                      0x00000000U
#define UARTLIN_LCRH_WLEN_BITL6                                      0x00000020U
#define UARTLIN_LCRH_WLEN_BITL7                                      0x00000040U
#define UARTLIN_LCRH_WLEN_BITL8                                      0x00000060U
/*

        Field:           SPS
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Stick Parity Select:

                         0: Stick parity is disabled
                         1: The parity bit is transmitted and checked as invert of [EPS] field (i.e. the parity bit is transmitted and checked as 1 when [EPS] = 0).

                         This bit has no effect when [PEN] disables parity checking and generation.

*/
#define UARTLIN_LCRH_SPS                                             0x00000080U
#define UARTLIN_LCRH_SPS_M                                           0x00000080U
#define UARTLIN_LCRH_SPS_S                                           7U
/*

        Field:           TXBRKSYNC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART LIN mode TXBRKSYNC:

                         0: In LIN mode TXBRKSYNC will not be sent.
                         1: In LIN mode send TXBRKSYNC field and reset the LCRH.TXBRKSYNC bit.

                         This bit has no effect when [PEN] disables parity checking and generation.

*/
#define UARTLIN_LCRH_TXBRKSYNC                                       0x00000100U
#define UARTLIN_LCRH_TXBRKSYNC_M                                     0x00000100U
#define UARTLIN_LCRH_TXBRKSYNC_S                                     8U
/*

        Field:           DELIM
        From..to bits:   9...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In UART LIN defines the length of DELIM field that has to be sent

        ENUMs:
            LEN_1:
            LEN_2:
            LEN_3:
            LEN_4:
*/
#define UARTLIN_LCRH_DELIM_W                                         2U
#define UARTLIN_LCRH_DELIM_M                                         0x00000600U
#define UARTLIN_LCRH_DELIM_S                                         9U
#define UARTLIN_LCRH_DELIM_LEN_1                                     0x00000000U
#define UARTLIN_LCRH_DELIM_LEN_2                                     0x00000200U
#define UARTLIN_LCRH_DELIM_LEN_3                                     0x00000400U
#define UARTLIN_LCRH_DELIM_LEN_4                                     0x00000600U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL
    Offset name:         UARTLIN_O_CTL
    Relative address:    0x30
    Description:         Control
    Default Value:       0x00000000

        Field:           UARTEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Enable

        ENUMs:
            DIS:                         UART disabled
            EN:                          UART enabled
*/
#define UARTLIN_CTL_UARTEN                                           0x00000001U
#define UARTLIN_CTL_UARTEN_M                                         0x00000001U
#define UARTLIN_CTL_UARTEN_S                                         0U
#define UARTLIN_CTL_UARTEN_DIS                                       0x00000000U
#define UARTLIN_CTL_UARTEN_EN                                        0x00000001U
/*

        Field:           SIREN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SIR Enable
                         This bit has no effect if UARTEN bit disables the UART.

        ENUMs:
            DIS:                         IrDA SIR ENDEC is disabled
            EN:                          IrDA SIR ENDEC is enabled. Data is transmitted and received via nSIROUT and SIRIN.
*/
#define UARTLIN_CTL_SIREN                                            0x00000002U
#define UARTLIN_CTL_SIREN_M                                          0x00000002U
#define UARTLIN_CTL_SIREN_S                                          1U
#define UARTLIN_CTL_SIREN_DIS                                        0x00000000U
#define UARTLIN_CTL_SIREN_EN                                         0x00000002U
/*

        Field:           SIRLP
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SIR low power IrDA mode
                         This bit selects the IrDA encoding mode

        ENUMs:
            DIS:                         Low-level bits are transmitted as active high with a 3/16th period width,
            EN:                          Low-level bits are transmitted with a pulse width of 3 times the period of IrLPBaud16, regardless of the selected bit rate.
*/
#define UARTLIN_CTL_SIRLP                                            0x00000004U
#define UARTLIN_CTL_SIRLP_M                                          0x00000004U
#define UARTLIN_CTL_SIRLP_S                                          2U
#define UARTLIN_CTL_SIRLP_DIS                                        0x00000000U
#define UARTLIN_CTL_SIRLP_EN                                         0x00000004U
/*

        Field:           LINEN
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This is the LIN Mode of operation configuration bit.

        ENUMs:
            DIS:
            EN:
*/
#define UARTLIN_CTL_LINEN                                            0x00000008U
#define UARTLIN_CTL_LINEN_M                                          0x00000008U
#define UARTLIN_CTL_LINEN_S                                          3U
#define UARTLIN_CTL_LINEN_DIS                                        0x00000000U
#define UARTLIN_CTL_LINEN_EN                                         0x00000008U
/*

        Field:           ABDEN
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This configuration bit defines whether we want automatic baud rate detection enabled or not in the LIN mode of operation.

        ENUMs:
            DIS:
            EN:
*/
#define UARTLIN_CTL_ABDEN                                            0x00000010U
#define UARTLIN_CTL_ABDEN_M                                          0x00000010U
#define UARTLIN_CTL_ABDEN_S                                          4U
#define UARTLIN_CTL_ABDEN_DIS                                        0x00000000U
#define UARTLIN_CTL_ABDEN_EN                                         0x00000010U
/*

        Field:           DORMEN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DORMEN bit is only functionally makes sense for LIN mode of operation.
                         When dormant mode is disabled, break and sync data shall be loaded to RX FIFO and associated interrupt flags shall be set as in normal UART operation.
                         When dormant mode is enabled, break and sync data shall not be loaded to RX FIFO and RX FIFO shall be updated with actual data (PID) only after successful reception of break/sync fields.

        ENUMs:
            DIS:
            EN:
*/
#define UARTLIN_CTL_DORMEN                                           0x00000020U
#define UARTLIN_CTL_DORMEN_M                                         0x00000020U
#define UARTLIN_CTL_DORMEN_S                                         5U
#define UARTLIN_CTL_DORMEN_DIS                                       0x00000000U
#define UARTLIN_CTL_DORMEN_EN                                        0x00000020U
/*

        Field:           FCEN
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART FIFO Concatenation Enable
                         Enabling the lFIFO concatenation in TX moderesulting in 16 TX buffers.

        ENUMs:
            DIS:                         UART FIFO Concatenation  disabled
            EN:                          UART FIFO Concatenation  enabled
*/
#define UARTLIN_CTL_FCEN                                             0x00000040U
#define UARTLIN_CTL_FCEN_M                                           0x00000040U
#define UARTLIN_CTL_FCEN_S                                           6U
#define UARTLIN_CTL_FCEN_DIS                                         0x00000000U
#define UARTLIN_CTL_FCEN_EN                                          0x00000040U
/*

        Field:           LBE
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Loop Back Enable
                         Enabling the loop-back mode connects the **UARTTXD** output from the **UART** to **UARTRXD** input of the **UART**.

        ENUMs:
            DIS:                         Loop Back disabled
            EN:                          Loop Back enabled
*/
#define UARTLIN_CTL_LBE                                              0x00000080U
#define UARTLIN_CTL_LBE_M                                            0x00000080U
#define UARTLIN_CTL_LBE_S                                            7U
#define UARTLIN_CTL_LBE_DIS                                          0x00000000U
#define UARTLIN_CTL_LBE_EN                                           0x00000080U
/*

        Field:           TXE
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Transmit Enable
                         If the **UART** is disabled in the middle of transmission, it completes the current character before stopping.

        ENUMs:
            DIS:                         UART Transmit disabled
            EN:                          UART Transmit enabled
*/
#define UARTLIN_CTL_TXE                                              0x00000100U
#define UARTLIN_CTL_TXE_M                                            0x00000100U
#define UARTLIN_CTL_TXE_S                                            8U
#define UARTLIN_CTL_TXE_DIS                                          0x00000000U
#define UARTLIN_CTL_TXE_EN                                           0x00000100U
/*

        Field:           RXE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UART Receive Enable
                         If the **UART** is disabled in the middle of reception, it completes the current character before stopping.

        ENUMs:
            DIS:                         UART Receive disabled
            EN:                          UART Receive enabled
*/
#define UARTLIN_CTL_RXE                                              0x00000200U
#define UARTLIN_CTL_RXE_M                                            0x00000200U
#define UARTLIN_CTL_RXE_S                                            9U
#define UARTLIN_CTL_RXE_DIS                                          0x00000000U
#define UARTLIN_CTL_RXE_EN                                           0x00000200U
/*

        Field:           RTS
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Request to Send
                         This bit is the complement of the active-low **UART** **RTS** output. That is, when the bit is programmed to a 1 then **RTS** output on the pins is LOW.

*/
#define UARTLIN_CTL_RTS                                              0x00000800U
#define UARTLIN_CTL_RTS_M                                            0x00000800U
#define UARTLIN_CTL_RTS_S                                            11U
/*

        Field:           RTSEN
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     **RTS** hardware flow control enable

        ENUMs:
            DIS:                         **RTS** hardware flow control disabled
            EN:                          **RTS** hardware flow control enabled
*/
#define UARTLIN_CTL_RTSEN                                            0x00004000U
#define UARTLIN_CTL_RTSEN_M                                          0x00004000U
#define UARTLIN_CTL_RTSEN_S                                          14U
#define UARTLIN_CTL_RTSEN_DIS                                        0x00000000U
#define UARTLIN_CTL_RTSEN_EN                                         0x00004000U
/*

        Field:           CTSEN
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     **CTS** hardware flow control enable

        ENUMs:
            DIS:                         **CTS** hardware flow control disabled
            EN:                          **CTS** hardware flow control enabled
*/
#define UARTLIN_CTL_CTSEN                                            0x00008000U
#define UARTLIN_CTL_CTSEN_M                                          0x00008000U
#define UARTLIN_CTL_CTSEN_S                                          15U
#define UARTLIN_CTL_CTSEN_DIS                                        0x00000000U
#define UARTLIN_CTL_CTSEN_EN                                         0x00008000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IFLS
    Offset name:         UARTLIN_O_IFLS
    Relative address:    0x34
    Description:         Interrupt **FIFO** Level Select
    Default Value:       0x00000002

        Field:           TXSEL
        From..to bits:   0...2
        DefaultValue:    0x2
        Access type:     read-write
        Description:     Transmit interrupt **FIFO** level select:
                         This field sets the trigger points for the transmit interrupt. Values 0b101-0b111 are reserved.

        ENUMs:
            QUARTER:                     Transmit **FIFO** becomes <= 1/4 full
            HALF:                        Transmit **FIFO** becomes <= 1/2 full
            THREEQU:                     Transmit **FIFO** becomes <= 3/4 full
*/
#define UARTLIN_IFLS_TXSEL_W                                         3U
#define UARTLIN_IFLS_TXSEL_M                                         0x00000007U
#define UARTLIN_IFLS_TXSEL_S                                         0U
#define UARTLIN_IFLS_TXSEL_QUARTER                                   0x00000001U
#define UARTLIN_IFLS_TXSEL_HALF                                      0x00000002U
#define UARTLIN_IFLS_TXSEL_THREEQU                                   0x00000003U
/*

        Field:           RXSEL
        From..to bits:   3...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive interrupt **FIFO** level select:
                         This field sets the trigger points for the receive interrupt. Values 0b101-0b111 are reserved.

        ENUMs:
            QUARTER:                     Receive **FIFO** becomes >= 1/4 full
            HALF:                        Receive **FIFO** becomes >= 1/2 full
            THREEQU:                     Receive **FIFO** becomes >= 3/4 full
*/
#define UARTLIN_IFLS_RXSEL_W                                         3U
#define UARTLIN_IFLS_RXSEL_M                                         0x00000038U
#define UARTLIN_IFLS_RXSEL_S                                         3U
#define UARTLIN_IFLS_RXSEL_QUARTER                                   0x00000008U
#define UARTLIN_IFLS_RXSEL_HALF                                      0x00000010U
#define UARTLIN_IFLS_RXSEL_THREEQU                                   0x00000018U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMSC
    Offset name:         UARTLIN_O_IMSC
    Relative address:    0x38
    Description:         Interrupt Mask Set/Clear
    Default Value:       0x00000000

        Field:           CTSM
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clear to Send (CTS) modem interrupt mask. A read returns the current mask for **UART**'s clear to send interrupt. On a write of 1, the mask of the overrun error interrupt is set which means the interrupt state will be reflected in [MIS.CTSMMIS]. A write of 0 clears the mask which means [MIS.CTSMMIS] will not reflect the interrupt.

*/
#define UARTLIN_IMSC_CTSM                                            0x00000002U
#define UARTLIN_IMSC_CTSM_M                                          0x00000002U
#define UARTLIN_IMSC_CTSM_S                                          1U
/*

        Field:           RX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive interrupt mask. A read returns the current mask for **UART**'s receive interrupt. On a write of 1, the mask of the overrun error interrupt is set which means the interrupt state will be reflected in [MIS.RXMIS]. A write of 0 clears the mask which means [MIS.RXMIS] will not reflect the interrupt.

*/
#define UARTLIN_IMSC_RX                                              0x00000010U
#define UARTLIN_IMSC_RX_M                                            0x00000010U
#define UARTLIN_IMSC_RX_S                                            4U
/*

        Field:           TX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit interrupt mask. A read returns the current mask for **UART**'s transmit interrupt. On a write of 1, the mask of the overrun error interrupt is set which means the interrupt state will be reflected in [MIS.TXMIS]. A write of 0 clears the mask which means [MIS.TXMIS] will not reflect the interrupt.

*/
#define UARTLIN_IMSC_TX                                              0x00000020U
#define UARTLIN_IMSC_TX_M                                            0x00000020U
#define UARTLIN_IMSC_TX_S                                            5U
/*

        Field:           RT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive timeout interrupt mask. A read returns the current mask for **UART**'s receive timeout interrupt. On a write of 1, the mask of the overrun error interrupt is set which means the interrupt state will be reflected in [MIS.RTMIS]. A write of 0 clears the mask which means this bitfield will not reflect the interrupt.
                         The raw interrupt for receive timeout [RIS.RTRIS] cannot be set unless the mask is set ([RTIM] = 1). This is because the mask acts as an enable for power saving. That is, the same status can be read from [MIS.RTMIS] and [RIS.RTRIS].

*/
#define UARTLIN_IMSC_RT                                              0x00000040U
#define UARTLIN_IMSC_RT_M                                            0x00000040U
#define UARTLIN_IMSC_RT_S                                            6U
/*

        Field:           FE
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Framing error interrupt mask. A read returns the current mask for **UART**'s framing error interrupt. On a write of 1, the mask of the overrun error interrupt is set which means the interrupt state will be reflected in [MIS.FEMIS]. A write of 0 clears the mask which means [MIS.FEMIS] will not reflect the interrupt.

*/
#define UARTLIN_IMSC_FE                                              0x00000080U
#define UARTLIN_IMSC_FE_M                                            0x00000080U
#define UARTLIN_IMSC_FE_S                                            7U
/*

        Field:           PE
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Parity error interrupt mask. A read returns the current mask for **UART**'s parity error interrupt. On a write of 1, the mask of the overrun error interrupt is set which means the interrupt state will be reflected in [MIS.PEMIS]. A write of 0 clears the mask which means [MIS.PEMIS] will not reflect the interrupt.

*/
#define UARTLIN_IMSC_PE                                              0x00000100U
#define UARTLIN_IMSC_PE_M                                            0x00000100U
#define UARTLIN_IMSC_PE_S                                            8U
/*

        Field:           BE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Break error interrupt mask. A read returns the current mask for **UART**'s break error interrupt. On a write of 1, the mask of the overrun error interrupt is set which means the interrupt state will be reflected in [MIS.BEMIS]. A write of 0 clears the mask which means [MIS.BEMIS] will not reflect the interrupt.

*/
#define UARTLIN_IMSC_BE                                              0x00000200U
#define UARTLIN_IMSC_BE_M                                            0x00000200U
#define UARTLIN_IMSC_BE_S                                            9U
/*

        Field:           OE
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Overrun error interrupt mask. A read returns the current mask for **UART**'s overrun error interrupt. On a write of 1, the mask of the overrun error interrupt is set which means the interrupt state will be reflected in [MIS.OEMIS]. A write of 0 clears the mask which means [MIS.OEMIS] will not reflect the interrupt.

*/
#define UARTLIN_IMSC_OE                                              0x00000400U
#define UARTLIN_IMSC_OE_M                                            0x00000400U
#define UARTLIN_IMSC_OE_S                                            10U
/*

        Field:           EOT
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     End of Transmission interrupt mask. A read returns the current mask for UART's EoT interrupt. On a write of 1, the mask of the EoT interrupt is set which means the interrupt state will be reflected in MIS.EOTMIS. A write of 0 clears the mask which means MIS.EOTMIS will not reflect the interrupt.

*/
#define UARTLIN_IMSC_EOT                                             0x00000800U
#define UARTLIN_IMSC_EOT_M                                           0x00000800U
#define UARTLIN_IMSC_EOT_S                                           11U
/*

        Field:           TXDMADONE
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tx DMA done interrupt mask. A read returns the current mask for UART's TXDMADONE interrupt. On a write of 1, the mask of the TXDMADONE interrupt is set which means the interrupt state will be reflected in MIS.TXDMADONEMIS. A write of 0 clears the mask which means MIS.TXDMADONEMIS will not reflect the interrupt.

*/
#define UARTLIN_IMSC_TXDMADONE                                       0x00001000U
#define UARTLIN_IMSC_TXDMADONE_M                                     0x00001000U
#define UARTLIN_IMSC_TXDMADONE_S                                     12U
/*

        Field:           RXDMADONE
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Rx DMA done interrupt mask. A read returns the current mask for UART's RXDMADONE interrupt. On a write of 1, the mask of the RXDMADONE interrupt is set which means the interrupt state will be reflected in MIS.RXDMADONEMIS. A write of 0 clears the mask which means MIS.RXDMADONEMIS will not reflect the interrupt.

*/
#define UARTLIN_IMSC_RXDMADONE                                       0x00002000U
#define UARTLIN_IMSC_RXDMADONE_M                                     0x00002000U
#define UARTLIN_IMSC_RXDMADONE_S                                     13U
/*

        Field:           LINBRK
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LIN Break field received/detected interrupt mask. A read returns the current mask for UART's LINBRK interrupt. On a write of 1, the mask of the LINBRK interrupt is set which means the interrupt state will be reflected in MIS.LINBRK. A write of 0 clears the mask which means MIS.LINBRK will not reflect the interrupt.

*/
#define UARTLIN_IMSC_LINBRK                                          0x00004000U
#define UARTLIN_IMSC_LINBRK_M                                        0x00004000U
#define UARTLIN_IMSC_LINBRK_S                                        14U
/*

        Field:           LINBRKTOE
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LIN Break field Time out error interrupt mask. A read returns the current mask for UART's LINBRKTOE interrupt. On a write of 1, the mask of the LINBRKTOE interrupt is set which means the interrupt state will be reflected in MIS.LINBRKTOE. A write of 0 clears the mask which means MIS.LINBRKTOE will not reflect the interrupt.

*/
#define UARTLIN_IMSC_LINBRKTOE                                       0x00008000U
#define UARTLIN_IMSC_LINBRKTOE_M                                     0x00008000U
#define UARTLIN_IMSC_LINBRKTOE_S                                     15U
/*

        Field:           LINSYNCTOE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LIN Sync Time out error interrupt mask. A read returns the current mask for UART's LINSYNCTOE interrupt. On a write of 1, the mask of the LINSYNCTOE interrupt is set which means the interrupt state will be reflected in MIS.LINSYNCTOE. A write of 0 clears the mask which means MIS.LINSYNCTOE will not reflect the interrupt.

*/
#define UARTLIN_IMSC_LINSYNCTOE                                      0x00010000U
#define UARTLIN_IMSC_LINSYNCTOE_M                                    0x00010000U
#define UARTLIN_IMSC_LINSYNCTOE_S                                    16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RIS
    Offset name:         UARTLIN_O_RIS
    Relative address:    0x3C
    Description:         Raw Interrupt Status
    Default Value:       0x00000001

        Field:           CTSM
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Clear to Send (CTS) modem interrupt status:
                         This field returns the raw interrupt state of **UART**'s clear to send interrupt.

*/
#define UARTLIN_RIS_CTSM                                             0x00000002U
#define UARTLIN_RIS_CTSM_M                                           0x00000002U
#define UARTLIN_RIS_CTSM_S                                           1U
/*

        Field:           RX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive interrupt status:
                         This field returns the raw interrupt state of **UART**'s receive interrupt.
                         When **FIFO**s are enabled ([LCRH.FEN] = 1), the receive interrupt is asserted if the receive **FIFO** reaches the programmed trigger
                         level ([IFLS.RXSEL]). The receive interrupt is cleared by reading data from the receive **FIFO** until it becomes less than the trigger level, or by clearing the interrupt through [ICR.RXIC].
                         When **FIFO**s are disabled ([LCRH.FEN] = 0), that is they have a depth of one location, the receive interrupt is asserted if data is received
                         thereby filling the location. The receive interrupt is cleared by performing a single read of the receive **FIFO**, or by clearing the interrupt through [ICR.RXIC].

*/
#define UARTLIN_RIS_RX                                               0x00000010U
#define UARTLIN_RIS_RX_M                                             0x00000010U
#define UARTLIN_RIS_RX_S                                             4U
/*

        Field:           TX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Transmit interrupt status:
                         This field returns the raw interrupt state of **UART**'s transmit interrupt.
                         When **FIFO**s are enabled ([LCRH.FEN] = 1), the transmit interrupt is asserted if the number of bytes in transmit **FIFO** is equal to or lower than the programmed trigger level ([IFLS.TXSEL]). The transmit interrupt is cleared by writing data to the transmit **FIFO** until it becomes greater than the trigger level, or by clearing the interrupt through [ICR.TXIC].
                         When **FIFO**s are disabled ([LCRH.FEN] = 0), that is they have a depth of one location, the transmit interrupt is asserted if there is no data present in the transmitters single location. It is cleared by performing a single write to the transmit **FIFO**, or by clearing the interrupt through [ICR.TXIC].

*/
#define UARTLIN_RIS_TX                                               0x00000020U
#define UARTLIN_RIS_TX_M                                             0x00000020U
#define UARTLIN_RIS_TX_S                                             5U
/*

        Field:           RT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive timeout interrupt status:
                         This field returns the raw interrupt state of **UART**'s receive timeout interrupt. The receive timeout interrupt is asserted when the receive **FIFO** is not empty, and no more data is received during a 32-bit period. The receive timeout interrupt is cleared either when the **FIFO** becomes empty through reading all the data, or when a 1 is written to [ICR.RTIC].
                         The raw interrupt for receive timeout cannot be set unless the mask is set ([IMSC.RTIM] = 1). This is because the mask acts as an enable for power saving. That is, the same status can be read from [MIS.RTMIS] and [RTRIS].

*/
#define UARTLIN_RIS_RT                                               0x00000040U
#define UARTLIN_RIS_RT_M                                             0x00000040U
#define UARTLIN_RIS_RT_S                                             6U
/*

        Field:           FE
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Framing error interrupt status:
                         This field returns the raw interrupt state of **UART**'s framing error interrupt. Framing error is set if the received character does not have a valid stop bit (a valid stop bit is 1).

*/
#define UARTLIN_RIS_FE                                               0x00000080U
#define UARTLIN_RIS_FE_M                                             0x00000080U
#define UARTLIN_RIS_FE_S                                             7U
/*

        Field:           PE
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Parity error interrupt status:
                         This field returns the raw interrupt state of **UART**'s parity error interrupt. Parity error is set if the parity of the received data character does not match the parity that the [LCRH.EPS] and [LCRH.SPS] select.

*/
#define UARTLIN_RIS_PE                                               0x00000100U
#define UARTLIN_RIS_PE_M                                             0x00000100U
#define UARTLIN_RIS_PE_S                                             8U
/*

        Field:           BE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Break error interrupt status:
                         This field returns the raw interrupt state of **UART**'s break error interrupt. Break error is set when a break condition is detected, indicating that the received data input (**UARTRXD** input pin) was held LOW for longer than a full-word transmission time (defined as start, data, parity and stop bits).

*/
#define UARTLIN_RIS_BE                                               0x00000200U
#define UARTLIN_RIS_BE_M                                             0x00000200U
#define UARTLIN_RIS_BE_S                                             9U
/*

        Field:           OE
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Overrun error interrupt status:
                         This field returns the raw interrupt state of **UART**'s overrun error interrupt. Overrun error occurs if data is received and the receive **FIFO** is full.

*/
#define UARTLIN_RIS_OE                                               0x00000400U
#define UARTLIN_RIS_OE_M                                             0x00000400U
#define UARTLIN_RIS_OE_S                                             10U
/*

        Field:           EOT
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     End of Transmission interrupt status:
                         This field returns the raw interrupt state of UART's end of transmission interrupt. End of transmission flag is set when all the Transmit data in the FIFO and on the TX Line is transmitted.

*/
#define UARTLIN_RIS_EOT                                              0x00000800U
#define UARTLIN_RIS_EOT_M                                            0x00000800U
#define UARTLIN_RIS_EOT_S                                            11U
/*

        Field:           TXDMADONE
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Tx DMA done interrupt status:
                         This field returns the raw interrupt state of UART's tx dma done interrupt. TX DMA done flag is set when you receive tx dma done status from dma module.

*/
#define UARTLIN_RIS_TXDMADONE                                        0x00001000U
#define UARTLIN_RIS_TXDMADONE_M                                      0x00001000U
#define UARTLIN_RIS_TXDMADONE_S                                      12U
/*

        Field:           RXDMADONE
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Rx DMA done interrupt status:
                         This field returns the raw interrupt state of UART's rx dma done interrupt. RX DMA done flag is set when you receive rx dma done status from dma module.

*/
#define UARTLIN_RIS_RXDMADONE                                        0x00002000U
#define UARTLIN_RIS_RXDMADONE_M                                      0x00002000U
#define UARTLIN_RIS_RXDMADONE_S                                      13U
/*

        Field:           LINBRK
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LIN BRK detected interrupt status:
                         This field returns the raw interrupt state of whether break field is received/detected in UART's LIN mode of operation.

*/
#define UARTLIN_RIS_LINBRK                                           0x00004000U
#define UARTLIN_RIS_LINBRK_M                                         0x00004000U
#define UARTLIN_RIS_LINBRK_S                                         14U
/*

        Field:           LINBRKTOE
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LIN BRK field time out interrupt status:
                         This field returns the raw interrupt state of whether break field is measurable in UART's LIN mode of operation. This is set when the timer measuring the Break field overflows.

*/
#define UARTLIN_RIS_LINBRKTOE                                        0x00008000U
#define UARTLIN_RIS_LINBRKTOE_M                                      0x00008000U
#define UARTLIN_RIS_LINBRKTOE_S                                      15U
/*

        Field:           LINSYNCTOE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LIN SYNC field time out interrupt status:
                         This field returns the raw interrupt state of whether sync field is measurable in UART's LIN mode of operation. This is set when the timer measuring the SYNC field overflows.

*/
#define UARTLIN_RIS_LINSYNCTOE                                       0x00010000U
#define UARTLIN_RIS_LINSYNCTOE_M                                     0x00010000U
#define UARTLIN_RIS_LINSYNCTOE_S                                     16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MIS
    Offset name:         UARTLIN_O_MIS
    Relative address:    0x40
    Description:         Masked Interrupt Status
    Default Value:       0x00000000

        Field:           CTSM
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Clear to Send (CTS) modem masked interrupt status:
                         This field returns the masked interrupt state of the clear to send interrupt which is the AND product of raw interrupt state [RIS.CTSRMIS] and the mask setting [IMSC.CTSMIM].

*/
#define UARTLIN_MIS_CTSM                                             0x00000002U
#define UARTLIN_MIS_CTSM_M                                           0x00000002U
#define UARTLIN_MIS_CTSM_S                                           1U
/*

        Field:           RX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive masked interrupt status:
                         This field returns the masked interrupt state of the receive interrupt  which is the AND product of raw interrupt state [RIS.RXRIS] and the mask setting [IMSC.RXIM].

*/
#define UARTLIN_MIS_RX                                               0x00000010U
#define UARTLIN_MIS_RX_M                                             0x00000010U
#define UARTLIN_MIS_RX_S                                             4U
/*

        Field:           TX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Transmit masked interrupt status:
                         This field returns the masked interrupt state of the transmit interrupt  which is the AND product of raw interrupt state [RIS.TXRIS] and the mask setting [IMSC.TXIM].

*/
#define UARTLIN_MIS_TX                                               0x00000020U
#define UARTLIN_MIS_TX_M                                             0x00000020U
#define UARTLIN_MIS_TX_S                                             5U
/*

        Field:           RT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive timeout masked interrupt status:
                         Returns the masked interrupt state of the receive timeout interrupt.
                         The raw interrupt for receive timeout cannot be set unless the mask is set ([IMSC.RTIM] = 1). This is because the mask acts as an enable for power saving. That is, the same status can be read from [RTMIS] and [RIS.RTRIS].

*/
#define UARTLIN_MIS_RT                                               0x00000040U
#define UARTLIN_MIS_RT_M                                             0x00000040U
#define UARTLIN_MIS_RT_S                                             6U
/*

        Field:           FE
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Framing error masked interrupt status: Returns the masked interrupt state of the framing error interrupt which is the AND product of raw interrupt state [RIS.FERIS] and the mask setting [IMSC.FEIM].

*/
#define UARTLIN_MIS_FE                                               0x00000080U
#define UARTLIN_MIS_FE_M                                             0x00000080U
#define UARTLIN_MIS_FE_S                                             7U
/*

        Field:           PE
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Parity error masked interrupt status:
                         This field returns the masked interrupt state of the parity error interrupt which is the AND product of raw interrupt state [RIS.PERIS] and the mask setting [IMSC.PEIM].

*/
#define UARTLIN_MIS_PE                                               0x00000100U
#define UARTLIN_MIS_PE_M                                             0x00000100U
#define UARTLIN_MIS_PE_S                                             8U
/*

        Field:           BE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Break error masked interrupt status:
                         This field returns the masked interrupt state of the break error interrupt which is the AND product of raw interrupt state [RIS.BERIS] and the mask setting [IMSC.BEIM].

*/
#define UARTLIN_MIS_BE                                               0x00000200U
#define UARTLIN_MIS_BE_M                                             0x00000200U
#define UARTLIN_MIS_BE_S                                             9U
/*

        Field:           OE
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Overrun error masked interrupt status:
                         This field returns the masked interrupt state of the overrun interrupt which is the AND product of raw interrupt state [RIS.OERIS] and the mask setting [IMSC.OEIM].

*/
#define UARTLIN_MIS_OE                                               0x00000400U
#define UARTLIN_MIS_OE_M                                             0x00000400U
#define UARTLIN_MIS_OE_S                                             10U
/*

        Field:           EOT
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     End of Transmission interrupt status:
                         This field returns the masked interrupt state of the End of transmission interrupt which is the AND product of raw interrupt state RIS.EOTRIS and the mask setting IMSC.EOTIM.

*/
#define UARTLIN_MIS_EOT                                              0x00000800U
#define UARTLIN_MIS_EOT_M                                            0x00000800U
#define UARTLIN_MIS_EOT_S                                            11U
/*

        Field:           TXDMADONE
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Tx DMA done interrupt status:
                         This field returns the masked interrupt state of the tx dma done interrupt which is the AND product of raw interrupt state RIS.TXDMADONERIS and the mask setting IMSC.TXDMADONEIM.

*/
#define UARTLIN_MIS_TXDMADONE                                        0x00001000U
#define UARTLIN_MIS_TXDMADONE_M                                      0x00001000U
#define UARTLIN_MIS_TXDMADONE_S                                      12U
/*

        Field:           RXDMADONE
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Rx DMA done interrupt status:
                         This field returns the masked interrupt state of the rx dma done interrupt which is the AND product of raw interrupt state RIS.RXDMADONERIS and the mask setting IMSC.RXDMADONEIM.

*/
#define UARTLIN_MIS_RXDMADONE                                        0x00002000U
#define UARTLIN_MIS_RXDMADONE_M                                      0x00002000U
#define UARTLIN_MIS_RXDMADONE_S                                      13U
/*

        Field:           LINBRK
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LIN BRK field detected interrupt status:
                         This field returns the masked interrupt state of the LIN BRK detected interrupt which is the AND product of raw interrupt state RIS.LINBRKRIS and the mask setting IMSC.LINBRKIM.

*/
#define UARTLIN_MIS_LINBRK                                           0x00004000U
#define UARTLIN_MIS_LINBRK_M                                         0x00004000U
#define UARTLIN_MIS_LINBRK_S                                         14U
/*

        Field:           LINBRKTOE
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LIN BRK field time out error interrupt status:
                         This field returns the masked interrupt state of the LIN BRK timeout error interrupt which is the AND product of raw interrupt state RIS.LINBRKTOERIS and the mask setting IMSC.LINBRKTOEIM.

*/
#define UARTLIN_MIS_LINBRKTOE                                        0x00008000U
#define UARTLIN_MIS_LINBRKTOE_M                                      0x00008000U
#define UARTLIN_MIS_LINBRKTOE_S                                      15U
/*

        Field:           LINSYNCTOE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LIN sync field time out error interrupt status:
                         This field returns the masked interrupt state of the LIN sync timeout error interrupt which is the AND product of raw interrupt state RIS.LINSYNCTOERIS and the mask setting IMSC.LINSYNCTOEIM.

*/
#define UARTLIN_MIS_LINSYNCTOE                                       0x00010000U
#define UARTLIN_MIS_LINSYNCTOE_M                                     0x00010000U
#define UARTLIN_MIS_LINSYNCTOE_S                                     16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICR
    Offset name:         UARTLIN_O_ICR
    Relative address:    0x44
    Description:         Interrupt Clear
                        On a write of 1, the corresponding interrupt is cleared. A write of 0 has no effect.
    Default Value:       0x00000000

        Field:           CTSM
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear to Send (CTS) modem interrupt clear:
                         Writing 1 to this field clears the clear to send interrupt ([RIS.CTSRMIS]). Writing 0 has no effect.

*/
#define UARTLIN_ICR_CTSM                                             0x00000002U
#define UARTLIN_ICR_CTSM_M                                           0x00000002U
#define UARTLIN_ICR_CTSM_S                                           1U
/*

        Field:           RX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Receive interrupt clear:
                         Writing 1 to this field clears the receive interrupt ([RIS.RXRIS]). Writing 0 has no effect.

*/
#define UARTLIN_ICR_RX                                               0x00000010U
#define UARTLIN_ICR_RX_M                                             0x00000010U
#define UARTLIN_ICR_RX_S                                             4U
/*

        Field:           TX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Transmit interrupt clear:
                         Writing 1 to this field clears the transmit interrupt ([RIS.TXRIS]). Writing 0 has no effect.

*/
#define UARTLIN_ICR_TX                                               0x00000020U
#define UARTLIN_ICR_TX_M                                             0x00000020U
#define UARTLIN_ICR_TX_S                                             5U
/*

        Field:           RT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Receive timeout interrupt clear:
                         Writing 1 to this field clears the receive timeout interrupt ([RIS.RTRIS]). Writing 0 has no effect.

*/
#define UARTLIN_ICR_RT                                               0x00000040U
#define UARTLIN_ICR_RT_M                                             0x00000040U
#define UARTLIN_ICR_RT_S                                             6U
/*

        Field:           FE
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Framing error interrupt clear:
                         Writing 1 to this field clears the framing error interrupt ([RIS.FERIS]). Writing 0 has no effect.

*/
#define UARTLIN_ICR_FE                                               0x00000080U
#define UARTLIN_ICR_FE_M                                             0x00000080U
#define UARTLIN_ICR_FE_S                                             7U
/*

        Field:           PE
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Parity error interrupt clear:
                         Writing 1 to this field clears the parity error interrupt ([RIS.PERIS]). Writing 0 has no effect.

*/
#define UARTLIN_ICR_PE                                               0x00000100U
#define UARTLIN_ICR_PE_M                                             0x00000100U
#define UARTLIN_ICR_PE_S                                             8U
/*

        Field:           BE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Break error interrupt clear:
                         Writing 1 to this field clears the break error interrupt ([RIS.BERIS]). Writing 0 has no effect.

*/
#define UARTLIN_ICR_BE                                               0x00000200U
#define UARTLIN_ICR_BE_M                                             0x00000200U
#define UARTLIN_ICR_BE_S                                             9U
/*

        Field:           OE
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Overrun error interrupt clear:
                         Writing 1 to this field clears the overrun error interrupt ([RIS.OERIS]). Writing 0 has no effect.

*/
#define UARTLIN_ICR_OE                                               0x00000400U
#define UARTLIN_ICR_OE_M                                             0x00000400U
#define UARTLIN_ICR_OE_S                                             10U
/*

        Field:           EOT
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     End of Transmission interrupt clear:
                         Writing 1 to this field clears the End of Transmission interrupt (RIS.EOTRIS). Writing 0 has no effect.

*/
#define UARTLIN_ICR_EOT                                              0x00000800U
#define UARTLIN_ICR_EOT_M                                            0x00000800U
#define UARTLIN_ICR_EOT_S                                            11U
/*

        Field:           TXDMADONE
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Tx DMA Done interrupt clear:
                         Writing 1 to this field clears the txdma done interrupt (RIS.TXDMADONERIS). Writing 0 has no effect.

*/
#define UARTLIN_ICR_TXDMADONE                                        0x00001000U
#define UARTLIN_ICR_TXDMADONE_M                                      0x00001000U
#define UARTLIN_ICR_TXDMADONE_S                                      12U
/*

        Field:           RXDMADONE
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Rx DMA Done interrupt clear:
                         Writing 1 to this field clears the rxdma done interrupt (RIS.RXDMADONERIS). Writing 0 has no effect.

*/
#define UARTLIN_ICR_RXDMADONE                                        0x00002000U
#define UARTLIN_ICR_RXDMADONE_M                                      0x00002000U
#define UARTLIN_ICR_RXDMADONE_S                                      13U
/*

        Field:           LINBRK
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     write-only
        Description:     LIN BRK field detected interrupt clear:
                         Writing 1 to this field clears the rxdma done interrupt (RIS.LINBRKRIS). Writing 0 has no effect.

*/
#define UARTLIN_ICR_LINBRK                                           0x00004000U
#define UARTLIN_ICR_LINBRK_M                                         0x00004000U
#define UARTLIN_ICR_LINBRK_S                                         14U
/*

        Field:           LINBRKTOE
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     write-only
        Description:     LIN BRK field timeout interrupt clear:
                         Writing 1 to this field clears the rxdma done interrupt (RIS.LINBRKTOERIS). Writing 0 has no effect.

*/
#define UARTLIN_ICR_LINBRKTOE                                        0x00008000U
#define UARTLIN_ICR_LINBRKTOE_M                                      0x00008000U
#define UARTLIN_ICR_LINBRKTOE_S                                      15U
/*

        Field:           LINSYNCTOE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     LIN SYNC timeout interrupt clear:
                         Writing 1 to this field clears the rxdma done interrupt (RIS.LINSYNCTOERIS). Writing 0 has no effect.

*/
#define UARTLIN_ICR_LINSYNCTOE                                       0x00010000U
#define UARTLIN_ICR_LINSYNCTOE_M                                     0x00010000U
#define UARTLIN_ICR_LINSYNCTOE_S                                     16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMACTL
    Offset name:         UARTLIN_O_DMACTL
    Relative address:    0x48
    Description:         DMA Control
    Default Value:       0x00000000

        Field:           RXDMAE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive **DMA** enable. If this bit is set to 1, **DMA** for the receive **FIFO** is enabled.

*/
#define UARTLIN_DMACTL_RXDMAE                                        0x00000001U
#define UARTLIN_DMACTL_RXDMAE_M                                      0x00000001U
#define UARTLIN_DMACTL_RXDMAE_S                                      0U
/*

        Field:           TXDMAE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit **DMA** enable. If this bit is set to 1, **DMA** for the transmit **FIFO** is enabled.

*/
#define UARTLIN_DMACTL_TXDMAE                                        0x00000002U
#define UARTLIN_DMACTL_TXDMAE_M                                      0x00000002U
#define UARTLIN_DMACTL_TXDMAE_S                                      1U
/*

        Field:           DMAONERR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA on error. If this bit is set to 1, the **DMA** receive request outputs (for  single and burst requests) are disabled when the **UART** error interrupt is asserted (more specifically if any of the error interrupts [RIS.PERIS], [RIS.BERIS], [RIS.FERIS] or [RIS.OERIS] are asserted).

*/
#define UARTLIN_DMACTL_DMAONERR                                      0x00000004U
#define UARTLIN_DMACTL_DMAONERR_M                                    0x00000004U
#define UARTLIN_DMACTL_DMAONERR_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TCR
    Offset name:         UARTLIN_O_TCR
    Relative address:    0x80
    Description:         Test Control
                        NOTE: This register is intended for integration testing and debugging only. In normal usecases, this register should not be used.
    Default Value:       0x00000000

        Field:           ITEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Integration test enable. When this bit is 1, the **UART** is placed in integration test mode, otherwise it is in normal operation.

*/
#define UARTLIN_TCR_ITEN                                             0x00000001U
#define UARTLIN_TCR_ITEN_M                                           0x00000001U
#define UARTLIN_TCR_ITEN_S                                           0U
/*

        Field:           TESTFIFO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Test **FIFO** enable. When this bit it 1, a write to the Test Data Register, [TDR.DATA] writes data into the receive **FIFO**, and a read from the [TDR.DATA] reads data out of the transmit **FIFO**. When this bit is 0, data cannot be read directly from the transmit **FIFO** or written directly to the receive **FIFO** (normal operation).

*/
#define UARTLIN_TCR_TESTFIFO                                         0x00000002U
#define UARTLIN_TCR_TESTFIFO_M                                       0x00000002U
#define UARTLIN_TCR_TESTFIFO_S                                       1U
/*

        Field:           SIRTEST
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SIR test enable. Setting this bit to 1 enables the receive data path during IrDA transmission (SIR
                         full-duplex operation is only available when testing). This bit must be set to 1 to enable SIR system
                         loopback testing, and you must also set the LBE bit to 1 in the Control Register, CTL

*/
#define UARTLIN_TCR_SIRTEST                                          0x00000004U
#define UARTLIN_TCR_SIRTEST_M                                        0x00000004U
#define UARTLIN_TCR_SIRTEST_S                                        2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ITIP
    Offset name:         UARTLIN_O_ITIP
    Relative address:    0x84
    Description:         Integration Test Input
                        NOTE: This register is intended for integration testing and debugging only. In normal usecases, this register should not be used.
    Default Value:       0x00000000

        Field:           UARTRXD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Reads return the value of the **UARTRXD** primary input at PrimeCell PL011 level.

*/
#define UARTLIN_ITIP_UARTRXD                                         0x00000001U
#define UARTLIN_ITIP_UARTRXD_M                                       0x00000001U
#define UARTLIN_ITIP_UARTRXD_S                                       0U
/*

        Field:           NUARTCTS
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Reads return the value of the nUARTCTS primary input at PrimeCell PL011 level.

*/
#define UARTLIN_ITIP_NUARTCTS                                        0x00000008U
#define UARTLIN_ITIP_NUARTCTS_M                                      0x00000008U
#define UARTLIN_ITIP_NUARTCTS_S                                      3U
/*

        Field:           RXDMACLR
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Writes to this bit specify the value to be driven on the intra-chip input at PrimeCell PL011 level,
                         UARTRXDMACLR, in the integration test mode.
                         Reads return the value of UARTRXDMACLR at the output of the test multiplexor.

*/
#define UARTLIN_ITIP_RXDMACLR                                        0x00000040U
#define UARTLIN_ITIP_RXDMACLR_M                                      0x00000040U
#define UARTLIN_ITIP_RXDMACLR_S                                      6U
/*

        Field:           TXDMACLR
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Writes to this bit specify the value to be driven on the intra-chip input at PrimeCell PL011 level,
                         UARTTXDMACLR, in the integration test mode.
                         Reads return the value of UARTTXDMACLR at the output of the test multiplexor.

*/
#define UARTLIN_ITIP_TXDMACLR                                        0x00000080U
#define UARTLIN_ITIP_TXDMACLR_M                                      0x00000080U
#define UARTLIN_ITIP_TXDMACLR_S                                      7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ITOP
    Offset name:         UARTLIN_O_ITOP
    Relative address:    0x88
    Description:         Integration Test Output
    Default Value:       0x00000000

        Field:           UARTTXD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Writes specify the value to be driven on UARTTXD, primary output of PrimeCell PL011 IP.

*/
#define UARTLIN_ITOP_UARTTXD                                         0x00000001U
#define UARTLIN_ITOP_UARTTXD_M                                       0x00000001U
#define UARTLIN_ITOP_UARTTXD_S                                       0U
/*

        Field:           NUARTRTS
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Writes specify the value to be driven on nUARTRTS, primary output of PrimeCell PL011 IP.

*/
#define UARTLIN_ITOP_NUARTRTS                                        0x00000008U
#define UARTLIN_ITOP_NUARTRTS_M                                      0x00000008U
#define UARTLIN_ITOP_NUARTRTS_S                                      3U
/*

        Field:           UARTINTR
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Intra-chip output of PrimeCell PL011 IP. Writes specify the value to be driven on UARTINTR.
                         Reads return the value of UARTINTR at the output of the test multiplexor.

*/
#define UARTLIN_ITOP_UARTINTR                                        0x00000040U
#define UARTLIN_ITOP_UARTINTR_M                                      0x00000040U
#define UARTLIN_ITOP_UARTINTR_S                                      6U
/*

        Field:           RXDMABREQ
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Intra-chip output of PrimeCell PL011 IP. Writes specify the value to be driven on UARTRXDMABREQ.
                         Reads return the value of UARTRXDMABREQ at the output of the test multiplexor.

*/
#define UARTLIN_ITOP_RXDMABREQ                                       0x00001000U
#define UARTLIN_ITOP_RXDMABREQ_M                                     0x00001000U
#define UARTLIN_ITOP_RXDMABREQ_S                                     12U
/*

        Field:           RXDMASREQ
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Intra-chip output of PrimeCell PL011 IP. Writes specify the value to be driven on UARTRXDMASREQ.
                         Reads return the value of UARTRXDMASREQ at the output of the test multiplexor.

*/
#define UARTLIN_ITOP_RXDMASREQ                                       0x00002000U
#define UARTLIN_ITOP_RXDMASREQ_M                                     0x00002000U
#define UARTLIN_ITOP_RXDMASREQ_S                                     13U
/*

        Field:           TXDMABREQ
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Intra-chip output of PrimeCell PL011 IP. Writes specify the value to be driven on UARTTXDMABREQ.
                         Reads return the value of UARTTXDMABREQ at the output of the test multiplexor.

*/
#define UARTLIN_ITOP_TXDMABREQ                                       0x00004000U
#define UARTLIN_ITOP_TXDMABREQ_M                                     0x00004000U
#define UARTLIN_ITOP_TXDMABREQ_S                                     14U
/*

        Field:           TXDMASREQ
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Intra-chip output of PrimeCell PL011 IP. Writes specify the value to be driven on UARTTXDMASREQ.
                         Reads return the value of UARTTXDMASREQ at the output of the test multiplexor.

*/
#define UARTLIN_ITOP_TXDMASREQ                                       0x00008000U
#define UARTLIN_ITOP_TXDMASREQ_M                                     0x00008000U
#define UARTLIN_ITOP_TXDMASREQ_S                                     15U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TDR
    Offset name:         UARTLIN_O_TDR
    Relative address:    0x8C
    Description:         Test Data
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     When the [TCR.TESTFIFO] bit is set to 1, data is written into the receive **FIFO** and read out of the transmit **FIFO**.

*/
#define UARTLIN_TDR_DATA_W                                           11U
#define UARTLIN_TDR_DATA_M                                           0x000007FFU
#define UARTLIN_TDR_DATA_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PERIPHID0
    Offset name:         UARTLIN_O_PERIPHID0
    Relative address:    0xFE0
    Description:         Peripheral Identification 0
    Default Value:       0x00000011

        Field:           PARTNUM0
        From..to bits:   0...7
        DefaultValue:    0x11
        Access type:     read-only
        Description:     Identifies the peripheral

*/
#define UARTLIN_PERIPHID0_PARTNUM0_W                                 8U
#define UARTLIN_PERIPHID0_PARTNUM0_M                                 0x000000FFU
#define UARTLIN_PERIPHID0_PARTNUM0_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PERIPHID1
    Offset name:         UARTLIN_O_PERIPHID1
    Relative address:    0xFE4
    Description:         Peripheral Identification 1
    Default Value:       0x00000000

        Field:           PARTNUM1
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Identifies the peripheral

*/
#define UARTLIN_PERIPHID1_PARTNUM1_W                                 4U
#define UARTLIN_PERIPHID1_PARTNUM1_M                                 0x0000000FU
#define UARTLIN_PERIPHID1_PARTNUM1_S                                 0U
/*

        Field:           DESIGNER0
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Identifies the designer (ARM)

*/
#define UARTLIN_PERIPHID1_DESIGNER0_W                                4U
#define UARTLIN_PERIPHID1_DESIGNER0_M                                0x000000F0U
#define UARTLIN_PERIPHID1_DESIGNER0_S                                4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PERIPHID2
    Offset name:         UARTLIN_O_PERIPHID2
    Relative address:    0xFE8
    Description:         Peripheral Identification 2
    Default Value:       0x00000004

        Field:           DESIGNER1
        From..to bits:   0...3
        DefaultValue:    0x4
        Access type:     read-only
        Description:     Identifies the designer (ARM)

*/
#define UARTLIN_PERIPHID2_DESIGNER1_W                                4U
#define UARTLIN_PERIPHID2_DESIGNER1_M                                0x0000000FU
#define UARTLIN_PERIPHID2_DESIGNER1_S                                0U
/*

        Field:           REVISION
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     UART revision

*/
#define UARTLIN_PERIPHID2_REVISION_W                                 4U
#define UARTLIN_PERIPHID2_REVISION_M                                 0x000000F0U
#define UARTLIN_PERIPHID2_REVISION_S                                 4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PERIPHID3
    Offset name:         UARTLIN_O_PERIPHID3
    Relative address:    0xFEC
    Description:         Peripheral Identification 3
    Default Value:       0x00000000

        Field:           CNF
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The configuration option of the UART.

*/
#define UARTLIN_PERIPHID3_CNF_W                                      8U
#define UARTLIN_PERIPHID3_CNF_M                                      0x000000FFU
#define UARTLIN_PERIPHID3_CNF_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PCELLID0
    Offset name:         UARTLIN_O_PCELLID0
    Relative address:    0xFF0
    Description:         PrimeCell Identification 0
    Default Value:       0x0000000D

        Field:           PCELLID0
        From..to bits:   0...7
        DefaultValue:    0xD
        Access type:     read-only
        Description:     This field is hard coded and reads back as 0x0D

*/
#define UARTLIN_PCELLID0_PCELLID0_W                                  8U
#define UARTLIN_PCELLID0_PCELLID0_M                                  0x000000FFU
#define UARTLIN_PCELLID0_PCELLID0_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PCELLID1
    Offset name:         UARTLIN_O_PCELLID1
    Relative address:    0xFF4
    Description:         PrimeCell Identification 1
    Default Value:       0x000000F0

        Field:           PCELLID1
        From..to bits:   0...7
        DefaultValue:    0xF0
        Access type:     read-only
        Description:     This field is hard coded and reads back as 0xF0

*/
#define UARTLIN_PCELLID1_PCELLID1_W                                  8U
#define UARTLIN_PCELLID1_PCELLID1_M                                  0x000000FFU
#define UARTLIN_PCELLID1_PCELLID1_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PCELLID2
    Offset name:         UARTLIN_O_PCELLID2
    Relative address:    0xFF8
    Description:         PrimeCell Identification 2
    Default Value:       0x00000005

        Field:           PCELLID2
        From..to bits:   0...7
        DefaultValue:    0x5
        Access type:     read-only
        Description:     This field is hard coded and reads back as 0x05

*/
#define UARTLIN_PCELLID2_PCELLID2_W                                  8U
#define UARTLIN_PCELLID2_PCELLID2_M                                  0x000000FFU
#define UARTLIN_PCELLID2_PCELLID2_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PCELLID3
    Offset name:         UARTLIN_O_PCELLID3
    Relative address:    0xFFC
    Description:         PrimeCell Identification 3
    Default Value:       0x000000B1

        Field:           PCELLID3
        From..to bits:   0...7
        DefaultValue:    0xB1
        Access type:     read-only
        Description:     This field is hard coded and reads back as 0xB1

*/
#define UARTLIN_PCELLID3_PCELLID3_W                                  8U
#define UARTLIN_PCELLID3_PCELLID3_M                                  0x000000FFU
#define UARTLIN_PCELLID3_PCELLID3_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         UARTLIN_O_CLKCFG
    Relative address:    0x1000
    Description:         This register enable or disables the bus clock *uartlin*
    Default Value:       NA

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     This bit enable or disables the bus clock *Uartlin*

        ENUMs:
            DIS:                         Disables the clock to *Uartlin*
            EN:                          Enables the clock to *Uartlin*
*/
#define UARTLIN_CLKCFG_EN                                            0x00000001U
#define UARTLIN_CLKCFG_EN_M                                          0x00000001U
#define UARTLIN_CLKCFG_EN_S                                          0U
#define UARTLIN_CLKCFG_EN_DIS                                        0x00000000U
#define UARTLIN_CLKCFG_EN_EN                                         0x00000001U

#endif /* __HW_UARTLIN_H__*/
