/******************************************************************************
 *  Filename:       uart.c
 *
 *  Description:    Driver for the UART peripheral.
 *
 *  Copyright (c) 2022 Texas Instruments Incorporated
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
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
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
 *
 ******************************************************************************/

#include "uart.h"

//*****************************************************************************
//
// Sets the configuration of a UART
//
//*****************************************************************************
void UARTConfigSetExpClk(uint32_t base, uint32_t UARTClkFreq, uint32_t baudFreq, uint32_t config)
{
    uint32_t div;

    // Check the arguments.
    ASSERT(baudFreq != 0);

    // Stop the UART.
    UARTDisable(base);

    // Compute the fractional baud rate divider.
    div = (((UARTClkFreq * 8) / baudFreq) + 1) / 2;

    // Set the baud rate.
    HWREG(base + UART_O_IBRD) = div / 64;
    HWREG(base + UART_O_FBRD) = div % 64;

    // Set parity, data length, and number of stop bits.
    HWREG(base + UART_O_LCRH) = config;
}

//*****************************************************************************
//
// Disables transmitting and receiving
//
//*****************************************************************************
void UARTDisable(uint32_t base)
{
    // Wait for end of TX.
    while (HWREG(base + UART_O_FR) & UART_FR_BUSY) {}

    // Disable the FIFO.
    HWREG(base + UART_O_LCRH) &= ~(UART_LCRH_FEN);

    // Disable the UART.
    HWREG(base + UART_O_CTL) &= ~(UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE);
}

//*****************************************************************************
//
// Blocks until a character is available, and returns it
//
//*****************************************************************************
uint8_t UARTGetChar(uint32_t base)
{
    // Wait until a char is available.
    while (HWREG(base + UART_O_FR) & UART_FR_RXFE) {}

    // Return the character.
    return (HWREG(base + UART_O_DR));
}

//*****************************************************************************
//
// Blocks until there is space in the data register, and writes a byte to it
//
//*****************************************************************************
void UARTPutChar(uint32_t base, uint8_t data)
{
    // Wait until space is available.
    while (HWREG(base + UART_O_FR) & UART_FR_TXFF) {}

    // Send the char.
    HWREG(base + UART_O_DR) = data;
}
