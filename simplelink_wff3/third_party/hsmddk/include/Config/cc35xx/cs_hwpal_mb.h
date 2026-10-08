/** cs_hwpal_mb.h
 *
 * Configuration Settings for the hardware platform abstraction layer
 * intended for the Linux user-space.
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

#ifndef INCLUDE_GUARD_CS_HWPAL_MB_H
#define INCLUDE_GUARD_CS_HWPAL_MB_H

/**----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include <third_party/hsmddk/include/Config/cs_hwpal_umdevxs.h>


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// TI Modification: MOST OF THESE MACROS ARE DEFINED ELSEWHERE

// DMA memory not used for D-cache
//#ifndef HWPAL_ARCH_COHERENT
//#define HWPAL_ARCH_COHERENT
//#endif

// Performance optimizations
//#define HWPAL_DMARES_UMDEVXS_OPT1
//#define HWPAL_DMARES_UMDEVXS_OPT2

// Log DMA buffer operations details
//#define HWPAL_TRACE_DMARESOURCE_BUF

// Detect DMA resource leaks
//#define HWPAL_TRACE_DMARESOURCE_LEAKS

// Lowest allowed DMA address
// #define HWPAL_DMARESOURCE_DMA_ADDR_MIN      0x20000000U

// Highest allowed DMA address
// #define HWPAL_DMARESOURCE_DMA_ADDR_MAX      0x3FFFFFFFU

// Logging level that DMAResource_CheckAndRegister() function will use
// for reporting errors that can be considered warnings otherwise
#define HWPAL_DMARESOURCE_LOG_LEVEL         LOG_INFO


#endif /* INCLUDE_GUARD_CS_HWPAL_MB_H */

/* end of file cs_hwpal_mb.h */
