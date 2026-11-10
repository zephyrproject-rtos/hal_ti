/*
 *  Copyright The Mbed TLS Contributors
 *  Copyright (c) 2025-2026, Texas Instruments Incorporated
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <string.h>

/* The TI PSA Crypto APIs are implemented by PSACrypto_ns.c on the NS side, and by ti_psa_crypto.c on the S side */
#include <ti/drivers/psa/ti_psa_crypto.h>
#include <ti/drivers/psa/ti_psa_crypto_aead.h>
#include <ti/drivers/psa/ti_psa_crypto_cipher.h>
#include <ti/drivers/psa/ti_psa_crypto_hash.h>
#include <ti/drivers/psa/ti_psa_crypto_helper.h> // for LOCAL_INPUT_ALLOC, LOCAL_OUTPUT_ALLOC, isHardwareAccelerated, etc
#include <ti/drivers/psa/ti_psa_crypto_mac.h>

/* Retrieves config-hsm.h and config-psa-crypto-hsm.h */
#include <third_party/mbedtls/include/psa/build_info.h>

#if (TFM_ENABLED == 1)
    /* PSACrypto_ns expects a psa_key_id_t only, without the owner encoded. */
    #ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
        #undef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    #endif
    #include <third_party/tfm/interface/include/psa/crypto.h>
    /**
     * \brief This value is used to mark an handle for multipart operations as invalid.
     */
    #define TFM_CRYPTO_INVALID_HANDLE (0x0u)
#else
    /* Use "full" crypto structs that are visible in S-only or S-side of TFM-enabled builds */
    #include <third_party/mbedtls/include/psa/crypto.h>
    /* Needed for psaInt_KeyMgmtGetKey() in SW Crypto execution paths */
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
    /* mbedtls_psa_xxx() APIs that route PSA to SW crypto */
    #include <third_party/mbedtls/library/psa_crypto_aead.h>
    #include <third_party/mbedtls/library/psa_crypto_cipher.h>
    #include <third_party/mbedtls/library/psa_crypto_ffdh.h>
    #include <third_party/mbedtls/library/psa_crypto_hash.h>
    #include <third_party/mbedtls/library/psa_crypto_mac.h>
    #include <third_party/mbedtls/library/psa_crypto_rsa.h>

    #include <third_party/mbedtls/library/common.h>
    #include <third_party/mbedtls/include/mbedtls/platform.h>
    #include <third_party/mbedtls/include/mbedtls/constant_time.h>
#endif

#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF) || defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
    #define BUILTIN_ALG_ANY_HKDF 1
#endif

#define HKDF_STATE_INIT    0 /* no input yet */
#define HKDF_STATE_STARTED 1 /* got salt */
#define HKDF_STATE_KEYED   2 /* got key */
#define HKDF_STATE_OUTPUT  3 /* output started */

/* Static Declarations */
#if (TI_SW_CRYPTO_ENABLED == 1)
static void psa_wipe_tag_output_buffer(uint8_t *output_buffer,
                                       psa_status_t status,
                                       size_t output_buffer_size,
                                       size_t output_buffer_length);
#endif

/******************************************************************************/
/* Key management */
/******************************************************************************/
psa_status_t psa_copy_key(mbedtls_svc_key_id_t source_key,
                          const psa_key_attributes_t *attributes,
                          mbedtls_svc_key_id_t *target_key)
{
    /* Call TI PSA function to access our KeyStore */
    return ti_psa_copy_key(source_key, attributes, target_key);
}

psa_status_t psa_destroy_key(mbedtls_svc_key_id_t key)
{
    /* Call TI PSA function to access our KeyStore */
    return ti_psa_destroy_key(key);
}

psa_status_t psa_export_key(mbedtls_svc_key_id_t key, uint8_t *data, size_t data_size, size_t *data_length)
{
    /* Call TI PSA function to access our KeyStore */
    return ti_psa_export_key(key, data, data_size, data_length);
}

psa_status_t psa_export_public_key(mbedtls_svc_key_id_t key, uint8_t *data, size_t data_size, size_t *data_length)
{
    /* Call TI PSA function to access our KeyStore */
    return ti_psa_export_public_key(key, data, data_size, data_length);
}

psa_status_t psa_generate_key(const psa_key_attributes_t *attributes, mbedtls_svc_key_id_t *key)
{
    /* Call TI PSA function to access our KeyStore */
    return ti_psa_generate_key(attributes, key);
}

psa_status_t psa_get_key_attributes(mbedtls_svc_key_id_t key, psa_key_attributes_t *attributes)
{
    /* Call TI PSA function to access our KeyStore */
    return ti_psa_get_key_attributes(key, attributes);
}

psa_status_t psa_import_key(const psa_key_attributes_t *attributes,
                            const uint8_t *data,
                            size_t data_length,
                            mbedtls_svc_key_id_t *key)
{
    /* Call TI PSA function to access our KeyStore */
    return ti_psa_import_key(attributes, data, data_length, key);
}

psa_status_t psa_purge_key(mbedtls_svc_key_id_t key)
{
    /* Call TI PSA function to access our KeyStore */
    return ti_psa_purge_key(key);
}

void psa_reset_key_attributes(psa_key_attributes_t *attributes)
{
    /* Call TI PSA function to access our KeyStore */
    ti_psa_reset_key_attributes(attributes);
}

/******************************************************************************/
/* Random generation */
/******************************************************************************/

/* This API must be defined when external RNG is used -
 * MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG. See the prototype
 * in crypto_extra.h. The entropy API path is as follows:
 * psa_generate_random -> psa_generate_random_internal ->
 * mbedtls_psa_external_get_random.
 */
psa_status_t mbedtls_psa_external_get_random(mbedtls_psa_external_random_context_t *context,
                                             uint8_t *output,
                                             size_t output_size,
                                             size_t *output_length)
{
    psa_status_t status;
    (void)context;

    status = ti_psa_generate_random(output, output_size);

    if (status != PSA_SUCCESS)
    {
        /* Nothing to do */
    }
    else
    {
        *output_length = output_size;
    }

    return status;
}

/* Route psa_generate_random() (top-level entropy API) to our external
 * RNG implementation
 */
