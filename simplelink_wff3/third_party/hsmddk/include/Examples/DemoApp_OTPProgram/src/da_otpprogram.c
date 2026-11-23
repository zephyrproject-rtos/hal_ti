/* da_otpprogram.c
 *
 * Demo Application intended as an OTP programming use example.
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

#include "da_otpprogram.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "c_da_otpprogram.h"            // configuration

#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>
#include "api_val.h"

#ifndef DA_OTPPROGRAM_KEYBLOB_FS_REMOVE
#include <stdio.h>      // fopen, fclose, fread
#endif

/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#include <stdlib.h>
#include <inttypes.h>

#define DA_ARG_SEEN_BLOB    0x01
#define DA_ARG_SEEN_POLICY  0x02
#define DA_ARG_SEEN_LABEL   0x04
#define DA_ARG_SEEN_OK      (DA_ARG_SEEN_BLOB|DA_ARG_SEEN_POLICY|DA_ARG_SEEN_LABEL)

#define DA_PREFIX           "DA_OTPPRG: "


/*----------------------------------------------------------------------------
 * Local variables
 */

static char * gl_otpp_Program = NULL;
static bool gl_otpp_Verbose = false;
static int32_t gl_otpp_ArgumentSeen = 0;

static uint8_t * gl_otpp_AD_Label = NULL;
static size_t gl_otpp_AD_LabelSize = 0;
static ValPolicyMask_t gl_otpp_AssetPolicy = 0;
static uint8_t gl_otpp_AssetData[2048+16];
static size_t gl_otpp_AssetDataSize = 0;


/*----------------------------------------------------------------------------
 * DisplayUsage
 *
 * Handle usage display & usage error situations.
 * This function never returns, instead calls exit with given code.
 */
static int32_t
DisplayUsage(
        const char * error)
{
    if (error != NULL)
    {
        // On usage errors, give error message and point user to -help.
        LOG_CRIT(DA_PREFIX "FAILED: %s.\n"
                 DA_PREFIX "Try '%s -help' for usage.\n",
                 error, gl_otpp_Program);
    }
    else
    {
        // Otherwise, build usage instructions.
        LOG_CRIT(DA_PREFIX "Example application for OTP programming.\n\n"
                 "Usage: %s [-help] [-verbose] blob <file> policy <number> label <data> [-exit]\n\n"
                 "Arguments:\n"
                 " -help            Display this information.\n"
                 " -verbose         Enable logging.\n"
                 " -exit            Exit without performing the OTP programming.\n"
#ifdef DA_OTPPROGRAM_KEYBLOB_FS_REMOVE
                 " blob             The key blob data is taken from a global area.\n"
#else
                 " blob <file>      Specifies the file name of the key blob data file.\n"
#endif
                 " policy <value>   Specifies the Asset policy.\n"
                 "                  When <value> starts with:\n"
                 "                    '0x'     a hexadecimal value is assumed\n"
                 "                    '0'      an octadecimal value is assumed\n"
                 "                    '[1..9]' a decimal value is assumed\n"
                 " label <data>     Specifies the Associated Data that must be used.\n",
                 gl_otpp_Program);
    }

    return -1;
}


/*----------------------------------------------------------------------------
 * HandleArguments
 *
 * Handles command line arguments.
 */
