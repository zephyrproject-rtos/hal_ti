/******************************************************************************
 *  Copyright (c) 2022-2023 Texas Instruments Incorporated
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

/*!****************************************************************************
 *  @file       aes.h
 *
 *  @brief      AES module header for CC23X0R5 devices
 *
 *  @anchor     ti_devices_cc23x0r5_aes_overview
 *
 *  This module provides the low-level functions used to access the LAES128
 *  crypto engine.
 ******************************************************************************/

#ifndef __AES_H__
#define __AES_H__

#include <stdint.h>

#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_aes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AES_BLOCK_SIZE                          16U //!< Block size in number of bytes
#define AES_BLOCK_SIZE_WORDS                    (AES_BLOCK_SIZE / 4U)
#define AES_BLOCK_SIZE_MULTIPLE_MASK            0xFFFFFFF0U
#define AES_BLOCK_SIZE_MULTIPLE_LENGTH(len)     ((len)&AES_BLOCK_SIZE_MULTIPLE_MASK)
#define AES_NON_BLOCK_SIZE_MULTIPLE_MASK        0x0000000FU
#define AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(len) ((len)&AES_NON_BLOCK_SIZE_MULTIPLE_MASK)
#define AES_GET_NUM_BLOCKS(len)                 ((len) >> 4)
#define AES_BLOCKS_TO_BYTES(numBlocks)          ((numBlocks) << 4)

#define AES_DOUBLE_BLOCK_SIZE_MULTIPLE_MASK (size_t)(0xFFFFFFE0UL)

#define AES_IV_LENGTH_BYTES  AES_BLOCK_SIZE
#define AES_TAG_LENGTH_BYTES AES_BLOCK_SIZE

#define AES_128_KEY_LENGTH_BYTES (128U / 8U)

#define IS_WORD_ALIGNED(ptr) (((uintptr_t)(ptr) << 30) == 0U)

#define AES_ICLR_ALL \
    ((uint32_t)AES_ICLR_AESDONE | (uint32_t)AES_ICLR_AESSTART | (uint32_t)AES_ICLR_CHADONE | (uint32_t)AES_ICLR_CHBDONE)

typedef union
{
    uint32_t words[4];
    uint8_t bytes[16];
} AES_BlockWordAligned;

/*! @cond NODOC */

/*!
 *  @brief Process word-aligned data for CBC-MAC or CMAC
 *
 *  @note  \c input cannot be NULL. AUTOCFG.BUSHALT must be enabled.
 *
 *  @param [in] input      Pointer word-aligned input
 *  @param [in] numBlocks  Number of 16-byte blocks of data to process
 *
 */
void AESProcessAlignedBlocksCMAC(const uint32_t *input, uint32_t numBlocks);

/*!
 *  @brief Process word-aligned data for CTR
 *
 *  @note  \c input and \c output cannot be NULL. AUTOCFG.BUSHALT must be enabled.
 *
 *  @param [in]  input      Pointer word-aligned input
 *  @param [out] output     Pointer word-aligned output
 *  @param [in]  numBlocks  Number of 16-byte blocks of data to process
 *
 */
void AESProcessAlignedBlocksCTR(const uint32_t *input, uint32_t *output, uint32_t numBlocks);

/*!
 *  @brief Process word-aligned data for ECB or CBC
 *
 *  @note  \c input and \c output cannot be NULL. AUTOCFG.BUSHALT must be enabled.
 *
 *  @param [in]  input      Pointer word-aligned input
 *  @param [out] output     Pointer word-aligned output
 *  @param [in]  numBlocks  Number of 16-byte blocks of data to process
 *
 */
void AESProcessAlignedBlocksECB(const uint32_t *input, uint32_t *output, uint32_t numBlocks);

/*!
 *  @brief Copy a 16-byte block of data
 *
 *      Copies a 16-byte block of data from the memory location pointed to by
 *      \c src to the memory location pointed to by \c dst. If \c src and \c dst
 *      are both word-aligned, the memory contents will be copied in words for
 *      optimal performance. If either \c src or \c dst are not word-aligned,
 *      the memory contents will be copied byte-by-byte.
 *
 *  @note  \c src and \c dst cannot be NULL.
 *
 *  @param [out] dst    Pointer to the memory location to copy to
 *  @param [in]  src    Pointer to the memory location to copy from
 *
 */
void AESCopyBlock(void *dst, const void *src);

