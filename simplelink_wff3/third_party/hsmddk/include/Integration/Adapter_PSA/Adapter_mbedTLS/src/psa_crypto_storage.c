/*
 *  Copyright The Mbed TLS Contributors
 *  Copyright (c) 2024, Texas Instruments Incorporated
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

/* TI Customizations: Altered implementation of some APIs to match key 'slot'
 * architecture used in our implementation.
 */

#include <string.h>

#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/psa_crypto_storage.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/private_access.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/platform.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/internal_trusted_storage.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa_key_store.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
/**
 * Persistent key storage magic header.
 */
#define PSA_KEY_STORAGE_MAGIC_HEADER "PSA\0KEY"
#define PSA_KEY_STORAGE_MAGIC_HEADER_LENGTH (sizeof(PSA_KEY_STORAGE_MAGIC_HEADER))

typedef struct {
    uint8_t magic[PSA_KEY_STORAGE_MAGIC_HEADER_LENGTH];

    uint8_t MBEDTLS_PRIVATE(lifetime[sizeof(psa_key_lifetime_t)]);
    uint8_t MBEDTLS_PRIVATE(type)[2];
    uint8_t MBEDTLS_PRIVATE(bits)[2];
    uint8_t MBEDTLS_PRIVATE(policy)[sizeof(psa_key_policy_t)];
    uint8_t assetPolicy[sizeof(PsaPolicyMask_t)];
    uint8_t data_len[4];
    /* May be extended when the key being stored is a key blob for a symmetric key
     * with the key usage set for both encryption and decryption
     */
    uint8_t key_data[];
} psa_persistent_key_storage_format;

/**
 * \brief Get data length for given key slot number.
 *
 * \param key               Persistent identifier whose stored data length
 *                          is to be obtained.
 * \param[out] data_length  The number of bytes that make up the data.
 *
 * \retval #PSA_SUCCESS \emptydescription
 * \retval #PSA_ERROR_STORAGE_FAILURE \emptydescription
 * \retval #PSA_ERROR_DOES_NOT_EXIST \emptydescription
 * \retval #PSA_ERROR_DATA_CORRUPT \emptydescription
 */
static psa_status_t psa_crypto_storage_get_data_length(const mbedtls_svc_key_id_t key,
                                                       size_t *data_length)
{
    psa_status_t status;
    psa_storage_uid_t data_identifier = psa_its_identifier_of_slot(key);
    struct psa_storage_info_t data_identifier_info;

    status = psa_its_get_info(data_identifier, &data_identifier_info);
    if (status != PSA_SUCCESS) {
        return status;
    }

    *data_length = (size_t) data_identifier_info.size;

    return PSA_SUCCESS;
}

/**
 * \brief Load persistent data for the given key slot number.
 *
 * This function reads data from a storage backend and returns the data in a
 * buffer.
 *
 * \param key               Persistent identifier of the key to be loaded. This
 *                          should be an occupied storage location.
 * \param[out] data         Buffer where the data is to be written.
 * \param data_size         Size of the \c data buffer in bytes.
 *
 * \retval #PSA_SUCCESS \emptydescription
 * \retval #PSA_ERROR_DATA_INVALID \emptydescription
 * \retval #PSA_ERROR_DATA_CORRUPT \emptydescription
 * \retval #PSA_ERROR_STORAGE_FAILURE \emptydescription
 * \retval #PSA_ERROR_DOES_NOT_EXIST \emptydescription
 */
static psa_status_t psa_crypto_storage_load(const mbedtls_svc_key_id_t key,
                                            uint8_t *data,
                                            size_t data_size)
{
    psa_status_t status;
    psa_storage_uid_t data_identifier = psa_its_identifier_of_slot(key);
    struct psa_storage_info_t data_identifier_info;
    size_t data_length = 0;

    status = psa_its_get_info(data_identifier, &data_identifier_info);
    if (status  != PSA_SUCCESS) {
        return status;
    }

    status = psa_its_get(data_identifier, 0, (uint32_t) data_size, data, &data_length);
    if (data_size  != data_length) {
        return PSA_ERROR_DATA_INVALID;
    }

    return status;
}

