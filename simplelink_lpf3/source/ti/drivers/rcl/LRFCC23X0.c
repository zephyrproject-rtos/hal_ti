/*
 * Copyright (c) 2021-2024, Texas Instruments Incorporated
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
/*
 *  ======== LRFCC23X0.c ========
 */

#include <stdint.h>
#include <stdlib.h>

#include <ti/drivers/rcl/LRF.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/log/Log.h>
#include <ti/drivers/dpl/HwiP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm32.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe32.h)
#include DeviceFamily_constructPath(inc/pbe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/rfe_common_ram_regs.h)


static uint32_t LRF_findPllMBase(uint32_t frequency);
static uint32_t countLeadingZeros(uint16_t value);
static uint32_t LRF_findCalM(uint32_t frequency, uint32_t prediv);
static uint32_t LRF_findFoff(int32_t frequencyOffset, uint32_t invSynthFreq);
static void LRF_programShape(const LRF_TxShape *txShape, uint32_t deviation, uint32_t invSynthFreq);
static uint32_t LRF_findLog2Bde1(uint32_t demmisc3);
static uint32_t LRF_programPQ(uint32_t pllMBase);
static void LRF_programCMixN(int32_t rxIntFrequency, uint32_t invSynthFreq);
static void LRF_applyTrim(const LRF_TrimDef *trimDef, const LRF_SwConfig *swConfig);
static void LRF_updateTrim(const LRF_TrimDef *trimDef, const LRF_SwConfig *swConfig);
static void LRF_setTrimCommon(const LRF_TrimDef *trimDef, const LRF_SwConfig *swConfig);
static void LRF_setTemperatureTrim(const LRF_TrimDef *trimDef);
static void LRF_temperatureCompensateTrim(const LRF_TrimDef *trimDef);
static uint32_t LRF_findExtTrim1TrimAdjustment(uint32_t temperatureDiff, uint32_t tempThreshFactor, uint32_t maxAdjustment);
static int32_t LRF_findExtTrim0TrimAdjustment(int32_t temperature, int32_t tempCompFactor, int32_t offset);
static uint32_t LRF_scaleFreqWithHFXTOffset(uint32_t frequency);
static void LRF_writeFifoPtr(uint32_t value, uintptr_t regAddr);
static void LRF_writeFifoPtrs(uint32_t value, uintptr_t regAddr0, uintptr_t regAddr1);

uint32_t swParamList[sizeof(LRF_SwParam)/sizeof(uint32_t)];
const size_t swParamListSz = sizeof(LRF_SwParam);

static struct {
    const LRF_TOPsmImage   *pbeLoaded;
    const LRF_TOPsmImage   *mceLoaded;
    const LRF_TOPsmImage   *rfeLoaded;
    uint16_t                phyFeatures;
    LRF_TxPowerTable_Entry  currentTxPower;
    LRF_TxPowerTable_Entry  rawTxPower;
} lrfPhyState = {0};

/* Required time from enabling refsys to synth programming */
#define LRF_REFSYS_ENABLE_TIME RCL_SCHEDULER_SYSTIM_US(30)

/* Status to tell if the RX FIFO is already in a deallocated state (SRP and RP being the same) */
static bool rxFifoDeallocated = true;

LRF_SetupResult LRF_setupRadio(const LRF_Config *lrfConfig, uint16_t phyFeatures, LRF_RadioState lrfState)
{
    enum {
        trimNoUpdate,
        trimPartialUpdate,
        trimFullUpdate
    } trimUpdate = trimNoUpdate;
    LRF_SetupResult result = SetupResult_Ok;

    if (lrfPhyState.pbeLoaded != lrfConfig->pbeImage || lrfState < RadioState_ImagesLoaded)
    {
        result = LRF_loadImage(lrfConfig->pbeImage, LRFD_PBERAM_BASE);
        lrfPhyState.pbeLoaded = lrfConfig->pbeImage;
    }
    if ((result == SetupResult_Ok) &&
        (lrfPhyState.mceLoaded != lrfConfig->mceImage || lrfState < RadioState_ImagesLoaded))
    {
        result = LRF_loadImage(lrfConfig->mceImage, LRFD_MCERAM_BASE);
        lrfPhyState.mceLoaded = lrfConfig->mceImage;
    }
    if ((result == SetupResult_Ok) &&
        (lrfPhyState.rfeLoaded != lrfConfig->rfeImage || lrfState < RadioState_ImagesLoaded))
    {
        result = LRF_loadImage(lrfConfig->rfeImage, LRFD_RFERAM_BASE);
        lrfPhyState.rfeLoaded = lrfConfig->rfeImage;
    }

    if ((result == SetupResult_Ok) && (lrfConfig->regConfigList != NULL))
    {
        LRF_ApplySettingsBase includeBase;

        if (lrfState < RadioState_Configured)
        {
            includeBase = LRF_ApplySettings_IncludeBase;
            Log_printf(RclCore, Log_VERBOSE, "Performing full setup");
            trimUpdate = trimFullUpdate;
        }
        else
        {
            includeBase = LRF_ApplySettings_NoBase;
            if (phyFeatures != lrfPhyState.phyFeatures)
            {
                Log_printf(RclCore, Log_VERBOSE, "Changing PHY features");
                trimUpdate = trimPartialUpdate;
            }
        }
        if (includeBase == LRF_ApplySettings_IncludeBase || phyFeatures != lrfPhyState.phyFeatures)
        {
            LRF_ApplySettingsState settingsState;
            /* Initialize setup state */
            lrfPhyState.phyFeatures = phyFeatures;
            LRF_initSettingsState(&settingsState, includeBase, phyFeatures);
            for (uint32_t i = 0; i < lrfConfig->regConfigList->numEntries; i++)
            {
                LRF_ConfigWord *config = lrfConfig->regConfigList->entries[i];

                result = LRF_applySettings(config, &settingsState, LRF_SETTINGS_BUFFER_UNLIMITED);

                if (result != SetupResult_Ok)
                {
                    break;
                }
            }
        }
        /* Invalidate RSSI value to cover the case in which no RX has run before. */
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_RSSI) = LRF_RSSI_INVALID;
        /* Set PBE to writing FIFO commands to FCMD */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FCMD) & 0x0FFF) >> 2;
    }

    if (result == SetupResult_Ok)
    {
        LRF_SwParam *swParam = (LRF_SwParam *) swParamList;

        if (swParam->swConfig == NULL)
        {
            result = SetupResult_ErrorSwConfig;
        }
        else
        {
            if (trimUpdate == trimFullUpdate)
            {
                LRF_applyTrim(swParam->trimDef, swParam->swConfig);
            }
            else if (trimUpdate == trimPartialUpdate)
            {
                LRF_updateTrim(swParam->trimDef, swParam->swConfig);
            }
            else
            {
                LRF_setTemperatureTrim(swParam->trimDef);
            }
        }
    }
    return result;
}

bool LRF_imagesNeedUpdate(const LRF_Config *lrfConfig)
{
    return ((lrfPhyState.pbeLoaded != lrfConfig->pbeImage && lrfConfig->pbeImage != NULL) ||
            (lrfPhyState.mceLoaded != lrfConfig->mceImage && lrfConfig->mceImage != NULL) ||
            (lrfPhyState.rfeLoaded != lrfConfig->rfeImage && lrfConfig->rfeImage != NULL));
}

static void LRF_applyTrim(const LRF_TrimDef *trimDef, const LRF_SwConfig *swConfig)
{

    if (trimDef != NULL)
    {
#ifdef DeviceFamily_CC27XX
        if (trimDef->revision >= LRF_TRIM_VERSION_CORRECT_AMOUNT_OF_PA_TRIMS_CC27XX)
        {
            HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_PATRIM01) = trimDef->trim0.pa2trim01;
            HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_PATRIM23) = trimDef->trim4.pa2trim23;
        }
        else
        {
            /* Workaround: Write trim0.pa2trim01 to all trim fields for revisions where all trim fields are not available in apptrims */
            uint16_t paTrim = trimDef->trim0.pa2trim01;
            HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_PATRIM01) = (paTrim << RFE_COMMON_RAM_PATRIM01_VAL1_S) | (paTrim << RFE_COMMON_RAM_PATRIM01_VAL0_S);
            HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_PATRIM23) = (paTrim << RFE_COMMON_RAM_PATRIM23_VAL3_S) | (paTrim << RFE_COMMON_RAM_PATRIM23_VAL2_S);
        }
#else
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_PA0)        = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_PA0) | trimDef->trim0.pa0;
#endif
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_ATSTREFH)   = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_ATSTREFH) | trimDef->trim0.atstRefH;

        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_LNA)        = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_LNA) | trimDef->trim1.lna;
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) | trimDef->trim1.ifampRfLdo;

