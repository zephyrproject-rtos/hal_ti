/* adapter_psa_asset.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the Asset Store services.
 */

/*
 * Copyright (c) 2024-2026 Texas Instruments Incorporated
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

#include <DeviceFamily.h>
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    #include <ti/drivers/xmem/XMEMWFF3.h>
    #include <ti/devices/cc35xx/inc/hw_memmap.h>
#endif

static const uint8_t gl_PSA_ADLabelKeyblob[] = PSA_AS_KEYBLOB_ADLABEL;

static Eip130Token_Command_t commandToken;
static Eip130Token_Result_t resultToken;
/*
 * CC35XX PSRAM bounce-buffer infrastructure
 *
 * On CC35XX the HSM can only access internal SRAM. Callers may supply buffers
 * located in PSRAM, so each function that passes a user pointer directly to an
 * HSM token must stage the data through an internal-RAM bounce buffer first.
 *
 * Two bounce buffers are used:
 *   gl_assetLoadBounce  - for plaintext asset data (max PSA_ASSET_SIZE_MAX bytes).
 *   gl_keyBlobBounce    - for key blobs and salt (max PSA_KEYBLOB_SIZE(PSA_ASSET_SIZE_MAX) bytes).
 *
 * Both buffers are sized to the maximum the PSA_STRICT_ARGS checks allow
 * through; no separate size check is needed in the PSRAM path.
 *
 * Both buffers are placed in .internalRAM.bss so they are reachable by the HSM.
 * They are safe to use as statics because CommonResourceXXF3 is always held for
 * the duration of each function that uses them.
 *
 * psaInt_xmemRead / psaInt_xmemWrite use the XMEM driver to transfer data
 * between PSRAM and the bounce buffers. The XMEM handle is opened lazily on
 * the first call; this is safe because the HSM lock is always held at that
 * point.
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
static uint8_t gl_assetLoadBounce[PSA_ASSET_SIZE_MAX] __attribute__((section(".internalRAM.bss"), aligned(4)));
static uint8_t gl_keyBlobBounce[PSA_KEYBLOB_ADDITIONAL_BYTES + PSA_ASSET_SIZE_MAX] __attribute__((section(".internalRAM.bss"), aligned(4)));
static XMEM_Handle gl_psramHandle = NULL;

static psa_status_t psaInt_xmemEnsureHandle(void)
{
    if (gl_psramHandle == NULL)
    {
        XMEM_Params p;
        XMEMWFF3_init();
        p.regionBase      = 0U;
        p.regionStartAddr = EXT_PSRAM_BASE;
        p.regionSize      = XMEM_MAX_PSRAM_SIZE;
        p.deviceNum       = XMEM_MEM_PSRAM;
        gl_psramHandle    = XMEMWFF3_open(&p);
    }
    return (gl_psramHandle != NULL) ? PSA_SUCCESS : PSA_ERROR_HARDWARE_FAILURE;
}

static psa_status_t psaInt_xmemRead(const void *src, void *dst, size_t len)
{
    if (psaInt_xmemEnsureHandle() != PSA_SUCCESS)
    {
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    if (XMEMWFF3_read(gl_psramHandle, XMEMWFF3_addrToOffset((uintptr_t)src), dst, len, XMEM_READ) != XMEM_STATUS_SUCCESS)
    {
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    return PSA_SUCCESS;
}

static psa_status_t psaInt_xmemWrite(void *dst, const void *src, size_t len)
{
    if (psaInt_xmemEnsureHandle() != PSA_SUCCESS)
    {
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    if (XMEMWFF3_write(gl_psramHandle, XMEMWFF3_addrToOffset((uintptr_t)dst), (void *)src, len, XMEM_WRITE) != XMEM_STATUS_SUCCESS)
    {
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    return PSA_SUCCESS;
}
#endif

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

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        /* Stage Data_p into internal RAM if it is in PSRAM. DataSize is
         * bounded by PSA_ASSET_SIZE_MAX (enforced by PSA_STRICT_ARGS), which
         * is also the size of gl_assetLoadBounce, so it always fits.
         */
        if (XMEMWFF3_isAddrExternal((uintptr_t)Data_p))
        {
            if (psaInt_xmemRead(Data_p, gl_assetLoadBounce, DataSize) != PSA_SUCCESS)
            {
                CommonResourceXXF3_releaseLock();
                return PSA_ERROR_HARDWARE_FAILURE;
            }
            Data_p = gl_assetLoadBounce;
        }
#endif

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

        const uint8_t *dataIn = Data_p;
        uint8_t *keyBlobDma = KeyBlob_p;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        /* Stage plaintext input into internal RAM if it is in PSRAM. DataSize
         * is bounded by PSA_ASSET_SIZE_MAX (enforced by PSA_STRICT_ARGS),
         * which is also the size of gl_assetLoadBounce, so it always fits.
         */
        if (XMEMWFF3_isAddrExternal((uintptr_t)dataIn))
        {
            if (psaInt_xmemRead(dataIn, gl_assetLoadBounce, DataSize) != PSA_SUCCESS)
            {
                CommonResourceXXF3_releaseLock();
                return PSA_ERROR_HARDWARE_FAILURE;
            }
            dataIn = gl_assetLoadBounce;
        }
        /* If KeyBlob_p is in PSRAM, redirect the HSM output to the internal
         * RAM bounce buffer and write back via XMEM after the operation. The
         * key blob size is bounded by PSA_KEYBLOB_SIZE(PSA_ASSET_SIZE_MAX)
         * (enforced by PSA_STRICT_ARGS), which is also the size of
         * gl_keyBlobBounce, so it always fits.
         */
        if (XMEMWFF3_isAddrExternal((uintptr_t)KeyBlob_p))
        {
            keyBlobDma = gl_keyBlobBounce;
        }
