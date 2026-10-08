/* adapter_vex_sym_hash.c
 *
 * Implementation of the VEX API.
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

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>          // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>   // API implementation
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_hash.h>

#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>

static uint64_t gl_DataAddr = 0U;

/*----------------------------------------------------------------------------
 * vex_SymHash
 */
VexStatus_t
vex_SymHash(
        const VexTokenCmd_Hash_t * const CommandToken_p,
        VexTokenRslt_Hash_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fInitWithDefault;
    bool fFinalize;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    switch (CommandToken_p->Mode)
    {
    default:
        /* MISRA - Intentially no break here */
    case VEXTOKEN_MODE_HASH_MAC_INIT2FINAL:
        fInitWithDefault = true;
        fFinalize = true;
        break;

    case VEXTOKEN_MODE_HASH_MAC_CONT2FINAL:
        fInitWithDefault = false;
        fFinalize = true;
        break;

    case VEXTOKEN_MODE_HASH_MAC_INIT2CONT:
        fInitWithDefault = true;
        fFinalize = false;
        break;

    case VEXTOKEN_MODE_HASH_MAC_CONT2CONT:
        fInitWithDefault = false;
        fFinalize = false;
        break;
    }

    if (CommandToken_p->DataSize != 0U)
    {
        // Convert input buffer and get address for token
        gl_DataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                  BUFMANAGER_BUFFERTYPE_IN,
                                  CommandToken_p->Data_p,
                                  CommandToken_p->DataSize,
                                  NULL);
        if (gl_DataAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
    }
    else if (!fInitWithDefault || !fFinalize)
    {
        funcres = VEX_INVALID_LENGTH;
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    if (funcres == VEX_SUCCESS)
    {
        // Format command token
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        Eip130Token_Command_Hash(&CommandToken,
                                 (uint8_t)CommandToken_p->Algorithm,
                                 fInitWithDefault,
                                 fFinalize,
                                 gl_DataAddr,
                                 CommandToken_p->DataSize);
        if (CommandToken_p->TempAssetId != 0U)
        {
            Eip130Token_Command_Hash_SetStateASID(
                &CommandToken,
                CommandToken_p->TempAssetId);
        }
        else
        {
            Eip130Token_Command_Hash_CopyState(
                &CommandToken,
                CommandToken_p->Digest,
                sizeof(CommandToken_p->Digest));
        }
        {
            uint64_t TotalMessageLength;
            TotalMessageLength = (uint64_t)(((uint64_t)CommandToken_p->TotalMessageLengthHi << 32) +
                                             (uint64_t)CommandToken_p->TotalMessageLengthLo);
            Eip130Token_Command_Hash_SetTotalMessageLength(
                &CommandToken,
                TotalMessageLength);
        }
        Eip130Token_Command_SetTokenID(&CommandToken, vex_DeviceGetTokenID(), false);

        // Initialize result token
        (void)memset(&ResultToken, 0, sizeof(ResultToken));

        // Exchange token with the EIP-130 HW
        funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_SymHash_PostProcessing
 */
VexStatus_t
vex_SymHash_PostProcessing(
        const VexTokenCmd_Hash_t * const CommandToken_p,
        VexTokenRslt_Hash_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fFinalize = false;

    switch(CommandToken_p->Mode)
    {
        case VEXTOKEN_MODE_HASH_MAC_INIT2FINAL:
        case VEXTOKEN_MODE_HASH_MAC_CONT2FINAL:
            fFinalize = true;
        default:
            fFinalize = false;
            break;
    }

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if ((ResultToken_p->Result >= 0) &&
        (fFinalize || (CommandToken_p->TempAssetId == 0U)))
    {
        // Copy digest from result
        Eip130Token_Result_Hash_CopyState(
            ResultTokenP_p,
            sizeof(ResultToken_p->Digest),
            ResultToken_p->Digest);
    }

    if (gl_DataAddr != 0U)
    {
        // Release used buffer, if needed
        (void)BufManager_Unmap(gl_DataAddr, false, false, 0U);
    }

    gl_DataAddr = 0;

    return funcres;
}


/* end of file adapter_vex_sym_hash.c */
