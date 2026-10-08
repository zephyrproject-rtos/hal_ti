/* adapter_vex_asym_asset_signverify.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the asymmetric crypto services for Sign/Verify.
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

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>              // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_intern_asym.h>   // API implementation
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_pk.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_asset.h>


/*----------------------------------------------------------------------------
 * vex_Asym_AssetSign
 */
VexStatus_t
vex_Asym_AssetSign(
        const VexTokenCmd_PkAssetSignVerify_t * const CommandToken_p,
        VexTokenRslt_PkAssetSignVerify_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;
    uint64_t HashDataAddr = 0;
    uint64_t SignAddr = 0;
    uint16_t TokenID;
    uint8_t ModulusWords;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    if (((CommandToken_p->ExplicitDigestSize == 0U) &&
         (CommandToken_p->HashData_p == NULL)) ||
        ((CommandToken_p->Sign_p == NULL) &&
         (CommandToken_p->Method != (uint32_t)VEXTOKEN_PKAS_EDDSA_SIGN_INITIAL) &&
         (CommandToken_p->Method != (uint32_t)VEXTOKEN_PKAS_EDDSA_SIGN_UPDATE)))
    {
        funcres = VEX_BAD_ARGUMENT;
    }
    else
    {
        if (CommandToken_p->HashData_p != NULL)
        {
            // Get hash data address for token
            HashDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                          BUFMANAGER_BUFFERTYPE_IN,
                                          CommandToken_p->HashData_p,
                                          CommandToken_p->HashDataSize,
                                          NULL);
            if (HashDataAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
        }

        if (funcres == VEX_SUCCESS)
        {
            // Get signature output address for token
            TokenID = vex_DeviceGetTokenID();
            if (CommandToken_p->Sign_p != NULL)
            {
                SignAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                          BUFMANAGER_BUFFERTYPE_OUT,
                                          CommandToken_p->Sign_p,
                                          CommandToken_p->SignSize,
                                          (void *)&TokenID);
                if (SignAddr == 0U)
                {
                    funcres = VEX_NO_MEMORY;
                }
            }

            if (funcres == VEX_SUCCESS)
            {
                ModulusWords = (uint8_t)((CommandToken_p->ModulusSizeInBits+31U)/32U);

                // Format command token
                (void)memset(&CommandToken, 0, sizeof(CommandToken));
                Eip130Token_Command_Pk_Asset_Command(
                    &CommandToken,
                    (uint8_t)CommandToken_p->Method,
                    ModulusWords, ModulusWords,
                    (uint8_t)CommandToken_p->SaltSize,
                    CommandToken_p->KeyAssetId,
                    CommandToken_p->DomainAssetId,
                    CommandToken_p->DigestAssetId,
                    HashDataAddr, (uint16_t)CommandToken_p->HashDataSize,
                    SignAddr, (uint16_t)CommandToken_p->SignSize);
#ifdef EIP130_ENABLE_EXPLICITDIGEST
                if(CommandToken_p->ExplicitDigestSize != 0U)
                {
                    Eip130Token_Command_Pk_Asset_SetExplicitDigest(
                        &CommandToken,
                        CommandToken_p->ExplicitDigest,
                        CommandToken_p->ExplicitDigestSize);
                }
                else
#endif
                {
                    uint64_t TotalMessageSize;
                    TotalMessageSize = (uint64_t)(((uint64_t)CommandToken_p->TotalMessageSizeHi << 32) +
                                                   (uint64_t)CommandToken_p->TotalMessageSizeLo);

                    Eip130Token_Command_Pk_Asset_SetAdditionalLength(
                        &CommandToken,
                        TotalMessageSize);
                }
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
                Eip130Token_Command_SetTokenID(&CommandToken, TokenID, true);
#else
                Eip130Token_Command_SetTokenID(&CommandToken, TokenID, false);
#endif

                // Initialize result token
                (void)memset(&ResultToken, 0, sizeof(ResultToken));

                // Exchange token with the EIP-130 HW
                funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
                if (funcres == VEX_SUCCESS)
                {
                    ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
                    if (ResultToken_p->Result >= 0)
                    {
                        // Copy output data
                        fCopy = true;

                        if (CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_EDDSA_SIGN_INITIAL)
                        {
                            // Get StateAssetId
                            Eip130Token_Result_AssetCreate(
                                &ResultToken,
                                &ResultToken_p->StateAssetId);
                        }
                    }
                }
            }
        }

        // Release used buffers, if needed
        if (HashDataAddr != 0U)
        {
            (void)BufManager_Unmap(HashDataAddr, false, false, 0U);
        }
        if (SignAddr != 0U)
        {
            int32_t rc = BufManager_Unmap(SignAddr, true, fCopy, 0U);
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
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * vex_Asym_AssetVerify
 */
VexStatus_t
vex_Asym_AssetVerify(
        const VexTokenCmd_PkAssetSignVerify_t * const CommandToken_p,
        VexTokenRslt_PkAssetSignVerify_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    uint64_t HashDataAddr = 0;
    uint64_t SignAddr = 0;
    uint8_t ModulusWords;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    if (((CommandToken_p->ExplicitDigestSize == 0U) &&
         (CommandToken_p->HashData_p == NULL)) ||
        ((CommandToken_p->Sign_p == NULL) &&
         (CommandToken_p->Method != (uint32_t)VEXTOKEN_PKAS_EDDSA_VERIFY_FINAL)))
    {
        funcres = VEX_BAD_ARGUMENT;
    }
    else
    {
        if (CommandToken_p->HashData_p != NULL)
        {
            // Get hash data address for token
            HashDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                          BUFMANAGER_BUFFERTYPE_IN,
                                          CommandToken_p->HashData_p,
                                          CommandToken_p->HashDataSize,
                                          NULL);
            if (HashDataAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
        }

        if (funcres == VEX_SUCCESS)
        {
            // Get signature address for token
            if (CommandToken_p->Sign_p != NULL)
            {
                SignAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                          BUFMANAGER_BUFFERTYPE_IN,
                                          CommandToken_p->Sign_p,
                                          CommandToken_p->SignSize,
                                          NULL);
                if (SignAddr == 0U)
                {
                    funcres = VEX_NO_MEMORY;
                }
            }

            if (funcres == VEX_SUCCESS)
            {
                ModulusWords = (uint8_t)((CommandToken_p->ModulusSizeInBits+31U)/32U);

                // Format command token
                (void)memset(&CommandToken, 0, sizeof(CommandToken));
                Eip130Token_Command_Pk_Asset_Command(
                    &CommandToken,
                    (uint8_t)CommandToken_p->Method,
                    ModulusWords, ModulusWords,
                    (uint8_t)CommandToken_p->SaltSize,
                    CommandToken_p->KeyAssetId,
                    CommandToken_p->DomainAssetId,
                    CommandToken_p->DigestAssetId,
                    HashDataAddr, (uint16_t)CommandToken_p->HashDataSize,
                    SignAddr, (uint16_t)CommandToken_p->SignSize);
#ifdef EIP130_ENABLE_EXPLICITDIGEST
                if(CommandToken_p->ExplicitDigestSize != 0U)
                {
                    Eip130Token_Command_Pk_Asset_SetExplicitDigest(
                        &CommandToken,
                        CommandToken_p->ExplicitDigest,
                        CommandToken_p->ExplicitDigestSize);
                }
                else
#endif
                {
                    uint64_t TotalMessageSize;
                    TotalMessageSize = (uint64_t)(((uint64_t)CommandToken_p->TotalMessageSizeHi << 32) +
                                                   (uint64_t)CommandToken_p->TotalMessageSizeLo);

                    Eip130Token_Command_Pk_Asset_SetAdditionalLength(
                        &CommandToken,
                        TotalMessageSize);
                }
                Eip130Token_Command_SetTokenID(&CommandToken, vex_DeviceGetTokenID(), false);

                // Initialize result token
                (void)memset(&ResultToken, 0, sizeof(ResultToken));

                // Exchange token with the EIP-130 HW
                funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
                if (funcres == VEX_SUCCESS)
                {
                    ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
                    if ((ResultToken_p->Result >= 0) &&
                        (CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_EDDSA_VERIFY_INITIAL))
                    {
                        // Get StateAssetId
                        Eip130Token_Result_AssetCreate(
                            &ResultToken,
                            &ResultToken_p->StateAssetId);
                    }
                }
            }
        }

        // Release used buffers, if needed
        if (HashDataAddr != 0U)
        {
            (void)BufManager_Unmap(HashDataAddr, false, false, 0U);
        }
        if (SignAddr != 0U)
        {
            (void)BufManager_Unmap(SignAddr, false, false, 0U);
        }
    }

    return funcres;
}


/* end of file adapter_vex_asym_asset_signverify.c */
