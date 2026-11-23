/*
 * Copyright (c) 2026 Texas Instruments Incorporated
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

#include <string.h>

#include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceXXF3.h>
#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/sha3/SHA3XXF3HSM.h>

#if (ENABLE_KEY_STORAGE == 1)
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
#endif

#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_interrupts.h>
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>
#include <third_party/hsmddk/include/Integration/HSMSAL/HSMSAL.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_asset_policy.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_hsm.h)

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    #include <ti/drivers/xmem/XMEMWFF3.h>
#endif

/* Max key length supported by HSM for HMAC - equal to the largest SHA3 block
 * size (SHA3-224 rate = 144 bytes). The HSM does not automatically hash keys
 * exceeding the block size.
 */
#define SHA3XXF3HSM_MAX_HMAC_KEY_LENGTH_BYTES 144

/* Forward declarations */
static inline uint32_t SHA3XXF3HSM_largestBlockSizeMultiple(uint32_t length, uint32_t blockSize);

static void SHA3XXF3HSM_setAlgorithmParams(SHA3XXF3HSM_Object *object);

static int_fast16_t SHA3XXF3HSM_processIntermediateBlocks(SHA3_Handle handle);

static int_fast16_t SHA3XXF3HSM_addData(SHA3_Handle handle, const void *data, size_t length);

static int_fast16_t SHA3XXF3HSM_finalize(SHA3_Handle handle, void *digest);

static int_fast16_t SHA3XXF3HSM_hashData(SHA3_Handle handle, const void *data, size_t length, void *digest);

static void SHA3XXF3HSM_hashPostProcess(uintptr_t driverHandle);

static void SHA3XXF3HSM_finalizePostProcess(uintptr_t driverHandle);

static void SHA3XXF3HSM_addDataPostProcess(uintptr_t driverHandle);

static void SHA3XXF3HSM_intermediateHashPostProcess(uintptr_t driverHandle);

static int_fast16_t SHA3XXF3HSM_processOneStepAndFinalizeOperation(SHA3_Handle handle);

static int_fast16_t SHA3XXF3HSM_createAndLoadKeyAssetID(SHA3_Handle handle);
static int_fast16_t SHA3XXF3HSM_createKeyAsset(SHA3_Handle handle);
static int_fast16_t SHA3XXF3HSM_LoadKeyAsset(SHA3_Handle handle, uint8_t *key);
static int_fast16_t SHA3XXF3HSM_CreateTempAssetID(SHA3_Handle handle);
static int_fast16_t SHA3XXF3HSM_freeAllAssets(SHA3_Handle handle);
static int_fast16_t SHA3XXF3HSM_freeAssetID(SHA3_Handle handle, uint32_t AssetID);

/* This table converts from SHA3_HashType values to the corresponding block
 * size.
 */
static const uint8_t blockSizeTable[] = {SHA3_BLOCK_SIZE_BYTES_224,
                                         SHA3_BLOCK_SIZE_BYTES_256,
                                         SHA3_BLOCK_SIZE_BYTES_384,
                                         SHA3_BLOCK_SIZE_BYTES_512};

static uint8_t *SHA3_data;

/* Tracks dataBytes that are used in intermediate state computations requiring
 * two HSM operations.
 */
static uint32_t SHA3_dataBytesRemaining;

static bool isInitialized = false;

/* Allows post-processing function to know transactionLength used in
 * SHA3XXF3HSM_addData().
 */
static uint32_t addDataTransactionLength;

/*
 *  ======== SHA3XXF3HSM_largestBlockSizeMultiple ========
 */
static inline uint32_t SHA3XXF3HSM_largestBlockSizeMultiple(uint32_t length, uint32_t blockSize)
{
    return (length / blockSize) * blockSize;
}

/*
 *  ======== SHA3XXF3HSM_setAlgorithmParams ========
 */
static void SHA3XXF3HSM_setAlgorithmParams(SHA3XXF3HSM_Object *object)
{
    switch (object->hashType)
    {
        case SHA3_HASH_TYPE_224:
            object->algorithm    = VEXTOKEN_ALGO_HASH_SHA3_224;
            object->digestLength = SHA3_DIGEST_LENGTH_BYTES_224;
            object->blockSize    = SHA3_BLOCK_SIZE_BYTES_224;
            break;
        case SHA3_HASH_TYPE_256:
            object->algorithm    = VEXTOKEN_ALGO_HASH_SHA3_256;
            object->digestLength = SHA3_DIGEST_LENGTH_BYTES_256;
            object->blockSize    = SHA3_BLOCK_SIZE_BYTES_256;
            break;
        case SHA3_HASH_TYPE_384:
            object->algorithm    = VEXTOKEN_ALGO_HASH_SHA3_384;
            object->digestLength = SHA3_DIGEST_LENGTH_BYTES_384;
            object->blockSize    = SHA3_BLOCK_SIZE_BYTES_384;
            break;
        case SHA3_HASH_TYPE_512:
            object->algorithm    = VEXTOKEN_ALGO_HASH_SHA3_512;
            object->digestLength = SHA3_DIGEST_LENGTH_BYTES_512;
            object->blockSize    = SHA3_BLOCK_SIZE_BYTES_512;
            break;
        default:
            /* Do nothing. Valid hash_type will be checked before this function
             * is called.
             */
            break;
    }

    if (object->key)
    {
        switch (object->hashType)
        {
            case SHA3_HASH_TYPE_224:
                object->algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_224;
                break;
            case SHA3_HASH_TYPE_256:
                object->algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_256;
                break;
            case SHA3_HASH_TYPE_384:
                object->algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_384;
                break;
            case SHA3_HASH_TYPE_512:
                object->algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_512;
                break;
            default:
                break;
        }
    }
}

/*
 *  ======== SHA3XXF3HSM_processIntermediateBlocks ========
 */
