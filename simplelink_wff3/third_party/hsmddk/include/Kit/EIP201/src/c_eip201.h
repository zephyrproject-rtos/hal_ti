/* c_eip201.h
 *
 * Configuration options for the EIP201 Driver Library module.
 * The project-specific cs_eip201.h file is included,
 * whereafter defaults are provided for missing parameters.
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

#ifndef INCLUDE_GUARD_C_EIP201_H
#define INCLUDE_GUARD_C_EIP201_H

/*----------------------------------------------------------------
 * Defines that can be used in the cs_xxx.h file
 */

/* EIP201_STRICT_ARGS
 *
 * Set this option to enable checking of all arguments to all EIP201 DL
 * functions. Disable it to reduce code size and reduce overhead.
 */

/* EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS <NOI>
 *
 * This configures the maximum Number Of Interrupt (NOI) sources
 * actually available in the EIP201 AIC.
 * This can be used for strict argument checking.
 */

/*----------------------------------------------------------------
 * inclusion of cs_eip201.h
 */

// EIP-201 Driver Library API
#include <third_party/hsmddk/include/Config/cs_eip201.h>


/*----------------------------------------------------------------
 * provide backup values for all missing configuration parameters
 */
#if !defined(EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS) \
             || (EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS > 32)
#undef  EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS
#define EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS 32
#endif


/*----------------------------------------------------------------
 * other configuration parameters that cannot be set in cs_xxx.h
 * but are considered product-configurable anyway
 */


/*----------------------------------------------------------------
 * correct implementation-specific collisions
 */

#ifndef EIP201_REMOVE_INITIALIZE
// EIP201_Initialize internally depends on EIP201_Config_Change
#ifdef EIP201_REMOVE_CONFIG_CHANGE
#undef EIP201_REMOVE_CONFIG_CHANGE
#endif
#endif

#ifndef EIP201_LO_REG_BASE
#define EIP201_LO_REG_BASE 0x00
#endif
#ifndef EIP201_HI_REG_BASE
#define EIP201_HI_REG_BASE 0x00
#endif

#endif /* INCLUDE_GUARD_C_EIP201_H */

/* end of file c_eip201.h */
