/* psatest_hash.c
 *
 * Description: hash tests for SHA-1, SHA-2 and SHA-3
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

#include "psatest_internal.h"

/* Test vectors. */
#include "testvectors_hash.h"

#define PSA_HASH_STATE_INIT   0U
#define PSA_HASH_STATE_SETUP  1U
#define PSA_HASH_STATE_UPDATE 2U
#define PSA_HASH_STATE_RESUME 3U

/*----------------------------------------------------------------------------
 * do_hash_test
 *
 * Helper function that runs a single hash test.
 */
static int
do_hash_test(uint32_t VectorIndex,
             psa_algorithm_t alg,
             TestVector_HASH_t Vector_p)
{
    psa_status_t Status;
    uint8_t Digest[64];
    size_t hash_length = 0U;

    (void)memset(Digest, 0, sizeof(Digest));
    Status = psa_hash_compute(alg, Vector_p->Msg_p, Vector_p->MsgLen, Digest, Vector_p->DigestLen, &hash_length);
    fail_if(PSA_SUCCESS != Status, "single hash operation", Status);
    fail_if(Vector_p->DigestLen != hash_length, "Length mismatch ", (int)hash_length);
    fail_if(memcmp(Digest, Vector_p->Digest_p, Vector_p->DigestLen) != 0, "", VectorIndex);

    return END_TEST_SUCCES;
}
/*----------------------------------------------------------------------------
 * do_hash_compare_test
 *
 * Helper function that runs a single hash test and compare values.
 */
static int
do_hash_compare_test(uint32_t VectorIndex,
                     psa_algorithm_t alg,
                     TestVector_HASH_t Vector_p)
{
    psa_status_t Status;

    Status = psa_hash_compare(alg, Vector_p->Msg_p, Vector_p->MsgLen,
                              Vector_p->Digest_p, Vector_p->DigestLen);
    fail_if(PSA_SUCCESS != Status, "Invalid digest value", VectorIndex);

    return END_TEST_SUCCES;
}
/*----------------------------------------------------------------------------
 * do_hash_update
 *
 * Helper function that runs hash update.
 */
static int
do_hash_update(psa_hash_operation_t *SymContext_p,
               TestVector_HASH_t Vector_p)
{
    psa_status_t Status;

    Status = psa_hash_update(SymContext_p, Vector_p->Msg_p, Vector_p->MsgLen);
    fail_if(PSA_SUCCESS != Status, "Update operation", Status);

    return END_TEST_SUCCES;
}

/*----------------------------------------------------------------------------
 * do_hash_final
 *
 * Helper function that runs hash Final.
 */
static int
do_hash_final(uint32_t VectorIndex,
              psa_hash_operation_t *SymContext_p,
              TestVector_HASH_t Vector_p)
{
    psa_status_t Status;
    uint8_t Digest[64];
    size_t hash_length;

    Status = psa_hash_finish(SymContext_p, Digest, Vector_p->DigestLen, &hash_length);
    fail_if(PSA_SUCCESS != Status, "Final operation", Status);
    fail_if(Vector_p->DigestLen != hash_length, "Length mismatch ", (int)hash_length);
    fail_if(memcmp(Digest, Vector_p->Digest_p, Vector_p->DigestLen) != 0, "", VectorIndex);

    return END_TEST_SUCCES;
}
/*----------------------------------------------------------------------------
 * do_hash_final_verify
 *
 * Helper function that runs hash Final and verify digest value.
 */
static int
do_hash_final_verify(psa_hash_operation_t *SymContext_p,
                     TestVector_HASH_t Vector_p)
{
    psa_status_t Status;

    Status = psa_hash_verify(SymContext_p, Vector_p->Digest_p, Vector_p->DigestLen);
    fail_if(PSA_SUCCESS != Status, "Final Verify operation", Status);

    return END_TEST_SUCCES;
}


