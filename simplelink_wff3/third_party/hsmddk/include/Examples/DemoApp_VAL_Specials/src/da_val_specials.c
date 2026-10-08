/* da_val_specials.c
 *
 * Demo Application for the VAL API Specials that cannot be tested via the
 * test program
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

#include "da_val_specials.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "c_da_val_specials.h"          // configuration

#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>
#include "api_val.h"

#include <stdlib.h>                     // malloc, free, strtoull


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define DA_PREFIX   "DA_VAL_SPEC: "


/*----------------------------------------------------------------------------
 * Local variables
 */
static uint32_t gl_DefaultCOID = 0x4F5A3647U;
static uint16_t gl_SampleCycles = 3072U;

// Hardware Unique Key (HUK)
static const uint8_t gl_HUK_OTPKeyBlob[] =
{
    0x7E, 0x5D, 0x36, 0x4E, 0x25, 0x7B, 0x27, 0xE4, 0x0B, 0x41, 0x05, 0xE9, 0x5E, 0xC0, 0xDE, 0x99,
    0xA0, 0xEA, 0x96, 0x0B, 0x72, 0xEB, 0x95, 0x37, 0x60, 0x34, 0x44, 0xA9, 0xFE, 0x62, 0xDB, 0x49,
    0x89, 0x63, 0x38, 0x2E, 0x24, 0x78, 0xE7, 0x17, 0x81, 0xE8, 0x63, 0x66, 0xF5, 0xE0, 0x67, 0xD8
};

static const uint8_t gl_ADLabelKeyblob[] = "SomeAssociatedDataForProvisioningWithKeyBlob";
static const uint8_t gl_ADLabelDerive[] = "Just some associated data for key derivation generation";

#if defined(DA_VAL_SPECIAL_SF_MILENAGE)
static uint8_t gl_DataBlobBuffer[(128 / 8) + 1024];
static ValSize_t gl_DataBlobSize;
#endif  /* DA_VAL_SPECIAL_SF_MILENAGE */

#ifdef DA_VAL_SPECIAL_SF_MILENAGE
// Milenage Related information
static const uint8_t gl_Milenage_AssetNumber = 6;

/* Test Set1 */
static const uint8_t gl_Milenage_TS1_OTPBlob[] =
{
    /* Keyblob without nodomain policy
    * 0xfa, 0xb5, 0x95, 0x7f, 0x74, 0x4c, 0x71, 0xa8, 0x8b, 0xf2, 0xf7, 0x73, 0x9d, 0x3c, 0xde, 0x36,
    * 0x63, 0x81, 0xeb, 0x75, 0x08, 0xdb, 0xcb, 0xcf, 0x6e, 0x1f, 0xeb, 0xee, 0xee, 0xf5, 0x38, 0xb1,
    * 0x3f, 0x0d, 0x69, 0xc0, 0x24, 0xe4, 0x86, 0xc6, 0x5e, 0x3c, 0x55, 0xa0, 0x25, 0xac, 0x92, 0x45
    */
    0x5a, 0xf7, 0xc3, 0x4a, 0x93, 0x3c, 0x0a, 0xc1, 0xc1, 0x51, 0x17, 0xbe, 0xc4, 0x70, 0x83, 0xef,
    0xd7, 0xff, 0x76, 0xac, 0x58, 0x49, 0x72, 0x03, 0xb5, 0x81, 0x46, 0x0f, 0x08, 0xb4, 0xf4, 0x37,
    0x26, 0x59, 0x0b, 0xa4, 0x42, 0xb7, 0xc2, 0x3d, 0x88, 0xdb, 0xfd, 0x3b, 0x66, 0x2d, 0x21, 0x80
};
static const uint8_t gl_Milenage_TS1_RAND[] =
{
    0x23, 0x55, 0x3C, 0xBE, 0x96, 0x37, 0xA8, 0x9D, 0x21, 0x8A, 0xE6, 0x4D, 0xAE, 0x47, 0xBF, 0x35
};
static const uint8_t gl_Milenage_TS1_SQN[] =
{
    0xFF, 0x9B, 0xB4, 0xD0, 0xB6, 0x07
};
static const uint8_t gl_Milenage_TS1_AMF[] =
{
    0xB9, 0xB9
};
static const uint8_t gl_Milenage_TS1_f1[] =
{
    0x4A, 0x9F, 0xFA, 0xC3, 0x54, 0xDF, 0xAF, 0xB3
};
static const uint8_t gl_Milenage_TS1_f1star[] =
{
    0x01, 0xCF, 0xAF, 0x9E, 0xC4, 0xE8, 0x71, 0xE9
};
static const uint8_t gl_Milenage_TS1_f2[] =
{
    0xA5, 0x42, 0x11, 0xD5, 0xE3, 0xBA, 0x50, 0xBF
};
static const uint8_t gl_Milenage_TS1_f3[] =
{
    0xB4, 0x0B, 0xA9, 0xA3, 0xC5, 0x8B, 0x2A, 0x05, 0xBB, 0xF0, 0xD9, 0x87, 0xB2, 0x1B, 0xF8, 0xCB
};
static const uint8_t gl_Milenage_TS1_f4[] =
{
    0xF7, 0x69, 0xBC, 0xD7, 0x51, 0x04, 0x46, 0x04, 0x12, 0x76, 0x72, 0x71, 0x1C, 0x6D, 0x34, 0x41
};
static const uint8_t gl_Milenage_TS1_f5[] =
{
    0xAA, 0x68, 0x9C, 0x64, 0x83, 0x70
};
static const uint8_t gl_Milenage_TS1_f5star[] =
{
    0x45, 0x1E, 0x8B, 0xEC, 0xA4, 0x3B
};
#endif /* DA_VAL_SPECIAL_SF_MILENAGE */

#ifdef DA_VAL_SPECIAL_FIRMWARE_LOAD
static const uint8_t gl_SFWBPKD_keyblob[] =
{
    0xEA, 0xCA, 0x25, 0x3C, 0xC2, 0x2F, 0x44, 0x32, 0x0A, 0x3B, 0xA8, 0x70, 0xB1, 0xE7, 0x74, 0x80,
    0xAF, 0x77, 0x0F, 0x61, 0x81, 0x62, 0xA4, 0x69, 0x69, 0x5C, 0x23, 0xAB, 0x45, 0x01, 0x82, 0x3C,
    0xF2, 0x00, 0x13, 0x9B, 0x7D, 0x08, 0x84, 0x70, 0xB2, 0x03, 0x71, 0x33, 0x88, 0x72, 0x68, 0x07
};
static const uint8_t gl_SFWBCR_keyblob[] =
{
    0x11, 0x4D, 0x09, 0xE5, 0x23, 0xF7, 0x4A, 0x8F, 0x2E, 0xA3, 0x03, 0x02, 0x90, 0x27, 0xFB, 0xF0,
    0x68, 0xD6, 0xCA, 0x2B, 0x74, 0xEF, 0xE3, 0x91, 0xBB, 0x1C, 0xFB, 0x1C, 0xD5, 0xEE, 0xA6, 0xCD,
    0x3B, 0x7D, 0x10, 0x03, 0x9A, 0xBB, 0xF7, 0xE4, 0x14, 0xF5, 0xDD, 0xC7, 0x75, 0xA5, 0xF7, 0xFE
};
static const uint8_t gl_SFWBVER_keyblob[] =
{
    0x95, 0xc2, 0x45, 0x92, 0x44, 0x08, 0x9f, 0x95, 0x2e, 0x40, 0x8c, 0x59, 0x92, 0xe5, 0xd9, 0x05,
    0x09, 0xbb, 0x44, 0x1a
};
#endif /* DA_VAL_SPECIAL_FIRMWARE_LOAD */


/*----------------------------------------------------------------------------
 * DoReset
 *
 * This function performs a firmware based reset.
 */
static ValStatus_t
DoReset(void)
{
    ValStatus_t FuncRes;

    FuncRes = val_SystemReset();
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        LOG_CRIT(DA_PREFIX "PASSED: Reset system.\n");
    }
    else
    {
        LOG_CRIT(DA_PREFIX "FAILED: val_SystemReset()=%d.\n", (int32_t)FuncRes);
    }
    return FuncRes;
}


/*----------------------------------------------------------------------------
 * WriteOTP
 *
 * This function writes an item (KeyBlob) to OTP.
 */
