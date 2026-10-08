/**
 * @file adapter_psa_key_management.h
 *
 * @brief PSA API - Key Management services definitions
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : DDK-130_bsd                                              */
/*   Version       : 4.1.1                                                    */
/*   Configuration : DDK_EIP130_BSD                                           */
/*                                                                            */
/*   Date          : 2023-Mar-10                                              */
/*                                                                            */
/* Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are permitted provided that the following conditions are     */
/* met:                                                                       */
/*                                                                            */
/* 1. Redistributions of source code must retain the above copyright          */
/* notice, this list of conditions and the following disclaimer.              */
/*                                                                            */
/* 2. Redistributions in binary form must reproduce the above copyright       */
/* notice, this list of conditions and the following disclaimer in the        */
/* documentation and/or other materials provided with the distribution.       */
/*                                                                            */
/* 3. Neither the name of the copyright holder nor the names of its           */
/* contributors may be used to endorse or promote products derived from       */
/* this software without specific prior written permission.                   */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       */
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT           */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,      */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       */
/* -------------------------------------------------------------------------- */

#ifndef INCLUDE_GUARD_ADAPTER_PSA_KEY_MANAGEMENT_H
#define INCLUDE_GUARD_ADAPTER_PSA_KEY_MANAGEMENT_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>      // uint8_t, uint16_t, uint32_t, uint64_t
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>      // size_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>                 // psa_status_t, psa_key_id_t, psa_key_context_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_derivation.h> // psa_key_derivation_operation_t

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

typedef struct
{
    psa_key_attributes_t attributes;
    PsaPolicyMask_t AssetPolicy;
    size_t key_size;
    PsaAssetId_t key_assetId;
    /* key_assetId2 is necessary for symmetric keys stored with persistence
     * PSA_KEY_PERSISTENCE_HSM_ASSET_STORE. Assets cannot do both encryption
     * and decryption with one asset policy.
     */
    PsaAssetId_t key_assetId2;
    uint8_t *key;
    /* Necessary for symmetric keys stored as key blobs. key2 will be used for
     * the decryption key blob.
     */
    uint8_t *key2;
    uint8_t fAllocated;
} psa_key_context_t;

/*!
 *  @brief  Enum for curve sizes in bits supported by KeyStore.
 */
typedef enum
{
    CURVE_LENGTH_192 = 192,
    CURVE_LENGTH_224 = 224,
    CURVE_LENGTH_256 = 256,
    CURVE_LENGTH_384 = 384,
    CURVE_LENGTH_512 = 512,
    CURVE_LENGTH_521 = 521,
} CurveLengthBits;

/*!
 *  @brief  Retrieve a pointer to a key entry for a given id.
 *
 *  This function will search for a key entry in KeyStore RAM that contains
 *  either the key material or key metadata for the key with the provided id.
 *  For volatile and Asset Store keys, if the entry is not found, the key does
 *  not exist. For persistent keys, persistent storage will be checked for the
 *  key. If it exists there, it will be reloaded to the key entry before the entry
 *  gets returned.
 *
 *  @param  [in] key            Key ID to search for
 *
 *  @param  [out] ppKeyEntry    Pointer to a key entry struct, to be returned if
 *                              the requested key is found in or loaded into
 *                              KeyStore RAM.
 *
 *  @post   #psaInt_KeyMgmtLoadKey()
 *  @post   #psaInt_KeyMgmtClrKeyInUse()
 *
 *  @retval #PSA_ERROR_DOES_NOT_EXIST            Key not found in RAM or NVM.
 *  @retval #PSA_ERROR_INVALID_HANDLE            Key found in RAM, but its entry is unallocated.
 */
psa_status_t
psaInt_KeyMgmtGetKey(mbedtls_svc_key_id_t key,
                     psa_key_context_t ** ppKeyEntry);

