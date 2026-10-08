/*
 *  Copyright The Mbed TLS Contributors
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
 *
 *  Modified by Texas Instruments to support SimpleLink device crypto hardware
 *  drivers.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include <ti/devices/DeviceFamily.h>

#include <ti/drivers/psa/ti_psa_crypto_helper.h>

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
    #include <third_party/psa_crypto/include/psa/crypto.h>
    #include <third_party/psa_crypto/crypto_helper.h>
#else
    #include <third_party/mbedtls/include/psa/crypto.h>
    #include <ti/drivers/psa/ti_psa_crypto.h>
    #include <ti/drivers/psa/ti_psa_crypto_cipher.h>
    #include <ti/drivers/psa/ti_psa_crypto_hash.h>
    #include <ti/drivers/psa/ti_psa_crypto_mac.h>
    #include <ti/drivers/psa/ti_psa_crypto_aead.h>
#endif

#ifdef TFM_BUILD
    #include "config_tfm.h"
#else
    #include <third_party/psa_crypto/crypto_config.h>
#endif

#include <ti/drivers/AESCBC.h>
#include <ti/drivers/AESCCM.h>
#include <ti/drivers/AESCMAC.h>
#include <ti/drivers/AESCTR.h>
#include <ti/drivers/AESECB.h>
#include <ti/drivers/AESGCM.h>
#include <ti/drivers/ECDH.h>
#include <ti/drivers/ECDSA.h>
#include <ti/drivers/EDDSA.h>
#include <ti/drivers/RNG.h>
#include <ti/drivers/SHA2.h>
#include <ti/drivers/TRNG.h>

#include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_init.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKeyPlaintext.h>
#include <ti/drivers/cryptoutils/ecc/ECCParams.h>

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
    #include <ti/drivers/aescbc/AESCBCCC26XX.h>
    #include <ti/drivers/aesccm/AESCCMCC26X4.h>
    #include <ti/drivers/aescmac/AESCMACCC26XX.h>
    #include <ti/drivers/aesctr/AESCTRCC26XX.h>
    #include <ti/drivers/aesecb/AESECBCC26XX.h>
    #include <ti/drivers/aesgcm/AESGCMCC26X4.h>
    #include <ti/drivers/ecdh/ECDHCC26X2.h>
    #include <ti/drivers/ecdsa/ECDSACC26X2.h>
    #include <ti/drivers/eddsa/EDDSACC26X2.h>
    #include <ti/drivers/sha2/SHA2CC26X2.h>
    #include <ti/drivers/trng/TRNGCC26XX.h>
#elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
       (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #include <ti/drivers/aescbc/AESCBCXXF3.h>
    #include <ti/drivers/aesccm/AESCCMXXF3.h>
    #include <ti/drivers/aescmac/AESCMACXXF3.h>
    #include <ti/drivers/aesctr/AESCTRXXF3.h>
    #include <ti/drivers/aesecb/AESECBXXF3.h>
    #include <ti/drivers/aesgcm/AESGCMXXF3HSM.h>
    #include <ti/drivers/ecdh/ECDHXXF3HSM.h>
    #include <ti/drivers/ecdsa/ECDSAXXF3HSM.h>
    #include <ti/drivers/eddsa/EDDSAXXF3HSM.h>
    #include <ti/drivers/rng/RNGXXF3HSM.h>
    #include <ti/drivers/sha2/SHA2XXF3HSM.h>
    #ifdef ENABLE_TI_CRYPTO_SHA3
        #include <ti/drivers/SHA3.h>
        #include <ti/drivers/sha3/SHA3XXF3HSM.h>
    #endif

    #include <ti/drivers/cryptoutils/utils/CryptoUtils.h>
    #include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
    #include <ti/drivers/dpl/SemaphoreP.h>
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_derivation.h>
    #define KeyStore_PSA_initKey KeyStore_PSA_initKeyHSM
#else
    #error "Device family not supported"
#endif

#if (TFM_ENABLED == 0) || defined(TFM_BUILD)
    /* For KeyStore_PSA_init(), KeyStore_acquireLock(), and KeyStore_releaseLock() in secure only build or TFM build */
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
#endif

#if ((TFM_ENABLED == 1) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX))
    #include <ti/drivers/crypto/PSACrypto_s.h>
    #include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>
#endif /* ((TFM_ENABLED == 1) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)) */

/* The PSA Crypto Wrapper is on the NS side for Thor TFM-enabled builds so requires special handling */
#if ((TFM_ENABLED == 1) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
    /* Array for storing the mbedTLS algorithm value of a key before translating
     * to the mbed TLS value in ti_psa_import_key. Used to recover the original
     * algorithm value in ti_psa_get_key_attributes. For now, the application can
     * create only up to ten keys at once on tfm_enabled configurations.
     */
    #define TFM_ENABLED_KEY_STORAGE_LIMIT 10

typedef struct
{
    mbedtls_svc_key_id_t keyID;
    psa_algorithm_t alg;
} psa_key_data_to_reverse_mapping;

static psa_key_data_to_reverse_mapping keyAlgorithms[TFM_ENABLED_KEY_STORAGE_LIMIT];
static uint8_t keyAlgorithmsLength = 0;

#endif /* ((TFM_ENABLED == 1) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)) */

#ifndef PSA_ECC_MAX_CURVE_BITS
    /* SECP_R1_521 is the largest supported curve */
    #define PSA_ECC_MAX_CURVE_BITS 521
#endif

#ifndef PSA_OUTPUT_BUF_SIZE
    #define PSA_OUTPUT_BUF_SIZE PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(PSA_ECC_MAX_CURVE_BITS)
#endif

/* Memory buffer for largest supported generated key, hash, shared secret, or
 * MAC to avoid malloc. Word-aligned to support HSM output buffer address
 * requirement.
 */
static uint8_t localBuf[PSA_OUTPUT_BUF_SIZE] __attribute__((aligned(4)));

#ifdef ENABLE_TI_CRYPTO_RNG
    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
/* Buffer used to byte-swap ECC curve order for key generation */
static uint8_t curveOrder[PSA_BITS_TO_BYTES(PSA_ECC_MAX_CURVE_BITS)] __attribute__((aligned(4)));
    #endif
#endif /* ENABLE_TI_CRYPTO_RNG */

/* The default value of psa_crypto_ns_caller must be false to support S-only builds.
 * For TFM-enabled builds, tfm_crypto_api_dispatcher() will set this flag for each PSA call.
 */
bool psa_crypto_ns_caller = false;

/**
 * Returns 1 if the algorithm is SHA2,
 * Otherwise, returns 0.
 */
#define PSA_ALG_IS_SHA2(alg)                                  \
    ((alg == PSA_ALG_SHA_224 || alg == PSA_ALG_SHA_256)   ? 1 \
     : (alg == PSA_ALG_SHA_384 || alg == PSA_ALG_SHA_512) ? 1 \
                                                          : 0)

/**
 * Returns 1 if the algorithm is SHA3,
 * Otherwise, returns 0.
 */
#define PSA_ALG_IS_SHA3(alg)                                    \
    ((alg == PSA_ALG_SHA3_224 || alg == PSA_ALG_SHA3_256)   ? 1 \
     : (alg == PSA_ALG_SHA3_384 || alg == PSA_ALG_SHA3_512) ? 1 \
                                                            : 0)

typedef enum
{
    PSA_POLLING_MODE = 0,
    PSA_BLOCKING_MODE,
    PSA_CALLBACK_MODE
} psa_return_behavior_t;

/******************************************************************************/
/* Global data, support functions and library management */
/******************************************************************************/

/* Device-specific crypto object mapping */
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))

    #define AESCBC_Object AESCBCCC26XX_Object

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
        #define AESCCM_Object AESCCMCC26X4_Object
        #define AESGCM_Object AESGCMCC26X4_Object
    #else
        #define AESCCM_Object AESCCMCC26XX_Object
        #define AESGCM_Object AESGCMCC26XX_Object
    #endif

    #define AESCMAC_Object AESCMACCC26XX_Object
    #define AESCTR_Object  AESCTRCC26XX_Object
    #define AESECB_Object  AESECBCC26XX_Object
    #define ECDH_Object    ECDHCC26X2_Object
    #define ECDSA_Object   ECDSACC26X2_Object
    #define EDDSA_Object   EDDSACC26X2_Object
    #define SHA2_Object    SHA2CC26X2_Object
    #define TRNG_Object    TRNGCC26XX_Object

#elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
       (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))

    #define AESCBC_Object  AESCBCXXF3_Object
    #define AESCCM_Object  AESCCMXXF3_Object
    #define AESCMAC_Object AESCMACXXF3_Object
    #define AESCTR_Object  AESCTRXXF3_Object
    #define AESECB_Object  AESECBXXF3_Object
    #define AESGCM_Object  AESGCMXXF3HSM_Object
    #define ECDH_Object    ECDHXXF3HSM_Object
    #define ECDSA_Object   ECDSAXXF3HSM_Object
    #define EDDSA_Object   EDDSAXXF3HSM_Object
    #define RNG_Object     RNGXXF3HSM_Object
    #define SHA2_Object    SHA2XXF3HSM_Object
    #define TRNG_Object    TRNGXXF3HSM_Object

#else
    #error "Device family not supported"
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* On CC35XX the HSM can only access internal RAM. If the driver objects are
     * placed in external RAM, and the HSM need to access data in the driver objects
     * then the data need to first be copied to internal RAM. To prevent this,
     * the driver objects will be placed in internal RAM.
     * Note, user input/output data can still be placed in external RAM, and the
     * drivers will then copy the data to/from internal RAM to handle this.
     */
    #define TI_PSA_OBJECT_ATTR __attribute__((section(".internalRAM.bss")))
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) ||                                               \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X1_CC26X1) ||                                                 \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4) ||                                          \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    /* No attributes needed. */
    #define TI_PSA_OBJECT_ATTR
#else
    #error "Device family not currently supported"
#endif

/* SimpleLink crypto driver config structs and their associated device-specific
 * object and HW attributes structs.
 */
#if defined(ENABLE_TI_CRYPTO_TRNG)
static TRNG_Handle trngHandle = NULL;
static TRNG_Config trngConfig;
static TRNG_Object trngObject TI_PSA_OBJECT_ATTR;
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))

    #ifdef ENABLE_TI_CRYPTO_AESCBC
static const AESCBCCC26XX_HWAttrs aescbcHWAttrs = {.intPriority = (~0)};
    #endif

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
        #ifdef ENABLE_TI_CRYPTO_AESCCM
static const AESCCMCC26X4_HWAttrs aesccmHWAttrs = {.intPriority = (~0)};
        #endif
        #ifdef ENABLE_TI_CRYPTO_AESGCM
static const AESGCMCC26X4_HWAttrs aesgcmHWAttrs = {.intPriority = (~0)};
        #endif
    #else /* DeviceFamily_PARENT_CC13X2_CC26X2 */
        #ifdef ENABLE_TI_CRYPTO_AESCCM
static const AESCCMCC26XX_HWAttrs aesccmHWAttrs = {.intPriority = (~0)};
        #endif
        #ifdef ENABLE_TI_CRYPTO_AESGCM
static const AESGCMCC26XX_HWAttrs aesgcmHWAttrs = {.intPriority = (~0)};
        #endif
    #endif

    #ifdef ENABLE_TI_CRYPTO_AESCMAC
static const AESCMACCC26XX_HWAttrs aescmacHWAttrs   = {.intPriority = (~0)};
static const AESCMACCC26XX_HWAttrs aescbcmacHWAttrs = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_AESCTR
static const AESCTRCC26XX_HWAttrs aesctrHWAttrs = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_AESECB
static const AESECBCC26XX_HWAttrs aesecbHWAttrs = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_ECDH
static ECDHCC26X2_HWAttrs ecdhHWAttrs = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_ECDSA
static ECDSACC26X2_HWAttrs ecdsaHWAttrs = {.intPriority = (~0), .trngIntPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_EDDSA
static EDDSACC26X2_HWAttrs eddsaHWAttrs = {.intPriority = (~0), .sha2IntPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_SHA2
static SHA2CC26X2_HWAttrs sha2HWAttrs = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_TRNG
static TRNGCC26XX_HWAttrs trngHWAttrs = {.intPriority = (~0), .swiPriority = 0, .samplesPerCycle = 240000};
    #endif

#elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
       (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))

    #ifdef ENABLE_TI_CRYPTO_AESCBC
static const AESCBCXXF3_HWAttrs aescbcHWAttrs     = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_AESCCM
static const AESCCMXXF3_HWAttrs aesccmHWAttrs     = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_AESCMAC
static const AESCMACXXF3_HWAttrs aescmacHWAttrs   = {.intPriority = (~0)};
static const AESCMACXXF3_HWAttrs aescbcmacHWAttrs = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_AESCTR
static const AESCTRXXF3_HWAttrs aesctrHWAttrs     = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_AESECB
static const AESECBXXF3_HWAttrs aesecbHWAttrs     = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_AESGCM
static const AESGCMXXF3HSM_HWAttrs aesgcmHWAttrs  = {.intPriority = (~0)};
    #endif

    #ifdef ENABLE_TI_CRYPTO_ECDH
static ECDHXXF3HSM_HWAttrs ecdhHWAttrs            = {.reserved1 = 0};
    #endif

    #ifdef ENABLE_TI_CRYPTO_ECDSA
static ECDSAXXF3HSM_HWAttrs ecdsaHWAttrs          = {.dummy = 0};
    #endif

    #ifdef ENABLE_TI_CRYPTO_EDDSA
static EDDSAXXF3HSM_HWAttrs eddsaHWAttrs          = {.reserved1 = 0};
    #endif

    #ifdef ENABLE_TI_CRYPTO_RNG
static RNGXXF3HSM_HWAttrs rngHWAttrs              = {.reserved1 = 0};
    #endif

    #ifdef ENABLE_TI_CRYPTO_SHA2
static SHA2XXF3HSM_HWAttrs sha2HWAttrs            = {.reserved1 = 0};
    #endif

    #ifdef ENABLE_TI_CRYPTO_SHA3
static SHA3XXF3HSM_HWAttrs sha3HWAttrs            = {.reserved1 = 0};
    #endif

#else
    #error "Device family not supported"
#endif

#ifdef TFM_BUILD
/* Crypto Driver Callback Functions */
extern void PSACrypto_s_aescbcHwiCallback(AESCBC_Handle handle,
                                          int_fast16_t returnValue,
                                          AESCBC_OperationUnion *operation,
                                          AESCBC_OperationType operationType);
extern void PSACrypto_s_aesccmHwiCallback(AESCCM_Handle handle,
                                          int_fast16_t returnValue,
                                          AESCCM_OperationUnion *operation,
                                          AESCCM_OperationType operationType);
extern void PSACrypto_s_aescmacHwiCallback(AESCMAC_Handle handle,
                                           int_fast16_t returnValue,
                                           AESCMAC_Operation *operation,
                                           AESCMAC_OperationType operationType);
extern void PSACrypto_s_aescbcmacHwiCallback(AESCMAC_Handle handle,
                                             int_fast16_t returnValue,
                                             AESCMAC_Operation *operation,
                                             AESCMAC_OperationType operationType);
extern void PSACrypto_s_aesctrHwiCallback(AESCTR_Handle handle,
                                          int_fast16_t returnValue,
                                          AESCTR_OperationUnion *operation,
                                          AESCTR_OperationType operationType);
extern void PSACrypto_s_aesecbHwiCallback(AESECB_Handle handle,
                                          int_fast16_t returnValue,
                                          AESECB_Operation *operation,
                                          AESECB_OperationType operationType);
extern void PSACrypto_s_aesgcmHwiCallback(AESGCM_Handle handle,
                                          int_fast16_t returnValue,
                                          AESGCM_OperationUnion *operation,
                                          AESGCM_OperationType operationType);
extern void PSACrypto_s_ecdhHwiCallback(ECDH_Handle handle,
                                        int_fast16_t returnStatus,
                                        ECDH_Operation operation,
                                        ECDH_OperationType operationType);
extern void PSACrypto_s_ecdsaHwiCallback(ECDSA_Handle handle,
                                         int_fast16_t returnStatus,
                                         ECDSA_Operation operation,
                                         ECDSA_OperationType operationType);
extern void PSACrypto_s_eddsaHwiCallback(EDDSA_Handle handle,
                                         int_fast16_t returnStatus,
                                         EDDSA_Operation operation,
                                         EDDSA_OperationType operationType);
extern void PSACrypto_s_sha2HwiCallback(SHA2_Handle handle, int_fast16_t returnStatus);

extern PSACrypto_s_SecureCallback *PSACrypto_s_secureCB;

#endif /* TFM_ENABLED */

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))

/* Externs for KeyMgmt functions */
extern psa_status_t KeyMgmt_psa_copy_key(mbedtls_svc_key_id_t source_key,
                                         const psa_key_attributes_t *attributes,
                                         mbedtls_svc_key_id_t *target_key);
extern psa_status_t KeyMgmt_psa_crypto_init(void);
extern psa_status_t KeyMgmt_psa_destroy_key(mbedtls_svc_key_id_t key);
extern psa_status_t KeyMgmt_psa_export_key(mbedtls_svc_key_id_t key,
                                           uint8_t *data,
                                           size_t data_size,
                                           size_t *data_length);
extern psa_status_t KeyMgmt_psa_export_public_key(mbedtls_svc_key_id_t key,
                                                  uint8_t *data,
                                                  size_t data_size,
                                                  size_t *data_length);
extern psa_status_t KeyMgmt_psa_get_key_attributes(mbedtls_svc_key_id_t key, psa_key_attributes_t *attributes);
extern psa_status_t KeyMgmt_psa_import_key(const psa_key_attributes_t *attributes,
                                           const uint8_t *data,
                                           size_t data_length,
                                           mbedtls_svc_key_id_t *key);
extern psa_status_t KeyMgmt_psa_purge_key(mbedtls_svc_key_id_t key);
extern void KeyMgmt_psa_reset_key_attributes(psa_key_attributes_t *attributes);

extern psa_status_t KeyMgmt_psa_key_derivation_setup(KeyMgmt_psa_key_derivation_operation_t *operation,
                                                     psa_algorithm_t alg);
extern psa_status_t KeyMgmt_psa_key_derivation_get_capacity(const KeyMgmt_psa_key_derivation_operation_t *operation,
                                                            size_t *capacity);
extern psa_status_t KeyMgmt_psa_key_derivation_set_capacity(KeyMgmt_psa_key_derivation_operation_t *operation,
                                                            size_t capacity);
extern psa_status_t KeyMgmt_psa_key_derivation_input_bytes(KeyMgmt_psa_key_derivation_operation_t *operation,
                                                           psa_key_derivation_step_t step,
                                                           const uint8_t *data,
                                                           size_t data_length);
extern psa_status_t KeyMgmt_psa_key_derivation_input_integer(KeyMgmt_psa_key_derivation_operation_t *operation,
                                                             psa_key_derivation_step_t step,
                                                             uint64_t value);
extern psa_status_t KeyMgmt_psa_key_derivation_input_key(KeyMgmt_psa_key_derivation_operation_t *operation,
                                                         psa_key_derivation_step_t step,
                                                         mbedtls_svc_key_id_t key);
extern psa_status_t KeyMgmt_psa_key_derivation_output_key(const psa_key_attributes_t *attributes,
                                                          KeyMgmt_psa_key_derivation_operation_t *operation,
                                                          mbedtls_svc_key_id_t *key);
extern psa_status_t KeyMgmt_psa_key_derivation_verify_bytes(KeyMgmt_psa_key_derivation_operation_t *operation,
                                                            const uint8_t *expected_output,
                                                            size_t output_length);
extern psa_status_t KeyMgmt_psa_key_derivation_verify_key(KeyMgmt_psa_key_derivation_operation_t *operation,
                                                          mbedtls_svc_key_id_t expected);
extern psa_status_t KeyMgmt_psa_key_derivation_abort(KeyMgmt_psa_key_derivation_operation_t *operation);

extern psa_status_t tfm_its_init(void);
#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) \
        * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                                                     \
        */

/* Forward declarations */
static psa_status_t psa_key_attributes_usage_check(psa_key_attributes_t *attributes,
                                                   psa_key_usage_t usage,
                                                   psa_algorithm_t alg);
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
static void *psa_aligned_malloc(size_t size, void **free_address);
#endif

#if defined(PSA_DEBUG)
static uint8_t *iv;
static uint8_t iv_set = 0U;
/*
 *  ======== psa_debug_get_iv ========
 */
psa_status_t psa_debug_get_iv(uint8_t **new_iv)
{
    if (iv_set == 0U)
    {
        return PSA_ERROR_BAD_STATE;
    }

    iv_set  = 0U;
    *new_iv = iv;
    return PSA_SUCCESS;
}

/*
 *  ======== psa_debug_set_iv ========
 */
void psa_debug_set_iv(uint8_t *new_iv)
{
    iv_set = 1U;
    iv     = new_iv;
}
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
static void *psa_aligned_malloc(size_t size, void **free_address)
{
    *free_address = malloc(size + 3);
    if (*free_address == NULL)
    {
        return NULL;
    }

    uintptr_t addr = (uintptr_t)(*free_address);
    if (addr % 4 == 0)
    {
        return *free_address;
    }
    else
    {
        addr = (addr + 3) & ~((uintptr_t)3);
        return (void *)addr;
    }
}
#endif

#if (defined(ENABLE_TI_CRYPTO_AESCBC) || defined(ENABLE_TI_CRYPTO_AESCCM) || defined(ENABLE_TI_CRYPTO_AESCMAC) || \
     defined(ENABLE_TI_CRYPTO_AESCTR) || defined(ENABLE_TI_CRYPTO_AESECB) || defined(ENABLE_TI_CRYPTO_AESGCM))

    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_set_aes_return_behavior ========
 */
static void psa_set_aes_return_behavior(AESCommonXXF3_Object *object, psa_return_behavior_t returnBehavior)
{
    if (returnBehavior == PSA_POLLING_MODE)
    {
        object->returnBehavior = AES_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        object->returnBehavior = AES_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        object->returnBehavior = AES_RETURN_BEHAVIOR_CALLBACK;
    }
}
    #endif /* TFM_BUILD && DeviceFamily_PARENT_CC27XX */
#endif     /* (defined(ENABLE_TI_CRYPTO_AESCBC) || defined(ENABLE_TI_CRYPTO_AESCCM) || \
              defined(ENABLE_TI_CRYPTO_AESCMAC) || defined(ENABLE_TI_CRYPTO_AESCTR) || \
              defined(ENABLE_TI_CRYPTO_AESECB) || defined(ENABLE_TI_CRYPTO_AESGCM)) */

#ifdef ENABLE_TI_CRYPTO_AESCBC
/*
 *  ======== psa_aescbc_construct ========
 */
static AESCBC_Handle psa_aescbc_construct(AESCBC_Config *aescbcConfig, AESCBC_Object *aescbcObject)
{
    AESCBC_Params aescbcParams;
    psa_return_behavior_t returnBehavior;

    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    AESCBC_Params_init(&aescbcParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        aescbcParams.returnBehavior = AESCBC_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        aescbcParams.returnBehavior = AESCBC_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        aescbcParams.returnBehavior = AESCBC_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        aescbcParams.callbackFxn = PSACrypto_s_aescbcHwiCallback;
    #endif
    }

    memset(aescbcObject, 0x0, sizeof(AESCBC_Object));
    aescbcConfig->object  = aescbcObject;
    aescbcConfig->hwAttrs = &aescbcHWAttrs;

    return AESCBC_construct(aescbcConfig, &aescbcParams);
}

    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_aescbc_set_return_behavior ========
 */
static void psa_aescbc_set_return_behavior(AESCBC_Handle aescbcHandle, psa_return_behavior_t returnBehavior)
{
    AESCBC_Object *object = (AESCBC_Object *)aescbcHandle->object;

    psa_set_aes_return_behavior(&object->common, returnBehavior);
}
    #endif
#endif

#ifdef ENABLE_TI_CRYPTO_AESCCM
/*
 *  ======== psa_aesccm_construct ========
 */
static AESCCM_Handle psa_aesccm_construct(AESCCM_Config *aesccmConfig, AESCCM_Object *aesccmObject)
{
    AESCCM_Params aesccmParams;
    psa_return_behavior_t returnBehavior;
    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    AESCCM_Params_init(&aesccmParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        aesccmParams.returnBehavior = AESCCM_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        aesccmParams.returnBehavior = AESCCM_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        aesccmParams.returnBehavior = AESCCM_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        aesccmParams.callbackFxn = PSACrypto_s_aesccmHwiCallback;
    #endif
    }

    memset(aesccmObject, 0x0, sizeof(AESCCM_Object));
    aesccmConfig->object  = aesccmObject;
    aesccmConfig->hwAttrs = &aesccmHWAttrs;

    return AESCCM_construct(aesccmConfig, &aesccmParams);
}
    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_aesccm_set_return_behavior ========
 */
static void psa_aesccm_set_return_behavior(AESCCM_Handle aesccmHandle, psa_return_behavior_t returnBehavior)
{
    AESCCM_Object *object = (AESCCM_Object *)aesccmHandle->object;

    psa_set_aes_return_behavior(&object->common, returnBehavior);
}
    #endif
#endif

#ifdef ENABLE_TI_CRYPTO_AESCMAC
static AESCMAC_Handle psa_aescmac_construct(AESCMAC_Config *aescmacConfig, AESCMAC_Object *aescmacObject)
{
    AESCMAC_Params aescmacParams;
    psa_return_behavior_t returnBehavior;
    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    AESCMAC_Params_init(&aescmacParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        aescmacParams.returnBehavior = AESCMAC_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        aescmacParams.returnBehavior = AESCMAC_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        aescmacParams.returnBehavior = AESCMAC_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        aescmacParams.callbackFxn = PSACrypto_s_aescmacHwiCallback;
    #endif
    }

    memset(aescmacObject, 0x0, sizeof(AESCMAC_Object));
    aescmacConfig->object  = aescmacObject;
    aescmacConfig->hwAttrs = &aescmacHWAttrs;

    return AESCMAC_construct(aescmacConfig, &aescmacParams);
}

    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_aescmac_set_return_behavior ========
 */
static void psa_aescmac_set_return_behavior(AESCMAC_Handle handle, psa_return_behavior_t returnBehavior)
{
    AESCMAC_Object *object = (AESCMAC_Object *)handle->object;

    psa_set_aes_return_behavior(&object->common, returnBehavior);
}

    #endif

/*
 *  ======== psa_aescbcmac_construct ========
 */
static AESCMAC_Handle psa_aescbcmac_construct(AESCMAC_Config *aescbcmacConfig, AESCMAC_Object *aescbcmacObject)
{
    AESCMAC_Params aescbcmacParams;
    psa_return_behavior_t returnBehavior;
    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    AESCMAC_Params_init(&aescbcmacParams);

    aescbcmacParams.operationalMode = AESCMAC_OPMODE_CBCMAC;

    if (returnBehavior == PSA_POLLING_MODE)
    {
        aescbcmacParams.returnBehavior = AESCMAC_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        aescbcmacParams.returnBehavior = AESCMAC_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        aescbcmacParams.returnBehavior = AESCMAC_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        aescbcmacParams.callbackFxn = PSACrypto_s_aescbcmacHwiCallback;
    #endif
    }

    memset(aescbcmacObject, 0x0, sizeof(AESCMAC_Object));
    aescbcmacConfig->object  = aescbcmacObject;
    aescbcmacConfig->hwAttrs = &aescbcmacHWAttrs;

    return AESCMAC_construct(aescbcmacConfig, &aescbcmacParams);
}

static AESCMAC_Handle psa_aescmac_get_handle(ti_psa_mac_operation_t *operation, psa_algorithm_t alg)
{
    AESCMAC_Handle handle;

    if (alg == PSA_ALG_CMAC)
    {
        handle = (AESCMAC_Handle)&operation->driver.aescmac.aescmacConfig;
    }
    else
    {
        handle = (AESCMAC_Handle)&operation->driver.aescbcmac.aescbcmacConfig;
    }

    return handle;
}
#endif

#ifdef ENABLE_TI_CRYPTO_AESCTR
/*
 *  ======== psa_aesctr_construct ========
 */
static AESCTR_Handle psa_aesctr_construct(AESCTR_Config *aesctrConfig, AESCTR_Object *aesctrObject)
{
    AESCTR_Params aesctrParams;
    psa_return_behavior_t returnBehavior;

    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    AESCTR_Params_init(&aesctrParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        aesctrParams.returnBehavior = AESCTR_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        aesctrParams.returnBehavior = AESCTR_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        aesctrParams.returnBehavior = AESCTR_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        aesctrParams.callbackFxn = PSACrypto_s_aesctrHwiCallback;
    #endif
    }

    memset(aesctrObject, 0x0, sizeof(AESCTR_Object));
    aesctrConfig->object  = aesctrObject;
    aesctrConfig->hwAttrs = &aesctrHWAttrs;

    return AESCTR_construct(aesctrConfig, &aesctrParams);
}

    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_aesctr_set_return_behavior ========
 */
static void psa_aesctr_set_return_behavior(AESCTR_Handle aesctrHandle, psa_return_behavior_t returnBehavior)
{
    AESCTR_Object *object = (AESCTR_Object *)aesctrHandle->object;

    psa_set_aes_return_behavior(&object->common, returnBehavior);
}
    #endif
#endif

#ifdef ENABLE_TI_CRYPTO_AESECB
/*
 *  ======== psa_aesecb_construct ========
 */
static AESECB_Handle psa_aesecb_construct(AESECB_Config *aesecbConfig, AESECB_Object *aesecbObject)
{
    AESECB_Params aesecbParams;
    psa_return_behavior_t returnBehavior;

    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    AESECB_Params_init(&aesecbParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        aesecbParams.returnBehavior = AESECB_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        aesecbParams.returnBehavior = AESECB_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        aesecbParams.returnBehavior = AESECB_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        aesecbParams.callbackFxn = PSACrypto_s_aesecbHwiCallback;
    #endif
    }

    memset(aesecbObject, 0x0, sizeof(AESECB_Object));
    aesecbConfig->object  = aesecbObject;
    aesecbConfig->hwAttrs = &aesecbHWAttrs;

    return AESECB_construct(aesecbConfig, &aesecbParams);
}

    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_aesecb_set_return_behavior ========
 */
static void psa_aesecb_set_return_behavior(AESECB_Handle aesecbHandle, psa_return_behavior_t returnBehavior)
{
    AESECB_Object *object = (AESECB_Object *)aesecbHandle->object;

    psa_set_aes_return_behavior(&object->common, returnBehavior);
}
    #endif
#endif

#ifdef ENABLE_TI_CRYPTO_AESGCM
/*
 *  ======== psa_aesgcm_construct ========
 */
static AESGCM_Handle psa_aesgcm_construct(AESGCM_Config *aesgcmConfig, AESGCM_Object *aesgcmObject)
{
    AESGCM_Params aesgcmParams;
    psa_return_behavior_t returnBehavior;
    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    AESGCM_Params_init(&aesgcmParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        aesgcmParams.returnBehavior = AESGCM_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        aesgcmParams.returnBehavior = AESGCM_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        aesgcmParams.returnBehavior = AESGCM_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        aesgcmParams.callbackFxn = PSACrypto_s_aesgcmHwiCallback;
    #endif
    }

    memset(aesgcmObject, 0x0, sizeof(AESGCM_Object));
    aesgcmConfig->object  = aesgcmObject;
    aesgcmConfig->hwAttrs = &aesgcmHWAttrs;

    return AESGCM_construct(aesgcmConfig, &aesgcmParams);
}

    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_aesgcm_set_return_behavior ========
 */
static void psa_aesgcm_set_return_behavior(AESGCM_Handle aesgcmHandle, psa_return_behavior_t returnBehavior)
{
    AESGCM_Object *object = (AESGCM_Object *)aesgcmHandle->object;

    psa_set_aes_return_behavior(&object->common, returnBehavior);
}
    #endif
#endif

#ifdef ENABLE_TI_CRYPTO_ECDH
/*
 *  ======== psa_ecdh_construct ========
 */
static ECDH_Handle psa_ecdh_construct(ECDH_Config *ecdhConfig, ECDH_Object *ecdhObject)
{
    ECDH_Params ecdhParams;

    psa_return_behavior_t returnBehavior;

    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    ECDH_Params_init(&ecdhParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        ecdhParams.returnBehavior = ECDH_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        ecdhParams.returnBehavior = ECDH_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        ecdhParams.returnBehavior = ECDH_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        ecdhParams.callbackFxn = PSACrypto_s_ecdhHwiCallback;
    #endif
    }

    memset(ecdhObject, 0x0, sizeof(ECDH_Object));
    ecdhConfig->object  = ecdhObject;
    ecdhConfig->hwAttrs = &ecdhHWAttrs;

    return ECDH_construct(ecdhConfig, &ecdhParams);
}
#endif

#ifdef ENABLE_TI_CRYPTO_ECDSA
/*
 *  ======== psa_ecdsa_construct ========
 */
static ECDSA_Handle psa_ecdsa_construct(ECDSA_Config *ecdsaConfig, ECDSA_Object *ecdsaObject)
{
    ECDSA_Params ecdsaParams;
    psa_return_behavior_t returnBehavior;

    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    ECDSA_Params_init(&ecdsaParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        ecdsaParams.returnBehavior = ECDSA_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        ecdsaParams.returnBehavior = ECDSA_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        ecdsaParams.returnBehavior = ECDSA_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        ecdsaParams.callbackFxn = PSACrypto_s_ecdsaHwiCallback;
    #endif
    }

    memset(ecdsaObject, 0x0, sizeof(ECDSA_Object));
    ecdsaConfig->object  = ecdsaObject;
    ecdsaConfig->hwAttrs = &ecdsaHWAttrs;

    return ECDSA_construct(ecdsaConfig, &ecdsaParams);
}

#endif

#ifdef ENABLE_TI_CRYPTO_EDDSA
/*
 *  ======== psa_eddsa_construct ========
 */