static ValStatus_t
WriteOTP(
        ValPolicyMask_t AssetPolicy,
        ValOctetsIn_t * const AssociatedData_p,
        const ValSize_t AssociatedDataSize,
        ValOctetsIn_t * const KeyBlob_p,
        const ValSize_t KeyBlobSize)
{
    ValStatus_t FuncRes;

    FuncRes = val_OTPDataWrite(AssetPolicy,
                               AssociatedData_p, AssociatedDataSize,
                               KeyBlob_p, KeyBlobSize);
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        LOG_CRIT(DA_PREFIX "PASSED: OTP data written.\n");
        LOG_CRIT(DA_PREFIX "Reset system to enable the information stored in OTP\n");
        FuncRes = DoReset();
    }
    else
    {
        LOG_CRIT(DA_PREFIX "FAILED: val_OTPDataWrite()=%d.\n", (int32_t)FuncRes);
    }
    return FuncRes;
}


/*----------------------------------------------------------------------------
 * WriteRandomHuk
 *
 * This function writes a randomly generated HUK and default COID to OTP.
 */
static ValStatus_t
WriteRandomHuk(
        const bool f128bit,
        const char * SampleCyclesInfo,
        const bool fAria)
{
    ValStatus_t FuncRes;
    ValSize_t KeyBlobSize = 0;
    uint8_t OTPKeyBlobBuffer[(128+256)/8];
    uint8_t * KeyBlob_p = NULL;

    if (SampleCyclesInfo[0] == '=')
    {
        gl_SampleCycles = (uint16_t)atoi(&SampleCyclesInfo[1]);
        if (gl_SampleCycles == 0U)
        {
            gl_SampleCycles = 2U;
        }
    }

    if (!f128bit)
    {
        KeyBlob_p = OTPKeyBlobBuffer;
        KeyBlobSize = sizeof(OTPKeyBlobBuffer);
        (void)memset(OTPKeyBlobBuffer, 0, KeyBlobSize);
    }

#ifdef DA_VAL_SPECIAL_ARIA_DRBG
    if (fAria)
    {
        FuncRes = val_ProvisionRandomRootKeyARIA(gl_DefaultCOID, f128bit,
                                                 0, gl_SampleCycles, 1, 0, 8,
                                                 gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                                                 KeyBlob_p, &KeyBlobSize);
    }
    else
#endif /* DA_VAL_SPECIAL_ARIA_DRBG */
    {
        FuncRes = val_ProvisionRandomRootKey(gl_DefaultCOID, f128bit,
                                             0, gl_SampleCycles, 1, 0, 8,
                                             gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                                             KeyBlob_p, &KeyBlobSize);
    }
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        LOG_CRIT(DA_PREFIX "PASSED: Random HUK written.\n");

        if (KeyBlob_p != NULL)
        {
            Log_HexDump("OTPKeyBlob(HUK)", 0, KeyBlob_p, (uint32_t)KeyBlobSize);
        }

        LOG_CRIT(DA_PREFIX "Reset system to enable the information stored in OTP\n");
        FuncRes = DoReset();
    }
    else
    {
        LOG_CRIT(DA_PREFIX "FAILED: val_ProvisionRandomRootKey%s()=%d.\n",
                 fAria ? "Aria" : "", (int32_t)FuncRes);
    }
    return FuncRes;
}


/*----------------------------------------------------------------------------
 * ConfigureTrng
 *
 * This function configures and actives the TRNG and AES based DRBG.
 */
static ValStatus_t
ConfigureTrng(void)
{
    ValStatus_t FuncRes;

    /* IntegrationItem:
     * The TRNG configuration needs to be adapted to meet the customer
     * specific FROs timing/behavior. */
    LOG_CRIT(DA_PREFIX "Configure TRNG (AES-DRBG) (%u)\n", gl_SampleCycles);
    FuncRes = val_TrngConfig(0, gl_SampleCycles, 1, 8, 0, 31, 56, 325, true);
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        LOG_CRIT(DA_PREFIX "PASSED: Configure TRNG\n");
    }
    else
    {
        LOG_CRIT(DA_PREFIX "FAILED: val_TrngConfig()=%d.\n", (int32_t)FuncRes);
    }
    return FuncRes;
}


#ifdef DA_VAL_SPECIAL_ARIA_DRBG
/*----------------------------------------------------------------------------
 * ConfigureAriaDrbg
 *
 * This function configures and actives the TRNG and ARIA based DRBG.
 */
static ValStatus_t
ConfigureAriaDrbg(void)
{
    ValStatus_t FuncRes;

    /* IntegrationItem:
     * The TRNG configuration needs to be adapted to meet the customer
     * specific FROs timing/behavior. */
    LOG_CRIT(DA_PREFIX "Configure ARIA-DRBG (%u)\n", gl_SampleCycles);
    FuncRes = val_TrngConfigAriaDRBG(0, gl_SampleCycles, 1, 8, 0, 31, 56, 325, true);
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        LOG_CRIT(DA_PREFIX "PASSED: Configure ARIA-DRBG\n");
    }
    else
    {
        LOG_CRIT(DA_PREFIX "FAILED: val_TrngConfigAriaDRBG()=%d.\n", (int32_t)FuncRes);
    }
    return FuncRes;
}
#endif /* DA_VAL_SPECIAL_ARIA_DRBG */


#ifdef DA_VAL_SPECIAL_DRBG_FORCESEED
/*----------------------------------------------------------------------------
 * ConfigureDrbgForceSeed
 *
 * This function configures and actives an AES based DRBG. Note that the use
 * of the FROs is disabled, so random data generation is stopped after
 * generating 64K bytes of random data.
 */
static ValStatus_t
ConfigureDrbgForceSeed(void)
{
    ValStatus_t FuncRes;

    LOG_CRIT(DA_PREFIX "Configure DRBG force seed\n");
    FuncRes = val_DRBGForceSeed(0, gl_HUK_OTPKeyBlob);
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        uint8_t RandNum[128];

        FuncRes = val_RandomData(128, RandNum);
        if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
        {
            LOG_CRIT(DA_PREFIX "PASSED: Configure DRBG force seed\n");
        }
        else
        {
            LOG_CRIT(DA_PREFIX "FAILED: val_RandomData()=%d.\n", (int32_t)FuncRes);
        }
    }
    else
    {
        LOG_CRIT(DA_PREFIX "FAILED: val_DRBGForceSeed()=%d.\n", (int32_t)FuncRes);
    }
    return FuncRes;
}
#endif /* DA_VAL_SPECIAL_DRBG_FORCESEED */


/*----------------------------------------------------------------------------
 * GetTrngRawData
 *
 * This function read raw data from TRNG.
 */
static ValStatus_t
GetTrngRawData(uint16_t aBlocks)
{
    uint8_t * pBuffer;
    ValSize_t Size;
    ValStatus_t FuncRes;

    Size = (ValSize_t)(aBlocks * 256);
    pBuffer = malloc(Size);
    if (pBuffer == 0)
    {
        LOG_CRIT(DA_PREFIX "ERROR: Memory allocation (%d)\n", (int32_t)Size);
        FuncRes = VAL_NO_MEMORY;
    }
    else
    {
        LOG_CRIT(DA_PREFIX "Read TRNG Raw Data\n");
        FuncRes = val_TrngRawData(Size, pBuffer);
        if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
        {
            Log_HexDump(DA_PREFIX "PASSED: Raw Data:", 0, pBuffer, (uint32_t)Size);
        }
        else
        {
            LOG_CRIT(DA_PREFIX "FAILED: val_TrngRawData()=%d\n", FuncRes);
        }
        free(pBuffer);
    }
    return FuncRes;
}


/*----------------------------------------------------------------------------
 * GetVersion
 *
 * This function configures and actives the TRNG.
 */
static ValStatus_t
GetVersion(void)
{
    ValOctetsOut_t DataOut_p[100];
    ValSize_t DataOutByteCount = 100;
    ValStatus_t FuncRes;

    LOG_CRIT(DA_PREFIX "Get version information as a sanity check\n");
    FuncRes = val_SystemGetVersion(DataOut_p, &DataOutByteCount);
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        LOG_CRIT(DA_PREFIX "PASSED: Version: %s\n", DataOut_p);
    }
    else
    {
        LOG_CRIT(DA_PREFIX "FAILED: val_SystemGetVersion()=%d\n", FuncRes);
    }
    return FuncRes;
}


#ifdef DA_VAL_SPECIAL_SF_MILENAGE
/*----------------------------------------------------------------------------
 * MilenageXor
 *
 * This function performs a XOR of two values and returns the result.
 */
static void
MilenageXor(
        uint8_t * aValueResult,
        const uint8_t * aValue1,
        const uint8_t * aValue2,
        const uint32_t Size)
{
    uint32_t i;

    for (i = 0; i < Size; i++)
    {
        aValueResult[i] = aValue1[i] ^ aValue2[i];
    }
}

