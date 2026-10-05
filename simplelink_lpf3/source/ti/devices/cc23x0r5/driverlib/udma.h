/******************************************************************************
 *  Filename:       udma.h
 *
 *  Description:    Defines and prototypes for the uDMA controller.
 *
 *  Copyright (c) 2022-2024 Texas Instruments Incorporated
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

#ifndef __UDMA_H__
#define __UDMA_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup udma_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "../inc/hw_types.h"
#include "../inc/hw_ints.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_dma.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
//! \brief A structure that defines an entry in the channel control table.
//!
//! These fields are used by the uDMA controller and normally it is not necessary for
//! software to directly read or write fields in the table.
//
//*****************************************************************************
typedef struct
{
    volatile void *pSrcEndAddr; //!< The ending source address of the data transfer.
    volatile void *pDstEndAddr; //!< The ending destination address of the data transfer.
    volatile uint32_t control;  //!< The channel control mode.
    volatile uint32_t spare;    //!< An unused location.
} uDMAControlTableEntry;

//*****************************************************************************
//
//! \brief A helper macro for building scatter-gather task table entries.
//!
//! This macro is intended to be used to help populate a table of uDMA tasks
//! for a scatter-gather transfer. This macro will calculate the values for
//! the fields of a task structure entry based on the input parameters.
//!
//! There are specific requirements for the values of each parameter.  No
//! checking is done so it is up to the caller to ensure that correct values
//! are used for the parameters.
//!
//! This macro is intended to be used to initialize individual entries of
//! a structure of uDMAControlTableEntry type, like this:
//!
/*!
\verbatim
  uDMAControlTableEntry MyTaskList[] =
  {
      uDMATaskStructEntry(Task1Count, UDMA_SIZE_8,
                          UDMA_SRC_INC_8, MySourceBuf,
                          UDMA_DST_INC_8, MyDestBuf,
                          UDMA_ARB_8, UDMA_MODE_MEM_SCATTER_GATHER),
      uDMATaskStructEntry(Task2Count, ... ),
  }
\endverbatim
*/
//! \param transferCount is the count of items to transfer for this task.
//! It must be in the range 1-1024.
//! \param itemSize is the bit size of the items to transfer for this task.
//! It must be one of:
//! - \ref UDMA_SIZE_8
//! - \ref UDMA_SIZE_16
//! - \ref UDMA_SIZE_32
//! \param srcIncrement is the bit size increment for source data.
//! It must be one of:
//! - \ref UDMA_SRC_INC_8
//! - \ref UDMA_SRC_INC_16
//! - \ref UDMA_SRC_INC_32
//! - \ref UDMA_SRC_INC_NONE
//! \param pSrcAddr is the starting address of the data to transfer.
//! \param dstIncrement is the bit size increment for destination data.
//! It must be one of:
//! - \ref UDMA_DST_INC_8
//! - \ref UDMA_DST_INC_16
//! - \ref UDMA_DST_INC_32
//! - \ref UDMA_DST_INC_NONE
//! \param pDstAddr is the starting address of the destination data.
//! \param arbSize is the arbitration size to use for the transfer task.
//! This is used to select the arbitration size in powers of 2, from 1 to 1024.
//! It must be one of:
//! - \ref UDMA_ARB_1
//! - \ref UDMA_ARB_2
//! - \ref UDMA_ARB_4
//! - ...
//! - \ref UDMA_ARB_1024
//! \param mode is the transfer mode for this task.
//! Note that normally all tasks will be one of the scatter-gather modes while the
//! last task is a task list will be AUTO or BASIC.
//! It must be one of:
//! - \ref UDMA_MODE_BASIC
//! - \ref UDMA_MODE_AUTO
//! - \ref UDMA_MODE_MEM_SCATTER_GATHER
//! - \ref UDMA_MODE_PER_SCATTER_GATHER
//!
//! \return None (this is not a function)
//
//*****************************************************************************
#define uDMATaskStructEntry(transferCount, itemSize, srcIncrement, pSrcAddr, dstIncrement, pDstAddr, arbSize, mode) \
    {                                                                                                               \
        (((srcIncrement) == UDMA_SRC_INC_NONE)                                                                      \
             ? (pSrcAddr)                                                                                           \
             : ((void *)(&((uint8_t *)(pSrcAddr))[((transferCount) << ((srcIncrement) >> 26)) - 1]))),              \
            (((dstIncrement) == UDMA_DST_INC_NONE)                                                                  \
                 ? (pDstAddr)                                                                                       \
                 : ((void *)(&((uint8_t *)(pDstAddr))[((transferCount) << ((dstIncrement) >> 30)) - 1]))),          \
            (srcIncrement) | (dstIncrement) | (itemSize) | (arbSize) | (((transferCount)-1) << 4) |                 \
                ((((mode) == UDMA_MODE_MEM_SCATTER_GATHER) || ((mode) == UDMA_MODE_PER_SCATTER_GATHER))             \
                     ? (mode) | UDMA_MODE_ALT_SELECT                                                                \
                     : (mode)),                                                                                     \
            0                                                                                                       \
    }