static EDDSA_Handle psa_eddsa_construct(EDDSA_Config *eddsaConfig, EDDSA_Object *eddsaObject)
{
    EDDSA_Params eddsaParams;
    psa_return_behavior_t returnBehavior;

    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    EDDSA_Params_init(&eddsaParams);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        eddsaParams.returnBehavior = EDDSA_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        eddsaParams.returnBehavior = EDDSA_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        eddsaParams.returnBehavior = EDDSA_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        eddsaParams.callbackFxn = PSACrypto_s_eddsaHwiCallback;
    #endif
    }

    memset(eddsaObject, 0x0, sizeof(EDDSA_Object));
    eddsaConfig->object  = eddsaObject;
    eddsaConfig->hwAttrs = &eddsaHWAttrs;

    return EDDSA_construct(eddsaConfig, &eddsaParams);
}

    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_eddsa_set_return_behavior ========
 */
static void psa_eddsa_set_return_behavior(EDDSA_Handle eddsaHandle, psa_return_behavior_t returnBehavior)
{
    EDDSA_Object *object = (EDDSA_Object *)eddsaHandle->object;

    if (returnBehavior == PSA_POLLING_MODE)
    {
        object->returnBehavior = EDDSA_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        object->returnBehavior = EDDSA_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        object->returnBehavior = EDDSA_RETURN_BEHAVIOR_CALLBACK;
    }
}
    #endif
#endif

#ifdef ENABLE_TI_CRYPTO_SHA2
/*
 *  ======== psa_sha2_construct ========
 */
static SHA2_Handle psa_sha2_construct(SHA2_Config *sha2Config, SHA2_Object *sha2Object)
{
    SHA2_Params sha2Params;
    psa_return_behavior_t returnBehavior;

    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    SHA2_Params_init(&sha2Params);

    if (returnBehavior == PSA_POLLING_MODE)
    {
        sha2Params.returnBehavior = SHA2_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        sha2Params.returnBehavior = SHA2_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        sha2Params.returnBehavior = SHA2_RETURN_BEHAVIOR_CALLBACK;
    #ifdef TFM_BUILD
        sha2Params.callbackFxn = PSACrypto_s_sha2HwiCallback;
    #endif
    }

    memset(sha2Object, 0x0, sizeof(SHA2_Object));
    sha2Config->object  = sha2Object;
    sha2Config->hwAttrs = &sha2HWAttrs; /* HW attributes can remain shared across instances, since we have no valuable
                                         data stored there. */

    return SHA2_construct(sha2Config, &sha2Params);
}

    #if defined(TFM_BUILD) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 *  ======== psa_sha2_set_return_behavior ========
 */
static void psa_sha2_set_return_behavior(SHA2_Handle sha2Handle, psa_return_behavior_t returnBehavior)
{
    SHA2_Object *object = (SHA2_Object *)sha2Handle->object;

    if (returnBehavior == PSA_POLLING_MODE)
    {
        object->returnBehavior = SHA2_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        object->returnBehavior = SHA2_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
        object->returnBehavior = SHA2_RETURN_BEHAVIOR_CALLBACK;
    }
}
    #endif

#endif

#ifdef ENABLE_TI_CRYPTO_RNG
/*
 *  ======== psa_rng_construct ========
 */
static RNG_Handle psa_rng_construct(RNG_Config *rngConfig, RNG_Object *rngObject)
{
    RNG_Params rngParams;

    psa_return_behavior_t returnBehavior;

    #ifdef TFM_BUILD
    /* Secure callers require the driver to be in polling mode. */
    returnBehavior = psa_crypto_ns_caller ? PSA_CALLBACK_MODE : PSA_POLLING_MODE;
    #else
    returnBehavior = PSA_BLOCKING_MODE;
    #endif

    RNG_Params_init(&rngParams);

    /* Note: For XXF3 family devices, the RNG driver uses a global return
     * behavior set by SysConfig and the return behavior in the RNG params is ignored.
     */
    if (returnBehavior == PSA_POLLING_MODE)
    {
        rngParams.returnBehavior = RNG_RETURN_BEHAVIOR_POLLING;
    }
    else if (returnBehavior == PSA_BLOCKING_MODE)
    {
        rngParams.returnBehavior = RNG_RETURN_BEHAVIOR_BLOCKING;
    }
    else
    {
    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        /* RNG_construct() will return NULL if RNG_RETURN_BEHAVIOR_CALLBACK is
         * specified so set to polling to match SysConfig default.
         */
        rngParams.returnBehavior = RNG_RETURN_BEHAVIOR_POLLING;
    #else
        rngParams.returnBehavior = RNG_RETURN_BEHAVIOR_CALLBACK;
        #error "Callback function must be implemented"
    #endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == \
            * DeviceFamily_PARENT_CC35XX)                                                    \
            * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                         \
            */
    }

    memset(rngObject, 0x0, sizeof(RNG_Object));
    rngConfig->object  = rngObject;
    rngConfig->hwAttrs = &rngHWAttrs;

    return RNG_construct(rngConfig, &rngParams);
}

#endif

#ifdef TFM_BUILD

/*
 *  ======== psa_setup_return_behavior ========
 */
void psa_setup_return_behavior(bool ns_caller)
{
    psa_crypto_ns_caller = ns_caller;

    if (ns_caller)
    {
        /* Note: For XXF3 devices, the return behavior for RNG is fixed in
         * SysConfig and not configurable.
         */
    #ifdef ENABLE_TI_CRYPTO_TRNG
        #error "psa_setup_return_behavior does not support TRNG"
    #endif
    }
}

#endif /* TFM_BUILD */

#ifdef ENABLE_TI_CRYPTO_AESCCM
/*
 *  ======== psa_validate_ccm_tag_length ========
 */
static psa_status_t psa_validate_ccm_tag_length(size_t tagLength)
{
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

    if ((tagLength == 4) || (tagLength == 6) || (tagLength == 8) || (tagLength == 10) || (tagLength == 12) ||
        (tagLength == 14) || (tagLength == 16))
    {
        status = PSA_SUCCESS;
    }

    return status;
}
#endif

#ifdef ENABLE_TI_CRYPTO_AESGCM
/*
 *  ======== psa_validate_gcm_tag_length ========
 */
static psa_status_t psa_validate_gcm_tag_length(size_t tagLength)
{
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

    if ((tagLength == 4) || (tagLength == 8) || ((tagLength >= 12) && (tagLength <= 16)))
    {
        status = PSA_SUCCESS;
    }

    return status;
}
#endif

#ifdef ENABLE_TI_CRYPTO_SHA2
/*
 *  ======== psa_set_sha2_hash_type ========
 */
static psa_status_t psa_set_sha2_hash_type(SHA2_Handle sha2Handle, psa_algorithm_t algorithm)
{
    int_fast16_t ret;
    psa_status_t status;

    if (sha2Handle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    switch (algorithm)
    {
        case PSA_ALG_SHA_224:
            ret = SHA2_setHashType(sha2Handle, SHA2_HASH_TYPE_224);
            break;

        case PSA_ALG_SHA_256:
            ret = SHA2_setHashType(sha2Handle, SHA2_HASH_TYPE_256);
            break;

        case PSA_ALG_SHA_384:
            ret = SHA2_setHashType(sha2Handle, SHA2_HASH_TYPE_384);
            break;

        case PSA_ALG_SHA_512:
            ret = SHA2_setHashType(sha2Handle, SHA2_HASH_TYPE_512);
            break;

        default:
            ret = SHA2_STATUS_UNSUPPORTED;
            break;
    }

    status = map_SHA2_status(ret);

    return status;
}
#endif

#ifdef ENABLE_TI_CRYPTO_SHA3
/*
 *  ======== psa_sha3_construct ========
 */
static SHA3_Handle psa_sha3_construct(SHA3_Config *sha3Config, SHA3XXF3HSM_Object *sha3Object)
{
    SHA3_Params sha3Params;

    SHA3_Params_init(&sha3Params);
    sha3Params.returnBehavior = SHA3_RETURN_BEHAVIOR_BLOCKING;

    memset(sha3Object, 0x0, sizeof(SHA3XXF3HSM_Object));
    sha3Config->object  = sha3Object;
    sha3Config->hwAttrs = &sha3HWAttrs;

    return SHA3_construct(sha3Config, &sha3Params);
}

/*
 *  ======== psa_set_sha3_hash_type ========
 */
static psa_status_t psa_set_sha3_hash_type(SHA3_Handle sha3Handle, psa_algorithm_t algorithm)
{
    int_fast16_t ret;
    psa_status_t status;

    if (sha3Handle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    switch (algorithm)
    {
        case PSA_ALG_SHA3_224:
            ret = SHA3_setHashType(sha3Handle, SHA3_HASH_TYPE_224);
            break;

        case PSA_ALG_SHA3_256:
            ret = SHA3_setHashType(sha3Handle, SHA3_HASH_TYPE_256);
            break;

        case PSA_ALG_SHA3_384:
            ret = SHA3_setHashType(sha3Handle, SHA3_HASH_TYPE_384);
            break;

        case PSA_ALG_SHA3_512:
            ret = SHA3_setHashType(sha3Handle, SHA3_HASH_TYPE_512);
            break;

        default:
            ret = SHA3_STATUS_ERROR;
            break;
    }

    /* SHA3 status codes are identical to SHA2 */
    status = map_SHA2_status(ret);

    return status;
}
#endif /* ENABLE_TI_CRYPTO_SHA3 */

/******************************************************************************/
/* Key management */
/******************************************************************************/

/** Check whether a given key type is valid for use with a given MAC algorithm
 *
 * Upon successful return of this function, the behavior of #PSA_MAC_LENGTH
 * when called with the validated \p algorithm and \p key_type is well-defined.
 *
 * \param[in] algorithm     The specific MAC algorithm (can be wildcard).
 * \param[in] key_type      The key type of the key to be used with the
 *                          \p algorithm.
 *
 * \retval #PSA_SUCCESS
 *         The \p key_type is valid for use with the \p algorithm
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The \p key_type is not valid for use with the \p algorithm
 */
static psa_status_t ti_psa_mac_key_can_do(psa_algorithm_t algorithm, psa_key_type_t key_type)
{
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

    if (PSA_ALG_IS_HMAC(algorithm))
    {
        if (key_type == PSA_KEY_TYPE_HMAC)
        {
            return PSA_SUCCESS;
        }
    }
    else if (PSA_ALG_IS_MAC(algorithm))
    {
        /* Our device only supports AES-MAC */
        if (key_type == PSA_KEY_TYPE_AES)
        {
            status = PSA_SUCCESS;
        }
    }

    return status;
}

/*
 *  ======== psa_key_algorithm_permits ========
 */
static int psa_key_algorithm_permits(psa_key_type_t key_type, psa_algorithm_t policy_alg, psa_algorithm_t requested_alg)
{
    /* If it isn't explicitly permitted, it's forbidden */
    int permits = 0;

    /* Common case: the policy only allows requested_alg */
    if (requested_alg == policy_alg)
    {
        permits = 1;
    }
    /* If policy_alg is a hash-and-sign with a wildcard for the hash, and
     * requested_alg is the same hash-and-sign family with any hash, then
     * requested_alg is compliant with policy_alg.
     */
    else if (PSA_ALG_IS_SIGN_HASH(requested_alg) && PSA_ALG_SIGN_GET_HASH(policy_alg) == PSA_ALG_ANY_HASH)
    {
        permits = ((policy_alg & ~PSA_ALG_HASH_MASK) == (requested_alg & ~PSA_ALG_HASH_MASK));
    }
    /* If policy_alg is a wildcard AEAD algorithm of the same base as the
     * requested algorithm, check the requested tag length to be equal-length or
     * longer than the wildcard-specified length.
     */
    else if (PSA_ALG_IS_AEAD(policy_alg) && PSA_ALG_IS_AEAD(requested_alg) &&
             (PSA_ALG_AEAD_WITH_SHORTENED_TAG(policy_alg, 0) == PSA_ALG_AEAD_WITH_SHORTENED_TAG(requested_alg, 0)) &&
             ((policy_alg & PSA_ALG_AEAD_AT_LEAST_THIS_LENGTH_FLAG) != 0))
    {
        permits = (PSA_ALG_AEAD_GET_TAG_LENGTH(policy_alg) <= PSA_ALG_AEAD_GET_TAG_LENGTH(requested_alg));
    }
    /* If policy_alg is a MAC algorithm of the same base as the requested
     * algorithm, check whether their MAC lengths are compatible.
     */
    else if (PSA_ALG_IS_MAC(policy_alg) && PSA_ALG_IS_MAC(requested_alg) &&
             (PSA_ALG_FULL_LENGTH_MAC(policy_alg) == PSA_ALG_FULL_LENGTH_MAC(requested_alg)))
    {
        /* Validate the combination of key type and algorithm. Since the policy
         * and requested algorithms are the same, we only need this once.
         */
        if (PSA_SUCCESS != ti_psa_mac_key_can_do(policy_alg, key_type))
        {
            permits = 1;
        }
        else
        {
            /* Get both the requested output length for the algorithm which is
             * to be verified, and the default output length for the base
             * algorithm. Note that none of the currently supported algorithms
             * have an output length dependent on actual key size, so setting it
             * to a bogus value of 0 is currently OK.
             */
            size_t requested_output_length = PSA_MAC_LENGTH(key_type, 0, requested_alg);
            size_t default_output_length   = PSA_MAC_LENGTH(key_type, 0, PSA_ALG_FULL_LENGTH_MAC(requested_alg));

            /* If the policy is default-length, only allow an algorithm with
             * a declared exact-length matching the default.
             */
            if (PSA_MAC_TRUNCATED_LENGTH(policy_alg) == 0)
            {
                permits = (requested_output_length == default_output_length);
            }
            /* If the requested algorithm is default-length, allow it if the
             * policy length exactly matches the default length.
             */
            else if (PSA_MAC_TRUNCATED_LENGTH(requested_alg) == 0 &&
                     PSA_MAC_TRUNCATED_LENGTH(policy_alg) == default_output_length)
            {
                permits = (1);
            }
            /* If policy_alg is an at-least-this-length wildcard MAC algorithm,
             * check for the requested MAC length to be equal to or longer than
             * the minimum allowed length.
             */
            else if ((policy_alg & PSA_ALG_MAC_AT_LEAST_THIS_LENGTH_FLAG) != 0)
            {
                permits = (PSA_MAC_TRUNCATED_LENGTH(policy_alg) <= requested_output_length);
            }
        }
    }
    /* If policy_alg is a generic key agreement operation, then using it for
     * a key derivation with that key agreement should also be allowed. This
     * behaviour is expected to be defined in a future specification version.
     */
    else if (PSA_ALG_IS_RAW_KEY_AGREEMENT(policy_alg) && PSA_ALG_IS_KEY_AGREEMENT(requested_alg))
    {
        permits = (PSA_ALG_KEY_AGREEMENT_GET_BASE(requested_alg) == policy_alg);
    }

    return permits;
}

/** Test whether a policy permits an algorithm.
 *
 * The caller must test usage flags separately.
 *
 * \note This function requires providing the key type for which the policy is
 *       being validated, since some algorithm policy definitions (e.g. MAC)
 *       have different properties depending on what kind of cipher it is
 *       combined with.
 *
 * \retval PSA_SUCCESS                  When \p alg is a specific algorithm
 *                                      allowed by the \p policy.
 * \retval PSA_ERROR_INVALID_ARGUMENT   When \p alg is not a specific algorithm
 * \retval PSA_ERROR_NOT_PERMITTED      When \p alg is a specific algorithm, but
 *                                      the \p policy does not allow it.
 */
static psa_status_t psa_key_policy_permits(const psa_key_policy_t *policy, psa_key_type_t key_type, psa_algorithm_t alg)
{
    psa_status_t status;

    /* '0' is not a valid algorithm */
    if (alg == 0)
    {
        status = PSA_ERROR_INVALID_ARGUMENT;
    }
    /* A requested algorithm cannot be a wildcard */
    else if (PSA_ALG_IS_WILDCARD(alg))
    {
        status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (psa_key_algorithm_permits(key_type, policy->MBEDTLS_PRIVATE(alg), alg) ||
             psa_key_algorithm_permits(key_type, policy->MBEDTLS_PRIVATE(alg2), alg))
    {
        status = PSA_SUCCESS;
    }
    else
    {
        status = PSA_ERROR_NOT_PERMITTED;
    }

    return status;
}

/** Check whether a set of key attributes allows the given usage policy and algorithm
 *
 * The key must have allow all the usage flags set in \p usage. If \p alg is
 * nonzero, the key must allow operations with this algorithm. If \p alg is
 * zero, the algorithm is not checked.
 */
static psa_status_t psa_key_attributes_usage_check(psa_key_attributes_t *attributes,
                                                   psa_key_usage_t usage,
                                                   psa_algorithm_t alg)
{
    psa_status_t status       = PSA_SUCCESS;
    psa_key_type_t key_type   = psa_get_key_type(attributes);
    psa_key_usage_t key_usage = psa_get_key_usage_flags(attributes);

#if (TFM_ENABLED == 0) || defined(TFM_BUILD)
    psa_key_policy_t key_policy = attributes->MBEDTLS_PRIVATE(policy);
#else
    psa_key_policy_t key_policy = {.usage = key_usage, .alg = attributes->alg};
#endif

    /* Enforce that usage policy for the key contains all the flags required by
     * the usage parameter. There is one exception: public keys can always be
     * exported, so we treat public key objects as if they had the export flag.
     */
    if (PSA_KEY_TYPE_IS_PUBLIC_KEY(key_type))
    {
        usage &= ~PSA_KEY_USAGE_EXPORT;
    }

    if ((key_usage & usage) != usage)
    {
        status = PSA_ERROR_NOT_PERMITTED;
    }
    /* Enforce that the usage policy permits the requested algorithm */
    else if (alg != 0)
    {
        status = psa_key_policy_permits(&key_policy, key_type, alg);
    }

    return status;
}

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))

/*
 *  ======== ti_psa_destroy_key ========
 */
psa_status_t ti_psa_destroy_key(mbedtls_svc_key_id_t key)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;

    if (HSMXXF3_acquireLock(SemaphoreP_WAIT_FOREVER, (uintptr_t)NULL))
    {
        if (KeyStore_acquireLock())
        {
            status = KeyMgmt_psa_destroy_key(key);
            KeyStore_releaseLock();
        }

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== ti_psa_purge_key ========
 */
psa_status_t ti_psa_purge_key(mbedtls_svc_key_id_t key)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;

    /* No HSM lock is required as no tokens will be submitted */

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_purge_key(key);
        KeyStore_releaseLock();
    }

    return status;
}

/*
 *  ======== ti_psa_get_key_attributes ========
 *  Retrieve full key attributes. If built into the TFM, the crypto secure
 *  service is responsible for translating the full key attributes to client key
 *  attributes.
 */
psa_status_t ti_psa_get_key_attributes(mbedtls_svc_key_id_t key, psa_key_attributes_t *attributes)
{
    psa_algorithm_t originalAlgorithm;
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;

    /* No HSM lock is required as no tokens will be submitted */

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_get_key_attributes(key, attributes);

        KeyStore_releaseLock();
    }

    if (status == PSA_SUCCESS)
    {
        /* Retrieve the algorithm set by the application, before the algorithm was
         * mapped to the value needed by the drivers.
         */
        originalAlgorithm = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2);

        psa_set_key_algorithm(attributes, originalAlgorithm);
    }

    return status;
}

/*
 *  ======== ti_psa_reset_key_attributes ========
 *  Reset full key attributes. If built into the TFM, the crypto secure
 *  service is responsible for:
 *  1) Translating client key attributes to the full key attributes before
 *     calling this function
 *  2) Translating the full key attributes to client key attributes after calling
 *     this function.
 */
void ti_psa_reset_key_attributes(psa_key_attributes_t *attributes)
{
    /* Acquiring the HSM and keystore lock is not required as this function does
     * not access the key store.
     */
    KeyMgmt_psa_reset_key_attributes(attributes);
}

/*
 *  ======== ti_psa_export_key ========
 */
psa_status_t ti_psa_export_key(mbedtls_svc_key_id_t key, uint8_t *data, size_t data_size, size_t *data_length)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;

    /* No HSM lock is required as no tokens will be submitted */

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_export_key(key, data, data_size, data_length);

        KeyStore_releaseLock();
    }

    return status;
}

/*
 *  ======== ti_psa_export_public_key ========
 */
psa_status_t ti_psa_export_public_key(mbedtls_svc_key_id_t key, uint8_t *data, size_t data_size, size_t *data_length)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;

    if (!HSMXXF3_acquireLock(SemaphoreP_WAIT_FOREVER, (uintptr_t)NULL))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_export_public_key(key, data, data_size, data_length);
        KeyStore_releaseLock();
    }

    HSMXXF3_releaseLock();

    return status;
}

/*
 *  ======== psa_copy_attr_and_modify_alg ========
 */
static psa_status_t psa_copy_attr_and_modify_alg(psa_key_attributes_t *dest,
                                                 const psa_key_attributes_t *src,
                                                 size_t len)
{
    psa_algorithm_t originalAlg = psa_get_key_algorithm(src);

    (void)memcpy(dest, src, len);

    if (PSA_ALG_IS_AEAD(originalAlg))
    {
        /* Distinct algorithms for AEAD with non-standard tag sizes are not
         * supported as the SL Crypto driver for CCM and GCM retrieve keystore
         * keys using the standard PSA_ALG_CCM or PSA_ALG_GCM algorithm.
         */
        psa_algorithm_t aeadAlg = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(originalAlg);

        if ((aeadAlg == PSA_ALG_CCM) || (aeadAlg == PSA_ALG_GCM))
        {
            psa_set_key_algorithm(dest, aeadAlg);
        }
        else if (originalAlg == PSA_ALG_CHACHA20_POLY1305)
        {
            /* Nothing to do, it is already copied into the destination attributes. */
        }
        else
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else if (PSA_ALG_IS_BLOCK_CIPHER_MAC(originalAlg))
    {
        /* Distinct algorithms for MAC with non-standard tag sizes are not
         * supported as the SL Crypto driver for CMAC/CBC-MAC retrieve keystore
         * keys using the standard PSA_ALG_CMAC or PSA_ALG_CBC_MAC algorithm.
         */
        psa_algorithm_t macAlg = PSA_ALG_FULL_LENGTH_MAC(originalAlg);

        if ((macAlg == PSA_ALG_CMAC) || (macAlg == PSA_ALG_CBC_MAC))
        {
            psa_set_key_algorithm(dest, macAlg);
        }
        else
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }

    /* Store the original algorithm value so that it can be restored by
     * ti_psa_get_key_attributes.
     */
    dest->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2) = originalAlg;

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_import_key ========
 *  This function requires full key attributes. If built into the TFM, the
 *  crypto secure service is responsible for translating client key attributes
 *  to the full key attributes before calling this function.
 */
psa_status_t ti_psa_import_key(const psa_key_attributes_t *attributes,
                               const uint8_t *data,
                               size_t data_length,
                               mbedtls_svc_key_id_t *key)
{
    psa_key_attributes_t attributesCopy;
    psa_status_t status;

    status = psa_copy_attr_and_modify_alg(&attributesCopy, attributes, sizeof(attributesCopy));

    if (status == PSA_SUCCESS)
    {
        if (HSMXXF3_acquireLock(SemaphoreP_WAIT_FOREVER, (uintptr_t)NULL))
        {
            if (KeyStore_acquireLock())
            {
                /* The following key types are not yet HW-accelerated. While that is the case, they must be
                 * available in plaintext for use in the mbedTLS software implementation.
                 */
                if (PSA_KEY_TYPE_IS_RSA(attributesCopy.MBEDTLS_PRIVATE(type)) ||
                    ((attributesCopy.MBEDTLS_PRIVATE(type)) == PSA_KEY_TYPE_CHACHA20) ||
                    PSA_KEY_TYPE_IS_DH(attributesCopy.MBEDTLS_PRIVATE(type)))
                {
                    psa_set_key_lifetime(
                        &attributesCopy,
                        PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_PERSISTENCE_VOLATILE,
                                                                       PSA_KEY_LOCATION_LOCAL_STORAGE));
                }
                status = KeyMgmt_psa_import_key(&attributesCopy, data, data_length, key);

                KeyStore_releaseLock();
            }
            else
            {
                status = PSA_ERROR_GENERIC_ERROR;
            }

            HSMXXF3_releaseLock();
        }
        else
        {
            status = PSA_ERROR_GENERIC_ERROR;
        }
    }

    if (status != PSA_SUCCESS)
    {
        *key = PSA_KEY_ID_NULL;
    }

    return status;
}

/*
 *  ======== ti_psa_copy_key ========
 *  This function requires full key attributes. If built into the TFM, the
 *  crypto secure service is responsible for translating client key attributes
 *  to the full key attributes before calling this function.
 */
psa_status_t ti_psa_copy_key(mbedtls_svc_key_id_t source_key,
                             const psa_key_attributes_t *attributes,
                             mbedtls_svc_key_id_t *target_key)
{
    psa_key_attributes_t attributesCopy;
    psa_status_t status;

    status = psa_copy_attr_and_modify_alg(&attributesCopy, attributes, sizeof(attributesCopy));

    if (status == PSA_SUCCESS)
    {
        if (HSMXXF3_acquireLock(SemaphoreP_WAIT_FOREVER, (uintptr_t)NULL))
        {
            if (KeyStore_acquireLock())
            {
                status = KeyMgmt_psa_copy_key(source_key, &attributesCopy, target_key);

                KeyStore_releaseLock();
            }
            else
            {
                status = PSA_ERROR_GENERIC_ERROR;
            }

            HSMXXF3_releaseLock();
        }
        else
        {
            status = PSA_ERROR_GENERIC_ERROR;
        }
    }

    if (status != PSA_SUCCESS)
    {
        *target_key = PSA_KEY_ID_NULL;
    }

    return status;
}

/*
 *  ======== psa_can_do_hash ========
 *  Helper function implemented by mbedTLS that must be implemented in our PSA Crypto library
 */
int psa_can_do_hash(psa_algorithm_t hash_alg)
{
    (void)hash_alg;
    return 1;
}

/*
 *  ======== psa_can_do_cipher ========
 *  Helper function implemented by mbedTLS that must be implemented in our PSA Crypto library
 */
int psa_can_do_cipher(psa_key_type_t key_type, psa_algorithm_t cipher_alg)
{
    (void)key_type;
    (void)cipher_alg;
    return 1;
}

#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)

/*
 *  ======== ti_psa_destroy_key ========
 */
psa_status_t ti_psa_destroy_key(mbedtls_svc_key_id_t key)
{
    #if (TFM_ENABLED == 1)
    /* Get index of element to remove */
    int8_t toRemove = -1;
    for (uint8_t i = 0; i < keyAlgorithmsLength; i++)
    {
        if (keyAlgorithms[i].keyID == key)
        {
            toRemove = i;
            break;
        }
    }

    if (toRemove >= 0)
    {
        /* Remove element by shifting everything to the left */
        for (uint8_t i = toRemove; i < keyAlgorithmsLength - 1; i++)
        {
            keyAlgorithms[i] = keyAlgorithms[i + 1];
        }

        keyAlgorithmsLength--;
    }
    #endif

    return KeyStore_PSA_destroyKey(key);
}

/*
 *  ======== ti_psa_purge_key ========
 */
psa_status_t ti_psa_purge_key(mbedtls_svc_key_id_t key)
{

    psa_status_t status             = PSA_SUCCESS;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    ti_psa_get_key_attributes(key, &attributes);
    psa_key_lifetime_t lifetime = psa_get_key_lifetime(&attributes);

    /* Volatile keys cannot be purged. So, only purge keys without the volatile lifetime. */
    if (lifetime != PSA_KEY_PERSISTENCE_VOLATILE)
    {
        status = KeyStore_PSA_purgeKey(key);
    }

    ti_psa_reset_key_attributes(&attributes);

    return status;
}

/*
 *  ======== ti_psa_get_key_attributes ========
 *  Retrieve all the publicly-accessible attributes of a key.
 */
psa_status_t ti_psa_get_key_attributes(mbedtls_svc_key_id_t key, psa_key_attributes_t *attributes)
{
    *attributes         = PSA_KEY_ATTRIBUTES_INIT;
    psa_status_t status = KeyStore_PSA_getKeyAttributes(key, attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Retrieve the algorithm set by the application, before the algorithm was
     * mapped to the value needed by the drivers.
     */
    psa_algorithm_t originalAlgorithm = 0;
    #if (TFM_ENABLED == 0)
    originalAlgorithm                 = attributes->core.policy.alg2;
    #else
    for (uint8_t i = 0; i < keyAlgorithmsLength; i++)
    {
        if (keyAlgorithms[i].keyID == key)
        {
            originalAlgorithm = keyAlgorithms[i].alg;
            break;
        }
    }

    if (originalAlgorithm == 0)
    {
        return PSA_ERROR_INVALID_HANDLE;
    }
    #endif

    psa_set_key_algorithm(attributes, originalAlgorithm);
    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_reset_key_attributes ========
 */
void ti_psa_reset_key_attributes(psa_key_attributes_t *attributes)
{
    #if (TFM_ENABLED == 1)
    *attributes = KEYSTORE_PSA_KEY_ATTRIBUTES_INIT;
    #else
    KeyStore_PSA_resetKeyAttributes(attributes);
    #endif
}

/*
 *  ======== ti_psa_export_key ========
 */
psa_status_t ti_psa_export_key(mbedtls_svc_key_id_t key, uint8_t *data, size_t data_size, size_t *data_length)
{
    return KeyStore_PSA_exportKey(key, data, data_size, data_length);
}

/*
 *  ======== ti_psa_export_public_key ========
 */
psa_status_t ti_psa_export_public_key(mbedtls_svc_key_id_t key, uint8_t *data, size_t data_size, size_t *data_length)
{
    ECDH_OperationGeneratePublicKey generatePublicKeyOp;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_status_t status;
    CryptoKey privateKey;
    CryptoKey publicKey;

    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    psa_key_type_t keyType = psa_get_key_type(&attributes);

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    /* KeyStore_PSA does not support exporting the public part of a key pair, so
     * in that case generate the public part using ECDH_generatePublicKey.
     */
    if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(keyType))
    {
    #ifdef ENABLE_TI_CRYPTO_ECDH
        int_fast16_t ret;
        size_t keyBits  = psa_get_key_bits(&attributes);
        size_t keyBytes = PSA_BITS_TO_BYTES(keyBits);
        size_t publicKeyBytes;
        ECDH_KeyMaterialEndianness endianess;
        ECDH_Config ecdhConfig;
        ECDH_Object ecdhObject;

        /* For most families key size is twice the private key size + 1 */
        psa_ecc_family_t keyFamily = PSA_KEY_TYPE_ECC_GET_FAMILY(keyType);
        if (keyFamily == PSA_ECC_FAMILY_MONTGOMERY)
        {
            publicKeyBytes = keyBytes;
            endianess      = ECDH_LITTLE_ENDIAN_KEY;
        }
        else
        {
            publicKeyBytes = keyBytes * 2 + 1;
            endianess      = ECDH_BIG_ENDIAN_KEY;
        }

        if (publicKeyBytes > data_size)
        {
            return PSA_ERROR_BUFFER_TOO_SMALL;
        }

        /* Init cryptoKeys for use in the GeneratePublicKey operation */
        CryptoKeyPlaintext_initBlankKey(&publicKey, data, publicKeyBytes);
        KeyStore_PSA_initKey(&privateKey, key, keyBytes, NULL);

        /* Init the operation */
        ECDH_OperationGeneratePublicKey_init(&generatePublicKeyOp);
        generatePublicKeyOp.myPrivateKey = &privateKey;
        generatePublicKeyOp.myPublicKey  = &publicKey;
        /* Get the correct parameters, some curves are not supported */
        generatePublicKeyOp.curve        = map_keyTypeToECCParams(keyType, keyBits);

        if (generatePublicKeyOp.curve == NULL)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }

        generatePublicKeyOp.keyMaterialEndianness = endianess;

        /* Create temporary handle for one-shot operation */
        ECDH_Handle ecdhHandle = psa_ecdh_construct(&ecdhConfig, &ecdhObject);

        if (ecdhHandle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        ret    = ECDH_generatePublicKey(ecdhHandle, &generatePublicKeyOp);
        status = map_ECDH_status(ret);

        if (status != PSA_SUCCESS)
        {
            *data_length = 0;
        }
        else
        {
            *data_length = publicKeyBytes;
        }

        /* Close temporary handle */
        if (((ECDH_Object *)ecdhHandle->object)->returnBehavior == ECDH_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the ECDH_Handle can be closed, since
             * this is a one-shot operation.
             */
            ((ECDH_Object *)ecdhHandle->object)->isOpen = false;
        }
        else
        {
            ECDH_close(ecdhHandle);
        }

    #endif /* ENABLE_TI_CRYPTO_ECDH */
    }
    else
    {
        /* KeyStore_PSA_exportPublicKey does not return until the export is complete */
        status = KeyStore_PSA_exportPublicKey(key, data, data_size, data_length);
    }

    return status;
}

/*
 *  ======== ti_psa_import_key ========
 */
psa_status_t ti_psa_import_key(const psa_key_attributes_t *attributes,
                               const uint8_t *data,
                               size_t data_length,
                               mbedtls_svc_key_id_t *key)
{
    psa_status_t status;
    psa_key_attributes_t attributesCopy;
    psa_key_type_t psaKeyType;
    psa_algorithm_t originalAlgorithm;

    attributesCopy    = *attributes;
    psaKeyType        = psa_get_key_type(attributes);
    originalAlgorithm = psa_get_key_algorithm(attributes);

    /* SL KeyStore driver does not support distinct algorithms for AEAD with
     * different tag sizes The SL Crypto driver for CCM and GCM can only accept
     * the standard PSA_ALG_CCM or PSA_ALG_GCM algorithm.
     */
    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(originalAlgorithm) == PSA_ALG_CCM)
    {
        psa_set_key_algorithm(&attributesCopy, PSA_ALG_CCM);
    }
    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(originalAlgorithm) == PSA_ALG_GCM)
    {
        psa_set_key_algorithm(&attributesCopy, PSA_ALG_GCM);
    }
    psa_set_key_type(&attributesCopy, psaKeyType);

    #if (TFM_ENABLED == 0)
    /* Store the original algorithm value so that it can be restored by
     * ti_psa_get_key_attributes.
     */
    attributesCopy.core.policy.alg2 = originalAlgorithm;
    #endif

    status = KeyStore_PSA_importKey(&attributesCopy, (uint8_t *)data, data_length, key);

    if (status != KEYSTORE_PSA_STATUS_SUCCESS)
    {
        KeyStore_PSA_destroyKey(*key);
        return status;
    }

    #if (TFM_ENABLED == 1)
    /* With TFM_ENABLED=1, key attributes struct only has one alg slot,
     * so store original algorithms in an array of length
     * TFM_ENABLED_KEY_STORAGE_LIMIT (TFM_ENABLED_KEY_STORAGE_LIMIT is the
     * max number of keys that can be stored at any one time)
     */
    if (keyAlgorithmsLength < TFM_ENABLED_KEY_STORAGE_LIMIT)
    {
        keyAlgorithms[keyAlgorithmsLength].keyID = *key;
        keyAlgorithms[keyAlgorithmsLength].alg   = originalAlgorithm;
        keyAlgorithmsLength++;
    }
    else
    {
        KeyStore_PSA_destroyKey(*key);
        status = PSA_ERROR_NOT_SUPPORTED;
    }
    #endif

    return status;
}

