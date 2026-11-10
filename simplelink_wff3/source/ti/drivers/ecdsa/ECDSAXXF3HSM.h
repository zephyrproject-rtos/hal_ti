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
 *  @file       ECDSAXXF3HSM.h
 *
 *  @brief      ECDSA HSM IP driver implementation for the Low Power F3 family
 *
 *  This file should only be included in the board file to fill the ECDSA_config
 *  struct.
 *
 *  # Hardware and Implementation Details #
 *
 *  The driver is backed by a software ECC library implementation.
 *
 *  # CC35XX: Callback Mode Restrictions with External Memory
 *  On CC35XX devices, #ECDSA_RETURN_BEHAVIOR_CALLBACK is not supported for
 *  sign operations when the ECDSA driver object is placed in PSRAM.
 *  Returns #ECDSA_STATUS_FEATURE_NOT_SUPPORTED in this case.
 *  Use #ECDSA_RETURN_BEHAVIOR_BLOCKING or #ECDSA_RETURN_BEHAVIOR_POLLING
 *  instead. See #HSMXXF3_BounceBuffers.
 *
 *  # Supported Curves #
 *
 *  The driver implementation supports the following curves for ECDSA:
 *
 *  | Curves Supported |
 *  |------------------|
 *  | NISTP256         |
 *  | NISTP224         |
 *  | NISTP2384        |
 *  | NISTP521         |
 *  | BRP256           |
 *  | BRP384           |
 *  | BRP512           |
 */

#ifndef ti_drivers_ecdsa_ECDSAXXF3HSM__include
#define ti_drivers_ecdsa_ECDSAXXF3HSM__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/ECDSA.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */
/* The largest signature will be for NIST521 which will produce 72B per component (S and R) */
#define ECDSAXXF3HSM_COMPONENT_VECTOR_LENGTH 144

/*!
 *  @brief  The curve provided is not supported
 */
#define ECDSAXXF3HSM_STATUS_NO_VALID_CURVE_TYPE_PROVIDED (ECDSA_STATUS_RESERVED - 0)

/*!
 *  @brief  The key encoding is not HSM masked to signify an HSM operation
 */
#define ECDSAXXF3HSM_STATUS_INVALID_KEY_ENCODING (ECDSA_STATUS_RESERVED - 1)

/*!
 *  @brief  An error ocurred on the HW level
 */
#define ECDSAXXF3HSM_STATUS_HARDWARE_ERROR (ECDSA_STATUS_RESERVED - 2)

/*!
 *  @brief      ECDSAXXF3HSM Hardware Attributes
 *
 *  ECDSAXXF3HSM hardware attributes should be included in the board file
 *  and pointed to by the ECDSA_config struct.
 */
typedef struct
{
    uint8_t dummy;
} ECDSAXXF3HSM_HWAttrs;

/*!
 *  @brief  Enum for the curve domain id supported by the driver.
 */
typedef enum
{
    ECDSA_DOMAIN_ID_SEC = 0,
    ECDSA_DOMAIN_ID_BRP = 1,
} ECDSA_DomainID;

/*!
 *  @brief      ECDSAXXF3HSM Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    CryptoKey *key;
    uint32_t keyAssetID;
    uint32_t paramAssetID;
    uint32_t publicObjAssetID;
    uint32_t curveParamSize;
    uint8_t signature[ECDSAXXF3HSM_COMPONENT_VECTOR_LENGTH] __attribute__((aligned(4)));
    int_fast16_t returnStatus;
    int_fast16_t hsmStatus;
    ECDSA_ReturnBehavior returnBehavior;
    uint32_t accessTimeout;
    ECDSA_CurveType curveType;
    ECDSA_DomainID domainId;
    ECDSA_CurveLength curveLength;
    ECDSA_DigestLength digestLength;
    ECDSA_OperationType operationType;
    ECDSA_Operation *operation;
    ECDSA_CallbackFxn callbackFxn;
    const uint8_t *curveParam;
    uint8_t *input;
    bool driverCreatedKeyAsset;
    bool isOpen;
} ECDSAXXF3HSM_Object;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_ecdsa_ECDSAXXF3HSM__include */
