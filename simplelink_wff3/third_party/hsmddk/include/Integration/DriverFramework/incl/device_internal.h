/* device_internal.h
 *
 * Driver Framework Device Internal interface.
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

#ifndef INCLUDE_GUARD_DEVICE_INTERNAL_H
#define INCLUDE_GUARD_DEVICE_INTERNAL_H

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include <third_party/hsmddk/include/Integration/DriverFramework/incl/c_device_generic.h>

// Driver Framework Device API
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_types.h>           // Device_Handle_t

// Driver Framework Device Platform interface
#include <third_party/hsmddk/include/Integration/DriverFramework/incl/device_platform.h>        // Device_Platform_*


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Global administration data
typedef struct
{
    // Initialization flag
    bool fInitialized;

    Device_Platform_Global_t Platform; // platform-specific global data
} Device_Global_Admin_t;

// Internal statically configured device administration data
typedef struct
{
    const char DevName[HWPAL_MAX_DEVICE_NAME_LENGTH];
    uint32_t DeviceNr;
    uint32_t FirstOfs;
    uint32_t LastOfs;
    uint32_t Flags; // swapping, tracing
} Device_Admin_Static_t;

// Internal device administration data
typedef struct
{
    char DevName[HWPAL_MAX_DEVICE_NAME_LENGTH];
    uint32_t DeviceNr;
    uint32_t FirstOfs;
    uint32_t LastOfs;
    uint32_t Flags; // swapping, tracing

#ifdef HWPAL_DEVICE_MAGIC
    uint32_t Magic;
#endif

    Device_Platform_t Platform; // platform-specific device data

    uint32_t DeviceId; // index in the device list

} Device_Admin_t;

#define HWPAL_DEVICE_ADD(_name, _devnr, _firstofs, _lastofs, _flags) \
                        {_name, _devnr, _firstofs, _lastofs, _flags}


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * Device_Internal_Static_Count_Get
 *
 * Returns number of statically configured devices in the HWPAL_DEVICES device
 * list.
 *
 */
uint32_t
Device_Internal_Static_Count_Get(void);


/*----------------------------------------------------------------------------
 * Device_Internal_Count_Get
 *
 * Returns number of maximum supported devices in the device list.
 *
 */
uint32_t
Device_Internal_Count_Get(void);


/*----------------------------------------------------------------------------
 * Device_Internal_Admin_Static_Get
 *
 * Returns pointer to the memory location where the statically configured
 * device list is stored.
 *
 */
const Device_Admin_Static_t *
Device_Internal_Admin_Static_Get(void);


/*----------------------------------------------------------------------------
 * Device_Internal_Admin_Get
 *
 * Returns pointer to the memory location where the device list is stored.
 *
 */
Device_Admin_t **
Device_Internal_Admin_Get(void);


/*----------------------------------------------------------------------------
 * Device_Internal_Admin_Global_Get
 *
 * Returns pointer to the memory location where the global device
 * administration data is stored.
 *
 */
Device_Global_Admin_t *
Device_Internal_Admin_Global_Get(void);


/*----------------------------------------------------------------------------
 * Device_Internal_Alloc
 *
 * Returns a pointer to a newly allocated block ByteCount bytes long, or a null
 * pointer if the block could not be allocated.
 *
 */
void *
Device_Internal_Alloc(
        uint32_t ByteCount);


/*----------------------------------------------------------------------------
 * Device_Internal_Free
 *
 * Deallocates the block of memory pointed at by Ptr.
 *
 */
void
Device_Internal_Free(
        void * Ptr);


/*----------------------------------------------------------------------------
 * Device_Internal_Initialize
 *
 * See Device_Initialize() description.
 *
 */
int32_t
Device_Internal_Initialize(
        void * CustomInitData_p);


/*----------------------------------------------------------------------------
 * Device_Internal_UnInitialize
 *
 * See Device_UnInitialize() description.
 *
 */
void
Device_Internal_UnInitialize(void);


/*-----------------------------------------------------------------------------
 * Device_Internal_Find
 *
 * See Device_Find() description.
 *
 * Index (input)
 *      Device  index in the device list.
 *
 */
Device_Handle_t
Device_Internal_Find(
        const char * DeviceName_p,
        const uint32_t Index);


/*-----------------------------------------------------------------------------
 * Device_Internal_GetIndex
 *
 * See Device_GetIndex() description.
 *
 */
int32_t
Device_Internal_GetIndex(
        const Device_Handle_t Device);


#endif /* INCLUDE_GUARD_DEVICE_INTERNAL_H */

/* end of file device_internal.h */

