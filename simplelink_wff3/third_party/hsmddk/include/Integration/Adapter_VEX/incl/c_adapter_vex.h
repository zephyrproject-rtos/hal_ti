/* c_adapter_vex.h
 *
 * Configuration options for the VEX API driver
 * The project-specific cs_adapter_vex.h file is included,
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

#ifndef INCLUDE_GUARD_C_ADAPTER_VEX_H
#define INCLUDE_GUARD_C_ADAPTER_VEX_H

/*----------------------------------------------------------------
 * Defines that can be used in the cs_xxx.h file
 */

/* currently none */


/*----------------------------------------------------------------
 *  cs_adapter_vex.h inclusion
 */
#include <third_party/hsmddk/include/Config/cs_adapter_vex.h>

#ifndef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX  LOG_SEVERITY_WARN
#endif

#ifndef VEX_DEVICE_NAME
/* Set the default device name to use */
#define VEX_DEVICE_NAME "EIP130"
#endif

#ifndef VEX_LOG_PREFIX
#define VEX_LOG_PREFIX  "VEX: "
#endif

#ifndef VEX_FIRMWARE_FILE
/* Set the default firmware image filename */
#define VEX_FIRMWARE_FILE  "firmware_eip130ram.sbi"
#endif

#ifndef VEX_MAILBOX_NR
/* Set the default mailbox to use */
#define VEX_MAILBOX_NR  1U
#endif

#ifndef VEX_CRYPTO_OFFICER_ID
/* Set the default Crypto Officer ID to use */
#define VEX_CRYPTO_OFFICER_ID  0x4F5A3647
#endif

#ifndef VEX_POLLING_SKIP_FIRST_DELAYS
/* Set the default */
#define VEX_POLLING_SKIP_FIRST_DELAYS  50
#endif

#ifndef VEX_POLLING_DELAY_MS
/* Set the default */
#define VEX_POLLING_DELAY_MS  1
#endif

#ifndef VEX_POLLING_MAXLOOPS
/*  Set the default */
#define VEX_POLLING_MAXLOOPS  5000
#endif

#if defined(VEX_TRACE_TOKENS) || defined(VEX_TRACE_TOKENS_ERROR)
#ifdef VEX_TRACE_TOKENS
#if VEX_TRACE_TOKENS > 0
/* Disable token result error tracing to enable specified token tracing */
#ifdef VEX_TRACE_TOKENS_ERROR
#undef VEX_TRACE_TOKENS_ERROR
#endif
#define VEX_TRACE_TOKENS_ERROR 0
#else
#ifndef VEX_TRACE_TOKENS_ERROR
/* No token tracing */
#define VEX_TRACE_TOKENS_ERROR 0
#endif
#endif
#else
/* Disable token tracing to enable specified token result error tracing */
#define VEX_TRACE_TOKENS       0
#endif
#else
/* No token tracing */
#define VEX_TRACE_TOKENS       0
#define VEX_TRACE_TOKENS_ERROR 0
#endif

#endif /* INCLUDE_GUARD_C_ADAPTER_VEX_H */

/* end of file c_adapter_vex.h */
