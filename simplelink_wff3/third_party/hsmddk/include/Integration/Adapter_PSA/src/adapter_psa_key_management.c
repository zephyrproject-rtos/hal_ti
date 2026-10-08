/* adapter_psa_key_management.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the key management services.
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

/*
 *  Copyright The Mbed TLS Contributors
 *  Copyright (c) 2024-2025, Texas Instruments Incorporated
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/c_adapter_psa.h>              // configuration
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/HSMSAL/HSMSAL.h> // Status type for genPubKey
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                       // size_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>                 // the API to implement
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/internal_trusted_storage.h> // PSA storage API reference
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa_key_store.h>              // psaInt_KeyStore_*
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>                // VexTokenCmd_*_t, VexTokenRslt_*_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_preprovisioned_keys.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asym_parse.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asym_write.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>
#include <third_party/hsmddk/include/Kit/EIP130/DomainHelper/incl/eip130_domain_ecc_curves.h>   // EIP130DOMAIN_ECC_FAMILY_*
#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/private_access.h> // MBEDTLS_PRIVATEs
#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/psa_crypto_storage.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/platform.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_pk.h> // generate public key token
#include <third_party/hsmddk/include/Config/cs_mbedtls.h>
#include <DeviceFamily.h>

#ifdef PSA_ENABLE_DEBUG_FUNCTIONS
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_debug.h>
#include <inttypes.h>
#endif

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/** Maximum length of SHA1/SHA224/SHA256 HMAC keys */
#define PSA_SYM_ALGO_MAX_HMAC_SHA2_KEY_SIZE     (512U / 8U)

/** Maximum length of SHA384/SHA512 HMAC keys */
#define PSA_SYM_ALGO_MAX_HMAC_SHA512_KEY_SIZE   (1024U / 8U)

/* The following extern values will come from sysconfig */
extern const size_t MBEDTLS_KEY_VOLATILE_COUNT;
extern const size_t MBEDTLS_KEY_ASSET_STORE_COUNT;
/* Persistent keys will have a pre-defined number of slots to cache keys that are also stored to NVM */
extern const size_t MBEDTLS_KEY_PERSISTENT_COUNT;

#define MBEDTLS_MAX_KEY_BUFF_ENTRIES (MBEDTLS_KEY_VOLATILE_COUNT + MBEDTLS_KEY_ASSET_STORE_COUNT + \
                                      MBEDTLS_KEY_PERSISTENT_COUNT)

#define COPROCESSOR_ASSET_POLICY_FLAGS (EIP130_ASSET_POLICY_PRIVATEDATA | EIP130_ASSET_POLICY_NONMODIFIABLE | \
                                        EIP130_ASSET_POLICY_COPROIFC)

/** Global value to not use ASN1DER - allowing for potential future configuration by
 * the application.
 */
static size_t bypassASN1DER = 1;

/* Physical tokens used when generating key pair or public key */
static Eip130Token_Command_t CommandToken;
static Eip130Token_Result_t ResultToken;

/** Key administration:
 *  Indices 0 through (MBEDTLS_KEY_PERSISTENT_COUNT - 1) are reserved for
 *  persistent keys. Indices MBEDTLS_KEY_PERSISTENT_COUNT through
 *  (MBEDTLS_KEY_PERSISTENT_COUNT + MBEDTLS_KEY_ASSET_STORE_SLOT_COUNT - 1)
 *  are reserved for asset store keys. The remaining MBEDTLS_KEY_VOLATILE_COUNT
 *  indices are reserved for volatile keys.
 */
extern psa_key_context_t gl_PSA_Key[];

/* Buffers that hold key material during key creation operations. For symmetric keys,
 * these buffers are used to hold key blobs for encryption and decryption, respectively.
 * Alternatively, it can hold randomly generated key material or key material to be copied.
 * For asymmetric keys, the larger buffer is used to hold the HSM-formatted key material
 * so that it can be imported and used as an asset for public key cryptography. The largest
 * public key supported is a component form NISTP-521 public key. The 521-bit curve length
 * must be converted to a word boundary, multiplied by number of bytes per word, and
 * added by 4 bytes for the additional header word per component. Since there are two components
 * in the public key, multiply the whole prior value by 2. We must add additional bytes for the
 * wrapping involved with key blobs.
 */
static uint8_t KeyDataBuffer[PSA_KEYBLOB_ADDITIONAL_BYTES + (2U * (PSA_ASYM_DATA_VHEADER + (4U * ((521U + 31U) / 32U))))];

/* 32 bytes is the size of the largest symmetric key supported. This second buffer would only be
 * used to hold key material for a decryption key blob for a given symmetric key.
 */
static uint8_t KeyDataBuffer2[PSA_KEYBLOB_ADDITIONAL_BYTES + 32];

/* vendor_ok is only true for key IDs assigned by the implementation -
 * i.e. volatile or preprovisioned keys. Keys with persistence HSM_ASSET_STORE
 * will have the same acceptable key ID range as persistent keys. The TKDK
 * and HUK occupy the highest two key IDs, so those IDs are only valid in the
 * context of key derivation, which does not use this API.
 */
static inline int psa_is_valid_key_id(psa_key_id_t key_id, int vendor_ok)
{
    if ((key_id >= PSA_KEY_ID_USER_MIN) &&
        (key_id <= PSA_KEY_ID_HSM_TKDK)) {
        return 1;
    }

    if (vendor_ok &&
        (key_id >= PSA_KEY_ID_VENDOR_MIN) &&
        (key_id <= PSA_KEY_ID_VENDOR_MAX)) {
        return 1;
    }

    return 0;
}

static inline int psa_is_preprovisioned_key_id(psa_key_id_t key_id)
{
    if ((key_id >= MBEDTLS_PSA_KEY_ID_BUILTIN_MIN) &&
        (key_id <= MBEDTLS_PSA_KEY_ID_BUILTIN_MAX))
    {
        return 1;
    }

    return 0;
}

/** Test whether a key identifier is a volatile key identifier.
 *
 * \param key_id  Key identifier to test.
 *
 * \retval 1
 *         The key identifier is a volatile key identifier.
 * \retval 0
 *         The key identifier is not a volatile key identifier.
 */
static inline int psa_key_id_is_volatile(psa_key_id_t key_id)
{
    return (key_id >= PSA_KEY_ID_VOLATILE_MIN) &&
           (key_id <= PSA_KEY_ID_VOLATILE_MAX);
}

/** Check whether a given key type is valid for use with a given MAC algorithm
 *
 * Upon successful return of this function, the behavior of #PSA_MAC_LENGTH
 * when called with the validated algorithm and key_type is well-defined.
 *
 * \param[in] algorithm     The specific MAC algorithm (can be wildcard).
 * \param[in] key_type      The key type of the key to be used with the
 *                          algorithm.
 *
 * \retval #PSA_SUCCESS
 *         The key_type is valid for use with the algorithm
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The key_type is not valid for use with the algorithm
 */
static psa_status_t psa_mac_key_can_do(psa_algorithm_t algorithm,
                                       psa_key_type_t key_type)
{
    if (PSA_ALG_IS_HMAC(algorithm))
    {
        if (key_type == PSA_KEY_TYPE_HMAC)
        {
            return PSA_SUCCESS;
        }
    }

    if (PSA_ALG_IS_BLOCK_CIPHER_MAC(algorithm))
    {
        /* Check that we're calling PSA_BLOCK_CIPHER_BLOCK_LENGTH with a cipher
         * key.
         */
        if ((key_type & PSA_KEY_TYPE_CATEGORY_MASK) ==
            PSA_KEY_TYPE_CATEGORY_SYMMETRIC)
        {
            /* PSA_BLOCK_CIPHER_BLOCK_LENGTH returns 1 for stream ciphers and
             * the block length (larger than 1) for block ciphers.
             */
            if (PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) > 1)
            {
                return PSA_SUCCESS;
            }
        }
    }

    return PSA_ERROR_INVALID_ARGUMENT;
}

/** Calculate the intersection of two algorithm usage policies.
 *
 * Return 0 (which allows no operation) on incompatibility.
 */
static psa_algorithm_t psa_key_policy_algorithm_intersection(
    psa_key_type_t key_type,
    psa_algorithm_t alg1,
    psa_algorithm_t alg2)
{
    /* Common case: both sides actually specify the same policy. */
    if (alg1 == alg2)
    {
        return alg1;
    }

    /* If the policies are from the same hash-and-sign family, check
     * if one is a wildcard. If so the other has the specific algorithm
     */
    if (PSA_ALG_IS_SIGN_HASH(alg1) &&
        PSA_ALG_IS_SIGN_HASH(alg2) &&
        (alg1 & ~PSA_ALG_HASH_MASK) == (alg2 & ~PSA_ALG_HASH_MASK))
    {
        if (PSA_ALG_SIGN_GET_HASH(alg1) == PSA_ALG_ANY_HASH)
        {
            return alg2;
        }
        if (PSA_ALG_SIGN_GET_HASH(alg2) == PSA_ALG_ANY_HASH)
        {
            return alg1;
        }
    }

    /* If the policies are from the same AEAD family, check whether
     * one of them is a minimum-tag-length wildcard. Calculate the most
     * restrictive tag length
     */
    if (PSA_ALG_IS_AEAD(alg1) && PSA_ALG_IS_AEAD(alg2) &&
        (PSA_ALG_AEAD_WITH_SHORTENED_TAG(alg1, 0) ==
         PSA_ALG_AEAD_WITH_SHORTENED_TAG(alg2, 0)))
    {
        size_t alg1_len = PSA_ALG_AEAD_GET_TAG_LENGTH(alg1);
        size_t alg2_len = PSA_ALG_AEAD_GET_TAG_LENGTH(alg2);
        size_t restricted_len = alg1_len > alg2_len ? alg1_len : alg2_len;

        /* If both are wildcards, return most restrictive wildcard */
        if (((alg1 & PSA_ALG_AEAD_AT_LEAST_THIS_LENGTH_FLAG) != 0) &&
            ((alg2 & PSA_ALG_AEAD_AT_LEAST_THIS_LENGTH_FLAG) != 0))
        {
            return PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(alg1, restricted_len);
        }
        /* If only one is a wildcard, return specific algorithm if compatible. */
        if (((alg1 & PSA_ALG_AEAD_AT_LEAST_THIS_LENGTH_FLAG) != 0) &&
            (alg1_len <= alg2_len))
        {
            return alg2;
        }
        if (((alg2 & PSA_ALG_AEAD_AT_LEAST_THIS_LENGTH_FLAG) != 0) &&
            (alg2_len <= alg1_len))
        {
            return alg1;
        }
    }

    /* If the policies are from the same MAC family, check whether one
     * of them is a minimum-MAC-length policy. Calculate the most
     * restrictive tag length.
     */
    if (PSA_ALG_IS_MAC(alg1) && PSA_ALG_IS_MAC(alg2) &&
        (PSA_ALG_FULL_LENGTH_MAC(alg1) ==
         PSA_ALG_FULL_LENGTH_MAC(alg2)))
    {
        /* Validate the combination of key type and algorithm. Since the base
         * algorithm of alg1 and alg2 are the same, we only need this once.
         */
        if (PSA_SUCCESS != psa_mac_key_can_do(alg1, key_type))
        {
            return 0;
        }

        /* Get the (exact or at-least) output lengths for both sides of the
         * requested intersection. None of the currently supported algorithms
         * have an output length dependent on the actual key size, so setting it
         * to a bogus value of 0 is currently OK.
         *
         * Note that for at-least-this-length wildcard algorithms, the output
         * length is set to the shortest allowed length, which allows us to
         * calculate the most restrictive tag length for the intersection.
         */
        size_t alg1_len = PSA_MAC_LENGTH(key_type, 0, alg1);
        size_t alg2_len = PSA_MAC_LENGTH(key_type, 0, alg2);
        size_t restricted_len = alg1_len > alg2_len ? alg1_len : alg2_len;

        /* If both are wildcards, return most restrictive wildcard */
        if (((alg1 & PSA_ALG_MAC_AT_LEAST_THIS_LENGTH_FLAG) != 0) &&
            ((alg2 & PSA_ALG_MAC_AT_LEAST_THIS_LENGTH_FLAG) != 0))
        {
            return PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(alg1, restricted_len);
        }

        /* If only one is an at-least-this-length policy, the intersection would
         * be the other (fixed-length) policy as long as said fixed length is
         * equal to or larger than the shortest allowed length.
         */
        if ((alg1 & PSA_ALG_MAC_AT_LEAST_THIS_LENGTH_FLAG) != 0)
        {
            return (alg1_len <= alg2_len) ? alg2 : 0;
        }

        if ((alg2 & PSA_ALG_MAC_AT_LEAST_THIS_LENGTH_FLAG) != 0)
        {
            return (alg2_len <= alg1_len) ? alg1 : 0;
        }

        /* If none of them are wildcards, check whether they define the same tag
         * length. This is still possible here when one is default-length and
         * the other specific-length. Ensure to always return the
         * specific-length version for the intersection.
         */
        if (alg1_len == alg2_len)
        {
            return PSA_ALG_TRUNCATED_MAC(alg1, alg1_len);
        }
    }
    /* If the policies are incompatible, allow nothing. */
    return 0;
}

/** Restrict a key policy based on a constraint.
 *
 * \note This function requires providing the key type for which the policy is
 *       being restricted, since some algorithm policy definitions (e.g. MAC)
 *       have different properties depending on what kind of cipher it is
 *       combined with.
 *
 * \param[in] key_type      The key type for which to restrict the policy
 * \param[in,out] policy    The policy to restrict.
 * \param[in] constraint    The policy constraint to apply.
 *
 * \retval #PSA_SUCCESS
 *         The target policy fits the constraint policy.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The key type, constraint policy, and target policy are not compatible.
 *         The target policy is left unchanged in this case.
 */
static psa_status_t psa_restrict_key_policy(psa_key_type_t key_type,
                                            psa_key_policy_t *target_policy,
                                            const psa_key_policy_t *constraint)
{
    psa_algorithm_t intersection_alg = psa_key_policy_algorithm_intersection(key_type, target_policy->MBEDTLS_PRIVATE(alg),
                                                                             constraint->MBEDTLS_PRIVATE(alg));

    psa_algorithm_t intersection_alg2 = psa_key_policy_algorithm_intersection(key_type, target_policy->MBEDTLS_PRIVATE(alg2),
                                                                              constraint->MBEDTLS_PRIVATE(alg2));

    if (intersection_alg == 0 && target_policy->MBEDTLS_PRIVATE(alg) != 0 && constraint->MBEDTLS_PRIVATE(alg) != 0)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (intersection_alg2 == 0 && target_policy->MBEDTLS_PRIVATE(alg2) != 0 && constraint->MBEDTLS_PRIVATE(alg2) != 0)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    target_policy->MBEDTLS_PRIVATE(usage) &= constraint->MBEDTLS_PRIVATE(usage);
    target_policy->MBEDTLS_PRIVATE(alg) = intersection_alg;
    target_policy->MBEDTLS_PRIVATE(alg2) = intersection_alg2;
    return PSA_SUCCESS;
}

/*----------------------------------------------------------------------------
 * local_CurveFamilyFromKeyType
 */
static uint8_t
local_CurveFamilyFromKeyType(psa_key_type_t key_type, uint8_t fECDH)
{
    psa_ecc_family_t Family;
    uint8_t CurveFamily = EIP130DOMAIN_ECC_FAMILY_NONE;

    Family = PSA_KEY_TYPE_ECC_GET_FAMILY(key_type);
    if (PSA_ECC_FAMILY_SECP_R1 == Family)
    {
        CurveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
    }
    else if (PSA_ECC_FAMILY_BRAINPOOL_P_R1 == Family)
    {
        CurveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
    }
    else if ((PSA_ECC_FAMILY_MONTGOMERY == Family) &&
                (fECDH != 0U))
    {
        CurveFamily = EIP130DOMAIN_ECC_FAMILY_MONTGOMERY;
    }
    else if ((PSA_ECC_FAMILY_TWISTED_EDWARDS == Family) &&
                (fECDH == 0U))
    {
        CurveFamily = EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS;
    }
    else
    {
        /* Leave CurveFamily as NONE */
    }
    return CurveFamily;
}

/*----------------------------------------------------------------------------
 * local_AsymBigIntToHW
 */
static void
local_AsymBigIntToHW(const uint8_t * const pData,
                     const size_t ModulusSizeBits,
                     const uint8_t BeginItem,
                     const uint8_t Items,
                     uint8_t * pBlob)
{
    uint8_t * ptr = pBlob;
    uint32_t RemainingLength = PSA_ASYM_DATA_SIZE_B2WB(ModulusSizeBits);
    uint32_t CopySize = (uint32_t)PSA_BITS_TO_BYTES(ModulusSizeBits);

    /* Convert big integer from application to HW format. Initialize
     * header with first 16 bits being the length of the sub-vector in bits.
     */
    *ptr = (uint8_t)(ModulusSizeBits);
    ptr++;
    *ptr = (uint8_t)(ModulusSizeBits >> 8);
    ptr++;
    /* BeginItem represents SubVectorIndex in the HSM sub-vector format */
    *ptr = (uint8_t)(BeginItem);
    ptr++;
    /* Items represents DomainID and SubVectCount in the HSM's sub-vector format. The former only needs
     * to be set in the first header word of a sub-vector structure.
     */
    *ptr = (uint8_t)(Items);
    ptr++;

    /* Copy data */
    if (CopySize > RemainingLength)
    {
        /* Prevent buffer overrun */
        LOG_WARN("Warning: Truncated BigInt data to HW conversion (%u > %u)\n",
                 CopySize, RemainingLength);
        CopySize = RemainingLength;
    }
    else
    {
        /* MISRA - Intentionally empty */
    }

    if (ModulusSizeBits != 255U)
    {
        /* Reverse the data */
        psaInt_ReverseMemCpy(ptr, pData, CopySize);
    }
    else
    {
        /* Keys for Curve25519 and Ed25519 are already provided in little endian format, per PSA spec */
        (void)memcpy(ptr, pData, CopySize);
    }


    /* Zeroize remaining part if needed */
    RemainingLength -= CopySize;
    if (0U != RemainingLength)
    {
        (void)memset(&ptr[CopySize], 0, RemainingLength);
    }
    else
    {
        /* MISRA - Intentionally empty */
    }
}


/*----------------------------------------------------------------------------
 * local_AsymBigIntPointToHW
 */
static void
local_AsymBigIntPointToHW(const uint8_t * const pData,
                          const size_t ModulusSizeBits,
                          const uint8_t Items,
                          uint8_t * const pBlob)
{
    /* "Items" is a variable representing the highest 8 bits of an HSM sub-vector header, comprising
     * the DomainID and SubVectCount fields. DomainID (the higher 4 bits) helps distinguish between
     * curve types, while SubVectCount defines the number of components that will make up the
     * sub-vector structure.
     */
    local_AsymBigIntToHW(pData, ModulusSizeBits, 0, Items, pBlob);

    /* Second component of the public key. Provide pointer to data starting
     * after the X component. BeginItem is passed in as '1' to represent the index
     * of the second sub-vector. Mask "Items" since we do not need to set the 'DomainID'
     * field of the header beyond the first in the HSM's sub-vector format. However,
     * the sub-vector count must be included in all sub-vector header words.
     */
    local_AsymBigIntToHW(pData + PSA_BITS_TO_BYTES(ModulusSizeBits),
                         ModulusSizeBits, 1, (uint8_t)(Items & 0x0FU),
                         &pBlob[PSA_ASYM_DATA_VHEADER +
                                PSA_ASYM_DATA_SIZE_B2WB(ModulusSizeBits)]);
}

/*----------------------------------------------------------------------------
 * local_AsymPointOutputFromHW
 */
static void
local_AsymPointOutputFromHW(uint8_t * const pOutput,
                            const size_t ModulusSizeBits,
                            const uint8_t CurveFamily,
                            const uint8_t * const HWFormatInput)
{
    if (CurveFamily == EIP130DOMAIN_ECC_FAMILY_MONTGOMERY)
    {
        /* One component, output should be in little-endian */
        (void)memcpy(&pOutput[0], &HWFormatInput[PSA_ASYM_DATA_VHEADER], PSA_ASYM_DATA_SIZE_B2B(ModulusSizeBits));
    }
    else
    {
        /* Two components, output should be in big-endian octet format */
        uint32_t secondComponentStart;

        pOutput[0] = 0x04;

        psaInt_ReverseMemCpy(&pOutput[1], &HWFormatInput[PSA_ASYM_DATA_VHEADER], PSA_ASYM_DATA_SIZE_B2B(ModulusSizeBits));

        /* In HW format, the second component starts after the first component plus the header of the second component. */
        secondComponentStart = PSA_ASYM_DATA_SIZE_VWB(ModulusSizeBits) + PSA_ASYM_DATA_VHEADER;

        psaInt_ReverseMemCpy(&pOutput[1 + PSA_ASYM_DATA_SIZE_B2B(ModulusSizeBits)],
                             &HWFormatInput[secondComponentStart],
                             PSA_ASYM_DATA_SIZE_B2B(ModulusSizeBits));
    }
}
/*----------------------------------------------------------------------------
 * local_SymKeyType
 *
 * This function handles key asset creation for symmetric keys types.
 * attributes
 *     active key attributes.
 * key_size
 *      key size.
 * AssetPolicy
 *      pointer to fill asset policy.
 *
 * Return Value:
 *     psa_status_t
 *                  one of psa status
 *     AssetPolicy
 *                  Asset policy
 */
static psa_status_t
local_SymKeyType(const psa_key_attributes_t * attributes,
                 size_t key_size,
                 PsaPolicyMask_t * AssetPolicy)
{
    psa_status_t funcres = PSA_SUCCESS;
    psa_key_usage_t psaUsage = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
    psa_algorithm_t psaAlg = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg);

    if (PSA_ALG_IS_MAC(psaAlg))
    {
        if (PSA_ALG_IS_HMAC(psaAlg))
        {
            /* Hash based MAC operation */
            *AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH;
            if ((PSA_KEY_USAGE_SIGN_MESSAGE == (psaUsage & PSA_KEY_USAGE_SIGN_MESSAGE)) ||
                (PSA_KEY_USAGE_VERIFY_MESSAGE == (psaUsage & PSA_KEY_USAGE_VERIFY_MESSAGE)))
            {
                /* The HMAC driver always expects a MAC generate token to be submitted to the HSM.
                 * It will then retrieve the generated MAC and compare it to the expected MAC, in the case
                 * of verify operations. The AssetPolicy is what instructs the token to generate the MAC.
                 */
                *AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            switch (PSA_ALG_HMAC_GET_HASH(psaAlg))
            {
            case PSA_ALG_SHA_1:
                /* Minimum (security) Length limit for HMAC keys is 112/8 */
                if ((key_size < (112U / 8U)) ||
                    (key_size > PSA_SYM_ALGO_MAX_HMAC_SHA2_KEY_SIZE))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA1;
                }
                break;
            case PSA_ALG_SHA_224:
                if ((key_size < ((224U / 8U) / 2U)) ||
                    (key_size > PSA_SYM_ALGO_MAX_HMAC_SHA2_KEY_SIZE))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA224;
                }
                break;
            case PSA_ALG_SHA_256:
                if ((key_size < ((256U / 8U) / 2U)) ||
                    (key_size > PSA_SYM_ALGO_MAX_HMAC_SHA2_KEY_SIZE))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA256;
                }
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case PSA_ALG_SHA_384:
                if ((key_size < ((384U / 8U) / 2U)) ||
                    (key_size > PSA_SYM_ALGO_MAX_HMAC_SHA512_KEY_SIZE))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA384;
                }
                break;
            case PSA_ALG_SHA_512:
                if ((key_size < ((512U / 8U) / 2U)) ||
                    (key_size > PSA_SYM_ALGO_MAX_HMAC_SHA512_KEY_SIZE))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA512;
                }
                break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
            case PSA_ALG_SHA3_224:
                if ((key_size < ((224U / 8U) / 2U)) ||
                    (key_size > (1152U / 8U)))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_224;
                }
                break;
            case PSA_ALG_SHA3_256:
                if ((key_size < ((256U / 8U) / 2U)) ||
                    (key_size > (1088U / 8U)))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_256;
                }
                break;
            case PSA_ALG_SHA3_384:
                if ((key_size < ((384U / 8U) / 2U)) ||
                    (key_size > (832U / 8U)))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_384;
                }
                break;
            case PSA_ALG_SHA3_512:
                if ((key_size < ((512U / 8U) / 2U)) ||
                    (key_size > (576U / 8U)))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_512;
                }
                break;
#endif
            default:
                funcres = PSA_ERROR_INVALID_ARGUMENT;
                break;
            }
        }
        else
        {
            /* Cipher based MAC operation */
            if ((key_size != (128U / 8U)) &&
                (key_size != (192U / 8U)) &&
                (key_size != (256U / 8U)))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                *AssetPolicy = EIP130_ASSET_POLICY_SYM_MACCIPHER;
                if ((PSA_KEY_USAGE_SIGN_MESSAGE == (psaUsage & PSA_KEY_USAGE_SIGN_MESSAGE)) ||
                    (PSA_KEY_USAGE_VERIFY_MESSAGE == (psaUsage & PSA_KEY_USAGE_VERIFY_MESSAGE)))
                {
                    /* The AESCMAC driver always expects a MAC generate token to be submitted to the HSM.
                     * It will then retrieve the generated MAC and compare it to the expected MAC, in the case
                     * of verify operations. The AssetPolicy is what instructs the token to generate the MAC.
                     */
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                if (PSA_ALG_CMAC == psaAlg)
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCMCMCMAC;
                }
                else if (PSA_ALG_CBC_MAC == psaAlg)
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCMCMCBCMAC;
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                if (PSA_KEY_TYPE_AES == attributes->MBEDTLS_PRIVATE(type))
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
                }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
                else if (PSA_KEY_TYPE_ARIA == attributes->MBEDTLS_PRIVATE(type))
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
                }
