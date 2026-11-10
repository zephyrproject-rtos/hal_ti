/* psatest_parser.c
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

#include "psatest_internal.h"
#ifdef PSA_ENABLE_DEBUG_FUNCTIONS
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_debug.h>
#endif


void
psatest_initialize(void)
{
    /* Intentially empty */
}

void
psatest_terminate(void)
{
#ifdef PSA_ENABLE_DEBUG_FUNCTIONS
    psaDebug_KeyStoreDump();
#endif
}

int
build_suite(void)
{
    struct TestSuite * TestSuite_p = sfzutf_tsuite_create("PSA_Tests");
    if (TestSuite_p != NULL)
    {
        if (suite_add_test_Hash(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_cipher(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_mac(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_aead(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_asym_sign(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_asym_enc(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_asym_ecdh(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_key_derivation(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_generate_key(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_import_key(TestSuite_p) != 0) goto FuncErrorReturn;
        if (suite_add_test_copy_key(TestSuite_p) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_parser.c */
