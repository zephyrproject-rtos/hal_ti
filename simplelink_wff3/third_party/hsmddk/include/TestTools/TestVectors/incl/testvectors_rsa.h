/* testvectors_rsa.h
 *
 * Description: Test vectors for RSA.
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

#ifndef INCLUDE_GUARD_TESTVECTORS_RSA_H
#define INCLUDE_GUARD_TESTVECTORS_RSA_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

/* Structures for Test Vectors. */
typedef struct
{
    const uint8_t * VersionId_p;
    uint32_t VersionIdBytes;
    const uint8_t * Modulus_p;
    uint32_t ModulusBytes;
    const uint8_t * PublicExponent_p;
    uint32_t PublicExponentBytes;
    const uint8_t * PrivateExponent_p;
    uint32_t PrivateExponentBytes;
    const uint8_t * Prime1_p;
    uint32_t Prime1Bytes;
    const uint8_t * Prime2_p;
    uint32_t Prime2Bytes;
    const uint8_t * Exponent1_p;
    uint32_t Exponent1Bytes;
    const uint8_t * Exponent2_p;
    uint32_t Exponent2Bytes;
    const uint8_t * Coefficient_p;
    uint32_t CoefficientBytes;
} TestVector_RSA_PKCS1v15_KeyPair_Rec_t;

typedef struct
{
    const char * Name_p;
    uint32_t ModulusBits;
    uint32_t HashBits;
    TestVector_RSA_PKCS1v15_KeyPair_Rec_t Key;
    const uint8_t * Msg_p;
    uint32_t MsgBytes;
    const uint8_t * Signature_p;
    uint32_t SignatureBytes;
} TestVector_RSA_PKCS1v15_Rec_t;

typedef const TestVector_RSA_PKCS1v15_Rec_t * TestVector_RSA_PKCS1v15_t;


typedef struct
{
    const uint8_t * Modulus_p;
    uint32_t ModulusBytes;
    const uint8_t * PublicExponent_p;
    uint32_t PublicExponentBytes;
    const uint8_t * PrivateExponent_p;
    uint32_t PrivateExponentBytes;
} TestVector_RSA_PSS_KeyPair_Rec_t;

typedef struct
{
    const char * Name_p;
    uint32_t ModulusBits;
    uint32_t HashBits;
    TestVector_RSA_PSS_KeyPair_Rec_t Key;
    const uint8_t * Msg_p;
    uint32_t MsgBytes;
    const uint8_t * Signature_p;
    uint32_t SignatureBytes;
} TestVector_RSA_PSS_Rec_t;

typedef const TestVector_RSA_PSS_Rec_t * TestVector_RSA_PSS_t;


typedef struct
{
    const uint8_t * Modulus_p;
    uint32_t ModulusBytes;
    const uint8_t * PublicExponent_p;
    uint32_t PublicExponentBytes;
    const uint8_t * PrivateExponent_p;
    uint32_t PrivateExponentBytes;
} TestVector_RSA_OAEP_KeyPair_Rec_t;

typedef struct
{
    const char * Name_p;
    uint32_t ModulusBits;
    uint32_t HashBits;
    TestVector_RSA_OAEP_KeyPair_Rec_t Key;
    const uint8_t * AdditionalInput_p;
    uint32_t AdditionalInputBytes;
    const uint8_t * AdditionalInputHash_p;
    uint32_t AdditionalInputHashBytes;
    const uint8_t * PlainData_p;
    uint32_t PlainDataBytes;
    const uint8_t * WrappedData_p;
    uint32_t WrappedDataBytes;
} TestVector_RSA_OAEP_Rec_t;

typedef const TestVector_RSA_OAEP_Rec_t * TestVector_RSA_OAEP_t;


typedef struct
{
    const uint8_t * Modulus_p;
    uint32_t ModulusBytes;
    const uint8_t * PublicExponent_p;
    uint32_t PublicExponentBytes;
    const uint8_t * PrivateExponent_p;
    uint32_t PrivateExponentBytes;
} TestVector_RSA_PKCS1V15WRAP_KeyPair_Rec_t;

