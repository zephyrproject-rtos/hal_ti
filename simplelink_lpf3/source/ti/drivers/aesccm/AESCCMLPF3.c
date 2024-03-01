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

#include <ti/drivers/aesccm/AESCCMLPF3.h>
#include <ti/drivers/AESCCM.h>
#include <ti/drivers/aescmac/AESCMACLPF3.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/aesctr/AESCTRLPF3.h>
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
#define AESCCMLPF3_DMA_SIZE_THRESHOLD (1U * AES_BLOCK_SIZE)

/* Forward declarations */
static int_fast16_t AESCCMLPF3_addData(AESCCM_Handle handle,
                                       AESCCM_OperationType operationType,
                                       AESCCM_OperationUnion *operation,
                                       const uint8_t *input,
                                       uint8_t *output,
                                       size_t inputLength);
static int_fast16_t AESCCMLPF3_addDataDMA(AESCCM_Handle handle, AESCCM_Mode direction, size_t inputLength);
static inline int_fast16_t AESCCMLPF3_finishTag(AESCCMLPF3_Object *object, AESCCM_Mode direction);
static int_fast16_t AESCCMLPF3_oneStepOperation(AESCCM_Handle handle,
                                                AESCCM_OneStepOperation *operation,
                                                AESCCM_OperationType operationType);
static int_fast16_t AESCCMLPF3_performFinalizeChecks(const AESCCMLPF3_Object *object,
                                                     const AESCCM_SegmentedFinalizeOperation *operation);
static void AESCCMLPF3_processB0(const uint8_t *nonce,
                                 uint8_t nonceLength,
                                 size_t totalAADLength,
                                 size_t totalDataLength,
                                 uint8_t macLength);
static size_t AESCCMLPF3_processB1withAAD(const uint8_t *aad, size_t aadSegmentLength, size_t aadTotalLength);
static void AESCCMLPF3_processOneStepCBCMACPolling(AESCCM_OneStepOperation *operation,
                                                   uint32_t tag[AES_TAG_LENGTH_BYTES / 4U],
                                                   AESCCM_Mode direction);
static void AESCCMLPF3_processOneStepCTRPolling(AESCCM_OneStepOperation *operation,
                                                uint32_t tag[AES_TAG_LENGTH_BYTES / 4U]);
static inline int_fast16_t AESCCMLPF3_processOneStepDecryptPolling(AESCCMLPF3_Object *object,
                                                                   AESCCM_OneStepOperation *operation);
static inline int_fast16_t AESCCMLPF3_processOneStepEncryptPolling(AESCCMLPF3_Object *object,
                                                                   AESCCM_OneStepOperation *operation);
static int_fast16_t AESCCMLPF3_setupSegmentedOperation(AESCCMLPF3_Object *object,
                                                       const CryptoKey *key,
                                                       size_t totalAADLength,
                                                       size_t totalDataLength,
                                                       size_t macLength);
static void AESCCMLPF3_processCBCMACFinalBlock(const uint8_t *input, size_t bytesRemaining);
static void AESCCMLPF3_processCTRCounterBlock(const uint8_t *nonce, uint8_t nonceLength, uint8_t counterVal);
static int_fast16_t AESCCMLPF3_processSegmentedCBCMAC(AESCCMLPF3_Object *object,
                                                      size_t aadSegmentLength,
                                                      size_t dataSegmentLength,
                                                      AESCCM_Mode direction);
static int_fast16_t AESCCMLPF3_processSegmentedCTR(AESCCMLPF3_Object *object, size_t dataSegmentLength);
static void AESCCMLPF3_processTagCTR(AESCCMLPF3_Object *object);
static int_fast16_t AESCCMLPF3_waitForDMA(const AESCCMLPF3_Object *object);

/*
 *  ======== AESCCMLPF3_getObject ========
 */
