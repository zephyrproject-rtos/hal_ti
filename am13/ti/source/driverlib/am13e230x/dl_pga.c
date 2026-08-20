
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

#include "dl_pga.h"

void DL_PGA_initParamsSetDefault(DL_PGA_Config *config)
{
    if (config == NULL)
    {
        ASSERT(false);
    }

    config->enable                   = false;
    config->gainValue                = DL_PGA_GAIN_1;
    config->enableOutput             = false;
    config->enableInternalGainOutput = false;
    config->pmuxInput                = DL_PGA_PMUX_INP1;
    config->nmuxInput                = DL_PGA_NMUX_RTOP;
    config->mmuxInput                = DL_PGA_MMUX_NAKED_OPAMP;
    config->enableFeedbackOnPin      = false;

    // Initialize Filter configuration
    config->filterConfig.resistorValue = DL_PGA_LOW_PASS_FILTER_DISABLED;

    // Initialize Chopper configuration
    config->chopperConfig.enableExternalChop = false;
    config->chopperConfig.chopMode           = DL_PGA_CHOP_DISABLED;

    config->lockRegistersMask = 0;
}

void DL_PGA_init(PGA_Regs *pga, DL_PGA_Config *config)
{
    if (pga == NULL || config == NULL)
    {
        ASSERT(false);
    }

    // Select the PGA positive input mux source
    DL_PGA_selectPMUXInput(pga, config->pmuxInput);

    // Select the PGA negative input multiplexer (NMUX) source
    DL_PGA_selectNMUXInput(pga, config->nmuxInput);

    // Select the input source for the M-Mux
    DL_PGA_selectMMUXInput(pga, config->mmuxInput);

    // Set the PGA gain value
    DL_PGA_setGain(pga, config->gainValue);

    // Enable or disable feedback to the PGA negative input pin
    if (config->enableFeedbackOnPin)
    {
        DL_PGA_enableFeedbackOnPin(pga);
    }
    else
    {
        DL_PGA_disableFeedbackOnPin(pga);
    }

    // Set the PGA output filter resistor value
    DL_PGA_setFilterResistor(pga, config->filterConfig.resistorValue);

    // Enable or disable the external chopping signal for the PGA
    if (config->chopperConfig.enableExternalChop)
    {
        DL_PGA_enableExternalChop(pga);
    }
    else
    {
        DL_PGA_disableExternalChop(pga);
    }

    // Select the PGA chop mode
    DL_PGA_chop(pga, config->chopperConfig.chopMode);

    // Enable or disable the PGA internal gain output on the pin
    if (config->enableInternalGainOutput)
    {
        DL_PGA_enableInternalGainOutput(pga);
    }
    else
    {
        DL_PGA_disableInternalGainOutput(pga);
    }

    // Enable or disable the PGA output on the pin
    if (config->enableOutput)
    {
        DL_PGA_enableOutput(pga);
    }
    else
    {
        DL_PGA_disableOutput(pga);
    }

    // Enable or disable the PGA
    if (config->enable)
    {
        DL_PGA_enable(pga);
    }
    else
    {
        DL_PGA_disable(pga);
    }

    // Lock the PGA registers
    DL_PGA_lockRegisters(pga, config->lockRegistersMask);
}
