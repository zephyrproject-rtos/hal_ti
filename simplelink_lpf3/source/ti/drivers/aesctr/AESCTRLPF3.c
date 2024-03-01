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

#include <ti/drivers/aesctr/AESCTRLPF3.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/cryptoutils/aes/AESCommonLPF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.h>
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
#define AESCTRLPF3_DMA_SIZE_THRESHOLD (1U * AES_BLOCK_SIZE)

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
#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESCTRLPF3_DMA_CONFIG                                                                            \
        ((uint32_t)AES_DMA_ADRCHA_TXTX0 | (uint32_t)AES_DMA_TRGCHA_AESDONE | (uint32_t)AES_DMA_ADRCHB_TXT0 | \
         (uint32_t)AES_DMA_TRGCHB_WRTXT3)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESCTRLPF3_DMA_CONFIG                                                                            \
        ((uint32_t)AES_DMA_ADRCHA_TXTX0 | (uint32_t)AES_DMA_TRGCHA_ECBDONE | (uint32_t)AES_DMA_ADRCHB_TXT0 | \
         (uint32_t)AES_DMA_TRGCHB_WRTXT3)
#else
    #error "Unsupported DeviceFamily_Parent for AESCTRLPF3!"
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
#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESCTRLPF3_GATE_CHA_DMA_CONFIG (AESCTRLPF3_DMA_CONFIG | (uint32_t)AES_DMA_DONEACT_GATE_TRGAES_ON_CHA)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESCTRLPF3_GATE_CHA_DMA_CONFIG (AESCTRLPF3_DMA_CONFIG | (uint32_t)AES_DMA_DONEACT_GATE_TRGECB_ON_CHA)
#else
    #error "Unsupported DeviceFamily_Parent for AESCTRLPF3!"
#endif

/* Forward declarations */
static void AESCTRLPF3_initCounter(AESCTRLPF3_Object *object, const uint8_t initialCounter[AES_BLOCK_SIZE]);
static int_fast16_t AESCTRLPF3_oneStepOperation(AESCTR_Handle handle,
                                                AESCTR_OneStepOperation *operation,
                                                AESCTR_OperationType operationType);
static int_fast16_t AESCTRLPF3_startOperation(AESCTR_Handle handle, bool isOneStepOrFinalOperation);
static int_fast16_t AESCTRLPF3_waitForResult(AESCTR_Handle handle);

/*
 *  ======== AESCTRLPF3_getObject ========
 */
