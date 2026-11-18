/* eip130_token_random.h
 *
 * Security Module Token helper functions
 * - Random token related functions and definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_RANDOM_H
#define INCLUDE_GUARD_EIP130TOKEN_RANDOM_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */

#define EIP130TOKEN_RANDOM_GENERATE_MAX_SIZE    65528      /* In bytes */

/*----------------------------------------------------------------------------
 * Eip130Token_Command_TRNG_Configure
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AutoSeed
 *     Setting that defines the automatic reseed after <AutoSeed> times
 *     64K Bytes of DRBG random generation.
 *
 * SampleCycles
 *     Setting that controls the number of (XOR-ed) FRO samples XOR-ed
 *     together to generate a single 'noise' bit. This value must be
 *     set such that the total amount of entropy in 8 'noise' bits
 *     equals at least 1 bit.
 *
 * SampleDiv
 *     Setting that controls the number of module clock cycles between
 *     samples taken from the FROs.
 *
 * NoiseBlocks
 *     Setting that defines number of 512 bit 'noise' blocks to process
 *     through the SHA-256 Conditioning function to generate a single
 *     256 bits 'full entropy' result for (re-)seeding the DRBG.
 *
 * RepCntCutoff
 *     'Cutoff' value for the NIST SP800-90B 'Repetition Count' test. The
 *     default setting for this value is 31, which corresponds to the cutoff
 *     value for a false positive rate of 2^-30 and 1 bit of entropy per 8-bit
 *     Noise Source sample.
 *     Setting this value to zero disables the 'Repetition Count' test.
 *
 * AdaptProp64Cutoff
 *     'Cutoff' value for the NIST SP800-90B 'Adaptive Proportion' test with a
 *     64 'noise samples' window. The default setting for this value is 56,
 *     which corresponds to the cutoff value for a false positive rate of
 *     2^-30 and 1 bit of entropy per 8-bit Noise Source sample.
 *     Setting this value to zero disables the 'Adaptive Proportion' test with
 *     a 64 'noise samples' window.
 *
 * AdaptProp512Cutoff
 *     'Cutoff' value for the NIST SP800-90B 'Adaptive Proportion' test with a
 *     512 'noise samples' window. The default setting for this value is 325,
 *     which corresponds to the cutoff value for a false positive rate of
 *     2^-30 and 1 bit of entropy per 8-bit Noise Source sample.
 *     Setting this value to zero disables the 'Adaptive Proportion' test with
 *     a 512 'noise samples' window.
 */
static inline void
Eip130Token_Command_TRNG_Configure(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t  AutoSeed,
        const uint16_t SampleCycles,
        const uint8_t  SampleDiv,
        const uint8_t  Scale,
        const uint8_t  NoiseBlocks,
        const uint8_t  RepCntCutoff,
        const uint8_t  AdaptProp64Cutoff,
        const uint16_t AdaptProp512Cutoff)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_TRNG |
                            EIP130TOKEN_SUBCODE_TRNGCONFIG);
    CommandToken_p->W[2] = ((Eip130TokenWord_t)AutoSeed << 8) | BIT_0;
    CommandToken_p->W[3] = ((Eip130TokenWord_t)SampleCycles << 16) |
                           (((Eip130TokenWord_t)SampleDiv & MASK_4_BITS) << 8) |
                           (((Eip130TokenWord_t)Scale & MASK_2_BITS) << 6) |
                           ((Eip130TokenWord_t)NoiseBlocks & MASK_5_BITS);
    CommandToken_p->W[4] = (((Eip130TokenWord_t)AdaptProp512Cutoff & MASK_9_BITS) << 16) |
                           (((Eip130TokenWord_t)AdaptProp64Cutoff & MASK_6_BITS) << 8) |
                           ((Eip130TokenWord_t)RepCntCutoff & MASK_6_BITS);
}


