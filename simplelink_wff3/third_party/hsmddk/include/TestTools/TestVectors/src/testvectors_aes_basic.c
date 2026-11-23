/* testvectors_aes_basic.c
 *
 * Description: Test vectors for AES, for key sizes 128, 192 and 256 bits
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

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

#include "testvectors_aes_basic.h"
#include "testvectors_aes_basic_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_AES(mode, key, ptx, ctx, iv) \
    {                                            \
        TESTVECTORS_MODE_##mode,                 \
        key, ptx, ctx, iv,                       \
        sizeof(key), sizeof(ptx)                 \
    }

static const TestVector_AES_BASIC_Rec_t aes_basic_test_vectors [] =
{
    TEST_VECTOR_AES(ECB, F_1_1_key, F_1_1_ptx, F_1_1_ctx, NULL),
    TEST_VECTOR_AES(ECB, F_1_3_key, F_1_3_ptx, F_1_3_ctx, NULL),
    TEST_VECTOR_AES(ECB, F_1_5_key, F_1_5_ptx, F_1_5_ctx, NULL),
    TEST_VECTOR_AES(CBC, F_2_1_key, F_2_1_ptx, F_2_1_ctx, F_2_1_iv),
    TEST_VECTOR_AES(CBC, F_2_3_key, F_2_3_ptx, F_2_3_ctx, F_2_3_iv),
    TEST_VECTOR_AES(CBC, F_2_5_key, F_2_5_ptx, F_2_5_ctx, F_2_5_iv),
    TEST_VECTOR_AES(CTR, F_5_1_key, F_5_1_ptx, F_5_1_ctx, F_5_1_iv),
    TEST_VECTOR_AES(CTR, F_5_3_key, F_5_3_ptx, F_5_3_ctx, F_5_3_iv),
    TEST_VECTOR_AES(CTR, F_5_5_key, F_5_5_ptx, F_5_5_ctx, F_5_5_iv),
    TEST_VECTOR_AES(ICM, F_4_1_key, F_4_1_ptx, F_4_1_ctx, F_4_1_iv),
    TEST_VECTOR_AES(ICM, F_4_2_key, F_4_2_ptx, F_4_2_ctx, F_4_2_iv)
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_aes_basic_num(void)
{
    return sizeof(aes_basic_test_vectors) / sizeof(aes_basic_test_vectors[0]);
}

TestVector_AES_BASIC_t
test_vectors_aes_basic_get(uint32_t Index)
{
    if (Index >= test_vectors_aes_basic_num())
    {
        return NULL;
    }
    return &aes_basic_test_vectors[Index];
}

void
test_vectors_aes_basic_release(TestVector_AES_BASIC_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}


/* end of file testvectors_aes_basic.c */
