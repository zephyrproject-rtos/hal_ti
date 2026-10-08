/* testvectors_des.c
 *
 * Description: Test vectors for DES in modes ECB and CBC
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

#if defined(EIP130_ENABLE_SYM_ALGO_DES) && \
    defined(EIP130_ENABLE_SYM_ALGO_3DES)

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_des.h"
#include "testvectors_des_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_DES(key, ptx, ctx, mode, iv) \
    {                                            \
        TESTVECTORS_MODE_##mode,                 \
        key, ptx, ctx, iv,                       \
        sizeof(key), sizeof(ptx)                 \
    }

static const TestVector_AES_BASIC_Rec_t des_test_vectors [] =
{
    TEST_VECTOR_DES(App_A_key, App_A_ptx, App_A_ctx, ECB, NULL),
    TEST_VECTOR_DES(IP_and_E_Test_key, IP_and_E_Test_ptx, IP_and_E_Test_ctx, ECB, NULL),
    TEST_VECTOR_DES(FIPS81_B1_key, FIPS81_B1_ptx, FIPS81_B1_ctx, ECB, NULL),
    TEST_VECTOR_DES(FIPS81_C1_key, FIPS81_C1_ptx, FIPS81_C1_ctx, CBC, FIPS81_C1_iv),
    TEST_VECTOR_DES(B_1_3DES_ECB_key, B_1_3DES_ECB_ptx, B_1_3DES_ECB_ctx, ECB, NULL),
    TEST_VECTOR_DES(TDES_ECB_Ex1_key, TDES_ECB_Ex1_ptx, TDES_ECB_Ex1_ctx, ECB, NULL),
    TEST_VECTOR_DES(TDES_ECB_Ex2_key, TDES_ECB_Ex2_ptx, TDES_ECB_Ex2_ctx, ECB, NULL),
    TEST_VECTOR_DES(TDES_CBC_Ex1_key, TDES_CBC_Ex1_ptx, TDES_CBC_Ex1_ctx, CBC, TDES_CBC_Ex1_iv),
    TEST_VECTOR_DES(TDES_CBC_Ex2_key, TDES_CBC_Ex2_ptx, TDES_CBC_Ex2_ctx, CBC, TDES_CBC_Ex2_iv)
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_des_num(void)
{
    return sizeof(des_test_vectors) / sizeof(des_test_vectors[0]);
}

TestVector_DES_t
test_vectors_des_get(uint32_t Index)
{
    if (Index >= test_vectors_des_num())
    {
        return NULL;
    }
    return &des_test_vectors[Index];
}

void
test_vectors_des_release(TestVector_DES_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_DES && EIP130_ENABLE_SYM_ALGO_3DES */

/* end of file testvectors_des.c */
