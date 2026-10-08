/* valtest_securetimer.c
 *
 * Description: Secure timer related tests
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


START_TEST(test_secure_timer)
{
    ValStatus_t Status;
    ValAssetId_t TimerAssetId_100us = VAL_ASSETID_INVALID;
    ValAssetId_t TimerAssetId_sec = VAL_ASSETID_INVALID;
    ValAssetId_t TimerAssetId_check = VAL_ASSETID_INVALID;
    uint32_t ElapsedTime;

    Status = val_SecureTimerStart(true, &TimerAssetId_check);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerStart()=", Status);

    Status = val_SecureTimerStart(false, &TimerAssetId_100us);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerStart()=", Status);

    Status = val_SecureTimerStart(true, &TimerAssetId_sec);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerStart()=", Status);

    Status = val_SecureTimerRead(TimerAssetId_sec, &ElapsedTime);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerRead()=", Status);
    // The expected ElapsedTime is zero. However, it can also be that the
    // execution moment of the timer start and read lay in the next consecutive
    // seconds. In that case, the ElapsedTime will be at the most one.
    fail_if(ElapsedTime > 1, "Expected to be zero or at the most one", ElapsedTime);

    Status = val_SecureTimerStop(TimerAssetId_check, &ElapsedTime);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerStop()=", Status);

    SFZUTF_USLEEP(100);

    Status = val_SecureTimerRead(TimerAssetId_100us, &ElapsedTime);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerRead()=", Status);
    fail_if(ElapsedTime == 0, "Expected to be not zero ", ElapsedTime);

    Status = val_SecureTimerRelease(TimerAssetId_100us);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerRelease()=", Status);

    while (true)
    {
        Status = val_SecureTimerRead(TimerAssetId_sec, &ElapsedTime);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerRead()=", Status);
        if (ElapsedTime != 0)
        {
            break;
        }
        SFZUTF_USLEEP(1000);
    }
    fail_if(ElapsedTime != 1, "Expected to be one ", ElapsedTime);

    Status = val_SecureTimerStop(TimerAssetId_sec, &ElapsedTime);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerStop()=", Status);
}
END_TEST


START_TEST(test_secure_timer_restart)
{
    ValStatus_t Status;
    ValAssetId_t TimerAssetId_100us1 = VAL_ASSETID_INVALID;
    ValAssetId_t TimerAssetId_100us2;
    uint32_t ElapsedTime1;
    uint32_t ElapsedTime2;

    /* Start a timer */
    Status = val_SecureTimerStart(false, &TimerAssetId_100us1);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerStart()=", Status);

    SFZUTF_USLEEP(1000);

    /* Read the elapsed time */
    Status = val_SecureTimerRead(TimerAssetId_100us1, &ElapsedTime1);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerRead()=", Status);

    /* Restart the timer
     * Note: The timer Asset ID is copied to make sure that no new Asset is created.
     */
    TimerAssetId_100us2 = TimerAssetId_100us1;
    Status = val_SecureTimerStart(false, &TimerAssetId_100us2);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerStart()=", Status);
    fail_if(TimerAssetId_100us2 != TimerAssetId_100us1, "Asset change not expected", Status);

    SFZUTF_USLEEP(500);

    /* Read the elapsed time - ElapsedTime2 shall be smaller than ElapsedTime1 */
    Status = val_SecureTimerRead(TimerAssetId_100us1, &ElapsedTime2);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerRead()=", Status);
    fail_if(ElapsedTime1 < ElapsedTime2, "ElapsedTime1 should be bigger than ElapsedTime2 ", (ElapsedTime1-ElapsedTime2));

    /* Stop and release the timer */
    Status = val_SecureTimerRelease(TimerAssetId_100us1);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SecureTimerRelease()=", Status);
}
END_TEST


int
suite_add_test_SecureTimer(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SecureTimer_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_secure_timer) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_secure_timer_restart) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_securetimer.c */
