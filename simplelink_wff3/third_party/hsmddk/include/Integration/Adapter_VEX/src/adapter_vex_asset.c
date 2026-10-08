/* adapter_vex_asset.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the Asset Store services.
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

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>              // Configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>       // API implementation
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_asset.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_timer.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_publicdata.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_otp.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_random.h>


static uint64_t gl_InputDataAddr = 0;
static uint64_t gl_OutputDataAddr = 0;
static uint64_t gl_AddInputDataAddr = 0;
static volatile uint16_t gl_TokenID;

/*----------------------------------------------------------------------------
 * vex_IsStaticAsset
 *
 * Determines type of Asset based on its AssetId.
 *
 * AssetId
 *     Reference to an Asset.
 *
 * Return Value:
 *     true  : Static Asset   (Asset resides in EIP-130 OTP)
 *     false : Dynamic Asset  (Asset resides in EIP-130 internal memory)
 */
static bool
vexLocal_IsStaticAsset(uint32_t AssetId)
{
    return (((AssetId & 0xFF03FF03U) ^ 0x5A02A501U) == 0U);
}


/*----------------------------------------------------------------------------
 * vexLocal_AssetLoadCommon
 */
static VexStatus_t
vexLocal_AssetLoadCommon(
        const VexTokenCmd_Generic_t * const LogicalCommandToken_p,
        VexTokenRslt_AssetLoad_t * const LogicalResultToken_p,
        Eip130Token_Command_t * const CommandToken_p,
        Eip130Token_Result_t * const ResultToken_p,
        const uint8_t * Input_p,
        uint32_t InputSize,
        const uint8_t * AddInput_p,
        uint32_t AddInputSize,
        const uint8_t * Output_p,
        uint32_t OutputSize)
{
    VexStatus_t funcres = VEX_SUCCESS;

    if (Input_p != NULL)
    {
        // Get input address for token
        gl_InputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(LogicalCommandToken_p->fFromUserSpace),
                                       BUFMANAGER_BUFFERTYPE_IN,
                                       Input_p, InputSize,
                                       NULL);
        if (gl_InputDataAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
        else
        {
            Eip130Token_Command_AssetLoad_SetInput(CommandToken_p,
                                                   gl_InputDataAddr, InputSize);
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        if (Output_p != NULL)
        {
            // Get output address for token
            gl_OutputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(LogicalCommandToken_p->fFromUserSpace),
                                            BUFMANAGER_BUFFERTYPE_OUT,
                                            Output_p, OutputSize,
                                            (void *)&gl_TokenID);
            if (gl_OutputDataAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
            else
            {
                Eip130Token_Command_AssetLoad_SetOutput(CommandToken_p,
                                                        gl_OutputDataAddr,
                                                        (uint32_t)BufManager_GetSize(gl_OutputDataAddr));
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
                Eip130Token_Command_SetTokenID(CommandToken_p, gl_TokenID, true);
#else
                Eip130Token_Command_SetTokenID(CommandToken_p, gl_TokenID, false);
#endif
            }
        }
        else
        {
            if (AddInput_p != NULL)
            {
                // Get input address for token
                gl_AddInputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(LogicalCommandToken_p->fFromUserSpace),
                                                  BUFMANAGER_BUFFERTYPE_IN,
                                                  AddInput_p, AddInputSize,
                                                  NULL);
                if (gl_AddInputDataAddr == 0U)
                {
                    funcres = VEX_NO_MEMORY;
                }
                else
                {
                    Eip130Token_Command_AssetLoad_SetOutput(CommandToken_p,
                                                            gl_AddInputDataAddr,
                                                            AddInputSize);
                }
            }

            if (funcres == VEX_SUCCESS)
            {
                Eip130Token_Command_SetTokenID(CommandToken_p, gl_TokenID, false);
            }
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        // Exchange token with the EIP-130 HW
        funcres = vex_PhysicalTokenExchange(CommandToken_p, ResultToken_p);
    }
    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_AssetLoadCommon_Post
 */
static VexStatus_t
vexLocal_AssetLoadCommon_Post(const VexTokenCmd_Generic_t * const CommandToken_p,
                              VexTokenRslt_AssetLoad_t * const ResultToken_p,
                              const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if ((ResultToken_p->Result >= 0) && (gl_OutputDataAddr != 0U))
    {
        Eip130Token_Result_AssetLoad_OutputSize(
            ResultTokenP_p,
            &ResultToken_p->DataBlobSize);
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * vex_Asset
 */
VexStatus_t
vex_Asset(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    gl_TokenID = vex_DeviceGetTokenID();
    VexStatus_t funcres = VEX_SUCCESS;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;
    uint16_t OutputDataSize = 0;

    // Initialize result token
    (void)memset(&ResultToken, 0, sizeof(ResultToken));

    // Format command token
    (void)memset(&CommandToken, 0, sizeof(CommandToken));
    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_ASSETSEARCH:
    {
        const VexTokenCmd_AssetSearch_t * const LocalCommandToken_p = (VexTokenCmd_AssetSearch_t *)CommandToken_p;

        Eip130Token_Command_AssetSearch(&CommandToken,
                                        LocalCommandToken_p->Number);
        break;
    }

    case VEXTOKEN_SUBCODE_ASSETCREATE:
    {
        const VexTokenCmd_AssetCreate_t * const LocalCommandToken_p = (VexTokenCmd_AssetCreate_t *)CommandToken_p;
        uint64_t Policy = (uint64_t)(((uint64_t)LocalCommandToken_p->PolicyHi << 32) +
                                     (uint64_t)LocalCommandToken_p->PolicyLo);

        Eip130Token_Command_AssetCreate(&CommandToken,
                                        Policy,
                                        LocalCommandToken_p->Size);
        break;
    }

    case VEXTOKEN_SUBCODE_ASSETLOAD:
    {
        switch (((VexTokenCmd_AssetLoadPlaintext_t *)CommandToken_p)->Method)
        {
        case VEXTOKEN_ASSETLOAD_IMPORT:
        {
            const VexTokenCmd_AssetLoadImport_t * const LocalCommandToken_p = (VexTokenCmd_AssetLoadImport_t *)CommandToken_p;

            VexTokenRslt_AssetLoad_t * LocalResultToken_p = (VexTokenRslt_AssetLoad_t *)ResultToken_p;

            Eip130Token_Command_AssetLoad_Import(&CommandToken,
                                                 LocalCommandToken_p->AssetId,
                                                 LocalCommandToken_p->KekAssetId);
            Eip130Token_Command_AssetLoad_SetAad(&CommandToken,
                                                 LocalCommandToken_p->AssociatedData,
                                                 LocalCommandToken_p->AssociatedDataSize);
            funcres = vexLocal_AssetLoadCommon(CommandToken_p, LocalResultToken_p,
                                               &CommandToken, &ResultToken,
                                               LocalCommandToken_p->KeyBlob_p,
                                               LocalCommandToken_p->KeyBlobSize,
                                               NULL, 0, NULL, 0);
            break;
        }

        case VEXTOKEN_ASSETLOAD_DERIVE:
        {
            const VexTokenCmd_AssetLoadDerive_t * const LocalCommandToken_p = (VexTokenCmd_AssetLoadDerive_t *)CommandToken_p;
            VexTokenRslt_AssetLoad_t * LocalResultToken_p = (VexTokenRslt_AssetLoad_t *)ResultToken_p;

            Eip130Token_Command_AssetLoad_Derive(&CommandToken,
                                                 LocalCommandToken_p->AssetId,
                                                 LocalCommandToken_p->KdkAssetId,
                                                 vex_ConvertFromUint32ToBool((uint32_t)LocalCommandToken_p->fCounter),
                                                 vex_ConvertFromUint32ToBool((uint32_t)LocalCommandToken_p->fRFC5869),
                                                 LocalCommandToken_p->AssetNumber);
            Eip130Token_Command_AssetLoad_SetAad(&CommandToken,
                                                 LocalCommandToken_p->AssociatedData,
                                                 LocalCommandToken_p->AssociatedDataSize);
            funcres = vexLocal_AssetLoadCommon(CommandToken_p, LocalResultToken_p,
                                               &CommandToken, &ResultToken,
                                               LocalCommandToken_p->Salt_p,
                                               LocalCommandToken_p->SaltSize,
                                               LocalCommandToken_p->IV_p,
                                               LocalCommandToken_p->IVSize,
                                               NULL, 0);
            break;
        }

        case VEXTOKEN_ASSETLOAD_PLAINTEXT:
        {
            const VexTokenCmd_AssetLoadPlaintext_t * const LocalCommandToken_p = (VexTokenCmd_AssetLoadPlaintext_t *)CommandToken_p;
            VexTokenRslt_AssetLoad_t * LocalResultToken_p = (VexTokenRslt_AssetLoad_t *)ResultToken_p;

            Eip130Token_Command_AssetLoad_Plaintext(&CommandToken,
                                                    LocalCommandToken_p->AssetId);
            if (LocalCommandToken_p->KekAssetId != 0U)
            {
                Eip130Token_Command_AssetLoad_Export(&CommandToken,
                                                     LocalCommandToken_p->KekAssetId);
                Eip130Token_Command_AssetLoad_SetAad(&CommandToken,
                                                     LocalCommandToken_p->AssociatedData,
                                                     LocalCommandToken_p->AssociatedDataSize);
                funcres = vexLocal_AssetLoadCommon(CommandToken_p, LocalResultToken_p,
                                                   &CommandToken, &ResultToken,
                                                   LocalCommandToken_p->Data_p,
                                                   LocalCommandToken_p->DataSize,
                                                   NULL, 0,
                                                   LocalCommandToken_p->KeyBlob_p,
                                                   LocalCommandToken_p->KeyBlobSize);
            }
            else
            {
                funcres = vexLocal_AssetLoadCommon(CommandToken_p, LocalResultToken_p,
                                                   &CommandToken, &ResultToken,
                                                   LocalCommandToken_p->Data_p,
                                                   LocalCommandToken_p->DataSize,
                                                   NULL, 0, NULL, 0);
            }
            break;
        }

        case VEXTOKEN_ASSETLOAD_RANDOM:
        {
            const VexTokenCmd_AssetLoadRandom_t * const LocalCommandToken_p = (VexTokenCmd_AssetLoadRandom_t *)CommandToken_p;
            VexTokenRslt_AssetLoad_t * LocalResultToken_p = (VexTokenRslt_AssetLoad_t *)ResultToken_p;

            Eip130Token_Command_AssetLoad_Random(&CommandToken,
                                                 LocalCommandToken_p->AssetId);
            if (LocalCommandToken_p->KekAssetId != 0U)
            {
                Eip130Token_Command_AssetLoad_Export(&CommandToken,
                                                     LocalCommandToken_p->KekAssetId);
                Eip130Token_Command_AssetLoad_SetAad(&CommandToken,
                                                     LocalCommandToken_p->AssociatedData,
                                                     LocalCommandToken_p->AssociatedDataSize);
                funcres = vexLocal_AssetLoadCommon(CommandToken_p, LocalResultToken_p,
                                                   &CommandToken, &ResultToken,
                                                   NULL, 0, NULL, 0,
                                                   LocalCommandToken_p->KeyBlob_p,
                                                   LocalCommandToken_p->KeyBlobSize);
            }
            else
            {
                funcres = vexLocal_AssetLoadCommon(CommandToken_p, LocalResultToken_p,
                                                   &CommandToken, &ResultToken,
                                                   NULL, 0, NULL, 0, NULL, 0);
            }
            break;
        }

        case VEXTOKEN_ASSETLOAD_SYMUNWRAP:
        {
            const VexTokenCmd_AssetLoadSymUnwrap_t * const LocalCommandToken_p = (VexTokenCmd_AssetLoadSymUnwrap_t *)CommandToken_p;
            VexTokenRslt_AssetLoad_t * LocalResultToken_p = (VexTokenRslt_AssetLoad_t *)ResultToken_p;

            Eip130Token_Command_AssetLoad_SymUnwrap(&CommandToken,
                                                    LocalCommandToken_p->AssetId,
                                                    LocalCommandToken_p->KekAssetId,
                                                    LocalCommandToken_p->Algorithm);
            funcres = vexLocal_AssetLoadCommon(CommandToken_p, LocalResultToken_p,
                                               &CommandToken, &ResultToken,
                                               LocalCommandToken_p->KeyBlob_p,
                                               LocalCommandToken_p->KeyBlobSize,
                                               NULL, 0, NULL, 0);
            break;
        }

        default:
            funcres = VEX_UNSUPPORTED;
            break;
        }
        break;
    }

    case VEXTOKEN_SUBCODE_ASSETDELETE:
    {
        const VexTokenCmd_AssetDelete_t * const LocalCommandToken_p = (VexTokenCmd_AssetDelete_t *)CommandToken_p;

        Eip130Token_Command_AssetDelete(&CommandToken,
                                        LocalCommandToken_p->AssetId);
        break;
    }

    case VEXTOKEN_SUBCODE_SECURETIMER:
    {
        const VexTokenCmd_SecureTimer_t * const LocalCommandToken_p = (VexTokenCmd_SecureTimer_t *)CommandToken_p;

        Eip130Token_Command_SecureTimer(&CommandToken,
                                        LocalCommandToken_p->AssetId,
                                        vex_ConvertFromUint32ToBool(LocalCommandToken_p->fSecond),
                                        (uint16_t)LocalCommandToken_p->Operation);
        break;
    }

    case VEXTOKEN_SUBCODE_PUBLICDATA:
    {
        const VexTokenCmd_PublicData_t * const LocalCommandToken_p = (VexTokenCmd_PublicData_t *)CommandToken_p;

        // Get output address for token
        gl_OutputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(LocalCommandToken_p->fFromUserSpace),
                                        BUFMANAGER_BUFFERTYPE_OUT,
                                        LocalCommandToken_p->Data_p,
                                        LocalCommandToken_p->DataSize,
                                        (void *)&gl_TokenID);
        if (gl_OutputDataAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
        else
        {
            Eip130Token_Command_PublicData_Read(&CommandToken,
                                                LocalCommandToken_p->AssetId,
                                                gl_OutputDataAddr, (uint32_t)BufManager_GetSize(gl_OutputDataAddr));
        }
        break;
    }

    case VEXTOKEN_SUBCODE_MONOTONICREAD:
        {
            const VexTokenCmd_MonotonicCounter_t * const LocalCommandToken_p = (VexTokenCmd_MonotonicCounter_t *)CommandToken_p;

            if (vexLocal_IsStaticAsset(LocalCommandToken_p->AssetId))
            {
                // Get output address for token
                gl_OutputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(LocalCommandToken_p->fFromUserSpace),
                                                BUFMANAGER_BUFFERTYPE_OUT,
                                                LocalCommandToken_p->Data_p,
                                                LocalCommandToken_p->DataSize,
                                                (void *)&gl_TokenID);
                if (gl_OutputDataAddr == 0U)
                {
                    funcres = VEX_NO_MEMORY;
                }
                else
                {
                    Eip130Token_Command_OTPMonotonicCounter_Read(&CommandToken,
                                                                 LocalCommandToken_p->AssetId,
                                                                 gl_OutputDataAddr,(uint32_t)BufManager_GetSize(gl_OutputDataAddr));
                }
            }
            else
            {
                funcres = VEX_UNSUPPORTED;
            }
            break;
        }

    case VEXTOKEN_SUBCODE_MONOTONICINCR:
    {
        const VexTokenCmd_MonotonicCounter_t * const LocalCommandToken_p = (VexTokenCmd_MonotonicCounter_t *)CommandToken_p;

        if (vexLocal_IsStaticAsset(LocalCommandToken_p->AssetId))
        {
            Eip130Token_Command_OTPMonotonicCounter_Increment(&CommandToken,
                                                              LocalCommandToken_p->AssetId);
        }
        else
        {
            funcres = VEX_UNSUPPORTED;
        }
        break;
    }

    case VEXTOKEN_SUBCODE_OTPDATAWRITE:
    {
        const VexTokenCmd_OTPDataWrite_t * const LocalCommandToken_p = (VexTokenCmd_OTPDataWrite_t *)CommandToken_p;

        if (LocalCommandToken_p->KeyBlob_p != NULL)
        {
            // Key blob given - Get input address for token
            gl_InputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(LocalCommandToken_p->fFromUserSpace),
                                           BUFMANAGER_BUFFERTYPE_IN,
                                           LocalCommandToken_p->KeyBlob_p,
                                           LocalCommandToken_p->KeyBlobSize,
                                           NULL);
            if (gl_InputDataAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
        }
        if (funcres == VEX_SUCCESS)
        {
            Eip130Token_Command_OTPDataWrite(&CommandToken,
                                             LocalCommandToken_p->PolicyLo,
                                             gl_InputDataAddr,
                                             (uint16_t)LocalCommandToken_p->KeyBlobSize,
                                             LocalCommandToken_p->AssociatedData,
                                             LocalCommandToken_p->AssociatedDataSize);
        }
        break;
    }

    case VEXTOKEN_SUBCODE_PROVISIONRANDOMHUK:
    {
        const VexTokenCmd_ProvisionRandomHUK_t * const LocalCommandToken_p = (VexTokenCmd_ProvisionRandomHUK_t *)CommandToken_p;

        if (LocalCommandToken_p->KeyBlobSize != 0U)
        {
            // Get output address for token
            gl_OutputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                            BUFMANAGER_BUFFERTYPE_OUT,
                                            LocalCommandToken_p->KeyBlob_p,
                                            LocalCommandToken_p->KeyBlobSize,
                                            (void *)&gl_TokenID);
            if (gl_OutputDataAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
            else
            {
                OutputDataSize = (uint16_t)BufManager_GetSize(gl_OutputDataAddr);
            }
        }
        if (funcres == VEX_SUCCESS)
        {
            Eip130Token_Command_ProvisionRandomHUK(&CommandToken,
                                                   vex_ConvertFromUint32ToBool(LocalCommandToken_p->f128bit),
                                                   LocalCommandToken_p->AutoSeed,
                                                   LocalCommandToken_p->SampleCycles,
                                                   LocalCommandToken_p->SampleDiv,
                                                   LocalCommandToken_p->Scale,
                                                   LocalCommandToken_p->NoiseBlocks,
                                                   LocalCommandToken_p->RepCntCutoff,
                                                   LocalCommandToken_p->AdaptProp64Cutoff,
                                                   LocalCommandToken_p->AdaptProp512Cutoff,
                                                   gl_OutputDataAddr,
                                                   OutputDataSize,
                                                   LocalCommandToken_p->AssociatedData,
                                                   LocalCommandToken_p->AssociatedDataSize);
            Eip130Token_Command_Identity(&CommandToken,
                                         LocalCommandToken_p->Identity);
#ifdef VEX_ENABLE_ARIA_DRBG
            if (LocalCommandToken_p->fAria != 0U)
            {
                Eip130Token_Command_TRNG_Configure_AriaDRBG(&CommandToken);
            }
#endif
        }
        break;
    }

#ifdef EIP130_ENABLE_CPIF
    case VEXTOKEN_SUBCODE_CPIF_EXPORT:
    {
        const VexTokenCmd_AssetExportCPIF_t * const LocalCommandToken_p = (VexTokenCmd_AssetExportCPIF_t *)CommandToken_p;

        Eip130Token_Command_AssetExport_Coprocessor(&CommandToken,
                                                    LocalCommandToken_p->AssetId,
                                                    LocalCommandToken_p->Address,
                                                    LocalCommandToken_p->CPxSelectionBits);
        break;
    }
#endif

#ifdef EIP130_ENABLE_ASSET_STORE_RESET
    case VEXTOKEN_SUBCODE_ASSETSTORERESET:
        Eip130Token_Command_AssetStore_Reset(&CommandToken);
        break;
#endif

    default:
        funcres = VEX_UNSUPPORTED;
        break;
    }

    if ((funcres == VEX_SUCCESS) &&
        (CommandToken_p->SubCode != VEXTOKEN_SUBCODE_ASSETLOAD))
    {
        if (gl_OutputDataAddr != 0U)
        {
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
            Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, true);
#else
            Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, false);
#endif
        }
        else
        {
            Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, false);
        }

        // Exchange token with the EIP-130 HW
        funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
    }

    return funcres;
}

