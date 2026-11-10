/* eip130_token_aunlock.h
 *
 * Security Module Token helper functions
 * - Authenticated unlock tokens related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_AUNLOCK_H
#define INCLUDE_GUARD_EIP130TOKEN_AUNLOCK_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AUnlock_Start
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 *
 * StateAssetID
 *      ID of Asset of Authenticated Unlock State.
 *
 * KeyAssetID
 *      ID of Asset of Authenticated Unlock Key.
 */
static inline void
Eip130Token_Command_AUnlock_Start(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t StateAssetID,
        const Eip130TokenAssetId_t KeyAssetID)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_AUTH_UNLOCK |
                            EIP130TOKEN_SUBCODE_AUNLOCKSTART);
    CommandToken_p->W[2] = (Eip130TokenWord_t)StateAssetID;
    CommandToken_p->W[3] = (Eip130TokenWord_t)KeyAssetID;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_AUnlock_CopyNonce
 *
 * This function copies the Nonce from the result token to the buffer
 * provided by the caller. The Nonce length is always 16 bytes.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * NonceData_p
 *      Pointer to the buffer to copy the nonce to.
 */
static inline void
Eip130Token_Result_AUnlock_CopyNonce(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * NonceData_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p, 2U, 16U, NonceData_p);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_AUnlock_Verify
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 *
 * StateAssetID
 *      ID of Asset of Authenticated Unlock State.
 *
 * NonceData_p
 *      Pointer to the buffer that holds the nonce.
 *
 * DataAddress
 *      DMA Address of the signature.
 *
 * DataLengthInBytes
 *      Size of the signature.
 */
static inline void
Eip130Token_Command_AUnlock_Verify(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t StateAssetID,
        const uint8_t * const NonceData_p,
        const Eip130TokenDmaAddress_t DataAddress,
        const Eip130TokenDmaSize_t DataLengthInBytes)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_AUTH_UNLOCK |
                            EIP130TOKEN_SUBCODE_AUNLOCKVERIFY);
    CommandToken_p->W[2] = (Eip130TokenWord_t)StateAssetID;
    CommandToken_p->W[3] = (Eip130TokenWord_t)DataLengthInBytes & MASK_10_BITS;
    CommandToken_p->W[4] = (Eip130TokenWord_t)(DataAddress);
    CommandToken_p->W[5] = (Eip130TokenWord_t)(DataAddress >> 32);

    Eip130Token_Command_WriteByteArray(CommandToken_p, 6U, NonceData_p, 16U);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SetSecureDebug
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 *
 * StateAssetID
 *      ID of Asset of Authenticated Unlock State.
 *
 * Set
 *      Indication to set the port bits, if not set the port bits are cleared.
 */
static inline void
Eip130Token_Command_SetSecureDebug(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t StateAssetID,
        const bool Set)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_AUTH_UNLOCK |
                            EIP130TOKEN_SUBCODE_SETSECUREDEBUG);
    CommandToken_p->W[2] = (Eip130TokenWord_t)StateAssetID;
    CommandToken_p->W[3] = Set ? BIT_31 : 0U;
}


#endif /* INCLUDE_GUARD_EIP130TOKEN_AUNLOCK_H */

/* end of file eip130_token_aunlock.h */
