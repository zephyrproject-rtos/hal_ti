/*
 *  Copyright (c) 2022-2026 Texas Instruments Incorporated
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

#ifndef TI_PSA_CRYPTO_HELPER_H
#define TI_PSA_CRYPTO_HELPER_H

#include <stdbool.h>
#include <stdint.h>

#include <ti/devices/DeviceFamily.h>
#if ((TFM_ENABLED == 1) && !defined(TFM_BUILD))
    #include <third_party/tfm/interface/include/psa/crypto.h>
#else
    #include <third_party/mbedtls/include/psa/crypto.h>
#endif

#include <ti/drivers/cryptoutils/ecc/ECCParams.h>

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #include <ti/drivers/ECDH.h>
    #include <ti/drivers/ECDSA.h>
#endif

/* Includes for mbedTLS content */
/* psa_crypto_local_input_t etc */
#if (TI_SW_CRYPTO_ENABLED == 1)
    #include <third_party/mbedtls/library/psa_crypto_core.h>
    #include <third_party/mbedtls/include/psa/build_info.h>
#endif

/* Identifiers for S-only PSA operations to determine if a given operation
 * is using the TI HW acceleration, or if it began with the mbedTLS SW
 * implementation.
 */
#define PSA_CRYPTO_TI_DRIVER_ID       1
#define PSA_CRYPTO_MBED_TLS_DRIVER_ID 2

/* Includes for mbedTLS content */
/* psa_crypto_local_input_t etc */
#if (TI_SW_CRYPTO_ENABLED == 1)
    #include <third_party/mbedtls/library/psa_crypto_core.h>
    #include <third_party/mbedtls/include/psa/build_info.h>
#endif

/* Identifiers for S-only PSA operations to determine if a given operation
 * is using the TI HW acceleration, or if it began with the mbedTLS SW
 * implementation.
 */
#define PSA_CRYPTO_TI_DRIVER_ID       1
#define PSA_CRYPTO_MBED_TLS_DRIVER_ID 2

/* Error mapping functions. These functions take as input SimpleLink driver
 * error codes and maps them to nearest PSA error code.
 */
psa_status_t map_AES_status(int_fast16_t status);
psa_status_t map_ECDH_status(int_fast16_t status);
psa_status_t map_ECDSA_status(int_fast16_t status, bool isVerifyOp);
psa_status_t map_EDDSA_status(int_fast16_t status, bool isVerifyOp);
psa_status_t map_RNG_status(int_fast16_t status);
psa_status_t map_SHA2_status(int_fast16_t status);
psa_status_t map_TRNG_status(int_fast16_t status);

/* Convert to and from the keyID format expected by the SimpleLink KeyStore API */
psa_key_id_t toKeyID(mbedtls_svc_key_id_t keystoreKeyID);
mbedtls_svc_key_id_t toKeyStoreKeyID(psa_key_id_t keyID);

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
/* Maps PSA ECC key types to their corresponding ECDSA Curve Type for HSM.
 * Assumes that the keyType is some form of ECC key type. Returns 0 if could not
 * find a mapping.
 */
ECDSA_CurveType map_keyTypeToECDSACurveTypeHSM(psa_key_type_t keyType, size_t keyBits);

/* Maps PSA ECC key types to their corresponding ECDH Curve Type for HSM.
 * Assumes that the keyType is some form of ECC key type. Returns 0 if could not
 * find a mapping.
 */
ECDH_CurveType map_keyTypeToECDHCurveTypeHSM(psa_key_type_t keyType, size_t keyBits);
#endif

/* Maps PSA ECC key types to their corresponding ECCParams_CurveParams struct
 * pointer. Assumes that the keyType is some form of ECC key type. Returns NULL
 * if could not find a mapping.
 */
const ECCParams_CurveParams *map_keyTypeToECCParams(psa_key_type_t keyType, size_t keyBits);

bool isHardwareAccelerated(psa_algorithm_t alg);
/* For type-safety, the following APIs have not been combined into one. The
 * operation ID would have to be stored at the same offset in each operation
 * struct for use of a void pointer to work.
 */
void setAeadOperationID(psa_aead_operation_t *operation, unsigned int id);
void setCipherOperationID(psa_cipher_operation_t *operation, unsigned int id);
void setHashOperationID(psa_hash_operation_t *operation, unsigned int id);
void setKeyDerivationOperationID(psa_key_derivation_operation_t *operation, unsigned int id);
void setMacOperationID(psa_mac_operation_t *operation, unsigned int id);

bool isHardwareAeadOperation(const psa_aead_operation_t *operation);
bool isHardwareCipherOperation(const psa_cipher_operation_t *operation);
bool isHardwareHashOperation(const psa_hash_operation_t *operation);
bool isHardwareKeyDerivationOperation(const psa_key_derivation_operation_t *operation);
bool isHardwareMacOperation(const psa_mac_operation_t *operation);

