/* testvectors_asn1_der.h
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

#ifndef INCLUDE_GUARD_TESTVECTORS_ASN1_DER_H
#define INCLUDE_GUARD_TESTVECTORS_ASN1_DER_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

typedef struct
{
    bool fPrivateKey;
    uint8_t KeyType;
    uint8_t Method;
    uint32_t ModulusSize;
    const uint8_t * pData;
    uint32_t DataLen;
} TestVector_ASN1_DER_Rec_t;

typedef const TestVector_ASN1_DER_Rec_t * TestVector_ASN1_DER_t;

/* Key type defines */
#define TV_ASN1DER_ECC_KEY_TYPE     0U
#define TV_ASN1DER_RSA_KEY_TYPE     1U
#define TV_ASN1DER_ECDH_KEY_TYPE    2U

/* Method defines */
#define TV_ASN1DER_NIST_METHOD      0U
#define TV_ASN1DER_BPOOL_METHOD     1U
#define TV_ASN1DER_MONT_METHOD      2U
#define TV_ASN1DER_TEDWARDS_METHOD  3U
#define TV_ASN1DER_PKCS1_METHOD     4U
#define TV_ASN1DER_PSS_METHOD       5U

/* API for using ASN1 DER test vectors. */

/* Request number of ASN1 DER test vectors available. */
uint32_t
test_vectors_asn1_der_num(void);

/* Request test vector by index.
   If Index >= test_vectors_asn1_der_num(), the function returns NULL.

   Note: The function returns zero only when invalid vector has been requested.
   Note: The received vector is constant and must not be altered by caller.
   The test vector is described by structure TestVector_ASN1_DER_t and
   the structure shall be accessed directly by the user of the test vector.
*/
TestVector_ASN1_DER_t
test_vectors_asn1_der_get(uint32_t Index);

/* Release a vector.
   It is mandatory to release a vector once user of test vector is finished
   with the vector. */
void
test_vectors_asn1_der_release(TestVector_ASN1_DER_t Vector_p);


#endif /* INCLUDE_GUARD_TESTVECTORS_ASN1_DER_H */

/* end of file testvectors_asn1_der.h */
