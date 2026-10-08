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

#include <ti/drivers/aesecb/AESECBXXF3.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/AESECB.h>
#include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceXXF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>
#include <ti/devices/DeviceFamily.h>

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    #include <ti/drivers/dma/UDMALPF3.h>
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) && (ENABLE_KEY_STORAGE == 1))
    #error "Key storage is not supported for CC23X0"
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        #include <ti/drivers/xmem/XMEMWFF3.h>
        #include <ti/drivers/utils/Math.h>
    #endif
    #if (ENABLE_KEY_STORAGE == 1)
        #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
        #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
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
 * Default AES ECB auto config:
 *  ECB SRC as BUF
 *  Trigger points for auto ECB as RDTX3 and WRBUF3S
 *   (the first encryption starts by writing BUF3, the successive ones by reading TXT3)
 *  BUSHALT enabled
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #define AESECBXXF3_DEFAULT_AUTOCFG                                             \
        ((uint32_t)AES_AUTOCFG_AESSRC_BUF | (uint32_t)AES_AUTOCFG_TRGAES_WRBUF3S | \
         (uint32_t)AES_AUTOCFG_TRGAES_RDTXT3 | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/* Not used for CC35XX */
#else
    #error "Unsupported DeviceFamily_Parent for AESECBXXF3!"
#endif

/*
 * AES ECB DMA config:
 *  - ADRCHA = BUF0
 *  - TRGCHA = ECBSTART
 *  - ADRCHB = TXT0
 *  - TRGCHB = ECBDONE
 *  - DONEACT = GATE_TRGECB_ON_CHA_DEL (to avoid spurious last ECB using DMA
 *                                      if data length > 1 block)
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #define AESECBXXF3_DMA_CONFIG                                                           \
        ((uint32_t)AES_DMA_ADRCHA_BUF0 | (uint32_t)AES_DMA_TRGCHA_AESSTART |                \
         (uint32_t)AES_DMA_DONEACT_GATE_TRGAES_ON_CHA_DEL | (uint32_t)AES_DMA_ADRCHB_TXT0 | \
         (uint32_t)AES_DMA_TRGCHB_AESDONE)
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/* Not used for CC35XX */
#else
    #error "Unsupported DeviceFamily_Parent for AESECBXXF3!"
#endif

/* Forward declarations */
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
static int_fast16_t AESECBXXF3_checkOperation(const AESECBXXF3_Object *object, const AESECB_Operation *operation);
static inline void AESECBXXF3_processDataCPU(const uint8_t *input, uint8_t *output, size_t inputLength);
static inline void AESECBXXF3_processDataDMA(AESCommonXXF3_Object *object,
                                             const uint8_t *input,
                                             uint8_t *output,
                                             size_t inputLength);
static inline int_fast16_t AESECBXXF3_oneStepOperation(AESECB_Handle handle,
                                                       AESECB_Operation *operation,
                                                       AESECB_OperationType operationType);
static int_fast16_t AESECBXXF3_startOperation(AESECB_Handle handle, AESECB_Operation *operation);
static inline int_fast16_t AESECBXXF3_waitForResult(AESECB_Handle handle);
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
static int_fast16_t AESECBXXF3HSM_oneStepOperation(AESECB_Handle handle,
                                                   AESECB_Operation *operation,
                                                   AESECB_OperationType operationType);
static int_fast16_t AESECBXXF3HSM_processOneStep(AESECB_Handle handle);
static int_fast16_t AESECBXXF3HSM_processOneStepInternal(AESECB_Handle handle);

static int_fast16_t AESECBXXF3HSM_addData(AESECB_Handle handle, AESECB_Operation *operation);

static int_fast16_t AESECBXXF3HSM_finalize(AESECB_Handle handle, AESECB_Operation *operation);

#endif

#if (ENABLE_KEY_STORAGE == 1)
static void AESECBXXF3HSM_keyUsageFromOperationType(KeyStore_PSA_KeyUsage *usage, AESECB_OperationType operationType);
static int_fast16_t AESECBXXF3HSM_freeAllAssets(AESECB_Handle handle);

/*
 *  ======== AESECBXXF3HSM_keyUsageFromOperationType ========
 */
static void AESECBXXF3HSM_keyUsageFromOperationType(KeyStore_PSA_KeyUsage *usage, AESECB_OperationType operationType)
{
    if ((operationType == AESECB_OPERATION_TYPE_ENCRYPT) ||
        (operationType == AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED) ||
        (operationType == AESECB_OPERATION_TYPE_FINALIZE_ENCRYPT_SEGMENTED))
    {
        *usage = KEYSTORE_PSA_KEY_USAGE_ENCRYPT;
    }
    else
    {
        *usage = KEYSTORE_PSA_KEY_USAGE_DECRYPT;
    }
}

/*
 *  ======== AESECBXXF3HSM_freeAllAssets ========
 */
static int_fast16_t AESECBXXF3HSM_freeAllAssets(AESECB_Handle handle)
{
    AESECBXXF3_Object *object = (AESECBXXF3_Object *)handle->object;
    int_fast16_t status       = AESECB_STATUS_SUCCESS;
    KeyStore_PSA_KeyFileId keyID;

    if ((object->common.key.encoding == CryptoKey_KEYSTORE_HSM) &&
        (object->keyLocation == KEYSTORE_PSA_KEY_LOCATION_HSM_ASSET_STORE))
    {
        GET_KEY_ID(keyID, object->common.key.u.keyStore.keyID);

        /* For keys with a persistence that does not designate them to remain in asset store,
         * the following function will remove them. Otherwise, the key will remain in asset store
         * for future usage.
         */
        status = KeyStore_PSA_assetPostProcessing(keyID);

        if (status != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            status = AESECB_STATUS_ERROR;
        }
        else
        {
            status = AESECB_STATUS_SUCCESS;
        }
    }

    return status;
}
#endif

/*
 *  ======== AESECBXXF3_getObject ========
 */
static inline AESECBXXF3_Object *AESECBXXF3_getObject(AESECB_Handle handle)
{
    AESECBXXF3_Object *object = (AESECBXXF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESECBXXF3_hwiFxn ========
 */
static void AESECBXXF3_hwiFxn(uintptr_t arg0)
{
    AESECB_Handle handle      = (AESECB_Handle)arg0;
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

    /*
     * Only the output channel B interrupt is enabled.
     */
    uint32_t intStatus = AESGetMaskedInterruptStatus();

    /* Disable DMA, clear interupts, and release power constraint */
    AESCommonXXF3_cleanupHwi(&object->common);

    if ((intStatus & (uint32_t)AES_MIS_CHBDONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonXXF3_DMA_CHB_BITMASK);

        if ((object->operationType == AESECB_OPERATION_TYPE_ENCRYPT) ||
            (object->operationType == AESECB_OPERATION_TYPE_FINALIZE_ENCRYPT_SEGMENTED))
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
 *  ======== AESECB_init ========
 */
void AESECB_init(void)
{
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    HSMXXF3_constructRTOSObjects();
#endif
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCommonXXF3_init();
#endif
}

/*
 *  ======== AESECB_construct ========
 */
AESECB_Handle AESECB_construct(AESECB_Config *config, const AESECB_Params *params)
{
    DebugP_assert(config);

    AESECB_Handle handle      = config;
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Callback return mode is not supported for CC35XX for now */
    if ((params != NULL) && (params->returnBehavior == AESECB_RETURN_BEHAVIOR_CALLBACK))
    {
        return NULL;
    }
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
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
        params = &AESECB_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AESECB_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->callbackFxn = params->callbackFxn;
    object->threadSafe  = true;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    object->common.returnBehavior = (AES_ReturnBehavior)params->returnBehavior;
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    int_fast16_t status;

    status = AESCommonXXF3_construct(&object->common, (AES_ReturnBehavior)params->returnBehavior, params->timeout);

    if (status != AES_STATUS_SUCCESS)
    {
        return NULL;
    }
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return handle;
}

/*
 *  ======== AESECB_close ========
 */
void AESECB_close(AESECB_Handle handle)
{
    DebugP_assert(handle);

    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCommonXXF3_close(&object->common);
#else
    /* Mark the module as unavailable */
    object->common.isOpen = false;
#endif
}

/*
 *  ======== AESECB_oneStepEncrypt ========
 */
int_fast16_t AESECB_oneStepEncrypt(AESECB_Handle handle, AESECB_Operation *operation)
{
    int_fast16_t status = AESECB_STATUS_SUCCESS;

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if (operation->key->encoding == CryptoKey_PLAINTEXT || operation->key->encoding == CryptoKey_KEYSTORE)
    {
        status = AESECBXXF3_oneStepOperation(handle, operation, AESECB_OPERATION_TYPE_ENCRYPT);
    }
    else
#endif
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
        if (operation->key->encoding == CryptoKey_PLAINTEXT_HSM || operation->key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        status = AESECBXXF3HSM_oneStepOperation(handle, operation, AESECB_OPERATION_TYPE_ENCRYPT);
    }
    else
#endif
    {
        status = AESECB_STATUS_ERROR;
    }
    return status;
}

/*
 *  ======== AESECB_oneStepDecrypt ========
 */
int_fast16_t AESECB_oneStepDecrypt(AESECB_Handle handle, AESECB_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    int_fast16_t status = AESECB_STATUS_SUCCESS;

    if (operation->key->encoding == CryptoKey_PLAINTEXT || operation->key->encoding == CryptoKey_KEYSTORE)
    {
        status = AESECB_STATUS_FEATURE_NOT_SUPPORTED;
    }
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    else if (operation->key->encoding == CryptoKey_PLAINTEXT_HSM || operation->key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        status = AESECBXXF3HSM_oneStepOperation(handle, operation, AESECB_OPERATION_TYPE_DECRYPT);
    }
#endif
    else
    {
        status = AESECB_STATUS_ERROR;
    }

    return status;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESECBXXF3_checkOperation ========
 */
static int_fast16_t AESECBXXF3_checkOperation(const AESECBXXF3_Object *object, const AESECB_Operation *operation)
{
    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESECB_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
    #endif

    /* Verify input length is a non-zero multiple of the AES block size */
    if ((operation->inputLength == 0UL) || (AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->inputLength) > 0UL))
    {
        return AESECB_STATUS_ERROR;
    }

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESECB_STATUS_ERROR;
    }

    return AESECB_STATUS_SUCCESS;
}

/*
 *  ======== AESECBXXF3_oneStepOperation ========
 */
static inline int_fast16_t AESECBXXF3_oneStepOperation(AESECB_Handle handle,
                                                       AESECB_Operation *operation,
                                                       AESECB_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);
    int_fast16_t status;

    status = AESECBXXF3_checkOperation(object, operation);

    if (status != AESECB_STATUS_SUCCESS)
    {
        return status;
    }

    /*
     * Check that there are no operations already in progress.
     * If not, mark the current operation to be in progress
     */
    status = AESCommonXXF3_setOperationInProgress(&object->common);

    if (status != AESECB_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
        {
            AESCommonXXF3_clearOperationInProgress(&object->common);
            return AESECB_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation     = operation;
    object->operationType = operationType;

    object->common.key          = *(operation->key);
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESECB_STATUS_SUCCESS;

    return AESECBXXF3_startOperation(handle, operation);
}

/*
 *  ======== AESECBXXF3_startOperation ========
 */
static int_fast16_t AESECBXXF3_startOperation(AESECB_Handle handle, AESECB_Operation *operation)
{
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);
    int_fast16_t status;
    #if (ENABLE_KEY_STORAGE == 1)
    int_fast16_t keyStoreStatus;
    uint8_t KeyStore_keyingMaterial[AESCommonXXF3_256_KEY_LENGTH_BYTES];
    KeyStore_PSA_KeyUsage usage;
    #endif

    if (operation->key->encoding == CryptoKey_PLAINTEXT)
    {
        /* Set up the key and AES engine to begin an operation */
        if (operation->inputLength == AES_BLOCK_SIZE)
        {
            AESCommonXXF3_setupOperation(&object->common.key, AESECBXXF3_SINGLE_BLOCK_AUTOCFG);
        }
        else
        {
            AESCommonXXF3_setupOperation(&object->common.key, AESECBXXF3_DEFAULT_AUTOCFG);
        }
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (operation->key->encoding == CryptoKey_KEYSTORE)
    {
        AESECBXXF3HSM_keyUsageFromOperationType(&usage, object->operationType);

        keyStoreStatus = KeyStore_PSA_retrieveFromKeyStore(operation->key,
                                                           &KeyStore_keyingMaterial[0],
                                                           sizeof(KeyStore_keyingMaterial),
                                                           &object->keyAssetID,
                                                           KEYSTORE_PSA_ALG_ECB_NO_PADDING,
                                                           usage);
        if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
        {
            AESWriteKEY(KeyStore_keyingMaterial);

            if (operation->inputLength == AES_BLOCK_SIZE)
            {
                /* Set AUTOCFG */
                AESSetAUTOCFG(AESECBXXF3_SINGLE_BLOCK_AUTOCFG);
            }
            else
            {
                /* Set AUTOCFG */
                AESSetAUTOCFG(AESECBXXF3_DEFAULT_AUTOCFG);
            }
        }
        else if (keyStoreStatus == KEYSTORE_PSA_STATUS_INVALID_KEY_ID)
        {
            return AESECB_STATUS_KEYSTORE_INVALID_ID;
        }
        else
        {
            return AESECB_STATUS_KEYSTORE_GENERIC_ERROR;
        }
    }
    #endif
    else
    {
        return AESECB_STATUS_FEATURE_NOT_SUPPORTED;
    }

    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        (operation->inputLength >= AESECBXXF3_DMA_SIZE_THRESHOLD))
    {
        /*
         * We need to set the HWI function and priority since the same physical
         * interrupt is shared by multiple drivers and they all need to coexist.
         * Whenever a driver starts an operation, it registers its HWI callback
         * with the OS.
         */
        AESECBXXF3_HWAttrs const *hwAttrs = handle->hwAttrs;
        AESCommonXXF3_setupHwi(AESECBXXF3_hwiFxn, (uintptr_t)handle, hwAttrs->intPriority);
    }

    AESECBXXF3_processData(&object->common, operation->input, operation->output, operation->inputLength);

    status = AESECBXXF3_waitForResult(handle);

    return status;
}

/*
 *  ======== AESECBXXF3_processData ========
 */
void AESECBXXF3_processData(AESCommonXXF3_Object *object, const uint8_t *input, uint8_t *output, size_t inputLength)
{
    /*
     * Process all operations with data length less than the DMA size
     * threshold as a polling mode operation.
     */
    if ((object->returnBehavior == AES_RETURN_BEHAVIOR_POLLING) || (inputLength < AESECBXXF3_DMA_SIZE_THRESHOLD))
    {
        /* Process all blocks with CPU R/W */
        AESECBXXF3_processDataCPU(input, output, inputLength);
    }
    else
    {
        AESECBXXF3_processDataDMA(object, input, output, inputLength);
    }
}

/*
 *  ======== AESECBXXF3_processDataCPU ========
 */
static inline void AESECBXXF3_processDataCPU(const uint8_t *input, uint8_t *output, size_t inputLength)
{
    /*
     * For efficiency, the next block of data can be written to AES BUF regs
     * while the AES engine is encrypting the previous block. The AES engine
     * takes 23-cycles to encrypt a block. If the SW can load blocks faster
     * than that, SW must wait until the AES HW is idle after writing two
     * blocks consecutively to avoid overwriting data before the AES engine
     * can consume it.
     */
    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
    size_t inputBytesProcessed  = 0;
    size_t outputBytesProcessed = 0;

    if (!IS_WORD_ALIGNED(input) || !IS_WORD_ALIGNED(output))
    {
        /* Write first block of input to trigger encryption */
        AESWriteBUF(&input[inputBytesProcessed]);
        inputBytesProcessed += AES_BLOCK_SIZE;

        while (inputBytesProcessed < inputLength)
        {
            /* Preload next input block */
            AESWriteBUF(&input[inputBytesProcessed]);
            inputBytesProcessed += AES_BLOCK_SIZE;

        #ifdef AES_BUSHALT_DISABLED
            /* Wait for encryption of previous input to complete */
            while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}
        #endif
            /*
             * Read output and trigger encryption of next input that was
             * preloaded at the start of this loop.
             */
            AESReadTXT(&output[outputBytesProcessed]);
            outputBytesProcessed += AES_BLOCK_SIZE;
        }

        /* Avoid triggering a spurious encryption upon reading the final output */
        AESClearAUTOCFGTrigger();
        #ifdef AES_BUSHALT_DISABLED
        /* Wait for encryption of final input block */
        while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}
        #endif
        /* Read final output */
        AESReadTXT(&output[outputBytesProcessed]);
    }
    else
    #endif /* (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 1) */
    {
        AESProcessAlignedBlocksECB((const uint32_t *)input,
                                   (uint32_t *)output,
                                   (uint32_t)AES_GET_NUM_BLOCKS(inputLength));
    }
}

/*
 *  ======== AESECBXXF3_processDataDMA ========
 */
static inline void AESECBXXF3_processDataDMA(AESCommonXXF3_Object *object,
                                             const uint8_t *input,
                                             uint8_t *output,
                                             size_t inputLength)
{
    /* Clear BUSHALT when using DMA */
    AESClearAUTOCFGBusHalt();

    /* Setup DMA configuration and set power constraint */
    AESCommonXXF3_setupDMA(object, AESECBXXF3_DMA_CONFIG);

    AESCommonXXF3_configInputDMA(input, inputLength);
    AESCommonXXF3_configOutputDMA(output, inputLength);

    /* Enable interrupt upon output DMA done */
    AESSetIMASK((uint32_t)AES_IMASK_CHBDONE_M);

    /* Manually trigger the DMA to start the ECB operation */
    AESSetTrigger((uint32_t)AES_TRG_DMACHA);
}

/*
 *  ======== AESECBXXF3_waitForResult ========
 */
static inline int_fast16_t AESECBXXF3_waitForResult(AESECB_Handle handle)
{
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);
    int_fast16_t status;

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (object->operation->inputLength < AESECBXXF3_DMA_SIZE_THRESHOLD))
    {
        /*
         * Save the returnStatus prior clearing operationInProgress or
         * releasing the access semaphore in case it's overwritten.
         */
        status = object->common.returnStatus;

        /* Mark that the current single-step or multi-step operation is done */
        if (object->operationType != AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED)
        {
            AESCommonXXF3_clearOperationInProgress(&object->common);
        }

        AESCommonXXF3_cleanup(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, object->operation, object->operationType);

            /* Always return success in callback mode */
            status = AESECB_STATUS_SUCCESS;
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
        status = AESECB_STATUS_SUCCESS;
    }

    return status;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESECB_setupEncrypt ========
 */
int_fast16_t AESECB_setupEncrypt(AESECB_Handle handle, const CryptoKey *key)
{
    DebugP_assert(handle);
    int_fast16_t status       = AESECB_STATUS_SUCCESS;
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

    /*
     * Key material pointer and length are not checked until adding or
     * finalizing data.
     */
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if ((key->encoding == CryptoKey_PLAINTEXT) || (key->encoding == CryptoKey_KEYSTORE))
    {
        /* When using the AES driver with the LAES engine */
        status = AESCommonXXF3_setupSegmentedOperation(&object->common, key);
    }
    else
#endif
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
        if (key->encoding == CryptoKey_PLAINTEXT_HSM || key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
        {
            return AESECB_STATUS_ERROR;
        }

        /* A segmented operation may have been started but not finalized yet */
        if (object->segmentedOperationInProgress)
        {
            return AESECB_STATUS_ERROR;
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
        status = AESECB_STATUS_ERROR;
    }

    if (status == AES_STATUS_SUCCESS)
    {
        /*
         * Initialize operation pointer to NULL in case AESECB_cancelOperation
         * is called after AESECB_setupXXXX and callback should be skipped.
         */
        object->operation = NULL;
    }

    object->operationType = AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED;

    return status;
}

/*
 *  ======== AESECB_setupDecrypt ========
 */
int_fast16_t AESECB_setupDecrypt(AESECB_Handle handle, const CryptoKey *key)
{
    DebugP_assert(handle);
    DebugP_assert(key);

    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);
    int_fast16_t status       = AESECB_STATUS_SUCCESS;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    if (key->encoding == CryptoKey_PLAINTEXT_HSM || key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
        if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
        {
            return AESECB_STATUS_ERROR;
        }

        /* A segmented operation may have been started but not finalized yet */
        if (object->segmentedOperationInProgress)
        {
            return AESECB_STATUS_ERROR;
        }

        /* Make internal copy of crypto key */
        object->common.key = *key;

        /* returnStatus is only changed in the case of an error or cancellation */
        object->common.returnStatus = AES_STATUS_SUCCESS;

        /* Initialize operation pointer to NULL in case AESECB_cancelOperation
         * is called after AESECB_setupXXXX and callback should be skipped.
         */
        object->operation = NULL;

        object->operationType = AESECB_OPERATION_TYPE_DECRYPT_SEGMENTED;

        object->segmentedOperationInProgress = true;
    }
    else
#endif
    {
        object->common.returnStatus = AESECB_STATUS_FEATURE_NOT_SUPPORTED;
        status                      = AESECB_STATUS_FEATURE_NOT_SUPPORTED;
    }

    /* Save the error status in case addData or finalize is called afterward */

    return status;
}

/*
 *  ======== AESECB_addData ========
 */
int_fast16_t AESECB_addData(AESECB_Handle handle, AESECB_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    int_fast16_t status = AESECB_STATUS_FEATURE_NOT_SUPPORTED;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    if (operation->key->encoding == CryptoKey_PLAINTEXT_HSM || operation->key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        return AESECBXXF3HSM_addData(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

    /*
     * Assert the segmented operation was setup.
     * LPF3 only supports ECB encryption.
     */
    DebugP_assert(object->operationType == AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED);

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESECB_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    status = AESECBXXF3_checkOperation(object, operation);

    if (status != AESECB_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
        {
            return AESECB_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation = operation;

    status = AESECBXXF3_startOperation(handle, operation);
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

/*
 *  ======== AESECB_finalize ========
 */
int_fast16_t AESECB_finalize(AESECB_Handle handle, AESECB_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    int_fast16_t status = AESECB_STATUS_FEATURE_NOT_SUPPORTED;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    if (operation->key->encoding == CryptoKey_PLAINTEXT_HSM || operation->key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        return AESECBXXF3HSM_finalize(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

    /*
     * Assert the segmented operation was setup.
     * LPF3 only supports ECB encryption.
     */
    DebugP_assert(object->operationType == AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED);

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESECB_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    if (operation->inputLength > 0U)
    {
    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
        /* Check word-alignment of input & output pointers */
        if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
        {
            return AESECB_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
        }
    #endif

        /* Verify input length is a multiple of the AES block size */
        if ((AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->inputLength) > 0U))
        {
            return AESECB_STATUS_ERROR;
        }

        /* Check DMA xfer limit for blocking and callback modes */
        if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
            !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
        {
            return AESECB_STATUS_ERROR;
        }
    }

    AESECB_OperationType operationType = AESECB_OPERATION_TYPE_FINALIZE_ENCRYPT_SEGMENTED;

    if (operation->inputLength > 0U)
    {
        /* Try and obtain access to the crypto module */
        if (object->threadSafe)
        {
            if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
            {
                return AESECB_STATUS_RESOURCE_UNAVAILABLE;
            }

            object->common.cryptoResourceLocked = true;
        }

        object->operationType = operationType;
        object->operation     = operation;

        status = AESECBXXF3_startOperation(handle, operation);
    }
    else /* Operation was finalized without additional data to process */
    {
        status = object->common.returnStatus;

        AESCommonXXF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, operation, operationType);

            /* Always return success in callback mode */
            status = AESECB_STATUS_SUCCESS;
        }
    }
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

/*
 *  ======== AESECB_cancelOperation ========
 */
int_fast16_t AESECB_cancelOperation(AESECB_Handle handle)
{
    DebugP_assert(handle);

    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

    /* Cancellation is only supported in callback mode */
    if (object->common.returnBehavior != AES_RETURN_BEHAVIOR_CALLBACK)
    {
        return AESECB_STATUS_ERROR;
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
        return AESECB_STATUS_SUCCESS;
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
        (void)AESECBXXF3HSM_freeAllAssets(handle);
    #endif
    }
#endif

    /*
     * Operation pointer could be NULL if a segmented operation was setup
     * but neither AESECB_addData or AESECB_finalize was called.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
    {
        /* Call the callback function provided by the application */
        object->callbackFxn(handle, AESECB_STATUS_CANCELED, object->operation, object->operationType);
    }

    return AESECB_STATUS_SUCCESS;
}

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)

/*
 *  ======== AESECBXXF3HSM_oneStepOperation ========
 */
static int_fast16_t AESECBXXF3HSM_oneStepOperation(AESECB_Handle handle,
                                                   AESECB_Operation *operation,
                                                   AESECB_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return HSMXXF3_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESECB_STATUS_ERROR;
    }

    object->operation     = operation;
    object->operationType = operationType;

    object->common.key          = *(operation->key);
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESECB_STATUS_SUCCESS;

    return AESECBXXF3HSM_processOneStep(handle);
}

/*
 *  ======== AESECBXXF3HSM_OneStepPostProcessing ========
 */
static inline void AESECBXXF3HSM_OneStepPostProcessing(uintptr_t arg0)
{
    AESECB_Handle handle      = (AESECB_Handle)arg0;
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);
    int_fast16_t status       = AESECB_STATUS_ERROR;
    int32_t physicalResult    = HSMXXF3_getResultCode();
    int32_t tokenResult       = physicalResult & HSMXXF3_RETVAL_MASK;

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = AESECB_STATUS_SUCCESS;
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    /* Free all assets. This includes key-related asset and state-related asset
     * (temporary asset).
     */
    #if (ENABLE_KEY_STORAGE == 1)
    if (AESECBXXF3HSM_freeAllAssets(handle) != AESECB_STATUS_SUCCESS)
    {
        status = AESECB_STATUS_ERROR;
    }
    #endif

    object->common.returnStatus = status;

    HSMXXF3_releaseLock();

    if ((object->operationType == AESECB_OPERATION_TYPE_FINALIZE_ENCRYPT_SEGMENTED) ||
        (object->operationType == AESECB_OPERATION_TYPE_FINALIZE_DECRYPT_SEGMENTED) ||
        (object->operationType == AESECB_OPERATION_TYPE_ENCRYPT) ||
        (object->operationType == AESECB_OPERATION_TYPE_DECRYPT))
    {
        object->segmentedOperationInProgress = false;
    }

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
    }
}

/*
 *  ======== AESECBXXF3HSM_processOneStep ========
 *
 *  On CC35XX, splits the operation into block-aligned chunks when input or
 *  output exceeds the PSRAM bounce slot, then delegates each chunk to
 *  processOneStepInternal. ECB blocks are independent so no state carries
 *  between chunks. CALLBACK mode is not supported for chunked operations.
 *  On all other targets, calls processOneStepInternal directly.
 */
static int_fast16_t AESECBXXF3HSM_processOneStep(AESECB_Handle handle)
{
    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    AESECBXXF3_Object *object   = AESECBXXF3_getObject(handle);
    AESECB_Operation *operation = object->operation;

    if (XMEMWFF3_isAddrExternal((uintptr_t)operation->output) &&
        (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK))
    {
        /* Callback mode is not supported by the HSM driver when the output
         * buffer is in external memory.
         */
        return AESECB_STATUS_FEATURE_NOT_SUPPORTED;
    }

    /* Calculate maximum chunk size, based on input/output locations and
     * input/output bounce buffer sizes. If the input address is in internal
     * memory, the input bounce buffer size is irrelevant, and is set to maximum
     * for the calculation, and the same logic applies to the output.
     * If either sizes get set to 0, the operation can not be completed, and an
     * error is returned.
     */
    size_t inputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)operation->input) ? HSMXXF3_inputBounce.size : SIZE_MAX;

    size_t outputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)operation->output) ? HSMXXF3_outputBounce.size
                                                                                    : SIZE_MAX;

    if (inputBounceSize == 0 || outputBounceSize == 0)
    {
        return AESECB_STATUS_ERROR;
    }

    size_t minBounceSize = Math_MIN(inputBounceSize, outputBounceSize);

    /* Each chunk must be a multiple of the AES block size. Round down to the
     * nearest block boundary.
     */
    size_t maxChunkSize = minBounceSize & ~(AES_BLOCK_SIZE - 1U);

    /* When input or output is in PSRAM and exceeds the bounce slot, split into
     * block-aligned chunks.
     */
    if ((operation->inputLength > maxChunkSize) &&
        (XMEMWFF3_isAddrExternal((uintptr_t)operation->input) || XMEMWFF3_isAddrExternal((uintptr_t)operation->output)))
    {
        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            return AESECB_STATUS_FEATURE_NOT_SUPPORTED;
        }

        AESECB_Operation chunkOperation = *operation;
        uint8_t *chunkInput             = (uint8_t *)operation->input;
        uint8_t *chunkOutput            = (uint8_t *)operation->output;
        size_t remainingBytes           = operation->inputLength;
        int_fast16_t status             = AESECB_STATUS_SUCCESS;

        while (remainingBytes > 0U)
        {
            size_t chunkSize = (remainingBytes > maxChunkSize) ? maxChunkSize : remainingBytes;

            chunkOperation.input       = chunkInput;
            chunkOperation.output      = chunkOutput;
            chunkOperation.inputLength = (uint32_t)chunkSize;
            object->operation          = &chunkOperation;

            status = AESECBXXF3HSM_processOneStepInternal(handle);
            if (status != AESECB_STATUS_SUCCESS)
            {
                return status;
            }

            chunkInput += chunkSize;
            chunkOutput += chunkSize;
            remainingBytes -= chunkSize;
        }
        return status;
    }
    #endif

    return AESECBXXF3HSM_processOneStepInternal(handle);
}

