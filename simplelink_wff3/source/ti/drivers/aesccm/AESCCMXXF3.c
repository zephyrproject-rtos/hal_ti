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

#include <ti/drivers/aesccm/AESCCMXXF3.h>
#include <ti/drivers/AESCCM.h>
#include <ti/drivers/aescmac/AESCMACXXF3.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/aesctr/AESCTRXXF3.h>
#include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceXXF3.h>
#include <ti/drivers/cryptoutils/utils/CryptoUtils.h>
#include <ti/devices/DeviceFamily.h>

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>

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
/* Using LPF3 driver implementation for WFF3, since the HSM IP is the same. */
    #if (ENABLE_KEY_STORAGE == 1)
        /* These includes must come before hsmddk/include/Integration/Adapter_PSA includes */
        #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
        #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
    #endif
    #include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        #include <ti/drivers/xmem/XMEMWFF3.h>
        #include <ti/drivers/utils/Math.h>
    #endif
    #include <ti/drivers/cryptoutils/hsm/HSMXXF3Utility.h>
    #include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#endif

#if (defined(__IAR_SYSTEMS_ICC__) || defined(__TI_COMPILER_VERSION__))
    #include <arm_acle.h>
    #define REV32 __rev
#else
    #define REV32 __builtin_bswap32
#endif

/* Note: The AES-CCM one-step polling operations are specifically designed
 * to optimize execution speed at the expense of code re-use and size.
 */

#define B0_FLAGS_CCM_HAS_ADATA 0x40 /* bit 6 in the Flags field of B0 */

/**
 * This AES CCM implementation limits AAD length to 0xFEFF (65279-bytes) to
 * simplify the code and improve execution speed.
 */
/* 0xFEFF bytes, For 0 < l(a) <= (2^16 - 2^8) - 1 */
#define B1_AAD_LENGTH_SMALL_LIMIT ((1UL << 16) - (1UL << 8) - 1UL)

#define B1_AAD_LENGTH_SMALL_BYTES 2U /* If 0 < l(a) < (2^16 - 2^8), the length field is encoded as two octets */
#define B1_AAD_SMALL_BYTES        (AES_BLOCK_SIZE - B1_AAD_LENGTH_SMALL_BYTES)

/**
 * The threshold at which blocking and callback mode transfers will utilize DMA.
 * For data lengths below this threshold, polling CPU R/W will be used instead
 * of DMA. With task switching and interrupt overhead, it is inefficient to
 * utilize DMA for shorter length operations.
 * The threshold value must be a multiple of AES_BLOCK_SIZE.
 */
#define AESCCMXXF3_DMA_SIZE_THRESHOLD (1U * AES_BLOCK_SIZE)

/* Forward declarations */
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
static int_fast16_t AESCCMXXF3_addData(AESCCM_Handle handle,
                                       AESCCM_OperationType operationType,
                                       AESCCM_OperationUnion *operation,
                                       const uint8_t *input,
                                       uint8_t *output,
                                       size_t inputLength);
static int_fast16_t AESCCMXXF3_addDataDMA(AESCCM_Handle handle, AESCCM_Mode direction, size_t inputLength);
static inline int_fast16_t AESCCMXXF3_finishTag(AESCCMXXF3_Object *object, AESCCM_Mode direction);
static int_fast16_t AESCCMXXF3_oneStepOperation(AESCCM_Handle handle,
                                                AESCCM_OneStepOperation *operation,
                                                AESCCM_OperationType operationType);
static int_fast16_t AESCCMXXF3_performFinalizeChecks(const AESCCMXXF3_Object *object,
                                                     const AESCCM_SegmentedFinalizeOperation *operation);
static void AESCCMXXF3_processB0(const uint8_t *nonce,
                                 uint8_t nonceLength,
                                 size_t totalAADLength,
                                 size_t totalDataLength,
                                 uint8_t macLength);
static size_t AESCCMXXF3_processB1withAAD(const uint8_t *aad, size_t aadSegmentLength, size_t aadTotalLength);
static void AESCCMXXF3_processOneStepCBCMACPolling(AESCCM_OneStepOperation *operation,
                                                   uint32_t tag[AES_TAG_LENGTH_BYTES / 4U],
                                                   AESCCM_Mode direction);
static void AESCCMXXF3_processOneStepCTRPolling(AESCCM_OneStepOperation *operation,
                                                uint32_t tag[AES_TAG_LENGTH_BYTES / 4U]);
static inline int_fast16_t AESCCMXXF3_processOneStepDecryptPolling(AESCCMXXF3_Object *object,
                                                                   AESCCM_OneStepOperation *operation);
static inline int_fast16_t AESCCMXXF3_processOneStepEncryptPolling(AESCCMXXF3_Object *object,
                                                                   AESCCM_OneStepOperation *operation);
static int_fast16_t AESCCMXXF3_setupSegmentedOperation(AESCCMXXF3_Object *object,
                                                       const CryptoKey *key,
                                                       size_t totalAADLength,
                                                       size_t totalDataLength,
                                                       size_t macLength);
static void AESCCMXXF3_processCBCMACFinalBlock(const uint8_t *input, size_t bytesRemaining);
static void AESCCMXXF3_processCTRCounterBlock(const uint8_t *nonce, uint8_t nonceLength, uint8_t counterVal);
static int_fast16_t AESCCMXXF3_processSegmentedCBCMAC(AESCCMXXF3_Object *object,
                                                      size_t aadSegmentLength,
                                                      size_t dataSegmentLength,
                                                      AESCCM_Mode direction);
static int_fast16_t AESCCMXXF3_processSegmentedCTR(AESCCMXXF3_Object *object, size_t dataSegmentLength);
static void AESCCMXXF3_processTagCTR(AESCCMXXF3_Object *object);
static int_fast16_t AESCCMXXF3_waitForDMA(const AESCCMXXF3_Object *object);
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    #if (ENABLE_KEY_STORAGE == 1)
static int_fast16_t AESCCMXXF3HSM_getKeyMaterial(AESCCMXXF3_Object *object);
    #endif
static void AESCCMXXF3HSM_setupObjectMetaData(AESCCMXXF3_Object *object);
static int_fast16_t AESCCMXXF3HSM_oneStepOperation(AESCCM_Handle handle,
                                                   AESCCM_OneStepOperation *operation,
                                                   AESCCM_OperationType operationType);
static int_fast16_t AESCCMXXF3HSM_oneStepOperationInternal(AESCCM_Handle handle,
                                                           AESCCM_OneStepOperation *operation,
                                                           AESCCM_OperationType operationType);
static int_fast16_t AESCCMXXF3HSM_performHSMOperation(AESCCM_Handle handle);
static void AESCCMXXF3HSM_postProcessingCommon(AESCCM_Handle handle, int_fast16_t status, int8_t tokenResult);
static int_fast16_t AESCCMXXF3HSM_setupSegmentedOperation(AESCCM_Handle handle,
                                                          AESCCM_OperationType operationType,
                                                          const CryptoKey *key,
                                                          size_t totalAADLength,
                                                          size_t totalDataLength,
                                                          size_t macLength);
static int_fast16_t AESCCMXXF3HSM_setupEncrypt(AESCCM_Handle handle,
                                               const CryptoKey *key,
                                               size_t totalAADLength,
                                               size_t totalPlaintextLength,
                                               size_t macLength);
static int_fast16_t AESCCMXXF3HSM_setupDecrypt(AESCCM_Handle handle,
                                               const CryptoKey *key,
                                               size_t totalAADLength,
                                               size_t totalPlaintextLength,
                                               size_t macLength);
static int_fast16_t AESCCMXXF3HSM_addAAD(AESCCM_Handle handle, AESCCM_SegmentedAADOperation *operation);
static int_fast16_t AESCCMXXF3HSM_addData(AESCCM_Handle handle,
                                          AESCCM_OperationType operationType,
                                          AESCCM_OperationUnion *operation);
static int_fast16_t AESCCMXXF3HSM_performFinalizeChecks(const AESCCMXXF3_Object *object,
                                                        const AESCCM_SegmentedFinalizeOperation *operation);
static int_fast16_t AESCCMXXF3HSM_finalizeCommon(AESCCM_Handle handle,
                                                 AESCCM_OperationType operationType,
                                                 AESCCM_SegmentedFinalizeOperation *operation);
static int_fast16_t AESCCMXXF3HSM_finalizeEncrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation);
static int_fast16_t AESCCMXXF3HSM_finalizeDecrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation);

static int_fast16_t AESCCMXXF3HSM_createTempAssetID(AESCCM_Handle handle);
static int_fast16_t AESCCMXXF3HSM_freeAllAssets(AESCCM_Handle handle);
static int_fast16_t AESCCMXXF3HSM_freeTempAssetID(AESCCM_Handle handle);
#endif
/*
 *  ======== AESCCMXXF3_getObject ========
 */
