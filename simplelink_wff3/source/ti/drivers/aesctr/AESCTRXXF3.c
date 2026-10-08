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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <ti/drivers/aesctr/AESCTRXXF3.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceXXF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>

#include <ti/devices/DeviceFamily.h>

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    #include <ti/drivers/dma/UDMALPF3.h>
    #include DeviceFamily_constructPath(driverlib/aes.h)
    #include DeviceFamily_constructPath(inc/hw_aes.h)
    #include DeviceFamily_constructPath(inc/hw_ints.h)
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) && (ENABLE_KEY_STORAGE == 1))
    #error "Key storage is not supported for CC23X0"
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #if (ENABLE_KEY_STORAGE == 1)
        /* These includes must come before hsmddk/include/Integration/Adapter_PSA includes */
        #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
        #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
    #endif
    /* Using LPF3 driver implementation for WFF3, since the HSM IP is the same. */
    #include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        #include <ti/drivers/xmem/XMEMWFF3.h>
        #include <ti/drivers/utils/Math.h>
    #endif
    #include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>
    #include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
    #include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_result.h>
    #include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_asset.h>
#endif

/**
 * The threshold at which blocking and callback mode transfers will utilize DMA.
 * For data lengths below this threshold, polling CPU R/W will be used instead
 * of DMA. With task switching and interrupt overhead, it is inefficient to
 * utilize DMA for shorter length operations.
 * The threshold value must be a multiple of AES_BLOCK_SIZE.
 */
#define AESCTRXXF3_DMA_SIZE_THRESHOLD (1U * AES_BLOCK_SIZE)

/*
 * AES DMA configuration to use when data length is not a block multiple and
 * the partial block of input/output remaining will be completed via CPU R/W.
 *
 * DMA channel A moves m[1:x] into TXTX when ECB completes
 *
 *    ADRCHA = TXTX0
 *    TRGCHA = ECBDONE
 *
 * DMA channel B moves ciphertext[1:x] to memory after channel A has written TXTX3.
 *
 *    ADRCHB = TXT0
 *    TRGCHB = WRTXT3
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #define AESCTRXXF3_DMA_CONFIG                                                                            \
        ((uint32_t)AES_DMA_ADRCHA_TXTX0 | (uint32_t)AES_DMA_TRGCHA_AESDONE | (uint32_t)AES_DMA_ADRCHB_TXT0 | \
         (uint32_t)AES_DMA_TRGCHB_WRTXT3)
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/* Not used for CC35XX. */
#else
    #error "Unsupported DeviceFamily_Parent for AESCTRXXF3!"
#endif

/*
 * AES DMA configuration to use when data length is exactly a block multiple.
 *
 * DMA channel A moves m[1:x] into TXTX when ECB completes
 *
 *    ADRCHA = TXTX0
 *    TRGCHA = ECBDONE
 *    DONEACT = GATE_TRGECB_ON_CHA (to avoid spurious last ECB using DMA)
 *
 * DMA channel B moves ciphertext[1:x] to memory after channel A has written TXTX3.
 *
 *    ADRCHB = TXT0
 *    TRGCHB = WRTXT3
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #define AESCTRXXF3_GATE_CHA_DMA_CONFIG (AESCTRXXF3_DMA_CONFIG | (uint32_t)AES_DMA_DONEACT_GATE_TRGAES_ON_CHA)
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/* Not used for CC35XX. */
#else
    #error "Unsupported DeviceFamily_Parent for AESCTRXXF3!"
#endif

/* Forward declarations */
static void AESCTRXXF3_initCounter(AESCTRXXF3_Object *object, const uint8_t initialCounter[AES_BLOCK_SIZE]);
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
static int_fast16_t AESCTRXXF3_oneStepOperation(AESCTR_Handle handle,
                                                AESCTR_OneStepOperation *operation,
                                                AESCTR_OperationType operationType);
static int_fast16_t AESCTRXXF3_startOperation(AESCTR_Handle handle, bool isOneStepOrFinalOperation);
static int_fast16_t AESCTRXXF3_waitForResult(AESCTR_Handle handle);
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
static int_fast16_t AESCTRXXF3HSM_oneStepOperation(AESCTR_Handle handle,
                                                   AESCTR_OneStepOperation *operation,
                                                   AESCTR_OperationType operationType);

static int_fast16_t AESCTRXXF3HSM_processOneStepOperation(AESCTR_Handle handle);

int_fast16_t AESCTRXXF3HSM_addData(AESCTR_Handle handle, AESCTR_SegmentedOperation *operation);

int_fast16_t AESCTRXXF3HSM_finalize(AESCTR_Handle handle, AESCTR_SegmentedOperation *operation);
    #if (ENABLE_KEY_STORAGE == 1)
static int_fast16_t AESCTRXXF3HSM_freeAllAssets(AESCTR_Handle handle);
    #endif
#endif

/*
 *  ======== AESCTRXXF3_getObject ========
 */
