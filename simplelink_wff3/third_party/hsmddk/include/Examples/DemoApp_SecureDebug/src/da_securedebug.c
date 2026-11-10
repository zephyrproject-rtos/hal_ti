/* da_securedebug.c
 *
 * Demo Application intended as an Secure Debug use example.
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

#ifdef DA_SECUREDEBUG_USERMODE
#include "da_securedebug.h"                  // da_securedebug_main()
#endif


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "c_da_securedebug.h"                // Configuration

#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>
#include "api_val.h"
#include "api_val_aunlock.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifdef DA_SECUREDEBUG_USERMODE
#include <stdlib.h>
#else
#define EXPORT_SYMTAB
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>       // printk
#include <linux/slab.h>
#include <asm/delay.h>          // udelay
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Rambus");
MODULE_DESCRIPTION("Demo program for the Secure Debug functionality.");
#endif

#define DA_PREFIX       "DA_SD: "


/*----------------------------------------------------------------------------
 * Local variables
 */
/* The assetnumber of the public AuthKey located in GPFW/OTP */
static uint16_t gl_PublicKey_AssetNumber = 0x81;    // Secure Debug Authentication key 1

#ifdef DA_SECUREDEBUG_ECDSA256
static const ValSize_t gl_KeyModulus_BitSize = 256;
static const ValSymAlgo_t gl_HashAlgo = VAL_SYM_ALGO_HASH_SHA256;
static uint8_t gl_SignatureBufferR[(4U * ((256U + 31U) / 32U))];
static uint8_t gl_SignatureBufferS[(4U * ((256U + 31U) / 32U))];

static uint8_t gl_EcdsaPrvKey[] =
{
    0x6F, 0x83, 0x87, 0x4D, 0x5A, 0x63, 0x86, 0xCD, 0x75, 0xF7, 0xC0, 0xC7, 0xC6, 0x67, 0x79, 0x6E,
    0x26, 0x90, 0x91, 0x74, 0x81, 0x4F, 0x4E, 0x08, 0xE0, 0x71, 0x67, 0x49, 0xB4, 0x71, 0xE0, 0x96
};
#else
static const ValSize_t gl_KeyModulus_BitSize = 521;
static const ValSymAlgo_t gl_HashAlgo = VAL_SYM_ALGO_HASH_SHA512;
static uint8_t gl_SignatureBufferR[(4U * ((521U + 31U) / 32U))];
static uint8_t gl_SignatureBufferS[(4U * ((521U + 31U) / 32U))];

static uint8_t gl_EcdsaPrvKey[] =
{
    0x05, 0x21
};
#endif

#ifdef DA_SECUREDEBUG_USERMODE
static const char * gl_sd_Program = "da_securedebug_u";
#endif


#ifdef DA_SECUREDEBUG_USERMODE
/*----------------------------------------------------------------------------
 * local_SecureDebugDisplayUsage
 *
 * Handle usage display & usage error situations.
 * This function never returns, instead calls exit with given code.
 */
static void
local_SecureDebugDisplayUsage(const char * error)
{
    if (error != NULL)
    {
        // On usage errors, give error message and point user to -help.
        LOG_CRIT(DA_PREFIX "FAILED: %s\n"
                 DA_PREFIX "Try '%s -help' for usage.\n",
                 error, gl_sd_Program);
    }
    else
    {
        LOG_CRIT(DA_PREFIX "Example application for the Secure Debug functionality.\n\n"
                 DA_PREFIX " Usage: %s [flags]\n\n"
                 DA_PREFIX " -help               Display this information.\n"
                 DA_PREFIX " -initotp            Initialize the OTP with a default COID and HUK.\n"
                 DA_PREFIX " -trng[=<Samples>]   Configure/Start the TRNG (default=3072).\n"
                 DA_PREFIX " -exit               Exit without running the Secure Debug functionality.\n",
                 gl_sd_Program);
    }
}


/*----------------------------------------------------------------------------
 * local_SecureDebugHandleOption
 *
 * Handles command line options.
 */