#ifdef DeviceFamily_CC27XX
        /* DCOLDO0 Workaround: DCOLDO0:FIRSTTRIM is hardcoded to 8U and DCOLDO0:SECONDTRIM is increased by 10 for CC27XX state B devices (see: RCL-616)
         * ASSUMPTION: AppTrims revision on CC27XX state C devices is not smaller than 7
         */
        if (trimDef->revision >= LRF_TRIM_VERSION_STATE_C_TRIM_WORKAROUND_CC27XX)
        {
            HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0) | trimDef->trim2.dcoLdo0;
        }
        else
        {
            uint32_t trimDcoldo0Val = trimDef->trim2.dcoLdo0;
            uint32_t secondTrimVal = (trimDcoldo0Val & LRFDRFE_DCOLDO0_SECONDTRIM_M) >> LRFDRFE_DCOLDO0_SECONDTRIM_S;

            /* Invert bit 3 and 5 to decode the SECONDTRIM value */
            uint32_t secondTrimValDecoded = secondTrimVal ^ LRF_TRIM_DCOLDO0_SECONDTRIM_CODED_BITS_MASK_STATE_B_DCOLDO_WORKAROUND_CC27XX;
            uint32_t newSecondTrimVal = secondTrimValDecoded + LRF_TRIM_DCOLDO0_SECONDTRIM_INC_STATE_B_DCOLDO_WORKAROUND_CC27XX;

            /* DCOLDO0[13:8]SECONDTRIM is saturated at 63U */
            if (newSecondTrimVal > LRF_TRIM_DCOLDO0_SECONDTRIM_MAX_STATE_B_DCOLDO_WORKAROUND_CC27XX)
            {
                newSecondTrimVal = LRF_TRIM_DCOLDO0_SECONDTRIM_MAX_STATE_B_DCOLDO_WORKAROUND_CC27XX;
            }

            /* Invert bit 3 and 5 to encode the SECONDTRIM value */
            uint32_t newSecondTrimValCoded = newSecondTrimVal ^ LRF_TRIM_DCOLDO0_SECONDTRIM_CODED_BITS_MASK_STATE_B_DCOLDO_WORKAROUND_CC27XX;

            /* Hardcode the FIRSTTRIM to 8U */
            trimDcoldo0Val = (trimDcoldo0Val & ~LRFDRFE_DCOLDO0_FIRSTTRIM_M) | (LRF_TRIM_DCOLDO0_FIRSTTRIM_VALUE_STATE_B_DCOLDO_WORKAROUND_CC27XX << LRFDRFE_DCOLDO0_FIRSTTRIM_S);

            trimDcoldo0Val = (trimDcoldo0Val & ~LRFDRFE_DCOLDO0_SECONDTRIM_M) | (newSecondTrimValCoded << LRFDRFE_DCOLDO0_SECONDTRIM_S);
            HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0) | trimDcoldo0Val;
        }
#else
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0)    = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0) | trimDef->trim2.dcoLdo0;
#endif
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCALDO)  = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCALDO) | trimDef->trim2.ifadcAldo;
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCDLDO)  = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCDLDO) | trimDef->trim2.ifadcDldo;

        /* DEMIQMC0 has no fields not to be trimmed */
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMIQMC0)   =  trimDef->trim4.demIQMC0;

        /* Write trim to shadow registers */
        HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_IFAMPRFLDODEFAULT) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) & LRFDRFE_IFAMPRFLDO_TRIM_M;

        LRF_setTrimCommon(trimDef, swConfig);
        LRF_temperatureCompensateTrim(trimDef);
    }
}

static void LRF_updateTrim(const LRF_TrimDef *trimDef, const LRF_SwConfig *swConfig)
{
    if (trimDef != NULL)
    {
        /* Remove trim fields from registers with BW variations */
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCQUANT)    = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCQUANT) & (~(LRFDRFE_IFADCQUANT_QUANTTHR_M));
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC0)        = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC0) & (~(LRFDRFE_IFADC0_AAFCAP_M | LRFDRFE_IFADC0_INT2ADJ_M | LRFDRFE_IFADC0_DITHEREN_M | LRFDRFE_IFADC0_DITHERTRIM_M));
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC1)        = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC1) & (~(LRFDRFE_IFADC1_TRIM_M | LRFDRFE_IFADC1_NRZ_M));
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCLF)       = 0; /* All fields are trimmed so everything needs to be cleared */
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO)    = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) & (~LRFDRFE_IFAMPRFLDO_AAFCAP_M);

        LRF_setTrimCommon(trimDef, swConfig);
        LRF_setTemperatureTrim(trimDef);
    }
}

static void LRF_setTrimCommon(const LRF_TrimDef *trimDef, const LRF_SwConfig *swConfig)
{
    uint8_t bwIndex = 0;
    uint8_t bwIndexDither = 0;
    uint8_t revision = trimDef->revision;
    if (revision >= LRF_TRIM_MIN_VERSION_FULL_FEATURES)
    {
        bwIndex = swConfig->bwIndex;
        bwIndexDither = swConfig->bwIndexDither;
    }
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCQUANT) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCQUANT) | trimDef->trimVariant[bwIndex].ifadcQuant;
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC0)     = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC0) | trimDef->trimVariant[bwIndex].ifadc0;
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC1)     = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC1) | trimDef->trimVariant[bwIndex].ifadc1;
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCLF)    = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCLF) | trimDef->trimVariant[bwIndex].ifadclf;

    if (revision >= LRF_TRIM_MIN_VERSION_FULL_FEATURES)
    {
        /* Set AAFCAP according to BW */
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) | trimDef->trim4.ifamprfldo[bwIndex];

        if (bwIndexDither != bwIndex)
        {
            /* Use different setting of dither settings compared to the rest of the IFADC0 register. */
            HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC0) = (HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADC0) & ~(LRFDRFE_IFADC0_DITHEREN_M | LRFDRFE_IFADC0_DITHERTRIM_M)) |
                (trimDef->trimVariant[bwIndexDither].ifadc0 & (LRFDRFE_IFADC0_DITHEREN_M | LRFDRFE_IFADC0_DITHERTRIM_M));
        }
    }
}

static void LRF_setTemperatureTrim(const LRF_TrimDef *trimDef)
{
    if (trimDef != NULL)
    {
        /* Remove trim fields from registers with temperature compensation */
        HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOF) = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOF) & (~RFE_COMMON_RAM_DIVLDOF_VOUTTRIM_M);
        HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOI) = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOI) & (~RFE_COMMON_RAM_DIVLDOI_VOUTTRIM_M);
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_TDCLDO)              = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_TDCLDO) & (~LRFDRFE_TDCLDO_VOUTTRIM_M);
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCO)                 = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCO) & (~LRFDRFE_DCO_TAILRESTRIM_M);

        LRF_temperatureCompensateTrim(trimDef);
    }
}

/* Number of shifts in temperature compensation for fields in lrfdrfeExtTrim1 */
#define LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP 4U
/* Adjustment per step of DIVLDO at lowest temperature */
#define LRF_DIVLDO_LOW_TEMP_ADJ_FACTOR 10U
/* Adjustment per step of DIVLDO at highest temperature */
#define LRF_DIVLDO_HIGH_TEMP_ADJ_FACTOR 10U
/* Adjustment per step of TDCLDO at lowest temperature */
#define LRF_TDCLDO_LOW_TEMP_ADJ_FACTOR 10U
/* Adjustment per step of TDCLDO at highest temperature */
#define LRF_TDCLDO_HIGH_TEMP_ADJ_FACTOR 10U
/* Adjustment per step of RTRIM at lowest temperature */
#define LRF_RTRIM_LOW_TEMP_ADJ_FACTOR 1U
/* Adjustment per step of RTRIM at highest temperature */
#define LRF_RTRIM_HIGH_TEMP_ADJ_FACTOR 1U
/* Maximum allowed value (saturation value) for RTRIM, except if RTRIM value in FCFG is above this level */
#define LRF_DEFAULT_RTRIM_MAX 12U

/* Number of shifts in temperature compensation for fields in lrfdrfeExtTrim0 */
#define LRF_EXTTRIM0_TEMPERATURE_SCALE_EXP 7

/* Lowest temperature supported */
#define LRF_TEMPERATURE_MIN (-40)
/* Highest temperature supported */
#define LRF_TEMPERATURE_MAX 125
/* Nominal temperature for offset definitions */
#define LRF_TEMPERATURE_NOM 25

/* Bit masks and positions in SPARE0 and SPARE1 */
/* RFE_SPARE0: Fast AGC only */
#define RFE_SPARE0_LOW_GAIN_BM  0x000F
#define RFE_SPARE0_LOW_GAIN     0
#define RFE_SPARE0_HIGH_GAIN_BM 0x00F0
#define RFE_SPARE0_HIGH_GAIN    4
/* RFE_SPARE1: Fast AGC: Threshold. Standard AGC: Magnitude */
/* These fields have the same position in the register */
#define RFE_SPARE1_AGC_VALUE_BM 0x000FF
#define RFE_SPARE1_AGC_VALUE    0

