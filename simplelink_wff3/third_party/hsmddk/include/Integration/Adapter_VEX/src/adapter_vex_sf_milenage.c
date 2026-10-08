/* adapter_vex_sf_milenage.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the Special Functions services for Milenage.
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

#ifdef VEX_ENABLE_SF_MILENAGE

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_intern_sf.h>   // API implementation
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_sf_milenage.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_result.h>     // EIP130TOKEN_RESULT_VERIFY_ERROR


/*----------------------------------------------------------------------------
 * vex_SF_Milenage
 */
VexStatus_t
vex_SF_Milenage(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;
    uint64_t DataBlobAddr = 0;
    uint16_t TokenID;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;
    const VexTokenCmd_SF_Milenage_t * LocalCT_p = (const VexTokenCmd_SF_Milenage_t *)CommandToken_p;

    TokenID = vex_DeviceGetTokenID();

    // Format command token
    (void)memset(&CommandToken, 0, sizeof(CommandToken));

    switch (LocalCT_p->Operation)
    {
    case VEXTOKEN_MILENAGE_OP_SQNADMINCREATE:
        if (LocalCT_p->AssetId == 0U)
        {
            // SQN Administration Create
            Eip130Token_Command_SF_MilenageSqnAdminCreate(
                &CommandToken,
                LocalCT_p->AssetNumber,
                vex_ConvertFromUint8ToBool(LocalCT_p->fAMF_SBtest));
        }
        else
        {
            // SQN Administration Reset
            Eip130Token_Command_SF_MilenageSqnAdminReset(
                &CommandToken,
                LocalCT_p->AssetId);
        }
        break;

    case VEXTOKEN_MILENAGE_OP_AUTNVERIFICATION:
        if (LocalCT_p->AssetId != 0U)
        {
            Eip130Token_Command_SF_MilenageAutnVerificationSqn(
                &CommandToken,
                LocalCT_p->AssetId,
                LocalCT_p->RAND,
                LocalCT_p->AUTN);
        }
        else
        {
            Eip130Token_Command_SF_MilenageAutnVerification(
                &CommandToken,
                LocalCT_p->AssetNumber,
                LocalCT_p->RAND,
                LocalCT_p->AUTN);
        }
        break;

    case VEXTOKEN_MILENAGE_OP_AUTSGENERATION:
        // Note AMF is directly behind SQN
        Eip130Token_Command_SF_MilenageAutsGeneration(
            &CommandToken,
            LocalCT_p->AssetNumber,
            LocalCT_p->RAND,
            LocalCT_p->SQN);
        break;

    case VEXTOKEN_MILENAGE_OP_SQNADMINEXPORT:
        {
            const VexTokenCmd_SF_MilenageExport_t * Local2CT_p = (const VexTokenCmd_SF_MilenageExport_t *)CommandToken_p;

            DataBlobAddr = BufManager_Map(vex_ConvertFromUint32ToBool(Local2CT_p->fFromUserSpace),
                                          BUFMANAGER_BUFFERTYPE_OUT,
                                          Local2CT_p->DataBlob_p,
                                          Local2CT_p->DataBlobSize,
                                          (void *)&TokenID);
            if (DataBlobAddr != 0U)
            {
                Eip130Token_Command_SF_MilenageSqnAdminExport(
                    &CommandToken,
                    Local2CT_p->AssetId,
                    Local2CT_p->KekAssetId,
                    DataBlobAddr,
                    (uint32_t)BufManager_GetSize(DataBlobAddr),
                    Local2CT_p->AssociatedData,
                    Local2CT_p->AssociatedDataSize);
            }
            else
            {
                funcres = VEX_NO_MEMORY;
            }
        }
        break;

    case VEXTOKEN_MILENAGE_OP_CONFORMANCECHECK:
        // Note AMF is directly behind SQN
        Eip130Token_Command_SF_MilenageConformance(
            &CommandToken,
            LocalCT_p->RAND,
            LocalCT_p->SQN,
            LocalCT_p->K,
            LocalCT_p->OP);
        break;

    default:
        funcres = VEX_UNSUPPORTED;
        break;
    }

    if (funcres == VEX_SUCCESS)
    {
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
            VexTokenRslt_SF_Milenage_t * LocalRT_p = (VexTokenRslt_SF_Milenage_t *)ResultToken_p;

            LocalRT_p->Result = Eip130Token_Result_Code(&ResultToken);
            if (LocalRT_p->Result >= 0)
            {
                switch (LocalCT_p->Operation)
                {
                case VEXTOKEN_MILENAGE_OP_SQNADMINCREATE:
                    if (LocalCT_p->AssetId == 0U)
                    {
                        Eip130Token_Result_SF_MilenageSqnAdminCreate(&ResultToken,
                                                                     &LocalRT_p->AssetId);

                    }
                    break;

                case VEXTOKEN_MILENAGE_OP_AUTNVERIFICATION:
                    LocalRT_p->EMMCause = 0;
                    Eip130Token_Result_SF_MilenageAutnVerification(&ResultToken,
                                                                   LocalRT_p->RES,
                                                                   LocalRT_p->CK,
                                                                   LocalRT_p->IK);
                    if (LocalCT_p->AssetId == 0U)
                    {
                        Eip130Token_Result_SF_MilenageAutnVerificationSQNAMF(&ResultToken,
                                                                             LocalRT_p->SQN);
                    }
                    break;

                case VEXTOKEN_MILENAGE_OP_AUTSGENERATION:
                    Eip130Token_Result_SF_MilenageAuts(&ResultToken,
                                                       LocalRT_p->AUTS);
                    break;

                case VEXTOKEN_MILENAGE_OP_SQNADMINEXPORT:
                    {
                        VexTokenRslt_SF_MilenageExport_t * Local2RT_p = (VexTokenRslt_SF_MilenageExport_t *)ResultToken_p;
                        Eip130Token_Result_SF_MilenageSqnAdminExport(&ResultToken,
                                                                     &Local2RT_p->DataBlobSize);
                        // Copy output data
                        fCopy = true;
                    }
                    break;

                case VEXTOKEN_MILENAGE_OP_CONFORMANCECHECK:
                    Eip130Token_Result_SF_MilenageConformance(&ResultToken,
                                                              LocalRT_p->RES,
                                                              LocalRT_p->CK,
                                                              LocalRT_p->IK,
                                                              LocalRT_p->MACA,
                                                              LocalRT_p->MACS,
                                                              LocalRT_p->AK,
                                                              LocalRT_p->AKstar,
                                                              LocalRT_p->OPc);
                    break;

                default:
                    /* MISRA - Intentially empty */
                    break;
                }
            }
            else
            {
                switch (LocalCT_p->Operation)
                {
                case VEXTOKEN_MILENAGE_OP_AUTNVERIFICATION:
                    if ((LocalRT_p->Result | (int32_t)EIP130TOKEN_RESULT_FASVC) == EIP130TOKEN_RESULT_VERIFY_ERROR)
                    {
                        Eip130Token_Result_SF_MilenageAutnVerificationEMMCause(&ResultToken,
                                                                               &LocalRT_p->EMMCause);
                        if (LocalRT_p->EMMCause == 21U)
                        {
                            Eip130Token_Result_SF_MilenageAuts(&ResultToken, LocalRT_p->AUTS);
                        }
                        else
                        {
                            (void)memset(LocalRT_p->AUTS, 0, sizeof(LocalRT_p->AUTS));
                        }
                    }
                    break;

                case VEXTOKEN_MILENAGE_OP_SQNADMINCREATE:
                    break;
                case VEXTOKEN_MILENAGE_OP_SQNADMINEXPORT:
                    break;
                case VEXTOKEN_MILENAGE_OP_CONFORMANCECHECK:
                    break;
                case VEXTOKEN_MILENAGE_OP_AUTSGENERATION:
                    break;
                default:
                    /* MISRA - Intentially empty */
                    break;
                }
            }
        }
    }

    // Release used buffers, if needed
    if (DataBlobAddr != 0U)
    {
        int32_t rc = BufManager_Unmap(DataBlobAddr, true, fCopy, 0U);
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

#endif /* VEX_ENABLE_SF_MILENAGE */

/* end of file adapter_vex_sf_milenage.c */
