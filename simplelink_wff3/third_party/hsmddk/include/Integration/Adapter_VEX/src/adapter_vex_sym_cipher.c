/* adapter_vex_sym_cipher.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the symmetric crypto cipher services.
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
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_crypto.h>


static uint64_t gl_AADAddr = 0;
static uint64_t gl_SrcDataAddr = 0;
static uint64_t gl_DstDataAddr = 0;
static volatile uint16_t gl_TokenID;

static VexStatus_t
vexLocal_SymCipherX_MapDataAddresses(
        const uint8_t * SrcData_p,
        uint64_t * SrcDataAddr,
        uint32_t SrcDataLength,
        uint8_t * DstData_p,
        uint64_t * DstDataAddr,
        uint32_t * DstDataLength,
        uint16_t * TokenID,
        uint32_t HostDataSize,
        const uint32_t fFromUserSpace)
{
    VexStatus_t Status = VEX_SUCCESS;
    if (SrcDataLength > 0U)
    {
        // for when padding is required, we need to allocate more memory
        if (SrcDataLength > HostDataSize)
        {
            *SrcDataAddr = BufManager_Alloc(vex_ConvertFromUint32ToBool(fFromUserSpace),
                                            BUFMANAGER_BUFFERTYPE_IN,
                                            SrcDataLength,
                                            SrcData_p,
                                            HostDataSize,
                                            NULL);
        }
        else
        {
            *SrcDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(fFromUserSpace),
                                          BUFMANAGER_BUFFERTYPE_IN,
                                          SrcData_p,
                                          SrcDataLength,
                                          NULL);
        }

        if (*SrcDataAddr > 0U)
        {
            // Pass control to device
            if (BufManager_PreDmaAddress(*SrcDataAddr) < 0)
            {
                Status = VEX_DATA_MAPPING_ERROR;
            }
        }
        else
        {
            Status = VEX_DATA_MAPPING_ERROR;
        }

        if (DstData_p != NULL)
        {
            // Get output address for token
            *DstDataAddr = BufManager_Map(vex_ConvertFromUint32ToBool(fFromUserSpace),
                                          BUFMANAGER_BUFFERTYPE_OUT,
                                          DstData_p,
                                          SrcDataLength,
                                          (void *)TokenID);
            if (*DstDataAddr == 0U)
            {
                Status = VEX_DATA_MAPPING_ERROR;
            }
            *DstDataLength = (uint32_t)BufManager_GetSize(*DstDataAddr);
        }
    }
    return Status;
}

static VexStatus_t
vexLocal_SymCipherAE_MapAADAddress(
        const uint8_t * AAD_p,
        uint32_t AADSize,
        uint64_t * AADAddr,
        const uint32_t AADLength,
        const uint32_t fFromUserSpace)
{
    VexStatus_t Status = VEX_SUCCESS;

    // Convert AAD buffer and get addresses for token
    if ((AADLength > 0U) && (AAD_p != NULL))
    {
        if ((AADLength - AADSize) == 0U)
        {
            *AADAddr = BufManager_Map(vex_ConvertFromUint32ToBool(fFromUserSpace),
                                      BUFMANAGER_BUFFERTYPE_IN,
                                      AAD_p, AADLength, NULL);
            if (*AADAddr == 0U)
            {
                Status = VEX_DATA_MAPPING_ERROR;
            }
        }
        else
        {
            // Allocate a buffer for the AAD and pad it with zeros
           *AADAddr = BufManager_Alloc(vex_ConvertFromUint32ToBool(fFromUserSpace),
                                       BUFMANAGER_BUFFERTYPE_IN,
                                       AADLength, AAD_p, AADSize, NULL);
            if (*AADAddr > 0U)
            {
                // determine required amount of padding
                const uint32_t PaddingSize = AADLength - AADSize;

                // *AADLength -= AADSize;

                if (AADLength > 0U)
                {
                    uint8_t* Data_p = BufManager_GetHostAddress(*AADAddr);
                    if (Data_p == NULL)
                    {
                        Status = VEX_DATA_MAPPING_ERROR;
                    }
                    else
                    {
                        // pad data with zeroes
                        Data_p = &Data_p[AADSize];
                        (void)memset(Data_p, 0, PaddingSize);
                    }
                }

                if (Status == VEX_SUCCESS)
                {
                    // Pass control on to device
                    if (BufManager_PreDmaAddress(*AADAddr) < 0)
                    {
                        Status = VEX_DATA_MAPPING_ERROR;
                    }
                }
            }
            else
            {
                Status = VEX_DATA_MAPPING_ERROR;
            }
        }
    }

    return Status;
}

/*----------------------------------------------------------------------------
 * vex_SymCipher
 */
