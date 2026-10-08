/* adapter_psa_key_derivation.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the key derivation services.
 */

/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/c_adapter_psa.h>              // configuration
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                       // size_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>                 // the API to implement
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_derivation.h> // psa_key_derivation_operation_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Note that the following prefixing macros cannot exist in
 * adapter_psa_key_management_prefix. This is because top-level
 * crypto.h includes that prefix header, and the KeyMgmt
 * key derivation APIs differ from those that the PSA API
 * defines in more than just API name. The derivation
 * operation struct is different.
 */
#define KEYMGMT_FUNCTION_NAME(x) KeyMgmt_##x

#define psa_key_derivation_get_capacity \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_get_capacity)
#define psa_key_derivation_set_capacity \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_set_capacity)
#define psa_key_derivation_input_bytes \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_input_bytes)
#define psa_key_derivation_input_integer \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_input_integer)
#define psa_key_derivation_output_bytes \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_output_bytes)
#define psa_key_derivation_input_key \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_input_key)
#define psa_key_derivation_output_key \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_output_key)
#define psa_key_derivation_verify_bytes \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_verify_bytes)
#define psa_key_derivation_verify_key \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_verify_key)
#define psa_key_derivation_setup \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_setup)
#define psa_key_derivation_abort \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_abort)
#define psa_key_derivation_key_agreement \
        KEYMGMT_FUNCTION_NAME(psa_key_derivation_key_agreement)

/*----------------------------------------------------------------------------
 * is_kdf_alg_supported
 */
static int is_kdf_alg_supported(psa_algorithm_t kdf_alg)
{
    if (kdf_alg == PSA_ALG_SP800_108_COUNTER_HMAC(PSA_ALG_SHA_256))
    {
        /* HKDFs are supported only when deriving keys from the TKDK */
        return 1;
    }
    else if (kdf_alg == PSA_ALG_SP800_108_COUNTER_CMAC)
    {
        /* Counter-based CMAC key derivation is default for all other key derivations */
        return 1;
    }

    return 0;
}

static psa_status_t validate_attributes(const psa_key_attributes_t * attributes, mbedtls_svc_key_id_t derivationKey, uint32_t capacity)
{
    psa_status_t status = PSA_SUCCESS;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(attributes->MBEDTLS_PRIVATE(lifetime));
    psa_key_persistence_t persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(attributes->MBEDTLS_PRIVATE(lifetime));
    size_t key_size = PSA_BITS_TO_BYTES(attributes->MBEDTLS_PRIVATE(bits));
    psa_key_id_t derivedKeyID;
    psa_key_id_t derivationKeyID;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    derivedKeyID = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id);
    derivationKeyID = derivationKey.MBEDTLS_PRIVATE(key_id);
#else
    derivedKeyID = attributes->MBEDTLS_PRIVATE(id);
    derivationKeyID = derivationKey;
