/*
 *  Copyright The Mbed TLS Contributors
 *  Copyright (c) 2025-2026 Texas Instruments Incorporated
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

#ifndef TI_PSA_CRYPTO_AEAD_H
#define TI_PSA_CRYPTO_AEAD_H

#include <stddef.h>
#include <stdint.h>

#include <ti/drivers/psa/ti_psa_crypto_aead_types.h>

#if ((TFM_ENABLED == 1) && !defined(TFM_BUILD))
    #include <third_party/tfm/interface/include/psa/crypto.h>
#else
    #include <third_party/mbedtls/include/psa/crypto.h>
#endif

static inline struct ti_psa_aead_operation_s ti_psa_aead_operation_init(void)
{
    const struct ti_psa_aead_operation_s v = TI_PSA_AEAD_OPERATION_INIT;
    return (v);
}

/******************************************************************************/
/* Multi-Step AEAD */
/******************************************************************************/
psa_status_t ti_psa_aead_abort(psa_aead_operation_t *psa_operation);

psa_status_t ti_psa_aead_encrypt_setup(psa_aead_operation_t *psa_operation,
                                       mbedtls_svc_key_id_t key,
                                       psa_algorithm_t alg);

psa_status_t ti_psa_aead_decrypt_setup(psa_aead_operation_t *psa_operation,
                                       mbedtls_svc_key_id_t key,
                                       psa_algorithm_t alg);

psa_status_t ti_psa_aead_finish(psa_aead_operation_t *psa_operation,
                                uint8_t *ciphertext,
                                size_t ciphertext_size,
                                size_t *ciphertext_length,
                                uint8_t *tag,
                                size_t tag_size,
                                size_t *tag_length);

psa_status_t ti_psa_aead_update(psa_aead_operation_t *psa_operation,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *output,
                                size_t output_size,
                                size_t *output_length);

psa_status_t ti_psa_aead_update_ad(psa_aead_operation_t *psa_operation, const uint8_t *input, size_t input_length);

/******************************************************************************/
/* One-Step AEAD */
/******************************************************************************/
psa_status_t ti_psa_aead_encrypt(mbedtls_svc_key_id_t key,
                                 psa_algorithm_t alg,
                                 const uint8_t *nonce,
                                 size_t nonce_length,
                                 const uint8_t *additional_data,
                                 size_t additional_data_length,
                                 const uint8_t *plaintext,
                                 size_t plaintext_length,
                                 uint8_t *ciphertext,
                                 size_t ciphertext_size,
                                 size_t *ciphertext_length);

psa_status_t ti_psa_aead_decrypt(mbedtls_svc_key_id_t key,
                                 psa_algorithm_t alg,
                                 const uint8_t *nonce,
                                 size_t nonce_length,
                                 const uint8_t *additional_data,
                                 size_t additional_data_length,
                                 const uint8_t *ciphertext,
                                 size_t ciphertext_length,
                                 uint8_t *plaintext,
                                 size_t plaintext_size,
                                 size_t *plaintext_length);

psa_status_t ti_psa_aead_generate_nonce(psa_aead_operation_t *psa_operation,
                                        uint8_t *nonce,
                                        size_t nonce_size,
                                        size_t *nonce_length);

psa_status_t ti_psa_aead_set_lengths(psa_aead_operation_t *psa_operation, size_t ad_length, size_t plaintext_length);

psa_status_t ti_psa_aead_set_nonce(psa_aead_operation_t *psa_operation, const uint8_t *nonce, size_t nonce_length);

psa_status_t ti_psa_aead_verify(psa_aead_operation_t *psa_operation,
                                uint8_t *plaintext,
                                size_t plaintext_size,
                                size_t *plaintext_length,
                                const uint8_t *tag,
                                size_t tag_length);

#endif /* TI_PSA_CRYPTO_AEAD_H */
