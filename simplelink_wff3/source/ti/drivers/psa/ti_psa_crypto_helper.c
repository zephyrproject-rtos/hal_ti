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

/******************************************************************************
 * PSA Crypto helper functions
 ******************************************************************************/

/* ti_psa_crypto_helper.h must be included before crypto_config.h */
#include <ti/drivers/psa/ti_psa_crypto_helper.h>
#if ((TFM_ENABLED == 1) && !defined(TFM_BUILD))
    /* PSACrypto_ns expects a psa_key_id_t only, without the owner encoded. */
    #ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
        #undef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    #endif
    #include <third_party/tfm/interface/include/psa/crypto.h>
    /* Needed to determine the HW-accelerated PSA algorithms */
    #include <third_party/mbedtls/ti/configs/config-psa-crypto-hsm.h>
    /**
     * \brief This value is used to mark an handle for multipart operations as invalid.
     */
    #define TFM_CRYPTO_INVALID_HANDLE (0x0u)
#else
    #include <third_party/mbedtls/include/psa/crypto.h>
#endif

#ifdef TFM_BUILD
    #include "config_tfm.h"
#else
    #include <third_party/psa_crypto/crypto_config.h>
#endif

#include <ti/drivers/AESCommon.h>
#include <ti/drivers/ECDH.h>
#include <ti/drivers/ECDSA.h>
#include <ti/drivers/RNG.h>
#include <ti/drivers/SHA2.h>
#include <ti/drivers/TRNG.h>

#include <ti/devices/DeviceFamily.h>

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #include <ti/drivers/EDDSA.h>
    #include <ti/drivers/ecdh/ECDHXXF3HSM.h>
    #include <ti/drivers/ecdsa/ECDSAXXF3HSM.h>
    #include <ti/drivers/rng/RNGXXF3HSM.h>
    #include <ti/drivers/trng/TRNGXXF3HSM.h>
    #include <ti/drivers/eddsa/EDDSAXXF3HSM.h>
#endif

#ifdef TFM_BUILD
    #include <third_party/tfm/secure_fw/partitions/crypto/tfm_crypto_api.h> /* For tfm_crypto_get_caller_id */
#elif (TI_SW_CRYPTO_ENABLED == 1)
    /* Includes for ti_psa_crypto_wrapper helper content, in NS side */
    #include <string.h>                                       //memcpy
    #include <third_party/mbedtls/include/mbedtls/platform.h> //mbedtls_calloc
    #include <third_party/mbedtls/library/common.h>

    /* Includes required for the MBEDTLS_ERR codes in mbedtls_to_psa_error() */
    #if defined(MBEDTLS_AES_C)
        #include <third_party/mbedtls/include/mbedtls/aes.h>
    #endif

    #if defined(MBEDTLS_ASN1_PARSE_C) || defined(MBEDTLS_ASN1_WRITE_C)
        #include <third_party/mbedtls/include/mbedtls/asn1.h>
        #include <third_party/mbedtls/include/mbedtls/asn1write.h>
    #endif

    #if defined(MBEDTLS_BIGNUM_C)
        #include <third_party/mbedtls/include/mbedtls/bignum.h>
    #endif

    #if defined(MBEDTLS_CAMELLIA_C)
        #include <third_party/mbedtls/include/mbedtls/camellia.h>
    #endif

    #if defined(MBEDTLS_CCM_C)
        #include <third_party/mbedtls/include/mbedtls/ccm.h>
    #endif

    #if defined(MBEDTLS_CHACHA20_C)
        #include <third_party/mbedtls/include/mbedtls/chacha20.h>
    #endif

    #if defined(MBEDTLS_CIPHER_C)
        #include <third_party/mbedtls/include/mbedtls/cipher.h>
    #endif

    #if defined(MBEDTLS_CHACHAPOLY_C)
        #include <third_party/mbedtls/include/mbedtls/chachapoly.h>
    #endif

    #if !(defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG) || defined(MBEDTLS_PSA_HMAC_DRBG_MD_TYPE))
        #include <third_party/mbedtls/include/mbedtls/ctr_drbg.h>
    #endif

    #if defined(MBEDTLS_DES_C)
        #include <third_party/mbedtls/include/mbedtls/des.h>
    #endif

    #if defined(MBEDTLS_ECP_LIGHT) || defined(MBEDTLS_ECP_RESTARTABLE)
        #include <third_party/mbedtls/include/mbedtls/ecp.h>
    #endif

    #include <third_party/mbedtls/include/mbedtls/entropy.h>
    #include <third_party/mbedtls/include/mbedtls/error.h>

    #if defined(MBEDTLS_GCM_C)
        #include <third_party/mbedtls/include/mbedtls/gcm.h>
    #endif

    #if !defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG) && defined(MBEDTLS_PSA_HMAC_DRBG_MD_TYPE)
        #include <third_party/mbedtls/include/mbedtls/hmac_drbg.h>
    #endif

    #if defined(MBEDTLS_MD_LIGHT)
        #include <third_party/mbedtls/include/mbedtls/md.h>
    #endif

    #if defined(MBEDTLS_PK_C)
        #include <third_party/mbedtls/include/mbedtls/pk.h>
    #endif

    #if defined(MBEDTLS_RSA_C)
        #include <third_party/mbedtls/include/mbedtls/rsa.h>
    #endif
#endif /* TFM_BUILD */

/*
 *  ======== map_SHA2_status ========
 */
psa_status_t map_SHA2_status(int_fast16_t status)
{
    psa_status_t psaStatus;

    switch (status)
    {
        case SHA2_STATUS_SUCCESS:
            psaStatus = PSA_SUCCESS;
            break;

        case SHA2_STATUS_ERROR:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;

        case SHA2_STATUS_RESOURCE_UNAVAILABLE:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

        case SHA2_STATUS_CANCELED:
            psaStatus = PSA_ERROR_BAD_STATE;
            break;

        case SHA2_STATUS_KEYSTORE_ERROR:
            psaStatus = PSA_ERROR_INVALID_HANDLE;
            break;

        case SHA2_STATUS_UNSUPPORTED:
            psaStatus = PSA_ERROR_NOT_SUPPORTED;
            break;

        default:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;
    }

    return psaStatus;
}

