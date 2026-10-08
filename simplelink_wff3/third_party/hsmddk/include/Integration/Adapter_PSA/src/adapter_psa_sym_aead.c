/* adapter_psa_sym_aead.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the symmetric crypto AEAD services.
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
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>
#include <third_party/hsmddk/include/Config/cs_mbedtls.h>

/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#define PSA_SYM_ALGO_CHACHA20_BLOCK_SIZE     (512U/8U)
#define PSA_SYM_ALGO_AES_BLOCK_SIZE          (128U/8U)

/* Size of state asset for GCM/CCM continuation */
#define PSA_SYM_STATE_ASSET_SIZE              48U

/* No GCM operation */
#define PSA_SYM_MODE_GCM_NONE 0U
/* Autonomous GCM operation (both H and Y0-encrypted calculated internally) */
#define PSA_SYM_MODE_GCM_AUTO 43U

/* States */
#define PSA_AEAD_STATE_INIT         0U
#define PSA_AEAD_STATE_SETUP        1U
#define PSA_AEAD_STATE_SET_LENGTH   2U
#define PSA_AEAD_STATE_SET_NONCE    3U
#define PSA_AEAD_STATE_UPDATE       4U
#define PSA_AEAD_STATE_IV           5U
#define PSA_AEAD_STATE_UPDATE_AAD   6U


/*----------------------------------------------------------------------------
 * psa_aead_encrypt
 */
psa_status_t
psa_aead_encrypt(mbedtls_svc_key_id_t key,
                 psa_algorithm_t alg,
                 const uint8_t * nonce,
                 size_t nonce_length,
                 const uint8_t * additional_data,
                 size_t additional_data_length,
                 const uint8_t * plaintext,
                 size_t plaintext_length,
                 uint8_t * ciphertext,
                 size_t ciphertext_size,
                 size_t * ciphertext_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_CipherAE_t t_cmd;
    VexTokenRslt_CipherAE_t t_res;
    uint8_t tag_size = 16;
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
    else if (!(PSA_ALG_IS_AEAD(alg)) ||
             ((NULL == additional_data) && (0U != additional_data_length)) ||
             ((NULL == plaintext) && (0U != plaintext_length)) ||
             (NULL == ciphertext) ||
             (0U == ciphertext_size) ||
             (NULL == ciphertext_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_AEAD_ENCRYPT_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type), alg, plaintext_length) > ciphertext_size)
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        (void)memset(&t_cmd, 0, sizeof(t_cmd));
        t_cmd.fNoRandomIV = 1U;
        switch (alg)
        {
        case PSA_ALG_CCM:
            if ((NULL == nonce) ||
                (7U > nonce_length) || (13U < nonce_length))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CCM;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_NONE;
            }
            break;
        case PSA_ALG_GCM:
            if ((NULL == nonce) || (16U != nonce_length))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_GCM;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_AUTO;
            }
            break;
#if !defined(PSA_REMOVE_SYM_ALGO_CHACHA20) && \
    !defined(PSA_REMOVE_SYM_ALGO_POLY1305)
        case PSA_ALG_CHACHA20_POLY1305:
            if ((NULL == nonce) || (12U != nonce_length))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CHACHA20_AEAD;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_NONE;
            }
            break;
#endif
        default:
            funcres = PSA_ERROR_NOT_SUPPORTED;
            break;
        }
        if (PSA_SUCCESS == funcres)
        {
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
            }
#if !defined(PSA_REMOVE_SYM_ALGO_ARIA_CCM) || \
    !defined(PSA_REMOVE_SYM_ALGO_ARIA_GCM)
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
            }
