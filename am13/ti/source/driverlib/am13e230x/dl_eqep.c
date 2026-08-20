
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

#include "dl_eqep.h"

void DL_EQEP_setCompareConfig(EQEP_Regs *eqep, uint16_t config, uint32_t compareValue, uint16_t cycles)
{
    uint16_t regValue;

    /* Verify the input arguments */
    ASSERT(cycles <= (EQEP_QPOSCTL_PCSPW_MASK + 1U));

    /* Set the compare match value */
    eqep->QPOSCMP = compareValue;

    /* Set the shadow register settings and pulse width. */
    regValue = (config & (uint16_t)(EQEP_QPOSCTL_PCSHDW_MASK | EQEP_QPOSCTL_PCLOAD_MASK)) | (cycles - 1U);

    eqep->QPOSCTL =
        (eqep->QPOSCTL & ~(EQEP_QPOSCTL_PCSPW_MASK | EQEP_QPOSCTL_PCLOAD_MASK | EQEP_QPOSCTL_PCSHDW_MASK)) | regValue;

    // Set position compare sync-output mode
    regValue = config & (uint16_t)(EQEP_QDECCTL_SOEN_MASK | EQEP_QDECCTL_SPSEL_MASK);

    eqep->QDECCTL = (eqep->QDECCTL & ~(EQEP_QDECCTL_SOEN_MASK | EQEP_QDECCTL_SPSEL_MASK)) | regValue;
}

void DL_EQEP_setInputPolarity(EQEP_Regs *eqep, bool invertQEPA, bool invertQEPB, bool invertIndex, bool invertStrobe)
{
    /* Configure QEPA signal polarity */
    if (invertQEPA)
    {
        eqep->QDECCTL |= EQEP_QDECCTL_QAP_MASK;
    }
    else
    {
        eqep->QDECCTL &= ~EQEP_QDECCTL_QAP_MASK;
    }

    /* Configure QEPB signal polarity */
    if (invertQEPB)
    {
        eqep->QDECCTL |= EQEP_QDECCTL_QBP_MASK;
    }
    else
    {
        eqep->QDECCTL &= ~EQEP_QDECCTL_QBP_MASK;
    }

    /* Configure index signal polarity */
    if (invertIndex)
    {
        eqep->QDECCTL |= EQEP_QDECCTL_QIP_MASK;
    }
    else
    {
        eqep->QDECCTL &= ~EQEP_QDECCTL_QIP_MASK;
    }

    /* Configure strobe signal polarity */
    if (invertStrobe)
    {
        eqep->QDECCTL |= EQEP_QDECCTL_QSP_MASK;
    }
    else
    {
        eqep->QDECCTL &= ~EQEP_QDECCTL_QSP_MASK;
    }
}

