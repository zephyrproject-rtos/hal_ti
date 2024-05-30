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
 *  @file       AESCMACLPF3.h
 *
 *  @brief      AESCMAC (CMAC & CBC-MAC) driver implementation for the Low Power F3 family
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

#ifndef ti_drivers_aescmac_AESCMACLPF3__include
#define ti_drivers_aescmac_AESCMACLPF3__include

#include <stdbool.h>
#include <stdint.h>

#include <ti/drivers/AESCMAC.h>
#include <ti/drivers/cryptoutils/aes/AESCommonLPF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/aes.h)

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Default AES CMAC & CBC-MAC auto config:
 *  ECB SRC as TXTXBUF
 *  Trigger point for auto ECB as WRBUF3 (encryption starts by writing BUF3)
 *  BUSHALT enabled
 */
#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESCMACLPF3_DEFAULT_AUTOCFG \
        ((uint32_t)AES_AUTOCFG_AESSRC_TXTXBUF | (uint32_t)AES_AUTOCFG_TRGAES_WRBUF3 | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESCMACLPF3_DEFAULT_AUTOCFG \
        ((uint32_t)AES_AUTOCFG_ECBSRC_TXTXBUF | (uint32_t)AES_AUTOCFG_TRGECB_WRBUF3 | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#else
    #error "Unsupported DeviceFamily_Parent for AESCMACLPF3!"
#endif

/*
 * AES CMAC DMA config:
 *  - ADRCHA = BUF0
 *  - TRGCHA = ECBSTART
 */
#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESCMACLPF3_DMA_CONFIG ((uint32_t)AES_DMA_ADRCHA_BUF0 | (uint32_t)AES_DMA_TRGCHA_AESSTART)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESCMACLPF3_DMA_CONFIG ((uint32_t)AES_DMA_ADRCHA_BUF0 | (uint32_t)AES_DMA_TRGCHA_ECBSTART)
#else
    #error "Unsupported DeviceFamily_Parent for AESCMACLPF3!"
#endif

#define AESCBCMACLPF3_DMA_CONFIG AESCMACLPF3_DMA_CONFIG

/*!
 *  @brief      AESCMACLPF3 Hardware Attributes
 *
 *  AESCMACLPF3 hardware attributes should be included in the board file
 *  and pointed to by the AESCMAC_config struct.
 */
typedef AESCommonLPF3_HWAttrs AESCMACLPF3_HWAttrs;

/*!
 *  @brief      AESCMACLPF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    /* Common member first to allow struct to be cast to the common type */
    AESCommonLPF3_Object common;
    volatile uint32_t intermediateTag[AES_TAG_LENGTH_BYTES / 4U];
    uint32_t finalInputBlock[AES_BLOCK_SIZE_WORDS];
    AESCMAC_CallbackFxn callbackFxn;
    AESCMAC_Operation *operation;
    AESCMAC_OperationType operationType;
    AESCMAC_OperationalMode operationalMode;
    bool threadSafe;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    size_t inputLength;
    /*!
     * @brief The staus of the HSM Boot up process
     * if HSMLPF3_STATUS_SUCCESS, the HSM booted properly.
     * if HSMLPF3_STATUS_ERROR, the HSM did not boot properly.
     */
    int_fast16_t hsmStatus;
    uint32_t tempAssetID;
    uint32_t keyAssetID;
    /* To indicate whether a segmented operation is in progress
     */
    bool segmentedOperationInProgress;
#endif
} AESCMACLPF3_Object;

/*! @cond NODOC */

/*!
 * @brief Processes the input blocks to generate the tag
 *
 * @param [in] input                Pointer to the input data
 * @param [in] transactionLength    Length of the input to process. Should be a block-size multiple.
 *
 * @return none
 */
void AESCMACLPF3_processBlocks(const uint8_t *input, size_t transactionLength);

/*!
 * @brief Waits for the AES HW computation to complete and reads the tag output
 *
 * @param [out] tagOut  Pointer to a block-sized array where the output tag should be stored.
 *
 * @return none
 */
void AESCMACLPF3_readTag(uint32_t tagOut[AES_TAG_LENGTH_BYTES / 4U]);

/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Acquire Lock on Crypto Resource. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @param  [in] handle   AESCMAC handle
 *  @param  [in] timeout  Timeout (in ClockP ticks) to wait for the semaphore.
 *      - @ref SemaphoreP_WAIT_FOREVER
 *      - @ref SemaphoreP_NO_WAIT
 *
 *  @return true  - Succeeded acquiring the lock on crypto resource
 *          false - Failed to acquire the lock on crypto resource
 */
__STATIC_INLINE bool AESCMAC_acquireLock(AESCMAC_Handle handle, uint32_t timeout)
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
 *  @param  [in] handle   AESCMAC handle
 */
__STATIC_INLINE void AESCMAC_releaseLock(AESCMAC_Handle handle)
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
 *  @param  [in] handle   AESCMAC handle
 */
__STATIC_INLINE void AESCMAC_enableThreadSafety(AESCMAC_Handle handle)
{
    AESCMACLPF3_Object *object = handle->object;
    object->threadSafe         = true;
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
 *  @param  [in] handle   AESCMAC handle
 */
__STATIC_INLINE void AESCMAC_disableThreadSafety(AESCMAC_Handle handle)
{
    AESCMACLPF3_Object *object = handle->object;
    object->threadSafe         = false;
}
/*! @endcond */

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aescmac_AESCMACLPF3__include */
