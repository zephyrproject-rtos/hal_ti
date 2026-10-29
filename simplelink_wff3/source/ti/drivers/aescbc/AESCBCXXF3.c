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

#include <ti/drivers/aescbc/AESCBCXXF3.h>
#include <ti/drivers/AESCBC.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/aesecb/AESECBXXF3.h>
#include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceXXF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>
#include <ti/drivers/cryptoutils/utils/CryptoUtils.h>

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    #include <ti/drivers/dma/UDMALPF3.h>
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) && (ENABLE_KEY_STORAGE == 1))
    #error "Key storage is not supported for CC23X0"
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    /* Using LPF3 driver implementation for WFF3 device, CC35XX since the HSM IP is the same. */
    #if (ENABLE_KEY_STORAGE == 1)
        /* These includes must come before hsmddk/include/Integration/Adapter_PSA includes */
        #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
        #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
    #endif
    #include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
    #include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>
    #include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
    #include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_result.h>
    #include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_asset.h>
    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        #include <ti/drivers/xmem/XMEMWFF3.h>
        #include <ti/drivers/utils/Math.h>
    #endif
#endif

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    #include DeviceFamily_constructPath(driverlib/aes.h)
    #include DeviceFamily_constructPath(inc/hw_aes.h)
    #include DeviceFamily_constructPath(inc/hw_ints.h)
#endif

/*
 * Default AES CBC auto config:
 *  CBC SRC as TXTXBUF
 *  Trigger points for auto CBC as RDTXT3 and WRBUF3S
 *   (the first encryption starts by writing BUF3, the successive ones by reading TXT3)
 *  DONEACT as GATE_TRGAES_ON_CHA_DEL (to avoid spurious last ECB using DMA)
 *  BUSHALT enabled
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #define AESCBCXXF3_DEFAULT_AUTOCFG                                                 \
        ((uint32_t)AES_AUTOCFG_AESSRC_TXTXBUF | (uint32_t)AES_AUTOCFG_TRGAES_WRBUF3S | \
         (uint32_t)AES_AUTOCFG_TRGAES_RDTXT3 | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/* Not used for CC35XX */
#else
    #error "Unsupported DeviceFamily_Parent for AESCBCXXF3!"
#endif

/*
 * AES CBC auto config for a single block encryption:
 *  CBC SRC as TXTXBUF
 *  Trigger points for auto CBC as WRBUF3S (encryption starts by writing BUF3)
 *  BUSHALT enabled
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #define AESCBCXXF3_SINGLE_BLOCK_AUTOCFG \
        ((uint32_t)AES_AUTOCFG_AESSRC_TXTXBUF | (uint32_t)AES_AUTOCFG_TRGAES_WRBUF3S | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/* Not used for CC35XX */
#else
    #error "Unsupported DeviceFamily_Parent for AESCBCXXF3!"
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/* Forward declarations */
static int_fast16_t AESCBCXXF3_checkOperation(AESCBCXXF3_Object *object,
                                              uint8_t *input,
                                              uint8_t *output,
                                              size_t inputLength);
static void AESCBCXXF3_finishOperation(AESCBCXXF3_Object *object);
static inline int_fast16_t AESCBCXXF3_oneStepOperation(AESCBC_Handle handle,
                                                       AESCBC_Operation *operation,
                                                       AESCBC_OperationType operationType);
static int_fast16_t AESCBCXXF3_startOperation(AESCBC_Handle handle,
                                              const uint8_t *input,
                                              uint8_t *output,
                                              size_t inputLength);
static inline int_fast16_t AESCBCXXF3_waitForResult(AESCBC_Handle handle);
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
static int_fast16_t AESCBCXXF3HSM_oneStepOperation(AESCBC_Handle handle,
                                                   AESCBC_OneStepOperation *operation,
                                                   AESCBC_OperationType operationType);
static int_fast16_t AESCBCXXF3HSM_processData(AESCBC_Handle handle);
int_fast16_t AESCBCXXF3HSM_addData(AESCBC_Handle handle, AESCBC_SegmentedOperation *operation);
int_fast16_t AESCBCXXF3HSM_finalize(AESCBC_Handle handle, AESCBC_SegmentedOperation *operation);
    #if (ENABLE_KEY_STORAGE == 1)
static int_fast16_t AESCBCXXF3HSM_freeAllAssets(AESCBC_Handle handle);
    #endif
#endif

/*
 *  ======== AESCBCXXF3_getObject ========
 */
