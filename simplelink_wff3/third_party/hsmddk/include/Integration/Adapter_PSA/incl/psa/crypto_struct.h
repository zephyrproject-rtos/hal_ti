/**
 * \file psa/crypto_struct.h
 *
 * \brief PSA cryptography module: structured type implementations
 *
 * \note This file may not be included directly. Applications must
 * include psa/crypto.h.
 *
 * This file contains the definitions of some data structures with
 * implementation-specific definitions.
 *
 * In implementations with isolation between the application and the
 * cryptography module, it is expected that the front-end and the back-end
 * would have different versions of this file.
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

/*
 * Copyright (c) 2018-2022, Arm Limited. All rights reserved.
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*
 * TI Customizations: Transitioned psa_client_key_attributes_s to
 * psa_key_attributes_s to match Mbed TLS v3.5. Also changed
 * psa_key_id_t to mbedtls_svc_key_id_t in order to allow for the
 * encoding of the owner along with the key ID.
 */

#ifndef PSA_CRYPTO_STRUCT_H
#define PSA_CRYPTO_STRUCT_H
#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/private_access.h>


/* TI Modifications: Remove content not relevant to DDK code. The DDK houses
 * Key Management and Key Derivation code - only structs related to these
 * items need to be defined here. This allows us to avoid a dependency from
 * the DDK on mbedTLS.
 */
#ifdef __cplusplus
extern "C" {
#endif

/* The type used internally for key sizes.
 * Public interfaces use size_t, but internally a smaller type is used. */
typedef uint16_t psa_key_bits_t;
/* The maximum value of the type used to represent bit-sizes.
 * This is used to mark an invalid key size. */
#define PSA_KEY_BITS_TOO_LARGE ( (psa_key_bits_t) ( -1 ) )
/* The maximum size of a key in bits.
 * Currently defined as the maximum that can be represented, rounded down
 * to a whole number of bytes.
 * This is an uncast value so that it can be used in preprocessor
 * conditionals. */
#define PSA_MAX_KEY_BITS 0xfff8U


struct psa_key_policy_s {
    psa_key_usage_t MBEDTLS_PRIVATE(usage);
    psa_algorithm_t MBEDTLS_PRIVATE(alg);
    psa_algorithm_t MBEDTLS_PRIVATE(alg2);
};
typedef struct psa_key_policy_s psa_key_policy_t;

struct psa_key_attributes_s {
    psa_key_type_t MBEDTLS_PRIVATE(type);
    psa_key_bits_t MBEDTLS_PRIVATE(bits);
    psa_key_lifetime_t MBEDTLS_PRIVATE(lifetime);
    psa_key_policy_t MBEDTLS_PRIVATE(policy);
    /* This type has a different layout in the client view wrt the
     * service view of the key id, i.e. in service view usually is
     * expected to have MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER defined
     * thus adding an owner field to the standard psa_key_id_t. For
     * implementations with client/service separation, this means the
     * object will be marshalled through a transport channel and
     * interpreted differently at each side of the transport. Placing
     * it at the end of structures allows to interpret the structure
     * at the client without reorganizing the memory layout of the
     * struct
     */
    mbedtls_svc_key_id_t MBEDTLS_PRIVATE(id);
};

/* See psa_crypto_client.c for the (also disabled) implementation of this API.
 * We will keep this here for now, but it likely can be removed soon.
 */
#if 0
psa_status_t psa_set_key_domain_parameters(psa_key_attributes_t *attributes,
                                           psa_key_type_t type,
                                           const uint8_t *data,
                                           size_t data_length);
#endif

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_STRUCT_H */

/* end of file crypto_struct.h */