//*****************************************************************************
//
// The hardware configured number of uDMA channels.
//
//*****************************************************************************
#define UDMA_NUM_CHANNELS 8

//*****************************************************************************
//
// The level of priority for the uDMA channels
//
//*****************************************************************************
#define UDMA_PRIORITY_LOW  0x00000000
#define UDMA_PRIORITY_HIGH 0x00000001

//*****************************************************************************
//
// Flags that can be passed to uDMAEnableChannelAttribute(),
// uDMADisableChannelAttribute(), and returned from uDMAGetChannelAttribute().
//
//*****************************************************************************
#define UDMA_ATTR_USEBURST      0x00000001
#define UDMA_ATTR_ALTSELECT     0x00000002
#define UDMA_ATTR_HIGH_PRIORITY 0x00000004
#define UDMA_ATTR_REQMASK       0x00000008
#define UDMA_ATTR_ALL           0x0000000F

//*****************************************************************************
//
// DMA control modes that can be passed to uDMASetChannelTransfer() and returned
// from uDMAGetChannelMode().
//
//*****************************************************************************
#define UDMA_MODE_STOP               0x00000000
#define UDMA_MODE_BASIC              0x00000001
#define UDMA_MODE_AUTO               0x00000002
#define UDMA_MODE_PINGPONG           0x00000003
#define UDMA_MODE_MEM_SCATTER_GATHER 0x00000004
#define UDMA_MODE_PER_SCATTER_GATHER 0x00000006
#define UDMA_MODE_M                  0x00000007 // uDMA Transfer Mode
#define UDMA_MODE_ALT_SELECT         0x00000001

//*****************************************************************************
//
// Channel configuration values that can be passed to uDMASetChannelControl().
//
//*****************************************************************************
#define UDMA_DST_INC_8     0x00000000
#define UDMA_DST_INC_16    0x40000000
#define UDMA_DST_INC_32    0x80000000
#define UDMA_DST_INC_NONE  0xC0000000
#define UDMA_DST_INC_M     0xC0000000 // Destination Address Increment
#define UDMA_DST_INC_S     30
#define UDMA_SRC_INC_8     0x00000000
#define UDMA_SRC_INC_16    0x04000000
#define UDMA_SRC_INC_32    0x08000000
#define UDMA_SRC_INC_NONE  0x0c000000
#define UDMA_SRC_INC_M     0x0C000000 // Source Address Increment
#define UDMA_SRC_INC_S     26
#define UDMA_SIZE_8        0x00000000
#define UDMA_SIZE_16       0x11000000
#define UDMA_SIZE_32       0x22000000
#define UDMA_SIZE_M        0x33000000 // Data Size
#define UDMA_SIZE_S        24
#define UDMA_ARB_1         0x00000000
#define UDMA_ARB_2         0x00004000
#define UDMA_ARB_4         0x00008000
#define UDMA_ARB_8         0x0000c000
#define UDMA_ARB_16        0x00010000
#define UDMA_ARB_32        0x00014000
#define UDMA_ARB_64        0x00018000
#define UDMA_ARB_128       0x0001c000
#define UDMA_ARB_256       0x00020000
#define UDMA_ARB_512       0x00024000
#define UDMA_ARB_1024      0x00028000
#define UDMA_ARB_M         0x0003C000 // Arbitration Size
#define UDMA_ARB_S         14
#define UDMA_NEXT_USEBURST 0x00000008
#define UDMA_XFER_SIZE_MAX 1024
#define UDMA_XFER_SIZE_M   0x00003FF0 // Transfer size
#define UDMA_XFER_SIZE_S   4

