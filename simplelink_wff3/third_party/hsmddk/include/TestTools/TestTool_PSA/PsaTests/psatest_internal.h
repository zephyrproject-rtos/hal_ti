/* psatest_internal.h
 *
 * Description: Internal utility functions
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

#ifndef INCLUDE_GUARD_PSA_TEST_INTERNAL_H
#define INCLUDE_GUARD_PSA_TEST_INTERNAL_H

#include "c_test_psa.h"                 // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#include "sfzutf_internal.h"            // test environment
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>

// PSA_TEST_MAX_* defines is used in several places in the test suite,
// including in test vectors
#define PSA_TEST_MAX_BUFLEN         512 /** Maximum general buffer length. */
#define PSA_TEST_MAX_VERSION_LENGTH 256 /** Maximum version information buffer length. */

/* Associated Data for general use */
extern const char * g_PsaTestAssociatedData_p;

/* Reset allowed indication */
extern bool g_PsaTestResetAllowed;

/* Test cleanup indication */
extern bool g_PsaTestCleanUp;

/* Begin vector index */
extern int g_PsaTestBeginVector;

/* Repeat vector indication */
extern bool g_PsaTestRepeatVector;

/* TRNG sample cycles to use */
extern uint16_t g_PsaTestTrngSampleCycles;

/* Verbose level */
extern int g_PsaTestVerbose;

/* Each suite needs to provide this interface */
int build_suite(void);

int suite_add_test_Hash(struct TestSuite * TestSuite_p);
int suite_add_test_cipher(struct TestSuite * TestSuite_p);
int suite_add_test_mac(struct TestSuite * TestSuite_p);
int suite_add_test_aead(struct TestSuite * TestSuite_p);
int suite_add_test_asym_sign(struct TestSuite * TestSuite_p);
int suite_add_test_asym_enc(struct TestSuite * TestSuite_p);
int suite_add_test_asym_ecdh(struct TestSuite * TestSuite_p);
int suite_add_test_key_derivation(struct TestSuite * TestSuite_p);
int suite_add_test_generate_key(struct TestSuite * TestSuite_p);
int suite_add_test_import_key(struct TestSuite * TestSuite_p);
int suite_add_test_copy_key(struct TestSuite * TestSuite_p);

void psatest_initialize(void);
void psatest_terminate(void);
bool psatest_IsCOIDAvailable(void);

#endif /* INCLUDE_GUARD_PSA_TEST_INTERNAL_H */

/* end of file psatest_internal.h */