static inline AESCBCXXF3_Object *AESCBCXXF3_getObject(AESCBC_Handle handle)
{
    AESCBCXXF3_Object *object = (AESCBCXXF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCBCXXF3_hwiFxn ========
 */
static void AESCBCXXF3_hwiFxn(uintptr_t arg0)
{
    AESCBC_Handle handle      = (AESCBC_Handle)arg0;
    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);

    /*
     * Only the output channel B interrupt is enabled.
     */
    uint32_t intStatus = AESGetMaskedInterruptStatus();

    /* Disable DMA, clear interupts, and release power constraint */
    AESCommonXXF3_cleanupHwi(&object->common);

    if ((intStatus & (uint32_t)AES_MIS_CHBDONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonXXF3_DMA_CHB_BITMASK);

        AESCBCXXF3_finishOperation(object);

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
            object->callbackFxn((AESCBC_Handle)handle,
                                object->common.returnStatus,
                                object->operation,
                                object->operationType);
        }
    }
}
#endif

/*
 *  ======== AESCBC_init ========
 */
void AESCBC_init(void)
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
 *  ======== AESCBC_construct ========
 */
AESCBC_Handle AESCBC_construct(AESCBC_Config *config, const AESCBC_Params *params)
{
    DebugP_assert(config);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    int_fast16_t status;
#endif
    AESCBC_Handle handle      = config;
    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Callback return mode is not supported for CC35XX for now */
    if ((params != NULL) && (params->returnBehavior == AESCBC_RETURN_BEHAVIOR_CALLBACK))
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
        params = &AESCBC_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AESCBC_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->callbackFxn = params->callbackFxn;
    object->threadSafe  = true;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    object->common.returnBehavior = (AES_ReturnBehavior)params->returnBehavior;
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
 *  ======== AESCBC_close ========
 */
void AESCBC_close(AESCBC_Handle handle)
{
    DebugP_assert(handle);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCommonXXF3_close(&object->common);
#else
    /* Mark the module as available */
    object->common.isOpen = false;
#endif
}

/*
 *  ======== AESCBC_setIV ========
 */
int_fast16_t AESCBC_setIV(AESCBC_Handle handle, const uint8_t *iv, size_t ivLength)
{
    DebugP_assert(handle);
    DebugP_assert(iv);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);

    /* Don't continue the operation if there was an error or cancellation */
    if (object->common.returnStatus != AESCBC_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    /* This function is reserved for segmented operations only */
    DebugP_assert((object->operationType == AESCBC_OP_TYPE_DECRYPT_SEGMENTED) ||
                  (object->operationType == AESCBC_OP_TYPE_ENCRYPT_SEGMENTED));

    /* The length of the new IV should be 16 or AES_BLOCK_SIZE bytes */
    if (ivLength != AES_BLOCK_SIZE)
    {
        return AESCBC_STATUS_ERROR;
    }

    /*
     * Copy the user-provided IV to the object structure since the IV in
     * operation struct is reserved for one-shot operations only
     */
    (void)memcpy((void *)&object->iv[0], (void *)iv, sizeof(object->iv));

    return AESCBC_STATUS_SUCCESS;
}

/*
 *  ======== AESCBC_oneStepEncrypt ========
 */
int_fast16_t AESCBC_oneStepEncrypt(AESCBC_Handle handle, AESCBC_Operation *operation)
{
    int_fast16_t status = AESCBC_STATUS_SUCCESS;

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if ((operation->key->encoding == CryptoKey_PLAINTEXT) || (operation->key->encoding == CryptoKey_KEYSTORE))
    {
        status = AESCBCXXF3_oneStepOperation(handle, operation, AESCBC_OPERATION_TYPE_ENCRYPT);
    }
    else
#endif
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
        if ((operation->key->encoding == CryptoKey_PLAINTEXT_HSM) ||
            (operation->key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        status = AESCBCXXF3HSM_oneStepOperation(handle, operation, AESCBC_OPERATION_TYPE_ENCRYPT);
    }
    else
#endif
    {
        status = AESCBC_STATUS_ERROR;
    }
    return status;
}

/*
 *  ======== AESCBC_oneStepDecrypt ========
 */
int_fast16_t AESCBC_oneStepDecrypt(AESCBC_Handle handle, AESCBC_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    int_fast16_t status = AESCBC_STATUS_SUCCESS;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    if ((operation->key->encoding == CryptoKey_PLAINTEXT_HSM) || (operation->key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        status = AESCBCXXF3HSM_oneStepOperation(handle, operation, AESCBC_OPERATION_TYPE_DECRYPT);
    }
    else
#endif
    {
        status = AESCBC_STATUS_FEATURE_NOT_SUPPORTED;
    }
    return status;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCBCXXF3_checkOperation ========
 */
static int_fast16_t AESCBCXXF3_checkOperation(AESCBCXXF3_Object *object,
                                              uint8_t *input,
                                              uint8_t *output,
                                              size_t inputLength)
{
    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(input) || !IS_WORD_ALIGNED(output))
    {
        return AESCBC_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
    #endif

    /* Verify input length is a non-zero multiple of the AES block size */
    if ((inputLength == 0UL) || (AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(inputLength) > 0UL))
    {
        return AESCBC_STATUS_ERROR;
    }

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonXXF3_isDMALengthValid(input, output, inputLength))
    {
        return AESCBC_STATUS_ERROR;
    }

    return AESCBC_STATUS_SUCCESS;
}

/*
 *  ======== AESCBCXXF3_oneStepOperation ========
 */
static inline int_fast16_t AESCBCXXF3_oneStepOperation(AESCBC_Handle handle,
                                                       AESCBC_OneStepOperation *operation,
                                                       AESCBC_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    int_fast16_t status;

    status = AESCBCXXF3_checkOperation(object, operation->input, operation->output, operation->inputLength);

    if (status != AESCBC_STATUS_SUCCESS)
    {
        return status;
    }

    /*
     * Check that there are no operations already in progress.
     * If not, mark the current operation to be in progress
     */
    status = AESCommonXXF3_setOperationInProgress(&object->common);

    if (status != AESCBC_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
        {
            AESCommonXXF3_clearOperationInProgress(&object->common);
            return AESCBC_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation     = (AESCBC_OperationUnion *)operation;
    object->operationType = operationType;
    (void)memcpy((void *)&object->iv[0], (void *)operation->iv, sizeof(object->iv));

    object->common.key          = *(operation->key);
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESCBC_STATUS_SUCCESS;

    status = AESCBCXXF3_startOperation(handle, operation->input, operation->output, operation->inputLength);

    return status;
}

/*
 *  ======== AESCCBXXF3_startOperation ========
 */
static int_fast16_t AESCBCXXF3_startOperation(AESCBC_Handle handle,
                                              const uint8_t *input,
                                              uint8_t *output,
                                              size_t inputLength)
{
    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    int_fast16_t status;
    #if (ENABLE_KEY_STORAGE == 1)
    int_fast16_t keyStoreStatus;
    uint8_t KeyStore_keyingMaterial[AESCommonXXF3_256_KEY_LENGTH_BYTES];
    KeyStore_PSA_KeyUsage usage;
    #endif

    if (object->common.key.encoding == CryptoKey_PLAINTEXT)
    {
        /* Set up the key and AES engine to begin an operation */
        if (inputLength == AES_BLOCK_SIZE)
        {
            AESCommonXXF3_setupOperation(&object->common.key, AESCBCXXF3_SINGLE_BLOCK_AUTOCFG);
        }
        else
        {
            AESCommonXXF3_setupOperation(&object->common.key, AESCBCXXF3_DEFAULT_AUTOCFG);
        }
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (object->common.key.encoding == CryptoKey_KEYSTORE)
    {
        if ((object->operationType == AESCBC_OP_TYPE_ONESTEP_ENCRYPT) ||
            (object->operationType == AESCBC_OP_TYPE_ENCRYPT_SEGMENTED) ||
            (object->operationType == AESCBC_OP_TYPE_FINALIZE_ENCRYPT_SEGMENTED))
        {
            usage = KEYSTORE_PSA_KEY_USAGE_ENCRYPT;
        }
        else
        {
            usage = KEYSTORE_PSA_KEY_USAGE_DECRYPT;
        }

        keyStoreStatus = KeyStore_PSA_retrieveFromKeyStore(&object->common.key,
                                                           &KeyStore_keyingMaterial[0],
                                                           sizeof(KeyStore_keyingMaterial),
                                                           &object->keyAssetID,
                                                           KEYSTORE_PSA_ALG_CBC_NO_PADDING,
                                                           usage);
        if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
        {
            AESWriteKEY(KeyStore_keyingMaterial);

            if (inputLength == AES_BLOCK_SIZE)
            {
                /* Set AUTOCFG */
                AESSetAUTOCFG(AESCBCXXF3_SINGLE_BLOCK_AUTOCFG);
            }
            else
            {
                /* Set AUTOCFG */
                AESSetAUTOCFG(AESCBCXXF3_DEFAULT_AUTOCFG);
            }
        }
        else if (keyStoreStatus == KEYSTORE_PSA_STATUS_INVALID_KEY_ID)
        {
            return AESCBC_STATUS_KEYSTORE_INVALID_ID;
        }
        else
        {
            return AESCBC_STATUS_KEYSTORE_GENERIC_ERROR;
        }
    }
    #endif
    else
    {
        return AESCBC_STATUS_FEATURE_NOT_SUPPORTED;
    }

    AESWriteIV((uint8_t *)&object->iv[0]);

    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        (inputLength >= AESECBXXF3_DMA_SIZE_THRESHOLD))
    {
        /*
         * We need to set the HWI function and priority since the same physical
         * interrupt is shared by multiple drivers and they all need to coexist.
         * Whenever a driver starts an operation, it registers its HWI callback
         * with the OS.
         */
        AESCBCXXF3_HWAttrs const *hwAttrs = handle->hwAttrs;
        AESCommonXXF3_setupHwi(AESCBCXXF3_hwiFxn, (uintptr_t)handle, hwAttrs->intPriority);
    }

    /* ECB function is used for processing the data */
    AESECBXXF3_processData(&object->common, input, output, inputLength);

    status = AESCBCXXF3_waitForResult(handle);

    return status;
}

/*
 *  ======== AESCCBXXF3_finishOperation ========
 */
static void AESCBCXXF3_finishOperation(AESCBCXXF3_Object *object)
{
    if ((object->operationType == AESCBC_OP_TYPE_ONESTEP_ENCRYPT) ||
        (object->operationType == AESCBC_OP_TYPE_FINALIZE_ENCRYPT_SEGMENTED))
    {
        /*
         * For one-shot and finalize operations, clear the IV buffer
         * to prevent data leakage
         */
        CryptoUtils_memset((void *)&object->iv[0], sizeof(object->iv), (uint8_t)0U, sizeof(object->iv));

        AESCommonXXF3_clearOperationInProgress(&object->common);
    }
    else
    {
        /*
         * Store the new iv into object for the next block should we want to
         * continue the chain of blocks in a later segmented operation.
         */
        AESReadIV32((uint32_t *)&object->iv[0]);
    }
}

/*
 *  ======== AESCBCXXF3_waitForResult ========
 */
static inline int_fast16_t AESCBCXXF3_waitForResult(AESCBC_Handle handle)
{
    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    int_fast16_t status;
    size_t inputLength;

    if (object->operationType == AESCBC_OP_TYPE_ONESTEP_ENCRYPT)
    {
        inputLength = object->operation->oneStepOperation.inputLength;
    }
    else
    {
        inputLength = object->operation->segmentedOperation.inputLength;
    }

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) || (inputLength < AESECBXXF3_DMA_SIZE_THRESHOLD))
    {
        AESCBCXXF3_finishOperation(object);

        /*
         * Save the returnStatus prior clearing operationInProgress or
         * releasing the access semaphore in case it's overwritten.
         */
        status = object->common.returnStatus;

        AESCommonXXF3_cleanup(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, object->operation, object->operationType);

            /* Always return success in callback mode */
            status = AESCBC_STATUS_SUCCESS;
        }
    }
    else if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_BLOCKING)
    {
        /* Ignore return value since timeout is infinite */
        (void)SemaphoreP_pend((SemaphoreP_Handle)&CryptoResourceXXF3_operationSemaphore,
                              (uint32_t)SemaphoreP_WAIT_FOREVER);

        status = object->common.returnStatus;
    }
    else /* AES_RETURN_BEHAVIOR_CALLBACK */
    {
        /* Success is always returned in callback mode */
        status = AESCBC_STATUS_SUCCESS;
    }

    return status;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCBC_setupEncrypt ========
 */
int_fast16_t AESCBC_setupEncrypt(AESCBC_Handle handle, const CryptoKey *key)
{
    DebugP_assert(handle);
    int_fast16_t status       = AESCBC_STATUS_ERROR;
    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    /*
     * Key material pointer and length are not checked until adding or
     * finalizing data.
     */
    if ((key->encoding == CryptoKey_PLAINTEXT) || (key->encoding == CryptoKey_KEYSTORE))
    {
        /* When using the AES driver with the LAES engine */
        status = AESCommonXXF3_setupSegmentedOperation(&object->common, key);
    }
    else
#endif
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
        if ((key->encoding == CryptoKey_PLAINTEXT_HSM) || (key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
        {
            return AESCBC_STATUS_ERROR;
        }

        /* A segmented operation may have been started but not finalized yet */
        if (object->segmentedOperationInProgress)
        {
            return AESCBC_STATUS_ERROR;
        }

        /* Make internal copy of crypto key */
        object->common.key = *key;

        /* returnStatus is only changed in the case of an error or cancellation */
        object->common.returnStatus = AES_STATUS_SUCCESS;

        status = AESCBC_STATUS_SUCCESS;

        object->segmentedOperationInProgress = true;
    }
    else
#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) \
        * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                                                     \
        */
    {
        /* User Key encoding is not valid or not supported */
    }

    if (status == AES_STATUS_SUCCESS)
    {
        /* Initialize operation pointer to NULL in case AESCBC_cancelOperation
         * is called after AESCBC_setupXXXX and callback should be skipped.
         */
        object->operation = NULL;

        object->operationType = AESCBC_OP_TYPE_ENCRYPT_SEGMENTED;
    }

    return status;
}

/*
 *  ======== AESCBC_setupDecrypt ========
 */
int_fast16_t AESCBC_setupDecrypt(AESCBC_Handle handle, const CryptoKey *key)
{
    DebugP_assert(handle);
    DebugP_assert(key);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    int_fast16_t status       = AESCBC_STATUS_FEATURE_NOT_SUPPORTED;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    if ((key->encoding == CryptoKey_PLAINTEXT_HSM) || (key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
        if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
        {
            return AESCBC_STATUS_ERROR;
        }

        /* A segmented operation may have been started but not finalized yet */
        if (object->segmentedOperationInProgress)
        {
            return AESCBC_STATUS_ERROR;
        }

        /* Make internal copy of crypto key */
        object->common.key = *key;

        /* returnStatus is only changed in the case of an error or cancellation */
        object->common.returnStatus = AES_STATUS_SUCCESS;

        /* Initialize operation pointer to NULL in case AESCBC_cancelOperation
         * is called after AESCBC_setupXXXX and callback should be skipped.
         */
        object->operation = NULL;

        object->segmentedOperationInProgress = true;

        status = AESCBC_STATUS_SUCCESS;

        object->operationType = AESCBC_OP_TYPE_DECRYPT_SEGMENTED;
    }
    else
#endif
    {
        /* empty */
    }

    /* Save the error status in case addData or finalize is called afterward */
    object->common.returnStatus = status;

    return status;
}

/*
 *  ======== AESCBC_addData ========
 */
int_fast16_t AESCBC_addData(AESCBC_Handle handle, AESCBC_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    int_fast16_t status       = AESCBC_STATUS_FEATURE_NOT_SUPPORTED;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    if ((object->common.key.encoding == CryptoKey_PLAINTEXT_HSM) ||
        (object->common.key.encoding == CryptoKey_KEYSTORE_HSM))
    {
        return AESCBCXXF3HSM_addData(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    /*
     * Assert the segmented operation was setup.
     * LAES128 only supports CBC encryption.
     */
    DebugP_assert(object->operationType == AESCBC_OP_TYPE_ENCRYPT_SEGMENTED);

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESCBC_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    status = AESCBCXXF3_checkOperation(object, operation->input, operation->output, operation->inputLength);

    if (status != AESCBC_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
        {
            return AESCBC_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation = (AESCBC_OperationUnion *)operation;

    status = AESCBCXXF3_startOperation(handle, operation->input, operation->output, operation->inputLength);
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

/*
 *  ======== AESCBC_finalize ========
 */
int_fast16_t AESCBC_finalize(AESCBC_Handle handle, AESCBC_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    int_fast16_t status       = AESCBC_STATUS_FEATURE_NOT_SUPPORTED;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    if ((object->common.key.encoding == CryptoKey_PLAINTEXT_HSM) ||
        (object->common.key.encoding == CryptoKey_KEYSTORE_HSM))
    {
        return AESCBCXXF3HSM_finalize(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    /*
     * Assert the segmented operation was setup.
     * LAES128 only supports CBC encryption.
     */
    DebugP_assert(object->operationType == AESCBC_OP_TYPE_ENCRYPT_SEGMENTED);

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESCBC_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    AESCBC_OperationType operationType = AESCBC_OP_TYPE_FINALIZE_ENCRYPT_SEGMENTED;

    if (operation->inputLength > 0U)
    {
    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
        /* Check word-alignment of input & output pointers */
        if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
        {
            return AESCBC_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
        }
    #endif

        /* Verify input length is a multiple of the AES block size */
        if (AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->inputLength) > 0U)
        {
            return AESCBC_STATUS_ERROR;
        }

        /* Check DMA xfer limit for blocking and callback modes */
        if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
            !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
        {
            return AESCBC_STATUS_ERROR;
        }

        /* Try and obtain access to the crypto module */
        if (object->threadSafe)
        {
            if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
            {
                return AESCBC_STATUS_RESOURCE_UNAVAILABLE;
            }

            object->common.cryptoResourceLocked = true;
        }

        object->operationType = operationType;
        object->operation     = (AESCBC_OperationUnion *)operation;

        status = AESCBCXXF3_startOperation(handle, operation->input, operation->output, operation->inputLength);
    }
    else /* Operation was finalized without additional data to process */
    {
        status = object->common.returnStatus;

        AESCommonXXF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCBC_OperationUnion *)operation, operationType);

            /* Always return success in callback mode */
            status = AESCBC_STATUS_SUCCESS;
        }
    }
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

/*
 *  ======== AESCBC_cancelOperation ========
 */
int_fast16_t AESCBC_cancelOperation(AESCBC_Handle handle)
{
    DebugP_assert(handle);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);

    /* Cancellation is only supported in callback mode */
    if (object->common.returnBehavior != AES_RETURN_BEHAVIOR_CALLBACK)
    {
        return AESCBC_STATUS_ERROR;
    }

    uintptr_t interruptKey = HwiP_disable();

    /*
     * Return success if there is no active operation to cancel.
     * Do not execute the callback as it would have been executed already
     * when the operation completed.
     */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    if (((object->common.key.encoding & CRYPTOKEY_HSM) == 0) && (!object->common.operationInProgress))
#else
    if (!object->common.operationInProgress)
#endif
    {
        HwiP_restore(interruptKey);
        return AESCBC_STATUS_SUCCESS;
    }

    HwiP_restore(interruptKey);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    /*
     * Cancel DMA for input and output channels, clear operation in-progress,
     * and releases crypto resource if necessary.
     */
    AESCommonXXF3_cancelOperation(&object->common, true);
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
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
        (void)AESCBCXXF3HSM_freeAllAssets(handle);
    #endif
    }
#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) \
        * || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)                                                     \
        */

    object->input  = NULL;
    object->output = NULL;

    /*
     * Operation pointer could be NULL if a segmented operation was setup
     * but neither AESCBC_addData or AESCBC_finalize was called.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
    {
        /* Call the callback function provided by the application */
        object->callbackFxn(handle, AESCBC_STATUS_CANCELED, object->operation, object->operationType);
    }

    return AESCBC_STATUS_SUCCESS;
}

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)

/*
 *  ======== AESCBCXXF3HSM_oneStepOperation ========
 */
static int_fast16_t AESCBCXXF3HSM_oneStepOperation(AESCBC_Handle handle,
                                                   AESCBC_OneStepOperation *operation,
                                                   AESCBC_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    /* No need to assert operationType since we control it within the driver */

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCBC_STATUS_ERROR;
    }

    /* Verify input length is non-zero */
    if (operation->inputLength == 0U)
    {
        return AESCBC_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESCBC_STATUS_ERROR;
    }

    object->operation           = (AESCBC_OperationUnion *)operation;
    object->operationType       = operationType;
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESCBC_STATUS_SUCCESS;

    /* Make internal copy of operational params */
    object->common.key  = *(operation->key);
    object->input       = operation->input;
    object->output      = operation->output;
    object->inputLength = operation->inputLength;

    /*
     * Copy the user-provided IV to the object structure since the IV in
     * operation struct is reserved for one-shot operations only
     */
    (void)memcpy((void *)&object->iv[0], (void *)operation->iv, sizeof(object->iv));

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When input or output is in PSRAM and exceeds the bounce slot, split into
     * block-aligned chunks. For both encrypt and decrypt, the IV for the next
     * chunk is read from the result token by processData post-processing and
     * stored in object->iv, so continuity is maintained automatically.
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
            return AESCBC_STATUS_FEATURE_NOT_SUPPORTED;
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

            chunkStatus = AESCBCXXF3HSM_processData(handle);
            if (chunkStatus != AESCBC_STATUS_SUCCESS)
            {
                return chunkStatus;
            }

            chunkInput += chunkSize;
            chunkOutput += chunkSize;
            remainingBytes -= chunkSize;
        }
        return AESCBC_STATUS_SUCCESS;
    }
    #endif

    return AESCBCXXF3HSM_processData(handle);
}

    #if (ENABLE_KEY_STORAGE == 1)
