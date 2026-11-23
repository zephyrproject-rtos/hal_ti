/* eip130_token_crypto.h
 *
 * Security Module Token helper functions
 * - Crypto token related functions and definitions
 *
 * This module can convert a set of parameters into a Security Module Command
 * token, or parses a set of parameters from a Security Module Result token.
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : DDK-130_bsd                                              */
/*   Version       : 4.1.1                                                    */
/*   Configuration : DDK_EIP130_BSD                                           */
/*                                                                            */
/*   Date          : 2023-Mar-10                                              */
/*                                                                            */
/* Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are permitted provided that the following conditions are     */
/* met:                                                                       */
/*                                                                            */
/* 1. Redistributions of source code must retain the above copyright          */
/* notice, this list of conditions and the following disclaimer.              */
/*                                                                            */
/* 2. Redistributions in binary form must reproduce the above copyright       */
/* notice, this list of conditions and the following disclaimer in the        */
/* documentation and/or other materials provided with the distribution.       */
/*                                                                            */
/* 3. Neither the name of the copyright holder nor the names of its           */
/* contributors may be used to endorse or promote products derived from       */
/* this software without specific prior written permission.                   */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       */
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT           */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,      */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       */
/* -------------------------------------------------------------------------- */

#ifndef INCLUDE_GUARD_EIP130TOKEN_CRYPTO_H
#define INCLUDE_GUARD_EIP130TOKEN_CRYPTO_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/MailboxControl/src/c_eip130.h>               /* EIP-130 configuration */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */

/* Symmetric Crypto cipher algorithms */
#define EIP130TOKEN_CRYPTO_ALGO_AES         0x00U
#define EIP130TOKEN_CRYPTO_ALGO_DES         0x01U
#define EIP130TOKEN_CRYPTO_ALGO_3DES        0x02U
#define EIP130TOKEN_CRYPTO_ALGO_CHACHA20    0x07U
#define EIP130TOKEN_CRYPTO_ALGO_SM4         0x08U
#define EIP130TOKEN_CRYPTO_ALGO_ARIA        0x09U

/* Symmetric Crypto cipher modes */
#define EIP130TOKEN_CRYPTO_MODE_ECB         0x00U
#define EIP130TOKEN_CRYPTO_MODE_CBC         0x01U
#define EIP130TOKEN_CRYPTO_MODE_CTR         0x02U
#define EIP130TOKEN_CRYPTO_MODE_ICM         0x03U
#define EIP130TOKEN_CRYPTO_MODE_f8          0x04U
#define EIP130TOKEN_CRYPTO_MODE_CCM         0x05U
#define EIP130TOKEN_CRYPTO_MODE_XTS         0x06U
#define EIP130TOKEN_CRYPTO_MODE_GCM         0x07U

#define EIP130TOKEN_CRYPTO_MODE_ENCRYPT     0x00U
#define EIP130TOKEN_CRYPTO_MODE_AEAD        0x01U


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_Operation
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Algorithm
 *     Operation algorithm. Must be one of EIP130TOKEN_CRYPTO_ALGO_*
 *
 * Mode
 *     Mode of operation. Must be one of EIP130TOKEN_CRYPTO_MODE_*
 *
 * fEncrypt
 *     true = Encrypt
 *     false = Decrypt
 *
 * DataLength
 *     Number of bytes to process.
 *     Must be a multiple of the blocksize.
 */
