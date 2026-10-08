/**
 * @file adapter_psa_asset.h
 *
 * @brief PSA API - Asset Management services definitions
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

#ifndef INCLUDE_GUARD_ADAPTER_PSA_ASSET_H
#define INCLUDE_GUARD_ADAPTER_PSA_ASSET_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h> // uint8_t, uint16_t, uint32_t, uint64_t
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_asset_policy.h>    // Asset policy defines based on cs_eip130.h
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>            // psa_status_t, PsaAssetId_t

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/** Asset Identifier, refers to an Asset in the Asset Store.\n
 *  The Asset Identifier (AssetId) value is implementation specific and its
 *  value should not be used directly, except for comparing against
 *  PSA_ASSETID_INVALID. */
typedef uint32_t PsaAssetId_t;

/** Guaranteed unused AssetId value */
#define PSA_ASSETID_INVALID  0U


/** The maximum value for the AssetSize parameter used in this API.\n
 *  Note: DH/DSA Domain parameters are taken as maximum reference */
#define PSA_ASSET_SIZE_MAX   (((3U * 32U) + 3072U + 3072U + 256U) / 8U)


/** The maximum value for the AssetNumber parameter used in this API. */
#define PSA_ASSET_NUMBER_MAX        126U

/** The maximum number of FW constants that needs to be added to the
 *  PSA_ASSET_NUMBER_MAX to get the actual maximum AssetNumber value. */
#define PSA_ASSET_NUMBER_CONSTANTS  3U


/** The maximum value for the PolicyNumber parameter used in this API. */
#define PSA_POLICY_NUMBER_MAX   30U


/** The minimum length of the label used in the Key Derivation Function (KDF). */
#define PSA_KDF_LABEL_MIN_SIZE       53U

/** The maximum length of the label used in the Key Derivation Function (KDF). */
#define PSA_KDF_LABEL_MAX_SIZE       (224U - 20U)


/** The minimum length of the label used in the AES-SIV keyblob export/import. */
#define PSA_KEYBLOB_AAD_MIN_SIZE     33U

/** The maximum length of the label used in the AES-SIV keyblob export/import. */
#define PSA_KEYBLOB_AAD_MAX_SIZE     224U


/** The extra wrapping bits necessary in an AES-SIV keyblob. */
#define PSA_KEYBLOB_ADDITIONAL_BYTES (128U / 8U)

/** The expected size of an AES-SIV keyblob.\n
 *  Note: AssetSize is the size of the Asset in octects (bytes). */
static inline size_t
PSA_KEYBLOB_SIZE(const size_t AssetSize)
{
    return (PSA_KEYBLOB_ADDITIONAL_BYTES + AssetSize);
}

/** The expected size of key material wrapped by AES-SIV.\n
 *  Note: KeyBlobSize is the size of the key blob in octects (bytes). */
static inline size_t
PSA_KEYMATERIAL_SIZE(const size_t KeyBlobSize)
{
    return (KeyBlobSize - PSA_KEYBLOB_ADDITIONAL_BYTES);
}

/** Asset Policy is a bitmask that defines the type and use of an Asset.\n
 *  The PSA_POLICY_* defines should be used to construct the Asset Policy
 *  bitmask.\n
 *  Note: The Asset Policy limitations depend on the implementation. So, please
 *        check the documentation.\n
 *  Note 2: As of HW V3 / AssetPolicy V2, the VAL_POLICY_* defines
 *         are deprecrated and only exist for backwards compatibility.\n
 *         Please use the EIP130_ASSET_POLICY_* defines
 *         from the DriverLibrary (eip130_asset_policy.h)\n
 * */
typedef uint64_t PsaPolicyMask_t;


#define PSA_POLICY_SOURCE_NON_SECURE          EIP130_ASSET_POLICY_SOURCENONSECURE
#define PSA_POLICY_CROSS_DOMAIN               EIP130_ASSET_POLICY_CROSSDOMAIN
#define PSA_POLICY_EXPORT                     EIP130_ASSET_POLICY_EXPORTABLE