//*****************************************************************************
//
// Channel numbers to be passed to API functions that require a channel number
// ID. On CC23x0 each uDMA channel is multiplexed between one or two different
// peripherals. The 1-to-1 mapping between UDMA channel and peripheral must be
// decided by the user and set in the event fabric registers EVTSVT.DMACH[x]SEL.
// The two valid peripherals for each channel are listed next to each channel's
// mask definition.
//
//*****************************************************************************
#define UDMA_CHANNEL_0_M 0x01 //!< UDMA channel 0 (SPI0_TX or UART0_RX)
#define UDMA_CHANNEL_1_M 0x02 //!< UDMA channel 1 (SPI0_RX or UART0_TX)
#define UDMA_CHANNEL_2_M 0x04 //!< UDMA channel 2 (UART0_TX)
#define UDMA_CHANNEL_3_M 0x08 //!< UDMA channel 3 (ADC0 or UART0_RX)
#define UDMA_CHANNEL_4_M 0x10 //!< UDMA channel 4 (AES_A)
#define UDMA_CHANNEL_5_M 0x20 //!< UDMA channel 5 (AES_B or ADC0)
#define UDMA_CHANNEL_6_M 0x40 //!< UDMA channel 6 (Software Event Channel 0)
#define UDMA_CHANNEL_7_M 0x80 //!< UDMA channel 7 (Software Event Channel 1)

//*****************************************************************************
//
// Flags to be OR'd with the channel ID to indicate if the primary or alternate
// control structure should be used.
//
//*****************************************************************************
#define UDMA_PRI_SELECT 0x00000000
#define UDMA_ALT_SELECT 0x00000008

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Enables the uDMA controller for use.
//!
//! This function enables the uDMA controller. The uDMA controller must be
//! enabled before it can be configured and used.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void uDMAEnable(void)
{
    // Set the master enable bit in the config register.
    HWREG(DMA_BASE + DMA_O_CFG) = DMA_CFG_MASTERENABLE;
}

//*****************************************************************************
//
//! \brief Disables the uDMA controller for use.
//!
//! This function disables the uDMA controller.  Once disabled, the uDMA
//! controller will not operate until re-enabled with \ref uDMAEnable().
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void uDMADisable(void)
{
    // Clear the master enable bit in the config register.
    HWREG(DMA_BASE + DMA_O_CFG) = 0;
}

//*****************************************************************************
//
//! \brief Gets the uDMA error status.
//!
//! This function returns the uDMA error status. It should be called from
//! within the uDMA error interrupt handler to determine if a uDMA error
//! occurred.
//!
//! \return Returns non-zero if a uDMA error is pending.
//
//*****************************************************************************
__STATIC_INLINE uint32_t uDMAGetErrorStatus(void)
{
    // Return the uDMA error status.
    return (HWREG(DMA_BASE + DMA_O_ERROR));
}

//*****************************************************************************
//
//! \brief Clears the uDMA error interrupt.
//!
//! This function clears a pending uDMA error interrupt. It should be called
//! from within the uDMA error interrupt handler to clear the interrupt.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void uDMAClearErrorStatus(void)
{
    // Clear the uDMA error interrupt.
    HWREG(DMA_BASE + DMA_O_ERROR) = DMA_ERROR_STATUS;
}

//*****************************************************************************
//
//! \brief Enables a uDMA channel for operation.
//!
//! This function enables the specified uDMA channels for use. This function must
//! be used to enable a channel before it can be used to perform a uDMA
//! transfer.
//!
//! When a uDMA transfer is completed, the channel will be automatically
//! disabled by the uDMA controller. Therefore, this function should be called
//! prior to starting up any new transfer.
//!
//! \param channelBitMask is the bitmask of the channels to enable.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void uDMAEnableChannel(uint32_t channelBitMask)
{
    HWREG(DMA_BASE + DMA_O_SETCHANNELEN) = channelBitMask;
}