#endif
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
            }
        }
    }
    else if (PSA_ALG_IS_CIPHER(psaAlg))
    {
        /* Check if the key is allowed to be used with LAES coprocessor */
        if (PSA_KEY_USAGE_COPROCESSOR == (psaUsage & PSA_KEY_USAGE_COPROCESSOR))
        {
            *AssetPolicy = COPROCESSOR_ASSET_POLICY_FLAGS | EIP130_ASSET_POLICY_COPRO1_ALLOW;

            if ((key_size != (128U / 8U)) || (PSA_KEY_TYPE_AES != attributes->MBEDTLS_PRIVATE(type)) ||
                (psaUsage & (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT)) == 0)
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            *AssetPolicy = EIP130_ASSET_POLICY_SYM_CIPHERBULK;
            /* Note that the asset policy will only reflect encryption usage even if both
            * encryption and decryption are set. The key creation APIs that call this function
            * will be responsible for populating the second asset policy differently if decryption
            * should also be allowed by the imported key.
            */
            if (PSA_KEY_USAGE_ENCRYPT == (psaUsage & PSA_KEY_USAGE_ENCRYPT))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
            }
            else if (PSA_KEY_USAGE_DECRYPT == (psaUsage & PSA_KEY_USAGE_DECRYPT))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            if (PSA_KEY_TYPE_AES == attributes->MBEDTLS_PRIVATE(type))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
                if (PSA_ALG_XTS == psaAlg)
                {
                    if ((key_size != (256U / 8U)) &&
                        (key_size != (512U / 8U)))
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                }
                else
                {
                    if ((key_size != (128U / 8U)) &&
                        (key_size != (192U / 8U)) &&
                        (key_size != (256U / 8U)))
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                }
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == attributes->MBEDTLS_PRIVATE(type))
            {
                if ((key_size != (128U / 8U)) &&
                    (key_size != (192U / 8U)) &&
                    (key_size != (256U / 8U)))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
                }
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == attributes->MBEDTLS_PRIVATE(type))
            {
                if (key_size != (3U * (64U / 8U)))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCACTDES;
                }
            }
#endif
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            switch (psaAlg)
            {
            case PSA_ALG_CTR:
#ifndef PSA_REMOVE_SYM_ALGO_3DES
                if (PSA_KEY_TYPE_DES != attributes->MBEDTLS_PRIVATE(type))
#endif
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCTR32;
                }
#ifndef PSA_REMOVE_SYM_ALGO_3DES
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
#endif
                break;
            case PSA_ALG_XTS:
                if (PSA_KEY_TYPE_AES == attributes->MBEDTLS_PRIVATE(type))
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCMCBXTS;
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                break;
            case PSA_ALG_ECB_NO_PADDING:
                *AssetPolicy |= EIP130_ASSET_POLICY_SCMCBECB;
                break;
            case PSA_ALG_CBC_NO_PADDING:
                *AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCBC;
                break;
            default:
                funcres = PSA_ERROR_INVALID_ARGUMENT;
                break;
            }
        }
    }
    else if (PSA_ALG_IS_AEAD(psaAlg))
    {
        /* Check if the key is allowed to be used with LAES coprocessor */
        if (PSA_KEY_USAGE_COPROCESSOR == (psaUsage & PSA_KEY_USAGE_COPROCESSOR))
        {
            *AssetPolicy = COPROCESSOR_ASSET_POLICY_FLAGS | EIP130_ASSET_POLICY_COPRO1_ALLOW;

            if ((key_size != (128U / 8U)) || (PSA_KEY_TYPE_AES != attributes->MBEDTLS_PRIVATE(type)) ||
                (psaUsage & (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT)) == 0)
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            *AssetPolicy = EIP130_ASSET_POLICY_SYM_CIPHERAUTH;

            if (PSA_KEY_USAGE_ENCRYPT == (psaUsage & PSA_KEY_USAGE_ENCRYPT))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
            }
            else if (PSA_KEY_USAGE_DECRYPT == (psaUsage & PSA_KEY_USAGE_DECRYPT))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            if (PSA_KEY_TYPE_AES == attributes->MBEDTLS_PRIVATE(type))
            {
                if ((key_size != (128U / 8U)) &&
                    (key_size != (192U / 8U)) &&
                    (key_size != (256U / 8U)))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
                }
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == attributes->MBEDTLS_PRIVATE(type))
            {
                if ((key_size != (128U / 8U)) &&
                    (key_size != (192U / 8U)) &&
                    (key_size != (256U / 8U)))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
                }
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_CHACHA20
            else if (PSA_KEY_TYPE_CHACHA20 == attributes->MBEDTLS_PRIVATE(type))
            {
                if (key_size != (256U / 8U))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_SCACCHACHA20;
                }
            }