static inline AESCTRXXF3_Object *AESCTRXXF3_getObject(AESCTR_Handle handle)
{
    AESCTRXXF3_Object *object = (AESCTRXXF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCTRXXF3_hwiFxn ========
 */
static void AESCTRXXF3_hwiFxn(uintptr_t arg0)
{
    AESCTR_Handle handle      = (AESCTR_Handle)arg0;
    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);

    /*
     * Only the output channel B interrupt is enabled.
     */
    uint32_t intStatus = AESGetMaskedInterruptStatus();

    /* Disable DMA, clear interupts, and release power constraint */
    AESCommonXXF3_cleanupHwi(&object->common);

    if ((intStatus & (uint32_t)AES_MIS_CHBDONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonXXF3_DMA_CHB_BITMASK);

        if ((object->inputLengthRemaining > 0U) && (object->inputLengthRemaining < AESCTRXXF3_DMA_SIZE_THRESHOLD))
        {
            /* Use CPU R/W to complete the CTR operation */
            AESCTRXXF3_processData(&object->input[object->inputLength - object->inputLengthRemaining],
                                   &object->output[object->inputLength - object->inputLengthRemaining],
                                   object->inputLengthRemaining,
                                   true);

            object->inputLengthRemaining = 0U;
        }

        if (object->inputLengthRemaining > 0U)
        {
            /*
             * If DMA Ping-Pong mode is supported in the future:
             *  - Set power contraint
             *  - Setup next DMA control struct to continue CTR operation
             */
        }

        /* Save the last counter value from the AES engine */
        AESCTRXXF3_readCounter((uint32_t *)&object->counter[0]);

        /* Check if one-step or final operation */
        if ((object->operationType & AESCTR_OP_FLAG_SEGMENTED) == 0)
        {
            AESCommonXXF3_clearOperationInProgress(&object->common);
        }

        /* Cleanup and release crypto resource lock */
        AESCommonXXF3_cleanup(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_BLOCKING)
        {
            /* Unblock the pending task to signal that the operation is complete */
            SemaphoreP_post(&CryptoResourceXXF3_operationSemaphore);
        }
        else
        {
            /* Call the callback function provided by the application */
            object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
        }
    }
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCTR_init ========
 */
void AESCTR_init(void)
{
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    HSMXXF3_constructRTOSObjects();
#endif
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCommonXXF3_init();
#endif
}

/*
 *  ======== AESCTR_construct ========
 */
AESCTR_Handle AESCTR_construct(AESCTR_Config *config, const AESCTR_Params *params)
{
    DebugP_assert(config);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    int_fast16_t status;
#endif
    AESCTR_Handle handle      = config;
    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Callback return mode is not supported for CC35XX for now */
    if ((params != NULL) && (params->returnBehavior == AESCTR_RETURN_BEHAVIOR_CALLBACK))
    {
        return NULL;
    }
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    /* Initialize and boot HSM */
    if (HSMXXF3_init() != HSMXXF3_STATUS_SUCCESS)
    {
        /* Upon HSM Boot failure, the AES-CCM Driver stores the failure status in the object
         * This is done so that users of the AES-CCM Driver do not get a NULL handle and still can use
         * the driver in LAES mode.
         */
        object->hsmStatus = HSMXXF3_STATUS_ERROR;
    }
    else
    {
        object->hsmStatus = HSMXXF3_STATUS_SUCCESS;
    }

    object->segmentedOperationInProgress = false;
#endif

    /* If params are NULL, use defaults */
    if (params == NULL)
    {
        params = &AESCTR_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AESCTR_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->callbackFxn = params->callbackFxn;
    object->threadSafe  = true;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Set common parameters for later use. */
    object->common.returnBehavior = (AES_ReturnBehavior)params->returnBehavior;

    object->common.isOpen = true;

    if (params->returnBehavior == AESCTR_RETURN_BEHAVIOR_BLOCKING)
    {
        object->common.semaphoreTimeout = params->timeout;
    }
    else
    {
        object->common.semaphoreTimeout = SemaphoreP_NO_WAIT;
    }
#else
    status = AESCommonXXF3_construct(&object->common, (AES_ReturnBehavior)params->returnBehavior, params->timeout);

    if (status != AES_STATUS_SUCCESS)
    {
        handle = NULL;
    }
#endif

    return handle;
}

/*
 *  ======== AESCTR_close ========
 */
void AESCTR_close(AESCTR_Handle handle)
{
    DebugP_assert(handle);

    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCommonXXF3_close(&object->common);
#else
    /* Mark the module as available */
    object->common.isOpen = false;
#endif
}

/*
 *  ======== AESCTR_oneStepEncrypt ========
 */
int_fast16_t AESCTR_oneStepEncrypt(AESCTR_Handle handle, AESCTR_OneStepOperation *operationStruct)
{
    int_fast16_t status;

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if (operationStruct->key->encoding == CryptoKey_PLAINTEXT || operationStruct->key->encoding == CryptoKey_KEYSTORE)
    {
        status = AESCTRXXF3_oneStepOperation(handle, operationStruct, AESCTR_OPERATION_TYPE_ENCRYPT);
    }
    else
#endif
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        if (operationStruct->key->encoding == CryptoKey_PLAINTEXT_HSM ||
            operationStruct->key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        status = AESCTRXXF3HSM_oneStepOperation(handle, operationStruct, AESCTR_OPERATION_TYPE_ENCRYPT);
    }
    else
#endif
    {
        status = AESCTR_STATUS_ERROR;
    }
    return status;
}

/*
 *  ======== AESCTR_oneStepDecrypt ========
 */
int_fast16_t AESCTR_oneStepDecrypt(AESCTR_Handle handle, AESCTR_OneStepOperation *operationStruct)
{
    int_fast16_t status;

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if ((operationStruct->key->encoding == CryptoKey_PLAINTEXT) ||
        (operationStruct->key->encoding == CryptoKey_KEYSTORE))
    {
        status = AESCTRXXF3_oneStepOperation(handle, operationStruct, AESCTR_OPERATION_TYPE_DECRYPT);
    }
    else
#endif
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        if ((operationStruct->key->encoding == CryptoKey_PLAINTEXT_HSM) ||
            (operationStruct->key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        status = AESCTRXXF3HSM_oneStepOperation(handle, operationStruct, AESCTR_OPERATION_TYPE_DECRYPT);
    }
    else
#endif
    {
        status = AESCTR_STATUS_ERROR;
    }
    return status;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCTRXXF3_oneStepOperation ========
 */
static int_fast16_t AESCTRXXF3_oneStepOperation(AESCTR_Handle handle,
                                                AESCTR_OneStepOperation *operation,
                                                AESCTR_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    /* No need to assert operationType since we control it within the driver */

    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    int_fast16_t status;

    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCTR_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
    #endif

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCTR_STATUS_ERROR;
    }

    /* Verify input length is non-zero */
    if (operation->inputLength == 0U)
    {
        return AESCTR_STATUS_ERROR;
    }

    /*
     * Check if there is no operation already in progress for this driver
     * instance, and then mark the current operation to be in progress.
     */
    status = AESCommonXXF3_setOperationInProgress(&object->common);

    if (status != AESCTR_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
        {
            AESCommonXXF3_clearOperationInProgress(&object->common);
            return AESCTR_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation           = (AESCTR_OperationUnion *)operation;
    object->operationType       = operationType;
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESCTR_STATUS_SUCCESS;

    /* Make internal copy of operational params */
    object->common.key           = *(operation->key);
    object->input                = operation->input;
    object->inputLength          = operation->inputLength;
    object->inputLengthRemaining = operation->inputLength;
    object->output               = operation->output;

    AESCTRXXF3_initCounter(object, &operation->initialCounter[0]);

    status = AESCTRXXF3_startOperation(handle, true);

    return status;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCTRXXF3_initCounter ========
 */
static void AESCTRXXF3_initCounter(AESCTRXXF3_Object *object, const uint8_t initialCounter[AES_BLOCK_SIZE])
{
    if (initialCounter != NULL)
    {
        (void)memcpy((void *)&object->counter[0], (void *)&initialCounter[0], sizeof(object->counter));
    }
    else
    {
        (void)memset((void *)&object->counter[0], 0, sizeof(object->counter));
    }
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCTRXXF3_startOperation ========
 */
static int_fast16_t AESCTRXXF3_startOperation(AESCTR_Handle handle, bool isOneStepOrFinalOperation)
{
    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    int_fast16_t status       = AESCTR_STATUS_SUCCESS;
    size_t bytesProcessed;
    #if (ENABLE_KEY_STORAGE == 1)
    int_fast16_t keyStoreStatus;
    uint8_t KeyStore_keyingMaterial[AESCommonXXF3_256_KEY_LENGTH_BYTES];
    KeyStore_PSA_KeyUsage usage = ((object->operationType & AESCTR_OP_MODE_MASK) == AESCTR_MODE_ENCRYPT)
                                      ? KEYSTORE_PSA_KEY_USAGE_ENCRYPT
                                      : KEYSTORE_PSA_KEY_USAGE_DECRYPT;
    #endif

    if (object->common.key.encoding == CryptoKey_PLAINTEXT)
    {
        /* Set up the key and AES engine to begin an operation */
        AESCommonXXF3_setupOperation(&object->common.key, AESCTRXXF3_DEFAULT_AUTOCFG);
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (object->common.key.encoding == CryptoKey_KEYSTORE)
    {
        keyStoreStatus = KeyStore_PSA_retrieveFromKeyStore(&object->common.key,
                                                           &KeyStore_keyingMaterial[0],
                                                           sizeof(KeyStore_keyingMaterial),
                                                           &object->keyAssetID,
                                                           KEYSTORE_PSA_ALG_CTR,
                                                           usage);

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
        {
            /* Write key material retrieved from KeyStore */
            AESWriteKEY(KeyStore_keyingMaterial);

            /* Set AUTOCFG */
            AESSetAUTOCFG(AESCTRXXF3_DEFAULT_AUTOCFG);
        }
        else if (keyStoreStatus == KEYSTORE_PSA_STATUS_INVALID_KEY_ID)
        {
            return AESCTR_STATUS_KEYSTORE_INVALID_ID;
        }
        else
        {
            return AESCTR_STATUS_KEYSTORE_GENERIC_ERROR;
        }
    }
    #endif
    else
    {
        return AESCTR_STATUS_FEATURE_NOT_SUPPORTED;
    }
    /*
     * Process all operations with data length less than the DMA size
     * threshold as a polling mode operation.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (object->inputLength < AESCTRXXF3_DMA_SIZE_THRESHOLD))
    {
        /* Write the counter value to the AES engine to trigger first encryption */
        AESCTRXXF3_writeCounter((uint32_t *)&object->counter[0]);

        /* Process all blocks with CPU R/W */
        AESCTRXXF3_processData(object->input, object->output, object->inputLength, isOneStepOrFinalOperation);

        object->inputLengthRemaining = 0U;
    }
    else
    {
        /*
         * We need to set the HWI function and priority since the same physical
         * interrupt is shared by multiple drivers and they all need to coexist.
         * Whenever a driver starts an operation, it registers its HWI callback
         * with the OS.
         */
        AESCTRXXF3_HWAttrs const *hwAttrs = handle->hwAttrs;
        AESCommonXXF3_setupHwi(AESCTRXXF3_hwiFxn, (uintptr_t)handle, hwAttrs->intPriority);

        bytesProcessed = AESCTRXXF3_configDataDMA(&object->common, object->input, object->output, object->inputLength);

        object->inputLengthRemaining -= bytesProcessed;

        /* Write the counter value to the AES engine to trigger first encryption */
        AESCTRXXF3_writeCounter((uint32_t *)&object->counter[0]);
    }

    status = AESCTRXXF3_waitForResult(handle);

    return status;
}

/*
 *  ======== AESCTRXXF3_configDataDMA ========
 */
size_t AESCTRXXF3_configDataDMA(AESCommonXXF3_Object *object, const uint8_t *input, uint8_t *output, size_t inputLength)
{
    size_t blockSizeDataLen = AES_BLOCK_SIZE_MULTIPLE_LENGTH(inputLength);

    /* Clear BUSHALT when using DMA */
    AESClearAUTOCFGBusHalt();

    /* Setup DMA configuration and set power constraint */
    if (blockSizeDataLen == inputLength)
    {
        AESCommonXXF3_setupDMA(object, AESCTRXXF3_GATE_CHA_DMA_CONFIG);
    }
    else
    {
        AESCommonXXF3_setupDMA(object, AESCTRXXF3_DMA_CONFIG);
    }

    /*
     * Only full blocks of data can be processed with DMA because the trigger
     * for DMA channel B (output) is based on channel A (input) writing the
     * last word of the TXTX register
     */
    AESCommonXXF3_configInputDMA(input, blockSizeDataLen);
    AESCommonXXF3_configOutputDMA(output, blockSizeDataLen);

    /* Enable interrupt upon output DMA done */
    AESSetIMASK((uint32_t)AES_IMASK_CHBDONE_M);

    return blockSizeDataLen;
}

/*
 *  ======== AESCTRXXF3_processData ========
 */
void AESCTRXXF3_processData(const uint8_t *input, uint8_t *output, size_t inputLength, bool isOneStepOrFinalOperation)
{
    size_t bytesProcessed                 = 0;
    size_t bytesRemaining                 = inputLength;
    size_t blockSizeAlignedBytesRemaining = AES_BLOCK_SIZE_MULTIPLE_LENGTH(inputLength);

    if (blockSizeAlignedBytesRemaining > 0U)
    {
        bytesRemaining -= blockSizeAlignedBytesRemaining;

    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
        if (!IS_WORD_ALIGNED(input) || !IS_WORD_ALIGNED(output))
        {
            do
            {
        #ifdef AES_BUSHALT_DISABLED
                /* Wait for encryption to complete */
                while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}
        #endif

                if ((blockSizeAlignedBytesRemaining == AES_BLOCK_SIZE) && (bytesRemaining == 0U))
                {
                    /*
                     * Do not auto-trigger encrypt and increment of counter
                     * value for last block of data.
                     */
                    AESSetAUTOCFG(AESCTRXXF3_LAST_BLOCK_AUTOCFG);
                }

                /* XOR input data with encrypted counter block to form ciphertext */
                AESWriteTXTXOR(&input[bytesProcessed]);

                /* Read the output ciphertext and trigger the encryption of the next counter block */
                AESReadTXT(&output[bytesProcessed]);

                bytesProcessed += AES_BLOCK_SIZE;
                blockSizeAlignedBytesRemaining -= AES_BLOCK_SIZE;

            } while (blockSizeAlignedBytesRemaining > 0U);
        }
        else
    #endif
        {
            /*
             * This optimization for word-aligned input & output is used to improve
             * performance for AES-CCM to ensure BLE stack can meet timing
             * requirements.
             */

            /* Safe to cast word-aligned input & output pointers */
            const uint32_t *input32 = (const uint32_t *)input;
            uint32_t *output32      = (uint32_t *)output;
            size_t inputBlocks      = AES_GET_NUM_BLOCKS(blockSizeAlignedBytesRemaining);

            if (!isOneStepOrFinalOperation && (bytesRemaining == 0U))
            {
                if (inputBlocks > 1U)
                {
                    /* Process all data except the last block */
                    AESProcessAlignedBlocksCTR(input32, output32, (uint32_t)inputBlocks - (uint32_t)1U);

                    input32  = (const uint32_t *)&input[blockSizeAlignedBytesRemaining - AES_BLOCK_SIZE];
                    output32 = (uint32_t *)&output[blockSizeAlignedBytesRemaining - AES_BLOCK_SIZE];
                }

                /*
                 * Do not auto-trigger encrypt and increment of counter
                 * value for last block of data.
                 */
                AESSetAUTOCFG(AESCTRXXF3_LAST_BLOCK_AUTOCFG);

                /* Process last block of data */
                AESProcessAlignedBlocksCTR(input32, output32, (uint32_t)1U);
            }
            else
            {
                /*
                 * Process all the data. This will trigger a spurious encryption
                 * when reading the final output which will be aborted during cleanup.
                 */
                AESProcessAlignedBlocksCTR(input32, output32, inputBlocks);
            }

            bytesProcessed = blockSizeAlignedBytesRemaining;
        }
    }

    /* Process any remaining partial blocks of input data */
    if (bytesRemaining > 0U)
    {
    #ifdef AES_BUSHALT_DISABLED
        /* Wait for encryption of counter block to complete */
        while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}
    #endif
        size_t i;

        /* This code is faster than calling memcpy() twice */
        for (i = 0U; i < bytesRemaining; i++)
        {
            volatile uint8_t *regTXTX = (volatile uint8_t *)(AES_BASE + AES_O_TXTX0);
            volatile uint8_t *regTXT  = (volatile uint8_t *)(AES_BASE + AES_O_TXT0);

            /* Write TXTX register to XOR input with previously encrypted counter block */
            regTXTX[i] = input[bytesProcessed + i];

            /* Read output from TXT register */
            output[bytesProcessed + i] = regTXT[i];
        }
    }
}

/*
 *  ======== AESCTRXXF3_waitForResult ========
 */
static int_fast16_t AESCTRXXF3_waitForResult(AESCTR_Handle handle)
{
    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    int_fast16_t status;

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (object->inputLength < AESCTRXXF3_DMA_SIZE_THRESHOLD))
    {
        /* Save the last counter value from the AES engine */
        AESCTRXXF3_readCounter((uint32_t *)&object->counter[0]);

        /*
         * Save the object's returnStatus before clearing operationInProgress or
         * posting the access semaphore in case it is overwritten.
         */
        status = object->common.returnStatus;

        if ((object->operationType & AESCTR_OP_FLAG_SEGMENTED) == 0U)
        {
            /* One-step or finalization operation is complete */
            AESCommonXXF3_clearOperationInProgress(&object->common);
        }

        AESCommonXXF3_cleanup(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, object->operation, object->operationType);

            /* Always return success in callback mode */
            status = AESCTR_STATUS_SUCCESS;
        }
    }
    else if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_BLOCKING)
    {
        /* Ignore return value since timeout is infinite */
        (void)SemaphoreP_pend((SemaphoreP_Handle)&CryptoResourceXXF3_operationSemaphore,
                              (uint32_t)SemaphoreP_WAIT_FOREVER);

        status = object->common.returnStatus;
    }
    else /* AESCTR_RETURN_BEHAVIOR_CALLBACK */
    {
        /* Success is always returned in callback mode */
        status = AESCTR_STATUS_SUCCESS;
    }

    return status;
}
#endif /* #if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCTR_addData ========
 */
int_fast16_t AESCTR_addData(AESCTR_Handle handle, AESCTR_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    int_fast16_t status       = AESCTR_STATUS_ERROR;

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if (object->common.key.encoding == CryptoKey_PLAINTEXT_HSM || object->common.key.encoding == CryptoKey_KEYSTORE_HSM)
    {
        return AESCTRXXF3HSM_addData(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)

    /* Assert the segmented operation was setup */
    DebugP_assert((object->operationType == AESCTR_OPERATION_TYPE_ENCRYPT_SEGMENTED) ||
                  (object->operationType == AESCTR_OPERATION_TYPE_DECRYPT_SEGMENTED));

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESCTR_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCTR_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
    #endif

    /* Verify the input length is non-zero and a multiple of the block size */
    if ((operation->inputLength == 0U) || ((operation->inputLength & AES_NON_BLOCK_SIZE_MULTIPLE_MASK) != 0U))
    {
        return AESCTR_STATUS_ERROR;
    }

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCTR_STATUS_ERROR;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
        {
            return AESCTR_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation = (AESCTR_OperationUnion *)operation;

    /* Make internal copy of operational params */
    object->input                = operation->input;
    object->inputLength          = operation->inputLength;
    object->inputLengthRemaining = operation->inputLength;
    object->output               = operation->output;

    status = AESCTRXXF3_startOperation(handle, false);

#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

/*
 *  ======== AESCTR_finalize ========
 */
int_fast16_t AESCTR_finalize(AESCTR_Handle handle, AESCTR_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    int_fast16_t status       = AESCTR_STATUS_ERROR;

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if (object->common.key.encoding == CryptoKey_PLAINTEXT_HSM || object->common.key.encoding == CryptoKey_KEYSTORE_HSM)
    {
        return AESCTRXXF3HSM_finalize(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCTR_OperationType operationType;

    /* Assert the segmented operation was setup */
    DebugP_assert((object->operationType == AESCTR_OPERATION_TYPE_ENCRYPT_SEGMENTED) ||
                  (object->operationType == AESCTR_OPERATION_TYPE_DECRYPT_SEGMENTED));

    /* Check for previous failure of segmented operation */
    if (object->common.returnStatus != AESCTR_STATUS_SUCCESS)
    {
        /* Return the failure status of previous call.
         * The callback will not be called.
         */
        return object->common.returnStatus;
    }

    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCTR_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
    #endif

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) && (operation->inputLength > 0U) &&
        !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCTR_STATUS_ERROR;
    }

    /*
     * Determine final operation type but do not save to object until
     * we have obtained access to CRYPTO resource or there is no input
     * to process. This allows app to retry finalization if the CRYPTO
     * resource is unavailable.
     */
    if (object->operationType == AESCTR_OPERATION_TYPE_ENCRYPT_SEGMENTED)
    {
        operationType = AESCTR_OPERATION_TYPE_ENCRYPT_FINALIZE;
    }
    else
    {
        operationType = AESCTR_OPERATION_TYPE_DECRYPT_FINALIZE;
    }

    if (operation->inputLength > 0U)
    {
        /* Try and obtain access to the crypto module */
        if (object->threadSafe)
        {
            if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
            {
                return AESCTR_STATUS_RESOURCE_UNAVAILABLE;
            }

            object->common.cryptoResourceLocked = true;
        }

        object->operationType = operationType;
        object->operation     = (AESCTR_OperationUnion *)operation;

        /* Make internal copy of operational params */
        object->input                = operation->input;
        object->inputLength          = operation->inputLength;
        object->inputLengthRemaining = operation->inputLength;
        object->output               = operation->output;

        status = AESCTRXXF3_startOperation(handle, true);
    }
    else /* Operation was finalized without additional data to process */
    {
        /*
         * Save the object's returnStatus in case it is
         * overwritten during setup of a new segmented operation
         * after the operationInProgress flag is cleared.
         */
        status = object->common.returnStatus;

        AESCommonXXF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCTR_OperationUnion *)operation, operationType);

            /* Always return success in callback mode */
            status = AESCTR_STATUS_SUCCESS;
        }
    }
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

/*
 *  ======== AESCTRXXF3_setupSegmentedOperation ========
 */
static int_fast16_t AESCTRXXF3_setupSegmentedOperation(AESCTRXXF3_Object *object,
                                                       const CryptoKey *key,
                                                       const uint8_t initialCounter[AES_BLOCK_SIZE])
{
    DebugP_assert(key);

    int_fast16_t status = AESCTR_STATUS_SUCCESS;

    /*
     * Key material pointer and length are not checked until adding or
     * finalizing data.
     */
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if (key->encoding == CryptoKey_PLAINTEXT || key->encoding == CryptoKey_KEYSTORE)
    {
        /* When using the AES driver with the LAES engine */
        status = AESCommonXXF3_setupSegmentedOperation(&object->common, key);
    }
    else
#endif
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        if (key->encoding == CryptoKey_PLAINTEXT_HSM || key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        /* A segmented operation may have been started but not finalized yet */
        if (object->segmentedOperationInProgress)
        {
            return AESCTR_STATUS_ERROR;
        }

        /* Make internal copy of crypto key */
        object->common.key = *key;

        /* returnStatus is only changed in the case of an error or cancellation */
        object->common.returnStatus = AES_STATUS_SUCCESS;

        object->segmentedOperationInProgress = true;
    }
    else
#endif
    {
        status = AESCTR_STATUS_ERROR;
    }

    if (status == AESCTR_STATUS_SUCCESS)
    {
        AESCTRXXF3_initCounter(object, &initialCounter[0]);

        /*
         * Initialize operation pointer to NULL in case AESCTR_cancelOperation
         * is called after AESCTR_setupXXXX and callback should be skipped.
         */
        object->operation = NULL;
    }

    return status;
}

/*
 *  ======== AESCTR_setupEncrypt ========
 */
int_fast16_t AESCTR_setupEncrypt(AESCTR_Handle handle, const CryptoKey *key, const uint8_t *initialCounter)
{
    DebugP_assert(handle);
    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    DebugP_assert(object);

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (((key->encoding == CryptoKey_PLAINTEXT_HSM) || (key->encoding == CryptoKey_KEYSTORE_HSM)) &&
        (object->hsmStatus != HSMXXF3_STATUS_SUCCESS))
    {
        return AESCTR_STATUS_ERROR;
    }
#endif

    int_fast16_t status = AESCTRXXF3_setupSegmentedOperation(object, key, initialCounter);

    if (status == AESCTR_STATUS_SUCCESS)
    {
        object->operationType = AESCTR_OPERATION_TYPE_ENCRYPT_SEGMENTED;
    }

    return status;
}

/*
 *  ======== AESCTR_setupDecrypt ========
 */
int_fast16_t AESCTR_setupDecrypt(AESCTR_Handle handle, const CryptoKey *key, const uint8_t *initialCounter)
{
    DebugP_assert(handle);
    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    DebugP_assert(object);

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (((key->encoding == CryptoKey_PLAINTEXT_HSM) || (key->encoding == CryptoKey_KEYSTORE_HSM)) &&
        (object->hsmStatus != HSMXXF3_STATUS_SUCCESS))
    {
        return AESCTR_STATUS_ERROR;
    }
#endif

    int_fast16_t status = AESCTRXXF3_setupSegmentedOperation(object, key, initialCounter);

    if (status == AESCTR_STATUS_SUCCESS)
    {
        object->operationType = AESCTR_OPERATION_TYPE_DECRYPT_SEGMENTED;
    }

    return status;
#else
    (void)handle;

    return AESCTR_STATUS_SUCCESS;
#endif
}

/*
 *  ======== AESCTR_cancelOperation ========
 */
int_fast16_t AESCTR_cancelOperation(AESCTR_Handle handle)
{
    DebugP_assert(handle);

    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);

    uintptr_t interruptKey = HwiP_disable();

    /*
     * Return success if there is no active operation to cancel.
     * Do not execute the callback as it would have been executed already
     * when the operation completed.
     */
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if (((object->common.key.encoding & CRYPTOKEY_HSM) == 0) && (!object->common.operationInProgress))
#else
    if (!object->common.operationInProgress)
#endif
    {
        HwiP_restore(interruptKey);
        return AESCTR_STATUS_SUCCESS;
    }

    HwiP_restore(interruptKey);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    /*
     * Cancel DMA for input and output channels, clear operation in-progress,
     * and releases crypto resource if necessary.
     */
    AESCommonXXF3_cancelOperation(&object->common, true);
#else
    /* Set return status explicitly here. */
    object->common.returnStatus = AESCTR_STATUS_CANCELED;
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if ((object->common.key.encoding & CRYPTOKEY_HSM))
    {
        /* Since the HSM cannot cancel an in-progress token, we must wait for the result to allow for
         * subsequent token submissions to succeed.
         */
        (void)HSMXXF3_cancelOperation();

        object->segmentedOperationInProgress = false;

        /* Attempt to free all the assets the driver created. Whether or not
         * this is successful, we should continue on to attempt cancellation of
         * the operation.
         */
    #if (ENABLE_KEY_STORAGE == 1)
        (void)AESCTRXXF3HSM_freeAllAssets(handle);
    #endif
    }
#endif

    /*
     * Operation pointer could be NULL if a segmented operation was setup
     * but neither AESCTR_addData or AESCTR_finalize was called.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
    {
        /* Call the callback function provided by the application */
        object->callbackFxn(handle, AESCTR_STATUS_CANCELED, object->operation, object->operationType);
    }

    return AESCTR_STATUS_SUCCESS;
}

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
/*
 *  ======== AESCTRXXF3HSM_oneStepOperation ========
 */
static int_fast16_t AESCTRXXF3HSM_oneStepOperation(AESCTR_Handle handle,
                                                   AESCTR_OneStepOperation *operation,
                                                   AESCTR_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    /* No need to assert operationType since we control it within the driver */

    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCTR_STATUS_ERROR;
    }

    /* Verify input length is non-zero */
    if (operation->inputLength == 0U)
    {
        return AESCTR_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESCTR_STATUS_ERROR;
    }

    object->operation           = (AESCTR_OperationUnion *)operation;
    object->operationType       = operationType;
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESCTR_STATUS_SUCCESS;

    /* Make internal copy of operational params */
    object->common.key = *(operation->key);

    object->input       = operation->input;
    object->output      = operation->output;
    object->inputLength = operation->inputLength;

    AESCTRXXF3_initCounter(object, &operation->initialCounter[0]);

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)

    /* It is currently not possible to write back data to PSRAM in callback mode */
    if (XMEMWFF3_isAddrExternal((uintptr_t)object->output) &&
        (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK))
    {
        return AESCTR_STATUS_FEATURE_NOT_SUPPORTED;
    }

    /* Calculate maximum chunk size, based on input/output locations and
     * input/output bounce buffer sizes. If the input address is in internal
     * memory, the input bounce buffer size is irrelevant, and is set to maximum
     * for the calculation, and the same logic applies to the output.
     * If either sizes get set to 0, the operation can not be completed, and an
     * error is returned.
     */
    size_t inputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)object->input) ? HSMXXF3_inputBounce.size : SIZE_MAX;

    size_t outputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)object->output) ? HSMXXF3_outputBounce.size : SIZE_MAX;

    if (inputBounceSize == 0 || outputBounceSize == 0)
    {
        return AESCBC_STATUS_ERROR;
    }

    size_t minBounceSize = Math_MIN(inputBounceSize, outputBounceSize);

    /* Round down to the nearest AES block boundary so every chunk submitted to
     * the HSM is a valid block-aligned length.
     */
    size_t maxChunkSize = minBounceSize & ~(AES_BLOCK_SIZE - 1U);

    /* If input or output is in PSRAM and exceeds the bounce slot, split into
     * block-aligned chunks. The counter for the next chunk is updated by
     * processOneStepOperation post-processing and stored in object->counter,
     * so continuity is maintained automatically across chunks.
     */
    if ((object->inputLength > maxChunkSize) &&
        (XMEMWFF3_isAddrExternal((uintptr_t)object->input) || XMEMWFF3_isAddrExternal((uintptr_t)object->output)))
    {
        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            return AESCTR_STATUS_FEATURE_NOT_SUPPORTED;
        }

        uint8_t *chunkInput   = (uint8_t *)operation->input;
        uint8_t *chunkOutput  = operation->output;
        size_t remainingBytes = operation->inputLength;

        while (remainingBytes > 0U)
        {
            int_fast16_t chunkStatus;
            size_t chunkSize = (remainingBytes > maxChunkSize) ? maxChunkSize : remainingBytes;

            object->input       = chunkInput;
            object->output      = chunkOutput;
            object->inputLength = chunkSize;

            chunkStatus = AESCTRXXF3HSM_processOneStepOperation(handle);
            if (chunkStatus != AESCTR_STATUS_SUCCESS)
            {
                return chunkStatus;
            }

            chunkInput += chunkSize;
            chunkOutput += chunkSize;
            remainingBytes -= chunkSize;
        }
        return AESCTR_STATUS_SUCCESS;
    }
    #endif

    return AESCTRXXF3HSM_processOneStepOperation(handle);
}

    #if (ENABLE_KEY_STORAGE == 1)
