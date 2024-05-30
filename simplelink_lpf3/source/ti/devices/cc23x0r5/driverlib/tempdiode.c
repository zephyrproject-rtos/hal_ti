/******************************************************************************
 *  Filename:       tempdiode.c
 *
 *  Description:    Driverlib for the high accuracy temperature diode
 *
 *  Copyright (c) 2023, Texas Instruments Incorporated
 *  All rights reserved.
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
 *  3) Neither the name of the ORGANIZATION nor the names of its contributors may
 *     be used to endorse or promote products derived from this software without
 *     specific prior written permission.
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

#include <stdint.h>

#include "adc.h"
#include "hapi.h"
#include "tempdiode.h"
#include "interrupt.h"

#include "../inc/hw_clkctl.h"
#include "../inc/hw_fcfg.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_pmud.h"
#include "../inc/hw_sys0.h"
#include "../inc/hw_types.h"

#ifdef __IAR_SYSTEMS_ICC__
__ramfunc static uint32_t TempDiodeRamHWREG(uint32_t address, uint32_t data);
#elif (defined(__GNUC__) || defined(__clang__))
static uint32_t TempDiodeRamHWREG(uint32_t address, uint32_t data) __attribute__((section(".TI.ramfunc"), noinline));
#else
    #error Unsupported Compiler
#endif

extern int32_t voltageToTempHardcoded(uint32_t microVolts);
static void enableADC(void);
static int32_t voltageToTemp(uint32_t microVolts);
static uint64_t isqrt(uint64_t n);

/* Macros for finding minimum between two and three numbers */
#define MIN2(a, b)    ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) MIN2(MIN2((a), (b)), (c))

//*****************************************************************************
//
// Writes data to register while executing from RAM
//
//*****************************************************************************
#ifdef __IAR_SYSTEMS_ICC__
__ramfunc static uint32_t TempDiodeRamHWREG(uint32_t address, uint32_t data)
{
    HWREG(address) = data;
    /* Wait at least 11 us before proceeding with any flash operations */
    HapiWaitUs(11);
    return HWREG(address);
}
#elif (defined(__GNUC__) || defined(__clang__))
static uint32_t TempDiodeRamHWREG(uint32_t address, uint32_t data)
{
    HWREG(address) = data;
    /* Wait at least 11 us before proceeding with any flash operations */
    HapiWaitUs(11);
    return HWREG(address);
}
#else
    #error Unsupported Compiler
#endif

//*****************************************************************************
//
// Enable and configure the ADC. Parameters are the same as used during
// trim-procedure.
//
//*****************************************************************************
static void enableADC(void)
{
    /* Enable ADC peripheral */
    HWREG(CLKCTL_BASE + CLKCTL_O_CLKENSET0) = CLKCTL_CLKENSET0_ADC0;

    /* Configure ADC CTL-register 0 */
    ADCSetMemctlRange(0, 0);

    /* Set maximum sampling duration for highest accuracy */
    ADCSetSampleDuration(ADC_CLOCK_DIVIDER_48, 1023);

    /* Use 12-bit resolution */
    ADCSetResolution(ADC_RESOLUTION_12_BIT);

    /* Use internal 1.4V reference, sample on internal channel 14 (VA_ATEST1) */
    ADCSetInput(ADC_FIXED_REFERENCE_1V4, ADC_MEMCTL0_CHANSEL_CHAN_14, 0);

    /* Adjust ADC to 1.4V reference */
    ADCSetAdjustmentOffset(ADC_FIXED_REFERENCE_1V4);

    /* Perform single conversion */
    ADCSetSequence(ADC_SEQUENCE_SINGLE);
}