static void LRF_temperatureCompensateTrim(const LRF_TrimDef *trimDef)
{
    uint32_t divLdoTempOffset = 0;
    uint32_t tdcLdoTempOffset = 0;
    uint32_t rtrimTempOffset = 0;
    int32_t rssiTempOffset = 0;
    int32_t agcValOffset = 0;
    int32_t agcHighGainOffset = 0;
    int32_t agcLowGainOffset = 0;

    if (trimDef->revision >= LRF_TRIM_MIN_VERSION_FULL_FEATURES)
    {
        int32_t temperature = hal_get_temperature();

        LRF_Trim_tempLdoRtrim tempLdoRtrim = trimDef->trim3.fields.lrfdrfeExtTrim1.tempLdoRtrim;

        int32_t tempThreshLow = LRF_TEMPERATURE_MIN + tempLdoRtrim.tThrl * (1 << LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP);
        int32_t tempThreshHigh = LRF_TEMPERATURE_MAX - tempLdoRtrim.tThrh * (1 << LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP);

        /* Adjust values for extreme temperatures */
        if (temperature < tempThreshLow)
        {
            uint32_t temperatureDiff = tempThreshLow - temperature;
            divLdoTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrl,
                LRF_DIVLDO_LOW_TEMP_ADJ_FACTOR * tempLdoRtrim.divLdoMinOffset);
            tdcLdoTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrl,
                LRF_TDCLDO_LOW_TEMP_ADJ_FACTOR * tempLdoRtrim.tdcLdoMinOffset);
            rtrimTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrl,
                LRF_RTRIM_LOW_TEMP_ADJ_FACTOR * tempLdoRtrim.rtrimMinOffset);
        }
        else if (temperature > tempThreshHigh)
        {
            uint32_t temperatureDiff = temperature - tempThreshHigh;
            divLdoTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrh,
                LRF_DIVLDO_HIGH_TEMP_ADJ_FACTOR * tempLdoRtrim.divLdoMaxOffset);
            tdcLdoTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrh,
                LRF_TDCLDO_HIGH_TEMP_ADJ_FACTOR * tempLdoRtrim.tdcLdoMaxOffset);
            rtrimTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrh,
                LRF_RTRIM_HIGH_TEMP_ADJ_FACTOR * tempLdoRtrim.rtrimMaxOffset);
        }

        rssiTempOffset = LRF_findExtTrim0TrimAdjustment(temperature, trimDef->trim3.fields.lrfdrfeExtTrim0.rssiTcomp, 0);

        if (((HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_AGCINFO) & RFE_COMMON_RAM_AGCINFO_MODE_M) >> RFE_COMMON_RAM_AGCINFO_MODE_S) == (RFE_COMMON_RAM_AGCINFO_MODE_FAST >> RFE_COMMON_RAM_AGCINFO_MODE_S))
        {
            /* Fast AGC */
            agcValOffset =LRF_findExtTrim0TrimAdjustment(temperature, trimDef->trim3.fields.lrfdrfeExtTrim0.agcThrTcomp,
                                                         trimDef->trim3.fields.lrfdrfeExtTrim0.agcThrOffset);
            agcHighGainOffset = trimDef->trim3.fields.lrfdrfeExtTrim0.highGainOffset;
            agcLowGainOffset = trimDef->trim3.fields.lrfdrfeExtTrim0.lowGainOffset;
        }
        else
        {
            /* Standard AGC */
            agcValOffset = LRF_findExtTrim0TrimAdjustment(temperature, trimDef->trim3.fields.lrfdrfeExtTrim0.magnTcomp,
                                                          trimDef->trim3.fields.lrfdrfeExtTrim0.magnOffset);
        }
    }

    uint32_t divLdoVoutTrim = trimDef->trim1.fields.divLdo.voutTrim;

    /* Most significant bit is inverted */
    divLdoVoutTrim ^= 0x40;

    divLdoVoutTrim += divLdoTempOffset;

    /* Saturate at maximum value */
    if (divLdoVoutTrim > (LRFDRFE_DIVLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S))
    {
        divLdoVoutTrim = (LRFDRFE_DIVLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S);
    }
    /* Write back with most signigicant bit inverted back */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOF) = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOF) | ((divLdoVoutTrim ^ 0x40) << RFE_COMMON_RAM_DIVLDOF_VOUTTRIM_S);

    /* Add offset to initial value */
    divLdoVoutTrim += HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOIOFF);

    /* Saturate at maximum value */
    if (divLdoVoutTrim > (LRFDRFE_DIVLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S))
    {
        divLdoVoutTrim = (LRFDRFE_DIVLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S);
    }
    /* Write back with most signigicant bit inverted back */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOI) = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOI) | ((divLdoVoutTrim ^ 0x40) << RFE_COMMON_RAM_DIVLDOI_VOUTTRIM_S);

    uint32_t tdcLdoVoutTrim = trimDef->trim1.fields.tdcLdo.voutTrim;

    if (tdcLdoTempOffset > 0)
    {
        /* Most significant bit is inverted */
        tdcLdoVoutTrim ^= 0x40;

        tdcLdoVoutTrim += tdcLdoTempOffset;

        /* Saturate at maximum value */
        if (tdcLdoVoutTrim > (LRFDRFE_TDCLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S))
        {
            tdcLdoVoutTrim = (LRFDRFE_TDCLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S);
        }

        /* Invert back */
        tdcLdoVoutTrim ^= 0x40;
    }
    /* Write back */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_TDCLDO) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_TDCLDO) | (tdcLdoVoutTrim << LRFDRFE_TDCLDO_VOUTTRIM_S);

#ifdef DeviceFamily_CC27XX
    /* RTRIM Workaround: hardcode the RTRIM to 10U rather than read it from FCFG for CC27XX state B devices (see: RCL-591)
     * ASSUMPTION: AppTrims revision on CC27XX state C devices is not smaller than 7
     */
    uint32_t rtrim;
    if (trimDef->revision >= LRF_TRIM_VERSION_STATE_C_TRIM_WORKAROUND_CC27XX)
    {
        rtrim = trimDef->trim2.fields.dco.tailresTrim;
    }
    else
    {
        rtrim = LRF_TRIM_RTRIM_VALUE_STATE_B_RTRIM_WORKAROUND_CC27XX;
    }
#else
    uint32_t rtrim = trimDef->trim2.fields.dco.tailresTrim;
#endif
    /* Temperature compensation and PHY offset can only be applied if the value is not above the saturation level */
    /* If RTRIM from FCFG is above this, always use that level */
    if (rtrim < LRF_DEFAULT_RTRIM_MAX)
    {
        /* Add offset from temperature compensation */
        rtrim += rtrimTempOffset;

        /* Add offset from PHY */
        rtrim += HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RTRIMOFF);

        /* Saturate */
        if (rtrim > LRF_DEFAULT_RTRIM_MAX)
        {
            rtrim = LRF_DEFAULT_RTRIM_MAX;
        }
    }

    /* Ensure it is not smaller than minimum from PHY */
    uint32_t minRtrim = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RTRIMMIN);
    if (rtrim < minRtrim)
    {
        rtrim = minRtrim;
    }

    /* Write into register */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCO) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCO) | (rtrim << LRFDRFE_DCO_TAILRESTRIM_S);

    /* Get RSSI offset from FCFG */
    int32_t rssiOffset = trimDef->trim4.rssiOffset;

#if defined(DeviceFamily_CC23X0R5) || defined(DeviceFamily_CC23X0R22) || defined(DeviceFamily_CC2340R53)
    /* RCL-335: Some devices (State D) have an error in the programmed RSSI offset */
    if (trimDef->revision == LRF_TRIM_VERSION_RSSIOFFSET_ISSUE_CC23X0R5)
    {
        if (rssiOffset <= LRF_TRIM_LIMIT_RSSIOFFSET_ISSUE_CC23X0R5)
        {
            rssiOffset += LRF_TRIM_CORRECTION_RSSIOFFSET_ISSUE_CC23X0R5;
        }
    }
