/* adapter_vex_physicaltoken.c
 *
 * Implementation of the VEX API.
 *
 * This file contains the physical token exchange implementation between the
 * VEX API and EIP-130 hardware.
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

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             // uint16_t
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>   // API implementation
#include <third_party/hsmddk/include/Kit/EIP130/MailboxControl/incl/eip130.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_interrupts.h>

/*----------------------------------------------------------------------------
 * vex_PhysicalTokenExchange
 */
VexStatus_t
vex_PhysicalTokenExchange(
        Eip130Token_Command_t * const CommandToken_p,
        Eip130Token_Result_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    Device_Handle_t Device;
    uint32_t Identity;
    uint8_t MailboxNumber;

    // Get identity of calling process
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
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
            Eip130Token_Command_SetTokenID(CommandToken_p, vex_DeviceGetTokenID(), true);
#else
            Eip130Token_Command_SetTokenID(CommandToken_p, vex_DeviceGetTokenID(), false);
#endif
            // Set identity in the token
            switch (CommandToken_p->W[0] & ((Eip130TokenWord_t)MASK_8_BITS << 24))
            {
            case (EIP130TOKEN_OPCODE_ASSETMANAGEMENT | EIP130TOKEN_SUBCODE_PROVISIONRANDOMHUK):
                // Use the provided identity for the Provision Random HUK token
                break;
            case (EIP130TOKEN_OPCODE_SYSTEM | EIP130TOKEN_SUBCODE_LOGIN):
                // Use the Officer ID that was defined at build level for the Login token
                Eip130Token_Command_Identity(CommandToken_p, VEX_CRYPTO_OFFICER_ID);
                break;
            default:
                // Use the identity of calling process for all other tokens
                Eip130Token_Command_Identity(CommandToken_p, Identity);
                break;
            }

            // Get device reference
            Device = vex_DeviceGetHandle();
            if (Device == NULL)
            {
                funcres = VEX_NOT_CONNECTED;
            }
            else
            {
                // Link the mailbox for use
                funcres = vex_DeviceLinkMailbox(MailboxNumber, Identity);
                if (funcres != VEX_SUCCESS)
                {
                    LOG_CRIT(VEX_LOG_PREFIX "%s: vex_DeviceLinkMailbox()=%d\n", __func__, funcres);
                    if (funcres >= -2)
                    {
                        funcres = VEX_INTERNAL_ERROR;
                    }
                    else
                    {
                        funcres = VEX_MAILBOX_IN_USE;
                    }
                }

                if (funcres == VEX_SUCCESS)
                {
#if (VEX_TRACE_TOKENS > 1)
                    int32_t funcres2;
                    LOG_CRIT(VEX_LOG_PREFIX "CommandToken (non-zero words only):\n");
                    for (funcres2 = 0; funcres2 < (int32_t)EIP130TOKEN_COMMAND_WORDS; funcres2++)
                    {
                        if (CommandToken_p->W[funcres2] != 0)
                        {
                            LOG_CRIT("\tW%02d=0x%08X\n", funcres2, CommandToken_p->W[funcres2]);
                        }
                    }
#elif (VEX_TRACE_TOKENS > 0)
                    LOG_CRIT(VEX_LOG_PREFIX "CommandToken 0x%08X\n", CommandToken_p->W[0]);
#endif
                    // Must be enabled before token is submitted, not to loose the interrupt
                    (void)Adapter_Interrupt_ClearAndEnable((int32_t)((2U * (MailboxNumber - 1U)) + 1U), 0U);

                    // Write the command token to the IN mailbox
                    // Note: It also checks that the mailbox is empty
                    switch (EIP130_MailboxWriteAndSubmitToken(Device,
                                                              MailboxNumber,
                                                              CommandToken_p,
                                                              true))
                    {
                    case 0:
                        break;
                    case -3:                        /* Token cannot be sent (Mailbox full or HW/FW issue) */
                        funcres = VEX_MAILBOX_IN_USE;
                        break;
                    case -4:                        /* Handover failed (Is HW active?) */
                        vex_DeviceStateIssue();     /* Report device state issue detected */
                        funcres = VEX_POWER_STATE_ERROR;
                        break;
                    default:
                        funcres = VEX_INTERNAL_ERROR;
                        break;
                    }
                }
            }
        }
    }

    return funcres;
}


/* end of file adapter_vex_physicaltoken.c */
