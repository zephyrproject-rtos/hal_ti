/******************************************************************************
 *  Filename:       dma.c
 *
 *  Description:    Driver for the peripheral DMA controller
 *
 *  Copyright (c) 2022-2026 Texas Instruments Incorporated
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

#include "dma.h"

// Max supported transfer length per transaction, in number of bytes
#define DMA_MAX_TRANSACTION_BYTES HOST_DMA_CH0TCTL_TRANSB_M
// Smallest supported block size, in number of words
#define DMA_BLOCK_SIZE_MIN        1
// Largest supported block size, in number of words
#define DMA_BLOCK_SIZE_MAX        63

//*****************************************************************************
//
// Link DMA channel to peripheral port
//
//*****************************************************************************
void DMAInitChannel(uint32_t channel, DMAPeripheral peripheral)
{
    uint32_t regOffset;
    uint32_t shiftValue;
    uint32_t configReg;

    // Check the arguments
    ASSERT(channel < DMA_NUM_CHANNELS);
    ASSERT(peripheral < DMA_NUM_PERIPHS);

    // Calculate register offset (0/4) based on the channel number
    regOffset = (channel / DMA_CHCTRL_NUMBER_OF_FIELDS) * sizeof(uint32_t);

    // Calculate bitfield position based on the channel number
    shiftValue = (channel % DMA_CHCTRL_NUMBER_OF_FIELDS) * DMA_CHCTL_FIELD_WIDTH;

    // Read register containing channel configuration
    configReg = HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CHCTL0 + regOffset);

    // Clear channel configuration
    configReg &= ~(HOST_DMA_CHCTL0_CH0_M << shiftValue);

    // Set new channel configuration
    configReg |= (peripheral << shiftValue);

    // Write back, to register, this links channel to peripheral
    HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CHCTL0 + regOffset) = configReg;
}

//*****************************************************************************
//
// Configure the specified channel
//
//*****************************************************************************
void DMAConfigureChannel(uint32_t channel, uint8_t blockSize, uint8_t wordSize, uint32_t config)
{
    // Check arguments
    ASSERT(channel < DMA_NUM_CHANNELS);
    ASSERT((blockSize >= DMA_BLOCK_SIZE_MIN) && (blockSize <= DMA_BLOCK_SIZE_MAX));
    // Check allowed flags and not allowed flags
    ASSERT((~(DMA_CONFIG_ALLOWED_MASK)&config) == 0);

    uint32_t regOffset = channel * DMA_CH_OFFSET;
    uint32_t configReg = config;

    // Incorporate block size and word size into the configuration value
    configReg |= (blockSize << HOST_DMA_CH0JCTL_BLKSIZE_S) & HOST_DMA_CH0JCTL_BLKSIZE_M;
    configReg |= (wordSize << HOST_DMA_CH0JCTL_WORDSIZE_S) & HOST_DMA_CH0JCTL_WORDSIZE_M;

    // Write configuration to hardware
    HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0JCTL + regOffset) = configReg;
}

//*****************************************************************************
//
// Start a DMA transaction
//
//*****************************************************************************
void DMAStartTransaction(uint32_t channel,
                         const uint32_t *srcStartAddr,
                         uint32_t *dstStartAddr,
                         uint16_t transLenByte,
                         bool remainingBytesBurst)
{
    // Check the arguments.
    ASSERT(channel < DMA_NUM_CHANNELS);
    ASSERT(transLenByte <= DMA_MAX_TRANSACTION_BYTES);

    uint32_t chOffset = channel * DMA_CH_OFFSET;
    uint32_t ctrlReg  = (transLenByte << HOST_DMA_CH0TCTL_TRANSB_S) & HOST_DMA_CH0TCTL_TRANSB_M;

    if (remainingBytesBurst)
    {
        // Set force burst request
        ctrlReg |= HOST_DMA_CH0TCTL_BURSTREQ;
    }

    // Write control register
    HWREG(HOST_DMA_TGT_BASE + chOffset + HOST_DMA_O_CH0TCTL) = ctrlReg;

    // Set destination address
    HWREG(HOST_DMA_TGT_BASE + chOffset + HOST_DMA_O_CH0OPTR) = ((uint32_t)dstStartAddr << HOST_DMA_CH0OPTR_OPTR_S) &
                                                               HOST_DMA_CH0OPTR_OPTR_M;

    // Set source address
    HWREG(HOST_DMA_TGT_BASE + chOffset + HOST_DMA_O_CH0TIPTR) = ((uint32_t)srcStartAddr << HOST_DMA_CH0TIPTR_IPTR_S) &
                                                                HOST_DMA_CH0TIPTR_IPTR_M;

    // Adjust register offset for channel 7.
    // TODO: Adjustment might need to be removed for PG2.0
    if (channel == 7)
    {
        chOffset += 0x20;
    }

    // Start transaction
    HWREG(HOST_DMA_TGT_BASE + chOffset + HOST_DMA_O_CH0TCTL2) = (DMA_CMD_RUN << HOST_DMA_CH0TCTL2_CMD_S) &
                                                                HOST_DMA_CH0TCTL2_CMD_M;
}

//*****************************************************************************
//
// Get channel status
//
//*****************************************************************************
uint32_t DMAGetChannelStatus(uint32_t channel)
{
    uint32_t chStatus;

    // Check argument
    ASSERT(channel < DMA_NUM_CHANNELS);

    chStatus = (HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0STA + (channel * DMA_CH_OFFSET)) & HOST_DMA_CH0STA_HWEVENT_M) >>
                HOST_DMA_CH0STA_HWEVENT_S;

    return chStatus;
}

//*****************************************************************************
//
// Get channel FSM Status
//
//*****************************************************************************
DMAChannelFsmState DMAGetChannelFSMState(uint32_t channel)
{
    uint32_t fsmStatus;

    // Check argument
    ASSERT(channel < DMA_NUM_CHANNELS);

    fsmStatus = (HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0STA + (channel * DMA_CH_OFFSET)) & HOST_DMA_CH0STA_FSMSTATE_M);

    return fsmStatus;
}

//*****************************************************************************
//
// Get channel direction
//
//*****************************************************************************
uint32_t DMAGetChannelDirection(uint32_t channel)
{
    uint32_t chDirection;

    // Check argument
    ASSERT(channel < DMA_NUM_CHANNELS);

    chDirection = HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0JCTL + (channel * DMA_CH_OFFSET)) &
                        HOST_DMA_CH0JCTL_SRCDSTCFG_M;

    return chDirection;
}
