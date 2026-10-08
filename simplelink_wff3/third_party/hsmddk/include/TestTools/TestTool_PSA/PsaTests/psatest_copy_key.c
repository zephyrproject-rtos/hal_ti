/* psatest_copy_key.c
 *
 * Description: tests for key copy function.
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
 * test_CopyKey_sym
 */
START_TEST(test_CopyKey_Sym)
{
    uint32_t ndx_src;
    uint32_t ndx_trgt;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx_src = 0U; ndx_src < 5; ndx_src++)
    {
        psa_algorithm_t Mode;
        TestVector_AES_BASIC_t tv_p;
        psa_key_id_t key_src;
        psa_key_id_t key_src_ver;
        psa_key_lifetime_t lifetime_src;
        psa_key_id_t uid_src;
        psa_key_id_t uid_src_ver;
        psa_key_attributes_t attributes_src;

        tv_p = test_vectors_aes_basic_get(0);
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

        uid_src = 0U;
        uid_src_ver = 0U;
        if (ndx_src == 1)
        {
            /* PSA Key Store - Persistence:Plaintext format */
            lifetime_src = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                           PSA_KEY_PERSISTENCE_DEFAULT;
            uid_src = 1U;
            uid_src_ver = 2U;
        }
        else if (ndx_src == 2)
        {
            /* HSM Asset Store */
            lifetime_src = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                           PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
        }
        else if (ndx_src == 3)
        {
            /* PSA Key Store - Volatile:Wrapped format */
            lifetime_src = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                           PSA_KEY_PERSISTENCE_VOLATILE;
        }
        else if (ndx_src == 4)
        {
            /* PSA Key Store - Persistence:Wrapped format */
            lifetime_src = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                           PSA_KEY_PERSISTENCE_DEFAULT;
            uid_src = 1U;
            uid_src_ver = 2U;
        }
        else
        {
            /* Default/ndx_src == 0 */
            /* PSA Key Store - Volatile:Plaintext format */
            lifetime_src = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                           PSA_KEY_PERSISTENCE_VOLATILE;
        }

        //LOG_CRIT("=> ndx_src=%d setup\n", ndx_src);

        setkeyattributes(&attributes_src, PSA_KEY_TYPE_AES, Mode,
                         (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_COPY),
                         (tv_p->KeyLen * 8U), lifetime_src, uid_src);
        Status = psa_import_key(&attributes_src, tv_p->Key_p, tv_p->KeyLen,
                                &key_src);
        fail_if(PSA_SUCCESS != Status, "psa_import_key ENCRYPT()", Status);

        setkeyattributes(&attributes_src, PSA_KEY_TYPE_AES, Mode,
                         (PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_COPY),
                         (tv_p->KeyLen * 8U), lifetime_src, uid_src_ver);
        Status = psa_import_key(&attributes_src, tv_p->Key_p, tv_p->KeyLen,
                                &key_src_ver);
        fail_if(PSA_SUCCESS != Status, "psa_import_key DECRYPT()", Status);

        for (ndx_trgt = 0U; ndx_trgt < 5; ndx_trgt++)
        {
            psa_key_id_t key_trgt;
            psa_key_id_t key_trgt_ver;
            psa_key_lifetime_t lifetime_trgt;
            psa_key_id_t uid_trgt;
            psa_key_id_t uid_trgt_ver;
            psa_key_attributes_t attributes_trgt;
            size_t IVSize;
            size_t output_length;
            uint8_t * ciphertext;
            uint8_t * plaintext;

            uid_trgt = 0U;
            uid_trgt_ver = 0U;
            if (ndx_trgt == 1)
            {
                /* PSA Key Store - Persistence:Plaintext format */
                lifetime_trgt = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                                PSA_KEY_PERSISTENCE_DEFAULT;
                uid_trgt = 3U;
                uid_trgt_ver = 4U;
            }
            else if (ndx_trgt == 2)
            {
                /* HSM Asset Store */
                lifetime_trgt = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
            }
            else if (ndx_trgt == 3)
            {
                /* PSA Key Store - Volatile:Wrapped format */
                lifetime_trgt = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                PSA_KEY_PERSISTENCE_VOLATILE;
            }
            else if (ndx_trgt == 4)
            {
                /* PSA Key Store - Persistence:Wrapped format */
                lifetime_trgt = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                PSA_KEY_PERSISTENCE_DEFAULT;
                uid_trgt = 3U;
                uid_trgt_ver = 4U;
            }
            else
            {
                /* Default/ndx_trgt == 0 */
                /* PSA Key Store - Volatile:Plaintext format */
                lifetime_trgt = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                                PSA_KEY_PERSISTENCE_VOLATILE;
            }

            //LOG_CRIT("=> ndx_src=%d, ndx_trgt=%d\n", ndx_src, ndx_trgt);

            setkeyattributes(&attributes_trgt, PSA_KEY_TYPE_AES, Mode,
                             PSA_KEY_USAGE_ENCRYPT, (tv_p->KeyLen * 8U),
                             lifetime_trgt, uid_trgt);
            Status = psa_copy_key(key_src, &attributes_trgt, &key_trgt);
            if (PSA_ERROR_HARDWARE_FAILURE == Status)
            {
                (void)psa_destroy_key(key_src);
                (void)psa_destroy_key(key_src_ver);
                unsupported_if(PSA_ERROR_HARDWARE_FAILURE == Status, "No Root key");
            }
            if ((ndx_src == 2) ||
                ((ndx_src == 3 || ndx_src == 4) && (ndx_trgt == 0 || ndx_trgt == 1)))
            {
                /* Cannot copy a key:
                 * - from PSA Key Store in Wrapped format to Plaintext format
                 * - from HSM Asset store to the PSA Key Store in general
                 */
                fail_if(PSA_ERROR_NOT_PERMITTED != Status, "psa_copy_key ENCRYPT()", Status);
            }
            else
            {
                fail_if(PSA_SUCCESS != Status, "psa_copy_key ENCRYPT()", Status);
            }

            setkeyattributes(&attributes_trgt, PSA_KEY_TYPE_AES, Mode,
                             PSA_KEY_USAGE_DECRYPT, (tv_p->KeyLen * 8U),
                             lifetime_trgt, uid_trgt_ver);
            Status = psa_copy_key(key_src_ver, &attributes_trgt, &key_trgt_ver);
            if ((ndx_src == 2) ||
                ((ndx_src == 3 || ndx_src == 4) && (ndx_trgt == 0 || ndx_trgt == 1)))
            {
                /* Can not copy a key:
                 * - from PSA Key Store in Wrapped format to Plaintext format
                 * - from HSM Asset store to PSA Key Store in general
                 */
                fail_if(PSA_ERROR_NOT_PERMITTED != Status, "psa_copy_key DECRYPT()", Status);
                continue;
            }
            else
            {
                fail_if(PSA_SUCCESS != Status, "psa_copy_key DECRYPT()", Status);
            }

            IVSize = PSA_CIPHER_IV_LENGTH(PSA_KEY_TYPE_AES, Mode);
            ciphertext = (uint8_t *)SFZUTF_MALLOC(tv_p->PtxLen + IVSize);
            fail_if(ciphertext == NULL, "Allocation ", (int)(tv_p->PtxLen + IVSize));
            (void)memset(ciphertext, 0, (tv_p->PtxLen + IVSize));

            plaintext = (uint8_t *)SFZUTF_MALLOC(tv_p->PtxLen);
            fail_if(plaintext == NULL, "Allocation ", (int)tv_p->PtxLen);
            (void)memset(plaintext, 0, tv_p->PtxLen);

            output_length = 0U;
            Status = psa_cipher_encrypt(key_trgt, Mode, tv_p->Ptx_p, tv_p->PtxLen,
                                        ciphertext, (tv_p->PtxLen + IVSize), &output_length);
            fail_if(PSA_SUCCESS != Status, "psa_cipher_encrypt ()", Status);
            fail_if(tv_p->PtxLen != (output_length - IVSize), "Length mismatch ENCRYPT", (int)output_length);
            if(memcmp(ciphertext, tv_p->Ctx_p, tv_p->PtxLen) != 0)
            {
                Failed++;
                LOG_CRIT("Wrong ciphertext\n");
            }
            else
            {
                Success++;
            }

            output_length = 0U;
            Status = psa_cipher_decrypt(key_trgt_ver, Mode, ciphertext, (tv_p->PtxLen + IVSize),
                                        plaintext, tv_p->PtxLen, &output_length);
            fail_if(PSA_SUCCESS != Status, "psa_cipher_decrypt ()", Status);
            fail_if(tv_p->PtxLen != output_length, "Length mismatch DECRYPT", (int)output_length);
            if(memcmp(plaintext, tv_p->Ptx_p, tv_p->PtxLen) != 0)
            {
                Failed++;
                LOG_CRIT("Wrong plaintext\n");
            }
            else
            {
                Success++;
            }

            SFZUTF_FREE(plaintext);
            SFZUTF_FREE(ciphertext);

            (void)psa_destroy_key(key_trgt);
            (void)psa_destroy_key(key_trgt_ver);
        }

        (void)psa_destroy_key(key_src);
        (void)psa_destroy_key(key_src_ver);

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
 * test_NegCopyKey
 */
START_TEST(test_NegCopyKey)
{
    TestVector_AES_BASIC_t tv_p;
    psa_status_t Status;
    psa_key_id_t Key1;
    psa_key_id_t Key2;
    psa_key_attributes_t attributes;

    tv_p = test_vectors_aes_basic_get(0);
    fail_if(NULL == tv_p, "No test vector", 0);

    /* Perform negative tests for copy key */
    setkeyattributes(&attributes, PSA_KEY_TYPE_AES, PSA_ALG_CBC_NO_PADDING,
                     (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_COPY),
                     (tv_p->KeyLen * 8U),
                     ((PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                      PSA_KEY_PERSISTENCE_VOLATILE), 0U);
    Status = psa_import_key(&attributes, tv_p->Key_p, tv_p->KeyLen, &Key1);
    fail_if(PSA_SUCCESS != Status, "psa_import_key()", Status);

    Status = psa_copy_key(Key1, NULL, &Key2);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_copy_key(1)", Status);

    /* Target key is persistent with Attributes.id is NULL */
    psa_set_key_lifetime(&attributes, (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) |
                                       PSA_KEY_PERSISTENCE_DEFAULT);
    Status = psa_copy_key(Key1, &attributes, &Key2);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_copy_key(2)", Status);

    /* Target key is persistent with Attributes.id is NULL */
    psa_set_key_lifetime(&attributes, (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) |
                                       PSA_KEY_PERSISTENCE_DEFAULT);
    Status = psa_copy_key(Key1, &attributes, &Key2);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_copy_key(3)", Status);

    /* Invalid storage location */
    psa_set_key_lifetime(&attributes, (3U << 8) | PSA_KEY_PERSISTENCE_VOLATILE);
    Status = psa_copy_key(Key1, &attributes, &Key2);
    fail_if(PSA_ERROR_NOT_PERMITTED != Status, "psa_copy_key(4)", Status);

    /* Destroy the key */
    Status = psa_destroy_key(Key1);
    fail_if(PSA_SUCCESS != Status, "psa_destroy_key()", Status);
}
END_TEST

int
suite_add_test_copy_key(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "CopyKey_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_CopyKey_Sym) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_NegCopyKey) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_copy_key.c */
