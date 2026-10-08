/* testvectors_ecc_curves.h
 *
 * Description: Structure for the ECC curves.
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

#ifndef INCLUDE_GUARD_TESTVECTORS_ECC_CURVES_H
#define INCLUDE_GUARD_TESTVECTORS_ECC_CURVES_H

#include <third_party/hsmddk/include/Config/cs_eip130.h>

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

/* Following defines are identical to ones used in VAL/PSA API */
#define TV_ECC_FAMILY_NONE             0U
#define TV_ECC_FAMILY_NIST_P           1U
#define TV_ECC_FAMILY_BRAINPOOL_R1     2U
#define TV_ECC_FAMILY_MONTGOMERY       3U
#define TV_ECC_FAMILY_TWISTED_EDWARDS  4U
#define TV_ECC_FAMILY_SM2              5U

/* Structures for the ECC curves. */
typedef struct
{
    uint32_t Family;
    uint32_t CurveBits;
    const uint8_t * P_p;
    uint32_t PLen;
    const uint8_t * A_p;
    uint32_t ALen;
    const uint8_t * B_p;
    uint32_t BLen;
    const uint8_t * ECPointX_p;
    uint32_t ECPointXLen;
    const uint8_t * ECPointY_p;
    uint32_t ECPointYLen;
    const uint8_t * Order_p;
    uint32_t OrderLen;
    const uint8_t Cofactor;
} TestVector_ECC_Curve_Rec_t;

typedef const TestVector_ECC_Curve_Rec_t * const TestVector_ECC_Curve_t;

#ifdef REMOVE_IFDEF_WHEN_USE_IS_REQUIRED
extern const TestVector_ECC_Curve_Rec_t ECurve_SEC_P128r1;
extern TestVector_ECC_Curve_t ECC_Curve_SEC_P128r1;
#endif
#ifdef REMOVE_IFDEF_WHEN_USE_IS_REQUIRED
extern const TestVector_ECC_Curve_Rec_t ECurve_SEC_P128r2;
extern TestVector_ECC_Curve_t ECC_Curve_SEC_P128r2;
#endif
#ifdef REMOVE_IFDEF_WHEN_USE_IS_REQUIRED
extern const TestVector_ECC_Curve_Rec_t ECurve_SEC_P160r1;
extern TestVector_ECC_Curve_t ECC_Curve_SEC_P160r1;
#endif
extern const TestVector_ECC_Curve_Rec_t ECurve_NIST_P192;
extern TestVector_ECC_Curve_t ECC_Curve_NIST_P192;
extern const TestVector_ECC_Curve_Rec_t ECurve_NIST_P224;
extern TestVector_ECC_Curve_t ECC_Curve_NIST_P224;
extern const TestVector_ECC_Curve_Rec_t ECurve_NIST_P256;
extern TestVector_ECC_Curve_t ECC_Curve_NIST_P256;
extern const TestVector_ECC_Curve_Rec_t ECurve_NIST_P384;
extern TestVector_ECC_Curve_t ECC_Curve_NIST_P384;
extern const TestVector_ECC_Curve_Rec_t ECurve_NIST_P521;
extern TestVector_ECC_Curve_t ECC_Curve_NIST_P521;
#ifdef EIP130_ENABLE_ASYM_ALGO_CURVE25519
extern const TestVector_ECC_Curve_Rec_t ECurve_25519;
extern TestVector_ECC_Curve_t ECC_Curve_25519;
#endif
#ifdef EIP130_ENABLE_ASYM_ALGO_EDDSA
extern const TestVector_ECC_Curve_Rec_t ECurve_Ed25519;
extern TestVector_ECC_Curve_t ECC_Curve_Ed25519;
#endif
#ifdef EIP130_ENABLE_ASYM_ALGO_SM2
extern const TestVector_ECC_Curve_Rec_t ECurve_SM2_Fp_256;
extern TestVector_ECC_Curve_t ECC_Curve_SM2_Fp_256;
extern const TestVector_ECC_Curve_Rec_t ECurve_SM2_Fp_192;
extern TestVector_ECC_Curve_t ECC_Curve_SM2_Fp_192;
#endif

#endif /* INCLUDE_GUARD_TESTVECTORS_ECC_CURVES_H */

/* end of file testvectors_ecc_curves.h */