//*****************************************************************************
//
// Converts a voltage (uV) measured across the diode to temperature (degC),
// with 4 fractional bits, using hardcoded coefficients. If the device has
// coefficients available in FCFG, or if different hardcoded values are needed,
// then this function can be overridden.
//
//*****************************************************************************
int32_t __attribute__((weak)) voltageToTempHardcoded(uint32_t microVolts)
{
    /* The tempsense diode voltage (mV) as a function of temperature (degC) can
     * be modeled as mV(T) = a*T^2 + b*T + c, where the coefficients are:
     * a = -0.000327
     * b = -1.435965
     * c = 835.584465
     *
     * To improve the performance we find the delta between the curve fit, and
     * the measured FCFG value. The FCFG temperature is not precisely 30 degC,
     * but 29.5 degC instead.
     * We calculate mV(29.5) = 792.938926 mV.
     *
     * The device-specific curve fit function then becomes
     * mV(T) = a*T^2 + b*T + c + delta, where delta = (FCFG_value - mV(29.5))
     *
     * mV(T) = -0.000327*T^2 - 1.435965*T + 835.584465 + FCFG_value - 792.938926
     *
     * To bring all constants from floating-point to fixed-point integers we
     * multiply the entire equation by a factor 2^24. This gives good enough
     * resolution, and leaves a margin before overflowing 64 bit calculations.
     * The shifted coefficients become as follows:
     *
     * aScaled = a * 2^24 = -5486
     * bScaled = b * 2^24 = -24091495
     * cScaled = c * 2^24 = 14018781056
     * mV(29.5)Scaled = 792.938926 * 2^24 = 13303307632
     *
     */

    int64_t aScaled    = -5486LL;       /*  -0.000327 * 2^24 */
    int64_t bScaled    = -24091495LL;   /*  -1.435965 * 2^24 */
    int64_t cScaled    = 14018781056LL; /* 835.584465 * 2^24 */
    int64_t mV28Scaled = 13303307632LL; /*   mV(29.5) * 2^24 */

    /* To find the temperature T, we solve the equation
     * 0 = p2*T^2 + p1*T + p0, using the quadratic formula, where
     * p2 = aScaled
     * p1 = bScaled
     * p0 = cScaled + fcfg_valueScaled - mV(29.5)Scaled - inputVoltageScaled
     *
     * T = (-p1 - sqrt(p1*p1 - 4*p2*p0)) / (2*p2)
     */

    int64_t fcfgValue = fcfg->appTrims.cc23x0r5.auxDiodeCal30C.auxDiodeVoltage -
                        fcfg->appTrims.cc23x0r5.auxDiodeCal30C.auxDiodeGnd;

    /* The FCFG voltage value is already left-shifted by 4, so we only shift it
     * 20 more.
     */
    int64_t fcfgValueScaled = fcfgValue << 20;

    /* Convert input voltage (microvolts) to scaled millivolts */
    int64_t inputVoltageScaled = (((int64_t)microVolts << 24) + 500) / 1000;

    int64_t p2 = aScaled;
    int64_t p1 = bScaled;
    int64_t p0 = cScaled + fcfgValueScaled - mV28Scaled - inputVoltageScaled;

    /* Apply quadratic formula, but scale numerator by a factor 16 to get 4
     * fractional bits in the temperature result.
     */
    int32_t temperature = ((-p1 - (int64_t)isqrt(p1 * p1 - (4 * p2 * p0))) << 4) / (2 * p2);

    return temperature;
}

