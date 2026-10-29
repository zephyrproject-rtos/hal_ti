/* testvectors_asn1_der.c
 *
 * Description: Test vectors for ASN1 DER objects.
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

#ifdef TESTVECTORS_ASN1_DER

#include <third_party/hsmddk/include/Config/cs_eip130.h>

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_asn1_der.h"
#include "testvectors_asn1_der_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_ASN1_DER(fPrivateKey, KeyType, Method, ModulusSize, key)  { fPrivateKey, KeyType, Method, ModulusSize, key, sizeof(key) }

static const TestVector_ASN1_DER_Rec_t ASN1_DER_TestVectors[] =
{
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 224U, Asn1Der_ECC_N224_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 224U, Asn1Der_ECC_N224_PubKey),
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 256U, Asn1Der_ECC_N256_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 256U, Asn1Der_ECC_N256_PubKey),
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 384U, Asn1Der_ECC_N384_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 384U, Asn1Der_ECC_N384_PubKey),
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 521U, Asn1Der_ECC_N521_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 521U, Asn1Der_ECC_N521_PubKey),
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 224U, Asn1Der_ECC_B224_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 224U, Asn1Der_ECC_B224_PubKey),
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 256U, Asn1Der_ECC_B256_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 256U, Asn1Der_ECC_B256_PubKey),
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 384U, Asn1Der_ECC_B384_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 384U, Asn1Der_ECC_B384_PubKey),
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 512U, Asn1Der_ECC_B512_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 512U, Asn1Der_ECC_B512_PubKey),

    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECDH_KEY_TYPE, TV_ASN1DER_NIST_METHOD, 256U, Asn1Der_ECC_N256_PubKey_ECDH),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECDH_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD, 256U, Asn1Der_ECC_B256_PubKey_ECDH),

#ifdef EIP130_ENABLE_ASYM_ALGO_CURVE25519
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_MONT_METHOD, 255U, Asn1Der_X25519_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_MONT_METHOD, 255U, Asn1Der_X25519_PubKey),
#endif
#ifdef EIP130_ENABLE_ASYM_ALGO_EDDSA
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_TEDWARDS_METHOD, 255U, Asn1Der_Ed25519_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_TEDWARDS_METHOD, 255U, Asn1Der_Ed25519_PubKey),
#endif
#ifdef EIP130_ENABLE_ASYM_ALGO_RSA
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_RSA_KEY_TYPE, TV_ASN1DER_PKCS1_METHOD, 2048U, Asn1Der_RSASSA_PKCS1v15_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_RSA_KEY_TYPE, TV_ASN1DER_PKCS1_METHOD, 2048U, Asn1Der_RSASSA_PKCS1v15_PubKey),
    TEST_VECTOR_ASN1_DER(true, TV_ASN1DER_RSA_KEY_TYPE, TV_ASN1DER_PSS_METHOD, 2048U, Asn1Der_RSASSA_PSS_PrvKey),
    TEST_VECTOR_ASN1_DER(false, TV_ASN1DER_RSA_KEY_TYPE, TV_ASN1DER_PSS_METHOD, 2048U, Asn1Der_RSASSA_PSS_PubKey),
#endif
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_asn1_der_num(void)
{
    return sizeof(ASN1_DER_TestVectors) / sizeof(ASN1_DER_TestVectors[0]);
}

TestVector_ASN1_DER_t
test_vectors_asn1_der_get(uint32_t Index)
{
    if (Index >= test_vectors_asn1_der_num())
    {
        return NULL;
    }
    return &ASN1_DER_TestVectors[Index];
}

void
test_vectors_asn1_der_release(TestVector_ASN1_DER_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* TESTVECTORS_ASN1_DER */

/* end of file testvectors_asn1_der.c */
