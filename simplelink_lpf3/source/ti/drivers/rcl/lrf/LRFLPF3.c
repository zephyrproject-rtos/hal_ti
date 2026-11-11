/*
 * Copyright (c) 2021-2026, Texas Instruments Incorporated
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
 *  ======== LRFLPF3.c ========
 */

#include <stdint.h>
#include <stdlib.h>

#include <ti/drivers/rcl/LRF.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Feature.h>
#include <ti/drivers/rcl/hal/RCL_Hal.h>

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

/* Definitions for trim */
#define LRF_TRIM_NORMAL_BW    0
#define LRF_TRIM_HIGH_BW      1                 /* Revision >= 4 only */s
#define LRF_TRIM_MIN_VERSION_FULL_FEATURES  4U    /* Only AppTrims revision 4 and above has all features */
#define LRF_TRIM_VERSION_DCOLDO_TEMPERATURE_COMPENSATION 8U /* Only AppTrims revision 8 and above have DCOLDO temperature compensation */

/* RCL-335: Some CC23X0R5 devices (State D) have an error in the programmed RSSI offset */
#define LRF_TRIM_VERSION_RSSIOFFSET_ISSUE_CC23X0R5 4U     /* AppTrims revision with issue in rssiOffset field */
#define LRF_TRIM_LIMIT_RSSIOFFSET_ISSUE_CC23X0R5  (-4)   /* If rssiOffset is less or equal to this, apply correction */
#define LRF_TRIM_CORRECTION_RSSIOFFSET_ISSUE_CC23X0R5 5  /* Correction to apply to devices with wrong RSSI offset */

/* RCL-616: DCOLDO0:FIRSTTRIM is hardcoded to 8 and DCOLDO0:SECONDTRIM is increased by 10 for CC27XX state B devices */
#define LRF_TRIM_DCOLDO0_SECONDTRIM_INC_STATE_B_DCOLDO_WORKAROUND_CC27XX 10U    /* DCOLDO0:SECONDTRIM needs to be increased by 10 on CC27XX state B devices */
#define LRF_TRIM_DCOLDO0_SECONDTRIM_CODED_BITS_MASK ((1U << 3U) | (1U << 5U))    /* Bits mask for bit 3 and 5 of DCOLDO0:SECONDTRIM */
#define LRF_TRIM_DCOLDO0_SECONDTRIM_MAX_STATE 63U    /* DCOLDO0:SECONDTRIM maximum value allowed within the range of 6-bit representation */
#define LRF_TRIM_DCOLDO0_FIRSTTRIM_MIN_STATE -8    /* DCOLDO0:FIRSTTRIM minimum value allowed within the range of 4-bit two's complement representation */

/* Constants used for calculating DCOLDO max offset when doing DCOLDO temperature compensation */
#define LRF_DCOLDOSECOND_HIGH_TEMP_ADJ_FACTOR 5
#define LRF_DCOLDOSECOND_LOW_TEMP_ADJ_FACTOR  5
#define LRF_DCOLDO_DEADBAND 10
#define LRF_DCOLDO_OFFSET_LOWER_SATURATION 0
/* The adjacent factor for DCOLDOFIRST is 2.5, this is represented as "5 >> 1" with following macros to avoid using float values */
#define LRF_DCOLDOFIRST_HIGH_TEMP_ADJ_FACTOR_S  1
#define LRF_DCOLDOFIRST_HIGH_TEMP_ADJ_FACTOR_MUL 5
#define LRF_DCOLDOFIRST_LOW_TEMP_ADJ_FACTOR_S   1
#define LRF_DCOLDOFIRST_LOW_TEMP_ADJ_FACTOR_MUL 5
/* Factor which is only needed for DCOLDOSECOND */
#define LRF_DCOLDOSECOND_FACTOR 2
/* This constant shifted 24 bits to approximates to 1/9 */
#define DIV_BY_NINE_CONSTANT 1864135U
/* Offest values in the DCOLDO compensation calculations */
#define LRF_DCOLDO_OFFSET_HIGH_TEMP 16
#define LRF_DCOLDO_OFFSET_LOW_TEMP 9
/* Shift values in the DCOLDO compensation calculations */
#define LRF_DCOLDO_SHIFT_HIGH_TEMP 5
#define LRF_DCOLDO_SHIFT_LOW_TEMP 25

/* Nominal temperature (degrees C) for offset definitions */
#define LRF_TEMPERATURE_NOM 25

#define LRF_DCDC_IPEAK_RF_ACTIVITY  3U

/* Only the lower 8-bits of the LRFDPBE_O_GPOCTRL are supported */
#define LRF_PBE_GPOCTRL_MASK 0xFFU

/* Set the LRFDRFE_O_SPARE5[14] bit to enable PA ESD protection */
#define LRF_CC27XX_RFE_SPARE5_PA_20DBM_ESD_CTRL_SET                      ((uint32_t)(0x1 << 14U))
#define LRF_CC27XX_PA_ESD_PROTECTION_VDDS_THRESHOLD_MV                   ((uint16_t)3635)
#define LRF_CC27XX_HIGH_PA_MODE                                          ((uint16_t)0x3)
#define LRF_CC27XX_RETRIEVE_PA_MODE_FROM_RAW_VALUE(txPowerRawValue)      (((uint16_t)(txPowerRawValue) >> 11) & 0x3U)

/* Set the LRFDRFE_O_SPARE5[13] bit to enable RTRIM Tx temperature compensation */
#define LRF_CC27XX_RFE_SPARE5_RTRIM_TX_COMP_BITMASK                      ((uint32_t)(0x1 << 13U))

/* Convert from 4-bit sign-magnitude to 8-bit signed (two's complement) */
#define LRF_TRIM_SIGN_MAG_TO_SIGNED(x) (int8_t)(((x & 0x8) ? -(x & 0x7) : (x & 0x7)))

/* Defined thresholds for VDDS compensation */
#define LRF_TxPower_Use_Vdds_Comp                                        ((LRF_TxPowerTable_Index){.fraction = 0, .dBm = 18})
#define LRF_CC27XX_VDDS_THRESHOLD_0                                      ((uint16_t)2850)
#define LRF_CC27XX_VDDS_THRESHOLD_1                                      ((uint16_t)3150)
#define LRF_CC27XX_VDDS_THRESHOLD_2                                      ((uint16_t)3450)

/* Factors needed for temperature coefficient compensation calculations */
#define LRF_CC27XX_SCALE_TEMP_COEFF 1024
#define LRF_CC27XX_NOM_TEMP_FACTOR 16 /* Resolution in FCFG field is 16 degrees/LSB, covering a range from -96 C to 112 C */
#define LRF_TxPower_Min_Temp_Coeff_Comp                                  ((LRF_TxPowerTable_Index){.fraction = 0, .dBm = 4})
#define LRF_TxPower_Max_Temp_Coeff_Comp                                  ((LRF_TxPowerTable_Index){.fraction = 0, .dBm = 20})

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
static void LRF_temperatureCompensateDcoldo(int32_t temperature, const LRF_TrimDef *trimDef);
static uint32_t LRF_findExtTrim1TrimAdjustment(uint32_t temperatureDiff, uint32_t tempThreshFactor, uint32_t maxAdjustment);
static int32_t LRF_findExtTrim0TrimAdjustment(int32_t temperature, int32_t tempCompFactor, int32_t offset);
static uint32_t LRF_scaleFreqWithHFXTOffset(uint32_t frequency);
static void LRF_temperatureNotification(int16_t currentTemperature);
static void LRF_applyAntennaSelection(void);
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
static inline bool LRF_requirePaEsdProtection(void);
#endif

uint32_t swParamList[sizeof(LRF_SwParam)/sizeof(uint32_t)];
const size_t swParamListSz = sizeof(LRF_SwParam);

