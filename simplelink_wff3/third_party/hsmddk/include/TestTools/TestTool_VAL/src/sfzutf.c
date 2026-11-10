/* sfzutf.c
 *
 * Description: SFZUTF implementation file.
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

#include "sfzutf_internal.h"

/* Active test information */
const char * g_pActiveTestName = "-";
int g_ActiveTestLoop = 0;

/* Test administration */
static struct TestSuite * gl_TestSuite = NULL;

struct TestSuite *
sfzutf_tsuite_create(
        const char * Name_p)
{
    struct TestSuite * TestSuite_p;

    if (gl_TestSuite == NULL)
    {
        TestSuite_p = (struct TestSuite *)SFZUTF_MALLOC(sizeof(struct TestSuite));
        if (TestSuite_p == NULL)
        {
            return NULL;
        }
        gl_TestSuite = TestSuite_p;
    }
    else
    {
        for (TestSuite_p = gl_TestSuite;
             TestSuite_p->NextSuite_p != NULL;
             TestSuite_p = TestSuite_p->NextSuite_p)
        {
            if (SFZUTF_STREQ(TestSuite_p->Name_p, Name_p))
            {
                return NULL;
            }
        }

        TestSuite_p->NextSuite_p = (struct TestSuite *)SFZUTF_MALLOC(sizeof(struct TestSuite));
        if (TestSuite_p->NextSuite_p == NULL)
        {
            return NULL;
        }
        TestSuite_p = TestSuite_p->NextSuite_p;
    }

    TestSuite_p->NextSuite_p    = NULL;
    TestSuite_p->TestCaseList_p = NULL;
    TestSuite_p->Enabled        = false;
    TestSuite_p->Name_p         = Name_p;
    return TestSuite_p;
}

void
sfzutf_tsuite_dump(void)
{
    struct TestSuite * TestSuite_p = gl_TestSuite;

    if (TestSuite_p != NULL)
    {
        while (TestSuite_p != NULL)
        {
            struct TestCase * TestCase_p = TestSuite_p->TestCaseList_p;

            LOG_CRIT("Test Suite: %s (%d)\n", TestSuite_p->Name_p, TestSuite_p->Enabled);

            while(TestCase_p != NULL)
            {
                struct Test * Test_p = TestCase_p->TestList_p;

                LOG_CRIT("  Test Case: %s (%d)\n", TestCase_p->Name_p, TestCase_p->Enabled);

                while(Test_p != NULL)
                {

                    LOG_CRIT("    Test: %s (%d, %d)\n", Test_p->Name_p, Test_p->NumberOfLoops, Test_p->Enabled);

                    Test_p = Test_p->NextTest_p;
                }

                TestCase_p = TestCase_p->NextCase_p;
            }

            TestSuite_p = TestSuite_p->NextSuite_p;
        }
    }
    else
    {
        LOG_CRIT("No Test Suite available\n");
    }
}

void
sfzutf_tsuite_release(
        const char * Name_p)
{
    struct TestSuite * TestSuite_p = gl_TestSuite;
    struct TestSuite * PrevTestSuite_p = NULL;

    while(TestSuite_p != NULL)
    {
        struct TestSuite * NextTestSuite_p = TestSuite_p->NextSuite_p;

        if ((Name_p == NULL) || SFZUTF_STREQ(TestSuite_p->Name_p, Name_p))
        {
            sfzutf_tcase_release(TestSuite_p->TestCaseList_p, NULL);
            SFZUTF_FREE(TestSuite_p);

            if (PrevTestSuite_p != NULL)
            {
                PrevTestSuite_p->NextSuite_p = NextTestSuite_p;
                break;
            }
        }
        else
        {
            PrevTestSuite_p = TestSuite_p;
        }
        TestSuite_p = NextTestSuite_p;
    }
}

struct TestCase *
sfzutf_tcase_create(
        struct TestSuite *TestSuite_p,
        const char * Name_p)
{
    struct TestCase *TestCase_p;

    if (TestSuite_p == NULL)
    {
        return NULL;
    }

    if (TestSuite_p->TestCaseList_p == NULL)
    {
        TestCase_p = (struct TestCase *)SFZUTF_MALLOC(sizeof(struct TestCase));
        if (TestCase_p == NULL)
        {
            return NULL;
        }
        TestSuite_p->TestCaseList_p = TestCase_p;
    }
    else
    {
        for (TestCase_p = TestSuite_p->TestCaseList_p;
             TestCase_p->NextCase_p != NULL;
             TestCase_p = TestCase_p->NextCase_p)
        {
            if (SFZUTF_STREQ(TestCase_p->Name_p, Name_p))
            {
                return NULL;
            }
        }

        TestCase_p->NextCase_p = (struct TestCase *)SFZUTF_MALLOC(sizeof(struct TestCase));
        if (TestCase_p->NextCase_p == NULL)
        {
            return NULL;
        }
        TestCase_p = TestCase_p->NextCase_p;
    }

    TestCase_p->NextCase_p       = NULL;
    TestCase_p->Name_p           = Name_p;
    TestCase_p->FixtureStartFunc = NULL;
    TestCase_p->FixtureEndFunc   = NULL;
    TestCase_p->TestList_p       = NULL;
    TestCase_p->TestsSuccess     = 0;
    TestCase_p->TestsFailed      = 0;
    TestCase_p->Enabled          = false;
    return TestCase_p;
}

