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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <ti/drivers/aescmac/AESCMACLPF3.h>

#include <ti/drivers/AESCMAC.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/aesecb/AESECBLPF3.h>
#include <ti/drivers/cryptoutils/aes/AESCommonLPF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.h>
#include <ti/drivers/cryptoutils/utils/CryptoUtils.h>
#include <ti/drivers/dma/UDMALPF3.h>

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/aes.h)
#include DeviceFamily_constructPath(inc/hw_aes.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)

/**
 * The threshold at which blocking and callback mode transfers will utilize DMA.
 * For data lengths below this threshold, polling CPU R/W will be used instead
 * of DMA. With task switching and interrupt overhead, it is inefficient to
 * utilize DMA for shorter length operations.
 * The threshold value must be a multiple of AES_BLOCK_SIZE.
 */
#define AESCMACLPF3_DMA_SIZE_THRESHOLD (1U * AES_BLOCK_SIZE)

#define AESCMAC_CONST_RB  ((uint8_t)0x87U)
#define AESCMAC_MSB_CHECK ((uint8_t)0x80U)
#define AESCMAC_PADDING   ((uint8_t)0x80U)

typedef enum
{
    AESCMAC_SUBKEY1,
    AESCMAC_SUBKEY2
} AESCMAC_SUBKEY_NUM;

/* Forward declarations */
static void AESCMACLPF3_deriveSubKey(uint8_t *buffer);
static void AESCMACLPF3_generateSubKey(AESCMAC_SUBKEY_NUM subKeyNum, uint32_t subKey[AES_BLOCK_SIZE_WORDS]);
static void AESCMACLPF3_getResult(AESCMACLPF3_Object *object);
static inline void AESCMACLPF3_prepareFinalInputBlock(AESCMACLPF3_Object *object, size_t *transactionLength);
static int_fast16_t AESCMACLPF3_setupSegmentedOperation(AESCMACLPF3_Object *object, const CryptoKey *key);
static int_fast16_t AESCMACLPF3_oneStepOperation(AESCMAC_Handle handle,
                                                 AESCMAC_Operation *operation,
                                                 const CryptoKey *key,
                                                 AESCMAC_OperationType operationType);
static int_fast16_t AESCMACLPF3_startOperation(AESCMAC_Handle handle);
static inline int_fast16_t AESCMACLPF3_waitForResult(AESCMAC_Handle handle);
static inline void AESCMACLPF3_xorBlock(uint32_t *block1_dst, const uint32_t *block2);

/*
 *  ======== AESCMACLPF3_getObject ========
 */
static inline AESCMACLPF3_Object *AESCMACLPF3_getObject(AESCMAC_Handle handle)
{
    AESCMACLPF3_Object *object = (AESCMACLPF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

/*
 *  ======== AESCMACLPF3_hwiFxn ========
 */
static void AESCMACLPF3_hwiFxn(uintptr_t arg0)
{
    AESCMAC_Handle handle      = (AESCMAC_Handle)arg0;
    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);

    /*
     * Only the input channel A interrupt is enabled.
     */
    uint32_t intStatus = AESGetMaskedInterruptStatus();

    /* Disable DMA, clear interupts, and release power constraint */
    AESCommonLPF3_cleanupHwi(&object->common);

    if ((intStatus & (uint32_t)AES_MIS_CHADONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonLPF3_DMA_CHA_BITMASK);

        AESCMACLPF3_getResult(object);

        /* Clear operation in-progress if one-step or finalize operation */
        if (object->operationType != AESCMAC_OP_TYPE_SEGMENTED_SIGN &&
            object->operationType != AESCMAC_OP_TYPE_SEGMENTED_VERIFY)
        {
            AESCommonLPF3_clearOperationInProgress(&object->common);
        }

        /* Cleanup and release crypto resource lock */
        AESCommonLPF3_cleanup(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_BLOCKING)
        {
            /* Unblock the pending task to signal that the operation is complete */
            SemaphoreP_post(&CryptoResourceLPF3_operationSemaphore);
        }
        else
        {
            /* Call the callback function provided by the application */
            object->callbackFxn((AESCMAC_Handle)handle,
                                object->common.returnStatus,
                                object->operation,
                                object->operationType);
        }
    }
}

/*
 *  ======== AESCMAC_init ========
 */
void AESCMAC_init(void)
{
    AESCommonLPF3_init();
}

/*
 *  ======== AESCMAC_construct ========
 */
AESCMAC_Handle AESCMAC_construct(AESCMAC_Config *config, const AESCMAC_Params *params)
{
    DebugP_assert(config);

    int_fast16_t status;
    AESCMAC_Handle handle      = config;
    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);

    /* If params are NULL, use defaults */
    if (params == NULL)
    {
        params = &AESCMAC_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AES_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->operationalMode = params->operationalMode;
    object->callbackFxn     = params->callbackFxn;
    object->threadSafe      = true;

    status = AESCommonLPF3_construct(&object->common, (AES_ReturnBehavior)params->returnBehavior, params->timeout);

    if (status != AES_STATUS_SUCCESS)
    {
        handle = NULL;
    }

    return handle;
}

/*
 *  ======== AESCMACLPF3_readTag ========
 */
void AESCMACLPF3_readTag(uint32_t tagOut[AES_TAG_LENGTH_BYTES / 4U])
{
    /* Wait until the operation is done */
    while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}

    AESReadTag32(&tagOut[0]);
}

