/* testvectors_aes_gcm.c
 *
 * Description: Test vectors for AES GCM.
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

#ifdef EIP130_ENABLE_SYM_ALGO_AES_GCM

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_aes_gcm.h"
#include "testvectors_aes_gcm_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_AES_GCM(key, pt, ct, aad, iv, h, y0, ghash, tag) \
  {                                                                  \
      key, pt, ct, aad, iv, h, y0, ghash, tag,                       \
      sizeof(key), sizeof(pt), sizeof(ct), sizeof(aad), sizeof(iv),  \
      sizeof(h), sizeof(y0), sizeof(ghash), sizeof(tag),             \
  }

/* Actual test vectors. */
static const TestVector_AES_GCM_Rec_t gcm_test_vectors[] =
{
    TEST_VECTOR_AES_GCM(AESGCM_128_tv0_Key, AESGCM_128_tv0_P, AESGCM_128_tv0_C, AESGCM_128_tv0_A, AESGCM_128_tv0_IV, AESGCM_128_tv0_H, AESGCM_128_tv0_Y0, AESGCM_128_tv0_GHASH, AESGCM_128_tv0_T),
    TEST_VECTOR_AES_GCM(AESGCM_128_tv1_Key, AESGCM_128_tv1_P, AESGCM_128_tv1_C, AESGCM_128_tv1_A, AESGCM_128_tv1_IV, AESGCM_128_tv1_H, AESGCM_128_tv1_Y0, AESGCM_128_tv1_GHASH, AESGCM_128_tv1_T),
    TEST_VECTOR_AES_GCM(AESGCM_128_tv2_Key, AESGCM_128_tv2_P, AESGCM_128_tv2_C, AESGCM_128_tv2_A, AESGCM_128_tv2_IV, AESGCM_128_tv2_H, AESGCM_128_tv2_Y0, AESGCM_128_tv2_GHASH, AESGCM_128_tv2_T),
    TEST_VECTOR_AES_GCM(AESGCM_128_tv3_Key, AESGCM_128_tv3_P, AESGCM_128_tv3_C, AESGCM_128_tv3_A, AESGCM_128_tv3_IV, AESGCM_128_tv3_H, AESGCM_128_tv3_Y0, AESGCM_128_tv3_GHASH, AESGCM_128_tv3_T),
    TEST_VECTOR_AES_GCM(AESGCM_128_tv4_Key, AESGCM_128_tv4_P, AESGCM_128_tv4_C, AESGCM_128_tv4_A, AESGCM_128_tv4_IV, AESGCM_128_tv4_H, AESGCM_128_tv4_Y0, AESGCM_128_tv4_GHASH, AESGCM_128_tv4_T),
    TEST_VECTOR_AES_GCM(AESGCM_192_tv0_Key, AESGCM_192_tv0_P, AESGCM_192_tv0_C, AESGCM_192_tv0_A, AESGCM_192_tv0_IV, AESGCM_192_tv0_H, AESGCM_192_tv0_Y0, AESGCM_192_tv0_GHASH, AESGCM_192_tv0_T),
    TEST_VECTOR_AES_GCM(AESGCM_192_tv1_Key, AESGCM_192_tv1_P, AESGCM_192_tv1_C, AESGCM_192_tv1_A, AESGCM_192_tv1_IV, AESGCM_192_tv1_H, AESGCM_192_tv1_Y0, AESGCM_192_tv1_GHASH, AESGCM_192_tv1_T),
    TEST_VECTOR_AES_GCM(AESGCM_192_tv2_Key, AESGCM_192_tv2_P, AESGCM_192_tv2_C, AESGCM_192_tv2_A, AESGCM_192_tv2_IV, AESGCM_192_tv2_H, AESGCM_192_tv2_Y0, AESGCM_192_tv2_GHASH, AESGCM_192_tv2_T),
    TEST_VECTOR_AES_GCM(AESGCM_192_tv3_Key, AESGCM_192_tv3_P, AESGCM_192_tv3_C, AESGCM_192_tv3_A, AESGCM_192_tv3_IV, AESGCM_192_tv3_H, AESGCM_192_tv3_Y0, AESGCM_192_tv3_GHASH, AESGCM_192_tv3_T),
    TEST_VECTOR_AES_GCM(AESGCM_192_tv4_Key, AESGCM_192_tv4_P, AESGCM_192_tv4_C, AESGCM_192_tv4_A, AESGCM_192_tv4_IV, AESGCM_192_tv4_H, AESGCM_192_tv4_Y0, AESGCM_192_tv4_GHASH, AESGCM_192_tv4_T),
    TEST_VECTOR_AES_GCM(AESGCM_256_tv0_Key, AESGCM_256_tv0_P, AESGCM_256_tv0_C, AESGCM_256_tv0_A, AESGCM_256_tv0_IV, AESGCM_256_tv0_H, AESGCM_256_tv0_Y0, AESGCM_256_tv0_GHASH, AESGCM_256_tv0_T),
    TEST_VECTOR_AES_GCM(AESGCM_256_tv1_Key, AESGCM_256_tv1_P, AESGCM_256_tv1_C, AESGCM_256_tv1_A, AESGCM_256_tv1_IV, AESGCM_256_tv1_H, AESGCM_256_tv1_Y0, AESGCM_256_tv1_GHASH, AESGCM_256_tv1_T),
    TEST_VECTOR_AES_GCM(AESGCM_256_tv2_Key, AESGCM_256_tv2_P, AESGCM_256_tv2_C, AESGCM_256_tv2_A, AESGCM_256_tv2_IV, AESGCM_256_tv2_H, AESGCM_256_tv2_Y0, AESGCM_256_tv2_GHASH, AESGCM_256_tv2_T),
    TEST_VECTOR_AES_GCM(AESGCM_256_tv3_Key, AESGCM_256_tv3_P, AESGCM_256_tv3_C, AESGCM_256_tv3_A, AESGCM_256_tv3_IV, AESGCM_256_tv3_H, AESGCM_256_tv3_Y0, AESGCM_256_tv3_GHASH, AESGCM_256_tv3_T),
    TEST_VECTOR_AES_GCM(AESGCM_256_tv4_Key, AESGCM_256_tv4_P, AESGCM_256_tv4_C, AESGCM_256_tv4_A, AESGCM_256_tv4_IV, AESGCM_256_tv4_H, AESGCM_256_tv4_Y0, AESGCM_256_tv4_GHASH, AESGCM_256_tv4_T),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_aes_gcm_num(void)
{
    return sizeof(gcm_test_vectors) / sizeof(gcm_test_vectors[0]);
}

TestVector_AES_GCM_t
test_vectors_aes_gcm_get(uint32_t Index)
{
    if (Index >= test_vectors_aes_gcm_num())
    {
         return NULL;
    }
    return &gcm_test_vectors[Index];
}

void
test_vectors_aes_gcm_release(TestVector_AES_GCM_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_AES_GCM */

/* end of file testvectors_aes_gcm.c */