//*****************************************************************************
//
// Converts a voltage (uV) measured across the diode to temperature (degC),
// with 4 fractional bits.
//
//*****************************************************************************
static int32_t voltageToTemp(uint32_t microVolts)
{
    /* Check if coefficients are directly available in FCFG. If not, fall back
     * on function using hardcoded values. Coefficients were only introduced in
     * FCFG layout revision 6.
     */
    uint8_t fcfgRevision = fcfg->appTrims.revision;

    if (fcfgRevision < 0x06)
    {
        return voltageToTempHardcoded(microVolts);
    }

    /* The tempsense diode voltage (mV) as a function of temperature (degC) can
     * be modeled as mV(T) = a*T^2 + b*T + c, where the coefficients are:
     * a = a_fcfg >> a_fcfg_shift
     * b = b_fcfg >> b_fcfg_shift
     * c = c_fcfg >> c_fcfg_shift
     */

    int64_t aScaled = fcfg->appTrims.cc23x0r5.auxDiodeCoeff.coeffP2;
    int64_t bScaled = fcfg->appTrims.cc23x0r5.auxDiodeCoeff.coeffP1;
    int64_t cScaled = fcfg->appTrims.cc23x0r5.auxDiodeCoeff.coeffP0;

    uint8_t aShiftFactor = fcfg->appTrims.cc23x0r5.auxDiodeCoeff.coeffP2Shift;
    uint8_t bShiftFactor = fcfg->appTrims.cc23x0r5.auxDiodeCoeff.coeffP1Shift;
    uint8_t cShiftFactor = fcfg->appTrims.cc23x0r5.auxDiodeCoeff.coeffP0Shift;

    /* Bring coefficients to the same scale. Try to shift towards the
     * numerically highest coefficient (the one with the largest shift) in
     * order to maintain highest possible resolution. Since coefficients are
     * 16-bit, they should be scaled maximum by 16, otherwise two coefficients
     * would overflow 64-bit when multiplied. If some coefficients need to be
     * shifted more than 16 bits, a middle ground must be found and some
     * coefficients must be shifted down instead.
     */
    uint8_t minShiftFactor = MIN3(aShiftFactor, bShiftFactor, cShiftFactor);

    /* Always shift up at least 16 bits */
    uint8_t commonShiftFactor = minShiftFactor + 16;

    int64_t *coefficients[3] = {&aScaled, &bScaled, &cScaled};
    uint8_t shiftFactors[3]  = {aShiftFactor, bShiftFactor, cShiftFactor};

    /* Loop over all three coefficients and scale each one. */
    for (int i = 0; i < 3; i++)
    {
        if (shiftFactors[i] < commonShiftFactor)
        {
            /* Scale this coefficient up towards the common scale factor */
            *coefficients[i] <<= (commonShiftFactor - shiftFactors[i]);
        }
        else if (shiftFactors[i] > commonShiftFactor)
        {
            /* Scale this coefficient down towards the common scale factor */
            *coefficients[i] >>= (shiftFactors[i] - commonShiftFactor);
        }
        else
        {
            /* Do nothing. Scale neither up nor down */
        }
    }

    /* Convert input voltage (microvolts) to scaled millivolts. The common
     * shift factor can be maximum 31 + 16 = 47, and microvolts can be maximum
     * 1,400,000, which means that (microvolts << commonShiftFactor) can in
     * theory overflow. Practically, the characteristics of the tempsense diode
     * tell us this will never happen, but we add a check just in case.
     */
    int64_t inputVoltageScaled;

    if (commonShiftFactor >= 42)
    {
        /* If shitfting up by more than 42, this value might overflow. Divide
         * by 1000 to convert to millivolts before shifting.
         */
        inputVoltageScaled = (int64_t)(microVolts / 1000) << commonShiftFactor;
    }
    else
    {
        inputVoltageScaled = (((int64_t)microVolts << commonShiftFactor) + 500) / 1000;
    }

    /* To find the temperature T, we solve the equation
     * 0 = p2*T^2 + p1*T + p0, using the quadratic formula, where
     * p2 = aScaled
     * p1 = bScaled
     * p0 = cScaled - inputVoltageScaled
     *
     * T = (-p1 - sqrt(p1*p1 - 4*p2*p0)) / (2*p2)
     */
    int64_t p2 = aScaled;
    int64_t p1 = bScaled;
    int64_t p0 = cScaled - inputVoltageScaled;

    /* Apply quadratic formula, but scale numerator by a factor 16 to get 4
     * fractional bits in the temperature result. Round to nearest integer.
     */
    int64_t dividend = (-p1 - (int64_t)isqrt(p1 * p1 - (4 * p2 * p0))) << 4;
    int64_t divisor  = 2 * p2;
    int32_t temperature;

    if ((dividend < 0LL) == (divisor < 0LL))
    {
        /* If dividend has same sign as divisor */
        temperature = (dividend + (divisor / 2)) / divisor;
    }
    else
    {
        /* If dividend has opposite sign as divisor */
        temperature = (dividend - (divisor / 2)) / divisor;
    }

    return temperature;
}

