/* eip130_token_common.c
 *
 * Security Module Token helper functions
 * - Common byte array related functions
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

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint8_t, IDENTIFIER_NOT_USED, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* the API to implement */


/*----------------------------------------------------------------------------
 * Eip130Token_Command_WriteByteArray
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * StartWord
 *     The word index of read.
 *
 * Data_p
 *     Pointer to the buffer.
 *
 * DataLenInBytes
 *     The size of the buffer to copy to the token.
 */
void
Eip130Token_Command_WriteByteArray(
        Eip130Token_Command_t * const CommandToken_p,
        uint32_t StartWord,
        const uint8_t * Data_p,
        const uint32_t DataLenInBytes)
{
    uint32_t LocalStartWord = StartWord;
    const uint8_t * LocalData_p = Data_p;

    if ((CommandToken_p != NULL) && (LocalData_p != NULL))
    {
        uint32_t i = 0;

        while (i < DataLenInBytes)
        {
            uint32_t W;

            if (LocalStartWord >= EIP130TOKEN_RESULT_WORDS)
            {
                break;
            }

            // LSB-first
            W = (uint32_t)(*LocalData_p);
            i++;
            if (i < DataLenInBytes)
            {
                LocalData_p++;
                W |= (((uint32_t)(*LocalData_p)) << 8);
                i++;
                if (i < DataLenInBytes)
                {
                    LocalData_p++;
                    W |= (((uint32_t)(*LocalData_p)) << 16);
                    i++;
                    if (i < DataLenInBytes)
                    {
                        LocalData_p++;
                        W |= (((uint32_t)(*LocalData_p)) << 24);
                        i++;
                        if (i < DataLenInBytes)
                        {
                            LocalData_p++;
                        }
                    }
                }
            }

            // Write word
            CommandToken_p->W[LocalStartWord] = W;
            LocalStartWord++;
        }
    }

    return;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_ReadByteArray
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * StartWord
 *     The word index of read.
 *
 * DestLenInBytes
 *     The size of the buffer to copy the read info to.
 *
 * Dest_p
 *     Pointer to the buffer.
 */
void
Eip130Token_Result_ReadByteArray(
        const Eip130Token_Result_t * const ResultToken_p,
        uint32_t StartWord,
        uint32_t DestLenOutBytes,
        uint8_t * Dest_p)
{
    uint32_t LocalStartWord = StartWord;
    uint8_t * LocalDest_p = Dest_p;

    if ((ResultToken_p != NULL) && (LocalDest_p != NULL))
    {
        uint32_t i = 0;

        while (i < DestLenOutBytes)
        {
            uint32_t W;

            if (LocalStartWord >= EIP130TOKEN_RESULT_WORDS)
            {
                break;
            }

            // Read word
            W = ResultToken_p->W[LocalStartWord];
            LocalStartWord++;

            // LSB-first
            *LocalDest_p = (uint8_t)W;
            i++;
            if (i < DestLenOutBytes)
            {
                W >>= 8;
                LocalDest_p++;
                *LocalDest_p = (uint8_t)W;
                i++;
                if (i < DestLenOutBytes)
                {
                    W >>= 8;
                    LocalDest_p++;
                    *LocalDest_p = (uint8_t)W;
                    i++;
                    if (i < DestLenOutBytes)
                    {
                        W >>= 8;
                        LocalDest_p++;
                        *LocalDest_p = (uint8_t)W;
                        i++;
                        if (i < DestLenOutBytes)
                        {
                            LocalDest_p++;
                        }
                    }
                }
            }
        }
    }

    return;
}

/* end of file eip130_token_common.c */
