/* basic_defs.h
 *
 * Driver Framework v4, Basic Definitions.
 *
 * This file provides a number of basic definitions and can be customized for
 * any compiler.
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

#ifndef INCLUDE_GUARD_BASIC_DEFS_H
#define INCLUDE_GUARD_BASIC_DEFS_H


/* ============ Compiler-based Configuration ============ */
#ifdef __cplusplus
#error "BasicDefs: C++ standard not supported"
#endif

#ifdef _MSC_VER
#define BASICDEFS_COMPILER_MICROSOFT_V1
#define BASICDEFS_TYPES_V1
#define BASICDEFS_BOOL_V1
// Microsoft compiler only supports "inline" in C++ mode and
// expects __inline in C mode
#define BASICDEFS_INLINE_V1
#endif

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L
#define BASICDEFS_TYPES_STDINT
#define BASICDEFS_BOOL_V1
#define BASICDEFS_INLINE_BUILTIN
#endif
#endif

#ifdef __CYGWIN__
#define BASICDEFS_COMPILER_CYGWIN_V1
#define BASICDEFS_TYPES_STDINT
#define BASICDEFS_BOOL_V1
#define BASICDEFS_INLINE_BUILTIN
#endif

#ifdef linux
#ifdef MODULE
// kernel loadable module
#define BASICDEFS_COMPILER_LINUX_V1
#define BASICDEFS_INLINE_BUILTIN
#include <linux/types.h>
#include <linux/version.h>
#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#endif /* KERNEL_VERSION */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,16,0)
#undef BASICDEFS_TYPES_STDINT
#undef BASICDEFS_BOOL_V1
#endif
#else
// user mode
#define BASICDEFS_COMPILER_LINUX_V1
#define BASICDEFS_TYPES_STDINT
#define BASICDEFS_BOOL_V1
#define BASICDEFS_INLINE_BUILTIN
#endif
#endif

/* ============ Boolean type ============ */

#ifdef BASICDEFS_BOOL_V1
// ISO-C99
#include <stdbool.h>
#endif

/* ============ Basic Types ============ */

#ifdef BASICDEFS_TYPES_STDINT
// ISO-C99
#include <stdint.h>
#endif

#ifdef BASICDEFS_TYPES_V1
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
#endif

// Depends on the build, it is going to be 32 or 64 bit
typedef unsigned long ulong_t;
typedef long long int llint_t;
typedef long int lint_t;

/* ============ NULL ============ */

#ifndef NULL
#define NULL 0
#endif

/* ============ MIN, MAX ============ */

// warning for side-effects on the following two macros since the arguments
// are evaluated twice changing this to inline functions is problematic
// because of type incompatibilities
#ifndef MIN
#define MIN(_x, _y) ((_x) < (_y) ? (_x) : (_y))
#endif

#ifndef MAX
#define MAX(_x, _y) ((_x) > (_y) ? (_x) : (_y))
#endif

/* ============ BIT_n ============ */

// using postfix "U" to be compatible with uint32
// ("UL" is not needed and gives lint warning)
#define BIT_0   ((uint32_t)0x00000001U)
#define BIT_1   ((uint32_t)0x00000002U)
#define BIT_2   ((uint32_t)0x00000004U)
#define BIT_3   ((uint32_t)0x00000008U)
#define BIT_4   ((uint32_t)0x00000010U)
#define BIT_5   ((uint32_t)0x00000020U)
#define BIT_6   ((uint32_t)0x00000040U)
#define BIT_7   ((uint32_t)0x00000080U)
#define BIT_8   ((uint32_t)0x00000100U)
#define BIT_9   ((uint32_t)0x00000200U)
#define BIT_10  ((uint32_t)0x00000400U)
#define BIT_11  ((uint32_t)0x00000800U)
#define BIT_12  ((uint32_t)0x00001000U)
#define BIT_13  ((uint32_t)0x00002000U)
#define BIT_14  ((uint32_t)0x00004000U)
#define BIT_15  ((uint32_t)0x00008000U)
#define BIT_16  ((uint32_t)0x00010000U)
#define BIT_17  ((uint32_t)0x00020000U)
#define BIT_18  ((uint32_t)0x00040000U)
#define BIT_19  ((uint32_t)0x00080000U)
#define BIT_20  ((uint32_t)0x00100000U)
#define BIT_21  ((uint32_t)0x00200000U)
#define BIT_22  ((uint32_t)0x00400000U)
#define BIT_23  ((uint32_t)0x00800000U)
#define BIT_24  ((uint32_t)0x01000000U)
#define BIT_25  ((uint32_t)0x02000000U)
#define BIT_26  ((uint32_t)0x04000000U)
#define BIT_27  ((uint32_t)0x08000000U)
#define BIT_28  ((uint32_t)0x10000000U)
#define BIT_29  ((uint32_t)0x20000000U)
#define BIT_30  ((uint32_t)0x40000000U)
#define BIT_31  ((uint32_t)0x80000000U)

