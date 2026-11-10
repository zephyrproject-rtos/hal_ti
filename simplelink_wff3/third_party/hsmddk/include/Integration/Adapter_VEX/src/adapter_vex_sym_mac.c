/* adapter_vex_sym_mac.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the symmetric crypto MAC services.
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
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_mac.h>


static uint64_t gl_DataAddr = 0;
static volatile uint16_t gl_TokenID;

/*----------------------------------------------------------------------------
 * vexLocal_SymMacUpdate
 */
static VexStatus_t
vexLocal_SymMacUpdate(
        const VexTokenCmd_Mac_t * const CommandToken_p,
        VexTokenRslt_Mac_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fInitWithDefault;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    // Convert input buffer and get address for token
    gl_DataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                              BUFMANAGER_BUFFERTYPE_IN,
                              CommandToken_p->Data_p,
                              CommandToken_p->DataSize,
                              NULL);
    if (gl_DataAddr == 0U)
    {
        funcres = VEX_NO_MEMORY;
    }
    else
    {
        switch (CommandToken_p->Mode)
        {
        default:
            /* MISRA - Intentially no break here */
        case VEXTOKEN_MODE_HASH_MAC_CONT2FINAL:
        case VEXTOKEN_MODE_HASH_MAC_INIT2FINAL:
            funcres = VEX_BAD_ARGUMENT;
            break;
        case VEXTOKEN_MODE_HASH_MAC_INIT2CONT:
            fInitWithDefault = true;
            break;
        case VEXTOKEN_MODE_HASH_MAC_CONT2CONT:
            fInitWithDefault = false;
            break;
        }

        if (funcres == VEX_SUCCESS)
        {
            // Format command token
            (void)memset(&CommandToken, 0, sizeof(CommandToken));
            Eip130Token_Command_Mac(&CommandToken,
                                    (uint8_t)CommandToken_p->Algorithm,
                                    fInitWithDefault,
                                    false,
                                    gl_DataAddr,
                                    CommandToken_p->DataSize);

            // Intermediate MAC value via the Asset Store
            Eip130Token_Command_Mac_SetASIDState(
                &CommandToken,
                CommandToken_p->TempAssetId);

            // Key from Asset Store
            Eip130Token_Command_Mac_SetASIDKey(
                &CommandToken,
                CommandToken_p->KeyAssetId);

            gl_TokenID = vex_DeviceGetTokenID();

            Eip130Token_Command_SetTokenID(&CommandToken,
                                           gl_TokenID, false);

            // Initialize result token
            (void)memset(&ResultToken, 0, sizeof(ResultToken));

            // Exchange token with the EIP-130 HW
            funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
        }
    }

   return funcres;
}


/*----------------------------------------------------------------------------
 * vexLocal_SymMacFinalHMAC
 */
