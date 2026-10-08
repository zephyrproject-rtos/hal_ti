/* valtest_sym_crypto.c
 *
 * Description: VAL Test Suite; Symmetric Crypto functionality
 *              for AES, AES-f8, DES and Triple-DES.
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
#include "testvectors_aes_basic.h"
#if defined(VALTEST_SYM_ALGO_DES) || defined(VALTEST_SYM_ALGO_3DES)
#include "testvectors_des.h"
#endif
#ifdef VALTEST_SYM_ALGO_AES_F8
#include "testvectors_aes_f8.h"
#endif
#ifdef VALTEST_SYM_ALGO_AES_XTS
#include "testvectors_xts_aes.h"
#endif
#ifdef VALTEST_SYM_ALGO_CHACHA20
#include "testvectors_chacha20.h"
#endif
#ifdef VALTEST_SYM_ALGO_SM4
#include "testvectors_sm4_basic.h"
#endif
#ifdef VALTEST_SYM_ALGO_ARIA
#include "testvectors_aria_basic.h"
#endif


typedef struct
{
    int Index;
    ValSymContextPtr_t SymContext_p;
    ValAssetId_t KeyAssetId;
    uint8_t * ptx_p;
    uint8_t * ctx_p;
    uint32_t txt_len;
    uint32_t BlockSize;
    bool fPadding;
    uint8_t PaddingByte;
    uint32_t options;
    int misalign;
} SymCryptTestCtx_t;

#define SYM_CRYPT_TEST_IN_PLACE        0x0001
#define SYM_CRYPT_TEST_MULTIPART       0x0002
#define SYM_CRYPT_TEST_UNALIGNED       0x0004


/*----------------------------------------------------------------------------
 * SetupTestContextAndEnvironment
 *
 * Setup for the "do_SymCryptTest" test.
 */
