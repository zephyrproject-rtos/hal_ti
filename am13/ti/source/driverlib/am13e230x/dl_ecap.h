
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
 * @defgroup DL_ECAP_AM13E230X  Driverlib ECAP API
 * @ingroup DL_AM13E230X
 *
 *@{
 */

#ifndef DL_ECAP_H
#define DL_ECAP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "soc.h"
#include "dl_common.h"
#include "hw_ecap.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 * @name DL_ECAP_MAX_PRESCALER_VALUE
 * @anchor DL_ECAP_MAX_PRESCALER_VALUE
 * @{
 */
/*!
 * @brief eCAP minimum and maximum values
 */
#define DL_ECAP_MAX_PRESCALER_VALUE 32U
/** @}*/

/**
 * @name DL_ECAP_ISR_SOURCE
 * @anchor DL_ECAP_ISR_SOURCE
 * @{
 */
/*!
 * @brief Capture Event 1 ISR source
 */
#define DL_ECAP_ISR_SOURCE_CEVT1   0x2U
/*!
 * @brief Capture Event 2 ISR source
 */
#define DL_ECAP_ISR_SOURCE_CEVT2   0x4U
/*!
 * @brief Capture Event 3 ISR source
 */
#define DL_ECAP_ISR_SOURCE_CEVT3   0x8U
/*!
 * @brief Capture Event 4 ISR source
 */
#define DL_ECAP_ISR_SOURCE_CEVT4   0x10U
/*!
 * @brief Counter Overflow ISR source
 */
#define DL_ECAP_ISR_SOURCE_CTROVF  0x20U
/*!
 * @brief Counter Equal Period ISR source
 */
#define DL_ECAP_ISR_SOURCE_CTR_PRD 0x40U
/*!
 * @brief Counter Equal Compare ISR source
 */
#define DL_ECAP_ISR_SOURCE_CTR_CMP 0x80U
/** @}*/

/*! @brief ECAP emulation modes */
typedef enum
{
    /*! TSCTR is stopped on emulation suspension */
    DL_ECAP_EMULATION_STOP        = 0x0U,
    /*! TSCTR runs until 0 before stopping on emulation suspension */
    DL_ECAP_EMULATION_RUN_TO_ZERO = 0x1U,
    /*! TSCTR is not affected by emulation suspension */
    DL_ECAP_EMULATION_FREE_RUN    = 0x2U
} DL_ECAP_EMULATION_MODE;

/*! @brief ECAP capture modes */
typedef enum
{
    /*! eCAP operates in continuous capture mode */
    DL_ECAP_CONTINUOUS_CAPTURE_MODE = 0U,
    /*! eCAP operates in one shot capture mode */
    DL_ECAP_ONE_SHOT_CAPTURE_MODE   = 1U
} DL_ECAP_CAPTURE_MODE;

/*! @brief ECAP event numbers */
typedef enum
{
    /*! eCAP event 1 */
    DL_ECAP_EVENT_1 = 0U,
    /*! eCAP event 2 */
    DL_ECAP_EVENT_2 = 1U,
    /*! eCAP event 3 */
    DL_ECAP_EVENT_3 = 2U,
    /*! eCAP event 4 */
    DL_ECAP_EVENT_4 = 3U
} DL_ECAP_EVENT;

/*! @brief ECAP sync out mode */
typedef enum
{
    /*! Sync out on the sync in signal and software force */
    DL_ECAP_SYNC_OUT_SYNCI       = 0U,
    /*! Sync out on counter equals period */
    DL_ECAP_SYNC_OUT_COUNTER_PRD = 1U,
    /*! Disable sync out signal */
    DL_ECAP_SYNC_OUT_DISABLED    = 2U
} DL_ECAP_SYNC_OUT_MODE;

/*! @brief ECAP APWM polarity */
typedef enum
{
    /*! APWM is active high */
    DL_ECAP_APWM_ACTIVE_HIGH = 0U,
    /*! APWM is active low */
    DL_ECAP_APWM_ACTIVE_LOW  = 1U
} DL_ECAP_APWM_POLARITY;

/*! @brief ECAP event polarity */
typedef enum
{
    /*! Rising edge polarity */
    DL_ECAP_EVENT_RISING_EDGE  = 0U,
    /*! Falling edge polarity */
    DL_ECAP_EVENT_FALLING_EDGE = 1U
} DL_ECAP_EVENT_POLARITY;

/*! @brief ECAP input capture signal sources */
typedef enum
{
    /*! Input signal from INPUTXBAR1 */
    DL_ECAP_INPUT_INPUTXBAR1              = 0U,
    /*! Input signal from INPUTXBAR2 */
    DL_ECAP_INPUT_INPUTXBAR2              = 1U,
    /*! Input signal from INPUTXBAR3 */
    DL_ECAP_INPUT_INPUTXBAR3              = 2U,
    /*! Input signal from INPUTXBAR4 */
    DL_ECAP_INPUT_INPUTXBAR4              = 3U,
    /*! Input signal from INPUTXBAR5 */
    DL_ECAP_INPUT_INPUTXBAR5              = 4U,
    /*! Input signal from INPUTXBAR6 */
    DL_ECAP_INPUT_INPUTXBAR6              = 5U,
    /*! Input signal from INPUTXBAR7 */
    DL_ECAP_INPUT_INPUTXBAR7              = 6U,
    /*! Input signal from INPUTXBAR8 */
    DL_ECAP_INPUT_INPUTXBAR8              = 7U,
    /*! Input signal from INPUTXBAR9 */
    DL_ECAP_INPUT_INPUTXBAR9              = 8U,
    /*! Input signal from INPUTXBAR10 */
    DL_ECAP_INPUT_INPUTXBAR10             = 9U,
    /*! Input signal from INPUTXBAR11 */
    DL_ECAP_INPUT_INPUTXBAR11             = 10U,
    /*! Input signal from INPUTXBAR12 */
    DL_ECAP_INPUT_INPUTXBAR12             = 11U,
    /*! Input signal from INPUTXBAR13 */
    DL_ECAP_INPUT_INPUTXBAR13             = 12U,
    /*! Input signal from INPUTXBAR14 */
    DL_ECAP_INPUT_INPUTXBAR14             = 13U,
    /*! Input signal from INPUTXBAR15 */
    DL_ECAP_INPUT_INPUTXBAR15             = 14U,
    /*! Input signal from INPUTXBAR16 */
    DL_ECAP_INPUT_INPUTXBAR16             = 15U,
    /*! Input signal from MCAN_INT0 */
    DL_ECAP_INPUT_MCAN_INT0               = 16U,
    /*! Input signal from OUTPUTXBAR1 */
    DL_ECAP_INPUT_OUTPUTXBAR1             = 17U,
    /*! Input signal from OUTPUTXBAR2 */
    DL_ECAP_INPUT_OUTPUTXBAR2             = 18U,
    /*! Input signal from OUTPUTXBAR3 */
    DL_ECAP_INPUT_OUTPUTXBAR3             = 19U,
    /*! Input signal from OUTPUTXBAR4 */
    DL_ECAP_INPUT_OUTPUTXBAR4             = 20U,
    /*! Input signal from OUTPUTXBAR5 */
    DL_ECAP_INPUT_OUTPUTXBAR5             = 21U,
    /*! Input signal from OUTPUTXBAR6 */
    DL_ECAP_INPUT_OUTPUTXBAR6             = 22U,
    /*! Input signal from OUTPUTXBAR7 */
    DL_ECAP_INPUT_OUTPUTXBAR7             = 23U,
    /*! Input signal from OUTPUTXBAR8 */
    DL_ECAP_INPUT_OUTPUTXBAR8             = 24U,
    /*! Input signal from ADC0_EVT1 */
    DL_ECAP_INPUT_ADC0_EVT1               = 29U,
    /*! Input signal from ADC0_EVT2 */
    DL_ECAP_INPUT_ADC0_EVT2               = 30U,
    /*! Input signal from ADC0_EVT3 */
    DL_ECAP_INPUT_ADC0_EVT3               = 31U,
    /*! Input signal from ADC0_EVT4 */
    DL_ECAP_INPUT_ADC0_EVT4               = 32U,
    /*! Input signal from ADC1_EVT1 */
    DL_ECAP_INPUT_ADC1_EVT1               = 33U,
    /*! Input signal from ADC1_EVT2 */
    DL_ECAP_INPUT_ADC1_EVT2               = 34U,
    /*! Input signal from ADC1_EVT3 */
    DL_ECAP_INPUT_ADC1_EVT3               = 35U,
    /*! Input signal from ADC1_EVT4 */
    DL_ECAP_INPUT_ADC1_EVT4               = 36U,
    /*! Input signal from ADC2_EVT1 */
    DL_ECAP_INPUT_ADC2_EVT1               = 37U,
    /*! Input signal from ADC2_EVT2 */
    DL_ECAP_INPUT_ADC2_EVT2               = 38U,
    /*! Input signal from ADC2_EVT3 */
    DL_ECAP_INPUT_ADC2_EVT3               = 39U,
    /*! Input signal from ADC2_EVT4 */
    DL_ECAP_INPUT_ADC2_EVT4               = 40U,
    /*! Input signal from CMPSS0_CTRIPL */
    DL_ECAP_INPUT_CMPSS0_CTRIPL           = 41U,
    /*! Input signal from CMPSS1_CTRIPL */
    DL_ECAP_INPUT_CMPSS1_CTRIPL           = 42U,
    /*! Input signal from CMPSS2_CTRIPL */
    DL_ECAP_INPUT_CMPSS2_CTRIPL           = 43U,
    /*! Input signal from CMPSS3_CTRIPL */
    DL_ECAP_INPUT_CMPSS3_CTRIPL           = 44U,
    /*! Input signal from CMPSS0_CTRIPH */
    DL_ECAP_INPUT_CMPSS0_CTRIPH           = 45U,
    /*! Input signal from CMPSS1_CTRIPH */
    DL_ECAP_INPUT_CMPSS1_CTRIPH           = 46U,
    /*! Input signal from CMPSS2_CTRIPH */
    DL_ECAP_INPUT_CMPSS2_CTRIPH           = 47U,
    /*! Input signal from CMPSS3_CTRIPH */
    DL_ECAP_INPUT_CMPSS3_CTRIPH           = 48U,
    /*! Input signal from CMPSS0_CTRIPH_OR_CTRIPL */
    DL_ECAP_INPUT_CMPSS0_CTRIPH_OR_CTRIPL = 49U,
    /*! Input signal from CMPSS1_CTRIPH_OR_CTRIPL */
    DL_ECAP_INPUT_CMPSS1_CTRIPH_OR_CTRIPL = 50U,
    /*! Input signal from CMPSS2_CTRIPH_OR_CTRIPL */
    DL_ECAP_INPUT_CMPSS2_CTRIPH_OR_CTRIPL = 51U,
    /*! Input signal from CMPSS3_CTRIPH_OR_CTRIPL */
    DL_ECAP_INPUT_CMPSS3_CTRIPH_OR_CTRIPL = 52U,
    /*! Input signal from INPUTXBARX */
    DL_ECAP_INPUT_INPUTXBARX              = 53U,
} DL_ECAP_INPUT;

/*! @brief ECAP sync-in pulse sources */
typedef enum
{
    /*! Disable Sync-in */
    DL_ECAP_SYNC_IN_PULSE_SRC_DISABLE       = 0x0,
    /*! Sync-in source is Input Xbar 5 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_INPUTXBAR5    = 0x1,
    /*! Sync-in source is Input Xbar 6 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_INPUTXBAR6    = 0x2,
    /*! Sync-in source is ECAP0 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_ECAP0_SYNCOUT = 0x3,
    /*! Sync-in source is ECAP1 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_ECAP1_SYNCOUT = 0x4,
    /*! Sync-in source is PWM0 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_PWM0_SYNCOUT  = 0x5,
    /*! Sync-in source is PWM1 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_PWM1_SYNCOUT  = 0x6,
    /*! Sync-in source is PWM2 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_PWM2_SYNCOUT  = 0x7,
    /*! Sync-in source is PWM3 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_PWM3_SYNCOUT  = 0x8,
    /*! Sync-in source is PWM4 sync-out signal */
    DL_ECAP_SYNC_IN_PULSE_SRC_PWM4_SYNCOUT  = 0x9
} DL_ECAP_SYNC_IN_PULSE_SRC;

/*! @brief ECAP operating modes */
typedef enum
{
    /*! Capture mode */
    DL_ECAP_OPERATING_MODE_CAPTURE = 0x0U,
    /*! APWM mode */
    DL_ECAP_OPERATING_MODE_APWM    = 0x1U,

} DL_ECAP_OPERATING_MODE;

/**
 * @brief ECAP APWM mode configuration structure
 */
typedef struct
{
    /*! APWM compare value */
    uint32_t              compareCount;
    /*! APWM period value */
    uint32_t              periodCount;
    /*! APWM output polarity select */
    DL_ECAP_APWM_POLARITY polarity;
} DL_ECAP_ApwmModeConfig;

/**
 * @brief ECAP capture mode configuration structure
 */
typedef struct
{
    /*! Capture input source select */
    DL_ECAP_INPUT          input;
    /*! Event Filter prescale */
    uint16_t               prescalerValue;
    /*! One shot or continuous mode control */
    DL_ECAP_CAPTURE_MODE   continouousOrOneShot;
    /*! Stop value for oneshot mode, wrap value for continuous mode */
    DL_ECAP_EVENT          wrapOrStopAtEvent;
    /*! Counter reset on capture event 1 */
    bool                   enableCounterResetOnCaptureEvent1;
    /*! Counter reset on capture event 2*/
    bool                   enableCounterResetOnCaptureEvent2;
    /*! Counter reset on capture event 3 */
    bool                   enableCounterResetOnCaptureEvent3;
    /*! Counter reset on capture event 4 */
    bool                   enableCounterResetOnCaptureEvent4;
    /*! Polarity select on capture event 1*/
    DL_ECAP_EVENT_POLARITY captureEvent1Polarity;
    /*! Polarity select on capture event 2 */
    DL_ECAP_EVENT_POLARITY captureEvent2Polarity;
    /*! Polarity select on capture event 3 */
    DL_ECAP_EVENT_POLARITY captureEvent3Polarity;
    /*! Polarity select on capture event 4 */
    DL_ECAP_EVENT_POLARITY captureEvent4Polarity;
    /*! Reset event filter, counter, modulo counter and CEVT[1,2,3,4] and CNTOVF , HRERROR flags */
    bool                   resetCounter;
    /*! Reset  Mod4 counter to zero, Unfreeze the Mod4 counter, Enable capture register loads */
    bool                   reArm;
} DL_ECAP_CaptureModeConfig;

/**
 * @brief ECAP sync configuration structure
 */
typedef struct
{
    /*! Sync input select */
    DL_ECAP_SYNC_IN_PULSE_SRC ecapSyncInSel;
    /*! Counter phase value to be loaded into timestamp counter for phase lag/lead - upon either a SYNCI event or S/W
     * force */
    uint32_t                  phaseShiftCount;
    /*! Sync output select */
    DL_ECAP_SYNC_OUT_MODE     syncOutSelect;
    /*! Disable or Enable counter to be loaded from CTRPHS upon SYNCI signal or SW force event */
    bool                      enableLoadCounter;
} DL_ECAP_SyncConfig;

/**
 * @brief ECAP interrupt configuration structure
 */
typedef struct
{
    /*! Interrupt enable mask. @ref DL_ECAP_ISR_SOURCE*/
    uint16_t      interruptSourceEnableMask;
    /*! DMA event select */
    DL_ECAP_EVENT dmaEventSelect;
} DL_ECAP_InterruptsConfig;

/**
 * @brief ECAP configuration structure
 */
typedef struct
{
    /*! Capture or APWM operating mode select */
    DL_ECAP_OPERATING_MODE    modeSelect;
    /*! Capture mode configuration.
        Relevant if ECAP is operated in capture mode. modeSelect is DL_ECAP_OPERATING_MODE_CAPTURE.
        No need to fill this structure in APWM mode.
    */
    DL_ECAP_CaptureModeConfig captureModeConfig;
    /*! APWM mode configuration
        Relevant if ECAP is operated in APWM mode. modeSelect is DL_ECAP_OPERATING_MODE_APWM.
        No need to fill this structure in Capture mode.
    */
    DL_ECAP_ApwmModeConfig    apwmModeConfig;
    /*! Sync configuration */
    DL_ECAP_SyncConfig        syncConfig;
    /*! Interrupt configuration */
    DL_ECAP_InterruptsConfig  interruptsConfig;
    /*! Emulation control */
    DL_ECAP_EMULATION_MODE    emulationMode;
} DL_ECAP_Config;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************

/**
 * @brief Sets the input prescaler
 *
 * This API divides the ECAP input scaler. The input capture signal (pulse
 * train) can be prescaled in multiples of 2 or can bypass the prescaler.
 *
 * Valid range of \e prescalerValue
 *  0 = Divide by 1 (i.e,. no prescale, by-pass the prescaler)
 *  1 = Divide by 2
 *  2 = Divide by 4
 *  3 = Divide by 6
 *  4 = Divide by 8
 *  5 = Divide by 10
 *  ...
 *  0x1E (30) = Divide by 60
 *  0x1F (31) = Divide by 62
 * Must be less than DL_ECAP_MAX_PRESCALER_VALUE
 *
 * @param[in] ecap           Pointer to the register overlay for the peripheral
 * @param[in] prescalerValue is the prescaler value for ECAP input
 */
__STATIC_INLINE void DL_ECAP_setEventPrescaler(ECAP_Regs *ecap, uint16_t prescalerValue)
{
    ASSERT(prescalerValue < DL_ECAP_MAX_PRESCALER_VALUE);

    ecap->ECCTL1 = (ecap->ECCTL1 & ~ECAP_ECCTL1_PRESCALE_MASK) | (prescalerValue << ECAP_ECCTL1_PRESCALE_OFS);
}

/**
 * @brief Sets the Capture Event polarity
 *
 * For each event the Capture event polarity value determines the edge on which
 * the capture is activated.
 *
 * @param[in] ecap           Pointer to the register overlay for the peripheral
 * @param[in] event          The event number to be used
 * @param[in] polarity       is polarity of the event
 */
__STATIC_INLINE void DL_ECAP_setEventPolarity(ECAP_Regs *ecap, DL_ECAP_EVENT event, DL_ECAP_EVENT_POLARITY polarity)
{
    uint16_t shift = ((uint16_t)event) << 1U;

    /* Write to CAP1POL, CAP2POL, CAP3POL or CAP4POL */
    ecap->ECCTL1 = (ecap->ECCTL1 & ~(1U << shift)) | ((uint16_t)polarity << shift);
}

/**
 * @brief Sets the capture mode
 *
 * This API sets the eCAP module to a continuous or one-shot mode. The value of event
 * determines the event number at which the counter stops (in one-shot mode) or
 * the counter wraps (in continuous mode).
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] mode      is the capture mode
 * @param[in] event     is the event number at which the counter stops or wraps
 */
__STATIC_INLINE void DL_ECAP_setCaptureMode(ECAP_Regs *ecap, DL_ECAP_CAPTURE_MODE mode, DL_ECAP_EVENT event)
{
    /* Write to CONT/ONESHT */
    ecap->ECCTL2 = (ecap->ECCTL2 & ~ECAP_ECCTL2_CONT_ONESHT_MASK) | (uint16_t)mode;

    /* Write to STOP_WRAP */
    ecap->ECCTL2 = (ecap->ECCTL2 & ~ECAP_ECCTL2_STOP_WRAP_MASK) | (((uint16_t)event) << ECAP_ECCTL2_STOP_WRAP_OFS);
}

/**
 * @brief Re-arms the eCAP module
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_reArm(ECAP_Regs *ecap)
{
    ecap->ECCTL2 |= ECAP_ECCTL2_REARM_MASK;
}

/**
 * @brief Enables interrupt source
 *
 * This API sets and enables eCAP interrupt source. The following are
 * valid interrupt sources.
 *  - DL_ECAP_ISR_SOURCE_CEVT1 - Event 1 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT2 - Event 2 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT3 - Event 3 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT4 - Event 4 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTROVF - Counter overflow generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_PRD - Counter equal period generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_CMP - Counter equal compare generates interrupt
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] intFlags  Bit mask of the interrupt sources to be enabled
 *                      @ref DL_ECAP_ISR_SOURCE
 */
__STATIC_INLINE void DL_ECAP_enableInterrupt(ECAP_Regs *ecap, uint16_t intFlags)
{
    ASSERT((intFlags & ~(DL_ECAP_ISR_SOURCE_CEVT1 | DL_ECAP_ISR_SOURCE_CEVT2 | DL_ECAP_ISR_SOURCE_CEVT3 |
                         DL_ECAP_ISR_SOURCE_CEVT4 | DL_ECAP_ISR_SOURCE_CTROVF | DL_ECAP_ISR_SOURCE_CTR_PRD |
                         DL_ECAP_ISR_SOURCE_CTR_CMP)) == 0U);

    ecap->ECEINT |= intFlags;
}

/**
 * @brief Disables interrupt source
 *
 * This API disables eCAP interrupt source. The following are
 * valid interrupt sources.
 *  - DL_ECAP_ISR_SOURCE_CEVT1 - Event 1 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT2 - Event 2 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT3 - Event 3 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT4 - Event 4 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTROVF - Counter overflow generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_PRD - Counter equal period generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_CMP - Counter equal compare generates interrupt
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] intFlags  Bit mask of the interrupt sources to be disabled
 *                      @ref DL_ECAP_ISR_SOURCE
 */
__STATIC_INLINE void DL_ECAP_disableInterrupt(ECAP_Regs *ecap, uint16_t intFlags)
{
    ASSERT((intFlags & ~(DL_ECAP_ISR_SOURCE_CEVT1 | DL_ECAP_ISR_SOURCE_CEVT2 | DL_ECAP_ISR_SOURCE_CEVT3 |
                         DL_ECAP_ISR_SOURCE_CEVT4 | DL_ECAP_ISR_SOURCE_CTROVF | DL_ECAP_ISR_SOURCE_CTR_PRD |
                         DL_ECAP_ISR_SOURCE_CTR_CMP)) == 0U);

    ecap->ECEINT &= ~intFlags;
}

/**
 * @brief Returns the interrupt flag
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 *
 * @return Returns the eCAP interrupt that has occurred. The following are
 *  valid return values:
 *  - DL_ECAP_ISR_SOURCE_CEVT1   - Event 1 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT2   - Event 2 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT3   - Event 3 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT4   - Event 4 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTROVF  - Counter overflow generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_PRD - Counter equal period generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_CMP - Counter equal compare generates interrupt
 *
 * @note - User can check if a combination of various interrupts have occurred
 *         by ORing the above return values.
 */
__STATIC_INLINE uint16_t DL_ECAP_getInterruptSource(ECAP_Regs *ecap)
{
    return (ecap->ECFLG & 0xFEU);
}

/**
 * @brief Returns the global interrupt flag status
 *
 * @param ecap          Pointer to the register overlay for the peripheral
 *
 * @return true if there is a global eCAP interrupt occured
 * @return false if there is no global eCAP interrupt occured
 */
__STATIC_INLINE bool DL_ECAP_getGlobalInterruptStatus(ECAP_Regs *ecap)
{
    return ((ecap->ECFLG & ECAP_ECFLG_INT_MASK) == ECAP_ECFLG_INT_MASK);
}

/**
 * @brief Clears interrupt flags
 *
 * This API clears eCAP interrupt flags. The following are
 * valid interrupt sources.
 *  - DL_ECAP_ISR_SOURCE_CEVT1   - Event 1 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT2   - Event 2 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT3   - Event 3 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT4   - Event 4 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTROVF  - Counter overflow generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_PRD - Counter equal period generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_CMP - Counter equal compare generates interrupt
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] intFlags  Bit mask of the interrupt sources to be cleared
 *                      @ref DL_ECAP_ISR_SOURCE
 */
__STATIC_INLINE void DL_ECAP_clearInterrupt(ECAP_Regs *ecap, uint16_t intFlags)
{
    ASSERT((intFlags & ~(DL_ECAP_ISR_SOURCE_CEVT1 | DL_ECAP_ISR_SOURCE_CEVT2 | DL_ECAP_ISR_SOURCE_CEVT3 |
                         DL_ECAP_ISR_SOURCE_CEVT4 | DL_ECAP_ISR_SOURCE_CTROVF | DL_ECAP_ISR_SOURCE_CTR_PRD |
                         DL_ECAP_ISR_SOURCE_CTR_CMP)) == 0U);

    ecap->ECCLR = intFlags;
}

/**
 * @brief Clears global interrupt flag
 *
 * This API clears the global interrupt bit, allowing further
 * interrupts to be generated if any of the event flags are set.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_clearGlobalInterrupt(ECAP_Regs *ecap)
{
    ecap->ECCLR = ECAP_ECCLR_INT_MASK;
}

/**
 * @brief Forces interrupt flags
 *
 * This API forces eCAP interrupt flags. The following are
 * valid interrupt sources.
 *  - DL_ECAP_ISR_SOURCE_CEVT1   - Event 1 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT2   - Event 2 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT3   - Event 3 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CEVT4   - Event 4 generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTROVF  - Counter overflow generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_PRD - Counter equal period generates interrupt
 *  - DL_ECAP_ISR_SOURCE_CTR_CMP - Counter equal compare generates interrupt
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] intFlags  Bit mask of the interrupt sources to be forced
 *                      @ref DL_ECAP_ISR_SOURCE
 */
__STATIC_INLINE void DL_ECAP_forceInterrupt(ECAP_Regs *ecap, uint16_t intFlags)
{
    ASSERT((intFlags & ~(DL_ECAP_ISR_SOURCE_CEVT1 | DL_ECAP_ISR_SOURCE_CEVT2 | DL_ECAP_ISR_SOURCE_CEVT3 |
                         DL_ECAP_ISR_SOURCE_CEVT4 | DL_ECAP_ISR_SOURCE_CTROVF | DL_ECAP_ISR_SOURCE_CTR_PRD |
                         DL_ECAP_ISR_SOURCE_CTR_CMP)) == 0U);

    ecap->ECFRC = intFlags;
}

/**
 * @brief Enables capture mode
 *
 * This API sets the eCAP module to operate in Capture mode.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_enableCaptureMode(ECAP_Regs *ecap)
{
    ecap->ECCTL2 &= ~(ECAP_ECCTL2_CAP_APWM_MASK);
}

/**
 * @brief Enables APWM mode
 *
 * This API sets the eCAP module to operate in APWM mode.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_enableAPWMMode(ECAP_Regs *ecap)
{
    ecap->ECCTL2 |= ECAP_ECCTL2_CAP_APWM_MASK;
}

/**
 * @brief Enables counter reset on an event
 *
 * This API enables the base timer (TSCTR) to be reset when the specified
 * capture event occurs.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] event     The event number on which the counter should reset
 */
__STATIC_INLINE void DL_ECAP_enableCounterResetOnEvent(ECAP_Regs *ecap, DL_ECAP_EVENT event)
{
    /* Set CTRRSTx bit corresponding to the event */
    ecap->ECCTL1 |= 1U << ((2U * (uint16_t)event) + 1U);
}

/**
 * @brief Disables counter reset on an event
 *
 * This API disables the base timer (TSCTR) reset on the specified capture event.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] event     The event number for which counter reset should be disabled
 */
__STATIC_INLINE void DL_ECAP_disableCounterResetOnEvent(ECAP_Regs *ecap, DL_ECAP_EVENT event)
{
    /* Clear CTRRSTx bit corresponding to the event */
    ecap->ECCTL1 &= ~(1U << ((2U * (uint16_t)event) + 1U));
}

/**
 * @brief Enables time stamp count capture
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_enableTimeStampCapture(ECAP_Regs *ecap)
{
    ecap->ECCTL1 |= ECAP_ECCTL1_CAPLDEN_MASK;
}

/**
 * @brief Disables time stamp count capture
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_disableTimeStampCapture(ECAP_Regs *ecap)
{
    ecap->ECCTL1 &= ~(ECAP_ECCTL1_CAPLDEN_MASK);
}

/**
 * @brief Sets the counter phase shift value
 *
 * This function configures the counter phase shift value to be loaded into
 * the main timestamp counter when a sync-in event occurs.
 *
 * @param[in] ecap        Pointer to the register overlay for the peripheral
 * @param[in] shiftCount  The phase shift value to be loaded
 */
__STATIC_INLINE void DL_ECAP_setPhaseShiftCount(ECAP_Regs *ecap, uint32_t shiftCount)
{
    ecap->CTRPHS = shiftCount;
}

/**
 * @brief Sets the source for sync-in pulse
 *
 * This API configures the source for the sync-in pulse to the eCAP module.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] source    The source for the sync-in pulse
 */
__STATIC_INLINE void DL_ECAP_setSyncInPulseSource(ECAP_Regs *ecap, DL_ECAP_SYNC_IN_PULSE_SRC source)
{
    ecap->ECAPSYNCINSEL =
        (ecap->ECAPSYNCINSEL & ~ECAP_ECAPSYNCINSEL_SEL_MASK) | ((uint32_t)source & ECAP_ECAPSYNCINSEL_SEL_MASK);
}

/**
 * @brief Enables counter loading with phase shift value
 *
 * This API enables loading of the counter with the value present in the
 * phase shift counter as defined by the DL_ECAP_setPhaseShiftCount() API.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_enableLoadCounter(ECAP_Regs *ecap)
{
    ecap->ECCTL2 |= ECAP_ECCTL2_SYNCI_EN_MASK;
}

/**
 * @brief Disables counter loading with phase shift value
 *
 * This function disables loading of the counter with the phase shift value
 * as defined by the DL_ECAP_setPhaseShiftCount() API.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_disableLoadCounter(ECAP_Regs *ecap)
{
    ecap->ECCTL2 &= ~ECAP_ECCTL2_SYNCI_EN_MASK;
}

/**
 * @brief Loads timestamp counter
 *
 * This API forces the value in the phase shift counter register to be
 * loaded into the timestamp counter register. Make sure to enable loading of
 * timestamp counter by calling DL_ECAP_enableLoadCounter() API before
 * calling this API.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_loadCounter(ECAP_Regs *ecap)
{
    ecap->ECCTL2 |= ECAP_ECCTL2_SWSYNC_MASK;
}

/**
 * @brief Configures Sync out signal mode
 *
 * This function sets the sync-out mode for the eCAP module. Valid values for mode are:
 * - DL_ECAP_SYNC_OUT_SYNCI - Trigger sync out on sync-in event and software force.
 * - DL_ECAP_SYNC_OUT_COUNTER_PRD - Trigger sync out when counter equals period.
 * - DL_ECAP_SYNC_OUT_DISABLED - Disable sync out.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] mode      isthe sync-out mode to set
 */
__STATIC_INLINE void DL_ECAP_setSyncOutMode(ECAP_Regs *ecap, DL_ECAP_SYNC_OUT_MODE mode)
{
    ecap->ECCTL2 = (ecap->ECCTL2 & ~ECAP_ECCTL2_SYNCO_SEL_MASK) | ((uint16_t)mode << ECAP_ECCTL2_SYNCO_SEL_OFS);
}

/**
 * @brief Stops the timestamp counter
 *
 * This API stops the ECAP timestamp counter (TSCTR) from running.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_stopCounter(ECAP_Regs *ecap)
{
    ecap->ECCTL2 &= ~ECAP_ECCTL2_TSCTRSTOP_MASK;
}

/**
 * @brief Starts the timestamp counter
 *
 * This API starts the ECAP timestamp counter (TSCTR) running.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_startCounter(ECAP_Regs *ecap)
{
    ecap->ECCTL2 |= ECAP_ECCTL2_TSCTRSTOP_MASK;
}

/**
 * @brief Sets eCAP APWM polarity
 *
 * This API sets the polarity of the eCAP in APWM mode.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] polarity  is the polarity to set (active high or active low)
 */
__STATIC_INLINE void DL_ECAP_setAPWMPolarity(ECAP_Regs *ecap, DL_ECAP_APWM_POLARITY polarity)
{
    ecap->ECCTL2 = (ecap->ECCTL2 & ~ECAP_ECCTL2_APWMPOL_MASK) | ((uint16_t)polarity << ECAP_ECCTL2_APWMPOL_OFS);
}

/**
 * @brief Sets eCAP APWM period
 *
 * This function sets the period count of the APWM waveform.
 * periodCount takes the actual count which is written to the register. The
 * user is responsible for converting the desired frequency or time into
 * the period count.
 *
 * @param[in] ecap         Pointer to the register overlay for the peripheral
 * @param[in] periodCount  is the period count to set for APWM
 */
__STATIC_INLINE void DL_ECAP_setAPWMPeriod(ECAP_Regs *ecap, uint32_t periodCount)
{
    ecap->CAP1 = periodCount;
}

/**
 * @brief Sets eCAP APWM on or off time count
 *
 * This function sets the on or off time count of the APWM waveform depending
 * on the polarity of the output. If the output , as set by
 * DL_ECAP_setAPWMPolarity(), is active high then compareCount determines the on
 * time. If the output is active low then compareCount determines the off
 * time. compareCount takes the actual count which is written to the register.
 * The user is responsible for converting the desired frequency or time into
 * the appropriate count value.
 *
 * @param[in] ecap          Pointer to the register overlay for the peripheral
 * @param[in] compareCount  is the compare count for APWM
 */
__STATIC_INLINE void DL_ECAP_setAPWMCompare(ECAP_Regs *ecap, uint32_t compareCount)
{
    ecap->CAP2 = compareCount;
}

/**
 * @brief Sets eCAP APWM shadow period
 *
 * This API sets the shadow period count of the APWM waveform.
 * periodCount takes the actual count which is written to the register. The
 * user is responsible for converting the desired frequency or time into
 * the period count.
 *
 * @param[in] ecap         Pointer to the register overlay for the peripheral
 * @param[in] periodCount  is the shadow period count to set for APWM
 */
__STATIC_INLINE void DL_ECAP_setAPWMShadowPeriod(ECAP_Regs *ecap, uint32_t periodCount)
{
    ecap->CAP3 = periodCount;
}

/**
 * @brief Sets eCAP APWM shadow on or off time count
 *
 * This function sets the shadow on or off time count of the APWM waveform
 * depending on the polarity of the output. If the output, as set by
 * DL_ECAP_setAPWMPolarity(), is active high then compareCount determines the
 * on time. If the output is active low then compareCount determines the off
 * time. compareCount takes the actual count which is written to the register.
 * The user is responsible for converting the desired frequency or time into
 * the appropriate count value.
 *
 * @param[in] ecap          Pointer to the register overlay for the peripheral
 * @param[in] compareCount  is the shadow on or off time count for APWM
 */
__STATIC_INLINE void DL_ECAP_setAPWMShadowCompare(ECAP_Regs *ecap, uint32_t compareCount)
{
    ecap->CAP4 = compareCount;
}

/**
 * @brief Returns the time-stamp counter value
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 *
 * @return The current timestamp counter value
 */
__STATIC_INLINE uint32_t DL_ECAP_getTimeStampCounter(ECAP_Regs *ecap)
{
    return ecap->TSCTR;
}

/**
 * @brief Returns event time stamp
 *
 * This function returns the current time stamp count of the given event.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] event     is the event number
 *
 * @return Event time stamp value
 */
__STATIC_INLINE uint32_t DL_ECAP_getEventTimeStamp(ECAP_Regs *ecap, DL_ECAP_EVENT event)
{
    uint32_t timeStamp;

    switch (event)
    {
        case DL_ECAP_EVENT_1:
            /* Read CAP1 register */
            timeStamp = ecap->CAP1;
            break;

        case DL_ECAP_EVENT_2:
            /* Read CAP2 register */
            timeStamp = ecap->CAP2;
            break;

        case DL_ECAP_EVENT_3:
            /* Read CAP3 register */
            timeStamp = ecap->CAP3;
            break;

        case DL_ECAP_EVENT_4:
            /* Read CAP4 register */
            timeStamp = ecap->CAP4;
            break;

        default:
            /* Invalid event parameter */
            timeStamp = 0U;
            break;
    }

    return timeStamp;
}

/**
 * @brief Select eCAP input
 *
 * This function selects the eCAP input signal.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] input     is the eCAP input signal source to select
 */
__STATIC_INLINE void DL_ECAP_selectECAPInput(ECAP_Regs *ecap, DL_ECAP_INPUT input)
{
    ecap->ECCTL0 = (ecap->ECCTL0 & ~ECAP_ECCTL0_INPUTSEL_MASK) | ((uint32_t)input);
}

/**
 * @brief Resets eCAP counters and flags
 *
 * This function resets the main counter (TSCTR), event filter,
 * modulo counter, and interrupt flags.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ECAP_resetCounters(ECAP_Regs *ecap)
{
    ecap->ECCTL2 |= ECAP_ECCTL2_CTRFILTRESET_MASK;
}

/**
 * @brief Sets the eCAP DMA source event
 *
 * This function sets the eCAP event source for the DMA trigger.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] event     is the event number to be used as DMA source
 */
__STATIC_INLINE void DL_ECAP_setDMASource(ECAP_Regs *ecap, DL_ECAP_EVENT event)
{
    ecap->ECCTL2 = (ecap->ECCTL2 & ~ECAP_ECCTL2_DMAEVTSEL_MASK) | ((uint16_t)event << ECAP_ECCTL2_DMAEVTSEL_OFS);
}

/**
 * @brief Returns the modulo counter status
 *
 * This API returns the modulo counter status, indicating which register
 * gets loaded on the next capture event.
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 *
 * @return DL_ECAP_EVENT value indicating which CAPn register will be loaded on the next event
 */
__STATIC_INLINE DL_ECAP_EVENT DL_ECAP_getModuloCounterStatus(ECAP_Regs *ecap)
{
    return (DL_ECAP_EVENT)(((ecap->ECCTL2 & ECAP_ECCTL2_MODCNTRSTS_MASK) >> ECAP_ECCTL2_MODCNTRSTS_OFS));
}

/**
 * @brief Configures the emulation mode
 *
 * This function configures the eCAP counter (TSCTR)  to the desired emulation
 * mode when emulation suspension occurs. Valid values for modes are:
 * - DL_ECAP_EMULATION_STOP - Counter stops immediately on emulation suspension
 * - DL_ECAP_EMULATION_RUN_TO_ZERO - Counter runs until 0 on emulation suspension
 * - DL_ECAP_EMULATION_FREE_RUN - Counter is unaffected by emulation suspension
 *
 * @param[in] ecap      Pointer to the register overlay for the peripheral
 * @param[in] mode      is the emulation mode to set
 */
__STATIC_INLINE void DL_ECAP_setEmulationMode(ECAP_Regs *ecap, DL_ECAP_EMULATION_MODE mode)
{
    ecap->ECCTL1 = (ecap->ECCTL1 & ~ECAP_ECCTL1_FREE_SOFT_MASK) | ((uint16_t)mode << ECAP_ECCTL1_FREE_SOFT_OFS);
}

/**
 * @brief Initializes the ECAP configuration parameters.
 *
 * This function initializes all the parameters of the ECAP configuration
 * structure to their default values.
 *
 * @param[in,out] config Pointer to the ECAP configuration structure.
 */

void DL_ECAP_initParamsSetDefault(DL_ECAP_Config *config);

/**
 * @brief Initializes the ECAP module
 *
 * This function configures the ECAP module according to the provided configuration.
 *
 * @param ecap Pointer to the ECAP register overlay
 * @param config Pointer to the ECAP configuration structure
 */
void DL_ECAP_init(ECAP_Regs *ecap, DL_ECAP_Config *config);

#ifdef __cplusplus
}
#endif

#endif /* DL_ECAP_H */
       /** @}*/
