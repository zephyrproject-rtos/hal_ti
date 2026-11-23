/* psatest_import_key.c
 *
 * Description: tests for key import function.
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
#include "testvectors_aes_basic.h"


/*----------------------------------------------------------------------------
 * setkeyattributes
 *
 * Helper function to set key attributes.
 */
static void
setkeyattributes(psa_key_attributes_t *attributes,
                 psa_key_type_t key_type,
                 psa_algorithm_t Mode,
                 psa_key_usage_t usage_flag,
                 size_t Key_size_bits,
                 psa_key_lifetime_t lifetime,
                 psa_key_id_t uid)
{
    psa_reset_key_attributes(attributes);

    psa_set_key_type(attributes, key_type);
    psa_set_key_algorithm(attributes, Mode);
    psa_set_key_usage_flags(attributes, usage_flag);
    psa_set_key_bits(attributes, Key_size_bits);
    psa_set_key_lifetime(attributes, lifetime);
    if (uid != 0)
    {
        psa_set_key_id(attributes, uid);
    }
}

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

/*----------------------------------------------------------------------------
 * test_ImportKey
 * Note: A lot of key import functionality is already tested during other
 *       tests, so this test will only touch the missing stuff.
 */
START_TEST(test_ImportKey)
{
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;
    psa_algorithm_t Mode;
    TestVector_AES_BASIC_t tv_p;
    psa_key_id_t Cached_key;
    psa_key_id_t Cached_key2;
    psa_key_id_t NVM_key;
    psa_key_id_t NVM_key2;
    psa_key_id_t NVM_key_ver;
    psa_key_id_t uid = 1U;
    psa_key_id_t uid_ver = 2U;
    psa_key_attributes_t attributes;
    psa_key_lifetime_t lifetime;
    size_t output_length;
    size_t IVSize;

    if (false == psatest_IsCOIDAvailable())
    {
        LOG_CRIT("Note that COID and HUK are required for all tests to PASS!!!\n");
    }

    tv_p = test_vectors_aes_basic_get(0);
    fail_if(NULL == tv_p, "No test vector", 0);

    switch (tv_p->Mode)
    {
    case TESTVECTORS_MODE_ECB:
        Mode = PSA_ALG_ECB_NO_PADDING;
        break;
    case TESTVECTORS_MODE_CBC:
        Mode = PSA_ALG_CBC_NO_PADDING;
        break;
    case TESTVECTORS_MODE_CTR:
        Mode = PSA_ALG_CTR;
        break;
    case TESTVECTORS_MODE_XTS:
        Mode = PSA_ALG_XTS;
        break;
    default:
        Mode = PSA_ALG_NONE;
        break;
    }
    if (PSA_ALG_NONE == Mode)
    {
        test_vectors_aes_basic_release(tv_p);
        unsupported("No test vector");
    }

    if (_i == 0)
    {
        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                   PSA_KEY_PERSISTENCE_DEFAULT;
    }
    else
    {
        lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                   PSA_KEY_PERSISTENCE_DEFAULT;
    }

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, Mode,
                     (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_CACHE),
                     (tv_p->KeyLen * 8U), lifetime, uid);
    Status = psa_import_key(&attributes, tv_p->Key_p, tv_p->KeyLen, &Cached_key);
    unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
    fail_if(PSA_SUCCESS != Status, "psa_import_key enc(1)", Status);

    Status = psa_import_key(&attributes, NULL, 0U, &Cached_key2);
    fail_if(PSA_SUCCESS != Status, "psa_import_key enc(2)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, Mode, PSA_KEY_USAGE_ENCRYPT,
                     (tv_p->KeyLen * 8U), lifetime, uid);
    Status = psa_import_key(&attributes, tv_p->Key_p, tv_p->KeyLen, &NVM_key);
    fail_if(PSA_SUCCESS != Status, "psa_import_key enc(3)", Status);

    Status = psa_import_key(&attributes, tv_p->Key_p, tv_p->KeyLen, &NVM_key2);
    fail_if(PSA_SUCCESS != Status, "psa_import_key enc(3)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, Mode, PSA_KEY_USAGE_DECRYPT,
                     (tv_p->KeyLen * 8U), lifetime, uid_ver);
    Status = psa_import_key(&attributes, tv_p->Key_p, tv_p->KeyLen, &NVM_key_ver);
    fail_if(PSA_SUCCESS != Status, "psa_import_key dec(1)", Status);

    IVSize = PSA_CIPHER_IV_LENGTH(PSA_KEY_TYPE_AES, Mode);
    uint8_t * ciphertext = (uint8_t *)SFZUTF_MALLOC(((tv_p->PtxLen) + IVSize));
    fail_if(ciphertext == NULL, "Allocation ", (int)((tv_p->PtxLen) + IVSize));
    (void)memset(ciphertext, 0, (tv_p->PtxLen) + IVSize);

    uint8_t * plaintext = (uint8_t *)SFZUTF_MALLOC(tv_p->PtxLen);
    fail_if(plaintext == NULL, "Allocation ", (int)tv_p->PtxLen);
    (void)memset(plaintext, 0, tv_p->PtxLen);

    output_length = 0U;
    Status = psa_cipher_encrypt(Cached_key, Mode, tv_p->Ptx_p, tv_p->PtxLen,
                                ciphertext, (tv_p->PtxLen + IVSize), &output_length);
    fail_if(PSA_SUCCESS != Status, "psa_cipher_encrypt ()", Status);
    fail_if(tv_p->PtxLen != (output_length - IVSize), "Length mismatch dec", (int)output_length);
    if(memcmp(ciphertext, tv_p->Ctx_p, tv_p->PtxLen) != 0)
    {
        Failed++;
        LOG_CRIT("Wrong ciphertext 1\n");
    }
    else
    {
        Success++;
    }

    output_length = 0U;
    Status = psa_cipher_decrypt(NVM_key_ver, Mode, ciphertext, (tv_p->PtxLen) + IVSize,
                                plaintext, tv_p->PtxLen, &output_length);
    fail_if(PSA_SUCCESS != Status, "psa_cipher_decrypt ()", Status);
    fail_if(tv_p->PtxLen != output_length, "Length mismatch dec", (int)output_length);
    if(memcmp(plaintext, tv_p->Ptx_p, tv_p->PtxLen) != 0)
    {
        Failed++;
        LOG_CRIT("Wrong plaintext\n");
    }
    else
    {
        Success++;
    }

    (void)memset(ciphertext, 0, (tv_p->PtxLen) + IVSize);
    output_length = 0U;
    Status = psa_cipher_encrypt(NVM_key, Mode, tv_p->Ptx_p, tv_p->PtxLen,
                                ciphertext, (tv_p->PtxLen + IVSize), &output_length);
    fail_if(PSA_SUCCESS != Status, "psa_cipher_encrypt ()", Status);
    fail_if(tv_p->PtxLen != (output_length - IVSize), "Length mismatch dec", (int)output_length);
    if(memcmp(ciphertext, tv_p->Ctx_p, tv_p->PtxLen) != 0)
    {
        Failed++;
        LOG_CRIT("Wrong ciphertext 2\n");
    }
    else
    {
        Success++;
    }

    SFZUTF_FREE(plaintext);
    SFZUTF_FREE(ciphertext);
    (void)psa_purge_key(Cached_key);
    (void)psa_destroy_key(Cached_key2);
    (void)psa_destroy_key(NVM_key2);
    (void)psa_destroy_key(NVM_key);
    (void)psa_destroy_key(NVM_key_ver);
    test_vectors_aes_basic_release(tv_p);

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_NegImportKey
 */
