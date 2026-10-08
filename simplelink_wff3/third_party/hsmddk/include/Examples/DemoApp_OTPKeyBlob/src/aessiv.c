/* aessiv.c
 *
 * AES-SIV implementation using the VAL API.
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */
#include "aessiv.h"                     // typedefs

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include "api_val.h"                    // val_*
#define LOG_SEVERITY_MAX  LOG_SEVERITY_CRIT
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>                        // Log_HexDump


static void
AESSIV_Xor(uint8_t * buffer,
           const uint8_t * XorValue)
{
    int32_t i;

    for (i = 0; i < (128/8); i++)
    {
        buffer[i] ^= XorValue[i];
    }
}


static void
AESSIV_BitShiftLeft(uint8_t * buffer)
{
    int32_t i;

    for (i = 0; i < ((128/8) - 1); i++)
    {
        buffer[i] = (uint8_t)((uint8_t)(buffer[i] << 1) | ((uint8_t)(buffer[i + 1] >> 7U) & 1U));
    }
    buffer[((128/8) -1)] = (uint8_t)(buffer[((128/8) -1)] << 1);
}


// It is the multiplication of S and 0...010 in the finite field
// represented using the primitive polynomial x^128 + x^7 + x^2 + x + 1.
static void
AESSIV_Dbl(uint8_t * buffer)
{
    const uint8_t AESSIV_XorBlock[(128/8)] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
    };
    bool XorNeeded = ((buffer[0] & ((uint8_t)0x80)) != 0U);

    AESSIV_BitShiftLeft(buffer);
    if (XorNeeded)
    {
        AESSIV_Xor(buffer, AESSIV_XorBlock);
    }
}