/*
 *  ======== AESCTRXXF3HSM_freeAllAssets ========
 */
static int_fast16_t AESCTRXXF3HSM_freeAllAssets(AESCTR_Handle handle)
{
#if (ENABLE_KEY_STORAGE == 1)
    AESCTRXXF3_Object *object = (AESCTRXXF3_Object *)handle->object;
    int_fast16_t status       = AESCTR_STATUS_SUCCESS;
    KeyStore_PSA_KeyFileId keyID;

    if ((object->common.key.encoding == CryptoKey_KEYSTORE_HSM) &&
        (object->keyLocation == KEYSTORE_PSA_KEY_LOCATION_HSM_ASSET_STORE))
    {
        GET_KEY_ID(keyID, object->common.key.u.keyStore.keyID);

        /* For keys with a persistence that does not designate them to remain in
         * asset store, the following function will remove them. Otherwise, the
         * key will remain in asset store for future usage.
         */
        status = KeyStore_PSA_assetPostProcessing(keyID);

        if (status != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            status = AESCTR_STATUS_ERROR;
        }
        else
        {
            status = AESCTR_STATUS_SUCCESS;
        }
    }

    return status;
}
    #endif

/*
 *  ======== AESCTRXXF3HSM_OneStepOperationPostProcessing ========
 */