#endif

    /* Apply temperature compensation */
    rssiOffset += rssiTempOffset;

    /* Apply PHY specific offset */
    rssiOffset += HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_PHYRSSIOFFSET);

    /* Store in HW register */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_RSSIOFFSET) = rssiOffset;

    if (((HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_AGCINFO) & RFE_COMMON_RAM_AGCINFO_MODE_M) >> RFE_COMMON_RAM_AGCINFO_MODE_S) == (RFE_COMMON_RAM_AGCINFO_MODE_FAST >> RFE_COMMON_RAM_AGCINFO_MODE_S))
    {
        uint32_t spare0Val = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_SPARE0SHADOW);
        if (agcHighGainOffset != 0 || agcLowGainOffset != 0)
        {
            int32_t lowGain = (spare0Val & RFE_SPARE0_LOW_GAIN_BM) >> RFE_SPARE0_LOW_GAIN;
            int32_t highGain = (spare0Val & RFE_SPARE0_HIGH_GAIN_BM) >> RFE_SPARE0_HIGH_GAIN;
            if (agcLowGainOffset != 0)
            {
                lowGain += agcLowGainOffset;
                if (lowGain < 0)
                {
                    lowGain = 0;
                }
                if (lowGain > (RFE_SPARE0_LOW_GAIN_BM >> RFE_SPARE0_LOW_GAIN))
                {
                    lowGain = (RFE_SPARE0_LOW_GAIN_BM >> RFE_SPARE0_LOW_GAIN);
                }
            }
            if (agcHighGainOffset != 0)
            {
                highGain += agcHighGainOffset;
                if (highGain < 0)
                {
                    highGain = 0;
                }
                if (highGain > (RFE_SPARE0_HIGH_GAIN_BM >> RFE_SPARE0_HIGH_GAIN))
                {
                    highGain = (RFE_SPARE0_HIGH_GAIN_BM >> RFE_SPARE0_HIGH_GAIN);
                }
            }
            spare0Val = (spare0Val & ~(RFE_SPARE0_LOW_GAIN_BM | RFE_SPARE0_HIGH_GAIN_BM)) |
                (lowGain << RFE_SPARE0_LOW_GAIN) | (highGain << RFE_SPARE0_HIGH_GAIN);
        }
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE0) = spare0Val;
    }

    uint32_t spare1Val = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_SPARE1SHADOW);
    if (agcValOffset != 0)
    {
        int32_t agcVal = (spare1Val & RFE_SPARE1_AGC_VALUE_BM) >> RFE_SPARE1_AGC_VALUE;
        agcVal += agcValOffset;
        if (agcVal < 0)
        {
            agcVal = 0;
        }
        if (agcVal > (RFE_SPARE1_AGC_VALUE_BM >> RFE_SPARE1_AGC_VALUE))
        {
            agcVal = (RFE_SPARE1_AGC_VALUE_BM >> RFE_SPARE1_AGC_VALUE);
        }
        spare1Val = (spare1Val & ~RFE_SPARE1_AGC_VALUE_BM) | (agcVal << RFE_SPARE1_AGC_VALUE);
    }
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE1) = spare1Val;
}

/* Represent 1/3 with the approximation LRF_ONE_THIRD_MANTISSA * 2^(-LRF_ONE_THIRD_NEG_EXP) */
#define LRF_ONE_THIRD_MANTISSA 21845U /* (round(1/3 * 2^16)) */
#define LRF_ONE_THIRD_NEG_EXP  16
/* Calculate temperature compensation for the fields in lrfdrfeExtTrim1 */
/* temperatureDiff: absolute difference from calculated temperature threshold */
/* tempThreshFactor: Temperature Threshold field as defined in the trim spec:
   The temperature threshold is given by (125 - tempThreshFactor * 2^k) for high temperatures and
   (-40C + tempThreshFactor * 2^k) for low temperatures, where k = LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP. */
/* maxAdjustment: The adjustment to apply at the extreme temperature */
/* Return: Adjustment to add to value */
static uint32_t LRF_findExtTrim1TrimAdjustment(uint32_t temperatureDiff, uint32_t tempThreshFactor, uint32_t maxAdjustment)
{
    uint32_t adjustment;
    /* Calculate adjustment = round((temperatureDiff * maxAdjustment) / (tempThreshFactor * 2^LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP)) */
    switch (tempThreshFactor)
    {
        case 0:
        default:
            /* tempThreshFactor = 0:
               No temperatures will be in the range for adjustment */
            adjustment = 0;
            break;
        case 1:
            /* tempThreshFactor = 1:
               adjustment = round((temperatureDiff * maxAdjustment) / (1 * 2^LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP)) */
            adjustment = ((temperatureDiff * maxAdjustment) + (1 << (LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP - 1))) >> LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP;
            break;
        case 2:
            /* tempThreshFactor = 2:
               adjustment = round((temperatureDiff * maxAdjustment) / (2 * 2^LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP)) */
            adjustment = ((temperatureDiff * maxAdjustment) + (1 << LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP)) >> (LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP + 1);
            break;
        case 3:
            /* tempThreshFactor = 3:
               adjustment = round((temperatureDiff * maxAdjustment) / (3 * 2^LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP))
               Use approximation with multiplication to avoid performing division */
            adjustment = ((temperatureDiff * maxAdjustment * LRF_ONE_THIRD_MANTISSA) + (1 << (LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP + LRF_ONE_THIRD_NEG_EXP - 1)))
                >> (LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP + LRF_ONE_THIRD_NEG_EXP);
            break;
    }
    return adjustment;
}

/* Calculate temperature compensation for the fields in lrfdrfeExtTrim0 */
/* temperature: temperature (degrees C) */
/* tempCompFactor: Temperature compensation coefficient used to find offset from the formula ((temperature - 25) * tempCompFactor) / 128 */
/* offset: Absolute offset to apply independent of temperature  */
/* Return: Adjustment to add to value */
static int32_t LRF_findExtTrim0TrimAdjustment(int32_t temperature, int32_t tempCompFactor, int32_t offset)
{
    return (((temperature - LRF_TEMPERATURE_NOM) * tempCompFactor) >> LRF_EXTTRIM0_TEMPERATURE_SCALE_EXP) + offset;
}

void LRF_enable(void)
{
    /* Set MSGBOX register to 0 */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_MSGBOX) = 0;

    /* Initialize and enable PBE TOPsm and FIFO */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_INIT)   = ((1 << LRFDPBE_INIT_MDMF_S)   |
                                                       (1 << LRFDPBE_INIT_TOPSM_S));
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_ENABLE) = ((1 << LRFDPBE_ENABLE_MDMF_S) |
                                                       (1 << LRFDPBE_ENABLE_TOPSM_S));

    /* Initialize and enable MCE TOPsm and FIFO */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_INIT)   = ((1 << LRFDMDM_INIT_TXRXFIFO_S)  |
                                                       (1 << LRFDMDM_INIT_TOPSM_S));
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_ENABLE) = ((1 << LRFDMDM_ENABLE_TXRXFIFO_S)|
                                                       (1 << LRFDMDM_ENABLE_TOPSM_S));

    /* Initialize and enable RFE TOPsm */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_INIT)   = (1 << LRFDRFE_INIT_TOPSM_S);
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_ENABLE) = (1 << LRFDRFE_ENABLE_TOPSM_S);
}

void LRF_disable(void)
{
    /* Request PBE powerdown */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_PDREQ) = LRFDPBE_PDREQ_TOPSMPDREQ_M;
    /* Disable all PBE modules */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_ENABLE) = 0;
    /* Stop powerdown request */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_PDREQ) = 0;

    /* Request MCE powerdown */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_PDREQ) = LRFDMDM_PDREQ_TOPSMPDREQ_M;
    /* Disable all MDM modules */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_ENABLE) = 0;
    /* Stop powerdown request */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_PDREQ) = 0;

    /* Request RFE powerdown */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_PDREQ) = LRFDRFE_PDREQ_TOPSMPDREQ_M;
    /* Disable all RFE modules */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_ENABLE) = 0;
    /* Stop powerdown request */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_PDREQ) = 0;
}

void LRF_waitForTopsmReady(void)
{
    /* Make sure PBE is finished booting */
    /* This poll should be quick as long as the TOPsms have been reset and enabled */
    while (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_MSGBOX) == 0)
    {
    }
}

uint32_t LRF_prepareRxFifo(void)
{
    uint32_t fifoSize;
    /* Reset RXFIFO. NOTE: Only allowed while PBE is not running, ref. RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_RXFIFO_RESET >> LRFDPBE_FCMD_DATA_S);
    /* Set up RXFIFO without auto commit or deallocate */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) & (~(LRFDPBE_FCFG0_RXADEAL_M | LRFDPBE_FCFG0_RXACOM_M));
    /* Read writable bytes, which is the FIFO size */
    fifoSize = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFWRITABLE);
    /* Write SRP to 0. This sets no available space for writing; to be updated
       by calling LRF_setRxFifoEffSz().
       This write can be done without protection since PBE is not allowed to be
       running here, ref RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFSRP) = 0;
    rxFifoDeallocated = false;

    return fifoSize;
}

uint32_t LRF_prepareTxFifo(void)
{
    /* Reset RXFIFO. NOTE: Only allowed while PBE is not running, ref. RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RESET >> LRFDPBE_FCMD_DATA_S);
    /* Set up TXFIFO with auto commit, without auto deallocate */
    uint32_t fcfg0 = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0);
    fcfg0 &= ~LRFDPBE_FCFG0_TXADEAL_M;
    fcfg0 |=  LRFDPBE_FCFG0_TXACOM_M;
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) = fcfg0;
    /* Return writable bytes, which is the FIFO size */
    return HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWRITABLE);
}

