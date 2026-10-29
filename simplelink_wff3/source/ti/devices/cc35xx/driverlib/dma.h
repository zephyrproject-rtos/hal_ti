/******************************************************************************
 *  Filename:       dma.h
 *
 *  Description:    Defines and prototypes for the DMA peripheral.
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

#ifndef ti_devices_dma__include
#define ti_devices_dma__include

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup dma_api
//! @{
//
//*****************************************************************************

#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_host_dma.h"
#include "../inc/hw_soc_aaon.h"
#include "../inc/hw_soc_aon.h"
#include "debug.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//! Number of available DMA channels
#define DMA_NUM_CHANNELS            14
//! DMA channel memory map offset, in bytes
#define DMA_CH_OFFSET               0x1000
//! DMA channel control field width, in number of bits (CHCTL register)
#define DMA_CHCTL_FIELD_WIDTH       HOST_DMA_CHCTL0_CH0_W
//! Number of fields in CHCTL register
#define DMA_CHCTRL_NUMBER_OF_FIELDS (32 / DMA_CHCTL_FIELD_WIDTH)

//*****************************************************************************
//
// Configuration values that can be passed to DMAConfigureChannel() as the config parameter
//
//*****************************************************************************
//! Source pointer wraps around (block mode)
//! (non-block mode by default - incremental)
#define DMA_CONFIG_SRC_PTR_WRAP       HOST_DMA_CH0JCTL_BLKMODESRC
//! Destination pointer wraps around (block mode)
//! (non-block mode by default - incremental)
#define DMA_CONFIG_DST_PTR_WRAP       HOST_DMA_CH0JCTL_BLKMODEDST
//! Tie DMA request signal high. This indicates to DMA arbiter that both source and
//! destination is ready for transaction. Set this bit when doing memory-to-memory transactions.
#define DMA_CONFIG_FORCE_REQ          HOST_DMA_CH0JCTL_DMASIGBPS
//! Source pointer (FIFO mode)
#define DMA_CONFIG_SRC_PTR_FIFO       HOST_DMA_CH0JCTL_FIFOMODS
//! Destination pointer (FIFO mode)
#define DMA_CONFIG_DST_PTR_FIFO       HOST_DMA_CH0JCTL_FIFOMODD
//! Link DMA channel to RX port of peripheral
#define DMA_CONFIG_RX                 0x00000000U
//! Link DMA channel to TX port of peripheral
#define DMA_CONFIG_TX                 HOST_DMA_CH0JCTL_SRCDSTCFG
//! Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)
#define DMA_CONFIG_CLEAR_AT_JOB_START HOST_DMA_CH0JCTL_ENCLR
//! Bitmask of allowed flags passed to \ref DMAConfigureChannel() and \ref DMAConfigureChannelFlags().
#define DMA_CONFIG_ALLOWED_MASK                                                                           \
    (DMA_CONFIG_SRC_PTR_WRAP | DMA_CONFIG_DST_PTR_WRAP | DMA_CONFIG_FORCE_REQ | DMA_CONFIG_SRC_PTR_FIFO | \
     DMA_CONFIG_DST_PTR_FIFO | DMA_CONFIG_TX | DMA_CONFIG_CLEAR_AT_JOB_START)

//*****************************************************************************
//
// Word size values that can be passed to DMAConfigureChannel() as the wordSize parameter
//
//*****************************************************************************
//! Word size is 1 byte
#define DMA_WORD_SIZE_1B 2
//! Word size is 2 bytes
#define DMA_WORD_SIZE_2B 1
//! Word size is 4 bytes
#define DMA_WORD_SIZE_4B 0

//*****************************************************************************
//
// Enumerations
//
//*****************************************************************************
// DMA peripheral mapping (source:
// https://confluence.itg.ti.com/display/WNG/Host+DMA#HostDMA-HostDMAAppendix1-Channelsallocation)
//! DMA peripheral ports enumerations for use with \ref DMAInitChannel().
typedef enum
{
    DMA_PERIPH_UARTLIN_0 = 0,  //!< UARTLIN0
    DMA_PERIPH_UARTLIN_1 = 1,  //!< UARTLIN1
    DMA_PERIPH_SPI_0     = 2,  //!< SPI0
    DMA_PERIPH_SPI_1     = 3,  //!< SPI1
    DMA_PERIPH_I2C_0     = 4,  //!< I2C0
    DMA_PERIPH_I2C_1     = 5,  //!< I2C1
    DMA_PERIPH_SDMMC     = 6,  //!< SDMMC
    DMA_PERIPH_SDIO      = 7,  //!< SDIO
    DMA_PERIPH_MCAN      = 8,  //!< MCAN
    DMA_PERIPH_ADC       = 9,  //!< ADC
    DMA_PERIPH_PDM       = 10, //!< PDM
    DMA_PERIPH_HIF       = 11, //!< HIF
    DMA_PERIPH_UARTLIN_2 = 12, //!< UARTLIN2
    DMA_NUM_PERIPHS      = 13  //!< Number of different DMA peripherals supported
} DMAPeripheral;

// TODO: Update to use DOC release defines when available (LPRFXXWARE-747)
typedef enum
{
    DMA_FSMSTATE_IDLE            = (0x0 << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_EXCEPTION       = (0x2 << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_DRAIN           = (0x3 << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_ABORT           = (0x4 << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_PENDING_ARB     = (0x8 << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_COPY            = (0x9 << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_COPY_LAST       = (0xA << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_DONE            = (0xC << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_SAVE_CTX        = (0xD << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_WAIT_NEXT_TRANS = (0xE << HOST_DMA_CH0STA_FSMSTATE_S),
    DMA_FSMSTATE_LAST            = (0xF << HOST_DMA_CH0STA_FSMSTATE_S)
} DMAChannelFsmState;

typedef enum
{
    DMA_HW_EVT_NO_EVENT   = 0, //!< No pending event // TODO: hw_ doc calls this "processing"
    DMA_HW_EVT_TRANS_DONE = 1, //!< Transaction done
    DMA_HW_EVT_ABORTED    = 2, //!< Transaction aborted by SW
    DMA_HW_EVT_EXC        = 4  //!< An error has occurred
} DMAChannelStatus;

typedef enum
{
    DMA_CMD_RUN   = 1,
    DMA_CMD_ABORT = 2,
    DMA_CMD_INIT  = 4
} DMACommand;

//*****************************************************************************
//
// Functions
//
//*****************************************************************************
//*****************************************************************************
//
//! \brief Initialize DMA channel by mapping it to a peripheral.
//!
//! \note For memory-to-memory transactions (for example RAM to RAM), it is not
//!       necessary to initialize the DMA channel. In those cases, call
//!       \ref DMAConfigureChannel() directly.
//!
//! \param channel is the DMA channel to configure.
//! \param peripheral is the peripheral (see \ref DMAPeripheral).
//
//*****************************************************************************
extern void DMAInitChannel(uint32_t channel, DMAPeripheral peripheral);

//*****************************************************************************
//
//! \brief Configure job for the specified channel.
//!
//! This function must be called after \ref DMAInitChannel().
//!
//! \param channel is the DMA channel to configure.
//! \param blockSize is size of the block in words (up to 64 words).
//! If block mode is enabled, defines the address wrap around. Since channel
//! arbitration decisions are made every block, this also effect how much
//! bandwidth is given to a specific channel.
//! \param wordSize is the word size.
//! The parameter can have one of these three values:
//! - \ref DMA_WORD_SIZE_1B
//! - \ref DMA_WORD_SIZE_2B
//! - \ref DMA_WORD_SIZE_4B
//! \param config is the DMA channel configuration for the peripheral.
//! The parameter is the bitwise OR of five values (all values set to 0 by default):
//! - Source pointer block mode behavior
//!   - \ref DMA_CONFIG_SRC_PTR_WRAP
//! - Destination pointer block mode behavior
//!   - \ref DMA_CONFIG_DST_PTR_WRAP
//! - Force request bit high.
//!   Use to indicate to DMA arbiter that source and destination is ready for
//!   the transaction. Must be used, for example, when using DMA for
//!   memory-to-memory transactions.
//!   - \ref DMA_CONFIG_FORCE_REQ
//! - Source pointer FIFO mode behavior
//!   - \ref DMA_CONFIG_SRC_PTR_FIFO
//! - Destination pointer FIFO mode behavior
//!   - \ref DMA_CONFIG_DST_PTR_FIFO
//! - Link DMA channel to RX or TX port of peripheral
//!   - \ref DMA_CONFIG_RX
//!   - \ref DMA_CONFIG_TX
//! - Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle
//!   after run cmd)
//!   - \ref DMA_CONFIG_CLEAR_AT_JOB_START
//
//*****************************************************************************
extern void DMAConfigureChannel(uint32_t channel, uint8_t blockSize, uint8_t wordSize, uint32_t config);

//*****************************************************************************
//
//! \brief Start job for the specified channel.
//!
//! This function must be called after \ref DMAConfigureChannel().
//!
//! \param channel is the DMA channel to start.
//! \param srcStartAddr is a pointer to the source data.
//! \param dstStartAddr is a pointer to the destination data.
//! \param transLenByte is the number of bytes to transfer
//! \param remainingBytesBurst enables transaction optimization in specific cases.
//!
//! \warning Parameter \c remainingBytesBurst can only be used with the
//!          DMA_PERIPH_HIF peripheral!
//!
//! When blockSize ( \ref DMAConfigureChannel()) is not a multiple of transLenByte,
//! the last transaction will be less than blockSize. By default, this last copy
//! will execute word by word. When multiple DMA channels work parallel the DMA
//! round-robin algorithm will move to other channels between every word.
//! When setting this flag to true, the behavior will change to copy the all
//! remaining bytes at once, BUT only after the destination peripheral asserts the
//! request signal to the DMA. For example, UART TX will assert the request flag
//! once the TX buffer is empty.
//!
//! \note Not every destination peripheral supports asserting will assert the
//! request signal. If remainingBytesBurst is true and the request signal is
//! not asserted the transaction will not complete!
//
//*****************************************************************************
extern void DMAStartTransaction(uint32_t channel,
                                const uint32_t *srcStartAddr,
                                uint32_t *dstStartAddr,
                                uint16_t transLenByte,
                                bool remainingBytesBurst);

//*****************************************************************************
//
//! \brief Returns the status of the specified channel.
//!
//! \param channel is the DMA channel.
//!
//! \return Returns a bitwise OR of one or more \ref DMAChannelStatus values.
//
//*****************************************************************************
extern uint32_t DMAGetChannelStatus(uint32_t channel);

//*****************************************************************************
//
//! \brief Returns the FSM status of the specified channel.
//!
//! \param channel is the DMA channel.
//!
//! \return Returns the DMA channel FSM state.
//
//*****************************************************************************
extern DMAChannelFsmState DMAGetChannelFSMState(uint32_t channel);

//*****************************************************************************
//
//! \brief Returns the direction of the specified channel.
//!
//! \param channel is the DMA channel.
//!
//! \return Returns \ref DMA_CONFIG_TX or \ref DMA_CONFIG_RX.
//
//*****************************************************************************
extern uint32_t DMAGetChannelDirection(uint32_t channel);

//*****************************************************************************
//
//! \brief Enables DMA interrupt sources.
//!
//! This function enables the indicated DMA interrupt sources. Only the
//! sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! \note This function must be called from secure context.
//!
//! \param channelMask is the bit mask of the DMA channel interrupts to be enabled.
//!                    Bit 0 enables channel 0, bit 1 channel 1, and so on.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void DMAEnableInt(uint32_t channelMask)
{
    // Enable the specified interrupts.
    HWREG(SOC_AAON_BASE + SOC_AAON_O_DMASIMASK) |= channelMask;
}

//*****************************************************************************
//
//! \brief Disables DMA channel interrupts.
//!
//! This function disables the indicated DMA interrupt sources. Only the
//! sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! \note This function must be called from secure context.
//!
//! \param channelMask is the bit mask of the DMA channel interrupts to disable.
//!                    Bit 0 disables channel 0, bit 1 channel 1, and so on.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void DMADisableInt(uint32_t channelMask)
{
    // Disable the specified interrupts.
    HWREG(SOC_AAON_BASE + SOC_AAON_O_DMASIMASK) &= ~(channelMask);
}

//*****************************************************************************
//
//! \brief Clears DMA interrupt sources.
//!
//! The specified DMA interrupt sources are cleared, so that they no longer
//! assert. This function must be called in the interrupt handler to keep the
//! interrupt from being recognized again immediately upon exit.
//!
//! \note This function must be called from secure context.
//!
//! \param channelMask is a bit mask of the channel interrupts to be cleared.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void DMAClearInt(uint32_t channelMask)
{
    // Clear the requested interrupt sources
    HWREG(SOC_AAON_BASE + SOC_AAON_O_DMASICLR) = channelMask;
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! This function returns the interrupt status for the DMA. Either
//! the raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \note This function must be called from secure context.
//!
//! \param masked selects either raw or masked interrupt.
//! - \c true  : Masked interrupt status is required.
//! - \c false : Raw interrupt status is required.
//!
//! \return Returns the current interrupt status
//
//*****************************************************************************
__STATIC_INLINE uint32_t DMAIntStatus(bool masked)
{
    // Return either the masked interrupt status or the raw interrupt status as
    // requested.
    if (masked)
    {
        return (HWREG(SOC_AAON_BASE + SOC_AAON_O_DMASMIS));
    }
    else
    {
        return (HWREG(SOC_AAON_BASE + SOC_AAON_O_DMASICLR));
    }
}

//*****************************************************************************
//
//! \brief Clear all flags and set the specified channel flags.
//!
//! This function can be called after \ref DMAConfigureChannel() when need to set
//! specific flags.
//! As a first step. the function clear all flags and then set the specified
//! channel flags.
//! \note It is not allow to you this fuction during channel operation
//! \param channel is the DMA channel to configure.
//! \param config is the DMA channel configuration for the peripheral.
//! The parameter is the bitwise OR of five values:
//! - Source pointer block mode behavior
//!   - \ref DMA_CONFIG_SRC_PTR_WRAP
//! - Destination pointer block mode behavior
//!   - \ref DMA_CONFIG_DST_PTR_WRAP
//! - Force request bit high.
//!   Use to indicate to DMA arbiter that source and destination is ready for
//!   the transaction. Must be used, for example, when using DMA for
//!   memory-to-memory transactions.
//!   - \ref DMA_CONFIG_FORCE_REQ
//! - Source pointer FIFO mode behavior
//!   - \ref DMA_CONFIG_SRC_PTR_FIFO
//! - Destination pointer FIFO mode behavior
//!   - \ref DMA_CONFIG_DST_PTR_FIFO
//! - Link DMA channel to RX or TX port of peripheral
//!   - \ref DMA_CONFIG_RX
//!   - \ref DMA_CONFIG_TX
//! - Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle
//!   after run cmd)
//!   - \ref DMA_CONFIG_CLEAR_AT_JOB_START
//
//*****************************************************************************
__STATIC_INLINE void DMAConfigureChannelFlags(uint32_t channel, uint32_t config)
{
    // Check arguments
    ASSERT(channel < DMA_NUM_CHANNELS);
    // Check allowed flags and not allowed flags
    ASSERT((~(DMA_CONFIG_ALLOWED_MASK)&config) == 0);

    uint32_t regOffset = channel * DMA_CH_OFFSET;
    uint32_t configReg = HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0JCTL + regOffset);

    // Clear flags
    configReg &= ~DMA_CONFIG_ALLOWED_MASK;

    // Incorporate flags to configuration value
    configReg |= config;

    // Write configuration to hardware
    HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0JCTL + regOffset) = configReg;
}

//*****************************************************************************
//
//! \brief Enable FIFO mode behavior for the destination pointer.
//!
//! When FIFO mode is enabled, the destination pointer is not incremented.
//!
//! This function can be called after \ref DMAInitChannel().
//!
//! \param channel is the DMA channel to configure.
//
//*****************************************************************************
__STATIC_INLINE void DMAEnableDestinationFifoMode(uint32_t channel)
{
    // Check arguments
    ASSERT(channel < DMA_NUM_CHANNELS);

    uint32_t regOffset = channel * DMA_CH_OFFSET;

    HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0JCTL + regOffset) |= HOST_DMA_CH0JCTL_FIFOMODD;
}

//*****************************************************************************
//
//! \brief Disable FIFO mode behavior for the destination pointer.
//!
//! When FIFO mode is disabled, the destination pointer will be incremented
//! after every transfer according to the word size.
//!
//! This function can be called after \ref DMAInitChannel().
//!
//! \param channel is the DMA channel to configure.
//
//*****************************************************************************
__STATIC_INLINE void DMADisableDestinationFifoMode(uint32_t channel)
{
    // Check arguments
    ASSERT(channel < DMA_NUM_CHANNELS);

    uint32_t regOffset = channel * DMA_CH_OFFSET;

    HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0JCTL + regOffset) &= ~HOST_DMA_CH0JCTL_FIFOMODD;
}

//*****************************************************************************
//
//! \brief Get channel linked peripheral
//!
//! This function can be called after \ref DMAInitChannel() when need to get
//! the linked peripheral to specific channel.
//! \param channel is the DMA channel to get linked peripheral.
//!
//! \return Returns the peripheral linked to the specified channel, one of
//!         \ref DMAPeripheral enum values.
//
//*****************************************************************************
__STATIC_INLINE uint32_t DMAGetChannelPeripheral(uint32_t channel)
{
    uint32_t regOffset;
    uint32_t shiftValue;
    uint32_t channelReg;
    uint32_t peripheral;

    // Calculate register offset (0/4) based on the channel number
    regOffset = (channel / DMA_CHCTRL_NUMBER_OF_FIELDS) * sizeof(uint32_t);

    // Read register containing channel configuration
    channelReg = HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CHCTL0 + regOffset);

    // Calculate bitfield position based on the channel number
    shiftValue = (channel % DMA_CHCTRL_NUMBER_OF_FIELDS) * DMA_CHCTL_FIELD_WIDTH;

    // Extract the peripheral
    peripheral = (channelReg & (HOST_DMA_CHCTL0_CH0_M << shiftValue)) >> shiftValue;

    return peripheral;
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

#endif // ti_devices_dma__include