static struct {
    const LRF_TOPsmImage   *pbeLoaded;
    const LRF_TOPsmImage   *mceLoaded;
    const LRF_TOPsmImage   *rfeLoaded;
    uint16_t                phyFeatures;
    int16_t                 lastTrimTemperature;
    LRF_TxPowerTable_Entry  currentTxPower;
    LRF_TxPowerTable_Entry  rawTxPower;
} lrfPhyState = {0};

/* Required time from enabling refsys to synth programming */
#define LRF_REFSYS_ENABLE_TIME RCL_SCHEDULER_SYSTIM_US(30)

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/* Stores the previous DCDC IPEAK setting to be set after RF activity */
static uint8_t dcdcIpeakRestoreSetting;
#endif

/* Temperature threshold (degrees C) for use by the temperature monitoring. A value of 0 disables the feature. */
uint16_t rclTemperatureThreshold = 8;

/* Coexistence configuration to use if no other configuration is provided through SysConfig or other file.
 * This default configuration disables coex. */
const LRF_CoexConfiguration lrfCoexConfiguration __attribute__((weak)) =
{
    .T1 = 0,
    .T2 = 0,
    .grantPin = RFE_COMMON_RAM_GRANTPIN_CFG_DIS >> RFE_COMMON_RAM_GRANTPIN_CFG_S,
    .invertedPriority = false,
    .ieeeTSync = RCL_SCHEDULER_SYSTIM_US(140),
    .ieeeCorrMask = 0x03,
};

/* Regulatory mask to use if no other configuration is provided through SysConfig or other file.
 * This default configuration disables the use of power limitation tables. */
const uint8_t rclRegulatoryMask __attribute__((weak)) = 0x00;

/* Bit mask indicating which bits in LRFDPBE_GPOCTRL register are written
 * This is the configuration supposed to not change during runtime and allowed
 * to be customized per project or platform
 */
__attribute__((weak)) uint8_t rclPbeGpoMask = 0x00;

/* Default value set to LRFDPBE_GPOCTRL, which specifies the default antennas if rclPbeGpoMask is non-zero */
static uint8_t rclPbeGpoVal = 0;

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
            Log_printf(LogModule_RCL, Log_INFO, "LRF_setupRadio: Performing full setup");
            trimUpdate = trimFullUpdate;
        }
        else
        {
            includeBase = LRF_ApplySettings_NoBase;
            if (phyFeatures != lrfPhyState.phyFeatures)
            {
                Log_printf(LogModule_RCL, Log_INFO, "LRF_setupRadio: Changing PHY features");
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
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FCMD) & 0x0FFFU) >> 2;
        /* Turn off coex grant signal in RFE */
        LRF_disableCoexGrant();
        /* Check if a default value needs to be set for LRFDPBE_O_GPOCTRL */
        if (rclPbeGpoMask != 0U)
        {
            LRF_applyAntennaSelection();
        }
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
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_PATRIM01) = trimDef->trim0.pa2trim01;
        HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_PATRIM23) = trimDef->trim4.pa2trim23;
#else
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_PA0)        = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_PA0) | trimDef->trim0.pa0;
#endif
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_ATSTREFH)   = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_ATSTREFH) | trimDef->trim0.atstRefH;

        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_LNA)        = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_LNA) | trimDef->trim1.lna;
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) | trimDef->trim1.ifampRfLdo;

        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCALDO)  = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCALDO) | trimDef->trim2.ifadcAldo;
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCDLDO)  = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFADCDLDO) | trimDef->trim2.ifadcDldo;

        /* DEMIQMC0 has no fields not to be trimmed */
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMIQMC0)   =  trimDef->trim4.demIQMC0;

        /* Write trim to shadow registers */
        HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_IFAMPRFLDODEFAULT) = HWREGH_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_IFAMPRFLDO) & LRFDRFE_IFAMPRFLDO_TRIM_M;

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
                ((uint32_t) trimDef->trimVariant[bwIndexDither].ifadc0 & (LRFDRFE_IFADC0_DITHEREN_M | LRFDRFE_IFADC0_DITHERTRIM_M));
        }
    }
}

static void LRF_setTemperatureTrim(const LRF_TrimDef *trimDef)
{
    if (trimDef != NULL)
    {
        /* Remove trim fields from registers with temperature compensation */
        HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOF) = (uint16_t) (HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOF) & (~RFE_COMMON_RAM_DIVLDOF_VOUTTRIM_M));
        HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOI) = (uint16_t) (HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOI) & (~RFE_COMMON_RAM_DIVLDOI_VOUTTRIM_M));
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_TDCLDO)              = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_TDCLDO) & (~LRFDRFE_TDCLDO_VOUTTRIM_M);
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCO)                 = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCO) & (~LRFDRFE_DCO_TAILRESTRIM_M);
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0)             = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0) &  (~(LRFDRFE_DCOLDO0_SECONDTRIM_M | LRFDRFE_DCOLDO0_FIRSTTRIM_M));

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

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/* Maximum allowed value (saturation value) for RTRIM. For CC27XX devices saturate at the maximum allowed value in FCFG. Ref. RCL-1071 */
#define LRF_DEFAULT_RTRIM_MAX 15U
#else
/* Maximum allowed value (saturation value) for RTRIM, except if RTRIM value in FCFG is above this level */
#define LRF_DEFAULT_RTRIM_MAX 12U
#endif

/* Number of shifts in temperature compensation for fields in lrfdrfeExtTrim0 */
#define LRF_EXTTRIM0_TEMPERATURE_SCALE_EXP 7

/* Lowest temperature supported */
#define LRF_TEMPERATURE_MIN (-40)
/* Highest temperature supported */
#define LRF_TEMPERATURE_MAX 125

/* Bit masks and positions in SPARE0 and SPARE1 */
/* RFE_SPARE0: Fast AGC only */
#define RFE_SPARE0_LOW_GAIN_BM  0x000FU
#define RFE_SPARE0_LOW_GAIN     0U
#define RFE_SPARE0_HIGH_GAIN_BM 0x00F0U
#define RFE_SPARE0_HIGH_GAIN    4U
/* RFE_SPARE1: Fast AGC: Threshold. Standard AGC: Magnitude */
/* These fields have the same position in the register */
#define RFE_SPARE1_AGC_VALUE_BM 0x000FFU
#define RFE_SPARE1_AGC_VALUE    0U

