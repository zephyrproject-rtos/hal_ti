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

#ifndef __lrf_h__
#define __lrf_h__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ti/drivers/rcl/hal/hal.h>

#if defined(DeviceFamily_CC23X0R5) || defined(DeviceFamily_CC23X0R2) || defined(DeviceFamily_CC27XX) || defined(DeviceFamily_CC23X0R22) || defined(DeviceFamily_CC2340R53)
#  include <ti/devices/DeviceFamily.h>
#  include DeviceFamily_constructPath(inc/hw_types.h)
#  include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#  include <ti/drivers/rcl/LRFCC23X0.h>
#endif

#ifdef DeviceFamily_CC1308
#  define BUFFER_SPLIT_SUPPORT
#  include "LRFCC1308.h"
#endif

/**
 *  Special value given as a TX power to indicate that the lowest available
 *  TX power is requested
 */
#define LRF_TxPower_Use_Min       ((LRF_TxPowerTable_Index){.rawValue = -128})
/**
 *  Special value given as a TX power to indicate that the highest available
 *  TX power is requested
 */
#define LRF_TxPower_Use_Max       ((LRF_TxPowerTable_Index){.rawValue = 125})
/**
 *  Special value given as a TX power to indicate that a given raw TX power
 *  register setting should be used.
 */
#define LRF_TxPower_Use_Raw       ((LRF_TxPowerTable_Index){.rawValue = 126})
/**
 *  Special value given as a TX power to indicate that a TX power should not
 *  be programmed; instead, use the register value written through settings or
 *  register write.
 */
#define LRF_TxPower_None          ((LRF_TxPowerTable_Index){.rawValue = 127})

/**
 *  Buffer available limit when no limit exists
 *
 */
#define LRF_SETTINGS_BUFFER_UNLIMITED 0x3FFF

/**
 * RSSI value indicating an invalid RSSI
 *
 */
#define LRF_RSSI_INVALID (127)


typedef enum LRF_RadioState_e {
    RadioState_Down = 0,
    RadioState_ImagesLoaded,  /* TOPsm images loaded, persists     */
    RadioState_Configured,    /* REGBANK values loaded, no persist */
} LRF_RadioState;

/**
 *  @brief Setup operation result
 */
typedef enum LRF_SetupResult_e {
    SetupResult_Ok,                    /*!< Setup was successful */
    SetupResult_Ok_Partial,            /*!< Setup was successful so far, need rest of buffer */
    SetupResult_ErrorImageLen,         /*!< An image was too long */
    SetupResult_ErrorConfigLen,        /*!< A register configuration table was too long */
    SetupResult_ErrorElemLen,          /*!< A register configuration element exceeded the table length */
    SetupResult_ErrorElemType,         /*!< A register configuration element had invalid type */
    SetupResult_ErrorElemAddrAlign,    /*!< A register configuration element had unsupported address alignment */
    SetupResult_ErrorParRange,         /*!< A register parameter element was outside the allowed range */
    SetupResult_ErrorSwConfig,         /*!< The swConfig field was NULL */
} LRF_SetupResult;

struct LRF_TOPsmImage_s {
    uint32_t  imageLen;
    uint32_t  image[];
};

typedef union {
    struct {
        uint32_t lengthMinus1 : 12;
        uint32_t type         : 4;
        uint32_t startAddress : 16;
    } region;
    uint32_t value32;
    uint16_t value16[2];
    struct {
        uint16_t value16;
        uint16_t address;
    } sparse;
    struct {
        uint16_t value16;
        uint16_t mask16;
    } masked;
    struct {
        uint32_t length              : 14;
        uint32_t invertedFeatureMask : 1;
        uint32_t compoundSegment     : 1;
        uint32_t featureMask         : 16;
    } segment;
} LRF_ConfigWord;

struct LRF_RegConfigList_s {
    uint32_t numEntries;
    LRF_ConfigWord *entries[];
};