/*
 *  ======== AESCBCXXF3HSM_freeAllAssets ========
 */
static int_fast16_t AESCBCXXF3HSM_freeAllAssets(AESCBC_Handle handle)
{
    AESCBCXXF3_Object *object = (AESCBCXXF3_Object *)handle->object;
    int_fast16_t status       = AESCBC_STATUS_SUCCESS;
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
            status = AESCBC_STATUS_ERROR;
        }
        else
        {
            status = AESCBC_STATUS_SUCCESS;
        }
    }

    return status;
}
    #endif

/*
 *  ======== AESCBCXXF3HSM_OneStepPostProcessing ========
 */
static inline void AESCBCXXF3HSM_OneStepPostProcessing(uintptr_t arg0)
{
    AESCBC_Handle handle      = (AESCBC_Handle)arg0;
    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    int_fast16_t status       = AESCBC_STATUS_ERROR;
    int32_t physicalResult    = HSMXXF3_getResultCode();
    int32_t tokenResult       = physicalResult & HSMXXF3_RETVAL_MASK;

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = AESCBC_STATUS_SUCCESS;

        HSMXXF3_getAESIV((void *)&object->iv[0]);
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    /* Free all assets. This includes key-related asset and state-related asset
     * (temporary asset).
     */
    #if (ENABLE_KEY_STORAGE == 1)
    if (AESCBCXXF3HSM_freeAllAssets(handle) != AESCBC_STATUS_SUCCESS)
    {
        status = AESCBC_STATUS_ERROR;
    }
    #endif

    object->common.returnStatus = status;

    HSMXXF3_releaseLock();

    if ((object->operationType == AESCBC_OPERATION_TYPE_ENCRYPT) ||
        (object->operationType == AESCBC_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESCBC_OP_TYPE_FINALIZE_ENCRYPT_SEGMENTED) ||
        (object->operationType == AESCBC_OP_TYPE_FINALIZE_DECRYPT_SEGMENTED))
    {
        object->segmentedOperationInProgress = false;
    }

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
    }
}

