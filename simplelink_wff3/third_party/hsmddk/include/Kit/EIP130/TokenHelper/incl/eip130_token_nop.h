/* eip130_token_nop.h
 *
 * Security Module Token helper functions
 * - NOP token related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_NOP_H
#define INCLUDE_GUARD_EIP130TOKEN_NOP_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command_t */

#ifdef EIP130_ENABLE_NOP
/*----------------------------------------------------------------------------
 * Eip130Token_Command_Nop
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 *
 * InputDataAddress
 *     Address of the input data buffer.
 *
 * InputDataLengthInBytes
 *     Size of the input data buffer being the number of bytes to copy.
 *     Must be a multiple of 4.
 *
 * OutputDataAddress
 *     Address of the output data buffer.
 *
 * OutputDataLengthInBytes
 *     Size of the output data buffer.
 *     Must be a multiple of 4.
 */
static inline void
Eip130Token_Command_Nop(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const Eip130TokenDmaSize_t InputDataLengthInBytes,
        const Eip130TokenDmaAddress_t OutputDataAddress,
        const Eip130TokenDmaSize_t OutputDataLengthInBytes)
{
    CommandToken_p->W[0] = EIP130TOKEN_OPCODE_NOP;
    CommandToken_p->W[2] = (Eip130TokenWord_t)InputDataLengthInBytes;
    CommandToken_p->W[3] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[4] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[5] = (Eip130TokenWord_t)InputDataLengthInBytes;
    CommandToken_p->W[6] = (Eip130TokenWord_t)(OutputDataAddress);
    CommandToken_p->W[7] = (Eip130TokenWord_t)(OutputDataAddress >> 32);
    CommandToken_p->W[8] = (Eip130TokenWord_t)OutputDataLengthInBytes;
}
#endif


#endif /* INCLUDE_GUARD_EIP130TOKEN_NOP_H */

/* end of file eip130_token_nop.h */
