/* adapter_psa_sym_cipher.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the symmetric crypto cipher services.
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
#define PSA_CIPHER_STATE_INIT   0U
#define PSA_CIPHER_STATE_SETUP  1U
#define PSA_CIPHER_STATE_UPDATE 2U
#define PSA_CIPHER_STATE_IV     3U


/*----------------------------------------------------------------------------
 * get_cipher_mode
 */
static uint32_t
get_cipher_mode(uint32_t alg)
{
    uint32_t cipher_mode;

    switch (alg)
    {
    case PSA_ALG_CTR:
        cipher_mode = VEXTOKEN_MODE_CIPHER_CTR;
        break;
    case PSA_ALG_CBC_NO_PADDING:
        cipher_mode = VEXTOKEN_MODE_CIPHER_CBC;
        break;
    case PSA_ALG_ECB_NO_PADDING:
    default:
        cipher_mode = VEXTOKEN_MODE_CIPHER_ECB;
        break;
    }

    return cipher_mode;
}


/*----------------------------------------------------------------------------
 * psa_cipher_encrypt
 */
psa_status_t
psa_cipher_encrypt(mbedtls_svc_key_id_t key,
                   psa_algorithm_t alg,
                   const uint8_t * input,
                   size_t input_length,
                   uint8_t * output,
                   size_t output_size,
                   size_t * output_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_Cipher_t t_cmd;
    VexTokenRslt_Cipher_t t_res;
    size_t block_size = 0U;
    size_t IVSize = 0U;
    PsaPolicyMask_t AssetPolicy = (PsaPolicyMask_t)0U;
    PsaAssetId_t TempAssetId = PSA_ASSETID_INVALID;
    uint8_t IVbuff[16] = { 0 };
    psa_key_type_t KeyType;
    psa_key_context_t *pKey = NULL;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_ENCRYPT != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_ENCRYPT))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (!(PSA_ALG_IS_CIPHER(alg)) ||
             (NULL == input) ||
             (0U == input_length) ||
             (NULL == output) ||
             (0U == output_size) ||
             (NULL == output_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        (void)memset(&t_cmd, 0, sizeof(t_cmd));
        KeyType = pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type);
        block_size = PSA_BLOCK_CIPHER_BLOCK_LENGTH(KeyType);
        IVSize = PSA_CIPHER_IV_LENGTH(KeyType, alg);
        AssetPolicy = EIP130_ASSET_POLICY_SYM_TEMP |
                      EIP130_ASSET_POLICY_SCUICIPHERBULK |
                      EIP130_ASSET_POLICY_SCDIRENCGEN;
        if (!psaInt_IsAccessSecure())
        {
            AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        switch (alg)
        {
        case PSA_ALG_CTR:
            if (PSA_KEY_TYPE_AES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CTR;
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCTR32;
            break;
        case PSA_ALG_XTS:
            if (PSA_KEY_TYPE_AES == KeyType)
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_XTS;
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
                AssetPolicy = (PsaPolicyMask_t)0U;
            }
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        case PSA_ALG_ECB_NO_PADDING:
            AssetPolicy = (PsaPolicyMask_t)0U;
            if (PSA_KEY_TYPE_AES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_3DES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_ECB;
            break;
        case PSA_ALG_CBC_NO_PADDING:
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCBC;
            if (PSA_KEY_TYPE_AES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_3DES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACTDES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CBC;
            break;
        default:
            funcres = PSA_ERROR_INVALID_ARGUMENT;
            break;
        }
    }
    if (PSA_SUCCESS == funcres)
    {
        if (0U != (input_length % block_size))
        {
            if ((PSA_ALG_ECB_NO_PADDING == alg) ||
                (PSA_ALG_CBC_NO_PADDING == alg))
            {
                funcres = PSA_ERROR_INVALID_PADDING;
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
            if (output_size < (PSA_CIPHER_ENCRYPT_OUTPUT_SIZE(KeyType, alg, input_length)))
            {
                funcres = PSA_ERROR_BUFFER_TOO_SMALL;
            }
            else
            {
                if ((PsaPolicyMask_t)0U != AssetPolicy)
                {
                    funcres = psaInt_AssetAlloc(AssetPolicy, IVSize, &TempAssetId);
                    if (PSA_SUCCESS == funcres)
                    {
                        funcres = psa_generate_random(IVbuff, IVSize);
                        if (PSA_SUCCESS == funcres)
                        {
                            funcres = psaInt_AssetLoadPlaintext(TempAssetId,
                                                                IVbuff, IVSize);
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
        /* Format service request */
#ifdef PSA_USE_TOKEN_KEY
        /* Make sure the key is available for the operation */
        funcres = psaInt_KeyMgmtLoadKey(pKey, NULL, 0, 0, t_cmd.Key,
                                        sizeof(t_cmd.Key), &t_cmd.KeySize);
        if (PSA_ERROR_NOT_PERMITTED == funcres)
        {
            funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0,
                                            NULL, 0, NULL);
            t_cmd.KeySize = (uint32_t)pKey->key_size;
        }
        else
        {
            t_cmd.KeyAssetId = PSA_ASSETID_INVALID;
        }
#else
        /* Make sure the key is available in the Asset Store */
        funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0,
                                        NULL, 0, NULL);
        t_cmd.KeySize = (uint32_t)pKey->key_size;
#endif
        if (PSA_SUCCESS == funcres)
        {
            t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
            t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_ENCRYPT;

            if (PSA_ALG_XTS == alg)
            {
                t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                (void)memcpy(t_cmd.IV, IVbuff, IVSize);
            }
            else
            {
                t_cmd.TempAssetId = TempAssetId;
            }
            t_cmd.fEncrypt = 1U;
            t_cmd.SrcData_p = input;
            t_cmd.DataSize = (uint32_t)input_length;
            t_cmd.DstData_p = &output[IVSize];
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
                    *output_length = input_length + IVSize;
                    (void)memcpy(output, IVbuff, IVSize);
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_cipher_decrypt
 */
psa_status_t
psa_cipher_decrypt(mbedtls_svc_key_id_t key,
                   psa_algorithm_t alg,
                   const uint8_t * input,
                   size_t input_length,
                   uint8_t * output,
                   size_t output_size,
                   size_t * output_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_Cipher_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    size_t block_size = 0U;
    PsaPolicyMask_t AssetPolicy = (PsaPolicyMask_t)0U;
    PsaAssetId_t TempAssetId = PSA_ASSETID_INVALID;
    size_t IVSize = 0U;
    psa_key_type_t KeyType;
    psa_key_context_t *pKey = NULL;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_DECRYPT != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_DECRYPT))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if (!(PSA_ALG_IS_CIPHER(alg)) ||
             (NULL == input) ||
             (0U == input_length) ||
             (NULL == output) ||
             (0U == output_size) ||
             (NULL == output_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        (void)memset(&t_cmd, 0, sizeof(t_cmd));
        KeyType = pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type);
        block_size = PSA_BLOCK_CIPHER_BLOCK_LENGTH(KeyType);
        IVSize = PSA_CIPHER_IV_LENGTH(KeyType, alg);
        AssetPolicy = EIP130_ASSET_POLICY_SYM_TEMP |
                      EIP130_ASSET_POLICY_SCUICIPHERBULK |
                      EIP130_ASSET_POLICY_SCDIRDECVRFY;
        if (!psaInt_IsAccessSecure())
        {
            AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        switch (alg)
        {
        case PSA_ALG_CTR:
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCTR32;
            if (PSA_KEY_TYPE_AES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CTR;
            break;
        case PSA_ALG_XTS:
            if (PSA_KEY_TYPE_AES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_XTS;
                AssetPolicy = (PsaPolicyMask_t)0U;
            }
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        case PSA_ALG_ECB_NO_PADDING:
            AssetPolicy = (PsaPolicyMask_t)0U;
            if (PSA_KEY_TYPE_AES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_3DES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_ECB;
            break;
        case PSA_ALG_CBC_NO_PADDING:
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCBC;
            if (PSA_KEY_TYPE_AES == KeyType)
            {
                AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == KeyType)
            {
                AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == KeyType)
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_3DES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACTDES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CBC;
            break;
        default:
            funcres = PSA_ERROR_INVALID_ARGUMENT;
            break;
        }
    }
    if (PSA_SUCCESS == funcres)
    {
        if (0U != ((input_length - IVSize) % block_size))
        {
            if ((PSA_ALG_ECB_NO_PADDING == alg) ||
                (PSA_ALG_CBC_NO_PADDING == alg))
            {
                funcres = PSA_ERROR_INVALID_PADDING;
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
            if (output_size < (PSA_CIPHER_DECRYPT_OUTPUT_SIZE(KeyType, alg, (input_length - IVSize))))
            {
                funcres = PSA_ERROR_BUFFER_TOO_SMALL;
            }
            else
            {
                if ((PsaPolicyMask_t)0U != AssetPolicy)
                {
                    funcres = psaInt_AssetAlloc(AssetPolicy, IVSize, &TempAssetId);
                    if (PSA_SUCCESS == funcres)
                    {
                        funcres = psaInt_AssetLoadPlaintext(TempAssetId,
                                                            input,
                                                            IVSize);
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
        /* Format service request */
#ifdef PSA_USE_TOKEN_KEY
        /* Make sure the key is available for the operation */
        funcres = psaInt_KeyMgmtLoadKey(pKey, NULL, 0, 0, t_cmd.Key, 
                                        sizeof(t_cmd.Key), &t_cmd.KeySize);
        if (PSA_ERROR_NOT_PERMITTED == funcres)
        {
            funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0,
                                            NULL, 0, NULL);
            t_cmd.KeySize = (uint32_t)pKey->key_size;
        }
        else
        {
            t_cmd.KeyAssetId = PSA_ASSETID_INVALID;
        }
#else
        /* Make sure the key is available in the Asset Store */
        funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0,
                                        NULL, 0, NULL);
        t_cmd.KeySize = (uint32_t)pKey->key_size;
#endif
        if (PSA_SUCCESS == funcres)
        {
            t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
            t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_ENCRYPT;

            if (PSA_ALG_XTS == alg)
            {
                t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                (void)memcpy(t_cmd.IV, input, IVSize);
            }
            else
            {
                t_cmd.TempAssetId = TempAssetId;
            }
            t_cmd.fEncrypt = 0U;
            t_cmd.SrcData_p = &input[IVSize];
            t_cmd.DataSize = (uint32_t)(input_length - IVSize);
            t_cmd.DstData_p = output;
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
                    *output_length = input_length - IVSize;
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_cipher_encrypt_setup
 */
psa_status_t
psa_cipher_encrypt_setup(psa_cipher_operation_t * operation,
                         mbedtls_svc_key_id_t key,
                         psa_algorithm_t alg)
{
    psa_status_t funcres = PSA_SUCCESS;
    PsaPolicyMask_t AssetPolicy;
    psa_key_context_t *pKey = NULL;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_ENCRYPT != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_ENCRYPT))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if ((NULL == operation) ||
             !(PSA_ALG_IS_CIPHER(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_CIPHER_STATE_INIT != operation->cipher_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        operation->block_size = PSA_BLOCK_CIPHER_BLOCK_LENGTH(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type));
        operation->key = key;
        operation->fEncrypt = 255U;
        operation->Mode = alg;
        operation->IVSize = PSA_CIPHER_IV_LENGTH(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type), alg);
        AssetPolicy = EIP130_ASSET_POLICY_SYM_TEMP |
                      EIP130_ASSET_POLICY_SCUICIPHERBULK |
                      EIP130_ASSET_POLICY_SCDIRENCGEN;
        if (!psaInt_IsAccessSecure())
        {
            AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        switch (alg)
        {
        case PSA_ALG_CTR:
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCTR32;
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_AES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_ARIA;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        case PSA_ALG_ECB_NO_PADDING:
            AssetPolicy = (PsaPolicyMask_t)0U;
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_AES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_ARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_3DES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        case PSA_ALG_CBC_NO_PADDING:
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCBC;
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_AES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_ARIA;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_3DES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACTDES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        default:
            funcres = PSA_ERROR_INVALID_ARGUMENT;
            break;
        }
    }
    if (PSA_SUCCESS == funcres)
    {
        if ((PsaPolicyMask_t)0U != AssetPolicy)
        {
            funcres = psaInt_AssetAlloc(AssetPolicy, operation->IVSize,
                                        &operation->TempAssetId);
        }
        else
        {
            operation->TempAssetId = PSA_ASSETID_INVALID;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_SUCCESS == funcres)
    {
        operation->cipher_state = PSA_CIPHER_STATE_SETUP;
        (void)psaInt_KeyMgmtSetKeyInUse(key);
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
 * psa_cipher_decrypt_setup
 */
psa_status_t
psa_cipher_decrypt_setup(psa_cipher_operation_t * operation,
                         mbedtls_svc_key_id_t key,
                         psa_algorithm_t alg)
{
    psa_status_t funcres = PSA_SUCCESS;
    PsaPolicyMask_t AssetPolicy;
    psa_key_context_t *pKey = NULL;

    funcres = psaInt_KeyMgmtGetKey(key, &pKey);
    if (funcres != PSA_SUCCESS)
    {
        /* Key not found */
    }
    else if (PSA_KEY_USAGE_DECRYPT != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_DECRYPT))
    {
        funcres = PSA_ERROR_NOT_PERMITTED;
    }
    else if ((NULL == operation) ||
             !(PSA_ALG_IS_CIPHER(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_CIPHER_STATE_INIT != operation->cipher_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        operation->block_size = PSA_BLOCK_CIPHER_BLOCK_LENGTH(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type));
        operation->key = key;
        operation->fEncrypt = 0U;
        operation->Mode = alg;
        operation->IVSize = PSA_CIPHER_IV_LENGTH(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type), alg);
        AssetPolicy = EIP130_ASSET_POLICY_SYM_TEMP |
                      EIP130_ASSET_POLICY_SCUICIPHERBULK |
                      EIP130_ASSET_POLICY_SCDIRDECVRFY;
        if (!psaInt_IsAccessSecure())
        {
            AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        switch (alg)
        {
        case PSA_ALG_CTR:
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCTR32;
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_AES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_ARIA;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        case PSA_ALG_ECB_NO_PADDING:
            AssetPolicy = (PsaPolicyMask_t)0U;
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_AES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_ARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_3DES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        case PSA_ALG_CBC_NO_PADDING:
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCBCBC;
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_AES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_ARIA;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                operation->alg = VEXTOKEN_ALGO_CIPHER_3DES;
                AssetPolicy |= EIP130_ASSET_POLICY_SCACTDES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        default:
            funcres = PSA_ERROR_INVALID_ARGUMENT;
            break;
        }
    }
    if (PSA_SUCCESS == funcres)
    {
        if ((PsaPolicyMask_t)0U != AssetPolicy)
        {
            funcres = psaInt_AssetAlloc(AssetPolicy, operation->IVSize,
                                        &operation->TempAssetId);
        }
        else
        {
            operation->TempAssetId = PSA_ASSETID_INVALID;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_SUCCESS == funcres)
    {
        operation->cipher_state = PSA_CIPHER_STATE_SETUP;
        (void)psaInt_KeyMgmtSetKeyInUse(key);
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
 * psa_cipher_generate_iv
 */
psa_status_t
psa_cipher_generate_iv(psa_cipher_operation_t * operation,
                       uint8_t * iv,
                       size_t iv_size,
                       size_t * iv_length)
{
    psa_status_t funcres = PSA_SUCCESS;

    if ((NULL == operation) ||
        (NULL == iv) ||
        (0U == iv_size) ||
        (NULL == iv_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (operation->IVSize > iv_size)
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if ((PSA_CIPHER_STATE_SETUP != operation->cipher_state) ||
             (PSA_ALG_ECB_NO_PADDING == operation->Mode))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        *iv_length = operation->IVSize;
        funcres = psa_generate_random(iv, *iv_length);
        if (PSA_SUCCESS == funcres)
        {
            funcres = psaInt_AssetLoadPlaintext(operation->TempAssetId,
                                                iv, *iv_length);
            if (PSA_SUCCESS == funcres)
            {
                operation->cipher_state = PSA_CIPHER_STATE_IV;
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_cipher_set_iv
 */
psa_status_t
psa_cipher_set_iv(psa_cipher_operation_t * operation,
                  const uint8_t * iv,
                  size_t iv_length)
{
    psa_status_t funcres = PSA_SUCCESS;

    if ((NULL == operation) ||
        (NULL == iv) ||
        (0U == iv_length) ||
        (iv_length > 16U))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if ((PSA_CIPHER_STATE_SETUP != operation->cipher_state) ||
             (PSA_ALG_ECB_NO_PADDING == operation->Mode))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        funcres = psaInt_AssetLoadPlaintext(operation->TempAssetId,
                                            iv, iv_length);
        if (PSA_SUCCESS == funcres)
        {
            operation->cipher_state = PSA_CIPHER_STATE_IV;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_cipher_update
 */
psa_status_t
psa_cipher_update(psa_cipher_operation_t * operation,
                  const uint8_t * input,
                  size_t input_length,
                  uint8_t * output,
                  size_t output_size,
                  size_t * output_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    uint32_t leftover;
    uint32_t new_leftover;
    uint64_t bytes_available;
    size_t bytes_to_process;
    VexTokenCmd_Cipher_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        (NULL == input) ||
        (0U == input_length) ||
        (NULL == output) ||
        (0U == output_size) ||
        (NULL == output_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else if (output_size < PSA_CIPHER_UPDATE_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type), operation->Mode, input_length))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if ((PSA_CIPHER_STATE_INIT == operation->cipher_state) ||
             (0U == operation->block_size))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if ((PSA_CIPHER_STATE_SETUP == operation->cipher_state) &&
             (PSA_ALG_ECB_NO_PADDING != operation->Mode))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        operation->cipher_state = PSA_CIPHER_STATE_UPDATE;

        leftover = operation->leftover_nbytes;
        bytes_available = (uint64_t)leftover + input_length;
        new_leftover = (uint32_t)bytes_available % operation->block_size;
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
            *output_length = 0U;
        }
        else
        {
            const uint8_t * ptr = input;
            uint32_t size;

            /* Format service request */
            t_cmd.Mode = get_cipher_mode(operation->Mode);
            t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
            t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_ENCRYPT;
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
            }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
            }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
            else if (PSA_KEY_TYPE_DES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_3DES;
            }
#endif
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            if (PSA_SUCCESS == funcres)
            {
#ifdef PSA_USE_TOKEN_KEY
                /* Make sure the key is available for the operation */
                funcres = psaInt_KeyMgmtLoadKey(pKey, NULL, 0, 0, t_cmd.Key,
                                                sizeof(t_cmd.Key), &t_cmd.KeySize);
                if (PSA_ERROR_NOT_PERMITTED == funcres)
                {
                    funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0,
                                                    NULL, 0, NULL);
                    t_cmd.KeySize = (uint32_t)pKey->key_size;
                }
                else
                {
                    t_cmd.KeyAssetId = PSA_ASSETID_INVALID;
                }
#else
                /* Make sure the key is available in the Asset Store */
                funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0,
                                                NULL, 0, NULL);
                t_cmd.KeySize = (uint32_t)pKey->key_size;
#endif
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            if (PSA_SUCCESS == funcres)
            {
                t_cmd.TempAssetId = operation->TempAssetId;
                t_cmd.fEncrypt = operation->fEncrypt;

                /* Handle leftover block combined with the new data */
                if (leftover != 0U)
                {
                    size = (operation->block_size - leftover);
                    (void)memcpy(&operation->leftover_buf[leftover], ptr, size);
                    t_cmd.SrcData_p = (const uint8_t *)operation->leftover_buf;
                    t_cmd.DataSize = operation->block_size;
                    *output_length = operation->block_size;
                    t_cmd.DstData_p = output;
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
                            bytes_to_process -= operation->block_size;
                            ptr = &ptr[size];
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
                    t_cmd.SrcData_p = (const uint8_t *)ptr;
                    t_cmd.DataSize = size;
                    if (0U != leftover)
                    {
                        t_cmd.DstData_p = &output[operation->block_size];
                    }
                    else
                    {
                        t_cmd.DstData_p = output;
                    }
                    *output_length += (size_t)size;
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
                            bytes_to_process -= size;
                            ptr = &ptr[size];
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
 * psa_cipher_finish
 */
psa_status_t
psa_cipher_finish(psa_cipher_operation_t * operation,
                  uint8_t * output,
                  size_t output_size,
                  size_t * output_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_Cipher_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        (NULL == output) ||
        (0U == output_size) ||
        (NULL == output_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_CIPHER_STATE_UPDATE != operation->cipher_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else
    {
        t_cmd.Mode = get_cipher_mode(operation->Mode);
        t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_ENCRYPT;
        if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
        {
            t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
        }
#ifndef PSA_REMOVE_SYM_ALGO_ARIA
        else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
        {
            t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
        }
#endif
#ifndef PSA_REMOVE_SYM_ALGO_3DES
        else if (PSA_KEY_TYPE_DES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
        {
            t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_3DES;
        }
#endif
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        if (PSA_SUCCESS == funcres)
        {
            if (0U != (operation->leftover_nbytes % operation->block_size))
            {
                if ((PSA_ALG_ECB_NO_PADDING == operation->Mode) ||
                    (PSA_ALG_CBC_NO_PADDING == operation->Mode))
                {
                    funcres = PSA_ERROR_INVALID_PADDING;
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
            if (output_size < PSA_BLOCK_CIPHER_BLOCK_LENGTH(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type)))
            {
                funcres = PSA_ERROR_BUFFER_TOO_SMALL;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            if (PSA_SUCCESS == funcres)
            {
#ifdef PSA_USE_TOKEN_KEY
                /* Make sure the key is available for the operation */
                funcres = psaInt_KeyMgmtLoadKey(pKey, NULL, 0, 0, t_cmd.Key,
                                                sizeof(t_cmd.Key), &t_cmd.KeySize);
                if (PSA_ERROR_NOT_PERMITTED == funcres)
                {
                    funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0,
                                                    NULL, 0, NULL);
                    t_cmd.KeySize = (uint32_t)pKey->key_size;
                }
                else
                {
                    t_cmd.KeyAssetId = PSA_ASSETID_INVALID;
                }
#else
                /* Make sure the key is available in the Asset Store */
                funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0,
                                                NULL, 0, NULL);
                t_cmd.KeySize = (uint32_t)pKey->key_size;
#endif
                if (PSA_SUCCESS == funcres)
                {
                    t_cmd.TempAssetId = operation->TempAssetId;
                    t_cmd.fEncrypt = operation->fEncrypt;
                    t_cmd.DataSize = (uint32_t)operation->leftover_nbytes;
                    t_cmd.SrcData_p = operation->leftover_buf;
                    t_cmd.DstData_p = output;
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
                            (void)psaInt_KeyMgmtClrKeyInUse(operation->key);
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                            operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                            operation->key = PSA_KEY_ID_NULL;
#endif
                            *output_length = operation->leftover_nbytes;
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_cipher_abort
 */
psa_status_t
psa_cipher_abort(psa_cipher_operation_t * operation)
{
    psa_status_t funcres = PSA_SUCCESS;

    if (NULL == operation)
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        if (PSA_ASSETID_INVALID != operation->TempAssetId)
        {
            (void)psaInt_AssetFree(operation->TempAssetId);
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        (void)psaInt_KeyMgmtClrKeyInUse(operation->key);
        (void)memset(operation, 0, sizeof(psa_cipher_operation_t));
    }

    return funcres;
}


/* end of file adapter_psa_sym_cipher.c */