/*
 *  ======== map_ECDSA_status ========
 */
psa_status_t map_ECDSA_status(int_fast16_t status, bool isVerifyOp)
{
    psa_status_t psaStatus;

    switch (status)
    {
        case ECDSA_STATUS_SUCCESS:
            psaStatus = PSA_SUCCESS;
            break;

        case ECDSA_STATUS_ERROR:
            if (isVerifyOp)
            {
                psaStatus = PSA_ERROR_INVALID_SIGNATURE;
            }
            else
            {
                psaStatus = PSA_ERROR_GENERIC_ERROR;
            }
            break;

        case ECDSA_STATUS_RESOURCE_UNAVAILABLE:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

        case ECDSA_STATUS_R_LARGER_THAN_ORDER:
        case ECDSA_STATUS_S_LARGER_THAN_ORDER:
            psaStatus = PSA_ERROR_INVALID_SIGNATURE;
            break;

        case ECDSA_STATUS_CANCELED:
            psaStatus = PSA_ERROR_BAD_STATE;
            break;

        case ECDSA_STATUS_INVALID_KEY_SIZE:
        case ECDSA_STATUS_POINT_AT_INFINITY:
        case ECDSA_STATUS_PUBLIC_KEY_NOT_ON_CURVE:
        case ECDSA_STATUS_PUBLIC_KEY_LARGER_THAN_PRIME:
        case ECDSA_STATUS_KEYSTORE_ERROR:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)

        case ECDSAXXF3HSM_STATUS_NO_VALID_CURVE_TYPE_PROVIDED:
        case ECDSAXXF3HSM_STATUS_INVALID_KEY_ENCODING:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

        case ECDSAXXF3HSM_STATUS_HARDWARE_ERROR:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1) \
        */

        default:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;
    }

    return psaStatus;
}

#ifdef ENABLE_TI_CRYPTO_EDDSA
/*
 *  ======== map_EDDSA_status ========
 */
psa_status_t map_EDDSA_status(int_fast16_t status, bool isVerifyOp)
{
    psa_status_t psaStatus;

    switch (status)
    {
        case EDDSA_STATUS_SUCCESS:
            psaStatus = PSA_SUCCESS;
            break;

        case EDDSA_STATUS_ERROR:
            if (isVerifyOp)
            {
                psaStatus = PSA_ERROR_INVALID_SIGNATURE;
            }
            else
            {
                psaStatus = PSA_ERROR_GENERIC_ERROR;
            }
            break;

        case EDDSA_STATUS_INVALID_R_SIZE:
        case EDDSA_STATUS_INVALID_S_SIZE:
        case EDDSA_STATUS_S_LARGER_THAN_ORDER:
            psaStatus = PSA_ERROR_INVALID_SIGNATURE;
            break;

        case EDDSA_STATUS_HASH_UNAVAILABLE:
        case EDDSA_STATUS_PKA_UNAVAILABLE:
        case EDDSA_STATUS_SHA2_HASH_FAILURE:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

        case EDDSA_STATUS_PUBLIC_KEY_NOT_ON_CURVE:
        case EDDSA_STATUS_INVALID_PRIVATE_KEY_SIZE:
        case EDDSA_STATUS_INVALID_PUBLIC_KEY_SIZE:
        case EDDSA_STATUS_KEY_ID_PARAM_MISMATCH:
        case EDDSA_STATUS_KEYSTORE_ERROR:
        case EDDSA_STATUS_KEYSTORE_GENERIC_FAILURE:
        case EDDSA_STATUS_KEYSTORE_INVALID_ID:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

        case EDDSA_STATUS_CANCELED:
            psaStatus = PSA_ERROR_BAD_STATE;
            break;

        default:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;
    }

    return psaStatus;
}
#endif

/*
 *  ======== map_ECDH_status ========
 */
psa_status_t map_ECDH_status(int_fast16_t status)
{
    psa_status_t psaStatus;

    switch (status)
    {
        case ECDH_STATUS_SUCCESS:
            psaStatus = PSA_SUCCESS;
            break;

        case ECDH_STATUS_ERROR:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;

        case ECDH_STATUS_RESOURCE_UNAVAILABLE:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

        case ECDH_STATUS_INVALID_KEY_SIZE:
        case ECDH_STATUS_KEYSTORE_ERROR:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

        case ECDH_STATUS_CANCELED:
            psaStatus = PSA_ERROR_BAD_STATE;
            break;

        case ECDH_STATUS_POINT_AT_INFINITY:
        case ECDH_STATUS_PRIVATE_KEY_LARGER_EQUAL_ORDER:
        case ECDH_STATUS_PRIVATE_KEY_ZERO:
        case ECDH_STATUS_PUBLIC_KEY_LARGER_THAN_PRIME:
        case ECDH_STATUS_PUBLIC_KEY_NOT_ON_CURVE:
            psaStatus = PSA_ERROR_INVALID_HANDLE;
            break;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)

        case ECDHXXF3HSM_STATUS_NO_VALID_CURVE_TYPE_PROVIDED:
        case ECDHXXF3HSM_STATUS_INVALID_PRIVATE_KEY_ENCODING:
        case ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_ENCODING:
        case ECDHXXF3HSM_STATUS_INVALID_SHARED_SECRET_KEY_ENCODING:
        case ECDHXXF3HSM_STATUS_INVALID_PRIVATE_KEY_SIZE:
        case ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_SIZE:
        case ECDHXXF3HSM_STATUS_INVALID_SHARED_SECRET_KEY_SIZE:
        case ECDHXXF3HSM_STATUS_INVALID_ECC_KEYS:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

        case ECDHXXF3HSM_STATUS_HARDWARE_ERROR:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1) \
        */

        default:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;
    }
    return psaStatus;
}

