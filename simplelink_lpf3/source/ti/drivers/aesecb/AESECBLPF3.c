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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <ti/drivers/aesecb/AESECBLPF3.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/AESECB.h>
#include <ti/drivers/cryptoutils/aes/AESCommonLPF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.h>
#include <ti/drivers/dma/UDMALPF3.h>

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    #include <ti/drivers/cryptoutils/hsm/HSMLPF3.h>
#endif

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/aes.h)
#include DeviceFamily_constructPath(inc/hw_aes.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)

/*
 * Default AES ECB auto config:
 *  ECB SRC as BUF
 *  Trigger points for auto ECB as RDTX3 and WRBUF3S
 *   (the first encryption starts by writing BUF3, the successive ones by reading TXT3)
 *  BUSHALT enabled
 */
#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESECBLPF3_DEFAULT_AUTOCFG                                             \
        ((uint32_t)AES_AUTOCFG_AESSRC_BUF | (uint32_t)AES_AUTOCFG_TRGAES_WRBUF3S | \
         (uint32_t)AES_AUTOCFG_TRGAES_RDTXT3 | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESECBLPF3_DEFAULT_AUTOCFG                                             \
        ((uint32_t)AES_AUTOCFG_ECBSRC_BUF | (uint32_t)AES_AUTOCFG_TRGECB_WRBUF3S | \
         (uint32_t)AES_AUTOCFG_TRGECB_RDTXT3 | (uint32_t)AES_AUTOCFG_BUSHALT_EN)
#else
    #error "Unsupported DeviceFamily_Parent for AESECBLPF3!"
#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    #define PSA_SYM_MODE_GCM_NONE 0U

    /* Size of state asset for GCM/CCM continuation */
    #define PSA_SYM_STATE_ASSET_SIZE 48U
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
#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    #define AESECBLPF3_DMA_CONFIG                                                           \
        ((uint32_t)AES_DMA_ADRCHA_BUF0 | (uint32_t)AES_DMA_TRGCHA_AESSTART |                \
         (uint32_t)AES_DMA_DONEACT_GATE_TRGAES_ON_CHA_DEL | (uint32_t)AES_DMA_ADRCHB_TXT0 | \
         (uint32_t)AES_DMA_TRGCHB_AESDONE)
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    #define AESECBLPF3_DMA_CONFIG                                                           \
        ((uint32_t)AES_DMA_ADRCHA_BUF0 | (uint32_t)AES_DMA_TRGCHA_ECBSTART |                \
         (uint32_t)AES_DMA_DONEACT_GATE_TRGECB_ON_CHA_DEL | (uint32_t)AES_DMA_ADRCHB_TXT0 | \
         (uint32_t)AES_DMA_TRGCHB_ECBDONE)
#else
    #error "Unsupported DeviceFamily_Parent for AESECBLPF3!"
#endif

/* Forward declarations */
static int_fast16_t AESECBLPF3_checkOperation(const AESECBLPF3_Object *object, const AESECB_Operation *operation);
static inline void AESECBLPF3_processDataCPU(const uint8_t *input, uint8_t *output, size_t inputLength);
static inline void AESECBLPF3_processDataDMA(AESCommonLPF3_Object *object,
                                             const uint8_t *input,
                                             uint8_t *output,
                                             size_t inputLength);
static inline int_fast16_t AESECBLPF3_oneStepOperation(AESECB_Handle handle,
                                                       AESECB_Operation *operation,
                                                       AESECB_OperationType operationType);
static int_fast16_t AESECBLPF3_startOperation(AESECB_Handle handle, AESECB_Operation *operation);
static inline int_fast16_t AESECBLPF3_waitForResult(AESECB_Handle handle);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
static int_fast16_t AESECBLPF3HSM_oneStepOperation(AESECB_Handle handle,
                                                   AESECB_Operation *operation,
                                                   AESECB_OperationType operationType);
static int_fast16_t AESECBLPF3HSM_processOneStep(AESECB_Handle handle);

static int_fast16_t AESECBLPF3HSM_addData(AESECB_Handle handle, AESECB_Operation *operation);

static int_fast16_t AESECBLPF3HSM_finalize(AESECB_Handle handle, AESECB_Operation *operation);

#endif

/*
 *  ======== AESEBCLPF3_getObject ========
 */
static inline AESECBLPF3_Object *AESEBCLPF3_getObject(AESECB_Handle handle)
{
    AESECBLPF3_Object *object = (AESECBLPF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

/*
 *  ======== AESECBLPF3_hwiFxn ========
 */
static void AESECBLPF3_hwiFxn(uintptr_t arg0)
{
    AESECB_Handle handle      = (AESECB_Handle)arg0;
    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);

    /*
     * Only the output channel B interrupt is enabled.
     */
    uint32_t intStatus = AESGetMaskedInterruptStatus();

    /* Disable DMA, clear interupts, and release power constraint */
    AESCommonLPF3_cleanupHwi(&object->common);

    if ((intStatus & (uint32_t)AES_MIS_CHBDONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonLPF3_DMA_CHB_BITMASK);

        if ((object->operationType == AESECB_OPERATION_TYPE_ENCRYPT) ||
            (object->operationType == AESECB_OPERATION_TYPE_FINALIZE_ENCRYPT_SEGMENTED))
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
 *  ======== AESECB_init ========
 */
void AESECB_init(void)
{
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    HSMLPF3_constructRTOSObjects();
#endif
    AESCommonLPF3_init();
}

/*
 *  ======== AESECB_construct ========
 */
AESECB_Handle AESECB_construct(AESECB_Config *config, const AESECB_Params *params)
{
    DebugP_assert(config);

    int_fast16_t status;
    AESECB_Handle handle      = config;
    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    /* Initialize and boot HSM */
    if (HSMLPF3_init() != HSMLPF3_STATUS_SUCCESS)
    {
        /* Upon HSM Boot failure, the AES-CCM Driver stores the failure status in the object
         * This is done so that users of the AES-CCM Driver do not get a NULL handle and still can use
         * the driver in LAES mode.
         */
        object->hsmStatus = HSMLPF3_STATUS_ERROR;
    }
    else
    {
        object->hsmStatus = HSMLPF3_STATUS_SUCCESS;
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

    status = AESCommonLPF3_construct(&object->common, (AES_ReturnBehavior)params->returnBehavior, params->timeout);

    if (status != AES_STATUS_SUCCESS)
    {
        return NULL;
    }

    return handle;
}

/*
 *  ======== AESECB_close ========
 */
void AESECB_close(AESECB_Handle handle)
{
    DebugP_assert(handle);

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);

    AESCommonLPF3_close(&object->common);
}

/*
 *  ======== AESECB_oneStepEncrypt ========
 */
int_fast16_t AESECB_oneStepEncrypt(AESECB_Handle handle, AESECB_Operation *operation)
{
    int_fast16_t status = AESECB_STATUS_SUCCESS;

    if (operation->key->encoding == CryptoKey_PLAINTEXT || operation->key->encoding == CryptoKey_KEYSTORE)
    {
        status = AESECBLPF3_oneStepOperation(handle, operation, AESECB_OPERATION_TYPE_ENCRYPT);
    }
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    else if (operation->key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        status = AESECBLPF3HSM_oneStepOperation(handle, operation, AESECB_OPERATION_TYPE_ENCRYPT);
    }
#endif
    else
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
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    else if (operation->key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        status = AESECBLPF3HSM_oneStepOperation(handle, operation, AESECB_OPERATION_TYPE_DECRYPT);
    }
#endif
    else
    {
        status = AESECB_STATUS_ERROR;
    }

    return status;
}

/*
 *  ======== AESECBLPF3_checkOperation ========
 */
static int_fast16_t AESECBLPF3_checkOperation(const AESECBLPF3_Object *object, const AESECB_Operation *operation)
{
#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
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
        !AESCommonLPF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESECB_STATUS_ERROR;
    }

    return AESECB_STATUS_SUCCESS;
}

/*
 *  ======== AESECBLPF3_oneStepOperation ========
 */
static inline int_fast16_t AESECBLPF3_oneStepOperation(AESECB_Handle handle,
                                                       AESECB_Operation *operation,
                                                       AESECB_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);
    int_fast16_t status;

    status = AESECBLPF3_checkOperation(object, operation);

    if (status != AESECB_STATUS_SUCCESS)
    {
        return status;
    }

    /*
     * Check that there are no operations already in progress.
     * If not, mark the current operation to be in progress
     */
    status = AESCommonLPF3_setOperationInProgress(&object->common);

    if (status != AESECB_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
        {
            AESCommonLPF3_clearOperationInProgress(&object->common);
            return AESECB_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation     = operation;
    object->operationType = operationType;

    object->common.key          = *(operation->key);
    /* We will only change the returnStatus if there is an error or cancellation */
    object->common.returnStatus = AESECB_STATUS_SUCCESS;

    return AESECBLPF3_startOperation(handle, operation);
}

/*
 *  ======== AESECBLPF3_startOperation ========
 */
static int_fast16_t AESECBLPF3_startOperation(AESECB_Handle handle, AESECB_Operation *operation)
{
    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);
    int_fast16_t status;

    /* Set up the key and AES engine to begin an operation */
    if (operation->inputLength == AES_BLOCK_SIZE)
    {
        AESCommonLPF3_setupOperation(&object->common.key, AESEBCLPF3_SINGLE_BLOCK_AUTOCFG);
    }
    else
    {
        AESCommonLPF3_setupOperation(&object->common.key, AESECBLPF3_DEFAULT_AUTOCFG);
    }

    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        (operation->inputLength >= AESECBLPF3_DMA_SIZE_THRESHOLD))
    {
        /*
         * We need to set the HWI function and priority since the same physical
         * interrupt is shared by multiple drivers and they all need to coexist.
         * Whenever a driver starts an operation, it registers its HWI callback
         * with the OS.
         */
        AESECBLPF3_HWAttrs const *hwAttrs = handle->hwAttrs;
        AESCommonLPF3_setupHwi(AESECBLPF3_hwiFxn, (uintptr_t)handle, hwAttrs->intPriority);
    }

    AESECBLPF3_processData(&object->common, operation->input, operation->output, operation->inputLength);

    status = AESECBLPF3_waitForResult(handle);

    return status;
}

/*
 *  ======== AESECBLPF3_processData ========
 */
void AESECBLPF3_processData(AESCommonLPF3_Object *object, const uint8_t *input, uint8_t *output, size_t inputLength)
{
    /*
     * Process all operations with data length less than the DMA size
     * threshold as a polling mode operation.
     */
    if ((object->returnBehavior == AES_RETURN_BEHAVIOR_POLLING) || (inputLength < AESECBLPF3_DMA_SIZE_THRESHOLD))
    {
        /* Process all blocks with CPU R/W */
        AESECBLPF3_processDataCPU(input, output, inputLength);
    }
    else
    {
        AESECBLPF3_processDataDMA(object, input, output, inputLength);
    }
}

/*
 *  ======== AESECBLPF3_processDataCPU ========
 */
static inline void AESECBLPF3_processDataCPU(const uint8_t *input, uint8_t *output, size_t inputLength)
{
    /*
     * For efficiency, the next block of data can be written to AES BUF regs
     * while the AES engine is encrypting the previous block. The AES engine
     * takes 23-cycles to encrypt a block. If the SW can load blocks faster
     * than that, SW must wait until the AES HW is idle after writing two
     * blocks consecutively to avoid overwriting data before the AES engine
     * can consume it.
     */
#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
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
#endif /* (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 1) */
    {
        AESProcessAlignedBlocksECB((const uint32_t *)input,
                                   (uint32_t *)output,
                                   (uint32_t)AES_GET_NUM_BLOCKS(inputLength));
    }
}

/*
 *  ======== AESECBLPF3_processDataDMA ========
 */
static inline void AESECBLPF3_processDataDMA(AESCommonLPF3_Object *object,
                                             const uint8_t *input,
                                             uint8_t *output,
                                             size_t inputLength)
{
    /* Clear BUSHALT when using DMA */
    AESClearAUTOCFGBusHalt();

    /* Setup DMA configuration and set power constraint */
    AESCommonLPF3_setupDMA(object, AESECBLPF3_DMA_CONFIG);

    AESCommonLPF3_configInputDMA(input, inputLength);
    AESCommonLPF3_configOutputDMA(output, inputLength);

    /* Enable interrupt upon output DMA done */
    AESSetIMASK((uint32_t)AES_IMASK_CHBDONE_M);

    /* Manually trigger the DMA to start the ECB operation */
    AESSetTrigger((uint32_t)AES_TRG_DMACHA);
}

/*
 *  ======== AESECBLPF3_waitForResult ========
 */
static inline int_fast16_t AESECBLPF3_waitForResult(AESECB_Handle handle)
{
    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);
    int_fast16_t status;

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (object->operation->inputLength < AESECBLPF3_DMA_SIZE_THRESHOLD))
    {
        /*
         * Save the returnStatus prior clearing operationInProgress or
         * releasing the access semaphore in case it's overwritten.
         */
        status = object->common.returnStatus;

        /* Mark that the current single-step or multi-step operation is done */
        if (object->operationType != AESECB_OPERATION_TYPE_ENCRYPT_SEGMENTED)
        {
            AESCommonLPF3_clearOperationInProgress(&object->common);
        }

        AESCommonLPF3_cleanup(&object->common);

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
        (void)SemaphoreP_pend((SemaphoreP_Handle)&CryptoResourceLPF3_operationSemaphore,
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

/*
 *  ======== AESECB_setupEncrypt ========
 */
int_fast16_t AESECB_setupEncrypt(AESECB_Handle handle, const CryptoKey *key)
{
    DebugP_assert(handle);
    int_fast16_t status       = AESECB_STATUS_SUCCESS;
    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);

    /*
     * Key material pointer and length are not checked until adding or
     * finalizing data.
     */
    if (key->encoding == CryptoKey_PLAINTEXT)
    {
        /* When using the AES driver with the LAES engine */
        status = AESCommonLPF3_setupSegmentedOperation(&object->common, key);
    }
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    else if (key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        if (object->hsmStatus != HSMLPF3_STATUS_SUCCESS)
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
#endif
    else
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

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);
    int_fast16_t status       = AESECB_STATUS_SUCCESS;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    if (key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
        if (object->hsmStatus != HSMLPF3_STATUS_SUCCESS)
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

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);
    int_fast16_t status;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    if (operation->key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        return AESECBLPF3HSM_addData(handle, operation);
    }
#endif

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

    status = AESECBLPF3_checkOperation(object, operation);

    if (status != AESECB_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->threadSafe)
    {
        if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
        {
            return AESECB_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->common.cryptoResourceLocked = true;
    }

    object->operation = operation;

    return AESECBLPF3_startOperation(handle, operation);
}

/*
 *  ======== AESECB_finalize ========
 */
int_fast16_t AESECB_finalize(AESECB_Handle handle, AESECB_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);
    int_fast16_t status;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    if (operation->key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        return AESECBLPF3HSM_finalize(handle, operation);
    }
#endif

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
#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
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
            !AESCommonLPF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
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
            if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
            {
                return AESECB_STATUS_RESOURCE_UNAVAILABLE;
            }

            object->common.cryptoResourceLocked = true;
        }

        object->operationType = operationType;
        object->operation     = operation;

        status = AESECBLPF3_startOperation(handle, operation);
    }
    else /* Operation was finalized without additional data to process */
    {
        status = object->common.returnStatus;

        AESCommonLPF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, operation, operationType);

            /* Always return success in callback mode */
            status = AESECB_STATUS_SUCCESS;
        }
    }

    return status;
}

