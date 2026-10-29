/* adapter_psa_asym_signature.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the Asymmetric crypto signature services.
 */

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

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/c_adapter_psa.h>              // configuration
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>                 // the API to implement
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>                // VexTokenCmd_*_t, VexTokenRslt_*_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>
#include <third_party/hsmddk/include/Kit/EIP130/DomainHelper/incl/eip130_domain_ecc_curves.h>   // EIP130DOMAIN_ECC_FAMILY_*


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Maximum message size when a hash is performed in an asymmetric crypto operation. */
#define PSA_ASYM_CMD_MAX_HASH_SIZE 4095U

/* for RSA operations for the maximum allowed modulus length in bits */
#define PSA_ASYM_RSA_VERIFY_MAX_BITS  4096U    /* Public key related modulus limit */


/*----------------------------------------------------------------------------
 * local_AsymRsaSignatureFromHW
 */
static void
local_AsymRsaSignatureFromHW(const uint8_t * const Blob_p,
                             const size_t ModulusSizeBits,
                             uint8_t * Signature_p)
{
    uint32_t Size = (uint32_t)PSA_BITS_TO_BYTES(ModulusSizeBits);

    /* Convert big integer from HW to application format */
    psaInt_ReverseMemCpy(Signature_p, &Blob_p[PSA_ASYM_DATA_VHEADER], Size);
}


/*----------------------------------------------------------------------------
 * local_AsymRsaSignatureToHW
 */