static int
SetupTestContextAndEnvironment(
        SymCryptTestCtx_t * TestCntxt_p,
        uint32_t Index,
        ValSymAlgo_t Algorithm,
        TestVectors_Mode_t TestMode,
        bool fKeyAsset,
        bool fDecrypt,
        const uint8_t * const Key_p,
        uint32_t KeySize,
        const uint8_t * const Iv_p,
        const uint8_t * const Ptx_p,
        const uint8_t * const Ctx_p,
        const uint32_t TxtLen)
{
    ValSymMode_t Mode = VAL_SYM_MODE_NONE;
    ValPolicyMask_t KeyAssetPolicy = 0;
    ValStatus_t Status;
    uint32_t IvSize = 0;

    memset(TestCntxt_p, 0, sizeof(SymCryptTestCtx_t));

    KeyAssetPolicy = EIP130_ASSET_POLICY_SYM_CIPHERBULK;
    switch (Algorithm)
    {
    case VAL_SYM_ALGO_CIPHER_AES:
    case VAL_SYM_ALGO_CIPHER_ARIA:
        switch (TestMode)
        {
        case TESTVECTORS_MODE_ECB:
            Mode = VAL_SYM_MODE_CIPHER_ECB;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCMCBECB;
            break;
        case TESTVECTORS_MODE_CBC:
            Mode = VAL_SYM_MODE_CIPHER_CBC;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCMCBCBC;
            IvSize = VAL_SYM_ALGO_AES_IV_SIZE;
            break;
        case TESTVECTORS_MODE_CTR:
            Mode = VAL_SYM_MODE_CIPHER_CTR;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCMCBCTR32;
            IvSize = VAL_SYM_ALGO_AES_IV_SIZE;
            TestCntxt_p->fPadding = true;
            TestCntxt_p->PaddingByte = 0xDC;
            break;
        case TESTVECTORS_MODE_ICM:
            Mode = VAL_SYM_MODE_CIPHER_ICM;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCMCBCTR16;
            IvSize = VAL_SYM_ALGO_AES_IV_SIZE;
            TestCntxt_p->fPadding = true;
            TestCntxt_p->PaddingByte = 0xDC;
            break;
#ifdef VALTEST_SYM_ALGO_AES_F8
        case TESTVECTORS_MODE_F8:
            Mode = VAL_SYM_MODE_CIPHER_F8;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCMCBF8;
            IvSize = VAL_SYM_ALGO_AES_IV_SIZE;
            TestCntxt_p->fPadding = true;
            TestCntxt_p->PaddingByte = 0xDC;
            break;
#endif
#ifdef VALTEST_SYM_ALGO_AES_XTS
        case TESTVECTORS_MODE_XTS:
            Mode = VAL_SYM_MODE_CIPHER_XTS;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCMCBXTS;
            IvSize = VAL_SYM_ALGO_AES_IV_SIZE;
            TestCntxt_p->fPadding = true;
            //TestCntxt_p->PaddingByte = 0x00;
            break;
#endif
        default:
            break;
        }
        if (Algorithm == VAL_SYM_ALGO_CIPHER_AES)
        {
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
            TestCntxt_p->BlockSize = VAL_SYM_ALGO_AES_BLOCK_SIZE;
        }
        else
        {
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACARIA;
            TestCntxt_p->BlockSize = VAL_SYM_ALGO_ARIA_BLOCK_SIZE;
        }
        break;
#ifdef VALTEST_SYM_ALGO_DES
    case VAL_SYM_ALGO_CIPHER_DES:
        // Note: No key Asset is allowed
        KeyAssetPolicy = 0;
        switch (TestMode)
        {
        case TESTVECTORS_MODE_ECB:
            Mode = VAL_SYM_MODE_CIPHER_ECB;
            break;
        case TESTVECTORS_MODE_CBC:
            Mode = VAL_SYM_MODE_CIPHER_CBC;
            IvSize = VAL_SYM_ALGO_DES_IV_SIZE;
            break;
        default:
            break;
        }
        TestCntxt_p->BlockSize = VAL_SYM_ALGO_DES_BLOCK_SIZE;
        break;
#endif
#ifdef VALTEST_SYM_ALGO_3DES
    case VAL_SYM_ALGO_CIPHER_TRIPLE_DES:
        switch (TestMode)
        {
        case TESTVECTORS_MODE_ECB:
            Mode = VAL_SYM_MODE_CIPHER_ECB;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACTDES | EIP130_ASSET_POLICY_SCMCBECB;
            break;
        case TESTVECTORS_MODE_CBC:
            Mode = VAL_SYM_MODE_CIPHER_CBC;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACTDES | EIP130_ASSET_POLICY_SCMCBCBC;
            IvSize = VAL_SYM_ALGO_DES_IV_SIZE;
            break;
        default:
            break;
        }
        TestCntxt_p->BlockSize = VAL_SYM_ALGO_DES_BLOCK_SIZE;
        break;
#endif
#ifdef VALTEST_SYM_ALGO_CHACHA20
    case VAL_SYM_ALGO_CIPHER_CHACHA20:
        Mode = VAL_SYM_MODE_CIPHER_CHACHA20_ENC;
        KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACCHACHA20;
        IvSize = VAL_SYM_ALGO_CHACHA20_IV_SIZE;
        TestCntxt_p->BlockSize = VAL_SYM_ALGO_CHACHA20_BLOCK_SIZE;
        TestCntxt_p->fPadding = true;
        //TestCntxt_p->PaddingByte = 0x00;
        break;
#endif
#ifdef VALTEST_SYM_ALGO_SM4
    case VAL_SYM_ALGO_CIPHER_SM4:
        switch (TestMode)
        {
        case TESTVECTORS_MODE_ECB:
            Mode = VAL_SYM_MODE_CIPHER_ECB;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACSM4 | EIP130_ASSET_POLICY_SCMCBECB;
            break;
        case TESTVECTORS_MODE_CBC:
            Mode = VAL_SYM_MODE_CIPHER_CBC;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACSM4 | EIP130_ASSET_POLICY_SCMCBCBC;
            IvSize = VAL_SYM_ALGO_AES_IV_SIZE;
            break;
        case TESTVECTORS_MODE_CTR:
            Mode = VAL_SYM_MODE_CIPHER_CTR;
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCACSM4 | EIP130_ASSET_POLICY_SCMCBCTR32;
            IvSize = VAL_SYM_ALGO_SM4_IV_SIZE;
            TestCntxt_p->fPadding = true;
            TestCntxt_p->PaddingByte = 0xDC;
            break;
        default:
            break;
        }
        TestCntxt_p->BlockSize = VAL_SYM_ALGO_SM4_BLOCK_SIZE;
        break;
#endif
    default:
        break;
    }

    Status = val_SymAlloc(Algorithm, Mode, false, &TestCntxt_p->SymContext_p);
    unsupported_if((Status == VAL_INVALID_ALGORITHM), "");
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    if (fKeyAsset && KeyAssetPolicy)
    {
        if (fDecrypt)
        {
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
        }
        else
        {
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
        }
        if (!val_IsAccessSecure())
        {
            KeyAssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(KeyAssetPolicy, KeySize,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &TestCntxt_p->KeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

#ifdef SFZUTF_USERMODE
        Status = val_AssetLoadPlaintext(TestCntxt_p->KeyAssetId,
                                        Key_p, KeySize);
#else
        {
            uint8_t * KeyCopy_p = (uint8_t *)SFZUTF_MALLOC(KeySize);
            fail_if(KeyCopy_p == NULL, "Allocation ", (int)KeySize);
            memcpy(KeyCopy_p, Key_p, KeySize);

            Status = val_AssetLoadPlaintext(TestCntxt_p->KeyAssetId,
                                            KeyCopy_p, KeySize);

            SFZUTF_FREE(KeyCopy_p);
        }
#endif
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(Key)=", Status);
    }

    Status = val_SymInitKey(TestCntxt_p->SymContext_p,
                            TestCntxt_p->KeyAssetId, Key_p, KeySize);
    fail_if(Status != VAL_SUCCESS, "val_SymInitKey()=", Status);

    if (IvSize)
    {
        Status = val_SymInitIV(TestCntxt_p->SymContext_p, Iv_p, IvSize);
        fail_if(Status != VAL_SUCCESS, "val_SymInitIV()=", Status);
    }

    TestCntxt_p->Index = (int)Index;
    TestCntxt_p->ptx_p = sfzutf_discard_const(Ptx_p);
    TestCntxt_p->ctx_p = sfzutf_discard_const(Ctx_p);
    TestCntxt_p->txt_len = TxtLen;

    return END_TEST_SUCCES;
}


/*----------------------------------------------------------------------------
 * do_SymCryptTest
 *
 * Perform a test with the 'val_SymCipher' API using the data and
 * options from the given "SymCryptTestCtx_t" test context.
 */
static int
do_SymCryptTest(
        SymCryptTestCtx_t * const TestCntxt_p,
        bool fDecrypt)
{
    static uint8_t result_text[VAL_TEST_MAX_BUFLEN];
    static uint8_t input_text[VAL_TEST_MAX_BUFLEN];
    ValSize_t result_len = sizeof(result_text);
    ValStatus_t Status;
    uint8_t * TxtIn_p;
    uint8_t * TxtOut_p;
    uint8_t * Result_p = result_text;
    uint32_t padding = 0;

    if (fDecrypt)
    {
        TxtIn_p = TestCntxt_p->ctx_p;
        TxtOut_p = TestCntxt_p->ptx_p;
    }
    else
    {
        Status = val_SymCipherInitEncrypt(TestCntxt_p->SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymCipherInitEncrypt()=", Status);

        TxtIn_p = TestCntxt_p->ptx_p;
        TxtOut_p = TestCntxt_p->ctx_p;
    }

    if (TestCntxt_p->options & SYM_CRYPT_TEST_IN_PLACE)
    {
        memset(Result_p, 0xDC, result_len);
        memcpy(Result_p, TxtIn_p, TestCntxt_p->txt_len);
        TxtIn_p = Result_p;
    }

    if (TestCntxt_p->options & SYM_CRYPT_TEST_UNALIGNED)
    {
        int offset = 1 + (TestCntxt_p->misalign % 3);

        memset(input_text, 0xDC, sizeof(input_text));
        memcpy(input_text + offset, TxtIn_p, TestCntxt_p->txt_len);
        TxtIn_p = input_text + offset;
        Result_p += 1 + ((offset + 1) % 3);
        result_len -= (ValSize_t)(1 + ((offset + 1) % 3));
        TestCntxt_p->misalign += 1;
    }

    if (TestCntxt_p->txt_len & (TestCntxt_p->BlockSize - 1))
    {
        fail_if(TestCntxt_p->fPadding == false, "Bad length for ECB/CBC ",
                TestCntxt_p->txt_len);

        padding = (0 - TestCntxt_p->txt_len) & (TestCntxt_p->BlockSize - 1);
        if (!(TestCntxt_p->options & SYM_CRYPT_TEST_UNALIGNED))
        {
            memset(input_text, TestCntxt_p->PaddingByte, (TestCntxt_p->txt_len + padding));
            memcpy(input_text, TxtIn_p, TestCntxt_p->txt_len);
            TxtIn_p = input_text;
        }
    }

    if (TestCntxt_p->options & SYM_CRYPT_TEST_MULTIPART)
    {
        ValSize_t src_len = TestCntxt_p->txt_len + padding;
        ValSize_t dst_space = result_len;
        uint8_t * srcpart_p = TxtIn_p;
        uint8_t * dstpart_p = Result_p;

        do
        {
            ValSize_t part_len = MIN(TestCntxt_p->BlockSize, src_len);
            ValSize_t dst_len = dst_space;

            if (src_len == part_len)
            {
#ifdef SFZUTF_USERMODE
                Status = val_SymCipherFinal(TestCntxt_p->SymContext_p,
                                            srcpart_p, part_len,
                                            dstpart_p, &dst_len);
#else
                uint8_t * InCopy_p;
                uint8_t * OutCopy_p;

                InCopy_p = (uint8_t *)SFZUTF_MALLOC(part_len);
                fail_if(InCopy_p == NULL, "Allocation ", (int)part_len);
                OutCopy_p = (uint8_t *)SFZUTF_MALLOC(dst_len);
                fail_if(OutCopy_p == NULL, "Allocation ", (int)dst_len);

                memcpy(InCopy_p, srcpart_p, part_len);
                Status = val_SymCipherFinal(TestCntxt_p->SymContext_p,
                                            InCopy_p, part_len,
                                            OutCopy_p, &dst_len);
                if (val_CheckFunctionResult(Status) == VAL_SUCCESS)
                {
                    memcpy(dstpart_p, OutCopy_p, dst_len);
                }

                SFZUTF_FREE(OutCopy_p);
                SFZUTF_FREE(InCopy_p);
#endif
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymCipherFinal()=", Status);
            }
            else
            {
#ifdef SFZUTF_USERMODE
                Status = val_SymCipherUpdate(TestCntxt_p->SymContext_p,
                                             srcpart_p, part_len,
                                             dstpart_p, &dst_len);
#else
                uint8_t * InCopy_p;
                uint8_t * OutCopy_p;

                InCopy_p = (uint8_t *)SFZUTF_MALLOC(part_len);
                fail_if(InCopy_p == NULL, "Allocation ", (int)part_len);
                OutCopy_p = (uint8_t *)SFZUTF_MALLOC(dst_len);
                fail_if(OutCopy_p == NULL, "Allocation ", (int)dst_len);

                memcpy(InCopy_p, srcpart_p, part_len);
                Status = val_SymCipherUpdate(TestCntxt_p->SymContext_p,
                                             InCopy_p, part_len,
                                             OutCopy_p, &dst_len);
                if (val_CheckFunctionResult(Status) == VAL_SUCCESS)
                {
                    memcpy(dstpart_p, OutCopy_p, dst_len);
                }

                SFZUTF_FREE(OutCopy_p);
                SFZUTF_FREE(InCopy_p);
#endif
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymCipherUpdate()=", Status);
            }

            fail_if(dst_len != TestCntxt_p->BlockSize,
                    "Unexpected partial result length ",
                    (int)dst_len);

            src_len -= part_len;
            dst_space -= dst_len;
            srcpart_p += part_len;
            dstpart_p += part_len;
        } while (src_len > 0);

        /* Let result_len = accumulated result length. */
        result_len -= dst_space;
    }
    else
    {
#ifdef SFZUTF_USERMODE
        Status = val_SymCipherFinal(TestCntxt_p->SymContext_p,
                                    TxtIn_p, TestCntxt_p->txt_len + padding,
                                    Result_p, &result_len);
#else
        uint8_t * InCopy_p;
        uint8_t * OutCopy_p;

        InCopy_p = (uint8_t *)SFZUTF_MALLOC(TestCntxt_p->txt_len + padding);
        fail_if(InCopy_p == NULL, "Allocation ", (int)(TestCntxt_p->txt_len + padding));
        OutCopy_p = (uint8_t *)SFZUTF_MALLOC(result_len);
        fail_if(OutCopy_p == NULL, "Allocation ", (int)result_len);

        memcpy(InCopy_p, TxtIn_p, (TestCntxt_p->txt_len + padding));
        Status = val_SymCipherFinal(TestCntxt_p->SymContext_p,
                                    InCopy_p, (TestCntxt_p->txt_len + padding),
                                    OutCopy_p, &result_len);
        if (val_CheckFunctionResult(Status) == VAL_SUCCESS)
        {
            memcpy(Result_p, OutCopy_p, result_len);
        }

        SFZUTF_FREE(OutCopy_p);
        SFZUTF_FREE(InCopy_p);
#endif
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymCipherFinal()=", Status);
    }
    fail_if(result_len != (ValSize_t)(TestCntxt_p->txt_len + padding),
            "Unexpected result length: ", (int)result_len);
    fail_if(memcmp(Result_p, TxtOut_p, TestCntxt_p->txt_len) != 0,
            "Unexpected output result ", -1);

    if (TestCntxt_p->KeyAssetId != VAL_ASSETID_INVALID)
    {
        Status = val_AssetFree(TestCntxt_p->KeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Key)=", Status);
    }

    return END_TEST_SUCCES;
}


/*----------------------------------------------------------------------------
 * test_sym_crypto_aes
 *
 * Test with AES test vectors. Intended to be called 6 times.
 * Uses encryption if loopcount _i is even.
 * Uses "in-place" operation when loopcount _i is 2, 3 or 5.
 * Uses "multipart" operation when loopcount is 4 or 5.
 */
START_TEST(test_sym_crypto_aes)
{
    SymCryptTestCtx_t TestCntxt;
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    for (Index = 0; ; Index++)
    {
        TestVector_AES_BASIC_t tv_p;

        tv_p = test_vectors_aes_basic_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (SetupTestContextAndEnvironment(&TestCntxt,
                                           Index,
                                           VAL_SYM_ALGO_CIPHER_AES,
                                           tv_p->Mode,
                                           ((_i & 4) != 0),
                                           ((_i & 1) != 0),
                                           tv_p->Key_p,
                                           tv_p->KeyLen,
                                           tv_p->Iv_p,
                                           tv_p->Ptx_p,
                                           tv_p->Ctx_p,
                                           tv_p->PtxLen) == END_TEST_SUCCES)
        {
            if ((_i == 2) || (_i == 3) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_IN_PLACE;
            }

            if ((_i == 4) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_MULTIPART;

            }

            if (do_SymCryptTest(&TestCntxt, ((_i & 1) != 0)) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            if (TestCntxt.SymContext_p != NULL)
            {
                (void)val_SymRelease(TestCntxt.SymContext_p);
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        test_vectors_aes_basic_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


/*----------------------------------------------------------------------------
 * test_sym_crypto_xts_aes
 *
 * Test with AES test vectors. Intended to be called 6 times.
 * Uses encryption if loopcount _i is even.
 * Uses "in-place" operation when loopcount _i is 2 and 3.
 */
#ifdef VALTEST_SYM_ALGO_AES_XTS
START_TEST(test_sym_crypto_xts_aes)
{
    SymCryptTestCtx_t TestCntxt;
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    for (Index = 0; ; Index++)
    {
        TestVector_XTS_AES_t tv_p;

        tv_p = test_vectors_xts_aes_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (SetupTestContextAndEnvironment(&TestCntxt,
                                           Index,
                                           VAL_SYM_ALGO_CIPHER_AES,
                                           TESTVECTORS_MODE_XTS,
                                           ((_i & 4) != 0),
                                           ((_i & 1) != 0),
                                           tv_p->Key_p,
                                           tv_p->KeyLen,
                                           tv_p->Tweak_p,
                                           tv_p->Ptx_p,
                                           tv_p->Ctx_p,
                                           tv_p->PtxLen) == END_TEST_SUCCES)
        {
            if ((_i == 2) || (_i == 3) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_IN_PLACE;
            }

            if (do_SymCryptTest(&TestCntxt, ((_i & 1) != 0)) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            if (TestCntxt.SymContext_p != NULL)
            {
                (void)val_SymRelease(TestCntxt.SymContext_p);
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        test_vectors_xts_aes_release(tv_p);
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


/*----------------------------------------------------------------------------
 * test_sym_crypto_aesf8
 *
 * Test with AES-f8 test vectors. Intended to be called 4 times.
 * Uses encryption if loopcount _i is even.
 * Uses "in-place" operation when loopcount _i is 2, 3 or 5.
 * Uses "multipart" operation when loopcount is 4 or 5.
 */
#ifdef VALTEST_SYM_ALGO_AES_F8
START_TEST(test_sym_crypto_aesf8)
{
    static const uint8_t EmptyIV[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    SymCryptTestCtx_t TestCntxt;
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    for (Index = 0; ; Index++)
    {
        TestVector_AES_f8_t tv_p;

        tv_p = test_vectors_aes_f8_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (SetupTestContextAndEnvironment(&TestCntxt,
                                           Index,
                                           VAL_SYM_ALGO_CIPHER_AES,
                                           TESTVECTORS_MODE_F8,
                                           (_i == 5),
                                           ((_i & 1) != 0),
                                           tv_p->Key_p,
                                           tv_p->KeyLen,
                                           EmptyIV,
                                           tv_p->Ptx_p,
                                           tv_p->Ctx_p,
                                           tv_p->PtxLen) == END_TEST_SUCCES)
        {
            if (val_SymCipherInitF8(TestCntxt.SymContext_p,
                                    tv_p->SaltKey_p,
                                    tv_p->SaltKeyLen,
                                    tv_p->Iv_p,
                                    TestCntxt.BlockSize) == VAL_SUCCESS)
            {
                if ((_i == 2) || (_i == 3) || (_i == 5))
                {
                    TestCntxt.options |= SYM_CRYPT_TEST_IN_PLACE;
                }

                if ((_i == 4) || (_i == 5))
                {
                    TestCntxt.options |= SYM_CRYPT_TEST_MULTIPART;
                }

                if (do_SymCryptTest(&TestCntxt, ((_i & 1) != 0))== END_TEST_SUCCES)
                {
                    Success++;
                }
                else
                {
                    LOG_CRIT("Processed vector %d\n", Index);
                    Failed++;
                }
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            if (TestCntxt.SymContext_p != NULL)
            {
                (void)val_SymRelease(TestCntxt.SymContext_p);
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        test_vectors_aes_f8_release(tv_p);
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


/*----------------------------------------------------------------------------
 * test_sym_crypto_des_3des
 *
 * Test with DES and TRIPLE_DES test vectors. Intended to be called 6 times.
 * Uses encryption if loopcount _i is even.
 * Uses "in-place" operation when loopcount _i is 2, 3 or 5.
 * Uses "multipart" operation when loopcount is 4 or 5.
 */
#if defined(VALTEST_SYM_ALGO_DES) || defined(VALTEST_SYM_ALGO_3DES)
START_TEST(test_sym_crypto_des_3des)
{
    SymCryptTestCtx_t TestCntxt;
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    for (Index = 0; ; Index++)
    {
        ValSymAlgo_t KeyType = VAL_SYM_ALGO_CIPHER_DES;
        TestVector_DES_t tv_p;

        tv_p = test_vectors_des_get(Index);
        if (tv_p == NULL)
        {
            break;
        }
        if (tv_p->KeyLen > 8)
        {
            KeyType = VAL_SYM_ALGO_CIPHER_TRIPLE_DES;
        }
        else if (_i == 5)
        {
            goto skip_des_vector;
        }

        if (SetupTestContextAndEnvironment(&TestCntxt,
                                           Index,
                                           KeyType,
                                           tv_p->Mode,
                                           (_i == 5),
                                           ((_i & 1) != 0),
                                           tv_p->Key_p,
                                           tv_p->KeyLen,
                                           tv_p->Iv_p,
                                           tv_p->Ptx_p,
                                           tv_p->Ctx_p,
                                           tv_p->PtxLen) == END_TEST_SUCCES)
        {
            if ((_i == 2) || (_i == 3) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_IN_PLACE;
            }

            if ((_i == 4) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_MULTIPART;
            }

            if (do_SymCryptTest(&TestCntxt, ((_i & 1) != 0)) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            if (TestCntxt.SymContext_p != NULL)
            {
                (void)val_SymRelease(TestCntxt.SymContext_p);
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

skip_des_vector:
        test_vectors_des_release(tv_p);
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


#ifdef VALTEST_SYM_ALGO_CHACHA20
/*----------------------------------------------------------------------------
 * valtest_IsChaCha20Supported
 *
 * This function checks if the ChaCha20 is supported or not.
 */
bool
valtest_IsChaCha20Supported(void)
{
    static uint8_t gl_ChaCha20Supported = 0;
    ValSymContextPtr_t SymContext_p = NULL;
    TestVector_ChaCha20_t tv_p;
    uint8_t * Data_p;
    ValStatus_t Status;
    ValSize_t result_len;
    uint8_t IV[VAL_SYM_ALGO_CHACHA20_IV_SIZE];

    if (gl_ChaCha20Supported == 0)
    {
        tv_p = test_vectors_chacha20_get(0U);
        if (tv_p == NULL)
        {
           Status = -1;
        }
        else
        {
            Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_CHACHA20,
                                  VAL_SYM_MODE_CIPHER_CHACHA20_ENC,
                                  false, &SymContext_p);
            if (Status >= VAL_SUCCESS)
            {
                Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID,
                                        tv_p->Key_p, tv_p->KeyLen);
                if (Status >= VAL_SUCCESS)
                {
                    memset(IV, 0, sizeof(IV));
                    memcpy(IV, tv_p->Counter_p, tv_p->CounterLen);
                    memcpy(&IV[tv_p->CounterLen], tv_p->Nonce_p, tv_p->NonceLen);

                    Status = val_SymInitIV(SymContext_p, IV, sizeof(IV));
                }
                if (Status >= VAL_SUCCESS)
                {
                    Data_p = (uint8_t *)SFZUTF_MALLOC(tv_p->DataLen);
                    if (Data_p == NULL)
                    {
                        Status = -1;
                    }
                    else
                    {
                        memcpy(Data_p, tv_p->PlainData_p, tv_p->DataLen);

                        result_len = tv_p->DataLen;
                        Status = val_SymCipherFinal(SymContext_p,
                                                    Data_p, tv_p->DataLen,
                                                    Data_p, &result_len);
                        SFZUTF_FREE(Data_p);
                    }
                }

                (void)val_SymRelease(SymContext_p);
            }
        }

        if (Status < VAL_SUCCESS)
        {
            gl_ChaCha20Supported = 0x5A;
        }
        else
        {
            gl_ChaCha20Supported = 0xA5;
        }
    }
    return (gl_ChaCha20Supported == 0xA5);
}


/*----------------------------------------------------------------------------
 * test_sym_crypto_chacha20
 *
 * Test with ChaCha20 test vectors. Intended to be called 6 times.
 * Uses encryption if loopcount _i is even.
 * Uses "in-place" operation when loopcount _i is 2 and 3.
 */
START_TEST(test_sym_crypto_chacha20)
{
    SymCryptTestCtx_t TestCntxt;
    uint8_t IV[VAL_SYM_ALGO_CHACHA20_IV_SIZE];
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    unsupported_if(!valtest_IsChaCha20Supported(), "");

    for (Index = 0; ; Index++)
    {
        TestVector_ChaCha20_t tv_p;

        tv_p = test_vectors_chacha20_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        memset(IV, 0, sizeof(IV));
        memcpy(IV, tv_p->Counter_p, tv_p->CounterLen);
        memcpy(&IV[tv_p->CounterLen], tv_p->Nonce_p, tv_p->NonceLen);

        if (SetupTestContextAndEnvironment(&TestCntxt,
                                           Index,
                                           VAL_SYM_ALGO_CIPHER_CHACHA20,
                                           0,
                                           ((_i & 4) != 0),
                                           ((_i & 1) != 0),
                                           tv_p->Key_p,
                                           tv_p->KeyLen,
                                           IV,
                                           tv_p->PlainData_p,
                                           tv_p->CipherData_p,
                                           tv_p->DataLen) == END_TEST_SUCCES)
        {
            if (val_SymCipherInitChaCha20(TestCntxt.SymContext_p,
                                          tv_p->NonceLen) == VAL_SUCCESS)
            {
                if ((_i == 2) || (_i == 3) || (_i == 5))
                {
                    TestCntxt.options |= SYM_CRYPT_TEST_IN_PLACE;
                }

                if (do_SymCryptTest(&TestCntxt, ((_i & 1) != 0)) == END_TEST_SUCCES)
                {
                    Success++;
                }
                else
                {
                    LOG_CRIT("Processed vector %d\n", Index);
                    Failed++;
                }
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            if (TestCntxt.SymContext_p != NULL)
            {
                (void)val_SymRelease(TestCntxt.SymContext_p);
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        test_vectors_chacha20_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


/*----------------------------------------------------------------------------
 * test_sym_crypto_chacha20_keygen
 *
 * Test the ChaCha20 key generation.
 */
START_TEST(test_sym_crypto_chacha20_keygen)
{
    static const uint8_t Key[] =
    {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
        0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F
    };
    static const uint8_t Nonce[] =
    {
        0x07, 0x00, 0x00, 0x00, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47
    };
    static const uint8_t Result[] =
    {
        0x7B, 0xAC, 0x2B, 0x25, 0x2D, 0xB4, 0x47, 0xAF, 0x09, 0xB6, 0x7A, 0x55, 0xA4, 0xE9, 0x55, 0x84,
        0x0A, 0xE1, 0xD6, 0x73, 0x10, 0x75, 0xD9, 0xEB, 0x2A, 0x93, 0x75, 0x78, 0x3E, 0xD5, 0x53, 0xFF
    };
    SymCryptTestCtx_t TestCntxt;
    uint8_t IV[VAL_SYM_ALGO_CHACHA20_IV_SIZE];
    uint8_t Output[(256/8)];
    ValSize_t ResultSize = (256/8);
    ValStatus_t Status;

    unsupported_if(!valtest_IsChaCha20Supported(), "");

    memset(IV, 0, sizeof(IV));
    memcpy(&IV[4], Nonce, sizeof(Nonce));
    memset(Output, 0, sizeof(Output));

    fail_if(SetupTestContextAndEnvironment(&TestCntxt,
                                           0,
                                           VAL_SYM_ALGO_CIPHER_CHACHA20,
                                           0,
                                           false,
                                           ((_i & 1) != 0),
                                           Key,
                                           sizeof(Key),
                                           IV,
                                           NULL,
                                           Output,
                                           0) != END_TEST_SUCCES,
            "Context setup", END_TEST_FAIL);

    if (_i)
    {
        fail_if(val_SymCipherInitEncrypt(TestCntxt.SymContext_p) != VAL_SUCCESS,
                "val_SymCipherInitEncrypt()=", VAL_BAD_ARGUMENT);
    }

#ifdef SFZUTF_USERMODE
    Status = val_SymCipherFinal(TestCntxt.SymContext_p,
                                NULL, 0,
                                Output, &ResultSize);
#else
    {
        uint8_t * Output_p = (uint8_t *)SFZUTF_MALLOC(ResultSize);
        fail_if(Output_p == NULL, "Allocation ", (int)ResultSize);

        Status = val_SymCipherFinal(TestCntxt.SymContext_p,
                                    NULL, 0,
                                    Output_p, &ResultSize);
        if (val_CheckFunctionResult(Status) == VAL_SUCCESS)
        {
            memcpy(Output, Output_p, ResultSize);
        }

        SFZUTF_FREE(Output_p);
    }
#endif

    if (TestCntxt.SymContext_p != NULL)
    {
        (void)val_SymRelease(TestCntxt.SymContext_p);
    }

    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymCipherFinal()=", Status);
    fail_if(ResultSize != (ValSize_t)(256/8),
            "Unexpected result length: ", (int)ResultSize);
    fail_if(memcmp(Output, Result, ResultSize) != 0,
            "Unexpected output result ", -1);
}
END_TEST
#endif


#ifdef VALTEST_SYM_ALGO_SM4
/*----------------------------------------------------------------------------
 * valtest_IsSM4Supported
 *
 * This function checks if the SM4 is supported or not.
 */
bool
valtest_IsSM4Supported(void)
{
    static uint8_t gl_SM4Supported = 0;
    ValSymContextPtr_t SymContext_p = NULL;
    TestVector_SM4_BASIC_t tv_p;
    uint8_t * Data_p;
    ValStatus_t Status;
    ValSize_t result_len;

    if (gl_SM4Supported != 0)
    {
        return (gl_SM4Supported == 0xA5);
    }

    tv_p = test_vectors_sm4_basic_get(0U);
    if (tv_p == NULL)
    {
        gl_SM4Supported = 0x5A;
        return false;
    }

    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_SM4,
                          VAL_SYM_MODE_CIPHER_ECB,
                          false, &SymContext_p);
    if (Status != VAL_SUCCESS)
    {
        gl_SM4Supported = 0x5A;
        return false;
    }

    Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID,
                            tv_p->Key_p, tv_p->KeyLen);
    if (Status != VAL_SUCCESS)
    {
        (void)val_SymRelease(SymContext_p);
        gl_SM4Supported = 0x5A;
        return false;
    }

    Data_p = (uint8_t *)SFZUTF_MALLOC(tv_p->PtxLen);
    if (Data_p == NULL)
    {
        (void)val_SymRelease(SymContext_p);
        gl_SM4Supported = 0x5A;
        return false;
    }
    memcpy(Data_p, tv_p->Ptx_p, tv_p->PtxLen);

    result_len = tv_p->PtxLen;
    Status = val_SymCipherFinal(SymContext_p,
                                Data_p, tv_p->PtxLen,
                                Data_p, &result_len);
    SFZUTF_FREE(Data_p);
    (void)val_SymRelease(SymContext_p);
    if (val_CheckFunctionResult(Status) != VAL_SUCCESS)
    {
        gl_SM4Supported = 0x5A;
    }
    else
    {
        gl_SM4Supported = 0xA5;
    }
    return (gl_SM4Supported == 0xA5);
}


/*----------------------------------------------------------------------------
 * test_sym_crypto_sm4
 *
 * Test with SM4 test vectors. Intended to be called 6 times.
 * Uses encryption if loopcount _i is even.
 * Uses "in-place" operation when loopcount _i is 2, 3 or 5.
 * Uses "multipart" operation when loopcount is 4 or 5.
 */
START_TEST(test_sym_crypto_sm4)
{
    SymCryptTestCtx_t TestCntxt;
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    unsupported_if(!valtest_IsSM4Supported(), "");

    for (Index = 0; ; Index++)
    {
        TestVector_SM4_BASIC_t tv_p;

        tv_p = test_vectors_sm4_basic_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (SetupTestContextAndEnvironment(&TestCntxt,
                                           Index,
                                           VAL_SYM_ALGO_CIPHER_SM4,
                                           tv_p->Mode,
                                           ((_i & 4) != 0),
                                           ((_i & 1) != 0),
                                           tv_p->Key_p,
                                           tv_p->KeyLen,
                                           tv_p->Iv_p,
                                           tv_p->Ptx_p,
                                           tv_p->Ctx_p,
                                           tv_p->PtxLen) == END_TEST_SUCCES)
        {
            if ((_i == 2) || (_i == 3) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_IN_PLACE;
            }

            if ((_i == 4) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_MULTIPART;

            }

            if (do_SymCryptTest(&TestCntxt, ((_i & 1) != 0)) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            if (TestCntxt.SymContext_p != NULL)
            {
                (void)val_SymRelease(TestCntxt.SymContext_p);
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        test_vectors_sm4_basic_release(tv_p);
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


#ifdef VALTEST_SYM_ALGO_ARIA
/*----------------------------------------------------------------------------
 * valtest_IsARIASupported
 *
 * This function checks if the ARIA is supported or not.
 */
bool
valtest_IsARIASupported(void)
{
    static uint8_t gl_ARIASupported = 0;
    ValSymContextPtr_t SymContext_p = NULL;
    TestVector_ARIA_BASIC_t tv_p;
    uint8_t * Data_p;
    ValStatus_t Status;
    ValSize_t result_len;

    if (gl_ARIASupported != 0)
    {
        return (gl_ARIASupported == 0xA5);
    }

    tv_p = test_vectors_aria_basic_get(0U);
    if (tv_p == NULL)
    {
        gl_ARIASupported = 0x5A;
        return false;
    }

    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_ARIA, VAL_SYM_MODE_CIPHER_ECB,
                          false, &SymContext_p);
    if (Status != VAL_SUCCESS)
    {
        gl_ARIASupported = 0x5A;
        return false;
    }

    Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID,
                            tv_p->Key_p, tv_p->KeyLen);
    if (Status != VAL_SUCCESS)
    {
        (void)val_SymRelease(SymContext_p);
        gl_ARIASupported = 0x5A;
        return false;
    }

    Data_p = (uint8_t *)SFZUTF_MALLOC(tv_p->PtxLen);
    if (Data_p == NULL)
    {
        (void)val_SymRelease(SymContext_p);
        gl_ARIASupported = 0x5A;
        return false;
    }
    memcpy(Data_p, tv_p->Ptx_p, tv_p->PtxLen);

    result_len = tv_p->PtxLen;
    Status = val_SymCipherFinal(SymContext_p,
                                Data_p, tv_p->PtxLen,
                                Data_p, &result_len);
    SFZUTF_FREE(Data_p);
    (void)val_SymRelease(SymContext_p);
    if (val_CheckFunctionResult(Status) != VAL_SUCCESS)
    {
        gl_ARIASupported = 0x5A;
    }
    else
    {
        gl_ARIASupported = 0xA5;
    }
    return (gl_ARIASupported == 0xA5);
}


/*----------------------------------------------------------------------------
 * test_sym_crypto_aria
 *
 * Test with ARIA test vectors. Intended to be called 6 times.
 * Uses encryption if loopcount _i is even.
 * Uses "in-place" operation when loopcount _i is 2, 3 or 5.
 * Uses "multipart" operation when loopcount is 4 or 5.
 */
START_TEST(test_sym_crypto_aria)
{
    SymCryptTestCtx_t TestCntxt;
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    unsupported_if(!valtest_IsARIASupported(), "");

    for (Index = 0; ; Index++)
    {
        TestVector_ARIA_BASIC_t tv_p;

        tv_p = test_vectors_aria_basic_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (SetupTestContextAndEnvironment(&TestCntxt,
                                           Index,
                                           VAL_SYM_ALGO_CIPHER_ARIA,
                                           tv_p->Mode,
                                           ((_i & 4) != 0),
                                           ((_i & 1) != 0),
                                           tv_p->Key_p,
                                           tv_p->KeyLen,
                                           tv_p->Iv_p,
                                           tv_p->Ptx_p,
                                           tv_p->Ctx_p,
                                           tv_p->PtxLen) == END_TEST_SUCCES)
        {
            if ((_i == 2) || (_i == 3) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_IN_PLACE;
            }

            if ((_i == 4) || (_i == 5))
            {
                TestCntxt.options |= SYM_CRYPT_TEST_MULTIPART;

            }

            if (do_SymCryptTest(&TestCntxt, ((_i & 1) != 0)) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            if (TestCntxt.SymContext_p != NULL)
            {
                (void)val_SymRelease(TestCntxt.SymContext_p);
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        test_vectors_aria_basic_release(tv_p);
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


/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_unaligned
 *
 * Test with unaligned in and output buffers using the AES test vectors.
 * Intended to be called 2 times.
 * Uses encryption if loopcount _i is even.
 * Uses "multipart" operation when loopcount is 1.
 */
#ifdef SFZUTF_USERMODE
START_TEST(test_sym_crypto_aes_unaligned)
{
    SymCryptTestCtx_t TestCntxt;
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    for (Index = 0; ; Index++)
    {
        TestVector_AES_BASIC_t tv_p;

        tv_p = test_vectors_aes_basic_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (SetupTestContextAndEnvironment(&TestCntxt,
                                           Index,
                                           VAL_SYM_ALGO_CIPHER_AES,
                                           tv_p->Mode,
                                           (_i == 5),
                                           ((_i & 1) != 0),
                                           tv_p->Key_p,
                                           tv_p->KeyLen,
                                           tv_p->Iv_p,
                                           tv_p->Ptx_p,
                                           tv_p->Ctx_p,
                                           tv_p->PtxLen) == END_TEST_SUCCES)
        {
            TestCntxt.options |= SYM_CRYPT_TEST_UNALIGNED;
            if (_i == 1)
            {
                TestCntxt.options |= SYM_CRYPT_TEST_MULTIPART;
            }

            if (do_SymCryptTest(&TestCntxt, ((_i & 1)  != 0)) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }

            if (TestCntxt.SymContext_p != NULL)
            {
                (void)val_SymRelease(TestCntxt.SymContext_p);
            }
        }
        else
        {
            LOG_CRIT("Processed vector %d\n", Index);
            Failed++;
        }

        test_vectors_aes_basic_release(tv_p);
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


/*----------------------------------------------------------------------------
 * test_sym_crypto_invalid_algorithm
 */
START_TEST(test_sym_crypto_invalid_algorithm)
{
    ValSymContextPtr_t SymContext_p;
    ValStatus_t Status;
    uint8_t inData[128];
    uint8_t outData[128];
    ValSize_t outDataSize;

    Status = val_SymAlloc(VAL_SYM_ALGO_MAC_HMAC_SHA256,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    outDataSize = sizeof(outData);
    Status = val_SymCipherUpdate(SymContext_p,
                                 inData,
                                 sizeof(inData),
                                 outData,
                                 &outDataSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ALGORITHM, "val_SymCipherUpdate()=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
}
END_TEST


/*----------------------------------------------------------------------------
 * test_sym_crypto_buffer_too_small
 */
START_TEST(test_sym_crypto_buffer_too_small)
{
    ValSymContextPtr_t SymContext_p = NULL;
    ValStatus_t Status;
    uint8_t inData[128];
    uint8_t outData[128];
    ValSize_t outDataSize;

    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_AES,
                          VAL_SYM_MODE_CIPHER_ECB,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    outDataSize = sizeof(outData) -5;
    Status = val_SymCipherUpdate(SymContext_p,
                                 inData,
                                 sizeof(inData),
                                 outData,
                                 &outDataSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_SymCipherUpdate()=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
}
END_TEST

/*----------------------------------------------------------------------------
 * test_sym_crypto_common
 */
START_TEST(test_sym_crypto_common)
{
    uint8_t Buffer[(128/8)];
    ValSymContextPtr_t SymContext_p;
    ValAssetId_t AssetId = 0x204;
    ValStatus_t Status;

    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_AES,
                          VAL_SYM_MODE_CIPHER_ECB,
                          false,
                          NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_SymAlloc()=", Status);

    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER,
                          VAL_SYM_MODE_CIPHER_ECB,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_INVALID_ALGORITHM, "val_SymAlloc()=", Status);

    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_AES,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_INVALID_MODE, "val_SymAlloc()=", Status);

#ifdef VALTEST_SYM_ALGO_3DES
    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_TRIPLE_DES,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_INVALID_MODE, "val_SymAlloc()=", Status);
#endif

    // AES-CBC (General cases)
    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_AES,
                          VAL_SYM_MODE_CIPHER_CBC,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID, NULL, 0);
    fail_if(Status != VAL_INVALID_KEYSIZE, "val_SymInitKey()=", Status);

    Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID, NULL, (128/8));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitKey()=", Status);

    Status = val_SymInitIV(SymContext_p, Buffer, 0);
    fail_if(Status != VAL_INVALID_LENGTH, "val_SymInitIV()=", Status);

    Status = val_SymInitIV(SymContext_p, NULL, (128/8));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitIV(BadArgument2)=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);

    // AES-ECB (Specific case)
    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_AES,
                          VAL_SYM_MODE_CIPHER_ECB,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymInitIV(SymContext_p, Buffer, (128/8));
    fail_if(Status != VAL_UNSUPPORTED, "val_SymInitIV()=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);

#ifdef VALTEST_SYM_ALGO_3DES
    // 3DES-CBC (General cases)
    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_TRIPLE_DES,
                          VAL_SYM_MODE_CIPHER_CBC,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID, NULL, 0);
    fail_if(Status != VAL_INVALID_KEYSIZE, "val_SymInitKey()=", Status);

    Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID, NULL, (3*(64/8)));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitKey()=", Status);

    Status = val_SymInitIV(SymContext_p, Buffer, 0);
    fail_if(Status != VAL_INVALID_LENGTH, "val_SymInitIV()=", Status);

    Status = val_SymInitIV(SymContext_p, NULL, (64/8));
    fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitIV(BadArgument2)=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);

    // 3DES-ECB (Specific case)
    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_TRIPLE_DES,
                          VAL_SYM_MODE_CIPHER_ECB,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymInitIV(SymContext_p, Buffer, (64/8));
    fail_if(Status != VAL_UNSUPPORTED, "val_SymInitIV()=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
#endif /* VALTEST_SYM_ALGO_3DES */

#ifdef VALTEST_SYM_ALGO_DES
    // DES-ECB
    Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_DES,
                          VAL_SYM_MODE_CIPHER_ECB,
                          false,
                          &SymContext_p);
    if (Status == VAL_SUCCESS)
    {
        Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID, NULL, 0);
        fail_if(Status != VAL_INVALID_KEYSIZE, "val_SymInitKey()=", Status);

        Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID, NULL, (64/8));
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitKey()=", Status);

        Status = val_SymInitIV(SymContext_p, Buffer, (64/8));
        fail_if(Status != VAL_UNSUPPORTED, "val_SymInitIV()=", Status);

        Status = val_SymRelease(SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);

        // DES-CBC
        Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_DES,
                              VAL_SYM_MODE_CIPHER_CBC,
                              false,
                              &SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

        Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID, NULL, 0);
        fail_if(Status != VAL_INVALID_KEYSIZE, "val_SymInitKey()=", Status);

        Status = val_SymInitKey(SymContext_p, VAL_ASSETID_INVALID, NULL, (64/8));
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitKey()=", Status);

        Status = val_SymInitKey(SymContext_p, AssetId, Buffer, (64/8));
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitKey()=", Status);

        Status = val_SymInitIV(SymContext_p, Buffer, 0);
        fail_if(Status != VAL_INVALID_LENGTH, "val_SymInitIV()=", Status);

        Status = val_SymInitIV(SymContext_p, NULL, (64/8));
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitIV(BadArgument2)=", Status);

        Status = val_SymRelease(SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
    }
    else
    {
        fail_if(Status != VAL_UNSUPPORTED, "val_SymAlloc(DES)=", Status);
    }
#endif /* VALTEST_SYM_ALGO_DES */

    if (valtest_StrictArgsCheck())
    {
        ValSize_t OutputSize = 10;

        Status = val_SymRelease(NULL);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymRelease(BadArgument1)=", Status);

        Status = val_SymInitKey(NULL, AssetId, Buffer, (128/8));
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitKey(BadArgument1)=", Status);

        Status = val_SymInitIV(NULL, Buffer, (128/8));
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymInitIV(BadArgument1)=", Status);

        Status = val_SymCipherInitEncrypt(NULL);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymCipherInitEncrypt(BadArgument1)=", Status);

        Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_AES,
                              VAL_SYM_MODE_CIPHER_CBC,
                              false,
                              &SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

        Status = val_SymCipherUpdate(NULL, Buffer, (128/8), Buffer, &OutputSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymCipherUpdate(BadArgument1)=", Status);

        Status = val_SymCipherUpdate(SymContext_p, NULL, (128/8), Buffer, &OutputSize );
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymCipherUpdate(BadArgument2)=", Status);

        Status = val_SymCipherUpdate(SymContext_p, Buffer, 0, Buffer, &OutputSize );
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymCipherUpdate(BadArgument3)=", Status);

        Status = val_SymCipherUpdate(SymContext_p, Buffer, (128/8), NULL, &OutputSize );
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymCipherUpdate(BadArgument4)=", Status);

        Status = val_SymCipherUpdate(SymContext_p, Buffer, (128/8), Buffer, NULL);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymCipherUpdate(BadArgument5)=", Status);

        Status = val_SymCipherFinal(NULL, Buffer, (128/8), Buffer, &OutputSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymCipherUpdate(BadArgument1)=", Status);

        Status = val_SymCipherFinal(SymContext_p, NULL, (128/8), Buffer, &OutputSize);
        fail_if(Status != VAL_BAD_ARGUMENT, "val_SymCipherUpdate(BadArgument2)=", Status);

        Status = val_SymRelease(SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
    }
}
END_TEST


/*----------------------------------------------------------------------------
 * suite_add_test_SymCrypto
 */
int
suite_add_test_SymCrypto(
    struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SymCrypto_Cipher_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_sym_crypto_common) != 0) goto FuncErrorReturn;

        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes, 6) != 0) goto FuncErrorReturn;
#ifdef VALTEST_SYM_ALGO_AES_XTS
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_xts_aes, 6) != 0) goto FuncErrorReturn;
#endif
#ifdef VALTEST_SYM_ALGO_AES_F8
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aesf8, 4) != 0) goto FuncErrorReturn;
#endif
#if defined(VALTEST_SYM_ALGO_DES) || defined(VALTEST_SYM_ALGO_3DES)
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_des_3des, 6) != 0) goto FuncErrorReturn;
#endif
#ifdef VALTEST_SYM_ALGO_CHACHA20
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_chacha20, 6) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_chacha20_keygen, 2) != 0) goto FuncErrorReturn;
#endif
#ifdef VALTEST_SYM_ALGO_SM4
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_sm4, 6) != 0) goto FuncErrorReturn;
#endif
#ifdef VALTEST_SYM_ALGO_ARIA
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aria, 6) != 0) goto FuncErrorReturn;
#endif

#ifdef SFZUTF_USERMODE
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes_unaligned, 2) != 0) goto FuncErrorReturn;
#endif
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_invalid_algorithm) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_buffer_too_small) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_sym_crypto.c */