typedef enum {
    HW_Region_Clear             = 0,
    HW_Write_16bit              = 1,
    HW_Write_32bit              = 2,
    HW_Write_16bit_sparse       = 3,
    SW_Region_Clear             = 4,
    SW_Write_16bit              = 5,
    SW_Write_32bit              = 6,
    SW_Write_16bit_sparse       = 7,
    Par_Region_Clear            = 8,
    Par_Reference_32bit         = 9,
    Par_Write_32bit             = 10,
    HW_Write_16bit_masked       = 11,
    LRF_RegionOperation_Skip    = 254,
    LRF_RegionOperation_Invalid = 255,
} LRF_RegionOperation;

typedef enum {
    LRF_ApplySettings_NoBase      = 0,
    LRF_ApplySettings_IncludeBase = 1,
} LRF_ApplySettingsBase;

typedef struct {
    /* Settings */
    uint16_t                phyFeatures;
    LRF_ApplySettingsBase   includeBase;

#ifdef BUFFER_SPLIT_SUPPORT
    /* State variables */
    bool                    started;
    int32_t                 totalLength;
    uint32_t                segmentLength;

    /* State variables for region */
    uintptr_t               address;
    LRF_RegionOperation     operation;
    uint32_t                regionLength;
    uint32_t                regionStart;
#endif
} LRF_ApplySettingsState;

#define LRF_PhyFeatures_Default 0

/* The definition below ensures an invalid value runtime and a warning compiletime */
#define __ERROR_Address_is_in_an_invalid_range_for_LRF_setup 0x00040000

#define _ADDRESS_REGION_BIT(_address)                                   \
    ((((((uintptr_t)(_address)) >= (LRF_BASE_ADDR)) &&                  \
       ((uintptr_t)(_address)) < ((LRF_BASE_ADDR) + 0x10000)) ? 0 :     \
      ((((uintptr_t)(_address)) >= (PBE_RAM_BASE_ADDR)) &&              \
        (((uintptr_t)(_address)) < ((PBE_RAM_BASE_ADDR) + 0x10000)) ?   \
       1 :                                                              \
       (((((uintptr_t)(_address)) >= 0) &&                              \
        (((uintptr_t)(_address)) < 0x10000)) ?                          \
       2 :                                                              \
       (__ERROR_Address_is_in_an_invalid_range_for_LRF_setup)))) << 14)

#define LRF_SETTINGS_CLEAR(_startAddress, _numWords)                    \
    ((((_numWords) - 1) & 0x0FFF) |                                     \
     _ADDRESS_REGION_BIT(_startAddress) |                               \
     ((((uintptr_t)(_startAddress)) & 0xFFFF) << 16))

#define LRF_SETTINGS_16BIT_BLOCK(_startAddress, _numWords)              \
    ((((_numWords) - 1) & 0x0FFF) |                                     \
    _ADDRESS_REGION_BIT(_startAddress) | (1 << 12) |                    \
     ((((uintptr_t)(_startAddress)) & 0xFFFF) << 16))

#define LRF_SETTINGS_16BIT_DUAL_ENTRY(_value0, _value1)                  \
    (((_value0) & 0xFFFF) | (((_value1) & 0xFFFF) << 16))

#define LRF_SETTINGS_32BIT_BLOCK(_startAddress, _numWords)              \
    ((((_numWords) - 1) & 0x0FFF) |                                     \
     _ADDRESS_REGION_BIT(_startAddress) | (2 << 12) |                   \
     ((((uintptr_t)(_startAddress)) & 0xFFFF) << 16))

#define LRF_SETTINGS_16BIT_SPARSE_BLOCK(_startAddress, _numWords)       \
    ((((_numWords) - 1) & 0x0FFF) |                                     \
     _ADDRESS_REGION_BIT(_startAddress) | (3 << 12))                    \

#define LRF_SETTINGS_16BIT_SPARSE_ENTRY(_address, _value)               \
    (((((uintptr_t)(_address)) & 0xFFFF) << 16) | ((_value) & 0xFFFF))

