/* eip130_token_pk.h
 *
 * Security Module Token helper functions
 * - Public key tokens related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_PK_H
#define INCLUDE_GUARD_EIP130TOKEN_PK_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */

#define EIP130TOKEN_PK_CMD_MAX_HASH_SIZE  4095U

/* Commands for PK operations with assets */
#define EIP130TOKEN_PK_ASSET_CMD_ECDH_ECDSA_KEY_CHECK           0x01U
#define EIP130TOKEN_PK_ASSET_CMD_DH_DSA_KEY_CHECK               0x02U
#define EIP130TOKEN_PK_ASSET_CMD_ECDSA_SIGN                     0x06U
#define EIP130TOKEN_PK_ASSET_CMD_ECDSA_VERIFY                   0x07U
#define EIP130TOKEN_PK_ASSET_CMD_RSA_PKCS_SIGN                  0x08U
#define EIP130TOKEN_PK_ASSET_CMD_RSA_PKCS_VER                   0x09U
#define EIP130TOKEN_PK_ASSET_CMD_RSA_PSS_SIGN                   0x0CU
#define EIP130TOKEN_PK_ASSET_CMD_RSA_PSS_VER                    0x0DU
#define EIP130TOKEN_PK_ASSET_CMD_DH_GEN_PUB_KEY                 0x10U
#define EIP130TOKEN_PK_ASSET_CMD_DH_GEN_PRIV_PUB_KEY            0x11U
#define EIP130TOKEN_PK_ASSET_CMD_DH_GEN_SINGLE_SH_SECR          0x12U
#define EIP130TOKEN_PK_ASSET_CMD_DH_GEN_DUAL_SH_SECR            0x13U
#define EIP130TOKEN_PK_ASSET_CMD_ECDH_ECDSA_GEN_PUB_KEY         0x14U
#define EIP130TOKEN_PK_ASSET_CMD_ECDH_ECDSA_GEN_PRIV_PUB_KEY    0x15U
#define EIP130TOKEN_PK_ASSET_CMD_ECDH_GEN_SINGLE_SH_SECR        0x16U
#define EIP130TOKEN_PK_ASSET_CMD_ECDH_GEN_DUAL_SH_SECR          0x17U
#define EIP130TOKEN_PK_ASSET_CMD_RSA_OAEP_WRAP_STRING           0x18U
#define EIP130TOKEN_PK_ASSET_CMD_RSA_OAEP_WRAP_HASHED           0x19U
#define EIP130TOKEN_PK_ASSET_CMD_RSA_OAEP_UNWRAP_STRING         0x1AU
#define EIP130TOKEN_PK_ASSET_CMD_RSA_OAEP_UNWRAP_HASHED         0x1BU
#define EIP130TOKEN_PK_ASSET_CMD_RSA_PKCS1V15_UNWRAP            0x21U
#define EIP130TOKEN_PK_ASSET_CMD_RSA_PKCS1V15_WRAP              0x22U
#define EIP130TOKEN_PK_ASSET_CMD_CURVE25519_GEN_PUBKEY          0x28U
#define EIP130TOKEN_PK_ASSET_CMD_CURVE25519_GEN_KEYPAIR         0x29U
#define EIP130TOKEN_PK_ASSET_CMD_CURVE25519_GEN_SHARED_SECRET   0x2AU
#define EIP130TOKEN_PK_ASSET_CMD_EDDSA_GEN_PUBKEY               0x2BU
#define EIP130TOKEN_PK_ASSET_CMD_EDDSA_GEN_KEYPAIR              0x2CU
#define EIP130TOKEN_PK_ASSET_CMD_EDDSA_SIGN_INITIAL             0x2DU
#define EIP130TOKEN_PK_ASSET_CMD_EDDSA_SIGN_UPDATE              0x2EU
#define EIP130TOKEN_PK_ASSET_CMD_EDDSA_SIGN_FINAL               0x2FU
#define EIP130TOKEN_PK_ASSET_CMD_EDDSA_VERIFY_INITIAL           0x30U
#define EIP130TOKEN_PK_ASSET_CMD_EDDSA_VERIFY_FINAL             0x31U
#define EIP130TOKEN_PK_ASSET_CMD_SM2DSA_SIGN                    0x32U
#define EIP130TOKEN_PK_ASSET_CMD_SM2DSA_VERIFY                  0x33U
#define EIP130TOKEN_PK_ASSET_CMD_SM2ENC_WRAP                    0x34U
#define EIP130TOKEN_PK_ASSET_CMD_SM2ENC_UNWRAP                  0x35U
#define EIP130TOKEN_PK_ASSET_CMD_SM2KEX_GEN_SH_SECR             0x36U
#define EIP130TOKEN_PK_ASSET_CMD_ECIES_WRAP                     0x38U
#define EIP130TOKEN_PK_ASSET_CMD_ECIES_UNWRAP                   0x39U

