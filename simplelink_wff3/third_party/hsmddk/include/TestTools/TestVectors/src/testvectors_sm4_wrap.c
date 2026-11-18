/* testvectors_sm4_wrap.c
 *
 * Description: Test vectors for SM4-WRAP.
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

#ifdef EIP130_ENABLE_SYM_ALGO_SM4

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_sm4_wrap.h"
#include "testvectors_sm4_wrap_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_SM4_WRAP_KW(key, ptx, ctx)  \
    {                                           \
        key, ptx, ctx,                          \
        sizeof(key), sizeof(ptx), sizeof(ctx),  \
        false                                   \
    }
#define TEST_VECTOR_SM4_WRAP_KWP(key, ptx, ctx) \
    {                                           \
        key, ptx, ctx,                          \
        sizeof(key), sizeof(ptx), sizeof(ctx),  \
        true                                    \
    }

static const TestVector_SM4_WRAP_Rec_t sm4_wrap_test_vectors [] =
{
    TEST_VECTOR_SM4_WRAP_KW(TC1_key, TC1_ptx, TC1_ctx),
    TEST_VECTOR_SM4_WRAP_KW(TC2_key, TC2_ptx, TC2_ctx),
    TEST_VECTOR_SM4_WRAP_KW(TC3_key, TC3_ptx, TC3_ctx),
    TEST_VECTOR_SM4_WRAP_KWP(TC4_key, TC4_ptx, TC4_ctx),
    TEST_VECTOR_SM4_WRAP_KWP(TC5_key, TC5_ptx, TC5_ctx),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_sm4_wrap_num(void)
{
    return sizeof(sm4_wrap_test_vectors) / sizeof(sm4_wrap_test_vectors[0]);
}

TestVector_SM4_WRAP_t
test_vectors_sm4_wrap_get(uint32_t Index)
{
    if (Index >= test_vectors_sm4_wrap_num())
    {
        return NULL;
    }
    return &sm4_wrap_test_vectors[Index];
}

void
test_vectors_sm4_wrap_release(TestVector_SM4_WRAP_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_SM4 */

/* end of file testvectors_sm4_wrap.c */
