/* testvectors_xts_aes_basic.c
 *
 * Description: Test vectors for AES in XTS mode.
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

#ifdef EIP130_ENABLE_SYM_ALGO_AES_XTS

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_xts_aes.h"
#include "testvectors_xts_aes_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_XTS_AES(key, ptx, ctx, tweak) \
    {                                             \
        key, ptx, ctx, tweak,                     \
        sizeof(key), sizeof(ptx)                  \
    }

static const TestVector_XTS_AES_Rec_t xts_aes_test_vectors [] =
{
    TEST_VECTOR_XTS_AES(V128_1_key, V128_1_ptx, V128_1_ctx, V128_1_tweak),
    TEST_VECTOR_XTS_AES(V128_2_key, V128_2_ptx, V128_2_ctx, V128_2_tweak),
    TEST_VECTOR_XTS_AES(V128_3_key, V128_3_ptx, V128_3_ctx, V128_3_tweak),
    TEST_VECTOR_XTS_AES(V256_1_key, V256_1_ptx, V256_1_ctx, V256_1_tweak),
    TEST_VECTOR_XTS_AES(V256_2_key, V256_2_ptx, V256_2_ctx, V256_2_tweak),
    TEST_VECTOR_XTS_AES(V256_3_key, V256_3_ptx, V256_3_ctx, V256_3_tweak),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_xts_aes_num(void)
{
    return sizeof(xts_aes_test_vectors) / sizeof(xts_aes_test_vectors[0]);
}

TestVector_XTS_AES_t
test_vectors_xts_aes_get(uint32_t Index)
{
    if (Index >= test_vectors_xts_aes_num())
    {
        return NULL;
    }
    return &xts_aes_test_vectors[Index];
}

void
test_vectors_xts_aes_release(TestVector_XTS_AES_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_AES_XTS */

/* end of file testvectors_xts_aes.c */
