/* adapter_psa_asset.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the Asset Store services.
 */

/*
 * Copyright (c) 2024-2025, Texas Instruments Incorporated
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
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>      // uint8_t, uint16_t, uint32_t, uint64_t
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>      // size_t
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>
#include <third_party/hsmddk/include/Kit/EIP130/DomainHelper/incl/eip130_domain_ecc_curves.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_asset.h>
#include <third_party/hsmddk/include/Integration/HSMSAL/HSMSAL.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>          // the API to implement
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>

#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>
#ifdef PSA_LOG_LOWLEVEL_ERROR
#include <inttypes.h>
#endif

static const uint8_t gl_PSA_ADLabelKeyblob[] = PSA_AS_KEYBLOB_ADLABEL;

static Eip130Token_Command_t commandToken;
static Eip130Token_Result_t resultToken;

/*----------------------------------------------------------------------------
 * psaInt_AssetAlloc
 *
 * Allocate an Asset and set its policy. Its content is setup later.
 */
psa_status_t
psaInt_AssetAlloc(const PsaPolicyMask_t AssetPolicy,
                  const size_t AssetSize,
                  PsaAssetId_t * const AssetId_p)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;

#ifdef PSA_STRICT_ARGS
    if (((PsaPolicyMask_t)0U == AssetPolicy) ||
        (PSA_ASSET_SIZE_MAX < AssetSize) ||
        (NULL == AssetId_p))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        *AssetId_p = PSA_ASSETID_INVALID;

        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));
        Eip130Token_Command_AssetCreate(&commandToken, AssetPolicy, AssetSize);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    Eip130Token_Result_AssetCreate(&resultToken, AssetId_p);
                    funcres = PSA_SUCCESS;
                }
                else if (tokenResult == EIP130TOKEN_RESULT_FULL_ERROR)
                {
                    funcres = PSA_ERROR_ASSET_STORE_FULL;
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
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
 * psaInt_AssetFree
 *
 * Free the Asset referenced by AssetId.
 */
psa_status_t
psaInt_AssetFree(const PsaAssetId_t AssetId)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;

#ifdef PSA_STRICT_ARGS
    if (PSA_ASSETID_INVALID == AssetId)
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));

        Eip130Token_Command_AssetDelete(&commandToken, AssetId);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    funcres = PSA_SUCCESS;
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
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
 * psaInt_AssetLoadPlaintext
 *
 * Setup the content of the asset referenced by TargetAssetId from the
 * given plain data.
 */
psa_status_t
psaInt_AssetLoadPlaintext(const PsaAssetId_t TargetAssetId,
                          const uint8_t * Data_p,
                          const size_t DataSize)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;

#ifdef PSA_STRICT_ARGS
    if ((PSA_ASSETID_INVALID == TargetAssetId) ||
        (NULL == Data_p) ||
        (0U == DataSize) ||
        (PSA_ASSET_SIZE_MAX < DataSize))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
        CommonResourceXXF3_acquireLock(SemaphoreP_WAIT_FOREVER);

        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));

        Eip130Token_Command_AssetLoad_Plaintext(&commandToken, TargetAssetId);
        Eip130Token_Command_AssetLoad_SetInput(&commandToken,
                                              (uintptr_t)Data_p,
                                              (uint32_t)DataSize);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    funcres = PSA_SUCCESS;
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
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

        CommonResourceXXF3_releaseLock();
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_AssetLoadPlaintextExport
 *
 * Set up the content of the asset referenced by TargetAssetId from the
 * given plain data and export the resulting asset as a key blob.
 * Use the given KEK and AD to create the key blob.
 */
psa_status_t
psaInt_AssetLoadPlaintextExport(const PsaAssetId_t TargetAssetId,
                                const uint8_t * const Data_p,
                                const size_t DataSize,
                                const PsaAssetId_t KekAssetId,
                                uint8_t * const KeyBlob_p,
                                size_t * const KeyBlobSize_p)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;
    uint32_t outputSize;