static inline AESCTRLPF3_Object *AESCTRLPF3_getObject(AESCTR_Handle handle)
{
    AESCTRLPF3_Object *object = (AESCTRLPF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

/*
 *  ======== AESCTRLPF3_hwiFxn ========
 */
static void AESCTRLPF3_hwiFxn(uintptr_t arg0)
{
    AESCTR_Handle handle      = (AESCTR_Handle)arg0;
    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);

    /*
     * Only the output channel B interrupt is enabled.
     */
    uint32_t intStatus = AESGetMaskedInterruptStatus();

    /* Disable DMA, clear interupts, and release power constraint */
    AESCommonLPF3_cleanupHwi(&object->common);

    if ((intStatus & (uint32_t)AES_MIS_CHBDONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonLPF3_DMA_CHB_BITMASK);

        if ((object->inputLengthRemaining > 0U) && (object->inputLengthRemaining < AESCTRLPF3_DMA_SIZE_THRESHOLD))
        {
            /* Use CPU R/W to complete the CTR operation */
            AESCTRLPF3_processData(&object->input[object->inputLength - object->inputLengthRemaining],
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
        AESCTRLPF3_readCounter((uint32_t *)&object->counter[0]);

        /* Check if one-step or final operation */
        if ((object->operationType & AESCTR_OP_FLAG_SEGMENTED) == 0)
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
            object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
        }
    }
}

/*
 *  ======== AESCTR_init ========
 */
void AESCTR_init(void)
{
    AESCommonLPF3_init();
}

/*
 *  ======== AESCTR_construct ========
 */
AESCTR_Handle AESCTR_construct(AESCTR_Config *config, const AESCTR_Params *params)
{
    DebugP_assert(config);

    int_fast16_t status;
    AESCTR_Handle handle      = config;
    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);

    /* If params are NULL, use defaults */
    if (params == NULL)
    {
        params = &AESCTR_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AESCTR_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->callbackFxn = params->callbackFxn;
    object->threadSafe  = true;

    status = AESCommonLPF3_construct(&object->common, (AES_ReturnBehavior)params->returnBehavior, params->timeout);

    if (status != AES_STATUS_SUCCESS)
    {
        handle = NULL;
    }

    return handle;
}

/*
 *  ======== AESCTR_close ========
 */
void AESCTR_close(AESCTR_Handle handle)
{
    DebugP_assert(handle);

    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);

    AESCommonLPF3_close(&object->common);
}

/*
 *  ======== AESCTR_oneStepEncrypt ========
 */
int_fast16_t AESCTR_oneStepEncrypt(AESCTR_Handle handle, AESCTR_OneStepOperation *operationStruct)
{
    return AESCTRLPF3_oneStepOperation(handle, operationStruct, AESCTR_OPERATION_TYPE_ENCRYPT);
}

/*
 *  ======== AESCTR_oneStepDecrypt ========
 */
int_fast16_t AESCTR_oneStepDecrypt(AESCTR_Handle handle, AESCTR_OneStepOperation *operationStruct)
{
    return AESCTRLPF3_oneStepOperation(handle, operationStruct, AESCTR_OPERATION_TYPE_DECRYPT);
}

/*
 *  ======== AESCTRLPF3_oneStepOperation ========
 */
static int_fast16_t AESCTRLPF3_oneStepOperation(AESCTR_Handle handle,
                                                AESCTR_OneStepOperation *operation,
                                                AESCTR_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    /* No need to assert operationType since we control it within the driver */

    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);
    int_fast16_t status;

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCTR_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
#endif

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonLPF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
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
    status = AESCommonLPF3_setOperationInProgress(&object->common);

    if (status != AESCTR_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
        {
            AESCommonLPF3_clearOperationInProgress(&object->common);
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

    AESCTRLPF3_initCounter(object, &operation->initialCounter[0]);

    status = AESCTRLPF3_startOperation(handle, true);

    return status;
}

/*
 *  ======== AESCTRLPF3_initCounter ========
 */
static void AESCTRLPF3_initCounter(AESCTRLPF3_Object *object, const uint8_t initialCounter[AES_BLOCK_SIZE])
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

/*
 *  ======== AESCTRLPF3_startOperation ========
 */
static int_fast16_t AESCTRLPF3_startOperation(AESCTR_Handle handle, bool isOneStepOrFinalOperation)
{
    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);
    int_fast16_t status       = AESCTR_STATUS_SUCCESS;
    size_t bytesProcessed;

    /* Set up the key and AES engine to begin an operation */
    AESCommonLPF3_setupOperation(&object->common.key, AESCTRLPF3_DEFAULT_AUTOCFG);

    /*
     * Process all operations with data length less than the DMA size
     * threshold as a polling mode operation.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (object->inputLength < AESCTRLPF3_DMA_SIZE_THRESHOLD))
    {
        /* Write the counter value to the AES engine to trigger first encryption */
        AESCTRLPF3_writeCounter((uint32_t *)&object->counter[0]);

        /* Process all blocks with CPU R/W */
        AESCTRLPF3_processData(object->input, object->output, object->inputLength, isOneStepOrFinalOperation);

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
        AESCTRLPF3_HWAttrs const *hwAttrs = handle->hwAttrs;
        AESCommonLPF3_setupHwi(AESCTRLPF3_hwiFxn, (uintptr_t)handle, hwAttrs->intPriority);

        bytesProcessed = AESCTRLPF3_configDataDMA(&object->common, object->input, object->output, object->inputLength);

        object->inputLengthRemaining -= bytesProcessed;

        /* Write the counter value to the AES engine to trigger first encryption */
        AESCTRLPF3_writeCounter((uint32_t *)&object->counter[0]);
    }

    status = AESCTRLPF3_waitForResult(handle);

    return status;
}

/*
 *  ======== AESCTRLPF3_configDataDMA ========
 */
size_t AESCTRLPF3_configDataDMA(AESCommonLPF3_Object *object, const uint8_t *input, uint8_t *output, size_t inputLength)
{
    size_t blockSizeDataLen = AES_BLOCK_SIZE_MULTIPLE_LENGTH(inputLength);

    /* Clear BUSHALT when using DMA */
    AESClearAUTOCFGBusHalt();

    /* Setup DMA configuration and set power constraint */
    if (blockSizeDataLen == inputLength)
    {
        AESCommonLPF3_setupDMA(object, AESCTRLPF3_GATE_CHA_DMA_CONFIG);
    }
    else
    {
        AESCommonLPF3_setupDMA(object, AESCTRLPF3_DMA_CONFIG);
    }

    /*
     * Only full blocks of data can be processed with DMA because the trigger
     * for DMA channel B (output) is based on channel A (input) writing the
     * last word of the TXTX register
     */
    AESCommonLPF3_configInputDMA(input, blockSizeDataLen);
    AESCommonLPF3_configOutputDMA(output, blockSizeDataLen);

    /* Enable interrupt upon output DMA done */
    AESSetIMASK((uint32_t)AES_IMASK_CHBDONE_M);

    return blockSizeDataLen;
}

/*
 *  ======== AESCTRLPF3_processData ========
 */
