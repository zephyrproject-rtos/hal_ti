/* valtest_parser.c
 *
 * Description: Calls other test functions
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


void
valtest_initialize(void)
{
}

void
valtest_terminate(void)
{
}

int
build_suite(void)
{
    struct TestSuite * TestSuite_p = sfzutf_tsuite_create("VAL_Tests");
    if (TestSuite_p != NULL)
    {
        if (suite_add_test_System(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_Nop(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_Random(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AssetManagement(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_SymHashHMac(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_SymCrypto(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_SymAuthCrypto(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_SymCipherMac(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_SymKeyWrap(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymEcdh(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymEcdsa(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymSm2(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymCurve25519(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymEddsa(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymDh(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymRsa(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymPk(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_AsymEcies(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_SecureTimer(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_Service(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_SpecialFunctions(TestSuite_p) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_parser.c */
