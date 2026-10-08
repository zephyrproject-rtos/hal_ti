/* psatest_asym_enc_dec.c
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
 * test_RSA_pkcs1v15_crypt
 *
 * Test with pkcs1v15 wrap/unwrap test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_RSA_pkcs1v15_crypt)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_verify_p == NULL)
        {
            break;
        }
        if ((tv_key_verify_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_verify_p->Method != TV_ASN1DER_PKCS1_METHOD) ||
            (tv_key_verify_p->ModulusSize != 2048U) ||
            (tv_key_verify_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_verify_p);
            continue;
        }
        tv_key_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm = PSA_ALG_RSA_PKCS1V15_CRYPT;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_PKCS1V15WRAP_t tv_p;
            psa_key_lifetime_t lifetime;
            psa_status_t Status;
            uint8_t wrapped_data[256] = {0};
            size_t output_length = 0;
            uint8_t plain_data[300] = {0};
            size_t output_length_unwrap = 0;
            psa_key_id_t uid;
            psa_key_id_t uid_ver;

            tv_p = test_vectors_rsa_pkcs1v15wrap_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }
            if (tv_p->ModulusBits != 2048)
            {
                test_vectors_rsa_pkcs1v15wrap_release(tv_p);
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

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                  lifetime, uid, tv_key_p->pData, tv_key_p->ModulusSize, tv_key_p->DataLen);
            unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign(1)", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                  lifetime, uid_ver, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify(1)", Status);

            if ((_i == 1) || (_i == 4))
            {
                psa_key_id_t key2;
                psa_key_id_t key_ver2;

                Status = setupasymkey(&key2, Algorithm, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                      lifetime, uid, NULL, tv_key_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey sign(2)", Status);

                Status = setupasymkey(&key_ver2, Algorithm, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                      lifetime, uid_ver, NULL, tv_key_verify_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey verify(2)", Status);

                (void)psa_destroy_key(key2);
                (void)psa_destroy_key(key_ver2);
            }

            Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                            NULL, 0,
                                            wrapped_data, sizeof(wrapped_data), &output_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_asymmetric_decrypt(key_ver, Algorithm, wrapped_data, output_length,
                                                NULL, 0,
                                                plain_data, tv_p->PlainDataBytes, &output_length_unwrap);
                if (Status != PSA_SUCCESS)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                else
                {
                    if (output_length_unwrap != tv_p->PlainDataBytes)
                    {
                        LOG_CRIT("Processed vector %d\n", ndx);
                        Failed++;
                    }
                    else
                    {
                        if (memcmp(tv_p->PlainData_p, plain_data, output_length_unwrap) != 0)
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
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_rsa_pkcs1v15wrap_release(tv_p);
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
 * test_RSA_OAEP
 *
 * Test with RSA OAEP wrap/unwrap test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_RSA_OAEP)
{
    uint32_t ndx;
    uint32_t ndx_key;
    int Failed = 0;
    int Success = 0;

    for (ndx_key = 0; ; ndx_key++)
    {
        TestVector_ASN1_DER_t tv_key_p;
        TestVector_ASN1_DER_t tv_key_verify_p;

        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_verify_p == NULL)
        {
            break;
        }
        if ((tv_key_verify_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_verify_p->Method != TV_ASN1DER_PKCS1_METHOD) ||
            (tv_key_verify_p->ModulusSize != 2048U) ||
            (tv_key_verify_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_verify_p);
            continue;
        }
        tv_key_p = test_vectors_asn1_der_get(ndx_key+1);

        for (ndx = 0; ; ndx++)
        {
            psa_algorithm_t Algorithm;
            psa_algorithm_t HashAlg;
            psa_key_id_t key;
            psa_key_id_t key_ver;
            TestVector_RSA_OAEP_t tv_p;
            psa_key_lifetime_t lifetime = 0;
            psa_status_t Status;
            uint8_t wrapped_data[256] = {0};
            size_t output_length = 0;
            uint8_t plain_data[300] = {0};
            size_t output_length_unwrap;
            psa_key_id_t uid;
            psa_key_id_t uid_ver;

            tv_p = test_vectors_rsa_oaep_get(ndx);
            if (tv_p == NULL)
            {
                test_vectors_asn1_der_release(tv_key_p);
                test_vectors_asn1_der_release(tv_key_verify_p);
                break;
            }
            if (tv_p->ModulusBits != 2048)
            {
                test_vectors_rsa_oaep_release(tv_p);
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
                test_vectors_rsa_oaep_release(tv_p);
                continue;
            }
            Algorithm = PSA_ALG_RSA_OAEP(HashAlg);

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

            Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                  lifetime, uid, tv_key_p->pData, tv_key_p->ModulusSize, tv_key_p->DataLen);
            unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
            fail_if(PSA_SUCCESS != Status, "setupasymkey sign(1)", Status);

            Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                  lifetime, uid_ver, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
            fail_if(PSA_SUCCESS != Status, "setupasymkey verify(1)", Status);

            if ((_i == 1) || (_i == 4))
            {
                psa_key_id_t key2;
                psa_key_id_t key_ver2;

                Status = setupasymkey(&key2, Algorithm, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                                      lifetime, uid, NULL, tv_key_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey sign(2)", Status);

                Status = setupasymkey(&key_ver2, Algorithm, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_RSA_KEY_PAIR,
                                      lifetime, uid_ver, NULL, tv_key_verify_p->ModulusSize, 0U);
                fail_if(PSA_SUCCESS != Status, "setupasymkey verify(2)", Status);

                (void)psa_destroy_key(key2);
                (void)psa_destroy_key(key_ver2);
            }

            Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                            tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                            wrapped_data, sizeof(wrapped_data), &output_length);
            if (PSA_SUCCESS == Status)
            {
                Status = psa_asymmetric_decrypt(key_ver, Algorithm, wrapped_data, output_length,
                                                tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                                plain_data, tv_p->PlainDataBytes, &output_length_unwrap);
                if (Status != PSA_SUCCESS)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                else
                {
                    if (output_length_unwrap != tv_p->PlainDataBytes)
                    {
                        LOG_CRIT("Processed vector %d\n", ndx);
                        Failed++;
                    }
                    else
                    {
                        if (memcmp(tv_p->PlainData_p, plain_data, output_length_unwrap) != 0)
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
            (void)psa_destroy_key(key);
            (void)psa_destroy_key(key_ver);
            test_vectors_rsa_oaep_release(tv_p);
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
 * test_asym_enc_invalid_arguments
 */
