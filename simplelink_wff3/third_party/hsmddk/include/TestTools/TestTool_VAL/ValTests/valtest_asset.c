/* valtest_asset.c
 *
 * Description: Asset store tests
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
//#include "valtest_vectors_crypto.h"
//#include "valtest_tvstore.h"

/* Test vectors. */
#include "testvectors_aes_wrap.h"
#ifdef VALTEST_SYM_ALGO_SM4
#include "testvectors_sm4_wrap.h"
#endif

typedef struct
{
    ValPolicyMask_t Policy;
    ValSize_t       Size;
    ValStatus_t     Result;
} TestAssetAllocateData_t;

const char * g_ValTestAssociatedData_p = "Some Associated Data to satisfy the various AssetLoad operations, which is also used to initialize the Asset data";


START_TEST(test_AssetAllocFree)
{
    ValAssetId_t AssetId;
    ValStatus_t Status;
    const TestAssetAllocateData_t * pTestData;
    unsigned int i;

    static const TestAssetAllocateData_t TestData_Table[] =
    {
        /* AES allowed key sizes. */
        { EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRENCGEN, 16, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRDECVRFY, 24, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRENCGEN, 32, VAL_SUCCESS },
        /* AES forbidden key sizes. */
        { EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRDECVRFY,  0, VAL_INVALID_LENGTH },
        { EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRENCGEN,  8, VAL_INVALID_LENGTH },
        { EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRDECVRFY, 30, VAL_INVALID_LENGTH },
        { EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRENCGEN, 33, VAL_INVALID_LENGTH },
        { EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRDECVRFY, 48, VAL_INVALID_LENGTH },
        /* AES no mode. */
        { EIP130_ASSET_POLICY_SYM_BULK_AES, 32, VAL_ACCESS_ERROR },
        /* Derive. */
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADTRUSTED, 32, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADNORMALHMAC | EIP130_ASSET_POLICY_SCAHSHA256, 16, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADNORMALHMAC | EIP130_ASSET_POLICY_SCAHSHA256, 32, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADNORMALHMAC | EIP130_ASSET_POLICY_SCAHSHA256, 48, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADNORMALHMAC | EIP130_ASSET_POLICY_SCAHSHA256, 56, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADNORMALCMAC | EIP130_ASSET_POLICY_SCACAES, 16, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADNORMALCMAC | EIP130_ASSET_POLICY_SCACAES, 24, VAL_SUCCESS },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADNORMALCMAC | EIP130_ASSET_POLICY_SCACAES, 32, VAL_SUCCESS },
        /* Derive invalid length. */
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADTRUSTED, 16, VAL_INVALID_LENGTH },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADTRUSTED, 24, VAL_INVALID_LENGTH },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADTRUSTED, 48, VAL_INVALID_LENGTH },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADTRUSTED, 64, VAL_INVALID_LENGTH },
        { EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADNORMALCMAC | EIP130_ASSET_POLICY_SCACAES, 48, VAL_INVALID_LENGTH },
        /* end marker */
        { 0, 0, 0}
    };

    for(pTestData = TestData_Table, i = 0;
        (pTestData->Policy != 0) || (pTestData->Size != 0);
        pTestData++, i++)
    {
        ValPolicyMask_t AssetPolicy = pTestData->Policy;

        LOG_INFO("Process vector %d\n", i);

        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, pTestData->Size,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(val_CheckFunctionResult(Status) != pTestData->Result, "val_AssetAlloc()=", Status);

        if (val_CheckFunctionResult(Status) == VAL_SUCCESS)
        {
            // Free allocated asset to keep list of allocated assets clean.
            Status = val_AssetFree(AssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);
        }
    }

    if (valtest_StrictArgsCheck())
    {
        Status = val_AssetAlloc(EIP130_ASSET_POLICY_SYM_BASE | EIP130_ASSET_POLICY_SCACAES | EIP130_ASSET_POLICY_SCDIRENCGEN,
                                16,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                NULL);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetAlloc()=", Status);

        Status = val_AssetAlloc(0, 0,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetAlloc()=", Status);

        Status = val_AssetAlloc(0, 16,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetAlloc()=", Status);

        Status = val_AssetAlloc(0, 32,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetAlloc()=", Status);

        Status = val_AssetAlloc((EIP130_ASSET_POLICY_ASYM_SIGNVERIFY |
                                EIP130_ASSET_POLICY_ACA_RSAPSS |
                                EIP130_ASSET_POLICY_ACH_SHA1),
                                VAL_ASSET_SIZE_MAX+1,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetAlloc()=", Status);

        Status = val_AssetFree(VAL_ASSETID_INVALID);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetFree(BadArgument1)=", Status);
    }
}
END_TEST


START_TEST(test_AssetSearch)
{
    ValAssetId_t AssetId;
    ValSize_t AssetSize;
    ValStatus_t Status;

    Status = val_AssetSearch(VAL_ASSETNUMBER_HUK, &AssetId, &AssetSize);
    if (val_CheckFunctionResult(Status) == VAL_INVALID_ASSET)
    {
        // Assume empty OTP, so no Assets to search
    }
    else
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetSearch(HUK)=", Status);
        fail_if((AssetSize != (256 / 8)) && (AssetSize != (128 / 8)), "val_AssetSearch(HUK)=", AssetSize);

        Status = val_AssetFree(AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "val_AssetFree()=", Status);
    }

    // Test unlikely asset number
    Status = val_AssetSearch(53, &AssetId, &AssetSize);
    fail_if(((val_CheckFunctionResult(Status) != VAL_INVALID_ASSET) &&
             (val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT)),
            "val_AssetSearch(53)=", Status);

    if (valtest_StrictArgsCheck())
    {
        Status = val_AssetSearch(32, NULL, NULL);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetSearch(NULL)=", Status);
    }
}
END_TEST


START_TEST(test_AssetGetRootKey)
{
    ValAssetId_t AssetId;

    // Expect to find a root key
    AssetId = val_AssetGetRootKey();
    unsupported_if((AssetId == VAL_ASSETID_INVALID), "No Root key");
}
END_TEST


START_TEST(test_AssetLoadImport)
{
    uint8_t * AssociatedData_p;
    ValSize_t AssociatedDataSize = strlen(g_ValTestAssociatedData_p);
    uint8_t * KeyBlob_p;
    ValSize_t KeyBlobSize = 128;
    ValAssetId_t RootAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t KEKAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t AssetId;
    ValPolicyMask_t AssetPolicy;
    ValStatus_t Status;
    ValSize_t Size = 48;

    //  Get root key
    RootAssetId = val_AssetGetRootKey();
    unsupported_if((RootAssetId == VAL_ASSETID_INVALID), "No Root key");

    KeyBlob_p = (uint8_t *)SFZUTF_MALLOC(KeyBlobSize);
    fail_if(KeyBlob_p == NULL, "Allocation ", (int)KeyBlobSize);

    AssociatedData_p = (uint8_t *)SFZUTF_MALLOC(AssociatedDataSize);
    fail_if(AssociatedData_p == NULL, "Allocation ", (int)AssociatedDataSize);
    memcpy(AssociatedData_p, g_ValTestAssociatedData_p, AssociatedDataSize);

    // Create and derive KEK Asset
    AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP | EIP130_ASSET_POLICY_SCAWAESSIV | EIP130_ASSET_POLICY_SCDIRENCDEC;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, 64,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &KEKAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(KEK)=", Status);

    Status = val_AssetLoadDerive(KEKAssetId, RootAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 false, false, NULL, 0, NULL, 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(KEK)=", Status);

    // Create an Asset for random initialization to generate a KeyBlob
    AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_SCDIRENCGEN | EIP130_ASSET_POLICY_SCAHSHA256;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, Size,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

    Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                       AssociatedData_p, AssociatedDataSize,
                                       KeyBlob_p, &KeyBlobSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadRandomExport(Key)=", Status);
    fail_if(KeyBlobSize != VAL_KEYBLOB_SIZE(Size), "KeyBlob size ", (int)KeyBlobSize);

    Status = val_AssetFree(AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset)=", Status);

    // Create an Asset to import the KeyBlob again
    Status = val_AssetAlloc(AssetPolicy, Size,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset)=", Status);

    KeyBlob_p[0] = (uint8_t)(KeyBlob_p[0] + 1);
    Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 KeyBlob_p, KeyBlobSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_UNWRAP_ERROR, "val_AssetLoadImport(Key)=", Status);
    KeyBlob_p[0] = (uint8_t)(KeyBlob_p[0] - 1);

    if (!valtest_StrictArgsCheck())
    {
        Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                     AssociatedData_p, (VAL_KDF_LABEL_MIN_SIZE - 1),
                                     KeyBlob_p, KeyBlobSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_UNWRAP_ERROR, "val_AssetLoadImport(Key)=", Status);
    }

    Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 KeyBlob_p, KeyBlobSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadImport(Key)=", Status);

    // Load the already loaded Asset
    Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 KeyBlob_p, KeyBlobSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_LOCATION, "val_AssetLoadImport(Key)=", Status);

    Status = val_AssetFree(AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset)=", Status);

    if (valtest_StrictArgsCheck())
    {
        Status = val_AssetAlloc(AssetPolicy, Size,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset)=", Status);

        Status = val_AssetLoadImport(VAL_ASSETID_INVALID, KEKAssetId,
                                     AssociatedData_p, AssociatedDataSize,
                                     KeyBlob_p, KeyBlobSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetLoadImport(BadArgument1)=", Status);

        Status = val_AssetLoadImport(AssetId, VAL_ASSETID_INVALID,
                                     AssociatedData_p, AssociatedDataSize,
                                     KeyBlob_p, KeyBlobSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetLoadImport(BadArgument2)=", Status);

        Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                     NULL, AssociatedDataSize,
                                     KeyBlob_p, KeyBlobSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetLoadImport(BadArgument3)=", Status);

        Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                     AssociatedData_p, (VAL_KEYBLOB_AAD_MIN_SIZE - 1),
                                     KeyBlob_p, KeyBlobSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetLoadImport(BadArgument4L)=", Status);

        Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                     AssociatedData_p, (VAL_KEYBLOB_AAD_MAX_SIZE + 1),
                                     KeyBlob_p, KeyBlobSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetLoadImport(BadArgument4H)=", Status);

        Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                     AssociatedData_p, AssociatedDataSize,
                                     NULL, KeyBlobSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetLoadImport(BadArgument5)=", Status);

        Status = val_AssetLoadImport(AssetId, KEKAssetId,
                                     AssociatedData_p, AssociatedDataSize,
                                     KeyBlob_p, VAL_KEYBLOB_SIZE(VAL_ASSET_SIZE_MAX) + 1);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AssetLoadImport(BadArgument6)=", Status);

        Status = val_AssetFree(AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset)=", Status);
    }

    // Release the involved Assets
    Status = val_AssetFree(KEKAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(KEK)=", Status);

    SFZUTF_FREE(AssociatedData_p);
    SFZUTF_FREE(KeyBlob_p);
}
END_TEST


START_TEST(test_AssetLoadDerive)
{
    static const char * gl_SaltData_p = "Some Salt Data";
    static const char * gl_IVData_p = "Some IV Some IV Some IV Some IV ";
    uint8_t * AssociatedData_p;
    ValSize_t AssociatedDataSize = strlen(g_ValTestAssociatedData_p);
    uint8_t * SaltData_p;
    ValSize_t SaltDataSize = strlen(gl_SaltData_p);
    uint8_t * IVData_p;
    ValSize_t IVDataSize = strlen(gl_IVData_p);
    ValAssetId_t RootAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t TrustedKDKAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t KDKAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t AssetId = VAL_ASSETID_INVALID;
    ValPolicyMask_t AssetPolicy;
    ValStatus_t Status;

    //  Get root key
    RootAssetId = val_AssetGetRootKey();
    unsupported_if((RootAssetId == VAL_ASSETID_INVALID), "No Root key");

    AssociatedData_p = (uint8_t *)SFZUTF_MALLOC(AssociatedDataSize);
    fail_if(AssociatedData_p == NULL, "Allocation ", (int)AssociatedDataSize);
    memcpy(AssociatedData_p, g_ValTestAssociatedData_p, AssociatedDataSize);

    SaltData_p = (uint8_t *)SFZUTF_MALLOC(SaltDataSize);
    fail_if(SaltData_p == NULL, "Allocation ", (int)SaltDataSize);
    memcpy(SaltData_p, gl_SaltData_p, SaltDataSize);

    IVData_p = (uint8_t *)SFZUTF_MALLOC(IVDataSize);
    fail_if(IVData_p == NULL, "Allocation ", (int)IVDataSize);
    memcpy(IVData_p, gl_IVData_p, IVDataSize);

    // Create and derive a Trusted KDK Asset (SP800-108 feedback mode)
    AssetPolicy = EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADTRUSTED;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, 32,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &TrustedKDKAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Trusted KDK)=", Status);

    Status = val_AssetLoadDerive(TrustedKDKAssetId, RootAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 false, false, NULL, 0, NULL, 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(Trusted KDK)=", Status);

    // ------ TrustedKDK1
    // Create and derive a Trusted KDK Asset (1 - SP800-108 counter mode)
    AssetPolicy = EIP130_ASSET_POLICY_SYM_DERIVE | EIP130_ASSET_POLICY_SCADTRUSTED;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, 32,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(TrustedKDK1)=", Status);

    // Invalid associated data size
    if (!valtest_StrictArgsCheck())
    {
        Status = val_AssetLoadDerive(AssetId, RootAssetId,
                                     AssociatedData_p, (VAL_KDF_LABEL_MIN_SIZE - 1),
                                     true, false, NULL, 0, NULL, 0, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_LENGTH, "val_AssetLoadDerive(TrustedKDK1)=", Status);
    }

    Status = val_AssetLoadDerive(AssetId, RootAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 true, false, NULL, 0, NULL, 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(TrustedKDK1)=", Status);

    Status = val_AssetFree(AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(TrustedKDK1)=", Status);

    // ------
    // Create and derive KDK Asset (SP800-108 feedback mode)
    AssetPolicy = EIP130_ASSET_POLICY_SYM_DERIVE |
                  EIP130_ASSET_POLICY_SCADNORMALHMAC |
                  EIP130_ASSET_POLICY_SCAHSHA256;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, 64,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &KDKAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(KDK)=", Status);

    Status = val_AssetLoadDerive(KDKAssetId, TrustedKDKAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 false, false, NULL, 0, NULL, 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(KDK)=", Status);

    // ------ Asset1
    // Create and derive KDK Asset (SP800-108 counter mode)
    AssetPolicy = EIP130_ASSET_POLICY_SYM_DERIVE |
                  EIP130_ASSET_POLICY_SCADNORMALHMAC |
                  EIP130_ASSET_POLICY_SCAHSHA256;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, 32,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset1)=", Status);

    Status = val_AssetLoadDerive(AssetId, KDKAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 true, false, NULL, 0, NULL, 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(Asset1)=", Status);

    Status = val_AssetFree(AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset1)=", Status);

    // ------ Asset2
    // Create and derive KDK Asset (RFC5869)
    AssetPolicy = EIP130_ASSET_POLICY_SYM_DERIVE |
                  EIP130_ASSET_POLICY_SCADNORMALHMAC |
                  EIP130_ASSET_POLICY_SCAHSHA256;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, 32,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset2)=", Status);

    Status = val_AssetLoadDerive(AssetId, KDKAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 false, true, NULL, 0, NULL, 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(Asset2)=", Status);

    Status = val_AssetFree(AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset2)=", Status);

    // ------ Asset3
    // Create and derive KDK Asset
    // (SP800-108 feedmode mode with Randomness Extraction (salt))
    AssetPolicy = EIP130_ASSET_POLICY_SYM_DERIVE |
                  EIP130_ASSET_POLICY_SCADNORMALHMAC |
                  EIP130_ASSET_POLICY_SCAHSHA256;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, 32,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset3)=", Status);

    Status = val_AssetLoadDerive(AssetId, KDKAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 false, false,
                                 SaltData_p, SaltDataSize,
                                 NULL, 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(Asset3)=", Status);

    Status = val_AssetFree(AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset3)=", Status);

    // ------ Asset4
    // Create and derive KDK Asset
    // (SP800-108 feedmode mode with Randomness Extraction (salt) and
    //  IV for Key Expansion)
    AssetPolicy = EIP130_ASSET_POLICY_SYM_DERIVE |
                  EIP130_ASSET_POLICY_SCADNORMALHMAC |
                  EIP130_ASSET_POLICY_SCAHSHA256;
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }
    Status = val_AssetAlloc(AssetPolicy, 32,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset4)=", Status);

    Status = val_AssetLoadDerive(AssetId, KDKAssetId,
                                 AssociatedData_p, AssociatedDataSize,
                                 false, false,
                                 SaltData_p, SaltDataSize,
                                 IVData_p, IVDataSize, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(Asset4)=", Status);

    Status = val_AssetFree(AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset4)=", Status);

    if (valtest_StrictArgsCheck())
    {
        AssetPolicy = EIP130_ASSET_POLICY_SYM_DERIVE |
                      EIP130_ASSET_POLICY_SCADNORMALHMAC |
                      EIP130_ASSET_POLICY_SCAHSHA256;
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, 32,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset)=", Status);

        Status = val_AssetLoadDerive(VAL_ASSETID_INVALID, KDKAssetId,
                                     AssociatedData_p, AssociatedDataSize,
                                     false, false,
                                     SaltData_p, SaltDataSize,
                                     IVData_p, IVDataSize, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadDerive(BadArgument1)=", Status);

        Status = val_AssetLoadDerive(AssetId, VAL_ASSETID_INVALID,
                                     AssociatedData_p, AssociatedDataSize,
                                     false, false,
                                     SaltData_p, SaltDataSize,
                                     IVData_p, IVDataSize, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadDerive(BadArgument2)=", Status);

        Status = val_AssetLoadDerive(AssetId, KDKAssetId,
                                     NULL, AssociatedDataSize,
                                     false, false,
                                     SaltData_p, SaltDataSize,
                                     IVData_p, IVDataSize, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadDerive(BadArgument3)=", Status);

        Status = val_AssetLoadDerive(AssetId, KDKAssetId,
                                     AssociatedData_p, (VAL_KDF_LABEL_MIN_SIZE - 1),
                                     false, false,
                                     SaltData_p, SaltDataSize,
                                     IVData_p, IVDataSize, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadDerive(BadArgument4L)=", Status);

        Status = val_AssetLoadDerive(AssetId, KDKAssetId,
                                     AssociatedData_p, (VAL_KDF_LABEL_MAX_SIZE + 1),
                                     false, false,
                                     SaltData_p, SaltDataSize,
                                     IVData_p, IVDataSize, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadDerive(BadArgument4H)=", Status);

        Status = val_AssetLoadDerive(AssetId, KDKAssetId,
                                     AssociatedData_p, AssociatedDataSize,
                                     true, true,
                                     SaltData_p, SaltDataSize,
                                     IVData_p, IVDataSize, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadDerive(BadArgument5&6)=", Status);

        Status = val_AssetFree(AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset)=", Status);
    }

    // ======
    // Release the KDK Asset
    Status = val_AssetFree(KDKAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(KDK)=", Status);

    // Release the Trusted KDK Asset
    Status = val_AssetFree(TrustedKDKAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Trusted KDK)=", Status);

    SFZUTF_FREE(AssociatedData_p);
    SFZUTF_FREE(SaltData_p);
    SFZUTF_FREE(IVData_p);
}
END_TEST


START_TEST(test_AssetLoadPlaintext)
{
    static const ValSize_t Sizes[] = { 16, 24, 32, 48, 64, 0};
    uint8_t * AssociatedData_p = NULL;
    ValSize_t AssociatedDataSize = strlen(g_ValTestAssociatedData_p);
    uint8_t * KeyData_p = NULL;
    uint8_t * KeyBlob_p = NULL;
    ValSize_t KeyBlobSize = 500;
    ValSize_t Size;
    ValSize_t MaxSize = 0;
    ValAssetId_t AssetId = VAL_ASSETID_INVALID;
    ValAssetId_t RootAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t KEKAssetId = VAL_ASSETID_INVALID;
    ValPolicyMask_t AssetPolicy;
    ValStatus_t Status;
    unsigned int ndx;

    if (_i & 1)
    {
        //  Get root key
        RootAssetId = val_AssetGetRootKey();
        unsupported_if((RootAssetId == VAL_ASSETID_INVALID), "No Root key");
    }

    // Prepare key data
    for (ndx = 0; ; ndx++)
    {
        Size = Sizes[ndx];
        if (Size == 0)
        {
            break;
        }
        if (MaxSize < Size)
        {
            MaxSize = Size;
        }
    }
    if (MaxSize > 0)
    {
        KeyData_p = (uint8_t *)SFZUTF_MALLOC(MaxSize);
        fail_if(KeyData_p == NULL, "Allocation ", (int)MaxSize);
        for (ndx = 0; ndx < MaxSize; ndx++)
        {
            KeyData_p[ndx] = (uint8_t)(ndx + 1);
        }

        AssociatedData_p = (uint8_t *)SFZUTF_MALLOC(AssociatedDataSize);
        fail_if(AssociatedData_p == NULL, "Allocation ", (int)AssociatedDataSize);
        memcpy(AssociatedData_p, g_ValTestAssociatedData_p, AssociatedDataSize);

        // Run tests
        if (RootAssetId != VAL_ASSETID_INVALID)
        {
            // Create and derive KEK Asset
            AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP | EIP130_ASSET_POLICY_SCAWAESSIV | EIP130_ASSET_POLICY_SCDIRENCDEC;
            if (!val_IsAccessSecure())
            {
                AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
            }
            Status = val_AssetAlloc(AssetPolicy, 64,
                                    VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                    &KEKAssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(KEK)=", Status);

            Status = val_AssetLoadDerive(KEKAssetId, RootAssetId,
                                         AssociatedData_p, AssociatedDataSize,
                                         false, false, NULL, 0, NULL, 0, 0);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(KEK)=", Status);
        }

        KeyBlob_p = (uint8_t *)SFZUTF_MALLOC(KeyBlobSize);
        fail_if(KeyBlob_p == NULL, "Allocation ", (int)KeyBlobSize);

        for (ndx = 0;; ndx++)
        {
            Size = Sizes[ndx];
            if (Size == 0)
            {
                break;
            }

            LOG_INFO("Process vector %d\n", ndx);

            // Create an Asset for random initialization
            if ((Size == 16) || (Size == 24) || (Size == 32))
            {
                AssetPolicy = EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRENCGEN;
            }
            else
            {
                AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_SCDIRENCGEN | EIP130_ASSET_POLICY_SCAHSHA256;
            }
            if (!val_IsAccessSecure())
            {
                AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
            }
            Status = val_AssetAlloc(AssetPolicy, Size,
                                    VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                    &AssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

            if (KEKAssetId == VAL_ASSETID_INVALID)
            {
                Status = val_AssetLoadPlaintext(AssetId, KeyData_p, Size);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(Key)=", Status);

                // Try to load a second time
                Status = val_AssetLoadPlaintext(AssetId, KeyData_p, Size);
                fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_LOCATION, "val_AssetLoadPlaintext(Key)=", Status);
            }
            else
            {
                KeyBlobSize = VAL_KEYBLOB_SIZE(Size) + 4;
                Status = val_AssetLoadPlaintextExport(AssetId,
                                                      KeyData_p, Size,
                                                      KEKAssetId,
                                                      AssociatedData_p, AssociatedDataSize,
                                                      KeyBlob_p, &KeyBlobSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintextExport(Key)=", Status);
                fail_if(KeyBlobSize != VAL_KEYBLOB_SIZE(Size), "KeyBlob size ", (int)KeyBlobSize);

                // Try to load a second time
                Status = val_AssetLoadPlaintextExport(AssetId,
                                                      KeyData_p, Size,
                                                      KEKAssetId,
                                                      AssociatedData_p, AssociatedDataSize,
                                                      KeyBlob_p, &KeyBlobSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_LOCATION, "val_AssetLoadPlaintextExport(Key)=", Status);
            }

            // Release the involved Asset
            Status = val_AssetFree(AssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset)=", Status);
        }
    }

    if (valtest_StrictArgsCheck())
    {
        Size = 32;
        AssetPolicy = EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRENCGEN;
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, Size,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset)=", Status);

        Status = val_AssetLoadPlaintext(VAL_ASSETID_INVALID, KeyData_p, 32);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintext(BadArgument1)=", Status);

        Status = val_AssetLoadPlaintext(AssetId, NULL, 32);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintext(BadArgument2)=", Status);

        Status = val_AssetLoadPlaintext(AssetId, KeyData_p, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintext(BadArgument3L)=", Status);

        Status = val_AssetLoadPlaintext(AssetId, KeyData_p, (VAL_ASSET_SIZE_MAX + 1));
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintext(BadArgument3H)=", Status);

        if (KEKAssetId != VAL_ASSETID_INVALID)
        {
            Status = val_AssetLoadPlaintextExport(VAL_ASSETID_INVALID,
                                                  KeyData_p, Size,
                                                  KEKAssetId,
                                                  AssociatedData_p, AssociatedDataSize,
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument1)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  NULL, Size,
                                                  KEKAssetId,
                                                  AssociatedData_p, AssociatedDataSize,
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument2)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, 0,
                                                  KEKAssetId,
                                                  AssociatedData_p, AssociatedDataSize,
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument3L)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, (VAL_ASSET_SIZE_MAX + 1),
                                                  KEKAssetId,
                                                  AssociatedData_p, AssociatedDataSize,
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument3H)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, Size,
                                                  VAL_ASSETID_INVALID,
                                                  AssociatedData_p, AssociatedDataSize,
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument4)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, Size,
                                                  KEKAssetId,
                                                  NULL, AssociatedDataSize,
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument5)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, Size,
                                                  KEKAssetId,
                                                  AssociatedData_p, (VAL_KEYBLOB_AAD_MIN_SIZE - 1),
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument6L)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, Size,
                                                  KEKAssetId,
                                                  AssociatedData_p, (VAL_KEYBLOB_AAD_MAX_SIZE + 1),
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument6H)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, Size,
                                                  KEKAssetId,
                                                  AssociatedData_p, AssociatedDataSize,
                                                  NULL, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument7)=", Status);

            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, Size,
                                                  KEKAssetId,
                                                  AssociatedData_p, AssociatedDataSize,
                                                  KeyBlob_p, NULL);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument8)=", Status);

            KeyBlobSize = (Size + (128 / 8)) - 1;
            Status = val_AssetLoadPlaintextExport(AssetId,
                                                  KeyData_p, Size,
                                                  KEKAssetId,
                                                  AssociatedData_p, AssociatedDataSize,
                                                  KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadPlaintextExport(BadArgument8H)=", Status);
        }

        Status = val_AssetFree(AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset)=", Status);
    }

    SFZUTF_FREE(KeyBlob_p);
    SFZUTF_FREE(KeyData_p);
    SFZUTF_FREE(AssociatedData_p);

    // Release the involved Assets
    if (KEKAssetId != VAL_ASSETID_INVALID)
    {
        Status = val_AssetFree(KEKAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(KEK)=", Status);
    }
}
END_TEST


START_TEST(test_AssetLoadRandom)
{
    static const ValSize_t Sizes[] = { 16, 24, 32, 48, 64, 0};
    ValSize_t Size;
    uint8_t * AssociatedData_p;
    ValSize_t AssociatedDataSize = strlen(g_ValTestAssociatedData_p);
    uint8_t * KeyBlob_p;
    ValSize_t KeyBlobSize = 100;
    ValAssetId_t AssetId = VAL_ASSETID_INVALID;
    ValAssetId_t RootAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t KEKAssetId = VAL_ASSETID_INVALID;
    ValPolicyMask_t AssetPolicy;
    ValStatus_t Status;
    int ndx;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    if (_i & 1)
    {
        //  Get root key
        RootAssetId = val_AssetGetRootKey();
        unsupported_if((RootAssetId == VAL_ASSETID_INVALID), "No Root key");
    }

    AssociatedData_p = (uint8_t *)SFZUTF_MALLOC(AssociatedDataSize);
    fail_if(AssociatedData_p == NULL, "Allocation ", (int)AssociatedDataSize);
    memcpy(AssociatedData_p, g_ValTestAssociatedData_p, AssociatedDataSize);

    if (RootAssetId != VAL_ASSETID_INVALID)
    {
        // Create and derive KEK Asset
        AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP | EIP130_ASSET_POLICY_SCAWAESSIV | EIP130_ASSET_POLICY_SCDIRENCDEC;
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, 64,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &KEKAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(KEK)=", Status);

        Status = val_AssetLoadDerive(KEKAssetId, RootAssetId,
                                     AssociatedData_p, AssociatedDataSize,
                                     false, false, NULL, 0, NULL, 0, 0);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(KEK)=", Status);
    }

    KeyBlob_p = (uint8_t *)SFZUTF_MALLOC(KeyBlobSize);
    fail_if(KeyBlob_p == NULL, "Allocation ", (int)KeyBlobSize);

    for (ndx = 0; ; ndx++)
    {
        Size = Sizes[ndx];
        if (Size == 0)
        {
            break;
        }

        LOG_INFO("Process vector %d\n", ndx);

        // Create an Asset for random initialization
        if ((Size == 16) || (Size == 24) || (Size == 32))
        {
            AssetPolicy = EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRDECVRFY;
        }
        else
        {
            AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_SCDIRDECVRFY | EIP130_ASSET_POLICY_SCAHSHA256;
        }
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, Size,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

        if (KEKAssetId == VAL_ASSETID_INVALID)
        {
            Status = val_AssetLoadRandom(AssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadRandom(Key)=", Status);

            // Try to load a second time
            Status = val_AssetLoadRandom(AssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_LOCATION, "val_AssetLoadRandomExport(Key)=", Status);
        }
        else
        {
            KeyBlobSize = VAL_KEYBLOB_SIZE(Size) + 4;
            Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                               AssociatedData_p, AssociatedDataSize,
                                               KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadRandomExport(Key)=", Status);
            fail_if(KeyBlobSize != VAL_KEYBLOB_SIZE(Size), "KeyBlob size ", (int)KeyBlobSize);

            // Try to load a second time
            Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                               AssociatedData_p, AssociatedDataSize,
                                               KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_LOCATION, "val_AssetLoadRandomExport(Key)=", Status);
        }

        // Release the involved Asset
        Status = val_AssetFree(AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset)=", Status);
    }

    if (valtest_StrictArgsCheck())
    {
        Size = 32;
        AssetPolicy = EIP130_ASSET_POLICY_SYM_BULK_AES | EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRENCGEN;
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, Size,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Asset)=", Status);

        Status = val_AssetLoadRandom(VAL_ASSETID_INVALID);
        fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandom(BadArgument1)=", Status);

        if (KEKAssetId != VAL_ASSETID_INVALID)
        {
            Status = val_AssetLoadRandomExport(VAL_ASSETID_INVALID, KEKAssetId,
                                               AssociatedData_p, AssociatedDataSize,
                                               KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument1)=", Status);

            Status = val_AssetLoadRandomExport(AssetId, VAL_ASSETID_INVALID,
                                               AssociatedData_p, AssociatedDataSize,
                                               KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument2)=", Status);

            Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                               NULL, AssociatedDataSize,
                                               KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument3)=", Status);

            Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                               AssociatedData_p, (VAL_KEYBLOB_AAD_MIN_SIZE - 1),
                                               KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument4L)=", Status);

            Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                               AssociatedData_p, (VAL_KEYBLOB_AAD_MAX_SIZE + 1),
                                               KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument4H)=", Status);

            Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                               AssociatedData_p, AssociatedDataSize,
                                               NULL, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument5)=", Status);

            Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                               AssociatedData_p, AssociatedDataSize,
                                               KeyBlob_p, NULL);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument6)=", Status);

            KeyBlobSize = (128 / 8) - 1;
            Status = val_AssetLoadRandomExport(AssetId, KEKAssetId,
                                               AssociatedData_p, AssociatedDataSize,
                                               KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument6H)=", Status);
        }

        Status = val_AssetFree(AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Asset)=", Status);
    }

    SFZUTF_FREE(KeyBlob_p);
    SFZUTF_FREE(AssociatedData_p);

    // Release the involved Assets
    if (KEKAssetId != VAL_ASSETID_INVALID)
    {
        Status = val_AssetFree(KEKAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(KEK)=", Status);
    }
}
END_TEST

