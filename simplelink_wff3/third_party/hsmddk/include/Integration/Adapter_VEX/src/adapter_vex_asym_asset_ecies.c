/* adapter_vex_asym_asset_ecies.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the ECIES VEX API
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
 * vex_Asym_AssetEcies
 */
#ifdef VEX_ENABLE_ASYM_ECIES
VexStatus_t
vex_Asym_AssetEcies(
        const VexTokenCmd_PkEcies_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    uint64_t OtherInfoAddr  = 0U;
    uint64_t OutputDataAddr = 0U;
    uint64_t WrapDataAddr = 0U;
    size_t OtherInfoSize  = 0U;
    size_t OutputDataSize = 0U;
    size_t WrapDataSize = 0U;
    uint16_t TokenID = 0U;
    bool fCopy = false;

    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    /* Required data for both WRAP and UNWRAP operations */
    if ((CommandToken_p->Data_p == NULL) ||
        (CommandToken_p->DataSize == 0U) ||
        (CommandToken_p->AssetDataId == 0U) ||
        (CommandToken_p->KeyAssetId == 0U) ||
        (CommandToken_p->DomainAssetId == 0U))
    {
        funcres = VEX_BAD_ARGUMENT;
    }
    else
    {
        TokenID = vex_DeviceGetTokenID();

        /* Operation specific token preparations & checks */
        if (CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_ECIESWRAP)
        {
            if ((CommandToken_p->EphPubKey_p == NULL) ||
                (CommandToken_p->EphPubKeySize == 0U))
            {
                funcres = VEX_BAD_ARGUMENT;
            }
            else
            {
                /* Map output buffer for ephemeral pubkey & Wrapped data */
                OutputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                                BUFMANAGER_BUFFERTYPE_OUT,
                                                CommandToken_p->EphPubKey_p,
                                                CommandToken_p->EphPubKeySize,
                                                (void *)&TokenID);
                if (OutputDataAddr == 0U)
                {
                    funcres = VEX_NO_MEMORY;
                }
                else
                {
                    WrapDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                                  BUFMANAGER_BUFFERTYPE_OUT,
                                                  CommandToken_p->Data_p,
                                                  CommandToken_p->DataSize,
                                                  (void *)&TokenID);
                    if (WrapDataAddr == 0U)
                    {
                        funcres = VEX_NO_MEMORY;
                    }
                    else
                    {
                        OutputDataSize = BufManager_GetSize(OutputDataAddr);
                        WrapDataSize = BufManager_GetSize(WrapDataAddr);
                    }
                }
            }
        }
        else
        {
            if (CommandToken_p->EphPubKeyAssetId == 0U)
            {
                funcres = VEX_BAD_ARGUMENT;
            }
            else
            {
                /* Map input buffer for wrapped data */
                OutputDataSize = CommandToken_p->DataSize;
                OutputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                                BUFMANAGER_BUFFERTYPE_IN,
                                                CommandToken_p->Data_p,
                                                OutputDataSize,
                                                NULL);
                if (OutputDataAddr == 0U)
                {
                    funcres = VEX_NO_MEMORY;
                }
            }
        }


        if ((funcres == VEX_SUCCESS) &&
            (CommandToken_p->OtherInfo_p != NULL) &&
            (CommandToken_p->OtherInfoSize != 0U))
        {
            OtherInfoSize = CommandToken_p->OtherInfoSize;
            OtherInfoAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
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
            Eip130Token_Command_Pk_Asset_Command(&CommandToken,
                                                 (uint8_t)CommandToken_p->Method,
                                                 (uint8_t)((CommandToken_p->ModulusSizeInBits+31U)/32U),
                                                 (uint8_t)((CommandToken_p->ModulusSizeInBits+31U)/32U),
                                                 0,
                                                 CommandToken_p->KeyAssetId,
                                                 CommandToken_p->DomainAssetId,
                                                 CommandToken_p->AssetDataId,
                                                 OtherInfoAddr,
                                                 (uint16_t)OtherInfoSize,
                                                 OutputDataAddr,
                                                 (uint16_t)OutputDataSize);

            if (CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_ECIESWRAP)
            {
                /* Set buffer where encrypted/wrapped data shall be written */
                Eip130Token_Command_Pk_Asset_SetAdditionalOutputData(&CommandToken,
                                                                     WrapDataAddr,
                                                                     (uint32_t)WrapDataSize);
            }
            else
            {
                Eip130Token_Command_Pk_Asset_SetAdditionalAssetId(&CommandToken,
                                                                  CommandToken_p->EphPubKeyAssetId);
            }

            Eip130Token_Command_SetTokenID(&CommandToken, TokenID, true);

            /* Initialize result token */
            (void)memset(&ResultToken, 0, sizeof(ResultToken));

            /* Exchange token with the EIP-130 HW */
            funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
            if (funcres == VEX_SUCCESS)
            {
                ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
                if ((ResultToken_p->Result >= 0) &&
                    (CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_ECIESWRAP))
                {
                    fCopy = true;
                }
            }
        }

        // Release used buffers, if needed
        if (OtherInfoAddr != 0U)
        {
            (void)BufManager_Unmap(OtherInfoAddr, false, false, 0U);
        }
        if (OutputDataAddr != 0U)
        {
            if (CommandToken_p->Method == (uint32_t)VEXTOKEN_PKAS_ECIESWRAP)
            {
                int32_t rc = BufManager_Unmap(OutputDataAddr, true, fCopy, 0U);
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
            else
            {
                (void)BufManager_Unmap(OutputDataAddr, false, false, 0U);
            }
        }
        if(WrapDataAddr != 0U)
        {
            int32_t rc = BufManager_Unmap(WrapDataAddr, true, fCopy, 0U);
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
#endif /* VEX_ENABLE_ASYM_ECIES */

/* end of file adapter_vex_asym_asset_ecies.c */
