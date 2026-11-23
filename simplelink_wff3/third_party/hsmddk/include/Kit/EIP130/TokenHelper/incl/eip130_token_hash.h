/* eip130_token_hash.h
 *
 * Security Module Token helper functions
 * - Hash token related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_HASH_H
#define INCLUDE_GUARD_EIP130TOKEN_HASH_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */

/* Symmetric Crypto hash algorithms */
#define EIP130TOKEN_HASH_ALGORITHM_SHA1         0x01U
#define EIP130TOKEN_HASH_ALGORITHM_SHA224       0x02U
#define EIP130TOKEN_HASH_ALGORITHM_SHA256       0x03U
#define EIP130TOKEN_HASH_ALGORITHM_SHA384       0x04U
#define EIP130TOKEN_HASH_ALGORITHM_SHA512       0x05U
#define EIP130TOKEN_HASH_ALGORITHM_SM3          0x06U
#define EIP130TOKEN_HASH_ALGORITHM_SHA3_224     0x07U
#define EIP130TOKEN_HASH_ALGORITHM_SHA3_256     0x08U
#define EIP130TOKEN_HASH_ALGORITHM_SHA3_384     0x09U
#define EIP130TOKEN_HASH_ALGORITHM_SHA3_512     0x0AU


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Hash
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * HashAlgo
 *     Hash algorithm selection. Use one of EIP130TOKEN_HASH_ALGORITHM_*
 *
 * fInitWithDefault
 *     Set to true to have the digest initialized with the default value
 *     according to the specification for the selected hash algorithm.
 *
 * fFinalize
 *     Set to true to have the hash finalized.
 *
 * InputDataAddress
 *     Address of data to be hashed.
 *
 * InputDataLengthInBytes
 *     Size/Length of the data block to be hashed.
 *     Note: For non-final hash (fFinalize == false) this must be a multiple
 *           of 64 bytes, otherwise the request will be rejected.
 *           For final hash, this can be any value.
 */
static inline void
Eip130Token_Command_Hash(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t HashAlgo,
        const bool fInitWithDefault,
        const bool fFinalize,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const Eip130TokenDmaSize_t InputDataLengthInBytes)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_HASH | ((Eip130TokenWord_t)1UL << 28));
    CommandToken_p->W[2] = (Eip130TokenWord_t)InputDataLengthInBytes;
    CommandToken_p->W[3] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[4] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[5] = (Eip130TokenWord_t)InputDataLengthInBytes;
    CommandToken_p->W[6] = (Eip130TokenWord_t)HashAlgo & MASK_4_BITS;
    if (!fInitWithDefault)
    {
        CommandToken_p->W[6] |= BIT_4;
    }
    if (!fFinalize)
    {
        CommandToken_p->W[6] |= BIT_5;
    }
    CommandToken_p->W[7] = 0U;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Hash_SetStateASID
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *     Asset ID of the intermediate state asset.
 */
static inline void
Eip130Token_Command_Hash_SetStateASID(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[7] = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Hash_SetTotalMessageLength
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * TotalMessageLengthInBytes = Bits 60:0
 *     This is the total message length c.q. the length of all data blocks
 *     that are hashed, required for when hash is finalized.
 */
static inline void
Eip130Token_Command_Hash_SetTotalMessageLength(
        Eip130Token_Command_t * const CommandToken_p,
        const uint64_t TotalMessageLengthInBytes)
{
    CommandToken_p->W[10] = (Eip130TokenWord_t)(TotalMessageLengthInBytes);
    CommandToken_p->W[11] = (Eip130TokenWord_t)(TotalMessageLengthInBytes >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Hash_CopyState
 *
 * This function copies the intermediate state from the buffer provided by the
 * caller into the command token. The requested number of bytes are copied.
 * Note that the length depends on the algorithm that is used.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * State_p
 *     Pointer to the intermediate state buffer.
 *
 * StateLenInBytes
 *     The size of the intermediate state to copy.
 */
static inline void
Eip130Token_Command_Hash_CopyState(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const State_p,
        const uint32_t StateLenInBytes)
{
    Eip130Token_Command_WriteByteArray(CommandToken_p, 14U,
                                       State_p, StateLenInBytes);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_Hash_CopyState
 *
 * This function copies the intermediate state or final digest from the result
 * token to the buffer provided by the caller. The requested number of bytes
 * are copied. Note that the length depends on the algorithm that is used.
 *
 * The digest is written to the destination buffer, Byte 0 first.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * StateLenInBytes
 *     The size of the intermediate state or final digest to copy.
 *
 * State_p
 *     Pointer to the intermediate state or final digest buffer.
 */
static inline void
Eip130Token_Result_Hash_CopyState(
        const Eip130Token_Result_t * const ResultToken_p,
        const uint32_t StateLenInBytes,
        uint8_t * State_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p, 2U,
                                     StateLenInBytes, State_p);
}


#endif /* INCLUDE_GUARD_EIP130TOKEN_HASH_H */

/* end of file eip130_token_hash.h */
