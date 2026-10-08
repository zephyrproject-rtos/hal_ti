/* valtest_asym_ecdsa.c
 *
 * Description: ECDSA tests
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
#define VALTEST_DOKEYCHECK

/* Test vectors. */
#include "testvectors_ecdsa.h"

/* Test helper functions. */
#include "valtest_asym_ecc_common.h"


static int
DoEccEcdsaParamsTest(
        uint32_t VectorIndex,
        TestVector_ECDSA_t Vector_p)
{
    int rc;
    ValStatus_t Status;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAssetId_t DomainAssetId = VAL_ASSETID_INVALID;

    IDENTIFIER_NOT_USED(VectorIndex);

    /* Load domain parameters */
    rc = test_AsymEccLoadDomain(Vector_p->Curve_p, &DomainAssetId, true);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }

    /* Dummy key entries */
    Status = val_AsymInitKey(VAL_ASSETID_INVALID, DomainAssetId,
                             Vector_p->Curve_p->CurveBits, VAL_SYM_ALGO_HASH_SHA1,
                             &PrivateKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    Status = val_AsymInitKey(VAL_ASSETID_INVALID, DomainAssetId,
                             Vector_p->Curve_p->CurveBits, VAL_SYM_ALGO_HASH_SHA1,
                             &PublicKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    /* Check public key (curve) parameters  */
    Status = val_AsymEccKeyCheck(&PublicKey, &PrivateKey);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccKeyCheck()=", Status);

    /* Clean-up*/
    Status = val_AssetFree(DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

    if (valtest_StrictArgsCheck())
    {
        Status = val_AsymEccKeyCheck(NULL, NULL);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccKeyCheck(BadArgument1&2)=", Status);

        (void)val_AsymInitKey(VAL_ASSETID_INVALID, DomainAssetId,
                              (VAL_ASYM_ECP_MIN_BITS - 1), VAL_SYM_ALGO_HASH_SHA1,
                              &PublicKey);
        Status = val_AsymEccKeyCheck(&PublicKey, &PrivateKey);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccKeyCheck(BadArgument1I)=", Status);
        Status = val_AsymEccKeyCheck(&PrivateKey, &PublicKey);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccKeyCheck(BadArgument2I)=", Status);

        (void)val_AsymInitKey(VAL_ASSETID_INVALID, DomainAssetId,
                              (VAL_ASYM_ECP_MAX_BITS + 1), VAL_SYM_ALGO_HASH_SHA1,
                              &PublicKey);
        Status = val_AsymEccKeyCheck(&PublicKey, &PrivateKey);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccKeyCheck(BadArgument1I)=", Status);
        Status = val_AsymEccKeyCheck(&PrivateKey, &PublicKey);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccKeyCheck(BadArgument2I)=", Status);

        (void)val_AsymInitKey(VAL_ASSETID_INVALID, VAL_ASSETID_INVALID,
                              VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA1,
                              &PublicKey);
        Status = val_AsymEccKeyCheck(&PublicKey, &PrivateKey);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccKeyCheck(BadArgument1I)=", Status);
        Status = val_AsymEccKeyCheck(&PrivateKey, &PublicKey);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccKeyCheck(BadArgument2I)=", Status);
    }

    return END_TEST_SUCCES;
}


static int
DoEccEcdsaGenKeyPairTest(
        uint32_t VectorIndex,
        TestVector_ECDSA_t Vector_p)
{
    int rc;
    uint8_t Buffer[(521+7)/8];
    uint8_t * PrivKeyBlob_p;
    ValSize_t PrivKeyBlobSize;
    ValSize_t tempPrivKeyBlobSize;
    uint8_t * AssociatedData_p;
    ValSize_t AssociatedDataSize = strlen(g_ValTestAssociatedData_p);
    ValStatus_t Status;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAsymECCPoint_t Point;
    ValAssetId_t RootAssetId;
    ValAssetId_t KEKAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t DomainAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PublicKeyAssetId = VAL_ASSETID_INVALID;
    ValSymAlgo_t HashAlgorithm;
    ValPolicyMask_t AssetPolicy;
    uint32_t ModulusSizeBits;

    (void)VectorIndex;

    //  Get root key
    RootAssetId = val_AssetGetRootKey();
    unsupported_if((RootAssetId == VAL_ASSETID_INVALID), "No Root key");

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

    /* Load domain parameters */
    rc = test_AsymEccLoadDomain(Vector_p->Curve_p, &DomainAssetId, false);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
    ModulusSizeBits = Vector_p->Curve_p->CurveBits;

    /* Determine Hash algorithm */
    switch (Vector_p->HashBits)
    {
    default:
    case 160:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA1;
        break;
    case 224:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA224;
        break;
    case 256:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA256;
        break;
    }

    /* Allocate the private key asset and initialize key structure */
    Status = val_AsymEcdsaAllocPrivateKeyAsset((ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                               ModulusSizeBits,
                                               HashAlgorithm,
                                               false, false,
                                               &PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaAllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(PrivateKeyAssetId, DomainAssetId,
                             ModulusSizeBits, HashAlgorithm,
                             &PrivateKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    /* Allocate the public key asset and initialize key structure */
    Status = val_AsymEcdsaAllocPublicKeyAsset(ModulusSizeBits,
                                              HashAlgorithm,
                                              false, false,
                                              &PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaAllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(PublicKeyAssetId, DomainAssetId,
                             ModulusSizeBits, HashAlgorithm,
                             &PublicKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    /* Initialize ECC point buffer for public key */
    Point.x.Data_p = Buffer;
    Point.x.ByteDataSize = sizeof(Buffer);
    Point.y.Data_p = Buffer;
    Point.y.ByteDataSize = sizeof(Buffer);

    /* Retrieve private key keyblob size */
    PrivKeyBlobSize = 0;
    Status = val_AsymEccGenKeyPair(&PublicKey, &PrivateKey,
                                   KEKAssetId,
                                   AssociatedData_p, AssociatedDataSize,
                                   &Point,
                                   AssociatedData_p, &PrivKeyBlobSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEccGenKeyPair()=", Status);

    PrivKeyBlobSize = 0;
    Status = val_AsymEccGenKeyPair(&PublicKey, &PrivateKey,
                                   KEKAssetId,
                                   AssociatedData_p, AssociatedDataSize,
                                   &Point,
                                   NULL, &PrivKeyBlobSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEccGenKeyPair()=", Status);
    fail_if(PrivKeyBlobSize != VAL_KEYBLOB_SIZE(VAL_ASYM_DATA_SIZE_B2WB(ModulusSizeBits)+4),
            "Size mismatch ", (int)VAL_KEYBLOB_SIZE(VAL_ASYM_DATA_SIZE_B2WB(ModulusSizeBits)+4));

    PrivKeyBlob_p = (uint8_t *)SFZUTF_MALLOC(PrivKeyBlobSize);
    fail_if(PrivKeyBlob_p == NULL, "Allocation ", (int)PrivKeyBlobSize);

    /* Switch keys */
    tempPrivKeyBlobSize = PrivKeyBlobSize;
    Status = val_AsymEccGenKeyPair(&PrivateKey, &PublicKey,
                                   KEKAssetId,
                                   AssociatedData_p, AssociatedDataSize,
                                   &Point,
                                   PrivKeyBlob_p, &tempPrivKeyBlobSize);
    fail_if(val_CheckFunctionResult(Status) == VAL_SUCCESS, "val_AsymEccGenKeyPair()=", Status);

    /* Generate a key pair */
    Status = val_AsymEccGenKeyPair(&PublicKey, &PrivateKey,
                                   KEKAssetId,
                                   AssociatedData_p, AssociatedDataSize,
                                   &Point,
                                   PrivKeyBlob_p, &PrivKeyBlobSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccGenKeyPair()=", Status);
    fail_if(Point.x.ByteDataSize != VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits),
            "Size mismatch ", (int)VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits));
    fail_if(Point.y.ByteDataSize != VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits),
            "Size mismatch ", (int)VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits));

    /* Clean-up*/
    Status = val_AssetFree(PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

    Status = val_AssetFree(PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

    Status = val_AssetFree(DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

    SFZUTF_FREE(PrivKeyBlob_p);
    SFZUTF_FREE(AssociatedData_p);

    return END_TEST_SUCCES;
}


static int
DoEcdsaTest(uint32_t VectorIndex,
            TestVector_ECDSA_t Vector_p,
            bool fTestKeyPair,
            bool fGenerateKeyPair,
            bool fGeneratePublicKey,
            bool fExplicitDigest,
            bool fUseTokenHashContext)
{
    int rc;
    uint8_t * AssociatedData_p;
    ValSize_t AssociatedDataSize = strlen(g_ValTestAssociatedData_p);
    uint8_t * InCopy_p;
    ValStatus_t Status;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAsymSign_t Signature;
    ValAssetId_t RootAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t KEKAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t DomainAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PublicKeyAssetId = VAL_ASSETID_INVALID;
    ValSymAlgo_t HashAlgorithm;
    uint32_t ModulusSizeBits;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    AssociatedData_p = (uint8_t *)SFZUTF_MALLOC(AssociatedDataSize);
    fail_if(AssociatedData_p == NULL, "Allocation ", (int)AssociatedDataSize);
    memcpy(AssociatedData_p, g_ValTestAssociatedData_p, AssociatedDataSize);

    if ((VectorIndex & 1) != 0U)
    {
        RootAssetId = val_AssetGetRootKey();
        if (RootAssetId != VAL_ASSETID_INVALID)
        {
            ValPolicyMask_t AssetPolicy;

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
    }

    /* Load domain parameters */
    rc = test_AsymEccLoadDomain(Vector_p->Curve_p, &DomainAssetId, false);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
    ModulusSizeBits = Vector_p->Curve_p->CurveBits;

    /* Determine Hash algorithm */
    switch (Vector_p->HashBits)
    {
    case 160:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA1;
        break;
    case 224:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA224;
        break;
    case 256:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA256;
        break;
#ifdef VALTEST_SYM_ALGO_SHA512
    case 384:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA384;
        break;
    case 512:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA512;
        break;
#endif
    default:
        return END_TEST_UNSUPPORTED;
    }

    /* Try to allocate a private/public key with wrong hash */
    Status = val_AsymEcdsaAllocPrivateKeyAsset((ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                               ModulusSizeBits,
                                               VAL_SYM_ALGO_HASH,
                                               false, false,
                                               &PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ALGORITHM, "val_AsymEcdsaAllocPrivateKeyAsset(Wrong Hash)=", Status);

    Status = val_AsymEcdsaAllocPublicKeyAsset(ModulusSizeBits,
                                              VAL_SYM_ALGO_HASH,
                                              false, false,
                                              &PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ALGORITHM, "val_AsymEcdsaAllocPublicKeyAsset(Wrong Hash)=", Status);

    /* Allocate the private key asset and initialize key structure */
    Status = val_AsymEcdsaAllocPrivateKeyAsset((ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                               ModulusSizeBits,
                                               HashAlgorithm,
                                               false, false,
                                               &PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaAllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(PrivateKeyAssetId, DomainAssetId,
                             ModulusSizeBits, HashAlgorithm,
                             &PrivateKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    /* Allocate the public key asset and initialize key structure */
    Status = val_AsymEcdsaAllocPublicKeyAsset(ModulusSizeBits,
                                              HashAlgorithm,
                                              false, false,
                                              &PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaAllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(PublicKeyAssetId, DomainAssetId,
                             ModulusSizeBits, HashAlgorithm,
                             &PublicKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    if (fGenerateKeyPair)
    {
        /* Generate a key pair */
        Status = val_AsymEccGenKeyPair(&PublicKey, &PrivateKey,
                                       VAL_ASSETID_INVALID,
                                       NULL, 0, NULL, NULL, NULL);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccGenKeyPair()=", Status);

        fTestKeyPair = true;            // Force key pair check
    }
    else
    {
        ValAsymBigInt_t BigIntPrivateKey;
        ValAsymECCPoint_t ECCPointPublicKey;

        /* Initialize the private key asset */
        BigIntPrivateKey.Data_p = sfzutf_discard_const(Vector_p->PrivateKey_p);
        BigIntPrivateKey.ByteDataSize = Vector_p->PrivateKeyLen;
        if (KEKAssetId != VAL_ASSETID_INVALID)
        {
            uint8_t * KeyBlob_p;
            ValSize_t KeyBlobSize = 0;

            Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigIntPrivateKey,
                                                             (ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                                             ModulusSizeBits,
                                                             PrivateKeyAssetId,
                                                             KEKAssetId,
                                                             AssociatedData_p, AssociatedDataSize,
                                                             AssociatedData_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEccLoadPrivateKeyAssetPlaintext()=", Status);

            KeyBlobSize = 0;
            Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigIntPrivateKey,
                                                             (ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                                             ModulusSizeBits,
                                                             PrivateKeyAssetId,
                                                             KEKAssetId,
                                                             AssociatedData_p, AssociatedDataSize,
                                                             NULL, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEccLoadPrivateKeyAssetPlaintext()=", Status);

            KeyBlob_p = (uint8_t *)SFZUTF_MALLOC(KeyBlobSize);
            fail_if(KeyBlob_p == NULL, "Allocation ", (int)KeyBlobSize);

            Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigIntPrivateKey,
                                                             (ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                                             ModulusSizeBits,
                                                             PrivateKeyAssetId,
                                                             KEKAssetId,
                                                             AssociatedData_p, AssociatedDataSize,
                                                             KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadPrivateKeyAssetPlaintext()=", Status);

            SFZUTF_FREE(KeyBlob_p);
        }
        else
        {
            Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigIntPrivateKey,
                                                             (ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                                             ModulusSizeBits,
                                                             PrivateKeyAssetId,
                                                             VAL_ASSETID_INVALID,
                                                             NULL, 0, NULL, NULL);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadPrivateKeyAssetPlaintext()=", Status);
        }

        /* Perform a private key check */
#ifdef VALTEST_DOKEYCHECK
        Status = val_AsymEccKeyCheck(NULL, &PrivateKey);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccKeyCheck()=", Status);
#endif

        if (fGeneratePublicKey)
        {
            /* Generate a public key */
            if ((VectorIndex & 1) != 0U)
            {
                Status = val_AsymEccGenPublicKey(&PublicKey, &PrivateKey, NULL);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccGenPublicKey()=", Status);
            }
            else
            {
                ECCPointPublicKey.x.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits);
                ECCPointPublicKey.y.ByteDataSize = ECCPointPublicKey.x.ByteDataSize;
                ECCPointPublicKey.x.Data_p = (uint8_t *)SFZUTF_MALLOC(ECCPointPublicKey.x.ByteDataSize);
                ECCPointPublicKey.y.Data_p = (uint8_t *)SFZUTF_MALLOC(ECCPointPublicKey.y.ByteDataSize);
                fail_if((ECCPointPublicKey.x.Data_p == NULL) ||
                        (ECCPointPublicKey.y.Data_p == NULL),
                        "Allocation ", (int)ECCPointPublicKey.y.ByteDataSize);
                memset(ECCPointPublicKey.x.Data_p, 0, ECCPointPublicKey.x.ByteDataSize);
                memset(ECCPointPublicKey.y.Data_p, 0, ECCPointPublicKey.y.ByteDataSize);

                Status = val_AsymEccGenPublicKey(&PublicKey, &PrivateKey, &ECCPointPublicKey);
                SFZUTF_FREE(ECCPointPublicKey.x.Data_p);
                SFZUTF_FREE(ECCPointPublicKey.y.Data_p);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccGenPublicKey()=", Status);

                /* try to load a second time to improve coverage */
                Status = val_AsymEccGenPublicKey(&PublicKey, &PrivateKey, NULL);
                fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "val_AsymEccGenPublicKey()=", Status);
            }

            fTestKeyPair = true;            // Force key pair check
        }
        else
        {
            ECCPointPublicKey.x.Data_p = sfzutf_discard_const(Vector_p->PublicKeyX_p);
            ECCPointPublicKey.x.ByteDataSize = Vector_p->PublicKeyXLen;
            ECCPointPublicKey.y.Data_p = sfzutf_discard_const(Vector_p->PublicKeyY_p);
            ECCPointPublicKey.y.ByteDataSize = Vector_p->PublicKeyYLen;

            if (KEKAssetId != VAL_ASSETID_INVALID)
            {
                uint8_t * KeyBlob_p;
                ValSize_t KeyBlobSize = 0;

                Status = val_AsymEccLoadPublicKeyAssetPlaintext(&ECCPointPublicKey,
                                                                (ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                                                ModulusSizeBits,
                                                                PublicKeyAssetId,
                                                                KEKAssetId,
                                                                AssociatedData_p, AssociatedDataSize,
                                                                AssociatedData_p, &KeyBlobSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEccLoadPublicKeyAssetPlaintext()=", Status);

                KeyBlobSize = 0;
                Status = val_AsymEccLoadPublicKeyAssetPlaintext(&ECCPointPublicKey,
                                                                (ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                                                ModulusSizeBits,
                                                                PublicKeyAssetId,
                                                                KEKAssetId,
                                                                AssociatedData_p, AssociatedDataSize,
                                                                NULL, &KeyBlobSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEccLoadPublicKeyAssetPlaintext()=", Status);

                KeyBlob_p = (uint8_t *)SFZUTF_MALLOC(KeyBlobSize);
                fail_if(KeyBlob_p == NULL, "Allocation ", (int)KeyBlobSize);

                Status = val_AsymEccLoadPublicKeyAssetPlaintext(&ECCPointPublicKey,
                                                                (ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                                                ModulusSizeBits,
                                                                PublicKeyAssetId,
                                                                KEKAssetId,
                                                                AssociatedData_p, AssociatedDataSize,
                                                                KeyBlob_p, &KeyBlobSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadPublicKeyAssetPlaintext()=", Status);

                SFZUTF_FREE(KeyBlob_p);
            }
            else
            {
                /* Initialize the public key asset */
                Status = val_AsymEccLoadPublicKeyAssetPlaintext(&ECCPointPublicKey,
                                                                (ValAsymECCurveFamily_t)Vector_p->Curve_p->Family,
                                                                ModulusSizeBits,
                                                                PublicKeyAssetId,
                                                                VAL_ASSETID_INVALID,
                                                                NULL, 0, NULL, NULL);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadPublicKeyAssetPlaintext()=", Status);
            }

            /* Perform a public key check */
#ifdef VALTEST_DOKEYCHECK
            Status = val_AsymEccKeyCheck(&PublicKey, NULL);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccKeyCheck()=", Status);
#endif
        }
    }

    if (KEKAssetId != VAL_ASSETID_INVALID)
    {
        // Release the involved Assets
        Status = val_AssetFree(KEKAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(KEK)=", Status);
    }

    /* Perform a full key pair check */
#ifdef VALTEST_DOKEYCHECK
    Status = val_AsymEccKeyCheck(&PublicKey, &PrivateKey);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccKeyCheck()=", Status);

    Status = val_AsymEccKeyCheck(&PrivateKey, &PrivateKey);
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "val_AsymEccKeyCheck()=", Status);
#endif

#ifdef SFZUTF_USERMODE
    InCopy_p = sfzutf_discard_const(Vector_p->Message_p);
#else
    InCopy_p = (uint8_t *)SFZUTF_MALLOC(Vector_p->MessageLen);
    fail_if(InCopy_p == NULL, "Allocation ", (int)Vector_p->MessageLen);
    memcpy(InCopy_p, Vector_p->Message_p, Vector_p->MessageLen);
#endif

    if (fTestKeyPair)
    {
        ValSymContextPtr_t HashContext_p = NULL;
        uint8_t * Data_p = InCopy_p;
        ValSize_t DataLen = Vector_p->MessageLen;

        /* If success expected (test vector contains successful data),
           try test vector also via Sign-Verify. */
        Signature.r.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits);
        Signature.s.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits);

        Signature.r.Data_p = (uint8_t *)SFZUTF_MALLOC(Signature.r.ByteDataSize);
        Signature.s.Data_p = (uint8_t *)SFZUTF_MALLOC(Signature.s.ByteDataSize);
        fail_if((Signature.r.Data_p == NULL) || (Signature.s.Data_p == NULL),
                "Allocation ", (int)Signature.r.ByteDataSize);
        memset(Signature.r.Data_p, 0, Signature.r.ByteDataSize);
        memset(Signature.s.Data_p, 0, Signature.s.ByteDataSize);

        if (fUseTokenHashContext && (DataLen > 4096))
        {
            // Allocate hash context
            Status = val_SymAlloc(HashAlgorithm, VAL_SYM_MODE_NONE, true, &HashContext_p);
            fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

            // Hash a block of data
            Status = val_SymHashUpdate(HashContext_p, Data_p, 4096);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashUpdate()=", Status);

            // Adjust references
            Data_p  += 4096;
            DataLen -= 4096;
        }

        /* Wrong key */
        Status = val_AsymEcdsaSign(&PublicKey, &Signature,
                                   Data_p, DataLen, HashContext_p, false);
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "val_AsymEcdsaSign()=", Status);

        Status = val_AsymEcdsaSign(&PrivateKey, &Signature,
                                   Data_p, DataLen, HashContext_p, false);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaSign()=", Status);
        fail_if(Signature.r.ByteDataSize != VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits),
                "Size mismatch ", VectorIndex);
        fail_if(Signature.s.ByteDataSize != VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits),
                "Size mismatch ", VectorIndex);

        if (fUseTokenHashContext && (DataLen > 4096))
        {
            (void)val_SymRelease(HashContext_p);

            // Restore hash context
            Status = val_SymAlloc(HashAlgorithm, VAL_SYM_MODE_NONE, true, &HashContext_p);
            fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

            // Hash a block of data
            Status = val_SymHashUpdate(HashContext_p, InCopy_p, 4096);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashUpdate()=", Status);
        }

        Signature.r.Data_p[1]++;
        Status = val_AsymEcdsaVerify(&PublicKey, &Signature,
                                     Data_p, DataLen, HashContext_p, false);
        fail_if(val_CheckFunctionResult(Status) != VAL_VERIFY_ERROR, "val_AsymEcdsaVerify()=", Status);
        Signature.r.Data_p[1]--;

        Status = val_AsymEcdsaVerify(&PublicKey, &Signature,
                                     Data_p, DataLen, HashContext_p, false);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaVerify()=", Status);

        SFZUTF_FREE(Signature.r.Data_p);
        SFZUTF_FREE(Signature.s.Data_p);

        if (fUseTokenHashContext && (DataLen > 4096))
        {
            (void)val_SymRelease(HashContext_p);
        }
    }
#ifdef EIP130_ENABLE_EXPLICITDIGEST
    else if (fExplicitDigest)
    {
        ValSymContextPtr_t HashContext_p = NULL;
        ValOctetsOut_t Digest[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
        ValSize_t DigestSize = sizeof(Digest);

        /* If success expected (test vector contains successful data),
           try test vector also via Sign-Verify. */
        Signature.r.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits);
        Signature.s.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits);

        Signature.r.Data_p = (uint8_t *)SFZUTF_MALLOC(Signature.r.ByteDataSize);
        Signature.s.Data_p = (uint8_t *)SFZUTF_MALLOC(Signature.s.ByteDataSize);
        fail_if((Signature.r.Data_p == NULL) || (Signature.s.Data_p == NULL),
                "Allocation ", (int)Signature.r.ByteDataSize);
        memset(Signature.r.Data_p, 0, Signature.r.ByteDataSize);
        memset(Signature.s.Data_p, 0, Signature.s.ByteDataSize);

        // Allocate hash context
        Status = val_SymAlloc(HashAlgorithm, VAL_SYM_MODE_NONE, true, &HashContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

        // Hash a block of data
        Status = val_SymHashFinal(HashContext_p,
                                  InCopy_p, Vector_p->MessageLen,
                                  Digest,  &DigestSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashFinal()=", Status);

        (void)val_SymRelease(HashContext_p);

        Status = val_AsymEcdsaSign(&PrivateKey, &Signature,
                                   Digest, DigestSize, NULL, true);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaSign()=", Status);
        fail_if(Signature.r.ByteDataSize != VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits),
                "Size mismatch ", VectorIndex);
        fail_if(Signature.s.ByteDataSize != VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits),
                "Size mismatch ", VectorIndex);

        Status = val_AsymEcdsaVerify(&PublicKey, &Signature,
                                     Digest, DigestSize, NULL, true);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaVerify()=", Status);

        SFZUTF_FREE(Signature.r.Data_p);
        SFZUTF_FREE(Signature.s.Data_p);
    }
#endif
    else
    {
        /* Build expected result. */
        Signature.r.Data_p = sfzutf_discard_const(Vector_p->SignatureR_p);
        Signature.r.ByteDataSize = Vector_p->SignatureRLen;
        Signature.s.Data_p = sfzutf_discard_const(Vector_p->SignatureS_p);
        Signature.s.ByteDataSize = Vector_p->SignatureSLen;

        /* Wrong key */
        Status = val_AsymEcdsaVerify(&PrivateKey, &Signature,
                                     InCopy_p, Vector_p->MessageLen,
                                     NULL, false);
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "val_AsymEcdsaVerify()=", Status);

        /* Verify test vector. */
        Status = val_AsymEcdsaVerify(&PublicKey, &Signature,
                                     InCopy_p, Vector_p->MessageLen,
                                     NULL, false);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaVerify()=", Status);
    }
#ifndef EIP130_ENABLE_EXPLICITDIGEST
    IDENTIFIER_NOT_USED(fExplicitDigest);
#endif

#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(InCopy_p);
#endif

    SFZUTF_FREE(AssociatedData_p);

    /* Clean-up*/
    Status = val_AssetFree(PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

    Status = val_AssetFree(PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

    Status = val_AssetFree(DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

    return END_TEST_SUCCES;
}


START_TEST (test_AsymEcdsaVectorsParamsCheck)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    for (ndx = 0; ; ndx++)
    {
        TestVector_ECDSA_t vector_p;

        vector_p = test_vectors_ecdsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        if (vector_p->Curve_p->CurveBits >= VAL_ASYM_ECP_MIN_BITS)
        {
            if (DoEccEcdsaParamsTest(ndx, vector_p) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        test_vectors_ecdsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST (test_AsymEcdsaGenKeyPair)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    for (ndx = 0; ; ndx++)
    {
        TestVector_ECDSA_t vector_p;

        vector_p = test_vectors_ecdsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        if ((vector_p->Curve_p->CurveBits >= VAL_ASYM_ECP_MIN_BITS) &&
            (vector_p->Curve_p->CurveBits >= vector_p->HashBits))
        {
            int rc = DoEccEcdsaGenKeyPairTest(ndx, vector_p);
            if ((rc != END_TEST_SUCCES) && (rc != END_TEST_UNSUPPORTED))
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }
        else
        {
            LOG_INFO("SKIPPED: vector %d\n", ndx);
        }

        test_vectors_ecdsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST (test_AsymEcdsaVectorsCheck)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    for (ndx = 0; ; ndx++)
    {
        TestVector_ECDSA_t vector_p;

        vector_p = test_vectors_ecdsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        if ((vector_p->Curve_p->CurveBits >= VAL_ASYM_ECP_MIN_BITS) &&
            (vector_p->Curve_p->CurveBits >= vector_p->HashBits))
        {
            if (DoEcdsaTest(ndx, vector_p, false, false, false, false, false) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        test_vectors_ecdsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST (test_AsymEcdsaVectorsKeyPairCheck)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    for (ndx = 0; ; ndx++)
    {
        TestVector_ECDSA_t vector_p;

        vector_p = test_vectors_ecdsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        if ((vector_p->Curve_p->CurveBits >= VAL_ASYM_ECP_MIN_BITS) &&
            (vector_p->Curve_p->CurveBits >= vector_p->HashBits))
        {
            if (DoEcdsaTest(ndx, vector_p, true, false, false, false, false) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        test_vectors_ecdsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST (test_AsymEcdsaVectorsKeyPairGenCheck)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    for (ndx = 0; ; ndx++)
    {
        TestVector_ECDSA_t vector_p;

        vector_p = test_vectors_ecdsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        if ((vector_p->Curve_p->CurveBits >= VAL_ASYM_ECP_MIN_BITS) &&
            (vector_p->Curve_p->CurveBits >= vector_p->HashBits))
        {
            if (DoEcdsaTest(ndx, vector_p, true, true, false, false, false) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        test_vectors_ecdsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST (test_AsymEcdsaVectorsPublicKeyGenCheck)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    for (ndx = 0; ; ndx++)
    {
        TestVector_ECDSA_t vector_p;

        vector_p = test_vectors_ecdsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        if ((vector_p->Curve_p->CurveBits >= VAL_ASYM_ECP_MIN_BITS) &&
            (vector_p->Curve_p->CurveBits >= vector_p->HashBits))
        {
            if (DoEcdsaTest(ndx, vector_p, true, false, true, false, false) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        test_vectors_ecdsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST (test_AsymEcdsaLongMessageCheck)
{
    bool fUseTokenDigest = false;
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    for (ndx = 0; ; ndx++)
    {
        TestVector_ECDSA_t vector_p;

        vector_p = test_vectors_ecdsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        if ((vector_p->Curve_p->CurveBits >= VAL_ASYM_ECP_MIN_BITS) &&
            (vector_p->Curve_p->CurveBits >= vector_p->HashBits))
        {
            TestVector_ECDSA_Rec_t Vector;
            uint32_t MessageLen = 10 * 1024;
            uint8_t * Message_p = (uint8_t *)SFZUTF_MALLOC(MessageLen);
            fail_if(Message_p == NULL, "Allocation ", (int)MessageLen);

            memset(Message_p, 'a', MessageLen);
            Vector.Message_p = Message_p;
            Vector.MessageLen = MessageLen;
            Vector.Curve_p = vector_p->Curve_p;
            Vector.PrivateKey_p = vector_p->PrivateKey_p;
            Vector.PrivateKeyLen = vector_p->PrivateKeyLen;
            Vector.PublicKeyX_p = vector_p->PublicKeyX_p;
            Vector.PublicKeyXLen = vector_p->PublicKeyXLen;
            Vector.PublicKeyY_p = vector_p->PublicKeyY_p;
            Vector.PublicKeyYLen = vector_p->PublicKeyYLen;
            Vector.HashBits = vector_p->HashBits;
            Vector.SignatureR_p = NULL;
            Vector.SignatureRLen = 0;
            Vector.SignatureS_p = NULL;
            Vector.SignatureSLen = 0;

            if (DoEcdsaTest(ndx, &Vector, true, false, false, false, fUseTokenDigest) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
                if (fUseTokenDigest)
                {
                    fUseTokenDigest = false;
                }
                else
                {
                    fUseTokenDigest = true;
                }
            }

            SFZUTF_FREE(Message_p);
        }

        test_vectors_ecdsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

#ifdef EIP130_ENABLE_EXPLICITDIGEST
START_TEST (test_AsymEcdsaExplicitDigest)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    for (ndx = 0; ; ndx++)
    {
        TestVector_ECDSA_t vector_p;

        vector_p = test_vectors_ecdsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        if ((vector_p->Curve_p->CurveBits >= VAL_ASYM_ECP_MIN_BITS) &&
            (vector_p->Curve_p->CurveBits >= vector_p->HashBits))
        {
            TestVector_ECDSA_Rec_t Vector;
            uint32_t MessageLen = 10 * 1024;
            uint8_t * Message_p = (uint8_t *)SFZUTF_MALLOC(MessageLen);
            fail_if(Message_p == NULL, "Allocation ", (int)MessageLen);

            memset(Message_p, 'a', MessageLen);
            Vector.Message_p = Message_p;
            Vector.MessageLen = MessageLen;
            Vector.Curve_p = vector_p->Curve_p;
            Vector.PrivateKey_p = vector_p->PrivateKey_p;
            Vector.PrivateKeyLen = vector_p->PrivateKeyLen;
            Vector.PublicKeyX_p = vector_p->PublicKeyX_p;
            Vector.PublicKeyXLen = vector_p->PublicKeyXLen;
            Vector.PublicKeyY_p = vector_p->PublicKeyY_p;
            Vector.PublicKeyYLen = vector_p->PublicKeyYLen;
            Vector.HashBits = vector_p->HashBits;
            Vector.SignatureR_p = NULL;
            Vector.SignatureRLen = 0;
            Vector.SignatureS_p = NULL;
            Vector.SignatureSLen = 0;

            if (DoEcdsaTest(ndx, &Vector, false, false, false, true, false) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }

            SFZUTF_FREE(Message_p);
        }

        test_vectors_ecdsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif

START_TEST(test_AsymEcdsaArguments)
{
    uint8_t Buffer[4];
    ValSize_t Size = 32;
    ValAssetId_t AssetId = 0x5001;
    ValAsymKey_t Key;
    ValAsymSign_t Sign;
    ValStatus_t Status;

    // ECC part
    if (test_AsymEccArguments() != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }

    // ECDSA part
    // - val_AsymEcdsaAllocPrivateKeyAsset
    Status = val_AsymEcdsaAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS-1, VAL_SYM_ALGO_HASH_SHA1, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPrivateKeyAsset(BadArgument1L)=", Status);

    Status = val_AsymEcdsaAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MAX_BITS+1, VAL_SYM_ALGO_HASH_SHA1, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPrivateKeyAsset(BadArgument1H)=", Status);

    Status = val_AsymEcdsaAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA224, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPrivateKeyAsset(BadArgument2I)=", Status);

    Status = val_AsymEcdsaAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA256, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPrivateKeyAsset(BadArgument2I)=", Status);

#ifdef VALTEST_SYM_ALGO_SHA512
    Status = val_AsymEcdsaAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA384, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPrivateKeyAsset(BadArgument2I)=", Status);

    Status = val_AsymEcdsaAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA512, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPrivateKeyAsset(BadArgument2I)=", Status);
#endif

    Status = val_AsymEcdsaAllocPrivateKeyAsset(VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA1, false, false, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPrivateKeyAsset(BadArgument3)=", Status);

    // - val_AsymEcdsaAllocPublicKeyAsset
    Status = val_AsymEcdsaAllocPublicKeyAsset(VAL_ASYM_ECP_MIN_BITS-1, VAL_SYM_ALGO_HASH_SHA1, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPublicKeyAsset(BadArgument1L)=", Status);

    Status = val_AsymEcdsaAllocPublicKeyAsset(VAL_ASYM_ECP_MAX_BITS+1, VAL_SYM_ALGO_HASH_SHA1, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPublicKeyAsset(BadArgument1H)=", Status);

    Status = val_AsymEcdsaAllocPublicKeyAsset(VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA224, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPublicKeyAsset(BadArgument2I)=", Status);

    Status = val_AsymEcdsaAllocPublicKeyAsset(VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA256, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPublicKeyAsset(BadArgument2I)=", Status);

#ifdef VALTEST_SYM_ALGO_SHA512
    Status = val_AsymEcdsaAllocPublicKeyAsset(VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA384, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPublicKeyAsset(BadArgument2I)=", Status);

    Status = val_AsymEcdsaAllocPublicKeyAsset(VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA512, false, false, &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPublicKeyAsset(BadArgument2I)=", Status);
#endif

    Status = val_AsymEcdsaAllocPublicKeyAsset(VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA1, false, false, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaAllocPublicKeyAsset(BadArgument3)=", Status);

    // - val_AsymEcdsaSign/val_AsymEcdsaVerify
    Sign.r.Data_p = Buffer;
    Sign.r.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);
    Sign.s.Data_p = Buffer;
    Sign.s.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);

    Status = val_AsymEcdsaSign(NULL, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1)=", Status);
    Status = val_AsymEcdsaVerify(NULL, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1)=", Status);

    Key.KeyAssetId = VAL_ASSETID_INVALID;
    Key.DomainAssetId = AssetId;
    Key.ModulusSizeBits = VAL_ASYM_ECP_MIN_BITS;
    Key.HashAlgorithm = VAL_SYM_ALGO_HASH_SHA1;

    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);
    Key.KeyAssetId = AssetId;

    Key.DomainAssetId = VAL_ASSETID_INVALID;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);
    Key.DomainAssetId = AssetId;

    Key.ModulusSizeBits = VAL_ASYM_ECP_MIN_BITS-1;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);

    Key.ModulusSizeBits = VAL_ASYM_ECP_MAX_BITS+1;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);
    Key.ModulusSizeBits = VAL_ASYM_ECP_MIN_BITS;

    Key.HashAlgorithm = VAL_SYM_ALGO_HASH_MAX;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);

    Size = 8096;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);
    Size = 32;

    Key.HashAlgorithm = VAL_SYM_ALGO_HASH_SHA224;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);

    Key.HashAlgorithm = VAL_SYM_ALGO_HASH_SHA256;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);

#ifdef VALTEST_SYM_ALGO_SHA512
    Key.HashAlgorithm = VAL_SYM_ALGO_HASH_SHA384;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);

    Key.HashAlgorithm = VAL_SYM_ALGO_HASH_SHA512;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument1I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument1I)=", Status);
#endif

    Key.HashAlgorithm = VAL_SYM_ALGO_HASH_SHA1;

    Status = val_AsymEcdsaSign(&Key, NULL, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument2)=", Status);
    Status = val_AsymEcdsaVerify(&Key, NULL, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument2)=", Status);

    Sign.r.Data_p = NULL;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument2I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument2I)=", Status);
    Sign.r.Data_p = Buffer;

    Sign.r.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS) - 1;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument2I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument2I)=", Status);
    Sign.r.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);

    Sign.s.Data_p = NULL;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument2I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument2I)=", Status);
    Sign.s.Data_p = Buffer;

    Sign.s.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS) - 1;
    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument2I)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument2I)=", Status);
    Sign.s.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);

    Status = val_AsymEcdsaSign(&Key, &Sign, NULL, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument2)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, NULL, Size, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument2)=", Status);

    Status = val_AsymEcdsaSign(&Key, &Sign, Buffer, 0, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaSign(BadArgument4L)=", Status);
    Status = val_AsymEcdsaVerify(&Key, &Sign, Buffer, 0, NULL, false);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEcdsaVerify(BadArgument4L)=", Status);
}
END_TEST


START_TEST(test_AsymEcdsaVectorsInitKey)
{
    ValAssetId_t AssetId = 0x5001;
    ValAsymKey_t Key;
    ValStatus_t Status;

    // General function
    // - val_AsymInitKey
    Status = val_AsymInitKey(AssetId, AssetId, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH, &Key);
    fail_if(Status != VAL_INVALID_ALGORITHM, "val_AsymInitKey(InvalidAlgorithm4)=", Status);
}
END_TEST

START_TEST(test_AsymEcdsaCurveCheck)
{
    ValAssetId_t DomainAssetId;
    ValStatus_t Status;

    /* Load domain parameters for all supported NIST curves */
    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_NIST_P, 192, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(N192)=", Status);
    (void)val_AssetFree(DomainAssetId);

    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_NIST_P, 224, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(N224)=", Status);
    (void)val_AssetFree(DomainAssetId);

    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_NIST_P, 256, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(N256)=", Status);
    (void)val_AssetFree(DomainAssetId);

    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_NIST_P, 384, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(N384)=", Status);
    (void)val_AssetFree(DomainAssetId);

    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_NIST_P, 521, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(N521)=", Status);
    (void)val_AssetFree(DomainAssetId);

    /* -> Negative test for coverage */
    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_NIST_P, 512, &DomainAssetId);
    fail_if(Status >= VAL_SUCCESS, "val_AsymEccInstallCurve(N512)=", Status);

    /* Load domain parameters for all supported BrainPool curves */
    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_BRAINPOOL_R1, 192, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(BP192)=", Status);
    (void)val_AssetFree(DomainAssetId);

    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_BRAINPOOL_R1, 224, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(BP224)=", Status);
    (void)val_AssetFree(DomainAssetId);

    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_BRAINPOOL_R1, 256, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(BP256)=", Status);
    (void)val_AssetFree(DomainAssetId);

    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_BRAINPOOL_R1, 384, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(BP384)=", Status);
    (void)val_AssetFree(DomainAssetId);

    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_BRAINPOOL_R1, 512, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve(BP512)=", Status);
    (void)val_AssetFree(DomainAssetId);

    /* -> Negative test for coverage */
    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_BRAINPOOL_R1, 521, &DomainAssetId);
    fail_if(Status >= VAL_SUCCESS, "val_AsymEccInstallCurve(BP521)=", Status);
}
END_TEST


int
suite_add_test_AsymEcdsa(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "AsymCrypto_ECDSA_Vectors");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaVectorsParamsCheck) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaGenKeyPair) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaVectorsCheck) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaVectorsKeyPairCheck) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaVectorsKeyPairGenCheck) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaVectorsPublicKeyGenCheck) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaLongMessageCheck) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaVectorsInitKey) != 0) goto FuncErrorReturn;
#ifdef EIP130_ENABLE_EXPLICITDIGEST
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaExplicitDigest) != 0) goto FuncErrorReturn;
#endif
        if (sfzutf_test_add(TestCase_p, test_AsymEcdsaCurveCheck) != 0) goto FuncErrorReturn;
        if (valtest_StrictArgsCheck())
        {
            if (sfzutf_test_add(TestCase_p, test_AsymEcdsaArguments) != 0) goto FuncErrorReturn;
        }
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_asym_ecdsa.c */
