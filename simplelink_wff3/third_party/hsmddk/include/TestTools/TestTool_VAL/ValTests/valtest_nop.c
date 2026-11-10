/* valtest_nop.c
 *
 * Description: NOP related tests
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

#include "valtest_internal.h"


#define TEST_NOP_BUFFER_SIZE 4096
START_TEST(test_nop)
{
    uint8_t * src_p;
    uint8_t * dst_p;
    uint32_t len;
    int i;
    ValStatus_t Status;

    src_p = (uint8_t *)SFZUTF_MALLOC(TEST_NOP_BUFFER_SIZE);
    dst_p = (uint8_t *)SFZUTF_MALLOC(TEST_NOP_BUFFER_SIZE + 4);
    fail_if(((src_p == NULL) || (dst_p == NULL)),
            "Allocation ", TEST_NOP_BUFFER_SIZE);

    for(i = 0; i < TEST_NOP_BUFFER_SIZE; i++)
    {
        src_p[i] = (uint8_t)i;
    }

    len = TEST_NOP_BUFFER_SIZE;
    memset(dst_p, 0xA5, len + 4);

    Status = val_NOP(src_p, dst_p, len);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_NOP()=", Status);

#ifdef VALTEST_TRACE_NOP_DATA
    Log_HexDump("NOP out:", 0, dst_p, len + 4);
#endif

    /* Verify copy actually happened. */
    fail_if(memcmp(dst_p, src_p, len) != 0, "Data mismatch", -1);

    /* Verify that copying didn't write anything beyond three bytes of
       workspace. */
    fail_if(dst_p[len + 0] != 0xA5, "Wrote beyond end of buffer ", dst_p[len + 0]);
    fail_if(dst_p[len + 1] != 0xA5, "Wrote beyond end of buffer ", dst_p[len + 1]);
    fail_if(dst_p[len + 2] != 0xA5, "Wrote beyond end of buffer ", dst_p[len + 2]);
    fail_if(dst_p[len + 3] != 0xA5, "Wrote beyond end of buffer ", dst_p[len + 3]);

    // try again with a different pattern
    for(i = 0; i < TEST_NOP_BUFFER_SIZE; i++)
    {
        src_p[i] = (uint8_t)(i ^ 0xFF);
    }

    len = TEST_NOP_BUFFER_SIZE;
    memset(dst_p, 0x5A, len + 4);

    Status = val_NOP(src_p, dst_p, len);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_NOP()=", Status);
    fail_if(val_CheckFipsApproved(Status), "val_NOP(FIPS)=", Status);

#ifdef VALTEST_TRACE_NOP_DATA
    Log_HexDump("NOP out:", 0, dst_p, len + 4);
#endif

    /* Verify copy actually happened. */
    fail_if(memcmp(dst_p, src_p, len) != 0, "Data mismatch", -1);

    /* Verify that copying didn't write anything beyond three bytes of
       workspace. */
    fail_if(dst_p[len + 0] != 0x5A, "Wrote beyond end of buffer ", dst_p[len + 0]);
    fail_if(dst_p[len + 1] != 0x5A, "Wrote beyond end of buffer ", dst_p[len + 1]);
    fail_if(dst_p[len + 2] != 0x5A, "Wrote beyond end of buffer ", dst_p[len + 2]);
    fail_if(dst_p[len + 3] != 0x5A, "Wrote beyond end of buffer ", dst_p[len + 3]);

    SFZUTF_FREE(src_p);
    SFZUTF_FREE(dst_p);
}
END_TEST
#undef TEST_NOP_BUFFER_SIZE

#ifdef SFZUTF_USERMODE
#define TEST_NOP_BUFFER_SIZE (16 + 8)
START_TEST(test_nop_unaligned_buffer)
{
    uint8_t * src_p;
    uint8_t * dst_p;
    uint32_t len;
    unsigned int i, j;
    ValStatus_t Status;

    src_p = (uint8_t *)SFZUTF_MALLOC(TEST_NOP_BUFFER_SIZE);
    dst_p = (uint8_t *)SFZUTF_MALLOC(TEST_NOP_BUFFER_SIZE + 4);
    fail_if(((src_p == NULL) || (dst_p == NULL)),
            "Allocation ", TEST_NOP_BUFFER_SIZE);

    for(i = 0; i < TEST_NOP_BUFFER_SIZE; i++)
    {
        src_p[i] = (uint8_t)(128 + i);
    }

    // The use of bounce buffers might render below tests useless
    //for(len = 1; len <= 16; len++)
    for(len = 8; len <= 16; len += 8)
    {
        // try all possible src alignments
        for(i = 0; i < 3; i++)
        {
            uint8_t * unaligned_src = src_p + i;

            // try all possible dst alignments
            for(j = 0; j < 3; j++)
            {
                uint8_t * unaligned_dst = dst_p + j;

                memset(dst_p, 0, (TEST_NOP_BUFFER_SIZE + 4));

                /* use NOP token to perform a memory copy */
                Status = val_NOP(unaligned_src, unaligned_dst, len);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_NOP()=", Status);

                /* Verify the copy really happened. */
                fail_if(memcmp(unaligned_dst, unaligned_src, len) != 0,
                            "Data mismatch", -1);
            }
        }
    }

    SFZUTF_FREE(src_p);
    SFZUTF_FREE(dst_p);
}
END_TEST
#undef TEST_NOP_BUFFER_SIZE
#endif

START_TEST(test_nop_arguments)
{
    uint8_t * DataBuffer_p;
    ValStatus_t Status;

    DataBuffer_p = (uint8_t *)SFZUTF_MALLOC(100);
    fail_if(DataBuffer_p == NULL, "Allocation ", 100);

    Status = val_NOP(NULL, DataBuffer_p, 64);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_NOP(BadArgument1)=", Status);

    Status = val_NOP(DataBuffer_p, NULL, 64);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_NOP(BadArgument2)=", Status);

    Status = val_NOP(DataBuffer_p, DataBuffer_p, 0);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_NOP(BadArgument3)=", Status);

    SFZUTF_FREE(DataBuffer_p);
}
END_TEST

int
suite_add_test_Nop(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "NOP_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_nop) != 0) goto FuncErrorReturn;
#ifdef SFZUTF_USERMODE
        if (sfzutf_test_add(TestCase_p, test_nop_unaligned_buffer) != 0) goto FuncErrorReturn;
#endif
        if (valtest_StrictArgsCheck())
        {
            if (sfzutf_test_add(TestCase_p, test_nop_arguments) != 0) goto FuncErrorReturn;
        }
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_nop.c */
