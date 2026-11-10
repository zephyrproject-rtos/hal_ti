/* cs_test_val.h
 *
 * Configuration Settings for the PSA API test tool.
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

#ifndef INCLUDE_GUARD_CS_TEST_PSA_TEST_H
#define INCLUDE_GUARD_CS_TEST_PSA_TEST_H

/*-----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include <third_party/hsmddk/include/Config/cs_adapter_psa.h>

/*----------------------------------------------------------------------------
 * Definitions and macros
 */
// Enable debug logging
#ifdef LOG_SEVERITY_MAX
#undef LOG_SEVERITY_MAX
#endif
#define LOG_SEVERITY_MAX  LOG_SEVERITY_CRIT
//#define LOG_SEVERITY_MAX  LOG_SEVERITY_WARN
//#define LOG_SEVERITY_MAX  LOG_SEVERITY_INFO

/*----------------------------------------------------------------------------
 * Hardware and firmware configuration specifics
 */
#ifndef PSA_REMOVE_SYM_ALGO_SHA512
#define PSATEST_SYM_ALGO_SHA512
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SHA3
#define PSATEST_SYM_ALGO_SHA3
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SM3
#define PSATEST_SYM_ALGO_SM3
#endif

#ifndef PSA_REMOVE_SYM_ALGO_AES_XTS
#define PSATEST_SYM_ALGO_AES_XTS
#endif
#ifndef PSA_REMOVE_SYM_ALGO_AES_CCM
#define PSATEST_SYM_ALGO_AES_CCM
#endif
#ifndef PSA_REMOVE_SYM_ALGO_AES_GCM
#define PSATEST_SYM_ALGO_AES_GCM
#endif
#ifndef PSA_REMOVE_SYM_ALGO_AES_F8
#define PSATEST_SYM_ALGO_AES_F8
#endif

#ifndef PSA_REMOVE_SYM_ALGO_3DES
#define PSATEST_SYM_ALGO_3DES
#endif

#ifndef PSA_REMOVE_SYM_ALGO_CHACHA20
#define PSATEST_SYM_ALGO_CHACHA20
#endif
#ifndef PSA_REMOVE_SYM_ALGO_POLY1305
#define PSATEST_SYM_ALGO_POLY1305
#endif

#ifndef PSA_REMOVE_SYM_ALGO_SM4
#define PSATEST_SYM_ALGO_SM4
#endif
#ifndef PSA_REMOVE_SYM_ALGO_SM4_GCM
#define PSATEST_SYM_ALGO_SM4_GCM
#endif

#ifndef PSA_REMOVE_SYM_ALGO_ARIA
#define PSATEST_SYM_ALGO_ARIA
#endif
#ifndef PSA_REMOVE_SYM_ALGO_ARIA_CCM
#define PSATEST_SYM_ALGO_ARIA_CCM
#endif
#ifndef PSA_REMOVE_SYM_ALGO_ARIA_GCM
#define PSATEST_SYM_ALGO_ARIA_GCM
#endif

#ifndef PSA_REMOVE_ASYM_CURVE25519
#define PSATEST_ASYM_CURVE25519
#endif

#if !defined(PSA_REMOVE_ASYM_EDDSA_SIGN) && \
    !defined(PSA_REMOVE_ASYM_EDDSA_VERIFY)
#define PSATEST_ASYM_EDDSA
#endif

#if !defined(PSA_REMOVE_ASYM_SM2DSA_SIGN) && \
    !defined(PSA_REMOVE_ASYM_SM2DSA_VERIFY) && \
    !defined(PSA_REMOVE_ASYM_SM2KEX_GEN_SHARED_SECRET) && \
    !defined(PSA_REMOVE_ASYM_SM2ENC)
#define PSATEST_ASYM_SM2
#endif

#ifndef PSA_REMOVE_ASYM_ECIES
#define PSATEST_ECIES
#endif

#endif /* INCLUDE_GUARD_CS_TEST_PSA_TEST_H */

/* end of file cs_test_psa.h */
