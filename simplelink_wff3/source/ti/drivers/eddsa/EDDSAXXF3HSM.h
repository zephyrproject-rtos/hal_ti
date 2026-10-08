/*
 * Copyright (c) 2025-2026 Texas Instruments Incorporated
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

/** ===========================================================================
 *  @file       EDDSAXXF3HSM.h
 *
 *  @brief      EdDSA driver implementation for the CC27XX and CC35XX family
 *
 *  This file should only be included in the board file to fill the
 *  EDDSA_config struct.
 *
 *  # CC35XX: Callback Mode Restrictions with External Memory
 *  On CC35XX devices, #EDDSA_RETURN_BEHAVIOR_CALLBACK is not supported when
 *  the EDDSA driver object is placed in external memory (PSRAM) for the
 *  following operations:
 *  - #EDDSA_generatePublicKey()
 *  - #EDDSA_sign()
 *  Returns #EDDSA_STATUS_FEATURE_NOT_SUPPORTED in these cases.
 *  Use #EDDSA_RETURN_BEHAVIOR_BLOCKING or #EDDSA_RETURN_BEHAVIOR_POLLING
 *  instead. See #HSMXXF3_BounceBuffers.
 *
 *  # Supported Curve Types #
 *
 *  The driver implementation supports the following curves for EdDSA:
 *
 *  | Curve        | Supported |
 *  |--------------|-----------|
 *  | Ed25519      | Yes       |
 *  | Ed448        | No        |
 *
 */

#ifndef ti_drivers_eddsa_EDDSAXXF3HSM__include
#define ti_drivers_eddsa_EDDSAXXF3HSM__include

#include <ti/drivers/EDDSA.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */
/* The largest signature will be for NIST521 which will produce 72B per component (S and R) */
#define EDDSA_COMPONENT_VECTOR_LENGTH_BYTES 72
#define EDDSA_CURVE_LENGTH_25519            255

/*!
 * @brief   An error status code returned if the hardware or software resource
 * is currently unavailable.
 *
 * EDDSA driver implementations may have hardware or software limitations on how
 * many clients can simultaneously perform operations. This status code is
 * returned if the mutual exclusion mechanism signals that an operation cannot
 * currently be performed.
 */
#define EDDSAXXF3HSM_STATUS_RESOURCE_UNAVAILABLE (ECDSA_STATUS_RESERVED - 0)

/*!
 *  @brief  An error ocurred on the HW level
 */
#define EDDSAXXF3HSM_STATUS_HARDWARE_ERROR (ECDSA_STATUS_RESERVED - 1)

/*!
 *  @brief  Message length must be greater than zero.
 */
#define EDDSAXXF3HSM_STATUS_INVALID_MESSAGE_LENGTH (ECDSA_STATUS_RESERVED - 2)

/*!
 *  @brief  Invalid encoding for private or public keys or both.
 */
#define EDDSAXXF3HSM_STATUS_INVALID_KEY_ENCODING (ECDSA_STATUS_RESERVED - 3)

/*!
 *  @brief      EDDSAXXF3HSM Hardware Attributes
 *
 *  EDDSAXXF3HSM hardware attributes should be included in the board file
 *  and pointed to by the EDDSA_config struct.
 */
typedef struct
{
    uint16_t reserved1;
} EDDSAXXF3HSM_HWAttrs;

/*!
 *  @brief      EDDSAXXF3HSM Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    CryptoKey *privateKey;
    CryptoKey *publicKey;
    bool isOpen;
    bool driverCreatedPrivateKeyAsset;
    bool driverCreatedPublicKeyAsset;
    int_fast16_t returnStatus;
    EDDSA_Operation *operation;
    EDDSA_OperationType operationType;
    EDDSA_CallbackFxn callbackFxn;
    EDDSA_ReturnBehavior returnBehavior;
    uint32_t semaphoreTimeout;
    int_fast16_t hsmStatus;
    uint32_t privateKeyAssetID;
    uint32_t publicKeyAssetID;
    uint32_t paramAssetID;
    uint32_t tempAssetID;
    uint32_t stateAssetID;
    const uint8_t *curveParam;
    uint32_t curveParamSize;
    uint8_t *input;
    size_t inputLength;
    size_t inputLengthRemaining;
    uint8_t signature[EDDSA_COMPONENT_VECTOR_LENGTH_BYTES];
} EDDSAXXF3HSM_Object;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_eddsa_EDDSAXXF3HSM__include */