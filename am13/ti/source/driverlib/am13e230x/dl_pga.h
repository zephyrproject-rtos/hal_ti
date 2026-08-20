
// This file is AUTO GENERATED, DO NOT EDIT manually

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
 * @defgroup DL_PGA_AM13E230X  Driverlib PGA API
 * @ingroup DL_AM13E230X
 *
 *@{
 */

#ifndef DL_PGA_H
#define DL_PGA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "soc.h"
#include "dl_common.h"
#include "hw_pga.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 * @name DL_PGA_REG_LOCK
 * @anchor DL_PGA_REG_LOCK
 * @{
 */
/*! @brief PGA Control Register Lock */
#define DL_PGA_REG_LOCK_PGACTL PGA_PGALOCK_PGACTL_MASK
/*! @brief PGA Multiplexer Selection Register Lock */
#define DL_PGA_REG_LOCK_MUXSEL PGA_PGALOCK_MUXSEL_MASK
/** @}*/

/*! @brief PGA Gain Values */
typedef enum
{
    /*! PGA gain value of 1 */
    DL_PGA_GAIN_1  = 0x0U,
    /*! PGA gain value of 2 or -1 */
    DL_PGA_GAIN_2  = 0x20U,
    /*! PGA gain value of 4 or -3 */
    DL_PGA_GAIN_4  = 0x40U,
    /*! PGA gain value of 8 or -7 */
    DL_PGA_GAIN_8  = 0x60U,
    /*! PGA gain value of 16 or -15 */
    DL_PGA_GAIN_16 = 0x80U,
    /*! PGA gain value of 32 or -31 */
    DL_PGA_GAIN_32 = 0xA0U,
    /*! PGA gain value of 64 or -63 */
    DL_PGA_GAIN_64 = 0xC0U
} DL_PGA_GAIN_VALUE;

/*! @brief PGA Low Pass Filter Resistor Values */
typedef enum
{
    /*! Low pass filter disabled (open circuit) */
    DL_PGA_LOW_PASS_FILTER_DISABLED         = 0U,
    /*! Resistor value of 50 Ohm */
    DL_PGA_LOW_PASS_FILTER_RESISTOR_50_OHM  = 2U,
    /*! Resistor value of 100 Ohm */
    DL_PGA_LOW_PASS_FILTER_RESISTOR_100_OHM = 4U,
    /*! Resistor value of 200 Ohm */
    DL_PGA_LOW_PASS_FILTER_RESISTOR_200_OHM = 6U,
    /*! Resistor value of 400 Ohm */
    DL_PGA_LOW_PASS_FILTER_RESISTOR_400_OHM = 8U,
    /*! Resistor value of 800 Ohm */
    DL_PGA_LOW_PASS_FILTER_RESISTOR_800_OHM = 10U
} DL_PGA_LOW_PASS_RESISTOR_VALUE;

/*! @brief PGA PMUX Input Selection */
typedef enum
{
    /*! PGA_INP0 as non-inverting input */
    DL_PGA_PMUX_INP0 = 0x00U,
    /*! PGA_INP1 as non-inverting input */
    DL_PGA_PMUX_INP1 = 0x01U,
    /*! PGA_INP2 as non-inverting input */
    DL_PGA_PMUX_INP2 = 0x02U,
    /*! PGA_INP3 as non-inverting input */
    DL_PGA_PMUX_INP3 = 0x03U,
    /*! PGA_INP4 as non-inverting input */
    DL_PGA_PMUX_INP4 = 0x04U,
    /*! PGA_INP5 as non-inverting input */
    DL_PGA_PMUX_INP5 = 0x05U,
    /*! PGA_INP6 as non-inverting input */
    DL_PGA_PMUX_INP6 = 0x06U,
    /*! PGA_INP7 as non-inverting input */
    DL_PGA_PMUX_INP7 = 0x07U,
    /*! PGA_INP8 as non-inverting input */
    DL_PGA_PMUX_INP8 = 0x08U
} DL_PGA_PMUX_INPUT;

/*! @brief PGA NMUX Input Selection */
typedef enum
{
    /*! RTOP (Inter Gain Resistor Tap Point) as inverting input */
    DL_PGA_NMUX_RTOP = 0x00U,
    /*! RTAP (Pre Gain Resistor Tap Point) as inverting input */
    DL_PGA_NMUX_RTAP = 0x01U,
    /*! PGA_INM0 as inverting input */
    DL_PGA_NMUX_INM0 = 0x02U,
    /*! PGA_INM1 as inverting input */
    DL_PGA_NMUX_INM1 = 0x03U,
    /*! PGA_INM2 as inverting input */
    DL_PGA_NMUX_INM2 = 0x04U,
    /*! PGA_INM3 as inverting input */
    DL_PGA_NMUX_INM3 = 0x05U
} DL_PGA_NMUX_INPUT;

/*! @brief PGA MMUX Input Selection */
typedef enum
{
    /*!  Stand alone op-amp or G=1 mode select */
    DL_PGA_MMUX_NAKED_OPAMP             = 0x00U,
    /*! Non-Inverting gain mode select, feeback resistors have path to VSSA */
    DL_PGA_MMUX_NON_INVERTING_GAIN_VSSA = 0x01U,
    /*! Inverting gain mode select, feedback resistors have path to local PGA_INM0 pin */
    DL_PGA_MMUX_INM0                    = 0x02U,
    /*! Inverting gain mode select, feedback resistors have path to local PGA_INM1 pin */
    DL_PGA_MMUX_INM1                    = 0x03U,
    /*! Inverting gain mode select, feedback resistors have path to local PGA_INM2 pin */
    DL_PGA_MMUX_INM2                    = 0x04U,
    /*! Inverting gain mode select, feedback resistors have path to local PGA_INM3 pin */
    DL_PGA_MMUX_INM3                    = 0x05U,
    /*! Inverting gain mode select, feedback resistors have path to global PGA_INMx pin */
    DL_PGA_MMUX_INM4                    = 0x06U,
    /*! Inverting gain mode select, feedback resistors have path to global PGA_INMx pin */
    DL_PGA_MMUX_INM5                    = 0x07U
} DL_PGA_MMUX_INPUT;

/*! @brief PGA Chopping Mode Selection */
typedef enum
{
    /*! Chopping is disabled */
    DL_PGA_CHOP_DISABLED             = 0x00U,
    /*! ADC assisted chop using ADC Start of Conversion (SOC) */
    DL_PGA_CHOP_ADC_ASSISTED_ADCSOC  = 0x02U,
    /*! ADC assisted chop using External PGA Chop Control Signal */
    DL_PGA_CHOP_ADC_ASSISTED_EXTCTRL = 0x03U
} DL_PGA_CHOP;

/**
 * @brief Filter configuration structure
 */
typedef struct
{
    /*! Select filter resistor value */
    DL_PGA_LOW_PASS_RESISTOR_VALUE resistorValue;
} DL_PGA_FilterConfig;

/**
 * @brief Chopper configuration structure
 */
typedef struct
{
    /*! Enable CHOP signal */
    bool        enableExternalChop;
    /*! Select Output chopping */
    DL_PGA_CHOP chopMode;
} DL_PGA_ChopperConfig;

/**
 * @brief Main configuration structure for the PGA.
 */
typedef struct
{
    /*! Enable PGA */
    bool                 enable;
    /*! PGA gain */
    DL_PGA_GAIN_VALUE    gainValue;
    /*! Enable PGA output to come to a pin */
    bool                 enableOutput;
    /*! Enable PGA internal gain path to come to a pin */
    bool                 enableInternalGainOutput;
    /*! PGA Positive Input Mux Select */
    DL_PGA_PMUX_INPUT    pmuxInput;
    /*! PGA Negative Input Mux Select */
    DL_PGA_NMUX_INPUT    nmuxInput;
    /*! PGA M Mux Select */
    DL_PGA_MMUX_INPUT    mmuxInput;
    /*! Enable Feedback to Negative Input Connection */
    bool                 enableFeedbackOnPin;
    /*! PGA Filter Configuration */
    DL_PGA_FilterConfig  filterConfig;
    /*! PGA Chopper Configuration */
    DL_PGA_ChopperConfig chopperConfig;
    /*! Enable/disable write to PGA registers. @ref DL_PGA_REG_LOCK */
    uint16_t             lockRegistersMask;
} DL_PGA_Config;

/**
 * @brief Enables the Programmable Gain Amplifier (PGA)
 *
 * @param[in] pga   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_enable(PGA_Regs *pga)
{
    pga->PGACTL |= PGA_PGACTL_PGAEN_MASK;
}

/**
 * @brief Disables the Programmable Gain Amplifier (PGA)
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_disable(PGA_Regs *pga)
{
    pga->PGACTL &= ~(PGA_PGACTL_PGAEN_MASK);
}

/**
 * @brief Sets the Programmable Gain Amplifier (PGA) gain value
 *
 * This API sets the gain value for the PGA.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 * @param[in] gainValue      The gain value to be set, from the @ref DL_PGA_GAIN_VALUE
 */
__STATIC_INLINE void DL_PGA_setGain(PGA_Regs *pga, DL_PGA_GAIN_VALUE gainValue)
{
    pga->PGACTL = ((pga->PGACTL & ~(PGA_PGACTL_GAIN_MASK)) | (uint16_t)gainValue);
}

/**
 * @brief Sets the PGA output filter resistor value
 *
 * This API configures the resistor value for the PGA output low pass RC filter.
 * The resistance for the RC low pass filter is provided within the microprocessor
 * and is determined by the resistorValue. The capacitor must be connected outside
 * the microprocessor.
 *
 * @note Setting \b DL_PGA_LOW_PASS_FILTER_DISABLED will disable the internal resistance
 *
 * @param[in] pga            Pointer to the register overlay for the PGA peripheral
 * @param[in] resistorValue  The resistor value to set, from the @ref DL_PGA_LOW_PASS_RESISTOR_VALUE
 */
__STATIC_INLINE void DL_PGA_setFilterResistor(PGA_Regs *pga, DL_PGA_LOW_PASS_RESISTOR_VALUE resistorValue)
{
    pga->PGACTL = ((pga->PGACTL & ~(PGA_PGACTL_FILT_RES_SEL_MASK)) | (uint16_t)resistorValue);
}

/**
 * @brief Enables the PGA output on the pin
 *
 * This API send the PGA output to the pin.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_enableOutput(PGA_Regs *pga)
{
    pga->PGACTL |= PGA_PGACTL_PGA_OUTENABLE_MASK;
}

/**
 * @brief Disables the PGA output on the pin
 *
 * This API prevents the PGA output to the pin.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_disableOutput(PGA_Regs *pga)
{
    pga->PGACTL &= ~(PGA_PGACTL_PGA_OUTENABLE_MASK);
}

/**
 * @brief Enables PGA internal gain output on the pin
 *
 * This API sends the PGA internal gain output to the pin.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_enableInternalGainOutput(PGA_Regs *pga)
{
    pga->PGACTL |= PGA_PGACTL_PGA_OUTEN_INTGAIN_MASK;
}

/**
 * @brief Disables PGA internal gain output on the pin
 *
 * This API prevents the PGA internal gain output from being sent to the pin.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_disableInternalGainOutput(PGA_Regs *pga)
{
    pga->PGACTL &= ~(PGA_PGACTL_PGA_OUTEN_INTGAIN_MASK);
}

/**
 * @brief Enables the external chopping signal for the PGA
 *
 * This API enables the external chopping signal control for PGA.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_enableExternalChop(PGA_Regs *pga)
{
    pga->PGACTL |= PGA_PGACTL_CHOP_EXTCTRL_MASK;
}

/**
 * @brief Disables the external chopping signal for the PGA
 *
 * This API disables the external chopping signal control for PGA.
 *
 * @param[in] pga            Pointer to the register overlay for the PGA peripheral
 */
__STATIC_INLINE void DL_PGA_disableExternalChop(PGA_Regs *pga)
{
    pga->PGACTL &= ~(PGA_PGACTL_CHOP_EXTCTRL_MASK);
}

/**
 * @brief Selects PGA positive input mux source
 *
 * This API selects the positive input mux source.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 * @param[in] pmuxInput      The positive input mux source, @ref DL_PGA_PMUX_INPUT
 */
__STATIC_INLINE void DL_PGA_selectPMUXInput(PGA_Regs *pga, DL_PGA_PMUX_INPUT pmuxInput)
{
    pga->MUXSEL = (pga->MUXSEL & ~(PGA_MUXSEL_PMUXSEL_MASK)) | ((uint16_t)pmuxInput << PGA_MUXSEL_PMUXSEL_OFS);
}

/**
 * @brief Selects PGA negative input multiplexer (NMUX) source
 *
 * This API selects the negative input mux source.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 * @param[in] nmuxInput      The negative input mux source, @ref DL_PGA_NMUX_INPUT
 */
__STATIC_INLINE void DL_PGA_selectNMUXInput(PGA_Regs *pga, DL_PGA_NMUX_INPUT nmuxInput)
{
    pga->MUXSEL = (pga->MUXSEL & ~(PGA_MUXSEL_NMUXSEL_MASK)) | ((uint16_t)nmuxInput << PGA_MUXSEL_NMUXSEL_OFS);
}

/**
 * @brief Selects the input source for the M-Mux
 *
 * This function configures the M-Mux input source. Valid values are as following:
 *
 * - \b DL_PGA_MMUX_NAKED_OPAMP - Stand alone op-amp or G=1 mode select
 * - \b DL_PGA_MMUX_NON_INVERTING_GAIN_VSSA - VSSA_RESARRAY connected
 *   to M-Mux input for non-inverting gain settings
 * - \b DL_PGA_MMUX_INVERTING_GAIN_NEG - PGA_NEG pin connected as
 *   M-Mux input source for inverting gain settings
 * - \b DL_PGA_MMUX_INVERTING_GAIN_NEG_SHARED - PGA_NEG_SHARED connected
 *   as M-Mux input source for inverting gain settings
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 * @param[in] mmuxInput      The M-Mux input mux source, @ref DL_PGA_MMUX_INPUT
 */
__STATIC_INLINE void DL_PGA_selectMMUXInput(PGA_Regs *pga, DL_PGA_MMUX_INPUT mmuxInput)
{
    pga->MUXSEL = (pga->MUXSEL & ~(PGA_MUXSEL_MMUXSEL_MASK)) | ((uint16_t)mmuxInput << PGA_MUXSEL_MMUXSEL_OFS);
}

/**
 * @brief Enable feedback to PGA negative input pin
 *
 * This API enables feedback to the PGA negative input pin and connects
 * PGA_INM to the PGA inverting input.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_enableFeedbackOnPin(PGA_Regs *pga)
{
    pga->MUXSEL |= PGA_MUXSEL_PGA_FBONPIN_MASK;
}

/**
 * @brief Disable feedback to PGA negative input pin
 *
 * This API disables feedback to the PGA negative input pin and connects
 * PGA_INM to the PGA inverting input.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_PGA_disableFeedbackOnPin(PGA_Regs *pga)
{
    pga->MUXSEL &= ~PGA_MUXSEL_PGA_FBONPIN_MASK;
}

/**
 * @brief Selects PGA chop mode
 *
 * This API selects the chopping mode to reduce the input offset to
 * a very small number (~uV level).
 *
 * @param[in] pga            Pointer to the register overlay for the PGA peripheral
 * @param[in] chop           The chop mode to be selected, @ref DL_PGA_CHOP
 */
__STATIC_INLINE void DL_PGA_chop(PGA_Regs *pga, DL_PGA_CHOP chop)
{
    pga->MUXSEL = (pga->MUXSEL & ~(PGA_MUXSEL_PGA_CHOP_MASK)) | ((uint16_t)chop << PGA_MUXSEL_PGA_CHOP_OFS);
}

/**
 * @brief Returns the PGA revision number
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 *
 * @return PGA revision number (8-bit value)
 */
__STATIC_INLINE uint16_t DL_PGA_getRevision(PGA_Regs *pga)
{
    return ((uint16_t)(pga->PGATYPE & PGA_PGATYPE_REV_MASK));
}

/**
 * @brief Returns the PGA type number
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 *
 * @return PGA type number (8-bit value)
 */
__STATIC_INLINE uint16_t DL_PGA_getType(PGA_Regs *pga)
{
    return ((uint16_t)((pga->PGATYPE & PGA_PGATYPE_TYPE_MASK) >> PGA_PGATYPE_TYPE_OFS));
}

/**
 * @brief Locks PGA registers
 *
 * This API locks the PGA registers specified by registerType.
 *
 * @param[in] pga            Pointer to the register overlay for the peripheral
 * @param[in] registerType   The PGA register(s) to be locked, @ref DL_PGA_REG_LOCK
 */
__STATIC_INLINE void DL_PGA_lockRegisters(PGA_Regs *pga, uint16_t registerType)
{
    pga->PGALOCK |= registerType;
}

/**
 * @brief Initializes the PGA configuration parameters.
 *
 * This function initializes all the parameters of the PGA configuration
 * structure to their default values.
 *
 * @param[in,out] config Pointer to the PGA configuration structure.
 */

void DL_PGA_initParamsSetDefault(DL_PGA_Config *config);

/**
 * @brief Initializes the PGA module
 *
 * This function configures the PGA module according to the provided configuration.
 *
 * @param pga Pointer to the PGA register overlay
 * @param config Pointer to the PGA configuration structure
 */
void DL_PGA_init(PGA_Regs *pga, DL_PGA_Config *config);

#ifdef __cplusplus
}
#endif

#endif /* DL_PGA_H */
       /** @}*/