START_TEST(test_asym_enc_invalid_arguments)
{
    uint32_t ndx;
    uint32_t ndx_key;
    TestVector_ASN1_DER_t tv_key_p;
    TestVector_ASN1_DER_t tv_key_verify_p;
    psa_algorithm_t Algorithm;
    psa_algorithm_t HashAlg;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    TestVector_RSA_OAEP_t tv_p;
    psa_key_lifetime_t lifetime;
    psa_status_t Status;
    uint8_t wrapped_data[256] = {0};
    size_t output_length = 0;
    psa_key_id_t uid = 0U;
    psa_key_id_t uid_ver = 0U;

    for (ndx_key = 0; ; ndx_key++)
    {
        tv_key_verify_p = test_vectors_asn1_der_get(ndx_key);
        if (tv_key_verify_p == NULL)
        {
            unsupported("No vector found");
        }
        if ((tv_key_verify_p->KeyType != TV_ASN1DER_RSA_KEY_TYPE) ||
            (tv_key_verify_p->Method != TV_ASN1DER_PKCS1_METHOD) ||
            (tv_key_verify_p->ModulusSize != 2048U) ||
            (tv_key_verify_p->fPrivateKey != true))
        {
            test_vectors_asn1_der_release(tv_key_verify_p);
        }
        else
        {
            tv_key_p = test_vectors_asn1_der_get(ndx_key+1);
            if (tv_key_verify_p == NULL)
            {
                unsupported("No vector found");
            }
            break;
        }
    }

    for (ndx = 0; ; ndx++)
    {
        tv_p = test_vectors_rsa_oaep_get(ndx);
        if (NULL == tv_p)
        {
            unsupported("No vector found");
        }
        if (tv_p->ModulusBits != 2048)
        {
            test_vectors_rsa_oaep_release(tv_p);
        }
        else
        {
            break;
        }
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
        test_vectors_rsa_oaep_release(tv_p);
        unsupported("Invalid hash");
    }

    LOG_INFO("Processed vector %d\n", ndx);

    /* Default/_i == 0 */
    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

    Algorithm = PSA_ALG_RSA_OAEP(HashAlg);
    Status = setupasymkey(&key, Algorithm, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_RSA_PUBLIC_KEY,
                           lifetime, uid, tv_key_p->pData, tv_key_p->ModulusSize, tv_key_p->DataLen);
    fail_if(PSA_SUCCESS != Status, "setupasymkey sign()", Status);

    Status = setupasymkey(&key_ver, Algorithm, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_RSA_KEY_PAIR,
                           lifetime, uid_ver, tv_key_verify_p->pData, tv_key_verify_p->ModulusSize, tv_key_verify_p->DataLen);
    fail_if(PSA_SUCCESS != Status, "setupasymkey verify()", Status);

    (void)psa_destroy_key(4); // make sure key is not used
    Status = psa_asymmetric_encrypt(4, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key_ver, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, 255, &output_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, PSA_ALG_RSA_PKCS1V15_SIGN(HashAlg), tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, Algorithm, NULL, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, 0,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    NULL, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, 0,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    NULL, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, 209,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_asymmetric_encrypt()=", Status);

    Status = psa_asymmetric_encrypt(key, PSA_ALG_RSA_OAEP(PSA_ALG_SHA3_224), tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_encrypt()=", Status);


    Status = psa_asymmetric_decrypt(4, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, PSA_ALG_RSA_PKCS1V15_SIGN(HashAlg), tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, Algorithm, NULL, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, Algorithm, tv_p->PlainData_p, 0,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    NULL, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, 0,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    NULL, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, Algorithm, tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, 209,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_asymmetric_decrypt()=", Status);

    Status = psa_asymmetric_decrypt(key_ver, PSA_ALG_RSA_OAEP(PSA_ALG_SHA3_224), tv_p->PlainData_p, tv_p->PlainDataBytes,
                                    tv_p->AdditionalInput_p, tv_p->AdditionalInputBytes,
                                    wrapped_data, sizeof(wrapped_data), &output_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_asymmetric_decrypt()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
    test_vectors_rsa_oaep_release(tv_p);
}
END_TEST

int
suite_add_test_asym_enc(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "ASymCrypto_encrypt_decrypt_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_RSA_pkcs1v15_crypt, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_RSA_OAEP, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_asym_enc_invalid_arguments) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_asym_enc_dec.c */
