/** @file cs_adapter_psa.h
 *
 * @brief Configuration Settings for the PSA API driver.
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

#ifndef INCLUDE_GUARD_CS_ADAPTER_PSA_H
#define INCLUDE_GUARD_CS_ADAPTER_PSA_H

/*-----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include <third_party/hsmddk/include/Config/cs_driver.h>
#include <third_party/hsmddk/include/Config/cs_adapter.h>
#include <third_party/hsmddk/include/Config/cs_eip130.h>


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
/* Strict argument checking use */
#ifdef ADAPTER_STRICT_ARGS
#define PSA_STRICT_ARGS                 /* Check arguments */
#define PSA_LOG_LOWLEVEL_ERROR          /* Log low level HW/FW errors */
#endif

/* Associated Data labels for key blob generation and key derivation */
#define PSA_AS_KEYBLOB_ADLABEL "SomeAssociatedDataForGeneratingTheKeyBlob"
#define PSA_AS_DERIVE_ADLABEL  "JustSomeAssociatedDataForTheAssetLoadDerivationFunction"

/* The Monotonic Counter asset number for the key blob KEK
 * 0     - No Monotonic Counter use in derivation
 * 1..95 - Monotonic Counter asset number
 */
#define PSA_AS_DERIVE_MC_ASSETNUMBER  0

/* Token use related defines */
#define PSA_USE_TOKEN_INTERMEDIATE_STATE /* Hash intermediate state is going via the token */
#define PSA_USE_TOKEN_KEY               /* (Encryption) Key is going via the token */

/* Next define enables the debug functions for the PSA API key management */
//#define PSA_ENABLE_DEBUG_FUNCTIONS

/*----------------------------------------------------------------
 * Defines (switches) that can be used to remove features (functionality)
 */
// - Asset Management related

// - Symmetric crypto related
#ifndef EIP130_ENABLE_SYM_ALGO_SHA512
#define PSA_REMOVE_SYM_ALGO_SHA512
#endif
#ifndef EIP130_ENABLE_SYM_ALGO_SHA3
#define PSA_REMOVE_SYM_ALGO_SHA3
#endif
#ifndef EIP130_ENABLE_SYM_ALGO_SM3
#define PSA_REMOVE_SYM_ALGO_SM3
#endif
#ifndef EIP130_ENABLE_SYM_ALGO_POLY1305
#define PSA_REMOVE_SYM_ALGO_POLY1305
#endif

#ifndef EIP130_ENABLE_SYM_ALGO_AES_XTS
#define PSA_REMOVE_SYM_ALGO_AES_XTS
#endif
#ifndef EIP130_ENABLE_SYM_ALGO_AES_CCM
#define PSA_REMOVE_SYM_ALGO_AES_CCM
#endif
#ifndef EIP130_ENABLE_SYM_ALGO_AES_GCM
#define PSA_REMOVE_SYM_ALGO_AES_GCM
#endif
#ifndef EIP130_ENABLE_SYM_ALGO_AES_F8
#define PSA_REMOVE_SYM_ALGO_AES_F8
#endif

#ifndef EIP130_ENABLE_SYM_ALGO_DES
#define PSA_REMOVE_SYM_ALGO_DES
#endif
#ifndef EIP130_ENABLE_SYM_ALGO_3DES
#define PSA_REMOVE_SYM_ALGO_3DES
#endif

#ifndef EIP130_ENABLE_SYM_ALGO_CHACHA20
#define PSA_REMOVE_SYM_ALGO_CHACHA20
#endif

#ifndef EIP130_ENABLE_SYM_ALGO_SM4
#define PSA_REMOVE_SYM_ALGO_SM4
#define PSA_REMOVE_SYM_SM4KEYWRAP
#define PSA_REMOVE_SYM_ALGO_SM4_GCM
#else
#ifndef EIP130_ENABLE_SYM_ALGO_SM4_GCM
#define PSA_REMOVE_SYM_ALGO_SM4_GCM
#endif
#endif

