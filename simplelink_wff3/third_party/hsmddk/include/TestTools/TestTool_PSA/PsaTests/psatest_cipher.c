/* psatest_cipher.c
 *
 * Description: cipher
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
#include "testvectors_aes_basic.h"
#include "testvectors_des.h"
#include "testvectors_xts_aes.h"
#include "testvectors_aria_basic.h"

#define PSA_CIPHER_STATE_INIT   0U
#define PSA_CIPHER_STATE_SETUP  1U
#define PSA_CIPHER_STATE_UPDATE 2U
#define PSA_CIPHER_STATE_IV     3U

typedef struct
{
    const uint8_t * Ptx_p;
    uint32_t PtxLen;
    const uint8_t * Ctx_p;
    const uint8_t * Iv_p;
    const uint8_t * key_p;
    uint32_t KeyLen;
} SymcipherCryptTV_t;

static void
setupcipherTVctx(SymcipherCryptTV_t *TVctx,
                 const uint8_t *Ptx_p,
                 uint32_t PtxLen,
                 const uint8_t *Key_p,
                 uint32_t KeyLen,
                 const uint8_t *Ctx_p,
                 const uint8_t * Iv_p)
{
    TVctx->Ptx_p = Ptx_p;
    TVctx->PtxLen = PtxLen;
    TVctx->Ctx_p = Ctx_p;
    TVctx->Iv_p = Iv_p;
    TVctx->key_p = Key_p;
    TVctx->KeyLen = KeyLen;
}

/*----------------------------------------------------------------------------
 * setupcipherkey
 *
 * Helper function to setup key.
 */
static psa_status_t
setupcipherkey(psa_key_id_t * key,
               psa_algorithm_t Mode,
               psa_key_usage_t usage_flag,
               psa_key_type_t key_type,
               psa_key_lifetime_t lifetime,
               psa_key_id_t uid,
               SymcipherCryptTV_t * Vector_p)
{
    psa_key_attributes_t attributes = { 0 };
    size_t bits = (Vector_p->KeyLen) * 8U;
    psa_status_t Status;

    if (0U == Vector_p->KeyLen)
    {
        Status = PSA_ERROR_INSUFFICIENT_DATA;
    }
    else
    {
        psa_set_key_type(&attributes, key_type);
        psa_set_key_algorithm(&attributes, Mode);
        psa_set_key_usage_flags(&attributes, usage_flag);
        psa_set_key_bits(&attributes, bits);
        psa_set_key_lifetime(&attributes, lifetime);
        if (uid != 0U)
        {
            psa_set_key_id(&attributes, uid);
        }
        Status = psa_import_key(&attributes, Vector_p->key_p, Vector_p->KeyLen, key);
    }

    return Status;
}

/*----------------------------------------------------------------------------
 * setupcipherkey_random
 *
 * Helper function to setup key with random key.
 */
static psa_status_t
setupcipherkey_random(psa_key_id_t * key,
                      psa_algorithm_t Mode,
                      psa_key_usage_t usage_flag,
                      psa_key_type_t key_type,
                      psa_key_lifetime_t lifetime,
                      psa_key_id_t uid,
                      uint32_t key_len)
{
    psa_key_attributes_t attributes = { 0 };
    size_t bits = key_len * 8U;
    psa_status_t Status;

    if (0U == key_len)
    {
        Status = PSA_ERROR_INSUFFICIENT_DATA;
    }
    else
    {
        psa_set_key_type(&attributes, key_type);
        psa_set_key_algorithm(&attributes, Mode);
        psa_set_key_usage_flags(&attributes, usage_flag);
        psa_set_key_bits(&attributes, bits);
        psa_set_key_lifetime(&attributes, lifetime);
        if (uid != 0U)
        {
            psa_set_key_id(&attributes, uid);
        }
        Status = psa_generate_key(&attributes, key);
    }

    return Status;
}

/*----------------------------------------------------------------------------
 * do_cipher_test
 *
 * Helper function that runs a single cipher test.
 */
static int
do_cipher_test(uint32_t VectorIndex,
               psa_key_id_t key,
               psa_key_id_t key_ver,
               psa_algorithm_t alg,
               uint16_t key_type,
               SymcipherCryptTV_t * Vector_p)

{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t output_length = 0U;
    size_t IVSize = 0U;
    uint8_t *plaintext = NULL;
    size_t plaintext_size = 0U;
    uint8_t *ciphertext = NULL;
    size_t ciphertext_size = 0U;
    uint8_t *decrypt_output = NULL;

    plaintext = (uint8_t *)SFZUTF_MALLOC(Vector_p->PtxLen);
    fail_if(plaintext == NULL, "Allocation ", (int)Vector_p->PtxLen);
    (void)memset(plaintext, 0, Vector_p->PtxLen);
    plaintext_size = Vector_p->PtxLen;
    ciphertext = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtxLen) + 16); // +16 max iv size
    ciphertext_size = (Vector_p->PtxLen) + 16;
    fail_if(ciphertext == NULL, "Allocation ", (int)(Vector_p->PtxLen) + 16);
    (void)memset(ciphertext, 0, (Vector_p->PtxLen) + 16);
    decrypt_output = (uint8_t *)SFZUTF_MALLOC(Vector_p->PtxLen);
    fail_if(decrypt_output == NULL, "Allocation ", (int)Vector_p->PtxLen);
    (void)memset(decrypt_output, 0, Vector_p->PtxLen);

    (void)memcpy(plaintext, Vector_p->Ptx_p, plaintext_size);
    IVSize = PSA_CIPHER_IV_LENGTH(key_type, alg);
    Status = psa_cipher_encrypt(key, alg, plaintext, Vector_p->PtxLen,
                                ciphertext, ciphertext_size, &output_length);
    fail_if(PSA_SUCCESS != Status, "single encrypt operation", Status);
    fail_if(Vector_p->PtxLen != (output_length - IVSize), "Length mismatch ", (int)output_length);

    ciphertext_size = 0;
    Status = psa_cipher_decrypt(key_ver, alg, ciphertext, ((Vector_p->PtxLen) + IVSize),
                                decrypt_output, Vector_p->PtxLen, &output_length);
    fail_if(PSA_SUCCESS != Status, "single decrypt operation", Status);
    fail_if(Vector_p->PtxLen != output_length, "Length mismatch ", (int)output_length);
    fail_if(memcmp(Vector_p->Ptx_p, decrypt_output, Vector_p->PtxLen) != 0, "", VectorIndex);

    SFZUTF_FREE(plaintext);
    SFZUTF_FREE(ciphertext);
    SFZUTF_FREE(decrypt_output);
    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * do_cipher_test_padding
 *
 * Helper function that runs a single cipher test with non block size input.
 */
