/* testvectors_aria_basic.c
 *
 * Description: Test vectors for ARIA, for key sizes 128, 192 and 256 bits
 *              and ECB, CBC and CTR modes.
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

#ifdef EIP130_ENABLE_SYM_ALGO_ARIA

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_aria_basic.h"
#include "testvectors_aria_basic_data.h"


/* Macros used to build test_vectors. */
#define TEST_VECTOR_ARIA(mode, key, ptx, ctx, iv) \
    {                                            \
        TESTVECTORS_MODE_##mode,                 \
        key, ptx, ctx, iv,                       \
        sizeof(key), sizeof(ptx)                 \
    }


static const TestVector_ARIA_BASIC_Rec_t aria_basic_test_vectors [] =
{
    TEST_VECTOR_ARIA(ECB, ARIA_ECB_128_1_key, ARIA_ECB_128_1_pt, ARIA_ECB_128_1_ct, NULL),
    TEST_VECTOR_ARIA(ECB, ARIA_ECB_128_2_key, ARIA_ECB_128_2_pt, ARIA_ECB_128_2_ct, NULL),
    TEST_VECTOR_ARIA(ECB, ARIA_ECB_192_1_key, ARIA_ECB_192_1_pt, ARIA_ECB_192_1_ct, NULL),
    TEST_VECTOR_ARIA(ECB, ARIA_ECB_192_2_key, ARIA_ECB_192_2_pt, ARIA_ECB_192_2_ct, NULL),
    TEST_VECTOR_ARIA(ECB, ARIA_ECB_256_1_key, ARIA_ECB_256_1_pt, ARIA_ECB_256_1_ct, NULL),
    TEST_VECTOR_ARIA(ECB, ARIA_ECB_256_2_key, ARIA_ECB_256_2_pt, ARIA_ECB_256_2_ct, NULL),

    TEST_VECTOR_ARIA(CBC, ARIA_CBC_128_1_key, ARIA_CBC_128_1_pt, ARIA_CBC_128_1_ct, ARIA_CBC_128_1_iv),
    TEST_VECTOR_ARIA(CBC, ARIA_CBC_128_2_key, ARIA_CBC_128_2_pt, ARIA_CBC_128_2_ct, ARIA_CBC_128_2_iv),
    TEST_VECTOR_ARIA(CBC, ARIA_CBC_192_1_key, ARIA_CBC_192_1_pt, ARIA_CBC_192_1_ct, ARIA_CBC_192_1_iv),
    TEST_VECTOR_ARIA(CBC, ARIA_CBC_192_2_key, ARIA_CBC_192_2_pt, ARIA_CBC_192_2_ct, ARIA_CBC_192_2_iv),
    TEST_VECTOR_ARIA(CBC, ARIA_CBC_256_1_key, ARIA_CBC_256_1_pt, ARIA_CBC_256_1_ct, ARIA_CBC_256_1_iv),
    TEST_VECTOR_ARIA(CBC, ARIA_CBC_256_2_key, ARIA_CBC_256_2_pt, ARIA_CBC_256_2_ct, ARIA_CBC_256_2_iv),

    TEST_VECTOR_ARIA(CTR, ARIA_CTR_128_1_key, ARIA_CTR_128_1_pt, ARIA_CTR_128_1_ct, ARIA_CTR_128_1_iv),
    TEST_VECTOR_ARIA(CTR, ARIA_CTR_128_2_key, ARIA_CTR_128_2_pt, ARIA_CTR_128_2_ct, ARIA_CTR_128_2_iv),
    TEST_VECTOR_ARIA(CTR, ARIA_CTR_192_1_key, ARIA_CTR_192_1_pt, ARIA_CTR_192_1_ct, ARIA_CTR_192_1_iv),
    TEST_VECTOR_ARIA(CTR, ARIA_CTR_192_2_key, ARIA_CTR_192_2_pt, ARIA_CTR_192_2_ct, ARIA_CTR_192_2_iv),
    TEST_VECTOR_ARIA(CTR, ARIA_CTR_256_1_key, ARIA_CTR_256_1_pt, ARIA_CTR_256_1_ct, ARIA_CTR_256_1_iv),
    TEST_VECTOR_ARIA(CTR, ARIA_CTR_256_2_key, ARIA_CTR_256_2_pt, ARIA_CTR_256_2_ct, ARIA_CTR_256_2_iv),

    TEST_VECTOR_ARIA(ICM, ARIA_ICM_128_1_key, ARIA_ICM_128_1_pt, ARIA_ICM_128_1_ct, ARIA_ICM_128_1_iv),
    TEST_VECTOR_ARIA(ICM, ARIA_ICM_192_1_key, ARIA_ICM_192_1_pt, ARIA_ICM_192_1_ct, ARIA_ICM_192_1_iv),
    TEST_VECTOR_ARIA(ICM, ARIA_ICM_256_1_key, ARIA_ICM_256_1_pt, ARIA_ICM_256_1_ct, ARIA_ICM_256_1_iv),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_aria_basic_num(void)
{
    return sizeof(aria_basic_test_vectors) / sizeof(aria_basic_test_vectors[0]);
}

TestVector_ARIA_BASIC_t
test_vectors_aria_basic_get(uint32_t Index)
{
    if (Index >= test_vectors_aria_basic_num())
    {
        return NULL;
    }
    return &aria_basic_test_vectors[Index];
}

void
test_vectors_aria_basic_release(TestVector_ARIA_BASIC_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_ARIA */

/* end of file testvectors_aria_basic.c */