/*
 *  ======== AESCMACLPF3_getResult ========
 */
static void AESCMACLPF3_getResult(AESCMACLPF3_Object *object)
{
    AESCMAC_Operation *operation = object->operation;
    uint8_t opcode               = (object->operationType & AESCMAC_OP_CODE_MASK);

    if (object->common.returnStatus == AESCMAC_STATUS_SUCCESS)
    {
        /* If One-step or Finalize operation, process the final input block */
        if (opcode != AESCMAC_OP_CODE_SEGMENTED)
        {
            AESWriteBUF32(&object->finalInputBlock[0]);
        }

        AESCMACLPF3_readTag((uint32_t *)&object->intermediateTag[0]);

        /* If One-step or Finalize operation, verify or copy the MAC */
        if (opcode != AESCMAC_OP_CODE_SEGMENTED)
        {
            if (object->operationType & AESCMAC_OP_FLAG_SIGN)
            {
                (void)memcpy((void *)operation->mac, (void *)&object->intermediateTag[0], operation->macLength);
            }
            else
            {
                /* Constant time comparison of output tag versus provided MAC */
                if (!CryptoUtils_buffersMatch(&object->intermediateTag[0], operation->mac, operation->macLength))
                {
                    object->common.returnStatus = AESCMAC_STATUS_MAC_INVALID;
                }
            }
        }
    }
}

/*
 *  ======== AESCMACLPF3_startOperation ========
 */
