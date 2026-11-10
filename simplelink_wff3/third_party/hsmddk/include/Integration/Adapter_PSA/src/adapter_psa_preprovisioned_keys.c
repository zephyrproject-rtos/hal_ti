/*
 * Copyright (c) 2024-2025, Texas Instruments Incorporated
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
#include <string.h>
#include <DeviceFamily.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_preprovisioned_keys.h>

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
/**
 * @brief Counter to keep track of the number of pre-provisioned keys available during psa_crypto_init()
 *
 * preProvisionedKeyCount is set to the empty macro to indicate no provisioned keys and later initialized to the number
 * of pre-provisioned key memory if pre-provisioned keys are available during initialization of KeyStore.
 */
static uint32_t preProvisionedKeyCount;

/**
 * @brief Global array of pre-provisioned key IDs
 *
 * During psa_crypto_init(), the pre-provisioned key memory is checked for the existence of pre-provisioned keys. If
 * they exist, pre-provisioned key memory is parsed to copy the necessary information in the the preProvisionedKeys
 * including the key ID, algorithm, usage, type, lifetime, address of the plaintext material, and the key length. This
 * array is later used to check the availability of a key in pre-provisioned key memory when an application or driver
 * requests for the key using key ID.
 */
static psa_key_context_t preProvisionedKeys[KEYMGMT_MAX_PREPROVISIONED_KEYS];

static psa_status_t local_initPreProvisionedKeys(void);
static psa_status_t local_getPreProvisionedKey(mbedtls_svc_key_id_t key,
                                               psa_key_context_t ** ppKeyEntry);


/*
 *  ======== KeyMgmt_initPreProvisionedKeys ========
 */
psa_status_t KeyMgmt_initPreProvisionedKeys(void)
{
    return local_initPreProvisionedKeys();
}

/*
 *  ======== KeyMgmt_getPreProvisionedKey ========
 */
psa_status_t KeyMgmt_getPreProvisionedKey(mbedtls_svc_key_id_t key,
                                          psa_key_context_t ** ppKeyEntry)
{
    return local_getPreProvisionedKey(key, ppKeyEntry);
}

/*
 *  ======== local_initPreProvisionedKeys ========
 */
