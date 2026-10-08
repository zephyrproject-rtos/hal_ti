/* adapter_firmware.c
 *
 * User-space implementation of Interface for obtaining the firmware image.
 * Read from file data segment.
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_firmware.h>

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/c_adapter_firmware.h>

// Driver Framework Basic Defs API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

// Logging API
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_alloc.h>

#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#ifdef EIP130_ENABLE_FIRMWARE_LOAD

/*----------------------------------------------------------------------------
 * Definitions and macros
 */
extern uint8_t _binary__lib_firmware_firmware_eip130ram_sbi_start;
extern uint8_t _binary__lib_firmware_firmware_eip130ram_sbi_end;
extern unsigned int _binary__lib_firmware_firmware_eip130ram_sbi_size;


/*----------------------------------------------------------------------------
 * Adapter_Firmware_Acquire
 */
Adapter_Firmware_t
Adapter_Firmware_Acquire(
        const char * Firmware_Name_p,
        const uint32_t ** Firmware_p,
        uint32_t * Firmware_Word32Count)
{
    unsigned int Firmware_ByteCount, i;
    uint32_t * Firmware_Data_p;

    uint8_t * p;
    uint8_t * fw_start = (uint8_t*)&_binary__lib_firmware_firmware_eip130ram_sbi_start;
    uint8_t * fw_end = (uint8_t*)&_binary__lib_firmware_firmware_eip130ram_sbi_end;
    uint32_t * fw_size = (uint32_t*)&_binary__lib_firmware_firmware_eip130ram_sbi_size;

    Firmware_ByteCount = (unsigned int)fw_size;

    LOG_INFO("%s: %s\n", __func__, Firmware_Name_p);

    // Initialize output parameters.
    *Firmware_p = NULL;
    *Firmware_Word32Count = 0;

    LOG_INFO("%s: firmware file size %d\n", __func__, Firmware_ByteCount);

    if (Firmware_ByteCount == 0 ||
        Firmware_ByteCount >= 256*1024 ||
        Firmware_ByteCount % sizeof(uint32_t) != 0)
    {
        LOG_CRIT("%s: Invalid file size %d\n", __func__, Firmware_ByteCount);
        return NULL;
    }

    // Allocate buffer for data
    p = Adapter_Alloc(Firmware_ByteCount);
    if (p == NULL)
    {
        LOG_CRIT("%s: Failed to allocate\n", __func__);
        return NULL;
    }

    Firmware_Data_p = (uint32_t*)p;

    // Read from firmware blob
    while(fw_start < fw_end)
    {
        *p = *fw_start;
        fw_start++;
        p++;
    }

    // Convert bytes from file to array of 32-bit words (in-place).
    {
        p = (uint8_t *)Firmware_Data_p;

        for (i = 0; i < Firmware_ByteCount / sizeof(uint32_t); i++)
        {
            Firmware_Data_p[i] = p[0] | (p[1]<<8) | (p[2]<<16) | (p[3]<<24);

            p += sizeof(uint32_t);
        }
    }

    // Pass results to caller
    *Firmware_p             = Firmware_Data_p;
    *Firmware_Word32Count   = Firmware_ByteCount / sizeof(uint32_t);

    IDENTIFIER_NOT_USED(Firmware_Name_p);

    return (Adapter_Firmware_t) Firmware_Data_p;
}


/*----------------------------------------------------------------------------
 * Adapter_Firmware_Release
 */
void
Adapter_Firmware_Release(
        Adapter_Firmware_t FirmwareHandle)
{
    LOG_INFO("%s\n", __func__);

    Adapter_Free((void*)FirmwareHandle);
}

#endif /* EIP130_ENABLE_FIRMWARE_LOAD */


/* end of file adapter_firmware.c */
