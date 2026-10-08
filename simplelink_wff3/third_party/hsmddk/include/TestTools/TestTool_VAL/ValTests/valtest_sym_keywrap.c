/* valtest_sym_keywrap.c
 *
 * Description: VAL Test Suite, AES-WRAP, SM4-WRAP
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
#include "testvectors_aes_wrap.h"
#ifdef VALTEST_SYM_ALGO_SM4
#include "testvectors_sm4_wrap.h"
#endif

/*----------------------------------------------------------------------------
 * do_AesKeyWrapUnwrap
 */
static int
do_KeyWrapUnwrap(
    TestVector_AES_WRAP_t tv_p,
    bool fWrap,
    bool fKeyAsset,
    uint8_t algorithm)
{
    ValStatus_t Status;
    ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;
    const uint8_t *TxtOut_p;
    uint8_t *TxtIn_p;
    uint8_t *Result_p;
    ValSize_t TxtInLen;
    ValSize_t ExpectedLen;
    ValSize_t ResultLen = (ValSize_t)(8+(((tv_p->PlainTxtLen + 7) & 0x0FFFFFF8) * 8));

    Result_p = (uint8_t *)SFZUTF_MALLOC(ResultLen);
    fail_if(Result_p == NULL, "Allocation ", (int)ResultLen);
    memset(Result_p, 0, ResultLen);

    if (fKeyAsset)
    {
        ValPolicyMask_t AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP | EIP130_ASSET_POLICY_SCAWKEY;
        if (fWrap)
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
        }
        else
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
        }
        if (algorithm == VAL_SYM_ALGO_CIPHER_AES)
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SCACAES;
        }
        else
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SCACSM4;
        }
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, (ValSize_t)tv_p->KeyLen,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &KeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

#ifdef SFZUTF_USERMODE
        Status = val_AssetLoadPlaintext(KeyAssetId,
                                        tv_p->KEK_p, (ValSize_t)tv_p->KeyLen);

#else
        {
            uint8_t *KeyCopy_p = (uint8_t *)SFZUTF_MALLOC(tv_p->KeyLen);
            fail_if(KeyCopy_p == NULL, "Allocation ", (int)tv_p->KeyLen);
            memcpy(KeyCopy_p, tv_p->KEK_p, tv_p->KeyLen);

            Status = val_AssetLoadPlaintext(KeyAssetId,
                                            KeyCopy_p, (ValSize_t)tv_p->KeyLen);

            SFZUTF_FREE(KeyCopy_p);
        }
#endif
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(Key)=", Status);
    }

    if (fWrap)
    {
        TxtInLen = (ValSize_t)tv_p->PlainTxtLen;
        TxtOut_p = tv_p->WrappedTxt_p;
        ExpectedLen = (ValSize_t)tv_p->WrappedTxtLen;

#ifdef SFZUTF_USERMODE
        TxtIn_p = (uint8_t *)sfzutf_discard_const(tv_p->PlainTxt_p);
#else
        TxtIn_p = (uint8_t *)SFZUTF_MALLOC(TxtInLen);
        fail_if(TxtIn_p == NULL, "Allocation ", (int)TxtInLen);
        memcpy(TxtIn_p, tv_p->PlainTxt_p, TxtInLen);
#endif

        if (fKeyAsset)
        {
            Status = val_SymKeyWrap(KeyAssetId,
                                    NULL,
                                    (ValSize_t)tv_p->KeyLen,
                                    (ValOctetsIn_t *)TxtIn_p,
                                    TxtInLen,
                                    (ValOctetsOut_t *)Result_p,
                                    &ResultLen,
                                    algorithm);
        }
        else
        {
            Status = val_SymKeyWrap(VAL_ASSETID_INVALID,
                                    (ValOctetsIn_Optional_t *)tv_p->KEK_p,
                                    (ValSize_t)tv_p->KeyLen,
                                    (ValOctetsIn_t *)TxtIn_p,
                                    TxtInLen,
                                    (ValOctetsOut_t *)Result_p,
                                    &ResultLen,
                                    algorithm);
        }
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymAesKeyWrap()=", Status);
    }
    else
    {
        TxtInLen = (ValSize_t)tv_p->WrappedTxtLen;
        TxtOut_p = tv_p->PlainTxt_p;
        ExpectedLen = (ValSize_t)tv_p->PlainTxtLen;

#ifdef SFZUTF_USERMODE
        TxtIn_p = (uint8_t *)sfzutf_discard_const(tv_p->WrappedTxt_p);
#else
        TxtIn_p = (uint8_t *)SFZUTF_MALLOC(TxtInLen);
        fail_if(TxtIn_p == NULL, "Allocation ", (int)TxtInLen);
        memcpy(TxtIn_p, tv_p->WrappedTxt_p, TxtInLen);
#endif

        if (fKeyAsset)
        {
            Status = val_SymKeyUnwrap(KeyAssetId,
                                      NULL,
                                      (ValSize_t)tv_p->KeyLen,
                                      (ValOctetsIn_t *)TxtIn_p,
                                      TxtInLen,
                                      (ValOctetsOut_t *)Result_p,
                                      &ResultLen,
                                      algorithm);
            fail_if(val_CheckFunctionResult(Status) != VAL_ACCESS_ERROR, "val_SymAesKeyUnwrap()=", Status);
        }
        else
        {
            Status = val_SymKeyUnwrap(VAL_ASSETID_INVALID,
                                      (ValOctetsIn_Optional_t *)tv_p->KEK_p,
                                      (ValSize_t)tv_p->KeyLen,
                                      (ValOctetsIn_t *)TxtIn_p,
                                      TxtInLen,
                                      (ValOctetsOut_t *)Result_p,
                                      &ResultLen,
                                      algorithm);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymAesKeyUnwrap()=", Status);
        }
    }

