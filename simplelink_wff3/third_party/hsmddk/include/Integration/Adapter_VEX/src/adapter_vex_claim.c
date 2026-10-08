/* adapter_vex_claim.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the services with which the exclusive mailbox locking
 * can be controlled.
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


/*----------------------------------------------------------------------------
 * vex_Claim
 */
VexStatus_t
vex_Claim(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    uint32_t Identity;
    int32_t retval;
    uint8_t MailboxNumber;

    // Get and set identity of calling process
    Identity = vex_IdentityGet();
    if (Identity == 0U)
    {
        funcres = VEX_NO_IDENTITY;
    }
    else
    {
        // Get mailbox number to use
        MailboxNumber = vex_MailboxGet(Identity);
        if (MailboxNumber == 0U)
        {
            funcres = VEX_NO_MAILBOX;
        }
        else
        {
            switch (CommandToken_p->SubCode)
            {
            case VEXTOKEN_SUBCODE_CLAIM_EXCL:
                retval = vex_DeviceLinkMailbox(MailboxNumber, Identity);
                if (retval != 0)
                {
                    if (retval == -5)
                    {
                        funcres = VEX_MAILBOX_IN_USE;
                    }
                    else
                    {
                        funcres = VEX_INTERNAL_ERROR;
                    }
                }
                break;
            case VEXTOKEN_SUBCODE_CLAIM_EXCL_OVERRULE:
                retval = vex_DeviceLinkMailboxOverrule(MailboxNumber, Identity);
                if (retval != 0)
                {
                    funcres = VEX_INTERNAL_ERROR;
                }
                break;
            case VEXTOKEN_SUBCODE_CLAIM_RELEASE:
                retval = vex_DeviceUnlinkMailbox(MailboxNumber, Identity);
                if (retval != 0)
                {
                    funcres = VEX_INTERNAL_ERROR;
                }
                break;
            default:
                funcres = VEX_UNSUPPORTED;
                break;
            }

            if (funcres == VEX_SUCCESS)
            {
                ResultToken_p->Result = 0;
            }
        }
    }

    return funcres;
}

/* end of file adapter_vex_claim.c */