static int32_t
HandleArguments(
        int32_t argc,
        char * argv[])
{
    int32_t funcres = 0;
    int32_t i;

    gl_otpp_Program = argv[0];

    i = 1;
    while (i < argc)
    {
        if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-help") == 0))
        {
            (void)DisplayUsage(NULL);
            funcres = 1;
            break;
        }

        if (strcmp(argv[i], "-verbose") == 0)
        {
            gl_otpp_Verbose = true;
            i += 1;
            continue;
        }
        else if (strcmp(argv[i], "-exit") == 0)
        {
            funcres = 1;
            break;
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        if ((i + 1) >= argc)
        {
            funcres = DisplayUsage("Wrong number of arguments");
            break;
        }

        if (!strcmp(argv[i], "blob"))
        {
#ifdef DA_OTPPROGRAM_KEYBLOB_FS_REMOVE
            extern uint8_t _binary_da_otpprogram_keyblob_bin_start;
            extern uint8_t _binary_da_otpprogram_keyblob_bin_end;
            extern uint32_t _binary_da_otpprogram_keyblob_bin_size;

            uint8_t * start = (uint8_t*)&_binary_da_otpprogram_keyblob_bin_start;
            uint8_t * end = (uint8_t*)&_binary_da_otpprogram_keyblob_bin_end;
            uint32_t * size = (uint32_t*)&_binary_da_otpprogram_keyblob_bin_size;
            uint8_t * p = gl_otpp_AssetData;

            gl_otpp_AssetDataSize = (size_t)size;

            // Read key blob
            while(start < end)
            {
                *p = *start;
                start++;
                p++;
            }
#else
            FILE *fp;

            // Read the AES-SIV key from the specified file
            fp = fopen(argv[i + 1], "rb");
            if (fp == NULL)
            {
                funcres = DisplayUsage("Cannot open key blob file");
                break;
            }

            gl_otpp_AssetDataSize = fread(gl_otpp_AssetData, 1, sizeof(gl_otpp_AssetData), fp);
            (void)fclose(fp);
#endif
            if (gl_otpp_AssetDataSize > 0U)
            {
                gl_otpp_ArgumentSeen = (gl_otpp_ArgumentSeen | DA_ARG_SEEN_BLOB);
            }
            else
            {
                funcres = DisplayUsage("Cannot read key blob file");
                break;
            }
        }
        else if (!strcmp(argv[i], "policy"))
        {
            char *EndPtr_p;
            ValPolicyMask_t AssetPolicy = (ValPolicyMask_t)strtoull(argv[i + 1], &EndPtr_p, 0);

            if ((EndPtr_p == argv[i + 1]) || (*EndPtr_p != '\0'))
            {
                funcres = DisplayUsage("Invalid policy value");
                break;
            }
            if (AssetPolicy == 0U)
            {
                funcres = DisplayUsage("Invalid policy, value can not be 0");
                break;
            }
            gl_otpp_AssetPolicy = AssetPolicy;
            gl_otpp_ArgumentSeen = (int32_t)(gl_otpp_ArgumentSeen | DA_ARG_SEEN_POLICY);
        }
        else if (!strcmp(argv[i], "label"))
        {
            // Assign Associated Data (label)
            gl_otpp_AD_Label = (uint8_t *)argv[i + 1];
            gl_otpp_AD_LabelSize = strlen(argv[i + 1]);

            gl_otpp_ArgumentSeen = (int32_t)(gl_otpp_ArgumentSeen | DA_ARG_SEEN_LABEL);
        }
        else
        {
            funcres = DisplayUsage("Invalid option specified.");
            break;
        }
        i += 2;
    }
    return funcres;
}


/*----------------------------------------------------------------------------
 * da_otpprogram_main
 */
int32_t
da_otpprogram_main(
        int32_t argc,
        char * argv[])
{
    int32_t res, MainReturnCode = -1;
    ValStatus_t funcres = -1;

    // Parse command line arguments.
    res = HandleArguments(argc, argv);
    if (res < 0)
    {
        MainReturnCode = -1; // some error
    }
    else if (res > 0)
    {
        MainReturnCode = 0; // exit normally
    }
    else
    {
        if ((gl_otpp_ArgumentSeen & DA_ARG_SEEN_OK) != DA_ARG_SEEN_OK)
        {
            MainReturnCode = DisplayUsage("Not all required arguments specified");
        }
        else
        {
            if (Driver130_Init() < 0)
            {
                LOG_CRIT(DA_PREFIX "FAILED: Driver130 initialization\n");
            }
            else
            {
                if (val_IsAccessSecure())
                {
                    if (gl_otpp_Verbose)
                    {
                        LOG_CRIT(DA_PREFIX "OTP Write information\n");
                        LOG_CRIT("Asset policy : 0x%" PRIx64 "\n", gl_otpp_AssetPolicy);
                        LOG_CRIT("AD Label     : %s\n", gl_otpp_AD_Label);
                        Log_HexDump("OTP BlobData", 0, gl_otpp_AssetData, (uint32_t)gl_otpp_AssetDataSize);
                    }

                    funcres = val_OTPDataWrite(gl_otpp_AssetPolicy,
                                               gl_otpp_AD_Label, gl_otpp_AD_LabelSize,
                                               gl_otpp_AssetData, gl_otpp_AssetDataSize);
                    if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: OTP data write (%d).\n", (int32_t)funcres);
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "PASSED: OTP data written.\n");
                        LOG_CRIT("NOTE: Firmware must be 'reset' to enable the Static Asset for use.\n");
                        MainReturnCode = 0;
                    }
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: No secure hardware connection.\n");
                }

                Driver130_Exit();
            }
        }
    }

    return MainReturnCode;
}


#ifndef DA_OTPPROGRAM_MAIN_REMOVE
/*----------------------------------------------------------------------------
 * main
 *
 * Program entry.
 */
int32_t
main(
        int32_t argc,
        char * argv[])
{
    return da_otpprogram_main(argc, argv);
}
#endif


/* end of file da_otpprogram.c */
