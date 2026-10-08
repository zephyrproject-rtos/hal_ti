/* c_adapter_bufmanager.h
 *
 * Default Buffer Manager Adapter Module Configuration
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

#ifndef INCLUDE_GUARD_C_ADAPTER_BUFMANAGER_H
#define INCLUDE_GUARD_C_ADAPTER_BUFMANAGER_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level Driver Framework configuration
#include <third_party/hsmddk/include/Config/cs_adapter.h>
#include <third_party/hsmddk/include/Config/cs_adapter_vex.h>         // Required for BufManager_Zeroize() use


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Enable swapping bytes in words written to or read from DMA buffers.
// Data is written to DMA buffer as bytes, not as words, so typically this
// byte swap is not needed, but on some systems it may be required to perform
// this byte swap in the DMA buffers, for example if the interconnect performs
// the byte swap in hardware for the DMA transfers.
//#define ADAPTER_BUFMAN_SWAP_ENABLE

// The number of polling attempts without delay in between
#ifndef ADAPTER_BUFMAN_POLLING_SKIP_FIRST_DELAYS
#define ADAPTER_BUFMAN_POLLING_SKIP_FIRST_DELAYS    50
#endif

// The delay (wait) time in milliseconds
// between the two consecutive polling attempts
#ifndef ADAPTER_BUFMAN_POLLING_DELAY_MS
#define ADAPTER_BUFMAN_POLLING_DELAY_MS             1
#endif

// Maximum number of polling attempts
#ifndef ADAPTER_BUFMAN_POLLING_MAXLOOPS
#define ADAPTER_BUFMAN_POLLING_MAXLOOPS             5000
#endif

// Add function BufManager_Zeroize() under condition
#ifdef VEX_DISABLE_TOKENID_WR_KEYPAIR
#define ADAPTER_BUFMAN_ZEROIZE
#endif


#endif /* INCLUDE_GUARD_C_ADAPTER_BUFMANAGER_H */

/* end of file c_adapter_bufmanager.h */