static int
do_cipher_test_padding(uint32_t VectorIndex,
                       psa_key_id_t key,
                       psa_key_id_t key_ver,
                       psa_algorithm_t alg,
                       uint16_t key_type,
                       SymcipherCryptTV_t * Vector_p)

{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t output_length = 0U;
    size_t IVSize = 0U;
    uint8_t * plaintext;
    size_t plaintext_size = (Vector_p->PtxLen) - 1U;
    uint8_t * ciphertext;
    size_t ciphertext_size = (Vector_p->PtxLen) + 16U - 1;
    uint8_t * decrypt_output;

    plaintext = (uint8_t *)SFZUTF_MALLOC(plaintext_size); // -1 byte (need padding)
    fail_if(plaintext == NULL, "Allocation ", (int)plaintext_size);
    (void)memset(plaintext, 0, plaintext_size);
    ciphertext = (uint8_t *)SFZUTF_MALLOC(ciphertext_size); // +16 max iv size - 1 padding
    fail_if(ciphertext == NULL, "Allocation ", (int)ciphertext_size);
    (void)memset(ciphertext, 0, ciphertext_size);
    decrypt_output = (uint8_t *)SFZUTF_MALLOC(plaintext_size);
    fail_if(decrypt_output == NULL, "Allocation ", (int)plaintext_size);
    (void)memset(decrypt_output, 0, plaintext_size);

    (void)memcpy(plaintext, Vector_p->Ptx_p, plaintext_size);
    IVSize = PSA_CIPHER_IV_LENGTH(key_type, alg);
    Status = psa_cipher_encrypt(key, alg, plaintext, plaintext_size,
                                ciphertext, ciphertext_size, &output_length);
    fail_if(PSA_SUCCESS != Status, "single encrypt operation", Status);
    fail_if(plaintext_size != (output_length - IVSize), "Length mismatch enc", (int)output_length);

    output_length = 0;
    Status = psa_cipher_decrypt(key_ver, alg, ciphertext, (plaintext_size + IVSize),
                                decrypt_output, plaintext_size, &output_length);
    fail_if(PSA_SUCCESS != Status, "single decrypt operation", Status);
    fail_if(plaintext_size != output_length, "Length mismatch dec", (int)output_length);
    fail_if(memcmp(Vector_p->Ptx_p, decrypt_output, output_length) != 0, "", VectorIndex);

    SFZUTF_FREE(plaintext);
    SFZUTF_FREE(ciphertext);
    SFZUTF_FREE(decrypt_output);
    return END_TEST_SUCCES;
}


/*----------------------------------------------------------------------------
 * do_cipher_update
 *
 * Helper function that runs cipher update.
 */
static int
do_cipher_update(uint32_t VectorIndex,
                 psa_cipher_operation_t *SymContext_p,
                 bool fencrypt,
                 SymcipherCryptTV_t * Vector_p,
                 uint16_t key_type)
{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    uint8_t *output = NULL;
    size_t output_length = 0U;
    size_t block_size = PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type);

    output = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtxLen));
    fail_if(output == NULL, "Allocation ", (int)(Vector_p->PtxLen));
    (void)memset(output, 0, Vector_p->PtxLen);
    if (fencrypt)
    {
        Status = psa_cipher_update(SymContext_p, Vector_p->Ptx_p, Vector_p->PtxLen, output, Vector_p->PtxLen, &output_length);
        fail_if(PSA_SUCCESS != Status, "Update Encrypt operation", Status);
        if (output_length != 0)
        {
            fail_if(((Vector_p->PtxLen) - block_size) != output_length, "Length mismatch ", (int)output_length);
            fail_if(memcmp(Vector_p->Ctx_p, output, output_length), "enc update data mismatch ", VectorIndex);
        }
    }
    else
    {
        Status = psa_cipher_update(SymContext_p, Vector_p->Ctx_p, Vector_p->PtxLen, output, Vector_p->PtxLen, &output_length);
        fail_if(PSA_SUCCESS != Status, "Update Decrypt operation", Status);
        if (output_length != 0)
        {
            fail_if(((Vector_p->PtxLen) - block_size) != output_length, "Length mismatch ", (int)output_length);
            fail_if(memcmp(Vector_p->Ptx_p, output, output_length), "dec update data mismatch ", VectorIndex);
        }
    }

    SFZUTF_FREE(output);
    return END_TEST_SUCCES;
}
/*----------------------------------------------------------------------------
 * do_cipher_final
 *
 * Helper function that runs cipher Final.
 */
static int
do_cipher_final(uint32_t VectorIndex,
                psa_cipher_operation_t *SymContext_p,
                bool fencrypt,
                SymcipherCryptTV_t * Vector_p,
                uint16_t key_type)
{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t output_length = 0U;
    size_t block_size = PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type);
    uint8_t *output = NULL;
    size_t output_size = 0U;

    output = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtxLen) + 15);
    output_size = (Vector_p->PtxLen) + 15;
    fail_if(output == NULL, "Allocation ", (int)(Vector_p->PtxLen) + 15);
    (void)memset(output, 0, (Vector_p->PtxLen) + 15);
    if (fencrypt)
    {
        Status = psa_cipher_finish(SymContext_p, output, output_size, &output_length);
        fail_if(PSA_SUCCESS != Status, "enc psa_cipher_finish", Status);
        fail_if(block_size != output_length, "enc final Length mismatch ", (int)output_length);
        fail_if(memcmp(Vector_p->Ctx_p+(Vector_p->PtxLen) - block_size, output, block_size) != 0, "Final data mismatch", VectorIndex);
    }
    else
    {
        Status = psa_cipher_finish(SymContext_p, output, output_size, &output_length);
        fail_if(PSA_SUCCESS != Status, "dec psa_cipher_finish", Status);
        fail_if(block_size != output_length, "dec final Length mismatch ", (int)output_length);
        fail_if(memcmp(Vector_p->Ptx_p+(Vector_p->PtxLen) - block_size, output, block_size) != 0, "dec Final data mismatch", VectorIndex);
    }

    SFZUTF_FREE(output);
    return END_TEST_SUCCES;
}

