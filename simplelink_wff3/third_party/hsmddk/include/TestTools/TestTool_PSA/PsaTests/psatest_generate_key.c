/* psatest_generate_key.c
 *
 * Description: tests for the key generation function.
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
#ifdef PSA_ENABLE_DEBUG_FUNCTIONS
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_debug.h>
#endif

/*----------------------------------------------------------------------------
 * do_GenerateKey
 */
static int
do_GenerateKey(bool fAsym,
               psa_key_type_t KeyType,
               uint32_t Algorithm,
               uint32_t UsageFlags,
               uint16_t Bits,
               uint32_t Lifetime,
               psa_key_id_t UId)
{
    psa_key_attributes_t Attributes;
    psa_key_id_t Key;
    psa_status_t Status;
    size_t PubkeyLen;
    uint8_t Pubkey[200];

    /* Setup attributes */
    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes, KeyType);
    psa_set_key_algorithm(&Attributes, Algorithm);
    psa_set_key_usage_flags(&Attributes, UsageFlags);
    psa_set_key_bits(&Attributes, Bits);
    psa_set_key_lifetime(&Attributes, Lifetime);
    if (UId != 0U)
    {
        /* Note: Adapts lifetime, so ONLY use when UId is not 0U */
        psa_set_key_id(&Attributes, UId);
    }

    /* Generate a key or kry pair */
    Status = psa_generate_key(&Attributes, &Key);
    unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
    fail_if((PSA_SUCCESS != Status), "psa_generate_key()=", Status);

    if (fAsym)
    {
        /* Get public key of the key pair */
        Status = psa_export_public_key(Key, Pubkey, sizeof(Pubkey), &PubkeyLen);
        if (PSA_SUCCESS != Status)
        {
            (void)psa_destroy_key(Key);
        }
        fail_if((PSA_SUCCESS != Status), "psa_export_public_key()=", Status);
        //Log_HexDump("Publickey", 0, Pubkey, PubkeyLen);
    }

    /* Destroy key again */
    Status = psa_destroy_key(Key);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key()=", Status);

    return END_TEST_SUCCES;
}


/*----------------------------------------------------------------------------
 * test_GenerateKey
 */
START_TEST(test_GenerateKey)
{
    bool fault = false;
    int rc;

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                        PSA_ALG_ECDSA(PSA_ALG_SHA_224),
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        224U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE,
                        0U);
    if (rc == END_TEST_UNSUPPORTED)
    {
        return END_TEST_UNSUPPORTED;
    }
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with NIST-224\n");
        fault = true;
    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                        PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        256U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with NIST-256\n");
        fault = true;
    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
                        PSA_ALG_ECDSA(PSA_ALG_SHA_384),
#else
                        PSA_ALG_ECDSA(PSA_ALG_SHA_256),
#endif
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        384U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with NIST-384\n");
        fault = true;
    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
                        PSA_ALG_ECDSA(PSA_ALG_SHA_512),
#else
                        PSA_ALG_ECDSA(PSA_ALG_SHA_256),
#endif
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        521U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with NIST-521\n");
        fault = true;
    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
                        PSA_ALG_ECDSA(PSA_ALG_SHA_224),
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        224U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with Brainpool-224\n");
        fault = true;
    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
                        PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        256U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with Brainpool-256\n");
        fault = true;
    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
                        PSA_ALG_ECDSA(PSA_ALG_SHA_384),
#else
                        PSA_ALG_ECDSA(PSA_ALG_SHA_256),
#endif
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        384U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with Brainpool-384\n");
        fault = true;

    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
                        PSA_ALG_ECDSA(PSA_ALG_SHA_512),
#else
                        PSA_ALG_ECDSA(PSA_ALG_SHA_256),
#endif
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        512U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with Brainpool-512\n");
        fault = true;
    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY),
                        PSA_ALG_ECDH,
                        PSA_KEY_USAGE_DERIVE,
                        255U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_DEFAULT,
                        5U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with X25519\n");
        fault = true;
    }

#ifndef PSA_REMOVE_SYM_ALGO_SHA512
    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS),
                        PSA_ALG_PURE_EDDSA,
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        255U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with Ed25519\n");
        fault = true;
    }
