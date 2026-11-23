/* testvectors_milenage.c
 *
 * Description: Test vectors for Milenage
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

#ifdef EIP130_ENABLE_SF_MILENAGE

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include "testvectors_milenage.h"
#include "testvectors_milenage_data.h"

/* Macros used to build the test vectors. */
#define TEST_VECTOR_MILENAGE(K, RAND, SQN, AMF, OP, OPc, f1, f1star, f2, f3, f4, f5, f5star)       \
    {                                                                                              \
        K, RAND, SQN, AMF, OP, OPc, f1, f1star, f2, f3, f4, f5, f5star,                            \
        sizeof(K), sizeof(RAND), sizeof(SQN), sizeof(AMF), sizeof(OP), sizeof(OPc),                \
        sizeof(f1), sizeof(f1star), sizeof(f2), sizeof(f3), sizeof(f4), sizeof(f5), sizeof(f5star) \
    }

static const TestVector_Milenage_Rec_t Milenage_test_vectors [] =
{
    TEST_VECTOR_MILENAGE(Milenage_TS1_K, Milenage_TS1_RAND, Milenage_TS1_SQN, Milenage_TS1_AMF,
                         Milenage_TS1_OP, Milenage_TS1_OPc,
                         Milenage_TS1_f1, Milenage_TS1_f1star, Milenage_TS1_f2, Milenage_TS1_f3,
                         Milenage_TS1_f4, Milenage_TS1_f5, Milenage_TS1_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS2_K, Milenage_TS2_RAND, Milenage_TS2_SQN, Milenage_TS2_AMF,
                         Milenage_TS2_OP, Milenage_TS2_OPc,
                         Milenage_TS2_f1, Milenage_TS2_f1star, Milenage_TS2_f2, Milenage_TS2_f3,
                         Milenage_TS2_f4, Milenage_TS2_f5, Milenage_TS2_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS3_K, Milenage_TS3_RAND, Milenage_TS3_SQN, Milenage_TS3_AMF,
                         Milenage_TS3_OP, Milenage_TS3_OPc,
                         Milenage_TS3_f1, Milenage_TS3_f1star, Milenage_TS3_f2, Milenage_TS3_f3,
                         Milenage_TS3_f4, Milenage_TS3_f5, Milenage_TS3_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS4_K, Milenage_TS4_RAND, Milenage_TS4_SQN, Milenage_TS4_AMF,
                         Milenage_TS4_OP, Milenage_TS4_OPc,
                         Milenage_TS4_f1, Milenage_TS4_f1star, Milenage_TS4_f2, Milenage_TS4_f3,
                         Milenage_TS4_f4, Milenage_TS4_f5, Milenage_TS4_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS5_K, Milenage_TS5_RAND, Milenage_TS5_SQN, Milenage_TS5_AMF,
                         Milenage_TS5_OP, Milenage_TS5_OPc,
                         Milenage_TS5_f1, Milenage_TS5_f1star, Milenage_TS5_f2, Milenage_TS5_f3,
                         Milenage_TS5_f4, Milenage_TS5_f5, Milenage_TS5_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS6_K, Milenage_TS6_RAND, Milenage_TS6_SQN, Milenage_TS6_AMF,
                         Milenage_TS6_OP, Milenage_TS6_OPc,
                         Milenage_TS6_f1, Milenage_TS6_f1star, Milenage_TS6_f2, Milenage_TS6_f3,
                         Milenage_TS6_f4, Milenage_TS6_f5, Milenage_TS6_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS7_K, Milenage_TS7_RAND, Milenage_TS7_SQN, Milenage_TS7_AMF,
                         Milenage_TS7_OP, Milenage_TS7_OPc,
                         Milenage_TS7_f1, Milenage_TS7_f1star, Milenage_TS7_f2, Milenage_TS7_f3,
                         Milenage_TS7_f4, Milenage_TS7_f5, Milenage_TS7_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS8_K, Milenage_TS8_RAND, Milenage_TS8_SQN, Milenage_TS8_AMF,
                         Milenage_TS8_OP, Milenage_TS8_OPc,
                         Milenage_TS8_f1, Milenage_TS8_f1star, Milenage_TS8_f2, Milenage_TS8_f3,
                         Milenage_TS8_f4, Milenage_TS8_f5, Milenage_TS8_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS9_K, Milenage_TS9_RAND, Milenage_TS9_SQN, Milenage_TS9_AMF,
                         Milenage_TS9_OP, Milenage_TS9_OPc,
                         Milenage_TS9_f1, Milenage_TS9_f1star, Milenage_TS9_f2, Milenage_TS9_f3,
                         Milenage_TS9_f4, Milenage_TS9_f5, Milenage_TS9_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS10_K, Milenage_TS10_RAND, Milenage_TS10_SQN, Milenage_TS10_AMF,
                         Milenage_TS10_OP, Milenage_TS10_OPc,
                         Milenage_TS10_f1, Milenage_TS10_f1star, Milenage_TS10_f2, Milenage_TS10_f3,
                         Milenage_TS10_f4, Milenage_TS10_f5, Milenage_TS10_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS11_K, Milenage_TS11_RAND, Milenage_TS11_SQN, Milenage_TS11_AMF,
                         Milenage_TS11_OP, Milenage_TS11_OPc,
                         Milenage_TS11_f1, Milenage_TS11_f1star, Milenage_TS11_f2, Milenage_TS11_f3,
                         Milenage_TS11_f4, Milenage_TS11_f5, Milenage_TS11_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS12_K, Milenage_TS12_RAND, Milenage_TS12_SQN, Milenage_TS12_AMF,
                         Milenage_TS12_OP, Milenage_TS12_OPc,
                         Milenage_TS12_f1, Milenage_TS12_f1star, Milenage_TS12_f2, Milenage_TS12_f3,
                         Milenage_TS12_f4, Milenage_TS12_f5, Milenage_TS12_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS13_K, Milenage_TS13_RAND, Milenage_TS13_SQN, Milenage_TS13_AMF,
                         Milenage_TS13_OP, Milenage_TS13_OPc,
                         Milenage_TS13_f1, Milenage_TS13_f1star, Milenage_TS13_f2, Milenage_TS13_f3,
                         Milenage_TS13_f4, Milenage_TS13_f5, Milenage_TS13_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS14_K, Milenage_TS14_RAND, Milenage_TS14_SQN, Milenage_TS14_AMF,
                         Milenage_TS14_OP, Milenage_TS14_OPc,
                         Milenage_TS14_f1, Milenage_TS14_f1star, Milenage_TS14_f2, Milenage_TS14_f3,
                         Milenage_TS14_f4, Milenage_TS14_f5, Milenage_TS14_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS15_K, Milenage_TS15_RAND, Milenage_TS15_SQN, Milenage_TS15_AMF,
                         Milenage_TS15_OP, Milenage_TS15_OPc,
                         Milenage_TS15_f1, Milenage_TS15_f1star, Milenage_TS15_f2, Milenage_TS15_f3,
                         Milenage_TS15_f4, Milenage_TS15_f5, Milenage_TS15_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS16_K, Milenage_TS16_RAND, Milenage_TS16_SQN, Milenage_TS16_AMF,
                         Milenage_TS16_OP, Milenage_TS16_OPc,
                         Milenage_TS16_f1, Milenage_TS16_f1star, Milenage_TS16_f2, Milenage_TS16_f3,
                         Milenage_TS16_f4, Milenage_TS16_f5, Milenage_TS16_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS17_K, Milenage_TS17_RAND, Milenage_TS17_SQN, Milenage_TS17_AMF,
                         Milenage_TS17_OP, Milenage_TS17_OPc,
                         Milenage_TS17_f1, Milenage_TS17_f1star, Milenage_TS17_f2, Milenage_TS17_f3,
                         Milenage_TS17_f4, Milenage_TS17_f5, Milenage_TS17_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS18_K, Milenage_TS18_RAND, Milenage_TS18_SQN, Milenage_TS18_AMF,
                         Milenage_TS18_OP, Milenage_TS18_OPc,
                         Milenage_TS18_f1, Milenage_TS18_f1star, Milenage_TS18_f2, Milenage_TS18_f3,
                         Milenage_TS18_f4, Milenage_TS18_f5, Milenage_TS18_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS19_K, Milenage_TS19_RAND, Milenage_TS19_SQN, Milenage_TS19_AMF,
                         Milenage_TS19_OP, Milenage_TS19_OPc,
                         Milenage_TS19_f1, Milenage_TS19_f1star, Milenage_TS19_f2, Milenage_TS19_f3,
                         Milenage_TS19_f4, Milenage_TS19_f5, Milenage_TS19_f5star),
    TEST_VECTOR_MILENAGE(Milenage_TS20_K, Milenage_TS20_RAND, Milenage_TS20_SQN, Milenage_TS20_AMF,
                         Milenage_TS20_OP, Milenage_TS20_OPc,
                         Milenage_TS20_f1, Milenage_TS20_f1star, Milenage_TS20_f2, Milenage_TS20_f3,
                         Milenage_TS20_f4, Milenage_TS20_f5, Milenage_TS20_f5star),
};


/* The function API for accessing the vectors. */
uint32_t
test_vectors_milenage_num(void)
{
    return sizeof(Milenage_test_vectors) / sizeof(Milenage_test_vectors[0]);
}

TestVector_Milenage_t
test_vectors_milenage_get(uint32_t Index)
{
    if (Index >= test_vectors_milenage_num())
    {
        return NULL;
    }
    return &Milenage_test_vectors[Index];
}

void
test_vectors_milenage_release(TestVector_Milenage_t Vector_p)
{
    /* Test vectors are statically defined => nothing to do. */
    (void)Vector_p;
}

#endif /* EIP130_ENABLE_SF_MILENAGE */

/* end of file testvectors_milenage.c */
