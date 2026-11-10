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
 * @file ti_psa_crypto_hash_types.h
 * @brief Type definitions for the TI PSA hash driver context.
 *
 * Separated from ti_psa_crypto_hash.h to break circular include dependency
 * with mbedTLS psa/crypto.h. See ti_psa_crypto_cipher_types.h for details.
 */

#ifndef TI_PSA_CRYPTO_HASH_TYPES_H
#define TI_PSA_CRYPTO_HASH_TYPES_H

#include <stddef.h>
#include <stdint.h>

#include <psa/crypto_types.h>
#include <psa/crypto_sizes.h>
#include <ti/devices/DeviceFamily.h>
#include <ti/drivers/SHA2.h>
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #include <ti/drivers/sha2/SHA2XXF3HSM.h>
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2)
    #include <ti/drivers/sha2/SHA2CC26X2.h>
#else
    #error "Device family not currently supported"
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    #include <ti/drivers/SHA3.h>
    #include <ti/drivers/sha3/SHA3XXF3HSM.h>
#endif

/**
 * Returns the number of bytes of the input length field for a SHA2 alg.
 * Returns zero if the alg is not SHA2.
 */
#define PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(alg)             \
    (((alg == PSA_ALG_SHA_224) || (alg == PSA_ALG_SHA_256))   ? 8u  \
     : ((alg == PSA_ALG_SHA_384) || (alg == PSA_ALG_SHA_512)) ? 16u \
                                                              : 0u)

/**
 * Returns the number of bytes of the hash suspend state field for a SHA2 alg.
 * Returns zero if the alg is not SHA2.
 */
#define PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(alg)               \
    (((alg == PSA_ALG_SHA_224) || (alg == PSA_ALG_SHA_256))   ? 32u \
     : ((alg == PSA_ALG_SHA_384) || (alg == PSA_ALG_SHA_512)) ? 64u \
                                                              : 0u)

struct ti_psa_hash_operation_s
{
    /* Driver config struct - pointer to this is referred to as the driver handle */
    SHA2_Config sha2Config;
    /* Driver object */
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    SHA2XXF3HSM_Object sha2Object;
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2)
    SHA2CC26X2_Object sha2Object;
#else
    #error "Device family not currently supported"
#endif
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    SHA3_Config sha3Config;
    SHA3XXF3HSM_Object sha3Object;
#endif
    /* Used to mark the operation struct as ready.*/
    unsigned int id;
    /* alg identifier */
    psa_algorithm_t alg;
};

typedef struct ti_psa_hash_operation_s ti_psa_hash_operation_t;

#define TI_PSA_HASH_OPERATION_INIT \
    (ti_psa_hash_operation_t)      \
    {                              \
        0                          \
    }

#endif /* TI_PSA_CRYPTO_HASH_TYPES_H */
