/* psatest_asym_ecdh.c
 *
 * Description: tests for asymmetric key agreement.
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

#include "psatest_internal.h"

/* Test vectors. */
#include "testvectors_asn1_der.h"


/*----------------------------------------------------------------------------
 * GetTestVector
 */
static TestVector_ASN1_DER_t
GetTestVector(uint8_t KeyType,
              uint8_t Method,
              uint32_t ModulusSize,
              bool fPrivateKey)
{
    TestVector_ASN1_DER_t pTestVector;
    uint32_t ndx_key;

    for(ndx_key = 0; ; ndx_key++)
    {
        pTestVector = test_vectors_asn1_der_get(ndx_key);
        if (pTestVector == NULL)
        {
            break;
        }

        if ((pTestVector->KeyType != KeyType) ||
            (pTestVector->Method != Method) ||
            (pTestVector->fPrivateKey != fPrivateKey) ||
            (pTestVector->ModulusSize != ModulusSize))
        {
            test_vectors_asn1_der_release(pTestVector);
        }
        else
        {
            break;
        }
    }

    return pTestVector;
}


static int
doKeyAgreementTest(uint8_t Method,
                   uint32_t ModulusSize,
                   int Loop)
{
    TestVector_ASN1_DER_t tv_prvkey_p;
    psa_key_attributes_t attributes;
    psa_key_id_t StatPrvKey;
    psa_key_id_t EmphPrvKey;
    psa_status_t Status;
    psa_key_lifetime_t lifetime;
    size_t StatPubkeyLen;
    size_t EphmPubkeyLen;
    size_t Secret1Len;
    size_t Secret2Len;
    uint8_t StatPubkey[200] = { 0 };
    uint8_t EphmPubkey[200] = { 0 };
    uint8_t SharedSecret1[200] = { 0 };
    uint8_t SharedSecret2[200] = { 0 };
    psa_key_id_t uid;

    tv_prvkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, Method,
                                ModulusSize, true);
    fail_if((tv_prvkey_p == NULL), "Found no valid key", ModulusSize);

    /* Setup basic attributes */
    (void)memset(&attributes, 0, sizeof(attributes));
    if (TV_ASN1DER_NIST_METHOD == Method)
    {
        psa_set_key_type(&attributes,
                         PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    }
    else if (TV_ASN1DER_BPOOL_METHOD == Method)
    {
        psa_set_key_type(&attributes,
                         PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1));
    }
    else
    {
        psa_set_key_type(&attributes,
                         PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY));
    }
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDH);
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DERIVE);
    psa_set_key_bits(&attributes, ModulusSize);
    uid = 0U;
    if (Loop == 1)
    {
        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
        uid = 1U;
    }
    else if (Loop == 2)
    {
        lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
    }
    else if (Loop == 3)
    {
        lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
    }
    else if (Loop == 4)
    {
        lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
        uid = 1U;
    }
    else
    {
        /* Default/Loop == 0 */
        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
    }
    psa_set_key_lifetime(&attributes, lifetime);
    if (uid != 0U)
    {
        psa_set_key_id(&attributes, uid);
    }

    /* Import test static private key */
    Status = psa_import_key(&attributes,
                            tv_prvkey_p->pData, tv_prvkey_p->DataLen,
                            &StatPrvKey);
    unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
    fail_if((PSA_SUCCESS != Status), "psa_import_key(static)=", Status);

    if ((Loop == 1) || (Loop == 4))
    {
        psa_key_id_t key2;

        Status = psa_import_key(&attributes, NULL, 0U, &key2);
        fail_if((PSA_SUCCESS != Status), "psa_import_key(2)=", Status);

        (void)psa_destroy_key(key2);
    }

    /* Get public key of the static key pair */
    Status = psa_export_public_key(StatPrvKey,
                                   StatPubkey, sizeof(StatPubkey),
                                   &StatPubkeyLen);
    fail_if((PSA_SUCCESS != Status), "psa_export_public_key(static)", Status);
    //Log_HexDump("Publickey(static)", 0, StatPubkey, StatPubkeyLen);

    psa_set_key_id(&attributes, 0U);
    if ((Loop & 1) == 0)
    {
        psa_set_key_lifetime(&attributes,
                             (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                             PSA_KEY_PERSISTENCE_VOLATILE);
    }
    else
    {
        psa_set_key_lifetime(&attributes,
                             (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                             PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);
    }

    /* Generate an ephemeral key pair */
    Status = psa_generate_key(&attributes, &EmphPrvKey);
    if (PSA_ERROR_HARDWARE_FAILURE == Status)
    {
        (void)psa_destroy_key(StatPrvKey);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
    }
    fail_if((PSA_SUCCESS != Status), "psa_generate_key(ephemeral)=", Status);

    /* Get public key of the ephemeral key pair */
    Status = psa_export_public_key(EmphPrvKey,
                                   EphmPubkey, sizeof(EphmPubkey), &EphmPubkeyLen);
    fail_if((PSA_SUCCESS != Status), "psa_export_public_key(ephemeral)=", Status);
    //Log_HexDump("Publickey(ephemeral)", 0, EphmPubkey, EphmPubkeyLen);

    /* Generate shared secret for static private key and ephemeral public key */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey, EphmPubkey, EphmPubkeyLen,
                                   SharedSecret1, sizeof(SharedSecret1), &Secret1Len);
    fail_if((PSA_SUCCESS != Status), "psa_raw_key_agreement(static/ephemeral)=", Status);

    /* Generate shared secret for ephemeral private key and static public key */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   EmphPrvKey, StatPubkey, StatPubkeyLen,
                                   SharedSecret2, sizeof(SharedSecret2), &Secret2Len);
    fail_if((PSA_SUCCESS != Status), "psa_raw_key_agreement(static/ephemeral)=", Status);

    /* Release the used private key entries */
    Status = psa_destroy_key(StatPrvKey);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key(static)=", Status);
    Status = psa_destroy_key(EmphPrvKey);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key(ephemeral)=", Status);

    /* Compare generated shared secrets */
    //Log_HexDump("Secret1", 0, SharedSecret1, Secret1Len);
    //Log_HexDump("Secret2", 0, SharedSecret2, Secret2Len);
    fail_if((Secret1Len != Secret2Len), "psa_raw_key_agreement(static/ephemeral)=",
            (Secret1Len - Secret2Len));
    fail_if(memcmp(SharedSecret1, SharedSecret2, Secret1Len) != 0, "", 1);

    return END_TEST_SUCCES;
}