#ifdef PSA_STRICT_ARGS
    if ((DataSize > PSA_ASSET_SIZE_MAX) ||
        (KeyBlob_p == NULL) ||
        (KeyBlobSize_p == NULL))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
        CommonResourceXXF3_acquireLock(SemaphoreP_WAIT_FOREVER);

        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));

        Eip130Token_Command_AssetLoad_Plaintext(&commandToken, TargetAssetId);

        Eip130Token_Command_AssetLoad_Export(&commandToken, KekAssetId);

        Eip130Token_Command_AssetLoad_SetAad(&commandToken,
                                             (const uint8_t *)gl_PSA_ADLabelKeyblob,
                                             (uint32_t)(sizeof(gl_PSA_ADLabelKeyblob) - 1U));

        Eip130Token_Command_AssetLoad_SetInput(&commandToken,
                                               (uintptr_t)Data_p,
                                               (uint32_t)DataSize);
        Eip130Token_Command_AssetLoad_SetOutput(&commandToken,
                                                (uintptr_t)KeyBlob_p,
                                                (uint32_t)*KeyBlobSize_p);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    Eip130Token_Result_AssetLoad_OutputSize(&resultToken, &outputSize);

                    if (0U == outputSize)
                    {
                        funcres = PSA_ERROR_CORRUPTION_DETECTED;
                    }
                    else
                    {
                        *KeyBlobSize_p = outputSize;
                        funcres = PSA_SUCCESS;
                    }
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
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

        CommonResourceXXF3_releaseLock();
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_AssetLoadImport
 *
 * Setup the content of the asset referenced by TargetAssetId from the
 * given key blob. Use the given KEK and AD to unwrap the key blob.
 */
psa_status_t
psaInt_AssetLoadImport(const PsaAssetId_t TargetAssetId,
                       const PsaAssetId_t KekAssetId,
                       const uint8_t * const KeyBlob_p,
                       const size_t KeyBlobSize)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;

#ifdef PSA_STRICT_ARGS
    if ((KeyBlobSize > PSA_KEYBLOB_SIZE(PSA_ASSET_SIZE_MAX)) ||
        (KeyBlob_p == NULL) || (KeyBlobSize == 0U))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
        CommonResourceXXF3_acquireLock(SemaphoreP_WAIT_FOREVER);

        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));

        Eip130Token_Command_AssetLoad_Import(&commandToken,
                                             TargetAssetId,
                                             KekAssetId);

        Eip130Token_Command_AssetLoad_SetAad(&commandToken,
                                             (const uint8_t *)gl_PSA_ADLabelKeyblob,
                                             (uint32_t)(sizeof(gl_PSA_ADLabelKeyblob) - 1U));

        Eip130Token_Command_AssetLoad_SetInput(&commandToken,
                                              (uintptr_t)KeyBlob_p,
                                              (uint32_t)KeyBlobSize);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    funcres = PSA_SUCCESS;
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
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

        CommonResourceXXF3_releaseLock();
    }
    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_AssetLoadRandom
 *
 * Setup the content of the asset referenced by TargetAssetId with random
 * data obtained from the RNG.
 */
psa_status_t
psaInt_AssetLoadRandom(const PsaAssetId_t TargetAssetId)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;

#ifdef PSA_STRICT_ARGS
    if (PSA_ASSETID_INVALID == TargetAssetId)
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));

        Eip130Token_Command_AssetLoad_Random(&commandToken, TargetAssetId);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    funcres = PSA_SUCCESS;
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
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
 * psaInt_AssetLoadRandomExport
 *
 * Setup the content of the asset referenced by TargetAssetId with random
 * data obtained from the RNG and export the resulting asset as a key blob.
 * Use the given KEK and AD to create the key blob.
 */
psa_status_t
psaInt_AssetLoadRandomExport(const PsaAssetId_t TargetAssetId,
                             const PsaAssetId_t KekAssetId,
                             uint8_t * const KeyBlob_p,
                             size_t * const KeyBlobSize_p)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;
    uint32_t outputSize;

#ifdef PSA_STRICT_ARGS
    if ((KeyBlob_p == NULL) || (KeyBlobSize_p == NULL))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
        CommonResourceXXF3_acquireLock(SemaphoreP_WAIT_FOREVER);

        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));

        Eip130Token_Command_AssetLoad_Random(&commandToken, TargetAssetId);

        Eip130Token_Command_AssetLoad_Export(&commandToken, KekAssetId);

        Eip130Token_Command_AssetLoad_SetAad(&commandToken,
                                             (const uint8_t *)gl_PSA_ADLabelKeyblob,
                                             (uint32_t)(sizeof(gl_PSA_ADLabelKeyblob) - 1U));

        Eip130Token_Command_AssetLoad_SetOutput(&commandToken,
                                                (uintptr_t)KeyBlob_p,
                                                (uint32_t)*KeyBlobSize_p);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    Eip130Token_Result_AssetLoad_OutputSize(&resultToken, &outputSize);

                    if (0U == outputSize)
                    {
                        funcres = PSA_ERROR_CORRUPTION_DETECTED;
                    }
                    else
                    {
                        *KeyBlobSize_p = outputSize;
                        funcres = PSA_SUCCESS;
                    }
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
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

        CommonResourceXXF3_releaseLock();
    }
    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_AssetLoadDerive
 *
 * Setup the content of the asset referenced by TargetAssetId by deriving it
 * from the given KDK and label info.
 */
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
                       const uint8_t AssetNumber)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;

