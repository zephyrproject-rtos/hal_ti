/* adapter_vex_hardware.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the hardware registers related services.
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

#ifdef VEX_ENABLE_HW_FUNCTIONS

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>       // API implementation
#include <third_party/hsmddk/include/Kit/EIP130/MailboxControl/incl/eip130.h>                     // EIP-130 interface


/*----------------------------------------------------------------------------
 * vex_Hardware
 */
VexStatus_t
vex_Hardware(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    Device_Handle_t Device;

    Device = vex_DeviceGetHandle();
    if (Device == NULL)
    {
        funcres = VEX_NOT_CONNECTED;
    }
    else
    {
        // Format result token
        ResultToken_p->Result = EIP130TOKEN_RESULT_SUCCESS;
        switch (CommandToken_p->SubCode)
        {
        case VEXTOKEN_SUBCODE_MODULESTATUS:
            {
                VexTokenRslt_ModuleStatus_t * LocalRT_p = (VexTokenRslt_ModuleStatus_t *)ResultToken_p;

                EIP130_ModuleGetStatus(Device,
                                       &LocalRT_p->Bit0,
                                       &LocalRT_p->Bit1,
                                       &LocalRT_p->FatalError,
                                       &LocalRT_p->CRC24Ok,
                                       &LocalRT_p->CRC24Busy,
                                       &LocalRT_p->CRC24Error,
                                       &LocalRT_p->FwImageWritten,
                                       &LocalRT_p->FwImageCheckDone,
                                       &LocalRT_p->FwImageAccepted);
            }
            break;
        case VEXTOKEN_SUBCODE_EIP_OPTIONS:
            {
                VexTokenRslt_EipOptions_t * LocalRT_p = (VexTokenRslt_EipOptions_t *)ResultToken_p;

                EIP130_MailboxGetOptions(Device,
                                         &LocalRT_p->MyHostId,
                                         &LocalRT_p->MasterId,
                                         &LocalRT_p->Protection,
                                         &LocalRT_p->ProtectionAvailable,
                                         &LocalRT_p->nMailboxes,
                                         &LocalRT_p->MailboxSize,
                                         &LocalRT_p->HostId,
                                         &LocalRT_p->SecureHostId);
                EIP130_ModuleGetOptions(Device, NULL, NULL,
                                        &LocalRT_p->StandardEngines,
                                        &LocalRT_p->CustomEngines);
            }
            break;
        case VEXTOKEN_SUBCODE_EIP_VERSION:
            {
                VexTokenRslt_EipVersion_t * LocalRT_p = (VexTokenRslt_EipVersion_t *)ResultToken_p;

                EIP130_ModuleGetVersion(Device,
                                        &LocalRT_p->EipNumber,
                                        &LocalRT_p->MajorVersion,
                                        &LocalRT_p->MinorVersion,
                                        &LocalRT_p->PatchLevel);
            }
            break;
        default:
            funcres = VEX_UNSUPPORTED;
            break;
        }
    }

    return funcres;
}

#endif /* VEX_ENABLE_HW_FUNCTIONS */

/* end of file adapter_vex_hardware.c */