#ifdef ENABLE_TI_CRYPTO_RNG
/*
 *  ======== map_RNG_status ========
 */
psa_status_t map_RNG_status(int_fast16_t status)
{
    psa_status_t psaStatus;

    switch (status)
    {
        case RNG_STATUS_SUCCESS:
            psaStatus = PSA_SUCCESS;
            break;

        case RNG_STATUS_ERROR:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;

        case RNG_STATUS_RESOURCE_UNAVAILABLE:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

        case RNG_STATUS_INVALID_INPUTS:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

        case RNG_STATUS_CANCELED:
            psaStatus = PSA_ERROR_BAD_STATE;
            break;

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)

        case RNG_STATUS_INVALID_KEY_ENCODING:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

    #endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == \
              DeviceFamily_PARENT_CC23X1) */

        default:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;
    }

    return psaStatus;
}
#endif

#ifdef ENABLE_TI_CRYPTO_TRNG
/*
 *  ======== map_TRNG_status ========
 */
psa_status_t map_TRNG_status(int_fast16_t status)
{
    psa_status_t psaStatus;

    switch (status)
    {
        case TRNG_STATUS_SUCCESS:
            psaStatus = PSA_SUCCESS;
            break;

        case TRNG_STATUS_ERROR:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;

        case TRNG_STATUS_RESOURCE_UNAVAILABLE:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

        case TRNG_STATUS_INVALID_INPUTS:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

        case TRNG_STATUS_CANCELED:
            psaStatus = PSA_ERROR_BAD_STATE;
            break;

        case TRNG_STATUS_KEYSTORE_ERROR:
            psaStatus = PSA_ERROR_INVALID_HANDLE;
            break;

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)

        case TRNG_STATUS_INVALID_INPUT_SIZE:
        case TRNG_STATUS_INVALID_KEY_ENCODING:
            psaStatus = PSA_ERROR_INVALID_ARGUMENT;
            break;

        case TRNG_STATUS_ALREADY_IN_SPECIFIED_NRBG_TYPE:
            /* This is not an error so return success */
            psaStatus = PSA_SUCCESS;
            break;

    #endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == \
              DeviceFamily_PARENT_CC23X1) */

        default:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;
    }

    return psaStatus;
}
#endif

/*
 *  ======== map_AES_status ========
 */
psa_status_t map_AES_status(int_fast16_t status)
{
    psa_status_t psaStatus;

    switch (status)
    {
        case AES_STATUS_SUCCESS:
            psaStatus = PSA_SUCCESS;
            break;

        case AES_STATUS_ERROR:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;

        case AES_STATUS_RESOURCE_UNAVAILABLE:
            psaStatus = PSA_ERROR_HARDWARE_FAILURE;
            break;

        case AES_STATUS_CANCELED:
            psaStatus = PSA_ERROR_BAD_STATE;
            break;

        case AES_STATUS_FEATURE_NOT_SUPPORTED:
            psaStatus = PSA_ERROR_NOT_SUPPORTED;
            break;

        case AES_STATUS_KEYSTORE_GENERIC_ERROR:
        case AES_STATUS_KEYSTORE_INVALID_ID:
            psaStatus = PSA_ERROR_INVALID_HANDLE;
            break;

        case AES_STATUS_MAC_INVALID:
            psaStatus = PSA_ERROR_INVALID_SIGNATURE;
            break;

        default:
            psaStatus = PSA_ERROR_GENERIC_ERROR;
            break;
    }

    return psaStatus;
}

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
/*
 *  ======== map_keyTypeToECDSACurveTypeHSM ========
 */
