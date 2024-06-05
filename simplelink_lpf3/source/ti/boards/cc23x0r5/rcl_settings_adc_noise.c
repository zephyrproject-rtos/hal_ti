// SETTINGS FOR PHY BASED ON RADIO CONTROL LAYER (SOURCE FILE)
//
//
// CODE EXPORT INFORMATION
// This file is generated
//
// Tool name           SmartRF Studio 8
// Tool version        0.6.0.327 INTERNAL
// Created             2024-05-28 13:53:16.066
// Computer            swtools
// User                -
//
//
// WORKSPACE INFORMATION
//
// Workspace file      srf_cli.workspace
// Device              CC2340R5
//     Package         QFN40 5x5 RKP
//     Revision(s)     B (2.0)
// SDK                 SimpleLink LPF3 SDK 8.11.00.09
// Board               LP-EM-CC2340R5
// PHY                 ADC Noise
// PHY abbreviation    adc_noise
//
//
// VALIDATION WARNINGS
//
// No warnings

#include "rcl_settings_adc_noise.h"
#include DeviceFamily_constructPath(rf_patches/lrf_rfe_binary_ble5.h)


// Configuration: Common
static const uint32_t LRF_commonRegConfig[] =
{
    0x0000002C,                          // Segment length = 44
    0x0000A002,                          //     Data structure 32-bit region (start byte position = 0, count = 3)
    (uint32_t) &LRF_swConfigAdcNoise,    //         LRF_swParam : swConfig
    0x00000000,                          //         LRF_swParam : txPowerTable
    (uint32_t) &(fcfg->appTrims),        //         LRF_swParam : trimDef
    0x00003003,                          //     HW sparse region (address/value pairs, count = 4)
    0x30800000,                          //         LRFDRFE.MAGNTHRCFG
    0x30880000,                          //         LRFDRFE.RSSIOFFSET
    0x31201820,                          //         LRFDRFE.MISC0
    0x31300C07,                          //         LRFDRFE.PHEDISC
    0x30A01002,                          //     HW 16-bit region (start address = 0x30A0, count = 3)
    0x1F40A246,                          //         LRFDRFE.SPARE3                      LRFDRFE.SPARE2
    0x00000000,                          //         -                                   LRFDRFE.SPARE4
    0x30B01002,                          //     HW 16-bit region (start address = 0x30B0, count = 3)
    0x0006000A,                          //         LRFDRFE.IFAMPRFLDO                  LRFDRFE.LNA
    0x00000000,                          //         -                                   LRFDRFE.PA0
    0x30C40005,                          //     HW zero region (start address = 0x30C4, count = 6)
    0x30E4100C,                          //     HW 16-bit region (start address = 0x30E4, count = 13)
    0x00000200,                          //         LRFDRFE.DCO                         LRFDRFE.ATSTREFH
    0x00000008,                          //         LRFDRFE.DIVLDO                      LRFDRFE.DIV
    0x00000000,                          //         LRFDRFE.DCOLDO0                     LRFDRFE.TDCLDO
    0x07060000,                          //         LRFDRFE.PRE0                        LRFDRFE.DCOLDO1
    0x06050000,                          //         LRFDRFE.PRE2                        LRFDRFE.PRE1
    0x40080603,                          //         LRFDRFE.CAL0                        LRFDRFE.PRE3
    0x00007F00,                          //         -                                   LRFDRFE.CAL1
    0x31381002,                          //     HW 16-bit region (start address = 0x3138, count = 3)
    0x047FDF7F,                          //         LRFDRFE.PLLMON1                     LRFDRFE.PLLMON0
    0x00001804,                          //         -                                   LRFDRFE.MOD0
    0x68046005,                          //     RAM 32-bit region (start address = 0x6804, count = 6)
    0x03000012,                          //         RFE_COMMON_RAM.TDCCAL0              RFE_COMMON_RAM.SYNTHCTL
    0x00100000,                          //         RFE_COMMON_RAM.TDCCAL2              RFE_COMMON_RAM.TDCCAL1
    0x569B0400,                          //         RFE_COMMON_RAM.K1LSB                RFE_COMMON_RAM.TDCPLL
    0x012D010A,                          //         RFE_COMMON_RAM.K2BL                 RFE_COMMON_RAM.K1MSB
    0x132C0034,                          //         RFE_COMMON_RAM.K3BL                 RFE_COMMON_RAM.K2AL
    0x916F07AB,                          //         RFE_COMMON_RAM.K5                   RFE_COMMON_RAM.K3AL
    0x68206005,                          //     RAM 32-bit region (start address = 0x6820, count = 6)
    0x00000000,                          //         RFE_COMMON_RAM.RTRIMMIN             RFE_COMMON_RAM.RTRIMOFF
    0x48080008,                          //         RFE_COMMON_RAM.DIVF                 RFE_COMMON_RAM.DIVI
    0x00000000,                          //         RFE_COMMON_RAM.DIVLDOF              RFE_COMMON_RAM.DIVLDOI
    0x00470014,                          //         RFE_COMMON_RAM.LDOSETTLE            RFE_COMMON_RAM.DIVLDOIOFF
    0x0005002E,                          //         RFE_COMMON_RAM.DCOSETTLE            RFE_COMMON_RAM.CHRGSETTLE
    0x0000FE00,                          //         RFE_COMMON_RAM.IFAMPRFLDODEFAULT    RFE_COMMON_RAM.IFAMPRFLDOTX
    0x683E5003,                          //     RAM 16-bit region (start address = 0x683E, count = 4)
    0x00220050,                          //         RFE_COMMON_RAM.SPARE0SHADOW         RFE_COMMON_RAM.PHYRSSIOFFSET
    0x00000045                           //         RFE_COMMON_RAM.AGCINFO              RFE_COMMON_RAM.SPARE1SHADOW
};


// LRF register configuration list
static const LRF_RegConfigList LRF_regConfigList = {
    .numEntries = 1,
    .entries = {
        (LRF_ConfigWord*) LRF_commonRegConfig 
    }
};

// LRF_SwConfig data structure
const LRF_SwConfig LRF_swConfigAdcNoise = {
    .rxIntFrequency        = 0,
    .rxFrequencyOffset     = 0,
    .txFrequencyOffset     = 0,
    .modFrequencyDeviation = 0x00000000,
    .txShape               = (LRF_TxShape*) 0,
    .bwIndex               = 0x01,
    .bwIndexDither         = 0x01 
};

// LRF_Config data structure
const LRF_Config LRF_configAdcNoise = {
    .pbeImage              = (LRF_TOPsmImage*) 0,
    .mceImage              = (LRF_TOPsmImage*) 0,
    .rfeImage              = (const LRF_TOPsmImage*) LRF_RFE_binary_ble5,
    .regConfigList         = &LRF_regConfigList 
};
