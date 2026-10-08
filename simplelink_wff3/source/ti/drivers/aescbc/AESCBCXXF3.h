/*
 * Copyright (c) 2021-2026 Texas Instruments Incorporated
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
 *  @file       AESCBCXXF3.h
 *
 *  @brief      AESCBC driver implementation for the Low Power F3 devices
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
 *  - Decryption is not supported since the AES HW only supports encryption.
 *  - Only plaintext CryptoKeys are supported by this implementation.
 *
 *  # CC35XX: Callback Mode Restrictions with External Memory
 *  On CC35XX devices, #AESCBC_RETURN_BEHAVIOR_CALLBACK is not supported when
 *  the input or output buffer is in PSRAM and the data length exceeds the
 *  bounce buffer chunk size (min of input/output bounce buffer sizes, rounded
 *  down to an AES block boundary). This applies to one-step operations
 *  (#AESCBC_oneStepEncrypt / #AESCBC_oneStepDecrypt) as well as segmented
 *  operations (#AESCBC_addData / #AESCBC_finalize).
 *
 *  Returns #AESCBC_STATUS_FEATURE_NOT_SUPPORTED in that case.
 *  Use #AESCBC_RETURN_BEHAVIOR_BLOCKING or #AESCBC_RETURN_BEHAVIOR_POLLING
 *  instead. See #HSMXXF3_BounceBuffers.
 *
 *  # Runtime Parameter Validation #
 *  The driver implementation does not perform runtime checks for most input
 *  parameters. Only values that are likely to have a stochastic element to
 *  them are checked (such as whether a driver is already open). Higher input
 *  parameter validation coverage is achieved by turning on assertions when
 *  compiling the driver.
 */

#ifndef ti_drivers_aescbc_AESCBCXXF3__include
#define ti_drivers_aescbc_AESCBCXXF3__include

#include <stdbool.h>
#include <stdint.h>

#include <ti/drivers/AESCBC.h>
#include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceXXF3.h>
#include <ti/devices/DeviceFamily.h>

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    #include DeviceFamily_constructPath(driverlib/aes.h)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief      AESCBCXXF3 Hardware Attributes
 *
 *  AESCBCXXF3 hardware attributes should be included in the board file
 *  and pointed to by the AESCBC_config struct.
 */
typedef AESCommonXXF3_HWAttrs AESCBCXXF3_HWAttrs;

/*!
 *  @brief      AESCBCXXF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    /* Common member first to allow struct to be cast to the common type */
    AESCommonXXF3_Object common;
    volatile uint32_t iv[AES_IV_LENGTH_BYTES / 4];
    const uint8_t *input;
    uint8_t *output;
    AESCBC_CallbackFxn callbackFxn;
    AESCBC_OperationUnion *operation;
    AESCBC_OperationType operationType;
    bool threadSafe;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    size_t inputLength;
    /*!
     * @brief The status of the HSM Boot up process
     * if HSMXXF3_STATUS_SUCCESS, the HSM booted properly.
     * if HSMXXF3_STATUS_ERROR, the HSM did not boot properly.
     */
    int_fast16_t hsmStatus;
    uint32_t keyAssetID;
    /* Intentionally use implementation-independent uint32_t datatype for
     * keyLocation to avoid user dependencies on any implementation-specific
     * headers (e.g. mbedTLS). This data type must be large enough to hold any
     * implementation-specific keyLocation data.
     */
    uint32_t keyLocation;
    /* To indicate whether a segmented operation is in progress */
    bool segmentedOperationInProgress;
#endif
} AESCBCXXF3_Object;

/*!
 *  @cond NODOC
 *
 *  @brief Acquire Lock on Crypto Resource. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @param  [in] handle   AESCBC handle
 *  @param  [in] timeout  Timeout (in ClockP ticks) to wait for the semaphore.
 *      - @ref SemaphoreP_WAIT_FOREVER
 *      - @ref SemaphoreP_NO_WAIT
 *
 *  @return true  - Succeeded acquiring the lock on crypto resource
 *          false - Failed to acquire the lock on crypto resource
 */
__STATIC_INLINE bool AESCBC_acquireLock(AESCBC_Handle handle, uint32_t timeout)
{
    return CryptoResourceXXF3_acquireLock(timeout);
}
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Release Lock on Crypto Resource. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @param  [in] handle   AESCBC handle
 */
__STATIC_INLINE void AESCBC_releaseLock(AESCBC_Handle handle)
{
    CryptoResourceXXF3_releaseLock();
}
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Enable thread safety. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @param  [in] handle   AESCBC handle
 */
__STATIC_INLINE void AESCBC_enableThreadSafety(AESCBC_Handle handle)
{
    AESCBCXXF3_Object *object = (AESCBCXXF3_Object *)handle->object;
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
 *  @param  [in] handle   AESCBC handle
 */
__STATIC_INLINE void AESCBC_disableThreadSafety(AESCBC_Handle handle)
{
    AESCBCXXF3_Object *object = (AESCBCXXF3_Object *)handle->object;
    object->threadSafe        = false;
}
/*! @endcond */

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aesmode_AESCBCXXF3__include */
