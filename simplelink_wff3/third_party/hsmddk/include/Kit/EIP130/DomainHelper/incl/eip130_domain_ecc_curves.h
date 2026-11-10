/* eip130_domain_ecc_curves.h
 *
 * Standard (pre-defined) ECC curves interface.
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

#ifndef INCLUDE_GUARD_EIP130DOMAIN_ECC_CURVES_H
#define INCLUDE_GUARD_EIP130DOMAIN_ECC_CURVES_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint8_t, etc. */


/* Eip130Domain_ECCurveFamily_t - Elliptic Curve families */
typedef uint8_t Eip130Domain_ECCurveFamily_t;

#define EIP130DOMAIN_ECC_FAMILY_NONE             0U
#define EIP130DOMAIN_ECC_FAMILY_NIST_P           1U
#define EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1     2U
#define EIP130DOMAIN_ECC_FAMILY_MONTGOMERY       3U
#define EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS  4U
#define EIP130DOMAIN_ECC_FAMILY_SM2              5U


/*----------------------------------------------------------------------------
 * Eip130Domain_ECC_GetCurve
 *
 * This function returns the curve parameters for the requested (standard) EC
 * curve.
 *
 * CurveFamily
 *     The family of the requested EC curve.
 *     (Please, see Eip130Domain_ECCurveFamily_t)
 *
 * CurveBits
 *      Size of the EC curve in bits
 *
 * pCurveParams
 *     Pointer that will point to the curve parameters or NULL on return.
 *
 * pCurveParamsSize
 *     Pointer that points to a size variable that will hold the size of
 *     the returned curve parameters in bytes.
 *
 * Return Value:
 *     false: If curve is not found/supported
 *     true:  If curve is found/supported
 */
bool
Eip130Domain_ECC_GetCurve(const Eip130Domain_ECCurveFamily_t CurveFamily,
                          const uint32_t CurveBits,
                          const uint8_t ** ppCurveParams,
                          uint32_t * pCurveParamsSize);


#endif /* INCLUDE_GUARD_EIP130DOMAIN_ECC_CURVES_H */

/* end of file eip130_domain_ecc_curves.h */
