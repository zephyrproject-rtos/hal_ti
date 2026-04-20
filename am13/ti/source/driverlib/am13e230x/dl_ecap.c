
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

#include "dl_ecap.h"

void DL_ECAP_initParamsSetDefault(DL_ECAP_Config *config)
{
    // Initialize capture or APWM mode select
    config->modeSelect = DL_ECAP_OPERATING_MODE_CAPTURE;

    // Initialize capture mode configuration
    config->captureModeConfig.input                = DL_ECAP_INPUT_INPUTXBAR1;
    config->captureModeConfig.prescalerValue       = 1;
    config->captureModeConfig.continouousOrOneShot = DL_ECAP_CONTINUOUS_CAPTURE_MODE;
    config->captureModeConfig.wrapOrStopAtEvent    = DL_ECAP_EVENT_1;

    config->captureModeConfig.enableCounterResetOnCaptureEvent1 = false;
    config->captureModeConfig.enableCounterResetOnCaptureEvent2 = false;
    config->captureModeConfig.enableCounterResetOnCaptureEvent3 = false;
    config->captureModeConfig.enableCounterResetOnCaptureEvent4 = false;
    config->captureModeConfig.captureEvent1Polarity             = DL_ECAP_EVENT_RISING_EDGE;
    config->captureModeConfig.captureEvent2Polarity             = DL_ECAP_EVENT_RISING_EDGE;
    config->captureModeConfig.captureEvent3Polarity             = DL_ECAP_EVENT_RISING_EDGE;
    config->captureModeConfig.captureEvent4Polarity             = DL_ECAP_EVENT_RISING_EDGE;

    // By default, do not reset counter
    config->captureModeConfig.resetCounter = false;
    // By default, do not re-arm
    config->captureModeConfig.reArm        = false;

    // Initialize APWM mode configuration
    config->apwmModeConfig.compareCount = 0;
    config->apwmModeConfig.periodCount  = 0;
    config->apwmModeConfig.polarity     = DL_ECAP_APWM_ACTIVE_HIGH;

    // Initialize sync configuration
    config->syncConfig.ecapSyncInSel     = DL_ECAP_SYNC_IN_PULSE_SRC_DISABLE;
    config->syncConfig.phaseShiftCount   = 0;
    config->syncConfig.syncOutSelect     = DL_ECAP_SYNC_OUT_DISABLED;
    config->syncConfig.enableLoadCounter = false;

    // Initialize interrupt configuration
    config->interruptsConfig.interruptSourceEnableMask = 0;
    config->interruptsConfig.dmaEventSelect            = DL_ECAP_EVENT_1;

    // Initialize default emulation mode
    config->emulationMode = DL_ECAP_EMULATION_STOP;
}

void DL_ECAP_init(ECAP_Regs *ecap, DL_ECAP_Config *config)
{
    // Configure capture or APWM mode
    if (config->modeSelect == DL_ECAP_OPERATING_MODE_CAPTURE)
    {
        // Enable capture mode
        DL_ECAP_enableCaptureMode(ecap);

        // Configure capture mode
        DL_ECAP_setEventPrescaler(ecap, config->captureModeConfig.prescalerValue);
        DL_ECAP_setCaptureMode(ecap, config->captureModeConfig.continouousOrOneShot,
                               config->captureModeConfig.wrapOrStopAtEvent);

        // Configure event polarities
        DL_ECAP_setEventPolarity(ecap, DL_ECAP_EVENT_1, config->captureModeConfig.captureEvent1Polarity);
        DL_ECAP_setEventPolarity(ecap, DL_ECAP_EVENT_2, config->captureModeConfig.captureEvent2Polarity);
        DL_ECAP_setEventPolarity(ecap, DL_ECAP_EVENT_3, config->captureModeConfig.captureEvent3Polarity);
        DL_ECAP_setEventPolarity(ecap, DL_ECAP_EVENT_4, config->captureModeConfig.captureEvent4Polarity);

        // Configure counter reset on events
        if (config->captureModeConfig.enableCounterResetOnCaptureEvent1)
        {
            DL_ECAP_enableCounterResetOnEvent(ecap, DL_ECAP_EVENT_1);
        }
        else
        {
            DL_ECAP_disableCounterResetOnEvent(ecap, DL_ECAP_EVENT_1);
        }
        if (config->captureModeConfig.enableCounterResetOnCaptureEvent2)
        {
            DL_ECAP_enableCounterResetOnEvent(ecap, DL_ECAP_EVENT_2);
        }
        else
        {
            DL_ECAP_disableCounterResetOnEvent(ecap, DL_ECAP_EVENT_2);
        }
        if (config->captureModeConfig.enableCounterResetOnCaptureEvent3)
        {
            DL_ECAP_enableCounterResetOnEvent(ecap, DL_ECAP_EVENT_3);
        }
        else
        {
            DL_ECAP_disableCounterResetOnEvent(ecap, DL_ECAP_EVENT_3);
        }
        if (config->captureModeConfig.enableCounterResetOnCaptureEvent4)
        {
            DL_ECAP_enableCounterResetOnEvent(ecap, DL_ECAP_EVENT_4);
        }
        else
        {
            DL_ECAP_disableCounterResetOnEvent(ecap, DL_ECAP_EVENT_4);
        }

        // Select ECAP input
        DL_ECAP_selectECAPInput(ecap, config->captureModeConfig.input);
    }
    else if (config->modeSelect == DL_ECAP_OPERATING_MODE_APWM)
    {
        // Enable APWM mode
        DL_ECAP_enableAPWMMode(ecap);

        // Configure APWM mode
        DL_ECAP_setAPWMPeriod(ecap, config->apwmModeConfig.periodCount);
        DL_ECAP_setAPWMCompare(ecap, config->apwmModeConfig.compareCount);
        DL_ECAP_setAPWMPolarity(ecap, config->apwmModeConfig.polarity);
    }

    // Configure sync
    DL_ECAP_setSyncInPulseSource(ecap, config->syncConfig.ecapSyncInSel);
    DL_ECAP_setPhaseShiftCount(ecap, config->syncConfig.phaseShiftCount);
    DL_ECAP_setSyncOutMode(ecap, config->syncConfig.syncOutSelect);
    if (config->syncConfig.enableLoadCounter)
    {
        DL_ECAP_enableLoadCounter(ecap);
    }
    else
    {
        DL_ECAP_disableLoadCounter(ecap);
    }

    // Configure interrupts and DMA event
    DL_ECAP_enableInterrupt(ecap, config->interruptsConfig.interruptSourceEnableMask);
    DL_ECAP_setDMASource(ecap, config->interruptsConfig.dmaEventSelect);

    // Configure emulation mode
    DL_ECAP_setEmulationMode(ecap, config->emulationMode);

    // Reset counters and flags if required
    if (config->captureModeConfig.resetCounter)
    {
        DL_ECAP_resetCounters(ecap);
    }

    // Re-arm if required
    if (config->captureModeConfig.reArm)
    {
        DL_ECAP_reArm(ecap);
    }
}