static int_fast16_t SHA3XXF3HSM_processIntermediateBlocks(SHA3_Handle handle)
{
    SHA3XXF3HSM_Object *object = handle->object;
    uint32_t blockSize         = blockSizeTable[object->hashType];
    uint32_t transactionLength = SHA3XXF3HSM_largestBlockSizeMultiple(SHA3_dataBytesRemaining, blockSize);
    int_fast16_t status        = SHA3_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;

    /* Make sure to always leave some in buffer, so there's no empty-finalize
     * case.
     */
    if ((SHA3_dataBytesRemaining % blockSize) == 0)
    {
        transactionLength -= blockSize;
    }

    SHA3XXF3HSM_setAlgorithmParams(object);

    object->input       = SHA3_data;
    object->inputLength = transactionLength;
    object->mode        = VEXTOKEN_MODE_HASH_MAC_CONT2CONT;

    /* Populates the HSMXXF3 commandToken as a hash token for a SHA3 operation.
     */
    HSMXXF3_constructSHA3PhysicalToken(object);

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->returnBehavior,
                                    SHA3XXF3HSM_intermediateHashPostProcess,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        /* operationInProgress is still true from the SHA3_addData() call. */

        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking
         * modes (and calls the drivers post-processing fxn) and returns
         * immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
        else
        {
            /* Release the CommonResource semaphore. */
            CommonResourceXXF3_releaseLock();

            /* If there's an error waiting for the result, abort any
             * post-processing and be sure to release locks here. This can only
             * happen in polling mode, so do not call the user's callback.
             */
            object->operationInProgress = false;

            HSMXXF3_releaseLock();
        }
    }
    else
    {
        object->bytesInBuffer   = 0;
        object->bytesProcessed  = 0;
        SHA3_data               = NULL;
        SHA3_dataBytesRemaining = 0;

        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        /* The post-process function will not execute, so this execution path
         * must release the lock and power constraint itself.
         */
        HSMXXF3_releaseLock();

        object->operationInProgress = false;

        /* If there is an HSM token error, clear internal buffers as the
         * segmented hash is now corrupted. Set operationInProgress to false
         * because we are no longer waiting for an HSM result. In this case, we
         * will call the application's callback with error status, because the
         * initial SHA3_addData() call was successful.
         */
        if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, SHA3_STATUS_ERROR);
        }
    }

    return status;
}

/*
 *  ======== SHA3_init ========
 */
void SHA3_init(void)
{
    HSMXXF3_constructRTOSObjects();

    isInitialized = true;
}

/*
 *  ======== SHA3_construct ========
 */
