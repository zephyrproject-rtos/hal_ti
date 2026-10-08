/* adapter_vex_trng.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the TRNG services.
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
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_random.h>

static uint64_t gl_InputDataAddr = 0;
static uint64_t gl_OutputDataAddr = 0;
static volatile uint16_t gl_TokenID;

/*----------------------------------------------------------------------------
 * vexLocal_TrngRandom
 */
static VexStatus_t
vexLocal_TrngRandom(
        const VexTokenCmd_Random_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p,
        uint16_t RawKey)
{
    VexStatus_t funcres;
    uint16_t Size;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    if ((RawKey != 0U) && ((CommandToken_p->Size % 256U) != 0U))
    {
        funcres = VEX_INVALID_LENGTH;
    }
    else
    {
        // Random output via DMA and setup DMA OutputAddress in token.
        gl_TokenID = vex_DeviceGetTokenID();

        if (RawKey == 0U)
        {
            Size = CommandToken_p->Size;

            gl_InputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                      BUFMANAGER_BUFFERTYPE_OUT,
                                      CommandToken_p->Data_p,
                                      CommandToken_p->Size,
                                      (void *)&gl_TokenID);
        }
        else
        {
            Size = ((uint16_t)CommandToken_p->Size / 256U);

            // Note: The TRNG Raw data dump does not respect the write TokenID
            //       after DMA data write
            gl_InputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                      BUFMANAGER_BUFFERTYPE_OUT,
                                      CommandToken_p->Data_p,
                                      CommandToken_p->Size,
                                      NULL/*(void *)&TokenID*/);
        }

        if (gl_InputDataAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
        else
        {
            // Format command token
            (void)memset(&CommandToken, 0, sizeof(CommandToken));
            Eip130Token_Command_RandomNumber_Generate(&CommandToken, Size, gl_InputDataAddr);
            if (RawKey != 0U)
            {
                Eip130Token_Command_RandomNumber_SetRawKey(&CommandToken, RawKey);
            }
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
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_TrngRandom_Post
 */
static VexStatus_t
vexLocal_TrngRandom_Post(
        const VexTokenCmd_Random_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;
    int32_t rc;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if (ResultToken_p->Result >= 0)
    {
        // Copy output data
        fCopy = true;
    }

    // Release used buffer, if needed
    if (gl_InputDataAddr != 0U)
    {
        rc = BufManager_Unmap(gl_InputDataAddr, true, fCopy, 0U);
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * vexLocal_TrngConfig
 */
static VexStatus_t
vexLocal_TrngConfig(
        const VexTokenCmd_TrngConfig_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    // Format command token
    (void)memset(&CommandToken, 0, sizeof(CommandToken));
#ifdef VEX_ENABLE_DRBG_FORCESEED
    if(CommandToken_p->fDRBGForceSeed)
    {
        Eip130Token_Command_DRBG_ForceSeed(&CommandToken,
                                            CommandToken_p->AutoSeed,
                                            CommandToken_p->Seed);
    }
    else
#endif
    if ((CommandToken_p->fReseed != 0U) &&
        (CommandToken_p->fLoadStart == 0U))
    {
        // Only reseed
        Eip130Token_Command_PRNG_ReseedNow(&CommandToken);
    }
    else
    {
        // Configure
        Eip130Token_Command_TRNG_Configure(
            &CommandToken,
            CommandToken_p->AutoSeed,
            CommandToken_p->SampleCycles,
            CommandToken_p->SampleDiv,
            CommandToken_p->Scale,
            CommandToken_p->NoiseBlocks,
            CommandToken_p->RepCntCutoff,
            CommandToken_p->AdaptProp64Cutoff,
            CommandToken_p->AdaptProp512Cutoff);

        if (CommandToken_p->fReseed != 0U)
        {
            // RRD = Reseed post-processor
            CommandToken.W[2] |= BIT_1;
        }
#ifdef VEX_ENABLE_ARIA_DRBG
        if(CommandToken_p->fAria != 0U)
        {
            Eip130Token_Command_TRNG_Configure_AriaDRBG(&CommandToken);
        }
#endif
    }

    gl_TokenID = vex_DeviceGetTokenID();

    Eip130Token_Command_SetTokenID(&CommandToken,
                                   gl_TokenID,
                                   false);

    // Initialize result token
    (void)memset(&ResultToken, 0, sizeof(ResultToken));

    // Exchange token with the EIP-130 HW
    funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_TrngConfig_Post
 */
static VexStatus_t
vexLocal_TrngConfig_Post(
        const VexTokenCmd_TrngConfig_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);

    return VEX_SUCCESS;
}


/*----------------------------------------------------------------------------
 * vexLocal_VerifyDrbg
 */
static VexStatus_t
vexLocal_VerifyDrbg(
        const VexTokenCmd_DrbgPP_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    if (CommandToken_p->InputData_p != NULL)
    {
        // Convert input buffer and get address for token
        gl_InputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                       BUFMANAGER_BUFFERTYPE_IN,
                                       CommandToken_p->InputData_p,
                                       CommandToken_p->InputDataSize,
                                       NULL);
        if (gl_InputDataAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        // Get output address for token
        // Note: The TRNG Post-Processing Verification does not respect the write
        //       TokenID after DMA data write
        gl_TokenID = vex_DeviceGetTokenID();
        gl_OutputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                        BUFMANAGER_BUFFERTYPE_OUT,
                                        CommandToken_p->OutputData_p,
                                        CommandToken_p->OutputDataSize,
                                        NULL/*(void *)&TokenID*/);
        if (gl_OutputDataAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
        else
        {
            // Format command token
            (void)memset(&CommandToken, 0, sizeof(CommandToken));
            Eip130Token_Command_TRNG_PP_Verification(&CommandToken,
                                                     CommandToken_p->Test,
                                                     CommandToken_p->Pattern,
                                                     CommandToken_p->Size,
                                                     gl_InputDataAddr,
                                                     gl_OutputDataAddr);
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
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_VerifyDrbg_Post
 */
static VexStatus_t
vexLocal_VerifyDrbg_Post(
        const VexTokenCmd_DrbgPP_t * const CommandToken_p,
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

    // Release used buffers, if needed
    if (gl_InputDataAddr != 0U)
    {
        (void)BufManager_Unmap(gl_InputDataAddr, false, false, 0U);
    }
    if (gl_OutputDataAddr != 0U)
    {
        int32_t rc = BufManager_Unmap(gl_OutputDataAddr, true, fCopy, 0U);
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

    return funcres;
}


/*----------------------------------------------------------------------------
 * vexLocal_VerifyNrbg
 */
static VexStatus_t
vexLocal_VerifyNrbg(
        const VexTokenCmd_NrbgVerify_t * const CommandToken_p,
        VexTokenRslt_NrbgVerify_t * const ResultToken_p)
{
    VexStatus_t funcres;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    // Convert input buffer and get address for token
    gl_InputDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                              BUFMANAGER_BUFFERTYPE_IN,
                              CommandToken_p->InputData_p,
                              CommandToken_p->Size,
                              NULL);
    if (gl_InputDataAddr == 0U)
    {
        funcres = VEX_NO_MEMORY;
    }
    else
    {
        // Format command token
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        Eip130Token_Command_TRNG_HW_SelfTest(&CommandToken,
                                             gl_InputDataAddr,
                                             CommandToken_p->Size,
                                             CommandToken_p->RepCntCutoff,
                                             CommandToken_p->RepCntCount,
                                             CommandToken_p->RepCntData,
                                             CommandToken_p->AdaptProp64Cutoff,
                                             CommandToken_p->AdaptProp64Count,
                                             CommandToken_p->AdaptProp64Data,
                                             CommandToken_p->AdaptProp512Cutoff,
                                             CommandToken_p->AdaptProp512Count,
                                             CommandToken_p->AdaptProp512Data);

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
 * vexLocal_VerifyNrbg_Post
 */
static VexStatus_t
vexLocal_VerifyNrbg_Post(
        const VexTokenCmd_NrbgVerify_t * const CommandToken_p,
        VexTokenRslt_NrbgVerify_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if (ResultToken_p->Result >= 0)
    {
        Eip130Token_Result_TRNG_HW_SelfTest(ResultTokenP_p,
                                            &ResultToken_p->RepCntCutoff,
                                            &ResultToken_p->RepCntCount,
                                            &ResultToken_p->RepCntData,
                                            &ResultToken_p->AdaptProp64Cutoff,
                                            &ResultToken_p->AdaptProp64Count,
                                            &ResultToken_p->AdaptProp64Data,
                                            &ResultToken_p->AdaptProp64Fail,
                                            &ResultToken_p->AdaptProp512Cutoff,
                                            &ResultToken_p->AdaptProp512Count,
                                            &ResultToken_p->AdaptProp512Data,
                                            &ResultToken_p->AdaptProp512Fail);
    }

    // Release used buffer, if needed
    if (gl_InputDataAddr != 0U)
    {
        (void)BufManager_Unmap(gl_InputDataAddr, false, false, 0U);
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * vex_Trng
 */
VexStatus_t
vex_Trng(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_UNSUPPORTED;

    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_RANDOMNUMBER:
        funcres = vexLocal_TrngRandom((VexTokenCmd_Random_t *)CommandToken_p,
                                      ResultToken_p, 0);
        break;

    case VEXTOKEN_SUBCODE_TRNGRAWDATA:
        funcres = vexLocal_TrngRandom((VexTokenCmd_Random_t *)CommandToken_p,
                                      ResultToken_p, 0x5244);
        break;

    case VEXTOKEN_SUBCODE_TRNGCONFIG:
        funcres = vexLocal_TrngConfig((VexTokenCmd_TrngConfig_t *)CommandToken_p,
                                      ResultToken_p);
        break;

    case VEXTOKEN_SUBCODE_VERIFYDRBG:
        funcres = vexLocal_VerifyDrbg((VexTokenCmd_DrbgPP_t *)CommandToken_p,
                                      ResultToken_p);
        break;

    case VEXTOKEN_SUBCODE_VERIFYNRBG:
        funcres = vexLocal_VerifyNrbg((VexTokenCmd_NrbgVerify_t *)CommandToken_p,
                                      (VexTokenRslt_NrbgVerify_t *)ResultToken_p);
        break;

    default:
        /* MISRA - Intentially empty */
        break;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_Trng
 */
VexStatus_t
vex_Trng_PostProcessing(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_UNSUPPORTED;

    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_RANDOMNUMBER:
        funcres = vexLocal_TrngRandom_Post((VexTokenCmd_Random_t *)CommandToken_p,
                                      ResultToken_p, ResultTokenP_p);
        break;

    case VEXTOKEN_SUBCODE_TRNGRAWDATA:
        funcres = vexLocal_TrngRandom_Post((VexTokenCmd_Random_t *)CommandToken_p,
                                      ResultToken_p, ResultTokenP_p);
        break;

    case VEXTOKEN_SUBCODE_TRNGCONFIG:
        funcres = vexLocal_TrngConfig_Post((VexTokenCmd_TrngConfig_t *)CommandToken_p,
                                      ResultToken_p, ResultTokenP_p);
        break;

    case VEXTOKEN_SUBCODE_VERIFYDRBG:
        funcres = vexLocal_VerifyDrbg_Post((VexTokenCmd_DrbgPP_t *)CommandToken_p,
                                      ResultToken_p,
                                      ResultTokenP_p);
        break;

    case VEXTOKEN_SUBCODE_VERIFYNRBG:
        funcres = vexLocal_VerifyNrbg_Post((VexTokenCmd_NrbgVerify_t *)CommandToken_p,
                                      (VexTokenRslt_NrbgVerify_t *)ResultToken_p,
                                      ResultTokenP_p);
        break;

    default:
        /* MISRA - Intentially empty */
        break;
    }

    gl_InputDataAddr = 0;
    gl_OutputDataAddr = 0;
    gl_TokenID = 0;

    return funcres;
}

/* end of file adapter_vex_trng.c */