#endif
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }

            switch (psaAlg)
            {
#if !defined(PSA_REMOVE_SYM_ALGO_CHACHA20) && \
    !defined(PSA_REMOVE_SYM_ALGO_POLY1305)
            case PSA_ALG_CHACHA20_POLY1305:
#endif
            case PSA_ALG_CCM:
                *AssetPolicy |= EIP130_ASSET_POLICY_SCMCACCM;
                break;
            case PSA_ALG_GCM:
                *AssetPolicy |= EIP130_ASSET_POLICY_SCMCAGCM;
                break;
            default:
                funcres = PSA_ERROR_INVALID_ARGUMENT;
                break;
            }
        }
    }
    else if (PSA_ALG_IS_SP800_108_COUNTER_MAC(psaAlg))
    {
        *AssetPolicy |= EIP130_ASSET_POLICY_SYM_DERIVE;

        if (psaAlg == PSA_ALG_SP800_108_COUNTER_CMAC)
        {
            /* The psaAlg and AssetPolicy refer to the derived key. In this case, we are
             * deriving another KDK that is neither the HUK nor the TKDK.
             */
            *AssetPolicy |= EIP130_ASSET_POLICY_SCADNORMALCMAC;
        }
        else if (psaAlg == PSA_ALG_SP800_108_COUNTER_HMAC(PSA_ALG_SHA_256))
        {
            /* The psaAlg and AssetPolicy refer to the capabilities of the derived key.
             * In this case, the key being derived is the TKDK.
             */
            *AssetPolicy |= EIP130_ASSET_POLICY_SCADTRUSTED;
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    if (PSA_SUCCESS == funcres)
    {
        if (!psaInt_IsAccessSecure())
        {
            *AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        *AssetPolicy = (PsaPolicyMask_t)0;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * local_MapCurveLengthToHashPolicy
 *
 * This function gets the hash mode to be used in asymmetric key from a key length,
 * for use in cases where a key is imported but the hash algorithm isn't specified.
 *
 * ModulusSizeBits
 *     Length of the curve to find a hash algorithm for.
 * asset_policy
 *      Asset policy to update with hash policy.
 *
 * Return Value:
 *     psa_status_t
 *                  one of psa status
 */
static psa_status_t local_MapCurveLengthToHashPolicy(uint32_t ModulusSizeBits, PsaPolicyMask_t *asset_policy)
{
    psa_status_t status = PSA_SUCCESS;

    switch (ModulusSizeBits)
    {
        case CURVE_LENGTH_192:
        case CURVE_LENGTH_224:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA224;
            break;
        case CURVE_LENGTH_256:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA256;
            break;
        case CURVE_LENGTH_384:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA384;
            break;
        case CURVE_LENGTH_512:
        case CURVE_LENGTH_521:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA512;
            break;
        default:
            status = PSA_ERROR_INVALID_ARGUMENT;
    }
    return status;
}

/*----------------------------------------------------------------------------
 * local_AsymHashPolicy
 *
 * This function get hash mode to be used in asymmetric key and update
 * the policy.
 *
 * alg
 *     active alg to get hash type from.
 * asset_policy
 *      asset policy to update with hash policy.
 *
 * Return Value:
 *     psa_status_t
 *                  one of psa status
 */
static psa_status_t
local_AsymHashPolicy(psa_algorithm_t alg,
                     PsaPolicyMask_t *asset_policy,
                     uint32_t ModulusSizeBits,
                     uint8_t check)
{
    psa_status_t funcres = PSA_SUCCESS;

    /* If the hash alg is NONE or ANY_HASH, we will assign the hash length such that the below error conditions
     * will not be true. Therefore, we do not need to enter this 'check' conditional.
     */
    if ((0U != check) &&
        (PSA_ALG_NONE != PSA_ALG_GET_HASH(alg)) &&
        (PSA_ALG_ANY_HASH != PSA_ALG_GET_HASH(alg)))
    {
        size_t DigestNBits = (8U * PSA_HASH_LENGTH(PSA_ALG_GET_HASH(alg)));
        /* At PSA layer and KeyStore layer, we reject digest lengths that are
         * less than the modulus size, per FIPS 186-4 recommendation. An
         * exception is made at modulus size 521 bits, since a 512 bit hash
         * meets the security strength recommendation for that key size.
         */
        if ((DigestNBits < ModulusSizeBits) && (ModulusSizeBits != 521))
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_SUCCESS == funcres)
    {
        switch (PSA_ALG_GET_HASH(alg))
        {
        case PSA_ALG_SHA_1:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA1;
            break;
        case PSA_ALG_SHA_224:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA224;
            break;
        case PSA_ALG_SHA_256:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case PSA_ALG_SHA_384:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA384;
            break;
        case PSA_ALG_SHA_512:
            *asset_policy |= EIP130_ASSET_POLICY_ACH_SHA512;
            break;
#endif
        case PSA_ALG_NONE:
        case PSA_ALG_ANY_HASH:
            /* If the algorithm doesn't specify a specific hash type (e.g. PSA_ALG_ECDSA_ANY),
             * we will derive it from the curve length corresponding to the key being imported. We
             * will do the same for algorithms that specify ALL hash types using PSA_ALG_ANY_HASH.
             */
            funcres = local_MapCurveLengthToHashPolicy(ModulusSizeBits, asset_policy);
            break;
        default:
            funcres = PSA_ERROR_INVALID_ARGUMENT;
            break;
        }
    }
    else
    {
        /* Error already set */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_AsymKeyType
 *
 * This function handles key asset creation for Asymmetric keys types.
 * attributes
 *     active key attributes.
 * data_length
 *      data size.
 * key
 *      key ID.
 *
 * Return Value:
 *     psa_status_t
 *                  one of psa status
 *     key
 *                  Key ID
 */
static psa_status_t
local_AsymKeyType(const size_t PersistentItemSize,
                  const psa_key_attributes_t * attributes,
                  bool isDerivedKey,
                  const uint8_t * data,
                  size_t data_length,
                  uint8_t * pOutputData,
                  size_t * pOutputDataLength,
                  psa_key_bits_t * modulus_size,
                  PsaPolicyMask_t * AssetPolicy)
{
    psa_status_t funcres = PSA_SUCCESS;
    size_t exponent_size = 0U;
    /* Curve25519 is the only EC curve with a key_bit size that is not exactly 8 times*/
    size_t curve_bits;

    if (attributes->MBEDTLS_PRIVATE(bits) == 0)
    {
        if (PSA_ECC_FAMILY_MONTGOMERY == PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
        {
            curve_bits = 255U;
        }
        else if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
        {
            /* NISTP-521 is a unique case where the key_bit size is not exactly 8 times the byte size */
            curve_bits = (PSA_BYTES_TO_BITS(data_length) == 528U) ?
                          521U : PSA_BYTES_TO_BITS((data_length));
        }
        else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
        {
            /* local_AsymKeyType is only used for Montgomery and Weierstrass ECC public keys currently.
             * Since we check for Montgomery above, this condition catches all Weierstrass public keys,
             * and those are in octet format. So, subtract the header byte, then divide by two
             * (since there are two components in the public key) before converting to a bit value.
             */
            curve_bits = (PSA_BYTES_TO_BITS((data_length-1) / 2U) == 528U) ?
                          521U : PSA_BYTES_TO_BITS((data_length - 1U) / 2U);
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else
    {
        curve_bits = attributes->MBEDTLS_PRIVATE(bits);
    }

    if (PSA_ALG_IS_SIGN(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
    {
        *AssetPolicy = EIP130_ASSET_POLICY_ASYM_SIGNVERIFY;
        if (PSA_KEY_TYPE_IS_RSA(attributes->MBEDTLS_PRIVATE(type)))
        {
            funcres = local_AsymHashPolicy(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg), AssetPolicy, 0U, 0U);
            if (PSA_SUCCESS == funcres)
            {
                Asn1Der_BigNumber Modulus;
                Asn1Der_BigNumber PubExponent;

                if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
                {
                    Asn1Der_BigNumber PrvExponent;

                    if (PSA_ALG_IS_RSA_PSS(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
                    {
                        *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA |
                                        EIP130_ASSET_POLICY_ACA_RSAPSS;

                        if (0U == PersistentItemSize)
                        {
                            funcres = PSAInt_AsymParse_RSA_PSS(data, data_length,
                                                               &Modulus, &PrvExponent,
                                                               &PubExponent);
                        }
                        else
                        {
                            /* MISRA - Intentially empty */
                        }
                    }
                    else if (PSA_ALG_IS_RSA_PKCS1V15_SIGN(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
                    {
                        *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA |
                                        EIP130_ASSET_POLICY_ACA_RSAPKCS1V15;

                        if (0U == PersistentItemSize)
                        {
                            funcres = PSAInt_AsymParse_RSA_PKCS1(data, data_length,
                                                                 &Modulus, &PrvExponent,
                                                                 &PubExponent);
                        }
                        else
                        {
                            /* MISRA - Intentially empty */
                        }
                    }
                    else
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                    if (PSA_SUCCESS == funcres)
                    {
                        if (0U == PersistentItemSize)
                        {
                            *modulus_size = PSA_BYTES_TO_BITS(Modulus.Length);

                            if ((0U != attributes->MBEDTLS_PRIVATE(bits)) &&
                                (*modulus_size != attributes->MBEDTLS_PRIVATE(bits)))
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else
                            {
                                /* Convert to VaultIP HW format */
                                if ((NULL == pOutputData) ||
                                    (NULL == pOutputDataLength) ||
                                    (*pOutputDataLength < (2U * PSA_ASYM_DATA_SIZE_VWB(*modulus_size))))
                                {
                                    funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                                }
                                else
                                {
                                    *pOutputDataLength = 2U * PSA_ASYM_DATA_SIZE_VWB(*modulus_size);
                                    local_AsymBigIntToHW(Modulus.pData, *modulus_size,
                                                         0, 2, pOutputData);
                                    local_AsymBigIntToHW(PrvExponent.pData, *modulus_size,
                                                         1, 2, &pOutputData[PSA_ASYM_DATA_VHEADER +
                                                         Modulus.Length]);
                                }
                            }
                        }
                        else
                        {
                            /* Convert to VaultIP HW format */
                            if ((NULL == pOutputData) ||
                                (NULL == pOutputDataLength))
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else if (0U != curve_bits)
                            {
                                *modulus_size = curve_bits;
                                if (*pOutputDataLength < (2U * PSA_ASYM_DATA_SIZE_VWB(*modulus_size)))
                                {
                                    funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                                }
                                else
                                {
                                    *pOutputDataLength = 2U * PSA_ASYM_DATA_SIZE_VWB(*modulus_size);
                                }
                            }
                            else
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                        }
                    }
                    else
                    {
                        /* Error already set */
                    }
                }
                else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
                {
                    uint8_t fPSS;

                    if (0U == PersistentItemSize)
                    {
                        funcres = PSAInt_AsymParse_RSA_PubKey(data, data_length,
                                                              &Modulus, &PubExponent,
                                                              &fPSS);
                    }
                    else
                    {
                        if (PSA_ALG_IS_RSA_PSS(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
                        {
                            fPSS = 255U;
                        }
                        else
                        {
                            fPSS = 0U;
                        }
                    }
                    if (PSA_SUCCESS == funcres)
                    {
                        if (PSA_ALG_IS_RSA_PSS(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
                        {
                            if (0U != fPSS)
                            {
                                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_RSAPSS |
                                                EIP130_ASSET_POLICY_PUBLICDATA;
                            }
                            else
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                        }
                        else if (PSA_ALG_IS_RSA_PKCS1V15_SIGN(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
                        {
                            if (0U == fPSS)
                            {
                                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_RSAPKCS1V15 |
                                                EIP130_ASSET_POLICY_PUBLICDATA;
                            }
                            else
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                        }
                        else
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                    }
                    else
                    {
                        /* Error already set */
                    }
                    if (PSA_SUCCESS == funcres)
                    {
                        if (0U == PersistentItemSize)
                        {
                            *modulus_size = PSA_BYTES_TO_BITS(Modulus.Length);

                            if ((0U != attributes->MBEDTLS_PRIVATE(bits)) &&
                                (*modulus_size != attributes->MBEDTLS_PRIVATE(bits)))
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else
                            {
                                exponent_size = PSA_BYTES_TO_BITS(PubExponent.Length);

                                /* Convert to VaultIP HW format */
                                if ((NULL == pOutputData) ||
                                    (NULL == pOutputDataLength) ||
                                    (*pOutputDataLength < (PSA_ASYM_DATA_SIZE_VWB(*modulus_size) +
                                                           PSA_ASYM_DATA_SIZE_VWB(exponent_size))))
                                {
                                    funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                                }
                                else
                                {
                                    *pOutputDataLength = (PSA_ASYM_DATA_SIZE_VWB(*modulus_size) +
                                                          PSA_ASYM_DATA_SIZE_VWB(exponent_size));
                                    local_AsymBigIntToHW(Modulus.pData, *modulus_size,
                                                         0, 2, pOutputData);
                                    local_AsymBigIntToHW(PubExponent.pData, exponent_size,
                                                         1, 2, &pOutputData[PSA_ASYM_DATA_VHEADER +
                                                                            Modulus.Length]);
                                }
                            }
                        }
                        else
                        {
                            if (0U != curve_bits)
                            {
                                /* Nothing to do. */
                            }
                            else
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                        }
                    }
                    else
                    {
                        /* Error already set */
                    }
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
            }
            else
            {
                /* Error already set */
            }
        }
        else if (PSA_KEY_TYPE_IS_ECC(attributes->MBEDTLS_PRIVATE(type)))
        {
            if (PSA_ALG_IS_ECDSA(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDSA;

                funcres = local_AsymHashPolicy(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg),
                                               AssetPolicy, curve_bits, 255U);
                if (PSA_SUCCESS == funcres)
                {
                    Asn1Der_BigNumber KeyInfo;
                    size_t CurveBits;
                    uint8_t CurveFamily;
                    /* "items" is a variable representing the highest 8 bits of an HSM sub-vector header, comprising
                     * the DomainID and SubVectCount fields. DomainID (the higher 4 bits) helps distinguish between
                     * curve types, while SubVectCount defines the number of components that will make up the
                     * sub-vector structure.
                     */
                    uint8_t items;

                    /* KEY_PAIR type corresponds to a private key in storage, but its attributes correspond to
                     * the pair of the private key and the public key you can generate from it.
                     */
                    if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
                    {
                        *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA;

                        if (0U == PersistentItemSize)
                        {
                            funcres = PSAInt_AsymParse_EC_SEC1(data, data_length,
                                                               &KeyInfo,
                                                               &CurveFamily,
                                                               &CurveBits,
                                                               NULL);
                            if (PSA_SUCCESS == funcres)
                            {
                                switch (CurveFamily)
                                {
                                case EIP130DOMAIN_ECC_FAMILY_NIST_P:
                                    if (PSA_ECC_FAMILY_SECP_R1 !=
                                        PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                                    {
                                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                                    }
                                    else
                                    {
                                        /* This will set DomainID to 0, and SubVectCount to 1 for this sub-vector. */
                                        items = 0x1U;
                                    }
                                    break;
                                case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
                                    if (PSA_ECC_FAMILY_BRAINPOOL_P_R1 !=
                                        PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                                    {
                                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                                    }
                                    else
                                    {
                                        /* This will set DomainID to 1, and SubVectCount to 1 for this sub-vector. Brainpool
                                         * curves have a different domain than SECP curves.
                                         */
                                        items = 0x11U;
                                    }
                                    break;
                                default:
                                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                                    break;
                                }
                            }
                            else
                            {
                                /* Error already set */
                            }
                        }
                        else
                        {
                            /* Validate the key type belongs to a support ECC family */
                            switch (PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                            {
                            case PSA_ECC_FAMILY_SECP_R1:
                                items = 0x1U;
                                break;
                            case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
                                items = 0x11U;
                                break;
                            default:
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                                break;
                            }
                        }
                        if (PSA_SUCCESS == funcres)
                        {
                            if (0U == PersistentItemSize)
                            {
                                if (attributes->MBEDTLS_PRIVATE(bits) != CurveBits)
                                {
                                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                                }
                                else
                                {
                                    /* Convert to VaultIP HW format */
                                    if ((NULL == pOutputData) ||
                                        (NULL == pOutputDataLength))
                                    {
                                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                                    }
                                    else if (*pOutputDataLength < PSA_ASYM_DATA_SIZE_VWB(CurveBits))
                                    {
                                        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                                    }
                                    else
                                    {
                                        *modulus_size = CurveBits;

                                        *pOutputDataLength = PSA_ASYM_DATA_SIZE_VWB(CurveBits);
                                        local_AsymBigIntToHW(KeyInfo.pData, CurveBits, 0,
                                                             items, pOutputData);
                                    }
                                }
                            }
                            else
                            {
                                if (0U != curve_bits)
                                {
                                    *modulus_size = curve_bits;

                                    /* Convert to VaultIP HW format */
                                    if (isDerivedKey)
                                    {
                                        /* Nothing to do - there are no input or output buffers of key material to format */
                                    }
                                    else if ((NULL == pOutputData) ||
                                        (NULL == pOutputDataLength) ||
                                        (*pOutputDataLength < (PSA_ASYM_DATA_SIZE_VWB(curve_bits))))
                                    {
                                        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                                    }
                                    else
                                    {
                                        /* Set the output data length to the curve_bits in bytes plus the number
                                         * of bytes for the sub-vector header word.
                                         */
                                        *pOutputDataLength = PSA_ASYM_DATA_SIZE_VWB(curve_bits);

                                        /* Pass key data directly in. API changed to take data pointer
                                         * instead of ASN1DerBigNumber.
                                         */
                                        local_AsymBigIntToHW(data, curve_bits, 0,
                                                             items, pOutputData);
                                    }
                                }
                                else
                                {
                                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                                }
                            }
                        }
                        else
                        {
                            /* Error already set */
                        }
                    }
                    else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
                    {
                        uint8_t fECDH = 0U;
                        funcres = psaInt_KeyMgmtReadECPubKey(PersistentItemSize, data, data_length,
                                                             PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)),
                                                             curve_bits,
                                                             &CurveFamily, &CurveBits,
                                                             &fECDH,
                                                             pOutputData,
                                                             pOutputDataLength);
                        if (PSA_SUCCESS == funcres)
                        {
                            if (0U != fECDH)
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else
                            {
                                *modulus_size = CurveBits;
                            }
                        }
                        else
                        {
                            /* Error already set */
                        }
                    }
                    else
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                }
                else
                {
                    /* Error already set */
                }
            }
            else if (PSA_ALG_PURE_EDDSA == attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg))
            {
                Asn1Der_BigNumber KeyInfo;
                size_t CurveBits;
                uint8_t CurveFamily;

                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_EDDSA | EIP130_ASSET_POLICY_ACH_SHA512;

                if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
                {
                    *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA;

                    if (0U == PersistentItemSize)
                    {
                        funcres = PSAInt_AsymParse_EC_EdX(data, data_length,
                                                          &KeyInfo,
                                                          &CurveFamily, &CurveBits,
                                                          NULL);
                        if (PSA_SUCCESS == funcres)
                        {
                            if ((CurveFamily != EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS) ||
                                (PSA_ECC_FAMILY_TWISTED_EDWARDS !=
                                 PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type))))
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else
                            {
                                if (attributes->MBEDTLS_PRIVATE(bits) != CurveBits)
                                {
                                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                                }
                                else
                                {
                                    *modulus_size = CurveBits;

                                    /* Convert to VaultIP HW format */
                                    if ((NULL == pOutputData) ||
                                        (NULL == pOutputDataLength) ||
                                        (*pOutputDataLength < PSA_ASYM_DATA_SIZE_VWB(CurveBits)))
                                    {
                                        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                                    }
                                    else
                                    {
                                        *pOutputDataLength = PSA_ASYM_DATA_SIZE_VWB(CurveBits);
                                        local_AsymBigIntToHW(KeyInfo.pData, CurveBits, 0,
                                                             0x11U, pOutputData);
                                    }
                                }
                            }
                        }
                        else
                        {
                            /* Error already set */
                        }
                    }
                    else
                    {
                        if (PSA_ECC_FAMILY_TWISTED_EDWARDS !=
                             PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                        else
                        {
                            if (0U != curve_bits)
                            {
                                *modulus_size = curve_bits;

                                /* Convert to VaultIP HW format */
                                if (isDerivedKey)
                                {
                                    /* Nothing to do - there are no input or output buffers of key material to format */
                                }
                                else if ((NULL == pOutputData) ||
                                    (NULL == pOutputDataLength) ||
                                    (*pOutputDataLength < (PSA_ASYM_DATA_SIZE_VWB(curve_bits))))
                                {
                                    funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                                }
                                else
                                {
                                    /* Set the output data length to the curve_bits in bytes plus the number
                                     * of bytes for the sub-vector header word.
                                     */
                                    *pOutputDataLength = PSA_ASYM_DATA_SIZE_VWB(curve_bits);

                                    local_AsymBigIntToHW(data, curve_bits, 0,
                                                         0x11, pOutputData);
                                }
                            }
                            else
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                        }
                    }
                }
                else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
                {
                    uint8_t fECDH;

                    if (0U == PersistentItemSize)
                    {
                        funcres = psaInt_KeyMgmtReadECPubKey(PersistentItemSize, data, data_length,
                                                             PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)),
                                                             attributes->MBEDTLS_PRIVATE(bits),
                                                             &CurveFamily, &CurveBits,
                                                             &fECDH,
                                                             pOutputData,
                                                             pOutputDataLength);
                        if (PSA_SUCCESS == funcres)
                        {
                            if (0U != fECDH)
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else
                            {
                                *modulus_size = CurveBits;
                            }
                        }
                        else
                        {
                            /* Error already set */
                        }
                    }
                    else
                    {
                        if (PSA_ECC_FAMILY_TWISTED_EDWARDS !=
                             PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                        else
                        {
                            if (0U != curve_bits)
                            {
                                *modulus_size  = curve_bits;

                                /* Convert to VaultIP HW format */
                                if (isDerivedKey)
                                {
                                    /* Nothing to do - there are no input or output buffers of key material to format */
                                }
                                else if ((NULL == pOutputData) ||
                                    (NULL == pOutputDataLength) ||
                                    (*pOutputDataLength < (PSA_ASYM_DATA_SIZE_VWB(curve_bits))))
                                {
                                    funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                                }
                                else
                                {
                                    /* Set the output data length to the curve_bits in bytes plus the number
                                        * of bytes for the sub-vector header word.
                                        */
                                    *pOutputDataLength = PSA_ASYM_DATA_SIZE_VWB(curve_bits);

                                    local_AsymBigIntToHW(data, curve_bits, 0,
                                                         0x11, pOutputData);
                                }
                            }
                            else
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                        }
                    }
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else if (PSA_ALG_IS_ASYMMETRIC_ENCRYPTION(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
    {
        *AssetPolicy = EIP130_ASSET_POLICY_ASYM_DECENC;
        if (PSA_ALG_RSA_PKCS1V15_CRYPT == attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg))
        {
            *AssetPolicy |= EIP130_ASSET_POLICY_ACA_RSAPKCS1V15;
        }
        else if (PSA_ALG_IS_RSA_OAEP(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
        {
            *AssetPolicy |= EIP130_ASSET_POLICY_ACA_RSAOEAP;
            funcres = local_AsymHashPolicy(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg), AssetPolicy, 0U, 0U);
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        if (PSA_SUCCESS == funcres)
        {
            Asn1Der_BigNumber Modulus;
            Asn1Der_BigNumber PubExponent;

            if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
            {
                Asn1Der_BigNumber PrvExponent;

                *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA |
                                EIP130_ASSET_POLICY_STANY;

                if (0U == PersistentItemSize)
                {
                    funcres = PSAInt_AsymParse_RSA_PKCS1(data, data_length,
                                                         &Modulus, &PrvExponent,
                                                         &PubExponent);
                    if (PSA_SUCCESS == funcres)
                    {
                        if (PrvExponent.Length <= Modulus.Length)
                        {
                            *modulus_size  = PSA_BYTES_TO_BITS(Modulus.Length);

                            /* Convert to VaultIP HW format */
                            if ((NULL == pOutputData) ||
                                (NULL == pOutputDataLength) ||
                                (*pOutputDataLength < (2U * PSA_ASYM_DATA_SIZE_VWB(*modulus_size))))
                            {
                                funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                            }
                            else
                            {
                                *pOutputDataLength = 2U * PSA_ASYM_DATA_SIZE_VWB(*modulus_size);
                                if (attributes->MBEDTLS_PRIVATE(bits) == (*modulus_size))
                                {
                                    local_AsymBigIntToHW(Modulus.pData, *modulus_size,
                                                         0, 2, pOutputData);
                                    local_AsymBigIntToHW(PrvExponent.pData, *modulus_size,
                                                         1, 2, &pOutputData[PSA_ASYM_DATA_VHEADER +
                                                                            Modulus.Length]);
                                }
                                else
                                {
                                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                                }
                            }
                        }
                        else
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                    }
                    else
                    {
                        /* Error already set */
                    }
                }
                else
                {
                    if (0U != curve_bits)
                    {
                        /* Nothing to do. */
                    }
                    else
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                }
            }
            else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
            {
                uint8_t fPSS;

                if (0U == PersistentItemSize)
                {
                    funcres = PSAInt_AsymParse_RSA_PubKey(data, data_length,
                                                          &Modulus, &PubExponent,
                                                          &fPSS);
                    if (PSA_SUCCESS == funcres)
                    {
                        if (0U == fPSS)
                        {
                            *modulus_size = PSA_BYTES_TO_BITS(Modulus.Length);
                            exponent_size = PSA_BYTES_TO_BITS(PubExponent.Length);

                            /* Convert to VaultIP HW format */
                            if ((NULL == pOutputData) ||
                                (NULL == pOutputDataLength) ||
                                (*pOutputDataLength < (PSA_ASYM_DATA_SIZE_VWB(*modulus_size) +
                                                       PSA_ASYM_DATA_SIZE_VWB(exponent_size))))
                            {
                                funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                            }
                            else
                            {
                                *pOutputDataLength = (PSA_ASYM_DATA_SIZE_VWB(*modulus_size) +
                                                      PSA_ASYM_DATA_SIZE_VWB(exponent_size));
                                if (attributes->MBEDTLS_PRIVATE(bits) == (*modulus_size))
                                {
                                    local_AsymBigIntToHW(Modulus.pData, *modulus_size,
                                                         0, 2, pOutputData);
                                    local_AsymBigIntToHW(PubExponent.pData, exponent_size,
                                                         1, 2, &pOutputData[PSA_ASYM_DATA_VHEADER +
                                                                            Modulus.Length]);
                                }
                                else
                                {
                                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                                }
                            }
                        }
                        else
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                    }
                    else
                    {
                        /* Error already set */
                    }
                }
                else
                {
                    if (0U != curve_bits)
                    {
                        /* Nothing to do. */
                    }
                    else
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                }
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            /* Error already set */
        }
    }
    else if (PSA_ALG_IS_KEY_AGREEMENT(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
    {
        *AssetPolicy = EIP130_ASSET_POLICY_ASYM_KEYEXCHANGE;
        if (PSA_ALG_IS_FFDH(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if (PSA_ALG_IS_ECDH(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
        {
            Asn1Der_BigNumber KeyInfo;
            size_t CurveBits;
            uint8_t CurveFamily;
            uint8_t items;

            if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA |
                                EIP130_ASSET_POLICY_STANY;

                if (PSA_ECC_FAMILY_MONTGOMERY ==
                    PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                {
                    if (0U == PersistentItemSize)
                    {
                        funcres = PSAInt_AsymParse_EC_EdX(data, data_length,
                                                          &KeyInfo,
                                                          &CurveFamily, &CurveBits,
                                                          NULL);
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                }
                else if ((PSA_ECC_FAMILY_SECP_R1 ==
                          PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type))) ||
                         (PSA_ECC_FAMILY_BRAINPOOL_P_R1 ==
                          PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type))))
                {
                    if (0U == PersistentItemSize)
                    {
                        funcres = PSAInt_AsymParse_EC_SEC1(data, data_length,
                                                           &KeyInfo,
                                                           &CurveFamily, &CurveBits,
                                                           NULL);
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                if (PSA_SUCCESS == funcres)
                {
                    if (0U == PersistentItemSize)
                    {
                        switch (CurveFamily)
                        {
                        case EIP130DOMAIN_ECC_FAMILY_NIST_P:
                            if (PSA_ECC_FAMILY_SECP_R1 !=
                                    PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else
                            {
                                items = 0x1U;
                                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
                            }
                            break;
                        case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
                            if (PSA_ECC_FAMILY_BRAINPOOL_P_R1 !=
                                    PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else
                            {
                                items = 0x11U;
                                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
                            }
                            break;
                        case EIP130DOMAIN_ECC_FAMILY_MONTGOMERY:
                            if (PSA_ECC_FAMILY_MONTGOMERY !=
                                    PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                            {
                                funcres = PSA_ERROR_INVALID_ARGUMENT;
                            }
                            else
                            {
                                items = 0x01U;
                                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_CURVE25519;
                            }
                            break;
                        default:
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                            break;
                        }
                    }
                    else
                    {
                        switch (PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                        {
                        case PSA_ECC_FAMILY_SECP_R1:
                            *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
                            items = 0x1U;
                            break;
                        case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
                            *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
                            items = 0x11U;
                            break;
                        case PSA_ECC_FAMILY_MONTGOMERY:
                            *AssetPolicy |= EIP130_ASSET_POLICY_ACA_CURVE25519;
                            items = 0x01U;
                            break;
                        default:
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                            break;
                        }
                    }
                }
                else
                {
                    /* Error already set */
                }
                if (PSA_SUCCESS == funcres)
                {
                    if (0U == PersistentItemSize)
                    {
                        if (attributes->MBEDTLS_PRIVATE(bits) != CurveBits)
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                        else
                        {
                            *modulus_size = CurveBits;

                            /* Convert to VaultIP HW format */
                            if ((NULL == pOutputData) ||
                                (NULL == pOutputDataLength) ||
                                (*pOutputDataLength < PSA_ASYM_DATA_SIZE_VWB(CurveBits)))
                            {
                                funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                            }
                            else
                            {
                                *pOutputDataLength = PSA_ASYM_DATA_SIZE_VWB(CurveBits);
                                local_AsymBigIntToHW(KeyInfo.pData, CurveBits, 0,
                                                     items, pOutputData);
                            }
                        }
                    }
                    else
                    {
                        if (isDerivedKey)
                        {
                            /* There are no input or output buffers of key material to format. Nothing
                             * to do.
                             */
                        }
                        else if ((NULL == pOutputData) || (NULL == pOutputDataLength))
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                        else if (*pOutputDataLength < PSA_ASYM_DATA_SIZE_VWB(curve_bits))
                        {
                            funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                        }
                        else if (0U != curve_bits)
                        {
                            *modulus_size = curve_bits;
                            *pOutputDataLength = PSA_ASYM_DATA_SIZE_VWB(*modulus_size);

                            /* Pass key data directly in to be HSM sub-vector formatted. Note that
                             * curve_bits will be 255 if Curve25519 is being used. In that case, the
                             * following API will use that information to determine that the data is
                             * already in little-endian format.
                             */
                            local_AsymBigIntToHW(data, curve_bits, 0,
                                                 items, pOutputData);

                            /* If Curve25519 is used, the private key stored should be pruned. However, it cannot be done
                             * inside of local_AsymBigIntToHW(), since that is also used for Curve25519 Public Keys, which
                             * must not be pruned.
                             */
                            if (curve_bits == 255U)
                            {
                                /* Prune the private key. It is now in HW format, so we must skip the header word
                                 * to prune the 0th and 31st bytes of the key material.
                                 */
                                pOutputData[PSA_ASYM_DATA_VHEADER] &= 0xF8UL;
                                pOutputData[PSA_ASYM_DATA_VHEADER + 31] &= 0x7FFUL;
                                pOutputData[PSA_ASYM_DATA_VHEADER + 31] |= 0x40UL;
                            }
                        }
                        else
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                    }
                }
                else
                {
                    /* Error already set */
                }
            }
            else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
            {
                uint8_t fECDH = 0U;

                /* Convert the public key from its given format to the HSM sub-vector format. Note that if
                 * the provided 'bits' value is 255, then the HSM sub-vector formatting API will know that the provided
                 * material is already in little-endian ordering. Per the PSA spec, public keys for Montgomery curves
                 * must be provided in little-endian. This will provide the output into pOutputData and the corresponding
                 * size into pOutputDataLength.
                 */
                funcres = psaInt_KeyMgmtReadECPubKey(PersistentItemSize, data, data_length,
                                                     PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)),
                                                     curve_bits,
                                                     &CurveFamily, &CurveBits,
                                                     &fECDH,
                                                     pOutputData,
                                                     pOutputDataLength);
                if (0U != PersistentItemSize)
                {
                    /* If PersistentItemSize is non-zero, the input is not ASN1DER-formatted - this is the default case.
                     * fECDH is only populated by the prior API if the public key was given in ASN1DER format.
                     * Otherwise, we can assume ECDH by the given key attributes.
                     */
                    fECDH = 255U;
                }

                switch (PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                {
                case PSA_ECC_FAMILY_SECP_R1:
                case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
                    *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
                    break;
                case PSA_ECC_FAMILY_MONTGOMERY:
                    *AssetPolicy |= EIP130_ASSET_POLICY_ACA_CURVE25519;
                    break;
                default:
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                    break;
                }

                if (PSA_SUCCESS == funcres)
                {
                    if (0U == PersistentItemSize)
                    {
                        if (0U == fECDH)
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                        else
                        {
                            *modulus_size = CurveBits;
                        }
                    }
                    else
                    {
                        if (0U != curve_bits)
                        {
                            *modulus_size = curve_bits;
                        }
                        else
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                    }
                }
                else
                {
                    /* Error already set */
                }
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    if (PSA_SUCCESS == funcres)
    {
        if (!psaInt_IsAccessSecure())
        {
            *AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        *AssetPolicy = (PsaPolicyMask_t)0;
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_AsymKeyGenType
 */
static psa_status_t
local_AsymKeyGenType(const psa_key_attributes_t * attributes,
                     uint8_t * pCurveFamily,
                     size_t * pModulusSize,
                     uint8_t * pfECDH,
                     PsaPolicyMask_t * AssetPolicy)
{
    psa_status_t funcres = PSA_SUCCESS;

    if (PSA_ALG_IS_SIGN(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
    {
        *pfECDH = 0U;
        *AssetPolicy = EIP130_ASSET_POLICY_ASYM_SIGNVERIFY;
        if (PSA_KEY_TYPE_IS_ECC(attributes->MBEDTLS_PRIVATE(type)))
        {
            *pModulusSize = (size_t)attributes->MBEDTLS_PRIVATE(bits);

            if (PSA_ALG_IS_ECDSA(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDSA;

                if (PSA_ECC_FAMILY_SECP_R1 ==
                    PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                {
                    *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
                }
                else if (PSA_ECC_FAMILY_BRAINPOOL_P_R1 ==
                         PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                {
                    *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                if (PSA_SUCCESS == funcres)
                {
                    funcres = local_AsymHashPolicy(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg),
                                                   AssetPolicy, *pModulusSize, 255U);
                }
                else
                {
                    /* Error already set */
                }
                if (PSA_SUCCESS == funcres)
                {
                    if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
                    {
                        *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA;
                    }
                    else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
                    {
                        /* The AssetPolicy is already OK */
                    }
                    else
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                }
                else
                {
                    /* Error already set */
                }
            }
            else if (PSA_ALG_PURE_EDDSA == attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_EDDSA | EIP130_ASSET_POLICY_ACH_SHA512;

                if (PSA_ECC_FAMILY_TWISTED_EDWARDS ==
                    PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
                {
                    *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS;
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                if (PSA_SUCCESS == funcres)
                {
                    if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
                    {
                        *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA;
                    }
                    else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
                    {
                        /* The AssetPolicy is already OK */
                    }
                    else
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                }
                else
                {
                    /* Error already set */
                }
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else if (PSA_ALG_IS_KEY_AGREEMENT(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
    {
        *AssetPolicy = EIP130_ASSET_POLICY_ASYM_KEYEXCHANGE;
        if (PSA_ALG_IS_FFDH(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if (PSA_ALG_IS_ECDH(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
        {
            *pfECDH = 255U;
            *pModulusSize = (size_t)attributes->MBEDTLS_PRIVATE(bits);
            if (PSA_ECC_FAMILY_SECP_R1 ==
                PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
            {
                *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
            }
            else if (PSA_ECC_FAMILY_BRAINPOOL_P_R1 ==
                     PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
            {
                *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_ECDH;
            }
            else if (PSA_ECC_FAMILY_MONTGOMERY ==
                     PSA_KEY_TYPE_ECC_GET_FAMILY(attributes->MBEDTLS_PRIVATE(type)))
            {
                *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_MONTGOMERY;
                *AssetPolicy |= EIP130_ASSET_POLICY_ACA_CURVE25519;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            if (PSA_KEY_TYPE_IS_KEY_PAIR(attributes->MBEDTLS_PRIVATE(type)))
            {
                *AssetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA |
                                EIP130_ASSET_POLICY_STANY;

                switch (*pCurveFamily)
                {
                case EIP130DOMAIN_ECC_FAMILY_NIST_P:
                    break;
                case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
                case EIP130DOMAIN_ECC_FAMILY_MONTGOMERY:
                    break;
                default:
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                    break;
                }
            }
            else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->MBEDTLS_PRIVATE(type)))
            {
                /* The AssetPolicy is already OK */
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    if (PSA_SUCCESS == funcres)
    {
        if (!psaInt_IsAccessSecure())
        {
            *AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        *AssetPolicy = (PsaPolicyMask_t)0;
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_AsymKeyGenPrv
 *
 * Generates the private key for the ECDH, ECDSA, X25519 and ed25519
 * functionality based on standard EC curves.
 */
static psa_status_t
local_AsymKeyGenPrv(PsaPolicyMask_t AssetPolicy,
                    uint8_t CurveFamily,
                    size_t ModulusSize,
                    PsaAssetId_t * pAssetId,
                    const uint8_t * output,
                    const size_t * output_length)
{
    PsaAssetId_t KekAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t PrvKeyAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t PubKeyAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t DomainAssetId = PSA_ASSETID_INVALID;
    size_t KeySize;
    VexTokenCmd_PkAssetGenKey_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    psa_status_t funcres;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;

    funcres = psaInt_AsymEccInstallCurve(CurveFamily, ModulusSize,
                                         &DomainAssetId);
    if (PSA_SUCCESS == funcres)
    {
        /* Create the private key Asset */
        KeySize = PSA_ASYM_DATA_SIZE_VWB(ModulusSize);
        if (NULL == pAssetId)
        {
            /* Assume key blob must be output */
            if ((NULL == output) ||
                (NULL == output_length))
            {
                /* Safeguard: Should not happen
                 *            because the buffer is always provided */
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                if (*output_length < PSA_KEYBLOB_SIZE(KeySize))
                {
                    /* Safeguard: Should not happen
                     *            because the buffer should be big enough */
                    funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        if (PSA_SUCCESS == funcres)
        {
            funcres = psaInt_AssetAlloc(AssetPolicy, KeySize, &PrvKeyAssetId);
        }
        else
        {
            /* Error already set */
        }
    }
    else
    {
        /* Error already set */
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Create the public key Asset */
        PsaPolicyMask_t PubAssetPolicy = (AssetPolicy & (~(EIP130_ASSET_POLICY_PRIVATEDATA |
                                                           EIP130_ASSET_POLICY_STANY))) |
                                         EIP130_ASSET_POLICY_PUBLICDATA;
        switch (CurveFamily)
        {
        case EIP130DOMAIN_ECC_FAMILY_NIST_P:
        case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
            funcres = psaInt_AssetAlloc(PubAssetPolicy, (2U * KeySize),
                                        &PubKeyAssetId);
            break;
        case EIP130DOMAIN_ECC_FAMILY_MONTGOMERY:
        case EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS:
            funcres = psaInt_AssetAlloc(PubAssetPolicy, KeySize,
                                        &PubKeyAssetId);
            break;
        default:
            /* Safeguard: Should never happen, checked when installing the curve */
            funcres = PSA_ERROR_NOT_SUPPORTED;
            break;
        }
    }
    else
    {
        /* Error already set */
    }
    if ((PSA_SUCCESS == funcres) &&
        (NULL == pAssetId))
    {
        /* Get the KEK AssetId for the private key key blob. If
         * we retrieve success, we are guaranteed to have a valid
         * AssetID.
         */
        funcres = psaInt_AssetGetKeyBlobKEK(&KekAssetId);
    }
    else
    {
        /* Error already set */
    }

    if (PSA_SUCCESS == funcres)
    {
        /* Generate a key pair */
        /* Format service request */
        t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_PUBLIC_KEY;
        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_PK_WITHASSETS;
        if (CurveFamily == EIP130DOMAIN_ECC_FAMILY_MONTGOMERY)
        {
            t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_CURVE25519_GEN_KEYPAIR;
        }
        else if (CurveFamily == EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS)
        {
            t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_EDDSA_GEN_KEYPAIR;
        }
        else
        {
            t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_ECDH_ECDSA_GEN_KEYPAIR;
        }
        t_cmd.ModulusSizeInBits = (uint32_t)ModulusSize;
        t_cmd.DivisorSizeInBits = (uint32_t)ModulusSize;
        t_cmd.PrivKeyAssetId = PrvKeyAssetId;
        t_cmd.PubKeyAssetId = PubKeyAssetId;
        t_cmd.DomainAssetId = DomainAssetId;
        t_cmd.KekAssetId = KekAssetId;
        if (PSA_ASSETID_INVALID != KekAssetId)
        {
            psaInt_AssetGetKeyBlobLabel(t_cmd.AssociatedData,
                                        &t_cmd.AssociatedDataSize);
        }
        else
        {
            t_cmd.AssociatedDataSize = 0U;
        }
        t_cmd.KeyBlob_p = output;
        t_cmd.KeyBlobSize = (uint32_t)PSA_KEYBLOB_SIZE(KeySize);
        t_cmd.PubKey_p = NULL;
        t_cmd.PubKeySize = 0U;
        t_res.Result = 0;

        /* Exchange service request with the next driver level */
        funcres = psaInt_ExchangeToken((VexTokenCmd_Generic_t *)&t_cmd,
                                       sizeof(t_cmd),
                                       (VexTokenRslt_Generic_t *)&t_res,
                                       sizeof(t_res));
        if (PSA_SUCCESS == funcres)
        {
            if (0 > t_res.Result)
            {
#ifdef PSA_LOG_LOWLEVEL_ERROR
                LOG_WARN("Abort - %s()=%d\n", __func__, t_res.Result);
#endif
                funcres = PSA_ERROR_CORRUPTION_DETECTED;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
        else
        {
            /* Error already set */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    /* Release the used Assets if applicable */
    if (PSA_ASSETID_INVALID != PrvKeyAssetId)
    {
        if (NULL == pAssetId)
        {
            /* Assume private key key blob output */
            removalResult = psaInt_AssetFree(PrvKeyAssetId);
            if (removalResult != PSA_SUCCESS)
            {
                funcres = removalResult;
            }
        }
        else
        {
            /* Return private key AssetId */
            *pAssetId = PrvKeyAssetId;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != PubKeyAssetId)
    {
        removalResult = psaInt_AssetFree(PubKeyAssetId);
        if (removalResult != PSA_SUCCESS)
        {
            funcres = removalResult;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != KekAssetId)
    {
        removalResult = psaInt_AssetFree(KekAssetId);
        if (removalResult != PSA_SUCCESS)
        {
            funcres = removalResult;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != DomainAssetId)
    {
        removalResult = psaInt_AssetFree(DomainAssetId);
        if (removalResult != PSA_SUCCESS)
        {
            funcres = removalResult;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_AsymKeyGenPub
 *
 * @brief Generates the public key for the given ECDH, ECDSA, X25519 or ed25519
 * private key.
 *
 * @param [in] PrvKeyAssetId AssetID of private key to generate pubKey from.
 *
 * @param [out] PubKeyAssetId AssetID of public key to populate if non-NULL
 *
 * @param [in] AssetPolicy AssetPolicy of private key to derive public key policy
 *
 * @param [in] componentFormat Request to return pubKey in component or octet format
 *
 * @param [in] CurveFamily Curve family to generate for
 *
 * @param [in] ModulusSizeInBits Number of bits for the curve modulus
 *
 * @param [in] fECDH Whether or not the private key's alg is KEY_AGREEMENT
 *
 * @param [out] data Output pointer for public key if non-NULL
 *
 * @param [in] data_size Size of buffer to write public key too, if data non-NULL
 *
 * @param [out] data_length Actual size of public key returned, if data non-NULL
 *
 */
static psa_status_t
local_AsymKeyGenPub(PsaAssetId_t PrvKeyAssetId,
                    PsaAssetId_t *PubKeyAssetId,
                    PsaPolicyMask_t AssetPolicy,
                    bool componentFormat,
                    uint8_t CurveFamily,
                    size_t ModulusSizeInBits,
                    uint8_t fECDH,
                    uint8_t * data,
                    size_t data_size,
                    size_t * data_length)
{
    PsaAssetId_t LocalDomainAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t LocalPubKeyAssetId = PSA_ASSETID_INVALID;
    /* Size of the public key in component format */
    size_t PubKeySize;
    /* Size of the public key in format for application - octet string in most cases */
    size_t RealPubKeySize;
    uint32_t Method;
    psa_status_t funcres;
    HSMSALStatus_t status;
    int32_t tokenResult;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;
    uint8_t octetBytePresent = 0;

    /* If the caller requests an asset, the asset must be loaded from component form so componentFormat should
     * be true. However, if the caller requests plaintext, it could be in either component or octet form, depending
     * on if the caller is serving a driver or the application.
     */
    if (((PubKeyAssetId == NULL) && (data != NULL) && (data_size != 0U) && (data_length != NULL)) ||
        ((PubKeyAssetId != NULL) && (data == NULL) && (data_size == 0U) && (data_length == NULL) && (componentFormat == true)))
    {
        funcres = PSA_SUCCESS;
    }
    else
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }

    if (PSA_SUCCESS == funcres)
    {
        /* Create and load curve asset */
        funcres = psaInt_AsymEccInstallCurve(CurveFamily, ModulusSizeInBits,
                                             &LocalDomainAssetId);
    }
    else
    {
        /* Error already set */
    }

    if (PSA_SUCCESS == funcres)
    {
        /* Create the public key Asset */
        switch (CurveFamily)
        {
        case EIP130DOMAIN_ECC_FAMILY_NIST_P:
        case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
            Method = (uint32_t)VEXTOKEN_PKAS_ECDH_ECDSA_GEN_PUBKEY;
            PubKeySize = 2U * PSA_ASYM_DATA_SIZE_VWB(ModulusSizeInBits);
            RealPubKeySize = 2U * PSA_ASYM_DATA_SIZE_B2B(ModulusSizeInBits);
            octetBytePresent = 1;
            break;
        case EIP130DOMAIN_ECC_FAMILY_MONTGOMERY:
            Method = (uint32_t)VEXTOKEN_PKAS_CURVE25519_GEN_PUBKEY;
            PubKeySize = PSA_ASYM_DATA_SIZE_VWB(ModulusSizeInBits);
            RealPubKeySize = PSA_ASYM_DATA_SIZE_B2B(ModulusSizeInBits);
            break;
        case EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS:
            Method = (uint32_t)VEXTOKEN_PKAS_EDDSA_GEN_PUBKEY;
            PubKeySize = PSA_ASYM_DATA_SIZE_VWB(ModulusSizeInBits);
            RealPubKeySize = PSA_ASYM_DATA_SIZE_B2B(ModulusSizeInBits);
            break;
        default:
            /* Safeguard: Should never happen, already checked earlier */
            funcres = PSA_ERROR_NOT_SUPPORTED;
            break;
        }

        if (PSA_SUCCESS == funcres)
        {
            if((componentFormat) && (PubKeyAssetId == NULL))
            {
                if (data_size < PubKeySize)
                {
                    funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
            else if (PubKeyAssetId == NULL)
            {
                /* Add one for octet byte */
                if (data_size < (RealPubKeySize + octetBytePresent))
                {
                    funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
            else
            {
                /* No buffer size validation necessary if returning asset ID */
            }
        }
        else
        {
            /* Error already set */
        }
        if (PSA_SUCCESS == funcres)
        {
            PsaPolicyMask_t PubKeyAssetPolicy;

            PubKeyAssetPolicy = (AssetPolicy & (~(EIP130_ASSET_POLICY_PRIVATEDATA |
                                                  EIP130_ASSET_POLICY_STANY))) |
                                EIP130_ASSET_POLICY_PUBLICDATA;

            funcres = psaInt_AssetAlloc(PubKeyAssetPolicy, PubKeySize,
                                        &LocalPubKeyAssetId);
        }
        else
        {
            /* Error already set */
        }
    }
    else
    {
        /* Error already set */
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Generate the public key Asset */
        /* Format service request */
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        Eip130Token_Command_Pk_Asset_Command(
            &CommandToken,
            (uint8_t)Method,
            (uint8_t)(PSA_ASYM_DATA_SIZE_WB(ModulusSizeInBits)),
            (uint8_t)(PSA_ASYM_DATA_SIZE_WB(ModulusSizeInBits)),
            0,
            PrvKeyAssetId,
            LocalDomainAssetId,
            LocalPubKeyAssetId,
            0, 0,
            (uintptr_t)&KeyDataBuffer[0], (uint16_t)PubKeySize);

        /* Exchange service request with the next driver level */
        status = HSMSAL_SubmitPhysicalToken(&CommandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&ResultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&ResultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    /* Public key data is now in KeyDataBuffer */
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
                }
            }
            else
            {
                funcres = PSA_ERROR_HARDWARE_FAILURE;
            }
        }
        else
        {
            funcres = PSA_ERROR_HARDWARE_FAILURE;
        }
    }
    else
    {
        /* Error already set */
    }

    if (PSA_SUCCESS == funcres)
    {
        if (componentFormat)
        {
            /* The component format that the HSM returns is expected. Now check if an asset or plaintext was requested. */
            if (PubKeyAssetId == NULL)
            {
                (void)memcpy(data, KeyDataBuffer, PubKeySize);
                *data_length = PubKeySize;
            }
            else
            {
                /* The public key is already loaded into LocalPubKeyAssetId. We will return this. */
                *PubKeyAssetId = LocalPubKeyAssetId;
            }
        }
        else
        {
            /* We can assume we are working with plaintext in this condition - componentFormat MUST be true for
             * an asset to be the output of this function.
             */
            PubKeySize = PSA_ASYM_DATA_SIZE_B2B(ModulusSizeInBits);

            /* Convert the public key to export format, as defined by PSA spec. For Weierstrass curves,
             * big-endian octet format should be used. For Montgomery curves, little-endian format should
             * be used.
             */
            if ((CurveFamily == EIP130DOMAIN_ECC_FAMILY_MONTGOMERY) ||
                (CurveFamily == EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS))
            {
                /* For Montgomery and Twisted Edwards curves, the data should be output in little-endian, so we should not reverse
                 * the HSM output data. Further, it is known that this CurveFamily has only one component and
                 * no octet byte prefix.
                 */
                (void)memcpy(data, &KeyDataBuffer[PSA_ASYM_DATA_VHEADER], PubKeySize);

                *data_length = PubKeySize;
            }
            else
            {
                if (octetBytePresent)
                {
                    data[0] = 0x04U;
                }
                /* Copy the first component back to the output, starting from word 1 of the sub-vector format the HSM outputs */
                psaInt_ReverseMemCpy(data + octetBytePresent, &KeyDataBuffer[PSA_ASYM_DATA_VHEADER],
                                        PubKeySize);
                /* If two components, copy the second one to the output */
                if (RealPubKeySize != PubKeySize)
                {
                    psaInt_ReverseMemCpy(&data[PubKeySize + octetBytePresent],
                                            &KeyDataBuffer[(2U * PSA_ASYM_DATA_VHEADER) +
                                                            PSA_ASYM_DATA_SIZE_B2WB(ModulusSizeInBits)],
                                            PubKeySize);
                    *data_length = (2U * PubKeySize) + octetBytePresent;
                }
                else
                {
                    *data_length = PubKeySize + octetBytePresent;
                }
            }
        }

        if (!bypassASN1DER)
        {
            Asn1Der_BigNumber PubKey;
            uint8_t * pActualBegin = NULL;

            (void)memcpy(KeyDataBuffer, data + 1, RealPubKeySize);

            PubKey.pData = KeyDataBuffer;
            PubKey.Length = RealPubKeySize;
            PubKey.Sign = 0U;
            funcres = PSAInt_AsymWrite_EC_PubKey(&PubKey,
                                                 CurveFamily,
                                                 ModulusSizeInBits,
                                                 fECDH,
                                                 data_size, data,
                                                 &pActualBegin);
            if (PSA_SUCCESS == funcres)
            {
                if (pActualBegin != data)
                {
                    /* Move DER public key to the begin of the data buffer */
                    size_t Length = data_size - (size_t)(pActualBegin - data);
                    uint8_t * pPtr = data;

                    *data_length = Length;
                    for (; Length != 0U; Length--)
                    {
                        *pPtr = *pActualBegin;
                        pPtr++;
                        pActualBegin++;
                    }
                }
                else
                {
                    /* Shall not directly happen due to the provided buffer */
                    *data_length = data_size;
                }
            }
            else
            {
                /* Error already set */
            }
        }
        else
        {
            /* MISRA - Intentionally empty */
        }
    }
    else
    {
        /* Error already set */
    }

    /* Release the used Assets if applicable. If the public key asset is loaded but the caller
     * requested for it, then we should not free it.
     */
    if ((PSA_ASSETID_INVALID != LocalPubKeyAssetId) &&
        (PubKeyAssetId == NULL))
    {
        removalResult = psaInt_AssetFree(LocalPubKeyAssetId);
        if (removalResult != PSA_SUCCESS)
        {
            funcres = removalResult;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != LocalDomainAssetId)
    {
        removalResult = psaInt_AssetFree(LocalDomainAssetId);
        if (removalResult != PSA_SUCCESS)
        {
            funcres = removalResult;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_GetFreeKeyEntry
 *
 * Searches for an empty key entry and returns the array index.
 * Note: The key entry is allocated for use.
 */
static psa_status_t
local_GetFreeKeyEntry(uint32_t * index, psa_key_persistence_t persistence)
{
    psa_status_t funcres = PSA_SUCCESS;
    uint32_t key_index;
    uint32_t max_index;
    psa_key_context_t * tempEntry;
    psa_key_persistence_t entryPersistence;
    psa_key_usage_t entryUsage;
    uint32_t persistentOverwriteIndex;

    /* The last MBEDTLS_KEY_VOLATILE_COUNT indices of the static array are reserved for volatile
     * keys. The middle MBEDTLS_KEY_ASSET_STORE_COUNT indices are for asset store keys. The rest of
     * the entries in the array are for persistent keys only.
     */
    if (PSA_KEY_PERSISTENCE_VOLATILE == persistence)
    {
        /* Start at the end of the asset store key region */
        key_index = MBEDTLS_MAX_KEY_BUFF_ENTRIES - MBEDTLS_KEY_VOLATILE_COUNT;
        /* Volatile keys occupy the final segment of the array */
        max_index = MBEDTLS_MAX_KEY_BUFF_ENTRIES;
    }
    else if (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == persistence)
    {
        /* Start at the end of the persistent key region */
        key_index = MBEDTLS_KEY_PERSISTENT_COUNT;
        /* End before the start of the volatile key region */
        max_index = MBEDTLS_MAX_KEY_BUFF_ENTRIES - MBEDTLS_KEY_VOLATILE_COUNT;
    }
    else
    {
        /* PSA_KEY_PERSISTENCE_DEFAULT == persistence
         * Start at beginning of array for MBEDTLS_KEY_PERSISTENT_COUNT keys.
         */
        key_index = 0U;
        /* End before the start of the asset store key region */
        max_index = MBEDTLS_KEY_PERSISTENT_COUNT;
    }

    /* In the case that there are no available persistent key entries, this will
     * store the first persistent entry that can be overwritten, since it can always be
     * retrieved again from persistent storage next time it is needed.
     */
     persistentOverwriteIndex = max_index;

    for (; key_index < max_index; key_index++)
    {
        tempEntry = &gl_PSA_Key[key_index];
        entryPersistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(tempEntry->attributes.MBEDTLS_PRIVATE(lifetime));
        entryUsage = tempEntry->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);

        if (0U == tempEntry->fAllocated)
        {
            break;
        }
        else if ((persistence == PSA_KEY_PERSISTENCE_DEFAULT) &&
                 (entryPersistence == PSA_KEY_PERSISTENCE_DEFAULT) &&
                 ((entryUsage & PSA_KEY_USAGE_CACHE) != PSA_KEY_USAGE_CACHE) &&
                 (persistentOverwriteIndex == max_index))
        {
            /* Persistent keys can overwrite other persistent keys stored in KeyStore RAM
             * if necessary, since the metadata can be recovered from ITS with an ITS search.
             * However, only keys without PSA_KEY_USAGE_CACHE will be replaced, to give some priority
             * to those persistent keys which are specifically designated to be cached. The caching of
             * keys without this usage is an implementation choice for efficiency.
             */
            persistentOverwriteIndex = key_index;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    if (key_index < max_index)
    {
        gl_PSA_Key[key_index].fAllocated = 255U;
        *index = key_index;
    }
    else if (persistence == PSA_KEY_PERSISTENCE_DEFAULT)
    {
        /* This API should always be able to return an acquired entry for persistent keys */
        if (persistentOverwriteIndex == max_index)
        {
            /* If all persistent keys had the cache flag, then we will choose to replace the first one.
             * This is necessary to avoid a condition where all persistent slots are occupied by
             * keys with the cache flag, thus preventing any replacement in the cache.
             */
            persistentOverwriteIndex = 0U;
        }
        else
        {
            /* A persistent key without the cache flag has already been marked for replacement */
        }

        /* persistentOverwriteIndex is only valid when the provided persistence
         * is DEFAULT, which is desired. The persistent key being replaced
         * in KeyStore RAM has its key material cached here, and
         * it should be removed.
         */
        if (NULL != gl_PSA_Key[persistentOverwriteIndex].key)
        {
            /* Remove the volatile entry */
            psaInt_mbedtls_free(gl_PSA_Key[persistentOverwriteIndex].key);
        }

        if (NULL != gl_PSA_Key[persistentOverwriteIndex].key2)
        {
            /* Remove the volatile entry */
            psaInt_mbedtls_free(gl_PSA_Key[persistentOverwriteIndex].key2);
        }

        /* Make sure that the key entry is cleared */
        (void)memset(&gl_PSA_Key[persistentOverwriteIndex], 0, sizeof(psa_key_context_t));

        gl_PSA_Key[persistentOverwriteIndex].fAllocated = 255U;
        *index = persistentOverwriteIndex;
    }
    else
    {
        /* Since the function result is NOT success, the caller must not
         * expect an output value in 'index'
         */
        funcres = PSA_ERROR_INSUFFICIENT_STORAGE;
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_RemoveKey
 *
 * Removes/Releases the specified key entry from the cache and
 * from the persistent key store.
 */
static psa_status_t
local_RemoveKey(psa_key_context_t * pKey)
{
    psa_status_t funcres = PSA_SUCCESS;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;
    mbedtls_svc_key_id_t key = pKey->attributes.MBEDTLS_PRIVATE(id);
    psa_key_persistence_t key_persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(pKey->attributes.MBEDTLS_PRIVATE(lifetime));
    psa_storage_uid_t UId;
    psa_key_id_t id;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    id = key.MBEDTLS_PRIVATE(key_id);
#else
    id = key;
#endif

    if (psa_is_preprovisioned_key_id(id))
    {
        funcres = PSA_ERROR_NOT_SUPPORTED;
    }
    else
    {
        if (PSA_ASSETID_INVALID != pKey->key_assetId)
        {
            /* Remove the HSM Asset Store entry */
            removalResult = psaInt_AssetFree(pKey->key_assetId);
            if (removalResult != PSA_SUCCESS)
            {
                funcres = removalResult;
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        if (PSA_ASSETID_INVALID != pKey->key_assetId2)
        {
            /* Remove the HSM Asset Store entry */
            removalResult = psaInt_AssetFree(pKey->key_assetId2);
            if (removalResult != PSA_SUCCESS)
            {
                funcres = removalResult;
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        if (NULL != pKey->key)
        {
            /* Remove the volatile entry */
            psaInt_mbedtls_free(pKey->key);
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        if (NULL != pKey->key2)
        {
            /* Remove the volatile entry */
            psaInt_mbedtls_free(pKey->key2);
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        /* Keys with volatile or HSM Asset Store persistence need not perform any releases from KeyStore NVM. Also,
         * verify the key was successfully stored before attempting to remove it.
         */
        if ((key_persistence == PSA_KEY_PERSISTENCE_DEFAULT) &&
            (psa_is_key_present_in_storage(key)))
        {
            /* Remove the persistent entry */
            UId = psa_its_identifier_of_slot(key);
            funcres = psaInt_KeyStore_PersistentRelease(UId);
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        if (PSA_SUCCESS == funcres)
        {
            /* Make sure that the key entry is cleared, if all other removal was successful.
             * If not, the cache entry should remain intact to attempt removal again.
             */
            (void)memset(pKey, 0, sizeof(psa_key_context_t));
        }
        else
        {
            /* Error already set */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_LoadImport
 *
 * Imports the Asset (Key) Blob (wrapped form) of the key into VaultIP/HSM.
 */
static psa_status_t
local_LoadImport(const PsaAssetId_t TargetAssetId,
                 const uint8_t * const KeyBlob_p,
                 const size_t KeyBlobSize_p)
{
    PsaAssetId_t KekAssetId;
    psa_status_t funcres;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;

    /* Retrieve the asset ID for the KEK, which is responsible for
     * encrypting the key blob. If funcres is PSA_SUCCESS, the
     * KekAssetId is guaranteed to be valid.
     */
    funcres = psaInt_AssetGetKeyBlobKEK(&KekAssetId);
    if ((funcres == PSA_SUCCESS) &&
        (KekAssetId != PSA_ASSETID_INVALID))
    {
        funcres = psaInt_AssetLoadImport(TargetAssetId, KekAssetId,
                                         KeyBlob_p, KeyBlobSize_p);
        removalResult = psaInt_AssetFree(KekAssetId);
        if (removalResult != PSA_SUCCESS)
        {
            funcres = removalResult;
        }
    }
    else
    {
        /* Error already set */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_LoadPlaintextExport
 *
 * Creates, loads and frees an Asset with the provided plaintext data and
 * returns the Asset (Key) Blob of the data (wrapped form).
 */
static psa_status_t
local_LoadPlaintextExport(PsaPolicyMask_t TargetAssetPolicy,
                          const uint8_t * data,
                          size_t data_length,
                          uint8_t * const KeyBlob_p,
                          size_t * const KeyBlobSize_p)
{
    PsaAssetId_t TargetAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t KekAssetId    = PSA_ASSETID_INVALID;
    psa_status_t funcres;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;

    /* Retrieve the asset ID for the KEK, which is responsible for
     * encrypting the key blob. If funcres is PSA_SUCCESS, the
     * KekAssetId is guaranteed to be valid.
     */
    funcres = psaInt_AssetGetKeyBlobKEK(&KekAssetId);
    if ((funcres == PSA_SUCCESS) &&
        (KekAssetId != PSA_ASSETID_INVALID))
    {
        funcres = psaInt_AssetAlloc(TargetAssetPolicy, data_length,
                                    &TargetAssetId);
        if (PSA_SUCCESS == funcres)
        {
            funcres = psaInt_AssetLoadPlaintextExport(TargetAssetId,
                                                      data, data_length,
                                                      KekAssetId,
                                                      KeyBlob_p, KeyBlobSize_p);
            removalResult = psaInt_AssetFree(TargetAssetId);
            if (removalResult != PSA_SUCCESS)
            {
                funcres = removalResult;
            }
        }
        else
        {
            /* Error already set */
        }

        removalResult = psaInt_AssetFree(KekAssetId);
        if (removalResult != PSA_SUCCESS)
        {
            funcres = removalResult;
        }
    }
    else
    {
        /* Error already set */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_LoadRandomExport
 *
 * Creates, loads and frees an Asset with random data and returns the Asset
 * (Key) Blob of the generate data (wrapped form).
 */
static psa_status_t
local_LoadRandomExport(PsaPolicyMask_t TargetAssetPolicy,
                       size_t data_length,
                       uint8_t * const KeyBlob_p,
                       size_t * const KeyBlobSize_p)
{
    PsaAssetId_t TargetAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t KekAssetId    = PSA_ASSETID_INVALID;
    psa_status_t funcres;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;

    /* Retrieve the asset ID for the KEK, which is responsible for
     * encrypting the key blob. If funcres is PSA_SUCCESS, the
     * KekAssetId is guaranteed to be valid.
     */
    funcres = psaInt_AssetGetKeyBlobKEK(&KekAssetId);
    if ((funcres == PSA_SUCCESS) &&
        (KekAssetId != PSA_ASSETID_INVALID))
    {
        funcres = psaInt_AssetAlloc(TargetAssetPolicy, data_length,
                                    &TargetAssetId);
        if (PSA_SUCCESS == funcres)
        {
            funcres = psaInt_AssetLoadRandomExport(TargetAssetId,
                                                   KekAssetId,
                                                   KeyBlob_p, KeyBlobSize_p);
            removalResult = psaInt_AssetFree(TargetAssetId);
            if (removalResult != PSA_SUCCESS)
            {
                funcres = removalResult;
            }
        }
        else
        {
            /* Error already set */
        }

        removalResult = psaInt_AssetFree(KekAssetId);
        if (removalResult != PSA_SUCCESS)
        {
            funcres = removalResult;
        }
    }
    else
    {
        /* Error already set */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_KeyMgmtGetKey
 *
 * Returns the key entry for the specified KeyId, when it is allocated.
 */
psa_status_t
psaInt_KeyMgmtGetKey(mbedtls_svc_key_id_t key,
                     psa_key_context_t ** ppKeyEntry)
{
    psa_status_t funcres = PSA_SUCCESS;
    psa_key_context_t * pEntry;
    uint32_t entryIdx;
    psa_key_id_t id;
    bool iakIsPreProvisioned = false;
    uint8_t CurveFamily = 0U;
    uint8_t fECDH = 0U;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    id = key.MBEDTLS_PRIVATE(key_id);
#else
    id = key;
#endif
    /* The last 'MBEDTLS_KEY_VOLATILE_COUNT' indices of the global array are for volatile keys. Their associated
     * key IDs range from PSA_KEY_ID_VOLATILE_MIN to PSA_KEY_ID_VOLATILE_MAX, but that range is only valid if
     * MBEDTLS_KEY_VOLATILE_COUNT is greater than 0. For example, if MBEDTLS_KEY_VOLATILE_COUNT is 1, then
     * PSA_KEY_ID_VOLATILE_MIN will be the only possible volatile key ID stored in the array.
     */
    if ((psa_key_id_is_volatile(id)) && ((id - PSA_KEY_ID_VOLATILE_MIN) <= (MBEDTLS_KEY_VOLATILE_COUNT - 1)))
    {
        /* The index of a volatile key in the global array is always tied to the key ID. The first available
         * slot in the array for volatile keys will always be the volatile key with PSA_KEY_ID_VOLATILE_MIN.
         */
        entryIdx = (id - PSA_KEY_ID_VOLATILE_MIN + MBEDTLS_KEY_PERSISTENT_COUNT + MBEDTLS_KEY_ASSET_STORE_COUNT);

        /* The condition check above guarantees that this index exists within gl_PSA_Key */
        pEntry = &gl_PSA_Key[entryIdx];

#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
        if (id != pEntry->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id))
#else
        if (id != pEntry->attributes.MBEDTLS_PRIVATE(id))
#endif
        {
            funcres = PSA_ERROR_INVALID_HANDLE;
        }
        else if (0U == pEntry->fAllocated)
        {
            funcres = PSA_ERROR_INVALID_HANDLE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else if ((psa_is_valid_key_id(id, 0)) || (id == PSA_KEY_ID_IAK))
    {
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
        if (id == PSA_KEY_ID_IAK)
        {
            /* We must first check if the IAK is preprovisioned, if it is being requested.
             * If it is not preprovisioned, then we will attempt to retrieve it
             * from KeyStore cache space, as we would for any other persistent key.
             */
            funcres = KeyMgmt_getPreProvisionedKey(key, &pEntry);

            if (funcres == PSA_ERROR_INVALID_HANDLE)
            {
                /* If PSA_ERROR_INVALID_HANDLE, then the IAK does not exist as
                 * a preprovisioned key. Continue on to see if it was imported
                 * as a persistent key instead.
                 */
            }
            else
            {
                /* In this case, we have either successfully retrieved the IAK
                 * from the preprovisioned key space, or there was some other
                 * failure unrelated to the IAK not existing in that space.
                 * There is no need to check the KeyStore cache for the key in
                 * either of these cases.
                 */
                iakIsPreProvisioned = true;
            }
        }
#endif
        /* For CC35XX, the IAK does not yet exist & cannot be pre-provisioned.
         * This boolean will always be false from its initialization at the
         * top of the function.
         */
        if (!iakIsPreProvisioned)
        {
            /* Persistent keys and asset store keys share the same valid key ID ranges, so we must check the full array
             * besides the region containing only volatile keys.
             */
            for (entryIdx = 0U; entryIdx < (MBEDTLS_KEY_PERSISTENT_COUNT + MBEDTLS_KEY_ASSET_STORE_COUNT); entryIdx++)
            {
                pEntry = &gl_PSA_Key[entryIdx];
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                if (id == pEntry->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id))
#else
                if (id == pEntry->attributes.MBEDTLS_PRIVATE(id))
#endif
                {
                    /* Key ID was found in the cache */
                    funcres = PSA_SUCCESS;
                    break;
                }
            }

            if (entryIdx >= (MBEDTLS_KEY_PERSISTENT_COUNT + MBEDTLS_KEY_ASSET_STORE_COUNT))
            {
                /* If we've not found the given key ID in the array, check if that ID is associated with a key
                 * in persistent storage.
                 */
                if (psa_is_key_present_in_storage(key))
                {
                    /* Get free entry pointer for pEntry, that will evict an entry of another persistent key
                     * if necessary.
                     */
                    funcres = local_GetFreeKeyEntry(&entryIdx, PSA_KEY_PERSISTENCE_DEFAULT);

                    if (funcres == PSA_SUCCESS)
                    {
                        pEntry = &gl_PSA_Key[entryIdx];

                        /* Load persistent key material along with its attributes directly into the global array entry */
                        funcres = psa_load_persistent_key_into_slot(key, pEntry);

                        if (funcres == PSA_SUCCESS)
                        {
                            /* When key blobs are stored to NVM, the key_size is stored as the length of the wrapped key material. This is
                             * necessary to store and load the correct data lengths to ITS. However, when we read from ITS, we want key_size
                             * to reflect the size of the key material without the wrapping. This is because the Asset Create token expects
                             * the length of the actual asset key material, ignoring extra bytes from a key blob wrapping.
                             */
                            psa_key_location_t key_location = PSA_KEY_LIFETIME_GET_LOCATION(pEntry->attributes.MBEDTLS_PRIVATE(lifetime));
                            pEntry->key_size = (key_location == PSA_KEY_LOCATION_LOCAL_STORAGE) ? pEntry->key_size : PSA_KEYMATERIAL_SIZE(pEntry->key_size);

                            /* Key attributes are stored to NVM before the key bits attribute gets set internally. We must re-calculate it here, assuming
                             * that the key bits weren't set by the caller of the key creation API. This also only needs to be done for asymmetric keys,
                             * since they are the only keys where the bits attribute is relevant to operations.
                             */
                            if ((pEntry->attributes.MBEDTLS_PRIVATE(bits) == 0) && (PSA_KEY_TYPE_IS_ASYMMETRIC(pEntry->attributes.MBEDTLS_PRIVATE(type))))
                            {
                                fECDH = PSA_ALG_IS_ECDH(pEntry->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)) ? 1U : 0U;
                                CurveFamily = local_CurveFamilyFromKeyType(pEntry->attributes.MBEDTLS_PRIVATE(type), fECDH);
                                if ((CurveFamily == EIP130DOMAIN_ECC_FAMILY_MONTGOMERY) ||
                                    (CurveFamily == EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS))
                                {
                                    /* Curve25519/Ed25519 are the only montgomery curves we support. */
                                    pEntry->attributes.MBEDTLS_PRIVATE(bits) = 255U;
                                }
                                else
                                {
                                    /* For Weierstrass curves, consider the HW format sizes for both public keys & private keys.
                                    * Note that there is a collision between PSA_ASYM_DATA_SIZE_VWB_MACRO(521) &
                                    * 2*PSA_ASYM_DATA_SIZE_VWB_MACRO(256), so we must separate the switch statements for public
                                    * and private keys.
                                    */
                                    if (PSA_KEY_TYPE_IS_KEY_PAIR(pEntry->attributes.MBEDTLS_PRIVATE(type)))
                                    {
                                        switch (pEntry->key_size)
                                        {
                                            case PSA_ASYM_DATA_SIZE_VWB_MACRO(192):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 192U;
                                                break;
                                            case PSA_ASYM_DATA_SIZE_VWB_MACRO(224):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 224U;
                                                break;
                                            case PSA_ASYM_DATA_SIZE_VWB_MACRO(256):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 256U;
                                                break;
                                            case PSA_ASYM_DATA_SIZE_VWB_MACRO(384):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 384U;
                                                break;
                                            case PSA_ASYM_DATA_SIZE_VWB_MACRO(512):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 512U;
                                                break;
                                            case PSA_ASYM_DATA_SIZE_VWB_MACRO(521):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 521U;
                                                break;
                                            default:
                                                funcres = PSA_ERROR_CORRUPTION_DETECTED;
                                                break;
                                        }
                                    }
                                    else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(pEntry->attributes.MBEDTLS_PRIVATE(type)))
                                    {
                                        switch (pEntry->key_size)
                                        {
                                            case (2U * PSA_ASYM_DATA_SIZE_VWB_MACRO(192)):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 192U;
                                                break;
                                            case (2U * PSA_ASYM_DATA_SIZE_VWB_MACRO(224)):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 224U;
                                                break;
                                            case (2U * PSA_ASYM_DATA_SIZE_VWB_MACRO(256)):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 256U;
                                                break;
                                            case (2U * PSA_ASYM_DATA_SIZE_VWB_MACRO(384)):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 384U;
                                                break;
                                            case (2U * PSA_ASYM_DATA_SIZE_VWB_MACRO(512)):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 512U;
                                                break;
                                            case (2U * PSA_ASYM_DATA_SIZE_VWB_MACRO(521)):
                                                pEntry->attributes.MBEDTLS_PRIVATE(bits) = 521U;
                                                break;
                                            default:
                                                funcres = PSA_ERROR_CORRUPTION_DETECTED;
                                                break;
                                        }
                                    }
                                    else
                                    {
                                        /* Safeguard: Should never happen, already checked earlier */
                                        funcres = PSA_ERROR_NOT_SUPPORTED;
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_HANDLE;
                }
            }
            else if (0U == pEntry->fAllocated)
            {
                funcres = PSA_ERROR_INVALID_HANDLE;
            }
            else
            {
                /* MISRA - Intentionally empty */
            }
        }
    }
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
    else if (psa_is_preprovisioned_key_id(id))
    {
        /* If the key doesn't exist in KeyStore RAM nor in KeyStore Flash, then check
         * if it is a pre-provisioned key. This function may return PSA_SUCCESS if the key
         * is found and valid, PSA_ERROR_INVALID_ARGUMENT if the key is found and invalid,
         * or PSA_ERROR_INVALID_HANDLE if it is not found.
         */
        funcres = KeyMgmt_getPreProvisionedKey(key, &pEntry);
    }
#endif
    else
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }

    /* Return pointer to the entry where the key metadata (and potentially
     * wrapped/unwrapped key material) is stored
     */
    if (funcres == PSA_SUCCESS)
    {
        *ppKeyEntry = pEntry;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * psaInt_KeyMgmtLoadKey
 *
 * Loads the key either in plaintext directly to the caller, or into Asset Store
 * to provide the caller an Asset ID.
 */
psa_status_t
psaInt_KeyMgmtLoadKey(psa_key_context_t * pKey,
                      uint32_t * const pAssetId,
                      psa_algorithm_t target_alg,
                      psa_key_usage_t target_usage,
                      uint8_t * const pData,
                      size_t const DataSize,
                      uint32_t * const pActualDataSize)
{
    psa_status_t funcres = PSA_SUCCESS;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;
    psa_key_usage_t key_usage;
    psa_key_type_t key_type;
    psa_key_location_t key_location;
    /* Used to point to either pKey->key or pKey->key2, dependent on which usage (encryption or
     * decryption) is being requested for the symmetric key as an asset. Otherwise defaults
     * to pKey->key.
     */
    uint8_t *key;
    /* Reassigned in the case that there are two asset IDs involved with a symmetric key. */
    PsaAssetId_t * pKeyAssetId;
    PsaPolicyMask_t AssetPolicy;
    bool pubKeyGenerated = false;
    uint8_t fECDH = 0U;
    uint8_t CurveFamily = 0U;
    size_t CurveBits = 0U;
    size_t PublicKeyLength = 0U;
    psa_key_id_t id;

    /* Note: when pKey is given it is expected to be correct.
     * If the caller requests an Asset ID, pData, DataSize, and pActualDataSize should be NULL/0.
     * If the caller requests plaintext, pAssetId should be NULL.
     */
    if ((NULL != pKey) &&
        (((NULL != pAssetId) && (NULL == pData) && (0U == DataSize) && (NULL == pActualDataSize)) ||
         ((NULL == pAssetId) && (NULL != pData) && (0U != DataSize) && (NULL != pActualDataSize))))
    {
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
        id = pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id);
#else
        id = pKey->attributes.MBEDTLS_PRIVATE(id);
#endif
        /* If a pre-provisioned key is requested for a crypto operation (not an export),
         * we have to convert to HW format and produce an asset policy for the key, because
         * that has not yet been done.
         */
        if ((psa_is_preprovisioned_key_id(id)) &&
            (target_usage != PSA_KEY_USAGE_EXPORT))
        {
            if (PSA_KEY_TYPE_IS_UNSTRUCTURED(pKey->attributes.MBEDTLS_PRIVATE(type)))
            {
                funcres = local_SymKeyType(&pKey->attributes, pKey->key_size, &pKey->AssetPolicy);

                key = pKey->key;
            }
            else if (PSA_KEY_TYPE_IS_ASYMMETRIC(pKey->attributes.MBEDTLS_PRIVATE(type)))
            {
                size_t KeyDataBufferSize = sizeof(KeyDataBuffer);
                funcres = local_AsymKeyType(bypassASN1DER, &pKey->attributes,
                                            false, pKey->key, pKey->key_size,
                                            KeyDataBuffer, &KeyDataBufferSize,
                                            &pKey->attributes.MBEDTLS_PRIVATE(bits), &pKey->AssetPolicy);

                key = KeyDataBuffer;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            key = pKey->key;
        }

        if (funcres != PSA_SUCCESS)
        {
            goto exit;
        }

        pKeyAssetId = &pKey->key_assetId;
        AssetPolicy = pKey->AssetPolicy;

        /* This is our cached marker that a key is symmetric, and we may have its data split to support
         * two separate assets
         */
        key_usage = pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
        key_type = pKey->attributes.MBEDTLS_PRIVATE(type);
        key_location = PSA_KEY_LIFETIME_GET_LOCATION(pKey->attributes.MBEDTLS_PRIVATE(lifetime));

        if ((PSA_KEY_TYPE_IS_SYMMETRIC(key_type)) &&
            (PSA_KEY_USAGE_ENCRYPT == (key_usage & PSA_KEY_USAGE_ENCRYPT)) &&
            (PSA_KEY_USAGE_DECRYPT == (key_usage & PSA_KEY_USAGE_DECRYPT)) &&
            (0 == (key_usage & PSA_KEY_USAGE_COPROCESSOR)) &&
            (pAssetId != NULL))
        {
            /* The stored key is symmetric for both encrypt & decrypt, and not a coprocessor key. We
             * must check the target usage to know which asset to return. It is expected that the
             * target_usage meets one of the following two conditions, if an asset is requested.
             * Note that the only differences between the two keys can be the key blob content,
             * asset ID, and asset policies.
             */
            if (PSA_KEY_USAGE_ENCRYPT == (target_usage & PSA_KEY_USAGE_ENCRYPT))
            {
                /* key, pKeyAssetId, and AssetPolicy can be left as they are */
            }
            else if (PSA_KEY_USAGE_DECRYPT == (target_usage & PSA_KEY_USAGE_DECRYPT))
            {
                /* Encrypt is the default - switch to decrypt pointers/policy in this case */
                pKeyAssetId = &pKey->key_assetId2;
                AssetPolicy = (pKey->AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);
                key = pKey->key2;
            }
            else
            {
                /* If the target_usage is not specified to one of the above two cases for symmetric
                 * keys, then only plaintext keys can be loaded back. The asset policy affects
                 * the asset's content, so we cannot provide an asset without this information.
                 */
                pKeyAssetId = NULL;
            }
        }
        else if (((PSA_KEY_USAGE_VERIFY_MESSAGE == (target_usage & PSA_KEY_USAGE_VERIFY_MESSAGE)) ||
                  (PSA_KEY_USAGE_VERIFY_HASH == (target_usage & PSA_KEY_USAGE_VERIFY_HASH))) &&
                 (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)))
        {
            /* The largest public key that can be requested back is a component form NISTP-521 public key.
             * The 521-bit curve length must be converted to a word boundary, multiplied by number
             * of bytes per word, and added by 4 bytes for the additional header word per component.
             * Since there are two components in the public key, multiply the whole prior value by 2.
             */
            PsaAssetId_t PrivateAssetId;

            if (*pKeyAssetId != PSA_ASSETID_INVALID)
            {
                /* The private key (key_pair) is already in asset store */
                PrivateAssetId = *pKeyAssetId;
            }
            else
            {
                funcres = psaInt_AssetAlloc(AssetPolicy, pKey->key_size, &PrivateAssetId);

                if (PSA_SUCCESS == funcres)
                {
                    if (PSA_KEY_LOCATION_LOCAL_STORAGE == key_location)
                    {
                        /* Key data is available as plaintext */
                        funcres = psaInt_AssetLoadPlaintext(PrivateAssetId,
                                                            key,
                                                            pKey->key_size);
                    }
                    else if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location)
                    {
                        /* Key data is available as Asset blob (wrapped form) */
                        funcres = local_LoadImport(PrivateAssetId,
                                                   key,
                                                   PSA_KEYBLOB_SIZE(pKey->key_size));
                    }
                    else
                    {
                        funcres = PSA_ERROR_CORRUPTION_DETECTED;
                    }
                }
                else
                {
                    /* Error already set */
                }
            }

            if (PSA_SUCCESS == funcres)
            {
                /* Now we have a private key asset to generate a public key from */

                if (PSA_ALG_IS_KEY_AGREEMENT(pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
                {
                    fECDH = 255U;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }

                CurveFamily = local_CurveFamilyFromKeyType(pKey->attributes.MBEDTLS_PRIVATE(type), fECDH);
                CurveBits = pKey->attributes.MBEDTLS_PRIVATE(bits);

                if (NULL != pAssetId)
                {
                    /* If public key is requested as an asset, return it directly to the output parameter */
                    funcres = local_AsymKeyGenPub(PrivateAssetId, pAssetId, pKey->AssetPolicy, true,
                                                  CurveFamily, CurveBits,
                                                  fECDH, NULL, 0, NULL);
                }
                else
                {
                    /* If public key is requested in plaintext (component format, since a crypto driver would be the caller) */
                    funcres = local_AsymKeyGenPub(PrivateAssetId, NULL, pKey->AssetPolicy, true,
                                                  CurveFamily, CurveBits,
                                                  fECDH, KeyDataBuffer, sizeof(KeyDataBuffer), &PublicKeyLength);

                    if (PSA_SUCCESS == funcres)
                    {
                        if (DataSize >= PublicKeyLength)
                        {
                            (void)memcpy(pData, KeyDataBuffer, PublicKeyLength);
                            *pActualDataSize = PublicKeyLength;
                        }
                        else
                        {
                            funcres = PSA_ERROR_BUFFER_TOO_SMALL;
                        }
                    }
                    else
                    {
                        /* Error already set */
                    }
                }

                /* Since all work to return a public key to the caller has been done above, we must skip the execution paths below */
                pubKeyGenerated = true;
            }
            else
            {
                /* Error already set */
            }
        }
        else if ((PSA_KEY_USAGE_EXPORT == (target_usage & PSA_KEY_USAGE_EXPORT)) &&
                 (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) &&
                 (pData != NULL))
        {
            /* If the public key is being requested as an export, it must be converted from HSM HW format to the format
             * specified by the PSA spec for points of each curve family.
             */
            if (PSA_ALG_IS_KEY_AGREEMENT(pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
            {
                fECDH = 255U;
            }
            else
            {
                /* MISRA - Intentially empty */
            }

            CurveFamily = local_CurveFamilyFromKeyType(pKey->attributes.MBEDTLS_PRIVATE(type), fECDH);
            CurveBits = pKey->attributes.MBEDTLS_PRIVATE(bits);

            if ((CurveFamily == EIP130DOMAIN_ECC_FAMILY_MONTGOMERY) ||
                (CurveFamily == EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS))
            {
                PublicKeyLength = PSA_ASYM_DATA_SIZE_B2B(CurveBits);
            }
            else
            {
                PublicKeyLength = 1 + (2 * PSA_ASYM_DATA_SIZE_B2B(CurveBits));
            }

            if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location)
            {
                /* TODO: It should be possible to export a public key that is stored in asset or wrapped form, using
                 * a Public Data Read token. The token will read it into PublicDataBuffer, before using
                 * local_AsymPointOutputFromHW() to convert it from the HW format.
                 */
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else if (NULL == key)
            {
                funcres = PSA_ERROR_CORRUPTION_DETECTED;
            }
            else if (DataSize < PublicKeyLength)
            {
                funcres = PSA_ERROR_BUFFER_TOO_SMALL;
            }
            else if (psa_is_preprovisioned_key_id(id))
            {
                /* Pre-provisioned keys are stored in import/export format as they remain in flash. Therefore,
                 * we do not need to convert the format back from the HW format when exporting.
                 */
                (void)memcpy(pData, key, pKey->key_size);

                *pActualDataSize = (uint32_t)pKey->key_size;
            }
            else
            {
                local_AsymPointOutputFromHW(pData, CurveBits, CurveFamily, key);
                *pActualDataSize = PublicKeyLength;
            }

            pubKeyGenerated = true;
        }
        else
        {
            /* MISRA - Intentionally empty */
        }

        if (pubKeyGenerated == true)
        {
            /* Nothing to do - if public key was generated or loaded successfully, it has already been copied to the requested asset
             * or buffer. If there was an error generating or loading it, we should skip the below functionality to retrieve data from
             * the key slot.
             */
        }
        else if (pKeyAssetId == NULL)
        {
            /* This condition occurs if the user requests an asset ID for a symmetric key,
             * but does not provide a valid target usage to choose either the encryption
             * asset or the decryption asset.
             */
            funcres = PSA_ERROR_INVALID_ARGUMENT;
            *pAssetId = PSA_ASSETID_INVALID;
        }
        else if (*pKeyAssetId != PSA_ASSETID_INVALID)
        {
            /* Key is already in the Asset Store */
            if (NULL != pAssetId)
            {
                *pAssetId = *pKeyAssetId;
            }
            else
            {
                funcres = PSA_ERROR_NOT_PERMITTED;

                /* Set default */
                (void)memset(pData, 0, DataSize);
                *pActualDataSize = 0U;
            }
        }
        else
        {
            /* Key is in the PSA key storage (either in RAM or NVM) */

            if (NULL != pAssetId)
            {
                *pAssetId = PSA_ASSETID_INVALID;

                /* The size allocated should be that of the plaintext key material, not including any
                 * extra bytes from a key blob wrapping. pKey->key_size always stores this length.
                 */
                funcres = psaInt_AssetAlloc(AssetPolicy, pKey->key_size, pKeyAssetId);

                if (PSA_SUCCESS == funcres)
                {
                    if (NULL != key)
                    {
                        /* Key is in RAM. This should be the case for persistent and volatile keys, as
                         * psaInt_KeyMgmtGetKey (and its locking variant) will load the persistent key into
                         * the slot from NVM
                         */
                        if (PSA_KEY_LOCATION_LOCAL_STORAGE == key_location)
                        {
                            /* Key data is available as plaintext */
                            funcres = psaInt_AssetLoadPlaintext(*pKeyAssetId,
                                                                key,
                                                                pKey->key_size);
                        }
                        else if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location)
                        {
                            /* Key data is available as Asset blob (wrapped form) */
                            funcres = local_LoadImport(*pKeyAssetId,
                                                       key,
                                                       PSA_KEYBLOB_SIZE(pKey->key_size));
                        }
                        else
                        {
                            /* Safeguard: Should not happen, blocked by earlier tests */
                            funcres = PSA_ERROR_CORRUPTION_DETECTED;
                        }
                    }
                    else
                    {
                        /* Safeguard: Should not happen, blocked by earlier tests */
                        funcres = PSA_ERROR_CORRUPTION_DETECTED;
                    }

                    if (funcres != PSA_SUCCESS)
                    {
                        /* Cleanup the Asset */
                        removalResult = psaInt_AssetFree(*pKeyAssetId);
                        if (removalResult != PSA_SUCCESS)
                        {
                            funcres = removalResult;
                        }
                        else
                        {
                            *pKeyAssetId = PSA_ASSETID_INVALID;
                        }
                    }
                    else
                    {
                        /* Return the asset ID to reference the requested key */
                        *pAssetId = *pKeyAssetId;
                    }
                }
                else
                {
                    /* The most likely error is that the Asset Store is full.
                     * Another possibility is that the Asset Policy/size is wrong
                     */
                    funcres = PSA_ERROR_HARDWARE_FAILURE;

                    /* Make sure AssetId is invalid */
                    *pKeyAssetId = PSA_ASSETID_INVALID;
                }
            }
            else
            {
                /* Set default */
                (void)memset(pData, 0, DataSize);
                *pActualDataSize = 0U;

                if (NULL != key)
                {
                    /* Key is in RAM */
                    if (PSA_KEY_LOCATION_LOCAL_STORAGE == key_location)
                    {
                        /* Key data is available as plaintext */
                        if (DataSize >= pKey->key_size)
                        {
                            (void)memcpy(pData, key, pKey->key_size);
                            *pActualDataSize = (uint32_t)pKey->key_size;
                        }
                        else
                        {
                            funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                        }
                    }
                    else if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location)
                    {
                        /* Key data is available as Asset blob (wrapped form) */
                        funcres = PSA_ERROR_NOT_PERMITTED;
                    }
                    else
                    {
                        /* Safeguard: Should not happen, blocked by earlier tests */
                        funcres = PSA_ERROR_CORRUPTION_DETECTED;
                    }
                }
                else
                {
                    /* Safeguard: Should not happen, blocked by earlier tests */
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
                }
            }
        }
    }
    else
    {
        /* Safeguard: Should not happen, blocked by psaInt_KeyMgmtGetKey() */
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }

exit:
    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_KeyMgmtReleaseKey
 *
 * Releases/Frees the key from VaultIP/HSM.
 */
psa_status_t
psaInt_KeyMgmtReleaseKey(psa_key_context_t * pKey)
{
    psa_status_t funcres;
    psa_key_persistence_t persistence;

    if (NULL != pKey)
    {
        if (pKey->key_assetId != PSA_ASSETID_INVALID)
        {
            funcres = psaInt_AssetFree(pKey->key_assetId);
            pKey->key_assetId = PSA_ASSETID_INVALID;

            persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(pKey->attributes.MBEDTLS_PRIVATE(lifetime));
            if (persistence == PSA_KEY_PERSISTENCE_HSM_ASSET_STORE)
            {
                /* If the persistence is PSA_KEY_PERSISTENCE_HSM_ASSET_STORE, then there is no use for the key entry once
                 * the key has been removed from the asset store.
                 */
                (void)memset(pKey, 0, sizeof(psa_key_context_t));
            }
            else
            {
                /* Nothing to do. If the key has a different persistence, then there is still valuable data stored in cache. */
            }
        }
        else
        {
            /* Key is already not in the Asset Store */
            funcres = PSA_SUCCESS;
        }
    }
    else
    {
        /* Invalid key reference */
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_KeyMgmtReadECPubKey
 *
 * Reads/parses a public key (by default in plain format) and returns the public key
 * data in VaultIP/HSM HW format.
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
                           size_t * pOutputDataLength)
{
    Asn1Der_BigNumber PubKey;
    psa_status_t funcres;
    uint8_t items;
    uint8_t octetBytePresent = 0;

    if (PersistentItemSize == 0)
    {
        funcres = PSAInt_AsymParse_EC_PubKey(pData, DataLen,
                                             pCurveFamily, pCurveBits,
                                             &PubKey, pfECDH);
    }
    else
    {
        funcres = PSA_SUCCESS;

        /* If the input key is not DER-formatted, then we cannot extract Curve Bit
         * information from it. We'll just set the local pCurveBits value to the value
         * that was passed into (or inferred from) the key attributes.
         */
        *pCurveBits = ExpCurveBits;

        /* Per the PSA spec, public keys for SECP or BRAINPOOL family must be octet strings
         * with the 0x04 initial byte.
         */
        switch (ExpCurveFamily)
        {
            case PSA_ECC_FAMILY_SECP_R1:
                items = 0x2U;
                octetBytePresent = 1;
                if (pData[0] != 0x04U)
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                break;
            case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
                items = 0x12U;
                octetBytePresent = 1;
                if (pData[0] != 0x04U)
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                break;
            case PSA_ECC_FAMILY_MONTGOMERY:
                items = 0x01U;
                break;
            default:
                funcres = PSA_ERROR_INVALID_ARGUMENT;
                break;
        }
    }

    if (PSA_SUCCESS == funcres)
    {
        if (ExpCurveBits != *pCurveBits)
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if (PersistentItemSize == 0)
        {
            switch (*pCurveFamily)
            {
            case EIP130DOMAIN_ECC_FAMILY_NIST_P:
                if (PSA_ECC_FAMILY_SECP_R1 != ExpCurveFamily)
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    /* Note that the least significant 4 bits here contain a 2,
                     * indicating SubVectCount of 2, since a public key will require
                     * two components in the HSM vector structure.
                     */
                    items = 0x2U;
                }
                break;
            case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
                if (PSA_ECC_FAMILY_BRAINPOOL_P_R1 != ExpCurveFamily)
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    /* Specify two components, and a DomainID of 1 */
                    items = 0x12U;
                }
                break;
            case EIP130DOMAIN_ECC_FAMILY_MONTGOMERY:
                if (PSA_ECC_FAMILY_MONTGOMERY != ExpCurveFamily)
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    /* Specify a single component, and a DomainID of 0 */
                    items = 0x01U;
                }
                break;
            case EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS:
                if (PSA_ECC_FAMILY_TWISTED_EDWARDS != ExpCurveFamily)
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else
                {
                    items = 0x11U;
                }
                break;
            default:
                funcres = PSA_ERROR_INVALID_ARGUMENT;
                break;
            }
        }
    }
    else
    {
        /* Error already set */
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Convert to VaultIP HW format */
        if ((NULL == pOutputData) ||
            (NULL == pOutputDataLength))
        {
            /* Safeguard: Should not happen */
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if (*pOutputDataLength < ((items & 0x0FU) * PSA_ASYM_DATA_SIZE_VWB(*pCurveBits)))
        {
            funcres = PSA_ERROR_BUFFER_TOO_SMALL;
        }
        else
        {
            *pOutputDataLength = (items & 0x0FU) * PSA_ASYM_DATA_SIZE_VWB(*pCurveBits);
            if (0x01U == (items & 0x0FU))
            {
                if (PersistentItemSize == 0)
                {
                    local_AsymBigIntToHW(PubKey.pData, *pCurveBits, 0, items,
                                         pOutputData);
                }
                else
                {
                    local_AsymBigIntToHW(pData + octetBytePresent, *pCurveBits, 0, items,
                                         pOutputData);
                }
            }
            else
            {
                if (PersistentItemSize == 0)
                {
                    local_AsymBigIntPointToHW(PubKey.pData, *pCurveBits, items,
                                              pOutputData);
                }
                else
                {
                    local_AsymBigIntPointToHW(pData + octetBytePresent, *pCurveBits, items,
                                              pOutputData);
                }
            }
        }
    }
    else
    {
        /* Error already set */
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * psaInt_KeyMgmtDeriveKey
 *
 * Derive a Key from provided KDK and save resulting asset in a slot.
 */
psa_status_t
psaInt_KeyMgmtDeriveKey(const psa_key_attributes_t * attributes,
                        KeyMgmt_psa_key_derivation_operation_t * operation,
                        mbedtls_svc_key_id_t * key)
{
    psa_status_t funcres;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;
    psa_key_persistence_t key_persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(attributes->MBEDTLS_PRIVATE(lifetime));
    PsaPolicyMask_t AssetPolicy = (PsaPolicyMask_t)0U;
    PsaPolicyMask_t AssetPolicy2 = (PsaPolicyMask_t)0U;
    size_t key_size = (attributes->MBEDTLS_PRIVATE(bits) + 7) / 8;
    /* Refers to the output length, L, that is part of the key's context. Calculated from the capacity
     * for KDKs that the HSM doesn't handle the context for.
     */
    uint32_t outputLength = 0U;
    uint32_t key_index = 0U;
    size_t inputDataSize = operation->labelSize + operation->contextSize;
    psa_key_bits_t modulus_size = 0U;
    psa_key_context_t *pKey = NULL;
    bool useCounterMode = true;
    bool isBidirectionalKey = false;
    uint32_t derivationKeyAssetID = PSA_ASSETID_INVALID;
    uint32_t derivedKeyAssetID = PSA_ASSETID_INVALID;
    /* Used in case we are deriving a symmetric key */
    uint32_t derivedKeyAssetID2 = PSA_ASSETID_INVALID;
    psa_key_type_t key_usage = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
    psa_key_id_t derivationKeyID;
    psa_key_id_t derivedKeyID;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    derivationKeyID = operation->inputKey.MBEDTLS_PRIVATE(key_id);
    derivedKeyID = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id);
#else
    derivationKeyID = operation->inputKey;
    derivedKeyID = attributes->MBEDTLS_PRIVATE(id);
#endif

    /* Populate the asset policy of the key asset we are going to derive */
    if (PSA_KEY_TYPE_IS_UNSTRUCTURED(attributes->MBEDTLS_PRIVATE(type)))
    {
        /* This handles DERIVE key types (valid for HMAC KDKs) as well as AES key types (valid for CMAC KDKs). */
        funcres = local_SymKeyType(attributes, key_size, &AssetPolicy);
    }
    else if (PSA_KEY_TYPE_IS_ASYMMETRIC(attributes->MBEDTLS_PRIVATE(type)))
    {
        funcres = local_AsymKeyType(bypassASN1DER, attributes,
                                    true, NULL, key_size, NULL, 0,
                                    &modulus_size, &AssetPolicy);
    }
    else
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check if a key with the given ID already exists in a slot or persistent storage */
    if ((PSA_SUCCESS == funcres) && (key_persistence != PSA_KEY_PERSISTENCE_VOLATILE))
    {
        /* Volatile keys are guaranteed to not have duplicates since we choose the value based
         * on the open volatile slot. All we have to check is that there IS an open slot remaining.
         * However, volatile derived keys are not currently possible so this check should have no
         * effect.
         */

        if (psaInt_KeyMgmtGetKey(attributes->MBEDTLS_PRIVATE(id), &pKey) == PSA_SUCCESS)
        {
            funcres = PSA_ERROR_ALREADY_EXISTS;
        }
        else
        {
            /* Nothing to do. psaInt_KeyMgmtGetKey exhaustively checks for pre-existing keys. */
        }
    }

    /* Find free slot for the derived key. If we can do that, retrieve the KDK in asset form. */
    if (PSA_SUCCESS == funcres)
    {
        funcres = local_GetFreeKeyEntry(&key_index, key_persistence);
        if (PSA_SUCCESS == funcres)
        {
            /* Now that we have a slot to put the derived key in, we must retrieve the derivation key as an asset to perform
             * derivation from it. We will first use pKey to load the derivation key (unless it's the HUK). If that's
             * successful, we'll point pKey to the free slot (at the key_index we just found).
             */
            if (derivationKeyID == PSA_KEY_ID_HSM_HUK)
            {
                funcres = psaInt_AssetSearch(PSA_ASSETNUMBER_HUK, &derivationKeyAssetID, NULL);
                useCounterMode = false;

                /* Override the error code to notify the application that it needs to provision the HUK */
                if (funcres == PSA_ERROR_DOES_NOT_EXIST)
                {
                    funcres = PSA_ERROR_HUK_NOT_PROVISIONED;
                }
            }
            else
            {
                funcres = psaInt_KeyMgmtGetKey(operation->inputKey, &pKey);
                if (PSA_SUCCESS == funcres)
                {
                    funcres = psaInt_KeyMgmtLoadKey(pKey, &derivationKeyAssetID, 0, 0, NULL, 0, NULL);
                }
            }
        }
    }

    if ((PSA_KEY_USAGE_ENCRYPT == (key_usage & PSA_KEY_USAGE_ENCRYPT)) &&
        (PSA_KEY_USAGE_DECRYPT == (key_usage & PSA_KEY_USAGE_DECRYPT)) &&
        (PSA_KEY_TYPE_IS_SYMMETRIC(attributes->MBEDTLS_PRIVATE(type))))
    {
        /* Place marker to note that two key assets will have to be created,
         * if the key is to be used as an HSM asset. In this case, the assetPolicy populated
         * by local_SymKeyType will reflect only the encryption usage. We will populate
         * a second asset policy to preserve the user-specified decryption usage.
         */
        isBidirectionalKey = true;
    }

    /* Allocate an asset for the derived key, then perform the derivation. */
    if (PSA_SUCCESS == funcres)
    {
        funcres = psaInt_AssetAlloc(AssetPolicy, key_size, &derivedKeyAssetID);

        if (PSA_SUCCESS == funcres)
        {
            /* TODO: See HSM_DDK-80 and update this condition if 0 inputDataSize is to be supported */
            if ((derivationKeyID != PSA_KEY_ID_HSM_HUK) &&
                (derivationKeyID != PSA_KEY_ID_HSM_TKDK))
            {
                /* For normal key derivations, the HSM won't append the derivation length
                 * automatically. We have to add it here. Assumption is that the length
                 * fits within 4 bytes - which is what the PSA spec states the length
                 * should be stored in.
                 */
                outputLength = operation->capacity * 8;

                (void)memcpy(operation->fixedInputData, &outputLength, 4);

                inputDataSize += 4;
            }

            /* Perform the derivation. useCounterMode defines whether or not
             * the derivation uses counter mode, since derivations from the HUK
             * are always in feedback mode. Derivations from the TKDK or any other
             * KDK are in counter mode.
             */
            funcres = psaInt_AssetLoadDerive(derivedKeyAssetID,
                                             derivationKeyAssetID,
                                             operation->fixedInputData,
                                             inputDataSize,
                                             useCounterMode, false, NULL,
                                             0, NULL, 0, 0);
        }

        if ((PSA_SUCCESS == funcres) &&
            (isBidirectionalKey))
        {
            /* XOR the asset policy of the first (encryption) key we've stored to get
             * the policy for the decryption key.
             */
            AssetPolicy2 = (AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

            funcres = psaInt_AssetAlloc(AssetPolicy2, key_size, &derivedKeyAssetID2);
        }

        if ((PSA_SUCCESS == funcres) &&
            (isBidirectionalKey))
        {
            /* Perform the 2nd derivation. useCounterMode defines whether or not
             * the derivation uses counter mode, since derivations from the HUK
             * are always in feedback mode. Derivations from the TKDK or any other
             * KDK are in counter mode.
             */
            funcres = psaInt_AssetLoadDerive(derivedKeyAssetID2,
                                             derivationKeyAssetID,
                                             operation->fixedInputData,
                                             inputDataSize,
                                             useCounterMode, false, NULL,
                                             0, NULL, 0, 0);
        }
    }

    /* If we successfully performed the derivation, now populate the newly derived key slot */
    if (PSA_SUCCESS == funcres)
    {
        /* Reduce operation capacity by the number of bytes of key material derived. Though deriving
         * a symmetric key requires two derivations, both should produce the same material. So
         * capacity should still lessen by the key_size just once.
         */
        operation->capacity -= key_size;

        /* Point to the free key slot that we will place the newly derived key into */
        pKey = &gl_PSA_Key[key_index];

        /* Save derived key asset into slot */
        pKey->key_assetId = derivedKeyAssetID;
        pKey->key_assetId2 = derivedKeyAssetID2;

        /* Initialize remaining part of the key entry */
        pKey->attributes.MBEDTLS_PRIVATE(type) = attributes->MBEDTLS_PRIVATE(type);
        pKey->attributes.MBEDTLS_PRIVATE(bits) = attributes->MBEDTLS_PRIVATE(bits);
        pKey->attributes.MBEDTLS_PRIVATE(lifetime) = attributes->MBEDTLS_PRIVATE(lifetime);
        pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
        pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg) = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg);
        pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2) = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2);
        pKey->key_size = key_size;
        pKey->AssetPolicy = AssetPolicy;

        /* Set an automatic output key ID for the asset store key, if a particular ID wasn't requested. */
        if (derivedKeyID == PSA_KEY_ID_NULL)
        {
            /* Only persistent keys come before asset store keys in the key array.*/
            derivedKeyID = PSA_KEY_ID_ASSET_STORE_AUTO_MIN + (key_index - MBEDTLS_KEY_PERSISTENT_COUNT);
        }
        else
        {
            /* Nothing to do. Use the key ID provided. */
        }

#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
        /* A key ID initialized to PSA_KEY_ID_NULL also has a default owner value. So, we can use
         * the provided owner value in any case.
         */
        key->MBEDTLS_PRIVATE(owner) = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);
        pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner) = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);

        key->MBEDTLS_PRIVATE(key_id) = derivedKeyID;
        pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id) = derivedKeyID;
#else
        *key = derivedKeyID;
        pKey->attributes.MBEDTLS_PRIVATE(id) = derivedKeyID;
#endif
    }

    if (pKey != NULL)
    {
        if (PSA_SUCCESS != funcres)
        {
            if (PSA_ASSETID_INVALID != pKey->key_assetId)
            {
                /* Remove the HSM Asset Store entry */
                removalResult = psaInt_AssetFree(pKey->key_assetId);
                if (removalResult != PSA_SUCCESS)
                {
                    funcres = removalResult;
                }
            }
            else
            {
                /* MISRA - Intentially empty */
            }

            if (PSA_ASSETID_INVALID != pKey->key_assetId2)
            {
                /* Remove the HSM Asset Store entry */
                removalResult = psaInt_AssetFree(pKey->key_assetId2);
                if (removalResult != PSA_SUCCESS)
                {
                    funcres = removalResult;
                }
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * psa_import_key
 *
 * Create a Key and load the material to KeyStore RAM/NVM or Asset Store.
 */
psa_status_t
psa_import_key(const psa_key_attributes_t * attributes,
               const uint8_t * data,
               size_t data_length,
               mbedtls_svc_key_id_t * key)
{
    psa_key_context_t * pKey = NULL;
    PsaPolicyMask_t AssetPolicy = (PsaPolicyMask_t)0U;
    PsaPolicyMask_t AssetPolicy2;
    psa_status_t funcres = PSA_SUCCESS;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;
    psa_key_persistence_t key_persistence;
    psa_key_location_t key_location;
    psa_key_usage_t key_usage;
    psa_key_type_t key_type;
    psa_key_bits_t key_bits = 0U;
    size_t DataSize = 0U;
    size_t DataToSaveSize = 0U;
    const uint8_t * pDataToSave = NULL;
    /* Consider making this buffer global - investigate its usage in asymmetric keys */
    uint32_t key_index;
    psa_key_id_t attributesID;
    bool isBidirectionalKey = false;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    attributesID = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id);
#else
    attributesID = attributes->MBEDTLS_PRIVATE(id);
#endif

    if ((NULL == key) ||
        (NULL == attributes) ||
        (PSA_KEY_TYPE_NONE == attributes->MBEDTLS_PRIVATE(type)) ||
        (PSA_ALG_NONE == attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if ((0U != attributes->MBEDTLS_PRIVATE(bits)) &&
             (data_length != (size_t)PSA_BITS_TO_BYTES(attributes->MBEDTLS_PRIVATE(bits))) &&
             (data_length != ((2 * (size_t)PSA_BITS_TO_BYTES(attributes->MBEDTLS_PRIVATE(bits))) + 1)) &&
             (!PSA_KEY_TYPE_IS_RSA(attributes->MBEDTLS_PRIVATE(type))))
    {
        /* If the 'bits' field is set, it is expected to match either the private or public key length.
         * Since RSA is DER-encoded, we cannot perform this check.
         */
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        key_location = PSA_KEY_LIFETIME_GET_LOCATION(attributes->MBEDTLS_PRIVATE(lifetime));
        key_persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(attributes->MBEDTLS_PRIVATE(lifetime));
        key_usage = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
        key_type = attributes->MBEDTLS_PRIVATE(type);

        if (PSA_KEY_ID_NULL != attributesID)
        {
            if ((!psa_is_valid_key_id(attributesID, 0)) && (attributesID != PSA_KEY_ID_IAK))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else if ((PSA_KEY_PERSISTENCE_DEFAULT == key_persistence) ||
                     (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence))
            {
                if (PSA_SUCCESS == psaInt_KeyMgmtGetKey(attributesID, &pKey))
                {
                    /* A key with the requested ID already exists */
                    funcres = PSA_ERROR_ALREADY_EXISTS;
                }
                else
                {
                    /* Nothing to do. psaInt_KeyMgmtGetKey exhaustively checks for pre-existing keys. */
                }
            }
            else
            {
                /* When a key id is passed through the attributes struct, the key must be either
                 * persistent or meant to be stored in Asset Store.
                 */
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else if ((PSA_KEY_PERSISTENCE_VOLATILE == key_persistence) ||
                 (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence))
        {
            /* Only keys with these two persistences may be created without an input key ID */
        }
        else
        {
            /* A key ID must be provided for keys without volatile or asset store persistence */
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }

        if ((PSA_KEY_USAGE_ENCRYPT == (key_usage & PSA_KEY_USAGE_ENCRYPT)) &&
            (PSA_KEY_USAGE_DECRYPT == (key_usage & PSA_KEY_USAGE_DECRYPT)) &&
            (PSA_KEY_TYPE_IS_SYMMETRIC(key_type)) &&
            (0 == (key_usage & PSA_KEY_USAGE_COPROCESSOR)))
        {
            /* Place marker to note that two key blobs or assets will have to be created, if the key
             * is to be used as an HSM asset. In this case, the assetPolicy populated by
             * local_SymKeyType will reflect only the encryption usage. We will populate a second
             * asset policy to preserve the user-specified decryption usage. Coprocessor keys do not
             * require a second asset policy since they are always bidirectional.
             */
            isBidirectionalKey = true;
        }
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Check exceptions before normal cases */
        if ((PSA_KEY_TYPE_IS_RSA(attributes->MBEDTLS_PRIVATE(type))) ||
            (PSA_KEY_TYPE_IS_DH(attributes->MBEDTLS_PRIVATE(type))) ||
            (attributes->MBEDTLS_PRIVATE(type) == PSA_KEY_TYPE_CHACHA20))
        {
            /* RSA keys need to be stored in the DER format directly if used for
             * SW operations. When RSA is enabled via HW acceleration, this condition should be removed.
             * At that point, local_AsymKeyType will be needed to translate the RSA attributes
             * into an HSM Asset Policy. For DH keys, only SW is supported currently as well,
             * so we must skip the local_AsymKeyType call, even though they are not DER-encoded.
             */
            if (NULL == data)
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                pDataToSave = data;
                DataToSaveSize = data_length;
                if (PSA_KEY_TYPE_IS_DH(attributes->MBEDTLS_PRIVATE(type)))
                {
                    /* SW implementation for FFDH makes use of the attributes->bits value, even though
                     * it's not mandatory to import an FFDH key with that value set. So, set the
                     * key_bits here so that we can assign the key SLOT's attributes->bits value.
                     */
                    key_bits = PSA_BYTES_TO_BITS(data_length);
                }
            }
        }
        else if (PSA_KEY_TYPE_IS_UNSTRUCTURED(attributes->MBEDTLS_PRIVATE(type)))
        {
            /* New item */
            if (NULL == data)
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                pDataToSave = data;
                DataToSaveSize = data_length;
            }

            if (PSA_SUCCESS == funcres)
            {
                funcres = local_SymKeyType(attributes, DataToSaveSize, &AssetPolicy);

                /* For all symmetric key types we support, there is a simple relationship between
                 * the key bits & the data length provided to the import API. We set this here so
                 * that it gets stored in the key slot's attributes->bits field.
                 */
                key_bits = PSA_BYTES_TO_BITS(data_length);
            }
            else
            {
                /* Error already set */
            }
        }
        else if (PSA_KEY_TYPE_IS_ASYMMETRIC(attributes->MBEDTLS_PRIVATE(type)))
        {
            DataSize = sizeof(KeyDataBuffer);
            /* bypassASN1DER is true by default */
            funcres = local_AsymKeyType(bypassASN1DER, attributes,
                                        false, data, data_length,
                                        KeyDataBuffer, &DataSize,
                                        &key_bits, &AssetPolicy);
            pDataToSave = KeyDataBuffer;
            DataToSaveSize = DataSize;
        }
        else
        {
            /* No vendor-defined key functionality */
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        if (PSA_SUCCESS == funcres)
        {
            /* If key_persistence is PSA_KEY_PERSISTENCE_DEFAULT, then another persistent key
             * may be replaced in the cache if storage is limited.
             */
            funcres = local_GetFreeKeyEntry(&key_index, key_persistence);
            if (PSA_SUCCESS == funcres)
            {
                psa_key_id_t keyID;
                pKey = &gl_PSA_Key[key_index];

                /* Volatile key IDs start at PSA_KEY_ID_VOLATILE_MIN and increment based on the
                 * first available index for volatile keys in the global array. The key ID is always
                 * tied to the index for volatile keys.
                 */
                if (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence)
                {
                    keyID = PSA_KEY_ID_VOLATILE_MIN + (key_index - (MBEDTLS_MAX_KEY_BUFF_ENTRIES - MBEDTLS_KEY_VOLATILE_COUNT));
                }
                else if ((PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence) &&
                         (attributesID == PSA_KEY_ID_NULL))
                {
                    /* Set an automatic key ID for an Asset Store key. Only persistent keys come
                     * before asset store keys in the key array.
                     */
                    keyID = PSA_KEY_ID_ASSET_STORE_AUTO_MIN + (key_index - MBEDTLS_KEY_PERSISTENT_COUNT);
                }
                else
                {
                    keyID = attributesID;
                }

                if (PSA_KEY_LOCATION_LOCAL_STORAGE == key_location)
                {
                    if (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence)
                    {
                        pKey->key = psaInt_mbedtls_calloc(1, DataToSaveSize);
                        if (NULL == pKey->key)
                        {
                            funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                        }
                        else
                        {
                            (void)memcpy(pKey->key, pDataToSave, DataToSaveSize);
                        }
                    }
                    else if (PSA_KEY_PERSISTENCE_DEFAULT == key_persistence)
                    {
                        /* New persistent item */
                        funcres = psa_save_persistent_key(pKey,
                                                          attributes,
                                                          &AssetPolicy,
                                                          pDataToSave,
                                                          NULL,
                                                          DataToSaveSize);
                    }
                    else
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                }
                else if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location)
                {
                    if ((PSA_ALG_IS_HMAC(attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg))) &&
                        ((DataToSaveSize % 4) != 0))
                    {
                        /* Copy HMAC key data into a buffer, so that we can pad 0s after. HMAC keys can have padded 0s
                         * up until the block length of the given hash algorithm. To bypass HSM limitation with key blob
                         * output size, we only need to round up to the nearest 4-byte multiple of key size. For every
                         * key length that the driver accepts, the next nearest 4-byte multiple cannot go above the block
                         * length for the specified hash algorithm, so this padding is valid.
                         */
                        (void)memcpy(KeyDataBuffer, pDataToSave, DataToSaveSize);

                        /* Pad with 0s. The actual key length may not use ALL of these padded 0s. */
                        (void)memset(KeyDataBuffer+DataToSaveSize, 0, sizeof(KeyDataBuffer) - DataToSaveSize);

                        pDataToSave = KeyDataBuffer;

                        /* For HMAC, with variable length keys, we must round up the key length to the nearest multiple
                         * of 4. Exporting a key blob fails when its length is not a 4-byte multiple.
                         */
                        DataToSaveSize = ((DataToSaveSize + 3) / 4) * 4;
                    }

                    DataSize = PSA_KEYBLOB_SIZE(DataToSaveSize);
                    if (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence)
                    {
                        pKey->key = psaInt_mbedtls_calloc(1, DataSize);
                        if (NULL == pKey->key)
                        {
                            funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                        }
                        else
                        {
                            funcres = local_LoadPlaintextExport(AssetPolicy,
                                                                pDataToSave,
                                                                DataToSaveSize,
                                                                pKey->key,
                                                                &DataSize);
                        }

                        if ((PSA_SUCCESS == funcres) && isBidirectionalKey)
                        {
                            pKey->key2 = psaInt_mbedtls_calloc(1, DataSize);

                            if (NULL == pKey->key2)
                            {
                                funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                            }
                            else
                            {
                                /* XOR the asset policy of the first (encryption) key we've stored to get
                                 * the policy for the decryption key.
                                 */
                                AssetPolicy2 = (AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

                                funcres = local_LoadPlaintextExport(AssetPolicy2,
                                                                    pDataToSave,
                                                                    DataToSaveSize,
                                                                    pKey->key2,
                                                                    &DataSize);
                            }
                        }
                    }
                    else if (PSA_KEY_PERSISTENCE_DEFAULT == key_persistence)
                    {
                        /* New persistent item */
                        if (DataSize > sizeof(KeyDataBuffer))
                        {
                            funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                        }
                        else
                        {
                            /* Receive key blob into KeyDataBuffer */
                            funcres = local_LoadPlaintextExport(AssetPolicy,
                                                                pDataToSave,
                                                                DataToSaveSize,
                                                                KeyDataBuffer,
                                                                &DataSize);
                        }

                        if ((PSA_SUCCESS == funcres) && isBidirectionalKey)
                        {
                            /* XOR the asset policy of the first (encryption) key we've stored to get
                             * the policy for the decryption key.
                             */
                            AssetPolicy2 = (AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

                            /* Receive second key blob into KeyDataBuffer2 */
                            funcres = local_LoadPlaintextExport(AssetPolicy2,
                                                                pDataToSave,
                                                                DataToSaveSize,
                                                                KeyDataBuffer2,
                                                                &DataSize);

                            /* If we've received both key blobs successfully, save them both to NVM */
                            if (PSA_SUCCESS == funcres)
                            {
                                funcres = psa_save_persistent_key(pKey,
                                                                  attributes,
                                                                  &AssetPolicy,
                                                                  KeyDataBuffer,
                                                                  KeyDataBuffer2,
                                                                  DataSize);
                            }
                        }
                        else if (PSA_SUCCESS == funcres)
                        {
                            /* isBidirectionalKey is false - so we only have one key blob to store */
                            funcres = psa_save_persistent_key(pKey,
                                                              attributes,
                                                              &AssetPolicy,
                                                              KeyDataBuffer,
                                                              NULL,
                                                              DataSize);
                        }
                        else
                        {
                            /* Error already set */
                        }
                    }
                    else if (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence)
                    {
                        funcres = psaInt_AssetAlloc(AssetPolicy, DataToSaveSize,
                                                    &pKey->key_assetId);
                        if (PSA_SUCCESS == funcres)
                        {
                            funcres = psaInt_AssetLoadPlaintext(pKey->key_assetId,
                                                                pDataToSave,
                                                                DataToSaveSize);
                        }
                        else
                        {
                            /* Error already set */
                        }

                        if ((PSA_SUCCESS == funcres) && isBidirectionalKey)
                        {
                            /* XOR the asset policy of the first (encryption) key we've stored to get
                             * the policy for the decryption key.
                             */
                            AssetPolicy2 = (AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

                            funcres = psaInt_AssetAlloc(AssetPolicy2, DataToSaveSize,
                                                        &pKey->key_assetId2);
                        }
                        else
                        {
                            /* Error or success already set */
                        }

                        if ((PSA_SUCCESS == funcres) && isBidirectionalKey)
                        {
                            funcres = psaInt_AssetLoadPlaintext(pKey->key_assetId2,
                                                                pDataToSave,
                                                                DataToSaveSize);
                        }
                    }
                    else
                    {
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }

                if (PSA_SUCCESS != funcres)
                {
                    /* Do necessary cleanup */
                    removalResult = local_RemoveKey(pKey);
                    if (removalResult != PSA_SUCCESS)
                    {
                        funcres = removalResult;
                    }
                }
                else
                {
                    /* Initialize remaining part of the key entry */
                    pKey->attributes.MBEDTLS_PRIVATE(type) = attributes->MBEDTLS_PRIVATE(type);
                    pKey->attributes.MBEDTLS_PRIVATE(bits) = (attributes->MBEDTLS_PRIVATE(bits) == 0) ? key_bits : attributes->MBEDTLS_PRIVATE(bits);
                    pKey->attributes.MBEDTLS_PRIVATE(lifetime) = attributes->MBEDTLS_PRIVATE(lifetime);
                    pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
                    pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg) = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg);
                    pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2) = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2);
                    pKey->key_size = DataToSaveSize;
                    pKey->AssetPolicy = AssetPolicy;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                    key->MBEDTLS_PRIVATE(key_id) = keyID;
                    pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id) = keyID;

                    /* A key ID initialized to PSA_KEY_ID_NULL also has a default owner value. We can just keep that. */
                    key->MBEDTLS_PRIVATE(owner) = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);
                    pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner) = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);
#else
                    *key = (mbedtls_svc_key_id_t)keyID;
                    pKey->attributes.MBEDTLS_PRIVATE(id) = (mbedtls_svc_key_id_t)keyID;
#endif
                }
            }
            else
            {
                /* Error already set */
            }
        }
        else
        {
            /* Error already set */
        }
    }
    else
    {
        /* Error already set */
    }

    if ((PSA_SUCCESS != funcres) && (key != NULL))
    {
        /* Make sure the returned key is invalid */
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
        key->MBEDTLS_PRIVATE(key_id) = PSA_KEY_ID_NULL;
#else
        *key = (mbedtls_svc_key_id_t)PSA_KEY_ID_NULL;
#endif
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_generate_key
 *
 * Generate random key using TRNG Token, then load the data to KeyStore RAM/NVM or Asset Store.
 */
psa_status_t
psa_generate_key(const psa_key_attributes_t * attributes,
                 mbedtls_svc_key_id_t * key)
{
    psa_status_t funcres = PSA_SUCCESS;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;
    psa_key_persistence_t key_persistence;
    psa_key_location_t key_location;
    psa_key_usage_t key_usage;
    psa_key_type_t key_type;
    psa_key_context_t * pKey = NULL;
    PsaPolicyMask_t AssetPolicy = (PsaPolicyMask_t)0;
    PsaPolicyMask_t AssetPolicy2;
    size_t ModulusSize = 0U;
    size_t KeySize = 0U;
    uint8_t CurveFamily = 0U;
    /* Size of largest symmetric key - used to retrieve random plaintext */
    uint8_t SymmetricKeyDataBuffer[32];
    uint32_t key_index;
    psa_key_id_t keyID = PSA_KEY_ID_NULL;
    psa_key_id_t attributesID;
    bool isBidirectionalKey = false;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    attributesID = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id);
#else
    attributesID = attributes->MBEDTLS_PRIVATE(id);
#endif

    if ((NULL == key) ||
        (NULL == attributes) ||
        (PSA_KEY_TYPE_NONE == attributes->MBEDTLS_PRIVATE(type)) ||
        (0U == attributes->MBEDTLS_PRIVATE(bits)) ||
        (PSA_ALG_NONE == attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        if (PSA_KEY_TYPE_IS_UNSTRUCTURED(attributes->MBEDTLS_PRIVATE(type)))
        {
            /* Set the actual key size */
            KeySize = (size_t)PSA_BITS_TO_BYTES(attributes->MBEDTLS_PRIVATE(bits));

            funcres = local_SymKeyType(attributes, KeySize, &AssetPolicy);
        }
        else if (PSA_KEY_TYPE_IS_ASYMMETRIC(attributes->MBEDTLS_PRIVATE(type)))
        {
            if (PSA_KEY_TYPE_IS_RSA(attributes->MBEDTLS_PRIVATE(type)))
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            else
            {
                uint8_t fECDH;

                funcres = local_AsymKeyGenType(attributes, &CurveFamily,
                                               &ModulusSize, &fECDH,
                                               &AssetPolicy);

                /* Set the actual key size */
                KeySize = PSA_ASYM_DATA_SIZE_VWB(ModulusSize);
            }
        }
        else
        {
            /* No vendor-defined key functionality */
            funcres = PSA_ERROR_NOT_SUPPORTED;
        }

        key_persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(attributes->MBEDTLS_PRIVATE(lifetime));
        key_usage = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
        key_type = attributes->MBEDTLS_PRIVATE(type);

        /* Validate the key ID that has been passed in where necessary. Don't overwrite an
         * error set beforehand.
         */
        if (PSA_SUCCESS == funcres)
        {
            if (PSA_KEY_ID_NULL != attributesID)
            {
                if (!psa_is_valid_key_id(attributesID, 0))
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                else if ((PSA_KEY_PERSISTENCE_DEFAULT == key_persistence) ||
                         (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence))
                {
                    if (PSA_SUCCESS == psaInt_KeyMgmtGetKey(attributesID, &pKey))
                    {
                        /* A key with the requested ID already exists */
                        funcres = PSA_ERROR_ALREADY_EXISTS;
                    }
                    else
                    {
                        /* If the input ID is not null and not a duplicate, we can save the Key ID that
                         * we'll assign to the persistent/asset store key. Volatile Key ID will have to
                         * be set later based on the open key entry found.
                         */
                        keyID = attributesID;
                    }
                }
                else
                {
                    /* When a key id is passed through the attributes struct, the key must be either
                     * persistent or meant to be stored in Asset Store.
                     */
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
            }
            else if ((PSA_KEY_PERSISTENCE_VOLATILE == key_persistence) ||
                     (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence))
            {
                /* Only keys with these two persistences may be created without an input key ID */
            }
            else
            {
                /* A key ID must be provided for keys without volatile or asset store persistence */
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }

            if ((PSA_KEY_USAGE_ENCRYPT == (key_usage & PSA_KEY_USAGE_ENCRYPT)) &&
                (PSA_KEY_USAGE_DECRYPT == (key_usage & PSA_KEY_USAGE_DECRYPT)) &&
                (PSA_KEY_TYPE_IS_SYMMETRIC(key_type)))
            {
                /* Place marker to note that two key blobs or assets will have to be created,
                 * if the key is to be used as an HSM asset. In this case, the assetPolicy populated
                 * by local_SymKeyType will reflect only the encryption usage. We will populate
                 * a second asset policy to preserve the user-specified decryption usage.
                 */
                isBidirectionalKey = true;
            }
        }
        else
        {
            /* Error already set */
        }

        if (PSA_SUCCESS == funcres)
        {
            if (0U == KeySize)
            {
                /* Safeguard: Should not happen but safety first */
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
        else
        {
            /* Error already set */
        }

        if (PSA_SUCCESS == funcres)
        {
            key_location = PSA_KEY_LIFETIME_GET_LOCATION(attributes->MBEDTLS_PRIVATE(lifetime));
            if (PSA_KEY_LOCATION_LOCAL_STORAGE == key_location)
            {
                /* Key will be in plaintext form in the PSA key store */
                if (PSA_KEY_TYPE_IS_ASYMMETRIC(attributes->MBEDTLS_PRIVATE(type)))
                {
                    /* Asymmetric crypto
                     * => A private key is never available in the plaintext
                     */
                    funcres = PSA_ERROR_NOT_SUPPORTED;
                }
                else if ((PSA_KEY_PERSISTENCE_VOLATILE == key_persistence) ||
                         (PSA_KEY_PERSISTENCE_DEFAULT == key_persistence))
                {
                    /* For persistent keys, we have already verified that the key ID is not a duplicate
                     * with psaInt_KeyMgmtGetKey. No need to check again here - just mark the key
                     * as nonexistent so that we can generate a new one.
                     */
                    funcres = PSA_ERROR_DOES_NOT_EXIST;
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }

                if (PSA_ERROR_DOES_NOT_EXIST == funcres)
                {
                    /* Generate a random key */
                    if (sizeof(KeyDataBuffer) < KeySize)
                    {
                        funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                    }
                    else
                    {
                        funcres = psa_generate_random(KeyDataBuffer, KeySize);
                    }

                    if (PSA_SUCCESS == funcres)
                    {
                        /* If key_persistence is PSA_KEY_PERSISTENCE_DEFAULT, then another persistent key
                         * may be replaced in the cache if storage is limited.
                         */
                        funcres = local_GetFreeKeyEntry(&key_index, key_persistence);
                    }
                    else
                    {
                        /* Error already set */
                    }
                    if (PSA_SUCCESS == funcres)
                    {
                        pKey = &gl_PSA_Key[key_index];
                        if (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence)
                        {
                            keyID = PSA_KEY_ID_VOLATILE_MIN + (key_index - (MBEDTLS_MAX_KEY_BUFF_ENTRIES - MBEDTLS_KEY_VOLATILE_COUNT));
                            /* Store in volatile storage */
                            pKey->key = psaInt_mbedtls_calloc(1, KeySize);
                            if (NULL == pKey->key)
                            {
                                funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                            }
                            else
                            {
                                (void)memcpy(pKey->key, KeyDataBuffer, KeySize);
                            }
                        }
                        else
                        {
                            /* Store in persistent storage */
                            funcres = psa_save_persistent_key(pKey,
                                                              attributes,
                                                              &AssetPolicy,
                                                              KeyDataBuffer,
                                                              NULL,
                                                              KeySize);
                        }
                    }
                    else
                    {
                        /* Error already set */
                    }
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
            else if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location)
            {
                /* Key will be in wrapped form (Asset Blob) form in the PSA key store */
                size_t KeyBlobSize = PSA_KEYBLOB_SIZE(KeySize);

                if ((PSA_KEY_PERSISTENCE_DEFAULT == key_persistence) ||
                    (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence) ||
                    (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence))
                {
                    /* For persistent keys, we have already verified that the key ID is not a duplicate
                     * with psaInt_KeyMgmtGetKey. No need to check again here - just mark the key
                     * as nonexistent so that we can generate a new one.
                     */
                    funcres = PSA_ERROR_DOES_NOT_EXIST;
                }
                else
                {
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }

                if (PSA_ERROR_DOES_NOT_EXIST == funcres)
                {
                    if (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence)
                    {
                        funcres = local_GetFreeKeyEntry(&key_index, key_persistence);
                        if (PSA_SUCCESS == funcres)
                        {
                            pKey = &gl_PSA_Key[key_index];
                            if (PSA_KEY_ID_NULL == attributesID)
                            {
                                keyID = PSA_KEY_ID_ASSET_STORE_AUTO_MIN + (key_index - MBEDTLS_KEY_PERSISTENT_COUNT);
                            }
                            else
                            {
                                /* Nothing to do. keyID was already set to attributesID above. */
                            }

                            if (PSA_KEY_TYPE_IS_ASYMMETRIC(attributes->MBEDTLS_PRIVATE(type)))
                            {
                                /* Generate ECDH/ECDSA/Curve25519/EdDSA key pair */
                                funcres = local_AsymKeyGenPrv(AssetPolicy,
                                                              CurveFamily,
                                                              ModulusSize,
                                                              &pKey->key_assetId,
                                                              NULL, NULL);
                            }
                            else if (isBidirectionalKey)
                            {
                                /* We cannot directly generate a random asset for a key meant for
                                 * encryption and decryption - the internal key material would be
                                 * different for each in that case. Instead, we'll generate the key
                                 * material directly and import it twice, with different asset policies.
                                 */
                                if (sizeof(KeyDataBuffer) < KeySize)
                                {
                                    funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                                }
                                else
                                {
                                    funcres = psa_generate_random(KeyDataBuffer, KeySize);
                                }

                                if (PSA_SUCCESS == funcres)
                                {
                                    funcres = psaInt_AssetAlloc(AssetPolicy, KeySize,
                                                                &pKey->key_assetId);
                                }
                                else
                                {
                                    /* Error already set */
                                }

                                if (PSA_SUCCESS == funcres)
                                {
                                    funcres = psaInt_AssetLoadPlaintext(pKey->key_assetId,
                                                                        KeyDataBuffer,
                                                                        KeySize);

                                    if (PSA_SUCCESS != funcres)
                                    {
                                        removalResult = psaInt_AssetFree(pKey->key_assetId);

                                        if (removalResult != PSA_SUCCESS)
                                        {
                                            funcres = removalResult;
                                        }
                                        else
                                        {
                                            pKey->key_assetId = PSA_ASSETID_INVALID;
                                        }
                                    }
                                }
                                else
                                {
                                    /* Error already set */
                                }

                                if (PSA_SUCCESS == funcres)
                                {
                                    AssetPolicy2 = (AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

                                    funcres = psaInt_AssetAlloc(AssetPolicy2, KeySize,
                                                                &pKey->key_assetId2);
                                }
                                else
                                {
                                    /* Error already set */
                                }

                                if (PSA_SUCCESS == funcres)
                                {
                                    funcres = psaInt_AssetLoadPlaintext(pKey->key_assetId2,
                                                                        KeyDataBuffer,
                                                                        KeySize);

                                    if (PSA_SUCCESS != funcres)
                                    {
                                        removalResult = psaInt_AssetFree(pKey->key_assetId2);

                                        if (removalResult != PSA_SUCCESS)
                                        {
                                            funcres = removalResult;
                                        }
                                        else
                                        {
                                            pKey->key_assetId2 = PSA_ASSETID_INVALID;
                                        }
                                    }
                                }
                                else
                                {
                                    /* Error already set */
                                }
                            }
                            else
                            {
                                /* Generate a random key */
                                funcres = psaInt_AssetAlloc(AssetPolicy, KeySize,
                                                            &pKey->key_assetId);
                                if (PSA_SUCCESS == funcres)
                                {
                                    funcres = psaInt_AssetLoadRandom(pKey->key_assetId);
                                    if (PSA_SUCCESS == funcres)
                                    {
                                        /* MISRA - Intentionally empty */
                                    }
                                    else
                                    {
                                        removalResult = psaInt_AssetFree(pKey->key_assetId);
                                        if (removalResult != PSA_SUCCESS)
                                        {
                                            funcres = removalResult;
                                        }
                                        else
                                        {
                                            pKey->key_assetId = PSA_ASSETID_INVALID;
                                        }
                                    }
                                }
                                else
                                {
                                    /* Error already set */
                                }
                            }
                        }
                        else
                        {
                            /* Error already set */
                        }
                    }
                    else
                    {
                        if (sizeof(KeyDataBuffer) < KeyBlobSize)
                        {
                            funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                        }
                        else if (PSA_KEY_TYPE_IS_ASYMMETRIC(attributes->MBEDTLS_PRIVATE(type)))
                        {
                            /* Generate ECDH/ECDSA/Curve25519/EdDSA key pair */
                            funcres = local_AsymKeyGenPrv(AssetPolicy,
                                                          CurveFamily,
                                                          ModulusSize,
                                                          NULL,
                                                          KeyDataBuffer,
                                                          &KeyBlobSize);
                        }
                        else if (isBidirectionalKey)
                        {
                            if (sizeof(SymmetricKeyDataBuffer) < KeySize)
                            {
                                funcres= PSA_ERROR_INSUFFICIENT_MEMORY;
                            }
                            else
                            {
                                /* Generate a random key in plaintext - we'll import two assets from it */
                                funcres = psa_generate_random(SymmetricKeyDataBuffer, KeySize);
                            }

                            if (PSA_SUCCESS == funcres)
                            {
                                /* This will take the random plaintext key in SymmetricKeyDataBuffer,
                                 * and place a key blob (allowed to perform encryption) in
                                 * KeyDataBuffer
                                 */
                                funcres = local_LoadPlaintextExport(AssetPolicy,
                                                                    SymmetricKeyDataBuffer,
                                                                    KeySize,
                                                                    KeyDataBuffer,
                                                                    &KeyBlobSize);
                            }
                            else
                            {
                                /* Error already set */
                            }

                            if (PSA_SUCCESS == funcres)
                            {
                                /* XOR the asset policy of the first (encryption) key we've stored to get
                                 * the policy for the decryption key.
                                 */
                                AssetPolicy2 = (AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

                                /* Receive second key blob into KeyDataBuffer2 */
                                funcres = local_LoadPlaintextExport(AssetPolicy2,
                                                                    SymmetricKeyDataBuffer,
                                                                    KeySize,
                                                                    KeyDataBuffer2,
                                                                    &KeyBlobSize);
                            }
                        }
                        else
                        {
                            /* Generate a random key inside an asset directly */
                            funcres = local_LoadRandomExport(AssetPolicy,
                                                             KeySize,
                                                             KeyDataBuffer,
                                                             &KeyBlobSize);
                        }
                        if (PSA_SUCCESS == funcres)
                        {
                            /* If key_persistence is PSA_KEY_PERSISTENCE_DEFAULT, then another persistent key
                             * may be replaced in the cache if storage is limited.
                             */
                            funcres = local_GetFreeKeyEntry(&key_index, key_persistence);
                        }
                        else
                        {
                            /* Error already set */
                        }

                        if (PSA_SUCCESS == funcres)
                        {
                            pKey = &gl_PSA_Key[key_index];
                            if (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence)
                            {
                                keyID = PSA_KEY_ID_VOLATILE_MIN + (key_index - (MBEDTLS_MAX_KEY_BUFF_ENTRIES - MBEDTLS_KEY_VOLATILE_COUNT));
                                /* Store in volatile storage */
                                pKey->key = psaInt_mbedtls_calloc(1, KeyBlobSize);
                                if (NULL == pKey->key)
                                {
                                    funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                                }
                                else
                                {
                                    (void)memcpy(pKey->key,
                                                 KeyDataBuffer, KeyBlobSize);
                                }

                                if ((PSA_SUCCESS == funcres) && isBidirectionalKey)
                                {
                                    pKey->key2 = psaInt_mbedtls_calloc(1, KeyBlobSize);
                                    if (NULL == pKey->key2)
                                    {
                                        funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                                    }
                                    else
                                    {
                                        (void)memcpy(pKey->key2,
                                                     KeyDataBuffer2, KeyBlobSize);
                                    }
                                }
                            }
                            else if (isBidirectionalKey)
                            {
                                /* Store in persistent storage, with both key blobs */
                                funcres = psa_save_persistent_key(pKey,
                                                                  attributes,
                                                                  &AssetPolicy,
                                                                  KeyDataBuffer,
                                                                  KeyDataBuffer2,
                                                                  KeyBlobSize);
                            }
                            else
                            {
                                /* Store in persistent storage */
                                funcres = psa_save_persistent_key(pKey,
                                                                  attributes,
                                                                  &AssetPolicy,
                                                                  KeyDataBuffer,
                                                                  NULL,
                                                                  KeyBlobSize);
                            }
                        }
                        else
                        {
                            /* Error already set */
                        }
                    }
                }
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else
        {
            /* Error already set */
        }
    }
    if (PSA_SUCCESS == funcres)
    {
        if (NULL != pKey)
        {
            /* Initialize remaining part of the key entry */
            pKey->attributes.MBEDTLS_PRIVATE(type) = attributes->MBEDTLS_PRIVATE(type);
            pKey->attributes.MBEDTLS_PRIVATE(bits) = attributes->MBEDTLS_PRIVATE(bits);
            pKey->attributes.MBEDTLS_PRIVATE(lifetime) = attributes->MBEDTLS_PRIVATE(lifetime);
            pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
            pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg) = attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg);
            pKey->key_size = KeySize;
            pKey->AssetPolicy = AssetPolicy;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
            key->MBEDTLS_PRIVATE(key_id) = keyID;
            key->MBEDTLS_PRIVATE(owner) = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);
            pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id) = keyID;
            pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner) = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);
#else
            *key = keyID;
            pKey->attributes.MBEDTLS_PRIVATE(id) = keyID;
#endif
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        if (NULL != pKey)
        {
            /* Make sure the key entry is cleared */
            removalResult = local_RemoveKey(pKey);
            if (removalResult != PSA_SUCCESS)
            {
                funcres = removalResult;
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        /* Make sure the returned key is invalid */
        if (NULL != key)
        {
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
            key->MBEDTLS_PRIVATE(key_id) = PSA_KEY_ID_NULL;
#else
            *key = PSA_KEY_ID_NULL;
#endif
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_destroy_key
 *
 * Delete a key from wherever it is stored.
 */
psa_status_t
psa_destroy_key(mbedtls_svc_key_id_t key)
{
    psa_status_t funcres;
    psa_key_context_t * pKey;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);

    if (funcres == PSA_SUCCESS)
    {
        funcres = local_RemoveKey(pKey);
    }
    else
    {
        /* Error already set */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_purge_key
 *
 * Remove all non-essential copies of a persistent key from volatile storage.
 */
psa_status_t
psa_purge_key(mbedtls_svc_key_id_t key)
{
    psa_key_context_t * pKey;
    psa_status_t funcres = PSA_ERROR_GENERIC_ERROR;
    psa_key_id_t id;
    uint32_t temp_index;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    id = key.MBEDTLS_PRIVATE(key_id);
#else
    id = key;
#endif

    /* This function does nothing and returns successfully for volatile keys */
    if (psa_key_id_is_volatile(id))
    {
        funcres = PSA_SUCCESS;
    }
    else if ((!psa_is_valid_key_id(id, 0)) && (id != PSA_KEY_ID_IAK))
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else
    {
        for (temp_index = 0U; temp_index < (MBEDTLS_KEY_PERSISTENT_COUNT + MBEDTLS_KEY_ASSET_STORE_COUNT); temp_index++)
        {
            pKey = &gl_PSA_Key[temp_index];

#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
            if (id == pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id))
#else
            if (id == pKey->attributes.MBEDTLS_PRIVATE(id))
#endif
            {
                if (PSA_KEY_LIFETIME_GET_PERSISTENCE(pKey->attributes.MBEDTLS_PRIVATE(lifetime)) ==
                    PSA_KEY_PERSISTENCE_HSM_ASSET_STORE)
                {
                    /* Nothing to purge for keys with this persistence */
                    funcres = PSA_SUCCESS;
                }
                else
                {
                    /* Remove the cached copy (key material and attributes) of the persistent key.
                     * It can (and will) still be loaded back upon next request to use the key.
                     */
                    if (NULL != pKey->key)
                    {
                        /* Remove the volatile entry */
                        psaInt_mbedtls_free(pKey->key);

                        funcres = PSA_SUCCESS;
                    }
                    else
                    {
                        /* If the key is found in the cache, then the key material is
                        * expected to be allocated there too
                        */
                        funcres = PSA_ERROR_CORRUPTION_DETECTED;
                    }

                    /* If the key is symmetric with bi-directional usage, we may have to
                     * free the second allocated key blob
                     */
                    if (NULL != pKey->key2)
                    {
                        /* Remove the volatile entry */
                        psaInt_mbedtls_free(pKey->key2);

                        funcres = PSA_SUCCESS;
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }

                    (void)memset(pKey, 0, sizeof(psa_key_context_t));
                }

                break;
            }
        }

    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * psa_get_key_attributes
 *
 * Return key attributes of the requested key ID.
 */
psa_status_t
psa_get_key_attributes(mbedtls_svc_key_id_t key,
                       psa_key_attributes_t * attributes)
{
    psa_key_context_t * pKey;
    psa_status_t funcres;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (PSA_SUCCESS == funcres)
    {
        if (NULL == attributes)
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else
        {
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
            attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id) = pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id);
            attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner) = pKey->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);
#else
            attributes->MBEDTLS_PRIVATE(id) = pKey->attributes.MBEDTLS_PRIVATE(id);
#endif
            attributes->MBEDTLS_PRIVATE(bits) = pKey->attributes.MBEDTLS_PRIVATE(bits);
            attributes->MBEDTLS_PRIVATE(type) = pKey->attributes.MBEDTLS_PRIVATE(type);
            attributes->MBEDTLS_PRIVATE(lifetime) = pKey->attributes.MBEDTLS_PRIVATE(lifetime);
            attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg) = pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg);
            attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2) = pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2);
            attributes->MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) = pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
        }
    }
    else
    {
        /* Error already set */
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * psa_reset_key_attributes
 *
 * Reset key attributes structure to freshly initialized state.
 */
void
psa_reset_key_attributes(psa_key_attributes_t * attributes)
{
    memset(attributes, 0, sizeof(*attributes));
}

/*----------------------------------------------------------------------------
 * psa_copy_key
 *
 * Copy a key.
 */
psa_status_t
psa_copy_key(mbedtls_svc_key_id_t source_key,
             const psa_key_attributes_t * attributes,
             mbedtls_svc_key_id_t * target_key)
{
    psa_key_context_t * pSrcKeyEntry;
    psa_key_context_t * pTgtKeyEntry;
    size_t CopyKeySize;
    PsaPolicyMask_t AssetPolicy2;
    psa_key_persistence_t key_persistence_src;
    psa_key_location_t key_location_src;
    psa_key_usage_t key_usage_src;
    psa_key_type_t key_type_src;
    psa_key_persistence_t key_persistence_trgt;
    psa_key_location_t key_location_trgt;
    psa_status_t funcres = PSA_SUCCESS;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;
    uint32_t target_index;
    psa_key_id_t attributesID;
    psa_key_id_t trgtKeyEntryID;
    bool isBidirectionalKey = false;
    /* If the key policy needs to be restricted based on the intersection of the provided policy and the source policy,
     * we'll need a separate attributes struct to use for the actual key creation without overwriting the application's struct.
     */
    psa_key_attributes_t actual_attributes = *attributes;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
    attributesID = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id);
#else
    attributesID = attributes->MBEDTLS_PRIVATE(id);
#endif
    key_persistence_trgt = PSA_KEY_LIFETIME_GET_PERSISTENCE(attributes->MBEDTLS_PRIVATE(lifetime));

    /* Check for a valid key ID if the copy is meant to be persistent. The ID must be in range
     * and not duplicate that of an existing key.
     */
    if (PSA_KEY_ID_NULL != attributesID)
    {
        /* Check for both error conditions, but don't overwrite the first if the second is also
         * true
         */
        if (!psa_is_valid_key_id(attributesID, 0))
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if ((PSA_KEY_PERSISTENCE_DEFAULT == key_persistence_trgt) ||
                 (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence_trgt))
        {
            if (PSA_SUCCESS == psaInt_KeyMgmtGetKey(attributes->MBEDTLS_PRIVATE(id), &pTgtKeyEntry))
            {
                funcres = PSA_ERROR_ALREADY_EXISTS;
            }
            else
            {
                /* Nothing to do. psaInt_KeyMgmtGetKey exhaustively checks for pre-existing keys. */
            }
        }
        else
        {
            /* When a key id is passed through the attributes struct, the key must be either
             * persistent or meant to be stored in Asset Store.
             */
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else if ((PSA_KEY_PERSISTENCE_VOLATILE == key_persistence_trgt) ||
             (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence_trgt))
    {
        /* Only keys with these two persistences may be created without an input key ID */
    }
    else
    {
        /* A key ID must be provided for keys without volatile or asset store persistence */
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }

    if (PSA_SUCCESS == funcres)
    {
        funcres = psaInt_KeyMgmtGetKey(source_key, &pSrcKeyEntry);
    }

    if (PSA_SUCCESS == funcres)
    {
        /* Get source key data */
        key_persistence_src = PSA_KEY_LIFETIME_GET_PERSISTENCE(pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(lifetime));
        key_location_src = PSA_KEY_LIFETIME_GET_LOCATION(pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(lifetime));
        key_usage_src = pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
        key_type_src = pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(type);

        if ((PSA_KEY_USAGE_ENCRYPT == (key_usage_src & PSA_KEY_USAGE_ENCRYPT)) &&
            (PSA_KEY_USAGE_DECRYPT == (key_usage_src & PSA_KEY_USAGE_DECRYPT)) &&
            (PSA_KEY_TYPE_IS_SYMMETRIC(key_type_src)))
        {
            /* Place marker to note that two key blobs or assets will have to be created,
             * if the key is to be used as an HSM asset. In this case, the assetPolicy populated
             * by local_SymKeyType will reflect only the encryption usage. We will populate
             * a second asset policy to preserve the user-specified decryption usage.
             */
            isBidirectionalKey = true;
        }

        if ((NULL == attributes) ||
            (NULL == target_key) ||
            ((0U != attributes->MBEDTLS_PRIVATE(bits)) &&
             (pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(bits) != attributes->MBEDTLS_PRIVATE(bits))) ||
            ((attributes->MBEDTLS_PRIVATE(type) != PSA_KEY_TYPE_NONE) &&
             (pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(type) != attributes->MBEDTLS_PRIVATE(type))))
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if ((PSA_KEY_USAGE_COPY != (key_usage_src & PSA_KEY_USAGE_COPY)) ||
                 ((PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location_src) &&
                  (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence_src)))
        {
            funcres = PSA_ERROR_NOT_PERMITTED;
        }
        else
        {
            /* Validate that the algorithm for the target key is a valid combination with that of the source key */
            funcres = psa_restrict_key_policy(pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(type),
                                              &actual_attributes.MBEDTLS_PRIVATE(policy),
                                              &pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(policy));

            if (PSA_SUCCESS == funcres)
            {
                key_location_trgt = PSA_KEY_LIFETIME_GET_LOCATION(attributes->MBEDTLS_PRIVATE(lifetime));

                /* If key_persistence_trgt is PSA_KEY_PERSISTENCE_DEFAULT, then another persistent
                 * key may be replaced in the cache if storage is limited.
                 */
                funcres = local_GetFreeKeyEntry(&target_index, key_persistence_trgt);
            }
            else
            {
                /* Error already set */
            }

            if (PSA_SUCCESS == funcres)
            {
                psa_key_context_t * pTrgtKeyEntry = &gl_PSA_Key[target_index];
                psa_key_id_t tKeyID;
                if (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence_trgt)
                {
                    /* Volatile key IDs exist in a specific region of the global array. The base index of this
                     * region is the difference between the max number of entries and the number of volatile
                     * keys
                     */
                    tKeyID = PSA_KEY_ID_VOLATILE_MIN + (target_index -
                                                       (MBEDTLS_MAX_KEY_BUFF_ENTRIES - MBEDTLS_KEY_VOLATILE_COUNT));
                }
                else if ((PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence_trgt) &&
                         (PSA_KEY_ID_NULL == attributesID))
                {
                    /* Set an automatic key ID for an Asset Store key. Only persistent keys come
                     * before asset store keys in the key array.
                     */
                    tKeyID = PSA_KEY_ID_ASSET_STORE_AUTO_MIN + (target_index - MBEDTLS_KEY_PERSISTENT_COUNT);
                }
                else
                {
                    tKeyID = attributesID;
                }
                /* Set the attributes of the target key entry. Note that the key policy is the only thing that may be different between actual_attributes and the passed in
                 * attributes pointer. Therefore, the attributes pointer will be used directly to store all information besides the key policy.
                 */
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                target_key->MBEDTLS_PRIVATE(key_id) = tKeyID;
                target_key->MBEDTLS_PRIVATE(owner) = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);
                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id) = tKeyID;
                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner) = attributes->MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(owner);
                trgtKeyEntryID = pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(id).MBEDTLS_PRIVATE(key_id);
#else
                *target_key = tKeyID;
                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(id) = tKeyID;
                trgtKeyEntryID = pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(id);
#endif

                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(lifetime) = attributes->MBEDTLS_PRIVATE(lifetime);
                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(type) = pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(type);
                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(bits) = pSrcKeyEntry->attributes.MBEDTLS_PRIVATE(bits);
                /* The intersection of the policies provided and of the source key are stored in actual_attributes */
                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) = actual_attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg) = actual_attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg);
                pTrgtKeyEntry->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2) = actual_attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg2);
                pTrgtKeyEntry->key_size = pSrcKeyEntry->key_size;
                pTrgtKeyEntry->AssetPolicy = pSrcKeyEntry->AssetPolicy;

                /* First get the source key from right location */
                if (PSA_KEY_LOCATION_LOCAL_STORAGE == key_location_src)
                {
                    /* Source key is stored in plaintext format */
                    CopyKeySize = pSrcKeyEntry->key_size;
                }
                else if ((PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location_src) &&
                         (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location_trgt))
                {
                    /* Source key is stored in wrapped format */
                    CopyKeySize = PSA_KEYBLOB_SIZE(pSrcKeyEntry->key_size);
                }
                else
                {
                    funcres = PSA_ERROR_NOT_PERMITTED;
                }

                if (PSA_SUCCESS == funcres)
                {
                    if (NULL != pSrcKeyEntry->key)
                    {
                        /* Source key is in volatile storage */
                        (void)memcpy(KeyDataBuffer, pSrcKeyEntry->key, CopyKeySize);
                    }
                    else
                    {
                        /* Safeguard: Should not happen */
                        funcres = PSA_ERROR_INVALID_ARGUMENT;
                    }

                    if ((PSA_SUCCESS == funcres) && isBidirectionalKey &&
                        (CopyKeySize == PSA_KEYBLOB_SIZE(pSrcKeyEntry->key_size)))
                    {
                        /* key2 is only allocated if it is storing a key blob of a symmetric
                         * key - it would store the blob of an asset used for decryption.
                         */
                        if (NULL != pSrcKeyEntry->key2)
                        {
                            /* Source key blob for decryption is in volatile storage */
                            (void)memcpy(KeyDataBuffer2, pSrcKeyEntry->key2, CopyKeySize);
                        }
                        else
                        {
                            /* Safeguard: Should not happen */
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                    }
                }
                else
                {
                    /* Error already set */
                }

                if (PSA_SUCCESS == funcres)
                {
                    /* Check the location of the target key */
                    if (PSA_KEY_LOCATION_LOCAL_STORAGE == key_location_trgt)
                    {
                        /* We have already checked that the source location is also
                         * PSA_KEY_LOCATION_LOCAL_STORAGE if we are in this condition.
                         * Therefore, there is no need to use KeyDataBuffer2 and
                         * pTrgetKeyEntry->key2.
                         */
                        if (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence_trgt)
                        {
                            /* Store in volatile storage */
                            pTrgtKeyEntry->key = psaInt_mbedtls_calloc(1, CopyKeySize);
                            if (NULL == pTrgtKeyEntry->key)
                            {
                                funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                            }
                            else
                            {
                                (void)memcpy(pTrgtKeyEntry->key, KeyDataBuffer, CopyKeySize);
                            }
                        }
                        else if ((PSA_KEY_PERSISTENCE_DEFAULT == key_persistence_trgt) &&
                                 (PSA_KEY_ID_NULL != trgtKeyEntryID))
                        {
                            /* Store in persistent storage */
                            funcres = psa_save_persistent_key(pTrgtKeyEntry,
                                                              &pTrgtKeyEntry->attributes,
                                                              &pTrgtKeyEntry->AssetPolicy,
                                                              KeyDataBuffer,
                                                              NULL,
                                                              CopyKeySize);
                        }
                        else
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                    }
                    else if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location_trgt)
                    {
                        /* Target key goes to Secure Element store */
                        if (PSA_KEY_PERSISTENCE_VOLATILE == key_persistence_trgt)
                        {
                            if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location_src)
                            {
                                /* Source key is already in wrapped format */
                                pTrgtKeyEntry->key = psaInt_mbedtls_calloc(1, CopyKeySize);
                                if (NULL == pTrgtKeyEntry->key)
                                {
                                    funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                                }
                                else
                                {
                                    (void)memcpy(pTrgtKeyEntry->key,
                                                 KeyDataBuffer, CopyKeySize);
                                }

                                if ((PSA_SUCCESS == funcres) && isBidirectionalKey)
                                {
                                    pTrgtKeyEntry->key2 = psaInt_mbedtls_calloc(1, CopyKeySize);
                                    if (NULL == pTrgtKeyEntry->key2)
                                    {
                                        funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                                    }
                                    else
                                    {
                                        (void)memcpy(pTrgtKeyEntry->key2,
                                                     KeyDataBuffer2, CopyKeySize);
                                    }
                                }
                            }
                            else
                            {
                                /* Source key is in plaintext format and must
                                 * be converted to wrapped format */
                                size_t KeyBlobSize = PSA_KEYBLOB_SIZE(CopyKeySize);

                                pTrgtKeyEntry->key = psaInt_mbedtls_calloc(1, KeyBlobSize);
                                if (NULL == pTrgtKeyEntry->key)
                                {
                                    funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                                }
                                else
                                {
                                    funcres = local_LoadPlaintextExport(pTrgtKeyEntry->AssetPolicy,
                                                                        KeyDataBuffer,
                                                                        CopyKeySize,
                                                                        pTrgtKeyEntry->key,
                                                                        &KeyBlobSize);
                                }

                                if ((PSA_SUCCESS == funcres) && isBidirectionalKey)
                                {
                                    pTrgtKeyEntry->key2 = psaInt_mbedtls_calloc(1, KeyBlobSize);
                                    if (NULL == pTrgtKeyEntry->key2)
                                    {
                                        funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
                                    }
                                    else
                                    {
                                        /* XOR the asset policy of the first (encryption) key we've stored to get
                                         * the policy for the decryption key.
                                         */
                                        AssetPolicy2 = (pTrgtKeyEntry->AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

                                        funcres = local_LoadPlaintextExport(AssetPolicy2,
                                                                            KeyDataBuffer,
                                                                            CopyKeySize,
                                                                            pTrgtKeyEntry->key2,
                                                                            &KeyBlobSize);
                                    }
                                }
                            }
                        }
                        else if (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence_trgt)
                        {
                            /* Target key goes to VaultIP */
                            funcres = psaInt_AssetAlloc(pTrgtKeyEntry->AssetPolicy,
                                                        pSrcKeyEntry->key_size,
                                                        &pTrgtKeyEntry->key_assetId);
                            if (PSA_SUCCESS == funcres)
                            {
                                if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location_src)
                                {
                                    /* Source key is in wrapped format */
                                    funcres = local_LoadImport(pTrgtKeyEntry->key_assetId,
                                                               KeyDataBuffer,
                                                               PSA_KEYBLOB_SIZE(pSrcKeyEntry->key_size));
                                }
                                else
                                {
                                    /* Source key is in plaintext format */
                                    funcres = psaInt_AssetLoadPlaintext(pTrgtKeyEntry->key_assetId,
                                                                        KeyDataBuffer,
                                                                        pSrcKeyEntry->key_size);
                                }
                            }
                            else
                            {
                                /* Error already set */
                            }

                            if ((PSA_SUCCESS == funcres) && isBidirectionalKey)
                            {
                                /* XOR the asset policy of the first (encryption) key we've stored to get
                                 * the policy for the decryption key.
                                 */
                                AssetPolicy2 = (pTrgtKeyEntry->AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

                                funcres = psaInt_AssetAlloc(AssetPolicy2,
                                                            pSrcKeyEntry->key_size,
                                                            &pTrgtKeyEntry->key_assetId2);
                                if (PSA_SUCCESS == funcres)
                                {
                                    if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location_src)
                                    {
                                        /* Source key is in wrapped format */
                                        funcres = local_LoadImport(pTrgtKeyEntry->key_assetId2,
                                                                   KeyDataBuffer2,
                                                                   PSA_KEYBLOB_SIZE(pSrcKeyEntry->key_size));
                                    }
                                    else
                                    {
                                        /* Source key is in plaintext format. In this case, there's only
                                         * one version of the key stored, so we will retrieve it from
                                         * KeyDataBuffer instead of KeyDataBuffer2
                                         */
                                        funcres = psaInt_AssetLoadPlaintext(pTrgtKeyEntry->key_assetId2,
                                                                            KeyDataBuffer,
                                                                            pSrcKeyEntry->key_size);
                                    }
                                }
                                else
                                {
                                    /* Error already set */
                                }
                            }
                        }
                        else if ((PSA_KEY_PERSISTENCE_DEFAULT == key_persistence_trgt) &&
                                 (PSA_KEY_ID_NULL != trgtKeyEntryID))
                        {
                            if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location_src)
                            {
                                /* Source key is already in wrapped format */
                                funcres = psa_save_persistent_key(pTrgtKeyEntry,
                                                                  &pTrgtKeyEntry->attributes,
                                                                  &pTrgtKeyEntry->AssetPolicy,
                                                                  KeyDataBuffer,
                                                                  KeyDataBuffer2,
                                                                  CopyKeySize);
                            }
                            else
                            {
                                /* Source key is in plaintext format and must
                                 * be converted to wrapped format */
                                size_t KeyBlobSize = PSA_KEYBLOB_SIZE(CopyKeySize);

                                if (isBidirectionalKey)
                                {
                                    /* XOR the asset policy of the first (encryption) key we've stored to get
                                     * the policy for the decryption key.
                                     */
                                    AssetPolicy2 = (pTrgtKeyEntry->AssetPolicy ^ EIP130_ASSET_POLICY_SCDIRENCDEC);

                                    funcres = local_LoadPlaintextExport(AssetPolicy2,
                                                                        KeyDataBuffer,
                                                                        CopyKeySize,
                                                                        KeyDataBuffer2,
                                                                        &KeyBlobSize);

                                    if (PSA_SUCCESS == funcres)
                                    {
                                        /* KeyDataBuffer contains the plaintext, but we'll also use it to retrieve
                                         * the key blob. We can overwrite the plaintext.
                                         */
                                        funcres = local_LoadPlaintextExport(pTrgtKeyEntry->AssetPolicy,
                                                                            KeyDataBuffer,
                                                                            CopyKeySize,
                                                                            KeyDataBuffer,
                                                                            &KeyBlobSize);
                                    }
                                    else
                                    {
                                        /* Error already set */
                                    }

                                    if (PSA_SUCCESS == funcres)
                                    {
                                        /* Store in persistent storage */
                                        funcres = psa_save_persistent_key(pTrgtKeyEntry,
                                                                          &pTrgtKeyEntry->attributes,
                                                                          &pTrgtKeyEntry->AssetPolicy,
                                                                          KeyDataBuffer,
                                                                          KeyDataBuffer2,
                                                                          KeyBlobSize);
                                    }
                                    else
                                    {
                                        /* Error already set */
                                    }
                                }
                                else
                                {
                                    /* KeyDataBuffer contains the plaintext, but we'll also use it to retrieve
                                     * the key blob. We can overwrite the plaintext.
                                     */
                                    funcres = local_LoadPlaintextExport(pTrgtKeyEntry->AssetPolicy,
                                                                        KeyDataBuffer,
                                                                        CopyKeySize,
                                                                        KeyDataBuffer,
                                                                        &KeyBlobSize);
                                    if (PSA_SUCCESS == funcres)
                                    {
                                        /* Store in persistent storage */
                                        funcres = psa_save_persistent_key(pTrgtKeyEntry,
                                                                          &pTrgtKeyEntry->attributes,
                                                                          &pTrgtKeyEntry->AssetPolicy,
                                                                          KeyDataBuffer,
                                                                          NULL,
                                                                          KeyBlobSize);
                                    }
                                    else
                                    {
                                        /* Error already set */
                                    }
                                }
                            }
                        }
                        else
                        {
                            funcres = PSA_ERROR_INVALID_ARGUMENT;
                        }
                    }
                    else
                    {
                        funcres = PSA_ERROR_NOT_PERMITTED;
                    }
                }
                else
                {
                    /* Error already set */
                }
                if (funcres != PSA_SUCCESS)
                {
                    /* Do necessary cleanup - overwrite existing error if there was a cleanup issue, as it
                     * would interfere with future operations
                     */
                    removalResult = local_RemoveKey(pTrgtKeyEntry);
                    if (removalResult != PSA_SUCCESS)
                    {
                        funcres = removalResult;
                    }
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
            else
            {
                /* Error already set */
            }
        }
    }
    else
    {
        /* Error return is already set */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_export_key
 */
psa_status_t
psa_export_key(mbedtls_svc_key_id_t key,
               uint8_t * data,
               size_t data_size,
               size_t * data_length)
{
    psa_key_context_t * pKey;
    psa_status_t funcres;
    psa_key_location_t key_location;
    psa_key_persistence_t key_persistence;
    psa_key_usage_t key_usage;
    size_t CurveBits;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);

    if (PSA_SUCCESS != funcres)
    {
        /* Error return is already set */
    }
    else if ((NULL == data) ||
             (NULL == data_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_KEY_USAGE_EXPORT != (pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_EXPORT))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (data_size < (size_t)(PSA_EXPORT_KEY_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(type),
                                                             pKey->attributes.MBEDTLS_PRIVATE(bits))))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        key_location = PSA_KEY_LIFETIME_GET_LOCATION(pKey->attributes.MBEDTLS_PRIVATE(lifetime));
        key_persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(pKey->attributes.MBEDTLS_PRIVATE(lifetime));
        key_usage = pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage);
        if (PSA_KEY_LOCATION_LOCAL_STORAGE == key_location)
        {
            if (NULL != pKey->key)
            {
                if ((PSA_KEY_TYPE_IS_ASYMMETRIC(pKey->attributes.MBEDTLS_PRIVATE(type))) &&
                    (PSA_KEY_TYPE_IS_KEY_PAIR(pKey->attributes.MBEDTLS_PRIVATE(type))))
                {
                    /* This condition is specifically for asymmetric private keys */
                    CurveBits = pKey->attributes.MBEDTLS_PRIVATE(bits);
                    *data_length = PSA_ASYM_DATA_SIZE_B2B(CurveBits);

                    if (CurveBits == 255U)
                    {
                        /* If Curve25519 is used, the private key should be exported in little-endian format.
                         * Since all asymmetric private keys are already stored in little-endian for the HSM
                         * component format, we can just copy the key material directly out. The key material
                         * is also already pruned.
                         */
                        (void)memcpy(data, &pKey->key[PSA_ASYM_DATA_VHEADER], PSA_ASYM_DATA_SIZE_B2B(CurveBits));
                    }
                    else
                    {
                        /* For Weierstrass curve families, the private key is expected to be output
                         * in big-endian. Therefore, the key material must be reversed from the
                         * component format it is stored in.
                         */
                        psaInt_ReverseMemCpy(data, &pKey->key[PSA_ASYM_DATA_VHEADER], PSA_ASYM_DATA_SIZE_B2B(CurveBits));
                    }
                }
                else if (PSA_KEY_TYPE_IS_UNSTRUCTURED(pKey->attributes.MBEDTLS_PRIVATE(type)))
                {
                    *data_length = pKey->key_size;
                    (void)memcpy(data, pKey->key, *data_length);
                }
                else
                {
                    /* TODO: Add support for exporting public keys via psa_export_key(). See HSM_DDK-85. */
                    funcres = PSA_ERROR_NOT_SUPPORTED;
                }
            }
            else if (PSA_KEY_PERSISTENCE_DEFAULT == key_persistence)
            {
                /* TODO: Persistent key material that is not currently cached in RAM cannot be
                 * exported to the caller. This should be supported - see HSM_DDK-84.
                 */
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            else
            {
                /* Safeguard: Should never happen, already blocked by
                 * psa_import_key() or psa_generate_key()
                 */
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else if (PSA_KEY_LOCATION_HSM_ASSET_STORE == key_location)
        {
            if ((PSA_KEY_TYPE_IS_UNSTRUCTURED(pKey->attributes.MBEDTLS_PRIVATE(type))) ||
                ((PSA_KEY_TYPE_IS_ASYMMETRIC(pKey->attributes.MBEDTLS_PRIVATE(type))) &&
                (PSA_KEY_TYPE_IS_KEY_PAIR(pKey->attributes.MBEDTLS_PRIVATE(type)))))
            {
                if (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE == key_persistence)
                {
                    /* Exporting a key from HSM Asset Store is not a supported feature. */
                    funcres = PSA_ERROR_NOT_SUPPORTED;
                }
                else if (NULL != pKey->key)
                {
                    /* If the key slot is storing a key blob, it can be directly copied out. In the case of symmetric
                     * keys with symmetric usage, two key blobs will be copied out. The key slot may store the key blob
                     * for persistent keys as well, so long as they have not been purged from nor replaced in RAM.
                     */
                    *data_length = (PSA_KEYBLOB_SIZE(pKey->key_size));

                    (void)memcpy(data, pKey->key, *data_length);

                    /* In the case where the key's usage is for both encrypt and decrypt, pKey->key2 will
                     * have the second key blob. This is never the case for asymmetric keys that we support.
                     */
                    if ((NULL != pKey->key2) && (PSA_KEY_USAGE_ENCRYPT == (key_usage & PSA_KEY_USAGE_ENCRYPT)) &&
                        (PSA_KEY_USAGE_DECRYPT == (key_usage & PSA_KEY_USAGE_DECRYPT)))
                    {
                        (void)memcpy(data + (*data_length), pKey->key2, *data_length);

                        *data_length += (PSA_KEYBLOB_SIZE(pKey->key_size));
                    }
                }
                else if (PSA_KEY_PERSISTENCE_DEFAULT == key_persistence)
                {
                    /* TODO: Persistent key material that is not currently cached in RAM cannot be
                     * exported to the caller. This should be supported - see HSM_DDK-84.
                     */
                    funcres = PSA_ERROR_NOT_SUPPORTED;
                }
                else
                {
                    /* If the key does not exist in KeyStore RAM, Flash, or the HSM Asset Store, then the arguments passed in are wrong. */
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
            }
            else
            {
                /* TODO: Add support for exporting public keys via psa_export_key(). See HSM_DDK-85. */
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
        }
        else
        {
            funcres = PSA_ERROR_NOT_SUPPORTED;
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_export_public_key
 */
psa_status_t
psa_export_public_key(mbedtls_svc_key_id_t key,
                      uint8_t * data,
                      size_t data_size,
                      size_t * data_length)
{
    psa_key_context_t *pKey = NULL;
    uint8_t CurveFamily = 0U;
    PsaAssetId_t PrvKeyAssetId = PSA_ASSETID_INVALID;
    psa_status_t funcres = PSA_SUCCESS;
    /* removalResult is used in cases where funcres already reflects a failure, but the cleanup
     * process is not guaranteed to succeed. removalResult will overwrite funcres when cleanup
     * fails - but if it succeeds, we must not replace the original error condition in funcres.
     */
    psa_status_t removalResult;
    psa_key_persistence_t key_persistence;
    uint8_t fECDH = 0U;
    bool isPubKey = false;
    size_t curve_bits;

    if ((NULL == data) ||
        (NULL == data_length) ||
        (data_size == 0U))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    }

    if (PSA_SUCCESS == funcres)
    {
        key_persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(pKey->attributes.MBEDTLS_PRIVATE(lifetime));
        /* Key found - it must be an asymmetric ECC key_pair or public key. Note that exporting a public key
         * is always allowed in either case, regardless of key usage flags.
         */
        if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(pKey->attributes.MBEDTLS_PRIVATE(type)))
        {
            if (PSA_ALG_IS_KEY_AGREEMENT(pKey->attributes.MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(alg)))
            {
                fECDH = 255U;
            }
            else
            {
                /* MISRA - Intentially empty */
            }

            CurveFamily = local_CurveFamilyFromKeyType(pKey->attributes.MBEDTLS_PRIVATE(type), fECDH);

            if (CurveFamily == EIP130DOMAIN_ECC_FAMILY_NONE)
            {
                /* Safeguard: Should never happen, checked by psa_import_key()
                 *            or psa_generate_key()
                 */
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
        }
        else if (PSA_KEY_TYPE_IS_PUBLIC_KEY(pKey->attributes.MBEDTLS_PRIVATE(type)))
        {
            isPubKey = true;
            funcres = psaInt_KeyMgmtLoadKey(pKey, NULL, 0, PSA_KEY_USAGE_EXPORT, data, data_size, (uint32_t *)data_length);
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else
    {
        /* Error already set */
    }

    if (!isPubKey)
    {
        if (PSA_SUCCESS == funcres)
        {
            funcres = psaInt_KeyMgmtLoadKey(pKey, &PrvKeyAssetId, 0, 0, NULL, 0, NULL);
        }
        else
        {
            /* Error already set */
        }
        if (PSA_SUCCESS == funcres)
        {
            curve_bits = (size_t)pKey->attributes.MBEDTLS_PRIVATE(bits);

            funcres = local_AsymKeyGenPub(PrvKeyAssetId, NULL, pKey->AssetPolicy, false,
                                          CurveFamily, curve_bits,
                                          fECDH, data, data_size, data_length);
        }
        else
        {
            /* Error already set */
        }

        /* This private key asset is no longer needed, unless it was already stored in that format */
        if ((PSA_ASSETID_INVALID != PrvKeyAssetId) && (PSA_KEY_PERSISTENCE_HSM_ASSET_STORE != key_persistence))
        {
            removalResult = psaInt_AssetFree(PrvKeyAssetId);
            if (PSA_SUCCESS != removalResult)
            {
                funcres = removalResult;
            }
            else
            {
                pKey->key_assetId = PSA_ASSETID_INVALID;
            }
        }
        else
        {
            /* MISRA - Intentionally empty */
        }
    }
    else
    {
        /* MISRA - Intentionally empty */
    }

    return funcres;
}


#ifdef PSA_ENABLE_DEBUG_FUNCTIONS
/*----------------------------------------------------------------------------
 * psaDebug_KeyStoreDump
 */
void
psaDebug_KeyStoreDump(void)
{
    psa_status_t funcres;
    uint32_t key_index;

    for (key_index = 0U; key_index <= MBEDTLS_MAX_KEY_BUFF_ENTRIES; key_index++)
    {
        if (0U != gl_PSA_Key[key_index].fAllocated)
        {
            const psa_key_context_t * const pKey = &gl_PSA_Key[key_index];

            LOG_CRIT("Key %u exists with a size of %u bytes (0x%" PRIx64 ")\n",
                     key_index, (uint32_t)pKey->key_size, pKey->AssetPolicy);
            if (0U != pKey->key_assetId)
            {
                LOG_CRIT("  ==> VaultIP Asset Store (0x%X)\n",
                         pKey->key_assetId);
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            if (NULL != pKey->key)
            {
                LOG_CRIT("  ==> Volatile PSA Key Store\n");
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            if (PSA_KEY_ID_NULL != pKey->attributes.MBEDTLS_PRIVATE(id))
            {
                LOG_CRIT("  ==> Persistent PSA Key Store (%u)\n",
                         pKey->attributes.MBEDTLS_PRIVATE(id));
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    for (key_index = 1U; key_index < PSA_MAX_KEY_BITS; key_index++)
    {
        struct psa_storage_info_t info;

        funcres = psaInt_KeyStore_PersistentInfo(key_index, &info);
        if (PSA_ERROR_INVALID_HANDLE == funcres)
        {
            /* All UID handled */
            break;
        }
        else
        {
            if (PSA_SUCCESS == funcres)
            {
                LOG_CRIT("Persistent Key %u exists with a size of %u bytes\n",
                         key_index, (uint32_t)info.size);
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
    }
}
#endif


/* end of file adapter_psa_key_management.c */
