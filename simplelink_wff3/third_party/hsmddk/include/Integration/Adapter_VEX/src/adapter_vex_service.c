/* adapter_vex_service.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the service services.
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
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_service.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_otp.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>     // bufmanager for firmwarecheck


/*----------------------------------------------------------------------------
 * vex_Service
 */
VexStatus_t
vex_Service(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;
#ifdef VEX_ENABLE_FIRMWARE_LOAD
    uint64_t SrcDataAddr = 0;
#endif

    // Format command token
    (void)memset(&CommandToken, 0, sizeof(CommandToken));
    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_REGISTERREAD:
        {
            const VexTokenCmd_Register_t * const LocalCommandToken_p = (VexTokenCmd_Register_t *)CommandToken_p;
            Eip130Token_Command_RegisterRead(
                &CommandToken,
                (uint16_t)LocalCommandToken_p->Address);
        }
        break;

    case VEXTOKEN_SUBCODE_REGISTERWRITE:
        {
            const VexTokenCmd_Register_t * const LocalCommandToken_p = (VexTokenCmd_Register_t *)CommandToken_p;
            Eip130Token_Command_RegisterWrite(
                &CommandToken,
                (uint16_t)LocalCommandToken_p->Address,
                LocalCommandToken_p->Value);
        }
        break;

    case VEXTOKEN_SUBCODE_CLOCKSWITCH:
        {
            const VexTokenCmd_ClockSwitch_t * const LocalCommandToken_p = (VexTokenCmd_ClockSwitch_t *)CommandToken_p;
            Eip130Token_Command_ClockSwitch(
                &CommandToken,
                LocalCommandToken_p->On,
                LocalCommandToken_p->Off);
        }
        break;

    case VEXTOKEN_SUBCODE_ZEROOUTMAILBOX:
        Eip130Token_Command_ZeroizeOutputMailbox(&CommandToken);
        break;

    case VEXTOKEN_SUBCODE_SELECTOTPZERO:
        Eip130Token_Command_OTPSelectZeroize(&CommandToken);
        break;

    case VEXTOKEN_SUBCODE_ZEROIZEOTP:
        Eip130Token_Command_OTPZeroize(&CommandToken);
        break;

#ifdef VEX_ENABLE_FIRMWARE_LOAD
    case VEXTOKEN_SUBCODE_FIRMWARECHECK:
        {
            const VexTokenCmd_FirmwareCheck_t * const LocalCommandToken_p = (VexTokenCmd_FirmwareCheck_t *)CommandToken_p;
            // Convert input buffer and get address for token
            SrcDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                        BUFMANAGER_BUFFERTYPE_IN,
                                        LocalCommandToken_p->FirmwareImage_p,
                                        LocalCommandToken_p->FirmwareImageSize,
                                        NULL);
            if (SrcDataAddr == 0U)
            {
                funcres = VEX_DATA_MAPPING_ERROR;
            }
            else
            {
                Eip130Token_Command_FirmwareCheck(
                    &CommandToken,
                    SrcDataAddr,
                    LocalCommandToken_p->FirmwareImageSize);
            }
        }
        break;
    case VEXTOKEN_SUBCODE_UPDATEROLLBACKID:
        {
            const VexTokenCmd_UpdateRollbackID_t * const LocalCommandToken_p = (VexTokenCmd_UpdateRollbackID_t *)CommandToken_p;
            Eip130Token_Command_UpdateRollbackID(
                &CommandToken,
                LocalCommandToken_p->RollbackID);
        }
        break;
#endif

    default:
        funcres = VEX_UNSUPPORTED;
        break;
    }

    if (funcres == VEX_SUCCESS)
    {
        Eip130Token_Command_SetTokenID(&CommandToken, vex_DeviceGetTokenID(), false);

        // Initialize result token
        (void)memset(&ResultToken, 0, sizeof(ResultToken));

        // Exchange token with the EIP-130 HW
        funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
        if (funcres == VEX_SUCCESS)
        {
            ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
            if ((ResultToken_p->Result >= 0) &&
                (CommandToken_p->SubCode == (uint32_t)VEXTOKEN_SUBCODE_REGISTERREAD))
            {
                // Success
                ((VexTokenRslt_Register_t *)ResultToken_p)->Value = ResultToken.W[1];
            }
        }

#ifdef VEX_ENABLE_FIRMWARE_LOAD
        if (SrcDataAddr != 0U)
        {
            (void)BufManager_Unmap(SrcDataAddr, false, false, 0U);
        }
#endif
    }

    return funcres;
}

/* end of file adapter_vex_service.c */
