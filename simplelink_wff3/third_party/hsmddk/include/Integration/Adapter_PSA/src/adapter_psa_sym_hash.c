/* adapter_psa_sym_hash.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the symmetric crypto hash services.
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
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#define PSA_HASH_STATE_INIT   0U
#define PSA_HASH_STATE_SETUP  1U
#define PSA_HASH_STATE_UPDATE 2U
#define PSA_HASH_STATE_RESUME 3U

#define PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH ((size_t)4U)

#define PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(alg) \
    ( ((alg) == PSA_ALG_SHA_1)  ? 8U  :                 \
      ((alg) == PSA_ALG_SHA_224)? 8U  :                 \
      ((alg) == PSA_ALG_SHA_256) ? 8U  :                \
      ((alg) == PSA_ALG_SHA_384) ? 16U :                \
      ((alg) == PSA_ALG_SHA_512) ? 16U :                \
      0U )

#define PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(alg) \
    ( ((alg) == PSA_ALG_SHA_1)   ? 20U :              \
      ((alg) == PSA_ALG_SHA_224) ? 32U :              \
      ((alg) == PSA_ALG_SHA_256) ? 32U :              \
      ((alg) == PSA_ALG_SHA_384) ? 64U :              \
      ((alg) == PSA_ALG_SHA_512) ? 64U :              \
      0U )

#define PSA_HASH_SUSPEND_OUTPUT_SIZE(alg)               \
    ( PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH +         \
      PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(alg) + \
      PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(alg) +   \
      PSA_HASH_BLOCK_LENGTH(alg) - 1U )


/*----------------------------------------------------------------------------
 * psa_hash_compute
 */