/*
 *  ======== AESCBCXXF3HSM_processData ========
 */
static int_fast16_t AESCBCXXF3HSM_processData(AESCBC_Handle handle)
{
    int_fast16_t status       = AESCBC_STATUS_SUCCESS;
    int_fast16_t hsmRetval    = HSMXXF3_STATUS_ERROR;
    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    uint8_t *keyMaterial      = NULL;
    #if (ENABLE_KEY_STORAGE == 1)
    KeyStore_PSA_KeyFileId keyID;
    KeyStore_PSA_KeyAttributes attributes = KEYSTORE_PSA_KEY_ATTRIBUTES_INIT;
    KeyStore_PSA_KeyLifetime lifetime;
    int_fast16_t keyStoreStatus;
    uint8_t KeyStore_keyingMaterial[AESCommonXXF3_256_KEY_LENGTH_BYTES];
    KeyStore_PSA_KeyUsage usage;
    #endif

    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESCBC_STATUS_RESOURCE_UNAVAILABLE;
    }

    if (object->common.key.encoding == CryptoKey_PLAINTEXT_HSM)
    {
        keyMaterial = object->common.key.u.plaintext.keyMaterial;
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (object->common.key.encoding == CryptoKey_KEYSTORE_HSM)
    {
        if ((object->operationType == AESCBC_OP_TYPE_ONESTEP_ENCRYPT) ||
            (object->operationType == AESCBC_OP_TYPE_ENCRYPT_SEGMENTED) ||
            (object->operationType == AESCBC_OP_TYPE_FINALIZE_ENCRYPT_SEGMENTED))
        {
            usage = KEYSTORE_PSA_KEY_USAGE_ENCRYPT;
        }
        else
        {
            usage = KEYSTORE_PSA_KEY_USAGE_DECRYPT;
        }

        GET_KEY_ID(keyID, object->common.key.u.keyStore.keyID);

        keyStoreStatus = KeyStore_PSA_getKeyAttributes(keyID, &attributes);

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
        {
            keyStoreStatus = KeyStore_PSA_retrieveFromKeyStore(&object->common.key,
                                                               &KeyStore_keyingMaterial[0],
                                                               sizeof(KeyStore_keyingMaterial),
                                                               &object->keyAssetID,
                                                               KEYSTORE_PSA_ALG_CBC_NO_PADDING,
                                                               usage);

            if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
            {
                lifetime = KeyStore_PSA_getKeyLifetime(&attributes);

                object->keyLocation = KEYSTORE_PSA_KEY_LIFETIME_GET_LOCATION(lifetime);

                keyMaterial = &KeyStore_keyingMaterial[0];
            }
        }

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_INVALID_KEY_ID)
        {
            status = AESCBC_STATUS_KEYSTORE_INVALID_ID;
        }
        else if (keyStoreStatus != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            status = AESCBC_STATUS_KEYSTORE_GENERIC_ERROR;
        }

        if (status != AESCBC_STATUS_SUCCESS)
        {
            HSMXXF3_releaseLock();

            return status;
        }
    }
    #endif
    else
    {
        HSMXXF3_releaseLock();

        return AESCBC_STATUS_FEATURE_NOT_SUPPORTED;
    }

    /* keyMaterial will point to either KeyStore_keyingMaterial, or plaintext key material from
     * the application's CryptoKey object. It is possible that keyMaterial points to
     * KeyStore_keyingMaterial as an empty array - in this case, the object's keyLocation
     * will reflect that, so HSMXXF3 will retrieve the loaded HSM Asset ID instead.
     */
    HSMXXF3_constructAESCBCOneStepPhysicalToken(object, keyMaterial);

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
    if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
    {
        HSMXXF3_releaseLock();

        return AESCBC_STATUS_RESOURCE_UNAVAILABLE;
    }

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->common.returnBehavior,
                                    AESCBCXXF3HSM_OneStepPostProcessing,
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