static int_fast16_t AESCMACLPF3_startOperation(AESCMAC_Handle handle)
{
    AESCMACLPF3_Object *object   = AESCMACLPF3_getObject(handle);
    AESCMAC_Operation *operation = object->operation;

    /* Input pointer cannot be NULL if input length is non-zero */
    DebugP_assert((operation->inputLength == 0U) || operation->input);

    uint8_t opcode = (object->operationType & AESCMAC_OP_CODE_MASK);

    /*
     * MAC pointer cannot be NULL if performing a one-step operation or
     * finalizing a segmented operation
     */
    DebugP_assert((opcode == AESCMAC_OP_CODE_SEGMENTED) || (operation->mac));

    AESCMAC_OperationType operationType;
    int_fast16_t status      = AESCMAC_STATUS_ERROR;
    size_t transactionLength = operation->inputLength;

    /* Load key */
    AESCommonLPF3_loadKey(&object->common.key);

    /*
     * If One-step or Finalization operation, prepare the final
     * input block and adjust the transaction length accordingly.
     */
    if (opcode != AESCMAC_OP_CODE_SEGMENTED)
    {
        AESCMACLPF3_prepareFinalInputBlock(object, &transactionLength);
    }

    AESSetAUTOCFG(AESCMACLPF3_DEFAULT_AUTOCFG);

    /*
     * Set IV to intermediate tag (initialized to zero at the start
     * of a new operation).
     */
    AESWriteIV32((uint32_t *)&object->intermediateTag[0]);

    if (transactionLength == 0U)
    {
        /*
         * If transaction length is zero, only the final input block
         * of data remains to be processed for CMAC. Call AESCMAC_getResult()
         * to process the last block, obtain the result, and store status of
         * the operation in object->returnStatus.
         */
        AESCMACLPF3_getResult(object);

        /*
         * Save the object's data to provide to callback in case it
         * is overwritten during by the start of a new operation
         * after the operationInProgress flag is cleared or access
         * semaphore is posted.
         */
        status        = object->common.returnStatus;
        operationType = object->operationType;

        AESCommonLPF3_clearOperationInProgress(&object->common);

        /*
         * Handle clean up of the operation and post access semaphore to allow
         * callback to chain operations.
         */
        AESCommonLPF3_cleanup(&(object->common));

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            /* Call the callback function provided by the application */
            object->callbackFxn(handle, status, operation, operationType);

            /* Always return success in callback mode */
            status = AESCMAC_STATUS_SUCCESS;
        }
    }
    else
    {
        if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
            (transactionLength < AESCMACLPF3_DMA_SIZE_THRESHOLD))
        {
            /*
             * Process all data. Transaction length is updated in
             * AESCMACLPF3_prepareFinalInputBlock() to be the truncated
             * message length (which excludes the final block).
             */
            AESCMACLPF3_processBlocks(operation->input, transactionLength);
        }
        else
        {
            /*
             * We need to set the HWI function and priority since the same physical
             * interrupt is shared by multiple drivers and they all need to coexist.
             * Whenever a driver starts an operation, it registers its HWI callback
             * with the OS.
             */
            AESCMACLPF3_HWAttrs const *hwAttrs = handle->hwAttrs;
            AESCommonLPF3_setupHwi(AESCMACLPF3_hwiFxn, (uintptr_t)handle, hwAttrs->intPriority);

            /* Clear BUSHALT when using DMA */
            AESClearAUTOCFGBusHalt();

            /* Setup DMA configuration and set power constraint */
            AESCommonLPF3_setupDMA(&object->common, AESCMACLPF3_DMA_CONFIG);

            AESCommonLPF3_configInputDMA(operation->input, transactionLength);

            /* Enable interrupt upon input DMA done */
            AESSetIMASK((uint32_t)AES_IMASK_CHADONE_M);

            /* Manually trigger the DMA to start the ECB operation */
            AESSetTrigger((uint32_t)AES_TRG_DMACHA);
        }

        status = AESCMACLPF3_waitForResult(handle);
    }

    return status;
}

/*
 *  ======== AESCMACLPF3_processBlocks ========
 */
void AESCMACLPF3_processBlocks(const uint8_t *input, size_t transactionLength)
{
#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    AESProcessAlignedBlocksCMAC((const uint32_t *)input, (uint32_t)AES_GET_NUM_BLOCKS(transactionLength));
#else
    size_t bytesProcessed                = 0;
    size_t transactionLengthDoubleBlocks = transactionLength & AES_DOUBLE_BLOCK_SIZE_MULTIPLE_MASK;
    size_t transactionLengthSingleBlocks = transactionLength & (size_t)~AES_DOUBLE_BLOCK_SIZE_MULTIPLE_MASK;

    /*
     * The code below has additional optimizations for word-aligned input data
     * to support lower latency AES-CCM operations for BLE stack.
     */
    if (IS_WORD_ALIGNED(input))
    {
        AESProcessAlignedBlocksCMAC((const uint32_t *)input, (uint32_t)AES_GET_NUM_BLOCKS(transactionLength));
    }
    else
    {
        while (bytesProcessed < transactionLengthDoubleBlocks)
        {
            AESWriteBUF(&input[bytesProcessed]);
            bytesProcessed += AES_BLOCK_SIZE;

            AESWriteBUF(&input[bytesProcessed]);
            bytesProcessed += AES_BLOCK_SIZE;
        }

        /* Process any remaining single block */
        if (transactionLengthSingleBlocks != 0U)
        {
            AESWriteBUF(&input[bytesProcessed]);
        }
    }
#endif
}