//*****************************************************************************
//
//! \brief Disables a uDMA channel for operation.
//!
//! This function disables the specified uDMA channels. Once disabled, a channel
//! will not respond to uDMA transfer requests until re-enabled via
//! \ref uDMAEnableChannel().
//!
//! \param channelBitMask is the bitmask of the channels to disable.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void uDMADisableChannel(uint32_t channelBitMask)
{
    HWREG(DMA_BASE + DMA_O_CLEARCHANNELEN) = channelBitMask;
}

//*****************************************************************************
//
//! \brief Checks if a uDMA channel is enabled for operation.
//!
//! This function checks to see if a specific uDMA channel is enabled.  This
//! can be used to check the status of a transfer, since the channel will
//! be automatically disabled at the end of a transfer. Note that if multiple
//! channels are specified in the bitmask, the return value will be true if at
//! least one channel is enabled.
//!
//! \param channelBitMask is the bitmask of the channel to check.
//!
//! \return Returns status of uDMA channel.
//! - \c true  : Channel is enabled.
//! - \c false : Channel is disabled.
//
//*****************************************************************************
__STATIC_INLINE bool uDMAIsChannelEnabled(uint32_t channelBitMask)
{
    return ((HWREG(DMA_BASE + DMA_O_SETCHANNELEN) & (channelBitMask)) ? true : false);
}

//*****************************************************************************
//
//! \brief Sets the base address for the channel control table.
//!
//! This function sets the base address of the channel control table. This
//! table resides in system memory and holds control information for each uDMA
//! channel.  The table must be aligned on a 1024 byte boundary. The base
//! address must be set before any of the channel functions can be used.
//! Setting the base address of the primary control table will automatically
//! set the address for the alternate control table as the next memory
//! location after the primary control table.
//!
//! The size of the channel control table depends on the number of uDMA
//! channels, and which transfer modes are used.  Refer to the introductory
//! text and the microcontroller datasheet for more information about the
//! channel control table.
//!
//! \note This register cannot be read when the controller is in the reset
//! state.
//!
//! \param pControlTable is a pointer to the 1024 byte aligned base address
//! of the uDMA channel control table. The address must be an absolute address
//! in system memory space.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void uDMASetControlBase(void *pControlTable)
{
    // Check the arguments.
    ASSERT(((uint32_t)pControlTable & ~0x3FF) == (uint32_t)pControlTable);
    ASSERT((uint32_t)pControlTable >= SRAM_BASE);

    // Program the base address into the register.
    HWREG(DMA_BASE + DMA_O_CTRL) = (uint32_t)pControlTable;
}

//*****************************************************************************
//
//! \brief Gets the base address for the channel control table.
//!
//! This function gets the base address of the channel control table.  This
//! table resides in system memory and holds control information for each uDMA
//! channel.
//!
//! \return Returns a pointer to the base address of the channel control table.
//
//*****************************************************************************
__STATIC_INLINE void *uDMAGetControlBase(void)
{
    // Read the current value of the control base register, and return it to
    // the caller.
    return ((void *)HWREG(DMA_BASE + DMA_O_CTRL));
}

//*****************************************************************************
//
//! \brief Gets the base address for the channel control table alternate structures.
//!
//! This function gets the base address of the second half of the channel
//! control table that holds the alternate control structures for each channel.
//!
//! \return Returns a pointer to the base address of the second half of the
//! channel control table.
//
//*****************************************************************************
__STATIC_INLINE void *uDMAGetControlAlternateBase(void)
{
    // Read the current value of the control base register, and return it to
    // the caller.
    return ((void *)HWREG(DMA_BASE + DMA_O_ALTCTRL));
}

