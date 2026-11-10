/* adapter_vex_asym_common.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the ECC curve asset install functionality.
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

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>          // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_intern_asym.h>   // API implementation
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_asset.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_asset_policy.h>
#include <third_party/hsmddk/include/Kit/EIP130/DomainHelper/incl/eip130_domain_ecc_curves.h>


/*----------------------------------------------------------------------------
 * vex_Asym_AssetInstallECCurve
 */
VexStatus_t
vex_Asym_AssetInstallECCurve(
        const VexTokenCmd_PkAssetInstallCurve_t * const CommandToken_p,
        VexTokenRslt_AssetCreate_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    const uint8_t * pCurveParams = NULL;
    uint32_t CurveParamsSize = 0;
    uint32_t AssetID = 0;
    uint64_t InputDataAddr = 0;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    // Get EC curve parameters
    if (Eip130Domain_ECC_GetCurve((Eip130Domain_ECCurveFamily_t)CommandToken_p->CurveFamily,
                                  CommandToken_p->CurveBits,
                                  &pCurveParams, &CurveParamsSize))
    {
        if (pCurveParams == NULL)
        {
            funcres = VEX_NO_MEMORY;
        }
        else
        {
            // Get input address for token
            InputDataAddr = BufManager_Alloc(false,
                                             BUFMANAGER_BUFFERTYPE_IN,
                                             CurveParamsSize,
                                             pCurveParams, CurveParamsSize,
                                             NULL);
            if (InputDataAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
            else
            {
                // Pass control to device
                if (BufManager_PreDmaAddress(InputDataAddr) < 0)
                {
                    funcres = VEX_DATA_MAPPING_ERROR;
                }
                else
                {
                    // Initialize command & result token
                    (void)memset(&CommandToken, 0, sizeof(CommandToken));
                    (void)memset(&ResultToken, 0, sizeof(ResultToken));

                    // Create asset
                    Eip130Token_Command_AssetCreate(&CommandToken,
                                                    EIP130_ASSET_POLICY_ASYM_KEYPARAMS,
                                                    CurveParamsSize);
                    Eip130Token_Command_SetTokenID(&CommandToken,
                                                   vex_DeviceGetTokenID(), false);

                    // Exchange token with the EIP-130 HW
                    funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
                    if (funcres == VEX_SUCCESS)
                    {
                        ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
                        if (ResultToken_p->Result >= 0)
                        {
                            // Retrieve AssetID of created asset
                            Eip130Token_Result_AssetCreate(&ResultToken,
                                                           &AssetID);

                            // Load asset
                            Eip130Token_Command_AssetLoad_Plaintext(&CommandToken,
                                                                    AssetID);
                            Eip130Token_Command_AssetLoad_SetInput(&CommandToken,
                                                                   InputDataAddr,
                                                                   CurveParamsSize);
                            Eip130Token_Command_SetTokenID(&CommandToken,
                                                           vex_DeviceGetTokenID(),
                                                           false);

                            // Exchange token with the EIP-130 HW for assetload
                            funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
                            if (funcres == VEX_SUCCESS)
                            {
                                ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
                                if (ResultToken_p->Result >= 0)
                                {
                                    ResultToken_p->AssetId = AssetID;
                                }
                            }

                            if (ResultToken_p->AssetId == 0U)
                            {
                                // Delete the Asset in case of an load issue
                                Eip130Token_Command_AssetDelete(&CommandToken, AssetID);
                                Eip130Token_Command_SetTokenID(&CommandToken,
                                                               vex_DeviceGetTokenID(),
                                                               false);

                                (void)vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
                            }
                        }
                    }
                }

                (void)BufManager_Unmap(InputDataAddr, false, false, 0U);
            }
        }
    }
    else
    {
        funcres = VEX_BAD_ARGUMENT;
    }

    return funcres;
}


/* end of file adapter_vex_asym_common.c */