SHA3_Handle SHA3_construct(SHA3_Config *config, const SHA3_Params *params)
{
    SHA3_Handle handle;
    SHA3XXF3HSM_Object *object;
    uintptr_t key;

    handle = (SHA3_Config *)config;
    object = handle->object;

    key = HwiP_disable();

    if (object->isOpen || !isInitialized)
    {
        HwiP_restore(key);
        return NULL;
    }

    object->isOpen              = true;
    object->operationInProgress = false;

    HwiP_restore(key);

    if (params == NULL)
    {
        params = &SHA3_defaultParams;
    }

    /* Because there is no alternative hardware accelerator for SHA3, a NULL
     * handle is returned when the HSM cannot boot successfully.
     */
    if (HSMXXF3_init() != HSMXXF3_STATUS_SUCCESS)
    {
        return NULL;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Reject construction if object->buffer is in PSRAM and the bounce buffer
     * is too small for the largest possible block (SHA3-224, 144 B). This
     * covers all hash types so no per-operation check is needed.
     */
    if (XMEMWFF3_isAddrExternal((uintptr_t)object->buffer) &&
        SHA3XXF3HSM_MAX_BLOCK_SIZE_BYTES > HSMXXF3_inputBounce.size)
    {
        object->isOpen = false;
        return NULL;
    }
#endif

    object->bytesInBuffer  = 0;
    object->bytesProcessed = 0;
    object->returnBehavior = params->returnBehavior;
    object->callbackFxn    = params->callbackFxn;
    object->hashType       = params->hashType;
    object->keyAssetID     = 0U;
    object->tempAssetID    = 0U;

    if (params->returnBehavior == SHA3_RETURN_BEHAVIOR_BLOCKING)
    {
        object->accessTimeout = params->timeout;
    }
    else
    {
        object->accessTimeout = SemaphoreP_NO_WAIT;
    }

    return handle;
}

/*
 *  ======== SHA3_close ========
 */
void SHA3_close(SHA3_Handle handle)
{
    SHA3XXF3HSM_Object *object = handle->object;

    /* This is true only if in callback mode and waiting on a result. */
    if (object->operationInProgress)
    {
        SHA3_cancelOperation(handle);
    }

    if (!HSMXXF3_acquireLock(object->accessTimeout, (uintptr_t)handle))
    {
        return;
    }

    /* SHA3_close() is a void function and cannot return the status of
     * attempting to clean up. The best the driver can do is attempt to remove
     * all assets it created, if they weren't already released like they should
     * have been.
     */
    (void)SHA3XXF3HSM_freeAllAssets(handle);

    HSMXXF3_releaseLock();

    object->isOpen = false;
}

/*
 *  ======== SHA3_addData ========
 */
int_fast16_t SHA3_addData(SHA3_Handle handle, const void *data, size_t length)
{
    /* DMA length check must happen before XMEM chunking so that oversized
     * requests are rejected regardless of memory location.
     */
    if (length > DMA_MAX_TXN_LENGTH)
    {
        return SHA3_STATUS_DMA_ERROR;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When the input is in PSRAM/external flash and exceeds the HSM bounce
     * buffer, split the call into chunks of at most HSMXXF3_inputBounce.size
     * bytes and let the existing init/update state machine in
     * SHA3XXF3HSM_addData stitch them back together. CALLBACK mode is rejected
     * because each chunk would fire its own callback.
     */
    if ((length > HSMXXF3_inputBounce.size) && XMEMWFF3_isAddrExternal((uintptr_t)data))
    {
        SHA3XXF3HSM_Object *object = handle->object;
        const uint8_t *chunk       = (const uint8_t *)data;
        int_fast16_t status;

        if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
        {
            return SHA3_STATUS_UNSUPPORTED;
        }
        while (length > 0U)
        {
            size_t chunkSize = (length > HSMXXF3_inputBounce.size) ? HSMXXF3_inputBounce.size : length;
            status           = SHA3XXF3HSM_addData(handle, chunk, chunkSize);
            if (status != SHA3_STATUS_SUCCESS)
            {
                return status;
            }
            chunk += chunkSize;
            length -= chunkSize;
        }
        return SHA3_STATUS_SUCCESS;
    }
#endif
    return SHA3XXF3HSM_addData(handle, data, length);
}

/*
 *  ======== SHA3XXF3HSM_addData ========
 */
static int_fast16_t SHA3XXF3HSM_addData(SHA3_Handle handle, const void *data, size_t length)
{
    SHA3XXF3HSM_Object *object = handle->object;
    uint32_t blockSize         = blockSizeTable[object->hashType];
    int_fast16_t status        = SHA3_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    uint8_t *bufferTail;
    uint32_t transactionLength;
    uint32_t remainingDataLength;
    const uint8_t *transactionStartAddress;
    const uint8_t *remainingData;
    uint32_t bytesToCopyToBuffer;
    bool tokenSubmitted;
    uintptr_t key;

    /* Try and obtain access to the crypto module. */
    if (!HSMXXF3_acquireLock(object->accessTimeout, (uintptr_t)handle))
    {
        return SHA3_STATUS_RESOURCE_UNAVAILABLE;
    }

    if (length == 0)
    {
        /* No operation, as no new data has been provided. Any cleanup or
         * intermediate hashes necessary would be completed by a prior call to
         * SHA3XXF3HSM_addData. Set tokenSubmitted to false so that we still
         * trigger a callback.
         */
        tokenSubmitted = false;
    }
    else if ((object->bytesInBuffer + length) == blockSize)
    {
        /* We must make sure to always leave some data in buffer, so that
         * there's no empty-finalize case.
         */
        bufferTail = &object->buffer[object->bytesInBuffer];
        memcpy(bufferTail, data, length);
        object->bytesInBuffer += length;
        SHA3_dataBytesRemaining = 0;
        tokenSubmitted          = false;
    }
    else if ((object->bytesInBuffer + length) > blockSize)
    {
        /* We have accumulated enough data to start a transaction. Now the
         * question remains whether we have to merge bytes from the data stream
         * into the buffer first. If so, we do that now, then start a
         * transaction. If the buffer is empty, we can start a transaction on
         * the data stream. Once the transaction is finished, we will decide how
         * to follow up, i.e. copy remaining data into the buffer.
         */

        transactionLength = SHA3XXF3HSM_largestBlockSizeMultiple((object->bytesInBuffer + length), blockSize);
        if (transactionLength > DMA_MAX_TXN_LENGTH)
        {
            HSMXXF3_releaseLock();

            return SHA3_STATUS_DMA_ERROR;
        }

        if (object->bytesInBuffer > 0)
        {
            /* Copy to buffer so it has exactly the block size in it. */
            bufferTail          = &object->buffer[object->bytesInBuffer];
            bytesToCopyToBuffer = blockSize - object->bytesInBuffer;
            memcpy(bufferTail, data, bytesToCopyToBuffer);

            /* The data in buffer right now is going to get consumed. */
            object->bytesInBuffer = 0;

            /* Overwrite transactionLength to just one block's worth of data.
             * Another token will be submitted in
             * SHA3XXF3HSM_processIntermediateBlocks() if necessary. Data is
             * consumed directly from the buffer for the first token.
             */
            transactionLength       = blockSize;
            transactionStartAddress = object->buffer;

            /* This points to the data passed in to SHA3_addData() that isn't
             * being consumed by the first upcoming hash token. It may be used
             * in an intermediate hash, and the remainder data will be buffered.
             */
            SHA3_data               = (uint8_t *)data + bytesToCopyToBuffer;
            SHA3_dataBytesRemaining = length - bytesToCopyToBuffer;
        }
        else
        {
            /* The SHA3_addData() call solely provided more than a blockSize of
             * data. Buffer any remainder.
             */
            transactionStartAddress = data;

            /* Make sure to always leave some in buffer, so there's no
             * empty-finalize case.
             */
            if ((object->bytesInBuffer + length) % blockSize == 0)
            {
                transactionLength -= blockSize;
            }

            remainingData = (uint8_t *)data + transactionLength;

            remainingDataLength = length - transactionLength;

            /* Buffer any remaining data. */
            if (remainingDataLength > 0)
            {
                memcpy(object->buffer, remainingData, remainingDataLength);
                object->bytesInBuffer = remainingDataLength;
            }
        }

        SHA3XXF3HSM_setAlgorithmParams(object);

        object->input       = (uint8_t *)transactionStartAddress;
        object->inputLength = transactionLength;

        /* Finally we need to decide whether this is the first hash operation or
         * a follow-up from a previous one.
         */
        if (object->bytesProcessed > 0)
        {
            object->mode = VEXTOKEN_MODE_HASH_MAC_CONT2CONT;
        }
        else
        {
            object->mode = VEXTOKEN_MODE_HASH_MAC_INIT2CONT;
        }

        /* Populates the HSMXXF3 commandToken as a hash token for a SHA3
         * operation.
         */
        HSMXXF3_constructSHA3PhysicalToken(object);

        /* The postProcessFxn needs access to the transaction length that was
         * determined above.
         */
        addDataTransactionLength = transactionLength;

        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master
         * transactions. For now, there is no protection against I2S, so I2S
         * must not be used at the same time as the HSM.
         */
        if (!CommonResourceXXF3_acquireLock(object->accessTimeout))
        {
            HSMXXF3_releaseLock();

            return SHA3_STATUS_RESOURCE_UNAVAILABLE;
        }

        /* Starting the operation and setting object->operationInProgress must
         * be atomic.
         */
        key = HwiP_disable();

        hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->returnBehavior,
                                        SHA3XXF3HSM_addDataPostProcess,
                                        (uintptr_t)handle);

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            object->operationInProgress = true;

            HwiP_restore(key);

            tokenSubmitted = true;

            /* The return status is overwritten if this token submission yields
             * an error, or if SHA3XXF3HSM_processIntermediateBlocks() gets called
             * and returns an error.
             */

            /* Handles post command token submission mechanism. Waits for a
             * result token from the HSM IP in polling and blocking modes (and
             * calls the drivers post-processing fxn) and returns immediately
             * when in callback mode.
             */
            hsmRetval = HSMXXF3_waitForResult();

            if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
            {
                status = object->returnStatus;
            }
            else
            {
                /* If there's an error waiting for the result, abort any
                 * post-processing and be sure to release locks here. This can
                 * only happen in polling mode, so do not call the user's
                 * callback.
                 */

                object->operationInProgress = false;

                /* Release the CommonResource semaphore. */
                CommonResourceXXF3_releaseLock();

                HSMXXF3_releaseLock();
            }
        }
        else
        {
            HwiP_restore(key);

            /* If there is an HSM token error, clear internal buffers as the
             * segmented hash is now corrupted.
             */
            SHA3_reset(handle);

            tokenSubmitted = false;

            status = SHA3_STATUS_ERROR;
        }
    }
    else
    {
        /* No action required by the HSM. */
        bufferTail = &object->buffer[object->bytesInBuffer];
        memcpy(bufferTail, data, length);
        object->bytesInBuffer += length;
        SHA3_dataBytesRemaining = 0;
        status                  = SHA3_STATUS_SUCCESS;
        tokenSubmitted          = false;
    }

    if (!tokenSubmitted)
    {
        object->returnStatus = SHA3_STATUS_SUCCESS;

        status = SHA3_STATUS_SUCCESS;

        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        HSMXXF3_releaseLock();

        /* Since there's no HSM operation ongoing, we can call the application's
         * callback function now. Make sure not to call it if there was a token
         * submission error.
         */
        if (status == SHA3_STATUS_SUCCESS && object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status);
        }
    }

    return status;
}