/*!
 *  @brief Write AES key
 *
 *      Writes the given 128-bit key to the AES KEY0..KEY3 registers.
 *
 *  @param [in] key     Array containing the key material.
 *
 */
__STATIC_INLINE void AESWriteKEY(const uint8_t key[16])
{
    AESCopyBlock((void *)(AES_BASE + AES_O_KEY0), key);
}

/*!
 *  @brief Write AES Buffer registers
 *
 *      Writes the given values to the AES BUF0..BUF3 registers.
 *
 *  @param [in] buf     Array containing the values to be written to the
 *                      buffer registers.
 *
 */
__STATIC_INLINE void AESWriteBUF(const uint8_t buf[16])
{
    AESCopyBlock((void *)(AES_BASE + AES_O_BUF0), buf);
}

/*!
 *  @brief Write AES Buffer registers
 *
 *      Writes the given values to the AES BUF0..BUF3 registers.
 *
 *  @param [in] buf     Word-aligned array containing the values to be written to the
 *                      buffer registers.
 *
 */
__STATIC_INLINE void AESWriteBUF32(const uint32_t buf[4])
{
    HWREG(AES_BASE + AES_O_BUF0) = buf[0];
    HWREG(AES_BASE + AES_O_BUF1) = buf[1];
    HWREG(AES_BASE + AES_O_BUF2) = buf[2];
    HWREG(AES_BASE + AES_O_BUF3) = buf[3];
}

/*!
 *  @brief Read AES Buffer registers
 *
 *      Reads the contents from the AES BUF0..BUF3 registers.
 *
 *  @param [out] buf    Array where the buffer contents will be written to.
 *
 */
__STATIC_INLINE void AESReadBUF(uint8_t buf[16])
{
    AESCopyBlock(buf, (const void *)(AES_BASE + AES_O_BUF0));
}

/*!
 *  @brief Read AES Buffer registers
 *
 *      Reads the contents from the AES BUF0..BUF3 registers.
 *
 *  @param [out] buf    Word-aligned array where the buffer contents will be written to.
 *
 */
__STATIC_INLINE void AESReadBUF32(uint32_t buf[4])
{
    buf[0] = HWREG(AES_BASE + AES_O_BUF0);
    buf[1] = HWREG(AES_BASE + AES_O_BUF1);
    buf[2] = HWREG(AES_BASE + AES_O_BUF2);
    buf[3] = HWREG(AES_BASE + AES_O_BUF3);
}

/*!
 *  @brief Write AES Text Word XOR registers
 *
 *      Writes the given values to the AES TXTX0..TXTX3 registers.
 *
 *  @param [in] txtxor  Array containing the values to be written to the
 *                      TXTX registers.
 *
 */
__STATIC_INLINE void AESWriteTXTXOR(const uint8_t txtxor[16])
{
    AESCopyBlock((void *)(AES_BASE + AES_O_TXTX0), txtxor);
}

/*!
 *  @brief Write AES Text Word XOR registers
 *
 *      Writes the given values to the AES TXTX0..TXTX3 registers.
 *
 *  @param [in] txtxor  Word-aligned array containing the values to be written to the
 *                      TXTX registers.
 *
 */
__STATIC_INLINE void AESWriteTXTXOR32(const uint32_t txtxor[4])
{
    HWREG(AES_BASE + AES_O_TXTX0) = txtxor[0];
    HWREG(AES_BASE + AES_O_TXTX1) = txtxor[1];
    HWREG(AES_BASE + AES_O_TXTX2) = txtxor[2];
    HWREG(AES_BASE + AES_O_TXTX3) = txtxor[3];
}

/*!
 *  @brief Read Text Word XOR Buffer Word registers
 *
 *      Reads the contents from the AES TXTXBUF0..TXTXBUF0 registers.
 *
 *  @param [out] txtxbuf    Array where the TXTXBUF register contents will be
 *                          written to.
 *
 */
__STATIC_INLINE void AESReadTXTXBUF(uint8_t txtxbuf[16])
{
    AESCopyBlock(txtxbuf, (const void *)(AES_BASE + AES_O_TXTXBUF0));
}

/*!
 *  @brief Write AES Text Word registers
 *
 *      Writes the given values to the AES TXT0..TXT3 registers.
 *
 *  @param [in] txt     Array containing the values to be written to the
 *                      TXT registers.
 *
 */
__STATIC_INLINE void AESWriteTXT(const uint8_t txt[16])
{
    AESCopyBlock((void *)(AES_BASE + AES_O_TXT0), txt);
}

