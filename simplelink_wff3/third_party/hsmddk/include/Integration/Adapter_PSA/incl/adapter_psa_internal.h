/* adapter_psa_internal.h
 *
 * PSA API Internal interfaces and definitions.
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

#ifndef INCLUDE_GUARD_ADAPTER_PSA_INTERNAL_H
#define INCLUDE_GUARD_ADAPTER_PSA_INTERNAL_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                   // size_t
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_alloc.h>


#define MAX_DMA_SIZE  0x001FFFFFU
#define SM3_BLOCK_SIZE (512U / 8U)

/*----------------------------------------------------------------------------
 * PSA_ASYM_DATA_V_HEADER
 *
 * The size of the HW asymmetric crypto element header.
 * bit 15..0  = SubVectorLength (in bits)
 * bit 23..16 = SubVectorIndex
 * bit 31..24 = NrOfSubVectors
 */
#define PSA_ASYM_DATA_VHEADER       (4U)

/*----------------------------------------------------------------------------
 * PSA_ASYM_DATA_SIZE_B2WB
 *
 * Converts a size in bits to a size in bytes aligned on a word boundary.
 */
static inline uint32_t
PSA_ASYM_DATA_SIZE_B2WB(const size_t x)
{
    return (uint32_t)(4U * ((x + 31U) / 32U));
}

/*----------------------------------------------------------------------------
 * PSA_ASYM_DATA_SIZE_WB
 *
 * Converts a size in bits to a size in words aligned on a word boundary.
 */
static inline uint32_t
PSA_ASYM_DATA_SIZE_WB(const size_t x)
{
    return (uint32_t)((x + 31U) / 32U);
}
/*----------------------------------------------------------------------------
 * PSA_ASYM_DATA_SIZE_VWB
 *
 * The size of a HW asymmetric crypto element in bytes based on a bits size.
 */
static inline uint32_t
PSA_ASYM_DATA_SIZE_VWB(const size_t x)
{
    return (uint32_t)(PSA_ASYM_DATA_VHEADER + PSA_ASYM_DATA_SIZE_B2WB(x));
}

#define PSA_ASYM_DATA_SIZE_VWB_MACRO(x) \
    (PSA_ASYM_DATA_VHEADER + (4U * ((x + 31U) / 32U)))


/*----------------------------------------------------------------------------
 * PSA_ASYM_DATA_SIZE_B2B
 *
 * Converts a size in bits to a size in bytes.
 */
static inline uint32_t
PSA_ASYM_DATA_SIZE_B2B(const size_t x)
{
    return (uint32_t)((x + 7U) / 8U);
}


/*----------------------------------------------------------------------------
 * discard_const
 */
static inline uint8_t *
psaInt_discard_const(const uint8_t * Ptr_p)
{
    union
    {
        const uint8_t *c_p;
        uint8_t *n_p;
    } Conversion;

    Conversion.c_p = Ptr_p;
    return Conversion.n_p;
}


/*----------------------------------------------------------------------------
 * psaInt_ReverseMemCpy
 *
 * This function performs a reverse memcpy.
 *
 * Dest_p
 *     Pointer to the destination buffer
 *
 * Src_p
 *     Pointer to the source buffer
 *
 * Size
 *     Size of the copy in bytes
 *
 * Return Value:
 *     N/A
 */
void
psaInt_ReverseMemCpy(uint8_t * Dest_p,
                     const uint8_t * Src_p,
                     size_t Size);


#endif /* INCLUDE_GUARD_ADAPTER_PSA_INTERNAL_H */

/* end of file adapter_psa_internal.h */