void AESCTRLPF3_processData(const uint8_t *input, uint8_t *output, size_t inputLength, bool isOneStepOrFinalOperation)
{
    size_t bytesProcessed                 = 0;
    size_t bytesRemaining                 = inputLength;
    size_t blockSizeAlignedBytesRemaining = AES_BLOCK_SIZE_MULTIPLE_LENGTH(inputLength);

    if (blockSizeAlignedBytesRemaining > 0U)
    {
        bytesRemaining -= blockSizeAlignedBytesRemaining;

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
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
                    AESSetAUTOCFG(AESCTRLPF3_LAST_BLOCK_AUTOCFG);
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
                AESSetAUTOCFG(AESCTRLPF3_LAST_BLOCK_AUTOCFG);

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
 *  ======== AESCTRLPF3_waitForResult ========
 */
static int_fast16_t AESCTRLPF3_waitForResult(AESCTR_Handle handle)
{
    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);
    int_fast16_t status;

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (object->inputLength < AESCTRLPF3_DMA_SIZE_THRESHOLD))
    {
        /* Save the last counter value from the AES engine */
        AESCTRLPF3_readCounter((uint32_t *)&object->counter[0]);

        /*
         * Save the object's returnStatus before clearing operationInProgress or
         * posting the access semaphore in case it is overwritten.
         */
        status = object->common.returnStatus;

        if ((object->operationType & AESCTR_OP_FLAG_SEGMENTED) == 0U)
        {
            /* One-step or finalization operation is complete */
            AESCommonLPF3_clearOperationInProgress(&object->common);
        }

        AESCommonLPF3_cleanup(&object->common);

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
        (void)SemaphoreP_pend((SemaphoreP_Handle)&CryptoResourceLPF3_operationSemaphore,
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

/*
 *  ======== AESCTR_addData ========
 */
int_fast16_t AESCTR_addData(AESCTR_Handle handle, AESCTR_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);
    int_fast16_t status;

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

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
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
        !AESCommonLPF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCTR_STATUS_ERROR;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
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

    status = AESCTRLPF3_startOperation(handle, false);

    return status;
}

/*
 *  ======== AESCTR_finalize ========
 */
int_fast16_t AESCTR_finalize(AESCTR_Handle handle, AESCTR_SegmentedOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);
    AESCTR_OperationType operationType;
    int_fast16_t status;

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

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCTR_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
#endif

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) && (operation->inputLength > 0U) &&
        !AESCommonLPF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
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
            if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
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

        status = AESCTRLPF3_startOperation(handle, true);
    }
    else /* Operation was finalized without additional data to process */
    {
        /*
         * Save the object's returnStatus in case it is
         * overwritten during setup of a new segmented operation
         * after the operationInProgress flag is cleared.
         */
        status = object->common.returnStatus;

        AESCommonLPF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCTR_OperationUnion *)operation, operationType);

            /* Always return success in callback mode */
            status = AESCTR_STATUS_SUCCESS;
        }
    }

    return status;
}

/*
 *  ======== AESCTRLPF3_setupSegmentedOperation ========
 */
static int_fast16_t AESCTRLPF3_setupSegmentedOperation(AESCTRLPF3_Object *object,
                                                       const CryptoKey *key,
                                                       const uint8_t initialCounter[AES_BLOCK_SIZE])
{
    DebugP_assert(key);

    /*
     * Key material pointer and length are not checked until adding or
     * finalizing data.
     */

    int_fast16_t status = AESCommonLPF3_setupSegmentedOperation(&object->common, key);

    if (status == AESCTR_STATUS_SUCCESS)
    {
        AESCTRLPF3_initCounter(object, &initialCounter[0]);

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
    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);
    DebugP_assert(object);

    int_fast16_t status = AESCTRLPF3_setupSegmentedOperation(object, key, initialCounter);

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
    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);
    DebugP_assert(object);

    int_fast16_t status = AESCTRLPF3_setupSegmentedOperation(object, key, initialCounter);

    if (status == AESCTR_STATUS_SUCCESS)
    {
        object->operationType = AESCTR_OPERATION_TYPE_DECRYPT_SEGMENTED;
    }

    return status;
}

/*
 *  ======== AESCTR_cancelOperation ========
 */
int_fast16_t AESCTR_cancelOperation(AESCTR_Handle handle)
{
    DebugP_assert(handle);

    AESCTRLPF3_Object *object = AESCTRLPF3_getObject(handle);

    uintptr_t interruptKey = HwiP_disable();

    /*
     * Return success if there is no active operation to cancel.
     * Do not execute the callback as it would have been executed already
     * when the operation completed.
     */
    if (!object->common.operationInProgress)
    {
        HwiP_restore(interruptKey);
        return AESCTR_STATUS_SUCCESS;
    }

    HwiP_restore(interruptKey);

    /*
     * Cancel DMA for input and output channels, clear operation in-progress,
     * and releases crypto resource if necessary.
     */
    AESCommonLPF3_cancelOperation(&object->common, true);

    /*
     * Operation pointer could be NULL if a segmented operation was setup
     * but neither AESCCM_addData or AESCCM_finalize was called.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
    {
        /* Call the callback function provided by the application */
        object->callbackFxn(handle, AESCTR_STATUS_CANCELED, object->operation, object->operationType);
    }

    return AESCTR_STATUS_SUCCESS;
}