//*****************************************************************************
//
//! \brief Requests a uDMA channel to start a transfer.
//!
//! This function allows software to request a uDMA channel to begin a
//! transfer. This could be used for performing a memory to memory transfer,
//! or if for some reason a transfer needs to be initiated by software instead
//! of the peripheral associated with that channel.
//!
//! \note If the channel is a software channel and interrupts are used, then
//! the completion will be signaled on the uDMA dedicated interrupt. If a
//! peripheral channel is used, then the completion will be signaled on the
//! peripheral's interrupt.
//!
//! \param channelBitMask is the bitmask of the channel on which to request a
//!        uDMA transfer.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void uDMARequestChannel(uint32_t channelBitMask)
{
    // Set the bit for this channel in the software uDMA request register.
    HWREG(DMA_BASE + DMA_O_SOFTREQ) = channelBitMask;
}

//*****************************************************************************
//
//! \brief Enables attributes of a uDMA channel.
//!
//! This function is used to enable attributes of a uDMA channel.
//!
//! \param channelBitMask is bitmask of the channel to configure.
//! \param attr is a combination of attributes for the channel.
//! The parameter is the bitwise OR of any of the following:
//! - \ref UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst mode.
//! - \ref UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//! for this channel (it is very unlikely that this flag should be used).
//! - \ref UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority.
//! - \ref UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//! peripheral for this channel.
//!
//! \return None
//
//*****************************************************************************
extern void uDMAEnableChannelAttribute(uint32_t channelBitMask, uint32_t attr);

//*****************************************************************************
//
//! \brief Disables attributes of an uDMA channel.
//!
//! This function is used to disable attributes of a uDMA channel.
//!
//! \param channelBitMask is bitmask of the channel to configure.
//! \param attr is a combination of attributes for the channel.
//! The parameter is the bitwise OR of any of the following:
//! - \ref UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst mode.
//! - \ref UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//! for this channel (it is very unlikely that this flag should be used).
//! - \ref UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority.
//! - \ref UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//! peripheral for this channel.
//!
//! \return None
//
//*****************************************************************************
extern void uDMADisableChannelAttribute(uint32_t channelBitMask, uint32_t attr);

//*****************************************************************************
//
//! \brief Gets the enabled attributes of a uDMA channel.
//!
//! This function returns a combination of flags representing the attributes of
//! the uDMA channel.
//!
//! \param channelBitMask is the bitmask of the channel to configure.
//!
//! \return Returns the bitwise OR of the attributes of the uDMA channel, which
//! can be any of the following:
//! - \ref UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst mode.
//! - \ref UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//! for this channel (it is very unlikely that this flag should be used).
//! - \ref UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority.
//! - \ref UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//! peripheral for this channel.
//
//*****************************************************************************
extern uint32_t uDMAGetChannelAttribute(uint32_t channelBitMask);

//*****************************************************************************
//
//! \brief Sets the control parameters for a uDMA channel control structure.
//!
//! This function is used to set control parameters for a uDMA transfer.  These
//! are typically parameters that are not changed often.
//!
//! \note The address increment cannot be smaller than the data size.
//!
//! \param pChannelControlStruct is a pointer to the primary or alternate
//! control table of the uDMA channel to be set.
//! \param control is the bitwise OR of five values:
//! - Data size
//!   - \ref UDMA_SIZE_8  : 8 bits.
//!   - \ref UDMA_SIZE_16 : 16 bits.
//!   - \ref UDMA_SIZE_32 : 32 bits.
//! - Source address increment
//!   - \ref UDMA_SRC_INC_8    : 8 bits.
//!   - \ref UDMA_SRC_INC_16   : 16 bits.
//!   - \ref UDMA_SRC_INC_32   : 32 bits.
//!   - \ref UDMA_SRC_INC_NONE : Non-incrementing.
//! - Destination address increment
//!   - \ref UDMA_DST_INC_8    : 8 bits.
//!   - \ref UDMA_DST_INC_16   : 16 bits.
//!   - \ref UDMA_DST_INC_32   : 32 bits.
//!   - \ref UDMA_DST_INC_NONE : Non-incrementing.
//! - Arbitration size. Determines how many items are transferred before
//! the uDMA controller re-arbitrates for the bus. In power of 2.
//!   - \ref UDMA_ARB_1
//!   - \ref UDMA_ARB_2
//!   - \ref UDMA_ARB_4
//!   - \ref UDMA_ARB_8
//!   - ...
//!   - \ref UDMA_ARB_1024
//! - Force the channel to only respond to burst requests at the tail end of a scatter-gather transfer.
//!   - \ref UDMA_NEXT_USEBURST
//!
//! \return None
//
//*****************************************************************************
extern void uDMASetChannelControl(volatile uDMAControlTableEntry *pChannelControlStruct, uint32_t control);