#ifndef SFZUTF_USERMODE
    SFZUTF_FREE(TxtIn_p);
#endif

    if (val_CheckFunctionResult(Status) == VAL_SUCCESS)
    {
        fail_if(ResultLen != ExpectedLen, "Mismatch", (int)ResultLen);
        fail_if(memcmp(TxtOut_p, Result_p, ResultLen) != 0,  "Mismatch", -1);
    }

    if (KeyAssetId != VAL_ASSETID_INVALID)
    {
        Status = val_AssetFree(KeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Key)=", Status);
    }

    SFZUTF_FREE(Result_p);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * test_aes_wrap_unwrap
 *
 * Test with the AES-WRAP test vectors. Intended to be run twice, to cover
 * encryption/wrap (_1 = 0) and decryption/unwrap (_i = 1).
 */
START_TEST(test_aes_wrap_unwrap)
{
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    for (Index = 0U; ; Index++)
    {
        TestVector_AES_WRAP_t tv_p;

        tv_p = test_vectors_aes_wrap_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->fKWP)
        {
            if (do_KeyWrapUnwrap(tv_p, ((_i & 1) == 0), ((_i & 2) != 0), VAL_SYM_ALGO_CIPHER_AES) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }
        }

        test_vectors_aes_wrap_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

#ifdef VALTEST_SYM_ALGO_SM4
START_TEST(test_sm4_wrap_unwrap)
{
    uint32_t Index;
    int Success = 0;
    int Failed = 0;

    for (Index = 0U; ; Index++)
    {
        TestVector_SM4_WRAP_t tv_p;

        tv_p = test_vectors_sm4_wrap_get(Index);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->fKWP)
        {
            if (do_KeyWrapUnwrap((TestVector_AES_WRAP_t)tv_p, ((_i & 1) == 0), ((_i & 2) != 0), VAL_SYM_ALGO_CIPHER_SM4) == END_TEST_SUCCES)
            {
                Success++;
            }
            else
            {
                LOG_CRIT("Processed vector %d\n", Index);
                Failed++;
            }
        }

        test_vectors_sm4_wrap_release(tv_p);
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

int
suite_add_test_SymKeyWrap(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SymCrypto_KeyWrapUnwrap_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add_loop(TestCase_p, test_aes_wrap_unwrap, 4) != 0) goto FuncErrorReturn;
#ifdef VALTEST_SYM_ALGO_SM4
        if (sfzutf_test_add_loop(TestCase_p, test_sm4_wrap_unwrap, 4) != 0) goto FuncErrorReturn;
#endif
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_sym_keywrap.c */