/*!
 *  @brief Write AES Text Word registers
 *
 *      Writes the given values to the AES TXT0..TXT3 registers.
 *
 *  @param [in] txt     Word-aligned array containing the values to be written to the
 *                      TXT registers.
 *
 */
__STATIC_INLINE void AESWriteTXT32(const uint32_t txt[4])
{
    HWREG(AES_BASE + AES_O_TXT0) = txt[0];
    HWREG(AES_BASE + AES_O_TXT1) = txt[1];
    HWREG(AES_BASE + AES_O_TXT2) = txt[2];
    HWREG(AES_BASE + AES_O_TXT3) = txt[3];
}

/*!
 *  @brief Read AES Text Word registers
 *
 *      Reads the contents of the AES TXT0..TXT3 registers.
 *
 *  @param [out] txt    Array where the values from the TXT registers
 *                      will be written to.
 *
 */
__STATIC_INLINE void AESReadTXT(uint8_t txt[16])
{
    AESCopyBlock(txt, (const void *)(AES_BASE + AES_O_TXT0));
}

/*!
 *  @brief Read AES Text Word registers
 *
 *      Reads the contents of the AES TXT0..TXT3 registers.
 *
 *  @param [out] txt    Word-aligned array where the values from the TXT registers
 *                      will be written to.
 *
 */
__STATIC_INLINE void AESReadTXT32(uint32_t txt[4])
{
    txt[0] = HWREG(AES_BASE + AES_O_TXT0);
    txt[1] = HWREG(AES_BASE + AES_O_TXT1);
    txt[2] = HWREG(AES_BASE + AES_O_TXT2);
    txt[3] = HWREG(AES_BASE + AES_O_TXT3);
}

/*!
 *  @brief Write AES Tag
 *
 *      Writes the given Tag to the crypto engine.
 *
 *  @param [in] tag     Array containing the Tag.
 *
 */
__STATIC_INLINE void AESWriteTag(const uint8_t tag[16])
{
    AESWriteTXT(tag);
}

/*!
 *  @brief Write AES Tag
 *
 *      Writes the given Tag to the crypto engine.
 *
 *  @param [in] tag     Array containing the Tag.
 *
 */
__STATIC_INLINE void AESWriteTag32(const uint32_t tag[4])
{
    AESWriteTXT32(tag);
}

/*!
 *  @brief Read AES Tag
 *
 *      Reads the Tag from the crypto engine.
 *
 *  @param [out] tag    Array where the Tag will be written to.
 *
 */
__STATIC_INLINE void AESReadTag(uint8_t tag[16])
{
    AESReadTXT(tag);
}

/*!
 *  @brief Read AES Tag
 *
 *      Reads the Tag from the crypto engine.
 *
 *  @param [out] tag    Word-aligned array where the Tag will be written to.
 *
 */
__STATIC_INLINE void AESReadTag32(uint32_t tag[4])
{
    AESReadTXT32(tag);
}

/*!
 *  @brief Set AES AutoCfg
 *
 *      Sets the configuration for automatic HW updates to TXT and BUF.
 *
 *  @param [in] autoCfg Specifies what configuration to be set.
 *      - @ref AES_AUTOCFG_CHBDONECLR_M
 *      - @ref AES_AUTOCFG_CHADONECLR_M
 *      - @ref AES_AUTOCFG_ECBSTARTCLR_M
 *      - @ref AES_AUTOCFG_ECBDONECLR_M
 *      - @ref AES_AUTOCFG_BUSHALT_M
 *      - @ref AES_AUTOCFG_CTRSIZE_M
 *      - @ref AES_AUTOCFG_CTRALIGN_M
 *      - @ref AES_AUTOCFG_CTRENDIAN_M
 *      - @ref AES_AUTOCFG_TRGTXT_M
 *      - @ref AES_AUTOCFG_AESSRC_M
 *      - @ref AES_AUTOCFG_TRGAES_M
 *
 */
__STATIC_INLINE void AESSetAUTOCFG(uint32_t autoCfg)
{
    HWREG(AES_BASE + AES_O_AUTOCFG) = autoCfg;
}

/*!
 *  @brief Clear the ECB trigger mask in AUTOCFG
 *
 *      Clears the ECB trigger mask in AUTOCFG
 *
 */
