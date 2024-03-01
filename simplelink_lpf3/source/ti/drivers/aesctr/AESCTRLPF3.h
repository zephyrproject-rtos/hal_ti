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
 *  @file       AESCTRLPF3.h
 *
 *  @brief      AESCTR driver implementation for the Low Power F3 family
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
 *
 *  # Runtime Parameter Validation #
 *  The driver implementation does not perform runtime checks for most input parameters.
 *  Only values that are likely to have a stochastic element to them are checked (such
 *  as whether a driver is already open). Higher input parameter validation coverage is
 *  achieved by turning on assertions when compiling the driver.
 */

#ifndef ti_drivers_aesctr_AESCTRLPF3__include
#define ti_drivers_aesctr_AESCTRLPF3__include

#include <stdbool.h>
#include <stdint.h>

#include <ti/drivers/AESCTR.h>
#include <ti/drivers/cryptoutils/aes/AESCommonLPF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/aes.h)

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Default AES CTR auto config:
 *  ECB SRC as BUF
 *  Trigger points for auto ECB as RDTX3 and WRBUF3S
 *   (the first encryption starts by writing BUF3, the successive ones by reading TXT3)
 *  Counter size as 128-bits
 *  Counter endianness as Big Endian
 *  BUSHALT enabled
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    #define AES_AUTOCFG_CTRENDN_BIGENDIAN AES_AUTOCFG_CTRENDIAN_BIGENDIAN
#endif