static inline AESCCMXXF3_Object *AESCCMXXF3_getObject(AESCCM_Handle handle)
{
    AESCCMXXF3_Object *object = (AESCCMXXF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCCMXXF3_hwiFxn ========
 *
 * Note: In order to support callback return behavior, there is an undesireable
 * amount of processing done within this ISR. If support for callback return
 * behavior can be removed in the future, this processing should be moved to
 * the thread context to improve IRQ responsiveness.
 */
static void AESCCMXXF3_hwiFxn(uintptr_t arg0)
{
    bool isOpDone             = false;
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    /* For CBC-MAC, only the input channel A interrupt is enabled.
     * For CTR, only the output channel B interrupt is enabled.
     */
    uint32_t intStatus = AESGetMaskedInterruptStatus();

    /* Disable DMA, clear interupts, and release power constraint */
    AESCommonXXF3_cleanupHwi(&object->common);

    AESCCM_Mode direction = AESCCM_MODE_ENCRYPT;

    if ((object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        direction = AESCCM_MODE_DECRYPT;
    }

    if ((intStatus & (uint32_t)AES_MIS_CHADONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonXXF3_DMA_CHA_BITMASK);

        const uint8_t *plainText = object->input;
        if (direction == AESCCM_MODE_DECRYPT)
        {
            plainText = object->output;
        }

        /* DMA is used to process full blocks of data but there if there is a
         * partial block of data remaining, handle it with CPU R/W.
         */
        if (object->inputCBCMACLengthRemaining > 0U)
        {
            size_t inputCBCMACLengthRemaining = object->inputCBCMACLengthRemaining;
            /* Use CPU R/W to complete the CBC-MAC operation */
            AESCCMXXF3_processCBCMACFinalBlock(&plainText[object->inputLength - inputCBCMACLengthRemaining],
                                               inputCBCMACLengthRemaining);

            object->totalCBCMACLengthRemaining -= inputCBCMACLengthRemaining;
            object->inputCBCMACLengthRemaining = 0U;
        }

        /* Wait for operation to complete and save the intermediate tag */
        AESCMACXXF3_readTag((uint32_t *)&object->intermediateTag[0]);

        if (object->totalCBCMACLengthRemaining == 0U)
        {
            object->common.returnStatus = AESCCMXXF3_finishTag(object, direction);
        }

        if (direction == AESCCM_MODE_DECRYPT)
        {
            isOpDone = true;
        }
        else /* Encrypt */
        {
            object->common.returnStatus = AESCCMXXF3_processSegmentedCTR(object, object->inputLength);

            /* Operation will be handled without DMA if length less than threshold */
            if (object->inputLength < AESCCMXXF3_DMA_SIZE_THRESHOLD)
            {
                isOpDone = true;
            }
        }
    }

    if ((intStatus & (uint32_t)AES_MIS_CHBDONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonXXF3_DMA_CHB_BITMASK);

        /* DMA is used to process all full blocks of data. If there is a
         * partial block of data remaining, process it with CPU R/W.
         */
        if (object->inputCTRLengthRemaining > 0U)
        {
            size_t inputCTRLengthRemaining = object->inputCTRLengthRemaining;
            /* Use CPU R/W to complete the CTR operation */
            AESCTRXXF3_processData(&object->input[object->inputLength - inputCTRLengthRemaining],
                                   &object->output[object->inputLength - inputCTRLengthRemaining],
                                   inputCTRLengthRemaining,
                                   true);

            object->totalCTRLengthRemaining -= inputCTRLengthRemaining;
            object->inputCTRLengthRemaining = 0U;
        }

        if (object->totalCTRLengthRemaining > 0U)
        {
            /* Store the counter if more input data is expected */
            AESCTRXXF3_readCounter((uint32_t *)&object->intermediateCounter[0]);
        }

        if (direction == AESCCM_MODE_ENCRYPT)
        {
            isOpDone = true;
        }
        else /* Decrypt */
        {
            object->common.returnStatus = AESCCMXXF3_processSegmentedCBCMAC(object,
                                                                            0U,
                                                                            object->inputLength,
                                                                            AESCCM_MODE_DECRYPT);

            /* Operation is completed without DMA if length < threshold */
            if (object->inputLength < AESCCMXXF3_DMA_SIZE_THRESHOLD)
            {
                isOpDone = true;
            }
        }
    }

    if (isOpDone)
    {
        /* Store sum of AES lengths in a temporary variable to explicitly
         * define access order since both fields are volatile.
         */
        size_t totalLengthRemaining = object->totalCTRLengthRemaining;
        totalLengthRemaining += object->totalCBCMACLengthRemaining;

        if (totalLengthRemaining == 0U)
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

/*
 *  ======== AESCCMXXF3_finishTag ========
 */
static inline int_fast16_t AESCCMXXF3_finishTag(AESCCMXXF3_Object *object, AESCCM_Mode direction)
{
    int_fast16_t status = AESCCM_STATUS_SUCCESS;

    AESCCMXXF3_processTagCTR(object);

    if (object->mac != NULL)
    {
        if (direction == AESCCM_MODE_ENCRYPT)
        {
            (void)memcpy((void *)&object->mac[0], (void *)&object->intermediateTag[0], object->macLength);
        }
        else /* Decrypt */
        {
            /* Perform a constant time comparison of the calculated MAC and the decrypted MAC */
            bool macValid = CryptoUtils_buffersMatch(object->intermediateTag, object->mac, (size_t)object->macLength);

            if (!macValid)
            {
                status = AESCCM_STATUS_MAC_INVALID;
            }
        }
    }

    return status;
}

/*
 *  ======== AESCCMXXF3_waitForDMA ========
 */
static int_fast16_t AESCCMXXF3_waitForDMA(const AESCCMXXF3_Object *object)
{
    int_fast16_t status;

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_BLOCKING)
    {
        /* This function may be called from handler or thread contexts.
         * Only block on semaphore when called from thread context
         * (i.e. Interrupt Program Status Register is zero)
         */
        if ((uint32_t)__get_IPSR() == (uint32_t)0U)
        {
            /* Ignore return value since timeout is infinite */
            (void)SemaphoreP_pend((SemaphoreP_Handle)&CryptoResourceXXF3_operationSemaphore,
                                  (uint32_t)SemaphoreP_WAIT_FOREVER);
        }

        /* Return status stored in ISR */
        status = object->common.returnStatus;
    }
    else /* AES_RETURN_BEHAVIOR_CALLBACK */
    {
        /* Success is always returned in callback mode */
        status = AESCCM_STATUS_SUCCESS;
    }

    return status;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCCM_init ========
 */
void AESCCM_init(void)
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
 *  ======== AESCCM_construct ========
 */
AESCCM_Handle AESCCM_construct(AESCCM_Config *config, const AESCCM_Params *params)
{
    DebugP_assert(config);

    AESCCM_Handle handle      = config;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Callback return mode is not supported for CC35XX for now */
    if ((params != NULL) && (params->returnBehavior == AESCCM_RETURN_BEHAVIOR_CALLBACK))
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

        object->segmentedOperationInProgress = false;
    }
#endif

    /* If params are NULL, use defaults */
    if (params == NULL)
    {
        params = &AESCCM_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AESCCM_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->callbackFxn = params->callbackFxn;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Set common parameters for later use. */
    object->common.isOpen = true;

    object->common.returnBehavior = (AES_ReturnBehavior)params->returnBehavior;

    if (params->returnBehavior == AESCCM_RETURN_BEHAVIOR_BLOCKING)
    {
        object->common.semaphoreTimeout = params->timeout;
    }
    else
    {
        object->common.semaphoreTimeout = SemaphoreP_NO_WAIT;
    }
#else
    int_fast16_t status;
    status = AESCommonXXF3_construct(&object->common, (AES_ReturnBehavior)params->returnBehavior, params->timeout);

    if (status != AES_STATUS_SUCCESS)
    {
        handle = NULL;
    }
#endif

    return handle;
}

/*
 *  ======== AESCCM_close ========
 */
void AESCCM_close(AESCCM_Handle handle)
{
    DebugP_assert(handle);

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCommonXXF3_close(&object->common);
#else
    /* Mark the module as available */
    object->common.isOpen = false;
#endif
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCCMXXF3_processCBCMACFinalBlock ========
 */
static void AESCCMXXF3_processCBCMACFinalBlock(const uint8_t *input, size_t bytesRemaining)
{
    /* No need to reload the last intermediate tag because it still loaded in
     * the AES engine from the previous CBCMAC operation.
     */

    /* Must wait until engine is idle before clearing BUF */
    while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}

    /* When the CPU pushes data in a cipher mode that has the WRBUF3
     * configuration set during initialization code, the engine shows IDLE state
     * for one clock cycle before starting the next operation. If the state is
     * sampled at this exact moment and then issue clear, the engine is already
     * processing - so the clear operation gets ignored. To prevent this race,
     * poll idle twice in a row to confirm the engine truly halted before
     * proceeding with the clear.
     */
    while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}

    /* Clear the WRBUF3 configuration and do a manual trigger instead since it
     * is unknown how many bytes will be copied to the BUF register.
     * Store the current configuration to restore it later.
     */
    uint32_t autoCfg = HWREG(AES_BASE + AES_O_AUTOCFG);
    AESSetAUTOCFG(autoCfg & ~AES_AUTOCFG_TRGAES_M);

    /* Zero out the BUF registers */
    AESClearBUF();

    /* Copy directly to BUF registers. (void)memcpy is safe to use here since
     * the order of the writes is not important when writing a partial block.
     */
    (void)memcpy((void *)(AES_BASE + AES_O_BUF0), input, bytesRemaining);

    AESSetTrigger((uint32_t)AES_TRG_AESOP_TXTXBUF);

    /* Restore the configuration */
    AESSetAUTOCFG(autoCfg);
}

    #define M_PRIME_OFFSET 3

    /*
     *  ======== AESCCMXXF3_processB0 ========
     */
    #if defined(__IAR_SYSTEMS_ICC__)
        #pragma inline = forced
    #elif defined(__TI_COMPILER_VERSION__)
        #pragma FUNC_ALWAYS_INLINE(AESCCMXXF3_processB0)
    #else
__attribute__((always_inline)) inline
    #endif
static void AESCCMXXF3_processB0(const uint8_t *nonce,
                                 uint8_t nonceLength,
                                 size_t totalAADLength,
                                 size_t totalDataLength,
                                 uint8_t macLength)
{
    AES_BlockWordAligned B0;

    /* ============================================
     * First block B0 formatting per RFC3610:
     *    Octet Number   Contents
     *    ------------   ---------
     *    0              Flags
     *    1 ... 15-L     Nonce N
     *    16-L ... 15    l(m)
     *
     * Flags in octet 0 of B0:
     *    Bit Number   Contents
     *    ----------   ----------------------
     *    7            Reserved (always zero)
     *    6            Adata
     *    5 ... 3      M'
     *    2 ... 0      L'
     * ============================================
     */

    /* Set L'
     *   nonceLength = 15 - L
     *   L' = L - 1
     *   L' = 15 - nonceLength - 1
     *   L' = 14 - nonceLength
     */
    B0.words[0] = (uint32_t)14U - (uint32_t)nonceLength;

    /* Set M'
     *   M' = (M - 2) / 2 where M = length of MAC
     */
    B0.words[0] |= (((uint32_t)macLength - (uint32_t)2U) >> 1) << M_PRIME_OFFSET;

    if (totalAADLength != 0U)
    {
        /* Set bit 6 (Adata) */
        B0.words[0] |= (uint32_t)B0_FLAGS_CCM_HAS_ADATA;
    }

    /* Set l(m), the length of the message, in most-significant-byte first order.
     *
     * Do this before copying nonce so word-based write can be utilized and then
     * nonce's byte-wise copy will overwrite parts of the word not used for l(m).
     */
    B0.words[3] = REV32(totalDataLength);

    /* Copy nonce into B0, clearing bytes first to ensure uncopied bytes are zero. */
    B0.words[1] = (uint32_t)0U;
    B0.words[2] = (uint32_t)0U;

    (void)memcpy(&B0.bytes[1], nonce, nonceLength);

    AESWriteBUF32(B0.words);
}

/*
 *  ======== AESCCMXXF3_processB1withAAD ========
 */
static size_t AESCCMXXF3_processB1withAAD(const uint8_t *aad, size_t aadSegmentLength, size_t aadTotalLength)
{
    size_t aadBytesProcessed = aadSegmentLength;
    AES_BlockWordAligned B1;

    B1.words[0] = (uint32_t)0U;
    B1.words[1] = (uint32_t)0U;
    B1.words[2] = (uint32_t)0U;
    B1.words[3] = (uint32_t)0U;

    /* Per RFC3610: If 0 < l(a) < (2^16 - 2^8), then the length field
     * is encoded as two octets which contain the value l(a) in
     * most-significant-byte first order.
     *
     * Note: Accessing via byte ptr is 5-cycles faster than using bit shift
     * and masking.
     */
    uint8_t *aadLengthBytePtr = (uint8_t *)&aadTotalLength;
    B1.bytes[1]               = *(aadLengthBytePtr);
    B1.bytes[0]               = *(aadLengthBytePtr + 1U);

    /* Append the remaining AAD bytes */
    if (aadSegmentLength == 1U)
    {
        /* Optimization for BLE stack use case which has 1-byte AAD */
        B1.bytes[2] = aad[0];
    }
    else if (aadSegmentLength <= B1_AAD_SMALL_BYTES)
    {
        (void)memcpy((void *)&B1.bytes[2], (void *)aad, aadSegmentLength);
    }
    else
    {
        (void)memcpy((void *)&B1.bytes[2], (void *)aad, B1_AAD_SMALL_BYTES);
        aadBytesProcessed = B1_AAD_SMALL_BYTES;
    }

    /* B1 can be written to BUF while AES engine is still processing B0 */
    AESWriteBUF32(B1.words);

    return aadBytesProcessed;
}

/*
 *  ======== AESCCMXXF3_processCBCMACPolling ========
 */
static void AESCCMXXF3_processOneStepCBCMACPolling(AESCCM_OneStepOperation *operation,
                                                   uint32_t tag[AES_TAG_LENGTH_BYTES / 4U],
                                                   AESCCM_Mode direction)
{
    size_t dataBytesRemaining;
    size_t aadBytesRemaining;

    AESSetAUTOCFG(AESCMACXXF3_DEFAULT_AUTOCFG);

    /* Set IV to zero */
    AESClearIV();

    AESCCMXXF3_processB0(operation->nonce,
                         operation->nonceLength,
                         operation->aadLength,
                         operation->inputLength,
                         operation->macLength);

    /* Process AAD */
    if (operation->aadLength > 0U)
    {
        aadBytesRemaining = operation->aadLength;

        /* Process B1 with AAD */
        aadBytesRemaining -= AESCCMXXF3_processB1withAAD(operation->aad, operation->aadLength, operation->aadLength);

        /* Process any remaining AAD */
        if (aadBytesRemaining > 0U)
        {
            size_t blockSizeAlignedAADLength = AES_BLOCK_SIZE_MULTIPLE_LENGTH(aadBytesRemaining);

            if (blockSizeAlignedAADLength > 0U)
            {
                AESCMACXXF3_processBlocks(&operation->aad[operation->aadLength - aadBytesRemaining],
                                          blockSizeAlignedAADLength);

                aadBytesRemaining -= blockSizeAlignedAADLength;
            }

            if (aadBytesRemaining > 0U)
            {
                AESCCMXXF3_processCBCMACFinalBlock(&operation->aad[operation->aadLength - aadBytesRemaining],
                                                   aadBytesRemaining);
            }
        }
    }

    dataBytesRemaining = operation->inputLength;

    if (dataBytesRemaining > 0U)
    {
        /* Perform CBCMAC on plaintext data, that is, depending on encryption/decryption,
         * use input/output data respectively.
         */

        uint8_t *plainText = operation->input;
        if (direction != AESCCM_MODE_ENCRYPT)
        {
            plainText = operation->output;
        }

        size_t blockSizeAlignedDataRemaining = AES_BLOCK_SIZE_MULTIPLE_LENGTH(dataBytesRemaining);

        if (blockSizeAlignedDataRemaining > 0U)
        {
            AESCMACXXF3_processBlocks(plainText, blockSizeAlignedDataRemaining);

            dataBytesRemaining -= blockSizeAlignedDataRemaining;
        }

        if (dataBytesRemaining > 0U)
        {
            AESCCMXXF3_processCBCMACFinalBlock(&plainText[operation->inputLength - dataBytesRemaining],
                                               dataBytesRemaining);
        }
    }

    /* Wait for operation to complete and save the intermediate tag */
    AESCMACXXF3_readTag(&tag[0]);
}

/*
 *  ======== AESCCMXXF3_processOneStepCTRPolling ========
 */
static void AESCCMXXF3_processOneStepCTRPolling(AESCCM_OneStepOperation *operation,
                                                uint32_t tag[AES_TAG_LENGTH_BYTES / 4U])
{
    /* Init Counter Mode */
    if (operation->inputLength == 0U)
    {
        AESSetAUTOCFG(AESCTRXXF3_LAST_BLOCK_AUTOCFG);
    }
    else
    {
        AESSetAUTOCFG(AESCTRXXF3_DEFAULT_AUTOCFG);
    }

    /* Process counter block with counter value of 0 */
    AESCCMXXF3_processCTRCounterBlock(operation->nonce, operation->nonceLength, (uint8_t)0U);

    /* =====================
     * Process Tag
     * =====================
     */

    /* XOR tag with encrypted counter block to form ciphertext */
    AESWriteTXTXOR32(tag);

    /* Read the tag ciphertext and trigger the encryption of the next counter block */
    AESReadTag32(tag);

    if (operation->inputLength > 0U)
    {
        /* ==================
         * Process input data
         * ==================
         */
        AESCTRXXF3_processData(operation->input, operation->output, operation->inputLength, true);
    }
}

/*
 *  ======== AESCCMXXF3_processOneStepEncryptPolling ========
 */
static inline int_fast16_t AESCCMXXF3_processOneStepEncryptPolling(AESCCMXXF3_Object *object,
                                                                   AESCCM_OneStepOperation *operation)
{
    /* Calculate the MAC for the AAD and message */
    AESCCMXXF3_processOneStepCBCMACPolling(operation, (uint32_t *)&object->intermediateTag[0], AESCCM_MODE_ENCRYPT);

    /* Encrypt the MAC and the message */
    AESCCMXXF3_processOneStepCTRPolling(operation, (uint32_t *)&object->intermediateTag[0]);

    (void)memcpy((void *)&operation->mac[0], (void *)&object->intermediateTag[0], operation->macLength);

    /* This operation is always successful */
    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCMXXF3_processOneStepDecryptPolling ========
 */
static inline int_fast16_t AESCCMXXF3_processOneStepDecryptPolling(AESCCMXXF3_Object *object,
                                                                   AESCCM_OneStepOperation *operation)
{
    bool macValid;
    int_fast16_t status = AESCCM_STATUS_MAC_INVALID;
    uint32_t *mac;

    /* Use the object's intermediateCounter field which is only used for
     * segmented operations to store the MAC to save stack space.
     */
    mac = (uint32_t *)&object->intermediateCounter[0];

    /* Create a word-aligned copy of the MAC */
    (void)memcpy((void *)mac, (void *)operation->mac, operation->macLength);

    /* Decrypt the MAC and the message */
    AESCCMXXF3_processOneStepCTRPolling(operation, mac);

    /* Calculate the MAC on the decrypted message and AAD */
    AESCCMXXF3_processOneStepCBCMACPolling(operation, (uint32_t *)&object->intermediateTag[0], AESCCM_MODE_DECRYPT);

    /* Perform a constant time comparision of the calculated MAC and the decrypted MAC */
    macValid = CryptoUtils_buffersMatch(object->intermediateTag, mac, (size_t)operation->macLength);

    if (macValid)
    {
        status = AESCCM_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== AESCCMXXF3_oneStepOperation ========
 */
static int_fast16_t AESCCMXXF3_oneStepOperation(AESCCM_Handle handle,
                                                AESCCM_OneStepOperation *operation,
                                                AESCCM_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    /* Internally generated nonces aren't supported for now */
    DebugP_assert(!operation->nonceInternallyGenerated);
    DebugP_assert(operation->nonce && (operation->nonceLength >= 7U) && (operation->nonceLength <= 13U));
    DebugP_assert((operation->aad && (operation->aadLength > 0U)) ||
                  (operation->input && (operation->inputLength > 0U)));
    DebugP_assert(operation->mac && (operation->macLength <= 16U));
    /* Implementation only supports aadLength to 65,279 bytes */
    DebugP_assert(operation->aadLength <= B1_AAD_LENGTH_SMALL_LIMIT)

        bool dmaActive        = false;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status;
    #if (ENABLE_KEY_STORAGE == 1)
    KeyStore_PSA_KeyUsage usage = (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ? KEYSTORE_PSA_KEY_USAGE_ENCRYPT
                                                                                    : KEYSTORE_PSA_KEY_USAGE_DECRYPT;
    #endif

    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCCM_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
    #endif

    /* The nonce length must be 7 to 13 bytes long */
    if ((operation->nonceLength < (uint8_t)7U) || (operation->nonceLength > (uint8_t)13U))
    {
        return AESCCM_STATUS_ERROR;
    }

    /* The combined length of AAD and payload data must be non-zero. */
    if ((operation->aadLength + operation->inputLength) == 0U)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Check if there is no operation already in progress for this driver
     * instance, and then mark the current operation to be in progress.
     */
    status = AESCommonXXF3_setOperationInProgress(&object->common);

    if (status != AES_STATUS_SUCCESS)
    {
        return status;
    }

    if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
    {
        AESCommonXXF3_clearOperationInProgress(&object->common);
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    object->common.cryptoResourceLocked = true;
    object->common.returnStatus         = AESCCM_STATUS_SUCCESS;

    if (operation->key->encoding == CryptoKey_PLAINTEXT)
    {
        AESCommonXXF3_loadKey(operation->key);
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (operation->key->encoding == CryptoKey_KEYSTORE)
    {
        /* AES engine supports only 128-bit (16-byte) keys. */
        DebugP_assert(operation->key->u.keyStore.keyLength == AES_128_KEY_LENGTH_BYTES);

        /* When loading a key blob, the asset ID will be set to non-zero value */
        status = AESCommonXXF3_loadKeyFromKeyStore(operation->key, &object->keyAssetID, KEYSTORE_PSA_ALG_CCM, usage);

        if (status != AES_STATUS_SUCCESS)
        {
            AESCommonXXF3_clearOperationInProgress(&object->common);

            object->common.cryptoResourceLocked = false;

            CryptoResourceXXF3_releaseLock();

            return status;
        }
    }
    #endif
    else
    {
        return AESCCM_STATUS_FEATURE_NOT_SUPPORTED;
    }

    /* Process all one-step operations with data length less than the DMA size
     * threshold as a polling mode operation.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (operation->inputLength < AESCCMXXF3_DMA_SIZE_THRESHOLD))
    {
        if (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT)
        {
            status = AESCCMXXF3_processOneStepEncryptPolling(object, operation);
        }
        else /* operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT */
        {
            status = AESCCMXXF3_processOneStepDecryptPolling(object, operation);
        }
    }
    else
    {
        object->operation     = (AESCCM_OperationUnion *)operation;
        object->operationType = operationType;

        /* Copy data pointers */
        object->input  = operation->input;
        object->output = operation->output;
        object->mac    = operation->mac;
        object->aad    = operation->aad;
        object->nonce  = operation->nonce;

        /* Copy length info */
        object->nonceLength                = operation->nonceLength;
        object->totalAADLength             = operation->aadLength;
        object->totalDataLength            = operation->inputLength;
        object->totalCBCMACLengthRemaining = operation->inputLength;
        object->totalCTRLengthRemaining    = operation->inputLength;
        object->macLength                  = operation->macLength;

        /* Init AAD processing vars */
        object->aadBytesProcessed = 0U;
        object->bufferedAADLength = (uint8_t)0U;

        AESCCM_Mode direction = AESCCM_MODE_ENCRYPT;

        if (operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT)
        {
            direction = AESCCM_MODE_DECRYPT;
        }

        if ((operation->aadLength > 0U) && (status == AESCCM_STATUS_SUCCESS))
        {
            /* Process the entire AAD using CPU R/W. It is expected that
             * the AAD length is relatively short (<= 64-bytes). Therefore,
             * using DMA is inefficient after DMA setup, task switching,
             * and interrupt overhead are accounted for.
             */
            status = AESCCMXXF3_processSegmentedCBCMAC(object, operation->aadLength, 0, direction);
        }

        if ((operation->inputLength > 0U) && (status == AESCCM_STATUS_SUCCESS))
        {
            /* Process Data with DMA */
            status    = AESCCMXXF3_addDataDMA(handle, direction, operation->inputLength);
            dmaActive = true;
        }
    }

    if (!dmaActive)
    {
        AESCommonXXF3_clearOperationInProgress(&object->common);

        /* Cleanup and release crypto resource lock */
        AESCommonXXF3_cleanup(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, operationType);

            /* Always return success in callback mode */
            status = AESCCM_STATUS_SUCCESS;
        }
    }

    return status;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCCM_oneStepEncrypt ========
 */
int_fast16_t AESCCM_oneStepEncrypt(AESCCM_Handle handle, AESCCM_OneStepOperation *operation)
{
    int_fast16_t status = AESCCM_STATUS_SUCCESS;

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if ((operation->key->encoding == CryptoKey_PLAINTEXT) || (operation->key->encoding == CryptoKey_KEYSTORE))
    {
        status = AESCCMXXF3_oneStepOperation(handle, operation, AESCCM_OP_TYPE_ONESTEP_ENCRYPT);
    }
    else
#endif
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        if ((operation->key->encoding == CryptoKey_PLAINTEXT_HSM) ||
            (operation->key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        status = AESCCMXXF3HSM_oneStepOperation(handle, operation, AESCCM_OP_TYPE_ONESTEP_ENCRYPT);
    }
    else
#endif
    {
        status = AESCCM_STATUS_ERROR;
    }
    return status;
}

/*
 *  ======== AESCCM_oneStepDecrypt ========
 */
int_fast16_t AESCCM_oneStepDecrypt(AESCCM_Handle handle, AESCCM_OneStepOperation *operation)
{
    int_fast16_t status = AESCCM_STATUS_SUCCESS;

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if ((operation->key->encoding == CryptoKey_PLAINTEXT) || (operation->key->encoding == CryptoKey_KEYSTORE))
    {
        status = AESCCMXXF3_oneStepOperation(handle, operation, AESCCM_OP_TYPE_ONESTEP_DECRYPT);
    }
    else
#endif
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        if ((operation->key->encoding == CryptoKey_PLAINTEXT_HSM) ||
            (operation->key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        status = AESCCMXXF3HSM_oneStepOperation(handle, operation, AESCCM_OP_TYPE_ONESTEP_DECRYPT);
    }
    else
#endif
    {
        status = AESCCM_STATUS_ERROR;
    }
    return status;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCCMXXF3_setupSegmentedOperation ========
 */
static int_fast16_t AESCCMXXF3_setupSegmentedOperation(AESCCMXXF3_Object *object,
                                                       const CryptoKey *key,
                                                       size_t totalAADLength,
                                                       size_t totalDataLength,
                                                       size_t macLength)
{
    DebugP_assert(key);

    int_fast16_t status = AESCommonXXF3_setupSegmentedOperation(&object->common, key);

    if (status == AES_STATUS_SUCCESS)
    {
        /* If the user doesn't provide the total lengths in the setupXXXX()
         * calls, they must provide the lengths in setLengths().
         */
        object->totalAADLength  = totalAADLength;
        object->totalDataLength = totalDataLength;
        object->macLength       = (uint8_t)macLength;

        object->totalCTRLengthRemaining    = totalDataLength;
        object->totalCBCMACLengthRemaining = totalDataLength;
        object->aadBytesProcessed          = 0U;
        object->bufferedAADLength          = (uint8_t)0U;

        /* Initialize MAC pointer to NULL to avoid premature processing of the
         * MAC in the ISR.
         */
        object->mac = NULL;

        /* Initialize operation pointer to NULL in case AESCCM_cancelOperation
         * is called after AESCCM_setupXXXX and callback should be skipped.
         */
        object->operation = NULL;
    }

    return status;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCCM_setupEncrypt ========
 */
int_fast16_t AESCCM_setupEncrypt(AESCCM_Handle handle,
                                 const CryptoKey *key,
                                 size_t totalAADLength,
                                 size_t totalPlaintextLength,
                                 size_t macLength)
{
    DebugP_assert(handle);
    int_fast16_t status = AES_STATUS_FEATURE_NOT_SUPPORTED;

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if ((key->encoding == CryptoKey_PLAINTEXT_HSM) || (key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        return AESCCMXXF3HSM_setupEncrypt(handle, key, totalAADLength, totalPlaintextLength, macLength);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    status = AESCCMXXF3_setupSegmentedOperation(object, key, totalAADLength, totalPlaintextLength, macLength);
    if (status == AES_STATUS_SUCCESS)
    {
        object->operationType = AESCCM_OPERATION_TYPE_ENCRYPT;
    }
#endif

    return status;
}

/*
 *  ======== AESCCM_setupDecrypt ========
 */
int_fast16_t AESCCM_setupDecrypt(AESCCM_Handle handle,
                                 const CryptoKey *key,
                                 size_t totalAADLength,
                                 size_t totalPlaintextLength,
                                 size_t macLength)
{
    DebugP_assert(handle);

    int_fast16_t status = AES_STATUS_FEATURE_NOT_SUPPORTED;

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if ((key->encoding == CryptoKey_PLAINTEXT_HSM) || (key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        return AESCCMXXF3HSM_setupDecrypt(handle, key, totalAADLength, totalPlaintextLength, macLength);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    status = AESCCMXXF3_setupSegmentedOperation(object, key, totalAADLength, totalPlaintextLength, macLength);
    if (status == AESCCM_STATUS_SUCCESS)
    {
        object->operationType = AESCCM_OPERATION_TYPE_DECRYPT;
    }
#endif

    return status;
}

/*
 *  ======== AESCCM_setLengths ========
 */
int_fast16_t AESCCM_setLengths(AESCCM_Handle handle, size_t aadLength, size_t plaintextLength, size_t macLength)
{
    DebugP_assert(handle);

    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    /* This shouldn't be called after addXXX() or finalizeXXX() */
    DebugP_assert(object->operationType == AESCCM_OPERATION_TYPE_DECRYPT ||
                  object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT);

    /* Don't continue the segmented operation if there
     * was an error or a cancellation
     */
    if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    /* The combined length of AAD and payload data must be non-zero. */
    if ((aadLength == 0U) && (plaintextLength == 0U))
    {
        return AESCCM_STATUS_ERROR;
    }

    object->totalAADLength             = aadLength;
    object->totalDataLength            = plaintextLength;
    object->totalCBCMACLengthRemaining = plaintextLength;
    object->totalCTRLengthRemaining    = plaintextLength;
    object->macLength                  = (uint8_t)macLength;

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    object->aadBytesProcessed        = 0U;
    object->bufferedAADLength        = 0U;
    object->totalAADLengthRemaining  = aadLength;
    object->totalDataLengthRemaining = plaintextLength;

    if ((object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT) && (macLength == 0U))
    {
        /* We are not supplied the macLength at this point of the segmented operation.
         * Therefore, the driver gives it a dummy length which is the max length until
         * the user supplies the desired macLength in _setLengths() API.
         */
        object->macLength = HSM_MAC_MAX_LENGTH;
    }

    if (((aadLength > AES_BLOCK_SIZE) || (plaintextLength > AES_BLOCK_SIZE)) && (object->tempAssetID == 0U))
    {
        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
        {
            return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
        }

        status = AESCCMXXF3HSM_createTempAssetID(handle);

        HSMXXF3_releaseLock();
    }
#endif

    return status;
}

/*
 *  ======== AESCCM_setNonce ========
 */
int_fast16_t AESCCM_setNonce(AESCCM_Handle handle, const uint8_t *nonce, size_t nonceLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    /* This function cannot be called after addXXX() or finalizeXXX() */
    DebugP_assert((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error during setup.
     */
    if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    /* The nonce length must be 7 to 13 bytes long */
    if ((nonceLength < 7U) || (nonceLength > 13U))
    {
        return AESCCM_STATUS_ERROR;
    }

    object->nonce       = nonce;
    object->nonceLength = (uint8_t)nonceLength;

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCM_generateNonce ========
 */
int_fast16_t AESCCM_generateNonce(AESCCM_Handle handle, uint8_t *nonce, size_t nonceSize, size_t *nonceLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);
    DebugP_assert(nonceSize > 0U);
    DebugP_assert(nonceLength);

    /* This feature is not currently supported */
    return AESCCM_STATUS_FEATURE_NOT_SUPPORTED;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCCMXXF3_processSegmentedCBCMAC ========
 */
static int_fast16_t AESCCMXXF3_processSegmentedCBCMAC(AESCCMXXF3_Object *object,
                                                      size_t aadSegmentLength,
                                                      size_t dataSegmentLength,
                                                      AESCCM_Mode direction)
{
    bool dmaActive            = false;
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    size_t aadBytesRemaining  = 0U;
    size_t dataBytesRemaining = 0U;

    AESSetAUTOCFG(AESCMACXXF3_DEFAULT_AUTOCFG);

    /* Process B0 block if no AAD and no data has been proceeded yet */
    if ((object->aadBytesProcessed == 0U) && (object->totalCBCMACLengthRemaining == object->totalDataLength))
    {
        /* Set IV to zero */
        AESClearIV();

        AESCCMXXF3_processB0(object->nonce,
                             object->nonceLength,
                             object->totalAADLength,
                             object->totalDataLength,
                             object->macLength);
    }
    else
    {
        /* Restore intermediate tag */
        AESWriteTag32((uint32_t *)&object->intermediateTag[0]);
    }

    /* ===========
     * Process AAD
     * ===========
     */
    if (aadSegmentLength > 0U)
    {
        aadBytesRemaining = aadSegmentLength;

        if (object->aadBytesProcessed == 0U)
        {
            /* Process B1 with AAD */
            object->aadBytesProcessed = AESCCMXXF3_processB1withAAD(object->aad,
                                                                    aadSegmentLength,
                                                                    object->totalAADLength);
            aadBytesRemaining -= object->aadBytesProcessed;
        }

        /* Process any remaining AAD */
        if (aadBytesRemaining > 0U)
        {
            /* Check for any buffered AAD from the previous transaction.
             * Due to the AAD length parameter restrictions on AESCCM_addAAD(),
             * there always must be two bytes of buffered AAD if non-zero.
             */
            if (object->bufferedAADLength > (uint8_t)0U)
            {
                AES_BlockWordAligned aadBlock;

                aadBlock.words[0] = (uint32_t)0U;
                aadBlock.words[1] = (uint32_t)0U;
                aadBlock.words[2] = (uint32_t)0U;
                aadBlock.words[3] = (uint32_t)0U;

                /* Copy buffered AAD into the local AAD block */
                aadBlock.bytes[0] = object->bufferedAAD[0];
                aadBlock.bytes[1] = object->bufferedAAD[1];

                size_t aadBlockBytesAvail = (AES_BLOCK_SIZE - AESCCMXXF3_AAD_BUFFER_SIZE);
                const uint8_t *newAAD     = &object->aad[aadSegmentLength - aadBytesRemaining];

                /* Copy the new AAD into the local AAD block */
                if (aadBytesRemaining >= aadBlockBytesAvail)
                {
                    (void)memcpy((void *)&aadBlock.bytes[AESCCMXXF3_AAD_BUFFER_SIZE],
                                 (void *)newAAD,
                                 aadBlockBytesAvail);

                    object->aadBytesProcessed += AES_BLOCK_SIZE;
                    aadBytesRemaining -= aadBlockBytesAvail;
                }
                else
                {
                    (void)memcpy((void *)&aadBlock.bytes[AESCCMXXF3_AAD_BUFFER_SIZE],
                                 (void *)newAAD,
                                 aadBytesRemaining);

                    object->aadBytesProcessed += (aadBytesRemaining + AESCCMXXF3_AAD_BUFFER_SIZE);
                    aadBytesRemaining = 0U;
                }

                AESCMACXXF3_processBlocks(aadBlock.bytes, sizeof(aadBlock));

                object->bufferedAADLength = (uint8_t)0U;
            }

            size_t blockSizeAlignedAADLength = AES_BLOCK_SIZE_MULTIPLE_LENGTH(aadBytesRemaining);

            if (blockSizeAlignedAADLength > 0U)
            {
                AESCMACXXF3_processBlocks(&object->aad[aadSegmentLength - aadBytesRemaining],
                                          blockSizeAlignedAADLength);

                object->aadBytesProcessed += blockSizeAlignedAADLength;
                aadBytesRemaining -= blockSizeAlignedAADLength;
            }

            if (aadBytesRemaining > 0U)
            {
                if ((object->aadBytesProcessed + aadBytesRemaining) == object->totalAADLength)
                {
                    AESCCMXXF3_processCBCMACFinalBlock(&object->aad[aadSegmentLength - aadBytesRemaining],
                                                       aadBytesRemaining);
                    object->aadBytesProcessed += aadBytesRemaining;
                }
                else if (aadBytesRemaining == AESCCMXXF3_AAD_BUFFER_SIZE)
                {
                    /* Save leftover AAD bytes to process later */
                    const uint8_t *aadRemaining = &object->aad[aadSegmentLength - AESCCMXXF3_AAD_BUFFER_SIZE];
                    object->bufferedAAD[0]      = *aadRemaining;
                    object->bufferedAAD[1]      = *(aadRemaining + 1U);
                    object->bufferedAADLength   = (uint8_t)AESCCMXXF3_AAD_BUFFER_SIZE;
                }
                else
                {
                    /* This should never happen if API restrictions on AAD length are followed */
                    AESAbort();
                    return AESCCM_STATUS_ERROR;
                }
            }
        }
    }

    /* ============
     * Process Data
     * ============
     */
    if (dataSegmentLength > 0U)
    {
        dataBytesRemaining = dataSegmentLength;

        /* Perform CBC-MAC on plaintext data:
         *  - For encryption, plaintext data points to object's input.
         *  - For decryption, plaintext data points to object's output.
         */
        const uint8_t *plainText = object->input;
        if (direction == AESCCM_MODE_DECRYPT)
        {
            plainText = object->output;
        }

        size_t blockSizeAlignedDataRemaining = AES_BLOCK_SIZE_MULTIPLE_LENGTH(dataBytesRemaining);

        if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
            (blockSizeAlignedDataRemaining < AESCCMXXF3_DMA_SIZE_THRESHOLD))
        {
            /* Process all the full blocks of data */
            if (blockSizeAlignedDataRemaining > 0U)
            {
                AESCMACXXF3_processBlocks(plainText, blockSizeAlignedDataRemaining);

                dataBytesRemaining -= blockSizeAlignedDataRemaining;
            }

            if (dataBytesRemaining > 0U)
            {
                AESCCMXXF3_processCBCMACFinalBlock(&plainText[dataSegmentLength - dataBytesRemaining],
                                                   dataBytesRemaining);
            }

            object->inputCBCMACLengthRemaining -= dataSegmentLength;
            object->totalCBCMACLengthRemaining -= dataSegmentLength;
        }
        else
        {
            /* Clear BUSHALT when using DMA */
            AESClearAUTOCFGBusHalt();

            /* Setup DMA configuration and set power constraint */
            AESCommonXXF3_setupDMA(&object->common, AESCBCMACLPF3_DMA_CONFIG);

            AESCommonXXF3_configInputDMA(plainText, blockSizeAlignedDataRemaining);

            /* Enable interrupt upon input DMA done */
            AESSetIMASK((uint32_t)AES_IMASK_CHADONE_M);

            object->inputCBCMACLengthRemaining -= blockSizeAlignedDataRemaining;
            object->totalCBCMACLengthRemaining -= blockSizeAlignedDataRemaining;

            dmaActive = true;

            /* Manually trigger the DMA to start the CBC-MAC operation */
            AESSetTrigger((uint32_t)AES_TRG_DMACHA);
        }
    }

    if (dmaActive)
    {
        status = AESCCMXXF3_waitForDMA(object);
    }
    else
    {
        /* Wait for operation to complete and save the intermediate tag */
        AESCMACXXF3_readTag((uint32_t *)&object->intermediateTag[0]);
    }

    return status;
}

/*
 *  ======== AESCCMXXF3_processCTRCounterBlock ========
 */
static void AESCCMXXF3_processCTRCounterBlock(const uint8_t *nonce, uint8_t nonceLength, uint8_t counterVal)
{
    /* ============================================
     * Initial flags, nonce, and counter formatting per RFC3610:
     *    Octet Number   Contents
     *    ------------   ---------
     *    0              Flags
     *    1 ... 15-L     Nonce N
     *    16-L ... 15    Counter i (most-significant-byte first)
     *
     * The Flags field is formatted as follows:
     *
     *    Bit Number   Contents
     *    ----------   ----------------------
     *    7            Reserved (always zero)
     *    6            Reserved (always zero)
     *    5 ... 3      Zero
     *    2 ... 0      L'
     *
     *   where L' = 14 - nonceLength
     * ============================================
     */
    AES_BlockWordAligned counter;

    counter.words[0] = (uint32_t)0U;
    counter.words[1] = (uint32_t)0U;
    counter.words[2] = (uint32_t)0U;
    counter.words[3] = (uint32_t)0U;

    counter.bytes[0] = (uint8_t)14U - nonceLength;

    (void)memcpy((void *)&counter.bytes[1], (void *)nonce, nonceLength);

    counter.bytes[15] = counterVal;

    /* Initial write to AES_O_BUF3 triggers the encryption */
    AESCTRXXF3_writeCounter(counter.words);

    /* Wait for encryption of counter block to complete */
    while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}
}

/*
 *  ======== AESCCMXXF3_processTagCTR ========
 */
static void AESCCMXXF3_processTagCTR(AESCCMXXF3_Object *object)
{
    /* Use default CTR config without AES_AUTOCFG_TRGAES_RDTXT3
     * to avoid triggering an encryption of the next counter value
     * when reading out the encrypted tag.
     */
    AESSetAUTOCFG(AESCTRXXF3_LAST_BLOCK_AUTOCFG);

    /* Process counter block with counter value of 0 */
    AESCCMXXF3_processCTRCounterBlock(object->nonce, object->nonceLength, (uint8_t)0U);

    /* XOR tag with encrypted counter block to form ciphertext */
    AESWriteTXTXOR32((uint32_t *)&object->intermediateTag[0]);

    /* Read the tag ciphertext */
    AESReadTag32((uint32_t *)&object->intermediateTag[0]);
}

/*
 *  ======== AESCCMXXF3_processSegmentedCTR ========
 */
static int_fast16_t AESCCMXXF3_processSegmentedCTR(AESCCMXXF3_Object *object, size_t dataSegmentLength)
{
    bool dmaActive      = false;
    bool firstCounter   = false;
    int_fast16_t status = AESCCM_STATUS_SUCCESS;

    if (object->totalCTRLengthRemaining == object->totalDataLength)
    {
        firstCounter = true;
    }

    AESSetAUTOCFG(AESCTRXXF3_DEFAULT_AUTOCFG);

    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        (dataSegmentLength >= AESCCMXXF3_DMA_SIZE_THRESHOLD))
    {
        size_t bytesProcessed;

        bytesProcessed = AESCTRXXF3_configDataDMA(&object->common, object->input, object->output, dataSegmentLength);

        object->totalCTRLengthRemaining -= bytesProcessed;
        object->inputCTRLengthRemaining -= bytesProcessed;

        dmaActive = true;
    }

    /* Writing the counter value will trigger the first encryption */
    if (firstCounter)
    {
        /* Process counter block with initial counter value of 1 */
        AESCCMXXF3_processCTRCounterBlock(object->nonce, object->nonceLength, (uint8_t)1U);
    }
    else
    {
        /* Restore intermediate counter */
        AESCTRXXF3_writeCounter((uint32_t *)&object->intermediateCounter[0]);
    }

    if (dmaActive)
    {
        status = AESCCMXXF3_waitForDMA(object);
    }
    else
    {
        /* Process data with CPU R/W */
        AESCTRXXF3_processData(object->input, object->output, dataSegmentLength, false);

        object->totalCTRLengthRemaining -= dataSegmentLength;

        /* Store the counter */
        AESCTRXXF3_readCounter((uint32_t *)&object->intermediateCounter[0]);
    }

    return status;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCCM_addAAD ========
 */
int_fast16_t AESCCM_addAAD(AESCCM_Handle handle, AESCCM_SegmentedAADOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AES_STATUS_FEATURE_NOT_SUPPORTED;

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if ((object->common.key.encoding == CryptoKey_PLAINTEXT_HSM) ||
        (object->common.key.encoding == CryptoKey_KEYSTORE_HSM))
    {
        return AESCCMXXF3HSM_addAAD(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    #if (ENABLE_KEY_STORAGE == 1)
    KeyStore_PSA_KeyUsage usage;
    #endif

    object->operation = (AESCCM_OperationUnion *)operation;

    /* Don't continue the segmented operation if there
     * was an error or a cancellation.
     */
    if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    /* This operation can be called after setup or after addAAD again. */
    DebugP_assert((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT));

    size_t calcAADLen = object->aadBytesProcessed + (size_t)object->bufferedAADLength + operation->aadLength;

    /* The input length must be a non-zero multiple of an AES block size
     * unless you are dealing with the last chunk of AAD.
     */
    if ((operation->aadLength == 0U) ||
        ((AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->aadLength) > 0U) && (calcAADLen != object->totalAADLength)))
    {
        return AESCCM_STATUS_ERROR;
    }

    /* The total AAD input length must not exceed the total length specified
     * in AESCCM_setLengths() or the setupXXXX() call.
     */
    if (calcAADLen > object->totalAADLength)
    {
        return AESCCM_STATUS_ERROR;
    }

    AESCCM_Mode direction              = AESCCM_MODE_ENCRYPT;
    AESCCM_OperationType operationType = AESCCM_OP_TYPE_AAD_ENCRYPT;

    if ((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT))
    {
        direction     = AESCCM_MODE_DECRYPT;
        operationType = AESCCM_OP_TYPE_AAD_DECRYPT;
    }

    if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    object->common.cryptoResourceLocked = true;

    /* Load only the key into the AES engine now. The AUTOCFG values are loaded as needed
     * depending on whether it's a CTR operation or a CBC-MAC operation.
     */
    if (object->common.key.encoding == CryptoKey_PLAINTEXT)
    {
        AESCommonXXF3_loadKey(&object->common.key);
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (object->common.key.encoding == CryptoKey_KEYSTORE)
    {
        /* AES engine supports only 128-bit (16-byte) keys. */
        DebugP_assert(object->common.key.u.keyStore.keyLength == AES_128_KEY_LENGTH_BYTES);

        usage = (direction == AESCCM_MODE_ENCRYPT) ? KEYSTORE_PSA_KEY_USAGE_ENCRYPT : KEYSTORE_PSA_KEY_USAGE_DECRYPT;

        status = AESCommonXXF3_loadKeyFromKeyStore(&object->common.key,
                                                   &object->keyAssetID,
                                                   KEYSTORE_PSA_ALG_CCM,
                                                   usage);

        if (status != AES_STATUS_SUCCESS)
        {
            AESCommonXXF3_clearOperationInProgress(&object->common);

            object->common.cryptoResourceLocked = false;

            CryptoResourceXXF3_releaseLock();

            return status;
        }
    }
    #endif
    else
    {
        return AESCCM_STATUS_FEATURE_NOT_SUPPORTED;
    }

    object->operationType = operationType;
    object->aad           = operation->aad;

    /* AAD is expected to be relatively short in length (< a few AES blocks)
     * so DMA is not utilized for blocking and callback modes because the
     * interrupt and task switching overhead would outweigh any CPU cycles
     * saved using DMA. Code size and complexity is reduced by not supporting
     * DMA for AAD.
     */

    status = AESCCMXXF3_processSegmentedCBCMAC(object, operation->aadLength, 0, direction);

    if ((status == AESCCM_STATUS_SUCCESS) && (object->totalDataLength == 0U) &&
        (object->aadBytesProcessed == object->totalAADLength))
    {
        AESCCMXXF3_processTagCTR(object);
    }

    /* Cleanup and release crypto resource lock */
    AESCommonXXF3_cleanup(&object->common);

    object->common.returnStatus = status;

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, operationType);

        /* Always return success in callback mode */
        status = AESCCM_STATUS_SUCCESS;
    }
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCCMXXF3_addDataDMA ========
 */
static int_fast16_t AESCCMXXF3_addDataDMA(AESCCM_Handle handle, AESCCM_Mode direction, size_t inputLength)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status;

    object->inputLength                = inputLength;
    object->inputCBCMACLengthRemaining = inputLength;

    object->inputLength             = inputLength;
    object->inputCTRLengthRemaining = inputLength;

    /* We need to set the HWI function and priority since the same physical
     * interrupt is shared by multiple drivers and they all need to coexist.
     * Whenever a driver starts an operation, it registers its HWI callback
     * with the OS.
     */
    AESCCMXXF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    AESCommonXXF3_setupHwi(AESCCMXXF3_hwiFxn, (uintptr_t)handle, hwAttrs->intPriority);

    if (direction == AESCCM_MODE_ENCRYPT)
    {
        status = AESCCMXXF3_processSegmentedCBCMAC(object, 0U, inputLength, AESCCM_MODE_ENCRYPT);
    }
    else
    {
        status = AESCCMXXF3_processSegmentedCTR(object, inputLength);
    }

    return status;
}

/*
 *  ======== AESCCMXXF3_addData ========
 */
static int_fast16_t AESCCMXXF3_addData(AESCCM_Handle handle,
                                       AESCCM_OperationType operationType,
                                       AESCCM_OperationUnion *operation,
                                       const uint8_t *input,
                                       uint8_t *output,
                                       size_t inputLength)
{
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    #if (ENABLE_KEY_STORAGE == 1)
    KeyStore_PSA_KeyUsage usage;

    if ((operationType == AESCCM_OP_TYPE_DATA_ENCRYPT) || (operationType == AESCCM_OP_TYPE_FINALIZE_ENCRYPT))
    {
        usage = KEYSTORE_PSA_KEY_USAGE_ENCRYPT;
    }
    else
    {
        /* (operationType == AESCCM_OP_TYPE_DATA_DECRYPT) ||
         * (operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT)
         */
        usage = KEYSTORE_PSA_KEY_USAGE_DECRYPT;
    }
    #endif

    if (!CryptoResourceXXF3_acquireLock(object->common.semaphoreTimeout))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    object->common.cryptoResourceLocked = true;

    /* Load only the key into the AES engine now. The AUTOCFG values are loaded as needed
     * depending on whether it's a CTR operation or a CBC-MAC operation.
     */
    if (object->common.key.encoding == CryptoKey_PLAINTEXT)
    {
        AESCommonXXF3_loadKey(&object->common.key);
    }
    #if (ENABLE_KEY_STORAGE == 1)
    else if (object->common.key.encoding == CryptoKey_KEYSTORE)
    {
        /* AES engine supports only 128-bit (16-byte) keys. */
        DebugP_assert(object->common.key.u.keyStore.keyLength == AES_128_KEY_LENGTH_BYTES);

        status = AESCommonXXF3_loadKeyFromKeyStore(&object->common.key,
                                                   &object->keyAssetID,
                                                   KEYSTORE_PSA_ALG_CCM,
                                                   usage);

        if (status != AES_STATUS_SUCCESS)
        {
            AESCommonXXF3_clearOperationInProgress(&object->common);

            object->common.cryptoResourceLocked = false;

            CryptoResourceXXF3_releaseLock();

            return status;
        }
    }
    #endif
    else
    {
        return AESCCM_STATUS_FEATURE_NOT_SUPPORTED;
    }

    object->operationType = operationType;
    object->operation     = operation;

    object->input  = input;
    object->output = output;

    AESCCM_Mode direction = AESCCM_MODE_ENCRYPT;

    if ((object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        direction = AESCCM_MODE_DECRYPT;
    }

    /* Process all segmented operations with data length less than the DMA
     * size threshold as a polling mode operation.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) || (inputLength < AESCCMXXF3_DMA_SIZE_THRESHOLD))
    {
        if (direction == AESCCM_MODE_ENCRYPT)
        {
            status = AESCCMXXF3_processSegmentedCBCMAC(object, 0, inputLength, AESCCM_MODE_ENCRYPT);
        }

        if (status == AESCCM_STATUS_SUCCESS)
        {
            status = AESCCMXXF3_processSegmentedCTR(object, inputLength);
        }

        if ((direction == AESCCM_MODE_DECRYPT) && (status == AESCCM_STATUS_SUCCESS))
        {
            status = AESCCMXXF3_processSegmentedCBCMAC(object, 0U, inputLength, AESCCM_MODE_DECRYPT);
        }

        if ((object->totalCBCMACLengthRemaining == 0U) && (status == AESCCM_STATUS_SUCCESS))
        {
            AESCCMXXF3_processTagCTR(object);
        }

        object->common.returnStatus = status;

        /* Cleanup and release crypto resource lock */
        AESCommonXXF3_cleanup(&object->common);
    }
    else
    {
        status = AESCCMXXF3_addDataDMA(handle, direction, inputLength);

        if (status != AESCCM_STATUS_SUCCESS)
        {
            object->common.returnStatus = status;

            /* Cleanup and release crypto resource lock */
            AESCommonXXF3_cleanup(&object->common);
        }
    }

    return status;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCCM_addData ========
 */
int_fast16_t AESCCM_addData(AESCCM_Handle handle, AESCCM_SegmentedDataOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;

    /* This operation can be called after setupXXXX, addAAD, or addData */
    DebugP_assert((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT));

    if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

#if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCCM_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if ((object->common.key.encoding == CryptoKey_PLAINTEXT_HSM) ||
        (object->common.key.encoding == CryptoKey_KEYSTORE_HSM))
    {
        /* The input length must be a non-zero multiple of an AES block size
         * unless you are dealing with the last chunk of payload data
         */
        if ((operation->inputLength == 0U) || ((AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->inputLength) > 0U) &&
                                               (operation->inputLength != object->totalDataLengthRemaining)))
        {
            return AESCCM_STATUS_ERROR;
        }

        /* The total input length must not exceed the lengths specified in
         * AESCCM_setLengths() or setupXXXX().
         */
        if (operation->inputLength > object->totalDataLengthRemaining)
        {
            return AESCCM_STATUS_ERROR;
        }
    }
    else
#endif
    {
        /* The input length must be a non-zero multiple of an AES block size
         * unless you are dealing with the last chunk of payload data
         */
        if ((operation->inputLength == 0U) || ((AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->inputLength) > 0U) &&
                                               (operation->inputLength != object->totalCBCMACLengthRemaining)))
        {
            return AESCCM_STATUS_ERROR;
        }

        /* The total input length must not exceed the lengths specified in
         * AESCCM_setLengths() or setupXXXX().
         */
        if (operation->inputLength > object->totalCBCMACLengthRemaining)
        {
            return AESCCM_STATUS_ERROR;
        }
    }

    /* The AAD input length specified so far must match the total length
     * specified in the setLengths() or setupXXXX() calls.
     * All AAD input must be processed at this point.
     */
    if ((object->aadBytesProcessed != object->totalAADLength)
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
        && ((object->common.key.encoding == CryptoKey_PLAINTEXT) || (object->common.key.encoding == CryptoKey_KEYSTORE))
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        && (object->common.key.encoding == CryptoKey_KEYSTORE)
#endif
    )
    {
        return AESCCM_STATUS_ERROR;
    }

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCCM_STATUS_ERROR;
    }
#endif

    AESCCM_OperationType operationType = AESCCM_OP_TYPE_DATA_ENCRYPT;

    if ((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT) || (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT))
    {
        operationType = AESCCM_OP_TYPE_DATA_DECRYPT;
    }

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    if ((object->common.key.encoding == CryptoKey_PLAINTEXT) || (object->common.key.encoding == CryptoKey_KEYSTORE))
    {
        status = AESCCMXXF3_addData(handle,
                                    operationType,
                                    (AESCCM_OperationUnion *)operation,
                                    operation->input,
                                    operation->output,
                                    operation->inputLength);
    }
    else
#endif
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        if ((object->common.key.encoding == CryptoKey_PLAINTEXT_HSM) ||
            (object->common.key.encoding == CryptoKey_KEYSTORE_HSM))
    {
        status = AESCCMXXF3HSM_addData(handle, operationType, (AESCCM_OperationUnion *)operation);
        return status;
    }
    else
#endif
    {
        status = AESCCM_STATUS_ERROR;
    }

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) &&
        (operation->inputLength < AESCCMXXF3_DMA_SIZE_THRESHOLD))
    {
        object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, operationType);

        /* Always return success in callback mode */
        status = AESCCM_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== AESCCM_finalizeEncrypt ========
 */
int_fast16_t AESCCM_finalizeEncrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AES_STATUS_FEATURE_NOT_SUPPORTED;

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if ((object->common.key.encoding == CryptoKey_PLAINTEXT_HSM) ||
        (object->common.key.encoding == CryptoKey_KEYSTORE_HSM))
    {
        return AESCCMXXF3HSM_finalizeEncrypt(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    status = AESCCMXXF3_performFinalizeChecks(object, operation);

    if (status != AESCCM_STATUS_SUCCESS)
    {
        return status;
    }

    if (operation->inputLength > 0U)
    {
        object->mac       = operation->mac;
        object->macLength = operation->macLength;

        status = AESCCMXXF3_addData(handle,
                                    AESCCM_OP_TYPE_FINALIZE_ENCRYPT,
                                    (AESCCM_OperationUnion *)operation,
                                    operation->input,
                                    operation->output,
                                    operation->inputLength);
    }

    /* If the return behavior is polling or the operation is finalized with
     * input length less than the DMA size threshold (which includes the case
     * of finalizing without any additional data), all data processing will
     * be complete at this point.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (operation->inputLength < AESCCMXXF3_DMA_SIZE_THRESHOLD))
    {
        if (status == AESCCM_STATUS_SUCCESS)
        {
            (void)memcpy(operation->mac, (uint32_t *)&object->intermediateTag[0], operation->macLength);
        }
        else
        {
            object->common.returnStatus = status;
        }

        AESCommonXXF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, AESCCM_OP_TYPE_FINALIZE_ENCRYPT);

            /* Always return success in callback mode */
            status = AESCCM_STATUS_SUCCESS;
        }
    }
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

/*
 *  ======== AESCCM_finalizeDecrypt ========
 */
int_fast16_t AESCCM_finalizeDecrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_FEATURE_NOT_SUPPORTED;

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if ((object->common.key.encoding == CryptoKey_PLAINTEXT_HSM) ||
        (object->common.key.encoding == CryptoKey_KEYSTORE_HSM))
    {
        return AESCCMXXF3HSM_finalizeDecrypt(handle, operation);
    }
#endif

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)

    status = AESCCMXXF3_performFinalizeChecks(object, operation);

    if (status != AESCCM_STATUS_SUCCESS)
    {
        return status;
    }

    if (operation->inputLength > 0U)
    {
        object->mac       = operation->mac;
        object->macLength = operation->macLength;

        status = AESCCMXXF3_addData(handle,
                                    AESCCM_OP_TYPE_FINALIZE_DECRYPT,
                                    (AESCCM_OperationUnion *)operation,
                                    operation->input,
                                    operation->output,
                                    operation->inputLength);
    }

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (operation->inputLength < AESCCMXXF3_DMA_SIZE_THRESHOLD))
    {
        if (status == AESCCM_STATUS_SUCCESS)
        {
            /* Perform a constant time comparision of the calculated MAC and the decrypted MAC */
            bool macValid = CryptoUtils_buffersMatch(object->intermediateTag,
                                                     operation->mac,
                                                     (size_t)operation->macLength);

            if (!macValid)
            {
                status = AESCCM_STATUS_MAC_INVALID;
            }
        }
        else
        {
            object->common.returnStatus = status;
        }

        AESCommonXXF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, AESCCM_OP_TYPE_FINALIZE_DECRYPT);

            /* Always return success in callback mode */
            status = AESCCM_STATUS_SUCCESS;
        }
    }
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

    return status;
}

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/*
 *  ======== AESCCMXXF3_performFinalizeChecks ========
 */
static int_fast16_t AESCCMXXF3_performFinalizeChecks(const AESCCMXXF3_Object *object,
                                                     const AESCCM_SegmentedFinalizeOperation *operation)
{
    /* This operation can be called after setupXXXX, addAAD, or addData */
    DebugP_assert((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error or a cancellation.
     */
    if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCCM_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
    #endif

    /* All AAD should be processed at this point in time. */
    if (object->aadBytesProcessed != object->totalAADLength)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Additional payload data cannot be passed in finalize */
    if (operation->inputLength != object->totalCBCMACLengthRemaining)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonXXF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCCM_STATUS_ERROR;
    }

    return AESCCM_STATUS_SUCCESS;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */

/*
 *  ======== AESCCM_cancelOperation ========
 */
int_fast16_t AESCCM_cancelOperation(AESCCM_Handle handle)
{
    DebugP_assert(handle);

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;

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
#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
    if (((object->common.key.encoding & CRYPTOKEY_HSM) == 0) && (!object->common.operationInProgress))
#else
    if (!object->common.operationInProgress)
#endif
    {
        HwiP_restore(interruptKey);
    }
    else
    {
        HwiP_restore(interruptKey);

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
        /* Cancel DMA for input and output channels, clear operation in-progress,
         * and releases crypto resource if necessary.
         */
        AESCommonXXF3_cancelOperation(&object->common, true);
#endif

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))
        /* Since the HSM cannot cancel an in-progress token, we must wait for the result to allow for
         * subsequent token submissions to succeed.
         */
        (void)HSMXXF3_cancelOperation();

        object->segmentedOperationInProgress = false;

        /* Free all assets. This includes key-related asset and state-related asset (temporary asset). */
        status = AESCCMXXF3HSM_freeAllAssets(handle);
#endif

        /* Operation pointer could be NULL if a segmented operation was setup
         * but neither AESCCM_addData or AESCCM_finalize was called.
         */
        if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
        {
            /* Call the callback function provided by the application */
            object->callbackFxn(handle, AESCCM_STATUS_CANCELED, object->operation, object->operationType);
        }
    }

    (void)memset(object->output, 0, object->totalDataLength);

    object->aad       = NULL;
    object->input     = NULL;
    object->output    = NULL;
    object->nonce     = NULL;
    object->mac       = NULL;
    object->operation = NULL;

    object->inputLength                = 0;
    object->totalCBCMACLengthRemaining = 0;
    object->totalCTRLengthRemaining    = 0;
    object->totalAADLength             = 0;
    object->totalDataLength            = 0;
    object->aadBytesProcessed          = 0;

    object->macLength   = 0;
    object->nonceLength = 0;

    return status;
}

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) || \
     (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1))

/*
 *  ======== AESCCMXXF3HSM_setMac ========
 */
int_fast16_t AESCCMXXF3HSM_setMac(AESCCM_Handle handle, const uint8_t *mac, size_t macLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    /* This function cannot be called after addXXX() or finalizeXXX() */
    DebugP_assert((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error during setup.
     */
    if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    object->mac       = (uint8_t *)mac;
    object->macLength = (uint8_t)macLength;

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCMXXF3HSM_createAssetPostProcessing ========
 */
static inline void AESCCMXXF3HSM_createAssetPostProcessing(uintptr_t arg0)
{
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int8_t tokenResult        = HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK;

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->tempAssetID = HSMXXF3_getResultAssetID();
        status              = AESCCM_STATUS_SUCCESS;
    }

    object->common.returnStatus = status;
}

/*
 *  ======== AESCCMXXF3HSM_createTempAssetID ========
 */
static int_fast16_t AESCCMXXF3HSM_createTempAssetID(AESCCM_Handle handle)
{
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int_fast16_t hsmRetval    = HSMXXF3_STATUS_ERROR;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    uint64_t assetPolicy = HSM_ASSET_POLICY_SYM_AES_AUTH | HSM_ASSET_POLICY_TEMPORARY | HSM_ASSET_POLICY_SYM_MODE_CCM;

    if (object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT)
    {
        assetPolicy |= HSM_ASSET_POLICY_DIR_ENC_GEN;
    }
    else
    {
        assetPolicy |= HSM_ASSET_POLICY_DIR_DEC_VRFY;
    }

    HSMXXF3_constructCreateAssetToken(assetPolicy, HSM_AEAD_TEMP_ASSET_SIZE);

    hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                    AESCCMXXF3HSM_createAssetPostProcessing,
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
 *  ======== AESCCMXXF3HSM_postProcessingCommon ========
 */
static void AESCCMXXF3HSM_postProcessingCommon(AESCCM_Handle handle, int_fast16_t status, int8_t tokenResult)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    if (status == AESCCM_STATUS_SUCCESS)
    {
        if (object->operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT)
        {
            AESCCM_OneStepOperation *operation = (AESCCM_OneStepOperation *)object->operation;

            HSMXXF3_getAESEncryptTag(&operation->mac[0], operation->macLength);
        }
        else if ((object->operationType == AESCCM_OP_TYPE_FINALIZE_ENCRYPT) &&
                 ((object->inputLength != 0U) || (object->aadLength != 0U)))
        {
            AESCCM_SegmentedFinalizeOperation *operation = (AESCCM_SegmentedFinalizeOperation *)object->operation;

            HSMXXF3_getAESEncryptTag(&operation->mac[0], operation->macLength);
        }
        else if (object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT)
        {
            HSMXXF3_getAESEncryptTag((void *)&object->intermediateTag[0], object->macLength);
        }
        else if ((tokenResult == EIP130TOKEN_RESULT_VERIFY_ERROR) &&
                 ((object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT)))
        {
            status = AESCCM_STATUS_MAC_INVALID;
        }
    }

    if ((object->operationType == AESCCM_OP_TYPE_FINALIZE_ENCRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        object->segmentedOperationInProgress = false;
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    /* Free all assets. This includes key-related asset and state-related asset (temporary asset). */
    if (AESCCMXXF3HSM_freeAllAssets(handle) != AESCCM_STATUS_SUCCESS)
    {
        status = AESCCM_STATUS_ERROR;
    }

    object->common.returnStatus = status;

    HSMXXF3_releaseLock();

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
    }
}

/*
 *  ======== AESCCMXXF3HSM_processFinalBlockPostProcessing ========
 */
inline static void AESCCMXXF3HSM_processFinalBlockPostProcessing(uintptr_t arg0)
{
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int32_t physicalResult    = HSMXXF3_getResultCode();
    int8_t tokenResult        = physicalResult & HSMXXF3_RETVAL_MASK;

    /* The HSM IP will throw an error when operation->macLength is zero despite it producing a correct
     * ciphertext/plaintext for both encrypt/decrypt operations and will compute a mac anyways.
     */
    if ((tokenResult == EIP130TOKEN_RESULT_SUCCESS) || ((tokenResult == EIP130TOKEN_RESULT_VERIFY_ERROR) &&
                                                        ((object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT) ||
                                                         (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT) ||
                                                         (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))))
    {
        object->totalDataLengthRemaining -= object->inputLength;

        status = AESCCM_STATUS_SUCCESS;
    }

    if (status == AESCCM_STATUS_SUCCESS)
    {
        uint8_t *output = NULL;

        if ((object->operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ||
            (object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT))
        {
            AESCCM_OneStepOperation *operation = (AESCCM_OneStepOperation *)object->operation;
            output                             = operation->output + (object->totalDataLength - object->inputLength);
        }
        else if ((object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT) ||
                 (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT))
        {
            AESCCM_SegmentedDataOperation *operation = (AESCCM_SegmentedDataOperation *)object->operation;
            output = operation->output + (operation->inputLength - object->inputLength);
        }
        else
        {
            AESCCM_SegmentedFinalizeOperation *operation = (AESCCM_SegmentedFinalizeOperation *)object->operation;
            output = operation->output + (operation->inputLength - object->inputLength);
        }

        (void)memcpy(output, object->outputFinalBlock, object->inputLength);
    }

    AESCCMXXF3HSM_postProcessingCommon(handle, status, tokenResult);
}

/*
 *  ======== AESCCMXXF3HSM_processFinalBlock ========
 */
static int_fast16_t AESCCMXXF3HSM_processFinalBlock(AESCCM_Handle handle)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int_fast16_t hsmRetval    = HSMXXF3_STATUS_ERROR;
    size_t remainderLength    = 0U;
    bool saveIV               = false;
    bool loadIV               = true;

    if ((object->operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_FINALIZE_ENCRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        remainderLength = object->totalDataLengthRemaining;
    }
    else
    {
        AESCCM_SegmentedDataOperation *operation = (AESCCM_SegmentedDataOperation *)object->operation;
        remainderLength                          = operation->inputLength - object->inputLength;
    }

    (void)memset(object->inputFinalBlock, 0, AES_BLOCK_SIZE);
    (void)memcpy(object->inputFinalBlock, object->input + object->inputLength, remainderLength);

    (void)memset(object->outputFinalBlock, 0, AES_BLOCK_SIZE);

    object->input       = object->inputFinalBlock;
    object->output      = object->outputFinalBlock;
    object->inputLength = remainderLength;
    object->aadLength   = 0U;

    HSMXXF3_constructCCMToken(object, saveIV, loadIV); /* only loadIV is true */

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->common.returnBehavior,
                                    AESCCMXXF3HSM_processFinalBlockPostProcessing,
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
 *  ======== AESCCMXXF3HSM_postProcessingFxn ========
 */
static inline void AESCCMXXF3HSM_postProcessingFxn(uintptr_t arg0)
{
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int8_t tokenResult        = HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK;
    bool finalizeOp           = true;

    if ((tokenResult == EIP130TOKEN_RESULT_SUCCESS) || ((tokenResult == EIP130TOKEN_RESULT_VERIFY_ERROR) &&
                                                        ((object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT) ||
                                                         (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT) ||
                                                         (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))))
    {
        object->totalAADLengthRemaining -= object->aadLength;
        object->totalDataLengthRemaining -= object->inputLength;

        status = AESCCM_STATUS_SUCCESS;
    }

    if (status == AESCCM_STATUS_SUCCESS)
    {
        if ((object->operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ||
            (object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT))
        {
            AESCCM_OneStepOperation *operation = (AESCCM_OneStepOperation *)object->operation;

            if (object->totalDataLengthRemaining > 0U)
            {
                status = AESCCMXXF3HSM_processFinalBlock(handle);

                if (status == AESCCM_STATUS_SUCCESS)
                {
                    finalizeOp = false;
                }
            }
            else if (operation->inputLength < AES_BLOCK_SIZE)
            {
                (void)memcpy(operation->output, object->output, operation->inputLength);
            }
        }
        else if ((object->operationType == AESCCM_OP_TYPE_FINALIZE_ENCRYPT) ||
                 (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
        {
            AESCCM_SegmentedFinalizeOperation *operation = (AESCCM_SegmentedFinalizeOperation *)object->operation;

            if (object->totalDataLengthRemaining > 0U)
            {
                status = AESCCMXXF3HSM_processFinalBlock(handle);

                if (status == AESCCM_STATUS_SUCCESS)
                {
                    finalizeOp = false;
                }
            }
            else if (operation->inputLength < AES_BLOCK_SIZE)
            {
                (void)memcpy(operation->output, object->output, operation->inputLength);
            }
        }
        else if ((object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT) ||
                 (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT))
        {
            AESCCM_SegmentedDataOperation *operation = (AESCCM_SegmentedDataOperation *)object->operation;

            if ((!HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE(operation->inputLength)) &&
                (operation->inputLength > AES_BLOCK_SIZE))
            {
                status = AESCCMXXF3HSM_processFinalBlock(handle);

                if (status == AESCCM_STATUS_SUCCESS)
                {
                    finalizeOp = false;
                }
            }
            else if (operation->inputLength < AES_BLOCK_SIZE)
            {
                /* inputLength is not block multiple and therefore is the last data chunk. In this case, copy to use
                 * buffer.
                 */
                (void)memcpy(operation->output, object->output, operation->inputLength);
            }
        }
    }

    if (finalizeOp)
    {
        AESCCMXXF3HSM_postProcessingCommon(handle, status, tokenResult);
    }
}

    #if (ENABLE_KEY_STORAGE == 1)
/*
 *  ======== AESCCMXXF3HSM_getKeyMaterial ========
 */
static int_fast16_t AESCCMXXF3HSM_getKeyMaterial(AESCCMXXF3_Object *object)
{
    int_fast16_t status = AESCCM_STATUS_SUCCESS;

    if (object->common.key.encoding == CryptoKey_KEYSTORE_HSM)
    {
        KeyStore_PSA_KeyFileId keyID;
        KeyStore_PSA_KeyAttributes attributes = KEYSTORE_PSA_KEY_ATTRIBUTES_INIT;
        KeyStore_PSA_KeyUsage usage           = KEYSTORE_PSA_KEY_USAGE_ENCRYPT;
        KeyStore_PSA_KeyLifetime lifetime;
        int_fast16_t keyStoreStatus;

        if ((object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT) ||
            (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT) ||
            (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT) ||
            (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT))
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
            status = AESCCM_STATUS_KEYSTORE_INVALID_ID;
        }
        else if (keyStoreStatus != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            status = AESCCM_STATUS_KEYSTORE_GENERIC_ERROR;
        }
    }

    return status;
}
    #endif

/*
 *  ======== AESCCMXXF3HSM_setupObjectMetaData ========
 */
static void AESCCMXXF3HSM_setupObjectMetaData(AESCCMXXF3_Object *object)
{
    bool saveIV = false;
    bool loadIV = false;

    if ((object->operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT))
    {
        AESCCM_OneStepOperation *operation = (AESCCM_OneStepOperation *)object->operation;

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
    else if ((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) ||
             (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT))
    {
        AESCCM_SegmentedAADOperation *operation = (AESCCM_SegmentedAADOperation *)object->operation;

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
    else if ((object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT) ||
             (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT))
    {
        AESCCM_SegmentedDataOperation *operation = (AESCCM_SegmentedDataOperation *)object->operation;

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
        AESCCM_SegmentedFinalizeOperation *operation = (AESCCM_SegmentedFinalizeOperation *)object->operation;

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

    HSMXXF3_constructCCMToken(object, saveIV, loadIV);
}

/*
 *  ======== AESCCMXXF3HSM_performHSMOperation ========
 */
static int_fast16_t AESCCMXXF3HSM_performHSMOperation(AESCCM_Handle handle)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int_fast16_t hsmRetval    = HSMXXF3_STATUS_ERROR;

    AESCCMXXF3HSM_setupObjectMetaData(object);

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
    if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
    {
        /* In the case of failure to initialize the operation, we need to free all assets allocated.
         * Capturing the return status of this operation is pointless since we are returning an
         * error code anyways.
         */
        (void)AESCCMXXF3HSM_freeTempAssetID(handle);

        HSMXXF3_releaseLock();

        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->common.returnBehavior,
                                    AESCCMXXF3HSM_postProcessingFxn,
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
        (void)AESCCMXXF3HSM_freeTempAssetID(handle);

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== AESCCMXXF3HSM_oneStepOperation ========
 *
 *  On CC35XX, splits the operation into bounce-buffer-sized chunks when AAD or
 *  payload data exceeds the PSRAM bounce slot, then reassembles output and MAC.
 *  Uses the saveIV/loadIV + tempAssetID state mechanism to preserve the CBC-MAC
 *  across chunk boundaries. CALLBACK mode is not supported for chunked operations.
 *  On other targets, delegates directly to oneStepOperationInternal.
 */
static int_fast16_t AESCCMXXF3HSM_oneStepOperation(AESCCM_Handle handle,
                                                   AESCCM_OneStepOperation *operation,
                                                   AESCCM_OperationType operationType)
{
    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    bool aadIsExternal   = (operation->aad != NULL) && XMEMWFF3_isAddrExternal((uintptr_t)operation->aad);
    bool inputIsExternal = (operation->input != NULL) && XMEMWFF3_isAddrExternal((uintptr_t)operation->input);

    /* Block-aligned maximum chunk sizes for each bounce slot. */
    size_t inputBounceSize  = inputIsExternal ? HSMXXF3_inputBounce.size : SIZE_MAX;
    size_t outputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)operation->output) ? HSMXXF3_outputBounce.size
                                                                                    : SIZE_MAX;
    size_t maxPayloadChunk  = Math_MIN(inputBounceSize, outputBounceSize) & ~(AES_BLOCK_SIZE - 1U);
    size_t maxAADChunk      = HSMXXF3_auxBounce.size & ~(AES_BLOCK_SIZE - 1U);

    bool needsPayloadChunking = inputIsExternal && (operation->inputLength > maxPayloadChunk) && (maxPayloadChunk > 0U);
    bool needsAADChunking     = aadIsExternal && (operation->aadLength > maxAADChunk) && (maxAADChunk > 0U);

    if (!needsPayloadChunking && !needsAADChunking)
    {
        /* Single-token path: bounce buffers are large enough for the full operation. */
        return AESCCMXXF3HSM_oneStepOperationInternal(handle, operation, operationType);
    }

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        return AESCCM_STATUS_FEATURE_NOT_SUPPORTED;
    }

    /*
     * Multi-chunk path.  We drive the existing saveIV/loadIV + tempAssetID
     * machinery by temporarily changing operationType and operation pointer
     * for each intermediate submit, then restoring ONE_STEP for the final
     * chunk so postProcessingCommon extracts the MAC correctly.
     *
     * The object fields totalAADLength / totalDataLength never change; only
     * the *Remaining counters move, exactly as they would during a real
     * segmented operation.  setupObjectMetaData reads these to decide
     * saveIV/loadIV, so the HSM sees the correct state machine.
     */

    /* --- Validate and initialise the object, same as oneStepOperationInternal --- */
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    DebugP_assert(!operation->nonceInternallyGenerated);
    DebugP_assert(operation->nonce && (operation->nonceLength >= 7U) && (operation->nonceLength <= 13U));
    DebugP_assert((operation->aad && (operation->aadLength > 0U)) ||
                  (operation->input && (operation->inputLength > 0U)));
    DebugP_assert(operation->mac && (operation->macLength <= 16U));
    DebugP_assert(operation->aadLength <= B1_AAD_LENGTH_SMALL_LIMIT);

    if ((operation->nonceLength < (uint8_t)7U) || (operation->nonceLength > (uint8_t)13U))
    {
        return AESCCM_STATUS_ERROR;
    }
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }
    if ((operation->aadLength + operation->inputLength) == 0U)
    {
        return AESCCM_STATUS_ERROR;
    }
    if (object->segmentedOperationInProgress)
    {
        return AESCCM_STATUS_ERROR;
    }

    object->common.returnStatus = AESCCM_STATUS_SUCCESS;
    object->operation           = (AESCCM_OperationUnion *)operation;
    object->operationType       = operationType;
    object->common.key          = *(operation->key);
    object->input               = operation->input;
    object->output              = operation->output;
    object->mac                 = operation->mac;
    object->aad                 = operation->aad;
    object->nonce               = operation->nonce;
    object->inputLength         = operation->inputLength;
    object->totalDataLength     = operation->inputLength;
    object->macLength           = operation->macLength;
    object->aadLength           = operation->aadLength;
    object->totalAADLength      = operation->aadLength;
    object->nonceLength         = operation->nonceLength;

    object->totalDataLengthRemaining = object->totalDataLength;
    object->totalAADLengthRemaining  = object->totalAADLength;
    object->tempAssetID              = 0U;

    if ((operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) && (operation->macLength == 0U))
    {
        object->macLength = HSM_MAC_MAX_LENGTH;
    }

    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    int_fast16_t status = AESCCM_STATUS_SUCCESS;

    /* A temp asset is always needed when chunking because intermediate chunks
     * use saveIV/loadIV to carry the CBC-MAC state across token boundaries.
     */
    status = AESCCMXXF3HSM_createTempAssetID(handle);

        #if (ENABLE_KEY_STORAGE == 1)
    if (status == AESCCM_STATUS_SUCCESS)
    {
        status = AESCCMXXF3HSM_getKeyMaterial(object);
    }
        #endif

    if (status != AESCCM_STATUS_SUCCESS)
    {
        (void)AESCCMXXF3HSM_freeTempAssetID(handle);
        HSMXXF3_releaseLock();
        return status;
    }

    /* ------------------------------------------------------------------ */
    /* AAD phase: submit AAD in bounce-buffer-sized chunks via raw token  */
    /* submission, using the AAD_ENCRYPT/AAD_DECRYPT operationType so     */
    /* that setupObjectMetaData drives the saveIV/loadIV state machine.   */
    /*                                                                     */
    /* setupObjectMetaData(AAD_ENCRYPT) buffers the last block of each    */
    /* final AAD chunk into aadFinalBlock so that it can be submitted with*/
    /* the following DATA token.  We stop the AAD loop before the last    */
    /* chunk and leave totalAADLengthRemaining non-zero so that the DATA  */
    /* phase picks up the buffered tail.  If there is no payload, we also */
    /* skip the last AAD chunk in this loop and let performHSMOperation   */
    /* submit it as the final ONE_STEP token.                             */
    /* ------------------------------------------------------------------ */
    if (operation->aadLength > 0U)
    {
        AESCCM_SegmentedAADOperation aadOp;
        const uint8_t *aadPtr = operation->aad;
        size_t aadRemaining   = operation->aadLength;

        /* Submit all intermediate AAD chunks that won't fit in the bounce
         * buffer.  Stop when aadRemaining fits, so the last chunk can be
         * deferred to the DATA (or final ONE_STEP) token.
         */
        while (aadRemaining > HSMXXF3_auxBounce.size)
        {
            aadOp.aad       = (uint8_t *)aadPtr;
            aadOp.aadLength = maxAADChunk;

            object->operationType = (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ? AESCCM_OP_TYPE_AAD_ENCRYPT
                                                                                      : AESCCM_OP_TYPE_AAD_DECRYPT;
            object->operation     = (AESCCM_OperationUnion *)&aadOp;
            object->aad           = aadPtr;
            object->aadLength     = maxAADChunk;
            object->input         = NULL;
            object->output        = NULL;
            object->inputLength   = 0U;

            /* setupObjectMetaData may buffer the last AES block of this chunk
             * into aadFinalBlock.  Because aadRemaining > auxBounce > maxAADChunk
             * here, operation->aadLength != totalAADLengthRemaining, so no
             * buffering occurs for non-final chunks.
             */
            AESCCMXXF3HSM_setupObjectMetaData(object);

            /* Due to errata SYS_211, acquire CommonResource lock before each
             * token submission, same as performHSMOperation does.
             */
            if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
            }

            /* Use POLLING for intermediate tokens — avoids interrupt-state
             * side-effects with a NULL callback for BLOCKING-mode callers.
             * Same pattern as createTempAssetID / freeTempAssetID.
             */
            int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)handle);
            if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
            {
                hsmRetval = HSMXXF3_waitForResult();
            }

            CommonResourceXXF3_releaseLock();

            if (hsmRetval != HSMXXF3_STATUS_SUCCESS || ((HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK) != 0))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_ERROR;
            }

            object->totalAADLengthRemaining -= maxAADChunk;

            aadPtr += maxAADChunk;
            aadRemaining -= maxAADChunk;
        }

        /* aadRemaining now fits in the bounce buffer (≤ auxBounce).
         *
         * Run setupObjectMetaData(AAD_ENCRYPT) for this last chunk and submit
         * the token.  setupObjectMetaData buffers the trailing bytes that must
         * travel with the first DATA token into aadFinalBlock / bufferedAADLength
         * and reduces object->aadLength accordingly.  After the token returns we
         * decrement totalAADLengthRemaining only by the amount actually submitted,
         * leaving bufferedAADLength in totalAADLengthRemaining so that the DATA
         * phase sees it > 0 and includes the buffered tail.
         *
         * For the no-payload case, the last AAD chunk is left for
         * performHSMOperation (ONE_STEP) so that postProcessingCommon runs and
         * extracts the MAC.
         */
        if (operation->inputLength > 0U)
        {
            aadOp.aad       = (uint8_t *)aadPtr;
            aadOp.aadLength = aadRemaining;

            object->operationType = (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ? AESCCM_OP_TYPE_AAD_ENCRYPT
                                                                                      : AESCCM_OP_TYPE_AAD_DECRYPT;
            object->operation     = (AESCCM_OperationUnion *)&aadOp;
            object->aad           = aadPtr;
            object->aadLength     = aadRemaining;
            object->input         = NULL;
            object->output        = NULL;
            object->inputLength   = 0U;

            AESCCMXXF3HSM_setupObjectMetaData(object);
            /* object->aadLength is now the amount to submit (may be < aadRemaining
             * if setupObjectMetaData buffered the tail into aadFinalBlock).
             */
            size_t submittedAAD = object->aadLength;

            if (submittedAAD > 0U)
            {
                if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
                {
                    (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                    HSMXXF3_releaseLock();
                    return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
                }

                int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)handle);
                if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
                {
                    hsmRetval = HSMXXF3_waitForResult();
                }

                CommonResourceXXF3_releaseLock();

                if (hsmRetval != HSMXXF3_STATUS_SUCCESS || ((HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK) != 0))
                {
                    (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                    HSMXXF3_releaseLock();
                    return AESCCM_STATUS_ERROR;
                }
            }

            /* Decrement by the amount submitted.  The remainder (bufferedAADLength)
             * stays in totalAADLengthRemaining so DATA tokens include it.
             */
            object->totalAADLengthRemaining -= submittedAAD;
        }
        else
        {
            /* No payload: leave the remaining AAD in object->aad / aadLength so
             * performHSMOperation (ONE_STEP) submits it as the final token and
             * postProcessingCommon extracts the MAC.
             */
            object->aad       = aadPtr;
            object->aadLength = aadRemaining;
        }

        object->operationType = operationType;
        object->operation     = (AESCCM_OperationUnion *)operation;
    }

    /* ------------------------------------------------------------------ */
    /* Payload phase: submit block-aligned intermediate payload chunks;    */
    /* the final chunk (which may include remaining AAD) goes through      */
    /* performHSMOperation so postProcessingCommon extracts the MAC.       */
    /* ------------------------------------------------------------------ */
    if (operation->inputLength > 0U)
    {
        AESCCM_SegmentedDataOperation dataOp;
        uint8_t *inputPtr    = (uint8_t *)operation->input;
        uint8_t *outputPtr   = (uint8_t *)operation->output;
        size_t dataRemaining = operation->inputLength;

        while (dataRemaining > maxPayloadChunk)
        {
            dataOp.input       = inputPtr;
            dataOp.output      = outputPtr;
            dataOp.inputLength = (uint32_t)maxPayloadChunk;

            object->operationType = (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ? AESCCM_OP_TYPE_DATA_ENCRYPT
                                                                                      : AESCCM_OP_TYPE_DATA_DECRYPT;
            object->operation     = (AESCCM_OperationUnion *)&dataOp;
            object->input         = inputPtr;
            object->output        = outputPtr;
            object->inputLength   = maxPayloadChunk;
            /* AAD was fully submitted during the AAD phase; clear for data tokens. */
            object->aad           = NULL;
            object->aadLength     = 0U;

            AESCCMXXF3HSM_setupObjectMetaData(object);

            if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
            }

            int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)handle);
            if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
            {
                hsmRetval = HSMXXF3_waitForResult();
            }

            CommonResourceXXF3_releaseLock();

            if (hsmRetval != HSMXXF3_STATUS_SUCCESS || ((HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK) != 0))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_ERROR;
            }

            object->totalDataLengthRemaining -= maxPayloadChunk;
            /* The buffered AAD tail (if any) was included in this chunk's token;
             * clear totalAADLengthRemaining so subsequent chunks do not repeat it.
             */
            object->totalAADLengthRemaining = 0U;
            object->bufferedAADLength       = 0U;

            inputPtr += maxPayloadChunk;
            outputPtr += maxPayloadChunk;
            dataRemaining -= maxPayloadChunk;
        }

        /* Final payload chunk: use FINALIZE operationType so setupObjectMetaData
         * sets loadIV=true (CBC-MAC state was saved by intermediate tokens) and
         * postProcessingCommon extracts the MAC.  ONE_STEP would not set loadIV
         * and would also overwrite W[25]/W[9] with the full original AAD, causing
         * the HSM to try to DMA from the original AAD address again.
         */
        AESCCM_SegmentedFinalizeOperation finalizeOp;
        finalizeOp.input       = inputPtr;
        finalizeOp.output      = outputPtr;
        finalizeOp.inputLength = (uint32_t)dataRemaining;
        finalizeOp.mac         = operation->mac;
        finalizeOp.macLength   = operation->macLength;

        object->operationType = (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ? AESCCM_OP_TYPE_FINALIZE_ENCRYPT
                                                                                  : AESCCM_OP_TYPE_FINALIZE_DECRYPT;
        object->operation     = (AESCCM_OperationUnion *)&finalizeOp;

        status = AESCCMXXF3HSM_performHSMOperation(handle);
    }
    else
    {
        /* AAD-only operation (no payload, only chunked AAD in PSRAM).
         * All intermediate AAD chunks were submitted above.  The remaining
         * AAD (aadRemaining ≤ auxBounce) was not yet submitted — manually
         * split it into the block-aligned portion and the tail (which
         * setupObjectMetaData(FINALIZE) will pick up from aadFinalBlock via
         * totalAADLengthRemaining > 0).
         */
        const uint8_t *aadPtr  = operation->aad + (operation->aadLength - object->totalAADLengthRemaining);
        size_t aadRemaining    = object->totalAADLengthRemaining;
        size_t blockAlignedAAD = aadRemaining & ~(AES_BLOCK_SIZE - 1U);
        size_t tailLen         = aadRemaining - blockAlignedAAD;

        if (blockAlignedAAD >= AES_BLOCK_SIZE)
        {
            /* Reserve the last full block for aadFinalBlock so the FINALIZE
             * token carries it as the per-spec "last AAD block" alongside the
             * zero-length payload.
             */
            blockAlignedAAD -= AES_BLOCK_SIZE;
            tailLen = AES_BLOCK_SIZE;
        }

        (void)memset(object->aadFinalBlock, 0, AES_BLOCK_SIZE);
        (void)memcpy(object->aadFinalBlock, aadPtr + blockAlignedAAD, tailLen);
        object->bufferedAADLength = tailLen;

        /* Submit the block-aligned AAD prefix if any (no FINALIZE yet). */
        if (blockAlignedAAD > 0U)
        {
            AESCCM_SegmentedAADOperation aadOp;
            aadOp.aad       = (uint8_t *)aadPtr;
            aadOp.aadLength = blockAlignedAAD;

            object->operationType = (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ? AESCCM_OP_TYPE_AAD_ENCRYPT
                                                                                      : AESCCM_OP_TYPE_AAD_DECRYPT;
            object->operation     = (AESCCM_OperationUnion *)&aadOp;
            object->aad           = aadPtr;
            object->aadLength     = blockAlignedAAD;
            object->input         = NULL;
            object->output        = NULL;
            object->inputLength   = 0U;

            AESCCMXXF3HSM_setupObjectMetaData(object);

            if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
            }

            int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)handle);
            if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
            {
                hsmRetval = HSMXXF3_waitForResult();
            }

            CommonResourceXXF3_releaseLock();

            if (hsmRetval != HSMXXF3_STATUS_SUCCESS || ((HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK) != 0))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_ERROR;
            }

            object->totalAADLengthRemaining -= blockAlignedAAD;
        }

        /* FINALIZE with zero-length payload: setupObjectMetaData picks up
         * aadFinalBlock (tailLen bytes) via totalAADLengthRemaining > 0.
         */
        AESCCM_SegmentedFinalizeOperation finalizeOp;
        finalizeOp.input       = NULL;
        finalizeOp.output      = NULL;
        finalizeOp.inputLength = 0U;
        finalizeOp.mac         = operation->mac;
        finalizeOp.macLength   = operation->macLength;

        object->operationType = (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) ? AESCCM_OP_TYPE_FINALIZE_ENCRYPT
                                                                                  : AESCCM_OP_TYPE_FINALIZE_DECRYPT;
        object->operation     = (AESCCM_OperationUnion *)&finalizeOp;

        status = AESCCMXXF3HSM_performHSMOperation(handle);
    }

    return status;
    #else
    return AESCCMXXF3HSM_oneStepOperationInternal(handle, operation, operationType);
    #endif /* DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX */
}

/*
 *  ======== AESCCMXXF3HSM_oneStepOperationInternal ========
 */
static int_fast16_t AESCCMXXF3HSM_oneStepOperationInternal(AESCCM_Handle handle,
                                                           AESCCM_OneStepOperation *operation,
                                                           AESCCM_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    /* Internally generated nonces aren't supported for now */
    DebugP_assert(!operation->nonceInternallyGenerated);
    DebugP_assert(operation->nonce && (operation->nonceLength >= 7U) && (operation->nonceLength <= 13U));
    DebugP_assert((operation->aad && (operation->aadLength > 0U)) ||
                  (operation->input && (operation->inputLength > 0U)));
    DebugP_assert(operation->mac && (operation->macLength <= 16U));
    /* Implementation only supports aadLength to 65,279 bytes */
    DebugP_assert(operation->aadLength <= B1_AAD_LENGTH_SMALL_LIMIT);

    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;

    /* The nonce length must be 7 to 13 bytes long */
    if ((operation->nonceLength < (uint8_t)7U) || (operation->nonceLength > (uint8_t)13U))
    {
        return AESCCM_STATUS_ERROR;
    }

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* The combined length of AAD and payload data must be non-zero. */
    if ((operation->aadLength + operation->inputLength) == 0U)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESCCM_STATUS_ERROR;
    }

    object->common.returnStatus = AESCCM_STATUS_SUCCESS;

    object->operation     = (AESCCM_OperationUnion *)operation;
    object->operationType = operationType;

    object->common.key = *(operation->key);
    object->input      = operation->input;
    object->output     = operation->output;
    object->mac        = operation->mac;
    object->aad        = operation->aad;
    object->nonce      = operation->nonce;

    object->inputLength     = operation->inputLength;
    object->totalDataLength = operation->inputLength;
    object->macLength       = operation->macLength;
    object->aadLength       = operation->aadLength;
    object->totalAADLength  = operation->aadLength;
    object->nonceLength     = operation->nonceLength;

    object->totalDataLengthRemaining = object->totalDataLength;
    object->totalAADLengthRemaining  = object->totalAADLength;

    object->tempAssetID = 0U;

    if ((operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT) && (operation->macLength == 0U))
    {
        /* We are not supplied the macLength at this point of the segmented operation.
         * Therefore, the driver gives it a dummy length which is the max length until
         * the user supplies the desired macLength in _setLengths() API.
         */
        object->macLength = HSM_MAC_MAX_LENGTH;
    }

    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    /* If input length is larger than 1 block and it is not a multiple of block-size,
     * then a one step operation becomes a segmented operation and requires a state
     * asset to store the intermediate state of the MAC within the HSM.
     */
    if ((operation->inputLength > AES_BLOCK_SIZE) &&
        (!HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE((operation->inputLength))))
    {
        status = AESCCMXXF3HSM_createTempAssetID(handle);
    }

    #if (ENABLE_KEY_STORAGE == 1)
    status = AESCCMXXF3HSM_getKeyMaterial(object);
    #endif

    if (status != AESCCM_STATUS_SUCCESS)
    {
        /* In the case of failure to initialize the operation, we need to free all assets allocated.
         * Capturing the return status of this operation is pointless since we are returning an
         * error code anyways.
         */
        (void)AESCCMXXF3HSM_freeTempAssetID(handle);

        HSMXXF3_releaseLock();
    }
    else
    {
        status = AESCCMXXF3HSM_performHSMOperation(handle);
    }

    return status;
}

/*
 *  ======== AESCCMXXF3HSM_setupSegmentedOperation ========
 */
static int_fast16_t AESCCMXXF3HSM_setupSegmentedOperation(AESCCM_Handle handle,
                                                          AESCCM_OperationType operationType,
                                                          const CryptoKey *key,
                                                          size_t totalAADLength,
                                                          size_t totalDataLength,
                                                          size_t macLength)
{
    DebugP_assert(handle);
    DebugP_assert(key);
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Make internal copy of crypto key */
    object->common.key = *key;

    /* returnStatus is only changed in the case of an error or cancellation */
    object->common.returnStatus = AES_STATUS_SUCCESS;

    object->segmentedOperationInProgress = true;

    object->operationType = operationType;

    /* If the user doesn't provide the total lengths in the setupXXXX()
     * calls, they must provide the lengths in setLengths().
     */
    object->totalAADLength           = totalAADLength;
    object->totalDataLength          = totalDataLength;
    object->macLength                = (uint8_t)macLength;
    object->aadBytesProcessed        = 0U;
    object->bufferedAADLength        = (uint8_t)0U;
    object->totalAADLengthRemaining  = totalAADLength;
    object->totalDataLengthRemaining = totalDataLength;

    if ((operationType == AESCCM_OPERATION_TYPE_ENCRYPT) && (macLength == 0U))
    {
        /* We are not supplied the macLength at this point of the segmented operation.
         * Therefore, the driver gives it a dummy length which is the max length until
         * the user supplies the desired macLength in _setLengths() API.
         */
        object->macLength = HSM_MAC_MAX_LENGTH;
    }

    (void)memset(object->KeyStore_keyingMaterial, 0, AESCommonXXF3_256_KEY_LENGTH_BYTES);
    (void)memset(object->inputFinalBlock, 0, AES_BLOCK_SIZE);
    (void)memset(object->outputFinalBlock, 0, AES_BLOCK_SIZE);
    (void)memset(object->aadFinalBlock, 0, AES_BLOCK_SIZE);

    /* Initialize MAC pointer to NULL to avoid premature processing of the
     * MAC in the ISR.
     */
    object->mac = NULL;

    /* Initialize operation pointer to NULL in case AESCCM_cancelOperation
     * is called after AESCCM_setupXXXX and callback should be skipped.
     */
    object->operation = NULL;

    #if (ENABLE_KEY_STORAGE == 1)
    status = AESCCMXXF3HSM_getKeyMaterial(object);
    #endif

    if (((totalAADLength > AES_BLOCK_SIZE) || (totalDataLength > AES_BLOCK_SIZE)) && (object->tempAssetID == 0U))
    {
        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
        {
            return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
        }

        status = AESCCMXXF3HSM_createTempAssetID(handle);

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== AESCCMXXF3HSM_setupEncrypt ========
 */
int_fast16_t AESCCMXXF3HSM_setupEncrypt(AESCCM_Handle handle,
                                        const CryptoKey *key,
                                        size_t totalAADLength,
                                        size_t totalPlaintextLength,
                                        size_t macLength)
{
    return AESCCMXXF3HSM_setupSegmentedOperation(handle,
                                                 AESCCM_OPERATION_TYPE_ENCRYPT,
                                                 key,
                                                 totalAADLength,
                                                 totalPlaintextLength,
                                                 macLength);
}

/*
 *  ======== AESCCMXXF3HSM_setupDecrypt ========
 */
int_fast16_t AESCCMXXF3HSM_setupDecrypt(AESCCM_Handle handle,
                                        const CryptoKey *key,
                                        size_t totalAADLength,
                                        size_t totalPlaintextLength,
                                        size_t macLength)
{
    return AESCCMXXF3HSM_setupSegmentedOperation(handle,
                                                 AESCCM_OPERATION_TYPE_DECRYPT,
                                                 key,
                                                 totalAADLength,
                                                 totalPlaintextLength,
                                                 macLength);
}

    /*
     *  ======== AESCCMXXF3HSM_submitAADTail ========
     *
     *  Submits a single AAD chunk that fits within the aux bounce buffer.
     *  Called with the HSMXXF3 lock already held. Handles the small final-block
     *  buffering path and the normal performHSMOperation path.
     *  Only used on CC35XX where the chunked AAD path needs this helper.
     */
    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
static int_fast16_t AESCCMXXF3HSM_submitAADTail(AESCCM_Handle handle, AESCCM_SegmentedAADOperation *operation)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    if ((operation->aadLength <= AES_BLOCK_SIZE) && (operation->aadLength == object->totalAADLengthRemaining))
    {
        (void)memcpy(&object->aadFinalBlock[0], operation->aad, operation->aadLength);
        object->bufferedAADLength = operation->aadLength;

        object->common.returnStatus = AESCCM_STATUS_SUCCESS;

        HSMXXF3_releaseLock();

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
        }

        return AESCCM_STATUS_SUCCESS;
    }

    return AESCCMXXF3HSM_performHSMOperation(handle);
}
    #endif /* DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX */

/*
 *  ======== AESCCMXXF3HSM_addAAD ========
 */
int_fast16_t AESCCMXXF3HSM_addAAD(AESCCM_Handle handle, AESCCM_SegmentedAADOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMXXF3_Object *object          = AESCCMXXF3_getObject(handle);
    object->operation                  = (AESCCM_OperationUnion *)operation;
    AESCCM_OperationType operationType = AESCCM_OP_TYPE_AAD_ENCRYPT;

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if ((object->totalAADLength == 0U) || (object->hsmStatus != HSMXXF3_STATUS_SUCCESS))
    {
        return AESCCM_STATUS_ERROR;
    }
    else if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        /* Don't continue the segmented operation if there
         * was an error or a cancellation.
         */
        return object->common.returnStatus;
    }

    if ((!HSM_IS_SIZE_MULTIPLE_OF_AES_BLOCK_SIZE(operation->aadLength)) &&
        (operation->aadLength != object->totalAADLengthRemaining))
    {
        return AESCCM_STATUS_ERROR;
    }

    /* This operation can be called after setup or after addAAD again. */
    DebugP_assert((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT));

    if ((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT))
    {
        operationType = AESCCM_OP_TYPE_AAD_DECRYPT;
    }

    object->operationType = operationType;

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When the caller's AAD segment is in PSRAM and exceeds the aux bounce
     * buffer, split it into bounce-buffer-sized intermediate tokens here
     * before submitting the remaining tail via AESCCMXXF3HSM_submitAADTail.
     */
    size_t maxAADChunk = HSMXXF3_auxBounce.size & ~(AES_BLOCK_SIZE - 1U);

    if (XMEMWFF3_isAddrExternal((uintptr_t)operation->aad) && (operation->aadLength > HSMXXF3_auxBounce.size) &&
        (maxAADChunk > 0U))
    {
        /* Callback mode is not supported for chunked operations because each
         * intermediate token submission would fire a separate callback.
         */
        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            return AESCCM_STATUS_FEATURE_NOT_SUPPORTED;
        }

        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
        {
            return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
        }

        AESCCM_SegmentedAADOperation aadOp;
        const uint8_t *aadPtr = operation->aad;
        size_t aadRemaining   = operation->aadLength;

        while (aadRemaining > HSMXXF3_auxBounce.size)
        {
            aadOp.aad       = (uint8_t *)aadPtr;
            aadOp.aadLength = maxAADChunk;

            object->operation   = (AESCCM_OperationUnion *)&aadOp;
            object->aad         = aadPtr;
            object->aadLength   = maxAADChunk;
            object->input       = NULL;
            object->output      = NULL;
            object->inputLength = 0U;

            AESCCMXXF3HSM_setupObjectMetaData(object);

            if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
            }

            int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)handle);
            if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
            {
                hsmRetval = HSMXXF3_waitForResult();
            }

            CommonResourceXXF3_releaseLock();

            if (hsmRetval != HSMXXF3_STATUS_SUCCESS || ((HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK) != 0))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_ERROR;
            }

            object->totalAADLengthRemaining -= maxAADChunk;
            aadPtr += maxAADChunk;
            aadRemaining -= maxAADChunk;
        }

        aadOp.aad         = (uint8_t *)aadPtr;
        aadOp.aadLength   = aadRemaining;
        object->operation = (AESCCM_OperationUnion *)&aadOp;

        /* Lock already held — submit remaining tail directly. */
        return AESCCMXXF3HSM_submitAADTail(handle, &aadOp);
    }
    #endif /* DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX */

    /* Check for small-block buffering path before acquiring the lock, matching
     * original behavior where no lock was needed for this path on CC27XX.
     */
    if ((operation->aadLength <= AES_BLOCK_SIZE) && (operation->aadLength == object->totalAADLengthRemaining))
    {
        (void)memcpy(&object->aadFinalBlock[0], operation->aad, operation->aadLength);
        object->bufferedAADLength = operation->aadLength;

        object->common.returnStatus = AESCCM_STATUS_SUCCESS;

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, object->common.returnStatus, object->operation, object->operationType);
        }

        return AESCCM_STATUS_SUCCESS;
    }

    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    return AESCCMXXF3HSM_performHSMOperation(handle);
}