/*!
 *  @brief  Retrieve a pointer to a key entry for a given id, and lock the entry.
 *
 *  This function will search for a key entry in KeyStore RAM that contains
 *  either the key material or key metadata for the key with the provided id.
 *  For volatile and Asset Store keys, if the entry is not found, the key does
 *  not exist. For persistent keys, persistent storage will be checked for the
 *  key. If it exists there, it will be reloaded to the key entry before the entry
 *  gets returned.
 *
 *  @param  [in] key            Key ID to search for.
 *
 *  @param  [out] ppKeyEntry    Pointer to a key entry struct, to be returned if
 *                              the requested key is found in or loaded into
 *                              KeyStore RAM.
 *
 *  @post   #psaInt_KeyMgmtLoadKey()
 *  @post   #psaInt_KeyMgmtClrKeyInUse()
 *
 *  @retval #PSA_ERROR_DOES_NOT_EXIST            Key not found in RAM or NVM.
 *  @retval #PSA_ERROR_INVALID_HANDLE            Key found in RAM, but its entry is unallocated.
 */
psa_status_t
psaInt_KeyMgmtGetAndLockKey(mbedtls_svc_key_id_t key,
                            psa_key_context_t ** ppKeyEntry);

/*!
 *  @brief  Retrieve a key, either in plaintext or via an asset ID.
 *
 *  For a given key entry, this function will return the associated key material
 *  either to the provided plaintext pointer, or through the provided asset ID
 *  pointer. The asset ID pointer should be NULL if plaintext is requested, and
 *  the plaintext pointer & DataSize should be NULL/0 if an asset ID is requested.
 *  If an asset ID is requested, this function will load plaintext or a key blob
 *  to the HSM if the key is not already stored there. Plaintext cannot be returned
 *  for keys with location #PSA_KEY_LOCATION_HSM_ASSET_STORE.
 *
 *  @param  [in]  pKey             Key entry of the key to retrieve.
 *
 *  @param  [out] pAssetId         Pointer to an asset ID, to be returned if the pointer
 *                                 is non-null at call time.
 *
 *  @param  [in]  target_alg       Desired algorithm to use the key for. Before retrieving the key material,
 *                                 it must be verified that it is allowed to be used for a given algorithm.
 *
 *  @param  [in]  target_usage     Desired usage of the resulting asset - only used for
 *                                 symmetric keys. Must be one of PSA_KEY_USAGE_ENCRYPT
 *                                 or PSA_KEY_USAGE_DECRYPT.
 *
 *  @param  [out] pData            Pointer to a buffer to hold plaintext key, if non-null.
 *
 *  @param  [in]  DataSize         Size of the provided buffer at pData.
 *
 *  @param  [out] pActualDataSize  Size of the retrieved buffer, if less than or equal to
 *                                 DataSize.
 *
 *  @pre    #psaInt_KeyMgmtGetAndLockKey()
 *  @post   #psaInt_KeyMgmtClrKeyInUse()
 *
 *  @retval #PSA_ERROR_INVALID_ARGUMENT          Caller requests both asset ID and plaintext.
 *  @retval #PSA_ERROR_CORRUPTION_DETECTED       Token failure or other unexpected failure.
 *  @retval #PSA_ERROR_HARDWARE_FAILURE          Failure to allocate an asset to HSM.
 *  @retval #PSA_ERROR_INSUFFICIENT_MEMORY       DataSize is not large enough for the key material
 *  @retval #PSA_ERROR_NOT_PERMITTED             Attempt to retrieve HSM location key in plaintext.
 */
psa_status_t
psaInt_KeyMgmtLoadKey(psa_key_context_t * pKey,
                      uint32_t * const pAssetId,
                      psa_algorithm_t target_alg,
                      psa_key_usage_t target_usage,
                      uint8_t * const pData,
                      size_t const DataSize,
                      uint32_t * const pActualDataSize);

/*!
 *  @brief  Free an asset from the HSM Asset Store.
 *
 *  For a given key entry, this function will release the key from the asset store
 *  if it is already loaded there.
 *
 *  @param  [in]  pKey             Key entry of the key to free the asset for.
 *
 *
 *  @pre    #psaInt_KeyMgmtGetAndLockKey()
 *  @pre    #psaInt_KeyMgmtLoadKey()
 *
 *  @retval #PSA_ERROR_INVALID_ARGUMENT          The provided pEntry is NULL.
 *  @retval #PSA_ERROR_CORRUPTION_DETECTED       Token failure.
 *  @retval #PSA_ERROR_HARDWARE_FAILURE          Failure submitting token or retrieving result.
 */
