/** @file cs_hwpal_umdevxs.h
 *
 * @brief Configuration Settings for the hardware platform abstraction layer
 *        intended for the Linux user-space.
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

#ifndef INCLUDE_GUARD_CS_HWPAL_UMDEVXS_H
#define INCLUDE_GUARD_CS_HWPAL_UMDEVXS_H

/*-----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include <third_party/hsmddk/include/Config/cs_hwpal.h>


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#define HWPAL_DEVICE0_UMDEVXS  HWPAL_DEVICE_TO_FIND

// Check if the endianness conversion must be performed
#ifdef DRIVER_SWAPENDIAN
#define HWPAL_DEVICE_ENABLE_SWAP
#endif // DRIVER_SWAPENDIAN

// Enable cache-coherent DMA buffer allocation
#ifdef ARCH_X86
#define HWPAL_DMARESOURCE_ALLOC_CACHE_COHERENT
//#define HWPAL_DMARESOURCE_UMDEVXS_DCACHE_CTRL
#endif // ARCH_X86

#if defined(ARCH_ARM) || defined(ARCH_ARM64)
// Use non-cached DMA buffer allocation and mapping to user-space
#define HWPAL_DMARESOURCE_ALLOC_CACHE_COHERENT

//#define HWPAL_DMARESOURCE_UMDEVXS_DCACHE_CTRL

// Use minimum required cache-control functionality for DMA-safe buffers
//#define HWPAL_DMARESOURCE_MINIMUM_CACHE_CONTROL

// Use low-level instructions to clean and invalidate d-cache
//#define HWPAL_DMARESOURCE_DIRECT_DCACHE_CONTROL

// Enables Data cache control (flush / invalidate cache lines) for the ARM CPU
//#define HWPAL_DMARESOURCE_ARM_DCACHE_CTRL

// D-cache Store Buffer is used
//#define HWPAL_DMARESOURCE_DSB_ENABLE
#endif // defined(ARCH_ARM) || defined(ARCH_ARM64)

#ifdef ARCH_POWERPC
// Use low-level instructions to clean and invalidate d-cache
#define HWPAL_DMARESOURCE_DIRECT_DCACHE_CONTROL
#endif


#endif /* INCLUDE_GUARD_CS_HWPAL_UMDEVXS_H */

/* end of file cs_hwpal_umdevxs.h */