static void LRF_temperatureCompensateTrim(const LRF_TrimDef *trimDef)
{
    uint32_t divLdoTempOffset = 0;
    uint32_t tdcLdoTempOffset = 0;
    uint32_t rtrimTempOffset = 0;
    int32_t rssiTempOffset = 0;
    int32_t agcValOffset = 0;
    int32_t agcHighGainOffset = 0;
    int32_t agcLowGainOffset = 0;
    int16_t temperature = RCL_Hal_getTemperature();

    lrfPhyState.lastTrimTemperature = temperature;

    if (trimDef->revision >= LRF_TRIM_MIN_VERSION_FULL_FEATURES)
    {
        LRF_Trim_tempLdoRtrim tempLdoRtrim = trimDef->trim3.fields.lrfdrfeExtTrim1.tempLdoRtrim;

        int16_t tempThreshLow = LRF_TEMPERATURE_MIN + (int16_t) (tempLdoRtrim.tThrl * (1U << LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP));
        int16_t tempThreshHigh = LRF_TEMPERATURE_MAX - (int16_t) (tempLdoRtrim.tThrh * (1U << LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP));

        /* Adjust values for extreme temperatures */
        if (temperature < tempThreshLow)
        {
            uint32_t temperatureDiff = (uint32_t) (tempThreshLow - temperature);
            divLdoTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrl,
                LRF_DIVLDO_LOW_TEMP_ADJ_FACTOR * tempLdoRtrim.divLdoMinOffset);
            tdcLdoTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrl,
                LRF_TDCLDO_LOW_TEMP_ADJ_FACTOR * tempLdoRtrim.tdcLdoMinOffset);
            rtrimTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrl,
                LRF_RTRIM_LOW_TEMP_ADJ_FACTOR * tempLdoRtrim.rtrimMinOffset);
        }
        else if (temperature > tempThreshHigh)
        {
            uint32_t temperatureDiff = (uint32_t) (temperature - tempThreshHigh);
            divLdoTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrh,
                LRF_DIVLDO_HIGH_TEMP_ADJ_FACTOR * tempLdoRtrim.divLdoMaxOffset);
            tdcLdoTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrh,
                LRF_TDCLDO_HIGH_TEMP_ADJ_FACTOR * tempLdoRtrim.tdcLdoMaxOffset);
            rtrimTempOffset = LRF_findExtTrim1TrimAdjustment(temperatureDiff, tempLdoRtrim.tThrh,
                LRF_RTRIM_HIGH_TEMP_ADJ_FACTOR * tempLdoRtrim.rtrimMaxOffset);
        }
        else
        {
            /* Do nothing */
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

    LRF_temperatureCompensateDcoldo(temperature, trimDef);

    uint32_t divLdoVoutTrim = trimDef->trim1.fields.divLdo.voutTrim;

    /* Most significant bit is inverted */
    divLdoVoutTrim ^= 0x40U;

    divLdoVoutTrim += divLdoTempOffset;

    /* Saturate at maximum value */
    if (divLdoVoutTrim > (LRFDRFE_DIVLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S))
    {
        divLdoVoutTrim = (LRFDRFE_DIVLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S);
    }
    /* Write back with most signigicant bit inverted back */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOF) = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOF) | (((uint16_t) divLdoVoutTrim ^ 0x40U) << RFE_COMMON_RAM_DIVLDOF_VOUTTRIM_S);

    /* Add offset to initial value */
    divLdoVoutTrim += HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOIOFF);

    /* Saturate at maximum value */
    if (divLdoVoutTrim > (LRFDRFE_DIVLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S))
    {
        divLdoVoutTrim = (LRFDRFE_DIVLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S);
    }
    /* Write back with most signigicant bit inverted back */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOI) = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_DIVLDOI) | (((uint16_t) divLdoVoutTrim ^ 0x40U) << RFE_COMMON_RAM_DIVLDOI_VOUTTRIM_S);

    uint32_t tdcLdoVoutTrim = trimDef->trim1.fields.tdcLdo.voutTrim;

    if (tdcLdoTempOffset > 0U)
    {
        /* Most significant bit is inverted */
        tdcLdoVoutTrim ^= 0x40U;

        tdcLdoVoutTrim += tdcLdoTempOffset;

        /* Saturate at maximum value */
        if (tdcLdoVoutTrim > (LRFDRFE_TDCLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S))
        {
            tdcLdoVoutTrim = (LRFDRFE_TDCLDO_VOUTTRIM_ONES >> LRFDRFE_DIVLDO_VOUTTRIM_S);
        }

        /* Invert back */
        tdcLdoVoutTrim ^= 0x40U;
    }
    /* Write back */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_TDCLDO) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_TDCLDO) | (tdcLdoVoutTrim << LRFDRFE_TDCLDO_VOUTTRIM_S);

    uint32_t rtrim = trimDef->trim2.fields.dco.tailresTrim;

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
#if defined(DeviceFamily_PARENT) && (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    /* RTRIM Tx Compensation might be required depending on the selected Tx output power. For now, initialize RAM registers to default values. */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RTRIMTXCMP) = 0;
    /* Write rtrim into RAM register instead of the usual register (LRFDRFE:DCO.TAILRESTRIM) */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RTRIM) = (rtrim << RFE_COMMON_RAM_RTRIM_VAL_S);
    /* Signal the LRF to use the default RTRIM value. This might change based on the programmed Tx output power */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE5) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE5) & ~(LRF_CC27XX_RFE_SPARE5_RTRIM_TX_COMP_BITMASK);
#else
    /* Write into register */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCO) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCO) | (rtrim << LRFDRFE_DCO_TAILRESTRIM_S);
#endif

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
    rssiOffset += (int32_t) HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_PHYRSSIOFFSET);

    /* Store in HW register */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_RSSIOFFSET) = (uint32_t) rssiOffset;

    if (((HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_AGCINFO) & RFE_COMMON_RAM_AGCINFO_MODE_M) >> RFE_COMMON_RAM_AGCINFO_MODE_S) == (RFE_COMMON_RAM_AGCINFO_MODE_FAST >> RFE_COMMON_RAM_AGCINFO_MODE_S))
    {
        uint32_t spare0Val = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_SPARE0SHADOW);
        if (agcHighGainOffset != 0 || agcLowGainOffset != 0)
        {
            int32_t lowGain = (int32_t) ((spare0Val & RFE_SPARE0_LOW_GAIN_BM) >> RFE_SPARE0_LOW_GAIN);
            int32_t highGain = (int32_t) ((spare0Val & RFE_SPARE0_HIGH_GAIN_BM) >> RFE_SPARE0_HIGH_GAIN);
            if (agcLowGainOffset != 0)
            {
                lowGain += agcLowGainOffset;
                if (lowGain < 0)
                {
                    lowGain = 0;
                }
                if (lowGain > (int32_t) (RFE_SPARE0_LOW_GAIN_BM >> RFE_SPARE0_LOW_GAIN))
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
                if (highGain > (int32_t) (RFE_SPARE0_HIGH_GAIN_BM >> RFE_SPARE0_HIGH_GAIN))
                {
                    highGain = (RFE_SPARE0_HIGH_GAIN_BM >> RFE_SPARE0_HIGH_GAIN);
                }
            }
            spare0Val = (spare0Val & ~(RFE_SPARE0_LOW_GAIN_BM | RFE_SPARE0_HIGH_GAIN_BM)) |
                (uint32_t) (lowGain << RFE_SPARE0_LOW_GAIN) | (uint32_t) (highGain << RFE_SPARE0_HIGH_GAIN);
        }
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE0) = spare0Val;
    }

    uint32_t spare1Val = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_SPARE1SHADOW);
    if (agcValOffset != 0)
    {
        int32_t agcVal = (int32_t) ((spare1Val & RFE_SPARE1_AGC_VALUE_BM) >> RFE_SPARE1_AGC_VALUE);
        agcVal += agcValOffset;
        if (agcVal < 0)
        {
            agcVal = 0;
        }
        if (agcVal > (int32_t) (RFE_SPARE1_AGC_VALUE_BM >> RFE_SPARE1_AGC_VALUE))
        {
            agcVal = (RFE_SPARE1_AGC_VALUE_BM >> RFE_SPARE1_AGC_VALUE);
        }
        spare1Val = (uint32_t) ((spare1Val & ~RFE_SPARE1_AGC_VALUE_BM) | ((uint32_t) agcVal << RFE_SPARE1_AGC_VALUE));
    }
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE1) = spare1Val;
}

/* Represent 1/3 with the approximation LRF_ONE_THIRD_MANTISSA * 2^(-LRF_ONE_THIRD_NEG_EXP) */
#define LRF_ONE_THIRD_MANTISSA 21845U /* (round(1/3 * 2^16)) */
#define LRF_ONE_THIRD_NEG_EXP  16U
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
            adjustment = ((temperatureDiff * maxAdjustment) + (1U << (LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP - 1U))) >> LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP;
            break;
        case 2:
            /* tempThreshFactor = 2:
               adjustment = round((temperatureDiff * maxAdjustment) / (2 * 2^LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP)) */
            adjustment = ((temperatureDiff * maxAdjustment) + (1U << LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP)) >> (LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP + 1U);
            break;
        case 3:
            /* tempThreshFactor = 3:
               adjustment = round((temperatureDiff * maxAdjustment) / (3 * 2^LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP))
               Use approximation with multiplication to avoid performing division */
            adjustment = ((temperatureDiff * maxAdjustment * LRF_ONE_THIRD_MANTISSA) + (1U << (LRF_EXTTRIM1_TEMPERATURE_SCALE_EXP + LRF_ONE_THIRD_NEG_EXP - 1U)))
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

