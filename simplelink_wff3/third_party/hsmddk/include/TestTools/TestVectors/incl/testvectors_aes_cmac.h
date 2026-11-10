/* testvectors_aes_cmac.h
 *
 * Description: Test vectors for AES CMAC.
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

#ifndef INCLUDE_GUARD_TESTVECTORS_AES_CMAC_H
#define INCLUDE_GUARD_TESTVECTORS_AES_CMAC_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

/* Structure for Test Vectors. */
typedef struct
{
    const uint8_t *Key;
    const uint8_t *Msg;
    const uint8_t *Mac;
    uint32_t KeyLen;
    uint32_t MsgLen;
    uint32_t MacLen;
} TestVector_AES_CMAC_Rec_t;

typedef const TestVector_AES_CMAC_Rec_t * TestVector_AES_CMAC_t;

/* API for using AES CMAC test vectors. */

/* Request number of AES CMAC test vectors available. */
uint32_t
test_vectors_aes_cmac_num(void);

/* Request test vector by index.
   If Index >= test_vectors_aes_cmac_num(), the function returns NULL.

   Note: The function returns zero only when invalid vector has been requested.
   Note: The received vector is constant and must not be altered by caller.
   The test vector is described by structure TestVector_AES_CMAC_t and
   the structure shall be accessed directly by the user of the test vector.
*/
TestVector_AES_CMAC_t
test_vectors_aes_cmac_get(uint32_t Index);

/* Release a vector.
   It is mandatory to release a vector once user of test vector is finished
   with the vector. */
void
test_vectors_aes_cmac_release(TestVector_AES_CMAC_t Vector_p);

/* Search test vector with specific properties.
   The (inline) helper function provides an test vector with
   KeyMin <= KeyLen <= KeyMax
   and
   MsgMin <= MsgLen <= MsgMax.

   Returns NULL if no suitable vector was found.
 */
static inline
TestVector_AES_CMAC_t test_vectors_aes_cmac_search(
        uint32_t KeyMin,
        uint32_t KeyMax,
        uint32_t MsgMin,
        uint32_t MsgMax)
{
    TestVector_AES_CMAC_t vector_p;
    uint32_t i;

    for (i = 0U; ; i++)
    {
        vector_p = test_vectors_aes_cmac_get(i);

        if (!vector_p)
        {
            break;
        }

        if (vector_p->KeyLen >= KeyMin &&
            vector_p->KeyLen <= KeyMax &&
            vector_p->MsgLen >= MsgMin &&
            vector_p->MsgLen <= MsgMax)
        {
            break;
        }
    }
    return vector_p;
}


#endif /* INCLUDE_GUARD_TESTVECTORS_AES_CMAC_H */

/* end of file testvectors_aes_cmac.h */
