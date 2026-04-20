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
 * @defgroup DL_UNICOMM_AM13E230X  Driverlib UNICOMM API
 * @ingroup DL_AM13E230X
 *
 * @{
 */

#ifndef DL_UNICOMM_H
#define DL_UNICOMM_H

#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! @brief  Configuration struct for Unicomm Registers. */
typedef struct
{
    /*! Unicomm Instance Pointer */
    UNICOMM_Regs *const     inst;
    /*! Unicomm Uart Instance Pointer */
    UNICOMMUART_Regs *const uart;
    /*! Unicomm I2CC Instance Pointer */
    UNICOMMI2CC_Regs *const i2cc;
    /*! Unicomm I2CT Instance Pointer */
    UNICOMMI2CT_Regs *const i2ct;
    /*! Unicomm SPI Instance Pointer */
    UNICOMMSPI_Regs *const  spi;
    /*! Mode */
    bool const              fixedMode;
} DL_UNICOMM_Inst_Regs;

/*! @brief  Configuration struct for Unicomm0 Registers. */
extern const DL_UNICOMM_Inst_Regs UC0_Inst;

/*! @brief  Configuration struct for Unicomm1 Registers. */

extern const DL_UNICOMM_Inst_Regs UC1_Inst;
/*! @brief  Configuration struct for Unicomm2 Registers. */

extern const DL_UNICOMM_Inst_Regs UC2_Inst;

/*! @brief  Configuration struct for Unicomm3 Registers. */

extern const DL_UNICOMM_Inst_Regs UC3_Inst;

/*! @brief  Configuration struct for Unicomm4 Registers. */
extern const DL_UNICOMM_Inst_Regs UC4_Inst;

/*! @brief  Configuration struct for Unicomm5 Registers. */
extern const DL_UNICOMM_Inst_Regs UC5_Inst;

/* Non-Const static pointers for Legacy compatibility */

static DL_UNICOMM_Inst_Regs *UC0_INST_PTR = (DL_UNICOMM_Inst_Regs *)&UC0_Inst;
static DL_UNICOMM_Inst_Regs *UC1_INST_PTR = (DL_UNICOMM_Inst_Regs *)&UC1_Inst;
static DL_UNICOMM_Inst_Regs *UC2_INST_PTR = (DL_UNICOMM_Inst_Regs *)&UC2_Inst;
static DL_UNICOMM_Inst_Regs *UC3_INST_PTR = (DL_UNICOMM_Inst_Regs *)&UC3_Inst;
static DL_UNICOMM_Inst_Regs *UC4_INST_PTR = (DL_UNICOMM_Inst_Regs *)&UC4_Inst;
static DL_UNICOMM_Inst_Regs *UC5_INST_PTR = (DL_UNICOMM_Inst_Regs *)&UC5_Inst;

/*! @brief DL_UNICOMM_IP_MODE_SEL */

typedef enum
{
    /*! Select UART functionality */
    DL_UNICOMM_UART           = UNICOMM_IPMODE_SELECT_UART,
    /*! Select SPI functionality*/
    DL_UNICOMM_SPI            = UNICOMM_IPMODE_SELECT_SPI,
    /*! Select I2C functionality in controller mode */
    DL_UNICOMM_I2C_CONTROLLER = UNICOMM_IPMODE_SELECT_I2C_CONTROLLER,
    /*! Select I2C functionality in target mode */
    DL_UNICOMM_I2C_TARGET     = UNICOMM_IPMODE_SELECT_I2C_PERIPHERAL,
} DL_UNICOMM_IP_MODE_SEL;

/**
 *  @brief Enables power on unicomm module
 *
 *  @param unicomm        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UNICOMM_enablePower(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->inst->GPRCM.PWREN = (UNICOMM_PWREN_KEY_UNLOCK_W | UNICOMM_PWREN_ENABLE_ENABLE);

    __DSB();
    __ISB();
}

/**
 *  @brief Disables power on unicomm module
 *
 *  @param unicomm        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UNICOMM_disablePower(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->inst->GPRCM.PWREN = (UNICOMM_PWREN_KEY_UNLOCK_W | UNICOMM_PWREN_ENABLE_DISABLE);
}

/**
 *  @brief Returns if  power on unicomm module
 *
 *  @param unicomm        Pointer to the register overlay for the peripheral
 *
 *  @return true if power is enabled
 *  @return false if power is disabled
 */
__STATIC_INLINE bool DL_UNICOMM_isPowerEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->inst->GPRCM.PWREN & UNICOMM_PWREN_ENABLE_MASK) == UNICOMM_PWREN_ENABLE_ENABLE);
}

/**
 *  @brief Resets unicomm peripheral
 *
 *  @param unicomm        Pointer to the register overlay for the UNICOMM peripheral
 */
__STATIC_INLINE void DL_UNICOMM_reset(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->inst->GPRCM.RSTCTL =
        (UNICOMM_RSTCTL_KEY_UNLOCK_W | UNICOMM_RSTCTL_RESETSTKYCLR_CLR | UNICOMM_RSTCTL_RESETASSERT_ASSERT);
}

/**
 *  @brief Returns if unicomm peripheral was reset
 *
 *  @param unicomm        Pointer to the register overlay for the UNICOMM peripheral
 *
 *  @return true if peripheral was reset
 *  @return false if peripheral wasn't reset
 *
 */
__STATIC_INLINE bool DL_UNICOMM_isReset(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->inst->GPRCM.STAT & UNICOMM_STAT_RESETSTKY_MASK) == UNICOMM_STAT_RESETSTKY_RESET);
}

/**
 *  @brief Configure the unicomm peripheral for specified ip mode
 *
 *  @param unicomm        Pointer to the register overlay for the UNICOMM peripheral
 *  @param ipMode         Specifies IP mode functionality. One of @ref DL_UNICOMM_IP_MODE_SEL
 */
__STATIC_INLINE void DL_UNICOMM_setIPMode(DL_UNICOMM_Inst_Regs *unicomm, DL_UNICOMM_IP_MODE_SEL ipMode)
{
    unicomm->inst->IPMODE = (ipMode & UNICOMM_IPMODE_SELECT_MASK);
}

/**
 *  @brief Returns ip mode the unicomm peripheral is configured to
 *
 *  @param unicomm        Pointer to the register overlay for the UNICOMM peripheral
 *
 *  @return  Configured IP mode selection
 *  @retval  One of @ref DL_UNICOMM_IP_MODE_SEL
 */
__STATIC_INLINE DL_UNICOMM_IP_MODE_SEL DL_UNICOMM_getIPMode(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (DL_UNICOMM_IP_MODE_SEL)(unicomm->inst->IPMODE & UNICOMM_IPMODE_SELECT_MASK);
}
/**
 *  @brief Returns whether the IP is advanced IP or not
 *
 *  @param unicomm        Pointer to the register overlay for the UNICOMM peripheral
 *
 *  @return  IP advanced capable or not
 *  @retval  bool
 */

__STATIC_INLINE bool DL_UNICOMM_isAdvanceFeaturesEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (bool)((unicomm == &UC2_Inst) || (unicomm == &UC5_Inst));
}

#ifdef __cplusplus
}
#endif

#endif /* DL_UNICOMM_H */
       /** @}*/
