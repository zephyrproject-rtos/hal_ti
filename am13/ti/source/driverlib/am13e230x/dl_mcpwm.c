/*This file is AUTO GENERATED, DO NOT EDIT manually*/

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

#include "dl_mcpwm.h"

void DL_MCPWM_setEmulationMode(MCPWM_Regs *mcpwm, DL_MCPWM_EMULATION_MODE emulationMode)
{
    DL_Common_updateReg(&mcpwm->TBCTL, ((uint32_t)emulationMode << MCPWM_TBCTL_FREE_SOFT_OFS),
                        MCPWM_TBCTL_FREE_SOFT_MASK);
}

void DL_MCPWM_initParamsSetDefault(DL_MCPWM_Config *config)
{
    if (config == NULL)
    {
        ASSERT(false);
    }

    // Initialize Time Base configuration
    config->timeBaseConfig.enablePhaseShift          = false;
    config->timeBaseConfig.clockDivider              = DL_MCPWM_CLOCK_DIVIDER_1;
    config->timeBaseConfig.counterDirectionAfterSync = DL_MCPWM_COUNT_MODE_UP_AFTER_SYNC;
    config->timeBaseConfig.syncInSource              = DL_MCPWM_SYNC_IN_PULSE_SRC_DISABLE;
    config->timeBaseConfig.syncPerSource             = DL_MCPWM_SYNC_PULSE_DISABLED;
    config->timeBaseConfig.syncOutPulseMode          = DL_MCPWM_SYNC_OUT_PULSE_DISABLED;
    config->timeBaseConfig.emulationMode             = DL_MCPWM_EMULATION_STOP_AFTER_NEXT_TB;
    config->timeBaseConfig.initialCounterValue       = 0x0000;
    config->timeBaseConfig.counterMode               = DL_MCPWM_COUNTER_MODE_UP;
    config->timeBaseConfig.periodValue               = 0x0000;
    config->timeBaseConfig.phaseShiftValue           = 0x0000;

    // Initialize Counter Compare configuration
    config->counterCompareConfig.pwm1CompareAValue = 0x0000;
    config->counterCompareConfig.pwm1CompareBValue = 0x0000;
    config->counterCompareConfig.pwm2CompareAValue = 0x0000;
    config->counterCompareConfig.pwm2CompareBValue = 0x0000;
    config->counterCompareConfig.pwm3CompareAValue = 0x0000;
    config->counterCompareConfig.pwm3CompareBValue = 0x0000;
    config->counterCompareConfig.compareCValue     = 0x0000;
    config->counterCompareConfig.compareDValue     = 0x0000;

    // Initialize Action Qualifier configuration
    config->actionQualifierConfig.aqPwm1A.actionAtZero          = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1A.actionAtPeriod        = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1A.actionAtCountUpCmpA   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1A.actionAtCountDownCmpA = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1A.actionAtCountUpCmpB   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1A.actionAtCountDownCmpB = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1A.pwmSwForceAction      = DL_MCPWM_AQ_SW_FORCE_DISABLED;

    config->actionQualifierConfig.aqPwm1B.actionAtZero          = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1B.actionAtPeriod        = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1B.actionAtCountUpCmpA   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1B.actionAtCountDownCmpA = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1B.actionAtCountUpCmpB   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1B.actionAtCountDownCmpB = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm1B.pwmSwForceAction      = DL_MCPWM_AQ_SW_FORCE_DISABLED;

    config->actionQualifierConfig.aqPwm2A.actionAtZero          = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2A.actionAtPeriod        = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2A.actionAtCountUpCmpA   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2A.actionAtCountDownCmpA = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2A.actionAtCountUpCmpB   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2A.actionAtCountDownCmpB = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2A.pwmSwForceAction      = DL_MCPWM_AQ_SW_FORCE_DISABLED;

    config->actionQualifierConfig.aqPwm2B.actionAtZero          = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2B.actionAtPeriod        = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2B.actionAtCountUpCmpA   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2B.actionAtCountDownCmpA = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2B.actionAtCountUpCmpB   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2B.actionAtCountDownCmpB = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm2B.pwmSwForceAction      = DL_MCPWM_AQ_SW_FORCE_DISABLED;

    config->actionQualifierConfig.aqPwm3A.actionAtZero          = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3A.actionAtPeriod        = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3A.actionAtCountUpCmpA   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3A.actionAtCountDownCmpA = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3A.actionAtCountUpCmpB   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3A.actionAtCountDownCmpB = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3A.pwmSwForceAction      = DL_MCPWM_AQ_SW_FORCE_DISABLED;

    config->actionQualifierConfig.aqPwm3B.actionAtZero          = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3B.actionAtPeriod        = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3B.actionAtCountUpCmpA   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3B.actionAtCountDownCmpA = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3B.actionAtCountUpCmpB   = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3B.actionAtCountDownCmpB = DL_MCPWM_AQ_OUTPUT_NO_CHANGE;
    config->actionQualifierConfig.aqPwm3B.pwmSwForceAction      = DL_MCPWM_AQ_SW_FORCE_DISABLED;

    // Initialize Dead-Band configuration
    config->deadBandConfig.enableRisingEdgeDelayOnPathA  = false;
    config->deadBandConfig.enableFallingEdgeDelayOnPathB = false;
    config->deadBandConfig.enableOutputSwapA             = false;
    config->deadBandConfig.enableOutputSwapB             = false;
    config->deadBandConfig.risingEdgeDelayPolarity       = DL_MCPWM_DB_POLARITY_ACTIVE_HIGH;
    config->deadBandConfig.fallingEdgeDelayPolarity      = DL_MCPWM_DB_POLARITY_ACTIVE_HIGH;
    config->deadBandConfig.risingEdgeDelayInputSource    = DL_MCPWM_DB_INPUT_PWMA;
    config->deadBandConfig.fallingEdgeDelayInputSource   = DL_MCPWM_DB_INPUT_PWMA;
    config->deadBandConfig.fallingEdgeDelayCount         = 0x0000;
    config->deadBandConfig.risingEdgeDelayCount          = 0x0000;

    // Initialize Trip Zone configuration
    config->tripZoneConfig.enableTripZoneMask = 0;
    config->tripZoneConfig.cbcClearEvent      = DL_MCPWM_TZ_CBC_PULSE_CLR_NONE;
    config->tripZoneConfig.actionOnA          = DL_MCPWM_TZ_ACTION_HIGH_Z;
    config->tripZoneConfig.actionOnB          = DL_MCPWM_TZ_ACTION_HIGH_Z;

    // Initialize Event Trigger configuration
    config->eventTriggerConfig.socPulseGenConfig.SOCA.enable      = false;
    config->eventTriggerConfig.socPulseGenConfig.SOCA.eventSource = DL_MCPWM_SOC_DISABLED;
    config->eventTriggerConfig.socPulseGenConfig.SOCA.eventPeriod = 0;

    config->eventTriggerConfig.socPulseGenConfig.SOCB.enable      = false;
    config->eventTriggerConfig.socPulseGenConfig.SOCB.eventSource = DL_MCPWM_SOC_DISABLED;
    config->eventTriggerConfig.socPulseGenConfig.SOCB.eventPeriod = 0;

    config->eventTriggerConfig.socPulseGenConfig.SOCC.enable      = false;
    config->eventTriggerConfig.socPulseGenConfig.SOCC.eventSource = DL_MCPWM_SOC_DISABLED;
    config->eventTriggerConfig.socPulseGenConfig.SOCC.eventPeriod = 0;

    config->eventTriggerConfig.socPulseGenConfig.SOCD.enable      = false;
    config->eventTriggerConfig.socPulseGenConfig.SOCD.eventSource = DL_MCPWM_SOC_DISABLED;
    config->eventTriggerConfig.socPulseGenConfig.SOCD.eventPeriod = 0;

    config->eventTriggerConfig.etConfig.ET1.eventSource = DL_MCPWM_EVT_DISABLED;
    config->eventTriggerConfig.etConfig.ET1.eventPeriod = 0;

    config->eventTriggerConfig.etConfig.ET2.eventSource = DL_MCPWM_EVT_DISABLED;
    config->eventTriggerConfig.etConfig.ET2.eventPeriod = 0;

    config->eventTriggerConfig.interruptGenConfig = 0x0000;

    // Initialize Load Mode configuration
    config->loadModeConfig.pwm1CmpALoadMode         = DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm1CmpBLoadMode         = DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm2CmpALoadMode         = DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm2CmpBLoadMode         = DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm3CmpALoadMode         = DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm3CmpBLoadMode         = DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.cmpCLoadMode             = DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.cmpDLoadMode             = DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm1AaqLoadMode          = DL_MCPWM_AQ_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm1BaqLoadMode          = DL_MCPWM_AQ_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm2AaqLoadMode          = DL_MCPWM_AQ_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm2BaqLoadMode          = DL_MCPWM_AQ_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm3AaqLoadMode          = DL_MCPWM_AQ_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.pwm3BaqLoadMode          = DL_MCPWM_AQ_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.periodLoadMode           = DL_MCPWM_PERIOD_SHADOW_LOAD_ENABLE;
    config->loadModeConfig.fallingEdgeDelayLoadMode = DL_MCPWM_FED_LOAD_ON_CNTR_ZERO;
    config->loadModeConfig.risingEdgeDelayLoadMode  = DL_MCPWM_RED_LOAD_ON_CNTR_ZERO;

    config->loadModeConfig.globalLoadConfig.enableGlobalLoad   = false;
    config->loadModeConfig.globalLoadConfig.enableOneShotMode  = false;
    config->loadModeConfig.globalLoadConfig.triggerEvent       = DL_MCPWM_GL_LOAD_PULSE_CNTR_ZERO;
    config->loadModeConfig.globalLoadConfig.enableOneShotLatch = false;
    config->loadModeConfig.globalLoadConfig.forceLoadEvent     = false;
}

