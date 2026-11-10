/* testvectors_aria_cbcmac.c
 *
 * Description: Test vectors for ARIA CBC-MAC.
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
#include "testvectors_aria_cbcmac.h"
#include "testvectors_aria_cbcmac_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_ARIA_CBCMAC(key, keylen, msg, msglen, mac, maclen) \
    {                                                      \
        test_vector_keys + (key),                          \
        test_vector_msgs + (msg),                          \
        test_vector_macs + (mac),                          \
        keylen,                                            \
        msglen,                                            \
        maclen,                                            \
    }

static const TestVector_ARIA_CBCMAC_Rec_t cbcmac_test_vectors[] =
{
    /* Miscellaneous ARIA CBC-MAC Test Vector #1 */
    TEST_VECTOR_ARIA_CBCMAC(0, 16, 0, 262, 0, 16),
    /* Miscellaneous ARIA CBC-MAC Test Vector #2 */
    TEST_VECTOR_ARIA_CBCMAC(0, 24, 0, 262, 16, 16),
    /* Miscellaneous ARIA CBC-MAC Test Vector #3 */
    TEST_VECTOR_ARIA_CBCMAC(0, 32, 0, 262, 32, 16),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_aria_cbcmac_num(void)
{
    return sizeof(cbcmac_test_vectors) / sizeof(cbcmac_test_vectors[0]);
}

TestVector_ARIA_CBCMAC_t
test_vectors_aria_cbcmac_get(uint32_t Index)
{
    if (Index >= test_vectors_aria_cbcmac_num())
    {
        return NULL;
    }
    return &cbcmac_test_vectors[Index];
}

void
test_vectors_aria_cbcmac_release(TestVector_ARIA_CBCMAC_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_ARIA */

/* end of file testvectors_aria_cbcmac.c */
