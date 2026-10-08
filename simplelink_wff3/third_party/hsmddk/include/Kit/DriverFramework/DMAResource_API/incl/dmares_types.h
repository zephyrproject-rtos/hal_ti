/* dmares_types.h
 *
 * Driver Framework, DMAResource API, Type Definitions
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

#ifndef INCLUDE_GUARD_DMARES_TYPES_H
#define INCLUDE_GUARD_DMARES_TYPES_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>         // bool, uint8_t, uint32_t, inline


/*----------------------------------------------------------------------------
 * DMAResource_Handle_t
 *
 * This handle represents a DMA Resource Record that holds information about
 * a memory resource that can be accessed by a device using DMA, from another
 * memory domain in the same host or from another host (CPU/DSP).
 */

typedef void * DMAResource_Handle_t;

typedef uint32_t DMAResource_AddrDomain_t;


/*----------------------------------------------------------------------------
 * DMAResource_AddrPair_t
 *
 * This type describes a dynamic resource address coupled with its memory
 * domain. The caller is encouraged to store the address with the domain
 * information.
 * The use of 'void *' for the Address_p avoids unsafe void-pointer function
 * output parameters in 99% of all cases. However, in some odd cases the
 * Address_p part needs to be adapted and that is why Domain must be located
 * first in the struct. It also guarantees that Address_p part starts always
 * at the same offset.
 */
typedef struct
{
    DMAResource_AddrDomain_t Domain;    // Defines domain of Address_p
    void * Address_p;                   // type ensures 64-bit support
} DMAResource_AddrPair_t;


/*----------------------------------------------------------------------------
 * DMAResource_Properties_t
 *
 * Buffer properties. When allocating a buffer, these are the requested
 * properties for the buffer. When registering or attaching to an externally
 * allocated buffer these properties describe the already allocated buffer.
 * The exact fields and values supported is implementation specific.
 *
 * For both uses, the data structure should be initialized to all zeros
 * before filling in some or all of the fields. This ensures forward
 * compatibility in case this structure is extended with more fields.
 *
 * Example usage:
 *     DMAResource_Properties_t Props = {0};
 *     Props.fIsCached = true;
 */
typedef struct
{
    uint32_t Size;       // size of the buffer in bytes
    int32_t Alignment;   // buffer start address alignment
                         // examples: 4 for 32bit
    uint8_t Bank;        // can be used to indicate on-chip memory
    bool fCached;        // true = SW needs to control the coherency management
} DMAResource_Properties_t;


/*----------------------------------------------------------------------------
 * DMAResource_Record_t
 *
 * This type is the record that describes a DMAResource. The details of the
 * type are implementation specific and therefore in a separate header file.
 *
 * Several DMAResource API functions return a handle to a newly instantiated
 * record. Use DMAResource_Handle2RecordPtr to get a pointer to the actual
 * record and to access fields in the record.
 */

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/dmares_record.h>   // DMAResource_Record_t definition


#endif /* INCLUDE_GUARD_DMARES_TYPES_H */

/* end of file dmares_types.h */
