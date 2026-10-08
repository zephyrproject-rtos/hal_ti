/* psatest_mac.c
 *
 * Description: tests for HMAC and MAC
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
#include "testvectors_aes_cmac.h"
#include "testvectors_aes_cbcmac.h"
#include "testvectors_aria_cmac.h"
#include "testvectors_aria_cbcmac.h"
#include "testvectors_hmac.h"


typedef struct
{
    const uint8_t * Msg_p;
    uint32_t MsgLen;
    const uint8_t * Mac_p;
    uint32_t MacLen;
    const uint8_t * key_p;
    uint32_t KeyLen;
} SymmacCryptTV_t;


static void
setupmacTVctx(SymmacCryptTV_t *TVctx,
              const uint8_t *Msg_p,
              uint32_t MsgLen,
              const uint8_t *key_p,
              uint32_t key_len,
              const uint8_t *Mac_p,
              uint32_t Mac_len)
{
    TVctx->Msg_p = Msg_p;
    TVctx->MsgLen = MsgLen;
    TVctx->Mac_p = Mac_p;
    TVctx->MacLen = Mac_len;
    TVctx->key_p = key_p;
    TVctx->KeyLen = key_len;
}


/*----------------------------------------------------------------------------
 * setupmackey
 *
 * Helper function to setup key.
 */
static psa_status_t
setupmackey(psa_key_id_t * key,
            psa_algorithm_t alg,
            psa_key_usage_t usage_flag,
            psa_key_type_t key_type,
            psa_key_lifetime_t lifetime,
            psa_key_id_t uid,
            SymmacCryptTV_t * Vector_p)
{
    psa_status_t Status = PSA_SUCCESS;
    psa_key_attributes_t attributes = { 0 };
    uint8_t hashed_key[(1152U / 8U)];
    size_t key_size = 0U;
    bool hash_needed = false;

    if (0U == Vector_p->KeyLen)
    {
        Status = PSA_ERROR_INSUFFICIENT_DATA;
    }
    else
    {
        if (PSA_ALG_IS_HMAC(alg))
        {
            memset(hashed_key, 0, 144);
            switch (PSA_ALG_HMAC_GET_HASH(alg))
            {
            case PSA_ALG_SHA_1:
            case PSA_ALG_SHA_224:
            case PSA_ALG_SHA_256:
                if (Vector_p->KeyLen > (512U / 8U))
                {
                    hash_needed = true;
                }
                break;
            case PSA_ALG_SHA_384:
            case PSA_ALG_SHA_512:
                if (Vector_p->KeyLen > (1024U / 8U))
                {
                    hash_needed = true;
                }
                break;
            case PSA_ALG_SHA3_224:
                if (Vector_p->KeyLen > (1152U / 8U))
                {
                    hash_needed = true;
                }
                break;
            case PSA_ALG_SHA3_256:
                if (Vector_p->KeyLen > (1088U / 8U))
                {
                    hash_needed = true;
                }
                break;
            case PSA_ALG_SHA3_384:
                if (Vector_p->KeyLen > (832U / 8U))
                {
                    hash_needed = true;
                }
                break;
            case PSA_ALG_SHA3_512:
                if (Vector_p->KeyLen > (576U / 8U))
                {
                    hash_needed = true;
                }
                break;
            default:
                Status = PSA_ERROR_INSUFFICIENT_DATA;
                break;
            }
        }
        else
        {
            /* Assume CMAC or CBC-MAC */
        }
        if (PSA_SUCCESS == Status)
        {
            if (hash_needed == true)
            {
                Status = psa_hash_compute(PSA_ALG_HMAC_GET_HASH(alg),
                                          Vector_p->key_p, Vector_p->KeyLen,
                                          hashed_key, 64, &key_size);
            }
            else
            {
                memcpy(hashed_key, Vector_p->key_p, Vector_p->KeyLen);
                key_size = Vector_p->KeyLen;
            }
        }
        else
        {
        }
        if (PSA_SUCCESS == Status)
        {
            psa_set_key_type(&attributes, key_type);
            psa_set_key_algorithm(&attributes, alg);
            psa_set_key_usage_flags(&attributes, usage_flag);
            psa_set_key_lifetime(&attributes, lifetime);
            psa_set_key_bits(&attributes, key_size * 8);
            if (uid != 0U)
            {
                psa_set_key_id(&attributes, uid);
            }
            Status = psa_import_key(&attributes, hashed_key, key_size, key);
        }
        else
        {
        }
    }

    return Status;
}

/*----------------------------------------------------------------------------
 * do_mac_test
 *
 * Helper function that runs a single mac test.
 */
