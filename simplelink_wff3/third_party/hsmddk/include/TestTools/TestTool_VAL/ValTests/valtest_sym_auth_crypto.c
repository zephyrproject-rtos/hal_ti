/* valtest_sym_auth_crypto.c
 *
 * Description: Authenticated crypto tests
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

#include "valtest_internal.h"

/* Test vectors. */
#ifdef VALTEST_SYM_ALGO_AES_CCM
#include "testvectors_aes_ccm.h"
#ifndef VALTEST_SYM_CONT_MAXCHUNK_SIZE
#define VALTEST_SYM_CONT_MAXCHUNK_SIZE 16U
#endif
#endif
#ifdef VALTEST_SYM_ALGO_AES_GCM
#include "testvectors_aes_gcm.h"
/* Chunk size for symmetric crypto continuation tests */
#ifndef VALTEST_SYM_CONT_MAXCHUNK_SIZE
#define VALTEST_SYM_CONT_MAXCHUNK_SIZE 16U
#endif
#endif
#ifdef VALTEST_SYM_ALGO_ARIA_CCM
#include "testvectors_aria_ccm.h"
#endif
#ifdef VALTEST_SYM_ALGO_ARIA_GCM
#include "testvectors_aria_gcm.h"
#endif
#ifdef VALTEST_SYM_ALGO_SM4_GCM
#include "testvectors_sm4_gcm.h"
#endif
#if (defined(VALTEST_SYM_ALGO_CHACHA20) && defined(VALTEST_SYM_ALGO_POLY1305))
#include "testvectors_chacha20_poly1305_aead.h"
#endif

#if defined(VALTEST_SYM_ALGO_AES_CCM) || \
    defined(VALTEST_SYM_ALGO_AES_GCM) || \
    (defined(VALTEST_SYM_ALGO_CHACHA20) && defined(VALTEST_SYM_ALGO_POLY1305)) || \
    defined(VALTEST_SYM_ALGO_ARIA_CCM) || \
    defined(VALTEST_SYM_ALGO_ARIA_GCM) || \
    defined(VALTEST_SYM_ALGO_SM4_GCM)
/*----------------------------------------------------------------------------
 * SetupTestContextAndEnvironment
 *
 * Setup for the "do_SymAuthCryptTest" test.
 */