__STATIC_INLINE void AESClearAUTOCFGTrigger(void)
{
    /* Read the current AUTOCFG value */
    uint32_t autoCfg = HWREG(AES_BASE + AES_O_AUTOCFG);

    /* Clear the TRGECB bits */
    autoCfg &= (uint32_t)~AES_AUTOCFG_TRGAES_M;

    HWREG(AES_BASE + AES_O_AUTOCFG) = autoCfg;
}

/*!
 *  @brief Clear the BUSHALT enable in AUTOCFG
 *
 *      Clears the BUSHALT enable in AUTOCFG
 *
 */
__STATIC_INLINE void AESClearAUTOCFGBusHalt(void)
{
    /* Read the current AUTOCFG value */
    uint32_t autoCfg = HWREG(AES_BASE + AES_O_AUTOCFG);

    /* Clear the BUSHALT bit */
    autoCfg &= (uint32_t)~AES_AUTOCFG_BUSHALT_M;

    HWREG(AES_BASE + AES_O_AUTOCFG) = autoCfg;
}

/*!
 *  @brief Get AES Status
 *
 *      Gets the state of the AES Accelerator.
 *
 *  @return The state of the AES Accelerator:
 *      - @ref AES_STA_STATE_BUSY
 *      - @ref AES_STA_STATE_IDLE
 */
__STATIC_INLINE uint32_t AESGetStatus(void)
{
    return (HWREG(AES_BASE + AES_O_STA) & AES_STA_STATE_M);
}

/*!
 *  @brief Set AES Trigger
 *
 *      Sets the operations to be manually triggered.
 *
 *  @param [in] triggerMask Specifies which operations to be triggered.
 *      - @ref AES_TRG_DMACHA
 *      - @ref AES_TRG_DMACHB
 *      - @ref AES_TRG_AESOP_TXTXBUF
 *      - @ref AES_TRG_AESOP_BUF
 *      - @ref AES_TRG_AESOP_TXT
 *
 */
__STATIC_INLINE void AESSetTrigger(uint32_t triggerMask)
{
    HWREG(AES_BASE + AES_O_TRG) = triggerMask;
}

/*!
 *  @brief Abort AES operation
 *
 *      Aborts an ongoing AES operation.
 *
 *  @note   An abort will clear TXT, BUF, DMA, AUTOCFG registers.
 *
 */
__STATIC_INLINE void AESAbort(void)
{
    HWREG(AES_BASE + AES_O_ABORT) = AES_ABORT_ABORTAES_SET;
}

/*!
 *  @brief Clear AES TXT registers
 *
 *      Clears the contents of TXT registers, if STATE = IDLE.
 *      Else, the contents remain unchanged.
 *
 */
__STATIC_INLINE void AESClearTXT(void)
{
    HWREG(AES_BASE + AES_O_CLR) = AES_CLR_TXT_M;
}

/*!
 *  @brief Clear AES BUF registers
 *
 *      Clears the contents of BUF registers, if STATE = IDLE.
 *      Else, the contents remain unchanged.
 *
 */
__STATIC_INLINE void AESClearBUF(void)
{
    HWREG(AES_BASE + AES_O_CLR) = AES_CLR_BUF_M;
}

/*!
 *  @brief Clear AES TXT & BUF registers
 *
 *      Clears the contents of TXT and BUF registers, if STATE = IDLE.
 *      Else, the contents remain unchanged.
 *

 */
__STATIC_INLINE void AESClearTXTAndBUF(void)
{
    HWREG(AES_BASE + AES_O_CLR) = AES_CLR_TXT_M | AES_CLR_BUF_M;
}

/*!
 *  @brief Write AES IV
 *
 *      Writes the given IV to the crypto engine.
 *
 *  @param [in] iv      Array containing the IV.
 *
 */
__STATIC_INLINE void AESWriteIV(const uint8_t iv[16])
{
    AESWriteTXT(iv);
}

/*!
 *  @brief Write AES IV
 *
 *      Writes the given IV to the crypto engine.
 *
 *  @param [in] iv      Word-aligned array containing the IV.
 *
 */
__STATIC_INLINE void AESWriteIV32(const uint32_t iv[4])
{
    AESWriteTXT32(iv);
}

/*!
 *  @brief Clear AES IV
 *
 *      Clears the IV in crypto engine.
 *
 */
__STATIC_INLINE void AESClearIV(void)
{
    AESClearTXT();
}

/*!
 *  @brief Read AES IV
 *
 *      Reads the IV from the crypto engine.
 *
 *  @param [out] iv     Array where the IV will be written to.
 *
 */
__STATIC_INLINE void AESReadIV(uint8_t iv[16])
{
    AESReadTXT(iv);
}