/*
 *  ======== SHA3_finalize ========
 */
int_fast16_t SHA3_finalize(SHA3_Handle handle, void *digest)
{
    return SHA3XXF3HSM_finalize(handle, digest);
}

/*
 *  ======== SHA3XXF3HSM_finalize ========
 */
static int_fast16_t SHA3XXF3HSM_finalize(SHA3_Handle handle, void *digest)
{
    SHA3XXF3HSM_Object *object = handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    uintptr_t key;

    SHA3XXF3HSM_setAlgorithmParams(object);

    object->input       = object->buffer;
    object->output      = digest;
    object->inputLength = object->bytesInBuffer;

    if (object->bytesProcessed == 0)
    {
        /* Since no hash operation has been performed yet and no intermediate
         * state is available, we have to perform a full hash operation on the
         * data in buffer.
         */
        object->mode            = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
        object->totalDataLength = (uint32_t)object->bytesInBuffer;
    }
    else if (object->bytesInBuffer > 0)
    {
        /* We've already performed a hash, so there's an intermediate state,
         * but there's also data in the buffer.
         */
        object->mode            = (uint32_t)VEXTOKEN_MODE_HASH_MAC_CONT2FINAL;
        object->totalDataLength = ((uint32_t)object->bytesInBuffer) + object->bytesProcessed;
    }
    else
    {
        return SHA3_STATUS_ERROR;
    }

    /* Try and obtain access to the crypto module. */
    if (!HSMXXF3_acquireLock(object->accessTimeout, (uintptr_t)handle))
    {
        return SHA3_STATUS_RESOURCE_UNAVAILABLE;
    }

    /* Populates the HSMXXF3 commandToken as a hash token for a SHA3 operation.
     */
    HSMXXF3_constructSHA3PhysicalToken(object);

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions.
     */
    if (!CommonResourceXXF3_acquireLock(object->accessTimeout))
    {
        HSMXXF3_releaseLock();

        return SHA3_STATUS_RESOURCE_UNAVAILABLE;
    }

    key = HwiP_disable();

    /* Exchange token to hash the remainder data. */
    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->returnBehavior,
                                    SHA3XXF3HSM_finalizePostProcess,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        object->operationInProgress = true;

        HwiP_restore(key);

        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking
         * modes (and calls the drivers post-processing fxn) and returns
         * immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
        else
        {
            /* Release the CommonResource semaphore. */
            CommonResourceXXF3_releaseLock();

            /* If there's an error waiting for the result, abort any
             * post-processing and be sure to release locks here. This can only
             * happen in polling mode, so do not call the user's callback.
             */
            HSMXXF3_releaseLock();
        }
    }
    else
    {
        HwiP_restore(key);

        status = SHA3_STATUS_ERROR;

        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        /* The application's callback is not called in this error case. */

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== SHA3_hashData ========
 */
int_fast16_t SHA3_hashData(SHA3_Handle handle, const void *data, size_t dataLength, void *digest)
{
    /* DMA length check must happen before XMEM chunking so that oversized
     * requests are rejected regardless of memory location.
     */
    if (dataLength > DMA_MAX_TXN_LENGTH)
    {
        return SHA3_STATUS_DMA_ERROR;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Same chunking strategy as SHA3_addData: when the input is in external
     * memory and too large for the bounce buffer, fall back to the segmented
     * init/update/finalize path. SHA3_addData below already chunks internally.
     */
    if ((dataLength > HSMXXF3_inputBounce.size) && XMEMWFF3_isAddrExternal((uintptr_t)data))
    {
        SHA3XXF3HSM_Object *object = handle->object;
        int_fast16_t status;

        if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
        {
            return SHA3_STATUS_UNSUPPORTED;
        }
        SHA3_reset(handle);
        status = SHA3_addData(handle, data, dataLength);
        if (status != SHA3_STATUS_SUCCESS)
        {
            return status;
        }
        return SHA3_finalize(handle, digest);
    }
#endif
    return SHA3XXF3HSM_hashData(handle, data, dataLength, digest);
}

/*
 *  ======== SHA3XXF3HSM_hashData ========
 */
static int_fast16_t SHA3XXF3HSM_hashData(SHA3_Handle handle, const void *data, size_t dataLength, void *digest)
{
    SHA3XXF3HSM_Object *object = handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;
    int_fast16_t hsmRetval     = HSMXXF3_STATUS_ERROR;
    uintptr_t key;

    if (dataLength > DMA_MAX_TXN_LENGTH)
    {
        return SHA3_STATUS_DMA_ERROR;
    }

    /* Try and obtain access to the crypto module. */
    if (!HSMXXF3_acquireLock(object->accessTimeout, (uintptr_t)handle))
    {
        return SHA3_STATUS_RESOURCE_UNAVAILABLE;
    }

    /* Calls to SHA3_hashData() clear intermediate data from a previous partial
     * operation started with SHA3_addData().
     */
    object->bytesInBuffer   = 0;
    object->bytesProcessed  = 0;
    SHA3_data               = NULL;
    SHA3_dataBytesRemaining = 0;
    object->input           = (uint8_t *)data;
    object->output          = digest;
    object->inputLength     = dataLength;
    object->totalDataLength = object->inputLength;
    object->mode            = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
    object->key             = NULL;
    object->returnStatus    = SHA3_STATUS_SUCCESS;

    /* Algorithm (HASH or HMAC) depends on object->key value. */
    SHA3XXF3HSM_setAlgorithmParams(object);

    /* Populates the HSMXXF3 commandToken as a hash token for a SHA3 operation.
     */
    HSMXXF3_constructSHA3PhysicalToken(object);

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions.
     */
    if (!CommonResourceXXF3_acquireLock(object->accessTimeout))
    {
        HSMXXF3_releaseLock();

        return SHA3_STATUS_RESOURCE_UNAVAILABLE;
    }

    key = HwiP_disable();

    hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->returnBehavior,
                                    SHA3XXF3HSM_hashPostProcess,
                                    (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        object->operationInProgress = true;

        HwiP_restore(key);

        /* Handles post command token submission mechanism.
         * Waits for a result token from the HSM IP in polling and blocking
         * modes (and calls the drivers post-processing fxn) and returns
         * immediately when in callback mode.
         */
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
        else
        {
            /* Release the CommonResource semaphore. */
            CommonResourceXXF3_releaseLock();

            HSMXXF3_releaseLock();
        }
    }
    else
    {
        HwiP_restore(key);

        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        HSMXXF3_releaseLock();
    }

    return status;
}

/*
 *  ======== SHA3_reset ========
 */
void SHA3_reset(SHA3_Handle handle)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;

    /* This is only true when the handle is in callback mode, and the result has
     * not yet been received.
     */
    if (object->operationInProgress == true)
    {
        SHA3_cancelOperation(handle);
    }

    /* Clear internal buffers relevant to a segmented hash from prior
     * SHA3_addData() calls. SHA3_hashData() also clears intermediate data.
     */
    object->bytesInBuffer   = 0;
    object->bytesProcessed  = 0;
    SHA3_data               = NULL;
    SHA3_dataBytesRemaining = 0;
}

/*
 *  ======== SHA3_cancelOperation ========
 */
int_fast16_t SHA3_cancelOperation(SHA3_Handle handle)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;

    object->bytesInBuffer   = 0;
    object->bytesProcessed  = 0;
    SHA3_data               = NULL;
    SHA3_dataBytesRemaining = 0;

    if (!object->operationInProgress)
    {
        /* Do nothing. */
    }
    else
    {
        object->operationInProgress = false;

        /* Since the HSM cannot cancel an in-progress token, we must wait for
         * the result to allow for subsequent token submissions to succeed.
         */
        (void)HSMXXF3_cancelOperation();

        if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, SHA3_STATUS_CANCELED);
        }
    }

    return SHA3_STATUS_SUCCESS;
}