static ValStatus_t
do_AssetLoadSymUnwrap(const uint8_t *KEK_p,
                      const uint8_t *PlainTxt_p,
                      const uint8_t *WrappedTxt_p,
                      uint32_t KeyLen,
                      uint32_t PlainTxtLen,
                      uint32_t WrappedTxtLen,
                      uint8_t algorithm)
{
    ValStatus_t Status = END_TEST_SUCCES;
    IDENTIFIER_NOT_USED(PlainTxt_p);

    if ((KeyLen > 0) && (PlainTxtLen > 0) && (WrappedTxtLen > 0))
    {
        ValPolicyMask_t AssetPolicy;
        ValAssetId_t KekAssetId = VAL_ASSETID_INVALID;
        ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;
        uint8_t *KekData_p = NULL;
        uint8_t *KeyData_p = NULL;

        // Create KEK asset
        if (algorithm == VAL_SYM_ALGO_CIPHER_AES)
        {
            AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP_AES;
        }
        else
        {
            AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP_SM4;
        }
        AssetPolicy |= EIP130_ASSET_POLICY_SCAWKEY | EIP130_ASSET_POLICY_SCDIRDECVRFY;
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, KeyLen,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &KekAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(KEK)=", Status);

        KekData_p = (uint8_t *)SFZUTF_MALLOC(KeyLen);
        fail_if(KekData_p == NULL, "Allocation ", (int)KeyLen);
        memcpy(KekData_p, KEK_p, KeyLen);

        Status = val_AssetLoadPlaintext(KekAssetId, KekData_p, KeyLen);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(KEK)=", Status);

        SFZUTF_FREE(KekData_p);

        // create asset for unwrapped data
        if ((PlainTxtLen == 16) || (PlainTxtLen == 24) || (PlainTxtLen == 32))
        {
            if (algorithm == VAL_SYM_ALGO_CIPHER_AES)
            {
                AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP_AES;
            }
            else
            {
                AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP_SM4;
            }
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRDECVRFY;
        }
        else if ((PlainTxtLen >= (160 / 8)) && (PlainTxtLen <= 64))
        {
            AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_SCDIRENCGEN | EIP130_ASSET_POLICY_SCAHSHA1;
        }
        else
        {
            AssetPolicy = EIP130_ASSET_POLICY_ASYM_SIGNVERIFY | EIP130_ASSET_POLICY_ACA_ECDSA;
        }
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, PlainTxtLen,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &KeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

        KeyData_p = (uint8_t *)SFZUTF_MALLOC(WrappedTxtLen);
        fail_if(KeyData_p == NULL, "Allocation ", (int)WrappedTxtLen);
        memcpy(KeyData_p, WrappedTxt_p, WrappedTxtLen);

        // Initialize the Asset with a corrupt keyblob through an unwrap operation
        KeyData_p[4] = (uint8_t)(KeyData_p[4] ^ -1);
        Status = val_AssetLoadSymUnwrap(KeyAssetId, KekAssetId, KeyData_p, WrappedTxtLen, algorithm);
        fail_if(val_CheckFunctionResult(Status) != VAL_UNWRAP_ERROR, "AssetLoadSymUnwrap(Key)=", Status);
        KeyData_p[4] = (uint8_t)(KeyData_p[4] ^ -1);

        // Keyblob too small for an unwrap operation
        Status = val_AssetLoadSymUnwrap(KeyAssetId, KekAssetId, KeyData_p, (WrappedTxtLen - (32 / 8)), algorithm);
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "AssetLoadSymUnwrap(Key)=", Status);

        // Initialize the Asset through an unwrap operation
        Status = val_AssetLoadSymUnwrap(KeyAssetId, KekAssetId, KeyData_p, WrappedTxtLen, algorithm);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "AssetLoadSymUnwrap(Key)=", Status);

        SFZUTF_FREE(KeyData_p);

        // Release the involved Assets
        Status = val_AssetFree(KeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Key)=", Status);

        Status = val_AssetFree(KekAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(KEK)=", Status);
        if (valtest_StrictArgsCheck())
        {
            ValSize_t Size = 32;
            KeyData_p = (uint8_t *)SFZUTF_MALLOC((Size + (64 / 8)));
            fail_if(KeyData_p == NULL, "Allocation ", (int)(Size + (64 / 8)));

            KekAssetId = 0x15004;
            Status = val_AssetLoadSymUnwrap(VAL_ASSETID_INVALID, KekAssetId, KeyData_p, (Size + (64 / 8)), algorithm);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandom(BadArgument1)=", Status);

            Status = val_AssetLoadSymUnwrap(KeyAssetId, VAL_ASSETID_INVALID, KeyData_p, (Size + (64 / 8)), algorithm);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument2)=", Status);

            Status = val_AssetLoadSymUnwrap(KeyAssetId, KekAssetId, NULL, (Size + (64 / 8)), algorithm);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument3)=", Status);

            Status = val_AssetLoadSymUnwrap(KeyAssetId, KekAssetId, KeyData_p, (VAL_ASSET_SIZE_MAX + (64 / 8) + 1), algorithm);
            fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AssetLoadRandomExport(BadArgument4H)=", Status);

            SFZUTF_FREE(KeyData_p);
        }
    }
    return END_TEST_SUCCES;
}

