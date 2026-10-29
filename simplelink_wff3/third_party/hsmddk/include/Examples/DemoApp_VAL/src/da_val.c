/* da_val.c
 *
 * Demo Application for the VAL API
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

#ifdef DA_VAL_USERMODE
#include "da_val.h"
#endif


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "c_da_val.h"                   // configuration
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>
#include "api_val.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifdef DA_VAL_USERMODE
#include <stdlib.h>
#else // DA_VAL_USERMODE
#define EXPORT_SYMTAB
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>               // printk
#include <linux/slab.h>
#include <asm/delay.h>                  // udelay
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Rambus");
MODULE_DESCRIPTION("Demo program for the VAL API.");
#endif // !DA_VAL_USERMODE

#define DA_PREFIX   "DA_VAL: "

#define DATA_IN_BYTE_COUNT_SIZE   40
#define DATA_OUT_BYTE_COUNT_SIZE  100

/*----------------------------------------------------------------------------
 * da_val_module_init
 */
static int32_t
da_val_module_init(void)
{
    int32_t rc = -1;
    const uint32_t DataInByteCount = DATA_IN_BYTE_COUNT_SIZE;
    ValSize_t DataOutByteCount = DATA_OUT_BYTE_COUNT_SIZE;
    ValStatus_t FuncRes;
    int32_t maxOTPAssetNumber = 0;
    uint8_t Mode = 0;
    uint8_t i;
    uint8_t DataIn_p[DATA_IN_BYTE_COUNT_SIZE];
    ValOctetsOut_t DataOut_p[DATA_OUT_BYTE_COUNT_SIZE];

    LOG_CRIT(DA_PREFIX "Starting Demo Application\n");
    // Get version information to check token functionality
    LOG_CRIT(DA_PREFIX "Version test: Start\n");

    (void)memset(DataOut_p, 0, DataOutByteCount);
    FuncRes = val_SystemGetVersion(DataOut_p, &DataOutByteCount);
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        LOG_CRIT(DA_PREFIX "Version: %s\n", DataOut_p);
        LOG_CRIT(DA_PREFIX "Version test: PASSED\n");
    }
    else
    {
        LOG_CRIT(DA_PREFIX "Version retrieving failed (%d)\n", FuncRes);
        LOG_CRIT(DA_PREFIX "Version test: FAILED\n");
    }

    if(val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        // Get state information
        LOG_CRIT(DA_PREFIX "State test: Start\n");
        {
            uint8_t OtpErrorCode = 0;
            uint16_t OtpErrorLocation = 0;
            uint8_t ErrorTest = 0;
            uint8_t CryptoOfficer = 0;
            uint8_t HostID = 0;
            uint8_t NonSecure = 0;
            uint32_t Identity = 0;

            FuncRes = val_SystemGetState(&OtpErrorCode, &OtpErrorLocation,
                                         &Mode, &ErrorTest, &CryptoOfficer,
                                         &HostID, &NonSecure, &Identity);
            if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
            {
                LOG_CRIT(DA_PREFIX "  State:\n");
                {
                    const char * ptr;

                    switch (OtpErrorCode)
                    {
                    case 0:
                        ptr = "No anomaly";
                        break;
                    case 1:
                        ptr = "Empty";
                        break;
                    case 2:
                        ptr = "Unsupported size";
                        break;
                    case 3:
                        ptr = "FAT Error";
                        break;
                    case 8:
                        ptr = "OTP is zeroized";
                        break;
                    default:
                        ptr = "Reserved???";
                        break;
                    }
                    LOG_CRIT(DA_PREFIX "    OTP State     : %u - %s\n", OtpErrorCode, ptr);
                }
                switch (Mode)
                {
                case 0:
                    LOG_CRIT(DA_PREFIX "    Mode          : Active Mode\n");
                    break;
                case 3:
                    LOG_CRIT(DA_PREFIX "    Mode          : Fatal Error - Login Failed\n");
                    break;
                case 4:
                    LOG_CRIT(DA_PREFIX "    Mode          : Fatal Error - Self-test (0x%02X)\n",
                             ErrorTest);
                    break;
                case 5:
                    LOG_CRIT(DA_PREFIX "    Mode          : Fatal Error - DMA\n");
                    break;
                case 6:
                    LOG_CRIT(DA_PREFIX "    Mode          : Fatal Error - NRBG or DRBG\n");
                    break;
                case 7:
                    LOG_CRIT(DA_PREFIX "    Mode          : Fatal Error - Key generation\n");
                    break;
                case 15:
                    LOG_CRIT(DA_PREFIX "    Mode          : Active Mode - Login successful\n");
                    break;
                default:
                    LOG_CRIT(DA_PREFIX "    Mode          : %u (0x%02X)\n", Mode, ErrorTest);
                    break;
                }

                if (CryptoOfficer != 0U)
                {
                    LOG_CRIT(DA_PREFIX "    CryptoOfficer : Available\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "    CryptoOfficer : NOT Available\n");
                }

                LOG_CRIT(DA_PREFIX "    HostID        : %u\n", HostID);

                if (NonSecure != 0U)
                {
                    LOG_CRIT(DA_PREFIX "    Secure        : No\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "    Secure        : Yes\n");
                }

                LOG_CRIT(DA_PREFIX "    Identity      : 0x%X\n", Identity);
                LOG_CRIT(DA_PREFIX "State test: PASSED\n");
            }
            else
            {
                LOG_CRIT(DA_PREFIX "State retrieving failed (%d)\n", FuncRes);
                LOG_CRIT(DA_PREFIX "State test: FAILED\n");
            }
        }

        if(val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
        {
            // Scan OTP objects
            LOG_CRIT(DA_PREFIX "OTP Scan: Start\n");
            maxOTPAssetNumber = (int32_t)VAL_ASSET_NUMBER_MAX;
            for (i = 0; i < (uint8_t)maxOTPAssetNumber; i++)
            {
                ValAssetId_t AssetId = VAL_ASSETID_INVALID;

                FuncRes = val_AssetSearch(i, &AssetId, &DataOutByteCount);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    const char * pType = "Private Static Asset";
                    const uint8_t * pData = NULL;

                    FuncRes = val_PublicDataRead(AssetId, DataOut_p, DataOutByteCount);
                    if ((val_CheckFunctionResult(FuncRes) == VAL_SUCCESS) ||
                        (val_CheckFunctionResult(FuncRes) == VAL_BUFFER_TOO_SMALL))
                    {
                        pType = "Public Data object";
                        if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                        {
                            pData = DataOut_p;
                        }
                    }
                    else
                    {
                        FuncRes = val_MonotonicCounterRead(AssetId, DataOut_p, DataOutByteCount);
                        if ((val_CheckFunctionResult(FuncRes) == VAL_SUCCESS) ||
                            (val_CheckFunctionResult(FuncRes) == VAL_BUFFER_TOO_SMALL))
                        {
                            pType = "Monotonic Counter";
                            if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                            {
                                pData = DataOut_p;
                            }
                        }
                    }
                    LOG_CRIT(DA_PREFIX "  Found Asset number %d (%s), size %d bytes\n",
                             (int32_t)i, pType, (int32_t)DataOutByteCount);
                    if (pData != NULL)
                    {
                        Log_HexDump(DA_PREFIX "    Data", 0, pData, (uint32_t)DataOutByteCount);
                    }
                }
                else if (val_CheckFunctionResult(FuncRes) == VAL_INTERNAL_ERROR)
                {
                    LOG_CRIT(DA_PREFIX "OTP Scan: FAILED\n");
                    break;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
            if (i == (uint8_t)maxOTPAssetNumber)
            {
                LOG_CRIT(DA_PREFIX "OTP Scan: PASSED\n");
            }

            if ((Mode == 0U) || (Mode == 15U))
            {
                // Perform a NOP operation to check the DMA functionality
                LOG_CRIT(DA_PREFIX "NOP test: Start\n");

                for(i = 0; i < DataInByteCount; i++)
                {
                    DataIn_p[i] = i;
                }

                FuncRes = val_NOP(DataIn_p, DataOut_p, DataInByteCount);
                if(val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    bool is_passed = true;

                    for(i = 0; i < DataInByteCount; i++)
                    {
                        if (DataOut_p[i] != i)
                        {
                            LOG_CRIT(DA_PREFIX "Data check failed\n");
                            LOG_CRIT(DA_PREFIX "NOP test FAILED\n");
                            is_passed = false;
                        }
                    }

                    if (is_passed)
                    {
                        LOG_CRIT(DA_PREFIX "NOP test: PASSED\n");
                        rc = 0; // success
                    }
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "Operation failed (%d)\n", FuncRes);
                    LOG_CRIT(DA_PREFIX "NOP test: FAILED\n");
                }
            }
            else
            {
                LOG_CRIT(DA_PREFIX "NOP test: Skipped, only works in active mode\n");
            }
        }
    }

    return rc;
}


/*----------------------------------------------------------------------------
 * da_val_module_exit
 */
static void
da_val_module_exit(void)
{
    LOG_CRIT(DA_PREFIX "Stopping Demo Application\n");
}


#ifdef DA_VAL_USERMODE
/*----------------------------------------------------------------------------
 * da_val_main
 */
int32_t
da_val_main(
        int32_t argc,
        const char **argv)
{
    int32_t i;
    int32_t status = 0;
    bool fHelp = false;
    ValStatus_t FuncRes;

    if (Driver130_Init() < 0)
    {
        LOG_CRIT(DA_PREFIX "Demo Application: Driver130_Init() failed\n");
        status = -1;
    }
    else
    {
        // Process option arguments
        for (i = 1; argc > i; i++)
        {
            if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-help") == 0))
            {
                LOG_CRIT(DA_PREFIX "Example application for functionality provided by the VAL API.\n\n");
                LOG_CRIT("Syntax     : %s [<option> ...]\n", argv[0]);
                LOG_CRIT("Description: Execute the Demo Application. Note that you can\n");
                LOG_CRIT("             use the options to perform an operation to set\n");
                LOG_CRIT("             the hardware in a certain state.\n");
                LOG_CRIT("Options    : -help              Display this information\n");
                LOG_CRIT("             -initotp           Initialize the OTP with a default COID and HUK\n");
                LOG_CRIT("             -reset             Reset firmware (hardware)\n");
                LOG_CRIT("             -trng[=<Samples>]  Configure/Start the TRNG (default=3072)\n");

                fHelp = true;
                continue;
            }

            if (strcmp(argv[i], "-reset") == 0)
            {
                // Reset system to have known starting state
                LOG_CRIT(DA_PREFIX "Reset system\n");
                FuncRes = val_SystemReset();
                if(val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "Reset system PASSED\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "Reset system FAILED\n");
                }
                fHelp = true;
            }
            else if (strncmp(argv[i], "-trng", 5) == 0)
            {
                uint16_t SampleCycles = 3072;

                if (argv[i][5] == '=')
                {
                    SampleCycles = (uint16_t)atoi(&argv[i][6]);
                    if (SampleCycles == 0U)
                    {
                        SampleCycles = 2;
                    }
                }

                /* IntegrationItem:
                 * The TRNG configuration needs to be adapted to meet the customer
                 * specific FROs timing/behavior. */
                LOG_CRIT(DA_PREFIX "Configure TRNG (%u)\n", SampleCycles);
                FuncRes = val_TrngConfig(0, SampleCycles, 1, 8, 0, 31, 56, 325, true);
                if(val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "Configure TRNG PASSED\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "Configure TRNG FAILED\n");
                    fHelp = true;
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

                LOG_CRIT(DA_PREFIX "Program HUK and Crypto Officer ID\n");
                FuncRes = val_OTPDataWrite(EIP130_ASSET_POLICY_NONMODIFIABLE |
                                           (VAL_ASSETNUMBER_HUK << 1U) |
                                           EIP130_ASSET_POLICY_NODOMAIN |
                                           EIP130_ASSET_POLICY_PRIVATEDATA |
                                           EIP130_ASSET_POLICY_GDHUK,
                                           ADLabel, sizeof(ADLabel) - 1U,
                                           AssetData, sizeof(AssetData));
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: OTP data write (%d).\n", (int32_t)FuncRes);
                    fHelp = true;
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "PASSED: OTP data written.\n");

                    LOG_CRIT(DA_PREFIX "Reset system\n");
                    FuncRes = val_SystemReset();
                    if(FuncRes == VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "Reset system PASSED\n");
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "Reset system FAILED\n");
                    }
                }
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }

        if (fHelp == false)
        {
            (void)da_val_module_init();
            (void)da_val_module_exit();
        }

        Driver130_Exit();
    }

    return status;
}


#ifndef DA_VAL_MAIN_REMOVE
/*----------------------------------------------------------------------------
 * main
 */
int32_t
main(
        int32_t argc,
        const char ** argv)
{
    return da_val_main(argc, argv);
}
#endif // !DA_VAL_MAIN_REMOVE
#else // DA_VAL_USERMODE
module_init(da_val_module_init);
module_exit(da_val_module_exit);
#endif // !DA_VAL_USERMODE


/* end of file da_val.c */