static int32_t
AESSIV_S2V(const AESSIV_Context * Context_p,
           const uint8_t * Data_p,
           const size_t DataSize,
           uint8_t * Mac_p)
{
    const uint8_t zero_block[(128/8)] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    int32_t funcres = 0;
    size_t DataBufSize = 0;
    ValSize_t MacSize = (128/8);
    ValStatus_t Status;
    ValPolicyMask_t MACKeyAssetPolicy = EIP130_ASSET_POLICY_SYM_MACCIPHER |
                                        EIP130_ASSET_POLICY_SCACAES |
                                        EIP130_ASSET_POLICY_SCDIRENCGEN;
    ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;
    uint32_t i;
    ValSymContextBuffer SymContext;

    if (Context_p->Verbose)
    {
        Log_HexDump("CMAC Key", 0, Context_p->Key, (uint32_t)(Context_p->KeySize / 2U));
    }

    Status = val_SymInitContext(VAL_SYM_ALGO_MAC_AES_CMAC, VAL_SYM_MODE_NONE, false,
                                (ValSymContextPtr_t)&SymContext, sizeof(SymContext));
    if (Status < VAL_SUCCESS)
    {
        LOG_CRIT("S2V FAILED: Context initialization\n");
        funcres = -1;
    }
    else
    {
        ValSymContextPtr_t SymContext_p = (ValSymContextPtr_t)&SymContext;

        /* Create key asset */
        Status = val_AssetAlloc(MACKeyAssetPolicy, (ValSize_t)(Context_p->KeySize / 2U),
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &KeyAssetId);
        if (Status < VAL_SUCCESS)
        {
            LOG_CRIT("S2V FAILED: Asset creation\n");
            funcres = -1;
        }
        else
        {
            Status = val_AssetLoadPlaintext(KeyAssetId, Context_p->Key,
                                            (ValSize_t)(Context_p->KeySize / 2U));
            if (Status < VAL_SUCCESS)
            {
                LOG_CRIT("S2V FAILED: Asset Loaded\n");
                funcres = -1;
            }
            else
            {
                Status = val_SymInitKey(SymContext_p, KeyAssetId,
                                        Context_p->Key, (ValSize_t)(Context_p->KeySize / 2U));
                if (Status < VAL_SUCCESS)
                {
                    LOG_CRIT("S2V FAILED: Key initialization\n");
                    funcres = -1;
                }
                else
                {
                    Status = val_SymMacGenerate(SymContext_p,
                                                zero_block, sizeof(zero_block),
                                                Mac_p, &MacSize);
                    if (Status < VAL_SUCCESS)
                    {
                        LOG_CRIT("S2V FAILED: MAC generation\n");
                        funcres = -1;
                    }
                }
            }

            (void)val_AssetFree(KeyAssetId);
        }

        (void)val_SymRelease((ValSymContextPtr_t)&SymContext);
    }

    if (funcres == 0)
    {
        if (Context_p->Verbose)
        {
            Log_HexDump("MAC(0)", 0, Mac_p, (uint32_t)MacSize);
        }

        for (i = 0; i < Context_p->AD_ListCount; i++)
        {
            uint8_t LocalMac[(128/8)];
            ValSize_t ADsize = 0;

            if (Context_p->Verbose)
            {
                Log_HexDump("MAC(..)", 0, Mac_p, (uint32_t)MacSize);
            }
            AESSIV_Dbl(Mac_p);
            if (Context_p->Verbose)
            {
                Log_HexDump("MACdbl(..)", 0, Mac_p, (uint32_t)MacSize);
            }

            Status = val_SymInitContext(VAL_SYM_ALGO_MAC_AES_CMAC, VAL_SYM_MODE_NONE, false,
                                        (ValSymContextPtr_t)&SymContext, sizeof(SymContext));
            if (Status < VAL_SUCCESS)
            {
                LOG_CRIT("S2V FAILED: Context initialization\n");
                funcres = -1;
            }
            else
            {
                ValSymContextPtr_t SymContext_p = (ValSymContextPtr_t)&SymContext;

                Status = val_AssetAlloc(MACKeyAssetPolicy, (ValSize_t)(Context_p->KeySize / 2U),
                                        VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                        &KeyAssetId);
                if (Status < VAL_SUCCESS)
                {
                    LOG_CRIT("S2V FAILED: Asset creation\n");
                    funcres = -1;
                }
                else
                {
                    Status = val_AssetLoadPlaintext(KeyAssetId, Context_p->Key,
                                                    (ValSize_t)(Context_p->KeySize / 2U));
                    if (Status < VAL_SUCCESS)
                    {
                        LOG_CRIT("S2V FAILED: Asset Loaded\n");
                        funcres = -1;
                    }
                    else
                    {
                        Status = val_SymInitKey(SymContext_p, KeyAssetId,
                                                Context_p->Key, (ValSize_t)(Context_p->KeySize/2U));
                        if (Status < VAL_SUCCESS)
                        {
                            LOG_CRIT("S2V FAILED: Key initialization\n");
                            funcres = -1;
                        }
                        else
                        {
                            ADsize = (ValSize_t)(Context_p->AD_List[i+1U] - Context_p->AD_List[i]);
                            MacSize = (128/8);
                            Status = val_SymMacGenerate(SymContext_p,
                                                        Context_p->AD_List[i], ADsize,
                                                        LocalMac, &MacSize);
                            if (Status < VAL_SUCCESS)
                            {
                                LOG_CRIT("S2V FAILED: MAC generation\n");
                                funcres = -1;
                            }
                            else
                            {
                                AESSIV_Xor(Mac_p, LocalMac);
                                if (Context_p->Verbose)
                                {
                                    Log_HexDump("MACxor(..)", 0, Mac_p, (uint32_t)MacSize);
                                }
                            }
                        }
                    }

                    (void)val_AssetFree(KeyAssetId);
                }

                (void)val_SymRelease((ValSymContextPtr_t)&SymContext);
            }

            if (funcres < 0)
            {
                break;
            }
        }
    }

    if (funcres == 0)
    {
        uint8_t DataBuf[(128U / 8U) + (2U * 1024U)];

        if (DataSize >= (128U / 8U))
        {
            DataBufSize = DataSize;
        }
        else
        {
            DataBufSize = (128U / 8U);
        }

        if (DataSize <= sizeof(DataBuf))
        {
            if (DataSize >= (128U / 8U))
            {
                (void)memcpy(DataBuf, Data_p, DataSize);
                AESSIV_Xor(&DataBuf[DataBufSize - 16U], Mac_p);
            }
            else
            {
                AESSIV_Dbl(Mac_p);
                (void)memcpy(DataBuf, Data_p, DataSize);
                DataBuf[DataSize] = 0x80; // Pad
                for (i = (uint32_t)(DataSize + 1U); i < (128U / 8U); i++)
                {
                    DataBuf[i] = 0x00;
                }
                AESSIV_Xor(DataBuf, Mac_p);
            }

            if (Context_p->Verbose)
            {
                Log_HexDump("CMAC Data", 0, DataBuf, (uint32_t)DataBufSize);
            }

            Status = val_SymInitContext(VAL_SYM_ALGO_MAC_AES_CMAC, VAL_SYM_MODE_NONE, false,
                                        (ValSymContextPtr_t)&SymContext, sizeof(SymContext));
            if (Status < VAL_SUCCESS)
            {
                LOG_CRIT("S2V FAILED: Context initialization\n");
                funcres = -1;
            }
            else
            {
                ValSymContextPtr_t SymContext_p = (ValSymContextPtr_t)&SymContext;

                Status = val_AssetAlloc(MACKeyAssetPolicy, (ValSize_t)(Context_p->KeySize / 2U),
                                        VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                        &KeyAssetId);
                if (Status < VAL_SUCCESS)
                {
                    LOG_CRIT("S2V FAILED: Asset creation\n");
                    funcres = -1;
                }
                else
                {
                    Status = val_AssetLoadPlaintext(KeyAssetId, Context_p->Key,
                                                    (ValSize_t)(Context_p->KeySize / 2U));
                    if (Status < VAL_SUCCESS)
                    {
                        LOG_CRIT("S2V FAILED: Asset Loaded\n");
                        funcres = -1;
                    }
                    else
                    {
                        Status = val_SymInitKey(SymContext_p, KeyAssetId,
                                                Context_p->Key, (ValSize_t)(Context_p->KeySize/2U));
                        if (Status < VAL_SUCCESS)
                        {
                            LOG_CRIT("S2V FAILED: Key initialization\n");
                            funcres = -1;
                        }
                        else
                        {
                            MacSize = (128/8);
                            Status = val_SymMacGenerate(SymContext_p,
                                                        DataBuf, DataBufSize,
                                                        Mac_p, &MacSize);
                            if (Status < VAL_SUCCESS)
                            {
                                LOG_CRIT("S2V FAILED: MAC generation\n");
                                funcres = -1;
                            }
                            else
                            {
                                if (Context_p->Verbose)
                                {
                                    Log_HexDump("V", 0, Mac_p, (uint32_t)MacSize);
                                }
                            }
                        }
                    }

                    (void)val_AssetFree(KeyAssetId);
                }

                (void)val_SymRelease((ValSymContextPtr_t)&SymContext);
            }
        }
    }

    return funcres;
}