static inline void AESCTRXXF3HSM_OneStepOperationPostProcessing(uintptr_t arg0)
{
    AESCTR_Handle handle      = (AESCTR_Handle)arg0;
    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    int_fast16_t status       = AESCTR_STATUS_ERROR;
    int32_t physicalResult    = HSMXXF3_getResultCode();
    int32_t tokenResult       = physicalResult & HSMXXF3_RETVAL_MASK;

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = AESCTR_STATUS_SUCCESS;

        HSMXXF3_getAESIV((void *)&object->counter[0]);
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    /* Free all assets. This includes key-related asset and state-related asset
     * (temporary asset).
     */
    #if (ENABLE_KEY_STORAGE == 1)
    if (AESCTRXXF3HSM_freeAllAssets(handle) != AESCTR_STATUS_SUCCESS)
    {
        status = AESCTR_STATUS_ERROR;
    }
    #endif

    object->common.returnStatus = status;

    HSMXXF3_releaseLock();

    if ((object->operationType == AESCTR_OPERATION_TYPE_ENCRYPT_FINALIZE) ||
        (object->operationType == AESCTR_OPERATION_TYPE_DECRYPT_FINALIZE) ||
        (object->operationType == AESCTR_OPERATION_TYPE_ENCRYPT) ||
        (object->operationType == AESCTR_OPERATION_TYPE_DECRYPT))
    {
        object->segmentedOperationInProgress = false;
    }

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
    }
}

