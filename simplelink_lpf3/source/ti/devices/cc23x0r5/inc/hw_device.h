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
#ifndef __HW_DEVICE_H__
#define __HW_DEVICE_H__

#include "hw_memmap.h"
#include "hw_platform.h"

//*****************************************************************************
//
// Address, offset and size definitions
//
//*****************************************************************************

// --- ROM definitions ---
/// Size of the call stack used in ROM, in number of bytes
#define BOOT_CSTACK_SIZE                        (1024-sizeof(fcfg_appTrims_t))

// --- FLASH definitions ---
/// Size of a 1T flash sector, in number of bytes
#define FLASH_1T_SECTOR_SIZE                    2048
/// Flash word width in number of bits
#define FLASH_DATAWIDTH_BITS                    128
/// Size of a 2T flash sector, in number of bytes
#define FLASH_2T_SECTOR_SIZE                    (FLASH_1T_SECTOR_SIZE/2)
/// Size of a MAIN flash sector, in number of bytes
#define FLASH_MAIN_SECTOR_SIZE                  FLASH_1T_SECTOR_SIZE

// --- Factory Configuration (FCFG) definitions ---
/// Size of generalTrims section in FCFG, in number of 32-bit words
#define FCFG_GENERALTRIMS_SIZE                  ((FLASH_2T_SECTOR_SIZE / 4) - 104)

// --- Customer Configuration (CCFG) definitions ---
/*! Macro for default CCFG configuration. All fields can be overwritten by
 *  setting the field to another value further down in the struct definition
 *  within a C file.
 */
#define CCFG_DEFAULT_VALUES \
    .bootCfg = { \
        .pBldrVtor = XCFG_BC_PBLDR_UNDEF, \
        .bldrParam = { 0x00000000 }, \
        .pAppVtor = CCFG_BC_PAPP_NONE, \
        .crc32 = 0x0BAD0BAD \
    }, \
    .hwOpts[0] = 0xFFFFFFFF, \
    .hwOpts[1] = 0xFFFFFFFF, \
    .permissions = { \
        .allowReturnToFactory   = CCFG_PERMISSION_ALLOW, \
        .allowFakeStby          = CCFG_PERMISSION_ALLOW, \
        .allowToolsClientMode   = CCFG_PERMISSION_ALLOW, \
        .allowChipErase         = CCFG_PERMISSION_ALLOW, \
        .allowFlashProgram      = CCFG_PERMISSION_ALLOW, \
        .allowFlashVerify       = CCFG_PERMISSION_ALLOW, \
        .allowEnergyTrace       = CCFG_PERMISSION_ALLOW, \
        .allowDebugPort         = CCFG_PERMISSION_ALLOW, \
    }, \
    .misc = { \
        .saciTimeoutOverride = 0 \
    }, \
    .flashProt = { \
        .writeEraseProt = { \
            .mainSectors0_31   = 0xFFFFFFFF, \
            .mainSectors32_255 = 0xFFFFFFFF, \
            .auxSectors        = 0xFFFFFFFF, \
        }, \
        .res = 0xFFFFFFFF, \
        .chipEraseRetain = { \
            .mainSectors0_31   = 0, \
            .mainSectors32_255 = 0, \
        } \
    }, \
    .hwInitCopyList = { CPYLST_EOL }, \
    .crc32 = 0x0BAD0BAD, \
    .userRecord.crc32 = 0x0BAD0BAD, \
    .debugCfg = { \
        .authorization = CCFG_DBGAUTH_DBGOPEN, \
        .allowBldr = CCFG_DBGBLDR_ALLOW, \
        .pwdId = {1, 1, 2, 3, 5, 8, 13, 21 }, \
        .pwdHash = { /* SHA256 of "Open Sesame!" */ \
            0x6D, 0xD7, 0xE4, 0x36, 0xEB, 0xF4, 0x31, 0xDF, \
            0x95, 0xAE, 0x15, 0xEE, 0x03, 0xBA, 0x8E, 0xE4, \
            0xC4, 0xC6, 0x3F, 0xD8, 0x45, 0x3F, 0x67, 0x5E, \
            0x74, 0xD7, 0xC2, 0x01, 0x2C, 0x90, 0x58, 0xE5, \
        }, \
        .crc32 = 0x0BAD0BAD, \
    }
#endif // __HW_DEVICE_H__
