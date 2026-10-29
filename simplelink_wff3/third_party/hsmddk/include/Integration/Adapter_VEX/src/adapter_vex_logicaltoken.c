/* adapter_vex_logicaltoken.c
 *
 * Implementation of the VEX API.
 *
 * This file contains the logical token exchange implementation between the
 * VAL API and VEX API.
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

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             // uint16_t, uint32_t, bool
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>            // API to implement
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>   // vex_*() and VexToken_Command/Result_t
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_alloc.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_sleep.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_getpid.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_types.h>           // DMAResource_Handle_t/Properties_t/AddrPair_t
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_buf.h>             // DMAResource_Alloc/Release

/*----------------------------------------------------------------------------
 * vexLocal_LogicalToken
 *      Execute the logical token request
 */
VexStatus_t
vex_LogicalToken(const VexTokenCmd_Generic_t * const CommandToken_p,
                      VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_LOCK_TIMEOUT;

    if (vex_DeviceGetHandle() != NULL)
    {
        /* Device connection is available */
        switch (CommandToken_p->OpCode)
        {
        case VEXTOKEN_OPCODE_NOP:
            funcres = vex_Nop((VexTokenCmd_Nop_t *)CommandToken_p, ResultToken_p);
            break;

        case VEXTOKEN_OPCODE_ENCRYPTION:
            if (CommandToken_p->SubCode == VEXTOKEN_SUBCODE_AUTHENCRYPT)
            {
                funcres = vex_SymCipherAE((VexTokenCmd_CipherAE_t *)CommandToken_p,
                                          (VexTokenRslt_CipherAE_t *)ResultToken_p);
            }
            else if (CommandToken_p->SubCode == VEXTOKEN_SUBCODE_ENCRYPT)
            {
                funcres = vex_SymCipher((VexTokenCmd_Cipher_t *)CommandToken_p,
                                        (VexTokenRslt_Cipher_t *)ResultToken_p);
            }
            else
            {
                funcres = VEX_INVALID_SUBCODE;
            }
            break;

        case VEXTOKEN_OPCODE_HASH:
            funcres = vex_SymHash((VexTokenCmd_Hash_t *)CommandToken_p,
                                    (VexTokenRslt_Hash_t *)ResultToken_p);
            break;

        case VEXTOKEN_OPCODE_MAC:
            funcres = vex_SymMac((VexTokenCmd_Mac_t *)CommandToken_p,
                                    (VexTokenRslt_Mac_t *)ResultToken_p);
            break;

        case VEXTOKEN_OPCODE_TRNG:
            funcres = vex_Trng(CommandToken_p, ResultToken_p);
            break;

#ifdef VEX_ENABLE_SF
        case VEXTOKEN_OPCODE_SPECIALFUNCTIONS:
            funcres = vex_SpecialFunctions(CommandToken_p, ResultToken_p);
            break;
#endif

        case VEXTOKEN_OPCODE_SYMWRAP:
            {
                funcres = vex_SymKeyWrap((VexTokenCmd_KeyWrap_t *)CommandToken_p,
                                            (VexTokenRslt_KeyWrap_t *)ResultToken_p);
            }
            break;

        case VEXTOKEN_OPCODE_ASSETMANAGEMENT:
            funcres = vex_Asset(CommandToken_p, ResultToken_p);
            break;

        case VEXTOKEN_OPCODE_AUTH_UNLOCK:
            funcres = vex_AUnlock(CommandToken_p, ResultToken_p);
            break;

        case VEXTOKEN_OPCODE_PUBLIC_KEY:
            funcres = vex_Asym(CommandToken_p, ResultToken_p);
            break;

        case VEXTOKEN_OPCODE_SERVICE:
            funcres = vex_Service(CommandToken_p, ResultToken_p);
            break;

        case VEXTOKEN_OPCODE_SYSTEM:
            funcres = vex_System(CommandToken_p, ResultToken_p);
            break;

#ifdef VEX_ENABLE_HW_FUNCTIONS
        case VEXTOKEN_OPCODE_HARDWARE:
            funcres = vex_Hardware(CommandToken_p, ResultToken_p);
            break;
#endif

        case VEXTOKEN_OPCODE_CLAIMCONTROL:
            funcres = vex_Claim(CommandToken_p, ResultToken_p);
            break;

        default:
            funcres = VEX_INVALID_OPCODE;
            break;
        }
    }
    else
    {
        funcres = VEX_NOT_CONNECTED;
    }

    return funcres;
}

/* end of file adapter_vex_logicaltoken.c */