/*
 *  ======== AESECBXXF3HSM_processOneStepInternal ========
 */
static int_fast16_t AESECBXXF3HSM_processOneStepInternal(AESECB_Handle handle)
{
    int_fast16_t status       = AESECB_STATUS_ERROR;
    int_fast16_t hsmRetval    = HSMXXF3_STATUS_ERROR;
    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);
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
        return AESECB_STATUS_RESOURCE_UNAVAILABLE;
    }

    if (object->common.key.encoding == CryptoKey_PLAINTEXT_HSM)
    {
        HSMXXF3_constructAESECBOneStepPhysicalToken(object, object->common.key.u.plaintext.keyMaterial);
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (object->common.key.encoding == CryptoKey_KEYSTORE_HSM)
    {
        GET_KEY_ID(keyID, object->common.key.u.keyStore.keyID);

        keyStoreStatus = KeyStore_PSA_getKeyAttributes(keyID, &attributes);

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
        {
            AESECBXXF3HSM_keyUsageFromOperationType(&usage, object->operationType);

            keyStoreStatus = KeyStore_PSA_retrieveFromKeyStore(&object->common.key,
                                                               &KeyStore_keyingMaterial[0],
                                                               sizeof(KeyStore_keyingMaterial),
                                                               &object->keyAssetID,
                                                               KEYSTORE_PSA_ALG_ECB_NO_PADDING,
                                                               usage);

            if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
            {
                lifetime = KeyStore_PSA_getKeyLifetime(&attributes);

                object->keyLocation = KEYSTORE_PSA_KEY_LIFETIME_GET_LOCATION(lifetime);
            }
        }

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_INVALID_KEY_ID)
        {
            HSMXXF3_releaseLock();

            return AESECB_STATUS_KEYSTORE_INVALID_ID;
        }
        else if (keyStoreStatus != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            HSMXXF3_releaseLock();

            return AESECB_STATUS_KEYSTORE_GENERIC_ERROR;
        }

        HSMXXF3_constructAESECBOneStepPhysicalToken(object, &KeyStore_keyingMaterial[0]);
    }
    #endif
    else
    {
        HSMXXF3_releaseLock();

        return AESECB_STATUS_FEATURE_NOT_SUPPORTED;
    }

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
    if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
    {
        HSMXXF3_releaseLock();

        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->common.returnBehavior,
                                    AESECBXXF3HSM_OneStepPostProcessing,
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

static int_fast16_t AESECBXXF3HSM_addData(AESECB_Handle handle, AESECB_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESECB_STATUS_ERROR;
    }

    /*
     * Assert the segmented operation was setup.
     * F3 only supports ECB encryption.
     */
    DebugP_assert((object->operationType == AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED) ||
                  (object->operationType == AESECB_OPERATION_TYPE_DECRYPT_SEGMENTED));

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESECB_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    object->operation = operation;

    return AESECBXXF3HSM_processOneStep(handle);
}