static int32_t
local_SecureDebugHandleOption(const char * str)
{
    int32_t status = 0;

    if ((strcmp(str, "--help") == 0) || (strcmp(str, "-help") == 0))
    {
        local_SecureDebugDisplayUsage(NULL);
        status = 1;
    }
    else
    {
        if (strcmp(str, "-initotp") == 0)
        {
            static const uint8_t AssetData[] =
            {
                0x7E, 0x5D, 0x36, 0x4E, 0x25, 0x7B, 0x27, 0xE4, 0x0B, 0x41, 0x05, 0xE9, 0x5E, 0xC0, 0xDE, 0x99,
                0xA0, 0xEA, 0x96, 0x0B, 0x72, 0xEB, 0x95, 0x37, 0x60, 0x34, 0x44, 0xA9, 0xFE, 0x62, 0xDB, 0x49,
                0x89, 0x63, 0x38, 0x2E, 0x24, 0x78, 0xE7, 0x17, 0x81, 0xE8, 0x63, 0x66, 0xF5, 0xE0, 0x67, 0xD8
            };
            static const uint8_t ADLabel[] = "SomeAssociatedDataForProvisioningWithKeyBlob";
            ValStatus_t FuncRes;

            LOG_CRIT(DA_PREFIX "Program HUK and Crypto Officer ID\n");
            FuncRes = val_OTPDataWrite(EIP130_ASSET_POLICY_NONMODIFIABLE |
                                       (VAL_ASSETNUMBER_HUK << 1) |
                                       EIP130_ASSET_POLICY_NODOMAIN |
                                       EIP130_ASSET_POLICY_PRIVATEDATA |
                                       EIP130_ASSET_POLICY_GDHUK,
                                       ADLabel, sizeof(ADLabel) - 1U,
                                       AssetData, sizeof(AssetData));
            if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
            {
                LOG_CRIT(DA_PREFIX "FAILED: OTP data write (%d).\n", (int32_t)FuncRes);
            }
            else
            {
                LOG_CRIT(DA_PREFIX "PASSED: OTP data written.\n");

                LOG_CRIT(DA_PREFIX "Reset system\n");
                FuncRes = val_SystemReset();
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "Reset system PASSED\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "Reset system FAILED\n");
                }
            }
            status = val_CheckFunctionResult(FuncRes);
        }
        else if (strncmp(str, "-trng", 5) == 0)
        {
            ValStatus_t FuncRes;
            uint16_t SampleCycles = 3072;

            if (str[5] == '=')
            {
                SampleCycles = (uint16_t)atoi(&str[6]);
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
            if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
            {
                LOG_CRIT(DA_PREFIX "Configure TRNG FAILED\n");
            }
            else
            {
                LOG_CRIT(DA_PREFIX "Configure TRNG PASSED\n");
            }
            status = val_CheckFunctionResult(FuncRes);
        }
        else if (strcmp(str, "-exit") == 0)
        {
            status = 1;
        }
        else
        {
            local_SecureDebugDisplayUsage("Invalid option specified.");
            status = -2;
        }
    }

    return status;
}
#endif


/*----------------------------------------------------------------------------
 * local_SecureDebugAuthenticationService (ECDSA)
 */
