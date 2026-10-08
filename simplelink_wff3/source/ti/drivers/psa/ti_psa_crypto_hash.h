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

#ifndef TI_PSA_CRYPTO_HASH_H
#define TI_PSA_CRYPTO_HASH_H

#include <stddef.h>
#include <stdint.h>

#include <ti/drivers/psa/ti_psa_crypto_hash_types.h>

#if ((TFM_ENABLED == 1) && !defined(TFM_BUILD))
    #include <third_party/tfm/interface/include/psa/crypto.h>
#else
    #include <third_party/mbedtls/include/psa/crypto.h>
#endif

static inline struct ti_psa_hash_operation_s ti_psa_hash_operation_init(void)
{
    const struct ti_psa_hash_operation_s v = TI_PSA_HASH_OPERATION_INIT;
    return (v);
}

/******************************************************************************/
/* Multi-step hash operations */
/******************************************************************************/
psa_status_t ti_psa_hash_abort(psa_hash_operation_t *psa_operation);

psa_status_t ti_psa_hash_resume(psa_hash_operation_t *psa_operation,
                                const uint8_t *hash_state,
                                size_t hash_state_length);

psa_status_t ti_psa_hash_setup(psa_hash_operation_t *psa_operation, psa_algorithm_t alg);

psa_status_t ti_psa_hash_suspend(psa_hash_operation_t *psa_operation,
                                 uint8_t *hash_state,
                                 size_t hash_state_size,
                                 size_t *hash_state_length);

psa_status_t ti_psa_hash_update(psa_hash_operation_t *psa_operation, const uint8_t *input, size_t input_length);

psa_status_t ti_psa_hash_finish(psa_hash_operation_t *psa_operation,
                                uint8_t *hash,
                                size_t hash_size,
                                size_t *hash_length);

/******************************************************************************/
/* One-step hash operations */
/******************************************************************************/
psa_status_t ti_psa_hash_clone(const psa_hash_operation_t *source_operation, psa_hash_operation_t *target_operation);

psa_status_t ti_psa_hash_compare(psa_algorithm_t alg,
                                 const uint8_t *input,
                                 size_t input_length,
                                 const uint8_t *hash,
                                 size_t hash_length);

psa_status_t ti_psa_hash_compute(psa_algorithm_t alg,
                                 const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *hash,
                                 size_t hash_size,
                                 size_t *hash_length);

psa_status_t ti_psa_hash_verify(psa_hash_operation_t *psa_operation, const uint8_t *hash, size_t hash_length);

#endif /* TI_PSA_CRYPTO_HASH_H */
