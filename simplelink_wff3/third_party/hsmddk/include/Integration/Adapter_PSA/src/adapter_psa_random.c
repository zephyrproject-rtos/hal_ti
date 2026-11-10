/* adapter_psa_random.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the random data related services.
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
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>                 // uint16_t
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                       // size_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>                 // the API to implement
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>                // VexTokenCmd_*_t, VexTokenRslt_*_t
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_exchangetoken.h>

/*----------------------------------------------------------------------------
 * psa_generate_random
 */
psa_status_t
psa_generate_random(uint8_t * output,
                    size_t output_size)
{
    VexTokenCmd_Random_t t_cmd;
    VexTokenRslt_Generic_t t_res;
    psa_status_t funcres;

    if ((NULL == output) ||
        (0U == output_size) || (65535U < output_size))
    {
        funcres = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        /* Format service request */
        t_cmd.OpCode = (uint32_t)VEXTOKEN_OPCODE_TRNG;
        t_cmd.SubCode = (uint32_t)VEXTOKEN_SUBCODE_RANDOMNUMBER;
        t_cmd.Data_p = (uint8_t *)output;
        t_cmd.Size = (uint16_t)output_size;
        t_res.Result = 0;

        /* Exchange service request with the next driver level */
        funcres = psaInt_ExchangeToken((VexTokenCmd_Generic_t *)&t_cmd,
                                       sizeof(t_cmd),
                                       (VexTokenRslt_Generic_t *)&t_res,
                                       sizeof(t_res));
        if (PSA_SUCCESS == funcres)
        {
            if (0 > t_res.Result)
            {
#ifdef PSA_LOG_LOWLEVEL_ERROR
                LOG_WARN("Abort - %s()=%d\n", __func__, t_res.Result);
#endif
                funcres = PSA_ERROR_CORRUPTION_DETECTED;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return funcres;
}


/* end of file adapter_psa_random.c */