/*
 *  ======== AESCBCXXF3HSM_addData ========
 */
int_fast16_t AESCBCXXF3HSM_addData(AESCBC_Handle handle, AESCBC_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCBC_STATUS_ERROR;
    }

    /*
     * Assert the segmented operation was setup.
     * LAES128 only supports CBC encryption.
     */
    DebugP_assert(object->operationType == AESCBC_OP_TYPE_ENCRYPT_SEGMENTED);

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESCBC_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    object->operation = (AESCBC_OperationUnion *)operation;

    /* Make internal copy of operational params */
    object->input       = operation->input;
    object->output      = operation->output;
    object->inputLength = operation->inputLength;

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When input or output is in PSRAM and exceeds the bounce slot, split into
     * block-aligned chunks. The IV for the next chunk is read from the result
     * token by processData post-processing and stored in object->iv, so CBC
     * continuity is maintained automatically across chunks.
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
            return AESCBC_STATUS_FEATURE_NOT_SUPPORTED;
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

            chunkStatus = AESCBCXXF3HSM_processData(handle);
            if (chunkStatus != AESCBC_STATUS_SUCCESS)
            {
                return chunkStatus;
            }

            chunkInput += chunkSize;
            chunkOutput += chunkSize;
            remainingBytes -= chunkSize;
        }
        return AESCBC_STATUS_SUCCESS;
    }
    #endif

    return AESCBCXXF3HSM_processData(handle);
}