START_TEST(test_ecdh_NIST)
{
    int rc = doKeyAgreementTest(TV_ASN1DER_NIST_METHOD, 521, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


START_TEST(test_ecdh_BPOOL)
{
    int rc = doKeyAgreementTest(TV_ASN1DER_BPOOL_METHOD, 256, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


START_TEST(test_ecdh_curve25519)
{
    int rc = doKeyAgreementTest(TV_ASN1DER_MONT_METHOD, 255, _i);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


START_TEST(test_ecdh_NegKeyAgreement)
{
    TestVector_ASN1_DER_t tv_prvkey_p;
    TestVector_ASN1_DER_t tv_pubkey_p;
    psa_key_attributes_t attributes;
    psa_key_id_t StatPrvKey;
    psa_key_id_t TestKey;
    psa_status_t Status;
    size_t PubkeyLen;
    size_t SecretLen;
    uint8_t Pubkey[200];
    uint8_t SharedSecret[200];

    tv_prvkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD,
                                256U, true);
    fail_if((tv_prvkey_p == NULL), "Found no valid key", 256);

    tv_pubkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD,
                                256U, false);
    fail_if((tv_prvkey_p == NULL), "Found no valid key", 256);

    /* Setup basic attributes */
    (void)memset(&attributes, 0, sizeof(attributes));
    psa_set_key_type(&attributes,
                     PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDH);
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DERIVE);
    psa_set_key_bits(&attributes, 256U);
    psa_set_key_lifetime(&attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);

    /* Import test static private key */
    Status = psa_import_key(&attributes,
                            tv_prvkey_p->pData, tv_prvkey_p->DataLen,
                            &StatPrvKey);
    fail_if((PSA_SUCCESS != Status), "psa_import_key(static)=", Status);

    /* Get public key of the static private key (pair) */
    Status = psa_export_public_key(StatPrvKey, Pubkey, sizeof(Pubkey), &PubkeyLen);
    fail_if((PSA_SUCCESS != Status), "psa_export_public_key(static)", Status);

    /* Generate shared secret with invalid function arguments */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   PSA_KEY_ID_NULL,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_raw_key_agreement(key=0)=", Status);

    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   NULL, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(peer_key=NULL)=", Status);

    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, 0U,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(peer_key_length=0)=", Status);

    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   NULL, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(output=NULL)=", Status);

    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), NULL);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(output_length=NULL)=", Status);

    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, 0U, &SecretLen);
    fail_if((PSA_ERROR_BUFFER_TOO_SMALL != Status), "psa_raw_key_agreement(output_size=0)=", Status);

    Status = psa_raw_key_agreement(PSA_ALG_ECDSA_ANY,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(wrong alg1)=", Status);

    /* Import test static private key */
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_MESSAGE);
    Status = psa_import_key(&attributes,
                            tv_prvkey_p->pData, tv_prvkey_p->DataLen,
                            &TestKey);
    fail_if((PSA_SUCCESS != Status), "psa_import_key(TestKey1)=", Status);

    /* Generate shared secret with invalid function arguments */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   TestKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_NOT_PERMITTED != Status), "psa_raw_key_agreement(wrong alg2)=", Status);

    /* Release the static private key (pair) */
    Status = psa_destroy_key(TestKey);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key(static)=", Status);

    /* Generate shared secret with a not supported algorithm */
    Status = psa_raw_key_agreement(PSA_ALG_FFDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_NOT_SUPPORTED != Status), "psa_raw_key_agreement(not supported algorithm)=", Status);

    /* Generate shared secret with wrong public key - EC_GENERIC type */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(wrong pubkey1)=", Status);

    tv_pubkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD,
                                384U, false);
    fail_if((tv_prvkey_p == NULL), "Found no valid key", 384);

    /* Generate shared secret with wrong public key - other curve size */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(wrong pubkey2)=", Status);

    tv_pubkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD,
                                256U, false);
    fail_if((tv_prvkey_p == NULL), "Found no valid key", 256);

    /* Generate shared secret with wrong public key - other curve type/method */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(wrong pubkey3)=", Status);

    tv_pubkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_MONT_METHOD,
                                255U, false);
    fail_if((tv_prvkey_p == NULL), "Found no valid key", 255);

    /* Generate shared secret with wrong public key - other curve type/method */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(wrong pubkey4)=", Status);

    tv_pubkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_TEDWARDS_METHOD,
                                255U, false);
    fail_if((tv_prvkey_p == NULL), "Found no valid key", 255);

    /* Generate shared secret with wrong public key - other curve type/method */
    Status = psa_raw_key_agreement(PSA_ALG_ECDH,
                                   StatPrvKey,
                                   tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                                   SharedSecret, sizeof(SharedSecret), &SecretLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_raw_key_agreement(wrong pubkey5)=", Status);

    /* Release the static private key (pair) */
    Status = psa_destroy_key(StatPrvKey);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key(StatPrvKey)=", Status);
}
END_TEST