static int
do_mac_test(uint32_t VectorIndex,
            psa_key_id_t key,
            psa_algorithm_t alg,
            size_t mac_size,
            bool fverify,
            SymmacCryptTV_t * Vector_p)
{
    psa_status_t Status;
    uint8_t mac[512] = {0};
    size_t mac_length = 0U;

    if (fverify)
    {
        Status = psa_mac_verify(key, alg, Vector_p->Msg_p,
                                Vector_p->MsgLen, Vector_p->Mac_p, Vector_p->MacLen);
        fail_if(PSA_SUCCESS != Status, "single mac operation verify", Status);
    }
    else
    {
        Status = psa_mac_compute(key, alg, Vector_p->Msg_p,
                                Vector_p->MsgLen, mac, mac_size, &mac_length);
        fail_if(PSA_SUCCESS != Status, "single mac generate operation", Status);
        fail_if(Vector_p->MacLen != mac_length, "Length mismatch ", (int)mac_length);
        fail_if(memcmp(mac, Vector_p->Mac_p, Vector_p->MacLen) != 0, "", VectorIndex);
    }
    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * do_mac_update
 *
 * Helper function that runs update mac test.
 */
static int
do_mac_update(psa_mac_operation_t *SymContext_p,
              SymmacCryptTV_t * Vector_p)
{
    psa_status_t Status;

    Status = psa_mac_update(SymContext_p, Vector_p->Msg_p, Vector_p->MsgLen);
    fail_if(PSA_SUCCESS != Status, "mac update operation", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * do_mac_final
 *
 * Helper function that runs final mac test.
 */
static int
do_mac_final(uint32_t VectorIndex,
               psa_mac_operation_t *SymContext_p,
               bool fverify,
               SymmacCryptTV_t * Vector_p)
{
    psa_status_t Status;
    uint8_t mac[512] = {0};
    size_t mac_length = 0U;

    if (fverify)
    {
        Status = psa_mac_verify_finish(SymContext_p, Vector_p->Mac_p, Vector_p->MacLen);
        fail_if(PSA_SUCCESS != Status, "final mac operation verify", Status);
    }
    else
    {
        Status = psa_mac_sign_finish(SymContext_p, mac, sizeof(mac), &mac_length);
        fail_if(PSA_SUCCESS != Status, "final mac operation", Status);
        fail_if(Vector_p->MacLen != mac_length, "Length mismatch ", (int)mac_length);
        fail_if(memcmp(mac, Vector_p->Mac_p, Vector_p->MacLen) != 0, "", VectorIndex);
    }
    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_hmac
 *
 * Test with HMAC test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_hmac)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        psa_status_t Status;
        psa_algorithm_t HashAlg;
        psa_algorithm_t Algorithm;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        size_t mac_size;
        bool fverify = false;
        TestVector_HMAC_t tv_p;
        SymmacCryptTV_t tv_hmac;
        psa_key_lifetime_t lifetime;
        psa_key_id_t uid;
        psa_key_id_t uid_ver;

        tv_p = test_vectors_hmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            HashAlg = PSA_ALG_SHA_1;
            mac_size = (160U/8U);
            break;
        case TESTVECTORS_HASH_SHA224:
            HashAlg = PSA_ALG_SHA_224;
            mac_size = (224U/8U);
            break;
        case TESTVECTORS_HASH_SHA256:
            HashAlg = PSA_ALG_SHA_256;
            mac_size = (256U/8U);
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            HashAlg = PSA_ALG_SHA_384;
            mac_size = (384U/8U);
            break;
        case TESTVECTORS_HASH_SHA512:
            HashAlg = PSA_ALG_SHA_512;
            mac_size = (512U/8U);
            break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            HashAlg = PSA_ALG_SHA3_224;
            mac_size = (224U/8U);
            break;
        case TESTVECTORS_HASH_SHA3_256:
            HashAlg = PSA_ALG_SHA3_256;
            mac_size = (256U/8U);
            break;
        case TESTVECTORS_HASH_SHA3_384:
            HashAlg = PSA_ALG_SHA3_384;
            mac_size = (384U/8U);
            break;
        case TESTVECTORS_HASH_SHA3_512:
            HashAlg = PSA_ALG_SHA3_512;
            mac_size = (512U/8U);
            break;
#endif
        default:
            HashAlg = PSA_ALG_NONE;
            mac_size = 0U;
            break;
        }
        if ((mac_size == 0) ||
            (tv_p->KeyLen < (112U/8U)) ||
            (tv_p->KeyLen < (mac_size/2U)) ||
            (mac_size != tv_p->MacLen))
        {
            test_vectors_hmac_release(tv_p);
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
        Algorithm = PSA_ALG_HMAC(HashAlg);

        setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
        Status = setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_HMAC, lifetime, uid, &tv_hmac);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
        fail_if(PSA_SUCCESS != Status, "setupmackey sign()", Status);
        if (do_mac_test(ndx, key, Algorithm, mac_size, fverify, &tv_hmac) != END_TEST_SUCCES)
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

        Status = setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_HMAC, lifetime, uid_ver, &tv_hmac);
        fail_if(PSA_SUCCESS != Status, "setupmackey ver()", Status);
        fverify = true;
        if (do_mac_test(ndx, key_ver, Algorithm, mac_size, fverify, &tv_hmac) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            (void)psa_destroy_key(key_ver);
            Failed++;
        }
        else
        {
            Status = psa_destroy_key(key_ver);
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

        test_vectors_hmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_hmac_multipart)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = false;
        psa_algorithm_t Algorithm;
        psa_algorithm_t HashAlg;
        psa_status_t Status;
        SymmacCryptTV_t tv_hmac;
        size_t mac_size;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_hmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            HashAlg = PSA_ALG_SHA_1;
            mac_size = (160/8);
            break;
        case TESTVECTORS_HASH_SHA224:
            HashAlg = PSA_ALG_SHA_224;
            mac_size = (224/8);
            break;
        case TESTVECTORS_HASH_SHA256:
            HashAlg = PSA_ALG_SHA_256;
            mac_size = (256/8);
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            HashAlg = PSA_ALG_SHA_384;
            mac_size = (384/8);
            break;
        case TESTVECTORS_HASH_SHA512:
            HashAlg = PSA_ALG_SHA_512;
            mac_size = (512/8);
            break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            HashAlg = PSA_ALG_SHA3_224;
            mac_size = (224/8);
            break;
        case TESTVECTORS_HASH_SHA3_256:
            HashAlg = PSA_ALG_SHA3_256;
            mac_size = (256/8);
            break;
        case TESTVECTORS_HASH_SHA3_384:
            HashAlg = PSA_ALG_SHA3_384;
            mac_size = (384/8);
            break;
        case TESTVECTORS_HASH_SHA3_512:
            HashAlg = PSA_ALG_SHA3_512;
            mac_size = (512/8);
            break;
#endif
        default:
            HashAlg = PSA_ALG_NONE;
            mac_size = 0U;
            break;
        }
        if ((mac_size == 0) ||
            (tv_p->KeyLen < (112U/8U)) ||
            (tv_p->KeyLen < (mac_size/2U)) ||
            (mac_size != tv_p->MacLen))
        {
            test_vectors_hmac_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_hmac, 0, sizeof(tv_hmac));
        Algorithm = PSA_ALG_HMAC(HashAlg);
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_HMAC, lifetime, 0U, &tv_hmac))
        {
            Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup", Status);

            if (do_mac_update(&SymContext, &tv_hmac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_hmac) != END_TEST_SUCCES)
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

        test_vectors_hmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_hmac_multipart_verify)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = true;
        psa_algorithm_t HashAlg;
        psa_algorithm_t Algorithm;
        psa_status_t Status;
        SymmacCryptTV_t tv_hmac;
        size_t mac_size;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_hmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            HashAlg = PSA_ALG_SHA_1;
            mac_size = (160/8);
            break;
        case TESTVECTORS_HASH_SHA224:
            HashAlg = PSA_ALG_SHA_224;
            mac_size = (224/8);
            break;
        case TESTVECTORS_HASH_SHA256:
            HashAlg = PSA_ALG_SHA_256;
            mac_size = (256/8);
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            HashAlg = PSA_ALG_SHA_384;
            mac_size = (384/8);
            break;
        case TESTVECTORS_HASH_SHA512:
            HashAlg = PSA_ALG_SHA_512;
            mac_size = (512/8);
            break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            HashAlg = PSA_ALG_SHA3_224;
            mac_size = (224/8);
            break;
        case TESTVECTORS_HASH_SHA3_256:
            HashAlg = PSA_ALG_SHA3_256;
            mac_size = (256/8);
            break;
        case TESTVECTORS_HASH_SHA3_384:
            HashAlg = PSA_ALG_SHA3_384;
            mac_size = (384/8);
            break;
        case TESTVECTORS_HASH_SHA3_512:
            HashAlg = PSA_ALG_SHA3_512;
            mac_size = (512/8);
            break;
