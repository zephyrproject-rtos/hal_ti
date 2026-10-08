/*
 * Copyright (c) 2024-2026 Texas Instruments Incorporated
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

#include <stdint.h>
#include <stdbool.h>

/* Top-level and device-specific includes */
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/ECDH.h>
#include <ti/drivers/ecdh/ECDHXXF3HSM.h>
#include <ti/drivers/cryptoutils/ecc/ECCParams.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKeyPlaintext.h>
#include <ti/drivers/cryptoutils/utils/CryptoUtils.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>

/* HSM-related includes */
#include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
#include <ti/drivers/cryptoutils/hsm/HSMXXF3Utility.h>
#include <third_party/hsmddk/include/Integration/HSMSAL/HSMSAL.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_asset_policy.h>
#include <third_party/hsmddk/include/Kit/EIP130/DomainHelper/incl/eip130_domain_ecc_curves.h>

/* RTOS-related includes */
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/DebugP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    #include <ti/drivers/xmem/XMEMWFF3.h>
    /* HSM Register names for CC35XX are different compared to CC27XX
     * Below mapping helps to keep the source code same between
     * both devices.
     */
    #define INT_HSM_SEC_IRQ INT_OSPR_HSM_HOST_0_SEC_IRQ
#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) */

/* KeyStore-related includes */
#if (ENABLE_KEY_STORAGE == 1)
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>

    /* Note that this size is in terms of the HSM sub-vector format, which is how KeyStore will
     * return the key material to the driver. The 521-bit curve length must be converted to a word boundary,
     * multiplied by number of bytes per word, and added by 4 bytes for the additional header word per component.
     */
    #define ECDHXXF3HSM_MAX_PRIVATE_KEY_SIZE \
        ((HSM_WORD_LENGTH * ((ECDH_CURVE_LENGTH_521 + 31) / 32)) + HSM_ASYM_DATA_VHEADER)
#endif

/* Helper functions */
static int_fast16_t ECDHXXF3HSM_initializeHSMOperations(ECDH_Handle handle);
static int_fast16_t ECDHXXF3HSM_setECCurveParameters(ECDHXXF3HSM_Object *object);
static int_fast16_t ECDHXXF3HSM_validateKeys(ECDHXXF3HSM_Object *object);

static int_fast16_t ECDHXXF3HSM_createAndLoadAllAssets(ECDH_Handle handle);

static int_fast16_t ECDHXXF3HSM_createAndLoadPrivateKeyAssetID(ECDH_Handle handle);
static int_fast16_t ECDHXXF3HSM_createPrivateKeyAsset(ECDH_Handle handle);
static int_fast16_t ECDHXXF3HSM_LoadPrivateKeyAsset(ECDH_Handle handle, uint8_t *key, bool isFromKeyStore);

static int_fast16_t ECDHXXF3HSM_createAndLoadPublicKeyAssetID(ECDH_Handle handle);
static int_fast16_t ECDHXXF3HSM_createPublicKeyAsset(ECDH_Handle handle);
static int_fast16_t ECDHXXF3HSM_LoadPublicKeyAsset(ECDH_Handle handle);

static int_fast16_t ECDHXXF3HSM_createPublicDataAsset(ECDH_Handle handle);

static int_fast16_t ECDHXXF3HSM_createAndLoadECurveAssetID(ECDH_Handle handle);
static int_fast16_t ECDHXXF3HSM_createECurveAsset(ECDH_Handle handle);
static int_fast16_t ECDHXXF3HSM_LoadECurve(ECDH_Handle handle);

static int_fast16_t ECDHXXF3HSM_freeAssetID(ECDH_Handle handle, uint32_t AssetID);
static int_fast16_t ECDHXXF3HSM_freeAllAssets(ECDH_Handle handle);

/*
 *  ======== ECDH_init ========
 */
void ECDH_init(void)
{
    HSMXXF3_constructRTOSObjects();
}

/*
 *  ======== ECDH_Params_init ========
 */
void ECDH_Params_init(ECDH_Params *params)
{
    *params = ECDH_defaultParams;
}

/*
 *  ======== ECDH_construct ========
 */
ECDH_Handle ECDH_construct(ECDH_Config *config, const ECDH_Params *params)
{
    ECDH_Handle handle         = NULL;
    ECDHXXF3HSM_Object *object = config->object;
    uint_fast8_t key;

    /* Initialize and boot HSM and related FW architectures */
    if (HSMXXF3_init() != HSMXXF3_STATUS_SUCCESS)
    {
        /* Upon HSM Boot failure, this driver stores the failure status in the object */
        object->hsmStatus = HSMXXF3_STATUS_ERROR;

        return NULL;
    }
    else
    {
        object->hsmStatus = HSMXXF3_STATUS_SUCCESS;
    }

    /* If params are NULL, use defaults */
    if (params == NULL)
    {
        params = (ECDH_Params *)&ECDH_defaultParams;
    }

    key = HwiP_disable();

    if (object->isOpen)
    {
        HwiP_restore(key);
        return NULL;
    }
    else
    {
        object->isOpen = true;

        HwiP_restore(key);

        object->returnBehavior    = params->returnBehavior;
        object->callbackFxn       = params->callbackFxn;
        object->accessTimeout     = params->returnBehavior == ECDH_RETURN_BEHAVIOR_BLOCKING ? params->timeout
                                                                                            : SemaphoreP_NO_WAIT;
        object->returnStatus      = ECDH_STATUS_SUCCESS;
        object->privateKeyAssetID = 0U;
        object->paramAssetID      = 0U;
        object->publicKeyAssetID  = 0U;
        object->publicDataAssetID = 0U;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        if (XMEMWFF3_isAddrExternal((uintptr_t)object))
        {
            /* Callback mode is not supported when the ECDH object is in external
             * memory because the object contains the output buffer used by the HSM.
             */
            if (object->returnBehavior == ECDH_RETURN_BEHAVIOR_CALLBACK)
            {
                object->isOpen = false;
                return NULL;
            }

            /* The input and output bounce buffers must each be large enough to
             * hold the ECDH component vector (P-521 worst case: 144 bytes).
             * object->output[] is used as scratch for key material staged via
             * stageInput before loading into HSM assets, and as the HSM output
             * destination staged via stageOutput for the generate-public-key result.
             */
            if (HSMXXF3_inputBounce.size < ECDH_COMPONENT_VECTOR_LENGTH ||
                HSMXXF3_outputBounce.size < ECDH_COMPONENT_VECTOR_LENGTH)
            {
                object->isOpen = false;
                return NULL;
            }
        }
#endif

        handle = (ECDH_Handle)config;
    }

    return handle;
}

/*
 *  ======== ECDH_close ========
 */
void ECDH_close(ECDH_Handle handle)
{
    ECDHXXF3HSM_Object *object = handle->object;

    /* In the case of callback, we need to check whether there is an operation in progress.
     * If so, HSMXXF3_cancelOperation() API will take care of canceling the operation and
     * setting the HSM back to a ready state.
     */
    if (object->returnBehavior == ECDH_RETURN_BEHAVIOR_CALLBACK)
    {
        /* Since the HSM cannot cancel an in-progress token, we must wait for the result to allow for
         * subsequent token submissions to succeed.
         */
        (void)HSMXXF3_cancelOperation();
    }

    object->isOpen = false;
}

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
/* BLE stack leverages ECCParams_CurveParams, therefore, we cannot get rid of it. However, for CC35XX devices, we can
 * just rely on the curveType member in the operation struct.
 */
/*
 *  ======== ECDHXXF3HSM_compareCurves ========
 */