START_TEST(test_sym_crypto_aes_padding)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_BASIC_t tv_p;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime = 0;

        tv_p = test_vectors_aes_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->Mode != TESTVECTORS_MODE_CTR)
        {
            test_vectors_aes_basic_release(tv_p);
            continue;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        Status = setupcipherkey(&key, PSA_ALG_CTR, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey enc()", Status);
        Status = setupcipherkey(&key_ver, PSA_ALG_CTR, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey dec()", Status);

        if (END_TEST_SUCCES != do_cipher_test_padding(ndx, key, key_ver, PSA_ALG_CTR, PSA_KEY_TYPE_AES, &tv_cipher))
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        test_vectors_aes_basic_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_sym_crypto_aes
 *
 * Test with AES test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_sym_crypto_aes)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_BASIC_t tv_p;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_id_t uid;
        psa_key_id_t uid_ver;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;

        tv_p = test_vectors_aes_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

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
            // Not (yet) supported
            test_vectors_aes_basic_release(tv_p);
            continue;
        }

        uid = 0U;
        uid_ver = 0U;
        if (_i == 1)
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
            uid_ver = 2U;
        }
        else if (_i == 2)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
        }
        else if (_i == 3)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }
        else if (_i == 4)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
            uid_ver = 2U;
        }
        else
        {
            /* Default/_i == 0 */
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }

        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, uid, &tv_cipher);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
        fail_if(PSA_SUCCESS != Status, "setupcipherkey enc()", Status);
        Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, uid_ver, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey dec()", Status);
        if (do_cipher_test(ndx, key, key_ver, Mode, PSA_KEY_TYPE_AES, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        test_vectors_aes_basic_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST(test_sym_crypto_xts_aes)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_XTS_AES_t tv_p;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_xts_aes_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Tweak_p);
        Status = setupcipherkey(&key, PSA_ALG_XTS, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey enc()", Status);
        Status = setupcipherkey(&key_ver, PSA_ALG_XTS, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey dec()", Status);
        if (END_TEST_SUCCES != do_cipher_test(ndx, key, key_ver, PSA_ALG_XTS, PSA_KEY_TYPE_AES, &tv_cipher))
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        test_vectors_xts_aes_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_multipart_enc
 *
 * Test with AES continuation encrypt test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_sym_crypto_aes_multipart_enc)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    bool fencrypt = true;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_BASIC_t tv_p;
        psa_cipher_operation_t SymContext;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t uid;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;
        psa_status_t Status;

        tv_p = test_vectors_aes_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

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
            // Not (yet) supported
            test_vectors_aes_basic_release(tv_p);
            continue;
        }

        uid = 0U;
        if (_i == 1)
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
        }
        else if (_i == 2)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
        }
        else if (_i == 3)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }
        else if (_i == 4)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
        }
        else
        {
            /* Default/_i == 0 */
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_cipher, 0, sizeof(tv_cipher));
        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, uid, &tv_cipher);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
        if (PSA_SUCCESS == Status)
        {
            Status = psa_cipher_encrypt_setup(&SymContext, key, Mode);
            fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()=", Status);
            if (PSA_ALG_ECB_NO_PADDING !=Mode)
            {
                Status = psa_cipher_set_iv(&SymContext, tv_cipher.Iv_p, 16U);
                fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);
            }
            if(do_cipher_update(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_AES) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if(do_cipher_final(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_AES) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    (void)psa_destroy_key(key);
                    Failed++;
                }
                else
                {
                    Status = psa_destroy_key(key);
                    if (PSA_SUCCESS != Status)
                    {
                        LOG_CRIT("Processed vector %d\n", ndx);
                        Failed++;
                    }
                    else
                    {
                        Success++;
                    }
                }
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        Status = psa_cipher_abort(&SymContext);
        fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);
        fail_if(SymContext.alg != PSA_ALG_NONE, "psa_cipher_abort()=", SymContext.alg);
        test_vectors_aes_basic_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_multipart_dec
 *
 * Test with AES continuation decrypt test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_sym_crypto_aes_multipart_dec)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_BASIC_t tv_p;
        psa_cipher_operation_t SymContext;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t uid;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;
        psa_status_t Status;
        bool fencrypt = false;

        tv_p = test_vectors_aes_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

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
            // Not (yet) supported
            test_vectors_aes_basic_release(tv_p);
            continue;
        }

        uid = 0U;
        if (_i == 1)
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
        }
        else if (_i == 2)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
        }
        else if (_i == 3)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }
        else if (_i == 4)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
        }
        else
        {
            /* Default/_i == 0 */
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_cipher, 0, sizeof(tv_cipher));
        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, uid, &tv_cipher);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
        if (PSA_SUCCESS == Status)
        {
            Status = psa_cipher_decrypt_setup(&SymContext, key, Mode);
            fail_if(Status != PSA_SUCCESS, "psa_cipher_decrypt_setup()=", Status);
            if (PSA_ALG_ECB_NO_PADDING !=Mode)
            {
                Status = psa_cipher_set_iv(&SymContext, tv_cipher.Iv_p, 16U);
                fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);
            }
            if(do_cipher_update(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_AES) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if(do_cipher_final(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_AES) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    (void)psa_destroy_key(key);
                    Failed++;
                }
                else
                {
                    Status = psa_destroy_key(key);
                    if (PSA_SUCCESS != Status)
                    {
                        LOG_CRIT("Processed vector %d\n", ndx);
                        Failed++;
                    }
                    else
                    {
                        Success++;
                    }
                }
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        test_vectors_aes_basic_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

#ifdef PSATEST_SYM_ALGO_ARIA
START_TEST(test_sym_crypto_aria)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_ARIA_BASIC_t tv_p;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;

        tv_p = test_vectors_aria_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

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
            // Not (yet) supported
            test_vectors_aria_basic_release(tv_p);
            continue;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey enc()", Status);
        Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey dec()", Status);
        if (END_TEST_SUCCES != do_cipher_test(ndx, key, key_ver, Mode, PSA_KEY_TYPE_ARIA, &tv_cipher))
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }

        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        test_vectors_aria_basic_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_ARIA