ECDSA_CurveType map_keyTypeToECDSACurveTypeHSM(psa_key_type_t keyType, size_t keyBits)
{
    psa_ecc_family_t curveFamily = PSA_KEY_TYPE_ECC_GET_FAMILY(keyType);
    ECDSA_CurveType curveType    = (ECDSA_CurveType)0; /* 0 is an invalid curveType */

    switch (curveFamily)
    {
        case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
            switch (keyBits)
            {
                case 256:
                    curveType = ECDSA_TYPE_BRP_P_256_R1;
                    break;
                case 384:
                    curveType = ECDSA_TYPE_BRP_P_384_R1;
                    break;
                case 512:
                    curveType = ECDSA_TYPE_BRP_P_512_R1;
                    break;
                default:
                    break;
            }
            break;

        case PSA_ECC_FAMILY_SECP_R1:
            switch (keyBits)
            {
                case 192:
                    // TODO: Uncomment once this curve type is supported by HSM drivers (TIDRIVERS-6205)
                    // curveType = ECDSA_TYPE_SEC_P_192_R1;
                    break;
                case 224:
                    curveType = ECDSA_TYPE_SEC_P_224_R1;
                    break;
                case 256:
                    curveType = ECDSA_TYPE_SEC_P_256_R1;
                    break;
                case 384:
                    curveType = ECDSA_TYPE_SEC_P_384_R1;
                    break;
                case 521:
                    curveType = ECDSA_TYPE_SEC_P_521_R1;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }

    return curveType;
}

/*
 *  ======== map_keyTypeToECDHCurveTypeHSM ========
 */
ECDH_CurveType map_keyTypeToECDHCurveTypeHSM(psa_key_type_t keyType, size_t keyBits)
{
    psa_ecc_family_t curveFamily = PSA_KEY_TYPE_ECC_GET_FAMILY(keyType);
    ECDH_CurveType curveType     = (ECDH_CurveType)0; /* 0 is an invalid curveType */

    switch (curveFamily)
    {
        case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
            switch (keyBits)
            {
                case 256:
                    curveType = ECDH_TYPE_BRP_P_256_R1;
                    break;
                case 384:
                    curveType = ECDH_TYPE_BRP_P_384_R1;
                    break;
                case 512:
                    curveType = ECDH_TYPE_BRP_P_512_R1;
                    break;
                default:
                    break;
            }
            break;

        case PSA_ECC_FAMILY_SECP_R1:
            switch (keyBits)
            {
                case 192:
                    // TODO: Uncomment once this curve type is supported by HSM drivers (TIDRIVERS-6737)
                    // curveType = ECDH_TYPE_SEC_P_192_R1;
                    break;
                case 224:
                    curveType = ECDH_TYPE_SEC_P_224_R1;
                    break;
                case 256:
                    curveType = ECDH_TYPE_SEC_P_256_R1;
                    break;
                case 384:
                    curveType = ECDH_TYPE_SEC_P_384_R1;
                    break;
                case 521:
                    curveType = ECDH_TYPE_SEC_P_521_R1;
                    break;
                default:
                    break;
            }
            break;

        case PSA_ECC_FAMILY_MONTGOMERY:
            switch (keyBits)
            {
                case 255:
                    curveType = ECDH_TYPE_CURVE_25519;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }

    return curveType;
}

#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) \
        * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                                                     \
        */

/*
 *  ======== map_keyTypeToECCParams ========
 */
const ECCParams_CurveParams *map_keyTypeToECCParams(psa_key_type_t keyType, size_t keyBits)
{
    psa_ecc_family_t curveFamily             = PSA_KEY_TYPE_ECC_GET_FAMILY(keyType);
    const ECCParams_CurveParams *curveParams = NULL;

    switch (curveFamily)
    {
        case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
            switch (keyBits)
            {
                case 256:
                    curveParams = &ECCParams_BrainpoolP256R1;
                    break;
                case 384:
                    curveParams = &ECCParams_BrainpoolP384R1;
                    break;
                case 512:
                    curveParams = &ECCParams_BrainpoolP512R1;
                    break;
                default:
                    break;
            }
            break;

        case PSA_ECC_FAMILY_SECP_R1:
            switch (keyBits)
            {
#if ((DeviceFamily_PARENT != DeviceFamily_PARENT_CC27XX) && (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) && \
     (DeviceFamily_PARENT != DeviceFamily_PARENT_CC23X1))
                /* NIST P192 is not supported by HSM driver at this time */
                case 192:
                    curveParams = &ECCParams_NISTP192;
                    break;
#endif
                case 224:
                    curveParams = &ECCParams_NISTP224;
                    break;
                case 256:
                    curveParams = &ECCParams_NISTP256;
                    break;
                case 384:
                    curveParams = &ECCParams_NISTP384;
                    break;
                case 521:
                    curveParams = &ECCParams_NISTP521;
                    break;
                default:
                    break;
            }
            break;

        case PSA_ECC_FAMILY_MONTGOMERY:
            if (keyBits == 255)
            {
                curveParams = &ECCParams_Curve25519;
            }
            break;

        case PSA_ECC_FAMILY_TWISTED_EDWARDS:
            if (keyBits == 255)
            {
                curveParams = &ECCParams_Ed25519;
            }
            break;

        default:
            break;
    }

    return curveParams;
}

/*
 *  ======== toKeyStoreKeyID ========
 */
mbedtls_svc_key_id_t toKeyStoreKeyID(psa_key_id_t keyID)
{
#if (((TFM_ENABLED == 0) || defined(TFM_BUILD)) && defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER))
    mbedtls_svc_key_id_t keystoreKeyID;

    keystoreKeyID.key_id = keyID;

    #ifdef TFM_BUILD
    /* tfm_crypto_get_caller_id always returns PSA_SUCCESS */
    (void)tfm_crypto_get_caller_id(&keystoreKeyID.owner);
    #else
    keystoreKeyID.owner            = PSA_CRYPTO_KEY_ID_DEFAULT_OWNER;
    #endif /* TFM_BUILD */

    return keystoreKeyID;
#else
    return (mbedtls_svc_key_id_t)keyID;
#endif
}

/*
 *  ======== toKeyID ========
 */
psa_key_id_t toKeyID(mbedtls_svc_key_id_t keystoreKeyID)
{
#if (((TFM_ENABLED == 0) || defined(TFM_BUILD)) && defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER))
    return keystoreKeyID.key_id;
#else
    return (psa_key_id_t)keystoreKeyID;
#endif
}

/* Helper content for the ti_psa_crypto_wrapper */
#ifndef TFM_BUILD
static bool isAcceleratedHash(psa_algorithm_t alg)
{
    bool status = false;

    switch (alg)
    {
    #if defined(MBEDTLS_PSA_ACCEL_ALG_SHA_224)
        case PSA_ALG_SHA_224:
            status = true;
            break;
    #endif
    #if defined(MBEDTLS_PSA_ACCEL_ALG_SHA_256)
        case PSA_ALG_SHA_256:
            status = true;
            break;
    #endif
    #if defined(MBEDTLS_PSA_ACCEL_ALG_SHA_384)
        case PSA_ALG_SHA_384:
            status = true;
            break;
    #endif
    #if defined(MBEDTLS_PSA_ACCEL_ALG_SHA_512)
        case PSA_ALG_SHA_512:
            status = true;
            break;
    #endif
    #ifdef ENABLE_TI_CRYPTO_SHA3
        #if defined(MBEDTLS_PSA_ACCEL_ALG_SHA3_224)
        case PSA_ALG_SHA3_224:
            status = true;
            break;
        #endif
        #if defined(MBEDTLS_PSA_ACCEL_ALG_SHA3_256)
        case PSA_ALG_SHA3_256:
            status = true;
            break;
        #endif
        #if defined(MBEDTLS_PSA_ACCEL_ALG_SHA3_384)
        case PSA_ALG_SHA3_384:
            status = true;
            break;
        #endif
        #if defined(MBEDTLS_PSA_ACCEL_ALG_SHA3_512)
        case PSA_ALG_SHA3_512:
            status = true;
            break;
        #endif
    #endif /* ENABLE_TI_CRYPTO_SHA3 */
        default:
            status = false;
            break;
    }

    return status;
}

/** Check if a PSA algorithm has HW support.
 *
 * \param[in] alg               The PSA algorithm to check for hardware support.
 * \return                      True, if the algorithm has hardware support.
 * \return                      False, if the algorithm can only be done via software.
 */
bool isHardwareAccelerated(psa_algorithm_t alg)
{
    /* If the MBEDTLS_PSA_ACCEL_ALG_XXX macro for a given algorithm is
     * defined, then that means that the algorithm is hardware accelerated
     * for the target device.
     */
    bool status = false;
    psa_algorithm_t macAlg;

    if (PSA_ALG_IS_HMAC(alg))
    {
    #if defined(MBEDTLS_PSA_ACCEL_ALG_HMAC)
        if (isAcceleratedHash(PSA_ALG_HMAC_GET_HASH(alg)))
        {
            status = true;
        }
    #endif
    }
    else if (PSA_ALG_IS_ECDSA(alg))
    {
    #if defined(MBEDTLS_PSA_ACCEL_ALG_ECDSA)
        if (alg == PSA_ALG_ECDSA_ANY || isAcceleratedHash(PSA_ALG_SIGN_GET_HASH(alg)))
        {
            status = true;
        }
    #endif
    }
    else if (alg == PSA_ALG_PURE_EDDSA)
    {
        /* There is no MBEDTLS_PSA_ACCEL_ALG macro for EDDSA.
         * So, at mbedTLS build time, we'll just always assume
         * it's using hardware acceleration. This requires
         * that ENABLE_TI_CRYPTO_EDDSA is always defined in
         * secure drivers, since we won't implement a SW
         * fallback for EDDSA.
         */
        status = true;
    }
    else if (PSA_ALG_IS_AEAD(alg))
    {
        /* Check AEAD type */
        if (MBEDTLS_PSA_ALG_AEAD_EQUAL(alg, PSA_ALG_GCM))
        {
    #if defined(MBEDTLS_PSA_ACCEL_ALG_GCM)
            status = true;
    #endif
        }
        else if (MBEDTLS_PSA_ALG_AEAD_EQUAL(alg, PSA_ALG_CCM))
        {
    #if defined(MBEDTLS_PSA_ACCEL_ALG_CCM)
            status = true;
    #endif
        }
    }
    else if (PSA_ALG_IS_HASH(alg))
    {
        status = isAcceleratedHash(alg);
    }
    else if (PSA_ALG_IS_BLOCK_CIPHER_MAC(alg))
    {
        macAlg = PSA_ALG_FULL_LENGTH_MAC(alg);

        if (macAlg == PSA_ALG_CBC_MAC)
        {
    #if defined(MBEDTLS_PSA_ACCEL_ALG_CBC_MAC)
            status = true;
    #endif
        }
        else if (macAlg == PSA_ALG_CMAC)
        {
    #if defined(MBEDTLS_PSA_ACCEL_ALG_CMAC)
            status = true;
    #endif
        }
    }
    else if (PSA_ALG_IS_SP800_108_COUNTER_MAC(alg))
    {
        /* PSA_ALG_SP800_108_COUNTER_CMAC or PSA_ALG_SP800_108_COUNTER_HMAC for key derivation */
        status = true;
    }
    else
    {
        switch (alg)
        {
    #ifdef MBEDTLS_PSA_ACCEL_ALG_CBC_NO_PADDING
            case PSA_ALG_CBC_NO_PADDING:
                status = true;
                break;
    #endif
    #ifdef MBEDTLS_PSA_ACCEL_ALG_CBC_PKCS7
            case PSA_ALG_CBC_PKCS7:
                status = true;
                break;
    #endif
    #ifdef MBEDTLS_PSA_ACCEL_ALG_CCM_STAR_NO_TAG
            case PSA_ALG_CCM_STAR_NO_TAG:
                status = true;
                break;
    #endif
    #ifdef MBEDTLS_PSA_ACCEL_ALG_CTR
            case PSA_ALG_CTR:
                status = true;
                break;
    #endif
    #ifdef MBEDTLS_PSA_ACCEL_ALG_ECB_NO_PADDING
            case PSA_ALG_ECB_NO_PADDING:
                status = true;
                break;
    #endif
    #ifdef MBEDTLS_PSA_ACCEL_ALG_ECDH
            case PSA_ALG_ECDH:
                status = true;
                break;
    #endif
            default:
                status = false;
        }
    }

    return status;
}

void setAeadOperationID(psa_aead_operation_t *operation, unsigned int id)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    (void)operation;
    (void)id;
    #else
    operation->MBEDTLS_PRIVATE(id) = id;
    #endif /* TFM_ENABLED == 1 */
}

