/*
 * Copyright (c) 2025, Texas Instruments Incorporated
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
/*
 *  Copyright The Mbed TLS Contributors
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

#ifndef INCLUDE_GUARD_ADAPTER_PSA_KEY_DERIVATION_H
#define INCLUDE_GUARD_ADAPTER_PSA_KEY_DERIVATION_H
#include <stdint.h>
#include <stdbool.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>          // configuration

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PSA_KDF_LABEL_MAX_SIZE
#define PSA_KDF_LABEL_MAX_SIZE       (224U - 20U)
#endif

/* The structure and initialization for TI-specific key derivation operation(s).
 * The top-level psa_key_derivation_s struct will hold a context that is this
 * TI-specific struct.
 */
struct KeyMgmt_psa_key_derivation_s
{
    psa_algorithm_t alg;
    mbedtls_svc_key_id_t inputKey;
    /* Should be at least 53 bytes of label data. Has to also fit an end marker
     * between the label and the context, which is 1 byte (0x00). It should also
     * fit four bytes for the length of the key to derive.
     */
    uint8_t fixedInputData[PSA_KDF_LABEL_MAX_SIZE];
    size_t labelSize;
    size_t contextSize;
    uint32_t handle;
    uint32_t capacity;
    bool canDerive;
    bool capacitySet;
};

typedef struct KeyMgmt_psa_key_derivation_s KeyMgmt_psa_key_derivation_operation_t;

#define KEYMGMT_PSA_KEY_DERIVATION_OPERATION_INIT {0, MBEDTLS_SVC_KEY_ID_INIT, {0}, 0, 0, 0, 0, false, false}
static inline struct KeyMgmt_psa_key_derivation_s
KeyMgmt_psa_key_derivation_operation_init(void)
{
    const struct KeyMgmt_psa_key_derivation_s v = KEYMGMT_PSA_KEY_DERIVATION_OPERATION_INIT;
    return (v);
}

/* KeyMgmt_psa_key_derivation APIs */
psa_status_t
KeyMgmt_psa_key_derivation_setup(KeyMgmt_psa_key_derivation_operation_t * operation,
                                 psa_algorithm_t alg);

psa_status_t
KeyMgmt_psa_key_derivation_get_capacity(const KeyMgmt_psa_key_derivation_operation_t *operation,
                                        size_t *capacity);

psa_status_t
KeyMgmt_psa_key_derivation_set_capacity(KeyMgmt_psa_key_derivation_operation_t * operation,
                                        size_t capacity);

psa_status_t
KeyMgmt_psa_key_derivation_input_bytes(KeyMgmt_psa_key_derivation_operation_t * operation,
                                       psa_key_derivation_step_t step,
                                       const uint8_t * data,
                                       size_t data_length);

psa_status_t
KeyMgmt_psa_key_derivation_input_integer(KeyMgmt_psa_key_derivation_operation_t * operation,
                                         psa_key_derivation_step_t step,
                                         uint64_t value);

psa_status_t
KeyMgmt_psa_key_derivation_input_key(KeyMgmt_psa_key_derivation_operation_t * operation,
                                     psa_key_derivation_step_t step,
                                     mbedtls_svc_key_id_t key);

psa_status_t
KeyMgmt_psa_key_derivation_output_bytes(KeyMgmt_psa_key_derivation_operation_t * operation,
                                        uint8_t * output,
                                        size_t output_length);

psa_status_t
KeyMgmt_psa_key_derivation_output_key(const psa_key_attributes_t * attributes,
                                      KeyMgmt_psa_key_derivation_operation_t * operation,
                                      mbedtls_svc_key_id_t * key);

psa_status_t
KeyMgmt_psa_key_derivation_verify_bytes(KeyMgmt_psa_key_derivation_operation_t * operation,
                                        const uint8_t *expected_output,
                                        size_t output_length);

psa_status_t
KeyMgmt_psa_key_derivation_verify_key(KeyMgmt_psa_key_derivation_operation_t * operation,
                                      mbedtls_svc_key_id_t expected);

psa_status_t
KeyMgmt_psa_key_derivation_abort(KeyMgmt_psa_key_derivation_operation_t * operation);

psa_status_t
KeyMgmt_psa_key_derivation_key_agreement(KeyMgmt_psa_key_derivation_operation_t * operation,
                                         psa_key_derivation_step_t step,
                                         mbedtls_svc_key_id_t private_key,
                                         const uint8_t * peer_key,
                                         size_t peer_key_length);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_GUARD_ADAPTER_PSA_KEY_DERIVATION_H */