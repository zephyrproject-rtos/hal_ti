/* valtest_asym_eddsa.c
 *
 * Description: EsDSA tests
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

/* Test vectors. */
#include "testvectors_eddsa.h"

/* Test helper functions. */
#include "valtest_asym_ecc_common.h"


#ifdef VALTEST_ASYM_EDDSA
static int
DoEddsaTest(uint32_t VectorIndex,
            TestVector_EdDSA_t Vector_p,
            bool fTestKeyPair,
            bool fGenerateKeyPair,
            bool fGeneratePublicKey)
{
    uint8_t * AssociatedData_p;
    ValSize_t AssociatedDataSize = strlen(g_ValTestAssociatedData_p);
    ValStatus_t Status;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAsymSign_t Signature;
    ValAssetId_t RootAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t KEKAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t DomainAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PublicKeyAssetId = VAL_ASSETID_INVALID;
    uint32_t ModulusSizeBits = 255U;

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

    /* Negative load domain parameters check (coverage) */
    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_TWISTED_EDWARDS, 448, &DomainAssetId);
    fail_if(Status >= VAL_SUCCESS, "val_AsymEccInstallCurve(448)=", Status);

    /* Load domain parameters */
    Status = val_AsymEccInstallCurve(VAL_ECC_FAMILY_TWISTED_EDWARDS,
                                     ModulusSizeBits, &DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccInstallCurve()=", Status);

    /* Allocate the private key asset and initialize key structure */
    Status = val_AsymEddsaAllocPrivateKeyAsset(false, false, &PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaAllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(PrivateKeyAssetId, DomainAssetId,
                             ModulusSizeBits, VAL_SYM_ALGO_HASH_SHA512,
                             &PrivateKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    /* Allocate the public key asset and initialize key structure */
    Status = val_AsymEddsaAllocPublicKeyAsset(false, false, &PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEcdsaAllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(PublicKeyAssetId, DomainAssetId,
                             ModulusSizeBits, VAL_SYM_ALGO_HASH_SHA512,
                             &PublicKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    if (fGenerateKeyPair)
    {
        /* Generate a key pair */
        Status = val_AsymEddsaGenKeyPair(&PublicKey, &PrivateKey,
                                         VAL_ASSETID_INVALID,
                                         NULL, 0, NULL, NULL, NULL);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEddsaGenKeyPair()=", Status);

        fTestKeyPair = true;            // Force key pair check
    }
    else
    {
        ValAsymBigInt_t BigIntPrivateKey;
        ValAsymBigInt_t BigIntPublicKey;

        /* Initialize the private key asset */
        BigIntPrivateKey.Data_p = sfzutf_discard_const(Vector_p->PrivateKey_p);
        BigIntPrivateKey.ByteDataSize = Vector_p->PrivateKeyLen;
        if (KEKAssetId != VAL_ASSETID_INVALID)
        {
            uint8_t * KeyBlob_p;
            ValSize_t KeyBlobSize = 0;

            Status = val_AsymEddsaLoadKeyAssetPlaintext(&BigIntPrivateKey,
                                                        PrivateKeyAssetId,
                                                        KEKAssetId,
                                                        AssociatedData_p, AssociatedDataSize,
                                                        AssociatedData_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEddsaLoadKeyAssetPlaintext()=", Status);

            KeyBlobSize = 0;
            Status = val_AsymEddsaLoadKeyAssetPlaintext(&BigIntPrivateKey,
                                                        PrivateKeyAssetId,
                                                        KEKAssetId,
                                                        AssociatedData_p, AssociatedDataSize,
                                                        NULL, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEddsaLoadKeyAssetPlaintext()=", Status);

            KeyBlob_p = (uint8_t *)SFZUTF_MALLOC(KeyBlobSize);
            fail_if(KeyBlob_p == NULL, "Allocation ", (int)KeyBlobSize);

            Status = val_AsymEddsaLoadKeyAssetPlaintext(&BigIntPrivateKey,
                                                        PrivateKeyAssetId,
                                                        KEKAssetId,
                                                        AssociatedData_p, AssociatedDataSize,
                                                        KeyBlob_p, &KeyBlobSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEddsaLoadKeyAssetPlaintext()=", Status);

            SFZUTF_FREE(KeyBlob_p);
        }
        else
        {
            Status = val_AsymEddsaLoadKeyAssetPlaintext(&BigIntPrivateKey,
                                                        PrivateKeyAssetId,
                                                        VAL_ASSETID_INVALID,
                                                        NULL, 0, NULL, NULL);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEddsaLoadKeyAssetPlaintext()=", Status);
        }

        if (fGeneratePublicKey)
        {
            /* Generate a public key */
            BigIntPublicKey.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits);
            BigIntPublicKey.Data_p = (uint8_t *)SFZUTF_MALLOC(BigIntPublicKey.ByteDataSize);
            fail_if((BigIntPublicKey.Data_p == NULL),
                    "Allocation ", (int)BigIntPublicKey.ByteDataSize);
            memset(BigIntPublicKey.Data_p, 0, BigIntPublicKey.ByteDataSize);

            Status = val_AsymEddsaGenPublicKey(&PublicKey, &PrivateKey, NULL);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccGenPublicKey()=", Status);

            SFZUTF_FREE(BigIntPublicKey.Data_p);
        }
        else
        {
            BigIntPublicKey.Data_p = sfzutf_discard_const(Vector_p->PublicKey_p);
            BigIntPublicKey.ByteDataSize = Vector_p->PublicKeyLen;
            if (KEKAssetId != VAL_ASSETID_INVALID)
            {
                uint8_t * KeyBlob_p;
                ValSize_t KeyBlobSize = 0;

                Status = val_AsymEddsaLoadKeyAssetPlaintext(&BigIntPublicKey,
                                                            PublicKeyAssetId,
                                                            KEKAssetId,
                                                            AssociatedData_p, AssociatedDataSize,
                                                            AssociatedData_p, &KeyBlobSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEddsaLoadKeyAssetPlaintext()=", Status);

                KeyBlobSize = 0;
                Status = val_AsymEddsaLoadKeyAssetPlaintext(&BigIntPublicKey,
                                                            PublicKeyAssetId,
                                                            KEKAssetId,
                                                            AssociatedData_p, AssociatedDataSize,
                                                            NULL, &KeyBlobSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEddsaLoadKeyAssetPlaintext()=", Status);

                KeyBlob_p = (uint8_t *)SFZUTF_MALLOC(KeyBlobSize);
                fail_if(KeyBlob_p == NULL, "Allocation ", (int)KeyBlobSize);

                Status = val_AsymEddsaLoadKeyAssetPlaintext(&BigIntPublicKey,
                                                            PublicKeyAssetId,
                                                            KEKAssetId,
                                                            AssociatedData_p, AssociatedDataSize,
                                                            KeyBlob_p, &KeyBlobSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEddsaLoadKeyAssetPlaintext()=", Status);

                SFZUTF_FREE(KeyBlob_p);
            }
            else
            {
                /* Initialize the public key asset */
                Status = val_AsymEddsaLoadKeyAssetPlaintext(&BigIntPublicKey,
                                                            PublicKeyAssetId,
                                                            VAL_ASSETID_INVALID,
                                                            NULL, 0, NULL, NULL);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEddsaLoadKeyAssetPlaintext()=", Status);
            }
        }
    }

    if (KEKAssetId != VAL_ASSETID_INVALID)
    {
        // Release the involved Assets
        Status = val_AssetFree(KEKAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(KEK)=", Status);
    }

    if (fTestKeyPair)
    {
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

        Status = val_AsymEddsaSign(&PrivateKey, &PublicKey, &Signature,
                                   Vector_p->Message_p, Vector_p->MessageLen);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEddsaSign()=", Status);
        fail_if(Signature.r.ByteDataSize != VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits),
                "Size mismatch ", VectorIndex);
        fail_if(Signature.s.ByteDataSize != VAL_ASYM_DATA_SIZE_B2B(ModulusSizeBits),
                "Size mismatch ", VectorIndex);

        Signature.r.Data_p[1]++;
        Status = val_AsymEddsaVerify(&PublicKey, &Signature,
                                     Vector_p->Message_p, Vector_p->MessageLen);
        fail_if(val_CheckFunctionResult(Status) != VAL_VERIFY_ERROR, "val_AsymEddsaVerify()=", Status);
        Signature.r.Data_p[1]--;

        Status = val_AsymEddsaVerify(&PublicKey, &Signature,
                                     Vector_p->Message_p, Vector_p->MessageLen);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEddsaVerify()=", Status);

        SFZUTF_FREE(Signature.r.Data_p);
        SFZUTF_FREE(Signature.s.Data_p);
    }
    else
    {
        /* Build expected result. */
        Signature.r.Data_p = sfzutf_discard_const(Vector_p->SignatureR_p);
        Signature.r.ByteDataSize = Vector_p->SignatureRLen;
        Signature.s.Data_p = sfzutf_discard_const(Vector_p->SignatureS_p);
        Signature.s.ByteDataSize = Vector_p->SignatureSLen;

        /* Verify test vector. */
        Status = val_AsymEddsaVerify(&PublicKey, &Signature,
                                     Vector_p->Message_p, Vector_p->MessageLen);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEddsaVerify()=", Status);
    }

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
#endif


START_TEST(test_AsymEddsaVectorsCheck)
{
#ifdef VALTEST_ASYM_EDDSA
    uint32_t ndx;
    int rc = END_TEST_SUCCES;
    int Success = 0;
    int Failed = 0;
    bool fTestKeyPair = false;
    bool fGenerateKeyPair = false;
    bool fGeneratePublicKey = false;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    if (_i == 1)
    {
        fTestKeyPair = true;
    }
    if (_i == 2)
    {
        fGenerateKeyPair = true;
    }
    if (_i == 3)
    {
        fTestKeyPair = true;
        fGeneratePublicKey = true;
    }

    for (ndx = 0U; ; ndx++)
    {
        TestVector_EdDSA_t vector_p;

        vector_p = test_vectors_eddsa_get(ndx);
        if (vector_p == NULL)
        {
            break;
        }

        rc = DoEddsaTest(ndx, vector_p,
                         fTestKeyPair, fGenerateKeyPair, fGeneratePublicKey);
        if (rc != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }

        test_vectors_eddsa_release(vector_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
#else
    return END_TEST_UNSUPPORTED;
#endif
}
END_TEST


START_TEST (test_AsymEddsaLongMessageCheck)
{
#ifdef VALTEST_ASYM_EDDSA
    int rc = END_TEST_SUCCES;
    TestVector_EdDSA_Rec_t Vector;
    uint32_t MessageLen = 10 * 1024;
    uint8_t * Message_p;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    Message_p = (uint8_t *)SFZUTF_MALLOC(MessageLen);
    fail_if(Message_p == NULL, "Allocation ", (int)MessageLen);
    memset(Message_p, 'a', MessageLen);
    memset(&Vector, 0, sizeof(Vector));
    Vector.Message_p = Message_p;
    Vector.MessageLen = MessageLen;

    rc = DoEddsaTest(0, &Vector, false, true, false);

    SFZUTF_FREE(Message_p);

    fail_if(rc, "#wrong tests", 1);
#else
    return END_TEST_UNSUPPORTED;
#endif
}
END_TEST


int
suite_add_test_AsymEddsa(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "AsymCrypto_EdDSA_Vectors");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_AsymEddsaVectorsCheck, 4) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymEddsaLongMessageCheck) != 0) goto FuncErrorReturn;
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_asym_ecdsa.c */