psa_status_t
psaInt_KeyMgmtReleaseKey(psa_key_context_t * pKey);

/*!
 *  @brief  Mark a key entry as in use.
 *
 *  For a given key ID, this function will lock the key entry so it cannot be accessed
 *  or modified by another entity.
 *
 *  @param  [in]  key             Key id of the key entry to lock.
 *
 *  @post    #psaInt_KeyMgmtClrKeyInUse()
 *
 *  @retval #PSA_ERROR_INVALID_HANDLE            The associated key entry is unallocated.
 *  @retval #PSA_ERROR_KEY_IN_USE                The key entry is already locked.
 *  @retval #PSA_ERROR_DOES_NOT_EXIST            Key entry not found for given ID.
 */
psa_status_t
psaInt_KeyMgmtSetKeyInUse(mbedtls_svc_key_id_t key);

/*!
 *  @brief  Mark a key entry as not in use.
 *
 *  For a given key ID, this function will unlock the key entry so it can be accessed
 *  or modified by another entity.
 *
 *  @param  [in]  key             Key id of the key entry to unlock.
 *
 *  @post    #psaInt_KeyMgmtClrKeyInUse()
 *
 *  @retval #PSA_ERROR_INVALID_HANDLE            The associated key entry is unallocated.
 *  @retval #PSA_ERROR_CORRUPTION_DETECTED       The key entry wasn't already locked.
 *  @retval #PSA_ERROR_DOES_NOT_EXIST            Key entry not found for given ID.
 */
psa_status_t
psaInt_KeyMgmtClrKeyInUse(mbedtls_svc_key_id_t key);

/*!
 *  @brief  Convert a public key from import format to HSM vectorized format.
 *
 *  Takes public key material from what the application provided to a key creation
 *  API, and converts it into the format the HSM requires for public key operations.
 *  By default, this API assumes the input has been provided per the PSA spec. It also
 *  has support for ASN1DER parsing that is disabled by default.
 *
 *  @param [in]  PersistentItemSize  Indicator to bypass ASN1DER parsing. If non-zero,
 *                                   read the data from the format the PSA spec requires.
 *
 *  @param [in]  pData               Input data for the public key
 *
 *  @param [in]  DataLen             Input data length of the public key
 *
 *  @param [in]  ExpCurveFamily      PSA curve family of the public key
 *
 *  @param [in]  ExpCurveBits        Curve length in bits
 *
 *  @param [out] pCurveFamily        Curve family, as determined by ASN1DER input
 *
 *  @param [out] pCurveBits          Curve bits, as determined by ASN1DER input or ExpCurveBits
 *
 *  @param [out] pfECDH              Whether or not the provided public key is for ECDH
 *
 *  @param [out] pOutputData         Public key, in HSM vectorized format
 *
 *  @param [out] pOutputDataLength   Public key length, in HSM vectorized format
 *
 *  @retval #PSA_ERROR_INVALID_ARGUMENT   The provided public key or curve data is incorrect.
 *  @retval #PSA_ERROR_BUFFER_TOO_SMALL   The buffer to hold the vectorized output is too small.
*/
psa_status_t
psaInt_KeyMgmtReadECPubKey(const size_t PersistentItemSize,
                           const uint8_t * pData,
                           size_t DataLen,
                           psa_ecc_family_t ExpCurveFamily,
                           size_t ExpCurveBits,
                           uint8_t * pCurveFamily,
                           size_t * pCurveBits,
                           uint8_t * pfECDH,
                           uint8_t * pOutputData,
                           size_t * pOutputDataLength);

psa_status_t
psaInt_KeyMgmtDeriveKey(const psa_key_attributes_t * attributes,
                        KeyMgmt_psa_key_derivation_operation_t * operation,
                        mbedtls_svc_key_id_t * key);

#endif /* INCLUDE_GUARD_ADAPTER_PSA_KEY_MANAGEMENT_H */

/* end of file adapter_psa_key_management.h */