void setCipherOperationID(psa_cipher_operation_t *operation, unsigned int id)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    (void)operation;
    (void)id;
    #else
    operation->MBEDTLS_PRIVATE(id) = id;
    #endif /* TFM_ENABLED == 1 */
}

void setHashOperationID(psa_hash_operation_t *operation, unsigned int id)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    (void)operation;
    (void)id;
    #else
    operation->MBEDTLS_PRIVATE(id) = id;
    #endif /* TFM_ENABLED == 1 */
}

void setKeyDerivationOperationID(psa_key_derivation_operation_t *operation, unsigned int id)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    (void)operation;
    (void)id;
    #else
    operation->MBEDTLS_PRIVATE(id) = id;
    #endif /* TFM_ENABLED == 1 */
}

void setMacOperationID(psa_mac_operation_t *operation, unsigned int id)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    (void)operation;
    (void)id;
    #else
    operation->MBEDTLS_PRIVATE(id) = id;
    #endif /* TFM_ENABLED == 1 */
}

bool isHardwareAeadOperation(const psa_aead_operation_t *operation)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    return (operation->handle != TFM_CRYPTO_INVALID_HANDLE);
    #else
    return (operation->MBEDTLS_PRIVATE(id) == PSA_CRYPTO_TI_DRIVER_ID);
    #endif /* TFM_ENABLED == 1 */
}