void
sfzutf_tcase_release(
        struct TestCase * TestCaseList_p,
        const char * Name_p)
{
    struct TestCase * TestCase_p = TestCaseList_p;
    struct TestCase * PrevTestCase_p = NULL;

    while(TestCase_p != NULL)
    {
        struct TestCase * NextTestCase_p = TestCase_p->NextCase_p;

        if ((Name_p == NULL) || SFZUTF_STREQ(TestCase_p->Name_p, Name_p))
        {
            sfzutf_ttest_release(TestCase_p->TestList_p, NULL);
            SFZUTF_FREE(TestCase_p);

            if (PrevTestCase_p != NULL)
            {
                PrevTestCase_p->NextCase_p = NextTestCase_p;
                break;
            }
        }
        else
        {
            PrevTestCase_p = TestCase_p;
        }
        TestCase_p = NextTestCase_p;
    }
}

int
sfzutf_tcase_add_fixture(
        struct TestCase * TestCase_p,
        SFun StartFunc,
        SFun EndFunc)
{
    if (TestCase_p == NULL)
    {
        return -1;
    }

    TestCase_p->FixtureStartFunc = StartFunc;
    TestCase_p->FixtureEndFunc   = EndFunc;

    return 0;
}

int
sfzutf_ttest_create(
        struct TestCase * TestCase_p,
        TFun TestFunction,
        const char * Name_p,
        int NumberOfLoops)
{
    struct Test * Test_p;

    if (TestCase_p == NULL)
    {
        return -1;
    }

    if (TestCase_p->TestList_p == NULL)
    {
        Test_p = (struct Test *)SFZUTF_MALLOC(sizeof(struct Test));
        if (Test_p == NULL)
        {
            return -1;
        }
        TestCase_p->TestList_p = Test_p;
    }
    else
    {
        for (Test_p = TestCase_p->TestList_p;
             Test_p->NextTest_p != NULL;
             Test_p = Test_p->NextTest_p)
        {
            if (SFZUTF_STREQ(Test_p->Name_p, Name_p))
            {
                return -1;
            }
        }

        Test_p->NextTest_p = (struct Test *)SFZUTF_MALLOC(sizeof(struct Test));
        if (Test_p->NextTest_p == NULL)
        {
            return -1;
        }
        Test_p = Test_p->NextTest_p;
    }

    Test_p->NextTest_p = NULL;
    Test_p->Name_p     = Name_p;
    Test_p->TestFunc   = TestFunction;
    Test_p->Enabled    = false;
    Test_p->Start      = 0;
    if (NumberOfLoops > 0)
    {
        Test_p->NumberOfLoops = (NumberOfLoops - 1);
    }
    else
    {
        Test_p->NumberOfLoops = 0;
    }
    return 0;
}

void
sfzutf_ttest_release(
        struct Test * TestList_p,
        const char * Name_p)
{
    struct Test * Test_p = TestList_p;
    struct Test * PrevTest_p = NULL;

    while(Test_p != NULL)
    {
        struct Test * NextTest_p = Test_p->NextTest_p;

        if ((Name_p == NULL) || SFZUTF_STREQ(Test_p->Name_p, Name_p))
        {
            SFZUTF_FREE(Test_p);

            if (PrevTest_p != NULL)
            {
                PrevTest_p->NextTest_p = NextTest_p;
                break;
            }
        }
        else
        {
            PrevTest_p = Test_p;
        }
        Test_p = NextTest_p;
    }
}

