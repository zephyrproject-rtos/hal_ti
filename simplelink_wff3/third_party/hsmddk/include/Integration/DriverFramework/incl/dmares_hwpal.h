/* dmares_hwpal.h
 *
 * HW and OS abstraction API
 * for the Driver Framework DMAResource API implementation
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

#ifndef INCLUDE_GUARD_DMARES_HWPAL_H
#define INCLUDE_GUARD_DMARES_HWPAL_H


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>         // uint32_t, NULL, inline, bool

// Driver Framework DMAResource Types API
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_types.h>

// Driver Framework C Library abstraction API
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Dynamic flag cannot be mixed with any other HWPAL_DMARESOURCE_BANK_* flags
#define HWPAL_DMARESOURCE_BANK_DYNAMIC                  0U

// Maximum number of supported dynamic DMA banks
#define HWPAL_DMARESOURCE_MAX_NOF_BANKS                 30U

// Static flags can be mixed with each other for the same bank
#define HWPAL_DMARESOURCE_BANK_STATIC                   (HWPAL_DMARESOURCE_MAX_NOF_BANKS + 1U)
#define HWPAL_DMARESOURCE_BANK_STATIC_FIXED_ADDR        (HWPAL_DMARESOURCE_MAX_NOF_BANKS + 3U)

#define HWPAL_DMARESOURCE_BANK_STATIC_LAST              HWPAL_DMARESOURCE_BANK_STATIC_FIXED_ADDR


// Internal DMAResource_Properties_t extension
typedef struct
{
    void * Addr;
    uint32_t BankType;
} HWPAL_DMAResource_Properties_Ext_t;


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MaxAlignment_Get
 */
uint32_t
HWPAL_DMAResource_MaxAlignment_Get(void);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_DCache_Alignment_Get
 */
uint32_t
HWPAL_DMAResource_DCache_Alignment_Get(void);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MemAlloc
 */
void *
HWPAL_DMAResource_MemAlloc(
        size_t ByteCount);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MemFree
 */
void
HWPAL_DMAResource_MemFree(
        void * Buf_p);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Alloc
 */
void *
HWPAL_DMAResource_Lock_Alloc(void);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Free
 */
void
HWPAL_DMAResource_Lock_Free(void * Lock_p);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Acquire
 */
void
HWPAL_DMAResource_Lock_Acquire(
        void * Lock_p,
        ulong_t * Flags);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Release
 */
void
HWPAL_DMAResource_Lock_Release(
        void * Lock_p,
        ulong_t * const Flags);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Alloc
 */
int32_t
HWPAL_DMAResource_Alloc(
        const DMAResource_Properties_t RequestedProperties,
        const HWPAL_DMAResource_Properties_Ext_t RequestedPropertiesExt,
        DMAResource_AddrPair_t * const AddrPair_p,
        DMAResource_Handle_t * const Handle_p);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Release
 */
int32_t
HWPAL_DMAResource_Release(
        const DMAResource_Handle_t Handle);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Init
 */
bool
HWPAL_DMAResource_Init(void);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_UnInit
 */
void
HWPAL_DMAResource_UnInit(void);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_CheckAndRegister
 */
int32_t
HWPAL_DMAResource_CheckAndRegister(
        const DMAResource_Properties_t RequestedProperties,
        const DMAResource_AddrPair_t AddrPair,
        const char AllocatorRef,
        DMAResource_Handle_t * const Handle_p);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Record_Update
 */
int32_t
HWPAL_DMAResource_Record_Update(
        const int32_t Identifier,
        DMAResource_Record_t * const Rec_p);


#endif /* INCLUDE_GUARD_DMARES_HWPAL_H */

/* end of file dmares_hwpal.h */