uint32_t LRF_peekRxFifo(int32_t offset)
{
    int32_t index = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP) + offset;
    int32_t fifosz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2;
    if (index >= fifosz)
    {
        index -= fifosz;
    }

    return HWREG_READ_LRF(LRFD_BUFRAM_BASE + (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG3) << 2) + index);
}

uint32_t LRF_peekTxFifo(int32_t offset)
{
    int32_t index = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFRP) + offset;
    int32_t fifosz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG2) & LRFDPBE_FCFG2_TXSIZE_M) >> LRFDPBE_FCFG2_TXSIZE_S) << 2;
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    return HWREG_READ_LRF(LRFD_BUFRAM_BASE + (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG1) << 2) + index);
}

uint8_t *LRF_getTxFifoWrAddr(int32_t offset)
{
    int32_t index = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWP) + offset;
    return (uint8_t *) (TXF_UNWRAPPED_BASE_ADDR + (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG1) << 2) + index);
}

/* Use the workaround of RCL-367 to write the FIFO pointer register with
 * address regAddr to the given value. This allows PBE to protect against
 * writing FCMD at the same time */
static void LRF_writeFifoPtr(uint32_t value, uintptr_t regAddr)
{
    /* Run in protected region to avoid unnecessary delays */
    uintptr_t key = HwiP_disable();
    /* Direct PBE to write FIFO commands to FSTAT register to make them ignored */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FSTAT) & 0x0FFF) >> 2;
    /* Wait a little so that PBE has time to finish any pending command writes */
    /* Do the wait by dummy reads of FIFOCMDADD */
    (void) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD);
    (void) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD);
    /* Write to specified register */
    HWREG_WRITE_LRF(regAddr) = value;
    /* Set PBE back to writing FIFO commands to FCMD */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FCMD) & 0x0FFF) >> 2;

    HwiP_restore(key);
}

/* Use the workaround of RCL-367 to write both FIFO pointer registers with
 * addresses regAddr0 and regAddr1 to the given value. This allows PBE to
 * protect against writing FCMD at the same time */
static void LRF_writeFifoPtrs(uint32_t value, uintptr_t regAddr0, uintptr_t regAddr1)
{
    /* Run in protected region to avoid unnecessary delays */
    uintptr_t key = HwiP_disable();
    /* Direct PBE to write FIFO commands to FSTAT register to make them ignored */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FSTAT) & 0x0FFF) >> 2;
    /* Wait a little so that PBE has time to finish any pending command writes */
    /* Do the wait by dummy reads of FIFOCMDADD */
    (void) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD);
    (void) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD);
    /* Write to specified registers */
    HWREG_WRITE_LRF(regAddr0) = value;
    HWREG_WRITE_LRF(regAddr1) = value;
    /* Set PBE back to writing FIFO commands to FCMD */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FCMD) & 0x0FFF) >> 2;


    HwiP_restore(key);
}

void LRF_skipTxFifoWords(uint32_t wordLength)
{
    int32_t index = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFRP) + (wordLength * 4);
    int32_t fifosz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG2) & LRFDPBE_FCFG2_TXSIZE_M) >> LRFDPBE_FCFG2_TXSIZE_S) << 2;
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    LRF_writeFifoPtr(index, (LRFDPBE_BASE + LRFDPBE_O_TXFRP));
}

void LRF_discardRxFifoWords(uint32_t wordLength)
{
    int32_t index = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP) + (wordLength * 4);
    int32_t fifosz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2;
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    /* Write updated pointer to rp and srp */
    LRF_writeFifoPtrs(index, (LRFDPBE_BASE + LRFDPBE_O_RXFRP), (LRFDPBE_BASE + LRFDPBE_O_RXFSRP));
    /* RX FIFO is now deallocated */
    rxFifoDeallocated = true;
}

void LRF_readRxFifoWords(uint32_t *data32, uint32_t wordLength)
{
    /* Due to RCL-367, the packet is read from memory, and the read pointer is updated afterwards */
    /* Pointer to unwrapped FIFO RAM representation */
    uint32_t fifoStart = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG3) & LRFDPBE_FCFG3_RXSTRT_M) >> LRFDPBE_FCFG3_RXSTRT_S) << 2;
    uint32_t readPointer = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP) & ~0x0003;
    volatile uint32_t *fifoReadPtr = (volatile uint32_t *) (RXF_UNWRAPPED_BASE_ADDR + fifoStart + readPointer);

    /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#ifdef DeviceFamily_CC27XX
    ASM_4_NOPS();
#endif //DeviceFamily_CC27XX
    for (uint32_t i = 0; i < wordLength; i++) {
        *data32++ = *fifoReadPtr++;
    }
    /* Update read pointer */
    int32_t index = readPointer + (wordLength * 4);
    int32_t fifosz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2;
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    LRF_writeFifoPtr(index, (LRFDPBE_BASE + LRFDPBE_O_RXFRP));
    /* RP was moved, so RX FIFO is not deallocated */
    rxFifoDeallocated = false;
}

void LRF_writeTxFifoWords(const uint32_t *data32, uint32_t wordLength)
{
    /* Due to RCL-367, the packet is written to memory, and the write pointer is updated afterwards */
    /* Pointer to unwrapped FIFO RAM representation */
    uint32_t fifoStart = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG1) & LRFDPBE_FCFG1_TXSTRT_M) >> LRFDPBE_FCFG1_TXSTRT_S) << 2;
    uint32_t writePointer = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWP) & ~0x0003;
    volatile uint32_t *fifoWritePtr = (volatile uint32_t *) (TXF_UNWRAPPED_BASE_ADDR + fifoStart + writePointer);

    /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#ifdef DeviceFamily_CC27XX
    ASM_4_NOPS();
#endif //DeviceFamily_CC27XX
    for (uint32_t i = 0; i < wordLength; i++) {
        *fifoWritePtr++ = *data32++;
    }
    /* Update write pointer */
    int32_t index = writePointer + (wordLength * 4);
    int32_t fifosz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG2) & LRFDPBE_FCFG2_TXSIZE_M) >> LRFDPBE_FCFG2_TXSIZE_S) << 2;
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    LRF_writeFifoPtr(index, (LRFDPBE_BASE + LRFDPBE_O_TXFWP));
}

void LRF_setRxFifoEffSz(uint32_t maxSz)
{
    uint32_t fifoSz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2;
    if (maxSz >= fifoSz)
    {
        /* Deallocate RX FIFO to get no additional FIFO restriction */
        /* Due to RCL-367, the operation is done with a FIFO pointer register write */
        if (!rxFifoDeallocated)
        {
            /* We should not do this write if the FIFO was already deallocated, as it would move the SRP one full round */
            LRF_writeFifoPtr(HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP), (LRFDPBE_BASE + LRFDPBE_O_RXFSRP));
            rxFifoDeallocated = true;
        }
    }
    else {
        uint32_t newSrp;
        /* A limit of 0 can't be achieved through manipulating SRP. For all practical purposes, a limit of 1 has the same effect. */
        if (maxSz == 0)
        {
            maxSz = 1;
        }

        newSrp = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP) + maxSz;
        if (newSrp >= fifoSz)
        {
            newSrp -= fifoSz;
        }
        /* The new SRP value will always be a write forward in the FIFO */
        /* Do not write if the value is the same as before, as this will be
            interpreted by the FIFO HW as going a full round forward */

        if (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFSRP) != newSrp)
        {
            LRF_writeFifoPtr(newSrp, (LRFDPBE_BASE + LRFDPBE_O_RXFSRP));
            /* SRP is now different from RP, so RX FIFO is not deallocated */
            rxFifoDeallocated = false;
        }
    }
}

