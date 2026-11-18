/******************************************************************************
 *  Filename:       adc.c
 *
 *  Description:    Driver for the ADC.
 *
 *  Copyright (c) 2024-2025 Texas Instruments Incorporated
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

#include "adc.h"
#include "debug.h"

// Set ADC maximum value based on fixed 12 bit unsigned resolution
#define ADC_MAX_CODE 0xFFF

// ADC offset trim
#define ADC_CTRL_FSBIT0 0x000

// ADC refbuf trim
#define ADC_CTRL_FSBIT1 0x20

//*****************************************************************************
//
// Sets the clock-divider value, and sample duration
//
//*****************************************************************************
void ADCSetSampleDuration(uint32_t clkDiv, uint16_t clkCycles)
{
    uint32_t tempCtl;

    ASSERT((ADC_CTL0_SCLKDIV_M & clkDiv) == clkDiv);
    ASSERT((ADC_SCOMP0_SMP_M & clkCycles) == clkCycles);

    // Read current control register
    tempCtl = HWREG(ADC_BASE + ADC_O_CTL0);

    // Clear clk-div bits
    tempCtl &= ~(ADC_CTL0_SCLKDIV_M);

    // Set clk-div bits from argument
    tempCtl |= clkDiv;

    // Write back control register
    HWREG(ADC_BASE + ADC_O_CTL0) = tempCtl;

    // write sample-duration
    HWREG(ADC_BASE + ADC_O_SCOMP0) = clkCycles;
}

//*****************************************************************************
//
// Sets the ADC reference source and input channel
//
//*****************************************************************************
void ADCSetInput(uint32_t reference, uint8_t channel, uint8_t fullScaleRange, uint32_t index)
{
    uint32_t tempCtl;
    uint32_t tempModCtl;
    // Set internal reference to disabled by default
    uint32_t refCfg = ADC_REFCFG_REFEN_DISABLE;

    ASSERT(reference == ADC_INTERNAL_REFERENCE || reference == ADC_EXTERNAL_REFERENCE ||
           reference == ADC_VDDA_REFERENCE);
    ASSERT(channel < (ADC_MEMCTL_0_CHANSEL_M >> ADC_MEMCTL_0_CHANSEL_S));
    ASSERT(fullScaleRange <= ADC_FULL_SCALE_RANGE_0V0_1V8);

    // Read current control register
    tempCtl = HWREG(ADC_BASE + ADC_O_MEMCTL_0 + (4 * index));

    // Clear full scale range (3.3V range), reference, channel and mode bits
    tempCtl &= ~(ADC_MEMCTL_0_FSR_M | ADC_MEMCTL_0_VRSEL_M | ADC_MEMCTL_0_CHANSEL_M | ADC_MEMCTL_0_MOD_M);

    // Set channel
    tempCtl |= channel << ADC_MEMCTL_0_CHANSEL_S;

    // Set single ended mode
    tempCtl |= ADC_MODE_SINGLE;

    // Set internal reference, if selected
    if (reference == ADC_INTERNAL_REFERENCE)
    {
        // Enable internal reference, set bias current and set reference voltage
        // level
        refCfg = ADC_REFCFG_IBPROG_VAL0 | ADC_REFCFG_REFEN_ENABLE | ADC_REFCFG_REFVSEL_V1P4;

        // Set mem-ctrl register to use internal reference
        tempCtl |= ADC_MEMCTL_0_VRSEL_INTREF;
    }
    else if (reference == ADC_EXTERNAL_REFERENCE)
    {
        // Set external reference
        tempCtl |= ADC_MEMCTL_0_VRSEL_EXTREF;
    }

    // Read current mode control register
    tempModCtl = HWREG(ADC_BASE + ADC_O_MODCTL);
    // Clear scale select and voltage reference range bits.
    tempModCtl &= ~(ADC_MODCTL_SCASEL_M | ADC_MODCTL_VREFRAN_M);

    // Set full scale range, scale select and voltage reference range bits to
    // modify the full scale range.
    switch (fullScaleRange)
    {
        case ADC_FULL_SCALE_RANGE_0V0_3V3:
            // Set scale select bit to get (0.0-3.3 V)
            tempModCtl |= ADC_MODCTL_SCASEL_M;
            break;
        case ADC_FULL_SCALE_RANGE_0V1_3V3:
            // Set reference voltage bit to get (0.1-3.3 V)
            tempModCtl |= ADC_MODCTL_VREFRAN_M;
            break;
        case ADC_FULL_SCALE_RANGE_0V0_1V8:
            // Set FSR bit to get (0.0-1.8 V)
            tempCtl |= ADC_MEMCTL_0_FSR_M;
            break;
        case ADC_FULL_SCALE_RANGE_0V0_3V2:
            // Default range when all bits are cleared
        default:
            break;
    }

    // Write back control registers
    HWREG(ADC_BASE + ADC_O_MEMCTL_0 + (4 * index)) = tempCtl;
    HWREG(ADC_BASE + ADC_O_REFCFG)                 = refCfg;
    HWREG(ADC_BASE + ADC_O_MODCTL)                 = tempModCtl;
}

//*****************************************************************************
//
// Set the ADC sampling mode
//
//*****************************************************************************
void ADCSetSamplingMode(uint32_t samplingMode)
{
    uint32_t tempCtl;

    ASSERT((ADC_CTL1_SAMPMODE_M & samplingMode) == samplingMode);

    // Read current control register
    tempCtl = HWREG(ADC_BASE + ADC_O_CTL1);

    // Clear sampling mode related fields
    tempCtl &= ~(ADC_CTL1_SAMPMODE_M);

    // Set sampling mode
    tempCtl |= samplingMode;

    // Write back control register
    HWREG(ADC_BASE + ADC_O_CTL1) = tempCtl;
}

//*****************************************************************************
//
// Set the ADC trigger source
//
//*****************************************************************************
void ADCSetTriggerSource(uint32_t triggerSource)
{
    uint32_t tempCtl;

    ASSERT((ADC_CTL1_TRIGSRC_M & triggerSource) == triggerSource);

    // Read current control register
    tempCtl = HWREG(ADC_BASE + ADC_O_CTL1);

    // Clear trigger-related fields
    tempCtl &= ~(ADC_CTL1_SC_M | ADC_CTL1_TRIGSRC_M);

    // Set trigger source
    tempCtl |= triggerSource;

    // Write back control register
    HWREG(ADC_BASE + ADC_O_CTL1) = tempCtl;
}

//*****************************************************************************
//
// Set the ADC trigger policy
//
//*****************************************************************************
void ADCSetTriggerPolicy(uint32_t triggerPolicy, uint32_t index)
{
    uint32_t tempCtl;

    ASSERT((ADC_MEMCTL_0_TRIG_M & triggerPolicy) == triggerPolicy);

    // Read current memory control register
    tempCtl = HWREG(ADC_BASE + ADC_O_MEMCTL_0 + (4 * index));

    // Clear trigger policy related fields
    tempCtl &= ~ADC_MEMCTL_0_TRIG_M;

    // Set trigger policy
    tempCtl |= triggerPolicy;

    // Write back memory control register
    HWREG(ADC_BASE + ADC_O_MEMCTL_0 + (4 * index)) = tempCtl;
}

//*****************************************************************************
//
// Set start and stop control registers
//
//*****************************************************************************
void ADCSetMemctlRange(uint32_t start, uint32_t stop)
{
    uint32_t tempCtl;

    // Read current control register
    tempCtl = HWREG(ADC_BASE + ADC_O_CTL2);

    // Clear start and stop address bits
    tempCtl &= ~(ADC_CTL2_ENDADD_M | ADC_CTL2_STARTADD_M);

    // Set start and stop address bits
    tempCtl |= (start << ADC_CTL2_STARTADD_S) & ADC_CTL2_STARTADD_M;
    tempCtl |= (stop << ADC_CTL2_ENDADD_S) & ADC_CTL2_ENDADD_M;

    // Write back control register
    HWREG(ADC_BASE + ADC_O_CTL2) = tempCtl;
}

//*****************************************************************************
//
// Set power down policy
//
//*****************************************************************************
void ADCSetPowerDownPolicy(uint32_t powerDownPolicy)
{
    uint32_t tempCtl;

    ASSERT((ADC_CTL0_PWRDN_M & powerDownPolicy) == powerDownPolicy);

    // Read current control register
    tempCtl = HWREG(ADC_BASE + ADC_O_CTL0);

    // Clear power down policy bits
    tempCtl &= ~(ADC_CTL0_PWRDN_M);

    // Set power down policy bits
    tempCtl |= powerDownPolicy;

    // Write back control register
    HWREG(ADC_BASE + ADC_O_CTL0) = tempCtl;
}

//*****************************************************************************
//
// Set sample clock source
//
//*****************************************************************************
void ADCSetSamplingClk(uint32_t clkSrc)
{
    uint32_t regVal;

    ASSERT(clkSrc <= ADC_SAMPLE_CLK_SOC_PLL_CLK_DIV);

    // Set sample clock source
    regVal = HWREG(ADC_BASE + ADC_O_CONVCTL);
    regVal &= ~(ADC_CONVCTL_CONCLKSEL_M | ADC_CONVCTL_CONVCLKEN_M);
    regVal |= (clkSrc << ADC_CONVCTL_CONCLKSEL_S);
    HWREG(ADC_BASE + ADC_O_CONVCTL) = regVal;

    // The clock must be enabled after the clock source have been selected.
    // This is required to avoid a glitch.
    regVal |= (1 << ADC_CONVCTL_CONVCLKEN_S);
    HWREG(ADC_BASE + ADC_O_CONVCTL) = regVal;
}

//*****************************************************************************
//
// Set conversion sequence
//
//*****************************************************************************
void ADCSetSequence(uint32_t sequence)
{
    uint32_t tempCtl;

    ASSERT((ADC_CTL1_CONSEQ_M & sequence) == sequence);

    // Read current control register
    tempCtl = HWREG(ADC_BASE + ADC_O_CTL1);

    // Clear sequence bits
    tempCtl &= ~(ADC_CTL1_CONSEQ_M);

    // Set sequence bits
    tempCtl |= sequence;

    // Write back control register
    HWREG(ADC_BASE + ADC_O_CTL1) = tempCtl;
}

//*****************************************************************************
//
// Convert ADC code to microvolts
//
//*****************************************************************************
uint32_t ADCValueToMicrovolts(uint32_t adcCode, uint32_t fullScaleRange)
{
    uint32_t microVolts;
    uint32_t lowerScaleLimitMicroVolt;
    uint32_t upperScaleLimitMicroVolt;
    uint32_t fsrSpanMicroVolt;
    // Shift value to to scale down the conversion voltage and avoid overflow
    const uint8_t SHIFT_VALUE = 2;

    switch (fullScaleRange)
    {
        case ADC_FULL_SCALE_RANGE_0V0_3V3:
            lowerScaleLimitMicroVolt = 0;
            upperScaleLimitMicroVolt = 3300000;
            break;
        case ADC_FULL_SCALE_RANGE_0V1_3V3:
            lowerScaleLimitMicroVolt = 100000;
            upperScaleLimitMicroVolt = 3300000;
            break;
        case ADC_FULL_SCALE_RANGE_0V0_3V2:
            lowerScaleLimitMicroVolt = 0;
            upperScaleLimitMicroVolt = 3200000;
            break;
        case ADC_FULL_SCALE_RANGE_0V0_1V8:
            lowerScaleLimitMicroVolt = 0;
            upperScaleLimitMicroVolt = 1800000;
            break;
        default:
            return 0;
    }

    fsrSpanMicroVolt = upperScaleLimitMicroVolt - lowerScaleLimitMicroVolt;

    // Shift down voltage to avoid 32bit overflow
    fsrSpanMicroVolt >>= SHIFT_VALUE;

    // Convert from code to microvolts rounding to the nearest integer.
    microVolts = (((adcCode * fsrSpanMicroVolt) + (ADC_MAX_CODE >> 1)) / ADC_MAX_CODE);

    // Shift result back up and add lower scale limit
    microVolts = (microVolts << SHIFT_VALUE) + lowerScaleLimitMicroVolt;

    return microVolts;
}

//*****************************************************************************
//
// Store trim values
//
//*****************************************************************************
void ADCStoreTrims(void)
{
    // Currently not supported
}

//*****************************************************************************
//
// Restore trim values
//
//*****************************************************************************
void ADCRestoreTrims(void)
{
    // The boot code should copy the e-fuse trims to memory, but this is not
    // supported in device rev. 1.0. Since we don't have the trim values we use
    // hard-coded values based on typical trim values as a workaround.
    HWREG(ADC_BASE + ADC_O_CTRL) = (ADC_CTRL_FSBIT1 << ADC_CTRL_FSBIT1_S) | (ADC_CTRL_FSBIT0 << ADC_CTRL_FSBIT0_S);
}
