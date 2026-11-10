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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <ti/drivers/aesgcm/AESGCMXXF3HSM.h>
#include <ti/drivers/aesecb/AESECBXXF3.h>
#include <ti/drivers/aesctr/AESCTRXXF3.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceXXF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>
#include <ti/drivers/cryptoutils/utils/CryptoUtils.h>

#include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
#include <ti/drivers/cryptoutils/hsm/HSMXXF3Utility.h>

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/devices/DeviceFamily.h>

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    #include <ti/drivers/power/PowerCC27XX.h>
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #include <ti/drivers/power/PowerCC23X1.h>
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    #include <ti/drivers/power/PowerWFF3.h>
    #include <ti/drivers/xmem/XMEMWFF3.h>
    #include <ti/drivers/utils/Math.h>
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
    #include DeviceFamily_constructPath(driverlib/aes.h)
    #include DeviceFamily_constructPath(inc/hw_aes.h)
    #include DeviceFamily_constructPath(inc/hw_ints.h)
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) && (ENABLE_KEY_STORAGE == 1))
    #error "Key storage is not supported for CC23X0"
#endif

#if (ENABLE_KEY_STORAGE == 1)
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
#endif

/* Forward declarations */
#if (ENABLE_KEY_STORAGE == 1)
static int_fast16_t AESGCMXXF3HSM_getKeyMaterial(AESGCMXXF3HSM_Object *object);
#endif
static void AESGCMXXF3HSM_setupObjectMetaData(AESGCMXXF3HSM_Object *object);
static int_fast16_t AESGCMXXF3HSM_oneStepOperation(AESGCM_Handle handle,
                                                   AESGCM_OneStepOperation *operation,
                                                   AESGCM_OperationType operationType);
static int_fast16_t AESGCMXXF3HSM_performHSMOperation(AESGCM_Handle handle);
static void AESGCMXXF3HSM_postProcessingCommon(AESGCM_Handle handle, int_fast16_t status, int8_t tokenResult);
static int_fast16_t AESGCMXXF3HSM_setupSegmentedOperation(AESGCM_Handle handle,
                                                          AESGCM_OperationType operationType,
                                                          const CryptoKey *key,
                                                          size_t totalAADLength,
                                                          size_t totalDataLength);
static int_fast16_t AESGCMXXF3HSM_addData(AESGCM_Handle handle,
                                          AESGCM_OperationType operationType,
                                          AESGCM_OperationUnion *operation);
static int_fast16_t AESGCMXXF3HSM_performFinalizeChecks(const AESGCMXXF3HSM_Object *object,
                                                        const AESGCM_SegmentedFinalizeOperation *operation);
static int_fast16_t AESGCMXXF3HSM_finalizeCommon(AESGCM_Handle handle,
                                                 AESGCM_OperationType operationType,
                                                 AESGCM_SegmentedFinalizeOperation *operation);
static int_fast16_t AESGCMXXF3HSM_createTempAssetID(AESGCM_Handle handle);
static int_fast16_t AESGCMXXF3HSM_freeAllAssets(AESGCM_Handle handle);
static int_fast16_t AESGCMXXF3HSM_freeTempAssetID(AESGCM_Handle handle);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESGCMXXF3HSM_dataMaxChunkSize ========
 *  Returns the largest block-aligned chunk of data/input/output that can be staged
 *  through the bounce buffers in a single token. Considers only whichever buffers
 *  are actually in external memory; internal-RAM buffers bypass the bounce path.
 *  Returns 0 if a required bounce buffer has zero size (misconfigured).
 */
static size_t AESGCMXXF3HSM_dataMaxChunkSize(const void *input, const void *output)
{
    size_t inputBounceSize  = XMEMWFF3_isAddrExternal((uintptr_t)input) ? HSMXXF3_inputBounce.size : SIZE_MAX;
    size_t outputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)output) ? HSMXXF3_outputBounce.size : SIZE_MAX;

    if ((inputBounceSize == 0U) || (outputBounceSize == 0U))
    {
        return 0U;
    }

    return Math_MIN(inputBounceSize, outputBounceSize) & ~(AES_BLOCK_SIZE - 1U);
}

/*
 *  ======== AESGCMXXF3HSM_aadMaxChunkSize ========
 *  Returns the largest block-aligned chunk of AAD that can be staged through the
 *  aux bounce buffer in a single token. Returns 0 if auxBounce is not configured.
 */
static size_t AESGCMXXF3HSM_aadMaxChunkSize(void)
{
    if (HSMXXF3_auxBounce.size == 0U)
    {
        return 0U;
    }

    return HSMXXF3_auxBounce.size & ~(AES_BLOCK_SIZE - 1U);
}
#endif

/*
 *  ======== AESGCMXXF3HSM_getObject ========
 */