void DL_EQEP_initParamsSetDefault(DL_EQEP_Config *config)
{
    if (config == NULL)
    {
        ASSERT(false);
    }

    // Initialize emulation mode
    config->emulationMode = DL_EQEP_EMULATIONMODE_STOPIMMEDIATELY;

    // Initialize input configuration
    config->inputConfig.qepASrc      = DL_EQEP_SOURCE_INPUTXBAR;
    config->inputConfig.qepBSrc      = DL_EQEP_SOURCE_INPUTXBAR;
    config->inputConfig.qepIndexSrc  = DL_EQEP_SOURCE_INPUTXBAR;
    config->inputConfig.qepStrobeSrc = DL_EQEP_STROBE_FROM_GPIO;

    // Initialize QMA configuration
    config->qmaConfig.qmaMode = DL_EQEP_QMA_MODE_BYPASS;

    // Initialize QDU configuration
    config->qduConfig.enableDirectionChangeDuringIndex = false;
    config->qduConfig.invertQEPA                       = false;
    config->qduConfig.invertQEPB                       = false;
    config->qduConfig.invertIndex                      = false;
    config->qduConfig.invertStrobe                     = false;
    config->qduConfig.positionCounterSource            = DL_EQEP_CONFIG_QUADRATURE;
    config->qduConfig.externalClockRate                = DL_EQEP_CONFIG_2X_RESOLUTION;
    config->qduConfig.swap                             = DL_EQEP_CONFIG_NO_SWAP;
    config->qduConfig.indexGate                        = DL_EQEP_CONFIG_IGATE_DISABLE;

    // Initialize PCCU configuration
    config->pccuConfig.positionCounterResetMode                                 = DL_EQEP_POSITION_RESET_IDX;
    config->pccuConfig.maxPositionCount                                         = 0;
    config->pccuConfig.positionCount                                            = 0;
    config->pccuConfig.positionLatchConfig.latchModeConfig                      = DL_EQEP_LATCH_CNT_READ_BY_CPU;
    config->pccuConfig.positionLatchConfig.strobeEventLatchConfig               = DL_EQEP_LATCH_RISING_STROBE;
    config->pccuConfig.positionLatchConfig.indexEventLatchConfig                = DL_EQEP_LATCH_RISING_INDEX;
    config->pccuConfig.positionInitializationConfig.initMode                    = DL_EQEP_INIT_DO_NOTHING;
    config->pccuConfig.positionInitializationConfig.initialPositionCount        = 0;
    config->pccuConfig.positionInitializationConfig.swInitializePositionCounter = false;
    config->pccuConfig.positionCompareConfig.positionCompareValue               = 0;
    config->pccuConfig.positionCompareConfig.enablePositionCompare              = false;
    config->pccuConfig.positionCompareConfig.shadowLoadConfig                   = DL_EQEP_COMPARE_NO_SHADOW;
    config->pccuConfig.positionCompareConfig.syncOutConfig                      = DL_EQEP_COMPARE_NO_SYNC_OUT;
    config->pccuConfig.positionCompareConfig.syncOutPolarity                    = false;
    config->pccuConfig.positionCompareConfig.syncOutPulseWidthcycles            = 0;
    config->pccuConfig.enablePositionCounterOrReset                             = false;

    // Initialize QCAP configuration
    config->qcapConfig.enableCapture          = false;
    config->qcapConfig.capPrescale            = DL_EQEP_CAPTURE_CLK_DIV_1;
    config->qcapConfig.evntPrescale           = DL_EQEP_UNIT_POS_EVNT_DIV_1;
    config->qcapConfig.utimeConfig.enable     = false;
    config->qcapConfig.utimeConfig.unitPeriod = 0;

    // Initialize QWDOG configuration
    config->qwdogConfig.enable            = false;
    config->qwdogConfig.initialTimerValue = 0;
    config->qwdogConfig.period            = 0;

    // Initialize interrupt configuration
    config->interruptConfig.intFlags = 0x0000;
}

