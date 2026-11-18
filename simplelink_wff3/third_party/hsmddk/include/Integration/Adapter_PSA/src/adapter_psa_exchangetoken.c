/* adapter_psa_ExchangeToken.c
 *
 * Send the provided token to the VEX layer.
 *
 * This file contains the token exchange with the next driver level.
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

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/c_adapter_psa.h>              // configuration
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>                 // uint32_t
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                       // size_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>                // VexStatus_t, VexTokenCmd_*_t, VexTokenRslt_*_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal_ext.h>   // ADAPTER_PSA_INTERNAL_USER_SPACE_FLAG

/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * psaInt_ExchangeToken
 *
 * Send the provided token to the VEX layer.
 */
psa_status_t
psaInt_ExchangeToken(VexTokenCmd_Generic_t * const CommandToken_p,
                     const uint32_t CommandTokenSize,
                     VexTokenRslt_Generic_t * const ResultToken_p,
                     const uint32_t ResultTokenSize)
{
    psa_status_t retval = PSA_SUCCESS;
    VexStatus_t funcres;

#ifdef PSA_STRICT_ARGS
    if ((NULL == CommandToken_p) || (NULL == ResultToken_p))
    {
        retval = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
#endif
    {
        /* Send the token to the VEX layer */
        CommandToken_p->fFromUserSpace = ADAPTER_PSA_INTERNAL_USER_SPACE_FLAG;
        funcres = vex_LogicalToken(CommandToken_p, ResultToken_p);
        if (VEX_SUCCESS != funcres)
        {
#ifdef PSA_LOG_LOWLEVEL_ERROR
            LOG_WARN("Abort - %s()=%d\n", __func__, funcres);
#endif
            retval = PSA_ERROR_HARDWARE_FAILURE;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return retval;
}


/* end of file adapter_psa_ExchangeToken.c */
