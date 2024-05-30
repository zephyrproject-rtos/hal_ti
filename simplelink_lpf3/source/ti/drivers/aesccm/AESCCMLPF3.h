/*
 * Copyright (c) 2021-2024, Texas Instruments Incorporated
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
/** ==========================================================================
 *  @file       AESCCMLPF3.h
 *
 *  @brief      AESCCM driver implementation for the Low Power F3 family
 *
 *  # CCM Specification
 *  This implementation follows NIST 800-38c -
 *  https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38c.pdf
 *  All symbols used in the implementation for identifiers and in the comments including
 *  but not limited to B0, B1 and S0 are all adopted from this NIST 800-38c.
 *
 * # Hardware Accelerator #
 * The Low Power F3 family of devices has dedicated hardware accelerators.
 * CC23XX devices have one dedicated accelerator whereas CC27XX devices have two
 * (Primary and Secondary). Combined they can perform AES encryption operations with
 * 128-bit, 192-bit and 256-bit keys. Only one operation can be carried out on the
 * accelerator at a time. Mutual exclusion is implemented at the driver level and
 * coordinated between all drivers relying on the accelerator. It is transparent to
 * the application and only noted to ensure sensible access timeouts are set.
 *
 *  # Implementation Limitations
 *  - Only plaintext CryptoKeys are supported by this implementation.
 *  - Maximum AAD length is limited to 65279-bytes.
 *
 *  The following limitations apply to the AESCCMLPF3 Driver for CC27xx device family only:
 *  - The CryptoKey input must have the correct encoding, @ref CryptoKey.h.
 *  - The application can only use one handle per driver.
 *    Concurrent dynamic instances will be supported in the future.
 *  - CCM driver only supports polling return behaviour.
 *    Blocking and callback return behaviours will be supported in the future.
 *
 *  # Runtime Parameter Validation #
 *  The driver implementation does not perform runtime checks for most input parameters.
 *  Only values that are likely to have a stochastic element to them are checked (such
 *  as whether a driver is already open). Higher input parameter validation coverage is
 *  achieved by turning on assertions when compiling the driver.
 */

#ifndef ti_drivers_aesccm_AESCCMLPF3__include
#define ti_drivers_aesccm_AESCCMLPF3__include

#include <stdbool.h>
#include <stdint.h>

#include <ti/drivers/AESCCM.h>
#include <ti/drivers/cryptoutils/aes/AESCommonLPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/aes.h)

#ifdef __cplusplus
extern "C" {
#endif

#define AESCCMLPF3_AAD_BUFFER_SIZE 2U

/*!
 *  @brief      AESCCMLPF3 Hardware Attributes
 *
 *  AESCCMLPF3 hardware attributes should be included in the board file
 *  and pointed to by the AESCCM_config struct.
 */
typedef AESCommonLPF3_HWAttrs AESCCMLPF3_HWAttrs;

/*!
 *  @brief      AESCCMLPF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    /* Common member first to allow struct to be cast to the common type */
    AESCommonLPF3_Object common;
    const uint8_t *aad;
    const uint8_t *input;
    uint8_t *output;
    const uint8_t *nonce;
    uint8_t *mac;
    volatile uint32_t intermediateCounter[AES_IV_LENGTH_BYTES / 4];
    volatile uint32_t intermediateTag[AES_TAG_LENGTH_BYTES / 4];
    AESCCM_CallbackFxn callbackFxn;
    AESCCM_OperationUnion *operation;
    size_t inputLength;
    volatile size_t inputCBCMACLengthRemaining;
    volatile size_t inputCTRLengthRemaining;
    size_t totalAADLength;
    size_t totalDataLength;
    size_t aadBytesProcessed;
    volatile size_t totalCBCMACLengthRemaining;
    volatile size_t totalCTRLengthRemaining;
    AESCCM_OperationType operationType;
    uint8_t bufferedAAD[AESCCMLPF3_AAD_BUFFER_SIZE];
    uint8_t bufferedAADLength;
    uint8_t macLength;
    uint8_t nonceLength;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    size_t aadLength;
    volatile size_t totalDataLengthRemaining;
    volatile size_t totalAADLengthRemaining;
    /*!
     * @brief The staus of the HSM Boot up process
     * if HSMLPF3_STATUS_SUCCESS, the HSM booted properly.
     * if HSMLPF3_STATUS_ERROR, the HSM did not boot properly.
     */
    int_fast16_t hsmStatus;
    uint32_t tempAssetID;
    /* To indicate whether a segmented operation is in progress
     */
    bool segmentedOperationInProgress;
#endif
} AESCCMLPF3_Object;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*!
 *  @brief  Function to set the mac for an AES CCM segmented operation.
 *          This API needs to be called only when the subsequent #AESCCM_addData() operation is processing all of the
 * remaining data in a single call.
 *
 *  @note   This API is only concerned with segmented decryption operations.
 *
 *  @pre    #AESCCM_setupDecrypt(), #AESCCM_setLengths(), or #AESCCM_addAAD()
 *
 *  @param  [in] handle           A CCM handle returned from #AESCCM_open()
 *                                or #AESCCM_construct()
 *
 *  @param  [in] mac            Pointer to the buffer containing the mac
 *
 *  @param  [in] macLength      The length of the mac in bytes
 *
 *  @retval #AESCCM_STATUS_SUCCESS                  The operation succeeded.
 *  @retval #AESCCM_STATUS_ERROR                    The operation failed.
 *  @retval #AESCCM_STATUS_FEATURE_NOT_SUPPORTED    The operation is not
 *                                                  supported in this device.
 *
 *  @post   #AESCCM_addData()
 */
int_fast16_t AESCCMLPF3HSM_setMac(AESCCM_Handle handle, const uint8_t *mac, size_t macLength);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aesccm_AESCCMLPF3__include */
