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

/* TI Customizations: Changed API parameters to take in key context struct. Used subset of
 * mbedTLS APIs in their file of the same name. Other APIs are used as static functions 
 * in the source file, since they did not need to be exposed. Modified API names.
 */

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>  // uint8_t, uint16_t, uint32_t, uint64_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>             // psa_status_t, psa_key_id_t, psa_key_context_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h> // psa_key_context_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/storage_common.h> // psa_storage_uid_t
/* Limit the maximum key size in storage. This should have no effect
 * since the key size is limited in memory. */
#define PSA_CRYPTO_MAX_STORAGE_SIZE (PSA_BITS_TO_BYTES(PSA_MAX_KEY_BITS))

/**
 * \brief Retrieve an ITS file identifier for a given key ID.
 *
 * This function returns the ITS file identifier that should be
 * provided to the psa_its_xxx() APIs for a given key ID.
 *
 * \param key           Persistent identifier to retrieve for.
 *
 * \retval              ITS File identifier.
 */
psa_storage_uid_t psa_its_identifier_of_slot(mbedtls_svc_key_id_t key);

/**
 * \brief Checks if persistent data is stored for the given key slot number
 *
 * This function checks if any key data or metadata exists for the key slot in
 * the persistent storage.
 *
 * \param key           Persistent identifier to check.
 *
 * \retval 0
 *         No persistent data present for slot number
 * \retval 1
 *         Persistent data present for slot number
 */
int psa_is_key_present_in_storage(const mbedtls_svc_key_id_t key);

/**
 * \brief Format key data and metadata and save to a location for given key
 *        slot.
 *
 * This function formats the key data and metadata and saves it to a
 * persistent storage backend. The storage location corresponding to the
 * key slot must be empty, otherwise this function will fail. This function
 * should be called after loading the key into an internal slot to ensure the
 * persistent key is not saved into a storage location corresponding to an
 * already occupied non-persistent key, as well as ensuring the key data is
 * validated.
 *
 * Note: This function will only succeed for key buffers which are not
 * empty. If passed a NULL pointer or zero-length, the function will fail
 * with #PSA_ERROR_INVALID_ARGUMENT.
 *
 * \param[in] attr          The attributes of the key to save.
 *                          The key identifier field in the attributes
 *                          determines the key's location.
 * \param[in] data          Buffer containing the key data or a key blob.
 * \param[in] data2         Buffer containing a key blob wrapped around the same
 *                          material as #data, but with an asset policy for decryption.
 *                          Only necessary for symmetric, wrapped keys.
 * \param[in] data_length   The number of bytes that make up the key data.
 *
 * \retval #PSA_SUCCESS \emptydescription
 * \retval #PSA_ERROR_INVALID_ARGUMENT \emptydescription
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY \emptydescription
 * \retval #PSA_ERROR_INSUFFICIENT_STORAGE \emptydescription
 * \retval #PSA_ERROR_STORAGE_FAILURE \emptydescription
 * \retval #PSA_ERROR_ALREADY_EXISTS \emptydescription
 * \retval #PSA_ERROR_DATA_INVALID \emptydescription
 * \retval #PSA_ERROR_DATA_CORRUPT \emptydescription
 */
psa_status_t psa_save_persistent_key(psa_key_context_t * pEntry,
                                     const psa_key_attributes_t *attr,
                                     const PsaPolicyMask_t *assetPolicy,
                                     const uint8_t *data,
                                     const uint8_t *data2,
                                     const size_t data_length);


/**
 * \brief Retrieve key data and metadata and save to given key slot.
 * 
 * This function retrieves the key data and metadata from ITS in the expected 
 * format from the persistent storage backend. The provided key entry must be empty
 * with a NULL pointer to key data, as it will be allocated within this function.  
 *
 * \param[in] key           
 * \param[in] pEntry          Buffer containing the key data.
 */
psa_status_t psa_load_persistent_key_into_slot(const mbedtls_svc_key_id_t key,
                                               psa_key_context_t * pEntry);                                     