/*
 *  ======== AESCCMXXF3HSM_addData ========
 */
static int_fast16_t AESCCMXXF3HSM_addData(AESCCM_Handle handle,
                                          AESCCM_OperationType operationType,
                                          AESCCM_OperationUnion *operation)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    object->operationType = operationType;
    object->operation     = operation;

    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When the caller's payload segment is in PSRAM and exceeds the bounce
     * buffers, split it into bounce-buffer-sized intermediate tokens here
     * before the final chunk falls through to performHSMOperation below.
     */
    AESCCM_SegmentedDataOperation *dataOp = (AESCCM_SegmentedDataOperation *)operation;
    size_t inputBounceSize  = XMEMWFF3_isAddrExternal((uintptr_t)dataOp->input) ? HSMXXF3_inputBounce.size : SIZE_MAX;
    size_t outputBounceSize = XMEMWFF3_isAddrExternal((uintptr_t)dataOp->output) ? HSMXXF3_outputBounce.size : SIZE_MAX;
    size_t maxPayloadChunk  = Math_MIN(inputBounceSize, outputBounceSize) & ~(AES_BLOCK_SIZE - 1U);

    if ((dataOp->input != NULL) && XMEMWFF3_isAddrExternal((uintptr_t)dataOp->input) &&
        (dataOp->inputLength > maxPayloadChunk) && (maxPayloadChunk > 0U))
    {
        /* Callback mode is not supported for chunked operations because each
         * intermediate token submission would fire a separate callback.
         */
        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            return AESCCM_STATUS_FEATURE_NOT_SUPPORTED;
        }

        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
        {
            return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
        }

        AESCCM_SegmentedDataOperation chunkOp;
        uint8_t *inputPtr    = (uint8_t *)dataOp->input;
        uint8_t *outputPtr   = (uint8_t *)dataOp->output;
        size_t dataRemaining = dataOp->inputLength;

        while (dataRemaining > maxPayloadChunk)
        {
            chunkOp.input       = inputPtr;
            chunkOp.output      = outputPtr;
            chunkOp.inputLength = (uint32_t)maxPayloadChunk;

            object->operation   = (AESCCM_OperationUnion *)&chunkOp;
            object->input       = inputPtr;
            object->output      = outputPtr;
            object->inputLength = maxPayloadChunk;
            /* AAD was fully submitted before this call; clear for data tokens. */
            object->aad         = NULL;
            object->aadLength   = 0U;

            AESCCMXXF3HSM_setupObjectMetaData(object);

            if (!CommonResourceXXF3_acquireLock(object->common.semaphoreTimeout))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
            }

            int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)handle);
            if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
            {
                hsmRetval = HSMXXF3_waitForResult();
            }

            CommonResourceXXF3_releaseLock();

            if (hsmRetval != HSMXXF3_STATUS_SUCCESS || ((HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK) != 0))
            {
                (void)AESCCMXXF3HSM_freeTempAssetID(handle);
                HSMXXF3_releaseLock();
                return AESCCM_STATUS_ERROR;
            }

            object->totalDataLengthRemaining -= maxPayloadChunk;
            /* The buffered AAD tail (if any) was included in this chunk's token;
             * clear totalAADLengthRemaining so subsequent chunks do not repeat it.
             */
            object->totalAADLengthRemaining = 0U;
            object->bufferedAADLength       = 0U;

            inputPtr += maxPayloadChunk;
            outputPtr += maxPayloadChunk;
            dataRemaining -= maxPayloadChunk;
        }

        /* Point the operation at the remaining tail and fall through to
         * performHSMOperation with the lock already held.
         */
        chunkOp.input       = inputPtr;
        chunkOp.output      = outputPtr;
        chunkOp.inputLength = (uint32_t)dataRemaining;
        object->operation   = (AESCCM_OperationUnion *)&chunkOp;

        return AESCCMXXF3HSM_performHSMOperation(handle);
    }
    #endif /* DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX */

    if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    return AESCCMXXF3HSM_performHSMOperation(handle);
}