static int32_t
local_SecureDebugAuthenticationService(const uint8_t * NonceB_p,
                                       uint8_t * NonceA_p,
                                       ValAsymSign_t * Signature_p)
{
    int32_t FuncReturnCode = -1;
    uint8_t Nonce[32];
    ValStatus_t funcres;
    ValAsymKey_t PrivateKey;
    ValAssetId_t CurveParamAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAsymBigInt_t prvkeyData = { gl_EcdsaPrvKey, sizeof(gl_EcdsaPrvKey) };

    // Get the NonceA part
    funcres = val_RandomData(16, NonceA_p);
    if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
    {
        LOG_CRIT(DA_PREFIX "FAILED: AuthenticationService NonceA generation.\n");
    }
    else
    {
        // Combine NonceA and NonceB
        (void)memcpy(&Nonce[0],  NonceA_p, 16);
        (void)memcpy(&Nonce[16], NonceB_p, 16);

        // creation of curve params
        funcres = val_AsymEccInstallCurve(VAL_ECC_FAMILY_NIST_P,
#ifdef DA_SECUREDEBUG_ECDSA256
                                          256,
#else
                                          521,
#endif
                                          &CurveParamAssetId);
        if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
        {
            LOG_CRIT(DA_PREFIX "FAILED: EC Curve Parameters load\n");
        }
        else
        {
            // Allocate and load Privatekey
            funcres = val_AsymEcdsaAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P,
                                                        gl_KeyModulus_BitSize, gl_HashAlgo,
                                                        false, true, &PrivateKeyAssetId);
            if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
            {
                LOG_CRIT(DA_PREFIX "FAILED: AuthenticationService Key allocation\n");
            }
            else
            {
                funcres = val_AsymEccLoadPrivateKeyAssetPlaintext(&prvkeyData,
                                                                  VAL_ECC_FAMILY_NIST_P,
                                                                  gl_KeyModulus_BitSize,
                                                                  PrivateKeyAssetId,
                                                                  VAL_ASSETID_INVALID,
                                                                  NULL, 0, NULL, NULL);
                if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: AuthenticationService Key load\n");
                }
                else
                {
                    funcres = val_AsymInitKey(PrivateKeyAssetId, CurveParamAssetId,
                                              gl_KeyModulus_BitSize, gl_HashAlgo,
                                              &PrivateKey);
                    if (funcres != VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: AuthenticationService Key initialization\n");
                    }
                    else
                    {
                        PrivateKey.DomainAssetId = CurveParamAssetId;
                        PrivateKey.KeyAssetId = PrivateKeyAssetId;
#ifdef DA_SECUREDEBUG_ECDSA256
                        Signature_p->r.Data_p = gl_SignatureBufferR;
                        Signature_p->s.Data_p = gl_SignatureBufferS;
                        Signature_p->r.ByteDataSize = sizeof(gl_SignatureBufferR);
                        Signature_p->s.ByteDataSize = sizeof(gl_SignatureBufferS);
#else
                        Signature_p->r.Data_p = &gl_SignatureBufferR[2];
                        Signature_p->s.Data_p = &gl_SignatureBufferS[2];
                        Signature_p->r.ByteDataSize = sizeof(gl_SignatureBufferR) - 2U;
                        Signature_p->s.ByteDataSize = sizeof(gl_SignatureBufferS) - 2U;
#endif
                        funcres = val_AsymEcdsaSign(&PrivateKey, Signature_p, Nonce, 32, NULL, false);
                        if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
                        {
                            LOG_CRIT(DA_PREFIX "FAILED: AuthenticationService Signing of Nonce (A+B)\n");
                        }
                        else
                        {
#ifndef DA_SECUREDEBUG_ECDSA256
                            /* Adjust value and size for Auhtenticated Unlock Verify signature layout */
                            gl_SignatureBufferR[0] = 0;
                            gl_SignatureBufferR[1] = 0;
                            gl_SignatureBufferS[0] = 0;
                            gl_SignatureBufferS[1] = 0;
                            Signature_p->r.Data_p = gl_SignatureBufferR;
                            Signature_p->s.Data_p = gl_SignatureBufferS;
                            Signature_p->r.ByteDataSize = sizeof(gl_SignatureBufferR);
                            Signature_p->s.ByteDataSize = sizeof(gl_SignatureBufferS);
#endif
                            FuncReturnCode = 0;
                        }
                    }
                }
            }
        }
    }

    if (PrivateKeyAssetId != VAL_ASSETID_INVALID)
    {
        (void)val_AssetFree(PrivateKeyAssetId);
    }

    return FuncReturnCode;
}


/*----------------------------------------------------------------------------
 * da_securedebug_module_init
 */