START_TEST(test_ImportKeyECDH)
{
    TestVector_ASN1_DER_t tv_pubkey_p;
    psa_key_attributes_t attributes;
    psa_status_t Status;
    psa_key_id_t Key;
    psa_key_id_t Key2;

    /* ECDH public key import tests */
    tv_pubkey_p = GetTestVector(TV_ASN1DER_ECDH_KEY_TYPE, TV_ASN1DER_BPOOL_METHOD,
                                256U, false);
    fail_if((tv_pubkey_p == NULL), "Found no valid key", 256);

    setkeyattributes(&attributes, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
                     PSA_ALG_ECDH, (PSA_KEY_USAGE_DERIVE | PSA_KEY_USAGE_EXPORT),
                     256U, ((PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT),
                     1U);
    Status = psa_import_key(&attributes,
                            tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                            &Key);
    fail_if((PSA_SUCCESS != Status), "psa_import_key(1)=", Status);

    Status = psa_import_key(&attributes, NULL, 0U, &Key2);
    fail_if((PSA_SUCCESS != Status), "psa_import_key(2)=", Status);

    (void)psa_destroy_key(Key);
    (void)psa_destroy_key(Key2);

    tv_pubkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_MONT_METHOD,
                                255U, false);
    fail_if((tv_pubkey_p == NULL), "Found no valid key", 255);

    setkeyattributes(&attributes, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_MONTGOMERY),
                     PSA_ALG_ECDH, (PSA_KEY_USAGE_DERIVE | PSA_KEY_USAGE_EXPORT),
                     255U, ((PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT),
                     1U);
    Status = psa_import_key(&attributes,
                            tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                            &Key);
    fail_if((PSA_SUCCESS != Status), "psa_import_key(3)=", Status);

    Status = psa_import_key(&attributes, NULL, 0U, &Key2);
    fail_if((PSA_SUCCESS != Status), "psa_import_key(4)=", Status);

    (void)psa_destroy_key(Key);
    (void)psa_destroy_key(Key2);
}
END_TEST

