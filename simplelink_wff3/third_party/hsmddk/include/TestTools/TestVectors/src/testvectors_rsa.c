/* testvectors_rsa.c
 *
 * Description: Test vectors for RSA algorithm.
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

#ifdef EIP130_ENABLE_ASYM_ALGO_RSA

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_rsa.h"
#include "testvectors_rsa_data.h"


/* The function API for accessing the vectors. */
uint32_t
test_vectors_rsa_pkcs1v15_num(void)
{
    return (sizeof(test_vectors_rsa_pkcs1v15) /
            sizeof(test_vectors_rsa_pkcs1v15[0]));
}

TestVector_RSA_PKCS1v15_t
test_vectors_rsa_pkcs1v15_get(uint32_t Index)
{
    if (Index >= test_vectors_rsa_pkcs1v15_num())
    {
        return NULL;
    }
    return &test_vectors_rsa_pkcs1v15[Index];
}

void
test_vectors_rsa_pkcs1v15_release(TestVector_RSA_PKCS1v15_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}


uint32_t
test_vectors_rsa_pss_num(void)
{
    return (sizeof(test_vectors_rsa_pss) / sizeof(test_vectors_rsa_pss[0]));
}

TestVector_RSA_PSS_t
test_vectors_rsa_pss_get(uint32_t Index)
{
    if (Index >= test_vectors_rsa_pss_num())
    {
        return NULL;
    }
    return &test_vectors_rsa_pss[Index];
}

void
test_vectors_rsa_pss_release(TestVector_RSA_PSS_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}


uint32_t
test_vectors_rsa_oaep_num(void)
{
    return (sizeof(test_vectors_rsa_oaep) / sizeof(test_vectors_rsa_oaep[0]));
}

TestVector_RSA_OAEP_t
test_vectors_rsa_oaep_get(uint32_t Index)
{
    if (Index >= test_vectors_rsa_oaep_num())
    {
        return NULL;
    }
    return &test_vectors_rsa_oaep[Index];
}

void
test_vectors_rsa_oaep_release(TestVector_RSA_OAEP_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}


uint32_t
test_vectors_rsa_pkcs1v15wrap_num(void)
{
    return (sizeof(test_vectors_rsa_pkcs1v15wrap) /
            sizeof(test_vectors_rsa_pkcs1v15wrap[0]));
}

TestVector_PKCS1V15WRAP_t
test_vectors_rsa_pkcs1v15wrap_get(uint32_t Index)
{
    if (Index >= test_vectors_rsa_pkcs1v15wrap_num())
    {
        return NULL;
    }
    return &test_vectors_rsa_pkcs1v15wrap[Index];
}

void
test_vectors_rsa_pkcs1v15wrap_release(TestVector_PKCS1V15WRAP_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_ASYM_ALGO_RSA */

/* end of file testvectors_rsa.c */