START_TEST(test_AssetLoadSymUnwrap_aes)
{
    TestVector_AES_WRAP_t aes_tv_p;
    int Failed = 0;
    int Passed = 0;
    uint32_t i;

    for (i = 0; ; i++)
    {
        aes_tv_p = test_vectors_aes_wrap_get(i);
        if (aes_tv_p == NULL)
        {
            break;
        }

        if(aes_tv_p->PlainTxtLen > 8)
        {
            if (do_AssetLoadSymUnwrap(aes_tv_p->KEK_p,
                                      aes_tv_p->PlainTxt_p,
                                      aes_tv_p->WrappedTxt_p,
                                      aes_tv_p->KeyLen,
                                      aes_tv_p->PlainTxtLen,
                                      aes_tv_p->WrappedTxtLen,
                                      VAL_SYM_ALGO_CIPHER_AES) == END_TEST_SUCCES)
            {
                Passed++;
            }
            else
            {
                Failed++;
                LOG_CRIT("Processed vector %d\n", i);
            }
        }
        test_vectors_aes_wrap_release(aes_tv_p);
    }
    fail_if(((Failed != 0) || (Passed == 0)), "vectors failed=", Failed);
}
END_TEST

#ifdef VALTEST_SYM_ALGO_SM4
START_TEST(test_AssetLoadSymUnwrap_sm4)
{
    TestVector_SM4_WRAP_t sm4_tv_p;
    int Failed = 0;
    int Passed = 0;
    uint32_t i;

    for (i = 0U; ; i++)
    {
        sm4_tv_p = test_vectors_sm4_wrap_get(i);
        if (sm4_tv_p == NULL)
        {
            break;
        }

        if (sm4_tv_p->PlainTxtLen > 8)
        {
            if (do_AssetLoadSymUnwrap(sm4_tv_p->KEK_p,
                                      sm4_tv_p->PlainTxt_p,
                                      sm4_tv_p->WrappedTxt_p,
                                      sm4_tv_p->KeyLen,
                                      sm4_tv_p->PlainTxtLen,
                                      sm4_tv_p->WrappedTxtLen,
                                      VAL_SYM_ALGO_CIPHER_SM4) == END_TEST_SUCCES)
            {
                Passed++;
            }
            else
            {
                Failed++;
                LOG_CRIT("Processed vector %d\n", i);
            }
        }
        test_vectors_sm4_wrap_release(sm4_tv_p);
    }
    fail_if(((Failed != 0) || (Passed == 0)), "vectors failed=", Failed);
}
END_TEST
#endif

