/* psatest_asym_sign_verify.c
 *
 * Description: tests for asymmetric signatures.
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
#include "testvectors_rsa.h"
#include "testvectors_ecdsa.h"
#include "testvectors_eddsa.h"
#include "testvectors_asn1_der.h"

/*----------------------------------------------------------------------------
 * setupasymkey
 *
 * Helper function to setup key.
 */
static psa_status_t
setupasymkey(psa_key_id_t * key,
             psa_algorithm_t Mode,
             psa_key_usage_t usage_flag,
             psa_key_type_t key_type,
             psa_key_lifetime_t lifetime,
             psa_key_id_t uid,
             const uint8_t * data_p,
             uint32_t ModulusSize,
             uint32_t Datalen)
{
    psa_key_attributes_t attributes = { 0 };
    psa_status_t Status;

    psa_set_key_type(&attributes, key_type);
    psa_set_key_algorithm(&attributes, Mode);
    psa_set_key_usage_flags(&attributes, usage_flag);
    psa_set_key_bits(&attributes, ModulusSize);
    psa_set_key_lifetime(&attributes, lifetime);
    if (uid != 0U)
    {
        psa_set_key_id(&attributes, uid);
    }
    Status = psa_import_key(&attributes, data_p, Datalen, key);

    return Status;
}
/*----------------------------------------------------------------------------
 * test_pkcs1v15_2048
 *
 * Test with pkcs1v15 sign/verify test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_pkcs1v15_2048)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_PKCS1_METHOD) ||
            (tv_key_sign_p->ModulusSize != 2048U) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }

        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm;
            psa_algorithm_t HashAlg;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_RSA_PKCS1v15_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t signature[256] = {0};
            size_t signature_length = 0;
            psa_key_id_t uid;
            psa_key_id_t uid_ver;

            tv_p = test_vectors_rsa_pkcs1v15_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_sign_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }
            if (tv_p->ModulusBits != 2048)
            {
                test_vectors_rsa_pkcs1v15_release(tv_p);
                continue;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                HashAlg = PSA_ALG_SHA_1;
                break;
            case 224:
                HashAlg = PSA_ALG_SHA_224;
                break;
            case 256:
                HashAlg = PSA_ALG_SHA_256;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                HashAlg = PSA_ALG_SHA_384;
                break;
            case 512:
                HashAlg = PSA_ALG_SHA_512;
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_rsa_pkcs1v15_release(tv_p);
                continue;
            }
            Algorithm = PSA_ALG_RSA_PKCS1V15_SIGN(HashAlg);

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

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                  lifetime, uid, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
            unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign(1)", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                  lifetime, uid_ver, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify(1)", Status);

            if ((_i == 1) || (_i == 4))
            {
                psa_key_id_t key2;
                psa_key_id_t key_ver2;

                Status = setupasymkey(&key2, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                      lifetime, uid, NULL, tv_key_sign_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey sign(2)", Status);

                Status = setupasymkey(&key_ver2, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                      lifetime, uid_ver, NULL, tv_key_verify_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey verify(2)", Status);

                (void)psa_destroy_key(key2);
                (void)psa_destroy_key(key_ver2);
            }

            Status = psa_sign_message(key, Algorithm, tv_p->Msg_p, tv_p->MsgBytes, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_message(key_ver, Algorithm, tv_p->Msg_p, tv_p->MsgBytes, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_rsa_pkcs1v15_release(tv_p);
        }
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_pkcs1v15_long_msg
 *
 * Test with pkcs1v15 sign/verify with long message.
 */
