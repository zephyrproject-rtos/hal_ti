/* device_rw.h
 *
 * Driver Framework, Device API, Read/Write functions
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

#ifndef INCLUDE_GUARD_DEVICE_RW_H
#define INCLUDE_GUARD_DEVICE_RW_H

// Driver Framework Basic Defs API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>     // uint32_t, inline

// Driver Framework Device API
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_types.h>   // Device_Handle_t


/*----------------------------------------------------------------------------
 * Device_Read32
 *
 * This function can be used to read one static 32bit resource inside a device
 * (typically a register or memory location). Since reading registers can have
 * side effects, the implementation must guarantee that the resource will be
 * read only once and no neighboring resources will be accessed.
 *
 * If required (decided based on internal configuration), on the fly endianness
 * swapping of the value read will be performed before it is returned to the
 * caller.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * ByteOffset (input)
 *     The byte offset within the device for the resource to read.
 *
 * Return Value
 *     The value read.
 *
 * When the Device or Offset parameters are invalid, or a read error occurs,
 * the implementation will return an unspecified value.
 */
uint32_t
Device_Read32(
        const Device_Handle_t Device,
        const uint32_t ByteOffset);


/*----------------------------------------------------------------------------
 * Device_Read32Check
 *
 * This function can be used to read one static 32-bit resource inside a device
 * (typically a register or memory location). Since reading registers can have
 * side effects, the implementation must guarantee that the resource will be
 * read only once and no neighboring resources will be accessed.
 *
 * If required (decided based on internal configuration), on the fly endianess
 * swapping of the value read will be performed before it is returned to the
 * caller.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * ByteOffset (input)
 *     The byte offset within the device for the resource to read.
 *
 * Value_p (output)
 *     The 32-bit value read from the register.
 *
 * Return Value
 *     0 for success, non-zero value for read error.
 *
 * When the Device or Offset parameters are invalid, or a read error occurs,
 * the implementation will return an unspecified value.
 */
int32_t
Device_Read32Check(
        const Device_Handle_t Device,
        const uint32_t ByteOffset,
        uint32_t * const Value_p);


/*----------------------------------------------------------------------------
 * Device_Write32
 *
 * This function can be used to write one static 32bit resource inside a
 * device (typically a register or memory location). Since writing registers
 * can have side effects, the implementation must guarantee that the resource
 * will be written exactly once and no neighboring resources will be
 * accessed.
 *
 * If required (decided based on internal configuration), on the fly endianness
 * swapping of the value to be written will be performed.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * ByteOffset (input)
 *     The byte offset within the device for the resource to write.
 *
 * Value (input)
 *     The 32bit value to write.
 *
 * Return ValueIn
 *     0 for success, non-zero value for write error.
 *
 * The write can only be successful when the Device and ByteOffset parameters
 * are valid.
 */
int32_t
Device_Write32(
        const Device_Handle_t Device,
        const uint32_t ByteOffset,
        const uint32_t ValueIn);


/*----------------------------------------------------------------------------
 * Device_Read32Array
 *
 * This function perform the same task as Device_Read32 for an array of
 * consecutive 32bit words, allowing the implementation to use a more optimal
 * burst-read (if available).
 *
 * See Device_Read32 for pre-conditions and a more detailed description.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * StartByteOffset (input)
 *     Byte offset of the first resource to read.
 *     This value is incremented by 4 for each following resource.
 *
 * MemoryDst_p (output)
 *     Pointer to the memory where the retrieved words will be stored.
 *
 * Count (input)
 *     The number of 32bit words to transfer.
 *
 * Return Value
 *     0 for success, non-zero value for read error.
 *
 * When the Device or Offset parameters are invalid, or a read error occurs,
 * the implementation will return unspecified array values.
 */
int32_t
Device_Read32Array(
        const Device_Handle_t Device,
        const uint32_t StartByteOffset,
        uint32_t * MemoryDst_p,
        const int32_t Count);


/*----------------------------------------------------------------------------
 * Device_Write32Array
 *
 * This function perform the same task as Device_Write32 for an array of
 * consecutive 32bit words, allowing the implementation to use a more optimal
 * burst-write (if available).
 *
 * See Device_Write32 for pre-conditions and a more detailed description.
 *
 * Device (input)
 *     Handle for the device instance as returned by Device_Find.
 *
 * StartByteOffset (input)
 *     Byte offset of the first resource to write.
 *     This value is incremented by 4 for each following resource.
 *
 * MemorySrc_p (input)
 *     Pointer to the memory where the values to be written are located.
 *
 * Count (input)
 *     The number of 32bit words to transfer.
 *
 * Return Value
 *     0 for success, non-zero value for write error.
 */
int32_t
Device_Write32Array(
        const Device_Handle_t Device,
        const uint32_t StartByteOffset,
        const uint32_t * MemorySrc_p,
        const int32_t Count);


/* The defines below specify the possible return codes of the implementations
   of these API functions */

/* Device error return code for invalid parameter */
#define DEVICE_RW_PARAM_ERROR 0x00000010

/* Device error return code for a not initialized situation */
#define DEVICE_NOT_INITIALIZED_ERROR 0xEEEEEEEEU


#endif /* INCLUDE_GUARD_DEVICE_RW_H */

/* end of file device_rw.h */
