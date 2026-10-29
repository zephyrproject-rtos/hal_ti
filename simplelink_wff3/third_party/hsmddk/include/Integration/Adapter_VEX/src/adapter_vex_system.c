/* adapter_vex_system.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the system services.
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
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_system.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_service.h>


/*----------------------------------------------------------------------------
 * vex_System
 */
VexStatus_t
vex_System(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;
    uint16_t TokenID = vex_DeviceGetTokenID();
    int32_t NrCommands = 1;

    // Format command token
    (void)memset(&CommandToken, 0, sizeof(CommandToken));
    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_SYSTEMINFO:
        Eip130Token_Command_SystemInfo(&CommandToken);
        break;

    case VEXTOKEN_SUBCODE_SELFTEST:
        Eip130Token_Command_SystemSelfTest(&CommandToken);
        break;

    case VEXTOKEN_SUBCODE_RESET:
        Eip130Token_Command_SystemReset(&CommandToken);
        NrCommands = 2;                 // Perform additional verify command
        break;

    case VEXTOKEN_SUBCODE_LOGIN:
        Eip130Token_Command_SystemLogin(&CommandToken);
        break;

#ifdef VEX_ENABLE_FIRMWARE_SLEEP
    case VEXTOKEN_SUBCODE_SLEEP:
    case VEXTOKEN_SUBCODE_RESUMEFROMSLEEP:
        {
            VexStatus_t rc;

            if (CommandToken_p->SubCode == (uint32_t)VEXTOKEN_SUBCODE_SLEEP)
            {
                rc = vex_DeviceSleep();
            }
            else
            {
                rc = vex_DeviceResumeFromSleep();
            }

            // Remove the FAsvc bit setting before further processing
            if(rc < 0)
            {
                rc = (VexStatus_t)((uint32_t)rc |
                                   (uint32_t)EIP130TOKEN_RESULT_FASVC);
            }
            else
            {
                rc = (VexStatus_t)((uint32_t)rc &
                                   ~(uint32_t)EIP130TOKEN_RESULT_FASVC);
            }

            switch (rc)
            {
            default:
                if (rc < -256)
                {
                    // Successful, but a firmware error
                    ResultToken_p->Result = rc + 256;
                    break;
                }
                // Save result for tracing purpose
                ResultToken_p->Result = rc;
                funcres = VEX_INTERNAL_ERROR;
                break;
            case 0:
                // Successful
                NrCommands = 0;
                funcres = VEX_SUCCESS;
                break;
            case -1:
                funcres = VEX_UNSUPPORTED;
                break;
            case -2:
                funcres = VEX_OPERATION_NOT_ALLOWED;
                break;
            case -3:
                funcres = VEX_OPERATION_FAILED;
                break;
            case -4:
                funcres = VEX_POWER_STATE_ERROR;
                break;
            }
            break;
        }
#endif

    default:
        funcres = VEX_UNSUPPORTED;
        break;
    }

    if ((NrCommands > 0) && (funcres == VEX_SUCCESS))
    {
        // Initialize result token
        (void)memset(&ResultToken, 0, sizeof(ResultToken));

        for (; NrCommands > 0; NrCommands--)
        {
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
            Eip130Token_Command_SetTokenID(&CommandToken, TokenID, true);
#else
            Eip130Token_Command_SetTokenID(&CommandToken, TokenID, false);
#endif
            // Exchange token with the EIP-130 HW
            funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
            if (funcres == VEX_SUCCESS)
            {
                Eip130TokenWord_t SubCode = (CommandToken.W[0] & ((Eip130TokenWord_t)0x0f << 28));

                ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
                if (ResultToken_p->Result >= 0)
                {
                    // Success
                    if (SubCode == (Eip130TokenWord_t)VEXTOKEN_SUBCODE_SYSTEMINFO)
                    {
                        VexTokenRslt_SystemInfo_t * LocalRT_p = (VexTokenRslt_SystemInfo_t *)ResultToken_p;

#ifdef VEX_ENABLE_FIRMWARE_LOAD
                        LocalRT_p->Firmware.RollbackId = (uint8_t)(ResultToken.W[1] >> 24);
#else
                        LocalRT_p->Firmware.RollbackId = 0;
#endif
                        LocalRT_p->Firmware.Major = (uint8_t)(ResultToken.W[1] >> 16);
                        LocalRT_p->Firmware.Minor = (uint8_t)(ResultToken.W[1] >> 8);
                        LocalRT_p->Firmware.Patch = (uint8_t)(ResultToken.W[1] >> 0);

                        LocalRT_p->Hardware.Major = (uint8_t)(ResultToken.W[2] >> 16);
                        LocalRT_p->Hardware.Minor = (uint8_t)(ResultToken.W[2] >> 8);
                        LocalRT_p->Hardware.Patch = (uint8_t)(ResultToken.W[2] >> 0);
                        LocalRT_p->Hardware.MemorySizeInBytes = (uint16_t)ResultToken.W[3];

                        LocalRT_p->OTP.ErrorLocation = (uint16_t)(ResultToken.W[5] & MASK_12_BITS);
                        LocalRT_p->OTP.ErrorCode = (uint8_t)((ResultToken.W[5] >> 12) & MASK_4_BITS);

                        LocalRT_p->Self.Identity = ResultToken.W[4];
                        LocalRT_p->Self.HostID = (uint8_t)((ResultToken.W[3] >> 16) & MASK_3_BITS);
                        LocalRT_p->Self.NonSecure = (uint8_t)((ResultToken.W[3] >> 19) & MASK_1_BIT);
                        LocalRT_p->Self.CryptoOfficer = (uint8_t)((ResultToken.W[3] >> 27) & MASK_1_BIT);
                        LocalRT_p->Self.Mode = (uint8_t)((ResultToken.W[3] >> 28) & MASK_4_BITS);
                        LocalRT_p->Self.ErrorTest = (uint8_t)((ResultToken.W[5] >> 16) & MASK_8_BITS);
                    }
                    else if (SubCode == (Eip130TokenWord_t)VEXTOKEN_SUBCODE_RESET)
                    {
                        // Wait until reset is finished and immediately restore login state
                        Eip130Token_Command_SystemLogin(&CommandToken);
                        TokenID = vex_DeviceGetTokenID();
                    }
                    else
                    {
                        /* MISRA - Intentially empty */
                    }
                }
                else
                {
                    // Error
                    if (SubCode == (Eip130TokenWord_t)EIP130TOKEN_SUBCODE_LOGIN)
                    {
                        // Ignore FAsvc bit setting for this token
                        ResultToken_p->Result = (int32_t)((uint32_t)ResultToken_p->Result |
                                                          (uint32_t)EIP130TOKEN_RESULT_FASVC);
                        if (ResultToken_p->Result == EIP130TOKEN_RESULT_INVALID_TOKEN)
                        {
                            // Login token not support, so must be regarded as no error
                            ResultToken_p->Result = EIP130TOKEN_RESULT_SUCCESS;
                        }
                    }
                }
            }
        }
    }

    return funcres;
}


/* end of file adapter_vex_system.c */