/*
 *  ======== AESCMACLPF3_xorBlock ========
 *  XOR's two 16-byte blocks, storing the result in block1_dst.
 */
static inline void AESCMACLPF3_xorBlock(uint32_t *block1_dst, const uint32_t *block2)
{
    uint_fast8_t i;

    for (i = (uint_fast8_t)0U; i < (uint_fast8_t)AES_BLOCK_SIZE_WORDS; i++)
    {
        block1_dst[i] = block1_dst[i] ^ block2[i];
    }
}

/*
 *  ======== AESCMACLPF3_prepareFinalInputBlock ========
 */
static inline void AESCMACLPF3_prepareFinalInputBlock(AESCMACLPF3_Object *object, size_t *transactionLength)
{
    AESCMAC_Operation *operation = object->operation;
    size_t finalInputLength      = 0U;
    size_t truncatedInputLength  = 0U;
    uint32_t subKey[AES_BLOCK_SIZE_WORDS];

    /* Copy last partial or full block of input into local buffer */
    CryptoUtils_memset((void *)&object->finalInputBlock[0],
                       sizeof(object->finalInputBlock),
                       (uint8_t)0U,
                       sizeof(object->finalInputBlock));

    if (operation->inputLength != 0U)
    {
        finalInputLength = AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->inputLength);

        if (finalInputLength == 0U)
        {
            finalInputLength = AES_BLOCK_SIZE;
        }

        truncatedInputLength = operation->inputLength - finalInputLength;

        (void)memcpy(object->finalInputBlock, &operation->input[truncatedInputLength], finalInputLength);
    }

    /* CMAC requires the final block to be XOR'd with a subkey */
    if (object->operationalMode == AESCMAC_OPMODE_CMAC)
    {
        /* Check if input message length is a positive block multiple */
        if ((operation->inputLength != 0U) && (finalInputLength == AES_BLOCK_SIZE))
        {
            /* Generate subkey1 */
            AESCMACLPF3_generateSubKey(AESCMAC_SUBKEY1, subKey);
        }
        else
        {
            /* Generate subkey2 */
            AESCMACLPF3_generateSubKey(AESCMAC_SUBKEY2, subKey);

            /* Set padding byte if partial block */
            ((uint8_t *)&object->finalInputBlock[0])[finalInputLength] = AESCMAC_PADDING;
        }

        /* XOR final block with subkey */
        AESCMACLPF3_xorBlock(object->finalInputBlock, subKey);
    }

    *transactionLength = truncatedInputLength;
}

/*
 *  ======== AESCMACLPF3_oneStepOperation ========
 */