static inline void
Eip130Token_Command_Crypto_Operation(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t Algorithm,
        const uint8_t Mode,
        const bool fEncrypt,
        const uint32_t DataLengthInBytes)
{
    CommandToken_p->W[0] = EIP130TOKEN_OPCODE_ENCRYPTION;
    CommandToken_p->W[2] = (Eip130TokenWord_t)DataLengthInBytes;

    /* Algorithm, Mode and direction */
    CommandToken_p->W[11] = ((Eip130TokenWord_t)Algorithm & MASK_4_BITS) +
                            (((Eip130TokenWord_t)Mode & MASK_4_BITS) << 4);
    if (fEncrypt)
    {
        CommandToken_p->W[11] |= BIT_15;
    }
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetDataAddresses
 *
 * This function sets the Data address for Input and Output to use.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * InputDataAddress
 *     Input data Address.
 *
 * InputDataLengthInBytes
 *     Input data length.
 *
 * OutputDataAddress
 *     Output data Address.
 *
 * OutputDataLengthInBytes
 *     Output data length.
 */
static inline void
Eip130Token_Command_Crypto_SetDataAddresses(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const Eip130TokenDmaSize_t InputDataLengthInBytes,
        const Eip130TokenDmaAddress_t OutputDataAddress,
        const Eip130TokenDmaSize_t OutputDataLengthInBytes)
{
    CommandToken_p->W[3] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[4] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[5] = (Eip130TokenWord_t)(InputDataLengthInBytes);
    CommandToken_p->W[6] = (Eip130TokenWord_t)(OutputDataAddress);
    CommandToken_p->W[7] = (Eip130TokenWord_t)(OutputDataAddress >> 32);
    CommandToken_p->W[8] = (Eip130TokenWord_t)(OutputDataLengthInBytes);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetKeyLength
 *
 * This function sets the coded length of the AES or ARIA key.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * KeyLengthInBytes
 *     Key length.
 */
static inline void
Eip130Token_Command_Crypto_SetKeyLength(
        Eip130Token_Command_t * const CommandToken_p,
        const uint32_t KeyLengthInBytes)
{
    Eip130TokenWord_t CodedKeyLen;

    /* Coded key length only needed for AES and ARIA */
    switch (KeyLengthInBytes)
    {
    case (128 / 8):
        CodedKeyLen = 1U;
        break;

    case (192 / 8):
        CodedKeyLen = 2U;
        break;

    case (256 / 8):
        CodedKeyLen = 3U;
        break;

    default:
        CodedKeyLen = 0U;
        break;
    }
    CommandToken_p->W[11] |= (CodedKeyLen << 16);
}


#ifdef EIP130_ENABLE_SYM_ALGO_CHACHA20
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_ChaCha20_SetKeyLength
 *
 * This function sets the coded length of the ChaCha20 key.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * KeyLengthInBytes
 *     Key length.
 */
static inline void
Eip130Token_Command_Crypto_ChaCha20_SetKeyLength(
        Eip130Token_Command_t * const CommandToken_p,
        const uint32_t KeyLengthInBytes)
{
    /* Key length for ChaCha20 */
    if (KeyLengthInBytes == (128U / 8U))
    {
        CommandToken_p->W[11] |= BIT_16;
    }
}
#endif


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetASLoadKey
 *
 * This function sets the Asset Store Load location for the key and activates
 * its use. This also disables the use of the key via the token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *     Key Asset Identifier.
 */
static inline void
Eip130Token_Command_Crypto_SetASLoadKey(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[11] |= BIT_8;
    CommandToken_p->W[17]  = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetASLoadIV
 *
 * This function sets the Asset Store Load location for the IV and
 * activates its use. This also disables the use of the IV via the token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *     Input IV Asset Identifier.
 */
static inline void
Eip130Token_Command_Crypto_SetASLoadIV(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[11] |= BIT_9;
    CommandToken_p->W[13]  = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetASSaveIV
 *
 * This function sets the Asset Store Save location for the IV and
 * activates its use.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *     Output IV Asset Identifier.
 */
static inline void
Eip130Token_Command_Crypto_SetASSaveIV(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[11] |= BIT_12;
    CommandToken_p->W[12]  = (Eip130TokenWord_t)AssetId;
}


#if defined(EIP130_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_SM_GCM)
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetNoRandomIV
 *
 * This function sets the "NoRandomIV" indication for GCM operations.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_Crypto_SetNoRandomIV(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[11] |= BIT_14;
}
#endif


#ifdef EIP130_ENABLE_SYM_ALGO_CHACHA20
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetNonceLength
 *
 * This function sets the Nonce length for ChaCha20.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * NonceLengthInBytes
 *     Nonce length.
 */
static inline void
Eip130Token_Command_Crypto_SetNonceLength(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t NonceLengthInBytes)
{
    CommandToken_p->W[11] |= (((Eip130TokenWord_t)NonceLengthInBytes & MASK_4_BITS) << 20);
}
#endif


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_CopyKey
 *
 * This function copies the key from the buffer provided by the caller into
 * the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Key_p
 *     Pointer to the key buffer.
 *
 * KeyLengthInBytes
 *     Key length.
 */
static inline void
Eip130Token_Command_Crypto_CopyKey(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const Key_p,
        const uint32_t KeyLengthInBytes)
{
    Eip130Token_Command_WriteByteArray(CommandToken_p, 17U,
                                       Key_p, KeyLengthInBytes);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_CopyIV
 *
 * This function copies the IV from the buffer provided by the caller into
 * the command token. The IV length is always 16 bytes.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * IV_p
 *     Pointer to the IV buffer.
 */
static inline void
Eip130Token_Command_Crypto_CopyIV(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const IV_p)
{
    Eip130Token_Command_WriteByteArray(CommandToken_p, 13U, IV_p, 16U);
}


#if defined(EIP130_ENABLE_SYM_ALGO_AES_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_SM4_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_CHACHA20)
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetADAddress
 *
 * This function sets the Associated Data address and length provided by the
 * caller into the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * InputDataAddress
 *     Input data address of the Associated Data (AAD).
 *
 * DataLengthInBytes
 *     Associated Data length.
 */
static inline void
Eip130Token_Command_Crypto_SetADAddress(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const uint32_t DataLengthInBytes)
{
    CommandToken_p->W[9]  = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[10] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[25] = (Eip130TokenWord_t)(DataLengthInBytes);
}
#endif

#if defined(EIP130_ENABLE_SYM_ALGO_AES_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_SM4_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_CHACHA20)
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_SetADPartAddress
 *
 * This function sets the Associated Data address and length provided by the
 * caller into the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * DataLengthInBytes
 *     Associated Data length.
 */
static inline void
Eip130Token_Command_Crypto_SetADPartLen(
        Eip130Token_Command_t * const CommandToken_p,
        const uint32_t DataLengthInBytes)
{
    CommandToken_p->W[26] = (Eip130TokenWord_t)(DataLengthInBytes);
}
#endif

#if defined(EIP130_ENABLE_SYM_ALGO_AES_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_SM4_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_CHACHA20)
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_CopyNonce
 *
 * This function copies the Nonce from the buffer provided by the caller into
 * the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Nonce_p
 *     Pointer to the nonce buffer.
 *
 * NonceLengthInBytes
 *     Nonce length.
 */
static inline void
Eip130Token_Command_Crypto_CopyNonce(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const Nonce_p,
        const uint32_t NonceLengthInBytes)
{
    CommandToken_p->W[11] |= (((Eip130TokenWord_t)NonceLengthInBytes & MASK_4_BITS) << 20);

    Eip130Token_Command_WriteByteArray(CommandToken_p, 29U,
                                       Nonce_p, NonceLengthInBytes);
}
#endif


#if defined(EIP130_ENABLE_SYM_ALGO_AES_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_SM4_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_CHACHA20)
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_CopyTag
 *
 * This function copies the Tag from the buffer provided by the caller into
 * the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Tag_p
 *     Pointer to the TAG buffer.
 *
 * TagLengthInBytes
 *     TAG length.
 */
static inline void
Eip130Token_Command_Crypto_CopyTag(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const Tag_p,
        const uint32_t TagLengthInBytes)
{
    CommandToken_p->W[11] |= (((Eip130TokenWord_t)TagLengthInBytes & MASK_5_BITS) << 24);

    if ((CommandToken_p->W[11] & BIT_15) == 0U)
    {
        /* Decrypt operation, so tag is input */
        Eip130Token_Command_WriteByteArray(CommandToken_p, 33U,
                                           Tag_p, TagLengthInBytes);
    }
}
#endif


#ifdef EIP130_ENABLE_SYM_ALGO_AES_F8
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_Copyf8SaltKey
 *
 * This function copies the f8 salt key from the buffer provided by the caller
 * into the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Key_p
 *     Pointer to the f8 salt key buffer.
 *
 * KeyLengthInBytes
 *     The f8 salt key length.
 */
static inline void
Eip130Token_Command_Crypto_Copyf8SaltKey(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const Key_p,
        const uint32_t KeyLengthInBytes)
{
    CommandToken_p->W[11] |= (((Eip130TokenWord_t)KeyLengthInBytes & MASK_5_BITS) << 24);

    Eip130Token_Command_WriteByteArray(CommandToken_p, 29U,
                                       Key_p, KeyLengthInBytes);
}
#endif


#ifdef EIP130_ENABLE_SYM_ALGO_AES_F8
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Crypto_Copyf8IV
 *
 * This function copies the f8 IV from the buffer provided by the caller into
 * the command token. The f8 IV length is always 16 bytes.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * f8IV_p
 *     Pointer to the f8 IV buffer.
 */
static inline void
Eip130Token_Command_Crypto_Copyf8IV(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const f8IV_p)
{
    Eip130Token_Command_WriteByteArray(CommandToken_p, 25U, f8IV_p, 16U);
}
#endif


/*----------------------------------------------------------------------------
 * Eip130Token_Result_Crypto_CopyIV
 *
 * This function copies the IV from the result token to the buffer
 * provided by the caller. The IV length is always 16 bytes.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * Dest_p
 *      Pointer to the buffer to copy the IV to.
 */
static inline void
Eip130Token_Result_Crypto_CopyIV(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * Dest_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p, 2U, 16U, Dest_p);
}


#if defined(EIP130_ENABLE_SYM_ALGO_AES_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_CCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_ARIA_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_SM4_GCM) || \
    defined(EIP130_ENABLE_SYM_ALGO_CHACHA20)
/*----------------------------------------------------------------------------
 * Eip130Token_Result_Crypto_CopyTag
 *
 * This function copies the Tag from the result token to the buffer
 * provided by the caller. The Tag length is always 16 bytes.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * Dest_p
 *      Pointer to the buffer to copy the Tag to.
 */
static inline void
Eip130Token_Result_Crypto_CopyTag(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * Dest_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p, 6U, 16U, Dest_p);
}
#endif


#endif /* INCLUDE_GUARD_EIP130TOKEN_CRYPTO_H */

/* end of file eip130_token_crypto.h */
