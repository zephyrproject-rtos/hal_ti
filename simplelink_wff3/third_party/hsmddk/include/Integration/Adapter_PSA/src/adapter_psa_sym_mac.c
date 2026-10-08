/* adapter_val_sym_mac.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the symmetric crypto mac services.
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
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                       // size_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>                 // the API to implement
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/internal_trusted_storage.h> // PSA storage API reference
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>                // VexTokenCmd_*_t, VexTokenRslt_*_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>
#include <third_party/hsmddk/include/Config/cs_mbedtls.h>

/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#define PSA_MAC_STATE_INIT      0U
#define PSA_MAC_STATE_SETUP     1U
#define PSA_MAC_STATE_UPDATE    2U

#define PSA_SYM_ALGO_HMAC_SHA3_224_BLOCK_SIZE   (1152U/8U)
#define PSA_SYM_ALGO_HMAC_SHA3_256_BLOCK_SIZE   (1088U/8U)
#define PSA_SYM_ALGO_HMAC_SHA3_384_BLOCK_SIZE   (832U/8U)
#define PSA_SYM_ALGO_HMAC_SHA3_512_BLOCK_SIZE   (576U/8U)

#define PSA_SYM_ALGO_HMAC_SHA1_DIGEST_SIZE      (160U/8U)
#define PSA_SYM_ALGO_HMAC_SHA2_224_DIGEST_SIZE  (224U/8U)
#define PSA_SYM_ALGO_HMAC_SHA2_256_DIGEST_SIZE  (256U/8U)
#define PSA_SYM_ALGO_HMAC_SHA2_384_DIGEST_SIZE  (384U/8U)
#define PSA_SYM_ALGO_HMAC_SHA2_512_DIGEST_SIZE  (512U/8U)
#define PSA_SYM_ALGO_HMAC_SHA3_224_DIGEST_SIZE  (224U/8U)
#define PSA_SYM_ALGO_HMAC_SHA3_256_DIGEST_SIZE  (256U/8U)
#define PSA_SYM_ALGO_HMAC_SHA3_384_DIGEST_SIZE  (384U/8U)
#define PSA_SYM_ALGO_HMAC_SHA3_512_DIGEST_SIZE  (512U/8U)
#define PSA_SYM_ALGO_HMAC_SM3_DIGEST_SIZE       (256U/8U)
#define PSA_SYM_ALGO_MAC_AES_DIGEST_SIZE        (128U/8U)
#define PSA_SYM_ALGO_MAC_ARIA_DIGEST_SIZE       (128U/8U)
#define PSA_SYM_ALGO_MAC_POLY1305_DIGEST_SIZE   (128U/8U)

#define PSA_SYM_ALGO_HMAC_SHA1_STATE_SIZE       (160U/8U)
#define PSA_SYM_ALGO_HMAC_SHA2_224_STATE_SIZE   (256U/8U)
#define PSA_SYM_ALGO_HMAC_SHA2_384_STATE_SIZE   (512U/8U)
#define PSA_SYM_ALGO_HMAC_SHA3_STATE_SIZE       (1600U/8U)


/*----------------------------------------------------------------------------
 * get_mac_asset_policy
 */
static PsaPolicyMask_t
get_mac_asset_policy(uint32_t alg,
                     uint8_t fVerify)
{
    PsaPolicyMask_t AssetPolicy = 0U;

    if (fVerify != 0U)
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
    }
    else
    {
        AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
    }
    switch (alg)
    {
    case VEXTOKEN_ALGO_MAC_HMAC_SHA1:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA1 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA224:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA224 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA256:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA256 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA384:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA384 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA512:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA512 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA3_224:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_224 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA3_256:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_256 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA3_384:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_384 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA3_512:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_512 |
                       EIP130_ASSET_POLICY_SYM_MACHASH;
        break;
    case VEXTOKEN_ALGO_MAC_AES_CMAC:
        AssetPolicy |= EIP130_ASSET_POLICY_SYM_MACCIPHER |
                       EIP130_ASSET_POLICY_SCACAES |
                       EIP130_ASSET_POLICY_SCMCMCMAC;
        break;
    case VEXTOKEN_ALGO_MAC_AES_CBC_MAC:
        AssetPolicy |= EIP130_ASSET_POLICY_SYM_MACCIPHER |
                       EIP130_ASSET_POLICY_SCACAES |
                       EIP130_ASSET_POLICY_SCMCMCBCMAC;
        break;
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
    case VEXTOKEN_ALGO_MAC_ARIA_CMAC:
        AssetPolicy |= EIP130_ASSET_POLICY_SYM_MACCIPHER |
                       EIP130_ASSET_POLICY_SCACARIA |
                       EIP130_ASSET_POLICY_SCMCMCMAC;
        break;
    case VEXTOKEN_ALGO_MAC_ARIA_CBC_MAC:
        AssetPolicy |= EIP130_ASSET_POLICY_SYM_MACCIPHER |
                       EIP130_ASSET_POLICY_SCACARIA |
                       EIP130_ASSET_POLICY_SCMCMCBCMAC;
        break;
#endif
    default:
        AssetPolicy = 0U;
        break;
    }

    return AssetPolicy;
}


