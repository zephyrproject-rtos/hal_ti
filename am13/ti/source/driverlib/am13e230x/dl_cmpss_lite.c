
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

#include "dl_cmpss_lite.h"

void DL_CMPSSLITE_configFilterHigh(CMPSS_LITE_Regs *cmpsslite, uint32_t samplePrescale, uint16_t sampleWindow,
                                   uint16_t threshold)
{
    uint16_t regValue;

    ASSERT(samplePrescale <= 16777215UL);
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 64U));
    ASSERT((threshold - 1U) >= ((sampleWindow - 1U) / 2U));

    regValue = ((sampleWindow - 1U) << CMPSS_LITE_CTRIPHFILCTL_SAMPWIN_OFS) |
               ((threshold - 1U) << CMPSS_LITE_CTRIPHFILCTL_THRESH_OFS);

    /* Update filter control register */
    cmpsslite->CTRIPHFILCTL =
        (cmpsslite->CTRIPHFILCTL & ~(CMPSS_LITE_CTRIPHFILCTL_SAMPWIN_MASK | CMPSS_LITE_CTRIPHFILCTL_THRESH_MASK)) |
        regValue;

    /* Set filter sample clock prescaler */
    cmpsslite->CTRIPHFILCLKCTL  = (uint16_t)samplePrescale;
    cmpsslite->CTRIPHFILCLKCTL2 = (uint16_t)(samplePrescale >> 16U);
}

void DL_CMPSSLITE_configFilterLow(CMPSS_LITE_Regs *cmpsslite, uint32_t samplePrescale, uint16_t sampleWindow,
                                  uint16_t threshold)
{
    uint16_t regValue;

    ASSERT(samplePrescale <= 16777215UL);
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 64U));
    ASSERT((threshold - 1U) >= ((sampleWindow - 1U) / 2U));

    regValue = ((sampleWindow - 1U) << CMPSS_LITE_CTRIPLFILCTL_SAMPWIN_OFS) |
               ((threshold - 1U) << CMPSS_LITE_CTRIPLFILCTL_THRESH_OFS);

    /* Update filter control register */
    cmpsslite->CTRIPLFILCTL =
        (cmpsslite->CTRIPLFILCTL & ~(CMPSS_LITE_CTRIPLFILCTL_SAMPWIN_MASK | CMPSS_LITE_CTRIPLFILCTL_THRESH_MASK)) |
        regValue;

    /* Set filter sample clock prescaler */
    cmpsslite->CTRIPLFILCLKCTL  = (uint16_t)samplePrescale;
    cmpsslite->CTRIPLFILCLKCTL2 = (uint16_t)(samplePrescale >> 16U);
}

void DL_CMPSSLITE_configLatchOnPWMSYNC(CMPSS_LITE_Regs *cmpsslite, bool highEnable, bool lowEnable)
{
    /* If the highEnable is true, set the bit that will enable PWMSYNC to reset
       the high comparator digital filter latch. If not, clear the bit. */

    if (highEnable)
    {
        cmpsslite->COMPSTSCLR |= CMPSS_LITE_COMPSTSCLR_HSYNCCLREN_MASK;
    }
    else
    {
        cmpsslite->COMPSTSCLR &= ~CMPSS_LITE_COMPSTSCLR_HSYNCCLREN_MASK;
    }

    /* If the lowEnable is true, set the bit that will enable PWMSYNC to reset
       the low comparator digital filter latch. If not, clear the bit. */

    if (lowEnable)
    {
        cmpsslite->COMPSTSCLR |= CMPSS_LITE_COMPSTSCLR_LSYNCCLREN_MASK;
    }
    else
    {
        cmpsslite->COMPSTSCLR &= ~CMPSS_LITE_COMPSTSCLR_LSYNCCLREN_MASK;
    }
}