/*----------------------------------------------------------------------------
 * MilenageAutnCheck
 *
 * This function performs the Milenage AUTN verification related operations.
 */
static ValStatus_t
MilenageAutnCheck(void)
{
    uint8_t AUTN[sizeof(gl_Milenage_TS1_SQN) + sizeof(gl_Milenage_TS1_AMF) + sizeof(gl_Milenage_TS1_f1)];
    uint8_t RES[sizeof(gl_Milenage_TS1_f2)];
    uint8_t CK[sizeof(gl_Milenage_TS1_f3)];
    uint8_t IK[sizeof(gl_Milenage_TS1_f4)];
    ValStatus_t FuncRes = VAL_SUCCESS;
    ValAssetId_t SqnAdminAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t KekAssetId = VAL_ASSETID_INVALID;

    LOG_CRIT(DA_PREFIX "Milenage AUTN verification check\n");

    // Format AUTN
    MilenageXor(AUTN,
                gl_Milenage_TS1_SQN, gl_Milenage_TS1_f5,
                sizeof(gl_Milenage_TS1_SQN));
    (void)memcpy(&AUTN[sizeof(gl_Milenage_TS1_SQN)],
                 gl_Milenage_TS1_AMF, sizeof(gl_Milenage_TS1_AMF));
    (void)memcpy(&AUTN[sizeof(gl_Milenage_TS1_SQN) + sizeof(gl_Milenage_TS1_AMF)],
                 gl_Milenage_TS1_f1, sizeof(gl_Milenage_TS1_f1));

    {
        uint8_t SQN[sizeof(gl_Milenage_TS1_SQN)];
        uint8_t AMF[sizeof(gl_Milenage_TS1_AMF)];

        FuncRes = val_SFMilenageAutnVerification(gl_Milenage_AssetNumber,
                                                 gl_Milenage_TS1_RAND, AUTN,
                                                 RES, CK, IK, SQN, AMF);
        if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
        {
            if ((memcmp(RES, gl_Milenage_TS1_f2, sizeof(gl_Milenage_TS1_f2)) == 0) &&
                (memcmp(CK, gl_Milenage_TS1_f3, sizeof(gl_Milenage_TS1_f3)) == 0) &&
                (memcmp(IK, gl_Milenage_TS1_f4, sizeof(gl_Milenage_TS1_f4)) == 0) &&
                (memcmp(SQN, gl_Milenage_TS1_SQN, sizeof(gl_Milenage_TS1_SQN)) == 0) &&
                (memcmp(AMF, gl_Milenage_TS1_AMF, sizeof(gl_Milenage_TS1_AMF)) == 0))
            {
                LOG_CRIT(DA_PREFIX "PASSED: val_SFMilenageAutnVerification()=OK\n");
            }
            else
            {
                LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageAutnVerification()=Bad Result\n");
                FuncRes = VAL_DATA_OVERRUN_ERROR;
            }
        }
        else
        {
            LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageAutsGeneration()=%d\n", (int32_t)FuncRes);
        }
    }

    if(val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        FuncRes = val_SFMilenageSqnAdminCreate(gl_Milenage_AssetNumber, true,
                                               &SqnAdminAssetId);
        if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
        {
            uint8_t AUTS[sizeof(gl_Milenage_TS1_SQN) + sizeof(gl_Milenage_TS1_f1star)];
            uint32_t EMMCause = 0;

            LOG_CRIT(DA_PREFIX "PASSED: val_SFMilenageSqnAdminCreate()=OK\n");

            FuncRes = val_SFMilenageAutnVerificationSqn(SqnAdminAssetId,
                                                        gl_Milenage_TS1_RAND, AUTN,
                                                        &EMMCause, RES, CK, IK, AUTS);
            if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
            {
                int32_t result1 = memcmp(RES, gl_Milenage_TS1_f2, sizeof(gl_Milenage_TS1_f2));
                int32_t result2 = memcmp(CK, gl_Milenage_TS1_f3, sizeof(gl_Milenage_TS1_f3));
                int32_t result3 = memcmp(IK, gl_Milenage_TS1_f4, sizeof(gl_Milenage_TS1_f4));
                if ((result1 == 0) && (result2 == 0) && (result3 == 0))
                {
                    LOG_CRIT(DA_PREFIX "PASSED: val_SFMilenageAutnVerificationSqn()=OK\n");

                    FuncRes = val_SFMilenageAutnVerificationSqn(SqnAdminAssetId,
                                                                gl_Milenage_TS1_RAND, AUTN,
                                                                &EMMCause, RES, CK, IK, AUTS);
                    if((val_CheckFunctionResult(FuncRes) == VAL_VERIFY_ERROR) && (EMMCause == 21))
                    {
                        ValPolicyMask_t AssetPolicy;

                        LOG_CRIT(DA_PREFIX "PASSED: val_SFMilenageAutnVerificationSqn(EMMCause)=OK\n");

                        // Create Trusted Key Encryption Key (KEK) Asset
                        AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP | EIP130_ASSET_POLICY_SCAWAESSIV | EIP130_ASSET_POLICY_SCDIRENCDEC;
                        if (!val_IsAccessSecure())
                        {
                            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
                        }
                        FuncRes = val_AssetAlloc(AssetPolicy, (512 / 8),
                                                 VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                                 &KekAssetId);
                        if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                        {

                            FuncRes = val_AssetLoadDerive(KekAssetId, val_AssetGetRootKey(),
                                                          gl_ADLabelDerive, (sizeof(gl_ADLabelDerive) - 1U),
                                                          false, false, NULL, 0, NULL, 0, 0);
                            if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                            {
                                gl_DataBlobSize = 300;
                                FuncRes = val_SFMilenageSqnAdminExport(SqnAdminAssetId, KekAssetId,
                                                                       gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                                                                       gl_DataBlobBuffer, &gl_DataBlobSize);
                                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                                {
                                    if (gl_DataBlobSize == ((128U / 8U) + 200U))
                                    {
                                        LOG_CRIT(DA_PREFIX "PASSED: val_SFMilenageSqnAdminExport()=OK\n");
                                    }
                                    else
                                    {
                                        LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageSqnAdminExport() wrong blob size (%d != %d)\n",
                                                 (int32_t)gl_DataBlobSize, ((128/8) + 200));
                                    }
                                    FuncRes = val_SFMilenageSqnAdminReset(SqnAdminAssetId);
                                    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                                    {
                                        LOG_CRIT(DA_PREFIX "PASSED: val_SFMilenageSqnAdminReset()=OK\n");
                                    }
                                    else
                                    {
                                        LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageSqnAdminReset()=%d\n", (int32_t)FuncRes);
                                    }
                                }
                                else
                                {
                                    LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageSqnAdminExport()=%d\n", (int32_t)FuncRes);
                                }
                            }
                            else
                            {
                                LOG_CRIT(DA_PREFIX "FAILED: val_AssetLoadRandom(KEK)=%d\n", (int32_t)FuncRes);
                            }
                        }
                        else
                        {
                            LOG_CRIT(DA_PREFIX "FAILED: val_AssetAlloc(KEK)=%d\n", (int32_t)FuncRes);
                        }
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageAutnVerificationSqn(EMMCause)=%d (%d)\n",
                                 (int32_t)FuncRes, (int32_t)EMMCause);
                    }
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageAutnVerificationSqn()=Bad Result (%d,%d,%d)\n",
                             result1, result2, result3);
                    FuncRes = VAL_DATA_OVERRUN_ERROR;
                }
            }
            else
            {
                LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageAutnVerificationSqn()=%d\n", (int32_t)FuncRes);
            }
        }
        else
        {
            LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageSqnAdminCreate()=%d\n", (int32_t)FuncRes);
        }

        if (SqnAdminAssetId != VAL_ASSETID_INVALID)
        {
            (void)val_SFMilenageSqnAdminRelease(SqnAdminAssetId); // Note: = val_AssetFree
        }
        if (KekAssetId != VAL_ASSETID_INVALID)
        {
            (void)val_AssetFree(KekAssetId);
        }
    }

    return FuncRes;
}


/*----------------------------------------------------------------------------
 * MilenageAutsCheck
 *
 * This function performs the Milenage AUTS Generation.
 */