/* ============ MASK_n_BITS ============ */

#define MASK_1_BIT      (BIT_1 - 1U)
#define MASK_2_BITS     (BIT_2 - 1U)
#define MASK_3_BITS     (BIT_3 - 1U)
#define MASK_4_BITS     (BIT_4 - 1U)
#define MASK_5_BITS     (BIT_5 - 1U)
#define MASK_6_BITS     (BIT_6 - 1U)
#define MASK_7_BITS     (BIT_7 - 1U)
#define MASK_8_BITS     (BIT_8 - 1U)
#define MASK_9_BITS     (BIT_9 - 1U)
#define MASK_10_BITS    (BIT_10 - 1U)
#define MASK_11_BITS    (BIT_11 - 1U)
#define MASK_12_BITS    (BIT_12 - 1U)
#define MASK_13_BITS    (BIT_13 - 1U)
#define MASK_14_BITS    (BIT_14 - 1U)
#define MASK_15_BITS    (BIT_15 - 1U)
#define MASK_16_BITS    (BIT_16 - 1U)
#define MASK_17_BITS    (BIT_17 - 1U)
#define MASK_18_BITS    (BIT_18 - 1U)
#define MASK_19_BITS    (BIT_19 - 1U)
#define MASK_20_BITS    (BIT_20 - 1U)
#define MASK_21_BITS    (BIT_21 - 1U)
#define MASK_22_BITS    (BIT_22 - 1U)
#define MASK_23_BITS    (BIT_23 - 1U)
#define MASK_24_BITS    (BIT_24 - 1U)
#define MASK_25_BITS    (BIT_25 - 1U)
#define MASK_26_BITS    (BIT_26 - 1U)
#define MASK_27_BITS    (BIT_27 - 1U)
#define MASK_28_BITS    (BIT_28 - 1U)
#define MASK_29_BITS    (BIT_29 - 1U)
#define MASK_30_BITS    (BIT_30 - 1U)
#define MASK_31_BITS    (BIT_31 - 1U)

#define MASK_N_BITS(start, end) ((-1U >> (31 - (end))) & ~((1U << (start)) - 1U))

/* ============ EXTRACT_BIT(S) ============ */
#define EXTRACT_BIT(bit, input)         (((input) >> (bit)) & 1U)
#define EXTRACT_BITS(start, end, input) (((input) >> (start)) & MASK_N_BITS(0, (end) - (start)))

/* ============ IDENTIFIER_NOT_USED ============ */

#define IDENTIFIER_NOT_USED(_v)   (void)(_v)

/* ============ inline ============ */

#ifdef BASICDEFS_INLINE_V1
#define inline __inline
#endif


/* ============ COMPILE_STATIC_ASSERT ============ */
/*
 * Macro to make function scope compile time assertions. The condition
 * must be a constant C expression (expression that can be evaluated
 * at compile time) evaluating to true when the required condition
 * holds and to false otherwise.
 *
 * When condition evaluates to true the macro has no effect.
 *
 * When condition evaluates to false the compilation fails due to
 * declaration of arrays of size -1.
 */
#define COMPILE_STATIC_ASSERT(condition)                                         \
    do {                                                                         \
        const int32_t static_assertion[1 - (2 * ((condition) ? 0 : 1))] = { 1 }; \
        if (static_assertion[0] == 0)                                            \
        { /* Nothing */ }                                                        \
        else                                                                     \
        { /* Nothing */ }                                                        \
    } while (false)


#endif /* INCLUDE_GUARD_BASIC_DEFS_H */

/* end of file basic_defs.h */
