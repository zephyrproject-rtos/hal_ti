/* eip130_token_asset.h
 *
 * Security Module Token helper functions
 * - Asset Management token related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_ASSET_H
#define INCLUDE_GUARD_EIP130TOKEN_ASSET_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */

/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetSearch
 *
 * Request to return the ID for a static asset with the given index.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetNumber
 *      Asset number of the Static Asset to search for.
 */
static inline void
Eip130Token_Command_AssetSearch(
        Eip130Token_Command_t * const CommandToken_p,
        const uint32_t AssetNumber)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETSEARCH);
    CommandToken_p->W[4] = ((Eip130TokenWord_t)AssetNumber & MASK_8_BITS) << 16;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_AssetSearch
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * AssetId_p
 *      Pointer to the variable in which the AssetId must be returned.
 *
 * DataLength_p
 *      Optional pointer to the variable in which the data length must be
 *      returned.
 */
static inline void
Eip130Token_Result_AssetSearch(
        const Eip130Token_Result_t * const ResultToken_p,
        Eip130TokenAssetId_t * const AssetId_p,
        uint32_t * const DataLength_p)
{
    *AssetId_p = ResultToken_p->W[1];

    if (DataLength_p != NULL)
    {
        *DataLength_p = (ResultToken_p->W[2] & MASK_10_BITS);
    }
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetCreate
 *
 * Request to create an asset with the given policy and length.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Policy
 *      Policy of the Asset to create.
 *
 * LengthInBytes
 *      Length of the Asset in bytes.
 */
static inline void
Eip130Token_Command_AssetCreate(
        Eip130Token_Command_t * const CommandToken_p,
        const uint64_t Policy,
        const uint32_t LengthInBytes)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETCREATE);
    CommandToken_p->W[2] = (Eip130TokenWord_t)(Policy);
    CommandToken_p->W[3] = (Eip130TokenWord_t)(Policy >> 32);
    CommandToken_p->W[4] = ((Eip130TokenWord_t)LengthInBytes & MASK_10_BITS);
    CommandToken_p->W[5] = 0U;
    CommandToken_p->W[6] = 0U;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_AssetCreate
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * AssetId_p
 *      Pointer to the variable in which the AssetId must be returned.
 */
static inline void
Eip130Token_Result_AssetCreate(
        const Eip130Token_Result_t * const ResultToken_p,
        Eip130TokenAssetId_t * const AssetId_p)
{
    *AssetId_p = ResultToken_p->W[1];
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetDelete
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Asset to delete.
 */
static inline void
Eip130Token_Command_AssetDelete(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETDELETE);
    CommandToken_p->W[2] = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_Derive
 *
 * Request to setup the target asset content by derivation.
 *
 * Notes:
 * - Use Eip130Token_Command_AssetLoad_SetAad to setup the additional data to
 *   be used as input for the key derivation process.
 * - Use Eip130Token_Command_AssetLoad_SetInput for Salt related information
 * - Use Eip130Token_Command_AssetLoad_SetOutput for IV related information
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Asset to load (initialize).
 *
 * KdkAssetId
 *      Asset ID of the Key Derivation Key Asset to use.
 *
 * Counter
 *      When set, the key derivation is performed with the KDF in counter mode
 *      as defined in NIST SP800-108.
 *
 * RFC5869
 *      When set, the key derivation is performed as defined in RFC 5869.
 *
 * AssetNumber
 *      This number refers to a monotonic counter to be included in key
 *      derivation of the (Trusted Wrap) key.
 *      This number is in the range of [0..95].
 */
static inline void
Eip130Token_Command_AssetLoad_Derive(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId,
        const Eip130TokenAssetId_t KdkAssetId,
        const bool Counter,
        const bool RFC5869,
        const uint8_t AssetNumber)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETLOAD);
    CommandToken_p->W[2] = (Eip130TokenWord_t)AssetId;
    CommandToken_p->W[3] = BIT_24;      /* Derive */
    if (Counter)
    {
        CommandToken_p->W[3] |= BIT_14; /* Counter mode */
    }
    if (RFC5869)
    {
        CommandToken_p->W[3] |= BIT_15; /* RFC5869 method */
    }
    CommandToken_p->W[4] = 0U;
    CommandToken_p->W[5] = 0U;
    CommandToken_p->W[6] = 0U;
    CommandToken_p->W[7] = 0U;
    CommandToken_p->W[8] = (Eip130TokenWord_t)AssetNumber << 24;
    CommandToken_p->W[9] = (Eip130TokenWord_t)KdkAssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_Random
 *
 * Request to setup the target asset content with random data. The asset
 * size was already specified when the asset was created.
 *
 * Notes:
 * - Use Eip130Token_Command_AssetLoad_Export to also request the export of
 *   the asset as key blob.
 * - Use Eip130Token_Command_AssetLoad_SetAad to setup the additional data to
 *   be needed for generating the key blob.
 * - Use Eip130Token_Command_AssetLoad_SetOutput for key blob data related
 *   information
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Asset to load (initialize).
 */