#define LRF_SETTINGS_16BIT_MASKED_BLOCK(_startAddress, _numWords)       \
    ((((_numWords) - 1) & 0x0FFF) | (11 << 12) |                        \
     ((((uintptr_t)(_startAddress)) & 0xFFFF) << 16))

#define LRF_SETTINGS_16BIT_MASKED_ENTRY(_mask, _value)                  \
    ((((_mask) & 0xFFFF) << 16) | ((_value) & 0xFFFF))

LRF_SetupResult LRF_setupRadio(const LRF_Config *lrfConfig, uint16_t phyFeatures, LRF_RadioState lrfState);

LRF_SetupResult LRF_loadImage(const LRF_TOPsmImage *image, uint32_t destinationAddress);

static inline void LRF_resetSettingsState(LRF_ApplySettingsState *state)
{
#ifdef BUFFER_SPLIT_SUPPORT
    state->totalLength = 0;
#else
    (void)state;
#endif
}

void LRF_initSettingsState(LRF_ApplySettingsState *state,
                           LRF_ApplySettingsBase   includeBase,
                           uint16_t                phyFeatures);
LRF_SetupResult LRF_applySettings(LRF_ConfigWord         *config,
                                  LRF_ApplySettingsState *state,
                                  int32_t                 bufferAvailWords);

void LRF_enable(void);
void LRF_disable(void);
void LRF_powerDown(void);
void LRF_sendHardStop(void);
void LRF_sendGracefulStop(void);
void LRF_hardStop(void);

void LRF_waitForTopsmReady(void);
uint32_t LRF_prepareRxFifo(void);
uint32_t LRF_prepareTxFifo(void);
uint32_t LRF_peekRxFifo(int32_t offset);
uint32_t LRF_peekTxFifo(int32_t offset);
uint8_t *LRF_getTxFifoWrAddr(int32_t offset);
void LRF_skipTxFifoWords(uint32_t wordLength);
void LRF_discardRxFifoWords(uint32_t wordLength);
void LRF_readRxFifoWords(uint32_t *data32, uint32_t wordLength);
void LRF_writeTxFifoWords(const uint32_t *data32, uint32_t wordLength);
void LRF_setRxFifoEffSz(uint32_t maxSz);
void LRF_programFrequency(uint32_t frequency, bool tx);
uint32_t LRF_enableSynthRefsys(void);
void LRF_disableSynthRefsys(void);
void LRF_setClockEnable(uint16_t mask, uint8_t entryNumber);
void LRF_clearClockEnable(uint16_t mask, uint8_t entryNumber);
int8_t LRF_readRssi(void);
void LRF_setRawTxPower(uint32_t value, uint32_t temperatureCoefficient);
LRF_TxPowerTable_Entry LRF_getRawTxPower(void);
bool LRF_imagesNeedUpdate(const LRF_Config *lrfConfig);

/**
 * @brief Search for settings corresponding to the highest tx power lower than
 * specified value in the tx power table
 *
 *  @param  table pointer to the tx power table to be searched
 *  @param  powerLevel maximum allowed power level
 *
 *  @return Settings corresponding to a power level equal to or lower than requested
 *  or LRF_TxPowerTable_INVALID_VALUE if no valid setting was found.
 *
 */
LRF_TxPowerTable_Entry LRF_TxPowerTable_findValue(const LRF_TxPowerTable *table, LRF_TxPowerTable_Index powerLevel);

void LRF_rclEnableRadioClocks(void);
void LRF_rclDisableRadioClocks(void);

static inline void LRF_enableHwInterrupt(uint32_t mask)
{
    hal_enable_command_radio_interrupt(mask);
}

static inline void LRF_disableHwInterrupt(uint32_t mask)
{
    hal_disable_command_radio_interrupt(mask);
}

static inline void LRF_clearHwInterrupt(uint32_t mask)
{
    hal_clear_command_radio_interrupt(mask);
}

extern uint32_t swParamList[];
extern const size_t swParamListSz;

#endif