/*----------------------------------------------------------------------------
 * get_mac_size
 */
static size_t
get_mac_size(uint32_t alg,
             bool fUpdate)
{
    size_t MacNBytes;

    switch (alg)
    {
    case VEXTOKEN_ALGO_MAC_HMAC_SHA1:
        MacNBytes = PSA_SYM_ALGO_HMAC_SHA1_DIGEST_SIZE;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA224:
        if (fUpdate)
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_224_STATE_SIZE;
        }
        else
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_224_DIGEST_SIZE;
        }
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA256:
        MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_256_DIGEST_SIZE;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA384:
        if (fUpdate)
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_384_STATE_SIZE;
        }
        else
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_384_DIGEST_SIZE;
        }
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA512:
        MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_512_DIGEST_SIZE;
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA3_224:
        if (fUpdate)
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_STATE_SIZE;
        }
        else
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_224_DIGEST_SIZE;
        }
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA3_256:
        if (fUpdate)
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_STATE_SIZE;
        }
        else
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_256_DIGEST_SIZE;
        }
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA3_384:
        if (fUpdate)
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_STATE_SIZE;
        }
        else
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_384_DIGEST_SIZE;
        }
        break;
    case VEXTOKEN_ALGO_MAC_HMAC_SHA3_512:
        if (fUpdate)
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_STATE_SIZE;
        }
        else
        {
            MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_512_DIGEST_SIZE;
        }
        break;
    case VEXTOKEN_ALGO_MAC_AES_CMAC:
    case VEXTOKEN_ALGO_MAC_AES_CBC_MAC:
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
    case VEXTOKEN_ALGO_MAC_ARIA_CMAC:
    case VEXTOKEN_ALGO_MAC_ARIA_CBC_MAC:
#endif
        MacNBytes =  PSA_SYM_ALGO_MAC_AES_DIGEST_SIZE;
        break;
    default:
        MacNBytes = 0U;
        break;
    }

    return MacNBytes;
}


/*----------------------------------------------------------------------------
 * get_mac_algorithm
 */
static uint32_t
get_mac_algorithm(uint32_t alg,
                  const psa_key_context_t * const pKey)
{
    uint32_t Algorithm;

    if (PSA_ALG_IS_HMAC(alg))
    {
        switch (PSA_ALG_HMAC_GET_HASH(alg))
        {
        case PSA_ALG_SHA_1:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA1;
            break;
        case PSA_ALG_SHA_224:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA224;
            break;
        case PSA_ALG_SHA_256:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case PSA_ALG_SHA_384:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA384;
            break;
        case PSA_ALG_SHA_512:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA512;
            break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case PSA_ALG_SHA3_224:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_224;
            break;
        case PSA_ALG_SHA3_256:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_256;
            break;
        case PSA_ALG_SHA3_384:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_384;
            break;
        case PSA_ALG_SHA3_512:
            Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_512;
            break;
#endif
        default:
            Algorithm = 0U;
            break;
        }
    }
    else if (PSA_ALG_IS_MAC(alg))
    {
        switch (alg)
        {
        case PSA_ALG_CMAC:
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                Algorithm = VEXTOKEN_ALGO_MAC_ARIA_CMAC;
            }
            else
#endif
            {
                Algorithm = VEXTOKEN_ALGO_MAC_AES_CMAC;
            }
            break;
        case PSA_ALG_CBC_MAC:
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                Algorithm = VEXTOKEN_ALGO_MAC_ARIA_CBC_MAC;
            }
            else
#endif
            {
                Algorithm = VEXTOKEN_ALGO_MAC_AES_CBC_MAC;
            }
            break;
        default:
            Algorithm = 0U;
            break;
        }
    }
    else
    {
        Algorithm = 0U;
    }

    return Algorithm;
}


