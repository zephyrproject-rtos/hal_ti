/* valtest_asym_rsa.c
 *
 * Description: RSA tests
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

#include "testvectors_rsa.h"


/*----------------------------------------------------------------------------
 * test_release_key
 *
 * Helper function that releases the key related assets.
 */
static void
test_release_key(
    ValAsymKey_t * Key_p)
{
    if (Key_p->DomainAssetId != VAL_ASSETID_INVALID)
    {
        (void)val_AssetFree(Key_p->DomainAssetId);
        Key_p->DomainAssetId = VAL_ASSETID_INVALID;
    }
    if (Key_p->KeyAssetId != VAL_ASSETID_INVALID)
    {
        (void)val_AssetFree(Key_p->KeyAssetId);
        Key_p->KeyAssetId = VAL_ASSETID_INVALID;
    }
}

/*----------------------------------------------------------------------------
 * test_load_rsa_pkcs1v15_privkey
 *
 * Helper function that allocates and initializes the RSA PKCS#1v1.5 private
 * key.
 */
static int
test_load_rsa_pkcs1v15_privkey(
    TestVector_RSA_PKCS1v15_t tv_p,
    ValAsymKey_t * PrivateKey_p)
{
    ValStatus_t Status;
    ValSymAlgo_t HashAlgorithm;
    ValAssetId_t AssetId;
    ValAsymBigInt_t ModulusData;
    ValAsymBigInt_t ExponentData;

    switch (tv_p->HashBits)
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

    Status = val_AsymRsaPkcs1v15AllocPrivateKeyAsset(tv_p->ModulusBits,
                                                     (tv_p->Key.PrivateExponentBytes*8),
                                                     HashAlgorithm,
                                                     false, false,
                                                     &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPkcs1v15AllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(AssetId, VAL_ASSETID_INVALID,
                             tv_p->ModulusBits, HashAlgorithm,
                             PrivateKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    ModulusData.ByteDataSize = tv_p->Key.ModulusBytes;
    ExponentData.ByteDataSize = tv_p->Key.PrivateExponentBytes;
#ifdef SFZUTF_USERMODE
    ModulusData.Data_p = sfzutf_discard_const(tv_p->Key.Modulus_p);
    ExponentData.Data_p = sfzutf_discard_const(tv_p->Key.PrivateExponent_p);
#else
    ModulusData.Data_p = (uint8_t *)SFZUTF_MALLOC(ModulusData.ByteDataSize);
    fail_if(ModulusData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ModulusData.Data_p, tv_p->Key.Modulus_p, ModulusData.ByteDataSize);
    ExponentData.Data_p = (uint8_t *)SFZUTF_MALLOC(ExponentData.ByteDataSize);
    fail_if(ExponentData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ExponentData.Data_p, tv_p->Key.PrivateExponent_p, ExponentData.ByteDataSize);
#endif
    Status = val_AsymRsaLoadKeyAssetPlaintext(&ModulusData,
                                              tv_p->ModulusBits,
                                              &ExponentData,
                                              (tv_p->Key.PrivateExponentBytes*8),
                                              AssetId,
                                              VAL_ASSETID_INVALID,
                                              NULL, 0, NULL, 0);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(ExponentData.Data_p);
    SFZUTF_FREE(ModulusData.Data_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaLoadKeyAssetPlaintext()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_load_rsa_pkcs1v15_pubkey
 *
 * Helper function that allocates and initializes the RSA PKCS#1v1.5 public
 * key.
 */
static int
test_load_rsa_pkcs1v15_pubkey(
        TestVector_RSA_PKCS1v15_t tv_p,
        ValAsymKey_t * PublicKey_p)
{
    ValStatus_t Status;
    ValSymAlgo_t HashAlgorithm;
    ValAssetId_t AssetId;
    ValAsymBigInt_t ModulusData;
    ValAsymBigInt_t ExponentData;

    switch (tv_p->HashBits)
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

    Status = val_AsymRsaPkcs1v15AllocPublicKeyAsset(tv_p->ModulusBits,
                                                    (tv_p->Key.PublicExponentBytes*8),
                                                    HashAlgorithm,
                                                    false, false,
                                                    &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPkcs1v15AllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(AssetId, VAL_ASSETID_INVALID,
                             tv_p->ModulusBits, HashAlgorithm,
                             PublicKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    ModulusData.ByteDataSize = tv_p->Key.ModulusBytes;
    ExponentData.ByteDataSize = tv_p->Key.PublicExponentBytes;
#ifdef SFZUTF_USERMODE
    ModulusData.Data_p = sfzutf_discard_const(tv_p->Key.Modulus_p);
    ExponentData.Data_p = sfzutf_discard_const(tv_p->Key.PublicExponent_p);
#else
    ModulusData.Data_p = SFZUTF_MALLOC(ModulusData.ByteDataSize);
    fail_if(ModulusData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ModulusData.Data_p, tv_p->Key.Modulus_p, ModulusData.ByteDataSize);
    ExponentData.Data_p = SFZUTF_MALLOC(ExponentData.ByteDataSize);
    fail_if(ExponentData.Data_p == NULL, "Allocation ", (int)ExponentData.ByteDataSize);
    memcpy(ExponentData.Data_p, tv_p->Key.PublicExponent_p, ExponentData.ByteDataSize);
#endif

    Status = val_AsymRsaLoadKeyAssetPlaintext(&ModulusData,
                                              tv_p->ModulusBits,
                                              &ExponentData,
                                              (tv_p->Key.PublicExponentBytes*8),
                                              AssetId,
                                              VAL_ASSETID_INVALID,
                                              NULL, 0, NULL, 0);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(ExponentData.Data_p);
    SFZUTF_FREE(ModulusData.Data_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaLoadKeyAssetPlaintext()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_pkcs1v15_sign
 *
 * Helper function that performs the RSA PKCS#1v1.5 signature generation
 * operation.
 */
static int
test_rsa_pkcs1v15_sign(
        TestVector_RSA_PKCS1v15_t tv_p,
        ValAsymKey_t * PrivateKey_p,
        ValAsymBigInt_t * Signature_p)
{
    uint8_t * Msg_p;
    ValStatus_t Status;

#ifdef SFZUTF_USERMODE
    Msg_p = sfzutf_discard_const(tv_p->Msg_p);
#else
    Msg_p = SFZUTF_MALLOC(tv_p->MsgBytes);
    fail_if(Msg_p == NULL, "Allocation ", (int)tv_p->MsgBytes);
    memcpy(Msg_p, tv_p->Msg_p, tv_p->MsgBytes);
#endif
    Status = val_AsymRsaPkcs1v15Sign(PrivateKey_p, Signature_p,
                                     Msg_p, tv_p->MsgBytes, NULL, false);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(Msg_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPkcs1v15Sign()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_pkcs1v15_verify
 *
 * Helper function that performs the RSA PKCS#1v1.5 signature verify operation.
 */
static int
test_rsa_pkcs1v15_verify(
        TestVector_RSA_PKCS1v15_t tv_p,
        ValAsymKey_t * PublicKey_p,
        ValAsymBigInt_t * Signature_p)
{
    uint8_t * Msg_p;
    ValStatus_t Status;

#ifdef SFZUTF_USERMODE
    Msg_p = sfzutf_discard_const(tv_p->Msg_p);
#else
    Msg_p = SFZUTF_MALLOC(tv_p->MsgBytes);
    fail_if(Msg_p == NULL, "Allocation ", (int)tv_p->MsgBytes);
    memcpy(Msg_p, tv_p->Msg_p, tv_p->MsgBytes);
#endif
    Status = val_AsymRsaPkcs1v15Verify(PublicKey_p, Signature_p,
                                       Msg_p, tv_p->MsgBytes, NULL, false);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(Msg_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPkcs1v15Verify()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_pkcs1v15
 *
 * Helper function that performs tests for all RSA PKCS#1v1.5 test vectors
 * with the specified modulus (ModulusBits). The Iteration specifies which
 * test must be performed.
 */
static int
test_rsa_pkcs1v15(
        uint32_t ModulusBits,
        int Iteration)
{
    uint32_t Index;
    int Success = 0;
    int Failed = 0;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAsymBigInt_t Signature;

    PrivateKey.DomainAssetId = VAL_ASSETID_INVALID;
    PrivateKey.KeyAssetId = VAL_ASSETID_INVALID;
    PublicKey.DomainAssetId = VAL_ASSETID_INVALID;
    PublicKey.KeyAssetId = VAL_ASSETID_INVALID;

    for (Index = 0U; ; Index++)
    {
        TestVector_RSA_PKCS1v15_t tv_p;
        int rc = END_TEST_FAIL;

        tv_p = test_vectors_rsa_pkcs1v15_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->ModulusBits == ModulusBits)
        {
            Signature.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(tv_p->ModulusBits);
            Signature.Data_p = SFZUTF_MALLOC(Signature.ByteDataSize);
            if (Signature.Data_p != NULL)
            {
                switch (Iteration)
                {
                case 0:
                    // Verify only
                    rc = test_load_rsa_pkcs1v15_pubkey(tv_p, &PublicKey);
                    if (rc == END_TEST_SUCCES)
                    {
                        if (tv_p->SignatureBytes > Signature.ByteDataSize)
                        {
                            rc = END_TEST_FAIL;
                        }
                        else
                        {
                            memcpy(Signature.Data_p, tv_p->Signature_p, tv_p->SignatureBytes);
                            Signature.ByteDataSize = tv_p->SignatureBytes;
                            rc = test_rsa_pkcs1v15_verify(tv_p, &PublicKey, &Signature);
                        }
                    }
                    if ((rc == END_TEST_SUCCES) || g_ValTestCleanUp)
                    {
                        test_release_key(&PublicKey);
                    }
                    break;

                case 1:
                    // Sign-verify
                    rc = test_load_rsa_pkcs1v15_privkey(tv_p, &PrivateKey);
                    if (rc == END_TEST_SUCCES)
                    {
                        rc = test_load_rsa_pkcs1v15_pubkey(tv_p, &PublicKey);
                    }
                    if (rc == END_TEST_SUCCES)
                    {
                        rc = test_rsa_pkcs1v15_sign(tv_p, &PrivateKey, &Signature);
                    }
                    if (rc == END_TEST_SUCCES)
                    {
                        rc = test_rsa_pkcs1v15_verify(tv_p, &PublicKey, &Signature);
                    }
                    if ((rc == END_TEST_SUCCES) || g_ValTestCleanUp)
                    {
                        test_release_key(&PublicKey);
                        test_release_key(&PrivateKey);
                    }
                    break;

                default:
                    break;
                }
                SFZUTF_FREE(Signature.Data_p);
            }
            if (rc == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }
        }

        test_vectors_rsa_pkcs1v15_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }

    return END_TEST_SUCCES;
}

START_TEST(test_rsa_pkcs1v15_1024)
{
    int rc = test_rsa_pkcs1v15(1024, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_pkcs1v15_2048)
{
    int rc = test_rsa_pkcs1v15(2048, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_pkcs1v15_3072)
{
    int rc = test_rsa_pkcs1v15(3072, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


/*----------------------------------------------------------------------------
 * test_load_rsa_pss_privkey
 *
 * Helper function that allocates and initializes the RSA PSS private key.
 */
static int
test_load_rsa_pss_privkey(
    TestVector_RSA_PSS_t tv_p,
    ValAsymKey_t * PrivateKey_p)
{
    ValStatus_t Status;
    ValSymAlgo_t HashAlgorithm;
    ValAssetId_t AssetId;
    ValAsymBigInt_t ModulusData;
    ValAsymBigInt_t ExponentData;

    switch (tv_p->HashBits)
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

    Status = val_AsymRsaPssAllocPrivateKeyAsset(tv_p->ModulusBits,
                                                (tv_p->Key.PrivateExponentBytes*8),
                                                HashAlgorithm,
                                                false, false,
                                                &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPssAllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(AssetId, VAL_ASSETID_INVALID,
                             tv_p->ModulusBits, HashAlgorithm,
                             PrivateKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    ModulusData.ByteDataSize = tv_p->Key.ModulusBytes;
    ExponentData.ByteDataSize = tv_p->Key.PrivateExponentBytes;
#ifdef SFZUTF_USERMODE
    ModulusData.Data_p = sfzutf_discard_const(tv_p->Key.Modulus_p);
    ExponentData.Data_p = sfzutf_discard_const(tv_p->Key.PrivateExponent_p);
#else
    ModulusData.Data_p = SFZUTF_MALLOC(ModulusData.ByteDataSize);
    fail_if(ModulusData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ModulusData.Data_p, tv_p->Key.Modulus_p, ModulusData.ByteDataSize);
    ExponentData.Data_p = SFZUTF_MALLOC(ExponentData.ByteDataSize);
    fail_if(ExponentData.Data_p == NULL, "Allocation ", (int)ExponentData.ByteDataSize);
    memcpy(ExponentData.Data_p, tv_p->Key.PrivateExponent_p, ExponentData.ByteDataSize);
#endif
    Status = val_AsymRsaLoadKeyAssetPlaintext(&ModulusData,
                                              tv_p->ModulusBits,
                                              &ExponentData,
                                              (tv_p->Key.PrivateExponentBytes*8),
                                              AssetId,
                                              VAL_ASSETID_INVALID,
                                              NULL, 0, NULL, 0);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(ExponentData.Data_p);
    SFZUTF_FREE(ModulusData.Data_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaLoadKeyAssetPlaintext()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_load_rsa_pss_pubkey
 *
 * Helper function that allocates and initializes the RSA PSS public key.
 */
static int
test_load_rsa_pss_pubkey(
        TestVector_RSA_PSS_t tv_p,
        ValAsymKey_t * PublicKey_p)
{
    ValStatus_t Status;
    ValSymAlgo_t HashAlgorithm;
    ValAssetId_t AssetId;
    ValAsymBigInt_t ModulusData;
    ValAsymBigInt_t ExponentData;

    switch (tv_p->HashBits)
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

    Status = val_AsymRsaPssAllocPublicKeyAsset(tv_p->ModulusBits,
                                               (tv_p->Key.PublicExponentBytes*8),
                                               HashAlgorithm,
                                               false, false,
                                               &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPssAllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(AssetId, VAL_ASSETID_INVALID,
                             tv_p->ModulusBits, HashAlgorithm,
                             PublicKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    ModulusData.ByteDataSize = tv_p->Key.ModulusBytes;
    ExponentData.ByteDataSize = tv_p->Key.PublicExponentBytes;
#ifdef SFZUTF_USERMODE
    ModulusData.Data_p = sfzutf_discard_const(tv_p->Key.Modulus_p);
    ExponentData.Data_p = sfzutf_discard_const(tv_p->Key.PublicExponent_p);
#else
    ModulusData.Data_p = SFZUTF_MALLOC(ModulusData.ByteDataSize);
    fail_if(ModulusData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ModulusData.Data_p, tv_p->Key.Modulus_p, ModulusData.ByteDataSize);
    ExponentData.Data_p = SFZUTF_MALLOC(ExponentData.ByteDataSize);
    fail_if(ExponentData.Data_p == NULL, "Allocation ", (int)ExponentData.ByteDataSize);
    memcpy(ExponentData.Data_p, tv_p->Key.PublicExponent_p, ExponentData.ByteDataSize);
#endif
    Status = val_AsymRsaLoadKeyAssetPlaintext(&ModulusData,
                                              tv_p->ModulusBits,
                                              &ExponentData,
                                              (tv_p->Key.PublicExponentBytes*8),
                                              AssetId,
                                              VAL_ASSETID_INVALID,
                                              NULL, 0, NULL, 0);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(ExponentData.Data_p);
    SFZUTF_FREE(ModulusData.Data_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaLoadKeyAssetPlaintext()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_pss_sign
 *
 * Helper function that performs the RSA PSS signature generation operation.
 */
static int
test_rsa_pss_sign(
        TestVector_RSA_PSS_t tv_p,
        ValAsymKey_t * PrivateKey_p,
        ValAsymBigInt_t * Signature_p)
{
    ValStatus_t Status;
    uint8_t * Msg_p;

#ifdef SFZUTF_USERMODE
    Msg_p = sfzutf_discard_const(tv_p->Msg_p);
#else
    Msg_p = SFZUTF_MALLOC(tv_p->MsgBytes);
    fail_if((Msg_p == NULL), "Allocation ", (int)tv_p->MsgBytes);
    memcpy(Msg_p, tv_p->Msg_p, tv_p->MsgBytes);
#endif
    Status = val_AsymRsaPssSign(PrivateKey_p, Signature_p,
                                Msg_p, tv_p->MsgBytes, NULL,
                                (tv_p->HashBits/8), false);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(Msg_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPssSign()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_pss_verify
 *
 * Helper function that performs the RSA PSS signature verify operation.
 */
static int
test_rsa_pss_verify(
        TestVector_RSA_PSS_t tv_p,
        ValAsymKey_t * PublicKey_p,
        ValAsymBigInt_t * Signature_p)
{
    ValStatus_t Status;
    uint8_t * Msg_p;

#ifdef SFZUTF_USERMODE
    Msg_p = sfzutf_discard_const(tv_p->Msg_p);
#else
    Msg_p = SFZUTF_MALLOC(tv_p->MsgBytes);
    fail_if((Msg_p == NULL), "Allocation ", (int)tv_p->MsgBytes);
    memcpy(Msg_p, tv_p->Msg_p, tv_p->MsgBytes);
#endif
    Status = val_AsymRsaPssVerify(PublicKey_p, Signature_p,
                                  Msg_p, tv_p->MsgBytes, NULL,
                                  (tv_p->HashBits/8), false);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(Msg_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPssVerify()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_pss
 *
 * Helper function that performs tests for all RSA PSS test vectors with the
 * specified modulus (ModulusBits). The Iteration specifies which test must be
 * performed.
 */
static int
test_rsa_pss(
        uint32_t ModulusBits,
        int Iteration)
{
    uint32_t Index;
    int Success = 0;
    int Failed = 0;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAsymBigInt_t Signature;

    if (Iteration)
    {
        unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");
    }

    PrivateKey.DomainAssetId = VAL_ASSETID_INVALID;
    PrivateKey.KeyAssetId = VAL_ASSETID_INVALID;
    PublicKey.DomainAssetId = VAL_ASSETID_INVALID;
    PublicKey.KeyAssetId = VAL_ASSETID_INVALID;

    for (Index = 0U; ; Index++)
    {
        TestVector_RSA_PSS_t tv_p;
        int rc = END_TEST_FAIL;

        tv_p = test_vectors_rsa_pss_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->ModulusBits == ModulusBits)
        {
            Signature.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(tv_p->ModulusBits);
            Signature.Data_p = SFZUTF_MALLOC(Signature.ByteDataSize);
            if (Signature.Data_p != NULL)
            {
                switch (Iteration)
                {
                case 0:                     // Verify only
                    rc = test_load_rsa_pss_pubkey(tv_p, &PublicKey);
                    if (rc == END_TEST_SUCCES)
                    {
                        if (tv_p->SignatureBytes > Signature.ByteDataSize)
                        {
                            rc = END_TEST_FAIL;
                        }
                        else
                        {
                            memcpy(Signature.Data_p, tv_p->Signature_p, tv_p->SignatureBytes);
                            Signature.ByteDataSize = tv_p->SignatureBytes;
                            rc = test_rsa_pss_verify(tv_p, &PublicKey, &Signature);
                        }
                    }
                    if ((rc == END_TEST_SUCCES) || g_ValTestCleanUp)
                    {
                        test_release_key(&PublicKey);
                    }
                    break;

                case 1:                     // Sign-verify
                    rc = test_load_rsa_pss_privkey(tv_p, &PrivateKey);
                    if (rc == END_TEST_SUCCES)
                    {
                        rc = test_load_rsa_pss_pubkey(tv_p, &PublicKey);
                    }
                    if (rc == END_TEST_SUCCES)
                    {
                        rc = test_rsa_pss_sign(tv_p, &PrivateKey, &Signature);
                    }
                    if (rc == END_TEST_SUCCES)
                    {
                        rc = test_rsa_pss_verify(tv_p, &PublicKey, &Signature);
                    }
                    if ((rc == END_TEST_SUCCES) || g_ValTestCleanUp)
                    {
                        test_release_key(&PublicKey);
                        test_release_key(&PrivateKey);
                    }
                    break;

                default:
                    break;
                }
                SFZUTF_FREE(Signature.Data_p);
            }
            if (rc == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }
        }

        test_vectors_rsa_pss_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }

    return END_TEST_SUCCES;
}

START_TEST(test_rsa_pss_1024)
{
    int rc = test_rsa_pss(1024, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_pss_2048)
{
    int rc = test_rsa_pss(2048, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_pss_3072)
{
    int rc = test_rsa_pss(3072, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


/*----------------------------------------------------------------------------
 * test_load_rsa_oaep_privkey
 *
 * Helper function that allocates and initializes the RSA OAEP private key.
 */
static int
test_load_rsa_oaep_privkey(
    TestVector_RSA_OAEP_t tv_p,
    ValAsymKey_t * PrivateKey_p)
{
    ValStatus_t Status;
    ValSymAlgo_t HashAlgorithm;
    ValAssetId_t AssetId;
    ValAsymBigInt_t ModulusData;
    ValAsymBigInt_t ExponentData;

    switch (tv_p->HashBits)
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
        LOG_CRIT("%s:%d> FAILED: Invalid hash bits (%d)\n",
                 __func__, __LINE__, tv_p->HashBits);
        return END_TEST_UNSUPPORTED;
    }

    Status = val_AsymRsaOaepAllocPrivateKeyAsset(tv_p->ModulusBits,
                                                 (tv_p->Key.PrivateExponentBytes*8),
                                                 HashAlgorithm,
                                                 false, false, false,
                                                 &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaOaepAllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(AssetId, VAL_ASSETID_INVALID,
                             tv_p->ModulusBits, HashAlgorithm,
                             PrivateKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    ModulusData.ByteDataSize = tv_p->Key.ModulusBytes;
    ExponentData.ByteDataSize = tv_p->Key.PrivateExponentBytes;
#ifdef SFZUTF_USERMODE
    ModulusData.Data_p = sfzutf_discard_const(tv_p->Key.Modulus_p);
    ExponentData.Data_p = sfzutf_discard_const(tv_p->Key.PrivateExponent_p);
#else
    ModulusData.Data_p = SFZUTF_MALLOC(ModulusData.ByteDataSize);
    fail_if(ModulusData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ModulusData.Data_p, tv_p->Key.Modulus_p, ModulusData.ByteDataSize);
    ExponentData.Data_p = SFZUTF_MALLOC(ExponentData.ByteDataSize);
    fail_if(ExponentData.Data_p == NULL, "Allocation ", (int)ExponentData.ByteDataSize);
    memcpy(ExponentData.Data_p, tv_p->Key.PrivateExponent_p, ExponentData.ByteDataSize);
#endif
    Status = val_AsymRsaLoadKeyAssetPlaintext(&ModulusData,
                                              tv_p->ModulusBits,
                                              &ExponentData,
                                              (tv_p->Key.PrivateExponentBytes*8),
                                              AssetId,
                                              VAL_ASSETID_INVALID,
                                              NULL, 0, NULL, 0);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(ExponentData.Data_p);
    SFZUTF_FREE(ModulusData.Data_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaLoadKeyAssetPlaintext()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_load_rsa_oaep_pubkey
 *
 * Helper function that allocates and initializes the RSA OAEP public key.
 */
static int
test_load_rsa_oaep_pubkey(
        TestVector_RSA_OAEP_t tv_p,
        ValAsymKey_t * PublicKey_p)
{
    ValStatus_t Status;
    ValSymAlgo_t HashAlgorithm;
    ValAssetId_t AssetId;
    ValAsymBigInt_t ModulusData;
    ValAsymBigInt_t ExponentData;

    switch (tv_p->HashBits)
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
        LOG_CRIT("%s:%d> FAILED: Invalid hash bits (%d)\n",
                 __func__, __LINE__, tv_p->HashBits);
        return END_TEST_UNSUPPORTED;
    }

    Status = val_AsymRsaOaepAllocPublicKeyAsset(tv_p->ModulusBits,
                                                (tv_p->Key.PublicExponentBytes*8),
                                                HashAlgorithm,
                                                false, false,
                                                &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaOaepAllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(AssetId, VAL_ASSETID_INVALID,
                             tv_p->ModulusBits, HashAlgorithm,
                             PublicKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    ModulusData.ByteDataSize = tv_p->Key.ModulusBytes;
    ExponentData.ByteDataSize = tv_p->Key.PublicExponentBytes;
#ifdef SFZUTF_USERMODE
    ModulusData.Data_p = sfzutf_discard_const(tv_p->Key.Modulus_p);
    ExponentData.Data_p = sfzutf_discard_const(tv_p->Key.PublicExponent_p);
#else
    ModulusData.Data_p = SFZUTF_MALLOC(ModulusData.ByteDataSize);
    fail_if(ModulusData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ModulusData.Data_p, tv_p->Key.Modulus_p, ModulusData.ByteDataSize);
    ExponentData.Data_p = SFZUTF_MALLOC(ExponentData.ByteDataSize);
    fail_if(ExponentData.Data_p == NULL, "Allocation ", (int)ExponentData.ByteDataSize);
    memcpy(ExponentData.Data_p, tv_p->Key.PublicExponent_p, ExponentData.ByteDataSize);
#endif
    Status = val_AsymRsaLoadKeyAssetPlaintext(&ModulusData,
                                              tv_p->ModulusBits,
                                              &ExponentData,
                                              (tv_p->Key.PublicExponentBytes*8),
                                              AssetId,
                                              VAL_ASSETID_INVALID,
                                              NULL, 0, NULL, 0);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(ExponentData.Data_p);
    SFZUTF_FREE(ModulusData.Data_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaLoadKeyAssetPlaintext()=", Status);

    return END_TEST_SUCCES;
}

static int
test_rsa_oaep_init_key(
        TestVector_RSA_OAEP_t tv_p,
        ValAssetId_t * AssetId_p,
        bool fVerify,
        bool fLoad)
{
    ValStatus_t Status;
    ValPolicyMask_t AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH;

    if (fVerify)
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
    }
    else
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
    }

    switch (tv_p->HashBits)
    {
    case 160:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA1;
        break;
    case 224:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA224;
        break;
    case 256:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA256;
        break;
    case 384:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA384;
        break;
    case 512:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA512;
        break;
    default:
        LOG_CRIT("%s:%d> FAILED: Invalid hash bits (%d)\n",
                 __func__, __LINE__, tv_p->HashBits);
        return END_TEST_FAIL;
    }
    if (fLoad)
    {
        AssetPolicy |= EIP130_ASSET_POLICY_EXPORTABLE;
    }
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }

    Status = val_AssetAlloc(AssetPolicy, tv_p->PlainDataBytes,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            AssetId_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

    if (fLoad)
    {
#ifdef SFZUTF_USERMODE
        uint8_t * Key_p = sfzutf_discard_const(tv_p->PlainData_p);
#else
       uint8_t * Key_p = (uint8_t *)SFZUTF_MALLOC(tv_p->PlainDataBytes);
       fail_if(Key_p == NULL, "Allocation ", (int)tv_p->PlainDataBytes);
       memcpy(Key_p, tv_p->PlainData_p, tv_p->PlainDataBytes);
#endif
       Status = val_AssetLoadPlaintext(*AssetId_p, Key_p, tv_p->PlainDataBytes);
#ifndef SFZUTF_USERMODE
       SFZUTF_FREE(Key_p);
#endif
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(Key)=", Status);
    }

    return END_TEST_SUCCES;
}

static int
test_rsa_oaep_wrap(
        TestVector_RSA_OAEP_t tv_p,
        ValAsymKey_t * Key_p,
        ValAssetId_t AssetId,
        bool fHash,
        bool fUnwrap)
{
    uint8_t * WrappedData_p;
    uint8_t * AdditionalInput_p;
    ValStatus_t Status;

    WrappedData_p = SFZUTF_MALLOC(tv_p->WrappedDataBytes);
    fail_if(WrappedData_p == NULL, "Allocation ", (int)tv_p->WrappedDataBytes);
    if (fUnwrap)
    {
        memcpy(WrappedData_p, tv_p->WrappedData_p, tv_p->WrappedDataBytes);
    }

    if (fUnwrap)
    {
        if (fHash)
        {
#ifdef SFZUTF_USERMODE
            AdditionalInput_p = sfzutf_discard_const(tv_p->AdditionalInputHash_p);
#else
            AdditionalInput_p = SFZUTF_MALLOC(tv_p->AdditionalInputHashBytes);
            fail_if(AdditionalInput_p == NULL, "Allocation ", (int)tv_p->AdditionalInputHashBytes);
            memcpy(AdditionalInput_p, tv_p->AdditionalInputHash_p, tv_p->AdditionalInputHashBytes);
#endif
            Status = val_AsymRsaOaepUnwrapHash(Key_p, AssetId,
                                               AdditionalInput_p, tv_p->AdditionalInputHashBytes,
                                               WrappedData_p, tv_p->WrappedDataBytes);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaOaepUnwrapHash()=", Status);
        }
        else
        {
#ifdef SFZUTF_USERMODE
            AdditionalInput_p = sfzutf_discard_const(tv_p->AdditionalInput_p);
#else
            AdditionalInput_p = SFZUTF_MALLOC(tv_p->AdditionalInputBytes);
            fail_if(AdditionalInput_p == NULL, "Allocation ", (int)tv_p->AdditionalInputBytes);
            memcpy(AdditionalInput_p, tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes);
#endif
            Status = val_AsymRsaOaepUnwrapString(Key_p, AssetId,
                                                 AdditionalInput_p, tv_p->AdditionalInputBytes,
                                                 WrappedData_p, tv_p->WrappedDataBytes);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaOaepUnwrapString()=", Status);
        }
    }
    else
    {
        if (fHash)
        {
#ifdef SFZUTF_USERMODE
            AdditionalInput_p = sfzutf_discard_const(tv_p->AdditionalInputHash_p);
#else
            AdditionalInput_p = SFZUTF_MALLOC(tv_p->AdditionalInputHashBytes);
            fail_if(AdditionalInput_p == NULL, "Allocation ", (int)tv_p->AdditionalInputHashBytes);
            memcpy(AdditionalInput_p, tv_p->AdditionalInputHash_p, tv_p->AdditionalInputHashBytes);
#endif
            Status = val_AsymRsaOaepWrapHash(Key_p, AssetId,
                                             AdditionalInput_p, tv_p->AdditionalInputHashBytes,
                                             WrappedData_p, tv_p->WrappedDataBytes);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaOaepWrapHash()=", Status);
        }
        else
        {
#ifdef SFZUTF_USERMODE
            AdditionalInput_p = sfzutf_discard_const(tv_p->AdditionalInput_p);
#else
            AdditionalInput_p = SFZUTF_MALLOC(tv_p->AdditionalInputBytes);
            fail_if(AdditionalInput_p == NULL, "Allocation ", (int)tv_p->AdditionalInputBytes);
            memcpy(AdditionalInput_p, tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes);
#endif
            Status = val_AsymRsaOaepWrapString(Key_p, AssetId,
                                               AdditionalInput_p, tv_p->AdditionalInputBytes,
                                               WrappedData_p, tv_p->WrappedDataBytes);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaOaepWrapString()=", Status);
        }

        //Log_HexDump("WrappedData:", 0, WrappedData_p, tv_p->WrappedDataBytes);
    }

#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(AdditionalInput_p);
#endif
    SFZUTF_FREE(WrappedData_p);

    return END_TEST_SUCCES;
}

static int
test_rsa_hmac_check(
        uint32_t HashBits,
        ValAssetId_t AssetId,
        uint8_t * MacBuffer,
        uint8_t * MacCheck)
{
    static const char message[] = "This some text to do the HMAC...";
    ValSymContextPtr_t SymContext_p = NULL;
    ValSymAlgo_t Algorithm;
    ValStatus_t Status;
    ValSize_t MacSizeExpected = 0;
    uint8_t * Message_p;

    switch (HashBits)
    {
    case 160:
        Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA1;
        MacSizeExpected = (160/8);
        break;
    case 224:
        Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA224;
        MacSizeExpected = (224/8);
        break;
    case 256:
        Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA256;
        MacSizeExpected = (256/8);
        break;
    case 384:
        Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA384;
        MacSizeExpected = (384/8);
        break;
    case 512:
        Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA512;
        MacSizeExpected = (512/8);
        break;
    default:
        LOG_CRIT("%s:%d> FAILED: Invalid hash bits (%d)\n",
                 __func__, __LINE__, HashBits);
        return END_TEST_FAIL;
    }

    Status = val_SymAlloc(Algorithm, VAL_SYM_MODE_NONE, false, &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymInitKey(SymContext_p, AssetId, NULL, 0);
    fail_if(Status != VAL_SUCCESS, "val_SymInitKey()=", Status);

#ifdef SFZUTF_USERMODE
    Message_p = sfzutf_discard_const(message);
#else
    Message_p = (uint8_t *)SFZUTF_MALLOC(sizeof(message));
    fail_if(Message_p == NULL, "Allocation ", (int)sizeof(message));
    memcpy(Message_p, message, sizeof(message));
#endif

    if (MacBuffer != NULL)
    {
        ValSize_t MacSize = VAL_SYM_ALGO_MAX_DIGEST_SIZE;

        Status = val_SymMacGenerate(SymContext_p,
                                    Message_p, sizeof(message),
                                    MacBuffer, &MacSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacGenerate()=", Status);
        fail_if(MacSize != MacSizeExpected, "Wrong MAC size ", (int)MacSize);
    }
    else
    {
        fail_if(MacCheck == NULL, "Expected check information", 0);

        Status = val_SymMacVerify(SymContext_p,
                                  Message_p, sizeof(message),
                                  VAL_ASSETID_INVALID,
                                  MacCheck, MacSizeExpected);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacVerify()=", Status);
    }

    Status = val_SymRelease(SymContext_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacVerify()=", Status);

#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(Message_p);
#endif

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_oaep
 *
 * Helper function that performs tests for all RSA OAEP test vectors with the
 * specified modulus (ModulusBits). The Iteration specifies which test must be
 * performed.
 */
static int
test_rsa_oaep(
        uint32_t ModulusBits)
{
    uint32_t Index;
    int Success = 0;
    int Failed = 0;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAssetId_t AssetIdWrapKey;
    ValAssetId_t AssetIdUnwrapKeyString;
    ValAssetId_t AssetIdUnwrapKeyHash;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    PrivateKey.DomainAssetId = VAL_ASSETID_INVALID;
    PrivateKey.KeyAssetId = VAL_ASSETID_INVALID;
    PublicKey.DomainAssetId = VAL_ASSETID_INVALID;
    PublicKey.KeyAssetId = VAL_ASSETID_INVALID;
    AssetIdWrapKey = VAL_ASSETID_INVALID;
    AssetIdUnwrapKeyString = VAL_ASSETID_INVALID;
    AssetIdUnwrapKeyHash = VAL_ASSETID_INVALID;

    for (Index = 0U; ; Index++)
    {
        TestVector_RSA_OAEP_t tv_p;
        int rc = END_TEST_FAIL;

        tv_p = test_vectors_rsa_oaep_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->ModulusBits == ModulusBits)
        {
            // Create and load Private Key asset
            rc = test_load_rsa_oaep_privkey(tv_p, &PrivateKey);
            if (rc == END_TEST_SUCCES)
            {
                // Create and load Public Key asset
                rc = test_load_rsa_oaep_pubkey(tv_p, &PublicKey);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Create and load key for wrapping
                rc = test_rsa_oaep_init_key(tv_p, &AssetIdWrapKey, false, true);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Create key for unwrapping with string
                rc = test_rsa_oaep_init_key(tv_p, &AssetIdUnwrapKeyString, true, false);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Create key for unwrapping with hash
                rc = test_rsa_oaep_init_key(tv_p, &AssetIdUnwrapKeyHash, true, false);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Wrap key with string
                rc = test_rsa_oaep_wrap(tv_p, &PublicKey, AssetIdWrapKey, false, false);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Wrap key with hash
                rc = test_rsa_oaep_wrap(tv_p, &PublicKey, AssetIdWrapKey, true, false);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Unwrap key with string
                rc = test_rsa_oaep_wrap(tv_p, &PrivateKey, AssetIdUnwrapKeyString, false, true);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Unwrap key with hash
                rc = test_rsa_oaep_wrap(tv_p, &PrivateKey, AssetIdUnwrapKeyHash, true, true);
            }
            if (rc == END_TEST_SUCCES)
            {
                uint8_t MacRef[VAL_SYM_ALGO_MAX_DIGEST_SIZE];

                // Verify unwrap operations
                rc = test_rsa_hmac_check(tv_p->HashBits, AssetIdWrapKey, MacRef, NULL);
                if (rc == END_TEST_SUCCES)
                {
                    rc = test_rsa_hmac_check(tv_p->HashBits, AssetIdUnwrapKeyString, NULL, MacRef);
                }
                if (rc == END_TEST_SUCCES)
                {
                    rc = test_rsa_hmac_check(tv_p->HashBits, AssetIdUnwrapKeyHash, NULL, MacRef);
                }
            }

            // Clean-up assets
            if ((rc == END_TEST_SUCCES) || g_ValTestCleanUp)
            {
                if (AssetIdWrapKey != VAL_ASSETID_INVALID)
                {
                    (void)val_AssetFree(AssetIdWrapKey);
                    AssetIdWrapKey = VAL_ASSETID_INVALID;
                }
                if (AssetIdUnwrapKeyString != VAL_ASSETID_INVALID)
                {
                    (void)val_AssetFree(AssetIdUnwrapKeyString);
                    AssetIdUnwrapKeyString = VAL_ASSETID_INVALID;
                }
                if (AssetIdUnwrapKeyHash != VAL_ASSETID_INVALID)
                {
                    (void)val_AssetFree(AssetIdUnwrapKeyHash);
                    AssetIdUnwrapKeyHash = VAL_ASSETID_INVALID;
                }
                test_release_key(&PublicKey);
                test_release_key(&PrivateKey);
            }

            if (rc == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }
        }

        test_vectors_rsa_oaep_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }

    return END_TEST_SUCCES;
}

START_TEST(test_rsa_oaep_1024)
{
    int rc = test_rsa_oaep(1024);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_oaep_2048)
{
    int rc = test_rsa_oaep(2048);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_oaep_3072)
{
    int rc = test_rsa_oaep(3072);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


/*----------------------------------------------------------------------------
 * test_rsa_pkcs1v15wrap_privkey
 *
 * Helper function that allocates and initializes the RSA PKCS#1v1.5 wrap
 * private key.
 */
static int
test_rsa_pkcs1v15wrap_privkey(
    TestVector_PKCS1V15WRAP_t tv_p,
    ValAsymKey_t * PrivateKey_p,
    bool fAllowAny)
{
    ValStatus_t Status;
    ValAssetId_t AssetId;
    ValAsymBigInt_t ModulusData;
    ValAsymBigInt_t ExponentData;

    Status = val_AsymRsaPkcs1v15WrapAllocPrivateKeyAsset(tv_p->ModulusBits,
                                                         (tv_p->Key.PrivateExponentBytes*8),
                                                         false, false, fAllowAny,
                                                         &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
            "val_AsymRsaPkcs1v15WrapAllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(AssetId, VAL_ASSETID_INVALID,
                             tv_p->ModulusBits, VAL_SYM_ALGO_NONE,
                             PrivateKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    ModulusData.ByteDataSize = tv_p->Key.ModulusBytes;
    ExponentData.ByteDataSize = tv_p->Key.PrivateExponentBytes;
#ifdef SFZUTF_USERMODE
    ModulusData.Data_p = sfzutf_discard_const(tv_p->Key.Modulus_p);
    ExponentData.Data_p = sfzutf_discard_const(tv_p->Key.PrivateExponent_p);
#else
    ModulusData.Data_p = SFZUTF_MALLOC(ModulusData.ByteDataSize);
    fail_if(ModulusData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ModulusData.Data_p, tv_p->Key.Modulus_p, ModulusData.ByteDataSize);
    ExponentData.Data_p = SFZUTF_MALLOC(ExponentData.ByteDataSize);
    fail_if(ExponentData.Data_p == NULL, "Allocation ", (int)ExponentData.ByteDataSize);
    memcpy(ExponentData.Data_p, tv_p->Key.PrivateExponent_p, ExponentData.ByteDataSize);
#endif
    Status = val_AsymRsaLoadKeyAssetPlaintext(&ModulusData,
                                              tv_p->ModulusBits,
                                              &ExponentData,
                                              (tv_p->Key.PrivateExponentBytes*8),
                                              AssetId,
                                              VAL_ASSETID_INVALID,
                                              NULL, 0, NULL, 0);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(ExponentData.Data_p);
    SFZUTF_FREE(ModulusData.Data_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaLoadKeyAssetPlaintext()=", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_pkcs1v15wrap_pubkey
 *
 * Helper function that allocates and initializes the RSA PKCS#1v1.5 wrap
 * public key.
 */
static int
test_rsa_pkcs1v15wrap_pubkey(
        TestVector_PKCS1V15WRAP_t tv_p,
        ValAsymKey_t * PublicKey_p)
{
    ValStatus_t Status;
    ValAssetId_t AssetId;
    ValAsymBigInt_t ModulusData;
    ValAsymBigInt_t ExponentData;

    Status = val_AsymRsaPkcs1v15WrapAllocPublicKeyAsset(tv_p->ModulusBits,
                                                        (tv_p->Key.PublicExponentBytes*8),
                                                        false, false,
                                                        &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
            "val_AsymRsaPkcs1v15WrapAllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(AssetId, VAL_ASSETID_INVALID,
                             tv_p->ModulusBits, VAL_SYM_ALGO_NONE,
                             PublicKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    ModulusData.ByteDataSize = tv_p->Key.ModulusBytes;
    ExponentData.ByteDataSize = tv_p->Key.PublicExponentBytes;
#ifdef SFZUTF_USERMODE
    ModulusData.Data_p = sfzutf_discard_const(tv_p->Key.Modulus_p);
    ExponentData.Data_p = sfzutf_discard_const(tv_p->Key.PublicExponent_p);
#else
    ModulusData.Data_p = SFZUTF_MALLOC(ModulusData.ByteDataSize);
    fail_if(ModulusData.Data_p == NULL, "Allocation ", (int)ModulusData.ByteDataSize);
    memcpy(ModulusData.Data_p, tv_p->Key.Modulus_p, ModulusData.ByteDataSize);
    ExponentData.Data_p = SFZUTF_MALLOC(ExponentData.ByteDataSize);
    fail_if(ExponentData.Data_p == NULL, "Allocation ", (int)ExponentData.ByteDataSize);
    memcpy(ExponentData.Data_p, tv_p->Key.PublicExponent_p, ExponentData.ByteDataSize);
#endif
    Status = val_AsymRsaLoadKeyAssetPlaintext(&ModulusData,
                                              tv_p->ModulusBits,
                                              &ExponentData,
                                              (tv_p->Key.PublicExponentBytes*8),
                                              AssetId,
                                              VAL_ASSETID_INVALID,
                                              NULL, 0, NULL, 0);
#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(ExponentData.Data_p);
    SFZUTF_FREE(ModulusData.Data_p);
#endif
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaLoadKeyAssetPlaintext()=", Status);

    return END_TEST_SUCCES;
}

static int
test_rsa_pkcs1v15wrap_init_key(
        TestVector_PKCS1V15WRAP_t tv_p,
        ValAssetId_t * AssetId_p,
        bool fVerify,
        bool fLoad)
{
    ValStatus_t Status;
    ValPolicyMask_t AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH;

    if (fVerify)
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
    }
    else
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
    }

    switch (tv_p->HashBits)
    {
    case 160:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA1;
        break;
    case 224:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA224;
        break;
    case 256:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA256;
        break;
    case 384:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA384;
        break;
    case 512:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA512;
        break;
    default:
        LOG_CRIT("%s:%d> FAILED: Invalid hash bits (%d)\n",
                 __func__, __LINE__, tv_p->HashBits);
        return END_TEST_FAIL;
    }
    if (fLoad)
    {
        AssetPolicy |= EIP130_ASSET_POLICY_EXPORTABLE;
    }
    if (!val_IsAccessSecure())
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
    }

    Status = val_AssetAlloc(AssetPolicy, tv_p->PlainDataBytes,
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            AssetId_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

    if (fLoad)
    {
#ifdef SFZUTF_USERMODE
        uint8_t * Key_p = sfzutf_discard_const(tv_p->PlainData_p);
#else
       uint8_t * Key_p = (uint8_t *)SFZUTF_MALLOC(tv_p->PlainDataBytes);
       fail_if(Key_p == NULL, "Allocation ", (int)tv_p->PlainDataBytes);
       memcpy(Key_p, tv_p->PlainData_p, tv_p->PlainDataBytes);
#endif
       Status = val_AssetLoadPlaintext(*AssetId_p, Key_p, tv_p->PlainDataBytes);
#ifndef SFZUTF_USERMODE
       SFZUTF_FREE(Key_p);
#endif
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(Key)=", Status);
    }

    return END_TEST_SUCCES;
}

static int
test_rsa_pkcs1v15wrap_wrap(
        TestVector_PKCS1V15WRAP_t tv_p,
        ValAsymKey_t * Key_p,
        ValAssetId_t AssetId,
        bool fUnwrap)
{
    uint8_t * WrappedData_p = NULL;
    ValStatus_t Status;

    WrappedData_p = SFZUTF_MALLOC(tv_p->WrappedDataBytes);
    fail_if(WrappedData_p == NULL, "Allocation ", (int)tv_p->WrappedDataBytes);

    if (fUnwrap)
    {
        (void)memcpy(WrappedData_p, tv_p->WrappedData_p, tv_p->WrappedDataBytes);

        Status = val_AsymRsaPkcs1v15Unwrap(Key_p, AssetId,
                                           WrappedData_p, tv_p->WrappedDataBytes);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPkcs1v15Unwrap()=", Status);
    }
    else
    {
        (void)memset(WrappedData_p, 0, tv_p->WrappedDataBytes);
        Status = val_AsymRsaPkcs1v15Wrap(Key_p, AssetId,
                                         WrappedData_p, tv_p->WrappedDataBytes);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPkcs1v15Wrap()=", Status);
    }

    SFZUTF_FREE(WrappedData_p);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_rsa_pkcs1v15wrap
 *
 * Helper function that performs tests for all RSA PKCS#1v1.5 wrap test vectors
 * with the specified modulus (ModulusBits). The Iteration specifies which test
 * must be performed.
 */
static int
test_rsa_pkcs1v15wrap(
        uint32_t ModulusBits)
{
    uint32_t Index;
    int Success = 0;
    int Failed = 0;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAssetId_t AssetIdWrapKey;
    ValAssetId_t AssetIdUnwrapKey;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    PrivateKey.DomainAssetId = VAL_ASSETID_INVALID;
    PrivateKey.KeyAssetId = VAL_ASSETID_INVALID;
    PublicKey.DomainAssetId = VAL_ASSETID_INVALID;
    PublicKey.KeyAssetId = VAL_ASSETID_INVALID;
    AssetIdWrapKey = VAL_ASSETID_INVALID;
    AssetIdUnwrapKey = VAL_ASSETID_INVALID;

    for (Index = 0U; ; Index++)
    {
        TestVector_PKCS1V15WRAP_t tv_p;
        int rc = END_TEST_FAIL;

        tv_p = test_vectors_rsa_pkcs1v15wrap_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->ModulusBits == ModulusBits)
        {
            // Create and load Private Key asset
            rc = test_rsa_pkcs1v15wrap_privkey(tv_p, &PrivateKey, false);
            if (rc == END_TEST_SUCCES)
            {
                // Create and load Public Key asset
                rc = test_rsa_pkcs1v15wrap_pubkey(tv_p, &PublicKey);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Create and load key for wrapping
                rc = test_rsa_pkcs1v15wrap_init_key(tv_p, &AssetIdWrapKey, false, true);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Create key for unwrapping
                rc = test_rsa_pkcs1v15wrap_init_key(tv_p, &AssetIdUnwrapKey, true, false);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Wrap key
                rc = test_rsa_pkcs1v15wrap_wrap(tv_p, &PublicKey, AssetIdWrapKey, false);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Unwrap key
                rc = test_rsa_pkcs1v15wrap_wrap(tv_p, &PrivateKey, AssetIdUnwrapKey, true);
            }
            if (rc == END_TEST_SUCCES)
            {
                uint8_t MacRef[VAL_SYM_ALGO_MAX_DIGEST_SIZE];

                // Verify unwrap operations
                rc = test_rsa_hmac_check(tv_p->HashBits, AssetIdWrapKey, MacRef, NULL);
                if (rc == END_TEST_SUCCES)
                {
                    rc = test_rsa_hmac_check(tv_p->HashBits, AssetIdUnwrapKey, NULL, MacRef);
                }
            }

            // Clean-up assets
            if ((rc == END_TEST_SUCCES) || g_ValTestCleanUp)
            {
                if (AssetIdWrapKey != VAL_ASSETID_INVALID)
                {
                    (void)val_AssetFree(AssetIdWrapKey);
                    AssetIdWrapKey = VAL_ASSETID_INVALID;
                }
                if (AssetIdUnwrapKey != VAL_ASSETID_INVALID)
                {
                    (void)val_AssetFree(AssetIdUnwrapKey);
                    AssetIdUnwrapKey = VAL_ASSETID_INVALID;
                }
                test_release_key(&PublicKey);
                test_release_key(&PrivateKey);
            }

            if (rc == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }
        }

        test_vectors_rsa_pkcs1v15wrap_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }

    return END_TEST_SUCCES;
}

/* Unwrap data to a public data asset */
static int
test_rsa_pkcs1v15Unwrap_PublicData(
        uint32_t ModulusBits,
        bool fAllowAny)
{
    uint32_t Index;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAssetId_t AssetIdUnwrapKey;
    ValPolicyMask_t AssetPolicy;
    int rc = END_TEST_SUCCES;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    PrivateKey.DomainAssetId = VAL_ASSETID_INVALID;
    PrivateKey.KeyAssetId = VAL_ASSETID_INVALID;
    PublicKey.DomainAssetId = VAL_ASSETID_INVALID;
    PublicKey.KeyAssetId = VAL_ASSETID_INVALID;
    AssetIdUnwrapKey = VAL_ASSETID_INVALID;

    for (Index = 0U; ; Index++)
    {
        TestVector_PKCS1V15WRAP_t tv_p;

        tv_p = test_vectors_rsa_pkcs1v15wrap_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->ModulusBits == ModulusBits)
        {
            rc = test_rsa_pkcs1v15wrap_privkey(tv_p, &PrivateKey, fAllowAny);
            if (rc == END_TEST_SUCCES)
            {
                // Create and load Public Key asset
                rc = test_rsa_pkcs1v15wrap_pubkey(tv_p, &PublicKey);
            }
            if (rc == END_TEST_SUCCES)
            {
                // Create public data asset for unwrap key
                AssetPolicy = EIP130_ASSET_POLICY_NONMODIFIABLE | EIP130_ASSET_POLICY_NODOMAIN |
                              EIP130_ASSET_POLICY_GENERICDATA | EIP130_ASSET_POLICY_PUBLICDATA;
                if (!val_IsAccessSecure())
                {
                    AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
                }
                rc = val_AssetAlloc(AssetPolicy, tv_p->PlainDataBytes,
                                        VAL_ASSET_LIFETIME_INFINITE, true, false, 0,
                                        &AssetIdUnwrapKey);
                if (val_CheckFunctionResult(rc) != VAL_SUCCESS)
                {
                    rc = END_TEST_FAIL;
                }
            }
            if (rc == END_TEST_SUCCES)
            {
                // Unwrap key
                uint8_t * WrappedData_p;
                ValStatus_t Status;

                WrappedData_p = SFZUTF_MALLOC(tv_p->WrappedDataBytes);
                fail_if(WrappedData_p == NULL, "Allocation ", (int)tv_p->WrappedDataBytes);
                memcpy(WrappedData_p, tv_p->WrappedData_p, tv_p->WrappedDataBytes);

                Status = val_AsymRsaPkcs1v15Unwrap(&PrivateKey, AssetIdUnwrapKey,
                                                   WrappedData_p, tv_p->WrappedDataBytes);
                SFZUTF_FREE(WrappedData_p);
                if (fAllowAny)
                {
                    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymRsaPkcs1v15Unwrap(Pubdata)=", Status);
                }
                else
                {
                    fail_if(val_CheckFunctionResult(Status) != VAL_ACCESS_ERROR, "val_AsymRsaPkcs1v15Unwrap(Pubdata)=", Status);
                }
            }

            if ((rc == END_TEST_SUCCES) || g_ValTestCleanUp)
            {
                if (AssetIdUnwrapKey != VAL_ASSETID_INVALID)
                {
                    (void)val_AssetFree(AssetIdUnwrapKey);
                    AssetIdUnwrapKey = VAL_ASSETID_INVALID;
                }
                test_release_key(&PublicKey);
                test_release_key(&PrivateKey);
            }

            test_vectors_rsa_pkcs1v15wrap_release(tv_p);
            /* only one vector is sufficient for this test! */
            break;
        }

    }
    return rc;
}

START_TEST(test_rsa_pkcs1v15wrap_PublicData)
{
    int rc = test_rsa_pkcs1v15Unwrap_PublicData(1024, ((_i & 1) != 0));
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_pkcs1v15wrap_1024)
{
    int rc = test_rsa_pkcs1v15wrap(1024);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_pkcs1v15wrap_2048)
{
    int rc = test_rsa_pkcs1v15wrap(2048);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST

START_TEST(test_rsa_pkcs1v15wrap_3072)
{
    int rc = test_rsa_pkcs1v15wrap(3072);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


int
suite_add_test_AsymRsa(
    struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "AsymCrypto_RSA_Vectors");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
            goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_rsa_pkcs1v15_1024, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_rsa_pkcs1v15_2048, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_rsa_pkcs1v15_3072, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_rsa_pss_1024, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_rsa_pss_2048, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_rsa_pss_3072, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_rsa_oaep_1024) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_rsa_oaep_2048) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_rsa_oaep_3072) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_rsa_pkcs1v15wrap_1024) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_rsa_pkcs1v15wrap_2048) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_rsa_pkcs1v15wrap_3072) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_rsa_pkcs1v15wrap_PublicData, 2) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_asym_rsa.c */