/* Calculate temperature compensation for Dcoldo values */
/* temperature: temperature (degrees C) */
/* Function uses FCFG values dcoldoSecondMaxOffset, dcoldoSecondMinOffset, dcoldoFirstMaxOffset and dcoldoFirstMinOffset
   to adjust offset of the DCOLDO values based on temperature.
   For temperatures over 35:
       offsetDcoLdoSecond = (((-(25-temperature)-10) * 2 * dcoldoSecondMaxOffset) + 16) / 32
       offsetDcoLdoFirst  = (((-(25-temperature)-10) * dcoldoSecondMaxOffset) + 16) / 32
   For temperatures under 15:
       offsetDcoLdoSecond = (((25-temperature)-10) * 2 * dcoldoSecondMinOffset) + 9) / 18
       offsetDcoLdoFirst  = (((25-temperature)-10) * dcoldoSecondMinOffset) + 9) / 18
   For temperatures between 15 and 35:
       offsetDcoLdoSecond = 0
       offsetDcoLdoFirst  = 0    */
static void LRF_temperatureCompensateDcoldo(int32_t temperature, const LRF_TrimDef *trimDef)
{
    uint32_t trimDcoldo0Val;
    if (trimDef->revision >= LRF_TRIM_VERSION_DCOLDO_TEMPERATURE_COMPENSATION) {
        /* Only compensate if temperature is outside deadband limits */
        int32_t offsetDcoLdoFirst = 0;
        int32_t offsetDcoLdoSecond = 0;
        if ((temperature >= LRF_TEMPERATURE_NOM + LRF_DCOLDO_DEADBAND) || (temperature <=  LRF_TEMPERATURE_NOM - LRF_DCOLDO_DEADBAND))
        {
            int32_t dcoldoSecondMaxOffset = (int32_t) trimDef->trim3.fields.lrfdrfeExtTrim1.dcoldoOffset.dcoldoSecondMaxOffset;
            int32_t dcoldoSecondMinOffset = (int32_t) trimDef->trim3.fields.lrfdrfeExtTrim1.dcoldoOffset.dcoldoSecondMinOffset;
            int32_t dcoldoFirstMaxOffset  = (int32_t) trimDef->trim3.fields.lrfdrfeExtTrim1.dcoldoOffset.dcoldoFirstMaxOffset;
            int32_t dcoldoFirstMinOffset  = (int32_t) trimDef->trim3.fields.lrfdrfeExtTrim1.dcoldoOffset.dcoldoFirstMinOffset;

            int32_t tempDiff = LRF_TEMPERATURE_NOM - temperature;
            int32_t upperSaturationFirst;
            int32_t upperSaturationSecond;
            /* Calculate offset values for the trims, also set upper saturation */
            if (temperature > LRF_TEMPERATURE_NOM)
            {
                offsetDcoLdoSecond = (int32_t) (((-tempDiff-LRF_DCOLDO_DEADBAND) * LRF_DCOLDOSECOND_FACTOR * dcoldoSecondMaxOffset) + LRF_DCOLDO_OFFSET_HIGH_TEMP) >> LRF_DCOLDO_SHIFT_HIGH_TEMP;
                offsetDcoLdoFirst  = (int32_t) (((-tempDiff-LRF_DCOLDO_DEADBAND) * dcoldoFirstMaxOffset) + LRF_DCOLDO_OFFSET_HIGH_TEMP) >> LRF_DCOLDO_SHIFT_HIGH_TEMP;
                upperSaturationSecond = dcoldoSecondMaxOffset * LRF_DCOLDOSECOND_HIGH_TEMP_ADJ_FACTOR;
                upperSaturationFirst  = (dcoldoFirstMaxOffset * LRF_DCOLDOFIRST_HIGH_TEMP_ADJ_FACTOR_MUL) >> LRF_DCOLDOFIRST_HIGH_TEMP_ADJ_FACTOR_S;
            }
            else
            {
                offsetDcoLdoSecond = (int32_t) ((((tempDiff-LRF_DCOLDO_DEADBAND) * LRF_DCOLDOSECOND_FACTOR * dcoldoSecondMinOffset) + LRF_DCOLDO_OFFSET_LOW_TEMP) * DIV_BY_NINE_CONSTANT) >> LRF_DCOLDO_SHIFT_LOW_TEMP;
                offsetDcoLdoFirst  = (int32_t) ((((tempDiff-LRF_DCOLDO_DEADBAND) * dcoldoFirstMinOffset) + LRF_DCOLDO_OFFSET_LOW_TEMP)  * DIV_BY_NINE_CONSTANT) >> LRF_DCOLDO_SHIFT_LOW_TEMP;
                upperSaturationSecond = dcoldoSecondMinOffset * LRF_DCOLDOSECOND_LOW_TEMP_ADJ_FACTOR;
                upperSaturationFirst  = (dcoldoFirstMinOffset * LRF_DCOLDOFIRST_LOW_TEMP_ADJ_FACTOR_MUL) >> LRF_DCOLDOFIRST_LOW_TEMP_ADJ_FACTOR_S;
            }

            /* Saturate values if out of bounds */
            if (offsetDcoLdoSecond > upperSaturationSecond)
            {
                offsetDcoLdoSecond = upperSaturationSecond;
            }
            if (offsetDcoLdoSecond < LRF_DCOLDO_OFFSET_LOWER_SATURATION)
            {
                offsetDcoLdoSecond = LRF_DCOLDO_OFFSET_LOWER_SATURATION;
            }

            if (offsetDcoLdoFirst > upperSaturationFirst)
            {
                offsetDcoLdoFirst = upperSaturationFirst;
            }
            if (offsetDcoLdoFirst < LRF_DCOLDO_OFFSET_LOWER_SATURATION)
            {
                offsetDcoLdoFirst = LRF_DCOLDO_OFFSET_LOWER_SATURATION;
            }
        }

        /* Get trim values to add offset */
        trimDcoldo0Val = trimDef->trim2.dcoLdo0;
        uint32_t secondTrimVal = (trimDcoldo0Val & LRFDRFE_DCOLDO0_SECONDTRIM_M) >> LRFDRFE_DCOLDO0_SECONDTRIM_S;
        int32_t firstTrimVal = (int32_t) ((trimDcoldo0Val & LRFDRFE_DCOLDO0_FIRSTTRIM_M) >> LRFDRFE_DCOLDO0_FIRSTTRIM_S);

        /* Sign extend DCOLDO0:FIRSTTRIM since it is a negative value */
        firstTrimVal = ((firstTrimVal << (int32_t) (32U - LRFDRFE_DCOLDO0_FIRSTTRIM_W )) >> (int32_t) (32U - LRFDRFE_DCOLDO0_FIRSTTRIM_W));

        /* Invert bit 3 and 5 to decode the SECONDTRIM value */
        uint32_t secondTrimValDecoded = secondTrimVal ^ LRF_TRIM_DCOLDO0_SECONDTRIM_CODED_BITS_MASK;

        /* Add offset to trim values */
        uint32_t newSecondTrimVal = secondTrimValDecoded + (uint32_t) offsetDcoLdoSecond;

        /* The voltage output of DCOLDO0:FIRSTTRIM has a negative slope where the minimum trim value gives the maximum output voltage.
        For this reason we need to subtract the temperature offset instead of adding it. */
        int32_t newFirstTrimVal =  firstTrimVal - offsetDcoLdoFirst;

        /* DCOLDO0.SECONDTRIM is saturated at LRF_TRIM_DCOLDO0_SECONDTRIM_MAX_STATE */
        if (newSecondTrimVal > LRF_TRIM_DCOLDO0_SECONDTRIM_MAX_STATE)
        {
            newSecondTrimVal = LRF_TRIM_DCOLDO0_SECONDTRIM_MAX_STATE;
        }
        /* DCOLDO0.FIRSTTRIM is saturated at LRF_TRIM_DCOLDO0_FIRSTTRIM_MIN_STATE since it is a negative value */
        if (newFirstTrimVal < LRF_TRIM_DCOLDO0_FIRSTTRIM_MIN_STATE)
        {
            newFirstTrimVal = LRF_TRIM_DCOLDO0_FIRSTTRIM_MIN_STATE;
        }

        /* Invert bit 3 and 5 to encode the SECONDTRIM value */
        uint32_t newSecondTrimValCoded = newSecondTrimVal ^ LRF_TRIM_DCOLDO0_SECONDTRIM_CODED_BITS_MASK;

        /* Write offseted trim values to their register */
        trimDcoldo0Val = (trimDcoldo0Val & ~LRFDRFE_DCOLDO0_FIRSTTRIM_M) | (((uint32_t) (newFirstTrimVal) << LRFDRFE_DCOLDO0_FIRSTTRIM_S) &  LRFDRFE_DCOLDO0_FIRSTTRIM_M );
        trimDcoldo0Val = (trimDcoldo0Val & ~LRFDRFE_DCOLDO0_SECONDTRIM_M) | (newSecondTrimValCoded << LRFDRFE_DCOLDO0_SECONDTRIM_S);
    }
    else
    {
        trimDcoldo0Val = trimDef->trim2.dcoLdo0;
    }
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DCOLDO0) | trimDcoldo0Val;
}