/*
 *  ======== AESCCMXXF3HSM_performFinalizeChecks ========
 */
static int_fast16_t AESCCMXXF3HSM_performFinalizeChecks(const AESCCMXXF3_Object *object,
                                                        const AESCCM_SegmentedFinalizeOperation *operation)
{
    /* This operation can be called after setupXXXX, addAAD, or addData */
    DebugP_assert((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error or a cancellation.
     */
    if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMXXF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Additional payload data cannot be passed in finalize */
    if (operation->inputLength != object->totalDataLengthRemaining)
    {
        return AESCCM_STATUS_ERROR;
    }

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCMXXF3HSM_finalizeCommon ========
 */
static int_fast16_t AESCCMXXF3HSM_finalizeCommon(AESCCM_Handle handle,
                                                 AESCCM_OperationType operationType,
                                                 AESCCM_SegmentedFinalizeOperation *operation)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;

    status = AESCCMXXF3HSM_performFinalizeChecks(object, operation);

    if (status != AESCCM_STATUS_SUCCESS)
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
        status = AESCCMXXF3HSM_addData(handle, operationType, (AESCCM_OperationUnion *)operation);
    }
    else
    {
        object->operationType = operationType;

        if (operationType == AESCCM_OP_TYPE_FINALIZE_ENCRYPT)
        {
            (void)memcpy(operation->mac, (uint8_t *)&object->intermediateTag[0], operation->macLength);
        }

        if (!HSMXXF3_acquireLock(object->common.semaphoreTimeout, (uintptr_t)handle))
        {
            return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
        }

        object->aadLength   = 0U;
        object->inputLength = 0U;

        AESCCMXXF3HSM_postProcessingCommon(handle, status, (int8_t)AESCCM_STATUS_SUCCESS);
    }

    return status;
}

/*
 *  ======== AESCCMXXF3HSM_finalizeEncrypt ========
 */
int_fast16_t AESCCMXXF3HSM_finalizeEncrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    return AESCCMXXF3HSM_finalizeCommon(handle, AESCCM_OP_TYPE_FINALIZE_ENCRYPT, operation);
}

