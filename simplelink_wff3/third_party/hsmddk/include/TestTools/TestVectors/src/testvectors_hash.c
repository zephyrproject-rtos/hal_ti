/* testvectors_hash.c
 *
 * Description: Test vectors for hash algorithms
 *              MD5, SHA1, SHA2_224 and SHA2_256.
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

#include <third_party/hsmddk/include/Config/cs_eip130.h>

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_hash.h"
#include "testvectors_hash_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_HASH(alg, msg, msglen, result) \
    {                                              \
        TESTVECTORS_HASH_##alg,                    \
        msg, result,                               \
        msglen, sizeof(result)                     \
    }

static const TestVector_HASH_Rec_t
hash_test_vectors [] = {
    TEST_VECTOR_HASH(SHA160, null_msg, 0, SHA1_0_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_1_bytes_msg, 1, SHA1_1_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_2_bytes_msg, 2, SHA1_2_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_3_bytes_msg, 3, SHA1_3_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_4_bytes_msg, 4, SHA1_4_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_5_bytes_msg, 5, SHA1_5_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_6_bytes_msg, 6, SHA1_6_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_7_bytes_msg, 7, SHA1_7_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_8_bytes_msg, 8, SHA1_8_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_9_bytes_msg, 9, SHA1_9_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_10_bytes_msg, 10, SHA1_10_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_11_bytes_msg, 11, SHA1_11_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_12_bytes_msg, 12, SHA1_12_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_13_bytes_msg, 13, SHA1_13_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_14_bytes_msg, 14, SHA1_14_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_15_bytes_msg, 15, SHA1_15_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_16_bytes_msg, 16, SHA1_16_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_17_bytes_msg, 17, SHA1_17_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_18_bytes_msg, 18, SHA1_18_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_19_bytes_msg, 19, SHA1_19_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_20_bytes_msg, 20, SHA1_20_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_21_bytes_msg, 21, SHA1_21_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_22_bytes_msg, 22, SHA1_22_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_23_bytes_msg, 23, SHA1_23_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_24_bytes_msg, 24, SHA1_24_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_25_bytes_msg, 25, SHA1_25_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_26_bytes_msg, 26, SHA1_26_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_27_bytes_msg, 27, SHA1_27_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_28_bytes_msg, 28, SHA1_28_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_29_bytes_msg, 29, SHA1_29_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_30_bytes_msg, 30, SHA1_30_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_31_bytes_msg, 31, SHA1_31_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_32_bytes_msg, 32, SHA1_32_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_33_bytes_msg, 33, SHA1_33_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_34_bytes_msg, 34, SHA1_34_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_35_bytes_msg, 35, SHA1_35_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_36_bytes_msg, 36, SHA1_36_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_37_bytes_msg, 37, SHA1_37_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_38_bytes_msg, 38, SHA1_38_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_39_bytes_msg, 39, SHA1_39_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_40_bytes_msg, 40, SHA1_40_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_41_bytes_msg, 41, SHA1_41_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_42_bytes_msg, 42, SHA1_42_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_43_bytes_msg, 43, SHA1_43_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_44_bytes_msg, 44, SHA1_44_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_45_bytes_msg, 45, SHA1_45_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_46_bytes_msg, 46, SHA1_46_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_47_bytes_msg, 47, SHA1_47_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_48_bytes_msg, 48, SHA1_48_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_49_bytes_msg, 49, SHA1_49_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_50_bytes_msg, 50, SHA1_50_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_51_bytes_msg, 51, SHA1_51_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_52_bytes_msg, 52, SHA1_52_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_53_bytes_msg, 53, SHA1_53_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_54_bytes_msg, 54, SHA1_54_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_55_bytes_msg, 55, SHA1_55_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_56_bytes_msg, 56, SHA1_56_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_57_bytes_msg, 57, SHA1_57_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_58_bytes_msg, 58, SHA1_58_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_59_bytes_msg, 59, SHA1_59_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_60_bytes_msg, 60, SHA1_60_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_61_bytes_msg, 61, SHA1_61_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_62_bytes_msg, 62, SHA1_62_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_63_bytes_msg, 63, SHA1_63_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_64_bytes_msg, 64, SHA1_64_bytes_digest),
    TEST_VECTOR_HASH(SHA160, SHA1_6400_bytes_msg, 6400, SHA1_6400_bytes_digest),
    TEST_VECTOR_HASH(SHA224, null_msg, 0, SHA224_0_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_1_bytes_msg, 1, SHA224_1_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_2_bytes_msg, 2, SHA224_2_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_3_bytes_msg, 3, SHA224_3_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_4_bytes_msg, 4, SHA224_4_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_5_bytes_msg, 5, SHA224_5_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_6_bytes_msg, 6, SHA224_6_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_7_bytes_msg, 7, SHA224_7_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_8_bytes_msg, 8, SHA224_8_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_9_bytes_msg, 9, SHA224_9_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_10_bytes_msg, 10, SHA224_10_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_11_bytes_msg, 11, SHA224_11_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_12_bytes_msg, 12, SHA224_12_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_13_bytes_msg, 13, SHA224_13_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_14_bytes_msg, 14, SHA224_14_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_15_bytes_msg, 15, SHA224_15_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_16_bytes_msg, 16, SHA224_16_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_17_bytes_msg, 17, SHA224_17_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_18_bytes_msg, 18, SHA224_18_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_19_bytes_msg, 19, SHA224_19_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_20_bytes_msg, 20, SHA224_20_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_21_bytes_msg, 21, SHA224_21_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_22_bytes_msg, 22, SHA224_22_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_23_bytes_msg, 23, SHA224_23_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_24_bytes_msg, 24, SHA224_24_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_25_bytes_msg, 25, SHA224_25_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_26_bytes_msg, 26, SHA224_26_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_27_bytes_msg, 27, SHA224_27_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_28_bytes_msg, 28, SHA224_28_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_29_bytes_msg, 29, SHA224_29_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_30_bytes_msg, 30, SHA224_30_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_31_bytes_msg, 31, SHA224_31_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_32_bytes_msg, 32, SHA224_32_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_33_bytes_msg, 33, SHA224_33_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_34_bytes_msg, 34, SHA224_34_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_35_bytes_msg, 35, SHA224_35_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_36_bytes_msg, 36, SHA224_36_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_37_bytes_msg, 37, SHA224_37_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_38_bytes_msg, 38, SHA224_38_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_39_bytes_msg, 39, SHA224_39_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_40_bytes_msg, 40, SHA224_40_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_41_bytes_msg, 41, SHA224_41_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_42_bytes_msg, 42, SHA224_42_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_43_bytes_msg, 43, SHA224_43_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_44_bytes_msg, 44, SHA224_44_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_45_bytes_msg, 45, SHA224_45_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_46_bytes_msg, 46, SHA224_46_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_47_bytes_msg, 47, SHA224_47_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_48_bytes_msg, 48, SHA224_48_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_49_bytes_msg, 49, SHA224_49_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_50_bytes_msg, 50, SHA224_50_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_51_bytes_msg, 51, SHA224_51_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_52_bytes_msg, 52, SHA224_52_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_53_bytes_msg, 53, SHA224_53_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_54_bytes_msg, 54, SHA224_54_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_55_bytes_msg, 55, SHA224_55_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_56_bytes_msg, 56, SHA224_56_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_57_bytes_msg, 57, SHA224_57_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_58_bytes_msg, 58, SHA224_58_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_59_bytes_msg, 59, SHA224_59_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_60_bytes_msg, 60, SHA224_60_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_61_bytes_msg, 61, SHA224_61_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_62_bytes_msg, 62, SHA224_62_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_63_bytes_msg, 63, SHA224_63_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_64_bytes_msg, 64, SHA224_64_bytes_digest),
    TEST_VECTOR_HASH(SHA224, SHA224_6400_bytes_msg, 6400, SHA224_6400_bytes_digest),
    TEST_VECTOR_HASH(SHA256, null_msg, 0, SHA256_0_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_1_bytes_msg, 1, SHA256_1_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_2_bytes_msg, 2, SHA256_2_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_3_bytes_msg, 3, SHA256_3_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_4_bytes_msg, 4, SHA256_4_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_5_bytes_msg, 5, SHA256_5_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_6_bytes_msg, 6, SHA256_6_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_7_bytes_msg, 7, SHA256_7_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_8_bytes_msg, 8, SHA256_8_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_9_bytes_msg, 9, SHA256_9_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_10_bytes_msg, 10, SHA256_10_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_11_bytes_msg, 11, SHA256_11_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_12_bytes_msg, 12, SHA256_12_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_13_bytes_msg, 13, SHA256_13_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_14_bytes_msg, 14, SHA256_14_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_15_bytes_msg, 15, SHA256_15_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_16_bytes_msg, 16, SHA256_16_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_17_bytes_msg, 17, SHA256_17_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_18_bytes_msg, 18, SHA256_18_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_19_bytes_msg, 19, SHA256_19_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_20_bytes_msg, 20, SHA256_20_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_21_bytes_msg, 21, SHA256_21_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_22_bytes_msg, 22, SHA256_22_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_23_bytes_msg, 23, SHA256_23_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_24_bytes_msg, 24, SHA256_24_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_25_bytes_msg, 25, SHA256_25_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_26_bytes_msg, 26, SHA256_26_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_27_bytes_msg, 27, SHA256_27_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_28_bytes_msg, 28, SHA256_28_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_29_bytes_msg, 29, SHA256_29_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_30_bytes_msg, 30, SHA256_30_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_31_bytes_msg, 31, SHA256_31_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_32_bytes_msg, 32, SHA256_32_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_33_bytes_msg, 33, SHA256_33_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_34_bytes_msg, 34, SHA256_34_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_35_bytes_msg, 35, SHA256_35_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_36_bytes_msg, 36, SHA256_36_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_37_bytes_msg, 37, SHA256_37_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_38_bytes_msg, 38, SHA256_38_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_39_bytes_msg, 39, SHA256_39_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_40_bytes_msg, 40, SHA256_40_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_41_bytes_msg, 41, SHA256_41_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_42_bytes_msg, 42, SHA256_42_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_43_bytes_msg, 43, SHA256_43_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_44_bytes_msg, 44, SHA256_44_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_45_bytes_msg, 45, SHA256_45_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_46_bytes_msg, 46, SHA256_46_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_47_bytes_msg, 47, SHA256_47_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_48_bytes_msg, 48, SHA256_48_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_49_bytes_msg, 49, SHA256_49_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_50_bytes_msg, 50, SHA256_50_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_51_bytes_msg, 51, SHA256_51_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_52_bytes_msg, 52, SHA256_52_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_53_bytes_msg, 53, SHA256_53_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_54_bytes_msg, 54, SHA256_54_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_55_bytes_msg, 55, SHA256_55_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_56_bytes_msg, 56, SHA256_56_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_57_bytes_msg, 57, SHA256_57_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_58_bytes_msg, 58, SHA256_58_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_59_bytes_msg, 59, SHA256_59_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_60_bytes_msg, 60, SHA256_60_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_61_bytes_msg, 61, SHA256_61_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_62_bytes_msg, 62, SHA256_62_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_63_bytes_msg, 63, SHA256_63_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_64_bytes_msg, 64, SHA256_64_bytes_digest),
    TEST_VECTOR_HASH(SHA256, SHA256_6400_bytes_msg, 6400, SHA256_6400_bytes_digest),
    TEST_VECTOR_HASH(SHA384, null_msg, 0, SHA384_0_bytes_digest),
    TEST_VECTOR_HASH(SHA384, SHA256_1_bytes_msg, 1, SHA384_1_bytes_digest),
    TEST_VECTOR_HASH(SHA384, SHA256_16_bytes_msg, 16, SHA384_16_bytes_digest),
    TEST_VECTOR_HASH(SHA384, SHA256_6400_bytes_msg, 6400, SHA384_6400_bytes_digest),
    TEST_VECTOR_HASH(SHA512, null_msg, 0, SHA512_0_bytes_digest),
    TEST_VECTOR_HASH(SHA512, SHA256_1_bytes_msg, 1, SHA512_1_bytes_digest),
    TEST_VECTOR_HASH(SHA512, SHA256_16_bytes_msg, 16, SHA512_16_bytes_digest),
    TEST_VECTOR_HASH(SHA512, SHA256_6400_bytes_msg, 6400, SHA512_6400_bytes_digest),
    TEST_VECTOR_HASH(SHA512, SHA256_6400_bytes_msg, 6400, SHA512_6400_bytes_digest),
    TEST_VECTOR_HASH(SHA512, SHA256_6400_bytes_msg, 6400, SHA512_6400_bytes_digest),
    //SHA3 testvectors from https://www.di-mgt.com.au/sha_testvectors.html
    TEST_VECTOR_HASH(SHA3_224, SHA3_3_bytes_msg, 3, SHA3_224_3_bytes_digest),
    TEST_VECTOR_HASH(SHA3_224, SHA3_56_bytes_msg, 56, SHA3_224_56_bytes_digest),
    TEST_VECTOR_HASH(SHA3_224, SHA3_112_bytes_msg, 112, SHA3_224_112_bytes_digest),
    TEST_VECTOR_HASH(SHA3_224, SHA3_144_bytes_msg, 144, SHA3_224_144_bytes_digest),
    TEST_VECTOR_HASH(SHA3_224, SHA3_150_bytes_msg, 150, SHA3_224_150_bytes_digest),

    TEST_VECTOR_HASH(SHA3_256, SHA3_3_bytes_msg, 3, SHA3_256_3_bytes_digest),
    TEST_VECTOR_HASH(SHA3_256, SHA3_56_bytes_msg, 56, SHA3_256_56_bytes_digest),
    TEST_VECTOR_HASH(SHA3_256, SHA3_112_bytes_msg, 112, SHA3_256_112_bytes_digest),
    TEST_VECTOR_HASH(SHA3_256, SHA3_136_bytes_msg, 136, SHA3_256_136_bytes_digest),
    TEST_VECTOR_HASH(SHA3_256, SHA3_150_bytes_msg, 150, SHA3_256_150_bytes_digest),

    TEST_VECTOR_HASH(SHA3_384, SHA3_3_bytes_msg, 3, SHA3_384_3_bytes_digest),
    TEST_VECTOR_HASH(SHA3_384, SHA3_56_bytes_msg, 56, SHA3_384_56_bytes_digest),
    TEST_VECTOR_HASH(SHA3_384, SHA3_104_bytes_msg, 104, SHA3_384_104_bytes_digest),
    TEST_VECTOR_HASH(SHA3_384, SHA3_112_bytes_msg, 112, SHA3_384_112_bytes_digest),
    TEST_VECTOR_HASH(SHA3_384, SHA3_150_bytes_msg, 150, SHA3_384_150_bytes_digest),

    TEST_VECTOR_HASH(SHA3_512, SHA3_3_bytes_msg, 3, SHA3_512_3_bytes_digest),
    TEST_VECTOR_HASH(SHA3_512, SHA3_56_bytes_msg, 56, SHA3_512_56_bytes_digest),
    TEST_VECTOR_HASH(SHA3_512, SHA3_72_bytes_msg, 72, SHA3_512_72_bytes_digest),
    TEST_VECTOR_HASH(SHA3_512, SHA3_112_bytes_msg, 112, SHA3_512_112_bytes_digest),
    TEST_VECTOR_HASH(SHA3_512, SHA3_150_bytes_msg, 150, SHA3_512_150_bytes_digest),

    TEST_VECTOR_HASH(SM3, SM3_3_bytes_msg, 3, SM3_3_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_46_bytes_msg, 46, SM3_46_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_46_bytes_msg_2, 46, SM3_46_bytes_digest_2),
    TEST_VECTOR_HASH(SM3, SM3_64_bytes_msg, 64, SM3_64_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_65_bytes_msg, 65, SM3_65_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_65_bytes_msg_2, 65, SM3_65_bytes_digest_2),
    TEST_VECTOR_HASH(SM3, SM3_66_bytes_msg, 66, SM3_66_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_66_bytes_msg_2, 66, SM3_66_bytes_digest_2),
    TEST_VECTOR_HASH(SM3, SM3_67_bytes_msg, 67, SM3_67_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_69_bytes_msg, 69, SM3_69_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_83_bytes_msg, 83, SM3_83_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_85_bytes_msg, 85, SM3_85_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_211_bytes_msg, 211, SM3_211_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_212_bytes_msg, 212, SM3_212_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_212_bytes_msg_2, 212, SM3_212_bytes_digest_2),
    TEST_VECTOR_HASH(SM3, SM3_217_bytes_msg, 217, SM3_217_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_218_bytes_msg, 218, SM3_218_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_218_bytes_msg_2, 218, SM3_218_bytes_digest_2),
    TEST_VECTOR_HASH(SM3, SM3_224_bytes_msg, 224, SM3_224_bytes_digest),
    TEST_VECTOR_HASH(SM3, SM3_229_bytes_msg, 229, SM3_229_bytes_digest),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_hash_num(void)
{
    return sizeof(hash_test_vectors) / sizeof(hash_test_vectors[0]);
}

TestVector_HASH_t
test_vectors_hash_get(uint32_t Index)
{
    if (Index >= test_vectors_hash_num())
    {
        return NULL;
    }
    return &hash_test_vectors[Index];
}

#ifdef EIP130_ENABLE_SYM_ALGO_SM3
TestVector_HASH_t
test_vectors_first_sm3_get(void)
{
    uint32_t i;

    for (i = 0U; i < test_vectors_hash_num(); i++)
    {
        if (hash_test_vectors[i].Algorithm == TESTVECTORS_HASH_SM3)
        {
            return &hash_test_vectors[i];
        }
    }
    return NULL;
}
#endif /* EIP130_ENABLE_SYM_ALGO_SM3 */

void
test_vectors_hash_release(TestVector_HASH_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}


/* end of file testvectors_hash.c */