static ValStatus_t
MilenageAutsCheck(void)
{
    ValStatus_t FuncRes = VAL_SUCCESS;
    uint8_t AUTS[sizeof(gl_Milenage_TS1_SQN) + sizeof(gl_Milenage_TS1_f1star)];
    uint8_t SQNmsAK[sizeof(gl_Milenage_TS1_SQN)];

    FuncRes = val_SFMilenageAutsGeneration(gl_Milenage_AssetNumber,
                                           gl_Milenage_TS1_RAND,
                                           gl_Milenage_TS1_SQN, gl_Milenage_TS1_AMF,
                                           AUTS);
    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
    {
        int32_t result1;
        int32_t result2;

        MilenageXor(SQNmsAK,
                    gl_Milenage_TS1_SQN, gl_Milenage_TS1_f5star,
                    sizeof(gl_Milenage_TS1_SQN));
        result1 = memcmp(AUTS, SQNmsAK, sizeof(gl_Milenage_TS1_SQN));
        result2 = memcmp(&AUTS[sizeof(gl_Milenage_TS1_SQN)],
                         gl_Milenage_TS1_f1star, sizeof(gl_Milenage_TS1_f1star));
        if ((result1 == 0) && (result2 == 0))
        {
            LOG_CRIT(DA_PREFIX "PASSED: val_SFMilenageAutsGeneration=OK\n");
        }
        else
        {
            LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageAutsGeneration=Bad Result (%d,%d)\n",
                     result1, result2);
            FuncRes = VAL_DATA_OVERRUN_ERROR;
        }
    }
    else
    {
        LOG_CRIT(DA_PREFIX "FAILED: val_SFMilenageAutsGeneration()=%d\n", (int32_t)FuncRes);
    }

    return FuncRes;
}
#endif /* DA_VAL_SPECIAL_SF_MILENAGE */

#ifdef DA_VAL_SPECIAL_FIRMWARE_LOAD
/*----------------------------------------------------------------------------
 * read_file
 *
 * This is a helper function to load the Firmware image into memory
 */
static int32_t
read_file(const char * filename,
          uint8_t ** buffer,
          size_t * filesize)
{
    size_t ReadSize = 0;
    FILE * fp = NULL;
    int32_t rc = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        LOG_CRIT(DA_PREFIX "ERROR: Could not open image file %s\n", filename);
        rc = -1;
    }
    else
    {
        /* Determine file size */
        rc = fseek(fp, 0L, SEEK_END);
        if (rc == 0)
        {
            long int size = ftell(fp);
            if (size <= 0)
            {
                LOG_CRIT(DA_PREFIX "ERROR: Size of %s issue\n", filename);
                rc = -1;
            }
            else
            {
                *filesize = (size_t)size;
            }
        }
        if (rc == 0)
        {
            rc = fseek(fp, 0L, SEEK_SET);
        }

        if (rc == 0)
        {
            /* Allocate a buffer */
            *buffer = malloc(*filesize);
            if (*buffer == NULL)
            {
                LOG_CRIT(DA_PREFIX "ERROR: Memory allocation (input)\n");
                rc = -1;
            }
            else
            {
                /* Read the file data to the buffer */
                ReadSize = fread(*buffer, 1, *filesize, fp);
                if ((ferror(fp) != 0) || (*filesize != ReadSize))
                {
                    LOG_CRIT(DA_PREFIX "ERROR: Error while reading file %s (%d, %d, %d)\n",
                             filename, ferror(fp), (int32_t)*filesize, (int32_t)ReadSize);
                    free(*buffer);
                    rc = -1;
                }
            }
        }
        (void)fclose(fp);
    }
    return rc;
}


/*----------------------------------------------------------------------------
 * DAVS_FirmwareCheck
 *
 * This function checks a firmware image trough the firmware check command
 */
static ValStatus_t
DAVS_FirmwareCheck(const char *filename)
{
    ValStatus_t FuncRes;
    uint8_t * FirmwareImageBuf_p = NULL;
    size_t ImageSize = 0;

    if (read_file(filename, &FirmwareImageBuf_p, &ImageSize) == 0)
    {
        FuncRes = val_ServiceFirmwareCheck(FirmwareImageBuf_p, (uint32_t)ImageSize);
        free(FirmwareImageBuf_p);
    }
    else
    {
        FuncRes = VAL_INTERNAL_ERROR;
    }

    return FuncRes;
}
#endif


/*----------------------------------------------------------------------------
 * da_val_specials_main
 */
