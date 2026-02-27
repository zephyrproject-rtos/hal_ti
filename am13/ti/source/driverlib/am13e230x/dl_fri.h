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
 * @defgroup DL_FRI_AM13E230X  Driverlib FRI API
 * @ingroup DL_AM13E230X
 *
 * The FRI module manage the Flash read interface.
 *
 *
 * @{
 */

#ifndef DL_FRI_H
#define DL_FRI_H

#include <stdint.h>

#include <soc.h>
#include <dl_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name DL_FRI_DLB
 * @anchor DL_FRI_DLB
 *  @{
 */
/*! @brief Enables DATA line buffer on the DMA data read access path */
#define DL_FRI_DLB_ENABLED  ((uint32_t)0x00000002U)
/*! @brief Disables DATA line buffer on the DMA data read access path */
#define DL_FRI_DLB_DISABLED ((uint32_t)0x00000000U)
/** @}*/

/**
 * @name DL_FRI_CACHE
 * @anchor DL_FRI_CACHE
 *  @{
 */
/*! * @brief Enables cache on the CPU access path */
#define DL_FRI_CACHE_ENABLED  ((uint32_t)0x00000004U)
/*! * @brief Disables cache on the CPU access path */
#define DL_FRI_CACHE_DISABLED ((uint32_t)0x00000000U)
/** @}*/

/*! @brief Enables ECC */
#define DL_FRI_ECC_ENABLE  ((uint32_t)0x0000000AU)
/*! @brief Disables ECC */
#define DL_FRI_ECC_DISABLE ((uint32_t)0x00000000U)

/**
 * @name DL_FRI_ECC_TEST_MODE
 * @anchor DL_FRI_ECC_TEST_MODE
 *  @{
 */
/*! @brief Disables TEST MODE FOR ECC */
#define DL_FRI_ECC_TEST_MODE_DISABLE      ((uint32_t)0x00000000U)
/*! @brief Enables TEST MODE FOR ECC with 1 bit error */
#define DL_FRI_ECC_TEST_MODE_ENABLE_1_BIT ((uint32_t)0x00000001U)
/*! @brief Enables TEST MODE FOR ECC with 2 bits error */
#define DL_FRI_ECC_TEST_MODE_ENABLE_2_BIT ((uint32_t)0x00000003U)
/** @}*/

/**
 * @brief Configures caching in flash accesses and the data line buffer
 *        on the DMA data read access path
 *
 * @param dataLineBuffer [in]  data line buffer option @ref DL_FRI_DLB
 * @param Cache [in]  cache option @ref DL_FRI_CACHE
 *
 */
__STATIC_INLINE void DL_FRI_setCacheConfig(uint32_t dataLineBuffer, uint32_t Cache)
{
    FRI->FRD_INTF_CTRL = (dataLineBuffer | Cache);
}

/**
 * @brief Returns instruction prefetch, data line buffer and cache configuration
 *
 * @return Bitwise OR of @ref DL_FRI_DLB and @ref DL_FRI_CACHE
 */

__STATIC_INLINE uint32_t DL_FRI_getCacheConfig(void)
{
    return (FRI->FRD_INTF_CTRL & (FRI_FRD_INTF_CTRL_DLB_EN_MASK | FRI_FRD_INTF_CTRL_CACHE_EN_MASK));
}

/**
 * @brief Enable the data line buffer on the DMA data read access path
 */
__STATIC_INLINE void DL_FRI_enableDLB(void)
{
    FRI->FRD_INTF_CTRL = (FRI->FRD_INTF_CTRL | FRI_FRD_INTF_CTRL_DLB_EN_MASK);
}

/**
 * @brief Disable the data line buffer on the DMA data read access path
 */
__STATIC_INLINE void DL_FRI_disableDLB(void)
{
    FRI->FRD_INTF_CTRL = (FRI->FRD_INTF_CTRL & (~FRI_FRD_INTF_CTRL_DLB_EN_MASK));
}

/**
 * @brief Enable Flash Cache on the CPU access path, applicable for both code
 *        fetches as well as data reads
 */
__STATIC_INLINE void DL_FRI_enableCache(void)
{
    FRI->FRD_INTF_CTRL = (FRI->FRD_INTF_CTRL | FRI_FRD_INTF_CTRL_CACHE_EN_MASK);
}

/**
 * @brief Disable Flash Cache on the CPU access path, applicable for both code
 *        fetches as well as data reads
 */
__STATIC_INLINE void DL_FRI_disableCache(void)
{
    FRI->FRD_INTF_CTRL = (FRI->FRD_INTF_CTRL & (~FRI_FRD_INTF_CTRL_CACHE_EN_MASK));
}

/**
 * @brief Enable Flash ECC
 */
__STATIC_INLINE void DL_FRI_enableECC(void)
{
    uint32_t ctlTemp = DL_FRI_getCacheConfig();
    DL_FRI_setCacheConfig(DL_FRI_DLB_DISABLED, DL_FRI_CACHE_DISABLED);

    FRI->ECC_ENABLE = (FRI_ECC_ENABLE_MASK & DL_FRI_ECC_ENABLE);

    DL_Common_delayCycles(100);
    FRI->FRD_INTF_CTRL = ctlTemp;
}

/**
 * @brief Disable Flash ECC
 */
__STATIC_INLINE void DL_FRI_disableECC(void)
{
    uint32_t ctlTemp = DL_FRI_getCacheConfig();
    DL_FRI_setCacheConfig(DL_FRI_DLB_DISABLED, DL_FRI_CACHE_DISABLED);

    FRI->ECC_ENABLE = (FRI_ECC_ENABLE_MASK & DL_FRI_ECC_DISABLE);

    DL_Common_delayCycles(100);
    FRI->FRD_INTF_CTRL = ctlTemp;
}

/**
 * @brief Set Flash ECC Test Mode
 * @param[in] mode One of @ref DL_FRI_ECC_TEST_MODE
 */
__STATIC_INLINE void DL_FRI_setECCTestMode(uint32_t mode)
{
    FRI->FECC_CTRL = ((FRI_FECC_CTRL_ECC_TEST_EN_MASK)&mode);
}

/**
 * @brief Set zero waitstates for read/fetch
 */
__STATIC_INLINE void DL_FRI_setZeroReadWaitStates(void)
{
    FRI->FRDCNTL = ((FRI->FRDCNTL) | FRI_FRDCNTL_WS0_MODE_MASK);
}

/**
 * @brief Set the number of wait states added to a flash read/fetch access
 *
 *  Changes the number of wait states used by the Flash controller. When
 *  changing the frequency of the clock, the number of wait states may need to
 *  be updated.
 *  The RWAIT(states) value can be set anywhere from 0 to 0xF. For a flash access,
 *  data is returned in RWAIT+1 SYSCLK cycles.
 *
 *  @param[in]  states  Number of wait states to set. Recommended values
 *                      are based on the system clock speed:
 *                           - < 50MHZ        : 0 wait state
 *                           - 50MHz  - 100MHz: 1 wait state
 *                           - 100MHz - 150MHz: 2 wait states
 *                           - 150MHz - 200MHz: 3 wait states
 *
 */
void DL_FRI_setReadWaitStates(uint32_t states);

/**
 *  @brief Get the number of wait states used by the Flash
 *
 *  @return The number of wait states used by the Flash
 */
__STATIC_INLINE uint32_t DL_FRI_getReadWaitStates(void)
{
    uint32_t frdCntl = FRI->FRDCNTL;
    if (frdCntl & FRI_FRDCNTL_WS0_MODE_MASK)
    {
        frdCntl = 0;
    }
    else
    {
        frdCntl = (frdCntl & FRI_FRDCNTL_RWAIT_MASK) >> FRI_FRDCNTL_RWAIT_OFS;
    }
    return frdCntl;
}

#ifdef __cplusplus
}

#endif

#endif /* DL_FRI_H */
/** @}*/