/*
 *  ======== SHA3_setHashType ========
 */
int_fast16_t SHA3_setHashType(SHA3_Handle handle, SHA3_HashType type)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_SUCCESS;

    if ((object->operationInProgress) || (object->bytesProcessed > 0))
    {
        status = SHA3_STATUS_ERROR;
    }
    else
    {
        object->hashType = type;
    }

    return status;
}

/*
 *  ======== SHA3_setupHmac ========
 */
int_fast16_t SHA3_setupHmac(SHA3_Handle handle, const CryptoKey *key)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;

    object->mode         = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2CONT;
    object->key          = (CryptoKey *)key;
    object->keyAssetID   = 0U;
    object->tempAssetID  = 0U;
    object->returnStatus = SHA3_STATUS_SUCCESS;

    /* Algorithm (HASH or HMAC) depends on object->key value. */
    SHA3XXF3HSM_setAlgorithmParams(object);

    if ((object->key->encoding == CryptoKey_PLAINTEXT_HSM) || (object->key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        if (!HSMXXF3_acquireLock(object->accessTimeout, (uintptr_t)handle))
        {
            return SHA3_STATUS_RESOURCE_UNAVAILABLE;
        }

        status = SHA3XXF3HSM_createAndLoadKeyAssetID(handle);

        if (status == SHA3_STATUS_SUCCESS)
        {
            status = SHA3XXF3HSM_CreateTempAssetID(handle);
        }

        /* If an error occurred at any point AFTER successfully creating the key
         * asset, then there is an allocated asset that the driver must clean
         * up.
         */
        if (status != SHA3_STATUS_SUCCESS)
        {
            (void)SHA3XXF3HSM_freeAllAssets(handle);
        }

        HSMXXF3_releaseLock();
    }

    if ((status == SHA3_STATUS_SUCCESS) && (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK))
    {
        object->callbackFxn(handle, object->returnStatus);
    }

    return status;
}

/*
 *  ======== SHA3_finalizeHmac ========
 */
int_fast16_t SHA3_finalizeHmac(SHA3_Handle handle, void *hmac)
{
    return SHA3XXF3HSM_finalize(handle, hmac);
}

/*
 *  ======== SHA3_hmac ========
 */
int_fast16_t SHA3_hmac(SHA3_Handle handle, const CryptoKey *key, const void *data, size_t size, void *hmac)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* When input data is in external memory and exceeds the bounce buffer,
     * fall back to the segmented path (setupHmac + addData + finalizeHmac).
     * CALLBACK mode is unsupported for this path because addData would fire
     * intermediate callbacks.
     */
    if ((size > HSMXXF3_inputBounce.size) && XMEMWFF3_isAddrExternal((uintptr_t)data))
    {
        if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
        {
            return SHA3_STATUS_UNSUPPORTED;
        }
        status = SHA3_setupHmac(handle, key);
        if (status != SHA3_STATUS_SUCCESS)
        {
            return status;
        }
        status = SHA3_addData(handle, data, size);
        if (status != SHA3_STATUS_SUCCESS)
        {
            return status;
        }
        return SHA3_finalizeHmac(handle, hmac);
    }
#endif

    object->bytesInBuffer   = 0;
    object->bytesProcessed  = 0;
    SHA3_data               = NULL;
    SHA3_dataBytesRemaining = 0;
    object->input           = (uint8_t *)data;
    object->output          = hmac;
    object->inputLength     = size;
    object->totalDataLength = object->inputLength;
    object->mode            = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
    object->key             = (CryptoKey *)key;
    object->keyAssetID      = 0U;
    object->tempAssetID     = 0U;
    object->returnStatus    = SHA3_STATUS_SUCCESS;

    /* Algorithm (HASH or HMAC) depends on object->key value. */
    SHA3XXF3HSM_setAlgorithmParams(object);

    if ((object->key->encoding == CryptoKey_PLAINTEXT_HSM) || (object->key->encoding == CryptoKey_KEYSTORE_HSM))
    {
        if (!HSMXXF3_acquireLock(object->accessTimeout, (uintptr_t)handle))
        {
            return SHA3_STATUS_RESOURCE_UNAVAILABLE;
        }

        status = SHA3XXF3HSM_createAndLoadKeyAssetID(handle);

        if (status != SHA3_STATUS_SUCCESS)
        {
            /* If an error occurred at any point AFTER successfully creating the
             * key asset, then there is an allocated asset that the driver must
             * clean up.
             */
            (void)SHA3XXF3HSM_freeAllAssets(handle);

            HSMXXF3_releaseLock();
        }
    }

    if (status == SHA3_STATUS_SUCCESS)
    {
        status = SHA3XXF3HSM_processOneStepAndFinalizeOperation(handle);
    }

    return status;
}

/*
 *  ======== SHA3XXF3HSM_oneStepAndFinalizePostProcessing ========
 */
static inline void SHA3XXF3HSM_oneStepAndFinalizePostProcessing(uintptr_t arg0)
{
    SHA3_Handle handle         = (SHA3_Handle)arg0;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int32_t physicalResult     = HSMXXF3_getResultCode();
    int_fast16_t status        = SHA3_STATUS_ERROR;

    if ((physicalResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = SHA3_STATUS_SUCCESS;

        HSMXXF3_getResultDigest(object->output, object->digestLength);
    }
    else
    {
        status = SHA3_STATUS_ERROR;
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    if (SHA3XXF3HSM_freeAllAssets(handle) != SHA3_STATUS_SUCCESS)
    {
        object->returnStatus = SHA3_STATUS_ERROR;
    }
    else
    {
        object->returnStatus = status;
    }

    HSMXXF3_releaseLock();

    if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->returnStatus);
    }
}