/*!
 *  @brief Read AES IV
 *
 *      Reads the IV from the crypto engine.
 *
 *  @param [out] iv     Word-aligned array where the IV will be written to.
 *
 */
__STATIC_INLINE void AESReadIV32(uint32_t iv[4])
{
    AESReadTXT32(iv);
}

/*!
 *  @brief Get AES Raw Interrupt Status
 *
 *      Gets the current Raw Interrupt Status
 *
 *  @return The Raw Interrupt Status:
 *      - @ref AES_RIS_CHBDONE_M
 *      - @ref AES_RIS_CHADONE_M
 *      - @ref AES_RIS_ECBSTART_M
 *      - @ref AES_RIS_ECBDONE_M
 */
__STATIC_INLINE uint32_t AESGetRawInterruptStatus(void)
{
    return HWREG(AES_BASE + AES_O_RIS);
}

/*!
 *  @brief Set AES Interrupt
 *
 *      Sets one or more AES Interrupts.
 *
 *  @param [in] intFlags    Specifies which interrupt(s) to be set.
 *      - @ref AES_ISET_CHBDONE_M
 *      - @ref AES_ISET_CHADONE_M
 *      - @ref AES_ISET_ECBSTART_M
 *      - @ref AES_ISET_ECBDONE_M
 *

 */
__STATIC_INLINE void AESSetInterrupt(uint32_t intFlags)
{
    HWREG(AES_BASE + AES_O_ISET) = intFlags;
}

/*!
 *  @brief Clear AES Interrupt
 *
 *      Clears one or more AES Interrupts.
 *
 *  @param [in] intFlags    Specifies which interrupt(s) to be cleared.
 *      - @ref AES_ICLR_CHBDONE_M
 *      - @ref AES_ICLR_CHADONE_M
 *      - @ref AES_ICLR_AESSTART_M
 *      - @ref AES_ICLR_AESDONE_M
 *
 */
__STATIC_INLINE void AESClearInterrupt(uint32_t intFlags)
{
    HWREG(AES_BASE + AES_O_ICLR) = intFlags;
}

/*!
 *  @brief Get AES Masked Interrupt Status
 *
 *      Gets the Masked Interrupt Status.
 *
 *  @return The Masked Interrupt Status.
 *      - @ref AES_MIS_CHBDONE_M
 *      - @ref AES_MIS_CHADONE_M
 *      - @ref AES_MIS_ECBSTART_M
 *      - @ref AES_MIS_ECBDONE_M
 */
__STATIC_INLINE uint32_t AESGetMaskedInterruptStatus(void)
{
    return HWREG(AES_BASE + AES_O_MIS);
}

/*!
 *  @brief Set AES IMASK
 *
 *      Enables/disables interrupts.
 *
 *  @param [in] intFlags    Specifies which interrupts to be enabled/disabled.
 *      - @ref AES_IMASK_CHBDONE_M
 *      - @ref AES_IMASK_CHADONE_M
 *      - @ref AES_IMASK_ECBSTART_M
 *      - @ref AES_IMASK_ECBDONE_M
 *
 */
__STATIC_INLINE void AESSetIMASK(uint32_t intFlags)
{
    HWREG(AES_BASE + AES_O_IMASK) = intFlags;
}

/*!
 *  @brief Setup AES DMA
 *
 *      Setup the DMA for the AES engine
 *
 *  @param [in] dmaConfig       Specifies the DMA configuration for done side-effects,
 *                              addresses and triggers for DMA channel A & B.
 *      - @ref AES_DMA_DONEACT_M
 *      - @ref AES_DMA_ADRCHA_M
 *      - @ref AES_DMA_TRGCHA_M
 *      - @ref AES_DMA_ADRCHB_M
 *      - @ref AES_DMA_TRGCHB_M
 *
 */
__STATIC_INLINE void AESSetupDMA(uint32_t dmaConfig)
{
    HWREG(AES_BASE + AES_O_DMA) = dmaConfig;
}

/*!
 *  @brief Disable DMA
 *
 *      Disables the DMA for the crypto engine
 *
 */
__STATIC_INLINE void AESDisableDMA(void)
{
    HWREG(AES_BASE + AES_O_DMA) = AES_DMA_DONEACT_DIS | AES_DMA_TRGCHB_DIS | AES_DMA_TRGCHA_DIS;
}

/*! @endcond */

#ifdef __cplusplus
}
#endif

#endif /* __AES_H__ */
