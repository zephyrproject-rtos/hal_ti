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
/** ============================================================================
 *  @file       ECDHXXF3HSM.h
 *
 *  @brief      ECDH HSM IP driver implementation for the Low Power F3 and WiFi
 *              F3 family
 *
 *  This file should only be included in the board file to fill the #ECDH_config
 *  struct.
 *
 *  # CC35XX: Callback Mode Restrictions with External Memory
 *  On CC35XX devices, #ECDH_RETURN_BEHAVIOR_CALLBACK is not supported when the
 *  ECDH driver object is placed in PSRAM. #ECDH_construct() and #ECDH_open()
 *  return NULL in this case. Use #ECDH_RETURN_BEHAVIOR_BLOCKING or
 *  #ECDH_RETURN_BEHAVIOR_POLLING instead.
 *
 *  Additionally, #ECDH_construct() and #ECDH_open() return NULL if the ECDH
 *  driver object is in PSRAM and either #HSMXXF3_inputBounce or
 *  #HSMXXF3_outputBounce is smaller than #ECDH_COMPONENT_VECTOR_LENGTH
 *  (144 bytes, the P-521 component vector size). The input buffer is required
 *  because object->output[] is used as scratch for key material that is staged
 *  via stageInput before being loaded into HSM assets.
 *  See #HSMXXF3_BounceBuffers.
 *
 */

#ifndef ti_drivers_ecdh_ECDHXXF3HSM__include
#define ti_drivers_ecdh_ECDHXXF3HSM__include

#include <stdint.h>
#include <stdbool.h>
#include <ti/drivers/ECDH.h>

#include <third_party/hsmddk/include/Kit/EIP130/DomainHelper/incl/eip130_domain_ecc_curves.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */
/* The largest signature will be for NIST521 which will produce 72B per component (S and R) */
#define ECDH_COMPONENT_VECTOR_LENGTH 144

/*!
 *  @brief  An error ocurred on the HW level
 */
#define ECDHXXF3HSM_STATUS_HARDWARE_ERROR (ECDH_STATUS_RESERVED - 0)

/*!
 *  @brief  The curve provided is not supported
 */
#define ECDHXXF3HSM_STATUS_NO_VALID_CURVE_TYPE_PROVIDED (ECDH_STATUS_RESERVED - 1)

/*!
 *  @brief  The private key encoding is not HSM masked to signify an HSM operation
 */
#define ECDHXXF3HSM_STATUS_INVALID_PRIVATE_KEY_ENCODING (ECDH_STATUS_RESERVED - 2)

/*!
 *  @brief  The public key encoding is not HSM masked to signify an HSM operation
 */
#define ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_ENCODING (ECDH_STATUS_RESERVED - 3)

/*!
 *  @brief  The shared secret key encoding is not HSM masked to signify an HSM operation
 */
#define ECDHXXF3HSM_STATUS_INVALID_SHARED_SECRET_KEY_ENCODING (ECDH_STATUS_RESERVED - 4)

/*!
 *  @brief  The private key length does not match the curve type length provided
 */
#define ECDHXXF3HSM_STATUS_INVALID_PRIVATE_KEY_SIZE (ECDH_STATUS_RESERVED - 5)

/*!
 *  @brief  The public key length does not match the curve type length provided
 */
#define ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_SIZE (ECDH_STATUS_RESERVED - 6)

/*!
 *  @brief  The shared secret key length does not match the curve type length provided
 */
#define ECDHXXF3HSM_STATUS_INVALID_SHARED_SECRET_KEY_SIZE (ECDH_STATUS_RESERVED - 7)

/*!
 *  @brief  The public key length does not match the curve type length provided
 */
#define ECDHXXF3HSM_STATUS_INVALID_ECC_KEYS (ECDH_STATUS_RESERVED - 8)

/*!
 *  @brief  The public key octet string value is incorrect
 */
#define ECDHXXF3HSM_STATUS_INVALID_PUBLIC_KEY_OCTET_VALUE (ECDH_STATUS_RESERVED - 9)

/*!
 *  @brief Hardware-specific configuration attributes
 *
 *  ECDHXXF3HSM hardware attributes are used in the board file by the
 *  #ECDH_Config struct.
 */
typedef struct
{
    uint8_t reserved1;
} ECDHXXF3HSM_HWAttrs;

/*!
 *  @brief  Enum for the curve domain id supported by the driver.
 */
typedef enum
{
    ECDH_DOMAIN_ID_SEC = 0,
    ECDH_DOMAIN_ID_BRP = 1,
} ECDH_DomainID;

/*!
 *  @brief ECDHXXF3HSM Object
 *
 *  \note The application must not access any member variables of this structure!
 */
typedef struct
{
    const CryptoKey *privateKey;
    CryptoKey *publicKey;
    CryptoKey *sharedSecret;
    ECDH_CurveType curveType;
    ECDH_CurveLength curveLength;
    ECDH_DomainID domainId;
    Eip130Domain_ECCurveFamily_t curveFamily;
    ECDH_CallbackFxn callbackFxn;
    ECDH_Operation *operation;
    ECDH_OperationType operationType;
    ECDH_ReturnBehavior returnBehavior;
    ECDH_KeyMaterialEndianness keyMaterialEndianness;
    uint32_t accessTimeout;
    int_fast16_t returnStatus;
    int_fast16_t hsmStatus;
    uint32_t privateKeyAssetID;
    uint32_t publicKeyAssetID;
    uint32_t publicDataAssetID;
    uint32_t paramAssetID;
    const uint8_t *curveParam;
    uint32_t curveParamSize;
    uint8_t output[ECDH_COMPONENT_VECTOR_LENGTH];
    bool driverCreatedKeyAsset;
    bool isOpen;
} ECDHXXF3HSM_Object;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_ecdh_ECDHXXF3HSM__include */