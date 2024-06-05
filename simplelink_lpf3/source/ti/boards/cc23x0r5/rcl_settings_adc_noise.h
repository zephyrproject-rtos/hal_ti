// SETTINGS FOR PHY BASED ON RADIO CONTROL LAYER (HEADER FILE)
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

#ifndef RCLSETTINGSADCNOISE_H
#define RCLSETTINGSADCNOISE_H

#include <ti/devices/DeviceFamily.h>
#include <ti/drivers/rcl/LRF.h>
#include DeviceFamily_constructPath(inc/hw_fcfg.h)


// LRF data structures
extern const LRF_SwConfig LRF_swConfigAdcNoise;
extern const LRF_Config   LRF_configAdcNoise;


// COMMON register field values

// Address    Module            Register             Bit(s)     Field           Value
// -----------------------------------------------------------------------------------
// 0x3080     LRFDRFE           MAGNTHRCFG           [1]        SEL             0x0
// 0x3088     LRFDRFE           RSSIOFFSET           [7:0]      VAL             <TRIM>
// 0x30A0     LRFDRFE           SPARE2               [15:0]     VAL             0xA246
// 0x30A4     LRFDRFE           SPARE3               [15:0]     VAL             0x1F40
// 0x30A8     LRFDRFE           SPARE4               [15:0]     VAL             0x0000
// 0x30B0     LRFDRFE           LNA                  [7:4]      TRIM            <TRIM>
// 0x30B0     LRFDRFE           LNA                  [3]        BIAS            0x1
// 0x30B0     LRFDRFE           LNA                  [2:1]      IB              0x1
// 0x30B4     LRFDRFE           IFAMPRFLDO           [15:9]     TRIM            <TRIM>
// 0x30B4     LRFDRFE           IFAMPRFLDO           [7:4]      AAFCAP          <TRIM>
// 0x30B4     LRFDRFE           IFAMPRFLDO           [3:1]      IFAMPIB         0x3
// 0x30B8     LRFDRFE           PA0                  [4:0]      TRIM            <TRIM>
// 0x30C4     LRFDRFE           IFADC0               [14:12]    DITHERTRIM      <TRIM>
// 0x30C4     LRFDRFE           IFADC0               [11:10]    DITHEREN        <TRIM>
// 0x30C4     LRFDRFE           IFADC0               [7:4]      INT2ADJ         <TRIM>
// 0x30C4     LRFDRFE           IFADC0               [3:2]      AAFCAP          <TRIM>
// 0x30C8     LRFDRFE           IFADC1               [15]       NRZ             <TRIM>
// 0x30C8     LRFDRFE           IFADC1               [14:9]     TRIM            <TRIM>
// 0x30CC     LRFDRFE           IFADCLF              [15:12]    FF3             <TRIM>
// 0x30CC     LRFDRFE           IFADCLF              [11:8]     FF2             <TRIM>
// 0x30CC     LRFDRFE           IFADCLF              [7:4]      FF1             <TRIM>
// 0x30CC     LRFDRFE           IFADCLF              [3:0]      INT3            <TRIM>
// 0x30D0     LRFDRFE           IFADCQUANT           [2:0]      QUANTTHR        <TRIM>
// 0x30D4     LRFDRFE           IFADCALDO            [13:8]     TRIMOUT         <TRIM>
// 0x30D8     LRFDRFE           IFADCDLDO            [13:8]     TRIMOUT         <TRIM>
// 0x30E4     LRFDRFE           ATSTREFH             [14:10]    IREFTRIM        <TRIM>
// 0x30E4     LRFDRFE           ATSTREFH             [9]        BIAS            0x1
// 0x30E8     LRFDRFE           DCO                  [6:3]      TAILRESTRIM     <TRIM>
// 0x30E8     LRFDRFE           DCO                  [0]        CRSCAPCM        0x0
// 0x30EC     LRFDRFE           DIV                  [15]       PDET            0x0
// 0x30EC     LRFDRFE           DIV                  [14:12]    NMIREFTRIM      0x0
// 0x30EC     LRFDRFE           DIV                  [11:9]     PMIREFTRIM      0x0
// 0x30EC     LRFDRFE           DIV                  [8]        TXBBOOST        0x0
// 0x30EC     LRFDRFE           DIV                  [7]        S1GFRC          0x0
// 0x30EC     LRFDRFE           DIV                  [6:5]      BUFGAIN         0x0
// 0x30EC     LRFDRFE           DIV                  [4]        BIAS            0x0
// 0x30EC     LRFDRFE           DIV                  [3]        OUT             0x1
// 0x30EC     LRFDRFE           DIV                  [2:0]      RATIO           0x0
// 0x30F0     LRFDRFE           DIVLDO               [15]       SPARE15         0x0
// 0x30F0     LRFDRFE           DIVLDO               [14:8]     VOUTTRIM        <TRIM>
// 0x30F0     LRFDRFE           DIVLDO               [7]        ITST            0x0
// 0x30F0     LRFDRFE           DIVLDO               [6:4]      TMUX            0x0
// 0x30F0     LRFDRFE           DIVLDO               [3]        SPARE3          0x0
// 0x30F0     LRFDRFE           DIVLDO               [2]        MODE            0x0
// 0x30F0     LRFDRFE           DIVLDO               [1]        BYPASS          0x0
// 0x30F0     LRFDRFE           DIVLDO               [0]        CTL             0x0
// 0x30F4     LRFDRFE           TDCLDO               [14:8]     VOUTTRIM        <TRIM>
// 0x30F8     LRFDRFE           DCOLDO0              [13:8]     SECONDTRIM      <TRIM>
// 0x30F8     LRFDRFE           DCOLDO0              [7:4]      FIRSTTRIM       <TRIM>
// 0x30FC     LRFDRFE           DCOLDO1              [10]       REFSRC          0x0
// 0x30FC     LRFDRFE           DCOLDO1              [9:8]      DIVATST         0x0
// 0x3100     LRFDRFE           PRE0                 [13:8]     PLLDIV1         0x07
// 0x3100     LRFDRFE           PRE0                 [5:0]      PLLDIV0         0x06
// 0x3104     LRFDRFE           PRE1                 [5:0]      HSDDC           0x00
// 0x3108     LRFDRFE           PRE2                 [15:12]    MIDCALDIVLSB    0x0
// 0x3108     LRFDRFE           PRE2                 [11:6]     CRSCALDIV       0x18
// 0x3108     LRFDRFE           PRE2                 [5:0]      FSMDIV          0x05
// 0x310C     LRFDRFE           PRE3                 [15:5]     FINECALDIV      0x030
// 0x310C     LRFDRFE           PRE3                 [4:0]      MIDCALDIVMSB    0x03
// 0x3110     LRFDRFE           CAL0                 [14:8]     FCSTART         0x40
// 0x3110     LRFDRFE           CAL0                 [3:2]      TDCAVG          0x2
// 0x3114     LRFDRFE           CAL1                 [14:8]     FCTOP           0x7F
// 0x3114     LRFDRFE           CAL1                 [6:0]      FCBOT           0x00
// 0x3120     LRFDRFE           MISC0                [13]       PHCPT           0x0
// 0x3120     LRFDRFE           MISC0                [12]       TDCCALCORR      0x1
// 0x3120     LRFDRFE           MISC0                [11]       TDCMSBCORR      0x1
// 0x3120     LRFDRFE           MISC0                [5:4]      DLYCANCRS       0x2
// 0x3130     LRFDRFE           PHEDISC              [13:10]    CNT             0x3
// 0x3130     LRFDRFE           PHEDISC              [9:0]      THR             0x007
// 0x3138     LRFDRFE           PLLMON0              [15:14]    PHELOLCNT       0x3
// 0x3138     LRFDRFE           PLLMON0              [13:8]     PHELOLTHR       0x1F
// 0x3138     LRFDRFE           PLLMON0              [6:0]      FCTHR           0x7F
// 0x313C     LRFDRFE           PLLMON1              [12:8]     PHELOCKCNT      0x04
// 0x313C     LRFDRFE           PLLMON1              [7:0]      PHELOCKTHR      0x7F
// 0x3140     LRFDRFE           MOD0                 [12:11]    SCHEME          0x3
// 0x3140     LRFDRFE           MOD0                 [10:8]     SYMSHP          0x0
// 0x3140     LRFDRFE           MOD0                 [3:2]      INTPFACT        0x1
// 0x6804     RFE_COMMON_RAM    SYNTHCTL             [7]        CHRGFILT        0x0
// 0x6804     RFE_COMMON_RAM    SYNTHCTL             [6]        VREFBP          0x0
// 0x6804     RFE_COMMON_RAM    SYNTHCTL             [5]        TXWAITMOD       0x0
// 0x6804     RFE_COMMON_RAM    SYNTHCTL             [4]        PHEDISC         0x1
// 0x6804     RFE_COMMON_RAM    SYNTHCTL             [3]        RTRIMTST        0x0
// 0x6804     RFE_COMMON_RAM    SYNTHCTL             [2]        IIR             0x0
// 0x6804     RFE_COMMON_RAM    SYNTHCTL             [1]        REFDTHR         0x1
// 0x6804     RFE_COMMON_RAM    SYNTHCTL             [0]        FCDEM           0x0
// 0x6806     RFE_COMMON_RAM    TDCCAL0              [10:8]     STOP            0x3
// 0x6808     RFE_COMMON_RAM    TDCCAL1              [7:0]      SUB             0x00
// 0x680A     RFE_COMMON_RAM    TDCCAL2              [5:0]      AVG             0x10
// 0x680C     RFE_COMMON_RAM    TDCPLL               [10:8]     STOP            0x4
// 0x680E     RFE_COMMON_RAM    K1LSB                [15:0]     VAL             0x569B
// 0x6810     RFE_COMMON_RAM    K1MSB                [15:0]     VAL             0x010A
// 0x6812     RFE_COMMON_RAM    K2BL                 [15]       HPM             0x0
// 0x6812     RFE_COMMON_RAM    K2BL                 [14:0]     VAL             0x012D
// 0x6814     RFE_COMMON_RAM    K2AL                 [15]       HPM             0x0
// 0x6814     RFE_COMMON_RAM    K2AL                 [14:0]     VAL             0x0034
// 0x6816     RFE_COMMON_RAM    K3BL                 [15:0]     VAL             0x132C
// 0x6818     RFE_COMMON_RAM    K3AL                 [15:0]     VAL             0x07AB
// 0x681A     RFE_COMMON_RAM    K5                   [15:0]     VAL             0x916F
// 0x6820     RFE_COMMON_RAM    RTRIMOFF             [3:0]      VAL             0x0
// 0x6822     RFE_COMMON_RAM    RTRIMMIN             [3:0]      VAL             0x0
// 0x6824     RFE_COMMON_RAM    DIVI                 [15]       PDET            0x0
// 0x6824     RFE_COMMON_RAM    DIVI                 [14:12]    NMIREFTRIM      0x0
// 0x6824     RFE_COMMON_RAM    DIVI                 [11:9]     PMIREFTRIM      0x0
// 0x6824     RFE_COMMON_RAM    DIVI                 [8]        TXBOOST         0x0
// 0x6824     RFE_COMMON_RAM    DIVI                 [7]        S1GFRC          0x0
// 0x6824     RFE_COMMON_RAM    DIVI                 [6:5]      BUFGAIN         0x0
// 0x6824     RFE_COMMON_RAM    DIVI                 [4]        BIAS            0x0
// 0x6824     RFE_COMMON_RAM    DIVI                 [3]        OUT             0x1
// 0x6824     RFE_COMMON_RAM    DIVI                 [2:0]      RATIO           0x0
// 0x6826     RFE_COMMON_RAM    DIVF                 [15]       PDET            0x0
// 0x6826     RFE_COMMON_RAM    DIVF                 [14:12]    NMIREFTRIM      0x4
// 0x6826     RFE_COMMON_RAM    DIVF                 [11:9]     PMIREFTRIM      0x4
// 0x6826     RFE_COMMON_RAM    DIVF                 [8]        TXBOOST         0x0
// 0x6826     RFE_COMMON_RAM    DIVF                 [7]        S1GFRC          0x0
// 0x6826     RFE_COMMON_RAM    DIVF                 [6:5]      BUFGAIN         0x0
// 0x6826     RFE_COMMON_RAM    DIVF                 [4]        BIAS            0x0
// 0x6826     RFE_COMMON_RAM    DIVF                 [3]        OUT             0x1
// 0x6826     RFE_COMMON_RAM    DIVF                 [2:0]      RATIO           0x0
// 0x6828     RFE_COMMON_RAM    DIVLDOI              [15]       ITEST           0x0
// 0x6828     RFE_COMMON_RAM    DIVLDOI              [14:8]     VOUTTRIM        0x00
// 0x6828     RFE_COMMON_RAM    DIVLDOI              [7]        ITST            0x0
// 0x6828     RFE_COMMON_RAM    DIVLDOI              [6:4]      TMUX            0x0
// 0x6828     RFE_COMMON_RAM    DIVLDOI              [2]        MODE            0x0
// 0x6828     RFE_COMMON_RAM    DIVLDOI              [1]        BYPASS          0x0
// 0x6828     RFE_COMMON_RAM    DIVLDOI              [0]        CTL             0x0
// 0x682A     RFE_COMMON_RAM    DIVLDOF              [15]       ITEST           0x0
// 0x682A     RFE_COMMON_RAM    DIVLDOF              [14:8]     VOUTTRIM        0x00
// 0x682A     RFE_COMMON_RAM    DIVLDOF              [7]        ITST            0x0
// 0x682A     RFE_COMMON_RAM    DIVLDOF              [6:4]      TMUX            0x0
// 0x682A     RFE_COMMON_RAM    DIVLDOF              [2]        MODE            0x0
// 0x682A     RFE_COMMON_RAM    DIVLDOF              [1]        BYPASS          0x0
// 0x682A     RFE_COMMON_RAM    DIVLDOF              [0]        CTL             0x0
// 0x682C     RFE_COMMON_RAM    DIVLDOIOFF           [6:0]      VAL             0x14
// 0x682E     RFE_COMMON_RAM    LDOSETTLE            [9:0]      VAL             0x047
// 0x6830     RFE_COMMON_RAM    CHRGSETTLE           [9:0]      VAL             0x02E
// 0x6832     RFE_COMMON_RAM    DCOSETTLE            [9:0]      VAL             0x005
// 0x6834     RFE_COMMON_RAM    IFAMPRFLDOTX         [15:9]     TRIM            0x7F
// 0x6836     RFE_COMMON_RAM    IFAMPRFLDODEFAULT    [15:9]     TRIM            0x00
// 0x683E     RFE_COMMON_RAM    PHYRSSIOFFSET        [7:0]      VAL             0x50
// 0x6840     RFE_COMMON_RAM    SPARE0SHADOW         [15:0]     VAL             0x0022
// 0x6842     RFE_COMMON_RAM    SPARE1SHADOW         [15:0]     VAL             0x0045
// 0x6844     RFE_COMMON_RAM    AGCINFO              [0]        MODE            0x0


#endif
