/* eip130_token_common.h
 *
 * Security Module Token helper functions
 * - Common token related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_COMMON_H
#define INCLUDE_GUARD_EIP130TOKEN_COMMON_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/MailboxControl/src/c_eip130.h>               /* EIP-130 configuration */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_result.h>    /* EIP130TOKEN_RESULT_FASVC */


/* Function return status
 * In general:
 *      0   Success/No error
 *     >0   Warning code
 *     <0   Error code
 */
typedef int32_t Eip130FunctionStatus_t;

/* Register word */
typedef uint32_t Eip130RegisterWord_t;

/* Token word and other token related type defines */
typedef uint32_t Eip130TokenWord_t;
typedef uint32_t Eip130TokenAssetId_t;
typedef uint32_t Eip130TokenDmaSize_t;
typedef uint64_t Eip130TokenDmaAddress_t;

/* Command Token */
#define EIP130TOKEN_COMMAND_WORDS   64U
typedef struct
{
    Eip130TokenWord_t W[EIP130TOKEN_COMMAND_WORDS];
} Eip130Token_Command_t;

/* Result Token */
#define EIP130TOKEN_RESULT_WORDS    64U
typedef struct
{
    Eip130TokenWord_t W[EIP130TOKEN_RESULT_WORDS];
} Eip130Token_Result_t;

/* Token operation codes */
#define EIP130TOKEN_OPCODE_NOP                    ((Eip130TokenWord_t)0UL << 24)
#define EIP130TOKEN_OPCODE_ENCRYPTION             ((Eip130TokenWord_t)1UL << 24)
#define EIP130TOKEN_OPCODE_HASH                   ((Eip130TokenWord_t)2UL << 24)
#define EIP130TOKEN_OPCODE_MAC                    ((Eip130TokenWord_t)3UL << 24)
#define EIP130TOKEN_OPCODE_TRNG                   ((Eip130TokenWord_t)4UL << 24)
#define EIP130TOKEN_OPCODE_SPECIALFUNCTIONS       ((Eip130TokenWord_t)5UL << 24)
#define EIP130TOKEN_OPCODE_SYMWRAP                ((Eip130TokenWord_t)6UL << 24)
#define EIP130TOKEN_OPCODE_ASSETMANAGEMENT        ((Eip130TokenWord_t)7UL << 24)
#define EIP130TOKEN_OPCODE_AUTH_UNLOCK            ((Eip130TokenWord_t)8UL << 24)
#define EIP130TOKEN_OPCODE_PUBLIC_KEY             ((Eip130TokenWord_t)9UL << 24)
#define EIP130TOKEN_OPCODE_SERVICE                ((Eip130TokenWord_t)14UL << 24)
#define EIP130TOKEN_OPCODE_SYSTEM                 ((Eip130TokenWord_t)15UL << 24)

