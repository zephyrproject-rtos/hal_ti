
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
 * @defgroup DL_ADC_AM13E230X  Driverlib ADC API
 * @ingroup DL_AM13E230X
 *
 *@{
 */

#ifndef DL_ADC_H
#define DL_ADC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "soc.h"
#include "dl_common.h"
#include "hw_adc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! @brief Interrupt pulse position */
typedef enum
{
    /*!
     * @brief End of acquisition window
     *
     * Set Interrupt pulse position for pulse generation to occur when ADC begins conversion + a number of sysclk
     * cycles controlled by DL_ADC_setEarlyInterruptGenerationDelay
     */
    DL_ADC_PULSE_END_OF_ACQ_WIN = 0,

    /*!
     * @brief End of conversion
     *
     * Set Interrupt pulse position for pulse generation to occur at the end of conversion 1 cycle prior to the ADC
     * result latching into its result register
     */
    DL_ADC_PULSE_END_OF_CONV = 1
} DL_ADC_INT_PULSE_POS;

/*! @brief ADC clock divider. ADCCLK = (input clock) / divider */
typedef enum
{
    /*! ADCCLK = (input clock) / 1.0 */
    DL_ADC_CLOCK_DIVIDE_1_0 = 0U,
    /*! ADCCLK = (input clock) / 1.5 */
    DL_ADC_CLOCK_DIVIDE_1_5 = 1U,
    /*! ADCCLK = (input clock) / 2.0 */
    DL_ADC_CLOCK_DIVIDE_2_0 = 2U,
    /*! ADCCLK = (input clock) / 2.5 */
    DL_ADC_CLOCK_DIVIDE_2_5 = 3U,
    /*! ADCCLK = (input clock) / 3.0 */
    DL_ADC_CLOCK_DIVIDE_3_0 = 4U,
    /*! ADCCLK = (input clock) / 3.5 */
    DL_ADC_CLOCK_DIVIDE_3_5 = 5U,
    /*! ADCCLK = (input clock) / 4.0 */
    DL_ADC_CLOCK_DIVIDE_4_0 = 6U,
    /*! ADCCLK = (input clock) / 4.5 */
    DL_ADC_CLOCK_DIVIDE_4_5 = 7U,
    /*! ADCCLK = (input clock) / 5.0 */
    DL_ADC_CLOCK_DIVIDE_5_0 = 8U,
    /*! ADCCLK = (input clock) / 5.5 */
    DL_ADC_CLOCK_DIVIDE_5_5 = 9U,
    /*! ADCCLK = (input clock) / 6.0 */
    DL_ADC_CLOCK_DIVIDE_6_0 = 10U,
    /*! ADCCLK = (input clock) / 6.5 */
    DL_ADC_CLOCK_DIVIDE_6_5 = 11U,
    /*! ADCCLK = (input clock) / 7.0 */
    DL_ADC_CLOCK_DIVIDE_7_0 = 12U,
    /*! ADCCLK = (input clock) / 7.5 */
    DL_ADC_CLOCK_DIVIDE_7_5 = 13U,
    /*! ADCCLK = (input clock) / 8.0 */
    DL_ADC_CLOCK_DIVIDE_8_0 = 14U,
    /*! ADCCLK = (input clock) / 8.5 */
    DL_ADC_CLOCK_DIVIDE_8_5 = 15U
} DL_ADC_CLK_PRESCALE;

/*! @brief SOC/EOC number */
/*! This value identifies the start-of-conversion (SOC) that a function is configuring or accessing. Note that
 * in some cases (for example, ADC_setInterruptSource()) \e socNumber is used to refer to the corresponding
 * end-of-conversion (EOC).
 */
typedef enum
{
    /*! SOC/EOC number 0 */
    DL_ADC_SOC_NUMBER0  = 0U,
    /*! SOC/EOC number 1 */
    DL_ADC_SOC_NUMBER1  = 1U,
    /*! SOC/EOC number 2 */
    DL_ADC_SOC_NUMBER2  = 2U,
    /*! SOC/EOC number 3 */
    DL_ADC_SOC_NUMBER3  = 3U,
    /*! SOC/EOC number 4 */
    DL_ADC_SOC_NUMBER4  = 4U,
    /*! SOC/EOC number 5 */
    DL_ADC_SOC_NUMBER5  = 5U,
    /*! SOC/EOC number 6 */
    DL_ADC_SOC_NUMBER6  = 6U,
    /*! SOC/EOC number 7 */
    DL_ADC_SOC_NUMBER7  = 7U,
    /*! SOC/EOC number 8 */
    DL_ADC_SOC_NUMBER8  = 8U,
    /*! SOC/EOC number 9 */
    DL_ADC_SOC_NUMBER9  = 9U,
    /*! SOC/EOC number 10 */
    DL_ADC_SOC_NUMBER10 = 10U,
    /*! SOC/EOC number 11 */
    DL_ADC_SOC_NUMBER11 = 11U,
    /*! SOC/EOC number 12 */
    DL_ADC_SOC_NUMBER12 = 12U,
    /*! SOC/EOC number 13 */
    DL_ADC_SOC_NUMBER13 = 13U,
    /*! SOC/EOC number 14 */
    DL_ADC_SOC_NUMBER14 = 14U,
    /*! SOC/EOC number 15 */
    DL_ADC_SOC_NUMBER15 = 15U
} DL_ADC_SOC_NUMBER;

/*! @brief ADC Interrupt number */
typedef enum
{
    /*! ADCINT1 Interrupt */
    DL_ADC_INT_NUMBER1 = 0U,
    /*! ADCINT2 Interrupt */
    DL_ADC_INT_NUMBER2 = 1U,
    /*! ADCINT3 Interrupt */
    DL_ADC_INT_NUMBER3 = 2U,
    /*! ADCINT4 Interrupt */
    DL_ADC_INT_NUMBER4 = 3U
} DL_ADC_INT_NUMBER;

/*! @brief ADC DMA Interrupt number */
typedef enum
{
    /*! ADCDMAINT1 Interrupt */
    DL_ADC_DMAINT_NUMBER1 = 0U,
    /*! ADCDMAINT2 Interrupt */
    DL_ADC_DMAINT_NUMBER2 = 1U,
    /*! ADCDMAINT3 Interrupt */
    DL_ADC_DMAINT_NUMBER3 = 2U,
    /*! ADCDMAINT4 Interrupt */
    DL_ADC_DMAINT_NUMBER4 = 3U
} DL_ADC_DMAINT_NUMBER;

/*! @brief ADC Channel */
/*! This is the input pin on which the signal to be converted is located. */
typedef enum
{
    /*! single-ended, ADCIN0 is converted */
    DL_ADC_CH_ADCIN0  = 0U,
    /*! single-ended, ADCIN1 is converted */
    DL_ADC_CH_ADCIN1  = 1U,
    /*! single-ended, ADCIN2 is converted */
    DL_ADC_CH_ADCIN2  = 2U,
    /*! single-ended, ADCIN3 is converted */
    DL_ADC_CH_ADCIN3  = 3U,
    /*! single-ended, ADCIN4 is converted */
    DL_ADC_CH_ADCIN4  = 4U,
    /*! single-ended, ADCIN5 is converted */
    DL_ADC_CH_ADCIN5  = 5U,
    /*! single-ended, ADCIN6 is converted */
    DL_ADC_CH_ADCIN6  = 6U,
    /*! single-ended, ADCIN7 is converted */
    DL_ADC_CH_ADCIN7  = 7U,
    /*! single-ended, ADCIN8 is converted */
    DL_ADC_CH_ADCIN8  = 8U,
    /*! single-ended, ADCIN9 is converted */
    DL_ADC_CH_ADCIN9  = 9U,
    /*! single-ended, ADCIN10 is converted */
    DL_ADC_CH_ADCIN10 = 10U,
    /*! single-ended, ADCIN11 is converted */
    DL_ADC_CH_ADCIN11 = 11U,
    /*! single-ended, ADCIN12 is converted */
    DL_ADC_CH_ADCIN12 = 12U,
    /*! single-ended, ADCIN13 is converted */
    DL_ADC_CH_ADCIN13 = 13U,
    /*! single-ended, ADCIN14 is converted */
    DL_ADC_CH_ADCIN14 = 14U,
    /*! single-ended, ADCIN15 is converted */
    DL_ADC_CH_ADCIN15 = 15U,
    /*! single-ended, ADCIN16 is converted */
    DL_ADC_CH_ADCIN16 = 16U,
    /*! single-ended, ADCIN17 is converted */
    DL_ADC_CH_ADCIN17 = 17U,
    /*! single-ended, ADCIN18 is converted */
    DL_ADC_CH_ADCIN18 = 18U,
    /*! single-ended, ADCIN19 is converted */
    DL_ADC_CH_ADCIN19 = 19U,
    /*! single-ended, ADCIN20 is converted */
    DL_ADC_CH_ADCIN20 = 20U,
    /*! single-ended, ADCIN21 is converted */
    DL_ADC_CH_ADCIN21 = 21U,
    /*! single-ended, ADCIN22 is converted */
    DL_ADC_CH_ADCIN22 = 22U,
    /*! single-ended, ADCIN23 is converted */
    DL_ADC_CH_ADCIN23 = 23U,
    /*! single-ended, ADCIN24 is converted */
    DL_ADC_CH_ADCIN24 = 24U,
    /*! single-ended, ADCIN25 is converted */
    DL_ADC_CH_ADCIN25 = 25U,
    /*! single-ended, ADCIN26 is converted */
    DL_ADC_CH_ADCIN26 = 26U,
    /*! single-ended, ADCIN27 is converted */
    DL_ADC_CH_ADCIN27 = 27U,
    /*! single-ended, ADCIN28 is converted */
    DL_ADC_CH_ADCIN28 = 28U,
    /*! single-ended, ADCIN29 is converted */
    DL_ADC_CH_ADCIN29 = 29U,
    /*! single-ended, ADCIN30 is converted */
    DL_ADC_CH_ADCIN30 = 30U,
    /*! single-ended, ADCIN31 is converted */
    DL_ADC_CH_ADCIN31 = 31U
} DL_ADC_CHANNEL;

/*! @brief SEQ number */
typedef enum
{
    /*! Sequencer number 1 */
    DL_ADC_SEQ_NUMBER1 = 0U,
    /*! Sequencer number 2 */
    DL_ADC_SEQ_NUMBER2 = 1U,
    /*! Sequencer number 3 */
    DL_ADC_SEQ_NUMBER3 = 2U,
    /*! Sequencer number 4 */
    DL_ADC_SEQ_NUMBER4 = 3U
} DL_ADC_SEQ_NUMBER;

/*! @brief PPB number */
typedef enum
{
    /*! Post-processing block 1 */
    DL_ADC_PPB_NUMBER1 = 0U,
    /*! Post-processing block 2 */
    DL_ADC_PPB_NUMBER2 = 1U,
    /*! Post-processing block 3 */
    DL_ADC_PPB_NUMBER3 = 2U,
    /*! Post-processing block 4 */
    DL_ADC_PPB_NUMBER4 = 3U,
} DL_ADC_PPB_NUMBER;

/**
 * @brief Offset trim value
 */
#define DL_ADC_OFFSET_TRIM_VALUE(offset) ((offset) >= 0 ? (offset) * 16 : 256 - (-(offset)) * 16)

/*! @brief ADC Offset trim value */
/*! Offset can be corrected in the range of +7 to -8 LSBs */
typedef enum
{
    /*! Offset trim of -7 LSBs */
    DL_ADC_OFF_TRIM_MIN_7LSB = DL_ADC_OFFSET_TRIM_VALUE(-7),
    /*! Offset trim of -6 LSBs */
    DL_ADC_OFF_TRIM_MIN_6LSB = DL_ADC_OFFSET_TRIM_VALUE(-6),
    /*! Offset trim of -5 LSBs */
    DL_ADC_OFF_TRIM_MIN_5LSB = DL_ADC_OFFSET_TRIM_VALUE(-5),
    /*! Offset trim of -4 LSBs */
    DL_ADC_OFF_TRIM_MIN_4LSB = DL_ADC_OFFSET_TRIM_VALUE(-4),
    /*! Offset trim of -3 LSBs */
    DL_ADC_OFF_TRIM_MIN_3LSB = DL_ADC_OFFSET_TRIM_VALUE(-3),
    /*! Offset trim of -2 LSBs */
    DL_ADC_OFF_TRIM_MIN_2LSB = DL_ADC_OFFSET_TRIM_VALUE(-2),
    /*! Offset trim of -1 LSBs */
    DL_ADC_OFF_TRIM_MIN_1LSB = DL_ADC_OFFSET_TRIM_VALUE(-1),
    /*! Offset trim of 0 LSBs */
    DL_ADC_OFF_TRIM_0LSB     = DL_ADC_OFFSET_TRIM_VALUE(0),
    /*! Offset trim of 1 LSBs */
    DL_ADC_OFF_TRIM_1LSB     = DL_ADC_OFFSET_TRIM_VALUE(1),
    /*! Offset trim of 2 LSBs */
    DL_ADC_OFF_TRIM_2LSB     = DL_ADC_OFFSET_TRIM_VALUE(2),
    /*! Offset trim of 3 LSBs */
    DL_ADC_OFF_TRIM_3LSB     = DL_ADC_OFFSET_TRIM_VALUE(3),
    /*! Offset trim of 4 LSBs */
    DL_ADC_OFF_TRIM_4LSB     = DL_ADC_OFFSET_TRIM_VALUE(4),
    /*! Offset trim of 5 LSBs */
    DL_ADC_OFF_TRIM_5LSB     = DL_ADC_OFFSET_TRIM_VALUE(5),
    /*! Offset trim of 6 LSBs */
    DL_ADC_OFF_TRIM_6LSB     = DL_ADC_OFFSET_TRIM_VALUE(6),
    /*! Offset trim of 7 LSBs */
    DL_ADC_OFF_TRIM_7LSB     = DL_ADC_OFFSET_TRIM_VALUE(7)
} DL_ADC_OFFSET_TRIM;

/*! @brief PPB Oversampling limit */
typedef enum
{
    /*! No conversion is accumulated */
    DL_ADC_PPB_LIMIT_NIL = 0U,
    /*! 2 conversions are accumulated */
    DL_ADC_PPB_LIMIT_2   = 1U,
    /*! 4 conversions are accumulated */
    DL_ADC_PPB_LIMIT_4   = 2U,
    /*! 8 conversions are accumulated */
    DL_ADC_PPB_LIMIT_8   = 3U
} DL_ADC_PPB_LIMIT;

/*! @brief PPB PSUM shift value */
typedef enum
{
    /*! No Right shift */
    DL_ADC_PPB_SHIFT_0 = 0U,
    /*! PSUM is right shifted to 1. SUM = PSUM >> 1 */
    DL_ADC_PPB_SHIFT_1 = 1U,
    /*! PSUM is right shifted to 2. SUM = PSUM >> 2 */
    DL_ADC_PPB_SHIFT_2 = 2U,
    /*! PSUM is right shifted to 3. SUM = PSUM >> 3 */
    DL_ADC_PPB_SHIFT_3 = 3U,
    /*! PSUM is right shifted to 4. SUM = PSUM >> 4 */
    DL_ADC_PPB_SHIFT_4 = 4U,
    /*! PSUM is right shifted to 5. SUM = PSUM >> 5 */
    DL_ADC_PPB_SHIFT_5 = 5U,
    /*! PSUM is right shifted to 6. SUM = PSUM >> 6 */
    DL_ADC_PPB_SHIFT_6 = 6U,
    /*! PSUM is right shifted to 7. SUM = PSUM >> 7 */
    DL_ADC_PPB_SHIFT_7 = 7U
} DL_ADC_PPB_SHIFT;

/*! @brief PPB Compare source select */
typedef enum
{
    /*! PPB compare source is PPBRESULT */
    DL_ADC_PPB_COMPSOURCE_RESULT = 0U,
    /*! PPB compare source is PPBSUM */
    DL_ADC_PPB_COMPSOURCE_SUM    = 1U
} DL_ADC_PPB_COMPSOURCE;

/*! @brief PPB sync input */
typedef enum
{
    /*! ADC Syncin is disabled */
    DL_ADC_SYNCIN_DISABLE       = 0U,
    /*! ADC Syncin is INPUTXBAR5 */
    DL_ADC_SYNCIN_INPUTXBAR5    = 1U,
    /*! ADC Syncin is INPUTXBAR6 */
    DL_ADC_SYNCIN_INPUTXBAR6    = 2U,
    /*! ADC Syncin is ECAP0_SYNCOUT */
    DL_ADC_SYNCIN_ECAP0_SYNCOUT = 3U,
    /*! ADC Syncin is ECAP1_SYNCOUT */
    DL_ADC_SYNCIN_ECAP1_SYNCOUT = 4U,
    /*! ADC Syncin is PWM0_SYNCPER */
    DL_ADC_SYNCIN_PWM0_SYNCPER  = 5U,
    /*! ADC Syncin is PWM1_SYNCPER */
    DL_ADC_SYNCIN_PWM1_SYNCPER  = 6U,
    /*! ADC Syncin is PWM2_SYNCPER */
    DL_ADC_SYNCIN_PWM2_SYNCPER  = 7U,
    /*! ADC Syncin is PWM3_SYNCPER */
    DL_ADC_SYNCIN_PWM3_SYNCPER  = 8U,
    /*! ADC Syncin is PWM4_SYNCPER */
    DL_ADC_SYNCIN_PWM4_SYNCPER  = 9U
} DL_ADC_PPB_SYNC_INPUT;

/*! @brief ADC SOC Seqeunce preemt */
typedef enum
{
    /*! SOC Sequence preempt is disabled */
    DL_ADC_SEQ_PREEMPT_DISABLE          = 0,
    /*! SOC Sequence preempt is enabled but will not restart aborted sequence */
    DL_ADC_SEQ_PREEMPT_ENABLE_NORESTART = 2,
    /*! SOC Sequence preempt is enabled and will restart aborted sequence */
    DL_ADC_SEQ_PREEMPT_ENABLE_RESTART   = 3
} DL_ADC_SEQ_PREEMPT;

/*! @brief ADC Triggers */
/*! This specifies the event that will trigger a conversion to start. */
typedef enum
{
    DL_ADC_TRIGGER_SOFTWARE            = 0,
    DL_ADC_TRIGGER_TIMG4_0_GEN_EVENT0  = 1,
    DL_ADC_TRIGGER_TIMG12_0_GEN_EVENT0 = 3,
    DL_ADC_TRIGGER_INPUTXBAR5          = 5,
    DL_ADC_TRIGGER_PWM0_SOCA           = 6,
    DL_ADC_TRIGGER_PWM0_SOCB           = 7,
    DL_ADC_TRIGGER_PWM0_SOCC           = 8,
    DL_ADC_TRIGGER_PWM0_SOCD           = 9,
    DL_ADC_TRIGGER_PWM1_SOCA           = 10,
    DL_ADC_TRIGGER_PWM1_SOCB           = 11,
    DL_ADC_TRIGGER_PWM1_SOCC           = 12,
    DL_ADC_TRIGGER_PWM1_SOCD           = 13,
    DL_ADC_TRIGGER_PWM2_SOCA           = 14,
    DL_ADC_TRIGGER_PWM2_SOCB           = 15,
    DL_ADC_TRIGGER_PWM2_SOCC           = 16,
    DL_ADC_TRIGGER_PWM2_SOCD           = 17,
    DL_ADC_TRIGGER_PWM3_SOCA           = 18,
    DL_ADC_TRIGGER_PWM3_SOCB           = 19,
    DL_ADC_TRIGGER_PWM3_SOCC           = 20,
    DL_ADC_TRIGGER_PWM3_SOCD           = 21,
    DL_ADC_TRIGGER_PWM4_SOCA           = 22,
    DL_ADC_TRIGGER_PWM4_SOCB           = 23,
    DL_ADC_TRIGGER_PWM4_SOCC           = 24,
    DL_ADC_TRIGGER_PWM4_SOCD           = 25,
    DL_ADC_TRIGGER_ADC0_SEQ1           = 26,
    DL_ADC_TRIGGER_ADC1_SEQ1           = 27,
    DL_ADC_TRIGGER_ADC2_SEQ1           = 28,
} DL_ADC_TRIGGER;

/*! @brief Sample capacitor reset to either vrefhi/2 or vreflo */
typedef enum
{
    /*! Sample Capacitor reset to Vreflo */
    DL_ADC_SAMPLE_CAP_RESET_SELECT_VREFLO    = 0,
    /*! Sample Capacitor reset to Vrefhi/2 */
    DL_ADC_SAMPLE_CAP_RESET_SELECT_VREFHIBY2 = 1
} DL_ADC_SAMPLE_CAP_RESET_SELECT;

/**
 * @brief Step size between SOCxCTL registers
 */
#define DL_ADCSOCCTL_STEP (ADC_ADCSOC1CTL - ADC_ADCSOC0CTL)

/**
 * @brief Step size between ADCPPBxCONFIG registers
 */
#define DL_ADCPPBCONFIG_STEP (ADC_ADCPPB2CONFIG - ADC_ADCPPB1CONFIG)

/**
 * @brief Step size between ADCPPBxLIMIT registers
 */
#define DL_ADCPPBLIMIT_STEP (ADC_ADCPPB2LIMIT - ADC_ADCPPB1LIMIT)

/**
 * @brief Step size between ADCPPBxPCOUNT registers
 */
#define DL_ADCPPBPCOUNT_STEP (ADC_ADCPPB2PCOUNT - ADC_ADCPPB1PCOUNT)

/**
 * @brief Step size between ADCPPBxCONFIG2 registers
 */
#define DL_ADCPPBCONFIG2_STEP (ADC_ADCPPB2CONFIG2 - ADC_ADCPPB1CONFIG2)

/**
 * @brief Step size between ADCSEQxCONFIG registers
 */
#define DL_ADCSEQCONFIG_STEP (ADC_ADCSEQ2CONFIG - ADC_ADCSEQ1CONFIG)

/**
 * @brief Step size between ADCRESULTx registers
 */
#define DL_ADCRESULT_STEP (ADC_ADCRESULT1 - ADC_ADCRESULT0)

/**
 * @brief Step size between ADCPPBxRESULT registers
 */
#define DL_ADCPPBRESULT_STEP (ADC_ADCPPB2RESULT - ADC_ADCPPB1RESULT)

/**
 * @brief Step size between ADCPPBxSUM registers
 */
#define DL_ADCPPBSUM_STEP (ADC_ADCPPB2PSUM - ADC_ADCPPB1PSUM)

/**
 * @brief Step size between ADCPPBxCOUNT registers
 */
#define DL_ADCPPBCOUNT_STEP (ADC_ADCPPB2COUNT - ADC_ADCPPB1COUNT)

/**
 * @brief Step size between ADCSEQx FIFO Result registers
 */
#define DL_ADCSEQ_FIFORESULT_STEP (ADC_ADCSEQ2FIFORESULT - ADC_ADCSEQ1FIFORESULT)

/**
 * @brief Step size between ADCSEQx FIFO Status registers
 */
#define DL_ADCSEQ_FIFOSTATUS_STEP (ADC_ADCSEQ2FIFOSTATUS - ADC_ADCSEQ1FIFOSTATUS)

/**
 * @brief maximum value of sample window
 */
#define DL_SAMPLEWINDOW_MAX 1472

/**
 * @brief minimum value of sample window
 */
#define DL_SAMPLEWINDOW_MIN 1

/**
 * @brief maximum value of delay for early interrupt generation
 */
#define DL_CYCLE_DELAY_MAX 63

/**
 * @name  DL_ADC_EVT
 * @anchor  DL_ADC_EVT
 * @{
 */
/*!
 * @brief ADC PPB Trip High Event
 */
#define DL_ADC_EVT_TRIPHI 1U
/*!
 * @brief ADC PPB Trip Low Event
 */
#define DL_ADC_EVT_TRIPLO 2U
/*!
 * @brief ADC PPB Within Trip limit Event
 */
#define DL_ADC_EVT_NLIMIT 8U
/** @}*/

/**
 * @brief Analog Core configuration structure.
 */
typedef struct
{
    /*! Enable power to ADC core */
    bool                enablePowerAdcCore;
    /*! ADC clock prescaler
        - Valid values: @ref DL_ADC_CLK_PRESCALE
    */
    DL_ADC_CLK_PRESCALE clkPrescale;
    /*! Offset trim value
        - Valid values: @ref DL_ADC_OFFSET_TRIM
    */
    DL_ADC_OFFSET_TRIM  offsetTrim;
} DL_ADC_CoreConfig;

/**
 * @brief Sequencer N's configuration structure.
 */
typedef struct
{
    /*! Enable the sequencer */
    bool                           enableSequencer;
    /*! Sample window duration */
    uint32_t                       sampleWindow;
    /*! Trigger source
        - Valid values: @ref DL_ADC_TRIGGER
    */
    DL_ADC_TRIGGER                 trigger;
    /*! Start SOC number for this sequencer
        - Valid values: @ref DL_ADC_SOC_NUMBER
    */
    DL_ADC_SOC_NUMBER              socStartNumber;
    /*! Enable sample capacitor reset */
    bool                           enableSampleCapReset;
    /*! Sample capacitor reset value
        - Valid values: @ref DL_ADC_SAMPLE_CAP_RESET_SELECT
    */
    DL_ADC_SAMPLE_CAP_RESET_SELECT capResetVal;
} DL_ADC_SeqNConfig;

/**
 * @brief Sequencer configuration structure.
 */
typedef struct
{
    /*! Configuration of each sequencer */
    DL_ADC_SeqNConfig  seqNConfig[4];
    /*! End SOC number for all sequencers
        - Valid values: @ref DL_ADC_SOC_NUMBER
    */
    DL_ADC_SOC_NUMBER  endSocNumber;
    /*! Sequencer preemption mode
        - Valid values: @ref DL_ADC_SEQ_PREEMPT
    */
    DL_ADC_SEQ_PREEMPT seqPreemptMode;
} DL_ADC_SeqConfig;

/**
 * @brief SOC configurations structure.
 */
typedef struct
{
    /*! Channel selection for SOC.
        - Valid values: @ref DL_ADC_CHANNEL */
    DL_ADC_CHANNEL channel;
    /*! Enable comparator */
    bool           enableComparator;
} DL_ADC_SocConfig;

/**
 * @brief PPB configuration structure.
 */
typedef struct
{
    /*! Enable/disable event sources (bit mask)
        - Valid values: @ref DL_ADC_EVT*/
    uint32_t              evtFlags;
    /*! Enable/disable event interrupt sources (bit mask)
        - Valid values: @ref DL_ADC_EVT*/
    uint32_t              evtIntFlags;
    /*! Enable CBC clear */
    bool                  cbcClear;
    /*! Trip high limit */
    uint16_t              tripHiLimit;
    /*! Trip low limit */
    uint16_t              tripLoLimit;
    /*! Oversampling limit
        - Valid values: @ref DL_ADC_PPB_LIMIT
    */
    DL_ADC_PPB_LIMIT      oversamplingLimit;
    /*! Shift value
        - Valid values: @ref DL_ADC_PPB_SHIFT
    */
    DL_ADC_PPB_SHIFT      shiftVal;
    /*! Compare source
        - Valid values: @ref DL_ADC_PPB_COMPSOURCE
    */
    DL_ADC_PPB_COMPSOURCE compSrc;
    /*! Sync Input
        - Valid values: @ref DL_ADC_PPB_SYNC_INPUT
    */
    DL_ADC_PPB_SYNC_INPUT syncIn;
} DL_ADC_PpbConfig;

/**
 * @brief Interrupt block configuration structure.
 */
typedef struct
{
    /*! Enable continuous mode for interrupt */
    bool              enableContinuousMode;
    /*! Enable interrupt */
    bool              enableInterrupt;
    /*! Interrupt trigger SOC number
        - Valid values: @ref DL_ADC_SOC_NUMBER
    */
    DL_ADC_SOC_NUMBER trigger;
} DL_ADC_IntNConfig;

/**
 * @brief Interrupt configuration structure.
 */
typedef struct
{
    /*! Interrupt cycle delay.
        - Delay in terms of system clock cycles
    */
    uint8_t              interruptCycleDelay;
    /*! Interrupt pulse position
        - Valid values: @ref DL_ADC_INT_PULSE_POS
    */
    DL_ADC_INT_PULSE_POS pulseMode;
    /*! Configuration of each interrupt block */
    DL_ADC_IntNConfig    intNConfig[4];
    /*! Configuration of each DMA interrupt block */
    DL_ADC_IntNConfig    dmaIntNConfig[4];
} DL_ADC_IntConfig;

/**
 * @brief Main configuration structure for the ADC.
 */
typedef struct
{
    /*! Analog Core configurations */
    DL_ADC_CoreConfig coreConfig;
    /*! SOC configurations */
    DL_ADC_SocConfig  socConfig[16];
    /*! Sequencer configurations */
    DL_ADC_SeqConfig  seqConfig;
    /*! PPB configurations */
    DL_ADC_PpbConfig  ppbConfig[4];
    /*! Interrupt configurations */
    DL_ADC_IntConfig  intConfig;
} DL_ADC_Config;

/**
 * @brief   Enables power for the ADC module
 *
 * The API enables the ADC module. To configure any ADC register, the ADC module
 * should be enabled by setting the PWREN register with an appropriate KEY value.
 *
 * @param adc       Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ADC_enablePower(ADC_Regs *adc)
{
    adc->GPRCM.PWREN = (ADC_PWREN_KEY_UNLOCK_W | ADC_PWREN_ENABLE_ENABLE);
}

/**
 * @brief   Disables power for the ADC module
 *
 * The API disables the ADC module. This means that the ADC registers are not
 * accessible for read/write operations.
 *
 * @param adc       Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ADC_disablePower(ADC_Regs *adc)
{
    adc->GPRCM.PWREN = (ADC_PWREN_KEY_UNLOCK_W | ADC_PWREN_ENABLE_DISABLE);
}

/**
 * @brief Returns if power enable (PWREN) register for the ADC is enabled
 *
 * @param adc       Pointer to the register overlay for the peripheral
 *
 * @return true if power is enabled
 * @return false if power is disabled
 */
__STATIC_INLINE bool DL_ADC_isPowerEnabled(ADC_Regs *adc)
{
    return ((adc->GPRCM.PWREN & ADC_PWREN_ENABLE_MASK) == ADC_PWREN_ENABLE_ENABLE);
}

/**
 * @brief Resets ADC peripheral
 *
 * @param adc       Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ADC_reset(ADC_Regs *adc)
{
    adc->GPRCM.RSTCTL = (ADC_RSTCTL_KEY_UNLOCK_W | ADC_RSTCTL_RESETSTKYCLR_CLR | ADC_RSTCTL_RESETASSERT_ASSERT);
}

/**
 * @brief Returns if ADC peripheral was reset
 *
 * @param adc       Pointer to the register overlay for the peripheral
 *
 * @return true if peripheral was reset
 * @return false if peripheral was not reset
 */
__STATIC_INLINE bool DL_ADC_isReset(ADC_Regs *adc)
{
    return ((adc->GPRCM.STAT & ADC_STAT_RESETSTKYCLR_MASK) == ADC_STAT_RESETSTKYCLR_RESET);
}

/**
 * @brief Returns if ADC is busy and cannot sample another channel
 *
 * @param adc       Pointer to the register overlay for the peripheral
 *
 * @return true if ADC is busy sampling
 * @return false if all samples are complete and available to sample another channel
 */
__STATIC_INLINE bool DL_ADC_isBusy(ADC_Regs *adc)
{
    return ((adc->ADCCTL1 & ADC_ADCCTL1_ADCBSY_MASK) == ADC_ADCCTL1_ADCBSY_MASK);
}

/**
 * @brief Returns the current processing SOC or last converted SOC
 *
 * @param adc       Pointer to the register overlay for the peripheral
 *
 * @return SOC number of the last busy or current processing channel (4 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_lastBusyChannel(ADC_Regs *adc)
{
    return (((adc->ADCCTL1) & ADC_ADCCTL1_ADCBSYCHN_MASK) >> ADC_ADCCTL1_ADCBSYCHN_OFS);
}

/**
 * @brief Powers up the analog-to-digital converter core.
 *
 * This API powers up the analog circuitry inside the analog core.
 *
 * @note Allow at least a 500us delay before sampling after calling this API.
 *       If you enable multiple ADCs, you can delay after they all have begun
 *       powering up.
 *
 * @param adc       Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ADC_powerUp(ADC_Regs *adc)
{
    adc->ADCCTL1 |= ADC_ADCCTL1_ADCPWDNZ_MASK;
}

/**
 * @brief Powers down the analog-to-digital converter core.
 *
 * This API powers down the analog circuitry inside the analog core.
 *
 * @param adc       Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_ADC_powerDown(ADC_Regs *adc)
{
    adc->ADCCTL1 &= ~(ADC_ADCCTL1_ADCPWDNZ_MASK);
}

/**
 * @brief Sets interrupt pulse position
 *
 * This API configures the end-of-conversion (EOC) pulse generated by ADC.
 * This pulse will be generated either at the end of the acquisition window
 * plus a number of SYSCLK cycles configured by ADC_setInterruptCycleOffset()
 * (pass \b DL_ADC_PULSE_END_OF_ACQ_WIN into \e pulseMode) or at the end of the
 * voltage conversion, one cycle prior to the ADC result latching into it's
 * result register (pass \b DL_ADC_PULSE_END_OF_CONV into \e pulseMode).
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] pulseMode is the pulse position you want to set, can be 0 or 1
 */
__STATIC_INLINE void DL_ADC_setInterruptPulseMode(ADC_Regs *adc, DL_ADC_INT_PULSE_POS pulseMode)
{
    adc->ADCCTL1 = (adc->ADCCTL1 & ~(ADC_ADCCTL1_INTPULSEPOS_MASK)) | (pulseMode << ADC_ADCCTL1_INTPULSEPOS_OFS);
}

/**
 * @brief Sets clock prescaler value or clock divide ratio value
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] clkPrescale is the valid clock prescaler value you want to set
                          to make the ADCCLK. @ref DL_ADC_CLK_PRESCALE
 */
__STATIC_INLINE void DL_ADC_setPrescaler(ADC_Regs *adc, DL_ADC_CLK_PRESCALE clkPrescale)
{
    adc->ADCCTL2 = (adc->ADCCTL2 & ~(ADC_ADCCTL2_PRESCALE_MASK)) | clkPrescale;
}

/**
 * @brief Enables continue mode for an ADC interrupt.
 *
 * The ADCINT pulses will be generated for the specified ADC interrupt whenever
 * an EOC pulse is generated irrespective of whether or not the flag bit is set.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_enableContinuousMode(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    adc->ADCINTSEL |=
        (ADC_ADCINTSEL_INT1CONT_MASK << (adcIntNum * (ADC_ADCINTSEL_INT2CONT_OFS - ADC_ADCINTSEL_INT1CONT_OFS)));
}

/**
 * @brief Disables continue mode for an ADC interrupt.
 *
 * The ADCINT pulses will not be generated for the specified ADC interrupt until
 * the corresponding interrupt flag for the previous interrupt occurrence
 * has been cleared using DL_ADC_clearInterruptStatus().
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_disableContinuousMode(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    adc->ADCINTSEL &=
        ~(ADC_ADCINTSEL_INT1CONT_MASK << (adcIntNum * (ADC_ADCINTSEL_INT2CONT_OFS - ADC_ADCINTSEL_INT1CONT_OFS)));
}

/**
 * @brief Enables an ADC interrupt source.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_enableInterrupt(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    adc->ADCINTSEL |= ADC_ADCINTSEL_INT1E_MASK << (adcIntNum * (ADC_ADCINTSEL_INT2E_OFS - ADC_ADCINTSEL_INT1E_OFS));
}

/**
 * @brief Disables an ADC interrupt source.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_disableInterrupt(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    adc->ADCINTSEL &= ~(ADC_ADCINTSEL_INT1E_MASK << (adcIntNum * (ADC_ADCINTSEL_INT2E_OFS - ADC_ADCINTSEL_INT1E_OFS)));
}

/**
 * @brief Selects which EOC to be selected as a source for the interrupt
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 * @param[in] intTrigger is the interrupt trigger to be configured
 */
__STATIC_INLINE void DL_ADC_setInterruptSource(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum, DL_ADC_SOC_NUMBER intTrigger)
{
    uint32_t shiftVal = adcIntNum * (ADC_ADCINTSEL_INT2SEL_OFS - ADC_ADCINTSEL_INT1SEL_OFS);
    adc->ADCINTSEL    = (adc->ADCINTSEL & ~(ADC_ADCINTSEL_INT1SEL_MASK << shiftVal)) | (intTrigger << shiftVal);
}

/**
 * @brief Enables continue mode for an ADC interrupt for DMA.
 *
 * The ADCDMAINT pulses will be generated for the specified ADC interrupt for DMA whenever
 * an EOC pulse is generated irrespective of whether or not the flag bit is set.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_enableDMAContinuousMode(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    uint32_t shiftVal  = adcIntNum * (ADC_ADCDMAINTSEL_DMAINT2CONT_OFS - ADC_ADCDMAINTSEL_DMAINT1CONT_OFS);
    adc->ADCDMAINTSEL |= (ADC_ADCDMAINTSEL_DMAINT1CONT_MASK << shiftVal);
}

/**
 * @brief Disables continue mode for an ADC interrupt for DMA.
 *
 * The ADCDMAINT pulses will not be generated for the specified ADC interrupt for DMA until
 * the corresponding interrupt flag for the previous interrupt occurrence
 * has been cleared using DL_ADC_clearDMAInterruptStatus().
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_disableDMAContinuousMode(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    uint32_t shiftVal  = adcIntNum * (ADC_ADCDMAINTSEL_DMAINT2CONT_OFS - ADC_ADCDMAINTSEL_DMAINT1CONT_OFS);
    adc->ADCDMAINTSEL &= ~(ADC_ADCDMAINTSEL_DMAINT1CONT_MASK << shiftVal);
}

/**
 * @brief Enables an ADC interrupt for DMA.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_enableDMAInterrupt(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    uint32_t shiftVal  = adcIntNum * (ADC_ADCDMAINTSEL_DMAINT2E_OFS - ADC_ADCDMAINTSEL_DMAINT1E_OFS);
    adc->ADCDMAINTSEL |= ADC_ADCDMAINTSEL_DMAINT1E_MASK << shiftVal;
}

/**
 * @brief Disables an ADC interrupt for DMA.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_disableDMAInterrupt(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    uint32_t shiftVal  = adcIntNum * (ADC_ADCDMAINTSEL_DMAINT2E_OFS - ADC_ADCDMAINTSEL_DMAINT1E_OFS);
    adc->ADCDMAINTSEL &= ~(ADC_ADCDMAINTSEL_DMAINT1E_MASK << shiftVal);
}

/**
 * @brief Selects which EOC to be selected as a source for the DMA interrupt
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 * @param[in] intTrigger is the interrupt trigger to be configured
 */
__STATIC_INLINE void DL_ADC_setDMAInterruptSource(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum,
                                                  DL_ADC_SOC_NUMBER intTrigger)
{
    uint32_t shiftVal = adcIntNum * (ADC_ADCDMAINTSEL_DMAINT2SEL_OFS - ADC_ADCDMAINTSEL_DMAINT1SEL_OFS);
    adc->ADCDMAINTSEL =
        (adc->ADCDMAINTSEL & ~(ADC_ADCDMAINTSEL_DMAINT1SEL_MASK << shiftVal)) | (intTrigger << shiftVal);
}

/**
 * @brief Returns the Raw ADC interrupt status.
 *
 * This API returns the raw ADC interrupt status which indicates if the
 * associated interrupt condition occured. This flag will be set irrespective
 * of corresponding interrupt enable settings.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 *
 * @return true if Selected EOC event occured
 * @return false if Selected EOC event did not occur
 */
__STATIC_INLINE bool DL_ADC_getRawInterruptStatus(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    return (((adc->ADCRAWINTFLG >> adcIntNum) & ADC_ADCRAWINTFLG_ADCRAWINT1_MASK) == ADC_ADCRAWINTFLG_ADCRAWINT1_MASK);
}

/**
 * @brief Returns the Raw ADC DMA interrupt status.
 *
 * This API returns the raw ADC DMA interrupt status which indicates if the
 * associated interrupt condition occured. This flag will be set irrespective
 * of corresponding DMA interrupt enable settings.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 *
 * @return true if Selected EOC event occured
 * @return false if Selected EOC event did not occur
 */
__STATIC_INLINE bool DL_ADC_getRawDMAInterruptStatus(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    return (((adc->ADCRAWINTFLG >> adcIntNum) & ADC_ADCRAWINTFLG_ADCDMARAWINT1_MASK) ==
            ADC_ADCRAWINTFLG_ADCDMARAWINT1_MASK);
}

/**
 * @brief Returns the current ADC interrupt status.
 *
 * This API returns the interrupt status for the analog-to-digital converter.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 *
 * @return true if ADCINT pulse generated
 * @return false if ADCINT pulse not generated
 */
__STATIC_INLINE bool DL_ADC_getInterruptStatus(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    return (((adc->ADCINTFLG >> adcIntNum) & ADC_ADCINTFLG_ADCINT1_MASK) == ADC_ADCINTFLG_ADCINT1_MASK);
}

/**
 * @brief Returns the result ready Flag Status for ADC interrupt.
 *
 * The result ready flag is set when the conversion results associated with ADCINTx latch
 * into the corresponding results register. This flag can be used in an ISR that is entered
 * in early interrupt mode to ensure that the corresponding results are ready before proceeding
 * to read the result register.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 *
 * @return true if conversion results have latched
 * @return false if conversion results have not latched
 */
__STATIC_INLINE bool DL_ADC_getInterruptResultReadyStatus(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    return (((adc->ADCINTFLG >> adcIntNum) & ADC_ADCINTFLG_ADCINT1RESULT_MASK) == ADC_ADCINTFLG_ADCINT1RESULT_MASK);
}

/**
 * @brief Returns the current ADC DMA Interrupt Flag status.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 *
 * @return true if ADCDMAINT pulse generated
 * @return false if ADCDMAINT pulse not generated
 */
__STATIC_INLINE bool DL_ADC_getDMAInterruptStatus(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    return (((adc->ADCINTFLG >> adcIntNum) & ADC_ADCINTFLG_ADCDMAINT1_MASK) == ADC_ADCINTFLG_ADCDMAINT1_MASK);
}

/**
 * @brief Force ADC interrupt flags status
 *
 * This API forces ADCINT flags in the ADCINTFLG and ADCRAWINTFLG registers.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_forceInterruptStatus(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    adc->ADCINTFLGFRC |= (ADC_ADCINTFLGFRC_ADCINT1_MASK << adcIntNum);
}

/**
 * @brief Force ADC DMA interrupt flag status
 *
 * This API forces ADCDMAINT flags in the ADCINTFLG and ADCRAWINTFLG registers.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_forceDMAInterruptStatus(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    adc->ADCINTFLGFRC |= (ADC_ADCINTFLGFRC_ADCDMAINT1_MASK << adcIntNum);
}

/**
 * @brief Clears ADC interrupt flag status
 *
 * This API clears the specified ADC interrupt status in ADCINTFLG, ADCRAWINTFLG registers
 * so that they no longer assert. If not in continuous mode, this function must be called
 * before any further interrupt pulses may occur. If software sets the clear bit on the
 * same cycle that hardware is trying to set the flag it, then hardware has priority
 * and the overflow bit will not be set.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_clearInterruptStatus(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    adc->ADCINTFLGCLR |= (ADC_ADCINTFLGCLR_ADCINT1_MASK << adcIntNum);
}

/**
 * @brief Clears ADC DMA interrupt flag status
 * This API clears the specified ADC DMA interrupt status in ADCINTFLG, ADCRAWINTFLG registers
 * so that they no longer assert. If software sets the clear bit on the same cycle that hardware
 * is trying to set the flag it, then hardware has priority and the overflow bit will not be set.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_clearDMAInterruptStatus(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    adc->ADCINTFLGCLR |= (ADC_ADCINTFLGCLR_ADCINT1_MASK << (adcIntNum + ADC_ADCINTFLGCLR_ADCDMAINT1_OFS));
}

/**
 * @brief Returns Interrupt Overflow status
 *
 * The interrupt overflow flag is set if an overflow occurred when generating ADCINT pulses.
 * If the respective ADCINTFLG bit is set and a selected additional EOC trigger is generated,
 * then an overflow condition occurs.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 *
 * @return true if ADC interrupt overflow flag for the specified interrupt is set
 * @return false if No ADC interrupt overflow flag is set
 */
__STATIC_INLINE bool DL_ADC_getInterruptOverflowStatus(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    return (((adc->ADCINTOVF >> adcIntNum) & ADC_ADCINTOVF_ADCINT1OVF_MASK) == ADC_ADCINTOVF_ADCINT1OVF_MASK);
}

/**
 * @brief Returns DMA Interrupt Overflow status
 *
 * The DMA interrupt overflow flag is set if an overflow occurred when generating
 * ADCINT pulses. If the respective ADCINTFLG bit is set and a selected additional
 * EOC trigger is generated, then an overflow condition occurs.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 *
 * @return true if ADC DMA interrupt overflow flag for the specified interrupt is set
 * @return false if No ADC DMA interrupt overflow flag is set
 */
__STATIC_INLINE bool DL_ADC_getDMAInterruptOverflowStatus(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    return (((adc->ADCINTOVF >> adcIntNum) & ADC_ADCINTOVF_ADCDMAINT1OVF_MASK) == ADC_ADCINTOVF_ADCDMAINT1OVF_MASK);
}

/**
 * @brief Clears ADC interrupt overflow status flag
 *
 * If software tries to clear the overflow in the same cycle that hardware tries
 * to set the overflow, then hardware has priority.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_clearInterruptOverflowStatus(ADC_Regs *adc, DL_ADC_INT_NUMBER adcIntNum)
{
    adc->ADCINTOVFCLR |= (ADC_ADCINTOVFCLR_ADCINT1OVF_MASK << adcIntNum);
}

/**
 * @brief Clears ADC DMA interrupt overflow status flag
 *
 * If software tries to clear the overflow in the same cycle that hardware tries
 * to set the overflow, then hardware has priority.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] adcIntNum The interrupt number to be used
 */
__STATIC_INLINE void DL_ADC_clearDMAInterruptOverflowStatus(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER adcIntNum)
{
    adc->ADCINTOVFCLR |= (ADC_ADCINTOVFCLR_ADCDMAINT1OVF_MASK << adcIntNum);
}

/**
 * @brief Returns Start of Conversion Status
 *
 * This Flag is set when Trigger has been received and sample is pending for SOCx.
 * The Flag will be automatically cleared when the SOCx conversion is started
 * where x is the soc number.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] socNumber is the number of the start-of-conversion
 *
 * @return true if no sample pending for SOC
 * @return false if trigger has been received and sample is pending for SOC
 */
__STATIC_INLINE bool DL_ADC_getSOCStatus(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber)
{
    return (((adc->ADCSOCFLG1 >> socNumber) & ADC_ADCSOCFLG1_SOC0_MASK) == ADC_ADCSOCFLG1_SOC0_MASK);
}

/**
 * @brief Returns Start of Conversion Overflow Status
 *
 * This Flag is set, if an SOCx event was generated in hardware while
 * an existing SOCx event was already penidng, where x is the soc number.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] socNumber is the number of the start-of-conversion
 *
 * @return true if no SOC event overflow has occured
 * @return false if SOC event overflow has occured
 */
__STATIC_INLINE bool DL_ADC_getSOCOverflowStatus(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber)
{
    return (((adc->ADCSOCOVF1 >> socNumber) & ADC_ADCSOCOVF1_SOC0OVF_MASK) == ADC_ADCSOCOVF1_SOC0OVF_MASK);
}

/**
 * @brief Clears Start of Conversion Overflow flag
 *
 * This API clears SOCx overflow flag. If software tries to set this bit on the same
 * clock cycle that hardware tries to set the overflow bit in the register, then hardware
 * has the priority and the register will be set.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] socNumber is the number of the start-of-conversion
 */
__STATIC_INLINE void DL_ADC_clearSOCOverflowStatus(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber)
{
    adc->ADCSOCOVFCLR1 |= ADC_ADCSOCOVFCLR1_SOC0OVF_MASK << socNumber;
}

/**
 * @brief Selects the channel to be converted
 *
 * This API slects the channel to be converted when the SOCx event
 * is recieved by the ADC, where x is the soc number.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] socNumber is the number of the start-of-conversion
 * @param[in] channel   is the number associated with the input signal.
 */
__STATIC_INLINE void DL_ADC_selectSOCChannel(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber, DL_ADC_CHANNEL channel)
{
    volatile uint32_t *ctlRegAddr;
    ctlRegAddr  = (uint32_t *)((uint8_t *)&adc->ADCSOC0CTL + socNumber * DL_ADCSOCCTL_STEP);
    *ctlRegAddr = (*ctlRegAddr & ~ADC_ADCSOC0CTL_CHSEL_MASK) | (channel << ADC_ADCSOC0CTL_CHSEL_OFS);
}

/**
 * @brief Enables SOC thrashold comparator
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] socNumber is the number of the start-of-conversion
 */
__STATIC_INLINE void DL_ADC_enableSOCComparator(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber)
{
    volatile uint32_t *ctlRegAddr;
    ctlRegAddr   = (uint32_t *)((uint8_t *)&adc->ADCSOC0CTL + socNumber * DL_ADCSOCCTL_STEP);
    *ctlRegAddr |= ADC_ADCSOC0CTL_COMPEN_MASK;
}

/**
 * @brief Disables SOC thrashold comparator
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] socNumber is the number of the start-of-conversion
 */
__STATIC_INLINE void DL_ADC_disableSOCComparator(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber)
{
    volatile uint32_t *ctlRegAddr;
    ctlRegAddr   = (uint32_t *)((uint8_t *)&adc->ADCSOC0CTL + socNumber * DL_ADCSOCCTL_STEP);
    *ctlRegAddr &= ~(ADC_ADCSOC0CTL_COMPEN_MASK);
}

/**
 * @brief Returns PPB TRIP high status
 *
 * The Flag is set, if the digital compare trip high event has occurred for PPBx,
 * where x is the ppb number.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] ppbNumber is the number of the post-processing block
 *
 * @return true if trip high event has occurred
 * @return false if trip high event has not occurred
 */
__STATIC_INLINE bool DL_ADC_getPPBTripHighStatus(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber)
{
    uint32_t shiftVal = ppbNumber * (ADC_ADCEVTSTAT_PPB2TRIPHI_OFS - ADC_ADCEVTSTAT_PPB1TRIPHI_OFS);
    return (((adc->ADCEVTSTAT >> shiftVal) & ADC_ADCEVTSTAT_PPB1TRIPHI_MASK) == ADC_ADCEVTSTAT_PPB1TRIPHI_MASK);
}

/**
 * @brief Returns PPB TRIP low status
 *
 * The Flag is set, if the digital compare trip low event has occurred for PPBx,
 * where x is the ppb number.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] ppbNumber is the number of the post-processing block
 *
 * @return true if trip low event has occurred
 * @return false if trip low event has not occurred
 */
__STATIC_INLINE bool DL_ADC_getPPBTripLowStatus(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber)
{
    uint32_t shiftVal = ppbNumber * (ADC_ADCEVTSTAT_PPB2TRIPLO_OFS - ADC_ADCEVTSTAT_PPB1TRIPLO_OFS);
    return (((adc->ADCEVTSTAT >> shiftVal) & ADC_ADCEVTSTAT_PPB1TRIPLO_MASK) == ADC_ADCEVTSTAT_PPB1TRIPLO_MASK);
}

/**
 * @brief Returns PPB TRIP limit status
 *
 * The Flag is set, if the digital compare trip limit event has occurred in PPBx,
 * where x is the ppb number.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] ppbNumber is the number of the post-processing block
 *
 * @return true if trip limit event has occurred
 * @return false if trip limit event has not occurred
 */
__STATIC_INLINE bool DL_ADC_getPPBTripLimitStatus(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber)
{
    uint32_t shiftVal = ppbNumber * (ADC_ADCEVTSTAT_PPB2INLIMIT_OFS - ADC_ADCEVTSTAT_PPB1INLIMIT_OFS);
    return (((adc->ADCEVTSTAT >> shiftVal) & ADC_ADCEVTSTAT_PPB1INLIMIT_MASK) == ADC_ADCEVTSTAT_PPB1INLIMIT_MASK);
}

/**
 * @ brief Clears the corresponding PPB events in the ADCEVTSTAT register
 *
 * This API clears the indicated ADC PPB event flags. After an event occurs
 * this function must be called to allow additional events to be prduced.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] ppbNumber is the number of the post-processing block
 * @param evtFlags      Bit mask of the event source to be cleared.
                        @ref DL_ADC_EVT.
 */
__STATIC_INLINE void DL_ADC_clearPPBEventStatus(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, uint32_t evtFlags)
{
    adc->ADCEVTCLR |=
        (uint32_t)(evtFlags << (ppbNumber * (ADC_ADCEVTCLR_PPB2TRIPHI_OFS - ADC_ADCEVTCLR_PPB1TRIPHI_OFS)));
}

/**
 * @brief Enables individual ADC PPB event sources
 *
 * This API allows the specified PPB events to activate the event signal to the PWM blocks.
 * The flag must be cleared before it can produce additional events to the PWM blocks.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] ppbNumber is the number of the post-processing block
 * @param evtFlags      Bit mask of the event source to be enabled.
                        @ref DL_ADC_EVT.
 */
__STATIC_INLINE void DL_ADC_enablePPBEvent(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, uint32_t evtFlags)
{
    adc->ADCEVTSEL |=
        (uint32_t)(evtFlags << (ppbNumber * (ADC_ADCEVTSEL_PPB2TRIPHI_OFS - ADC_ADCEVTSEL_PPB1TRIPHI_OFS)));
}

/**
 * @brief Disables individual ADC PPB event sources
 *
 * This API disables the specified PPB events from propagating to other modules.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] ppbNumber is the number of the post-processing block
 * @param evtFlags      Bit mask of the event source to be disabled.
                        @ref DL_ADC_EVT.
 */
__STATIC_INLINE void DL_ADC_disablePPBEvent(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, uint32_t evtFlags)
{
    adc->ADCEVTSEL &=
        ~(uint32_t)(evtFlags << (ppbNumber * (ADC_ADCEVTSEL_PPB2TRIPHI_OFS - ADC_ADCEVTSEL_PPB1TRIPHI_OFS)));
}

/**
 * @brief Enables individual ADC PPB event interrupt sources.
 *
 * This API allows the specified PPB events to activate the event interrupt signal to the PIE.
 * The flag must be cleared before it can produce additional interrupts to the PIE.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] ppbNumber is the number of the post-processing block
 * @param intFlags      Bit mask of the event interrupt source to be enabled.
                        @ref DL_ADC_EVT.
 */
__STATIC_INLINE void DL_ADC_enablePPBEventInterrupt(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, uint32_t intFlags)
{
    adc->ADCEVTINTSEL |=
        (uint32_t)(intFlags << (ppbNumber * (ADC_ADCEVTINTSEL_PPB2TRIPHI_OFS - ADC_ADCEVTINTSEL_PPB1TRIPHI_OFS)));
}

/**
 * @brief Disables individual ADC PPB event interrupt sources.
 *
 * This API allows the specified PPB events to activate the event interrupt signal to the PIE.
 * The flag must be cleared before it can produce additional interrupts to the PIE.
 *
 * @param[in] adc       Pointer to the register overlay for the peripheral
 * @param[in] ppbNumber is the number of the post-processing block
 * @param intFlags      Bit mask of the event interrupt source to be disabled.
                        @ref DL_ADC_EVT.
 */
__STATIC_INLINE void DL_ADC_disablePPBEventInterrupt(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, uint32_t intFlags)
{
    adc->ADCEVTINTSEL &=
        ~(uint32_t)(intFlags << (ppbNumber * (ADC_ADCEVTINTSEL_PPB2TRIPHI_OFS - ADC_ADCEVTINTSEL_PPB1TRIPHI_OFS)));
}

/**
 * @brief Returns ADC Type.
 *
 * It is always set to 6 for ADC-12b.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 *
 * @return     ADC Type number (8 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_getADCType(ADC_Regs *adc)
{
    return (adc->ADCREV & ADC_ADCREV_TYPE_MASK);
}

/**
 * @brief Returns ADC Revision
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 *
 * @return     ADC Revision number (24 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_getADCRevision(ADC_Regs *adc)
{
    return (uint32_t)((adc->ADCREV & ADC_ADCREV_REV_MASK) >> ADC_ADCREV_REV_OFS);
}

/**
 * @brief Sets ADC Offset Trim
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  offsetTrim is the offset trim
 */
__STATIC_INLINE void DL_ADC_setOffsetTrim(ADC_Regs *adc, DL_ADC_OFFSET_TRIM offsetTrim)
{
    adc->ADCOFFTRIM = (adc->ADCOFFTRIM & ~(ADC_ADCOFFTRIM_OFFTRIM_MASK)) | offsetTrim;
}

/**
 * @brief Enables cycle-by-cycle clear of ADC PPB event flags
 *
 * This API enables automatic cycle-by-cycle clear of ADC PPB event flags.
 * When enabled, the desired PPB event flags (ADCEVTSTAT) are automatically cleared
 * on the next PPBxRESULT load, unless a set condition is also occurring at
 * the same time, in which case the set takes precedence.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 */
__STATIC_INLINE void DL_ADC_enablePPBEventCBCClear(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber)
{
    volatile uint32_t *ppbConfigAddr;
    ppbConfigAddr   = (uint32_t *)((uint8_t *)&adc->ADCPPB1CONFIG + ppbNumber * DL_ADCPPBCONFIG_STEP);
    *ppbConfigAddr |= ADC_ADCPPB1CONFIG_CBCEN_MASK;
}

/**
 * @brief Disables cycle-by-cycle clear of ADC PPB event flags
 *
 * This API disables the cycle-by-cycle clear of ADC PPB event flags. When disabled,
 * the desired PPB event flags are to be cleared explicitly in software inorder
 * to generate next set of interrupts/events.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 */
__STATIC_INLINE void DL_ADC_disablePPBEventCBCClear(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber)
{
    volatile uint32_t *ppbConfigAddr;
    ppbConfigAddr   = (uint32_t *)((uint8_t *)&adc->ADCPPB1CONFIG + ppbNumber * DL_ADCPPBCONFIG_STEP);
    *ppbConfigAddr &= ~(ADC_ADCPPB1CONFIG_CBCEN_MASK);
}

/**
 * @brief Sets the digital comparator trip high limit
 *
 * This API sets the windowed trip high limits for a PPB. This value set
 * the digital comparator so that when the value is exceeded, a high event will occur.
 * When comparing to an ADCPPBxRESULT register, the upper bits TRIPHI[15:13]
 * will be ignored.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 * @param[in]  tripHiLimit is the value of the digital comparator trip high limit.
 */
__STATIC_INLINE void DL_ADC_setPPBTripHighLimit(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, uint16_t tripHiLimit)
{
    volatile uint32_t *ppbConfigAddr;
    ppbConfigAddr  = (uint32_t *)((uint8_t *)&adc->ADCPPB1TRIPHI + ppbNumber * DL_ADCPPBCONFIG_STEP);
    *ppbConfigAddr = (*ppbConfigAddr & ~(ADC_ADCPPB1TRIPHI_LIMITHI_MASK)) | tripHiLimit;
}

/**
 * @brief Sets the digital comparator trip low limit
 *
 * This API sets the windowed trip low limits for a PPB if ADCPPB{#}TRIPLO.LIMITLO2EN = 1.
 * This value set the digital comparator so that when the value is exceeded, a low event
 * will occur. When comparing to an ADCPPBxRESULT register, the upper bits TRIPHI[15:13]
 * will be ignored.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 * @param[in]  tripLoLimit is the value of the digital comparator trip low limit.
 */
__STATIC_INLINE void DL_ADC_setPPBTripLowLimit(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, uint16_t tripLoLimit)
{
    volatile uint32_t *ppbConfigAddr;
    ppbConfigAddr  = (uint32_t *)((uint8_t *)&adc->ADCPPB1TRIPLO + ppbNumber * DL_ADCPPBCONFIG_STEP);
    *ppbConfigAddr = (*ppbConfigAddr & ~(ADC_ADCPPB1TRIPLO_LIMITLO_MASK)) | tripLoLimit;
}

/**
 * @brief Sets the timing of early interrupt generation
 *
 * This API configures the cycle delay between the negative edge of a sample pulse
 * and an early interrupt pulse being generated. It only applies when early interrupt
 * generation is enabled. That means the DL_ADC_setInterruptPulseMode() API's
 * pulseMode parameter is configured as DL_ADC_PULSE_END_OF_ACQ_WIN.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  cycleDelay is the delay in terms of system clock cycles
 */
__STATIC_INLINE void DL_ADC_setInterruptCycleDelay(ADC_Regs *adc, uint8_t cycleDelay)
{
    ASSERT(cycleDelay <= DL_CYCLE_DELAY_MAX);
    adc->ADCINTCYCLE = (adc->ADCINTCYCLE & ~(ADC_ADCINTCYCLE_DELAY_MASK)) | cycleDelay;
}

/**
 * @brief Returns the ADC wrapper type
 *
 * It is always set to 6 for this ADC.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 *
 * @return     ADC Wrapper Type (8 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_getADCWrapperType(ADC_Regs *adc)
{
    return (adc->ADCREV2 & ADC_ADCREV2_WRAPPERTYPE_MASK);
}

/**
 * @brief Returns the ADC wrapper revision
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 *
 * @return     ADC Wrapper Revision version (24 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_getADCWrapperRevision(ADC_Regs *adc)
{
    return ((adc->ADCREV2 & ADC_ADCREV2_WRAPPERREV_MASK) >> ADC_ADCREV2_WRAPPERREV_OFS);
}

/**
 * @brief Sets the oversampling limit
 *
 * This API configures the PPB oversampling count limit which defines the
 * number of ADC conversions to accumulate before partial sum is automatically
 * loaded to the sum registes.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 * @param[in]  limit is the oversampling limit
 */
__STATIC_INLINE void DL_ADC_setPPBOversamplingLimit(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, DL_ADC_PPB_LIMIT limit)
{
    volatile uint32_t *ppbLimitAddr;
    ppbLimitAddr  = (uint32_t *)((uint8_t *)&adc->ADCPPB1LIMIT + ppbNumber * DL_ADCPPBLIMIT_STEP);
    *ppbLimitAddr = (*ppbLimitAddr & ~(ADC_ADCPPB1LIMIT_LIMIT_MASK)) | limit;
}

/**
 * @brief Reads the oversampling partial count
 *
 * The API returns the oversampled partial count. Each time a new result
 * propagates through the PPB signal chain and accumulates into ADCPPB{#}PSUM,
 * PPB{#}PCOUNT register is incremented by 1. The partial count result is available
 * 1 SYSCLK cycle after the associated ADCPPB{#}RESULT is available. That means it
 * will be 2 SYSCLK cycles after the associated ADCRESULT is available, unless
 * multiple PPBs point to the same SOC.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 *
 * @return     Oversampled Partial Count (3 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_readPPBPCount(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber)
{
    volatile uint32_t *ppbpcountAddr;
    ppbpcountAddr = (uint32_t *)((uint8_t *)&adc->ADCPPB1PCOUNT + ppbNumber * DL_ADCPPBPCOUNT_STEP);
    return (*ppbpcountAddr & ADC_ADCPPB1PCOUNT_PCOUNT_MASK);
}

/**
 * @brief Sets PPB shift value
 *
 * This API configures the shift value required to right shift the PPB PSUM
 * before loading into the final PPB SUM.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 * @param[in]  shiftVal is the number of bits to right shift PPB PSUM
 */
__STATIC_INLINE void DL_ADC_setPPBShiftValue(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, DL_ADC_PPB_SHIFT shiftVal)
{
    volatile uint32_t *ppbConfig2Addr;
    ppbConfig2Addr  = (uint32_t *)((uint8_t *)&adc->ADCPPB1CONFIG2 + ppbNumber * DL_ADCPPBCONFIG2_STEP);
    *ppbConfig2Addr = (*ppbConfig2Addr & ~(ADC_ADCPPB1CONFIG2_SHIFT_MASK)) | (shiftVal << ADC_ADCPPB1CONFIG2_SHIFT_OFS);
}

/**
 * @brief Configures PPB compare source
 *
 * This API configures the desired source to be used for threshold compare.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 * @param[in]  compSrc is the desired source to be used for threshold compare.
 */
__STATIC_INLINE void DL_ADC_selectPPBCompareSource(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber,
                                                   DL_ADC_PPB_COMPSOURCE compSrc)
{
    volatile uint32_t *ppbConfig2Addr;
    ppbConfig2Addr = (uint32_t *)((uint8_t *)&adc->ADCPPB1CONFIG2 + ppbNumber * DL_ADCPPBCONFIG2_STEP);
    *ppbConfig2Addr =
        (*ppbConfig2Addr & ~(ADC_ADCPPB1CONFIG2_COMPSEL_MASK)) | (compSrc << ADC_ADCPPB1CONFIG2_COMPSEL_OFS);
}

/**
 * @brief Configures PPB Sync source
 *
 * This API configures the desired sync source to be used for PPB.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 * @param[in]  syncInSrc is the desired sync source to be used for PPB.
 */
__STATIC_INLINE void DL_ADC_selectPPBSyncSource(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber,
                                                DL_ADC_PPB_SYNC_INPUT syncInSrc)
{
    volatile uint32_t *ppbConfig2Addr;
    ppbConfig2Addr = (uint32_t *)((uint8_t *)&adc->ADCPPB1CONFIG2 + ppbNumber * DL_ADCPPBCONFIG2_STEP);
    *ppbConfig2Addr =
        (*ppbConfig2Addr & ~(ADC_ADCPPB1CONFIG2_SYNCINSEL_MASK)) | (syncInSrc << ADC_ADCPPB1CONFIG2_SYNCINSEL_OFS);
}

/**
 * @brief Reads the oversampled partial sum from the PPB
 *
 * Each time a new result propagates through the PPB signal chain and latches into ADCPPB{#}RESULT,
 * the result is subsequently accumulated into ADCPPB{#}PSUM register. This register is reset
 * when either a count-match event occurs (PCOUNT = LIMIT) or PPB{#} receives a sync event.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 *
 * @return Oversampling Partial Sum (16 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_readPPBPSum(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber)
{
    volatile uint32_t *ppbpSumAddr;
    ppbpSumAddr = (uint32_t *)((uint8_t *)&adc->ADCPPB1PSUM + ppbNumber * DL_ADCPPBSUM_STEP);
    return (*ppbpSumAddr & ADC_ADCPPB1PSUM_PSUM_MASK);
}

/**
 * @brief Sets end SOC number of last enabled sequence
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  socNumber is the end SOC number of last enabled sequencer
 */
__STATIC_INLINE void DL_ADC_setSeqEndSOC(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber)
{
    adc->ADCSEQCTL = (adc->ADCSEQCTL & ~(ADC_ADCSEQCTL_SEQEND_MASK)) | socNumber;
}

/**
 * @brief Sets SOC sequence preempt and restart setting
 *
 * This API selects the sequencer whether to preempt and restart aborted Seqeunce.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  seqPreempt selects whether to preempt and restart aborted Seqeunce or not
 */
__STATIC_INLINE void DL_ADC_setSeqPreemptMode(ADC_Regs *adc, DL_ADC_SEQ_PREEMPT seqPreempt)
{
    adc->ADCSEQCTL = (adc->ADCSEQCTL & ~(ADC_ADCSEQCTL_SEQPREEMPT_MASK)) | (seqPreempt << ADC_ADCSEQCTL_SEQPREEMPT_OFS);
}

/**
 * @brief Sets up the sequencer configurations
 *
 * This API configures the sample window, trigger source and beginning SOC number of the sequencer.
 *
 * The sample window is the acquisition window duration in SYSCLK cycles. The selected duration
 * must be at least as long as one ADCCLK cycle. Also, the datasheet will specify a minimum window
 * duration requirement in nanoseconds. The sample window value is calculated based on the combination
 * of ACQPS[7:6] and ACQPS[5:0], where ACQPS[7:6] determines scale and ACQPS[7:6] determines offset.
 * If ACQPS[7:6] value is:
 * "00" ->  sample window = ACQPS[5:0] + 1 sysclk cycles
 * "01" ->  sample window = 64 + ((ACQPS[5:0] +1) * 2) sysclk cycles
 * "10" ->  sample window = 192 + ((ACQPS[5:0] +1) * 4) sysclk cycles
 * "11" ->  sample window = 448 + ((ACQPS[5:0] +1) * 16) sysclk cycles
 * Based on the sampleWindow corresponding ACQPS value will be calculated and configured in ADCSOCxCTL register.
 *
 * The trigger source specifies the event that causes the SOC such as software, a timer interrupt, an MCPWM event
 * or an ADC interrupt. Based on the trigger, the SOCx flag in the ADCSOCFLG1 register will be set to initiate
 * a conversion to start once priority is given to it.
 *
 * The socStartNumber parameter specifies the which SOC number is the beginning SOC of the sequencer.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 * @param[in]  sampleWindow is acquisition window duration
 * @param[in]  trigger the source that will cause the SOC
 * @param[in]  socStartNumber is the beginning SOC of the sequencer
 */
__STATIC_INLINE void DL_ADC_setupSequencer(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber, uint32_t sampleWindow,
                                           DL_ADC_TRIGGER trigger, DL_ADC_SOC_NUMBER socStartNumber)
{
    uint32_t           ACQPS;
    uint32_t           mask;
    volatile uint32_t *seqConfigAddr;

    ASSERT(sampleWindow >= DL_SAMPLEWINDOW_MIN && sampleWindow <= DL_SAMPLEWINDOW_MAX);

    mask = (ADC_ADCSEQ1CONFIG_ACQPS_MASK | ADC_ADCSEQ1CONFIG_SEQSTART_MASK | ADC_ADCSEQ1CONFIG_TRIGSEL_MASK);

    if (sampleWindow > 448UL)
    {
        if ((sampleWindow % 16) != 0)
        {
            sampleWindow = sampleWindow + (16 - (sampleWindow % 16));
        }
        ACQPS = (3 << 6UL) | (((sampleWindow - 448UL) >> 4UL) - 1UL);
    }
    else if (sampleWindow > 192UL)
    {
        if ((sampleWindow % 4) != 0)
        {
            sampleWindow = sampleWindow + (4 - (sampleWindow % 4));
        }
        ACQPS = (2 << 6UL) | (((sampleWindow - 192UL) >> 2UL) - 1UL);
    }
    else if (sampleWindow > 64UL)
    {
        sampleWindow = sampleWindow + (sampleWindow % 2);
        ACQPS        = (1 << 6UL) | (((sampleWindow - 64UL) >> 1UL) - 1UL);
    }
    else
    {
        ACQPS = sampleWindow - 1UL;
    }

    seqConfigAddr  = (uint32_t *)((uint8_t *)&adc->ADCSEQ1CONFIG + seqNumber * DL_ADCSEQCONFIG_STEP);
    *seqConfigAddr = (*seqConfigAddr & ~(mask)) | ACQPS | (socStartNumber << ADC_ADCSEQ1CONFIG_SEQSTART_OFS) |
                     (trigger << ADC_ADCSEQ1CONFIG_TRIGSEL_OFS);
}

/**
 * @brief Enables the sequencer
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 */
__STATIC_INLINE void DL_ADC_enableSequencer(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber)
{
    volatile uint32_t *seqConfigAddr;
    seqConfigAddr   = (uint32_t *)((uint8_t *)&adc->ADCSEQ1CONFIG + seqNumber * DL_ADCSEQCONFIG_STEP);
    *seqConfigAddr |= ADC_ADCSEQ1CONFIG_SEQENABLE_MASK;
}

/**
 * @brief Disables the sequencer
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 */
__STATIC_INLINE void DL_ADC_disableSequencer(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber)
{
    volatile uint32_t *seqConfigAddr;
    seqConfigAddr   = (uint32_t *)((uint8_t *)&adc->ADCSEQ1CONFIG + seqNumber * DL_ADCSEQCONFIG_STEP);
    *seqConfigAddr &= ~ADC_ADCSEQ1CONFIG_SEQENABLE_MASK;
}

/**
 * @brief Enables the sample capacitor reset
 *
 * This API enables the sample capacitor reset after each conversion.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 */
__STATIC_INLINE void DL_ADC_enableSampleCapReset(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber)
{
    volatile uint32_t *seqConfigAddr;
    seqConfigAddr   = (uint32_t *)((uint8_t *)&adc->ADCSEQ1CONFIG + seqNumber * DL_ADCSEQCONFIG_STEP);
    *seqConfigAddr &= ~ADC_ADCSEQ1CONFIG_SAMPCAPRESETDISABLE_MASK;
}

/**
 * @brief Disables the sample capacitor reset
 *
 * This API disables the sample capacitor reset after each conversion
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 */
__STATIC_INLINE void DL_ADC_disableSampleCapReset(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber)
{
    volatile uint32_t *seqConfigAddr;
    seqConfigAddr   = (uint32_t *)((uint8_t *)&adc->ADCSEQ1CONFIG + seqNumber * DL_ADCSEQCONFIG_STEP);
    *seqConfigAddr |= ADC_ADCSEQ1CONFIG_SAMPCAPRESETDISABLE_MASK;
}

/**
 * @brief Selects the sample capacitor reset value
 *
 * This API sets the sample capacitor to reset to either Vrefhi/2 or Vreflo after each conversion.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 * @param[in]  capResetVal is used to select sample cap reset to either vrefhi/2 or vreflo
 */
__STATIC_INLINE void DL_ADC_selectSampleCAPResetValue(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber,
                                                      DL_ADC_SAMPLE_CAP_RESET_SELECT capResetVal)
{
    volatile uint32_t *seqConfigAddr;
    seqConfigAddr  = (uint32_t *)((uint8_t *)&adc->ADCSEQ1CONFIG + seqNumber * DL_ADCSEQCONFIG_STEP);
    *seqConfigAddr = (*seqConfigAddr & ~(ADC_ADCSEQ1CONFIG_SAMPCAPRESETSEL_MASK)) |
                     ((uint32_t)capResetVal << ADC_ADCSEQ1CONFIG_SAMPCAPRESETSEL_OFS);
}

/**
 * @brief Forces a trigger to sequencer
 *
 * This API forces a trigger to sequencer regardless of the value of
 * hardware trigger.
 *
 * @param[in]  adc Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 */
__STATIC_INLINE void DL_ADC_forceSequencer(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber)
{
    volatile uint32_t *seqConfigAddr;
    seqConfigAddr   = (uint32_t *)((uint8_t *)&adc->ADCSEQ1CONFIG + seqNumber * DL_ADCSEQCONFIG_STEP);
    *seqConfigAddr |= ADC_ADCSEQ1CONFIG_SEQSWFRC_MASK;
}

/**
 * @brief Reads the 12-bit ADC result
 *
 * This API returns the ADC conversion result. If the oversampling is enabled, the API will returns the
 * Final SUM of the specified number of samples.
 *
 * @param[in]  adcResult Pointer to the register overlay for the peripheral
 * @param[in]  socNumber is the SOC number of the result
 *
 * @return     ADC conversion result (16 bit value)
 */
__STATIC_INLINE uint16_t DL_ADC_readResult(ADC_RESULT_Regs *adcResult, DL_ADC_SOC_NUMBER socNumber)
{
    volatile uint16_t *resultAddr;
    resultAddr = (uint16_t *)((uint8_t *)&adcResult->ADCRESULT0 + socNumber * DL_ADCRESULT_STEP);
    return (*resultAddr & ADC_ADCRESULT0_RESULT_MASK);
}

/**
 * @brief Reads the processed conversion result from the PPB
 *
 * This API returns the processed conversion result. The results are available 1 SYSCLK
 * cycle after the associated ADCRESULT is available, unless multiple PPBs point to the same SOC.
 * In the case of multiple PPBs associated with the same SOC, the lowest numbered PPB's result
 * will be availble 1 SYSCLK cycle after the associated ADCRESULT and subsequent results
 * (in order from lowest numbered PPB to highest) will each become available
 * every 2-3 SYSCLK cycles.
 *
 * @param[in]  adcResult Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 *
 * @return     The signed 13-bit PPB result
 */
__STATIC_INLINE uint32_t DL_ADC_readPPBResult(ADC_RESULT_Regs *adcResult, DL_ADC_PPB_NUMBER ppbNumber)
{
    volatile uint32_t *ppbResultAddr;
    ppbResultAddr = (uint32_t *)((uint8_t *)&adcResult->ADCPPB1RESULT + ppbNumber * DL_ADCPPBRESULT_STEP);
    return (*ppbResultAddr & ADC_ADCPPB1RESULT_PPBRESULT_MASK);
}

/**
 * @brief Returns the oversampling final sum result
 *
 * This API returns the processed sum of results. The result is available 1 SYSCLK
 * cycle after the associated ADCPPBRESULT is available. This will be 2 SYSCLK cycles
 * after the associated ADCRESULT is available, unless multiple PPBs point to the same SOC.
 *
 * @param[in]  adcResult Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 *
 * @return     The signed 16-bit final oversampling sum result
 */
__STATIC_INLINE uint32_t DL_ADC_readPPBSum(ADC_RESULT_Regs *adcResult, DL_ADC_PPB_NUMBER ppbNumber)
{
    volatile uint32_t *ppbSumAddr;
    ppbSumAddr = (uint32_t *)((uint8_t *)&adcResult->ADCPPB1SUM + ppbNumber * DL_ADCPPBSUM_STEP);
    return (*ppbSumAddr & ADC_ADCPPB1SUM_SUM_MASK);
}

/**
 * @brief Returns the oversampling final count.
 *
 * This API returns the processed final count value. The result is available 1 SYSCLK
 * cycle after the associated ADCPPBRESULT is available. This will be 2 SYSCLK cycles
 * after the associated ADCRESULT is available, unless multiple PPBs point to the same SOC.
 *
 * @param[in]  adcResult Pointer to the register overlay for the peripheral
 * @param[in]  ppbNumber is the number of the post-processing block
 *
 * @return     The signed 4-bit final oversampling count value
 */
__STATIC_INLINE uint32_t DL_ADC_readPPBCount(ADC_RESULT_Regs *adcResult, DL_ADC_PPB_NUMBER ppbNumber)
{
    volatile uint32_t *ppbCountAddr;
    ppbCountAddr = (uint32_t *)((uint8_t *)&adcResult->ADCPPB1COUNT + ppbNumber * DL_ADCPPBCOUNT_STEP);
    return (*ppbCountAddr & ADC_ADCPPB1COUNT_COUNT_MASK);
}

/**
 * @brief Returns 32-bit FIFO result containing a pair of conversion results.
 *
 * This API returns the conversion result of all SOCs associated with the sequencer
 * in a sequential manner through FIFO mode. Since the Result registers are maximum 16-bits wide,
 * every read will return RESULT corresponding to 2 consecutive SOCs. LSB 16-bits [15:0] will contain
 * odd results {1,3,5,7...}, and MSB 16-bits [31:16] will contain even results {2,4,6,8...}. If odd number
 * of SOCs are associated with a sequencer, final read will have 16’h0 in the MSB 16-bits [31:16].
 * For Example, if SEQ1 – Start: SOC0, End: SOC2
 * First read will return SOC0’s result in LSB 16-bits [15:0] and soc1’s result in MSB 16-bits [31:16]
 * Second read will return SOC2’s result in LSB 16-bits [15:0] and 16'h0 in MSB 16-bits [31:16].
 *
 * @param[in]  adcResult Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 *
 * @return     FIFO result consisting of 2 consequtive conversion results (32 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_readSeqFIFOResult(ADC_RESULT_Regs *adcResult, DL_ADC_SEQ_NUMBER seqNumber)
{
    volatile uint32_t *seqResultAddr;
    seqResultAddr = (uint32_t *)((uint8_t *)&adcResult->ADCSEQ1FIFORESULT + seqNumber * DL_ADCSEQ_FIFORESULT_STEP);
    return (*seqResultAddr & ADC_ADCSEQ1FIFORESULT_SEQFIFORESULT_MASK);
}

/**
 * @brief Returns the status of FIFO conversions for a given sequencer
 *
 * This API can be used to check if conversion from all the SOCs associated with the Sequencer are
 * complete and result is available to be read.
 *
 * @param[in]  adcResult Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 *
 * @return     true if conversion from all the SOCs associated with the Sequencer are complete and result is available
 * to be read
 * @return     false if all conversions associated with the current Sequencer are NOT complete.
 */
__STATIC_INLINE bool DL_ADC_isSeqFIFOValid(ADC_RESULT_Regs *adcResult, DL_ADC_SEQ_NUMBER seqNumber)
{
    volatile uint32_t *seqFIFOStatus;
    seqFIFOStatus = (uint32_t *)((uint8_t *)&adcResult->ADCSEQ1FIFOSTATUS + seqNumber * DL_ADCSEQ_FIFOSTATUS_STEP);
    return ((*seqFIFOStatus & ADC_ADCSEQ1FIFOSTATUS_SEQFIFOVALID_MASK) == ADC_ADCSEQ1FIFOSTATUS_SEQFIFOVALID_MASK);
}

/**
 * @brief Returns the number of pending reads in the FIFO
 *
 * @note       -This field is only updated when after the last byte of ADCSEQ{#}FIFORESULT is read.
               -The Pending read information will not be updated for debug reads.
               -Once all the data in the FIFO has been read, FIFO will wrap back. Subsequent reads
                will read from the beginning of the FIFO.
 *
 * @param[in]  adcResult Pointer to the register overlay for the peripheral
 * @param[in]  seqNumber is the sequencer number
 *
 * @return     number of pending reads (4 bit value)
 */
__STATIC_INLINE uint32_t DL_ADC_getPendingReads(ADC_RESULT_Regs *adcResult, DL_ADC_SEQ_NUMBER seqNumber)
{
    volatile uint32_t *seqFIFOStatus;
    seqFIFOStatus = (uint32_t *)((uint8_t *)&adcResult->ADCSEQ1FIFOSTATUS + seqNumber * DL_ADCSEQ_FIFOSTATUS_STEP);
    return ((*seqFIFOStatus & ADC_ADCSEQ1FIFOSTATUS_SEQFIFOPENDREAD_MASK) >> ADC_ADCSEQ1FIFOSTATUS_SEQFIFOPENDREAD_OFS);
}

/**
 * @brief Initializes the ADC configuration parameters.
 *
 * This function initializes all the parameters of the ADC configuration
 * structure to their default values.
 *
 * @param[in,out] config Pointer to the ADC configuration structure.
 */

void DL_ADC_initParamsSetDefault(DL_ADC_Config *config);

/**
 * @brief Initializes the ADC module
 *
 * This function configures the ADC module according to the provided configuration.
 *
 * @param adc Pointer to the ADC register overlay
 * @param config Pointer to the ADC configuration structure
 */
void DL_ADC_init(ADC_Regs *adc, DL_ADC_Config *config);

/**
 * @brief Initializes the SOC submodule of ADC
 *
 * This function configures the SOC submodule according to the provided configuration.
 *
 * @param adc Pointer to the ADC register overlay
 * @param socNumber SOC number
 * @param socConfig Pointer to the SOC configurations structure.
 */
void DL_ADC_socInit(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber, DL_ADC_SocConfig *socConfig);

/**
 * @brief Initializes the PPB submodule of ADC
 *
 * This function configures the PPB submodule according to the provided configuration.
 *
 * @param adc Pointer to the ADC register overlay
 * @param ppbNumber PPB number
 * @param ppbConfig Pointer to the PPB configurations structure.
 */
void DL_ADC_ppbInit(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, DL_ADC_PpbConfig *ppbConfig);

/**
 * @brief Initializes the interrupt block submodule of ADC
 *
 * This function configures the interrupt block submodule according to the provided configuration.
 *
 * @param adc Pointer to the ADC register overlay
 * @param intNumber Interrupt block number
 * @param intNConfig Pointer to the interrupt block configurations structure.
 */
void DL_ADC_interruptInit(ADC_Regs *adc, DL_ADC_INT_NUMBER intNumber, DL_ADC_IntNConfig *intNConfig);

/**
 * @brief Initializes the DMA interrupt block submodule of ADC
 *
 * This function configures the DMA interrupt block submodule according to the provided configuration.
 *
 * @param adc Pointer to the ADC register overlay
 * @param dmaIntNumber DMA interrupt block number
 * @param dmaIntNConfig Pointer to the DMA interrupt block configurations structure.
 */
void DL_ADC_dmaInterruptInit(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER dmaIntNumber, DL_ADC_IntNConfig *dmaIntNConfig);

/**
 * @brief Initializes the sequencer submodule of ADC
 *
 * This function configures the sequencer submodule according to the provided configuration.
 *
 * @param adc Pointer to the ADC register overlay
 * @param seqNumber Sequencer number
 * @param seqNConfig Pointer to the sequencer configurations structure.
 */
void DL_ADC_sequencerInit(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber, DL_ADC_SeqNConfig *seqNConfig);

#ifdef __cplusplus
}
#endif

#endif /* DL_ADC_H */
       /** @}*/
