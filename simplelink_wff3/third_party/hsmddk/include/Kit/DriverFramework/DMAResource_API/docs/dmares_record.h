/* dmares_record.h
 *
 * Driver Framework, DMAResource Record Definition (example)
 *
 * This file is an customizable declaration of the DMAResource_Record_t type
 * as part DMA Resource API.
 * Do not include this file directly; include dmares_types.h instead.
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
#error "Please include dmares_types.h instead of dmares_record.h"
#endif

/*----------------------------------------------------------------------------
 * Address Domains
 *
 * This is a list of domains that are supported by the implementation.
 * The domain describes the applicability of the address.
 */
enum
{
    DMARES_DOMAIN_DEVICE_CM,
    DMARES_DOMAIN_DEVICE_PE,
    DMARES_DOMAIN_DEVICE_PKA,
    DMARES_DOMAIN_PHYSICAL,
    DMARES_DOMAIN_BUS,
    DMARES_DOMAIN_INTERHOST,
    DMARES_DOMAIN_USER,
    DMARES_DOMAIN_KERNEL,
    DMARES_DOMAIN_DRIVER,
    DMARES_DOMAIN_APPLICATION,
    DMARES_DOMAIN_UNKNOWN
};

#define DMARES_ADDRPAIRS_CAPACITY 4

typedef struct
{
    uint32_t Magic;     // signature used to validate handles

    struct
    {
        // for freeing the buffer
        void * AllocatedAddr_p;
        unsigned int AllocatedSize;     // in bytes

        char AllocatorRef;
    } alloc;

    DMAResource_Properties_t Props;

    // list of applicable addresses for this resource
    DMAResource_AddrPair_t AddPairs[DMARES_ADDRPAIRS_CAPACITY];

    struct
    {
        // aligned start-address, data starts here
        void * HostAddr_p;
    } host;

    struct
    {
        // used by Read32/Write32[Array]
        bool fSwapEndianness;
    } swap;

} DMAResource_Record_t;


/* end of file dmares_record.h */
