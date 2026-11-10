/* testvectors_aria_ccm.c
 *
 * Description: Test vectors for ARIA CCM.
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

#ifdef EIP130_ENABLE_SYM_ALGO_ARIA_CCM

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_aria_ccm.h"
#include "testvectors_aria_ccm_data.h"

/* Use macro to build ccm_test_vectors. */
#define TEST_VECTOR_ARIA_CCM(key, nonce, aad, payload, ct)                 \
  {                                                                        \
      key, nonce, aad, payload, ct,                                        \
      sizeof(key), sizeof(nonce), sizeof(aad), sizeof(payload), sizeof(ct) \
  }

/* Actual test vectors. */
static const TestVector_ARIA_CCM_Rec_t ccm_test_vectors[] =
{
    TEST_VECTOR_ARIA_CCM(ARIA_CCM_128_1_K,ARIA_CCM_128_1_N, ARIA_CCM_128_1_A, ARIA_CCM_128_1_P, ARIA_CCM_128_1_C),
    TEST_VECTOR_ARIA_CCM(ARIA_CCM_128_2_K,ARIA_CCM_128_2_N, ARIA_CCM_128_2_A, ARIA_CCM_128_2_P, ARIA_CCM_128_2_C),
    TEST_VECTOR_ARIA_CCM(ARIA_CCM_192_1_K,ARIA_CCM_192_1_N, ARIA_CCM_192_1_A, ARIA_CCM_192_1_P, ARIA_CCM_192_1_C),
    TEST_VECTOR_ARIA_CCM(ARIA_CCM_192_2_K,ARIA_CCM_192_2_N, ARIA_CCM_192_2_A, ARIA_CCM_192_2_P, ARIA_CCM_192_2_C),
    TEST_VECTOR_ARIA_CCM(ARIA_CCM_256_1_K,ARIA_CCM_256_1_N, ARIA_CCM_256_1_A, ARIA_CCM_256_1_P, ARIA_CCM_256_1_C),
    TEST_VECTOR_ARIA_CCM(ARIA_CCM_256_2_K,ARIA_CCM_256_2_N, ARIA_CCM_256_2_A, ARIA_CCM_256_2_P, ARIA_CCM_256_2_C)
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_aria_ccm_num(void)
{
    return sizeof(ccm_test_vectors) / sizeof(ccm_test_vectors[0]);
}

TestVector_ARIA_CCM_t
test_vectors_aria_ccm_get(uint32_t Index)
{
    if (Index >= test_vectors_aria_ccm_num())
    {
        return NULL;
    }
    return &ccm_test_vectors[Index];
}

void
test_vectors_aria_ccm_release(TestVector_ARIA_CCM_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_ARIA_CCM */

/* end of file testvectors_aria_ccm.c */
