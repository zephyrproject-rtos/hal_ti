/* regress.c
 *
 * Regression system for MicroBlaze FreeRTOS
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


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Demo application VAL entry point
#include "da_val.h"                 // da_val_main

// Demo application VAL specials entry point
#include "da_val_specials.h"        // da_val_specials_main

// Demo application Secure Debug entry point
#include "da_securedebug.h"         // da_securedebug_main()

// Demo application OTP Key Blob entry point
#include "da_otpkeyblob.h"          // da_otpkeyblob_main()

// Demo application OTP Program entry point
#include "da_otpprogram.h"          // da_otpprogram_main()

// Test Tool VAL entry point
#include "test_val.h"               // test_val_main()

// Test Tool VAL entry point
#include "test_psa.h"               // test_psa_main()

// FreeRTOS API
#include <FreeRTOS.h>
#include "task.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

typedef int (*Test_Function_t)(int argc, char ** argv);

typedef struct
{
    Test_Function_t func;
    int argc;
    char * argv[5];
} Test_Func_Params_t;


/*----------------------------------------------------------------------------
 * Local variables
 */

static Test_Func_Params_t TestFuncs[] =
{
#ifndef SKIP_PROGRAMS
    // func               argc  argv
    { da_otpkeyblob_main,    3, {"da_otpkeyblob_main",   "-help",
                                                         "-exit", 0, 0     } },
    { da_otpprogram_main,    3, {"da_otpprogram_main",   "-help",
                                                         "-exit", 0, 0     } },
    { da_securedebug_main,   3, {"da_securedebug_main",  "-help",
                                                         "-exit", 0        } },
    { da_val_specials_main,  5, {"da_val_specials_main", "-help",
                                                         "-hwversion",
                                                         "-hwoptions",
                                                         "-hwmodulestatus" } },
    { da_val_main,           2, {"da_val_main",          "-help", 0, 0, 0  } },
    { da_val_main,           2, {"da_val_main",          "-initotp",
                                                         0, 0, 0           } },
    { test_val_main,         1, {"test_val_main",        0, 0, 0, 0        } }
    { test_psa_main,         1, {"test_psa_main",        0, 0, 0, 0        } }
#else
    { da_val_main,           2, {"da_val_main",          0, 0, 0, 0        } },
#endif
};


/*----------------------------------------------------------------------------
 * TestTask
 *
 * Test task function.
 */
static void
TestTask(
        void * arg_p)
{
    unsigned int i, Count = sizeof(TestFuncs) / sizeof(TestFuncs[0]);

    for (i = 0; i < Count; i++)
        if (TestFuncs[i].func)
            TestFuncs[i].func(TestFuncs[i].argc, TestFuncs[i].argv);

    while(1);
}


/*----------------------------------------------------------------------------
 * main
 */
int
main(
        int argc,
        char **argv)
{
    TaskHandle_t TestTaskHandle;

    xTaskCreate(TestTask,
                (const char *)"Regression task",
                0x40000 / sizeof(uint32_t),
                NULL,
                tskIDLE_PRIORITY,
                &TestTaskHandle);

    // Start the tasks and timer running
    vTaskStartScheduler();

    return 0;
}


/* end of file regress.c */