static int32_t
AESSIV_AESCTR(const AESSIV_Context * Context_p,
              bool fEncrypt,
              const uint8_t * IV_p,
              const uint8_t * InData_p,
              const size_t InDataSize,
              uint8_t * OutData_p,
              size_t OutDataSize)
{
    int32_t funcres = 0;
    ValStatus_t Status;
    size_t OutSize = OutDataSize;
    uint8_t tmpIV[(128/8)];
    ValSymContextBuffer SymContext;

    Status = val_SymInitContext(VAL_SYM_ALGO_CIPHER_AES, VAL_SYM_MODE_CIPHER_CTR, false,
                                (ValSymContextPtr_t)&SymContext, sizeof(SymContext));
    if (Status < VAL_SUCCESS)
    {
        LOG_CRIT("CTR FAILED: Context initialization\n");
        funcres = -1;
    }
    else
    {
        ValSymContextPtr_t SymContext_p = (ValSymContextPtr_t)&SymContext;

        if (fEncrypt)
        {
            Status =  val_SymCipherInitEncrypt(SymContext_p);
            if (Status < VAL_SUCCESS)
            {
                LOG_CRIT("CTR FAILED: Encrypt set\n");
                funcres = -1;
            }
        }

        if (funcres == 0)
        {
            if (Context_p->Verbose)
            {
                Log_HexDump("CTR Key", 0,
                            &Context_p->Key[Context_p->KeySize / 2U],
                            (uint32_t)(Context_p->KeySize / 2U));
            }
            Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID,
                                    &Context_p->Key[Context_p->KeySize / 2U],
                                    (ValSize_t)(Context_p->KeySize / 2U));
            if (Status < VAL_SUCCESS)
            {
                LOG_CRIT("CTR FAILED: Key initialization\n");
                funcres = -1;
            }
            else
            {
                (void)memcpy(tmpIV, IV_p, sizeof(tmpIV));
                tmpIV[8] = (uint8_t)(tmpIV[8] & ((uint8_t)0x7F));
                tmpIV[12] = (uint8_t)(tmpIV[12] & ((uint8_t)0x7F));
                if (Context_p->Verbose)
                {
                    Log_HexDump("CTR IV", 0, tmpIV, (uint32_t)sizeof(tmpIV));
                }
                Status = val_SymInitIV(SymContext_p, tmpIV, sizeof(tmpIV));
                if (Status < VAL_SUCCESS)
                {
                    LOG_CRIT("CTR FAILED: IV initialization\n");
                    funcres = -1;
                }
                else
                {
                    const size_t InSize = (InDataSize + ((128U / 8U) - 1U)) & (~(size_t)((128U / 8U) - 1U));
                    if (InSize == InDataSize)
                    {
                        if (Context_p->Verbose)
                        {
                            Log_HexDump("CTR DataIn(1)", 0, InData_p, (uint32_t)InSize);
                        }
                        Status = val_SymCipherFinal(SymContext_p,
                                                    InData_p, InSize,
                                                    OutData_p, &OutSize);
                        if (Status < VAL_SUCCESS)
                        {
                            LOG_CRIT("CTR FAILED: Cipher operation\n");
                            funcres = -1;
                        }
                    }
                    else
                    {
                        uint8_t InDataBuf[2U * 1024U];
                        uint8_t OutDataBuf[2U * 1024U];

                        if (InSize > sizeof(InDataBuf))
                        {
                            LOG_CRIT("CTR FAILED: Data is too big for a key blob\n");
                            funcres = -1;
                        }
                        else
                        {
                            (void)memcpy(InDataBuf, InData_p, InDataSize);
                            if ((sizeof(InDataBuf) - InDataSize) > 0UL)
                            {
                                (void)memset(&InDataBuf[InDataSize], 0, (sizeof(InDataBuf) - InDataSize));
                            }
                            (void)memset(OutDataBuf, 0, sizeof(OutDataBuf));

                            if (Context_p->Verbose)
                            {
                                Log_HexDump("CTR DataIn(2)", 0, InDataBuf, (uint32_t)InSize);
                            }

                            OutSize = InSize;
                            Status = val_SymCipherFinal(SymContext_p,
                                                        InDataBuf, InSize,
                                                        OutDataBuf, &OutSize);
                            if (Status < VAL_SUCCESS)
                            {
                                LOG_CRIT("CTR FAILED: Cipher operation\n");
                                funcres = -1;
                            }
                            else
                            {
                                (void)memcpy(OutData_p, OutDataBuf, InDataSize);
                            }
                        }
                    }

                    if ((funcres >= 0) && (Context_p->Verbose))
                    {
                        Log_HexDump("CTR DataOut", 0, OutData_p, (uint32_t)OutSize);
                    }
                }
            }
        }

        (void)val_SymRelease((ValSymContextPtr_t)&SymContext);
    }

    return funcres;
}