VexStatus_t
vex_SymCipher(
        const VexTokenCmd_Cipher_t * const CommandToken_p,
        VexTokenRslt_Cipher_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    uint32_t SrcDataLength;
    uint32_t DstDataLength = 0;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    SrcDataLength = CommandToken_p->DataSize;
    switch (CommandToken_p->Algorithm)
    {
#ifdef VEX_ENABLE_SYM_ALGO_ARIA
    case VEXTOKEN_ALGO_CIPHER_ARIA:
#endif
    case VEXTOKEN_ALGO_CIPHER_AES:
        if (SrcDataLength == 0U)
        {
            funcres = VEX_INVALID_LENGTH;
        }
        else if ((CommandToken_p->Mode == VEXTOKEN_MODE_CIPHER_CTR) ||
                 (CommandToken_p->Mode == VEXTOKEN_MODE_CIPHER_ICM) ||
                 (CommandToken_p->Mode == VEXTOKEN_MODE_CIPHER_XTS))
        {
            /* Make sure that the data is block size aligned because
             * the data can be padded with zeros automatically.
             */
            SrcDataLength +=  ((128U / 8U) - 1U);
            SrcDataLength &= ~((uint32_t)(128U / 8U) - 1U);
        }
        else if ((SrcDataLength & ((128U / 8U) - 1U)) != 0U)
        {
            funcres = VEX_INVALID_LENGTH;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        break;

#if defined(VEX_ENABLE_SYM_ALGO_DES) || defined(VEX_ENABLE_SYM_ALGO_3DES)
#ifdef VEX_ENABLE_SYM_ALGO_DES
    case VEXTOKEN_ALGO_CIPHER_DES:
#endif
#ifdef VEX_ENABLE_SYM_ALGO_3DES
    case VEXTOKEN_ALGO_CIPHER_3DES:
#endif
        if (SrcDataLength == 0U)
        {
            funcres = VEX_INVALID_LENGTH;
        }
        else if (CommandToken_p->Mode == VEXTOKEN_MODE_CIPHER_CTR)
        {
            /* Make sure that the data is block size aligned because
             * the data can be padded with zeros automatically.
             */
            SrcDataLength +=  ((64U / 8U) - 1U);
            SrcDataLength &= ~((uint32_t)(64U / 8U) - 1U);
        }
        else if ((SrcDataLength & ((64U / 8U) - 1U)) != 0U)
        {
            funcres = VEX_INVALID_LENGTH;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        break;
#endif

#ifdef VEX_ENABLE_SYM_ALGO_CHACHA20
    case VEXTOKEN_ALGO_CIPHER_CHACHA20:
        if ((SrcDataLength & ((512U/8U) - 1U)) != 0U)
        {
            funcres = VEX_INVALID_LENGTH;
        }
        else if (SrcDataLength == 0U)
        {
            if (CommandToken_p->SrcData_p == NULL)
            {
                /* The output buffer size is assumed at least 32-byte. */
                SrcDataLength = (256U / 8U);
            }
            else
            {
                funcres = VEX_BAD_ARGUMENT;
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        break;
#endif

#ifdef VEX_ENABLE_SYM_ALGO_SM4
    case VEXTOKEN_ALGO_CIPHER_SM4:
        if (SrcDataLength == 0U)
        {
            funcres = VEX_INVALID_LENGTH;
        }
        else if (CommandToken_p->Mode == VEXTOKEN_MODE_CIPHER_CTR)
        {
            /* Make sure that the data is block size aligned because
             * the data can be padded with zeros automatically.
             */
            SrcDataLength +=  ((128U / 8U) - 1U);
            SrcDataLength &= ~((uint32_t)(128U / 8U) - 1U);
        }
        else if ((SrcDataLength & ((128U / 8U) - 1U)) != 0U)
        {
            funcres = VEX_INVALID_LENGTH;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        break;
#endif

    default:
        /* MISRA - Intentially empty */
        funcres = VEX_UNSUPPORTED;
        break;
    }

    if (funcres == VEX_SUCCESS)
    {
        // Get output address for token
        gl_TokenID = vex_DeviceGetTokenID();
        funcres = vexLocal_SymCipherX_MapDataAddresses(
                      CommandToken_p->SrcData_p, &gl_SrcDataAddr, SrcDataLength,
                      CommandToken_p->DstData_p, &gl_DstDataAddr, &DstDataLength,
                      (uint16_t*)&gl_TokenID, CommandToken_p->DataSize,
                      CommandToken_p->fFromUserSpace);
        if (funcres != VEX_SUCCESS)
        {
            funcres = VEX_NO_MEMORY;
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        // Format command token
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        switch (CommandToken_p->Algorithm)
        {
        case VEXTOKEN_ALGO_CIPHER_AES:
            Eip130Token_Command_Crypto_Operation(
                &CommandToken,
                (uint8_t)EIP130TOKEN_CRYPTO_ALGO_AES,
                (uint8_t)CommandToken_p->Mode,
                vex_ConvertFromUint32ToBool((uint32_t)CommandToken_p->fEncrypt),
                SrcDataLength);
            if (CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_XTS)
            {
                Eip130Token_Command_Crypto_SetKeyLength(
                    &CommandToken,
                    CommandToken_p->KeySize/2U);
            }
            else
            {
                Eip130Token_Command_Crypto_SetKeyLength(
                    &CommandToken,
                    CommandToken_p->KeySize);

#ifdef VEX_ENABLE_SYM_ALGO_AES_F8
                if (CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_F8)
                {
                    // f8 IV
                    Eip130Token_Command_Crypto_Copyf8IV(
                        &CommandToken,
                        CommandToken_p->f8_IV);

                    // f8 SaltKey
                    Eip130Token_Command_Crypto_Copyf8SaltKey(
                        &CommandToken,
                        CommandToken_p->f8_SaltKey,
                        (uint32_t)CommandToken_p->f8_SaltKeySize);
                }
#endif
            }
            break;

#ifdef VEX_ENABLE_SYM_ALGO_DES
        case VEXTOKEN_ALGO_CIPHER_DES:
            Eip130Token_Command_Crypto_Operation(
                &CommandToken,
                (uint8_t)EIP130TOKEN_CRYPTO_ALGO_DES,
                (uint8_t)CommandToken_p->Mode,
                vex_ConvertFromUint32ToBool((uint32_t)CommandToken_p->fEncrypt),
                SrcDataLength);
            break;
#endif

#ifdef VEX_ENABLE_SYM_ALGO_3DES
        case VEXTOKEN_ALGO_CIPHER_3DES:
            Eip130Token_Command_Crypto_Operation(
                &CommandToken,
                (uint8_t)EIP130TOKEN_CRYPTO_ALGO_3DES,
                (uint8_t)CommandToken_p->Mode,
                vex_ConvertFromUint32ToBool((uint32_t)CommandToken_p->fEncrypt),
                SrcDataLength);
            break;
#endif

#ifdef VEX_ENABLE_SYM_ALGO_CHACHA20
        case VEXTOKEN_ALGO_CIPHER_CHACHA20:
            Eip130Token_Command_Crypto_Operation(
                &CommandToken,
                (uint8_t)EIP130TOKEN_CRYPTO_ALGO_CHACHA20,
                (uint8_t)CommandToken_p->Mode,
                vex_ConvertFromUint32ToBool((uint32_t)CommandToken_p->fEncrypt),
                CommandToken_p->DataSize);
            Eip130Token_Command_Crypto_ChaCha20_SetKeyLength(
                &CommandToken,
                CommandToken_p->KeySize);
            Eip130Token_Command_Crypto_SetNonceLength(
                &CommandToken,
                CommandToken_p->NonceLength);
            break;
#endif

#ifdef VEX_ENABLE_SYM_ALGO_SM4
        case VEXTOKEN_ALGO_CIPHER_SM4:
            Eip130Token_Command_Crypto_Operation(
                &CommandToken,
                (uint8_t)EIP130TOKEN_CRYPTO_ALGO_SM4,
                (uint8_t)CommandToken_p->Mode,
                vex_ConvertFromUint32ToBool((uint32_t)CommandToken_p->fEncrypt),
                SrcDataLength);
            break;
#endif

#ifdef VEX_ENABLE_SYM_ALGO_ARIA
        case VEXTOKEN_ALGO_CIPHER_ARIA:
            Eip130Token_Command_Crypto_Operation(
                &CommandToken,
                (uint8_t)EIP130TOKEN_CRYPTO_ALGO_ARIA,
                (uint8_t)CommandToken_p->Mode,
                vex_ConvertFromUint32ToBool((uint32_t)CommandToken_p->fEncrypt),
                SrcDataLength);
            if (CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_XTS)
            {
                Eip130Token_Command_Crypto_SetKeyLength(
                    &CommandToken,
                    CommandToken_p->KeySize/2U);
            }
            else
            {
                Eip130Token_Command_Crypto_SetKeyLength(
                    &CommandToken,
                    CommandToken_p->KeySize);

#ifdef VEX_ENABLE_SYM_ALGO_ARIA_F8
                if (CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_F8)
                {
                    // f8 IV
                    Eip130Token_Command_Crypto_Copyf8IV(
                        &CommandToken,
                        CommandToken_p->f8_IV);

                    // f8 SaltKey
                    Eip130Token_Command_Crypto_Copyf8SaltKey(
                        &CommandToken,
                        CommandToken_p->f8_SaltKey,
                        (uint32_t)CommandToken_p->f8_SaltKeySize);
                }
 #endif
            }
            break;
#endif

        default:
            funcres = VEX_UNSUPPORTED;
            break;
        }
    }

    if (funcres == VEX_SUCCESS)
    {
        // Key
        if (CommandToken_p->KeyAssetId != 0U)
        {
            // From Asset Store
            Eip130Token_Command_Crypto_SetASLoadKey(
                &CommandToken,
                CommandToken_p->KeyAssetId);
        }
        else
        {
            // From token
            Eip130Token_Command_Crypto_CopyKey(
                &CommandToken,
                CommandToken_p->Key,
                CommandToken_p->KeySize);
        }

        // IV
        if ((CommandToken_p->Mode != (uint32_t)VEXTOKEN_MODE_CIPHER_ECB)
#ifdef VEX_ENABLE_SYM_ALGO_CHACHA20
            || (CommandToken_p->Algorithm == (uint32_t)VEXTOKEN_ALGO_CIPHER_CHACHA20)
#endif
           )
        {
            if (CommandToken_p->TempAssetId != 0U)
            {
                // From Asset Store
                Eip130Token_Command_Crypto_SetASLoadIV(
                    &CommandToken,
                    CommandToken_p->TempAssetId);
                Eip130Token_Command_Crypto_SetASSaveIV(
                    &CommandToken,
                    CommandToken_p->TempAssetId);
            }
            else
            {
                // From token
                Eip130Token_Command_Crypto_CopyIV(
                    &CommandToken,
                    CommandToken_p->IV);
            }
        }

        Eip130Token_Command_Crypto_SetDataAddresses(
            &CommandToken,
            gl_SrcDataAddr, SrcDataLength,
            gl_DstDataAddr, DstDataLength);
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
 * vex_SymCipher_PostProcessing
 */
VexStatus_t
vex_SymCipher_PostProcessing(
        const VexTokenCmd_Cipher_t * const CommandToken_p,
        VexTokenRslt_Cipher_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = true;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if (ResultToken_p->Result >= 0)
    {
        // Copy output data
        fCopy = true;

        if (CommandToken_p->TempAssetId == 0U)
        {
            if ((CommandToken_p->Mode != (uint32_t)VEXTOKEN_MODE_CIPHER_ECB)
#ifdef VEX_ENABLE_SYM_ALGO_CHACHA20
            || (CommandToken_p->Algorithm == (uint32_t)VEXTOKEN_ALGO_CIPHER_CHACHA20)
#endif
                )
            {
                // From token
                Eip130Token_Result_Crypto_CopyIV(ResultTokenP_p,
                                                 ResultToken_p->IV);
            }
        }
    }

    // Release used buffers, if needed
    if (gl_SrcDataAddr != 0U)
    {
        (void)BufManager_Unmap(gl_SrcDataAddr, false, false, 0U);
    }
    if (gl_DstDataAddr != 0U)
    {
        if (BufManager_Unmap(gl_DstDataAddr, true, fCopy,
                             CommandToken_p->DataSize) != 0)
        {
            funcres = VEX_DATA_MAPPING_ERROR;
        }
    }

    gl_SrcDataAddr = 0;
    gl_DstDataAddr = 0;

    return funcres;
}


static VexStatus_t
vexLocal_SymCipherAE_Update(
        const VexTokenCmd_CipherAE_t * const CommandToken_p,
        VexTokenRslt_CipherAE_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    uint32_t AADLength = 0U;
    uint32_t SrcDataLength = 0U;
    uint32_t DstDataLength = 0U;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    AADLength = CommandToken_p->AADSize;
    SrcDataLength = CommandToken_p->DataSize;

    switch (CommandToken_p->Algorithm)
    {
#ifdef VEX_ENABLE_SYM_ALGO_ARIA
    case VEXTOKEN_ALGO_CIPHER_ARIA:
#endif
#ifdef VEX_ENABLE_SYM_ALGO_SM4
    case VEXTOKEN_ALGO_CIPHER_SM4:
#endif
    case VEXTOKEN_ALGO_CIPHER_AES:
        AADLength +=  ((128U / 8U) - 1U);
        AADLength &= (uint32_t)(~((128U / 8U) - 1U));
        break;

#ifdef VEX_ENABLE_SYM_ALGO_CHACHA20
    case VEXTOKEN_ALGO_CIPHER_CHACHA20:
        AADLength +=  ((512U / 8U) - 1U);
        AADLength &= (uint32_t)~((512U / 8U) - 1U);
        break;
#endif

    default:
        funcres = VEX_UNSUPPORTED;
        break;
    }
    if ((SrcDataLength == 0U) &&
        (AADLength != CommandToken_p->AADSize))
    {
        /* Only final AAD can have a misaligned size, in all other cases AAD
         * must have a block aligned size */
        funcres = VEX_UNSUPPORTED;
    }

    if (funcres == VEX_SUCCESS)
    {
        gl_TokenID = vex_DeviceGetTokenID();
        funcres = vexLocal_SymCipherX_MapDataAddresses(
                      CommandToken_p->SrcData_p, &gl_SrcDataAddr, SrcDataLength,
                      CommandToken_p->DstData_p, &gl_DstDataAddr, &DstDataLength,
                      (uint16_t*)&gl_TokenID, CommandToken_p->DataSize,
                      CommandToken_p->fFromUserSpace);
    }
    if (funcres == VEX_SUCCESS)
    {
        funcres = vexLocal_SymCipherAE_MapAADAddress(
                      CommandToken_p->AAD_p, CommandToken_p->AADSize,
                      &gl_AADAddr, AADLength, CommandToken_p->fFromUserSpace);
    }
    if (funcres == VEX_SUCCESS)
    {
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        Eip130Token_Command_Crypto_Operation(
            &CommandToken,
            (uint8_t)CommandToken_p->Algorithm,
            (uint8_t)CommandToken_p->Mode,
            vex_ConvertFromUint32ToBool((uint32_t)CommandToken_p->fEncrypt),
            CommandToken_p->TotalDataLength);

        Eip130Token_Command_Crypto_SetADPartLen(&CommandToken, AADLength);

        Eip130Token_Command_Crypto_SetADAddress(
            &CommandToken,
            gl_AADAddr, (uint16_t)CommandToken_p->TotalAADLength);

        Eip130Token_Command_Crypto_SetDataAddresses(
            &CommandToken,
            gl_SrcDataAddr, SrcDataLength,
            gl_DstDataAddr, DstDataLength);

#if defined(VEX_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(VEX_ENABLE_SYM_ALGO_ARIA_GCM) || \
    defined(VEX_ENABLE_SYM_ALGO_SM4_GCM)
        if (CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_GCM)
        {
            if (CommandToken_p->fEncrypt != 0U)
            {
                if (CommandToken_p->fNoRandomIV != 0U)
                {
                    // Nonce and counter (IV) provided
                    Eip130Token_Command_Crypto_SetNoRandomIV(&CommandToken);

                    // Copy the IV for the encryption operation
                    Eip130Token_Command_Crypto_CopyIV(&CommandToken,
                                                      CommandToken_p->IV);
                }
            }
            else
            {
                // Copy IV for a decrypt operation
                Eip130Token_Command_Crypto_CopyIV(&CommandToken,
                                                  CommandToken_p->IV);
            }
        }
#endif

#if defined(VEX_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(VEX_ENABLE_SYM_ALGO_ARIA_CCM)
        if (CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_CCM)
        {
            Eip130Token_Command_Crypto_CopyNonce(
            &CommandToken,
            CommandToken_p->NonceHashKey,
            (uint32_t)CommandToken_p->NonceHashKeySize);
        }
#endif

        // any part except the last must have AS_SaveIV=1
        Eip130Token_Command_Crypto_SetASSaveIV(
            &CommandToken,
            CommandToken_p->TempAssetId);

        // any part except the first must have AS_Load_IV=1
        if ((CommandToken_p->OpMode != VEXTOKEN_MODE_CIPHER_AE_INIT2CONT) &&
            (CommandToken_p->OpMode != VEXTOKEN_MODE_CIPHER_AE_AAD_INIT2CONT))
        {
            Eip130Token_Command_Crypto_SetASLoadIV(&CommandToken,
                                                   CommandToken_p->TempAssetId);
        }

        Eip130Token_Command_Crypto_CopyTag(&CommandToken,
                                           CommandToken_p->Tag,
                                           CommandToken_p->TagSize);

        Eip130Token_Command_Crypto_SetKeyLength(&CommandToken,
                                                CommandToken_p->KeySize);
        // copy key
        if (CommandToken_p->KeyAssetId != 0U)
        {
            // From Asset Store
            Eip130Token_Command_Crypto_SetASLoadKey(&CommandToken,
                                                    CommandToken_p->KeyAssetId);
        }
        else
        {
            // From token
            Eip130Token_Command_Crypto_CopyKey(&CommandToken,
                                               CommandToken_p->Key,
                                               CommandToken_p->KeySize);
        }

#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
        Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, true);
#else
        Eip130Token_Command_SetTokenID(&CommandToken, gl_TokenID, false);
#endif

        // Initialize result token
        (void)memset(&ResultToken, 0, sizeof(ResultToken));
        funcres = vex_PhysicalTokenExchange(&CommandToken, &ResultToken);
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_SymCipherAE_Final
 */
static VexStatus_t
vexLocal_SymCipherAE_Final(
        const VexTokenCmd_CipherAE_t * const CommandToken_p,
        VexTokenRslt_CipherAE_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    uint8_t Algorithm;
    uint32_t AADLength;
    uint32_t SrcDataLength;
    uint32_t DstDataLength = 0;
    uint32_t ActualSrcDataLength;
    Eip130Token_Command_t CommandToken;
    Eip130Token_Result_t ResultToken;

    // Align data sizes, if needed
    AADLength = CommandToken_p->AADSize;
    SrcDataLength = CommandToken_p->DataSize;
    ActualSrcDataLength = SrcDataLength;
    switch (CommandToken_p->Algorithm)
    {
    case VEXTOKEN_ALGO_CIPHER_AES:
        Algorithm = (uint8_t)EIP130TOKEN_CRYPTO_ALGO_AES;
        AADLength +=  ((128U / 8U) - 1U);
        AADLength &= (uint32_t)(~((128U / 8U) - 1U));
        SrcDataLength +=  ((128U / 8U) - 1U);
        SrcDataLength &= (uint32_t)(~((128U / 8U) - 1U));
        if (CommandToken_p->TempAssetId != 0U)
        {
            ActualSrcDataLength = CommandToken_p->TotalDataLength;
        }
        break;

#ifdef VEX_ENABLE_SYM_ALGO_ARIA
    case VEXTOKEN_ALGO_CIPHER_ARIA:
        Algorithm = (uint8_t)EIP130TOKEN_CRYPTO_ALGO_ARIA;
        AADLength +=  ((128U / 8U) - 1U);
        AADLength &= (uint32_t)~((128U / 8U) - 1U);
        SrcDataLength +=  ((128U / 8U) - 1U);
        SrcDataLength &= (uint32_t)~((128U / 8U) - 1U);
        break;
#endif

#ifdef VEX_ENABLE_SYM_ALGO_SM4
    case VEXTOKEN_ALGO_CIPHER_SM4:
        Algorithm = (uint8_t)EIP130TOKEN_CRYPTO_ALGO_SM4;
        AADLength +=  ((128U / 8U) - 1U);
        AADLength &= (uint32_t)~((128U / 8U) - 1U);
        SrcDataLength +=  ((128U / 8U) - 1U);
        SrcDataLength &= (uint32_t)~((128U / 8U) - 1U);
        break;
#endif

#ifdef VEX_ENABLE_SYM_ALGO_CHACHA20
    case VEXTOKEN_ALGO_CIPHER_CHACHA20:
        Algorithm = (uint8_t)EIP130TOKEN_CRYPTO_ALGO_CHACHA20;
        AADLength +=  ((512U / 8U) - 1U);
        AADLength &= (uint32_t)~((512U / 8U) - 1U);
        SrcDataLength +=  ((512U / 8U) - 1U);
        SrcDataLength = (uint32_t)(SrcDataLength & (~((512U / 8U) - 1U)));
        break;
#endif

    default:
        funcres = VEX_UNSUPPORTED;
        break;
    }

    if (funcres == VEX_SUCCESS)
    {
        gl_TokenID = vex_DeviceGetTokenID();
        funcres = vexLocal_SymCipherX_MapDataAddresses(
                      CommandToken_p->SrcData_p, &gl_SrcDataAddr, SrcDataLength,
                      CommandToken_p->DstData_p, &gl_DstDataAddr, &DstDataLength,
                      (uint16_t*)&gl_TokenID, CommandToken_p->DataSize, CommandToken_p->fFromUserSpace);
    }
    if (funcres == VEX_SUCCESS)
    {
        funcres = vexLocal_SymCipherAE_MapAADAddress(
                      CommandToken_p->AAD_p, CommandToken_p->AADSize,
                      &gl_AADAddr, AADLength,
                      CommandToken_p->fFromUserSpace);
    }
    if (funcres == VEX_SUCCESS)
    {
        // Format command token
        (void)memset(&CommandToken, 0, sizeof(CommandToken));
        Eip130Token_Command_Crypto_Operation(
            &CommandToken,
            Algorithm,
            (uint8_t)CommandToken_p->Mode,
            vex_ConvertFromUint32ToBool((uint32_t)CommandToken_p->fEncrypt),
            ActualSrcDataLength);

        // Key
        switch (CommandToken_p->Algorithm)
        {
        default:
        case VEXTOKEN_ALGO_CIPHER_AES:
#ifdef VEX_ENABLE_SYM_ALGO_ARIA
        case VEXTOKEN_ALGO_CIPHER_ARIA:
#endif
#ifdef VEX_ENABLE_SYM_ALGO_SM4
        case VEXTOKEN_ALGO_CIPHER_SM4:
#endif
            Eip130Token_Command_Crypto_SetKeyLength(
                &CommandToken,
                CommandToken_p->KeySize);
            break;

#ifdef VEX_ENABLE_SYM_ALGO_CHACHA20
        case VEXTOKEN_ALGO_CIPHER_CHACHA20:
            Eip130Token_Command_Crypto_ChaCha20_SetKeyLength(
                &CommandToken,
                CommandToken_p->KeySize);
            break;
#endif
        }
        if (CommandToken_p->KeyAssetId != 0U)
        {
            // From Asset Store
            Eip130Token_Command_Crypto_SetASLoadKey(&CommandToken,
                                                    CommandToken_p->KeyAssetId);
        }
        else
        {
            // From token
            Eip130Token_Command_Crypto_CopyKey(&CommandToken,
                                               CommandToken_p->Key,
                                               CommandToken_p->KeySize);
        }

#if defined(VEX_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(VEX_ENABLE_SYM_ALGO_ARIA_GCM) || \
    defined(VEX_ENABLE_SYM_ALGO_SM4_GCM)
        if (CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_GCM)
        {
            if (CommandToken_p->fEncrypt != 0U)
            {
                if ((CommandToken_p->fNoRandomIV != 0U))
                {
                    // Nonce and counter (IV) provided
                    Eip130Token_Command_Crypto_SetNoRandomIV(&CommandToken);

                    // Copy the IV for the encryption operation
                    Eip130Token_Command_Crypto_CopyIV(&CommandToken,
                                                      CommandToken_p->IV);
                }
            }
            else
            {
                // Copy IV for a decrypt operation
                Eip130Token_Command_Crypto_CopyIV(&CommandToken,
                                                  CommandToken_p->IV);
            }
        }
        else
#endif
        {
            // Nonce
            Eip130Token_Command_Crypto_CopyNonce(
                &CommandToken,
                CommandToken_p->NonceHashKey,
                (uint32_t)CommandToken_p->NonceHashKeySize);
        }

#if defined(VEX_ENABLE_SYM_ALGO_AES_GCM) || \
    defined(VEX_ENABLE_SYM_ALGO_ARIA_CCM)
        // continuation-final, previous set IV will be ignored, as state asset is used instead
        if (CommandToken_p->TempAssetId != 0U)
        {
            Eip130Token_Command_Crypto_SetASLoadIV(
                &CommandToken,
                CommandToken_p->TempAssetId);
            // AAD length must be the total AAD size in case of continuation
            AADLength = CommandToken_p->TotalAADLength;
            Eip130Token_Command_Crypto_SetADPartLen(&CommandToken, CommandToken_p->AADSize);
        }
        else
        {
            AADLength =  CommandToken_p->AADSize;
        }
#else
        AADLength = CommandToken_p->AADSize;
#endif

        // Set data addresses
        Eip130Token_Command_Crypto_SetADAddress(
            &CommandToken,
            gl_AADAddr, AADLength);
        Eip130Token_Command_Crypto_SetDataAddresses(
            &CommandToken,
            gl_SrcDataAddr, SrcDataLength,
            gl_DstDataAddr, DstDataLength);
        Eip130Token_Command_Crypto_CopyTag(
            &CommandToken,
            CommandToken_p->Tag,
            CommandToken_p->TagSize);
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
 * vex_SymCipherAE
 */
VexStatus_t
vex_SymCipherAE(
        const VexTokenCmd_CipherAE_t * const CommandToken_p,
        VexTokenRslt_CipherAE_t * const ResultToken_p)
{
    VexStatus_t funcres;

    switch (CommandToken_p->OpMode)
    {
    case VEXTOKEN_MODE_CIPHER_AE_INIT2FINAL:
    case VEXTOKEN_MODE_CIPHER_AE_CONT2FINAL:
        funcres = vexLocal_SymCipherAE_Final(CommandToken_p, ResultToken_p);
        break;

    case VEXTOKEN_MODE_CIPHER_AE_INIT2CONT:
    case VEXTOKEN_MODE_CIPHER_AE_CONT2CONT:
    case VEXTOKEN_MODE_CIPHER_AE_AAD_FINAL2INIT_DATA:
    case VEXTOKEN_MODE_CIPHER_AE_AAD_INIT2CONT:
        funcres = vexLocal_SymCipherAE_Update(CommandToken_p, ResultToken_p);
        break;

    default:
        funcres = VEX_INTERNAL_ERROR;
        break;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_SymCipherAE_Final_Post
 */
static VexStatus_t
vexLocal_SymCipherAE_Final_Post(const VexTokenCmd_CipherAE_t * const CommandToken_p,
                           VexTokenRslt_CipherAE_t * const ResultToken_p,
                           const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if (ResultToken_p->Result >= 0)
    {
        // Copy output data from physical result token to the logical one.
        fCopy = true;
        if (CommandToken_p->fEncrypt != 0U)
        {
            Eip130Token_Result_Crypto_CopyTag(ResultTokenP_p,
                                                ResultToken_p->Tag);
            if ((CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_GCM) &&
                (CommandToken_p->fNoRandomIV == 0U))
            {
                Eip130Token_Result_Crypto_CopyIV(ResultTokenP_p,
                                                    ResultToken_p->IV);
            }
        }
    }

    // Release used buffers, if needed
    if (gl_AADAddr != 0U)
    {
        (void)BufManager_Unmap(gl_AADAddr, false, false, 0U);
    }
    if (gl_SrcDataAddr != 0U)
    {
        (void)BufManager_Unmap(gl_SrcDataAddr, false, false, 0U);
    }
    if (gl_DstDataAddr != 0U)
    {
        if (BufManager_Unmap(gl_DstDataAddr, true, fCopy,
                             CommandToken_p->DataSize) != 0)
        {
            funcres = VEX_DATA_MAPPING_ERROR;
        }
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vexLocal_SymCipherAE_Update_Post
 */
static VexStatus_t
vexLocal_SymCipherAE_Update_Post(const VexTokenCmd_CipherAE_t * const CommandToken_p,
                           VexTokenRslt_CipherAE_t * const ResultToken_p,
                           const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_SUCCESS;
    bool fCopy = false;

    ResultToken_p->Result = Eip130Token_Result_Code(ResultTokenP_p);
    if (ResultToken_p->Result >= 0)
    {
        // Copy output data from physical result token to the logical one.
        fCopy = true;
        if (CommandToken_p->fEncrypt != 0U)
        {
            // When doing AES-GCM with "random-IV-generation", the IV is output on the first part,
            // and only on the first part.
            if ((CommandToken_p->Mode == (uint32_t)VEXTOKEN_MODE_CIPHER_GCM) &&
                (CommandToken_p->fNoRandomIV == 0U) &&
                ((CommandToken_p->OpMode == (uint32_t)VEXTOKEN_MODE_CIPHER_AE_INIT2CONT) ||
                (CommandToken_p->OpMode == (uint32_t)VEXTOKEN_MODE_CIPHER_AE_AAD_INIT2CONT)))
            {
                Eip130Token_Result_Crypto_CopyIV(ResultTokenP_p,
                                                    ResultToken_p->IV);
            }
        }
    }

    // Release used buffers, if needed
    if (gl_AADAddr != 0U)
    {
        (void)BufManager_Unmap(gl_AADAddr, false, false, 0U);
    }
    if (gl_SrcDataAddr != 0U)
    {
        (void)BufManager_Unmap(gl_SrcDataAddr, false, false, 0U);
    }
    if (gl_DstDataAddr != 0U)
    {
        if (BufManager_Unmap(gl_DstDataAddr, true, fCopy,
                             CommandToken_p->DataSize) != 0)
        {
            funcres = VEX_DATA_MAPPING_ERROR;
        }
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_SymCipherAE_PostProcessing
 */
VexStatus_t
vex_SymCipherAE_PostProcessing(const VexTokenCmd_CipherAE_t * const CommandToken_p,
                               VexTokenRslt_CipherAE_t * const ResultToken_p,
                               const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres;

    switch (CommandToken_p->OpMode)
    {
    case VEXTOKEN_MODE_CIPHER_AE_INIT2FINAL:
    case VEXTOKEN_MODE_CIPHER_AE_CONT2FINAL:
        funcres = vexLocal_SymCipherAE_Final_Post(CommandToken_p, ResultToken_p, ResultTokenP_p);
        break;

    case VEXTOKEN_MODE_CIPHER_AE_INIT2CONT:
    case VEXTOKEN_MODE_CIPHER_AE_CONT2CONT:
    case VEXTOKEN_MODE_CIPHER_AE_AAD_FINAL2INIT_DATA:
    case VEXTOKEN_MODE_CIPHER_AE_AAD_INIT2CONT:
        funcres = vexLocal_SymCipherAE_Update_Post(CommandToken_p, ResultToken_p, ResultTokenP_p);
        break;

    default:
        funcres = VEX_INTERNAL_ERROR;
        break;
    }

    gl_AADAddr = 0;
    gl_SrcDataAddr = 0;
    gl_DstDataAddr = 0;
    gl_TokenID = 0;

    return funcres;
}

/* end of file adapter_vex_sym_cipher.c */
