/* c_dmares_gen.h
 *
 * Default configuration for generic Driver Framework DMAResource API
 * implementation.
 *
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

#ifndef INCLUDE_GUARD_C_DMARES_GEN_H
#define INCLUDE_GUARD_C_DMARES_GEN_H


/*----------------------------------------------------------------
 * get configuration settings from product config file
 */
#include <third_party/hsmddk/include/Config/cs_hwpal.h>

// choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT
#ifndef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX LOG_SEVERITY_INFO
#endif

#ifdef HWPAL_DMARESOURCE_BANKS_ENABLE
#ifndef HWPAL_DMARESOURCE_BANKS
#error "Expected HWPAL_DMARESOURCE_BANKS defined by cs_hwpal.h"
#endif
#endif // HWPAL_DMARESOURCE_BANKS_ENABLE

// Enable use of UMDevXS device
#ifdef HWPAL_USE_UMDEVXS_DEVICE
#define HWPAL_DMARESOURCE_USE_UMDEVXS_DEVICE
#endif // HWPAL_USE_UMDEVXS_DEVICE

/*----------------------------------------------------------------
 * Other configuration parameters that can be set in a top level
 * configuration
 */

// Enables DMA resources banks so that different memory regions can be used
// for DMA buffer allocation
//#define HWPAL_DMARESOURCE_BANKS_ENABLE

#ifndef HWPAL_DMARESOURCE_DMA_ALIGNMENT_BYTE_COUNT
#ifdef HWPAL_DMARESOURCE_64BIT
// Default 8 bytes (64 bits) address alignment
#define HWPAL_DMARESOURCE_DMA_ALIGNMENT_BYTE_COUNT      8
#else
// Default 4 bytes (32 bits) address alignment
#define HWPAL_DMARESOURCE_DMA_ALIGNMENT_BYTE_COUNT      4
#endif
#endif

// When defined enables strict argument checking
//#define HWPAL_DMARESOURCE_STRICT_ARGS_CHECKS


#endif /* INCLUDE_GUARD_C_DMARES_GEN_H */

/* end of file c_dmares_gen.h */