void DL_MCPWM_init(MCPWM_Regs *mcpwm, DL_MCPWM_Config *config)
{
    if (mcpwm == NULL || config == NULL)
    {
        ASSERT(false);
    }

    DL_MCPWM_configureTimeBase(mcpwm, &config->timeBaseConfig);
    DL_MCPWM_configureCounterCompare(mcpwm, &config->counterCompareConfig);

    DL_MCPWM_configureActionQualifierActions(mcpwm, DL_MCPWM_AQ_OUTPUT_1A, &(config->actionQualifierConfig.aqPwm1A));
    DL_MCPWM_configureActionQualifierActions(mcpwm, DL_MCPWM_AQ_OUTPUT_1B, &(config->actionQualifierConfig.aqPwm1B));

    DL_MCPWM_configureActionQualifierActions(mcpwm, DL_MCPWM_AQ_OUTPUT_2A, &(config->actionQualifierConfig.aqPwm2A));
    DL_MCPWM_configureActionQualifierActions(mcpwm, DL_MCPWM_AQ_OUTPUT_2B, &(config->actionQualifierConfig.aqPwm2B));

    DL_MCPWM_configureActionQualifierActions(mcpwm, DL_MCPWM_AQ_OUTPUT_3A, &(config->actionQualifierConfig.aqPwm3A));
    DL_MCPWM_configureActionQualifierActions(mcpwm, DL_MCPWM_AQ_OUTPUT_3B, &(config->actionQualifierConfig.aqPwm3B));

    DL_MCPWM_configureDeadBand(mcpwm, &config->deadBandConfig);
    DL_MCPWM_configureTripZone(mcpwm, &config->tripZoneConfig);
    DL_MCPWM_configureEventTrigger(mcpwm, &config->eventTriggerConfig);
    DL_MCPWM_configureLoadMode(mcpwm, &config->loadModeConfig);
}

