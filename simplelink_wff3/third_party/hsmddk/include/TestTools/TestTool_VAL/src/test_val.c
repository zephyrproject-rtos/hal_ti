/* test_val.c
 *
 * Test Tool for VAL API
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#ifdef TEST_VAL_USERMODE
#include "test_val.h"                   // test_val_main()
#endif


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "c_test_val.h"                 // configuration

// Driver Framework C Run-time abstraction
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

// Logging API
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

// Driver Initialization API
#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>

#include "sfzutf_internal.h"            // test environment
#include "valtest_internal.h"           // test suite setup


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#ifndef TEST_VAL_USERMODE
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Rambus");
MODULE_DESCRIPTION("Test program for the VAL API.");
#endif


/*----------------------------------------------------------------------------
 * Global variables
 */
int32_t g_ValTestVerbose = 0;
int32_t g_ValTestBeginVector = 0;
uint16_t g_ValTestTrngSampleCycles = 3072;
#ifdef TEST_VAL_USERMODE
bool g_ValTestResetAllowed = true;
#else
bool g_ValTestResetAllowed = false;
#endif
bool g_ValTestRepeatVector = false;
bool g_ValTestCleanUp = true;


/*----------------------------------------------------------------------------
 * Local variables
 */
static char * gl_SuiteName_p = NULL;
static char * gl_TCaseName_p = NULL;
static char * gl_TestName_p = NULL;
static int * gl_IterValue_p = NULL;
#ifdef TEST_VAL_USERMODE
static int gl_IterValue = 0;
#endif
static SfzUtfEnable_t gl_EnableMode = SFZUTF_ENABLE_ALL;
static bool gl_DumpTestSuite = false;


/*----------------------------------------------------------------------------
 * test_val_module_init
 *
 * Initializes and runs the tests for the VAL API
 */
static int
test_val_module_init(void)
{
    struct TestSuite * Suite_p = NULL;

    LOG_CRIT(
#ifdef TEST_VAL_USERMODE
             "Starting Test Application (U%d)\n",
#else
             "Starting Test Application (K%d)\n",
#endif
             SFZUTF_GETPID());

    if (build_suite() == 0)
    {
        Suite_p = sfzutf_tsuite_get(NULL);
        if (Suite_p != NULL)
        {
            if (sfzutf_tsuite_enable(Suite_p,
                                     gl_SuiteName_p,
                                     gl_TCaseName_p,
                                     gl_TestName_p,
                                     gl_IterValue_p,
                                     gl_EnableMode))
            {
                if (g_ValTestVerbose || gl_DumpTestSuite)
                {
                    sfzutf_tsuite_dump();
                }

                if (!gl_DumpTestSuite)
                {
                    uint32_t Successes = 0;
                    uint32_t Failures = 0;

                    if (sfzutf_tsuite_run(Suite_p, &Successes, &Failures) < 0)
                    {
                        LOG_CRIT("FAILED(%d): Test execution aborted\n",
                                 SFZUTF_GETPID());
                    }
                    else if (Failures == 0)
                    {
                        LOG_CRIT("PASSED(%d): %u tests\n", SFZUTF_GETPID(), Successes);
                    }
                    else
                    {
                        LOG_CRIT("FAILED(%d): %u of %u tests\n", SFZUTF_GETPID(),
                                 Failures, (Failures + Successes));
                    }
                }
            }
            else
            {
                LOG_CRIT("FAILED(%d): No tests enabled\n", SFZUTF_GETPID());

                if (g_ValTestVerbose)
                {
                    sfzutf_tsuite_dump();
                }
            }
        }
        else
        {
            LOG_CRIT("FAILED(%d): No test suite to test\n", SFZUTF_GETPID());
        }
    }
    else
    {
        LOG_CRIT("FAILED(%d): Test suite setup\n", SFZUTF_GETPID());

        sfzutf_tsuite_dump();
    }

    sfzutf_tsuite_release(NULL);

    return 0;
}


/*----------------------------------------------------------------------------
 * test_val_module_exit
 *
 * Stops the tests.
 */
static void
test_val_module_exit(void)
{
    LOG_CRIT("Stopping Test Application (%d)\n", SFZUTF_GETPID());
}


#ifdef TEST_VAL_USERMODE
/*----------------------------------------------------------------------------
 * ConvertToLower
 */
static void
ConvertToLower(
        char *p)
{
    while(*p != 0)
    {
        if ((*p >= 'A') && (*p <= 'Z'))
        {
            *p = *p | 0x60;
        }
        p++;
    }
}


