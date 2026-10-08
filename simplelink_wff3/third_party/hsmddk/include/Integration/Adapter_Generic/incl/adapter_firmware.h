/* adapter_firmware.h
 *
 * Interface for obtaining the firmware image.
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

#ifndef INCLUDE_GUARD_ADAPTER_FIRMWARE_H
#define INCLUDE_GUARD_ADAPTER_FIRMWARE_H


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Defs API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

#ifdef EIP130_ENABLE_FIRMWARE_LOAD

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// This data type represents a firmware resource.
// Note: Use NULL to set to a known uninitialized value
typedef void * Adapter_Firmware_t;


/*----------------------------------------------------------------------------
 * Adapter_Firmware_Acquire
 *
 * Obtain access to a specific firmware image in the form of an array of 32-bit
 * words. This function allocates any required buffers to store the
 * firmware. Multiple calls to this function are possible and multiple
 * firmware images remain valid at the same time. Access to the firmware
 * image remains valid until Adapter_Firmware_Release is called.
 *
 * Firmware_Name_p (input)
 *       Null terminated string that indicates which firmware to load.
 *       This is typically a file name under a implementation-defined
 *       fixed directory, but not all implementations are required to
 *       load firmware from a file system.
 *
 * Firmware_p (output)
 *       Pointer to array of 32-bit words that represents the loaded firmware.
 *
 * Firmware_Word32Count (output)
 *       Size of the array in 32-bit words.
 *
 * Return: NULL if firmware load failed, otherwise a value that can be
 *         passed to Adapter_Firmware_Release for release.
 */
Adapter_Firmware_t
Adapter_Firmware_Acquire(
    const char * Firmware_Name_p,
    const uint32_t ** Firmware_p,
    uint32_t  * Firmware_Word32Count);

/*----------------------------------------------------------------------------
 * Adapter_Firmware_Release
 *
 * Release any resources that were allocated by a single call to
 * Adapter_Firmware_Acquire. It is illegal to call this function multiple
 * times for the same handle.
 *
 * FirmwareHandle (input)
 *         Handle as returned by Adapter_Firmware_Acquire().
 */
void
Adapter_Firmware_Release(
   Adapter_Firmware_t FirmwareHandle);


#endif /* EIP130_ENABLE_FIRMWARE_LOAD */


#endif /* INCLUDE_GUARD_ADAPTER_FIRMWARE_H */

/* end of file adapter_firmware.h */
