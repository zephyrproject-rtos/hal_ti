/* eip130_token_wrap.h
 *
 * Security Module Token helper functions
 * - AES Wrap/Unwrap token related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_WRAP_H
#define INCLUDE_GUARD_EIP130TOKEN_WRAP_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */

#ifdef EIP130_ENABLE_SYM_KEYWRAP
/*----------------------------------------------------------------------------
 * Eip130Token_Command_WrapUnwrap
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * fWrap
 *     true  = Wrap
 *     false = Unwrap
 *
 * InputDataAddress
 *     Address of data to be wrapped or unwrapped.
 *
 * InputDataLengthInBytes
 *     Number of bytes to process.
 *     Must be at least 16, at most 1024 and always a multiple of 8.
 *
 * OutputDataAddress
 *     Address of the buffer for data that has been wrapped or unwrapped.
 */
static inline void
Eip130Token_Command_WrapUnwrap(
        Eip130Token_Command_t * const CommandToken_p,
        const bool fWrap,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const uint16_t InputDataLengthInBytes,
        const Eip130TokenDmaAddress_t OutputDataAddress)
{
    CommandToken_p->W[0] = EIP130TOKEN_OPCODE_SYMWRAP;
    CommandToken_p->W[2] = ((Eip130TokenWord_t)InputDataLengthInBytes & MASK_11_BITS);
    CommandToken_p->W[3] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[4] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[5] = (Eip130TokenWord_t)(OutputDataAddress);
    CommandToken_p->W[6] = (Eip130TokenWord_t)(OutputDataAddress >> 32);
    if (fWrap)
    {
        CommandToken_p->W[7] = BIT_15;
    }
    else
    {
        CommandToken_p->W[7] = 0U;
    }
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_WrapUnwrap_SetAlgorithm
 *
 * This function sets the algorithm used by the operation
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Algorithm
 *     algorithm type (AES = 0 or SM4 = 8)
 */
static inline void
Eip130Token_Command_WrapUnwrap_SetAlgorithm(
        Eip130Token_Command_t * const CommandToken_p,
        uint8_t Algorithm)
{
    CommandToken_p->W[7] |= ((Eip130TokenWord_t)Algorithm & MASK_4_BITS);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_WrapUnwrap_SetKeyLength
 *
 * This function sets the coded length of the AES key.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * KeyLengthInBytes
 *     The length of the key.
 */
static inline void
Eip130Token_Command_WrapUnwrap_SetKeyLength(
        Eip130Token_Command_t * const CommandToken_p,
        const uint32_t KeyLengthInBytes)
{
    uint32_t CodedKeyLen;

    /* Key length only needed for AES */
    switch (KeyLengthInBytes)
    {
    case 128 / 8:
        CodedKeyLen = 1U;
        break;

    case 192 / 8:
        CodedKeyLen = 2U;
        break;

    case 256 / 8:
        CodedKeyLen = 3U;
        break;

    default:
        CodedKeyLen = 0U;
        break;
    }
    CommandToken_p->W[7] |= ((Eip130TokenWord_t)CodedKeyLen << 16);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_WrapUnwrap_SetASLoadKey
 *
 * This function sets the Asset Store Load location for the key and activates
 * its use. This also disables the use of the key via the token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Key Encryption Key Asset to use.
 */
static inline void
Eip130Token_Command_WrapUnwrap_SetASLoadKey(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[7] |= BIT_8;
    CommandToken_p->W[8] = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_WrapUnwrap_CopyKey
 *
 * This function copies the key from the buffer provided by the caller into
 * the command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Key_p
 *     Key data to copy to the token.
 *
 * KeyLengthInBytes
 *     The length of the key data.
 */
static inline void
Eip130Token_Command_WrapUnwrap_CopyKey(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const Key_p,
        const uint32_t KeyLengthInBytes)
{
    CommandToken_p->W[7] &= ~(Eip130TokenWord_t)BIT_8;
    Eip130Token_Command_WriteByteArray(CommandToken_p, 8U,
                                       Key_p, KeyLengthInBytes);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_WrapUnwrap_GetDataLength
 *
 * This function returns the length of the result object from the result token.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * DataLengthInBytes_p
 *      Pointer to the variable in which the data length must be returned.
 */
static inline void
Eip130Token_Result_WrapUnwrap_GetDataLength(
        const Eip130Token_Result_t * const ResultToken_p,
        uint32_t * const DataLengthInBytes_p)
{
    *DataLengthInBytes_p = (ResultToken_p->W[1] & MASK_11_BITS);
}
#endif

#endif /* INCLUDE_GUARD_EIP130TOKEN_WRAP_H */

/* end of file eip130_token_wrap.h */