static int_fast16_t AESCMACLPF3_oneStepOperation(AESCMAC_Handle handle,
                                                 AESCMAC_Operation *operation,
                                                 const CryptoKey *key,
                                                 AESCMAC_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(key);
    /* No need to assert operationType since we control it within the driver */

    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);

    /* CBC-MAC is not permitted for zero length messages */
    if ((object->operationalMode == AESCMAC_OPMODE_CBCMAC) && (operation->inputLength == 0U))
    {
        return AESCMAC_STATUS_ERROR;
    }

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input pointer */
    if (!IS_WORD_ALIGNED(operation->input))
    {
        return AESCMAC_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
#endif

    if (operation->macLength > sizeof(object->intermediateTag))
    {
        return AESCMAC_STATUS_ERROR;
    }

    /*
     * Check that there is no operation already in progress for this driver
     * instance.
     */
    int_fast16_t status = AESCommonLPF3_setOperationInProgress(&object->common);

    if (status != AESCMAC_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
        {
            AESCommonLPF3_clearOperationInProgress(&object->common);
            return AESCMAC_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation           = operation;
    object->operationType       = operationType;
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESCMAC_STATUS_SUCCESS;
    /* Make internal copy of crypto key */
    object->common.key          = *key;

    /* Zero the intermediate tag because it will be used as the IV */
    CryptoUtils_memset((void *)&object->intermediateTag[0],
                       sizeof(object->intermediateTag),
                       (uint8_t)0U,
                       sizeof(object->intermediateTag));

    status = AESCMACLPF3_startOperation(handle);

    if ((status != AESCMAC_STATUS_SUCCESS) && (object->common.cryptoResourceLocked))
    {
        CryptoResourceLPF3_releaseLock();
        object->common.cryptoResourceLocked = false;
        AESCommonLPF3_clearOperationInProgress(&object->common);
    }

    return status;
}

/*
 *  ======== AESCMACLPF3_waitForResult ========
 */
static inline int_fast16_t AESCMACLPF3_waitForResult(AESCMAC_Handle handle)
{
    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);
    int_fast16_t status        = AESCMAC_STATUS_ERROR;
    uint8_t opcode             = (object->operationType & AESCMAC_OP_CODE_MASK);

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (object->operation->inputLength < AESCMACLPF3_DMA_SIZE_THRESHOLD))
    {
        AESCMACLPF3_getResult(object);

        /*
         * Save the object's returnStatus before clearing operationInProgress or
         * posting the access semaphore in case it is overwritten.
         */
        status = object->common.returnStatus;

        /* Mark operation as no longer in progress if one-step or final operation */
        if (opcode != AESCMAC_OP_CODE_SEGMENTED)
        {
            AESCommonLPF3_clearOperationInProgress(&object->common);
        }

        AESCommonLPF3_cleanup(&(object->common));

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, object->operation, object->operationType);

            /* Always return success in callback mode */
            status = AESCMAC_STATUS_SUCCESS;
        }
    }
    else if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_BLOCKING)
    {
        (void)SemaphoreP_pend((SemaphoreP_Handle)&CryptoResourceLPF3_operationSemaphore,
                              (uint32_t)SemaphoreP_WAIT_FOREVER);

        status = object->common.returnStatus;
    }
    else /* AES_RETURN_BEHAVIOR_CALLBACK */
    {
        /* AESCMAC_STATUS_SUCCESS is always returned in callback mode */
        status = AESCMAC_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== AESCMAC_oneStepSign ========
 */
int_fast16_t AESCMAC_oneStepSign(AESCMAC_Handle handle, AESCMAC_Operation *operation, CryptoKey *key)
{
    return AESCMACLPF3_oneStepOperation(handle, operation, key, AESCMAC_OP_TYPE_SIGN);
}

/*
 *  ======== AESCMAC_oneStepVerify ========
 */
int_fast16_t AESCMAC_oneStepVerify(AESCMAC_Handle handle, AESCMAC_Operation *operation, CryptoKey *key)
{
    return AESCMACLPF3_oneStepOperation(handle, operation, key, AESCMAC_OP_TYPE_VERIFY);
}

/*
 *  ======== AESCMACLPF3_setupSegmentedOperation ========
 */
static int_fast16_t AESCMACLPF3_setupSegmentedOperation(AESCMACLPF3_Object *object, const CryptoKey *key)
{
    DebugP_assert(key);

    /*
     * Key material pointer and length are not asserted until adding or
     * finalizing data.
     */

    int_fast16_t status = AESCommonLPF3_setupSegmentedOperation(&object->common, key);

    if (status == AESCMAC_STATUS_SUCCESS)
    {
        /*
         * Initialize operation pointer to NULL in case AESCBC_cancelOperation
         * is called after AESCMAC_setupXXXX and callback should be skipped.
         */
        object->operation = NULL;

        /* Zero the intermediate tag because it will be used as the IV */
        CryptoUtils_memset((void *)&object->intermediateTag[0],
                           sizeof(object->intermediateTag),
                           (uint8_t)0U,
                           sizeof(object->intermediateTag));
    }

    return status;
}

/*
 *  ======== AESCMAC_setupSign ========
 */
int_fast16_t AESCMAC_setupSign(AESCMAC_Handle handle, const CryptoKey *key)
{
    DebugP_assert(handle);

    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);

    int_fast16_t status = AESCMACLPF3_setupSegmentedOperation(object, key);

    if (status == AESCMAC_STATUS_SUCCESS)
    {
        object->operationType = AESCMAC_OP_TYPE_SEGMENTED_SIGN;
    }

    return status;
}