VexStatus_t
vex_Asset_PostProcessing(const VexTokenCmd_Generic_t * const CommandToken_p,
                         VexTokenRslt_Generic_t * const ResultToken_p,
                         const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if (ResultToken_p->Result >= 0)
    {
        // Success
        switch (CommandToken_p->SubCode)
        {
        case VEXTOKEN_SUBCODE_ASSETSEARCH:
        {
            VexTokenRslt_AssetSearch_t * LocalResultToken_p = (VexTokenRslt_AssetSearch_t *)ResultToken_p;
            Eip130Token_Result_AssetSearch(ResultTokenP_p,
                                            &LocalResultToken_p->AssetId,
                                            &LocalResultToken_p->Size);
            break;
        }

        case VEXTOKEN_SUBCODE_ASSETCREATE:
        {
            VexTokenRslt_AssetCreate_t * LocalResultToken_p = (VexTokenRslt_AssetCreate_t *)ResultToken_p;
            Eip130Token_Result_AssetCreate(ResultTokenP_p,
                                            &LocalResultToken_p->AssetId);
            break;
        }

        case VEXTOKEN_SUBCODE_ASSETLOAD:
        {
            vexLocal_AssetLoadCommon_Post(CommandToken_p,
                                          (VexTokenRslt_AssetLoad_t * ) ResultToken_p,
                                          ResultTokenP_p);
            break;
        }

        case VEXTOKEN_SUBCODE_SECURETIMER:
        {
            const VexTokenCmd_SecureTimer_t * const LocalCommandToken_p = (VexTokenCmd_SecureTimer_t *)CommandToken_p;
            VexTokenRslt_SecureTimer_t * LocalResultToken_p = (VexTokenRslt_SecureTimer_t *)ResultToken_p;

            if (LocalCommandToken_p->Operation ==
                    (uint32_t)VEXTOKEN_SECURETIMER_START)
            {
                Eip130Token_Result_SecureTimer(ResultTokenP_p,
                                                &LocalResultToken_p->AssetId,
                                                NULL);
            }
            else
            {
                Eip130Token_Result_SecureTimer(ResultTokenP_p,
                                                NULL,
                                                &LocalResultToken_p->ElapsedTime);
            }
            break;
        }

        case VEXTOKEN_SUBCODE_PUBLICDATA:
        {
            VexTokenRslt_PublicData_t * LocalResultToken_p = (VexTokenRslt_PublicData_t *)ResultToken_p;
            fCopy = true;
            Eip130Token_Result_Publicdata_Read(ResultTokenP_p,
                                                &LocalResultToken_p->DataSize);
            break;
        }

        case VEXTOKEN_SUBCODE_MONOTONICREAD:
        {
            VexTokenRslt_MonotonicCounter_t * LocalResultToken_p = (VexTokenRslt_MonotonicCounter_t *)ResultToken_p;
            fCopy = true;
            Eip130Token_Result_OTPMonotonicCounter_Read(ResultTokenP_p,
                                                        &LocalResultToken_p->DataSize);
            break;
        }

        case VEXTOKEN_SUBCODE_PROVISIONRANDOMHUK:
        {
            VexTokenRslt_ProvisionRandomHUK_t * LocalResultToken_p = (VexTokenRslt_ProvisionRandomHUK_t *)ResultToken_p;
            if (gl_OutputDataAddr != 0U)
            {
                fCopy = true;
                Eip130Token_Result_ProvisionRandomHUK(ResultTokenP_p,
                                                        &LocalResultToken_p->DataBlobSize);
            }
            else
            {
                LocalResultToken_p->DataBlobSize = 0;
            }
            break;
        }

        default:
            // Default means no post-processing required
            break;
        }
    }

    // Release used buffers, if needed
    if (gl_InputDataAddr != 0U)
    {
        (void)BufManager_Unmap(gl_InputDataAddr, false, false, 0U);
    }
    if (gl_AddInputDataAddr != 0U)
    {
        (void)BufManager_Unmap(gl_AddInputDataAddr, false, false, 0U);
    }
    if (gl_OutputDataAddr != 0U)
    {
        int32_t rc = BufManager_Unmap(gl_OutputDataAddr, true, fCopy, 0U);
        if (rc != 0)
        {
            if (rc == -3)
            {
                funcres = VEX_DATA_TIMEOUT;
            }
            else
            {
                funcres = VEX_DATA_MAPPING_ERROR;
            }
        }
    }

    gl_OutputDataAddr = 0;
    gl_InputDataAddr = 0;
    gl_AddInputDataAddr = 0;
    gl_TokenID = 0;

    return funcres;
}


/* end of file adapter_vex_asset.c */