static int
sfzutf_tcase_run(
        struct TestCase * TestCase_p,
        unsigned int * pSuccesses,
        unsigned int * pFailures)
{
    while (TestCase_p != NULL)
    {
        TestCase_p->TestsSuccess = 0;
        TestCase_p->TestsFailed  = 0;

        if (TestCase_p->Enabled)
        {
            struct Test *Test_p;

            LOG_INFO("TESTCASE BEGIN %s\n", TestCase_p->Name_p);

            for (Test_p = TestCase_p->TestList_p;
                 Test_p != NULL;
                 Test_p = Test_p->NextTest_p)
            {
                if (Test_p->Enabled)
                {
                    int Count;

                    for (Count = Test_p->Start;
                         Count <= Test_p->NumberOfLoops;
                         Count++)
                    {
                        int Result = 0;

                        LOG_INFO("TEST BEGIN %s:L%d\n", Test_p->Name_p, Count);

                        if (TestCase_p->FixtureStartFunc != NULL)
                        {
                            TestCase_p->FixtureStartFunc();
                        }

                        if (Test_p->TestFunc != NULL)
                        {
                            Result = Test_p->TestFunc(Count);
                        }

                        if (TestCase_p->FixtureEndFunc != NULL)
                        {
                            TestCase_p->FixtureEndFunc();
                        }

                        if (Result == END_TEST_SUCCES)
                        {
                            TestCase_p->TestsSuccess++;
                        }
                        else
                        {
                            if (Result == END_TEST_ABORT)
                            {
                                return END_TEST_ABORT;
                            }

                            /* Only count failed tests, not the skipped or unsupported ones */
                            if (Result == END_TEST_FAIL)
                            {
                                TestCase_p->TestsFailed++;
                            }
                        }

                        LOG_INFO("TEST END %s:L%d\n", Test_p->Name_p, Count);
                    }
                }
            }

            LOG_INFO("TESTCASE_END %s\n", TestCase_p->Name_p);
        }

        *pSuccesses += TestCase_p->TestsSuccess;
        *pFailures  += TestCase_p->TestsFailed;
        TestCase_p = TestCase_p->NextCase_p;
    }

    return END_TEST_SUCCES;
}

int
sfzutf_tsuite_run(
        struct TestSuite * TestSuite_p,
        unsigned int * pSuccesses,
        unsigned int * pFailures)
{
    while(TestSuite_p != NULL)
    {
        if (TestSuite_p->Enabled)
        {
            unsigned int TestCaseSuccesses = 0;
            unsigned int TestCaseFailures = 0;

            LOG_INFO("TESTSUITE BEGIN %s\n", TestSuite_p->Name_p);

            if (sfzutf_tcase_run(TestSuite_p->TestCaseList_p,
                                           &TestCaseSuccesses,
                                           &TestCaseFailures) < 0)
            {
                /* Abort */
                LOG_INFO("TESTSUITE END %s (ABORT)\n", TestSuite_p->Name_p);
                return END_TEST_ABORT;
            }

            LOG_INFO("TESTSUITE END %s (%u/%u)\n", TestSuite_p->Name_p,
                     TestCaseSuccesses, (TestCaseFailures + TestCaseSuccesses));

            *pSuccesses += TestCaseSuccesses;
            *pFailures += TestCaseFailures;
        }

        TestSuite_p = TestSuite_p->NextSuite_p;
    }

    return END_TEST_SUCCES;
}

struct TestSuite *
sfzutf_tsuite_get(
        const char * const SuiteName_p)
{
    struct TestSuite * TestSuite_p = gl_TestSuite;

    if (SuiteName_p != NULL)
    {
        while (TestSuite_p->NextSuite_p != NULL)
        {
            if (!SFZUTF_STREQ(TestSuite_p->Name_p, SuiteName_p))
            {
                break;
            }
            TestSuite_p = TestSuite_p->NextSuite_p;
        }
    }
    return TestSuite_p;
}