static int
SetupTestContextAndEnvironment(
        const ValSymAlgo_t Algorithm,
        const ValSymMode_t Mode,
        const uint8_t * KeyData_p,
        const uint32_t KeyDataLen,
        bool fKeyAsset,
        bool fDecrypt,
        ValSymContextPtr_t * SymContext_pp,
        ValAssetId_t * KeyAssetId_p)
{
    ValStatus_t Status;

    switch (Mode)
    {
#if defined(VALTEST_SYM_ALGO_AES_CCM) || defined(VALTEST_SYM_ALGO_ARIA_CCM)
    case VAL_SYM_MODE_CIPHER_CCM:
#endif
#if defined(VALTEST_SYM_ALGO_AES_GCM) || defined(VALTEST_SYM_ALGO_ARIA_GCM) || defined(VALTEST_SYM_ALGO_SM4_GCM)
    case VAL_SYM_MODE_CIPHER_GCM:
#endif
#if defined(VALTEST_SYM_ALGO_CHACHA20) && defined(VALTEST_SYM_ALGO_POLY1305)
    case VAL_SYM_MODE_CIPHER_CHACHA20_AEAD:
#endif
        Status = val_SymAlloc(Algorithm, Mode, false, SymContext_pp);
        break;

    default:
        Status = VAL_INVALID_ALGORITHM;
        break;
    }
    unsupported_if((Status == VAL_INVALID_ALGORITHM), "");
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    if (fKeyAsset)
    {
        uint8_t * Key_p;
        ValPolicyMask_t KeyAssetPolicy = EIP130_ASSET_POLICY_SYM_CIPHERAUTH;
        if (fDecrypt)
        {
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
        }
        else
        {
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
        }
        switch (Mode)
        {
#if defined(VALTEST_SYM_ALGO_AES_CCM) || defined(VALTEST_SYM_ALGO_ARIA_CCM)
        case VAL_SYM_MODE_CIPHER_CCM:
            if (Algorithm == VAL_SYM_ALGO_CIPHER_ARIA)
            {
                KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACARIA | EIP130_ASSET_POLICY_SCMCACCM;
            }
            else
            {
                KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACAES | EIP130_ASSET_POLICY_SCMCACCM;
            }
            break;
#endif
#if defined(VALTEST_SYM_ALGO_AES_GCM) || defined(VALTEST_SYM_ALGO_ARIA_GCM) || defined(VALTEST_SYM_ALGO_SM4_GCM)
        case VAL_SYM_MODE_CIPHER_GCM:
            if (Algorithm == VAL_SYM_ALGO_CIPHER_ARIA)
            {
                KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACARIA | EIP130_ASSET_POLICY_SCMCAGCM;
            }
            else
            {
                KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACAES | EIP130_ASSET_POLICY_SCMCAGCM;
            }
            break;
#endif
#if defined(VALTEST_SYM_ALGO_CHACHA20) && defined(VALTEST_SYM_ALGO_POLY1305)
        case VAL_SYM_MODE_CIPHER_CHACHA20_AEAD:
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACCHACHA20 | EIP130_ASSET_POLICY_SCMCACCM;
            break;
#endif
        default:
            /* Safeguard: Should never happen due to earlier test. */
            break;
        }
        if (!val_IsAccessSecure())
        {
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(KeyAssetPolicy, KeyDataLen,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                KeyAssetId_p);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

#ifdef SFZUTF_USERMODE
        Key_p = sfzutf_discard_const(KeyData_p);
#else
        Key_p = (uint8_t *)SFZUTF_MALLOC(KeyDataLen);
        fail_if(Key_p == NULL, "Allocation ", (int)KeyDataLen);
        memcpy(Key_p, KeyData_p, KeyDataLen);
#endif

        Status = val_AssetLoadPlaintext(*KeyAssetId_p, Key_p, KeyDataLen);

#ifndef SFZUTF_USERMODE
        SFZUTF_FREE(Key_p);
#endif
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(Key)=", Status);

        Status = val_SymInitKey(*SymContext_pp, *KeyAssetId_p,
                                NULL, KeyDataLen);
    }
    else
    {
        Status = val_SymInitKey(*SymContext_pp, VAL_ASSETID_INVALID,
                                KeyData_p, KeyDataLen);
    }
    fail_if(Status != VAL_SUCCESS, "val_SymInitKey()=", Status);

    return END_TEST_SUCCES;
}

/* Chunk size is VALTEST_SYM_CONT_MAXCHUNK_SIZE = 16 */
/* Chunk size may be 16N, it must by 16 bytes aligned */
static int
do_multipart(const ValSymContextPtr_t SymContext_p,
             uint8_t* AAD_p,
             const ValSize_t AADLen,
             uint8_t* Input_p,
             const ValSize_t InputLen,
             uint8_t* Output_p,
             uint8_t* IV_p,
             ValSize_t * IVLen,
             uint8_t * Tag_p,
             ValSize_t * TagLen)
{
    ValStatus_t Status;
    ValSize_t TotalDataLeft = InputLen;
    ValSize_t TotalAADLeft = AADLen;
    ValSize_t OutputLen = VALTEST_SYM_CONT_MAXCHUNK_SIZE;
    // init has already been done
    while ((TotalDataLeft > 0) || (TotalAADLeft > 0))
    {
        if (TotalAADLeft > 0)
        {
            // Only process 16N bytes of AAD data, with at least 1 AAD byte left.
            // No PTX / CTX data is passed / processed.
            if ((TotalAADLeft <= 16))
            {
                // Process a final sequence of AAD data and all or the first 16N bytes of PTX/CTX data.
                if ((TotalDataLeft <= 16))
                {
                    OutputLen = TotalDataLeft;
                    // do final AAD and final Data
                    Status = val_SymCipherAEFinal(SymContext_p,
                                                  AAD_p, TotalAADLeft,
                                                  Input_p, InputLen,
                                                  Output_p, &OutputLen,
                                                  IV_p, IVLen,
                                                  Tag_p, TagLen);
                    fail_if(Status != VAL_SUCCESS, "val_SymCipherAEFinal()=", Status);
                    TotalDataLeft = 0;
                }
                else
                {
                    // final AAD, and first 16N bytes data
                    Status = val_SymCipherAEUpdate(SymContext_p,
                                                   AAD_p, TotalAADLeft,
                                                   Input_p,
                                                   VALTEST_SYM_CONT_MAXCHUNK_SIZE,
                                                   Output_p,
                                                   &OutputLen,
                                                   IV_p,
                                                   IVLen);
                    fail_if(Status != VAL_SUCCESS, "val_SymCipherAEUpdate()=", Status);

                    Input_p += VALTEST_SYM_CONT_MAXCHUNK_SIZE;
                    Output_p += VALTEST_SYM_CONT_MAXCHUNK_SIZE;
                    TotalDataLeft -= VALTEST_SYM_CONT_MAXCHUNK_SIZE;
                }

                TotalAADLeft = 0;
            }
            else
            {
                // only process 16N AAD
                Status = val_SymCipherAEUpdate(SymContext_p,
                                               AAD_p, VALTEST_SYM_CONT_MAXCHUNK_SIZE,
                                               NULL,
                                               0,
                                               Output_p,
                                               &OutputLen,
                                               IV_p,
                                               IVLen);
                fail_if(Status != VAL_SUCCESS, "val_SymCipherAEUpdate()=", Status);

                AAD_p += VALTEST_SYM_CONT_MAXCHUNK_SIZE;
                TotalAADLeft -= VALTEST_SYM_CONT_MAXCHUNK_SIZE;
            }
        }
        else
        {
            if (TotalDataLeft <= 16)
            {
                OutputLen = TotalDataLeft;
                // do final, without AAD (as it has already been processed)
                Status = val_SymCipherAEFinal(SymContext_p,
                                              NULL, 0U,
                                              Input_p, TotalDataLeft,
                                              Output_p, &OutputLen,
                                              IV_p, IVLen,
                                              Tag_p, TagLen);
                fail_if(Status != VAL_SUCCESS, "val_SymCipherAEFinal()=", Status);

                TotalDataLeft = 0;
            }
            else
            {
                // do update, AAD = NULL
                OutputLen = VALTEST_SYM_CONT_MAXCHUNK_SIZE;
                Status = val_SymCipherAEUpdate(SymContext_p,
                                               NULL,
                                               0U,
                                               Input_p,
                                               VALTEST_SYM_CONT_MAXCHUNK_SIZE,
                                               Output_p,
                                               &OutputLen,
                                               IV_p,
                                               IVLen);
                fail_if(Status != VAL_SUCCESS, "val_SymCipherAEUpdate()=", Status);

                Input_p += VALTEST_SYM_CONT_MAXCHUNK_SIZE;
                Output_p += VALTEST_SYM_CONT_MAXCHUNK_SIZE;
                TotalDataLeft -= VALTEST_SYM_CONT_MAXCHUNK_SIZE;
            }
        }
    }

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * do_SymAuthCryptTest
 *
 * Common helper function for authtenticated cipher testing.
 */
static int
do_SymAuthCryptTest(
        ValSymContextPtr_t SymContext_p,
        const ValSymMode_t Mode,
        const uint8_t * NonceHashKey_p,
        const uint32_t NonceHashKeyLen,
        const ValSymGCMMode_t GCMMode,
        const uint8_t * tvPt_p,
        const uint32_t tvPtLen,
        const uint8_t * tvCt_p,
        const uint32_t tvCtLen,
        const uint8_t * tvAad_p,
        const uint32_t tvAadLen,
        const uint8_t * tvTag_p,
        const uint32_t tvTagLen,
        const bool fDecrypt,
        const bool fInPlace,
        const bool fMultipart)
{
    int retval = END_TEST_SUCCES;
    static uint8_t ResultBuffer[VAL_TEST_MAX_BUFLEN];
    static uint8_t InputBuffer[VAL_TEST_MAX_BUFLEN];
    uint8_t TagBuffer[VAL_SYM_ALGO_MAX_TAG_SIZE];
    uint8_t IVBuffer[VAL_SYM_ALGO_MAX_IV_SIZE];
    ValStatus_t Status;
    uint8_t * Aad_p = NULL;
    uint8_t * TxtIn_p;
    uint8_t * TxtOut_p;
    uint8_t * Result_p = ResultBuffer;
#ifndef SFZUTF_USERMODE
    uint8_t * TempBuffer_p;
#endif
    ValSize_t TxtInLen;
    ValSize_t TxtOutLen;
    ValSize_t Padding = 0;
    ValSize_t TagLen = tvTagLen;
    ValSize_t ResultLen = sizeof(ResultBuffer);
    ValSize_t IVLen = 0;

    IDENTIFIER_NOT_USED(tvCtLen);

    Status = val_SymCipherAEInit(SymContext_p,
                                 NonceHashKey_p, NonceHashKeyLen,
                                 TagLen, tvPtLen, tvAadLen, GCMMode);
    fail_if(Status != VAL_SUCCESS, "val_SymCipherAEInit()=", Status);

    TxtInLen  = tvPtLen;
    TxtOutLen = TxtInLen;
    if (fDecrypt)
    {
        TxtIn_p = sfzutf_discard_const(tvCt_p);
        if (GCMMode == VAL_SYM_MODE_GCM_GHASH)
        {
            TxtOut_p = NULL;
        }
        else
        {
            TxtOut_p = sfzutf_discard_const(tvPt_p);
        }
        memcpy(TagBuffer, tvTag_p, TagLen);
    }
    else
    {
        if (GCMMode == VAL_SYM_MODE_GCM_GHASH)
        {
            /* Note always use the CipherText for a GHASH calculation */
            TxtIn_p = sfzutf_discard_const(tvCt_p);
            TxtOut_p = NULL;
        }
        else
        {
            TxtIn_p = sfzutf_discard_const(tvPt_p);
            TxtOut_p = sfzutf_discard_const(tvCt_p);
        }
        memset(TagBuffer, 0, sizeof(TagBuffer));
        TagLen = sizeof(TagBuffer);

        Status = val_SymCipherInitEncrypt(SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymCipherInitEncrypt()=", Status);
    }

#if defined(VALTEST_SYM_ALGO_CHACHA20) && defined(VALTEST_SYM_ALGO_POLY1305)
    if (Mode == VAL_SYM_MODE_CIPHER_CHACHA20_AEAD)
    {
        if (TxtInLen & (VAL_SYM_ALGO_CHACHA20_BLOCK_SIZE - 1))
        {
            Padding = (0 - TxtInLen) & (VAL_SYM_ALGO_CHACHA20_BLOCK_SIZE - 1);
            memcpy(InputBuffer, TxtIn_p, TxtInLen);
            memset(&InputBuffer[TxtInLen], 0x00, Padding);
            TxtIn_p = InputBuffer;
        }
    }
    else
#else
    IDENTIFIER_NOT_USED(Mode);
#endif
    if (TxtInLen & (VAL_SYM_ALGO_AES_BLOCK_SIZE - 1))
    {
        Padding = (0 - TxtInLen) & (VAL_SYM_ALGO_AES_BLOCK_SIZE - 1);
        memcpy(InputBuffer, TxtIn_p, TxtInLen);
        memset(&InputBuffer[TxtInLen], 0x00, Padding);
        TxtIn_p = InputBuffer;
    }

    if (fInPlace)
    {
#ifndef SFZUTF_USERMODE
        TempBuffer_p = (uint8_t *)SFZUTF_MALLOC(TxtInLen + Padding);
        fail_if(TempBuffer_p == NULL, "Allocation ", (int)(TxtInLen + Padding));
        Result_p = TempBuffer_p;
#endif
        memcpy(Result_p, TxtIn_p, (TxtInLen + Padding));
        TxtIn_p = Result_p;
    }
    else
    {
#ifndef SFZUTF_USERMODE
        TempBuffer_p = (uint8_t *)SFZUTF_MALLOC(TxtInLen + Padding);
        fail_if(TempBuffer_p == NULL, "Allocation ", (int)(TxtInLen + Padding));
        memcpy(TempBuffer_p, TxtIn_p, (TxtInLen + Padding));
        TxtIn_p = TempBuffer_p;
#endif

        if (GCMMode != VAL_SYM_MODE_GCM_GHASH)
        {
#ifndef SFZUTF_USERMODE
            Result_p = (uint8_t *)SFZUTF_MALLOC(TxtInLen + Padding);
            fail_if(Result_p == NULL, "Allocation ", (int)(TxtInLen + Padding));
            ResultLen = TxtInLen + Padding;
#endif
            memset(Result_p, 0xDC, ResultLen);
        }
        else
        {
            Result_p = NULL;
            ResultLen = 0;
        }
    }

    if (tvAadLen > 0)
    {
#ifdef SFZUTF_USERMODE
        Aad_p = sfzutf_discard_const(tvAad_p);
#else
        Aad_p = (uint8_t *)SFZUTF_MALLOC(tvAadLen);
        fail_if(Aad_p == NULL, "Allocation ", (int)tvAadLen);
        memcpy(Aad_p, tvAad_p, tvAadLen);
#endif
    }

    if (fMultipart)
    {
        Status = do_multipart(SymContext_p,
                              Aad_p,tvAadLen,
                              TxtIn_p, TxtInLen,
                              Result_p,
                              IVBuffer, &IVLen,
                              TagBuffer, &TagLen);
    }
    else
    {
        Status = val_SymCipherAEFinal(SymContext_p,
                                      Aad_p, tvAadLen,
                                      TxtIn_p, TxtInLen,
                                      Result_p, &ResultLen,
                                      IVBuffer, &IVLen,
                                      TagBuffer, &TagLen);
    }

    if (val_CheckFunctionResult(Status) == VAL_SUCCESS)
    {
        if (TxtOut_p != NULL)
        {
            if (memcmp(Result_p, TxtOut_p, TxtOutLen) != 0)
            {
                print_fail("memcmp(Result_p, TxtOut_p, TxtOutLen) != 0", -1);
                retval = END_TEST_FAIL;
            }
        }
        if (!fDecrypt)
        {
            if (memcmp(TagBuffer, tvTag_p, TagLen) != 0)
            {
                print_fail("memcmp(TagBuffer, tvTag_p, TagLen) != 0", -1);
                retval = END_TEST_FAIL;
            }
        }
    }
    else
    {
        retval = END_TEST_FAIL;
        print_fail(fMultipart ? "do_multipart()=" : "val_SymCipherAEFinal()=", Status);
    }

#ifndef SFZUTF_USERMODE
    if (Aad_p != NULL)
    {
        SFZUTF_FREE(Aad_p);
    }
    if (!fInPlace)
    {
        SFZUTF_FREE(TxtIn_p);
    }
    if (Result_p != NULL)
    {
        SFZUTF_FREE(Result_p);
    }
#endif

    return retval;
}
#endif

#ifdef VALTEST_SYM_ALGO_AES_CCM
static int
do_test_authenticated_crypto_aes_ccm(
    const int _i,
    const bool fMultipart)
{
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    for (Index = 0U; ; Index++)
    {
        TestVector_AES_CCM_t tv_p;
        ValSymContextPtr_t SymContext_p;
        ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;

        tv_p = test_vectors_aes_ccm_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (fMultipart && ((tv_p->PtLen <= 16) && (tv_p->AadLen <= 16)))
        {
            test_vectors_aes_ccm_release(tv_p);
            continue;
        }

        if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_AES,
                                           VAL_SYM_MODE_CIPHER_CCM,
                                           tv_p->Key_p, tv_p->KeyLen,
                                           ((_i & 4) != 0),
                                           ((_i & 1) != 0),
                                           &SymContext_p,
                                           &KeyAssetId) == END_TEST_SUCCES)
        {
            if (do_SymAuthCryptTest(SymContext_p,
                                    VAL_SYM_MODE_CIPHER_CCM,
                                    tv_p->Nonce_p, tv_p->NonceLen,
                                    VAL_SYM_MODE_GCM_NONE,
                                    tv_p->Pt_p, tv_p->PtLen,
                                    tv_p->Ct_p, tv_p->CtLen,
                                    tv_p->Aad_p, tv_p->AadLen,
                                    (tv_p->Ct_p + tv_p->PtLen),
                                    (tv_p->CtLen - tv_p->PtLen),
                                    ((_i & 1) != 0),
                                    ((_i == 2) || (_i == 3)),
                                    fMultipart) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            (void)val_SymRelease(SymContext_p);
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        if (KeyAssetId != VAL_ASSETID_INVALID)
        {
            (void)val_AssetFree(KeyAssetId);
            KeyAssetId = VAL_ASSETID_INVALID;
        }

        test_vectors_aes_ccm_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
    return END_TEST_SUCCES;
}

START_TEST(test_authenticated_crypto_aes_ccm)
{
    if (do_test_authenticated_crypto_aes_ccm(_i, false) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
    if (do_test_authenticated_crypto_aes_ccm(_i, true) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST
#endif


#ifdef VALTEST_SYM_ALGO_AES_GCM
/**
 * @brief GCM tests
 * 1. decrypt encrypted vector data
 * 2. compare decrypted data with vector plain text
 *    if plain text is equal, Confirmed decrypt working
 * 3. Encrypt vector plain text
 * 4. decrypt encrypted data
 * 5. compare with vector plain text
 *    if plain text is equal, encrypt working
 */
static int
do_gcm_encrypt(const ValSymContextPtr_t SymContext_p,
               const TestVector_AES_GCM_t tv_p,
               uint8_t * IV_p,
               ValSize_t * IVLen,
               uint8_t * Tag_p,
               ValSize_t * TagLen,
               uint8_t * Result_p,
               ValSize_t * ResultLen,
               const bool fNoRandomIV,
               const bool fMultipart)
{
    static uint8_t InputBuffer[VAL_TEST_MAX_BUFLEN];
    uint8_t TagBuffer[VAL_SYM_ALGO_MAX_TAG_SIZE];

    uint8_t * TxtIn_p;
    uint8_t * Aad_p = NULL;
#ifndef SFZUTF_USERMODE
    uint8_t * TempBuffer_p;
#endif
    ValStatus_t Status;
    ValSize_t TxtInLen;
    ValSize_t Padding = 0;

    if (fNoRandomIV)
    {
        if (tv_p->IVLen == 12)
        {
            uint8_t IV[VAL_SYM_ALGO_AES_IV_SIZE];

            memcpy(IV, tv_p->IV_p, tv_p->IVLen);
            memcpy(&IV[12], "\x00\x00\x00\x01", 4);
            Status = val_SymInitIV(SymContext_p, IV, VAL_SYM_ALGO_AES_IV_SIZE);
        }
        else
        {
            Status = val_SymInitIV(SymContext_p, tv_p->Y0_p, VAL_SYM_ALGO_AES_IV_SIZE);
        }
        fail_if(Status != VAL_SUCCESS, "val_SymInitIV()=", Status);

        Status = val_SymCipherInitNoRandomIV(SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymCipherInitNoRandomIV()=", Status);
    }

    *TagLen = tv_p->TagLen;
    Status = val_SymCipherAEInit(SymContext_p,
                                 NULL, 0,
                                 *TagLen, tv_p->PtLen, tv_p->AadLen, VAL_SYM_MODE_GCM_AUTO);
    fail_if(Status != VAL_SUCCESS, "val_SymCipherAEInit()=", Status);

    /* set input parameters */
    TxtIn_p = sfzutf_discard_const(tv_p->Pt_p);
    TxtInLen  = tv_p->PtLen;

    memcpy(Tag_p, tv_p->Tag_p, *TagLen);
    memset(TagBuffer, 0, sizeof(TagBuffer));
    *TagLen = sizeof(TagBuffer);

    Status = val_SymCipherInitEncrypt(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymCipherInitEncrypt()=", Status);

    if (tv_p->PtLen & (VAL_SYM_ALGO_AES_BLOCK_SIZE - 1))
    {
        Padding = (0 - TxtInLen) & (VAL_SYM_ALGO_AES_BLOCK_SIZE - 1);
        memcpy(InputBuffer, TxtIn_p, TxtInLen);
        memset(&InputBuffer[TxtInLen], 0x00, Padding);
        TxtIn_p = InputBuffer;
    }
#ifndef SFZUTF_USERMODE
    TempBuffer_p = (uint8_t *)SFZUTF_MALLOC(TxtInLen + Padding);
    fail_if(TempBuffer_p == NULL, "Allocation ", (int)(TxtInLen + Padding));
    memcpy(TempBuffer_p, TxtIn_p, (TxtInLen + Padding));
    TxtIn_p = TempBuffer_p;
#endif

    if (tv_p->AadLen > 0)
    {
#ifdef SFZUTF_USERMODE
        Aad_p = sfzutf_discard_const(tv_p->Aad_p);
#else
        Aad_p = (uint8_t *)SFZUTF_MALLOC(tv_p->AadLen);
        fail_if(Aad_p == NULL, "Allocation ", (int)tv_p->AadLen);
        memcpy(Aad_p, tv_p->Aad_p, tv_p->AadLen);
#endif
    }

    if (fMultipart)
    {
        Status = do_multipart(SymContext_p,
                              Aad_p, tv_p->AadLen,
                              TxtIn_p, TxtInLen,
                              Result_p,
                              IV_p, IVLen,
                              Tag_p, TagLen);
    }
    else
    {
        // init-final operation
        Status = val_SymCipherAEFinal(SymContext_p,
                                      Aad_p, tv_p->AadLen,
                                      TxtIn_p, TxtInLen,
                                      Result_p, ResultLen,
                                      IV_p, IVLen,
                                      Tag_p, TagLen);
    }


#ifndef SFZUTF_USERMODE
    if (Aad_p != NULL)
    {
        SFZUTF_FREE(Aad_p);
    }
    SFZUTF_FREE(TxtIn_p);
#endif

    if (fMultipart)
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "do_multipart()=", Status);
    }
    else
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymCipherAEFinal()=", Status);
    }

    return END_TEST_SUCCES;
}


static int
do_gcm_decrypt(const ValSymContextPtr_t SymContext_p,
               const TestVector_AES_GCM_t tv_p,
               uint8_t * IV_p,
               ValSize_t * IVLen,
               uint8_t * Tag_p,
               ValSize_t * TagLen,
               uint8_t * Result_p,
               ValSize_t * ResultLen,
               uint8_t* EncryptData_p,
               const bool fMultipart)
{
    static uint8_t InputBuffer[VAL_TEST_MAX_BUFLEN];
    uint8_t * TxtIn_p;
    uint8_t * Aad_p = NULL;
#ifndef SFZUTF_USERMODE
    uint8_t * TempBuffer_p;
#endif
    ValSize_t TxtInLen;
    ValSize_t Padding = 0;
    ValStatus_t Status = 0;

    *TagLen = (uint32_t)tv_p->TagLen;
    if (*IVLen == 0)
    {
        /* Only acceptible IV lengths are 12 and 16 bytes
         * When 16 bytes, it is expected that the counter value is already set
         */
        *IVLen = (uint32_t)tv_p->IVLen;
        if (*IVLen == 12 || *IVLen == 16)
        {
            memcpy(IV_p, tv_p->IV_p, *IVLen);
            if(*IVLen == 12)
            {
                memcpy(&IV_p[12], "\x00\x00\x00\x01", 4);
                /* val_SymCipherAEFinal requires a 16 byte input buffer */
                *IVLen += 4;
            }
        }
    }
    else
    {
        if (*IVLen < 12 || *IVLen > 16)
        {
            LOG_WARN("GCM IV length is unsupported %d\n", *IVLen);
        }
    }
    Status = val_SymInitIV(SymContext_p, IV_p, VAL_SYM_ALGO_AES_IV_SIZE);
    fail_if(Status != VAL_SUCCESS, "val_SymInitIV()=", Status);

    Status = val_SymCipherAEInit(SymContext_p,
                                 NULL, 0,
                                 (uint32_t)*TagLen, tv_p->PtLen, tv_p->AadLen, VAL_SYM_MODE_GCM_AUTO);
    fail_if(Status != VAL_SUCCESS, "val_SymCipherAEInit()=", Status);

    TxtInLen  = tv_p->CtLen;
    if(EncryptData_p == NULL)
    {
        TxtIn_p = sfzutf_discard_const(tv_p->Ct_p);
        memcpy(Tag_p, tv_p->Tag_p, (uint32_t)*TagLen);
    }
    else
    {
        TxtIn_p = EncryptData_p;
    }

    if (tv_p->PtLen & (VAL_SYM_ALGO_AES_BLOCK_SIZE - 1))
    {
        Padding = (0 - TxtInLen) & (VAL_SYM_ALGO_AES_BLOCK_SIZE - 1);
        memcpy(InputBuffer, TxtIn_p, TxtInLen);
        memset(&InputBuffer[TxtInLen], 0x00, Padding);
        TxtIn_p = InputBuffer;
    }
#ifndef SFZUTF_USERMODE
    TempBuffer_p = (uint8_t *)SFZUTF_MALLOC(TxtInLen + Padding);
    fail_if(TempBuffer_p == NULL, "Allocation ", (int)(TxtInLen + Padding));
    memcpy(TempBuffer_p, TxtIn_p, (TxtInLen + Padding));
    TxtIn_p = TempBuffer_p;
#endif

    if (tv_p->AadLen > 0)
    {
#ifdef SFZUTF_USERMODE
        Aad_p = sfzutf_discard_const(tv_p->Aad_p);
#else
        Aad_p = (uint8_t *)SFZUTF_MALLOC(tv_p->AadLen);
        fail_if(Aad_p == NULL, "Allocation ", (int)tv_p->AadLen);
        memcpy(Aad_p, tv_p->Aad_p, tv_p->AadLen);
#endif
    }

    if (fMultipart)
    {
        Status = do_multipart(SymContext_p,
                              Aad_p, tv_p->AadLen,
                              TxtIn_p, TxtInLen,
                              Result_p,
                              IV_p, IVLen,
                              Tag_p, TagLen);
    }
    else
    {
        Status = val_SymCipherAEFinal(SymContext_p,
                                      Aad_p, tv_p->AadLen,
                                      TxtIn_p, TxtInLen,
                                      Result_p, ResultLen,
                                      IV_p, IVLen,
                                      Tag_p, TagLen);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymCipherAEFinal()=", Status);
    }

#ifndef SFZUTF_USERMODE
    if (Aad_p != NULL)
    {
        SFZUTF_FREE(Aad_p);
    }
    SFZUTF_FREE(TxtIn_p);
#endif

    return END_TEST_SUCCES;
}


static int
test_authenticated_crypto_aes_gcm(const ValSymGCMMode_t Mode,
                                  const int _i,
                                  const bool fMultipart)
{
    uint32_t Index;
    int Failed = 0;
    int Success = 0;
    IDENTIFIER_NOT_USED(Mode);

    //loop trough vectors
    for (Index = 0U; ; Index++)
    {
        TestVector_AES_GCM_t tv_p;
        ValSymContextPtr_t SymContext_p;
        ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;
        uint8_t IVBuffer[VAL_SYM_ALGO_AES_IV_SIZE];
        uint8_t ResultBuffer[VAL_TEST_MAX_BUFLEN];
        uint8_t TagBuffer[VAL_SYM_ALGO_MAX_TAG_SIZE];
        ValSize_t ResultLen = sizeof(ResultBuffer);
        ValSize_t IVLen = 0;
        ValSize_t TagLen = 0;
        int VectorPass = END_TEST_FAIL;

        tv_p = test_vectors_aes_gcm_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->IVLen != 12)
        {
            // ignore vector since non-96 bits IV's are not supported
            LOG_WARN("AES-GCM vector %d ignored (non 96-bit IV)\n", Index);
            test_vectors_aes_gcm_release(tv_p);
            continue;
        }

        if (tv_p->PtLen <= 16U && fMultipart)
        {
            //ignore vectors with small amount of data for multipart test
            test_vectors_aes_gcm_release(tv_p);
            continue;
        }

        /* decrypt test*/
        {
            if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_AES,
                                               VAL_SYM_MODE_CIPHER_GCM,
                                               tv_p->Key_p, tv_p->KeyLen,
                                               ((_i & 4) != 0),
                                               true,
                                               &SymContext_p,
                                               &KeyAssetId) == END_TEST_SUCCES)
            {
                memset(ResultBuffer, 0, sizeof(ResultBuffer));
                if (do_gcm_decrypt(SymContext_p, tv_p,
                                   IVBuffer, &IVLen,
                                   TagBuffer, &TagLen,
                                   ResultBuffer, &ResultLen, NULL,
                                   fMultipart) == END_TEST_SUCCES)
                {
                    if (!fMultipart && ResultLen != tv_p->PtLen)
                    {
                        LOG_CRIT("ResultLen != tv_p->PtLen (%d)\n", (int)ResultLen);
                    }
                    else if (memcmp(tv_p->Pt_p, ResultBuffer, tv_p->PtLen) != 0)
                    {
                        // pt checked here, tag is already checked by fw
                        LOG_CRIT("ResultBuffer != tv_p->Pt_p\n");
                    }
                    else
                    {
                        /* Data looks OK */
                        VectorPass = END_TEST_SUCCES;
                    }
                }

                (void)val_SymRelease(SymContext_p);
            }
            memset(ResultBuffer, 0, sizeof(ResultBuffer));
            memset(TagBuffer, 0, sizeof(TagBuffer));
            memset(IVBuffer, 0, sizeof(IVBuffer));
            TagLen = 0;
        }

        /* do encrypt test only when decrypt succeeds */
        if (VectorPass == END_TEST_SUCCES)
        {
            VectorPass = END_TEST_FAIL;
            if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_AES,
                                               VAL_SYM_MODE_CIPHER_GCM,
                                               tv_p->Key_p, tv_p->KeyLen,
                                               ((_i & 4) != 0),
                                               false,
                                               &SymContext_p,
                                               &KeyAssetId) == END_TEST_SUCCES)
            {
                IVLen = 16;
                if (do_gcm_encrypt(SymContext_p, tv_p,
                                   IVBuffer, &IVLen,
                                   TagBuffer, &TagLen,
                                   ResultBuffer, &ResultLen,
                                   false, fMultipart) == END_TEST_SUCCES)
                {
                    (void)val_SymRelease(SymContext_p);

                    /* Decrypt encrypted data */
                    if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_AES,
                                                       VAL_SYM_MODE_CIPHER_GCM,
                                                       tv_p->Key_p, tv_p->KeyLen,
                                                       ((_i & 4) != 0),
                                                       true,
                                                       &SymContext_p,
                                                       &KeyAssetId) == END_TEST_SUCCES)
                    {
                        /* 2nd Resultbuffer is the encrypted data of the encrypt operation as input
                         * for the decrypt operation*/

                        /* For decrypt, Tag from encrypt operation is input */
                        if (do_gcm_decrypt(SymContext_p, tv_p,
                                           IVBuffer, &IVLen,
                                           TagBuffer, &TagLen,
                                           ResultBuffer, &ResultLen, ResultBuffer,
                                           fMultipart) == END_TEST_SUCCES)
                        {
                            (void)val_SymRelease(SymContext_p);

                            if (!fMultipart && ResultLen != tv_p->PtLen)
                            {
                                LOG_CRIT("ResultLen != tv_p->PtLen %d\n", (int)ResultLen);
                            }
                            else if (memcmp(tv_p->Pt_p, ResultBuffer, tv_p->PtLen) != 0)
                            {
                                // tag not checked here as this is already done by firmware!
                                // (firmware would give verify error)
                                LOG_CRIT("ResultBuffer != tv_p->Pt_p %d\n", -1);
                            }
                            else
                            {
                                /* For coverage purpose */
                                if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_AES,
                                                                   VAL_SYM_MODE_CIPHER_GCM,
                                                                   tv_p->Key_p, tv_p->KeyLen,
                                                                   ((_i & 4) != 0),
                                                                   false,
                                                                   &SymContext_p,
                                                                   &KeyAssetId) == END_TEST_SUCCES)
                                {
                                    /* Do same vector with IV from vector*/
                                    if (do_gcm_encrypt(SymContext_p, tv_p,
                                                       IVBuffer, &IVLen,
                                                       TagBuffer, &TagLen,
                                                       ResultBuffer, &ResultLen,
                                                       true, fMultipart)
                                                       == END_TEST_SUCCES)
                                    {
                                        // no random iv here, so check generated tag against tag in vector
                                        if (memcmp(TagBuffer, tv_p->Tag_p, TagLen) != 0)
                                        {
                                            VectorPass = END_TEST_FAIL;
                                        }
                                        else
                                        {
                                            VectorPass = END_TEST_SUCCES;
                                        }
                                    }

                                    (void)val_SymRelease(SymContext_p);
                                }
                            }
                        }
                        else
                        {
                            (void)val_SymRelease(SymContext_p);
                        }
                    }
                }
                else
                {
                    (void)val_SymRelease(SymContext_p);
                }
            }
        }
        if (VectorPass == END_TEST_FAIL)
        {
            LOG_CRIT("AES-GCM vector %d Failed\n", Index);
            Failed++;
        }
        else
        {
            Success++;
        }
        test_vectors_aes_gcm_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }

    return END_TEST_SUCCES;
}