/*
 *  ======== AESCTRXXF3HSM_processOneStepOperation ========
 */
static int_fast16_t AESCTRXXF3HSM_processOneStepOperation(AESCTR_Handle handle)
{
    int_fast16_t status       = AESCTR_STATUS_ERROR;
    int_fast16_t hsmRetval    = HSMXXF3_STATUS_ERROR;
    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    uint8_t *keyMaterial      = NULL;
    #if (ENABLE_KEY_STORAGE == 1)
    KeyStore_PSA_KeyFileId keyID;
    KeyStore_PSA_KeyAttributes attributes = KEYSTORE_PSA_KEY_ATTRIBUTES_INIT;
    KeyStore_PSA_KeyLifetime lifetime;
    int_fast16_t keyStoreStatus;
    uint8_t KeyStore_keyingMaterial[AESCommonXXF3_256_KEY_LENGTH_BYTES];
    KeyStore_PSA_KeyUsage usage = ((object->operationType & AESCTR_OP_MODE_MASK) == AESCTR_MODE_ENCRYPT)
                                      ? KEYSTORE_PSA_KEY_USAGE_ENCRYPT
                                      : KEYSTORE_PSA_KEY_USAGE_DECRYPT;
    #endif
    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESCTR_STATUS_RESOURCE_UNAVAILABLE;
    }

    if (object->common.key.encoding == CryptoKey_PLAINTEXT_HSM)
    {
        keyMaterial = object->common.key.u.plaintext.keyMaterial;
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (object->common.key.encoding == CryptoKey_KEYSTORE_HSM)
    {
        GET_KEY_ID(keyID, object->common.key.u.keyStore.keyID);

        keyStoreStatus = KeyStore_PSA_getKeyAttributes(keyID, &attributes);

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
        {
            keyStoreStatus = KeyStore_PSA_retrieveFromKeyStore(&object->common.key,
                                                               &KeyStore_keyingMaterial[0],
                                                               sizeof(KeyStore_keyingMaterial),
                                                               &object->keyAssetID,
                                                               KEYSTORE_PSA_ALG_CTR,
                                                               usage);

            if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
            {
                lifetime = KeyStore_PSA_getKeyLifetime(&attributes);

                object->keyLocation = KEYSTORE_PSA_KEY_LIFETIME_GET_LOCATION(lifetime);

                keyMaterial = &KeyStore_keyingMaterial[0];

                status = AESCTR_STATUS_SUCCESS;
            }
        }

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_INVALID_KEY_ID)
        {
            status = AESCTR_STATUS_KEYSTORE_INVALID_ID;
        }
        else if (keyStoreStatus != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            status = AESCTR_STATUS_KEYSTORE_GENERIC_ERROR;
        }

        if (status != AESCTR_STATUS_SUCCESS)
        {
            HSMXXF3_releaseLock();

            return status;
        }
    }
    #endif
    else
    {
        HSMXXF3_releaseLock();

        return AESCTR_STATUS_FEATURE_NOT_SUPPORTED;
    }

    HSMXXF3_constructAESCTROneStepPhysicalToken(object, keyMaterial);

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
    if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
    {
        HSMXXF3_releaseLock();

        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->common.returnBehavior,
                                    AESCTRXXF3HSM_OneStepOperationPostProcessing,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->common.returnStatus;
        }
    }

    if (hsmRetval != HSMXXF3_STATUS_SUCCESS)
    {
        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        HSMXXF3_releaseLock();
    }

    return status;
}