void DL_CMPSSLITE_initParamsSetDefault(DL_CMPSSLITE_Config *config)
{
    if (config == NULL)
    {
        ASSERT(false);
    }

    // Initialize common configuration
    config->enableModule    = false;
    config->hysteresis      = DL_CMPSSLITE_HYSTERESIS_NONE;
    config->dacSwLoadSelect = DL_CMPSSLITE_DACVAL_MCLK;

    // Initialize high comparator subsystem configuration
    config->highCompSSConfig.syncSource = DL_CMPSSLITE_SYNCSOURCE_MCPWM0_SYNCPER;
    config->highCompSSConfig.useComp    = false;
    config->highCompSSConfig.useDac     = false;
    config->highCompSSConfig.useFilter  = false;

    // Initialize high comparator subsystem - COMP configuration
    config->highCompSSConfig.compConfig.sourceSelect        = DL_CMPSSLITE_INSRC_DAC;
    config->highCompSSConfig.compConfig.invert              = false;
    config->highCompSSConfig.compConfig.tripSourceSelect    = DL_CMPSSLITE_TRIP_ASYNC_COMP;
    config->highCompSSConfig.compConfig.tripOutSourceSelect = DL_CMPSSLITE_TRIPOUT_ASYNC_COMP;

    // Initialize high comparator subsystem - DAC configuration
    config->highCompSSConfig.dacConfig.initialDacValue = 0;

    // Initialize high comparator subsystem - Digital filter configuration
    config->highCompSSConfig.filterConfig.initFilter                = false;
    config->highCompSSConfig.filterConfig.filtInput                 = DL_CMPSSLITE_FILTIN_COMPOUT;
    config->highCompSSConfig.filterConfig.samplePrescale            = 0;
    config->highCompSSConfig.filterConfig.sampleWindow              = 0;
    config->highCompSSConfig.filterConfig.threshold                 = 0;
    config->highCompSSConfig.filterConfig.asyncORLatch              = false;
    config->highCompSSConfig.filterConfig.enableLatchResetOnPWMSYNC = false;

    // Initialize low comparator subsystem configuration
    config->lowCompSSConfig.syncSource = DL_CMPSSLITE_SYNCSOURCE_MCPWM0_SYNCPER;
    config->lowCompSSConfig.useComp    = false;
    config->lowCompSSConfig.useDac     = false;
    config->lowCompSSConfig.useFilter  = false;

    // Initialize low comparator subsystem - COMP configuration
    config->lowCompSSConfig.compConfig.sourceSelect        = DL_CMPSSLITE_INSRC_DAC;
    config->lowCompSSConfig.compConfig.invert              = false;
    config->lowCompSSConfig.compConfig.tripSourceSelect    = DL_CMPSSLITE_TRIP_ASYNC_COMP;
    config->lowCompSSConfig.compConfig.tripOutSourceSelect = DL_CMPSSLITE_TRIPOUT_ASYNC_COMP;

    // Initialize low comparator subsystem - DAC configuration
    config->lowCompSSConfig.dacConfig.initialDacValue = 0;

    // Initialize low comparator subsystem - Digital filter configuration
    config->lowCompSSConfig.filterConfig.initFilter                = false;
    config->lowCompSSConfig.filterConfig.filtInput                 = DL_CMPSSLITE_FILTIN_COMPOUT;
    config->lowCompSSConfig.filterConfig.samplePrescale            = 0;
    config->lowCompSSConfig.filterConfig.sampleWindow              = 0;
    config->lowCompSSConfig.filterConfig.threshold                 = 0;
    config->lowCompSSConfig.filterConfig.asyncORLatch              = false;
    config->lowCompSSConfig.filterConfig.enableLatchResetOnPWMSYNC = false;
}