START_TEST(test_authenticated_crypto_aes_gcm_auto)
{
    // init-final tests
    if (test_authenticated_crypto_aes_gcm(VAL_SYM_MODE_GCM_AUTO, _i, false) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
    // multipart tests
    if (test_authenticated_crypto_aes_gcm(VAL_SYM_MODE_GCM_AUTO, _i, true) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST
#endif /* VALTEST_SYM_ALGO_AES_GCM */


#if defined(VALTEST_SYM_ALGO_CHACHA20) && defined(VALTEST_SYM_ALGO_POLY1305)
START_TEST(test_authenticated_crypto_chacha20_aead)
{
    uint32_t Index;
    int Failed = 0;
    int Success = 0;

    unsupported_if(!valtest_IsChaCha20Supported(), "");

    for (Index = 0U; ; Index++)
    {
        TestVector_ChaCha20_Poly1305_t tv_p;
        ValSymContextPtr_t SymContext_p;
        ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;

        tv_p = test_vectors_chacha20_poly1305_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_CHACHA20,
                                           VAL_SYM_MODE_CIPHER_CHACHA20_AEAD,
                                           tv_p->Key_p, tv_p->KeyLen,
                                           ((_i & 4) != 0),
                                           ((_i & 1) != 0),
                                           &SymContext_p,
                                           &KeyAssetId) == END_TEST_SUCCES)
        {
            if (do_SymAuthCryptTest(SymContext_p,
                                    VAL_SYM_MODE_CIPHER_CHACHA20_AEAD,
                                    tv_p->Nonce_p, tv_p->NonceLen,
                                    VAL_SYM_MODE_GCM_NONE,
                                    tv_p->PlainData_p, tv_p->DataLen,
                                    tv_p->CipherData_p, tv_p->DataLen,
                                    tv_p->Aad_p, tv_p->AadLen,
                                    tv_p->Tag_p, 16,
                                    ((_i & 1) != 0),
                                    ((_i == 2) || (_i == 3)), false) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Process vector %d\n", Index);
                Failed++;
            }

            (void)val_SymRelease(SymContext_p);
        }
        else
        {
            LOG_CRIT("Process vector %d\n", Index);
            Failed++;
        }

        if (KeyAssetId != VAL_ASSETID_INVALID)
        {
            (void)val_AssetFree(KeyAssetId);
            KeyAssetId = VAL_ASSETID_INVALID;
        }

        test_vectors_chacha20_poly1305_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif


#ifdef VALTEST_SYM_ALGO_ARIA_CCM
START_TEST(test_authenticated_crypto_aria_ccm)
{
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    unsupported_if(!valtest_IsARIASupported(), "");

    for (Index = 0U; ; Index++)
    {
        TestVector_ARIA_CCM_t tv_p;
        ValSymContextPtr_t SymContext_p;
        ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;

        tv_p = test_vectors_aria_ccm_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_ARIA,
                                           VAL_SYM_MODE_CIPHER_CCM,
                                           tv_p->Key_p, tv_p->KeyLen,
                                           ((_i & 4) != 0),
                                           ((_i & 1) != 0),
                                           &SymContext_p,
                                           &KeyAssetId) == END_TEST_SUCCES)
        {
            if (do_SymAuthCryptTest(SymContext_p,
                                    VAL_SYM_MODE_CIPHER_CCM,
                                    tv_p->Nonce_p, tv_p->NonceLen,
                                    VAL_SYM_MODE_GCM_NONE,
                                    tv_p->Pt_p, tv_p->PtLen,
                                    tv_p->Ct_p, tv_p->CtLen,
                                    tv_p->Aad_p, tv_p->AadLen,
                                    (tv_p->Ct_p+tv_p->PtLen), (tv_p->CtLen - tv_p->PtLen),
                                    ((_i & 1) != 0),
                                    ((_i == 2) || (_i == 3)), false) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            (void)val_SymRelease(SymContext_p);
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        if (KeyAssetId != VAL_ASSETID_INVALID)
        {
            (void)val_AssetFree(KeyAssetId);
            KeyAssetId = VAL_ASSETID_INVALID;
        }

        test_vectors_aria_ccm_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif


#ifdef VALTEST_SYM_ALGO_ARIA_GCM
static int
test_authenticated_crypto_aria_gcm(
        const ValSymGCMMode_t Mode,
        const int _i)
{
    uint32_t Index;
    int Failed = 0;
    int Success = 0;
    IDENTIFIER_NOT_USED(Mode);

    //loop trough vectors
    for (Index = 0U; ; Index++)
    {
        TestVector_ARIA_GCM_t tv_p;
        ValSymContextPtr_t SymContext_p;
        ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;
        uint8_t IVBuffer[VAL_SYM_ALGO_ARIA_IV_SIZE];
        uint8_t ResultBuffer[VAL_TEST_MAX_BUFLEN];
        uint8_t TagBuffer[VAL_SYM_ALGO_MAX_TAG_SIZE];
        ValSize_t ResultLen = sizeof(ResultBuffer);
        ValSize_t IVLen = 0;
        ValSize_t TagLen = 0;
        int VectorPass = END_TEST_FAIL;

        tv_p = test_vectors_aria_gcm_get(Index);
        if (tv_p == NULL)
        {
            break;
        }
        if (tv_p->IVLen != 12)
        {
            // ignore vector since non-96 bits IV's are not supported
            LOG_CRIT("ARIA-GCM vector %d ignored (non 96-bit IV)\n", Index);
            test_vectors_aria_gcm_release(tv_p);
            continue;
        }
        /* decrypt test*/
        {
            if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_ARIA,
                                               VAL_SYM_MODE_CIPHER_GCM,
                                               tv_p->Key_p, tv_p->KeyLen,
                                               ((_i & 4) != 0),
                                               true,
                                               &SymContext_p,
                                               &KeyAssetId) == END_TEST_SUCCES)
            {
                memset(ResultBuffer, 0, sizeof(ResultBuffer));
                if (do_gcm_decrypt(SymContext_p, (TestVector_AES_GCM_t)tv_p,
                                IVBuffer, &IVLen,
                                TagBuffer, &TagLen,
                                ResultBuffer, &ResultLen, NULL, false) == END_TEST_SUCCES)
                {
                    //check whether data is corresponding with vector
                    //check whether pt is ok compared to vector
                    if(ResultLen != tv_p->PtLen)
                    {
                        LOG_CRIT("ResultLen != tv_p->PtLen (%d)\n", (int)ResultLen);
                    }
                    else if(memcmp(tv_p->Pt_p, ResultBuffer, tv_p->PtLen) !=0)
                    {
                        LOG_CRIT("ResultBuffer != tv_p->Pt_p\n");
                    }
                    else
                    {
                        VectorPass = END_TEST_SUCCES;
                    }
                }

                (void)val_SymRelease(SymContext_p);
            }
            memset(ResultBuffer, 0, sizeof(ResultBuffer));
            memset(TagBuffer, 0, sizeof(TagBuffer));
            memset(IVBuffer, 0, sizeof(IVBuffer));
            IVLen = 0;
            TagLen = 0;
        }

        /* do encrypt test only when decrypt succeeds*/
        if (VectorPass == END_TEST_SUCCES)
        {
            VectorPass = END_TEST_FAIL;
            if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_ARIA,
                                               VAL_SYM_MODE_CIPHER_GCM,
                                               tv_p->Key_p, tv_p->KeyLen,
                                               ((_i & 4) != 0),
                                               false,
                                               &SymContext_p,
                                               &KeyAssetId) == END_TEST_SUCCES)
            {
                IVLen = 16;
                if (do_gcm_encrypt(SymContext_p, (TestVector_AES_GCM_t)tv_p,
                                   IVBuffer, &IVLen,
                                   TagBuffer, &TagLen,
                                   ResultBuffer, &ResultLen, false, false) == END_TEST_SUCCES)
                {
                    (void)val_SymRelease(SymContext_p);

                    /* Decrypt encrypted data */
                    if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_ARIA,
                                                       VAL_SYM_MODE_CIPHER_GCM,
                                                       tv_p->Key_p, tv_p->KeyLen,
                                                       ((_i & 4) != 0),
                                                       true,
                                                       &SymContext_p,
                                                       &KeyAssetId) == END_TEST_SUCCES)
                    {
                        /* 2nd Resultbuffer is the encrypted data of the encrypt operation */
                        if (do_gcm_decrypt(SymContext_p, (TestVector_AES_GCM_t)tv_p,
                                           IVBuffer, &IVLen,
                                           TagBuffer, &TagLen,
                                           ResultBuffer, &ResultLen, ResultBuffer,
                                           false) == END_TEST_SUCCES)
                        {
                            if (ResultLen != tv_p->PtLen)
                            {
                                LOG_CRIT("ResultLen != tv_p->PtLen %d\n", (int)ResultLen);
                            }
                            else if(memcmp(tv_p->Pt_p, ResultBuffer, tv_p->PtLen) !=0)
                            {
                                LOG_CRIT("ResultBuffer != tv_p->Pt_p %d\n", -1);
                            }
                            else
                            {
                                VectorPass = END_TEST_SUCCES;
                            }
                        }

                        (void)val_SymRelease(SymContext_p);
                    }
                }
                else
                {
                    (void)val_SymRelease(SymContext_p);
                }
            }
        }
        if(VectorPass == END_TEST_FAIL)
        {
            LOG_CRIT("ARIA-GCM vector %d Failed\n", Index);
            Failed++;
        }
        else
        {
            Success++;
        }
        test_vectors_aria_gcm_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }

    return END_TEST_SUCCES;
}


