/* adapter_psa_asym_encryption.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the Asymmetric crypto encryption services.
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
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>                // VexTokenCmd_*_t, VexTokenRslt_*_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>

/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * psa_asymmetric_encrypt
 *
 * Encrypt a short message with public key.
 */
psa_status_t
psa_asymmetric_encrypt(mbedtls_svc_key_id_t key,
                       psa_algorithm_t alg,
                       const uint8_t * input,
                       size_t input_length,
                       const uint8_t * salt,
                       size_t salt_length,
                       uint8_t * output,
                       size_t output_size,
                       size_t * output_length)
{
    psa_status_t funcres;
    VexTokenCmd_PkAssetWrap_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    PsaAssetId_t AssetId = PSA_ASSETID_INVALID;
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
    else if (output_size < PSA_ASYMMETRIC_ENCRYPT_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type),
                                                              pKey->modulus_size, alg))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if (!(PSA_ALG_IS_ASYMMETRIC_ENCRYPTION(alg)) ||
             (NULL == input) ||
             (0U == input_length) ||
             ((NULL == salt) && (0U != salt_length)) ||
             ((NULL != salt) && (0U == salt_length)) ||
             (NULL == output) ||
             (NULL == output_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (208U < salt_length)
    {
        funcres = PSA_ERROR_NOT_SUPPORTED;
    }
    else
    {
        funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0, NULL, 0, NULL);
        if (PSA_SUCCESS == funcres)
        {
            if (PSA_ALG_IS_RSA_OAEP(alg))
            {
                switch (PSA_ALG_GET_HASH(alg))
                {
                case PSA_ALG_SHA_1:
                case PSA_ALG_SHA_224:
                case PSA_ALG_SHA_256:
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
                case PSA_ALG_SHA_384:
                case PSA_ALG_SHA_512:
#endif
                    break;
                default:
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                    break;
                }
                t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_RSA_OAEP_WRAP_STRING;
            }
            else if (PSA_ALG_RSA_PKCS1V15_CRYPT == alg)
            {
                t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_RSA_PKCS1V15_WRAP;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            if (PSA_SUCCESS == funcres)
            {
                AssetPolicy = EIP130_ASSET_POLICY_NONMODIFIABLE |
                              EIP130_ASSET_POLICY_NODOMAIN |
                              EIP130_ASSET_POLICY_PUBLICDATA |
                              EIP130_ASSET_POLICY_GENERICDATA |
                              EIP130_ASSET_POLICY_GDPUBLICDATA |
                              EIP130_ASSET_POLICY_EXPORTABLE;
                if (!psaInt_IsAccessSecure())
                {
                    AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                funcres = psaInt_AssetAlloc(AssetPolicy, input_length, &AssetId);
                if (PSA_SUCCESS == funcres)
                {
                    funcres = psaInt_AssetLoadPlaintext(AssetId, input, input_length);
                    if (PSA_SUCCESS == funcres)
                    {
                        /* Format service request (key AssetId is already filled in) */
                        t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_PUBLIC_KEY;
                        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_PK_WITHASSETS;
                        t_cmd.ModulusSizeInBits = (uint32_t)pKey->modulus_size;
                        t_cmd.AssetId = AssetId;
                        t_cmd.DomainAssetId = PSA_ASSETID_INVALID;
                        if (0U != salt_length)
                        {
                            t_cmd.AdditionalInputSize = (uint32_t)salt_length;
                            (void)memcpy(t_cmd.AdditionalInput, salt, salt_length);
                        }
                        else
                        {
                            t_cmd.AdditionalInputSize = (uint32_t)salt_length;
                        }
                        t_cmd.Data_p = output;
                        t_cmd.DataSize = (uint32_t)output_size;
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
                                *output_length = (size_t)PSA_BITS_TO_BYTES(pKey->modulus_size);
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
                    (void)psaInt_AssetFree(AssetId);
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_asymmetric_decrypt
 *
 * decrypt a short message with private key.
 */
psa_status_t
psa_asymmetric_decrypt(mbedtls_svc_key_id_t key,
                       psa_algorithm_t alg,
                       const uint8_t * input,
                       size_t input_length,
                       const uint8_t * salt,
                       size_t salt_length,
                       uint8_t * output,
                       size_t output_size,
                       size_t * output_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_PkAssetWrap_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    PsaAssetId_t AssetId = PSA_ASSETID_INVALID;
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
    /* Note: The size check will be done later because for this implementation
     *       the actual Asset size determines to size of the required output
     *       buffer. */
    else if (!(PSA_ALG_IS_ASYMMETRIC_ENCRYPTION(alg)) ||
             (NULL == input) ||
             (0U == input_length) ||
             ((NULL == salt) && (0U != salt_length)) ||
             ((NULL != salt) && (0U == salt_length)) ||
             (NULL == output) ||
             (NULL == output_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (208U < salt_length)
    {
        funcres = PSA_ERROR_NOT_SUPPORTED;
    }
    else
    {
        funcres = psaInt_KeyMgmtLoadKey(pKey, &t_cmd.KeyAssetId, 0, 0, NULL, 0, NULL);
        if (PSA_SUCCESS == funcres)
        {
            if (PSA_ALG_IS_RSA_OAEP(alg))
            {
                switch (PSA_ALG_GET_HASH(alg))
                {
                case PSA_ALG_SHA_1:
                case PSA_ALG_SHA_224:
                case PSA_ALG_SHA_256:
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
                case PSA_ALG_SHA_384:
                case PSA_ALG_SHA_512:
#endif
                    break;
                default:
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                    break;
                }
                t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_RSA_OAEP_UNWRAP_STRING;
            }
            else if (PSA_ALG_RSA_PKCS1V15_CRYPT == alg)
            {
                t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_RSA_PKCS1V15_UNWRAP;
            }
            else
            {
                funcres = PSA_ERROR_INVALID_ARGUMENT;
            }
            if (PSA_SUCCESS == funcres)
            {
                AssetPolicy = EIP130_ASSET_POLICY_NONMODIFIABLE |
                              EIP130_ASSET_POLICY_NODOMAIN |
                              EIP130_ASSET_POLICY_PUBLICDATA |
                              EIP130_ASSET_POLICY_GENERICDATA |
                              EIP130_ASSET_POLICY_GDPUBLICDATA |
                              EIP130_ASSET_POLICY_EXPORTABLE;
                if (!psaInt_IsAccessSecure())
                {
                    AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                funcres = psaInt_AssetAlloc(AssetPolicy, output_size, &AssetId);
                if (PSA_SUCCESS == funcres)
                {
                    t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_PUBLIC_KEY;
                    t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_PK_WITHASSETS;
                    t_cmd.ModulusSizeInBits = (uint32_t)pKey->modulus_size;
                    t_cmd.KeyAssetId = pKey->key_assetId;
                    t_cmd.AssetId = AssetId;
                    t_cmd.DomainAssetId = PSA_ASSETID_INVALID;
                    if (0U != salt_length)
                    {
                        t_cmd.AdditionalInputSize = (uint32_t)salt_length;
                        (void)memcpy(t_cmd.AdditionalInput, salt, salt_length);
                    }
                    else
                    {
                        t_cmd.AdditionalInputSize = (uint32_t)salt_length;
                    }
                    t_cmd.Data_p = input;
                    t_cmd.DataSize = (uint32_t)input_length;
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
                            funcres = psaInt_PublicDataRead(AssetId, output, output_size, output_length);
                        }
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                    (void)psaInt_AssetFree(AssetId);
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

    return funcres;
}


/* end of file adapter_psa_asym_encryption.c */