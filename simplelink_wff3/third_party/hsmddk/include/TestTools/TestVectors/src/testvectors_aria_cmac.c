/* testvectors_aria_cmac.c
 *
 * Description: Test vectors for ARIA CMAC.
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
#include "testvectors_aria_cmac.h"
#include "testvectors_aria_cmac_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_ARIA_CMAC(key, keylen, msg, msglen, mac, maclen) \
    {                                                      \
        test_vector_keys + (key),                          \
        test_vector_msgs + (msg),                          \
        test_vector_macs + (mac),                          \
        keylen,                                            \
        msglen,                                            \
        maclen,                                            \
    }

/* Actual test vectors. */
static const TestVector_ARIA_CMAC_Rec_t cmac_test_vectors[] =
{
    /* CMACGenARIA128 COUNT =0 */
    TEST_VECTOR_ARIA_CMAC(0,   16,    0,   0,   0,  8),
    /* CMACGenARIA128 COUNT =5 */
    TEST_VECTOR_ARIA_CMAC(16,  16,    0,   6,   8,  8),
    /* CMACGenARIA128 COUNT =10 */
    TEST_VECTOR_ARIA_CMAC(32,  16,    6,  18,  16, 10),
    /* CMACGenARIA128 COUNT =15 */
    TEST_VECTOR_ARIA_CMAC(48,  16,   24, 185,  26, 10),
    /* CMACGenARIA192 COUNT =20 */
    TEST_VECTOR_ARIA_CMAC(64,  24,  209,   0,  36, 11),
    /* CMACGenARIA192 COUNT =25 */
    TEST_VECTOR_ARIA_CMAC(88,  24,  209,  28,  47, 11),
    /* CMACGenARIA192 COUNT =30 */
    TEST_VECTOR_ARIA_CMAC(112, 24,  237,  52,  58, 12),
    /* CMACGenARIA192 COUNT =40 */
    TEST_VECTOR_ARIA_CMAC(136, 24,  289, 190,  70, 13),
    /* CMACGenARIA256 COUNT =47 */
    TEST_VECTOR_ARIA_CMAC(160, 32,  479,   0,  83, 13),
    /* CMACGenARIA256 COUNT =50 */
    TEST_VECTOR_ARIA_CMAC(192, 32,  479,  46,  96, 14),
    /* CMACGenARIA256 COUNT =56 */
    TEST_VECTOR_ARIA_CMAC(224, 32,  525,  88, 110, 14),
    /* CMACGenARIA256 COUNT =65 */
    TEST_VECTOR_ARIA_CMAC(256, 32,  613, 162, 124, 15),
    /* CMACGenARIA128 COUNT =70 */
    TEST_VECTOR_ARIA_CMAC(288, 16,  775,   0, 139, 16),
    /* CMACGenARIA128 COUNT =75 */
    TEST_VECTOR_ARIA_CMAC(304, 16,  775, 112, 155, 16),
    /* CMACGenARIA128 COUNT =80 */
    TEST_VECTOR_ARIA_CMAC(320, 16,  887,  66, 171, 16),
    /* CMACGenARIA192 COUNT =70 */
    TEST_VECTOR_ARIA_CMAC(336, 24,  953,   0, 187, 16),
    /* CMACGenARIA192 COUNT =75 */
    TEST_VECTOR_ARIA_CMAC(360, 24,  953, 112, 203, 16),
    /* CMACGenARIA192 COUNT =80 */
    TEST_VECTOR_ARIA_CMAC(384, 24, 1065,  66, 219, 16),
    /* CMACGenARIA256 COUNT =70 */
    TEST_VECTOR_ARIA_CMAC(408, 32, 1131,   0, 235, 16),
    /* CMACGenARIA256 COUNT =75 */
    TEST_VECTOR_ARIA_CMAC(440, 32, 1131, 112, 251, 16),
    /* CMACGenARIA256 COUNT =80 */
    TEST_VECTOR_ARIA_CMAC(472, 32, 1243,  66, 267, 16),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_aria_cmac_num(void)
{
    return sizeof(cmac_test_vectors) / sizeof(cmac_test_vectors[0]);
}

TestVector_ARIA_CMAC_t
test_vectors_aria_cmac_get(uint32_t Index)
{
    if (Index >= test_vectors_aria_cmac_num())
    {
         return NULL;
    }
    return &cmac_test_vectors[Index];
}

void
test_vectors_aria_cmac_release(TestVector_ARIA_CMAC_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SYM_ALGO_ARIA */

/* end of file testvectors_aria_cmac.c */
