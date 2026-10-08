/*
 * Copyright (c) 2023-2026 Texas Instruments Incorporated
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
 *  @file       AESGCMXXF3HSM.h
 *
 *  @brief      AESGCM driver implementation for the Low Power F3 family
 *
 *  This file should only be included in the board file to fill the AESGCM_config
 *  struct.
 *
 * # Hardware Accelerator #
 * The Low Power F3 family of devices has dedicated hardware accelerators.
 * CC23XX devices have one dedicated accelerator whereas CC27XX devices have two
 * (Primary and Secondary). Combined they can perform AES encryption operations with
 * 128-bit, 192-bit and 256-bit keys. Only one operation can be carried out on the
 * accelerator at a time. Mutual exclusion is implemented at the driver level and
 * coordinated between all drivers relying on the accelerator. It is transparent to
 * the application and only noted to ensure sensible access timeouts are set.
 * The GHASH computation for GCM has optimizations using Shoup's 4-bit tables that
 * are precomputed for each hash key H.
 *
 *  # CC35XX: External Memory (PSRAM) Support
 *  On CC35XX devices, AES-GCM input, output, and AAD buffers may reside in
 *  PSRAM. The driver object itself may also be placed in PSRAM. Bounce buffers
 *  must be configured via SysConfig (HSM module) large enough to hold the
 *  largest single-pass transfer. See #HSMXXF3_BounceBuffers.
 *
 *  Callback return behavior (#AESGCM_RETURN_BEHAVIOR_CALLBACK) is not
 *  supported on CC35XX regardless of buffer location.
 *
 *  # Implementation Limitations
 *  - Only plaintext CryptoKeys are supported by this implementation.
 *  - Callback return behavior is not supported by this implementation.
 *  - Blocking return behavior operates the same as polling return behavior and
 *    does not block the calling thread.
 *
 *  # Runtime Parameter Validation #
 *  The driver implementation does not perform runtime checks for most input
 *  parameters. Only values that are likely to have a stochastic element to them
 *  are checked (such as whether a driver is already open). Higher input
 *  parameter validation coverage is achieved by turning on assertions when
 *  compiling the driver.
 */

#ifndef ti_drivers_aesgcm_AESGCMXXF3HSM__include
#define ti_drivers_aesgcm_AESGCMXXF3HSM__include

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ti/drivers/AESGCM.h>
#include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>

#include <ti/devices/DeviceFamily.h>
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    #include DeviceFamily_constructPath(driverlib/aes.h)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief      AESGCMXXF3 Hardware Attributes
 *
 *  AESGCMXXF3 hardware attributes should be included in the board file
 *  and pointed to by the AESGCM_config struct.
 */
typedef AESCommonXXF3_HWAttrs AESGCMXXF3HSM_HWAttrs;

/*!
 *  @brief      AESGCMXXF3HSM Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    /* Common member first to allow struct to be cast to the common type */
    AESCommonXXF3_Object common;
    const uint8_t *aad;
    const uint8_t *input;
    uint8_t *output;
    const uint8_t *iv;
    uint8_t *mac;
    uint32_t counter[AES_BLOCK_SIZE_WORDS];
    volatile uint32_t intermediateTag[AES_BLOCK_SIZE_WORDS];
    uint32_t hashKey[AES_BLOCK_SIZE_WORDS];
    uint32_t tagOTP[AES_BLOCK_SIZE_WORDS];
    AESGCM_CallbackFxn callbackFxn;
    AESGCM_OperationUnion *operation;
    size_t inputLength;
    size_t aadLength;
    uint8_t bufferedAADLength;
    size_t totalAADLength;
    size_t totalDataLength;
    volatile size_t totalDataLengthRemaining;
    volatile size_t totalAADLengthRemaining;
    AESGCM_OperationType operationType;
    uint8_t macLength;
    uint8_t ivLength;
    uint8_t KeyStore_keyingMaterial[AESCommonXXF3_256_KEY_LENGTH_BYTES];
    uint8_t inputFinalBlock[AES_BLOCK_SIZE];
    uint8_t aadFinalBlock[AES_BLOCK_SIZE];
    uint8_t outputFinalBlock[AES_BLOCK_SIZE] __attribute__((aligned(4)));
    /*!
     * @brief The status of the HSM Boot up process
     * if HSMXXF3_STATUS_SUCCESS, the HSM booted properly.
     * if HSMXXF3_STATUS_ERROR, the HSM did not boot properly.
     */
    int_fast16_t hsmStatus;
    uint32_t keyAssetID;
    uint32_t tempAssetID;
    /* Intentionally use implementation-independent uint32_t datatype for
     * keyLocation to avoid user dependencies on any implementation-specific
     * headers (e.g. mbedTLS). This data type must be large enough to hold any
     * implementation-specific keyLocation data.
     */
    uint32_t keyLocation;
    /* To indicate whether a segmented operation is in progress */
    bool segmentedOperationInProgress;
} AESGCMXXF3HSM_Object;

/*!
 *  @brief  Function to set the mac for an AES CCM segmented operation.
 *          This API needs to be called only when the subsequent #AESGCM_addData() operation is processing all of the
 * remaining data in a single call.
 *
 *  @note   This API is only concerned with segmented decryption operations.
 *
 *  @pre    #AESGCM_setupDecrypt(), #AESGCM_setLengths(), or #AESGCM_addAAD()
 *
 *  @param  [in] handle           A CCM handle returned from #AESGCM_open()
 *                                or #AESGCM_construct()
 *
 *  @param  [in] mac            Pointer to the buffer containing the mac
 *
 *  @param  [in] macLength      The length of the mac in bytes
 *
 *  @retval #AESGCM_STATUS_SUCCESS                  The operation succeeded.
 *  @retval #AESGCM_STATUS_ERROR                    The operation failed.
 *  @retval #AESGCM_STATUS_FEATURE_NOT_SUPPORTED    The operation is not
 *                                                  supported in this device.
 *
 *  @post   #AESGCM_addData()
 */
int_fast16_t AESGCMXXF3HSM_setMac(AESGCM_Handle handle, const uint8_t *mac, size_t macLength);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aesgcm_AESGCMXXF3HSM__include */
