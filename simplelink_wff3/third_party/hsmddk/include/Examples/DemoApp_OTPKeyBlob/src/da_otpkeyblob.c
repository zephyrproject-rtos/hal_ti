/* da_otpkeyblob.c
 *
 * Demo Application intended as an OTP key blob generation example.
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

#include "da_otpkeyblob.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "c_da_otpkeyblob.h"            // configuration

#include "aessiv.h"
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>
#include "api_val.h"

#ifndef DA_OTPKEYBLOB_FS_REMOVE
#include <stdio.h>      // fopen, fclose, fread
#endif


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#include <stdlib.h>

#define DA_ARG_SEEN_KEY     0x01
#define DA_ARG_SEEN_LABEL   0x02
#define DA_ARG_SEEN_POLICY  0x04
#define DA_ARG_SEEN_DATA    0x08
#define DA_ARG_SEEN_OUTPUT  0x10

#ifndef DA_OTPKEYBLOB_FS_REMOVE
#define DA_ARG_SEEN_OK      (DA_ARG_SEEN_KEY    | DA_ARG_SEEN_LABEL |  \
                             DA_ARG_SEEN_POLICY | DA_ARG_SEEN_DATA  |  \
                             DA_ARG_SEEN_OUTPUT)
#else
#define DA_ARG_SEEN_OK      (DA_ARG_SEEN_KEY    | DA_ARG_SEEN_LABEL |  \
                             DA_ARG_SEEN_POLICY | DA_ARG_SEEN_DATA)
#endif

#define DA_PREFIX       "DA_OTPKB: "


/*----------------------------------------------------------------------------
 * Local variables
 */
static char * gl_Program = NULL;
static bool gl_Verbose = false;

