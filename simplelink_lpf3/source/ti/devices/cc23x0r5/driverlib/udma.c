/******************************************************************************
 *  Filename:       udma.c
 *
 *  Description:    Driver for the uDMA controller
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

#include "udma.h"

//*****************************************************************************
//
// Enables attributes of a uDMA channel
//
//*****************************************************************************
void uDMAEnableChannelAttribute(uint32_t channelBitMask, uint32_t attr)
{
    // Check the arguments.
    ASSERT((attr & ~(UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT | UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK)) == 0);

    // Set the useburst bit for this channel if set in attr.
    if (attr & UDMA_ATTR_USEBURST)
    {
        HWREG(DMA_BASE + DMA_O_SETBURST) = channelBitMask;
    }

    // Set the request mask bit for this channel, if set in attr.
    if (attr & UDMA_ATTR_REQMASK)
    {
        HWREG(DMA_BASE + DMA_O_SETREQMASK) = channelBitMask;
    }

    // Set the alternate control select bit for this channel,
    // if set in attr.
    if (attr & UDMA_ATTR_ALTSELECT)
    {
        HWREG(DMA_BASE + DMA_O_SETCHNLPRIALT) = channelBitMask;
    }

    // Set the high priority bit for this channel, if set in attr.
    if (attr & UDMA_ATTR_HIGH_PRIORITY)
    {
        HWREG(DMA_BASE + DMA_O_SETCHNLPRIORITY) = channelBitMask;
    }
}

//*****************************************************************************
//
// Disables attributes of a uDMA channel
//
//*****************************************************************************
void uDMADisableChannelAttribute(uint32_t channelBitMask, uint32_t attr)
{
    // Check the arguments.
    ASSERT((attr & ~(UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT | UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK)) == 0);

    // Clear the useburst bit for this channel if set in attr.
    if (attr & UDMA_ATTR_USEBURST)
    {
        HWREG(DMA_BASE + DMA_O_CLEARBURST) = channelBitMask;
    }

    // Clear the request mask bit for this channel, if set in attr.
    if (attr & UDMA_ATTR_REQMASK)
    {
        HWREG(DMA_BASE + DMA_O_CLEARREQMASK) = channelBitMask;
    }

    // Clear the alternate control select bit for this channel, if set in
    // ululAttr.
    if (attr & UDMA_ATTR_ALTSELECT)
    {
        HWREG(DMA_BASE + DMA_O_CLEARCHNLPRIALT) = channelBitMask;
    }

    // Clear the high priority bit for this channel, if set in attr.
    if (attr & UDMA_ATTR_HIGH_PRIORITY)
    {
        HWREG(DMA_BASE + DMA_O_CLEARCHNLPRIORITY) = channelBitMask;
    }
}

//*****************************************************************************
//
// Gets the enabled attributes of a uDMA channel
//
//*****************************************************************************
uint32_t uDMAGetChannelAttribute(uint32_t channelBitMask)
{
    uint32_t attr = 0;

    // Check to see if useburst bit is set for this channel.
    if (HWREG(DMA_BASE + DMA_O_SETBURST) & (channelBitMask))
    {
        attr |= UDMA_ATTR_USEBURST;
    }

    // Check to see if the alternate control bit is set for this channel.
    if (HWREG(DMA_BASE + DMA_O_SETCHNLPRIALT) & (channelBitMask))
    {
        attr |= UDMA_ATTR_ALTSELECT;
    }

    // Check to see if the high priority bit is set for this channel.
    if (HWREG(DMA_BASE + DMA_O_SETCHNLPRIORITY) & (channelBitMask))
    {
        attr |= UDMA_ATTR_HIGH_PRIORITY;
    }

    // Check to see if the request mask bit is set for this channel.
    if (HWREG(DMA_BASE + DMA_O_SETREQMASK) & (channelBitMask))
    {
        attr |= UDMA_ATTR_REQMASK;
    }

    // Return the configuration flags.
    return (attr);
}

//*****************************************************************************
//
// Sets the control parameters for a uDMA channel control structure
//
//*****************************************************************************
void uDMASetChannelControl(volatile uDMAControlTableEntry *pChannelControlStruct, uint32_t control)
{
    // Check the arguments.
    ASSERT(HWREG(DMA_BASE + DMA_O_CTRL) != 0);

    // Get the current control word value and mask off the fields to be
    // changed, then OR in the new settings.
    pChannelControlStruct->control = ((pChannelControlStruct->control &
                                       ~(UDMA_DST_INC_M | UDMA_SRC_INC_M | UDMA_SIZE_M | UDMA_ARB_M |
                                         UDMA_NEXT_USEBURST)) |
                                      control);
}

//*****************************************************************************
//
// Sets the transfer parameters for a uDMA channel control structure
//
//*****************************************************************************
void uDMASetChannelTransfer(volatile uDMAControlTableEntry *pChannelControlStruct,
                            uint32_t mode,
                            void *pSrcAddr,
                            void *pDstAddr,
                            uint32_t transferSize)
{
    uint32_t controlTableAddr;
    uint32_t control;
    uint32_t incValue;
    uint32_t bufferBytes;
    uint32_t channelStructIndex;

    // Check the arguments.
    ASSERT(HWREG(DMA_BASE + DMA_O_CTRL) != 0);
    ASSERT(mode <= UDMA_MODE_PER_SCATTER_GATHER);
    ASSERT((transferSize != 0) && (transferSize <= UDMA_XFER_SIZE_MAX));

    // Get the base address of the control table.
    controlTableAddr = HWREG(DMA_BASE + DMA_O_CTRL);

    // Get the current control word value and mask off the mode and size
    // fields.
    control = (pChannelControlStruct->control & ~(UDMA_XFER_SIZE_M | UDMA_MODE_M));

    // Evaluate if the received table is a primary or alternate control table.
    // To do this, calculate the index of the received control table among the
    // entire control table array. This is the offset between the received table
    // and the base address of the control table, divided by the size of the single
    // control table block (16B).
    channelStructIndex = (((uint32_t)pChannelControlStruct) - controlTableAddr) >> 4;

    // Adjust the mode if the alt control structure is selected.
    if (channelStructIndex & UDMA_ALT_SELECT)
    {
        if ((mode == UDMA_MODE_MEM_SCATTER_GATHER) || (mode == UDMA_MODE_PER_SCATTER_GATHER))
        {
            mode |= UDMA_MODE_ALT_SELECT;
        }
    }

    // Set the transfer size and mode in the control word (but don't write the
    // control word yet as it could kick off a transfer).
    control |= mode | ((transferSize - 1) << UDMA_XFER_SIZE_S);

    // Get the address increment value for the source, from the control word.
    incValue = (control & UDMA_SRC_INC_M);

    // Compute the ending source address of the transfer.  If the source
    // increment is set to none, then the ending address is the same as the
    // beginning.
    if (incValue != UDMA_SRC_INC_NONE)
    {
        incValue    = incValue >> UDMA_SRC_INC_S;
        bufferBytes = transferSize << incValue;
        pSrcAddr    = (void *)((uint32_t)pSrcAddr + bufferBytes - (1 << incValue));
    }

    // Load the source ending address into the control block.
    pChannelControlStruct->pSrcEndAddr = pSrcAddr;

    // Get the address increment value for the destination, from the control
    // word.
    incValue = control & UDMA_DST_INC_M;

    // Compute the ending destination address of the transfer.  If the
    // destination increment is set to none, then the ending address is the
    // same as the beginning.
    if (incValue != UDMA_DST_INC_NONE)
    {
        // There is a special case if this is setting up a scatter-gather
        // transfer.  The destination pointer needs to point to the end of
        // the alternate structure for this channel instead of calculating
        // the end of the buffer in the normal way.
        if ((mode == UDMA_MODE_MEM_SCATTER_GATHER) || (mode == UDMA_MODE_PER_SCATTER_GATHER))
        {
            if (channelStructIndex & UDMA_ALT_SELECT)
            {
                pDstAddr = (void *)&(pChannelControlStruct->spare);
            }
            else
            {
                pDstAddr = (void *)&pChannelControlStruct[UDMA_ALT_SELECT].spare;
            }
        }
        // Not a scatter-gather transfer, calculate end pointer normally.
        else
        {
            incValue    = incValue >> UDMA_DST_INC_S;
            bufferBytes = transferSize << incValue;
            pDstAddr    = (void *)((uint32_t)pDstAddr + bufferBytes - 1);
        }
    }

    // Load the destination ending address into the control block.
    pChannelControlStruct->pDstEndAddr = pDstAddr;

    // Write the new control word value.
    pChannelControlStruct->control = control;
}

//*****************************************************************************
//
// Gets the current transfer size for a uDMA channel control structure
//
//*****************************************************************************
uint32_t uDMAGetChannelSize(volatile uDMAControlTableEntry const *pChannelControlStruct)
{
    uint32_t control;

    // Check the arguments.
    ASSERT(HWREG(DMA_BASE + DMA_O_CTRL) != 0);

    // Get the current control word value and mask off all but the size field
    // and the mode field.
    control = (pChannelControlStruct->control & (UDMA_XFER_SIZE_M | UDMA_MODE_M));

    // If the size field and mode field are 0 then the transfer is finished
    // and there are no more items to transfer.
    if (control == 0)
    {
        return (0);
    }

    // Otherwise, if either the size field or more field is non-zero, then
    // not all the items have been transferred.
    else
    {
        // Shift the size field and add one, then return to user.
        return ((control >> UDMA_XFER_SIZE_S) + 1);
    }
}

//*****************************************************************************
//
// Gets the transfer mode for a uDMA channel control structure
//
//*****************************************************************************
uint32_t uDMAGetChannelMode(volatile uDMAControlTableEntry const *pChannelControlStruct)
{
    uint32_t control;

    // Check the arguments.
    ASSERT(HWREG(DMA_BASE + DMA_O_CTRL) != 0);

    // Get the current control word value and mask off all but the mode field.
    control = (pChannelControlStruct->control & UDMA_MODE_M);

    // Check if scatter/gather mode, and if so, mask off the alt bit.
    if (((control & ~UDMA_MODE_ALT_SELECT) == UDMA_MODE_MEM_SCATTER_GATHER) ||
        ((control & ~UDMA_MODE_ALT_SELECT) == UDMA_MODE_PER_SCATTER_GATHER))
    {
        control &= ~UDMA_MODE_ALT_SELECT;
    }

    // Return the mode to the caller.
    return (control);
}