/* (FXTALINVL + (FXTALINVH << 16)) = round(2^67/48e6) */
#define FXTALINVL 0x00001E52U
#define FXTALINVH 0x02CBD3F0U
/* (fXtalInv.word[0] + (fXtalInv.word[1] << 16)) = round(2^67/fXtal), where fXtal is clock frequency in Hz */
/* Only 16 bits are used of word[0] */
LRF_DoubleWord fXtalInv =
{
    .word = {FXTALINVL, FXTALINVH},
};
/* Calculate PLLM base, that is PLLM assuming an FREF corresponding to the crystal frequency */
/* This can be used to find true PLLM by multiplying with prediv */
static uint32_t LRF_findPllMBase(uint32_t frequency)
{
    /* 2^51 / fxtal */
    uint32_t frefInv = fXtalInv.word[1];

    uint32_t pllMBase;
    /* Find pllMBase = frequency / fxtal, encoded as <12.18u> */
    /* First, find pllMBase = frequency / fxtal * 2^(51-32) */
    pllMBase = (frefInv >> 16) * (frequency >> 16);
    uint32_t tmpPllMBase;
    tmpPllMBase = ((frefInv >> 16) * (frequency & 0xFFFFU)) >> 1;
    tmpPllMBase += ((frefInv & 0xFFFFU) * (frequency >> 16)) >> 1;
    tmpPllMBase += (1U << 14);
    tmpPllMBase >>= 15;
    pllMBase += tmpPllMBase;

    /* Divide by 2 with rounding to get pllMBase = frequency / fxtal * 2^18 */
    pllMBase += 1;
    pllMBase >>= 1;

    return pllMBase;
}

static uint32_t countLeadingZeros(uint16_t value)
{
   int numZeros = 0;
   if (value >= 0x0100) {
      value >>= 8;
   }
   else {
      numZeros += 8;
   }
   if (value >= 0x10) {
      value >>= 4;
   }
   else {
      numZeros += 4;
   }
   if (value >= 0x04) {
      value >>= 2;
   }
   else {
      numZeros += 2;
   }
   if (value >= 0x02) {
       /* No need to shift down value since this is the last step */
   }
   else {
      numZeros += 1;
   }
   return numZeros;
}

static uint32_t LRF_findCalM(uint32_t frequency, uint32_t prediv)
{
    /* Find 2^47 / fref = 2^47 * prediv / fxtal */
    uint32_t frefInv = (fXtalInv.word[1] >> 4) * prediv;
    /* Round to 2^31 * prediv / fxtal */
    frefInv += 1 << 15;
    frefInv >>= 16;

    uint32_t calM;
    /* Find calM = frequency / fref (no fractional bits) */
    /* First, find calM = frequency / fref * 2^(31-15)) */
    calM = frefInv * ((frequency + (1 << 14)) >> 15);

    /* Divide by 2^16 with rounding to get calM = frequency / fref */
    calM += 1 << 15;
    calM >>= 16;

    return calM;
}

/* invSynthFreq = 2^47 / synthFrequency */
static uint32_t LRF_findFoff(int32_t frequencyOffset, uint32_t invSynthFreq)
{
    uint32_t absFrequencyOffset;
    int32_t fOffRes;
    if (frequencyOffset == 0)
    {
        return 0;
    }
    else {
        if (frequencyOffset < 0)
        {
            absFrequencyOffset = -frequencyOffset;
        }
        else
        {
            absFrequencyOffset = frequencyOffset;
        }
        /* Calculate 2^41 * abs(frequencyOffset) / synthFrequency */
        absFrequencyOffset = (absFrequencyOffset + (1U << 5)) >> 6;
        absFrequencyOffset *= invSynthFreq;
        /* Round to 2^21 * abs(frequencyOffset) / synthFrequency */
        absFrequencyOffset = (absFrequencyOffset + (1U << 19)) >> 20;
        /* Re-intruduce sign */
        if (frequencyOffset < 0)
        {
            fOffRes = -absFrequencyOffset;
        }
        else
        {
            fOffRes = absFrequencyOffset;
        }

        return (((uint32_t)fOffRes) & LRFDRFE_MOD1_FOFF_M);
    }
}

#define NUM_TX_FILTER_TAPS 24
/* deviation in Hz */
/* invSynthFreq = 2^51 / synthFrequency */
static void LRF_programShape(const LRF_TxShape *txShape, uint32_t deviation, uint32_t invSynthFreq)
{
    /* If txShape is NULL, do not program shape, but instead leave the values programmed as part of setup */
    if (txShape != NULL)
    {
        union {
            uint8_t  b[NUM_TX_FILTER_TAPS];
            uint32_t w[NUM_TX_FILTER_TAPS/4];
        } filterCoeff;
        /* Find deviation * 2^29/fs * 2^10 */
        uint32_t deviationFactor1 = ((deviation >> 12) * invSynthFreq) +
            (((deviation & 0x0FFFU) * invSynthFreq) >> 12);
        /* Find deviation * 2^29/fs * scale / 2^16 */
        uint32_t scale = txShape->scale;
        uint32_t deviationFactor2 = ((((deviationFactor1 >> 15) * scale) >> 1) +
                                     (((deviationFactor1 & 0x7FFF) * scale) >> 16) + (1 << 4)) >> 5;
        /* Find shapeGain and scaling */
        int32_t shapeGain = 8 - countLeadingZeros(deviationFactor2 >> 11);
        if (shapeGain < 0)
        {
            shapeGain = 0;
        }
        uint32_t startCoeff = NUM_TX_FILTER_TAPS - txShape->numCoeff;
        for (uint32_t i = 0; i < startCoeff; i++)
        {
            filterCoeff.b[i] = 0;
        }
        for (uint32_t i = 0; i < NUM_TX_FILTER_TAPS - startCoeff; i++)
        {
            filterCoeff.b[i + startCoeff] =
                ((deviationFactor2 * txShape->coeff[i]) + (1 << (18 + shapeGain))) >> (19 + shapeGain);
        }

        /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#ifdef DeviceFamily_CC27XX
        ASM_4_NOPS();
#endif //DeviceFamily_CC27XX
        for (int i = 0; i <  NUM_TX_FILTER_TAPS / 4; i++)
        {
            *((unsigned long*) (LRFDRFE32_BASE + LRFDRFE32_O_DTX1_DTX0) + i) = filterCoeff.w[i];
        }
        if (shapeGain > 3)
        {
            /* TODO: Scale by adjusting the symbol mapping */
            shapeGain = 3;
        }
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_MOD0) = (HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_MOD0) & ~LRFDRFE_MOD0_SHPGAIN_M) | (shapeGain << LRFDRFE_MOD0_SHPGAIN_S);
    }
}

static uint32_t LRF_findLog2Bde1(uint32_t demmisc3)
{
    uint32_t log2Bde1;
    if ((demmisc3 & LRFDMDM_DEMMISC3_BDE1FILTMODE_M) != 0)
    {
        log2Bde1 = 0;
    }
    else
    {
        log2Bde1 = (demmisc3 & LRFDMDM_DEMMISC3_BDE1NUMSTAGES_M) >> LRFDMDM_DEMMISC3_BDE1NUMSTAGES_S;
    }
    return log2Bde1;
}

/* Calculate P as rateWord * bde1 * bde2 * pdifDecim * 9 * 2^4
   Calculate Q as pllMBase * pre
   Normalize Q to 28 bits and do the same normalization to P */
