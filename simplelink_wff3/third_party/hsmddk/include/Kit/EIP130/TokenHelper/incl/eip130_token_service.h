/* eip130_token_service.h
 *
 * Security Module Token helper functions
 * - Service tokens related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_SERVICE_H
#define INCLUDE_GUARD_EIP130TOKEN_SERVICE_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */


/*----------------------------------------------------------------------------
 * Eip130Token_Command_RegisterWrite
 *
 * This token can be used to write the DMA controller configuration register.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Address
 *     Address to write.
 *
 * Value
 *     Value to write.
 */
static inline void
Eip130Token_Command_RegisterWrite(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t Address,
        const uint32_t Value)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SERVICE |
                            EIP130TOKEN_SUBCODE_REGISTERWRITE);
    CommandToken_p->W[2] = 1U;          /* only one word */
    CommandToken_p->W[3] = 0U;          /* Mask = 0 = Write all 32 bits */
    CommandToken_p->W[4] = (Eip130TokenWord_t)Address; /* Address to write to */
    CommandToken_p->W[5] = (Eip130TokenWord_t)Value;   /* Value to write */
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_RegisterRead
 *
 * This token can be used to read the DMA controller configuration register.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * Address
 *     Address to read.
 */
static inline void
Eip130Token_Command_RegisterRead(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t Address)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SERVICE |
                            EIP130TOKEN_SUBCODE_REGISTERREAD);
    CommandToken_p->W[2] = 1U;          /* only one word */
    CommandToken_p->W[3] = (Eip130TokenWord_t)Address; /* Address to read from */
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_RegisterRead
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * Value_p
 *      Pointer to the variable in which the value must be returned.
 */
static inline void
Eip130Token_Result_RegisterRead(
        const Eip130Token_Result_t * const ResultToken_p,
        uint32_t * const Value_p)
{
    *Value_p = ResultToken_p->W[1];
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_ZeroizeOutputMailbox
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_ZeroizeOutputMailbox(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SERVICE |
                            EIP130TOKEN_SUBCODE_ZEROOUTMAILBOX);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_ClockSwitch
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * ClocksForcedOn
 *     Bitmask specifying (with 1b's) the clocks that needs to be forced ON
 *     (always ON).
 *
 * ClocksForcedOff
 *     Bitmask specifying (with 1b's) the clocks that needs to be forced OFF
 *     (always OFF).
 */
static inline void
Eip130Token_Command_ClockSwitch(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t ClocksForcedOn,
        const uint16_t ClocksForcedOff)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SERVICE |
                            EIP130TOKEN_SUBCODE_CLOCKSWITCH);
    CommandToken_p->W[2] = ((Eip130TokenWord_t)ClocksForcedOff << 16) |
                           (Eip130TokenWord_t)ClocksForcedOn;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_FirmwareCheck
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * InputDataAddress
 *     The address of the firmware image to be checked.
 *
 * InputDataLength
 *     The length of the firmware image in bytes.
 */
static inline void
Eip130Token_Command_FirmwareCheck(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const Eip130TokenDmaSize_t InputDataLength)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SERVICE |
                            EIP130TOKEN_SUBCODE_FIRMWARECHECK);
    CommandToken_p->W[2] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[3] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[4] = (Eip130TokenWord_t)InputDataLength;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_UpdateRollbackID
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * RollbackID
 *     The new value for the SFWVBVER monotonic counter or
 *     zero to update it to the RollbackID of the current firmware
 */
static inline void
Eip130Token_Command_UpdateRollbackID(
        Eip130Token_Command_t * const CommandToken_p,
        uint16_t RollbackID)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SERVICE |
                            EIP130TOKEN_SUBCODE_UPDATEROLLBACKID);
    CommandToken_p->W[2] = (Eip130TokenWord_t)RollbackID;
}


#endif /* INCLUDE_GUARD_EIP130TOKEN_SERVICE_H */

/* end of file eip130_token_service.h */