/*----------------------------------------------------------------------------
 * test_NegImportKey
 */
START_TEST(test_NegImportKey)
{
    TestVector_AES_BASIC_t tv_p;
    uint32_t ndx, ndx2;
    psa_status_t Status;
    psa_key_id_t key[MBEDTLS_MAX_KEY_BUFF_ENTRIES + 1U];
    psa_key_attributes_t attributes = { 0 };
    psa_key_lifetime_t lifetime;
    uint8_t DataBuffer[400U/8U] = { 0 };

    /* Clear key table before test */
    for (ndx = 1; ndx <= MBEDTLS_MAX_KEY_BUFF_ENTRIES; ndx++)
    {
        (void)psa_destroy_key(ndx);
    }

    /* Perform negative tests for key management (key table) */
    tv_p = test_vectors_aes_basic_get(0);
    fail_if(NULL == tv_p, "No test vector", 0);

    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                PSA_KEY_PERSISTENCE_VOLATILE;

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CBC_NO_PADDING,
                     (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_COPY),
                     (tv_p->KeyLen * 8U), lifetime, 0U);
    /* Note: PSA_ERROR_INVALID_HANDLE is returned when the key table is full
     *       and PSA_ERROR_INSUFFICIENT_STORAGE when memory is full */
    for (ndx = 0; ndx < (MBEDTLS_MAX_KEY_BUFF_ENTRIES + 1U); ndx++)
    {
        Status = psa_import_key(&attributes, tv_p->Key_p, tv_p->KeyLen, &key[ndx]);
        if ((PSA_ERROR_INSUFFICIENT_STORAGE != Status) &&
            (PSA_ERROR_INVALID_HANDLE != Status))
        {
            fail_if(PSA_SUCCESS != Status, "psa_import_key(table)", Status);

            Status = psa_copy_key(key[ndx], &attributes, &key[ndx + 1]);
            if ((PSA_ERROR_INSUFFICIENT_STORAGE != Status) &&
                (PSA_ERROR_INVALID_HANDLE != Status))
            {
                fail_if(PSA_SUCCESS != Status, "psa_copy_key(table)", Status);
                ndx++;
            }
        }
        if ((PSA_ERROR_INSUFFICIENT_STORAGE == Status) ||
            (PSA_ERROR_INVALID_HANDLE == Status))
        {
            break;
        }
    }
    for (ndx2 = 0; ndx2 < ndx; ndx2++)
    {
        Status = psa_destroy_key(key[ndx2]);
        fail_if(PSA_SUCCESS != Status, "psa_destroy_key(table)", Status);

        /* The copy is removed as well */
        ndx2++;
    }

    /* General functionality */
    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CBC_NO_PADDING,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(NULL, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G1)", Status);

    Status = psa_import_key(&attributes, NULL, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G2)", Status);

    Status = psa_import_key(&attributes, DataBuffer, 0U, &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G3)", Status);

    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), NULL);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G4)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_NONE,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G5)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_NONE, PSA_ALG_CBC_NO_PADDING,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G6)", Status);

    setkeyattributes(&attributes, (PSA_KEY_TYPE_VENDOR_FLAG + 1U),
                     PSA_ALG_CBC_NO_PADDING, PSA_KEY_USAGE_ENCRYPT,
                     256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G7)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CBC_NO_PADDING,
                     PSA_KEY_USAGE_ENCRYPT, 256U,
                     PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                         2U, PSA_KEY_LOCATION_LOCAL_STORAGE),
                     0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G8)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CBC_NO_PADDING,
                     PSA_KEY_USAGE_ENCRYPT, 256U,
                     PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                         2U, PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT),
                     0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G9)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CBC_NO_PADDING,
                     PSA_KEY_USAGE_ENCRYPT, 256U,
                     (PSA_KEY_LOCATION_VENDOR_FLAG | 2U),
                     0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G10)", Status);

    psa_set_key_id(&attributes, 5U);    /* Set attributes.id */
    attributes.lifetime = 0;            /* Force lifetime to local volatile */
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(G11)", Status);

    /* Symmetric algorithm related */
    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CBC_NO_PADDING,
                     PSA_KEY_USAGE_ENCRYPT, 200U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (200U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(200)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_XTS,
                     PSA_KEY_USAGE_ENCRYPT, 400U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (400U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(400)", Status);

#ifdef PSATEST_SYM_ALGO_ARIA
    setkeyattributes(&attributes, PSA_KEY_TYPE_ARIA, PSA_ALG_CBC_NO_PADDING,
                     PSA_KEY_USAGE_ENCRYPT, 200U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (200U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(ARIA)", Status);
#endif

#ifdef PSATEST_SYM_ALGO_3DES
    setkeyattributes(&attributes, PSA_KEY_TYPE_DES, PSA_ALG_CBC_NO_PADDING,
                     PSA_KEY_USAGE_ENCRYPT, 64U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (64U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(3DES)", Status);
#endif

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_1),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 104U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (104U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-1 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_1),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 520U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (520U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-1 UL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_224),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 104U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (104U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-224 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_224),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 520U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (520U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-224 UL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_256),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 120U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (120U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-256 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_256),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 520U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (520U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-256 UL)", Status);

#ifndef PSA_REMOVE_SYM_ALGO_SHA512
    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_384),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 184U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (184U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-384 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_384),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 1032U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (1032U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-384 UL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_512),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 248U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (248U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-512 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_512),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 1032U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (1032U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-512 UL)", Status);
#endif

#ifndef PSA_REMOVE_SYM_ALGO_SHA3
    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA3_224),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 104U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (104U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-3-224 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA3_224),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 1160U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (1160U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-3-224 UL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA3_256),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 120U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (120U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-3-256 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA3_256),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 1096U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (1096U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-3-256 UL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA3_384),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 184U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (184U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-3-384 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA3_384),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 840U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (840U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-3-384 UL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA3_512),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 248U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (248U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-3-512 LL)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA3_512),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 584U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (584U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC-SHA-3-512 UL)", Status);
#endif

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(((psa_algorithm_t)0x020000f2U)),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 300U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (300U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC wrong algo)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_HMAC, PSA_ALG_HMAC(PSA_ALG_SHA_256),
                     PSA_KEY_USAGE_DECRYPT, 300U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (300U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(HMAC wrong usage)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CMAC,
                     PSA_KEY_USAGE_SIGN_MESSAGE, 200U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (200U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(AES-CMAC)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, ((psa_algorithm_t)0x03c00300U),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CMAC wrong algo)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_DES, PSA_ALG_CMAC,
                     PSA_KEY_USAGE_SIGN_MESSAGE, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CMAC wrong key type)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CMAC,
                     PSA_KEY_USAGE_DECRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CMAC wrong usage)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CTR,
                     PSA_KEY_USAGE_SIGN_MESSAGE, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CIPH wrong usage)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_CAMELLIA, PSA_ALG_CTR,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CIPH wrong algo)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_DES, PSA_ALG_CTR,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CIPH wrong algo)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_DES, PSA_ALG_XTS,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CIPH wrong algo)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_OFB,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CIPH wrong method)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_GCM,
                     PSA_KEY_USAGE_SIGN_MESSAGE, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(AEAD wrong usage)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_GCM,
                     PSA_KEY_USAGE_ENCRYPT, 200U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (200U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(AEAD AES wrong size)", Status);

#ifdef PSATEST_SYM_ALGO_ARIA
    setkeyattributes(&attributes, PSA_KEY_TYPE_ARIA, PSA_ALG_GCM,
                     PSA_KEY_USAGE_ENCRYPT, 200U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (200U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(AEAD ARIA wrong size)", Status);
#endif

#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
    setkeyattributes(&attributes, PSA_KEY_TYPE_CHACHA20, PSA_ALG_CHACHA20_POLY1305,
                     PSA_KEY_USAGE_ENCRYPT, 200U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (200U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(AEAD CHACHA20 wrong size)", Status);
#endif

    setkeyattributes(&attributes, PSA_KEY_TYPE_CAMELLIA, PSA_ALG_GCM,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(AEAD wrong algo)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, ((psa_algorithm_t)0x05500f00U),
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(AEAD wrong method)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CCM_STAR_NO_TAG,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(AEAD wrong method)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_VENDOR_FLAG,
                     PSA_KEY_USAGE_ENCRYPT, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(CIPH wrong operation)", Status);

    /* ASymmetric algorithm related */
    setkeyattributes(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                     PSA_ALG_ECDSA(PSA_ALG_SHA3_256),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(PK wrong hash)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                     PSA_ALG_ECDSA(PSA_ALG_SHA_512),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(PK wrong hash/modulus)", Status);

    setkeyattributes(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                     PSA_ALG_ECDSA(PSA_ALG_SHA_384),
                     PSA_KEY_USAGE_SIGN_MESSAGE, 256U, lifetime, 0U);
    Status = psa_import_key(&attributes, DataBuffer, (256U / 8U), &key[0]);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_import_key(PK wrong hash/modulus)", Status);
}
END_TEST

/*----------------------------------------------------------------------------
 * test_NegImportKeyAsn1Parse
 */
START_TEST(test_NegImportKeyAsn1Parse)
{
    TestVector_ASN1_DER_t tv_prvkey_p;
    psa_key_attributes_t attributes;
    psa_key_id_t StatPrvKey;
    psa_status_t Status;
    size_t ModifiedDataLen;
    uint8_t ModifiedData[200] = { 0 };
    uint8_t temp1;

    tv_prvkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_NIST_METHOD,
                                224, true);
    fail_if((tv_prvkey_p == NULL), "Found no valid NIST key", 224);

    /* Setup basic attributes */
    (void)memset(&attributes, 0, sizeof(attributes));
    psa_set_key_type(&attributes,
                     PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDH);
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DERIVE);
    psa_set_key_bits(&attributes, 224);
    psa_set_key_lifetime(&attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);

    ModifiedDataLen = tv_prvkey_p->DataLen;
    (void)memcpy(ModifiedData, tv_prvkey_p->pData, ModifiedDataLen);

    /* Modify start sequence */
    temp1 = ModifiedData[0];
    ModifiedData[0] = 0x31U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(1.1)=", Status);
    ModifiedData[0] = temp1;

    /* Modify sequence length */
    ModifiedData[1] = 0x70U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(1.2)=", Status);
    ModifiedData[1] = temp1;

    /* Modify overall length */
    ModifiedDataLen = 0x20U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(1.3)=", Status);
    ModifiedDataLen = tv_prvkey_p->DataLen;

    /* Modify version */
    temp1 = ModifiedData[4];
    ModifiedData[4] = 0U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(1.4)=", Status);
    ModifiedData[4] = temp1;

    /* Modify curve to OID_EC_GRP_SECP384R1 (supported) */
    temp1 = ModifiedData[43];
    ModifiedData[43] = 0x22U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_INVALID_ARGUMENT != Status), "psa_import_key(1.5)=", Status);

    /* Modify curve to OID_EC_GRP_SECP224K1 (not supported)  */
    ModifiedData[43] = 0x20U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(1.6)=", Status);
    ModifiedData[43] = temp1;

    tv_prvkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_MONT_METHOD,
                                255, true);
    fail_if((tv_prvkey_p == NULL), "Found no valid NIST key", 255);

    /* Setup basic attributes */
    (void)memset(&attributes, 0, sizeof(attributes));
    psa_set_key_type(&attributes,
                     PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY));
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDH);
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DERIVE);
    psa_set_key_bits(&attributes, 255);
    psa_set_key_lifetime(&attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);

    /* Modify start sequence */
    temp1 = ModifiedData[0];
    ModifiedData[0] = 0x31U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(2.1)=", Status);
    ModifiedData[0] = temp1;

    /* Modify sequence length */
    ModifiedData[1] = 0x20U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(2.2)=", Status);
    ModifiedData[1] = temp1;

    /* Modify overall length */
    ModifiedDataLen = 0x20U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(2.3)=", Status);
    ModifiedDataLen = tv_prvkey_p->DataLen;

    /* Modify version */
    temp1 = ModifiedData[4];
    ModifiedData[4] = 2U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(2.4)=", Status);
    ModifiedData[4] = temp1;

    /* Modify curve to OID_ID_ED25519 (supported) */
    temp1 = ModifiedData[11];
    ModifiedData[11] = 0x70U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(2.5)=", Status);
    ModifiedData[11] = temp1;

    /* Modify curve to not supported */
    temp1 = ModifiedData[10];
    ModifiedData[10] = 0x81U;
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(2.6)=", Status);
    ModifiedData[10] = temp1;

    tv_prvkey_p = GetTestVector(TV_ASN1DER_ECC_KEY_TYPE, TV_ASN1DER_TEDWARDS_METHOD,
                                255, true);
    fail_if((tv_prvkey_p == NULL), "Found no valid key", 255);

    /* Setup basic attributes */
    (void)memset(&attributes, 0, sizeof(attributes));
    psa_set_key_type(&attributes,
                     PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY));
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDH);
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DERIVE);
    psa_set_key_bits(&attributes, 255);
    psa_set_key_lifetime(&attributes,
                         (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                         PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);

    /* Modify start sequence */
    Status = psa_import_key(&attributes,
                            ModifiedData, ModifiedDataLen,
                            &StatPrvKey);
    fail_if((PSA_ERROR_DATA_CORRUPT != Status), "psa_import_key(3.1)=", Status);
}
END_TEST

