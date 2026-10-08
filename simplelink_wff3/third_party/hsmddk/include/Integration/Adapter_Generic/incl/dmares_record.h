/* dmares_record.h
 *
 * Driver Framework, DMAResource Record Definition
 *
 * The document "Driver Framework Porting Guide" contains the detailed
 * specification of this API. The information contained in this header file
 * is for reference only.
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

#ifndef INCLUDE_GUARD_DMARES_RECORD_H
#define INCLUDE_GUARD_DMARES_RECORD_H


#include <third_party/hsmddk/include/Config/cs_adapter.h>     // enable switches for conditional fields
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>     // uint8_t, uint32_t

/*----------------------------------------------------------------------------
 * AddrTrans_Domain_t
 *
 * This is a list of domains that can be supported by the implementation.
 * Can be used with variables of the DMAResource_AddrDomain_t type
 *
 */
typedef enum
{
    DMARES_DOMAIN_UNKNOWN = 0,
    DMARES_DOMAIN_HOST,
    DMARES_DOMAIN_HOST_UNALIGNED,
    DMARES_DOMAIN_BUS
} AddrTrans_Domain_t;


// Maximum number of address/domain pairs stored per DMA resource.
#define DMARES_ADDRPAIRS_CAPACITY 3

typedef struct
{
    uint32_t Magic;     // signature used to validate handles

    // DMA resource properties: Size, Alignment, Bank & fCached
    DMAResource_Properties_t Props;

    // Storage for upto N address/domain pairs.
    DMAResource_AddrPair_t AddrPairs[DMARES_ADDRPAIRS_CAPACITY];

    // if true, 32-bit words are swapped when transferred to/from
    // the DMA resource
    bool fSwapEndianness;

    // this implementation supports the following allocator references:
    // 'A' -> this DMA resource has been obtained through DMAResource_Alloc
    // 'R' -> this DMA resource has been obtained through
    //        DMAResource_CheckAndRegister using Linux DMA API
    // 'k' -> this DMA resource has been obtained through
    //        DMAResource_CheckAndRegister using Linux kmalloc() allocator
    // 'N' -> used to register buffers that do not need to be DMA-safe
    // 'T' -> this DMA resource has been obtained through DMAResource_Attach
    char AllocatorRef;

    // maximum data amount that can be stored in bytes, e.g. allocated size
    unsigned int BufferSize;

#ifndef ADAPTER_REMOVE_BOUNCEBUFFERS
    struct
    {
        // bounce buffer for DMAResource_CheckAndRegister'ed buffers
        // note: used only when concurrency is impossible
        //       (PE source packets allow concurrency!!)
        DMAResource_Handle_t Bounce_Handle;
    } bounce;
#endif

#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    struct
    {
        // for secure detection of PEC_SGList handles
        bool IsSGList;
    } sg;
#endif

    bool fIsNewSA;

#ifndef ADAPTER_USE_LARGE_TRANSFORM_DISABLE
    bool fIsLargeTransform;
#endif

    // Implementation-specific DMA resource context
    void * Context_p;

    void * DriverHandle;

    // Type of DMA bank
    unsigned int BankType;

} DMAResource_Record_t;

#define DMARES_RECORD_MAGIC 0xde42b5e7


#endif /* INCLUDE_GUARD_DMARES_RECORD_H */

/* end of file dmares_record.h */