#ifndef EIP130_ENABLE_SYM_ALGO_ARIA
#define PSA_REMOVE_SYM_ALGO_ARIA
#define PSA_REMOVE_SYM_ALGO_ARIA_XTS
#define PSA_REMOVE_SYM_ALGO_ARIA_CCM
#define PSA_REMOVE_SYM_ALGO_ARIA_GCM
#define PSA_REMOVE_SYM_ALGO_ARIA_F8
#define PSA_REMOVE_TRNG_CONFIG_ARIA
#else
#define PSA_REMOVE_SYM_ALGO_ARIA_F8
#define PSA_REMOVE_SYM_ALGO_ARIA_XTS
#ifndef EIP130_ENABLE_SYM_ALGO_ARIA_CCM
#define PSA_REMOVE_SYM_ALGO_ARIA_CCM
#endif
#ifndef EIP130_ENABLE_SYM_ALGO_ARIA_GCM
#define PSA_REMOVE_SYM_ALGO_ARIA_GCM
#endif
#endif

#if !defined(EIP130_ENABLE_SYM_KEYWRAP_AES) && \
    !defined(EIP130_ENABLE_SYM_KEYWRAP_SM4)
#define PSA_REMOVE_SYM_KEYWRAP
#endif

// - Asymmetric crypto related
#if !defined(EIP130_ENABLE_ASYM_ALGO_ECDH) && \
    !defined(EIP130_ENABLE_ASYM_ALGO_ECDSA)
#define PSA_REMOVE_ASYM_ECC_GEN_KEYPAIR
#define PSA_REMOVE_ASYM_ECC_GEN_PUBLICKEY
#define PSA_REMOVE_ASYM_ECC_KEY_CHECK
#endif

#ifndef EIP130_ENABLE_ASYM_ALGO_ECDH
#define PSA_REMOVE_ASYM_ECDH_GEN_SHAREDSECRET_SINGLE
#define PSA_REMOVE_ASYM_ECDH_GEN_SHAREDSECRET_DUAL
#endif

#ifndef EIP130_ENABLE_ASYM_ALGO_ECDSA
#define PSA_REMOVE_ASYM_ECDSA_SIGN
#define PSA_REMOVE_ASYM_ECDSA_VERIFY
#endif

#ifndef EIP130_ENABLE_ASYM_ALGO_CURVE25519
#define PSA_REMOVE_ASYM_CURVE25519
#endif

#ifndef EIP130_ENABLE_ASYM_ALGO_EDDSA
#define PSA_REMOVE_ASYM_EDDSA_SIGN
#define PSA_REMOVE_ASYM_EDDSA_VERIFY
#endif

#ifndef EIP130_ENABLE_ASYM_ALGO_DH
#define PSA_REMOVE_ASYM_DH_GEN_KEYPAIR
#define PSA_REMOVE_ASYM_DH_GEN_PUBLICKEY
#define PSA_REMOVE_ASYM_DH_KEY_CHECK

#define PSA_REMOVE_ASYM_DH_GEN_SHAREDSECRET_SINGLE
#define PSA_REMOVE_ASYM_DH_GEN_SHAREDSECRET_DUAL
#endif

#ifndef EIP130_ENABLE_ASYM_ALGO_RSA
#define PSA_REMOVE_ASYM_RSAPKCS1V15_SIGN
#define PSA_REMOVE_ASYM_RSAPKCS1V15_VERIFY
#define PSA_REMOVE_ASYM_RSAPSS_SIGN
#define PSA_REMOVE_ASYM_RSAPSS_VERIFY
#define PSA_REMOVE_ASYM_RSA_OAEP
#endif

#ifndef EIP130_ENABLE_ASYM_ALGO_SM2
#define PSA_REMOVE_ASYM_SM2DSA_SIGN
#define PSA_REMOVE_ASYM_SM2DSA_VERIFY
#define PSA_REMOVE_ASYM_SM2KEX_GEN_SHARED_SECRET
#define PSA_REMOVE_ASYM_SM2ENC
#endif

#ifndef EIP130_ENABLE_ASYM_ALGO_ECIES
#define PSA_REMOVE_ASYM_ECIES
#endif

// - Random related

// - Miscellaneous

// - Special Functions related

// - Service related

// - System related

// - Claim control related


#endif /* INCLUDE_GUARD_CS_ADAPTER_PSA_H */

/* end of file cs_adapter_psa.h */