/*----------------------------------------------------------------------------
 * test_NegExportKey
 */
START_TEST(test_NegExportKey)
{
    TestVector_ASN1_DER_t tv_pubkey_p;
    psa_key_attributes_t Attributes;
    psa_key_id_t Key;
    psa_status_t Status;
    size_t DataLen = 0;
    uint8_t DataBuffer[200] = { 0 };

    tv_pubkey_p = GetTestVector(TV_ASN1DER_ECDH_KEY_TYPE, TV_ASN1DER_NIST_METHOD,
                                256U, false);
    fail_if((tv_pubkey_p == NULL), "Found no valid key", 256);

    /* Setup basic attributes */
    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes,
                     PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_algorithm(&Attributes, PSA_ALG_ECDH);
    psa_set_key_usage_flags(&Attributes,
                            (PSA_KEY_USAGE_DERIVE | PSA_KEY_USAGE_EXPORT));
    psa_set_key_bits(&Attributes, 256U);
    psa_set_key_lifetime(&Attributes,
                         (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                         PSA_KEY_PERSISTENCE_VOLATILE);

    /* Import the public key */
    Status = psa_import_key(&Attributes,
                            tv_pubkey_p->pData, tv_pubkey_p->DataLen,
                            &Key);
    fail_if((PSA_SUCCESS != Status), "psa_import_key()=", Status);

    /* test export key arguments */
    Status = psa_export_key(Key, NULL, sizeof(DataBuffer), &DataLen);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_export_key(1)", Status);

    Status = psa_export_key(Key, DataBuffer, sizeof(DataBuffer), NULL);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_export_key(2)", Status);

    Status = psa_export_key(Key, DataBuffer, (256U / 8U), &DataLen);
    fail_if(PSA_ERROR_BUFFER_TOO_SMALL != Status, "psa_export_key(3)", Status);

    Status = psa_export_key(Key, DataBuffer, sizeof(DataBuffer), &DataLen);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_export_key(4)", Status);

    /* Destroy key */
    Status = psa_destroy_key(Key);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key()=", Status);

    /* Setup attributes */
    (void)memset(&Attributes, 0, sizeof(Attributes));
    psa_set_key_type(&Attributes, PSA_KEY_TYPE_AES);
    psa_set_key_algorithm(&Attributes, PSA_ALG_CTR);
    psa_set_key_usage_flags(&Attributes, PSA_KEY_USAGE_ENCRYPT);
    psa_set_key_bits(&Attributes, 128U);
    psa_set_key_lifetime(&Attributes, (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                      PSA_KEY_PERSISTENCE_HSM_ASSET_STORE);

    /* Generate a key */
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_SUCCESS != Status), "psa_generate_key()=", Status);

    Status = psa_export_key(Key, DataBuffer, sizeof(DataBuffer), &DataLen);
    fail_if(PSA_ERROR_NOT_PERMITTED != Status, "psa_export_key(5)", Status);

    /* Destroy key */
    Status = psa_destroy_key(Key);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key()=", Status);

    /* Setup attributes */
    psa_set_key_usage_flags(&Attributes,
                            (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_EXPORT));

    /* Generate a key */
    Status = psa_generate_key(&Attributes, &Key);
    fail_if((PSA_SUCCESS != Status), "psa_generate_key()=", Status);

    Status = psa_export_key(Key, DataBuffer, sizeof(DataBuffer), &DataLen);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_export_key(6)", Status);

    /* Destroy key */
    Status = psa_destroy_key(Key);
    fail_if((PSA_SUCCESS != Status), "psa_destroy_key()=", Status);
}
END_TEST

/*----------------------------------------------------------------------------
 * test_NegDestroyPurgeKey
 */
START_TEST(test_NegDestroyPurgeKey)
{
    psa_status_t Status;

    /* Destroy key */
    Status = psa_destroy_key(0);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_destroy_key(0)=", Status);

    Status = psa_destroy_key(MBEDTLS_MAX_KEY_BUFF_ENTRIES + 1);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_destroy_key(MAX)=", Status);

    /* Purge key */
    Status = psa_purge_key(0);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_purge_key(0)=", Status);

    Status = psa_purge_key(MBEDTLS_MAX_KEY_BUFF_ENTRIES + 1);
    fail_if((PSA_ERROR_INVALID_HANDLE != Status), "psa_purge_key(MAX)=", Status);
}
END_TEST


int
suite_add_test_import_key(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "ImportKey_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_ImportKey, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_ImportKeyECDH) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_NegImportKey) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_NegImportKeyAsn1Parse) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_NegExportKey) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_NegDestroyPurgeKey) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_import_key.c */