/*
 *  ======== AESCCMXXF3HSM_finalizeDecrypt ========
 */
int_fast16_t AESCCMXXF3HSM_finalizeDecrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    return AESCCMXXF3HSM_finalizeCommon(handle, AESCCM_OP_TYPE_FINALIZE_DECRYPT, operation);
}

/*
 *  ======== AESCCMXXF3HSM_freeAllAssets ========
 */
static int_fast16_t AESCCMXXF3HSM_freeAllAssets(AESCCM_Handle handle)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    #if (ENABLE_KEY_STORAGE == 1)
    KeyStore_PSA_KeyFileId keyID;
    #endif

    if ((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT))
    {
        /* Operation is not done yet and therefore, do not free any asset. */
        return AESCCM_STATUS_SUCCESS;
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
        if (status == AESCCM_STATUS_SUCCESS)
        {
            status = KeyStore_PSA_assetPostProcessing(keyID);

            if (status != KEYSTORE_PSA_STATUS_SUCCESS)
            {
                status = AESCCM_STATUS_ERROR;
            }
            else
            {
                status = AESCCM_STATUS_SUCCESS;
            }
        }
        else
        {
            (void)KeyStore_PSA_assetPostProcessing(keyID);
        }
    }
    #endif

    if (status != AESCCM_STATUS_SUCCESS)
    {
        (void)AESCCMXXF3HSM_freeTempAssetID(handle);
    }
    else
    {
        status = AESCCMXXF3HSM_freeTempAssetID(handle);
    }

    return status;
}

/*
 *  ======== AESCCMXXF3HSM_freeAssetPostProcessing ========
 */
static inline void AESCCMXXF3HSM_freeAssetPostProcessing(uintptr_t arg0)
{
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int8_t tokenResult        = HSMXXF3_getResultCode() & HSMXXF3_RETVAL_MASK;

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->tempAssetID = 0;
        status              = AESCCM_STATUS_SUCCESS;
    }

    object->common.returnStatus = status;
}

/*
 *  ======== AESCCMXXF3HSM_freeTempAssetID ========
 */
static int_fast16_t AESCCMXXF3HSM_freeTempAssetID(AESCCM_Handle handle)
{
    AESCCMXXF3_Object *object = AESCCMXXF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    int_fast16_t hsmRetval    = HSMXXF3_STATUS_ERROR;

    if (object->tempAssetID != 0)
    {
        HSMXXF3_constructDeleteAssetToken(object->tempAssetID);

        hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                        AESCCMXXF3HSM_freeAssetPostProcessing,
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

#endif