#endif
#if !defined(PSA_REMOVE_SYM_ALGO_CHACHA20) && \
    !defined(PSA_REMOVE_SYM_ALGO_POLY1305)
            else if (PSA_KEY_TYPE_CHACHA20 == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_CHACHA20;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
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
                    t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
                    t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_AUTHENCRYPT;
                    t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_INIT2FINAL;
                    t_cmd.AAD_p = additional_data;
                    t_cmd.AADSize = (uint32_t)additional_data_length;
                    t_cmd.SrcData_p = plaintext;
                    t_cmd.DataSize = (uint32_t)plaintext_length;
                    t_cmd.DstData_p = ciphertext;
                    t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                    if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
                    {
                        t_cmd.TotalDataLength = (uint32_t)plaintext_length;
                        t_cmd.TotalAADLength = (uint32_t)additional_data_length;
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                    (void)memset(&t_res.Tag, 0, sizeof(t_res.Tag));
                    t_cmd.TagSize = (uint8_t)tag_size;
                    t_cmd.fEncrypt = 1U;

                    if (PSA_ALG_GCM == alg)
                    {
                        (void)memset(&t_res.IV, 0, sizeof(t_cmd.IV));
                        (void)memcpy(t_cmd.IV, nonce, nonce_length);
                        t_cmd.NonceHashKeySize = 0U;
                    }
                    else
                    {
                        (void)memcpy(t_cmd.NonceHashKey, nonce, nonce_length);
                        t_cmd.NonceHashKeySize = (uint8_t)nonce_length;
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
                            *ciphertext_length = plaintext_length + tag_size;
                            (void)memcpy(&ciphertext[plaintext_length], t_res.Tag, tag_size);
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
 * psa_aead_decrypt
 */
psa_status_t
psa_aead_decrypt(mbedtls_svc_key_id_t key,
                 psa_algorithm_t alg,
                 const uint8_t * nonce,
                 size_t nonce_length,
                 const uint8_t * additional_data,
                 size_t additional_data_length,
                 const uint8_t * ciphertext,
                 size_t ciphertext_length,
                 uint8_t * plaintext,
                 size_t plaintext_size,
                 size_t * plaintext_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_CipherAE_t t_cmd;
    VexTokenRslt_CipherAE_t t_res;
    uint8_t tag_size;
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
    else if (!(PSA_ALG_IS_AEAD(alg)) ||
             ((NULL == additional_data) && (0U != additional_data_length)) ||
             ((NULL == plaintext) && (0U != plaintext_size)) ||
             (NULL == ciphertext) ||
             (0U == ciphertext_length) ||
             (NULL == plaintext_length) ||
             (ciphertext_length < plaintext_size))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_AEAD_DECRYPT_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type), alg, ciphertext_length) > plaintext_size)
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        tag_size = (uint8_t)(ciphertext_length - plaintext_size);
        if (tag_size > 16U)
        {
            tag_size = 16U;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        (void)memset(&t_cmd, 0, sizeof(t_cmd));
        t_cmd.fNoRandomIV = 1U;
        switch (alg)
        {
        case PSA_ALG_CCM:
            if ((NULL == nonce) ||
                (7U > nonce_length) || (13U < nonce_length))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CCM;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_NONE;
            }
            break;
        case PSA_ALG_GCM:
            if ((NULL == nonce) || (16U != nonce_length))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_GCM;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_AUTO;
            }
            break;
#if !defined(PSA_REMOVE_SYM_ALGO_CHACHA20) && \
    !defined(PSA_REMOVE_SYM_ALGO_POLY1305)
        case PSA_ALG_CHACHA20_POLY1305:
            if ((NULL == nonce) || (12U != nonce_length))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CHACHA20_AEAD;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_NONE;
            }
            break;
#endif
        default:
            funcres = PSA_ERROR_NOT_SUPPORTED;
            break;
        }
        if (PSA_SUCCESS == funcres)
        {
            if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
            }
#if !defined(PSA_REMOVE_SYM_ALGO_ARIA_CCM) || \
    !defined(PSA_REMOVE_SYM_ALGO_ARIA_GCM)
            else if (PSA_KEY_TYPE_ARIA == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_ARIA;
            }
