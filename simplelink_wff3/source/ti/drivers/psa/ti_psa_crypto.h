/*
 *  Copyright The Mbed TLS Contributors
 *  Copyright 2025, Texas Instruments Incorporated
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
 *
 *  Modified by Texas Instruments to support SimpleLink device crypto hardware
 *  drivers.
 */

#ifndef TI_PSA_CRYPTO_H
#define TI_PSA_CRYPTO_H

#include <stddef.h>
#include <stdint.h>

#if ((TFM_ENABLED == 1) && !defined(TFM_BUILD))
    #include <third_party/tfm/interface/include/psa/crypto.h>
#else
    #include <third_party/mbedtls/include/psa/crypto.h>
#endif

typedef enum
{
    AES_ENCRYPT = 0,
    AES_DECRYPT
} aes_operation_t;

/******************************************************************************/
/* Key management */
/******************************************************************************/
psa_status_t ti_psa_copy_key(mbedtls_svc_key_id_t source_key,
                             const psa_key_attributes_t *attributes,
                             mbedtls_svc_key_id_t *target_key);

psa_status_t ti_psa_destroy_key(mbedtls_svc_key_id_t key);

psa_status_t ti_psa_export_key(mbedtls_svc_key_id_t key, uint8_t *data, size_t data_size, size_t *data_length);

psa_status_t ti_psa_export_public_key(mbedtls_svc_key_id_t key, uint8_t *data, size_t data_size, size_t *data_length);

psa_status_t ti_psa_generate_key(const psa_key_attributes_t *attributes, mbedtls_svc_key_id_t *key);

psa_status_t ti_psa_get_key_attributes(mbedtls_svc_key_id_t key, psa_key_attributes_t *attributes);

psa_status_t ti_psa_import_key(const psa_key_attributes_t *attributes,
                               const uint8_t *data,
                               size_t data_length,
                               mbedtls_svc_key_id_t *key);

psa_status_t ti_psa_purge_key(mbedtls_svc_key_id_t key);

void ti_psa_reset_key_attributes(psa_key_attributes_t *attributes);

/******************************************************************************/
/* Asymmetric cryptography */
/******************************************************************************/
psa_status_t ti_psa_asymmetric_encrypt(mbedtls_svc_key_id_t key,
                                       psa_algorithm_t alg,
                                       const uint8_t *input,
                                       size_t input_length,
                                       const uint8_t *salt,
                                       size_t salt_length,
                                       uint8_t *output,
                                       size_t output_size,
                                       size_t *output_length);

psa_status_t ti_psa_asymmetric_decrypt(mbedtls_svc_key_id_t key,
                                       psa_algorithm_t alg,
                                       const uint8_t *input,
                                       size_t input_length,
                                       const uint8_t *salt,
                                       size_t salt_length,
                                       uint8_t *output,
                                       size_t output_size,
                                       size_t *output_length);

psa_status_t ti_psa_sign_message(mbedtls_svc_key_id_t key,
                                 psa_algorithm_t alg,
                                 const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *signature,
                                 size_t signature_size,
                                 size_t *signature_length);

psa_status_t ti_psa_verify_message(mbedtls_svc_key_id_t key,
                                   psa_algorithm_t alg,
                                   const uint8_t *input,
                                   size_t input_length,
                                   const uint8_t *signature,
                                   size_t signature_length);

psa_status_t ti_psa_sign_hash(mbedtls_svc_key_id_t key,
                              psa_algorithm_t alg,
                              const uint8_t *hash,
                              size_t hash_length,
                              uint8_t *signature,
                              size_t signature_size,
                              size_t *signature_length);

psa_status_t ti_psa_verify_hash(mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg,
                                const uint8_t *hash,
                                size_t hash_length,
                                const uint8_t *signature,
                                size_t signature_length);

/******************************************************************************/
/* Key Derivation */
/******************************************************************************/
psa_status_t ti_psa_key_derivation_abort(psa_key_derivation_operation_t *operation);

psa_status_t ti_psa_key_derivation_get_capacity(const psa_key_derivation_operation_t *operation, size_t *capacity);

psa_status_t ti_psa_key_derivation_input_bytes(psa_key_derivation_operation_t *operation,
                                               psa_key_derivation_step_t step,
                                               const uint8_t *data,
                                               size_t data_length);

psa_status_t ti_psa_key_derivation_input_integer(psa_key_derivation_operation_t *operation,
                                                 psa_key_derivation_step_t step,
                                                 uint64_t value);

psa_status_t ti_psa_key_derivation_input_key(psa_key_derivation_operation_t *operation,
                                             psa_key_derivation_step_t step,
                                             mbedtls_svc_key_id_t key);

psa_status_t ti_psa_key_derivation_output_bytes(psa_key_derivation_operation_t *operation,
                                                uint8_t *output,
                                                size_t output_length);

psa_status_t ti_psa_key_derivation_output_key(const psa_key_attributes_t *attributes,
                                              psa_key_derivation_operation_t *operation,
                                              mbedtls_svc_key_id_t *key);

psa_status_t ti_psa_key_derivation_set_capacity(psa_key_derivation_operation_t *operation, size_t capacity);

psa_status_t ti_psa_key_derivation_setup(psa_key_derivation_operation_t *operation, psa_algorithm_t alg);

psa_status_t ti_psa_key_derivation_verify_bytes(psa_key_derivation_operation_t *operation,
                                                const uint8_t *expected_output,
                                                size_t output_length);

psa_status_t ti_psa_key_derivation_verify_key(psa_key_derivation_operation_t *operation, mbedtls_svc_key_id_t expected);

/******************************************************************************/
/* Key Agreement */
/******************************************************************************/
psa_status_t ti_psa_raw_key_agreement(psa_algorithm_t alg,
                                      mbedtls_svc_key_id_t private_key,
                                      const uint8_t *peer_key,
                                      size_t peer_key_length,
                                      uint8_t *output,
                                      size_t output_size,
                                      size_t *output_length);

psa_status_t ti_psa_key_derivation_key_agreement(psa_key_derivation_operation_t *operation,
                                                 psa_key_derivation_step_t step,
                                                 mbedtls_svc_key_id_t private_key,
                                                 const uint8_t *peer_key,
                                                 size_t peer_key_length);

#endif /* TI_PSA_CRYPTO_H */