void LRF_enable(void)
{
    /* Set MSGBOX register to 0 */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_MSGBOX) = 0;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    dcdcIpeakRestoreSetting = RCL_Hal_setDcdcIpeakSetting(LRF_DCDC_IPEAK_RF_ACTIVITY);
#endif

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
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    (void) RCL_Hal_setDcdcIpeakSetting(dcdcIpeakRestoreSetting);
#endif

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
    while (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_MSGBOX) == 0U)
    {
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
    pllMBase += 1U;
    pllMBase >>= 1;

    return pllMBase;
}

static uint32_t countLeadingZeros(uint16_t value)
{
   uint32_t numZeros = 0;
   if (value >= 0x0100U) {
      value >>= 8U;
   }
   else {
      numZeros += 8U;
   }
   if (value >= 0x10U) {
      value >>= 4U;
   }
   else {
      numZeros += 4U;
   }
   if (value >= 0x04U) {
      value >>= 2U;
   }
   else {
      numZeros += 2U;
   }
   if (value >= 0x02U) {
       /* No need to shift down value since this is the last step */
   }
   else {
      numZeros += 1U;
   }
   return numZeros;
}

static uint32_t LRF_findCalM(uint32_t frequency, uint32_t prediv)
{
    /* Find 2^47 / fref = 2^47 * prediv / fxtal */
    uint32_t frefInv = (fXtalInv.word[1] >> 4) * prediv;
    /* Round to 2^31 * prediv / fxtal */
    frefInv += 1U << 15;
    frefInv >>= 16;

    uint32_t calM;
    /* Find calM = frequency / fref (no fractional bits) */
    /* First, find calM = frequency / fref * 2^(31-15)) */
    calM = frefInv * ((frequency + (1U << 14)) >> 15);

    /* Divide by 2^16 with rounding to get calM = frequency / fref */
    calM += 1U << 15;
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
            absFrequencyOffset = (uint32_t) -frequencyOffset;
        }
        else
        {
            absFrequencyOffset = (uint32_t) frequencyOffset;
        }
        /* Calculate 2^41 * abs(frequencyOffset) / synthFrequency */
        absFrequencyOffset = (absFrequencyOffset + (1U << 5)) >> 6;
        absFrequencyOffset *= invSynthFreq;
        /* Round to 2^21 * abs(frequencyOffset) / synthFrequency */
        absFrequencyOffset = (absFrequencyOffset + (1U << 19)) >> 20;
        /* Re-intruduce sign */
        if (frequencyOffset < 0)
        {
            fOffRes = -(int32_t) absFrequencyOffset;
        }
        else
        {
            fOffRes = (int32_t) absFrequencyOffset;
        }

        return (((uint32_t)fOffRes) & LRFDRFE_MOD1_FOFF_M);
    }
}

#define NUM_TX_FILTER_TAPS 24U
/* deviation in Hz */
/* invSynthFreq = 2^51 / synthFrequency */
static void LRF_programShape(const LRF_TxShape *txShape, uint32_t deviation, uint32_t invSynthFreq)
{
    /* If txShape is NULL, do not program shape, but instead leave the values programmed as part of setup */
    if (txShape != NULL)
    {
        union {
            uint8_t  b[NUM_TX_FILTER_TAPS];
            uint32_t w[NUM_TX_FILTER_TAPS/4U];
        } filterCoeff;
        /* Find deviation * 2^29/fs * 2^10 */
        uint32_t deviationFactor1 = ((deviation >> 12) * invSynthFreq) +
            (((deviation & 0x0FFFU) * invSynthFreq) >> 12);
        /* Find deviation * 2^29/fs * scale / 2^16 */
        uint32_t scale = txShape->scale;
        uint32_t deviationFactor2 = ((((deviationFactor1 >> 15) * scale) >> 1) +
                                     (((deviationFactor1 & 0x7FFFU) * scale) >> 16) + (1U << 4)) >> 5;
        /* Find shapeGain and scaling */
        int32_t shapeGain = (int32_t) (8U - countLeadingZeros((uint16_t) (deviationFactor2 >> 11)));
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
            filterCoeff.b[i + startCoeff] = (uint8_t) (
                ((deviationFactor2 * txShape->coeff[i]) + (1U << (18U + (uint32_t) shapeGain))) >> (19U + (uint32_t) shapeGain));
        }

        /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        ASM_4_NOPS();
#endif
        for (uint32_t i = 0; i <  NUM_TX_FILTER_TAPS / 4U; i++)
        {
            *((unsigned long*) (LRFDRFE32_BASE + LRFDRFE32_O_DTX1_DTX0) + i) = filterCoeff.w[i];
        }
        if (shapeGain > 3)
        {
            /* TODO: Scale by adjusting the symbol mapping */
            shapeGain = 3;
        }
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_MOD0) = (HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_MOD0) & ~LRFDRFE_MOD0_SHPGAIN_M) | (uint32_t) (shapeGain << LRFDRFE_MOD0_SHPGAIN_S);
    }
}