#endif
#if !defined(PSA_REMOVE_SYM_ALGO_CHACHA20) && \
    !defined(PSA_REMOVE_SYM_ALGO_POLY1305)
            else if (PSA_KEY_TYPE_CHACHA20 == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
            {
                t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_CHACHA20;
            }
#endif
            else
            {
                funcres = PSA_ERROR_NOT_SUPPORTED;
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
                    t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
                    t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_AUTHENCRYPT;
                    t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_INIT2FINAL;
                    t_cmd.fEncrypt = 0U;
                    t_cmd.AAD_p = additional_data;
                    t_cmd.AADSize = (uint32_t)additional_data_length;
                    t_cmd.SrcData_p = ciphertext;
                    t_cmd.DstData_p = plaintext;
                    t_cmd.DataSize = (uint32_t)(ciphertext_length - tag_size);
                    t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                    if (PSA_KEY_TYPE_AES == pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
                    {
                        t_cmd.TotalDataLength = (uint32_t)(ciphertext_length - tag_size);
                        t_cmd.TotalAADLength = (uint32_t)additional_data_length;
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                    (void)memcpy(t_cmd.Tag, &ciphertext[ciphertext_length - tag_size], tag_size);
                    t_cmd.TagSize = (uint8_t)tag_size;

                    if (PSA_ALG_GCM == alg)
                    {
                        (void)memcpy(t_cmd.IV, nonce, nonce_length);
                    }
                    else
                    {
                        (void)memcpy(t_cmd.NonceHashKey, nonce, nonce_length);
                        t_cmd.NonceHashKeySize = (uint8_t)nonce_length;
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
                            *plaintext_length = ciphertext_length - tag_size;
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
 * psa_aead_encrypt_setup
 */
psa_status_t
psa_aead_encrypt_setup(psa_aead_operation_t * operation,
                       mbedtls_svc_key_id_t key,
                       psa_algorithm_t alg)
{
    psa_status_t funcres = PSA_SUCCESS;
    PsaPolicyMask_t AssetPolicy = (EIP130_ASSET_POLICY_SYM_TEMP |
                                   EIP130_ASSET_POLICY_SCUICIPHERAUTH |
                                   EIP130_ASSET_POLICY_SCACAES |
                                   EIP130_ASSET_POLICY_SCDIRENCGEN);
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
    else if ((NULL == operation) || !(PSA_ALG_IS_AEAD(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_AEAD_STATE_INIT != operation->aead_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (PSA_KEY_TYPE_AES != pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
    {
        funcres = PSA_ERROR_NOT_SUPPORTED;
    }
    else
    {
        operation->Mode = alg;
        operation->key = key;
        operation->fEncrypt = 255U;
        if (!psaInt_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        if (PSA_ALG_GCM == alg)
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCAGCM;
        }
        else if (PSA_ALG_CCM == alg)
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCACCM;
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        if (PSA_SUCCESS == funcres)
        {
            funcres = psaInt_AssetAlloc(AssetPolicy, PSA_SYM_STATE_ASSET_SIZE,
                                        &operation->TempAssetId);
            if (PSA_SUCCESS == funcres)
            {
                operation->aead_state = PSA_AEAD_STATE_SETUP;
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
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_aead_decrypt_setup
 */
psa_status_t
psa_aead_decrypt_setup(psa_aead_operation_t * operation,
                       mbedtls_svc_key_id_t key,
                       psa_algorithm_t alg)
{
    psa_status_t funcres = PSA_SUCCESS;
    PsaPolicyMask_t AssetPolicy = (EIP130_ASSET_POLICY_SYM_TEMP |
                                   EIP130_ASSET_POLICY_SCUICIPHERAUTH |
                                   EIP130_ASSET_POLICY_SCACAES |
                                   EIP130_ASSET_POLICY_SCDIRDECVRFY);
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
    else if ((NULL == operation) || !(PSA_ALG_IS_AEAD(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_AEAD_STATE_INIT != operation->aead_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (PSA_KEY_TYPE_AES != pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type))
    {
        funcres = PSA_ERROR_NOT_SUPPORTED;
    }
    else
    {
        operation->Mode = alg;
        operation->key = key;
        operation->fEncrypt = 0U;
        if (!psaInt_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        if (PSA_ALG_GCM == alg)
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCAGCM;
        }
        else if (PSA_ALG_CCM == alg)
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SCMCACCM;
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        if (PSA_SUCCESS == funcres)
        {
            funcres = psaInt_AssetAlloc(AssetPolicy, PSA_SYM_STATE_ASSET_SIZE,
                                        &operation->TempAssetId);
            if (PSA_SUCCESS == funcres)
            {
                operation->aead_state = PSA_AEAD_STATE_SETUP;
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
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_aead_set_lengths
 */
psa_status_t
psa_aead_set_lengths(psa_aead_operation_t * operation,
                     size_t ad_length,
                     size_t plaintext_length)
{
    psa_status_t funcres = PSA_SUCCESS;

    if ((NULL == operation) ||
        ((0U == ad_length) && (0U == plaintext_length)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_AEAD_STATE_SETUP != operation->aead_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        operation->ad_length = (uint32_t)ad_length;
        operation->plaintext_length = (uint32_t)plaintext_length;
        operation->aead_state = PSA_AEAD_STATE_SET_LENGTH;
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_aead_generate_nonce
 */
psa_status_t
psa_aead_generate_nonce(psa_aead_operation_t * operation,
                        uint8_t * nonce,
                        size_t nonce_size,
                        size_t * nonce_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        (NULL == nonce) ||
        (0U == nonce_size) ||
        (NULL == nonce_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (((PSA_ALG_CCM == operation->Mode) &&
              (PSA_AEAD_STATE_SET_LENGTH != operation->aead_state)) ||
             ((PSA_AEAD_STATE_SETUP != operation->aead_state) &&
              (PSA_AEAD_STATE_SET_LENGTH != operation->aead_state)))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else if (nonce_size < PSA_AEAD_NONCE_LENGTH(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type), operation->Mode))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        if (PSA_ALG_CCM == operation->Mode)
        {
            *nonce_length = 13U;
        }
        else if (PSA_ALG_GCM == operation->Mode)
        {
            *nonce_length = 12U;
        }
        else
        {
            funcres = PSA_ERROR_DATA_INVALID;
        }

        if (PSA_SUCCESS == funcres)
        {
            funcres = psa_generate_random(nonce, *nonce_length);
            if (PSA_SUCCESS == funcres)
            {
                if (PSA_ALG_GCM == operation->Mode)
                {
                    /* Initialize the counter */
                    uint8_t * ptr = &nonce[*nonce_length];
                    *ptr = 0U;
                    ptr++;
                    *ptr = 0U;
                    ptr++;
                    *ptr = 0U;
                    ptr++;
                    *ptr = 1U;

                    /* Correct nonce length */
                    *nonce_length = 16U;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                (void)memcpy(operation->nonce, nonce, *nonce_length);
                operation->nonce_length = (uint8_t)*nonce_length;
                operation->aead_state = PSA_AEAD_STATE_SET_NONCE;
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
 * psa_aead_set_nonce
 */
psa_status_t
psa_aead_set_nonce(psa_aead_operation_t * operation,
                   const uint8_t * nonce,
                   size_t nonce_length)
{
    psa_status_t funcres = PSA_SUCCESS;

    if ((NULL == operation) ||
        (NULL == nonce) ||
        (0U == nonce_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (((PSA_ALG_CCM == operation->Mode) &&
              (PSA_AEAD_STATE_SET_LENGTH != operation->aead_state)) ||
             ((PSA_AEAD_STATE_SETUP != operation->aead_state) &&
              (PSA_AEAD_STATE_SET_LENGTH != operation->aead_state)))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        switch (operation->Mode)
        {
        case PSA_ALG_CCM:
            if ((7U > nonce_length) || (13U < nonce_length))
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            break;
        case PSA_ALG_GCM:
            if (16U != nonce_length)
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            break;
        default:
            funcres = PSA_ERROR_DATA_INVALID;
            break;
        }
        if (PSA_SUCCESS == funcres)
        {
            (void)memcpy(operation->nonce, nonce, nonce_length);
            operation->nonce_length = (uint8_t)nonce_length;
            operation->aead_state = PSA_AEAD_STATE_SET_NONCE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_aead_update_ad
 */
psa_status_t
psa_aead_update_ad(psa_aead_operation_t * operation,
                   const uint8_t * input,
                   size_t input_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_CipherAE_t t_cmd;
    VexTokenRslt_CipherAE_t t_res;
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
    else if ((PSA_AEAD_STATE_SET_NONCE != operation->aead_state) &&
             (PSA_AEAD_STATE_UPDATE_AAD != operation->aead_state))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (input_length > operation->ad_length)
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else
    {
        operation->aead_state = PSA_AEAD_STATE_UPDATE_AAD;

        leftover = operation->leftover_nbytes_AAD;
        bytes_available = (uint64_t)leftover + input_length;
        new_leftover = (uint32_t)bytes_available % PSA_SYM_ALGO_AES_BLOCK_SIZE;
        if (0U == new_leftover)
        {
            new_leftover = PSA_SYM_ALGO_AES_BLOCK_SIZE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        bytes_to_process = (size_t)(bytes_available - new_leftover);
        if (0U == bytes_to_process)
        {
            (void)memcpy(&operation->leftover_AAD[leftover], input,
                         input_length);
            operation->leftover_nbytes_AAD += (uint32_t)input_length;
        }
        else
        {
            const uint8_t * ptr = input;
            uint32_t size;

            (void)memset(&t_res, 0, sizeof(t_res));
            if (PSA_ALG_CCM == operation->Mode)
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CCM;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_NONE;
                (void)memcpy(t_cmd.NonceHashKey,
                             operation->nonce, operation->nonce_length);
                t_cmd.NonceHashKeySize = operation->nonce_length;
            }
            else if (PSA_ALG_GCM == operation->Mode)
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_GCM;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_AUTO;
                (void)memcpy(t_cmd.IV,
                             operation->nonce, operation->nonce_length);
                t_cmd.NonceHashKeySize = 0U;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }

            if (PSA_SUCCESS == funcres)
            {
                /* Process AAD only, either first chunk or continuation */
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
                    t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
                    t_cmd.fNoRandomIV = 1U;
                    t_cmd.fEncrypt = operation->fEncrypt;
                    t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_AAD_INIT2CONT;
                    t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
                    t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_AUTHENCRYPT;
                    t_cmd.TempAssetId = operation->TempAssetId;
                    t_cmd.TotalAADLength = (uint32_t)bytes_available;
                    t_cmd.DataSize = 0U;
                    t_cmd.TotalDataLength = operation->plaintext_length;
                    t_cmd.TagSize = 16U;

                    /* Handle leftover block combined with the new AAD data */
                    if (leftover != 0U)
                    {
                        size = (PSA_SYM_ALGO_AES_BLOCK_SIZE - leftover);
                        (void)memcpy(&operation->leftover_AAD[leftover], ptr, size);
                        t_cmd.AAD_p = (const uint8_t *)operation->leftover_AAD;
                        t_cmd.AADSize = (uint32_t)PSA_SYM_ALGO_AES_BLOCK_SIZE;
                        operation->TotalAADLength += (uint32_t)PSA_SYM_ALGO_AES_BLOCK_SIZE;

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
                                bytes_to_process -= PSA_SYM_ALGO_AES_BLOCK_SIZE;
                                ptr = &ptr[size];
                                /* Mark initialization done */
                                operation->fUpdateAadDone = 255U;
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
                        if ((MAX_DMA_SIZE - (PSA_SYM_ALGO_AES_BLOCK_SIZE- 1U)) < bytes_to_process)
                        {
                            size = (MAX_DMA_SIZE - (PSA_SYM_ALGO_AES_BLOCK_SIZE - 1U));
                        }
                        else
                        {
                            size = (uint32_t)bytes_to_process;
                        }
                        t_cmd.AAD_p = (const uint8_t *)ptr;
                        t_cmd.AADSize = size;
                        t_cmd.TotalAADLength = (uint32_t)bytes_available;
                        operation->TotalAADLength += (uint32_t)size;

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
                                /* Mark initialization done */
                                operation->fUpdateAadDone = 255U;
                            }
                        }
                        else
                        {
                            /* MISRA - Intentially empty */
                        }
                    }
                    if (PSA_SUCCESS == funcres)
                    {
                        /* Handle update leftover data */
                        operation->leftover_nbytes_AAD = new_leftover;
                        if (0U != new_leftover)
                        {
                            (void)memcpy(operation->leftover_AAD, ptr, new_leftover);
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
            else
            {
                /* MISRA - Intentially empty */
            }
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_aead_update
 */
psa_status_t
psa_aead_update(psa_aead_operation_t * operation,
                const uint8_t * input,
                size_t input_length,
                uint8_t * output,
                size_t output_size,
                size_t * output_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_CipherAE_t t_cmd;
    VexTokenRslt_CipherAE_t t_res;
    uint32_t leftover;
    uint32_t new_leftover;
    uint64_t bytes_available;
    size_t bytes_to_process;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        (NULL == input) ||
        (0U == input_length) ||
        (NULL == output) ||
        (0U == output_size) ||
        (NULL == output_length))
    {
        funcres = PSA_ERROR_DATA_INVALID;
    }
    else if ((PSA_AEAD_STATE_SET_NONCE != operation->aead_state) &&
             (PSA_AEAD_STATE_UPDATE_AAD != operation->aead_state) &&
             (PSA_AEAD_STATE_UPDATE != operation->aead_state))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if ((input_length > operation->plaintext_length) ||
             (operation->ad_length !=
             (operation->TotalAADLength + operation->leftover_nbytes_AAD)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else if (output_size < PSA_AEAD_UPDATE_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type), operation->Mode, input_length))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        operation->aead_state = PSA_AEAD_STATE_UPDATE;

        leftover = operation->leftover_nbytes_data;
        bytes_available = (uint64_t)leftover + input_length;
        new_leftover = (uint32_t)bytes_available % PSA_SYM_ALGO_AES_BLOCK_SIZE;
        if (0U == new_leftover)
        {
            new_leftover = PSA_SYM_ALGO_AES_BLOCK_SIZE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        bytes_to_process = (size_t)(bytes_available - new_leftover);
        if (0U == bytes_to_process)
        {
            (void)memcpy(&operation->leftover_data[leftover], input,
                         input_length);
            operation->leftover_nbytes_data += (uint32_t)input_length;
            *output_length = 0U;
        }
        else
        {
            const uint8_t * ptr = input;
            uint32_t size;

            (void)memset(&t_res, 0, sizeof(t_res));
            if (PSA_ALG_CCM == operation->Mode)
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CCM;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_NONE;
                (void)memcpy(t_cmd.NonceHashKey, operation->nonce, operation->nonce_length);
                t_cmd.NonceHashKeySize = operation->nonce_length;
            }
            else if (PSA_ALG_GCM == operation->Mode)
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_GCM;
                t_cmd.GCMMode = PSA_SYM_MODE_GCM_AUTO;
                (void)memcpy(t_cmd.IV, operation->nonce, operation->nonce_length);
                t_cmd.NonceHashKeySize = 0U;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            if (PSA_SUCCESS == funcres)
            {
                /* Process data only, either first chunk or continuation */
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
                    if (0U == operation->fUpdateDone)
                    {
                        if (0U == operation->leftover_nbytes_AAD)
                        {
                            t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_INIT2CONT;
                            t_cmd.AADSize = 0U;
                        }
                        else
                        {
                            t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_AAD_FINAL2INIT_DATA;
                            t_cmd.AADSize = operation->leftover_nbytes_AAD;
                        }
                    }
                    else
                    {
                        t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_CONT2CONT;
                        t_cmd.AADSize = 0U;
                    }
                    t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
                    t_cmd.fNoRandomIV = 1U;
                    t_cmd.fEncrypt = operation->fEncrypt;
                    t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
                    t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_AUTHENCRYPT;
                    t_cmd.TempAssetId = operation->TempAssetId;
                    t_cmd.TotalDataLength = operation->plaintext_length;
                    t_cmd.AAD_p = operation->leftover_AAD;
                    t_cmd.TotalAADLength = operation->ad_length;
                    t_cmd.TagSize = 16U;

                    /* Handle leftover block combined with the new data */
                    if (0U != leftover)
                    {
                        size = (PSA_SYM_ALGO_AES_BLOCK_SIZE - leftover);
                        (void)memcpy(&operation->leftover_data[leftover], ptr, size);
                        t_cmd.SrcData_p = (const uint8_t *)operation->leftover_data;
                        t_cmd.DataSize = (uint32_t)PSA_SYM_ALGO_AES_BLOCK_SIZE;
                        *output_length = (size_t)PSA_SYM_ALGO_AES_BLOCK_SIZE;
                        t_cmd.DstData_p = output;
                        operation->TotalDataLength += (uint32_t)PSA_SYM_ALGO_AES_BLOCK_SIZE;

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
                                bytes_to_process -= PSA_SYM_ALGO_AES_BLOCK_SIZE;
                                ptr = &ptr[size];

                                /* Mark initialization done */
                                operation->fUpdateDone = 255U;
                                t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_CONT2CONT;
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
                        if ((MAX_DMA_SIZE - (PSA_SYM_ALGO_AES_BLOCK_SIZE- 1U)) < bytes_to_process)
                        {
                            size = (MAX_DMA_SIZE - (PSA_SYM_ALGO_AES_BLOCK_SIZE - 1U));
                        }
                        else
                        {
                            size = (uint32_t)bytes_to_process;
                        }
                        t_cmd.SrcData_p = (const uint8_t *)ptr;
                        t_cmd.DataSize = size;
                        *output_length += (size_t)size;
                        t_cmd.TotalDataLength = operation->plaintext_length;
                        operation->TotalDataLength += (uint32_t)size;
                        if (0U != leftover)
                        {
                            t_cmd.DstData_p = &output[PSA_SYM_ALGO_AES_BLOCK_SIZE];
                        }
                        else
                        {
                            t_cmd.DstData_p = output;
                        }
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

                                /* Mark initialization done */
                                operation->fUpdateDone = 255U;
                                t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_CONT2CONT;
                            }
                        }
                        else
                        {
                            /* MISRA - Intentially empty */
                        }
                    }
                    if (PSA_SUCCESS == funcres)
                    {
                        /* Handle update leftover data */
                        operation->leftover_nbytes_data = new_leftover;
                        if (0U != new_leftover)
                        {
                            (void)memcpy(operation->leftover_data, ptr, new_leftover);
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
            else
            {
                /* MISRA - Intentially empty */
            }
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_aead_finish
 */
psa_status_t
psa_aead_finish(psa_aead_operation_t * operation,
                uint8_t * ciphertext,
                size_t ciphertext_size,
                size_t * ciphertext_length,
                uint8_t * tag,
                size_t tag_size,
                size_t * tag_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_CipherAE_t t_cmd;
    VexTokenRslt_CipherAE_t t_res;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        ((NULL == ciphertext) && (0U != ciphertext_size)) ||
        (NULL == ciphertext_length) ||
        (NULL == tag) ||
        (0U == tag_size) ||
        (NULL == tag_length) ||
        (0U == operation->fEncrypt))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if ((PSA_AEAD_STATE_UPDATE != operation->aead_state) &&
             (PSA_AEAD_STATE_UPDATE_AAD != operation->aead_state))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else if (((operation->leftover_nbytes_data != 0U) &&
              (ciphertext_size < PSA_AEAD_FINISH_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type),
                                                                  operation->Mode))) ||
             (tag_size < PSA_AEAD_TAG_LENGTH(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type),
                                            (8U * (pKey->key_size)), operation->Mode)))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if ((operation->plaintext_length !=
             (operation->TotalDataLength + operation->leftover_nbytes_data)) ||
             (operation->ad_length !=
             (operation->TotalAADLength + operation->leftover_nbytes_AAD)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        t_cmd.fNoRandomIV = 1U;
        t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
        if (PSA_ALG_CCM == operation->Mode)
        {
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CCM;
            t_cmd.GCMMode = PSA_SYM_MODE_GCM_NONE;
            (void)memcpy(t_cmd.NonceHashKey, operation->nonce, operation->nonce_length);
            t_cmd.NonceHashKeySize = operation->nonce_length;
        }
        else if (PSA_ALG_GCM == operation->Mode)
        {
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_GCM;
            t_cmd.GCMMode = PSA_SYM_MODE_GCM_AUTO;
            (void)memcpy(t_cmd.IV, operation->nonce, operation->nonce_length);
            t_cmd.NonceHashKeySize = 0U;
        }
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
            if (PSA_SUCCESS == funcres)
            {
                if ((0U == operation->fUpdateDone) && (0U == operation->fUpdateAadDone))
                {
                    t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_INIT2FINAL;
                    t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                }
                else
                {
                    t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_CONT2FINAL;
                    t_cmd.TempAssetId = operation->TempAssetId;
                }
                t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
                t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_AUTHENCRYPT;
                t_cmd.fEncrypt = operation->fEncrypt;
                t_cmd.TagSize = (uint8_t)tag_size;
                if ((0U == operation->fUpdateDone) &&
                    (0U != operation->leftover_nbytes_AAD))
                {
                    t_cmd.AAD_p = operation->leftover_AAD;
                    t_cmd.AADSize = operation->leftover_nbytes_AAD;
                }
                else
                {
                    t_cmd.AADSize = 0U;
                }
                t_cmd.SrcData_p = operation->leftover_data;
                t_cmd.DataSize = operation->leftover_nbytes_data;
                t_cmd.TotalAADLength = operation->ad_length;
                t_cmd.TotalDataLength = operation->plaintext_length;
                t_cmd.DstData_p = ciphertext;

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
                        *ciphertext_length = (size_t)(operation->leftover_nbytes_data);
                        (void)memcpy(tag, t_res.Tag, tag_size);
                        *tag_length = t_cmd.TagSize;
                        (void)psaInt_KeyMgmtClrKeyInUse(operation->key);
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                        operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                        operation->key = PSA_KEY_ID_NULL;
#endif
                        if (PSA_ASSETID_INVALID != operation->TempAssetId)
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_aead_verify
 */
psa_status_t
psa_aead_verify(psa_aead_operation_t * operation,
                uint8_t * plaintext,
                size_t plaintext_size,
                size_t * plaintext_length,
                const uint8_t * tag,
                size_t tag_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_CipherAE_t t_cmd;
    VexTokenRslt_CipherAE_t t_res;
    psa_key_context_t *pKey = NULL;

    if ((NULL == operation) ||
        ((NULL == plaintext) && (0U != plaintext_size)) ||
        (NULL == plaintext_length) ||
        (NULL == tag) ||
        (0U == tag_length) ||
        (0U != operation->fEncrypt))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if ((PSA_AEAD_STATE_UPDATE != operation->aead_state) &&
             (PSA_AEAD_STATE_UPDATE_AAD != operation->aead_state))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else if (psaInt_KeyMgmtGetKey(operation->key, &pKey) != PSA_SUCCESS)
    {
        funcres = PSA_ERROR_INVALID_HANDLE;
    }
    else if ((operation->leftover_nbytes_data != 0U) &&
             (plaintext_size < PSA_AEAD_VERIFY_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type),
                                                           operation->Mode)))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if ((operation->plaintext_length !=
              (operation->TotalDataLength + operation->leftover_nbytes_data)) ||
             (operation->ad_length !=
              (operation->TotalAADLength + operation->leftover_nbytes_AAD)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        t_cmd.fNoRandomIV = 1U;
        t_cmd.Algorithm = (uint32_t)VEXTOKEN_ALGO_CIPHER_AES;
        if (PSA_ALG_CCM == operation->Mode)
        {
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_CCM;
            t_cmd.GCMMode = PSA_SYM_MODE_GCM_NONE;
            (void)memcpy(t_cmd.NonceHashKey, operation->nonce, operation->nonce_length);
            t_cmd.NonceHashKeySize = operation->nonce_length;
        }
        else if (PSA_ALG_GCM == operation->Mode)
        {
            t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_CIPHER_GCM;
            t_cmd.GCMMode = PSA_SYM_MODE_GCM_AUTO;
            (void)memcpy(t_cmd.IV, operation->nonce, operation->nonce_length);
        }
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
            if (PSA_SUCCESS == funcres)
            {
                if ((0U == operation->fUpdateDone) && (0U == operation->fUpdateAadDone))
                {
                    t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_INIT2FINAL;
                    t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                }
                else
                {
                    t_cmd.OpMode = (uint8_t)VEXTOKEN_MODE_CIPHER_AE_CONT2FINAL;
                    t_cmd.TempAssetId = operation->TempAssetId;
                }
                t_cmd.OpCode  = (uint32_t)VEXTOKEN_OPCODE_ENCRYPTION;
                t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_AUTHENCRYPT;
                t_cmd.fEncrypt = operation->fEncrypt;
                (void)memcpy(t_cmd.Tag, tag, tag_length);
                t_cmd.TagSize = (uint8_t)tag_length;
                if ((0U == operation->fUpdateDone) &&
                    (0U != operation->leftover_nbytes_AAD))
                {
                    t_cmd.AAD_p = operation->leftover_AAD;
                    t_cmd.AADSize = operation->leftover_nbytes_AAD;
                }
                else
                {
                    t_cmd.AADSize = 0U;
                }
                t_cmd.SrcData_p = operation->leftover_data;
                t_cmd.DataSize = operation->leftover_nbytes_data;
                t_cmd.TotalAADLength = operation->ad_length;
                t_cmd.TotalDataLength = operation->plaintext_length;
                t_cmd.DstData_p = plaintext;

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
                        funcres = PSA_ERROR_INVALID_SIGNATURE;
                    }
                    else
                    {
                        *plaintext_length = (size_t)(operation->leftover_nbytes_data);
                        (void)psaInt_KeyMgmtClrKeyInUse(operation->key);
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
                        operation->key = MBEDTLS_SVC_KEY_ID_NULL;
#else
                        operation->key = PSA_KEY_ID_NULL;
#endif
                        if (PSA_ASSETID_INVALID != operation->TempAssetId)
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_aead_abort
 */
psa_status_t
psa_aead_abort(psa_aead_operation_t * operation)
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
        (void)memset(operation, 0, sizeof(psa_aead_operation_t));
    }

    return funcres;
}


/* end of file adapter_psa_sym_aead.c */