/*
 *  ======== AESECB_cancelOperation ========
 */
int_fast16_t AESECB_cancelOperation(AESECB_Handle handle)
{
    DebugP_assert(handle);

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);

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
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    if (((object->common.key.encoding & CRYPTOKEY_HSM) == 0) && (!object->common.operationInProgress))
#else
    if (!object->common.operationInProgress)
#endif
    {
        HwiP_restore(interruptKey);
        return AESECB_STATUS_SUCCESS;
    }

    HwiP_restore(interruptKey);

    /*
     * Cancel DMA for input and output channels, clear operation in-progress,
     * and releases crypto resource if necessary.
     */
    AESCommonLPF3_cancelOperation(&object->common, true);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    if ((object->common.key.encoding & CRYPTOKEY_HSM))
    {
        /* Since the HSM cannot cancel an in-progress token, we must wait for the result to allow for
         * subsequent token submissions to succeed.
         */
        (void)HSMLPF3_cancelOperation();

        object->segmentedOperationInProgress = false;
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

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)

/*
 *  ======== AESECBLPF3HSM_oneStepOperation ========
 */
static int_fast16_t AESECBLPF3HSM_oneStepOperation(AESECB_Handle handle,
                                                   AESECB_Operation *operation,
                                                   AESECB_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMLPF3_STATUS_SUCCESS)
    {
        return HSMLPF3_STATUS_ERROR;
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

    return AESECBLPF3HSM_processOneStep(handle);
}