int32_t
AESSIV_Init(AESSIV_Context * Context_p,
            const bool Verbose)
{
    (void)memset(Context_p, 0, sizeof(AESSIV_Context));
    Context_p->Verbose = Verbose;
    return 0;
}


int32_t
AESSIV_SetKey(AESSIV_Context * Context_p,
              const uint8_t * Key_p,
              const size_t KeySize)
{
    int32_t rc = 0;

    if (KeySize > sizeof(Context_p->Key))
    {
        rc = -1;
    }
    else
    {
        (void)memcpy(Context_p->Key, Key_p, KeySize);
        Context_p->KeySize = KeySize;
        if (Context_p->Verbose)
        {
            Log_HexDump("Set Key", 0, Context_p->Key, (uint32_t)Context_p->KeySize);
        }
    }
    return rc;
}


int32_t
AESSIV_SetAD(AESSIV_Context * Context_p,
             const uint8_t * AD_p,
             const size_t ADSize)
{
    int32_t funcres = 0;
    uint8_t * Begin_p = NULL;

    if (Context_p->AD_ListCount == 0U)
    {
        if (ADSize > sizeof(Context_p->AD_Buffer))
        {
            funcres = -1;
        }
        else
        {
            Begin_p = Context_p->AD_Buffer;
            Context_p->AD_List[Context_p->AD_ListCount] = Begin_p;
        }
    }
    else
    {
        if (Context_p->AD_ListCount == ((sizeof(Context_p->AD_List) / sizeof(Context_p->AD_List[0])) - 1UL))
        {
            funcres = -1;
        }
        else
        {
            Begin_p = Context_p->AD_List[Context_p->AD_ListCount];
            if (ADSize > (size_t)(sizeof(Context_p->AD_Buffer) - (size_t)(Begin_p - Context_p->AD_Buffer)))
            {
                funcres = -1;
            }
        }
    }

    if (funcres == 0)
    {
        (void)memcpy(Begin_p, AD_p, ADSize);
        if (Context_p->Verbose)
        {
            Log_HexDump("Set AD", 0, Context_p->AD_List[Context_p->AD_ListCount], (uint32_t)ADSize);
        }
        Context_p->AD_ListCount++;
        Context_p->AD_List[Context_p->AD_ListCount] = &Begin_p[ADSize];
    }

    return funcres;
}


int32_t
AESSIV_Encrypt(AESSIV_Context * Context_p,
               const uint8_t * InData_p,
               const size_t InDataSize,
               uint8_t * OutData_p,
               size_t * OutDataSize_p)
{
    int32_t funcres = 0;
    uint8_t V[(128/8)];

    if ((InDataSize + (128U/8U)) > *OutDataSize_p)
    {
        funcres = -1;
    }
    else
    {
        if (AESSIV_S2V(Context_p, InData_p, InDataSize, V) < 0)
        {
            funcres = -1;
        }
        else
        {
            if (AESSIV_AESCTR(Context_p, true, V,
                              InData_p, InDataSize,
                              &OutData_p[(128U / 8U)], (*OutDataSize_p - (128U / 8U))) < 0)
            {
                funcres = -1;
            }
            else
            {
                (void)memcpy(OutData_p, V, (128U/8U));
                *OutDataSize_p = InDataSize + (128U/8U);

                if (Context_p->Verbose)
                {
                    Log_HexDump("KeyBlob Data", 0, OutData_p, (uint32_t)(*OutDataSize_p));
                }
            }
        }
    }

    return funcres;
}

/* end of file aessiv.c */