#endif

    if ((attributes->MBEDTLS_PRIVATE(type) == PSA_KEY_TYPE_NONE) ||
        (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type))))
    {
        status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if ((location != PSA_KEY_LOCATION_HSM_ASSET_STORE) ||
             (persistence != PSA_KEY_PERSISTENCE_HSM_ASSET_STORE))
    {
        /* Derived keys cannot be retrieved in plaintext. They must be derived as keys with HSM_ASSET_STORE
         * persistence because the Asset Load Derive token cannot export a key blob of the derived key.
         */
        status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (((derivationKeyID == PSA_KEY_ID_HSM_HUK) && (derivedKeyID != PSA_KEY_ID_HSM_TKDK)) ||
             ((derivedKeyID != PSA_KEY_ID_NULL) && (derivedKeyID < PSA_KEY_ID_USER_MIN)) ||
             ((derivationKeyID != PSA_KEY_ID_HSM_HUK) && (derivedKeyID >= PSA_KEY_ID_HSM_TKDK)))
    {
        /* The derived key ID can only be that of the TKDK when the KDK is the HUK. The ID must be
         * at least the minimum value, if one is provided. If the KDK is not the HUK, then the derived
         * KDK ID must not be that of the TKDK or anything higher.
         */
        status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (key_size > capacity)
    {
        status = PSA_ERROR_INSUFFICIENT_DATA;
    }

    return status;
}

/*----------------------------------------------------------------------------
 * psa_key_derivation_setup
 */
psa_status_t
psa_key_derivation_setup(KeyMgmt_psa_key_derivation_operation_t * operation,
                         psa_algorithm_t alg)
{
    if ((alg & PSA_ALG_CATEGORY_MASK) != PSA_ALG_CATEGORY_KEY_DERIVATION)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!is_kdf_alg_supported(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    operation->alg = alg;
    operation->inputKey = MBEDTLS_SVC_KEY_ID_INIT;
    operation->labelSize = 0U;
    operation->contextSize = 0U;
    operation->canDerive = false;
    /* Per PSA spec */
    operation->capacity = 0x1FFFFFFF;
    operation->capacitySet = false;
    return PSA_SUCCESS;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_get_capacity
 */
psa_status_t
psa_key_derivation_get_capacity(const KeyMgmt_psa_key_derivation_operation_t *operation,
                                size_t *capacity)
{
    if (operation->alg == 0) {
        /* This is a blank key derivation operation. */
        return PSA_ERROR_BAD_STATE;
    }

    *capacity = operation->capacity;
    return PSA_SUCCESS;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_set_capacity
 */
psa_status_t
psa_key_derivation_set_capacity(KeyMgmt_psa_key_derivation_operation_t * operation,
                                size_t capacity)
{
    if (operation->alg == 0) {
        return PSA_ERROR_BAD_STATE;
    }

    if (capacity > operation->capacity) {
        /* For the supported KDFs, the initial capacity is set to 2^29-1 bytes. */
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (operation->capacitySet)
    {
        return PSA_ERROR_NOT_PERMITTED;
    }

    /* For HMAC-based KDKs (i.e. the TKDK), this has no effect. The HSM automatically
     * places the key context (which includes the output length, L) without regard for
     * what the operation's capacity value is.
     */
    operation->capacity = capacity;
    operation->capacitySet = true;
    return PSA_SUCCESS;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_input_bytes
 */
psa_status_t
psa_key_derivation_input_bytes(KeyMgmt_psa_key_derivation_operation_t * operation,
                               psa_key_derivation_step_t step,
                               const uint8_t * data,
                               size_t data_length)
{
    psa_status_t status = PSA_SUCCESS;
    psa_key_id_t id;
    size_t maxLength;

    if ((operation == NULL) || (data == NULL) || (data_length == 0U))
    {
        status = PSA_ERROR_INVALID_ARGUMENT;
    }

#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    id = operation->inputKey.MBEDTLS_PRIVATE(key_id);
#else
    id = operation->inputKey;
#endif

    if (id == PSA_KEY_ID_NULL)
    {
        /* Operation is out of order - a valid key should be input before bytes. */
        status = PSA_ERROR_BAD_STATE;
    }

    if (status == PSA_SUCCESS)
    {
        if (step == PSA_KEY_DERIVATION_INPUT_LABEL)
        {
            if ((id == PSA_KEY_ID_HSM_TKDK) || (id == PSA_KEY_ID_HSM_HUK))
            {
                /* For these two keys, the HSM will add the 'context' automatically.
                 * That includes the end marker for the label and the length of the output.
                 * This means that the user-provided label can take the full operation buffer
                 * space.
                 */
                maxLength = PSA_KDF_LABEL_MAX_SIZE;
            }
            else
            {
                /* For normal KDKs, the HSM will not add the 'context' nor the output length.
                 * Therefore, we must save 5 bytes in our operation buffer to store the end
                 * marker byte (1 byte) and the length of the output (4 bytes).
                 */
                maxLength = PSA_KDF_LABEL_MAX_SIZE - 5;
            }

            if (data_length > maxLength)
            {
                status = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                /* Copy user-provided label. The "context" field of the fixed input data will be appended
                 * on the next (optional) call to psa_key_derivation_input_bytes.
                 */
                (void)memcpy((void *)&operation->fixedInputData[0], (void *)data, data_length);

                operation->labelSize = data_length;
            }
        }
        else if (step == PSA_KEY_DERIVATION_INPUT_CONTEXT)
        {
            if (operation->labelSize == 0)
            {
                /* A label must be added before a context. Technically, both are optional,
                 * but we won't support adding a 0-length label and then a non-zero-length
                 * context.
                 */
                status = PSA_ERROR_BAD_STATE;
            }
            else if ((id == PSA_KEY_ID_HSM_TKDK) || (id == PSA_KEY_ID_HSM_HUK))
            {
                /* No need to use the application-provided context, as the HSM will append
                 * one automatically for the trusted KDKs. The HUK and TKDK have reserved
                 * PSA Key IDs that reside within the range of valid IDs for persistent
                 * and asset store keys.
                 */
                status = PSA_SUCCESS;
                /* The HSM-appended context for the HUK and TKDK is always 13 bytes, including
                 * fields for an end marker, host ID, asset policy, FIPS-Approved mode, and length.
                 */
                operation->contextSize = 13U;
            }
            else if (((operation->labelSize + data_length) > (PSA_KDF_LABEL_MAX_SIZE - 5)) ||
                     ((operation->labelSize + data_length + 5) < PSA_KDF_LABEL_MIN_SIZE))
            {
                /* 5 reserved bytes for (1 byte) end marker between label and context,
                 * and 4 bytes for length of output key. Note that the PSA spec requires 4
                 * bytes for the output key length, but the SP800-108 spec requires 2 bytes.
                 */
                status = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                /* Place end marker between label and context, per SP800-108 specification */
                operation->fixedInputData[operation->labelSize] = (uint8_t)0x00;

                /* Copy user-provided context. The "length" field of the fixed input data will be appended
                 * when an output is requested from the key derivation
                 */
                (void)memcpy((void *)&operation->fixedInputData[(operation->labelSize + 1)], (void *)data, data_length);
                operation->contextSize = data_length;

                status = PSA_SUCCESS;
            }
        }
        else
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    return status;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_input_integer
 */
psa_status_t
psa_key_derivation_input_integer(KeyMgmt_psa_key_derivation_operation_t * operation,
                                 psa_key_derivation_step_t step,
                                 uint64_t value)
{
    (void)operation;
    (void)step;
    (void)value;

    /* The supported Key Derivation algorithms do not require any input integers,
     * so this API is unsupported.
     */
    return PSA_ERROR_NOT_SUPPORTED;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_input_key
 */
psa_status_t
psa_key_derivation_input_key(KeyMgmt_psa_key_derivation_operation_t * operation,
                             psa_key_derivation_step_t step,
                             mbedtls_svc_key_id_t key)
{
    psa_status_t status = PSA_SUCCESS;
    psa_key_attributes_t attributes;
    psa_algorithm_t psaAlg;
    psa_algorithm_t psaUsage;
    psa_key_type_t psaType;
    psa_key_id_t derivationKeyID;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    derivationKeyID = key.MBEDTLS_PRIVATE(key_id);
#else
    derivationKeyID = key;
#endif

    if (step == PSA_KEY_DERIVATION_INPUT_SECRET)
    {
        if (derivationKeyID == PSA_KEY_ID_HSM_HUK)
        {
            /* The HUK does not occupy a slot in KeyStore and therefore does not have stored PSA Attributes.
             * The HUK is always allowed to perform the TKDK derivation, unless the TKDK already exists, which
             * would be checked later.
             */
            if (operation->alg == PSA_ALG_SP800_108_COUNTER_CMAC)
            {
                operation->canDerive = true;

                status = PSA_SUCCESS;
            }
            else
            {
                status = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            status = psa_get_key_attributes(key, &attributes);

            if (status == PSA_SUCCESS)
            {
                psaAlg = attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg);
                psaUsage = attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
                psaType = attributes.MBEDTLS_PRIVATE(type);

                if ((derivationKeyID == PSA_KEY_ID_HSM_TKDK) &&
                    (operation->alg == PSA_ALG_SP800_108_COUNTER_HMAC(PSA_ALG_SHA_256)) &&
                    (psaAlg == PSA_ALG_SP800_108_COUNTER_HMAC(PSA_ALG_SHA_256)) &&
                    ((psaType == PSA_KEY_TYPE_HMAC) || (psaType == PSA_KEY_TYPE_DERIVE)))
                {
                    /* Valid key type for the given derivation operation */
                }
                else if ((derivationKeyID != PSA_KEY_ID_HSM_TKDK) &&
                         (operation->alg == PSA_ALG_SP800_108_COUNTER_CMAC) &&
                         (psaAlg == PSA_ALG_SP800_108_COUNTER_CMAC) &&
                         (psaType == PSA_KEY_TYPE_AES))
                {
                    /* Valid key type for the given derivation operation */
                }
                else
                {
                    status = PSA_ERROR_INVALID_ARGUMENT;
                }

                if ((psaUsage != PSA_KEY_USAGE_DERIVE) &&
                    (psaUsage != PSA_KEY_USAGE_VERIFY_DERIVATION))
                {
                    status = PSA_ERROR_INVALID_ARGUMENT;
                }
                else if (psaUsage == PSA_KEY_USAGE_DERIVE)
                {
                    operation->canDerive = true;
                }
            }
            else
            {
                /* Error already set */
            }
        }
    }
    else
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    if (status == PSA_SUCCESS)
    {
        operation->inputKey = key;
    }

    return status;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_output_bytes
 */
psa_status_t
psa_key_derivation_output_bytes(KeyMgmt_psa_key_derivation_operation_t * operation,
                                uint8_t * output,
                                size_t output_length)
{
    (void)operation;
    (void)output;
    (void)output_length;

    /* As of now, not supported to retrieve derived key in plaintext. May be possible
     * in future with creation of public data asset to derive into.
     */
    return PSA_ERROR_NOT_SUPPORTED;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_output_key
 */
psa_status_t
psa_key_derivation_output_key(const psa_key_attributes_t * attributes,
                              KeyMgmt_psa_key_derivation_operation_t * operation,
                              mbedtls_svc_key_id_t * key)
{
    psa_status_t status;

    status = validate_attributes(attributes, operation->inputKey, operation->capacity);

    if (status != PSA_SUCCESS)
    {
        /* Error already set. validate_attributes will validate attribute requirements specific
         * to key derivations - there may still be an invalid argument found in key management
         * when the derived asset policy is being created after this point.
         */
    }
    else if (!is_kdf_alg_supported(operation->alg))
    {
        /* If a valid algorithm hasn't been saved via the setup API,
         * then the operation struct is in a bad state to continue.
         */
        status = PSA_ERROR_BAD_STATE;
    }
    else if (!operation->canDerive)
    {
        /* operation->canDerive reflects whether the key that was input permits derivation */
        status = PSA_ERROR_NOT_PERMITTED;
    }
    else
    {
        status = psaInt_KeyMgmtDeriveKey(attributes, operation, key);
    }

    return status;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_verify_bytes
 */
psa_status_t
psa_key_derivation_verify_bytes(KeyMgmt_psa_key_derivation_operation_t * operation,
                                const uint8_t *expected_output,
                                size_t output_length)
{
    (void)operation;
    (void)expected_output;
    (void)output_length;

    return PSA_ERROR_NOT_SUPPORTED;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_verify_key
 */
psa_status_t
psa_key_derivation_verify_key(KeyMgmt_psa_key_derivation_operation_t * operation,
                              mbedtls_svc_key_id_t expected)
{
    (void)operation;
    (void)expected;

    return PSA_ERROR_NOT_SUPPORTED;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_set_capacity
 */
psa_status_t
psa_key_derivation_abort(KeyMgmt_psa_key_derivation_operation_t * operation)
{
    operation->alg = 0;
    operation->inputKey = MBEDTLS_SVC_KEY_ID_INIT;
    (void)memset(operation->fixedInputData, 0, PSA_KDF_LABEL_MAX_SIZE);
    operation->labelSize = 0;
    operation->contextSize = 0;
    operation->handle = 0;
    operation->capacity = 0;
    operation->canDerive = false;
    operation->capacitySet = false;

    return PSA_SUCCESS;
}


/*----------------------------------------------------------------------------
 * psa_key_derivation_key_agreement
 */
psa_status_t
psa_key_derivation_key_agreement(KeyMgmt_psa_key_derivation_operation_t * operation,
                                 psa_key_derivation_step_t step,
                                 mbedtls_svc_key_id_t private_key,
                                 const uint8_t * peer_key,
                                 size_t peer_key_length)
{
    (void)operation;
    (void)step;
    (void)private_key;
    (void)peer_key;
    (void)peer_key_length;

    return PSA_ERROR_NOT_SUPPORTED;
}


/* end of file adapter_psa_key_derivation.c */