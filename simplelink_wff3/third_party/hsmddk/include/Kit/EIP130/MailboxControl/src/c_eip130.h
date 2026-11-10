/* c_eip130.h
 *
 * Configuration options for the EIP130 module.
 * The project-specific cs_eip130.h file is included,
 * whereafter defaults are provided for missing parameters.
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

#ifndef INCLUDE_GUARD_C_EIP130_H
#define INCLUDE_GUARD_C_EIP130_H

/*----------------------------------------------------------------
 * Defines that can be used in the cs_eip130.h file
 */
/* Use this define to enable argument checking of all EIP-130 and token helper
 * functions. When disabled it reduces code size and overhead */
//#define EIP130_STRICT_ARGS

/* Next defines are Hardware / Firmware specific
 * Note that the setting of these defines depend on the used hardware/firmware
 * configuration.
 */
/* - General defines */
//#define EIP130_ENABLE_FIRMWARE_LOAD           /* Enable firmware load functionality */
//#define EIP130_ENABLE_DPA_SUPPORT             /* Hardware has Differential Power Analysis support */
//#define EIP130_ALLOW_MASTER_NONSECURE         /* Hardware allows a non-secure master Host */

/* - Token Group NOP */
//#define EIP130_ENABLE_NOP                     /* Enable NOP functionality */

/* - Token Group Encryption (Symmetric) */
//#define EIP130_ENABLE_SYM_ALGO_AES            /* Enable AES use (Note: Enabled by default) */
//#define EIP130_ENABLE_SYM_ALGO_AES_XTS        /* Enable XTS-AES use */
//#define EIP130_ENABLE_SYM_ALGO_AES_CCM        /* Enable AES-CCM use */
//#define EIP130_ENABLE_SYM_ALGO_AES_GCM        /* Enable AES_GCM use */
//#define EIP130_ENABLE_SYM_ALGO_AES_F8         /* Enable AES-f8 use */

//#define EIP130_ENABLE_SYM_ALGO_DES            /* Enable DES use */
//#define EIP130_ENABLE_SYM_ALGO_3DES           /* Enable Triple DES (3DES) use */

//#define EIP130_ENABLE_SYM_ALGO_CHACHA20       /* Enable ChaCha20 use */

//#define EIP130_ENABLE_SYM_ALGO_ARIA           /* Enable ARIA use */
//#define EIP130_ENABLE_SYM_ALGO_ARIA_CCM       /* Enable ARIA-CCM use */
//#define EIP130_ENABLE_SYM_ALGO_ARIA_GCM       /* Enable ARIA-GCM use */

//#define EIP130_ENABLE_SYM_ALGO_SM4            /* Enable SM4 use */
//#define EIP130_ENABLE_SYM_ALGO_SM4_GCM        /* Enable SM4-GCM use */

/* - Token Group Hash (Symmetric) */
//#define EIP130_ENABLE_SYM_ALGO_SHA512         /* Enable SHA-2-384/512 use */
//#define EIP130_ENABLE_SYM_ALGO_SHA3           /* Enable SHA3 use */
//#define EIP130_ENABLE_SYM_ALGO_SM3            /* Enable SM3 use */

/* - Token Group MAC (Symmetric) */
//#define EIP130_ENABLE_SYM_ALGO_POLY1305       /* Enable Poly1305 use */

/* - Token Group TRNG */
//#define EIP130_ENABLE_DRBG_FORCESEED          /* Enable DRBG Force Seed functionality */
//#define EIP130_ENABLE_SYM_ALGO_ARIA_DRBG      /* Enable ARIA-CTR-DRBG use */

/* - Token Group Special Functions */
//#define EIP130_ENABLE_SF_MILENAGE             /* Enable Special Functions for Milenage */

/* - Token Group Symmetric Wrap */
//#define EIP130_ENABLE_SYM_KEYWRAP_AES         /* Enable AES Keywrap use */
//#define EIP130_ENABLE_SYM_KEYWRAP_SM4         /* Enable SM4 Keywrap use */

/* - Token Group Asset Management */
//#define EIP130_ENABLE_CPIF                    /* Enable CoProcessor Interface functionality */
//#define EIP130_ENABLE_ASSET_STORE_RESET       /* Enable Asset Store reset functionality */

/* - Token Group Authenticated Unlock */