START_TEST(test_hash)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Algorithm;
        TestVector_HASH_t tv_p;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (0U == tv_p->MsgLen)
        {
            test_vectors_hash_release(tv_p);
            continue;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = PSA_ALG_SHA_1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = PSA_ALG_SHA_224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = PSA_ALG_SHA_384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = PSA_ALG_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = PSA_ALG_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = PSA_ALG_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = PSA_ALG_SHA3_512;
            break;
#endif
        default:
            Algorithm = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Algorithm)
        {
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        if (do_hash_test(ndx, Algorithm, tv_p) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        if (do_hash_compare_test(ndx, Algorithm, tv_p))
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }

        test_vectors_hash_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST(test_hash_multipart)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;
        psa_hash_operation_t SymContext;
        psa_algorithm_t Algorithm;
        psa_status_t Status;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (0U == tv_p->MsgLen)
        {
            test_vectors_hash_release(tv_p);
            continue;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = PSA_ALG_SHA_1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = PSA_ALG_SHA_224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = PSA_ALG_SHA_384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = PSA_ALG_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = PSA_ALG_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = PSA_ALG_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = PSA_ALG_SHA3_512;
            break;
#endif
#endif
        default:
            Algorithm = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Algorithm)
        {
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        SymContext.hash_state = PSA_HASH_STATE_INIT;

        Status = psa_hash_setup(&SymContext, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);
        if (do_hash_update(&SymContext, tv_p) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            if (do_hash_final(ndx, &SymContext, tv_p) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }
        Status = psa_hash_abort(&SymContext);
        fail_if(Status != PSA_SUCCESS, "psa_hash_abort()=", Status);
        fail_if(SymContext.alg != PSA_ALG_NONE, "psa_hash_abort()=", SymContext.alg);
        test_vectors_hash_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

START_TEST(test_hash_update_in_chunks)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;
        psa_hash_operation_t SymContext;
        psa_algorithm_t Algorithm;
        psa_status_t Status;
        const uint8_t* Msg_p;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (0U == tv_p->MsgLen)
        {
            test_vectors_hash_release(tv_p);
            continue;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = PSA_ALG_SHA_1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = PSA_ALG_SHA_224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = PSA_ALG_SHA_384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = PSA_ALG_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = PSA_ALG_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = PSA_ALG_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = PSA_ALG_SHA3_512;
            break;
#endif
#endif
        default:
            Algorithm = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Algorithm)
        {
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        SymContext.hash_state = PSA_HASH_STATE_INIT;
        Status = psa_hash_setup(&SymContext, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);

        if ((Algorithm == PSA_ALG_SHA_1) ||
            (Algorithm == PSA_ALG_SHA_224) ||
            (Algorithm == PSA_ALG_SHA_256) ||
            (Algorithm == PSA_ALG_SHA_384) ||
            (Algorithm == PSA_ALG_SHA_512))
        {
            if (6400U == tv_p->MsgLen)
            {
                Msg_p = tv_p->Msg_p;
                Status = psa_hash_update(&SymContext, Msg_p, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext, Msg_p+60, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext, Msg_p+120, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext, Msg_p+180, 6220);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                if (do_hash_final(ndx, &SymContext, tv_p) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                else
                {
                    Success++;
                }
            }
            else
            {
                test_vectors_hash_release(tv_p);
                continue;
            }
        }
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        else if ((Algorithm == PSA_ALG_SHA3_224) ||
                 (Algorithm == PSA_ALG_SHA3_256) ||
                 (Algorithm == PSA_ALG_SHA3_384) ||
                 (Algorithm == PSA_ALG_SHA3_512))
        {
            if (150U == tv_p->MsgLen)
            {
                Msg_p = tv_p->Msg_p;
                Status = psa_hash_update(&SymContext, Msg_p, 30);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext, Msg_p+30, 30);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext, Msg_p+60, 30);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext, Msg_p+90, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                if (do_hash_final(ndx, &SymContext, tv_p) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                else
                {
                    Success++;
                }
            }
            else
            {
                test_vectors_hash_release(tv_p);
                continue;
            }
        }
#endif
#endif

        test_vectors_hash_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
START_TEST(test_hash_clone)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;
        psa_hash_operation_t SymContext;
        psa_hash_operation_t SymContext_cloned;
        psa_algorithm_t Algorithm;
        psa_status_t Status;
        const uint8_t* Msg_p;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (0U == tv_p->MsgLen)
        {
            test_vectors_hash_release(tv_p);
            continue;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = PSA_ALG_SHA_1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = PSA_ALG_SHA_224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = PSA_ALG_SHA_384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = PSA_ALG_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = PSA_ALG_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = PSA_ALG_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = PSA_ALG_SHA3_512;
            break;
#endif
#endif
        default:
            Algorithm = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Algorithm)
        {
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        SymContext.hash_state = PSA_HASH_STATE_INIT;
        Status = psa_hash_setup(&SymContext, Algorithm);
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        if ((Algorithm == PSA_ALG_SHA3_224) ||
            (Algorithm == PSA_ALG_SHA3_256) ||
            (Algorithm == PSA_ALG_SHA3_384) ||
            (Algorithm == PSA_ALG_SHA3_512))
        {
            fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_setup()=", Status);
            test_vectors_hash_release(tv_p);
            continue;
        }
        else
#endif
#endif
        {
            fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);
        }

        if ((Algorithm == PSA_ALG_SHA_1) ||
            (Algorithm == PSA_ALG_SHA_224) ||
            (Algorithm == PSA_ALG_SHA_256) ||
            (Algorithm == PSA_ALG_SHA_384) ||
            (Algorithm == PSA_ALG_SHA_512))
        {
            if (6400U == tv_p->MsgLen)
            {
                Msg_p = tv_p->Msg_p;
                Status = psa_hash_update(&SymContext, Msg_p, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext, Msg_p+60, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_clone(&SymContext, &SymContext_cloned);
                fail_if(PSA_SUCCESS != Status, "psa_hash_clone", Status);
                Status = psa_hash_update(&SymContext_cloned, Msg_p+120, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext_cloned, Msg_p+180, 6220);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                if (do_hash_final(ndx, &SymContext_cloned, tv_p) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                else
                {
                    Success++;
                }
            }
            else
            {
                test_vectors_hash_release(tv_p);
                continue;
            }
        }
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        else if ((Algorithm == PSA_ALG_SHA3_224) ||
                 (Algorithm == PSA_ALG_SHA3_256) ||
                 (Algorithm == PSA_ALG_SHA3_384) ||
                 (Algorithm == PSA_ALG_SHA3_512))
        {
            if (150U == tv_p->MsgLen)
            {
                Msg_p = tv_p->Msg_p;
                Status = psa_hash_update(&SymContext, Msg_p, 30);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext, Msg_p+30, 30);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_clone(&SymContext, &SymContext_cloned);
                fail_if(PSA_SUCCESS != Status, "psa_hash_clone", Status);
                Status = psa_hash_update(&SymContext_cloned, Msg_p+60, 30);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                Status = psa_hash_update(&SymContext_cloned, Msg_p+90, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);
                if (do_hash_final(ndx, &SymContext_cloned, tv_p) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                else
                {
                    Success++;
                }
            }
            else
            {
                test_vectors_hash_release(tv_p);
                continue;
            }
        }
#endif
#endif

        test_vectors_hash_release(tv_p);
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

START_TEST(test_hash_multipart_verify)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;
        psa_hash_operation_t SymContext;
        psa_algorithm_t Algorithm;
        psa_status_t Status;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (0U == tv_p->MsgLen)
        {
            test_vectors_hash_release(tv_p);
            continue;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = PSA_ALG_SHA_1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = PSA_ALG_SHA_224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = PSA_ALG_SHA_384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = PSA_ALG_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = PSA_ALG_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = PSA_ALG_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = PSA_ALG_SHA3_512;
            break;
#endif
#endif
        default:
            Algorithm = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Algorithm)
        {
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        memset(&SymContext, 0, sizeof(SymContext));
        SymContext.hash_state = PSA_HASH_STATE_INIT;
        Status = psa_hash_setup(&SymContext, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);

        if (do_hash_update(&SymContext, tv_p) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            if (do_hash_final_verify(&SymContext, tv_p) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        test_vectors_hash_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST

#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
START_TEST(test_hash_multipart_suspend)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;
        psa_hash_operation_t SymContext_sus;
        psa_hash_operation_t SymContext_res;
        psa_algorithm_t Algorithm;
        psa_status_t Status;
        uint8_t hash_state[256];
        size_t hash_state_length;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if (0U == tv_p->MsgLen)
        {
            LOG_INFO("Skip test \n");
            test_vectors_hash_release(tv_p);
            continue;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = PSA_ALG_SHA_1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = PSA_ALG_SHA_224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = PSA_ALG_SHA_384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = PSA_ALG_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = PSA_ALG_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = PSA_ALG_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = PSA_ALG_SHA3_512;
            break;
#endif
#endif
        default:
            Algorithm = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Algorithm)
        {
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        memset(&SymContext_sus, 0, sizeof(SymContext_sus));
        memset(&SymContext_res, 0, sizeof(SymContext_res));
        memset(&hash_state, 0, sizeof(hash_state));
        SymContext_sus.hash_state = PSA_HASH_STATE_INIT;

        Status = psa_hash_setup(&SymContext_sus, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);

        if (do_hash_update(&SymContext_sus, tv_p) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Status = psa_hash_suspend(&SymContext_sus, hash_state, 256, &hash_state_length);
            fail_if(Status != PSA_SUCCESS, "psa_hash_suspend()=", Status);

            Status = psa_hash_resume(&SymContext_res, hash_state, hash_state_length);
            fail_if(Status != PSA_SUCCESS, "psa_hash_resume()=", Status);

            if (do_hash_final(ndx, &SymContext_res, tv_p) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        test_vectors_hash_release(tv_p);
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

#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
START_TEST(test_hash_multipart_verify_suspend)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;
        psa_hash_operation_t SymContext_sus;
        psa_hash_operation_t SymContext_res;
        psa_algorithm_t Algorithm;
        psa_status_t Status;
        uint8_t hash_state[256];
        size_t hash_state_length;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (0U == tv_p->MsgLen)
        {
            test_vectors_hash_release(tv_p);
            continue;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = PSA_ALG_SHA_1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = PSA_ALG_SHA_224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = PSA_ALG_SHA_384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = PSA_ALG_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = PSA_ALG_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = PSA_ALG_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = PSA_ALG_SHA3_512;
            break;
#endif
#endif
        default:
            Algorithm = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Algorithm)
        {
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        memset(&SymContext_sus, 0, sizeof(SymContext_sus));
        memset(&SymContext_res, 0, sizeof(SymContext_res));
        memset(&hash_state, 0, sizeof(hash_state));
        SymContext_sus.hash_state = PSA_HASH_STATE_INIT;

        Status = psa_hash_setup(&SymContext_sus, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);

        if (do_hash_update(&SymContext_sus, tv_p) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Status = psa_hash_suspend(&SymContext_sus, hash_state, 256, &hash_state_length);
            fail_if(Status != PSA_SUCCESS, "psa_hash_suspend()=", Status);

            Status = psa_hash_resume(&SymContext_res, hash_state, hash_state_length);
            fail_if(Status != PSA_SUCCESS, "psa_hash_resume()=", Status);

            if (do_hash_final_verify(&SymContext_res, tv_p) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        test_vectors_hash_release(tv_p);
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

#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
START_TEST(test_hash_update_in_chunks_suspend)
{
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;
        psa_hash_operation_t SymContext_sus;
        psa_hash_operation_t SymContext_res;
        psa_hash_operation_t SymContext_res1;
        psa_algorithm_t Algorithm;
        psa_status_t Status;
        uint8_t hash_state[256];
        size_t hash_state_length;
        const uint8_t* Msg_p;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if (0U == tv_p->MsgLen)
        {
            test_vectors_hash_release(tv_p);
            continue;
        }

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = PSA_ALG_SHA_1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = PSA_ALG_SHA_224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = PSA_ALG_SHA_256;
            break;
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = PSA_ALG_SHA_384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = PSA_ALG_SHA_512;
            break;
#endif
#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = PSA_ALG_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = PSA_ALG_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = PSA_ALG_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = PSA_ALG_SHA3_512;
            break;
#endif
#endif
        default:
            Algorithm = PSA_ALG_NONE;
            break;
        }
        if (PSA_ALG_NONE == Algorithm)
        {
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        memset(&SymContext_sus, 0, sizeof(SymContext_sus));
        memset(&SymContext_res, 0, sizeof(SymContext_sus));
        memset(&SymContext_res1, 0, sizeof(SymContext_sus));
        memset(&hash_state, 0, sizeof(hash_state));
        SymContext_sus.hash_state = PSA_HASH_STATE_INIT;

        Status = psa_hash_setup(&SymContext_sus, Algorithm);
        fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);

        if ((Algorithm == PSA_ALG_SHA_1) ||
            (Algorithm == PSA_ALG_SHA_224) ||
            (Algorithm == PSA_ALG_SHA_256) ||
            (Algorithm == PSA_ALG_SHA_384) ||
            (Algorithm == PSA_ALG_SHA_512))
        {
            if (6400U == tv_p->MsgLen)
            {
                Msg_p = tv_p->Msg_p;
                Status = psa_hash_update(&SymContext_sus, Msg_p, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);

                Status = psa_hash_suspend(&SymContext_sus, hash_state, 256, &hash_state_length);
                fail_if(Status != PSA_SUCCESS, "psa_hash_suspend()=", Status);

                Status = psa_hash_resume(&SymContext_res, hash_state, hash_state_length);
                fail_if(Status != PSA_SUCCESS, "psa_hash_resume()=", Status);

                Status = psa_hash_update(&SymContext_res, Msg_p+60, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);

                memset(&hash_state, 0, sizeof(hash_state));
                hash_state_length = 0;
                Status = psa_hash_suspend(&SymContext_res, hash_state, 256, &hash_state_length);
                fail_if(Status != PSA_SUCCESS, "psa_hash_suspend()=", Status);

                Status = psa_hash_resume(&SymContext_res1, hash_state, hash_state_length);
                fail_if(Status != PSA_SUCCESS, "psa_hash_resume()=", Status);

                Status = psa_hash_update(&SymContext_res1, Msg_p+120, 60);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);

                Status = psa_hash_update(&SymContext_res1, Msg_p+180, 6220);
                fail_if(PSA_SUCCESS != Status, "Update operation", Status);

                if (do_hash_final(ndx, &SymContext_res1, tv_p) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                else
                {
                    Success++;
                }
            }
            else
            {
            }
        }

        test_vectors_hash_release(tv_p);
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

START_TEST(test_hash_state)
{
    psa_hash_operation_t SymContext;
    psa_algorithm_t Algorithm = PSA_ALG_SHA_256;
    size_t hash_size = (256/8);
    uint8_t hashData[256] = { 0 };
    uint8_t Digest[256];
    size_t hash_length;
    psa_status_t Status;

    memset(&SymContext, 0, sizeof(SymContext));
    SymContext.hash_state = PSA_HASH_STATE_SETUP;
    Status = psa_hash_setup(&SymContext, Algorithm);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_setup()=", Status);

    SymContext.hash_state = PSA_HASH_STATE_INIT;
    Status = psa_hash_update(&SymContext, hashData, sizeof(hashData));
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_update()=", Status);
    SymContext.hash_state = PSA_HASH_STATE_UPDATE;
    Status = psa_hash_update(&SymContext, hashData, sizeof(hashData));
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_update()=", Status);

    SymContext.hash_state = PSA_HASH_STATE_INIT;
    Status = psa_hash_finish(&SymContext, Digest, hash_size, &hash_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_finish()=", Status);
    SymContext.hash_state = PSA_HASH_STATE_SETUP;
    Status = psa_hash_finish(&SymContext, Digest, hash_size, &hash_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_finish()=", Status);

    SymContext.hash_state = PSA_HASH_STATE_INIT;
    Status = psa_hash_verify(&SymContext, Digest, hash_size);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_verify()=", Status);
    SymContext.hash_state = PSA_HASH_STATE_SETUP;
    Status = psa_hash_verify(&SymContext, Digest, hash_size);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_verify()=", Status);

}
END_TEST
/*----------------------------------------------------------------------------
 * Some negative Hash tests
 *--------------------------------------------------------------------------*/
START_TEST(test_hash_invalid_algorithm)
{
    psa_hash_operation_t SymContext;
    size_t hash_size = 256;
    uint8_t hashData[256] = { 0 };
    uint8_t Digest[256];
    size_t hash_length = 256;
    psa_status_t Status;

    memset(&SymContext, 0, sizeof(SymContext));
    Status = psa_hash_compute(PSA_ALG_NONE, hashData, hash_length,
                              Digest, hash_size, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compute()=", Status);

    Status = psa_hash_compute(PSA_ALG_CBC_MAC, hashData, hash_length,
                              Digest, hash_size, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compute()=", Status);

    Status = psa_hash_compare(PSA_ALG_NONE, hashData, hash_length,
                              Digest, hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compare()=", Status);

    Status = psa_hash_compare(PSA_ALG_CBC_MAC, hashData, hash_length,
                              Digest, hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compare()=", Status);

    Status = psa_hash_setup(&SymContext, PSA_ALG_NONE);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_setup()=", Status);

    Status = psa_hash_setup(&SymContext, PSA_ALG_CBC_MAC);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_setup()=", Status);
}
END_TEST


START_TEST(test_hash_buffer_too_small)
{
    psa_hash_operation_t SymContext;
    psa_algorithm_t Algorithm = PSA_ALG_SHA_256;
    size_t hash_size = (224/8);
    uint8_t Digest[224];
    size_t hash_length;
    psa_status_t Status;
    TestVector_HASH_t tv_p;

    tv_p = test_vectors_hash_get(138);
    fail_if(NULL == tv_p, "No test vector", 138);

    Status = psa_hash_compute(Algorithm, tv_p->Digest_p, tv_p->MsgLen,
                              Digest, hash_size, &hash_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_hash_compute()=", Status);

    memset(&SymContext, 0, sizeof(SymContext));
    SymContext.hash_state = PSA_HASH_STATE_INIT;
    Status = psa_hash_setup(&SymContext, Algorithm);
    fail_if(Status != PSA_SUCCESS, "psa_hash_setup()", Status);
    Status = psa_hash_update(&SymContext, tv_p->Msg_p, tv_p->MsgLen);
    fail_if(Status != PSA_SUCCESS, "psa_hash_update()", Status);
    Status = psa_hash_finish(&SymContext, Digest, hash_size, &hash_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_hash_finish()=", Status);

    Status = psa_hash_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_hash_abort()=", Status);

    test_vectors_hash_release(tv_p);
}
END_TEST


START_TEST(test_hash_arguments)
{
    psa_hash_operation_t SymContext;
    psa_algorithm_t Algorithm = PSA_ALG_SHA_256;
    uint8_t Digest[224];
    size_t hash_length;
    psa_status_t Status;
    TestVector_HASH_t tv_p;

    tv_p = test_vectors_hash_get(138);
    fail_if(NULL == tv_p, "No test vector", 138);

    memset(&SymContext, 0, sizeof(SymContext));

    Status = psa_hash_compute(PSA_ALG_MD5, tv_p->Msg_p, 17U,
                              Digest, tv_p->DigestLen, &hash_length);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_compute()=", Status);
    Status = psa_hash_compute(Algorithm, NULL, 17U,
                              Digest, tv_p->DigestLen, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compute()=", Status);
    Status = psa_hash_compute(Algorithm, tv_p->Msg_p, 0,
                              Digest, tv_p->DigestLen, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compute()=", Status);
    Status = psa_hash_compute(Algorithm, tv_p->Msg_p, tv_p->DigestLen,
                              NULL, tv_p->DigestLen, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compute()=", Status);
    Status = psa_hash_compute(Algorithm, tv_p->Msg_p, tv_p->DigestLen,
                              Digest, 0, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compute()=", Status);
    Status = psa_hash_compute(Algorithm, tv_p->Msg_p, tv_p->DigestLen,
                              Digest, tv_p->DigestLen, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compute()=", Status);

    Status = psa_hash_compare(Algorithm, NULL, tv_p->DigestLen,
                              tv_p->Digest_p, tv_p->DigestLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compare()=", Status);
    Status = psa_hash_compare(PSA_ALG_MD5, tv_p->Msg_p, tv_p->DigestLen,
                              tv_p->Digest_p, tv_p->DigestLen);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_compare()=", Status);
    Status = psa_hash_compare(Algorithm, tv_p->Msg_p, 0,
                              tv_p->Digest_p, tv_p->DigestLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compare()=", Status);
    Status = psa_hash_compare(Algorithm, tv_p->Msg_p, tv_p->DigestLen,
                              NULL, tv_p->DigestLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compare()=", Status);
    Status = psa_hash_compare(Algorithm, tv_p->Msg_p, tv_p->DigestLen,
                              tv_p->Digest_p, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_compare()=", Status);

    Status = psa_hash_setup(NULL, Algorithm);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_setup()=", Status);
    Status = psa_hash_setup(&SymContext, PSA_ALG_MD5);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_setup()=", Status);

    Status = psa_hash_update(NULL, tv_p->Msg_p, tv_p->MsgLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_update()=", Status);
    Status = psa_hash_update(&SymContext, NULL, tv_p->MsgLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_update()=", Status);
    Status = psa_hash_update(&SymContext, tv_p->Msg_p, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_update()=", Status);

    Status = psa_hash_finish(NULL, Digest, tv_p->DigestLen, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_finish()=", Status);
    Status = psa_hash_finish(&SymContext, NULL, tv_p->DigestLen, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_finish()=", Status);
    Status = psa_hash_finish(&SymContext, Digest, 0, &hash_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_finish()=", Status);
    Status = psa_hash_finish(&SymContext, Digest, tv_p->DigestLen, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_finish()=", Status);

    Status = psa_hash_verify(NULL, tv_p->Digest_p, tv_p->DigestLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_verify()=", Status);
    Status = psa_hash_verify(&SymContext, NULL, tv_p->DigestLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_verify()=", Status);
    Status = psa_hash_verify(&SymContext, tv_p->Digest_p, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_verify()=", Status);

    Status = psa_hash_abort(NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_abort()=", Status);

    test_vectors_hash_release(tv_p);
}
END_TEST

#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
START_TEST(test_hash_not_supported_algorithm)
{
    psa_hash_operation_t SymContext;
    psa_status_t Status;

    memset(&SymContext, 0, sizeof(SymContext));
    SymContext.hash_state = PSA_HASH_STATE_INIT;
    Status = psa_hash_setup(&SymContext, PSA_ALG_SHA3_224);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_setup()=", Status);

    Status = psa_hash_setup(&SymContext, PSA_ALG_SHA3_256);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_setup()=", Status);

    Status = psa_hash_setup(&SymContext, PSA_ALG_SHA3_384);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_setup()=", Status);

    Status = psa_hash_setup(&SymContext, PSA_ALG_SHA3_512);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_setup()=", Status);
}
END_TEST
#endif

#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
START_TEST(test_invalid_args_suspend_resume)
{
    psa_hash_operation_t SymContext;
    psa_status_t Status;
    uint8_t hash_state[256] = { 0 };
    size_t hash_state_size;
    size_t hash_state_len;

    memset(&SymContext, 0, sizeof(SymContext));
    SymContext.hash_state = PSA_HASH_STATE_INIT;
    Status = psa_hash_setup(&SymContext, PSA_ALG_SHA_256);
    fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);
    hash_state_size = 256;
    Status = psa_hash_suspend(NULL, hash_state, hash_state_size, &hash_state_len);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_suspend()=", Status);

    Status = psa_hash_suspend(&SymContext, NULL, hash_state_size, &hash_state_len);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_suspend()=", Status);

    Status = psa_hash_suspend(&SymContext, hash_state, 0, &hash_state_len);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_suspend()=", Status);

    Status = psa_hash_suspend(&SymContext, hash_state, hash_state_size, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_suspend()=", Status);

    Status = psa_hash_suspend(&SymContext, hash_state, 100, &hash_state_len);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_hash_suspend()=", Status);

    SymContext.hash_state = PSA_HASH_STATE_INIT;
    Status = psa_hash_suspend(&SymContext, hash_state, hash_state_size, &hash_state_len);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_suspend()=", Status);

    hash_state_len = 200;
    Status = psa_hash_resume(NULL, hash_state, hash_state_len);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_resume()=", Status);

    Status = psa_hash_resume(&SymContext, NULL, hash_state_len);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_resume()=", Status);

    Status = psa_hash_resume(&SymContext, hash_state, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_resume()=", Status);

    SymContext.hash_state = PSA_HASH_STATE_UPDATE;
    Status = psa_hash_resume(&SymContext, hash_state, hash_state_len);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_resume()=", Status);

    Status = psa_hash_clone(&SymContext, NULL);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_clone()=", Status);

    Status = psa_hash_clone(NULL, &SymContext);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_hash_clone()=", Status);

    Status = psa_hash_abort(NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_hash_abort()=", Status);
}
END_TEST
#endif

#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
START_TEST(test_suspend_resume_not_supported)
{
    psa_hash_operation_t SymContext;
    psa_status_t Status;
    uint8_t hash_state[256] = { 0 };
    size_t hash_state_size;
    size_t hash_state_len;

    memset(&SymContext, 0, sizeof(SymContext));
    SymContext.hash_state = PSA_HASH_STATE_INIT;
    Status = psa_hash_setup(&SymContext, PSA_ALG_SHA_256);
    fail_if(Status != PSA_SUCCESS, "psa_hash_setup()=", Status);
    hash_state_size = 256;
    Status = psa_hash_suspend(&SymContext, hash_state, hash_state_size, &hash_state_len);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_suspend()=", Status);

    hash_state_len = 200;
    Status = psa_hash_resume(&SymContext, hash_state, hash_state_len);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_resume()=", Status);

    Status = psa_hash_clone(&SymContext, &SymContext);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_hash_clone()=", Status);
}
END_TEST
#endif

#undef PSA_HASH_STATE_INIT
#undef PSA_HASH_STATE_SETUP
#undef PSA_HASH_STATE_UPDATE
#undef PSA_HASH_STATE_RESUME

int
suite_add_test_Hash(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SymCrypto_Hash_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_hash) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_multipart) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_multipart_verify) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_update_in_chunks) != 0) goto FuncErrorReturn;
#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
        if (sfzutf_test_add(TestCase_p, test_hash_clone) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_multipart_suspend) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_multipart_verify_suspend) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_update_in_chunks_suspend) != 0) goto FuncErrorReturn;
#endif

#ifndef PSA_USE_TOKEN_INTERMEDIATE_STATE
        if (sfzutf_test_add(TestCase_p, test_suspend_resume_not_supported) != 0) goto FuncErrorReturn;
#endif

        if (sfzutf_test_add(TestCase_p, test_hash_state) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_invalid_algorithm) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_buffer_too_small) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_arguments) != 0) goto FuncErrorReturn;
#ifdef PSA_USE_TOKEN_INTERMEDIATE_STATE
        if (sfzutf_test_add(TestCase_p, test_hash_not_supported_algorithm) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_invalid_args_suspend_resume) != 0) goto FuncErrorReturn;
#endif
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_hash.c */
