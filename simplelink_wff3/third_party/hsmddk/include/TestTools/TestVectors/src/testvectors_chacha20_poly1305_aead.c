/* testvectors_chacha20_poly1305_aead.c
 *
 * Description: Test vectors for ChaCha20-Poly1305-AEAD.
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

#if defined(EIP130_ENABLE_SYM_ALGO_CHACHA20) && \
    defined(EIP130_ENABLE_SYM_ALGO_POLY1305)

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_chacha20_poly1305_aead.h"
#include "testvectors_chacha20_poly1305_aead_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_CHACHA20_POLY1305(key, aad, nonce, ptx, ctx, tag)   \
    {                                                                   \
        key, aad, nonce, ptx, ctx, tag,                                 \
        sizeof(key), sizeof(aad), sizeof(nonce), sizeof(ptx)            \
    }

static const TestVector_ChaCha20_Poly1305_Rec_t chacha20_poly1305_test_vectors [] =
{
    TEST_VECTOR_CHACHA20_POLY1305(
            ChaCha20_Poly1305_TV1_Key,
            ChaCha20_Poly1305_TV1_AAD,
            ChaCha20_Poly1305_TV1_Nonce,
            ChaCha20_Poly1305_TV1_PlainData,
            ChaCha20_Poly1305_TV1_CipherData,
            ChaCha20_Poly1305_TV1_Tag),

    TEST_VECTOR_CHACHA20_POLY1305(
            ChaCha20_Poly1305_TV2_Key,
            ChaCha20_Poly1305_TV2_AAD,
            ChaCha20_Poly1305_TV2_Nonce,
            ChaCha20_Poly1305_TV2_PlainData,
            ChaCha20_Poly1305_TV2_CipherData,
            ChaCha20_Poly1305_TV2_Tag),
};

/* The function API for accessing the vectors. */
uint32_t
test_vectors_chacha20_poly1305_num(void)
{
    return sizeof(chacha20_poly1305_test_vectors) / sizeof(chacha20_poly1305_test_vectors[0]);
}

TestVector_ChaCha20_Poly1305_t
test_vectors_chacha20_poly1305_get(uint32_t Index)
{
    if (Index >= test_vectors_chacha20_poly1305_num())
    {
        return NULL;
    }
    return &chacha20_poly1305_test_vectors[Index];
}

void
test_vectors_chacha20_poly1305_release(TestVector_ChaCha20_Poly1305_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_CHACHA20 && EIP130_ENABLE_SYM_ALGO_POLY1305 */

/* end of file testvectors_chacha20_poly1305_aead.c */