/* - Token Group Public Key operations (Asymmetric) */
//#define EIP130_ENABLE_EXPLICITDIGEST          /* Enable sign/verify explicit digest use */
//#define EIP130_ENABLE_ASYM_ALGO_DH            /* Enable DH use */
//#define EIP130_ENABLE_ASYM_ALGO_ECDH          /* Enable ECDH use */
//#define EIP130_ENABLE_ASYM_ALGO_CURVE25519    /* Enable ECDH based on Curve25519 use */
//#define EIP130_ENABLE_ASYM_ALGO_ECDSA         /* Enable ECDSA use */
//#define EIP130_ENABLE_ASYM_ALGO_EDDSA         /* Enable EDDSA use */
//#define EIP130_ENABLE_ASYM_ALGO_RSA           /* Enable RSA use */
//#define EIP130_ENABLE_ASYM_ALGO_SM2           /* Enable SM2 use */
//#define EIP130_ENABLE_ASYM_ALGO_ECIES         /* Enable ECIES use */

/* - Token Group Service */

/* - Token Group System */
//#define EIP130_ENABLE_FIRMWARE_SLEEP          /* Enable firmware sleep functionality */


/* Special Footprint reduction switches */
//#define EIP130_REMOVE_MAILBOXGETOPTIONS
//#define EIP130_REMOVE_MAILBOXACCESSVERIFY
//#define EIP130_REMOVE_MAILBOXACCESSCONTROL
//#define EIP130_REMOVE_MAILBOXLINK
//#define EIP130_REMOVE_MAILBOXLINKRESET
//#define EIP130_REMOVE_MAILBOXUNLINK
//#define EIP130_REMOVE_MAILBOXCANWRITETOKEN
//#define EIP130_REMOVE_MAILBOXRAWSTATUS
//#define EIP130_REMOVE_MAILBOXRESET
//#define EIP130_REMOVE_MAILBOXLINKID
//#define EIP130_REMOVE_MAILBOXOUTID

//#define EIP130_REMOVE_FIRMWARELOGIN
//#define EIP130_REMOVE_FIRMWARECHECK
//#define EIP130_REMOVE_FIRMWAREDOWNLOAD
//#define EIP130_REMOVE_MODULEFIRMWAREWRITTEN
//#define EIP130_REMOVE_MODULEGETOPTIONS
//#define EIP130_REMOVE_MODULEGETSTATUS
//#define EIP130_REMOVE_MODULEGETVERSION
//#define EIP130_REMOVE_VERSION_OPTION


/*----------------------------------------------------------------
 * inclusion of cs_eip130.h
 */
#include <third_party/hsmddk/include/Config/cs_eip130.h>


/*----------------------------------------------------------------
 * Sanity check of defines
 */
#if defined EIP130_ENABLE_SYM_ALGO_AES_XTS || \
    defined EIP130_ENABLE_SYM_ALGO_AES_CCM || \
    defined EIP130_ENABLE_SYM_ALGO_AES_GCM || \
    defined EIP130_ENABLE_SYM_ALGO_AES_KEYWRAP
#ifndef EIP130_ENABLE_SYM_ALGO_AES
#error "EIP130_ENABLE_SYM_ALGO_AES is required when using AES related functionality"
#endif
#endif

#if defined EIP130_ENABLE_SYM_ALGO_ARIA_CCM || \
    defined EIP130_ENABLE_SYM_ALGO_ARIA_GCM || \
    defined EIP130_ENABLE_SYM_ALGO_ARIA_DRBG
#ifndef EIP130_ENABLE_SYM_ALGO_ARIA
#error "EIP130_ENABLE_SYM_ALGO_ARIA is required when using ARIA related functionality"
#endif
#endif

#if defined EIP130_ENABLE_SYM_ALGO_SM4_GCM
#ifndef EIP130_ENABLE_SYM_ALGO_SM4
#error "EIP130_ENABLE_SYM_ALGO_SM4 is required when using SM4 related functionality"
#endif
#endif

#ifdef EIP130_ENABLE_ASYM_ALGO_EDDSA
#ifndef EIP130_ENABLE_SYM_ALGO_SHA512
#error "EIP130_ENABLE_ASYM_ALGO_EDDSA requires SHA-2-512 functionality"
#endif
#endif

#ifdef EIP130_ENABLE_ASYM_ALGO_SM2
#ifndef EIP130_ENABLE_SYM_ALGO_SM3
#error "EIP130_ENABLE_ASYM_ALGO_SM2 requires SM3 functionality"
#endif
#endif


#endif /* INCLUDE_GUARD_C_EIP130_H */

/* end of file c_eip130.h */
