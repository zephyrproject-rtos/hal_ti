/*
 * Copyright (c) 2021-2023, Texas Instruments Incorporated
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
 *  # Hardware Accelerator #
 *  The Low Power F3 family of devices has a dedicated AES hardware that can perform
 *  AES encryption operations with 128-bit keys. Only one operation
 *  can be carried out on the accelerator at a time. Mutual exclusion is
 *  implemented at the driver level and coordinated between all drivers relying on
 *  the accelerator. It is transparent to the application and only noted to ensure
 *  sensible access timeouts are set.
 *
 *  # Implementation Limitations
 *  - Only plaintext CryptoKeys are supported by this implementation.
 *  - Maximum AAD length is limited to 65279-bytes.
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
} AESCCMLPF3_Object;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aesccm_AESCCMLPF3__include */
