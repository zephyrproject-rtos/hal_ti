/******************************************************************************
 *  Filename:       adc.h
 *
 *  Description:    Prototypes and defines for the ADC API.
 *
 *  Copyright (c) 2024-2026 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef ti_devices_adc__include
#define ti_devices_adc__include

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup adc_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include "../inc/hw_adc.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
// Values
//
//*****************************************************************************

//! \brief Set ADC clock to system clock divided by 1
#define ADC_CLOCK_DIVIDER_1 ADC_CTL0_SCLKDIV_DIV_BY_1

//! \brief Set ADC clock to system clock divided by 2
#define ADC_CLOCK_DIVIDER_2 ADC_CTL0_SCLKDIV_DIV_BY_2

//! \brief Set ADC clock to system clock divided by 4
#define ADC_CLOCK_DIVIDER_4 ADC_CTL0_SCLKDIV_DIV_BY_4

//! \brief Set ADC clock to system clock divided by 8
#define ADC_CLOCK_DIVIDER_8 ADC_CTL0_SCLKDIV_DIV_BY_8

//! \brief Set ADC clock to system clock divided by 16
#define ADC_CLOCK_DIVIDER_16 ADC_CTL0_SCLKDIV_DIV_BY_16

//! \brief Set ADC clock to system clock divided by 24
#define ADC_CLOCK_DIVIDER_24 ADC_CTL0_SCLKDIV_DIV_BY_24

//! \brief Set ADC clock to system clock divided by 32
#define ADC_CLOCK_DIVIDER_32 ADC_CTL0_SCLKDIV_DIV_BY_32

//! \brief Set ADC clock to system clock divided by 48
#define ADC_CLOCK_DIVIDER_48 ADC_CTL0_SCLKDIV_DIV_BY_48

//! \brief Set ADC mode to single ended
#define ADC_MODE_SINGLE (0 << ADC_MEMCTL_0_MOD_S)

//! \brief Set ADC mode to differential
#define ADC_MODE_DIFFERENTIAL (1 << ADC_MEMCTL_0_MOD_S)

//! \brief Set ADC reference to internal, which is fixed to 1.4 V
#define ADC_INTERNAL_REFERENCE 0

//! \brief Set ADC reference to external, where VPP pin must be supplied with
//! 1.8 V
#define ADC_EXTERNAL_REFERENCE 1

//! \brief Set ADC reference to VDDA, which is fixed to 1.8 V
#define ADC_VDDA_REFERENCE 2

//! \brief Set ADC to measure from 0 to 3.3 V
#define ADC_FULL_SCALE_RANGE_0V0_3V3 0

//! \brief Set ADC to measure from 0.1 to 3.3 V
#define ADC_FULL_SCALE_RANGE_0V1_3V3 1

//! \brief Set ADC to measure from 0 to 3.2 V
#define ADC_FULL_SCALE_RANGE_0V0_3V2 2

//! \brief Set ADC to measure from 0 to 1.8 V
#define ADC_FULL_SCALE_RANGE_0V0_1V8 3

//! \brief ADC is powered down on completion of a conversion if there is no
//! pending trigger. To be used with \ref ADCSetPowerDownPolicy()
#define ADC_POWER_DOWN_POLICY_AUTO ADC_CTL0_PWRDN_AUTO

//! \brief ADC remains powered on as long as the power mode it set to manual.
//! To be used with \ref ADCSetPowerDownPolicy()
#define ADC_POWER_DOWN_POLICY_MANUAL ADC_CTL0_PWRDN_MANUAL

//! \brief Set ADC conversion sequence to repeat control registers defined by
//! start and stop address, as set by \ref ADCSetMemctlRange
#define ADC_SEQUENCE_REPEATSEQUENCE ADC_CTL1_CONSEQ_REPEATSEQUENCE

//! \brief Set ADC conversion sequence to repeat control register defined by
//! start as set by \ref ADCSetMemctlRange
#define ADC_SEQUENCE_REPEATSINGLE ADC_CTL1_CONSEQ_REPEATSINGLE

//! \brief Set ADC conversion sequence to a single pass of control registers
//! defined by start and stop address, as set by \ref ADCSetMemctlRange
#define ADC_SEQUENCE_SEQUENCE ADC_CTL1_CONSEQ_SEQUENCE

//! \brief Set ADC conversion sequence to do a single conversion of control
//! register defined by start, as set by \ref ADCSetMemctlRange
#define ADC_SEQUENCE_SINGLE ADC_CTL1_CONSEQ_SINGLE

//! \brief Sample duration is controlled by values set using
//! \ref ADCSetSampleDuration()
#define ADC_SAMPLE_MODE_AUTO ADC_CTL1_SAMPMODE_AUTO

//! \brief Sample phase is manually started using \ref ADCStartConversion() and
//! manually stopped using \ref ADCStopConversion()
//!
//! This can only be used when the trigger source selected by
//! \ref ADCSetTriggerSource() is \ref ADC_TRIGGER_SOURCE_SOFTWARE
#define ADC_SAMPLE_MODE_MANUAL ADC_CTL1_SAMPMODE_MANUAL

//! \brief The ADC trigger source is a hardware event.
//!
//! Can only be used when the sample mode configured using
//! \ref ADCSetSamplingMode() is \ref ADC_SAMPLE_MODE_AUTO
#define ADC_TRIGGER_SOURCE_EVENT ADC_CTL1_TRIGSRC_EVENT

//! \brief The ADC trigger source is software.
//!
//! \ref ADCStartConversion() is used to trigger the start of a conversion.
//! If the sampling mode configured using \ref ADCSetSamplingMode() is
//! \ref ADC_SAMPLE_MODE_MANUAL, then the sample phase must also be manually
//! stopped using \ref ADCStopConversion()
#define ADC_TRIGGER_SOURCE_SOFTWARE ADC_CTL1_TRIGSRC_SOFTWARE

//! \brief The next conversion is automatically started after the completion of
//! the previous conversion.
//!
//! This means that no trigger is needed to start the next conversion.
#define ADC_TRIGGER_POLICY_AUTO_NEXT ADC_MEMCTL_0_TRIG_AUTO_NEXT

//! \brief The next conversion requires a trigger
#define ADC_TRIGGER_POLICY_TRIGGER_NEXT ADC_MEMCTL_0_TRIG_TRIGGER_NEXT

//! \brief Result ready in memory result register 15
#define ADC_INT_MEMRES_15 ADC_INTEVT0BM_MEMRESIFG15

//! \brief Result ready in memory result register 14
#define ADC_INT_MEMRES_14 ADC_INTEVT0BM_MEMRESIFG14

//! \brief Result ready in memory result register 13
#define ADC_INT_MEMRES_13 ADC_INTEVT0BM_MEMRESIFG13

//! \brief Result ready in memory result register 12
#define ADC_INT_MEMRES_12 ADC_INTEVT0BM_MEMRESIFG12

//! \brief Result ready in memory result register 11
#define ADC_INT_MEMRES_11 ADC_INTEVT0BM_MEMRESIFG11

//! \brief Result ready in memory result register 10
#define ADC_INT_MEMRES_10 ADC_INTEVT0BM_MEMRESIFG10

//! \brief Result ready in memory result register 9
#define ADC_INT_MEMRES_09 ADC_INTEVT0BM_MEMRESIFG9

//! \brief Result ready in memory result register 8
#define ADC_INT_MEMRES_08 ADC_INTEVT0BM_MEMRESIFG8

//! \brief Result ready in memory result register 7
#define ADC_INT_MEMRES_07 ADC_INTEVT0BM_MEMRESIFG7

//! \brief Result ready in memory result register 6
#define ADC_INT_MEMRES_06 ADC_INTEVT0BM_MEMRESIFG6

//! \brief Result ready in memory result register 5
#define ADC_INT_MEMRES_05 ADC_INTEVT0BM_MEMRESIFG5

//! \brief Result ready in memory result register 4
#define ADC_INT_MEMRES_04 ADC_INTEVT0BM_MEMRESIFG4

//! \brief Result ready in memory result register 3
#define ADC_INT_MEMRES_03 ADC_INTEVT0BM_MEMRESIFG3

//! \brief Result ready in memory result register 2
#define ADC_INT_MEMRES_02 ADC_INTEVT0BM_MEMRESIFG2

//! \brief Result ready in memory result register 1
#define ADC_INT_MEMRES_01 ADC_INTEVT0BM_MEMRESIFG1

//! \brief Result ready in memory result register 0
#define ADC_INT_MEMRES_00 ADC_INTEVT0BM_MEMRESIFG0

//! \brief Conversion underflow
#define ADC_INT_UVIFG ADC_INTEVT0BM_UVIFG

//! \brief DMA transaction done
#define ADC_INT_DMADONE ADC_INTEVT0BM_DMADONE

//! \brief ADC result is inside window comparator range
#define ADC_INT_INIFG ADC_INTEVT0BM_INIFG

//! \brief ADC result is below window comparator range
#define ADC_INT_LOWIFG ADC_INTEVT0BM_LOFG

//! \brief ADC result is above window comparator range
#define ADC_INT_HIGHIFG ADC_INTEVT0BM_HIFG

//! \brief Sequence conversion timeout overflow
#define ADC_INT_TOVIFG ADC_INTEVT0BM_TOVIFG

//! \brief Conversion overflow
#define ADC_INT_OVIFG ADC_INTEVT0BM_OVIFG

//! \brief All interrupts
#define ADC_INT_ALL                                                                                        \
    (ADC_INT_OVIFG | ADC_INT_TOVIFG | ADC_INT_HIGHIFG | ADC_INT_LOWIFG | ADC_INT_INIFG | ADC_INT_DMADONE | \
     ADC_INT_UVIFG | ADC_INT_MEMRES_00 | ADC_INT_MEMRES_01 | ADC_INT_MEMRES_02 | ADC_INT_MEMRES_03 |       \
     ADC_INT_MEMRES_04 | ADC_INT_MEMRES_05 | ADC_INT_MEMRES_06 | ADC_INT_MEMRES_07 | ADC_INT_MEMRES_08 |   \
     ADC_INT_MEMRES_09 | ADC_INT_MEMRES_10 | ADC_INT_MEMRES_11 | ADC_INT_MEMRES_12 | ADC_INT_MEMRES_13 |   \
     ADC_INT_MEMRES_14 | ADC_INT_MEMRES_15)

//*****************************************************************************
//
//! \name ADC sample clock sources
//! \{
//
//*****************************************************************************
//! Sample clock gated
#define ADC_SAMPLE_CLK_NONE            0
//! SOC clock
#define ADC_SAMPLE_CLK_SOC_CLK         1
//! HFXT clock
#define ADC_SAMPLE_CLK_HFXT            2
//! SOC PLL CLOCK DIV
#define ADC_SAMPLE_CLK_SOC_PLL_CLK_DIV 3
//! \}

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Sets the clock-divider value, and sample duration
//!
//! This function sets the clock divider, which determines the ADC clock,
//! derived from the system clock, and sets the duration of a sample in
//! ADC-clock cycles
//!
//! \param clkDiv is the clock divider value
//! - \ref ADC_CLOCK_DIVIDER_1
//! - \ref ADC_CLOCK_DIVIDER_2
//! - \ref ADC_CLOCK_DIVIDER_4
//! - \ref ADC_CLOCK_DIVIDER_8
//! - \ref ADC_CLOCK_DIVIDER_16
//! - \ref ADC_CLOCK_DIVIDER_24
//! - \ref ADC_CLOCK_DIVIDER_32
//! - \ref ADC_CLOCK_DIVIDER_48
//!
//! \param clkCycles is the duration of a sample, in ADC-clock cycles.
//! Valid range of input is [0, 16383]
//!
//! \note
//! The numerical value of clkDiv is not the actual divider value.
//! See the list of possible arguments and which divider value they represent.
//!
//! \note
//! The minimum sampling time for the ADC is 500 ns if using an external
//! reference source or 1000 ns if using an internal reference source. The
//! clock-divider and sample duration must be set accordingly to maintain this
//! requirement.
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetSampleDuration(uint32_t clkDiv, uint16_t clkCycles);

//*****************************************************************************
//
//! \brief Sets the ADC reference source and input channel
//!
//! This function sets the ADC reference and input channel. The control register
//! index that the settings are applied to must also be passed as a parameter
//!
//! \param reference Reference source used in conversion
//! - \ref ADC_INTERNAL_REFERENCE
//! - \ref ADC_VDDA_REFERENCE
//! - \ref ADC_EXTERNAL_REFERENCE
//!
//! \param channel Internal channels that can be muxed to ADC.
//! Channels 0-11 correspond to analog pins 0-11. See device data for more
//! information.
//!
//! \param fullScaleRange Select sample range of the ADC.
//! - \ref ADC_FULL_SCALE_RANGE_0V0_3V3
//! - \ref ADC_FULL_SCALE_RANGE_0V1_3V3
//! - \ref ADC_FULL_SCALE_RANGE_0V0_3V2
//! - \ref ADC_FULL_SCALE_RANGE_0V0_1V8
//!
//! \param index Index of which control register to write to. See device data
//! for valid indexes.
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetInput(uint32_t reference, uint8_t channel, uint8_t fullScaleRange, uint32_t index);

//*****************************************************************************
//
//! \brief Set start and stop control registers
//!
//! This function selects which control registers should be selected for a
//! conversion. Valid indexes are [0, 3]. For a single conversion, start and
//! stop should be set to the same.
//!
//! \param start the index of first control register used in sequence
//! \param stop the index of last control register used in sequence
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetMemctlRange(uint32_t start, uint32_t stop);

//*****************************************************************************
//
//! \brief Set power down policy
//!
//! This function sets the power down policy for the ADC.
//!
//! \param powerDownPolicy
//! - \ref ADC_POWER_DOWN_POLICY_MANUAL
//! - \ref ADC_POWER_DOWN_POLICY_AUTO
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetPowerDownPolicy(uint32_t powerDownPolicy);

//*****************************************************************************
//
//! \brief Set conversion sequence
//!
//! This function sets the sequence for ADC conversions. The actual sequence is
//! defined by \ref ADCSetMemctlRange. For a single conversion, start and stop
//! should be set to the same.
//!
//! \param sequence
//! - \ref ADC_SEQUENCE_REPEATSEQUENCE
//! - \ref ADC_SEQUENCE_REPEATSINGLE
//! - \ref ADC_SEQUENCE_SEQUENCE
//! - \ref ADC_SEQUENCE_SINGLE
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetSequence(uint32_t sequence);

//*****************************************************************************
//
//! \brief Set sampling clock source
//!
//! This function sets the source of the sample clock.
//!
//! \param clkSrc
//! - \ref ADC_SAMPLE_CLK_NONE
//! - \ref ADC_SAMPLE_CLK_SOC_CLK
//! - \ref ADC_SAMPLE_CLK_HFXT
//! - \ref ADC_SAMPLE_CLK_SOC_PLL_CLK_DIV
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetSamplingClk(uint32_t clkSrc);

//*****************************************************************************
//
//! \brief Set ADC sampling mode
//!
//! \param samplingMode
//! - \ref ADC_SAMPLE_MODE_MANUAL
//! - \ref ADC_SAMPLE_MODE_AUTO
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetSamplingMode(uint32_t samplingMode);

//*****************************************************************************
//
//! \brief Set ADC trigger source
//!
//! \param triggerSource
//! - \ref ADC_TRIGGER_SOURCE_SOFTWARE
//! - \ref ADC_TRIGGER_SOURCE_EVENT
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetTriggerSource(uint32_t triggerSource);

//*****************************************************************************
//
//! \brief Set ADC trigger policy
//!
//! This is not applicable when the sequence set by \ref ADCSetSequence() is
//! \ref ADC_SEQUENCE_SINGLE
//!
//! \param triggerPolicy
//! - \ref ADC_TRIGGER_POLICY_AUTO_NEXT
//! - \ref ADC_TRIGGER_POLICY_TRIGGER_NEXT
//!
//! \param index Index of which control register to write to. See device data
//!              for valid indexes.
//!
//! \return None
//
//*****************************************************************************
extern void ADCSetTriggerPolicy(uint32_t triggerPolicy, uint32_t index);

//*****************************************************************************
//
//! \brief Start conversion.
//!
//! Can only be used if the trigger source is set to
//! \ref ADC_TRIGGER_SOURCE_SOFTWARE using \ref ADCSetTriggerSource()
//!
//! \note It takes a minimum of 16 system-clock cycles for the BUSY-bit in the
//! STATUS register to go high after calling this function.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCStartConversion(void)
{
    HWREG(ADC_BASE + ADC_O_CTL1) |= ADC_CTL1_SC_START;
}

//*****************************************************************************
//
//! \brief Stop sample phase of a conversion.
//!
//! Only applicable if the trigger source is set to
//! \ref ADC_TRIGGER_SOURCE_SOFTWARE using \ref ADCSetTriggerSource() and if the
//! sampling mode is set to \ref ADC_SAMPLE_MODE_MANUAL using
//! \ref ADCSetSamplingMode().
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCStopConversion(void)
{
    HWREG(ADC_BASE + ADC_O_CTL1) &= ~ADC_CTL1_SC_M;
}

//*****************************************************************************
//
//! \brief Enable conversion
//!
//! This will enable ADC conversions. The ADC sequencer will wait for the
//! trigger configured using \ref ADCSetTriggerSource() before the first
//! conversion is started.
//!
//! If the trigger source has been configured to
//! \ref ADC_TRIGGER_SOURCE_SOFTWARE, then the conversion can be started using
//! \ref ADCStartConversion().
//!
//! \note While conversion is enabled, configuration of the ADC is not possible,
//! so all configurations must be done before enabling conversion.
//!
//! \sa ADCDisableConversion()
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCEnableConversion(void)
{
    HWREG(ADC_BASE + ADC_O_CTL0) |= ADC_CTL0_ENC_ON;
}

//*****************************************************************************
//
//! \brief Disable conversion
//!
//! This will disable ADC conversions. The current conversion will finish and
//! the result can be read out using \ref ADCReadResult() or
//! \ref ADCReadResultNonBlocking(). Any subsequent conversions in a sequence
//! will be aborted.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCDisableConversion(void)
{
    HWREG(ADC_BASE + ADC_O_CTL0) &= ~ADC_CTL0_ENC_M;
}

//*****************************************************************************
//
//! \brief Enable DMA trigger for data transfer.
//!
//! \note The DMA trigger is automatically cleared by hardware based on DMA done
//! signal at the end of data transfer. Software has to re-enable the DMA
//! trigger for ADC to generate DMA triggers after the DMA done signal.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCEnableDmaTrigger(void)
{
    HWREG(ADC_BASE + ADC_O_CTL2) |= ADC_CTL2_DMAEN_ENABLE;
}

//*****************************************************************************
//
//! \brief Disable DMA trigger for data transfer.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCDisableDmaTrigger(void)
{
    HWREG(ADC_BASE + ADC_O_CTL2) &= ~ADC_CTL2_DMAEN_M;
}

//*****************************************************************************
//
//! \brief Read conversion result from ADC
//!
//! This function blocks until a conversion is done, and returns data from the
//! given memory register. The index corresponds to the selected control
//! register used for the conversion
//!
//! \param index Index of which memory result register to read from
//!
//! \return Raw ADC conversion result
//
//*****************************************************************************
__STATIC_INLINE uint32_t ADCReadResult(uint32_t index)
{

    while (HWREG(ADC_BASE + ADC_O_STA) & ADC_STA_BUSY_ACTIVE) {}

    // Return data from result register
    return HWREG(ADC_BASE + ADC_O_MEMRES_0 + (4 * index));
}

//*****************************************************************************
//
//! \brief Check if ADC is busy
//!
//! This function returns whether the ADC is busy or not.
//!
//! \return ADC Busy status
//! true: ADC sampling or conversion is in progress.
//! false: No ADC sampling or conversion in progress.
//!
//! \note It takes a minimum of 9 system-clock cycles between writing to the
//! START-bit, and the BUSY-bit in the STATUS register going high
//
//*****************************************************************************
__STATIC_INLINE bool ADCIsBusy(void)
{

    if (HWREG(ADC_BASE + ADC_O_STA) & ADC_STA_BUSY_ACTIVE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//*****************************************************************************
//
//! \brief Read conversion result from ADC
//!
//! This function returns data from the given memory register without blocking.
//! The index corresponds to the selected control register used for the
//! conversion
//!
//! \param index Index of which memory result register to read from
//!
//! \return Raw ADC conversion result
//
//*****************************************************************************
__STATIC_INLINE uint32_t ADCReadResultNonBlocking(uint32_t index)
{
    // Return data from result register
    return HWREG(ADC_BASE + ADC_O_MEMRES_0 + (4 * index));
}

//*****************************************************************************
//
//! \brief Convert ADC code to microvolts
//!
//! This function converts an adjusted ADC code to microvolts
//!
//! \param adcCode Raw adjusted adc code
//!
//! \param fullScaleRange Select sample range of the ADC. The range should be
//! the same as the one configured for the sample using ADCSetInput.
//! - \ref ADC_FULL_SCALE_RANGE_0V0_3V3
//! - \ref ADC_FULL_SCALE_RANGE_0V1_3V3
//! - \ref ADC_FULL_SCALE_RANGE_0V0_3V2
//! - \ref ADC_FULL_SCALE_RANGE_0V0_1V8
//!
//! \return ADC result in microvolts. If the fullScaleRange is not one of the
//!         above, the result will always be 0.
//
//*****************************************************************************
extern uint32_t ADCValueToMicrovolts(uint32_t adcCode, uint32_t fullScaleRange);

//*****************************************************************************
//
//! \brief Enables individual ADC interrupt sources.
//!
//! This function enables the indicated ADC interrupt sources.
//!
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//! The parameter is the bitwise OR of any of the following:
//! - ADC_INT_MEMRES_N (\ref ADC_INT_MEMRES_00, \ref ADC_INT_MEMRES_01, etc)
//! - \ref ADC_INT_UVIFG
//! - \ref ADC_INT_DMADONE
//! - \ref ADC_INT_INIFG
//! - \ref ADC_INT_LOWIFG
//! - \ref ADC_INT_HIGHIFG
//! - \ref ADC_INT_TOVIFG
//! - \ref ADC_INT_OVIFG
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCEnableInterrupt(uint32_t intFlags)
{
    // Enable the specified interrupts.
    HWREG(ADC_BASE + ADC_O_INTEVT0BM) |= intFlags;
}

//*****************************************************************************
//
//! \brief Disables individual ADC interrupt sources.
//!
//! This function disables the indicated ADC interrupt sources.
//!
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//! The parameter is the bitwise OR of any of the following:
//! - ADC_INT_MEMRES_N (\ref ADC_INT_MEMRES_00, \ref ADC_INT_MEMRES_01, etc)
//! - \ref ADC_INT_UVIFG
//! - \ref ADC_INT_DMADONE
//! - \ref ADC_INT_INIFG
//! - \ref ADC_INT_LOWIFG
//! - \ref ADC_INT_HIGHIFG
//! - \ref ADC_INT_TOVIFG
//! - \ref ADC_INT_OVIFG
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCDisableInterrupt(uint32_t intFlags)
{
    // Disable the specified interrupts.
    HWREG(ADC_BASE + ADC_O_INTEVT0BM) &= ~(intFlags);
}

//*****************************************************************************
//
//! \brief Gets the current raw interrupt status.
//!
//! This function returns the raw interrupt status for the ADC
//!
//! \return Returns the current interrupt status, a bitwise OR of the following:
//! - ADC_INT_MEMRES_N (\ref ADC_INT_MEMRES_00, \ref ADC_INT_MEMRES_01, etc)
//! - \ref ADC_INT_UVIFG
//! - \ref ADC_INT_DMADONE
//! - \ref ADC_INT_INIFG
//! - \ref ADC_INT_LOWIFG
//! - \ref ADC_INT_HIGHIFG
//! - \ref ADC_INT_TOVIFG
//! - \ref ADC_INT_OVIFG
//
//*****************************************************************************
__STATIC_INLINE uint32_t ADCRawInterruptStatus(void)
{
    return (HWREG(ADC_BASE + ADC_O_INTEVT0RIS));
}

//*****************************************************************************
//
//! \brief Gets the current masked interrupt status.
//!
//! This function returns the masked interrupt status for the ADC
//!
//! \return Returns the current interrupt status, enumerated as a bit field of:
//! - ADC_INT_MEMRES_N (\ref ADC_INT_MEMRES_00, \ref ADC_INT_MEMRES_01, etc)
//! - \ref ADC_INT_UVIFG
//! - \ref ADC_INT_DMADONE
//! - \ref ADC_INT_INIFG
//! - \ref ADC_INT_LOWIFG
//! - \ref ADC_INT_HIGHIFG
//! - \ref ADC_INT_TOVIFG
//! - \ref ADC_INT_OVIFG
//
//*****************************************************************************
__STATIC_INLINE uint32_t ADCMaskedInterruptStatus(void)
{
    return (HWREG(ADC_BASE + ADC_O_INTEVT0MIS));
}

//*****************************************************************************
//
//! \brief Clears ADC interrupt sources.
//!
//! The specified ADC interrupt sources are cleared, so that they no longer
//! assert. This function must be called in the interrupt handler to keep the
//! interrupt from being triggered again immediately upon exit.
//!
//! \note Due to write buffers and synchronizers in the system it may take
//! several clock cycles from a register write clearing an event in a module and
//! until the event is actually cleared in the NVIC of the system CPU. It is
//! recommended to clear the event source early in the interrupt service routine
//! (ISR) to allow the event clear to propagate to the NVIC before returning
//! from the ISR.
//! At the same time, an early event clear allows new events of the same type to
//! be pended instead of ignored if the event is cleared later in the ISR.
//! It is the responsibility of the programmer to make sure that enough time has
//! passed before returning from the ISR to avoid false re-triggering of the
//! cleared event. A simple, although not necessarily optimal, way of clearing
//! an event before returning from the ISR is:
//! -# Write to clear event (buffered write).
//! -# Dummy read from the event source module (making sure the write has
//! propagated).
//! -# Wait two system CPU clock cycles, either user code or two NOPs (allowing
//! cleared event to propagate through any synchronizers).
//!
//! \param intFlags is a bit mask of the interrupt sources to be cleared. The
//! parameter is the bitwise OR of any of the following:
//! - ADC_INT_MEMRES_N (\ref ADC_INT_MEMRES_00, \ref ADC_INT_MEMRES_01, etc)
//! - \ref ADC_INT_UVIFG
//! - \ref ADC_INT_DMADONE
//! - \ref ADC_INT_INIFG
//! - \ref ADC_INT_LOWIFG
//! - \ref ADC_INT_HIGHIFG
//! - \ref ADC_INT_TOVIFG
//! - \ref ADC_INT_OVIFG
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void ADCClearInterrupt(uint32_t intFlags)
{
    // Clear the requested interrupt sources
    HWREG(ADC_BASE + ADC_O_INTEVT0CLR) = intFlags;
}

//*****************************************************************************
//
//! \brief Store trim values
//!
//! The ADC MMRs do not retain their values when the system enters sleep mode.
//! Therefore, it is necessary to store the trim values from the ADC MMRs before
//! entering sleep. This function performs the storing process to preserve the
//! trim values.
//!
//! \note This function must be called before entering sleep.
//!
//! \pre ADCRestoreTrims() is called when exiting sleep.
//!
//! \return None
//
//*****************************************************************************
extern void ADCStoreTrims(void);

//*****************************************************************************
//
//! \brief Restore trim values
//!
//! The ADC MMRs do not retain their values when the system enters sleep mode.
//! Therefore, it is necessary to restore the trim values in the ADC MMRs upon
//! waking up from sleep. This function performs that restoration process.
//!
//! \note This function must be called when exiting sleep.
//!
//! \pre ADCStoreTrims() is called before entering sleep.
//!
//! \return None
//
//*****************************************************************************
extern void ADCRestoreTrims(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
//! Close the Doxygen group.
//! @}
//! @}
//
//*****************************************************************************

#endif // ti_devices_adc__include