#ifdef VALTEST_ASSET_EXPORT_VIA_CPIF
static inline ValPolicyMask_t
CPBitToPolicyMode(uint16_t cp_bit)
{
    return (ValPolicyMask_t)cp_bit << 16;
}

START_TEST(test_AssetExportCPIF)
{
    uint32_t i;
    const uint8_t DataSet1[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
    const uint8_t DataSet2[] = { 0x5A, 0x5A, 0x5A, 0x5A, 0xA5, 0xA5, 0xA5, 0xA5,
                                 0xA5, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
                                 0x0F, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA };
    const uint8_t DataSet3[] = { 0x12, 0x34, 0x56, 0x78 };
    const uint8_t DataSet4[] = { 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };

    struct Entry
    {
        const uint8_t * data;
        uint32_t len;
        uint16_t address;
        uint16_t cp_bits;
    } DataArray[] = {
        { DataSet1, sizeof(DataSet1), 0x4,   BIT_0 },
        { DataSet2, sizeof(DataSet2), 0x16,  BIT_1 },
        { DataSet3, sizeof(DataSet3), 0x160, BIT_2 },
        { DataSet4, sizeof(DataSet4), 0x200, BIT_3 },
        { DataSet1, sizeof(DataSet1), 0x20,  BIT_0 | BIT_5 | BIT_7 | BIT_9 },
        { DataSet2, sizeof(DataSet2), 0x40,  MASK_10_BITS }
    };

    for (i = 0; i < sizeof(DataArray)/sizeof(DataArray[0]); i++)
    {
        uint8_t * Data_p;
        ValAssetId_t AssetId = VAL_ASSETID_INVALID;
        ValStatus_t Status;
        ValPolicyMask_t AssetPolicy = EIP130_ASSET_POLICY_NONMODIFIABLE|
                                      EIP130_ASSET_POLICY_EXPORTABLE|
                                      EIP130_ASSET_POLICY_PRIVATEDATA|
                                      EIP130_ASSET_POLICY_COPROIFC;

        AssetPolicy |= CPBitToPolicyMode(DataArray[i].cp_bits);
        AssetPolicy |= (!val_IsAccessSecure()) ? EIP130_ASSET_POLICY_SOURCENONSECURE : 0;

        Status = val_AssetAlloc(AssetPolicy, DataArray[i].len,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetId);
        unsupported_if(val_CheckFunctionResult(Status) == VAL_ACCESS_ERROR, "");
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc()=", Status);

        Data_p = (uint8_t *)SFZUTF_MALLOC(DataArray[i].len);
        fail_if(Data_p == NULL, "Allocation ", (int)DataArray[i].len);
        memcpy(Data_p, DataArray[i].data, DataArray[i].len);

        Status = val_AssetLoadPlaintext(AssetId, Data_p, DataArray[i].len);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext()=", Status);

        SFZUTF_FREE(Data_p);

        Status = val_AssetExportViaCPIF(AssetId, DataArray[i].address, DataArray[i].cp_bits);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetExportViaCPIF()=", Status);

        Status = val_AssetFree(AssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);
    }
}
END_TEST
#endif


int
suite_add_test_AssetManagement(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "AssetManagement_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_AssetGetRootKey) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AssetSearch) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AssetAllocFree) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AssetLoadDerive) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_AssetLoadPlaintext, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_AssetLoadRandom, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AssetLoadImport) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AssetLoadSymUnwrap_aes) != 0) goto FuncErrorReturn;
#ifdef VALTEST_SYM_ALGO_SM4
        if (sfzutf_test_add(TestCase_p, test_AssetLoadSymUnwrap_sm4) != 0) goto FuncErrorReturn;
#endif
#ifdef VALTEST_ASSET_EXPORT_VIA_CPIF
        if (sfzutf_test_add(TestCase_p, test_AssetExportCPIF) != 0) goto FuncErrorReturn;
#endif

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_asset.c */