bool isHardwareCipherOperation(const psa_cipher_operation_t *operation)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    return (operation->handle != TFM_CRYPTO_INVALID_HANDLE);
    #else
    return (operation->MBEDTLS_PRIVATE(id) == PSA_CRYPTO_TI_DRIVER_ID);
    #endif /* TFM_ENABLED == 1 */
}

bool isHardwareHashOperation(const psa_hash_operation_t *operation)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    return (operation->handle != TFM_CRYPTO_INVALID_HANDLE);
    #else
    return (operation->MBEDTLS_PRIVATE(id) == PSA_CRYPTO_TI_DRIVER_ID);
    #endif /* TFM_ENABLED == 1 */
}

bool isHardwareKeyDerivationOperation(const psa_key_derivation_operation_t *operation)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    return (operation->handle != TFM_CRYPTO_INVALID_HANDLE);
    #else
    return (operation->MBEDTLS_PRIVATE(id) == PSA_CRYPTO_TI_DRIVER_ID);
    #endif /* TFM_ENABLED == 1 */
}

bool isHardwareMacOperation(const psa_mac_operation_t *operation)
{
    #if (TFM_ENABLED == 1)
    /* In the NS side of TFM builds, where the ti_psa_crypto_wrapper is built,
     * there is no 'id' inside the operation struct. These operations can be
     * identified as HW-accelerated if they have an operation 'handle' instead.
     */
    return (operation->handle != TFM_CRYPTO_INVALID_HANDLE);
    #else
    return (operation->MBEDTLS_PRIVATE(id) == PSA_CRYPTO_TI_DRIVER_ID);
    #endif /* TFM_ENABLED == 1 */
}

    #if (TI_SW_CRYPTO_ENABLED == 1)