psa_status_t
psa_hash_compute(psa_algorithm_t alg,
                 const uint8_t * input,
                 size_t input_length,
                 uint8_t * hash,
                 size_t hash_size,
                 size_t * hash_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_Hash_t t_cmd;
    VexTokenRslt_Hash_t t_res;
    size_t block_size = 0U;
    size_t DigestNBytes = 0U;
    uint64_t TotalMessageLength = (uint64_t)input_length;

    if ((NULL == input) ||
        (0U == input_length) ||
        (NULL == hash) ||
        (0U == hash_size) ||
        (NULL == hash_length) ||
        (!PSA_ALG_IS_HASH(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        {
            block_size = PSA_HASH_BLOCK_LENGTH(alg);
            DigestNBytes = PSA_HASH_LENGTH(alg);
        }
        if (DigestNBytes > hash_size)
        {
            funcres = PSA_ERROR_BUFFER_TOO_SMALL;
        }
        else if (0U == DigestNBytes)
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if ((MAX_DMA_SIZE - (block_size - 1U)) < input_length)
        {
            funcres = PSA_ERROR_NOT_SUPPORTED;
        }
        else
        {
            (void)memset(&t_cmd, 0, sizeof(t_cmd));
            switch (alg)
            {
            case PSA_ALG_SHA_1:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA1;
                break;
            case PSA_ALG_SHA_224:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA224;
                break;
            case PSA_ALG_SHA_256:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA256;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case PSA_ALG_SHA_384:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA384;
                break;
            case PSA_ALG_SHA_512:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA512;
                break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
            case PSA_ALG_SHA3_224:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA3_224;
                TotalMessageLength %= (uint64_t)block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = (uint64_t)block_size;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_256:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA3_256;
                TotalMessageLength %= (uint64_t)block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = (uint64_t)block_size;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_384:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA3_384;
                TotalMessageLength %= (uint64_t)block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = (uint64_t)block_size;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_512:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA3_512;
                TotalMessageLength %= (uint64_t)block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = (uint64_t)block_size;
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
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Format service request */
        t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_HASH;
        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_NOT_USED;
        t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
        t_cmd.Data_p = input;
        t_cmd.DataSize = (uint32_t)input_length;
        t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength);
        t_cmd.TotalMessageLengthHi = (uint32_t)(TotalMessageLength >> 32);

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
                (void)memcpy(hash, t_res.Digest, DigestNBytes);
                *hash_length = DigestNBytes;
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
 * psa_hash_compare
 */
psa_status_t
psa_hash_compare(psa_algorithm_t alg,
                 const uint8_t * input,
                 size_t input_length,
                 const uint8_t * hash,
                 size_t hash_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    VexTokenCmd_Hash_t t_cmd;
    VexTokenRslt_Hash_t t_res;
    size_t block_size = 0U;
    size_t DigestNBytes = 0U;
    uint64_t TotalMessageLength = (uint64_t)input_length;

    if ((NULL == input) ||
        (0U == input_length) ||
        (NULL == hash) ||
        (0U == hash_length) ||
        (!PSA_ALG_IS_HASH(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        {
            block_size = PSA_HASH_BLOCK_LENGTH(alg);
            DigestNBytes = PSA_HASH_LENGTH(alg);
        }
        if (0U == DigestNBytes)
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if ((MAX_DMA_SIZE - (block_size - 1U)) < input_length)
        {
            funcres = PSA_ERROR_NOT_SUPPORTED;
        }
        else
        {
            (void)memset(&t_cmd, 0, sizeof(t_cmd));
            switch (alg)
            {
            case PSA_ALG_SHA_1:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA1;
                break;
            case PSA_ALG_SHA_224:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA224;
                break;
            case PSA_ALG_SHA_256:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA256;
                break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
            case PSA_ALG_SHA_384:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA384;
                break;
            case PSA_ALG_SHA_512:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA512;
                break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
            case PSA_ALG_SHA3_224:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA3_224;
                TotalMessageLength %= (uint64_t)block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = (uint64_t)block_size;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_256:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA3_256;
                TotalMessageLength %= (uint64_t)block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = (uint64_t)block_size;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_384:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA3_384;
                TotalMessageLength %= (uint64_t)block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = (uint64_t)block_size;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
                break;
            case PSA_ALG_SHA3_512:
                t_cmd.Algorithm = VEXTOKEN_ALGO_HASH_SHA3_512;
                TotalMessageLength = ((uint64_t)input_length % block_size);
                TotalMessageLength %= (uint64_t)block_size;
                if (0U == TotalMessageLength)
                {
                    TotalMessageLength = (uint64_t)block_size;
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
    }
    if (PSA_SUCCESS == funcres)
    {
        /* Format service request */
        t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_HASH;
        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_NOT_USED;
        t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
        t_cmd.Data_p = input;
        t_cmd.DataSize = (uint32_t)input_length;
        t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength);
        t_cmd.TotalMessageLengthHi = (uint32_t)(TotalMessageLength >> 32);

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
                if (0 != memcmp(hash, t_res.Digest, hash_length))
                {
                    funcres = PSA_ERROR_INVALID_SIGNATURE;
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * get_hash_asset_policy
 */
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
static PsaPolicyMask_t
get_hash_asset_policy(uint32_t alg)
{
    PsaPolicyMask_t AssetPolicy = EIP130_ASSET_POLICY_SYM_TEMP |
                                  EIP130_ASSET_POLICY_SCUIHASH |
                                  EIP130_ASSET_POLICY_SCDIRENCGEN;

    switch (alg)
    {
    case PSA_ALG_SHA_1:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA1;
        break;
    case PSA_ALG_SHA_224:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA224;
        break;
    case PSA_ALG_SHA_256:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA256;
        break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
    case PSA_ALG_SHA_384:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA384;
        break;
    case PSA_ALG_SHA_512:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA512;
        break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
    case PSA_ALG_SHA3_224:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_224;
        break;
    case PSA_ALG_SHA3_256:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_256;
        break;
    case PSA_ALG_SHA3_384:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_384;
        break;
    case PSA_ALG_SHA3_512:
        AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_512;
        break;
#endif
    default:
        AssetPolicy = 0U;
        break;
    }

    return AssetPolicy;
}
#endif


/*----------------------------------------------------------------------------
 * get_digest_size
 */
static size_t
get_digest_size(uint32_t alg,
                bool fupdate)
{
    size_t DigestNBytes;

    switch (alg)
    {
    case PSA_ALG_SHA_1:
        DigestNBytes = (160U / 8U);
        break;
    case PSA_ALG_SHA_224:
        if (fupdate)
        {
            DigestNBytes = (256U / 8U);
        }
        else
        {
            DigestNBytes = (224U / 8U);
        }
        break;
    case PSA_ALG_SHA_256:
        DigestNBytes = (256U / 8U);
        break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
    case PSA_ALG_SHA_384:
        if (fupdate)
        {
            DigestNBytes = (512U / 8U);
        }
        else
        {
            DigestNBytes = (384U / 8U);
        }
        break;
    case PSA_ALG_SHA_512:
        DigestNBytes = (512U / 8U);
        break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
    case PSA_ALG_SHA3_224:
        if (fupdate)
        {
            DigestNBytes = (1600U / 8U);
        }
        else
        {
            DigestNBytes = (224U / 8U);
        }
        break;
    case PSA_ALG_SHA3_256:
        if (fupdate)
        {
            DigestNBytes = (1600U / 8U);
        }
        else
        {
            DigestNBytes = (256U / 8U);
        }
        break;
    case PSA_ALG_SHA3_384:
        if (fupdate)
        {
            DigestNBytes = (1600U / 8U);
        }
        else
        {
            DigestNBytes = (384U / 8U);
        }
        break;
    case PSA_ALG_SHA3_512:
        if (fupdate)
        {
            DigestNBytes = (1600U / 8U);
        }
        else
        {
            DigestNBytes = (512U / 8U);
        }
        break;
#endif
#endif
    default:
        DigestNBytes = 0U;
        break;
    }

    return DigestNBytes;
}


/*----------------------------------------------------------------------------
 * psa_to_vex_alg
 */
static uint32_t
psa_to_vex_alg(uint32_t alg)
{
    uint32_t vex_alg;

    switch (alg)
    {
    case PSA_ALG_SHA_1:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA1;
        break;
    case PSA_ALG_SHA_224:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA224;
        break;
    case PSA_ALG_SHA_256:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA256;
        break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
    case PSA_ALG_SHA_384:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA384;
        break;
    case PSA_ALG_SHA_512:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA512;
        break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
    case PSA_ALG_SHA3_224:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA3_224;
        break;
    case PSA_ALG_SHA3_256:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA3_256;
        break;
    case PSA_ALG_SHA3_384:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA3_384;
        break;
    case PSA_ALG_SHA3_512:
        vex_alg = VEXTOKEN_ALGO_HASH_SHA3_512;
        break;
#endif
#endif
    default:
        vex_alg = 0U;
        break;
    }

    return vex_alg;
}


/*----------------------------------------------------------------------------
 * psa_hash_setup
 */
psa_status_t
psa_hash_setup(psa_hash_operation_t * operation,
               psa_algorithm_t alg)
{
    psa_status_t funcres = PSA_SUCCESS;

    if ((NULL == operation) ||
        (!PSA_ALG_IS_HASH(alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_HASH_STATE_INIT != operation->hash_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        {
            operation->block_size = PSA_HASH_BLOCK_LENGTH(alg);
        }
        switch (alg)
        {
        case PSA_ALG_SHA_1:
            operation->alg = PSA_ALG_SHA_1;
            break;
        case PSA_ALG_SHA_224:
            operation->alg = PSA_ALG_SHA_224;
            break;
        case PSA_ALG_SHA_256:
            operation->alg = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case PSA_ALG_SHA_384:
            operation->alg = PSA_ALG_SHA_384;
            break;
        case PSA_ALG_SHA_512:
            operation->alg = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case PSA_ALG_SHA3_224:
            operation->alg = PSA_ALG_SHA3_224;
            break;
        case PSA_ALG_SHA3_256:
            operation->alg = PSA_ALG_SHA3_256;
            break;
        case PSA_ALG_SHA3_384:
            operation->alg = PSA_ALG_SHA3_384;
            break;
        case PSA_ALG_SHA3_512:
            operation->alg = PSA_ALG_SHA3_512;
            break;
#endif
#endif
        default:
            funcres = PSA_ERROR_NOT_SUPPORTED;
            break;
        }
    }

#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
    if (PSA_SUCCESS == funcres)
    {
        PsaPolicyMask_t AssetPolicy;
        size_t DigestNBytes;

        DigestNBytes = get_digest_size(operation->alg, true);
        if (0U != DigestNBytes)
        {
            AssetPolicy = get_hash_asset_policy(operation->alg);
            if (!psaInt_IsAccessSecure())
            {
                AssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            funcres = psaInt_AssetAlloc(AssetPolicy, DigestNBytes,
                                        &operation->TempAssetId);
            if (PSA_SUCCESS != funcres)
            {
                funcres = PSA_ERROR_HARDWARE_FAILURE;
            }
            else
            {
                operation->hash_state = PSA_HASH_STATE_SETUP;
                operation->fUpdateDone = 0U;
                operation->TotalMessageLength = 0U;
                operation->leftover_nbytes = 0U;
            }
        }
        else
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
#else
    if (PSA_SUCCESS == funcres)
    {
        operation->hash_state = PSA_HASH_STATE_SETUP;
        operation->fUpdateDone = 0U;
        operation->TempAssetId = PSA_ASSETID_INVALID;
        operation->TotalMessageLength = 0U;
        operation->leftover_nbytes = 0U;
    }
    else
    {
        /* MISRA - Intentially empty */
    }
#endif

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_hash_update
 */
psa_status_t
psa_hash_update(psa_hash_operation_t * operation,
                const uint8_t * input,
                size_t input_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    uint32_t leftover;
    uint32_t new_leftover;
    uint64_t bytes_available;
    size_t bytes_to_process;
    VexTokenCmd_Hash_t t_cmd;
    VexTokenRslt_Hash_t t_res;

    if ((NULL == operation) ||
        (NULL == input) ||
        (0U == input_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if ((PSA_HASH_STATE_INIT == operation->hash_state) ||
             (0U == operation->block_size))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        operation->hash_state = PSA_HASH_STATE_UPDATE;

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

            /* Format service request */
            t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_HASH;
            t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_NOT_USED;
            t_cmd.Algorithm = psa_to_vex_alg(operation->alg);
            t_cmd.TotalMessageLengthLo = 0U;
            t_cmd.TotalMessageLengthHi = 0U;
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
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
                t_cmd.TempAssetId = operation->TempAssetId;
#else
                t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                (void)memset(t_cmd.Digest, 0, sizeof(t_cmd.Digest));
                (void)memcpy(t_cmd.Digest, operation->inter_digest,
                             sizeof(operation->inter_digest));
#endif
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

#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
                        /* Save the intermediate Digest for the next operation */
                        (void)memcpy(operation->inter_digest, t_res.Digest,
                                     sizeof(operation->inter_digest));
#endif
                    }
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
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
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
                t_cmd.TempAssetId = operation->TempAssetId;
#else
                t_cmd.TempAssetId = PSA_ASSETID_INVALID;
                (void)memset(t_cmd.Digest, 0, sizeof(t_cmd.Digest));
                (void)memcpy(t_cmd.Digest, operation->inter_digest,
                             sizeof(operation->inter_digest));
#endif
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

#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
                        /* Save the intermediate Digest for the next operation */
                        (void)memcpy(operation->inter_digest, t_res.Digest,
                                     sizeof(operation->inter_digest));
#endif
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
                if (0U != new_leftover)
                {
                    (void)memcpy(operation->leftover_buf, ptr, new_leftover);
                }
            }
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_hash_finish
 */
psa_status_t
psa_hash_finish(psa_hash_operation_t * operation,
                uint8_t * hash,
                size_t hash_size,
                size_t * hash_length)
{
    psa_status_t funcres = PSA_SUCCESS;
    size_t DigestNBytes;
    uint64_t TotalMessageLength;
    VexTokenCmd_Hash_t t_cmd;
    VexTokenRslt_Hash_t t_res;

    if ((NULL == operation) ||
        (NULL == hash) ||
        (0U == hash_size) ||
        (NULL == hash_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (((PSA_HASH_STATE_UPDATE != operation->hash_state) &&
              (PSA_HASH_STATE_RESUME != operation->hash_state)) ||
             (0U == operation->block_size))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        DigestNBytes = get_digest_size(operation->alg, false);
        if (DigestNBytes > hash_size)
        {
            funcres = PSA_ERROR_BUFFER_TOO_SMALL;
        }
        else if (0U == DigestNBytes)
        {
            funcres = PSA_ERROR_INVALID_ARGUMENT;
        }
        else
        {
            TotalMessageLength = operation->TotalMessageLength + operation->leftover_nbytes;
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
            if ((PSA_ALG_SHA3_224 == operation->alg) ||
                (PSA_ALG_SHA3_256 == operation->alg) ||
                (PSA_ALG_SHA3_384 == operation->alg) ||
                (PSA_ALG_SHA3_512 == operation->alg))
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
#endif
#endif

            /* Format service request */
            t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_HASH;
            t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_NOT_USED;
            t_cmd.Algorithm = psa_to_vex_alg(operation->alg);
            if (operation->fUpdateDone != 0U)
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_CONT2FINAL;
            }
            else
            {
                t_cmd.Mode = (uint32_t)VEXTOKEN_MODE_HASH_MAC_INIT2FINAL;
            }
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
            t_cmd.TempAssetId = operation->TempAssetId;
#else
            t_cmd.TempAssetId = PSA_ASSETID_INVALID;
            (void)memset(t_cmd.Digest, 0, sizeof(t_cmd.Digest));
            (void)memcpy(t_cmd.Digest, operation->inter_digest,
                         sizeof(operation->inter_digest));
#endif
            t_cmd.Data_p = operation->leftover_buf;
            t_cmd.DataSize = operation->leftover_nbytes;
            t_cmd.TotalMessageLengthLo = (uint32_t)(TotalMessageLength);
            t_cmd.TotalMessageLengthHi = (uint32_t)(TotalMessageLength >> 32);

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
                    (void)memcpy(hash, t_res.Digest, DigestNBytes);
                    *hash_length = DigestNBytes;

#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
                    (void)psaInt_AssetFree(operation->TempAssetId);
                    operation->TempAssetId = PSA_ASSETID_INVALID;
#endif
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
 * psa_hash_verify
 */
psa_status_t
psa_hash_verify(psa_hash_operation_t * operation,
                const uint8_t * hash,
                size_t hash_length)
{
    psa_status_t funcres;
    uint8_t Digest[64];
    size_t DigestNBytes = 0U;

    if ((NULL == operation) ||
        (NULL == hash) ||
        (0U == hash_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        (void)memset(Digest, 0, sizeof(Digest));
        funcres = psa_hash_finish(operation, Digest, sizeof(Digest), &DigestNBytes);
        if (PSA_SUCCESS == funcres)
        {
            if (0 != memcmp(hash, Digest, hash_length))
            {
                funcres = PSA_ERROR_INVALID_SIGNATURE;
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
 * psa_hash_abort
 */
psa_status_t
psa_hash_abort(psa_hash_operation_t * operation)
{
    psa_status_t funcres = PSA_SUCCESS;

    if (NULL == operation)
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
        if (PSA_ASSETID_INVALID != operation->TempAssetId)
        {
            (void)psaInt_AssetFree(operation->TempAssetId);
        }
#endif

        (void)memset(operation, 0, sizeof(psa_hash_operation_t));
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psa_hash_suspend
 */
psa_status_t
psa_hash_suspend(psa_hash_operation_t * operation,
                 uint8_t * hash_state,
                 size_t hash_state_size,
                 size_t * hash_state_length)
{
#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
    psa_status_t funcres = PSA_SUCCESS;

    if ((NULL == operation) ||
        (NULL == hash_state) ||
        (0U == hash_state_size) ||
        (NULL == hash_state_length) ||
        (0U == PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(operation->alg)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (hash_state_size < PSA_HASH_SUSPEND_OUTPUT_SIZE(operation->alg))
    {
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
    }
    else if (((PSA_HASH_STATE_SETUP != operation->hash_state) &&
              (PSA_HASH_STATE_UPDATE != operation->hash_state) &&
              (PSA_HASH_STATE_RESUME != operation->hash_state)) ||
             (0U == operation->block_size))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        uint64_t bytes_available = operation->TotalMessageLength + operation->leftover_nbytes;
        uint8_t index;

        for (index = 0U; index < PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH; index++)
        {
            hash_state[index] = (uint8_t)(operation->alg >> (index * 8U));
        }

        for (index = 0U; index < PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(operation->alg); index++)
        {
            hash_state[PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH + index] =
                (uint8_t)(bytes_available >> (index * 8U));
        }

        (void)memcpy(&hash_state[PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH +
                                 PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(operation->alg)],
                     operation->inter_digest,
                     PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(operation->alg));

        (void)memcpy(&hash_state[PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH +
                                 PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(operation->alg) +
                                 PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(operation->alg)],
                     operation->leftover_buf, operation->leftover_nbytes);

        *hash_state_length = PSA_HASH_SUSPEND_OUTPUT_SIZE(operation->alg);
    }

    return funcres;
#else
    (void)operation;
    (void)hash_state;
    (void)hash_state_size;
    (void)hash_state_length;

    return PSA_ERROR_NOT_SUPPORTED;
#endif
}


/*----------------------------------------------------------------------------
 * psa_hash_resume
 */
psa_status_t
psa_hash_resume(psa_hash_operation_t * operation,
                const uint8_t * hash_state,
                size_t hash_state_length)
{
#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
    psa_status_t funcres = PSA_SUCCESS;

    if ((NULL == operation) ||
        (NULL == hash_state) ||
        (0U == hash_state_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (PSA_HASH_STATE_INIT != operation->hash_state)
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        uint64_t bytes_available = 0U;
        uint8_t index;

        operation->TempAssetId = PSA_ASSETID_INVALID;
        operation->alg = 0U;
        for (index = 0U; index < PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH; index++)
        {
            operation->alg |= ((uint32_t)hash_state[index]) << (index * 8U);
        }
        operation->block_size = PSA_HASH_BLOCK_LENGTH(operation->alg);
        if ((0U == operation->block_size) ||
            (0U == PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(operation->alg)))
        {
            funcres = PSA_ERROR_BAD_STATE;
        }
        else
        {
            for (index = 0U; index < PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(operation->alg); index++)
            {
                /* Note: Although the length field for SHA-384/512 is 128-bit,
                 *       it is truncated to 64-bit for calculational reasons
                 *       for now.
                 */
                if (index < 8U)
                {
                    bytes_available |= ((uint64_t)hash_state[PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH + index]) << (index * 8U);
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }

            (void)memcpy(operation->inter_digest,
                         &hash_state[PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH +
                                     PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(operation->alg)],
                         PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(operation->alg));

            operation->leftover_nbytes = (uint32_t)(bytes_available % operation->block_size);
            if (0U == operation->leftover_nbytes)
            {
                operation->leftover_nbytes = operation->block_size;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
            if (bytes_available > operation->leftover_nbytes)
            {
                operation->fUpdateDone = 255U;
                operation->TotalMessageLength = bytes_available - operation->leftover_nbytes;
            }
            else
            {
                operation->fUpdateDone = 0U;
                operation->TotalMessageLength = 0U;
            }

            (void)memcpy(operation->leftover_buf,
                         &hash_state[PSA_HASH_SUSPEND_ALGORITHM_FIELD_LENGTH +
                                     PSA_HASH_SUSPEND_INPUT_LENGTH_FIELD_LENGTH(operation->alg) +
                                     PSA_HASH_SUSPEND_HASH_STATE_FIELD_LENGTH(operation->alg)],
                         operation->leftover_nbytes);

            operation->hash_state = PSA_HASH_STATE_RESUME;
        }
    }

    return funcres;
#else
    (void)operation;
    (void)hash_state;
    (void)hash_state_length;

    return PSA_ERROR_NOT_SUPPORTED;
#endif
}


/*----------------------------------------------------------------------------
 * psa_hash_clone
 */
psa_status_t
psa_hash_clone(const psa_hash_operation_t * source_operation,
               psa_hash_operation_t * target_operation)
{
#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
    psa_status_t funcres = PSA_SUCCESS;

    if ((NULL == source_operation) ||
        (NULL == target_operation))
    {
        funcres = PSA_ERROR_BAD_STATE;
    }
    else
    {
        (void)memcpy(target_operation, source_operation, sizeof(psa_hash_operation_t));
    }

    return funcres;
#else
    (void)source_operation;
    (void)target_operation;

    return PSA_ERROR_NOT_SUPPORTED;
#endif
}


/* end of file adapter_psa_sym_hash.c */