static int_fast16_t AESECBXXF3HSM_finalize(AESECB_Handle handle, AESECB_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBXXF3_Object *object = AESECBXXF3_getObject(handle);
    int_fast16_t status;

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESECB_STATUS_ERROR;
    }

    /*
     * Assert the segmented operation was setup.
     * F3 only supports ECB encryption.
     */
    DebugP_assert((object->operationType == AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED) ||
                  (object->operationType == AESECB_OPERATION_TYPE_DECRYPT_SEGMENTED));

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESECB_STATUS_SUCCESS)
    {
        /*
         * Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

    if (object->operationType == AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED)
    {
        object->operationType = AESECB_OPERATION_TYPE_FINALIZE_ENCRYPT_SEGMENTED;
    }
    else if (object->operationType == AESECB_OPERATION_TYPE_DECRYPT_SEGMENTED)
    {
        object->operationType = AESECB_OPERATION_TYPE_FINALIZE_DECRYPT_SEGMENTED;
    }

    if (operation->inputLength > 0U)
    {
        object->operation = operation;

        status = AESECBXXF3HSM_processOneStep(handle);
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
            object->callbackFxn(handle, status, operation, object->operationType);

            /* Always return success in callback mode */
            status = AESECB_STATUS_SUCCESS;
        }
    }

    return status;
}

#endif
