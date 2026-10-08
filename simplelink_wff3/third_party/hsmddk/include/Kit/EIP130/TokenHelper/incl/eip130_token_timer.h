/* eip130_token_timer.h
 *
 * Security Module Token helper functions
 * - Secure Timer related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_TIMER_H
#define INCLUDE_GUARD_EIP130TOKEN_TIMER_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SecureTimer
 *
 * This function initializes the command token for a Secure Timer (Re)Start,
 * Stop and read operation.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId (optional for start)
 *      AssetId of the secure timer to stop, read or restart.
 *
 * fSecond
 *      Second timer indication otherwise 100 us timer is used.
 *
 * Operation
 *      Secure timer operation to perform (re)start, stop or read.
 */
static inline void
Eip130Token_Command_SecureTimer(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId,
        const bool fSecond,
        const uint16_t Operation)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_ASSETMANAGEMENT |
                            EIP130TOKEN_SUBCODE_SECURETIMER);
    CommandToken_p->W[2] = (Eip130TokenWord_t)AssetId;
    CommandToken_p->W[3] = (Eip130TokenWord_t)Operation & MASK_2_BITS;
    if (fSecond)
    {
        CommandToken_p->W[3] |= BIT_15;
    }
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SecureTimer
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * AssetId_p (optional)
 *      Pointer to the variable in which the AssetId must be returned.
 *
 * ElapsedTime_p (optional)
 *      Pointer to the variable in which the elapsed time must be returned.
 */
static inline void
Eip130Token_Result_SecureTimer(
        const Eip130Token_Result_t * const ResultToken_p,
        Eip130TokenAssetId_t * const AssetId_p,
        uint32_t * const ElapsedTime_p)
{
    if (AssetId_p != NULL)
    {
        *AssetId_p = ResultToken_p->W[1];
    }
    if (ElapsedTime_p != NULL)
    {
        *ElapsedTime_p = ResultToken_p->W[2];
    }
}


#endif /* INCLUDE_GUARD_EIP130TOKEN_TIMER_H */

/* end of file eip130_token_timer.h */