int32_t
da_val_specials_main(
        int32_t argc,
        const char **argv)
{
    int32_t status = 0;

    if (Driver130_Init() < 0)
    {
        LOG_CRIT(DA_PREFIX "FAILED: Driver130_Init()\n");
        status = -1;
    }
    else
    {
        ValStatus_t FuncRes = VAL_SUCCESS;
        int32_t i;

        // Process option arguments
        for (i = 1; argc > i; i++)
        {
            if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-help") == 0))
            {
                LOG_CRIT(DA_PREFIX "Example application for special functionality provided by the VAL API.\n\n");
                LOG_CRIT("Syntax     : %s [<option> ...]\n", argv[0]);
                LOG_CRIT("Description: Executes a Demo Application that can perform special VAL API\n");
                LOG_CRIT("             operations. Note that you can use the options to perform an\n");
                LOG_CRIT("             operation to set the hardware in a certain state and the provided\n");
                LOG_CRIT("             operations (options) are executed in the provided order.\n");
                LOG_CRIT("Options    : -help              Display this information.\n");
#ifdef DA_VAL_SPECIAL_ASSET_STORE_RESET
                LOG_CRIT("             -asreset           Reset/Clear dynamic Asset Store\n");
#endif /* DA_VAL_SPECIAL_ASSET_STORE_RESET */
#ifdef DA_VAL_SPECIAL_SF_MILENAGE
                LOG_CRIT("             -milenageotp       Write Milenage K and OPc to OTP. Note that the OTP\n");
                LOG_CRIT("                                must be initialized with HUK and COID, and the firmware\n");
                LOG_CRIT("                                is reset to re-initialize the Static Asset references.\n");
                LOG_CRIT("             -milenageautn      Check the Milenage AUTN verification sequence based\n");
                LOG_CRIT("                                on the Milenage K and OPc.\n");
                LOG_CRIT("             -milenageauts      Check the Milenage AUTS generation sequence based\n");
                LOG_CRIT("                                on the Milenage K and OPc.\n");
#endif /* DA_VAL_SPECIAL_SF_MILENAGE */
                LOG_CRIT("             -counterotp[=<Assetnumber>]\n");
                LOG_CRIT("                                Initialize a 32-bit OTP monotonic counter without keyblob\n");
                LOG_CRIT("                                for the specified AssetNumber.\n");
                LOG_CRIT("                                The default AssetNumber is 33 and note that the OTP must\n");
                LOG_CRIT("                                be initialized with HUK and COID, and the firmware is\n");
                LOG_CRIT("                                reset to re-initialize the Static Asset references.\n");
                LOG_CRIT("             -counterinc[=<Assetnumber>]\n");
                LOG_CRIT("                                Increment the specified monotonic counter.\n");
                LOG_CRIT("                                The default AssetNumber is 33.\n");
                LOG_CRIT("             -counterkeyderive[=<Assetnumber>]\n");
                LOG_CRIT("                                Validate Asset key blob generation when the KEK derivation\n");
                LOG_CRIT("                                is based on a monotonic counter.\n");
                LOG_CRIT("                                The default AssetNumber is 33.\n");
                LOG_CRIT("             -initotp           Initialize the OTP with a default COID and HUK.\n");
#ifdef DA_VAL_SPECIAL_FIRMWARE_LOAD
                LOG_CRIT("                                Initializes SFWBVER to zero.\n");
#endif
                LOG_CRIT("                                After successful initialization of the COID and HUK,\n");
                LOG_CRIT("                                the firmware is reset to re-initialize the Static \n");
                LOG_CRIT("                                Asset references.\n");
                LOG_CRIT("             -provrndhuk128[=<Samples>]\n");
                LOG_CRIT("                                Initialize the OTP with a random 128-bit HUK\n");
                LOG_CRIT("                                based on AES-DRBG with default COID.\n");
                LOG_CRIT("                                There is no OTP key blob generated. Optionally\n");
                LOG_CRIT("                                <Samples> specify the TRNG cycle samples for\n");
                LOG_CRIT("                                the TRNG Configure/Start (default=3072).\n");
                LOG_CRIT("             -provrndhuk256[=<Samples>]\n");
                LOG_CRIT("                                Initialize the OTP with a random 256-bit HUK\n");
                LOG_CRIT("                                based on AES-DRBG with default COID.\n");
                LOG_CRIT("                                There is no OTP key blob generated. Optionally\n");
                LOG_CRIT("                                <Samples> specify the TRNG cycle samples for\n");
                LOG_CRIT("                                the TRNG Configure/Start (default=3072).\n");
#ifdef DA_VAL_SPECIAL_ARIA_DRBG
                LOG_CRIT("             -ariaprovrndhuk128[=<Samples>]\n");
                LOG_CRIT("                                Initialize the OTP with a random 128-bit HUK\n");
                LOG_CRIT("                                based on ARIA-DRBG without default COID.\n");
                LOG_CRIT("                                There is no OTP key blob generated. Optionally\n");
                LOG_CRIT("                                <Samples> specify the TRNG cycle samples for\n");
                LOG_CRIT("                                the TRNG Configure/Start (default=3072).\n");
                LOG_CRIT("             -ariaprovrndhuk256[=<Samples>]\n");
                LOG_CRIT("                                Initialize the OTP with a random 256-bit HUK\n");
                LOG_CRIT("                                based on ARIA-DRBG with default COID.\n");
                LOG_CRIT("                                There is no OTP key blob generated. Optionally\n");
                LOG_CRIT("                                <Samples> specify the TRNG cycle samples for\n");
                LOG_CRIT("                                the TRNG Configure/Start (default=3072).\n");
#endif /* DA_VAL_SPECIAL_ARIA_DRBG */
                LOG_CRIT("             -sleep             Set hardware in Sleep mode.\n");
                LOG_CRIT("             -stopsleep         Resume hardware from Sleep mode.\n");
                LOG_CRIT("             -hwmodulestatus    Get module status from hardware.\n");
                LOG_CRIT("             -hwoptions         Get hardware options.\n");
                LOG_CRIT("             -hwversion         Get hardware version information.\n");
                LOG_CRIT("             -selftest          Run self-test.\n");
                LOG_CRIT("             -system            System information.\n");
                LOG_CRIT("             -reset             Reset firmware.\n");
                LOG_CRIT("             -regread=<Register>\n");
                LOG_CRIT("                                Read an internal register, where <Register> must be a\n");
                LOG_CRIT("                                hexadecimal representation of an address (e.g. 0xF878).\n");
                LOG_CRIT("             -regwrite=<Register>,<Value>\n");
                LOG_CRIT("                                Write the specified <Value> to an internal register,\n");
                LOG_CRIT("                                where <Register> and <Value> must be a hexadecimal\n");
                LOG_CRIT("                                representation of an address or value (e.g. 0xF878).\n");
                LOG_CRIT("             -trng[=<Samples>]  Configure/Start the TRNG and enables an AES-DRBG.\n");
                LOG_CRIT("                                Optionally <Samples> specify the TRNG cycle\n");
                LOG_CRIT("                                samples (default=3072).\n");
                LOG_CRIT("             -trngrawdata[=<Blocks>]\n");
                LOG_CRIT("                                Read raw data from TRNG/NRBG.\n");
                LOG_CRIT("                                Optionally <Blocks> specify the number of data\n");
                LOG_CRIT("                                blocks (default=40), which is <Blocks>*256 bytes.\n");
#ifdef DA_VAL_SPECIAL_ARIA_DRBG
                LOG_CRIT("             -ariadrbg[=<Samples>]\n");
                LOG_CRIT("                                Configure/Start the TRNG and enables an ARIA-DRBG.\n");
                LOG_CRIT("                                Optionally <Samples> specify the TRNG cycle\n");
                LOG_CRIT("                                samples (default=3072).\n");
#endif /* DA_VAL_SPECIAL_ARIA_DRBG */
#ifdef DA_VAL_SPECIAL_DRBG_FORCESEED
                LOG_CRIT("             -drbgforceseed     Initialize the DRBG with a seed. Note that this\n");
                LOG_CRIT("                                command disables FROs use and reseeding.\n");
                LOG_CRIT("                                Used Seed=0xD867E0F56663E88117E778242E386389\n");
                LOG_CRIT("                                            49DB62FEA94434603795EB720B96EAA0\n");
                LOG_CRIT("                                            99DEC05EE905410BE4277B254E365D7E\n");
#endif /* DA_VAL_SPECIAL_DRBG_FORCESEED */
#ifdef DA_VAL_SPECIAL_FIRMWARE_LOAD
                LOG_CRIT("             -sfwbotp           Write SFWBPKD, SFWBCR and SFWBVER to OTP. Note that\n");
                LOG_CRIT("                                the OTP must be initialized with HUK and COID, and the\n");
                LOG_CRIT("                                firmware is reset to re-initialize the Static\n");
                LOG_CRIT("                                Asset references.\n");
                LOG_CRIT("             -firmwarecheck=filename\n");
                LOG_CRIT("                                Run a firmware check on the specified firmware image file.\n");
                LOG_CRIT("             -updaterollbackid=RollbackId\n");
                LOG_CRIT("                                Update the RollbackId (SFWBVER).\n");
#endif
                LOG_CRIT("             -zerootp           Zeroize (destroy) OTP.\n");
                continue;
            }

            if (strcmp(argv[i], "-reset") == 0)
            {
                // Reset system to have known starting state
                LOG_CRIT(DA_PREFIX "Reset system\n");
                FuncRes = DoReset();
            }
            else if (strncmp(argv[i], "-regread=", 9) == 0)
            {
                char *EndPtr_p;
                uint32_t RegAddress = (uint32_t)strtoull(&argv[i][9], &EndPtr_p, 0);
                uint32_t RegValue = 0;

                if ((EndPtr_p == argv[i + 1]) || (*EndPtr_p != '\0') ||
                    (RegAddress > (uint32_t)0x0fffc))
                {
                    LOG_CRIT(DA_PREFIX "FAILED: Invalid register address\n");
                    break;
                }

                FuncRes = val_ServiceRegisterRead(RegAddress, &RegValue);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "PASSED: RegisterRead(0x%x)=0x%x\n", RegAddress, RegValue);
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_ServiceRegisterRead()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strncmp(argv[i], "-regwrite=", 10) == 0)
            {
                char *EndPtr_pR;
                char *EndPtr_pV;
                uint32_t RegAddress = (uint32_t)strtoull(&argv[i][10], &EndPtr_pR, 0);
                uint32_t RegValue = 0;

                if ((*EndPtr_pR != ',') || (RegAddress > (uint32_t)0x0fffc))
                {
                    LOG_CRIT(DA_PREFIX "FAILED: Invalid register address\n");
                    break;
                }
                EndPtr_pR++;
                RegValue = (uint32_t)strtoull(EndPtr_pR, &EndPtr_pV, 0);
                if ((EndPtr_pV == argv[i + 1]) || (*EndPtr_pV != '\0'))
                {
                    LOG_CRIT(DA_PREFIX "FAILED: Invalid register value\n");
                    break;
                }

                FuncRes = val_ServiceRegisterWrite(RegAddress, RegValue);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "PASSED: RegisterWrite(0x%x)=0x%x\n", RegAddress, RegValue);
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_ServiceRegisterWrite()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strncmp(argv[i], "-trngrawdata", 12) == 0)
            {
                uint16_t blocks = 40;

                if (argv[i][12] == '=')
                {
                    blocks = (uint16_t)atoi(&argv[i][13]);
                }
                FuncRes = GetTrngRawData(blocks);
            }
            else if (strncmp(argv[i], "-trng", 5) == 0)
            {
                if (argv[i][5] == '=')
                {
                    gl_SampleCycles = (uint16_t)atoi(&argv[i][6]);
                    if (gl_SampleCycles == 0U)
                    {
                        gl_SampleCycles = 2U;
                    }
                }
                FuncRes = ConfigureTrng();
            }
#ifdef DA_VAL_SPECIAL_ARIA_DRBG
            else if (strncmp(argv[i], "-ariadrbg", 9) == 0)
            {
                if (argv[i][9] == '=')
                {
                    gl_SampleCycles = (uint16_t)atoi(&argv[i][10]);
                    if (gl_SampleCycles == 0U)
                    {
                        gl_SampleCycles = 2U;
                    }
                }
                FuncRes = ConfigureAriaDrbg();
            }
#endif /* DA_VAL_SPECIAL_ARIA_DRBG */
#ifdef DA_VAL_SPECIAL_DRBG_FORCESEED
            else if (strcmp(argv[i], "-drbgforceseed") == 0)
            {
                FuncRes = ConfigureDrbgForceSeed();
            }
#endif /* DA_VAL_SPECIAL_DRBG_FORCESEED */
            else if (strcmp(argv[i], "-initotp") == 0)
            {
                LOG_CRIT(DA_PREFIX "Program default HUK and Crypto Officer ID in OTP\n");
                FuncRes = WriteOTP(EIP130_ASSET_POLICY_NONMODIFIABLE |
                                   (VAL_ASSETNUMBER_HUK << 1) |
                                   EIP130_ASSET_POLICY_NODOMAIN |
                                   EIP130_ASSET_POLICY_PRIVATEDATA |
                                   EIP130_ASSET_POLICY_GDHUK,
                                   gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                                   gl_HUK_OTPKeyBlob, sizeof(gl_HUK_OTPKeyBlob));
            }
#ifdef DA_VAL_SPECIAL_ASSET_STORE_RESET
            else if (strcmp(argv[i], "-asreset") == 0)
            {
                LOG_CRIT(DA_PREFIX "Reset/Clear dynamic Asset Store\n");
                FuncRes = val_AssetStoreReset();
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetStoreReset()=%d\n", (int32_t)FuncRes);
                    break;
                }
            }
