/* testvectors_ecdsa.h
 *
 * Description: Test vectors for ECDSA.
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

#ifndef INCLUDE_GUARD_TESTVECTORS_ECDSA_H
#define INCLUDE_GUARD_TESTVECTORS_ECDSA_H

#include <third_party/hsmddk/include/Config/cs_eip130.h>

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_ecc_curves.h"

/* Structures for Test Vectors. */
typedef struct
{
    const TestVector_ECC_Curve_Rec_t * Curve_p;
    const uint8_t * PrivateKey_p;
    uint32_t PrivateKeyLen;
    const uint8_t * PublicKeyX_p;
    uint32_t PublicKeyXLen;
    const uint8_t * PublicKeyY_p;
    uint32_t PublicKeyYLen;
    const uint8_t * Message_p;
    uint32_t MessageLen;
    uint32_t HashBits;
    const uint8_t * SignatureR_p;
    uint32_t SignatureRLen;
    const uint8_t * SignatureS_p;
    uint32_t SignatureSLen;
} TestVector_ECDSA_Rec_t;

typedef const TestVector_ECDSA_Rec_t * TestVector_ECDSA_t;

#ifdef EIP130_ENABLE_ASYM_ALGO_SM2
/* For SM2 we can reuse same data structure from ECDSA with one
   additional field, UserIdentity */
typedef struct
{
    const TestVector_ECC_Curve_Rec_t * Curve_p;
    const uint8_t * UserIdentity_p;
    uint32_t UserIdentityLen;
    const uint8_t * PrivateKey_p;
    uint32_t PrivateKeyLen;
    const uint8_t * PublicKeyX_p;
    uint32_t PublicKeyXLen;
    const uint8_t * PublicKeyY_p;
    uint32_t PublicKeyYLen;
    const uint8_t * Message_p;
    uint32_t MessageLen;
    uint32_t HashBits;
    const uint8_t * SignatureR_p;
    uint32_t SignatureRLen;
    const uint8_t * SignatureS_p;
    uint32_t SignatureSLen;
} TestVector_SM2DSA_Rec_t;

typedef const TestVector_SM2DSA_Rec_t * TestVector_SM2DSA_t;

struct TestVector_SM2KEX_KeyPair
{
    const uint8_t * PrivateKey_p;
    const uint8_t * PublicKeyX_p;
    const uint8_t * PublicKeyY_p;
};

struct TestVector_SM2KEX_Peer
{
    const uint8_t * UserIdentity_p;
    uint32_t UserIdentityLen;
    const struct TestVector_SM2KEX_KeyPair StaticKeyPair;
    const uint8_t * ZA;
    const struct TestVector_SM2KEX_KeyPair EphemeralKeyPair;
};

struct TestVector_SM2KEX_Rec
{
    const TestVector_ECC_Curve_Rec_t * Curve_p;
    struct TestVector_SM2KEX_Peer Peers[2];
    const uint8_t * Vx;
    const uint8_t * Vy;
    const uint8_t * KB;
};
typedef const struct TestVector_SM2KEX_Rec * TestVector_SM2KEX_t;
#endif

/* API for using ECDSA test vectors. */

/* Request number of ECDSA test vectors available. */
uint32_t
test_vectors_ecdsa_num(void);

/* Request test vector by index.
   If Index >= test_vectors_ecdsa_num(), the function returns NULL.

   Note: The function returns zero only when invalid vector has been requested.
   Note: The received vector is constant and must not be altered by caller.
   The test vector is described by structure TestVector_ECDSA_t and
   the structure shall be accessed directly by the user of the test vector.
*/
TestVector_ECDSA_t
test_vectors_ecdsa_get(uint32_t Index);
#ifdef EIP130_ENABLE_ASYM_ALGO_SM2
TestVector_SM2DSA_t
test_vectors_sm2dsa_get(uint32_t Index);
TestVector_SM2KEX_t
test_vectors_sm2kex_get(uint32_t Index);
#endif

/* Release a vector.
   It is mandatory to release a vector once user of test vector is finished
   with the vector. */
void
test_vectors_ecdsa_release(TestVector_ECDSA_t Vector_p);
#ifdef EIP130_ENABLE_ASYM_ALGO_SM2
void
test_vectors_sm2dsa_release(TestVector_SM2DSA_t Vector_p);
void
test_vectors_sm2kex_release(TestVector_SM2KEX_t Vector_p);
#endif

/* Search test vector with specific properties.
   The (inline) helper function provides an test vector with
   CurveBitsMin <= CurveBits <= CurveBitsMax
   and
   HashBitsMin <= HashBits <= HashBitsMax.

   Returns NULL if no suitable vector was found.
 */
static inline
TestVector_ECDSA_t test_vectors_ecdsa_search(
        uint32_t CurveBitsMin,
        uint32_t CurveBitsMax,
        uint32_t HashBitsMin,
        uint32_t HashBitsMax)
{
    TestVector_ECDSA_t vector_p;
    uint32_t i;

    for (i = 0; ; i++)
    {
        vector_p = test_vectors_ecdsa_get(i);
        if (vector_p == NULL)
        {
            break;
        }

        if (vector_p->Curve_p->CurveBits >= CurveBitsMin &&
            vector_p->Curve_p->CurveBits <= CurveBitsMax &&
            vector_p->HashBits >= HashBitsMin &&
            vector_p->HashBits <= HashBitsMax)
        {
            break;
        }

        test_vectors_ecdsa_release(vector_p);
    }

    return vector_p;
}


#endif /* INCLUDE_GUARD_TESTVECTORS_ECDSA_H */

/* end of file testvectors_ecdsa.h */