static void psa_format_key_data_for_storage(const uint8_t *data,
                                            const uint8_t *data2,
                                            const size_t data_length,
                                            const psa_key_attributes_t *attr,
                                            const PsaPolicyMask_t *assetPolicy,
                                            uint8_t *storage_data)
{
    psa_persistent_key_storage_format *storage_format =
        (psa_persistent_key_storage_format *) storage_data;


    memcpy(storage_format->magic, PSA_KEY_STORAGE_MAGIC_HEADER,
           PSA_KEY_STORAGE_MAGIC_HEADER_LENGTH);

    memcpy(storage_format->MBEDTLS_PRIVATE(lifetime), &attr->MBEDTLS_PRIVATE(lifetime), sizeof(psa_key_lifetime_t));

    memcpy(storage_format->MBEDTLS_PRIVATE(type), &attr->MBEDTLS_PRIVATE(type), sizeof(psa_key_type_t));

    memcpy(storage_format->MBEDTLS_PRIVATE(bits), &attr->MBEDTLS_PRIVATE(bits), sizeof(psa_key_bits_t));

    memcpy(storage_format->MBEDTLS_PRIVATE(policy),
           &attr->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage), sizeof(psa_key_usage_t));

    memcpy(storage_format->MBEDTLS_PRIVATE(policy) + sizeof(psa_key_usage_t),
           &attr->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg), sizeof(psa_algorithm_t));

    memcpy(storage_format->MBEDTLS_PRIVATE(policy) + sizeof(psa_key_usage_t) + sizeof(psa_algorithm_t),
           &attr->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2), sizeof(psa_algorithm_t));

    memcpy(storage_format->assetPolicy, assetPolicy, sizeof(PsaPolicyMask_t));

    memcpy(storage_format->data_len, &data_length, sizeof(data_length));

    memcpy(storage_format->key_data, data, data_length);

    if (data2 != NULL)
    {
        memcpy(storage_format->key_data + data_length, data2, data_length);
    }
}

static psa_status_t check_magic_header(const uint8_t *data)
{
    if (memcmp(data, PSA_KEY_STORAGE_MAGIC_HEADER,
               PSA_KEY_STORAGE_MAGIC_HEADER_LENGTH) != 0) {
        return PSA_ERROR_DATA_INVALID;
    }
    return PSA_SUCCESS;
}

static psa_status_t psa_parse_key_data_from_storage(const uint8_t *storage_data,
                                                    size_t storage_data_length,
                                                    uint8_t **key_data,
                                                    uint8_t **key_data2,
                                                    size_t *key_data_length,
                                                    psa_key_attributes_t *attr,
                                                    PsaPolicyMask_t *assetPolicy)
{
    psa_status_t status;
    const psa_persistent_key_storage_format *storage_format =
        (const psa_persistent_key_storage_format *) storage_data;
    bool hasSymmetricKey = false;

    if (storage_data_length < sizeof(*storage_format))
    {
        return PSA_ERROR_DATA_INVALID;
    }

    status = check_magic_header(storage_data);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    memcpy(key_data_length, storage_format->data_len, sizeof(size_t));

    if (*key_data_length > (storage_data_length - sizeof(*storage_format)) ||
        *key_data_length > PSA_CRYPTO_MAX_STORAGE_SIZE)
        {
        return PSA_ERROR_DATA_INVALID;
    }
    else if ((storage_data_length) - sizeof(*storage_format) == ((*key_data_length) * 2))
    {
        /* The common case is that the difference of storage_data_length and the
         * storage_format struct size is exactly equal to the key_data_length. If
         * the difference is instead equal to two times key_data_length, then that means
         * there is a second key blob present immediately after the first. This is
         * the case only for symmetric keys with bi-directional PSA usage.
         */
        hasSymmetricKey = true;
    }
    else if ((storage_data_length - sizeof(*storage_format) > *key_data_length))
    {
        /* If more key data is retrieved from ITS than is expected for one key, and
         * it's not specifically the amount of data for two key blobs, then the data
         * is invalid.
         */
        return PSA_ERROR_DATA_INVALID;
    }

    if (*key_data_length == 0)
    {
        *key_data = NULL;
    }
    else
    {
        *key_data = psaInt_mbedtls_calloc(1, *key_data_length);
        if (*key_data == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
        memcpy(*key_data, storage_format->key_data, *key_data_length);

        /* storage_data_length may reflect that there are two key blobs stored
         * consecutively
         */
        if (hasSymmetricKey)
        {
            *key_data2 = psaInt_mbedtls_calloc(1, *key_data_length);
            if (*key_data2 == NULL)
            {
                return PSA_ERROR_INSUFFICIENT_MEMORY;
            }
            memcpy(*key_data2, storage_format->key_data + *key_data_length, *key_data_length);
        }
    }

    memcpy(&attr->MBEDTLS_PRIVATE(lifetime), storage_format->MBEDTLS_PRIVATE(lifetime), sizeof(psa_key_lifetime_t));
    memcpy(&attr->MBEDTLS_PRIVATE(type), storage_format->MBEDTLS_PRIVATE(type), sizeof(psa_key_type_t));
    memcpy(&attr->MBEDTLS_PRIVATE(bits), storage_format->MBEDTLS_PRIVATE(bits), sizeof(psa_key_bits_t));

    memcpy(&attr->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage),
           storage_format->MBEDTLS_PRIVATE(policy),
           sizeof(psa_key_usage_t));

    memcpy(&attr->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg),
           storage_format->MBEDTLS_PRIVATE(policy) + sizeof(psa_key_usage_t),
           sizeof(psa_algorithm_t));

    memcpy(&attr->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2),
           storage_format->MBEDTLS_PRIVATE(policy) + sizeof(psa_key_usage_t) + sizeof(psa_algorithm_t),
           sizeof(psa_algorithm_t));

    memcpy(assetPolicy, storage_format->assetPolicy, sizeof(PsaPolicyMask_t));

    return PSA_SUCCESS;
}