//*****************************************************************************
//
// Reads temperature from high accuracy temperature diode with 4 fractional bits
//
//*****************************************************************************
int32_t TempDiodeGetTemp(void)
{
    uint32_t diodeVoltage = 0;
    bool intAlreadyDisabled;

    /* Unlock ATESTCFG register and connect VR_ATEST to VA_ATEST */
    HWREG(SYS0_BASE + SYS0_O_ATESTCFG) = 0x5A000000 | SYS0_ATESTCFG_VR2VA1 | SYS0_ATESTCFG_VR2VA0;

    /* Disable interrupts and keep track of whether interrupts were already
     * disabled or not
     */
    intAlreadyDisabled = IntDisableMaster();

    /* Connect 1uA IREF to test bus. This is done via a function executing from
     * RAM, while interrupts are disabled, to ensure that no flash-operations
     * are active when the reference current is enabled.
     */
    TempDiodeRamHWREG(PMUD_BASE + PMUD_O_PREFSYS, PMUD_PREFSYS_TEST2);

    /* If interrupts were already disabled, then they should be left disabled.
     * If interrupts were already enabled, then they should be re-enabled here.
     */
    if (intAlreadyDisabled == false)
    {
        IntEnableMaster();
    }

    enableADC();

    /* Measure the high side of the diode */
    HWREG(SYS0_BASE + SYS0_O_TSENSCFG) = SYS0_TSENSCFG_SEL_VALUE;

    /* Perform a dummy-read of the ADC for better settling */
    ADCManualTrigger();
    CPUDelay(3);
    ADCReadResult(0);

    /* Do 4 ADC conversions for averaging */
    for (uint32_t i = 0; i < 4; i++)
    {
        ADCManualTrigger();
        CPUDelay(3);
        diodeVoltage += ADCReadResult(0);
    }

    /* Measure ground (low side of the diode) */
    HWREG(SYS0_BASE + SYS0_O_TSENSCFG) = SYS0_TSENSCFG_SEL_GND;

    /* Perform a dummy-read of the ADC for better settling */
    ADCManualTrigger();
    CPUDelay(3);
    ADCReadResult(0);

    /* Do 4 ADC conversions for averaging */
    for (uint32_t i = 0; i < 4; i++)
    {
        ADCManualTrigger();
        CPUDelay(3);
        diodeVoltage -= ADCReadResult(0);
    }

    /* Calculate an average of the 4 readings, rounded to the nearest integer */
    diodeVoltage = (diodeVoltage + 2) >> 2;

    /* Adjust ADC value to compensate for device/reference specific gain */
    uint16_t gain = ADCGetAdjustmentGain(ADC_FIXED_REFERENCE_1V4);
    diodeVoltage  = ADCAdjustValueForGain(diodeVoltage, ADC_RESOLUTION_12_BIT, gain);

    /* Convert raw reading to microvolts */
    diodeVoltage = ADCValueToMicrovolts(diodeVoltage, ADC_RESOLUTION_12_BIT, 1400000);

    /* Disable ADC */
    HWREG(CLKCTL_BASE + CLKCTL_O_CLKENCLR0) = CLKCTL_CLKENCLR0_ADC0;

    /* Reset ATB */
    HWREG(SYS0_BASE + SYS0_O_ATESTCFG) = 0x5A00000F;

    /* Disable temperature diode measurement */
    HWREG(SYS0_BASE + SYS0_O_TSENSCFG) &= ~SYS0_TSENSCFG_SEL_M;

    /* Disconnect all test reference signals */
    intAlreadyDisabled = IntDisableMaster();
    TempDiodeRamHWREG(PMUD_BASE + PMUD_O_PREFSYS, 0);
    if (intAlreadyDisabled == false)
    {
        IntEnableMaster();
    }

    return voltageToTemp(diodeVoltage);
}

//*****************************************************************************
//
// Compute the integer square root of a number n. This function returns the
// largest integer whose square is equal to or less than n.
//
//*****************************************************************************
static uint64_t isqrt(uint64_t n)
{
    uint64_t remainder, root;

    /* Initialize the remainder and root to zero */
    remainder = 0;
    root      = 0;

    /* Loop over the 32 bits in the root */
    for (uint32_t index = 0; index < 32; index++)
    {
        /*
         * Shift the root up by a bit to make room for the new bit that is
         * about to be computed.
         */
        root <<= 1;

        /* Get two more bits from the input into the remainder */
        remainder = ((remainder << 2) + (n >> 62));
        n <<= 2;

        /* Make the test root be 2n + 1 */
        root++;

        /* See if the root is greater than the remainder */
        if (root <= remainder)
        {
            /* Subtract the test root from the remainder */
            remainder -= root;

            /* Increment the root, setting the second LSB */
            root++;
        }
        else
        {
            /*
             * The root is greater than the remainder, so the new bit of the
             * root is actually zero
             */
            root--;
        }
    }

    /* Return the computed root */
    return root >> 1;
}