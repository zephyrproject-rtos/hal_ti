/* cs_hwpal_ext.h
 *
 * EIP-130 (FPGA) chip specific configuration parameters
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

#ifndef INCLUDE_GUARD_CS_HWPAL_EXT_H
#define INCLUDE_GUARD_CS_HWPAL_EXT_H

// CC27XX interface
#include <DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Disable PCI Configuration Space support support
#define HWPAL_REMOVE_DEVICE_PCICONFIGSPACE

#define HWPAL_DMARESOURCE_REMOVE_ATTACH

// Device name in the Device Tree Structure
#define HWPAL_DEVICE_NAME           DRIVER_DEVICE_NAME
#define HWPAL_PLATFORM_DEVICE_NAME  DRIVER_DEVICE_NAME

// Max number of IRQ's supported by device
#define HWPAL_PLATFORM_IRQ_COUNT    1

// Index of the IRQ in the "interrupts" property of the Open Firmware device
// tree entry. 0 is the first IRQ listed, 1 is the second IRQ listed, etc.
#define HWPAL_PLATFORM_IRQ_IDX      0

#define HWPAL_REMAP_ADDRESSES       ;

// Definition of static resources inside the device
// Refer to the data sheet of device for the correct values
//                   Name           DevNr  Start       Last        Flags (see below)
#define HWPAL_DEVICES \
    HWPAL_DEVICE_ADD(HWPAL_DEVICE_NAME,       0, 0x00000000, 0x0003FFFF, 7), \
    HWPAL_DEVICE_ADD(HWPAL_DEVICE_NAME"_NS0", 0, 0x00040000, 0x0007FFFF, 7), \
    HWPAL_DEVICE_ADD(HWPAL_DEVICE_NAME"_AIC", 0, 0x00003E00, 0x00003E1F, 7)

// Flags:
//   bit0 = Trace reads (requires HWPAL_TRACE_DEVICE_READ)
//   bit1 = Trace writes (requires HWPAL_TRACE_DEVICE_WRITE)
//   bit2 = Swap word endianness (requires HWPAL_DEVICE_ENABLE_SWAP)

// Maximum number of devices in the device list,
// must be equal to or greater than the number of devices in HWPAL_DEVICES
#define HWPAL_DEVICE_COUNT          3U

#ifdef ARCH_MB // For MicroBlaze only
// Address where the device list is mapped in the MMIO
#define HWPAL_DEVICE_MEM_ADDR   HSMCRYPTO_BASE
#endif

// #define HWPAL_USE_MSI

// Enables DMA resources banks so that different memory regions can be used
// for DMA buffer allocation
#ifdef DRIVER_DMARESOURCE_BANKS_ENABLE
#define HWPAL_DMARESOURCE_BANKS_ENABLE
#endif // DRIVER_DMARESOURCE_BANKS_ENABLE

#ifdef HWPAL_DMARESOURCE_BANKS_ENABLE
// Definition of DMA banks, one dynamic and 1 static
//                                 Bank    Type   Shared  Cached  Addr  Blocks   Block Size
#define HWPAL_DMARESOURCE_BANKS                                                              \
        HWPAL_DMARESOURCE_BANK_ADD (0,       0,     0,      1,      0,    0,         0),     \
        HWPAL_DMARESOURCE_BANK_ADD (1,       1,     1,      1,      0,                       \
                                    DRIVER_DMA_BANK_ELEMENT_COUNT,                           \
                                    DRIVER_DMA_BANK_ELEMENT_BYTE_COUNT)
#endif // HWPAL_DMARESOURCE_BANKS_ENABLE

#define HWPAL_DMARESOURCE_ADDR_MASK               0xffffffffULL


#endif /* INCLUDE_GUARD_CS_HWPAL_EXT_H */

/* end of file cs_hwpal_ext.h */