static uint32_t LRF_findLog2Bde1(uint32_t demmisc3)
{
    uint32_t log2Bde1;
    if ((demmisc3 & LRFDMDM_DEMMISC3_BDE1FILTMODE_M) != 0U)
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
#define P_FACTOR 9U
/* Shift from P formula */
#define P_SHIFT 4U
/* Right shift of PLL M to allow 32-bit calculation */
#define Q_MAGN_SHIFT 6U
/* Number of bits in P and Q */
#define FRAC_NUM_BITS 28U
/* Number of extra bits in an uint32_t compared to the P and Q HW registers */
#define FRAC_EXTRA_BITS (32U - FRAC_NUM_BITS)
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

    leftShiftP = (int32_t) (log2Bde1 + log2PdifDecim + P_SHIFT);

    uint32_t demFracP = rateWord * bde2;
    if (demFracP > (uint32_t)((1ULL << 32) / P_FACTOR))
    {
        if ((demFracP & 1U) != 0U)
        {
            roundingError = true;
        }
        demFracP >>= 1;
        leftShiftP -= 1;
    }
    demFracP *= P_FACTOR;

    /* Preliminary calculation to find scaling factor - round PLLM upwards to ensure no overflow
       in final calculation */
    uint32_t demFracQ = ((pllMBase + ((1U << Q_MAGN_SHIFT) - 1U)) >> Q_MAGN_SHIFT) * pre;
    uint32_t num0Q = countLeadingZeros((uint16_t) (demFracQ >> 16));

    int32_t pllMShift = (int32_t) (Q_MAGN_SHIFT + FRAC_EXTRA_BITS - num0Q);
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
        pllMBaseRounded = (pllMBase + (1U << ((uint32_t) pllMShift - 1U))) >> (uint32_t) pllMShift;
        demFracQ = pllMBaseRounded * pre;
        /* Multiply PLLM back (rounding is now applied) */
        pllMBaseRounded <<= (uint32_t) pllMShift;
        leftShiftP -= pllMShift;
    }

    if (leftShiftP >= 0)
    {
        demFracP <<= leftShiftP;
    }
    else
    {
        /* Check if right shift of P introduces rounding error */
        if ((demFracP & ((1U << -leftShiftP) - 1U)) != 0U)
        {
            roundingError = true;
        }
        demFracP >>= -leftShiftP;
    }

    if (demFracP >= demFracQ)
    {
        Log_printf(LogModule_RCL, Log_ERROR, "LRF_programPQ: Error, resampler fraction greater than 1; demodulator will not work");
    }
    if (roundingError)
    {
        Log_printf(LogModule_RCL, Log_WARNING, "LRF_programPQ: Rounding error in fractional resampler");
    }
    if (pllMBaseRounded != pllMBase)
    {
        Log_printf(LogModule_RCL, Log_VERBOSE, "LRF_programPQ: PLLM base rounded from %08X to %08X to fit in fractional resampler", pllMBase, pllMBaseRounded);
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    /* Check if shadow register for downsampler coefficient P is in use */
    if ((HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_BAUDCOMP) & LRFDMDM_BAUDCOMP_FRAC_SHADOW) != 0U)
    {
        /* Write downsampler coefficient P to shadow registers for new Rx operations to restore */
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMCOHR3) = demFracP & 0x0000FFFFU;
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMCOHR4) = demFracP >> 16;
    }
#endif

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
        absRxIntFrequency = (uint32_t) (-rxIntFrequency);
    }
    else
    {
        absRxIntFrequency =  (uint32_t) rxIntFrequency;
    }

    absRxIntFrequency = (absRxIntFrequency + (1U << 5)) >> 6;
    /* Find 2^41 * abs(rxIntFrequency) / synthFrequency */
    uint32_t cMixN = absRxIntFrequency * invSynthFreq;
    /* Find 2^37 * abs(rxIntFrequency) / synthFrequency * 9 */
    cMixN = ((cMixN + (1U << 3)) >> 4) * 9U;

    /* Find 2^(15 + log2Bde1) * abs(rxIntFrequency) / synthFrequency * 9 */
    uint32_t rightShift = (37U - 15U) - LRF_findLog2Bde1(HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC3));
    cMixN = (cMixN + (1U << (rightShift - 1U))) >> rightShift;

    int32_t signedCMixN;
    /* Use inverse sign */
    if (rxIntFrequency > 0)
    {
        signedCMixN = -(int32_t) cMixN;
    }
    else
    {
        signedCMixN = (int32_t) cMixN;
    }
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        /* Workaround (RCL-489): Invert RX frequency programmed to account for swapped I and Q signals in CC27xx PG1.0
         * TODO: May be swapped back for later PGs
         */
    signedCMixN = -signedCMixN;
#endif

    cMixN = (uint32_t) signedCMixN & LRFDMDM_DEMMISC0_CMIXN_M;
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
        synthFrequency = frequency - (uint32_t) swConfig->txFrequencyOffset;
    }
    else
    {
        synthFrequency = frequency - (uint32_t) swConfig->rxFrequencyOffset
            - (uint32_t) swConfig->rxIntFrequency;
    }

    /* Compensate desired frequency for temperature-dependent offset in HFXT, if any */
    uint32_t synthFrequencyCompensated = LRF_scaleFreqWithHFXTOffset(synthFrequency);

    /* Frequency divided by 2^16, rounded */
    uint32_t frequencyDiv2_16 = (synthFrequency + (1U << 15)) >> 16;

    /* Start calculating 2^47/frequency (approximated as 2^31/(synthFrequency/2^16)) */
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_DIVIDEND) = 1U << 31;
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_DIVISOR) = frequencyDiv2_16;

    /* Write approximate freuency to RFE */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_K5) = (uint16_t) frequencyDiv2_16;

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
    while ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DIVSTA) & LRFDRFE_DIVSTA_STAT_M) != 0U)
    {
    }
    uint32_t invSynthFreq = HWREG_READ_LRF(LRFDRFE32_BASE + LRFDRFE32_O_QUOTIENT);

    /* Calculate intermediate frequencies */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RXIF) = (uint16_t) LRF_findFoff(swConfig->rxFrequencyOffset, invSynthFreq);
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_TXIF) = (uint16_t) LRF_findFoff(swConfig->txFrequencyOffset, invSynthFreq);

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
    if ((atstref & LRFDRFE32_ATSTREF_BIAS_M) == 0U)
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

int8_t LRF_readMaxRssi(void)
{
    return (int8_t)(HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_RSSIMAX) & LRFDRFE_RSSIMAX_VAL_M);
}

void LRF_initializeMaxRssi(int8_t initRssi)
{
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_RSSIMAX) = ((uint32_t)initRssi) & LRFDRFE_RSSIMAX_VAL_M;
}

void LRF_setRawTxPower(uint32_t value, uint32_t temperatureCoefficient)
{
    lrfPhyState.rawTxPower.value.rawValue = (uint16_t) value;
    lrfPhyState.rawTxPower.tempCoeff = (uint8_t) temperatureCoefficient;
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

void LRF_enableCoexGrant(void)
{
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_GRANTPIN) =
        (lrfCoexConfiguration.grantPin << RFE_COMMON_RAM_GRANTPIN_CFG_S);
}

void LRF_disableCoexGrant(void)
{
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_GRANTPIN) =
        RFE_COMMON_RAM_GRANTPIN_CFG_DIS;
}

void LRF_deassertCoexRequest(void)
{
    /* Set coex REQUEST and PRIORITY lines low to indicate no request */
    /* Should only be done when PBE is finished */
    uint32_t pbeGpo = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_GPOCTRL);
    pbeGpo &= ~(LRFDPBE_GPOCTRL_GPO0_M | LRFDPBE_GPOCTRL_GPO1_M);
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_GPOCTRL) = pbeGpo;
}

/* Avoid IB = 0 as it effectively turns the PA off */
#define RFE_PA0_IB_MIN_USED 1