#endif

        Eip130Token_Command_AssetLoad_Plaintext(&commandToken, TargetAssetId);

        Eip130Token_Command_AssetLoad_Export(&commandToken, KekAssetId);

        Eip130Token_Command_AssetLoad_SetAad(&commandToken,
                                             (const uint8_t *)gl_PSA_ADLabelKeyblob,
                                             (uint32_t)(sizeof(gl_PSA_ADLabelKeyblob) - 1U));

        Eip130Token_Command_AssetLoad_SetInput(&commandToken,
                                               (uintptr_t)dataIn,
                                               (uint32_t)DataSize);
        Eip130Token_Command_AssetLoad_SetOutput(&commandToken,
                                                (uintptr_t)keyBlobDma,
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
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
                        if (keyBlobDma != KeyBlob_p)
                        {
                            funcres = psaInt_xmemWrite(KeyBlob_p, gl_keyBlobBounce, outputSize);
                        }
                        else
#endif
                        {
                            funcres = PSA_SUCCESS;
                        }
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

        const uint8_t *keyBlobIn = KeyBlob_p;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        /* Stage key blob input into internal RAM if it is in PSRAM. KeyBlobSize
         * is bounded by PSA_KEYBLOB_SIZE(PSA_ASSET_SIZE_MAX) (enforced by
         * PSA_STRICT_ARGS), which is also the size of gl_keyBlobBounce, so it
         * always fits.
         */
        if (XMEMWFF3_isAddrExternal((uintptr_t)keyBlobIn))
        {
            if (psaInt_xmemRead(keyBlobIn, gl_keyBlobBounce, KeyBlobSize) != PSA_SUCCESS)
            {
                CommonResourceXXF3_releaseLock();
                return PSA_ERROR_HARDWARE_FAILURE;
            }
            keyBlobIn = gl_keyBlobBounce;
        }
#endif

        Eip130Token_Command_AssetLoad_Import(&commandToken,
                                             TargetAssetId,
                                             KekAssetId);

        Eip130Token_Command_AssetLoad_SetAad(&commandToken,
                                             (const uint8_t *)gl_PSA_ADLabelKeyblob,
                                             (uint32_t)(sizeof(gl_PSA_ADLabelKeyblob) - 1U));

        Eip130Token_Command_AssetLoad_SetInput(&commandToken,
                                              (uintptr_t)keyBlobIn,
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

        uint8_t *keyBlobDma = KeyBlob_p;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        /* If KeyBlob_p is in PSRAM, redirect the HSM output to the internal
         * RAM bounce buffer and write back via XMEM after the operation. The
         * key blob size is bounded by PSA_KEYBLOB_SIZE(PSA_ASSET_SIZE_MAX)
         * (enforced by PSA_STRICT_ARGS), which is also the size of
         * gl_keyBlobBounce, so it always fits.
         */
        if (XMEMWFF3_isAddrExternal((uintptr_t)KeyBlob_p))
        {
            keyBlobDma = gl_keyBlobBounce;
        }
#endif

        Eip130Token_Command_AssetLoad_Random(&commandToken, TargetAssetId);

        Eip130Token_Command_AssetLoad_Export(&commandToken, KekAssetId);

        Eip130Token_Command_AssetLoad_SetAad(&commandToken,
                                             (const uint8_t *)gl_PSA_ADLabelKeyblob,
                                             (uint32_t)(sizeof(gl_PSA_ADLabelKeyblob) - 1U));

        Eip130Token_Command_AssetLoad_SetOutput(&commandToken,
                                                (uintptr_t)keyBlobDma,
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
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
                        if (keyBlobDma != KeyBlob_p)
                        {
                            funcres = psaInt_xmemWrite(KeyBlob_p, gl_keyBlobBounce, outputSize);
                        }
                        else
#endif
                        {
                            funcres = PSA_SUCCESS;
                        }
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

        const uint8_t *saltIn = Salt_p;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
        /* Stage salt input into internal RAM if it is in PSRAM. Salt is
         * documented as at most 64 bytes, well within gl_keyBlobBounce.
         */
        if (XMEMWFF3_isAddrExternal((uintptr_t)saltIn))
        {
            if (psaInt_xmemRead(saltIn, gl_keyBlobBounce, SaltSize) != PSA_SUCCESS)
            {
                CommonResourceXXF3_releaseLock();
                return PSA_ERROR_HARDWARE_FAILURE;
            }
            saltIn = gl_keyBlobBounce;
        }
#endif

        Eip130Token_Command_AssetLoad_SetInput(&commandToken,
                                               (uintptr_t)saltIn,
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