static inline AESCCMLPF3_Object *AESCCMLPF3_getObject(AESCCM_Handle handle)
{
    AESCCMLPF3_Object *object = (AESCCMLPF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

/*
 *  ======== AESCCMLPF3_hwiFxn ========
 *
 * Note: In order to support callback return behavior, there is an undesireable
 * amount of processing done within this ISR. If support for callback return
 * behavior can be removed in the future, this processing should be moved to
 * the thread context to improve IRQ responsiveness.
 */
static void AESCCMLPF3_hwiFxn(uintptr_t arg0)
{
    bool isOpDone             = false;
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

    /* For CBC-MAC, only the input channel A interrupt is enabled.
     * For CTR, only the output channel B interrupt is enabled.
     */
    uint32_t intStatus = AESGetMaskedInterruptStatus();

    /* Disable DMA, clear interupts, and release power constraint */
    AESCommonLPF3_cleanupHwi(&object->common);

    AESCCM_Mode direction = AESCCM_MODE_ENCRYPT;

    if ((object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        direction = AESCCM_MODE_DECRYPT;
    }

    if ((intStatus & (uint32_t)AES_MIS_CHADONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonLPF3_DMA_CHA_BITMASK);

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
            AESCCMLPF3_processCBCMACFinalBlock(&plainText[object->inputLength - inputCBCMACLengthRemaining],
                                               inputCBCMACLengthRemaining);

            object->totalCBCMACLengthRemaining -= inputCBCMACLengthRemaining;
            object->inputCBCMACLengthRemaining = 0U;
        }

        /* Wait for operation to complete and save the intermediate tag */
        AESCMACLPF3_readTag((uint32_t *)&object->intermediateTag[0]);

        if (object->totalCBCMACLengthRemaining == 0U)
        {
            object->common.returnStatus = AESCCMLPF3_finishTag(object, direction);
        }

        if (direction == AESCCM_MODE_DECRYPT)
        {
            isOpDone = true;
        }
        else /* Encrypt */
        {
            object->common.returnStatus = AESCCMLPF3_processSegmentedCTR(object, object->inputLength);

            /* Operation will be handled without DMA if length less than threshold */
            if (object->inputLength < AESCCMLPF3_DMA_SIZE_THRESHOLD)
            {
                isOpDone = true;
            }
        }
    }

    if ((intStatus & (uint32_t)AES_MIS_CHBDONE_M) != (uint32_t)0U)
    {
        UDMALPF3_clearInterrupt(AESCommonLPF3_DMA_CHB_BITMASK);

        /* DMA is used to process all full blocks of data. If there is a
         * partial block of data remaining, process it with CPU R/W.
         */
        if (object->inputCTRLengthRemaining > 0U)
        {
            size_t inputCTRLengthRemaining = object->inputCTRLengthRemaining;
            /* Use CPU R/W to complete the CTR operation */
            AESCTRLPF3_processData(&object->input[object->inputLength - inputCTRLengthRemaining],
                                   &object->output[object->inputLength - inputCTRLengthRemaining],
                                   inputCTRLengthRemaining,
                                   true);

            object->totalCTRLengthRemaining -= inputCTRLengthRemaining;
            object->inputCTRLengthRemaining = 0U;
        }

        if (object->totalCTRLengthRemaining > 0U)
        {
            /* Store the counter if more input data is expected */
            AESCTRLPF3_readCounter((uint32_t *)&object->intermediateCounter[0]);
        }

        if (direction == AESCCM_MODE_ENCRYPT)
        {
            isOpDone = true;
        }
        else /* Decrypt */
        {
            object->common.returnStatus = AESCCMLPF3_processSegmentedCBCMAC(object,
                                                                            0U,
                                                                            object->inputLength,
                                                                            AESCCM_MODE_DECRYPT);

            /* Operation is completed without DMA if length < threshold */
            if (object->inputLength < AESCCMLPF3_DMA_SIZE_THRESHOLD)
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
 *  ======== AESCCMLPF3_finishTag ========
 */
static inline int_fast16_t AESCCMLPF3_finishTag(AESCCMLPF3_Object *object, AESCCM_Mode direction)
{
    int_fast16_t status = AESCCM_STATUS_SUCCESS;

    AESCCMLPF3_processTagCTR(object);

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
 *  ======== AESCCMLPF3_waitForDMA ========
 */
static int_fast16_t AESCCMLPF3_waitForDMA(const AESCCMLPF3_Object *object)
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
            (void)SemaphoreP_pend((SemaphoreP_Handle)&CryptoResourceLPF3_operationSemaphore,
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

/*
 *  ======== AESCCM_init ========
 */
void AESCCM_init(void)
{
    AESCommonLPF3_init();
}

/*
 *  ======== AESCCM_construct ========
 */
AESCCM_Handle AESCCM_construct(AESCCM_Config *config, const AESCCM_Params *params)
{
    DebugP_assert(config);

    int_fast16_t status;
    AESCCM_Handle handle      = config;
    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

    /* If params are NULL, use defaults */
    if (params == NULL)
    {
        params = &AESCCM_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AESCCM_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->callbackFxn = params->callbackFxn;

    status = AESCommonLPF3_construct(&object->common, (AES_ReturnBehavior)params->returnBehavior, params->timeout);

    if (status != AES_STATUS_SUCCESS)
    {
        handle = NULL;
    }

    return handle;
}

/*
 *  ======== AESCCM_close ========
 */
void AESCCM_close(AESCCM_Handle handle)
{
    DebugP_assert(handle);

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

    AESCommonLPF3_close(&object->common);
}

/*
 *  ======== AESCCMLPF3_processCBCMACFinalBlock ========
 */
static void AESCCMLPF3_processCBCMACFinalBlock(const uint8_t *input, size_t bytesRemaining)
{
    /* No need to reload the last intermediate tag because it still loaded in
     * the AES engine from the previous CBCMAC operation.
     */

    /* Must wait until engine is idle before clearing BUF */
    while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}

    /* Zero out the BUF registers */
    AESClearBUF();

    /* Copy directly to BUF registers. memcpy is safe to use here since the
     * order of the writes is not important when writing a partial block.
     */
    (void)memcpy((void *)(AES_BASE + AES_O_BUF0), input, bytesRemaining);

#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0
    AESSetTrigger((uint32_t)AES_TRG_AESOP_TXTXBUF);
#elif DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    AESSetTrigger((uint32_t)AES_TRG_ECBOP_TXTXBUF);
#else
    #error "Unsupported DeviceFamily_Parent for AESCMACLPF3!"
#endif
}

#define M_PRIME_OFFSET 3

/*
 *  ======== AESCCMLPF3_processB0 ========
 */
#if defined(__IAR_SYSTEMS_ICC__)
    #pragma inline = forced
#elif defined(__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(AESCCMLPF3_processB0)
#else
__attribute__((always_inline)) inline
#endif
static void AESCCMLPF3_processB0(const uint8_t *nonce,
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
 *  ======== AESCCMLPF3_processB1withAAD ========
 */
static size_t AESCCMLPF3_processB1withAAD(const uint8_t *aad, size_t aadSegmentLength, size_t aadTotalLength)
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
 *  ======== AESCCMLPF3_processCBCMACPolling ========
 */
static void AESCCMLPF3_processOneStepCBCMACPolling(AESCCM_OneStepOperation *operation,
                                                   uint32_t tag[AES_TAG_LENGTH_BYTES / 4U],
                                                   AESCCM_Mode direction)
{
    size_t dataBytesRemaining;
    size_t aadBytesRemaining;

    AESSetAUTOCFG(AESCMACLPF3_DEFAULT_AUTOCFG);

    /* Set IV to zero */
    AESClearIV();

    AESCCMLPF3_processB0(operation->nonce,
                         operation->nonceLength,
                         operation->aadLength,
                         operation->inputLength,
                         operation->macLength);

    /* Process AAD */
    if (operation->aadLength > 0U)
    {
        aadBytesRemaining = operation->aadLength;

        /* Process B1 with AAD */
        aadBytesRemaining -= AESCCMLPF3_processB1withAAD(operation->aad, operation->aadLength, operation->aadLength);

        /* Process any remaining AAD */
        if (aadBytesRemaining > 0U)
        {
            size_t blockSizeAlignedAADLength = AES_BLOCK_SIZE_MULTIPLE_LENGTH(aadBytesRemaining);

            if (blockSizeAlignedAADLength > 0U)
            {
                AESCMACLPF3_processBlocks(&operation->aad[operation->aadLength - aadBytesRemaining],
                                          blockSizeAlignedAADLength);

                aadBytesRemaining -= blockSizeAlignedAADLength;
            }

            if (aadBytesRemaining > 0U)
            {
                AESCCMLPF3_processCBCMACFinalBlock(&operation->aad[operation->aadLength - aadBytesRemaining],
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
            AESCMACLPF3_processBlocks(plainText, blockSizeAlignedDataRemaining);

            dataBytesRemaining -= blockSizeAlignedDataRemaining;
        }

        if (dataBytesRemaining > 0U)
        {
            AESCCMLPF3_processCBCMACFinalBlock(&plainText[operation->inputLength - dataBytesRemaining],
                                               dataBytesRemaining);
        }
    }

    /* Wait for operation to complete and save the intermediate tag */
    AESCMACLPF3_readTag(&tag[0]);
}

/*
 *  ======== AESCCMLPF3_processOneStepCTRPolling ========
 */
static void AESCCMLPF3_processOneStepCTRPolling(AESCCM_OneStepOperation *operation,
                                                uint32_t tag[AES_TAG_LENGTH_BYTES / 4U])
{
    /* Init Counter Mode */
    if (operation->inputLength == 0U)
    {
        AESSetAUTOCFG(AESCTRLPF3_LAST_BLOCK_AUTOCFG);
    }
    else
    {
        AESSetAUTOCFG(AESCTRLPF3_DEFAULT_AUTOCFG);
    }

    /* Process counter block with counter value of 0 */
    AESCCMLPF3_processCTRCounterBlock(operation->nonce, operation->nonceLength, (uint8_t)0U);

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
        AESCTRLPF3_processData(operation->input, operation->output, operation->inputLength, true);
    }
}

/*
 *  ======== AESCCMLPF3_processOneStepEncryptPolling ========
 */
static inline int_fast16_t AESCCMLPF3_processOneStepEncryptPolling(AESCCMLPF3_Object *object,
                                                                   AESCCM_OneStepOperation *operation)
{
    /* Calculate the MAC for the AAD and message */
    AESCCMLPF3_processOneStepCBCMACPolling(operation, (uint32_t *)&object->intermediateTag[0], AESCCM_MODE_ENCRYPT);

    /* Encrypt the MAC and the message */
    AESCCMLPF3_processOneStepCTRPolling(operation, (uint32_t *)&object->intermediateTag[0]);

    (void)memcpy((void *)&operation->mac[0], (void *)&object->intermediateTag[0], operation->macLength);

    /* This operation is always successful */
    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCMLPF3_processOneStepDecryptPolling ========
 */
static inline int_fast16_t AESCCMLPF3_processOneStepDecryptPolling(AESCCMLPF3_Object *object,
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
    AESCCMLPF3_processOneStepCTRPolling(operation, mac);

    /* Calculate the MAC on the decrypted message and AAD */
    AESCCMLPF3_processOneStepCBCMACPolling(operation, (uint32_t *)&object->intermediateTag[0], AESCCM_MODE_DECRYPT);

    /* Perform a constant time comparision of the calculated MAC and the decrypted MAC */
    macValid = CryptoUtils_buffersMatch(object->intermediateTag, mac, (size_t)operation->macLength);

    if (macValid)
    {
        status = AESCCM_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== AESCCMLPF3_oneStepOperation ========
 */
static int_fast16_t AESCCMLPF3_oneStepOperation(AESCCM_Handle handle,
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
    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);
    int_fast16_t status;

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
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
        !AESCommonLPF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Check if there is no operation already in progress for this driver
     * instance, and then mark the current operation to be in progress.
     */
    status = AESCommonLPF3_setOperationInProgress(&object->common);

    if (status != AES_STATUS_SUCCESS)
    {
        return status;
    }

    if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
    {
        AESCommonLPF3_clearOperationInProgress(&object->common);
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    object->common.cryptoResourceLocked = true;
    object->common.returnStatus         = AESCCM_STATUS_SUCCESS;

    AESCommonLPF3_loadKey(operation->key);

    /* Process all one-step operations with data length less than the DMA size
     * threshold as a polling mode operation.
     */
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (operation->inputLength < AESCCMLPF3_DMA_SIZE_THRESHOLD))
    {
        if (operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT)
        {
            status = AESCCMLPF3_processOneStepEncryptPolling(object, operation);
        }
        else /* operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT */
        {
            status = AESCCMLPF3_processOneStepDecryptPolling(object, operation);
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
            status = AESCCMLPF3_processSegmentedCBCMAC(object, operation->aadLength, 0, direction);
        }

        if ((operation->inputLength > 0U) && (status == AESCCM_STATUS_SUCCESS))
        {
            /* Process Data with DMA */
            status    = AESCCMLPF3_addDataDMA(handle, direction, operation->inputLength);
            dmaActive = true;
        }
    }

    if (!dmaActive)
    {
        AESCommonLPF3_clearOperationInProgress(&object->common);

        /* Cleanup and release crypto resource lock */
        AESCommonLPF3_cleanup(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, operationType);

            /* Always return success in callback mode */
            status = AESCCM_STATUS_SUCCESS;
        }
    }

    return status;
}

/*
 *  ======== AESCCM_oneStepEncrypt ========
 */
int_fast16_t AESCCM_oneStepEncrypt(AESCCM_Handle handle, AESCCM_OneStepOperation *operation)
{
    return AESCCMLPF3_oneStepOperation(handle, operation, AESCCM_OP_TYPE_ONESTEP_ENCRYPT);
}

/*
 *  ======== AESCCM_oneStepDecrypt ========
 */
int_fast16_t AESCCM_oneStepDecrypt(AESCCM_Handle handle, AESCCM_OneStepOperation *operation)
{
    return AESCCMLPF3_oneStepOperation(handle, operation, AESCCM_OP_TYPE_ONESTEP_DECRYPT);
}

/*
 *  ======== AESCCMLPF3_setupSegmentedOperation ========
 */
static int_fast16_t AESCCMLPF3_setupSegmentedOperation(AESCCMLPF3_Object *object,
                                                       const CryptoKey *key,
                                                       size_t totalAADLength,
                                                       size_t totalDataLength,
                                                       size_t macLength)
{
    DebugP_assert(key);

    int_fast16_t status = AESCommonLPF3_setupSegmentedOperation(&object->common, key);

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
    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

    int_fast16_t status = AESCCMLPF3_setupSegmentedOperation(object,
                                                             key,
                                                             totalAADLength,
                                                             totalPlaintextLength,
                                                             macLength);
    if (status == AES_STATUS_SUCCESS)
    {
        object->operationType = AESCCM_OPERATION_TYPE_ENCRYPT;
    }

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

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

    int_fast16_t status = AESCCMLPF3_setupSegmentedOperation(object,
                                                             key,
                                                             totalAADLength,
                                                             totalPlaintextLength,
                                                             macLength);
    if (status == AESCCM_STATUS_SUCCESS)
    {
        object->operationType = AESCCM_OPERATION_TYPE_DECRYPT;
    }

    return status;
}

/*
 *  ======== AESCCM_setLengths ========
 */
int_fast16_t AESCCM_setLengths(AESCCM_Handle handle, size_t aadLength, size_t plaintextLength, size_t macLength)
{
    DebugP_assert(handle);

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

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

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCM_setNonce ========
 */
int_fast16_t AESCCM_setNonce(AESCCM_Handle handle, const uint8_t *nonce, size_t nonceLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

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

/*
 *  ======== AESCCMLPF3_processSegmentedCBCMAC ========
 */
static int_fast16_t AESCCMLPF3_processSegmentedCBCMAC(AESCCMLPF3_Object *object,
                                                      size_t aadSegmentLength,
                                                      size_t dataSegmentLength,
                                                      AESCCM_Mode direction)
{
    bool dmaActive            = false;
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    size_t aadBytesRemaining  = 0U;
    size_t dataBytesRemaining = 0U;

    AESSetAUTOCFG(AESCMACLPF3_DEFAULT_AUTOCFG);

    /* Process B0 block if no AAD and no data has been proceeded yet */
    if ((object->aadBytesProcessed == 0U) && (object->totalCBCMACLengthRemaining == object->totalDataLength))
    {
        /* Set IV to zero */
        AESClearIV();

        AESCCMLPF3_processB0(object->nonce,
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
            object->aadBytesProcessed = AESCCMLPF3_processB1withAAD(object->aad,
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

                size_t aadBlockBytesAvail = (AES_BLOCK_SIZE - AESCCMLPF3_AAD_BUFFER_SIZE);
                const uint8_t *newAAD     = &object->aad[aadSegmentLength - aadBytesRemaining];

                /* Copy the new AAD into the local AAD block */
                if (aadBytesRemaining >= aadBlockBytesAvail)
                {
                    (void)memcpy((void *)&aadBlock.bytes[AESCCMLPF3_AAD_BUFFER_SIZE],
                                 (void *)newAAD,
                                 aadBlockBytesAvail);

                    object->aadBytesProcessed += AES_BLOCK_SIZE;
                    aadBytesRemaining -= aadBlockBytesAvail;
                }
                else
                {
                    (void)memcpy((void *)&aadBlock.bytes[AESCCMLPF3_AAD_BUFFER_SIZE],
                                 (void *)newAAD,
                                 aadBytesRemaining);

                    object->aadBytesProcessed += (aadBytesRemaining + AESCCMLPF3_AAD_BUFFER_SIZE);
                    aadBytesRemaining = 0U;
                }

                AESCMACLPF3_processBlocks(aadBlock.bytes, sizeof(aadBlock));

                object->bufferedAADLength = (uint8_t)0U;
            }

            size_t blockSizeAlignedAADLength = AES_BLOCK_SIZE_MULTIPLE_LENGTH(aadBytesRemaining);

            if (blockSizeAlignedAADLength > 0U)
            {
                AESCMACLPF3_processBlocks(&object->aad[aadSegmentLength - aadBytesRemaining],
                                          blockSizeAlignedAADLength);

                object->aadBytesProcessed += blockSizeAlignedAADLength;
                aadBytesRemaining -= blockSizeAlignedAADLength;
            }

            if (aadBytesRemaining > 0U)
            {
                if ((object->aadBytesProcessed + aadBytesRemaining) == object->totalAADLength)
                {
                    AESCCMLPF3_processCBCMACFinalBlock(&object->aad[aadSegmentLength - aadBytesRemaining],
                                                       aadBytesRemaining);
                    object->aadBytesProcessed += aadBytesRemaining;
                }
                else if (aadBytesRemaining == AESCCMLPF3_AAD_BUFFER_SIZE)
                {
                    /* Save leftover AAD bytes to process later */
                    const uint8_t *aadRemaining = &object->aad[aadSegmentLength - AESCCMLPF3_AAD_BUFFER_SIZE];
                    object->bufferedAAD[0]      = *aadRemaining;
                    object->bufferedAAD[1]      = *(aadRemaining + 1U);
                    object->bufferedAADLength   = (uint8_t)AESCCMLPF3_AAD_BUFFER_SIZE;
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
            (blockSizeAlignedDataRemaining < AESCCMLPF3_DMA_SIZE_THRESHOLD))
        {
            /* Process all the full blocks of data */
            if (blockSizeAlignedDataRemaining > 0U)
            {
                AESCMACLPF3_processBlocks(plainText, blockSizeAlignedDataRemaining);

                dataBytesRemaining -= blockSizeAlignedDataRemaining;
            }

            if (dataBytesRemaining > 0U)
            {
                AESCCMLPF3_processCBCMACFinalBlock(&plainText[dataSegmentLength - dataBytesRemaining],
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
            AESCommonLPF3_setupDMA(&object->common, AESCBCMACLPF3_DMA_CONFIG);

            AESCommonLPF3_configInputDMA(plainText, blockSizeAlignedDataRemaining);

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
        status = AESCCMLPF3_waitForDMA(object);
    }
    else
    {
        /* Wait for operation to complete and save the intermediate tag */
        AESCMACLPF3_readTag((uint32_t *)&object->intermediateTag[0]);
    }

    return status;
}

/*
 *  ======== AESCCMLPF3_processCTRCounterBlock ========
 */
static void AESCCMLPF3_processCTRCounterBlock(const uint8_t *nonce, uint8_t nonceLength, uint8_t counterVal)
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
    AESCTRLPF3_writeCounter(counter.words);

    /* Wait for encryption of counter block to complete */
    while (AESGetStatus() != (uint32_t)AES_STA_STATE_IDLE) {}
}

/*
 *  ======== AESCCMLPF3_processTagCTR ========
 */
static void AESCCMLPF3_processTagCTR(AESCCMLPF3_Object *object)
{
    /* Use default CTR config without AES_AUTOCFG_TRGAES_RDTXT3
     * to avoid triggering an encryption of the next counter value
     * when reading out the encrypted tag.
     */
    AESSetAUTOCFG(AESCTRLPF3_LAST_BLOCK_AUTOCFG);

    /* Process counter block with counter value of 0 */
    AESCCMLPF3_processCTRCounterBlock(object->nonce, object->nonceLength, (uint8_t)0U);

    /* XOR tag with encrypted counter block to form ciphertext */
    AESWriteTXTXOR32((uint32_t *)&object->intermediateTag[0]);

    /* Read the tag ciphertext */
    AESReadTag32((uint32_t *)&object->intermediateTag[0]);
}

/*
 *  ======== AESCCMLPF3_processSegmentedCTR ========
 */
static int_fast16_t AESCCMLPF3_processSegmentedCTR(AESCCMLPF3_Object *object, size_t dataSegmentLength)
{
    bool dmaActive      = false;
    bool firstCounter   = false;
    int_fast16_t status = AESCCM_STATUS_SUCCESS;

    if (object->totalCTRLengthRemaining == object->totalDataLength)
    {
        firstCounter = true;
    }

    AESSetAUTOCFG(AESCTRLPF3_DEFAULT_AUTOCFG);

    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        (dataSegmentLength >= AESCCMLPF3_DMA_SIZE_THRESHOLD))
    {
        size_t bytesProcessed;

        bytesProcessed = AESCTRLPF3_configDataDMA(&object->common, object->input, object->output, dataSegmentLength);

        object->totalCTRLengthRemaining -= bytesProcessed;
        object->inputCTRLengthRemaining -= bytesProcessed;

        dmaActive = true;
    }

    /* Writing the counter value will trigger the first encryption */
    if (firstCounter)
    {
        /* Process counter block with initial counter value of 1 */
        AESCCMLPF3_processCTRCounterBlock(object->nonce, object->nonceLength, (uint8_t)1U);
    }
    else
    {
        /* Restore intermediate counter */
        AESCTRLPF3_writeCounter((uint32_t *)&object->intermediateCounter[0]);
    }

    if (dmaActive)
    {
        status = AESCCMLPF3_waitForDMA(object);
    }
    else
    {
        /* Process data with CPU R/W */
        AESCTRLPF3_processData(object->input, object->output, dataSegmentLength, false);

        object->totalCTRLengthRemaining -= dataSegmentLength;

        /* Store the counter */
        AESCTRLPF3_readCounter((uint32_t *)&object->intermediateCounter[0]);
    }

    return status;
}

/*
 *  ======== AESCCM_addAAD ========
 */
int_fast16_t AESCCM_addAAD(AESCCM_Handle handle, AESCCM_SegmentedAADOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);
    int_fast16_t status;

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

    if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    object->common.cryptoResourceLocked = true;

    /* Load only the key into the AES engine now. The AUTOCFG values are loaded as needed
     * depending on whether it's a CTR operation or a CBC-MAC operation.
     */
    AESCommonLPF3_loadKey(&object->common.key);

    object->operationType = operationType;
    object->aad           = operation->aad;

    /* AAD is expected to be relatively short in length (< a few AES blocks)
     * so DMA is not utilized for blocking and callback modes because the
     * interrupt and task switching overhead would outweigh any CPU cycles
     * saved using DMA. Code size and complexity is reduced by not supporting
     * DMA for AAD.
     */

    status = AESCCMLPF3_processSegmentedCBCMAC(object, operation->aadLength, 0, direction);

    if ((status == AESCCM_STATUS_SUCCESS) && (object->totalDataLength == 0U) &&
        (object->aadBytesProcessed == object->totalAADLength))
    {
        AESCCMLPF3_processTagCTR(object);
    }

    /* Cleanup and release crypto resource lock */
    AESCommonLPF3_cleanup(&object->common);

    object->common.returnStatus = status;

    if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, operationType);

        /* Always return success in callback mode */
        status = AESCCM_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== AESCCMLPF3_addDataDMA ========
 */
static int_fast16_t AESCCMLPF3_addDataDMA(AESCCM_Handle handle, AESCCM_Mode direction, size_t inputLength)
{
    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);
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
    AESCCMLPF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    AESCommonLPF3_setupHwi(AESCCMLPF3_hwiFxn, (uintptr_t)handle, hwAttrs->intPriority);

    if (direction == AESCCM_MODE_ENCRYPT)
    {
        status = AESCCMLPF3_processSegmentedCBCMAC(object, 0U, inputLength, AESCCM_MODE_ENCRYPT);
    }
    else
    {
        status = AESCCMLPF3_processSegmentedCTR(object, inputLength);
    }

    return status;
}

/*
 *  ======== AESCCMLPF3_addData ========
 */
static int_fast16_t AESCCMLPF3_addData(AESCCM_Handle handle,
                                       AESCCM_OperationType operationType,
                                       AESCCM_OperationUnion *operation,
                                       const uint8_t *input,
                                       uint8_t *output,
                                       size_t inputLength)
{
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

    if (!CryptoResourceLPF3_acquireLock(object->common.semaphoreTimeout))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    object->common.cryptoResourceLocked = true;

    /* Load only the key into the AES engine now. The AUTOCFG values are loaded as needed
     * depending on whether it's a CTR operation or a CBC-MAC operation.
     */
    AESCommonLPF3_loadKey(&object->common.key);

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
    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) || (inputLength < AESCCMLPF3_DMA_SIZE_THRESHOLD))
    {
        if (direction == AESCCM_MODE_ENCRYPT)
        {
            status = AESCCMLPF3_processSegmentedCBCMAC(object, 0, inputLength, AESCCM_MODE_ENCRYPT);
        }

        if (status == AESCCM_STATUS_SUCCESS)
        {
            status = AESCCMLPF3_processSegmentedCTR(object, inputLength);
        }

        if ((direction == AESCCM_MODE_DECRYPT) && (status == AESCCM_STATUS_SUCCESS))
        {
            status = AESCCMLPF3_processSegmentedCBCMAC(object, 0U, inputLength, AESCCM_MODE_DECRYPT);
        }

        if ((object->totalCBCMACLengthRemaining == 0U) && (status == AESCCM_STATUS_SUCCESS))
        {
            AESCCMLPF3_processTagCTR(object);
        }

        object->common.returnStatus = status;

        /* Cleanup and release crypto resource lock */
        AESCommonLPF3_cleanup(&object->common);
    }
    else
    {
        status = AESCCMLPF3_addDataDMA(handle, direction, inputLength);

        if (status != AESCCM_STATUS_SUCCESS)
        {
            object->common.returnStatus = status;

            /* Cleanup and release crypto resource lock */
            AESCommonLPF3_cleanup(&object->common);
        }
    }

    return status;
}

/*
 *  ======== AESCCM_addData ========
 */
int_fast16_t AESCCM_addData(AESCCM_Handle handle, AESCCM_SegmentedDataOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);
    int_fast16_t status;

    /* This operation can be called after setupXXXX, addAAD, or addData */
    DebugP_assert((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT));

    if (object->common.returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->common.returnStatus;
    }

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCCM_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
#endif

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

    /* The AAD input length specified so far must match the total length
     * specified in the setLengths() or setupXXXX() calls.
     * All AAD input must be processed at this point.
     */
    if (object->aadBytesProcessed != object->totalAADLength)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonLPF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCCM_STATUS_ERROR;
    }

    AESCCM_OperationType operationType = AESCCM_OP_TYPE_DATA_ENCRYPT;

    if ((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT) || (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT))
    {
        operationType = AESCCM_OP_TYPE_DATA_DECRYPT;
    }

    status = AESCCMLPF3_addData(handle,
                                operationType,
                                (AESCCM_OperationUnion *)operation,
                                operation->input,
                                operation->output,
                                operation->inputLength);

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) &&
        (operation->inputLength < AESCCMLPF3_DMA_SIZE_THRESHOLD))
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

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);
    int_fast16_t status;

    status = AESCCMLPF3_performFinalizeChecks(object, operation);

    if (status != AESCCM_STATUS_SUCCESS)
    {
        return status;
    }

    if (operation->inputLength > 0U)
    {
        object->mac       = operation->mac;
        object->macLength = operation->macLength;

        status = AESCCMLPF3_addData(handle,
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
        (operation->inputLength < AESCCMLPF3_DMA_SIZE_THRESHOLD))
    {
        if (status == AESCCM_STATUS_SUCCESS)
        {
            (void)memcpy(operation->mac, (uint32_t *)&object->intermediateTag[0], operation->macLength);
        }
        else
        {
            object->common.returnStatus = status;
        }

        AESCommonLPF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, AESCCM_OP_TYPE_FINALIZE_ENCRYPT);

            /* Always return success in callback mode */
            status = AESCCM_STATUS_SUCCESS;
        }
    }

    return status;
}

/*
 *  ======== AESCCM_finalizeDecrypt ========
 */
int_fast16_t AESCCM_finalizeDecrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);
    int_fast16_t status;

    status = AESCCMLPF3_performFinalizeChecks(object, operation);

    if (status != AESCCM_STATUS_SUCCESS)
    {
        return status;
    }

    if (operation->inputLength > 0U)
    {
        object->mac       = operation->mac;
        object->macLength = operation->macLength;

        status = AESCCMLPF3_addData(handle,
                                    AESCCM_OP_TYPE_FINALIZE_DECRYPT,
                                    (AESCCM_OperationUnion *)operation,
                                    operation->input,
                                    operation->output,
                                    operation->inputLength);
    }

    if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_POLLING) ||
        (operation->inputLength < AESCCMLPF3_DMA_SIZE_THRESHOLD))
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

        AESCommonLPF3_clearOperationInProgress(&object->common);

        if (object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, AESCCM_OP_TYPE_FINALIZE_DECRYPT);

            /* Always return success in callback mode */
            status = AESCCM_STATUS_SUCCESS;
        }
    }

    return status;
}