#ifdef PSA_STRICT_ARGS
    if ((PSA_ASSETID_INVALID == TargetAssetId) ||
        (PSA_ASSETID_INVALID == KdkAssetId) ||
        (NULL == AssociatedData_p) ||
        (0U == AssociatedDataSize) ||
        (fCounter && fRFC5869))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
        CommonResourceXXF3_acquireLock(SemaphoreP_WAIT_FOREVER);

        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));

        Eip130Token_Command_AssetLoad_Derive(&commandToken,
                                             TargetAssetId,
                                             KdkAssetId,
                                             fCounter,
                                             fRFC5869,
                                             AssetNumber);

        Eip130Token_Command_AssetLoad_SetAad(&commandToken,
                                             AssociatedData_p,
                                             (uint32_t)AssociatedDataSize);

        Eip130Token_Command_AssetLoad_SetInput(&commandToken,
                                               (uintptr_t)Salt_p,
                                               (uint32_t)SaltSize);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    funcres = PSA_SUCCESS;
                }
                else
                {
                    funcres = PSA_ERROR_CORRUPTION_DETECTED;
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

        CommonResourceXXF3_releaseLock();
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_PublicDataRead
 *
 * Read a public data object.
 */
psa_status_t
psaInt_PublicDataRead(const PsaAssetId_t AssetId,
                      uint8_t * const Data_p,
                      const size_t DataSize,
                      size_t * output_length)
{
    VexTokenCmd_PublicData_t t_cmd;
    VexTokenRslt_PublicData_t t_res;
    psa_status_t funcres;

#ifdef PSA_STRICT_ARGS
    if ((PSA_ASSETID_INVALID == AssetId) ||
        (NULL == Data_p) ||
        (0U == DataSize) ||
        (NULL == output_length))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Due to errata SYS_211, get HSM lock to avoid AHB bus master transactions. */
        CommonResourceXXF3_acquireLock(SemaphoreP_WAIT_FOREVER);

        /* Format service request */
        t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_ASSETMANAGEMENT;
        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_PUBLICDATA;
        t_cmd.AssetId = (uint32_t)AssetId;
        t_cmd.Data_p = (const uint8_t *)Data_p;
        t_cmd.DataSize = (uint32_t)DataSize;
        t_res.Result = 0;
        t_res.DataSize = 0U;

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
                /* Zeroize remaining part of the buffer */
                uint32_t i = t_res.DataSize;
                *output_length = (size_t)t_res.DataSize;
                for (; i < DataSize; i++)
                {
                    Data_p[i] = 0U;
                }
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        CommonResourceXXF3_releaseLock();
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_AssetSearch
 *
 * Get the AssetId for the provided StaticAssetNumber.
 */
psa_status_t
psaInt_AssetSearch(const uint16_t StaticAssetNumber,
                   PsaAssetId_t * const AssetId_p,
                   size_t * const AssetSize_p)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    HSMSALStatus_t status;
    int32_t tokenResult;

#ifdef PSA_STRICT_ARGS
    if ((NULL == AssetId_p) ||
        (StaticAssetNumber > (PSA_ASSET_NUMBER_MAX + PSA_ASSET_NUMBER_CONSTANTS)))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        *AssetId_p = PSA_ASSETID_INVALID;

        /* Format service request */
        (void)memset(&commandToken, 0, sizeof(Eip130Token_Command_t));
        (void)memset(&resultToken, 0, sizeof(Eip130Token_Result_t));

        Eip130Token_Command_AssetSearch(&commandToken, StaticAssetNumber);

        status = HSMSAL_SubmitPhysicalToken(&commandToken);

        if (status == HSMSAL_SUCCESS)
        {
            status = HSMSAL_WaitForResultPolling(&resultToken);

            if (status == HSMSAL_SUCCESS)
            {
                tokenResult = Eip130Token_Result_Code(&resultToken);

                if ((tokenResult & MASK_8_BITS) == EIP130TOKEN_RESULT_SUCCESS)
                {
                    Eip130Token_Result_AssetSearch(&resultToken,
                                                   AssetId_p,
                                                   (uint32_t *)AssetSize_p);
                    funcres = PSA_SUCCESS;
                }
                else
                {
                    funcres = PSA_ERROR_DOES_NOT_EXIST;
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
 * psaInt_AssetGetKeyBlobKEK
 *
 * Get the AssetId of the Asset Blob KEK.
 */
psa_status_t
psaInt_AssetGetKeyBlobKEK(PsaAssetId_t * const KekAssetId)
{
    static const uint8_t ADLabelDerive[] = PSA_AS_DERIVE_ADLABEL;
    PsaAssetId_t RootKeyAssetId = PSA_ASSETID_INVALID;
    psa_status_t funcres;
    psa_status_t removalResult;

    *KekAssetId = PSA_ASSETID_INVALID;

    /* Need to check error if AssetSearch yields that HUK is not found - may mean that the user needs to
     * provision it. If that is the case, the error code describes it.
     */
    funcres = psaInt_AssetSearch(PSA_ASSETNUMBER_HUK, &RootKeyAssetId, NULL);

    /* The conditions for the if statement come together - one cannot be true
     * without the other
     */
    if ((funcres == PSA_SUCCESS) &&
        (RootKeyAssetId != PSA_ASSETID_INVALID))
    {
        PsaPolicyMask_t KekAssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP |
                                         EIP130_ASSET_POLICY_SCAWAESSIV |
                                         EIP130_ASSET_POLICY_SCDIRENCDEC;
        if (!psaInt_IsAccessSecure())
        {
            KekAssetPolicy |= PSA_POLICY_SOURCE_NON_SECURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        funcres = psaInt_AssetAlloc(KekAssetPolicy, 64, KekAssetId);
        if (PSA_SUCCESS == funcres)
        {
            funcres = psaInt_AssetLoadDerive(*KekAssetId, RootKeyAssetId,
                                             ADLabelDerive,
                                             (sizeof(ADLabelDerive) - 1U),
                                             false, false, NULL, 0, NULL, 0,
                                             PSA_AS_DERIVE_MC_ASSETNUMBER);
            if (PSA_SUCCESS != funcres)
            {
                LOG_CRIT("Failed: Asset Blob KEK initialization\n");
                removalResult = psaInt_AssetFree(*KekAssetId);
                if (removalResult != PSA_SUCCESS)
                {
                    funcres = removalResult;
                }

                *KekAssetId = PSA_ASSETID_INVALID;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
        else
        {
            LOG_CRIT("Failed: Asset Blob KEK creation\n");
        }
    }
    else if (funcres == PSA_ERROR_DOES_NOT_EXIST)
    {
        funcres = PSA_ERROR_HUK_NOT_PROVISIONED;
    }
    else
    {
        LOG_CRIT("Failed: Get Root key reference\n");
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * psaInt_AssetGetKeyBlobLabel
 *
 * Get the Associated Data (label) for the Asset Blob.
 */
void
psaInt_AssetGetKeyBlobLabel(uint8_t *pData,
                            uint32_t * pDataSize)
{
    *pDataSize = (uint32_t)(sizeof(gl_PSA_ADLabelKeyblob) - 1U);
    (void)memcpy(pData, gl_PSA_ADLabelKeyblob, *pDataSize);
}


/*----------------------------------------------------------------------------
 * psaInt_AsymEccInstallCurve
 *
 * Get curve family and curvebits and create asset and load it with the selected
 * family and return Asset ID for the asset.
 */
psa_status_t
psaInt_AsymEccInstallCurve(const uint8_t CurveFamily,
                           const size_t CurveBits,
                           PsaAssetId_t * const AssetId_p)
{
    psa_status_t funcres = PSA_ERROR_HARDWARE_FAILURE;
    psa_status_t removalResult;
    const uint8_t * pCurveParams = NULL;
    uint32_t CurveParamsSize = 0;
    uint32_t AssetID = 0;

    if (NULL == AssetId_p)
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else if (!Eip130Domain_ECC_GetCurve((Eip130Domain_ECCurveFamily_t)CurveFamily, CurveBits,
                                        &pCurveParams, &CurveParamsSize))
    {
        *AssetId_p = PSA_ASSETID_INVALID;
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        *AssetId_p = PSA_ASSETID_INVALID;

        /* Format service request */
        funcres = psaInt_AssetAlloc(EIP130_ASSET_POLICY_ASYM_KEYPARAMS,
                                    CurveParamsSize,
                                    &AssetID);

        if (funcres == PSA_SUCCESS)
        {
            funcres = psaInt_AssetLoadPlaintext(AssetID, pCurveParams, CurveParamsSize);

            if (funcres == PSA_SUCCESS)
            {
                *AssetId_p = AssetID;
            }
            else
            {
                removalResult = psaInt_AssetFree(AssetID);
                if (removalResult != PSA_SUCCESS)
                {
                    funcres = removalResult;
                }
            }
        }
        else
        {
            /* Error already set */
        }
    }

    return funcres;
}


/* end of file adapter_psa_asset.c */