void DL_EQEP_init(EQEP_Regs *eqep, DL_EQEP_Config *config)
{
    if (eqep == NULL || config == NULL)
    {
        ASSERT(false);
    }

    // Disable EQEP position counter/reset before all configuration
    DL_EQEP_disableModule(eqep);

    DL_EQEP_setEmulationMode(eqep, config->emulationMode);

    // Input source configuration
    DL_EQEP_SOURCE_SELECT eqepSourceSelect;
    eqepSourceSelect.sourceA     = config->inputConfig.qepASrc;
    eqepSourceSelect.sourceB     = config->inputConfig.qepBSrc;
    eqepSourceSelect.sourceIndex = config->inputConfig.qepIndexSrc;
    DL_EQEP_selectSource(eqep, eqepSourceSelect);
    DL_EQEP_setStrobeSource(eqep, config->inputConfig.qepStrobeSrc);

    // QMA configuration
    DL_EQEP_setQMAModuleMode(eqep, config->qmaConfig.qmaMode);

    // QDU configuration
    if (config->qduConfig.enableDirectionChangeDuringIndex)
    {
        DL_EQEP_enableDirectionChangeDuringIndex(eqep);
    }
    else
    {
        DL_EQEP_disableDirectionChangeDuringIndex(eqep);
    }

    DL_EQEP_setInputPolarity(eqep, config->qduConfig.invertQEPA, config->qduConfig.invertQEPB,
                             config->qduConfig.invertIndex, config->qduConfig.invertStrobe);

    uint16_t decoderConfig  = 0x0000;
    decoderConfig          |= config->qduConfig.positionCounterSource;
    decoderConfig          |= config->qduConfig.externalClockRate;
    decoderConfig          |= config->qduConfig.swap;
    decoderConfig          |= config->qduConfig.indexGate;
    DL_EQEP_setDecoderConfig(eqep, decoderConfig);

    // PCCU configuration
    DL_EQEP_setPositionCounterConfig(eqep, config->pccuConfig.positionCounterResetMode,
                                     config->pccuConfig.maxPositionCount);
    DL_EQEP_setPosition(eqep, config->pccuConfig.positionCount);

    DL_EQEP_setLatchMode(eqep, config->pccuConfig.positionLatchConfig.latchModeConfig |
                                   config->pccuConfig.positionLatchConfig.strobeEventLatchConfig |
                                   config->pccuConfig.positionLatchConfig.indexEventLatchConfig);

    DL_EQEP_setPositionInitMode(eqep, config->pccuConfig.positionInitializationConfig.initMode);
    DL_EQEP_setInitialPosition(eqep, config->pccuConfig.positionInitializationConfig.initialPositionCount);
    if (config->pccuConfig.positionInitializationConfig.swInitializePositionCounter)
    {
        DL_EQEP_setSWPositionInit(eqep, true);
    }
    else
    {
        DL_EQEP_setSWPositionInit(eqep, false);
    }

    DL_EQEP_setCompareConfig(eqep,
                             config->pccuConfig.positionCompareConfig.shadowLoadConfig |
                                 config->pccuConfig.positionCompareConfig.syncOutConfig,
                             config->pccuConfig.positionCompareConfig.positionCompareValue,
                             config->pccuConfig.positionCompareConfig.syncOutPulseWidthcycles);
    // Alternately use DL_EQEP_setComparePulseWidth
    // Note: positionCompareConfig.syncOutPolarity is unused.
    //      SyncOut polarity is Active High by default

    if (config->pccuConfig.positionCompareConfig.enablePositionCompare)
    {
        DL_EQEP_enableCompare(eqep);
    }
    else
    {
        DL_EQEP_disableCompare(eqep);
    }

    // QCAP configuration
    DL_EQEP_setCaptureConfig(eqep, config->qcapConfig.capPrescale, config->qcapConfig.evntPrescale);

    if (config->qcapConfig.enableCapture)
    {
        DL_EQEP_enableCapture(eqep);
    }
    else
    {
        DL_EQEP_disableCapture(eqep);
    }

    if (config->qcapConfig.utimeConfig.enable)
    {
        DL_EQEP_enableUnitTimer(eqep, config->qcapConfig.utimeConfig.unitPeriod);
    }
    else
    {
        DL_EQEP_disableUnitTimer(eqep);
    }

    // QWDOG configuration
    DL_EQEP_setWatchdogTimerValue(eqep, config->qwdogConfig.initialTimerValue);

    if (config->qwdogConfig.enable)
    {
        DL_EQEP_enableWatchdog(eqep, config->qwdogConfig.period);
    }
    else
    {
        DL_EQEP_disableWatchdog(eqep);
    }

    // Interrupt configuration
    DL_EQEP_disableInterrupt(eqep, 0xFFFF);
    DL_EQEP_enableInterrupt(eqep, config->interruptConfig.intFlags);

    // Enable EQEP position counter after all configuration
    if (config->pccuConfig.enablePositionCounterOrReset)
    {
        DL_EQEP_enableModule(eqep);
    }
    else
    {
        DL_EQEP_disableModule(eqep);
    }
}