static inline AESGCMXXF3HSM_Object *AESGCMXXF3HSM_getObject(AESGCM_Handle handle)
{
    AESGCMXXF3HSM_Object *object = (AESGCMXXF3HSM_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

/*
 *  ======== AESGCM_init ========
 */
void AESGCM_init(void)
{
    HSMXXF3_constructRTOSObjects();
}

/*
 *  ======== AESGCM_construct ========
 */
AESGCM_Handle AESGCM_construct(AESGCM_Config *config, const AESGCM_Params *params)
{
    DebugP_assert(config);

    AESGCM_Handle handle         = config;
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Callback return mode is not supported for CC35XX for now */
    if ((params != NULL) && (params->returnBehavior == AESGCM_RETURN_BEHAVIOR_CALLBACK))
    {
        return NULL;
    }
#endif

    /* Initialize and boot HSM */
    if (HSMXXF3_init() != HSMXXF3_STATUS_SUCCESS)
    {
        /* Upon HSM Boot failure, the AES-GCM Driver stores the failure status in the object. */
        object->hsmStatus = HSMXXF3_STATUS_ERROR;

        return NULL;
    }
    else
    {
        object->hsmStatus = HSMXXF3_STATUS_SUCCESS;
    }

    /* If params are NULL, use defaults */
    if (params == NULL)
    {
        params = &AESGCM_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AESGCM_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->callbackFxn = params->callbackFxn;

    object->common.returnBehavior = (AES_ReturnBehavior)params->returnBehavior;

    if (params->returnBehavior == AESGCM_RETURN_BEHAVIOR_BLOCKING)
    {
        object->common.semaphoreTimeout = params->timeout;
    }
    else
    {
        object->common.semaphoreTimeout = SemaphoreP_NO_WAIT;
    }

    object->segmentedOperationInProgress = false;

    return handle;
}

/*
 *  ======== AESGCM_close ========
 */
void AESGCM_close(AESGCM_Handle handle)
{
    DebugP_assert(handle);
}

/*
 *  ======== AESGCM_oneStepEncrypt ========
 */
int_fast16_t AESGCM_oneStepEncrypt(AESGCM_Handle handle, AESGCM_OneStepOperation *operationStruct)
{
    return AESGCMXXF3HSM_oneStepOperation(handle, operationStruct, AESGCM_OPERATION_TYPE_ENCRYPT);
}

/*
 *  ======== AESGCM_oneStepDecrypt ========
 */
int_fast16_t AESGCM_oneStepDecrypt(AESGCM_Handle handle, AESGCM_OneStepOperation *operationStruct)
{
    return AESGCMXXF3HSM_oneStepOperation(handle, operationStruct, AESGCM_OPERATION_TYPE_DECRYPT);
}

/*
 *  ======== AESGCMXXF3HSM_oneStepOperation ========
 */
static int_fast16_t AESGCMXXF3HSM_oneStepOperation(AESGCM_Handle handle,
                                                   AESGCM_OneStepOperation *operation,
                                                   AESGCM_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    /* No need to assert operationType since we control it within the driver */

    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_SUCCESS;

    /* Verify input + AAD length is non-zero */
    if ((operation->inputLength + operation->aadLength) == 0U)
    {
        return AESGCM_STATUS_ERROR;
    }

    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESGCM_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESGCM_STATUS_ERROR;
    }

    object->operation           = (AESGCM_OperationUnion *)operation;
    object->operationType       = operationType;
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESGCM_STATUS_SUCCESS;

    /* Make internal copy of operational params */
    object->common.key = *(operation->key);
    object->input      = operation->input;
    object->output     = operation->output;
    object->mac        = operation->mac;
    object->aad        = operation->aad;
    object->iv         = operation->iv;

    object->inputLength     = operation->inputLength;
    object->totalDataLength = operation->inputLength;
    object->macLength       = operation->macLength;
    object->aadLength       = operation->aadLength;
    object->totalAADLength  = operation->aadLength;
    object->ivLength        = operation->ivLength;

    object->totalDataLengthRemaining = object->totalDataLength;
    object->totalAADLengthRemaining  = object->totalAADLength;

    object->tempAssetID = 0U;

    if ((operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT) && (operation->macLength == 0U))
    {
        /* We are not supplied the macLength at this point of the segmented operation.
         * Therefore, the driver gives it a dummy length which is the max length until
         * the user supplies the desired macLength in _setLengths() API.
         */
        object->macLength = HSM_MAC_MAX_LENGTH;
    }

    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    /* If input length is larger than 1 block and it is not a multiple of block-size,
     * then a one step operation becomes a segmented operation and requires a state
     * asset to store the intermediate state of the MAC within the HSM.
     */
    if ((operation->inputLength > AES_BLOCK_SIZE) &&
        (!HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE((operation->inputLength))))
    {
        status = AESGCMXXF3HSM_createTempAssetID(handle);
    }

#if (ENABLE_KEY_STORAGE == 1)
    status = AESGCMXXF3HSM_getKeyMaterial(object);
#endif

    /* Clear the counter value */
    (void)memset(object->counter, 0U, sizeof(object->counter));

    if (status != AESGCM_STATUS_SUCCESS)
    {
        /* In the case of failure to initialize the operation, we need to free all assets allocated.
         * Capturing the return status of this operation is pointless since we are returning an
         * error code anyways.
         */
        (void)AESGCMXXF3HSM_freeTempAssetID(handle);

        HSMXXF3_releaseLock();

        return status;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When either AAD or data/output buffers are in PSRAM and exceed their respective bounce
     * slots, convert to a multi-token segmented sequence: chunk AAD (if any) as AAD_ENCRYPT/DECRYPT
     * tokens, chunk all-but-last data as DATA_ENCRYPT/DECRYPT, and the final data chunk as
     * FINALIZE_ENCRYPT/DECRYPT. The lock is released and re-acquired between tokens; the
     * tempAssetID preserves GHASH/CTR state across them.
     */
    {
        size_t dataMaxChunk = AESGCMXXF3HSM_dataMaxChunkSize(operation->input, operation->output);
        size_t aadMaxChunk  = AESGCMXXF3HSM_aadMaxChunkSize();

        bool aadNeedsChunk = (operation->aad != NULL) && XMEMWFF3_isAddrExternal((uintptr_t)operation->aad) &&
                             (operation->aadLength > aadMaxChunk);
        bool dataNeedsChunk = (operation->inputLength > dataMaxChunk) &&
                              (XMEMWFF3_isAddrExternal((uintptr_t)operation->input) ||
                               XMEMWFF3_isAddrExternal((uintptr_t)operation->output));

        if (aadNeedsChunk || dataNeedsChunk)
        {
            /* Multi-token chunking requires polling between tokens to re-acquire the lock;
             * callback mode cannot block between tokens so it is not supported.
             */
            if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
            {
                (void)AESGCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();

                return AESGCM_STATUS_FEATURE_NOT_SUPPORTED;
            }

            /* A zero chunk size means the bounce buffer is misconfigured or too small to hold
             * even one block, making chunking impossible.
             */
            if ((dataMaxChunk == 0U) || (aadMaxChunk == 0U))
            {
                (void)AESGCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();

                return AESGCM_STATUS_ERROR;
            }

            /* A tempAssetID is required to carry GHASH/CTR state across tokens; create one now
             * if not already present (the earlier single-step path only creates one for non-block-
             * aligned input lengths).
             */
            if (object->tempAssetID == 0U)
            {
                status = AESGCMXXF3HSM_createTempAssetID(handle);

                if (status != AESGCM_STATUS_SUCCESS)
                {
                    HSMXXF3_releaseLock();

                    return status;
                }
            }

            AESGCM_OperationType aadOpType   = (operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT)
                                                   ? AESGCM_OP_TYPE_AAD_ENCRYPT
                                                   : AESGCM_OP_TYPE_AAD_DECRYPT;
            AESGCM_OperationType dataOpType  = (operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT)
                                                   ? AESGCM_OP_TYPE_DATA_ENCRYPT
                                                   : AESGCM_OP_TYPE_DATA_DECRYPT;
            AESGCM_OperationType finalOpType = (operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT)
                                                   ? AESGCM_OP_TYPE_FINALIZE_ENCRYPT
                                                   : AESGCM_OP_TYPE_FINALIZE_DECRYPT;

            /* --- AAD phase --- */
            if (operation->aadLength > 0U)
            {
                AESGCM_SegmentedAADOperation aadOp;
                uint8_t *chunkAAD = (uint8_t *)operation->aad;
                size_t remaining  = operation->aadLength;

                object->operationType = aadOpType;

                while (remaining > 0U)
                {
                    size_t chunkSize  = (remaining > aadMaxChunk) ? aadMaxChunk : remaining;
                    aadOp.aad         = chunkAAD;
                    aadOp.aadLength   = chunkSize;
                    object->operation = (AESGCM_OperationUnion *)&aadOp;

                    status = AESGCMXXF3HSM_performHSMOperation(handle);

                    if (status != AESGCM_STATUS_SUCCESS)
                    {
                        object->operation = (AESGCM_OperationUnion *)operation;

                        return status;
                    }

                    chunkAAD += chunkSize;
                    remaining -= chunkSize;

                    /* performHSMOperation releases the lock on completion, so re-acquire it
                     * before the next chunk. Skip this on the last chunk since the loop exits.
                     */
                    if (remaining > 0U)
                    {
                        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
                        {
                            object->operation = (AESGCM_OperationUnion *)operation;

                            return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
                        }
                    }
                }
            }

            /* --- Data phase --- */
            {
                AESGCM_SegmentedDataOperation dataOp;
                AESGCM_SegmentedFinalizeOperation finalOp;
                uint8_t *chunkIn  = (uint8_t *)operation->input;
                uint8_t *chunkOut = operation->output;
                size_t remaining  = operation->inputLength;

                while (remaining > dataMaxChunk)
                {
                    dataOp.input          = chunkIn;
                    dataOp.output         = chunkOut;
                    dataOp.inputLength    = dataMaxChunk;
                    object->operationType = dataOpType;
                    object->operation     = (AESGCM_OperationUnion *)&dataOp;

                    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
                    {
                        object->operation = (AESGCM_OperationUnion *)operation;

                        return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
                    }

                    status = AESGCMXXF3HSM_performHSMOperation(handle);

                    if (status != AESGCM_STATUS_SUCCESS)
                    {
                        object->operation = (AESGCM_OperationUnion *)operation;

                        return status;
                    }

                    chunkIn += dataMaxChunk;
                    chunkOut += dataMaxChunk;
                    remaining -= dataMaxChunk;
                }

                /* Final chunk — finalize op type triggers MAC computation. */
                finalOp.input         = chunkIn;
                finalOp.output        = chunkOut;
                finalOp.inputLength   = remaining;
                finalOp.mac           = operation->mac;
                finalOp.macLength     = operation->macLength;
                object->operationType = finalOpType;
                object->operation     = (AESGCM_OperationUnion *)&finalOp;

                if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
                {
                    object->operation = (AESGCM_OperationUnion *)operation;

                    return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
                }

                status = AESGCMXXF3HSM_performHSMOperation(handle);
            }

            object->operation = (AESGCM_OperationUnion *)operation;

            return status;
        }
    }
#endif

    status = AESGCMXXF3HSM_performHSMOperation(handle);

    return status;
}

/*
 *  ======== AESGCMXXF3HSM_postProcessingCommon ========
 */
static void AESGCMXXF3HSM_postProcessingCommon(AESGCM_Handle handle, int_fast16_t status, int8_t tokenResult)
{
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);

    if (status == AESGCM_STATUS_SUCCESS)
    {
        if (object->operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT)
        {
            AESGCM_OneStepOperation *operation = (AESGCM_OneStepOperation *)object->operation;

            HSMXXF3_getAESEncryptTag(&operation->mac[0], operation->macLength);
        }
        else if ((object->operationType == AESGCM_OP_TYPE_FINALIZE_ENCRYPT) &&
                 ((object->inputLength != 0U) || (object->aadLength != 0U)))
        {
            AESGCM_SegmentedFinalizeOperation *operation = (AESGCM_SegmentedFinalizeOperation *)object->operation;

            HSMXXF3_getAESEncryptTag(&operation->mac[0], operation->macLength);
        }
        else if (object->operationType == AESGCM_OP_TYPE_DATA_ENCRYPT)
        {
            HSMXXF3_getAESEncryptTag((void *)&object->intermediateTag[0], object->macLength);
        }
        else if ((tokenResult == EIP130TOKEN_RESULT_VERIFY_ERROR) &&
                 ((object->operationType == AESGCM_OP_TYPE_FINALIZE_DECRYPT) ||
                  (object->operationType == AESGCM_OP_TYPE_ONESTEP_DECRYPT) ||
                  (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT)))
        {
            status = AESGCM_STATUS_MAC_INVALID;
        }
    }

    if ((object->operationType == AESGCM_OP_TYPE_FINALIZE_ENCRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        object->segmentedOperationInProgress = false;
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    /* Free all assets. This includes key-related asset and state-related asset (temporary asset). */
    if (AESGCMXXF3HSM_freeAllAssets(handle) != AESGCM_STATUS_SUCCESS)
    {
        status = AESGCM_STATUS_ERROR;
    }

    object->common.returnStatus = status;

    HSMXXF3_releaseLock();

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
    }
}

/*
 *  ======== AESGCMXXF3HSM_processFinalBlockPostProcessing ========
 */
inline static void AESGCMXXF3HSM_processFinalBlockPostProcessing(uintptr_t arg0)
{
    AESGCM_Handle handle         = (AESGCM_Handle)arg0;
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_ERROR;
    int32_t physicalResult       = HSMXXF3_getResultCode();
    int8_t tokenResult           = physicalResult & HSMXXF3_RETVAL_MASK;

    /* The HSM IP will throw an error when operation->macLength is zero despite it producing a correct
     * ciphertext/plaintext for both encrypt/decrypt operations and will compute a mac anyways.
     */
    if ((tokenResult == EIP130TOKEN_RESULT_SUCCESS) || ((tokenResult == EIP130TOKEN_RESULT_VERIFY_ERROR) &&
                                                        ((object->operationType == AESGCM_OP_TYPE_ONESTEP_DECRYPT) ||
                                                         (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT) ||
                                                         (object->operationType == AESGCM_OP_TYPE_FINALIZE_DECRYPT))))
    {
        object->totalDataLengthRemaining -= object->inputLength;

        status = AESGCM_STATUS_SUCCESS;
    }

    if (status == AESGCM_STATUS_SUCCESS)
    {
        uint8_t *output = NULL;

        if ((object->operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT) ||
            (object->operationType == AESGCM_OP_TYPE_ONESTEP_DECRYPT))
        {
            AESGCM_OneStepOperation *operation = (AESGCM_OneStepOperation *)object->operation;
            output                             = operation->output + (object->totalDataLength - object->inputLength);
        }
        else if ((object->operationType == AESGCM_OP_TYPE_DATA_ENCRYPT) ||
                 (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT))
        {
            AESGCM_SegmentedDataOperation *operation = (AESGCM_SegmentedDataOperation *)object->operation;
            output = operation->output + (operation->inputLength - object->inputLength);
        }
        else
        {
            AESGCM_SegmentedFinalizeOperation *operation = (AESGCM_SegmentedFinalizeOperation *)object->operation;
            output = operation->output + (operation->inputLength - object->inputLength);
        }

        (void)memcpy(output, object->outputFinalBlock, object->inputLength);
    }

    AESGCMXXF3HSM_postProcessingCommon(handle, status, tokenResult);
}

/*
 *  ======== AESGCMXXF3HSM_processFinalBlock ========
 */
static int_fast16_t AESGCMXXF3HSM_processFinalBlock(AESGCM_Handle handle)
{
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_ERROR;
    int_fast16_t hsmRetval       = HSMXXF3_STATUS_ERROR;
    size_t remainderLength       = 0U;
    bool saveIV                  = false;
    bool loadIV                  = true;

    if ((object->operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_ONESTEP_DECRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_FINALIZE_ENCRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        remainderLength = object->totalDataLengthRemaining;
    }
    else
    {
        AESGCM_SegmentedDataOperation *operation = (AESGCM_SegmentedDataOperation *)object->operation;
        remainderLength                          = operation->inputLength - object->inputLength;
    }

    (void)memset(object->inputFinalBlock, 0, AES_BLOCK_SIZE);
    (void)memcpy(object->inputFinalBlock, object->input + object->inputLength, remainderLength);

    (void)memset(object->outputFinalBlock, 0, AES_BLOCK_SIZE);

    object->input       = object->inputFinalBlock;
    object->output      = object->outputFinalBlock;
    object->inputLength = remainderLength;
    object->aadLength   = 0U;

    HSMXXF3_constructGCMToken(object, saveIV, loadIV); /* only loadIV is true */

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->common.returnBehavior,
                                    AESGCMXXF3HSM_processFinalBlockPostProcessing,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->common.returnStatus;
        }
    }

    return status;
}

/*
 *  ======== AESGCMXXF3HSM_postProcessingFxn ========
 */
static inline void AESGCMXXF3HSM_postProcessingFxn(uintptr_t arg0)
{
    AESGCM_Handle handle         = (AESGCM_Handle)arg0;
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_ERROR;
    int8_t tokenResult           = HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK;
    bool finalizeOp              = true;

    /* The HSM IP will throw an error when operation->macLength is zero despite it producing a correct
     * ciphertext/plaintext for both encrypt/decrypt operations and will compute a mac anyways.
     */
    if ((tokenResult == EIP130TOKEN_RESULT_SUCCESS) || ((tokenResult == EIP130TOKEN_RESULT_VERIFY_ERROR) &&
                                                        ((object->operationType == AESGCM_OP_TYPE_ONESTEP_DECRYPT) ||
                                                         (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT) ||
                                                         (object->operationType == AESGCM_OP_TYPE_FINALIZE_DECRYPT))))
    {
        object->totalAADLengthRemaining -= object->aadLength;
        object->totalDataLengthRemaining -= object->inputLength;

        status = AESGCM_STATUS_SUCCESS;
    }

    if (status == AESGCM_STATUS_SUCCESS)
    {
        if ((object->operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT) ||
            (object->operationType == AESGCM_OP_TYPE_ONESTEP_DECRYPT))
        {
            AESGCM_OneStepOperation *operation = (AESGCM_OneStepOperation *)object->operation;

            if (object->totalDataLengthRemaining > 0U)
            {
                status = AESGCMXXF3HSM_processFinalBlock(handle);

                if (status == AESGCM_STATUS_SUCCESS)
                {
                    finalizeOp = false;
                }
            }
            else if (operation->inputLength < AES_BLOCK_SIZE)
            {
                (void)memcpy(operation->output, object->output, operation->inputLength);
            }
        }
        else if ((object->operationType == AESGCM_OP_TYPE_FINALIZE_ENCRYPT) ||
                 (object->operationType == AESGCM_OP_TYPE_FINALIZE_DECRYPT))
        {
            AESGCM_SegmentedFinalizeOperation *operation = (AESGCM_SegmentedFinalizeOperation *)object->operation;

            if (object->totalDataLengthRemaining > 0U)
            {
                status = AESGCMXXF3HSM_processFinalBlock(handle);

                if (status == AESGCM_STATUS_SUCCESS)
                {
                    finalizeOp = false;
                }
            }
            else if (operation->inputLength < AES_BLOCK_SIZE)
            {
                (void)memcpy(operation->output, object->output, operation->inputLength);
            }
        }
        else if ((object->operationType == AESGCM_OP_TYPE_DATA_ENCRYPT) ||
                 (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT))
        {
            AESGCM_SegmentedDataOperation *operation = (AESGCM_SegmentedDataOperation *)object->operation;

            if ((!HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE(operation->inputLength)) &&
                (operation->inputLength > AES_BLOCK_SIZE))
            {
                status = AESGCMXXF3HSM_processFinalBlock(handle);

                if (status == AESGCM_STATUS_SUCCESS)
                {
                    finalizeOp = false;
                }
            }
            else if (operation->inputLength < AES_BLOCK_SIZE)
            {
                (void)memcpy(operation->output, object->output, operation->inputLength);
            }
        }
    }

    if (finalizeOp)
    {
        AESGCMXXF3HSM_postProcessingCommon(handle, status, tokenResult);
    }
}

#if (ENABLE_KEY_STORAGE == 1)
/*
 *  ======== AESGCMXXF3HSM_getKeyMaterial ========
 */
static int_fast16_t AESGCMXXF3HSM_getKeyMaterial(AESGCMXXF3HSM_Object *object)
{
    int_fast16_t status = AESGCM_STATUS_SUCCESS;

    if (object->common.key.encoding == CryptoKey_KEYSTORE_HSM)
    {
        KeyStore_PSA_KeyFileId keyID;
        KeyStore_PSA_KeyAttributes attributes = KEYSTORE_PSA_KEY_ATTRIBUTES_INIT;
        KeyStore_PSA_KeyUsage usage           = KEYSTORE_PSA_KEY_USAGE_ENCRYPT;
        KeyStore_PSA_KeyLifetime lifetime;
        int_fast16_t keyStoreStatus;

        if ((object->operationType == AESGCM_OP_TYPE_ONESTEP_DECRYPT) ||
            (object->operationType == AESGCM_OP_TYPE_AAD_DECRYPT) ||
            (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT) ||
            (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT))
        {
            usage = KEYSTORE_PSA_KEY_USAGE_DECRYPT;
        }

        GET_KEY_ID(keyID, object->common.key.u.keyStore.keyID);

        keyStoreStatus = KeyStore_PSA_getKeyAttributes(keyID, &attributes);

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
        {
            keyStoreStatus = KeyStore_PSA_retrieveFromKeyStore(&object->common.key,
                                                               &object->KeyStore_keyingMaterial[0],
                                                               AESCommonXXF3_256_KEY_LENGTH_BYTES,
                                                               &object->keyAssetID,
                                                               KEYSTORE_PSA_ALG_CCM,
                                                               usage);

            if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
            {
                lifetime = KeyStore_PSA_getKeyLifetime(&attributes);

                object->keyLocation = KEYSTORE_PSA_KEY_LIFETIME_GET_LOCATION(lifetime);
            }
        }

        if (keyStoreStatus == KEYSTORE_PSA_STATUS_INVALID_KEY_ID)
        {
            status = AESGCM_STATUS_KEYSTORE_INVALID_ID;
        }
        else if (keyStoreStatus != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            status = AESGCM_STATUS_KEYSTORE_GENERIC_ERROR;
        }
    }

    return status;
}
#endif

/*
 *  ======== AESGCMXXF3HSM_setupObjectMetaData ========
 */
static void AESGCMXXF3HSM_setupObjectMetaData(AESGCMXXF3HSM_Object *object)
{
    bool saveIV = false;
    bool loadIV = false;

    if ((object->operationType == AESGCM_OP_TYPE_ONESTEP_ENCRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_ONESTEP_DECRYPT))
    {
        AESGCM_OneStepOperation *operation = (AESGCM_OneStepOperation *)object->operation;

        if (operation->inputLength < AES_BLOCK_SIZE)
        {
            (void)memset(object->inputFinalBlock, 0, AES_BLOCK_SIZE);
            (void)memcpy(object->inputFinalBlock, operation->input, operation->inputLength);

            (void)memset(object->outputFinalBlock, 0, AES_BLOCK_SIZE);

            object->input       = object->inputFinalBlock;
            object->output      = object->outputFinalBlock;
            object->inputLength = operation->inputLength;
        }
        else if (HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE(operation->inputLength))
        {
            /* Get block-size aligned input length */
            object->input       = operation->input;
            object->output      = operation->output;
            object->inputLength = operation->inputLength;
        }
        else
        {
            /* Get block-size aligned input length */
            object->input       = operation->input;
            object->output      = operation->output;
            object->inputLength = operation->inputLength & AES_BLOCK_SIZE_MULTIPLE_MASK;

            saveIV = true;
        }
    }
    else if ((object->operationType == AESGCM_OP_TYPE_AAD_ENCRYPT) ||
             (object->operationType == AESGCM_OP_TYPE_AAD_DECRYPT))
    {
        AESGCM_SegmentedAADOperation *operation = (AESGCM_SegmentedAADOperation *)object->operation;

        object->input       = NULL;
        object->output      = NULL;
        object->inputLength = 0U;

        if (HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE(operation->aadLength))
        {
            /* Get block-size aligned input length */
            object->aad       = operation->aad;
            object->aadLength = operation->aadLength;

            if (operation->aadLength == object->totalAADLengthRemaining)
            {
                object->aadLength -= AES_BLOCK_SIZE;
                object->bufferedAADLength = AES_BLOCK_SIZE;

                (void)memset(object->aadFinalBlock, 0, AES_BLOCK_SIZE);
                (void)memcpy(&object->aadFinalBlock[0], operation->aad + object->aadLength, object->bufferedAADLength);
            }
        }
        else
        {
            /* Get block-size aligned input length */
            object->aad               = operation->aad;
            object->aadLength         = (operation->aadLength & AES_BLOCK_SIZE_MULTIPLE_MASK);
            object->bufferedAADLength = (operation->aadLength & AES_NON_BLOCK_SIZE_MULTIPLE_MASK);

            (void)memset(object->aadFinalBlock, 0, AES_BLOCK_SIZE);
            (void)memcpy(&object->aadFinalBlock[0], operation->aad + object->aadLength, object->bufferedAADLength);
        }

        if (object->tempAssetID != 0U)
        {
            if (object->totalAADLengthRemaining != object->totalAADLength)
            {
                loadIV = true;
            }

            saveIV = true;
        }
    }
    else if ((object->operationType == AESGCM_OP_TYPE_DATA_ENCRYPT) ||
             (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT))
    {
        AESGCM_SegmentedDataOperation *operation = (AESGCM_SegmentedDataOperation *)object->operation;

        if (object->totalAADLengthRemaining > 0U)
        {
            object->aad       = &object->aadFinalBlock[0];
            object->aadLength = object->bufferedAADLength;
        }
        else
        {
            object->aad       = NULL;
            object->aadLength = 0;
        }

        if (operation->inputLength == 0U)
        {
            /* Get block-size aligned input length */
            object->input       = NULL;
            object->output      = NULL;
            object->inputLength = 0U;
        }
        else if (operation->inputLength < AES_BLOCK_SIZE)
        {
            (void)memset(object->inputFinalBlock, 0, AES_BLOCK_SIZE);
            (void)memcpy(object->inputFinalBlock, operation->input, operation->inputLength);

            (void)memset(object->outputFinalBlock, 0, AES_BLOCK_SIZE);

            object->input       = object->inputFinalBlock;
            object->output      = object->outputFinalBlock;
            object->inputLength = operation->inputLength;
        }
        else if (HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE(operation->inputLength))
        {
            /* Get block-size aligned input length */
            object->input       = operation->input;
            object->output      = operation->output;
            object->inputLength = operation->inputLength;
        }
        else
        {
            /* Get block-size aligned input length */
            object->input       = operation->input;
            object->output      = operation->output;
            object->inputLength = operation->inputLength & AES_BLOCK_SIZE_MULTIPLE_MASK;
        }

        if (object->tempAssetID != 0U)
        {
            if ((object->totalAADLength != object->totalAADLengthRemaining) ||
                (object->totalDataLength != object->totalDataLengthRemaining))
            {
                loadIV = true;
            }

            if (object->totalDataLengthRemaining != object->inputLength)
            {
                saveIV = true;
            }
        }
    }
    else
    {
        AESGCM_SegmentedFinalizeOperation *operation = (AESGCM_SegmentedFinalizeOperation *)object->operation;

        if (object->totalAADLengthRemaining > 0U)
        {
            object->aad       = &object->aadFinalBlock[0];
            object->aadLength = object->bufferedAADLength;
        }
        else
        {
            object->aad       = NULL;
            object->aadLength = 0;
        }

        if (operation->inputLength == 0U)
        {
            /* Get block-size aligned input length */
            object->input       = NULL;
            object->output      = NULL;
            object->inputLength = 0U;
        }
        else if (operation->inputLength < AES_BLOCK_SIZE)
        {
            (void)memset(object->inputFinalBlock, 0, AES_BLOCK_SIZE);
            (void)memcpy(object->inputFinalBlock, operation->input, operation->inputLength);

            (void)memset(object->outputFinalBlock, 0, AES_BLOCK_SIZE);

            object->input       = object->inputFinalBlock;
            object->output      = object->outputFinalBlock;
            object->inputLength = operation->inputLength;
        }
        else if (HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE(operation->inputLength))
        {
            /* Get block-size aligned input length */
            object->input       = operation->input;
            object->output      = operation->output;
            object->inputLength = operation->inputLength;
        }
        else
        {
            /* Get block-size aligned input length */
            object->input       = operation->input;
            object->output      = operation->output;
            object->inputLength = operation->inputLength & AES_BLOCK_SIZE_MULTIPLE_MASK;
        }

        if (object->tempAssetID != 0U)
        {
            if ((object->totalAADLength != object->totalAADLengthRemaining) ||
                (object->totalDataLength != object->totalDataLengthRemaining))
            {
                loadIV = true;
            }

            if (object->totalDataLengthRemaining != object->inputLength)
            {
                saveIV = true;
            }
        }
    }

    HSMXXF3_constructGCMToken(object, saveIV, loadIV);
}

/*
 *  ======== AESGCMXXF3HSM_performHSMOperation ========
 */
static int_fast16_t AESGCMXXF3HSM_performHSMOperation(AESGCM_Handle handle)
{
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_ERROR;
    int_fast16_t hsmRetval       = HSMXXF3_STATUS_ERROR;

    AESGCMXXF3HSM_setupObjectMetaData(object);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When the AAD length is not a multiple of 16 bytes and the entire AAD fits in
     * one bounce-buffer chunk, setupObjectMetaData has no complete 16-byte blocks to
     * submit - it buffers all bytes in aadFinalBlock for the DATA token and sets
     * object->aadLength = 0. Submitting this zero-content token writes an initial
     * GCM state to tempAssetID; the DATA token that follows uses loadIV=false on the
     * already-written asset, which the EIP-130 rejects. Skip the token: aadFinalBlock
     * is already populated and the DATA token will include those bytes with a fresh IV
     * initialization.
     */
    if (((object->operationType == AESGCM_OP_TYPE_AAD_ENCRYPT) ||
         (object->operationType == AESGCM_OP_TYPE_AAD_DECRYPT)) &&
        (object->aadLength == 0U))
    {
        HSMXXF3_releaseLock();
        return AESGCM_STATUS_SUCCESS;
    }
#endif

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
    if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
    {
        HSMXXF3_releaseLock();

        return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->common.returnBehavior,
                                    AESGCMXXF3HSM_postProcessingFxn,
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

        /* In the case of failure to initialize the operation, we need to free all assets allocated.
         * Capturing the return status of this operation is pointless since we are returning an
         * error code anyways.
         */
        (void)AESGCMXXF3HSM_freeTempAssetID(handle);

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== AESGCM_cancelOperation ========
 */
int_fast16_t AESGCM_cancelOperation(AESGCM_Handle handle)
{
    DebugP_assert(handle);

    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_ERROR;

    /* Cancellation is only supported in callback mode */
    if (object->common.returnBehavior != AES_RETURN_BEHAVIOR_CALLBACK)
    {
        return status;
    }

    uintptr_t interruptKey = HwiP_disable();

    /* Return success if there is no active operation to cancel.
     * Do not execute the callback as it would have been executed already
     * when the operation completed.
     */
    if (((object->common.key.encoding & CRYPTOKEY_HSM) == 0) && (!object->common.operationInProgress))
    {
        HwiP_restore(interruptKey);
    }
    else
    {
        HwiP_restore(interruptKey);

        /* Since the HSM cannot cancel an in-progress token, we must wait for the result to allow for
         * subsequent token submissions to succeed.
         */
        (void)HSMXXF3_cancelOperation();

        object->segmentedOperationInProgress = false;

        /* Free all assets. This includes key-related asset and state-related asset (temporary asset). */
        status = AESGCMXXF3HSM_freeAllAssets(handle);

        object->aad       = NULL;
        object->input     = NULL;
        object->output    = NULL;
        object->iv        = NULL;
        object->mac       = NULL;
        object->operation = NULL;

        object->inputLength              = 0U;
        object->totalDataLengthRemaining = 0U;
        object->totalAADLength           = 0U;
        object->totalDataLength          = 0U;

        object->macLength = 0U;
        object->ivLength  = 0U;

        /* Operation pointer could be NULL if a segmented operation was setup
         * but neither AESGCM_addData or AESGCM_finalize was called.
         */
        if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
        {
            /* Call the callback function provided by the application */
            object->callbackFxn(handle, AESGCM_STATUS_CANCELED, object->operation, object->operationType);
        }
    }

    return status;
}

/*
 *  ======== AESGCMXXF3HSM_setupSegmentedOperation ========
 */
static int_fast16_t AESGCMXXF3HSM_setupSegmentedOperation(AESGCM_Handle handle,
                                                          AESGCM_OperationType operationType,
                                                          const CryptoKey *key,
                                                          size_t totalAADLength,
                                                          size_t totalDataLength)
{
    DebugP_assert(key);

    int_fast16_t status          = AESGCM_STATUS_SUCCESS;
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);

    /* If the HSM IP or HSMSAL failed to boot, then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESGCM_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESGCM_STATUS_ERROR;
    }

    /* Make internal copy of crypto key */
    object->common.key = *key;

    /* returnStatus is only changed in the case of an error or cancellation */
    object->common.returnStatus = AES_STATUS_SUCCESS;

    /* If the user doesn't provide the total lengths in the setupXXXX()
     * calls, they must provide the lengths in setLengths().
     */
    object->totalAADLength  = totalAADLength;
    object->totalDataLength = totalDataLength;

    object->totalDataLengthRemaining = totalDataLength;
    object->totalAADLengthRemaining  = totalAADLength;
    object->inputLength              = 0U;
    object->aadLength                = 0U;

    object->operationType = operationType;

    /* We are not supplied the macLength at this point of the segmented operation.
     * Therefore, the driver gives it a dummy length which is the max length until
     * the user supplies the desired macLength in _setLengths() API.
     */
    object->macLength = HSM_MAC_MAX_LENGTH;

    (void)memset(object->KeyStore_keyingMaterial, 0, AESCommonXXF3_256_KEY_LENGTH_BYTES);
    (void)memset(object->inputFinalBlock, 0, AES_BLOCK_SIZE);
    (void)memset(object->outputFinalBlock, 0, AES_BLOCK_SIZE);
    (void)memset(object->aadFinalBlock, 0, AES_BLOCK_SIZE);

    /* Initialize MAC pointer to NULL to avoid premature processing of the
     * MAC in the ISR.
     */
    object->mac = NULL;

    /* Initialize operation pointer to NULL in case AESGCM_cancelOperation
     * is called after AESGCM_setupXXXX and callback should be skipped.
     */
    object->operation = NULL;

    object->segmentedOperationInProgress = true;

#if (ENABLE_KEY_STORAGE == 1)
    status = AESGCMXXF3HSM_getKeyMaterial(object);
#endif

    if (((totalAADLength > AES_BLOCK_SIZE) || (totalDataLength > AES_BLOCK_SIZE)) && (object->tempAssetID == 0U))
    {
        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
        {
            return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
        }

        status = AESGCMXXF3HSM_createTempAssetID(handle);

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== AESGCM_setupEncrypt ========
 */
int_fast16_t AESGCM_setupEncrypt(AESGCM_Handle handle,
                                 const CryptoKey *key,
                                 size_t totalAADLength,
                                 size_t totalPlaintextLength)
{
    return AESGCMXXF3HSM_setupSegmentedOperation(handle,
                                                 AESGCM_OPERATION_TYPE_ENCRYPT,
                                                 key,
                                                 totalAADLength,
                                                 totalPlaintextLength);
}

/*
 *  ======== AESGCM_setupDecrypt ========
 */
int_fast16_t AESGCM_setupDecrypt(AESGCM_Handle handle,
                                 const CryptoKey *key,
                                 size_t totalAADLength,
                                 size_t totalPlaintextLength)
{
    return AESGCMXXF3HSM_setupSegmentedOperation(handle,
                                                 AESGCM_OPERATION_TYPE_DECRYPT,
                                                 key,
                                                 totalAADLength,
                                                 totalPlaintextLength);
}

/*
 *  ======== AESGCM_setLengths ========
 */
int_fast16_t AESGCM_setLengths(AESGCM_Handle handle, size_t aadLength, size_t plaintextLength)
{
    DebugP_assert(handle);

    int_fast16_t status          = AESGCM_STATUS_SUCCESS;
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);

    /* This shouldn't be called after addXXX() or finalizeXXX() */
    DebugP_assert(object->operationType == AESGCM_OPERATION_TYPE_DECRYPT ||
                  object->operationType == AESGCM_OPERATION_TYPE_ENCRYPT);

    /* Don't continue the segmented operation if there
     * was an error or a cancellation
     */
    if (object->common.returnStatus != AESGCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    /* The combined length of AAD and payload data must be non-zero. */
    if ((aadLength == 0U) && (plaintextLength == 0U))
    {
        return AESGCM_STATUS_ERROR;
    }

    object->totalAADLength           = aadLength;
    object->totalDataLength          = plaintextLength;
    object->totalAADLengthRemaining  = aadLength;
    object->totalDataLengthRemaining = plaintextLength;

    if (((aadLength > AES_BLOCK_SIZE) || (plaintextLength > AES_BLOCK_SIZE)) && (object->tempAssetID == 0U))
    {
        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
        {
            return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
        }

        status = AESGCMXXF3HSM_createTempAssetID(handle);

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== AESGCMXXF3HSM_setMac ========
 */
int_fast16_t AESGCMXXF3HSM_setMac(AESGCM_Handle handle, const uint8_t *mac, size_t macLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);

    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);

    /* This function cannot be called after addXXX() or finalizeXXX() */
    DebugP_assert((object->operationType == AESGCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESGCM_OPERATION_TYPE_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error during setup.
     */
    if (object->common.returnStatus != AESGCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    object->mac       = (uint8_t *)mac;
    object->macLength = (uint8_t)macLength;

    if ((object->operationType == AESGCM_OPERATION_TYPE_ENCRYPT) && (macLength == 0U))
    {
        /* We are not supplied the macLength at this point of the segmented operation.
         * Therefore, the driver gives it a dummy length which is the max length until
         * the user supplies the desired macLength in _setLengths() API.
         */
        object->macLength = HSM_MAC_MAX_LENGTH;
    }

    return AESGCM_STATUS_SUCCESS;
}

/*
 *  ======== AESGCM_setIV ========
 */
int_fast16_t AESGCM_setIV(AESGCM_Handle handle, const uint8_t *iv, size_t ivLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);

    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);

    /* This function cannot be called after addXXX() or finalizeXXX() */
    DebugP_assert((object->operationType == AESGCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESGCM_OPERATION_TYPE_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error during setup.
     */
    if (object->common.returnStatus != AESGCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    object->iv       = iv;
    object->ivLength = (uint8_t)ivLength;

    return AESGCM_STATUS_SUCCESS;
}

/*
 *  ======== AESGCM_generateIV ========
 */
int_fast16_t AESGCM_generateIV(AESGCM_Handle handle, uint8_t *iv, size_t ivSize, size_t *ivLength)
{
    /* Segmented operations are not currently supported by this implementation */
    return AESGCM_STATUS_FEATURE_NOT_SUPPORTED;
}

/*
 *  ======== AESGCM_addAAD ========
 */
int_fast16_t AESGCM_addAAD(AESGCM_Handle handle, AESGCM_SegmentedAADOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESGCMXXF3HSM_Object *object       = AESGCMXXF3HSM_getObject(handle);
    object->operation                  = (AESGCM_OperationUnion *)operation;
    AESGCM_OperationType operationType = AESGCM_OP_TYPE_AAD_ENCRYPT;

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if ((object->totalAADLength == 0U) || (object->hsmStatus != HSMXXF3_STATUS_SUCCESS))
    {
        return AESGCM_STATUS_ERROR;
    }
    else if (object->common.returnStatus != AESGCM_STATUS_SUCCESS)
    {
        /* Don't continue the segmented operation if there
         * was an error or a cancellation.
         */
        return object->common.returnStatus;
    }

    /* This operation can be called after setup or after addAAD again. */
    DebugP_assert((object->operationType == AESGCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESGCM_OPERATION_TYPE_ENCRYPT) ||
                  (object->operationType == AESGCM_OP_TYPE_AAD_DECRYPT) ||
                  (object->operationType == AESGCM_OP_TYPE_AAD_ENCRYPT));

    if ((object->operationType == AESGCM_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_AAD_DECRYPT))
    {
        operationType = AESGCM_OP_TYPE_AAD_DECRYPT;
    }

    object->operationType = operationType;
    object->operation     = (AESGCM_OperationUnion *)operation;

    if ((operation->aadLength <= AES_BLOCK_SIZE) && (operation->aadLength == object->totalAADLengthRemaining))
    {
        (void)memcpy(&object->aadFinalBlock[0], operation->aad, operation->aadLength);
        object->bufferedAADLength = operation->aadLength;

        object->common.returnStatus = AESGCM_STATUS_SUCCESS;

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
        }

        return AESGCM_STATUS_SUCCESS;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When AAD is in PSRAM and exceeds the aux bounce slot, chunk through multiple tokens. The
     * tempAssetID preserves GHASH state between them. freeAllAssets is a no-op for AAD op types,
     * so the asset survives across all but the final finalize token.
     */
    if (XMEMWFF3_isAddrExternal((uintptr_t)operation->aad))
    {
        size_t aadMaxChunk = AESGCMXXF3HSM_aadMaxChunkSize();

        if (aadMaxChunk == 0U)
        {
            return AESGCM_STATUS_ERROR;
        }

        if (operation->aadLength > aadMaxChunk)
        {
            if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
            {
                return AESGCM_STATUS_FEATURE_NOT_SUPPORTED;
            }

            AESGCM_SegmentedAADOperation tempOp;
            uint8_t *chunkAAD = (uint8_t *)operation->aad;
            size_t remaining  = operation->aadLength;
            int_fast16_t status;

            while (remaining > 0U)
            {
                size_t chunkSize  = (remaining > aadMaxChunk) ? aadMaxChunk : remaining;
                tempOp.aad        = chunkAAD;
                tempOp.aadLength  = chunkSize;
                object->operation = (AESGCM_OperationUnion *)&tempOp;

                if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
                {
                    object->operation = (AESGCM_OperationUnion *)operation;

                    return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
                }

                status = AESGCMXXF3HSM_performHSMOperation(handle);

                if (status != AESGCM_STATUS_SUCCESS)
                {
                    object->operation = (AESGCM_OperationUnion *)operation;

                    return status;
                }

                chunkAAD += chunkSize;
                remaining -= chunkSize;
            }

            object->operation = (AESGCM_OperationUnion *)operation;

            return AESGCM_STATUS_SUCCESS;
        }
    }
#endif

    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    return AESGCMXXF3HSM_performHSMOperation(handle);
}

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESGCMXXF3HSM_processExternalDataChunks ========
 *  Submits DATA tokens for PSRAM-backed input/output in maxChunkSize increments
 *  while remaining > stopAt, advancing *pChunkIn, *pChunkOut, and *pRemaining.
 *  stopAt = 0 consumes all data; stopAt = maxChunkSize leaves the last chunk
 *  for the caller to submit as a FINALIZE token.
 */
static int_fast16_t AESGCMXXF3HSM_processExternalDataChunks(AESGCM_Handle handle,
                                                            AESGCM_OperationType dataOpType,
                                                            uint8_t **pChunkIn,
                                                            uint8_t **pChunkOut,
                                                            size_t *pRemaining,
                                                            size_t maxChunkSize,
                                                            size_t stopAt)
{
    AESGCM_SegmentedDataOperation tempOp;
    int_fast16_t status = AESGCM_STATUS_SUCCESS;

    while (*pRemaining > stopAt)
    {
        size_t chunkSize   = (*pRemaining > maxChunkSize) ? maxChunkSize : *pRemaining;
        tempOp.input       = *pChunkIn;
        tempOp.output      = *pChunkOut;
        tempOp.inputLength = chunkSize;

        status = AESGCMXXF3HSM_addData(handle, dataOpType, (AESGCM_OperationUnion *)&tempOp);

        if (status != AESGCM_STATUS_SUCCESS)
        {
            return status;
        }

        *pChunkIn += chunkSize;
        *pChunkOut += chunkSize;
        *pRemaining -= chunkSize;
    }

    return status;
}
#endif

/*
 *  ======== AESGCM_addData ========
 */
int_fast16_t AESGCM_addData(AESGCM_Handle handle, AESGCM_SegmentedDataOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);

    /* This operation can be called after setupXXXX, addAAD, or addData */
    DebugP_assert((object->operationType == AESGCM_OP_TYPE_AAD_ENCRYPT) ||
                  (object->operationType == AESGCM_OP_TYPE_DATA_ENCRYPT));

    if (object->common.returnStatus != AESGCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->output))
    {
        return AESGCM_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }

    /* The input length must be a non-zero multiple of an AES block size
     * unless you are dealing with the last chunk of payload data
     */
    if ((operation->inputLength == 0U) || ((!HSM_IS_SIZE_MULTIPLE_OF_WORD(operation->inputLength)) &&
                                           (operation->inputLength != object->totalDataLengthRemaining)))
    {
        return AESGCM_STATUS_ERROR;
    }

    /* The total input length must not exceed the lengths specified in
     * AESGCM_setLengths() or setupXXXX().
     */
    if (operation->inputLength > object->totalDataLengthRemaining)
    {
        return AESGCM_STATUS_ERROR;
    }

    AESGCM_OperationType operationType = AESGCM_OP_TYPE_DATA_ENCRYPT;

    if ((object->operationType == AESGCM_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_AAD_DECRYPT) || (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT))
    {
        operationType = AESGCM_OP_TYPE_DATA_DECRYPT;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When input or output is in PSRAM and exceeds the bounce slot, split into block-aligned chunks.
     * freeAllAssets is a no-op for DATA op types, so the tempAssetID (GHASH/CTR state) survives
     * across all chunk tokens.
     */
    if (XMEMWFF3_isAddrExternal((uintptr_t)operation->input) || XMEMWFF3_isAddrExternal((uintptr_t)operation->output))
    {
        size_t maxChunkSize = AESGCMXXF3HSM_dataMaxChunkSize(operation->input, operation->output);

        if (maxChunkSize == 0U)
        {
            return AESGCM_STATUS_ERROR;
        }

        if (operation->inputLength > maxChunkSize)
        {
            if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
            {
                return AESGCM_STATUS_FEATURE_NOT_SUPPORTED;
            }

            uint8_t *chunkIn  = (uint8_t *)operation->input;
            uint8_t *chunkOut = operation->output;
            size_t remaining  = operation->inputLength;

            return AESGCMXXF3HSM_processExternalDataChunks(handle,
                                                           operationType,
                                                           &chunkIn,
                                                           &chunkOut,
                                                           &remaining,
                                                           maxChunkSize,
                                                           0U);
        }
    }
#endif

    return AESGCMXXF3HSM_addData(handle, operationType, (AESGCM_OperationUnion *)operation);
}

/*
 *  ======== AESGCMXXF3HSM_addData ========
 */
static int_fast16_t AESGCMXXF3HSM_addData(AESGCM_Handle handle,
                                          AESGCM_OperationType operationType,
                                          AESGCM_OperationUnion *operation)
{
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESGCM_STATUS_ERROR;
    }

    object->operationType = operationType;
    object->operation     = operation;

    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    return AESGCMXXF3HSM_performHSMOperation(handle);
}

/*
 *  ======== AESGCMXXF3HSM_performFinalizeChecks ========
 */
static int_fast16_t AESGCMXXF3HSM_performFinalizeChecks(const AESGCMXXF3HSM_Object *object,
                                                        const AESGCM_SegmentedFinalizeOperation *operation)
{
    /* This operation can be called after setupXXXX, addAAD, or addData */
    DebugP_assert((object->operationType == AESGCM_OP_TYPE_AAD_ENCRYPT) ||
                  (object->operationType == AESGCM_OP_TYPE_DATA_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error or a cancellation.
     */
    if (object->common.returnStatus != AESGCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESGCM_STATUS_ERROR;
    }

    /* Additional payload data can be passed in finalize */
    if (operation->inputLength != object->totalDataLengthRemaining)
    {
        return AESGCM_STATUS_ERROR;
    }

    return AESGCM_STATUS_SUCCESS;
}

/*
 *  ======== AESGCMXXF3HSM_finalizeCommon ========
 */
static int_fast16_t AESGCMXXF3HSM_finalizeCommon(AESGCM_Handle handle,
                                                 AESGCM_OperationType operationType,
                                                 AESGCM_SegmentedFinalizeOperation *operation)
{
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_ERROR;

    status = AESGCMXXF3HSM_performFinalizeChecks(object, operation);

    if (status != AESGCM_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->totalDataLengthRemaining == object->totalDataLength)
    {
        object->input  = operation->input;
        object->output = operation->output;
    }

    object->mac       = operation->mac;
    object->macLength = operation->macLength;

    if ((operation->inputLength > 0U) || (object->totalAADLengthRemaining > 0U))
    {
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        /* When input or output is in PSRAM and exceeds the bounce slot, process all but the last
         * chunk as DATA tokens, then submit the last chunk as the FINALIZE token. The DATA op type
         * keeps freeAllAssets as a no-op so the tempAssetID survives between tokens.
         */
        if ((operation->inputLength > 0U) && (XMEMWFF3_isAddrExternal((uintptr_t)operation->input) ||
                                              XMEMWFF3_isAddrExternal((uintptr_t)operation->output)))
        {
            size_t maxChunkSize = AESGCMXXF3HSM_dataMaxChunkSize(operation->input, operation->output);

            if (maxChunkSize == 0U)
            {
                return AESGCM_STATUS_ERROR;
            }

            if (operation->inputLength > maxChunkSize)
            {
                if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
                {
                    return AESGCM_STATUS_FEATURE_NOT_SUPPORTED;
                }

                AESGCM_OperationType dataOpType = (operationType == AESGCM_OP_TYPE_FINALIZE_ENCRYPT)
                                                      ? AESGCM_OP_TYPE_DATA_ENCRYPT
                                                      : AESGCM_OP_TYPE_DATA_DECRYPT;

                AESGCM_SegmentedFinalizeOperation finalOp;
                uint8_t *chunkIn  = (uint8_t *)operation->input;
                uint8_t *chunkOut = operation->output;
                size_t remaining  = operation->inputLength;

                status = AESGCMXXF3HSM_processExternalDataChunks(handle,
                                                                 dataOpType,
                                                                 &chunkIn,
                                                                 &chunkOut,
                                                                 &remaining,
                                                                 maxChunkSize,
                                                                 maxChunkSize);

                if (status != AESGCM_STATUS_SUCCESS)
                {
                    return status;
                }

                finalOp.input       = chunkIn;
                finalOp.output      = chunkOut;
                finalOp.inputLength = remaining;
                finalOp.mac         = operation->mac;
                finalOp.macLength   = operation->macLength;

                return AESGCMXXF3HSM_addData(handle, operationType, (AESGCM_OperationUnion *)&finalOp);
            }
        }
#endif
        status = AESGCMXXF3HSM_addData(handle, operationType, (AESGCM_OperationUnion *)operation);
    }
    else
    {
        object->operationType = operationType;

        if (operationType == AESGCM_OP_TYPE_FINALIZE_ENCRYPT)
        {
            (void)memcpy(operation->mac, (void *)&object->intermediateTag[0], operation->macLength);
        }

        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
        {
            return AESGCM_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->aadLength   = 0U;
        object->inputLength = 0U;

        AESGCMXXF3HSM_postProcessingCommon(handle, status, (int8_t)AESGCM_STATUS_SUCCESS);
    }

    return status;
}

/*
 *  ======== AESGCM_finalizeEncrypt ========
 */
int_fast16_t AESGCM_finalizeEncrypt(AESGCM_Handle handle, AESGCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    return AESGCMXXF3HSM_finalizeCommon(handle, AESGCM_OP_TYPE_FINALIZE_ENCRYPT, operation);
}

/*
 *  ======== AESGCM_finalizeDecrypt ========
 */
int_fast16_t AESGCM_finalizeDecrypt(AESGCM_Handle handle, AESGCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    return AESGCMXXF3HSM_finalizeCommon(handle, AESGCM_OP_TYPE_FINALIZE_DECRYPT, operation);
}

/*
 *  ======== AESGCMXXF3HSM_CreateAssetPostProcessing ========
 */
static inline void AESGCMXXF3HSM_CreateAssetPostProcessing(uintptr_t arg0)
{
    AESGCM_Handle handle         = (AESGCM_Handle)arg0;
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_ERROR;
    int32_t tokenResult          = HSMXXF3_getResultCode();

    if ((tokenResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->tempAssetID = HSMXXF3_getResultAssetID();
        status              = AESGCM_STATUS_SUCCESS;
    }

    object->common.returnStatus = status;
}

/*
 *  ======== AESGCMXXF3HSM_createTempAssetID ========
 */
static int_fast16_t AESGCMXXF3HSM_createTempAssetID(AESGCM_Handle handle)
{
    int_fast16_t status          = AESGCM_STATUS_ERROR;
    int_fast16_t hsmRetval       = HSMXXF3_STATUS_ERROR;
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    uint64_t assetPolicy = HSM_ASSET_POLICY_SYM_AES_AUTH | HSM_ASSET_POLICY_TEMPORARY | HSM_ASSET_POLICY_SYM_MODE_GCM;

    if (object->operationType == AESGCM_OPERATION_TYPE_ENCRYPT)
    {
        assetPolicy |= HSM_ASSET_POLICY_DIR_ENC_GEN;
    }
    else
    {
        assetPolicy |= HSM_ASSET_POLICY_DIR_DEC_VRFY;
    }

    HSMXXF3_constructCreateAssetToken(assetPolicy, HSM_AEAD_TEMP_ASSET_SIZE);

    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    AESGCMXXF3HSM_CreateAssetPostProcessing,
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
        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== AESGCMXXF3HSM_freeAllAssets ========
 */
static int_fast16_t AESGCMXXF3HSM_freeAllAssets(AESGCM_Handle handle)
{
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_SUCCESS;
#if (ENABLE_KEY_STORAGE == 1)
    KeyStore_PSA_KeyFileId keyID;
#endif

    if ((object->operationType == AESGCM_OP_TYPE_AAD_ENCRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_AAD_DECRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_DATA_ENCRYPT) ||
        (object->operationType == AESGCM_OP_TYPE_DATA_DECRYPT))
    {
        /* Operation is not done yet and therefore, do not free any asset. */
        return AESGCM_STATUS_SUCCESS;
    }

#if (ENABLE_KEY_STORAGE == 1)
    if ((object->common.key.encoding == CryptoKey_KEYSTORE_HSM) &&
        (object->keyLocation == KEYSTORE_PSA_KEY_LOCATION_HSM_ASSET_STORE))
    {
        GET_KEY_ID(keyID, object->common.key.u.keyStore.keyID);

        /* For keys with a persistence that does not designate them to remain in asset store,
         * the following function will remove them. Otherwise, the key will remain in asset store
         * for future usage.
         */
        if (status == AESGCM_STATUS_SUCCESS)
        {
            status = KeyStore_PSA_assetPostProcessing(keyID);

            if (status != KEYSTORE_PSA_STATUS_SUCCESS)
            {
                status = AESGCM_STATUS_ERROR;
            }
            else
            {
                status = AESGCM_STATUS_SUCCESS;
            }
        }
        else
        {
            (void)KeyStore_PSA_assetPostProcessing(keyID);
        }
    }
#endif

    if (status != AESGCM_STATUS_SUCCESS)
    {
        (void)AESGCMXXF3HSM_freeTempAssetID(handle);
    }
    else
    {
        status = AESGCMXXF3HSM_freeTempAssetID(handle);
    }

    return status;
}

/*
 *  ======== AESGCMXXF3HSM_FreeTempAssetIDPostProcessing ========
 */
static inline void AESGCMXXF3HSM_FreeTempAssetIDPostProcessing(uintptr_t arg0)
{
    AESGCM_Handle handle         = (AESGCM_Handle)arg0;
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_ERROR;
    int32_t tokenResult          = HSMXXF3_getResultCode();

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->tempAssetID = 0U;
        status              = AESGCM_STATUS_SUCCESS;
    }

    object->common.returnStatus = status;
}

/*
 *  ======== AESGCMXXF3HSM_freeTempAssetID ========
 */
static int_fast16_t AESGCMXXF3HSM_freeTempAssetID(AESGCM_Handle handle)
{
    AESGCMXXF3HSM_Object *object = AESGCMXXF3HSM_getObject(handle);
    int_fast16_t status          = AESGCM_STATUS_SUCCESS;
    int_fast16_t hsmRetval       = HSMXXF3_STATUS_ERROR;

    if (object->tempAssetID != 0)
    {
        HSMXXF3_constructDeleteAssetToken(object->tempAssetID);

        hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                        AESGCMXXF3HSM_FreeTempAssetIDPostProcessing,
                                        (uintptr_t)handle);

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            hsmRetval = HSMXXF3_waitForResult();

            if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
            {
                status = object->common.returnStatus;
            }
        }
    }
    return status;
}