START_TEST(test_sym_crypto_aria_multipart_enc)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_ARIA_BASIC_t tv_p;
        psa_cipher_operation_t SymContext;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;
        psa_status_t Status;
        bool fencrypt = true;

        tv_p = test_vectors_aria_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

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
            // Not (yet) supported
            test_vectors_aria_basic_release(tv_p);
            continue;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_cipher, 0, sizeof(tv_cipher));
        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        if (PSA_SUCCESS == setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_cipher))
        {
            Status = psa_cipher_encrypt_setup(&SymContext, key, Mode);
            fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()=", Status);
            if (PSA_ALG_ECB_NO_PADDING !=Mode)
            {
                Status = psa_cipher_set_iv(&SymContext, tv_cipher.Iv_p, 16U);
                fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);
            }
            if(do_cipher_update(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_ARIA) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if(do_cipher_final(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_ARIA) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    (void)psa_destroy_key(key);
                    Failed++;
                }
                else
                {
                    Status = psa_destroy_key(key);
                    if (PSA_SUCCESS != Status)
                    {
                        LOG_CRIT("Processed vector %d\n", ndx);
                        Failed++;
                    }
                    else
                    {
                        Success++;
                    }
                }
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        test_vectors_aria_basic_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_ARIA
START_TEST(test_sym_crypto_aria_multipart_dec)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_ARIA_BASIC_t tv_p;
        psa_cipher_operation_t SymContext;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;
        psa_status_t Status;
        bool fencrypt = false;

        tv_p = test_vectors_aria_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

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
            // Not (yet) supported
            test_vectors_aria_basic_release(tv_p);
            continue;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_cipher, 0, sizeof(tv_cipher));
        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        if (PSA_SUCCESS == setupcipherkey(&key, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_cipher))
        {
            Status = psa_cipher_decrypt_setup(&SymContext, key, Mode);
            fail_if(Status != PSA_SUCCESS, "psa_cipher_decrypt_setup()=", Status);
            if (PSA_ALG_ECB_NO_PADDING !=Mode)
            {
                Status = psa_cipher_set_iv(&SymContext, tv_cipher.Iv_p, 16U);
                fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);
            }
            if(do_cipher_update(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_ARIA) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if(do_cipher_final(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_ARIA) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    (void)psa_destroy_key(key);
                    Failed++;
                }
                else
                {
                    Status = psa_destroy_key(key);
                    if (PSA_SUCCESS != Status)
                    {
                        LOG_CRIT("Processed vector %d\n", ndx);
                        Failed++;
                    }
                    else
                    {
                        Success++;
                    }
                }
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        test_vectors_aria_basic_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_3DES
START_TEST(test_sym_crypto_des)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_DES_t tv_p;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;

        tv_p = test_vectors_des_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->KeyLen < 24U)
        {
            // Only TDES is supported
            test_vectors_des_release(tv_p);
            continue;
        }

        switch (tv_p->Mode)
        {
        case TESTVECTORS_MODE_ECB:
            Mode = PSA_ALG_ECB_NO_PADDING;
            break;
        case TESTVECTORS_MODE_CBC:
            Mode = PSA_ALG_CBC_NO_PADDING;
            break;
        default:
            Mode = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Mode)
        {
            // Not (yet) supported
            test_vectors_des_release(tv_p);
            continue;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_DES, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey enc()", Status);
        Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_DES, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey dec()", Status);
        if (do_cipher_test(ndx, key, key_ver, Mode, PSA_KEY_TYPE_DES, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }

        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        test_vectors_des_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_3DES
START_TEST(test_sym_crypto_des_multipart_enc)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_DES_t tv_p;
        psa_cipher_operation_t SymContext;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;
        psa_status_t Status;
        bool fencrypt = true;

        tv_p = test_vectors_des_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->KeyLen < 24U)
        {
            // Only TDES is supported
            test_vectors_des_release(tv_p);
            continue;
        }

        switch (tv_p->Mode)
        {
        case TESTVECTORS_MODE_ECB:
            Mode = PSA_ALG_ECB_NO_PADDING;
            break;
        case TESTVECTORS_MODE_CBC:
            Mode = PSA_ALG_CBC_NO_PADDING;
            break;
        default:
            Mode = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Mode)
        {
            // Not (yet) supported
            test_vectors_des_release(tv_p);
            continue;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_cipher, 0, sizeof(tv_cipher));
        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        if (PSA_SUCCESS == setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_DES, lifetime, 0U, &tv_cipher))
        {
            Status = psa_cipher_encrypt_setup(&SymContext, key, Mode);
            fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()=", Status);
            if (PSA_ALG_ECB_NO_PADDING !=Mode)
            {
                Status = psa_cipher_set_iv(&SymContext, tv_cipher.Iv_p, 8U);
                fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);
            }
            if(do_cipher_update(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_DES) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if(do_cipher_final(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_DES) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    (void) psa_destroy_key(key);
                    Failed++;
                }
                else
                {
                    Status = psa_destroy_key(key);
                    if (PSA_SUCCESS != Status)
                    {
                        LOG_CRIT("Processed vector %d\n", ndx);
                        Failed++;
                    }
                    else
                    {
                        Success++;
                    }
                }
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        test_vectors_des_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_3DES
START_TEST(test_sym_crypto_des_multipart_dec)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_DES_t tv_p;
        psa_cipher_operation_t SymContext;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;
        psa_status_t Status;
        bool fencrypt = false;

        tv_p = test_vectors_des_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->KeyLen < 24U)
        {
            // Only TDES is supported
            test_vectors_des_release(tv_p);
            continue;
        }

        switch (tv_p->Mode)
        {
        case TESTVECTORS_MODE_ECB:
            Mode = PSA_ALG_ECB_NO_PADDING;
            break;
        case TESTVECTORS_MODE_CBC:
            Mode = PSA_ALG_CBC_NO_PADDING;
            break;
        default:
            Mode = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Mode)
        {
            // Not (yet) supported
            test_vectors_des_release(tv_p);
            continue;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_cipher, 0, sizeof(tv_cipher));
        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        if (PSA_SUCCESS == setupcipherkey(&key, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_DES, lifetime, 0U, &tv_cipher))
        {
            Status = psa_cipher_decrypt_setup(&SymContext, key, Mode);
            fail_if(Status != PSA_SUCCESS, "psa_cipher_decrypt_setup()=", Status);
            if (PSA_ALG_ECB_NO_PADDING != Mode)
            {
                Status = psa_cipher_set_iv(&SymContext, tv_cipher.Iv_p, 8U);
                fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);
            }
            if(do_cipher_update(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_DES) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if(do_cipher_final(ndx, &SymContext, fencrypt, &tv_cipher, PSA_KEY_TYPE_DES) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    (void)psa_destroy_key(key);
                    Failed++;
                }
                else
                {
                    Status = psa_destroy_key(key);
                    if (PSA_SUCCESS != Status)
                    {
                        LOG_CRIT("Processed vector %d\n", ndx);
                        Failed++;
                    }
                    else
                    {
                        Success++;
                    }
                }
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        test_vectors_des_release(tv_p);
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

/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_random
 */
START_TEST(test_sym_crypto_aes_random)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_BASIC_t tv_p;
        SymcipherCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_id_t uid;
        psa_key_lifetime_t lifetime = 0;
        psa_algorithm_t Mode;

        tv_p = test_vectors_aes_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

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
            // Not (yet) supported
            test_vectors_aes_basic_release(tv_p);
            continue;
        }

        if (_i == 0)
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
            uid = 0U;
        }
        else
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
        }

        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        Status = setupcipherkey_random(&key, Mode, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_EXPORT,
                                        PSA_KEY_TYPE_AES, lifetime, uid, tv_cipher.KeyLen);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey_random enc()", Status);
        uint8_t *exported_key = (uint8_t *)SFZUTF_MALLOC(tv_cipher.KeyLen);
        fail_if(exported_key == NULL, "Allocation ", (int)tv_cipher.KeyLen);
        size_t key_length = 0;
        (void)memset(exported_key, 0, tv_cipher.KeyLen);
        Status = psa_export_key(key, exported_key, tv_cipher.KeyLen, &key_length);
        fail_if(PSA_SUCCESS != Status, "psa_export_key()", Status);
        if (key_length !=0)
        {
            psa_key_attributes_t attributes;
            size_t bits = key_length * 8U;
            psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
            psa_set_key_algorithm(&attributes, Mode);
            psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DECRYPT);
            psa_set_key_bits(&attributes, bits);
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
            psa_set_key_lifetime(&attributes, lifetime);
            Status = psa_import_key(&attributes, exported_key, key_length, &key_ver);
            fail_if(PSA_SUCCESS != Status, "psa_import_key()", Status);
        }
        if (do_cipher_test(ndx, key, key_ver, Mode, PSA_KEY_TYPE_AES, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        SFZUTF_FREE(exported_key);
        test_vectors_aes_basic_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_gen_iv
 */
START_TEST(test_sym_crypto_aes_gen_iv)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_BASIC_t tv_p;
        SymcipherCryptTV_t tv_cipher;
        psa_cipher_operation_t SymContext;
        psa_cipher_operation_t SymContext_ver;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime;
        psa_algorithm_t Mode;
        uint8_t iv[16] = {0};
        size_t iv_size = 16;
        size_t iv_length = 0;

        tv_p = test_vectors_aes_basic_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

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
        if (Mode != PSA_ALG_CBC_NO_PADDING)
        {
            test_vectors_aes_basic_release(tv_p);
            continue;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

        setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
        Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT,PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey enc()", Status);
        Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupcipherkey dec()", Status);

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&SymContext_ver, 0, sizeof(SymContext_ver));

        Status = psa_cipher_encrypt_setup(&SymContext, key, Mode);
        fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()=", Status);
        Status = psa_cipher_generate_iv(&SymContext, iv, iv_size, &iv_length);
        fail_if(Status != PSA_SUCCESS, "psa_cipher_generate_iv()=", Status);
        //Do encrypt with generated IV
        uint8_t *output = (uint8_t *)SFZUTF_MALLOC((tv_cipher.PtxLen));
        fail_if(output == NULL, "Allocation ", (int)(tv_cipher.PtxLen));
        (void)memset(output, 0, tv_cipher.PtxLen);
        size_t output_length = 0;
        size_t output_len_final = 0;
        size_t output_size = tv_cipher.PtxLen;
        Status = psa_cipher_update(&SymContext, tv_cipher.Ptx_p, tv_cipher.PtxLen, output, tv_cipher.PtxLen, &output_length);
        fail_if(PSA_SUCCESS != Status, "Update Encrypt operation", Status);
        Status = psa_cipher_finish(&SymContext, &output[output_length], output_size, &output_len_final);
        fail_if(PSA_SUCCESS != Status, "final Encrypt operation", Status);

        Status = psa_cipher_decrypt_setup(&SymContext_ver, key_ver, Mode);
        fail_if(Status != PSA_SUCCESS, "psa_cipher_decrypt_setup()=", Status);
        Status = psa_cipher_set_iv(&SymContext_ver, iv, iv_length);
        fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);
        //Do decrypt with generated IV
        uint8_t *output_dec = (uint8_t *)SFZUTF_MALLOC((tv_cipher.PtxLen));
        fail_if(output_dec == NULL, "Allocation ", (int)(tv_cipher.PtxLen));
        (void)memset(output_dec, 0, tv_cipher.PtxLen);
        size_t output_len_update = 0;
        Status = psa_cipher_update(&SymContext_ver, output, tv_cipher.PtxLen, output_dec, tv_cipher.PtxLen, &output_len_update);
        fail_if(PSA_SUCCESS != Status, "Update decrypt operation", Status);
        Status = psa_cipher_finish(&SymContext_ver, &output_dec[output_len_update], output_size, &output_len_final);
        fail_if(PSA_SUCCESS != Status, "final decrypt operation", Status);
        fail_if(tv_cipher.PtxLen != (output_len_final+output_len_update), "Length mismatch ", (int)output_length);
        if (memcmp(tv_cipher.Ptx_p, output_dec, tv_cipher.PtxLen) != 0)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }

        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        SFZUTF_FREE(output);
        SFZUTF_FREE(output_dec);
        test_vectors_aes_basic_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_mul_padding
 *
 * Test with AES continuation with chunk inputs that is not block aligned test.
 */