/*
 *  ======== psa_copy_key ========
 */
psa_status_t psa_copy_key(mbedtls_svc_key_id_t source_key,
                          const psa_key_attributes_t *attributes,
                          mbedtls_svc_key_id_t *target_key)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

#else

    #error "Key Management functions not supported for this device"

#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) \
        * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                                                     \
        */

/******************************************************************************/
/* Message digests */
/******************************************************************************/

/* Hash suspend/resume cannot be supported if TFM is enabled and PSA Crypto
 * Wrapper is not built into TFM since the internal driver structs are not
 * accessible to save/restore the hash state.
 *
 * The CC27xx SHA2 driver may buffer an entire block of data, thus cannot
 * support hash suspend/resume which limits the amount of unprocessed input
 * to (block_size - 1) bytes.
 */
#if ((TFM_ENABLED == 1) && !defined(TFM_BUILD))

/*
 *  ======== ti_psa_hash_resume ========
 */
psa_status_t ti_psa_hash_resume(psa_hash_operation_t *psa_operation,
                                const uint8_t *hash_state,
                                size_t hash_state_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

/*
 *  ======== ti_psa_hash_suspend ========
 */
psa_status_t ti_psa_hash_suspend(psa_hash_operation_t *psa_operation,
                                 uint8_t *hash_state,
                                 size_t hash_state_size,
                                 size_t *hash_state_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

#else

/*
 * addIntToCharArrayBigEndian, charArrayBigEndianToInt
 * Helper functions for ti_psa_hash_suspend and ti_psa_hash_resume
 */

    #ifdef ENABLE_TI_CRYPTO_SHA2
/*
 *  ======== addIntToCharArrayBigEndian ========
 *  Adds a 'numBytes' byte value to a uint8_t array in big endian format.
 *  The first (numBytes - 4) of the array are zeroed out and the 'value' is
 *  written to the last 4-bytes of the array. 'numBytes' must be >= 4.
 */
static void addIntToCharArrayBigEndian(uint32_t value, uint8_t numBytes, uint8_t *array)
{
    uint_fast8_t arrayIndex;
    uint8_t byte;
    uint8_t rightShiftAmount = 24U;

    /* Zero the leading bytes since only the last 4-bytes holds the 'value' */
    (void)memset(array, 0U, (numBytes - 4U));

    /* Write the 32-bit 'value' in big endian format */
    for (arrayIndex = (numBytes - 4U); arrayIndex < numBytes; arrayIndex++)
    {
        byte              = (value >> rightShiftAmount) & 0xFF;
        array[arrayIndex] = byte;
        rightShiftAmount -= 8U;
    }
}

/*
 *  ======== charArrayBigEndianToInt ========
 *  Extracts a uint32_t value from a uint8_t array in big endian format.
 */
static uint32_t charArrayBigEndianToInt(const uint8_t *array)
{
    uint_fast8_t i;
    uint32_t value          = 0U;
    uint8_t leftShiftAmount = 24U;

    /* Extract the 32-bit 'value' from big endian byte array */
    for (i = 0U; i < sizeof(uint32_t); i++)
    {
        value |= array[i] << leftShiftAmount;
        leftShiftAmount -= 8U;
    }

    return value;
}

    #endif /* ENABLE_TI_CRYPTO_SHA2 */

/*
 *  ======== ti_psa_hash_resume ========
 */
psa_status_t ti_psa_hash_resume(psa_hash_operation_t *psa_operation,
                                const uint8_t *hash_state,
                                size_t hash_state_length)
{
    #ifndef ENABLE_TI_CRYPTO_SHA2
    return PSA_ERROR_NOT_SUPPORTED;
    #else
    ti_psa_hash_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

        #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
            (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
    SHA2CC26X2_Object *object          = (SHA2CC26X2_Object *)operation->sha2Config.object;
        #elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
               (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
               (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    SHA2XXF3HSM_Object *object = (SHA2XXF3HSM_Object *)operation->sha2Config.object;
        #else
            #error "Device family not supported"
        #endif

    if (object == NULL || object->isOpen == false)
    {
        return PSA_ERROR_BAD_STATE;
    }

    psa_algorithm_t alg;
    psa_status_t status;
    uint_fast8_t i;
    uint32_t inputLength;
    uint32_t leadingZero;
    uint8_t blockSize;
    uint8_t digestBufferLength;
    uint8_t inputLengthNumBytes;

    /* hash_state = alg || input_length || hash_state || unprocessed_input */

    alg = charArrayBigEndianToInt(hash_state);
    hash_state += 4;

    blockSize           = PSA_HASH_BLOCK_LENGTH(alg);
    digestBufferLength  = PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(alg);
    inputLengthNumBytes = PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(alg);

    /* Operation must be in an inactive state */
    if ((operation->id != 0) || (operation->alg != 0))
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* SL drivers only support SHA2 */
    if (!PSA_ALG_IS_SHA2(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Check that the input length does not require more than 4 bytes to store.
     * 'inputLengthNumBytes' is either 8 or 16 but SHA2 driver stores input length
     * as a 4-byte integer. Integer lengths that require more than 4 bytes are
     * not supported.
     */
    for (i = 0U; i < (inputLengthNumBytes - 4U); i += 4U)
    {
        leadingZero = charArrayBigEndianToInt(hash_state);
        hash_state += 4;

        if (leadingZero != 0U)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }

    inputLength = charArrayBigEndianToInt(hash_state);
    hash_state += 4;

    /* Restore the operation struct contents */
    status = ti_psa_hash_setup(psa_operation, alg);

    if (status == PSA_SUCCESS)
    {
        object->bytesProcessed = (inputLength / blockSize) * blockSize;

        /* Copy hash state to SHA2 driver object */
        (void)memcpy(object->digest, hash_state, digestBufferLength);
        hash_state += digestBufferLength;

        if (sizeof(object->buffer) >= blockSize)
        {
            /* Copy any unprocessed data to SHA2 driver object */
            (void)memcpy(object->buffer, hash_state, blockSize);

            /* Set object->bytesInBuffer to any remaining partial blocks of the
             * inputLength (total number of bytes input to the hash).
             */
            object->bytesInBuffer = inputLength % blockSize;
        }
        else
        {
            /* If the buffer is smaller than the block size, then it cannot
             * support any unprocessed input.
             */
            object->bytesInBuffer = 0U;

            status = PSA_ERROR_BUFFER_TOO_SMALL;
        }
    }

    return status;
    #endif /* ENABLE_TI_CRYPTO_SHA2 */
}

/*
 *  ======== ti_psa_hash_suspend ========
 */
psa_status_t ti_psa_hash_suspend(psa_hash_operation_t *psa_operation,
                                 uint8_t *hash_state,
                                 size_t hash_state_size,
                                 size_t *hash_state_length)
{
    #ifndef ENABLE_TI_CRYPTO_SHA2
    return PSA_ERROR_NOT_SUPPORTED;
    #else
    ti_psa_hash_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
        #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
            (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
    SHA2CC26X2_Object *object          = (SHA2CC26X2_Object *)operation->sha2Config.object;
        #elif ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
               (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
               (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    SHA2XXF3HSM_Object *object = (SHA2XXF3HSM_Object *)operation->sha2Config.object;
        #else
            #error "Device family not supported"
        #endif

    if (object == NULL || object->isOpen == false)
    {
        return PSA_ERROR_BAD_STATE;
    }

    psa_algorithm_t alg         = operation->alg;
    uint8_t inputLengthNumBytes = PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(alg);
    uint8_t hashStateNumBytes   = PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(alg);

    /* Operation must be in an active state */
    if ((operation->id == 0U) || (operation->alg == 0))
    {
        return PSA_ERROR_BAD_STATE;
    }

        /* The CC27xx SHA2 driver may buffer an entire block of data, thus cannot
         * support hash suspend/resume which limits the amount of unprocessed input
         * to (block_size - 1) bytes.
         */
        #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
             (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
             (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if (object->bytesInBuffer == PSA_HASH_BLOCK_LENGTH(alg))
    {
        if (operation->sha2Object.isOpen == false)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* Finalize to cleanup the operation */
        (void)SHA2_finalize((SHA2_Handle)&operation->sha2Config, NULL);
        return PSA_ERROR_NOT_SUPPORTED;
    }
        #endif

    /* Buffer must be large enough to fit all the data */
    *hash_state_length = 4 + inputLengthNumBytes + hashStateNumBytes + object->bytesInBuffer;
    if (hash_state_size < *hash_state_length)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* SHA3 does not support neither suspend nor resume */
    if ((alg == PSA_ALG_SHA3_224) || (alg == PSA_ALG_SHA3_256) || (alg == PSA_ALG_SHA3_384) ||
        (alg == PSA_ALG_SHA3_512))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Per the PSA spec, hash suspend state has the following format:
     * hash_suspend_state = algorithm || input_length || hash_state || unprocessed_input
     */

    /* Add algorithm identifier (32 bit integer value) in big endian format */
    addIntToCharArrayBigEndian(operation->alg, 4, hash_state);
    hash_state += 4;

    uint32_t inputLength = object->bytesProcessed + object->bytesInBuffer;

    /* Add input length in big endian format. For all hash algorithms other than
     * MD2, this is the total number of bytes of input to the hash computation
     * including the unprocessed bytes.
     */
    addIntToCharArrayBigEndian(inputLength, inputLengthNumBytes, hash_state);
    hash_state += inputLengthNumBytes;

    /* Add the current hash state (i.e. hash digest):
     * - For SHA-224 and SHA-256: 8x 32-bit integers, in big-endian encoding.
     * - For SHA-512, SHA-384 and SHA-512/256: 8x 64-bit integers, in big-endian encoding.
     */
    (void)memcpy(hash_state, object->digest, hashStateNumBytes);
    hash_state += hashStateNumBytes;

    /* Add the unprocessed input data. Must be between 0 and (block_size - 1) bytes */
    (void)memcpy(hash_state, object->buffer, object->bytesInBuffer);

    /* Operation should return to an inactive state */
    return ti_psa_hash_abort(psa_operation);
    #endif /* ENABLE_TI_CRYPTO_SHA2 */
}

#endif /* ((TFM_ENABLED == 1) && !defined(TFM_BUILD)) */

/*
 *  ======== ti_psa_hash_abort ========
 */
psa_status_t ti_psa_hash_abort(psa_hash_operation_t *psa_operation)
{
#if !defined(ENABLE_TI_CRYPTO_SHA2) && !defined(ENABLE_TI_CRYPTO_SHA3)
    return PSA_ERROR_NOT_SUPPORTED;
#else
    ti_psa_hash_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    /* Aborting a non-active operation is allowed */
    if (operation->alg == 0)
    {
        return PSA_SUCCESS;
    }

    #ifdef ENABLE_TI_CRYPTO_SHA2
    if (PSA_ALG_IS_SHA2(operation->alg))
    {
        if (operation->sha2Object.isOpen == false)
        {
            return PSA_ERROR_BAD_STATE;
        }
        SHA2_close((SHA2_Handle)&operation->sha2Config);
    }
    else
    #endif
    #ifdef ENABLE_TI_CRYPTO_SHA3
        if (PSA_ALG_IS_SHA3(operation->alg))
    {
        if (operation->sha3Object.isOpen == false)
        {
            return PSA_ERROR_BAD_STATE;
        }
        SHA3_close((SHA3_Handle)&operation->sha3Config);
    }
    else
    #endif
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* After any operation is aborted, it must be 'setup' again. Each setup call
     * re-constructs the handle.
     */
    *operation = TI_PSA_HASH_OPERATION_INIT;

    return PSA_SUCCESS;
#endif /* !ENABLE_TI_CRYPTO_SHA2 && !ENABLE_TI_CRYPTO_SHA3 */
}

/*
 *  ======== ti_psa_hash_setup ========
 */
psa_status_t ti_psa_hash_setup(psa_hash_operation_t *psa_operation, psa_algorithm_t alg)
{
#if !defined(ENABLE_TI_CRYPTO_SHA2) && !defined(ENABLE_TI_CRYPTO_SHA3)
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status                = PSA_ERROR_CORRUPTION_DETECTED;
    ti_psa_hash_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    /* Except for first call to this function, this function cannot be called
     * without calling psa_hash_abort operation, which resets the internal
     * buffers for the hash driver.
     */

    /* Return this error to prevent out of order execution */
    if (operation->id != 0)
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* There should be no alg in this object yet */
    if (operation->alg != 0)
    {
        return PSA_ERROR_BAD_STATE;
    }

    #ifdef ENABLE_TI_CRYPTO_SHA2
    if (PSA_ALG_IS_SHA2(alg))
    {
        SHA2_Handle sha2Handle = psa_sha2_construct(&operation->sha2Config, &operation->sha2Object);

        if (sha2Handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        status = psa_set_sha2_hash_type(sha2Handle, alg);
    }
    else
    #endif /* ENABLE_TI_CRYPTO_SHA2 */
    #ifdef ENABLE_TI_CRYPTO_SHA3
        if (PSA_ALG_IS_SHA3(alg))
    {
        SHA3_Handle sha3Handle = psa_sha3_construct(&operation->sha3Config, &operation->sha3Object);

        if (sha3Handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        status = psa_set_sha3_hash_type(sha3Handle, alg);
    }
    else
    #endif /* ENABLE_TI_CRYPTO_SHA3 */
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (status == PSA_SUCCESS)
    {
        operation->alg = alg;
        operation->id  = PSA_CRYPTO_TI_DRIVER_ID;
    }

    return status;
#endif     /* !ENABLE_TI_CRYPTO_SHA2 && !ENABLE_TI_CRYPTO_SHA3 */
}

/*
 *  ======== ti_psa_hash_update ========
 */
psa_status_t ti_psa_hash_update(psa_hash_operation_t *psa_operation, const uint8_t *input, size_t input_length)
{
#if !defined(ENABLE_TI_CRYPTO_SHA2) && !defined(ENABLE_TI_CRYPTO_SHA3)
    return PSA_ERROR_NOT_SUPPORTED;
#else
    int_fast16_t ret;
    psa_status_t status;
    ti_psa_hash_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    /* Return this error to prevent out of order execution */
    if (operation->id == 0U)
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Don't require hash implementations to behave correctly on a zero-length
     * input which may have an invalid pointer.
     */
    if (input_length == 0)
    {
    #ifdef TFM_BUILD
        return PSA_OPERATION_COMPLETE;
    #else
        return PSA_SUCCESS;
    #endif
    }

    #ifdef ENABLE_TI_CRYPTO_SHA2
    if (PSA_ALG_IS_SHA2(operation->alg))
    {
        if (operation->sha2Object.isOpen == false)
        {
            return PSA_ERROR_BAD_STATE;
        }
        ret = SHA2_addData((SHA2_Handle)&operation->sha2Config, input, input_length);
    }
    else
    #endif
    #ifdef ENABLE_TI_CRYPTO_SHA3
        if (PSA_ALG_IS_SHA3(operation->alg))
    {
        if (operation->sha3Object.isOpen == false)
        {
            return PSA_ERROR_BAD_STATE;
        }
        ret = SHA3_addData((SHA3_Handle)&operation->sha3Config, input, input_length);
    }
    else
    #endif
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    status = map_SHA2_status(ret);

    return status;
#endif /* !ENABLE_TI_CRYPTO_SHA2 && !ENABLE_TI_CRYPTO_SHA3 */
}

/*
 *  ======== ti_psa_hash_finish ========
 */
psa_status_t ti_psa_hash_finish(psa_hash_operation_t *psa_operation,
                                uint8_t *hash,
                                size_t hash_size,
                                size_t *hash_length)
{
#if !defined(ENABLE_TI_CRYPTO_SHA2) && !defined(ENABLE_TI_CRYPTO_SHA3)
    return PSA_ERROR_NOT_SUPPORTED;
#else
    int_fast16_t ret;
    psa_status_t status                = PSA_SUCCESS;
    ti_psa_hash_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    size_t actual_hash_length          = PSA_HASH_LENGTH(operation->alg);

    /* Fill the output buffer with something that isn't a valid hash (barring an
     * attack on the hash and deliberately-crafted input), in case the caller
     * doesn't check the return status properly.
     */
    *hash_length = actual_hash_length;

    /* If hash_size is 0 then hash may be NULL and then the call to memset would
     * have undefined behavior.
     */
    if (hash_size != 0)
    {
        (void)memset(hash, '!', hash_size);
    }

    /* If the output length is smaller than the hash, then report user mistake
     * for this alg that does not support a shortened hash.
     */
    if (hash_size < actual_hash_length)
    {
        status = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if (operation->id == 0U)
    {
        status = PSA_ERROR_BAD_STATE;
    }
    #ifdef ENABLE_TI_CRYPTO_SHA2
    else if (PSA_ALG_IS_SHA2(operation->alg))
    {
        if (operation->sha2Object.isOpen == false)
        {
            status = PSA_ERROR_BAD_STATE;
        }
        else
        {
            ret    = SHA2_finalize((SHA2_Handle)&operation->sha2Config, hash);
            status = map_SHA2_status(ret);
        }
    }
    #endif
    #ifdef ENABLE_TI_CRYPTO_SHA3
    else if (PSA_ALG_IS_SHA3(operation->alg))
    {
        if (operation->sha3Object.isOpen == false)
        {
            status = PSA_ERROR_BAD_STATE;
        }
        else
        {
            ret    = SHA3_finalize((SHA3_Handle)&operation->sha3Config, hash);
            status = map_SHA2_status(ret);
        }
    }
    #endif /* ENABLE_TI_CRYPTO_SHA3 */
    else
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    #ifdef TFM_BUILD
    if (psa_crypto_ns_caller)
    {
        /* Set a marker so that the secure callback knows that the SHA2_Handle can be closed, since
         * this is a segmented finish operation.
         */
        ((SHA2_Object *)operation->sha2Config.object)->isOpen = false;
    }
    else
    #else
    {
        /* Ignore this return value and return the previously set status. There is no callback for secure callers.
         * We can safely abort the operation so that it can be setup again.
         */
        (void)ti_psa_hash_abort(psa_operation);
    }
    #endif

        return status;
#endif /* !ENABLE_TI_CRYPTO_SHA2 && !ENABLE_TI_CRYPTO_SHA3 */
}

/*
 *  ======== ti_psa_hash_verify ========
 */
psa_status_t ti_psa_hash_verify(psa_hash_operation_t *psa_operation, const uint8_t *hash, size_t hash_length)
{
    uint8_t *actual_hash = &localBuf[0];
    size_t actual_hash_length;
    psa_status_t status;

    if (hash_length > sizeof(localBuf))
    {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    /* Zero out max TI supported hash size */
    (void)memset(actual_hash, 0, SHA2_DIGEST_LENGTH_BYTES_512);

#ifdef TFM_BUILD
    if (psa_crypto_ns_caller)
    {
        /* Compute the hash */
        status = ti_psa_hash_finish(psa_operation,
                                    &PSACrypto_s_secureCB->buffer[0],
                                    SHA2_DIGEST_LENGTH_BYTES_512,
                                    &actual_hash_length);
    }
    else
#endif
    {
        /* Compute the hash */
        status = ti_psa_hash_finish(psa_operation, actual_hash, SHA2_DIGEST_LENGTH_BYTES_512, &actual_hash_length);
    }

    if (status != PSA_SUCCESS)
    {
        if (status == PSA_ERROR_BUFFER_TOO_SMALL)
        {
            status = PSA_ERROR_INVALID_SIGNATURE;
        }
    }
    else
    {
#ifdef TFM_BUILD
        PSACrypto_s_secureCB->length = actual_hash_length;
#else
        /* For verification the hash_length provided must be the same as the
         * actual_hash_length.
         */
        if (actual_hash_length != hash_length)
        {
            status = PSA_ERROR_INVALID_SIGNATURE;
        }
        else
        {
            status = memcmp(hash, actual_hash, actual_hash_length);

            if (status != 0)
            {
                status = PSA_ERROR_INVALID_SIGNATURE;
            }
            else
            {
                status = PSA_SUCCESS;
            }
        }
#endif
    }

    /* Flush the internal hash buffers */
    if (status != PSA_SUCCESS)
    {
        /* Ignore this return value and return the previously set status */
        (void)ti_psa_hash_abort(psa_operation);
    }

    return status;
}

/*
 *  ======== ti_psa_hash_compute_sha2_internal ========
 */
static psa_status_t ti_psa_hash_compute_sha2_internal(SHA2_Handle sha2Handle,
                                                      psa_algorithm_t alg,
                                                      const uint8_t *input,
                                                      size_t input_length,
                                                      uint8_t *hash,
                                                      size_t hash_size,
                                                      size_t *hash_length)
{
#ifndef ENABLE_TI_CRYPTO_SHA2
    return PSA_ERROR_NOT_SUPPORTED;
#else
    int_fast16_t ret;
    psa_status_t status;
    size_t actual_hash_length = PSA_HASH_LENGTH(alg);

    /* Check if operation is a hash */
    if (!PSA_ALG_IS_HASH(alg))
    {
        SHA2_close(sha2Handle);
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Fill the output buffer with something that isn't a valid hash (barring an
     * attack on the hash and deliberately-crafted input), in case the caller
     * doesn't check the return status properly.
     */
    *hash_length = actual_hash_length;

    /* If hash_size is 0 then hash may be NULL and then the call to memset would
     * have undefined behavior.
     */
    if (hash_size != 0)
    {
        (void)memset(hash, '!', hash_size);
    }

    /* If the output length is smaller than the hash, then report user mistake
     * for this alg that does not support a shortened hash.
     */
    if (hash_size < actual_hash_length)
    {
        SHA2_close(sha2Handle);
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    status = psa_set_sha2_hash_type(sha2Handle, alg);
    if (status != PSA_SUCCESS)
    {
        SHA2_close(sha2Handle);
        return status;
    }

    ret    = SHA2_hashData(sha2Handle, input, input_length, hash);
    status = map_SHA2_status(ret);

    /* Close temporary handle */
    if (((SHA2_Object *)sha2Handle->object)->returnBehavior == SHA2_RETURN_BEHAVIOR_CALLBACK)
    {
        /* Set a marker so that the secure callback knows that the SHA2_Handle can be closed, since
         * this is a one-shot operation.
         */
        ((SHA2_Object *)sha2Handle->object)->isOpen = false;
    }
    else
    {
        SHA2_close(sha2Handle);
    }

    return status;
#endif
}

#ifdef ENABLE_TI_CRYPTO_SHA3
/*
 *  ======== ti_psa_hash_compute_sha3_internal ========
 */
static psa_status_t ti_psa_hash_compute_sha3_internal(SHA3_Handle sha3Handle,
                                                      psa_algorithm_t alg,
                                                      const uint8_t *input,
                                                      size_t input_length,
                                                      uint8_t *hash,
                                                      size_t hash_size,
                                                      size_t *hash_length)
{
    int_fast16_t ret;
    psa_status_t status;
    size_t actual_hash_length = PSA_HASH_LENGTH(alg);

    /* Check if operation is a hash */
    if (!PSA_ALG_IS_HASH(alg))
    {
        SHA3_close(sha3Handle);
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Fill the output buffer with something that isn't a valid hash (barring an
     * attack on the hash and deliberately-crafted input), in case the caller
     * doesn't check the return status properly.
     */
    *hash_length = actual_hash_length;

    /* If hash_size is 0 then hash may be NULL and then the call to memset would
     * have undefined behavior.
     */
    if (hash_size != 0)
    {
        (void)memset(hash, '!', hash_size);
    }

    /* If the output length is smaller than the hash, then report user mistake
     * for this alg that does not support a shortened hash.
     */
    if (hash_size < actual_hash_length)
    {
        SHA3_close(sha3Handle);
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    status = psa_set_sha3_hash_type(sha3Handle, alg);
    if (status != PSA_SUCCESS)
    {
        SHA3_close(sha3Handle);
        return status;
    }

    ret    = SHA3_hashData(sha3Handle, input, input_length, hash);
    status = map_SHA2_status(ret);

    /* Close temporary handle */
    if (((SHA3XXF3HSM_Object *)sha3Handle->object)->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
    {
        /* Set a marker so that the secure callback knows that the SHA3_Handle can be closed, since
         * this is a one-shot operation.
         */
        ((SHA3XXF3HSM_Object *)sha3Handle->object)->isOpen = false;
    }
    else
    {
        SHA3_close(sha3Handle);
    }

    return status;
}
#endif /* ENABLE_TI_CRYPTO_SHA3 */

/*
 *  ======== ti_psa_hash_compute ========
 */
psa_status_t ti_psa_hash_compute(psa_algorithm_t alg,
                                 const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *hash,
                                 size_t hash_size,
                                 size_t *hash_length)
{
#ifdef ENABLE_TI_CRYPTO_SHA3
    if (PSA_ALG_IS_SHA3(alg))
    {
        SHA3_Config sha3Config;
        SHA3XXF3HSM_Object sha3Object;
        SHA3_Handle sha3Handle = psa_sha3_construct(&sha3Config, &sha3Object);

        if (sha3Handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* This function will take care of closing the handle */
        return ti_psa_hash_compute_sha3_internal(sha3Handle, alg, input, input_length, hash, hash_size, hash_length);
    }
#endif

#ifndef ENABLE_TI_CRYPTO_SHA2
    return PSA_ERROR_NOT_SUPPORTED;
#else
    SHA2_Config sha2Config;
    SHA2_Object sha2Object;

    /* Construct temporary handle for one-shot operation */
    SHA2_Handle sha2Handle = psa_sha2_construct(&sha2Config, &sha2Object);

    if (sha2Handle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* This function will take care of closing the handle */
    return ti_psa_hash_compute_sha2_internal(sha2Handle, alg, input, input_length, hash, hash_size, hash_length);
#endif
}

/*
 *  ======== ti_psa_hash_compare ========
 */
psa_status_t ti_psa_hash_compare(psa_algorithm_t alg,
                                 const uint8_t *input,
                                 size_t input_length,
                                 const uint8_t *hash,
                                 size_t hash_length)
{
    int rc;
    psa_status_t status;
    size_t actual_hash_length;
    uint8_t actual_hash[PSA_HASH_LENGTH(PSA_ALG_SHA_512)];

    if (!PSA_ALG_IS_HASH(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

#ifdef TFM_BUILD
    if (psa_crypto_ns_caller)
    {
        /* Compute the hash and write to secure CB buffer. To allow the
         * computation to be completed in callback mode, the hash comparision
         * will be completed within the NS client. Calling the top-level
         * ti_psa_hash_compute function means callback mode is used.
         */
        status = ti_psa_hash_compute(alg,
                                     input,
                                     input_length,
                                     &PSACrypto_s_secureCB->buffer[0],
                                     hash_length,
                                     &PSACrypto_s_secureCB->length);
    }
    else
#endif
    {
        /* Compute the hash - create our own handle, so that we can determine the return behavior needed.
         * This is important if multiple SL API calls are made within one PSA call. In this case,
         * only one SL API call is made, so we can construct with the default return behavior per
         * build configuration. The return behavior set by the construct() function also depends
         * on NS/S caller in TFM-enabled builds.
         */
#ifdef ENABLE_TI_CRYPTO_SHA3
        if (PSA_ALG_IS_SHA3(alg))
        {
            SHA3_Config sha3Config;
            SHA3XXF3HSM_Object sha3Object;
            SHA3_Handle sha3Handle = psa_sha3_construct(&sha3Config, &sha3Object);

            if (sha3Handle == NULL)
            {
                return PSA_ERROR_BAD_STATE;
            }

            /* This function will also close the handle. */
            status = ti_psa_hash_compute_sha3_internal(sha3Handle,
                                                       alg,
                                                       input,
                                                       input_length,
                                                       actual_hash,
                                                       hash_length,
                                                       &actual_hash_length);
        }
        else
#endif
        {
#ifdef ENABLE_TI_CRYPTO_SHA2
            SHA2_Config sha2Config;
            SHA2_Object sha2Object;
            SHA2_Handle sha2Handle = psa_sha2_construct(&sha2Config, &sha2Object);

            if (sha2Handle == NULL)
            {
                return PSA_ERROR_BAD_STATE;
            }

            /* This function will also close the handle. */
            status = ti_psa_hash_compute_sha2_internal(sha2Handle,
                                                       alg,
                                                       input,
                                                       input_length,
                                                       actual_hash,
                                                       hash_length,
                                                       &actual_hash_length);
#else
            return PSA_ERROR_NOT_SUPPORTED;
#endif
        }

        if (status != PSA_SUCCESS)
        {
            /* In case the length was not correct for the output, we report a
             * invalid signature. Check crypto_values.h under the
             * PSA_ERROR_INVALID_ARGUMENT macro for further explanation (Only in
             * compare operation).
             */
            if (status == PSA_ERROR_BUFFER_TOO_SMALL)
            {
                status = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            /* Compare the actual hash with the provided hash */
            rc = memcmp(actual_hash, hash, hash_length);

            if (rc != 0)
            {
                status = PSA_ERROR_INVALID_SIGNATURE;
            }
        }
    }

    return status;
}

/*
 *  ======== ti_psa_hash_clone ========
 */
psa_status_t ti_psa_hash_clone(const psa_hash_operation_t *source_operation, psa_hash_operation_t *target_operation)
{
#if !defined(ENABLE_TI_CRYPTO_SHA2) && !defined(ENABLE_TI_CRYPTO_SHA3)
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status                                = PSA_ERROR_CORRUPTION_DETECTED;
    const ti_psa_hash_operation_t *ti_source_operation = &source_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    ti_psa_hash_operation_t *ti_target_operation       = &target_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if ((ti_source_operation->id == 0) || (ti_target_operation->id != 0))
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* There should be no alg in this object yet */
    if (ti_target_operation->alg != 0)
    {
        return PSA_ERROR_BAD_STATE;
    }

    #ifdef ENABLE_TI_CRYPTO_SHA2
    if (PSA_ALG_IS_SHA2(ti_source_operation->alg))
    {
        SHA2_Handle sha2Handle = psa_sha2_construct(&ti_target_operation->sha2Config, &ti_target_operation->sha2Object);

        if (sha2Handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        status = psa_set_sha2_hash_type(sha2Handle, ti_source_operation->alg);

        if (status == PSA_SUCCESS)
        {
            ti_target_operation->alg = ti_source_operation->alg;
            ti_target_operation->id  = PSA_CRYPTO_TI_DRIVER_ID;
            /* Copy over the contents of the prior driver object to the new one */
            memcpy(&ti_target_operation->sha2Object, &ti_source_operation->sha2Object, sizeof(SHA2_Object));

            /* Some SHA2 object members cannot be directly copied. If actual values are
             * needed for these variables, the driver will set them up internally.
             */
            ti_target_operation->sha2Object.input               = NULL;
            ti_target_operation->sha2Object.output              = NULL;
            ti_target_operation->sha2Object.key                 = NULL;
            ti_target_operation->sha2Object.operationInProgress = false;
        }
    }
    else
    #endif
    #ifdef ENABLE_TI_CRYPTO_SHA3
        if (PSA_ALG_IS_SHA3(ti_source_operation->alg))
    {
        SHA3_Handle sha3Handle = psa_sha3_construct(&ti_target_operation->sha3Config, &ti_target_operation->sha3Object);

        if (sha3Handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        status = psa_set_sha3_hash_type(sha3Handle, ti_source_operation->alg);

        if (status == PSA_SUCCESS)
        {
            ti_target_operation->alg = ti_source_operation->alg;
            ti_target_operation->id  = PSA_CRYPTO_TI_DRIVER_ID;
            /* Copy over the contents of the prior driver object to the new one */
            memcpy(&ti_target_operation->sha3Object, &ti_source_operation->sha3Object, sizeof(SHA3XXF3HSM_Object));

            /* Some SHA3 object members cannot be directly copied. If actual values are
             * needed for these variables, the driver will set them up internally.
             */
            ti_target_operation->sha3Object.input               = NULL;
            ti_target_operation->sha3Object.output              = NULL;
            ti_target_operation->sha3Object.key                 = NULL;
            ti_target_operation->sha3Object.operationInProgress = false;
        }
    }
    else
    #endif
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    return status;
#endif /* !ENABLE_TI_CRYPTO_SHA2 && !ENABLE_TI_CRYPTO_SHA3 */
}

/******************************************************************************/
/* Message Authentication Code (MAC) */
/******************************************************************************/

/*
 *  ======== ti_psa_mac_finalize_alg_and_key_validation ========
 */
static psa_status_t ti_psa_mac_finalize_alg_and_key_validation(psa_algorithm_t alg,
                                                               const psa_key_attributes_t *attributes,
                                                               size_t *mac_size)
{
    psa_status_t status     = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits         = psa_get_key_bits(attributes);

    if (!PSA_ALG_IS_MAC(alg))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Validate the combination of key type and algorithm */
    status = ti_psa_mac_key_can_do(alg, key_type);

    if (status == PSA_SUCCESS)
    {
        /* Get the output length for the algorithm and key combination */
        *mac_size = PSA_MAC_LENGTH(key_type, key_bits, alg);

        if (*mac_size < 4)
        {
            /* A very short MAC is too short for security since it can be
             * brute-forced. Ancient protocols with 32-bit MACs do exist, so we
             * make this our minimum, even though 32 bits is still too small for
             * security.
             */
            status = PSA_ERROR_NOT_SUPPORTED;
        }
        else if (*mac_size > PSA_MAC_LENGTH(key_type, key_bits, PSA_ALG_FULL_LENGTH_MAC(alg)))
        {
            /* It's impossible to "truncate" to a larger length than the full
             * length of the algorithm.
             */
            status = PSA_ERROR_INVALID_ARGUMENT;
        }
        else
        {
            status = PSA_SUCCESS;
        }
    }

    return status;
}

/*
 *  ======== ti_psa_mac_setup ========
 */
static psa_status_t ti_psa_mac_setup(ti_psa_mac_operation_t *operation,
                                     mbedtls_svc_key_id_t key,
                                     psa_algorithm_t alg,
                                     bool is_sign)
{
#if defined(ENABLE_TI_CRYPTO_SHA2) || defined(ENABLE_TI_CRYPTO_SHA3) || defined(ENABLE_TI_CRYPTO_AESCMAC)
    int_fast16_t ret;
#endif
    psa_status_t status             = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;

    if (operation->id != 0)
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    status = ti_psa_mac_finalize_alg_and_key_validation(alg, &attributes, &operation->mac_size);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes,
                                            (is_sign) ? PSA_KEY_USAGE_SIGN_MESSAGE : PSA_KEY_USAGE_VERIFY_MESSAGE,
                                            alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    size_t keyBits = psa_get_key_bits(&attributes);

    KeyStore_PSA_initKey(&operation->cryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);

    operation->is_sign = is_sign;

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    psa_algorithm_t macAlg = PSA_ALG_FULL_LENGTH_MAC(alg);

    if ((macAlg == PSA_ALG_CMAC) || (macAlg == PSA_ALG_CBC_MAC))
    {
#ifdef ENABLE_TI_CRYPTO_AESCMAC

        AESCMAC_Handle handle = psa_aescmac_get_handle(operation, macAlg);

        if (handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        if (is_sign)
        {
            ret = AESCMAC_setupSign(handle, &operation->cryptoKey);
        }
        else
        {
            ret = AESCMAC_setupVerify(handle, &operation->cryptoKey);
        }

        status = map_AES_status(ret);
#endif /* ENABLE_TI_CRYPTO_AESCMAC */
    }
    else if (PSA_ALG_IS_HMAC(alg))
    {
        psa_algorithm_t hashAlg = PSA_ALG_HMAC_GET_HASH(alg);

#ifdef ENABLE_TI_CRYPTO_SHA2
        if (PSA_ALG_IS_SHA2(hashAlg))
        {
            SHA2_Handle sha2Handle = psa_sha2_construct(&operation->driver.sha2.sha2Config,
                                                        &operation->driver.sha2.sha2Object);
            /* This call will handle checking supported alg */
            status                 = psa_set_sha2_hash_type(sha2Handle, hashAlg);

            if (status == PSA_SUCCESS)
            {
    #ifdef TFM_BUILD
                /* Preserves previous behavior for NS callers to have setupHmac be in polling mode.
                 * No change for S callers, which already have polling mode set via psa_sha2_construct.
                 */
                psa_sha2_set_return_behavior(sha2Handle, PSA_POLLING_MODE);
    #endif
                ret    = SHA2_setupHmac(sha2Handle, &operation->cryptoKey);
                status = map_SHA2_status(ret);

    #ifdef TFM_BUILD
                if (psa_crypto_ns_caller)
                {
                    /* Restore SHA2 callback return behavior - only for NS callers. For secure callers,
                     * we will want all steps of the operation to be in polling mode.
                     */
                    psa_sha2_set_return_behavior(sha2Handle, PSA_CALLBACK_MODE);
                }
    #endif
            }
        }
        else
#endif
#ifdef ENABLE_TI_CRYPTO_SHA3
            if (PSA_ALG_IS_SHA3(hashAlg))
        {
            SHA3_Handle sha3Handle = psa_sha3_construct(&operation->driver.sha3.sha3Config,
                                                        &operation->driver.sha3.sha3Object);

            status = psa_set_sha3_hash_type(sha3Handle, hashAlg);

            if (status == PSA_SUCCESS)
            {
                ret    = SHA3_setupHmac(sha3Handle, &operation->cryptoKey);
                status = map_SHA2_status(ret);
            }
        }
        else
#endif
        {
            status = PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else
    {
        status = PSA_ERROR_INVALID_ARGUMENT;
    }

    if (status == PSA_SUCCESS)
    {
        /* Store the algorithm as the full length version to make algorithm
         * checking easier. No information is lost since the mac length is
         * stored in operation->mac_length.
         */
        operation->alg                   = PSA_ALG_FULL_LENGTH_MAC(alg);
        operation->id                    = PSA_CRYPTO_TI_DRIVER_ID;
        operation->unprocessed_len       = 0;
        operation->curr_unprocessed_data = &operation->unprocessedData[0];
    }

    return status;
}

/*
 *  ======== ti_psa_mac_sign_setup ========
 */
psa_status_t ti_psa_mac_sign_setup(psa_mac_operation_t *psa_operation, mbedtls_svc_key_id_t key, psa_algorithm_t alg)
{
    ti_psa_mac_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    return ti_psa_mac_setup(operation, key, alg, true);
}

/*
 *  ======== ti_psa_mac_verify_setup ========
 */
psa_status_t ti_psa_mac_verify_setup(psa_mac_operation_t *psa_operation, mbedtls_svc_key_id_t key, psa_algorithm_t alg)
{
    ti_psa_mac_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    return ti_psa_mac_setup(operation, key, alg, false);
}

#ifdef ENABLE_TI_CRYPTO_AESCMAC

/*
 *  ======== ti_psa_mac_cancel_internal ========
 */
static void ti_psa_mac_cancel_internal(ti_psa_mac_operation_t *operation)
{
    AESCMAC_Handle handle = psa_aescmac_get_handle(operation, operation->alg);

    #ifdef TFM_BUILD
    if (psa_crypto_ns_caller)
    {
        psa_aescmac_set_return_behavior(handle, PSA_POLLING_MODE);
    }
    #endif

    /* Always returns success */
    (void)AESCMAC_cancelOperation(handle);

    #ifdef TFM_BUILD
    if (psa_crypto_ns_caller)
    {
        psa_aescmac_set_return_behavior(handle, PSA_CALLBACK_MODE);
    }
    #endif
}

/*
 *  ======== ti_psa_mac_update_internal ========
 */
static psa_status_t ti_psa_mac_update_internal(ti_psa_mac_operation_t *operation,
                                               psa_algorithm_t alg,
                                               const uint8_t *input,
                                               size_t input_length,
                                               bool isFinalOp)
{
    #ifndef TFM_BUILD
    (void)isFinalOp;
    #endif
    int_fast16_t ret;
    psa_status_t status;

    AESCMAC_Handle handle = psa_aescmac_get_handle(operation, alg);

    if (handle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    AESCMAC_Operation aescmacOp;

    AESCMAC_Operation_init(&aescmacOp);
    aescmacOp.input       = (uint8_t *)input;
    aescmacOp.inputLength = input_length;

    #ifdef TFM_BUILD
    if (!isFinalOp && psa_crypto_ns_caller)
    {
        psa_aescmac_set_return_behavior(handle, PSA_POLLING_MODE);
    }
    #endif

    ret    = AESCMAC_addData(handle, &aescmacOp);
    status = map_AES_status(ret);

    #ifdef TFM_BUILD
    if (!isFinalOp && psa_crypto_ns_caller)
    {
        psa_aescmac_set_return_behavior(handle, PSA_CALLBACK_MODE);
    }
    #endif

    return status;
}
#endif

/*
 *  ======== ti_psa_mac_abort ========
 */
psa_status_t ti_psa_mac_abort(psa_mac_operation_t *psa_operation)
{
    psa_status_t status;
    ti_psa_mac_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    /* Aborting a non-active operation is allowed */
    if (operation->id == 0U)
    {
        return PSA_SUCCESS;
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if ((operation->alg == PSA_ALG_CMAC) || (operation->alg == PSA_ALG_CBC_MAC))
    {
#ifdef ENABLE_TI_CRYPTO_AESCMAC
        ti_psa_mac_cancel_internal(operation);
        status = PSA_SUCCESS;
#endif
    }
    else if (PSA_ALG_IS_HMAC(operation->alg))
    {
        psa_algorithm_t hashAlg = PSA_ALG_HMAC_GET_HASH(operation->alg);

#ifdef ENABLE_TI_CRYPTO_SHA2
        if (PSA_ALG_IS_SHA2(hashAlg))
        {
            /* Clear internal SHA2 buffers */
            SHA2_reset((SHA2_Handle)&operation->driver.sha2.sha2Config);
            status = PSA_SUCCESS;
        }
        else
#endif
#ifdef ENABLE_TI_CRYPTO_SHA3
            if (PSA_ALG_IS_SHA3(hashAlg))
        {
            /* Clear internal SHA3 buffers */
            SHA3_reset((SHA3_Handle)&operation->driver.sha3.sha3Config);
            status = PSA_SUCCESS;
        }
        else
#endif
        {
            status = PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else
    {
        status = PSA_ERROR_INVALID_ARGUMENT;
    }

    *operation = TI_PSA_MAC_OPERATION_INIT;

    return status;
}

/*
 *  ======== ti_psa_mac_update ========
 */
psa_status_t ti_psa_mac_update(psa_mac_operation_t *psa_operation, const uint8_t *input, size_t input_length)
{
    int_fast16_t ret;
    psa_status_t status               = PSA_SUCCESS;
    ti_psa_mac_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if (operation->id == 0U)
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Don't require hash implementations to behave correctly on a zero-length
     * input, which may have an invalid pointer.
     */
    if (input_length == 0)
    {
#ifdef TFM_BUILD
        return PSA_OPERATION_COMPLETE;
#else
        return PSA_SUCCESS;
#endif
    }

    if (operation->alg == 0)
    {
        return PSA_ERROR_BAD_STATE;
    }

    if (!PSA_ALG_IS_MAC(operation->alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if ((operation->alg == PSA_ALG_CMAC) || (operation->alg == PSA_ALG_CBC_MAC))
    {
#ifdef ENABLE_TI_CRYPTO_AESCMAC
        /* Input needs to be buffered (and the final block of data needs to be
         * saved for use in ti_psa_mac_sign_finish). the code must buffer all input
         * but and must leave the unprocessedData buffer unempty. In other
         * words, AESCMAC_addData must not be called on any data that could
         * potentially be the last data passed in using this function.
         */
        size_t totalUnprocessedLen = operation->unprocessed_len + input_length;

        /* Not enough total data to make up one block */
        if (totalUnprocessedLen < PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
        {
            /* Buffer the data and wait for more data to arrive */
            (void)memcpy(operation->curr_unprocessed_data + operation->unprocessed_len, input, input_length);
            operation->unprocessed_len = totalUnprocessedLen;

    #ifdef TFM_BUILD
            return PSA_OPERATION_COMPLETE;
    #else
            return PSA_SUCCESS;
    #endif
        }

        /* Enough data to make up at least a single block. Append enough input data
         * to the existing unprocessed data to build a full block.
         */
        size_t amountToCopy = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE - operation->unprocessed_len;
        (void)memcpy(operation->curr_unprocessed_data + operation->unprocessed_len, input, amountToCopy);
        input += amountToCopy;
        operation->unprocessed_len += amountToCopy;

        /* Do not add the data if it could be the last block of data */
        totalUnprocessedLen -= PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;

        if (totalUnprocessedLen == 0)
        {
    #ifdef TFM_BUILD
            return PSA_OPERATION_COMPLETE;
    #else
            return PSA_SUCCESS;
    #endif
        }

        /* Get the largest multiple of the block size that is less than the
         * number of bytes of unprocessed data.
         */
        size_t amountToAdd = (totalUnprocessedLen / PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE) * PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;

        bool isFinalOp = true;

        if (amountToAdd > 0)
        {
            isFinalOp = false;
        }

        status = ti_psa_mac_update_internal(operation,
                                            operation->alg,
                                            operation->curr_unprocessed_data,
                                            PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE,
                                            isFinalOp);

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        operation->unprocessed_len = 0;

    #ifdef TFM_BUILD
        /* Update the current pointer to unprocessed data to avoid potentially
         * modifying the input buffer before the crypto engine has processed it
         * when the SL driver is operating with callback return behavior.
         */
        if (operation->curr_unprocessed_data == &operation->unprocessedData[0])
        {
            operation->curr_unprocessed_data = &operation->unprocessedData[PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE];
        }
        else
        {
            operation->curr_unprocessed_data = &operation->unprocessedData[0];
        }
    #endif

        /* To ensure that not all of the data is added */
        if (amountToAdd == totalUnprocessedLen)
        {
            amountToAdd -= PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;
        }

        if (amountToAdd > 0)
        {
            isFinalOp = true;

            /* Add any left over data to the unprocessed data buffer. This must
             * be done prior to ti_psa_mac_update_internal() in case callback
             * return behavior is used.
             */
            (void)memcpy(operation->curr_unprocessed_data, (input + amountToAdd), (totalUnprocessedLen - amountToAdd));
            operation->unprocessed_len = totalUnprocessedLen - amountToAdd;

            status = ti_psa_mac_update_internal(operation, operation->alg, input, amountToAdd, isFinalOp);
        }
        else
        {
            /* Add any left over data to the unprocessed data buffer */
            (void)memcpy(operation->curr_unprocessed_data, input, totalUnprocessedLen);
            operation->unprocessed_len = totalUnprocessedLen;

    #ifdef TFM_BUILD
            if (!isFinalOp)
            {
                status = PSA_OPERATION_COMPLETE;
            }
    #endif
        }

#endif /* ENABLE_TI_CRYPTO_AESCMAC */
    }
    else if (PSA_ALG_IS_HMAC(operation->alg))
    {
        psa_algorithm_t hashAlg = PSA_ALG_HMAC_GET_HASH(operation->alg);

#ifdef ENABLE_TI_CRYPTO_SHA2
        if (PSA_ALG_IS_SHA2(hashAlg))
        {
            if (operation->driver.sha2.sha2Object.isOpen == false)
            {
                return PSA_ERROR_BAD_STATE;
            }

            ret    = SHA2_addData(&operation->driver.sha2.sha2Config, input, input_length);
            status = map_SHA2_status(ret);
        }
        else
#endif
#ifdef ENABLE_TI_CRYPTO_SHA3
            if (PSA_ALG_IS_SHA3(hashAlg))
        {
            if (operation->driver.sha3.sha3Object.isOpen == false)
            {
                return PSA_ERROR_BAD_STATE;
            }

            ret    = SHA3_addData((SHA3_Handle)&operation->driver.sha3.sha3Config, input, input_length);
            status = map_SHA2_status(ret);
        }
        else
#endif
        {
            status = PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else
    {
        (void)ret;
        status = PSA_ERROR_INVALID_ARGUMENT;
    }

    return status;
}

/*
 *  ======== ti_psa_mac_sign_finish ========
 */
psa_status_t ti_psa_mac_sign_finish(psa_mac_operation_t *psa_operation,
                                    uint8_t *mac,
                                    size_t mac_size,
                                    size_t *mac_length)
{
    int_fast16_t ret;
    psa_status_t status;
    ti_psa_mac_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if (operation->id == 0U)
    {
        status = PSA_ERROR_BAD_STATE;
        goto exit;
    }

    if (!operation->is_sign)
    {
        status = PSA_ERROR_BAD_STATE;
        goto exit;
    }

    /* Sanity check. This will guarantee that mac_size != 0 (and so mac != NULL)
     * once all the error checks are done.
     */
    if (operation->mac_size == 0U)
    {
        status = PSA_ERROR_BAD_STATE;
        goto exit;
    }

    if (mac_size < operation->mac_size)
    {
        status = PSA_ERROR_BUFFER_TOO_SMALL;
        goto exit;
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    /* Use the default computed mac size or the mac_size passed in */
    if ((operation->alg == PSA_ALG_CMAC) || (operation->alg == PSA_ALG_CBC_MAC))
    {
#ifdef ENABLE_TI_CRYPTO_AESCMAC
        AESCMAC_Handle handle = psa_aescmac_get_handle(operation, operation->alg);

        if (handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }
        AESCMAC_Operation aescmacOp;

        AESCMAC_Operation_init(&aescmacOp);
        aescmacOp.input       = operation->curr_unprocessed_data;
        aescmacOp.inputLength = operation->unprocessed_len;
        aescmacOp.mac         = mac;
        aescmacOp.macLength   = operation->mac_size;

        /* AESCMAC_finalize does not accept input lengths of zero, so if there
         * is no input, call oneStepSign, otherwise call finalize.
         */
        if (operation->unprocessed_len == 0)
        {
            ti_psa_mac_cancel_internal(operation);

            ret = AESCMAC_oneStepSign(handle, &aescmacOp, &operation->cryptoKey);
        }
        else
        {
            ret = AESCMAC_finalize(handle, &aescmacOp);
        }

        status = map_AES_status(ret);
#endif
    }
    else if (PSA_ALG_IS_HMAC(operation->alg))
    {
        psa_algorithm_t hashAlg = PSA_ALG_HMAC_GET_HASH(operation->alg);

#ifdef ENABLE_TI_CRYPTO_SHA2
        if (PSA_ALG_IS_SHA2(hashAlg))
        {
            ret    = SHA2_finalizeHmac(&operation->driver.sha2.sha2Config, mac);
            status = map_SHA2_status(ret);

    #ifdef TFM_BUILD
            if (psa_crypto_ns_caller)
            {
                /* Mark the segmented operation as complete so that the secure callback can at least
                 * close the driver handle.
                 */
                ((SHA2_Object *)operation->driver.sha2.sha2Config.object)->isOpen = false;
            }
            else
            {
                SHA2_close((SHA2_Handle)&operation->driver.sha2.sha2Config);
            }
    #endif
        }
        else
#endif
#ifdef ENABLE_TI_CRYPTO_SHA3
            if (PSA_ALG_IS_SHA3(hashAlg))
        {
            ret    = SHA3_finalizeHmac((SHA3_Handle)&operation->driver.sha3.sha3Config, mac);
            status = map_SHA2_status(ret);
        }
        else
#endif
        {
            status = PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else
    {
        (void)ret;
        status = PSA_ERROR_INVALID_ARGUMENT;
    }

exit:
    if (status != PSA_SUCCESS)
    {
        operation->mac_size = 0;
    }

#ifdef TFM_BUILD
    PSACrypto_s_secureCB->length = operation->mac_size;

    /* NS client will handle calling ti_psa_mac_abort() after verifying the final
     * result and invalidating excess room in output buffer.
     */
#else
    *mac_length = operation->mac_size;

    /* In case of success, set the potential excess room in the output buffer to
     * an invalid value, to avoid potentially leaking a longer MAC. In case of
     * error, set the output length and content to a safe default, such that in
     * case the caller misses an error check, the output would be an
     * unachievable MAC.
     */
    if (mac_size > operation->mac_size)
    {
        (void)memset(&mac[operation->mac_size], '!', mac_size - operation->mac_size);
    }

    (void)ti_psa_mac_abort(psa_operation);
#endif

    return status;
}

/*
 *  ======== ti_psa_mac_verify_finish ========
 */
psa_status_t ti_psa_mac_verify_finish(psa_mac_operation_t *psa_operation, const uint8_t *mac, size_t mac_length)
{
    int_fast16_t ret;
    psa_status_t status;
    ti_psa_mac_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if (operation->id == 0U)
    {
        status = PSA_ERROR_BAD_STATE;
        goto exit;
    }

    if (operation->is_sign)
    {
        status = PSA_ERROR_BAD_STATE;
        goto exit;
    }

    /* Sanity check. This will guarantee that mac_size != 0 (and so mac != NULL)
     * once all the error checks are done.
     */
    if (operation->mac_size == 0)
    {
        status = PSA_ERROR_BAD_STATE;
        goto exit;
    }

    if (mac_length != operation->mac_size)
    {
        status = PSA_ERROR_INVALID_SIGNATURE;
        goto exit;
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    /* Use the default computed mac size or the mac_size passed in */
    if ((operation->alg == PSA_ALG_CMAC) || (operation->alg == PSA_ALG_CBC_MAC))
    {
#ifdef ENABLE_TI_CRYPTO_AESCMAC
        AESCMAC_Handle handle = psa_aescmac_get_handle(operation, operation->alg);

        if (handle == NULL)
        {
            status = PSA_ERROR_BAD_STATE;
            goto exit;
        }
        AESCMAC_Operation aescmacOp;

        AESCMAC_Operation_init(&aescmacOp);
        aescmacOp.input       = operation->curr_unprocessed_data;
        aescmacOp.inputLength = operation->unprocessed_len;
        aescmacOp.mac         = (uint8_t *)mac;
        aescmacOp.macLength   = operation->mac_size;

        /* AESCMAC_finalize does not accept input lengths of zero, so if there
         * is no input, call oneStepVerify, otherwise call finalize.
         */
        if (operation->unprocessed_len == 0)
        {
            ti_psa_mac_cancel_internal(operation);

            ret = AESCMAC_oneStepVerify(handle, &aescmacOp, &operation->cryptoKey);
        }
        else
        {
            ret = AESCMAC_finalize(handle, &aescmacOp);
        }

        status = map_AES_status(ret);
#endif
    }
    else if (PSA_ALG_IS_HMAC(operation->alg))
    {
        psa_algorithm_t hashAlg = PSA_ALG_HMAC_GET_HASH(operation->alg);

#ifdef ENABLE_TI_CRYPTO_SHA2
        if (PSA_ALG_IS_SHA2(hashAlg))
        {
            int rc;

            if (operation->driver.sha2.sha2Object.isOpen == false)
            {
                status = PSA_ERROR_BAD_STATE;
                goto exit;
            }

    #ifdef TFM_BUILD
            if (psa_crypto_ns_caller)
            {
                ret    = SHA2_finalizeHmac(&operation->driver.sha2.sha2Config, &PSACrypto_s_secureCB->buffer[0]);
                status = map_SHA2_status(ret);
            }
            else
    #endif
            {
                uint8_t actualMAC[PSA_HMAC_MAX_HASH_BLOCK_SIZE] = {0};

                ret    = SHA2_finalizeHmac(&operation->driver.sha2.sha2Config, actualMAC);
                status = map_SHA2_status(ret);

                if (status == PSA_SUCCESS)
                {
                    rc = memcmp(actualMAC, mac, operation->mac_size);

                    if (rc != 0)
                    {
                        status = PSA_ERROR_INVALID_SIGNATURE;
                    }
                }
            }

    #ifdef TFM_BUILD
            if (psa_crypto_ns_caller)
            {
                /* Mark the segmented operation as complete so that the secure callback can at least
                 * close the driver handle.
                 */
                ((SHA2_Object *)operation->driver.sha2.sha2Config.object)->isOpen = false;
            }
            else
            {
                SHA2_close((SHA2_Handle)&operation->driver.sha2.sha2Config);
            }
    #endif
        }
        else
#endif
#ifdef ENABLE_TI_CRYPTO_SHA3
            if (PSA_ALG_IS_SHA3(hashAlg))
        {
            int rc;

            if (operation->driver.sha3.sha3Object.isOpen == false)
            {
                status = PSA_ERROR_BAD_STATE;
                goto exit;
            }

            uint8_t actualMAC[PSA_HMAC_MAX_HASH_BLOCK_SIZE] = {0};

            ret    = SHA3_finalizeHmac((SHA3_Handle)&operation->driver.sha3.sha3Config, actualMAC);
            status = map_SHA2_status(ret);

            if (status == PSA_SUCCESS)
            {
                rc = memcmp(actualMAC, mac, operation->mac_size);

                if (rc != 0)
                {
                    status = PSA_ERROR_INVALID_SIGNATURE;
                }
            }
        }
        else
#endif
        {
            status = PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else
    {
        (void)ret;
        status = PSA_ERROR_INVALID_ARGUMENT;
    }

exit:
#ifdef TFM_BUILD
    /* Do nothing. NS client will handle calling ti_psa_mac_abort() after verifying
     * the MAC.
     */
#else
    (void)ti_psa_mac_abort(psa_operation);
#endif

    return status;
}

/*
 *  ======== ti_psa_mac_compute ========
 */
psa_status_t ti_psa_mac_compute(mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *mac,
                                size_t mac_size,
                                size_t *mac_length)
{
    int_fast16_t ret;
    psa_status_t status             = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    size_t operation_mac_size       = 0;
    psa_algorithm_t algBase;
    size_t keyBits;
    CryptoKey cryptoKey;

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    keyBits = psa_get_key_bits(&attributes);

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_SIGN_MESSAGE, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Compute operation mac size */
    status = ti_psa_mac_finalize_alg_and_key_validation(alg, &attributes, &operation_mac_size);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    if (mac_size < operation_mac_size)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    KeyStore_PSA_initKey(&cryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);

    algBase = PSA_ALG_FULL_LENGTH_MAC(alg);

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if ((algBase == PSA_ALG_CMAC) || (algBase == PSA_ALG_CBC_MAC))
    {
#ifdef ENABLE_TI_CRYPTO_AESCMAC
        AESCMAC_Config aescmacConfig;
        AESCMAC_Object aescmacObject;
        AESCMAC_Handle handle;

        if (algBase == PSA_ALG_CMAC)
        {
            handle = psa_aescmac_construct(&aescmacConfig, &aescmacObject);
        }
        else
        {
            handle = psa_aescbcmac_construct(&aescmacConfig, &aescmacObject);
        }

        if (handle == NULL)
        {
            status = PSA_ERROR_BAD_STATE;
        }
        else
        {
            AESCMAC_Operation aescmacOp;
            AESCMAC_Operation_init(&aescmacOp);
            aescmacOp.input       = (uint8_t *)input;
            aescmacOp.inputLength = input_length;
            aescmacOp.mac         = mac;
            aescmacOp.macLength   = operation_mac_size;

            ret    = AESCMAC_oneStepSign(handle, &aescmacOp, &cryptoKey);
            status = map_AES_status(ret);

            if (((AESCMAC_Object *)handle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
            {
                /* Set a marker so that the secure callback knows that the handle can be closed, since
                 * this is a one-shot operation.
                 */
                ((AESCMAC_Object *)handle->object)->common.isOpen = false;
            }
            else
            {
                AESCMAC_close(handle);
            }
        }
#endif
    }
    else if (PSA_ALG_IS_HMAC(alg))
    {
#ifdef ENABLE_TI_CRYPTO_SHA2
        psa_algorithm_t hashAlg = PSA_ALG_HMAC_GET_HASH(alg);
        SHA2_Config sha2Config;
        SHA2_Object sha2Object;
        /* This constructs a handle with the appropriate return behavior per configuration.
         * Blocking for S-only, Polling for S caller in S/NS, Callback for NS caller in S/NS.
         */
        SHA2_Handle sha2Handle = psa_sha2_construct(&sha2Config, &sha2Object);

        if (sha2Handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        status = psa_set_sha2_hash_type(sha2Handle, hashAlg);

        if (status == PSA_SUCCESS)
        {
            ret    = SHA2_hmac(sha2Handle, &cryptoKey, input, input_length, mac);
            status = map_SHA2_status(ret);
        }

        /* Close temporary handle */
        if (sha2Object.returnBehavior == SHA2_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the SHA2_Handle can be closed, since
             * this is a one-shot operation.
             */
            sha2Object.isOpen = false;
        }
        else
        {
            SHA2_close(sha2Handle);
        }
#endif
    }
#ifdef ENABLE_TI_CRYPTO_SHA3
    else if (PSA_ALG_IS_HMAC(alg) && PSA_ALG_IS_SHA3(PSA_ALG_HMAC_GET_HASH(alg)))
    {
        psa_algorithm_t hashAlg = PSA_ALG_HMAC_GET_HASH(alg);
        SHA3_Config sha3Config;
        SHA3XXF3HSM_Object sha3Object;
        SHA3_Handle sha3Handle = psa_sha3_construct(&sha3Config, &sha3Object);

        if (sha3Handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        status = psa_set_sha3_hash_type(sha3Handle, hashAlg);

        if (status == PSA_SUCCESS)
        {
            ret    = SHA3_hmac(sha3Handle, &cryptoKey, input, input_length, mac);
            status = map_SHA2_status(ret);
        }

        /* Close temporary handle */
        if (sha3Object.returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
        {
            sha3Object.isOpen = false;
        }
        else
        {
            SHA3_close(sha3Handle);
        }
    }
#endif
    else
    {
        (void)ret;
        /* Do nothing */
    }

    if (status == PSA_SUCCESS)
    {
        *mac_length = operation_mac_size;
    }

    return status;
}

/*
 *  ======== ti_psa_mac_verify ========
 */
psa_status_t ti_psa_mac_verify(mbedtls_svc_key_id_t key,
                               psa_algorithm_t alg,
                               const uint8_t *input,
                               size_t input_length,
                               const uint8_t *mac,
                               size_t mac_length)
{
    int_fast16_t ret;
    psa_status_t status             = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    size_t operation_mac_size       = 0;
    size_t keyBits;
    psa_algorithm_t algBase;
    CryptoKey cryptoKey;

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    keyBits = psa_get_key_bits(&attributes);

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_VERIFY_MESSAGE, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Compute operation mac size */
    status = ti_psa_mac_finalize_alg_and_key_validation(alg, &attributes, &operation_mac_size);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    if (mac_length < operation_mac_size)
    {
        return PSA_ERROR_INVALID_SIGNATURE;
    }

    KeyStore_PSA_initKey(&cryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);

    algBase = PSA_ALG_FULL_LENGTH_MAC(alg);

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if ((algBase == PSA_ALG_CMAC) || (algBase == PSA_ALG_CBC_MAC))
    {
#ifdef ENABLE_TI_CRYPTO_AESCMAC
        AESCMAC_Config aescmacConfig;
        AESCMAC_Object aescmacObject;
        AESCMAC_Handle handle;

        if (algBase == PSA_ALG_CMAC)
        {
            handle = psa_aescmac_construct(&aescmacConfig, &aescmacObject);
        }
        else
        {
            handle = psa_aescbcmac_construct(&aescmacConfig, &aescmacObject);
        }

        if (handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }
        AESCMAC_Operation aescmacOp;

        AESCMAC_Operation_init(&aescmacOp);
        aescmacOp.input       = (uint8_t *)input;
        aescmacOp.inputLength = input_length;
        aescmacOp.mac         = (uint8_t *)mac;
        aescmacOp.macLength   = mac_length;

        ret    = AESCMAC_oneStepVerify(handle, &aescmacOp, &cryptoKey);
        status = map_AES_status(ret);

        if (((AESCMAC_Object *)handle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the handle can be closed, since
             * this is a one-shot operation.
             */
            ((AESCMAC_Object *)handle->object)->common.isOpen = false;
        }
        else
        {
            AESCMAC_close(handle);
        }
#endif /* ENABLE_TI_CRYPTO_AESCMAC */
    }
    else if (PSA_ALG_IS_HMAC(alg))
    {
#ifdef ENABLE_TI_CRYPTO_SHA2
        psa_algorithm_t hashAlg = PSA_ALG_HMAC_GET_HASH(alg);
        SHA2_Config sha2Config;
        SHA2_Object sha2Object;
        SHA2_Handle sha2Handle = psa_sha2_construct(&sha2Config, &sha2Object);

        if (sha2Handle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* This call will handle checking supported alg */
        status = psa_set_sha2_hash_type(sha2Handle, hashAlg);
        if (status != PSA_SUCCESS)
        {
            SHA2_close(sha2Handle);
            return status;
        }

    #ifdef TFM_BUILD
        if (psa_crypto_ns_caller)
        {
            ret    = SHA2_hmac(sha2Handle, &cryptoKey, input, input_length, &PSACrypto_s_secureCB->buffer[0]);
            status = map_SHA2_status(ret);
        }
        else
    #endif
        {
            ret    = SHA2_hmac(sha2Handle, &cryptoKey, input, input_length, &localBuf[0]);
            status = map_SHA2_status(ret);

            if (status == PSA_SUCCESS)
            {
                int rc;

                /* Add a verification step here */
                rc = memcmp(localBuf, mac, mac_length);
                if (rc != 0)
                {
                    /* No match */
                    status = PSA_ERROR_INVALID_SIGNATURE;
                }
            }
        }
        /* Close temporary handle */
        if (sha2Object.returnBehavior == SHA2_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the SHA2_Handle can be closed, since
             * this is a one-shot operation.
             */
            sha2Object.isOpen = false;
        }
        else
        {
            SHA2_close(sha2Handle);
        }
#endif /* ENABLE_TI_CRYPTO_SHA2 */
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    return status;
}

/******************************************************************************/
/* Asymmetric cryptography */
/******************************************************************************/

/*
 *  ======== psa_sign_verify_check_alg ========
 */
static psa_status_t psa_sign_verify_check_alg(int input_is_message, psa_algorithm_t alg)
{
    if (input_is_message)
    {
        if (!PSA_ALG_IS_SIGN_MESSAGE(alg))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        if (PSA_ALG_IS_HASH_AND_SIGN(alg))
        {
            if (!PSA_ALG_IS_HASH(PSA_ALG_SIGN_GET_HASH(alg)))
            {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
        }
    }
    else
    {
        if (PSA_ALG_SIGN_GET_HASH(alg) == PSA_ALG_NONE)
        {
            /* Nothing to do - this is a valid case. If the alg is PSA_ALG_ECDSA_ANY, then
             * we can verify hashes by looking at the hash length.
             */
        }
        else if (!PSA_ALG_IS_HASH_AND_SIGN(alg))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        else if (PSA_ALG_SIGN_GET_HASH(alg) == PSA_ALG_ANY_HASH)
        {
            /* This wildcard cannot be used for operations - only for key policies. */
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    return PSA_SUCCESS;
}

#ifdef ENABLE_TI_CRYPTO_ECDSA
/*
 *  ======== psa_get_hash_length ========
 */
static psa_status_t psa_get_hash_length(psa_algorithm_t hash_alg, size_t *hash_size)
{
    psa_status_t status = PSA_SUCCESS;

    switch (hash_alg)
    {
        case PSA_ALG_SHA_224:
            *hash_size = SHA2_DIGEST_LENGTH_BYTES_224;
            break;

        case PSA_ALG_SHA_256:
            *hash_size = SHA2_DIGEST_LENGTH_BYTES_256;
            break;

        case PSA_ALG_SHA_384:
            *hash_size = SHA2_DIGEST_LENGTH_BYTES_384;
            break;

        case PSA_ALG_SHA_512:
            *hash_size = SHA2_DIGEST_LENGTH_BYTES_512;
            break;

        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    return status;
}
#endif

/*
 *  ======== ti_psa_sign_message ========
 */
psa_status_t ti_psa_sign_message(mbedtls_svc_key_id_t key,
                                 psa_algorithm_t alg,
                                 const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *signature,
                                 size_t signature_size,
                                 size_t *signature_length)
{
    int_fast16_t ret;
    psa_status_t status             = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_type_t keyType;
    size_t keyBits;
    size_t keyBytes;

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_SIGN_MESSAGE, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    keyType = psa_get_key_type(&attributes);
    keyBits = psa_get_key_bits(&attributes);

    *signature_length = PSA_SIGN_OUTPUT_SIZE(keyType, keyBits, alg);

    /* 1 to represent message instead of hash */
    status = psa_sign_verify_check_alg(1, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Immediately reject a zero-length signature buffer. This guarantees that
     * signature must be a valid pointer. (On the other hand, the input buffer
     * can in principle be empty since it doesn't actually have to be a hash.)
     */
    if (signature_size == 0)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (!PSA_KEY_TYPE_IS_KEY_PAIR(keyType))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    keyBytes = PSA_BITS_TO_BYTES(keyBits);

#if defined(ENABLE_TI_CRYPTO_EDDSA) || defined(ENABLE_TI_CRYPTO_ECDSA)
    CryptoKey privateKey;
    CryptoKey publicKey;
    KeyStore_PSA_initKey(&privateKey, key, keyBytes, NULL);
#endif

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (alg == PSA_ALG_PURE_EDDSA)
    {
#ifdef ENABLE_TI_CRYPTO_EDDSA
        /* The twisted Edwards curves Ed25519 */
        uint8_t *myPublicKeyMaterial;

        /* First generate public key */
        if (sizeof(localBuf) >= ECCParams_CURVE25519_LENGTH)
        {
            myPublicKeyMaterial = &localBuf[0];
        }
        else
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }

        /* Construct EDDSA handle */
        EDDSA_Config eddsaConfig;
        EDDSA_Object eddsaObject;
        EDDSA_Handle eddsaHandle = psa_eddsa_construct(&eddsaConfig, &eddsaObject);

        if (eddsaHandle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        CryptoKeyPlaintext_initBlankKey(&publicKey, myPublicKeyMaterial, ECCParams_CURVE25519_LENGTH);
        EDDSA_OperationGeneratePublicKey operation;
        EDDSA_OperationGeneratePublicKey_init(&operation);
        operation.myPrivateKey = &privateKey;
        operation.myPublicKey  = &publicKey;
    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
        /* Only non-HSM drivers utilize input curve params for EdDSA */
        operation.curve = &ECCParams_Ed25519;
    #endif

    #ifdef TFM_BUILD
        if (psa_crypto_ns_caller)
        {
            /* Set EDDSA driver to use polling mode since an additional SL API call is needed */
            psa_eddsa_set_return_behavior(eddsaHandle, PSA_POLLING_MODE);
        }
    #endif

        ret = EDDSA_generatePublicKey(eddsaHandle, &operation);

    #ifdef TFM_BUILD
        if (psa_crypto_ns_caller)
        {
            /* Set EDDSA driver to use callback mode for the final SL API call */
            psa_eddsa_set_return_behavior(eddsaHandle, PSA_CALLBACK_MODE);
        }
    #endif

        status = map_EDDSA_status(ret, false);

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        EDDSA_OperationSign eddsaSignOp;

        EDDSA_OperationSign_init(&eddsaSignOp);
    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
        /* Only non-HSM drivers utilize input curve params for EdDSA */
        eddsaSignOp.curve = &ECCParams_Ed25519;
    #endif
        eddsaSignOp.myPrivateKey           = &privateKey;
        eddsaSignOp.myPublicKey            = &publicKey;
        eddsaSignOp.preHashedMessage       = input;
        eddsaSignOp.preHashedMessageLength = input_length;
        eddsaSignOp.R                      = signature;
        eddsaSignOp.S                      = signature + (*signature_length / 2);

        ret    = EDDSA_sign(eddsaHandle, &eddsaSignOp);
        status = map_EDDSA_status(ret, false);

        if (eddsaObject.returnBehavior == EDDSA_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the EDDSA_Handle can be closed, since
             * this is a one-shot operation.
             */
            eddsaObject.isOpen = false;
        }
        else
        {
            EDDSA_close(eddsaHandle);
        }
#endif /* ENABLE_TI_CRYPTO_EDDSA */
    }
    else if (PSA_ALG_IS_RANDOMIZED_ECDSA(alg) && PSA_KEY_TYPE_IS_ECC(keyType))
    {
#ifdef ENABLE_TI_CRYPTO_ECDSA
        psa_algorithm_t hash_alg = PSA_ALG_SIGN_GET_HASH(alg);
        size_t hash_length;
        size_t hash_size;
        size_t curveBytes;
        uint8_t *hash = NULL;
        ECDSA_OperationSign ecdsaSignOp;

        ECDSA_OperationSign_init(&ecdsaSignOp);

    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        ecdsaSignOp.curveType = map_keyTypeToECDSACurveTypeHSM(keyType, keyBits);

        if (ecdsaSignOp.curveType == (ECDSA_CurveType)0)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    #elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
        ecdsaSignOp.curve = map_keyTypeToECCParams(keyType, keyBits);

        if (ecdsaSignOp.curve == NULL)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    #endif

        status = psa_get_hash_length(hash_alg, &hash_size);

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        curveBytes = PSA_BITS_TO_BYTES(psa_get_key_bits(&attributes));

        /* Per FIPS 186-4 recommendation, the hash length must provide at least as much
         * security strength as the curve length. This is satisfied when the hash length
         * at least matches the curve length, as well as when SHA-512 is used with a 521-bit
         * curve.
         */
        if ((hash_size < curveBytes) && ((hash_size != 64) && (curveBytes != 66)))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        if (hash_size <= sizeof(localBuf))
        {
            hash = &localBuf[0];
        }
        else
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    #ifdef ENABLE_TI_CRYPTO_SHA3
        if (PSA_ALG_IS_SHA3(hash_alg))
        {
            SHA3_Config sha3Config;
            SHA3XXF3HSM_Object sha3Object;
            SHA3_Handle sha3Handle = psa_sha3_construct(&sha3Config, &sha3Object);

            if (sha3Handle == NULL)
            {
                return PSA_ERROR_BAD_STATE;
            }

            /* Compute the hash - this function will close the handle for us. */
            status = ti_psa_hash_compute_sha3_internal(sha3Handle,
                                                       hash_alg,
                                                       input,
                                                       input_length,
                                                       hash,
                                                       hash_size,
                                                       &hash_length);
        }
        else
    #endif
    #ifdef ENABLE_TI_CRYPTO_SHA2
        {
            /* Construct our own SHA2 handle for control over the return behavior. */
            SHA2_Config sha2Config;
            SHA2_Object sha2Object;
            SHA2_Handle sha2Handle = psa_sha2_construct(&sha2Config, &sha2Object);

            if (sha2Handle == NULL)
            {
                return PSA_ERROR_BAD_STATE;
            }

        #ifdef TFM_BUILD
            /* For NS callers, intermediate SL calls must be in polling mode. For S callers,
             * ALL SL calls must be in polling mode. So, if this is a TFM-build, we must
             * be in polling mode for this intermediate operation. Note that this is redundant
             * for S callers, since it is set this way in psa_sha2_construct anyways.
             */
            psa_sha2_set_return_behavior(sha2Handle, PSA_POLLING_MODE);
        #endif

            /* Compute the hash - this function will close the handle for us. */
            status = ti_psa_hash_compute_sha2_internal(sha2Handle,
                                                       hash_alg,
                                                       input,
                                                       input_length,
                                                       hash,
                                                       hash_size,
                                                       &hash_length);
        }
    #else
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    #endif

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        ecdsaSignOp.myPrivateKey = &privateKey;
        ecdsaSignOp.hash         = hash;
        ecdsaSignOp.hashLength   = hash_length;
        ecdsaSignOp.r            = signature;
        ecdsaSignOp.s            = signature + (*signature_length / 2);

        /* Construct ECDSA handle */
        ECDSA_Config ecdsaConfig;
        ECDSA_Object ecdsaObject;
        ECDSA_Handle ecdsaHandle = psa_ecdsa_construct(&ecdsaConfig, &ecdsaObject);

        if (ecdsaHandle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* Generates the signature of the message hash */
        ret    = ECDSA_sign(ecdsaHandle, &ecdsaSignOp);
        status = map_ECDSA_status(ret, false);

        if (ecdsaObject.returnBehavior == ECDSA_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the ECDSA_Handle can be closed, since
             * this is a one-shot operation.
             */
            ecdsaObject.isOpen = false;
        }
        else
        {
            ECDSA_close(ecdsaHandle);
        }
#endif /* ENABLE_TI_CRYPTO_ECDSA */
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }
    /* Supported Curve Types are listed in ECDSACC26X2.h. Montgomery and
     * Edwards curve types are not currently supported.
     */

    return status;
}

/*
 *  ======== ti_psa_verify_message ========
 */
psa_status_t ti_psa_verify_message(mbedtls_svc_key_id_t key,
                                   psa_algorithm_t alg,
                                   const uint8_t *input,
                                   size_t input_length,
                                   const uint8_t *signature,
                                   size_t signature_length)
{
    int_fast16_t ret;
    psa_status_t status             = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_type_t keyType;
    psa_key_bits_t keyBits;
    psa_ecc_family_t curve;
    size_t publicKeyBytes;

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_VERIFY_MESSAGE, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    keyType = psa_get_key_type(&attributes);
    keyBits = psa_get_key_bits(&attributes);

    /* 1 to indicate message instead of hash */
    status = psa_sign_verify_check_alg(1, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Immediately reject a zero-length signature buffer. This guarantees that
     * signature must be a valid pointer. (On the other hand, the input buffer
     * can in principle be empty since it doesn't actually have to be a hash.)
     */
    if (signature_length == 0)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    curve = PSA_KEY_TYPE_ECC_GET_FAMILY(keyType);

    /* Note: The public key size for Montgomery and Twisted Edwards curves is
     * the same as the key_bytes, while the public key size for Weierstrass and
     * Brainpool curves use uncompressed format (2 x key_bytes + 1). The
     * following publicKeyBytes assignment cannot be replaced with
     * PSA_EXPORT_KEY_OUTPUT_SIZE(keyType, keyBits) because it returns the
     * uncompressed format size for Twisted Edwards curves which is incorrect.
     */
    publicKeyBytes = ((curve == PSA_ECC_FAMILY_MONTGOMERY) || (curve == PSA_ECC_FAMILY_TWISTED_EDWARDS))
                         ? PSA_BITS_TO_BYTES(keyBits)
                         : PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(keyBits);

#if defined(ENABLE_TI_CRYPTO_EDDSA) || defined(ENABLE_TI_CRYPTO_ECDSA)
    CryptoKey publicKey;
    KeyStore_PSA_initKey(&publicKey, key, publicKeyBytes, NULL);
#endif

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (alg == PSA_ALG_PURE_EDDSA)
    {
#ifdef ENABLE_TI_CRYPTO_EDDSA
        /* Construct EDDSA handle */
        EDDSA_Config eddsaConfig;
        EDDSA_Object eddsaObject;
        EDDSA_Handle eddsaHandle = psa_eddsa_construct(&eddsaConfig, &eddsaObject);

        if (eddsaHandle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        EDDSA_OperationVerify eddsaVerifyOp;

        EDDSA_OperationVerify_init(&eddsaVerifyOp);
    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X2_CC26X2) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4))
        /* Only non-HSM drivers utilize input curve params for EdDSA */
        eddsaVerifyOp.curve = &ECCParams_Ed25519;
    #endif
        eddsaVerifyOp.theirPublicKey         = &publicKey;
        eddsaVerifyOp.preHashedMessage       = input;
        eddsaVerifyOp.preHashedMessageLength = input_length;
        eddsaVerifyOp.R                      = signature;
        eddsaVerifyOp.S                      = signature + (signature_length / 2);

        ret    = EDDSA_verify(eddsaHandle, &eddsaVerifyOp);
        status = map_EDDSA_status(ret, true);

        if (eddsaObject.returnBehavior == EDDSA_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the EDDSA_Handle can be closed, since
             * this is a one-shot operation.
             */
            eddsaObject.isOpen = false;
        }
        else
        {
            EDDSA_close(eddsaHandle);
        }
#endif /* ENABLE_TI_CRYPTO_EDDSA */
    }
    else if (PSA_ALG_IS_RANDOMIZED_ECDSA(alg) && PSA_KEY_TYPE_IS_ECC(keyType))
    {
#ifdef ENABLE_TI_CRYPTO_ECDSA
        psa_algorithm_t hash_alg = PSA_ALG_SIGN_GET_HASH(alg);
        size_t hash_length;
        uint8_t *hash = NULL;
        size_t hash_size;
        size_t curveBytes;
        ECDSA_OperationVerify ecdsaVerifyOp;

        ECDSA_OperationVerify_init(&ecdsaVerifyOp);

    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        ecdsaVerifyOp.curveType = map_keyTypeToECDSACurveTypeHSM(keyType, keyBits);

        if (ecdsaVerifyOp.curveType == (ECDSA_CurveType)0)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    #elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
        ecdsaVerifyOp.curve = map_keyTypeToECCParams(keyType, keyBits);

        if (ecdsaVerifyOp.curve == NULL)
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    #endif

        status = psa_get_hash_length(hash_alg, &hash_size);

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        curveBytes = PSA_BITS_TO_BYTES(psa_get_key_bits(&attributes));

        /* Per FIPS 186-4 recommendation, the hash length must provide at least as much
         * security strength as the curve length. This is satisfied when the hash length
         * at least matches the curve length, as well as when SHA-512 is used with a 521-bit
         * curve.
         */
        if ((hash_size < curveBytes) && ((hash_size != 64) && (curveBytes != 66)))
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        if (hash_size <= sizeof(localBuf))
        {
            hash = &localBuf[0];
        }
        else
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    #ifdef ENABLE_TI_CRYPTO_SHA3
        if (PSA_ALG_IS_SHA3(hash_alg))
        {
            SHA3_Config sha3Config;
            SHA3XXF3HSM_Object sha3Object;
            SHA3_Handle sha3Handle = psa_sha3_construct(&sha3Config, &sha3Object);

            if (sha3Handle == NULL)
            {
                return PSA_ERROR_BAD_STATE;
            }

            /* Compute the hash - this function will close the handle for us. */
            status = ti_psa_hash_compute_sha3_internal(sha3Handle,
                                                       hash_alg,
                                                       input,
                                                       input_length,
                                                       hash,
                                                       hash_size,
                                                       &hash_length);
        }
        else
    #endif
    #ifdef ENABLE_TI_CRYPTO_SHA2
        {
            /* Construct our own SHA2 handle for control over the return behavior. */
            SHA2_Config sha2Config;
            SHA2_Object sha2Object;
            SHA2_Handle sha2Handle = psa_sha2_construct(&sha2Config, &sha2Object);

            if (sha2Handle == NULL)
            {
                return PSA_ERROR_BAD_STATE;
            }

        #ifdef TFM_BUILD
            /* For NS callers, intermediate SL calls must be in polling mode. For S callers,
             * ALL SL calls must be in polling mode. So, if this is a TFM-build, we must
             * be in polling mode for this intermediate operation. Note that this is redundant
             * for S callers, since it is set this way in psa_sha2_construct anyways.
             */
            psa_sha2_set_return_behavior(sha2Handle, PSA_POLLING_MODE);
        #endif

            /* Compute the hash - this function will close the handle for us. */
            status = ti_psa_hash_compute_sha2_internal(sha2Handle,
                                                       hash_alg,
                                                       input,
                                                       input_length,
                                                       hash,
                                                       hash_size,
                                                       &hash_length);
        }
    #else
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    #endif

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        ecdsaVerifyOp.theirPublicKey = &publicKey;
        ecdsaVerifyOp.hash           = hash;
        ecdsaVerifyOp.hashLength     = hash_length;
        ecdsaVerifyOp.r              = signature;
        ecdsaVerifyOp.s              = signature + (signature_length / 2);

        /* Construct ECDSA handle */
        ECDSA_Config ecdsaConfig;
        ECDSA_Object ecdsaObject;
        ECDSA_Handle ecdsaHandle = psa_ecdsa_construct(&ecdsaConfig, &ecdsaObject);

        if (ecdsaHandle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* Generates the signature */
        ret    = ECDSA_verify(ecdsaHandle, &ecdsaVerifyOp);
        status = map_ECDSA_status(ret, true);

        if (ecdsaObject.returnBehavior == ECDSA_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the ECDSA_Handle can be closed, since
             * this is a one-shot operation.
             */
            ecdsaObject.isOpen = false;
        }
        else
        {
            ECDSA_close(ecdsaHandle);
        }
#endif /* ENABLE_TI_CRYPTO_ECDSA */
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    return status;
}

/*
 *  ======== ti_psa_sign_hash ========
 */
psa_status_t ti_psa_sign_hash(mbedtls_svc_key_id_t key,
                              psa_algorithm_t alg,
                              const uint8_t *hash,
                              size_t hash_length,
                              uint8_t *signature,
                              size_t signature_size,
                              size_t *signature_length)
{
#ifndef ENABLE_TI_CRYPTO_ECDSA
    return PSA_ERROR_NOT_SUPPORTED;
#else
    int_fast16_t ret;
    psa_status_t status             = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    size_t curveBits;
    size_t keyBits;
    CryptoKey privateKey;
    psa_key_type_t privateKeyType;
    size_t outputSize;
    size_t curveBytes;

    *signature_length = 0;

    /* 0 to rep hash */
    status = psa_sign_verify_check_alg(0, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Immediately reject a zero-length signature buffer. This guarantees that
     * signature must be a valid pointer. (On the other hand, the input buffer
     * can in principle be empty since it doesn't actually have to be a hash.)
     */
    if (signature_size == 0)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_SIGN_HASH, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Use key type to map to curve type */
    privateKeyType = psa_get_key_type(&attributes);
    keyBits        = psa_get_key_bits(&attributes);

    /* SL Crypto drivers only support ECC */
    if (!PSA_KEY_TYPE_IS_ECC_KEY_PAIR(privateKeyType))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Only support ECDSA for ti_psa_sign_hash */
    if (!PSA_ALG_IS_ECDSA(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* No support for deterministic ECDSA */
    if (PSA_ALG_IS_DETERMINISTIC_ECDSA(alg))
    {
        /* We return PSA_ERROR_NOT_PERMITTED instead of PSA_ERROR_NOT_SUPPORTED
         * due to mbedTLS's usage of psa_sign_hash in pk_wrap.c. PSA_ERROR_NOT_PERMITTED
         * is the expected error code that instructs the PK wrapper to call with
         * PSA_ALG_ECDSA instead, which we do support.
         */
        return PSA_ERROR_NOT_PERMITTED;
    }

    curveBits  = psa_get_key_bits(&attributes);
    curveBytes = PSA_BITS_TO_BYTES(curveBits);
    outputSize = PSA_SIGN_OUTPUT_SIZE(privateKeyType, curveBits, alg);
    if (signature_size < outputSize)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if ((PSA_ALG_GET_HASH(alg) != PSA_ALG_NONE) && (hash_length != PSA_HASH_LENGTH(PSA_ALG_GET_HASH(alg))))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Per FIPS 186-4 recommendation, the hash length must provide at least as much
     * security strength as the curve length. This is satisfied when the hash length
     * at least matches the curve length, as well as when SHA-512 is used with a 521-bit
     * curve.
     */
    if ((hash_length < curveBytes) && ((hash_length != 64) && (curveBytes != 66)))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ECDSA_OperationSign ecdsaSignOp;

    ECDSA_OperationSign_init(&ecdsaSignOp);

    KeyStore_PSA_initKey(&privateKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);

    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    ecdsaSignOp.curveType = map_keyTypeToECDSACurveTypeHSM(privateKeyType, keyBits);

    if (ecdsaSignOp.curveType == (ECDSA_CurveType)0)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
    #elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
    ecdsaSignOp.curve = map_keyTypeToECCParams(privateKeyType, keyBits);

    if (ecdsaSignOp.curve == NULL)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
    #endif

    ecdsaSignOp.myPrivateKey = &privateKey;
    ecdsaSignOp.hash         = hash;
    ecdsaSignOp.hashLength   = hash_length;
    ecdsaSignOp.r            = signature;
    ecdsaSignOp.s            = signature + curveBytes;

    ECDSA_Config ecdsaConfig;
    ECDSA_Object ecdsaObject;
    ECDSA_Handle ecdsaHandle = psa_ecdsa_construct(&ecdsaConfig, &ecdsaObject);

    if (ecdsaHandle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Generates the signature */
    ret    = ECDSA_sign(ecdsaHandle, &ecdsaSignOp);
    status = map_ECDSA_status(ret, false);

    if (status == PSA_SUCCESS)
    {
        *signature_length = outputSize;
    }

    if (ecdsaObject.returnBehavior == ECDSA_RETURN_BEHAVIOR_CALLBACK)
    {
        /* Set a marker so that the secure callback knows that the ECDSA_Handle can be closed, since
         * this is a one-shot operation.
         */
        ecdsaObject.isOpen = false;
    }
    else
    {
        ECDSA_close(ecdsaHandle);
    }

    return status;
#endif /* ENABLE_TI_CRYPTO_ECDSA */
}

/*
 *  ======== ti_psa_verify_hash ========
 */
psa_status_t ti_psa_verify_hash(mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg,
                                const uint8_t *hash,
                                size_t hash_length,
                                const uint8_t *signature,
                                size_t signature_length)
{
#ifndef ENABLE_TI_CRYPTO_ECDSA
    return PSA_ERROR_NOT_SUPPORTED;
#else
    int_fast16_t ret;
    psa_status_t status             = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    size_t publicKeyBytes;
    size_t expectedOutputSize;
    size_t keyBits;
    size_t curveBytes;
    psa_key_type_t keyType;

    /* 0 to rep hash */
    status = psa_sign_verify_check_alg(0, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_VERIFY_HASH, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Use key type to map to curve type */
    keyType = psa_get_key_type(&attributes);
    keyBits = psa_get_key_bits(&attributes);

    /* Only accept PSA_KEY_TYPE_ECC_KEY_PAIR keys here */
    if (!PSA_KEY_TYPE_ECC_PUBLIC_KEY(keyType))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Only support ECDSA */
    if (!PSA_ALG_IS_ECDSA(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* No support for deterministic ecdsa */
    if (PSA_ALG_IS_DETERMINISTIC_ECDSA(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    expectedOutputSize = PSA_SIGN_OUTPUT_SIZE(keyType, keyBits, alg);

    if (signature_length != expectedOutputSize)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    curveBytes = PSA_BITS_TO_BYTES(psa_get_key_bits(&attributes));

    /* Per FIPS 186-4 recommendation, the hash length must provide at least as much
     * security strength as the curve length. This is satisfied when the hash length
     * at least matches the curve length, as well as when SHA-512 is used with a 521-bit
     * curve.
     */
    if ((hash_length < curveBytes) && ((hash_length != 64) && (curveBytes != 66)))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    publicKeyBytes = PSA_EXPORT_KEY_OUTPUT_SIZE(keyType, keyBits);

    ECDSA_OperationVerify ecdsaVerifyOp;
    CryptoKey publicKey;

    ECDSA_OperationVerify_init(&ecdsaVerifyOp);

    KeyStore_PSA_initKey(&publicKey, key, publicKeyBytes, NULL);

    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    ecdsaVerifyOp.curveType = map_keyTypeToECDSACurveTypeHSM(keyType, keyBits);

    if (ecdsaVerifyOp.curveType == (ECDSA_CurveType)0)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
    #elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
    ecdsaVerifyOp.curve = map_keyTypeToECCParams(keyType, keyBits);

    if (ecdsaVerifyOp.curve == NULL)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
    #endif

    ecdsaVerifyOp.theirPublicKey = &publicKey;
    ecdsaVerifyOp.hash           = hash;
    ecdsaVerifyOp.hashLength     = hash_length;
    ecdsaVerifyOp.r              = signature;
    ecdsaVerifyOp.s              = signature + (signature_length / 2);

    /* Construct ECDSA handle */
    ECDSA_Config ecdsaConfig;
    ECDSA_Object ecdsaObject;
    ECDSA_Handle ecdsaHandle = psa_ecdsa_construct(&ecdsaConfig, &ecdsaObject);

    if (ecdsaHandle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Generates the signature */
    ret    = ECDSA_verify(ecdsaHandle, &ecdsaVerifyOp);
    status = map_ECDSA_status(ret, true);

    if (ecdsaObject.returnBehavior == ECDSA_RETURN_BEHAVIOR_CALLBACK)
    {
        /* Set a marker so that the secure callback knows that the ECDSA_Handle can be closed, since
         * this is a one-shot operation.
         */
        ecdsaObject.isOpen = false;
    }
    else
    {
        ECDSA_close(ecdsaHandle);
    }
    return status;
#endif /* ENABLE_TI_CRYPTO_ECDSA */
}

/*
 *  ======== ti_psa_asymmetric_encrypt ========
 */
psa_status_t ti_psa_asymmetric_encrypt(mbedtls_svc_key_id_t key,
                                       psa_algorithm_t alg,
                                       const uint8_t *input,
                                       size_t input_length,
                                       const uint8_t *salt,
                                       size_t salt_length,
                                       uint8_t *output,
                                       size_t output_size,
                                       size_t *output_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

/*
 *  ======== ti_psa_asymmetric_decrypt ========
 */
psa_status_t ti_psa_asymmetric_decrypt(mbedtls_svc_key_id_t key,
                                       psa_algorithm_t alg,
                                       const uint8_t *input,
                                       size_t input_length,
                                       const uint8_t *salt,
                                       size_t salt_length,
                                       uint8_t *output,
                                       size_t output_size,
                                       size_t *output_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

/******************************************************************************/
/* Symmetric cryptography */
/******************************************************************************/

/*
 *  ======== psa_cipher_error ========
 *  Puts the operation in an error state, resets the key attributes if necessary,
 *  and spits back the error code to return to the application
 */
static psa_status_t psa_cipher_error(ti_psa_cipher_operation_t *operation,
                                     psa_status_t error,
                                     psa_key_attributes_t *attributes)
{
    operation->in_error_state = 1U;

    if (attributes != NULL)
    {
        ti_psa_reset_key_attributes(attributes);
    }

    return error;
}

/*
 *  ======== ti_psa_cipher_encrypt ========
 */
psa_status_t ti_psa_cipher_encrypt(mbedtls_svc_key_id_t key,
                                   psa_algorithm_t alg,
                                   const uint8_t *input,
                                   size_t input_length,
                                   uint8_t *output,
                                   size_t output_size,
                                   size_t *output_length)
{
    int_fast16_t ret;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_type_t symKeyType;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t blockLength;
    size_t keyBits;
    size_t outputSize;
    uint8_t *output_aligned   = output;
    void *output_free_address = NULL;

#if defined(ENABLE_TI_CRYPTO_AESCTR) || defined(ENABLE_TI_CRYPTO_AESCBC)
    size_t ivSize;
    #if defined(PSA_DEBUG)
    uint8_t tempArray[16] = {0};
    uint8_t *iv_array2    = tempArray;
    #else
    uint8_t iv_array[16] = {0};
    #endif
#endif

    *output_length = 0;

    /* The requested algorithm must be one that can be processed by cipher */
    if (!PSA_ALG_IS_CIPHER(alg))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_ENCRYPT, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    symKeyType  = psa_get_key_type(&attributes);
    blockLength = PSA_BLOCK_CIPHER_BLOCK_LENGTH(symKeyType);
    if (input_length < blockLength)
    {
        /* If no padding is required, then input must be at least blockLength */
        if (alg == PSA_ALG_ECB_NO_PADDING || alg == PSA_ALG_CBC_NO_PADDING)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

#if defined(ENABLE_TI_CRYPTO_AESCTR) || defined(ENABLE_TI_CRYPTO_AESCBC)
    /* IV length */
    ivSize = PSA_CIPHER_IV_LENGTH(symKeyType, alg);
#endif

    /* This macro accounts for the IV as well  */
    outputSize = PSA_CIPHER_ENCRYPT_OUTPUT_SIZE(symKeyType, alg, input_length);
    /* Make sure output_size is big enough to take in the IV (if there is one) and ciphertext */
    if (output_size < outputSize)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    keyBits = psa_get_key_bits(&attributes);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(output))
    {
        /* Handle unaligned address case */
        output_aligned = psa_aligned_malloc(outputSize, &output_free_address);
        if (output_aligned == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }
#endif

    if (alg == PSA_ALG_ECB_NO_PADDING)
    {
#ifdef ENABLE_TI_CRYPTO_AESECB
        AESECB_Config aesecbConfig;
        AESECB_Object aesecbObject;

        /* Construct temporary handle for one-shot operation */
        AESECB_Handle aesecbHandle = psa_aesecb_construct(&aesecbConfig, &aesecbObject);

        if (aesecbHandle == NULL)
        {
            if (output_aligned != output)
            {
                free(output_free_address);
            }
            return PSA_ERROR_BAD_STATE;
        }

        AESECB_Operation aesecbOp;
        CryptoKey aesecbCryptoKey;

        AESECB_Operation_init(&aesecbOp);
        KeyStore_PSA_initKey(&aesecbCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
        aesecbOp.key         = &aesecbCryptoKey;
        aesecbOp.input       = (uint8_t *)input;
        aesecbOp.inputLength = input_length;
        aesecbOp.output      = output_aligned;

        ret    = AESECB_oneStepEncrypt(aesecbHandle, &aesecbOp);
        status = map_AES_status(ret);

        if (((AESECB_Object *)aesecbHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the AESECB_Handle can be closed, since
             * this is a one-shot operation.
             */
            ((AESECB_Object *)aesecbHandle->object)->common.isOpen = false;
        }
        else
        {
            AESECB_close(aesecbHandle);
        }
#endif
    }
    else if (alg == PSA_ALG_CTR)
    {
#ifdef ENABLE_TI_CRYPTO_AESCTR
        AESCTR_Config aesctrConfig;
        AESCTR_Object aesctrObject;

        /* Construct temporary handle for one-shot operation */
        AESCTR_Handle aesctrHandle = psa_aesctr_construct(&aesctrConfig, &aesctrObject);
        if (aesctrHandle == NULL)
        {
            if (output_aligned != output)
            {
                free(output_free_address);
            }
            return PSA_ERROR_BAD_STATE;
        }

        AESCTR_Operation aesctrOp;
        CryptoKey aesctrCryptoKey;

        AESCTR_Operation_init(&aesctrOp);
        KeyStore_PSA_initKey(&aesctrCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
        aesctrOp.key         = &aesctrCryptoKey;
        aesctrOp.input       = input;
        aesctrOp.inputLength = input_length;
        /* Per PSA spec, psa_cipher_encrypt IV is followed by ciphertext */
        aesctrOp.output      = output_aligned + ivSize;

    #if defined(PSA_DEBUG)
        status = psa_debug_get_iv(&iv_array2);
        if (status != PSA_SUCCESS)
        {
            status = ti_psa_generate_random(iv_array2, ivSize);
            if (status != PSA_SUCCESS)
            {
                if (output_aligned != output)
                {
                    free(output_free_address);
                }
                return status;
            }
        }
        aesctrOp.initialCounter = iv_array2;
    #else
        status = ti_psa_generate_random(iv_array, ivSize);
        if (status != PSA_SUCCESS)
        {
            if (output_aligned != output)
            {
                free(output_free_address);
            }
            return status;
        }
        aesctrOp.initialCounter = iv_array;
    #endif

        ret    = AESCTR_oneStepEncrypt(aesctrHandle, &aesctrOp);
        status = map_AES_status(ret);

        /* Write the IV to output buffer */
    #if defined(PSA_DEBUG)
        (void)memcpy(output_aligned, iv_array2, ivSize);
    #else
        (void)memcpy(output_aligned, iv_array, ivSize);
    #endif

        if (((AESCTR_Object *)aesctrHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the driver handle can be closed, since
             * this is a one-shot operation.
             */
            ((AESCTR_Object *)aesctrHandle->object)->common.isOpen = false;
        }
        else
        {
            AESCTR_close(aesctrHandle);
        }

#endif /* ENABLE_TI_CRYPTO_AESCTR */
    }
    else if (alg == PSA_ALG_CBC_NO_PADDING)
    {
#ifdef ENABLE_TI_CRYPTO_AESCBC
        AESCBC_Config aescbcConfig;
        AESCBC_Object aescbcObject;
        AESCBC_Operation aescbcOp;
        CryptoKey aescbcCryptoKey;

        AESCBC_Operation_init(&aescbcOp);
        KeyStore_PSA_initKey(&aescbcCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
        aescbcOp.key         = &aescbcCryptoKey;
        aescbcOp.input       = (uint8_t *)input;
        aescbcOp.inputLength = input_length;
        /* Per PSA spec, psa_cipher_encrypt IV is followed by ciphertext */
        aescbcOp.output      = output_aligned + ivSize;

    #if defined(PSA_DEBUG)
        status = psa_debug_get_iv(&iv_array2);
        if (status != PSA_SUCCESS)
        {
            status = ti_psa_generate_random(iv_array2, ivSize);
            if (status != PSA_SUCCESS)
            {
                if (output_aligned != output)
                {
                    free(output_free_address);
                }
                return status;
            }
        }

        aescbcOp.iv = iv_array2;
    #else
        status = ti_psa_generate_random(iv_array, ivSize);
        if (status != PSA_SUCCESS)
        {
            if (output_aligned != output)
            {
                free(output_free_address);
            }
            return status;
        }
        aescbcOp.iv = iv_array;
    #endif

        AESCBC_Handle aescbcHandle = psa_aescbc_construct(&aescbcConfig, &aescbcObject);

        if (aescbcHandle == NULL)
        {
            if (output_aligned != output)
            {
                free(output_free_address);
            }
            return PSA_ERROR_BAD_STATE;
        }

        ret    = AESCBC_oneStepEncrypt(aescbcHandle, &aescbcOp);
        status = map_AES_status(ret);

        /* Write the IV to output buffer */
    #if defined(PSA_DEBUG)
        (void)memcpy(output_aligned, iv_array2, ivSize);
    #else
        (void)memcpy(output_aligned, iv_array, ivSize);
    #endif

        if (((AESCBC_Object *)aescbcHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the driver handle can be closed, since
             * this is a one-shot operation.
             */
            ((AESCBC_Object *)aescbcHandle->object)->common.isOpen = false;
        }
        else
        {
            AESCBC_close(aescbcHandle);
        }

#endif /* ENABLE_TI_CRYPTO_AESCBC */
    }
    else
    {
        (void)ret;
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    if (status == PSA_SUCCESS)
    {
        *output_length = outputSize;
    }

    if (output_aligned != output)
    {
        (void)memcpy(output, output_aligned, outputSize);
        free(output_free_address);
    }

    return status;
}

/*
 *  ======== ti_psa_cipher_decrypt ========
 */
psa_status_t ti_psa_cipher_decrypt(mbedtls_svc_key_id_t key,
                                   psa_algorithm_t alg,
                                   const uint8_t *input,
                                   size_t input_length,
                                   uint8_t *output,
                                   size_t output_size,
                                   size_t *output_length)
{
    int_fast16_t ret;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_type_t symKeyType;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t blockLength;
    size_t ivSize;
    size_t keyBits;
    size_t payloadSize;
    uint8_t *output_aligned   = output;
    void *output_free_address = NULL;

    *output_length = 0;

    /* The requested algorithm must be one that can be processed by cipher */
    if (!PSA_ALG_IS_CIPHER(alg))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_DECRYPT, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    symKeyType  = psa_get_key_type(&attributes);
    ivSize      = PSA_CIPHER_IV_LENGTH(symKeyType, alg);
    payloadSize = PSA_CIPHER_DECRYPT_OUTPUT_SIZE(symKeyType, alg, input_length - ivSize);

    /* This is needed to check that there is an IV the input since if there is
     * none, the payloadSize will be a large unreasonable number due to previous
     * operation.
     */
    if (payloadSize > PSA_CIPHER_DECRYPT_OUTPUT_MAX_SIZE(input_length))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (output_size < payloadSize)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    blockLength = PSA_BLOCK_CIPHER_BLOCK_LENGTH(symKeyType);
    /* If payload size is smaller than the actual block length, then there is a
     * problem if there is no padding.
     */
    if (payloadSize < blockLength)
    {
        /* If no padding is required, then input must be at least blockLength */
        if (alg == PSA_ALG_ECB_NO_PADDING || alg == PSA_ALG_CBC_NO_PADDING)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    keyBits = psa_get_key_bits(&attributes);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(output))
    {
        /* Handle unaligned address case */
        output_aligned = psa_aligned_malloc(payloadSize, &output_free_address);
        if (output_aligned == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }
#endif

    if (alg == PSA_ALG_ECB_NO_PADDING)
    {
#ifdef ENABLE_TI_CRYPTO_AESECB
        AESECB_Config aesecbConfig;
        AESECB_Object aesecbObject;

        /* Construct temporary handle for one-shot operation */
        AESECB_Handle aesecbHandle = psa_aesecb_construct(&aesecbConfig, &aesecbObject);

        if (aesecbHandle == NULL)
        {
            if (output_aligned != output)
            {
                free(output_free_address);
            }
            return PSA_ERROR_BAD_STATE;
        }
        AESECB_Operation aesecbOp;
        CryptoKey aesecbCryptoKey;

        AESECB_Operation_init(&aesecbOp);
        KeyStore_PSA_initKey(&aesecbCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
        aesecbOp.key         = &aesecbCryptoKey;
        aesecbOp.input       = (uint8_t *)(input + ivSize);
        aesecbOp.inputLength = input_length - ivSize;
        aesecbOp.output      = output_aligned;

        ret    = AESECB_oneStepDecrypt(aesecbHandle, &aesecbOp);
        status = map_AES_status(ret);

        if (((AESECB_Object *)aesecbHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the AESECB_Handle can be closed, since
             * this is a one-shot operation.
             */
            ((AESECB_Object *)aesecbHandle->object)->common.isOpen = false;
        }
        else
        {
            AESECB_close(aesecbHandle);
        }
#endif
    }
    else if (alg == PSA_ALG_CTR)
    {
#ifdef ENABLE_TI_CRYPTO_AESCTR
        AESCTR_Config aesctrConfig;
        AESCTR_Object aesctrObject;

        /* Construct temporary handle for one-shot operation */
        AESCTR_Handle aesctrHandle = psa_aesctr_construct(&aesctrConfig, &aesctrObject);
        if (aesctrHandle == NULL)
        {
            if (output_aligned != output)
            {
                free(output_free_address);
            }
            return PSA_ERROR_BAD_STATE;
        }

        AESCTR_Operation aesctrOp;
        CryptoKey aesctrCryptoKey;

        AESCTR_Operation_init(&aesctrOp);
        KeyStore_PSA_initKey(&aesctrCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
        aesctrOp.key            = &aesctrCryptoKey;
        aesctrOp.input          = (uint8_t *)(input + ivSize);
        aesctrOp.inputLength    = input_length - ivSize;
        aesctrOp.output         = output_aligned;
        aesctrOp.initialCounter = input;

        ret    = AESCTR_oneStepDecrypt(aesctrHandle, &aesctrOp);
        status = map_AES_status(ret);

        if (((AESCTR_Object *)aesctrHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the driver handle can be closed, since
             * this is a one-shot operation.
             */
            ((AESCTR_Object *)aesctrHandle->object)->common.isOpen = false;
        }
        else
        {
            AESCTR_close(aesctrHandle);
        }
#endif
    }
    else if (alg == PSA_ALG_CBC_NO_PADDING)
    {
#ifdef ENABLE_TI_CRYPTO_AESCBC
        AESCBC_Config aescbcConfig;
        AESCBC_Object aescbcObject;

        /* Construct temporary handle for one-shot operation */
        AESCBC_Handle aescbcHandle = psa_aescbc_construct(&aescbcConfig, &aescbcObject);

        if (aescbcHandle == NULL)
        {
            if (output_aligned != output)
            {
                free(output_free_address);
            }
            return PSA_ERROR_BAD_STATE;
        }

        AESCBC_Operation aescbcOp;
        CryptoKey aescbcCryptoKey;

        AESCBC_Operation_init(&aescbcOp);
        KeyStore_PSA_initKey(&aescbcCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
        aescbcOp.key         = &aescbcCryptoKey;
        aescbcOp.input       = (uint8_t *)(input + ivSize);
        aescbcOp.inputLength = input_length - ivSize;
        aescbcOp.output      = output_aligned;
        aescbcOp.iv          = (uint8_t *)input;

        ret    = AESCBC_oneStepDecrypt(aescbcHandle, &aescbcOp);
        status = map_AES_status(ret);

        if (((AESCBC_Object *)aescbcHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Set a marker so that the secure callback knows that the AESCBC_Handle can be closed, since
             * this is a one-shot operation.
             */
            ((AESCBC_Object *)aescbcHandle->object)->common.isOpen = false;
        }
        else
        {
            AESCBC_close(aescbcHandle);
        }
#endif
    }
    else
    {
        (void)ret;
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    if (status == PSA_SUCCESS)
    {
        *output_length = payloadSize;
    }

    if (output_aligned != output)
    {
        (void)memcpy(output, output_aligned, payloadSize);
        free(output_free_address);
    }

    return status;
}

/*
 *  ======== ti_psa_cipher_setup ========
 */
static psa_status_t ti_psa_cipher_setup(ti_psa_cipher_operation_t *operation,
                                        mbedtls_svc_key_id_t key,
                                        psa_algorithm_t alg,
                                        aes_operation_t cipher_operation)
{
    int_fast16_t ret;
    psa_status_t status;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_usage_t usage           = (cipher_operation == AES_ENCRYPT ? PSA_KEY_USAGE_ENCRYPT : PSA_KEY_USAGE_DECRYPT);

    /* A context must be freshly initialized before it can be set up */
    if ((operation->id != 0U) || (operation->in_error_state == 1U))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    /* The requested algorithm must be one that can be processed by cipher */
    if (!PSA_ALG_IS_CIPHER(alg))
    {
        return psa_cipher_error(operation, PSA_ERROR_NOT_SUPPORTED, NULL);
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return psa_cipher_error(operation, status, &attributes);
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, usage, alg);
    if (status != PSA_SUCCESS)
    {
        return psa_cipher_error(operation, status, &attributes);
    }

    /* Added to validate the key type since PSA_KEY_TYPE_RAW_DATA is not allowed
     * and anything other than PSA_KEY_TYPE_AES is invalid.
     */
    psa_key_type_t keyType = psa_get_key_type(&attributes);
    if (keyType != PSA_KEY_TYPE_AES)
    {
        return psa_cipher_error(operation, PSA_ERROR_INVALID_ARGUMENT, &attributes);
    }

    /* Initialize the operation struct members, except for id. The id member is
     * used to indicate to ti_psa_cipher_abort that there are resources to free, so
     * we only set it (in the driver wrapper) after resources have been
     * allocated/initialized.
     */
    operation->iv_set = 0U;
    if (alg == PSA_ALG_ECB_NO_PADDING)
    {
        operation->iv_required = 0U;
    }
    else
    {
        operation->iv_required = 1U;
    }

    operation->default_iv_length = PSA_CIPHER_IV_LENGTH(keyType, alg);

    operation->unprocessed_len       = 0;
    operation->curr_unprocessed_data = &operation->unprocessed_data[0];

    size_t keyBits = psa_get_key_bits(&attributes);
    KeyStore_PSA_initKey(&operation->cryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);

    if (cipher_operation == AES_ENCRYPT)
    {
        switch (alg)
        {
#ifdef ENABLE_TI_CRYPTO_AESECB
            case PSA_ALG_ECB_NO_PADDING:
                {
                    AESECB_Handle aesecbHandle;
                    aesecbHandle = psa_aesecb_construct(&operation->driver.aesecb.aesecbConfig,
                                                        &operation->driver.aesecb.aesecbObject);

                    if (aesecbHandle == NULL)
                    {
                        return PSA_ERROR_BAD_STATE;
                    }

                    ret    = AESECB_setupEncrypt(aesecbHandle, &operation->cryptoKey);
                    status = map_AES_status(ret);
                    break;
                }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCBC
            case PSA_ALG_CBC_NO_PADDING:
                {
                    AESCBC_Handle aescbcHandle;
                    aescbcHandle = psa_aescbc_construct(&operation->driver.aescbc.aescbcConfig,
                                                        &operation->driver.aescbc.aescbcObject);

                    if (aescbcHandle == NULL)
                    {
                        return PSA_ERROR_BAD_STATE;
                    }

                    ret    = AESCBC_setupEncrypt(aescbcHandle, &operation->cryptoKey);
                    status = map_AES_status(ret);
                    break;
                }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCTR
            case PSA_ALG_CTR:
                {
                    AESCTR_Handle aesctrHandle;
                    aesctrHandle = psa_aesctr_construct(&operation->driver.aesctr.aesctrConfig,
                                                        &operation->driver.aesctr.aesctrObject);

                    if (aesctrHandle == NULL)
                    {
                        return PSA_ERROR_BAD_STATE;
                    }

                    ret    = AESCTR_setupEncrypt(aesctrHandle, &operation->cryptoKey, NULL);
                    status = map_AES_status(ret);
                    break;
                }
#endif

            default:
                status = PSA_ERROR_NOT_SUPPORTED;
                break;
        }
    }
    else
    {
        switch (alg)
        {
#ifdef ENABLE_TI_CRYPTO_AESECB
            case PSA_ALG_ECB_NO_PADDING:
                {
                    AESECB_Handle aesecbHandle;
                    aesecbHandle = psa_aesecb_construct(&operation->driver.aesecb.aesecbConfig,
                                                        &operation->driver.aesecb.aesecbObject);

                    if (aesecbHandle == NULL)
                    {
                        return PSA_ERROR_BAD_STATE;
                    }

                    ret    = AESECB_setupDecrypt(aesecbHandle, &operation->cryptoKey);
                    status = map_AES_status(ret);
                    break;
                }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCBC
            case PSA_ALG_CBC_NO_PADDING:
                {
                    AESCBC_Handle aescbcHandle;
                    aescbcHandle = psa_aescbc_construct(&operation->driver.aescbc.aescbcConfig,
                                                        &operation->driver.aescbc.aescbcObject);

                    if (aescbcHandle == NULL)
                    {
                        return PSA_ERROR_BAD_STATE;
                    }

                    ret    = AESCBC_setupDecrypt(aescbcHandle, &operation->cryptoKey);
                    status = map_AES_status(ret);
                    break;
                }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCTR
            case PSA_ALG_CTR:
                {
                    AESCTR_Handle aesctrHandle;
                    aesctrHandle = psa_aesctr_construct(&operation->driver.aesctr.aesctrConfig,
                                                        &operation->driver.aesctr.aesctrObject);

                    if (aesctrHandle == NULL)
                    {
                        return PSA_ERROR_BAD_STATE;
                    }

                    ret    = AESCTR_setupDecrypt(aesctrHandle, &operation->cryptoKey, NULL);
                    status = map_AES_status(ret);
                    break;
                }
#endif

            default:
                (void)ret;
                status = PSA_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    if (status != PSA_SUCCESS)
    {
        return psa_cipher_error(operation, status, &attributes);
    }

    operation->alg = alg;
    operation->id  = PSA_CRYPTO_TI_DRIVER_ID;

    return status;
}

/*
 *  ======== ti_psa_cipher_encrypt_setup ========
 */
psa_status_t ti_psa_cipher_encrypt_setup(psa_cipher_operation_t *psa_operation,
                                         mbedtls_svc_key_id_t key,
                                         psa_algorithm_t alg)
{
    ti_psa_cipher_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    operation->is_encrypt                = 1U;
    return ti_psa_cipher_setup(operation, key, alg, AES_ENCRYPT);
}

/*
 *  ======== ti_psa_cipher_decrypt_setup ========
 */
psa_status_t ti_psa_cipher_decrypt_setup(psa_cipher_operation_t *psa_operation,
                                         mbedtls_svc_key_id_t key,
                                         psa_algorithm_t alg)
{
    ti_psa_cipher_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    operation->is_encrypt                = 0U;
    return ti_psa_cipher_setup(operation, key, alg, AES_DECRYPT);
}

/*
 *  ======== ti_psa_cipher_generate_iv ========
 */
psa_status_t ti_psa_cipher_generate_iv(psa_cipher_operation_t *psa_operation,
                                       uint8_t *iv,
                                       size_t iv_size,
                                       size_t *iv_length)
{
    psa_status_t status                  = PSA_ERROR_CORRUPTION_DETECTED;
    ti_psa_cipher_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    uint8_t tempArray[16]                = {0};
    uint8_t *iv_array2                   = tempArray;

    *iv_length = 0;

    if ((operation->id == 0U) || (operation->in_error_state == 1))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if ((operation->iv_set == 1U) || (operation->iv_required == 0U))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if (iv_size < operation->default_iv_length)
    {
        return psa_cipher_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
    }

    status = ti_psa_generate_random(iv_array2, operation->default_iv_length);

    if (status != PSA_SUCCESS)
    {
        return psa_cipher_error(operation, status, NULL);
    }

    status = ti_psa_cipher_set_iv(psa_operation, iv_array2, operation->default_iv_length);
    if (status != PSA_SUCCESS)
    {
        return psa_cipher_error(operation, status, NULL);
    }

    operation->iv_set = 1U;
    (void)memcpy(iv, iv_array2, operation->default_iv_length);
    *iv_length = operation->default_iv_length;

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_cipher_set_iv ========
 */
psa_status_t ti_psa_cipher_set_iv(psa_cipher_operation_t *psa_operation, const uint8_t *iv, size_t iv_length)
{
    int_fast16_t ret;
    psa_status_t status;
    ti_psa_cipher_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if ((operation->id == 0U) || (operation->in_error_state == 1U))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if ((operation->iv_set == 1U) || (operation->iv_required == 0U))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if (iv_length > PSA_CIPHER_IV_MAX_SIZE)
    {
        return psa_cipher_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    if (iv_length < operation->default_iv_length)
    {
        return psa_cipher_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    switch (operation->alg)
    {
#ifdef ENABLE_TI_CRYPTO_AESCBC
        case PSA_ALG_CBC_NO_PADDING:
            ret    = AESCBC_setIV((AESCBC_Handle)&operation->driver.aescbc.aescbcConfig, iv, iv_length);
            status = map_AES_status(ret);
            break;
#endif

#ifdef ENABLE_TI_CRYPTO_AESCTR
        case PSA_ALG_CTR:
    #ifdef TFM_BUILD
            if (psa_crypto_ns_caller)
            {
                psa_aesctr_set_return_behavior((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig, PSA_POLLING_MODE);
            }
    #endif
            ret    = AESCTR_cancelOperation((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig);
            status = map_AES_status(ret);

    #ifdef TFM_BUILD
            if (psa_crypto_ns_caller)
            {
                psa_aesctr_set_return_behavior((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig,
                                               PSA_CALLBACK_MODE);
            }
    #endif

            if (status == PSA_SUCCESS)
            {
                /* AESCTR driver does not have a setIV function, but the initial
                 * counter can be set with setupEncrypt.
                 */
                if (operation->is_encrypt == 1U)
                {
                    ret = AESCTR_setupEncrypt((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig,
                                              &operation->cryptoKey,
                                              iv);
                }
                else
                {
                    ret = AESCTR_setupDecrypt((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig,
                                              &operation->cryptoKey,
                                              iv);
                }

                status = map_AES_status(ret);
            }
            break;
#endif

        default:
            (void)ret;
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    if (status != PSA_SUCCESS)
    {
        return psa_cipher_error(operation, status, NULL);
    }

    operation->iv_set = 1U;
    return status;
}

/*
 * Helper functions for ti_psa_cipher_update.
 */

/*
 *  ======== psa_aesAddBlock ========
 */
static psa_status_t psa_aesAddBlock(ti_psa_cipher_operation_t *operation,
                                    size_t numBlocks,
                                    const uint8_t *input,
                                    uint8_t *output,
                                    bool isFinalOp)
{
    int_fast16_t ret;
    psa_status_t status = PSA_SUCCESS;

    switch (operation->alg)
    {
#ifdef ENABLE_TI_CRYPTO_AESECB
        case PSA_ALG_ECB_NO_PADDING:
            {
    #ifdef TFM_BUILD
                /* Polling mode is required for NS callers on non-final operations, or always for
                 * S callers. This call should be redundant for S callers, since polling mode
                 * was set upon handle construction, which is stored in the psa operation.
                 */
                if ((!isFinalOp && psa_crypto_ns_caller) || (!psa_crypto_ns_caller))
                {
                    psa_aesecb_set_return_behavior((AESECB_Handle)&operation->driver.aesecb.aesecbConfig,
                                                   PSA_POLLING_MODE);
                }
    #endif
                AESECB_Operation aesecbOp;

                AESECB_Operation_init(&aesecbOp);
                aesecbOp.input       = (uint8_t *)input;
                aesecbOp.key         = &operation->cryptoKey;
                aesecbOp.inputLength = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE * numBlocks;
                aesecbOp.output      = output;
                ret                  = AESECB_addData((AESECB_Handle)&operation->driver.aesecb.aesecbConfig, &aesecbOp);
                status               = map_AES_status(ret);

    #ifdef TFM_BUILD
                if (!isFinalOp && psa_crypto_ns_caller)
                {
                    /* Only restore to callback mode for NS callers that changed this temporarily.
                     * S callers want to remain in polling mode (which should be retained from
                     * the handle construction, anyways).
                     */
                    psa_aesecb_set_return_behavior((AESECB_Handle)&operation->driver.aesecb.aesecbConfig,
                                                   PSA_CALLBACK_MODE);
                }
    #endif
                break;
            }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCTR
        case PSA_ALG_CTR:
            {
    #ifdef TFM_BUILD
                /* Polling mode is required for NS callers on non-final operations, or always for
                 * S callers. This call should be redundant for S callers, since polling mode
                 * was set upon handle construction, which is stored in the psa operation.
                 */
                if ((!isFinalOp && psa_crypto_ns_caller) || (!psa_crypto_ns_caller))
                {
                    psa_aesctr_set_return_behavior((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig,
                                                   PSA_POLLING_MODE);
                }
    #endif
                AESCTR_SegmentedOperation aesctrSegmentedOp;

                AESCTR_SegmentedOperation_init(&aesctrSegmentedOp);
                aesctrSegmentedOp.input       = (uint8_t *)input;
                aesctrSegmentedOp.inputLength = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE * numBlocks;
                aesctrSegmentedOp.output      = output;
                ret    = AESCTR_addData((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig, &aesctrSegmentedOp);
                status = map_AES_status(ret);

    #ifdef TFM_BUILD
                if (!isFinalOp && psa_crypto_ns_caller)
                {
                    psa_aesctr_set_return_behavior((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig,
                                                   PSA_CALLBACK_MODE);
                }
    #endif
                break;
            }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCBC
        case PSA_ALG_CBC_NO_PADDING:
            {
    #ifdef TFM_BUILD
                /* Polling mode is required for NS callers on non-final operations, or always for
                 * S callers. This call should be redundant for S callers, since polling mode
                 * was set upon handle construction, which is stored in the psa operation.
                 */
                if ((!isFinalOp && psa_crypto_ns_caller) || (!psa_crypto_ns_caller))
                {
                    psa_aescbc_set_return_behavior((AESCBC_Handle)&operation->driver.aescbc.aescbcConfig,
                                                   PSA_POLLING_MODE);
                }
    #endif
                AESCBC_SegmentedOperation aescbcSegmentedOp;
                AESCBC_SegmentedOperation_init(&aescbcSegmentedOp);
                aescbcSegmentedOp.input       = (uint8_t *)input;
                aescbcSegmentedOp.inputLength = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE * numBlocks;
                aescbcSegmentedOp.output      = output;
                ret    = AESCBC_addData((AESCBC_Handle)&operation->driver.aescbc.aescbcConfig, &aescbcSegmentedOp);
                status = map_AES_status(ret);

    #ifdef TFM_BUILD
                if (!isFinalOp && psa_crypto_ns_caller)
                {
                    /* Only restore to callback mode for NS callers that changed this temporarily.
                     * S callers want to remain in polling mode (which should be retained from
                     * the handle construction, anyways).
                     */
                    psa_aescbc_set_return_behavior((AESCBC_Handle)&operation->driver.aescbc.aescbcConfig,
                                                   PSA_CALLBACK_MODE);
                }
    #endif
                break;
            }
#endif

        default:
            (void)ret;
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    return status;
}

/*
 *  ======== psa_aesAddDataNoPadding ========
 */
static psa_status_t psa_aesAddDataNoPadding(ti_psa_cipher_operation_t *operation,
                                            const uint8_t *input,
                                            size_t input_length,
                                            uint8_t *output,
                                            size_t output_size)
{
    psa_status_t status = PSA_SUCCESS;
    bool isFinalOp      = true;

    /* First check if there is enough input data to process */
    if (input_length + operation->unprocessed_len < PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
    {
        /* Buffer for next time */
        (void)memcpy((operation->curr_unprocessed_data + operation->unprocessed_len), input, input_length);
        operation->unprocessed_len += input_length;
#ifdef TFM_BUILD
        return PSA_OPERATION_COMPLETE;
#else
        return PSA_SUCCESS;
#endif
    }

    /* If there is data to process, then first process buffered data */
    if (operation->unprocessed_len != 0)
    {
        /* Figure out how much more is needed to get to a block size */
        size_t copy_len = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE - operation->unprocessed_len;
        (void)memcpy((operation->curr_unprocessed_data + operation->unprocessed_len), input, copy_len);

        if ((input_length - copy_len) >= PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
        {
            isFinalOp = false;
        }

        status = psa_aesAddBlock(operation, 1, operation->curr_unprocessed_data, output, isFinalOp);

        /* Update outputs */
        output += PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;
        /* Update inputs */
        input += copy_len;
        input_length -= copy_len;
        /* Reset to show buffer is empty */
        operation->unprocessed_len = 0;
    }

    /* Process all the remaining blocks of data */
    if ((status == PSA_SUCCESS) && (input_length >= PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE))
    {
        size_t remainingFullBlocks = (input_length / PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE);
        size_t dataToAdd           = remainingFullBlocks * PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;

        isFinalOp = true;

        status = psa_aesAddBlock(operation, remainingFullBlocks, input, output, isFinalOp);
        /* Update inputs */
        input += dataToAdd;
        input_length -= dataToAdd;
    }

    /* Check if there is any data left to be buffered (data left should always
     * be < PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE).
     */
    if ((status == PSA_SUCCESS) && (input_length != 0))
    {
#ifdef TFM_BUILD
        /* Update the current pointer to unprocessed data to avoid potentially
         * modifying the input buffer before the crypto engine has processed it
         * when the SL driver is operating with callback return behavior.
         */
        if (operation->curr_unprocessed_data == &operation->unprocessed_data[0])
        {
            operation->curr_unprocessed_data = &operation->unprocessed_data[PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE];
        }
        else
        {
            operation->curr_unprocessed_data = &operation->unprocessed_data[0];
        }
#endif

        (void)memcpy(operation->curr_unprocessed_data, input, input_length);
        operation->unprocessed_len = input_length;
    }

    return status;
}

/*
 *  ======== ti_psa_cipher_update ========
 */
psa_status_t ti_psa_cipher_update(psa_cipher_operation_t *psa_operation,
                                  const uint8_t *input,
                                  size_t input_length,
                                  uint8_t *output,
                                  size_t output_size,
                                  size_t *output_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t totalUnprocessedLen;
    ti_psa_cipher_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    uint8_t *output_aligned              = output;
    *output_length                       = 0;
    void *output_free_address            = NULL;

    if ((operation->id == 0U) || (operation->in_error_state == 1U))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if ((operation->iv_required == 1U) && (operation->iv_set == 0U))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if (operation->alg == 0)
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    /* The requested algorithm must be one that can be processed by cipher */
    if (!PSA_ALG_IS_CIPHER(operation->alg))
    {
        return psa_cipher_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    if (input_length == 0)
    {
#ifdef TFM_BUILD
        return PSA_OPERATION_COMPLETE;
#else
        return PSA_SUCCESS;
#endif
    }

    totalUnprocessedLen = operation->unprocessed_len + input_length;

    /* SL CBC, ECB, and CTR drivers only support adding full blocks of data */
    *output_length = (totalUnprocessedLen / PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE) * PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;

    if (output_size < *output_length)
    {
        return psa_cipher_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(output))
    {
        /* Handle unaligned address case */
        output_aligned = psa_aligned_malloc(*output_length, &output_free_address);
        if (output_aligned == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }
#endif

    switch (operation->alg)
    {
        /* Note no padding means if the input is not BLOCK LENGTH, then the
         * input data needs to be buffered and processed when the data buffered
         * size = BLOCK LENGTH.
         */
        case PSA_ALG_ECB_NO_PADDING:
        case PSA_ALG_CTR:
        case PSA_ALG_CBC_NO_PADDING:
            status = psa_aesAddDataNoPadding(operation, input, input_length, output_aligned, output_size);
            break;

        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    if ((status != PSA_SUCCESS)
#ifdef TFM_BUILD
        && (status != PSA_OPERATION_COMPLETE))
#else
    )
#endif
    {
        if (output_aligned != output)
        {
            free(output_free_address);
        }
        return psa_cipher_error(operation, status, NULL);
    }
    else if (output_aligned != output)
    {
        (void)memcpy(output, output_aligned, *output_length);
        free(output_free_address);
    }

    return status;
}

/*
 *  ======== ti_psa_cipher_finish ========
 */
psa_status_t ti_psa_cipher_finish(psa_cipher_operation_t *psa_operation,
                                  uint8_t *output,
                                  size_t output_size,
                                  size_t *output_length)
{
    int_fast16_t ret;
    psa_status_t status                  = PSA_ERROR_GENERIC_ERROR;
    ti_psa_cipher_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    uint8_t *output_aligned              = output;
    void *output_free_address            = NULL;

    if ((operation->id == 0U) || (operation->in_error_state == 1U))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if ((operation->iv_required == 1U) && (operation->iv_set == 0U))
    {
        return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    /* The requested algorithm must be one that can be processed by cipher */
    if (!PSA_ALG_IS_CIPHER(operation->alg))
    {
        return psa_cipher_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    /* True for ciphers supported/tested */
    *output_length = PSA_CIPHER_FINISH_OUTPUT_SIZE(PSA_KEY_TYPE_AES, operation->alg);
    if (output_size < *output_length)
    {
        return psa_cipher_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
    }

    if (operation->unprocessed_len != 0)
    {
        if ((operation->alg == PSA_ALG_ECB_NO_PADDING) || (operation->alg == PSA_ALG_CBC_NO_PADDING))
        {
            return psa_cipher_error(operation, PSA_ERROR_BAD_STATE, NULL);
        }
        else if (output_size < operation->unprocessed_len)
        {
            return psa_cipher_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
        }
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(output))
    {
        /* Handle unaligned address case */
        output_aligned = psa_aligned_malloc(*output_length, &output_free_address);
        if (output_aligned == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }
#endif

    switch (operation->alg)
    {
#ifdef ENABLE_TI_CRYPTO_AESECB
        case PSA_ALG_ECB_NO_PADDING:
            {
                AESECB_Operation aesecbOp;

                AESECB_Operation_init(&aesecbOp);
                aesecbOp.output      = output_aligned;
                aesecbOp.key         = &operation->cryptoKey;
                aesecbOp.inputLength = 0;

                ret    = AESECB_finalize((AESECB_Handle)&operation->driver.aesecb.aesecbConfig, &aesecbOp);
                status = map_AES_status(ret);
    #ifdef TFM_BUILD
                if (psa_crypto_ns_caller)
                {
                    /* Set a marker so that the secure callback knows that the AESECB_Handle can be closed, since
                     * this is a segmented finish operation. Ideally, the psa operation should be aborted,
                     * but at least closing the handle will have to suffice for TFM_enabled for now.
                     */
                    ((AESECB_Object *)&operation->driver.aesecb.aesecbObject)->common.isOpen = false;
                }
                else
    #endif
                {
                    /* Close the handle here, since there is no callback for secure callers nor
                     * S-only configurations. Abort the operation to allow it to be setup again.
                     */
                    ti_psa_cipher_abort(psa_operation);
                }
                break;
            }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCTR
        case PSA_ALG_CTR:
            {
                /* CTR input length does not need to be a multiple of the block
                 * size, so there may be more input data left to process
                 */
                AESCTR_SegmentedOperation aesctrSegmentedOp;

                AESCTR_SegmentedOperation_init(&aesctrSegmentedOp);
                aesctrSegmentedOp.output      = output_aligned;
                aesctrSegmentedOp.input       = operation->curr_unprocessed_data;
                aesctrSegmentedOp.inputLength = operation->unprocessed_len;

                ret    = AESCTR_finalize((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig, &aesctrSegmentedOp);
                status = map_AES_status(ret);
                *output_length = operation->unprocessed_len;
                break;
            }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCBC
        case PSA_ALG_CBC_NO_PADDING:
            {
                AESCBC_SegmentedOperation aescbcSegmentedOp;
                AESCBC_SegmentedOperation_init(&aescbcSegmentedOp);
                aescbcSegmentedOp.inputLength = 0;
                aescbcSegmentedOp.output      = output_aligned;

                ret    = AESCBC_finalize((AESCBC_Handle)&operation->driver.aescbc.aescbcConfig, &aescbcSegmentedOp);
                status = map_AES_status(ret);
    #ifdef TFM_BUILD
                if (psa_crypto_ns_caller)
                {
                    /* Set a marker so that the secure callback knows that the AESCBC_Handle can be closed, since
                     * this is a segmented finish operation. Ideally, the psa operation should be aborted,
                     * but at least closing the handle will have to suffice for TFM_enabled for now.
                     */
                    ((AESCBC_Object *)&operation->driver.aescbc.aescbcObject)->common.isOpen = false;
                }
                else
    #endif
                {
                    /* Close the handle here, since there is no callback for secure callers nor
                     * S-only configurations. Abort the operation to allow it to be setup again.
                     */
                    ti_psa_cipher_abort(psa_operation);
                }
                break;
            }
#endif
        default:
            (void)ret;
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

#if (TFM_ENABLED == 1) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
    /* On tfm_enabled, there is an issue with AESCBC_finalize returning an error code
     * even when the operation completed successfully. In those cases, abort the operation
     * and return psa_success.
     */
    if ((operation->alg == PSA_ALG_CBC_NO_PADDING) && (status == PSA_ERROR_GENERIC_ERROR))
    {
        ti_psa_cipher_abort(operation);
        status = PSA_SUCCESS;
    }
#endif

    if (status != PSA_SUCCESS)
    {
        *output_length = 0;
        if (output_aligned != output)
        {
            free(output_free_address);
        }
        return psa_cipher_error(operation, status, NULL);
    }
    else if (output_aligned != output)
    {
        (void)memcpy(output, output_aligned, *output_length);
        free(output_free_address);
    }

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_cipher_abort ========
 */
psa_status_t ti_psa_cipher_abort(psa_cipher_operation_t *psa_operation)
{
    psa_status_t status                  = PSA_SUCCESS;
    ti_psa_cipher_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if (operation->id == 0U)
    {
        /* The object has (apparently) been initialized but it is not (yet)
         * in use. It's ok to call abort on such an object, and there's
         * nothing to do.
         */
        return PSA_SUCCESS;
    }

    switch (operation->alg)
    {
#ifdef ENABLE_TI_CRYPTO_AESECB
        case PSA_ALG_ECB_NO_PADDING:
            /* Cancel operation is not supported in polling mode for AESECB,
             * workaround is to close the driver instance.
             */
            AESECB_close((AESECB_Handle)&operation->driver.aesecb.aesecbConfig);
            break;
#endif

#ifdef ENABLE_TI_CRYPTO_AESCTR
        case PSA_ALG_CTR:
            {
                int_fast16_t ret;

    #ifdef TFM_BUILD
                if (psa_crypto_ns_caller)
                {
                    psa_aesctr_set_return_behavior((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig,
                                                   PSA_POLLING_MODE);
                }
    #endif
                ret    = AESCTR_cancelOperation((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig);
                status = map_AES_status(ret);

    #ifdef TFM_BUILD
                if (psa_crypto_ns_caller)
                {
                    psa_aesctr_set_return_behavior((AESCTR_Handle)&operation->driver.aesctr.aesctrConfig,
                                                   PSA_CALLBACK_MODE);
                }
    #endif
                break;
            }
#endif

#ifdef ENABLE_TI_CRYPTO_AESCBC
        case PSA_ALG_CBC_NO_PADDING:
            /* Cancel operation is not supported in polling mode for AESCBC,
             * workaround is to close the driver instance.
             */
            AESCBC_close((AESCBC_Handle)&operation->driver.aescbc.aescbcConfig);
            break;
#endif

        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    *operation = TI_PSA_CIPHER_OPERATION_INIT;

    if (status != PSA_SUCCESS)
    {
        return psa_cipher_error(operation, status, NULL);
    }

    return status;
}

/******************************************************************************/
/* Authenticated Encryption with Associated Data (AEAD) */
/******************************************************************************/

/*
 *  ======== ti_psa_aead_error ========
 *  Puts the operation into an error state, resets key attributes if necessary,
 *  and spits back out the error code to be returned to the application.
 */
static psa_status_t ti_psa_aead_error(ti_psa_aead_operation_t *operation,
                                      psa_status_t error,
                                      psa_key_attributes_t *attributes)
{
    operation->in_error_state = 1U;

    if (attributes != NULL)
    {
        ti_psa_reset_key_attributes(attributes);
    }

    return error;
}

/*
 *  ======== ti_psa_aead_set_lengths_internal ========
 */
static psa_status_t ti_psa_aead_set_lengths_internal(ti_psa_aead_operation_t *operation,
                                                     size_t ad_length,
                                                     size_t plaintext_length)
{
    int_fast16_t ret;
    psa_status_t status;

    switch (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg))
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        case PSA_ALG_CCM:
            ret    = AESCCM_setLengths((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig,
                                    ad_length,
                                    plaintext_length,
                                    operation->tagSize);
            status = map_AES_status(ret);
            break;
#endif

#ifdef ENABLE_TI_CRYPTO_AESGCM
        case PSA_ALG_GCM:
            ret = AESGCM_setLengths((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, ad_length, plaintext_length);
            status = map_AES_status(ret);
            break;
#endif

        default:
            (void)ret;
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, NULL);
    }

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_aead_set_lengths ========
 */
psa_status_t ti_psa_aead_set_lengths(psa_aead_operation_t *psa_operation, size_t ad_length, size_t plaintext_length)
{
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if ((operation->id == 0U) || (operation->iv_set == 1U) || (operation->in_error_state == 1U))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    operation->length_set      = true;
    operation->adLength        = ad_length;
    operation->plaintextLength = plaintext_length;

    return ti_psa_aead_set_lengths_internal(operation, ad_length, plaintext_length);
}

/******************************************************************************/
/* Multi-step AEAD operations */
/******************************************************************************/

/*
 *  ======== ti_psa_aead_encrypt_setup ========
 */
psa_status_t ti_psa_aead_encrypt_setup(psa_aead_operation_t *psa_operation,
                                       mbedtls_svc_key_id_t key,
                                       psa_algorithm_t alg)
{
    int_fast16_t ret;
    psa_status_t status;
    psa_key_attributes_t attributes    = PSA_KEY_ATTRIBUTES_INIT;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if ((operation->id != 0) || (operation->in_error_state == 1U))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    /* Check if the algorithm is part of the AEAD (auth encryptions with associated data) */
    if (!(PSA_ALG_IS_AEAD(alg)))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, &attributes);
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_ENCRYPT, alg);
    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, &attributes);
    }

    /* Call the hardware related operations */
    size_t keyBits = psa_get_key_bits(&attributes);
    size_t keyType = psa_get_key_type(&attributes);
    KeyStore_PSA_initKey(&operation->cryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);

    size_t tagLength = PSA_AEAD_TAG_LENGTH(keyType, keyBits, alg);

    /* True for supported AEAD */
    if (PSA_BLOCK_CIPHER_BLOCK_LENGTH(keyType) != PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, &attributes);
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_CCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        /* Check for correct tag size. Test assumes tagLength=0 is invalid */
        status = psa_validate_ccm_tag_length(tagLength);

        if (status == PSA_SUCCESS)
        {
            AESCCM_Handle aesccmHandle;
            aesccmHandle = psa_aesccm_construct(&operation->driver.aesccm.aesccmConfig,
                                                &operation->driver.aesccm.aesccmObject);

            if (aesccmHandle == NULL)
            {
                return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
            }

            ret    = AESCCM_setupEncrypt(aesccmHandle, &operation->cryptoKey, 0, 0, tagLength);
            status = map_AES_status(ret);
        }
#endif
    }
    else if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_GCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESGCM
        /* Check for correct tag size. Test assumes tagLength=0 is invalid */
        status = psa_validate_gcm_tag_length(tagLength);

        if (status == PSA_SUCCESS)
        {
            AESGCM_Handle aesgcmHandle;
            aesgcmHandle = psa_aesgcm_construct(&operation->driver.aesgcm.aesgcmConfig,
                                                &operation->driver.aesgcm.aesgcmObject);
            if (aesgcmHandle == NULL)
            {
                return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
            }

            ret    = AESGCM_setupEncrypt(aesgcmHandle, &operation->cryptoKey, 0, tagLength);
            status = map_AES_status(ret);
        }
#endif
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, &attributes);
    }

    operation->alg                   = alg;
    operation->tagSize               = tagLength;
    operation->id                    = PSA_CRYPTO_TI_DRIVER_ID;
    operation->curr_unprocessed_data = &operation->unprocessedData[0];

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_aead_decrypt_setup ========
 */
psa_status_t ti_psa_aead_decrypt_setup(psa_aead_operation_t *psa_operation,
                                       mbedtls_svc_key_id_t key,
                                       psa_algorithm_t alg)
{
    int_fast16_t ret;
    psa_status_t status;
    psa_key_attributes_t attributes    = PSA_KEY_ATTRIBUTES_INIT;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if ((operation->id != 0) || (operation->in_error_state == 1U))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    /* Check if the algorithm is part of the AEAD (auth encryptions with associated data) */
    if (!(PSA_ALG_IS_AEAD(alg)))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, &attributes);
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_DECRYPT, alg);
    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, &attributes);
    }

    /* Call the hardware related operations */
    size_t keyBits = psa_get_key_bits(&attributes);
    size_t keyType = psa_get_key_type(&attributes);
    KeyStore_PSA_initKey(&operation->cryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);

    size_t tagLength = PSA_AEAD_TAG_LENGTH(keyType, keyBits, alg);

    /* True for supported AEAD */
    if (PSA_BLOCK_CIPHER_BLOCK_LENGTH(keyType) != PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, &attributes);
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_CCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        /* Check for correct tag size. Test assumes tagLength=0 is invalid */
        status = psa_validate_ccm_tag_length(tagLength);

        if (status == PSA_SUCCESS)
        {
            AESCCM_Handle aesccmHandle;
            aesccmHandle = psa_aesccm_construct(&operation->driver.aesccm.aesccmConfig,
                                                &operation->driver.aesccm.aesccmObject);

            if (aesccmHandle == NULL)
            {
                return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
            }

            ret    = AESCCM_setupDecrypt(aesccmHandle, &operation->cryptoKey, 0, 0, tagLength);
            status = map_AES_status(ret);
        }
#endif
    }
    else if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_GCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESGCM
        /* Check for correct tag size. Test assumes tagLength=0 is invalid */
        status = psa_validate_gcm_tag_length(tagLength);

        if (status == PSA_SUCCESS)
        {
            AESGCM_Handle aesgcmHandle;
            aesgcmHandle = psa_aesgcm_construct(&operation->driver.aesgcm.aesgcmConfig,
                                                &operation->driver.aesgcm.aesgcmObject);
            if (aesgcmHandle == NULL)
            {
                return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
            }

            ret    = AESGCM_setupDecrypt(aesgcmHandle, &operation->cryptoKey, 0, 0);
            status = map_AES_status(ret);
        }
#endif
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, &attributes);
    }

    operation->alg                   = alg;
    operation->tagSize               = tagLength;
    operation->id                    = PSA_CRYPTO_TI_DRIVER_ID;
    operation->curr_unprocessed_data = &operation->unprocessedData[0];

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_aead_update_ad_internal ========
 *  Uses the appropriate driver depending on the alg to update the additional
 *  data. Unless it is the final call to this function for the operation,
 *  input_length must be a multiple of the block size.
 */
static psa_status_t ti_psa_aead_update_ad_internal(ti_psa_aead_operation_t *operation,
                                                   psa_algorithm_t alg,
                                                   const uint8_t *input,
                                                   size_t input_length,
                                                   bool isFinalOp)
{
    int_fast16_t ret;
    psa_status_t status;

    if (input_length == 0)
    {
        return PSA_SUCCESS;
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_CCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM

    #ifdef TFM_BUILD
        /* Polling mode is required for NS callers on non-final operations, or always for
         * S callers. This call should be redundant for S callers, since polling mode
         * was set upon handle construction, which is stored in the psa operation.
         */
        if ((!isFinalOp && psa_crypto_ns_caller) || (!psa_crypto_ns_caller))
        {
            psa_aesccm_set_return_behavior((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, PSA_POLLING_MODE);
        }
    #endif
        AESCCM_SegmentedAADOperation aesccmSegmentedAadOp;

        AESCCM_SegmentedAADOperation_init(&aesccmSegmentedAadOp);
        aesccmSegmentedAadOp.aad       = (uint8_t *)input;
        aesccmSegmentedAadOp.aadLength = input_length;

        ret    = AESCCM_addAAD((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, &aesccmSegmentedAadOp);
        status = map_AES_status(ret);

    #ifdef TFM_BUILD
        if (!isFinalOp && psa_crypto_ns_caller)
        {
            /* Only restore to callback mode for NS callers that changed this temporarily.
             * S callers want to remain in polling mode (which should be retained from
             * the handle construction, anyways).
             */
            psa_aesccm_set_return_behavior((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, PSA_CALLBACK_MODE);
        }
    #endif
#endif
    }
    else if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_GCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESGCM

    #ifdef TFM_BUILD
        /* Polling mode is required for NS callers on non-final operations, or always for
         * S callers. This call should be redundant for S callers, since polling mode
         * was set upon handle construction, which is stored in the psa operation.
         */
        if ((!isFinalOp && psa_crypto_ns_caller) || (!psa_crypto_ns_caller))
        {
            psa_aesgcm_set_return_behavior((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, PSA_POLLING_MODE);
        }
    #endif
        AESGCM_SegmentedAADOperation aesgcmSegmentedAadOp;

        AESGCM_SegmentedAADOperation_init(&aesgcmSegmentedAadOp);
        aesgcmSegmentedAadOp.aad       = (uint8_t *)input;
        aesgcmSegmentedAadOp.aadLength = input_length;

        ret    = AESGCM_addAAD((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, &aesgcmSegmentedAadOp);
        status = map_AES_status(ret);

    #ifdef TFM_BUILD
        if (!isFinalOp && psa_crypto_ns_caller)
        {
            /* Only restore to callback mode for NS callers that changed this temporarily.
             * S callers want to remain in polling mode (which should be retained from
             * the handle construction, anyways).
             */
            psa_aesgcm_set_return_behavior((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, PSA_CALLBACK_MODE);
        }
    #endif
#endif
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    return status;
}

/*
 *  ======== ti_psa_aead_update_internal ========
 *  Uses the appropriate driver depending on the alg to pass additional data to
 *  the operation. Unless it is the final call to this function for the
 *  operation, input_length must be a multiple of the block size.
 */
static psa_status_t ti_psa_aead_update_internal(ti_psa_aead_operation_t *operation,
                                                psa_algorithm_t alg,
                                                const uint8_t *input,
                                                size_t input_length,
                                                uint8_t *output,
                                                bool isFinalOp)
{
    int_fast16_t ret;
    psa_status_t status;

    if (input_length == 0)
    {
        return PSA_SUCCESS;
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_CCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM

    #ifdef TFM_BUILD
        /* Polling mode is required for NS callers on non-final operations, or always for
         * S callers. This call should be redundant for S callers, since polling mode
         * was set upon handle construction, which is stored in the psa operation.
         */
        if ((!isFinalOp && psa_crypto_ns_caller) || (!psa_crypto_ns_caller))
        {
            psa_aesccm_set_return_behavior((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, PSA_POLLING_MODE);
        }
    #endif
        AESCCM_SegmentedDataOperation aesccmSegmentedDataOp;
        AESCCM_SegmentedDataOperation_init(&aesccmSegmentedDataOp);

        aesccmSegmentedDataOp.input       = (uint8_t *)input;
        aesccmSegmentedDataOp.output      = output;
        aesccmSegmentedDataOp.inputLength = input_length;

        ret    = AESCCM_addData((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, &aesccmSegmentedDataOp);
        status = map_AES_status(ret);

    #ifdef TFM_BUILD
        if (!isFinalOp && psa_crypto_ns_caller)
        {
            /* Only restore to callback mode for NS callers that changed this temporarily.
             * S callers want to remain in polling mode (which should be retained from
             * the handle construction, anyways).
             */
            psa_aesccm_set_return_behavior((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, PSA_CALLBACK_MODE);
        }
    #endif
#endif
    }
    else if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg) == PSA_ALG_GCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESGCM

    #ifdef TFM_BUILD
        /* Polling mode is required for NS callers on non-final operations, or always for
         * S callers. This call should be redundant for S callers, since polling mode
         * was set upon handle construction, which is stored in the psa operation.
         */
        if ((!isFinalOp && psa_crypto_ns_caller) || (!psa_crypto_ns_caller))
        {
            psa_aesgcm_set_return_behavior((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, PSA_POLLING_MODE);
        }
    #endif
        AESGCM_SegmentedDataOperation aesgcmSegmentedDataOp;

        AESGCM_SegmentedDataOperation_init(&aesgcmSegmentedDataOp);
        aesgcmSegmentedDataOp.input       = (uint8_t *)input;
        aesgcmSegmentedDataOp.output      = output;
        aesgcmSegmentedDataOp.inputLength = input_length;

        ret    = AESGCM_addData((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, &aesgcmSegmentedDataOp);
        status = map_AES_status(ret);

    #ifdef TFM_BUILD
        if (!isFinalOp && psa_crypto_ns_caller)
        {
            /* Only restore to callback mode for NS callers that changed this temporarily.
             * S callers want to remain in polling mode (which should be retained from
             * the handle construction, anyways).
             */
            psa_aesgcm_set_return_behavior((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, PSA_CALLBACK_MODE);
        }
    #endif
#endif
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    return status;
}

/*
 *  ======== ti_psa_aead_update ========
 */
psa_status_t ti_psa_aead_update(psa_aead_operation_t *psa_operation,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *output,
                                size_t output_size,
                                size_t *output_length)
{
    bool isFinalOp      = false;
    psa_status_t status = PSA_SUCCESS;
    size_t totalUnprocessedLen;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    uint8_t *output_aligned            = output;
    /* Preserve temp buffer start address before output_aligned advances in loop */
    uint8_t *output_aligned_start      = output;
    void *output_free_address          = NULL;

    *output_length = 0;

    /* Per PSA spec, calling ti_psa_aead_set_lengths() is optional for GCM.
     * However, our SL GCM driver requires the lengths to be set prior to
     * processing any data so an error must be returned.
     */
    if (!operation->length_set)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if ((operation->id == 0U) || (operation->in_error_state == 1U) || (operation->iv_set == 0U))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    operation->runningPlaintextLength += input_length;

    if (operation->length_set && ((operation->runningADLength < operation->adLength) ||
                                  (operation->runningPlaintextLength > operation->plaintextLength)))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    if (!operation->done_updating_ad)
    {
        /* Add any remaining additional data */
        status = ti_psa_aead_update_ad_internal(operation,
                                                operation->alg,
                                                operation->curr_unprocessed_data,
                                                operation->unprocessed_len,
                                                isFinalOp);
        if (status != PSA_SUCCESS)
        {
            return ti_psa_aead_error(operation, status, NULL);
        }

        operation->done_updating_ad = true;
        operation->unprocessed_len  = 0;
    }

    totalUnprocessedLen = operation->unprocessed_len + input_length;

    /* SL CCM and GCM drivers only support adding full blocks of data */
    *output_length = (totalUnprocessedLen / PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE) * PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;

    if (output_size < *output_length)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
    }

    /* Not enough total data to make up one block */
    if (totalUnprocessedLen < PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
    {
        /* Buffer the data */
        (void)memcpy(operation->curr_unprocessed_data + operation->unprocessed_len, input, input_length);
        operation->unprocessed_len = totalUnprocessedLen;

#ifdef TFM_BUILD
        return PSA_OPERATION_COMPLETE;
#else
        return PSA_SUCCESS;
#endif
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(output))
    {
        /* Handle unaligned address case - the tag is provided in the output token,
         * so no need to align the provided output tag address.
         */
        output_aligned = psa_aligned_malloc(*output_length, &output_free_address);
        if (output_aligned == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
        output_aligned_start = output_aligned;
    }
#endif

    if (operation->unprocessed_len > 0)
    {
        /* Enough data to make up at least a single block. Append enough input data
         * to the existing unprocessed data to build a full block.
         */
        size_t amountToCopy = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE - operation->unprocessed_len;
        (void)memcpy(operation->curr_unprocessed_data + operation->unprocessed_len, input, amountToCopy);
        input += amountToCopy;

        /* If there will be less than a full block remaining, then this is final
         * operation to be issued to the SL driver for this call to ti_psa_aead_update().
         */
        if ((totalUnprocessedLen - PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE) < PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
        {
            isFinalOp = true;
        }

        status = ti_psa_aead_update_internal(operation,
                                             operation->alg,
                                             operation->curr_unprocessed_data,
                                             PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE,
                                             output_aligned,
                                             isFinalOp);

        if (status != PSA_SUCCESS)
        {
            /* Check if psa_aligned_malloc allocated a temp buffer. */
            if (output_aligned_start != output)
            {
                /* Free the temp buffer. */
                free(output_free_address);
            }
            return ti_psa_aead_error(operation, status, NULL);
        }

        output_aligned += PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;
        totalUnprocessedLen -= PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;
        operation->unprocessed_len = 0;

#ifdef TFM_BUILD
        /* Update the current pointer to unprocessed data to avoid potentially
         * modifying the input buffer before the crypto engine has processed it
         * when the SL driver is operating with callback return behavior.
         */
        if (operation->curr_unprocessed_data == &operation->unprocessedData[0])
        {
            operation->curr_unprocessed_data = &operation->unprocessedData[PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE];
        }
        else
        {
            operation->curr_unprocessed_data = &operation->unprocessedData[0];
        }
#endif
    }

    /* Get the largest block size multiple of the remaining data to process */
    size_t amountToAdd = (totalUnprocessedLen / PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE) * PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;

    if (amountToAdd > 0)
    {
        isFinalOp = true;

        status = ti_psa_aead_update_internal(operation, operation->alg, input, amountToAdd, output_aligned, isFinalOp);
        if (status != PSA_SUCCESS)
        {
            /* Check if psa_aligned_malloc allocated a temp buffer. */
            if (output_aligned_start != output)
            {
                /* Free the temp buffer. */
                free(output_free_address);
            }
            return ti_psa_aead_error(operation, status, NULL);
        }

        totalUnprocessedLen -= amountToAdd;
        input += amountToAdd;
        output_aligned += amountToAdd;
    }

    /* Add any left over data to the unprocessed data buffer */
    if (totalUnprocessedLen > 0)
    {
        (void)memcpy(operation->curr_unprocessed_data, input, totalUnprocessedLen);
        operation->unprocessed_len = totalUnprocessedLen;
    }

    /* Check if psa_aligned_malloc allocated a temp buffer. */
    if (output_aligned_start != output)
    {
        /* Copy back to unaligned output buffer and free temp buffer */
        (void)memcpy(output, output_aligned_start, *output_length);
        free(output_free_address);
    }

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_aead_update_ad ========
 */
psa_status_t ti_psa_aead_update_ad(psa_aead_operation_t *psa_operation, const uint8_t *input, size_t input_length)
{
    bool isFinalOp                     = false;
    psa_status_t status                = PSA_SUCCESS;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    size_t totalUnprocessedLen         = operation->unprocessed_len + input_length;

    /* Per PSA spec, calling ti_psa_aead_set_lengths() is optional for GCM.
     * However, our SL GCM driver requires the lengths to be set prior to
     * processing any data so an error must be returned.
     */
    if (!operation->length_set)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if ((operation->id == 0U) || (operation->in_error_state == 1U) || (operation->iv_set == 0U) ||
        operation->done_updating_ad)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    operation->runningADLength += input_length;

    if (operation->length_set && (operation->runningADLength > operation->adLength))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    /* Not enough total data to make up one block */
    if (totalUnprocessedLen < PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
    {
        /* Buffer the data and wait for more data to arrive */
        (void)memcpy(operation->curr_unprocessed_data + operation->unprocessed_len, input, input_length);
        operation->unprocessed_len = totalUnprocessedLen;
#ifdef TFM_BUILD
        return PSA_OPERATION_COMPLETE;
#else
        return PSA_SUCCESS;
#endif
    }

    if (operation->unprocessed_len > 0)
    {
        /* Create a full block of unprocessed data to add */
        size_t amountToCopy = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE - operation->unprocessed_len;
        (void)memcpy(operation->curr_unprocessed_data + operation->unprocessed_len, input, amountToCopy);
        input += amountToCopy;

        if ((totalUnprocessedLen - PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE) == 0)
        {
            isFinalOp = true;
        }

        status = ti_psa_aead_update_ad_internal(operation,
                                                operation->alg,
                                                operation->curr_unprocessed_data,
                                                PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE,
                                                isFinalOp);
        if (status != PSA_SUCCESS)
        {
            return ti_psa_aead_error(operation, status, NULL);
        }

        totalUnprocessedLen -= PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;
        operation->unprocessed_len = 0;

#ifdef TFM_BUILD
        /* Update the current pointer to unprocessed data to avoid potentially
         * modifying the input buffer before the crypto engine has processed it
         * when the SL driver is operating with callback return behavior.
         */
        if (operation->curr_unprocessed_data == &operation->unprocessedData[0])
        {
            operation->curr_unprocessed_data = &operation->unprocessedData[PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE];
        }
        else
        {
            operation->curr_unprocessed_data = &operation->unprocessedData[0];
        }
#endif
    }

    /* Get the largest multiple of the block size that is less than the number
     * of bytes of unprocessed data.
     */
    size_t amountToAdd = ((int)(totalUnprocessedLen / PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)) *
                         PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;

    if (amountToAdd > 0)
    {
        isFinalOp = true;

        status = ti_psa_aead_update_ad_internal(operation, operation->alg, input, amountToAdd, isFinalOp);
        if (status != PSA_SUCCESS)
        {
            return ti_psa_aead_error(operation, status, NULL);
        }
        totalUnprocessedLen -= amountToAdd;
        input += amountToAdd;
    }

    /* Add any left over data to the unprocessed data buffer */
    if (totalUnprocessedLen > 0)
    {
        (void)memcpy(operation->curr_unprocessed_data, input, totalUnprocessedLen);
        operation->unprocessed_len = totalUnprocessedLen;
    }

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_aead_set_nonce ========
 */
psa_status_t ti_psa_aead_set_nonce(psa_aead_operation_t *psa_operation, const uint8_t *nonce, size_t nonce_length)
{
    int_fast16_t ret;
    psa_status_t status;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if ((operation->id == 0U) || (operation->iv_set == 1U) || (operation->in_error_state == 1U))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg) == PSA_ALG_CCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        /* CCM requires that the length be set before setting the nonce */
        if (!operation->length_set)
        {
            status = PSA_ERROR_BAD_STATE;
        }
        else
        {
            /* Verify proper nonce length */
            if ((nonce_length < 7) || (nonce_length > 13))
            {
                status = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                ret    = AESCCM_setNonce((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, nonce, nonce_length);
                status = map_AES_status(ret);
            }
        }
#endif
    }
    else if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg) == PSA_ALG_GCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESGCM
        /* Verify proper nonce length */
        if ((nonce_length == 0U) || (nonce_length > PSA_AEAD_NONCE_MAX_SIZE))
        {
            status = PSA_ERROR_INVALID_ARGUMENT;
        }
        else
        {
            /* Currently the AESGCM driver only supports nonce lengths of 12 */
            ret    = AESGCM_setIV((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, nonce, nonce_length);
            status = map_AES_status(ret);
        }
#endif
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, NULL);
    }

    operation->iv_set = 1U;

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_aead_generate_nonce ========
 */
psa_status_t ti_psa_aead_generate_nonce(psa_aead_operation_t *psa_operation,
                                        uint8_t *nonce,
                                        size_t nonce_size,
                                        size_t *nonce_length)
{
    psa_status_t status;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    uint8_t buffer[16]; /* word multiple buffer as required by HSM */
#endif

    if ((operation->id == 0U) || (operation->iv_set == 1U) || (operation->in_error_state == 1U))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if ((PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg) == PSA_ALG_CCM) && !operation->length_set)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    /* For CCM, this size may not be correct according to the PSA
     * specification. The PSA Crypto 1.0.1 specification states:
     *
     * CCM encodes the plaintext length pLen in L octets, with L the smallest
     * integer >= 2 where pLen < 2^(8L). The nonce length is then 15 - L bytes.
     *
     * However this restriction that L has to be the smallest integer is not
     * applied in practice, and it is not implementable here since the
     * plaintext length may or may not be known at this time.
     */
    *nonce_length = PSA_AEAD_NONCE_LENGTH(PSA_KEY_TYPE_AES, operation->alg);

    if (*nonce_length > nonce_size)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
    }

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    status = ti_psa_generate_random(buffer, sizeof(buffer));
#else
    status = ti_psa_generate_random(nonce, *nonce_length);
#endif

    if (status != PSA_SUCCESS)
    {
        return ti_psa_aead_error(operation, status, NULL);
    }

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    (void)memcpy(nonce, buffer, *nonce_length);
#endif

    return ti_psa_aead_set_nonce(psa_operation, nonce, *nonce_length);
}

/*
 *  ======== ti_psa_aead_finish ========
 */
psa_status_t ti_psa_aead_finish(psa_aead_operation_t *psa_operation,
                                uint8_t *ciphertext,
                                size_t ciphertext_size,
                                size_t *ciphertext_length,
                                uint8_t *tag,
                                size_t tag_size,
                                size_t *tag_length)
{
    int_fast16_t ret;
    psa_status_t status                = PSA_SUCCESS;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    uint8_t *output                    = ciphertext;
    void *output_free_address          = NULL;

    *ciphertext_length = 0;

    if ((operation->id == 0U) || (operation->iv_set == 0U) || (operation->in_error_state == 1U))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if (ciphertext_size < operation->unprocessed_len)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
    }

    if (tag_size < operation->tagSize)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
    }

    if (operation->length_set && ((operation->runningADLength < operation->adLength) ||
                                  (operation->runningPlaintextLength < operation->plaintextLength)))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    /* To handle the case when update is never called because there is zero
     * plaintext, but there is still additional data that has not been
     * processed.
     */
    if (!operation->done_updating_ad)
    {
        status = ti_psa_aead_update_ad_internal(operation,
                                                operation->alg,
                                                operation->curr_unprocessed_data,
                                                operation->unprocessed_len,
                                                false);
        if (status != PSA_SUCCESS)
        {
            return ti_psa_aead_error(operation, status, NULL);
        }

        operation->done_updating_ad = true;
        operation->unprocessed_len  = 0;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(ciphertext))
    {
        /* Handle unaligned address case - the tag is provided in the output token,
         * so no need to align the provided output tag address.
         */
        output = psa_aligned_malloc(operation->plaintextLength, &output_free_address);
        if (output == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }
#endif

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg) == PSA_ALG_CCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        AESCCM_SegmentedFinalizeOperation aesccmSegmentedFinalizeOp;
        AESCCM_SegmentedFinalizeOperation_init(&aesccmSegmentedFinalizeOp);
        aesccmSegmentedFinalizeOp.input       = operation->curr_unprocessed_data;
        aesccmSegmentedFinalizeOp.output      = output;
        aesccmSegmentedFinalizeOp.inputLength = operation->unprocessed_len;
        aesccmSegmentedFinalizeOp.mac         = tag;
        aesccmSegmentedFinalizeOp.macLength   = operation->tagSize;

        ret = AESCCM_finalizeEncrypt((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, &aesccmSegmentedFinalizeOp);
        *tag_length                = aesccmSegmentedFinalizeOp.macLength;
        *ciphertext_length         = aesccmSegmentedFinalizeOp.inputLength;
        operation->unprocessed_len = 0;

        status = map_AES_status(ret);
#endif
    }
    else if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg) == PSA_ALG_GCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESGCM
        AESGCM_SegmentedFinalizeOperation aesgcmSegmentedFinalizeOp;
        AESGCM_SegmentedFinalizeOperation_init(&aesgcmSegmentedFinalizeOp);
        aesgcmSegmentedFinalizeOp.input       = operation->curr_unprocessed_data;
        aesgcmSegmentedFinalizeOp.output      = output;
        aesgcmSegmentedFinalizeOp.inputLength = operation->unprocessed_len;
        aesgcmSegmentedFinalizeOp.mac         = tag;
        aesgcmSegmentedFinalizeOp.macLength   = operation->tagSize;

        ret = AESGCM_finalizeEncrypt((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, &aesgcmSegmentedFinalizeOp);
        *tag_length                = aesgcmSegmentedFinalizeOp.macLength;
        *ciphertext_length         = aesgcmSegmentedFinalizeOp.inputLength;
        operation->unprocessed_len = 0;

        status = map_AES_status(ret);
#endif
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    if (status != PSA_SUCCESS)
    {
        if (output != ciphertext)
        {
            free(output_free_address);
        }
        return ti_psa_aead_error(operation, status, NULL);
    }
    else if (output != ciphertext)
    {
        /* Handle unaligned address case - copy the aligned output back to the
         * original unaligned buffer and free the temporary buffer.
         */
        (void)memcpy(ciphertext, output, *ciphertext_length);
        free(output_free_address);
    }

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_aead_verify ========
 */
psa_status_t ti_psa_aead_verify(psa_aead_operation_t *psa_operation,
                                uint8_t *plaintext,
                                size_t plaintext_size,
                                size_t *plaintext_length,
                                const uint8_t *tag,
                                size_t tag_length)

{
    int_fast16_t ret;
    psa_status_t status                = PSA_SUCCESS;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;
    uint8_t *output                    = plaintext;
    *plaintext_length                  = 0;
    void *output_free_address          = NULL;

    if ((operation->id == 0U) || (operation->iv_set == 0U) || (operation->in_error_state == 1U))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BAD_STATE, NULL);
    }

    if (plaintext_size < operation->unprocessed_len)
    {
        return ti_psa_aead_error(operation, PSA_ERROR_BUFFER_TOO_SMALL, NULL);
    }

    if (operation->length_set && ((operation->runningADLength < operation->adLength) ||
                                  (operation->runningPlaintextLength < operation->plaintextLength)))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    if ((PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg) == PSA_ALG_CCM) && (operation->tagSize != tag_length))
    {
        return ti_psa_aead_error(operation, PSA_ERROR_INVALID_ARGUMENT, NULL);
    }

    /* To handle the case when update is never called because there is zero
     * ciphertext, but there is still additional data that has not been
     * processed.
     */
    if (!operation->done_updating_ad)
    {
        status = ti_psa_aead_update_ad_internal(operation,
                                                operation->alg,
                                                operation->curr_unprocessed_data,
                                                operation->unprocessed_len,
                                                false);
        if (status != PSA_SUCCESS)
        {
            return ti_psa_aead_error(operation, status, NULL);
        }

        operation->done_updating_ad = true;
        operation->unprocessed_len  = 0;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(plaintext))
    {
        /* Handle unaligned address case */
        output = psa_aligned_malloc(operation->plaintextLength, &output_free_address);
        if (output == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }
#endif

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg) == PSA_ALG_CCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        AESCCM_SegmentedFinalizeOperation aesccmSegmentedFinalizeOp;
        AESCCM_SegmentedFinalizeOperation_init(&aesccmSegmentedFinalizeOp);
        aesccmSegmentedFinalizeOp.input       = operation->curr_unprocessed_data;
        aesccmSegmentedFinalizeOp.output      = output;
        aesccmSegmentedFinalizeOp.inputLength = operation->unprocessed_len;
        aesccmSegmentedFinalizeOp.mac         = (uint8_t *)tag;
        aesccmSegmentedFinalizeOp.macLength   = operation->tagSize;

        ret = AESCCM_finalizeDecrypt((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig, &aesccmSegmentedFinalizeOp);
        *plaintext_length = aesccmSegmentedFinalizeOp.inputLength;

        status = map_AES_status(ret);
#endif
    }
    else if (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg) == PSA_ALG_GCM)
    {
#ifdef ENABLE_TI_CRYPTO_AESGCM
        AESGCM_SegmentedFinalizeOperation aesgcmSegmentedFinalizeOp;
        AESGCM_SegmentedFinalizeOperation_init(&aesgcmSegmentedFinalizeOp);
        aesgcmSegmentedFinalizeOp.input       = operation->curr_unprocessed_data;
        aesgcmSegmentedFinalizeOp.output      = output;
        aesgcmSegmentedFinalizeOp.inputLength = operation->unprocessed_len;
        aesgcmSegmentedFinalizeOp.mac         = (uint8_t *)tag;
        aesgcmSegmentedFinalizeOp.macLength   = tag_length;

        ret = AESGCM_finalizeDecrypt((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig, &aesgcmSegmentedFinalizeOp);
        *plaintext_length = aesgcmSegmentedFinalizeOp.inputLength;

        status = map_AES_status(ret);
#endif
    }
    else
    {
        (void)ret;
        /* Do nothing */
    }

    if (status != PSA_SUCCESS)
    {
        if (output != plaintext)
        {
            free(output_free_address);
        }
        return ti_psa_aead_error(operation, status, NULL);
    }
    else if (output != plaintext)
    {
        /* Handle unaligned address case - copy the aligned output back to the
         * original unaligned buffer and free the temporary buffer.
         */
        (void)memcpy(plaintext, output, *plaintext_length);
        free(output_free_address);
    }

    return PSA_SUCCESS;
}

/*
 *  ======== ti_psa_aead_abort ========
 */
psa_status_t ti_psa_aead_abort(psa_aead_operation_t *psa_operation)
{
    psa_status_t status                = PSA_SUCCESS;
    ti_psa_aead_operation_t *operation = &psa_operation->MBEDTLS_PRIVATE(ctx).ti_ctx;

    if (operation->id == 0U)
    {
        /* The object has (apparently) been initialized but it is not (yet) in
         * use. It's ok to call abort on such an object, and there's nothing to
         * do.
         */
        return PSA_SUCCESS;
    }

    switch (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(operation->alg))
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        case PSA_ALG_CCM:
            /* Close driver since cancellation is not supported for polling mode */
            AESCCM_close((AESCCM_Handle)&operation->driver.aesccm.aesccmConfig);
            break;
#endif

#ifdef ENABLE_TI_CRYPTO_AESGCM
        case PSA_ALG_GCM:
            /* Close driver since cancellation is not supported for polling mode */
            AESGCM_close((AESGCM_Handle)&operation->driver.aesgcm.aesgcmConfig);
            break;
#endif

        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    *operation = TI_PSA_AEAD_OPERATION_INIT;

    return status;
}

/******************************************************************************/
/* One-step AEAD operations */
/******************************************************************************/

/*
 *  ======== ti_psa_aead_encrypt ========
 */
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
                                 size_t *ciphertext_length)
{
    int_fast16_t ret;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_type_t keyType;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t keyBits;
    size_t tagLength;
    uint8_t *output           = ciphertext;
    void *output_free_address = NULL;
    uint8_t *tag;

    *ciphertext_length = 0;

    if (!PSA_ALG_IS_AEAD(alg) || PSA_ALG_IS_WILDCARD(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_ENCRYPT, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    keyType   = psa_get_key_type(&attributes);
    keyBits   = psa_get_key_bits(&attributes);
    tagLength = PSA_AEAD_TAG_LENGTH(keyType, keyBits, alg);
    if (tagLength > PSA_AEAD_TAG_MAX_SIZE)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (ciphertext_size < (plaintext_length + tagLength))
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* True for supported AEAD */
    if (PSA_BLOCK_CIPHER_BLOCK_LENGTH(keyType) != PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(ciphertext))
    {
        /* Handle unaligned address case */
        output = psa_aligned_malloc(plaintext_length + tagLength, &output_free_address);
        if (output == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }
#endif

    tag = output + plaintext_length;

    if (((tag == NULL) && (tagLength != 0)) || ((additional_data == NULL) && (additional_data_length != 0)) ||
        ((plaintext == NULL) && (plaintext_length != 0)) || ((output == NULL) && (ciphertext_size != 0)) ||
        (nonce == NULL))
    {
        if (output != ciphertext)
        {
            free(output_free_address);
        }
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    switch (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg))
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        case PSA_ALG_CCM:
            {
                /* Check for correct tag size. Test assumes tagLength=0 is invalid */
                status = psa_validate_ccm_tag_length(tagLength);
                if (status != PSA_SUCCESS)
                {
                    if (output != ciphertext)
                    {
                        free(output_free_address);
                    }
                    return status;
                }
                AESCCM_Config aesccmConfig;
                AESCCM_Object aesccmObject;

                AESCCM_Handle aesccmHandle = psa_aesccm_construct(&aesccmConfig, &aesccmObject);

                if (aesccmHandle == NULL)
                {
                    if (output != ciphertext)
                    {
                        free(output_free_address);
                    }
                    return PSA_ERROR_BAD_STATE;
                }

                AESCCM_OneStepOperation aesccmOneStepOp;
                CryptoKey aesccmCryptoKey;
                AESCCM_OneStepOperation_init(&aesccmOneStepOp);
                KeyStore_PSA_initKey(&aesccmCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
                aesccmOneStepOp.key         = &aesccmCryptoKey;
                aesccmOneStepOp.aad         = (uint8_t *)additional_data;
                aesccmOneStepOp.aadLength   = additional_data_length;
                aesccmOneStepOp.input       = (uint8_t *)plaintext;
                aesccmOneStepOp.output      = output;
                aesccmOneStepOp.inputLength = plaintext_length;
                aesccmOneStepOp.nonce       = (uint8_t *)nonce;
                aesccmOneStepOp.nonceLength = nonce_length;
                aesccmOneStepOp.mac         = tag;
                aesccmOneStepOp.macLength   = tagLength;

                ret    = AESCCM_oneStepEncrypt(aesccmHandle, &aesccmOneStepOp);
                status = map_AES_status(ret);

                if (((AESCCM_Object *)aesccmHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
                {
                    /* Set a marker so that the secure callback knows that the driver handle can be closed, since
                     * this is a one-shot operation.
                     */
                    ((AESCCM_Object *)aesccmHandle->object)->common.isOpen = false;
                }
                else
                {
                    AESCCM_close(aesccmHandle);
                }
                break;
            }
#endif

#ifdef ENABLE_TI_CRYPTO_AESGCM
        case PSA_ALG_GCM:
            {
                /* Check for correct tag size. Test assumes tagLength=0 is invalid */
                status = psa_validate_gcm_tag_length(tagLength);
                if (status != PSA_SUCCESS)
                {
                    if (output != ciphertext)
                    {
                        free(output_free_address);
                    }
                    return status;
                }
                AESGCM_Config aesgcmConfig;
                AESGCM_Object aesgcmObject;

                AESGCM_Handle aesgcmHandle = psa_aesgcm_construct(&aesgcmConfig, &aesgcmObject);

                if (aesgcmHandle == NULL)
                {
                    if (output != ciphertext)
                    {
                        free(output_free_address);
                    }
                    return PSA_ERROR_BAD_STATE;
                }

                AESGCM_OneStepOperation aesgcmOneStepOp;
                CryptoKey aesgcmCryptoKey;
                AESGCM_OneStepOperation_init(&aesgcmOneStepOp);
                KeyStore_PSA_initKey(&aesgcmCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
                aesgcmOneStepOp.key                   = &aesgcmCryptoKey;
                aesgcmOneStepOp.aad                   = (uint8_t *)additional_data;
                aesgcmOneStepOp.aadLength             = additional_data_length;
                aesgcmOneStepOp.input                 = (uint8_t *)plaintext;
                aesgcmOneStepOp.output                = output;
                aesgcmOneStepOp.inputLength           = plaintext_length;
                aesgcmOneStepOp.iv                    = (uint8_t *)nonce;
                aesgcmOneStepOp.ivLength              = nonce_length;
                aesgcmOneStepOp.ivInternallyGenerated = 0;
                aesgcmOneStepOp.mac                   = tag;
                aesgcmOneStepOp.macLength             = tagLength;

                ret    = AESGCM_oneStepEncrypt(aesgcmHandle, &aesgcmOneStepOp);
                status = map_AES_status(ret);

                if (((AESGCM_Object *)aesgcmHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
                {
                    /* Set a marker so that the secure callback knows that the driver handle can be closed, since
                     * this is a one-shot operation.
                     */
                    ((AESGCM_Object *)aesgcmHandle->object)->common.isOpen = false;
                }
                else
                {
                    AESGCM_close(aesgcmHandle);
                }
                break;
            }
#endif

        default:
            (void)ret;
            /* Do nothing */
            break;
    }

    if (status == PSA_SUCCESS)
    {
        *ciphertext_length = PSA_AEAD_ENCRYPT_OUTPUT_SIZE(keyType, alg, plaintext_length);
    }

    if (output != ciphertext)
    {
        /* Handle unaligned address case */
        (void)memcpy(ciphertext, output, *ciphertext_length);
        free(output_free_address);
    }
    return status;
}

/*
 *  ======== ti_psa_aead_decrypt ========
 */
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
                                 size_t *plaintext_length)
{
    int_fast16_t ret;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_type_t keyType;
    psa_status_t status;
    size_t keyBits;
    size_t payload_length;
    size_t tagLength;
    uint8_t *output           = plaintext;
    void *output_free_address = NULL;
    uint8_t *tag;

    if (plaintext_length != NULL)
    {
        *plaintext_length = 0;
    }
    else
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!PSA_ALG_IS_AEAD(alg) || PSA_ALG_IS_WILDCARD(alg))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(key, &attributes);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&attributes, PSA_KEY_USAGE_DECRYPT, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    keyType        = psa_get_key_type(&attributes);
    keyBits        = psa_get_key_bits(&attributes);
    tagLength      = PSA_AEAD_TAG_LENGTH(keyType, keyBits, alg);
    payload_length = ciphertext_length - tagLength;
    if ((tagLength > PSA_AEAD_TAG_MAX_SIZE) || (tagLength > ciphertext_length))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (payload_length > plaintext_size)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* True for supported AEAD */
    if (PSA_BLOCK_CIPHER_BLOCK_LENGTH(keyType) != PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    if (!IS_WORD_ALIGNED(plaintext))
    {
        /* Handle unaligned address case */
        output = psa_aligned_malloc(PSA_AEAD_DECRYPT_OUTPUT_SIZE(keyType, alg, ciphertext_length),
                                    &output_free_address);
        if (output == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }
#endif

    tag = (uint8_t *)(ciphertext + payload_length);

    if (((tag == NULL) && (tagLength != 0)) || ((additional_data == NULL) && (additional_data_length != 0)) ||
        ((output == NULL) && (plaintext_length != 0)) || ((ciphertext == NULL) && (ciphertext_length != 0)) ||
        (nonce == NULL))
    {
        if (output != plaintext)
        {
            free(output_free_address);
        }
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Init status in case the crypto driver is not supported */
    status = PSA_ERROR_NOT_SUPPORTED;

    switch (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg))
    {
#ifdef ENABLE_TI_CRYPTO_AESCCM
        case PSA_ALG_CCM:
            {
                /* Check for correct tag size. Test assumes tagLength=0 is invalid */
                status = psa_validate_ccm_tag_length(tagLength);
                if (status != PSA_SUCCESS)
                {
                    if (output != plaintext)
                    {
                        free(output_free_address);
                    }
                    return status;
                }
                AESCCM_Config aesccmConfig;
                AESCCM_Object aesccmObject;
                AESCCM_Handle aesccmHandle = psa_aesccm_construct(&aesccmConfig, &aesccmObject);

                if (aesccmHandle == NULL)
                {
                    if (output != plaintext)
                    {
                        free(output_free_address);
                    }
                    return PSA_ERROR_BAD_STATE;
                }

                AESCCM_OneStepOperation aesccmOneStepOp;
                CryptoKey aesccmCryptoKey;

                AESCCM_OneStepOperation_init(&aesccmOneStepOp);
                KeyStore_PSA_initKey(&aesccmCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
                aesccmOneStepOp.key         = &aesccmCryptoKey;
                aesccmOneStepOp.aad         = (uint8_t *)additional_data;
                aesccmOneStepOp.aadLength   = additional_data_length;
                aesccmOneStepOp.input       = (uint8_t *)ciphertext;
                aesccmOneStepOp.output      = (uint8_t *)output;
                aesccmOneStepOp.inputLength = payload_length;
                aesccmOneStepOp.nonce       = (uint8_t *)nonce;
                aesccmOneStepOp.nonceLength = nonce_length;
                aesccmOneStepOp.mac         = tag;
                aesccmOneStepOp.macLength   = tagLength;

                ret    = AESCCM_oneStepDecrypt(aesccmHandle, &aesccmOneStepOp);
                status = map_AES_status(ret);

                if (((AESCCM_Object *)aesccmHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
                {
                    /* Set a marker so that the secure callback knows that the driver handle can be closed, since
                     * this is a one-shot operation.
                     */
                    ((AESCCM_Object *)aesccmHandle->object)->common.isOpen = false;
                }
                else
                {
                    AESCCM_close(aesccmHandle);
                }

                break;
            }
#endif

#ifdef ENABLE_TI_CRYPTO_AESGCM
        case PSA_ALG_GCM:
            {
                /* Check for correct tag size. Test assumes tagLength=0 is invalid */
                status = psa_validate_gcm_tag_length(tagLength);
                if (status != PSA_SUCCESS)
                {
                    if (output != plaintext)
                    {
                        free(output_free_address);
                    }
                    return status;
                }

                AESGCM_Config aesgcmConfig;
                AESGCM_Object aesgcmObject;

                AESGCM_Handle aesgcmHandle = psa_aesgcm_construct(&aesgcmConfig, &aesgcmObject);

                if (aesgcmHandle == NULL)
                {
                    if (output != ciphertext)
                    {
                        free(output_free_address);
                    }
                    return PSA_ERROR_BAD_STATE;
                }

                AESGCM_OneStepOperation aesgcmOneStepOp;
                CryptoKey aesgcmCryptoKey;

                AESGCM_OneStepOperation_init(&aesgcmOneStepOp);
                KeyStore_PSA_initKey(&aesgcmCryptoKey, key, PSA_BITS_TO_BYTES(keyBits), NULL);
                aesgcmOneStepOp.key                   = &aesgcmCryptoKey;
                aesgcmOneStepOp.aad                   = (uint8_t *)additional_data;
                aesgcmOneStepOp.aadLength             = additional_data_length;
                aesgcmOneStepOp.input                 = (uint8_t *)ciphertext;
                aesgcmOneStepOp.output                = output;
                aesgcmOneStepOp.inputLength           = payload_length;
                aesgcmOneStepOp.iv                    = (uint8_t *)nonce;
                aesgcmOneStepOp.ivLength              = nonce_length;
                aesgcmOneStepOp.ivInternallyGenerated = 0;
                aesgcmOneStepOp.mac                   = tag;
                aesgcmOneStepOp.macLength             = tagLength;

                ret    = AESGCM_oneStepDecrypt(aesgcmHandle, &aesgcmOneStepOp);
                status = map_AES_status(ret);

                if (((AESGCM_Object *)aesgcmHandle->object)->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
                {
                    /* Set a marker so that the secure callback knows that the driver handle can be closed, since
                     * this is a one-shot operation.
                     */
                    ((AESGCM_Object *)aesgcmHandle->object)->common.isOpen = false;
                }
                else
                {
                    AESGCM_close(aesgcmHandle);
                }
                break;
            }
#endif

        default:
            (void)ret;
            /* Do nothing */
            break;
    }

    if (status == PSA_SUCCESS)
    {
        *plaintext_length = PSA_AEAD_DECRYPT_OUTPUT_SIZE(keyType, alg, ciphertext_length);
    }

    if (output != plaintext)
    {
        /* Handle unaligned address case */
        (void)memcpy(plaintext, output, *plaintext_length);
        free(output_free_address);
    }
    return status;
}

/******************************************************************************/
/* Key derivation */
/******************************************************************************/

/*
 *  ======== ti_psa_key_derivation_abort ========
 */
psa_status_t ti_psa_key_derivation_abort(psa_key_derivation_operation_t *operation)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    psa_status_t status;

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_key_derivation_abort(&operation->MBEDTLS_PRIVATE(ctx).ti_ctx);

        KeyStore_releaseLock();

        return status;
    }
    else
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_get_capacity ========
 */
psa_status_t ti_psa_key_derivation_get_capacity(const psa_key_derivation_operation_t *operation, size_t *capacity)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    psa_status_t status;

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_key_derivation_get_capacity(&operation->MBEDTLS_PRIVATE(ctx).ti_ctx, capacity);

        KeyStore_releaseLock();

        return status;
    }
    else
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_set_capacity ========
 */
psa_status_t ti_psa_key_derivation_set_capacity(psa_key_derivation_operation_t *operation, size_t capacity)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    psa_status_t status;

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_key_derivation_set_capacity(&operation->MBEDTLS_PRIVATE(ctx).ti_ctx, capacity);

        KeyStore_releaseLock();

        return status;
    }
    else
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_output_bytes ========
 */
psa_status_t ti_psa_key_derivation_output_bytes(psa_key_derivation_operation_t *operation,
                                                uint8_t *output,
                                                size_t output_length)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    return PSA_ERROR_NOT_SUPPORTED;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_output_key ========
 */
psa_status_t ti_psa_key_derivation_output_key(const psa_key_attributes_t *attributes,
                                              psa_key_derivation_operation_t *operation,
                                              mbedtls_svc_key_id_t *key)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    psa_status_t status;
    psa_key_attributes_t attributesCopy;

    status = psa_copy_attr_and_modify_alg(&attributesCopy, attributes, sizeof(attributesCopy));

    if (status == PSA_SUCCESS)
    {
        if (HSMXXF3_acquireLock(SemaphoreP_WAIT_FOREVER, (uintptr_t)NULL))
        {
            if (KeyStore_acquireLock())
            {
                status = KeyMgmt_psa_key_derivation_output_key(&attributesCopy,
                                                               &operation->MBEDTLS_PRIVATE(ctx).ti_ctx,
                                                               key);

                if (status != PSA_SUCCESS)
                {
                    *key = mbedtls_svc_key_id_make(PSA_CRYPTO_KEY_ID_DEFAULT_OWNER, PSA_KEY_ID_NULL);
                }

                KeyStore_releaseLock();
            }
            else
            {
                status = PSA_ERROR_GENERIC_ERROR;
            }

            HSMXXF3_releaseLock();
        }
        else
        {
            status = PSA_ERROR_GENERIC_ERROR;
        }
    }

    return status;

#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_setup ========
 */
psa_status_t ti_psa_key_derivation_setup(psa_key_derivation_operation_t *operation, psa_algorithm_t alg)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    psa_status_t status;

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_key_derivation_setup(&operation->MBEDTLS_PRIVATE(ctx).ti_ctx, alg);

        KeyStore_releaseLock();

        return status;
    }
    else
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_input_bytes ========
 */
psa_status_t ti_psa_key_derivation_input_bytes(psa_key_derivation_operation_t *operation,
                                               psa_key_derivation_step_t step,
                                               const uint8_t *data,
                                               size_t data_length)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    psa_status_t status;

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_key_derivation_input_bytes(&operation->MBEDTLS_PRIVATE(ctx).ti_ctx,
                                                        step,
                                                        data,
                                                        data_length);

        KeyStore_releaseLock();

        return status;
    }
    else
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_input_integer ========
 */
psa_status_t ti_psa_key_derivation_input_integer(psa_key_derivation_operation_t *operation,
                                                 psa_key_derivation_step_t step,
                                                 uint64_t value)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    psa_status_t status;

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_key_derivation_input_integer(&operation->MBEDTLS_PRIVATE(ctx).ti_ctx, step, value);

        KeyStore_releaseLock();

        return status;
    }
    else
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_input_key ========
 */
psa_status_t ti_psa_key_derivation_input_key(psa_key_derivation_operation_t *operation,
                                             psa_key_derivation_step_t step,
                                             mbedtls_svc_key_id_t key)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    psa_status_t status;

    if (KeyStore_acquireLock())
    {
        status = KeyMgmt_psa_key_derivation_input_key(&operation->MBEDTLS_PRIVATE(ctx).ti_ctx, step, key);

        KeyStore_releaseLock();

        return status;
    }
    else
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_verify_bytes ========
 */
psa_status_t ti_psa_key_derivation_verify_bytes(psa_key_derivation_operation_t *operation,
                                                const uint8_t *expected_output,
                                                size_t output_length)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    return PSA_ERROR_NOT_SUPPORTED;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/*
 *  ======== ti_psa_key_derivation_verify_key ========
 */
psa_status_t ti_psa_key_derivation_verify_key(psa_key_derivation_operation_t *operation, mbedtls_svc_key_id_t expected)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    return PSA_ERROR_NOT_SUPPORTED;
#else
    return PSA_ERROR_NOT_SUPPORTED;
#endif
}

/******************************************************************************/
/* Key Agreement */
/******************************************************************************/

/*
 *  ======== ti_psa_raw_key_agreement ========
 */
psa_status_t ti_psa_raw_key_agreement(psa_algorithm_t alg,
                                      mbedtls_svc_key_id_t private_key,
                                      const uint8_t *peer_key,
                                      size_t peer_key_length,
                                      uint8_t *output,
                                      size_t output_size,
                                      size_t *output_length)
{
#ifndef ENABLE_TI_CRYPTO_ECDH
    return PSA_ERROR_NOT_SUPPORTED;
#else
    int_fast16_t ret;
    psa_ecc_family_t curveFamily;
    psa_key_attributes_t privateKeyAttr = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_type_t privateKeyType;
    psa_status_t status;
    size_t curveBits;
    size_t curveBytes;
    size_t keyBits;
    size_t publicKeyBytes;

    /* For now, ECDH is the only supported key agreement algorithm */
    if (alg != PSA_ALG_ECDH)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Fetch key attributes using key ID */
    status = ti_psa_get_key_attributes(private_key, &privateKeyAttr);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Check key policies (permitted usage and allowed algorithms) */
    status = psa_key_attributes_usage_check(&privateKeyAttr, PSA_KEY_USAGE_DERIVE, alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    privateKeyType = psa_get_key_type(&privateKeyAttr);
    curveFamily    = PSA_KEY_TYPE_ECC_GET_FAMILY(privateKeyType);
    keyBits        = psa_get_key_bits(&privateKeyAttr);
    curveBits      = psa_get_key_bits(&privateKeyAttr);
    curveBytes     = PSA_BITS_TO_BYTES(curveBits);

    /* The only valid key type is PSA_KEY_TYPE_IS_ECC_KEY_PAIR */
    if (!PSA_KEY_TYPE_IS_ECC_KEY_PAIR(privateKeyType))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    ECDH_OperationComputeSharedSecret computeSharedSecretOp;
    CryptoKey sharedSecret;
    CryptoKey ecdhPrivateKey;
    CryptoKey ecdhPublicKey;
    ECDH_Config ecdhConfig;
    ECDH_Object ecdhObject;

    ECDH_OperationComputeSharedSecret_init(&computeSharedSecretOp);

    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    computeSharedSecretOp.curveType = map_keyTypeToECDHCurveTypeHSM(privateKeyType, keyBits);

    if (computeSharedSecretOp.curveType == 0)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
    #elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC13X4_CC26X3_CC26X4)
    computeSharedSecretOp.curve = map_keyTypeToECCParams(privateKeyType, keyBits);

    if (computeSharedSecretOp.curve == NULL)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
    #else
        #error "Device not supported"
    #endif

    if (curveFamily == PSA_ECC_FAMILY_MONTGOMERY)
    {
        publicKeyBytes                              = curveBytes;
        computeSharedSecretOp.keyMaterialEndianness = ECDH_LITTLE_ENDIAN_KEY;
    }
    else
    {
        publicKeyBytes = PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(curveBits);

        /* Check that the first byte of the peer key is 0x04 to indicate
         * uncompressed point format.
         */
        if (peer_key[0] != 0x04)
        {
            /* Key format required for platform implementation. For more info,
             * see TI Drivers API documentation.
             */
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    /* Check if peer key has the correct length to verify that it is on the same
     * curve. This check needs to change in the future to a better check that
     * verifies the public key is on the correct (chosen) curve.
     */
    if (peer_key_length != publicKeyBytes)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (output_size < curveBytes)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* The device supports Montgomery and Short Weierstrass */
    KeyStore_PSA_initKey(&ecdhPrivateKey, private_key, PSA_BITS_TO_BYTES(keyBits), NULL);
    CryptoKeyPlaintext_initKey(&ecdhPublicKey, (uint8_t *)peer_key, peer_key_length);

    #ifdef TFM_BUILD
    if (psa_crypto_ns_caller)
    {
        PSACrypto_s_secureCB->length  = curveBytes;
        PSACrypto_s_secureCB->keyBits = keyBits;

        /* Store the shared secret material in the secure callback buffer. The
         * PSA Crypto NS client is responsible for copying the 'x' component of
         * the shared secret to the user provided buffer.
         */
        CryptoKeyPlaintext_initBlankKey(&sharedSecret, &PSACrypto_s_secureCB->buffer[0], publicKeyBytes);
    }
    else
    #endif
    {
        CryptoKeyPlaintext_initBlankKey(&sharedSecret, &localBuf[0], publicKeyBytes);
    }

    computeSharedSecretOp.myPrivateKey   = &ecdhPrivateKey;
    computeSharedSecretOp.theirPublicKey = &ecdhPublicKey;
    computeSharedSecretOp.sharedSecret   = &sharedSecret;

    ECDH_Handle ecdhHandle = psa_ecdh_construct(&ecdhConfig, &ecdhObject);

    if (ecdhHandle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    ret    = ECDH_computeSharedSecret(ecdhHandle, &computeSharedSecretOp);
    status = map_ECDH_status(ret);

    if (!psa_crypto_ns_caller)
    {
        if (status == PSA_SUCCESS)
        {
            if (keyBits == 255)
            {
                /* For Curve25519, only the 'x' component is returned by the ECDH
                 * driver thus it can be copied directly as the shared secret.
                 */
                (void)memcpy(output, &localBuf[0], curveBytes);
            }
            else
            {
                /* The ECDH driver returns the shared secret in uncompressed point
                 * format (0x04 || x || y). Copy only the 'x' component in raw
                 * encoding format as the shared secret.
                 */
                (void)memcpy(output, &localBuf[1], curveBytes);
            }

            *output_length = curveBytes;
        }
    }

    /* Close temporary handle */
    if (((ECDH_Object *)ecdhHandle->object)->returnBehavior == ECDH_RETURN_BEHAVIOR_CALLBACK)
    {
        /* Set a marker so that the secure callback knows that the ECDH_Handle can be closed, since
         * this is a one-shot operation.
         */
        ((ECDH_Object *)ecdhHandle->object)->isOpen = false;
    }
    else
    {
        ECDH_close(ecdhHandle);
    }

    return status;
#endif /* ENABLE_TI_CRYPTO_ECDH */
}

/*
 *  ======== ti_psa_key_derivation_key_agreement ========
 */
psa_status_t ti_psa_key_derivation_key_agreement(psa_key_derivation_operation_t *operation,
                                                 psa_key_derivation_step_t step,
                                                 mbedtls_svc_key_id_t private_key,
                                                 const uint8_t *peer_key,
                                                 size_t peer_key_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

/******************************************************************************/
/* Random generation */
/******************************************************************************/

/*
 *  ======== ti_psa_generate_random ========
 */
psa_status_t ti_psa_generate_random(uint8_t *output, size_t output_size)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #ifndef ENABLE_TI_CRYPTO_RNG
    return PSA_ERROR_NOT_SUPPORTED;
    #else
    int_fast16_t ret;
    psa_status_t status;
    RNG_Config rngConfig;
    RNG_Object rngObject;

    RNG_Handle rngHandle = psa_rng_construct(&rngConfig, &rngObject);

    if (rngHandle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    ret    = RNG_getRandomBits(rngHandle, output, PSA_BYTES_TO_BITS(output_size));
    status = map_RNG_status(ret);

    /* There is no callback mode for RNG, so we can just close the driver immediately after. */
    RNG_close(rngHandle);

    return status;
    #endif /* ENABLE_TI_CRYPTO_RNG */
#else
    #ifndef ENABLE_TI_CRYPTO_TRNG
    return PSA_ERROR_NOT_SUPPORTED;
    #else
    int_fast16_t ret;
    psa_status_t status;

    if (trngHandle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    ret    = TRNG_getRandomBytes(trngHandle, output, output_size);
    status = map_TRNG_status(ret);

    return status;
    #endif /* ENABLE_TI_CRYPTO_TRNG */
#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) \
        * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                                                     \
        */
}

#ifdef ENABLE_TI_CRYPTO_RNG
    #if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
         (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
/*
 *  ======== psa_get_curve_order ========
 *  Returns a pointer to the curve order in little-endian.
 */
static psa_status_t psa_get_curve_order(const uint8_t **order, psa_key_type_t key_type, size_t key_bits)
{
    psa_status_t status                      = PSA_SUCCESS;
    const ECCParams_CurveParams *curveParams = map_keyTypeToECCParams(key_type, key_bits);

    if (curveParams != NULL)
    {
        *order = curveParams->order;
    }
    else
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    return status;
}
    #endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == \
            * DeviceFamily_PARENT_CC35XX)                                                    \
            * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                         \
            */
#endif     /* ENABLE_TI_CRYPTO_RNG */

/*
 *  ======== ti_psa_generate_key ========
 *  This function requires full key attributes. If built into the TFM, the
 *  crypto secure service is responsible for translating client key attributes
 *  to the full key attributes before calling this function.
 */
psa_status_t ti_psa_generate_key(const psa_key_attributes_t *attributes, mbedtls_svc_key_id_t *key)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #ifndef ENABLE_TI_CRYPTO_RNG
    return PSA_ERROR_NOT_SUPPORTED;
    #else
    const uint8_t *upperLimit;
    int_fast16_t ret;
    psa_key_type_t keyType = psa_get_key_type(attributes);
    psa_status_t status;
    size_t keyBits       = psa_get_key_bits(attributes);
    size_t keyBytes      = PSA_BITS_TO_BYTES(keyBits);
    uint8_t *keyMaterial = NULL;

    if (PSA_KEY_TYPE_IS_PUBLIC_KEY(keyType) || (keyBits == 0))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (keyBytes <= sizeof(localBuf))
    {
        keyMaterial = &localBuf[0];
    }
    else
    {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    if (PSA_KEY_TYPE_IS_UNSTRUCTURED(keyType))
    {
        /* Symmetric key or raw non-key data can use any random number */
        status = ti_psa_generate_random(keyMaterial, keyBytes);
    }
    else if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(keyType) || PSA_KEY_TYPE_IS_DH_KEY_PAIR(keyType))
    {
        /* Set upper limit to point to curve order (little-endian) */
        status = psa_get_curve_order(&upperLimit, keyType, keyBits);
        if (status != PSA_SUCCESS)
        {
            return status;
        }

        RNG_Config rngConfig;
        RNG_Object rngObject;

        RNG_Handle rngHandle = psa_rng_construct(&rngConfig, &rngObject);

        if (rngHandle == NULL)
        {
            return PSA_ERROR_BAD_STATE;
        }

        /* A private key 'd' must be with the range: 1 <= d < n, where 'n' is
         * the order of the chosen curve. The lower limit (inclusive) is 1 and
         * upper limit (exclusive) is 'n' when provided to
         * RNG_getxxRandomNumberInRange().
         */
        if (PSA_ECC_FAMILY_IS_WEIERSTRASS(PSA_KEY_TYPE_ECC_GET_FAMILY(keyType)))
        {
            /* Private keys are big-endian for Weierstrass (Brainpool and
             * SECP/NIST) curves.
             */

            /* Convert curve order to big-endian format for upper limit */
            CryptoUtils_reverseCopy(upperLimit, &curveOrder[0], keyBytes);
            upperLimit = &curveOrder[0];

            ret = RNG_getBERandomNumberInRange(rngHandle, CryptoUtils_limitOne, upperLimit, keyMaterial, keyBits);
        }
        else
        {
            /* Private keys are little-endian for Montgomery (Curve25519) and
             * Edwards (Ed25519) curves.
             */
            ret = RNG_getLERandomNumberInRange(rngHandle, CryptoUtils_limitOne, upperLimit, keyMaterial, keyBits);
        }

        status = map_RNG_status(ret);
        /* There is no callback mode for RNG, so we can just close the driver immediately after. */
        RNG_close(rngHandle);
    }
    else
    {
        /* Other key types such as RSA and DES keys are not supported */
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (status == PSA_SUCCESS)
    {
        status = ti_psa_import_key(attributes, keyMaterial, keyBytes, key);
    }

    return status;
    #endif /* ENABLE_TI_CRYPTO_RNG */
#else
    #ifndef ENABLE_TI_CRYPTO_TRNG
    return PSA_ERROR_NOT_SUPPORTED;
    #else
    int_fast16_t ret;
    CryptoKey cryptoKey;
    uint8_t *keyMaterial   = NULL;
    psa_key_type_t keyType = psa_get_key_type(attributes);
    psa_status_t status;
    size_t keyBytes = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));

    if (trngHandle == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    if (PSA_KEY_TYPE_IS_PUBLIC_KEY(keyType) || (keyBytes == 0))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (keyBytes <= sizeof(localBuf))
    {
        keyMaterial = &localBuf[0];
    }
    else
    {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    CryptoKeyPlaintext_initBlankKey(&cryptoKey, keyMaterial, keyBytes);

    ret    = TRNG_generateKey(trngHandle, &cryptoKey);
    status = map_TRNG_status(ret);

    if (status == PSA_SUCCESS)
    {
        status = ti_psa_import_key(attributes, keyMaterial, keyBytes, key);
    }

    return status;
    #endif /* ENABLE_TI_CRYPTO_TRNG */
#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) \
        * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                                                     \
        */
}

/******************************************************************************/
/* Initialization */
/******************************************************************************/

/*
 *  ======== psa_crypto_init ========
 */
psa_status_t psa_crypto_init(void)
{
    psa_status_t status = PSA_SUCCESS;

    HSMXXF3_constructRTOSObjects();

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if (HSMXXF3_init() != HSMXXF3_STATUS_SUCCESS)
    {
        return PSA_ERROR_HARDWARE_FAILURE;
    }
#endif

/* Driver init */
#ifdef ENABLE_TI_CRYPTO_AESCBC
    AESCBC_init();
#endif

#ifdef ENABLE_TI_CRYPTO_AESCCM
    AESCCM_init();
#endif

#ifdef ENABLE_TI_CRYPTO_AESCMAC
    /* It is safe to unconditionally initialize AES CMAC driver */
    AESCMAC_init();
#endif

#ifdef ENABLE_TI_CRYPTO_AESCTR
    AESCTR_init();
#endif

#ifdef ENABLE_TI_CRYPTO_AESECB
    AESECB_init();
#endif

#ifdef ENABLE_TI_CRYPTO_AESGCM
    AESGCM_init();
#endif

#ifdef ENABLE_TI_CRYPTO_ECDH
    ECDH_init();
#endif

#ifdef ENABLE_TI_CRYPTO_ECDSA
    ECDSA_init();
#endif

#ifdef ENABLE_TI_CRYPTO_EDDSA
    EDDSA_init();
#endif

#ifdef ENABLE_TI_CRYPTO_SHA2
    SHA2_init(); /* Driver initializations only need to be called once per application, rather than once per thread,
                  * so this can remain in psa_crypto_init().
                  */
#endif

#if defined(ENABLE_TI_CRYPTO_RNG)
    RNG_init();
#endif

#if defined(ENABLE_TI_CRYPTO_TRNG)
    if (trngHandle == NULL)
    {
        TRNG_init();

        TRNG_Params trngParams;
        TRNG_Params_init(&trngParams);
        trngParams.returnBehavior = TRNG_RETURN_BEHAVIOR_BLOCKING;

        memset(&trngObject, 0x0, sizeof(trngObject));
        trngConfig.object  = &trngObject;
        trngConfig.hwAttrs = &trngHWAttrs;

        trngHandle = TRNG_construct(&trngConfig, &trngParams);
    }
#endif

#if (TFM_ENABLED == 0)
    /* Initialize Key Store which will handle initialization of ITS */
    status = KeyStore_PSA_init();
#endif

    return status;
}