psa_status_t mbedtls_to_psa_error(int ret)
{
    /* Mbed TLS error codes can combine a high-level error code and a
     * low-level error code. The low-level error usually reflects the
     * root cause better, so dispatch on that preferably. */
    int low_level_ret = -(-ret & 0x007f);
    switch (low_level_ret != 0 ? low_level_ret : ret)
    {
        case 0:
            return PSA_SUCCESS;

        #if defined(MBEDTLS_AES_C)
        case MBEDTLS_ERR_AES_INVALID_KEY_LENGTH:
        case MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH:
            return PSA_ERROR_NOT_SUPPORTED;
        case MBEDTLS_ERR_AES_BAD_INPUT_DATA:
            return PSA_ERROR_INVALID_ARGUMENT;
        #endif

        #if defined(MBEDTLS_ASN1_PARSE_C) || defined(MBEDTLS_ASN1_WRITE_C)
        case MBEDTLS_ERR_ASN1_OUT_OF_DATA:
        case MBEDTLS_ERR_ASN1_UNEXPECTED_TAG:
        case MBEDTLS_ERR_ASN1_INVALID_LENGTH:
        case MBEDTLS_ERR_ASN1_LENGTH_MISMATCH:
        case MBEDTLS_ERR_ASN1_INVALID_DATA:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_ASN1_ALLOC_FAILED:
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        case MBEDTLS_ERR_ASN1_BUF_TOO_SMALL:
            return PSA_ERROR_BUFFER_TOO_SMALL;
        #endif

        #if defined(MBEDTLS_CAMELLIA_C)
        case MBEDTLS_ERR_CAMELLIA_BAD_INPUT_DATA:
        case MBEDTLS_ERR_CAMELLIA_INVALID_INPUT_LENGTH:
            return PSA_ERROR_NOT_SUPPORTED;
        #endif

        #if defined(MBEDTLS_CCM_C)
        case MBEDTLS_ERR_CCM_BAD_INPUT:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_CCM_AUTH_FAILED:
            return PSA_ERROR_INVALID_SIGNATURE;
        #endif

        #if defined(MBEDTLS_CHACHA20_C)
        case MBEDTLS_ERR_CHACHA20_BAD_INPUT_DATA:
            return PSA_ERROR_INVALID_ARGUMENT;
        #endif

        #if defined(MBEDTLS_CHACHAPOLY_C)
        case MBEDTLS_ERR_CHACHAPOLY_BAD_STATE:
            return PSA_ERROR_BAD_STATE;
        case MBEDTLS_ERR_CHACHAPOLY_AUTH_FAILED:
            return PSA_ERROR_INVALID_SIGNATURE;
        #endif

        #if defined(MBEDTLS_CIPHER_C)
        case MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE:
            return PSA_ERROR_NOT_SUPPORTED;
        case MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_CIPHER_ALLOC_FAILED:
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        case MBEDTLS_ERR_CIPHER_INVALID_PADDING:
            return PSA_ERROR_INVALID_PADDING;
        case MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_CIPHER_AUTH_FAILED:
            return PSA_ERROR_INVALID_SIGNATURE;
        case MBEDTLS_ERR_CIPHER_INVALID_CONTEXT:
            return PSA_ERROR_CORRUPTION_DETECTED;
        #endif

        #if !(defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG) || defined(MBEDTLS_PSA_HMAC_DRBG_MD_TYPE))
        /* Only check CTR_DRBG error codes if underlying mbedtls_xxx
         * functions are passed a CTR_DRBG instance. */
        case MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED:
            return PSA_ERROR_INSUFFICIENT_ENTROPY;
        case MBEDTLS_ERR_CTR_DRBG_REQUEST_TOO_BIG:
        case MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG:
            return PSA_ERROR_NOT_SUPPORTED;
        case MBEDTLS_ERR_CTR_DRBG_FILE_IO_ERROR:
            return PSA_ERROR_INSUFFICIENT_ENTROPY;
        #endif

        #if defined(MBEDTLS_DES_C)
        case MBEDTLS_ERR_DES_INVALID_INPUT_LENGTH:
            return PSA_ERROR_NOT_SUPPORTED;
        #endif

        case MBEDTLS_ERR_ENTROPY_NO_SOURCES_DEFINED:
        case MBEDTLS_ERR_ENTROPY_NO_STRONG_SOURCE:
        case MBEDTLS_ERR_ENTROPY_SOURCE_FAILED:
            return PSA_ERROR_INSUFFICIENT_ENTROPY;

        #if defined(MBEDTLS_GCM_C)
        case MBEDTLS_ERR_GCM_AUTH_FAILED:
            return PSA_ERROR_INVALID_SIGNATURE;
        case MBEDTLS_ERR_GCM_BUFFER_TOO_SMALL:
            return PSA_ERROR_BUFFER_TOO_SMALL;
        case MBEDTLS_ERR_GCM_BAD_INPUT:
            return PSA_ERROR_INVALID_ARGUMENT;
        #endif

        #if !defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG) && defined(MBEDTLS_PSA_HMAC_DRBG_MD_TYPE)
        /* Only check HMAC_DRBG error codes if underlying mbedtls_xxx
         * functions are passed a HMAC_DRBG instance. */
        case MBEDTLS_ERR_HMAC_DRBG_ENTROPY_SOURCE_FAILED:
            return PSA_ERROR_INSUFFICIENT_ENTROPY;
        case MBEDTLS_ERR_HMAC_DRBG_REQUEST_TOO_BIG:
        case MBEDTLS_ERR_HMAC_DRBG_INPUT_TOO_BIG:
            return PSA_ERROR_NOT_SUPPORTED;
        case MBEDTLS_ERR_HMAC_DRBG_FILE_IO_ERROR:
            return PSA_ERROR_INSUFFICIENT_ENTROPY;
        #endif

        #if defined(MBEDTLS_MD_LIGHT)
        case MBEDTLS_ERR_MD_FEATURE_UNAVAILABLE:
            return PSA_ERROR_NOT_SUPPORTED;
        case MBEDTLS_ERR_MD_BAD_INPUT_DATA:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_MD_ALLOC_FAILED:
            return PSA_ERROR_INSUFFICIENT_MEMORY;
            #if defined(MBEDTLS_FS_IO)
        case MBEDTLS_ERR_MD_FILE_IO_ERROR:
            return PSA_ERROR_STORAGE_FAILURE;
            #endif
        #endif

        #if defined(MBEDTLS_BIGNUM_C)
            #if defined(MBEDTLS_FS_IO)
        case MBEDTLS_ERR_MPI_FILE_IO_ERROR:
            return PSA_ERROR_STORAGE_FAILURE;
            #endif
        case MBEDTLS_ERR_MPI_BAD_INPUT_DATA:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_MPI_INVALID_CHARACTER:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL:
            return PSA_ERROR_BUFFER_TOO_SMALL;
        case MBEDTLS_ERR_MPI_NEGATIVE_VALUE:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_MPI_DIVISION_BY_ZERO:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_MPI_NOT_ACCEPTABLE:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_MPI_ALLOC_FAILED:
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        #endif

        #if defined(MBEDTLS_PK_C)
        case MBEDTLS_ERR_PK_ALLOC_FAILED:
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        case MBEDTLS_ERR_PK_TYPE_MISMATCH:
        case MBEDTLS_ERR_PK_BAD_INPUT_DATA:
            return PSA_ERROR_INVALID_ARGUMENT;
            #if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) || defined(MBEDTLS_FS_IO) || defined(MBEDTLS_PSA_ITS_FILE_C)
        case MBEDTLS_ERR_PK_FILE_IO_ERROR:
            return PSA_ERROR_STORAGE_FAILURE;
            #endif
        case MBEDTLS_ERR_PK_KEY_INVALID_VERSION:
        case MBEDTLS_ERR_PK_KEY_INVALID_FORMAT:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_PK_UNKNOWN_PK_ALG:
            return PSA_ERROR_NOT_SUPPORTED;
        case MBEDTLS_ERR_PK_PASSWORD_REQUIRED:
        case MBEDTLS_ERR_PK_PASSWORD_MISMATCH:
            return PSA_ERROR_NOT_PERMITTED;
        case MBEDTLS_ERR_PK_INVALID_PUBKEY:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_PK_INVALID_ALG:
        case MBEDTLS_ERR_PK_UNKNOWN_NAMED_CURVE:
        case MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE:
            return PSA_ERROR_NOT_SUPPORTED;
        case MBEDTLS_ERR_PK_SIG_LEN_MISMATCH:
            return PSA_ERROR_INVALID_SIGNATURE;
        case MBEDTLS_ERR_PK_BUFFER_TOO_SMALL:
            return PSA_ERROR_BUFFER_TOO_SMALL;
        #endif

        case MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED:
            return PSA_ERROR_HARDWARE_FAILURE;
        case MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED:
            return PSA_ERROR_NOT_SUPPORTED;

        #if defined(MBEDTLS_RSA_C)
        case MBEDTLS_ERR_RSA_BAD_INPUT_DATA:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_RSA_INVALID_PADDING:
            return PSA_ERROR_INVALID_PADDING;
        case MBEDTLS_ERR_RSA_KEY_GEN_FAILED:
            return PSA_ERROR_HARDWARE_FAILURE;
        case MBEDTLS_ERR_RSA_KEY_CHECK_FAILED:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_RSA_PUBLIC_FAILED:
        case MBEDTLS_ERR_RSA_PRIVATE_FAILED:
            return PSA_ERROR_CORRUPTION_DETECTED;
        case MBEDTLS_ERR_RSA_VERIFY_FAILED:
            return PSA_ERROR_INVALID_SIGNATURE;
        case MBEDTLS_ERR_RSA_OUTPUT_TOO_LARGE:
            return PSA_ERROR_BUFFER_TOO_SMALL;
        case MBEDTLS_ERR_RSA_RNG_FAILED:
            return PSA_ERROR_INSUFFICIENT_ENTROPY;
        #endif

        #if defined(MBEDTLS_ECP_LIGHT)
        case MBEDTLS_ERR_ECP_BAD_INPUT_DATA:
        case MBEDTLS_ERR_ECP_INVALID_KEY:
            return PSA_ERROR_INVALID_ARGUMENT;
        case MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL:
            return PSA_ERROR_BUFFER_TOO_SMALL;
        case MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE:
            return PSA_ERROR_NOT_SUPPORTED;
        case MBEDTLS_ERR_ECP_SIG_LEN_MISMATCH:
        case MBEDTLS_ERR_ECP_VERIFY_FAILED:
            return PSA_ERROR_INVALID_SIGNATURE;
        case MBEDTLS_ERR_ECP_ALLOC_FAILED:
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        case MBEDTLS_ERR_ECP_RANDOM_FAILED:
            return PSA_ERROR_INSUFFICIENT_ENTROPY;

            #if defined(MBEDTLS_ECP_RESTARTABLE)
        case MBEDTLS_ERR_ECP_IN_PROGRESS:
            return PSA_OPERATION_INCOMPLETE;
            #endif
        #endif

        case MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED:
            return PSA_ERROR_CORRUPTION_DETECTED;

        default:
            return PSA_ERROR_GENERIC_ERROR;
    }
}

