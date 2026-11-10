/* adapter_vex_aunlock.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the Authenticated Unlock and Secure Debug services.
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
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_aunlock.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_otp.h>


/*----------------------------------------------------------------------------
 * vex_AUnlock
 */
VexStatus_t
vex_AUnlock(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;
    uint64_t SignAddr = 0;

    // Format command token
    (void)memset(&CommandToken, 0, sizeof(CommandToken));
    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_AUNLOCKSTART:
        {
            const VexTokenCmd_AuthUnlock_t * const LocalCT_p = (VexTokenCmd_AuthUnlock_t *)CommandToken_p;

            Eip130Token_Command_AUnlock_Start(
                &CommandToken,
                LocalCT_p->AuthStateAssetId,
                LocalCT_p->AuthKeyAssetId);
        }
        break;

    case VEXTOKEN_SUBCODE_AUNLOCKVERIFY:
        {
            const VexTokenCmd_AuthUnlock_t * const LocalCT_p = (VexTokenCmd_AuthUnlock_t *)CommandToken_p;

            if (LocalCT_p->Sign_p == NULL)
            {
                funcres = VEX_BAD_ARGUMENT;
            }
            else
            {
                // Get signature address for token
                SignAddr = BufManager_Map(vex_ConvertFromUint32ToBool(LocalCT_p->fFromUserSpace),
                                          BUFMANAGER_BUFFERTYPE_IN,
                                          LocalCT_p->Sign_p,
                                          LocalCT_p->SignSize,
                                          NULL);
                if (SignAddr == 0U)
                {
                    funcres = VEX_NO_MEMORY;
                }
                else
                {
                    Eip130Token_Command_AUnlock_Verify(
                        &CommandToken,
                        LocalCT_p->AuthStateAssetId,
                        LocalCT_p->Nonce,
                        SignAddr, LocalCT_p->SignSize);
                }
            }
        }
        break;

    case VEXTOKEN_SUBCODE_SETSECUREDEBUG:
        {
            const VexTokenCmd_SecureDebug_t * const LocalCT_p = (VexTokenCmd_SecureDebug_t *)CommandToken_p;

            Eip130Token_Command_SetSecureDebug(
                &CommandToken,
                LocalCT_p->AuthStateAssetId,
                vex_ConvertFromUint32ToBool(LocalCT_p->fSet));
        }
        break;

    default:
        funcres = VEX_UNSUPPORTED;
        break;
    }

    if (funcres == VEX_SUCCESS)
    {
        Eip130Token_Command_SetTokenID(&CommandToken,
                                       vex_DeviceGetTokenID(),
                                       false);

        // Initialize result token
        (void)memset(&ResultToken, 0, sizeof(ResultToken));

        // Exchange token with the EIP-130 HW
        funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
        if (funcres == VEX_SUCCESS)
        {
            ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
            if ((ResultToken_p->Result >= 0) &&
                (CommandToken_p->SubCode == (uint32_t)VEXTOKEN_SUBCODE_AUNLOCKSTART))
            {
                // Success - Copy AssetId and Nonce from result token
                Eip130Token_Result_AUnlock_CopyNonce(
                    &ResultToken,
                    ((VexTokenRslt_AuthUnlock_t *)ResultToken_p)->Nonce);
            }
        }

        if (SignAddr != 0U)
        {
            (void)BufManager_Unmap(SignAddr, false, false, 0U);
        }
    }

    return funcres;
}

/* end of file adapter_vex_aunlock.c */