/* Token sub codes */
/* TRNG operations */
#define EIP130TOKEN_SUBCODE_RANDOMNUMBER          ((Eip130TokenWord_t)0UL << 28)
#define EIP130TOKEN_SUBCODE_TRNGCONFIG            ((Eip130TokenWord_t)1UL << 28)
#define EIP130TOKEN_SUBCODE_VERIFYDRBG            ((Eip130TokenWord_t)2UL << 28)
#define EIP130TOKEN_SUBCODE_VERIFYNRBG            ((Eip130TokenWord_t)3UL << 28)
/* Asset Management operations */
#define EIP130TOKEN_SUBCODE_ASSETSEARCH           ((Eip130TokenWord_t)0UL << 28)
#define EIP130TOKEN_SUBCODE_ASSETCREATE           ((Eip130TokenWord_t)1UL << 28)
#define EIP130TOKEN_SUBCODE_ASSETLOAD             ((Eip130TokenWord_t)2UL << 28)
#define EIP130TOKEN_SUBCODE_ASSETDELETE           ((Eip130TokenWord_t)3UL << 28)
#define EIP130TOKEN_SUBCODE_PUBLICDATA            ((Eip130TokenWord_t)4UL << 28)
#define EIP130TOKEN_SUBCODE_MONOTONICREAD         ((Eip130TokenWord_t)5UL << 28)
#define EIP130TOKEN_SUBCODE_MONOTONICINCR         ((Eip130TokenWord_t)6UL << 28)
#define EIP130TOKEN_SUBCODE_OTPDATAWRITE          ((Eip130TokenWord_t)7UL << 28)
#define EIP130TOKEN_SUBCODE_SECURETIMER           ((Eip130TokenWord_t)8UL << 28)
#define EIP130TOKEN_SUBCODE_PROVISIONRANDOMHUK    ((Eip130TokenWord_t)9UL << 28)
#define EIP130TOKEN_SUBCODE_CPIF_EXPORT           ((Eip130TokenWord_t)10UL << 28)
#define EIP130TOKEN_SUBCODE_ASSETSTORERESET       ((Eip130TokenWord_t)15UL << 28)
/* KeyWrap and Encrypt vector operations */
#define EIP130TOKEN_SUBCODE_SYMKEYWRAP            ((Eip130TokenWord_t)0UL << 28)
#define EIP130TOKEN_SUBCODE_ENCRYPTVECTOR         ((Eip130TokenWord_t)1UL << 28)
/* Special Functions operations */
#define EIP130TOKEN_SUBCODE_SF_MILENAGE           ((Eip130TokenWord_t)0UL << 28)
/* Authenticated Unlock operations */
#define EIP130TOKEN_SUBCODE_AUNLOCKSTART          ((Eip130TokenWord_t)0UL << 28)
#define EIP130TOKEN_SUBCODE_AUNLOCKVERIFY         ((Eip130TokenWord_t)1UL << 28)
#define EIP130TOKEN_SUBCODE_SETSECUREDEBUG        ((Eip130TokenWord_t)2UL << 28)
/* Public key operations */
#define EIP130TOKEN_SUBCODE_PK_NOASSETS           ((Eip130TokenWord_t)0UL << 28)
#define EIP130TOKEN_SUBCODE_PK_WITHASSETS         ((Eip130TokenWord_t)1UL << 28)
/* Service operations */
#define EIP130TOKEN_SUBCODE_REGISTERREAD          ((Eip130TokenWord_t)0UL << 28)
#define EIP130TOKEN_SUBCODE_REGISTERWRITE         ((Eip130TokenWord_t)1UL << 28)
#define EIP130TOKEN_SUBCODE_CLOCKSWITCH           ((Eip130TokenWord_t)2UL << 28)
#define EIP130TOKEN_SUBCODE_ZEROOUTMAILBOX        ((Eip130TokenWord_t)3UL << 28)
#define EIP130TOKEN_SUBCODE_SELECTOTPZERO         ((Eip130TokenWord_t)4UL << 28)
#define EIP130TOKEN_SUBCODE_ZEROIZEOTP            ((Eip130TokenWord_t)5UL << 28)
#define EIP130TOKEN_SUBCODE_FIRMWARECHECK         ((Eip130TokenWord_t)6UL << 28)
#define EIP130TOKEN_SUBCODE_UPDATEROLLBACKID      ((Eip130TokenWord_t)7UL << 28)
/* System operations */
#define EIP130TOKEN_SUBCODE_SYSTEMINFO            ((Eip130TokenWord_t)0UL << 28)
#define EIP130TOKEN_SUBCODE_SELFTEST              ((Eip130TokenWord_t)1UL << 28)
#define EIP130TOKEN_SUBCODE_RESET                 ((Eip130TokenWord_t)2UL << 28)
#define EIP130TOKEN_SUBCODE_LOGIN                 ((Eip130TokenWord_t)3UL << 28)
#define EIP130TOKEN_SUBCODE_SLEEP                 ((Eip130TokenWord_t)4UL << 28)
#define EIP130TOKEN_SUBCODE_RESUMEFROMSLEEP       ((Eip130TokenWord_t)5UL << 28)
#define EIP130TOKEN_SUBCODE_SETTIME               ((Eip130TokenWord_t)8UL << 28)

/* Token/HW/Algorithm related limits */
#define EIP130TOKEN_DMA_MAXLENGTH           0x001FFFFFU /* 2 MB - 1 bytes */
#define EIP130TOKEN_DMA_TOKENID_SIZE        4U          /* bytes */
#define EIP130TOKEN_DMA_ARC4_STATE_BUF_SIZE 256U        /* bytes */