int_fast16_t AESCTRXXF3HSM_addData(AESCTR_Handle handle, AESCTR_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCTR_STATUS_ERROR;
    }

    /* Assert the segmented operation was setup */
    DebugP_assert((object->operationType == AESCTR_OPERATION_TYPE_ENCRYPT_SEGMENTED) ||
                  (object->operationType == AESCTR_OPERATION_TYPE_DECRYPT_SEGMENTED));

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESCTR_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    /* Verify the input length is non-zero and a multiple of the block size */
    if ((operation->inputLength == 0U) || ((operation->inputLength & AES_NON_BLOCK_SIZE_MULTIPLE_MASK) != 0U))
    {
        return AESCTR_STATUS_ERROR;
    }

    object->operation = (AESCTR_OperationUnion *)operation;

    object->input       = operation->input;
    object->output      = operation->output;
    object->inputLength = operation->inputLength;

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When input or output is in PSRAM and exceeds the bounce slot, split into
     * block-aligned chunks. The counter for the next chunk is updated by
     * processOneStepOperation post-processing and stored in object->counter,
     * so continuity is maintained automatically across chunks.
     */

    /* Calculate maximum chunk size, based on input/output locations and
     * input/output bounce buffer sizes. If the input address is in internal
     * memory, the input bounce buffer size is irrelevant, and is set to maximum
     * for the calculation, and the same logic applies to the output.
     * If either sizes get set to 0, the operation can not be completed, and an
     * error is returned.
     */
    size_t inputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)object->input) ? HSMXXF3_inputBounce.size : SIZE_MAX;

    size_t outputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)object->output) ? HSMXXF3_outputBounce.size : SIZE_MAX;

    if (inputBounceSize == 0 || outputBounceSize == 0)
    {
        return AESCBC_STATUS_ERROR;
    }

    size_t minBounceSize = Math_MIN(inputBounceSize, outputBounceSize);

    size_t maxChunkSize = minBounceSize & ~(AES_BLOCK_SIZE - 1U);

    if ((object->inputLength > maxChunkSize) &&
        (XMEMWFF3_isAddrExternal((uintptr_t)object->input) || XMEMWFF3_isAddrExternal((uintptr_t)object->output)))
    {
        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            return AESCTR_STATUS_FEATURE_NOT_SUPPORTED;
        }

        uint8_t *chunkInput   = (uint8_t *)operation->input;
        uint8_t *chunkOutput  = operation->output;
        size_t remainingBytes = operation->inputLength;

        while (remainingBytes > 0U)
        {
            int_fast16_t chunkStatus;
            size_t chunkSize = (remainingBytes > maxChunkSize) ? maxChunkSize : remainingBytes;

            object->input       = chunkInput;
            object->output      = chunkOutput;
            object->inputLength = chunkSize;

            chunkStatus = AESCTRXXF3HSM_processOneStepOperation(handle);
            if (chunkStatus != AESCTR_STATUS_SUCCESS)
            {
                return chunkStatus;
            }

            chunkInput += chunkSize;
            chunkOutput += chunkSize;
            remainingBytes -= chunkSize;
        }
        return AESCTR_STATUS_SUCCESS;
    }
    #endif

    return AESCTRXXF3HSM_processOneStepOperation(handle);
}