#endif /* DA_VAL_SPECIAL_ASSET_STORE_RESET */
            else if (strncmp(argv[i], "-provrndhuk128", 14) == 0)
            {
                LOG_CRIT(DA_PREFIX "Program random 128-bit HUK and default Crypto Officer ID in OTP (AES-DRBG)\n");
                FuncRes = WriteRandomHuk(true, &argv[i][14], false);
            }
            else if (strncmp(argv[i], "-provrndhuk256", 14) == 0)
            {
                LOG_CRIT(DA_PREFIX "Program random 256-bit HUK and default Crypto Officer ID in OTP (AES-DRBG)\n");
                FuncRes = WriteRandomHuk(false, &argv[i][14], false);
            }
#ifdef DA_VAL_SPECIAL_ARIA_DRBG
            else if (strncmp(argv[i], "-ariaprovrndhuk128", 14) == 0)
            {
                LOG_CRIT(DA_PREFIX "Program random 128-bit HUK  and default Crypto Officer ID in OTP (ARIA-DRBG)\n");
                FuncRes = WriteRandomHuk(true, &argv[i][14], true);
            }
            else if (strncmp(argv[i], "-ariaprovrndhuk256", 14) == 0)
            {
                LOG_CRIT(DA_PREFIX "Program random 256-bit HUK and default Crypto Officer ID in OTP (ARIA-DRBG)\n");
                FuncRes = WriteRandomHuk(false, &argv[i][14], true);
            }
