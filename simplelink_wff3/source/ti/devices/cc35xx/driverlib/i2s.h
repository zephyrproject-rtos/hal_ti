/******************************************************************************
 *  Filename:       i2s.h
 *
 *  Description:    Prototypes and defines for the I2S API.
 *
 *  Copyright (c) 2025-2026 Texas Instruments Incorporated
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

#ifndef ti_devices_i2s__include
#define ti_devices_i2s__include

//****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup i2s_api
//! @{
//
//****************************************************************************

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
#include "../inc/hw_i2s.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
// Defines for selecting I2S module clock source
//
//*****************************************************************************
#define I2S_CLK_SRC_SOC_CLK     I2S_CLKCFG_CLKSEL_SEL_1 //!< SOC clock
#define I2S_CLK_SRC_SOC_PLL_CLK I2S_CLKCFG_CLKSEL_SEL_2 //!< SOC PLL clock
#define I2S_CLK_SRC_HFXT_CLK    I2S_CLKCFG_CLKSEL_SEL_3 //!< HFXT

//*****************************************************************************
//
// Defines for selecting data pin usage.
//
//*****************************************************************************
#define I2S_SD0_DIS I2S_AIFDIRCFG_AD0_DIS //!< SD0 is disabled
#define I2S_SD0_IN  I2S_AIFDIRCFG_AD0_IN  //!< SD0 is an input
#define I2S_SD0_OUT I2S_AIFDIRCFG_AD0_OUT //!< SD0 is an output
#define I2S_SD1_DIS I2S_AIFDIRCFG_AD1_DIS //!< SD1 is disabled
#define I2S_SD1_IN  I2S_AIFDIRCFG_AD1_IN  //!< SD1 is an input
#define I2S_SD1_OUT I2S_AIFDIRCFG_AD1_OUT //!< SD1 is an output

//*****************************************************************************
//
// Defines for activating an audio channel.
//
//*****************************************************************************
#define I2S_CHAN0_MASK 0x00000001
#define I2S_CHAN1_MASK 0x00000002
#define I2S_CHAN2_MASK 0x00000004
#define I2S_CHAN3_MASK 0x00000008
#define I2S_CHAN4_MASK 0x00000010
#define I2S_CHAN5_MASK 0x00000020
#define I2S_CHAN6_MASK 0x00000040
#define I2S_CHAN7_MASK 0x00000080

//*****************************************************************************
//
// Defines for the audio format configuration
//
//*****************************************************************************
#define I2S_MEM_LENGTH_16 I2S_AIFFMTCFG_LEN32__16BIT //!< 16 bit size of word in memory
#define I2S_MEM_LENGTH_32 I2S_AIFFMTCFG_LEN32__32BIT //!< 32 bit size of word in memory
#define I2S_POS_EDGE      I2S_AIFFMTCFG_SMPLEDGE_POS //!< Sample on positive edge
#define I2S_NEG_EDGE      I2S_AIFFMTCFG_SMPLEDGE_NEG //!< Sample on negative edge

//*****************************************************************************
//
// Defines for the sample stamp counters
//
//*****************************************************************************
#define I2S_STMP_SATURATION 0x0000FFFF //!< The saturation value used when calculating the sample stamp

//*****************************************************************************
//
// Defines for the interrupt
//
//*****************************************************************************
#define I2S_INT_XCNT_CAPTURE I2S_IRQFLAGS_XCNTCPT   //!< MCUCLK Capture
#define I2S_INT_DMA_IN       I2S_IRQFLAGS_AIFDMAIN  //!< DMA output buffer full interrupt
#define I2S_INT_DMA_OUT      I2S_IRQFLAGS_AIFDMAOUT //!< DMA input buffer empty interrupt
#define I2S_INT_TIMEOUT      I2S_IRQFLAGS_WCLKTOUT  //!< Word Clock Timeout
#define I2S_INT_BUS_ERR      I2S_IRQFLAGS_BUSERR    //!< DMA Bus error
#define I2S_INT_WCLK_ERR     I2S_IRQFLAGS_WCLKERR   //!< Word Clock error
#define I2S_INT_PTR_ERR      I2S_IRQFLAGS_PTRERR    //!< Data pointer error (DMA data was not updated in time)
#define I2S_INT_ALL                                                                                                   \
    (I2S_INT_XCNT_CAPTURE | I2S_INT_DMA_IN | I2S_INT_DMA_OUT | I2S_INT_TIMEOUT | I2S_INT_BUS_ERR | I2S_INT_WCLK_ERR | \
     I2S_INT_PTR_ERR) //!< All interrupts

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

#ifdef DRIVERLIB_DEBUG
//*****************************************************************************
//
//! \internal
//!
//! \brief Checks an I2S base address.
//!
//! This function determines if an I2S module base address is valid.
//!
//! \param base is the base address of the I2S module.
//!
//! \return Returns \c true if the base address is valid and \c false
//! otherwise.
//
//*****************************************************************************
static bool I2SBaseValid(uint32_t base)
{
    return (base == I2S_BASE);
}
#endif

//*****************************************************************************
//
//! \brief Enables individual I2S interrupt sources.
//!
//! This function enables the indicated I2S interrupt sources. Only the
//! sources that are enabled can propagate to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! \param base is the base address of the I2S module.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2S_INT_XCNT_CAPTURE
//! - \ref I2S_INT_DMA_IN
//! - \ref I2S_INT_DMA_OUT
//! - \ref I2S_INT_TIMEOUT
//! - \ref I2S_INT_BUS_ERR
//! - \ref I2S_INT_WCLK_ERR
//! - \ref I2S_INT_PTR_ERR
//! - \ref I2S_INT_ALL (covers all the above)
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SEnableInt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Enable the specified interrupts
    HWREG(I2S_BASE + I2S_O_IRQMASK) |= intFlags;
}

//*****************************************************************************
//
//! \brief Disables individual I2S interrupt sources.
//!
//! This function disables the indicated I2S interrupt sources. Only the
//! sources that are enabled propagate to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! \param base is the base address of the I2S module.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2S_INT_XCNT_CAPTURE
//! - \ref I2S_INT_DMA_IN
//! - \ref I2S_INT_DMA_OUT
//! - \ref I2S_INT_TIMEOUT
//! - \ref I2S_INT_BUS_ERR
//! - \ref I2S_INT_WCLK_ERR
//! - \ref I2S_INT_PTR_ERR
//! - \ref I2S_INT_ALL (covers all the above)
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SDisableInt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Disable the specified interrupts
    HWREG(I2S_BASE + I2S_O_IRQMASK) &= ~intFlags;
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! This function returns the interrupt status for the specified I2S. Either
//! the raw interrupt status or the status of interrupts that propagate to the
//! processor can be returned.
//!
//! \param base is the base address of the I2S module.
//! \param masked selects between raw and masked interrupt status:
//! - \c false : Raw interrupt status is required.
//! - \c true  : Masked interrupt status is required.
//!
//! \return Returns the current interrupt status as a vector of:
//! - \ref I2S_INT_XCNT_CAPTURE
//! - \ref I2S_INT_DMA_IN
//! - \ref I2S_INT_DMA_OUT
//! - \ref I2S_INT_TIMEOUT
//! - \ref I2S_INT_BUS_ERR
//! - \ref I2S_INT_WCLK_ERR
//! - \ref I2S_INT_PTR_ERR
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2SIntStatus(uint32_t base, bool masked)
{
    uint32_t status;

    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Read the raw status
    status = HWREG(I2S_BASE + I2S_O_IRQFLAGS);

    // If the masked status is requested, mask the raw status with the interrupt
    // mask.
    if (masked)
    {
        status &= HWREG(I2S_BASE + I2S_O_IRQMASK);
    }

    return status;
}

//*****************************************************************************
//
//! \brief Clears I2S interrupt sources.
//!
//! The specified I2S interrupt sources are cleared, so that they no longer
//! assert. This function must be called in the interrupt handler to keep the
//! interrupt from being recognized again immediately upon exit.
//!
//! \param base is the base address of the I2S module.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2S_INT_XCNT_CAPTURE
//! - \ref I2S_INT_DMA_IN
//! - \ref I2S_INT_DMA_OUT
//! - \ref I2S_INT_TIMEOUT
//! - \ref I2S_INT_BUS_ERR
//! - \ref I2S_INT_WCLK_ERR
//! - \ref I2S_INT_PTR_ERR
//! - \ref I2S_INT_ALL (covers all the above)
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2SClearInt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Clear the requested interrupt sources
    HWREG(I2S_BASE + I2S_O_IRQCLR) = intFlags;
}

//*****************************************************************************
//
//! \brief Enable the Sample Stamp generator.
//!
//! Use this function to enable the sample stamp generator.
//!
//! \note It is the user's responsibility to ensure that the sample stamp
//! generator is properly configured before it is enabled. It is the setting
//! of the Input and Output triggers configured using
//! \ref I2SConfigureInSampleStampTrigger() and
//! \ref I2SConfigureOutSampleStampTrigger() that triggers the start point of
//! the audio streams.
//!
//! \param base is the base address of the I2S module.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SEnableSampleStamp(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Set the enable bit
    HWREG(I2S_BASE + I2S_O_STMPCTL) |= I2S_STMPCTL_STMPEN_M;
}

//*****************************************************************************
//
//! \brief Disable the Sample Stamp generator.
//!
//! Use this function to disable the sample stamp generator. When the sample
//! stamp generator is disabled, the clock counters are automatically cleared.
//!
//! \param base is the base address of the I2S module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2SDisableSampleStamp(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Clear the enable bit
    HWREG(I2S_BASE + I2S_O_STMPCTL) &= ~I2S_STMPCTL_STMPEN_M;
}

//*****************************************************************************
//
//! \brief Get the current value of a sample stamp counter.
//!
//! \param base is the base address of the I2S module.
//! \param channel is the sample stamp counter to sample.
//!
//! \return Returns the current value of the selected sample stamp channel.
//
//*****************************************************************************
extern uint32_t I2SGetSampleStamp(uint32_t base, uint32_t channel);

//*****************************************************************************
//
//! \brief Starts the I2S.
//!
//! I2S must be configured before it is started.
//!
//! \note Immediately after enabling the module the programmer must update
//! the DMA data pointer registers using \ref I2SSetInPointer() and
//! \ref I2SSetOutPointer() to ensure a new pointer is written before the DMA
//! transfer completes. Failure to update the pointer in time will result in
//! an \ref I2S_INT_PTR_ERR.
//!
//! \param base is the I2S module base address.
//! \param dmaLength is the number of frames in the DMA buffer. This will allow
//!        the DMA to read \c dmaLength frames between two pointer refreshes.
//!        Valid values are integers in the range [2, 256], both included.
//!
//! \return None.
//!
//! \sa I2SStop()
//
//*****************************************************************************
__STATIC_INLINE void I2SStart(uint32_t base, uint16_t dmaLength)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));
    ASSERT(dmaLength <= 256);
    ASSERT(dmaLength >= 2);

    // Enable the I2S module, by writting a non-zero value to AIFDMACFG.
    // AIFDMACFG expects the end frame index to be written, and the end index is
    // one less than the length.
    HWREG(I2S_BASE + I2S_O_AIFDMACFG) = (dmaLength - 1) & I2S_AIFDMACFG_ENDFRAMIDX_M;
}

//*****************************************************************************
//
//! \brief Stops the I2S module for operation.
//!
//! This function will immediately disable the I2S module. To ensure that
//! all buffer operations are completed before shutting down, the correct
//! procedure is:
//! 1. Do not update the data pointers using \ref I2SSetInPointer() and
//!    \ref I2SSetOutPointer().
//! 2. Wait until values returned by \ref I2SGetInPointerNext(),
//!    \ref I2SGetOutPointerNext(), \ref I2SGetInPointer() and
//!    \ref I2SGetOutPointer() are zero.
//! 3. Disable the I2S using \ref I2SStop() and clear the pointer
//!    error using \ref I2SClearInt().
//! 4. Disable bit clock source.
//!
//! \param base is the I2S module base address.
//!
//! \return None.
//!
//! \sa I2SStart()
//
//*****************************************************************************
__STATIC_INLINE void I2SStop(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Disable the I2S module
    HWREG(I2S_BASE + I2S_O_AIFDMACFG) = 0x00;
}

//*****************************************************************************
//
//! \brief Configure the serial format of the I2S module.
//!
//! The word length defines the size of the word transmitted on the data
//! lines. For single phased formats \c bitsPerSample is the exact number of
//! bits per word. In dual phased format this is the maximum number of bits per
//! word.
//!
//! \param base is the I2S module base address.
//! \param dataDelay is the number of BCLK periods between the first WCLK
//!         edge and the MSB of the first audio channel data transferred during
//!         the phase.
//!         Valued values are integers in the range [0, 255], both included.
//! \param memoryLength selects the memory length of the samples in memory.
//!        Possible values are:
//!        - \ref I2S_MEM_LENGTH_16
//!        - \ref I2S_MEM_LENGTH_32
//! \param samplingEdge selects if sampling on falling or rising edges.
//!        Possible values are:
//!        - \ref I2S_NEG_EDGE
//!        - \ref I2S_POS_EDGE
//! \param dualPhase must be set to \c true for dual phase and to \c false for
//!        single phase. This must be the same value as configured in
//!        \ref I2SConfigureClocks()
//! \param bitsPerSample is the number of bits transmitted for each sample.
//!        Valued values are integers in the range [8, 24], both included.
//!        If this number does not match with the memory length selected
//!        (16 bits or 32 bits), samples will be truncated or padded.
//!
//! \return None.
//!
//! \sa I2SConfigureFrame()
//
//*****************************************************************************
__STATIC_INLINE void I2SConfigureFormat(uint32_t base,
                                        uint8_t dataDelay,
                                        uint32_t memoryLength,
                                        uint32_t samplingEdge,
                                        bool dualPhase,
                                        uint8_t bitsPerSample)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));
    ASSERT(bitsPerSample <= 24); // Max. I2S_AIFFMTCFG_WORD_LEN
    ASSERT(bitsPerSample >= 8);  // Min. I2S_AIFFMTCFG_WORD_LEN

    // Setup register AIFFMTCFG Source
    HWREGH(I2S_BASE + I2S_O_AIFFMTCFG) = (dataDelay << I2S_AIFFMTCFG_DATADELAY_S) | (memoryLength) | (samplingEdge) |
                                         (dualPhase << I2S_AIFFMTCFG_DUALPHASE_S) |
                                         (bitsPerSample << I2S_AIFFMTCFG_WORDLEN_S);
}

//****************************************************************************
//
//! \brief Setup the two interfaces SD0 and SD1 (also called AD0 and AD1).
//!
//! This function sets interface's direction and activated channels.
//!
//! \param base is base address of the I2S module.
//! \param sd0Usage defines the usage of SD0. Valid values are:
//!         - \ref I2S_SD0_DIS
//!         - \ref I2S_SD0_IN
//!         - \ref I2S_SD0_OUT
//! \param sd0Channels defines the channel mask for SD0.
//!        Use a bitwise OR'ed combination of:
//!         - \ref I2S_CHAN0_MASK
//!         - \ref I2S_CHAN1_MASK
//!         - \ref I2S_CHAN2_MASK
//!         - \ref I2S_CHAN3_MASK
//!         - \ref I2S_CHAN4_MASK
//!         - \ref I2S_CHAN5_MASK
//!         - \ref I2S_CHAN6_MASK
//!         - \ref I2S_CHAN7_MASK
//! \param sd1Usage defines the usage of SD1. Valid values are:
//!         - \ref I2S_SD1_DIS
//!         - \ref I2S_SD1_IN
//!         - \ref I2S_SD1_OUT
//! \param sd1Channels defines the channel mask for SD1.
//!        Use a bitwise OR'ed combination of:
//!         - \ref I2S_CHAN0_MASK
//!         - \ref I2S_CHAN1_MASK
//!         - \ref I2S_CHAN2_MASK
//!         - \ref I2S_CHAN3_MASK
//!         - \ref I2S_CHAN4_MASK
//!         - \ref I2S_CHAN5_MASK
//!         - \ref I2S_CHAN6_MASK
//!         - \ref I2S_CHAN7_MASK
//!
//! \return None.
//!
//! \sa I2SConfigureFormat()
//
//****************************************************************************
__STATIC_INLINE void I2SConfigureFrame(uint32_t base,
                                       uint8_t sd0Usage,
                                       uint8_t sd0Channels,
                                       uint8_t sd1Usage,
                                       uint8_t sd1Channels)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Configure input/output channels
    HWREGB(I2S_BASE + I2S_O_AIFDIRCFG) = (sd0Usage | sd1Usage);

    // Configure the valid channel mask
    HWREGB(I2S_BASE + I2S_O_AIFWMASK0) = sd0Channels;
    HWREGB(I2S_BASE + I2S_O_AIFWMASK1) = sd1Channels;
}

//****************************************************************************
//
//! \brief Configure the I2S clocks (CCLK, WCLK and BCLK).
//!
//! This function does the following:
//! - Configure clocks to be either internal (Controller) or external (Target).
//! - Configure the I2S module to internally invert WCLK if selected by
//!   \c invertWclk.
//! - If \c isController is true, the I2S module will be configured to use
//!   internally generated clocks based on \c dualPhase, \c cclkDiv, \c wclkDiv
//!   and \c bclkDiv.
//!
//! \note This function will disable the I2S clocks if they were previously
//!       enabled. To enable the clocks use \ref I2SEnableControllerClocks().
//!
//! \param base is the base address of the I2S module.
//! \param isController selects if the device is a Target or a Controller:
//!                     - \c false: the device is a Target (external clock).
//!                     - \c true: the device is a Controller (internal clock).
//! \param invertWclk   selects if the WCLK should be internally inverted:
//!                     - \c false: WCLK is not inverted.
//!                     - \c true: WCLK is internally inverted.
//! \param dualPhase must be set to \c true for dual phase and to \c false for
//!        single phase. This must be the same value as configured in
//!        \ref I2SConfigureFormat().
//! \param cclkDiv is the desired controller clock (CCLK) divider.
//!        I.e. the number of ACLK periods in one CCLK period. Valid values are
//!        integers in the range [2, 1024], both included.
//! \param wclkDiv is the desired word clock (WCLK) divider.
//!        The interpretation of this value depends on the value of
//!        \c dualPhase:
//!         - \c false (single phase mode): \c wclkDiv is the number of BCLK
//!           periods in one WCLK period (rising edge to rising edge). Valid
//!           values for \c wclkDiv are integers in the range [2, 1024], both
//!           included.
//!         - \c true (dual phase mode): \c wclkDiv is the number of BCLK
//!           periods in each phase (one edge to the next opposite edge).
//!           Meaning the period of WCLK will be 2 * \c wclkDiv BLCK periods.
//!           Valid values for \c wclkDiv are integers in the range [1, 1023],
//!           both included.
//! \param bclkDiv is the desired bit clock (BCLK) divider.
//!        I.e. the number of ACLK periods in one BCLK period. Valid values are
//!        integers in the range [2, 1024], both included.
//!
//! \return None.
//
//****************************************************************************
__STATIC_INLINE void I2SConfigureClocks(uint32_t base,
                                        bool isController,
                                        bool invertWclk,
                                        bool dualPhase,
                                        uint32_t cclkDiv,
                                        uint32_t wclkDiv,
                                        uint32_t bclkDiv)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));
    ASSERT(cclkDiv <= 1024);
    ASSERT(cclkDiv >= 2);
    ASSERT(wclkDiv <= 1023);
    ASSERT(wclkDiv >= 1);
    ASSERT(bclkDiv <= 1024);
    ASSERT(bclkDiv >= 2);

    // Setup register WCLK and BCLK Source
    HWREGB(I2S_BASE + I2S_O_AIFWCLKSRC) = ((isController ? I2S_AIFWCLKSRC_WBCLKSRC_INT : I2S_AIFWCLKSRC_WBCLKSRC_EXT) |
                                           (invertWclk ? I2S_AIFWCLKSRC_WCLKINV : 0));

    // Configure internal clocks, if internal clocks are to be used
    if (isController)
    {

        // Make sure to compensate the WCLK division factor if using single
        // phase format.
        if (dualPhase == false)
        {
            wclkDiv -= 1;
        }

        // Write the clock division factors.
        // A value of 0 is interpreted as 1024 for CCLK and BCLK.
        HWREG(I2S_BASE + I2S_O_AIFMCLKDIV) = (cclkDiv == 1024 ? 0 : cclkDiv);
        HWREG(I2S_BASE + I2S_O_AIFWCLKDIV) = wclkDiv;
        HWREG(I2S_BASE + I2S_O_AIFBCLKDIV) = (bclkDiv == 1024 ? 0 : bclkDiv);

        // Configure the WCLK format and disable CCLK, WCLK and BCLK
        HWREG(I2S_BASE + I2S_O_AIFCLKCTL) = (dualPhase ? (1 << I2S_AIFCLKCTL_WCLKPHASE_S)
                                                       : (0 << I2S_AIFCLKCTL_WCLKPHASE_S));
    }
}

//*****************************************************************************
//
//! \brief Enable the I2S controller clocks (CCLK, WCLK and BCLK).
//!
//! Use this function to enable the controller clocks CCLK, WCLK and BCLK
//! (internally generated).
//!
//! \note The internal I2S clocks must have been configured using
//!       \ref I2SConfigureClocks() with the \c isController parameter set to
//!       \c true.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SEnableControllerClocks(uint32_t base)
{
    // Enable CCLK, WCLK and BCLK
    HWREG(I2S_BASE + I2S_O_AIFCLKCTL) |= I2S_AIFCLKCTL_MEN | I2S_AIFCLKCTL_WBEN;
}

//*****************************************************************************
//
//! \brief Disable the I2S controller clocks (CCLK, WCLK and BCLK).
//!
//! Use this function to disable the controller clocks CCLK, WCLK and BCLK
//! (internally generated).
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SDisableControllerClocks(uint32_t base)
{
    // Disable CCLK, WCLK and BCLK
    HWREG(I2S_BASE + I2S_O_AIFCLKCTL) &= ~(I2S_AIFCLKCTL_MEN | I2S_AIFCLKCTL_WBEN);
}

//****************************************************************************
//
//! \brief Set the next input buffer pointer.
//!
//! The next pointer should always be written while the DMA is using the
//! previously written pointer. If not written in time, an \ref I2S_INT_PTR_ERR
//! will occur and all inputs and outputs will be disabled.
//! This function assumes \c nextPointer is pointing to a valid address.
//!
//! \note It is recommended that the pointer update is done in an interrupt
//! context to ensure that the update is performed before the buffer is full.
//!
//! \param base is the base address of the I2S module.
//! \param nextPointer is the address of the data.
//!
//! \return None.
//!
//! \sa I2SSetOutPointer()
//
//****************************************************************************
__STATIC_INLINE void I2SSetInPointer(uint32_t base, uint32_t nextPointer)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    HWREG(I2S_BASE + I2S_O_AIFINPTNXT) = nextPointer;
}

//****************************************************************************
//
//! \brief Set the next output buffer pointer.
//!
//! The next pointer should always be written while the DMA is using the
//! previously written pointer. If not written in time, an \ref I2S_INT_PTR_ERR
//! will occur and all inputs and outputs will be disabled.
//! This function assumes \c nextPointer is pointing to a valid address.
//!
//! \note It is recommended that the pointer update is done in an interrupt
//! context to ensure that the update is performed before the buffer is full.
//!
//! \param base is the base address of the I2S module.
//! \param nextPointer is the address of the data.
//!
//! \return None.
//!
//! \sa I2SSetInPointer()
//
//****************************************************************************
__STATIC_INLINE void I2SSetOutPointer(uint32_t base, uint32_t nextPointer)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    HWREG(I2S_BASE + I2S_O_AIFOPTNXT) = nextPointer;
}

//****************************************************************************
//
//! \brief Get value of the next input pointer.
//!
//! \param base is the base address of the I2S module.
//!
//! \return the value of the next input pointer.
//
//****************************************************************************
__STATIC_INLINE uint32_t I2SGetInPointerNext(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    return (HWREG(I2S_BASE + I2S_O_AIFINPTNXT));
}

//****************************************************************************
//
//! \brief Get value of the next output pointer.
//!
//! \param base is the base address of the I2S module.
//!
//! \return the value of the next output pointer.
//
//****************************************************************************
__STATIC_INLINE uint32_t I2SGetOutPointerNext(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    return (HWREG(I2S_BASE + I2S_O_AIFOPTNXT));
}

//****************************************************************************
//
//! \brief Get value of the current input pointer.
//!
//! \param base is the base address of the I2S module.
//!
//! \return the value of the current input pointer.
//
//****************************************************************************
__STATIC_INLINE uint32_t I2SGetInPointer(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    return (HWREG(I2S_BASE + I2S_O_AIFINPTR));
}

//****************************************************************************
//
//! \brief Get value of the current output pointer.
//!
//! \param base is the base address of the I2S module.
//!
//! \return the value of the current output pointer.
//
//****************************************************************************
__STATIC_INLINE uint32_t I2SGetOutPointer(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    return (HWREG(I2S_BASE + I2S_O_AIFOUTPTR));
}

//*****************************************************************************
//
//! \brief Configure the input sample stamp trigger.
//!
//! Use this function to configure the input sample stamp trigger.
//!
//! \param base is the base address of the I2S module.
//! \param trigValue value used to set the trigger.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SConfigureInSampleStampTrigger(uint32_t base, uint16_t trigValue)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Setup the sample stamp trigger for input streams
    HWREGH(I2S_BASE + I2S_O_STMPINTRIG) = trigValue;
}

//*****************************************************************************
//
//! \brief Configure the output sample stamp trigger.
//!
//! Use this function to configure the output sample stamp trigger.
//!
//! \param base is the base address of the I2S module.
//! \param trigValue value used to set the trigger.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SConfigureOutSampleStampTrigger(uint32_t base, uint16_t trigValue)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Setup the sample stamp trigger for output streams
    HWREGH(I2S_BASE + I2S_O_STMPOTRIG) = trigValue;
}

//*****************************************************************************
//
//! \brief Configure the WCLK counter period.
//!
//! Use this function to configure the period of the WCLK counter.
//!
//! \param base is the base address of the I2S module.
//! \param period value used to define when the WCLK counter should reset. This
//!        should be configured the size of the sample buffer, in number of
//!        frames.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SConfigureWclkCounterPeriod(uint32_t base, uint16_t period)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    // Configure the WCLK counter period
    HWREGH(I2S_BASE + I2S_O_STMPWPER) = period;
}

//*****************************************************************************
//
//! \brief Confiugre the WCLK counter value.
//!
//! \param base is the base address of the I2S module.
//! \param value is the offset to add to the counter (this value can be
//!        negative).
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SConfigureWclkCounter(uint32_t base, int16_t value)
{
    uint16_t minusValue;

    // Check the arguments
    ASSERT(I2SBaseValid(base));

    if (value >= 0)
    {
        HWREGH(I2S_BASE + I2S_O_STMPWADD) = value;
    }
    else
    {
        minusValue                        = (uint16_t)(-value);
        HWREGH(I2S_BASE + I2S_O_STMPWADD) = HWREGH(I2S_BASE + I2S_O_STMPWPER) - minusValue;
    }
}

//*****************************************************************************
//
//! \brief Reset the WCLK count.
//!
//! \param base is the base address of the I2S module.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SResetWclkCounter(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    HWREGH(I2S_BASE + I2S_O_STMPWSET) = 0;
}

//*****************************************************************************
//
//! \brief Enables the clock source
//!
//! \param base is the base address of the I2S module.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SEnableClk(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    HWREG(I2S_BASE + I2S_O_CLKCFG) |= (I2S_CLKCFG_EN_M);
}

//*****************************************************************************
//
//! \brief Disables the clock source
//!
//! \param base is the base address of the I2S module.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SDisableClk(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    HWREG(I2S_BASE + I2S_O_CLKCFG) &= ~I2S_CLKCFG_EN_M;
}

//*****************************************************************************
//
//! \brief Enables the ADFS (Adaptive Digital Frequency Synthesizer) module
//!
//! \param base is the base address of the I2S module.
//!
//! \pre ADFS must be configured using I2SConfigureAdfs().
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SEnableAdfs(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    HWREG(I2S_BASE + I2S_O_CLKCFG) |= (I2S_CLKCFG_ADFSEN_M);
}

//*****************************************************************************
//
//! \brief Selects the ADFS inpt clock (Fref)
//!
//! \param base is the base address of the I2S module.
//! \param source is the clock source to select:
//! - \ref I2S_CLK_SRC_SOC_CLK
//! - \ref I2S_CLK_SRC_SOC_PLL_CLK
//! - \ref I2S_CLK_SRC_HFXT_CLK
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SSelectAdfsInputClk(uint32_t base, uint32_t source)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    uint32_t temp = HWREG(I2S_BASE + I2S_O_CLKCFG);
    temp &= ~I2S_CLKCFG_CLKSEL_M;
    temp |= (source & I2S_CLKCFG_CLKSEL_M);
    HWREG(I2S_BASE + I2S_O_CLKCFG) = temp;
}

//*****************************************************************************
//
//! \brief Configures the Adaptive Digital Frequency Synthesizer (ADFS) module
//!
//! The ADFS is used to generate arbitrary clock frequency from given input
//! clock by division and adaptive swallowing pattern needed to achieve the
//! required accuracy. The resultant clock frequency mean is equal to the
//! desired value although a significant jitter may occur. The best results are
//! achieved when there is a large factor between the input clock frequency
//! (Fref) and the desired output frequency (Freq). The ADFS is configured with
//! the following parameters:
//! \param tref is the Freq period in picoseconds, represented as a fixed-point
//! number with 17 integer bits and 4 fractional bits.
//! \param div is the divisor used to approximate the ratio between Fref and
//! Freq. It is calculated to minimize the error (delta) between the actual and
//! desired frequency ratios. Should be an integer higher or equal than 1.
//! \param delta is the Error in picoseconds that quantifies how far the
//! achieved period (using the chosen divider) deviates from the desired period.
//! It is represented as a fixed-point number with 13 integer bits and 4
//! fractional bits.
//! \param deltaSign it represents whether delta is negative (1) or non-negative
//! (0).
//!
//! \param base is the base address of the I2S module.
//!
//! The next equations can be used to compute the parameters:
//!
//! @code
//! tref = floor((1 / Fref) * 16)
//!
//! div_temp1 = floor(Fref / Freq);
//! div_temp2 = ceil(Fref / Freq);
//!
//! delta_temp1 = ((1/(Freq*div_temp1))-(1/Fref));
//! delta_temp2 = ((1/(Freq*div_temp2))-(1/Fref));
//!
//! if (abs(delta_temp1) < abs(delta_temp2))
//! {
//!     div = div_temp1;
//!     delta = delta_temp1;
//! }
//! else
//! {
//!     div = div_temp2;
//!     delta = delta_temp2;
//! }
//!
//! deltaSign = (delta < 0) ? 1 : 0;
//!
//! delta = floor(abs(delta)*16)
//! @endcode
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SConfigureAdfs(uint32_t base, uint32_t tref, uint32_t delta, uint32_t deltaSign, uint32_t div)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    HWREG(I2S_BASE + I2S_O_ADFSCTRL1) = (tref & I2S_ADFSCTRL1_TREF_M);
    HWREG(I2S_BASE + I2S_O_ADFSCTRL2) = ((delta & I2S_ADFSCTRL2_DELTA_M) |
                                         ((deltaSign << I2S_ADFSCTRL2_DELTASIGN_S) & I2S_ADFSCTRL2_DELTASIGN_M) |
                                         ((div << I2S_ADFSCTRL2_DIV_S) & I2S_ADFSCTRL2_DIV_M));
}

//*****************************************************************************
//
//! \brief Disables the ADFS (Adaptive Digital Frequency Synthesizer) module
//!
//! \param base is the base address of the I2S module.
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2SDisableAdfs(uint32_t base)
{
    // Check the arguments
    ASSERT(I2SBaseValid(base));

    HWREG(I2S_BASE + I2S_O_CLKCFG) &= ~(I2S_CLKCFG_ADFSEN_M);
}

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif
//****************************************************************************
//
//! Close the Doxygen group.
//! @}
//! @}
//
//****************************************************************************

#endif // ti_devices_i2s__include