/* Commands for PK operations without assets */
#define EIP130TOKEN_PK_CMD_NUMLOAD          0x01U
#define EIP130TOKEN_PK_CMD_NUMSETN          0x03U
#define EIP130TOKEN_PK_CMD_MODEXPE          0x04U
#define EIP130TOKEN_PK_CMD_MODEXPD          0x05U
#define EIP130TOKEN_PK_CMD_MODEXPCRT        0x06U
#define EIP130TOKEN_PK_CMD_ECMONTMUL        0x0AU
#define EIP130TOKEN_PK_CMD_ECCMUL           0x0BU
#define EIP130TOKEN_PK_CMD_ECCADD           0x0CU
#define EIP130TOKEN_PK_CMD_ECDSA_SIGN       0x0FU
#define EIP130TOKEN_PK_CMD_ECDSA_VERIFY     0x10U


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Asset_Command
 *
 * Request to perform a PK operation with assets
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Command
 *      Public Key operation (command) to perform.
 *
 * Nwords
 *      Number of words of the basic vector.
 *
 * Mwords
 *      Number of words of the alternate (shorter) vector.
 *
 * OtherLen
 *      Length of the other data in the token.
 *
 * KeyAssetId
 *     Asset ID of the main key asset.
 *
 * ParamAssetId (optional)
 *     Asset ID of the domain or curve parameters asset.
 *
 * IOAssetId (optional)
 *     Asset ID of the input and/or output of result asset.
 *
 * InputDataAddress
 *      Input data address.
 *
 * InputDataLengthInBytes
 *      Input data length.
 *
 * OutputDataAddress
 *      Output data or Signature address.
 *
 * OutputDataLengthInBytes
 *      Output data or Signature length.
 */
