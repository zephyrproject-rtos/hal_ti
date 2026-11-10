/* dmares_addr.h
 *
 * Driver Framework, DMAResource API, Address Translation functions
 * Translates an {address + domain} to an address in a requested domain.
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

#ifndef INCLUDE_GUARD_DMARES_ADDR_H
#define INCLUDE_GUARD_DMARES_ADDR_H

#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_types.h>       // DMAResource_AddrDomain/AddrPair/Handle_t

/*----------------------------------------------------------------------------
 * DMAResource_Translate
 *
 * Attempts to provide an address for a DMA Resource that can be used in the
 * requested address domain. Typically used to get the address that can be
 * used by a device to perform DMA.
 *
 * Handle (input)
 *     The handle to the DMA Resource record that was returned by
 *     DMAResource_Alloc, DMAResource_CheckAndRegister or DMAResource_Attach.
 *
 * DestDomain (input)
 *     The requested domain to translate the address to.
 *     Please check the implementation notes for supported domains.
 *
 * PairOut_p (output)
 *     Pointer to the memory location when the converted address plus domain
 *     will be written.
 *
 * Return Values
 *     0    Success
 *     <0   Error code (implementation dependent)
 */
int32_t
DMAResource_Translate(
        const DMAResource_Handle_t Handle,
        const DMAResource_AddrDomain_t DestDomain,
        DMAResource_AddrPair_t * const PairOut_p);


/*----------------------------------------------------------------------------
 * DMAResource_AddPair
 *
 * This function can be used to register another address pair known to the
 * caller for a DMA Resource.
 * The information will be stored in the DMA Resource Record and can be used
 * by DMAResource_Translate.
 * Typically used when an external DMA-safe buffer allocator returns two
 * addresses (for example virtual and physical).
 * Note: How many address pairs are supported is implementation specific.
 *
 * Handle (input)
 *     The handle to the DMA Resource record that was returned by
 *     DMAResource_CheckAndRegister or DMAResource_Attach.
 *
 * Pair (input)
 *     Address pair (address + domain) to be associated with the DMA Resource.
 *
 * Return Values
 *     0    Success
 *     <0   Error code (implementation dependent)
 */
int32_t
DMAResource_AddPair(
        const DMAResource_Handle_t Handle,
        const DMAResource_AddrPair_t Pair);


#endif /* INCLUDE_GUARD_DMARES_ADDR_H */

/* end of file dmares_addr.h */
