/*
 *  Copyright The Mbed TLS Contributors
 *  Copyright (c) 2026 Texas Instruments Incorporated
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

/**
 * @file ti_psa_crypto_cipher_types.h
 * @brief Type definitions for the TI PSA cipher driver context.
 *
 * This header is separated from ti_psa_crypto_cipher.h to break the circular
 * include dependency with mbedTLS psa/crypto.h. It provides only the struct
 * and typedef needed by crypto_driver_contexts_primitives.h, without requiring
 * psa_cipher_operation_t (which is defined later in crypto.h).
 */

#ifndef TI_PSA_CRYPTO_CIPHER_TYPES_H
#define TI_PSA_CRYPTO_CIPHER_TYPES_H

#include <stddef.h>
#include <stdint.h>

#include <psa/crypto_types.h>
#include <psa/crypto_sizes.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/devices/DeviceFamily.h>
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #include <ti/drivers/aesecb/AESECBXXF3.h>
    #include <ti/drivers/aescbc/AESCBCXXF3.h>
    #include <ti/drivers/aesctr/AESCTRXXF3.h>
#elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
       (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
    #include <ti/drivers/aesecb/AESECBCC26XX.h>
    #include <ti/drivers/aescbc/AESCBCCC26XX.h>
    #include <ti/drivers/aesctr/AESCTRCC26XX.h>
#else
    #error "Device family not currently supported"
#endif

struct ti_psa_cipher_operation_s
{
    union
    {
        struct
        {
            AESECB_Config aesecbConfig;
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
            AESECBXXF3_Object aesecbObject;
#elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
       (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
            AESECBCC26XX_Object aesecbObject;
#else
    #error "Device family not currently supported"
#endif
        } aesecb;
        struct
        {
            AESCBC_Config aescbcConfig;
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
            AESCBCXXF3_Object aescbcObject;
#elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
       (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
            AESCBCCC26XX_Object aescbcObject;
#else
    #error "Device family not currently supported"
#endif
        } aescbc;
        struct
        {
            AESCTR_Config aesctrConfig;
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
            AESCTRXXF3_Object aesctrObject;
#elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
       (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
            AESCTRCC26XX_Object aesctrObject;
#else
    #error "Device family not currently supported"
#endif
        } aesctr;
        /* Add other driver structs here as needed */
    } driver;
    /* Used to mark the operation struct as ready.*/
    unsigned int id;
    unsigned int iv_required:1;
    unsigned int iv_set:1;
    unsigned int is_encrypt:1;
    unsigned int in_error_state:1;
    size_t default_iv_length;
    psa_algorithm_t alg;

    /** Number of bytes that have not been processed yet */
    size_t unprocessed_len;

    /* Buffer for data that has not been processed yet. Word-aligned for max
     * performance and in case any drivers require aligned input buffer.
     * Double-buffer is used when PSA crypto is built into the TFM to prevent
     * corruption before the data can be consumed since the underlying crypto
     * drivers are used in callback mode. */
#ifdef TFM_BUILD
    uint8_t unprocessed_data[PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE * 2] __attribute__((aligned(4)));
#else
    uint8_t unprocessed_data[PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE] __attribute__((aligned(4)));
#endif /* TFM_BUILD */

    /* Pointer to the current unprocessed data */
    uint8_t *curr_unprocessed_data;

    CryptoKey cryptoKey;
};

typedef struct ti_psa_cipher_operation_s ti_psa_cipher_operation_t;

#define TI_PSA_CIPHER_OPERATION_INIT \
    (ti_psa_cipher_operation_t)      \
    {                                \
        0                            \
    }

#endif /* TI_PSA_CRYPTO_CIPHER_TYPES_H */