/*
 *  ======== SHA3XXF3HSM_processOneStepAndFinalizeOperation ========
 */
static int_fast16_t SHA3XXF3HSM_processOneStepAndFinalizeOperation(SHA3_Handle handle)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;

    (void)HSMXXF3_constructSHA3PhysicalToken(object);

    /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions.
     */
    if (!CommonResourceXXF3_acquireLock(object->accessTimeout))
    {
        HSMXXF3_releaseLock();

        return SHA3_STATUS_RESOURCE_UNAVAILABLE;
    }

    int_fast16_t hsmRetval = HSMXXF3_submitToken((HSMXXF3_ReturnBehavior)object->returnBehavior,
                                                 SHA3XXF3HSM_oneStepAndFinalizePostProcessing,
                                                 (uintptr_t)handle);

    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
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
 *  ======== SHA3XXF3HSM_hashPostProcess ========
 */
static void SHA3XXF3HSM_hashPostProcess(uintptr_t driverHandle)
{
    SHA3_Handle handle         = (SHA3_Handle)driverHandle;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int32_t physicalResult     = HSMXXF3_getResultCode();
    int_fast16_t status        = SHA3_STATUS_ERROR;

    /* tokenResult carries information regarding the operation result status as
     * well as many other information such as wether the operation is FIPS
     * approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract
     * only relevant information to an operation's result status.
     */
    if ((physicalResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = SHA3_STATUS_SUCCESS;

        HSMXXF3_getResultDigest(object->output, object->digestLength);
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    object->returnStatus = status;

    object->operationInProgress = false;

    HSMXXF3_releaseLock();

    if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->returnStatus);
    }
}

/*
 *  ======== SHA3XXF3HSM_finalizePostProcess ========
 */
static void SHA3XXF3HSM_finalizePostProcess(uintptr_t driverHandle)
{
    SHA3_Handle handle         = (SHA3_Handle)driverHandle;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int32_t physicalResult     = HSMXXF3_getResultCode();

    /* tokenResult carries information regarding the operation result status as
     * well as many other information such as wether the operation is FIPS
     * approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract
     * only relevant information to an operation's result status.
     */
    if ((physicalResult & HSMXXF3_RETVAL_MASK) > 0)
    {
        object->returnStatus = SHA3_STATUS_ERROR;
    }
    else
    {
        object->returnStatus = SHA3_STATUS_SUCCESS;
        HSMXXF3_getResultDigest(object->output, object->digestLength);
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    /* The multi-step operation is now complete, so reset any values tracking
     * data from the operation.
     */
    object->bytesProcessed  = 0;
    object->bytesInBuffer   = 0;
    SHA3_data               = NULL;
    SHA3_dataBytesRemaining = 0;

    if (object->key)
    {
        if (SHA3XXF3HSM_freeAllAssets(handle) != SHA3_STATUS_SUCCESS)
        {
            object->returnStatus = SHA3_STATUS_ERROR;
        }
    }

    HSMXXF3_releaseLock();

    object->operationInProgress = false;

    if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->returnStatus);
    }
}

/*
 *  ======== SHA3XXF3HSM_addDataPostProcess ========
 */
static void SHA3XXF3HSM_addDataPostProcess(uintptr_t driverHandle)
{
    SHA3_Handle handle         = (SHA3_Handle)driverHandle;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    uint32_t blockSize         = blockSizeTable[object->hashType];
    int32_t physicalResult     = HSMXXF3_getResultCode();

    /* tokenResult carries information regarding the operation result status as
     * well as many other information such as wether the operation is FIPS
     * approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract
     * only relevant information to an operation's result status.
     */
    if ((physicalResult & HSMXXF3_RETVAL_MASK) > 0)
    {
        object->returnStatus = SHA3_STATUS_ERROR;

        /* Release the CommonResource semaphore. */
        CommonResourceXXF3_releaseLock();

        SHA3_reset(handle);

        HSMXXF3_releaseLock();

        object->operationInProgress = false;

        if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, object->returnStatus);
        }
    }
    else
    {
        object->returnStatus = SHA3_STATUS_SUCCESS;

        /* Copy intermediate state from HSM result token. */
        HSMXXF3_getResultHashState(object->intermediateState, SHA3XXF3HSM_INTERMEDIATE_STATE_BYTES);

        object->bytesProcessed += addDataTransactionLength;

        if (SHA3_dataBytesRemaining > blockSize)
        {
            /* The post-processing function for
             * SHA3XXF3HSM_processIntermediateBlocks will be responsible for
             * calling the application's callback function. If there is a token
             * submission error on the intermediate hash, then the user's
             * callback will instead be called with status SHA3_STATUS_ERROR.
             */
            object->returnStatus = SHA3XXF3HSM_processIntermediateBlocks(handle);
        }
        else
        {
            /* Release the CommonResource semaphore. */
            CommonResourceXXF3_releaseLock();

            if (SHA3_dataBytesRemaining > 0)
            {
                memcpy(object->buffer, SHA3_data, SHA3_dataBytesRemaining);
                object->bytesInBuffer = SHA3_dataBytesRemaining;
            }

            object->returnStatus = SHA3_STATUS_SUCCESS;

            HSMXXF3_releaseLock();

            object->operationInProgress = false;

            if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
            {
                object->callbackFxn(handle, SHA3_STATUS_SUCCESS);
            }
        }
    }
}

/*
 *  ======== SHA3XXF3HSM_intermediateHashPostProcess ========
 */