#endif /* DA_VAL_SPECIAL_ARIA_DRBG */
            else if (strncmp(argv[i], "-counterotp", 11) == 0)
            {
                ValAssetNumber_t AssetNumber;

                if (argv[i][11] == '=')
                {
                    char *EndPtr_p;

                    AssetNumber = (ValAssetNumber_t)strtoull(&argv[i][12], &EndPtr_p, 0);
                    if ((EndPtr_p == argv[i + 1]) || (*EndPtr_p != '\0') ||
                        (AssetNumber == 0U) || (AssetNumber > VAL_ASSET_NUMBER_MAX))
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: Invalid AssetNumber\n");
                        break;
                    }
                }
                else
                {
                    AssetNumber = 33;
                }

                FuncRes = WriteOTP(EIP130_ASSET_POLICY_MODIFIABLE |
                                   ((ValPolicyMask_t)AssetNumber << 1U) |
                                   EIP130_ASSET_POLICY_NODOMAIN |
                                   EIP130_ASSET_POLICY_PUBLICDATA |
                                   EIP130_ASSET_POLICY_GENERICDATA |
                                   EIP130_ASSET_POLICY_GDMONOTONIC,
                                   NULL, 4, NULL, 0);
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: Init OTP monotonic counter without keyblob (OTPwrite=%d)\n",
                             (int32_t)FuncRes);
                    break;
                }
            }
            else if (strncmp(argv[i], "-counterkeyderive", 17) == 0)
            {
                ValAssetId_t AssetId = VAL_ASSETID_INVALID;
                ValAssetId_t RootAssetId = VAL_ASSETID_INVALID;
                ValAssetId_t KEKAssetId = VAL_ASSETID_INVALID;
                ValPolicyMask_t AssetPolicyKEK;
                ValPolicyMask_t AssetPolicyKey;
                ValSize_t DataSize;
                ValAssetId_t MCAssetId = VAL_ASSETID_INVALID;
                ValAssetNumber_t AssetNumber;
                uint8_t KeyBlob1_p[32];
                uint8_t KeyBlob2_p[32];
                ValSize_t KeyBlobSize = 32;
                ValSize_t Size = 16;
                const char * KeyData_p = "Sample Test data ";

                if (argv[i][17] == '=')
                {
                    char *EndPtr_p;

                    AssetNumber = (ValAssetNumber_t)strtoull(&argv[i][18], &EndPtr_p, 0);
                    if ((EndPtr_p == argv[i + 1]) || (*EndPtr_p != '\0') ||
                        (AssetNumber == 0U) || (AssetNumber > VAL_ASSET_NUMBER_MAX))
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: Invalid AssetNumber\n");
                        break;
                    }
                }
                else
                {
                    AssetNumber = 33;
                }

                (void)memset(KeyBlob1_p, 0, sizeof(KeyBlob1_p));
                (void)memset(KeyBlob2_p, 0, sizeof(KeyBlob2_p));

                // Get Asset ID of the root key (HUK)
                RootAssetId = val_AssetGetRootKey();
                if(RootAssetId == VAL_ASSETID_INVALID)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: No Root key\n");
                    break;
                }

                // Get Asset ID of the Monotonic Counter
                FuncRes = val_AssetSearch(AssetNumber, &MCAssetId, &DataSize);
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetSearch(Monotonic Counter)=%d\n",
                             FuncRes);
                    break;
                }

                // Create an KEK Asset for the Asset Key Blob
                AssetPolicyKEK = EIP130_ASSET_POLICY_SYM_WRAP | EIP130_ASSET_POLICY_SCAWAESSIV | EIP130_ASSET_POLICY_SCDIRENCDEC;
                if (!val_IsAccessSecure())
                {
                    AssetPolicyKEK |= EIP130_ASSET_POLICY_SOURCENONSECURE;
                }
                FuncRes = val_AssetAlloc(AssetPolicyKEK, 64,
                                         VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                         &KEKAssetId);
                if(val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetAlloc(KEK1)=%d\n", FuncRes);
                    break;
                }

                // Derive the Asset data for the AES-SIV KEK based on a Monotonic Counter
                FuncRes = val_AssetLoadDerive(
                              KEKAssetId, RootAssetId,
                              gl_ADLabelDerive, (sizeof(gl_ADLabelDerive) - 1U),
                              false, false, NULL, 0, NULL, 0, (uint8_t)AssetNumber);
                if(val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetLoadDerive(KEK1)=%d\n", FuncRes);
                    (void)val_AssetFree(KEKAssetId);
                    break;
                }

                // Create an AES key Asset
                AssetPolicyKey = EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRDECVRFY;
                if (!val_IsAccessSecure())
                {
                    AssetPolicyKey |= EIP130_ASSET_POLICY_SOURCENONSECURE;
                }
                FuncRes = val_AssetAlloc(AssetPolicyKey, Size,
                                         VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                         &AssetId);
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetAlloc(Key1)=%d\n", FuncRes);
                    (void)val_AssetFree(KEKAssetId);
                    break;
                }

                // Load the AES key with plaintext data and export the keyBlob
                FuncRes = val_AssetLoadPlaintextExport(
                              AssetId,
                              (const ValOctetsIn_t * const) KeyData_p, Size,
                              KEKAssetId,
                              gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                              KeyBlob1_p, &KeyBlobSize);

                // Delete the AES key and KEK Assets
                (void)val_AssetFree(AssetId);
                (void)val_AssetFree(KEKAssetId);

                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetLoadPlaintextExport(Key1)=%d\n",
                             FuncRes);
                    break;
                }

                // Increment the Monotonic Counter
                FuncRes = val_MonotonicCounterIncrement(MCAssetId);
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_MonotonicCounterIncrement()=%d\n", (int32_t)FuncRes);
                    break;
                }

                // Create an KEK Asset for the Asset Key Blob
                FuncRes = val_AssetAlloc(AssetPolicyKEK, 64,
                                         VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                         &KEKAssetId);
                if(val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetAlloc(KEK2)=%d\n", FuncRes);
                    break;
                }

                // Derive the Asset data for the AES-SIV KEK based on a Monotonic Counter
                FuncRes = val_AssetLoadDerive(
                              KEKAssetId, RootAssetId,
                              gl_ADLabelDerive, (sizeof(gl_ADLabelDerive) - 1U),
                              false, false, NULL, 0, NULL, 0, (uint8_t)AssetNumber);
                if(val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetLoadDerive(KEK2)=%d\n", FuncRes);
                    (void)val_AssetFree(KEKAssetId);
                    break;
                }

                // Create an AES key Asset
                FuncRes = val_AssetAlloc(AssetPolicyKey, Size,
                                         VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                         &AssetId);
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetAlloc(Key)=%d\n", FuncRes);
                    (void)val_AssetFree(KEKAssetId);
                    break;
                }

                // Load the AES key with plaintext data and export the keyBlob
                FuncRes = val_AssetLoadPlaintextExport(
                              AssetId,
                              (const ValOctetsIn_t * const) KeyData_p, Size,
                              KEKAssetId,
                              gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                              KeyBlob2_p, &KeyBlobSize);

                // Delete the AES key and KEK Assets
                (void)val_AssetFree(AssetId);
                (void)val_AssetFree(KEKAssetId);

                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetLoadPlaintextExport(Key2)=%d\n", FuncRes);
                    break;
                }

                if (memcmp(KeyBlob1_p, KeyBlob2_p, sizeof(KeyBlob1_p)) == 0)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: counterkeyderive Test\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "PASSED: counterkeyderive Test\n");
                }
            }
            else if (strncmp(argv[i], "-counterinc", 11) == 0)
            {
                ValAssetNumber_t AssetNumber;
                ValAssetId_t AssetId = VAL_ASSETID_INVALID;
                uint8_t DataBuffer1[16];
                uint8_t DataBuffer2[16];
                ValSize_t DataSize;

                if (argv[i][11] == '=')
                {
                    char *EndPtr_p;

                    AssetNumber = (ValAssetNumber_t)strtoull(&argv[i][12], &EndPtr_p, 0);
                    if ((EndPtr_p == argv[i + 1]) || (*EndPtr_p != '\0') ||
                        (AssetNumber == 0U) || (AssetNumber > VAL_ASSET_NUMBER_MAX))
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: Invalid AssetNumber\n");
                        break;
                    }
                }
                else
                {
                    AssetNumber = 33;
                }

                LOG_CRIT(DA_PREFIX "Monotonic Counter increment (AssetNumber=%u)\n",
                         AssetNumber);

                // Get Asset ID of the Monotonic Counter
                DataSize = sizeof(DataBuffer1);
                FuncRes = val_AssetSearch(AssetNumber, &AssetId, &DataSize);
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_AssetSearch()=%d\n", (int32_t)FuncRes);
                    break;
                }

                (void)memset(DataBuffer1, 0, sizeof(DataBuffer1));
                (void)memset(DataBuffer2, 0, sizeof(DataBuffer2));

                FuncRes = val_MonotonicCounterRead(AssetId, DataBuffer1, DataSize);
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_MonotonicCounterRead(Before)=%d\n", (int32_t)FuncRes);
                    break;
                }

                FuncRes = val_MonotonicCounterIncrement(AssetId);
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_MonotonicCounterIncrement()=%d\n", (int32_t)FuncRes);
                    break;
                }

                FuncRes = val_MonotonicCounterRead(AssetId, DataBuffer2, DataSize);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    Log_HexDump("Before increment:", 0, DataBuffer1, (uint32_t)DataSize);
                    Log_HexDump("After increment :", 0, DataBuffer2, (uint32_t)DataSize);
                    if (memcmp(DataBuffer1, DataBuffer2, DataSize) != 0)
                    {
                        LOG_CRIT(DA_PREFIX "PASSED: Monotonic Counter increment\n");
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: Monotonic Counter increment\n");
                        break;
                    }
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_MonotonicCounterRead(After)=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strcmp(argv[i], "-zerootp") == 0)
            {
                LOG_CRIT(DA_PREFIX "Zeroize (destroy) OTP\n");
                FuncRes = val_ServiceSelectOTPZeroize();
                if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_ServiceSelectOTPZeroize()=%d\n", (int32_t)FuncRes);
                    break;
                }

                FuncRes = val_ServiceZeroizeOTP();
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "PASSED: OTP Zeroize\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_ServiceZeroizeOTP()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strcmp(argv[i], "-sleep") == 0)
            {
                FuncRes = val_SystemSleep();
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "PASSED: hardware is in Sleep mode\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_SystemSleep()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strcmp(argv[i], "-stopsleep") == 0)
            {
                FuncRes = val_SystemResumeFromSleep();
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "PASSED: Resume hardware from Sleep mode\n");

                    FuncRes = GetVersion();
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_SystemResumeFromSleep()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strcmp(argv[i], "-selftest") == 0)
            {
                LOG_CRIT(DA_PREFIX "Running self-test\n");
                FuncRes = val_SystemSelfTest();
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "PASSED: self-test Passed\n");
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_SystemSelfTest()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strcmp(argv[i], "-system") == 0)
            {
                uint8_t OtpErrorCode = 0U;
                uint16_t OtpErrorLocation = 0U;
                uint8_t Mode = 0U;
                uint8_t ErrorTest = 0U;
                uint8_t CryptoOfficer = 0U;
                uint8_t HostID = 0U;
                uint8_t NonSecure = 0U;
                uint32_t Identity = 0U;

                FuncRes = val_SystemGetState(&OtpErrorCode, &OtpErrorLocation,
                                             &Mode, &ErrorTest, &CryptoOfficer,
                                             &HostID, &NonSecure, &Identity);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    const char * ptr;

                    LOG_CRIT(DA_PREFIX "PASSED: System State read\n");
                    LOG_CRIT(DA_PREFIX "OTP State      : %u (%u)\n", OtpErrorCode, OtpErrorLocation);
                    LOG_CRIT(DA_PREFIX "Mode           : %u (0x%02X)\n", Mode, ErrorTest);
                    if (CryptoOfficer != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "CryptoOfficerId: %s\n", ptr);
                    LOG_CRIT(DA_PREFIX "HostId         : %u\n", HostID);
                    if (NonSecure != 0U)
                    {
                        ptr = "No";
                    }
                    else
                    {
                        ptr = "Yes";
                    }
                    LOG_CRIT(DA_PREFIX "Secure         : %s\n", ptr);
                    LOG_CRIT(DA_PREFIX "Identity       : 0x%X\n", Identity);
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_SystemGetState()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strcmp(argv[i], "-hwmodulestatus") == 0)
            {
                uint8_t CRC24Ok = 0U;
                uint8_t CRC24Busy = 0U;
                uint8_t CRC24Error = 0U;
                uint8_t FwImageWritten = 0U;
                uint8_t FwImageCheck = 0U;
                uint8_t FwImageAccepted = 0U;
                uint8_t FatalError = 0U;

                FuncRes = val_HW_ModuleStatus(NULL, NULL, &FatalError,
                                              &CRC24Ok, &CRC24Busy, &CRC24Error,
                                              &FwImageWritten, &FwImageCheck, &FwImageAccepted);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    const char * ptr;

                    LOG_CRIT(DA_PREFIX "PASSED: Hardware Module Status read\n");
                    if (FatalError != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "Fatal error              : %s\n", ptr);
                    if (CRC24Ok != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "CRC24 Ok                 : %s\n", ptr);
                    if (CRC24Busy != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "CRC24 busy               : %s\n", ptr);
                    if (CRC24Error != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "CRC24 error              : %s\n", ptr);
                    if (FwImageWritten != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "Firmware image written   : %s\n", ptr);
                    if (FwImageCheck != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "Firmware image check busy: %s\n", ptr);
                    if (FwImageAccepted != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "Firmware image accepted  : %s\n", ptr);
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_HW_ModuleStatus()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strcmp(argv[i], "-hwoptions") == 0)
            {
                uint8_t nMailboxes = 0U;
                uint16_t MailboxSize = 0U;
                uint8_t HostId = 0U;
                uint8_t SecureHostId = 0U;
                uint8_t MasterId = 0U;
                uint8_t MyHostId = 0U;
                uint8_t ProtectionAvailable = 0U;
                uint8_t Protection = 0U;
                uint16_t StandardEngines = 0U;
                uint16_t CustomEngines = 0U;

                FuncRes = val_HW_EIP_Options(&nMailboxes, &MailboxSize,
                                             &HostId, &SecureHostId, &MasterId, &MyHostId,
                                             &ProtectionAvailable, &Protection,
                                             &StandardEngines, &CustomEngines);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    const char * ptr;

                    LOG_CRIT(DA_PREFIX "PASSED: Hardware EIP Options read\n");
                    LOG_CRIT(DA_PREFIX "Number of mailboxes   : %d\n", nMailboxes);
                    LOG_CRIT(DA_PREFIX "Mailbox size in bytes : %d\n", MailboxSize);
                    LOG_CRIT(DA_PREFIX "HostId                : 0x%X\n", HostId);
                    LOG_CRIT(DA_PREFIX "SecureHostId          : 0x%X\n", SecureHostId);
                    LOG_CRIT(DA_PREFIX "MasterId              : %d\n", MasterId);
                    LOG_CRIT(DA_PREFIX "MyHostId              : %d\n", MyHostId);
                    if (ProtectionAvailable != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "Protection available  : %s\n", ptr);
                    if (Protection != 0U)
                    {
                        ptr = "Yes";
                    }
                    else
                    {
                        ptr = "No";
                    }
                    LOG_CRIT(DA_PREFIX "Protection set        : %s\n", ptr);
                    LOG_CRIT(DA_PREFIX "Standard Engines      : 0x%04X\n", StandardEngines);
                    LOG_CRIT(DA_PREFIX "Custom Engines        : 0x%04X\n", CustomEngines);
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_HW_EIP_Options()=%d\n", (int32_t)FuncRes);
                }
            }
            else if (strcmp(argv[i], "-hwversion") == 0)
            {
                uint8_t EipNumber = 0U;
                uint8_t MajorVersion = 0U;
                uint8_t MinorVersion = 0U;
                uint8_t PatchLevel = 0U;

                FuncRes = val_HW_EIP_Version(&MajorVersion, &MinorVersion,
                                             &PatchLevel, &EipNumber);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "PASSED: Hardware EIP version read\n");
                    LOG_CRIT(DA_PREFIX "EIP HW number    : 0x%X (%d)\n", EipNumber, EipNumber);
                    LOG_CRIT(DA_PREFIX "HW major version : %d\n", MajorVersion);
                    LOG_CRIT(DA_PREFIX "HW minor version : %d\n", MinorVersion);
                    LOG_CRIT(DA_PREFIX "HW patch level   : %d\n", PatchLevel);
                }
                else
                {
                    LOG_CRIT(DA_PREFIX "FAILED: val_HW_EIP_Version()=%d\n", (int32_t)FuncRes);
                }
            }