static uint8_t gl_AES_SIV_Key[2*(256/8)];
static uint8_t gl_KeyBlob_Label[256];
static uint8_t * gl_AD_Label = NULL;
static size_t gl_AD_LabelSize = 0;
static uint8_t gl_AssetPolicy[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8_t gl_AssetData[1024];
static size_t gl_AssetDataSize = 0;
static uint8_t gl_Output[1024+(128/8)];
static char * gl_OutputFile = NULL;
static AESSIV_Context gl_AESSIV_Context;

static int32_t gl_ArgumentSeen = 0;


/*----------------------------------------------------------------------------
 * HandleArguments
 *
 * Handle usage display & usage error situations.
 * This function never returns, instead calls exit with given code.
 */
static int32_t
DisplayUsage(const char * error)
{
    if (error != NULL)
    {
        // On usage errors, give error message and point user to -help.
        LOG_CRIT(DA_PREFIX "FAILED: %s.\n"
                 DA_PREFIX "Try '%s -help' for usage.\n",
                 error, gl_Program);
    }
    else
    {
        // Otherwise, build usage instructions.
        LOG_CRIT(DA_PREFIX "Example application for OTP Key Blob generation.\n\n"
                 "Usage: %s [-help] [-verbose] key [file] label <data> policy <number> data [file] output [file]\n\n"
                 "Arguments:\n"
                 " -help            Display this information.\n"
                 " -verbose         Enable process logging.\n"
                 " -exit            Exit without performing OTP Key Blob generation.\n"
#ifdef DA_OTPKEYBLOB_FS_REMOVE
                 " key              Indentifies that the AES-SIV key must be taken from the global environment.\n"
#else
                 " key <file>       Specifies the file name of the binary file in which the AES-SIV key is given.\n"
#endif
                 " label <data>     Specifies the Associated Data that must be used.\n"
                 " policy <value>   Specifies the Asset policy. (See FW Reference Manual for details)\n"
                 "                  When <value> starts with:\n"
                 "                    '0x'     a hexadecimal value is assumed\n"
                 "                    '0'      an octa decimal value is assumed\n"
                 "                    '[1..9]' a decimal value is assumed\n"
#ifdef DA_OTPKEYBLOB_FS_REMOVE
                 " data             Indentifies that the data must be taken from the global environment.\n"
                 " output           The key blob data is stored in the global environment.\n",
#else
                 " data <file>      Specifies the file name of the binary file in which the Asset data is given.\n"
                 " output <file>    Specifies the file name of the file to which the key blob data must be written.\n",
#endif
                 gl_Program);
    }

    return -1;
}


/*----------------------------------------------------------------------------
 * HandleArguments
 *
 * Handles command line arguments.
 */
static int32_t
HandleArguments(int32_t argc,
                char * argv[])
{
    int32_t funcres = 0;
    int32_t i;

    gl_Program = argv[0];

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
            gl_Verbose = true;
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

        if (strcmp(argv[i], "key") == 0)
        {
            size_t rv;
#ifdef DA_OTPKEYBLOB_FS_REMOVE
            extern uint8_t _binary_da_otpkeyblob_keyblob_bin_start;
            extern uint8_t _binary_da_otpkeyblob_keyblob_bin_end;
            extern uint32_t _binary_da_otpkeyblob_keyblob_bin_size;

            uint8_t * start = (uint8_t*)&_binary_da_otpkeyblob_keyblob_bin_start;
            uint8_t * end = (uint8_t*)&_binary_da_otpkeyblob_keyblob_bin_end;
            uint32_t * size = (uint32_t*)&_binary_da_otpkeyblob_keyblob_bin_size;
            uint8_t * p = gl_AES_SIV_Key;

            rv = (size_t)size;

            // Read key blob
            while(start < end)
            {
                *p = *start;
                start++;
                p++;
            }
#else
            FILE * fp;

            // Read the AES-SIV key from the specified file
            fp = fopen(argv[i + 1], "rb");
            if (fp == NULL)
            {
                funcres = DisplayUsage("Cannot open key file");
                break;
            }

            rv = fread(gl_AES_SIV_Key, 1, sizeof(gl_AES_SIV_Key), fp);
            (void)fclose(fp);
#endif
            if (rv != sizeof(gl_AES_SIV_Key))
            {
                funcres = DisplayUsage("Cannot read key file or key has not the expected size");
                break;
            }

            gl_ArgumentSeen = (int32_t)(gl_ArgumentSeen | DA_ARG_SEEN_KEY);
        }
        else if (strcmp(argv[i], "label") == 0)
        {
            // Assign Associated Data (label)
            gl_AD_Label = (uint8_t *)argv[i + 1];
            gl_AD_LabelSize = strlen(argv[i + 1]);

            gl_ArgumentSeen |= DA_ARG_SEEN_LABEL;
        }
        else if (strcmp(argv[i], "policy") == 0)
        {
            char *EndPtr_p;
            int32_t j;
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

            for(j = 0; j < 8; j++)
            {
                gl_AssetPolicy[j] = (uint8_t)(AssetPolicy >> (j * 8));
            }
            gl_ArgumentSeen = (gl_ArgumentSeen | DA_ARG_SEEN_POLICY);
        }
        else if (strcmp(argv[i], "data") == 0)
        {
#ifdef DA_OTPKEYBLOB_FS_REMOVE
            extern uint8_t _binary_da_otpkeyblob_asset_bin_start;
            extern uint8_t _binary_da_otpkeyblob_asset_bin_end;
            extern uint32_t _binary_da_otpkeyblob_asset_bin_size;

            uint8_t * start = (uint8_t*)&_binary_da_otpkeyblob_asset_bin_start;
            uint8_t * end = (uint8_t*)&_binary_da_otpkeyblob_asset_bin_end;
            uint32_t * size = (uint32_t*)&_binary_da_otpkeyblob_asset_bin_size;
            uint8_t * p = gl_AssetData;

            gl_AssetDataSize = (size_t)size;

            // Read key blob
            while(start < end)
            {
                *p = *start;
                start++;
                p++;
            }
#else
            FILE * fp;

            // Read the Asset data from the specified file
            fp = fopen(argv[i + 1], "rb");
            if (fp == NULL)
            {
                funcres = DisplayUsage("Cannot open data file");
                break;
            }

            gl_AssetDataSize = fread(gl_AssetData, 1, sizeof(gl_AssetData), fp);
            (void)fclose(fp);
#endif

            if (gl_AssetDataSize > 0U)
            {
                gl_ArgumentSeen |= DA_ARG_SEEN_DATA;
            }
            else
            {
                funcres = DisplayUsage("Cannot read data file");
                break;
            }

        }
        else if (strcmp(argv[i], "output") == 0)
        {
            // Assign output file name
            gl_OutputFile = argv[i + 1];

            gl_ArgumentSeen |= DA_ARG_SEEN_OUTPUT;
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
 * GenerateKeyBlob
 */
static int32_t
GenerateKeyBlob(void)
{
    int32_t funcres = 0;
    int32_t FuncReturnCode = -1;
    size_t OutputSize = sizeof(gl_Output);

    FuncReturnCode = AESSIV_Init(&gl_AESSIV_Context, gl_Verbose);
    if (FuncReturnCode != 0)
    {
        funcres = DisplayUsage("KeyBlob setup failed (Init)");
    }
    else
    {
        FuncReturnCode = AESSIV_SetKey(&gl_AESSIV_Context,
                                       gl_AES_SIV_Key, sizeof(gl_AES_SIV_Key));
        if (FuncReturnCode != 0)
        {
            funcres = DisplayUsage("KeyBlob setup failed (Key)");
        }
        else
        {
            (void)memcpy(gl_KeyBlob_Label, gl_AD_Label, gl_AD_LabelSize);
            (void)memcpy(&gl_KeyBlob_Label[gl_AD_LabelSize], gl_AssetPolicy, 8);
            FuncReturnCode = AESSIV_SetAD(&gl_AESSIV_Context,
                                          gl_KeyBlob_Label, (gl_AD_LabelSize + 8U));
            if (FuncReturnCode != 0)
            {
                funcres = DisplayUsage("KeyBlob setup failed (AD)");
            }
            else
            {
                FuncReturnCode = AESSIV_Encrypt(&gl_AESSIV_Context,
                                                gl_AssetData, gl_AssetDataSize,
                                                gl_Output, &OutputSize);
                if (FuncReturnCode != 0)
                {
                    funcres = DisplayUsage("KeyBlob generation failed");
                }
                // If file system is not supported then the output data can be stored
                // anywhere in memory
#ifndef DA_OTPKEYBLOB_FS_REMOVE
                else
                {
                    FILE *fp;

                    fp = fopen(gl_OutputFile, "wb");
                    if (fp == NULL)
                    {
                        funcres = DisplayUsage("Cannot open output file");
                    }
                    else
                    {
                        FuncReturnCode = (int32_t)fwrite(gl_Output, OutputSize, 1, fp);
                        (void)fclose(fp);
                        if (FuncReturnCode != 1)
                        {
                            funcres = DisplayUsage("Cannot write output file");
                        }
                    }
                }
#endif
            }
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * da_otpkeyblob_main
 */
int32_t
da_otpkeyblob_main(int32_t argc,
                   char * argv[])
{
    int32_t rc;

    // Parse command line arguments.
    rc = HandleArguments(argc, argv);
    if (rc == 0)
    {
        if (gl_ArgumentSeen != DA_ARG_SEEN_OK)
        {
            rc = DisplayUsage("Not all required arguments specified");
        }
        else
        {
            if (Driver130_Init() < 0)
            {
                LOG_CRIT(DA_PREFIX "FAILED: Driver130 initialization\n");
                rc = -1;
            }
            else
            {
                rc = GenerateKeyBlob();

                Driver130_Exit();
            }
        }
    }
    else
    {
        if (rc > 0)
        {
            rc = 0;                     // exit normally
        }
    }

    return rc;
}


#ifndef DA_OTPKEYBLOB_MAIN_REMOVE
/*----------------------------------------------------------------------------
 * main
 *
 * Program entry.
 */
int32_t
main(int32_t argc,
     char * argv[])
{
    return da_otpkeyblob_main(argc, argv);
}
#endif


/* end of file da_otpkeyblob.c */