static inline void
Eip130Token_Command_AssetLoad_Random(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETLOAD);
    CommandToken_p->W[2] = (Eip130TokenWord_t)AssetId;
    CommandToken_p->W[3] = BIT_25;      /* Random */
    CommandToken_p->W[6] = 0U;
    CommandToken_p->W[7] = 0U;
    CommandToken_p->W[8] = 0U;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_Import
 *
 * Request to setup the target asset content from a key blob.
 *
 * Notes:
 * - Use Eip130Token_Command_AssetLoad_SetAad to setup the additional data to
 *   be needed to read the key blob.
 * - Use Eip130Token_Command_AssetLoad_SetInput for key blob data related
 *   information
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Asset to load (initialize).
 *
 * KekAssetId
 *      Asset ID of the Key Encryption Key Asset to use.
 */
static inline void
Eip130Token_Command_AssetLoad_Import(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId,
        const Eip130TokenAssetId_t KekAssetId)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETLOAD);
    CommandToken_p->W[2] = (Eip130TokenWord_t)AssetId;
    CommandToken_p->W[3] = BIT_26;      /* Import */
    CommandToken_p->W[4] = 0U;
    CommandToken_p->W[5] = 0U;
    CommandToken_p->W[9] = (Eip130TokenWord_t)KekAssetId; /* AES-SIV Key Encryption Key */
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_PlainText
 *
 * Request to setup the target asset content from plain text.
 *
 * Notes:
 * - Use Eip130Token_Command_AssetLoad_Export to also request the export of
 *   the asset as key blob.
 * - Use Eip130Token_Command_AssetLoad_SetAad to setup the additional data to
 *   be needed for generating the key blob.
 * - Use Eip130Token_Command_AssetLoad_SetOutput for key blob data related
 *   information
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Asset to load (initialize).
 */
static inline void
Eip130Token_Command_AssetLoad_Plaintext(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETLOAD);
    CommandToken_p->W[2] = (Eip130TokenWord_t)AssetId;
    CommandToken_p->W[3] = BIT_27;     /* Plaintext */
    CommandToken_p->W[4] = 0U;
    CommandToken_p->W[5] = 0U;
    CommandToken_p->W[6] = 0U;
    CommandToken_p->W[7] = 0U;
    CommandToken_p->W[8] = 0U;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_SymUnwrap
 *
 * Request to setup the target asset content from an AES/SM4 key wrapped key blob.
 *
 * Notes:
 * - Use Eip130Token_Command_AssetLoad_SetInput for key blob data related
 *   information
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Asset to load (initialize).
 *
 * KekAssetId
 *      Asset ID of the Key Encryption Key Asset to use.
 *
 * Algorithm
 *      Algorithm to use.
 */