/* Multiplication factor from P formula */
#define P_FACTOR 9
/* Shift from P formula */
#define P_SHIFT 4
/* Right shift of PLL M to allow 32-bit calculation */
#define Q_MAGN_SHIFT 6
/* Number of bits in P and Q */
#define FRAC_NUM_BITS 28
/* Number of extra bits in an uint32_t compared to the P and Q HW registers */
#define FRAC_EXTRA_BITS (32 - FRAC_NUM_BITS)
static uint32_t LRF_programPQ(uint32_t pllMBase)
{
    bool roundingError = false;
    uint32_t rateWord = (HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_BAUD) << 5);
    rateWord |= ((HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_BAUDPRE) & LRFDMDM_BAUDPRE_EXTRATEWORD_M) >> LRFDMDM_BAUDPRE_EXTRATEWORD_S);
    uint32_t pre = (HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_BAUDPRE) & LRFDMDM_BAUDPRE_PRESCALER_M);
    uint32_t demmisc3 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC3);
    uint32_t log2Bde1 = LRF_findLog2Bde1(demmisc3);

    uint32_t bde2 = (demmisc3 & LRFDMDM_DEMMISC3_BDE2DECRATIO_M) >> LRFDMDM_DEMMISC3_BDE2DECRATIO_S;
    uint32_t log2PdifDecim = (demmisc3 & LRFDMDM_DEMMISC3_PDIFDECIM_M) >> LRFDMDM_DEMMISC3_PDIFDECIM_S;
    int32_t leftShiftP;

    leftShiftP = log2Bde1 + log2PdifDecim + P_SHIFT;

    uint32_t demFracP = rateWord * bde2;
    if (demFracP > (uint32_t)((1ULL << 32) / P_FACTOR))
    {
        if ((demFracP & 1) != 0)
        {
            roundingError = true;
        }
        demFracP >>= 1;
        leftShiftP -= 1;
    }
    demFracP *= P_FACTOR;

    /* Preliminary calculation to find scaling factor - round PLLM upwards to ensure no overflow
       in final calculation */
    uint32_t demFracQ = ((pllMBase + ((1 << Q_MAGN_SHIFT) - 1)) >> Q_MAGN_SHIFT) * pre;
    uint32_t num0Q = countLeadingZeros(demFracQ >> 16);

    int32_t pllMShift = Q_MAGN_SHIFT + FRAC_EXTRA_BITS - num0Q;
    uint32_t pllMBaseRounded;
    if (pllMShift <= 0)
    {
        pllMBaseRounded = pllMBase;
        demFracQ = pllMBase * pre;
        int32_t leftShiftQ = -pllMShift;
        leftShiftP += leftShiftQ;
        /* leftShiftQ is sure to be positive since pllMShift <= 0 */
        demFracQ <<= leftShiftQ;
    }
    else
    {
        /* Scale PLLM to allow Q to fit */
        pllMBaseRounded = (pllMBase + (1U << (pllMShift - 1))) >> pllMShift;
        demFracQ = pllMBaseRounded * pre;
        /* Multiply PLLM back (rounding is now applied) */
        pllMBaseRounded <<= pllMShift;
        leftShiftP -= pllMShift;
    }

    if (leftShiftP >= 0)
    {
        demFracP <<= leftShiftP;
    }
    else
    {
        /* Check if right shift of P introduces rounding error */
        if ((demFracP & ((1 << -leftShiftP) - 1)) != 0)
        {
            roundingError = true;
        }
        demFracP >>= -leftShiftP;
    }

    if (demFracP >= demFracQ)
    {
        Log_printf(RclCore, Log_ERROR, "Error: resampler fraction greater than 1; demodulator will not work");
    }
    if (roundingError)
    {
        Log_printf(RclCore, Log_WARNING, "Rounding error in fractional resampler");
    }
    if (pllMBaseRounded != pllMBase)
    {
        Log_printf(RclCore, Log_INFO, "PLLM base rounded from %08X to %08X to fit in fractional resampler", pllMBase, pllMBaseRounded);
    }

#ifdef DeviceFamily_CC27XX
    /* Check if shadow register for downsampler coefficient P is in use */
    if ((HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_BAUDCOMP) & LRFDMDM_BAUDCOMP_FRAC_SHADOW) != 0)
    {
        /* Write downsampler coefficient P to shadow registers for new Rx operations to restore */
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMCOHR3) = demFracP & 0x0000FFFFU;
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMCOHR4) = demFracP >> 16;
    }
#endif /* DeviceFamily_CC27XX */

    HWREG_WRITE_LRF(LRFDMDM32_BASE + LRFDMDM32_O_DEMFRAC1_DEMFRAC0) = demFracP;
    HWREG_WRITE_LRF(LRFDMDM32_BASE + LRFDMDM32_O_DEMFRAC3_DEMFRAC2) = demFracQ;

    return pllMBaseRounded;
}

/* invSynthFreq = 2^47 / synthFrequency */
static void LRF_programCMixN(int32_t rxIntFrequency, uint32_t invSynthFreq)
{
    /* Calculate n = f_if/f_pll*24*12*bde1*1024
                   = f_if/f_pll * 2^(15 + log2Bde1) * 9 */
    uint32_t absRxIntFrequency;
    if (rxIntFrequency < 0)
    {
        absRxIntFrequency = -rxIntFrequency;
    }
    else
    {
        absRxIntFrequency = rxIntFrequency;
    }

    absRxIntFrequency = (absRxIntFrequency + (1 << 5)) >> 6;
    /* Find 2^41 * abs(rxIntFrequency) / synthFrequency */
    uint32_t cMixN = absRxIntFrequency * invSynthFreq;
    /* Find 2^37 * abs(rxIntFrequency) / synthFrequency * 9 */
    cMixN = ((cMixN + (1 << 3)) >> 4) * 9;

    /* Find 2^(15 + log2Bde1) * abs(rxIntFrequency) / synthFrequency * 9 */
    uint32_t rightShift = (37 - 15) - LRF_findLog2Bde1(HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC3));
    cMixN = (cMixN + (1 << (rightShift - 1))) >> rightShift;

    int32_t signedCMixN;
    /* Use inverse sign */
    if (rxIntFrequency > 0)
    {
        signedCMixN = -cMixN;
    }
    else
    {
        signedCMixN = cMixN;
    }
#ifdef DeviceFamily_CC27XX
        /* Workaround (RCL-489): Invert RX frequency programmed to account for swapped I and Q signals in CC27xx PG1.0
         * TODO: May be swapped back for later PGs
         */
    signedCMixN = -signedCMixN;
#endif

    cMixN = (uint32_t)(signedCMixN & LRFDMDM_DEMMISC0_CMIXN_M);
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC0) = cMixN;
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_SPARE3) = cMixN;
}

void LRF_programFrequency(uint32_t frequency, bool tx)
{
    uint32_t synthFrequency;
    LRF_SwParam *swParam = (LRF_SwParam *) swParamList;
    const LRF_SwConfig *swConfig = swParam->swConfig;

    /* Find frequency corrected for IF. Normally, the result will be the same for tx and rx, and
       that is a prerequisite for switching without recalibration. */
    if (tx)
    {
        synthFrequency = frequency - swConfig->txFrequencyOffset;
    }
    else
    {
        synthFrequency = frequency - swConfig->rxFrequencyOffset
            - swConfig->rxIntFrequency;
    }

    /* Compensate desired frequency for temperature-dependent offset in HFXT, if any */
    uint32_t synthFrequencyCompensated = LRF_scaleFreqWithHFXTOffset(synthFrequency);

    /* Frequency divided by 2^16, rounded */
    uint32_t frequencyDiv2_16 = (synthFrequency + (1 << 15)) >> 16;

    /* Start calculating 2^47/frequency (approximated as 2^31/(synthFrequency/2^16)) */
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_DIVIDEND) = 1U << 31;
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_DIVISOR) = frequencyDiv2_16;

    /* Write approximate freuency to RFE */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_K5) = frequencyDiv2_16;

    /* Find setting for coarse and mid calibration */
    uint32_t precalSetting = HWREG_READ_LRF(LRFDRFE32_BASE + LRFDRFE32_O_PRE3_PRE2);
    uint32_t coarsePrecal = (precalSetting & LRFDRFE32_PRE3_PRE2_CRSCALDIV_M) >> LRFDRFE32_PRE3_PRE2_CRSCALDIV_S;
    uint32_t midPrecal = (precalSetting &
                          (LRFDRFE32_PRE3_PRE2_MIDCALDIVMSB_M | LRFDRFE32_PRE3_PRE2_MIDCALDIVLSB_M))
        >> LRFDRFE_PRE2_MIDCALDIVLSB_S;

    uint32_t calMCoarse = LRF_findCalM(synthFrequency, coarsePrecal);
    uint32_t calMMid;
    if (coarsePrecal == midPrecal)
    {
        calMMid = calMCoarse;
    }
    else
    {
        calMMid = LRF_findCalM(synthFrequency, midPrecal);
    }
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_CALMMID_CALMCRS) = (calMCoarse << LRFDRFE32_CALMMID_CALMCRS_CALMCRS_VAL_S) |
        (calMMid << LRFDRFE32_CALMMID_CALMCRS_CALMMID_VAL_S);

    precalSetting = HWREG_READ_LRF(LRFDRFE32_BASE + LRFDRFE32_O_PRE1_PRE0);

    uint32_t precal0 = (precalSetting & LRFDRFE32_PRE1_PRE0_PLLDIV0_M) >> LRFDRFE32_PRE1_PRE0_PLLDIV0_S;
    uint32_t precal1 = (precalSetting & LRFDRFE32_PRE1_PRE0_PLLDIV1_M) >> LRFDRFE32_PRE1_PRE0_PLLDIV1_S;

    uint32_t pllMBase = LRF_findPllMBase(synthFrequency);
    pllMBase =  LRF_programPQ(pllMBase);

    uint32_t pllMBaseCompensated;
    if (synthFrequencyCompensated == synthFrequency)
    {
        pllMBaseCompensated = pllMBase;
    }
    else
    {
        pllMBaseCompensated = LRF_findPllMBase(synthFrequencyCompensated);
    }

    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_PLLM0) = ((pllMBaseCompensated * precal0) << LRFDRFE32_PLLM0_VAL_S);
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_PLLM1) = ((pllMBaseCompensated * precal1) << LRFDRFE32_PLLM1_VAL_S);

    /* Read out division result to find invSynthFreq */
    while ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DIVSTA) & LRFDRFE_DIVSTA_STAT_M) != 0)
    {
    }
    uint32_t invSynthFreq = HWREG_READ_LRF(LRFDRFE32_BASE + LRFDRFE32_O_QUOTIENT);

    /* Calculate intermediate frequencies */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RXIF) = LRF_findFoff(swConfig->rxFrequencyOffset, invSynthFreq);
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_TXIF) = LRF_findFoff(swConfig->txFrequencyOffset, invSynthFreq);

    /* Calculate CMIXN */
    LRF_programCMixN(swConfig->rxIntFrequency, invSynthFreq);

    LRF_programShape(swConfig->txShape, swConfig->modFrequencyDeviation,
                     invSynthFreq << 4);
}

