/** @file cs_adapter.h
 *
 * @brief Configuration Settings for the Driver Adapter module.
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

#ifndef INCLUDE_GUARD_CS_ADAPTER_H
#define INCLUDE_GUARD_CS_ADAPTER_H

/*-----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include <third_party/hsmddk/include/Config/cs_driver.h>


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
/** Adapter/driver name */
#define ADAPTER_DRIVER_NAME "Driver-" DRIVER_NAME

/** Maximum log severity - log level for the entire adapter (for now)
 *  choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT */
#ifdef DRIVER_PERFORMANCE
#define LOG_SEVERITY_MAX    LOG_SEVERITY_CRITICAL
#else
#define LOG_SEVERITY_MAX    LOG_SEVERITY_WARN
#endif

/** Bouncebuffers use */
#ifndef DRIVER_BOUNCEBUFFERS
#define ADAPTER_REMOVE_BOUNCEBUFFERS
#endif

/** Endian swap use */
#ifdef DRIVER_SWAPENDIAN
#define ADAPTER_ENABLE_SWAP
#endif

// Enable byte swap for words in DMA buffers
#ifdef DRIVER_BUFMAN_SWAP_ENABLE
// Enable it for Xilinx Zynq 70x FPGA MicroBlaze configured in BigEndian mode
// because in this mode either the MicroBlaze or the AXI interconnect will
// swap bytes in 32-bit words before/after writing/reading them to/from memory.
#define ADAPTER_BUFMAN_SWAP_ENABLE
#endif

/** Adapter/driver host and device type */
// Is host platform 64-bit?
#ifdef DRIVER_64BIT_HOST
#define ADAPTER_64BIT_HOST
// Is device 64-bit? Only makes sense on 64-bit host.
#ifdef DRIVER_64BIT_DEVICE
#define ADAPTER_64BIT_DEVICE
#endif  // DRIVER_64BIT_DEVICE
#endif  // DRIVER_64BIT_HOST

/** Strict argument checking use */
#ifndef DRIVER_PERFORMANCE
#define ADAPTER_STRICT_ARGS
#endif

// Misc options
/** Maximum DMA resource handles */
#define ADAPTER_MAX_DMARESOURCE_HANDLES  128U

/** EIP130 interrupt signals\n
 *  Assigned values represent interrupt source bit numbers */
typedef enum
{
    IRQ_MBX1_IN_FREE_IRQ  = 0,
    IRQ_MBX1_OUT_FULL_IRQ = 1,
    IRQ_MBX2_IN_FREE_IRQ  = 2,
    IRQ_MBX2_OUT_FULL_IRQ = 3,
    IRQ_MBX3_IN_FREE_IRQ  = 4,
    IRQ_MBX3_OUT_FULL_IRQ = 5,
    IRQ_MBX4_IN_FREE_IRQ  = 6,
    IRQ_MBX4_OUT_FULL_IRQ = 7,
    IRQ_MBX_LINKABLE_IRQ  = 8,
} Adapter_EIP130_Interrups_t;

#define ADAPTER_IRQ_MBX1_IN_FREE_IRQ_NAME     "IRQ_MBX1_FREE"
#define ADAPTER_IRQ_MBX1_OUT_FULL_IRQ_NAME    "IRQ_MBX1_FULL"
#define ADAPTER_IRQ_MBX2_IN_FREE_IRQ_NAME     "IRQ_MBX2_FREE"
#define ADAPTER_IRQ_MBX2_OUT_FULL_IRQ_NAME    "IRQ_MBX2_FULL"
#define ADAPTER_IRQ_MBX3_IN_FREE_IRQ_NAME     "IRQ_MBX3_FREE"
#define ADAPTER_IRQ_MBX3_OUT_FULL_IRQ_NAME    "IRQ_MBX3_FULL"
#define ADAPTER_IRQ_MBX4_IN_FREE_IRQ_NAME     "IRQ_MBX4_FREE"
#define ADAPTER_IRQ_MBX4_OUT_FULL_IRQ_NAME    "IRQ_MBX4_FULL"
#define ADAPTER_IRQ_MBX_LINKABLE_IRQ_NAME     "IRQ_MBX_LINKABLE"

/** Cache line size */
#define ADAPTER_PCICONFIG_CACHELINESIZE 1

/** VEX stub use */
#ifdef DRIVER_VEX_STUB_ENABLE
#define ADAPTER_INIT_VEX_STUB_ENABLE
#endif

/** VEX proxy use */
#ifdef DRIVER_VEX_PROXY_ENABLE
#define ADAPTER_INIT_VEX_PROXY_ENABLE
#endif

/** Token/Data poll timeout settings, delay wait time in milliseconds */
#ifdef DRIVER_POLLING_DELAY_MS
#define ADAPTER_BUFMAN_POLLING_DELAY_MS     DRIVER_POLLING_DELAY_MS
#endif

/** Token/Data poll timeout settings, maximum number of polling attempts */
#ifdef DRIVER_POLLING_MAXLOOPS
#define ADAPTER_BUFMAN_POLLING_MAXLOOPS     DRIVER_POLLING_MAXLOOPS
#endif


#endif /* INCLUDE_GUARD_CS_ADAPTER_H */

/* end of file cs_adapter.h */