static inline void
Eip130Token_Command_AssetLoad_SymUnwrap(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId,
        const Eip130TokenAssetId_t KekAssetId,
        uint8_t Algorithm)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETLOAD);
    CommandToken_p->W[2] = (Eip130TokenWord_t)AssetId;
    CommandToken_p->W[3] = BIT_28;       /* Unwrap */
    CommandToken_p->W[4] = 0U;
    CommandToken_p->W[5] = 0U;
    CommandToken_p->W[8] = (Eip130TokenWord_t)Algorithm << 16;
    CommandToken_p->W[9] = (Eip130TokenWord_t)KekAssetId;  /* Wrap Key Encryption Key */
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_SetAad
 *
 * Setup additional data for
 * - AssetLoad Derive
 * - AssetLoad Unwrap / Import
 * - AssetLoad Plaintext / Generate with request to produce a keyblob ('Wrap')
 *
 * Minimum AAD length is enforced by this function by padding with zero bytes.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssociatedData_p
 *      Associated Data address.
 *
 * AssociatedDataSizeInBytes
 *      Associated Data length.
 */
static inline void
Eip130Token_Command_AssetLoad_SetAad(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const AssociatedData_p,
        const uint32_t AssociatedDataSizeInBytes)
{
    CommandToken_p->W[3] |= ((Eip130TokenWord_t)AssociatedDataSizeInBytes << 16);

    Eip130Token_Command_WriteByteArray(CommandToken_p, 10U,
                                       AssociatedData_p,
                                       AssociatedDataSizeInBytes);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_SetInput
 *
 * Request to setup the asset related input data information.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * DataAddress
 *      Input Data address.
 *
 * DataLengthInBytes
 *      Input Data length.
 */
static inline void
Eip130Token_Command_AssetLoad_SetInput(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenDmaAddress_t DataAddress,
        const Eip130TokenDmaSize_t DataLengthInBytes)
{
    CommandToken_p->W[3] |= (Eip130TokenWord_t)DataLengthInBytes & MASK_10_BITS;
    CommandToken_p->W[4]  = (Eip130TokenWord_t)(DataAddress);
    CommandToken_p->W[5]  = (Eip130TokenWord_t)(DataAddress >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_SetOutput
 *
 * Request to setup the asset related output data information.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * DataAddress
 *      Output Data address.
 *
 * DataLengthInBytes
 *      Output Data length.
 */
static inline void
Eip130Token_Command_AssetLoad_SetOutput(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenDmaAddress_t DataAddress,
        const Eip130TokenDmaSize_t DataLengthInBytes)
{
    CommandToken_p->W[8] |= (Eip130TokenWord_t)DataLengthInBytes & MASK_10_BITS;
    CommandToken_p->W[6]  = (Eip130TokenWord_t)(DataAddress);
    CommandToken_p->W[7]  = (Eip130TokenWord_t)(DataAddress >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetLoad_Export
 *
 * Request to export an asset as key blob after its contents have been setup
 * with either random or plain text data.
 * Use Eip130Token_Command_AssetLoad_SetAad to setup the additional data to be
 * used when generating the key blob.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * KekAssetId
 *      Asset ID of the Key Encryption Key Asset to use.
 */
static inline void
Eip130Token_Command_AssetLoad_Export(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t KekAssetId)
{
    CommandToken_p->W[3] |= BIT_31;     /* KeyBlob */
    CommandToken_p->W[9]  = (Eip130TokenWord_t)KekAssetId; /* AES-SIV Key Encryption Key */
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_AssetLoad_OutputSize
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * OutputSizeInBytes_p
 *      Pointer to the variable in which the ouput size must be returned.
 */
static inline void
Eip130Token_Result_AssetLoad_OutputSize(
        const Eip130Token_Result_t * const ResultToken_p,
        uint32_t * const OutputSizeInBytes_p)
{
    *OutputSizeInBytes_p = ResultToken_p->W[1] & MASK_10_BITS;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetExport_Coprocessor
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 *
 * AssetId
 *      The Asset Identifier of the Asset to export via
 *      the Coprocesor Interface
 *
 * Address
 *      The Address in the Coprocessor, where the Asset will be exported.
 *
 * CPxSelectionBits
 *      Specifies the mask of CPx bits. The Asset data will be transfered
 *      to the Coprocessor connected via the cp_tcm_cs[x] pin.
 */
#ifdef EIP130_ENABLE_CPIF
static inline void
Eip130Token_Command_AssetExport_Coprocessor(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId,
        const uint16_t Address,
        const uint16_t CPxSelectionBits)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_CPIF_EXPORT);
    CommandToken_p->W[2] = (Eip130TokenWord_t)AssetId;
    CommandToken_p->W[3] = (Eip130TokenWord_t)CPxSelectionBits & MASK_10_BITS; /* SelectionBits */
    CommandToken_p->W[4] = (Eip130TokenWord_t)Address & MASK_16_BITS;
}
#endif


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AssetStore_Reset
 *
 * Request to reset (clear) the dynamic Asset Store.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
#ifdef EIP130_ENABLE_ASSET_STORE_RESET
static inline void
Eip130Token_Command_AssetStore_Reset(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_ASSETSTORERESET);
}
#endif


/*----------------------------------------------------------------------------
 * Eip130Token_Command_NeedsAppID
 *
 * Returns true when the provided token is an Asset Load token with the
 * Derive flag set.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline bool
Eip130Token_Command_NeedsAppID(
        const Eip130Token_Command_t * const CommandToken_p)
{
    bool rc = false;
    uint32_t tmp = MASK_8_BITS;
    tmp = (tmp << 24U);

    if ((CommandToken_p->W[0] & tmp) ==
        (EIP130TOKEN_OPCODE_ASSETMANAGEMENT | EIP130TOKEN_SUBCODE_ASSETLOAD))
    {
        /* Token = Asset Management - Asset Load */
        if ((CommandToken_p->W[3] & BIT_24) != 0U)
        {
            /* Derive command */
            rc = true;
        }
    }

    return rc;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_InsertAppID
 *
 * This function is called to insert the AppID at the start of the AAD area
 * in the AssetLoad command. This is needed when Eip130Token_Command_NeedsAppID
 * returns true.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_InsertAppID(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const AssociatedData_p,
        uint32_t AssociatedDataSizeInBytes)
{
    if (Eip130Token_Command_NeedsAppID(CommandToken_p))
    {
        uint32_t AADMax = (EIP130TOKEN_COMMAND_WORDS - 10U) * 4U; /* Max AAD bytes in token */
        uint32_t AADLen = (CommandToken_p->W[3] >> 16) & MASK_8_BITS;
        uint32_t AssociatedDataSize = AssociatedDataSizeInBytes;

        /* ensure additional data by itself fits */
        if (AssociatedDataSize > AADMax)
        {
            AssociatedDataSize = AADMax;
        }

        /* calculate how much of the current AAD data can remain */
        if ((AADLen + AssociatedDataSize) > AADMax)
        {
             AADLen = AADMax - AssociatedDataSize;
        }

        /* move the current AAD data to make space for the new data
         * move is done on byte-array, assuming LSB-first */
        if ((AADLen > 0U) && (AssociatedDataSize < AADMax))
        {
            uint8_t * AAD_Src_p = (uint8_t *)&CommandToken_p->W[10];
            uint8_t * AAD_Dst_p = &AAD_Src_p[AssociatedDataSize];
            int32_t i = (int32_t)(AADLen) - 1;

            while (i >= 0)
            {
                 AAD_Dst_p[i] = AAD_Src_p[i];
                 i--;
            }
        }

        /* now write the new Associated Data */
        Eip130Token_Command_WriteByteArray(CommandToken_p, 10U,
                                           AssociatedData_p,
                                           AssociatedDataSize);

        /* overwrite the length field
         * (do not try to update it due to size limiters above) */
        AADLen += AssociatedDataSize;
        CommandToken_p->W[3] &= ~(Eip130TokenWord_t)((Eip130TokenWord_t)MASK_8_BITS << 16);
        CommandToken_p->W[3] |= (AADLen << 16);
    }
}


#endif /* INCLUDE_GUARD_EIP130TOKEN_ASSET_H */

/* end of file eip130_token_asset.h */