static psa_status_t local_initPreProvisionedKeys(void)
{
    uint8_t *currentKey;
    void *dest;
    uint32_t keySize;
    uint32_t lifetime;
    uint32_t keyLength;
    uint32_t end;

    currentKey = (uint8_t *)(TI_SL_BUILT_IN_KEY_AREA_ADDR);

    /* Check for magic header to identify if pre-provisioned keys were programmed */
    if (memcmp(currentKey,
               KEYMGMT_PRE_PROVISIONED_KEY_MAGIC_HEADER,
               KEYMGMT_PRE_PROVISIONED_KEY_MAGIC_HEADER_LENGTH) != 0)
    {
        /* No error when pre-provisioned keys are not available */
        return PSA_SUCCESS;
    }

    /* Reset keySize (size of each key) and preProvisionedKeyCount (length of the pre-provisioned key array) */
    keySize                = 0;
    preProvisionedKeyCount = 0;

    /* Parse the pre-provisioned key memory until reaching the final end pattern for PP keys or empty pattern which
     * allows further addition of pre-provisioned keys to create a local copy of the key ID, size, and starting address
     * to be used by the application
     */
    do
    {
        /* Skip the Magic Header */
        keySize = KEYMGMT_PRE_PROVISIONED_KEY_MAGIC_HEADER_LENGTH;

        /* Copy Lifetime */
        memcpy(&lifetime, (currentKey + keySize), MEMBER_SIZE(KeyMgmt_PreProvisionedKeyMetaData, tiLifetime));
        keySize += MEMBER_SIZE(KeyMgmt_PreProvisionedKeyMetaData, tiLifetime);

        if (lifetime == KEYMGMT_PRE_PROVISIONED_KEY_VALID_LIFETIME)
        {
            /* Copy the psa_key_lifetime_t */
            dest = &(preProvisionedKeys[preProvisionedKeyCount].attributes.MBEDTLS_PRIVATE(lifetime));
            memcpy(dest,
                   (currentKey + keySize),
                   sizeof(psa_key_lifetime_t));
            keySize += sizeof(psa_key_lifetime_t);

            /* Copy the key id */
            dest = &(preProvisionedKeys[preProvisionedKeyCount].attributes.MBEDTLS_PRIVATE(id));
            /* If MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER is defined, then that should be reflected
             * in both the source and destination of the key information. In other words,
             * mbedtls_svc_key_id_t will include id & owner in both the preProvisionedKeys
             * buffer and actual pre-provisioned memory if the define is set.
             */
            memcpy(dest,
                   (currentKey + keySize),
                   sizeof(mbedtls_svc_key_id_t));
            keySize += sizeof(mbedtls_svc_key_id_t);

            /* Copy the Algorithm */
            dest = &(preProvisionedKeys[preProvisionedKeyCount].attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg));
            memcpy(dest,
                   (currentKey + keySize),
                   sizeof(psa_algorithm_t));
            keySize += sizeof(psa_algorithm_t);

            /* Copy the Usage */
            dest = &(preProvisionedKeys[preProvisionedKeyCount].attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage));
            memcpy(dest,
                   (currentKey + keySize),
                   sizeof(psa_key_usage_t));
            keySize += sizeof(psa_key_usage_t);

            /* Copy the key length */
            dest = &(preProvisionedKeys[preProvisionedKeyCount].key_size);
            memcpy(dest,
                   (currentKey + keySize),
                   MEMBER_SIZE(KeyMgmt_PreProvisionedKeyMetaData, keyLength));
            keySize += MEMBER_SIZE(KeyMgmt_PreProvisionedKeyMetaData, keyLength);

            /* Copy the psa_key_type_t */
            dest = &(preProvisionedKeys[preProvisionedKeyCount].attributes.MBEDTLS_PRIVATE(type));
            memcpy(dest,
                   (currentKey + keySize),
                   sizeof(psa_key_type_t));
            keySize += sizeof(psa_key_type_t);

            /* Skip over the reserved memory */
            keySize += MEMBER_SIZE(KeyMgmt_PreProvisionedKeyMetaData, reserved);

            /* Copy the starting addr of pre-provisioned key psa_key */
            preProvisionedKeys[preProvisionedKeyCount].key = currentKey + keySize;

            /* Mark the slot as allocated */
            preProvisionedKeys[preProvisionedKeyCount].fAllocated = 255U;

            keySize += (preProvisionedKeys[preProvisionedKeyCount].key_size +
                        MEMBER_SIZE(KeyMgmt_PreProvisionedKeyStorageFormat, fletcher));

            /* Increment the count of PP keys available in pre-provisioned key memory */
            preProvisionedKeyCount++;
        }
        else
        {
            /* Skip over the invalid key */
            keySize += (sizeof(mbedtls_svc_key_id_t) + sizeof(psa_algorithm_t) + sizeof(psa_key_usage_t) +
                        sizeof(psa_key_lifetime_t));

            memcpy(&keyLength, (currentKey + keySize), MEMBER_SIZE(KeyMgmt_PreProvisionedKeyMetaData, keyLength));

            keySize += (MEMBER_SIZE(KeyMgmt_PreProvisionedKeyMetaData, keyLength) + keyLength +
                        sizeof(psa_key_type_t) + MEMBER_SIZE(KeyMgmt_PreProvisionedKeyStorageFormat, fletcher) +
                        MEMBER_SIZE(KeyMgmt_PreProvisionedKeyMetaData, reserved));
        }

        /* Set to pre-provisioned key address tracking to the next PP key, if available, after the key and checksum */
        currentKey += keySize;

        /* Reset pre-provisioned key size tracking for the next PP key */
        keySize = 0;

        memcpy(&end, currentKey, sizeof(end));
    } while ((end != KEYMGMT_PRE_PROVISIONED_KEYS_END) && (end != KEYMGMT_PREPROVISIONED_KEYS_EMPTY));

    return PSA_SUCCESS;
}

static psa_status_t local_getPreProvisionedKey(mbedtls_svc_key_id_t key,
                                               psa_key_context_t ** ppKeyEntry)
{
    psa_status_t funcres = PSA_ERROR_GENERIC_ERROR;
    psa_key_context_t * pEntry;
    psa_key_id_t id;
    uint32_t entryIdx = 0;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    id = key.MBEDTLS_PRIVATE(key_id);
#else
    id = key;
#endif

    if ((id < MBEDTLS_PSA_KEY_ID_BUILTIN_MIN) ||
        (id > MBEDTLS_PSA_KEY_ID_BUILTIN_MAX))
    {
        /* If the ID being requested is not a valid pre-provisioned key ID,
         * then don't bother checking our array of pre-provisioned keys.
         * Since initialization doesn't check the pre-provisioned IDs, this
         * does mean that there may exist a key with an invalid ID in the
         * pre-provisioned array that can never be accessed. This is acceptable
         * because the application shouldn't expect to retrieve a key whose
         * ID is invalid.
         */
        entryIdx = preProvisionedKeyCount;
    }

    for (; entryIdx < preProvisionedKeyCount; entryIdx++)
    {
        pEntry = &preProvisionedKeys[entryIdx];

#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
        if (id == pEntry->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id))
#else
        if (id == pEntry->attributes.MBEDTLS_PRIVATE(id))
#endif
        {
            break;
        }
    }

    if (entryIdx >= preProvisionedKeyCount)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else
    {
        /* A slot with a matching ID was found - verify that the pre-provisioned key has valid
         * metadata before returning it.
         */
        psa_key_location_t key_location = PSA_KEY_LIFETIME_GET_LOCATION(pEntry->attributes.MBEDTLS_PRIVATE(lifetime));

        if ((key_location != PSA_KEY_LOCATION_LOCAL_STORAGE) ||
            (pEntry->fAllocated != 255U))
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else
        {
            /* Key is valid. Return pointer to its slot. */
            *ppKeyEntry = pEntry;

            funcres = PSA_SUCCESS;
        }
    }

    return funcres;
}
#endif /* (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX) */