typedef struct
{
    const char * Name_p;
    uint32_t ModulusBits;
    uint32_t HashBits;
    TestVector_RSA_PKCS1V15WRAP_KeyPair_Rec_t Key;
    const uint8_t * PlainData_p;
    uint32_t PlainDataBytes;
    const uint8_t * WrappedData_p;
    uint32_t WrappedDataBytes;
} TestVector_RSA_PKCS1V15WRAP_Rec_t;

typedef const TestVector_RSA_PKCS1V15WRAP_Rec_t * TestVector_PKCS1V15WRAP_t;


/* API for using RSA based test vectors. */

/* Request number of RSA PKCS#1 v1.5 test vectors available. */
uint32_t
test_vectors_rsa_pkcs1v15_num(void);

/* Request test vector by index.
   If Index >= test_vectors_rsa_pkcs1v15_num(), the function returns NULL.

   Note: The function returns zero only when invalid vector has been requested.
   Note: The received vector is constant and must not be altered by caller.
   The test vector is described by structure TestVector_RSA_PKCS1v15_t and
   the structure shall be accessed directly by the user of the test vector.
*/
TestVector_RSA_PKCS1v15_t
test_vectors_rsa_pkcs1v15_get(uint32_t Index);

/* Release a vector.
   It is mandatory to release a vector once user of test vector is finished
   with the vector. */
void
test_vectors_rsa_pkcs1v15_release(TestVector_RSA_PKCS1v15_t Vector_p);


/* Request number of RSA PSS test vectors available. */
uint32_t
test_vectors_rsa_pss_num(void);

/* Request test vector by index.
   If Index >= test_vectors_rsa_pss_num(), the function returns NULL.

   Note: The function returns zero only when invalid vector has been requested.
   Note: The received vector is constant and must not be altered by caller.
   The test vector is described by structure TestVector_RSA_PSS_t and
   the structure shall be accessed directly by the user of the test vector.
*/
TestVector_RSA_PSS_t
test_vectors_rsa_pss_get(uint32_t Index);

/* Release a vector.
   It is mandatory to release a vector once user of test vector is finished
   with the vector. */
void
test_vectors_rsa_pss_release(TestVector_RSA_PSS_t Vector_p);


/* Request number of RSA OAEP test vectors available. */
uint32_t
test_vectors_rsa_oaep_num(void);

/* Request test vector by index.
   If Index >= test_vectors_rsa_oaep_num(), the function returns NULL.

   Note: The function returns zero only when invalid vector has been requested.
   Note: The received vector is constant and must not be altered by caller.
   The test vector is described by structure TestVector_RSA_OAEP_t and
   the structure shall be accessed directly by the user of the test vector.
*/
TestVector_RSA_OAEP_t
test_vectors_rsa_oaep_get(uint32_t Index);

/* Release a vector.
   It is mandatory to release a vector once user of test vector is finished
   with the vector. */
void
test_vectors_rsa_oaep_release(TestVector_RSA_OAEP_t Vector_p);


/* Request number of RSA PKCS#1v1.5 test vectors available. */
uint32_t
test_vectors_rsa_pkcs1v15wrap_num(void);

/* Request test vector by index.
   If Index >= test_vectors_rsa_pkcs1v15wrap_num(), the function returns NULL.

   Note: The function returns zero only when invalid vector has been requested.
   Note: The received vector is constant and must not be altered by caller.
   The test vector is described by structure TestVector_PKCS1V15WRAP_t and
   the structure shall be accessed directly by the user of the test vector.
*/
TestVector_PKCS1V15WRAP_t
test_vectors_rsa_pkcs1v15wrap_get(uint32_t Index);

/* Release a vector.
   It is mandatory to release a vector once user of test vector is finished
   with the vector. */
void
test_vectors_rsa_pkcs1v15wrap_release(TestVector_PKCS1V15WRAP_t Vector_p);


#endif /* INCLUDE_GUARD_TESTVECTORS_RSA_H */

/* end of file testvectors_rsa.h */
