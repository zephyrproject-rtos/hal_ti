/* valtest_asym_ecies.c
 *
 * Description: ECIES tests
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

#ifdef VALTEST_ECIES
#include "testvectors_ecies.h"
#include "valtest_asym_ecc_common.h" /* test_AsymEccLoadDomain */

static int
ecies_wrap(
    TestVector_ECIES_t Tv_p,
    ValAsymECCPoint_t * EphPubkey_p,
    ValOctetsOut_t * WrappedData_p,
    ValSize_t WrappedDataSize,
    const ValOctetsIn_Optional_t * OtherInfo_p,
    ValSize_t OtherInfoSize,
    ValAssetId_t DomainAssetId)
{
    ValStatus_t Status;
    ValAsymKey_t PublicKey;
    ValAsymECCPoint_t PubkeyData;
    ValPolicyMask_t AssetPolicy;
    ValAssetId_t HmacKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PublicKeyAssetId = VAL_ASSETID_INVALID;
    ValSize_t ModulusSizeBits = Tv_p->Curve_p->CurveBits;

    PubkeyData.x.Data_p = sfzutf_discard_const(Tv_p->PublicKey_p);
    PubkeyData.x.ByteDataSize = (Tv_p->PublicKeyLen/2);
    PubkeyData.y.Data_p = ((uint8_t *)sfzutf_discard_const(Tv_p->PublicKey_p) + (Tv_p->PublicKeyLen/2));
    PubkeyData.y.ByteDataSize = (Tv_p->PublicKeyLen/2);

    /* - Allocate & load the public key asset and initialize key structure */
    Status = val_AsymEcdhAllocPublicKeyAsset(ModulusSizeBits, false, false, &PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdhAllocPublicKeyAsset=", Status);

    Status = val_AsymInitKey(PublicKeyAssetId, DomainAssetId,
                             ModulusSizeBits, VAL_SYM_ALGO_NONE,
                             &PublicKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey=", Status);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&PubkeyData,
                                                    VAL_ECC_FAMILY_NIST_P,
                                                    ModulusSizeBits,
                                                    PublicKeyAssetId,
                                                    VAL_ASSETID_INVALID,
                                                    NULL, 0, NULL, NULL);

    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadPublicKeyAssetPlaintext=(pubkey)", Status);

    /* - Allocate & load asset data (asset that shall be wrapped) */
    AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_NODOMAIN |
                  EIP130_ASSET_POLICY_SCDIRENCGEN | EIP130_ASSET_POLICY_SCAHSHA512 |
                  EIP130_ASSET_POLICY_EXPORTABLE;
    Status = val_AssetAlloc(AssetPolicy, Tv_p->HmacLen,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &HmacKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc=(HmacKeyAssetId)", Status);

    Status = val_AssetLoadRandom(HmacKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadRandom=(HmacKeyAssetId)", Status);

    Status = val_AsymECIESWrap(&PublicKey,
                               HmacKeyAssetId,
                               OtherInfo_p, OtherInfoSize,
                               EphPubkey_p,
                               WrappedData_p, WrappedDataSize);
    if (ModulusSizeBits == 384)
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "val_AsymECIESWrap=", Status);
    }
    else
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymECIESWrap=", Status);
    }

    /* cleanup assets */
    Status = val_AssetFree(HmacKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(DataAsset)=", Status);
    Status = val_AssetFree(PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(PublicKeyAsset)=", Status);

    return END_TEST_SUCCES;
}


static int
ecies_unwrap(
    TestVector_ECIES_t Tv_p,
    const ValAsymECCPoint_t * EphPubkey_p,
    const ValOctetsIn_t * WrappedData_p,
    ValSize_t WrappedDataSize,
    const ValOctetsIn_Optional_t * OtherInfo_p,
    ValSize_t OtherInfoSize,
    ValAssetId_t DomainAssetId)
{
    ValStatus_t Status;
    ValAsymKey_t PrivateKey;
    ValAsymBigInt_t PrivateKeyData;
    ValPolicyMask_t AssetPolicy;
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t EphemeralPublicKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t HmacKeyAssetId = VAL_ASSETID_INVALID;
    ValSize_t ModulusSizeBits = Tv_p->Curve_p->CurveBits;

    /* Allocate the private key asset and initialize key structure */
    Status = val_AsymEcdhAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P,
                                              ModulusSizeBits,
                                              false, false, false,
                                              &PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdhAllocPrivateKeyAsset=", Status);

    Status = val_AsymInitKey(PrivateKeyAssetId, DomainAssetId,
                             ModulusSizeBits, VAL_SYM_ALGO_NONE,
                             &PrivateKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey=", Status);

    PrivateKeyData.Data_p = sfzutf_discard_const(Tv_p->PrivateKey_p);
    PrivateKeyData.ByteDataSize = Tv_p->PrivateKeyLen;

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&PrivateKeyData,
                                                     VAL_ECC_FAMILY_NIST_P,
                                                     ModulusSizeBits,
                                                     PrivateKeyAssetId,
                                                     VAL_ASSETID_INVALID,
                                                     NULL, 0, NULL, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadPrivateKeyAssetPlaintext=", Status);

    /* Allocate the ephemeral public key asset and initialize key structure */
    Status = val_AsymEcdhAllocPublicKeyAsset(ModulusSizeBits, false, false, &EphemeralPublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdhAllocPublicKeyAsset=", Status);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(EphPubkey_p,
                                                    VAL_ECC_FAMILY_NIST_P,
                                                    ModulusSizeBits,
                                                    EphemeralPublicKeyAssetId,
                                                    VAL_ASSETID_INVALID,
                                                    NULL, 0, NULL, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadPublicKeyAssetPlaintext=", Status);

    /* Allocate asset for unwrapped data */
    AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_NODOMAIN |
                  EIP130_ASSET_POLICY_SCDIRENCGEN | EIP130_ASSET_POLICY_SCAHSHA512;
    Status = val_AssetAlloc(AssetPolicy, Tv_p->HmacLen,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &HmacKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(HmacKeyAssetId)=", Status);

    Status = val_AsymECIESUnwrap(&PrivateKey,
                                 HmacKeyAssetId, EphemeralPublicKeyAssetId,
                                 OtherInfo_p, OtherInfoSize,
                                 WrappedData_p, WrappedDataSize);
    if (ModulusSizeBits == 384)
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "val_AsymECIESUnwrap=", Status);
    }
    else
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymECIESUnwrap=", Status);
    }

    /* cleanup assets */
    Status = val_AssetFree(HmacKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(HmacKeyAssetId)=", Status);
    Status = val_AssetFree(PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(PrivateKeyAssetId)=", Status);
    Status = val_AssetFree(EphemeralPublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(EphemeralPublicKeyAssetId)=", Status);

    return END_TEST_SUCCES;
}


START_TEST(test_AsymECIES)
{
    int Success = 0;
    int Failed = 0;
    uint32_t Index = 0U;
    int rc = END_TEST_SUCCES;

    TestVector_ECIES_t tv_p;
    ValAsymECCPoint_t EphPubkey;
    uint8_t * WrappedData_p;
    ValSize_t WrappedDataSize;
    ValAssetId_t DomainAssetId;
    uint8_t * OtherInfo_p = NULL;
    ValSize_t OtherInfoSize = 0;

    if ((_i & 1) != 0)
    {
        uint8_t OtherInfo[] = "this is some associated data for ECIES wrap/unwrap";

        OtherInfoSize = sizeof(OtherInfo);
        OtherInfo_p = (uint8_t *)SFZUTF_MALLOC(OtherInfoSize);
        fail_if(OtherInfo_p == NULL, "Allocation ", (int)OtherInfoSize);
        memcpy(OtherInfo_p, OtherInfo, OtherInfoSize);
    }

    while((tv_p = test_vectors_ecies_get(Index)) != NULL)
    {
        Index++;
        /* Load domain parameters */
        rc = test_AsymEccLoadDomain(tv_p->Curve_p, &DomainAssetId, false);
        if (rc == END_TEST_FAIL)
        {
            return rc;
        }

        /* Allocate memory for output data of the ecies wrap function */
        WrappedDataSize = tv_p->HmacLen + 8;
        WrappedData_p = (uint8_t *)SFZUTF_MALLOC(WrappedDataSize);
        fail_if(WrappedData_p == NULL, "Allocation ", (int)WrappedDataSize);

        EphPubkey.x.ByteDataSize = tv_p->Curve_p->PLen;
        EphPubkey.x.Data_p = (uint8_t *)SFZUTF_MALLOC(EphPubkey.x.ByteDataSize);
        fail_if(EphPubkey.x.Data_p == NULL, "Allocation ", (int)EphPubkey.x.ByteDataSize);

        EphPubkey.y.ByteDataSize = tv_p->Curve_p->PLen;
        EphPubkey.y.Data_p = (uint8_t *)SFZUTF_MALLOC(EphPubkey.y.ByteDataSize);
        fail_if(EphPubkey.y.Data_p == NULL, "Allocation ", (int)EphPubkey.y.ByteDataSize);

        rc = ecies_wrap(tv_p,
                        &EphPubkey,
                        WrappedData_p, WrappedDataSize,
                        OtherInfo_p, OtherInfoSize,
                        DomainAssetId);
        if (rc == END_TEST_SUCCES)
        {
            rc = ecies_unwrap(tv_p,
                              &EphPubkey,
                              WrappedData_p, WrappedDataSize,
                              OtherInfo_p, OtherInfoSize,
                              DomainAssetId);
            if (rc == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                /* ECIES unwrap failed */
                Failed++;
            }
        }
        else
        {
            /* ECIES wrap failed */
            Failed++;
        }

        SFZUTF_FREE(WrappedData_p);
        SFZUTF_FREE(EphPubkey.x.Data_p);
        SFZUTF_FREE(EphPubkey.y.Data_p);
        rc = val_AssetFree(DomainAssetId);
        fail_if(val_CheckFunctionResult(rc) != VAL_SUCCESS, "val_AssetFree(DomainAssetId)=", rc);
        test_vectors_ecies_release(tv_p);
    }

    if ((_i & 1) != 0)
    {
        SFZUTF_FREE(OtherInfo_p);
    }

    fail_if(Failed > 0, "Failed Vectors: ", Failed);
}
END_TEST


START_TEST (test_AsymEciesStrictArguments)
{
    ValStatus_t Status;
    /* dummy data */
    ValAssetId_t AssetId = 0x5001;
    ValOctetsIn_Optional_t otherinfo[4] = "test";
    ValAsymECCPoint_t ephkey;
    ValAsymKey_t aKey = { 0x5002, 0x5003, 256, 0 };
    ValOctetsOut_t dataout[16] = { 0 };

    /* ECIESWrap strict args tests */
    Status = val_AsymECIESWrap(NULL,
                               AssetId,
                               otherinfo, sizeof(otherinfo),
                               &ephkey,
                               dataout, sizeof(dataout));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESWrap=(StrictArg)", Status);
    Status = val_AsymECIESWrap(&aKey,
                               VAL_ASSETID_INVALID,
                               otherinfo, sizeof(otherinfo),
                               &ephkey,
                               dataout, sizeof(dataout));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESWrap=(StrictArg)", Status);
    Status = val_AsymECIESWrap(&aKey,
                               AssetId,
                               otherinfo, sizeof(otherinfo),
                               NULL,
                               dataout, sizeof(dataout));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESWrap=(StrictArg)", Status);
    Status = val_AsymECIESWrap(&aKey,
                               AssetId,
                               otherinfo, sizeof(otherinfo),
                               &ephkey,
                               NULL, sizeof(dataout));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESWrap=(StrictArg)", Status);
    Status = val_AsymECIESWrap(&aKey,
                               AssetId,
                               otherinfo, sizeof(otherinfo),
                               &ephkey,
                               dataout, 0);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESWrap=(StrictArg)", Status);

    /* ECIESUnwrap strict args tests */
    Status = val_AsymECIESUnwrap(NULL,
                                 AssetId, AssetId,
                                 otherinfo, sizeof(otherinfo),
                                 dataout, sizeof(dataout));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESUnwrap=", Status);
    Status = val_AsymECIESUnwrap(&aKey,
                                 VAL_ASSETID_INVALID, AssetId,
                                 otherinfo, sizeof(otherinfo),
                                 dataout, sizeof(dataout));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESUnwrap=", Status);
    Status = val_AsymECIESUnwrap(&aKey,
                                 AssetId, VAL_ASSETID_INVALID,
                                 otherinfo, sizeof(otherinfo),
                                 dataout, sizeof(dataout));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESUnwrap=", Status);
    Status = val_AsymECIESUnwrap(&aKey,
                                 AssetId, AssetId,
                                 otherinfo, sizeof(otherinfo),
                                 NULL, sizeof(dataout));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESUnwrap=", Status);
    Status = val_AsymECIESUnwrap(&aKey,
                                 AssetId, AssetId,
                                 otherinfo, sizeof(otherinfo),
                                 dataout, 0);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymECIESUnwrap=", Status);
}
END_TEST
#endif


int
suite_add_test_AsymEcies(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "AsymCrypto_ECIES");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

#ifdef VALTEST_ECIES
        if (sfzutf_test_add_loop(TestCase_p, test_AsymECIES, 2) != 0) goto FuncErrorReturn;
        if (valtest_StrictArgsCheck())
        {
            if (sfzutf_test_add(TestCase_p, test_AsymEciesStrictArguments)) goto FuncErrorReturn;
        }
#endif
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_asym_ecies.c */
