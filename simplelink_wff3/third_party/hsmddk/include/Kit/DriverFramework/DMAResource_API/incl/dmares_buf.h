/* dmares_buf.h
 *
 * Driver Framework, DMAResource API, Buffer functions
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

#ifndef INCLUDE_GUARD_DMARES_BUF_H
#define INCLUDE_GUARD_DMARES_BUF_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>         // bool, uint8_t, uint32_t, inline
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_types.h>       // DMAResource_Handle/Properties_t


/*----------------------------------------------------------------------------
 * DMAResource_Alloc
 *
 * Allocate a buffer of requested size that can be used for device DMA.
 * DMAResource_Create is used to create a record and handle to administer
 * the buffer.
 *
 * RequestedProperties
 *     Requested properties of the buffer that will be allocated, including
 *     the size, start address alignment, etc. See DMAResource_Properties_t.
 *
 * AddrPair_p (output)
 *     Pointer to the memory location where the address and domain of the
 *     buffer will be written by this function when allocation is successful.
 *     This buffer address can then be used in the caller's memory domain.
 *
 * Handle_p (output)
 *     Pointer to the memory location when the handle will be returned.
 *
 * Return Values
 *     0    Success
 *     <0   Error code (implementation specific)
 */
int32_t
DMAResource_Alloc(
        const DMAResource_Properties_t RequestedProperties,
        DMAResource_AddrPair_t * const AddrPair_p,
        DMAResource_Handle_t * const Handle_p);


/*----------------------------------------------------------------------------
 * DMAResource_CheckAndRegister
 *
 * This function can be used to register an already allocated buffer that the
 * caller wishes to use for DMA. The implementation checks whether the
 * buffer is valid for DMA use. If this test passes, the buffer is registered
 * and can be use as for DMAResource_Alloc and DMAResource_Attach.
 * If the test fails, the buffer is rejected and not registered. The caller
 * will then have to bounce the data to another DMA-safe buffer.
 * The exact conditions for accepting or reject a buffer are implementation
 * specific. Please check the implementation notes.
 *
 * The buffer must be accessible to the caller using the provided address. Use
 * DMAResource_Attach for buffers that are not yet accessible to the caller.
 * It is allowed to register a subset of a DMA resource.
 * DMAResource_Create is used to create a record and handle to administrate
 * the buffer.
 *
 * RequestedProperties (input)
 *     Properties that describe the buffer that is being registered.
 *
 * AddrPair (input)
 *     Address and Domain of the buffer. The pointer in this structure must be
 *     valid to use on the host in the domain of the caller.
 *
 * AllocatorRef (input)
 *     Number to describe the source of this buffer. The exact numbers
 *     supported is implementation specific. This provides some flexibility
 *     for a specific implementation to provide address translation for a
 *     number of allocators.
 *
 * Handle_p (output)
 *     Pointer to the memory location when the handle will be returned when
 *     registration is successful.
 *
 * Return Values
 *     1    Rejected; buffer cannot be used for DMA
 *     0    Success
 *     <0   Error code (implementation specific)
 */
int32_t
DMAResource_CheckAndRegister(
        const DMAResource_Properties_t RequestedProperties,
        const DMAResource_AddrPair_t AddrPair,
        const char AllocatorRef,
        DMAResource_Handle_t * const Handle_p);


/*----------------------------------------------------------------------------
 * DMAResource_Attach
 *
 * This function must be used to make an already allocated buffer available
 * in the memory domain of the caller (add it to the address map). Use this
 * function instead of DMAResource_CheckAndRegister when an address of the
 * buffer is available, but not for this memory domain.
 * The exact memory domains supported by this function is implementation
 * specific.
 * DMAResource_Create is used to create a record and handle to administer
 * the buffer.
 *
 * ActualProperties (input)
 *     Properties that describe the buffer that is being registered.
 *
 * AddrPair (input)
 *     Address and Domain of the buffer. The pointer in this structure is
 *     NOT valid to use in the domain of the caller.
 *
 * Handle_p (output)
 *     Pointer to the memory location when the handle will be returned.
 *
 * Return Values
 *     0    Success
 *     <0   Error code (implementation specific)
 */
int32_t
DMAResource_Attach(
        const DMAResource_Properties_t ActualProperties,
        const DMAResource_AddrPair_t AddrPair,
        DMAResource_Handle_t * const Handle_p);


/*----------------------------------------------------------------------------
 * DMAResource_Release
 *
 * This function must be used as a counter-operation for DMAResource_Alloc,
 * DMAResource_CheckAndRegister and DMAResource_Attach. Allocated buffers are
 * freed, attached buffers are detached and registered buffers are simply
 * forgotten.
 * The caller must ensure the buffers are not in use anymore when this
 * function is called.
 * The related record and handle are also destroyed using DMAResource_Destroy,
 * so the handle and record cannot be used anymore when this function returns.
 *
 * Handle (input)
 *     The handle to the DMA Resource record that was returned by
 *     DMAResource_Alloc, DMAResource_CheckAndRegister or DMAResource_Attach.
 *
 * Return Values
 *     0    Success
 *     <0   Error code (implementation specific)
 */
int32_t
DMAResource_Release(
        const DMAResource_Handle_t Handle);


/*----------------------------------------------------------------------------
 * DMAResource_SwapEndianness_Set
 *
 * This function sets the endianness conversion option in the DMA resource
 * record. This field is considered by the functions in dmares_rw.h that
 * access integers.
 *
 * Handle (input)
 *     The handle to the DMA Resource record that was returned by
 *     DMAResource_Alloc, DMAResource_CheckAndRegister or DMAResource_Attach.
 *
 * fSwapEndianness
 *     true  = swap byte order of the integer before writing or after reading.
 *     false = do not swap byte order.
 *
 * Return Values
 *     0    Success
 *     <0   Error code (implementation specific)
 */
int32_t
DMAResource_SwapEndianness_Set(
        const DMAResource_Handle_t Handle,
        const bool fSwapEndianness);


/*----------------------------------------------------------------------------
 * DMAResource_SwapEndianness_Get
 *
 * This function retrieves the endianness conversion option from the
 * DMA resource record. See DMAResource_SwapEndianness_Set for details.
 *
 * Handle (input)
 *     The handle to the DMA Resource record that was returned by
 *     DMAResource_Alloc, DMAResource_CheckAndRegister or DMAResource_Attach.
 *
 * Return Values
 *     0    Success; fSwapEndianness is false
 *     1    Success; fSwapEndianness is true
 *     <0   Error code (implementation specific)
 */
int32_t
DMAResource_SwapEndianness_Get(
        const DMAResource_Handle_t Handle);


#endif /* INCLUDE_GUARD_DMARES_BUF_H */

/* end of file dmares_buf.h */