/*
 *  ======== AESECBLPF3HSM_OneStepPostProcessing ========
 */
static inline void AESECBLPF3HSM_OneStepPostProcessing(uintptr_t arg0)
{
    AESECB_Handle handle      = (AESECB_Handle)arg0;
    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);
    int_fast16_t status       = AESECB_STATUS_ERROR;
    int32_t physicalResult    = HSMLPF3_getResultCode();
    int32_t tokenResult       = physicalResult & HSMLPF3_RETVAL_MASK;

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = AESECB_STATUS_SUCCESS;
    }

    object->common.returnStatus = status;

    HSMLPF3_releaseLock();

    Power_releaseConstraint(PowerLPF3_DISALLOW_STANDBY);

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

static int_fast16_t AESECBLPF3HSM_processOneStep(AESECB_Handle handle)
{
    int_fast16_t status       = AESECB_STATUS_ERROR;
    int_fast16_t hsmRetval    = HSMLPF3_STATUS_ERROR;
    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);

    if (!HSMLPF3_acquireLock(SemaphoreP_NO_WAIT, (uintptr_t)handle))
    {
        return AESECB_STATUS_RESOURCE_UNAVAILABLE;
    }

    Power_setConstraint(PowerLPF3_DISALLOW_STANDBY);

    HSMLPF3_constructAESECBOneStepPhysicalToken(object);

    hsmRetval = HSMLPF3_submitToken((HSMLPF3_ReturnBehavior)object->common.returnBehavior,
                                    AESECBLPF3HSM_OneStepPostProcessing,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMLPF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMLPF3_waitForResult();

        if (hsmRetval == HSMLPF3_STATUS_SUCCESS)
        {
            status = object->common.returnStatus;
        }
    }

    if (hsmRetval != HSMLPF3_STATUS_SUCCESS)
    {
        Power_releaseConstraint(PowerLPF3_DISALLOW_STANDBY);

        HSMLPF3_releaseLock();
    }

    return status;
}

static int_fast16_t AESECBLPF3HSM_addData(AESECB_Handle handle, AESECB_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMLPF3_STATUS_SUCCESS)
    {
        return AESECB_STATUS_ERROR;
    }

    /*
     * Assert the segmented operation was setup.
     * LPF3 only supports ECB encryption.
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

    return AESECBLPF3HSM_processOneStep(handle);
}

static int_fast16_t AESECBLPF3HSM_finalize(AESECB_Handle handle, AESECB_Operation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESECBLPF3_Object *object = AESEBCLPF3_getObject(handle);
    int_fast16_t status;

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMLPF3_STATUS_SUCCESS)
    {
        return AESECB_STATUS_ERROR;
    }

    /*
     * Assert the segmented operation was setup.
     * LPF3 only supports ECB encryption.
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

        status = AESECBLPF3HSM_processOneStep(handle);
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
