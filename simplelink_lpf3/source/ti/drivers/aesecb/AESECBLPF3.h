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
 *  @file       AESECBLPF3.h
 *
 *  @brief      AESECB driver implementation for the Low Power F3 family
 *
 *  # Hardware Accelerator #
 *  The Low Power F3 family of devices has a dedicated AES hardware that can perform
 *  AES encryption operations with 128-bit keys. Only one operation
 *  can be carried out on the accelerator at a time. Mutual exclusion is
 *  implemented at the driver level and coordinated between all drivers
 *  relying on the accelerator. It is transparent to the application and only
 *  noted to ensure sensible access timeouts are set.
 *
 *  # Implementation Limitations
 *  - Decryption is not supported since the AES HW only supports encryption.
 *  - Only plaintext CryptoKeys are supported by this implementation.
 *
 *  # Runtime Parameter Validation #
 *  The driver implementation does not perform runtime checks for most input
 *  parameters. Only values that are likely to have a stochastic element to
 *  them are checked (such as whether a driver is already open). Higher input
 *  parameter validation coverage is achieved by turning on assertions when
 *  compiling the driver.
 */

#ifndef ti_drivers_aesecb_AESECBLPF3__include
#define ti_drivers_aesecb_AESECBLPF3__include

#include <stdbool.h>
#include <stdint.h>

#include <ti/drivers/AESECB.h>
#include <ti/drivers/cryptoutils/aes/AESCommonLPF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The threshold at which blocking and callback mode transfers will utilize DMA.
 * For data lengths below this threshold, polling CPU R/W will be used instead
 * of DMA. With task switching and interrupt overhead, it is inefficient to
 * utilize DMA for shorter length operations.
 * The threshold value must be a multiple of AES_BLOCK_SIZE.
 */
#define AESECBLPF3_DMA_SIZE_THRESHOLD (1U * AES_BLOCK_SIZE)

/*
 * AES ECB auto config for a single block encryption:
 *  ECB SRC as BUF
 *  Trigger points for auto ECB as WRBUF3S (encryption starts by writing BUF3)
 *  BUSHALT enabled
 */
#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESEBCLPF3_SINGLE_BLOCK_AUTOCFG \
        ((uint32_t)AES_AUTOCFG_AESSRC_BUF | (uint32_t)AES_AUTOCFG_TRGAES_WRBUF3S | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESEBCLPF3_SINGLE_BLOCK_AUTOCFG \
        ((uint32_t)AES_AUTOCFG_ECBSRC_BUF | (uint32_t)AES_AUTOCFG_TRGECB_WRBUF3S | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#else
    #error "Unsupported DeviceFamily_Parent for AESECBLPF3!"
#endif

/*!
 *  @brief      AESECBLPF3 Hardware Attributes
 *
 *  AESECBLPF3 hardware attributes should be included in the board file
 *  and pointed to by the AESECB_config struct.
 */
typedef AESCommonLPF3_HWAttrs AESECBLPF3_HWAttrs;

/*!
 *  @brief      AESECBLPF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    /* Common member first to allow struct to be cast to the common type */
    AESCommonLPF3_Object common;
    AESECB_Operation *operation;
    AESECB_CallbackFxn callbackFxn;
    AESECB_OperationType operationType;
    bool threadSafe;
} AESECBLPF3_Object;

/*!
 *  @cond NODOC
 *
 *  @brief Helper function to encrypt plaintext input
 *
 *      Writes the first block of data and calls #AESECBLPF3_processBlock()
 *
 *  @note This will be reused for AES CBC mode which is why it's exposed here.
 *
 *  @param [in]  object       Pointer to an #AESCommonLPF3_Object to track if
 *                            a HW operation is in progress
 *  @param [in]  input        Plaintext input to be encrypted
 *  @param [out] output       Buffer to store the decrypted ciphertext
 *  @param [in]  inputLength  Length of input to be encrypted
 */
void AESECBLPF3_processData(AESCommonLPF3_Object *object, const uint8_t *input, uint8_t *output, size_t inputLength);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Acquire Lock on Crypto Resource. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @param  [in] handle   AESECB handle
 *  @param  [in] timeout  Timeout (in ClockP ticks) to wait for the semaphore.
 *      - @ref SemaphoreP_WAIT_FOREVER
 *      - @ref SemaphoreP_NO_WAIT
 *
 *  @return true  - Succeeded acquiring the lock on crypto resource
 *          false - Failed to acquire the lock on crypto resource
 */
__STATIC_INLINE bool AESECB_acquireLock(AESECB_Handle handle, uint32_t timeout)
{
    return CryptoResourceLPF3_acquireLock(timeout);
}
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Release Lock on Crypto Resource. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @param  [in] handle   AESECB handle
 */
__STATIC_INLINE void AESECB_releaseLock(AESECB_Handle handle)
{
    CryptoResourceLPF3_releaseLock();
}
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Enable thread safety. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @param  [in] handle   AESECB handle
 */
__STATIC_INLINE void AESECB_enableThreadSafety(AESECB_Handle handle)
{
    AESECBLPF3_Object *object = handle->object;
    object->threadSafe        = true;
}
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Disable thread safety. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @note The user is responsible for reenabling thread safety after being
 *        done with the need for this driver.
 *
 *  @param  [in] handle   AESECB handle
 */
__STATIC_INLINE void AESECB_disableThreadSafety(AESECB_Handle handle)
{
    AESECBLPF3_Object *object = handle->object;
    object->threadSafe        = false;
}
/*! @endcond */

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aesecb_AESECBLPF3__include */