static VexStatus_t
vexLocal_SymMacFinalHMAC(
        const VexTokenCmd_Mac_t * const CommandToken_p,
        VexTokenRslt_Mac_t * const ResultToken_p,
        const uint32_t MACSize)
{
    VexStatus_t funcres = VEX_SUCCESS;
    uint64_t DataAddr = 0;
    bool fInitWithDefault;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    switch (CommandToken_p->Mode)
    {
    case VEXTOKEN_MODE_HASH_MAC_INIT2FINAL:
        fInitWithDefault = true;
        break;

    case VEXTOKEN_MODE_HASH_MAC_CONT2FINAL:
        fInitWithDefault = false;
        break;

    case VEXTOKEN_MODE_HASH_MAC_CONT2CONT:
    case VEXTOKEN_MODE_HASH_MAC_INIT2CONT:
    default:
        funcres = VEX_BAD_ARGUMENT;
        break;
    }

    if (funcres == VEX_SUCCESS)
    {
        if (CommandToken_p->DataSize != 0U)
        {
            // Convert input buffer and get address for token
            DataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                      BUFMANAGER_BUFFERTYPE_IN,
                                      CommandToken_p->Data_p,
                                      CommandToken_p->DataSize,
                                      NULL);
            if (DataAddr == 0U)
            {
                funcres = VEX_NO_MEMORY;
            }
        }
        else if (!fInitWithDefault)
        {
            funcres = VEX_INVALID_LENGTH;
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        if (funcres == VEX_SUCCESS)
        {
            // Format command token
            (void)memset(&CommandToken, 0, sizeof(CommandToken));
            Eip130Token_Command_Mac(&CommandToken,
                                    (uint8_t)CommandToken_p->Algorithm,
                                    fInitWithDefault,
                                    true,
                                    DataAddr,
                                    CommandToken_p->DataSize);
            // Intermediate MAC value via the Asset Store
            Eip130Token_Command_Mac_SetASIDState(
                &CommandToken,
                CommandToken_p->TempAssetId);

            // Key from Asset Store
            Eip130Token_Command_Mac_SetASIDKey(
                &CommandToken,
                CommandToken_p->KeyAssetId);

            if (CommandToken_p->SubCode == (uint32_t)VEXTOKEN_SUBCODE_MACVERIFY)
            {
                // Copy the MAC value to verify into the token, or set the Asset Store
                // reference
                if (CommandToken_p->MacAssetId != 0U)
                {
                    Eip130Token_Command_Mac_SetASIDVerifyMAC(
                        &CommandToken,
                        CommandToken_p->MacAssetId);
                }
                else
                {
                    Eip130Token_Command_Mac_CopyVerifyMAC(
                        &CommandToken,
                        CommandToken_p->Mac,
                        CommandToken_p->MacSize);
                }
            }
            {
                uint64_t TotalMessageLength;
                TotalMessageLength = (uint64_t)(((uint64_t)CommandToken_p->TotalMessageLengthHi << 32) +
                                                 (uint64_t)CommandToken_p->TotalMessageLengthLo);
                Eip130Token_Command_Mac_SetTotalMessageLength(
                    &CommandToken,
                    TotalMessageLength);
            }

            gl_TokenID = vex_DeviceGetTokenID();

            Eip130Token_Command_SetTokenID(&CommandToken,
                                           gl_TokenID,
                                           false);

            // Initialize result token
            (void)memset(&ResultToken, 0, sizeof(ResultToken));

            // Exchange token with the EIP-130 HW
           funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
           if (funcres == VEX_SUCCESS)
           {
               ResultToken_p->Result = Eip130Token_Result_Code(&ResultToken);
               if ((ResultToken_p->Result >= 0) &&
                   (CommandToken_p->SubCode == (uint32_t)VEXTOKEN_SUBCODE_MACGENERATE))
               {
                    Eip130Token_Result_Mac_CopyFinalMAC(&ResultToken,
                                                        MACSize,
                                                        ResultToken_p->Mac);
                }
            }

            // Release used buffer, if needed
            (void)BufManager_Unmap(DataAddr, false, false, 0U);
        }
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_SymMacFinalCipherMAC
 */
static VexStatus_t
vexLocal_SymMacFinalCipherMAC(
        const VexTokenCmd_Mac_t * const CommandToken_p,
        VexTokenRslt_Mac_t * const ResultToken_p,
        const uint32_t BlockSize)
{
    VexStatus_t funcres = VEX_SUCCESS;
    int32_t npadbytes;
    uint32_t DataSize;
    uint8_t *Data_p;
    bool fInitWithDefault;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    switch (CommandToken_p->Mode)
    {
    case VEXTOKEN_MODE_HASH_MAC_INIT2FINAL:
        fInitWithDefault = true;
        break;
    case VEXTOKEN_MODE_HASH_MAC_CONT2FINAL:
        fInitWithDefault = false;
        break;
    case VEXTOKEN_MODE_HASH_MAC_CONT2CONT:
    case VEXTOKEN_MODE_HASH_MAC_INIT2CONT:
    default:
        funcres = VEX_BAD_ARGUMENT;
        break;
    }

    if (funcres == VEX_SUCCESS)
    {
        // Align data size, if needed
        DataSize = (CommandToken_p->DataSize + BlockSize - 1U) & ~(BlockSize - 1U);
        if (DataSize == 0U)
        {
            if (fInitWithDefault &&
                (CommandToken_p->Algorithm == (uint32_t)VEXTOKEN_ALGO_MAC_AES_CBC_MAC))
            {
                // Return immediately
                ResultToken_p->Result = (int32_t)EIP130TOKEN_RESULT_SUCCESS;
            }
            else
            {
                DataSize += BlockSize;
            }
        }

        // Allocate an input buffer and get address for token
        gl_DataAddr = BufManager_Alloc(vex_ConvertFromUint32ToBool(CommandToken_p->fFromUserSpace),
                                    BUFMANAGER_BUFFERTYPE_IN,
                                    DataSize,
                                    CommandToken_p->Data_p,
                                    CommandToken_p->DataSize,
                                    NULL);
        if (gl_DataAddr == 0U)
        {
            funcres = VEX_NO_MEMORY;
        }
        else
        {
            // Pad data if needed
            npadbytes = ((int32_t)DataSize - (int32_t)CommandToken_p->DataSize);
            if (npadbytes > 0)
            {
                // Get the host reference of the buffer
                Data_p = BufManager_GetHostAddress(gl_DataAddr);
                if (Data_p == NULL)
                {
                    funcres = VEX_NO_MEMORY;
                }
                else
                {
                    Data_p = &Data_p[CommandToken_p->DataSize];

                    (void)memset(Data_p, 0, (size_t)npadbytes);
                    if ((CommandToken_p->Algorithm == (uint32_t)VEXTOKEN_ALGO_MAC_AES_CMAC)
#ifdef VEX_ENABLE_SYM_ALGO_ARIA
                        || (CommandToken_p->Algorithm == (uint32_t)VEXTOKEN_ALGO_MAC_ARIA_CMAC)
#endif
                        )
                    {
                        *Data_p = 0x80;
                        Data_p++;
                        if (npadbytes == (int32_t)BlockSize)
                        {
                            npadbytes--;
                        }
                    }
                }
            }

            if (funcres == VEX_SUCCESS)
            {
                // Pass control on to device
                if (BufManager_PreDmaAddress(gl_DataAddr) < 0)
                {
                    funcres = VEX_NO_MEMORY;
                }
                else
                {
                    // Format command token
                    (void)memset(&CommandToken, 0, sizeof(CommandToken));
                    Eip130Token_Command_Mac(&CommandToken,
                                            (uint8_t)CommandToken_p->Algorithm,
                                            fInitWithDefault,
                                            true,
                                            gl_DataAddr, DataSize);
                    // Intermediate MAC value via the Asset Store
                    Eip130Token_Command_Mac_SetASIDState(
                        &CommandToken,
                        CommandToken_p->TempAssetId);

                    // Key from Asset Store
                    Eip130Token_Command_Mac_SetASIDKey(
                        &CommandToken,
                        CommandToken_p->KeyAssetId);

                    if (CommandToken_p->SubCode == (uint32_t)VEXTOKEN_SUBCODE_MACVERIFY)
                    {
                        // Copy the MAC value to verify into the token, or set the Asset Store
                        // reference
                        if (CommandToken_p->MacAssetId != 0U)
                        {
                            // MAC value to verify from Asset Store
                            Eip130Token_Command_Mac_SetASIDVerifyMAC(
                                &CommandToken,
                                CommandToken_p->MacAssetId);
                        }
                        else
                        {
                            // MAC value to verify via token
                            Eip130Token_Command_Mac_CopyVerifyMAC(
                                &CommandToken,
                                CommandToken_p->Mac,
                                CommandToken_p->MacSize);
                        }
                    }

                    Eip130Token_Command_Mac_SetTotalMessageLength(&CommandToken,
                                                                  (uint64_t)npadbytes);

                    gl_TokenID = vex_DeviceGetTokenID();

                    Eip130Token_Command_SetTokenID(&CommandToken,
                                                   gl_TokenID,
                                                   false);

                    // Initialize result token
                    (void)memset(&ResultToken, 0, sizeof(ResultToken));

                    // Exchange token with the EIP-130 HW
                    funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
                }
            }
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * vex_SymMac
 */
VexStatus_t
vex_SymMac(
        const VexTokenCmd_Mac_t * const CommandToken_p,
        VexTokenRslt_Mac_t * const ResultToken_p)
{
    VexStatus_t funcres;

    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_MACUPDATE:
        switch (CommandToken_p->Algorithm)
        {
        case VEXTOKEN_ALGO_MAC_HMAC_SHA1:
        case VEXTOKEN_ALGO_MAC_HMAC_SHA224:
        case VEXTOKEN_ALGO_MAC_HMAC_SHA256:
#ifdef VEX_ENABLE_SYM_ALGO_SHA512
        case VEXTOKEN_ALGO_MAC_HMAC_SHA384:
        case VEXTOKEN_ALGO_MAC_HMAC_SHA512:
#endif
#ifdef VEX_ENABLE_SYM_ALGO_SHA3
        case VEXTOKEN_ALGO_MAC_HMAC_SHA3_224:
        case VEXTOKEN_ALGO_MAC_HMAC_SHA3_256:
        case VEXTOKEN_ALGO_MAC_HMAC_SHA3_384:
        case VEXTOKEN_ALGO_MAC_HMAC_SHA3_512:
#endif
#ifdef VEX_ENABLE_SYM_ALGO_SM3
        case VEXTOKEN_ALGO_MAC_HMAC_SM3:
#endif
        case VEXTOKEN_ALGO_MAC_AES_CMAC:
        case VEXTOKEN_ALGO_MAC_AES_CBC_MAC:
#ifdef VEX_ENABLE_SYM_ALGO_ARIA
        case VEXTOKEN_ALGO_MAC_ARIA_CMAC:
        case VEXTOKEN_ALGO_MAC_ARIA_CBC_MAC:
#endif
#ifdef VEX_ENABLE_SYM_ALGO_POLY1305
        case VEXTOKEN_ALGO_MAC_POLY1305:
#endif
            funcres = vexLocal_SymMacUpdate(CommandToken_p, ResultToken_p);
            break;
        default:
            funcres = VEX_BAD_ARGUMENT;
            break;
        }
        break;

    case VEXTOKEN_SUBCODE_MACGENERATE:
    case VEXTOKEN_SUBCODE_MACVERIFY:
        switch (CommandToken_p->Algorithm)
        {
        case VEXTOKEN_ALGO_MAC_HMAC_SHA1:
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (160U / 8U));
            break;
        case VEXTOKEN_ALGO_MAC_HMAC_SHA224:
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (224U / 8U));
            break;
        case VEXTOKEN_ALGO_MAC_HMAC_SHA256:
#ifdef VEX_ENABLE_SYM_ALGO_SM3
        case VEXTOKEN_ALGO_MAC_HMAC_SM3:
#endif
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (256U / 8U));
            break;
#ifdef VEX_ENABLE_SYM_ALGO_SHA512
        case VEXTOKEN_ALGO_MAC_HMAC_SHA384:
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (384U / 8U));
            break;
        case VEXTOKEN_ALGO_MAC_HMAC_SHA512:
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (512U / 8U));
            break;
#endif
#ifdef VEX_ENABLE_SYM_ALGO_SHA3
        case VEXTOKEN_ALGO_MAC_HMAC_SHA3_224:
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (224U / 8U));
            break;
        case VEXTOKEN_ALGO_MAC_HMAC_SHA3_256:
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (256U / 8U));
            break;
        case VEXTOKEN_ALGO_MAC_HMAC_SHA3_384:
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (384U / 8U));
            break;
        case VEXTOKEN_ALGO_MAC_HMAC_SHA3_512:
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (512U / 8U));
            break;