/* Asset numbers for special Static Assets */
/* - OTP */
#define PSA_ASSETNUMBER_NOTUSED     0x0       /* Not used/invalid number */
#define PSA_ASSETNUMBER_COID        0x60      /* Crypto Officer Identifer */
#define PSA_ASSETNUMBER_HUK         0x61      /* Hardware Unique Key */
#define PSA_ASSETNUMBER_SFWBPKD     0x62      /* Secure FirmWare Boot Public Key Digest */
#define PSA_ASSETNUMBER_SFWBCR      0x63      /* Secure FirmWare Boot Confidentiality Root */
#define PSA_ASSETNUMBER_SFWBVER     0x64      /* Secure FirmWare Boot Version (rollback value) */
#define PSA_ASSETNUMBER_ECI_SDKey   0x68      /* ECI Secure Debug ECDSA256 Public key */
#define PSA_ASSETNUMBER_Invalid     0x7F      /* Invalid number */

/* - Asset numbers of firmware constants Asset */
#define PSA_ASSETNUMBER_AUTHKEY1    0x81      /*# Secure Debug Authentication key 1 */
#define PSA_ASSETNUMBER_AUTHKEY2    0x82      /*# Secure Debug Authentication key 2 */
#define PSA_ASSETNUMBER_AUTHKEY3    0x83      /*# Secure Debug Authentication key 3 */

psa_status_t
psaInt_AssetAlloc(const PsaPolicyMask_t AssetPolicy,
                  const size_t AssetSize,
                  PsaAssetId_t * const AssetId_p);

psa_status_t
psaInt_AssetFree(const PsaAssetId_t AssetId);

psa_status_t
psaInt_AssetLoadPlaintext(const PsaAssetId_t TargetAssetId,
                          const uint8_t * Data_p,
                          const size_t DataSize);

psa_status_t
psaInt_AssetLoadPlaintextExport(const PsaAssetId_t TargetAssetId,
                                const uint8_t * const Data_p,
                                const size_t DataSize,
                                const PsaAssetId_t KekAssetId,
                                uint8_t * const KeyBlob_p,
                                size_t * const KeyBlobSize_p);
psa_status_t
psaInt_AssetLoadImport(const PsaAssetId_t TargetAssetId,
                       const PsaAssetId_t KekAssetId,
                       const uint8_t * const KeyBlob_p,
                       const size_t KeyBlobSize);

psa_status_t
psaInt_AssetLoadRandom(const PsaAssetId_t TargetAssetId);

psa_status_t
psaInt_AssetLoadRandomExport(const PsaAssetId_t TargetAssetId,
                             const PsaAssetId_t KekAssetId,
                             uint8_t * const KeyBlob_p,
                             size_t * const KeyBlobSize_p);

psa_status_t
psaInt_AssetLoadDerive(const PsaAssetId_t TargetAssetId,
                       const PsaAssetId_t KdkAssetId,
                       const uint8_t * const AssociatedData_p,
                       const size_t AssociatedDataSize,
                       const bool fCounter,
                       const bool fRFC5869,
                       const uint8_t * const Salt_p,
                       const size_t SaltSize,
                       const uint8_t * const IV_p,
                       const size_t IVSize,
                       const uint8_t AssetNumber);

psa_status_t
psaInt_AssetSearch(const uint16_t StaticAssetNumber,
                   PsaAssetId_t * const AssetId_p,
                   size_t * const AssetSize_p);

psa_status_t
psaInt_AssetGetKeyBlobKEK(PsaAssetId_t * const KekAssetId);

void
psaInt_AssetGetKeyBlobLabel(uint8_t *pData,
                            uint32_t * pDataSize);

psa_status_t
psaInt_AsymEccInstallCurve(const uint8_t CurveFamily,
                           const size_t CurveBits,
                           PsaAssetId_t * const AssetId_p);

/*-----------------------------------------------------------------------------
 * psaInt_PublicDataRead
 */
/**
 * This function reads the Public Data.
 *
 * @param [in] AssetId
 *     The Asset Id of the Public Data to read.
 *
 * @param [out] Data_p
 *     The pointer to the data buffer in which the Public Data must be
 *     returned.
 *
 * @param [in] DataSize
 *     The size of the data buffer.
 *
 * @param [in] output_length
 *     The actual used length of the output data buffer.
 *
 * @return One of the psa_status_t values.
 */
psa_status_t
psaInt_PublicDataRead(const PsaAssetId_t AssetId,
                      uint8_t * const Data_p,
                      const size_t DataSize,
                      size_t * output_length);

#endif /* INCLUDE_GUARD_ADAPTER_PSA_ASSET_H */

/* end of file adapter_psa_asset.h */