void LRF_programTemperatureCompensatedTxPower(void)
{
    LRF_TxPowerTable_Entry txPowerEntry = lrfPhyState.currentTxPower;
    uint8_t tempCoeff = txPowerEntry.tempCoeff;
    int32_t temperature = RCL_Hal_getTemperature();
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    if (rclFeatureControl.enableTxOutputPowerCompensation)
    {
        LRF_SwParam *swParam = (LRF_SwParam *) swParamList;

        /* Determine if temperature compensation of RTRIM is needed to ensure proper PA pulling for higher output powers */
        int8_t tempThreshold = swParam->trimDef->trim11.rtrimTxComp.thr;
        uint8_t rtrimAdjustment = swParam->trimDef->trim11.rtrimTxComp.fields.val;

        uint32_t minRtrim = HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RTRIMMIN);
        uint32_t rtrim = ((HWREGH_READ_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RTRIM) & RFE_COMMON_RAM_RTRIM_VAL_M) >> RFE_COMMON_RAM_RTRIM_VAL_S);

        /* Measure temperature and determine if RTRIM Tx compensation is needed */
        if (((uint8_t) tempThreshold != 0xFF) && (rtrimAdjustment != 0xF) && (LRF_CC27XX_RETRIEVE_PA_MODE_FROM_RAW_VALUE(txPowerEntry.value.rawValue) == LRF_CC27XX_HIGH_PA_MODE))
        {
            /* Read RTRIMCMPCMP from FCFG, add the value to the rtrim value, and write the result to RFERAM:RTRIMTXCMP */
            /* Trim value is given in 4-bit sign-magnitude, convert to signed 8-bit (twos-complement) before adding */
            int8_t convertedRtrimAdjustment = LRF_TRIM_SIGN_MAG_TO_SIGNED(rtrimAdjustment);
            int32_t adjustedRtrim = (int32_t) rtrim + (int32_t) convertedRtrimAdjustment;

            /* Saturate to take care of potential overflows and underflows */
            if (adjustedRtrim > LRF_DEFAULT_RTRIM_MAX)
            {
                adjustedRtrim = LRF_DEFAULT_RTRIM_MAX;
            }
            if (adjustedRtrim < minRtrim)
            {
                adjustedRtrim = minRtrim;
            }

            /* Write adjusted value to RFERAM:RTRIMTXCMP */
            HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RTRIMTXCMP) = ((uint32_t) (adjustedRtrim) << RFE_COMMON_RAM_RTRIMTXCMP_VAL_S);

            /*
            * Use measured temperature, compare with threshold in FCFG and determine if compensation is needed. If compensation is
            * needed, use LRFDRFE_O_SPARE5[13] to signal the LRF that the value in RFE_COMMON_RAM_O_RTRIMTXCMP should be used. Otherwise,
            * use the value in RFE_COMMON_RAM_O_RTRIM.
            */
            if (temperature <= tempThreshold)
            {
                /* Signal LRF about the need for RTRIM temperature compensation */
                txPowerEntry.value.rtrimTxCompCtl = 1;
            }
            else
            {
                /* Do not apply compensation */
                txPowerEntry.value.rtrimTxCompCtl = 0;
            }
        }
        else
        {
            /* Do not apply compensation */
            txPowerEntry.value.rtrimTxCompCtl = 0;
        }
    }
#endif

    if (tempCoeff != 0U)
    {
        int32_t ib = txPowerEntry.value.ib;
        /* Linear adjustment of IB field as a function of temperature, scaled
         * by the coefficient for the given setting */
        ib += ((temperature - LRF_TXPOWER_REFERENCE_TEMPERATURE) * (int32_t) tempCoeff)
            / LRF_TXPOWER_TEMPERATURE_SCALING;
        /* Saturate IB */
        if (ib <  RFE_PA0_IB_MIN_USED)
        {
            ib = RFE_PA0_IB_MIN_USED;
        }
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        /* TODO: See RCL-444. Use LRFDRFE_PA1_IB_MAX for CC27XX. */
        if (ib > (LRFDRFE_PA1_IB_MAX >> LRFDRFE_PA1_IB_S))
        {
            ib =  (LRFDRFE_PA1_IB_MAX >> LRFDRFE_PA1_IB_S);
        }
#else
        if (ib > (LRFDRFE_PA0_IB_MAX >> LRFDRFE_PA0_IB_S))
        {
            ib = (LRFDRFE_PA0_IB_MAX >> LRFDRFE_PA0_IB_S);
        }
#endif
        txPowerEntry.value.ib = (uint16_t) ib;
    }

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    if (rclFeatureControl.enablePaEsdProtection && (txPowerEntry.value.mode == LRF_CC27XX_HIGH_PA_MODE))
    {
        if (LRF_requirePaEsdProtection())
        {
            txPowerEntry.value.pa20dBmEsdCtl = 1;
        }
    }
#endif
    /* Program into RFE shadow register for PA power */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE5) = txPowerEntry.value.rawValue;
}