#endif
        default:
            HashAlg = PSA_ALG_NONE;
            mac_size = 0U;
            break;
        }
        if ((mac_size == 0) ||
            (tv_p->KeyLen < (112U/8U)) ||
            (tv_p->KeyLen < (mac_size/2U)) ||
            (mac_size != tv_p->MacLen))
        {
            test_vectors_hmac_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_hmac, 0, sizeof(tv_hmac));
        Algorithm = PSA_ALG_HMAC(HashAlg);
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_HMAC, lifetime, 0U, &tv_hmac))
        {
            Status = psa_mac_verify_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_verify_setup", Status);

            if (do_mac_update(&SymContext,&tv_hmac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_hmac) != END_TEST_SUCCES)
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

        test_vectors_hmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_hmac_multipart_key_in_use)
{
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HMAC_t tv_p;
        psa_mac_operation_t SymContext_sign1;
        psa_mac_operation_t SymContext_sign2;
        psa_mac_operation_t SymContext_ver1;
        psa_mac_operation_t SymContext_ver2;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_algorithm_t Algorithm;
        psa_algorithm_t HashAlg;
        psa_status_t Status;
        SymmacCryptTV_t tv_hmac;
        size_t mac_size;
        psa_key_lifetime_t lifetime;
        uint8_t mac[512] = {0};
        size_t mac_length = 0U;

        tv_p = test_vectors_hmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            HashAlg = PSA_ALG_SHA_1;
            mac_size = (160/8);
            break;
        case TESTVECTORS_HASH_SHA224:
            HashAlg = PSA_ALG_SHA_224;
            mac_size = (224/8);
            break;
        case TESTVECTORS_HASH_SHA256:
            HashAlg = PSA_ALG_SHA_256;
            mac_size = (256/8);
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            HashAlg = PSA_ALG_SHA_384;
            mac_size = (384/8);
            break;
        case TESTVECTORS_HASH_SHA512:
            HashAlg = PSA_ALG_SHA_512;
            mac_size = (512/8);
            break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            HashAlg = PSA_ALG_SHA3_224;
            mac_size = (224/8);
            break;
        case TESTVECTORS_HASH_SHA3_256:
            HashAlg = PSA_ALG_SHA3_256;
            mac_size = (256/8);
            break;
        case TESTVECTORS_HASH_SHA3_384:
            HashAlg = PSA_ALG_SHA3_384;
            mac_size = (384/8);
            break;
        case TESTVECTORS_HASH_SHA3_512:
            HashAlg = PSA_ALG_SHA3_512;
            mac_size = (512/8);
            break;
#endif
        default:
            HashAlg = PSA_ALG_NONE;
            mac_size = 0U;
            break;
        }
        if ((mac_size == 0) ||
            (tv_p->KeyLen < (112U/8U)) ||
            (tv_p->KeyLen < (mac_size/2U)) ||
            (mac_size != tv_p->MacLen))
        {
            test_vectors_hmac_release(tv_p);
            continue;
        }

        memset(&SymContext_sign1, 0, sizeof(SymContext_sign1));
        memset(&SymContext_sign2, 0, sizeof(SymContext_sign2));
        memset(&SymContext_ver1, 0, sizeof(SymContext_ver1));
        memset(&SymContext_ver2, 0, sizeof(SymContext_ver2));
        memset(&tv_hmac, 0, sizeof(tv_hmac));
        Algorithm = PSA_ALG_HMAC(HashAlg);
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
        Status = setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_HMAC, lifetime, 0U, &tv_hmac);
        fail_if(PSA_SUCCESS != Status, "setupmackey sign", Status);

        Status = setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_HMAC, lifetime, 0U, &tv_hmac);
        fail_if(PSA_SUCCESS != Status, "setupmackey verify", Status);

        Status = psa_mac_sign_setup(&SymContext_sign1, key, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup 1", Status);

        Status = psa_destroy_key(key);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_sign_setup(&SymContext_sign2, key, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup 2", Status);

        Status = psa_destroy_key(key);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_update(&SymContext_sign1, tv_hmac.Msg_p, tv_hmac.MsgLen);
        fail_if(PSA_SUCCESS != Status, "mac update operation", Status);

        Status = psa_destroy_key(key);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_update(&SymContext_sign2, tv_hmac.Msg_p, tv_hmac.MsgLen);
        fail_if(PSA_SUCCESS != Status, "mac update operation", Status);

        Status = psa_mac_sign_finish(&SymContext_sign1, mac, sizeof(mac), &mac_length);
        fail_if(PSA_SUCCESS != Status, "final mac operation", Status);
        fail_if(tv_hmac.MacLen != mac_length, "Length mismatch ", (int)mac_length);
        fail_if(memcmp(mac, tv_hmac.Mac_p, tv_hmac.MacLen) != 0, "", ndx);

        Status = psa_destroy_key(key);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_abort(&SymContext_sign2);
        fail_if(Status != PSA_SUCCESS, "psa_mac_abort", Status);

        Status = psa_destroy_key(key);
        fail_if(Status != PSA_SUCCESS, "psa_destroy_key", Status);

        Status = psa_mac_abort(&SymContext_sign1);
        fail_if(Status != PSA_SUCCESS, "psa_mac_abort", Status);

        Status = psa_mac_verify_setup(&SymContext_ver1, key_ver, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_mac_verify_setup 1", Status);

        Status = psa_destroy_key(key_ver);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_verify_setup(&SymContext_ver2, key_ver, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_mac_verify_setup 2", Status);

        Status = psa_destroy_key(key_ver);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_update(&SymContext_ver1, tv_hmac.Msg_p, tv_hmac.MsgLen);
        fail_if(PSA_SUCCESS != Status, "mac update operation", Status);

        Status = psa_destroy_key(key_ver);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_update(&SymContext_ver2, tv_hmac.Msg_p, tv_hmac.MsgLen);
        fail_if(PSA_SUCCESS != Status, "mac update operation", Status);

        Status = psa_destroy_key(key_ver);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_verify_finish(&SymContext_ver1, tv_hmac.Mac_p, tv_hmac.MacLen);
        fail_if(PSA_SUCCESS != Status, "final mac operation", Status);

        Status = psa_destroy_key(key_ver);
        fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_destroy_key", Status);

        Status = psa_mac_verify_finish(&SymContext_ver2, tv_hmac.Mac_p, tv_hmac.MacLen);
        fail_if(PSA_SUCCESS != Status, "final mac operation", Status);

        Status = psa_destroy_key(key_ver);
        fail_if(Status != PSA_SUCCESS, "psa_destroy_key", Status);

        Status = psa_mac_abort(&SymContext_ver1);
        fail_if(Status != PSA_SUCCESS, "psa_mac_abort", Status);

        Status = psa_mac_abort(&SymContext_ver2);
        fail_if(Status != PSA_SUCCESS, "psa_mac_abort", Status);

        test_vectors_hmac_release(tv_p);
        break;
    }
}
END_TEST

START_TEST(test_hmac_multipart_chunks)
{
    int Success = 0;
    int Failed = 0;
    TestVector_HMAC_t tv_p;
    psa_mac_operation_t SymContext;
    psa_key_id_t key;
    psa_algorithm_t HashAlg;
    psa_algorithm_t Algorithm;
    psa_status_t Status;
    SymmacCryptTV_t tv_hmac;
    size_t mac_size = 0;
    psa_key_lifetime_t lifetime;
    const uint8_t *input;
    uint8_t mac[512] = {0};
    size_t mac_length = 0U;

    tv_p = test_vectors_hmac_get(49);
    fail_if(tv_p == NULL, "No vector found", 49);

    switch (tv_p->Algorithm)
    {
    case TESTVECTORS_HASH_SHA160:
        HashAlg = PSA_ALG_SHA_1;
        mac_size = (160/8);
        break;
    case TESTVECTORS_HASH_SHA224:
        HashAlg = PSA_ALG_SHA_224;
        mac_size = (224/8);
        break;
    case TESTVECTORS_HASH_SHA256:
        HashAlg = PSA_ALG_SHA_256;
        mac_size = (256/8);
        break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
    case TESTVECTORS_HASH_SHA384:
        HashAlg = PSA_ALG_SHA_384;
        mac_size = (384/8);
        break;
    case TESTVECTORS_HASH_SHA512:
        HashAlg = PSA_ALG_SHA_512;
        mac_size = (512/8);
        break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
    case TESTVECTORS_HASH_SHA3_224:
        HashAlg = PSA_ALG_SHA3_224;
        mac_size = (224/8);
        break;
    case TESTVECTORS_HASH_SHA3_256:
        HashAlg = PSA_ALG_SHA3_256;
        mac_size = (256/8);
        break;
    case TESTVECTORS_HASH_SHA3_384:
        HashAlg = PSA_ALG_SHA3_384;
        mac_size = (384/8);
        break;
    case TESTVECTORS_HASH_SHA3_512:
        HashAlg = PSA_ALG_SHA3_512;
        mac_size = (512/8);
        break;
#endif
    default:
        HashAlg = PSA_ALG_NONE;
        mac_size = 0U;
        break;
    }
    if ((mac_size == 0) ||
        (tv_p->KeyLen < (112U/8U)) ||
        (tv_p->KeyLen < (mac_size/2U)) ||
        (mac_size != tv_p->MacLen))
    {
        test_vectors_hmac_release(tv_p);
        tv_p = NULL;
        fail_if(tv_p == NULL, "No vector found", 49);
    }

    memset(&SymContext, 0, sizeof(SymContext));
    memset(&tv_hmac, 0, sizeof(tv_hmac));
    Algorithm = PSA_ALG_HMAC(HashAlg);
    lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

    setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
    Status = setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_HMAC, lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status, "setupmackey enc()", Status);

    Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
    fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup", Status);

    input = tv_hmac.Msg_p;
    Status = psa_mac_update(&SymContext, input, 145);
    fail_if(PSA_SUCCESS != Status, "mac update operation", Status);

    Status = psa_mac_update(&SymContext, &input[145], 145);
    fail_if(PSA_SUCCESS != Status, "mac update operation", Status);

    Status = psa_mac_update(&SymContext, &input[290], 10);
    fail_if(PSA_SUCCESS != Status, "mac update operation", Status);

    Status = psa_mac_sign_finish(&SymContext, mac, sizeof(mac), &mac_length);
    fail_if(PSA_SUCCESS != Status, "final mac operation", Status);
    fail_if(tv_hmac.MacLen != mac_length, "Length mismatch ", (int)mac_length);
    if (memcmp(mac, tv_hmac.Mac_p, tv_hmac.MacLen) != 0)
    {
        Failed++;
    }
    else
    {
        Success++;
    }

    (void)psa_destroy_key(key);
    test_vectors_hmac_release(tv_p);

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_aes_cmac
 *
 * Test with CMAC test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_aes_cmac)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Algorithm = PSA_ALG_CMAC;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        size_t mac_size = (128/8);
        bool fverify;
        TestVector_AES_CMAC_t tv_p;
        SymmacCryptTV_t tv_mac;
        psa_status_t Status;
        psa_key_lifetime_t lifetime;
        psa_key_id_t uid;
        psa_key_id_t uid_ver;

        tv_p = test_vectors_aes_cmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (tv_p->MsgLen == 0)
        {
            test_vectors_aes_cmac_release(tv_p);
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

        fverify = false;
        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        Status = setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_AES, lifetime, uid, &tv_mac);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
        fail_if(PSA_SUCCESS != Status, "setupmackey sign()", Status);
        if (do_mac_test(ndx, key, Algorithm, mac_size, fverify, &tv_mac) != END_TEST_SUCCES)
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

        Status = setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_AES, lifetime, uid_ver, &tv_mac);
        fail_if(PSA_SUCCESS != Status, "setupmackey ver()", Status);
        fverify = true;
        if (do_mac_test(ndx, key_ver, Algorithm, mac_size, fverify, &tv_mac) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            (void)psa_destroy_key(key_ver);
            Failed++;
        }
        else
        {
            Status = psa_destroy_key(key_ver);
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

        test_vectors_aes_cmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aes_cmac_multipart)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_CMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = false;
        psa_algorithm_t Algorithm = PSA_ALG_CMAC;
        psa_status_t Status;
        SymmacCryptTV_t tv_mac;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aes_cmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (tv_p->MsgLen == 0)
        {
            test_vectors_aes_cmac_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_mac, 0, sizeof(tv_mac));
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_mac))
        {
            Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup", Status);

            if (do_mac_update(&SymContext, &tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_mac) != END_TEST_SUCCES)
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

        test_vectors_aes_cmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aes_cmac_multipart_verify)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_CMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = true;
        psa_algorithm_t Algorithm = PSA_ALG_CMAC;
        psa_status_t Status;
        SymmacCryptTV_t tv_mac;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aes_cmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (tv_p->MsgLen == 0)
        {
            test_vectors_aes_cmac_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_mac, 0, sizeof(tv_mac));
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_mac))
        {
            Status = psa_mac_verify_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_verify_setup", Status);

            if (do_mac_update(&SymContext,&tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_mac) != END_TEST_SUCCES)
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

        test_vectors_aes_cmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aes_cbcmac)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Algorithm = PSA_ALG_CBC_MAC;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        size_t mac_size = (128/8);
        bool fverify = false;
        TestVector_AES_CBCMAC_t tv_p;
        SymmacCryptTV_t tv_mac;
        psa_status_t Status;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aes_cbcmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_mac))
        {
            if (do_mac_test(ndx, key, Algorithm, mac_size, fverify, &tv_mac) != END_TEST_SUCCES)
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
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        if (PSA_SUCCESS == setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_mac))
        {
            fverify = true;
            if (do_mac_test(ndx, key_ver, Algorithm, mac_size, fverify, &tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key_ver);
                Failed++;
            }
            else
            {
                Status = psa_destroy_key(key_ver);
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
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        test_vectors_aes_cbcmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aes_cbcmac_multipart)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_CBCMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = false;
        psa_algorithm_t Algorithm = PSA_ALG_CBC_MAC;
        psa_status_t Status;
        SymmacCryptTV_t tv_mac;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aes_cbcmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_mac, 0, sizeof(tv_mac));
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_mac))
        {
            Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup", Status);

            if (do_mac_update(&SymContext, &tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_mac) != END_TEST_SUCCES)
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

        test_vectors_aes_cbcmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aes_cbcmac_multipart_verify)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_CBCMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = true;
        psa_algorithm_t Algorithm = PSA_ALG_CBC_MAC;
        psa_status_t Status;
        SymmacCryptTV_t tv_mac;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aes_cbcmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_mac, 0, sizeof(tv_mac));
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_mac))
        {
            Status = psa_mac_verify_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_verify_setup", Status);

            if (do_mac_update(&SymContext,&tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_mac) != END_TEST_SUCCES)
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

        test_vectors_aes_cbcmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aria_cmac)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Algorithm = PSA_ALG_CMAC;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        size_t mac_size = (128/8);
        bool fverify = false;
        TestVector_ARIA_CMAC_t tv_p;
        SymmacCryptTV_t tv_mac;
        psa_status_t Status;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aria_cmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if ((tv_p->MsgLen == 0) || (tv_p->MacLen != 16))
        {
            test_vectors_aria_cmac_release(tv_p);
            continue;
        }

        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_mac))
        {
            if (do_mac_test(ndx, key, Algorithm, mac_size, fverify, &tv_mac) != END_TEST_SUCCES)
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
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        if (PSA_SUCCESS == setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_mac))
        {
            fverify = true;
            if (do_mac_test(ndx, key_ver, Algorithm, mac_size, fverify, &tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Status = psa_destroy_key(key_ver);
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
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        test_vectors_aria_cmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aria_cmac_multipart)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_ARIA_CMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = false;
        psa_algorithm_t Algorithm = PSA_ALG_CMAC;
        psa_status_t Status;
        SymmacCryptTV_t tv_mac;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aria_cmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if ((tv_p->MsgLen == 0) || (tv_p->MacLen != 16))
        {
            test_vectors_aria_cmac_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_mac, 0, sizeof(tv_mac));
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_mac))
        {
            Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup", Status);

            if (do_mac_update(&SymContext, &tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_mac) != END_TEST_SUCCES)
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

        test_vectors_aria_cmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aria_cmac_multipart_verify)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_ARIA_CMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = true;
        psa_algorithm_t Algorithm = PSA_ALG_CMAC;
        psa_status_t Status;
        SymmacCryptTV_t tv_mac;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aria_cmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if ((tv_p->MsgLen == 0) || (tv_p->MacLen != 16))
        {
            test_vectors_aria_cmac_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_mac, 0, sizeof(tv_mac));
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_mac))
        {
            Status = psa_mac_verify_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_verify_setup", Status);

            if (do_mac_update(&SymContext,&tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_mac) != END_TEST_SUCCES)
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

        test_vectors_aria_cmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aria_cbcmac)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Algorithm = PSA_ALG_CBC_MAC;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        size_t mac_size = (128/8);
        bool fverify = false;
        TestVector_ARIA_CBCMAC_t tv_p;
        SymmacCryptTV_t tv_mac;
        psa_status_t Status;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aria_cbcmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_mac))
        {
            if (do_mac_test(ndx, key, Algorithm, mac_size, fverify, &tv_mac) != END_TEST_SUCCES)
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
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        if (PSA_SUCCESS == setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_mac))
        {
            fverify = true;
            if (do_mac_test(ndx, key_ver, Algorithm, mac_size, fverify, &tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key_ver);
                Failed++;
            }
            else
            {
                Status = psa_destroy_key(key_ver);
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
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }

        test_vectors_aria_cbcmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aria_cbcmac_multipart)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_ARIA_CBCMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = false;
        psa_algorithm_t Algorithm = PSA_ALG_CBC_MAC;
        psa_status_t Status;
        SymmacCryptTV_t tv_mac;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aria_cbcmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_mac, 0, sizeof(tv_mac));
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_mac))
        {
            Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup", Status);

            if (do_mac_update(&SymContext, &tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_mac) != END_TEST_SUCCES)
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

        test_vectors_aria_cbcmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_aria_cbcmac_multipart_verify)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_ARIA_CBCMAC_t tv_p;
        psa_mac_operation_t SymContext;
        psa_key_id_t key;
        bool fverify = true;
        psa_algorithm_t Algorithm = PSA_ALG_CBC_MAC;
        psa_status_t Status;
        SymmacCryptTV_t tv_mac;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aria_cbcmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&tv_mac, 0, sizeof(tv_mac));
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;

        setupmacTVctx(&tv_mac, tv_p->Msg, tv_p->MsgLen, tv_p->Key, tv_p->KeyLen, tv_p->Mac,tv_p->MacLen);
        if (PSA_SUCCESS == setupmackey(&key, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_mac))
        {
            Status = psa_mac_verify_setup(&SymContext, key, Algorithm);
            fail_if(Status != PSA_SUCCESS, "psa_mac_verify_setup", Status);

            if (do_mac_update(&SymContext,&tv_mac) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                (void)psa_destroy_key(key);
                Failed++;
            }
            else
            {
                if (do_mac_final(ndx, &SymContext, fverify, &tv_mac) != END_TEST_SUCCES)
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

        test_vectors_aria_cbcmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_mac_state)
{
    psa_mac_operation_t SymContext;
    psa_algorithm_t Algorithm = PSA_ALG_HMAC(PSA_ALG_SHA_256);
    size_t mac_size = (224/8);
    uint8_t mac[224];
    size_t mac_length;
    psa_status_t Status;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    TestVector_HMAC_t tv_p;
    SymmacCryptTV_t tv_hmac;
    psa_key_lifetime_t lifetime;

#define PSA_MAC_STATE_INIT      0U
#define PSA_MAC_STATE_SETUP     1U
#define PSA_MAC_STATE_UPDATE    2U

    tv_p = test_vectors_hmac_get(26);
    setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
    lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;
    Status = setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_HMAC , lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);
    Status = setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_HMAC , lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);

    SymContext.mac_state = PSA_MAC_STATE_SETUP;
    Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_mac_sign_setup()=", Status);

    SymContext.mac_state = PSA_MAC_STATE_SETUP;
    Status = psa_mac_verify_setup(&SymContext, key_ver, Algorithm);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_mac_verify_setup()=", Status);

    SymContext.mac_state = PSA_MAC_STATE_INIT;
    Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
    fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup()=", Status);
    SymContext.mac_state = PSA_MAC_STATE_INIT;
    Status = psa_mac_update(&SymContext, tv_hmac.Msg_p, tv_hmac.MsgLen);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_mac_update()=", Status);

    SymContext.mac_state = PSA_MAC_STATE_INIT;
    Status = psa_mac_sign_finish(&SymContext, mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_mac_sign_finish()=", Status);

    SymContext.mac_state = PSA_MAC_STATE_SETUP;
    Status = psa_mac_sign_finish(&SymContext, mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_mac_sign_finish()=", Status);

    SymContext.mac_state = PSA_MAC_STATE_INIT;
    Status = psa_mac_verify_finish(&SymContext, mac, mac_size);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_mac_verify_finish()=", Status);
    SymContext.mac_state = PSA_MAC_STATE_SETUP;
    Status = psa_mac_verify_finish(&SymContext, mac, mac_size);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_mac_verify_finish()=", Status);

    Status = psa_mac_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_mac_abort()=", Status);

    Status = psa_destroy_key(key);
    fail_if(Status != PSA_SUCCESS, "psa_destroy_key()=", Status);
    Status = psa_destroy_key(key_ver);
    fail_if(Status != PSA_SUCCESS, "psa_destroy_key()=", Status);

#undef PSA_MAC_STATE_INIT
#undef PSA_MAC_STATE_SETUP
#undef PSA_MAC_STATE_UPDATE
}
END_TEST

/*----------------------------------------------------------------------------
 * Some negative Hash tests
 *--------------------------------------------------------------------------*/
START_TEST(test_mac_invalid_algorithm)
{
    psa_mac_operation_t SymContext;
    psa_algorithm_t Algorithm = PSA_ALG_HMAC(PSA_ALG_SHA_256);
    size_t mac_size = 256;
    uint8_t mac[256];
    size_t mac_length;
    psa_status_t Status;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    TestVector_HMAC_t tv_p;
    SymmacCryptTV_t tv_hmac;
    psa_key_lifetime_t lifetime;

    memset(&SymContext, 0, sizeof(SymContext));
    tv_p = test_vectors_hmac_get(26);
    setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
    lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;
    Status = setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_HMAC , lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);
    Status = setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_HMAC , lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);

    Status = psa_mac_compute(key, PSA_ALG_NONE, tv_hmac.Msg_p, tv_hmac.MsgLen,
                             mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_compute()=", Status);

    Status = psa_mac_compute(key, PSA_ALG_CTR, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_compute()=", Status);

    Status = psa_mac_verify(key_ver, PSA_ALG_NONE, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, mac_size);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify()=", Status);

    Status = psa_mac_verify(key_ver, PSA_ALG_CTR, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, mac_size);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify()=", Status);

    Status = psa_mac_sign_setup(&SymContext, key, PSA_ALG_NONE);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_sign_setup()=", Status);

    Status = psa_mac_sign_setup(&SymContext, key, PSA_ALG_CTR);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_sign_setup()=", Status);

    Status = psa_mac_verify_setup(&SymContext, key_ver, PSA_ALG_NONE);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify_setup()=", Status);

    Status = psa_mac_verify_setup(&SymContext, key_ver, PSA_ALG_CTR);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify_setup()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
}
END_TEST

START_TEST(test_mac_buffer_too_small)
{
    psa_mac_operation_t SymContext;
    psa_mac_operation_t SymContext_ver;
    psa_algorithm_t Algorithm = PSA_ALG_HMAC(PSA_ALG_SHA_256);
    size_t mac_size = (224/8);
    uint8_t mac[224];
    size_t mac_length;
    psa_status_t Status;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    TestVector_HMAC_t tv_p;
    SymmacCryptTV_t tv_hmac;
    psa_key_lifetime_t lifetime;

    tv_p = test_vectors_hmac_get(26);
    setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
    lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;
    Status = setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_HMAC , lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);
    Status = setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_HMAC , lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);

    memset(&SymContext, 0, sizeof(SymContext));
    memset(&SymContext_ver, 0, sizeof(SymContext_ver));
    Status = psa_mac_compute(key, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_mac_compute()=", Status);

    Status = psa_mac_sign_setup(&SymContext, key, Algorithm);
    fail_if(Status != PSA_SUCCESS, "psa_mac_sign_setup()", Status);
    Status = psa_mac_update(&SymContext, tv_hmac.Msg_p, tv_hmac.MsgLen);
    fail_if(Status != PSA_SUCCESS, "psa_mac_update()", Status);
    Status = psa_mac_sign_finish(&SymContext, mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_mac_sign_finish()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_mac_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_mac_abort()=", Status);

    Status = psa_mac_verify_setup(&SymContext_ver, key_ver, Algorithm);
    fail_if(Status != PSA_SUCCESS, "psa_mac_verify_setup()", Status);
    Status = psa_mac_update(&SymContext_ver, tv_hmac.Msg_p, tv_hmac.MsgLen);
    fail_if(Status != PSA_SUCCESS, "psa_mac_update()", Status);
    Status = psa_mac_verify_finish(&SymContext_ver, mac, mac_size);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_mac_verify_finish()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_mac_abort(&SymContext_ver);
    fail_if(Status != PSA_SUCCESS, "psa_mac_abort()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
}
END_TEST

START_TEST(test_mac_arguments)
{
    psa_mac_operation_t SymContext;
    psa_algorithm_t Algorithm = PSA_ALG_HMAC(PSA_ALG_SHA_256);
    size_t mac_size = (224/8);
    uint8_t mac[224];
    size_t mac_length;
    psa_status_t Status;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    TestVector_HMAC_t tv_p;
    SymmacCryptTV_t tv_hmac;
    psa_key_lifetime_t lifetime;

    /* Ensure that the following key entries are empty
     * (could still be use due to previous failed tests)
     */
    (void)psa_destroy_key(1);
    (void)psa_destroy_key(2);
    (void)psa_destroy_key(3);
    (void)psa_destroy_key(4);
    (void)psa_destroy_key(5);

    /* Start various argument tests */
    tv_p = test_vectors_hmac_get(26);
    setupmacTVctx(&tv_hmac, tv_p->Msg_p, tv_p->MsgLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Mac_p,tv_p->MacLen);
    lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;
    Status = setupmackey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_HMAC , lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);
    Status = setupmackey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_HMAC , lifetime, 0U, &tv_hmac);
    fail_if(PSA_SUCCESS != Status,"Could not create key", Status);

    memset(&SymContext, 0, sizeof(SymContext));
    Status = psa_mac_compute(0, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                             mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_mac_compute()=", Status);

    (void)psa_destroy_key(5); // make sure key is not used
    Status = psa_mac_compute(5, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                             mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_mac_compute()=", Status);

    Status = psa_mac_compute(key_ver, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_mac_compute()=", Status);

    Status = psa_mac_compute(key, Algorithm, NULL, tv_hmac.MsgLen,
                              mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_compute()=", Status);

    Status = psa_mac_compute(key, Algorithm, tv_hmac.Msg_p, 0U,
                              mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_compute()=", Status);

    Status = psa_mac_compute(key, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              NULL, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_compute()=", Status);

    Status = psa_mac_compute(key, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, 0, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_compute()=", Status);

    Status = psa_mac_compute(key, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, mac_size, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_compute()=", Status);

    Status = psa_mac_verify(5, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, mac_size);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_mac_verify()=", Status);

    Status = psa_mac_verify(key, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, mac_size);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_mac_verify()=", Status);

    Status = psa_mac_verify(key_ver, Algorithm, NULL, tv_hmac.MsgLen,
                              mac, mac_size);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify()=", Status);

    Status = psa_mac_verify(key_ver, Algorithm, tv_hmac.Msg_p, 0,
                              mac, mac_size);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify()=", Status);

    Status = psa_mac_verify(key_ver, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              NULL, mac_size);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify()=", Status);

    Status = psa_mac_verify(key_ver, Algorithm, tv_hmac.Msg_p, tv_hmac.MsgLen,
                              mac, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify()=", Status);

    Status = psa_mac_sign_setup(&SymContext, 5, Algorithm);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_mac_sign_setup()=", Status);

    Status = psa_mac_sign_setup(&SymContext, key_ver, Algorithm);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_mac_sign_setup()=", Status);

    Status = psa_mac_sign_setup(NULL, key, Algorithm);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_sign_setup()=", Status);

    Status = psa_mac_verify_setup(&SymContext, 5, Algorithm);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_mac_verify_setup()=", Status);

    Status = psa_mac_verify_setup(&SymContext, key, Algorithm);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_mac_verify_setup()=", Status);

    Status = psa_mac_verify_setup(NULL, key_ver, Algorithm);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify_setup()=", Status);

    Status = psa_mac_update(NULL, tv_hmac.Msg_p, tv_hmac.MsgLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_update()=", Status);

    Status = psa_mac_update(&SymContext, NULL, tv_hmac.MsgLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_update()=", Status);

    Status = psa_mac_update(&SymContext, tv_hmac.Msg_p, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_update()=", Status);

    Status = psa_mac_sign_finish(NULL, mac, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_sign_finish()=", Status);

    Status = psa_mac_sign_finish(&SymContext, NULL, mac_size, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_sign_finish()=", Status);

    Status = psa_mac_sign_finish(&SymContext, mac, 0, &mac_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_sign_finish()=", Status);

    Status = psa_mac_sign_finish(&SymContext, mac, mac_size, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_sign_finish()=", Status);

    Status = psa_mac_verify_finish(NULL, mac, mac_size);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify_finish()=", Status);

    Status = psa_mac_verify_finish(&SymContext, NULL, mac_size);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify_finish()=", Status);

    Status = psa_mac_verify_finish(&SymContext, mac, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_verify_finish()=", Status);

    Status = psa_mac_abort(NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_mac_abort()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
}
END_TEST


int
suite_add_test_mac(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SymCrypto_Mac_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_hmac, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_multipart) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_multipart_verify) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_multipart_key_in_use) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_multipart_chunks) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_aes_cmac, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aes_cmac_multipart) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aes_cmac_multipart_verify) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aes_cbcmac) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aes_cbcmac_multipart) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aes_cbcmac_multipart_verify) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aria_cmac) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aria_cmac_multipart) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aria_cmac_multipart_verify) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aria_cbcmac) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aria_cbcmac_multipart) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_aria_cbcmac_multipart_verify) != 0) goto FuncErrorReturn;

        if (sfzutf_test_add(TestCase_p, test_mac_state) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_mac_invalid_algorithm) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_mac_buffer_too_small) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_mac_arguments) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_mac.c */
