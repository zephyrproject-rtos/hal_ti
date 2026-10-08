/* eip130_token_mac.h
 *
 * Security Module Token helper functions
 * - MAC token related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_MAC_H
#define INCLUDE_GUARD_EIP130TOKEN_MAC_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */


/* Symmetric Crypto MAC algorithms */
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA1         0x01U
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA224       0x02U
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA256       0x03U
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA384       0x04U
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA512       0x05U
#define EIP130TOKEN_MAC_ALGORITHM_SM3               0x06U
#define EIP130TOKEN_MAC_ALGORITHM_POLY1305          0x07U
#define EIP130TOKEN_MAC_ALGORITHM_AES_CMAC          0x08U
#define EIP130TOKEN_MAC_ALGORITHM_AES_CBCMAC        0x09U
#define EIP130TOKEN_MAC_ALGORITHM_ARIA_CMAC         0x0AU
#define EIP130TOKEN_MAC_ALGORITHM_ARIA_CBCMAC       0x0BU
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA3_224     0x0CU
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA3_256     0x0DU
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA3_384     0x0EU
#define EIP130TOKEN_MAC_ALGORITHM_HMAC_SHA3_512     0x0FU


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Mac
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * MacAlgo
 *     Mac algorithm selection. Use one of EIP130TOKEN_MAC_ALGORITHM_*.
 *
 * fInit
 *     Set to true to have the MAC initialized with the default value
 *     according to the specification for the selected algorithm.
 *
 * fFinalize
 *     Set to true to have the hash finalized.
 *
 * InputDataAddress
 *     Input address of data to be MACed.
 *
 * InputDataLengthInBytes
 *     Input size/Length of the data block to be MACed.
 *     Note: For non-final MAC (fFinalize == false) this must be a multiple
 *           of the block size bytes, otherwise the request will be rejected.
 */
static inline void
Eip130Token_Command_Mac(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t MacAlgo,
        const bool fInit,
        const bool fFinalize,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const Eip130TokenDmaSize_t InputDataLengthInBytes)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_MAC | ((Eip130TokenWord_t)1UL << 28));
    CommandToken_p->W[2] = (Eip130TokenWord_t)InputDataLengthInBytes;
    CommandToken_p->W[3] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[4] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[5] = (Eip130TokenWord_t)((InputDataLengthInBytes + 3U) & (uint32_t)~3UL);
    CommandToken_p->W[6] = (Eip130TokenWord_t)MacAlgo & MASK_4_BITS;
    if (!fInit)
    {
        CommandToken_p->W[6] |= BIT_4;
    }
    if (!fFinalize)
    {
        CommandToken_p->W[6] |= BIT_5;
    }
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Mac_SetTotalMessageLength
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * TotalMessageLengthInBytes = Bits 60:0
 *     This is the total message length c.q. the length of all data blocks
 *     that are MACed, required for when MAC is finalized.
 */
static inline void
Eip130Token_Command_Mac_SetTotalMessageLength(
        Eip130Token_Command_t * const CommandToken_p,
        const uint64_t TotalMessageLengthInBytes)
{
    CommandToken_p->W[10] = (Eip130TokenWord_t)(TotalMessageLengthInBytes);
    CommandToken_p->W[11] = (Eip130TokenWord_t)(TotalMessageLengthInBytes >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Mac_SetASIDKey
 *
 * This function sets the AssetId of the key Asset.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *     Asset ID of the key Asset.
 */
static inline void
Eip130Token_Command_Mac_SetASIDKey(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[8] = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Mac_SetASIDState
 *
 * This function sets the AssetId of the intermedaite state Asset.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *     Asset ID of the intermediate MAC Asset.
 */
static inline void
Eip130Token_Command_Mac_SetASIDState(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[7] = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Mac_SetASIDVerifyMAC
 *
 * This function sets the AssetId of the verify MAC Asset that shall be used
 * to verify the calculated final MAC and activates its use.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *     Asset ID of the verify MAC Asset.
 */
static inline void
Eip130Token_Command_Mac_SetASIDVerifyMAC(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[6] |= BIT_9;
    CommandToken_p->W[14] = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Mac_CopyVerifyMAC
 *
 * This function copies the verify MAC from the buffer provided by the caller
 * into the command token. The requested number of bytes are copied.
 * Note that the length depends on the algorithm that is used.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * VerifyMAC_p
 *     Pointer to the verify MAC buffer.
 *
 * VerifyMACLenInBytes
 *     The size of the verify MAC to copy.
 */
static inline void
Eip130Token_Command_Mac_CopyVerifyMAC(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const VerifyMAC_p,
        const uint32_t VerifyMACLenInBytes)
{
    CommandToken_p->W[6] &= ~(Eip130TokenWord_t)BIT_9;
    Eip130Token_Command_WriteByteArray(CommandToken_p, 14U,
                                       VerifyMAC_p, VerifyMACLenInBytes);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_Mac_CopyFinalMAC
 *
 * This function copies the final MAC from the result token to the buffer
 * provided by the caller. The requested number of bytes are copied.
 * Note that the length depends on the algorithm that is used.
 *
 * The final MAC is written to the destination buffer, Byte 0 first.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * MACLenInBytes
 *     The size of the final MAC to copy.
 *
 * MAC_p
 *     Pointer to the final MAC buffer.
 */
static inline void
Eip130Token_Result_Mac_CopyFinalMAC(
        const Eip130Token_Result_t * const ResultToken_p,
        const uint32_t MACLenInBytes,
        uint8_t * MAC_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p, 2U, MACLenInBytes, MAC_p);
}


#endif /* INCLUDE_GUARD_EIP130TOKEN_MAC_H */

/* end of file eip130_token_mac.h */