static int_fast16_t ECDHXXF3HSM_compareCurves(ECCParams_CurveParams *providedCurve, ECCParams_CurveParams *storedCurve)
{
    if (providedCurve->curveType != storedCurve->curveType)
    {
        return ECDH_STATUS_ERROR;
    }

    if (providedCurve->length != storedCurve->length)
    {
        return ECDH_STATUS_ERROR;
    }

    if (!CryptoUtils_buffersMatch(providedCurve->prime, storedCurve->prime, providedCurve->length))
    {
        return ECDH_STATUS_ERROR;
    }

    if (!CryptoUtils_buffersMatch(providedCurve->order, storedCurve->order, providedCurve->length))
    {
        return ECDH_STATUS_ERROR;
    }

    return ECDH_STATUS_SUCCESS;
}

/*
 *  ======== ECDHXXF3HSM_getECCCurveTypeByCurve ========
 */
static int_fast16_t ECDHXXF3HSM_getECCCurveTypeByCurve(ECDHXXF3HSM_Object *object)
{
    int_fast16_t status = ECDH_STATUS_ERROR;
    ECCParams_CurveParams *curve;

    if (object->operationType == ECDH_OPERATION_TYPE_GENERATE_PUBLIC_KEY)
    {
        ECDH_OperationGeneratePublicKey *operation = (ECDH_OperationGeneratePublicKey *)(object->operation);
        curve                                      = (ECCParams_CurveParams *)operation->curve;
    }
    else if (object->operationType == ECDH_OPERATION_TYPE_COMPUTE_SHARED_SECRET)
    {
        ECDH_OperationComputeSharedSecret *operation = (ECDH_OperationComputeSharedSecret *)(object->operation);
        curve                                        = (ECCParams_CurveParams *)operation->curve;
    }
    else
    {
        return ECDH_STATUS_ERROR;
    }

    if (curve == NULL)
    {
        /* curve is null, return an error. */
        return ECDH_STATUS_ERROR;
    }

    /* Initialize critical ECDH driver metadata:
     * - curve length: (224, 256, 384, 512, or 521 bits)
     * - digest length: (224, 256, 384, or 512 bits)
     * - curve family and domain ID: (NIST or BrainPool)
     */
    if (ECDHXXF3HSM_compareCurves(curve, (ECCParams_CurveParams *)&ECCParams_NISTP224) == ECDH_STATUS_SUCCESS)
    {
        object->curveLength = ECDH_CURVE_LENGTH_224;
        object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        object->curveType   = ECDH_TYPE_SEC_P_224_R1;
    }
    else if (ECDHXXF3HSM_compareCurves(curve, (ECCParams_CurveParams *)&ECCParams_NISTP256) == ECDH_STATUS_SUCCESS)
    {
        object->curveLength = ECDH_CURVE_LENGTH_256;
        object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        object->curveType   = ECDH_TYPE_SEC_P_256_R1;
    }
    else if (ECDHXXF3HSM_compareCurves(curve, (ECCParams_CurveParams *)&ECCParams_NISTP384) == ECDH_STATUS_SUCCESS)
    {
        object->curveLength = ECDH_CURVE_LENGTH_384;
        object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        object->curveType   = ECDH_TYPE_SEC_P_384_R1;
    }
    else if (ECDHXXF3HSM_compareCurves(curve, (ECCParams_CurveParams *)&ECCParams_NISTP521) == ECDH_STATUS_SUCCESS)
    {
        object->curveLength = ECDH_CURVE_LENGTH_521;
        object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        object->curveType   = ECDH_TYPE_SEC_P_521_R1;
    }
    else if (ECDHXXF3HSM_compareCurves(curve, (ECCParams_CurveParams *)&ECCParams_BrainpoolP256R1) ==
             ECDH_STATUS_SUCCESS)
    {
        object->curveLength = ECDH_CURVE_LENGTH_256;
        object->curveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
        object->curveType   = ECDH_TYPE_BRP_P_256_R1;
        object->domainId    = ECDH_DOMAIN_ID_BRP;
    }
    else if (ECDHXXF3HSM_compareCurves(curve, (ECCParams_CurveParams *)&ECCParams_BrainpoolP384R1) ==
             ECDH_STATUS_SUCCESS)
    {
        object->curveLength = ECDH_CURVE_LENGTH_384;
        object->curveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
        object->curveType   = ECDH_TYPE_BRP_P_384_R1;
        object->domainId    = ECDH_DOMAIN_ID_BRP;
    }
    else if (ECDHXXF3HSM_compareCurves(curve, (ECCParams_CurveParams *)&ECCParams_BrainpoolP512R1) ==
             ECDH_STATUS_SUCCESS)
    {
        object->curveLength = ECDH_CURVE_LENGTH_512;
        object->curveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
        object->curveType   = ECDH_TYPE_BRP_P_512_R1;
        object->domainId    = ECDH_DOMAIN_ID_BRP;
    }
    else if (ECDHXXF3HSM_compareCurves(curve, (ECCParams_CurveParams *)&ECCParams_Curve25519) == ECDH_STATUS_SUCCESS)
    {
        object->curveLength = ECDH_CURVE_LENGTH_255;
        object->curveFamily = EIP130DOMAIN_ECC_FAMILY_MONTGOMERY;
        object->curveType   = ECDH_TYPE_CURVE_25519;
    }

    if (object->curveFamily != EIP130DOMAIN_ECC_FAMILY_NONE)
    {
        status = ECDH_STATUS_SUCCESS;
    }

    return status;
}
#endif

/*
 *  ======== ECDHXXF3HSM_getECCCurveTypeByValue ========
 */
