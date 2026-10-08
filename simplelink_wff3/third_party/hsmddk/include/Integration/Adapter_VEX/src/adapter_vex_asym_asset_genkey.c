/* adapter_vex_asym_asset_genkey.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the asymmetric crypto services for key generation.
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


/*----------------------------------------------------------------------------
 * vex_Asym_AssetGenKeyPair
 */
VexStatus_t
vex_Asym_AssetGenKeyPair(
        const VexTokenCmd_PkAssetGenKey_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;
    uint64_t KeyBlobAddr = 0;
    size_t KeyBlobSize = 0;
    uint64_t PubKeyAddr = 0;
    size_t PubKeySize = 0;
    uint16_t TokenID;
    uint16_t BufManagerTokenID;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    TokenID = vex_DeviceGetTokenID();
#ifdef VEX_DISABLE_TOKENID_WR_KEYPAIR
    BufManagerTokenID = 0;
#else
    BufManagerTokenID = TokenID;
#endif

    if (CommandToken_p->KekAssetId != 0U)
    {
        if ((CommandToken_p->KeyBlob_p == NULL) ||
            (CommandToken_p->AssociatedDataSize >= (256U - 4U)))
        {
            funcres = VEX_BAD_ARGUMENT;
        }
        else
        {
            // Get Key output address for token
            KeyBlobAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                         BUFMANAGER_BUFFERTYPE_OUT,
                                         CommandToken_p->KeyBlob_p,
                                         CommandToken_p->KeyBlobSize,
                                         (void *)&BufManagerTokenID);
            if (KeyBlobAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
            else
            {
#ifdef VEX_DISABLE_TOKENID_WR_KEYPAIR
                KeyBlobSize = CommandToken_p->KeyBlobSize;
                BufManager_Zeroize(KeyBlobAddr);
#else
                KeyBlobSize = BufManager_GetSize(KeyBlobAddr);
#endif
            }
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        if (CommandToken_p->PubKey_p != NULL)
        {
            // Get public key output address for token
            PubKeyAddr = BufManager_Map(
                                vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                BUFMANAGER_BUFFERTYPE_OUT,
                                CommandToken_p->PubKey_p,
                                CommandToken_p->PubKeySize,
                                (void *)&BufManagerTokenID);
            if (PubKeyAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
            else
            {
#ifdef VEX_DISABLE_TOKENID_WR_KEYPAIR
                PubKeySize = CommandToken_p->PubKeySize;
                BufManager_Zeroize(PubKeyAddr);
#else
#ifdef VEX_KEYPAIR_PUBKEYSIZE_NOTOKENID
                PubKeySize = CommandToken_p->PubKeySize;
#else
                PubKeySize = BufManager_GetSize(PubKeyAddr);
#endif
#endif
            }
        }

        if (funcres == VEX_SUCCESS)
        {
            // Format command token
            (void)memset(&CommandToken, 0, sizeof(CommandToken));
            Eip130Token_Command_Pk_Asset_Command(
                &CommandToken,
                (uint8_t)CommandToken_p->Method,
                (uint8_t)((CommandToken_p->ModulusSizeInBits+31U)/32U),
                (uint8_t)((CommandToken_p->DivisorSizeInBits+31U)/32U),
                0,
                CommandToken_p->PrivKeyAssetId,
                CommandToken_p->DomainAssetId,
                CommandToken_p->PubKeyAssetId,
                KeyBlobAddr, (uint16_t)KeyBlobSize,
                PubKeyAddr, (uint16_t)PubKeySize);

            if (KeyBlobAddr != 0U)
            {
                Eip130Token_Command_Pk_Asset_SetAdditionalAssetId(
                    &CommandToken,
                    CommandToken_p->KekAssetId);
                Eip130Token_Command_Pk_Asset_SetAdditionalData(
                    &CommandToken,
                    CommandToken_p->AssociatedData,
                    (uint8_t)CommandToken_p->AssociatedDataSize);
                Eip130Token_Command_Pk_Asset_AddlenCorrection(&CommandToken, sizeof(uint32_t));
            }

#ifdef VEX_DISABLE_TOKENID_WR_KEYPAIR
            /* Skip WrTokenID indication set */
            Eip130Token_Command_SetTokenID(&CommandToken, TokenID, false);
#else
            if ((KeyBlobAddr == 0U) && (PubKeyAddr == 0U))
            {
                Eip130Token_Command_SetTokenID(&CommandToken, TokenID, false);
            }
            else
            {
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
                Eip130Token_Command_SetTokenID(&CommandToken, TokenID, true);
#else
                Eip130Token_Command_SetTokenID(&CommandToken, TokenID, false);
#endif
            }
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
                }
            }
        }
    }

    // Release used buffers, if needed
    if (KeyBlobAddr != 0U)
    {
        int32_t rc = BufManager_Unmap(KeyBlobAddr, true, fCopy, 0U);
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

    if (PubKeyAddr != 0U)
    {
        int32_t rc = BufManager_Unmap(PubKeyAddr, true, fCopy, 0U);
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * vex_Asym_AssetGenKeyPublic
 */
VexStatus_t
vex_Asym_AssetGenKeyPublic(
        const VexTokenCmd_PkAssetGenKey_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;
    uint64_t PubKeyAddr = 0;
    size_t PubKeySize = 0;
    uint16_t TokenID;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    TokenID = vex_DeviceGetTokenID();

    if (CommandToken_p->PubKey_p != NULL)
    {
        // Get public key output address for token
        PubKeyAddr = BufManager_Map(
                            vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                            BUFMANAGER_BUFFERTYPE_OUT,
                            CommandToken_p->PubKey_p,
                            CommandToken_p->PubKeySize,
                            (void *)&TokenID);
        if (PubKeyAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
        else
        {
            PubKeySize = CommandToken_p->PubKeySize;
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        // Format command token
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        Eip130Token_Command_Pk_Asset_Command(
            &CommandToken,
            (uint8_t)CommandToken_p->Method,
            (uint8_t)((CommandToken_p->ModulusSizeInBits+31U)/32U),
            (uint8_t)((CommandToken_p->DivisorSizeInBits+31U)/32U),
            0,
            CommandToken_p->PrivKeyAssetId,
            CommandToken_p->DomainAssetId,
            CommandToken_p->PubKeyAssetId,
            0, 0,
            PubKeyAddr, (uint16_t)PubKeySize);
        if (PubKeyAddr == 0U)
        {
            Eip130Token_Command_SetTokenID(&CommandToken, TokenID, false);
        }
        else
        {
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
            Eip130Token_Command_SetTokenID(&CommandToken, TokenID, true);
#else
            Eip130Token_Command_SetTokenID(&CommandToken, TokenID, false);
#endif
        }

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
            }
        }

        // Release used buffer, if needed
        if (PubKeyAddr != 0U)
        {
            int32_t rc = BufManager_Unmap(PubKeyAddr, true, fCopy, 0U);
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


/* end of file adapter_vex_asym_asset_genkey.c */
