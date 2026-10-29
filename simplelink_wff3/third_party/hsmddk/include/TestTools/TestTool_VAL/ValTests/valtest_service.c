/* valtest_service.c
 *
 * Description: service functionality related tests
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


START_TEST(test_service_ReadWriteRegister)
{
    ValStatus_t Status;
    uint32_t RegAddress = 0xF878;
    uint32_t RegValue = 0;
    bool fCOID;

    Status = val_ServiceRegisterRead(RegAddress, &RegValue);
    if (val_CheckFunctionResult(Status) == VAL_INVALID_ADDRESS)
    {
        RegAddress = 0xF8E4;
        Status = val_ServiceRegisterRead(RegAddress, &RegValue);
    }
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_ServiceRegisterRead()=", Status);

    fCOID = valtest_IsCOIDAvailable();
    if (val_IsAccessSecure() && fCOID)
    {
        Status = val_ServiceRegisterWrite(RegAddress, RegValue);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_ServiceRegisterWrite()=", Status);
    }
    else
    {
        Status = val_ServiceRegisterWrite(RegAddress, RegValue);
        if (fCOID)
        {
            fail_if(val_CheckFunctionResult(Status) != VAL_ACCESS_ERROR, "val_ServiceRegisterWrite()=", Status);
        }
        else
        {
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_ServiceRegisterWrite()=", Status);
        }
    }
}
END_TEST


START_TEST(test_service_ZeroizeMailbox)
{
    ValStatus_t Status;

    Status = val_ServiceZeroizeMailbox();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_ServiceZeroizeMailbox()=", Status);
}
END_TEST

START_TEST(test_service_ClockSwitch)
{
    ValOctetsInOut_t DigestBuffer[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t DigestBufferSize = VAL_SYM_ALGO_MAX_DIGEST_SIZE;
    ValStatus_t Status;
    ValSymContextPtr_t SymContext_p = NULL;
    uint8_t * Msg_p = NULL;

    Status = val_SymAlloc(VAL_SYM_ALGO_HASH_SHA256, VAL_SYM_MODE_NONE, false, &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Msg_p = (uint8_t *)SFZUTF_MALLOC(4);
    fail_if(Msg_p == NULL, "Allocation ", 4);
    memcpy(Msg_p, "Test", 4);

    // Force hash clock OFF
    Status = val_ServiceClockSwitch(0, 0x02);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_ServiceClockSwitch()=", Status);

    // Do hash
    Status = val_SymHashFinal(SymContext_p,
                              Msg_p, 4,
                              (ValOctetsInOut_t * const)&DigestBuffer, &DigestBufferSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_CLOCK_ERROR, "val_SymHashFinal()=", Status);

    // Set all clocks in automatic mode
    Status = val_ServiceClockSwitch(0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_ServiceClockSwitch()=", Status);

    // Do hash
    Status = val_SymHashFinal(SymContext_p,
                              Msg_p, 4,
                              (ValOctetsInOut_t * const)&DigestBuffer, &DigestBufferSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashFinal()=", Status);

    SFZUTF_FREE(Msg_p);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
}
END_TEST


int
suite_add_test_Service(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "Service_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_service_ReadWriteRegister) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_service_ZeroizeMailbox) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_service_ClockSwitch) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_service.c */