void DL_MCPWM_configureTimeBase(MCPWM_Regs *mcpwm, DL_MCPWM_TimeBaseConfig *timeBaseConfig)
{
    // Configure time base counter parameters
    DL_MCPWM_setEmulationMode(mcpwm, timeBaseConfig->emulationMode);
    DL_MCPWM_setTimeBaseCounter(mcpwm, timeBaseConfig->initialCounterValue);
    DL_MCPWM_setTimeBaseCounterMode(mcpwm, timeBaseConfig->counterMode);
    DL_MCPWM_setClockPrescaler(mcpwm, timeBaseConfig->clockDivider);

    // Configure time base period parameters
    DL_MCPWM_setTimeBasePeriodActive(mcpwm, timeBaseConfig->periodValue);
    DL_MCPWM_setTimeBasePeriodShadow(mcpwm, timeBaseConfig->periodValue);

    // Configure sync and emulation parameters
    DL_MCPWM_setSyncPulseSource(mcpwm, timeBaseConfig->syncPerSource);
    DL_MCPWM_setSyncOutPulseMode(mcpwm, timeBaseConfig->syncOutPulseMode);

    // Configure the phase shift parameters
    DL_MCPWM_setSyncInPulseSource(mcpwm, timeBaseConfig->syncInSource);
    if (timeBaseConfig->enablePhaseShift)
    {
        DL_MCPWM_enablePhaseShiftLoad(mcpwm);
    }
    else
    {
        DL_MCPWM_disablePhaseShiftLoad(mcpwm);
    }
    DL_MCPWM_setCountModeAfterSync(mcpwm, timeBaseConfig->counterDirectionAfterSync);
    DL_MCPWM_setPhaseShift(mcpwm, timeBaseConfig->phaseShiftValue);
}

