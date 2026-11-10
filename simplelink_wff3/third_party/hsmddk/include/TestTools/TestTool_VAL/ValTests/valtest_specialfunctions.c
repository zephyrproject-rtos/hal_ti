/* valtest_specialfunctions.c
 *
 * Description: Special Functions functionality related tests
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

#ifdef VALTEST_SF_MILENAGE
/* Test vectors. */
#include "testvectors_milenage.h"

static int
do_conformance_test(
        TestVector_Milenage_t Vector_p)
{
    ValStatus_t Status;
    uint8_t RES[8];
    uint8_t CK[16];
    uint8_t IK[16];
    uint8_t MACA[8];
    uint8_t MACS[8];
    uint8_t AK[6];
    uint8_t AKstar[6];
    uint8_t OPc[16];

    Status = val_SFMilenageConformance(Vector_p->RAND_p,
                                       Vector_p->SQN_p, Vector_p->AMF_p,
                                       Vector_p->K_p, Vector_p->OP_p,
                                       RES, CK, IK,
                                       MACA, MACS, AK, AKstar, OPc);

    unsupported_unless(val_CheckFunctionResult(Status) != VAL_INVALID_TOKEN, "Special Functions not activated");
    unsupported_unless(val_CheckFunctionResult(Status) != VAL_INVALID_PARAMETER, "Milenage (conformance) not activated");

    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SFMilenageConformance()=", Status);
    fail_if(memcmp(MACA, Vector_p->f1_p, sizeof(MACA)), "MACA != f1", -1);
    fail_if(memcmp(MACS, Vector_p->f1star_p, sizeof(MACS)), "MACS != f1star", -1);
    fail_if(memcmp(RES, Vector_p->f2_p, sizeof(RES)), "RES != f2", -1);
    fail_if(memcmp(CK, Vector_p->f3_p, sizeof(CK)), "CK != f3", -1);
    fail_if(memcmp(IK, Vector_p->f4_p, sizeof(IK)), "IK != f4", -1);
    fail_if(memcmp(AK, Vector_p->f5_p, sizeof(AK)), "AK != f5", -1);
    fail_if(memcmp(AKstar, Vector_p->f5star_p, sizeof(AKstar)), "AKstar != f5star", -1);
    fail_if(memcmp(OPc, Vector_p->OPc_p, sizeof(OPc)), "OPc != OPc", -1);

    return END_TEST_SUCCES;
}

START_TEST(test_SF_MilenageConformance)
{
    uint32_t ndx;
    int rc;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0; ; ndx++)
    {
        TestVector_Milenage_t tv_p = test_vectors_milenage_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        rc = do_conformance_test(tv_p);
        if (rc == END_TEST_UNSUPPORTED)
        {
            return rc;
        }
        if (rc != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        test_vectors_milenage_release(tv_p);
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
suite_add_test_SpecialFunctions(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SpecialFunctions_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }
#ifdef VALTEST_SF_MILENAGE
        if (sfzutf_test_add(TestCase_p, test_SF_MilenageConformance) != 0) goto FuncErrorReturn;
#endif

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_specialfunctions.c */