START_TEST(test_sym_crypto_aes_mul_padding)
{
    uint32_t ndx = 6;
    int Failed = 0;
    int Success = 0;

    TestVector_AES_BASIC_t tv_p;
    psa_cipher_operation_t SymContext;
    psa_cipher_operation_t SymContext_ver;
    SymcipherCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    psa_key_lifetime_t lifetime;
    psa_algorithm_t Mode;
    psa_status_t Status;
    const uint8_t *input;

    tv_p = test_vectors_aes_basic_get(ndx);
    if (tv_p == NULL)
    {
        return END_TEST_FAIL;
    }

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
        // Not (yet) supported
        test_vectors_aes_basic_release(tv_p);
        return END_TEST_FAIL;
    }

    /* Default/_i == 0 */
    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

    memset(&SymContext, 0, sizeof(SymContext));
    memset(&SymContext_ver, 0, sizeof(SymContext_ver));
    memset(&tv_cipher, 0, sizeof(tv_cipher));

    setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
    Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupcipherkey enc()", Status);
    Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupcipherkey enc()", Status);

    Status = psa_cipher_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()=", Status);

    Status = psa_cipher_set_iv(&SymContext, tv_cipher.Iv_p, 16U);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);

    uint8_t *output = (uint8_t *)SFZUTF_MALLOC((tv_cipher.PtxLen) - 1);
    fail_if(output == NULL, "Allocation ", (int)(tv_cipher.PtxLen) - 1);
    (void)memset(output, 0, tv_cipher.PtxLen - 1);
    size_t output_length = 0U;
    size_t Total_output_length = 0;

    input = tv_cipher.Ptx_p;
    Status = psa_cipher_update(&SymContext, input, 16, output, tv_cipher.PtxLen - 1, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_update()=", Status);
    Total_output_length = Total_output_length + output_length;

    Status = psa_cipher_update(&SymContext, &input[16], 16, &output[Total_output_length], tv_cipher.PtxLen - 1, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_update()=", Status);
    Total_output_length = Total_output_length + output_length;

    Status = psa_cipher_update(&SymContext, &input[32], 31, &output[Total_output_length], tv_cipher.PtxLen - 1, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_update()=", Status);
    Total_output_length = Total_output_length + output_length;

    Status = psa_cipher_finish(&SymContext, &output[Total_output_length], tv_cipher.PtxLen - 1, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_finish()=", Status);
    Total_output_length = Total_output_length + output_length;

    fail_if((tv_cipher.PtxLen -1) != Total_output_length, "final Length mismatch ", (int)Total_output_length);
    if (memcmp(tv_cipher.Ctx_p, output, Total_output_length) != 0)
    {
        LOG_CRIT("Processed vector %d\n", ndx);
        Failed++;
    }
    else
    {
        Success++;
    }

    (void)memset(output, 0, tv_cipher.PtxLen - 1);
    output_length = 0U;
    Total_output_length = 0;
    Status = psa_cipher_decrypt_setup(&SymContext_ver, key_ver, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()=", Status);

    Status = psa_cipher_set_iv(&SymContext_ver, tv_cipher.Iv_p, 16U);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_set_iv()=", Status);

    input = tv_cipher.Ctx_p;
    Status = psa_cipher_update(&SymContext_ver, input, 16, output, tv_cipher.PtxLen - 1, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_update()=", Status);
    Total_output_length = Total_output_length + output_length;

    Status = psa_cipher_update(&SymContext_ver, &input[16], 16, &output[Total_output_length], tv_cipher.PtxLen - 1, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_update()=", Status);
    Total_output_length = Total_output_length + output_length;

    Status = psa_cipher_update(&SymContext_ver, &input[32], 31, &output[Total_output_length], tv_cipher.PtxLen - 1, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_update()=", Status);
    Total_output_length = Total_output_length + output_length;

    Status = psa_cipher_finish(&SymContext_ver, &output[Total_output_length], tv_cipher.PtxLen - 1, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_finish()=", Status);
    Total_output_length = Total_output_length + output_length;
    fail_if((tv_cipher.PtxLen -1) != Total_output_length, "final Length mismatch ", (int)Total_output_length);
    if (memcmp(tv_cipher.Ptx_p, output, Total_output_length) != 0)
    {
        LOG_CRIT("Processed vector %d\n", ndx);
        Failed++;
    }
    else
    {
        Success++;
    }

    SFZUTF_FREE(output);
    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
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
 * Some negative cipher tests
 *--------------------------------------------------------------------------*/
START_TEST(test_cipher_state)
{
    psa_cipher_operation_t SymContext;
    psa_algorithm_t Mode = PSA_ALG_CTR;
    TestVector_AES_BASIC_t tv_p;
    SymcipherCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    uint8_t iv_buff[128];
    size_t iv_size = 16;
    uint8_t output[128];
    size_t output_length;
    size_t iv_length ;
    psa_status_t Status;

    tv_p = test_vectors_aes_basic_get(6);
    setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
    Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);
    Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_SETUP;
    Status = psa_cipher_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_encrypt_setup()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_SETUP;
    Status = psa_cipher_decrypt_setup(&SymContext, key_ver, Mode);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_decrypt_setup()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    SymContext.IVSize = iv_size;
    Status = psa_cipher_generate_iv(&SymContext, iv_buff, iv_size, &iv_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_generate_iv()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_SETUP;
    SymContext.Mode = PSA_ALG_ECB_NO_PADDING;
    Status = psa_cipher_generate_iv(&SymContext, iv_buff, iv_size, &iv_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_generate_iv()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_SETUP;
    SymContext.Mode = PSA_ALG_ECB_NO_PADDING;
    Status = psa_cipher_set_iv(&SymContext, iv_buff, iv_size);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_set_iv()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    SymContext.Mode = PSA_ALG_CTR;
    Status = psa_cipher_set_iv(&SymContext, iv_buff, iv_size);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_set_iv()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    Mode = PSA_ALG_ECB_NO_PADDING;
    Status = psa_cipher_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()=", Status);
    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    Status = psa_cipher_update(&SymContext, tv_cipher.Ptx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_update()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_cipher_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    Mode = PSA_ALG_CTR;
    Status = psa_cipher_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()=", Status);
    Status = psa_cipher_update(&SymContext, tv_cipher.Ptx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_update()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_cipher_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    Status = psa_cipher_finish(&SymContext, output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_finish()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_SETUP;
    Status = psa_cipher_finish(&SymContext, output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_finish()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_IV;
    Status = psa_cipher_finish(&SymContext, output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_cipher_finish()=", Status);

    Status = psa_cipher_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
    test_vectors_aes_basic_release(tv_p);
}
END_TEST

START_TEST(test_cipher_invalid_algorithm)
{
    psa_cipher_operation_t SymContext;
    psa_algorithm_t Mode = PSA_ALG_CTR;
    TestVector_AES_BASIC_t tv_p;
#ifdef PSATEST_SYM_ALGO_3DES
    TestVector_DES_t tv_p_DES;
#endif
    SymcipherCryptTV_t tv_cipher;
    SymcipherCryptTV_t tv_des;
    psa_key_id_t key = PSA_KEY_ID_NULL;
    psa_key_id_t key_ver = PSA_KEY_ID_NULL;
#ifdef PSATEST_SYM_ALGO_3DES
    psa_key_id_t key_des = PSA_KEY_ID_NULL;
    psa_key_id_t key_des_ver = PSA_KEY_ID_NULL;
#endif
    uint8_t output[128];
    size_t output_length;
    psa_status_t Status;

    tv_p = test_vectors_aes_basic_get(6);
    fail_if(NULL == tv_p, "No test vector", 0);

    setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
    Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create AES key", Status);
    Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create AES key", Status);

#ifdef PSATEST_SYM_ALGO_3DES
    tv_p_DES = test_vectors_des_get(4);
    fail_if(NULL == tv_p_DES, "No test vector", 0);

    setupcipherTVctx(&tv_des, tv_p_DES->Ptx_p, tv_p_DES->PtxLen, tv_p_DES->Key_p, tv_p_DES->KeyLen, tv_p_DES->Ctx_p, tv_p_DES->Iv_p);
    Status = setupcipherkey(&key_des, PSA_ALG_ECB_NO_PADDING, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_DES, 0U, 0U, &tv_des);
    fail_if(PSA_SUCCESS != Status,"Could not create DES key", Status);
    Status = setupcipherkey(&key_des_ver, PSA_ALG_ECB_NO_PADDING, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_DES, 0U, 0U, &tv_des);
    fail_if(PSA_SUCCESS != Status,"Could not create DES key", Status);
#endif

    (void)memset(&SymContext, 0, sizeof(SymContext));

    Status = psa_cipher_encrypt(key, PSA_ALG_SHA_256, tv_cipher.Ptx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(key, PSA_ALG_CFB, tv_cipher.Ptx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt()=", Status);

#ifdef PSATEST_SYM_ALGO_3DES
    Status = psa_cipher_encrypt(key_des, PSA_ALG_CTR, tv_cipher.Ptx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(key_des, PSA_ALG_XTS, tv_cipher.Ptx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_cipher_encrypt()=", Status);
#endif

    Status = psa_cipher_decrypt(key_ver, PSA_ALG_SHA_256, tv_cipher.Ctx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(key_ver, PSA_ALG_CFB, tv_cipher.Ctx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt()=", Status);

#ifdef PSATEST_SYM_ALGO_3DES
    Status = psa_cipher_decrypt(key_des_ver, PSA_ALG_CTR, tv_cipher.Ctx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(key_des_ver, PSA_ALG_XTS, tv_cipher.Ctx_p, tv_cipher.PtxLen,
                                output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_cipher_decrypt()=", Status);
#endif

    Status = psa_cipher_encrypt_setup(&SymContext, key, PSA_ALG_SHA_256);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt_setup()=", Status);

#ifdef PSATEST_SYM_ALGO_3DES
    Status = psa_cipher_encrypt_setup(&SymContext, key_des, PSA_ALG_CTR);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_cipher_encrypt_setup()=", Status);
#endif

    Status = psa_cipher_encrypt_setup(&SymContext, key, PSA_ALG_XTS);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt_setup()=", Status);

    Status = psa_cipher_decrypt_setup(&SymContext, key_ver, PSA_ALG_SHA_256);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt_setup()=", Status);

    Status = psa_cipher_decrypt_setup(&SymContext, key_des_ver, PSA_ALG_CTR);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_cipher_decrypt_setup()=", Status);

    Status = psa_cipher_decrypt_setup(&SymContext, key_ver, PSA_ALG_XTS);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt_setup()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
    test_vectors_aes_basic_release(tv_p);
#ifdef PSATEST_SYM_ALGO_3DES
    (void)psa_destroy_key(key_des);
    (void)psa_destroy_key(key_des_ver);
    test_vectors_des_release(tv_p_DES);
#endif
}
END_TEST

START_TEST(test_cipher_buffer_too_small)
{
    psa_cipher_operation_t SymContext;
    psa_algorithm_t Mode = PSA_ALG_ECB_NO_PADDING;
    TestVector_AES_BASIC_t tv_p;
    SymcipherCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    uint8_t iv_buff[128];
    uint8_t output[128];
    size_t output_length;
    size_t iv_length;
    psa_status_t Status;

    Status = psa_crypto_init();

    tv_p = test_vectors_aes_basic_get(0);
    setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
    Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);
    Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);

    (void)memset(&SymContext, 0, sizeof(SymContext));

    Status = psa_cipher_encrypt(key, Mode, tv_p->Ptx_p,
                                tv_p->PtxLen, output, 15, &output_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_decrypt(key_ver, Mode, tv_p->Ctx_p,
                                tv_p->PtxLen, output, 15, &output_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_cipher_decrypt()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    Status = psa_cipher_encrypt_setup(&SymContext, key, PSA_ALG_CTR);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()", Status);
    Status = psa_cipher_generate_iv(&SymContext, iv_buff, 15, &iv_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_cipher_decrypt()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_cipher_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    Status = psa_cipher_encrypt_setup(&SymContext, key, PSA_ALG_CTR);
    Status = psa_cipher_update(&SymContext, tv_p->Ptx_p, tv_p->PtxLen, output,
                               15, &output_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_cipher_update()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_cipher_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);

    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    Status = psa_cipher_encrypt_setup(&SymContext, key, PSA_ALG_ECB_NO_PADDING);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()", Status);
    Status = psa_cipher_update(&SymContext, tv_p->Ptx_p, tv_p->PtxLen, output,
                               tv_p->PtxLen, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_update()", Status);

    Status = psa_cipher_finish(&SymContext, output, 15, &output_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_cipher_finish()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_cipher_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
    test_vectors_aes_basic_release(tv_p);
}
END_TEST


START_TEST(test_cipher_arguments)
{
    psa_cipher_operation_t SymContext;
    psa_algorithm_t Mode = PSA_ALG_CTR;
    TestVector_AES_BASIC_t tv_p;
    SymcipherCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    uint8_t iv_buff[128];
    size_t iv_size = 16;
    uint8_t output[128];
    size_t output_length;
    size_t iv_length;
    psa_status_t Status;

    /* Ensure that the following key entries are empty
     * (could still be use due to previous failed tests)
     */
    (void)psa_destroy_key(1);
    (void)psa_destroy_key(2);
    (void)psa_destroy_key(3);
    (void)psa_destroy_key(4);
    (void)psa_destroy_key(5);

    tv_p = test_vectors_aes_basic_get(6);
    setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
    Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);
    Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);

    (void)memset(&SymContext, 0, sizeof(SymContext));

    Status = psa_cipher_encrypt(0, Mode, tv_cipher.Ptx_p, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(5, Mode, tv_cipher.Ptx_p, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(key_ver, Mode, tv_cipher.Ptx_p, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(key, Mode, NULL, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(key, Mode, tv_cipher.Ptx_p, 0, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(key, Mode, tv_cipher.Ptx_p, tv_cipher.PtxLen, NULL,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(key, Mode, tv_cipher.Ptx_p, tv_cipher.PtxLen, output,
                                0, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_encrypt(key, Mode, tv_cipher.Ptx_p, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_decrypt(0, Mode, tv_cipher.Ctx_p, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(5, Mode, tv_cipher.Ctx_p, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(key, Mode, tv_cipher.Ctx_p, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(key_ver, Mode, NULL, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(key_ver, Mode, tv_cipher.Ctx_p, 0, output,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(key_ver, Mode, tv_cipher.Ctx_p, tv_cipher.PtxLen, NULL,
                                tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(key_ver, Mode, tv_cipher.Ctx_p, tv_cipher.PtxLen, output,
                                0, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_decrypt(key_ver, Mode, tv_cipher.Ctx_p, tv_cipher.PtxLen, output,
                                tv_cipher.PtxLen, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt()=", Status);

    Status = psa_cipher_encrypt_setup(NULL, key, Mode);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_encrypt_setup()=", Status);

    Status = psa_cipher_encrypt_setup(&SymContext, 0, Mode);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_cipher_encrypt_setup()=", Status);

    Status = psa_cipher_encrypt_setup(&SymContext, 5, Mode);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_cipher_encrypt_setup()=", Status);

    Status = psa_cipher_encrypt_setup(&SymContext, key_ver, Mode);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_cipher_encrypt_setup()=", Status);

    Status = psa_cipher_decrypt_setup(NULL, key_ver, Mode);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_decrypt_setup()=", Status);

    Status = psa_cipher_decrypt_setup(&SymContext, 0, Mode);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_cipher_decrypt_setup()=", Status);

    Status = psa_cipher_decrypt_setup(&SymContext, 5, Mode);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_cipher_decrypt_setup()=", Status);

    Status = psa_cipher_decrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_cipher_decrypt_setup()=", Status);

    Status = psa_cipher_generate_iv(NULL, iv_buff, iv_size, &iv_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_generate_iv()=", Status);

    Status = psa_cipher_generate_iv(&SymContext, NULL, iv_size, &iv_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_generate_iv()=", Status);

    Status = psa_cipher_generate_iv(&SymContext, iv_buff, 0, &iv_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_generate_iv()=", Status);

    Status = psa_cipher_generate_iv(&SymContext, iv_buff, iv_size, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_generate_iv()=", Status);

    Status = psa_cipher_set_iv(NULL, tv_cipher.Iv_p, 16U);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_set_iv()=", Status);

    Status = psa_cipher_set_iv(&SymContext, NULL, 8U);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_set_iv()=", Status);

    Status = psa_cipher_set_iv(&SymContext, tv_cipher.Iv_p, 0U);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_set_iv()=", Status);

    Status = psa_cipher_set_iv(&SymContext, NULL, 20U);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_set_iv()=", Status);

    Status = psa_cipher_update(NULL, tv_cipher.Ptx_p, tv_cipher.PtxLen, output,
                               tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_update()=", Status);

    Status = psa_cipher_update(&SymContext, NULL, tv_cipher.PtxLen, output,
                               tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_update()=", Status);

    Status = psa_cipher_update(&SymContext, tv_cipher.Ptx_p, 0, output,
                               tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_update()=", Status);

    Status = psa_cipher_update(&SymContext, tv_cipher.Ptx_p, tv_cipher.PtxLen, NULL,
                               tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_update()=", Status);

    Status = psa_cipher_update(&SymContext, tv_cipher.Ptx_p, tv_cipher.PtxLen, output,
                               0, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_update()=", Status);

    Status = psa_cipher_update(&SymContext, tv_cipher.Ptx_p, tv_cipher.PtxLen, output,
                               tv_cipher.PtxLen, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_update()=", Status);

    Status = psa_cipher_finish(NULL, output ,tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_finish()=", Status);

    Status = psa_cipher_finish(&SymContext, NULL ,tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_finish()=", Status);

    Status = psa_cipher_finish(&SymContext, output ,0, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_finish()=", Status);

    Status = psa_cipher_finish(&SymContext, output ,tv_cipher.PtxLen, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_finish()=", Status);

    Status = psa_cipher_abort(NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_cipher_abort()=", Status);

    Status = psa_cipher_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
    test_vectors_aes_basic_release(tv_p);
}
END_TEST

START_TEST(test_cipher_invalid_padding)
{
    psa_cipher_operation_t SymContext;
    psa_algorithm_t Mode = PSA_ALG_ECB_NO_PADDING;
    TestVector_AES_BASIC_t tv_p;
    SymcipherCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    uint8_t output[128];
    size_t output_length;
    psa_status_t Status;

    Status = psa_crypto_init();

    tv_p = test_vectors_aes_basic_get(0);
    setupcipherTVctx(&tv_cipher, tv_p->Ptx_p, tv_p->PtxLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Ctx_p, tv_p->Iv_p);
    Status = setupcipherkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);
    Status = setupcipherkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, 0U, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);

    Status = psa_cipher_encrypt(key, Mode, tv_p->Ptx_p,
                                tv_p->PtxLen - 1, output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_PADDING, "psa_cipher_encrypt()=", Status);

    Status = psa_cipher_decrypt(key_ver, Mode, tv_p->Ctx_p,
                                tv_p->PtxLen - 1, output, tv_cipher.PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_PADDING, "psa_cipher_decrypt()=", Status);

    memset(&SymContext, 0, sizeof(SymContext));
    SymContext.cipher_state = PSA_CIPHER_STATE_INIT;
    Status = psa_cipher_encrypt_setup(&SymContext, key, PSA_ALG_ECB_NO_PADDING);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_encrypt_setup()", Status);
    Status = psa_cipher_update(&SymContext, tv_p->Ptx_p, tv_p->PtxLen, output,
                               tv_p->PtxLen, &output_length);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_update()", Status);

    SymContext.leftover_nbytes = 15;
    Status = psa_cipher_finish(&SymContext, output, tv_p->PtxLen, &output_length);
    fail_if(Status != PSA_ERROR_INVALID_PADDING, "psa_cipher_finish()=", Status);

    Status = psa_cipher_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_cipher_abort()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
    test_vectors_aes_basic_release(tv_p);
}
END_TEST

#undef PSA_CIPHER_STATE_INIT
#undef PSA_CIPHER_STATE_SETUP
#undef PSA_CIPHER_STATE_UPDATE
#undef PSA_CIPHER_STATE_IV

int
suite_add_test_cipher(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SymCrypto_cipher_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes_multipart_enc, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes_multipart_dec, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_xts_aes) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_padding) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes_random, 2) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_gen_iv) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_mul_padding) != 0) goto FuncErrorReturn;

#ifdef PSATEST_SYM_ALGO_ARIA
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aria) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aria_multipart_enc) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aria_multipart_dec) != 0) goto FuncErrorReturn;
#endif

#ifdef PSATEST_SYM_ALGO_3DES
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_des) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_des_multipart_enc) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_des_multipart_dec) != 0) goto FuncErrorReturn;
#endif

        if (sfzutf_test_add(TestCase_p, test_cipher_state) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_cipher_invalid_algorithm) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_cipher_buffer_too_small) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_cipher_arguments) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_cipher_invalid_padding) != 0) goto FuncErrorReturn;
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_cipher.c */