/**
 * \brief Store persistent data for the given key slot number.
 *
 * This function stores the given data buffer to a persistent storage.
 *
 * \param key           Persistent identifier of the key to be stored. This
 *                      should be an unoccupied storage location.
 * \param[in] data      Buffer containing the data to be stored.
 * \param data_length   The number of bytes
 *                      that make up the data.
 *
 * \retval #PSA_SUCCESS \emptydescription
 * \retval #PSA_ERROR_INSUFFICIENT_STORAGE \emptydescription
 * \retval #PSA_ERROR_ALREADY_EXISTS \emptydescription
 * \retval #PSA_ERROR_STORAGE_FAILURE \emptydescription
 * \retval #PSA_ERROR_DATA_INVALID \emptydescription
 */
static psa_status_t psa_crypto_storage_store(const mbedtls_svc_key_id_t key,
                                             const uint8_t *data,
                                             size_t data_length)
{
    psa_status_t status;
    psa_storage_uid_t data_identifier = psa_its_identifier_of_slot(key);
    struct psa_storage_info_t data_identifier_info;

    if (psa_is_key_present_in_storage(key) == 1)
    {
        return PSA_ERROR_ALREADY_EXISTS;
    }

    status = psa_its_set(data_identifier, (uint32_t) data_length, data, 0);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    status = psa_its_get_info(data_identifier, &data_identifier_info);
    if (status != PSA_SUCCESS)
    {
        goto exit;
    }

    if (data_identifier_info.size != data_length)
    {
        status = PSA_ERROR_DATA_INVALID;
        goto exit;
    }

exit:
    if (status != PSA_SUCCESS) {
        /* Remove the file in case we managed to create it but something
         * went wrong. It's ok if the file doesn't exist. If the file exists
         * but the removal fails, we're already reporting an error so there's
         * nothing else we can do. */
        (void) psa_its_remove(data_identifier);
    }
    return status;
}

/* Determine a file name (ITS file identifier) for the given key identifier.
 * The file name must be distinct from any file that is used for a purpose
 * other than storing a key. Currently, the only such file is the random seed
 * file whose name is PSA_CRYPTO_ITS_RANDOM_SEED_UID and whose value is
 * 0xFFFFFF52. */
psa_storage_uid_t psa_its_identifier_of_slot(mbedtls_svc_key_id_t key)
{
#if defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)
    /* Encode the owner in the upper 32 bits. This means that if
     * owner values are nonzero (as they are on a PSA platform),
     * no key file will ever have a value less than 0x100000000, so
     * the whole range 0..0xffffffff is available for non-key files. */
    uint32_t unsigned_owner_id = key.MBEDTLS_PRIVATE(owner);
    return ((uint64_t) unsigned_owner_id << 32) |
            key.MBEDTLS_PRIVATE(key_id);
#else
    /* Use the key id directly as a file name.
     * psa_is_key_id_valid() is responsible for
     * ensuring that key identifiers do not have a
     * value that is reserved for non-key files. */
    return key;
#endif
}