START_TEST(test_pkcs1v15_long_msg)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_PKCS1_METHOD) ||
            (tv_key_sign_p->ModulusSize != 2048U) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm;
            psa_algorithm_t HashAlg;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_RSA_PKCS1v15_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t signature[256] = {0};
            size_t signature_length = 0;
            uint32_t MessageLen = 10 * 1024;
            uint8_t * Message_p;

            tv_p = test_vectors_rsa_pkcs1v15_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_sign_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }
            if (tv_p->ModulusBits != 2048)
            {
                test_vectors_rsa_pkcs1v15_release(tv_p);
                continue;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                HashAlg = PSA_ALG_SHA_1;
                break;
            case 224:
                HashAlg = PSA_ALG_SHA_224;
                break;
            case 256:
                HashAlg = PSA_ALG_SHA_256;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                HashAlg = PSA_ALG_SHA_384;
                break;
            case 512:
                HashAlg = PSA_ALG_SHA_512;
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_rsa_pkcs1v15_release(tv_p);
                continue;
            }

            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
            Algorithm = PSA_ALG_RSA_PKCS1V15_SIGN(HashAlg);
            Message_p = (uint8_t *)SFZUTF_MALLOC(MessageLen);
            fail_if(Message_p == NULL, "Allocation ", (int)MessageLen);
            memset(Message_p, 'a', MessageLen);
            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                   lifetime, 0, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                   lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

            Status = psa_sign_message(key, Algorithm, Message_p, MessageLen, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_message(key_ver, Algorithm, Message_p, MessageLen, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            SFZUTF_FREE(Message_p);
            test_vectors_rsa_pkcs1v15_release(tv_p);
        }
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_pkcs1v15_hash_2048
 *
 * Test with pkcs1v15 sign/verify with hashed message.
 */
START_TEST(test_pkcs1v15_hash_2048)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_PKCS1_METHOD) ||
            (tv_key_sign_p->ModulusSize != 2048U) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm;
            psa_algorithm_t HashAlg;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_RSA_PKCS1v15_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t signature[256] = {0};
            size_t signature_length = 0;
            uint8_t hash[64] = {0};
            size_t hash_length = 0U;

            tv_p = test_vectors_rsa_pkcs1v15_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_sign_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }
            if (tv_p->ModulusBits != 2048)
            {
                test_vectors_rsa_pkcs1v15_release(tv_p);
                continue;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                HashAlg = PSA_ALG_SHA_1;
                break;
            case 224:
                HashAlg = PSA_ALG_SHA_224;
                break;
            case 256:
                HashAlg = PSA_ALG_SHA_256;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                HashAlg = PSA_ALG_SHA_384;
                break;
            case 512:
                HashAlg = PSA_ALG_SHA_512;
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_rsa_pkcs1v15_release(tv_p);
                continue;
            }

            Status = psa_hash_compute(HashAlg, tv_p->Msg_p, tv_p->MsgBytes, hash, 64, &hash_length);
            fail_if(PSA_SUCCESS != Status, "psa_hash_compute sign()", Status);

            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
            Algorithm = PSA_ALG_RSA_PKCS1V15_SIGN(HashAlg);

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_HASH, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                   lifetime, 0, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_HASH, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                   lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

            Status = psa_sign_hash(key, Algorithm, hash, hash_length, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_hash(key_ver, Algorithm, hash, hash_length, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_rsa_pkcs1v15_release(tv_p);
        }
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_pss_2048
 *
 * Test with pss sign/verify test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_pss_2048)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_p == NULL)
        {
            break;
        }
        if ((tv_key_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_p->Method != TV_ASN1DER_PSS_METHOD) ||
            (tv_key_p->ModulusSize != 2048U) ||
            (tv_key_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm;
            psa_algorithm_t HashAlg;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_RSA_PSS_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t signature[256] = {0};
            size_t signature_length = 0;
            psa_key_id_t uid;
            psa_key_id_t uid_ver;

            tv_p = test_vectors_rsa_pss_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }
            if (tv_p->ModulusBits != 2048)
            {
                test_vectors_rsa_pss_release(tv_p);
                continue;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                HashAlg = PSA_ALG_SHA_1;
                break;
            case 224:
                HashAlg = PSA_ALG_SHA_224;
                break;
            case 256:
                HashAlg = PSA_ALG_SHA_256;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                HashAlg = PSA_ALG_SHA_384;
                break;
            case 512:
                HashAlg = PSA_ALG_SHA_512;
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_rsa_pss_release(tv_p);
                continue;
            }
            Algorithm = PSA_ALG_RSA_PSS(HashAlg);

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

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                  lifetime, uid, tv_key_p->pData, tv_key_p->ModulusSize, tv_key_p->DataLen);
            unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign(1)", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                  lifetime, uid_ver, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify(1)", Status);

            if ((_i == 1) || (_i == 4))
            {
                psa_key_id_t key2;
                psa_key_id_t key_ver2;

                Status = setupasymkey(&key2, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                      lifetime, uid, NULL, tv_key_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey sign(2)", Status);

                Status = setupasymkey(&key_ver2, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                      lifetime, uid_ver, NULL, tv_key_verify_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey verify(2)", Status);

                (void)psa_destroy_key(key2);
                (void)psa_destroy_key(key_ver2);
            }

            Status = psa_sign_message(key, Algorithm, tv_p->Msg_p, tv_p->MsgBytes, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_message(key_ver, Algorithm, tv_p->Msg_p, tv_p->MsgBytes, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_rsa_pss_release(tv_p);
        }
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_pss_hash_2048
 *
 * Test with pss sign/verify with hashed message.
 */
START_TEST(test_pss_hash_2048)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_p == NULL)
        {
            break;
        }
        if ((tv_key_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_p->Method != TV_ASN1DER_PSS_METHOD) ||
            (tv_key_p->ModulusSize != 2048U) ||
            (tv_key_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm;
            psa_algorithm_t HashAlg;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_RSA_PSS_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t signature[256] = {0};
            size_t signature_length = 0;
            uint8_t hash[64] = {0};
            size_t hash_length = 0U;

            tv_p = test_vectors_rsa_pss_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }
            if (tv_p->ModulusBits != 2048)
            {
                test_vectors_rsa_pss_release(tv_p);
                continue;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                HashAlg = PSA_ALG_SHA_1;
                break;
            case 224:
                HashAlg = PSA_ALG_SHA_224;
                break;
            case 256:
                HashAlg = PSA_ALG_SHA_256;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                HashAlg = PSA_ALG_SHA_384;
                break;
            case 512:
                HashAlg = PSA_ALG_SHA_512;
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_rsa_pss_release(tv_p);
                continue;
            }

            Status = psa_hash_compute(HashAlg, tv_p->Msg_p, tv_p->MsgBytes, hash, 64, &hash_length);
            fail_if(PSA_SUCCESS != Status, "psa_hash_compute sign()", Status);

            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
            Algorithm = PSA_ALG_RSA_PSS(HashAlg);
            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_HASH, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                   lifetime, 0, tv_key_p->pData, tv_key_p->ModulusSize, tv_key_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_HASH, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                   lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

            Status = psa_sign_hash(key, Algorithm, hash, hash_length, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_hash(key_ver, Algorithm, hash, hash_length, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_rsa_pss_release(tv_p);
        }
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_pss_long_msg
 *
 * Test with pss sign/verify with long message.
 */
START_TEST(test_pss_long_msg)
{
    uint32_t ndx;
    uint32_t ndx_key;
    uint32_t ndx_hash;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_p == NULL)
        {
            break;
        }
        if ((tv_key_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_p->Method != TV_ASN1DER_PSS_METHOD) ||
            (tv_key_p->ModulusSize != 2048U) ||
            (tv_key_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        psa_algorithm_t HashAlg = PSA_ALG_NONE;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        for (ndx_hash = 0; ndx_hash < 5; ndx_hash++)
#else
        for (ndx_hash = 0; ndx_hash < 3; ndx_hash++)
#endif
        {
            if (ndx_hash == 0)
            {
                HashAlg = PSA_ALG_SHA_1;
            }
            else if (ndx_hash == 1)
            {
                HashAlg = PSA_ALG_SHA_224;
            }
            else if (ndx_hash == 2)
            {
                HashAlg = PSA_ALG_SHA_256;
            }
            else if (ndx_hash == 3)
            {
                HashAlg = PSA_ALG_SHA_384;
            }
            else
            {
                HashAlg = PSA_ALG_SHA_512;
            }
            for (ndx = 0; ; ndx++)
            {
                psa_algorithm_t Algorithm = PSA_ALG_NONE;
                psa_key_id_t key;
                psa_key_id_t key_ver;
                TestVector_RSA_PSS_t tv_p;
                psa_key_lifetime_t lifetime = 0;
                psa_status_t Status;
                uint8_t signature[256] = {0};
                size_t signature_length = 0;
                uint32_t MessageLen = 10 * 1024;
                uint8_t * Message_p;

                tv_p = test_vectors_rsa_pss_get(ndx);
                if (tv_p == NULL)
                {
                    test_vectors_asn1_der_release(tv_key_p);
                    test_vectors_asn1_der_release(tv_key_verify_p);
                    break;
                }
                if (tv_p->ModulusBits != 2048)
                {
                    test_vectors_rsa_pss_release(tv_p);
                    continue;
                }

                lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
                Algorithm = PSA_ALG_RSA_PSS(HashAlg);
                Message_p = (uint8_t *)SFZUTF_MALLOC(MessageLen);
                fail_if(Message_p == NULL, "Allocation ", (int)MessageLen);
                memset(Message_p, 'a', MessageLen);
                Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                    lifetime, 0, tv_key_p->pData, tv_key_p->ModulusSize, tv_key_p->DataLen);
                fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

                Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                    lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
                fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

                Status = psa_sign_message(key, Algorithm, Message_p, MessageLen, signature, sizeof(signature), &signature_length);
                if (PSA_SUCCESS == Status)
                {
                    Status = psa_verify_message(key_ver, Algorithm, Message_p, MessageLen, signature, signature_length);
                    if (Status != PSA_SUCCESS)
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
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                (void)psa_destroy_key(key);
                (void)psa_destroy_key(key_ver);
                SFZUTF_FREE(Message_p);
                test_vectors_rsa_pss_release(tv_p);
                break;
            }
        }
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_pss_any_salt_2048
 *
 * Test with pss sign/verify with any salt.
 */
START_TEST(test_pss_any_salt_2048)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_p == NULL)
        {
            break;
        }
        if ((tv_key_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_p->Method != TV_ASN1DER_PSS_METHOD) ||
            (tv_key_p->ModulusSize != 2048U) ||
            (tv_key_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm = PSA_ALG_NONE;
            psa_algorithm_t HashAlg = PSA_ALG_NONE;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_RSA_PSS_t tv_p;
            psa_key_lifetime_t lifetime = 0;
            psa_status_t Status;
            uint8_t signature[256] = {0};
            size_t signature_length = 0;

            tv_p = test_vectors_rsa_pss_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }
            if (tv_p->ModulusBits != 2048)
            {
                test_vectors_rsa_pss_release(tv_p);
                continue;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                HashAlg = PSA_ALG_SHA_1;
                break;
            case 224:
                HashAlg = PSA_ALG_SHA_224;
                break;
            case 256:
                HashAlg = PSA_ALG_SHA_256;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                HashAlg = PSA_ALG_SHA_384;
                break;
            case 512:
                HashAlg = PSA_ALG_SHA_512;
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_rsa_pss_release(tv_p);
                continue;
            }

            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
            Algorithm = PSA_ALG_RSA_PSS_ANY_SALT(HashAlg);
            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                   lifetime, 0, tv_key_p->pData, tv_key_p->ModulusSize, tv_key_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                   lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

            Status = psa_sign_message(key, Algorithm, tv_p->Msg_p, tv_p->MsgBytes, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_message(key_ver, Algorithm, tv_p->Msg_p, tv_p->MsgBytes, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_rsa_pss_release(tv_p);
        }
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_ecdsa_NIST
 *
 * Test with ecdsa NIST sign/verify test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_ecdsa_NIST)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for(ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_ECC_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_NIST_METHOD) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm;
            psa_algorithm_t HashAlg;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_ECDSA_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t signature[136] = {0};
            size_t signature_length = 0;
            psa_key_id_t uid;
            psa_key_id_t uid_ver;

            tv_p = test_vectors_ecdsa_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_sign_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                if (tv_key_sign_p->ModulusSize < 160U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_1;
                }
            break;
            case 224:
                if (tv_key_sign_p->ModulusSize < 224U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_224;
                }
            break;
            case 256:
                if (tv_key_sign_p->ModulusSize < 256U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_256;
                }
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                if (tv_key_sign_p->ModulusSize < 384U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_384;
                }
            break;
            case 512:
                if (tv_key_sign_p->ModulusSize < 512U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_512;
                }
            break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_ecdsa_release(tv_p);
                continue;
            }
            Algorithm = PSA_ALG_ECDSA(HashAlg);

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

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                                  lifetime, uid, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
            unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign(1)", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1),
                                  lifetime, uid_ver, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify(1)", Status);

            if ((_i == 1) || (_i == 4))
            {
                psa_key_id_t key2;
                psa_key_id_t key_ver2;

                Status = setupasymkey(&key2, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                                      lifetime, uid, NULL, tv_key_sign_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey sign(2)", Status);

                Status = setupasymkey(&key_ver2, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1),
                                      lifetime, uid_ver, NULL, tv_key_verify_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey verify(2)", Status);

                (void)psa_destroy_key(key2);
                (void)psa_destroy_key(key_ver2);
            }

            Status = psa_sign_message(key, Algorithm, tv_p->Message_p, tv_p->MessageLen, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_message(key_ver, Algorithm, tv_p->Message_p, tv_p->MessageLen, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_ecdsa_release(tv_p);
        }
        test_vectors_asn1_der_release(tv_key_sign_p);
        test_vectors_asn1_der_release(tv_key_verify_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_ecdsa_hash_NIST
 *
 * Test with ecdsa NIST sign/verify with hashed message.
 */
START_TEST(test_ecdsa_hash_NIST)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for(ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_ECC_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_NIST_METHOD) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm = PSA_ALG_NONE;
            psa_algorithm_t HashAlg = PSA_ALG_NONE;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_ECDSA_t tv_p;
            psa_key_lifetime_t lifetime = 0;
            psa_status_t Status;
            uint8_t signature[136] = {0};
            size_t signature_length = 0;
            uint8_t hash[64] = {0};
            size_t hash_length = 0U;

            tv_p = test_vectors_ecdsa_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_sign_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                if (tv_key_sign_p->ModulusSize < 160U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_1;
                }
                break;
            case 224:
                if (tv_key_sign_p->ModulusSize < 224U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_224;
                }
                break;
            case 256:
                if (tv_key_sign_p->ModulusSize < 256U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_256;
                }
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                if (tv_key_sign_p->ModulusSize < 384U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_384;
                }
                break;
            case 512:
                if (tv_key_sign_p->ModulusSize < 512U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_512;
                }
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_ecdsa_release(tv_p);
                continue;
            }

            Status = psa_hash_compute(HashAlg, tv_p->Message_p, tv_p->MessageLen, hash, 64, &hash_length);
            fail_if(PSA_SUCCESS != Status, "psa_hash_compute sign()", Status);

            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
            Algorithm = PSA_ALG_ECDSA(HashAlg);

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_HASH, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                                   lifetime, 0, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_HASH, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1),
                                   lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

            Status = psa_sign_hash(key, Algorithm, hash, hash_length, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_hash(key_ver, Algorithm, hash, hash_length, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_ecdsa_release(tv_p);
        }
        test_vectors_asn1_der_release(tv_key_sign_p);
        test_vectors_asn1_der_release(tv_key_verify_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_ecdsa_long_msg
 *
 * Test with ecdsa sign/verify with long message.
 */
START_TEST(test_ecdsa_long_msg)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for(ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_ECC_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_NIST_METHOD) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm = PSA_ALG_NONE;
            psa_algorithm_t HashAlg = PSA_ALG_NONE;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_ECDSA_t tv_p;
            psa_key_lifetime_t lifetime = 0;
            psa_status_t Status;
            uint8_t signature[136] = {0};
            size_t signature_length = 0;
            uint32_t MessageLen = 10 * 1024;
            uint8_t * Message_p;

            tv_p = test_vectors_ecdsa_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_sign_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                if (tv_key_sign_p->ModulusSize < 160U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_1;
                }
                break;
            case 224:
                if (tv_key_sign_p->ModulusSize < 224U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_224;
                }
                break;
            case 256:
                if (tv_key_sign_p->ModulusSize < 256U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_256;
                }
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                if (tv_key_sign_p->ModulusSize < 384U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_384;
                }
                break;
            case 512:
                if (tv_key_sign_p->ModulusSize < 512U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_512;
                }
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if ((PSA_ALG_NONE == HashAlg) ||
                (HashAlg != PSA_ALG_SHA_224))
            {
                test_vectors_ecdsa_release(tv_p);
                continue;
            }

            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
            Algorithm = PSA_ALG_ECDSA(HashAlg);
            Message_p = (uint8_t *)SFZUTF_MALLOC(MessageLen);
            fail_if(Message_p == NULL, "Allocation ", (int)MessageLen);
            memset(Message_p, 'a', MessageLen);
            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                                   lifetime, 0, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1),
                                   lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

            Status = psa_sign_message(key, Algorithm, Message_p, MessageLen, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_message(key_ver, Algorithm, Message_p, MessageLen, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_ecdsa_release(tv_p);
            SFZUTF_FREE(Message_p);
            break;
        }
        test_vectors_asn1_der_release(tv_key_sign_p);
        test_vectors_asn1_der_release(tv_key_verify_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_ecdsa_BPOOL
 *
 * Test with ecdsa Brain Pool sign/verify. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_ecdsa_BPOOL)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for(ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_ECC_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_BPOOL_METHOD) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm = PSA_ALG_NONE;
            psa_algorithm_t HashAlg = PSA_ALG_NONE;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_ECDSA_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t signature[136] = {0};
            size_t signature_length = 0;
            psa_key_id_t uid;
            psa_key_id_t uid_ver;


            tv_p = test_vectors_ecdsa_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_sign_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }

            switch(tv_p->HashBits)
            {
            case 160:
                if (tv_key_sign_p->ModulusSize < 160U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_1;
                }
                break;
            case 224:
                if (tv_key_sign_p->ModulusSize < 224U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_224;
                }
                break;
            case 256:
                if (tv_key_sign_p->ModulusSize < 256U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_256;
                }
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case 384:
                if (tv_key_sign_p->ModulusSize < 384U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_384;
                }
                break;
            case 512:
                if (tv_key_sign_p->ModulusSize < 512U)
                {
                    HashAlg = PSA_ALG_NONE;
                }
                else
                {
                    HashAlg = PSA_ALG_SHA_512;
                }
                break;
#endif
            default:
                HashAlg = PSA_ALG_NONE;
                break;
            }
            if (PSA_ALG_NONE == HashAlg)
            {
                test_vectors_ecdsa_release(tv_p);
                continue;
            }
            Algorithm = PSA_ALG_ECDSA(HashAlg);

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

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
                                  lifetime, uid, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
            unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign(1)", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
                                  lifetime, uid_ver, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify(1)", Status);

            if ((_i == 1) || (_i == 4))
            {
                psa_key_id_t key2;
                psa_key_id_t key_ver2;

                Status = setupasymkey(&key2, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
                                      lifetime, uid, NULL, tv_key_sign_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey sign(2)", Status);

                Status = setupasymkey(&key_ver2, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_BRAINPOOL_P_R1),
                                      lifetime, uid_ver, NULL, tv_key_verify_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey verify(2)", Status);

                (void)psa_destroy_key(key2);
                (void)psa_destroy_key(key_ver2);
            }

            Status = psa_sign_message(key, Algorithm, tv_p->Message_p, tv_p->MessageLen, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_message(key_ver, Algorithm, tv_p->Message_p, tv_p->MessageLen, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_ecdsa_release(tv_p);
        }
        test_vectors_asn1_der_release(tv_key_sign_p);
        test_vectors_asn1_der_release(tv_key_verify_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_eddsa_255
 *
 * Test with eddsa sign/verify test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_eddsa_255)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for(ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_ECC_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_TEDWARDS_METHOD) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm = PSA_ALG_PURE_EDDSA;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_EdDSA_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t signature[128] = {0};
            size_t signature_length = 0;
            psa_key_id_t uid;
            psa_key_id_t uid_ver;

            tv_p = test_vectors_eddsa_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_sign_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
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

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS),
                                  lifetime, uid, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
            unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign(1)", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS),
                                  lifetime, uid_ver, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify(1)", Status);

            if ((_i == 1) || (_i == 4))
            {
                psa_key_id_t key2;
                psa_key_id_t key_ver2;

                Status = setupasymkey(&key2, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS),
                                      lifetime, uid, NULL, tv_key_sign_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey sign(2)", Status);

                Status = setupasymkey(&key_ver2, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS),
                                      lifetime, uid_ver, NULL, tv_key_verify_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey verify(2)", Status);

                (void)psa_destroy_key(key2);
                (void)psa_destroy_key(key_ver2);
            }

            Status = psa_sign_message(key, Algorithm, tv_p->Message_p, tv_p->MessageLen, signature, sizeof(signature), &signature_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_verify_message(key_ver, Algorithm, tv_p->Message_p, tv_p->MessageLen, signature, signature_length);
                if (Status != PSA_SUCCESS)
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
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_eddsa_release(tv_p);
        }
        test_vectors_asn1_der_release(tv_key_sign_p);
        test_vectors_asn1_der_release(tv_key_verify_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
/*----------------------------------------------------------------------------
 * test_eddsa_255_long_msg
 *
 * Test with eddsa sign/verify with long message.
 */
START_TEST(test_eddsa_255_long_msg)
{
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for(ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_sign_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_sign_p == NULL)
        {
            break;
        }
        if ((tv_key_sign_p->KeyType != TV_ASN1DER_ECC_KEY_TYPE) ||
            (tv_key_sign_p->Method != TV_ASN1DER_TEDWARDS_METHOD) ||
            (tv_key_sign_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_sign_p);
            continue;
        }
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

        psa_algorithm_t Algorithm = PSA_ALG_PURE_EDDSA;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime = 0;
        psa_status_t Status;
        uint8_t signature[128] = {0};
        size_t signature_length = 0;
        uint32_t MessageLen = 10 * 1024;
        uint8_t * Message_p;

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        Message_p = (uint8_t *)SFZUTF_MALLOC(MessageLen);
        fail_if(Message_p == NULL, "Allocation ", (int)MessageLen);
        memset(Message_p, 'a', MessageLen);
        Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_SIGN_MESSAGE, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS),
                               lifetime, 0, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
        fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

        Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_VERIFY_MESSAGE, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS),
                               lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
        fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

        Status = psa_sign_message(key, Algorithm, Message_p, MessageLen, signature, sizeof(signature), &signature_length);
        if (PSA_SUCCESS == Status)
        {
            Status = psa_verify_message(key_ver, Algorithm, Message_p, MessageLen, signature, signature_length);
            if (Status != PSA_SUCCESS)
            {
                LOG_CRIT("Processed vector %d\n", ndx_key+1);
                Failed++;
            }
            else
            {
                Success++;
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", ndx_key);
            Failed++;
        }
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        SFZUTF_FREE(Message_p);

        test_vectors_asn1_der_release(tv_key_sign_p);
        test_vectors_asn1_der_release(tv_key_verify_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> Failed: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

/*----------------------------------------------------------------------------
 * test_asym_sign_ver_invalid_arguments
 */
START_TEST(test_asym_sign_ver_invalid_arguments)
{
    uint32_t ndx = 0;
    uint32_t ndx_key = 0;
    uint32_t ndx_key_TED = 0;
    TestVector_ASN1_DER_t tv_key_sign_p;
    TestVector_ASN1_DER_t tv_key_verify_p;
    TestVector_ASN1_DER_t tv_key_tedwards;
    TestVector_ECDSA_t tv_p;
    psa_algorithm_t Algorithm;
    psa_algorithm_t HashAlg = PSA_ALG_NONE;
    psa_key_id_t key_message;
    psa_key_id_t key_message_ver;
    psa_key_id_t key_hash;
    psa_key_id_t key_hash_ver;
    psa_key_id_t key_tedw = PSA_KEY_ID_NULL;
    psa_key_usage_t usage_flags;
    psa_key_lifetime_t lifetime = 0;
    psa_status_t Status;
    uint8_t signature[384] = {0};
    size_t signature_length = 0;

    tv_key_sign_p = test_vectors_asn1_der_get(ndx_key);
    tv_key_verify_p = test_vectors_asn1_der_get(ndx_key+1);

    for(ndx_key_TED = 0; ; ndx_key_TED++)
    {
        tv_key_tedwards = test_vectors_asn1_der_get(ndx_key_TED);
        if (tv_key_tedwards == NULL)
        {
            break;
        }
        if ((tv_key_tedwards->KeyType != TV_ASN1DER_ECC_KEY_TYPE) ||
            (tv_key_tedwards->Method != TV_ASN1DER_TEDWARDS_METHOD) ||
            (tv_key_tedwards->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_tedwards);
            continue;
        }
        else
        {
            break;
        }
    }

    tv_p = test_vectors_ecdsa_get(ndx);
    fail_if(NULL == tv_p, "No test vector", ndx);
    switch(tv_p->HashBits)
    {
    case 160:
        HashAlg = PSA_ALG_SHA_1;
        break;
    case 224:
        HashAlg = PSA_ALG_SHA_224;
        break;
    case 256:
        HashAlg = PSA_ALG_SHA_256;
        break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
    case 384:
        HashAlg = PSA_ALG_SHA_384;
        break;
    case 512:
        HashAlg = PSA_ALG_SHA_512;
        break;
#endif
    default:
        HashAlg = PSA_ALG_NONE;
        break;
    }
    if (PSA_ALG_NONE == HashAlg)
    {
        test_vectors_ecdsa_release(tv_p);
        tv_p = NULL;
        fail_if(NULL == tv_p, "No test vector", 0);
    }

    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
    Algorithm = PSA_ALG_ECDSA(HashAlg);

    usage_flags = PSA_KEY_USAGE_SIGN_MESSAGE;
    Status = setupasymkey(&key_message, Algorithm, usage_flags, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                           lifetime, 0, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
    fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

    usage_flags = PSA_KEY_USAGE_VERIFY_MESSAGE;
    Status = setupasymkey(&key_message_ver, Algorithm, usage_flags, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1),
                           lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
    fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

    usage_flags = PSA_KEY_USAGE_SIGN_HASH;
    Status = setupasymkey(&key_hash, Algorithm, usage_flags, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                           lifetime, 0, tv_key_sign_p->pData, tv_key_sign_p->ModulusSize, tv_key_sign_p->DataLen);
    fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

    usage_flags = PSA_KEY_USAGE_VERIFY_HASH;
    Status = setupasymkey(&key_hash_ver, Algorithm, usage_flags, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1),
                           lifetime, 0, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
    fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

    if (tv_key_tedwards != NULL)
    {
        usage_flags = PSA_KEY_USAGE_SIGN_MESSAGE;
        Status = setupasymkey(&key_tedw, PSA_ALG_PURE_EDDSA, usage_flags, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS),
                               lifetime, 0, tv_key_tedwards->pData, tv_key_tedwards->ModulusSize, tv_key_tedwards->DataLen);
        fail_if(PSA_SUCCESS != Status, "setupasymkey tedwards()", Status);
    }

    //key not imported
    (void)psa_destroy_key(6); // make sure key is not used
    Status = psa_sign_message(6, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                              signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_sign_message()=", Status);
    // invalid key usage flag
    Status = psa_sign_message(key_message_ver, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                              signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_sign_message()=", Status);
    // output buffer size small
    Status = psa_sign_message(key_message, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                              signature, 55, &signature_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_sign_message()=", Status);
    // wrong alg
    Status = psa_sign_message(key_message, PSA_ALG_RSA_OAEP(HashAlg), tv_p->Message_p, tv_p->MessageLen,
                              signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_message()=", Status);

    Status = psa_sign_message(key_message, Algorithm, NULL, tv_p->MessageLen,
                              signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_message()=", Status);

    Status = psa_sign_message(key_message, Algorithm, tv_p->Message_p, 0,
                              signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_message()=", Status);

    Status = psa_sign_message(key_message, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                              NULL, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_message()=", Status);

    Status = psa_sign_message(key_message, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                              signature, sizeof(signature), NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_message()=", Status);
    // wrong curve family
    Status = psa_sign_message(key_tedw, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                              signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_message()=", Status);
    // wrong curve family
    Status = psa_sign_message(key_message, PSA_ALG_PURE_EDDSA, tv_p->Message_p, tv_p->MessageLen,
                              signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_message()=", Status);
    //key not imported
    Status = psa_verify_message(6, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                                signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_verify_message()=", Status);
    // invalid key usage flag
    Status = psa_verify_message(key_message, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                                signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_verify_message()=", Status);
    // wrong alg
    Status = psa_verify_message(key_message_ver, PSA_ALG_RSA_OAEP(HashAlg), tv_p->Message_p, tv_p->MessageLen,
                                signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_message()=", Status);

    Status = psa_verify_message(key_message_ver, Algorithm, NULL, tv_p->MessageLen,
                                signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_message()=", Status);

    Status = psa_verify_message(key_message_ver, Algorithm, tv_p->Message_p, 0,
                                signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_message()=", Status);

    Status = psa_verify_message(key_message_ver, Algorithm, tv_p->Message_p, tv_p->MessageLen,
                                NULL, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_message()=", Status);


    Status = psa_sign_hash(6, Algorithm, tv_p->Message_p, 20,
                           signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash_ver, Algorithm, tv_p->Message_p, 20,
                           signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash, Algorithm, tv_p->Message_p, 20,
                           signature, 55, &signature_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash, PSA_ALG_RSA_OAEP(HashAlg), tv_p->Message_p, 20,
                           signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash, Algorithm, NULL, 20,
                           signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash, Algorithm, tv_p->Message_p, 20,
                           NULL, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash, Algorithm, tv_p->Message_p, 20,
                           signature, sizeof(signature), NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash, Algorithm, tv_p->Message_p, 33,
                           signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash, PSA_ALG_ED25519PH, tv_p->Message_p, 20,
                           signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_sign_hash()=", Status);

    Status = psa_sign_hash(key_hash, PSA_ALG_ED448PH, tv_p->Message_p, 20,
                           signature, sizeof(signature), &signature_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_sign_hash()=", Status);


    Status = psa_verify_hash(6, Algorithm, tv_p->Message_p, 20,
                             signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_verify_hash()=", Status);

    Status = psa_verify_hash(key_hash, Algorithm, tv_p->Message_p, 20,
                             signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_verify_hash()=", Status);

    Status = psa_verify_hash(key_hash_ver, PSA_ALG_RSA_OAEP(HashAlg), tv_p->Message_p, 20,
                             signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_hash()=", Status);

    Status = psa_verify_hash(key_hash_ver, Algorithm, NULL, 20,
                             signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_hash()=", Status);

    Status = psa_verify_hash(key_hash_ver, Algorithm, tv_p->Message_p, 20,
                             NULL, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_hash()=", Status);

    Status = psa_verify_hash(key_hash_ver, Algorithm, tv_p->Message_p, 20,
                             signature, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_hash()=", Status);

    Status = psa_verify_hash(key_hash_ver, Algorithm, tv_p->Message_p, 33,
                             signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_verify_hash()=", Status);

    Status = psa_verify_hash(key_hash_ver, PSA_ALG_ED25519PH, tv_p->Message_p, 20,
                             signature, sizeof(signature));
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_verify_hash()=", Status);

    (void)psa_destroy_key(key_message);
    (void)psa_destroy_key(key_message_ver);
    (void)psa_destroy_key(key_hash);
    (void)psa_destroy_key(key_hash_ver);
    (void)psa_destroy_key(key_tedw);
    test_vectors_ecdsa_release(tv_p);
    test_vectors_asn1_der_release(tv_key_sign_p);
    test_vectors_asn1_der_release(tv_key_verify_p);
    test_vectors_asn1_der_release(tv_key_tedwards);
}
END_TEST

int
suite_add_test_asym_sign(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "ASymCrypto_sign_ver_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_pkcs1v15_2048, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_pkcs1v15_hash_2048) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_pkcs1v15_long_msg) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_pss_2048, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_pss_hash_2048) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_pss_long_msg) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_pss_any_salt_2048) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_ecdsa_NIST, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_ecdsa_hash_NIST) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_ecdsa_long_msg) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_ecdsa_BPOOL, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_eddsa_255, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_eddsa_255_long_msg) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_asym_sign_ver_invalid_arguments) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_asym_sign_verify.c */