static void SHA3XXF3HSM_intermediateHashPostProcess(uintptr_t driverHandle)
{
    SHA3_Handle handle         = (SHA3_Handle)driverHandle;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    uint32_t blockSize         = blockSizeTable[object->hashType];
    uint32_t transactionLength = SHA3XXF3HSM_largestBlockSizeMultiple(SHA3_dataBytesRemaining, blockSize);
    int32_t physicalResult     = HSMXXF3_getResultCode();
    int_fast16_t status        = SHA3_STATUS_ERROR;

    /* tokenResult carries information regarding the operation result status as
     * well as many other information such as wether the operation is FIPS
     * approved or not. The code below applies an HSMXXF3_RETVAL_MASK to extract
     * only relevant information to an operation's result status.
     */
    if ((physicalResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        if ((SHA3_dataBytesRemaining % blockSize) == 0)
        {
            transactionLength -= blockSize;
        }

        /* Copy intermediate state from HSM result token. */
        HSMXXF3_getResultHashState(object->intermediateState, SHA3XXF3HSM_INTERMEDIATE_STATE_BYTES);

        object->bytesProcessed += transactionLength;

        /* Buffer any remaining data. */
        if (SHA3_dataBytesRemaining - transactionLength > 0)
        {
            memcpy(object->buffer, SHA3_data + transactionLength, (SHA3_dataBytesRemaining - transactionLength));
            object->bytesInBuffer += (SHA3_dataBytesRemaining - transactionLength);
        }

        /* No more intermediate hash needed. */
        SHA3_dataBytesRemaining = 0;

        status = SHA3_STATUS_SUCCESS;
    }

    /* Release the CommonResource semaphore. */
    CommonResourceXXF3_releaseLock();

    object->returnStatus = status;

    if (status == SHA3_STATUS_ERROR)
    {
        SHA3_reset(handle);
    }

    HSMXXF3_releaseLock();

    object->operationInProgress = false;

    if (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->returnStatus);
    }
}

/******************************************************************************/

/*
 *  ======== SHA3XXF3HSM_CreateKeyAssetPostProcessing ========
 */
static inline void SHA3XXF3HSM_CreateKeyAssetPostProcessing(uintptr_t arg0)
{
    SHA3_Handle handle         = (SHA3_Handle)arg0;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->keyAssetID = HSMXXF3_getResultAssetID();
        status             = SHA3_STATUS_SUCCESS;
    }

    object->returnStatus = status;
}

/*
 *  ======== SHA3XXF3HSM_createKeyAsset ========
 */
static int_fast16_t SHA3XXF3HSM_createKeyAsset(SHA3_Handle handle)
{
    int_fast16_t status        = SHA3_STATUS_ERROR;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    uint64_t assetPolicy       = 0x0;
    uint32_t keyLength         = 0U;

    if (object->key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        keyLength = object->key->u.plaintext.keyLength;
    }
#if (ENABLE_KEY_STORAGE == 1)
    else if (object->key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        keyLength = object->key->u.keyStore.keyLength;
    }
#endif

    /* Operation (Lower 16-bits + general Operation) + Direction. No Mode. */
    assetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_SCDIRENCGEN;

    switch (object->hashType)
    {
        case SHA3_HASH_TYPE_224:
            assetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_224;
            break;
        case SHA3_HASH_TYPE_256:
            assetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_256;
            break;
        case SHA3_HASH_TYPE_384:
            assetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_384;
            break;
        case SHA3_HASH_TYPE_512:
            assetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_512;
            break;
        default:
            /* Do nothing. Valid hash_type will be checked before this function
             * is called.
             */
            break;
    }

    HSMXXF3_constructCreateAssetToken(assetPolicy, keyLength);

    int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                                 SHA3XXF3HSM_CreateKeyAssetPostProcessing,
                                                 (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
    }

    return status;
}

/*
 *  ======== SHA3XXF3HSM_LoadKeyAssetPostProcessing ========
 */
static inline void SHA3XXF3HSM_LoadKeyAssetPostProcessing(uintptr_t arg0)
{
    SHA3_Handle handle         = (SHA3_Handle)arg0;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = SHA3_STATUS_SUCCESS;
    }

    object->returnStatus = status;
}

/*
 *  ======== SHA3XXF3HSM_LoadKeyAsset ========
 */
static int_fast16_t SHA3XXF3HSM_LoadKeyAsset(SHA3_Handle handle, uint8_t *key)
{
    int_fast16_t status        = SHA3_STATUS_ERROR;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    uint32_t keyLength         = 0U;

    if (object->key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        keyLength = object->key->u.plaintext.keyLength;
    }
#if (ENABLE_KEY_STORAGE == 1)
    else if (object->key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        keyLength = object->key->u.keyStore.keyLength;
    }
#endif

    /* Constructing an HSM token is a void operation that cannot fail. */
    (void)HSMXXF3_constructLoadPlaintextAssetToken(key, keyLength, object->keyAssetID);

    int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                                 SHA3XXF3HSM_LoadKeyAssetPostProcessing,
                                                 (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
    }

    return status;
}

/*
 *  ======== SHA3XXF3HSM_createAndLoadKeyAssetID ========
 */
static int_fast16_t SHA3XXF3HSM_createAndLoadKeyAssetID(SHA3_Handle handle)
{
    int_fast16_t status        = SHA3_STATUS_ERROR;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    uint8_t *keyMaterial       = NULL;
#if (ENABLE_KEY_STORAGE == 1)
    uint8_t KeyStore_keyingMaterial[SHA3XXF3HSM_MAX_HMAC_KEY_LENGTH_BYTES];
    KeyStore_PSA_KeyUsage usage = KEYSTORE_PSA_KEY_USAGE_SIGN_MESSAGE;
    KeyStore_PSA_Algorithm alg;

    switch (object->hashType)
    {
        case SHA3_HASH_TYPE_224:
            alg = KEYSTORE_PSA_ALG_HMAC(KEYSTORE_PSA_ALG_SHA3_224);
            break;
        case SHA3_HASH_TYPE_256:
            alg = KEYSTORE_PSA_ALG_HMAC(KEYSTORE_PSA_ALG_SHA3_256);
            break;
        case SHA3_HASH_TYPE_384:
            alg = KEYSTORE_PSA_ALG_HMAC(KEYSTORE_PSA_ALG_SHA3_384);
            break;
        case SHA3_HASH_TYPE_512:
            alg = KEYSTORE_PSA_ALG_HMAC(KEYSTORE_PSA_ALG_SHA3_512);
            break;
        default:
            return SHA3_STATUS_ERROR;
            break;
    }
#endif

    if (object->key->encoding == CryptoKey_PLAINTEXT_HSM)
    {
        keyMaterial = object->key->u.plaintext.keyMaterial;
    }
#if (ENABLE_KEY_STORAGE == 1)
    else if (object->key->encoding == CryptoKey_KEYSTORE_HSM)
    {
        keyMaterial = &KeyStore_keyingMaterial[0];

        status = KeyStore_PSA_retrieveFromKeyStore(object->key,
                                                   &KeyStore_keyingMaterial[0],
                                                   sizeof(KeyStore_keyingMaterial),
                                                   &object->keyAssetID,
                                                   alg,
                                                   usage);

        if (status != KEYSTORE_PSA_STATUS_SUCCESS)
        {
            return status;
        }
        else if (object->keyAssetID != 0)
        {
            /* In this case, we already retrieved an asset from KeyStore, so we
             * don't need the driver to create and load an asset itself. We must
             * mark this before validating key sizes to ensure we cleanup
             * properly in the case that key size validation fails.
             */
            object->driverCreatedKeyAsset = false;
        }
        else
        {
            /* Key material has been retrieved in plaintext. */
        }
    }
#endif
    else
    {
        /* Invalid key encoding. */
        return SHA3_STATUS_ERROR;
    }

    /* If we haven't already retrieved an asset directly from KeyStore, then the
     * driver will have to create and load an asset itself.
     */
    if (object->keyAssetID == 0)
    {
        status = SHA3XXF3HSM_createKeyAsset(handle);

        if (status == SHA3_STATUS_SUCCESS)
        {
            /* Due to errata SYS_211, get HSM lock to avoid AHB bus master
             * transactions. For now, there is no protection against I2S, so I2S
             * must not be used at the same time as the HSM.
             */
            if (!CommonResourceXXF3_acquireLock(object->accessTimeout))
            {
                return SHA3_STATUS_RESOURCE_UNAVAILABLE;
            }

            /* Now that the driver has successfully created an asset,
             * object->keyAssetID is now non-zero. If any failure condition
             * happens after this moment, the cleanup will expect
             * object->driverCreatedKeyAsset to be accurate, since the
             * keyAssetID will reflect that there is an asset to free, and the
             * cleanup will need to know how to do that.
             */
            object->driverCreatedKeyAsset = true;

            status = SHA3XXF3HSM_LoadKeyAsset(handle, keyMaterial);

            /* Release the CommonResource semaphore. */
            CommonResourceXXF3_releaseLock();
        }
        else
        {
            /* object->keyAssetID is still 0, so cleanup knows there's no asset
             * to free.
             */
        }
    }

    return status;
}

