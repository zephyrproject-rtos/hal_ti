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

static void enableADC(void);
static int32_t voltageToTemp(uint32_t microVolts);
static int64_t int_sqrt(uint64_t n);

/* Temporary PMUD PREFSYS register definition. */
#ifdef PMUD_O_PREFSYS
    #error "PMUD_O_PREFSYS defined in DOC release! Remove definitition below."
#endif

#define PMUD_O_PREFSYS     0x00000080U
#define PMUD_PREFSYS_TEST2 0x00000004U

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
// with 4 fractional bits.
//
//*****************************************************************************
static int32_t voltageToTemp(uint32_t microVolts)
{
    /* The tempsense diode voltage (mV) as a function of temperature (degC) can
     * be modeled as mV(T) = a*T^2 + b*T + c, where the coefficients are:
     * a = -0.000324
     * b = -1.432931
     * c = 833.729920
     *
     * To improve the performance we find the delta between the curve fit, and
     * the measured FCFG value. The FCFG temperature is not precisely 30 degC,
     * but 28.3 degC instead.
     * We calculate mV(28.3) = 792.918484 mV.
     *
     * The device-specific curve fit function then becomes
     * mV(T) = a*T^2 + b*T + c + delta, where delta = (FCFG_value - mV(28.3))
     *
     * mV(T) = -0.000324*T^2 - 1.432931*T + 833.729920 + FCFG_value - 792.918484
     *
     * To bring all constants from floating-point to fixed-point integers we
     * multiply the entire equation by a factor 2^24. This gives good enough
     * resolution, and leaves a margin before overflowing 64 bit calculations.
     * The shifted coefficients become as follows:
     *
     * aScaled = a * 2^24 = -5436
     * bScaled = b * 2^24 = -24040593
     * cScaled = c * 2^24 = 13987666953
     * mV(28.s)Scaled = 792.918484 * 2^24 = 13302964682
     *
     */

    int64_t aScaled    = -5436LL;       /*  -0.000324 * 2^24 */
    int64_t bScaled    = -24040593LL;   /*  -1.432931 * 2^24 */
    int64_t cScaled    = 13987666953LL; /* 833.729920 * 2^24 */
    int64_t mV28Scaled = 13302964682LL; /*   mV(28.3) * 2^24 */

    /* To find the temperature T, we solve the equation
     * 0 = p2*T^2 + p1*T + p0, using the quadratic formula, where
     * p2 = aScaled
     * p1 = bScaled
     * p0 = cScaled + fcfg_valueScaled - mV(28.s)Scaled - inputVoltageScaled
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
    int32_t temperature = ((-p1 - int_sqrt(p1 * p1 - (4 * p2 * p0))) << 4) / (2 * p2);

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

    /* Do 4 ADC conversions for averaging */
    for (uint32_t i = 0; i < 4; i++)
    {
        ADCManualTrigger();
        CPUDelay(3);
        diodeVoltage += ADCReadResult(0);
    }

    /* Measure ground (low side of the diode) */
    HWREG(SYS0_BASE + SYS0_O_TSENSCFG) = SYS0_TSENSCFG_SEL_GND;

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
// Compute the integer square root of a number n. Method taken from:
// https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Binary_numeral_system_(base_2)
//
//*****************************************************************************
static int64_t int_sqrt(uint64_t n)
{
    /* X_n+1 */
    int64_t x = n;

    /* c_n */
    int64_t c = 0;

    /* d_n which starts at the highest power of four <= n */
    int64_t d = 0x4000000000000000LL;

    while (d > n)
    {
        d >>= 2;
    }

    /* for d_n ... d_0 */
    while (d != 0)
    {
        if (x >= (c + d))
        {                     /* if X_m+1 ≥ Y_m then a_m = 2^m */
            x -= c + d;       /* X_m = X_m+1 - Y_m */
            c = (c >> 1) + d; /* c_m-1 = c_m/2 + d_m (a_m is 2^m) */
        }
        else
        {
            c >>= 1; /* c_m-1 = c_m/2. (a_m is 0) */
        }
        d >>= 2; /* d_m-1 = d_m/4 */
    }

    return c; /* c_-1 */
}