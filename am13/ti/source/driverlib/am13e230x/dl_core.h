/*This file is AUTO GENERATED, DO NOT EDIT manually*/

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

/**
 * @defgroup DL_CORE_AM13E230X  Driverlib CORE API
 * @ingroup DL_AM13E230X
 *
 * The Core module enables software to read from core registers of the CPU to
 * get more information about the device at runtime.
 *
 * @{
 */

#ifndef DL_CORE_H
#define DL_CORE_H

#include <stdint.h>

#include <soc.h>
#include <dl_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief   Get the implementer code for the processor
 *
 *  @return  The implementer code
 *
 *  @retval  0x41 for ARM
 */
__STATIC_INLINE uint32_t DL_CORE_getImplementer(void)
{
    return ((SCB->CPUID & SCB_CPUID_IMPLEMENTER_Msk) >> SCB_CPUID_IMPLEMENTER_Pos);
}

/**
 *  @brief   Get the major revision number 'n' in the 'npm' revision status
 *
 *  @return  The major revision number
 *
 *  @retval  0x01 for revision 0
 */
__STATIC_INLINE uint32_t DL_CORE_getVariant(void)
{
    return ((SCB->CPUID & SCB_CPUID_VARIANT_Msk) >> SCB_CPUID_VARIANT_Pos);
}

/**
 *  @brief   Get the architecture of the processor
 *
 *  @return  Value that defines the architecture of the processor
 *
 *  @retval  constant 0xF for Cortex-M33
 */
__STATIC_INLINE uint32_t DL_CORE_getArchitecture(void)
{
    return ((SCB->CPUID & SCB_CPUID_ARCHITECTURE_Msk) >> SCB_CPUID_ARCHITECTURE_Pos);
}

/**
 *  @brief   Get part number of the processor (not the device)
 *
 *  @return  Value that defines the processor
 *
 *  @retval  0xD21 for Cortex-M33
 */
__STATIC_INLINE uint32_t DL_CORE_getPartNumber(void)
{
    return ((SCB->CPUID & SCB_CPUID_PARTNO_Msk) >> SCB_CPUID_PARTNO_Pos);
}

/**
 *  @brief   Get the minor revision number 'm' in the 'npm' revision status
 *
 *  @return  The minor revision number
 *
 *  @retval  0x00 for patch 0
 */
__STATIC_INLINE uint32_t DL_CORE_getRevision(void)
{
    return ((SCB->CPUID & (uint32_t)SCB_CPUID_REVISION_Msk) >> (uint32_t)SCB_CPUID_REVISION_Pos);
}

/**
 * @brief Enable ROM wait state configuration
 */
__STATIC_INLINE void DL_CORE_enableROMWaitState(void)
{
    MEMCFG->ROM_WS_CONFIG = (MEMCFG->ROM_WS_CONFIG | MEMCFG_ROM_WS_CONFIG_ROM_WS_ENABLE_MASK);
}

/**
 * @brief Disable ROM wait state configuration
 */
__STATIC_INLINE void DL_CORE_disableROMWaitState(void)
{
    MEMCFG->ROM_WS_CONFIG = (MEMCFG->ROM_WS_CONFIG & (~MEMCFG_ROM_WS_CONFIG_ROM_WS_ENABLE_MASK));
}

#ifdef __cplusplus
}

#endif

#endif /* DL_CORE_H */
/** @}*/
