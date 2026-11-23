/* testvectors_ecdsa.c
 *
 * Description: Test vectors for ECDSA and SM2.
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

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_ecdsa.h"
#include "testvectors_ecdsa_data.h"

/* The function API for accessing the vectors. */

uint32_t
test_vectors_ecdsa_num(void)
{
    return sizeof(test_vectors_ecdsa) / sizeof(test_vectors_ecdsa[0]);
}

TestVector_ECDSA_t
test_vectors_ecdsa_get(uint32_t Index)
{
    if (Index >= test_vectors_ecdsa_num())
    {
        return NULL;
    }
    return &test_vectors_ecdsa[Index];
}

void
test_vectors_ecdsa_release(TestVector_ECDSA_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#ifdef EIP130_ENABLE_ASYM_ALGO_SM2
TestVector_SM2DSA_t
test_vectors_sm2dsa_get(uint32_t Index)
{
    uint32_t sm2dsa_num = sizeof(test_vectors_sm2dsa) /
                          sizeof(test_vectors_sm2dsa[0]);

    return (Index >= sm2dsa_num) ? NULL : &test_vectors_sm2dsa[Index];
}

void
test_vectors_sm2dsa_release(TestVector_SM2DSA_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}


TestVector_SM2KEX_t
test_vectors_sm2kex_get(uint32_t Index)
{
    uint32_t sm2kex_num = sizeof(test_vectors_sm2kex) /
                          sizeof(test_vectors_sm2kex[0]);

    return (Index >= sm2kex_num) ? NULL : &test_vectors_sm2kex[Index];
}

void
test_vectors_sm2kex_release(TestVector_SM2KEX_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}
#endif /* EIP130_ENABLE_ASYM_ALGO_SM2 */

/* end of file testvectors_ecdsa.c */