/* DMA data block must be an integer multiple of a work block size (in bytes) */
#define EIP130TOKEN_DMA_ALGO_BLOCKSIZE_HASH 64U
#define EIP130TOKEN_DMA_ALGO_BLOCKSIZE_AES  16U
#define EIP130TOKEN_DMA_ALGO_BLOCKSIZE_DES  8U
#define EIP130TOKEN_DMA_ALGO_BLOCKSIZE_ARC4 4U
#define EIP130TOKEN_DMA_ALGO_BLOCKSIZE_NOP  4U


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Clear
 *
 * This function initializes a Eip130Token_Command_t array with a known
 * pattern. This helps debugging.
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_Clear(
        Eip130Token_Command_t * const CommandToken_p)
{
    uint32_t i;

    for (i = 0; i < EIP130TOKEN_COMMAND_WORDS; i++)
    {
        CommandToken_p->W[i] = 0xAAAAAAAA;
    }
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Identity
 *
 * This function sets the token identity.
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 *
 * Identity
 *      A 32-bit value to identify the user.
 */
static inline void
Eip130Token_Command_Identity(
        Eip130Token_Command_t * const CommandToken_p,
        uint32_t Identity)
{
    CommandToken_p->W[1] = Identity;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SetTokenID
 *
 * This function sets the TokenID related field in the Command Token. The SM
 * will copy this value to the Result Token.
 * This can also be used for data stream synchronization: the TokenID is
 * appended to the end of the DMA stream. This word must be initialized to a
 * different value and then polled until the expected TokenID value/pattern
 * shows up.
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 *
 * TokenIDValue
 *      The 16 bit TokenID value that the SM will write to the Result Token
 *      and optionally appends to the end of the output DMA data stream.
 *
 * fWriteTokenID
 *      false  do not append TokenID to DMA data stream.
 *      true   write TokenID at end of DMA data stream. The stream will first
 *             be padded with zeros until a complete 32bit word before an extra
 *             32bit word is output with the TokenID in it.
 */
static inline void
Eip130Token_Command_SetTokenID(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t TokenIDValue,
        const bool fWriteTokenID)
{
    /* Replace TokenID field (word 0, lowest 16 bits) with TokenIDValue and
     * reset Write Token ID indication */
    CommandToken_p->W[0] &= (((Eip130TokenWord_t)MASK_16_BITS << 16) - BIT_18);
    CommandToken_p->W[0] |= TokenIDValue;
    if (fWriteTokenID)
    {
        /* Set Write Token ID field (word 0, bit 18) */
        CommandToken_p->W[0] |= BIT_18;
    }
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_Code
 *
 * This function extracts the result information from the result token.
 * This function can be used on any result token.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * Return Value
 *     0    No error or warning
 *     >0   warning code
 *     <0   Error code
 *     Note that FAsvc bit is returned on bit position 16
 */
static inline Eip130FunctionStatus_t
Eip130Token_Result_Code(
        const Eip130Token_Result_t * const ResultToken_p)
{
    Eip130TokenWord_t result;
    Eip130TokenWord_t FAsvc;
    Eip130FunctionStatus_t rv;

    result = ResultToken_p->W[0] >> 24;
    FAsvc = ResultToken_p->W[0] & EIP130TOKEN_RESULT_FASVC;

    if ((result & (Eip130TokenWord_t)BIT_7) != 0U)
    {
        uint32_t tmp = MASK_7_BITS;

        tmp = (result & tmp);
        rv = -((Eip130FunctionStatus_t)tmp);
        if (FAsvc == 0U)
        {
            tmp = ((uint32_t)rv & ~(uint32_t)EIP130TOKEN_RESULT_FASVC);
            rv  = (Eip130FunctionStatus_t)tmp;
        }
    }
    else
    {
        result |= FAsvc;
        rv = (Eip130FunctionStatus_t)result;
    }
    return rv;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_WriteByteArray
 *
 * This function fills a consecutive number of words in the command token with
 * bytes from an array. Four consecutive bytes form a 32bit word, LSB-first.
 *
 * CommandToken_p
 *      Pointer to the command token buffer.
 *
 * StartWord
 *      Start index in command token.
 *
 * Data_p
 *      Pointer to the data to write to the command token.
 *
 * DataLenInBytes
 *      Number of bytes to write.
 */
void
Eip130Token_Command_WriteByteArray(
        Eip130Token_Command_t * const CommandToken_p,
        uint32_t StartWord,
        const uint8_t * Data_p,
        const uint32_t DataLenInBytes);


/*----------------------------------------------------------------------------
 * Eip130Token_Result_ReadByteArray
 *
 * This function reads a number of consecutive words from the result token
 * and writes these to a byte array, breaking down each word into bytes, LSB
 * first.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * StartWord
 *      Start index in result token.
 *
 * DestLenInBytes
 *      Number of bytes to write.
 *
 * Dest_p
 *      Pointer to the data buffer to copy the data from the result token into.
 */
void
Eip130Token_Result_ReadByteArray(
        const Eip130Token_Result_t * const ResultToken_p,
        uint32_t StartWord,
        uint32_t DestLenOutBytes,
        uint8_t * Dest_p);


#endif /* INCLUDE_GUARD_EIP130TOKEN_COMMON_H */

/* end of file eip130_token_common.h */