/*----------------------------------------------------------------------------
 * GetDecimalValue
 */
static int
GetDecimalValue(
        char *p)
{
    int value = 0;

    while (*p != 0)
    {
        if ((*p >= '0') && (*p <= '9'))
        {
            value = (value * 10) + (int)(*p - '0');
        }
        else
        {
            break;
        }
        p++;
    }

    return value;
}


/*----------------------------------------------------------------------------
 * test_val_main
 */
int
test_val_main(
        int argc,
        char **argv)
{
    bool fRunTests = true;

    if (Driver130_Init() < 0)
    {
        LOG_CRIT("TestTool VAL: Driver130_Init() failed\n");
        return -1;
    }

    if (argc > 1)
    {
        int32_t i;

        // Process options
        for (i = 1; i < argc; i++)
        {
            ConvertToLower(argv[i]);
            if (strcmp(argv[i], "-case") == 0)
            {
                i++; // Increment to jump on next argument
                if (i < argc)
                {
                    gl_TCaseName_p = argv[i];
                    LOG_CRIT("Start TestCase '%s'\n", gl_TCaseName_p);
                }
            }
            else if (strcmp(argv[i], "-test") == 0)
            {
                i++; // Increment to jump on next argument
                if (i < argc)
                {
                    gl_TestName_p = argv[i];
                    LOG_CRIT("Start Test '%s'\n", gl_TestName_p);
                }
            }
            else if (strcmp(argv[i], "-iter") == 0)
            {
                i++; // Increment to jump on next argument
                if (i < argc)
                {
                    if ((gl_TCaseName_p != NULL) &&
                        (gl_TestName_p != NULL))
                    {
                        gl_IterValue = GetDecimalValue(argv[i]);
                        gl_IterValue_p = &gl_IterValue;
                        LOG_CRIT("Start at Iterator %d\n", gl_IterValue);
                    }
                }
            }
            else if (strcmp(argv[i], "-mode") == 0)
            {
                i++; // Increment to jump on next argument
                if (i < argc)
                {
                    ConvertToLower(argv[i]);

                    if (strcmp(argv[i], "all") == 0)
                    {
                        gl_EnableMode = SFZUTF_ENABLE_ALL;
                        LOG_CRIT("EnableMode = SFZUTF_ENABLE_ALL\n");
                    }
                    else if (strcmp(argv[i], "single") == 0)
                    {
                        gl_EnableMode = SFZUTF_ENABLE_SINGLE;
                        LOG_CRIT("EnableMode = SFZUTF_ENABLE_SINGLE\n");
                    }
                    else if (strcmp(argv[i], "after") == 0)
                    {
                        gl_EnableMode = SFZUTF_ENABLE_AFTER;
                        LOG_CRIT("EnableMode = SFZUTF_ENABLE_AFTER\n");
                    }
                }
            }
            else if (strcmp(argv[i], "-noreset") == 0)
            {
                // Disable reset
                g_ValTestResetAllowed = false;
            }
            else if (strcmp(argv[i], "-noclean") == 0)
            {
                // Disable clean up
                g_ValTestCleanUp = false;
            }
            else if (strncmp(argv[i], "-vector=", 8) == 0)
            {
                g_ValTestBeginVector = atoi(&argv[i][8]);
                if (g_ValTestBeginVector < 0)
                {
                    g_ValTestBeginVector = 0;
                }
            }
            else if (strcmp(argv[i], "-repeat") == 0)
            {
                // Enable repeat vector
                g_ValTestRepeatVector = true;
            }
            else if (strcmp(argv[i], "-d") == 0)
            {
                // Dump test suite
                gl_DumpTestSuite = true;
            }
            else if (strncmp(argv[i], "-v", 2) == 0)
            {
                // Enable verbose
                if (argv[i][2] == '=')
                {
                    g_ValTestVerbose = atoi(&argv[i][3]);
                    if (g_ValTestVerbose < 0)
                    {
                        // Set a maximum verbose level
                        g_ValTestVerbose = 255;
                    }
                }
                else
                {
                    g_ValTestVerbose = 1;
                }
            }
            else if (strcmp(argv[i], "-initotp") == 0)
            {
                static const uint8_t AssetData[] =
                {
                    0x7E, 0x5D, 0x36, 0x4E, 0x25, 0x7B, 0x27, 0xE4, 0x0B, 0x41, 0x05, 0xE9, 0x5E, 0xC0, 0xDE, 0x99,
                    0xA0, 0xEA, 0x96, 0x0B, 0x72, 0xEB, 0x95, 0x37, 0x60, 0x34, 0x44, 0xA9, 0xFE, 0x62, 0xDB, 0x49,
                    0x89, 0x63, 0x38, 0x2E, 0x24, 0x78, 0xE7, 0x17, 0x81, 0xE8, 0x63, 0x66, 0xF5, 0xE0, 0x67, 0xD8
                };
                static const uint8_t ADLabel[] = "SomeAssociatedDataForProvisioningWithKeyBlob";
                ValStatus_t FuncRes;

                FuncRes = val_OTPDataWrite(EIP130_ASSET_POLICY_NONMODIFIABLE |
                                           (VAL_ASSETNUMBER_HUK << 1) |
                                           EIP130_ASSET_POLICY_NODOMAIN |
                                           EIP130_ASSET_POLICY_PRIVATEDATA |
                                           EIP130_ASSET_POLICY_GDHUK,
                                           ADLabel, sizeof(ADLabel) - 1U,
                                           AssetData, sizeof(AssetData));
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT("FAILED: OTP data write (%d).\n", (int32_t)FuncRes);
                    fRunTests = false;
                }
                else
                {
                    LOG_CRIT("PASSED: OTP data written.\n");
                }
                if (g_ValTestResetAllowed)
                {
                    FuncRes = val_SystemReset();
                    if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                    {
                        LOG_CRIT("FAILED: System reset (%d).\n", (int32_t)FuncRes);
                        fRunTests = false;
                    }
                    else
                    {
                        LOG_CRIT("PASSED: System reset.\n");
                    }
                }
            }
            else if (strncmp(argv[i], "-trng", 5) == 0)
            {
                ValStatus_t FuncRes;

                if (argv[i][5] == '=')
                {
                    g_ValTestTrngSampleCycles = (uint16_t)atoi(&argv[i][6]);
                    if (g_ValTestTrngSampleCycles == 0)
                    {
                        g_ValTestTrngSampleCycles = 2;
                    }
                }

                LOG_CRIT("Configure TRNG: ");
                FuncRes = valtest_DefaultTrngConfig();
                if(val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT("PASSED\n");
                }
                else
                {
                    LOG_CRIT(" FAILED\n");
                    fRunTests = false;
                }
            }
            else if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-help") == 0))
            {
                LOG_CRIT("Syntax     : %s [<option> ...]\n", argv[0]);
                LOG_CRIT("Description: Execute the VAL API test application.\n");
                LOG_CRIT("             With the options you can specify the test application behavior.\n");
                LOG_CRIT("Options    : -help              Display this information\n");
                LOG_CRIT("             -noclean           No test cleanup\n");
                LOG_CRIT("             -noreset           No reset during tests is allowed\n");
                LOG_CRIT("             -initotp           Initialize the OTP with a default COID and HUK\n");
                LOG_CRIT("             -trng[=<Samples>]  Configure/Start the TRNG (default=3072)\n");
                LOG_CRIT("             -case <Test Case>  Define the test case to run\n");
                LOG_CRIT("             -test <Test>       Define the test to run\n");
                LOG_CRIT("             -iter <Iteration>  Define the iteration of the test/test case to run\n");
                LOG_CRIT("             -mode <mode>       Define the test enable mode:\n");
                LOG_CRIT("                                all     All tests including tests after the specified test\n");
                LOG_CRIT("                                single  Only the specified test\n");
                LOG_CRIT("                                after   Including all tests after the specified test\n");
                LOG_CRIT("             -vector=<Index>    Vector index number [0...]\n");
                LOG_CRIT("             -repeat            Repeat a vector till error or program is terminated\n");
                LOG_CRIT("             -d                 Dump test suite only\n");
                LOG_CRIT("             -v[=<level>]       Set verbose level\n");
                fRunTests = false;
            }
            else
            {
                LOG_CRIT("Illegal option: %s\n", argv[i]);
            }
        }
    }

    if (fRunTests)
    {
        (void)test_val_module_init();
        test_val_module_exit();
    }

    Driver130_Exit();

    return 0;
}


#ifndef TEST_VAL_MAIN_REMOVE
/*----------------------------------------------------------------------------
 * main
 */
int
main(
        int argc,
        char **argv)
{
    return test_val_main(argc, argv);
}
#endif // !TEST_VAL_MAIN_REMOVE
#else // TEST_VAL_USERMODE
module_init(test_val_module_init);
module_exit(test_val_module_exit);
#endif // !TEST_VAL_USERMODE


/* end of file test_val.c */

