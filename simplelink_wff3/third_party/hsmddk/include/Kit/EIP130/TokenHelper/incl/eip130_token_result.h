/* eip130_token_result.h
 *
 * Security Module Token helper result code definitions
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_RESULT_H
#define INCLUDE_GUARD_EIP130TOKEN_RESULT_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* int32_t, BIT_16, etc. */

/* The token result code is comprised of the FIPS-Approved service indication
 * and a success, warning or error indication.
 * In general (not looking at the FIPS-Approved service indication):
 *      0   Success/No error
 *     >0   Warning code
 *     <0   Error code
 */
/*typedef int32_t Eip130Token_Result_Codes_t;*/

/*----------------------------------------------------------------------------
 * The common result codes ranges and their most common warnings and errors.
 */
/** [1 .. 127]: The reserved for propagating the EIP-130 firmware warnings */

/** TRNG related warnings [64 ... 95]: None expected */

/** DMA related warnings [32 ... 63]: None expected */

/** Firmware related warnings [1 ... 31]: */
#define EIP130TOKEN_RESULT_WARNING_Z1USED       (16)    /** Z=1 is used */

/** Success */
#define EIP130TOKEN_RESULT_SUCCESS              (0)     /** No error */

/** [-1 .. -127]: The reserved for propagating the EIP-130 firmware error */
/** Firmware related errors [-1 ... -31]: */
#define EIP130TOKEN_RESULT_INVALID_TOKEN        (-1)    /** Invalid token */
#define EIP130TOKEN_RESULT_INVALID_PARAMETER    (-2)    /** Invalid parameter */
#define EIP130TOKEN_RESULT_INVALID_KEYSIZE      (-3)    /** Invalid key size */
#define EIP130TOKEN_RESULT_INVALID_LENGTH       (-4)    /** Invalid length */
#define EIP130TOKEN_RESULT_INVALID_LOCATION     (-5)    /** Invalid location */
#define EIP130TOKEN_RESULT_CLOCK_ERROR          (-6)    /** Clock error */
#define EIP130TOKEN_RESULT_ACCESS_ERROR         (-7)    /** Access error */
#define EIP130TOKEN_RESULT_UNWRAP_ERROR         (-10)   /** Unwrap error */
#define EIP130TOKEN_RESULT_DATA_OVERRUN_ERROR   (-11)   /** Data overrun error */
#define EIP130TOKEN_RESULT_ASSET_CHECKSUM_ERROR (-12)   /** Asset checksum error */
#define EIP130TOKEN_RESULT_INVALID_ASSET        (-13)   /** Invalid Asset */
#define EIP130TOKEN_RESULT_FULL_ERROR           (-14)   /** Full/Overflow error */
#define EIP130TOKEN_RESULT_INVALID_ADDRESS      (-15)   /** Invalid address */
#define EIP130TOKEN_RESULT_INVALID_MODULUS      (-17)   /** Invalid Modulus */
#define EIP130TOKEN_RESULT_VERIFY_ERROR         (-18)   /** Verify error */
#define EIP130TOKEN_RESULT_INVALID_STATE        (-19)   /** Invalid state */
#define EIP130TOKEN_RESULT_OTP_WRITE_ERROR      (-20)   /** OTP write error */
#define EIP130TOKEN_RESULT_ASSET_EXPIRED        (-21)   /** Asset Lifetime has expired */
#define EIP130TOKEN_RESULT_COPROCESSOR_IF_ERROR (-22)   /** Coprocessor interface error */
#define EIP130TOKEN_RESULT_PANIC_ERROR          (-31)   /** Panic error */

/** DMA related errors are bus related [-32 ... -63]: Bus specific error */

/** TRNG related errors [-64 ... -95]: */
#define EIP130TOKEN_RESULT_TRNG_SHUTDOWN_ERROR  (-65)   /** Too many FROs shutdown */
#define EIP130TOKEN_RESULT_DRBG_STUCK_ERROR     (-66)   /** Stuck DRBG */

/** The FIPS-Approved service indication */
#define EIP130TOKEN_RESULT_FASVC                (BIT_16)


#endif /* INCLUDE_GUARD_EIP130TOKEN_RESULT_H */

/* end of file eip130_token_result.h */
