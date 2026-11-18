/* adapter_vex_asym_asset_genshared.c
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
 * vex_Asym_AssetGenSharedSecret
 */
VexStatus_t
vex_Asym_AssetGenSharedSecret(
        const VexTokenCmd_PkAssetGenSharedSecret_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    uint64_t LocalEphPubKey = 0;
    uint64_t OtherInfoAddr = 0;
    size_t OtherInfoSize = 0;
    size_t LocalEphPubKeySize = 0;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    if ((CommandToken_p->OtherInfo_p != NULL) &&
        (CommandToken_p->OtherInfoSize != 0U))
    {
        // Get OtherInfo input address for token
        OtherInfoSize = CommandToken_p->OtherInfoSize;
        OtherInfoAddr = BufManager_Map(
                            vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                            BUFMANAGER_BUFFERTYPE_IN,
                            CommandToken_p->OtherInfo_p,
                            OtherInfoSize,
                            NULL);
        if (OtherInfoAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        if ((CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_SM2KEX_GEN_SHARED_SECRET) &&
            (CommandToken_p->LocalEphPubKey != NULL) &&
            (CommandToken_p->LocalEphPubKeySize != 0U))
        {
            // Get local ephemeral public key input address for token
            LocalEphPubKeySize = CommandToken_p->LocalEphPubKeySize;
            LocalEphPubKey = BufManager_Map(
                                 vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                 BUFMANAGER_BUFFERTYPE_IN,
                                 CommandToken_p->LocalEphPubKey,
                                 LocalEphPubKeySize,
                                 NULL);
            if (LocalEphPubKey == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
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
            (uint8_t)CommandToken_p->AssetIdListSize,
            CommandToken_p->PrivKeyAssetId,
            CommandToken_p->DomainAssetId,
            CommandToken_p->PubKeyAssetId,
            OtherInfoAddr, (uint16_t)OtherInfoSize,
            LocalEphPubKey, (uint16_t)LocalEphPubKeySize);

        if ((CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_DH_GEN_DKEYPAIR_SHARED_SECRET) ||
            (CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_ECDH_GEN_DKEYPAIR_SHARED_SECRET) ||
            (CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_SM2KEX_GEN_SHARED_SECRET))
        {
            if ((CommandToken_p->PubKey2AssetId == 0U) ||
                (CommandToken_p->PrivKey2AssetId == 0U))
            {
                funcres = VEX_BAD_ARGUMENT;
            }
            else
            {
                Eip130Token_Command_Pk_Asset_SetAdditionalAssetId(
                    &CommandToken,
                    CommandToken_p->PrivKey2AssetId);
                Eip130Token_Command_Pk_Asset_SetAdditionalAssetId(
                    &CommandToken,
                    CommandToken_p->PubKey2AssetId);
            }
        }

        if (funcres == VEX_SUCCESS)
        {
            uint32_t i;

            for (i = 0; i < CommandToken_p->AssetIdListSize; i++)
            {
                Eip130Token_Command_Pk_Asset_SetAdditionalAssetId(
                    &CommandToken,
                    CommandToken_p->AssetIdList[i]);
            }

            if (CommandToken_p->fSaveSharedSecret != 0U)
            {
                Eip130Token_Command_Pk_Asset_SaveSharedSecret(&CommandToken);
            }

            Eip130Token_Command_SetTokenID(&CommandToken, vex_DeviceGetTokenID(), false);

            // Initialize result token
            (void)memset(&ResultToken, 0, sizeof(ResultToken));

            // Exchange token with the EIP-130 HW
            funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
            if (funcres == VEX_SUCCESS)
            {
                ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
            }
        }
    }

    // Release used buffers, if needed
    if (LocalEphPubKey != 0U)
    {
        (void)BufManager_Unmap(LocalEphPubKey, false, false, 0U);
    }
    if (OtherInfoAddr != 0U)
    {
        (void)BufManager_Unmap(OtherInfoAddr, false, false, 0U);
    }

    return funcres;
}


/* end of file adapter_vex_asym_asset_genshared.c */