/*----------------------------------------------------------------------------
 * psa_mac_compute
 */
psa_status_t
psa_mac_compute(mbedtls_svc_key_id_t key,
                psa_algorithm_t alg,
                const uint8_t * input,
                size_t input_length,
                uint8_t * mac,
                size_t mac_size,
                size_t * mac_length)
{
    psa_status_t funcres;
    VexTokenCmd_Mac_t t_cmd;
    VexTokenRslt_Mac_t t_res;
    psa_key_context_t *pKey = NULL;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_SIGN_MESSAGE != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_SIGN_MESSAGE))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (!(PSA_ALG_IS_HMAC(alg) || PSA_ALG_IS_MAC(alg)) ||
             (NULL == input) ||
             (0U == input_length) ||
             (NULL == mac) ||
             (0U == mac_size) ||
             (NULL == mac_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        uint64_t TotalMessageLength = (uint64_t)input_length;

        t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength);
        t_cmd.TotalMessageLengthHi = (uint32_t)(TotalMessageLength >> 32);
        if (PSA_ALG_IS_HMAC(alg))
        {
            switch (PSA_ALG_HMAC_GET_HASH(alg))
            {
            case PSA_ALG_SHA_1:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA1;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA1_DIGEST_SIZE;
                break;
            case PSA_ALG_SHA_224:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA224;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA2_224_DIGEST_SIZE;
                break;
            case PSA_ALG_SHA_256:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA256;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA2_256_DIGEST_SIZE;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case PSA_ALG_SHA_384:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA384;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA2_384_DIGEST_SIZE;
                break;
            case PSA_ALG_SHA_512:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA512;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA2_512_DIGEST_SIZE;
                break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
            case PSA_ALG_SHA3_224:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_224;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA3_224_DIGEST_SIZE;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength % PSA_SYM_ALGO_HMAC_SHA3_224_BLOCK_SIZE);
                t_cmd.TotalMessageLengthHi = 0U;
                if (0U == t_cmd.TotalMessageLengthLo)
                {
                    t_cmd.TotalMessageLengthLo = PSA_SYM_ALGO_HMAC_SHA3_224_BLOCK_SIZE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_256:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_256;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA3_256_DIGEST_SIZE;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength % PSA_SYM_ALGO_HMAC_SHA3_256_BLOCK_SIZE);
                t_cmd.TotalMessageLengthHi = 0U;
                if (0U == t_cmd.TotalMessageLengthLo)
                {
                    t_cmd.TotalMessageLengthLo = PSA_SYM_ALGO_HMAC_SHA3_256_BLOCK_SIZE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_384:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_384;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA3_384_DIGEST_SIZE;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength % PSA_SYM_ALGO_HMAC_SHA3_384_BLOCK_SIZE);
                t_cmd.TotalMessageLengthHi = 0U;
                if (0U == t_cmd.TotalMessageLengthLo)
                {
                    t_cmd.TotalMessageLengthLo = PSA_SYM_ALGO_HMAC_SHA3_384_BLOCK_SIZE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_512:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_512;
                *mac_length = PSA_SYM_ALGO_HMAC_SHA3_512_DIGEST_SIZE;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength % PSA_SYM_ALGO_HMAC_SHA3_512_BLOCK_SIZE);
                t_cmd.TotalMessageLengthHi = 0U;
                if (0U == t_cmd.TotalMessageLengthLo)
                {
                    t_cmd.TotalMessageLengthLo = PSA_SYM_ALGO_HMAC_SHA3_512_BLOCK_SIZE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
#endif
            default:
                funcres = PSA_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        else if (PSA_ALG_IS_MAC(alg))
        {
            switch(alg)
            {
            case PSA_ALG_CMAC:
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
                if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
                {
                    t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_ARIA_CMAC;
                }
                else
#endif
                {
                    t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_AES_CMAC;
                }
                *mac_length = PSA_SYM_ALGO_MAC_AES_DIGEST_SIZE;
                break;
            case PSA_ALG_CBC_MAC:
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
                if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
                {
                    t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_ARIA_CBC_MAC;
                }
                else
#endif
                {
                    t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_AES_CBC_MAC;
                }
                *mac_length = PSA_SYM_ALGO_MAC_AES_DIGEST_SIZE;
                break;
            default:
                funcres = PSA_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        if (PSA_SUCCESS == funcres)
        {
            if (*mac_length > mac_size)
            {
                funcres = PSA_ERROR_BUFFER_TOO_SMALL;
            }
            else
            {
                /* Make sure the key is available in the Asset Store */
                funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0, NULL, 0, NULL);
                if (PSA_SUCCESS == funcres)
                {
                    /* Format service request (key AssetId is already filled in) */
                    t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_MAC;
                    t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_MACGENERATE;
                    t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
                    t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                    t_cmd.MacAssetId = PSA_ASSETID_INVALID;
                    t_cmd.MacSize = 0U;
                    t_cmd.Data_p = input;
                    t_cmd.DataSize = (uint32_t)input_length;

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
                            (void)memcpy(mac, t_res.Mac, sizeof(t_res.Mac));
                        }
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }

                    (void)psaInt_KeyMgmtReleaseKey(pKey);
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


    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_mac_verify
 */
psa_status_t
psa_mac_verify(mbedtls_svc_key_id_t key,
               psa_algorithm_t alg,
               const uint8_t * input,
               size_t input_length,
               const uint8_t * mac,
               size_t mac_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    size_t MacNBytes = 0U;
    VexTokenCmd_Mac_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    psa_key_context_t *pKey = NULL;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_VERIFY_MESSAGE != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_VERIFY_MESSAGE))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (!(PSA_ALG_IS_HMAC(alg) || PSA_ALG_IS_MAC(alg)) ||
             (NULL == input) ||
             (0U == input_length) ||
             (NULL == mac) ||
             (0U == mac_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        uint64_t TotalMessageLength = (uint64_t)input_length;

        t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength);
        t_cmd.TotalMessageLengthHi = (uint32_t)(TotalMessageLength >> 32);
        if (PSA_ALG_IS_HMAC(alg))
        {
            switch (PSA_ALG_HMAC_GET_HASH(alg))
            {
            case PSA_ALG_SHA_1:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA1;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA1_DIGEST_SIZE;
                break;
            case PSA_ALG_SHA_224:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA224;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_224_DIGEST_SIZE;
                break;
            case PSA_ALG_SHA_256:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA256;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_256_DIGEST_SIZE;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case PSA_ALG_SHA_384:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA384;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_384_DIGEST_SIZE;
                break;
            case PSA_ALG_SHA_512:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA512;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA2_512_DIGEST_SIZE;
                break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
            case PSA_ALG_SHA3_224:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_224;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_224_DIGEST_SIZE;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength % PSA_SYM_ALGO_HMAC_SHA3_224_BLOCK_SIZE);
                t_cmd.TotalMessageLengthHi = 0U;
                if (0U == t_cmd.TotalMessageLengthLo)
                {
                    t_cmd.TotalMessageLengthLo = PSA_SYM_ALGO_HMAC_SHA3_224_BLOCK_SIZE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_256:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_256;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_256_DIGEST_SIZE;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength % PSA_SYM_ALGO_HMAC_SHA3_256_BLOCK_SIZE);
                t_cmd.TotalMessageLengthHi = 0U;
                if (0U == t_cmd.TotalMessageLengthLo)
                {
                    t_cmd.TotalMessageLengthLo = PSA_SYM_ALGO_HMAC_SHA3_256_BLOCK_SIZE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_384:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_384;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_384_DIGEST_SIZE;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength % PSA_SYM_ALGO_HMAC_SHA3_384_BLOCK_SIZE);
                t_cmd.TotalMessageLengthHi = 0U;
                if (0U == t_cmd.TotalMessageLengthLo)
                {
                    t_cmd.TotalMessageLengthLo = PSA_SYM_ALGO_HMAC_SHA3_384_BLOCK_SIZE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_512:
                t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_HMAC_SHA3_512;
                MacNBytes = PSA_SYM_ALGO_HMAC_SHA3_512_DIGEST_SIZE;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength % PSA_SYM_ALGO_HMAC_SHA3_512_BLOCK_SIZE);
                t_cmd.TotalMessageLengthHi = 0U;
                if (0U == t_cmd.TotalMessageLengthLo)
                {
                    t_cmd.TotalMessageLengthLo = PSA_SYM_ALGO_HMAC_SHA3_512_BLOCK_SIZE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
#endif
            default:
                funcres = PSA_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        else if (PSA_ALG_IS_MAC(alg))
        {
            switch(alg)
            {
            case PSA_ALG_CMAC:
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
                if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
                {
                    t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_ARIA_CMAC;
                }
                else
#endif
                {
                    t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_AES_CMAC;
                }
                MacNBytes = PSA_SYM_ALGO_MAC_AES_DIGEST_SIZE;
                break;
            case PSA_ALG_CBC_MAC:
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
                if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
                {
                    t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_ARIA_CBC_MAC;
                }
                else
#endif
                {
                    t_cmd.Algorithm = VEXTOKEN_ALGO_MAC_AES_CBC_MAC;
                }
                MacNBytes = PSA_SYM_ALGO_MAC_AES_DIGEST_SIZE;
                break;
            default:
                funcres = PSA_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        if (PSA_SUCCESS == funcres)
        {
            if ((MacNBytes != mac_length) ||
                (mac_length > sizeof(t_cmd.Mac)))
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            else
            {
                /* Make sure the key is available in the Asset Store */
                funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0, NULL, 0, NULL);
                if (PSA_SUCCESS == funcres)
                {
                    /* Format service request (key AssetId is already filled in) */
                    t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_MAC;
                    t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_MACVERIFY;
                    t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
                    t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                    t_cmd.MacAssetId = PSA_ASSETID_INVALID;
                    t_cmd.Data_p = input;
                    t_cmd.DataSize = (uint32_t)input_length;
                    t_cmd.MacSize = (uint32_t)mac_length;
                    (void)memcpy(t_cmd.Mac, mac, mac_length);

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

                    (void)psaInt_KeyMgmtReleaseKey(pKey);
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_mac_sign_setup
 */
psa_status_t
psa_mac_sign_setup(psa_mac_operation_t * operation,
                   mbedtls_svc_key_id_t key,
                   psa_algorithm_t alg)
{
    psa_status_t funcres = PSA_SUCCESS;
    psa_key_context_t *pKey = NULL;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_SIGN_MESSAGE != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_SIGN_MESSAGE))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if ((NULL == operation) ||
             !(PSA_ALG_IS_HMAC(alg) || PSA_ALG_IS_MAC(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_MAC_STATE_INIT != operation->mac_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        operation->alg = get_mac_algorithm(alg, pKey);
        if (operation->alg == 0U)
        {
            funcres = PSA_ERROR_NOT_SUPPORTED;
        }
        else
        {
            operation->key = key;
            operation->fVerify = 0U;

            if (PSA_ALG_IS_HMAC(alg))
            {
                operation->block_size = PSA_HASH_BLOCK_LENGTH(PSA_ALG_HMAC_GET_HASH(alg));
            }
            else if (PSA_ALG_IS_MAC(alg))
            {
                operation->block_size = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;
            }
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
        }
    }
    if (PSA_SUCCESS == funcres)
    {
        size_t MacNBytes = get_mac_size(operation->alg, true);
        PsaPolicyMask_t AssetPolicy = get_mac_asset_policy(operation->alg,
                                                           operation->fVerify);
        if ((AssetPolicy == 0U) || (MacNBytes == 0U))
        {
            funcres = PSA_ERROR_NOT_SUPPORTED;
        }
        else
        {
            AssetPolicy &= ~(EIP130_ASSET_POLICY_NONMODIFIABLE);
            AssetPolicy |= EIP130_ASSET_POLICY_SYM_TEMP;
            if (!psaInt_IsAccessSecure())
            {
                AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            funcres = psaInt_AssetAlloc(AssetPolicy, MacNBytes,
                                        &operation->TempAssetId);
            if (PSA_SUCCESS == funcres)
            {
                operation->mac_state = PSA_MAC_STATE_SETUP;
                (void)psaInt_KeyMgmtSetKeyInUse(key);
            }
            else
            {
                operation->TempAssetId = PSA_ASSETID_INVALID;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                operation->key = PSA_KEY_ID_NULL;
#endif
            }
        }
    }
    else
    {
        if (NULL != operation)
        {
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                operation->key = PSA_KEY_ID_NULL;
#endif
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_mac_verify_setup
 */
psa_status_t
psa_mac_verify_setup(psa_mac_operation_t * operation,
                     mbedtls_svc_key_id_t key,
                     psa_algorithm_t alg)
{
    psa_status_t funcres = PSA_SUCCESS;
    psa_key_context_t *pKey = NULL;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_VERIFY_MESSAGE != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_VERIFY_MESSAGE))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if ((NULL == operation) ||
             !(PSA_ALG_IS_HMAC(alg) || PSA_ALG_IS_MAC(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_MAC_STATE_INIT != operation->mac_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        operation->alg = get_mac_algorithm(alg, pKey);
        if (operation->alg == 0U)
        {
            funcres = PSA_ERROR_NOT_SUPPORTED;
        }
        else
        {
            operation->key = key;
            operation->fVerify = 255U;

            if (PSA_ALG_IS_HMAC(alg))
            {
                operation->block_size = PSA_HASH_BLOCK_LENGTH(PSA_ALG_HMAC_GET_HASH(alg));
            }
            else if (PSA_ALG_IS_MAC(alg))
            {
                operation->block_size = PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;
            }
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
        }
    }
    if (PSA_SUCCESS == funcres)
    {
        size_t MacNBytes = get_mac_size(operation->alg, true);
        PsaPolicyMask_t AssetPolicy = get_mac_asset_policy(operation->alg,
                                                           operation->fVerify);
        if ((AssetPolicy == 0U) || (MacNBytes == 0U))
        {
            funcres = PSA_ERROR_NOT_SUPPORTED;
        }
        else
        {
            AssetPolicy &= ~(EIP130_ASSET_POLICY_NONMODIFIABLE);
            AssetPolicy |= EIP130_ASSET_POLICY_SYM_TEMP;
            if (!psaInt_IsAccessSecure())
            {
                AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            funcres = psaInt_AssetAlloc(AssetPolicy, MacNBytes,
                                        &operation->TempAssetId);
            if (PSA_SUCCESS == funcres)
            {
                operation->mac_state = PSA_MAC_STATE_SETUP;
                (void)psaInt_KeyMgmtSetKeyInUse(key);
            }
            else
            {
                operation->TempAssetId = PSA_ASSETID_INVALID;
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                operation->key = PSA_KEY_ID_NULL;
#endif
            }
        }
    }
    else
    {
        if (NULL != operation)
        {
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                operation->key = PSA_KEY_ID_NULL;
#endif
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_mac_update
 */
psa_status_t
psa_mac_update(psa_mac_operation_t * operation,
               const uint8_t * input,
               size_t input_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_Mac_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    uint32_t leftover;
    uint32_t new_leftover;
    uint64_t bytes_available;
    size_t bytes_to_process;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        (NULL == input) ||
        (0U == input_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else if ((PSA_MAC_STATE_INIT == operation->mac_state) ||
             (0U == operation->block_size))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        operation->mac_state = PSA_MAC_STATE_UPDATE;

        leftover = operation->leftover_nbytes;
        bytes_available = (uint64_t)((size_t)leftover + input_length);
        new_leftover = (uint32_t)(bytes_available % operation->block_size);
        if (0U == new_leftover)
        {
            new_leftover = operation->block_size;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        bytes_to_process = (size_t)(bytes_available - new_leftover);
        if (0U == bytes_to_process)
        {
            (void)memcpy(&operation->leftover_buf[leftover], input,
                         input_length);
            operation->leftover_nbytes += (uint32_t)input_length;
        }
        else
        {
            const uint8_t * ptr = input;
            uint32_t size;

            /* Make sure the key is available in the Asset Store */
            funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0, NULL, 0, NULL);
            if (PSA_SUCCESS == funcres)
            {
                /* Format service request (key AssetId is already filled in) */
                t_cmd.OpCode =  (uint32_t)VEXTOKEN_OPCODE_MAC;
                t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_MACUPDATE;
                t_cmd.Algorithm = operation->alg;
                t_cmd.TempAssetId = operation->TempAssetId;
                t_cmd.TotalMessageLengthLo = 0U;
                t_cmd.TotalMessageLengthHi = 0U;
                t_cmd.MacAssetId = PSA_ASSETID_INVALID;
                t_cmd.MacSize = 0U;
                if (operation->fUpdateDone == 0U)
                {
                    t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2CONT;
                }
                else
                {
                    t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_CONT2CONT;
                }

                /* Handle leftover block combined with the new data */
                if (leftover != 0U)
                {
                    size = (operation->block_size - leftover);
                    (void)memcpy(&operation->leftover_buf[leftover], ptr, size);
                    t_cmd.Data_p = (const uint8_t *)operation->leftover_buf;
                    t_cmd.DataSize = operation->block_size;
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
                            operation->TotalMessageLength += (uint64_t)operation->block_size;
                            bytes_to_process -= operation->block_size;
                            ptr = &ptr[size];

                            /* Mark initialization done */
                            operation->fUpdateDone = 255U;
                            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_CONT2CONT;
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

                /* Handle remaining blocksize aligned data */
                while ((PSA_SUCCESS == funcres) && (0U != bytes_to_process))
                {
                    if ((MAX_DMA_SIZE - (operation->block_size - 1U)) < bytes_to_process)
                    {
                        size = (MAX_DMA_SIZE - (operation->block_size - 1U));
                    }
                    else
                    {
                        size = (uint32_t)bytes_to_process;
                    }
                    t_cmd.Data_p = (const uint8_t *)ptr;
                    t_cmd.DataSize = size;
                    t_cmd.TempAssetId = operation->TempAssetId;
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
                            operation->TotalMessageLength += (uint64_t)size;
                            bytes_to_process -= size;
                            ptr = &ptr[size];

                            /* Mark initialization done */
                            operation->fUpdateDone = 255U;
                            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_CONT2CONT;
                        }
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                }

                /* Handle update leftover data */
                if (PSA_SUCCESS == funcres)
                {
                    operation->leftover_nbytes = new_leftover;
                    if (new_leftover != 0U)
                    {
                        (void)memcpy(operation->leftover_buf, ptr, new_leftover);
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

                (void)psaInt_KeyMgmtReleaseKey(pKey);
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
 * psa_mac_sign_finish
 */
psa_status_t
psa_mac_sign_finish(psa_mac_operation_t * operation,
                    uint8_t * mac,
                    size_t mac_size,
                    size_t * mac_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    size_t MacNBytes = 0U;
    VexTokenCmd_Mac_t t_cmd;
    VexTokenRslt_Mac_t t_res;
    uint64_t TotalMessageLength = 0U;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        (NULL == mac) ||
        (0U == mac_size) ||
        (NULL == mac_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_MAC_STATE_UPDATE != operation->mac_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else
    {
        MacNBytes = get_mac_size(operation->alg, false);
        if (MacNBytes > mac_size)
        {
            funcres = PSA_ERROR_BUFFER_TOO_SMALL;
        }
        else if (0U == MacNBytes)
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else
        {
            TotalMessageLength = operation->TotalMessageLength + operation->leftover_nbytes;

            if ((VEXTOKEN_ALGO_MAC_HMAC_SHA3_224 == operation->alg) ||
                (VEXTOKEN_ALGO_MAC_HMAC_SHA3_256 == operation->alg) ||
                (VEXTOKEN_ALGO_MAC_HMAC_SHA3_384 == operation->alg) ||
                (VEXTOKEN_ALGO_MAC_HMAC_SHA3_512 == operation->alg))
            {
                TotalMessageLength %= operation->block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = operation->block_size;
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

            /* Make sure the key is available in the Asset Store */
            funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0, NULL, 0, NULL);
            if (PSA_SUCCESS == funcres)
            {
                /* Format service request (key AssetId is already filled in) */
                t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_MAC;
                t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_MACGENERATE;
                if (operation->fUpdateDone != 0U)
                {
                    t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_CONT2FINAL;
                    t_cmd.TempAssetId = operation->TempAssetId;
                }
                else
                {
                    t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
                    t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                }
                t_cmd.Algorithm = operation->alg;
                t_cmd.Data_p = operation->leftover_buf;
                t_cmd.DataSize = operation->leftover_nbytes;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength);
                t_cmd.TotalMessageLengthHi = (uint32_t)(TotalMessageLength >> 32);
                t_cmd.MacAssetId = PSA_ASSETID_INVALID;
                t_cmd.MacSize = 0U;
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
                        (void)memcpy(mac, t_res.Mac, MacNBytes);
                        *mac_length = MacNBytes;
                        (void)psaInt_KeyMgmtClrKeyInUse(operation->key);
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                        operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                        operation->key = PSA_KEY_ID_NULL;
#endif
                        if (operation->TempAssetId != PSA_ASSETID_INVALID)
                        {
                            (void)psaInt_AssetFree(operation->TempAssetId);
                            operation->TempAssetId = PSA_ASSETID_INVALID;
                        }
                    }
                }
                else
                {
                    /* MISRA - Intentially empty */
                }

                (void)psaInt_KeyMgmtReleaseKey(pKey);
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
 * psa_mac_verify_finish
 */
psa_status_t
psa_mac_verify_finish(psa_mac_operation_t * operation,
                      const uint8_t * mac,
                      size_t mac_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    uint64_t TotalMessageLength = 0U;
    size_t MacNBytes = 0U;
    VexTokenCmd_Mac_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        (NULL == mac) ||
        (0U == mac_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_MAC_STATE_UPDATE != operation->mac_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else
    {
        MacNBytes = get_mac_size(operation->alg, false);
        if (MacNBytes != mac_length)
        {
            funcres = PSA_ERROR_BUFFER_TOO_SMALL;
        }
        else if (mac_length > sizeof(t_cmd.Mac))
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else
        {
            TotalMessageLength = operation->TotalMessageLength + operation->leftover_nbytes;

            if ((VEXTOKEN_ALGO_MAC_HMAC_SHA3_224 == operation->alg) ||
                (VEXTOKEN_ALGO_MAC_HMAC_SHA3_256 == operation->alg) ||
                (VEXTOKEN_ALGO_MAC_HMAC_SHA3_384 == operation->alg) ||
                (VEXTOKEN_ALGO_MAC_HMAC_SHA3_512 == operation->alg))
            {
                TotalMessageLength %= operation->block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = operation->block_size;
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

            /* Make sure the key is available in the Asset Store */
            funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0, NULL, 0, NULL);
            if (PSA_SUCCESS == funcres)
            {
                /* Format service request (key AssetId is already filled in) */
                t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_MAC;
                t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_MACVERIFY;
                if (operation->fUpdateDone != 0U)
                {
                    t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_CONT2FINAL;
                    t_cmd.TempAssetId = operation->TempAssetId;
                }
                else
                {
                    t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
                    t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                }
                t_cmd.Algorithm = operation->alg;
                t_cmd.Data_p = operation->leftover_buf;
                t_cmd.DataSize = operation->leftover_nbytes;
                t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength);
                t_cmd.TotalMessageLengthHi = (uint32_t)(TotalMessageLength >> 32);
                t_cmd.MacAssetId = PSA_ASSETID_INVALID;
                t_cmd.MacSize = (uint32_t)mac_length;
                (void)memcpy(t_cmd.Mac, mac, mac_length);
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
                        funcres = PSA_ERROR_INVALID_SIGNATURE;
                    }
                    else
                    {
                        (void)psaInt_KeyMgmtClrKeyInUse(operation->key);
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                        operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                        operation->key = PSA_KEY_ID_NULL;
#endif
                        if (operation->TempAssetId != PSA_ASSETID_INVALID)
                        {
                            (void)psaInt_AssetFree(operation->TempAssetId);
                            operation->TempAssetId = PSA_ASSETID_INVALID;
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

                (void)psaInt_KeyMgmtReleaseKey(pKey);
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
 * psa_mac_abort
 */
psa_status_t
psa_mac_abort(psa_mac_operation_t * operation)
{
    psa_status_t funcres = PSA_SUCCESS;

    if (NULL == operation)
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        if (operation->TempAssetId != PSA_ASSETID_INVALID)
        {
            (void)psaInt_AssetFree(operation->TempAssetId);
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        (void)psaInt_KeyMgmtClrKeyInUse(operation->key);
        (void)memset(operation, 0, sizeof(psa_mac_operation_t));
    }

    return funcres;
}


/* end of file adapter_val_sym_mac.c */