uint32_t LRF_enableSynthRefsys(void)
{
    uint32_t earliestStartTime;

    /* Enable REFSYS if not already done. If it is enabled now, we need to make sure that start
       time is late enough */
    uint32_t atstref = HWREG_READ_LRF(LRFDRFE32_BASE + LRFDRFE32_O_ATSTREF);
    if ((atstref & LRFDRFE32_ATSTREF_BIAS_M) == 0)
    {
        /* Bias not already enabled - enable it now */
        HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_ATSTREF) = atstref | LRFDRFE32_ATSTREF_BIAS_M;
        /* Set earliest start time of synth to some later time */
        earliestStartTime = LRF_REFSYS_ENABLE_TIME;
    }
    else
    {
        /* No restriction on start time */
        earliestStartTime = 0;
    }
    /* Add current time */
    earliestStartTime += RCL_Scheduler_getCurrentTime();

    return earliestStartTime;
}

void LRF_disableSynthRefsys(void)
{
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_ATSTREF) = HWREG_READ_LRF(LRFDRFE32_BASE + LRFDRFE32_O_ATSTREF) & (~LRFDRFE32_ATSTREF_BIAS_M);
}

void LRF_rclEnableRadioClocks(void)
{
    LRF_setRclClockEnable(LRFDDBELL_CLKCTL_BUFRAM_M |
                          LRFDDBELL_CLKCTL_DSBRAM_M |
                          LRFDDBELL_CLKCTL_RFERAM_M |
                          LRFDDBELL_CLKCTL_MCERAM_M |
                          LRFDDBELL_CLKCTL_PBERAM_M |
                          LRFDDBELL_CLKCTL_RFE_M |
                          LRFDDBELL_CLKCTL_MDM_M |
                          LRFDDBELL_CLKCTL_PBE_M);
}

void LRF_rclDisableRadioClocks(void)
{
    LRF_clearRclClockEnable(LRFDDBELL_CLKCTL_BUFRAM_M |
                            LRFDDBELL_CLKCTL_DSBRAM_M |
                            LRFDDBELL_CLKCTL_RFERAM_M |
                            LRFDDBELL_CLKCTL_MCERAM_M |
                            LRFDDBELL_CLKCTL_PBERAM_M |
                            LRFDDBELL_CLKCTL_RFE_M |
                            LRFDDBELL_CLKCTL_MDM_M |
                            LRFDDBELL_CLKCTL_PBE_M);
}

int8_t LRF_readRssi(void)
{
    return (int8_t)(HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_RSSI) & LRFDRFE_RSSI_VAL_M);
}

void LRF_setRawTxPower(uint32_t value, uint32_t temperatureCoefficient)
{
    lrfPhyState.rawTxPower.value.rawValue = value;
    lrfPhyState.rawTxPower.tempCoeff = temperatureCoefficient;
    lrfPhyState.rawTxPower.power = LRF_TxPower_Use_Raw;
}

LRF_TxPowerTable_Entry LRF_getRawTxPower(void)
{
    if (lrfPhyState.rawTxPower.power.rawValue == LRF_TxPower_Use_Raw.rawValue)
    {
        /* Raw TX power has been set */
        return lrfPhyState.rawTxPower;
    }
    else
    {
        /* Error: Raw TX power was never set */
        return LRF_TxPowerEntry_INVALID_VALUE;
    }
}

/* Avoid IB = 0 as it effectively turns the PA off */
#define RFE_PA0_IB_MIN_USED 1

void LRF_programTemperatureCompensatedTxPower(void)
{
    LRF_TxPowerTable_Entry txPowerEntry = lrfPhyState.currentTxPower;
    uint8_t tempCoeff = txPowerEntry.tempCoeff;
    if (tempCoeff != 0)
    {
        int32_t ib = txPowerEntry.value.ib;
        int32_t temperature = hal_get_temperature();
        /* Linear adjustment of IB field as a function of temperature, scaled
         * by the coefficient for the given setting */
        ib += ((temperature - LRF_TXPOWER_REFERENCE_TEMPERATURE) * (int32_t) tempCoeff)
            / LRF_TXPOWER_TEMPERATURE_SCALING;
        /* Saturate IB */
        if (ib < (int32_t) RFE_PA0_IB_MIN_USED)
        {
            ib = RFE_PA0_IB_MIN_USED;
        }
#ifdef DeviceFamily_CC27XX
        /* TODO: See RCL-444. Use LRFDRFE_PA1_IB_MAX for CC27XX. */
        if (ib > (int32_t) (LRFDRFE_PA1_IB_MAX >> LRFDRFE_PA1_IB_S))
        {
            ib = LRFDRFE_PA1_IB_MAX >> LRFDRFE_PA1_IB_S;
        }
#else
        if (ib > (int32_t) (LRFDRFE_PA0_IB_MAX >> LRFDRFE_PA0_IB_S))
        {
            ib = LRFDRFE_PA0_IB_MAX >> LRFDRFE_PA0_IB_S;
        }
#endif
        txPowerEntry.value.ib = ib;
    }
    /* Program into RFE shadow register for PA power */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE5) = txPowerEntry.value.rawValue;
}

LRF_TxPowerResult LRF_programTxPower(LRF_TxPowerTable_Index powerLevel)
{
    if (powerLevel.rawValue != LRF_TxPower_None.rawValue)
    {
        LRF_SwParam *swParam = (LRF_SwParam *) swParamList;
        LRF_TxPowerTable_Entry txPowerEntry = LRF_TxPowerTable_findValue(swParam->txPowerTable, powerLevel);
        if (txPowerEntry.value.rawValue != LRF_TxPowerTable_INVALID_VALUE.rawValue)
        {
            lrfPhyState.currentTxPower = txPowerEntry;
            LRF_programTemperatureCompensatedTxPower();
        }
        else
        {
            return TxPowerResult_Error;
        }
    }
    return TxPowerResult_Ok;
}

static uint32_t LRF_scaleFreqWithHFXTOffset(uint32_t frequency)
{
    /* Get HFXT ratio from HFTRACKCTL register. This will have been
     * updated by the power driver if compensation is enabled and the temperature has drifted beyond the threshold.
     */
    uint32_t ratio = hal_get_hfxt_ratio();

    /* If temperature compensation is disabled, or temperature has not drifted,
     * the ratio will have its reset-value of 0x400000. In this case, do not perform scaling of input frequency
     * to save computational cost.
     * Rationale:
     * ratio = 24 MHz / (2 * HFXT_freq) * 2^24 ==> HFXT_freq = 24 MHz / ratio * 2^23
     * (ref: CKMD.HFTRACKCTL.RATIO register description)
     * Nominal HFXT frequency is 48 MHz
     *
     * frequency_out = frequency_in * HFXT_nominal_freq / HFXT_freq
     *               = frequency_in * 48 MHz / (24 MHz / ratio * 2^23)
     * frequency_out = frequency_in * ratio * 2^-22
     *
     * The method below is a computationally cost-effective way to calculate the scaled result.
     * Instead of performing 64-bit multiplication and shifting, the multiplier and multiplicand are divided into
     * half-words which are multiplied, added, and shifted appropriately.
     */
    if (ratio != hal_get_hfxt_ratio_default())
    {
        uint32_t ah = frequency >> 16;      /* Multiplier high half-word */
        uint32_t al = frequency & 0xFFFF;   /* Multiplier low half-word */

        uint32_t bh = ratio >> 16;          /* Multiplicand high half-word */
        uint32_t bl = ratio & 0xFFFF;       /* Multiplicand low half-word */

        /* Perform standard long multiplication where each "digit" is a half-word
         * https://en.wikipedia.org/wiki/Multiplication_algorithm
         * The rounding error will be maximum 1 Hz in this calculation.
         * frequency * ratio >> 22 = [ah al] * [bh bl] >> 22
         * [ah al] * [bh bl] >> 22 = ([bl * al] + (([bl * ah] + [bh * al]) << 16) + ([bh * ah]) << 32) >> 22
         *                         = (([bl * ah] + [bh * al]) >> 6) + ([bh * ah]) << 10)
         */
        frequency = ((bl*ah + bh*al + ((bl*al) >> 16)) >> 6) + ((bh*ah) << 10);
    }

    return frequency;
}