void DL_CMPSSLITE_init(CMPSS_LITE_Regs *cmpsslite, DL_CMPSSLITE_Config *config)
{
    if (cmpsslite == NULL || config == NULL)
    {
        ASSERT(false);
    }

    // Set hysteresis configuration
    DL_CMPSSLITE_setHysteresis(cmpsslite, config->hysteresis);
    // Set DAC load select
    DL_CMPSSLITE_configDACHigh(cmpsslite, config->dacSwLoadSelect);

    uint16_t highConfig = DL_CMPSSLITE_INSRC_DAC;  // No invert, Neg input driven by internal DAC, ASYNCH disable

    // Configure high comparator subsystem
    DL_CMPSSLITE_configureSyncSourceHigh(cmpsslite, config->highCompSSConfig.syncSource);
    if (config->highCompSSConfig.useComp)
    {
        // COMP config
        if (config->highCompSSConfig.compConfig.invert)
        {
            highConfig |= DL_CMPSSLITE_CONFIG_INVERT;
        }
        if (config->highCompSSConfig.compConfig.sourceSelect == DL_CMPSSLITE_INSRC_DAC)
        {
            highConfig |= DL_CMPSSLITE_INSRC_DAC;
        }
        else
        {
            highConfig |= DL_CMPSSLITE_INSRC_PIN;
        }

        uint16_t highOutputConfig  = 0;
        highOutputConfig           = ((config->highCompSSConfig.compConfig.tripSourceSelect) &
                            (DL_CMPSSLITE_TRIP_ASYNC_COMP | DL_CMPSSLITE_TRIP_SYNC_COMP | DL_CMPSSLITE_TRIP_FILTER |
                             DL_CMPSSLITE_TRIP_LATCH));
        highOutputConfig          |= ((config->highCompSSConfig.compConfig.tripOutSourceSelect) &
                             (DL_CMPSSLITE_TRIPOUT_ASYNC_COMP | DL_CMPSSLITE_TRIPOUT_SYNC_COMP |
                              DL_CMPSSLITE_TRIPOUT_FILTER | DL_CMPSSLITE_TRIPOUT_LATCH));
        DL_CMPSSLITE_configOutputsHigh(cmpsslite, highOutputConfig);
    }

    if (config->highCompSSConfig.useDac)
    {
        // DAC Config
        DL_CMPSSLITE_setDACValueHigh(cmpsslite, config->highCompSSConfig.dacConfig.initialDacValue);
    }

    if (config->highCompSSConfig.useFilter)
    {
        if (config->highCompSSConfig.filterConfig.asyncORLatch)
        {
            highConfig |= DL_CMPSSLITE_CONFIG_ASYNCH_ENABLE;
        }

        // Digital Filter config
        DL_CMPSSLITE_configFilterHigh(cmpsslite, config->highCompSSConfig.filterConfig.samplePrescale,
                                      config->highCompSSConfig.filterConfig.sampleWindow,
                                      config->highCompSSConfig.filterConfig.threshold);
        DL_CMPSSLITE_configFilterInputHigh(cmpsslite, config->highCompSSConfig.filterConfig.filtInput);
        if (config->highCompSSConfig.filterConfig.initFilter)
        {
            DL_CMPSSLITE_initFilterHigh(cmpsslite);
        }
        if (config->highCompSSConfig.filterConfig.enableLatchResetOnPWMSYNC)
        {
            DL_CMPSSLITE_enableLatchResetOnPWMSYNCHigh(cmpsslite);
        }
        else
        {
            DL_CMPSSLITE_disableLatchResetOnPWMSYNCHigh(cmpsslite);
        }
    }

    DL_CMPSSLITE_configHighComparator(cmpsslite, highConfig);

    uint16_t lowConfig = DL_CMPSSLITE_INSRC_DAC;  // No invert, Neg input driven by internal DAC, ASYNCL disable

    // Configure low comparator subsystem
    DL_CMPSSLITE_configureSyncSourceLow(cmpsslite, config->lowCompSSConfig.syncSource);
    if (config->lowCompSSConfig.useComp)
    {
        // COMP config
        if (config->lowCompSSConfig.compConfig.invert)
        {
            lowConfig |= DL_CMPSSLITE_CONFIG_INVERT;
        }
        if (config->lowCompSSConfig.compConfig.sourceSelect == DL_CMPSSLITE_INSRC_DAC)
        {
            lowConfig |= DL_CMPSSLITE_INSRC_DAC;
        }
        else
        {
            lowConfig |= DL_CMPSSLITE_INSRC_PIN;
        }

        uint16_t lowOutputConfig  = 0;
        lowOutputConfig           = ((config->lowCompSSConfig.compConfig.tripSourceSelect) &
                           (DL_CMPSSLITE_TRIP_ASYNC_COMP | DL_CMPSSLITE_TRIP_SYNC_COMP | DL_CMPSSLITE_TRIP_FILTER |
                            DL_CMPSSLITE_TRIP_LATCH));
        lowOutputConfig          |= ((config->lowCompSSConfig.compConfig.tripOutSourceSelect) &
                            (DL_CMPSSLITE_TRIPOUT_ASYNC_COMP | DL_CMPSSLITE_TRIPOUT_SYNC_COMP |
                             DL_CMPSSLITE_TRIPOUT_FILTER | DL_CMPSSLITE_TRIPOUT_LATCH));
        DL_CMPSSLITE_configOutputsLow(cmpsslite, lowOutputConfig);
    }

    if (config->lowCompSSConfig.useDac)
    {
        // DAC Config
        DL_CMPSSLITE_setDACValueLow(cmpsslite, config->lowCompSSConfig.dacConfig.initialDacValue);
    }

    if (config->lowCompSSConfig.useFilter)
    {
        if (config->lowCompSSConfig.filterConfig.asyncORLatch)
        {
            lowConfig |= DL_CMPSSLITE_CONFIG_ASYNCH_ENABLE;
        }

        // Digital Filter config
        DL_CMPSSLITE_configFilterLow(cmpsslite, config->lowCompSSConfig.filterConfig.samplePrescale,
                                     config->lowCompSSConfig.filterConfig.sampleWindow,
                                     config->lowCompSSConfig.filterConfig.threshold);
        DL_CMPSSLITE_configFilterInputLow(cmpsslite, config->lowCompSSConfig.filterConfig.filtInput);
        if (config->lowCompSSConfig.filterConfig.initFilter)
        {
            DL_CMPSSLITE_initFilterLow(cmpsslite);
        }
        if (config->lowCompSSConfig.filterConfig.enableLatchResetOnPWMSYNC)
        {
            DL_CMPSSLITE_enableLatchResetOnPWMSYNCLow(cmpsslite);
        }
        else
        {
            DL_CMPSSLITE_disableLatchResetOnPWMSYNCLow(cmpsslite);
        }
    }

    DL_CMPSSLITE_configLowComparator(cmpsslite, lowConfig);

    // Enable or disable the comparator/DAC core
    if (config->enableModule)
    {
        DL_CMPSSLITE_enableModule(cmpsslite);
    }
    else
    {
        DL_CMPSSLITE_disableModule(cmpsslite);
    }
}