void DL_MCPWM_configureCounterCompare(MCPWM_Regs *mcpwm, DL_MCPWM_CounterCompareConfig *counterCompareConfig)
{
    // Compare PWM 1 A/B values
    DL_MCPWM_setCounterCompareActiveValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_1A, counterCompareConfig->pwm1CompareAValue);
    DL_MCPWM_setCounterCompareShadowValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_1A, counterCompareConfig->pwm1CompareAValue);
    DL_MCPWM_setCounterCompareActiveValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_1B, counterCompareConfig->pwm1CompareBValue);
    DL_MCPWM_setCounterCompareShadowValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_1B, counterCompareConfig->pwm1CompareBValue);

    // Compare PWM 2 A/B values
    DL_MCPWM_setCounterCompareActiveValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_2A, counterCompareConfig->pwm2CompareAValue);
    DL_MCPWM_setCounterCompareShadowValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_2A, counterCompareConfig->pwm2CompareAValue);
    DL_MCPWM_setCounterCompareActiveValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_2B, counterCompareConfig->pwm2CompareBValue);
    DL_MCPWM_setCounterCompareShadowValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_2B, counterCompareConfig->pwm2CompareBValue);

    // Compare PWM 3 A/B values
    DL_MCPWM_setCounterCompareActiveValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_3A, counterCompareConfig->pwm3CompareAValue);
    DL_MCPWM_setCounterCompareShadowValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_3A, counterCompareConfig->pwm3CompareAValue);
    DL_MCPWM_setCounterCompareActiveValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_3B, counterCompareConfig->pwm3CompareBValue);
    DL_MCPWM_setCounterCompareShadowValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_3B, counterCompareConfig->pwm3CompareBValue);

    // Compare C/D values
    DL_MCPWM_setCounterCompareActiveValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_C, counterCompareConfig->compareCValue);
    DL_MCPWM_setCounterCompareShadowValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_C, counterCompareConfig->compareCValue);
    DL_MCPWM_setCounterCompareActiveValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_D, counterCompareConfig->compareDValue);
    DL_MCPWM_setCounterCompareShadowValue(mcpwm, DL_MCPWM_COUNTER_COMPARE_D, counterCompareConfig->compareDValue);
}

