
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

#include "dl_adc.h"

void DL_ADC_initParamsSetDefault(DL_ADC_Config *config)
{
    if (config == NULL)
    {
        ASSERT(false);
    }

    // Initialize global configuration
    config->coreConfig.enablePowerAdcCore = true;
    config->coreConfig.clkPrescale        = DL_ADC_CLOCK_DIVIDE_1_0;
    config->coreConfig.offsetTrim         = DL_ADC_OFF_TRIM_0LSB;

    // Initialize SOC configuration
    for (uint8_t i = 0; i < 16; i++)
    {
        config->socConfig[i].channel          = DL_ADC_CH_ADCIN0;
        config->socConfig[i].enableComparator = false;
    }

    // Initialize sequencer configuration
    for (uint8_t i = 0; i < 4; i++)
    {
        config->seqConfig.seqNConfig[i].enableSequencer      = false;
        config->seqConfig.seqNConfig[i].sampleWindow         = DL_SAMPLEWINDOW_MIN;
        config->seqConfig.seqNConfig[i].trigger              = DL_ADC_TRIGGER_SOFTWARE;
        config->seqConfig.seqNConfig[i].socStartNumber       = DL_ADC_SOC_NUMBER0;
        config->seqConfig.seqNConfig[i].enableSampleCapReset = false;
        config->seqConfig.seqNConfig[i].capResetVal          = DL_ADC_SAMPLE_CAP_RESET_SELECT_VREFLO;
    }
    config->seqConfig.endSocNumber   = DL_ADC_SOC_NUMBER15;
    config->seqConfig.seqPreemptMode = DL_ADC_SEQ_PREEMPT_DISABLE;

    // Initialize PPB configuration
    for (uint8_t i = 0; i < 4; i++)
    {
        config->ppbConfig[i].evtFlags          = 0x0;
        config->ppbConfig[i].evtIntFlags       = 0x0;
        config->ppbConfig[i].cbcClear          = false;
        config->ppbConfig[i].tripHiLimit       = 0;
        config->ppbConfig[i].tripLoLimit       = 0;
        config->ppbConfig[i].oversamplingLimit = DL_ADC_PPB_LIMIT_NIL;
        config->ppbConfig[i].shiftVal          = DL_ADC_PPB_SHIFT_0;
        config->ppbConfig[i].compSrc           = DL_ADC_PPB_COMPSOURCE_RESULT;
        config->ppbConfig[i].syncIn            = DL_ADC_SYNCIN_DISABLE;
    }

    // Initialize interrupt configuration
    config->intConfig.interruptCycleDelay = 0;
    config->intConfig.pulseMode           = DL_ADC_PULSE_END_OF_ACQ_WIN;
    for (uint8_t i = 0; i < 4; i++)
    {
        config->intConfig.intNConfig[i].enableContinuousMode = false;
        config->intConfig.intNConfig[i].enableInterrupt      = false;
        config->intConfig.intNConfig[i].trigger              = DL_ADC_SOC_NUMBER0;
    }
    for (uint8_t i = 0; i < 4; i++)
    {
        config->intConfig.dmaIntNConfig[i].enableContinuousMode = false;
        config->intConfig.dmaIntNConfig[i].enableInterrupt      = false;
        config->intConfig.dmaIntNConfig[i].trigger              = DL_ADC_SOC_NUMBER0;
    }
}

