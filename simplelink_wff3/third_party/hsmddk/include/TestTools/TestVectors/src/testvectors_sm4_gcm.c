/* testvectors_sm4_gcm.c
 *
 * Description: Test vectors for SM4-GCM.
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

#ifdef EIP130_ENABLE_SYM_ALGO_SM4_GCM

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_sm4_gcm.h"
#include "testvectors_sm4_gcm_data.h"

/* Use macro to build gcm_test_vectors. */
#define TEST_VECTOR_SM4_GCM(key, pt, ct, aad, iv, h, y0, ghash, tag) \
  {                                                                  \
      key, pt, ct, aad, iv, h, y0, ghash, tag,                       \
      sizeof(key), sizeof(pt), sizeof(ct), sizeof(aad), sizeof(iv),  \
      sizeof(h), sizeof(y0), sizeof(ghash), sizeof(tag),             \
  }

/* Actual test vectors. */
static const TestVector_SM4_GCM_Rec_t gcm_test_vectors[] =
{
    TEST_VECTOR_SM4_GCM(SM4_GCM_128_1_K, SM4_GCM_128_1_P, SM4_GCM_128_1_C, SM4_GCM_128_1_A, SM4_GCM_128_1_IV, SM4_GCM_H_nu, SM4_GCM_Y0_nu, SM4_GCM_GH_nu, SM4_GCM_128_1_T),
    TEST_VECTOR_SM4_GCM(SM4_GCM_128_2_K, SM4_GCM_128_2_P, SM4_GCM_128_2_C, SM4_GCM_128_2_A, SM4_GCM_128_2_IV, SM4_GCM_H_nu, SM4_GCM_Y0_nu, SM4_GCM_GH_nu, SM4_GCM_128_2_T),
    TEST_VECTOR_SM4_GCM(SM4_GCM_128_3_K, SM4_GCM_128_3_P, SM4_GCM_128_3_C, SM4_GCM_128_3_A, SM4_GCM_128_3_IV, SM4_GCM_H_nu, SM4_GCM_Y0_nu, SM4_GCM_GH_nu, SM4_GCM_128_3_T),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_sm4_gcm_num(void)
{
    return sizeof(gcm_test_vectors) / sizeof(gcm_test_vectors[0]);
}

TestVector_SM4_GCM_t
test_vectors_sm4_gcm_get(uint32_t Index)
{
    if (Index >= test_vectors_sm4_gcm_num())
    {
        return NULL;
    }
    return &gcm_test_vectors[Index];
}

void
test_vectors_sm4_gcm_release(TestVector_SM4_GCM_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_SM4_GCM */

/* end of file testvectors_sm4_gcm.c */
