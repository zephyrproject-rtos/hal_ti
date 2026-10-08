/** @file cs_driver.h
 *
 * @brief Configuration Settings for the EIP-130 Drivers.
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

#ifndef INCLUDE_GUARD_CS_DRIVER_H
#define INCLUDE_GUARD_CS_DRIVER_H

/*----------------------------------------------------------------------------
 * Definitions and macros
 */
/** System behaviour specifics:\n */
/** Big-endian CPU use */
#ifdef ARCH_POWERPC
// Enable byte swap for 32-bit words in registers and internal memory,
// e.g. for device slave interface
#define DRIVER_SWAPENDIAN
#endif

#ifdef ARCH_MB_BE // MicroBlaze in Big Endian configuration
// Enable byte swap for words in DMA buffers, e.g. for device master interface
#define DRIVER_BUFMAN_SWAP_ENABLE
#endif

/** General driver/device name */
#define DRIVER_NAME             "EIP130"
#define DRIVER_DEVICE_NAME      DRIVER_NAME
#define DRIVER_TI_MODIFICATIONS_EXCLUDES 0

/** System Configuration */
// Driver Conf  Poll/Int  BounceBuff Performance
// C0 (Default)   Poll       Off         Yes
// C1             Int        Off         Yes
// C2             Poll       Off         No
// C3             Poll       On          No
// C4             Int        On          Yes
// C5             Int        On          No
// C6             Poll       On          Yes
// C7             Int        Off         No
#ifndef SYSTEMTEST_CONFIGURATION
/* Set default system configuration */
#define SYSTEMTEST_CONFIGURATION 2
#endif
#if SYSTEMTEST_CONFIGURATION == 0
//#define DRIVER_BOUNCEBUFFERS
#define DRIVER_PERFORMANCE

#elif SYSTEMTEST_CONFIGURATION == 2
//#define DRIVER_BOUNCEBUFFERS
//#define DRIVER_PERFORMANCE

#elif SYSTEMTEST_CONFIGURATION == 3
#define DRIVER_BOUNCEBUFFERS
//#define DRIVER_PERFORMANCE

#elif SYSTEMTEST_CONFIGURATION == 4
#define DRIVER_BOUNCEBUFFERS
#define DRIVER_PERFORMANCE

#endif


/*-----------------------------------------------------------------------------
 * Include platform specific driver configuration
 */
#include <DeviceFamily.h>
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    #include <third_party/hsmddk/include/Config/cc35xx/cs_driver_ext.h>
#else
    #include <third_party/hsmddk/include/Config/cc27xx/cs_driver_ext.h>
#endif



#endif /* INCLUDE_GUARD_CS_DRIVER_H */

/* end of file cs_driver.h */