int_fast16_t AESCTRXXF3HSM_finalize(AESCTR_Handle handle, AESCTR_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCTRXXF3_Object *object = AESCTRXXF3_getObject(handle);
    AESCTR_OperationType operationType;
    int_fast16_t status;

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCTR_STATUS_ERROR;
    }

    /* Assert the segmented operation was setup */
    DebugP_assert((object->operationType == AESCTR_OPERATION_TYPE_ENCRYPT_SEGMENTED) ||
                  (object->operationType == AESCTR_OPERATION_TYPE_DECRYPT_SEGMENTED));

    /* Check for previous failure of segmented operation */
    if (object->common.returnStatus != AESCTR_STATUS_SUCCESS)
    {
        /* Return the failure status of previous call.
         * The callback will not be called.
         */
        return object->common.returnStatus;
    }

    if (object->operationType == AESCTR_OPERATION_TYPE_ENCRYPT_SEGMENTED)
    {
        operationType = AESCTR_OPERATION_TYPE_ENCRYPT_FINALIZE;
    }
    else
    {
        operationType = AESCTR_OPERATION_TYPE_DECRYPT_FINALIZE;
    }

    if (operation->inputLength > 0U)
    {
        object->operationType = operationType;
        object->operation     = (AESCTR_OperationUnion *)operation;

        object->input       = operation->input;
        object->output      = operation->output;
        object->inputLength = operation->inputLength;

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        /* When input or output is in PSRAM and exceeds the bounce slot, split into
         * block-aligned chunks. The counter for the next chunk is updated by
         * processOneStepOperation post-processing and stored in object->counter,
         * so continuity is maintained automatically across chunks.
         */

        /* Calculate maximum chunk size, based on input/output locations and
         * input/output bounce buffer sizes. If the input address is in internal
         * memory, the input bounce buffer size is irrelevant, and is set to maximum
         * for the calculation, and the same logic applies to the output.
         * If either sizes get set to 0, the operation can not be completed, and an
         * error is returned.
         */
        size_t inputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)object->input) ? HSMXXF3_inputBounce.size
                                                                                   : SIZE_MAX;

        size_t outputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)object->output) ? HSMXXF3_outputBounce.size
                                                                                     : SIZE_MAX;

        if (inputBounceSize == 0 || outputBounceSize == 0)
        {
            return AESCBC_STATUS_ERROR;
        }

        size_t minBounceSize = Math_MIN(inputBounceSize, outputBounceSize);

        size_t maxChunkSize = minBounceSize & ~(AES_BLOCK_SIZE - 1U);

        if ((object->inputLength > maxChunkSize) &&
            (XMEMWFF3_isAddrExternal((uintptr_t)object->input) || XMEMWFF3_isAddrExternal((uintptr_t)object->output)))
        {
            if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
            {
                status = AESCTR_STATUS_FEATURE_NOT_SUPPORTED;
            }
            else
            {
                uint8_t *chunkInput   = (uint8_t *)operation->input;
                uint8_t *chunkOutput  = operation->output;
                size_t remainingBytes = operation->inputLength;

                status = AESCTR_STATUS_SUCCESS;
                while (remainingBytes > 0U)
                {
                    int_fast16_t chunkStatus;
                    size_t chunkSize = (remainingBytes > maxChunkSize) ? maxChunkSize : remainingBytes;

                    object->input       = chunkInput;
                    object->output      = chunkOutput;
                    object->inputLength = chunkSize;

                    chunkStatus = AESCTRXXF3HSM_processOneStepOperation(handle);
                    if (chunkStatus != AESCTR_STATUS_SUCCESS)
                    {
                        status = chunkStatus;
                        break;
                    }

                    chunkInput += chunkSize;
                    chunkOutput += chunkSize;
                    remainingBytes -= chunkSize;
                }
            }
        }
        else
        {
            status = AESCTRXXF3HSM_processOneStepOperation(handle);
        }
    #else
        status = AESCTRXXF3HSM_processOneStepOperation(handle);
    #endif
    }
    else /* Operation was finalized without additional data to process */
    {
        /* Save the object's returnStatus in case it is
         * overwritten during setup of a new segmented operation
         * after the operationInProgress flag is cleared.
         */
        status = object->common.returnStatus;

        object->segmentedOperationInProgress = false;

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCTR_OperationUnion *)operation, operationType);

            /* Always return success in callback mode */
            status = AESCTR_STATUS_SUCCESS;
        }
    }

    return status;
}

#endif /* ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) \
        * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))                                                     \
        */