static void
local_AsymRsaSignatureToHW(const uint8_t * const data_p,
                           const size_t ModulusSizeBits,
                           const uint8_t BeginItem,
                           const uint8_t Items,
                           uint8_t * Blob_p)
{
    uint8_t * ptr = Blob_p;
    uint32_t RemainingLength = PSA_ASYM_DATA_SIZE_B2WB((uint32_t)ModulusSizeBits);
    uint32_t CopySize = (uint32_t)PSA_BITS_TO_BYTES(ModulusSizeBits);

    /* Convert big integer from application to HW format */
    /* - Initialize header */
    *ptr = (uint8_t)(ModulusSizeBits);
    ptr++;
    *ptr = (uint8_t)(ModulusSizeBits >> 8);
    ptr++;
    *ptr = (uint8_t)(BeginItem);
    ptr++;
    *ptr = (uint8_t)(Items);
    ptr++;
    /* - Copy data reversed */
    if (CopySize > RemainingLength)
    {
        /* Prevent buffer overrun */
        LOG_WARN("Warning: Truncated BigInt data to HW conversion (%u > %u)\n",
                 CopySize, RemainingLength);
        CopySize = RemainingLength;
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    psaInt_ReverseMemCpy(ptr, data_p, CopySize);
    /* - Zeroize remaining part if needed */
    RemainingLength -= CopySize;
    if (RemainingLength != 0U)
    {
        (void)memset(&ptr[CopySize], 0, RemainingLength);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
}


/*----------------------------------------------------------------------------
 * local_AsymDsaSignatureFromHW
 */
static void
local_AsymDsaSignatureFromHW(const uint8_t * const Blob_p,
                             const size_t ModulusSizeBits,
                             uint8_t * Signature_p)
{
    /* Convert Signature from HW to application format */
    local_AsymRsaSignatureFromHW(Blob_p,
                                 ModulusSizeBits, Signature_p);
    local_AsymRsaSignatureFromHW(&Blob_p[PSA_ASYM_DATA_VHEADER +
                                         PSA_ASYM_DATA_SIZE_B2WB(ModulusSizeBits)],
                                 ModulusSizeBits,
                                 &Signature_p[PSA_BITS_TO_BYTES(ModulusSizeBits)]);
}


/*----------------------------------------------------------------------------
 * local_AsymDsaSignatureToHW
 */
static void
local_AsymDsaSignatureToHW(const uint8_t * const Signature_p,
                           const size_t ModulusSizeBits,
                           uint8_t * const Blob_p)
{
    /* Convert Signature from application to HW format */
    /* - Signature.r */
    local_AsymRsaSignatureToHW(Signature_p, ModulusSizeBits, 0, 2, Blob_p);
    /* - Signature.s */
    local_AsymRsaSignatureToHW(&Signature_p[PSA_BITS_TO_BYTES(ModulusSizeBits)],
                               ModulusSizeBits, 1, 2,
                               &Blob_p[PSA_ASYM_DATA_SIZE_VWB(ModulusSizeBits)]);
}


/*----------------------------------------------------------------------------
 * local_AsymEddsaGenPublicKey
 */
static psa_status_t
local_AsymEddsaGenPublicKey(PsaAssetId_t PrviKeyAssetId,
                            PsaAssetId_t DomainAssetId,
                            PsaAssetId_t PubKeyAssetId,
                            uint32_t ModulusSizeBits)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_PkAssetGenKey_t t_cmd;
    VexTokenRslt_Generic_t t_res;

    /* Format service request */
    t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_PUBLIC_KEY;
    t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_PK_WITHASSETS;
    t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_EDDSA_GEN_PUBKEY;
    t_cmd.ModulusSizeInBits = (uint32_t)ModulusSizeBits;
    t_cmd.DivisorSizeInBits = (uint32_t)ModulusSizeBits;
    t_cmd.PubKeyAssetId = PubKeyAssetId;
    t_cmd.PrivKeyAssetId = PrviKeyAssetId;
    t_cmd.DomainAssetId = DomainAssetId;
    t_cmd.PubKey_p = NULL;
    t_cmd.PubKeySize = 0U;
    t_cmd.KekAssetId = PSA_ASSETID_INVALID;
    t_cmd.AssociatedDataSize = 0U;
    t_cmd.KeyBlob_p = NULL;
    t_cmd.KeyBlobSize = 0U;
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
        /* MISRA - Intentially empty */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_AsymHashUpdate
 */
static psa_status_t
local_AsymHashUpdate(psa_algorithm_t alg,
                     PsaAssetId_t TempAssetId,
                     const uint8_t * Data_p,
                     size_t DataSize,
                     uint8_t fInitDone)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_Hash_t t_cmd;
    VexTokenRslt_Hash_t t_res;
    uint32_t BlockSize = PSA_HASH_BLOCK_LENGTH(alg);

    if (((DataSize & (BlockSize - 1U)) != 0U) ||
        (DataSize > (MAX_DMA_SIZE - (BlockSize - 1U))))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        switch (alg)
        {
        case PSA_ALG_SHA_1:
            t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_HASH_SHA1;
            break;
        case PSA_ALG_SHA_224:
            t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_HASH_SHA224;
            break;
        case PSA_ALG_SHA_256:
            t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_HASH_SHA256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case PSA_ALG_SHA_384:
            t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_HASH_SHA384;
            break;
        case PSA_ALG_SHA_512:
            t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_HASH_SHA512;
            break;
#endif
        default:
            funcres = PSA_ERROR_INVALID_ARGUMENT;
            break;
        }
    }

    if (PSA_SUCCESS == funcres)
    {
        /* Format service request */
        t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_HASH;
        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_NOT_USED;
        if (0U == fInitDone)
        {
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2CONT;
        }
        else
        {
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_CONT2CONT;
        }
        t_cmd.Data_p = (const uint8_t *)Data_p;
        t_cmd.DataSize = (uint32_t)DataSize;
        t_cmd.TempAssetId = TempAssetId;
        t_cmd.TotalMessageLengthLo = 0U;
        t_cmd.TotalMessageLengthHi = 0U;

        (void)memset(&t_res, 0, sizeof(t_res));

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
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_AsymDoEddsa
 *
 * Do EDDSA sign or verify.
 */
static psa_status_t
local_AsymDoEddsa(psa_key_context_t *pKey,
                 const uint8_t * input,
                 size_t input_length,
                 uint8_t * signature,
                 size_t * signature_length,
                 uint8_t fverify)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_PkAssetSignVerify_t t_cmd;
    VexTokenRslt_PkAssetSignVerify_t t_res;
    PsaAssetId_t PubKeyAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t StateAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t TempAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t DomainAssetId = PSA_ASSETID_INVALID;
    PsaPolicyMask_t PubKeyAssetPolicy;
    PsaPolicyMask_t TempAssetPolicy;
    size_t HashDataSize = 0U;
    uint8_t SigData[2U * (PSA_ASYM_DATA_VHEADER + (4U * ((255U + 31U) / 32U)))];
    uint32_t SigDataSize = 0U;

    if (PSA_ECC_FAMILY_TWISTED_EDWARDS !=
        PSA_KEY_TYPE_ECC_GET_FAMILY(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        funcres = psaInt_AsymEccInstallCurve(EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS,
                                             pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(bits),
                                             &DomainAssetId);
        if (PSA_SUCCESS == funcres)
        {
            TempAssetPolicy = EIP130_ASSET_POLICY_SYM_TEMP |
                              EIP130_ASSET_POLICY_SCUIHASH |
                              EIP130_ASSET_POLICY_SCDIRENCGEN |
                              EIP130_ASSET_POLICY_SCAHSHA512;

            PubKeyAssetPolicy = (pKey->AssetPolicy & ~EIP130_ASSET_POLICY_PRIVATEDATA) |
                                 EIP130_ASSET_POLICY_PUBLICDATA;
#ifdef EIP130_ENABLE_DPA_SUPPORT
            PubKeyAssetPolicy = PubKeyAssetPolicy & ~EIP130_ASSET_POLICY_AC_NDPA;
#endif
            if (!psaInt_IsAccessSecure())
            {
                TempAssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
                PubKeyAssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            funcres = psaInt_AssetAlloc(TempAssetPolicy,
                                        (512U / 8U),
                                        &TempAssetId);
            if ((0U == fverify) && (PSA_SUCCESS == funcres))
            {
                funcres = psaInt_AssetAlloc(PubKeyAssetPolicy,
                                            PSA_ASYM_DATA_SIZE_VWB(255U),
                                            &PubKeyAssetId);
                if (PSA_SUCCESS == funcres)
                {
                    funcres = local_AsymEddsaGenPublicKey(pKey->key_assetId,
                                                          DomainAssetId,
                                                          PubKeyAssetId,
                                                          pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(bits));
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
            if (PSA_SUCCESS == funcres)
            {
                SigDataSize = (2U * PSA_ASYM_DATA_SIZE_VWB(pKey->modulus_size));
                if (0U == fverify)
                {
                    if (96U < input_length)
                    {
                        HashDataSize = 96U;
                    }
                    else
                    {
                        HashDataSize = input_length;
                    }
                }
                else
                {
                    if (64U < input_length)
                    {
                        HashDataSize = 64U;
                    }
                    else
                    {
                        HashDataSize = input_length;
                    }

                    /* Convert the signature from application to HW format */
                    local_AsymDsaSignatureToHW(signature, pKey->modulus_size,
                                               SigData);
                }

                /* Format Initial service request */
                t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_PUBLIC_KEY;
                t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_PK_WITHASSETS;
                if (0U == fverify)
                {
                    t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_EDDSA_SIGN_INITIAL;
                    t_cmd.Sign_p = NULL;
                    t_cmd.SignSize = 0U;
                }
                else
                {
                    t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_EDDSA_VERIFY_INITIAL;
                    t_cmd.Sign_p = SigData;
                    t_cmd.SignSize = SigDataSize;
                }
                t_cmd.ModulusSizeInBits = (uint32_t)pKey->modulus_size;
                t_cmd.KeyAssetId = pKey->key_assetId;
                t_cmd.DomainAssetId = DomainAssetId;
                t_cmd.DigestAssetId = TempAssetId;
                t_cmd.HashData_p = input;
                t_cmd.HashDataSize = (uint32_t)HashDataSize;
                t_cmd.TotalMessageSizeLo = 0U;
                t_cmd.TotalMessageSizeLo = 0U;
                t_cmd.ExplicitDigestSize = 0U;
                t_cmd.SaltSize = 0U;
                t_res.Result = 0;
                t_res.StateAssetId = PSA_ASSETID_INVALID;

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
                    /* MISRA - Intentially empty */
                }
                if (PSA_SUCCESS == funcres)
                {
                    const uint8_t * ptr;
                    uint64_t TotalMessageLength = (uint64_t)input_length;

                    StateAssetId = (PsaAssetId_t)t_res.StateAssetId;

                    if (0U == fverify)
                    {
                        /* Hash the middle section of the message if needed */
                        if (96U < input_length)
                        {
                            ptr = &input[96];
                            HashDataSize = input_length - 96U;
                        }
                        else
                        {
                            ptr = input;
                            HashDataSize = input_length;
                        }
                        while(PSA_ASYM_CMD_MAX_HASH_SIZE < HashDataSize)
                        {
                            /* Hash a block of data */
                            size_t Size = HashDataSize - (2U * 128U);
                            if (MAX_DMA_SIZE < HashDataSize)
                            {
                                /* Limit the size to the maximum DMAable size */
                                Size = MAX_DMA_SIZE - (4U * 128U);
                            }
                            else
                            {
                                /* MISRA - Intentially empty */
                            }
                            Size = (size_t)(Size & (~(128U - 1U)));
                            funcres = local_AsymHashUpdate(PSA_ALG_SHA_512, TempAssetId, ptr, Size, 255U);
                            if (PSA_SUCCESS != funcres)
                            {
                                break;
                            }
                            else
                            {
                                /* Adjust references */
                                ptr = &ptr[Size];
                                HashDataSize -= Size;
                            }
                        }
                        if (PSA_SUCCESS == funcres)
                        {
                            /* Format SIGN-Update service request */
                            t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_EDDSA_SIGN_UPDATE;
                            t_cmd.DomainAssetId = PSA_ASSETID_INVALID;
                            t_cmd.KeyAssetId = PubKeyAssetId;
                            t_cmd.DigestAssetId = StateAssetId;
                            t_cmd.HashData_p = ptr;
                            t_cmd.HashDataSize = (uint32_t)HashDataSize;
                            t_cmd.TotalMessageSizeLo = (uint32_t)(TotalMessageLength);
                            t_cmd.TotalMessageSizeHi = (uint32_t)(TotalMessageLength >> 32);
                            t_cmd.ExplicitDigestSize = 0U;
                            t_res.Result = 0;

                            /* Exchange service request with the next driver level */
                            funcres = psaInt_ExchangeToken((VexTokenCmd_Generic_t *)&t_cmd,
                                                           sizeof(t_cmd),
                                                           (VexTokenRslt_Generic_t *)&t_res,
                                                           sizeof(t_res));
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
                        const uint8_t * ptr;
                        uint64_t TotalMessageLength = (uint64_t)input_length;

                        if (64U < input_length)
                        {
                            HashDataSize = input_length - 64U;
                            ptr = &input[64];
                        }
                        else
                        {
                            HashDataSize = input_length;
                            ptr = input;
                        }
                        while(PSA_ASYM_CMD_MAX_HASH_SIZE < HashDataSize)
                        {
                            /* Hash a block of data */
                            size_t Size = HashDataSize - (2U * 128U);
                            if (MAX_DMA_SIZE < HashDataSize)
                            {
                                /* Limit the size to the maximum DMAable size */
                                Size = MAX_DMA_SIZE - (4U * 128U);
                            }
                            else
                            {
                                /* MISRA - Intentially empty */
                            }
                            Size = (size_t)(Size & (~(128U - 1U)));
                            funcres = local_AsymHashUpdate(PSA_ALG_SHA_512, TempAssetId, ptr, Size, 255U);
                            if (PSA_SUCCESS != funcres)
                            {
                                break;
                            }
                            else
                            {
                                /* Adjust references */
                                ptr = &ptr[Size];
                                HashDataSize -= Size;
                            }
                        }
                        if (PSA_SUCCESS == funcres)
                        {
                            /* Format Final service request */
                            if (0U == fverify)
                            {
                                t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_EDDSA_SIGN_FINAL;
                                t_cmd.Sign_p = SigData;
                                t_cmd.SignSize = SigDataSize;
                            }
                            else
                            {
                                t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_EDDSA_VERIFY_FINAL;
                                t_cmd.DomainAssetId = PSA_ASSETID_INVALID;
                                t_cmd.DigestAssetId = StateAssetId;
                                t_cmd.TotalMessageSizeLo = (uint32_t)(TotalMessageLength);
                                t_cmd.TotalMessageSizeHi = (uint32_t)(TotalMessageLength >> 32);
                                t_cmd.ExplicitDigestSize = 0U;
                                t_cmd.Sign_p = NULL;
                                t_cmd.SignSize = 0U;
                            }
                            t_cmd.KeyAssetId = PSA_ASSETID_INVALID;
                            t_cmd.HashData_p = ptr;
                            t_cmd.HashDataSize = (uint32_t)HashDataSize;
                            t_res.Result = 0;

                            /* Exchange service request with the next driver level */
                            funcres = psaInt_ExchangeToken((VexTokenCmd_Generic_t *)&t_cmd,
                                                           sizeof(t_cmd),
                                                           (VexTokenRslt_Generic_t *)&t_res,
                                                           sizeof(t_res));
                        }
                        else
                        {
                            /* MISRA - Intentially empty */
                        }
                    }

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
                            /* State asset is deleted */
                            StateAssetId = PSA_ASSETID_INVALID;
                            if (0U == fverify)
                            {
                                local_AsymDsaSignatureFromHW(SigData,
                                                            pKey->modulus_size,
                                                            signature);
                                *signature_length = (size_t)(2U * PSA_BITS_TO_BYTES(pKey->modulus_size));
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
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    /* Cleanup used Assets */
    if (PSA_ASSETID_INVALID != PubKeyAssetId)
    {
        (void)psaInt_AssetFree(PubKeyAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != StateAssetId)
    {
        (void)psaInt_AssetFree(StateAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != TempAssetId)
    {
        (void)psaInt_AssetFree(TempAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != DomainAssetId)
    {
        (void)psaInt_AssetFree(DomainAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * local_AsymDoSignVerify
 *
 * Do sign or verify.
 */
static psa_status_t
local_AsymDoSignVerify(psa_algorithm_t alg,
                       const psa_key_context_t * pKey,
                       const uint8_t * input,
                       size_t input_length,
                       uint8_t * signature,
                       size_t * signature_length,
                       uint8_t fverify,
                       uint8_t fExplicitDigest)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_PkAssetSignVerify_t t_cmd;
    VexTokenRslt_PkAssetSignVerify_t t_res;
    PsaAssetId_t DomainAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t TempAssetId = PSA_ASSETID_INVALID;
    size_t HashDataSize = input_length;
    uint64_t TotalMessageLength = (uint64_t)input_length;
    uint32_t SigDataSize = 0U;
    uint8_t SigData[PSA_ASYM_DATA_VHEADER +
                    (4U * ((PSA_ASYM_RSA_VERIFY_MAX_BITS + 31U) / 32U))];

    if (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg))
    {
        if (0U == fverify)
        {
            t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_RSA_PKCS1V1_5_SIGN;
        }
        else
        {
            t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_RSA_PKCS1V1_5_VERIFY;
        }
        t_cmd.SaltSize = 0U;
        SigDataSize = PSA_ASYM_DATA_SIZE_VWB(pKey->modulus_size);
    }
    else if ((PSA_ALG_IS_RSA_PSS_STANDARD_SALT(alg)) ||
             (PSA_ALG_IS_RSA_PSS_ANY_SALT(alg)))
    {
         switch (PSA_ALG_GET_HASH(alg))
         {
         case PSA_ALG_SHA_1:
             t_cmd.SaltSize = (160U / 8U);
             break;
         case PSA_ALG_SHA_224:
             t_cmd.SaltSize = (224U / 8U);
             break;
         case PSA_ALG_SHA_256:
             t_cmd.SaltSize = (256U / 8U);
             break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
         case PSA_ALG_SHA_384:
             t_cmd.SaltSize = (384U / 8U);
             break;
         case PSA_ALG_SHA_512:
             t_cmd.SaltSize = (512U / 8U);
             break;
#endif
         default:
            funcres = PSA_ERROR_INVALID_ARGUMENT;
            break;
         }
         if (0U == fverify)
         {
             t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_RSA_PSS_SIGN;
         }
         else
         {
             t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_RSA_PSS_VERIFY;
         }
         SigDataSize = PSA_ASYM_DATA_SIZE_VWB((uint32_t)pKey->modulus_size);
    }
    else if (PSA_ALG_IS_ECDSA(alg))
    {
        uint8_t CurveFamily = EIP130DOMAIN_ECC_FAMILY_NONE;

        if (PSA_ECC_FAMILY_SECP_R1 ==
            PSA_KEY_TYPE_ECC_GET_FAMILY(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type)))
        {
            CurveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        }
        else if (PSA_ECC_FAMILY_BRAINPOOL_P_R1 ==
                 PSA_KEY_TYPE_ECC_GET_FAMILY(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type)))
        {
            CurveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        if (EIP130DOMAIN_ECC_FAMILY_NONE != CurveFamily)
        {
            funcres = psaInt_AsymEccInstallCurve(CurveFamily,
                                                 pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(bits),
                                                 &DomainAssetId);
            if (0U == fverify)
            {
                t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_ECDSA_SIGN;
            }
            else
            {
                t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_ECDSA_VERIFY;
            }
            t_cmd.SaltSize = 0U;
            SigDataSize = (2U * PSA_ASYM_DATA_SIZE_VWB(pKey->modulus_size));
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
        const uint8_t * ptr = input;

        if (0U != fExplicitDigest)
        {
            if ((512U / 8U) < HashDataSize)
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
        else if (PSA_ASYM_CMD_MAX_HASH_SIZE < HashDataSize)
        {
            size_t HashTempSize = 0U;
            PsaPolicyMask_t TempAssetPolicy = EIP130_ASSET_POLICY_SYM_TEMP |
                                              EIP130_ASSET_POLICY_SCUIHASH |
                                              EIP130_ASSET_POLICY_SCDIRENCGEN;
            if (!psaInt_IsAccessSecure())
            {
                TempAssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            switch (PSA_ALG_GET_HASH(alg))
            {
            case PSA_ALG_SHA_1:
                TempAssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA1;
                HashTempSize = (160U / 8U);
                break;
            case PSA_ALG_SHA_224:
                TempAssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA224;
                HashTempSize = (256U / 8U);
                break;
            case PSA_ALG_SHA_256:
                TempAssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA256;
                HashTempSize = (256U / 8U);
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case PSA_ALG_SHA_384:
                TempAssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA384;
                HashTempSize = (512U / 8U);
                break;
            case PSA_ALG_SHA_512:
                TempAssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA512;
                HashTempSize = (512U / 8U);
                break;
#endif
            default:
                funcres = PSA_ERROR_INVALID_ARGUMENT;
                break;
            }
            if (PSA_SUCCESS == funcres)
            {
                funcres = psaInt_AssetAlloc(TempAssetPolicy,
                                            HashTempSize,
                                            &TempAssetId);
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            if (PSA_SUCCESS == funcres)
            {
                uint8_t fInitDone = 0U;
                while(PSA_ASYM_CMD_MAX_HASH_SIZE < HashDataSize)
                {
                    /* Hash a block of data */
                    size_t Size = HashDataSize - (2U * 128U);
                    if (MAX_DMA_SIZE < HashDataSize)
                    {
                        /* Limit the size to the maximum DMAable size */
                        Size = MAX_DMA_SIZE - (4U * 128U);
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                    Size = (size_t)(Size & (~(128U - 1U)));
                    funcres = local_AsymHashUpdate(PSA_ALG_GET_HASH(alg), TempAssetId, ptr, Size, fInitDone);
                    if (PSA_SUCCESS != funcres)
                    {
                        break;
                    }
                    else
                    {
                        fInitDone = 255U;
                        /* Adjust references */
                        ptr = &ptr[Size];
                        HashDataSize -= Size;
                    }
                }
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
        if (PSA_SUCCESS == funcres)
        {
            if (0U != fverify)
            {
                if (PSA_ALG_IS_ECDSA(alg))
                {
                    local_AsymDsaSignatureToHW(signature, pKey->modulus_size,
                                               SigData);
                }
                else
                {
                    local_AsymRsaSignatureToHW(signature, pKey->modulus_size,
                                               0, 1, SigData);
                }
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_PUBLIC_KEY;
            t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_PK_WITHASSETS;
            t_cmd.ModulusSizeInBits = (uint32_t)pKey->modulus_size;
            t_cmd.Sign_p = SigData;
            t_cmd.SignSize = SigDataSize;
            t_cmd.KeyAssetId = pKey->key_assetId;
            t_cmd.DomainAssetId = DomainAssetId;
            if (0U != fExplicitDigest)
            {
                t_cmd.ExplicitDigestSize = (uint32_t)input_length;
                (void)memcpy(t_cmd.ExplicitDigest, input, input_length);
                t_cmd.DigestAssetId = PSA_ASSETID_INVALID;
                t_cmd.HashData_p = NULL;
                t_cmd.HashDataSize = 0U;
                t_cmd.TotalMessageSizeLo = 0U;
                t_cmd.TotalMessageSizeHi = 0U;
            }
            else
            {
                t_cmd.ExplicitDigestSize = 0U;
                t_cmd.DigestAssetId = TempAssetId;
                t_cmd.HashData_p = ptr;
                t_cmd.HashDataSize = (uint32_t)HashDataSize;
                t_cmd.TotalMessageSizeLo = (uint32_t)(TotalMessageLength);
                t_cmd.TotalMessageSizeHi = (uint32_t)(TotalMessageLength >> 32);
            }
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
                    if (0U == fverify)
                    {
                        /* Convert the signature from HW to application format */
                        if (PSA_ALG_IS_ECDSA(alg))
                        {
                            local_AsymDsaSignatureFromHW(SigData,
                                                         pKey->modulus_size,
                                                         signature);
                            *signature_length = (size_t)(2U * PSA_BITS_TO_BYTES(pKey->modulus_size));
                        }
                        else
                        {
                            local_AsymRsaSignatureFromHW(SigData,
                                                         pKey->modulus_size,
                                                         signature);
                            *signature_length = (size_t)PSA_BITS_TO_BYTES(pKey->modulus_size);
                        }
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

    /* Cleanup used Assets */
    if (PSA_ASSETID_INVALID != TempAssetId)
    {
        (void)psaInt_AssetFree(TempAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != DomainAssetId)
    {
        (void)psaInt_AssetFree(DomainAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_sign_message
 *
 * Do hash and sign operation
 */
psa_status_t
psa_sign_message(mbedtls_svc_key_id_t key,
                 psa_algorithm_t alg,
                 const uint8_t * input,
                 size_t input_length,
                 uint8_t * signature,
                 size_t signature_size,
                 size_t * signature_length)
{
    psa_key_context_t *pKey = NULL;
    PsaAssetId_t KeyAssetId = PSA_ASSETID_INVALID;
    psa_status_t funcres = PSA_SUCCESS;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_SIGN_MESSAGE != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_SIGN_MESSAGE))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (signature_size < PSA_SIGN_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type),
                                                   pKey->modulus_size, alg))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if (!PSA_ALG_IS_SIGN_MESSAGE(alg) ||
             (NULL == input) ||
             (0U == input_length) ||
             (NULL == signature) ||
             (NULL == signature_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        funcres = psaInt_KeyMgmtLoadKey(pKey, &KeyAssetId, 0, 0, NULL, 0, NULL);
        if (PSA_SUCCESS == funcres)
        {
            if (PSA_ALG_PURE_EDDSA == alg)
            {
                funcres = local_AsymDoEddsa(pKey, input, input_length,
                                            signature, signature_length, 0U);
            }
            else
            {
                funcres = local_AsymDoSignVerify(alg, pKey,
                                                 input, input_length,
                                                 signature, signature_length,
                                                 0U, 0U);
            }

            (void)psaInt_KeyMgmtReleaseKey(pKey);
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_verify_message
 *
 * Do hash and verify operation.
 */
psa_status_t
psa_verify_message(mbedtls_svc_key_id_t key,
                   psa_algorithm_t alg,
                   const uint8_t * input,
                   size_t input_length,
                   const uint8_t * signature,
                   size_t signature_length)
{
    psa_key_context_t *pKey = NULL;
    PsaAssetId_t KeyAssetId = PSA_ASSETID_INVALID;
    psa_status_t funcres = PSA_SUCCESS;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_VERIFY_MESSAGE != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_VERIFY_MESSAGE))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (!PSA_ALG_IS_SIGN_MESSAGE(alg) ||
             (NULL == input) ||
             (0U == input_length) ||
             (NULL == signature) ||
             (0U == signature_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        funcres = psaInt_KeyMgmtLoadKey(pKey, &KeyAssetId, 0, 0, NULL, 0, NULL);
        if (PSA_SUCCESS == funcres)
        {
            uint8_t * sign = psaInt_discard_const(signature);
            if (PSA_ALG_PURE_EDDSA == alg)
            {
                funcres = local_AsymDoEddsa(pKey, input, input_length, sign,
                                            NULL, 255U);
            }
            else
            {
                funcres = local_AsymDoSignVerify(alg, pKey,
                                                 input, input_length,
                                                 sign, NULL, 255U, 0U);
            }

            (void)psaInt_KeyMgmtReleaseKey(pKey);
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_sign_hash
 *
 * do sign operation with explicit digest.
 */
psa_status_t
psa_sign_hash(mbedtls_svc_key_id_t key,
              psa_algorithm_t alg,
              const uint8_t * hash,
              size_t hash_length,
              uint8_t * signature,
              size_t signature_size,
              size_t * signature_length)
{
    psa_key_context_t *pKey = NULL;
    PsaAssetId_t KeyAssetId = PSA_ASSETID_INVALID;
    psa_status_t funcres = PSA_SUCCESS;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_SIGN_HASH != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_SIGN_HASH))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (signature_size < PSA_SIGN_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type),
                                                   pKey->modulus_size,
                                                   alg))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if (!PSA_ALG_IS_SIGN_HASH(alg) ||
             (NULL == hash) ||
             (NULL == signature) ||
             (NULL == signature_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (((160U / 8U) != hash_length) &&
             ((224U / 8U) != hash_length) &&
             ((256U / 8U) != hash_length) &&
             ((384U / 8U) != hash_length) &&
             ((512U / 8U) != hash_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_ALG_IS_HASH_EDDSA(alg))
    {
        funcres = PSA_ERROR_NOT_SUPPORTED;
    }
    else
    {
        funcres = psaInt_KeyMgmtLoadKey(pKey, &KeyAssetId, 0, 0, NULL, 0, NULL);
        if (PSA_SUCCESS == funcres)
        {
            funcres = local_AsymDoSignVerify(alg, pKey, hash, hash_length,
                                             signature, signature_length,
                                             0U, 255U);

            (void)psaInt_KeyMgmtReleaseKey(pKey);
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_verify_hash
 *
 * do verify operation with explicit digest.
 */
psa_status_t
psa_verify_hash(mbedtls_svc_key_id_t key,
                psa_algorithm_t alg,
                const uint8_t * hash,
                size_t hash_length,
                const uint8_t * signature,
                size_t signature_length)
{
    psa_key_context_t *pKey = NULL;
    PsaAssetId_t KeyAssetId = PSA_ASSETID_INVALID;
    psa_status_t funcres = PSA_SUCCESS;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_VERIFY_HASH != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_VERIFY_HASH))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (!PSA_ALG_IS_SIGN_HASH(alg) ||
             (NULL == hash) ||
             (NULL == signature) ||
             (0U == signature_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (((160U / 8U) != hash_length) &&
             ((224U / 8U) != hash_length) &&
             ((256U / 8U) != hash_length) &&
             ((384U / 8U) != hash_length) &&
             ((512U / 8U) != hash_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_ALG_IS_HASH_EDDSA(alg))
    {
        funcres = PSA_ERROR_NOT_SUPPORTED;
    }
    else
    {
        funcres = psaInt_KeyMgmtLoadKey(pKey, &KeyAssetId, 0, 0, NULL, 0, NULL);
        if (PSA_SUCCESS == funcres)
        {
            uint8_t * sign = psaInt_discard_const(signature);
            funcres = local_AsymDoSignVerify(alg, pKey, hash, hash_length,
                                             sign, NULL, 255U, 255U);

            (void)psaInt_KeyMgmtReleaseKey(pKey);
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/* end of file adapter_psa_asym_signature.c */