LRF_TxPowerResult LRF_programTxPower(LRF_TxPowerTable_Index powerLevel, uint32_t rfFreq)
{
    if (powerLevel.rawValue != LRF_TxPower_None.rawValue)
    {
        LRF_SwParam *swParam = (LRF_SwParam *) swParamList;
        LRF_TxPowerTable_Index adjustedTxPowerLevel = powerLevel;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        if (powerLevel.rawValue != LRF_TxPower_Use_Raw.rawValue)
        {
            /* Perform frequency specific output power limiting */
            if ((swParam->txPowerTable != NULL) && (swParam->txPowerTable->numEntries > 0))
            {
                /* Handle special input argument - return highest possible tx power. */
                if (powerLevel.rawValue == LRF_TxPower_Use_Max.rawValue)
                {
                    adjustedTxPowerLevel = swParam->txPowerTable[swParam->txPowerTable->numEntries - 1].powerTable->power;
                }
                if ((rclRegulatoryMask != 0) && (rfFreq != LRF_TXPOWER_BYPASS_FREQUENCY_BACKOFF) && (swParam->txPowerLimitTable != NULL) && (swParam->txPowerLimitTable->numEntries > 0))
                {
                    /*
                    * Iterate over all entries in the power limit table. If the current frequency is within the range of the entry
                    * and the regulatory domain mask matches, adjust the power level if necessary.
                    */
                    uint16_t scaledRfFreq = rfFreq / swParam->txPowerLimitTable->freqDiv;

                    for (uint8_t i = 0; i < swParam->txPowerLimitTable->numEntries; i++)
                    {
                        if (scaledRfFreq >= swParam->txPowerLimitTable->limitTable[i].minFreq &&
                            scaledRfFreq < swParam->txPowerLimitTable->limitTable[i].maxFreq &&
                            (rclRegulatoryMask & swParam->txPowerLimitTable->limitTable[i].regulatoryMask) != 0)
                        {
                            /*
                                * If the power level of the current entry is lower than the current power level, then adjust the
                                * power level.
                                */
                            if (swParam->txPowerLimitTable->limitTable[i].maxTxPower.rawValue < adjustedTxPowerLevel.rawValue)
                            {
                                adjustedTxPowerLevel.rawValue = swParam->txPowerLimitTable->limitTable[i].maxTxPower.rawValue;
                            }
                        }
                    }
                }
            }

            /* Consider additional Tx Output power compensation that might be needed by CC27..P.. devices */
            if (rclFeatureControl.enableTxOutputPowerCompensation)
            {
                /* Perform VDDS compensation. Use BATMON to measure VDDS voltage and determine if output Tx power needs to be compensated */
                if (adjustedTxPowerLevel.rawValue >= LRF_TxPower_Use_Vdds_Comp.rawValue)
                {
                    uint16_t vdds = RCL_Hal_getVddsVoltage();

                    if ((vdds <= LRF_CC27XX_VDDS_THRESHOLD_0) && (swParam->trimDef->trim11.vddsComp.fields.r0 != 0xF))
                    {
                        adjustedTxPowerLevel.dBm += LRF_TRIM_SIGN_MAG_TO_SIGNED(swParam->trimDef->trim11.vddsComp.fields.r0);
                    }
                    else if ((vdds <= LRF_CC27XX_VDDS_THRESHOLD_1) && (swParam->trimDef->trim11.vddsComp.fields.r1 != 0xF))
                    {
                        adjustedTxPowerLevel.dBm += LRF_TRIM_SIGN_MAG_TO_SIGNED(swParam->trimDef->trim11.vddsComp.fields.r1);
                    }
                    else if ((vdds <= LRF_CC27XX_VDDS_THRESHOLD_2) && (swParam->trimDef->trim11.vddsComp.fields.r2 != 0xF))
                    {
                        adjustedTxPowerLevel.dBm += LRF_TRIM_SIGN_MAG_TO_SIGNED(swParam->trimDef->trim11.vddsComp.fields.r2);
                    }
                    else if ((vdds > LRF_CC27XX_VDDS_THRESHOLD_2) && (swParam->trimDef->trim11.vddsComp.fields.r3 != 0xF))
                    {
                        adjustedTxPowerLevel.dBm += LRF_TRIM_SIGN_MAG_TO_SIGNED(swParam->trimDef->trim11.vddsComp.fields.r3);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }

                /* Perform temperature coefficient compensation by measuring temperature and checking for valid FCFG values  */
                if (swParam->trimDef->trim11.tempCoeffComp.value != 0xFFFF)
                {
                    int32_t temperature = RCL_Hal_getTemperature();
                    int32_t tempCoeffCompFactor = 0;

                    /* FCFG field corresponding to nomTmp needs to be converted from 4-bit sign-magnitude to a signed 8-bit representation */
                    int32_t convNomTmp = (int32_t) (LRF_TRIM_SIGN_MAG_TO_SIGNED(swParam->trimDef->trim11.tempCoeffComp.fields.nomTmp)) * LRF_CC27XX_NOM_TEMP_FACTOR;
                    uint8_t powerThreshold = LRF_TxPower_Max_Temp_Coeff_Comp.dBm - (uint8_t) swParam->trimDef->trim11.tempCoeffComp.fields.nomIdx;

                    /* Temp coefficient compensation only applies to power levels below the calculated power threshold and above 4 dBm */
                    if ((adjustedTxPowerLevel.dBm < powerThreshold) && (adjustedTxPowerLevel.dBm > LRF_TxPower_Min_Temp_Coeff_Comp.dBm))
                    {
                        int32_t tempDiff = temperature - convNomTmp;
                        uint16_t powerDiff = (powerThreshold - adjustedTxPowerLevel.dBm);
                        if (temperature > convNomTmp)
                        {
                            tempCoeffCompFactor = ((int32_t) powerDiff * tempDiff * ((int32_t) LRF_TRIM_SIGN_MAG_TO_SIGNED(swParam->trimDef->trim11.tempCoeffComp.fields.highCmp))) / LRF_CC27XX_SCALE_TEMP_COEFF;
                        }
                        else
                        {
                            tempCoeffCompFactor = ((int32_t) powerDiff * tempDiff * ((int32_t) LRF_TRIM_SIGN_MAG_TO_SIGNED(swParam->trimDef->trim11.tempCoeffComp.fields.lowCmp))) / LRF_CC27XX_SCALE_TEMP_COEFF;
                        }

                        adjustedTxPowerLevel.dBm += (int8_t) tempCoeffCompFactor;

                        /* Limit the compensation to 4 dBm. This is to account for non-linearities in the PA table */
                        if (adjustedTxPowerLevel.dBm < LRF_TxPower_Min_Temp_Coeff_Comp.dBm)
                        {
                            adjustedTxPowerLevel.dBm = LRF_TxPower_Min_Temp_Coeff_Comp.dBm;
                        }
                    }
                }
            }
        }
#endif //if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)

        LRF_TxPowerTable_Entry txPowerEntry = LRF_TxPowerTable_findValue(swParam->txPowerTable, adjustedTxPowerLevel);
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
    uint32_t ratio = RCL_Hal_getHfxtRatio();

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
    if (ratio != RCL_Hal_getHfxtRatioDefault())
    {
        uint32_t ah = frequency >> 16;      /* Multiplier high half-word */
        uint32_t al = frequency & 0xFFFFU;   /* Multiplier low half-word */

        uint32_t bh = ratio >> 16;          /* Multiplicand high half-word */
        uint32_t bl = ratio & 0xFFFFU;       /* Multiplicand low half-word */

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

/*
 *  ======== LRF_temperatureNotification ========
 */
static void LRF_temperatureNotification(int16_t currentTemperature)
{
    (void) currentTemperature;
    /* Post event to tell handler that radio operation should be restarted */
    (void) RCL_Scheduler_postEvent(rclSchedulerState.currCmd, RCL_EventSilentlyRestartRadio);
}

/*
 *  ======== LRF_enableTemperatureMonitoring ========
 */
void LRF_enableTemperatureMonitoring(void)
{
    if (rclFeatureControl.enableTemperatureMonitoring)
    {
        if (rclTemperatureThreshold != 0U)
        {
            RCL_Hal_setTemperatureNotification(lrfPhyState.lastTrimTemperature, rclTemperatureThreshold, LRF_temperatureNotification);
        }
    }
}

/*
 *  ======== LRF_disableTemperatureMonitoring ========
 */
void LRF_disableTemperatureMonitoring(void)
{
    if (rclFeatureControl.enableTemperatureMonitoring)
    {
        RCL_Hal_stopTemperatureNotification();
    }
}

/*
 *  ======== LRF_updateTemperatureCompensation ========
 */
void LRF_updateTemperatureCompensation(uint32_t rfFrequency, bool tx)
{
    if (rclFeatureControl.enableTemperatureMonitoring)
    {
        LRF_SwParam *swParam = (LRF_SwParam *) swParamList;
        /* Allow SWTCXO updates and adjust HFXT with missed updates */
        RCL_Hal_powerReleaseSwTcxoUpdateConstraint();
        /* Set RF frequency word based on updated HFXT value */
        LRF_programFrequency(rfFrequency, tx);
        /* Re-calculate temperature dependent trims */
        LRF_setTemperatureTrim(swParam->trimDef);
        /* Re-calculate TX power */
        LRF_programTemperatureCompensatedTxPower();
        /* Set new limit for temperature monitoring */
        LRF_enableTemperatureMonitoring();
        /* Stop SWTCXO updates again */
        RCL_Hal_powerSetSwTcxoUpdateConstraint();
    }
}

/*
 *  ======== LRF_updateTemperatureCompensation ========
 */
int16_t LRF_getLastTrimTemperature(void)
{
    return lrfPhyState.lastTrimTemperature;
}

/*
 * ======== LRF_setAntennaSelection ========
 */
void LRF_setAntennaSelection(uint32_t value)
{
    rclPbeGpoVal = (uint8_t) (value & LRF_PBE_GPOCTRL_MASK);
}

/*
 * ======== LRF_applyAntennaSelection ========
 */
static void LRF_applyAntennaSelection(void)
{
    uint32_t pbeGpoVal = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_GPOCTRL);
    pbeGpoVal &= ~((uint32_t)rclPbeGpoMask);
    pbeGpoVal |= (uint32_t)(rclPbeGpoVal & rclPbeGpoMask);
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_GPOCTRL) = pbeGpoVal;
}

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/*
 * ======== LRF_requirePaEsdProtection ========
 */
static inline bool LRF_requirePaEsdProtection(void)
{
    /* To read the VDDS voltage from the BATMON, ensure that BatMonSupportLPF3_init()
     * has been called beforehand. This is guaranteed by the execution of
     * RCL_Hal_temperature_init() during the RCL initialization sequence.
     */
    const uint16_t vddsRead = RCL_Hal_getVddsVoltage();
    return (vddsRead >= LRF_CC27XX_PA_ESD_PROTECTION_VDDS_THRESHOLD_MV);
}

/*
 * ======== LRF_updatePaEsdProtection ========
 */
void LRF_updatePaEsdProtection(void)
{
    /* PA ESD protection is only applicable when the 20dBm PA mode is enabled */
    uint16_t txPowerRawValue = HWREGH_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE5);
    if (LRF_CC27XX_RETRIEVE_PA_MODE_FROM_RAW_VALUE(txPowerRawValue) != LRF_CC27XX_HIGH_PA_MODE)
    {
        return;
    }

    bool enabled = LRF_requirePaEsdProtection();
    if (enabled)
    {
        /* The 14th bit (bit position 14) of the LRFDRFE_O_SPARE5 register is used as the shadow bit
         * for the LRFDRFE:PA0:PA20DBMESDCTL field. This bit is set to 1 to enable the PA ESD protection.
         */
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE5) = txPowerRawValue | LRF_CC27XX_RFE_SPARE5_PA_20DBM_ESD_CTRL_SET;
    }
    else
    {
        /* Disable the PA ESD protection by clearing the corresponding bit. */
        HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE5) = txPowerRawValue & ~LRF_CC27XX_RFE_SPARE5_PA_20DBM_ESD_CTRL_SET;
    }
}
#endif