/*
 *  ======== AESCMAC_setupVerify ========
 */
int_fast16_t AESCMAC_setupVerify(AESCMAC_Handle handle, const CryptoKey *key)
{
    DebugP_assert(handle);

    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);

    int_fast16_t status = AESCMACLPF3_setupSegmentedOperation(object, key);

    if (status == AESCMAC_STATUS_SUCCESS)
    {
        object->operationType = AESCMAC_OP_TYPE_SEGMENTED_VERIFY;
    }

    return status;
}

/*
 *  ======== AESCMAC_addData ========
 */
int_fast16_t AESCMAC_addData(AESCMAC_Handle handle, AESCMAC_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);
    int_fast16_t status;

    /* Assert the segmented operation was setup */
    DebugP_assert((object->operationType == AESCMAC_OP_TYPE_SEGMENTED_SIGN) ||
                  (object->operationType == AESCMAC_OP_TYPE_SEGMENTED_VERIFY));

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESCMAC_STATUS_SUCCESS)
    {
        /* Return the status of the previous call.
         * The callback function will not be executed.
         */
        return object->common.returnStatus;
    }

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input pointer */
    if (!IS_WORD_ALIGNED(operation->input))
    {
        return AESCMAC_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
#endif

    /* Verify the input length is non-zero and a multiple of the block size */
    if ((operation->inputLength == 0U) || (AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->inputLength) > 0U))
    {
        return AESCMAC_STATUS_ERROR;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
        {
            return AESCMAC_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation = operation;
    status            = AESCMACLPF3_startOperation(handle);

    if ((status != AESCMAC_STATUS_SUCCESS) && (object->common.cryptoResourceLocked))
    {
        CryptoResourceLPF3_releaseLock();
        object->common.cryptoResourceLocked = false;
    }

    return status;
}

/* Perform ECB encryption on a block of zeros */
static inline void AESCMACLPF3_encryptZeroBlockECB(uint32_t output[AES_BLOCK_SIZE_WORDS])
{
    const uint32_t zeroBlock[AES_BLOCK_SIZE_WORDS] = {0};

    AESSetAUTOCFG(AESEBCLPF3_SINGLE_BLOCK_AUTOCFG);

    /* Write block of zeros to input */
    AESWriteBUF32(&zeroBlock[0]);

    /* Wait until the operation is done */
    while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}

    /* Read output */
    AESReadTXT32(&output[0]);
}

/*
 *  ======== AESCMACLPF3_generateSubKey ========
 *  Generate AES CMAC subkey based on
 *  https://tools.ietf.org/html/rfc4493#section-2.3
 */
static void AESCMACLPF3_generateSubKey(AESCMAC_SUBKEY_NUM subKeyNum, uint32_t subKey[AES_BLOCK_SIZE_WORDS])
{
    /* Perform ECB encryption on the block of zeros using CPU R/W */
    AESCMACLPF3_encryptZeroBlockECB(&subKey[0]);

    /*
     * At this point, subKey buffer only has the ciphertext
     * generated by encrypting a block of 0's.
     * Derive SubKey1.
     */
    AESCMACLPF3_deriveSubKey((uint8_t *)&subKey[0]);

    if (subKeyNum == AESCMAC_SUBKEY2)
    {
        /* At this point, subKey buffer contains SubKey1. Derive SubKey2. */
        AESCMACLPF3_deriveSubKey((uint8_t *)&subKey[0]);
    }
}

/*
 *  ======== AESCMACLPF3_deriveSubKey ========
 */
