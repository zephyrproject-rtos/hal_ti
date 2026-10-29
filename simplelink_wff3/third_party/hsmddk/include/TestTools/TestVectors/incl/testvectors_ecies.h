/* testvectors_ecies.h
 *
 * Description: Test vectors for ECIES.
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

#ifndef INCLUDE_GUARD_TESTVECTORS_ECIES_H
#define INCLUDE_GUARD_TESTVECTORS_ECIES_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_ecc_curves.h"

/* Structures for Test Vectors. */
typedef struct
{
    const TestVector_ECC_Curve_Rec_t * Curve_p;
    const uint8_t * PrivateKey_p;
    uint32_t PrivateKeyLen;
    const uint8_t * PublicKey_p;
    uint32_t PublicKeyLen;
    uint32_t HmacLen;
} TestVector_ECIES_Rec_t;

/* Note: Hmac (=message) is random generated in test */

typedef const TestVector_ECIES_Rec_t * TestVector_ECIES_t;

/* API for using ECIES test vectors. */

/* Request number of ECIES test vectors available. */
uint32_t
test_vectors_ecies_num(void);

/* Request test vector by index.
   If Index >= test_vectors_ECIES_num(), the function returns NULL.

   Notes:
   - The function returns zero only when invalid vector has been requested.
   - The received vector is constant and must not be altered by caller.
     The test vector is described by structure TestVector_ECIES_t and
     the structure shall be accessed directly by the user of the test vector.
*/
TestVector_ECIES_t
test_vectors_ecies_get(uint32_t Index);

/* Release a vector.
   It is mandatory to release a vector once user of test vector is finished
   with the vector. */
void
test_vectors_ecies_release(TestVector_ECIES_t Vector_p);

#endif

/* end of file testvectors_ecies.c */