#endif
        case VEXTOKEN_ALGO_MAC_AES_CMAC:
        case VEXTOKEN_ALGO_MAC_AES_CBC_MAC:
#ifdef VEX_ENABLE_SYM_ALGO_ARIA
        case VEXTOKEN_ALGO_MAC_ARIA_CMAC:
        case VEXTOKEN_ALGO_MAC_ARIA_CBC_MAC:
#endif
            funcres = vexLocal_SymMacFinalCipherMAC(CommandToken_p,
                                                    ResultToken_p,
                                                    (128U / 8U));
            break;
#ifdef VEX_ENABLE_SYM_ALGO_POLY1305
        case VEXTOKEN_ALGO_MAC_POLY1305:
            // For token processing it can be regarded as an HMAC
            funcres = vexLocal_SymMacFinalHMAC(CommandToken_p,
                                               ResultToken_p,
                                               (128U / 8U));
            break;
#endif
        default:
            funcres = VEX_BAD_ARGUMENT;
            break;
        }
        break;

    default:
        funcres = VEX_INVALID_SUBCODE;
        break;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_SymMacUpdate_Post
 */
static VexStatus_t
vexLocal_SymMacUpdate_Post(const VexTokenCmd_Mac_t * const CommandToken_p,
                                 VexTokenRslt_Mac_t * const ResultToken_p,
                                 const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if (CommandToken_p->TempAssetId == 0U)
    {
        Eip130Token_Result_Mac_CopyFinalMAC(
            ResultTokenP_p,
            sizeof(ResultToken_p->Mac),
            ResultToken_p->Mac);
    }

    // Release used buffer, if needed
    if(gl_DataAddr != 0)
    {
        (void)BufManager_Unmap(gl_DataAddr, false, false, 0U);
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_SymMacFinalCipherMAC_Post
 */
static VexStatus_t
vexLocal_SymMacFinalCipherMAC_Post(const VexTokenCmd_Mac_t * const CommandToken_p,
                                 VexTokenRslt_Mac_t * const ResultToken_p,
                                 const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if ((ResultToken_p->Result >= 0) &&
        (CommandToken_p->SubCode == (uint32_t)VEXTOKEN_SUBCODE_MACGENERATE))
    {
        Eip130Token_Result_Mac_CopyFinalMAC(ResultTokenP_p,
                                            (128U / 8U),
                                            ResultToken_p->Mac);
    }

    // Release used buffer, if needed
    if(gl_DataAddr != 0)
    {
        (void)BufManager_Unmap(gl_DataAddr, false, false, 0U);
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_SymMac_PostProcessing
 */
VexStatus_t
vex_SymMac_PostProcessing(const VexTokenCmd_Mac_t * const CommandToken_p,
                          VexTokenRslt_Mac_t * const ResultToken_p,
                          const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres;

    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_MACUPDATE:
        switch (CommandToken_p->Algorithm)
        {
        case VEXTOKEN_ALGO_MAC_AES_CMAC:
        case VEXTOKEN_ALGO_MAC_AES_CBC_MAC:
            funcres = vexLocal_SymMacUpdate_Post(CommandToken_p, ResultToken_p, ResultTokenP_p);
            break;
        default:
            funcres = VEX_BAD_ARGUMENT;
            break;
        }
        break;

    case VEXTOKEN_SUBCODE_MACGENERATE:
    case VEXTOKEN_SUBCODE_MACVERIFY:
        switch (CommandToken_p->Algorithm)
        {
        case VEXTOKEN_ALGO_MAC_AES_CMAC:
        case VEXTOKEN_ALGO_MAC_AES_CBC_MAC:
            funcres = vexLocal_SymMacFinalCipherMAC_Post(CommandToken_p, ResultToken_p, ResultTokenP_p);
            break;
        default:
            funcres = VEX_BAD_ARGUMENT;
            break;
        }
        break;

    default:
        funcres = VEX_INVALID_SUBCODE;
        break;
    }

    gl_DataAddr = 0;
    gl_TokenID = 0;

    return funcres;
}


/* end of file adapter_vex_sym_mac.c */