/*
 *  ======== SHA3XXF3HSM_CreateTempAssetPostProcessing ========
 */
static inline void SHA3XXF3HSM_CreateTempAssetPostProcessing(uintptr_t arg0)
{
    SHA3_Handle handle         = (SHA3_Handle)arg0;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;
    int32_t tokenResult        = HSMXXF3_getResultCode();

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->tempAssetID = HSMXXF3_getResultAssetID();
        status              = SHA3_STATUS_SUCCESS;
    }

    object->returnStatus = status;
}

/*
 *  ======== SHA3XXF3HSM_CreateTempAssetID ========
 */
static int_fast16_t SHA3XXF3HSM_CreateTempAssetID(SHA3_Handle handle)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;
    uint64_t assetPolicy       = 0x0;

    /* Operation (Lower 16-bits + general Operation) + Direction. No Mode. */
    assetPolicy = EIP130_ASSET_POLICY_SYM_TEMP | EIP130_ASSET_POLICY_SCUIMACHASH | EIP130_ASSET_POLICY_SCDIRENCGEN;

    switch (object->hashType)
    {
        case SHA3_HASH_TYPE_224:
            assetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_224;
            break;
        case SHA3_HASH_TYPE_256:
            assetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_256;
            break;
        case SHA3_HASH_TYPE_384:
            assetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_384;
            break;
        case SHA3_HASH_TYPE_512:
            assetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_512;
            break;
        default:
            /* Do nothing. Valid hash_type will be checked before this function
             * is called.
             */
            break;
    }

    HSMXXF3_constructCreateAssetToken(assetPolicy, SHA3XXF3HSM_INTERMEDIATE_STATE_BYTES);

    int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                                 SHA3XXF3HSM_CreateTempAssetPostProcessing,
                                                 (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
    }

    return status;
}

/*
 *  ======== SHA3XXF3HSM_FreeAssetPostProcessing ========
 */
static inline void SHA3XXF3HSM_FreeAssetPostProcessing(uintptr_t arg0)
{
    SHA3_Handle handle         = (SHA3_Handle)arg0;
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;
    int32_t physicalResult     = HSMXXF3_getResultCode();

    if ((physicalResult & HSMXXF3_RETVAL_MASK) == EIP130TOKEN_RESULT_SUCCESS)
    {
        status = SHA3_STATUS_SUCCESS;
    }

    object->returnStatus = status;

    if ((status == SHA3_STATUS_ERROR) && (object->returnBehavior == SHA3_RETURN_BEHAVIOR_CALLBACK))
    {
        object->callbackFxn(handle, object->returnStatus);
    }
}

/*
 *  ======== SHA3XXF3HSM_freeAssetID ========
 */
static int_fast16_t SHA3XXF3HSM_freeAssetID(SHA3_Handle handle, uint32_t AssetID)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_ERROR;

    (void)HSMXXF3_constructDeleteAssetToken(AssetID);

    int_fast16_t hsmRetval = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING,
                                                 SHA3XXF3HSM_FreeAssetPostProcessing,
                                                 (uintptr_t)handle);
    if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMXXF3_waitForResult();

        if (hsmRetval == HSMXXF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
    }

    return status;
}

/*
 *  ======== SHA3XXF3HSM_freeAllAssets ========
 */
static int_fast16_t SHA3XXF3HSM_freeAllAssets(SHA3_Handle handle)
{
    SHA3XXF3HSM_Object *object = (SHA3XXF3HSM_Object *)handle->object;
    int_fast16_t status        = SHA3_STATUS_SUCCESS;

    if (object->keyAssetID != 0)
    {
        /* If the object has a stored keyAssetID, then driverCreatedKeyAsset
         * MUST be set. It can only be false if KeyStore is enabled. If it is
         * false, it means that we retrieved an asset directly from KeyStore, so
         * the driver should not free the asset. Instead, the driver should
         * direct KeyStore to free the asset (which will perform the necessary
         * persistence check and only free the asset if it should be freed).
         */
        if (object->driverCreatedKeyAsset == true)
        {
            status = SHA3XXF3HSM_freeAssetID(handle, object->keyAssetID);
            if (status == SHA3_STATUS_SUCCESS)
            {
                object->keyAssetID = 0;
            }
        }
#if (ENABLE_KEY_STORAGE == 1)
        else
        {
            KeyStore_PSA_KeyFileId keyID;

            GET_KEY_ID(keyID, object->key->u.keyStore.keyID);

            status = KeyStore_PSA_assetPostProcessing(keyID);
            if (status == KEYSTORE_PSA_STATUS_SUCCESS)
            {
                object->keyAssetID = 0;
            }
        }
#endif
    }

    if (object->tempAssetID != 0)
    {
        status = SHA3XXF3HSM_freeAssetID(handle, object->tempAssetID);
        if (status == SHA3_STATUS_SUCCESS)
        {
            object->tempAssetID = 0;
        }
    }

    return status;
}