//*****************************************************************************
//
//! \brief Sets the transfer parameters for a uDMA channel control structure.
//!
//! This function is used to set the parameters for a uDMA transfer.  These are
//! typically parameters that are changed often. The function
//! \ref uDMASetChannelControl() MUST be called at least once for this channel prior
//! to calling this function.
//!
//! The \c pSrcAddr and \c pDstAddr parameters are pointers to the first
//! location of the data to be transferred. These addresses should be aligned
//! according to the item size. The compiler will take care of this if the
//! pointers are pointing to storage of the appropriate data type.
//!
//! The two scatter/gather modes, MEMORY and PERIPHERAL, are actually different
//! depending on whether the primary or alternate control structure is
//! selected. This function will recognize from the address of the
//! \c pChannelControlStruct if it's a primary or alternate control structure and
//! will set the scatter/gather mode as appropriate for it.
//!
//! The channel must also be enabled using \ref uDMAEnableChannel() after calling
//! this function. The transfer will not begin until the channel has been set
//! up and enabled. Note that the channel is automatically disabled after the
//! transfer is completed, meaning that \ref uDMAEnableChannel() must be called
//! again after setting up the next transfer.
//!
//! \note Great care must be taken to not modify a channel control structure
//! that is in use or else the results will be unpredictable, including the
//! possibility of undesired data transfers to or from memory or peripherals.
//! For BASIC and AUTO modes, it is safe to make changes when the channel is
//! disabled, or the \ref uDMAGetChannelMode() returns \ref UDMA_MODE_STOP. For
//! PINGPONG or one of the SCATTER_GATHER modes, it is safe to modify the
//! primary or alternate control structure only when the other is being used.
//! The \ref uDMAGetChannelMode() function will return \ref UDMA_MODE_STOP when a
//! channel control structure is inactive and safe to modify.
//!
//! \param pChannelControlStruct is a pointer to the primary or alternate
//! control table of the uDMA channel to be set.
//! \param mode is the type of uDMA transfer.
//! The parameter should be one of the following values:
//! - \ref UDMA_MODE_STOP     : Stops the uDMA transfer. The controller sets the mode
//! to this value at the end of a transfer.
//! - \ref UDMA_MODE_BASIC    : Perform a basic transfer based on request.
//! - \ref UDMA_MODE_AUTO to perform a transfer that will always complete once
//! started even if request is removed.
//! - \ref UDMA_MODE_PINGPONG : Set up a transfer that switches between the
//! primary and alternate control structures for the channel. This allows
//! use of ping-pong buffering for uDMA transfers.
//! - \ref UDMA_MODE_MEM_SCATTER_GATHER : Set up a memory scatter-gather transfer.
//! - \ref UDMA_MODE_PER_SCATTER_GATHER : Set up a peripheral scatter-gather transfer.
//! \param pSrcAddr is the source address for the transfer.
//! \param pDstAddr is the destination address for the transfer.
//! \param transferSize is the number of data items to transfer (\b NOT bytes).
//!
//! \return None
//
//*****************************************************************************
extern void uDMASetChannelTransfer(volatile uDMAControlTableEntry *pChannelControlStruct,
                                   uint32_t mode,
                                   void *pSrcAddr,
                                   void *pDstAddr,
                                   uint32_t transferSize);

//*****************************************************************************
//
//! \brief Gets the current transfer size for a uDMA channel control structure.
//!
//! This function is used to get the uDMA transfer size for a channel. The
//! transfer size is the number of items to transfer, where the size of an item
//! might be 8, 16, or 32 bits. If a partial transfer has already occurred,
//! then the number of remaining items will be returned. If the transfer is
//! complete, then 0 will be returned.
//!
//! \param pChannelControlStruct is a pointer to the primary or alternate
//! control table of the uDMA channel in use.
//!
//! \return Returns the number of items remaining to transfer.
//
//*****************************************************************************
extern uint32_t uDMAGetChannelSize(volatile uDMAControlTableEntry const *pChannelControlStruct);