/* The following code is copied from psa_crypto.c, which we do not build into our library.
 * We do need this content, however.
 */

/** Copy from an input buffer to a local copy.
 *
 * \param[in] input             Pointer to input buffer.
 * \param[in] input_len         Length of the input buffer.
 * \param[out] input_copy       Pointer to a local copy in which to store the input data.
 * \param[out] input_copy_len   Length of the local copy buffer.
 * \return                      #PSA_SUCCESS, if the buffer was successfully
 *                              copied.
 * \return                      #PSA_ERROR_CORRUPTION_DETECTED, if the local
 *                              copy is too small to hold contents of the
 *                              input buffer.
 */
psa_status_t psa_crypto_copy_input(const uint8_t *input, size_t input_len, uint8_t *input_copy, size_t input_copy_len)
{
    if (input_len > input_copy_len)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    if (input_len > 0)
    {
        memcpy(input_copy, input, input_len);
    }

    return PSA_SUCCESS;
}

/** Copy from a local output buffer into a user-supplied one.
 *
 * \param[in] output_copy       Pointer to a local buffer containing the output.
 * \param[in] output_copy_len   Length of the local buffer.
 * \param[out] output           Pointer to user-supplied output buffer.
 * \param[out] output_len       Length of the user-supplied output buffer.
 * \return                      #PSA_SUCCESS, if the buffer was successfully
 *                              copied.
 * \return                      #PSA_ERROR_BUFFER_TOO_SMALL, if the
 *                              user-supplied output buffer is too small to
 *                              hold the contents of the local buffer.
 */
psa_status_t psa_crypto_copy_output(const uint8_t *output_copy,
                                    size_t output_copy_len,
                                    uint8_t *output,
                                    size_t output_len)
{
    if (output_len < output_copy_len)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (output_copy_len > 0)
    {
        memcpy(output, output_copy, output_copy_len);
    }

    return PSA_SUCCESS;
}

psa_status_t psa_crypto_local_input_alloc(const uint8_t *input, size_t input_len, psa_crypto_local_input_t *local_input)
{
    psa_status_t status;

    *local_input = PSA_CRYPTO_LOCAL_INPUT_INIT;

    if (input_len == 0)
    {
        return PSA_SUCCESS;
    }

    local_input->buffer = mbedtls_calloc(input_len, 1);
    if (local_input->buffer == NULL)
    {
        /* Since we dealt with the zero-length case above, we know that
         * a NULL return value means a failure of allocation. */
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
    /* From now on, we must free local_input->buffer on error. */

    local_input->length = input_len;

    status = psa_crypto_copy_input(input, input_len, local_input->buffer, local_input->length);
    if (status != PSA_SUCCESS)
    {
        goto error;
    }

    return PSA_SUCCESS;

error:
    mbedtls_zeroize_and_free(local_input->buffer, local_input->length);
    local_input->buffer = NULL;
    local_input->length = 0;
    return status;
}

void psa_crypto_local_input_free(psa_crypto_local_input_t *local_input)
{
    mbedtls_zeroize_and_free(local_input->buffer, local_input->length);
    local_input->buffer = NULL;
    local_input->length = 0;
}

psa_status_t psa_crypto_local_output_alloc(uint8_t *output, size_t output_len, psa_crypto_local_output_t *local_output)
{
    *local_output = PSA_CRYPTO_LOCAL_OUTPUT_INIT;

    if (output_len == 0)
    {
        return PSA_SUCCESS;
    }
    local_output->buffer = mbedtls_calloc(output_len, 1);
    if (local_output->buffer == NULL)
    {
        /* Since we dealt with the zero-length case above, we know that
         * a NULL return value means a failure of allocation. */
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
    local_output->length   = output_len;
    local_output->original = output;

    return PSA_SUCCESS;
}

psa_status_t psa_crypto_local_output_free(psa_crypto_local_output_t *local_output)
{
    psa_status_t status;

    if (local_output->buffer == NULL)
    {
        local_output->length = 0;
        return PSA_SUCCESS;
    }
    if (local_output->original == NULL)
    {
        /* We have an internal copy but nothing to copy back to. */
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    status = psa_crypto_copy_output(local_output->buffer,
                                    local_output->length,
                                    local_output->original,
                                    local_output->length);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    mbedtls_zeroize_and_free(local_output->buffer, local_output->length);
    local_output->buffer = NULL;
    local_output->length = 0;

    return PSA_SUCCESS;
}
    #endif /* TI_SW_CRYPTO_ENABLED == 1 */
#endif     /* ifndef TFM_BUILD */