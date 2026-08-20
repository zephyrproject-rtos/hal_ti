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
 * @defgroup DL_XBAR_AM13E230X  Driverlib XBAR API
 * @ingroup DL_AM13E230X
 *
 *  The CrossBar (XBAR) Driver Library allows full configuration of
 *  the XBAR module.
 *
 * @{
 */

#ifndef DL_XBAR_H
#define DL_XBAR_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <soc.h>
#include <dl_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/*! @brief Key for the lock register */
#define DL_XBAR_LOCK_KEY 0x5A5A0000U

/**
 * @name DL_XBAR_INPUT
 * @anchor DL_XBAR_INPUT
 * @{
 */
/*! @brief '1' will be driven to the destination */
#define DL_XBAR_DRIVE_HIGH 0xFEU
/*! @brief '0' will be driven to the destination */
#define DL_XBAR_DRIVE_LOW  0xFFU
/** @}*/

/*! @brief DL_XBAR_InputNum */
typedef enum
{
    DL_XBAR_INPUT1,  //!< XBAR_INPUT1 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT2,  //!< XBAR_INPUT2 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT3,  //!< XBAR_INPUT3 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT4,  //!< XBAR_INPUT4 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT5,  //!< XBAR_INPUT5 - Connected to ECAP, PWMXBAR, OUTPUTXBAR, EXTSYNCIN1
    DL_XBAR_INPUT6,  //!< XBAR_INPUT6 - Connected to ECAP, PWMXBAR, OUTPUTXBAR, EXTSYNCIN2
    DL_XBAR_INPUT7,  //!< XBAR_INPUT7 - Connected to ECAP, PWMXBAR, OUTPUTXBAR, CMPSS0_EXT_FILTIN_H, CMPSS2_EXT_FILTIN_H
    DL_XBAR_INPUT8,  //!< XBAR_INPUT8 - Connected to ECAP, PWMXBAR, OUTPUTXBAR, CMPSS0_EXT_FILTIN_L, CMPSS2_EXT_FILTIN_L
    DL_XBAR_INPUT9,  //!< XBAR_INPUT9 - Connected to ECAP, PWMXBAR, OUTPUTXBAR, CMPSS1_EXT_FILTIN_H, CMPSS2_EXT_FILTIN_H
    DL_XBAR_INPUT10,  //!< XBAR_INPUT10 - Connected to ECAP, PWMXBAR, OUTPUTXBAR, CMPSS1_EXT_FILTIN_L,
                      //!< CMPSS2_EXT_FILTIN_L
    DL_XBAR_INPUT11,  //!< XBAR_INPUT11 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT12,  //!< XBAR_INPUT12 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT13,  //!< XBAR_INPUT13 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT14,  //!< XBAR_INPUT14 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT15,  //!< XBAR_INPUT15 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT16,  //!< XBAR_INPUT16 - Connected to ECAP, PWMXBAR, OUTPUTXBAR
    DL_XBAR_INPUT17,  //!< XBAR_INPUT17 - Connected to EQEP0A
    DL_XBAR_INPUT18,  //!< XBAR_INPUT18 - Connected to EQEP0B
    DL_XBAR_INPUT19,  //!< XBAR_INPUT19 - Connected to EQEP0I
    DL_XBAR_INPUT20,  //!< XBAR_INPUT20 - Connected to EQEP0S
    DL_XBAR_INPUT21,  //!< XBAR_INPUT21 - Connected to EQEP1A
    DL_XBAR_INPUT22,  //!< XBAR_INPUT22 - Connected to EQEP1B
    DL_XBAR_INPUT23,  //!< XBAR_INPUT23 - Connected to EQEP1I
    DL_XBAR_INPUT24,  //!< XBAR_INPUT24 - Connected to EQEP1S
    DL_XBAR_INPUT25,  //!< XBAR_INPUT25 - Connected to EQEP2A
    DL_XBAR_INPUT26,  //!< XBAR_INPUT26 - Connected to EQEP2B
    DL_XBAR_INPUT27,  //!< XBAR_INPUT27 - Connected to EQEP2I
    DL_XBAR_INPUT28,  //!< XBAR_INPUT28 - Connected to EQEP2S
} DL_XBAR_InputNum;

/*! @brief DL_XBAR_OutputNum */
typedef enum
{
    DL_XBAR_OUTPUT1,
    DL_XBAR_OUTPUT2,
    DL_XBAR_OUTPUT3,
    DL_XBAR_OUTPUT4,
    DL_XBAR_OUTPUT5,
    DL_XBAR_OUTPUT6,
    DL_XBAR_OUTPUT7,
    DL_XBAR_OUTPUT8,
    DL_XBAR_OUTPUT9,
    DL_XBAR_OUTPUT10,
    DL_XBAR_OUTPUT11,
    DL_XBAR_OUTPUT12,
} DL_XBAR_OutputNum;

/*! @brief DL_XBAR_OutputXBARSource */
typedef enum
{
    DL_XBAR_OUT_CMPSS0_CTRIPOUTH     = 0x000U,
    DL_XBAR_OUT_CMPSS0_CTRIPOUTL     = 0x001U,
    DL_XBAR_OUT_CMPSS1_CTRIPOUTH     = 0x002U,
    DL_XBAR_OUT_CMPSS1_CTRIPOUTL     = 0x003U,
    DL_XBAR_OUT_CMPSS2_CTRIPOUTH     = 0x004U,
    DL_XBAR_OUT_CMPSS2_CTRIPOUTL     = 0x005U,
    DL_XBAR_OUT_CMPSS3_CTRIPOUTH     = 0x006U,
    DL_XBAR_OUT_CMPSS3_CTRIPOUTL     = 0x007U,
    DL_XBAR_OUT_ADC0_EVT1            = 0x008U,
    DL_XBAR_OUT_ADC0_EVT2            = 0x009U,
    DL_XBAR_OUT_ADC0_EVT3            = 0x00AU,
    DL_XBAR_OUT_ADC0_EVT4            = 0x00BU,
    DL_XBAR_OUT_ADC1_EVT1            = 0x00CU,
    DL_XBAR_OUT_ADC1_EVT2            = 0x00DU,
    DL_XBAR_OUT_ADC1_EVT3            = 0x00EU,
    DL_XBAR_OUT_ADC1_EVT4            = 0x00FU,
    DL_XBAR_OUT_ADC2_EVT1            = 0x010U,
    DL_XBAR_OUT_ADC2_EVT2            = 0x011U,
    DL_XBAR_OUT_ADC2_EVT3            = 0x012U,
    DL_XBAR_OUT_ADC2_EVT4            = 0x013U,
    DL_XBAR_OUT_INPUTXBAR1           = 0x014U,
    DL_XBAR_OUT_INPUTXBAR2           = 0x015U,
    DL_XBAR_OUT_INPUTXBAR3           = 0x016U,
    DL_XBAR_OUT_INPUTXBAR4           = 0x017U,
    DL_XBAR_OUT_INPUTXBAR5           = 0x018U,
    DL_XBAR_OUT_INPUTXBAR6           = 0x019U,
    DL_XBAR_OUT_INPUTXBAR7           = 0x01AU,
    DL_XBAR_OUT_INPUTXBAR8           = 0x01BU,
    DL_XBAR_OUT_INPUTXBAR9           = 0x01CU,
    DL_XBAR_OUT_INPUTXBAR10          = 0x01DU,
    DL_XBAR_OUT_INPUTXBAR11          = 0x01EU,
    DL_XBAR_OUT_INPUTXBAR12          = 0x01FU,
    DL_XBAR_OUT_INPUTXBAR13          = 0x100U,
    DL_XBAR_OUT_INPUTXBAR14          = 0x101U,
    DL_XBAR_OUT_INPUTXBAR15          = 0x102U,
    DL_XBAR_OUT_INPUTXBAR16          = 0x103U,
    DL_XBAR_OUT_ECAP0_OUT            = 0x104U,
    DL_XBAR_OUT_ECAP1_OUT            = 0x105U,
    DL_XBAR_OUT_ADCSOCA              = 0x106U,
    DL_XBAR_OUT_ADCSOCB              = 0x107U,
    DL_XBAR_OUT_EXTSYNCOUT           = 0x108U,
    DL_XBAR_OUT_MCAN_INT0            = 0x109U,
    DL_XBAR_OUT_EQEP0_ERR            = 0x10CU,
    DL_XBAR_OUT_EQEP1_ERR            = 0x10DU,
    DL_XBAR_OUT_EQEP2_ERR            = 0x10EU,
    DL_XBAR_OUT_EQEP0_INDEX_SYNCOUT  = 0x10FU,
    DL_XBAR_OUT_EQEP0_STROBE_SYNCOUT = 0x110U,
    DL_XBAR_OUT_EQEP1_INDEX_SYNCOUT  = 0x111U,
    DL_XBAR_OUT_EQEP1_STROBE_SYNCOUT = 0x112U,
    DL_XBAR_OUT_EQEP2_INDEX_SYNCOUT  = 0x113U,
    DL_XBAR_OUT_EQEP2_STROBE_SYNCOUT = 0x114U,
    DL_XBAR_OUT_XCLKOUT              = 0x115U,
} DL_XBAR_OutputXBARSource;

/*! @brief DLXBAR_TripNum */
typedef enum
{
    DL_XBAR_TRIP1,
    DL_XBAR_TRIP2,
    DL_XBAR_TRIP3,
    DL_XBAR_TRIP4,
    DL_XBAR_TRIP5,
    DL_XBAR_TRIP6,
    DL_XBAR_TRIP7,
    DL_XBAR_TRIP8,
} DL_XBAR_TripNum;

/*! @brief DL_XBAR_PWMXBARSource */
typedef enum
{
    DL_XBAR_PWM_CMPSS0_CTRIPH = 0x000U,
    DL_XBAR_PWM_CMPSS0_CTRIPL = 0x001U,
    DL_XBAR_PWM_CMPSS1_CTRIPH = 0x002U,
    DL_XBAR_PWM_CMPSS1_CTRIPL = 0x003U,
    DL_XBAR_PWM_CMPSS2_CTRIPH = 0x004U,
    DL_XBAR_PWM_CMPSS2_CTRIPL = 0x005U,
    DL_XBAR_PWM_CMPSS3_CTRIPH = 0x006U,
    DL_XBAR_PWM_CMPSS3_CTRIPL = 0x007U,
    DL_XBAR_PWM_ADC0_EVT1     = 0x008U,
    DL_XBAR_PWM_ADC0_EVT2     = 0x009U,
    DL_XBAR_PWM_ADC0_EVT3     = 0x00AU,
    DL_XBAR_PWM_ADC0_EVT4     = 0x00BU,
    DL_XBAR_PWM_ADC1_EVT1     = 0x00CU,
    DL_XBAR_PWM_ADC1_EVT2     = 0x00DU,
    DL_XBAR_PWM_ADC1_EVT3     = 0x00EU,
    DL_XBAR_PWM_ADC1_EVT4     = 0x00FU,
    DL_XBAR_PWM_ADC2_EVT1     = 0x010U,
    DL_XBAR_PWM_ADC2_EVT2     = 0x011U,
    DL_XBAR_PWM_ADC2_EVT3     = 0x012U,
    DL_XBAR_PWM_ADC2_EVT4     = 0x013U,
    DL_XBAR_PWM_INPUTXBAR1    = 0x014U,
    DL_XBAR_PWM_INPUTXBAR2    = 0x015U,
    DL_XBAR_PWM_INPUTXBAR3    = 0x016U,
    DL_XBAR_PWM_INPUTXBAR4    = 0x017U,
    DL_XBAR_PWM_INPUTXBAR5    = 0x018U,
    DL_XBAR_PWM_INPUTXBAR6    = 0x019U,
    DL_XBAR_PWM_INPUTXBAR7    = 0x01AU,
    DL_XBAR_PWM_INPUTXBAR8    = 0x01BU,
    DL_XBAR_PWM_INPUTXBAR9    = 0x01CU,
    DL_XBAR_PWM_INPUTXBAR10   = 0x01DU,
    DL_XBAR_PWM_INPUTXBAR11   = 0x01EU,
    DL_XBAR_PWM_INPUTXBAR12   = 0x01FU,
    DL_XBAR_PWM_INPUTXBAR13   = 0x100U,
    DL_XBAR_PWM_INPUTXBAR14   = 0x101U,
    DL_XBAR_PWM_INPUTXBAR15   = 0x102U,
    DL_XBAR_PWM_INPUTXBAR16   = 0x103U,
    DL_XBAR_PWM_ECAP0_OUT     = 0x104U,
    DL_XBAR_PWM_ECAP1_OUT     = 0x105U,
    DL_XBAR_PWM_ADCSOCA       = 0x106U,
    DL_XBAR_PWM_ADCSOCB       = 0x107U,
    DL_XBAR_PWM_EXTSYNCOUT    = 0x108U,
    DL_XBAR_PWM_MCAN_INT0     = 0x109U,
    DL_XBAR_PWM_EQEP0_ERR     = 0x10CU,
    DL_XBAR_PWM_EQEP1_ERR     = 0x10DU,
    DL_XBAR_PWM_EQEP2_ERR     = 0x10EU,
    DL_XBAR_PWM_CPU_HALTED    = 0x10FU,
} DL_XBAR_PWMXBARSource;

/** @brief DL_XBAR_SyncOutSource */
typedef enum
{
    DL_XBAR_SYNCOUT_PWM0  = 0x0,
    DL_XBAR_SYNCOUT_PWM1  = 0x1,
    DL_XBAR_SYNCOUT_PWM2  = 0x2,
    DL_XBAR_SYNCOUT_PWM3  = 0x3,
    DL_XBAR_SYNCOUT_PWM4  = 0x4,
    DL_XBAR_SYNCOUT_ECAP0 = 0x18,
    DL_XBAR_SYNCOUT_ECAP1 = 0x19,
} DL_XBAR_SyncOutSource;

/**
 * @name DL_XBAR_ADCSOCOUT
 * @anchor DL_XBAR_ADCSOCOUT
 * @{
 */
/*! @brief Enable PWM0SOCA/B for ADCSOCA/B */
#define DL_XBAR_ADCSOCOUT_PWM0 XBAR_ADCSOCOUTSELECT_PWM0SOCAEN_MASK
/*! @brief Enable PWM1SOCA/B for ADCSOCA/B */
#define DL_XBAR_ADCSOCOUT_PWM1 XBAR_ADCSOCOUTSELECT_PWM1SOCAEN_MASK
/*! @brief Enable PWM2SOCA/B for ADCSOCA/B */
#define DL_XBAR_ADCSOCOUT_PWM2 XBAR_ADCSOCOUTSELECT_PWM2SOCAEN_MASK
/*! @brief Enable PWM3SOCA/B for ADCSOCA/B */
#define DL_XBAR_ADCSOCOUT_PWM3 XBAR_ADCSOCOUTSELECT_PWM3SOCAEN_MASK
/*! @brief Enable PWM4SOCA/B for ADCSOCA/B */
#define DL_XBAR_ADCSOCOUT_PWM4 XBAR_ADCSOCOUTSELECT_PWM4SOCAEN_MASK
/** @}*/

/* =========================================================================== */
/*                             XBAR Functions                                  */
/* =========================================================================== */

/*!
 *  @brief      Sets the GPIO or a non-GPIO input to an Input XBAR.
 *
 *  This function configures which GPIO / non-GPIO input is assigned to an
 *  Input X-BAR input.
 *
 *  The pin is specified by its numerical value. For example, GPIO34 (PB2) is
 *  specified by passing 34 as \e pin. Other non GPIO values :
 * 		- \b DL_XBAR_DRIVE_HIGH - '1' will be driven to the destination
 * 		- \b DL_XBAR_DRIVE_LOW  - '0' will be driven to the destination
 *
 *  @param[in]  input  XBAR input to be configured
 *  @param[in]  pin    Pin number / DL_XBAR_DRIVE_HIGH / DL_XBAR_DRIVE_LOW
 *
 *  \note 	Pin value greater than the available number of GPIO pins on a
 *  device (except 0xFF) will cause the destination to be driven '1'.
 *
 */
__STATIC_INLINE void DL_XBAR_setInputXBAR(DL_XBAR_InputNum input, uint8_t pin)
{
    INPUTXBAR->INPUTSELECT[(uint32_t)input] = pin;
}

/*!
 *  @brief      Enable Raw input signal from selected pad
 *  @param[in]  pin 	Pin to be configured
 *
 * 	@note 		This selection is common to all the INPUTXBARx output channels
 *	@sa 		DL_XBAR_disableRawInput
 */
__STATIC_INLINE void DL_XBAR_enableRawInput(uint8_t pin)
{
    uint32_t group     = pin / 32U;
    uint32_t inputMask = 1U << (pin % 32U);

    HWREG(&(INPUTXBAR->RAW_INPUTSELECT_PA) + group) |= inputMask;
}

/*!
 *  @brief      Disable Raw input signal from selected pad
 *  @param[in]  pin 	Pin to be configured
 *
 * 	@note 		This selection is common to all the INPUTXBARx output channels
 *	@sa 		DL_XBAR_enableRawInput
 */
__STATIC_INLINE void DL_XBAR_disableRawInput(uint8_t pin)
{
    uint32_t group     = pin / 32U;
    uint32_t inputMask = 1U << (pin % 32U);

    HWREG(&(INPUTXBAR->RAW_INPUTSELECT_PA) + group) &= ~inputMask;
}

/*!
 *  @brief      Locks the Input XBAR
 *  @param[in]  input  XBAR input to be configured
 */
__STATIC_INLINE void DL_XBAR_lockInputXBAR(DL_XBAR_InputNum input)
{
    INPUTXBAR->INPUTSELECTLOCK1 |= 1U << (uint32_t)input;
}

/*!
 *  @brief      Selects the input to the Output XBAR
 *
 *  This function selects an input to affect the Output X-BAR output. To
 *  select multiple inputs, the function can be called multiple times with the
 *  respective inputs. The X-BAR output would be an OR of the selected inputs.
 *
 *  @param[in]  output  XBAR output to be configured
 *  @param[in]  source  Input source to the X-BAR output.
 *
 *  @sa 		DL_XBAR_deselectOutputXBARSource
 */
__STATIC_INLINE void DL_XBAR_selectOutputXBARSource(DL_XBAR_OutputNum output, DL_XBAR_OutputXBARSource source)
{
    uint32_t group     = (uint32_t)source >> 8U;
    uint32_t inputMask = 1U << ((uint32_t)source & 0xFFU);

    HWREG(&(OUTPUTXBAR->OUTPUTXBAR_GXSEL[(uint32_t)output].OUTPUTXBARG0SEL) + group) |= inputMask;
}

/*!
 *  @brief      Deselects the input to the Output XBAR
 *
 *  This function deselects an input to not affect the Output X-BAR output. To
 *  deselect multiple inputs, the function can be called multiple times with the
 *  respective inputs. The X-BAR output would be an OR of of only the selected
 *  inputs
 *
 *  @param[in]  output  XBAR output to be configured
 *  @param[in]  source  Input source to the X-BAR output.
 *
 *  @sa 		DL_XBAR_selectOutputXBARSource
 */
__STATIC_INLINE void DL_XBAR_deselectOutputXBARSource(DL_XBAR_OutputNum output, DL_XBAR_OutputXBARSource source)
{
    uint32_t group     = (uint32_t)source >> 8U;
    uint32_t inputMask = 1U << ((uint32_t)source & 0xFFU);

    HWREG(&(OUTPUTXBAR->OUTPUTXBAR_GXSEL[(uint32_t)output].OUTPUTXBARG0SEL) + group) &= ~inputMask;
}

/*!
 *  @brief      Clears all the input source selection for the Output XBAR output
 *  @param[in]  output  XBAR output to be configured
 *
 *  @sa 		DL_XBAR_selectOutputXBARSource
 */
__STATIC_INLINE void DL_XBAR_clearOutputXBARSourceSelection(DL_XBAR_OutputNum output)
{
    OUTPUTXBAR->OUTPUTXBAR_GXSEL[(uint32_t)output].OUTPUTXBARG0SEL = 0U;
    OUTPUTXBAR->OUTPUTXBAR_GXSEL[(uint32_t)output].OUTPUTXBARG1SEL = 0U;
}

/*!
 *  @brief		Configure the polarity of the XBAR output before latch
 *  @param[in]  output  XBAR output to be configured
 *  @param[in]  invert  true if the output signal should be inverted, false otherwise
 */
__STATIC_INLINE void DL_XBAR_invertOutputXBARSignalBeforeLatch(DL_XBAR_OutputNum output, bool invert)
{
    if (invert)
    {
        OUTPUTXBAR->OUTPUTXBARFLAGINVERT |= 0x1U << ((uint32_t)output);
    }
    else
    {
        OUTPUTXBAR->OUTPUTXBARFLAGINVERT &= ~(0x1U << ((uint32_t)output));
    }
}

/*!
 *  @brief		Enable or disable the output latch to drive the selected output
 *  @param[in]  output  XBAR output to be configured
 *  @param[in]  enable  true if the output should be latched, false otherwise
 */
__STATIC_INLINE void DL_XBAR_setOutputXBARLatchMode(DL_XBAR_OutputNum output, bool enable)
{
    if (enable)
    {
        OUTPUTXBAR->OUTPUTXBAROUTLATCH |= 0x1U << ((uint32_t)output);
    }
    else
    {
        OUTPUTXBAR->OUTPUTXBAROUTLATCH &= ~(0x1U << ((uint32_t)output));
    }
}

/*!
 *  @brief		Configure the polarity of the Output XBAR signal
 *  @param[in]  output  XBAR output to be configured
 *  @param[in]  invert  true if the output signal should be inverted, false otherwise
 */
__STATIC_INLINE void DL_XBAR_invertOutputXBARSignal(DL_XBAR_OutputNum output, bool invert)
{
    if (invert)
    {
        OUTPUTXBAR->OUTPUTXBAROUTINVERT |= 0x1U << ((uint32_t)output);
    }
    else
    {
        OUTPUTXBAR->OUTPUTXBAROUTINVERT &= ~(0x1U << ((uint32_t)output));
    }
}

/*!
 *  @brief		Locks the Output XBAR
 *  @note		Once the configuration is locked, writes to GXSEL and INVERT registers are blocked
 */
__STATIC_INLINE void DL_XBAR_lockOutputXBAR(void)
{
    OUTPUTXBAR->OUTPUTXBARLOCK = DL_XBAR_LOCK_KEY | XBAR_OUTPUTXBARLOCK_LOCK_MASK;
}

/*!
 *  @brief		Selects the input to the PWM XBAR
 *
 *  This function selects an input to affect the PWM X-BAR output. To
 *  select multiple inputs, the function can be called multiple times with the
 *  respective inputs. The X-BAR output would be an OR of the selected inputs.
 *
 *  @param[in]  trip  	PWM XBAR output (trip) to be configured
 *  @param[in]  source  Input source to the X-BAR output.
 *
 *  @sa 		DL_XBAR_deselectPWMXBARSource
 */
__STATIC_INLINE void DL_XBAR_selectPWMXBARSource(DL_XBAR_TripNum trip, DL_XBAR_PWMXBARSource source)
{
    uint32_t group     = (uint32_t)source >> 8U;
    uint32_t inputMask = 1U << ((uint32_t)source & 0xFFU);

    HWREG(&(PWMXBAR->PWM_XBAR_GXSEL[(uint32_t)trip].PWMXBARG0SEL) + group) |= inputMask;
}

/*!
 *  @brief		Deselects the input to the PWM XBAR
 *
 *  This function deselects an input to not affect the PWM X-BAR output. To
 *  deselect multiple inputs, the function can be called multiple times with the
 *  respective inputs. The X-BAR output would be an OR of of only the selected
 *  inputs
 *
 *  @param[in]  trip  PWM XBAR output (trip) to be configured
 *  @param[in]  source  Input source to the X-BAR output.
 *
 *  @sa 		DL_XBAR_selectPWMXBARSource
 */
__STATIC_INLINE void DL_XBAR_deselectPWMXBARSource(DL_XBAR_TripNum trip, DL_XBAR_PWMXBARSource source)
{
    uint32_t group     = (uint32_t)source >> 8U;
    uint32_t inputMask = 1U << ((uint32_t)source & 0xFFU);

    HWREG(&(PWMXBAR->PWM_XBAR_GXSEL[(uint32_t)trip].PWMXBARG0SEL) + group) &= ~inputMask;
}

/*!
 *  @brief		Clears all the input source selection for the PWM XBAR output
 *  @param[in]  trip  PWM XBAR output (trip) to be configured
 *
 *  @sa 		DL_XBAR_selectPWMXBARSource
 */
__STATIC_INLINE void DL_XBAR_clearPWMXBARSourceSelection(DL_XBAR_TripNum trip)
{
    PWMXBAR->PWM_XBAR_GXSEL[(uint32_t)trip].PWMXBARG0SEL = 0U;
    PWMXBAR->PWM_XBAR_GXSEL[(uint32_t)trip].PWMXBARG1SEL = 0U;
}

/*!
 *  @brief		Configure the polarity of the PWM XBAR signal
 *  @param[in]  trip  PWM XBAR output (trip) to be configured
 *  @param[in]  invert  true if the output signal should be inverted, false otherwise
 */
__STATIC_INLINE void DL_XBAR_invertPWMXBARSignal(DL_XBAR_TripNum trip, bool invert)
{
    if (invert)
    {
        PWMXBAR->PWMXBAROUTINVERT |= 0x1U << ((uint32_t)trip);
    }
    else
    {
        PWMXBAR->PWMXBAROUTINVERT &= ~(0x1U << ((uint32_t)trip));
    }
}

/*!
 *  @brief		Locks the PWM XBAR
 *  @note		Once the configuration is locked, writes to GXSEL and INVERT registers are blocked
 */
__STATIC_INLINE void DL_XBAR_lockPWMXBAR(void)
{
    PWMXBAR->PWMXBARLOCK = DL_XBAR_LOCK_KEY | XBAR_PWMXBARLOCK_LOCK_MASK;
}

/*!
 *  @brief		Set the External SyncOut Source
 *	@param[in]  source  SyncOut Source
 *
 *  @note 		EXTSYNCOUT signal can be connected to OutputXBAR to route it
 *  			an external pin and/or to PWMXBAR to generate a PWM Trip signal
 */
__STATIC_INLINE void DL_XBAR_setExtSyncOutSource(DL_XBAR_SyncOutSource source)
{
    SYNC->SYNCSELECT = (uint32_t)source << XBAR_SYNCSELECT_SYNCOUT_OFS;
}

/*!
 *  @brief		Locks the ExtSyncOut Config
 *  @note		Once the configuration is locked, writes to SYNCSELECT registers are blocked
 */
__STATIC_INLINE void DL_XBAR_lockExtSyncOut(void)
{
    SYNC->SYNCSOCLOCK |= XBAR_SYNCSOCLOCK_SYNCSELECT_MASK;
}

/*!
 *  @brief		Set the External ADCSOCA Source
 *	@param[in]  source  External ADCSOCA Source. Logical OR of \b DL_XBAR_ADCSOCOUT_PWMx
 *
 *  @note 		EXTADCSOCA signal can be connected to OutputXBAR to route it
 *  			an external pin and/or to PWMXBAR to generate a PWM Trip signal
 */
__STATIC_INLINE void DL_XBAR_setExtADCSOCASource(uint32_t source)
{
    SYNC->ADCSOCOUTSELECT = (SYNC->ADCSOCOUTSELECT & 0xFFFF0000U) | source;
}

/*!
 *  @brief		Set the External ADCSOCB Source
 *	@param[in]  source  External ADCSOCB Source. Logical OR of \b DL_XBAR_ADCSOCOUT_PWMx
 *
 *  @note 		EXTADCSOCB signal can be connected to OutputXBAR to route it
 *  			an external pin and/or to PWMXBAR to generate a PWM Trip signal
 */
__STATIC_INLINE void DL_XBAR_setExtADCSOCBSource(uint32_t source)
{
    SYNC->ADCSOCOUTSELECT = (SYNC->ADCSOCOUTSELECT & 0xFFFFU) | (source << 16U);
}

/*!
 *  @brief		Locks the ExtADCSOCx Config
 *  @note		Once the configuration is locked, writes to ADCSOCOUTSELECT registers are blocked
 */
__STATIC_INLINE void DL_XBAR_lockExtADCSOCx(void)
{
    SYNC->SYNCSOCLOCK |= XBAR_SYNCSOCLOCK_ADCSOCOUTSELECT_MASK;
}

#ifdef __cplusplus
}
#endif

#endif /* DL_XBAR_H */
/** @}*/