static void AESCMACLPF3_deriveSubKey(uint8_t *buffer)
{
    uint_fast8_t i;
    uint8_t xorMask = (uint8_t)0U;

    if ((buffer[0] & AESCMAC_MSB_CHECK) != (uint8_t)0U)
    {
        xorMask = AESCMAC_CONST_RB;
    }

    for (i = (uint_fast8_t)0U; i < (uint_fast8_t)AES_BLOCK_SIZE; i += (uint_fast8_t)1U)
    {
        if (i != (uint_fast8_t)0U)
        {
            buffer[i - (uint_fast8_t)1U] += (buffer[i] >> 7U);
        }

        buffer[i] = buffer[i] << 1U;
    }

    buffer[AES_BLOCK_SIZE - 1U] ^= xorMask;
}

/*
 *  ======== AESCMAC_finalize ========
 */
int_fast16_t AESCMAC_finalize(AESCMAC_Handle handle, AESCMAC_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);
    int_fast16_t status;

    /* Assert the segmented operation was setup */
    DebugP_assert((object->operationType == AESCMAC_OP_TYPE_SEGMENTED_SIGN) ||
                  (object->operationType == AESCMAC_OP_TYPE_SEGMENTED_VERIFY));

    /* Check for previous failure or cancellation of segmented operation */
    if (object->common.returnStatus != AESCMAC_STATUS_SUCCESS)
    {
        /*
         * Return the failure status of previous call.
         * The callback will not be called.
         */
        return object->common.returnStatus;
    }

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input pointer */
    if (!IS_WORD_ALIGNED(operation->input))
    {
        return AESCMAC_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
#endif

    if (operation->macLength > sizeof(object->intermediateTag))
    {
        return AESCMAC_STATUS_ERROR;
    }

    if (operation->inputLength == 0U)
    {
        /*
         * Finalizing an operation without providing data to process is not
         * supported. Return an error.
         */
        return AESCMAC_STATUS_ERROR;
    }

    /* Try and obtain access to the crypto module */
    if (object->threadSafe)
    {
        if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
        {
            return AESCMAC_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    if (object->operationType == AESCMAC_OP_TYPE_SEGMENTED_SIGN)
    {
        object->operationType = AESCMAC_OP_TYPE_FINALIZE_SIGN;
    }
    else
    {
        object->operationType = AESCMAC_OP_TYPE_FINALIZE_VERIFY;
    }

    object->operation = operation;
    status            = AESCMACLPF3_startOperation(handle);

    if ((status != AESCMAC_STATUS_SUCCESS) && (object->common.cryptoResourceLocked))
    {
        CryptoResourceLPF3_releaseLock();
        object->common.cryptoResourceLocked = false;
    }

    return status;
}

/*
 *  ======== AESCMAC_close ========
 */
void AESCMAC_close(AESCMAC_Handle handle)
{
    DebugP_assert(handle);

    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);

    AESCommonLPF3_close(&object->common);
}

/*
 *  ======== AESCMAC_cancelOperation ========
 */
int_fast16_t AESCMAC_cancelOperation(AESCMAC_Handle handle)
{
    DebugP_assert(handle);

    AESCMACLPF3_Object *object = AESCMACLPF3_getObject(handle);

    uintptr_t interruptKey = HwiP_disable();

    /*
     * Return success if there is no active operation to cancel.
     * Do not execute the callback as it would have been executed already
     * when the operation completed.
     */
    if (!object->common.operationInProgress)
    {
        HwiP_restore(interruptKey);
        return AESCMAC_STATUS_SUCCESS;
    }

    HwiP_restore(interruptKey);

    /*
     * Cancel DMA for input channel A only, clear operation in-progress,
     * and release crypto resource if locked.
     */
    AESCommonLPF3_cancelOperation(&object->common, false);

    /*
     * Operation pointer could be NULL if a segmented operation was setup
     * but neither AESCMAC_addData or AESCMAC_finalize was called.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
    {
        /* Call the callback function provided by the application */
        object->callbackFxn(handle, AESCMAC_STATUS_CANCELED, object->operation, object->operationType);
    }

    return AESCMAC_STATUS_SUCCESS;
}