static psa_status_t psa_generate_random_internal(uint8_t *output, size_t output_size)
{
    /* Since we hardware accelerate random number generation, there will not
     * be an option for SW-based entropy. Therefore, MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG
     * MUST be defined.
     */
#if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
    psa_status_t status;
    size_t output_length = 0;
    status               = mbedtls_psa_external_get_random(NULL, output, output_size, &output_length);
    if (status != PSA_SUCCESS)
    {
        return status;
    }
    /* Breaking up a request into smaller chunks is currently not supported
     * for the external RNG interface. */
    if (output_length != output_size)
    {
        return PSA_ERROR_INSUFFICIENT_ENTROPY;
    }
    return PSA_SUCCESS;
#else
    /* If MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG is defined, we should never
     * reach this point.
     */
    #warning "MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG must be defined to support random number generation."

    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/* Top-level entropy API. Calls internal version, which then calls external RNG. */
psa_status_t psa_generate_random(uint8_t *output, size_t output_size)
{
    psa_status_t status;

#if (TI_SW_CRYPTO_ENABLED == 1)
    LOCAL_OUTPUT_DECLARE(output, output_internal);
    LOCAL_OUTPUT_ALLOC(output, output_size, output_internal);

    status = psa_generate_random_internal(output_internal, output_size);
#else
    status = psa_generate_random_internal(output, output_size);
#endif

#if (TI_SW_CRYPTO_ENABLED == 1)
    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
    LOCAL_OUTPUT_FREE(output, output_internal);
#endif
    return status;
}

/* TODO: MBEDTLS_PSA_BUILTIN_CIPHER must be defined for SW ciphers to work.
 * This is the case if any PSA cipher ALG is #WANTED but not #ACCELERATED
 */

/******************************************************************************/
/* Symmetric cryptography */
/******************************************************************************/

static psa_status_t psa_cipher_setup(psa_cipher_operation_t *operation,
                                     mbedtls_svc_key_id_t key,
                                     psa_algorithm_t alg,
                                     aes_operation_t cipher_operation)
{
    if (isHardwareAccelerated(alg))
    {
        /* Call hardware accelerated function - mark operation->MBEDTLS_PRIVATE(id) as HW-accelerated */
        setCipherOperationID(operation, PSA_CRYPTO_TI_DRIVER_ID);

        if (cipher_operation == AES_ENCRYPT)
        {
            /* Call hardware encryption setup */
            return ti_psa_cipher_encrypt_setup(operation, key, alg);
        }
        else
        {
            /* Call hardware decryption setup */
            return ti_psa_cipher_decrypt_setup(operation, key, alg);
        }
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* Call software implementation - retrieve key material & attributes first */
        setCipherOperationID(operation, PSA_CRYPTO_MBED_TLS_DRIVER_ID);

        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_cipher_encrypt_setup(psa_cipher_operation_t *operation, mbedtls_svc_key_id_t key, psa_algorithm_t alg)
{
    return psa_cipher_setup(operation, key, alg, AES_ENCRYPT);
}

psa_status_t psa_cipher_decrypt_setup(psa_cipher_operation_t *operation, mbedtls_svc_key_id_t key, psa_algorithm_t alg)
{
    return psa_cipher_setup(operation, key, alg, AES_DECRYPT);
}

psa_status_t psa_cipher_generate_iv(psa_cipher_operation_t *operation,
                                    uint8_t *iv_external,
                                    size_t iv_size,
                                    size_t *iv_length)
{
/* Declared variables are only used for SW path - defined at top anyways to avoid
 * LTO issues.
 */
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
#endif

    if (isHardwareCipherOperation(operation))
    {
        return ti_psa_cipher_generate_iv(operation, iv_external, iv_size, iv_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        status = PSA_ERROR_NOT_SUPPORTED;
        return status;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_cipher_set_iv(psa_cipher_operation_t *operation, const uint8_t *iv_external, size_t iv_length)
{
    if (isHardwareCipherOperation(operation))
    {
        return ti_psa_cipher_set_iv(operation, iv_external, iv_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
        // return mbedtls_psa_cipher_set_iv(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
        //                                  iv_external, iv_length);
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_cipher_update(psa_cipher_operation_t *operation,
                               const uint8_t *input,
                               size_t input_length,
                               uint8_t *output,
                               size_t output_size,
                               size_t *output_length)
{
    if (isHardwareCipherOperation(operation))
    {
        return ti_psa_cipher_update(operation, input, input_length, output, output_size, output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
        // return mbedtls_psa_cipher_update(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
        //                                  input, input_length,
        //                                  output, output_size,
        //                                  output_length);
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_cipher_finish(psa_cipher_operation_t *operation,
                               uint8_t *output,
                               size_t output_size,
                               size_t *output_length)
{
    if (isHardwareCipherOperation(operation))
    {
        return ti_psa_cipher_finish(operation, output, output_size, output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
        // return mbedtls_psa_cipher_finish(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
        //                                  output, output_size,
        //                                  output_length);
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_cipher_abort(psa_cipher_operation_t *operation)
{
#if (TFM_ENABLED == 1)
    /* Note that this condition may need to be modified to support SW PSA
     * in TFM_ENABLED configurations.
     */
    if (operation->handle == TFM_CRYPTO_INVALID_HANDLE)
    {
        /* No operation in progress */
        return PSA_SUCCESS;
    }
#else
    /* On the S-side, the operation has an ID which identifies it as HW or SW.
     * If it is neither, we can successfully consider it 'aborted.'
     */
    if (operation->MBEDTLS_PRIVATE(id) == 0)
    {
        /* The object has (apparently) been initialized but it is not (yet)
         * in use. It's ok to call abort on such an object, and there's
         * nothing to do.
         */
        return PSA_SUCCESS;
    }
#endif

    if (isHardwareCipherOperation(operation))
    {
        return ti_psa_cipher_abort(operation);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
        // return mbedtls_psa_cipher_abort(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx);
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_cipher_encrypt(mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *output,
                                size_t output_size,
                                size_t *output_length)
{
    /* For one-shot operations, directly check the algorithm for HW acceleration support, because
     * there is no operation struct previously initialized.
     */
    if (isHardwareAccelerated(alg))
    {
        return ti_psa_cipher_encrypt(key, alg, input, input_length, output, output_size, output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_cipher_decrypt(mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *output,
                                size_t output_size,
                                size_t *output_length)
{
    /* For one-shot operations, directly check the algorithm for HW acceleration support, because
     * there is no operation struct previously initialized.
     */
    if (isHardwareAccelerated(alg))
    {
        return ti_psa_cipher_decrypt(key, alg, input, input_length, output, output_size, output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

#if (TI_SW_CRYPTO_ENABLED == 1)
static psa_status_t psa_validate_tag_length(psa_algorithm_t alg)
{
    const uint8_t tag_len = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

    switch (PSA_ALG_AEAD_WITH_SHORTENED_TAG(alg, 0))
    {
    #if defined(PSA_WANT_ALG_CCM)
        case PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 0):
            /* CCM allows the following tag lengths: 4, 6, 8, 10, 12, 14, 16.*/
            if (tag_len < 4 || tag_len > 16 || tag_len % 2)
            {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
    #endif /* PSA_WANT_ALG_CCM */

    #if defined(PSA_WANT_ALG_GCM)
        case PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_GCM, 0):
            /* GCM allows the following tag lengths: 4, 8, 12, 13, 14, 15, 16. */
            if (tag_len != 4 && tag_len != 8 && (tag_len < 12 || tag_len > 16))
            {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
    #endif /* PSA_WANT_ALG_GCM */

    #if defined(PSA_WANT_ALG_CHACHA20_POLY1305)
        case PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CHACHA20_POLY1305, 0):
            /* We only support the default tag length. */
            if (tag_len != 16)
            {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
    #endif /* PSA_WANT_ALG_CHACHA20_POLY1305 */

        default:
            (void)tag_len;
            return PSA_ERROR_NOT_SUPPORTED;
    }
    return PSA_SUCCESS;
}
#endif

/****************************************************************/
/* AEAD */
/****************************************************************/
#if (TI_SW_CRYPTO_ENABLED == 1)
static psa_status_t psa_aead_final_checks(const psa_aead_operation_t *operation)
{
    if (operation->MBEDTLS_PRIVATE(id) == 0 || !operation->MBEDTLS_PRIVATE(nonce_set))
    {
        return PSA_ERROR_BAD_STATE;
    }

    if (operation->MBEDTLS_PRIVATE(lengths_set) &&
        (operation->MBEDTLS_PRIVATE(ad_remaining) != 0 || operation->MBEDTLS_PRIVATE(body_remaining) != 0))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    return PSA_SUCCESS;
}

/* Helper function to perform common nonce length checks. */
static psa_status_t psa_aead_check_nonce_length(psa_algorithm_t alg, size_t nonce_length)
{
    psa_algorithm_t base_alg = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg);

    switch (base_alg)
    {
    #if defined(PSA_WANT_ALG_GCM)
        case PSA_ALG_GCM:
            /* Not checking max nonce size here as GCM spec allows almost
             * arbitrarily large nonces. Please note that we do not generally
             * recommend the usage of nonces of greater length than
             * PSA_AEAD_NONCE_MAX_SIZE, as large nonces are hashed to a shorter
             * size, which can then lead to collisions if you encrypt a very
             * large number of messages.*/
            if (nonce_length != 0)
            {
                return PSA_SUCCESS;
            }
            break;
    #endif /* PSA_WANT_ALG_GCM */
    #if defined(PSA_WANT_ALG_CCM)
        case PSA_ALG_CCM:
            if (nonce_length >= 7 && nonce_length <= 13)
            {
                return PSA_SUCCESS;
            }
            break;
    #endif /* PSA_WANT_ALG_CCM */
    #if defined(PSA_WANT_ALG_CHACHA20_POLY1305)
        case PSA_ALG_CHACHA20_POLY1305:
            if (nonce_length == 12)
            {
                return PSA_SUCCESS;
            }
            else if (nonce_length == 8)
            {
                return PSA_ERROR_NOT_SUPPORTED;
            }
            break;
    #endif /* PSA_WANT_ALG_CHACHA20_POLY1305 */
        default:
            (void)nonce_length;
            return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_ERROR_INVALID_ARGUMENT;
}
#endif

static psa_status_t psa_aead_setup(psa_aead_operation_t *operation,
                                   mbedtls_svc_key_id_t key,
                                   psa_algorithm_t alg,
                                   aes_operation_t cipher_operation)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status     = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_context_t *slot = NULL;
#endif

    if (isHardwareAccelerated(alg))
    {
        /* Call hardware accelerated function - mark operation->MBEDTLS_PRIVATE(id) as HW-accelerated */
        setAeadOperationID(operation, PSA_CRYPTO_TI_DRIVER_ID);

        if (cipher_operation == AES_ENCRYPT)
        {
            /* Call hardware encryption setup */
            return ti_psa_aead_encrypt_setup(operation, key, alg);
        }
        else
        {
            /* Call hardware decryption setup */
            return ti_psa_aead_decrypt_setup(operation, key, alg);
        }
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        if (!PSA_ALG_IS_AEAD(alg) || PSA_ALG_IS_WILDCARD(alg))
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            goto exit;
        }

        if (operation->MBEDTLS_PRIVATE(id) != 0)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        if (operation->MBEDTLS_PRIVATE(nonce_set) || operation->MBEDTLS_PRIVATE(lengths_set) ||
            operation->MBEDTLS_PRIVATE(ad_started) || operation->MBEDTLS_PRIVATE(body_started))
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        /* Retrieve the specified key into its slot. This also loads
         * the key material and the key attributes into the slot.
         */
        status = psaInt_KeyMgmtGetKey(key, &slot);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        if ((status = psa_validate_tag_length(alg)) != PSA_SUCCESS)
        {
            goto exit;
        }

        /* Mark this operation as a SW operation */
        setAeadOperationID(operation, PSA_CRYPTO_MBED_TLS_DRIVER_ID);

        if (cipher_operation == AES_ENCRYPT)
        {
            status = mbedtls_psa_aead_encrypt_setup(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
                                                    &slot->attributes,
                                                    slot->key,
                                                    slot->key_size,
                                                    alg);
        }
        else
        {
            status = mbedtls_psa_aead_decrypt_setup(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
                                                    &slot->attributes,
                                                    slot->key,
                                                    slot->key_size,
                                                    alg);
        }

        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        operation->MBEDTLS_PRIVATE(key_type) = psa_get_key_type(&slot->attributes);
    }
exit:
    if (status == PSA_SUCCESS)
    {
        operation->MBEDTLS_PRIVATE(alg)        = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg);
        operation->MBEDTLS_PRIVATE(is_encrypt) = (cipher_operation == AES_ENCRYPT) ? 1 : 0;
        ;
    }
    else
    {
        psa_aead_abort(operation);
    }

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_abort(psa_aead_operation_t *operation)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
#endif

#if (TFM_ENABLED == 1)
    /* Note that this condition may need to be modified to support SW PSA
     * in TFM_ENABLED configurations.
     */
    if (operation->handle == TFM_CRYPTO_INVALID_HANDLE)
    {
        /* No operation in progress */
        return PSA_SUCCESS;
    }
#else
    /* On the S-side, the operation has an ID which identifies it as HW or SW.
     * If it is neither, we can successfully consider it 'aborted.'
     */
    if (operation->MBEDTLS_PRIVATE(id) == 0)
    {
        /* The object has (apparently) been initialized but it is not (yet)
         * in use. It's ok to call abort on such an object, and there's
         * nothing to do.
         */
        return PSA_SUCCESS;
    }
#endif

    if (isHardwareAeadOperation(operation))
    {
        return ti_psa_aead_abort(operation);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        status = mbedtls_psa_aead_abort(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx);

        memset(operation, 0, sizeof(*operation));

        return status;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_decrypt(mbedtls_svc_key_id_t key,
                              psa_algorithm_t alg,
                              const uint8_t *nonce,
                              size_t nonce_length,
                              const uint8_t *additional_data,
                              size_t additional_data_length,
                              const uint8_t *ciphertext,
                              size_t ciphertext_length,
                              uint8_t *plaintext,
                              size_t plaintext_size,
                              size_t *plaintext_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_context_t *slot;

    LOCAL_INPUT_DECLARE(nonce, nonce_internal);
    LOCAL_INPUT_DECLARE(additional_data, additional_data_internal);
    LOCAL_INPUT_DECLARE(ciphertext, ciphertext_internal);
    LOCAL_OUTPUT_DECLARE(plaintext, plaintext_internal);
#endif

    /* For one-shot operations, directly check the algorithm for HW acceleration support, because
     * there is no operation struct previously initialized.
     */
    if (isHardwareAccelerated(alg))
    {
        return ti_psa_aead_decrypt(key,
                                   alg,
                                   nonce,
                                   nonce_length,
                                   additional_data,
                                   additional_data_length,
                                   ciphertext,
                                   ciphertext_length,
                                   plaintext,
                                   plaintext_size,
                                   plaintext_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        *plaintext_length = 0;

        if (!PSA_ALG_IS_AEAD(alg) || PSA_ALG_IS_WILDCARD(alg))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        /* Retrieve the specified key into its slot. This also loads
         * the key material and the key attributes into the slot.
         */
        status = psaInt_KeyMgmtGetKey(key, &slot);
        if (status != PSA_SUCCESS)
        {
            return status;
        }

        LOCAL_INPUT_ALLOC(nonce, nonce_length, nonce_internal);
        LOCAL_INPUT_ALLOC(additional_data, additional_data_length, additional_data_internal);
        LOCAL_INPUT_ALLOC(ciphertext, ciphertext_length, ciphertext_internal);
        LOCAL_OUTPUT_ALLOC(plaintext, plaintext_size, plaintext_internal);

        status = psa_aead_check_nonce_length(alg, nonce_length);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        status = mbedtls_psa_aead_decrypt(&slot->attributes,
                                          slot->key,
                                          slot->key_size,
                                          alg,
                                          nonce_internal,
                                          nonce_length,
                                          additional_data_internal,
                                          additional_data_length,
                                          ciphertext_internal,
                                          ciphertext_length,
                                          plaintext_internal,
                                          plaintext_size,
                                          plaintext_length);

        if ((status != PSA_SUCCESS) && (plaintext_size != 0))
        {
            memset(plaintext_internal, 0, plaintext_size);
        }
    }
exit:
    LOCAL_INPUT_FREE(nonce, nonce_internal);
    LOCAL_INPUT_FREE(additional_data, additional_data_internal);
    LOCAL_INPUT_FREE(ciphertext, ciphertext_internal);
    LOCAL_OUTPUT_FREE(plaintext, plaintext_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_decrypt_setup(psa_aead_operation_t *operation, mbedtls_svc_key_id_t key, psa_algorithm_t alg)
{
    return psa_aead_setup(operation, key, alg, AES_DECRYPT);
}

psa_status_t psa_aead_encrypt(mbedtls_svc_key_id_t key,
                              psa_algorithm_t alg,
                              const uint8_t *nonce,
                              size_t nonce_length,
                              const uint8_t *additional_data,
                              size_t additional_data_length,
                              const uint8_t *plaintext,
                              size_t plaintext_length,
                              uint8_t *ciphertext,
                              size_t ciphertext_size,
                              size_t *ciphertext_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_context_t *slot;

    LOCAL_INPUT_DECLARE(nonce, nonce_internal);
    LOCAL_INPUT_DECLARE(additional_data, additional_data_internal);
    LOCAL_INPUT_DECLARE(plaintext, plaintext_internal);
    LOCAL_OUTPUT_DECLARE(ciphertext, ciphertext_internal);
#endif

    /* For one-shot operations, directly check the algorithm for HW acceleration support, because
     * there is no operation struct previously initialized.
     */
    if (isHardwareAccelerated(alg))
    {
        return ti_psa_aead_encrypt(key,
                                   alg,
                                   nonce,
                                   nonce_length,
                                   additional_data,
                                   additional_data_length,
                                   plaintext,
                                   plaintext_length,
                                   ciphertext,
                                   ciphertext_size,
                                   ciphertext_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        *ciphertext_length = 0;

        if (!PSA_ALG_IS_AEAD(alg) || PSA_ALG_IS_WILDCARD(alg))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        /* Retrieve the specified key into its slot. This also loads
         * the key material and the key attributes into the slot.
         */
        status = psaInt_KeyMgmtGetKey(key, &slot);
        if (status != PSA_SUCCESS)
        {
            return status;
        }

        LOCAL_INPUT_ALLOC(nonce, nonce_length, nonce_internal);
        LOCAL_INPUT_ALLOC(additional_data, additional_data_length, additional_data_internal);
        LOCAL_INPUT_ALLOC(plaintext, plaintext_length, plaintext_internal);
        LOCAL_OUTPUT_ALLOC(ciphertext, ciphertext_size, ciphertext_internal);

        status = psa_aead_check_nonce_length(alg, nonce_length);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        status = mbedtls_psa_aead_encrypt(&slot->attributes,
                                          slot->key,
                                          slot->key_size,
                                          alg,
                                          nonce_internal,
                                          nonce_length,
                                          additional_data_internal,
                                          additional_data_length,
                                          plaintext_internal,
                                          plaintext_length,
                                          ciphertext_internal,
                                          ciphertext_size,
                                          ciphertext_length);

        if ((status != PSA_SUCCESS) && (ciphertext_size != 0))
        {
            memset(ciphertext, 0, ciphertext_size);
        }
    }
exit:
    LOCAL_INPUT_FREE(nonce, nonce_internal);
    LOCAL_INPUT_FREE(additional_data, additional_data_internal);
    LOCAL_INPUT_FREE(plaintext, plaintext_internal);
    LOCAL_OUTPUT_FREE(ciphertext, ciphertext_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_encrypt_setup(psa_aead_operation_t *operation, mbedtls_svc_key_id_t key, psa_algorithm_t alg)
{
    return psa_aead_setup(operation, key, alg, AES_ENCRYPT);
}

psa_status_t psa_aead_finish(psa_aead_operation_t *operation,
                             uint8_t *ciphertext,
                             size_t ciphertext_size,
                             size_t *ciphertext_length,
                             uint8_t *tag,
                             size_t tag_size,
                             size_t *tag_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    LOCAL_OUTPUT_DECLARE(ciphertext, ciphertext_internal);
    LOCAL_OUTPUT_DECLARE(tag, tag_internal);
#endif

    if (isHardwareAeadOperation(operation))
    {
        return ti_psa_aead_finish(operation, ciphertext, ciphertext_size, ciphertext_length, tag, tag_size, tag_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_OUTPUT_ALLOC(ciphertext, ciphertext_size, ciphertext_internal);
        LOCAL_OUTPUT_ALLOC(tag, tag_size, tag_internal);

        *ciphertext_length = 0;
        *tag_length        = tag_size;

        status = psa_aead_final_checks(operation);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        if (!operation->MBEDTLS_PRIVATE(is_encrypt))
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        status = mbedtls_psa_aead_finish(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
                                         ciphertext_internal,
                                         ciphertext_size,
                                         ciphertext_length,
                                         tag_internal,
                                         tag_size,
                                         tag_length);
    }

exit:
    /* In case the operation fails and the user fails to check for failure or
     * the zero tag size, make sure the tag is set to something implausible.
     * Even if the operation succeeds, make sure we clear the rest of the
     * buffer to prevent potential leakage of anything previously placed in
     * the same buffer.*/
    psa_wipe_tag_output_buffer(tag_internal, status, tag_size, *tag_length);

    psa_aead_abort(operation);

    LOCAL_OUTPUT_FREE(ciphertext, ciphertext_internal);
    LOCAL_OUTPUT_FREE(tag, tag_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_generate_nonce(psa_aead_operation_t *operation,
                                     uint8_t *nonce,
                                     size_t nonce_size,
                                     size_t *nonce_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status                          = PSA_ERROR_CORRUPTION_DETECTED;
    uint8_t local_nonce[PSA_AEAD_NONCE_MAX_SIZE] = {0};
    size_t required_nonce_size                   = 0;

    LOCAL_OUTPUT_DECLARE(nonce, nonce_internal);
#endif

    if (isHardwareAeadOperation(operation))
    {
        return ti_psa_aead_generate_nonce(operation, nonce, nonce_size, nonce_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_OUTPUT_ALLOC(nonce, nonce_size, nonce_internal);

        *nonce_length = 0;

        if (operation->MBEDTLS_PRIVATE(id) == 0)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        if (operation->MBEDTLS_PRIVATE(nonce_set) || !operation->MBEDTLS_PRIVATE(is_encrypt))
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        /* For CCM, this size may not be correct according to the PSA
         * specification. The PSA Crypto 1.0.1 specification states:
         *
         * CCM encodes the plaintext length pLen in L octets, with L the smallest
         * integer >= 2 where pLen < 2^(8L). The nonce length is then 15 - L bytes.
         *
         * However this restriction that L has to be the smallest integer is not
         * applied in practice, and it is not implementable here since the
         * plaintext length may or may not be known at this time.
         */
        required_nonce_size = PSA_AEAD_NONCE_LENGTH(operation->MBEDTLS_PRIVATE(key_type),
                                                    operation->MBEDTLS_PRIVATE(alg));
        if (nonce_size < required_nonce_size)
        {
            status = PSA_ERROR_BUFFER_TOO_SMALL;
            goto exit;
        }

        status = psa_generate_random_internal(local_nonce, required_nonce_size);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        status = psa_aead_set_nonce(operation, local_nonce, required_nonce_size);
    }

exit:
    if (status == PSA_SUCCESS)
    {
        memcpy(nonce_internal, local_nonce, required_nonce_size);
        *nonce_length = required_nonce_size;
    }
    else
    {
        psa_aead_abort(operation);
    }

    LOCAL_OUTPUT_FREE(nonce, nonce_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_set_lengths(psa_aead_operation_t *operation, size_t ad_length, size_t plaintext_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
#endif

    if (isHardwareAeadOperation(operation))
    {
        return ti_psa_aead_set_lengths(operation, ad_length, plaintext_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        if (operation->MBEDTLS_PRIVATE(id) == 0)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        if (operation->MBEDTLS_PRIVATE(lengths_set) || operation->MBEDTLS_PRIVATE(ad_started) ||
            operation->MBEDTLS_PRIVATE(body_started))
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        switch (operation->MBEDTLS_PRIVATE(alg))
        {
    #if defined(PSA_WANT_ALG_GCM)
            case PSA_ALG_GCM:
                    /* Lengths can only be too large for GCM if size_t is bigger than 32
                     * bits. Without the guard this code will generate warnings on 32bit
                     * builds. */
        #if SIZE_MAX > UINT32_MAX
                if (((uint64_t)ad_length) >> 61 != 0 || ((uint64_t)plaintext_length) > 0xFFFFFFFE0ull)
                {
                    status = PSA_ERROR_INVALID_ARGUMENT;
                    goto exit;
                }
        #endif
                break;
    #endif /* PSA_WANT_ALG_GCM */
    #if defined(PSA_WANT_ALG_CCM)
            case PSA_ALG_CCM:
                if (ad_length > 0xFF00)
                {
                    status = PSA_ERROR_INVALID_ARGUMENT;
                    goto exit;
                }
                break;
    #endif /* PSA_WANT_ALG_CCM */
    #if defined(PSA_WANT_ALG_CHACHA20_POLY1305)
            case PSA_ALG_CHACHA20_POLY1305:
                /* No length restrictions for ChaChaPoly. */
                break;
    #endif /* PSA_WANT_ALG_CHACHA20_POLY1305 */
            default:
                break;
        }

        status = mbedtls_psa_aead_set_lengths(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
                                              ad_length,
                                              plaintext_length);
    }

exit:
    if (status == PSA_SUCCESS)
    {
        operation->MBEDTLS_PRIVATE(ad_remaining)   = ad_length;
        operation->MBEDTLS_PRIVATE(body_remaining) = plaintext_length;
        operation->MBEDTLS_PRIVATE(lengths_set)    = 1;
    }
    else
    {
        psa_aead_abort(operation);
    }

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_set_nonce(psa_aead_operation_t *operation, const uint8_t *nonce, size_t nonce_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status;

    LOCAL_INPUT_DECLARE(nonce, nonce_internal);
#endif

    if (isHardwareAeadOperation(operation))
    {
        return ti_psa_aead_set_nonce(operation, nonce, nonce_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_INPUT_ALLOC(nonce, nonce_length, nonce_internal);

        if (operation->MBEDTLS_PRIVATE(id) == 0)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        if (operation->MBEDTLS_PRIVATE(nonce_set))
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        status = psa_aead_check_nonce_length(operation->MBEDTLS_PRIVATE(alg), nonce_length);
        if (status != PSA_SUCCESS)
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            goto exit;
        }

        status = mbedtls_psa_aead_set_nonce(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx, nonce_internal, nonce_length);
    }

    /* Exit label is only needed for buffer copying, prevent unused warnings. */
    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
    if (status == PSA_SUCCESS)
    {
        operation->MBEDTLS_PRIVATE(nonce_set) = 1;
    }
    else
    {
        psa_aead_abort(operation);
    }

    LOCAL_INPUT_FREE(nonce, nonce_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_update(psa_aead_operation_t *operation,
                             const uint8_t *input,
                             size_t input_length,
                             uint8_t *output,
                             size_t output_size,
                             size_t *output_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    LOCAL_INPUT_DECLARE(input, input_internal);
    LOCAL_OUTPUT_DECLARE(output, output_internal);
#endif

    if (isHardwareAeadOperation(operation))
    {
        return ti_psa_aead_update(operation, input, input_length, output, output_size, output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_INPUT_ALLOC(input, input_length, input_internal);
        LOCAL_OUTPUT_ALLOC(output, output_size, output_internal);

        *output_length = 0;

        if (operation->MBEDTLS_PRIVATE(id) == 0)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        if (!operation->MBEDTLS_PRIVATE(nonce_set))
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        if (operation->MBEDTLS_PRIVATE(lengths_set))
        {
            /* Additional data length was supplied, but not all the additional
            data was supplied.*/
            if (operation->MBEDTLS_PRIVATE(ad_remaining) != 0)
            {
                status = PSA_ERROR_INVALID_ARGUMENT;
                goto exit;
            }

            /* Too much data provided. */
            if (operation->MBEDTLS_PRIVATE(body_remaining) < input_length)
            {
                status = PSA_ERROR_INVALID_ARGUMENT;
                goto exit;
            }

            operation->MBEDTLS_PRIVATE(body_remaining) -= input_length;
        }
    #if defined(PSA_WANT_ALG_CCM)
        else if (operation->MBEDTLS_PRIVATE(alg) == PSA_ALG_CCM)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }
    #endif /* PSA_WANT_ALG_CCM */

        status = mbedtls_psa_aead_update(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
                                         input_internal,
                                         input_length,
                                         output_internal,
                                         output_size,
                                         output_length);
    }

exit:
    if (status == PSA_SUCCESS)
    {
        operation->MBEDTLS_PRIVATE(body_started) = 1;
    }
    else
    {
        psa_aead_abort(operation);
    }

    LOCAL_INPUT_FREE(input, input_internal);
    LOCAL_OUTPUT_FREE(output, output_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_update_ad(psa_aead_operation_t *operation, const uint8_t *input, size_t input_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    LOCAL_INPUT_DECLARE(input, input_internal);
#endif

    if (isHardwareAeadOperation(operation))
    {
        return ti_psa_aead_update_ad(operation, input, input_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_INPUT_ALLOC(input, input_length, input_internal);

        if (operation->MBEDTLS_PRIVATE(id) == 0)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        if (!operation->MBEDTLS_PRIVATE(nonce_set) || operation->MBEDTLS_PRIVATE(body_started))
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        /* No input to add (zero length), nothing to do. */
        if (input_length == 0)
        {
            status = PSA_SUCCESS;
            goto exit;
        }

        if (operation->MBEDTLS_PRIVATE(lengths_set))
        {
            if (operation->MBEDTLS_PRIVATE(ad_remaining) < input_length)
            {
                status = PSA_ERROR_INVALID_ARGUMENT;
                goto exit;
            }

            operation->MBEDTLS_PRIVATE(ad_remaining) -= input_length;
        }
    #if defined(PSA_WANT_ALG_CCM)
        else if (operation->MBEDTLS_PRIVATE(alg) == PSA_ALG_CCM)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }
    #endif /* PSA_WANT_ALG_CCM */

        status = mbedtls_psa_aead_update_ad(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx, input_internal, input_length);
    }

exit:
    if (status == PSA_SUCCESS)
    {
        operation->MBEDTLS_PRIVATE(ad_started) = 1;
    }
    else
    {
        psa_aead_abort(operation);
    }

    LOCAL_INPUT_FREE(input, input_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_aead_verify(psa_aead_operation_t *operation,
                             uint8_t *plaintext,
                             size_t plaintext_size,
                             size_t *plaintext_length,
                             const uint8_t *tag,
                             size_t tag_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    uint8_t check_tag[PSA_AEAD_TAG_MAX_SIZE];
    size_t check_tag_length;

    LOCAL_OUTPUT_DECLARE(plaintext, plaintext_internal);
    LOCAL_INPUT_DECLARE(tag, tag_internal);
#endif

    if (isHardwareAeadOperation(operation))
    {
        return ti_psa_aead_verify(operation, plaintext, plaintext_size, plaintext_length, tag, tag_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_OUTPUT_ALLOC(plaintext, plaintext_size, plaintext_internal);
        LOCAL_INPUT_ALLOC(tag, tag_length, tag_internal);

        *plaintext_length = 0;

        status = psa_aead_final_checks(operation);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        if (operation->MBEDTLS_PRIVATE(is_encrypt))
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        status = mbedtls_psa_aead_finish(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
                                         plaintext_internal,
                                         plaintext_size,
                                         plaintext_length,
                                         check_tag,
                                         sizeof(check_tag),
                                         &check_tag_length);

        if (status == PSA_SUCCESS)
        {
            if ((tag_length != check_tag_length) || mbedtls_ct_memcmp(tag_internal, check_tag, tag_length) != 0)
            {
                status = PSA_ERROR_INVALID_SIGNATURE;
            }
        }

        mbedtls_platform_zeroize(check_tag, sizeof(check_tag));
    }

exit:
    psa_aead_abort(operation);

    LOCAL_OUTPUT_FREE(plaintext, plaintext_internal);
    LOCAL_INPUT_FREE(tag, tag_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

/****************************************************************/
/* Message digests */
/****************************************************************/
psa_status_t psa_hash_abort(psa_hash_operation_t *operation)
{
    psa_status_t status;

#if (TFM_ENABLED == 1)
    /* Note that this condition may need to be modified to support SW PSA
     * in TFM_ENABLED configurations.
     */
    if (operation->handle == TFM_CRYPTO_INVALID_HANDLE)
    {
        /* No operation in progress */
        return PSA_SUCCESS;
    }
#else
    /* On the S-side, the operation has an ID which identifies it as HW or SW.
     * If it is neither, we can successfully consider it 'aborted.'
     */
    if (operation->MBEDTLS_PRIVATE(id) == 0)
    {
        /* The object has (apparently) been initialized but it is not (yet)
         * in use. It's ok to call abort on such an object, and there's
         * nothing to do.
         */
        return PSA_SUCCESS;
    }
#endif

    if (isHardwareHashOperation(operation))
    {
        status = ti_psa_hash_abort(operation);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        status = mbedtls_psa_hash_abort(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx);
    }
#else
    else
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }
#endif /* TI_SW_CRYPTO_ENABLED */

    /* Reset the operation ID. Only for S-only builds, because TFM-enabled will handle
     * resetting the operation handle elsewhere.
     */
#if (TFM_ENABLED == 0)
    operation->MBEDTLS_PRIVATE(id) = 0;
#endif

    return status;
}

psa_status_t psa_hash_clone(const psa_hash_operation_t *source_operation, psa_hash_operation_t *target_operation)
{
    psa_status_t status = PSA_ERROR_NOT_SUPPORTED;
#if (TFM_ENABLED == 1)
    if ((source_operation->handle == TFM_CRYPTO_INVALID_HANDLE) ||
        (target_operation->handle != TFM_CRYPTO_INVALID_HANDLE))
    {
        /* Source operation is not valid or target operation is already in use */
        return PSA_ERROR_BAD_STATE;
    }
#else
    if ((source_operation->MBEDTLS_PRIVATE(id) == 0) || (target_operation->MBEDTLS_PRIVATE(id) != 0))
    {
        /* Source operation is not valid or target operation is already in use */
        return PSA_ERROR_BAD_STATE;
    }
#endif

    if (isHardwareHashOperation(source_operation))
    {
        setHashOperationID(target_operation, PSA_CRYPTO_TI_DRIVER_ID);
        status = ti_psa_hash_clone(source_operation, target_operation);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        setHashOperationID(target_operation, PSA_CRYPTO_MBED_TLS_DRIVER_ID);
        status = mbedtls_psa_hash_clone(&source_operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
                                        &target_operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx);
    }
#endif /* TI_SW_CRYPTO_ENABLED */

    if (status != PSA_SUCCESS)
    {
        (void)psa_hash_abort(target_operation);
    }

    return status;
}

psa_status_t psa_hash_compare(psa_algorithm_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              const uint8_t *hash,
                              size_t hash_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    uint8_t actual_hash[PSA_HASH_MAX_SIZE];
    size_t actual_hash_length;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    LOCAL_INPUT_DECLARE(input, input_internal);
    LOCAL_INPUT_DECLARE(hash, hash_internal);
#endif

    /* For one-shot operations, directly check the algorithm for HW acceleration support, because
     * there is no operation struct previously initialized.
     */
    if (isHardwareAccelerated(alg))
    {
        return ti_psa_hash_compare(alg, input, input_length, hash, hash_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        if (!PSA_ALG_IS_HASH(alg))
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            return status;
        }

        LOCAL_INPUT_ALLOC(input, input_length, input_internal);

        status = mbedtls_psa_hash_compute(alg,
                                          input_internal,
                                          input_length,
                                          actual_hash,
                                          sizeof(actual_hash),
                                          &actual_hash_length);

        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        if (actual_hash_length != hash_length)
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            goto exit;
        }

        LOCAL_INPUT_ALLOC(hash, hash_length, hash_internal);
        if (mbedtls_ct_memcmp(hash_internal, actual_hash, actual_hash_length) != 0)
        {
            status = PSA_ERROR_INVALID_SIGNATURE;
        }
    }
exit:
    mbedtls_platform_zeroize(actual_hash, sizeof(actual_hash));

    LOCAL_INPUT_FREE(input, input_internal);
    LOCAL_INPUT_FREE(hash, hash_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_hash_compute(psa_algorithm_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              uint8_t *hash,
                              size_t hash_size,
                              size_t *hash_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_INPUT_DECLARE(input, input_internal);
    LOCAL_OUTPUT_DECLARE(hash, hash_internal);
#endif

    /* For one-shot operations, directly check the algorithm for HW acceleration support, because
     * there is no operation struct previously initialized.
     */
    if (isHardwareAccelerated(alg))
    {
        return ti_psa_hash_compute(alg, input, input_length, hash, hash_size, hash_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        *hash_length = 0;
        if (!PSA_ALG_IS_HASH(alg))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        LOCAL_INPUT_ALLOC(input, input_length, input_internal);
        LOCAL_OUTPUT_ALLOC(hash, hash_size, hash_internal);

        status = mbedtls_psa_hash_compute(alg, input_internal, input_length, hash_internal, hash_size, hash_length);
    }
    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
    LOCAL_INPUT_FREE(input, input_internal);
    LOCAL_OUTPUT_FREE(hash, hash_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

static psa_status_t psa_hash_finish_internal(psa_hash_operation_t *operation,
                                             uint8_t *hash,
                                             size_t hash_size,
                                             size_t *hash_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    if (isHardwareHashOperation(operation))
    {
        status = ti_psa_hash_finish(operation, hash, hash_size, hash_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        *hash_length = 0;

        if (operation->MBEDTLS_PRIVATE(id) == 0)
        {
            return PSA_ERROR_BAD_STATE;
        }

        status = mbedtls_psa_hash_finish(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx, hash, hash_size, hash_length);
        psa_hash_abort(operation);
    }
#endif /* TI_SW_CRYPTO_ENABLED */
    return status;
}

psa_status_t psa_hash_finish(psa_hash_operation_t *operation, uint8_t *hash, size_t hash_size, size_t *hash_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_OUTPUT_DECLARE(hash, hash_internal);
#endif

    if (isHardwareHashOperation(operation))
    {
        return psa_hash_finish_internal(operation, hash, hash_size, hash_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_OUTPUT_ALLOC(hash, hash_size, hash_internal);

        status = psa_hash_finish_internal(operation, hash_internal, hash_size, hash_length);
    }

    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
    LOCAL_OUTPUT_FREE(hash, hash_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_hash_setup(psa_hash_operation_t *operation, psa_algorithm_t alg)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
#endif
    if (isHardwareAccelerated(alg))
    {
        /* Call hardware accelerated function - mark operation->MBEDTLS_PRIVATE(id) as HW-accelerated */
        setHashOperationID(operation, PSA_CRYPTO_TI_DRIVER_ID);

        return ti_psa_hash_setup(operation, alg);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* This parameter validation is only necessary in the SW path because the
         * ti_psa layer performs the same validation internally
         */
        if (operation->MBEDTLS_PRIVATE(id) != 0)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        if (!PSA_ALG_IS_HASH(alg))
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            goto exit;
        }

        /* Ensure all of the context is zeroized, since PSA_HASH_OPERATION_INIT only
         * directly zeroes the int-sized dummy member of the context union.
         */
        memset(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx, 0, sizeof(operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx));

        /* Mark SW implementation as active for this operation */
        setHashOperationID(operation, PSA_CRYPTO_MBED_TLS_DRIVER_ID);

        status = mbedtls_psa_hash_setup(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx, alg);
    }

exit:
    if (status != PSA_SUCCESS)
    {
        psa_hash_abort(operation);
    }

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_hash_update(psa_hash_operation_t *operation, const uint8_t *input, size_t input_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_INPUT_DECLARE(input, input_internal);
#endif

    if (isHardwareHashOperation(operation))
    {
        return ti_psa_hash_update(operation, input, input_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        if (operation->MBEDTLS_PRIVATE(id) == 0)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

        /* Don't require hash implementations to behave correctly on a
         * zero-length input, which may have an invalid pointer.
         */
        if (input_length == 0)
        {
            return PSA_SUCCESS;
        }

        LOCAL_INPUT_ALLOC(input, input_length, input_internal);
        status = mbedtls_psa_hash_update(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx, input_internal, input_length);
    }
exit:
    if (status != PSA_SUCCESS)
    {
        psa_hash_abort(operation);
    }

    LOCAL_INPUT_FREE(input, input_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_hash_verify(psa_hash_operation_t *operation, const uint8_t *hash, size_t hash_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    uint8_t actual_hash[PSA_HASH_MAX_SIZE];
    size_t actual_hash_length;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_INPUT_DECLARE(hash, hash_internal);
#endif

    if (isHardwareHashOperation(operation))
    {
        return ti_psa_hash_verify(operation, hash, hash_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        status = psa_hash_finish_internal(operation, actual_hash, sizeof(actual_hash), &actual_hash_length);

        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        if (actual_hash_length != hash_length)
        {
            status = PSA_ERROR_INVALID_SIGNATURE;
            goto exit;
        }

        LOCAL_INPUT_ALLOC(hash, hash_length, hash_internal);

        if (mbedtls_ct_memcmp(hash_internal, actual_hash, actual_hash_length) != 0)
        {
            status = PSA_ERROR_INVALID_SIGNATURE;
        }
    }

exit:
    mbedtls_platform_zeroize(actual_hash, sizeof(actual_hash));
    if (status != PSA_SUCCESS)
    {
        psa_hash_abort(operation);
    }
    LOCAL_INPUT_FREE(hash, hash_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

/****************************************************************/
/* MAC */
/****************************************************************/
psa_status_t psa_mac_abort(psa_mac_operation_t *operation)
{
#if (TFM_ENABLED == 1)
    /* Note that this condition may need to be modified to support SW PSA
     * in TFM_ENABLED configurations.
     */
    if (operation->handle == TFM_CRYPTO_INVALID_HANDLE)
    {
        /* No operation in progress */
        return PSA_SUCCESS;
    }
#else
    /* On the S-side, the operation has an ID which identifies it as HW or SW.
     * If it is neither, we can successfully consider it 'aborted.'
     */
    if (operation->MBEDTLS_PRIVATE(id) == 0)
    {
        /* The object has (apparently) been initialized but it is not (yet)
         * in use. It's ok to call abort on such an object, and there's
         * nothing to do.
         */
        return PSA_SUCCESS;
    }
#endif

    if (isHardwareMacOperation(operation))
    {
        return ti_psa_mac_abort(operation);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return mbedtls_psa_mac_abort(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx);
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_mac_compute(mbedtls_svc_key_id_t key,
                             psa_algorithm_t alg,
                             const uint8_t *input,
                             size_t input_length,
                             uint8_t *mac,
                             size_t mac_size,
                             size_t *mac_length)
{
    /* For one-shot operations, directly check the algorithm for HW acceleration support, because
     * there is no operation struct previously initialized.
     */
    if (isHardwareAccelerated(alg))
    {
        return ti_psa_mac_compute(key, alg, input, input_length, mac, mac_size, mac_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

static psa_status_t psa_mac_setup(psa_mac_operation_t *operation,
                                  mbedtls_svc_key_id_t key,
                                  psa_algorithm_t alg,
                                  bool is_sign)
{
    if (isHardwareAccelerated(alg))
    {
        /* Call hardware accelerated function - mark operation->MBEDTLS_PRIVATE(id) as HW-accelerated */
        setMacOperationID(operation, PSA_CRYPTO_TI_DRIVER_ID);

        if (is_sign)
        {
            /* Call hardware MAC sign setup */
            return ti_psa_mac_sign_setup(operation, key, alg);
        }
        else
        {
            /* Call hardware MAC verify setup */
            return ti_psa_mac_verify_setup(operation, key, alg);
        }
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* Call software implementation - retrieve key material & attributes first */
        setMacOperationID(operation, PSA_CRYPTO_MBED_TLS_DRIVER_ID);

        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_mac_sign_finish(psa_mac_operation_t *operation, uint8_t *mac, size_t mac_size, size_t *mac_length)
{
    if (isHardwareMacOperation(operation))
    {
        return ti_psa_mac_sign_finish(operation, mac, mac_size, mac_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return mbedtls_psa_mac_sign_finish(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx, mac, mac_size, mac_length);
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_mac_sign_setup(psa_mac_operation_t *operation, mbedtls_svc_key_id_t key, psa_algorithm_t alg)
{
    return psa_mac_setup(operation, key, alg, true);
}

psa_status_t psa_mac_update(psa_mac_operation_t *operation, const uint8_t *input, size_t input_length)
{
    if (isHardwareMacOperation(operation))
    {
        return ti_psa_mac_update(operation, input, input_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* This path is supported in the context of HKDF, where SW HMAC is used */
        return mbedtls_psa_mac_update(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx, input, input_length);
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_mac_verify(mbedtls_svc_key_id_t key,
                            psa_algorithm_t alg,
                            const uint8_t *input,
                            size_t input_length,
                            const uint8_t *mac,
                            size_t mac_length)
{
    if (isHardwareAccelerated(alg))
    {
        /* Call hardware accelerated function */
        return ti_psa_mac_verify(key, alg, input, input_length, mac, mac_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* Call software implementation - retrieve key material & attributes first */
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_mac_verify_finish(psa_mac_operation_t *operation, const uint8_t *mac, size_t mac_length)
{
    if (isHardwareMacOperation(operation))
    {
        return ti_psa_mac_verify_finish(operation, mac, mac_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
        // return mbedtls_psa_mac_verify_finish(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
        //                                     mac, mac_length);
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_mac_verify_setup(psa_mac_operation_t *operation, mbedtls_svc_key_id_t key, psa_algorithm_t alg)
{
    return psa_mac_setup(operation, key, alg, false);
}

/****************************************************************/
/* Key agreement */
/****************************************************************/
#if (TI_SW_CRYPTO_ENABLED == 1)
static psa_status_t psa_key_agreement_raw_internal(psa_algorithm_t alg,
                                                   psa_key_context_t *private_key,
                                                   const uint8_t *peer_key,
                                                   size_t peer_key_length,
                                                   uint8_t *shared_secret,
                                                   size_t shared_secret_size,
                                                   size_t *shared_secret_length)
{
    if (!PSA_ALG_IS_RAW_KEY_AGREEMENT(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Only include FFDH as an option, since we HW accelerate ECDH */
    switch (alg)
    {
    #if defined(MBEDTLS_PSA_BUILTIN_ALG_FFDH)
        case PSA_ALG_FFDH:
            return mbedtls_psa_ffdh_key_agreement((const psa_key_attributes_t *)&private_key->attributes,
                                                  peer_key,
                                                  peer_key_length,
                                                  private_key->key,
                                                  private_key->key_size,
                                                  shared_secret,
                                                  shared_secret_size,
                                                  shared_secret_length);
    #endif /* MBEDTLS_PSA_BUILTIN_ALG_FFDH */

        default:
            (void)alg;
            (void)private_key;
            (void)peer_key;
            (void)peer_key_length;
            (void)shared_secret;
            (void)shared_secret_size;
            (void)shared_secret_length;
            return PSA_ERROR_NOT_SUPPORTED;
    }
}
#endif

psa_status_t psa_raw_key_agreement(psa_algorithm_t alg,
                                   mbedtls_svc_key_id_t private_key,
                                   const uint8_t *peer_key,
                                   size_t peer_key_length,
                                   uint8_t *output,
                                   size_t output_size,
                                   size_t *output_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status     = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_context_t *slot = NULL;
    size_t expected_length;
    LOCAL_INPUT_DECLARE(peer_key, peer_key_internal);
    LOCAL_OUTPUT_DECLARE(output, output_internal);
#endif

    if (isHardwareAccelerated(alg))
    {
        return ti_psa_raw_key_agreement(alg,
                                        private_key,
                                        peer_key,
                                        peer_key_length,
                                        output,
                                        output_size,
                                        output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_OUTPUT_ALLOC(output, output_size, output_internal);

        if (!PSA_ALG_IS_KEY_AGREEMENT(alg))
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            goto exit;
        }

        /* Retrieve the specified key into its slot. This also loads
         * the key material and the key attributes into the slot.
         */
        status = psaInt_KeyMgmtGetKey(private_key, &slot);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        /* PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE() is in general an upper bound
         * for the output size. The PSA specification only guarantees that this
         * function works if output_size >= PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE(...),
         * but it might be nice to allow smaller buffers if the output fits.
         * At the time of writing this comment, with only ECDH implemented,
         * PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE() is exact so the point is moot.
         * If FFDH is implemented, PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE() can easily
         * be exact for it as well.
         */
        expected_length = PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE(slot->attributes.MBEDTLS_PRIVATE(type),
                                                            slot->attributes.MBEDTLS_PRIVATE(bits));
        if (output_size < expected_length)
        {
            status = PSA_ERROR_BUFFER_TOO_SMALL;
            goto exit;
        }

        LOCAL_INPUT_ALLOC(peer_key, peer_key_length, peer_key_internal);
        status = psa_key_agreement_raw_internal(alg,
                                                slot,
                                                peer_key_internal,
                                                peer_key_length,
                                                output_internal,
                                                output_size,
                                                output_length);
    }

exit:
    /* Check for successful allocation of output,
     * with an unsuccessful status. */
    if ((output_internal != NULL) && (status != PSA_SUCCESS))
    {
        /* If an error happens and is not handled properly, the output
         * may be used as a key to protect sensitive data. Arrange for such
         * a key to be random, which is likely to result in decryption or
         * verification errors. This is better than filling the buffer with
         * some constant data such as zeros, which would result in the data
         * being protected with a reproducible, easily knowable key.
         */
        psa_generate_random_internal(output_internal, output_size);
        *output_length = output_size;
    }

    if (output_internal == NULL)
    {
        /* output allocation failed. */
        *output_length = 0;
    }

    LOCAL_INPUT_FREE(peer_key, peer_key_internal);
    LOCAL_OUTPUT_FREE(output, output_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

/****************************************************************/
/* Asymmetric cryptography */
/****************************************************************/
psa_status_t psa_asymmetric_encrypt(mbedtls_svc_key_id_t key,
                                    psa_algorithm_t alg,
                                    const uint8_t *input,
                                    size_t input_length,
                                    const uint8_t *salt,
                                    size_t salt_length,
                                    uint8_t *output,
                                    size_t output_size,
                                    size_t *output_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status;
    psa_key_context_t *slot;

    LOCAL_INPUT_DECLARE(input, input_internal);
    LOCAL_INPUT_DECLARE(salt, salt_internal);
    LOCAL_OUTPUT_DECLARE(output, output_internal);
#endif

    if (isHardwareAccelerated(alg))
    {
        return ti_psa_asymmetric_encrypt(key,
                                         alg,
                                         input,
                                         input_length,
                                         salt,
                                         salt_length,
                                         output,
                                         output_size,
                                         output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* SW implementation */
        *output_length = 0;

        if (!PSA_ALG_IS_RSA_OAEP(alg) && salt_length != 0)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        /* Retrieve the specified key into its slot. This also loads
         * the key material and the key attributes into the slot.
         */
        status = psaInt_KeyMgmtGetKey(key, &slot);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        if (!(PSA_KEY_TYPE_IS_PUBLIC_KEY(slot->attributes.MBEDTLS_PRIVATE(type)) ||
              PSA_KEY_TYPE_IS_KEY_PAIR(slot->attributes.MBEDTLS_PRIVATE(type))))
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            goto exit;
        }

        LOCAL_INPUT_ALLOC(input, input_length, input_internal);
        LOCAL_INPUT_ALLOC(salt, salt_length, salt_internal);
        LOCAL_OUTPUT_ALLOC(output, output_size, output_internal);

        status = mbedtls_psa_asymmetric_encrypt(&slot->attributes,
                                                slot->key,
                                                slot->key_size,
                                                alg,
                                                input_internal,
                                                input_length,
                                                salt_internal,
                                                salt_length,
                                                output_internal,
                                                output_size,
                                                output_length);
    }

exit:
    LOCAL_INPUT_FREE(input, input_internal);
    LOCAL_INPUT_FREE(salt, salt_internal);
    LOCAL_OUTPUT_FREE(output, output_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_asymmetric_decrypt(mbedtls_svc_key_id_t key,
                                    psa_algorithm_t alg,
                                    const uint8_t *input,
                                    size_t input_length,
                                    const uint8_t *salt,
                                    size_t salt_length,
                                    uint8_t *output,
                                    size_t output_size,
                                    size_t *output_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status;
    psa_key_context_t *slot;

    LOCAL_INPUT_DECLARE(input, input_internal);
    LOCAL_INPUT_DECLARE(salt, salt_internal);
    LOCAL_OUTPUT_DECLARE(output, output_internal);
#endif

    if (isHardwareAccelerated(alg))
    {
        return ti_psa_asymmetric_decrypt(key,
                                         alg,
                                         input,
                                         input_length,
                                         salt,
                                         salt_length,
                                         output,
                                         output_size,
                                         output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* SW implementation */
        *output_length = 0;

        if (!PSA_ALG_IS_RSA_OAEP(alg) && salt_length != 0)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        /* Retrieve the specified key into its slot. This also loads
         * the key material and the key attributes into the slot.
         */
        status = psaInt_KeyMgmtGetKey(key, &slot);
        if (status != PSA_SUCCESS)
        {
            goto exit;
        }

        if (!PSA_KEY_TYPE_IS_KEY_PAIR(slot->attributes.MBEDTLS_PRIVATE(type)))
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            goto exit;
        }

        LOCAL_INPUT_ALLOC(input, input_length, input_internal);
        LOCAL_INPUT_ALLOC(salt, salt_length, salt_internal);
        LOCAL_OUTPUT_ALLOC(output, output_size, output_internal);

        status = mbedtls_psa_asymmetric_decrypt(&slot->attributes,
                                                slot->key,
                                                slot->key_size,
                                                alg,
                                                input_internal,
                                                input_length,
                                                salt_internal,
                                                salt_length,
                                                output_internal,
                                                output_size,
                                                output_length);
    }

exit:
    LOCAL_INPUT_FREE(input, input_internal);
    LOCAL_INPUT_FREE(salt, salt_internal);
    LOCAL_OUTPUT_FREE(output, output_internal);

    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

#if (TI_SW_CRYPTO_ENABLED == 1)
static void psa_wipe_tag_output_buffer(uint8_t *output_buffer,
                                       psa_status_t status,
                                       size_t output_buffer_size,
                                       size_t output_buffer_length)
{
    /* Unchanged from psa_crypto.c implementation. Called only
     * in SW path.
     */
    size_t offset = 0;

    if (output_buffer_size == 0)
    {
        /* If output_buffer_size is 0 then we have nothing to do. We must not
           call memset because output_buffer may be NULL in this case */
        return;
    }

    if (status == PSA_SUCCESS)
    {
        offset = output_buffer_length;
    }

    memset(output_buffer + offset, '!', output_buffer_size - offset);
}

static int is_hash_supported(psa_algorithm_t alg)
{
    switch (alg)
    {
    #if defined(PSA_WANT_ALG_MD5)
        case PSA_ALG_MD5:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_RIPEMD160)
        case PSA_ALG_RIPEMD160:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA_1)
        case PSA_ALG_SHA_1:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA_224)
        case PSA_ALG_SHA_224:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA_256)
        case PSA_ALG_SHA_256:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA_384)
        case PSA_ALG_SHA_384:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA_512)
        case PSA_ALG_SHA_512:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA3_224)
        case PSA_ALG_SHA3_224:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA3_256)
        case PSA_ALG_SHA3_256:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA3_384)
        case PSA_ALG_SHA3_384:
            return 1;
    #endif
    #if defined(PSA_WANT_ALG_SHA3_512)
        case PSA_ALG_SHA3_512:
            return 1;
    #endif
        default:
            return 0;
    }
}

static psa_status_t psa_sign_verify_check_alg(int input_is_message, psa_algorithm_t alg)
{
    /* Unchanged from psa_crypto.c implementation. Called only
     * in SW path.
     */
    if (input_is_message)
    {
        if (!PSA_ALG_IS_SIGN_MESSAGE(alg))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    psa_algorithm_t hash_alg = 0;
    if (PSA_ALG_IS_SIGN_HASH(alg))
    {
        hash_alg = PSA_ALG_SIGN_GET_HASH(alg);
    }

    /* Now hash_alg==0 if alg by itself doesn't need a hash.
     * This is good enough for sign-hash, but a guaranteed failure for
     * sign-message which needs to hash first for all algorithms
     * supported at the moment. */

    if (hash_alg == 0 && input_is_message)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (hash_alg == PSA_ALG_ANY_HASH)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    /* Give up immediately if the hash is not supported. This has
     * several advantages:
     * - For mechanisms that don't use the hash at all (e.g.
     *   ECDSA verification, randomized ECDSA signature), without
     *   this check, the operation would succeed even though it has
     *   been given an invalid argument. This would not be insecure
     *   since the hash was not necessary, but it would be weird.
     * - For mechanisms that do use the hash, we avoid an error
     *   deep inside the execution. In principle this doesn't matter,
     *   but there is a little more risk of a bug in error handling
     *   deep inside than in this preliminary check.
     * - When calling a driver, the driver might be capable of using
     *   a hash that the core doesn't support. This could potentially
     *   result in a buffer overflow if the hash is larger than the
     *   maximum hash size assumed by the core.
     * - Returning a consistent error makes it possible to test
     *   not-supported hashes in a consistent way.
     */
    if (hash_alg != 0 && !is_hash_supported(hash_alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_SUCCESS;
}

static psa_status_t psa_sign_hash_builtin(const psa_key_attributes_t *attributes,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg,
                                          const uint8_t *hash,
                                          size_t hash_length,
                                          uint8_t *signature,
                                          size_t signature_size,
                                          size_t *signature_length)
{
    if (attributes->MBEDTLS_PRIVATE(type) == PSA_KEY_TYPE_RSA_KEY_PAIR)
    {
        if (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))
        {
    #if defined(MBEDTLS_PSA_BUILTIN_ALG_RSA_PKCS1V15_SIGN) || defined(MBEDTLS_PSA_BUILTIN_ALG_RSA_PSS)
            return mbedtls_psa_rsa_sign_hash(attributes,
                                             key_buffer,
                                             key_buffer_size,
                                             alg,
                                             hash,
                                             hash_length,
                                             signature,
                                             signature_size,
                                             signature_length);
    #endif /* defined(MBEDTLS_PSA_BUILTIN_ALG_RSA_PKCS1V15_SIGN) || \
            * defined(MBEDTLS_PSA_BUILTIN_ALG_RSA_PSS) */
        }
        else
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else if (PSA_KEY_TYPE_IS_ECC(attributes->MBEDTLS_PRIVATE(type)))
    {
        if (PSA_ALG_IS_ECDSA(alg))
        {
    #if defined(MBEDTLS_PSA_BUILTIN_ALG_ECDSA) || defined(MBEDTLS_PSA_BUILTIN_ALG_DETERMINISTIC_ECDSA)
            return mbedtls_psa_ecdsa_sign_hash(attributes,
                                               key_buffer,
                                               key_buffer_size,
                                               alg,
                                               hash,
                                               hash_length,
                                               signature,
                                               signature_size,
                                               signature_length);
    #endif /* defined(MBEDTLS_PSA_BUILTIN_ALG_ECDSA) || \
            * defined(MBEDTLS_PSA_BUILTIN_ALG_DETERMINISTIC_ECDSA) */
        }
        else
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    (void)key_buffer;
    (void)key_buffer_size;
    (void)hash;
    (void)hash_length;
    (void)signature;
    (void)signature_size;
    (void)signature_length;

    return PSA_ERROR_NOT_SUPPORTED;
}

static psa_status_t psa_verify_hash_builtin(const psa_key_attributes_t *attributes,
                                            const uint8_t *key_buffer,
                                            size_t key_buffer_size,
                                            psa_algorithm_t alg,
                                            const uint8_t *hash,
                                            size_t hash_length,
                                            const uint8_t *signature,
                                            size_t signature_length)
{
    if (PSA_KEY_TYPE_IS_RSA(attributes->MBEDTLS_PRIVATE(type)))
    {
        if (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))
        {
    #if defined(MBEDTLS_PSA_BUILTIN_ALG_RSA_PKCS1V15_SIGN) || defined(MBEDTLS_PSA_BUILTIN_ALG_RSA_PSS)
            return mbedtls_psa_rsa_verify_hash(attributes,
                                               key_buffer,
                                               key_buffer_size,
                                               alg,
                                               hash,
                                               hash_length,
                                               signature,
                                               signature_length);
    #endif /* defined(MBEDTLS_PSA_BUILTIN_ALG_RSA_PKCS1V15_SIGN) || \
            * defined(MBEDTLS_PSA_BUILTIN_ALG_RSA_PSS) */
        }
        else
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else if (PSA_KEY_TYPE_IS_ECC(attributes->MBEDTLS_PRIVATE(type)))
    {
        if (PSA_ALG_IS_ECDSA(alg))
        {
    #if defined(MBEDTLS_PSA_BUILTIN_ALG_ECDSA) || defined(MBEDTLS_PSA_BUILTIN_ALG_DETERMINISTIC_ECDSA)
            return mbedtls_psa_ecdsa_verify_hash(attributes,
                                                 key_buffer,
                                                 key_buffer_size,
                                                 alg,
                                                 hash,
                                                 hash_length,
                                                 signature,
                                                 signature_length);
    #endif /* defined(MBEDTLS_PSA_BUILTIN_ALG_ECDSA) || \
            * defined(MBEDTLS_PSA_BUILTIN_ALG_DETERMINISTIC_ECDSA) */
        }
        else
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    (void)key_buffer;
    (void)key_buffer_size;
    (void)hash;
    (void)hash_length;
    (void)signature;
    (void)signature_length;

    return PSA_ERROR_NOT_SUPPORTED;
}

static psa_status_t psa_sign_verify_internal(mbedtls_svc_key_id_t key,
                                             bool is_sign,
                                             bool input_is_message,
                                             psa_algorithm_t alg,
                                             const uint8_t *input,
                                             size_t input_length,
                                             const uint8_t *signatureInput,
                                             uint8_t *signatureOutput,
                                             size_t signature_size,
                                             size_t *signature_length)
{
    psa_status_t status;
    psa_key_context_t *slot;
    size_t hash_length;
    uint8_t hash[PSA_HASH_MAX_SIZE];

    if (is_sign)
    {
        *signature_length = 0;
    }

    status = psa_sign_verify_check_alg(input_is_message, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Immediately reject a zero-length signature buffer. This guarantees
     * that signature must be a valid pointer. (On the other hand, the input
     * buffer can in principle be empty since it doesn't actually have
     * to be a hash.) */
    if (is_sign && (signature_size == 0))
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Retrieve the specified key into its slot. This also loads
     * the key material and the key attributes into the slot.
     */
    status = psaInt_KeyMgmtGetKey(key, &slot);
    if (status != PSA_SUCCESS)
    {
        goto exit;
    }

    if (is_sign)
    {
        if (!PSA_KEY_TYPE_IS_KEY_PAIR(slot->attributes.MBEDTLS_PRIVATE(type)))
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
            goto exit;
        }

        if (input_is_message)
        {
            if (PSA_ALG_IS_SIGN_HASH(alg))
            {
                status = psa_hash_compute(PSA_ALG_SIGN_GET_HASH(alg),
                                          input,
                                          input_length,
                                          hash,
                                          sizeof(hash),
                                          &hash_length);

                if (status != PSA_SUCCESS)
                {
                    goto exit;
                }

                status = psa_sign_hash_builtin(&slot->attributes,
                                               slot->key,
                                               slot->key_size,
                                               alg,
                                               hash,
                                               hash_length,
                                               signatureOutput,
                                               signature_size,
                                               signature_length);
            }
            else
            {
                status = PSA_ERROR_NOT_SUPPORTED;
            }
        }
        else
        {
            status = psa_sign_hash_builtin(&slot->attributes,
                                           slot->key,
                                           slot->key_size,
                                           alg,
                                           input,
                                           input_length,
                                           signatureOutput,
                                           signature_size,
                                           signature_length);
        }
    }
    else
    {
        if (input_is_message)
        {
            if (PSA_ALG_IS_SIGN_HASH(alg))
            {
                status = psa_hash_compute(PSA_ALG_SIGN_GET_HASH(alg),
                                          input,
                                          input_length,
                                          hash,
                                          sizeof(hash),
                                          &hash_length);

                if (status != PSA_SUCCESS)
                {
                    goto exit;
                }

                status = psa_verify_hash_builtin(&slot->attributes,
                                                 slot->key,
                                                 slot->key_size,
                                                 alg,
                                                 hash,
                                                 hash_length,
                                                 signatureInput,
                                                 *signature_length);
            }
            else
            {
                status = PSA_ERROR_NOT_SUPPORTED;
            }
        }
        else
        {
            status = psa_verify_hash_builtin(&slot->attributes,
                                             slot->key,
                                             slot->key_size,
                                             alg,
                                             input,
                                             input_length,
                                             signatureInput,
                                             *signature_length);
        }
    }

exit:
    psa_wipe_tag_output_buffer(signatureOutput, status, signature_size, *signature_length);

    return status;
}
#endif /* TI_SW_CRYPTO_ENABLED */

psa_status_t psa_sign_hash(mbedtls_svc_key_id_t key,
                           psa_algorithm_t alg,
                           const uint8_t *hash,
                           size_t hash_length,
                           uint8_t *signature,
                           size_t signature_size,
                           size_t *signature_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_INPUT_DECLARE(hash, hash_internal);
    LOCAL_OUTPUT_DECLARE(signature, signature_internal);
#endif

    if (isHardwareAccelerated(alg))
    {
        return ti_psa_sign_hash(key, alg, hash, hash_length, signature, signature_size, signature_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* SW implementation */
        LOCAL_INPUT_ALLOC(hash, hash_length, hash_internal);
        LOCAL_OUTPUT_ALLOC(signature, signature_size, signature_internal);

        status = psa_sign_verify_internal(key,
                                          1,
                                          0,
                                          alg,
                                          hash_internal,
                                          hash_length,
                                          NULL,
                                          signature_internal,
                                          signature_size,
                                          signature_length);
    }
    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
    LOCAL_INPUT_FREE(hash, hash_internal);
    LOCAL_OUTPUT_FREE(signature, signature_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_sign_message(mbedtls_svc_key_id_t key,
                              psa_algorithm_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              uint8_t *signature,
                              size_t signature_size,
                              size_t *signature_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_INPUT_DECLARE(input, input_internal);
    LOCAL_OUTPUT_DECLARE(signature, signature_internal);
#endif

    if (isHardwareAccelerated(alg))
    {
        return ti_psa_sign_message(key, alg, input, input_length, signature, signature_size, signature_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* SW implementation */
        LOCAL_INPUT_ALLOC(input, input_length, input_internal);
        LOCAL_OUTPUT_ALLOC(signature, signature_size, signature_internal);

        status = psa_sign_verify_internal(key,
                                          1,
                                          1,
                                          alg,
                                          input_internal,
                                          input_length,
                                          NULL,
                                          signature_internal,
                                          signature_size,
                                          signature_length);
    }
    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
    LOCAL_INPUT_FREE(input, input_internal);
    LOCAL_OUTPUT_FREE(signature, signature_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_verify_hash(mbedtls_svc_key_id_t key,
                             psa_algorithm_t alg,
                             const uint8_t *hash,
                             size_t hash_length,
                             const uint8_t *signature,
                             size_t signature_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_INPUT_DECLARE(hash, hash_internal);
    LOCAL_INPUT_DECLARE(signature, signature_internal);
#endif

    if (isHardwareAccelerated(alg))
    {
        return ti_psa_verify_hash(key, alg, hash, hash_length, signature, signature_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_INPUT_ALLOC(hash, hash_length, hash_internal);
        LOCAL_INPUT_ALLOC(signature, signature_length, signature_internal);
        /* 0 for is_sign, 0 for input_is_message */
        status = psa_sign_verify_internal(key,
                                          0,
                                          0,
                                          alg,
                                          hash_internal,
                                          hash_length,
                                          signature_internal,
                                          NULL,
                                          0,
                                          &signature_length);
    }
    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
    LOCAL_INPUT_FREE(hash, hash_internal);
    LOCAL_INPUT_FREE(signature, signature_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_verify_message(mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                const uint8_t *signature,
                                size_t signature_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_INPUT_DECLARE(input, input_internal);
    LOCAL_INPUT_DECLARE(signature, signature_internal);
#endif

    if (isHardwareAccelerated(alg))
    {
        return ti_psa_verify_message(key, alg, input, input_length, signature, signature_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_INPUT_ALLOC(input, input_length, input_internal);
        LOCAL_INPUT_ALLOC(signature, signature_length, signature_internal);
        /* 0 for is_sign, 1 for input_is_message */
        status = psa_sign_verify_internal(key,
                                          0,
                                          1,
                                          alg,
                                          input_internal,
                                          input_length,
                                          signature_internal,
                                          NULL,
                                          0,
                                          &signature_length);
    }
    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
    LOCAL_INPUT_FREE(input, input_internal);
    LOCAL_INPUT_FREE(signature, signature_internal);
    return status;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

/******************************************************************************/
/* Key derivation */
/******************************************************************************/
/* Note that the code for the SW path of key derivation (used only for HKDF currently)
 * is copied from psa_crypto.c. Also note that the ti_psa_key_derivation_xxx() layer is
 * passed the psa_key_derivation_operation_t structure directly, because the underlying
 * TI context is not needed until the DDK is called for HW-accelerated key derivation.
 * Therefore, the ti_psa_crypto layer can pass down the ti_ctx instead of us doing it here.
 */
psa_status_t psa_key_derivation_abort(psa_key_derivation_operation_t *operation)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status;
#endif

#if (TFM_ENABLED == 1)
    /* Note that this condition may need to be modified to support SW PSA
     * in TFM_ENABLED configurations.
     */
    if (operation->handle == TFM_CRYPTO_INVALID_HANDLE)
    {
        /* No operation in progress */
        return PSA_SUCCESS;
    }
#else
    /* On the S-side, the operation has an ID which identifies it as HW or SW.
     * If it is neither, we can successfully consider it 'aborted.'
     */
    if (operation->MBEDTLS_PRIVATE(id) == 0)
    {
        /* The object has (apparently) been initialized but it is not (yet)
         * in use. It's ok to call abort on such an object, and there's
         * nothing to do.
         */
        return PSA_SUCCESS;
    }
#endif

    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_abort(operation);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
    #if defined(BUILTIN_ALG_ANY_HKDF)
        if (PSA_ALG_IS_ANY_HKDF(operation->MBEDTLS_PRIVATE(alg)))
        {
            mbedtls_free(operation->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(hkdf).MBEDTLS_PRIVATE(info));
            status = psa_mac_abort(&operation->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(hkdf).MBEDTLS_PRIVATE(hmac));
            mbedtls_platform_zeroize(operation, sizeof(*operation));
            return status;
        }
        else
    #endif
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_get_capacity(const psa_key_derivation_operation_t *operation, size_t *capacity)
{
    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_get_capacity(operation, capacity);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        if (operation->MBEDTLS_PRIVATE(alg) == 0)
        {
            return PSA_ERROR_BAD_STATE;
        }

        *capacity = operation->MBEDTLS_PRIVATE(capacity);
        return PSA_SUCCESS;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_set_capacity(psa_key_derivation_operation_t *operation, size_t capacity)
{
    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_set_capacity(operation, capacity);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        if (operation->MBEDTLS_PRIVATE(alg) == 0)
        {
            return PSA_ERROR_BAD_STATE;
        }

        operation->MBEDTLS_PRIVATE(capacity) = capacity;
        return PSA_SUCCESS;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

#if (TI_SW_CRYPTO_ENABLED == 1)
    #if defined(BUILTIN_ALG_ANY_HKDF)
static psa_status_t psa_key_derivation_start_hmac(psa_mac_operation_t *operation,
                                                  psa_algorithm_t hash_alg,
                                                  const uint8_t *hmac_key,
                                                  size_t hmac_key_length)
{
    psa_status_t status             = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_set_key_type(&attributes, PSA_KEY_TYPE_HMAC);
    psa_set_key_bits(&attributes, PSA_BYTES_TO_BITS(hmac_key_length));
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_HASH);

    operation->MBEDTLS_PRIVATE(is_sign)  = 1;
    operation->MBEDTLS_PRIVATE(mac_size) = PSA_HASH_LENGTH(hash_alg);

    status = mbedtls_psa_mac_sign_setup(&operation->MBEDTLS_PRIVATE(ctx).mbedtls_ctx,
                                        &attributes,
                                        hmac_key,
                                        hmac_key_length,
                                        PSA_ALG_HMAC(hash_alg));

    if (status == PSA_SUCCESS)
    {
        /* This will mark the HMAC operation as SW-implemented. This way,
         * even though we do HW accelerate HMAC, we will use SW HMAC in the
         * context of HKDF.
         */
        setMacOperationID(operation, PSA_CRYPTO_MBED_TLS_DRIVER_ID);
    }

    psa_reset_key_attributes(&attributes);
    return status;
}

static psa_status_t psa_hkdf_input(psa_hkdf_key_derivation_t *hkdf,
                                   psa_algorithm_t kdf_alg,
                                   psa_key_derivation_step_t step,
                                   const uint8_t *data,
                                   size_t data_length)
{
    psa_algorithm_t hash_alg = PSA_ALG_HKDF_GET_HASH(kdf_alg);
    psa_status_t status;
    switch (step)
    {
        case PSA_KEY_DERIVATION_INPUT_SALT:
        #if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
            if (PSA_ALG_IS_HKDF_EXPAND(kdf_alg))
            {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
        #endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND */
            if (hkdf->MBEDTLS_PRIVATE(state) != HKDF_STATE_INIT)
            {
                return PSA_ERROR_BAD_STATE;
            }
            else
            {
                status = psa_key_derivation_start_hmac(&hkdf->MBEDTLS_PRIVATE(hmac), hash_alg, data, data_length);
                if (status != PSA_SUCCESS)
                {
                    return status;
                }
                hkdf->MBEDTLS_PRIVATE(state) = HKDF_STATE_STARTED;
                return PSA_SUCCESS;
            }
        case PSA_KEY_DERIVATION_INPUT_SECRET:
        #if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
            if (PSA_ALG_IS_HKDF_EXPAND(kdf_alg))
            {
                /* We shouldn't be in different state as HKDF_EXPAND only allows
                 * two inputs: SECRET (this case) and INFO which does not modify
                 * the state. It could happen only if the hkdf
                 * object was corrupted. */
                if (hkdf->MBEDTLS_PRIVATE(state) != HKDF_STATE_INIT)
                {
                    return PSA_ERROR_BAD_STATE;
                }

                /* Allow only input that fits expected prk size */
                if (data_length != PSA_HASH_LENGTH(hash_alg))
                {
                    return PSA_ERROR_INVALID_ARGUMENT;
                }

                memcpy(hkdf->MBEDTLS_PRIVATE(prk), data, data_length);
            }
            else
        #endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND */
            {
                /* HKDF: If no salt was provided, use an empty salt.
                 * HKDF-EXTRACT: salt is mandatory. */
                if (hkdf->MBEDTLS_PRIVATE(state) == HKDF_STATE_INIT)
                {
        #if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
                    if (PSA_ALG_IS_HKDF_EXTRACT(kdf_alg))
                    {
                        return PSA_ERROR_BAD_STATE;
                    }
        #endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
                    status = psa_key_derivation_start_hmac(&hkdf->MBEDTLS_PRIVATE(hmac), hash_alg, NULL, 0);
                    if (status != PSA_SUCCESS)
                    {
                        return status;
                    }
                    hkdf->MBEDTLS_PRIVATE(state) = HKDF_STATE_STARTED;
                }
                if (hkdf->MBEDTLS_PRIVATE(state) != HKDF_STATE_STARTED)
                {
                    return PSA_ERROR_BAD_STATE;
                }
                status = psa_mac_update(&hkdf->MBEDTLS_PRIVATE(hmac), data, data_length);
                if (status != PSA_SUCCESS)
                {
                    return status;
                }
                status = psa_mac_sign_finish(&hkdf->MBEDTLS_PRIVATE(hmac),
                                             hkdf->MBEDTLS_PRIVATE(prk),
                                             sizeof(hkdf->MBEDTLS_PRIVATE(prk)),
                                             &data_length);
                if (status != PSA_SUCCESS)
                {
                    return status;
                }
            }

            hkdf->MBEDTLS_PRIVATE(state)        = HKDF_STATE_KEYED;
            hkdf->MBEDTLS_PRIVATE(block_number) = 0;
        #if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
            if (PSA_ALG_IS_HKDF_EXTRACT(kdf_alg))
            {
                /* The only block of output is the PRK. */
                memcpy(hkdf->MBEDTLS_PRIVATE(output_block), hkdf->MBEDTLS_PRIVATE(prk), PSA_HASH_LENGTH(hash_alg));
                hkdf->MBEDTLS_PRIVATE(offset_in_block) = 0;
            }
            else
        #endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
            {
                /* Block 0 is empty, and the next block will be
                 * generated by psa_key_derivation_hkdf_read(). */
                hkdf->MBEDTLS_PRIVATE(offset_in_block) = PSA_HASH_LENGTH(hash_alg);
            }

            return PSA_SUCCESS;
        case PSA_KEY_DERIVATION_INPUT_INFO:
        #if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
            if (PSA_ALG_IS_HKDF_EXTRACT(kdf_alg))
            {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
        #endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
        #if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
            if (PSA_ALG_IS_HKDF_EXPAND(kdf_alg) && hkdf->MBEDTLS_PRIVATE(state) == HKDF_STATE_INIT)
            {
                return PSA_ERROR_BAD_STATE;
            }
        #endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
            if (hkdf->MBEDTLS_PRIVATE(state) == HKDF_STATE_OUTPUT)
            {
                return PSA_ERROR_BAD_STATE;
            }
            if (hkdf->MBEDTLS_PRIVATE(info_set))
            {
                return PSA_ERROR_BAD_STATE;
            }
            hkdf->MBEDTLS_PRIVATE(info_length) = data_length;
            if (data_length != 0)
            {
                hkdf->MBEDTLS_PRIVATE(info) = mbedtls_calloc(1, data_length);
                if (hkdf->MBEDTLS_PRIVATE(info) == NULL)
                {
                    return PSA_ERROR_INSUFFICIENT_MEMORY;
                }
                memcpy(hkdf->MBEDTLS_PRIVATE(info), data, data_length);
            }
            hkdf->MBEDTLS_PRIVATE(info_set) = 1;
            return PSA_SUCCESS;
        default:
            return PSA_ERROR_INVALID_ARGUMENT;
    }
}

static psa_status_t psa_key_derivation_hkdf_read(psa_hkdf_key_derivation_t *hkdf,
                                                 psa_algorithm_t kdf_alg,
                                                 uint8_t *output,
                                                 size_t output_length)
{
    psa_algorithm_t hash_alg = PSA_ALG_HKDF_GET_HASH(kdf_alg);
    uint8_t hash_length      = PSA_HASH_LENGTH(hash_alg);
    size_t hmac_output_length;
    psa_status_t status;
        #if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
    const uint8_t last_block = PSA_ALG_IS_HKDF_EXTRACT(kdf_alg) ? 0 : 0xff;
        #else
    const uint8_t last_block = 0xff;
        #endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */

    if (hkdf->MBEDTLS_PRIVATE(state) < HKDF_STATE_KEYED || (!hkdf->MBEDTLS_PRIVATE(info_set)
        #if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
                                                            && !PSA_ALG_IS_HKDF_EXTRACT(kdf_alg)
        #endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
                                                                ))
    {
        return PSA_ERROR_BAD_STATE;
    }
    hkdf->MBEDTLS_PRIVATE(state) = HKDF_STATE_OUTPUT;

    while (output_length != 0)
    {
        /* Copy what remains of the current block */
        uint8_t n = hash_length - hkdf->MBEDTLS_PRIVATE(offset_in_block);
        if (n > output_length)
        {
            n = (uint8_t)output_length;
        }
        memcpy(output, (hkdf->MBEDTLS_PRIVATE(output_block) + hkdf->MBEDTLS_PRIVATE(offset_in_block)), n);
        output += n;
        output_length -= n;
        hkdf->MBEDTLS_PRIVATE(offset_in_block) += n;
        if (output_length == 0)
        {
            break;
        }
        /* We can't be wanting more output after the last block, otherwise
         * the capacity check in psa_key_derivation_output_bytes() would have
         * prevented this call. It could happen only if the operation
         * object was corrupted or if this function is called directly
         * inside the library. */
        if (hkdf->MBEDTLS_PRIVATE(block_number) == last_block)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* We need a new block */
        ++hkdf->MBEDTLS_PRIVATE(block_number);
        hkdf->MBEDTLS_PRIVATE(offset_in_block) = 0;

        /* TI-MBEDTLS: Since the PSA key derivation operation struct, as well as the
         * hkdf key derivation struct, don't store the KDK key ID, we have to work with
         * plaintext. That's ok since we expect to use plaintext keys for SW Crypto. For
         * consistency and ease of implementation, SW HKDF will use SW HMAC. Doing
         * SW HKDF using accelerated HMAC would require the key derivation operation struct
         * to store the KDK key ID. Also, reset the HMAC operation struct so that it is clean
         * before starting the next HMAC operation.
         */
        hkdf->MBEDTLS_PRIVATE(hmac) = psa_mac_operation_init();
        status                      = psa_key_derivation_start_hmac(&hkdf->MBEDTLS_PRIVATE(hmac),
                                               hash_alg,
                                               hkdf->MBEDTLS_PRIVATE(prk),
                                               hash_length);
        if (status != PSA_SUCCESS)
        {
            return status;
        }

        if (hkdf->MBEDTLS_PRIVATE(block_number) != 1)
        {
            status = psa_mac_update(&hkdf->MBEDTLS_PRIVATE(hmac), hkdf->MBEDTLS_PRIVATE(output_block), hash_length);
            if (status != PSA_SUCCESS)
            {
                return status;
            }
        }
        status = psa_mac_update(&hkdf->MBEDTLS_PRIVATE(hmac),
                                hkdf->MBEDTLS_PRIVATE(info),
                                hkdf->MBEDTLS_PRIVATE(info_length));
        if (status != PSA_SUCCESS)
        {
            return status;
        }
        status = psa_mac_update(&hkdf->MBEDTLS_PRIVATE(hmac), &hkdf->MBEDTLS_PRIVATE(block_number), 1);
        if (status != PSA_SUCCESS)
        {
            return status;
        }
        status = psa_mac_sign_finish(&hkdf->MBEDTLS_PRIVATE(hmac),
                                     hkdf->MBEDTLS_PRIVATE(output_block),
                                     sizeof(hkdf->MBEDTLS_PRIVATE(output_block)),
                                     &hmac_output_length);
        if (status != PSA_SUCCESS)
        {
            return status;
        }
    }

    return PSA_SUCCESS;
}
    #endif /* defined(BUILTIN_ALG_ANY_HKDF) */
#endif     /* TI_SW_CRYPTO_ENABLED == 1 */

psa_status_t psa_key_derivation_output_bytes(psa_key_derivation_operation_t *operation,
                                             uint8_t *output,
                                             size_t output_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_OUTPUT_DECLARE(output, output_internal);
#endif

    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_output_bytes(operation, output, output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        if (operation->MBEDTLS_PRIVATE(alg) == 0)
        {
            return PSA_ERROR_BAD_STATE;
        }

        if (output_length == 0 && operation->MBEDTLS_PRIVATE(capacity) == 0)
        {
            /* Edge case: this is a finished operation, and 0 bytes
             * were requested. The right error in this case could
             * be either INSUFFICIENT_CAPACITY or BAD_STATE. Return
             * INSUFFICIENT_CAPACITY, which is right for a finished
             * operation, for consistency with the case when
             * output_length > 0.
             */
            return PSA_ERROR_INSUFFICIENT_DATA;
        }

        LOCAL_OUTPUT_ALLOC(output, output_length, output_internal);
        if (output_length > operation->MBEDTLS_PRIVATE(capacity))
        {
            operation->MBEDTLS_PRIVATE(capacity) = 0;
            /* Go through the error path to wipe all confidential data now
             * that the operation object is useless. */
            status                               = PSA_ERROR_INSUFFICIENT_DATA;
            goto exit;
        }

        operation->MBEDTLS_PRIVATE(capacity) -= output_length;

    #if defined(BUILTIN_ALG_ANY_HKDF)
        if (PSA_ALG_IS_ANY_HKDF(operation->MBEDTLS_PRIVATE(alg)))
        {
            status = psa_key_derivation_hkdf_read(&operation->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(hkdf),
                                                  operation->MBEDTLS_PRIVATE(alg),
                                                  output_internal,
                                                  output_length);
        }
    #endif

exit:
        if (status != PSA_SUCCESS)
        {
            /* Preserve the algorithm upon errors, but clear all sensitive state.
             * This allows us to differentiate between exhausted operations and
             * blank operations, so we can return PSA_ERROR_BAD_STATE on blank
             * operations.
             */
            psa_algorithm_t alg = operation->MBEDTLS_PRIVATE(alg);
            psa_key_derivation_abort(operation);
            operation->MBEDTLS_PRIVATE(alg) = alg;
            if (output_internal != NULL)
            {
                memset(output_internal, '!', output_length);
            }
        }

        LOCAL_OUTPUT_FREE(output, output_internal);
        return status;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_output_key(const psa_key_attributes_t *attributes,
                                           psa_key_derivation_operation_t *operation,
                                           mbedtls_svc_key_id_t *key)
{
    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_output_key(attributes, operation, key);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* This API is not needed for HKDF in any TLS 1.3 use-case. So, it will be omitted for now. */
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_setup(psa_key_derivation_operation_t *operation, psa_algorithm_t alg)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status;
    psa_algorithm_t hash_alg;
    size_t hash_size;
#endif

    if (isHardwareAccelerated(alg))
    {
        /* Call hardware accelerated function - mark operation->MBEDTLS_PRIVATE(id) as HW-accelerated */
        setKeyDerivationOperationID(operation, PSA_CRYPTO_TI_DRIVER_ID);

        return ti_psa_key_derivation_setup(operation, alg);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        if (operation->MBEDTLS_PRIVATE(alg) != 0)
        {
            return PSA_ERROR_BAD_STATE;
        }

        memset(&operation->MBEDTLS_PRIVATE(ctx), 0, sizeof(operation->MBEDTLS_PRIVATE(ctx)));

        if (!PSA_ALG_IS_ANY_HKDF(alg))
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
        else
        {
            status    = PSA_SUCCESS;
            hash_alg  = PSA_ALG_HKDF_GET_HASH(alg);
            hash_size = PSA_HASH_LENGTH(hash_alg);

            if (hash_size == 0)
            {
                status = PSA_ERROR_NOT_SUPPORTED;
            }

    #if defined(PSA_WANT_ALG_HKDF)
            if (PSA_ALG_IS_HKDF(alg))
            {
                operation->MBEDTLS_PRIVATE(capacity) = 255 * hash_size;
            }
            else
    #endif
    #if defined(PSA_WANT_ALG_HKDF_EXTRACT)
                if (PSA_ALG_IS_HKDF_EXTRACT(alg))
            {
                operation->MBEDTLS_PRIVATE(capacity) = hash_size;
            }
            else
    #endif
    #if defined(PSA_WANT_ALG_HKDF_EXPAND)
                if (PSA_ALG_IS_HKDF_EXPAND(alg))
            {
                operation->MBEDTLS_PRIVATE(capacity) = 255 * hash_size;
            }
            else
    #endif
            {
                status = PSA_ERROR_NOT_SUPPORTED;
            }
        }

        if (status == PSA_SUCCESS)
        {
            /* Mark SW implementation as active for this operation */
            setKeyDerivationOperationID(operation, PSA_CRYPTO_MBED_TLS_DRIVER_ID);
            operation->MBEDTLS_PRIVATE(alg) = alg;
        }

        return status;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_input_bytes(psa_key_derivation_operation_t *operation,
                                            psa_key_derivation_step_t step,
                                            const uint8_t *input,
                                            size_t input_length)
{
#if (TI_SW_CRYPTO_ENABLED == 1)
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    LOCAL_INPUT_DECLARE(input, input_internal);
#endif

    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_input_bytes(operation, step, input, input_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        LOCAL_INPUT_ALLOC(input, input_length, input_internal);

        if (operation->MBEDTLS_PRIVATE(alg) == PSA_ALG_NONE)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }

    #if defined(BUILTIN_ALG_ANY_HKDF)
        if (PSA_ALG_IS_ANY_HKDF(operation->MBEDTLS_PRIVATE(alg)))
        {
            status = psa_hkdf_input(&operation->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(hkdf),
                                    operation->MBEDTLS_PRIVATE(alg),
                                    step,
                                    input_internal,
                                    input_length);
        }
        else
    #endif /* BUILTIN_ALG_ANY_HKDF */
        {
            return PSA_ERROR_BAD_STATE;
        }

        if (status != PSA_SUCCESS)
        {
            psa_key_derivation_abort(operation);
        }

    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)
exit:
    #endif
        LOCAL_INPUT_FREE(input, input_internal);
        return status;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_input_integer(psa_key_derivation_operation_t *operation,
                                              psa_key_derivation_step_t step,
                                              uint64_t value)
{
    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_input_integer(operation, step, value);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* This API is not needed for HKDF in any TLS 1.3 use-case. So, it will be omitted for now. */
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_input_key(psa_key_derivation_operation_t *operation,
                                          psa_key_derivation_step_t step,
                                          mbedtls_svc_key_id_t key)
{
    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_input_key(operation, step, key);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* This API is not needed for HKDF in any TLS 1.3 use-case. So, it will be omitted for now. */
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_verify_bytes(psa_key_derivation_operation_t *operation,
                                             const uint8_t *expected_output,
                                             size_t output_length)
{
    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_verify_bytes(operation, expected_output, output_length);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* This API is not needed for HKDF in any TLS 1.3 use-case. So, it will be omitted for now. */
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_verify_key(psa_key_derivation_operation_t *operation, mbedtls_svc_key_id_t expected)
{
    if (isHardwareKeyDerivationOperation(operation))
    {
        return ti_psa_key_derivation_verify_key(operation, expected);
    }
#if (TI_SW_CRYPTO_ENABLED == 1)
    else
    {
        /* This API is not needed for HKDF in any TLS 1.3 use-case. So, it will be omitted for now. */
        return PSA_ERROR_NOT_SUPPORTED;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* TI_SW_CRYPTO_ENABLED */
}

psa_status_t psa_key_derivation_key_agreement(psa_key_derivation_operation_t *operation,
                                              psa_key_derivation_step_t step,
                                              mbedtls_svc_key_id_t private_key,
                                              const uint8_t *peer_key,
                                              size_t peer_key_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}
