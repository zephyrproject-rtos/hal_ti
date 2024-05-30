/*
 * Copyright (c) 2022-2024, Texas Instruments Incorporated
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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <third_party/tfm/secure_fw/partitions/internal_trusted_storage/tfm_internal_trusted_storage.h> /* tfm_its_init() */

#include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
#include <third_party/mbedtls/include/mbedtls/memory_buffer_alloc.h>
#include <third_party/mbedtls/include/mbedtls/platform.h>

/* Static buffer for alloc/free. The buffer size is allocated based on
 * assumption of 16 largest symmetric keys (32B) and 16 largest asymmetric
 * public keys (133B) that can be supported by KeyStore, with surplus bytes for
 * additional calloc calls within mbedTLS.
 */
uint8_t allocBuffer[3072];

extern psa_status_t psa_get_and_lock_key_slot_with_policy(mbedtls_svc_key_id_t key,
                                                          psa_key_slot_t **p_slot,
                                                          psa_key_usage_t usage,
                                                          psa_algorithm_t alg);

KeyStore_accessSemaphoreObject KeyStore_semaphoreObject = {.isAcquired = false, .isInitialized = false};

/** @brief Key handle identifier from mbedTLS 'psa_key_handle_t'. */
typedef psa_key_handle_t KeyStore_PSA_KeyHandle;

/* Flag to prevent multiple initialization of KeyStore driver */
static bool isKeyStoreInitialized = false;

/*!
 *  @cond NODOC
 *  @brief Non-public functions required by other drivers
 *
 *  The functions may be required by other drivers and are required to
 *  ensure thread-safe behavior across multiple calls.
 *  @endcond
 */

/*
 *  ======== KeyStore_acquireLock ========
 */
static inline bool KeyStore_acquireLock(void)
{
    SemaphoreP_Status resourceAcquired;

    /* Try and obtain access to the KeyStore module */
    resourceAcquired = SemaphoreP_pend(&KeyStore_semaphoreObject.KeyStore_accessSemaphore, SemaphoreP_WAIT_FOREVER);

    return resourceAcquired == SemaphoreP_OK;
}

/*
 *  ======== KeyStore_releaseLock ========
 */
static inline void KeyStore_releaseLock(void)
{
    SemaphoreP_post(&KeyStore_semaphoreObject.KeyStore_accessSemaphore);
}

/** \defgroup key_management Key management
 * @{
 */

/*
 *  ======== KeyStore_PSA_purgeKey ========
 */
int_fast16_t KeyStore_PSA_purgeKey(KeyStore_PSA_KeyFileId key)
{
    int_fast16_t status = KEYSTORE_PSA_STATUS_GENERIC_ERROR;

    if (!KeyStore_semaphoreObject.isAcquired)
    {
        if (!KeyStore_acquireLock())
        {
            status = KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE;
            return status;
        }
    }

    /*
     * Only purge persistent keys, volatile keys do not have to be purged.
     * Both type of keys will be destroyed after use by the application using
     * KeyStore_PSA_destroyKey()
     */
#if defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)
    if (key.MBEDTLS_PRIVATE(key_id) > KEYSTORE_PSA_MAX_VOLATILE_KEY_ID)
#else
    if (key > KEYSTORE_PSA_MAX_VOLATILE_KEY_ID)
#endif
    {
        status = psa_purge_key(key);
    }

    if (!KeyStore_semaphoreObject.isAcquired && (status != KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE))
    {
        KeyStore_releaseLock();
    }
    return status;
}

/*
 *  ======== KeyStore_cleanUp ========
 */
static int_fast16_t KeyStore_cleanUp(int_fast16_t status)
{
    KeyStore_semaphoreObject.isAcquired = false;
    if (status != KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE)
    {
        KeyStore_releaseLock();
    }

    return status;
}

/*
 *  ======== KeyStore_PSA_init ========
 */