static int32_t
da_securedebug_module_init(void)
{
    int32_t FuncReturnCode = -1;
    uint8_t NonceA[16];
    uint8_t NonceB[16];
    ValSize_t NonceLength = 16;
    ValStatus_t funcres;
    ValAssetId_t AuthStateASId = VAL_ASSETID_INVALID;
    ValAsymSign_t Signature;

    // Start the Authenticated Unlock operation
    // Note: The called function includes the find asset and create asset
    //       operations as shown in figure 4 of the Secure Debug Application
    //       Note.
    funcres = val_AuthenticatedUnlockStart(gl_PublicKey_AssetNumber,
                                           &AuthStateASId,
                                           NonceB, &NonceLength);
    if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
    {
        if (val_CheckFunctionResult(funcres) == VAL_UNSUPPORTED)
        {
            LOG_CRIT(DA_PREFIX "Authenticated Unlock/Secure Debug NOT SUPPORTED.\n");
            FuncReturnCode = 0;
        }
        else
        {
            LOG_CRIT(DA_PREFIX "FAILED: val_AuthenticatedUnlockStart(%d)=%d\n",
                     gl_PublicKey_AssetNumber, funcres);
        }
    }
    else
    {
        LOG_CRIT(DA_PREFIX "PASSED: Authenticated Unlock Start.\n");

        // Perform the Authentication Service actions
        if (local_SecureDebugAuthenticationService(NonceB, NonceA, &Signature) == 0)
        {
            LOG_CRIT(DA_PREFIX "PASSED: Authenticated Unlock signature generation.\n");

            // Perform the Authenticated Unlock verify operation, which on success
            // grants use of the val_SecureDebug().
            funcres = val_AuthenticatedUnlockVerify(AuthStateASId, &Signature, NonceA, 16);
            if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
            {
                if (val_CheckFunctionResult(funcres) == VAL_VERIFY_ERROR)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: Authenticated Unlock Verify.\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AuthenticatedUnlockVerify()=%d\n",
                             funcres);
                }
            }
            else
            {
                LOG_CRIT(DA_PREFIX "PASSED: Authenticated Unlock Verify.\n");

                // Enable Secure Debug
                // - Asserts the Secure Debug port bits that are defined in the AuthInfo of
                //   the AuthKey.
                funcres = val_SecureDebug(AuthStateASId, true);
                if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_SecureDebug(true)=%d\n", funcres);
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "PASSED: Secure Debug assert.\n");

                    // Disable Secure Debug
                    // - De-asserts the Secure Debug port bits that are defined in the AuthInfo
                    //   of the AuthKey.
                    funcres = val_SecureDebug(AuthStateASId, false);
                    if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: val_SecureDebug(false)=%d\n", funcres);
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "PASSED: Secure Debug de-assert.\n");
                        FuncReturnCode = 0;
                    }
                }
            }
        }
    }

    // Remove the Asset that holds the Authenticated Unlock state
    if (AuthStateASId != VAL_ASSETID_INVALID)
    {
        funcres = val_AuthenticatedUnlockRelease(AuthStateASId);
        if (val_CheckFunctionResult(funcres) != VAL_SUCCESS)
        {
            LOG_CRIT(DA_PREFIX "FAILED: val_AuthenticatedUnlockRelease()=%d\n",
                     funcres);
        }
    }

    return FuncReturnCode;
}


/*----------------------------------------------------------------------------
 * da_securedebug_module_exit
 */
static void
da_securedebug_module_exit(void)
{
    LOG_CRIT(DA_PREFIX "Stopped\n");
}


#ifdef DA_SECUREDEBUG_USERMODE
/*----------------------------------------------------------------------------
 * da_securedebug_main
 *
 * Handle command line arguments if any, call produce random.
 */
int32_t
da_securedebug_main(int32_t argc,
                    const char * argv[])
{
    int32_t i;
    int32_t MainReturnCode = 0;

    if (Driver130_Init() < 0)
    {
        LOG_CRIT(DA_PREFIX "FAILED: Driver130 initialization\n");
        MainReturnCode = -1;
    }
    else
    {
        // Parse command line arguments.
        gl_sd_Program = argv[0];
        for (i = 1; i < argc; i++)
        {
            // Check if argument is option
            MainReturnCode = local_SecureDebugHandleOption(argv[i]);
            if (MainReturnCode != 0)
            {
                break;
            }
        }

        if (MainReturnCode == 0)
        {
            MainReturnCode = da_securedebug_module_init();
            da_securedebug_module_exit();
        }
        else if (MainReturnCode > 0)
        {
            MainReturnCode = 0;
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        Driver130_Exit();
    }

    return MainReturnCode;
}


#ifndef DA_SECUREDEBUG_MAIN_REMOVE
/*----------------------------------------------------------------------------
 * main
 */
int32_t
main(int32_t argc,
     const char * argv[])
{
    return da_securedebug_main(argc, argv);
}
#endif // !DA_SECUREDEBUG_MAIN_REMOVE
#else // DA_SECUREDEBUG_USERMODE
module_init(da_securedebug_module_init);
module_exit(da_securedebug_module_exit);
#endif // !DA_SECUREDEBUG_USERMODE


/* end of file da_securedebug.c */