#ifdef DA_VAL_SPECIAL_SF_MILENAGE
            else if (strcmp(argv[i], "-milenageotp") == 0)
            {
                ValAssetId_t AssetId = VAL_ASSETID_INVALID;

                LOG_CRIT(DA_PREFIX "Program Milenage K and OPc in OTP\n");

                // Check if Milenage K and OPc is already written
                FuncRes = val_AssetSearch(gl_Milenage_AssetNumber, &AssetId, NULL);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "SKIPPED: Milenage K and OPc already exists\n");
                }
                else
                {
                    FuncRes = WriteOTP(EIP130_ASSET_POLICY_NONMODIFIABLE |
                                       ((ValPolicyMask_t)gl_Milenage_AssetNumber << 1) |
                                       EIP130_ASSET_POLICY_PRIVATEDATA |
                                       EIP130_ASSET_POLICY_NODOMAIN |
                                       EIP130_ASSET_POLICY_GDSPECIALFUNC |
                                       EIP130_ASSET_POLICY_GDSF_MILENAGEK_OPC,
                                       gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                                       gl_Milenage_TS1_OTPBlob, sizeof(gl_Milenage_TS1_OTPBlob));
                }
            }
            else if (strcmp(argv[i], "-milenageautn") == 0)
            {
                FuncRes = MilenageAutnCheck();
            }
            else if (strcmp(argv[i], "-milenageauts") == 0)
            {
                FuncRes = MilenageAutsCheck();
            }
#endif /* DA_VAL_SPECIAL_SF_MILENAGE */
#ifdef DA_VAL_SPECIAL_FIRMWARE_LOAD
            else if (strcmp(argv[i], "-sfwbotp") == 0)
            {
                ValAssetId_t AssetId = VAL_ASSETID_INVALID;

                LOG_CRIT(DA_PREFIX "Program SFWBPKD, SFWBCR and SFWBVER in OTP\n");

                // Check if SFWBPKD is already written
                FuncRes = val_AssetSearch(VAL_ASSETNUMBER_SFWBPKD, &AssetId, NULL);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "SKIPPED: SFWBPKD already exists\n");
                }
                else
                {
                    // Write SFWBVER
                    FuncRes = WriteOTP(EIP130_ASSET_POLICY_NONMODIFIABLE |
                                       (VAL_ASSETNUMBER_SFWBPKD << 1) |
                                       EIP130_ASSET_POLICY_NODOMAIN |
                                       EIP130_ASSET_POLICY_PUBLICDATA |
                                       EIP130_ASSET_POLICY_GENERICDATA |
                                       EIP130_ASSET_POLICY_GDPUBLICDATA,
                                       gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                                       gl_SFWBPKD_keyblob, sizeof(gl_SFWBPKD_keyblob));
                    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "SFWBPKD written\n");
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "SFWBPKD not written\n");
                    }
                }

                // Check if SFWBCR is already written
                FuncRes = val_AssetSearch(VAL_ASSETNUMBER_SFWBCR, &AssetId, NULL);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "SKIPPED: SFWBCR already exists\n");
                }
                else
                {
                    // Write SFWBCR
                    FuncRes = WriteOTP(EIP130_ASSET_POLICY_NONMODIFIABLE |
                                       (VAL_ASSETNUMBER_SFWBCR << 1U) |
                                       EIP130_ASSET_POLICY_NODOMAIN |
                                       EIP130_ASSET_POLICY_PRIVATEDATA |
                                       EIP130_ASSET_POLICY_SYMCRYPTO |
                                       EIP130_ASSET_POLICY_SCUIWRAP |
                                       EIP130_ASSET_POLICY_SCDIRDECVRFY |
                                       EIP130_ASSET_POLICY_SCACAES |
                                       EIP130_ASSET_POLICY_SCAWKEY,
                                       gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1),
                                       gl_SFWBCR_keyblob, sizeof(gl_SFWBCR_keyblob));
                    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "SFWBCR written\n");
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "SFWBCR not written\n");
                    }
                }

                // Check if SFWBVER is already written
                FuncRes = val_AssetSearch(VAL_ASSETNUMBER_SFWBVER, &AssetId, NULL);
                if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                {
                    LOG_CRIT(DA_PREFIX "SKIPPED: SFWBVER already exists\n");
                }
                else
                {
                    // Write SFWBVER
                    FuncRes = WriteOTP(EIP130_ASSET_POLICY_MODIFIABLE |
                                       (VAL_ASSETNUMBER_SFWBVER << 1) |
                                       EIP130_ASSET_POLICY_NODOMAIN |
                                       EIP130_ASSET_POLICY_PUBLICDATA |
                                       EIP130_ASSET_POLICY_GENERICDATA |
                                       EIP130_ASSET_POLICY_GDMONOTONIC,
                                       gl_ADLabelKeyblob, (sizeof(gl_ADLabelKeyblob) - 1U),
                                       gl_SFWBVER_keyblob, sizeof(gl_SFWBVER_keyblob));
                    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "SFWBVER written\n");
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "SFWBVER not written\n");
                    }
                }
            }
            else if(strncmp(argv[i], "-firmwarecheck", 14) == 0)
            {
                if (argv[i][14] == '=')
                {
                    FuncRes = DAVS_FirmwareCheck(&argv[i][15]);
                    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "PASSED: FirmwareImage is valid\n");
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: FirmwareCheck()=%d\n", (int32_t)FuncRes);
                    }
                }
            }
            else if(strncmp(argv[i], "-updaterollbackid", 17) == 0)
            {
                if (argv[i][17] == '=')
                {
                    char *EndPtr_p;
                    uint16_t RollbackId = 0;
                    RollbackId = (uint16_t)strtoull(&argv[i][18], &EndPtr_p, 0);
                    if (RollbackId > 33U)
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: Invalid RollbackID\n");
                        break;
                    }
                    FuncRes = val_ServiceUpdateRollbackID(RollbackId);
                    if (val_CheckFunctionResult(FuncRes) == VAL_SUCCESS)
                    {
                        LOG_CRIT(DA_PREFIX "PASSED: RollbackID updated to %d\n", RollbackId);
                    }
                    else
                    {
                        LOG_CRIT(DA_PREFIX "FAILED: val_ServiceUpdateRollbackID()=%d\n", (int32_t)FuncRes);
                    }
                }
            }

#endif /* DA_VAL_SPECIAL_FIRMWARE_LOAD */
            else
            {
                /* MISRA - Intentially empty */
            }

            if (val_CheckFunctionResult(FuncRes) != VAL_SUCCESS)
            {
                // Always exit on an error
                break;
            }
        }

        Driver130_Exit();
    }

    return status;
}


#ifndef DA_VAL_MAIN_REMOVE
/*----------------------------------------------------------------------------
 * main
 *
 * Program entry.
 */
int32_t
main(
        int32_t argc,
        const char **argv)
{
    return da_val_specials_main(argc, argv);
}
#endif // !DA_VAL_MAIN_REMOVE


/* end of file da_val_specials.c */


