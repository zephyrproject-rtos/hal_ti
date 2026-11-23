/**
 * \file psa/crypto_extra.h
 *
 * \brief PSA cryptography module: vendor extensions
 *
 * \note This file may not be included directly. Applications must
 * include psa/crypto.h.
 *
 * This file is reserved for vendor-specific definitions.
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
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/* Mbed TLS copyright added because function declaration & description is from their code */
#ifndef PSA_CRYPTO_EXTRA_H
#define PSA_CRYPTO_EXTRA_H

#include <stdint.h>

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto_types.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto_compat.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup crypto_types
 * @{
 */

/** DSA public key.
 *
 * The import and export format is the
 * representation of the public key `y = g^x mod p` as a big-endian byte
 * string. The length of the byte string is the length of the base prime `p`
 * in bytes.
 */
#define PSA_KEY_TYPE_DSA_PUBLIC_KEY                 ((psa_key_type_t)0x4002U)

/** DSA key pair (private and public key).
 *
 * The import and export format is the
 * representation of the private key `x` as a big-endian byte string. The
 * length of the byte string is the private key size in bytes (leading zeroes
 * are not stripped).
 *
 * Determinstic DSA key derivation with psa_generate_derived_key follows
 * FIPS 186-4 &sect;B.1.2: interpret the byte string as integer
 * in big-endian order. Discard it if it is not in the range
 * [0, *N* - 2] where *N* is the boundary of the private key domain
 * (the prime *p* for Diffie-Hellman, the subprime *q* for DSA,
 * or the order of the curve's base point for ECC).
 * Add 1 to the resulting integer and use this as the private key *x*.
 *
 */
#define PSA_KEY_TYPE_DSA_KEY_PAIR                    ((psa_key_type_t)0x7002U)

/**@}*/

/**
 * \brief Set domain parameters for a key.
 *
 * Some key types require additional domain parameters in addition to
 * the key type identifier and the key size. Use this function instead
 * of psa_set_key_type() when you need to specify domain parameters.
 *
 * The format for the required domain parameters varies based on the key type.
 *
 * - For RSA keys (#PSA_KEY_TYPE_RSA_PUBLIC_KEY or #PSA_KEY_TYPE_RSA_KEY_PAIR),
 *   the domain parameter data consists of the public exponent,
 *   represented as a big-endian integer with no leading zeros.
 *   This information is used when generating an RSA key pair.
 *   When importing a key, the public exponent is read from the imported
 *   key data and the exponent recorded in the attribute structure is ignored.
 *   As an exception, the public exponent 65537 is represented by an empty
 *   byte string.
 * - For DSA keys (#PSA_KEY_TYPE_DSA_PUBLIC_KEY or #PSA_KEY_TYPE_DSA_KEY_PAIR),
 *   the `Dss-Params` format as defined by RFC 3279 &sect;2.3.2.
 *   ```
 *   Dss-Params ::= SEQUENCE  {
 *      p       INTEGER,
 *      q       INTEGER,
 *      g       INTEGER
 *   }
 *   ```
 * - For Diffie-Hellman key exchange keys
 *   (#PSA_KEY_TYPE_DH_PUBLIC_KEY(#PSA_DH_FAMILY_CUSTOM) or
 *   #PSA_KEY_TYPE_DH_KEY_PAIR(#PSA_DH_FAMILY_CUSTOM)), the
 *   `DomainParameters` format as defined by RFC 3279 &sect;2.3.3.
 *   ```
 *   DomainParameters ::= SEQUENCE {
 *      p               INTEGER,                    -- odd prime, p=jq +1
 *      g               INTEGER,                    -- generator, g
 *      q               INTEGER,                    -- factor of p-1
 *      j               INTEGER OPTIONAL,           -- subgroup factor
 *      validationParams ValidationParams OPTIONAL
 *   }
 *   ValidationParams ::= SEQUENCE {
 *      seed            BIT STRING,
 *      pgenCounter     INTEGER
 *   }
 *   ```
 *
 * \note This function may allocate memory or other resources.
 *       Once you have called this function on an attribute structure,
 *       you must call psa_reset_key_attributes() to free these resources.
 *
 * \note This is an experimental extension to the interface. It may change
 *       in future versions of the library.
 *
 * \param[in,out] attributes    Attribute structure where the specified domain
 *                              parameters will be stored.
 *                              If this function fails, the content of
 *                              \p attributes is not modified.
 * \param type                  Key type (a \c PSA_KEY_TYPE_XXX value).
 * \param[in] data              Buffer containing the key domain parameters.
 *                              The content of this buffer is interpreted
 *                              according to \p type as described above.
 * \param data_length           Size of the \p data buffer in bytes.
 *
 * \retval #PSA_SUCCESS \emptydescription
 * \retval #PSA_ERROR_INVALID_ARGUMENT \emptydescription
 * \retval #PSA_ERROR_NOT_SUPPORTED \emptydescription
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY \emptydescription
 */
psa_status_t psa_set_key_domain_parameters(psa_key_attributes_t *attributes,
                                           psa_key_type_t type,
                                           const uint8_t *data,
                                           size_t data_length);

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_EXTRA_H */

/* end of file crypto_extra.h */