#ifdef EIP130_ENABLE_SYM_ALGO_ARIA_DRBG
/*----------------------------------------------------------------------------
 * Eip130Token_Command_TRNG_Configure_AriaDRBG
 *
 * This function set the TRNG configure indication that ARIA based DRBG shall
 * be used.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_TRNG_Configure_AriaDRBG(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[3] |= BIT_15;
}
#endif


/*----------------------------------------------------------------------------
 * Eip130Token_Command_PRNG_ReseedNow
 *
 * This function creates a command token that requests to reseed the TRNG.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_PRNG_ReseedNow(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_TRNG |
                            EIP130TOKEN_SUBCODE_TRNGCONFIG);
    CommandToken_p->W[2] = BIT_1;       /* RRD = Reseed DRBG with NRBG entropy */
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_RandomNumber_Generate
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * NumberLengthInBytes
 *     The number of random bytes to generate.
 *
 * OutputDataAddress
 *     DMA address of the buffer where the random number bytes will be written
 *     to. The size of the buffer must be an integer number of 32-bit words,
 *     equal or larger than NumberLengthInBytes.
 *     Note: When WriteTokenID is used, one more 32-bit word will be written.
 */
static inline void
Eip130Token_Command_RandomNumber_Generate(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t NumberLengthInBytes,
        const Eip130TokenDmaAddress_t OutputDataAddress)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_TRNG |
                            EIP130TOKEN_SUBCODE_RANDOMNUMBER);
    CommandToken_p->W[2] = (Eip130TokenWord_t)(NumberLengthInBytes);
    CommandToken_p->W[3] = (Eip130TokenWord_t)(OutputDataAddress);
    CommandToken_p->W[4] = (Eip130TokenWord_t)(OutputDataAddress >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_RandomNumber_SetRawKey
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_RandomNumber_SetRawKey(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t RawKey)
{
    CommandToken_p->W[2] |= ((Eip130TokenWord_t)RawKey << 16);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_RandomNumber_Generate
 *
 * This function extracts 'quality warning' details from a TRNG random number
 * generate result token.
 *
 * ResultToken_p
 *     Pointer to the result token buffer this function will read from.
 *
 * Return Value
 *     0    no warnings
 *     <0   Error code
 *     >0   the 5-bit Result code indicating some statistic anomaly in
 *          the generated random data.
 */
static inline Eip130FunctionStatus_t
Eip130Token_Result_RandomNumber_Generate(
        const Eip130Token_Result_t * const ResultToken_p)
{
    uint32_t tmp = ResultToken_p->W[0] >> 24U;
    Eip130FunctionStatus_t rv = (Eip130FunctionStatus_t)tmp;
    if (rv != 0)
    {
        if (((uint32_t)rv & (uint32_t)BIT_7) != 0U)
        {
            rv = -rv;
        }
        else if (((uint32_t)rv & ((uint32_t)BIT_6 | (uint32_t)BIT_5)) != (uint32_t)BIT_6)
        {
            rv = -rv;
        }
        else
        {
            tmp = (uint32_t)MASK_5_BITS;
            tmp = (uint32_t)rv & tmp;
            rv = (Eip130FunctionStatus_t)tmp;
        }
    }

    return rv;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_TRNG_PP_Verification
 *
 * This function initializes the TRNG post-processing verification token that
 * can be used to verify the SHA-2 Conditioning Function and AES-256 based
 * CTR-DRBG random number generator.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * TestRef
 *     Test to perform:
 *     0 - Conditioning Function with 12 bits repeating pattern
 *     1 - Conditioning Function with externally supplied 'noise' bits
 *     2 - DRBG data generation using known input data
 *
 * Pattern
 *     Repeating input pattern for the 'Conditioning Function with 12 bits
 *     repeating pattern' test. Please, read the Firmware Reference Manual
 *     for details.
 *
 * Size
 *     The actual value of Size depends on the test that is performed:
 *     0 - Number of 384 bits V & Key output blocks to generate in range 1-255.
 *     1 - Number of 384 bits V & Key output blocks to generate in range 1-255;
 *         the number of 512 bit 'noise blocks' to read equals the value given
 *         here times the NoiseBlocks value in the TRNG configuration token.
 *     2 - Splits the DataSize field in separate sub-fields:
 *         Bits [3:0]   = Total number of 384 bits seed blocks to read (range
 *                        1-15). The first is used for an 'Instantiate'
 *                        function, the others for a 're-seed' function.
 *         Bits [7:4]   = Number of 128-bit DRBG output words to generate in a
 *                        single data block (values 0-15 = 1-16 words).
 *         Bits [11:8]  = Number of data blocks to generate before each re-seed
 *                        (values 0-14 = 1-15 blocks, value 15 = 0 blocks).
 *         Bits [15:12] = Number of data blocks to generate after the last
 *                        re-seed (or 'Instantiate' if bits [3:0] are value 1).
 *                        Values 0-15 generate 1-16 blocks.
 *         Note: Using these sub-fields, several test-scenarios can be
 *               executed. Value 0x0002 performs an 'Instantiate-generate-
 *               reseed-generate' sequence while value 0x1F02 performs an
 *               'Instantiate-reseed-generate-generate' sequence.
 *
 * InputDataAddress
 *     DMA address of the buffer with the input data.
 *
 * OutputDataAddress
 *     DMA address of the buffer  in which the output data must be written.
 *
 * @return One of the ValStatus_t values.
 */
static inline void
Eip130Token_Command_TRNG_PP_Verification(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t TestRef,
        const uint16_t Pattern,
        const uint16_t Size,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const Eip130TokenDmaAddress_t OutputDataAddress)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_TRNG |
                            EIP130TOKEN_SUBCODE_VERIFYDRBG);
    CommandToken_p->W[2] = (((Eip130TokenWord_t)TestRef & MASK_4_BITS) << 28) |
                           (((Eip130TokenWord_t)Pattern & MASK_12_BITS) << 16) |
                           (Eip130TokenWord_t)Size;
    CommandToken_p->W[3] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[4] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    CommandToken_p->W[5] = (Eip130TokenWord_t)(OutputDataAddress);
    CommandToken_p->W[6] = (Eip130TokenWord_t)(OutputDataAddress >> 32);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_TRNG_HW_SelfTest
 *
 * This function initializes the TRNG hardware self-test verification token.
 * The self-test focuses on the following hardware-related functions:
 * - The NIST SP800-90B proposed 'Repetition Count' test on the noise source.
 * - The NIST SP800-90B proposed 'Adaptive Proportion' tests (with 64 and 512
 *   window sizes) on the noise source. and starts the True Random Number
 *   Generator (TRNG) and Deterministic Random Bit Generator (DRBG).
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * InputDataAddress
 *     DMA address of the buffer with the input data.
 *
 * SizeInBytes
 *     Size of the input data in bytes.
 *
 * RepCntCutoff
 *     'Cutoff' value for the NIST SP800-90B 'Repetition Count' test. The
 *     default setting for this value is 31, unless overruled here.
 *     Setting this value to zero disables the 'Repetition Count' test.
 *
 * RepCntCount
 *     Initial counter value for the NIST SP800-90B 'Repetition Count' test.
 *     Although it is possible to pre-load this counter, it will be reset to
 *     one (1) at the start of the test run.
 *
 * RepCntData
 *     Initial compare data value for the NIST SP800-90B 'Repetition Count'
 *     test. At the start of the test, this value indicates the last 8-bits
 *     'noise sample' value detected for repetition counting.
 *
 * AdaptProp64Cutoff
 *     'Cutoff' value for the NIST SP800-90B 'Adaptive Proportion' test with a
 *     64 'noise samples' window. The default setting for this value is 51,
 *     unless overruled here. Setting this value to zero disables the
 *     'Adaptive Proportion' test with a 64 'noise samples' window.
 *
 * AdaptProp64Count
 *     Initial counter value for the NIST SP800-90B 'Adaptive Proportion' test
 *     with a 64 'noise samples' window. Although it is possible to pre-load
 *     this counter, it will be reset to zero at the start of the test run.
 *
 * AdaptProp64Data
 *     Initial compare data value for the NIST SP800-90B 'Adaptive Proportion'
 *     test with a 64 'noise samples' window. Although this value is loaded
 *     into the HW compare register before the test run start, it will be
 *     overwritten immediately with the first 8-bits 'noise sample' in the
 *     test data stream.
 *
 * AdaptProp512Cutoff
 *     'Cutoff' value for the NIST SP800-90B 'Adaptive Proportion' test with a
 *     512 'noise samples' window. The default setting for this value is 325,
 *     unless overruled here. Setting this value to zero disables the 'Adaptive
 *     Proportion' test with a 512 'noise samples' window..
 *
 * AdaptProp512Count
 *     Initial counter value for the NIST SP800-90B 'Adaptive Proportion' test
 *     with a 512 'noise samples' window. Although it is possible to pre-load
 *     this counter, it will be reset to zero at the start of the test run.
 *
 * AdaptProp512Data
 *     Initial compare data value for the NIST SP800-90B 'Adaptive Proportion'
 *     test with a 512 'noise samples' window. Although this value is loaded
 *     into the HW compare register before the test run start, it will be
 *     overwritten immediately with the first 8-bits 'noise sample' in the
 *     test data stream.
 */
static inline void
Eip130Token_Command_TRNG_HW_SelfTest(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenDmaAddress_t InputDataAddress,
        const uint16_t SizeInBytes,
        const uint8_t RepCntCutoff,
        const uint8_t RepCntCount,
        const uint8_t RepCntData,
        const uint8_t AdaptProp64Cutoff,
        const uint8_t AdaptProp64Count,
        const uint8_t AdaptProp64Data,
        const uint16_t AdaptProp512Cutoff,
        const uint16_t AdaptProp512Count,
        const uint8_t AdaptProp512Data)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_TRNG |
                            EIP130TOKEN_SUBCODE_VERIFYNRBG);
    CommandToken_p->W[2] = (Eip130TokenWord_t)SizeInBytes;
    CommandToken_p->W[3] = (Eip130TokenWord_t)(InputDataAddress);
    CommandToken_p->W[4] = (Eip130TokenWord_t)(InputDataAddress >> 32);
    if ((RepCntCutoff != 0U) || (AdaptProp64Cutoff != 0U) || (AdaptProp512Cutoff != 0U))
    {
        CommandToken_p->W[2] |= BIT_29;
        CommandToken_p->W[5] = (((Eip130TokenWord_t)AdaptProp512Cutoff & MASK_9_BITS) << 16) |
                               (((Eip130TokenWord_t)AdaptProp64Cutoff & MASK_6_BITS) << 8) |
                               ((Eip130TokenWord_t)RepCntCutoff & MASK_6_BITS);
    }
    if ((RepCntCount != 0U) || (AdaptProp64Count != 0U) || (AdaptProp512Count != 0U))
    {
        CommandToken_p->W[2] |= BIT_30;
        CommandToken_p->W[6] = (((Eip130TokenWord_t)AdaptProp512Count & MASK_9_BITS) << 16) |
                               (((Eip130TokenWord_t)AdaptProp64Count & MASK_6_BITS) << 8) |
                               ((Eip130TokenWord_t)RepCntCount & MASK_6_BITS);
    }
    if ((RepCntData != 0U) || (AdaptProp64Data != 0U) || (AdaptProp512Data != 0U))
    {
        CommandToken_p->W[2] |= BIT_31;
        CommandToken_p->W[7] = ((Eip130TokenWord_t)AdaptProp512Data << 16) |
                               ((Eip130TokenWord_t)AdaptProp64Data << 8) |
                               ((Eip130TokenWord_t)RepCntData);
    }
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_TRNG_HW_SelfTest
 *
 * This function extracts the TRNG hardware self-test verification information.
 *
 * ResultToken_p
 *     Pointer to the result token buffer this function will read from.
 *
 * RepCntCutoff
 *     Pointer to a buffer where the 'Cutoff' value for the NIST SP800-90B
 *     'Repetition Count' test must be written, as present in the engine at
 *     the end of the test run.
 *
 * RepCntCount
 *     Pointer to a buffer where the counter value for the NIST SP800-90B
 *     'Repetition Count' test must be written, as present in the engine at
 *     the end of the test run.
 *
 * RepCntData
 *     Pointer to a buffer where the compare data value for the NIST SP800-90B
 *     'Repetition Count' test must be written, as present in the engine at
 *     the end of the test run.
 *
 * AdaptProp64Cutoff
 *     Pointer to a buffer where the 'Cutoff' value for the NIST SP800-90B
 *     'Adaptive Proportion' test with a 64 'noise samples' window must be
 *     written, as present in the engine at the end of the test run.
 *
 * AdaptProp64Count
 *     Pointer to a buffer where the counter value for the NIST SP800-90B
 *     'Adaptive Proportion' test with a 64 'noise samples' window must be
 *     written, as present in the engine at the end of the test run.
 *
 * AdaptProp64Data
 *     Pointer to a buffer where the compare data value for the NIST SP800-90B
 *     'Adaptive Proportion' test with a 64 'noise samples' window must be
 *     written, as present in the engine at the end of the test run.
 *
 * AdaptProp64Fail
 *     Pointer to a buffer where the failure indication for the NIST SP800-90B
 *     'Adaptive Proportion' test with a 64 'noise samples' window must be
 *     written.
 *
 * AdaptProp512Cutoff
 *     Pointer to a buffer where the 'Cutoff' value for the NIST SP800-90B
 *     'Adaptive Proportion' test with a 512 'noise samples' window must be
 *     written, as present in the engine at the end of the test run.
 *
 * AdaptProp512Count
 *     Pointer to a buffer where the counter value for the NIST SP800-90B
 *     'Adaptive Proportion' test with a 512 'noise samples' window must be
 *     written, as present in the engine at the end of the test run.
 *
 * AdaptProp512Data
 *     Pointer to a buffer where the compare data value for the NIST SP800-90B
 *     'Adaptive Proportion' test with a 512 'noise samples' window must be
 *     written, as present in the engine at the end of the test run.
 *
 * AdaptProp512Fail
 *     Pointer to a buffer where the failure indication for the NIST SP800-90B
 *     'Adaptive Proportion' test with a 512 'noise samples' window must be
 *     written.
 */
static inline void
Eip130Token_Result_TRNG_HW_SelfTest(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * const RepCntCutoff,
        uint8_t * const RepCntCount,
        uint8_t * const RepCntData,
        uint8_t * const AdaptProp64Cutoff,
        uint8_t * const AdaptProp64Count,
        uint8_t * const AdaptProp64Data,
        uint8_t * const AdaptProp64Fail,
        uint16_t * const AdaptProp512Cutoff,
        uint16_t * const AdaptProp512Count,
        uint8_t * const AdaptProp512Data,
        uint8_t * const AdaptProp512Fail)
{
    *RepCntCutoff = (uint8_t)(ResultToken_p->W[1] & MASK_6_BITS);
    *RepCntCount = (uint8_t)(ResultToken_p->W[2] & MASK_6_BITS);
    *RepCntData = (uint8_t)ResultToken_p->W[3];
    *AdaptProp64Cutoff = (uint8_t)((ResultToken_p->W[1] >> 8) & MASK_6_BITS);
    *AdaptProp64Count = (uint8_t)((ResultToken_p->W[2] >> 8) & MASK_6_BITS);
    *AdaptProp64Data = (uint8_t)(ResultToken_p->W[3] >> 8);
    *AdaptProp64Fail = (uint8_t)((ResultToken_p->W[3] >> 30) & MASK_1_BIT);
    *AdaptProp512Cutoff = (uint16_t)((ResultToken_p->W[1] >> 16) & MASK_9_BITS);
    *AdaptProp512Count = (uint16_t)((ResultToken_p->W[2] >> 16) & MASK_9_BITS);
    *AdaptProp512Data = (uint8_t)(ResultToken_p->W[3] >> 16);
    *AdaptProp512Fail = (uint8_t)((ResultToken_p->W[3] >> 31) & MASK_1_BIT);
}


#ifdef EIP130_ENABLE_DRBG_FORCESEED
/*----------------------------------------------------------------------------
* Eip130Token_Command_DRBG_ForceSeed
*
* CommandToken_p
*     Pointer to the command token buffer.
*
* AutoSeed
*     The setting that defines the threshold for the amount of random data that
*     can be extracted from the DRBG. The threshold is 'AutoSeed' times 64K
*     Bytes.
*
* Seed_p
*     The 384-bit seed that must be used to start the DRBG.
*/
static inline void
Eip130Token_Command_DRBG_ForceSeed(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t  AutoSeed,
        const uint8_t * const Seed_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_TRNG |
                            EIP130TOKEN_SUBCODE_TRNGCONFIG);
    CommandToken_p->W[2] = ((Eip130TokenWord_t)AutoSeed << 8) | BIT_7;

    Eip130Token_Command_WriteByteArray(CommandToken_p, 4U,
                                       Seed_p, (uint32_t)(384/4));
}
#endif


#endif /* INCLUDE_GUARD_EIP130TOKEN_RANDOM_H */

/* end of file eip130_token_random.h */
