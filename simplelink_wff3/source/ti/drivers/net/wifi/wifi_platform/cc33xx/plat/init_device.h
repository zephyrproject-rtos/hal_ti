/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef IDEV_H_
#define IDEV_H_

#include "osi_kernel.h"


/******************************************************************************
                                    DEFINE 
******************************************************************************/

struct hwinfo_bitmap
{
    uint32_t disable_5g                  : 1u;
    uint32_t disable_6g                  : 1u;
    uint32_t disable_ble                 : 1u;
    uint32_t disable_ble_m0plus          : 1u;
    uint32_t disable_m33                 : 1u;
    uint64_t udi                         : 64u;
    uint32_t pg_version                  : 4u;
    uint32_t metal_version               : 4u;
    uint32_t boot_rom_version            : 4u;
    uint32_t m3_rom_version              : 4u;
    uint32_t fuse_rom_structure_version  : 4u;
    uint64_t mac_address                 : 48u;
    uint32_t device_part_number          : 6u;
    uint32_t package_type                : 4u;
    uint32_t fw_rollback_protection_1    : 32u;
    uint32_t fw_rollback_protection_2    : 32u;
    uint32_t fw_rollback_protection_3    : 32u;
    uint32_t reserved                    : 13u;
} /* Aligned with boot code, must not be __packed */;


union hw_info
{
    struct hwinfo_bitmap    bitmap;
    uint8_t  bytes[sizeof (struct hwinfo_bitmap)] ;
};

/******************************************************************************
                      LOCAL FUNCTION PROTOTYPES
******************************************************************************/

int32_t init_device(uint32_t commandsEventsSizeBTL, uint32_t commandsEventsSize);

int32_t HwInit(void);

int32_t DeHwInit(void);

#endif /* IDEV_H_ */

