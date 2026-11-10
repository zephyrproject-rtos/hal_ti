/* cs_eip201.h
 *
 * Configuration Settings for the EIP-201 Driver Library module.
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

#ifndef INCLUDE_GUARD_CS_EIP201_H
#define INCLUDE_GUARD_CS_EIP201_H

// Top-level Driver configuration
#include <third_party/hsmddk/include/Config/cs_driver.h>      // top-level driver configuration

// set this option to enable checking of all arguments to all EIP201 functions
// disable it to reduce code size and reduce overhead
#ifndef DRIVER_PERFORMANCE
#define EIP201_STRICT_ARGS
#endif

// maximum number of interrupts as defined for this instance
#define EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS  14

/* EIP201_REMOVE_*
 *
 * These switches allow removal of unused API functions
 * to reduce footprint and increase code-coverage figures
 */
#ifdef DRIVER_POLLING
// disable all functions
#define EIP201_REMOVE_CONFIG_CHANGE
#define EIP201_REMOVE_CONFIG_READ
#define EIP201_REMOVE_SOURCEMASK_ENABLESOURCE
#define EIP201_REMOVE_SOURCEMASK_DISABLESOURCE
#define EIP201_REMOVE_SOURCEMASK_SOURCEISENABLED
#define EIP201_REMOVE_SOURCEMASK_READALL
#define EIP201_REMOVE_SOURCESTATUS_ISENABLEDSOURCEPENDING
#define EIP201_REMOVE_SOURCESTATUS_ISRAWSOURCEPENDING
#define EIP201_REMOVE_SOURCESTATUS_READALLENABLED
#define EIP201_REMOVE_SOURCESTATUS_READALLRAW
#define EIP201_REMOVE_INITIALIZE
#define EIP201_REMOVE_ACKNOWLEDGE
#endif /* DRIVER_POLLING */


#endif /* INCLUDE_GUARD_CS_EIP201_H */

/* end of file cs_eip201.h */