#endif

    rc = do_GenerateKey(false,
                        PSA_KEY_TYPE_AES,
                        PSA_ALG_CTR,
                        PSA_KEY_USAGE_ENCRYPT,
                        256U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with AES-CTR\n");
        fault = true;
    }

    rc = do_GenerateKey(false,
                        PSA_KEY_TYPE_AES,
                        PSA_ALG_XTS,
                        PSA_KEY_USAGE_ENCRYPT,
                        512U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with AES-XTS\n");
        fault = true;
    }

    rc = do_GenerateKey(false,
                        PSA_KEY_TYPE_AES,
                        PSA_ALG_CBC_NO_PADDING,
                        PSA_KEY_USAGE_DECRYPT,
                        128U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with AES-CBC\n");
        fault = true;
    }

    rc = do_GenerateKey(false,
                        PSA_KEY_TYPE_HMAC,
                        PSA_ALG_HMAC(PSA_ALG_SHA_256),
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        320U,
                        (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE,
                        0U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with HMAC-256\n");
        fault = true;

    }

#ifndef PSA_REMOVE_SYM_ALGO_SHA512
    rc = do_GenerateKey(false,
                        PSA_KEY_TYPE_HMAC,
                        PSA_ALG_HMAC(PSA_ALG_SHA_384),
                        PSA_KEY_USAGE_SIGN_MESSAGE,
                        384U,
                        (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_DEFAULT,
                        6U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with HMAC-384\n");
        fault = true;
    }
#endif

    if (fault)
    {
        return END_TEST_FAIL;
    }
    else
    {
        /* MISRA - Intentially empty */
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_GenerateCachedKey
 */
START_TEST(test_GenerateCachedKey)
{
    psa_key_attributes_t Attributes;
    psa_key_id_t Key;
    psa_status_t Status;
    bool fault = false;
    int rc;

    rc = do_GenerateKey(false,
                        PSA_KEY_TYPE_AES,
                        PSA_ALG_XTS,
                        PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_CACHE,
                        512U,
                        (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_DEFAULT,
                        4U);
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with AES-XTS\n");
        fault = true;
    }
    else
    {
        /* Remove the generated key from persistence storage */
        (void)memset(&Attributes, 0, sizeof(Attributes));
        psa_set_key_type(&Attributes, PSA_KEY_TYPE_AES);
        psa_set_key_algorithm(&Attributes, PSA_ALG_XTS);
        psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_ENCRYPT);
        psa_set_key_bits(&Attributes, 512U);
        psa_set_key_lifetime(&Attributes, (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                                          PSA_KEY_PERSISTENCE_DEFAULT);
        psa_set_key_id(&Attributes, 4U);

        Status = psa_import_key(&Attributes, NULL, 0U, &Key);
        fail_if(PSA_SUCCESS != Status, "psa_import_key(AES-XTS)", Status);
        (void)psa_destroy_key(Key);
    }

    rc = do_GenerateKey(true,
                        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                        PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_CACHE,
                        256U,
                        (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_DEFAULT,
                        7U);
    if (rc == END_TEST_UNSUPPORTED)
    {
        return END_TEST_UNSUPPORTED;
    }
    if (rc == END_TEST_FAIL)
    {
        LOG_CRIT("Issue with NIST-256\n");
        fault = true;
    }
    else
    {
        /* Remove the generated key from persistence storage */
        (void)memset(&Attributes, 0, sizeof(Attributes));
        psa_set_key_type(&Attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
        psa_set_key_algorithm(&Attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
        psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_SIGN_MESSAGE);
        psa_set_key_bits(&Attributes, 256U);
        psa_set_key_lifetime(&Attributes, (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                           PSA_KEY_PERSISTENCE_DEFAULT);
        psa_set_key_id(&Attributes, 7U);

        Status = psa_import_key(&Attributes, NULL, 0U, &Key);
        fail_if(PSA_SUCCESS != Status, "psa_import_key(NIST-256)", Status);
        (void)psa_destroy_key(Key);
    }

    if (fault)
    {
        return END_TEST_FAIL;
    }
    else
    {
        /* MISRA - Intentially empty */
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_NegGenerateKey
 */
START_TEST(test_NegGenerateKey)
{
    psa_key_attributes_t Attributes;
    psa_key_id_t Key;
    psa_key_id_t TestKey;
    psa_status_t Status;

    /* Setup attributes */
    (void)memset(&Attributes, 0, sizeof(Attributes));
    /* Check invalid function arguments use */
    Status = psa_generate_key(NULL, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(attributes=NULL)=", Status);

    Status = psa_generate_key(&Attributes, NULL);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(Key=NULL)=", Status);

    /* Check invalid attribute settings */
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(attributes.type)=", Status);

    psa_set_key_type(&Attributes, PSA_KEY_TYPE_VENDOR_FLAG);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(attributes.bits)=", Status);

    psa_set_key_bits(&Attributes, 256U);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(attributes.alg)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes,
                     PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS));
    psa_set_key_algorithm(&Attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_SIGN_MESSAGE);
    psa_set_key_bits(&Attributes, 255U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(curve1)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes,
                     PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_algorithm(&Attributes, PSA_ALG_PURE_EDDSA);
    psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_SIGN_MESSAGE);
    psa_set_key_bits(&Attributes, 256U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(curve2)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes,
                     PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_algorithm(&Attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_SIGN_MESSAGE);
    psa_set_key_bits(&Attributes, 521U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_NOT_SUPPORTED != Status), "psa_generate_key(location1)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes, PSA_KEY_TYPE_HMAC);
    psa_set_key_algorithm(&Attributes, PSA_ALG_HMAC(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&Attributes, (PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_EXPORT));
    psa_set_key_bits(&Attributes, 400U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(location2)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes, PSA_KEY_TYPE_HMAC);
    psa_set_key_algorithm(&Attributes, PSA_ALG_HMAC(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&Attributes, (PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_EXPORT));
    psa_set_key_bits(&Attributes, 400U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         0x81U);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(location3)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes, PSA_KEY_TYPE_HMAC);
    psa_set_key_algorithm(&Attributes, PSA_ALG_HMAC(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&Attributes, (PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_EXPORT));
    psa_set_key_bits(&Attributes, 300U);
    psa_set_key_lifetime(&Attributes, PSA_KEY_LOCATION_VENDOR_FLAG);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_generate_key(location4)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes,
                     PSA_KEY_TYPE_RSA_KEY_PAIR);
    psa_set_key_algorithm(&Attributes, PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_SIGN_MESSAGE);
    psa_set_key_bits(&Attributes, 2048U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_NOT_SUPPORTED != Status), "psa_generate_key(keytype1)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes, (PSA_KEY_TYPE_VENDOR_FLAG + 1U));
    psa_set_key_algorithm(&Attributes, PSA_ALG_HMAC(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_SIGN_MESSAGE);
    psa_set_key_bits(&Attributes, 400U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_ERROR_NOT_SUPPORTED != Status), "psa_generate_key(keytype2)=", Status);

    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes, PSA_KEY_TYPE_HMAC);
    psa_set_key_algorithm(&Attributes, PSA_ALG_HMAC(PSA_ALG_SHA_256));
    psa_set_key_usage_flags(&Attributes, (PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_EXPORT));
    psa_set_key_bits(&Attributes, 400U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_DEFAULT);
    psa_set_key_id(&Attributes, 6U);
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_SUCCESS != Status), "psa_generate_key(OK)=", Status);

    /* Special checks for persistent behavior */
    {
        uint8_t KeyBuffer[200U / 8U];

        Status = psa_import_key(&Attributes, KeyBuffer, (200U / 8U), &TestKey);
        fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(1)", Status);

        psa_set_key_bits(&Attributes, 0U);
        Status = psa_import_key(&Attributes, KeyBuffer, (200U / 8U), &TestKey);
        fail_if(PSA_ERROR_ALREADY_EXISTS != Status, "psa_import_key(2)", Status);
    }

    psa_set_key_bits(&Attributes, 300U);
    Status = psa_generate_key(&Attributes, &TestKey);
    fail_if((PSA_ERROR_ALREADY_EXISTS != Status), "psa_generate_key(2)=", Status);

    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_DEFAULT);
    psa_set_key_bits(&Attributes, 400U);
    Status = psa_generate_key(&Attributes, &TestKey);
    fail_if((PSA_ERROR_ALREADY_EXISTS != Status), "psa_generate_key(3)=", Status);

    /* Next seven test for psa_get_key_attributes() and psa_reset_key_attributes()
     * are intended for coverage purpose */
    Status = psa_get_key_attributes(Key, &Attributes);
    fail_if((PSA_SUCCESS != Status), "psa_get_key_attributes(1)=", Status);

    Status = psa_get_key_attributes(0, &Attributes);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_get_key_attributes(2)=", Status);

    Status = psa_get_key_attributes(500, &Attributes);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_get_key_attributes(3)=", Status);

    Status = psa_get_key_attributes(80, &Attributes);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_get_key_attributes(4)=", Status);

    Status = psa_get_key_attributes(Key, NULL);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_get_key_attributes(5)=", Status);

    Status = psa_destroy_key(Key);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key()=", Status);

    /* Next function calls are only for coverage improvement */
    psa_reset_key_attributes(NULL);
    psa_reset_key_attributes(&Attributes);

    psa_set_key_bits(&Attributes, PSA_MAX_KEY_BITS+1);
    (void)psa_get_key_id(&Attributes);
    (void)psa_get_key_lifetime(&Attributes);
    (void)psa_get_key_type(&Attributes);
    (void)psa_get_key_algorithm(&Attributes);
    (void)psa_get_key_bits(&Attributes);
    (void)psa_get_key_usage_flags(&Attributes);
    (void)psa_get_key_id(&Attributes);
    (void)psa_get_key_lifetime(&Attributes);

}
END_TEST

#ifdef PSA_ENABLE_DEBUG_FUNCTIONS
/*----------------------------------------------------------------------------
 * test_KeyStoreDump - more or less intended for coverage improvement
 */
START_TEST(test_KeyStoreDump)
{
    psa_key_attributes_t Attributes;
    psa_key_id_t Key1;
    psa_key_id_t Key2 = 0;
    psa_key_id_t Key3 = 0;
    psa_status_t Status;

    /* Setup basic attributes */
    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes, PSA_KEY_TYPE_AES);
    psa_set_key_algorithm(&Attributes, PSA_ALG_CTR);
    psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_ENCRYPT);
    psa_set_key_bits(&Attributes, 128U);

    /* Generate various keys */
    psa_set_key_lifetime(&Attributes, (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                      PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);
    Status = psa_generate_key(&Attributes, &Key1);
    fail_if((PSA_SUCCESS != Status), "psa_generate_key(1)=", Status);

    psa_set_key_bits(&Attributes, 192U);
    psa_set_key_lifetime(&Attributes, (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                      PSA_KEY_PERSISTENCE_VOLATILE);
    Status = psa_generate_key(&Attributes, &Key2);
    if (PSA_ERROR_HARDWARE_FAILURE != Status)
    {
        fail_if((PSA_SUCCESS != Status), "psa_generate_key(2)=", Status);

        psa_set_key_bits(&Attributes, 256U);
        psa_set_key_lifetime(&Attributes, (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                          PSA_KEY_PERSISTENCE_DEFAULT);
        psa_set_key_id(&Attributes, 1U);
        Status = psa_generate_key(&Attributes, &Key3);
        fail_if((PSA_SUCCESS != Status), "psa_generate_key(3)=", Status);
    }

    psaDebug_KeyStoreDump();

    /* Destroy keys */
    Status = psa_destroy_key(Key1);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key(1)=", Status);

    (void)psa_destroy_key(Key2);
    (void)psa_destroy_key(Key3);
}
END_TEST
#endif


int
suite_add_test_generate_key(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "GenerateKey_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_GenerateKey) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_GenerateCachedKey) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_NegGenerateKey) != 0) goto FuncErrorReturn;
#ifdef PSA_ENABLE_DEBUG_FUNCTIONS
        if (sfzutf_test_add(TestCase_p, test_KeyStoreDump) != 0) goto FuncErrorReturn;
#endif

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_generate_key.c */