//*****************************************************************************
//
//! \brief Gets the transfer mode for a uDMA channel control structure.
//!
//! This function is used to get the transfer mode for the uDMA channel. It
//! can be used to query the status of a transfer on a channel. When the
//! transfer is complete the mode will be \ref UDMA_MODE_STOP.
//!
//! \param pChannelControlStruct is a pointer to the primary or alternate
//! control table of the uDMA channel in use.
//!
//! \return Returns the transfer mode of the specified channel and control
//! structure, which will be one of the following values:
//! - \ref UDMA_MODE_STOP
//! - \ref UDMA_MODE_BASIC
//! - \ref UDMA_MODE_AUTO
//! - \ref UDMA_MODE_PINGPONG
//! - \ref UDMA_MODE_MEM_SCATTER_GATHER
//! - \ref UDMA_MODE_PER_SCATTER_GATHER
//
//*****************************************************************************
extern uint32_t uDMAGetChannelMode(volatile uDMAControlTableEntry const *pChannelControlStruct);

//*****************************************************************************
//
//! \brief Registers an interrupt handler for the uDMA controller in the dynamic interrupt table.
//!
//! \note Only use this function if you want to use the dynamic vector table (in SRAM)!
//!
//! This function registers a function as the interrupt handler for a specific
//! interrupt and enables the corresponding interrupt in the interrupt controller.
//!
//! \note The interrupt handler for uDMA is for transfer completion when the
//! software channel is used. The interrupts for each peripheral channel are
//! handled through the individual peripheral interrupt handlers.
//!
//! \param intChannel specifies which uDMA interrupt is to be registered.
//! - \c INT_DMA_DONE_COMB : Register an interrupt handler to process interrupts
//!   from the uDMA software channel.
//! \param pfnHandler is a pointer to the function to be called when the
//! interrupt is activated.
//!
//! \return None
//!
//! \sa \ref IntRegister() for important information about registering interrupt
//! handlers.
//
//*****************************************************************************
__STATIC_INLINE void uDMARegisterInt(uint32_t intChannel, void (*pfnHandler)(void))
{
    // Check the arguments.
    ASSERT(pfnHandler);
    ASSERT(intChannel == INT_DMA_DONE_COMB);

    // Register the interrupt handler.
    IntRegister(intChannel, pfnHandler);

    // Enable the memory management fault.
    IntEnable(intChannel);
}

//*****************************************************************************
//
//! \brief Unregisters an interrupt handler for the uDMA controller in the dynamic interrupt table.
//!
//! This function will disable and clear the handler to be called for the
//! specified uDMA interrupt.
//!
//! \param intChannel specifies which uDMA interrupt to unregister.
//! - \c INT_DMA_DONE_COMB : Register an interrupt handler to process interrupts
//!   from the uDMA software channel.
//!
//! \return None
//!
//! \sa \ref IntRegister() for important information about registering interrupt
//! handlers.
//
//*****************************************************************************
__STATIC_INLINE void uDMAUnregisterInt(uint32_t intChannel)
{
    // Check the arguments.
    ASSERT(intChannel == INT_DMA_DONE_COMB);

    // Disable the interrupt.
    IntDisable(intChannel);

    // Unregister the interrupt handler.
    IntUnregister(intChannel);
}

//*****************************************************************************
//
//! \brief Clears uDMA interrupt done status.
//!
//! Clears bits in the uDMA interrupt status register according to which bits
//! are set in \c channelBitMask. There is one bit for each channel. If a a bit
//! is set in \c channelBitMask, then that corresponding channel's interrupt
//! status will be cleared (if it was set).
//!
//! \param channelBitMask is a mask with one bit for each uDMA channel.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void uDMAClearInt(uint32_t channelBitMask)
{
    // Clear the requested bits in the uDMA interrupt status register.
    HWREG(DMA_BASE + DMA_O_REQDONE) = channelBitMask;
}

