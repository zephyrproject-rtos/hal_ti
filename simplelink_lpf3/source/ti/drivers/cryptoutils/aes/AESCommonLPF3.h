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
 *  @file       AESCommonLPF3.h
 *
 *  @brief      AESCommon driver implementation for the Low Power F3 family
 *
 *  The AESCommonLPF3 module provides common functionality used by the
 *  AES mode-specific implementations for the Low Power F3 family.
 */

#ifndef ti_drivers_aescommon_AESCommonLPF3__include
#define ti_drivers_aescommon_AESCommonLPF3__include

#include <stdbool.h>
#include <stdint.h>

#include <ti/drivers/AESCommon.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Unaligned input/output pointer arguments are not supported by default
 * because the performance will be up to 5x slower. Enabling unaligned I/O
 * is strongly discouraged.
 */
#ifndef AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE
    #define AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE 0
#endif

/* DMA Channel Numbers */
#define DMA_CH4 4U
#define DMA_CH5 5U

/* DMA Channel 4 is reserved for AES Channel A (input) */
#define AESCommonLPF3_DMA_CHA_BITMASK ((uint32_t)1U << DMA_CH4)
/* DMA Channel 5 is reserved for AES Channel B (output) */
#define AESCommonLPF3_DMA_CHB_BITMASK ((uint32_t)1U << DMA_CH5)

/*!
 *  @brief      AESCommonLPF3 Hardware Attributes
 */
typedef struct
{
    /*!
     * @brief Crypto Peripheral's interrupt priority.
     *
     * The Low Power F3 devices use either three or two priority bits,
     * depending on the device. That means ~0 has the same effect as (7 << 5)
     * or (3 << 6), respectively.
     *
     * Setting the priority to 0 is not supported by this driver.
     *
     * HWI's with priority 0 ignore the HWI dispatcher to support zero-latency
     * interrupts, thus invalidating the critical sections in this driver.
     */
    uint8_t intPriority;
} AESCommonLPF3_HWAttrs;

/*!
 *  @brief      AESCommonLPF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    uint32_t semaphoreTimeout;
    CryptoKey key;
    volatile int_fast16_t returnStatus;
    AES_ReturnBehavior returnBehavior;
    bool isOpen;
    volatile bool cryptoResourceLocked;
    volatile bool operationInProgress;
    volatile bool powerConstraintSet;
} AESCommonLPF3_Object;

/*!
 *  @cond NODOC
 *
 *  @brief  Initializes the common Crypto Resource RTOS objects used by AES drivers.
 *
 *  @note   The RTOS objects are common to all AES modes and are initialized
 *          only once.
 */
void AESCommonLPF3_init(void);

/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Constructs a new driver instance.
 *
 *  @param [in] object         #AESCommonLPF3_Object to configure the driver
 *                             instance.
 *  @param [in] returnBehavior #AES_ReturnBehavior to configure the driver
 *                              instance.
 *  @param [in] timeout        timeout to configure the driver instance.
 */
int_fast16_t AESCommonLPF3_construct(AESCommonLPF3_Object *object, AES_ReturnBehavior returnBehavior, uint32_t timeout);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Loads the Key material into the AES HW
 *
 *  @param [in] key         Pointer to the CryptoKey object containing the keyMaterial
 */
void AESCommonLPF3_loadKey(const CryptoKey *key);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Initializes the key and autoCFG values for an AES operation.
 *
 *  @param [in] key         Pointer to the CryptoKey object containing the keyMaterial
 *  @param [in] autoCfgVal  The AUTOCFG value to be set.
 */
void AESCommonLPF3_setupOperation(CryptoKey *key, uint32_t autoCfgVal);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Closes a given driver instance.
 *
 *  @param  [in] object  Pointer to an AESCommonLPF3 object
 *
 */
void AESCommonLPF3_close(AESCommonLPF3_Object *object);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Marks an operation to be in progress.
 *
 *  @param  [in] object  Pointer to an AESCommonLPF3 object
 *
 *  @retval AES_STATUS_SUCCESS  Successfully set operation in progress
 *  @retval AES_STATUS_ERROR    Another operation already in progress
 */
int_fast16_t AESCommonLPF3_setOperationInProgress(AESCommonLPF3_Object *object);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Clears an operation to be in progress.
 *
 *  @param  [in] object  Pointer to an AESCommonLPF3 object
 *
 */