int psa_is_key_present_in_storage(const mbedtls_svc_key_id_t key)
{
    psa_status_t ret;
    psa_storage_uid_t data_identifier = psa_its_identifier_of_slot(key);
    struct psa_storage_info_t data_identifier_info;

    ret = psa_its_get_info(data_identifier, &data_identifier_info);

    if (ret == PSA_ERROR_DOES_NOT_EXIST) {
        return 0;
    }

    return 1;
}

psa_status_t psa_save_persistent_key(psa_key_context_t * pEntry,
                                     const psa_key_attributes_t *attr,
                                     const PsaPolicyMask_t *assetPolicy,
                                     const uint8_t *data,
                                     const uint8_t *data2,
                                     const size_t data_length)
{
    size_t input_data_length;
    size_t storage_data_length;
    uint8_t *storage_data;
    psa_status_t status;

    /* All keys saved to persistent storage always have a key context */
    if (data == NULL || data_length == 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (data2 == NULL)
    {
        input_data_length = data_length;
    }
    else
    {
        /* In this case, a second key blob is provided that also needs to be saved */
        input_data_length = data_length * 2;
    }

    if (input_data_length > PSA_CRYPTO_MAX_STORAGE_SIZE) {
        return PSA_ERROR_INSUFFICIENT_STORAGE;
    }
    /* Note: sizeof(psa_persistent_key_storage_format) is 40 bytes. Relevant for SysConfig RAM configurations. */
    storage_data_length = input_data_length + sizeof(psa_persistent_key_storage_format);

    storage_data = psaInt_mbedtls_calloc(1, storage_data_length);
    if (storage_data == NULL) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    psa_format_key_data_for_storage(data, data2, data_length, attr, assetPolicy, storage_data);

    status = psa_crypto_storage_store(attr->MBEDTLS_PRIVATE(id),
                                      storage_data, storage_data_length);

    /* Free the storage_data from the cache now to limit fragmentation */
    memset(storage_data, 0, storage_data_length);

    psaInt_mbedtls_free(storage_data);

    /* After storing to persistent storage, also save the key and its attributes in
     * the cache
     */
    if (status == PSA_SUCCESS)
    {
        memcpy(&pEntry->attributes, attr, sizeof(psa_key_attributes_t));

        pEntry->key = psaInt_mbedtls_calloc(1, data_length);

        if (NULL == pEntry->key)
        {
            status = PSA_ERROR_INSUFFICIENT_MEMORY;
        }
        else
        {
            (void)memcpy(pEntry->key, data, data_length);

            if (NULL != data2)
            {
                pEntry->key2 = psaInt_mbedtls_calloc(1, data_length);

                if (NULL == pEntry->key2)
                {
                    status = PSA_ERROR_INSUFFICIENT_MEMORY;
                }
                else
                {
                    (void)memcpy(pEntry->key2, data2, data_length);
                }
            }
        }
    }

    return status;
}

psa_status_t psa_load_persistent_key_into_slot(const mbedtls_svc_key_id_t key,
                                               psa_key_context_t * pEntry)
{
    psa_status_t status = PSA_SUCCESS;
    uint8_t *loaded_data;
    size_t storage_data_length = 0;

    status = psa_crypto_storage_get_data_length(key, &storage_data_length);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* Allocate the storage_format struct to read from ITS */
    loaded_data = psaInt_mbedtls_calloc(1, storage_data_length);

    if (loaded_data == NULL) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    /* Read from ITS the storage_format struct and place it into loaded_data */
    status = psa_crypto_storage_load(key, loaded_data, storage_data_length);
    if (status != PSA_SUCCESS) {
        goto exit;
    }

    /* Populate pEntry with the key material and key metadata that has been loaded from ITS.
     * pEntry->key will be dynamically allocated here.
     */
    status = psa_parse_key_data_from_storage(loaded_data, storage_data_length,
                                             &pEntry->key, &pEntry->key2, &pEntry->key_size,
                                             &pEntry->attributes, &pEntry->AssetPolicy);

#if defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)
    pEntry->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id) = key.MBEDTLS_PRIVATE(key_id);
    pEntry->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner) = key.MBEDTLS_PRIVATE(owner);
#else
    pEntry->attributes.MBEDTLS_PRIVATE(id) = key;
#endif

    /* All keys saved to persistent storage always have a key context */
    if (status == PSA_SUCCESS &&
        (pEntry->key == NULL || pEntry->key_size == 0)) {
        status = PSA_ERROR_STORAGE_FAILURE;
    }

exit:
    memset(loaded_data, 0, storage_data_length);

    psaInt_mbedtls_free(loaded_data);

    return status;
}