int_fast16_t KeyStore_PSA_init(void)
{
    psa_status_t status = KEYSTORE_PSA_STATUS_GENERIC_ERROR;

    if (!isKeyStoreInitialized)
    {
        mbedtls_memory_buffer_alloc_init(allocBuffer, sizeof(allocBuffer));
        /*
         * Applications may call psa_crypto_init() function more than once,
         * for example in Key Store and TF-M. Once a call succeeds,
         * subsequent calls are guaranteed to succeed.
         */
        status = psa_crypto_init();

        if (status != PSA_SUCCESS)
        {
            return status;
        }

        status = tfm_its_init();

        if (status != PSA_SUCCESS)
        {
            psa_wipe_all_key_slots();
            return KEYSTORE_PSA_STATUS_GENERIC_ERROR;
        }

        if (!KeyStore_semaphoreObject.isInitialized)
        {
            SemaphoreP_constructBinary(&KeyStore_semaphoreObject.KeyStore_accessSemaphore, 1);
            KeyStore_semaphoreObject.isInitialized = true;
        }

        isKeyStoreInitialized = true;
    }
    else
    {
        status = KEYSTORE_PSA_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== KeyStore_PSA_getKey ========
 */
int_fast16_t KeyStore_PSA_getKey(KeyStore_PSA_KeyFileId key,
                                 uint8_t *data,
                                 size_t dataSize,
                                 size_t *dataLength,
                                 KeyStore_PSA_Algorithm alg,
                                 KeyStore_PSA_KeyUsage usage)
{
    psa_status_t status = KEYSTORE_PSA_STATUS_GENERIC_ERROR;
    psa_key_slot_t *slot;

    if (!KeyStore_acquireLock())
    {
        status = KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE;
        return status;
    }
    KeyStore_semaphoreObject.isAcquired = true;

    /*
     * Reject a zero-length output buffer now, since this can never be a
     * valid key representation. This way we know that data must be a valid
     * pointer and we can do things like memset(data, ..., dataSize). */
    if (dataSize == 0)
    {
        status = PSA_ERROR_BUFFER_TOO_SMALL;
        return KeyStore_cleanUp(status);
    }

    /*
     * Set the key to empty now, so that even when there are errors, we always
     * set dataLength to a value between 0 and dataSize. On error, setting
     * the key to empty is a good choice because an empty key representation is
     * unlikely to be accepted anywhere. */
    *dataLength = 0;

    /* Fetch key material from key storage. */
    status = psa_get_and_lock_key_slot_with_policy(key, &slot, usage, alg);

    if (status != KEYSTORE_PSA_STATUS_SUCCESS)
    {
        /* Ignore return value for decrement of lock counter, the return value from attempting to fetch key is apt for
         * application
         */
        (void)psa_unlock_key_slot(slot);
        return KeyStore_cleanUp(status);
    }

    psa_key_attributes_t attributes = {.MBEDTLS_PRIVATE(core) = slot->attr};

    status = psa_export_key_internal(&attributes, slot->key.data, slot->key.bytes, data, dataSize, dataLength);

    /* Decrement lock counter on key slot after accessing the key material */
    status = psa_unlock_key_slot(slot);

    return KeyStore_cleanUp(status);
}

/*
 *  ======== KeyStore_PSA_importKey ========
 */
int_fast16_t KeyStore_PSA_importKey(KeyStore_PSA_KeyAttributes *attributes,
                                    uint8_t *data,
                                    size_t dataLength,
                                    KeyStore_PSA_KeyFileId *key)
{
    int_fast16_t status = KEYSTORE_PSA_STATUS_GENERIC_ERROR;

    if (!KeyStore_acquireLock())
    {
        status = KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE;
        return status;
    }
    KeyStore_semaphoreObject.isAcquired = true;

    status = psa_import_key(attributes, data, dataLength, key);

    return KeyStore_cleanUp(status);
}

/*
 *  ======== KeyStore_PSA_exportKey ========
 */
int_fast16_t KeyStore_PSA_exportKey(KeyStore_PSA_KeyFileId key, uint8_t *data, size_t dataSize, size_t *dataLength)
{
    int_fast16_t status = KEYSTORE_PSA_STATUS_GENERIC_ERROR;

    if (!KeyStore_acquireLock())
    {
        status = KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE;
        return status;
    }
    KeyStore_semaphoreObject.isAcquired = true;

    status = psa_export_key(key, data, dataSize, dataLength);

    return KeyStore_cleanUp(status);
}

/*
 *  ======== KeyStore_PSA_exportPublicKey ========
 */
int_fast16_t KeyStore_PSA_exportPublicKey(KeyStore_PSA_KeyFileId key,
                                          uint8_t *data,
                                          size_t dataSize,
                                          size_t *dataLength)
{
    int_fast16_t status = KEYSTORE_PSA_STATUS_GENERIC_ERROR;

    if (!KeyStore_acquireLock())
    {
        status = KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE;
        return status;
    }
    KeyStore_semaphoreObject.isAcquired = true;

    status = psa_export_public_key(key, data, dataSize, dataLength);

    return KeyStore_cleanUp(status);
}

/*
 *  ======== KeyStore_PSA_destroyKey ========
 */
int_fast16_t KeyStore_PSA_destroyKey(KeyStore_PSA_KeyFileId key)
{
    int_fast16_t status = KEYSTORE_PSA_STATUS_GENERIC_ERROR;
    volatile uint32_t keyID;

    /* Create a copy of the key ID */
    SET_KEY_ID(keyID, key);

    if ((keyID >= KEYSTORE_PSA_PRE_PROVISIONED_KEY_ID_MIN) && (keyID <= KEYSTORE_PSA_PRE_PROVISIONED_KEY_ID_MAX))
    {
        return KEYSTORE_PSA_STATUS_NOT_SUPPORTED;
    }

    if (!KeyStore_acquireLock())
    {
        status = KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE;
        return status;
    }
    KeyStore_semaphoreObject.isAcquired = true;

    status = psa_destroy_key(key);

    return KeyStore_cleanUp(status);
}

/*
 *  ======== KeyStore_PSA_getKeyAttributes ========
 */
int_fast16_t KeyStore_PSA_getKeyAttributes(KeyStore_PSA_KeyFileId key, KeyStore_PSA_KeyAttributes *attributes)

{
    int_fast16_t status = KEYSTORE_PSA_STATUS_GENERIC_ERROR;

    if (!KeyStore_acquireLock())
    {
        status = KEYSTORE_PSA_STATUS_RESOURCE_UNAVAILABLE;
        return status;
    }
    KeyStore_semaphoreObject.isAcquired = true;

    status = psa_get_key_attributes(key, attributes);

    return KeyStore_cleanUp(status);
}

/*
 *  ======== KeyStore_PSA_resetKeyAttributes ========
 */
void KeyStore_PSA_resetKeyAttributes(KeyStore_PSA_KeyAttributes *attributes)
{
    mbedtls_free(attributes->MBEDTLS_PRIVATE(domain_parameters));
    memset(attributes, 0, sizeof(*attributes));
}
