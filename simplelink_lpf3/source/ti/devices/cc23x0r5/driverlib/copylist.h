/******************************************************************************
 *  Copyright (c) 2022-2023 Texas Instruments Incorporated. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************
 *  \file       copylist.h
 *
 *  \brief      Copy list format used to apply FCFG, CCFG, and standby wakeup
 *              configurations.
 *
 ******************************************************************************/

#ifndef __COPYLIST_H__
#define __COPYLIST_H__

#include <stdint.h>

#include "hapi.h"

#include "../inc/hw_types.h"

//*****************************************************************************
//
//! \brief Copy list macro to end a copy list
//!
//! Processing of the copy list with CopyList_apply() will stop upon
//! encountering this entry.
//!
//! Command      |31:28|27:20    |19:2                  |1:0|LW|Description
//! -------------|-----|---------|----------------------|---|--|----------------
//! EOL          |0000 |0000_0000|0000_0000_0000_0000_00|00 |0 |End-of-list
//!
//! \sa CopyList_apply()
//
//*****************************************************************************
#define CopyList_EOL 0U

//*****************************************************************************
//
//! \brief Copy list macro to do nothing.
//!
//! Command      |31:28|27:20    |19:2                  |1:0|LW|Description
//! -------------|-----|---------|----------------------|---|--|----------------
//! NOP = WAIT(0)|0001 |0000_0000|0000_0000_0000_0000_00|00 |0 |No operation
//!
//! \sa CopyList_apply()
//
//*****************************************************************************
#define CopyList_NOP CopyList_WAIT(0U)

//*****************************************************************************
//
//! \brief Copy list macro for waiting \c n iterations of a do-nothing loop
//!
//! Command      |31:28|27:20    |19:2                  |1:0|LW|Description
//! -------------|-----|---------|----------------------|---|--|----------------
//! WAIT(N)      |0001 |0000_0000|nnnn_nnnn_nnnn_nnnn_nn|00 |0 |Wait N/12 us
//!
//! \param[in] n Number of iterations to wait. Must be in range [1, 2^18 - 1].
//!
//! \sa CopyList_apply()
//
//*****************************************************************************
#define CopyList_WAIT(n) (0x10000000U | (((uint32_t)n << 2U) & 0xFFFFCU))

//*****************************************************************************
//
//! \brief Copy list macro for copying a single literal to a specified address
//!
//! This macro copies a 32-bit literal to a specified \c address. This command
//! expects the next word in the copy list to be the literal it is supposed to
//! copy.
//!
//! Command      |31:28|27:20    |19:2                  |1:0|LW|Description
//! -------------|-----|---------|----------------------|---|--|----------------
//! CPY(A,1)     |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|01 |1 |Copy single literal word to full address A
//!
//! \param[in] address Address to copy the following literal to. The address
//!                    must be word-aligned.
//!
//! \sa CopyList_apply()
//
//*****************************************************************************
#define CopyList_COPY(address) ((uint32_t)address | 0x1U)

//*****************************************************************************
//
//! \brief Copy list macro for copying multiple literals to a specified address
//!
//! This macro copies \c n 32-bit literal to a specified \c address. This
//! command expects the next \c n words in the copy list to be the literal it is
//! supposed to copy.
//!
//! Command      |31:28|27:20    |19:2                  |1:0|LW|Description
//! -------------|-----|---------|----------------------|---|--|----------------
//! CPY(A*,N)    |aaaa |nnnn_nnnn|aaaa_aaaa_aaaa_aaaa_aa|00 |N |Copy N literal words to address A*
//!
//! The devices' address space is arranged such that bits 20:27 are not actually
//! needed to specify any valid address.
//!
//! \param[in] address Address to copy the following literals to. The address
//!                    must be word-aligned.
//!
//! \param[in] n Number of words to copy. Must be in range [1, 255]
//!
//! \sa CopyList_apply()
//
//*****************************************************************************
#define CopyList_COPY_MULTI(address, n) (((uint32_t)address & 0xF00FFFFCU) | (((uint32_t)n << 20U) & 0xFF00000U))

//*****************************************************************************
//
//! \brief Copy list macro for continuing copy list processing at a new address
//!
//! This macro continues processing the copy list at \c address.
//!
//! Command      |31:28|27:20    |19:2                  |1:0|LW|Description
//! -------------|-----|---------|----------------------|---|--|----------------
//! JMP(A)       |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|10 |0 |Jump to new list at full address A
//!
//! \param[in] address Address to continue processing the copy list at. The
//!                    address must be word-aligned.
//!
//! \sa CopyList_apply()
//
//*****************************************************************************
#define CopyList_JUMP(address) ((uint32_t)address | 0x2U)

//*****************************************************************************
//
//! \brief Copy list macro to recurse to a new list
//!
//! Recurse into new list at \c address by invoking CopyList_apply(). Once this
//! list ends it will return back here and continue parsing this list.
//!
//! Command      |31:28|27:20    |19:2                  |1:0|LW|Description
//! -------------|-----|---------|----------------------|---|--|----------------
//! CALL(A)      |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|11 |0 |Recurse to list at full address A
//!
//! \param[in] address Address to continue processing the copy list at. The
//!                    address must be word-aligned.
//!
//! \sa CopyList_apply()
//
//*****************************************************************************
#define CopyList_CALL(address) ((uint32_t)address | 0x3U)

//*****************************************************************************
//
//! \brief Process copy list
//! Processes a copy list in a flexible CopyList format. Used by trims
//! in FCFG, for user-defined initialization in CCFG and may be used by
//! peripheral drivers to do HW reinitialization during wakeup from standby.
//! The copy list is processed as a sequence of 32b command words, followed by
//! zero or more literal words (LW):
//!
//! Command      |31:28|27:20    |19:2                  |1:0|LW|Description
//! -------------|-----|---------|----------------------|---|--|----------------
//! EOL          |0000 |0000_0000|0000_0000_0000_0000_00|00 |0 |End-of-list
//! WAIT(N)      |0001 |0000_0000|nnnn_nnnn_nnnn_nnnn_nn|00 |0 |Wait N/12 us
//! NOP = WAIT(0)|0001 |0000_0000|0000_0000_0000_0000_00|00 |0 |No operation
//! CPY(A*,N)    |aaaa |nnnn_nnnn|aaaa_aaaa_aaaa_aaaa_aa|00 |N |Copy N literal words to address A*
//! CPY(A,1)     |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|01 |1 |Copy single literal word to full address A
//! JMP(A)       |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|10 |0 |Jump to new list at full address A
//! CALL(A)      |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|11 |0 |Recurse to list at full address A
//!
//! A* is a reduced address space that covers all SRAM and peripheral space.
//! Bits 27:20 of this address will be assumed to be all zero. Full addresses
//! must have 32b alignment
//!
//! \param[in] list Pointer to the copy list
//
//*****************************************************************************
__STATIC_INLINE void CopyList_apply(const uint32_t *list)
{
    HapiApplyCopyList(list);
}

#endif //__COPYLIST_H__