/*
 *  ======== AESCCMLPF3_performFinalizeChecks ========
 */
static int_fast16_t AESCCMLPF3_performFinalizeChecks(const AESCCMLPF3_Object *object,
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

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
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

    /* Additional payload data can be passed in finalize */
    if (operation->inputLength != object->totalCBCMACLengthRemaining)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Check DMA xfer limit for blocking and callback modes */
    if ((object->common.returnBehavior != AES_RETURN_BEHAVIOR_POLLING) &&
        !AESCommonLPF3_isDMALengthValid(operation->input, operation->output, operation->inputLength))
    {
        return AESCCM_STATUS_ERROR;
    }

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCM_cancelOperation ========
 */
int_fast16_t AESCCM_cancelOperation(AESCCM_Handle handle)
{
    DebugP_assert(handle);

    AESCCMLPF3_Object *object = AESCCMLPF3_getObject(handle);

    /* Cancellation is only supported in callback mode */
    if (object->common.returnBehavior != AES_RETURN_BEHAVIOR_CALLBACK)
    {
        return AESCCM_STATUS_ERROR;
    }

    uintptr_t interruptKey = HwiP_disable();

    /* Return success if there is no active operation to cancel.
     * Do not execute the callback as it would have been executed already
     * when the operation completed.
     */
    if (!object->common.operationInProgress)
    {
        HwiP_restore(interruptKey);
    }
    else
    {
        HwiP_restore(interruptKey);

        /* Cancel DMA for input and output channels, clear operation in-progress,
         * and releases crypto resource if necessary.
         */
        AESCommonLPF3_cancelOperation(&object->common, true);

        /* Operation pointer could be NULL if a segmented operation was setup
         * but neither AESCCM_addData or AESCCM_finalize was called.
         */
        if ((object->common.returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
        {
            /* Call the callback function provided by the application */
            object->callbackFxn(handle, AESCCM_STATUS_CANCELED, object->operation, object->operationType);
        }
    }

    return AESCCM_STATUS_SUCCESS;
}