static int_fast16_t ECDHXXF3HSM_getECCCurveTypeByValue(ECDHXXF3HSM_Object *object)
{
    int_fast16_t status = ECDH_STATUS_ERROR;

    /* Initialize critical ECDH driver metadata:
     * - curve length: (224, 256, 384, 512, or 521 bits)
     * - digest length: (224, 256, 384, or 512 bits)
     * - curve family and domain ID: (NIST or BrainPool)
     */
    switch (object->curveType)
    {
        case ECDH_TYPE_SEC_P_224_R1:
            object->curveLength = ECDH_CURVE_LENGTH_224;
            object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
            break;
        case ECDH_TYPE_BRP_P_256_R1:
        case ECDH_TYPE_SEC_P_256_R1:
            object->curveLength = ECDH_CURVE_LENGTH_256;
            if (object->curveType == ECDH_TYPE_SEC_P_256_R1)
            {
                object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
            }
            else
            {
                object->curveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
                object->domainId    = ECDH_DOMAIN_ID_BRP;
            }
            break;
        case ECDH_TYPE_BRP_P_384_R1:
        case ECDH_TYPE_SEC_P_384_R1:
            object->curveLength = ECDH_CURVE_LENGTH_384;
            if (object->curveType == ECDH_TYPE_SEC_P_384_R1)
            {
                object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
            }
            else
            {
                object->curveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
                object->domainId    = ECDH_DOMAIN_ID_BRP;
            }
            break;
        case ECDH_TYPE_BRP_P_512_R1:
            object->curveLength = ECDH_CURVE_LENGTH_512;
            object->curveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
            object->domainId    = ECDH_DOMAIN_ID_BRP;
            break;
        case ECDH_TYPE_SEC_P_521_R1:
            object->curveLength = ECDH_CURVE_LENGTH_521;
            object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
            break;
        case ECDH_TYPE_CURVE_25519:
            object->curveLength = ECDH_CURVE_LENGTH_255;
            object->curveFamily = EIP130DOMAIN_ECC_FAMILY_MONTGOMERY;
            break;
        default:
            /* Invalid CurveType. Set object->curveFamily to NONE and return an error.
             * A valid CurveType that is supported by the ECDH driver should be
             * provided in order to perform a public key or a shared secret
             * operation.
             */
            object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NONE;
            break;
    }

    if (object->curveFamily != EIP130DOMAIN_ECC_FAMILY_NONE)
    {
        status = ECDH_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_setECCurveParameters ========
 */
static int_fast16_t ECDHXXF3HSM_setECCurveParameters(ECDHXXF3HSM_Object *object)
{
    int_fast16_t status = ECDH_STATUS_ERROR;
    object->curveFamily = EIP130DOMAIN_ECC_FAMILY_NONE;
    object->domainId    = ECDH_DOMAIN_ID_SEC;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    /* Try obtaining ECC curve type by parsing through a valid curve object */
    if (ECDHXXF3HSM_getECCCurveTypeByCurve(object) != ECDH_STATUS_SUCCESS)
    {
#endif
        /* If a valid curve object does not exist (junk data or null), then read the operation's curveType value */
        if (ECDHXXF3HSM_getECCCurveTypeByValue(object) != ECDH_STATUS_SUCCESS)
        {
            /* If the operation's curveType value is invalid, then return an error */
            return ECDHXXF3HSM_STATUS_NO_VALID_CURVE_TYPE_PROVIDED;
        }
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    }
#endif

    /* Retrieve and store the location of the appropriate curve parameters for later use.
     * These curve parameters will be loaded into the HSM IP as an asset holding the values
     * that will be later used to perform a public key or a shared secret operation.
     */
    if (Eip130Domain_ECC_GetCurve(object->curveFamily,
                                  object->curveLength,
                                  &object->curveParam,
                                  &object->curveParamSize))
    {
        status = ECDH_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_validateKeys ========
 */
static int_fast16_t ECDHXXF3HSM_validateKeys(ECDHXXF3HSM_Object *object)
{
    uint32_t privateKeyLength = 0;
    /* Checking the encoding for the private key.
     * This key might carry four different types of encodings.
     * Though all ECDH operations on CC27XX target the HSM, the non-HSM
     * encoding equivalents will be accepted, if using plaintext.
     */
    if ((object->privateKey->encoding != CryptoKey_PLAINTEXT) &&
        (object->privateKey->encoding != CryptoKey_PLAINTEXT_HSM))
    {
#if (ENABLE_KEY_STORAGE == 1)
        if (object->privateKey->encoding != CryptoKey_KEYSTORE_HSM)
        {
            return ECDHXXF3HSM_STATUS_INVALID_PRIVATE_KEY_ENCODING;
        }
#else
        return ECDHXXF3HSM_STATUS_INVALID_PRIVATE_KEY_ENCODING;
#endif
    }

    /* Checking for the encoding for the public key.
     * In the case of a generate public key operation, the key will hold _BLANK_ encoding.
     * In the case of a generate shared secret operation, the key will not.
     */
    if (object->operationType == ECDH_OPERATION_TYPE_GENERATE_PUBLIC_KEY)
    {
        if ((object->publicKey->encoding != CryptoKey_BLANK_PLAINTEXT) &&
            (object->publicKey->encoding != CryptoKey_BLANK_PLAINTEXT_HSM))
        {
            return ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_ENCODING;
        }
    }
    else
    {
        if ((object->publicKey->encoding != CryptoKey_PLAINTEXT) &&
            (object->publicKey->encoding != CryptoKey_PLAINTEXT_HSM))
        {
            return ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_ENCODING;
        }

        /* In the case of a generate shared secret operation, the ECDH driver checks against all known permutations */
        if ((object->sharedSecret->encoding != CryptoKey_BLANK_PLAINTEXT) &&
            (object->sharedSecret->encoding != CryptoKey_BLANK_PLAINTEXT_HSM))
        {
            return ECDHXXF3HSM_STATUS_INVALID_SHARED_SECRET_KEY_ENCODING;
        }
    }

    /* One of the following two conditions is guaranteed due to the encoding validation above */
    if ((object->privateKey->encoding & CRYPTOKEY_KEYSTORE) == 0)
    {
        privateKeyLength = object->privateKey->u.plaintext.keyLength;
    }
#if (ENABLE_KEY_STORAGE == 1)
    else
    {
        privateKeyLength = object->privateKey->u.keyStore.keyLength;
    }
#endif

    /* Check private key length. It should match the curve length after conversion. */
    if (privateKeyLength != BITS_TO_BYTES(object->curveLength))
    {
        return ECDHXXF3HSM_STATUS_INVALID_PRIVATE_KEY_SIZE;
    }

    if (object->keyMaterialEndianness == ECDH_BIG_ENDIAN_KEY)
    {
        /* For big endian, the formatting is the same no matter what the curve type is.
         * The format for uncompressed big endian, it is 1 + (BITS_TO_BYTES(object->curveLength) * 2).
         */
        if (object->publicKey->u.plaintext.keyLength !=
            ((BITS_TO_BYTES(object->curveLength) * HSM_ASYM_ECC_PUB_KEY_VCOUNT) + HSM_ASYM_ECC_PUB_KEY_UNCOMP_ENC_LENG))
        {
            return ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_SIZE;
        }

        /* For shared secret operations in big endian format,
         * the HSM_ASYM_ECC_PUB_KEY_UNCOMP_ENC_LENG mentioned above is the octet formatting string for the public key
         * indicating what the public key contains:
         * - Value 0x04 means that it is a uncompressed public key with X and Y components.
         */
        if ((object->operationType == ECDH_OPERATION_TYPE_COMPUTE_SHARED_SECRET) &&
            (object->publicKey->u.plaintext.keyMaterial[0] != HSM_ASYM_ECC_UNCOMP_ENC_VALUE))
        {
            return ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_OCTET_VALUE;
        }
    }
    else
    {
        /* For little endian, the formatting differs depending on the curve type.
         * The format for little endian is either one of the following:
         *  - (BITS_TO_BYTES(object->curveLength) * 2).
         *  - BITS_TO_BYTES(object->curveLength).
         */
        if (object->curveType == ECDH_TYPE_CURVE_25519)
        {
            if (object->publicKey->u.plaintext.keyLength != BITS_TO_BYTES(object->curveLength))
            {
                return ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_SIZE;
            }
        }
        else
        {
            if (object->publicKey->u.plaintext.keyLength !=
                (BITS_TO_BYTES(object->curveLength) * HSM_ASYM_ECC_PUB_KEY_VCOUNT))
            {
                return ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_SIZE;
            }
        }
    }

    if (object->operationType == ECDH_OPERATION_TYPE_COMPUTE_SHARED_SECRET)
    {
        /* We cannot guarantee what the user will pass in as a key length for the shared secret so we check against the
         * known permutations.
         */
        if ((object->sharedSecret->u.plaintext.keyLength != BITS_TO_BYTES(object->curveLength)) &&
            (object->sharedSecret->u.plaintext.keyLength !=
             (BITS_TO_BYTES(object->curveLength) * HSM_ASYM_ECC_PUB_KEY_VCOUNT)) &&
            (object->sharedSecret->u.plaintext.keyLength !=
             (BITS_TO_BYTES(object->curveLength) * HSM_ASYM_ECC_PUB_KEY_VCOUNT + 1)))
        {
            return ECDHXXF3HSM_STATUS_INVALID_SHARED_SECRET_KEY_SIZE;
        }
    }

    /* Zeroize the output buffers. */
    if (object->operationType == ECDH_OPERATION_TYPE_GENERATE_PUBLIC_KEY)
    {
        (void)memset(&object->publicKey->u.plaintext.keyMaterial[0], 0, object->publicKey->u.plaintext.keyLength);
    }
    else
    {
        (void)memset(&object->sharedSecret->u.plaintext.keyMaterial[0], 0, object->sharedSecret->u.plaintext.keyLength);
    }

    /* Zeroize the output buffer. */
    (void)memset(&object->output[0], 0, ECDH_COMPONENT_VECTOR_LENGTH);

    return ECDH_STATUS_SUCCESS;
}

/*
 *  ======== ECDHXXF3HSM_checkECCKeysPostProcessing ========
 */
static inline void ECDHXXF3HSM_checkECCKeysPostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDHXXF3HSM_STATUS_INVALID_ECC_KEYS;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    /* TokenResult carries information regarding the operation result status as well as other information such as
     * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
     * relevant information to an operation's result status.
     */
    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = ECDH_STATUS_SUCCESS;
    }

    object->hsmStatus = status;
}

/*
 *  ======== ECDHXXF3HSM_checkECCKeys ========
 */
static int_fast16_t ECDHXXF3HSM_checkECCKeys(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;

    /* Populates the HSMXXF3 commandToken as a check ECC keys token */
    HSMXXF3_constructECDHVerifyKeysPhysicalToken(object);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_checkECCKeysPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_initializeHSMOperations ========
 */
static int_fast16_t ECDHXXF3HSM_initializeHSMOperations(ECDH_Handle handle)
{
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_SUCCESS;

    /* Check if HSMXXF3 initialization (boot up sequence or SW architecture) has failed.
     * If so, return the appropriate code.
     */
    if (object->hsmStatus == HSMXXF3_STATUS_ERROR)
    {
        return ECDHXXF3HSM_STATUS_HARDWARE_ERROR;
    }

    /* Initializes critical ECDH driver metadata and retrieves and stores ECC curve parameters in the object */
    status = ECDHXXF3HSM_setECCurveParameters(object);

    if (status != ECDH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Validate encodings and key length for private, public, and shared secret CryptoKeys */
    status = ECDHXXF3HSM_validateKeys(object);

    if (status != ECDH_STATUS_SUCCESS)
    {
        return status;
    }

    if (!HSMXXF3_acquireLock(object->accessTimeout, (uintptr_t)handle))
    {
        return ECDH_STATUS_RESOURCE_UNAVAILABLE;
    }

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
    if (!CommonResourceXXF3_acquireLock(object->accessTimeout))
    {
        HSMXXF3_releaseLock();

        return ECDH_STATUS_RESOURCE_UNAVAILABLE;
    }

    /* Create and load assets necessary to conduct the operation:
     * - Private key, for both types of operations.
     * - Public key, for both types of operations.
     * - Public data object, for shared secret operations only.
     * - ECC curve parameters, for both types of operations.
     */
    status = ECDHXXF3HSM_createAndLoadAllAssets(handle);

    if (HSMXXF3_isStandaloneDMASupportEnabled() || (status != ECDH_STATUS_SUCCESS))
    {
        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();
    }

    if ((status == ECDH_STATUS_SUCCESS) && (object->curveType != ECDH_TYPE_CURVE_25519))
    {
        status = ECDHXXF3HSM_checkECCKeys(handle);
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_readPublicKeyMaterial ========
 */
static int_fast16_t ECDHXXF3HSM_readPublicKeyMaterial(ECDH_Handle handle)
{
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    uint32_t assetSize         = HSM_ASYM_DATA_SIZE_VWB(object->curveLength);
    uint8_t itemCount          = HSM_ASYM_ECC_PUB_KEY_VCOUNT;
    int32_t tokenResult        = 0U;

    /* Public key for curve25519 is comprised of only one component, pubkey.u.
     * For shared secret operations, if the user provides in big endian
     * more than one component, the ECDH driver only takes the first one.
     */
    if (object->curveType != ECDH_TYPE_CURVE_25519)
    {
        assetSize *= HSM_ASYM_ECC_PUB_KEY_VCOUNT;
    }
    else
    {
        /* Public key for curve25519 is composed of only one component, pubkey.u.
         * For other curves, the public key has two components, pubkey.x and pubkey.y.
         */
        itemCount = HSM_ASYM_CURVE25519_PUB_KEY_VCOUNT;
    }

    /* Initialize a buffer that will hold the single- or multi-component vector for the operation's key */
    (void)memset(&object->output[0], 0, assetSize);

    HSMXXF3_getPublicDataRead(object->publicDataAssetID, &object->output[0], assetSize);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            tokenResult = HSMXXF3_getResultCode();

            if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
            {
                status = ECDH_STATUS_SUCCESS;

                HSMXXF3_asymDHPubKeyFromHW(&object->output[0],
                                           object->curveLength,
                                           itemCount,
                                           (HSMXXF3_KeyMaterialEndianness)object->keyMaterialEndianness,
                                           object->publicKey->u.plaintext.keyMaterial);
            }
        }
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_readSharedSecret ========
 */
static int_fast16_t ECDHXXF3HSM_readSharedSecret(ECDH_Handle handle)
{
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    int32_t tokenResult        = 0U;
    uint8_t *key;

    /* Initialize a buffer that will hold the single- or multi-component vector for the operation's key */
    (void)memset(&object->output[0], 0, ECDH_COMPONENT_VECTOR_LENGTH);

    HSMXXF3_getPublicDataRead(object->publicDataAssetID,
                              &object->output[0],
                              HSM_ASYM_DATA_SIZE_B2WB(object->curveLength));

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            tokenResult = HSMXXF3_getResultCode();

            if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
            {
                status = ECDH_STATUS_SUCCESS;

                key = object->sharedSecret->u.plaintext.keyMaterial;

                /* The HSM stores the shared secret in the public data object in Big Endian format. */
                if (object->keyMaterialEndianness == ECDH_BIG_ENDIAN_KEY)
                {
                    /* First byte in big endian should always be 0x04 indicating that it is an uncompressed value */
                    object->sharedSecret->u.plaintext.keyMaterial[0] = HSM_ASYM_ECC_SRD_SCRT_ENC_VALUE;
                    key                                              = key + HSM_ASYM_ECC_PUB_KEY_UNCOMP_ENC_LENG;

                    memcpy(key, &object->output[0], BITS_TO_BYTES(object->curveLength));
                }
                else
                {
                    /* Reverse the Big Endian formatting to Little Endian. */
                    HSMXXF3_reverseMemCpy(key, &object->output[0], BITS_TO_BYTES(object->curveLength));
                }
            }
        }
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_ecdhCommonPostProcessing ========
 */
static void ECDHXXF3HSM_ecdhCommonPostProcessing(uintptr_t arg0, int_fast16_t status)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t assetStatus   = ECDH_STATUS_ERROR;

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    /* Free assets (private key and ECC curve assets) */
    assetStatus = ECDHXXF3HSM_freeAllAssets(handle);

    if (assetStatus != ECDH_STATUS_SUCCESS)
    {
        status = assetStatus;
    }

    object->returnStatus = status;

    HSMXXF3_releaseLock();

    if (object->returnBehavior == ECDH_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn((ECDH_Handle)arg0, status, *object->operation, object->operationType);
    }
}

/*
 *  ======== ECDHXXF3HSM_ecdhPostProcessing ========
 */
static inline void ECDHXXF3HSM_ecdhPostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();
    bool commonResourceRetval  = false;

    if (HSMXXF3_isStandaloneDMASupportEnabled())
    {
        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
        if ((object->returnBehavior == ECDH_RETURN_BEHAVIOR_BLOCKING) ||
            (object->returnBehavior == ECDH_RETURN_BEHAVIOR_POLLING))
        {
            /* The ECDH driver will opt to wait forever when called synchronously. */
            commonResourceRetval = CommonResourceXXF3_acquireLock(SemaphoreP_WAIT_FOREVER);
        }
        else
        {
            /* The ECDH driver will opt to attempt to acquire the lock with not wait when called asynchronously.
             * If the ECDH driver was not able to obtain the semaphore from first try, CommonResource will return a an
             * error and internally track when the entity that holds the semaphore releases it so that it can fire up
             * the HSM ISR immediatley after.
             */
            commonResourceRetval = CommonResourceXXF3_acquireLockWithDelay();
        }

        /* Execute the DMA-dependent operations only when the CommonResource semaphore has been acquired. */
        if (commonResourceRetval)
        {
            /* TokenResult carries information regarding the operation result status as well as other information such
             * as whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to
             * extract only relevant information to an operation's result status.
             */
            if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
            {
                if (object->operationType == ECDH_OPERATION_TYPE_GENERATE_PUBLIC_KEY)
                {
                    status = ECDHXXF3HSM_readPublicKeyMaterial(handle);

                    if (status == ECDH_STATUS_SUCCESS)
                    {
                        if (object->publicKey->encoding == CryptoKey_BLANK_PLAINTEXT)
                        {
                            object->publicKey->encoding = CryptoKey_PLAINTEXT;
                        }
                        else
                        {
                            object->publicKey->encoding = CryptoKey_PLAINTEXT_HSM;
                        }
                    }
                }
                else
                {
                    status = ECDHXXF3HSM_readSharedSecret(handle);

                    if (status == ECDH_STATUS_SUCCESS)
                    {
                        object->sharedSecret->encoding = (object->sharedSecret->encoding == CryptoKey_BLANK_PLAINTEXT)
                                                             ? CryptoKey_PLAINTEXT
                                                             : CryptoKey_PLAINTEXT_HSM;
                    }
                }
            }

            /* Execute the common phase in the post processing part:
             * - Free all created assets.
             * - Release the HSM access semaphore.
             * - When in Callback mode, call the user's callbck fxn.
             */
            ECDHXXF3HSM_ecdhCommonPostProcessing(arg0, status);
        }
        else
        {
            (void)HwiP_enableInterrupt(INT_HSM_SEC_IRQ);
        }
    }
    else
    {
        /* TokenResult carries information regarding the operation result status as well as other information such as
         * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
         * relevant information to an operation's result status.
         */
        if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
        {
            if (object->operationType == ECDH_OPERATION_TYPE_GENERATE_PUBLIC_KEY)
            {
                uint8_t itemCount = HSM_ASYM_ECC_PUB_KEY_VCOUNT;

                /* Public key for curve25519 is composed of only one component, pubkey.u.
                 * For other curves, the public key has two components, pubkey.x and pubkey.y.
                 */
                if (object->curveType == ECDH_TYPE_CURVE_25519)
                {
                    itemCount = HSM_ASYM_CURVE25519_PUB_KEY_VCOUNT;
                }

                HSMXXF3_asymDHPubKeyFromHW(&object->output[0],
                                           object->curveLength,
                                           itemCount,
                                           (HSMXXF3_KeyMaterialEndianness)object->keyMaterialEndianness,
                                           object->publicKey->u.plaintext.keyMaterial);

                if (object->publicKey->encoding == CryptoKey_BLANK_PLAINTEXT)
                {
                    object->publicKey->encoding = CryptoKey_PLAINTEXT;
                }
                else
                {
                    object->publicKey->encoding = CryptoKey_PLAINTEXT_HSM;
                }

                status = ECDH_STATUS_SUCCESS;
            }
            else
            {
                status = ECDHXXF3HSM_readSharedSecret(handle);

                if (status == ECDH_STATUS_SUCCESS)
                {
                    object->sharedSecret->encoding = (object->sharedSecret->encoding == CryptoKey_BLANK_PLAINTEXT)
                                                         ? CryptoKey_PLAINTEXT
                                                         : CryptoKey_PLAINTEXT_HSM;
                }
            }
        }

        /* Execute the common phase in the post processing part:
         * - Free all created assets.
         * - Release the HSM access semaphore.
         * - When in Callback mode, call the user's callbck fxn.
         */
        ECDHXXF3HSM_ecdhCommonPostProcessing(arg0, status);
    }
}

/*
 *  ======== ECDH_generatePublicKey ========
 */
int_fast16_t ECDH_generatePublicKey(ECDH_Handle handle, ECDH_OperationGeneratePublicKey *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    ECDHXXF3HSM_Object *object    = handle->object;
    int_fast16_t status           = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval        = HSMXXF3_STATUS_ERROR;
    object->privateKey            = operation->myPrivateKey;
    object->publicKey             = (CryptoKey *)operation->myPublicKey;
    object->curveType             = operation->curveType;
    object->operationType         = ECDH_OPERATION_TYPE_GENERATE_PUBLIC_KEY;
    object->keyMaterialEndianness = operation->keyMaterialEndianness;
    object->operation             = (ECDH_Operation *)operation;
    object->returnStatus          = ECDH_STATUS_SUCCESS;

    /* Initialize assets as unallocated so that a cleanup operation
     * doesn't attempt to free an asset that doesn't exist yet.
     */
    object->privateKeyAssetID = 0U;
    object->paramAssetID      = 0U;
    object->publicKeyAssetID  = 0U;
    object->publicDataAssetID = 0U;

    /* Perform the following operations:
     * - Check the HSM HW status
     * - Setup up Driver metadata and EC curve parameters
     * - Attempt to acquire access semaphore for HSM operations.
     * - Verify private and/or public keys.
     * - Create assets for the operation's keys and EC parameters
     */
    status = ECDHXXF3HSM_initializeHSMOperations(handle);

    if (status != ECDH_STATUS_SUCCESS)
    {
        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        /* In the case of failure to initialize the operation, we need to free all assets allocated
         * Capturing the return status of this operation is pointless since we are retuning an
         * error code anyways.
         */
        (void)ECDHXXF3HSM_freeAllAssets(handle);

        HSMXXF3_releaseLock();

        return status;
    }

    /* Populates the HSMXXF3 commandToken as a PK token for an ECDH generate public key operation */
    HSMXXF3_constructECDHGenPubPhysicalToken(object);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->returnBehavior,
                                    ECDHXXF3HSM_ecdhPostProcessing,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
    }

    if (hsmRetval != HSMXXF3_STATUS_SUCCESS)
    {
        status = ECDH_STATUS_ERROR;

        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        /* Free All allocated assets.
         * Ignore the return value here since the driver status code is error.
         */
        (void)ECDHXXF3HSM_freeAllAssets(handle);

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== ECDH_computeSharedSecret ========
 */
int_fast16_t ECDH_computeSharedSecret(ECDH_Handle handle, ECDH_OperationComputeSharedSecret *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    ECDHXXF3HSM_Object *object    = handle->object;
    int_fast16_t status           = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval        = HSMXXF3_STATUS_ERROR;
    object->privateKey            = operation->myPrivateKey;
    object->publicKey             = (CryptoKey *)operation->theirPublicKey;
    object->sharedSecret          = (CryptoKey *)operation->sharedSecret;
    object->curveType             = operation->curveType;
    object->operationType         = ECDH_OPERATION_TYPE_COMPUTE_SHARED_SECRET;
    object->keyMaterialEndianness = operation->keyMaterialEndianness;
    object->operation             = (ECDH_Operation *)operation;
    object->returnStatus          = ECDH_STATUS_SUCCESS;

    /* Initialize assets as unallocated so that a cleanup operation
     * doesn't attempt to free an asset that doesn't exist yet.
     */
    object->privateKeyAssetID = 0U;
    object->paramAssetID      = 0U;
    object->publicKeyAssetID  = 0U;
    object->publicDataAssetID = 0U;

    /* Perform the following operations:
     * - Check the HSM HW status
     * - Setup up Driver metadata and EC curve parameters
     * - Attempt to acquire access semaphore for HSM operations.
     * - Verify private and/or public keys.
     * - Create assets for the operation's keys and EC parameters
     */
    status = ECDHXXF3HSM_initializeHSMOperations(handle);

    if (status != ECDH_STATUS_SUCCESS)
    {
        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        /* In the case of failure to initialize the operation, we need to free all assets allocated
         * Capturing the return status of this operation is pointless since we are retuning an
         * error code anyways.
         */
        (void)ECDHXXF3HSM_freeAllAssets(handle);

        HSMXXF3_releaseLock();

        return status;
    }

    /* Populates the HSMXXF3 commandToken as a PK token for an ECDH generate public key operation */
    HSMXXF3_constructECDHGenShrdSecPhysicalToken(object);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->returnBehavior,
                                    ECDHXXF3HSM_ecdhPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
    }

    if (hsmRetval != HSMXXF3_STATUS_SUCCESS)
    {
        status = ECDH_STATUS_ERROR;

        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        /* Free All allocated assets.
         * Ignore the return value here since the driver status code is error.
         */
        (void)ECDHXXF3HSM_freeAllAssets(handle);

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== ECDH_cancelOperation ========
 */
int_fast16_t ECDH_cancelOperation(ECDH_Handle handle)
{
    ECDHXXF3HSM_Object *object = handle->object;

    object->returnStatus = ECDH_STATUS_CANCELED;

    /* In the case of callback, we need to check whether there is an operation in progress.
     * If so, HSMXXF3_cancelOperation() API will take care of canceling the operation and
     * setting the HSM back to a ready state.
     */
    if (object->returnBehavior == ECDH_RETURN_BEHAVIOR_CALLBACK)
    {
        /* Since the HSM cannot cancel an in-progress token, we must wait for the result to allow for
         * subsequent token submissions to succeed.
         */
        (void)HSMXXF3_cancelOperation();

        object->callbackFxn(handle, ECDH_STATUS_CANCELED, *object->operation, object->operationType);
    }

    return ECDH_STATUS_SUCCESS;
}

static int_fast16_t ECDHXXF3HSM_createAndLoadAllAssets(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_SUCCESS;
    ECDHXXF3HSM_Object *object = handle->object;

    /* Perform two HSM operations:
     * - Create an asset that holds the operation's asymmetric private key.
     * - Load the operation's private key onto HSM RAM.
     */
    status = ECDHXXF3HSM_createAndLoadPrivateKeyAssetID(handle);

    if (status != ECDH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Perform two HSM operations:
     * - Create An asset that holds the operation's asymmetric public key.
     * - If the operation is to generate a shared secret, load the operation's
     *   public key onto HSM RAM.
     */
    status = ECDHXXF3HSM_createAndLoadPublicKeyAssetID(handle);

    if (status != ECDH_STATUS_SUCCESS)
    {
        return status;
    }

    if ((HSMXXF3_isStandaloneDMASupportEnabled()) ||
        (object->operationType == ECDH_OPERATION_TYPE_COMPUTE_SHARED_SECRET))
    {
        /* Two scenarios where a public data object is need to hold a key
         * material.
         * 1. If the operation type is generate public key and the HSM allows
         *    for standalone DMA operations (HSM FW>=3.1.1), then the ECDH
         *    driver needs to create a public data object to hold the public key
         *    material.
         * 2. If the operation type is generate shared secret key. It does not
         *    matter what the HSM FW version is.
         */
        status = ECDHXXF3HSM_createPublicDataAsset(handle);

        if (status != ECDH_STATUS_SUCCESS)
        {
            return status;
        }
    }

    /* Perform two HSM operations:
     * - Create an asset that holds the operation's ECC curve parameters
     * - Load the appropriate ECC curve parameters onto HSM RAM
     */
    status = ECDHXXF3HSM_createAndLoadECurveAssetID(handle);

    return status;
}

/*
 *  ================ APIs to Handle Private Key Asset ================
 */

/*
 *  ======== ECDHXXF3HSM_createAndLoadPrivateKeyAssetID ========
 */
static int_fast16_t ECDHXXF3HSM_createAndLoadPrivateKeyAssetID(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;
    bool isKeyStoreKeyMaterial = false;
    uint8_t *keyMaterial;
#if (ENABLE_KEY_STORAGE == 1)
    uint8_t KeyStore_keyingMaterial[ECDHXXF3HSM_MAX_PRIVATE_KEY_SIZE];
    /* This is the intended usage of the key. Providing the intended usage allows KeyStore
     * to verify that the key being retrieved allows this usage. However, for CC27XX,
     * this check is performed in the PSA Crypto Wrapper as opposed to within KeyStore.
     */
    KeyStore_PSA_KeyUsage usage = KEYSTORE_PSA_KEY_USAGE_DERIVE;

    if (object->privateKey->encoding == CryptoKey_KEYSTORE_HSM)
    {
        keyMaterial = &KeyStore_keyingMaterial[0];

        /* Release the CommonResource semaphore before entering the KeyStore space since KeyStore will attempt to
         * acquire for key management operations.
         */
        CommonResourceXXF3_releaseLock();

        status = KeyStore_PSA_retrieveFromKeyStore(object->privateKey,
                                                   &KeyStore_keyingMaterial[0],
                                                   sizeof(KeyStore_keyingMaterial),
                                                   &object->privateKeyAssetID,
                                                   KEYSTORE_PSA_ALG_ECDH,
                                                   usage);

        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
        if (!CommonResourceXXF3_acquireLock(object->accessTimeout))
        {
            HSMXXF3_releaseLock();

            status = ECDH_STATUS_RESOURCE_UNAVAILABLE;
        }

        if (status != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            return status;
        }
        else if (object->privateKeyAssetID != 0)
        {
            /* In this case, we already retrieved an asset from KeyStore,
             * so we don't need the driver to create and load an asset itself.
             */
            object->driverCreatedKeyAsset = false;

            return status;
        }
        else
        {
            isKeyStoreKeyMaterial = true;
        }
    }
    else
#endif
    {
        keyMaterial = object->privateKey->u.plaintext.keyMaterial;
    }

    /* Constructs the policy for the asset and submits an asset create token to the HSM IP */
    status = ECDHXXF3HSM_createPrivateKeyAsset(handle);
    if (status == ECDH_STATUS_SUCCESS)
    {
        /* Now that the driver has successfully created an asset, object->privateKeyAssetID is now non-zero.
         * If any failure condition happens after this moment, the cleanup will expect
         * object->driverCreatedKeyAsset to be accurate, since the privateKeyAssetID will reflect that there
         * is an asset to free, and the cleanup will need to know how to do that.
         */
        object->driverCreatedKeyAsset = true;

        /* Constructs an asset load token and submits it to the HSM IP */
        status = ECDHXXF3HSM_LoadPrivateKeyAsset(handle, keyMaterial, isKeyStoreKeyMaterial);
    }
    else
    {
        /* If the driver fails to create an asset, privateKeyAssetID is already 0
         * from the top of ECDH_generatePublicKey() and ECDH_computeSharedSecret(),
         * so the cleanup already knows there is nothing to do here.
         */
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_CreatePrivateKeyAssetPostProcessing ========
 */
static inline void ECDHXXF3HSM_CreatePrivateKeyAssetPostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    /* TokenResult carries information regarding the operation result status as well as other information such as
     * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
     * relevant information to an operation's result status.
     */
    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->privateKeyAssetID = HSMXXF3_getResultAssetID();
        status                    = ECDH_STATUS_SUCCESS;
    }

    object->hsmStatus = status;
}

/*
 *  ======== ECDHXXF3HSM_createPrivateKeyAsset ========
 */
static int_fast16_t ECDHXXF3HSM_createPrivateKeyAsset(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;
    uint64_t assetPolicy       = 0U;
    uint32_t assetSize         = HSM_ASYM_DATA_SIZE_VWB(object->curveLength);

    /* Operation (Lower 16-bits + general Operation) + Direction. No Mode */
    assetPolicy = EIP130_ASSET_POLICY_ASYM_KEYEXCHANGE | EIP130_ASSET_POLICY_PRIVATEDATA | EIP130_ASSET_POLICY_STANY;

    if (object->curveType == ECDH_TYPE_CURVE_25519)
    {
        assetPolicy |= EIP130_ASSET_POLICY_ACA_CURVE25519;
    }
    else
    {
        assetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
    }

    /* Populates the HSMXXF3 commandToken as a create asset token */
    HSMXXF3_constructCreateAssetToken(assetPolicy, assetSize);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_CreatePrivateKeyAssetPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_LoadKeyAssetPostProcessing ========
 */
static inline void ECDHXXF3HSM_LoadKeyAssetPostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    /* TokenResult carries information regarding the operation result status as well as other information such as
     * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
     * relevant information to an operation's result status.
     */
    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = ECDH_STATUS_SUCCESS;
    }

    object->hsmStatus = status;
}

/*
 *  ======== ECDHXXF3HSM_formatCurve25519PrivateKeyScratch ========
 */
static void ECDHXXF3HSM_formatCurve25519PrivateKeyScratch(uint8_t *myPrivateKey)
{
    /*
     * As per RFC 7748, the private key of Curve25519 is pruned so that
     * the three LSB's are cleared, bit 255 is cleared, and bit 254 is
     * set.
     */
    /* Clear bit 0, 1, and 2 */
    myPrivateKey[0] &= 0xF8UL;
    /* Clear bit 255 */
    myPrivateKey[31] &= 0x7FFUL;
    /* Set bit 254 */
    myPrivateKey[31] |= 0x40UL;
}

/*
 *  ======== ECDHXXF3HSM_LoadPrivateKeyAsset ========
 */
static int_fast16_t ECDHXXF3HSM_LoadPrivateKeyAsset(ECDH_Handle handle, uint8_t *key, bool isFromKeyStore)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;
    uint32_t componentLength   = HSM_ASYM_DATA_SIZE_VWB(object->curveLength);

    if (!isFromKeyStore)
    {
        /* Initialize the object->output buffer that will hold the single or
         * multi-component vector for the operation's key.
         */
        (void)memset(&object->output[0], 0, componentLength);

        HSMXXF3_asymDHPriKeyToHW(object->privateKey->u.plaintext.keyMaterial,
                                 object->curveLength,
                                 object->domainId,
                                 (HSMXXF3_KeyMaterialEndianness)object->keyMaterialEndianness,
                                 &object->output[0]);
        if (object->curveType == ECDH_TYPE_CURVE_25519)
        {
            /* The ECDH driver needs to prune the private key. */
            ECDHXXF3HSM_formatCurve25519PrivateKeyScratch(&object->output[HSM_ASYM_DATA_VHEADER]);
        }

        /* Populates the HSMXXF3 commandToken as a load asset token */
        HSMXXF3_constructLoadPlaintextAssetToken(&object->output[0], componentLength, object->privateKeyAssetID);
    }
#if (ENABLE_KEY_STORAGE == 1)
    else
    {
        /* isFromKeyStore can only be true if ENABLE_KEY_STORAGE is true */
        if (object->curveType == ECDH_TYPE_CURVE_25519)
        {
            /* The ECDH driver needs to prune the private key - KeyStore does not do this. */
            ECDHXXF3HSM_formatCurve25519PrivateKeyScratch(&key[HSM_ASYM_DATA_VHEADER]);
        }

        /* Populates the HSMXXF3 commandToken as a load asset token */
        HSMXXF3_constructLoadPlaintextAssetToken(key, componentLength, object->privateKeyAssetID);
    }
#endif

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_LoadKeyAssetPostProcessing,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}

/*
 *  ================ APIs to Handle Public Key Asset ================
 */

/*
 *  ======== ECDHXXF3HSM_createAndLoadPublicKeyAssetID ========
 */
static int_fast16_t ECDHXXF3HSM_createAndLoadPublicKeyAssetID(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;

    /* Constructs the policy for the asset and submits an asset create token to the HSM IP */
    status = ECDHXXF3HSM_createPublicKeyAsset(handle);
    if ((status == ECDH_STATUS_SUCCESS) && (object->operationType == ECDH_OPERATION_TYPE_COMPUTE_SHARED_SECRET))
    {
        /* Constructs an asset load token and submits it to the HSM IP */
        status = ECDHXXF3HSM_LoadPublicKeyAsset(handle);
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_createPublicKeyAssetPostProcessing ========
 */
static inline void ECDHXXF3HSM_createPublicKeyAssetPostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    /* TokenResult carries information regarding the operation result status as well as other information such as
     * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
     * relevant information to an operation's result status.
     */
    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->publicKeyAssetID = HSMXXF3_getResultAssetID();
        status                   = ECDH_STATUS_SUCCESS;
    }

    object->hsmStatus = status;
}

/*
 *  ======== ECDHXXF3HSM_createPublicKeyAsset ========
 */
static int_fast16_t ECDHXXF3HSM_createPublicKeyAsset(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;
    uint64_t assetPolicy       = EIP130_ASSET_POLICY_ASYM_KEYEXCHANGE;
    uint32_t assetSize         = HSM_ASYM_DATA_SIZE_VWB(object->curveLength);

    /* Public key for curve25519 is comprised of only one component, pubkey.u.
     * For shared secret operations, if the user provides in big endian
     * more than one component, the ECDH driver only takes the first one.
     */
    if (object->curveType != ECDH_TYPE_CURVE_25519)
    {
        /* Operation (Lower 16-bits + general Operation) + Direction. No Mode */
        assetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
        assetSize *= HSM_ASYM_ECC_PUB_KEY_VCOUNT;
    }
    else
    {
        /* Operation (Lower 16-bits + general Operation) + Direction. No Mode */
        assetPolicy |= EIP130_ASSET_POLICY_ACA_CURVE25519;
    }

    /* Populates the HSMXXF3 commandToken as a create asset token */
    HSMXXF3_constructCreateAssetToken(assetPolicy, assetSize);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_createPublicKeyAssetPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_LoadPublicKeyAsset ========
 */
static int_fast16_t ECDHXXF3HSM_LoadPublicKeyAsset(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;
    uint32_t componentLength   = HSM_ASYM_DATA_SIZE_VWB(object->curveLength);
    uint8_t itemCount          = HSM_ASYM_CURVE25519_PUB_KEY_VCOUNT;

    /* Initialize the object->output buffer that will hold the single or
     * multi-component vector for the operation's key.
     */
    (void)memset(&object->output[0], 0, ECDH_COMPONENT_VECTOR_LENGTH);

    /* Public key for curve25519 is comprised of only one component, pubkey.u.
     * For shared secret operations, if the user provides in big endian
     * more than one component, the ECDH driver only takes the first one.
     */
    if (object->curveType != ECDH_TYPE_CURVE_25519)
    {
        componentLength *= HSM_ASYM_ECC_PUB_KEY_VCOUNT;
        itemCount = HSM_ASYM_ECC_PUB_KEY_VCOUNT;
    }

    HSMXXF3_asymDHPubKeyToHW(object->publicKey->u.plaintext.keyMaterial,
                             object->curveLength,
                             itemCount,
                             object->domainId,
                             (HSMXXF3_KeyMaterialEndianness)object->keyMaterialEndianness,
                             &object->output[0]);

    /* Populates the HSMXXF3 commandToken as a load asset token */
    HSMXXF3_constructLoadPlaintextAssetToken(&object->output[0], componentLength, object->publicKeyAssetID);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_LoadKeyAssetPostProcessing,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}

/*
 *  ================ APIs to Create Public Data Asset ================
 */

/*
 *  ======== ECDHXXF3HSM_createPublicDataAssetPostProcessing ========
 */
static inline void ECDHXXF3HSM_createPublicDataAssetPostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    /* TokenResult carries information regarding the operation result status as well as other information such as
     * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
     * relevant information to an operation's result status.
     */
    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->publicDataAssetID = HSMXXF3_getResultAssetID();
        status                    = ECDH_STATUS_SUCCESS;
    }

    object->hsmStatus = status;
}

/*
 *  ======== ECDHXXF3HSM_createPublicDataAsset ========
 */
static int_fast16_t ECDHXXF3HSM_createPublicDataAsset(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;
    uint64_t assetPolicy       = 0U;
    uint32_t assetSize         = 0U;

    if (object->operationType == ECDH_OPERATION_TYPE_GENERATE_PUBLIC_KEY)
    {
        assetSize = HSM_ASYM_DATA_SIZE_VWB(object->curveLength);

        /* Public key for curve25519 is comprised of only one component, pubkey.u.
         * For shared secret operations, if the user provides in big endian
         * more than one component, the ECDH driver only takes the first one.
         */
        if (object->curveType != ECDH_TYPE_CURVE_25519)
        {
            assetSize *= HSM_ASYM_ECC_PUB_KEY_VCOUNT;
        }
    }
    else
    {
        assetSize = HSM_ASYM_DATA_SIZE_B2WB(object->curveLength);
    }

    /* Operation (Lower 16-bits + general Operation) + Direction. No Mode */
    assetPolicy = EIP130_ASSET_POLICY_NONMODIFIABLE | EIP130_ASSET_POLICY_NODOMAIN | EIP130_ASSET_POLICY_PUBLICDATA |
                  EIP130_ASSET_POLICY_GENERICDATA | EIP130_ASSET_POLICY_GDPUBLICDATA;

    /* Populates the HSMXXF3 commandToken as a create asset token */
    HSMXXF3_constructCreateAssetToken(assetPolicy, assetSize);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_createPublicDataAssetPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}

/*
 *  ================ APIs to Create and Load ECC Curve Parameters ================
 */

/*
 *  ======== ECDHXXF3HSM_createAndLoadECurveAssetID ========
 */
static int_fast16_t ECDHXXF3HSM_createAndLoadECurveAssetID(ECDH_Handle handle)
{
    int_fast16_t status = ECDH_STATUS_ERROR;

    status = ECDHXXF3HSM_createECurveAsset(handle);
    if (status == ECDH_STATUS_SUCCESS)
    {
        status = ECDHXXF3HSM_LoadECurve(handle);
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_createECurveAssetPostProcessing ========
 */
static inline void ECDHXXF3HSM_createECurveAssetPostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    /* TokenResult carries information regarding the operation result status as well as other information such as
     * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
     * relevant information to an operation's result status.
     */
    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->paramAssetID = HSMXXF3_getResultAssetID();
        status               = ECDH_STATUS_SUCCESS;
    }

    object->hsmStatus = status;
}

/*
 *  ======== ECDHXXF3HSM_createECurveAsset ========
 */
static int_fast16_t ECDHXXF3HSM_createECurveAsset(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;
    uint64_t assetPolicy       = EIP130_ASSET_POLICY_ASYM_KEYPARAMS;

    /* Populates the HSMXXF3 commandToken as a create asset token */
    HSMXXF3_constructCreateAssetToken(assetPolicy, object->curveParamSize);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_createECurveAssetPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_LoadECurvePostProcessing ========
 */
static inline void ECDHXXF3HSM_LoadECurvePostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    /* TokenResult carries information regarding the operation result status as well as other information such as
     * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
     * relevant information to an operation's result status.
     */
    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = ECDH_STATUS_SUCCESS;
    }

    object->hsmStatus = status;
}

/*
 *  ======== ECDHXXF3HSM_LoadECurve ========
 */
static int_fast16_t ECDHXXF3HSM_LoadECurve(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;

    /* Populates the HSMXXF3 commandToken as a load asset token */
    HSMXXF3_constructLoadPlaintextAssetToken(object->curveParam, object->curveParamSize, object->paramAssetID);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_LoadECurvePostProcessing,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}

/*
 *  ================ APIs to Free Assets ================
 */

/*
 *  ======== ECDHXXF3HSM_freeAllAssets ========
 */
static int_fast16_t ECDHXXF3HSM_freeAllAssets(ECDH_Handle handle)
{
    int_fast16_t status        = ECDH_STATUS_SUCCESS;
    ECDHXXF3HSM_Object *object = handle->object;

    /* Check to see if a private key asset has been allocated.
     * If so, then free the asset.
     */
    if (object->privateKeyAssetID != 0)
    {
        /* If the object has a stored privateKeyAssetID, then driverCreatedKeyAsset MUST
         * be set. It can only be false if KeyStore is enabled. If it is false,
         * it means that we retrieved an asset directly from KeyStore, so the
         * driver should not free the asset. Instead, the driver should direct
         * KeyStore to free the asset (which will perform the necessary persistence
         * check and only free the asset if it should be freed).
         */
        if (object->driverCreatedKeyAsset == true)
        {
            status = ECDHXXF3HSM_freeAssetID(handle, object->privateKeyAssetID);
        }
#if (ENABLE_KEY_STORAGE == 1)
        else
        {
            KeyStore_PSA_KeyFileId keyID;

            GET_KEY_ID(keyID, object->privateKey->u.keyStore.keyID);

            status = KeyStore_PSA_assetPostProcessing(keyID);
        }
#endif

        /* This condition captures success from both the ECDHXXF3HSM and
         * KeyStore_PSA APIs.
         */
        if (status == ECDH_STATUS_SUCCESS)
        {
            object->privateKeyAssetID = 0;
        }
    }

    /* Check to see if a public key asset has been allocated.
     * If so, then free the asset.
     */
    if (object->publicKeyAssetID != 0)
    {
        if (ECDHXXF3HSM_freeAssetID(handle, object->publicKeyAssetID) != ECDH_STATUS_SUCCESS)
        {
            status = ECDH_STATUS_ERROR;
        }
        else
        {
            object->publicKeyAssetID = 0;
        }
    }

    /* Check to see if a public data asset has been allocated.
     * If so, then free the asset.
     */
    if (object->publicDataAssetID != 0)
    {
        if (ECDHXXF3HSM_freeAssetID(handle, object->publicDataAssetID) != ECDH_STATUS_SUCCESS)
        {
            status = ECDH_STATUS_ERROR;
        }
        else
        {
            object->publicDataAssetID = 0;
        }
    }

    /* Check to see if a ECC parameters asset has been allocated.
     * If so, then free the asset.
     */
    if (object->paramAssetID != 0)
    {
        if (ECDHXXF3HSM_freeAssetID(handle, object->paramAssetID) != ECDH_STATUS_SUCCESS)
        {
            status = ECDH_STATUS_ERROR;
        }
        else
        {
            object->paramAssetID = 0;
        }
    }

    return status;
}

/*
 *  ======== ECDHXXF3HSM_freeAssetPostProcessing ========
 */
static inline void ECDHXXF3HSM_freeAssetPostProcessing(uintptr_t arg0)
{
    ECDH_Handle handle         = (ECDH_Handle)arg0;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t status        = ECDH_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    /* TokenResult carries information regarding the operation result status as well as other information such as
     * whether the operation is FIPS approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract only
     * relevant information to an operation's result status.
     */
    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = ECDH_STATUS_SUCCESS;
    }

    object->hsmStatus = status;
}

/*
 *  ======== ECDHXXF3HSM_freeAssetID ========
 */
static int_fast16_t ECDHXXF3HSM_freeAssetID(ECDH_Handle handle, uint32_t assetID)
{
    int_fast16_t status        = ECDH_STATUS_ERROR;
    ECDHXXF3HSM_Object *object = handle->object;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;

    /* Populates the HSMXXF3 commandToken as a delete asset token */
    (void)HSMXXF3_constructDeleteAssetToken(assetID);

    /* Submit token to the HSM IP engine */
    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    ECDHXXF3HSM_freeAssetPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking modes (and calls the drivers post-processing
         * fxn) and returns immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->hsmStatus;
        }
    }

    return status;
}
