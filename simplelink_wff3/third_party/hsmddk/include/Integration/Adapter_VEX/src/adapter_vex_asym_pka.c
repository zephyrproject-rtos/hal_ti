/* adapter_vex_asym_pka.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the asymmetric crypto services for direct PKA/PKCP use.
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

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_intern_asym.h>   // API implementation
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_pk.h>

static volatile uint16_t gl_TokenID;

static uint64_t gl_VectorAddr = 0;
static uint64_t gl_InputAddr = 0;
static uint64_t gl_OutputAddr = 0;

/*----------------------------------------------------------------------------
 * vex_Asym_PkaNumSet
 */
VexStatus_t
vex_Asym_PkaNumSet(
        const VexTokenCmd_PkOperation_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    // Format command token
    (void)memset(&CommandToken, 0, sizeof(CommandToken));
    Eip130Token_Command_Pk_Claim(&CommandToken,
                                 CommandToken_p->Nwords,
                                 CommandToken_p->Mwords,
                                 CommandToken_p->Mmask);

    gl_TokenID = vex_DeviceGetTokenID();

#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
    Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, true);
#else
    Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, false);
#endif

    // Initialize result token
    (void)memset(&ResultToken, 0, sizeof(ResultToken));

    // Exchange token with the EIP-130 HW
    return vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
}

/*----------------------------------------------------------------------------
 * vex_Asym_PkaNumSet_Post
 */
VexStatus_t
vex_Asym_PkaNumSet_Post(
        const VexTokenCmd_PkOperation_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);

    gl_TokenID = 0;

    return funcres;
}


/*----------------------------------------------------------------------------
 * vex_Asym_PkaNumLoad
 */
VexStatus_t
vex_Asym_PkaNumLoad(
        const VexTokenCmd_PkOperation_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    // Get Vector input address for token
    gl_VectorAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                BUFMANAGER_BUFFERTYPE_IN,
                                CommandToken_p->InData_p,
                                CommandToken_p->InDataSize,
                                NULL);
    if (gl_VectorAddr == 0U)
    {
        funcres = VEX_NO_MEMORY;
    }
    else
    {
        // Format command token
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        Eip130Token_Command_Pk_NumLoad(&CommandToken,
                                       CommandToken_p->Index,
                                       gl_VectorAddr,
                                       CommandToken_p->InDataSize);

        gl_TokenID = vex_DeviceGetTokenID();

#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
        Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, true);
#else
        Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, false);
#endif

        // Initialize result token
        (void)memset(&ResultToken, 0, sizeof(ResultToken));

        // Exchange token with the EIP-130 HW
        funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_Asym_PkaNumLoad_Post
 */
VexStatus_t
vex_Asym_PkaNumLoad_Post(
        const VexTokenCmd_PkOperation_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);

    if (gl_VectorAddr != 0)
    {
        // Release used buffer
        (void)BufManager_Unmap(gl_VectorAddr, false, false, 0U);
    }

    gl_TokenID = 0;
    gl_VectorAddr = 0;

    return funcres;
}


/*----------------------------------------------------------------------------
 * vex_Asym_PkaOperation
 */
VexStatus_t
vex_Asym_PkaOperation(
        const VexTokenCmd_PkOperation_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    size_t InputSize = 0;
    size_t OutputSize = 0;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    gl_TokenID = vex_DeviceGetTokenID();

    // Get Vector input address for token
    if (CommandToken_p->InData_p != NULL)
    {
        InputSize = CommandToken_p->InDataSize;
        gl_InputAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                   BUFMANAGER_BUFFERTYPE_IN,
                                   CommandToken_p->InData_p,
                                   InputSize,
                                   NULL);
        if (gl_InputAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
    }

    if ((funcres == VEX_SUCCESS) &&
        (CommandToken_p->OutData_p != NULL))
    {
        gl_OutputAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                    BUFMANAGER_BUFFERTYPE_OUT,
                                    CommandToken_p->OutData_p,
                                    CommandToken_p->OutDataSize,
                                    (void *)&gl_TokenID);
        if (gl_OutputAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
        else
        {
            OutputSize = BufManager_GetSize(gl_OutputAddr);
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        // Format command token
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        Eip130Token_Command_Pk_Operation(&CommandToken,
                                         (uint8_t)CommandToken_p->Operation,
                                         CommandToken_p->PublicExponent,
                                         gl_InputAddr, (uint32_t)InputSize,
                                         gl_OutputAddr, (uint32_t)OutputSize);
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
        Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, true);
#else
        Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, false);
#endif

        // Initialize result token
        (void)memset(&ResultToken, 0, sizeof(ResultToken));

        // Exchange token with the EIP-130 HW
        funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_Asym_PkaOperation
 */
VexStatus_t
vex_Asym_PkaOperation_Post(
        const VexTokenCmd_PkOperation_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if (ResultToken_p->Result >= 0)
    {
        // Copy output data
        fCopy = true;
    }

    // Release used buffer(s)
    if (gl_InputAddr != 0U)
    {
        (void)BufManager_Unmap(gl_InputAddr, false, false, 0U);
    }
    if (gl_OutputAddr != 0U)
    {
        int32_t rc = BufManager_Unmap(gl_OutputAddr, true, fCopy, 0U);
        if (rc != 0)
        {
            if (rc == -3)
            {
                funcres = VEX_DATA_TIMEOUT;
            }
            else
            {
                funcres = VEX_DATA_MAPPING_ERROR;
            }
        }
    }

    gl_TokenID = 0;
    gl_InputAddr = 0;
    gl_OutputAddr = 0;

    return funcres;
}



/* end of file adapter_vex_asym_pka.c */
