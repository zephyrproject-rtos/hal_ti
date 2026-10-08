/******************************************************************************
 *  Filename:       uart.c
 *
 *  Description:    Driver for the UART peripheral.
 *
 *  Copyright (c) 2022-2025 Texas Instruments Incorporated
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
// Control UART bus clock
//
//*****************************************************************************
void UARTClockCtrl(uint32_t base, bool clkEnable)
{
    if (clkEnable)
    {
        // Enable UART bus clock
        HWREG(base + UARTLIN_O_CLKCFG) = UARTLIN_CLKCFG_EN;
    }
    else
    {
        // Disable UART bus clock
        HWREG(base + UARTLIN_O_CLKCFG) = 0;
    }
}

//*****************************************************************************
//
// Enable UART
//
//*****************************************************************************
void UARTEnable(uint32_t base)
{
    // Check the arguments.
    ASSERT((base == UARTLIN0_BASE) || (base == UARTLIN1_BASE) || (base == UARTLIN2_BASE))

    // Enable the FIFO.
    UARTEnableFifo(base);

    // Enable the UART.
    HWREG(base + UARTLIN_O_CTL) |= (UARTLIN_CTL_UARTEN | UARTLIN_CTL_TXE | UARTLIN_CTL_RXE);
}

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

    // Compute the fractional baud rate divider.
    div = (((UARTClkFreq * 8) / baudFreq) + 1) / 2;

    // Set the baud rate.
    HWREG(base + UARTLIN_O_IBRD) = div / 64;
    HWREG(base + UARTLIN_O_FBRD) = div % 64;

    // Set parity, data length, and number of stop bits.
    HWREG(base + UARTLIN_O_LCRH) = config;
}

//*****************************************************************************
//
// Disables transmitting and receiving
//
//*****************************************************************************
void UARTDisable(uint32_t base)
{
    // Wait for end of TX.
    while (HWREG(base + UARTLIN_O_FR) & UARTLIN_FR_BUSY) {}

    // Disable the FIFO.
    HWREG(base + UARTLIN_O_LCRH) &= ~(UARTLIN_LCRH_FEN);

    // Disable the UART.
    HWREG(base + UARTLIN_O_CTL) &= ~(UARTLIN_CTL_UARTEN | UARTLIN_CTL_TXE | UARTLIN_CTL_RXE);
}

//*****************************************************************************
//
// Blocks until a character is available, and returns it
//
//*****************************************************************************
uint8_t UARTGetChar(uint32_t base)
{
    // Wait until a char is available.
    while (HWREG(base + UARTLIN_O_FR) & UARTLIN_FR_RXFE) {}

    // Return the character.
    return UARTGetCharNonBlocking(base);
}

//*****************************************************************************
//
// Blocks until there is space in the data register, and writes a byte to it
//
//*****************************************************************************
void UARTPutChar(uint32_t base, uint8_t data)
{
    // Wait until space is available.
    while (HWREG(base + UARTLIN_O_FR) & UARTLIN_FR_TXFF) {}

    // Send the char.
    UARTPutCharNonBlocking(base, data);
}