#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESCTRLPF3_DEFAULT_AUTOCFG                                                \
        ((uint32_t)AES_AUTOCFG_AESSRC_BUF | (uint32_t)AES_AUTOCFG_TRGAES_WRBUF3S |    \
         (uint32_t)AES_AUTOCFG_TRGAES_RDTXT3 | (uint32_t)AES_AUTOCFG_CTRSIZE_CTR128 | \
         (uint32_t)AES_AUTOCFG_CTRENDN_BIGENDIAN | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESCTRLPF3_DEFAULT_AUTOCFG                                                \
        ((uint32_t)AES_AUTOCFG_ECBSRC_BUF | (uint32_t)AES_AUTOCFG_TRGECB_WRBUF3S |    \
         (uint32_t)AES_AUTOCFG_TRGECB_RDTXT3 | (uint32_t)AES_AUTOCFG_CTRSIZE_CTR128 | \
         (uint32_t)AES_AUTOCFG_CTRENDN_BIGENDIAN | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#else
    #error "Unsupported DeviceFamily_Parent for AESCTRLPF3!"
#endif

/*
 * AES CTR auto config for handling processing of the last
 * block of input to avoid starting encryption of the next counter block and
 * incrementing the counter value when the output is read from TXT3.
 *
 *  ECB SRC as BUF
 *  Trigger for auto ECB as WRBUF3S
 *   (the first encryption starts by writing BUF3)
 *  Counter size as 128-bits
 *  Counter endianness as Big Endian
 */
#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESCTRLPF3_LAST_BLOCK_AUTOCFG                                                 \
        ((uint32_t)AES_AUTOCFG_AESSRC_BUF | (uint32_t)AES_AUTOCFG_TRGAES_WRBUF3S |        \
         (uint32_t)AES_AUTOCFG_CTRSIZE_CTR128 | (uint32_t)AES_AUTOCFG_CTRENDN_BIGENDIAN | \
         (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESCTRLPF3_LAST_BLOCK_AUTOCFG                                                 \
        ((uint32_t)AES_AUTOCFG_ECBSRC_BUF | (uint32_t)AES_AUTOCFG_TRGECB_WRBUF3S |        \
         (uint32_t)AES_AUTOCFG_CTRSIZE_CTR128 | (uint32_t)AES_AUTOCFG_CTRENDN_BIGENDIAN | \
         (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#else
    #error "Unsupported DeviceFamily_Parent for AESCTRLPF3!"
#endif

/*!
 *  @brief      AESCTRLPF3 Hardware Attributes
 *
 *  AESCTRLPF3 hardware attributes should be included in the board file
 *  and pointed to by the AESCTR_config struct.
 */
typedef AESCommonLPF3_HWAttrs AESCTRLPF3_HWAttrs;

/*!
 *  @brief      AESCTRLPF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    /* Common member first to allow struct to be cast to the common type */
    AESCommonLPF3_Object common;
    volatile uint32_t counter[AES_BLOCK_SIZE_WORDS];
    const uint8_t *input;
    uint8_t *output;
    size_t inputLength;
    size_t inputLengthRemaining;
    AESCTR_OperationUnion *operation;
    AESCTR_CallbackFxn callbackFxn;
    AESCTR_OperationType operationType;
    bool threadSafe;
} AESCTRLPF3_Object;

/*! @cond NODOC */

/*!
 * @brief Processes the given input data using CPU R/W.
 *
 * @param [in]  input          Pointer to the input data
 * @param [out] output         Pointer to the output data
 * @param [in]  inputLength    Length of input data
 * @param [in]  isOneStepOrFinalOperation   Set to True for one-step or finalization
 *                                          operation, False otherwise.
 *
 */
void AESCTRLPF3_processData(const uint8_t *input, uint8_t *output, size_t inputLength, bool isOneStepOrFinalOperation);

/*!
 * @brief Configures the DMA to process the given input data.
 *        #AESCTRLPF3_writeCounter must be called to start the operation
 *
 * @param [in]  object         Pointer to an AESCommonLPF3_Object
 * @param [in]  input          Pointer to the input data
 * @param [out] output         Pointer to the output data
 * @param [in]  inputLength    Length of input data
 *
 * @return The number of bytes processed - a multiple of AES_BLOCK_SIZE.
 */
size_t AESCTRLPF3_configDataDMA(AESCommonLPF3_Object *object,
                                const uint8_t *input,
                                uint8_t *output,
                                size_t inputLength);

/*!
 * @brief Reads the latest counter value from the AES HW.
 *
 * @note  AES HW must be idle (i.e. no active encryption) when reading the counter value.
 *
 * @param [out] counterOut  Pointer to a block-sized array where the output counter should be stored.
 */
__STATIC_INLINE void AESCTRLPF3_readCounter(uint32_t counterOut[AES_BLOCK_SIZE_WORDS])
{
    /* Read the latest counter value from the AES engine */
    AESReadBUF32(&counterOut[0]);
}

/*!
 * @brief Writes the given counter into the AES HW
 *
 * @param [in] counterIn  Pointer to a block-sized array of the input counter.
 */
__STATIC_INLINE void AESCTRLPF3_writeCounter(uint32_t counterIn[AES_BLOCK_SIZE_WORDS])
{
    AESWriteBUF32(&counterIn[0]);
}

/*! @endcond */

/*!
 *  @cond NODOC
 *
 *  @brief Acquire Lock on Crypto Resource. This is an internal function that
 *         that may be called by other drivers to handle thread safety directly.
 *
 *  @param  [in] handle   An AESCTR handle
 *  @param  [in] timeout   Timeout (in ClockP ticks) to wait for the semaphore.
 *      - @ref SemaphoreP_WAIT_FOREVER
 *      - @ref SemaphoreP_NO_WAIT
 *
 *  @return true  - Succeeded acquiring the lock on crypto resource
 *          false - Failed to acquire the lock on crypto resource
 */
__STATIC_INLINE bool AESCTR_acquireLock(AESCTR_Handle handle, uint32_t timeout)
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
 *  @param  [in] handle   An AESCTR handle
 */
__STATIC_INLINE void AESCTR_releaseLock(AESCTR_Handle handle)
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
 *  @param  [in] handle   An AESCTR handle
 */
__STATIC_INLINE void AESCTR_enableThreadSafety(AESCTR_Handle handle)
{
    AESCTRLPF3_Object *object = handle->object;
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
 *  @param  [in] handle   An AESCTR handle
 */
__STATIC_INLINE void AESCTR_disableThreadSafety(AESCTR_Handle handle)
{
    AESCTRLPF3_Object *object = handle->object;
    object->threadSafe        = false;
}
/*! @endcond */

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aesctr_AESCTRLPF3__include */