//*****************************************************************************
//
//! \brief Get the uDMA interrupt status.
//!
//! This function returns the interrupt status for the specified UDMA. This
//! function does not differentiate between software or hardware activated
//! interrupts.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE uint32_t uDMAIntStatus(void)
{
    // Return the uDMA interrupt status register.
    return (HWREG(DMA_BASE + DMA_O_REQDONE));
}

//*****************************************************************************
//
//! \brief Enable interrupt on software event driven uDMA transfers.
//!
//! \note The main purpose of this function is to prevent propagation of uDMA
//! status signals to a peripheral, if a peripheral and a software event is
//! sharing the uDMA channel. If it is desired to initiate a transfer by
//! writing to a register inside the uDMA (this means a software driven
//! channel), then the uDMA status signals propagation need to be blocked to
//! the hardware peripherals.
//!
//! \param intChannel identifies which uDMA interrupt to enable software
//!        interrupts for.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void uDMAEnableSwEventInt(uint32_t intChannel)
{
    // Check the arguments.
    ASSERT(intChannel < UDMA_NUM_CHANNELS);

    // Enable the channel.
    HWREG(DMA_BASE + DMA_O_DONEMASK) |= intChannel;
}

//*****************************************************************************
//
//! \brief Disable interrupt on software event driven uDMA transfers.
//!
//! This register disables the blocking of the uDMA status signals propagation
//! to the hardware peripheral connected to the uDMA on the \c intChannel.
//!
//! \param intChannel identifies which uDMA interrupt to disable software
//!        interrupts for.
//!
//! \return None
//!
//! \sa \ref uDMAEnableSwEventInt()
//
//*****************************************************************************
__STATIC_INLINE void uDMADisableSwEventInt(uint32_t intChannel)
{
    // Check the arguments.
    ASSERT(intChannel < UDMA_NUM_CHANNELS);

    // Disable the SW channel.
    HWREG(DMA_BASE + DMA_O_DONEMASK) &= ~intChannel;
}

//*****************************************************************************
//
//! \brief Return the status of the uDMA module.
//!
//! \note This status register cannot be read when the controller is in the reset state.
//!
//! \return Current status of the uDMA module.
//
//*****************************************************************************
__STATIC_INLINE uint32_t uDMAGetStatus(void)
{
    // Read and return the status register.
    return HWREG(DMA_BASE + DMA_O_STATUS);
}

//*****************************************************************************
//
//! \brief Set the priority of a uDMA channel.
//!
//! \note Writing 0 to a bit has no effect on the priority. To reset a channel
//! priority to the default value use \ref uDMAClearChannelPriority().
//!
//! \param channelBitMask is bitmask of the uDMA channel to set the priority for.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void uDMASetChannelPriority(uint32_t channelBitMask)
{
    // Set the channel priority to high.
    HWREG(DMA_BASE + DMA_O_SETCHNLPRIORITY) = channelBitMask;
}

//*****************************************************************************
//
//! \brief Get the priority of a uDMA channel.
//!
//! \param channelBitMask The bitmask of the uDMA channel to get the priority for.
//!
//! \return Returns one of:
//! - \ref UDMA_PRIORITY_HIGH
//! - \ref UDMA_PRIORITY_LOW
//
//*****************************************************************************
__STATIC_INLINE bool uDMAGetChannelPriority(uint32_t channelBitMask)
{
    // Return the channel priority.
    return (HWREG(DMA_BASE + DMA_O_SETCHNLPRIORITY) & (channelBitMask) ? UDMA_PRIORITY_HIGH : UDMA_PRIORITY_LOW);
}

//*****************************************************************************
//
//! \brief Clear the priority of a uDMA channel.
//!
//! \note Writing 0 to a bit has no effect on the priority. To set a channel
//! priority to high use \ref uDMASetChannelPriority().
//!
//! \param channelBitMask The bitmask of the uDMA channel to clear the priority for.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void uDMAClearChannelPriority(uint32_t channelBitMask)
{
    // Clear the channel priority.
    HWREG(DMA_BASE + DMA_O_CLEARCHNLPRIORITY) = channelBitMask;
}

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
//! Close the Doxygen group.
//! @}
//! @}
//
//*****************************************************************************

#endif //  __UDMA_H__
