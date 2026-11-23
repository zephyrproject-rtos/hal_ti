/* adapter_psa_asym_key_agreement.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the Asymmetric crypto key agreement services.
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
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>

/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * psa_raw_key_agreement
 */
psa_status_t
psa_raw_key_agreement(psa_algorithm_t alg,
                      mbedtls_svc_key_id_t private_key,
                      const uint8_t * peer_key,
                      size_t peer_key_length,
                      uint8_t * output,
                      size_t output_size,
                      size_t * output_length)
{
    PsaPolicyMask_t AssetPolicy;
    psa_key_context_t * pKey = NULL;
    PsaAssetId_t DomainAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t PrvKeyAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t PubKeyAssetId = PSA_ASSETID_INVALID;
    PsaAssetId_t PubDataAssetId = PSA_ASSETID_INVALID;
    size_t CurveBits;
    size_t DataSize;
    psa_status_t funcres;
    uint8_t CurveFamily;
    uint8_t fECDH;
    uint8_t DataBuffer[2U * (PSA_ASYM_DATA_VHEADER + (4U * ((521U + 31U) / 32U)))];
    VexTokenCmd_PkAssetGenSharedSecret_t t_cmd;
    VexTokenRslt_Generic_t t_res;

    if (!(PSA_ALG_IS_RAW_KEY_AGREEMENT(alg)) ||
        (NULL == peer_key) || (0U == peer_key_length) ||
        (NULL == output) || (NULL == output_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        funcres = psaInt_KeyMgmtGetKey(private_key, &pKey);
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Key found
         * - Check the private key usage
         * - Check the output buffer size
         * - Read, check and convert the provided public key
         */
        if (PSA_KEY_USAGE_DERIVE != (pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(policy).MBEDTLS_PRIVATE(usage) & PSA_KEY_USAGE_DERIVE))
        {
            funcres = PSA_ERROR_NOT_PERMITTED;
        }
        else if (output_size <
                 (size_t)PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type),
                                                           pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(bits)))
        {
            funcres = PSA_ERROR_BUFFER_TOO_SMALL;
        }
        else
        {
            switch (alg)
            {
            case PSA_ALG_ECDH:
                if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type)))
                {
                    DataSize = sizeof(DataBuffer);
                    funcres = psaInt_KeyMgmtReadECPubKey(255U, peer_key, peer_key_length,
                                                         PSA_KEY_TYPE_ECC_GET_FAMILY(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type)),
                                                         pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(bits),
                                                         &CurveFamily, &CurveBits,
                                                         &fECDH,
                                                         DataBuffer, &DataSize);
                }
                else
                {
                    /* Safeguard: Should never happen, already blocked by
                     *            psa_import_key() or psa_generate_key() */
                    funcres = PSA_ERROR_INVALID_ARGUMENT;
                }
                break;
            default:
                funcres = PSA_ERROR_NOT_SUPPORTED;
                break;
            }
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_SUCCESS == funcres)
    {
        if (0U == fECDH)
        {
            /* Invalid public key */
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else
        {
            /* Create and load public key */
            AssetPolicy = (pKey->AssetPolicy & (~(EIP130_ASSET_POLICY_PRIVATEDATA |
                                                  EIP130_ASSET_POLICY_AC_NDPA|
                                                  EIP130_ASSET_POLICY_STANY))) |
                          EIP130_ASSET_POLICY_PUBLICDATA;
            funcres = psaInt_AssetAlloc(AssetPolicy, DataSize, &PubKeyAssetId);
            if (PSA_SUCCESS == funcres)
            {
                funcres = psaInt_AssetLoadPlaintext(PubKeyAssetId,
                                                    DataBuffer, DataSize);
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
        /* Install the curve */
        funcres = psaInt_AsymEccInstallCurve(CurveFamily, CurveBits,
                                             &DomainAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Create and load private key, when needed */
        funcres = psaInt_KeyMgmtLoadKey(pKey, &PrvKeyAssetId, 0, 0, NULL, 0, NULL);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Create public data object for the Shared Secret */
        AssetPolicy = EIP130_ASSET_POLICY_NONMODIFIABLE |
                      EIP130_ASSET_POLICY_NODOMAIN |
                      EIP130_ASSET_POLICY_PUBLICDATA |
                      EIP130_ASSET_POLICY_GENERICDATA |
                      EIP130_ASSET_POLICY_GDPUBLICDATA;
        if (!psaInt_IsAccessSecure())
        {
            AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        DataSize = PSA_ASYM_DATA_SIZE_B2WB(CurveBits);
        funcres = psaInt_AssetAlloc(AssetPolicy, DataSize, &PubDataAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Generate the Shared Secret */
        t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_PUBLIC_KEY;
        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_PK_WITHASSETS;
        if (PSA_ECC_FAMILY_MONTGOMERY ==
            PSA_KEY_TYPE_ECC_GET_FAMILY(pKey->attributes.MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type)))
        {
            t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_CURVE25519_GEN_SHARED_SECRET;
        }
        else
        {
            t_cmd.Method = (uint32_t)VEXTOKEN_PKAS_ECDH_GEN_SKEYPAIR_SHARED_SECRET;
        }
        t_cmd.ModulusSizeInBits = (uint32_t)CurveBits;
        t_cmd.DivisorSizeInBits = (uint32_t)CurveBits;
        t_cmd.PubKeyAssetId = (uint32_t)PubKeyAssetId;
        t_cmd.PrivKeyAssetId = (uint32_t)PrvKeyAssetId;
        t_cmd.DomainAssetId = (uint32_t)DomainAssetId;
        t_cmd.PubKey2AssetId = PSA_ASSETID_INVALID;
        t_cmd.PrivKey2AssetId = PSA_ASSETID_INVALID;
        t_cmd.OtherInfo_p = NULL;
        t_cmd.OtherInfoSize = 0U;
        t_cmd.LocalEphPubKey = NULL;
        t_cmd.LocalEphPubKeySize = 0U;
        t_cmd.fSaveSharedSecret = 1U;
        t_cmd.AssetIdListSize = 1U;
        t_cmd.AssetIdList[0] = (uint32_t)PubDataAssetId;
        t_res.Result = 0;

        funcres = psaInt_ExchangeToken((VexTokenCmd_Generic_t *)&t_cmd,
                                       sizeof(t_cmd), &t_res, sizeof(t_res));
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
    if (PSA_SUCCESS == funcres)
    {
        /* Read the Shared Secret */
        funcres = psaInt_PublicDataRead(PubDataAssetId, output,
                                        DataSize, &DataSize);
        if (PSA_SUCCESS == funcres)
        {
            /* Set actual output data length */
            *output_length = PSA_ASYM_DATA_SIZE_B2B(CurveBits);
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
    if (PSA_ASSETID_INVALID != PrvKeyAssetId)
    {
        (void)psaInt_KeyMgmtReleaseKey(pKey);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != PubDataAssetId)
    {
        (void)psaInt_AssetFree(PubDataAssetId);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (PSA_ASSETID_INVALID != PubKeyAssetId)
    {
        (void)psaInt_AssetFree(PubKeyAssetId);
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

    if (PSA_SUCCESS != funcres)
    {
        /* In case of an error, the output may be used as a key to protect
         * sensitive data. So, generate a random key that results most likely
         * in decryption or verification error.
         * The reason for doing this is that it is better than filling the
         * buffer with some constant data such as zeros, which will result
         * in the data being protected with a reproducible (easily knowable)
         * key.
         */
        if (NULL != output)
        {
            (void)psa_generate_random(output, output_size);
            if (NULL != output_length)
            {
                *output_length = output_size;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
        else if (NULL != output_length)
        {
            *output_length = 0U;
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


/* end of file adapter_psa_asym_key_agreement.c */