void DL_MCPWM_configureActionQualifierActions(MCPWM_Regs *mcpwm, DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE output,
                                              DL_MCPWM_Actions *aqPwm)
{
    // Configure Action Qualifier Actions - active and shadow

    DL_MCPWM_setActionQualifierActionActive(mcpwm, output, aqPwm->actionAtZero, DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    DL_MCPWM_setActionQualifierActionActive(mcpwm, output, aqPwm->actionAtPeriod,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    DL_MCPWM_setActionQualifierActionActive(mcpwm, output, aqPwm->actionAtCountUpCmpA,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    DL_MCPWM_setActionQualifierActionActive(mcpwm, output, aqPwm->actionAtCountDownCmpA,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    DL_MCPWM_setActionQualifierActionActive(mcpwm, output, aqPwm->actionAtCountUpCmpB,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    DL_MCPWM_setActionQualifierActionActive(mcpwm, output, aqPwm->actionAtCountDownCmpB,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

    DL_MCPWM_setActionQualifierActionShadow(mcpwm, output, aqPwm->actionAtZero, DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    DL_MCPWM_setActionQualifierActionShadow(mcpwm, output, aqPwm->actionAtPeriod,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    DL_MCPWM_setActionQualifierActionShadow(mcpwm, output, aqPwm->actionAtCountUpCmpA,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    DL_MCPWM_setActionQualifierActionShadow(mcpwm, output, aqPwm->actionAtCountDownCmpA,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    DL_MCPWM_setActionQualifierActionShadow(mcpwm, output, aqPwm->actionAtCountUpCmpB,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    DL_MCPWM_setActionQualifierActionShadow(mcpwm, output, aqPwm->actionAtCountDownCmpB,
                                            DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

    // Software Force Actions
    DL_MCPWM_setActionQualifierSWAction(mcpwm, output, aqPwm->pwmSwForceAction);
}

void DL_MCPWM_configureDeadBand(MCPWM_Regs *mcpwm, DL_MCPWM_DeadBandConfig *deadBandConfig)
{
    // Configure Dead-Band module
    DL_MCPWM_setDeadBandOutputSwapMode(mcpwm, DL_MCPWM_DB_OUTPUT_A, deadBandConfig->enableOutputSwapA);
    DL_MCPWM_setDeadBandOutputSwapMode(mcpwm, DL_MCPWM_DB_OUTPUT_B, deadBandConfig->enableOutputSwapB);
    DL_MCPWM_setDeadBandDelayMode(mcpwm, DL_MCPWM_DB_RED, deadBandConfig->enableRisingEdgeDelayOnPathA);
    DL_MCPWM_setDeadBandDelayMode(mcpwm, DL_MCPWM_DB_FED, deadBandConfig->enableFallingEdgeDelayOnPathB);
    DL_MCPWM_setDeadBandDelayPolarity(mcpwm, DL_MCPWM_DB_RED, deadBandConfig->risingEdgeDelayPolarity);
    DL_MCPWM_setDeadBandDelayPolarity(mcpwm, DL_MCPWM_DB_FED, deadBandConfig->fallingEdgeDelayPolarity);
    DL_MCPWM_setRisingEdgeDeadBandDelayInput(mcpwm, deadBandConfig->risingEdgeDelayInputSource);
    DL_MCPWM_setFallingEdgeDeadBandDelayInput(mcpwm, deadBandConfig->fallingEdgeDelayInputSource);

    // Configure initial Dead-Band delay counts
    DL_MCPWM_setRisingEdgeDelayCountActive(mcpwm, deadBandConfig->risingEdgeDelayCount);
    DL_MCPWM_setRisingEdgeDelayCountShadow(mcpwm, deadBandConfig->risingEdgeDelayCount);
    DL_MCPWM_setFallingEdgeDelayCountActive(mcpwm, deadBandConfig->fallingEdgeDelayCount);
    DL_MCPWM_setFallingEdgeDelayCountShadow(mcpwm, deadBandConfig->fallingEdgeDelayCount);
}

void DL_MCPWM_configureTripZone(MCPWM_Regs *mcpwm, DL_MCPWM_TripZoneConfig *tripZoneConfig)
{
    // Configure Trip Zone
    DL_MCPWM_enableTripZoneSignals(mcpwm, tripZoneConfig->enableTripZoneMask);
    DL_MCPWM_selectTripZoneCBCEvent(mcpwm, tripZoneConfig->cbcClearEvent);
    DL_MCPWM_setTripZoneAction(mcpwm, DL_MCPWM_TZ_ACTION_EVENT_TZA, tripZoneConfig->actionOnA);
    DL_MCPWM_setTripZoneAction(mcpwm, DL_MCPWM_TZ_ACTION_EVENT_TZB, tripZoneConfig->actionOnB);
}

void DL_MCPWM_configureEventTrigger(MCPWM_Regs *mcpwm, DL_MCPWM_EventTriggerConfig *eventTriggerConfig)
{
    // Configure Event Trigger SOC pulse generator
    if (eventTriggerConfig->socPulseGenConfig.SOCA.enable)
    {
        DL_MCPWM_enableADCTrigger(mcpwm, DL_MCPWM_SOC_A);
    }
    else
    {
        DL_MCPWM_disableADCTrigger(mcpwm, DL_MCPWM_SOC_A);
    }

    if (eventTriggerConfig->socPulseGenConfig.SOCB.enable)
    {
        DL_MCPWM_enableADCTrigger(mcpwm, DL_MCPWM_SOC_B);
    }
    else
    {
        DL_MCPWM_disableADCTrigger(mcpwm, DL_MCPWM_SOC_B);
    }

    if (eventTriggerConfig->socPulseGenConfig.SOCC.enable)
    {
        DL_MCPWM_enableADCTrigger(mcpwm, DL_MCPWM_SOC_C);
    }
    else
    {
        DL_MCPWM_disableADCTrigger(mcpwm, DL_MCPWM_SOC_C);
    }

    if (eventTriggerConfig->socPulseGenConfig.SOCD.enable)
    {
        DL_MCPWM_enableADCTrigger(mcpwm, DL_MCPWM_SOC_D);
    }
    else
    {
        DL_MCPWM_disableADCTrigger(mcpwm, DL_MCPWM_SOC_D);
    }

    DL_MCPWM_setADCTriggerSource(mcpwm, DL_MCPWM_SOC_A, eventTriggerConfig->socPulseGenConfig.SOCA.eventSource);
    DL_MCPWM_setADCTriggerSource(mcpwm, DL_MCPWM_SOC_B, eventTriggerConfig->socPulseGenConfig.SOCB.eventSource);
    DL_MCPWM_setADCTriggerSource(mcpwm, DL_MCPWM_SOC_C, eventTriggerConfig->socPulseGenConfig.SOCC.eventSource);
    DL_MCPWM_setADCTriggerSource(mcpwm, DL_MCPWM_SOC_D, eventTriggerConfig->socPulseGenConfig.SOCD.eventSource);
    DL_MCPWM_setADCTriggerEventPrescale(mcpwm, DL_MCPWM_SOC_A, eventTriggerConfig->socPulseGenConfig.SOCA.eventPeriod);
    DL_MCPWM_setADCTriggerEventPrescale(mcpwm, DL_MCPWM_SOC_B, eventTriggerConfig->socPulseGenConfig.SOCB.eventPeriod);
    DL_MCPWM_setADCTriggerEventPrescale(mcpwm, DL_MCPWM_SOC_C, eventTriggerConfig->socPulseGenConfig.SOCC.eventPeriod);
    DL_MCPWM_setADCTriggerEventPrescale(mcpwm, DL_MCPWM_SOC_D, eventTriggerConfig->socPulseGenConfig.SOCD.eventPeriod);

    // Configure Event Trigger ET1 and ET2
    DL_MCPWM_setEventTriggerSource(mcpwm, DL_MCPWM_ET_1, eventTriggerConfig->etConfig.ET1.eventSource);
    DL_MCPWM_setEventTriggerSource(mcpwm, DL_MCPWM_ET_2, eventTriggerConfig->etConfig.ET2.eventSource);
    DL_MCPWM_setEventTriggerEventPrescale(mcpwm, DL_MCPWM_ET_1, eventTriggerConfig->etConfig.ET1.eventPeriod);
    DL_MCPWM_setEventTriggerEventPrescale(mcpwm, DL_MCPWM_ET_2, eventTriggerConfig->etConfig.ET2.eventPeriod);

    // Configure Interrupt Generation
    DL_MCPWM_enableInterrupt(mcpwm, eventTriggerConfig->interruptGenConfig);
}

void DL_MCPWM_configureLoadMode(MCPWM_Regs *mcpwm, DL_MCPWM_LoadModeConfig *loadModeConfig)
{
    // Configure period Load Mode
    DL_MCPWM_setPeriodLoadMode(mcpwm, loadModeConfig->periodLoadMode);

    // Configure Counter Compare PWM 1/2/3 A/B Load Mode
    DL_MCPWM_setCounterCompareShadowLoadMode(mcpwm, DL_MCPWM_COUNTER_COMPARE_1A, loadModeConfig->pwm1CmpALoadMode);
    DL_MCPWM_setCounterCompareShadowLoadMode(mcpwm, DL_MCPWM_COUNTER_COMPARE_1B, loadModeConfig->pwm1CmpBLoadMode);

    DL_MCPWM_setCounterCompareShadowLoadMode(mcpwm, DL_MCPWM_COUNTER_COMPARE_2A, loadModeConfig->pwm2CmpALoadMode);
    DL_MCPWM_setCounterCompareShadowLoadMode(mcpwm, DL_MCPWM_COUNTER_COMPARE_2B, loadModeConfig->pwm2CmpBLoadMode);

    DL_MCPWM_setCounterCompareShadowLoadMode(mcpwm, DL_MCPWM_COUNTER_COMPARE_3A, loadModeConfig->pwm3CmpALoadMode);
    DL_MCPWM_setCounterCompareShadowLoadMode(mcpwm, DL_MCPWM_COUNTER_COMPARE_3B, loadModeConfig->pwm3CmpBLoadMode);

    // Configure Counter Compare C/D Load Mode
    DL_MCPWM_setCounterCompareShadowLoadMode(mcpwm, DL_MCPWM_COUNTER_COMPARE_C, loadModeConfig->cmpCLoadMode);
    DL_MCPWM_setCounterCompareShadowLoadMode(mcpwm, DL_MCPWM_COUNTER_COMPARE_D, loadModeConfig->cmpDLoadMode);

    // Configure Shadow to active load control of Action Qualifier A/B
    DL_MCPWM_setActionQualifierShadowLoadMode(mcpwm, DL_MCPWM_ACTION_QUALIFIER_1A, loadModeConfig->pwm1AaqLoadMode);
    DL_MCPWM_setActionQualifierShadowLoadMode(mcpwm, DL_MCPWM_ACTION_QUALIFIER_1B, loadModeConfig->pwm1BaqLoadMode);
    DL_MCPWM_setActionQualifierShadowLoadMode(mcpwm, DL_MCPWM_ACTION_QUALIFIER_2A, loadModeConfig->pwm2AaqLoadMode);
    DL_MCPWM_setActionQualifierShadowLoadMode(mcpwm, DL_MCPWM_ACTION_QUALIFIER_2B, loadModeConfig->pwm2BaqLoadMode);
    DL_MCPWM_setActionQualifierShadowLoadMode(mcpwm, DL_MCPWM_ACTION_QUALIFIER_3A, loadModeConfig->pwm3AaqLoadMode);
    DL_MCPWM_setActionQualifierShadowLoadMode(mcpwm, DL_MCPWM_ACTION_QUALIFIER_3B, loadModeConfig->pwm3BaqLoadMode);

    // Configure Dead-Band delay counts Load Mode
    DL_MCPWM_setRisingEdgeDelayCountShadowLoadMode(mcpwm, loadModeConfig->risingEdgeDelayLoadMode);
    DL_MCPWM_setFallingEdgeDelayCountShadowLoadMode(mcpwm, loadModeConfig->fallingEdgeDelayLoadMode);

    DL_MCPWM_GlobalLoadConfig *globalLoadConfig = &(loadModeConfig->globalLoadConfig);

    // Configure Global Load
    if (globalLoadConfig->enableGlobalLoad)
    {
        DL_MCPWM_enableGlobalLoad(mcpwm);
    }
    else
    {
        DL_MCPWM_disableGlobalLoad(mcpwm);
    }
    DL_MCPWM_setGlobalLoadTrigger(mcpwm, globalLoadConfig->triggerEvent);
    if (globalLoadConfig->enableOneShotMode)
    {
        DL_MCPWM_enableGlobalLoadOneShotMode(mcpwm);
    }
    else
    {
        DL_MCPWM_disableGlobalLoadOneShotMode(mcpwm);
    }

    if (globalLoadConfig->enableOneShotLatch)
    {
        // Set One Shot Latch
        DL_MCPWM_setGlobalLoadOneShotLatch(mcpwm);
    }
    else
    {
        // Clear One Shot Latch
        DL_MCPWM_clearGlobalLoadOneShotLatch(mcpwm);
    }

    if (globalLoadConfig->forceLoadEvent)
    {
        // Force Load Event
        DL_MCPWM_forceGlobalLoadOneShotEvent(mcpwm);
    }
}