void DL_ADC_init(ADC_Regs *adc, DL_ADC_Config *config)
{
    if (adc == NULL || config == NULL)
    {
        ASSERT(false);
    }

    // Global configuration
    DL_ADC_setPrescaler(adc, config->coreConfig.clkPrescale);
    DL_ADC_setOffsetTrim(adc, config->coreConfig.offsetTrim);

    // SOC configuration
    DL_ADC_SOC_NUMBER soc_map[] = {DL_ADC_SOC_NUMBER0,  DL_ADC_SOC_NUMBER1,  DL_ADC_SOC_NUMBER2,  DL_ADC_SOC_NUMBER3,
                                   DL_ADC_SOC_NUMBER4,  DL_ADC_SOC_NUMBER5,  DL_ADC_SOC_NUMBER6,  DL_ADC_SOC_NUMBER7,
                                   DL_ADC_SOC_NUMBER8,  DL_ADC_SOC_NUMBER9,  DL_ADC_SOC_NUMBER10, DL_ADC_SOC_NUMBER11,
                                   DL_ADC_SOC_NUMBER12, DL_ADC_SOC_NUMBER13, DL_ADC_SOC_NUMBER14, DL_ADC_SOC_NUMBER15};

    for (uint8_t i = 0; i < 16; i++)
    {
        DL_ADC_socInit(adc, soc_map[i], &(config->socConfig[i]));
    }

    // PPB configuration
    DL_ADC_PPB_NUMBER ppb_map[] = {DL_ADC_PPB_NUMBER1, DL_ADC_PPB_NUMBER2, DL_ADC_PPB_NUMBER3, DL_ADC_PPB_NUMBER4};

    for (uint8_t i = 0; i < 4; i++)
    {
        DL_ADC_ppbInit(adc, ppb_map[i], &(config->ppbConfig[i]));
    }

    // Interrupt configuration
    DL_ADC_setInterruptPulseMode(adc, config->intConfig.pulseMode);
    DL_ADC_setInterruptCycleDelay(adc, config->intConfig.interruptCycleDelay);

    DL_ADC_INT_NUMBER int_map[] = {DL_ADC_INT_NUMBER1, DL_ADC_INT_NUMBER2, DL_ADC_INT_NUMBER3, DL_ADC_INT_NUMBER4};

    DL_ADC_DMAINT_NUMBER dmaint_map[] = {DL_ADC_DMAINT_NUMBER1, DL_ADC_DMAINT_NUMBER2, DL_ADC_DMAINT_NUMBER3,
                                         DL_ADC_DMAINT_NUMBER4};
    for (uint8_t i = 0; i < 4; i++)
    {
        DL_ADC_interruptInit(adc, int_map[i], &(config->intConfig.intNConfig[i]));
        DL_ADC_dmaInterruptInit(adc, dmaint_map[i], &(config->intConfig.dmaIntNConfig[i]));
    }

    // Sequencer configuration
    DL_ADC_SEQ_NUMBER seq_map[] = {DL_ADC_SEQ_NUMBER1, DL_ADC_SEQ_NUMBER2, DL_ADC_SEQ_NUMBER3, DL_ADC_SEQ_NUMBER4};
    // Configurations common to all sequencers
    DL_ADC_setSeqEndSOC(adc, config->seqConfig.endSocNumber);
    DL_ADC_setSeqPreemptMode(adc, config->seqConfig.seqPreemptMode);

    // Configuration specific to each sequencer block
    for (uint8_t i = 0; i < 4; i++)
    {
        DL_ADC_sequencerInit(adc, seq_map[i], &(config->seqConfig.seqNConfig[i]));
    }

    // Global configuration
    // Power up the ADC analog core after all the submodules are initialized
    if (config->coreConfig.enablePowerAdcCore)
    {
        DL_ADC_powerUp(adc);
    }
    else
    {
        DL_ADC_powerDown(adc);
    }
}

void DL_ADC_socInit(ADC_Regs *adc, DL_ADC_SOC_NUMBER socNumber, DL_ADC_SocConfig *socConfig)
{
    if (adc == NULL || socConfig == NULL)
    {
        ASSERT(false);
    }

    DL_ADC_selectSOCChannel(adc, socNumber, socConfig->channel);
    if (socConfig->enableComparator)
    {
        DL_ADC_enableSOCComparator(adc, socNumber);
    }
    else
    {
        DL_ADC_disableSOCComparator(adc, socNumber);
    }
}

