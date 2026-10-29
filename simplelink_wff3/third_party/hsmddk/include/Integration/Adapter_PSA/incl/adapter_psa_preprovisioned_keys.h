/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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

#ifndef INCLUDE_GUARD_ADAPTER_PSA_PREPROVISIONED_KEYS_H
#define INCLUDE_GUARD_ADAPTER_PSA_PREPROVISIONED_KEYS_H

#include <stdint.h>
#include <stddef.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h> // psa_key_context_t


/* Macro to obtain size of struct member */
#define MEMBER_SIZE(type, member)    sizeof(((type *)0)->member)
/**
 *  Starting address of Pre-provisioned keys.
 *
 * The immutable platform Root of Trust stores the pre-provisioned key's programmed at
 * production. The built-in key implementation will read this address to obtain the
 * mbedtls_svc_key_id_t and other relevant meta data of all the pre-provisioned keys stored at this address
 */
#define TI_SL_BUILT_IN_KEY_AREA_ADDR 0x0000

#define FLETCHER_CHECKSUM_ALGORITHM 32 /* FLETCHER-32 */

/**
 * @brief Area size for pre-provisioned keys, 2KB - 256B (reserved for attestation data)
 */
#define KEYMGMT_PREPROVISIONED_AREA_SIZE (0x700) /* 1792 B */

/**
 * @brief Macro to indicate empty pre-provisioned key memory
 */
#define KEYMGMT_PREPROVISIONED_KEYS_EMPTY 0xFFFF

/**
 * @brief Pre-provisioned key storage magic header.
 */
#define KEYMGMT_PRE_PROVISIONED_KEY_MAGIC_HEADER        "HUK\0KEY"
#define KEYMGMT_PRE_PROVISIONED_KEYS_END                0
#define KEYMGMT_PRE_PROVISIONED_KEY_MAGIC_HEADER_LENGTH (sizeof(KEYMGMT_PRE_PROVISIONED_KEY_MAGIC_HEADER))
#define KEYMGMT_PRE_PROVISIONED_KEYS_END_LENGTH         (sizeof(KEYMGMT_PRE_PROVISIONED_KEYS_END))
#define KEYMGMT_MAX_PREPROVISIONED_KEYS                 0x10

/**
 * @brief Pre-provisioned key Lifetime
 */
#define KEYMGMT_PRE_PROVISIONED_KEY_VALID_LIFETIME   0xAAAA
#define KEYMGMT_PRE_PROVISIONED_KEY_INVALID_LIFETIME 0x8888

/**
 * @brief Admissible key ID range for Pre-provisioned keys
 *
 * 0x7fff0000 - 0x7fffefff is reserved to store pre-provisioned keys and certificates.
 */
#define KEYMGMT_PRE_PROVISIONED_KEY_ID_MAX MBEDTLS_PSA_KEY_ID_BUILTIN_MAX
#define KEYMGMT_PRE_PROVISIONED_KEY_ID_MIN MBEDTLS_PSA_KEY_ID_BUILTIN_MIN

/**
 * @brief Reserved pre-provisioned key IDs
 *
 * Some known pre-provisioned key used by attestation service have reserved key IDs in the admissible range for
 * pre-provisioned keys
 */
#define KEYMGMT_PRE_PROVISIONED_ATTESTATION_PUB_KEY_ID KEYMGMT_PRE_PROVISIONED_KEY_ID_MIN + 1
#define KEYMGMT_PRE_PROVISIONED_ATTESTATION_PRI_KEY_ID KEYMGMT_PRE_PROVISIONED_KEY_ID_MIN

/**
 * @brief Structure for storing pre-provisioned key's meta data
 *
 * - header      : magic header to indicate the start of the pre-provisioned key
 * - tiLifetime  : TI (vendor) lifetime of the key, to invalidate pre-provisioned key
 * - psaLifetime : Lifetime, persistence and location, of the pre-provisioned key
 * - id          : key id (and its owner when applicable)
 * - alg         : Cryptographic algorithm permitted using this key
 * - usage       : Usage for the key as described by the PSA API
 * - keyLength   : Length of the pre-provisioned key (bytes)
 * - type        : Key type of the pre-provisioned key, such as #PSA_KEY_TYPE_AES
 * - reserved    : Reserved padding to word-align pre-provisioned keyMaterial
 */
typedef struct
{
    uint8_t header[KEYMGMT_PRE_PROVISIONED_KEY_MAGIC_HEADER_LENGTH];
    uint32_t tiLifetime;
    psa_key_lifetime_t psaLifetime;
    mbedtls_svc_key_id_t id;
    psa_algorithm_t alg;
    psa_key_usage_t usage;
    uint32_t keyLength;
    psa_key_type_t type;
    uint16_t reserved; /* 2B reserved */
} KeyMgmt_PreProvisionedKeyMetaData;


/**
 *  @brief Size of the meta data associated with the pre-provisioned key
 */
#define KEYMGMT_PRE_PROVISIONED_KEY_METADATA_SIZE sizeof(KeyMgmt_PreProvisionedKeyMetaData)

/**
 * @brief Structure for storing pre-provisioned keys and their meta data
 *
 * - meta        : Structure with meta data associated with each pre-provisioned key
 * - KeyMaterial : A pointer to the plaintext key material
 * - fletcher    : 32-bit Fletcher checksum over the pre-provisioned key and its meta data
 */
typedef struct
{
    KeyMgmt_PreProvisionedKeyMetaData meta;
    uint8_t *keyMaterial;
    uint32_t fletcher;
} KeyMgmt_PreProvisionedKeyStorageFormat;

/*!
 *  @brief  Read pre-provisioned keys from flash into KeyStore RAM.
 *
 *  This function will search the pre-provisioned region of flash for any
 *  valid keys that can be loaded into KeyStore for future use via the
 *  key IDs. Note that no attribute validation is performed here - it is
 *  performed upon request of the key (KeyMgmt_getPreProvisionedKey).
 *
 *  @post   #KeyMgmt_getPreProvisionedKey()
 *
 *  @retval PSA_SUCCESS Either no pre-provisioned keys were found, or potentially
 *                      valid keys were found and loaded.
 */
psa_status_t KeyMgmt_initPreProvisionedKeys(void);

/*!
 *  @brief  Retrieve a pointer to a pre-provisioned key entry for a given id.
 *
 *  This function will search for a key entry in KeyStore RAM that contains
 *  the pre-provisioned key with the provided id.
 *
 *
 *  @param  [in] key            Key ID to search for
 *
 *  @param  [out] ppKeyEntry    Pointer to a key entry struct, to be returned if
 *                              the requested key is found in KeyStore RAM.
 *
 *  @post   #psaInt_KeyMgmtLoadKey()
 *
 *  @retval #PSA_ERROR_INVALID_ARGUMENT          Key found, but loaded from flash with invalid attributes.
 *  @retval #PSA_ERROR_INVALID_HANDLE            Key not found among the keys loaded from pre-provisioned flash.
 */
psa_status_t KeyMgmt_getPreProvisionedKey(mbedtls_svc_key_id_t key,
                                          psa_key_context_t ** ppKeyEntry);

#endif /* INCLUDE_GUARD_ADAPTER_PSA_PREPROVISIONED_KEYS_H */