START_TEST(test_authenticated_crypto_aria_gcm_auto)
{
    unsupported_if(!valtest_IsARIASupported(), "");

    if (test_authenticated_crypto_aria_gcm(VAL_SYM_MODE_GCM_AUTO, _i) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST
#endif


#ifdef VALTEST_SYM_ALGO_SM4_GCM
static int
run_authenticated_crypto_sm4_gcm(const int _i)
{
    uint32_t Index;
    int Failed = 0;
    int Success = 0;

    //loop trough vectors
    for (Index = 0U; ; Index++)
    {
        TestVector_SM4_GCM_t tv_p;
        ValSymContextPtr_t SymContext_p;
        ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;
        uint8_t IVBuffer[VAL_SYM_ALGO_SM4_IV_SIZE];
        uint8_t ResultBuffer[VAL_TEST_MAX_BUFLEN];
        uint8_t TagBuffer[VAL_SYM_ALGO_MAX_TAG_SIZE];
        ValSize_t ResultLen = sizeof(ResultBuffer);
        ValSize_t IVLen = 0;
        ValSize_t TagLen = 0;
        int VectorPass = END_TEST_FAIL;

        tv_p = test_vectors_sm4_gcm_get(Index);
        if (tv_p == NULL)
        {
            break;
        }
        if (tv_p->IVLen != 12)
        {
            // ignore vector since non-96 bits IV's are not supported
            LOG_CRIT("SM4-GCM vector %d ignored (non 96-bit IV)\n", Index);
            test_vectors_sm4_gcm_release(tv_p);
            continue;
        }

        /* decrypt test */
        {
            if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_SM4,
                                               VAL_SYM_MODE_CIPHER_GCM,
                                               tv_p->Key_p, tv_p->KeyLen,
                                               ((_i & 4) != 0),
                                               true,
                                               &SymContext_p,
                                               &KeyAssetId) == END_TEST_SUCCES)
            {
                memset(ResultBuffer, 0, sizeof(ResultBuffer));
                if (do_gcm_decrypt(SymContext_p, (TestVector_AES_GCM_t)tv_p,
                                   IVBuffer, &IVLen,
                                   TagBuffer, &TagLen,
                                   ResultBuffer, &ResultLen, NULL, false) == END_TEST_SUCCES)
                {
                    // check whether data is corresponding with vector
                    // check whether pt is ok compared to vector
                    if(ResultLen != tv_p->PtLen)
                    {
                        LOG_CRIT("ResultLen != tv_p->PtLen (%d)\n", (int)ResultLen);
                    }
                    else if(memcmp(tv_p->Pt_p, ResultBuffer, tv_p->PtLen) !=0)
                    {
                        LOG_CRIT("ResultBuffer != tv_p->Pt_p\n");
                    }
                    else
                    {
                        VectorPass = END_TEST_SUCCES;
                    }
                }

                (void)val_SymRelease(SymContext_p);
            }
            memset(ResultBuffer, 0, sizeof(ResultBuffer));
            memset(TagBuffer, 0, sizeof(TagBuffer));
            memset(IVBuffer, 0, sizeof(IVBuffer));
            IVLen = 0;
            TagLen = 0;
        }

        /* do encrypt test only when decrypt succeeds */
        if (VectorPass == END_TEST_SUCCES)
        {
            VectorPass = END_TEST_FAIL;
            if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_SM4,
                                               VAL_SYM_MODE_CIPHER_GCM,
                                               tv_p->Key_p, tv_p->KeyLen,
                                               ((_i & 4) != 0),
                                               false,
                                               &SymContext_p,
                                               &KeyAssetId) == END_TEST_SUCCES)
            {
                IVLen = 16;
                if (do_gcm_encrypt(SymContext_p, (TestVector_AES_GCM_t)tv_p,
                                   IVBuffer, &IVLen,
                                   TagBuffer, &TagLen,
                                   ResultBuffer, &ResultLen, false, false) == END_TEST_SUCCES)
                {
                    (void)val_SymRelease(SymContext_p);

                    /* Decrypt encrypted data */
                    if (SetupTestContextAndEnvironment(VAL_SYM_ALGO_CIPHER_SM4,
                                                       VAL_SYM_MODE_CIPHER_GCM,
                                                       tv_p->Key_p, tv_p->KeyLen,
                                                       ((_i & 4) != 0),
                                                       true,
                                                       &SymContext_p,
                                                       &KeyAssetId) == END_TEST_SUCCES)
                    {
                        /* 2nd Resultbuffer is the encrypted data of the encrypt operation */
                        if (do_gcm_decrypt(SymContext_p, (TestVector_AES_GCM_t)tv_p,
                                           IVBuffer, &IVLen,
                                           TagBuffer, &TagLen,
                                           ResultBuffer, &ResultLen, ResultBuffer, false) == END_TEST_SUCCES)
                        {
                            if (ResultLen != tv_p->PtLen)
                            {
                                LOG_CRIT("ResultLen != tv_p->PtLen %d\n", (int)ResultLen);
                            }
                            else if(memcmp(tv_p->Pt_p, ResultBuffer, tv_p->PtLen) !=0)
                            {
                                LOG_CRIT("ResultBuffer != tv_p->Pt_p %d\n", -1);
                            }
                            else
                            {

                                VectorPass = END_TEST_SUCCES;
                            }
                        }

                        (void)val_SymRelease(SymContext_p);
                    }
                }
                else
                {
                    (void)val_SymRelease(SymContext_p);
                }
            }
        }
        if(VectorPass == END_TEST_FAIL)
        {
            LOG_CRIT("SM4-GCM vector %d Failed\n", Index);
            Failed++;
        }
        else
        {
            Success++;
        }
        test_vectors_sm4_gcm_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }

    return END_TEST_SUCCES;
}

