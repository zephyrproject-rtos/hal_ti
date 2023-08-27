/******************************************************************************
 *  Filename:       spi.c
 *
 *  Description:    Driver for the Serial Peripheral Interface (SPI).
 *
 *  Copyright (c) 2023 Texas Instruments Incorporated
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

#include "spi.h"

// DSAMPLE default value limits based bit rate
#define DSAMPLE_MED_BITRATE  4000000U
#define DSAMPLE_HIGH_BITRATE 8000000U

// Maximum serial clock divider value
#define SCR_MAXIMUM 0x000003FFU

//*****************************************************************************
//
// Configures the serial peripheral port
//
//*****************************************************************************
static void SPIConfig(uint32_t baseAddr,
                      uint32_t freq,
                      uint32_t format,
                      uint32_t mode,
                      uint32_t bitRate,
                      uint32_t dataSize,
                      uint32_t dsample)
{
    uint16_t scr;
    uint32_t ratio;

    // Get existing settings
    uint32_t reg  = HWREG(baseAddr + SPI_O_CTL0);
    // Create mask for settings to modify
    uint32_t mask = (SPI_CTL0_DSS_M | SPI_CTL0_FRF_M | SPI_CTL0_SPO_M | SPI_CTL0_SPH_M);

    // Convert and mask data size to HW register format
    dataSize = (SPI_CTL0_DSS_M & (dataSize - 1));

    // Apply updated register
    HWREG(baseAddr + SPI_O_CTL0) = (reg & ~mask) | format | dataSize;

    // Set controller/peripheral mode and MSB first for shift reg
    HWREG(baseAddr + SPI_O_CTL1) = mode | SPI_CTL1_MSB_MSB;

    // Get existing settings
    reg = HWREG(baseAddr + SPI_O_CLKCFG1);

    // Create a mask for settings to modify
    mask = (SPI_CLKCFG1_DSAMPLE_M | SPI_CLKCFG1_SCR_M);

    // Calculate scr variable
    ratio = freq / (2U * bitRate);
    if ((ratio > 0U) && (ratio <= SCR_MAXIMUM))
    {
        scr = (uint16_t)(ratio - 1U);
    }
    else
    {
        scr = 0U;
    }

    // Set clock divider
    HWREG(baseAddr + SPI_O_CLKCFG1) = (reg & ~mask) | dsample | scr;
}

void SPIConfigSetExpClk(uint32_t base,
                        uint32_t spiClk,
                        uint32_t protocol,
                        uint32_t mode,
                        uint32_t bitRate,
                        uint32_t dataWidth)
{
    uint32_t dsample = 0U;

    ASSERT(SPIBaseValid(base));

    if (bitRate >= DSAMPLE_MED_BITRATE)
    {
        dsample = 1U << SPI_CLKCFG1_DSAMPLE_S;
    }
    else if (bitRate >= DSAMPLE_HIGH_BITRATE)
    {
        dsample = 2U << SPI_CLKCFG1_DSAMPLE_S;
    }

    SPIConfig(base, spiClk, protocol, mode, bitRate, dataWidth, dsample);
}

//*****************************************************************************
//
// Puts a data element into the SPI transmit FIFO
//
//*****************************************************************************
int32_t SPIPutDataNonBlocking(uint32_t base, uint32_t data)
{
    ASSERT(SPIBaseValid(base));

    // Check for space to write.
    if (HWREG(base + SPI_O_STA) & SPI_STA_TNF_NOT_FULL)
    {
        // Write the data to the SPI TX FIFO.
        HWREG(base + SPI_O_TXDATA) = data;
        return (1);
    }
    else
    {
        return (0);
    }
}

//*****************************************************************************
//
// Puts a data element into the SPI transmit FIFO
//
//*****************************************************************************
void SPIPutData(uint32_t base, uint32_t data)
{
    ASSERT(SPIBaseValid(base));

    // Check for space to write.
    while (!(HWREG(base + SPI_O_STA) & SPI_STA_TNF_NOT_FULL)) {}

    // Write the data to the SPI TX FIFO.
    HWREG(base + SPI_O_TXDATA) = data;
}

//*****************************************************************************
//
// Gets a data element from the SPI receive FIFO
//
//*****************************************************************************
void SPIGetData(uint32_t base, uint32_t *data)
{
    ASSERT(SPIBaseValid(base));

    // Wait until there is data to be read.
    while (HWREG(base + SPI_O_STA) & SPI_STA_RFE_EMPTY) {}

    // Read data from SPI RX FIFO.
    *data = HWREG(base + SPI_O_RXDATA);
}

//*****************************************************************************
//
// Gets a data element from the SPI receive FIFO
//
//*****************************************************************************
int32_t SPIGetDataNonBlocking(uint32_t base, uint32_t *data)
{
    // Check the arguments
    ASSERT(SPIBaseValid(base));

    // Check for data to read
    if (!(HWREG(base + SPI_O_STA) & SPI_STA_RFE_EMPTY))
    {
        *data = HWREG(base + SPI_O_RXDATA);
        return (1);
    }
    else
    {
        return (0);
    }
}

//*****************************************************************************
//
// Registers an interrupt handler for the serial peripheral port
//
//*****************************************************************************
void SPIRegisterInt(uint32_t base, void (*pfnHandler)(void))
{
    // Check the arguments
    ASSERT(SPIBaseValid(base));

    // Register the interrupt handler
    IntRegister((uint32_t)INT_SPI0_COMB, pfnHandler);

    // Enable the synchronous serial port interrupt
    IntEnable((uint32_t)INT_SPI0_COMB);
}

//*****************************************************************************
//
// Unregisters an interrupt handler for the serial peripheral port
//
//*****************************************************************************
void SPIUnregisterInt(uint32_t base)
{
    // Check the arguments
    ASSERT(SPIBaseValid(base));

    // Disable the interrupt
    IntDisable((uint32_t)INT_SPI0_COMB);

    // Unregister the interrupt handler
    IntUnregister((uint32_t)INT_SPI0_COMB);
}