#if (TI_SW_CRYPTO_ENABLED == 1)
    #if !defined(MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS)

        /* Declare a local copy of an input buffer and a variable that will be used
         * to store a pointer to the start of the buffer.
         *
         * Note: This macro must be called before any operations which may jump to
         * the exit label, so that the local input copy object is safe to be freed.
         *
         * Assumptions:
         * - input is the name of a pointer to the buffer to be copied
         * - The name LOCAL_INPUT_COPY_OF_input is unused in the current scope
         * - input_copy_name is a name that is unused in the current scope
         */
        #define LOCAL_INPUT_DECLARE(input, input_copy_name)                                     \
            psa_crypto_local_input_t LOCAL_INPUT_COPY_OF_##input = PSA_CRYPTO_LOCAL_INPUT_INIT; \
            const uint8_t *input_copy_name                       = NULL;

        /* Allocate a copy of the buffer input and set the pointer input_copy to
         * point to the start of the copy.
         *
         * Assumptions:
         * - psa_status_t status exists
         * - An exit label is declared
         * - input is the name of a pointer to the buffer to be copied
         * - LOCAL_INPUT_DECLARE(input, input_copy) has previously been called
         */
        #define LOCAL_INPUT_ALLOC(input, length, input_copy)                                    \
            status = psa_crypto_local_input_alloc(input, length, &LOCAL_INPUT_COPY_OF_##input); \
            if (status != PSA_SUCCESS)                                                          \
            {                                                                                   \
                goto exit;                                                                      \
            }                                                                                   \
            input_copy = LOCAL_INPUT_COPY_OF_##input.buffer;

        /* Free the local input copy allocated previously by LOCAL_INPUT_ALLOC()
         *
         * Assumptions:
         * - input_copy is the name of the input copy pointer set by LOCAL_INPUT_ALLOC()
         * - input is the name of the original buffer that was copied
         */
        #define LOCAL_INPUT_FREE(input, input_copy) \
            input_copy = NULL;                      \
            psa_crypto_local_input_free(&LOCAL_INPUT_COPY_OF_##input);

        /* Declare a local copy of an output buffer and a variable that will be used
         * to store a pointer to the start of the buffer.
         *
         * Note: This macro must be called before any operations which may jump to
         * the exit label, so that the local output copy object is safe to be freed.
         *
         * Assumptions:
         * - output is the name of a pointer to the buffer to be copied
         * - The name LOCAL_OUTPUT_COPY_OF_output is unused in the current scope
         * - output_copy_name is a name that is unused in the current scope
         */
        #define LOCAL_OUTPUT_DECLARE(output, output_copy_name)                                      \
            psa_crypto_local_output_t LOCAL_OUTPUT_COPY_OF_##output = PSA_CRYPTO_LOCAL_OUTPUT_INIT; \
            uint8_t *output_copy_name                               = NULL;

        /* Allocate a copy of the buffer output and set the pointer output_copy to
         * point to the start of the copy.
         *
         * Assumptions:
         * - psa_status_t status exists
         * - An exit label is declared
         * - output is the name of a pointer to the buffer to be copied
         * - LOCAL_OUTPUT_DECLARE(output, output_copy) has previously been called
         */
        #define LOCAL_OUTPUT_ALLOC(output, length, output_copy)                                     \
            status = psa_crypto_local_output_alloc(output, length, &LOCAL_OUTPUT_COPY_OF_##output); \
            if (status != PSA_SUCCESS)                                                              \
            {                                                                                       \
                goto exit;                                                                          \
            }                                                                                       \
            output_copy = LOCAL_OUTPUT_COPY_OF_##output.buffer;

        /* Free the local output copy allocated previously by LOCAL_OUTPUT_ALLOC()
         * after first copying back its contents to the original buffer.
         *
         * Assumptions:
         * - psa_status_t status exists
         * - output_copy is the name of the output copy pointer set by LOCAL_OUTPUT_ALLOC()
         * - output is the name of the original buffer that was copied
         */
        #define LOCAL_OUTPUT_FREE(output, output_copy)                                              \
            output_copy = NULL;                                                                     \
            do                                                                                      \
            {                                                                                       \
                psa_status_t local_output_status;                                                   \
                local_output_status = psa_crypto_local_output_free(&LOCAL_OUTPUT_COPY_OF_##output); \
                if (local_output_status != PSA_SUCCESS)                                             \
                {                                                                                   \
                    /* Since this error case is an internal error, it's more serious than           \
                     * any existing error code and so it's fine to overwrite the existing           \
                     * status. */                                                                   \
                    status = local_output_status;                                                   \
                }                                                                                   \
            } while (0)
    #else /* !MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS */
        #define LOCAL_INPUT_DECLARE(input, input_copy_name)     const uint8_t *input_copy_name = NULL;
        #define LOCAL_INPUT_ALLOC(input, length, input_copy)    input_copy = input;
        #define LOCAL_INPUT_FREE(input, input_copy)             input_copy = NULL;
        #define LOCAL_OUTPUT_DECLARE(output, output_copy_name)  uint8_t *output_copy_name = NULL;
        #define LOCAL_OUTPUT_ALLOC(output, length, output_copy) output_copy = output;
        #define LOCAL_OUTPUT_FREE(output, output_copy)          output_copy = NULL;
    #endif /* !MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS */
#endif     /* TI_SW_CRYPTO_ENABLED == 1 */
#endif     /* TI_PSA_CRYPTO_HELPER_H */