__STATIC_INLINE void AESCommonLPF3_clearOperationInProgress(AESCommonLPF3_Object *object)
{
    object->operationInProgress = false;
}
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Cleans up the driver object fields that can be reset
 *         in common across all AES modes after an operation is done
 *         and also releases the lock on the crypto resource.
 *
 *  @param  [in] object  Pointer to an AESCommonLPF3 object
 *
 *  @retval none
 */
void AESCommonLPF3_cleanup(AESCommonLPF3_Object *object);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Sets up a segmented operation.
 *
 *  @param [in] object  Pointer to an #AESCommonLPF3_Object
 *  @param [in] key     Pointer to the CryptoKey object to store in object
 */
int_fast16_t AESCommonLPF3_setupSegmentedOperation(AESCommonLPF3_Object *object, const CryptoKey *key);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Checks whether the data length is valid for the given \a input and
 *          \a output pointers.
 *
 *  @param [in] input     Pointer to the input data
 *  @param [in] output    Pointer to the output data
 *  @param [in] length    Length of the data in bytes
 *
 *  @return true if length is valid, false otherwise.
 */
bool AESCommonLPF3_isDMALengthValid(const void *input, const void *output, size_t length);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Configures the AES input DMA channel A for a transfer.
 *
 *  @note Max \a inputLength depends on the alignment of the \a input pointer.
 *        If \a input is word-aligned, max \a inputLength is 4KB.
 *        If \a input is halfword-aligned, max \a inputLength is 2KB.
 *        If \a input is byte-aligned, max \a inputLength is 1KB.
 *        \a inputLength be a multiple of AES_BLOCK_SIZE for proper triggering.
 *
 *  @param [in] input              Pointer to the input data
 *  @param [in] inputLength        Length of the input data in bytes,
 *                                 Must be a multiple of AES_BLOCK_SIZE.
 */
void AESCommonLPF3_configInputDMA(const void *input, size_t inputLength);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Configures the AES output DMA channel B for a transfer.
 *
 *  @note Max \a outputLength depends on the alignment of the \a output pointer.
 *        If \a output is word-aligned, max \a outputLength is 4KB.
 *        If \a output is halfword-aligned, max \a outputLength is 2KB.
 *        If \a output is byte-aligned, max \a outputLength is 1KB.
 *        \a outputLength must match the \a inputLength used to call
 *        #AESCommonLPF3_configInputDMA.
 *
 *  @param [out] output              Pointer to the output data
 *  @param [in]  outputLength        Length of the output data in bytes,
 *                                   Must be a multiple of AES_BLOCK_SIZE.
 */
void AESCommonLPF3_configOutputDMA(void *output, size_t outputLength);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Cancels the AES input channels A. If \a cancelChannelB is true,
 *          cancels AES output DMA channel B as well.
 *
 *  @param [in]  object              Pointer to an #AESCommonLPF3_Object
 *  @param [out] cancelChannelB      Boolean indicating whether DMA Channel B should be cancelled
 */
void AESCommonLPF3_cancelDMA(bool cancelChannelB);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Handles common cancellation operations: <br>
 *          1) Cancels DMA channel(s) <br>
 *          2) Sets return status <br>
 *          3) Clears operation in-progress flag <br>
 *          4) Releases crypto resource lock
 *
 *  @param [in]  object              Pointer to an #AESCommonLPF3_Object
 *  @param [out] cancelDMAChannelB   Boolean indicating whether DMA Channel B should be cancelled
 */
void AESCommonLPF3_cancelOperation(AESCommonLPF3_Object *object, bool cancelDMAChannelB);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Sets the callback function, interrupt priority and enables the AES interrupt.
 *
 *  @param [in] hwiFxn       Interrupt callback function
 *  @param [in] hwiFxnArg    Interrupt callback function argument
 *  @param [in] intPriority  Interrupt priority
 */
void AESCommonLPF3_setupHwi(HwiP_Fxn hwiFxn, uintptr_t hwiFxnArg, uint8_t intPriority);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Clears and disables AES interrupts and release power constraint if set.
 *
 *  @param [in]  object      Pointer to an #AESCommonLPF3_Object
 */
void AESCommonLPF3_cleanupHwi(AESCommonLPF3_Object *object);
/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief  Sets the AES DMA configuration and sets power constraint.
 *
 *  @param [in]  object      Pointer to an #AESCommonLPF3_Object
 *  @param [in]  dmaConfig   AES DMA configuration
 */
void AESCommonLPF3_setupDMA(AESCommonLPF3_Object *object, uint32_t dmaConfig);
/*! @endcond */

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aescommon_AESCommonLPF3__include */
