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
 *  @file       SHA2XXF3HSM.h
 *
 *  @brief      SHA2 driver implementation for the XXF3 HSM family
 *
 *  @note On CC27XX/CC23X1 devices, SHA2-224 and SHA2-384 are not yet
 *        supported.
 *
 *  # CC35XX: Callback Mode Restrictions with External Memory
 *  On CC35XX devices, #SHA2_RETURN_BEHAVIOR_CALLBACK is not supported when the input
 *  buffer is in PSRAM or external flash and the input length exceeds the input
 *  bounce buffer size. Returns #SHA2_STATUS_UNSUPPORTED in that case.
 *  Use #SHA2_RETURN_BEHAVIOR_BLOCKING or #SHA2_RETURN_BEHAVIOR_POLLING instead.
 *  See #HSMXXF3_BounceBuffers.
 */
#ifndef ti_drivers_sha2_SHA2XXF3HSM__include
#define ti_drivers_sha2_SHA2XXF3HSM__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/SHA2.h>
#include <ti/devices/DeviceFamily.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! \cond Internal APIs */

#define SHA2XXF3HSM_MAX_BLOCK_SIZE_BYTES    (SHA2_BLOCK_SIZE_BYTES_512)
#define SHA2XXF3HSM_MAX_DIGEST_LENGTH_BYTES (SHA2_DIGEST_LENGTH_BYTES_512)

/* The HSM's DMA Controller allows for an inputDataLength
 * of a DMA transfer to be 2^21 - 1 bytes.
 */
#define DMA_MAX_TXN_LENGTH 0x1FFFFFU

/*!
 *  @brief Hardware-specific configuration attributes
 *
 *  SHA2XXF3HSM hardware attributes are used in the board file by the
 *  #SHA2_Config struct.
 */
typedef struct
{
    uint8_t reserved1;
} SHA2XXF3HSM_HWAttrs;

/*!
 *  @brief SHA2XXF3HSM Object
 *
 *  \note The application must not access any member variables of this structure!
 */
typedef struct
{
    CryptoKey *key;
    uint32_t tempAssetID;
    uint32_t keyAssetID;
    uint8_t digest[SHA2XXF3HSM_MAX_DIGEST_LENGTH_BYTES];
    uint8_t buffer[SHA2XXF3HSM_MAX_BLOCK_SIZE_BYTES];
    uint32_t accessTimeout;
    uint32_t bytesProcessed;
    uint32_t totalDataLength;
    int_fast16_t returnStatus;
    SHA2_CallbackFxn callbackFxn;
    SHA2_ReturnBehavior returnBehavior;
    SHA2_HashType hashType;
    uint8_t *input;
    uint8_t *output;
    size_t inputLength;
    size_t digestLength;
    uint16_t bytesInBuffer;
    uint8_t algorithm;
    uint8_t mode;
    bool isOpen;
    volatile bool operationInProgress;
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    bool driverCreatedKeyAsset;
#endif
} SHA2XXF3HSM_Object;

/*! \endcond */

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_sha2_SHA2XXF3HSM__include  */