START_TEST(test_authenticated_crypto_sm4_gcm)
{
    unsupported_if(!valtest_IsSM4Supported(), "");

    if (run_authenticated_crypto_sm4_gcm(_i) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST
#endif


int
suite_add_test_SymAuthCrypto(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SymCrypto_CipherAuth_Tests");
    if (TestCase_p != NULL)
    {
#if defined(VALTEST_SYM_ALGO_AES_CCM) || \
    defined(VALTEST_SYM_ALGO_AES_GCM) || \
    (defined(VALTEST_SYM_ALGO_CHACHA20) && defined(VALTEST_SYM_ALGO_POLY1305)) || \
    defined(VALTEST_SYM_ALGO_ARIA_CCM) || \
    defined(VALTEST_SYM_ALGO_ARIA_GCM) || \
    defined(VALTEST_SYM_ALGO_SM4_GCM)
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

#ifdef VALTEST_SYM_ALGO_AES_CCM
        if (sfzutf_test_add_loop(TestCase_p, test_authenticated_crypto_aes_ccm, 6) != 0) goto FuncErrorReturn;
#endif
#ifdef VALTEST_SYM_ALGO_AES_GCM
        if (sfzutf_test_add(TestCase_p, test_authenticated_crypto_aes_gcm_auto) != 0) goto FuncErrorReturn;
#endif

#if defined(VALTEST_SYM_ALGO_CHACHA20) && defined(VALTEST_SYM_ALGO_POLY1305)
        if (sfzutf_test_add_loop(TestCase_p, test_authenticated_crypto_chacha20_aead, 6) != 0) goto FuncErrorReturn;
#endif

#ifdef VALTEST_SYM_ALGO_ARIA_CCM
        if (sfzutf_test_add_loop(TestCase_p, test_authenticated_crypto_aria_ccm, 6) != 0) goto FuncErrorReturn;
#endif
#ifdef VALTEST_SYM_ALGO_ARIA_GCM
        if (sfzutf_test_add(TestCase_p, test_authenticated_crypto_aria_gcm_auto) != 0) goto FuncErrorReturn;
#endif
#ifdef VALTEST_SYM_ALGO_SM4_GCM
        if (sfzutf_test_add(TestCase_p, test_authenticated_crypto_sm4_gcm) != 0) goto FuncErrorReturn;
#endif
#endif
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_sym_auth_crypto.c */
