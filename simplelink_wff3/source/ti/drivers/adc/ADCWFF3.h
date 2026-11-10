/*
 * Copyright (c) 2024-2025, Texas Instruments Incorporated
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
/*!****************************************************************************
 *  @file       ADCWFF3.h
 *  @brief      ADC driver implementation for the ADC peripheral on Wi-Fi F3
 *              devices
 *
 *  This ADC driver implementation is designed to operate on a ADC peripheral
 *  for Wi-Fi F3 devices.
 *
 *  Refer to @ref ADC.h for a complete description of APIs & example of use.
 *
 * # Limitations #
 *
 * ## #ADC_Params Attributes Limitations ##
 *
 * Some attributes in the #ADC_Params structure have a limited set of supported
 * values. These limitations are described below:
 *  - #ADC_Params.isProtected
 *    - Must be true. If this is false, #ADC_open() will fail and return NULL.
 *
 ******************************************************************************
 */
#ifndef ti_drivers_adc_ADCWFF3__include
#define ti_drivers_adc_ADCWFF3__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/ADC.h>
#include <ti/drivers/Power.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/adc.h)

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief  Specifies the source of the ADC reference voltage
 *
 *  @note   The actual reference values are slightly different for each device
 *          and are higher than the values specified above. This gain is saved
 *          in the eFuse. The function #ADC_convertToMicroVolts() must be used
 *          to derive actual voltage values. Do not attempt to compare raw
 *          values between devices or derive a voltage from them yourself. The
 *          results of doing so will only be approximately correct.
 *
 *  @warning    Refer to the datasheet to make sure the input voltage to the ADC
 *              never exceeds the specified limits.
 */
typedef enum
{
    ADCWFF3_INTERNAL_REFERENCE = ADC_INTERNAL_REFERENCE,
    ADCWFF3_VDDA_REFERENCE     = ADC_VDDA_REFERENCE,
    ADCWFF3_EXTERNAL_REFERENCE = ADC_EXTERNAL_REFERENCE
} ADCWFF3_ReferenceSource;

/*!
 *  @brief ADC sample clock source
 *
 *  This sets the sampling clock source.
 */
typedef enum
{
    /*! System-on-Chip clock, 80 Mhz. */
    ADCWFF3_SAMPLE_CLK_SOC_CLK         = ADC_SAMPLE_CLK_SOC_CLK,
    /*! High-Frequency Crystal clock, 40 Mhz. */
    ADCWFF3_SAMPLE_CLK_HFXT            = ADC_SAMPLE_CLK_HFXT,
    /*! Divided Phase-Locked Loop clock, 80 Mhz. */
    ADCWFF3_SAMPLE_CLK_SOC_PLL_CLK_DIV = ADC_SAMPLE_CLK_SOC_PLL_CLK_DIV
} ADCWFF3_SampleClockSource;

/*!
 *  @brief ADC clock-divider
 *
 *  This sets the sample clock divider value.
 */
typedef enum
{
    ADCWFF3_CLKDIV_1  = ADC_CLOCK_DIVIDER_1,
    ADCWFF3_CLKDIV_2  = ADC_CLOCK_DIVIDER_2,
    ADCWFF3_CLKDIV_4  = ADC_CLOCK_DIVIDER_4,
    ADCWFF3_CLKDIV_8  = ADC_CLOCK_DIVIDER_8,
    ADCWFF3_CLKDIV_16 = ADC_CLOCK_DIVIDER_16,
    ADCWFF3_CLKDIV_24 = ADC_CLOCK_DIVIDER_24,
    ADCWFF3_CLKDIV_32 = ADC_CLOCK_DIVIDER_32,
    ADCWFF3_CLKDIV_48 = ADC_CLOCK_DIVIDER_48
} ADCWFF3_ClockDivider;

/*!
 *  @brief ADC full scale range
 *
 *  This sets the voltage range the ADC can measure
 */
typedef enum
{
    ADCWFF3_FULL_SCALE_RANGE_0V0_3V3 = ADC_FULL_SCALE_RANGE_0V0_3V3,
    ADCWFF3_FULL_SCALE_RANGE_0V1_3V3 = ADC_FULL_SCALE_RANGE_0V1_3V3,
    ADCWFF3_FULL_SCALE_RANGE_0V0_3V2 = ADC_FULL_SCALE_RANGE_0V0_3V2,
    ADCWFF3_FULL_SCALE_RANGE_0V0_1V8 = ADC_FULL_SCALE_RANGE_0V0_1V8
} ADCWFF3_FullScaleRange;

/* ADC function table pointer */
extern const ADC_FxnTable ADCWFF3_fxnTable;

/*!
 *  @brief  ADCWFF3 Hardware attributes
 *  These fields are used by driverlib APIs and therefore must be populated by
 *  driverlib macro definitions.
 *
 */
typedef struct
{
    /*! DIO that the ADC input is routed to. */
    uint8_t adcInputDIO;
    /*! Internal signal routed to ADC. The channel number is determined by the selected DIO. */
    uint8_t internalChannel;
    /*! Reference source for the ADC to use. */
    ADCWFF3_ReferenceSource refSource;
    /*! Time the ADC spends sampling, in divided sampling clock cycles. Allowed range: 0 - 16383. */
    uint16_t samplingDuration;
    /*! ADC sample clock divider value. */
    ADCWFF3_ClockDivider adcClkDivider;
    /*! ADC sampling clock source. */
    ADCWFF3_SampleClockSource sampleClkSrc;
    /*! ADC full scale range. */
    ADCWFF3_FullScaleRange fullScaleRange;

} ADCWFF3_HWAttrs;

/*!
 *  @brief  ADCWFF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    /*! Flag if the instance is in use */
    bool isOpen;
    /*! For reconfiguration after Sleep */
    Power_NotifyObj postNotify;
} ADCWFF3_Object;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_adc_ADCWFF3__include */
