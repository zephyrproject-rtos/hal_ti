/* valtest_internal.h
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

#ifndef INCLUDE_GUARD_VAL_TEST_INTERNAL_H
#define INCLUDE_GUARD_VAL_TEST_INTERNAL_H

#include "c_test_val.h"                 // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#include "sfzutf_internal.h"            // test environment
#include "api_val.h"                    // API to test

// VAL_TEST_MAX_* defines is used in several places in the test suite,
// including in test vectors
#define VAL_TEST_MAX_BUFLEN         512 /** Maximum general buffer length. */
#define VAL_TEST_MAX_VERSION_LENGTH 256 /** Maximum version information buffer length. */

/* Associated Data for general use */
extern const char * g_ValTestAssociatedData_p;

/* Reset allowed indication */
extern bool g_ValTestResetAllowed;

/* Test cleanup indication */
extern bool g_ValTestCleanUp;

/* Begin vector index */
extern int32_t g_ValTestBeginVector;

/* Repeat vector indication */
extern bool g_ValTestRepeatVector;

/* TRNG sample cycles to use */
extern uint16_t g_ValTestTrngSampleCycles;

/* Verbose level */
extern int g_ValTestVerbose;

/* Each suite needs to provide this interface */
int build_suite(void);

int suite_add_test_System(struct TestSuite * TestSuite_p);
int suite_add_test_Nop(struct TestSuite * TestSuite_p);
int suite_add_test_Random(struct TestSuite * TestSuite_p);
int suite_add_test_AssetManagement(struct TestSuite * TestSuite_p);
int suite_add_test_SymHashHMac(struct TestSuite * TestSuite_p);
int suite_add_test_SymCrypto(struct TestSuite * TestSuite_p);
int suite_add_test_SymAuthCrypto(struct TestSuite * TestSuite_p);
int suite_add_test_SymCipherMac(struct TestSuite * TestSuite_p);
int suite_add_test_SymKeyWrap(struct TestSuite * TestSuite_p);
int suite_add_test_AsymDh(struct TestSuite * TestSuite_p);
int suite_add_test_AsymEcdh(struct TestSuite * TestSuite_p);
int suite_add_test_AsymEcdsa(struct TestSuite * TestSuite_p);
int suite_add_test_AsymSm2(struct TestSuite * TestSuite_p);
int suite_add_test_AsymCurve25519(struct TestSuite * TestSuite_p);
int suite_add_test_AsymEddsa(struct TestSuite * TestSuite_p);
int suite_add_test_AsymRsa(struct TestSuite * TestSuite_p);
int suite_add_test_AsymPk(struct TestSuite * TestSuite_p);
int suite_add_test_AsymEcies(struct TestSuite * TestSuite_p);
int suite_add_test_SecureTimer(struct TestSuite * TestSuite_p);
int suite_add_test_SpecialFunctions(struct TestSuite * TestSuite_p);
int suite_add_test_Service(struct TestSuite * TestSuite_p);

void valtest_initialize(void);
void valtest_terminate(void);
bool valtest_StrictArgsCheck(void);
ValStatus_t valtest_DefaultTrngConfig(void);
bool valtest_IsTrngActive(const bool fActivate);
bool valtest_IsCOIDAvailable(void);
bool valtest_IsChaCha20Supported(void);
bool valtest_IsPoly1305Supported(void);
bool valtest_IsSM4Supported(void);
bool valtest_IsARIASupported(void);
bool valtest_IsSM3Supported(void);

/*----------------------------------------------------------------------------
 * asn1get
 *
 * Simple ASN.1 decoder. Reads the next item (Tag-Length-Value triplet) from
 * 'octets_p'. The actual Tag must match 'tag'. Length must be in 1..0xFFFF.
 * Returns a pointer to the item's Value.
 * Integer values may start with 0x00 to avoid being interpreted as a negative
 * value, but that interpretation is up to the caller.
 */
uint8_t *
asn1get(const uint8_t * octets_p,
        size_t * itemlen_p,
        uint8_t tag);


/*----------------------------------------------------------------------------
 * asn1put
 *
 * Simple ASN.1 encoder. Stores the next item (Tag-Length-Value triplet) at
 * 'octets_p'.  Tag must be 0x30 (Sequence) or 0x02 (Integer). Length must be
 * in 0..0xFFFF. Uses 'c_memmove' to copy the item, unless item_p is NULL, e.g
 * for a Sequence.
 * Returns a pointer to the location right after the stored item ('item_p != NULL)
 * or to the start of the Value ('item_p' == NULL).
 */
uint8_t *
asn1put(uint8_t * octets_p,
        uint8_t * item_p,
        size_t itemlen,
        uint8_t tag);


#endif /* INCLUDE_GUARD_VAL_TEST_INTERNAL_H */

/* end of file valtest_internal.h */
