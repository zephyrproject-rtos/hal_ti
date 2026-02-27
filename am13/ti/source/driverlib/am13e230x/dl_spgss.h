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
 * @defgroup DL_SPGSS_AM13E230X  Driverlib SPGSS API
 * @ingroup DL_AM13E230X
 *
 * @{
 */

#ifndef DL_SPGSS_H
#define DL_SPGSS_H

#include "soc.h"
#include "dl_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! @brief DL_SPGSS_PAIR_CONTROLLER_SEL
    [NOTE] : Only unicomms withing the same SPGSS can be paired
    Example : UC0 can be paired with UC2 but not UC5
    (UC2 and UC0 belong to SPG0 , UC5 belongs to SPG1)
*/
typedef enum
{
    /*! Select UC0 as controller for loopback */
    DL_SPGSS_PAIR_CONTROLLER_UC0_ = SPGSS_PAIR0_CTL_SPG1,
    /*! Select UC1 as controller for loopback */
    DL_SPGSS_PAIR_CONTROLLER_UC1_ = SPGSS_PAIR0_CTL_SPG2,
    /*! Select UC2 as controller for loopback */
    DL_SPGSS_PAIR_CONTROLLER_UC2_ = SPGSS_PAIR0_CTL_SPG3,
    /*! Select UC3 as controller for loopback */
    DL_SPGSS_PAIR_CONTROLLER_UC3_ = SPGSS_PAIR0_CTL_SPG4,
    /*! Select UC4 as controller for loopback */
    DL_SPGSS_PAIR_CONTROLLER_UC4_ = SPGSS_PAIR0_CTL_SPG5,
    /*! Select UC5 as controller for loopback */
    DL_SPGSS_PAIR_CONTROLLER_UC5_ = SPGSS_PAIR0_CTL_SPG6,
} DL_SPGSS_PAIR_CONTROLLER_SEL;

/*! @brief DL_SPGSS_PAIR_TARGET_SEL */
typedef enum
{
    /*! Select UC0 as target for loopback */
    DL_SPGSS_PAIR_TARGET_UC0_ = SPGSS_PAIR0_TARGET_SPG1,
    /*! Select UC1 as target for loopback */
    DL_SPGSS_PAIR_TARGET_UC1_ = SPGSS_PAIR0_TARGET_SPG2,
    /*! Select UC2 as target for loopback */
    DL_SPGSS_PAIR_TARGET_UC2_ = SPGSS_PAIR0_TARGET_SPG3,
    /*! Select UC3 as target for loopback */
    DL_SPGSS_PAIR_TARGET_UC3_ = SPGSS_PAIR0_TARGET_SPG4,
    /*! Select UC4 as target for loopback */
    DL_SPGSS_PAIR_TARGET_UC4_ = SPGSS_PAIR0_TARGET_SPG5,
    /*! Select UC5 as target for loopback */
    DL_SPGSS_PAIR_TARGET_UC5_ = SPGSS_PAIR0_TARGET_SPG6,
} DL_SPGSS_PAIR_TARGET_SEL;

/*! @brief DL_SPGSS_PAIR_INDEX */
typedef enum
{
    /*! Loopback pair index 0 */
    DL_SPGSS_PAIR_INDEX_0 = 0,
    /*! Loopback pair index 1 */
    DL_SPGSS_PAIR_INDEX_1 = 1,
    /*! Loopback pair index 2 */
    DL_SPGSS_PAIR_INDEX_2 = 2,
    /*! Loopback pair index 3 */
    DL_SPGSS_PAIR_INDEX_3 = 3,
    /*! Loopback pair index 4 */
    DL_SPGSS_PAIR_INDEX_4 = 4,
    /*! Loopback pair index 5 */
    DL_SPGSS_PAIR_INDEX_5 = 5,
    /*! Loopback pair index 6 */
    DL_SPGSS_PAIR_INDEX_6 = 6,
    /*! Loopback pair index 7 */
    DL_SPGSS_PAIR_INDEX_7 = 7,
} DL_SPGSS_PAIR_INDEX;

/*! @brief DL_SPGSS_LPBK0_CONTROLLER_SEL
    [NOTE] : Only unicomms withing the same SPGSS can be paired
    Example : UC0 can be paired with UC2 but not UC5
    (UC2 and UC0 belong to SPG0 , UC5 belongs to SPG1)
*/
typedef enum
{
    /*! Select UC0 as controller for loopback */
    DL_SPGSS_LPBK0_CONTROLLER_UC0_ = SPGSS_LPBK0_CONTROLLER_SPG1,
    /*! Select UC1 as controller for loopback */
    DL_SPGSS_LPBK0_CONTROLLER_UC1_ = SPGSS_LPBK0_CONTROLLER_SPG2,
    /*! Select UC2 as controller for loopback */
    DL_SPGSS_LPBK0_CONTROLLER_UC2_ = SPGSS_LPBK0_CONTROLLER_SPG3,
    /*! Select UC3 as controller for loopback */
    DL_SPGSS_LPBK0_CONTROLLER_UC3_ = SPGSS_LPBK0_CONTROLLER_SPG4,
    /*! Select UC4 as controller for loopback */
    DL_SPGSS_LPBK0_CONTROLLER_UC4_ = SPGSS_LPBK0_CONTROLLER_SPG5,
    /*! Select UC5 as controller for loopback */
    DL_SPGSS_LPBK0_CONTROLLER_UC5_ = SPGSS_LPBK0_CONTROLLER_SPG6,
} DL_SPGSS_LPBK0_CONTROLLER_SEL;

/*! @brief DL_SPGSS_LPBK0_TARGET_SEL */
typedef enum
{
    /*! Select UC0 as target for loopback */
    DL_SPGSS_LPBK0_TARGET_UC0_ = SPGSS_LPBK0_PERIPHERAL_SPG1,
    /*! Select UC1 as target for loopback */
    DL_SPGSS_LPBK0_TARGET_UC1_ = SPGSS_LPBK0_PERIPHERAL_SPG2,
    /*! Select UC2 as target for loopback */
    DL_SPGSS_LPBK0_TARGET_UC2_ = SPGSS_LPBK0_PERIPHERAL_SPG3,
    /*! Select UC3 as target for loopback */
    DL_SPGSS_LPBK0_TARGET_UC3_ = SPGSS_LPBK0_PERIPHERAL_SPG4,
    /*! Select UC4 as target for loopback */
    DL_SPGSS_LPBK0_TARGET_UC4_ = SPGSS_LPBK0_PERIPHERAL_SPG5,
    /*! Select UC5 as target for loopback */
    DL_SPGSS_LPBK0_TARGET_UC5_ = SPGSS_LPBK0_PERIPHERAL_SPG6,
} DL_SPGSS_LPBK0_TARGET_SEL;

/**
 * @brief  Configuration struct for @ref DL_SPGSS_setPairLoopbackConfig.
 */
typedef struct
{
    /*! SPGSS pairing controller selection. One of @ref DL_SPGSS_PAIR_CONTROLLER_SEL */
    DL_SPGSS_PAIR_CONTROLLER_SEL controller;
    /*! SPGSS pairing target selection. One of @ref DL_SPGSS_PAIR_TARGET_SEL */
    DL_SPGSS_PAIR_TARGET_SEL     target;
} DL_SPGSS_PairLoopbackConfig;

/**
 * @brief  Configuration struct for @ref DL_SPGSS_setLoopbackConfig.
 */
typedef struct
{
    /*! SPGSS Loopback controller selection. One of @ref DL_SPGSS_LPBK0_CONTROLLER_SEL */
    DL_SPGSS_LPBK0_CONTROLLER_SEL controller;
    /*! SPGSS Loopback target selection. One of @ref DL_SPGSS_LPBK0_TARGET_SEL */
    DL_SPGSS_LPBK0_TARGET_SEL     target;
} DL_SPGSS_LoopbackConfig;

/**
 *  @brief      Enable SPGSS pair loopback
 *
 *  @param[in]  spgss  Pointer to the register overlay for the peripheral
 *  @param[in]  index  Specifies pair index to be configured. One of
 *                        @ref DL_SPGSS_PAIR_INDEX.
 */
__STATIC_INLINE void DL_SPGSS_enablePairLoopback(SPGSS_Regs *spgss, DL_SPGSS_PAIR_INDEX index)
{
    volatile uint32_t *pReg = &spgss->I2C_PAIR.PAIR0;

    *(pReg + (uint32_t)index) |= (SPGSS_PAIR0_EN_ENABLE);
}

/**
 *  @brief      Disable SPGSS pair loopback
 *
 *  @param[in]  spgss  Pointer to the register overlay for the peripheral
 *  @param[in]  index  Specifies pair index to be configured. One of
 *                        @ref DL_SPGSS_PAIR_INDEX.
 */
__STATIC_INLINE void DL_SPGSS_disablePairLoopback(SPGSS_Regs *spgss, DL_SPGSS_PAIR_INDEX index)
{
    volatile uint32_t *pReg = &spgss->I2C_PAIR.PAIR0;

    *(pReg + (uint32_t)index) &= ~(SPGSS_PAIR0_EN_ENABLE);
}

/**
 *  @brief      Set SPG controller and target for loopback
 *
 *  @param[in]  spgss  Pointer to the register overlay for the peripheral
 *  @param[in]  index  Specifies pair index to be configured. One of
 *                        @ref DL_SPGSS_PAIR_INDEX.
 *  @param[in]  config  Pointer to the pair configuration struct
 *                      @ref DL_SPGSS_LoopbackConfig.
 */
__STATIC_INLINE void DL_SPGSS_setPairLoopbackConfig(SPGSS_Regs *spgss, DL_SPGSS_PAIR_INDEX index,
                                                    DL_SPGSS_PairLoopbackConfig *config)
{
    volatile uint32_t *pReg = &spgss->I2C_PAIR.PAIR0;

    DL_Common_updateReg((pReg + (uint32_t)index), ((uint32_t)config->controller | (uint32_t)config->target),
                        (SPGSS_PAIR0_CTL_MASK | SPGSS_PAIR0_TARGET_MASK));
}

/**
 *  @brief      Get SPG controller and target for loopback
 *
 *  @param[in]  spgss  Pointer to the register overlay for the peripheral
 *  @param[in]  index  Specifies loopback index to be configured. One of
 *                        @ref DL_SPGSS_PAIR_INDEX.
 *  @param[in]  config  Pointer to the pair configuration struct
 *                      @ref DL_SPGSS_LoopbackConfig.
 */
__STATIC_INLINE void DL_SPGSS_getPairLoopbackConfig(SPGSS_Regs *spgss, DL_SPGSS_PAIR_INDEX index,
                                                    DL_SPGSS_PairLoopbackConfig *config)
{
    volatile uint32_t *pReg = &spgss->I2C_PAIR.PAIR0;

    config->controller = (DL_SPGSS_PAIR_CONTROLLER_SEL)(uint32_t)(*(pReg + (uint32_t)index) & SPGSS_PAIR0_CTL_MASK);
    config->target     = (DL_SPGSS_PAIR_TARGET_SEL)(uint32_t)(*(pReg + (uint32_t)index) & SPGSS_PAIR0_TARGET_MASK);
}

/**
 *  @brief      Enable SPGSS loopback
 *
 *  @param[in]  spgss  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_SPGSS_enableLoopback(SPGSS_Regs *spgss)
{
    volatile uint32_t *loopbackReg = &spgss->UNICOMM_LPBK.LPBK0;

    DL_Common_updateReg(loopbackReg, SPGSS_LPBK0_EN_ENABLE, SPGSS_LPBK0_EN_MASK);
}

/**
 *  @brief      Disable SPGSS loopback
 *
 *  @param[in]  spgss  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_SPGSS_disableLoopback(SPGSS_Regs *spgss)
{
    volatile uint32_t *loopbackReg = &spgss->UNICOMM_LPBK.LPBK0;

    DL_Common_updateReg(loopbackReg, SPGSS_LPBK0_EN_DISABLE, SPGSS_LPBK0_EN_MASK);
}

/**
 *  @brief      Set SPG controller and target for loopback
 *
 *  @param[in]  spgss  Pointer to the register overlay for the peripheral
 *  @param[in]  config  Pointer to the configuration struct
 *                      @ref DL_SPGSS_LoopbackConfig.
 */
__STATIC_INLINE void DL_SPGSS_setLoopbackConfig(SPGSS_Regs *spgss, DL_SPGSS_LoopbackConfig *config)
{
    volatile uint32_t *loopbackReg = &spgss->UNICOMM_LPBK.LPBK0;

    DL_Common_updateReg((loopbackReg), ((uint32_t)config->controller | (uint32_t)config->target),
                        (SPGSS_LPBK0_CONTROLLER_MASK | SPGSS_LPBK0_PERIPHERAL_MASK));
}

/**
 *  @brief      Get SPG controller and target for loopback
 *
 *  @param[in]  spgss  Pointer to the register overlay for the peripheral
 *  @param[in]  config  Pointer to the configuration struct
 *                      @ref DL_SPGSS_LoopbackConfig.
 */
__STATIC_INLINE void DL_SPGSS_getLoopbackConfig(SPGSS_Regs *spgss, DL_SPGSS_LoopbackConfig *config)
{
    volatile uint32_t *loopbackReg = &spgss->UNICOMM_LPBK.LPBK0;

    config->controller = (DL_SPGSS_LPBK0_CONTROLLER_SEL)(uint32_t)(*(loopbackReg)&SPGSS_LPBK0_CONTROLLER_MASK);
    config->target     = (DL_SPGSS_LPBK0_TARGET_SEL)(uint32_t)(*(loopbackReg)&SPGSS_LPBK0_PERIPHERAL_MASK);
}

#ifdef __cplusplus
}
#endif

#endif /* DL_SPGSS_H */
/** @}*/