static inline void
Eip130Token_Command_Pk_Asset_Command(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t Command,
        const uint8_t Nwords,
        const uint8_t Mwords,
        const uint8_t OtherLen,
        const Eip130TokenAssetId_t KeyAssetId,
        const Eip130TokenAssetId_t ParamAssetId,
        const Eip130TokenAssetId_t IOAssetId,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const uint16_t InputDataLengthInBytes,
        const Eip130TokenDmaAddress_t OutputDataAddress,
        const uint16_t OutputDataLengthInBytes)
{
    CommandToken_p->W[0]  = (EIP130TOKEN_OPCODE_PUBLIC_KEY |
                             EIP130TOKEN_SUBCODE_PK_WITHASSETS);
    CommandToken_p->W[2]  = ((Eip130TokenWord_t)Command | /* PK operation to perform */
                             ((Eip130TokenWord_t)Nwords << 16) |
                             ((Eip130TokenWord_t)Mwords << 24));
    CommandToken_p->W[3]  = (Eip130TokenWord_t)OtherLen << 8;
    CommandToken_p->W[4]  = (Eip130TokenWord_t)KeyAssetId;     /* asset containing x and y coordinates of pk */
    CommandToken_p->W[5]  = (Eip130TokenWord_t)ParamAssetId;   /* public key parameters: p, a, b, n, base x, base y[, h] */
    CommandToken_p->W[6]  = (Eip130TokenWord_t)IOAssetId;
    CommandToken_p->W[7]  = (((Eip130TokenWord_t)OutputDataLengthInBytes & MASK_12_BITS) << 16 ) |
                             ((Eip130TokenWord_t)InputDataLengthInBytes & MASK_12_BITS);
    CommandToken_p->W[8]  = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[9]  = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[10] = (Eip130TokenWord_t)(OutputDataAddress);
    CommandToken_p->W[11] = (Eip130TokenWord_t)(OutputDataAddress >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Asset_SetAdditionalData
 *
 * This function copies the additional data from the buffer provided by the
 * caller into the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AddData_p
 *      Additional input data address
 *
 * AddDataLengthInBytes
 *      Additional input data length
 */
static inline void
Eip130Token_Command_Pk_Asset_SetAdditionalData(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const AddData_p,
        const uint8_t AddDataLengthInBytes)
{
    Eip130TokenWord_t offset = ((CommandToken_p->W[3] & 0x0FFU) + 3U) & (Eip130TokenWord_t)~3UL;

    CommandToken_p->W[3] &= (Eip130TokenWord_t)~0x0FFUL;
    CommandToken_p->W[3] |= (offset + (Eip130TokenWord_t)AddDataLengthInBytes);
    Eip130Token_Command_WriteByteArray(CommandToken_p,
                                       (uint32_t)(12U + (offset / (uint32_t)sizeof(uint32_t))),
                                       AddData_p,
                                       (uint32_t)AddDataLengthInBytes);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Asset_SetAdditionalOutputData
 *
 * This function sets the AdditionalInput area of the PK token to an output
 * buffer, used in certain PK operations (ECIES).
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * OutputDataAddress
 *      Additional output data address
 *
 * OutputDataSize
 *      Additional input data length
 */
static inline void
Eip130Token_Command_Pk_Asset_SetAdditionalOutputData(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenDmaAddress_t OutputDataAddress,
        const Eip130TokenDmaSize_t OutputDataLengthInBytes)
{
    CommandToken_p->W[12] = (Eip130TokenWord_t)OutputDataLengthInBytes;
    CommandToken_p->W[13] = (Eip130TokenWord_t)(OutputDataAddress);
    CommandToken_p->W[14] = (Eip130TokenWord_t)(OutputDataAddress >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Asset_SetAdditionalAssetId
 *
 * This function copies the specified AssetId to the additional data area of
 * the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AddAssetId
 *      Additional AssetId
 */
static inline void
Eip130Token_Command_Pk_Asset_SetAdditionalAssetId(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AddAssetId)
{
    Eip130TokenWord_t offset = ((CommandToken_p->W[3] & 0x0FFU) + 3U) & (Eip130TokenWord_t)~3UL;

    CommandToken_p->W[3] &= (Eip130TokenWord_t)~0x0FFUL;
    CommandToken_p->W[3] |= (offset + (Eip130TokenWord_t)sizeof(uint32_t));
    CommandToken_p->W[12U + (offset / sizeof(uint32_t))] = (Eip130TokenWord_t)AddAssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Asset_SetAdditionalLength
 *
 * This function copies the specified length to the additional data area of
 * the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AddLength
 *      Additional length information
 */
static inline void
Eip130Token_Command_Pk_Asset_SetAdditionalLength(
        Eip130Token_Command_t * const CommandToken_p,
        const uint64_t AddLength)
{
    Eip130TokenWord_t offset = ((CommandToken_p->W[3] & 0x0FFU) + 3U) & (Eip130TokenWord_t)~3UL;

    CommandToken_p->W[3] &= (Eip130TokenWord_t)~0x0FFUL;
    CommandToken_p->W[3] |= (offset + (2U * (Eip130TokenWord_t)sizeof(uint32_t)));
    CommandToken_p->W[12U + (offset / sizeof(uint32_t))] = (Eip130TokenWord_t)(AddLength);
    CommandToken_p->W[13U + (offset / sizeof(uint32_t))] = (Eip130TokenWord_t)(AddLength >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Asset_AddlenCorrection
 *
 * This function corrects the AddLen in the command token with provided
 * correction.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Correction
 *      AddLen correction (bytes)
 */
static inline void
Eip130Token_Command_Pk_Asset_AddlenCorrection(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t Correction)
{
    CommandToken_p->W[3] -= (Eip130TokenWord_t)Correction;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Asset_SaveSharedSecret
 *
 * This function sets the indication in the token that the shared secret shall
 * be saved in an Asset for further processing for example to support special
 * key derivation methods.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_Pk_Asset_SaveSharedSecret(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[3] |= BIT_31;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Asset_ExplicitDigest
 *
 * This function sets the indication in the token that the digest is explicitly
 * available in the token as ad. The Digest needs to be put in the additional
 * data area via Eip130Token_Command_Pk_Asset_SetAdditionalData.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Digest_p
 *     Pointer to the Explicit Digest data
 *
 * DigestSize
 *     Size of the Explicit Digest in bytes
 */
#ifdef EIP130_ENABLE_EXPLICITDIGEST
static inline void
Eip130Token_Command_Pk_Asset_SetExplicitDigest(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const Digest_p,
        uint32_t DigestSize)
{
    CommandToken_p->W[3] &= (Eip130TokenWord_t)~0x0FFUL;
    CommandToken_p->W[3] |= BIT_30;
    CommandToken_p->W[3] |= ((Eip130TokenWord_t)DigestSize & 0x0FFU); /* set AddInputLen */
    CommandToken_p->W[6] = 0U;          /* Make sure IOAssetId is zero */

    Eip130Token_Command_WriteByteArray(CommandToken_p, 12U,
                                       Digest_p, DigestSize);

}
#endif

/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Claim
 *
 * Request to claim the PKA engine for PK operations without assets
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Nwords
 *      Number of words of the basic vector for NumSetN.
 *
 * Mwords
 *      Number of words of the alternate (shorter) vector for NumSetN.
 *
 * Mmask
 *      Bitmask specifying (with 1b's) which of the first 8 vectors in Number
 *      Array are Mwords long for NumSetN.
 */
static inline void
Eip130Token_Command_Pk_Claim(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t Nwords,
        const uint8_t Mwords,
        const uint8_t Mmask)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_PUBLIC_KEY |
                            EIP130TOKEN_SUBCODE_PK_NOASSETS);
    CommandToken_p->W[2] = ((Eip130TokenWord_t)EIP130TOKEN_PK_CMD_NUMSETN |
                            ((Eip130TokenWord_t)Mmask << 8) |
                            ((Eip130TokenWord_t)Nwords << 16) |
                            ((Eip130TokenWord_t)Mwords << 24));
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_NumLoad
 *
 * Request to load vectors for PK operations without assets
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Index
 *     Selects the location(s) in which to store the input vector(s) for
 *     NumLoad.
 *
 * InputDataAddress
 *      Input data address.
 *
 * InputDataLengthInBytes
 *      Input data length.
 */
static inline void
Eip130Token_Command_Pk_NumLoad(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t Index,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const Eip130TokenDmaSize_t InputDataLengthInBytes)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_PUBLIC_KEY |
                            EIP130TOKEN_SUBCODE_PK_NOASSETS);
    CommandToken_p->W[2] = (Eip130TokenWord_t)EIP130TOKEN_PK_CMD_NUMLOAD |
                           (((Eip130TokenWord_t)Index & MASK_4_BITS) << 24);
    CommandToken_p->W[5] = ((Eip130TokenWord_t)InputDataLengthInBytes & MASK_12_BITS);
    CommandToken_p->W[6] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[7] = (Eip130TokenWord_t)(InputDataAddress >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Operation
 *
 * Request to perform a PK operations without assets
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Command
 *      Public Key operation (command) to perform.
 *
 * PublicExponent
 *      Specifies exponent for RSA public key operation.
 *
 * InputDataAddress
 *      Input data address.
 *
 * InputDataLengthInBytes
 *      Input data length.
 *
 * OutputDataAddress
 *      Output data address.
 *
 * OutputDataLengthInBytes
 *      Output data length.
 */
static inline void
Eip130Token_Command_Pk_Operation(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t Command,
        const uint32_t PublicExponent,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const Eip130TokenDmaSize_t InputDataLengthInBytes,
        const Eip130TokenDmaAddress_t OutputDataAddress,
        const Eip130TokenDmaSize_t OutputDataLengthInBytes)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_PUBLIC_KEY |
                            EIP130TOKEN_SUBCODE_PK_NOASSETS);
    CommandToken_p->W[2] = ((Eip130TokenWord_t)Command & MASK_5_BITS); /* PK operation to perform */
    CommandToken_p->W[3] = (Eip130TokenWord_t)PublicExponent;
    CommandToken_p->W[5] = (((Eip130TokenWord_t)OutputDataLengthInBytes & MASK_12_BITS) << 16) |
                           ((Eip130TokenWord_t)InputDataLengthInBytes & MASK_12_BITS);
    CommandToken_p->W[6] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[7] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[8] = (Eip130TokenWord_t)(OutputDataAddress);
    CommandToken_p->W[9] = (Eip130TokenWord_t)(OutputDataAddress >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Pk_Relaese
 *
 * Request to release the PKA engine for PK operations without assets
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_Pk_Release(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_PUBLIC_KEY |
                            EIP130TOKEN_SUBCODE_PK_NOASSETS);
    CommandToken_p->W[2] = (Eip130TokenWord_t)EIP130TOKEN_PK_CMD_NUMSETN;
}


#endif /* INCLUDE_GUARD_EIP130TOKEN_PK_H */

/* end of file eip130_token_pk.h */