/*
 *  ======== AESCBCXXF3HSM_finalize ========
 */
int_fast16_t AESCBCXXF3HSM_finalize(AESCBC_Handle handle, AESCBC_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCBCXXF3_Object *object = AESCBCXXF3_getObject(handle);
    int_fast16_t status;
    AESCBC_OperationType operationType;

    /* Assert the segmented operation was setup */
    DebugP_assert((object->operationType == AESCBC_OPERATION_TYPE_ENCRYPT_SEGMENTED) ||
                  (object->operationType == AESCBC_OPERATION_TYPE_DECRYPT_SEGMENTED));

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESCBC_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    if (object->operationType == AESCBC_OP_TYPE_ENCRYPT_SEGMENTED)
    {
        operationType = AESCBC_OP_TYPE_FINALIZE_ENCRYPT_SEGMENTED;
    }
    else
    {
        operationType = AESCBC_OP_TYPE_FINALIZE_DECRYPT_SEGMENTED;
    }

    if (operation->inputLength > 0U)
    {
        object->operationType = operationType;
        object->operation     = (AESCBC_OperationUnion *)operation;

        /* Make internal copy of operational params */
        object->input       = operation->input;
        object->output      = operation->output;
        object->inputLength = operation->inputLength;

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        /* When input or output is in PSRAM and exceeds the bounce slot, split into
         * block-aligned chunks. The IV for the next chunk is read from the result
         * token by processData post-processing and stored in object->iv, so CBC
         * continuity is maintained automatically across chunks.
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
                status = AESCBC_STATUS_FEATURE_NOT_SUPPORTED;
            }
            else
            {
                uint8_t *chunkInput   = (uint8_t *)operation->input;
                uint8_t *chunkOutput  = operation->output;
                size_t remainingBytes = operation->inputLength;

                status = AESCBC_STATUS_SUCCESS;
                while (remainingBytes > 0U)
                {
                    int_fast16_t chunkStatus;
                    size_t chunkSize = (remainingBytes > maxChunkSize) ? maxChunkSize : remainingBytes;

                    object->input       = chunkInput;
                    object->output      = chunkOutput;
                    object->inputLength = chunkSize;

                    chunkStatus = AESCBCXXF3HSM_processData(handle);
                    if (chunkStatus != AESCBC_STATUS_SUCCESS)
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
            status = AESCBCXXF3HSM_processData(handle);
        }
    #else
        status = AESCBCXXF3HSM_processData(handle);
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
            object->callbackFxn(handle, status, (AESCBC_OperationUnion *)operation, operationType);

            /* Always return success in callback mode */
            status = AESCBC_STATUS_SUCCESS;
        }
    }

    return status;
}

#endif