START_TEST(test_ecdh_NegExportPublicKey)
{
    TestVector_ASN1_DER_t tv_p;
    psa_key_attributes_t attributes;
    psa_key_id_t TestKey;
    psa_status_t Status;
    size_t PubkeyLen;
    uint8_t Pubkey[200];

    tv_p = GetTestVector(TV_ASN1DER_RSA_KEY_TYPE, TV_ASN1DER_PKCS1_METHOD,
                         2048, true);
    fail_if((tv_p == NULL), "Found no valid key", 2048);

    /* Setup basic attributes */
    (void)memset(&attributes, 0, sizeof(attributes));
    psa_set_key_type(&attributes, PSA_KEY_TYPE_RSA_KEY_PAIR);
    psa_set_key_algorithm(&attributes,
                          PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_MESSAGE);
    psa_set_key_bits(&attributes, 2048);
    psa_set_key_lifetime(&attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);

    /* Import test static private key (pair) */
    Status = psa_import_key(&attributes, tv_p->pData, tv_p->DataLen, &TestKey);
    fail_if((PSA_SUCCESS != Status), "psa_import_key(TestKey)=", Status);

    /* Get public key with invalid function arguments */
    Status = psa_export_public_key(PSA_KEY_ID_NULL, Pubkey, sizeof(Pubkey), &PubkeyLen);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_export_public_key(key=0)=", Status);

    Status = psa_export_public_key(TestKey, NULL, sizeof(Pubkey), &PubkeyLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_export_public_key(data=NULL)", Status);

    Status = psa_export_public_key(TestKey, Pubkey, 0U, &PubkeyLen);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_export_public_key(data_size=0)", Status);

    Status = psa_export_public_key(TestKey, Pubkey, sizeof(Pubkey), NULL);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_export_public_key(data_length=NULL)", Status);

    /* Get public key of the static RSA key pair */
    Status = psa_export_public_key(TestKey, Pubkey, sizeof(Pubkey), &PubkeyLen);
    fail_if((PSA_ERROR_NOT_SUPPORTED != Status), "psa_export_public_key(RSA key pair)", Status);

    /* Release the static private key (pair) */
    Status = psa_destroy_key(TestKey);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key(TestKey)=", Status);

    /* Get a public key */
    tv_p = GetTestVector(TV_ASN1DER_ECDH_KEY_TYPE, TV_ASN1DER_NIST_METHOD,
                         256, false);
    fail_if((tv_p == NULL), "Found no valid key", 256);

    (void)memset(&attributes, 0, sizeof(attributes));
    psa_set_key_type(&attributes,
                     PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDH);
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DERIVE);
    psa_set_key_bits(&attributes, 256);
    psa_set_key_lifetime(&attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);

    /* Import static public key */
    Status = psa_import_key(&attributes, tv_p->pData, tv_p->DataLen, &TestKey);
    fail_if((PSA_SUCCESS != Status), "psa_import_key(public)=", Status);

    /* Get public key of the static RSA key pair */
    Status = psa_export_public_key(TestKey, Pubkey, sizeof(Pubkey), &PubkeyLen);
    fail_if((PSA_ERROR_NOT_SUPPORTED != Status), "psa_export_public_key(RSA key pair)", Status);

    /* Release the static private key (pair) */
    Status = psa_destroy_key(TestKey);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key(TestKey)=", Status);
}
END_TEST


int
suite_add_test_asym_ecdh(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "ASymCrypto_ECDH_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_ecdh_NIST, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_ecdh_BPOOL, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_ecdh_curve25519, 5) != 0) goto FuncErrorReturn;

        if (sfzutf_test_add(TestCase_p, test_ecdh_NegKeyAgreement) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_ecdh_NegExportPublicKey) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_asym_ecdh.c */