static bool
sfzutf_tcase_enable(
        struct TestCase * TestCase_p,
        const char * const TCaseName_p,
        const char * const TestName_p,
        const int * const IterValue_p,
        const SfzUtfEnable_t OrigEnableMode)
{
    SfzUtfEnable_t EnableMode = OrigEnableMode;
    bool EnabledAny = false;
    bool EnabledAnyAtAll = false;
    struct Test *Test_p;

    while (TestCase_p != NULL)
    {
      /* Select TestCase matching the conditions. */
        if (TCaseName_p == NULL ||
            SFZUTF_STREQ(TCaseName_p, TestCase_p->Name_p) ||
            EnableMode == SFZUTF_ENABLE_ALL)
        {
            Test_p = TestCase_p->TestList_p;

            while(Test_p != NULL)
            {
                /* Select  */
                if (TestName_p == NULL ||
                    SFZUTF_STREQ(TestName_p, Test_p->Name_p) ||
                    EnableMode == SFZUTF_ENABLE_ALL)
                {
                    if (IterValue_p != NULL)
                    {
                        if (EnableMode == SFZUTF_ENABLE_AFTER)
                        {
                            /* If IterValue is set and SFZUTF_ENABLE_AFTER
                               mode, trim test range according to IterValue. */
                            if (*IterValue_p < Test_p->Start)
                            {
                                /* Too small iter value, enable whole test. */
                                EnableMode = SFZUTF_ENABLE_ALL;
                            }
                            else if (*IterValue_p < Test_p->NumberOfLoops)
                            {
                                Test_p->Start = *IterValue_p;
                                EnableMode = SFZUTF_ENABLE_ALL;
                            }
                            else
                            {
                                /* Value beyond range => skip test. */
                            }
                        }
                        else if (EnableMode == SFZUTF_ENABLE_SINGLE)
                        {
                            if (*IterValue_p >= Test_p->Start &&
                                *IterValue_p <= Test_p->NumberOfLoops)
                            {
                                /* Enable single iteration. */
                                Test_p->Start = *IterValue_p;
                                Test_p->NumberOfLoops = *IterValue_p;
                            }
                            else
                            {
                                /* Out of range, skip this test */
                                goto skipEnable;
                            }
                        }
                    }

                    if ((EnableMode == SFZUTF_ENABLE_SINGLE) ||
                        (EnableMode == SFZUTF_ENABLE_ALL))
                    {
                        Test_p->Enabled = true;
                        EnabledAny = true;
                    }
                    else if (EnableMode == SFZUTF_ENABLE_AFTER)
                    {
                        if (TestName_p != NULL)
                        {
                            EnableMode = SFZUTF_ENABLE_ALL;
                        }
                    }
                }
skipEnable:
                Test_p = Test_p->NextTest_p;
            }

            /* If enable after mode has been chosen. */
            if ((TestName_p == NULL) &&
                (EnableMode == SFZUTF_ENABLE_AFTER))
            {
                EnableMode = SFZUTF_ENABLE_ALL;
            }
        }

        if (EnabledAny)
        {
            TestCase_p->Enabled = true;
            EnabledAnyAtAll = true;
            if (EnableMode == SFZUTF_ENABLE_SINGLE)
            {
                EnabledAny = false;
            }
        }
        TestCase_p = TestCase_p->NextCase_p;
    }

    return EnabledAnyAtAll;
}

bool
sfzutf_tsuite_enable(
        struct TestSuite * TestSuite_p,
        const char * const SuiteName_p,
        const char * const TCaseName_p,
        const char * const TestName_p,
        const int * const IterValue_p,
        const SfzUtfEnable_t OrigEnableMode)
{
    struct TestSuite * EnableTestSuite_p;
    bool EnabledAny = false;
    SfzUtfEnable_t EnableMode = OrigEnableMode;

    if (TestSuite_p == NULL)
    {
        EnableTestSuite_p = gl_TestSuite;
    }
    else
    {
        EnableTestSuite_p = TestSuite_p;
    }

    /* Select Suite matching the conditions. */
    if ((SuiteName_p == NULL) ||
        SFZUTF_STREQ(SuiteName_p, EnableTestSuite_p->Name_p) ||
        (EnableMode == SFZUTF_ENABLE_ALL))
    {
        EnabledAny = sfzutf_tcase_enable(EnableTestSuite_p->TestCaseList_p,
                                         TCaseName_p,
                                         TestName_p,
                                         IterValue_p,
                                         EnableMode);
        if (EnabledAny)
        {
            EnableTestSuite_p->Enabled = true;
        }

        if ((TestSuite_p == NULL) &&
            (EnableMode == SFZUTF_ENABLE_AFTER))
        {
            EnableMode = SFZUTF_ENABLE_ALL;
        }
    }

    if (EnableTestSuite_p->NextSuite_p)
    {
        EnabledAny |= sfzutf_tsuite_enable(EnableTestSuite_p->NextSuite_p,
                                           SuiteName_p,
                                           TCaseName_p,
                                           TestName_p,
                                           IterValue_p,
                                           EnableMode);
    }

    return EnabledAny;
}

#ifdef VALTEST_USE_FUNCTION
void
sfzutf_tsuite_disable(
        struct TestSuite * TestSuite_p)
{
    while(TestSuite_p != NULL)
    {
        struct TestCase * TestCase_p = TestSuite_p->TestCaseList_p;
        while(TestCase_p != NULL)
        {
            struct Test * Test_p = TestCase_p->TestList_p;
            while(Test_p != NULL)
            {
                Test_p->Enabled = false;
                Test_p = Test_p->NextTest_p;
            }

            TestCase_p->Enabled = false;
            TestCase_p = TestCase_p->NextCase_p;
        }

        TestSuite_p->Enabled = false;
        TestSuite_p = TestSuite_p->NextSuite_p;
    }
}
#endif


/* end of file sfzutf.c */
