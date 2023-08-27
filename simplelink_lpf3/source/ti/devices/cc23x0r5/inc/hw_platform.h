/******************************************************************************
 *  Copyright (c) 2021-2023 Texas Instruments Incorporated. All rights reserved.
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
 ******************************************************************************/
#ifndef __HW_PLATFORM_H__
#define __HW_PLATFORM_H__
#include "hw_memmap.h"
#include "hw_pmctl.h"

//*****************************************************************************
//
// Address, offset and constant definitions
//
//*****************************************************************************
// --- ROM definitions ---
/// Address of ROM FW revision structure
#define ROM_FWREV_ADDR (ROM_BASE + 0x0048)
/// Base address of HAPI table in ROM
#define ROM_HAPI_BASE  (ROM_BASE + 0x004C)
/// Address of CRC32 calculated over entire ROM
#define ROM_CRC_ADDR   (ROM_BASE + ROM_SIZE - 4)

// --- SRAM definitions ---
/// Magic value used in Fcfg.criticalTrim.sramRepair.magicWord to
/// indicate that SRAM repair information is valid
#define SRAMREP_MAGICWORD 0x40008100

//*****************************************************************************
//
// Boot status definitions (available through PMCTL::BOOTSTA) in addition to
// the defines listed in hw_pmctl.h
//
//*****************************************************************************
/// Boot sequence completed
#define PMCTL_BOOTSTA_BOOT_COMPLETE   (PMCTL_BOOTSTA_FLAG_MODE_BLDR)
/// Bootloader start initiated
#define PMCTL_BOOTSTA_BLDR_START_INIT (PMCTL_BOOTSTA_FLAG_MODE_BLDR | 0x02)
/// ROM serial bootloader complete
#define PMCTL_BOOTSTA_BLDR_COMPLETE   (PMCTL_BOOTSTA_FLAG_MODE_APP)
/// Application start initiated
#define PMCTL_BOOTSTA_APP_START_INIT  (PMCTL_BOOTSTA_FLAG_MODE_APP | 0x02)

#if !(defined(__ASM_INCLUDE__))
// Only included in C files

/// Data type for passing flags to bootloader/application entry function
typedef union
{
    uint32_t val32; ///< 32b value of word
    struct
    {
        uint32_t bCcfgValid:1;        ///< Is CCFG valid?
        uint32_t bAppCanBoot:1;       ///< Does a bootable application exist?
        uint32_t bChipEraseAllowed:1; ///< Is ChipErase operation allowed?
        uint32_t bParamsFromCcfg:1;   ///< Entry function params argument is CCFG(1) or FCFG(0)
        uint32_t bBldrAllowDbg:1;     ///< Is debugging of bootloader allowed?
        uint32_t res0:27;             ///< (Reserved for future use)
    } bldr;
} bldrEntryFlags_t;

#endif //!(defined(__ASM_INCLUDE__)

#endif // __HW_PLATFORM_H__