void DL_ADC_ppbInit(ADC_Regs *adc, DL_ADC_PPB_NUMBER ppbNumber, DL_ADC_PpbConfig *ppbConfig)
{
    if (adc == NULL || ppbConfig == NULL)
    {
        ASSERT(false);
    }

    DL_ADC_setPPBTripHighLimit(adc, ppbNumber, ppbConfig->tripHiLimit);
    DL_ADC_setPPBTripLowLimit(adc, ppbNumber, ppbConfig->tripLoLimit);
    DL_ADC_setPPBOversamplingLimit(adc, ppbNumber, ppbConfig->oversamplingLimit);
    DL_ADC_setPPBShiftValue(adc, ppbNumber, ppbConfig->shiftVal);
    DL_ADC_selectPPBCompareSource(adc, ppbNumber, ppbConfig->compSrc);
    DL_ADC_selectPPBSyncSource(adc, ppbNumber, ppbConfig->syncIn);

    if (ppbConfig->cbcClear)
    {
        DL_ADC_enablePPBEventCBCClear(adc, ppbNumber);
    }
    else
    {
        DL_ADC_disablePPBEventCBCClear(adc, ppbNumber);
    }

    uint32_t enableEvtFlags = (ppbConfig->evtFlags) & (DL_ADC_EVT_TRIPHI | DL_ADC_EVT_TRIPLO | DL_ADC_EVT_NLIMIT);
    DL_ADC_enablePPBEvent(adc, ppbNumber, enableEvtFlags);

    uint32_t disableEvtFlags = (~(ppbConfig->evtFlags)) & (DL_ADC_EVT_TRIPHI | DL_ADC_EVT_TRIPLO | DL_ADC_EVT_NLIMIT);
    DL_ADC_disablePPBEvent(adc, ppbNumber, disableEvtFlags);

    uint32_t enableEvtIntFlags = (ppbConfig->evtIntFlags) & (DL_ADC_EVT_TRIPHI | DL_ADC_EVT_TRIPLO | DL_ADC_EVT_NLIMIT);
    DL_ADC_enablePPBEventInterrupt(adc, ppbNumber, enableEvtIntFlags);

    uint32_t disableEvtIntFlags =
        (~(ppbConfig->evtIntFlags)) & (DL_ADC_EVT_TRIPHI | DL_ADC_EVT_TRIPLO | DL_ADC_EVT_NLIMIT);
    DL_ADC_disablePPBEventInterrupt(adc, ppbNumber, disableEvtIntFlags);
}

void DL_ADC_interruptInit(ADC_Regs *adc, DL_ADC_INT_NUMBER intNumber, DL_ADC_IntNConfig *intNConfig)
{
    if (adc == NULL || intNConfig == NULL)
    {
        ASSERT(false);
    }

    DL_ADC_setInterruptSource(adc, intNumber, intNConfig->trigger);

    if (intNConfig->enableContinuousMode)
    {
        DL_ADC_enableContinuousMode(adc, intNumber);
    }
    else
    {
        DL_ADC_disableContinuousMode(adc, intNumber);
    }

    if (intNConfig->enableInterrupt)
    {
        DL_ADC_enableInterrupt(adc, intNumber);
    }
    else
    {
        DL_ADC_disableInterrupt(adc, intNumber);
    }
}

void DL_ADC_dmaInterruptInit(ADC_Regs *adc, DL_ADC_DMAINT_NUMBER dmaIntNumber, DL_ADC_IntNConfig *dmaIntNConfig)
{
    if (adc == NULL || dmaIntNConfig == NULL)
    {
        ASSERT(false);
    }

    DL_ADC_setDMAInterruptSource(adc, dmaIntNumber, dmaIntNConfig->trigger);

    if (dmaIntNConfig->enableContinuousMode)
    {
        DL_ADC_enableDMAContinuousMode(adc, dmaIntNumber);
    }
    else
    {
        DL_ADC_disableDMAContinuousMode(adc, dmaIntNumber);
    }

    if (dmaIntNConfig->enableInterrupt)
    {
        DL_ADC_enableDMAInterrupt(adc, dmaIntNumber);
    }
    else
    {
        DL_ADC_disableDMAInterrupt(adc, dmaIntNumber);
    }
}

void DL_ADC_sequencerInit(ADC_Regs *adc, DL_ADC_SEQ_NUMBER seqNumber, DL_ADC_SeqNConfig *seqNConfig)
{
    if (adc == NULL || seqNConfig == NULL)
    {
        ASSERT(false);
    }

    DL_ADC_setupSequencer(adc, seqNumber, seqNConfig->sampleWindow, seqNConfig->trigger, seqNConfig->socStartNumber);

    if (seqNConfig->enableSampleCapReset)
    {
        DL_ADC_enableSampleCapReset(adc, seqNumber);
    }
    else
    {
        DL_ADC_disableSampleCapReset(adc, seqNumber);
    }
    DL_ADC_selectSampleCAPResetValue(adc, seqNumber, seqNConfig->capResetVal);

    if (seqNConfig->enableSequencer)
    {
        DL_ADC_enableSequencer(adc, seqNumber);
    }
    else
    {
        DL_ADC_disableSequencer(adc, seqNumber);
    }
}
