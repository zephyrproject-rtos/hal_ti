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

/**
 * @defgroup DL_MCPWM_AM13E230X  Driverlib MCPWM API
 * @ingroup DL_AM13E230X
 * @{
 */

#ifndef DL_MCPWM_H
#define DL_MCPWM_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "soc.h"
#include "hw_mcpwm.h"
#include "hw_sysctl.h"
#include "dl_common.h"
#include "dl_mcpwm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 * @name DL_MCPWM_TIME_BASE_STATUS
 * @anchor DL_MCPWM_TIME_BASE_STATUS
 * @{
 */
/*!
 * @brief Time base counter is counting up
 */
#define DL_MCPWM_TIME_BASE_STATUS_COUNT_UP   1U
/*!
 * @brief Time base counter is counting down
 */
#define DL_MCPWM_TIME_BASE_STATUS_COUNT_DOWN 0U
/** @}*/

/**
 * @name DL_MCPWM_DB_INPUT
 * @anchor DL_MCPWM_DB_INPUT
 * @{
 */
/*!
 * @brief PWMA signal is used as input to RED/FED
 */
#define DL_MCPWM_DB_INPUT_PWMA   0U
/*!
 * @brief PWMB signal is used as input to RED/FED
 */
#define DL_MCPWM_DB_INPUT_PWMB   1U
/*!
 * @brief RED output signal is used as input to FED
 */
#define DL_MCPWM_DB_INPUT_DB_RED 2U
/** @}*/

/**
 * @name DL_MCPWM_TZ_SIGNAL
 * @anchor DL_MCPWM_TZ_SIGNAL
 * @{
 */
/*!
 * @brief TZ1 Cycle By Cycle
 */
#define DL_MCPWM_TZ_SIGNAL_CBC1  MCPWM_TZSEL_CBC1_MASK
/*!
 * @brief TZ2 Cycle By Cycle
 */
#define DL_MCPWM_TZ_SIGNAL_CBC2  MCPWM_TZSEL_CBC2_MASK
/*!
 * @brief TZ3 Cycle By Cycle
 */
#define DL_MCPWM_TZ_SIGNAL_CBC3  MCPWM_TZSEL_CBC3_MASK
/*!
 * @brief TZ4 Cycle By Cycle
 */
#define DL_MCPWM_TZ_SIGNAL_CBC4  MCPWM_TZSEL_CBC4_MASK
/*!
 * @brief TZ5 Cycle By Cycle
 */
#define DL_MCPWM_TZ_SIGNAL_CBC5  MCPWM_TZSEL_CBC5_MASK
/*!
 * @brief TZ6 Cycle By Cycle
 */
#define DL_MCPWM_TZ_SIGNAL_CBC6  MCPWM_TZSEL_CBC6_MASK
/*!
 * @brief TZ7 Cycle By Cycle
 */
#define DL_MCPWM_TZ_SIGNAL_CBC7  MCPWM_TZSEL_CBC7_MASK
/*!
 * @brief TZ8 Cycle By Cycle
 */
#define DL_MCPWM_TZ_SIGNAL_CBC8  MCPWM_TZSEL_CBC8_MASK
/*!
 * @brief One-shot TZ1
 */
#define DL_MCPWM_TZ_SIGNAL_OSHT1 MCPWM_TZSEL_OST1_MASK
/*!
 * @brief One-shot TZ2
 */
#define DL_MCPWM_TZ_SIGNAL_OSHT2 MCPWM_TZSEL_OST2_MASK
/*!
 * @brief One-shot TZ3
 */
#define DL_MCPWM_TZ_SIGNAL_OSHT3 MCPWM_TZSEL_OST3_MASK
/*!
 * @brief One-shot TZ4
 */
#define DL_MCPWM_TZ_SIGNAL_OSHT4 MCPWM_TZSEL_OST4_MASK
/*!
 * @brief One-shot TZ5
 */
#define DL_MCPWM_TZ_SIGNAL_OSHT5 MCPWM_TZSEL_OST5_MASK
/*!
 * @brief One-shot TZ6
 */
#define DL_MCPWM_TZ_SIGNAL_OSHT6 MCPWM_TZSEL_OST6_MASK
/*!
 * @brief One-shot TZ7
 */
#define DL_MCPWM_TZ_SIGNAL_OSHT7 MCPWM_TZSEL_OST7_MASK
/*!
 * @brief One-shot TZ8
 */
#define DL_MCPWM_TZ_SIGNAL_OSHT8 MCPWM_TZSEL_OST8_MASK
/** @}*/

/**
 * @name DL_MCPWM_TZ_FLAG
 * @anchor DL_MCPWM_TZ_FLAG
 * @{
 */
/*!
 * @brief CBC flag 1
 */
#define DL_MCPWM_TZ_FLAG_CBC_TZ1 MCPWM_TZCBCOSTFLAG_CBC1_MASK
/*!
 * @brief CBC flag 2
 */
#define DL_MCPWM_TZ_FLAG_CBC_TZ2 MCPWM_TZCBCOSTFLAG_CBC2_MASK
/*!
 * @brief CBC flag 3
 */
#define DL_MCPWM_TZ_FLAG_CBC_TZ3 MCPWM_TZCBCOSTFLAG_CBC3_MASK
/*!
 * @brief CBC flag 4
 */
#define DL_MCPWM_TZ_FLAG_CBC_TZ4 MCPWM_TZCBCOSTFLAG_CBC4_MASK
/*!
 * @brief CBC flag 5
 */
#define DL_MCPWM_TZ_FLAG_CBC_TZ5 MCPWM_TZCBCOSTFLAG_CBC5_MASK
/*!
 * @brief CBC flag 6
 */
#define DL_MCPWM_TZ_FLAG_CBC_TZ6 MCPWM_TZCBCOSTFLAG_CBC6_MASK
/*!
 * @brief CBC flag 7
 */
#define DL_MCPWM_TZ_FLAG_CBC_TZ7 MCPWM_TZCBCOSTFLAG_CBC7_MASK
/*!
 * @brief CBC flag 8
 */
#define DL_MCPWM_TZ_FLAG_CBC_TZ8 MCPWM_TZCBCOSTFLAG_CBC8_MASK
/*!
 * @brief OST flag 1
 */
#define DL_MCPWM_TZ_FLAG_OST_TZ1 MCPWM_TZCBCOSTFLAG_OST1_MASK
/*!
 * @brief OST flag 2
 */
#define DL_MCPWM_TZ_FLAG_OST_TZ2 MCPWM_TZCBCOSTFLAG_OST2_MASK
/*!
 * @brief OST flag 3
 */
#define DL_MCPWM_TZ_FLAG_OST_TZ3 MCPWM_TZCBCOSTFLAG_OST3_MASK
/*!
 * @brief OST flag 4
 */
#define DL_MCPWM_TZ_FLAG_OST_TZ4 MCPWM_TZCBCOSTFLAG_OST4_MASK
/*!
 * @brief OST flag 5
 */
#define DL_MCPWM_TZ_FLAG_OST_TZ5 MCPWM_TZCBCOSTFLAG_OST5_MASK
/*!
 * @brief OST flag 6
 */
#define DL_MCPWM_TZ_FLAG_OST_TZ6 MCPWM_TZCBCOSTFLAG_OST6_MASK
/*!
 * @brief OST flag 7
 */
#define DL_MCPWM_TZ_FLAG_OST_TZ7 MCPWM_TZCBCOSTFLAG_OST7_MASK
/*!
 * @brief OST flag 8
 */
#define DL_MCPWM_TZ_FLAG_OST_TZ8 MCPWM_TZCBCOSTFLAG_OST8_MASK
/*!
 * @brief All Trip Zone flags
 */
#define DL_MCPWM_TZ_FLAG_ALL                                                                      \
    (MCPWM_TZCBCOSTFLAG_CBC1_MASK | MCPWM_TZCBCOSTFLAG_CBC2_MASK | MCPWM_TZCBCOSTFLAG_CBC3_MASK | \
     MCPWM_TZCBCOSTFLAG_CBC4_MASK | MCPWM_TZCBCOSTFLAG_CBC5_MASK | MCPWM_TZCBCOSTFLAG_CBC6_MASK | \
     MCPWM_TZCBCOSTFLAG_CBC7_MASK | MCPWM_TZCBCOSTFLAG_CBC8_MASK | MCPWM_TZCBCOSTFLAG_OST1_MASK | \
     MCPWM_TZCBCOSTFLAG_OST2_MASK | MCPWM_TZCBCOSTFLAG_OST3_MASK | MCPWM_TZCBCOSTFLAG_OST4_MASK | \
     MCPWM_TZCBCOSTFLAG_OST5_MASK | MCPWM_TZCBCOSTFLAG_OST6_MASK | MCPWM_TZCBCOSTFLAG_OST7_MASK | \
     MCPWM_TZCBCOSTFLAG_OST8_MASK)
/** @}*/

/**
 * @name DL_MCPWM_INT
 * @anchor DL_MCPWM_INT
 * @{
 */
/*!
 * @brief Interrupt Source is Trip Zone CBC signal.
 */
#define DL_MCPWM_INT_TZ_CBC    MCPWM_INTFLAG_CBC_MASK
/*!
 * @brief Interrupt Source is Trip Zone OST signal.
 */
#define DL_MCPWM_INT_TZ_OST    MCPWM_INTFLAG_OST_MASK
/*!
 * @brief Interrupt Source is ET1 signal.
 */
#define DL_MCPWM_INT_ET_1      MCPWM_INTFLAG_ET1_MASK
/*!
 * @brief Interrupt Source is ET2 signal.
 */
#define DL_MCPWM_INT_ET_2      MCPWM_INTFLAG_ET2_MASK
/*!
 * @brief Interrupt Source is Counter Overflow signal.
 */
#define DL_MCPWM_INT_TBCTR_OVF MCPWM_INTFLAG_CNT_OVF_MASK
/*!
 * @brief All Interrupt Sources.
 */
#define DL_MCPWM_INT_SOURCE_ALL \
    (DL_MCPWM_INT_TZ_CBC | DL_MCPWM_INT_TZ_OST | DL_MCPWM_INT_ET_1 | DL_MCPWM_INT_ET_2 | DL_MCPWM_INT_TBCTR_OVF)
/** @}*/

/*! @brief DL_MCPWM_TIME_BASE_COUNT_MODE */
typedef enum
{
    /*! Up-count mode */
    DL_MCPWM_COUNTER_MODE_UP          = 0,
    /*! Up-down count mode */
    DL_MCPWM_COUNTER_MODE_UP_DOWN     = 1,
    /*! Stop-Freeze counter */
    DL_MCPWM_COUNTER_MODE_STOP_FREEZE = 2
} DL_MCPWM_TIME_BASE_COUNT_MODE;

/*! @brief DL_MCPWM_CLOCK_DIVIDER */
typedef enum
{
    /*! Divide clock by 1 */
    DL_MCPWM_CLOCK_DIVIDER_1     = 0,
    /*! Divide clock by 2 */
    DL_MCPWM_CLOCK_DIVIDER_2     = 1,
    /*! Divide clock by 4 */
    DL_MCPWM_CLOCK_DIVIDER_4     = 2,
    /*! Divide clock by 8 */
    DL_MCPWM_CLOCK_DIVIDER_8     = 3,
    /*! Divide clock by 16 */
    DL_MCPWM_CLOCK_DIVIDER_16    = 4,
    /*! Divide clock by 32 */
    DL_MCPWM_CLOCK_DIVIDER_32    = 5,
    /*! Divide clock by 64 */
    DL_MCPWM_CLOCK_DIVIDER_64    = 6,
    /*! Divide clock by 128 */
    DL_MCPWM_CLOCK_DIVIDER_128   = 7,
    /*! Divide clock by 256 */
    DL_MCPWM_CLOCK_DIVIDER_256   = 8,
    /*! Divide clock by 512 */
    DL_MCPWM_CLOCK_DIVIDER_512   = 9,
    /*! Divide clock by 1024 */
    DL_MCPWM_CLOCK_DIVIDER_1024  = 10,
    /*! Divide clock by 2048 */
    DL_MCPWM_CLOCK_DIVIDER_2048  = 11,
    /*! Divide clock by 4096 */
    DL_MCPWM_CLOCK_DIVIDER_4096  = 12,
    /*! Divide clock by 8192 */
    DL_MCPWM_CLOCK_DIVIDER_8192  = 13,
    /*! Divide clock by 16384 */
    DL_MCPWM_CLOCK_DIVIDER_16384 = 14,
    /*! Divide clock by 32768 */
    DL_MCPWM_CLOCK_DIVIDER_32768 = 15,
} DL_MCPWM_CLOCK_DIVIDER;

/*! @brief DL_MCPWM_EMULATION_MODE */
typedef enum
{
    /*! Stop after TBCTR incrments or decrements */
    DL_MCPWM_EMULATION_STOP_AFTER_NEXT_TB    = 0,
    /*! Stop when counter completes whole cycle */
    DL_MCPWM_EMULATION_STOP_AFTER_FULL_CYCLE = 1,
    /*! Free run */
    DL_MCPWM_EMULATION_FREE_RUN              = 2
} DL_MCPWM_EMULATION_MODE;

/*! @brief DL_MCPWM_PERIOD_LOAD_MODE */
typedef enum
{
    /*! Load when counter equals zero */
    DL_MCPWM_PERIOD_SHADOW_LOAD_ENABLE  = 0,
    /*! Disable load from Shadow register */
    DL_MCPWM_PERIOD_SHADOW_LOAD_DISABLE = 1
} DL_MCPWM_PERIOD_LOAD_MODE;

/*! @brief DL_MCPWM_SYNC_COUNT_MODE */
typedef enum
{
    /*! Count down after sync event */
    DL_MCPWM_COUNT_MODE_DOWN_AFTER_SYNC = 0,
    /*! Count up after sync event */
    DL_MCPWM_COUNT_MODE_UP_AFTER_SYNC   = 1
} DL_MCPWM_SYNC_COUNT_MODE;

/*! @brief DL_MCPWM_SYNC_OUT_PULSE_MODE */
typedef enum
{
    /*! Sync pulse is generated by software */
    DL_MCPWM_SYNC_OUT_PULSE_ON_SOFTWARE          = 0,
    /*! Sync pulse is generated when time base counter equals zero */
    DL_MCPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO      = 1,
    /*! Sync pulse is generated when time base counter equals compare C value */
    DL_MCPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C = 2,
    /*! Sync pulse is generated when time base counter equals compare D value */
    DL_MCPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_D = 3,
    /*! Sync pulse is disabled */
    DL_MCPWM_SYNC_OUT_PULSE_DISABLED             = 4
} DL_MCPWM_SYNC_OUT_PULSE_MODE;

/*! @brief DL_MCPWM_SYNCPERSEL_SOURCE */
typedef enum
{
    /*! Sync Peripheral Signal Pulse is disabled */
    DL_MCPWM_SYNC_PULSE_DISABLED         = 0,
    /*! Sync Peripheral Signal Pulse is generated when time base counter equals Period */
    DL_MCPWM_SYNCPERSEL_SOURCE_PERIOD    = 2,
    /*! Sync Peripheral Signal Pulse is generated when time base counter equals zero */
    DL_MCPWM_SYNCPERSEL_SOURCE_ZERO      = 3,
    /*! Sync Peripheral Signal Pulse is generated when time base counter equals compare C value while counting up */
    DL_MCPWM_SYNCPERSEL_SOURCE_CMPC_UP   = 4,
    /*! Sync Peripheral Signal Pulse is generated when time base counter equals compare C value while counting down
     */
    DL_MCPWM_SYNCPERSEL_SOURCE_CMPC_DOWN = 5,
    /*! Sync Peripheral Signal Pulse is generated when time base counter equals compare D value while counting up */
    DL_MCPWM_SYNCPERSEL_SOURCE_CMPD_UP   = 6,
    /*! Sync Peripheral Signal Pulse is generated when time base counter equals compare D value while counting down
     */
    DL_MCPWM_SYNCPERSEL_SOURCE_CMPD_DOWN = 7
} DL_MCPWM_SYNCPERSEL_SOURCE;

/*! @brief DL_MCPWM_SYNC_IN_PULSE_SOURCE */
typedef enum
{
    /*! Disable Sync-in */
    DL_MCPWM_SYNC_IN_PULSE_SRC_DISABLE       = 0x0,
    /*! Sync-in source is Input XBAR5 signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_INPUTXBAR5    = 0x1,
    /*! Sync-in source is Input XBAR6 signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_INPUTXBAR6    = 0x2,
    /*! Sync-in source is ECAP0 sync-out signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_ECAP0_SYNCOUT = 0x3,
    /*! Sync-in source is ECAP1 sync-out signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_ECAP1_SYNCOUT = 0x4,
    /*! Sync-in source is PWM0 sync-out signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_PWM0_SYNCOUT  = 0x5,
    /*! Sync-in source is PWM1 sync-out signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_PWM1_SYNCOUT  = 0x6,
    /*! Sync-in source is PWM2 sync-out signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_PWM2_SYNCOUT  = 0x7,
    /*! Sync-in source is PWM3 sync-out signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_PWM3_SYNCOUT  = 0x8,
    /*! Sync-in source is PWM4 sync-out signal */
    DL_MCPWM_SYNC_IN_PULSE_SRC_PWM4_SYNCOUT  = 0x9
} DL_MCPWM_SYNC_IN_PULSE_SOURCE;

/*! @brief DL_MCPWM_COUNTER_COMPARE_MODULE */
typedef enum
{
    /*! Counter compare 1A */
    DL_MCPWM_COUNTER_COMPARE_1A = 0,
    /*! Counter compare 1B */
    DL_MCPWM_COUNTER_COMPARE_1B = 1,
    /*! Counter compare 2A */
    DL_MCPWM_COUNTER_COMPARE_2A = 2,
    /*! Counter compare 2B */
    DL_MCPWM_COUNTER_COMPARE_2B = 3,
    /*! Counter compare 3A */
    DL_MCPWM_COUNTER_COMPARE_3A = 4,
    /*! Counter compare 3B */
    DL_MCPWM_COUNTER_COMPARE_3B = 5,
    /*! Counter compare C */
    DL_MCPWM_COUNTER_COMPARE_C  = 6,
    /*! Counter compare D */
    DL_MCPWM_COUNTER_COMPARE_D  = 7
} DL_MCPWM_COUNTER_COMPARE_MODULE;

/*! @brief DL_MCPWM_COUNTER_COMPARE_LOAD_MODE */
typedef enum
{
    /*! Load when counter equals zero */
    DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO        = 0,
    /*! Load when counter equals period */
    DL_MCPWM_COMP_LOAD_ON_CNTR_PERIOD      = 1,
    /*! Load when counter equals zero or period */
    DL_MCPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    /*! Freeze shadow to active load */
    DL_MCPWM_COMP_LOAD_FREEZE              = 3
} DL_MCPWM_COUNTER_COMPARE_LOAD_MODE;

/*! @brief DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE */
typedef enum
{
    /*! DL_MCPWMx1A output */
    DL_MCPWM_AQ_OUTPUT_1A = 0,
    /*! DL_MCPWMx1B output */
    DL_MCPWM_AQ_OUTPUT_1B = 1,
    /*! DL_MCPWMx2A output */
    DL_MCPWM_AQ_OUTPUT_2A = 2,
    /*! DL_MCPWMx2B output */
    DL_MCPWM_AQ_OUTPUT_2B = 3,
    /*! DL_MCPWMx3A output */
    DL_MCPWM_AQ_OUTPUT_3A = 4,
    /*! DL_MCPWMx3B output */
    DL_MCPWM_AQ_OUTPUT_3B = 5
} DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE;

/*! @brief DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE */
typedef enum
{
    /*! No change in the output pins */
    DL_MCPWM_AQ_OUTPUT_NO_CHANGE = 0,
    /*! Set output pins to low */
    DL_MCPWM_AQ_OUTPUT_LOW       = 1,
    /*! Set output pins to High */
    DL_MCPWM_AQ_OUTPUT_HIGH      = 2,
    /*! Toggle the output pins */
    DL_MCPWM_AQ_OUTPUT_TOGGLE    = 3
} DL_MCPWM_ACTION_QUALIFIER_OUTPUT;

/*! @brief DL_MCPWM_ACTION_QUALIFIER_SW_FORCE_OUTPUT */
typedef enum
{
    /*! SW force Action is disabled */
    DL_MCPWM_AQ_SW_FORCE_DISABLED  = 0,
    /*! Set output pins to continuos low */
    DL_MCPWM_AQ_SW_CONTINUOUS_LOW  = 1,
    /*! Set output pins to continuos High */
    DL_MCPWM_AQ_SW_CONTINUOUS_HIGH = 2,
    /*! Set output to low when one shot is triggered */
    DL_MCPWM_AQ_SW_ONE_SHOT_LOW    = 5,
    /*! Set output to high when one shot is triggered */
    DL_MCPWM_AQ_SW_ONE_SHOT_HIGH   = 6,
    /*! Toggle output when one shot is triggered */
    DL_MCPWM_AQ_SW_ONE_SHOT_TOGGLE = 7
} DL_MCPWM_ACTION_QUALIFIER_SW_FORCE_OUTPUT;

/*! @brief DL_MCPWM_ACTION_QUALIFIER_MODULE */
typedef enum
{
    /*! Action Qualifier 1A */
    DL_MCPWM_ACTION_QUALIFIER_1A = 0,
    /*! Action Qualifier 1B */
    DL_MCPWM_ACTION_QUALIFIER_1B = 1,
    /*! Action Qualifier 2A */
    DL_MCPWM_ACTION_QUALIFIER_2A = 2,
    /*! Action Qualifier 2B */
    DL_MCPWM_ACTION_QUALIFIER_2B = 3,
    /*! Action Qualifier 3A */
    DL_MCPWM_ACTION_QUALIFIER_3A = 4,
    /*! Action Qualifier 3B */
    DL_MCPWM_ACTION_QUALIFIER_3B = 5
} DL_MCPWM_ACTION_QUALIFIER_MODULE;

/*! @brief DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE */
typedef enum
{
    /*! Load when counter equals zero */
    DL_MCPWM_AQ_LOAD_ON_CNTR_ZERO        = 0,
    /*! Load when counter equals period */
    DL_MCPWM_AQ_LOAD_ON_CNTR_PERIOD      = 1,
    /*! Load when counter equals zero or period */
    DL_MCPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    /*! Freeze shadow to active load */
    DL_MCPWM_AQ_LOAD_FREEZE              = 3
} DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE;

/*! @brief DL_MCPWM_ACTION_QUALIFIER_OUTPUT_EVENT */
typedef enum
{
    /*! Time base counter equals zero */
    DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO      = MCPWM_PWM1_AQCTLA_ZRO_OFS,
    /*! Time base counter equals period */
    DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD    = MCPWM_PWM1_AQCTLA_PRD_OFS,
    /*! Time base counter up equals CMPA */
    DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA   = MCPWM_PWM1_AQCTLA_CAU_OFS,
    /*! Time base counter down equals CMPA */
    DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA = MCPWM_PWM1_AQCTLA_CAD_OFS,
    /*! Time base counter up equals CMPB */
    DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB   = MCPWM_PWM1_AQCTLA_CBU_OFS,
    /*! Time base counter down equals CMPB */
    DL_MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB = MCPWM_PWM1_AQCTLA_CBD_OFS

} DL_MCPWM_ACTION_QUALIFIER_OUTPUT_EVENT;

/*! @brief DL_MCPWM_ACTION_QUALIFIER_EVENT_ACTION */
typedef enum
{
    /*! Time base counter equals zero and no change in the output pins  */
    DL_MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO      = 0x0,
    /*! Time base counter equals zero and set output pins to low  */
    DL_MCPWM_AQ_OUTPUT_LOW_ZERO            = 0x1,
    /*! Time base counter equals zero and set output pins to high  */
    DL_MCPWM_AQ_OUTPUT_HIGH_ZERO           = 0x2,
    /*! Time base counter equals zero and toggle the output pins  */
    DL_MCPWM_AQ_OUTPUT_TOGGLE_ZERO         = 0x3,
    /*! Time base counter equals period and no change in the output pins  */
    DL_MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD    = 0x0,
    /*! Time base counter equals period and set output pins to low  */
    DL_MCPWM_AQ_OUTPUT_LOW_PERIOD          = 0x4,
    /*! Time base counter equals period and set output pins to high  */
    DL_MCPWM_AQ_OUTPUT_HIGH_PERIOD         = 0x8,
    /*! Time base counter equals period and toggle the output pins  */
    DL_MCPWM_AQ_OUTPUT_TOGGLE_PERIOD       = 0xC,
    /*! Time base counter up equals CMPA and no change in the output pins  */
    DL_MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA   = 0x00,
    /*! Time base counter up equals CMPA and set output pins to low  */
    DL_MCPWM_AQ_OUTPUT_LOW_UP_CMPA         = 0x10,
    /*! Time base counter up equals CMPA and set output pins to high  */
    DL_MCPWM_AQ_OUTPUT_HIGH_UP_CMPA        = 0x20,
    /*! Time base counter up equals CMPA and toggle the output pins  */
    DL_MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPA      = 0x30,
    /*! Time base counter down equals CMPA and no change in the output pins  */
    DL_MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA = 0x00,
    /*! Time base counter down equals CMPA and set output pins to low  */
    DL_MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA       = 0x40,
    /*! Time base counter down equals CMPA and set output pins to high  */
    DL_MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPA      = 0x80,
    /*! Time base counter down equals CMPA and toggle the output pins  */
    DL_MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA    = 0xC0,
    /*! Time base counter up equals CMPB and no change in the output pins  */
    DL_MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB   = 0x000,
    /*! Time base counter up equals CMPB and set output pins to low  */
    DL_MCPWM_AQ_OUTPUT_LOW_UP_CMPB         = 0x100,
    /*! Time base counter up equals CMPB and set output pins to high  */
    DL_MCPWM_AQ_OUTPUT_HIGH_UP_CMPB        = 0x200,
    /*! Time base counter up equals CMPB and toggle the output pins  */
    DL_MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPB      = 0x300,
    /*! Time base counter down equals CMPB and no change in the output pins  */
    DL_MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB = 0x000,
    /*! Time base counter down equals CMPB and set output pins to low  */
    DL_MCPWM_AQ_OUTPUT_LOW_DOWN_CMPB       = 0x400,
    /*! Time base counter down equals CMPB and set output pins to high  */
    DL_MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPB      = 0x800,
    /*! Time base counter down equals CMPB and toggle the output pins  */
    DL_MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB    = 0xC00
} DL_MCPWM_ACTION_QUALIFIER_EVENT_ACTION;

/*! @brief DL_MCPWM_GLOBAL_LOAD_TRIGGER */
typedef enum
{
    /*! Load when counter is equal to zero */
    DL_MCPWM_GL_LOAD_PULSE_CNTR_ZERO        = 0x0,
    /*! Load when counter is equal to period */
    DL_MCPWM_GL_LOAD_PULSE_CNTR_PERIOD      = 0x1,
    /*! Load when counter is equal to zero or period */
    DL_MCPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD = 0x2,
    /*! Load on global force */
    DL_MCPWM_GL_LOAD_PULSE_GLOBAL_FORCE     = 0x3
} DL_MCPWM_GLOBAL_LOAD_TRIGGER;

/*! @brief DL_MCPWM_DEADBAND_OUTPUT */
typedef enum
{
    /*! DB output is DL_MCPWMA */
    DL_MCPWM_DB_OUTPUT_A = 1,
    /*! DB output is DL_MCPWMB */
    DL_MCPWM_DB_OUTPUT_B = 0
} DL_MCPWM_DEADBAND_OUTPUT;

/*! @brief DL_MCPWM_DEADBAND_DELAY_MODE */
typedef enum
{
    /*! DB RED (Rising Edge Delay) mode */
    DL_MCPWM_DB_RED = 1,
    /*! DB FED (Falling Edge Delay) mode */
    DL_MCPWM_DB_FED = 0
} DL_MCPWM_DEADBAND_DELAY_MODE;

/*! @brief DL_MCPWM_DEADBAND_POLARITY */
typedef enum
{
    /*! DB polarity is not inverted */
    DL_MCPWM_DB_POLARITY_ACTIVE_HIGH = 0,
    /*! DB polarity is inverted */
    DL_MCPWM_DB_POLARITY_ACTIVE_LOW  = 1
} DL_MCPWM_DEADBAND_POLARITY;

/*! @brief DL_MCPWM_RISING_EDGE_DELAY_LOAD_MODE */
typedef enum
{
    /*! Load when counter equals zero */
    DL_MCPWM_RED_LOAD_ON_CNTR_ZERO        = 0,
    /*! Load when counter equals period  */
    DL_MCPWM_RED_LOAD_ON_CNTR_PERIOD      = 1,
    /*! Load when counter equals zero or period  */
    DL_MCPWM_RED_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    /*! Freeze shadow to active load  */
    DL_MCPWM_RED_LOAD_FREEZE              = 3
} DL_MCPWM_RISING_EDGE_DELAY_LOAD_MODE;

/*! @brief DL_MCPWM_FALLING_EDGE_DELAY_LOAD_MODE */
typedef enum
{
    /*! Load when counter equals zero  */
    DL_MCPWM_FED_LOAD_ON_CNTR_ZERO        = 0,
    /*! Load when counter equals period  */
    DL_MCPWM_FED_LOAD_ON_CNTR_PERIOD      = 1,
    /*! Load when counter equals zero or period  */
    DL_MCPWM_FED_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    /*! Freeze shadow to active load  */
    DL_MCPWM_FED_LOAD_FREEZE              = 3
} DL_MCPWM_FALLING_EDGE_DELAY_LOAD_MODE;

/*! @brief DL_MCPWM_TRIP_ZONE_EVENT */
typedef enum
{
    /*! TZ1 - TZ8 action on TZ event A */
    DL_MCPWM_TZ_ACTION_EVENT_TZA = 0,
    /*! TZ1 - TZ8 action on TZ event B  */
    DL_MCPWM_TZ_ACTION_EVENT_TZB = 1
} DL_MCPWM_TRIP_ZONE_EVENT;

/*! @brief DL_MCPWM_TRIP_ZONE_ACTION */
typedef enum
{
    /*! High impedance state */
    DL_MCPWM_TZ_ACTION_HIGH_Z  = 0,
    /*! High voltage state */
    DL_MCPWM_TZ_ACTION_HIGH    = 1,
    /*! Low voltage state */
    DL_MCPWM_TZ_ACTION_LOW     = 2,
    /*! Disable action */
    DL_MCPWM_TZ_ACTION_DISABLE = 3
} DL_MCPWM_TRIP_ZONE_ACTION;

/*! @brief DL_MCPWM_TRIP_ZONE_CBC_MODE */
typedef enum
{
    /*! Disable CBC pulse Clear */
    DL_MCPWM_TZ_CBC_PULSE_CLR_NONE             = 0,
    /*! Clear CBC pulse when counter equals zero */
    DL_MCPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO        = 1,
    /*! Clear CBC pulse when counter equals period */
    DL_MCPWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD      = 2,
    /*! Clear CBC pulse when counter equals zero or period */
    DL_MCPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD = 3
} DL_MCPWM_TRIP_ZONE_CBC_MODE;

/*! @brief DL_MCPWM_SOC_TYPE */
typedef enum
{
    /*! SOC A */
    DL_MCPWM_SOC_A = 0,
    /*! SOC B */
    DL_MCPWM_SOC_B = 1,
    /*! SOC C */
    DL_MCPWM_SOC_C = 2,
    /*! SOC D */
    DL_MCPWM_SOC_D = 3
} DL_MCPWM_SOC_TYPE;

/*! @brief DL_MCPWM_SOC_SOURCE */
typedef enum
{
    /*! Event is Disabled */
    DL_MCPWM_SOC_DISABLED = 0,

    /*! Time-base counter equal to zero */
    DL_MCPWM_SOC_TBCTR_ZERO        = 2,
    /*! Time-base counter equal to period */
    DL_MCPWM_SOC_TBCTR_PERIOD      = 3,
    /*! Time-base counter equal to zero or period */
    DL_MCPWM_SOC_TBCTR_ZERO_PERIOD = 4,

    /*! Time-base counter equal to CMPC when the timer is incrementing */
    DL_MCPWM_SOC_TBCTR_U_CMPC = 8,
    /*! Time-base counter equal to CMPD when the timer is incrementing */
    DL_MCPWM_SOC_TBCTR_U_CMPD = 9,

    /*! Time-base counter equal to CMP1A when the timer is incrementing */
    DL_MCPWM_SOC_TBCTR_U_CMP1A = 10,
    /*! Time-base counter equal to CMP1B when the timer is incrementing */
    DL_MCPWM_SOC_TBCTR_U_CMP1B = 11,

    /*! Time-base counter equal to CMP2A when the timer is incrementing */
    DL_MCPWM_SOC_TBCTR_U_CMP2A = 12,
    /*! Time-base counter equal to CMP2B when the timer is incrementing */
    DL_MCPWM_SOC_TBCTR_U_CMP2B = 13,

    /*! Time-base counter equal to CMP3A when the timer is incrementing */
    DL_MCPWM_SOC_TBCTR_U_CMP3A = 14,
    /*! Time-base counter equal to CMP3B when the timer is incrementing */
    DL_MCPWM_SOC_TBCTR_U_CMP3B = 15,

    /*! Time-base counter equal to CMPC when the timer is Decrementing */
    DL_MCPWM_SOC_TBCTR_D_CMPC = 16,
    /*! Time-base counter equal to CMPD when the timer is Decrementing */
    DL_MCPWM_SOC_TBCTR_D_CMPD = 17,

    /*! Time-base counter equal to CMP1A when the timer is Decrementing */
    DL_MCPWM_SOC_TBCTR_D_CMP1A = 18,
    /*! Time-base counter equal to CMP1B when the timer is Decrementing */
    DL_MCPWM_SOC_TBCTR_D_CMP1B = 19,

    /*! Time-base counter equal to CMP2A when the timer is Decrementing */
    DL_MCPWM_SOC_TBCTR_D_CMP2A = 20,
    /*! Time-base counter equal to CMP2B when the timer is Decrementing */
    DL_MCPWM_SOC_TBCTR_D_CMP2B = 21,

    /*! Time-base counter equal to CMP3A when the timer is Decrementing */
    DL_MCPWM_SOC_TBCTR_D_CMP3A = 22,
    /*! Time-base counter equal to CMP3B when the timer is Decrementing */
    DL_MCPWM_SOC_TBCTR_D_CMP3B = 23
} DL_MCPWM_SOC_SOURCE;

/*! @brief DL_MCPWM_EVENT_TRIGGER_TYPE */
typedef enum
{
    /*! EVT 1 */
    DL_MCPWM_ET_1 = 0,
    /*! EVT 2 */
    DL_MCPWM_ET_2 = 1
} DL_MCPWM_EVENT_TRIGGER_TYPE;

/*! @brief DL_MCPWM_EVENT_TRIGGER_SOURCE */
typedef enum
{
    /*! Event is Disabled */
    DL_MCPWM_EVT_DISABLED = 0,

    /*! Time-base counter equal to zero */
    DL_MCPWM_EVT_TBCTR_ZERO        = 2,
    /*! Time-base counter equal to period */
    DL_MCPWM_EVT_TBCTR_PERIOD      = 3,
    /*! Time-base counter equal to zero or period */
    DL_MCPWM_EVT_TBCTR_ZERO_PERIOD = 4,

    /*! Time-base counter equal to CMPC when the timer is incrementing */
    DL_MCPWM_EVT_TBCTR_U_CMPC = 8,
    /*! Time-base counter equal to CMPD when the timer is incrementing */
    DL_MCPWM_EVT_TBCTR_U_CMPD = 9,

    /*! Time-base counter equal to CMP1A when the timer is incrementing */
    DL_MCPWM_EVT_TBCTR_U_CMP1A = 10,
    /*! Time-base counter equal to CMP1B when the timer is incrementing */
    DL_MCPWM_EVT_TBCTR_U_CMP1B = 11,

    /*! Time-base counter equal to CMP2A when the timer is incrementing */
    DL_MCPWM_EVT_TBCTR_U_CMP2A = 12,
    /*! Time-base counter equal to CMP2B when the timer is incrementing */
    DL_MCPWM_EVT_TBCTR_U_CMP2B = 13,

    /*! Time-base counter equal to CMP3A when the timer is incrementing */
    DL_MCPWM_EVT_TBCTR_U_CMP3A = 14,
    /*! Time-base counter equal to CMP3B when the timer is incrementing */
    DL_MCPWM_EVT_TBCTR_U_CMP3B = 15,

    /*! Time-base counter equal to CMPC when the timer is Decrementing */
    DL_MCPWM_EVT_TBCTR_D_CMPC = 16,
    /*! Time-base counter equal to CMPD when the timer is Decrementing */
    DL_MCPWM_EVT_TBCTR_D_CMPD = 17,

    /*! Time-base counter equal to CMP1A when the timer is Decrementing */
    DL_MCPWM_EVT_TBCTR_D_CMP1A = 18,
    /*! Time-base counter equal to CMP1B when the timer is Decrementing */
    DL_MCPWM_EVT_TBCTR_D_CMP1B = 19,

    /*! Time-base counter equal to CMP2A when the timer is Decrementing */
    DL_MCPWM_EVT_TBCTR_D_CMP2A = 20,
    /*! Time-base counter equal to CMP2B when the timer is Decrementing */
    DL_MCPWM_EVT_TBCTR_D_CMP2B = 21,

    /*! Time-base counter equal to CMP3A when the timer is Decrementing */
    DL_MCPWM_EVT_TBCTR_D_CMP3A = 22,
    /*! Time-base counter equal to CMP3B when the timer is Decrementing */
    DL_MCPWM_EVT_TBCTR_D_CMP3B = 23
} DL_MCPWM_EVENT_TRIGGER_SOURCE;

/**
 * @brief MCPWM Time Base configuration structure
 */
typedef struct
{
    /*! Configure clock prescale/divider. Configures TBCTL.CLKDIV
        - Valid values: @ref DL_MCPWM_CLOCK_DIVIDER
    */
    DL_MCPWM_CLOCK_DIVIDER clockDivider;

    /*! Select Time Base Counter mode. Configures TBCTL.CTR_MODE
        - Valid values: @ref DL_MCPWM_TIME_BASE_COUNT_MODE
    */
    DL_MCPWM_TIME_BASE_COUNT_MODE counterMode;

    /*! Direction of counter after Sync. Configures TBCTL.PHSDIR
        - Valid values: @ref DL_MCPWM_SYNC_COUNT_MODE
    */
    DL_MCPWM_SYNC_COUNT_MODE counterDirectionAfterSync;

    /*! Set Time Base Period. Configures TBCTL.TBPRD and TBCTL.TBPRDS
        - Valid values: 16 bit unsigned period value in cycles
    */
    uint16_t periodValue;

    /*! Configures initial value of TBCTR.TBCTR
        - Valid values: 16 bit unsigned integer
    */
    uint16_t initialCounterValue;

    /*! Enable phase shift load. Configures TBCTL.PHSEN
        - true : enable phase shift loading
        - false : disable phase shift loading
    */
    bool enablePhaseShift;

    /*! Configure Phase Shift count. Configures TBCTL.TBPHS
        - Valid values: 16 bit unsigned phase count in cycles
    */
    uint16_t phaseShiftValue;

    /*! Select Sync In pulse source. Configures TBCTL.SYNCISEL
        - Valid values: @ref DL_MCPWM_SYNC_IN_PULSE_SOURCE
    */
    DL_MCPWM_SYNC_IN_PULSE_SOURCE syncInSource;

    /*! Select SYNCPER source. Configures TBCTL.SYNCPERSEL
        - Valid values: @ref DL_MCPWM_SYNCPERSEL_SOURCE
    */
    DL_MCPWM_SYNCPERSEL_SOURCE syncPerSource;

    /*! Select Sync Out pulse source. Configures TBCTL.SYNCOSEL
        - Valid values: @ref DL_MCPWM_SYNC_OUT_PULSE_MODE
    */
    DL_MCPWM_SYNC_OUT_PULSE_MODE syncOutPulseMode;

    /*! Set emulation mode. Configures TBCTL.FREE_SOFT
        - Valid values: @ref DL_MCPWM_EMULATION_MODE
    */
    DL_MCPWM_EMULATION_MODE emulationMode;
} DL_MCPWM_TimeBaseConfig;

/**
 * @brief MCPWM Counter Compare configuration structure
 */
typedef struct
{
    /*! Configures initial value of PWM1_CMPA and PWM1_CMPAS
        - Valid values: 16 bit unsigned integer - compare value in cycles/counts
    */
    uint16_t pwm1CompareAValue;

    /*! Configures initial value of PWM1_CMPB and PWM1_CMPBS
        - Valid values: 16 bit unsigned integer - compare value in cycles/counts
    */
    uint16_t pwm1CompareBValue;

    /*! Configures initial value of PWM2_CMPA and PWM2_CMPAS
        - Valid values: 16 bit unsigned integer - compare value in cycles/counts
    */
    uint16_t pwm2CompareAValue;

    /*! Configures initial value of PWM2_CMPB and PWM2_CMPBS
        - Valid values: 16 bit unsigned integer - compare value in cycles/counts
    */
    uint16_t pwm2CompareBValue;

    /*! Configures initial value of PWM3_CMPA and PWM3_CMPAS
        - Valid values: 16 bit unsigned integer - compare value in cycles/counts
    */
    uint16_t pwm3CompareAValue;

    /*! Configures initial value of PWM3_CMPB and PWM3_CMPBS
        - Valid values: 16 bit unsigned integer - compare value in cycles/counts
    */
    uint16_t pwm3CompareBValue;

    /*! Configures initial value of CMPC
        - Valid values: 16 bit unsigned integer - compare value in cycles/counts
    */
    uint16_t compareCValue;

    /*! Configures initial value of CMPD
        - Valid values: 16 bit unsigned integer - compare value in cycles/counts
    */
    uint16_t compareDValue;
} DL_MCPWM_CounterCompareConfig;

/**
 * @brief MCPWM Action Qualifier configuration action on events structure
 */
typedef struct
{
    /*! Action When TBCTR = 0. Configures PWM1/2/3_AQCTLA/AS/B/BS.ZRO
        - Valid values: @ref DL_MCPWM_ACTION_QUALIFIER_OUTPUT
    */
    DL_MCPWM_ACTION_QUALIFIER_OUTPUT actionAtZero;

    /*! Action When TBCTR = TBPRD. Configures PWM1/2/3_AQCTLA/AS/B/BS.PRD
        - Valid values: @ref DL_MCPWM_ACTION_QUALIFIER_OUTPUT
    */
    DL_MCPWM_ACTION_QUALIFIER_OUTPUT actionAtPeriod;

    /*! Action When TBCTR = PWM1_CMPA on Up Count. Configures PWM1/2/3_AQCTLA/AS/B/BS.CAU
        - Valid values: @ref DL_MCPWM_ACTION_QUALIFIER_OUTPUT
    */
    DL_MCPWM_ACTION_QUALIFIER_OUTPUT actionAtCountUpCmpA;

    /*! Action When TBCTR = PWM1_CMPA on Down Count. Configures PWM1/2/3_AQCTLA/AS/B/BS.CAD
        - Valid values: @ref DL_MCPWM_ACTION_QUALIFIER_OUTPUT
    */
    DL_MCPWM_ACTION_QUALIFIER_OUTPUT actionAtCountDownCmpA;

    /*! Action When TBCTR = PWM1_CMPB on Up Count. Configures PWM1/2/3_AQCTLA/AS/B/BS.CBU
        - Valid values: @ref DL_MCPWM_ACTION_QUALIFIER_OUTPUT
    */
    DL_MCPWM_ACTION_QUALIFIER_OUTPUT actionAtCountUpCmpB;

    /*! Action When TBCTR = PWM1_CMPB on Down Count. Configures PWM1/2/3_AQCTLA/AS/B/BS.CBD
        - Valid values: @ref DL_MCPWM_ACTION_QUALIFIER_OUTPUT
    */
    DL_MCPWM_ACTION_QUALIFIER_OUTPUT actionAtCountDownCmpB;

    /*! Action qualifier software force actions on PWM1A/1B/2A/2B/3A/3B. Configures PWM1/2/3_AQSFRC.PWMA/B
        - Valid values: @ref DL_MCPWM_ACTION_QUALIFIER_SW_FORCE_OUTPUT
    */
    DL_MCPWM_ACTION_QUALIFIER_SW_FORCE_OUTPUT pwmSwForceAction;
} DL_MCPWM_Actions;

/**
 * @brief MCPWM Action Qualifier configuration structure
 */
typedef struct
{
    /*! Action qualifier actions configuration structure for PWM1_A.
        Configures PWM1_AQCTLA and PWM1_AQCTLAS */
    DL_MCPWM_Actions aqPwm1A;

    /*! Action qualifier actions configuration structure for PWM1_B.
        Configures PWM1_AQCTLB and PWM1_AQCTLBS */
    DL_MCPWM_Actions aqPwm1B;

    /*! Action qualifier actions configuration structure for PWM2_A.
        Configures PWM2_AQCTLA and PWM2_AQCTLAS */
    DL_MCPWM_Actions aqPwm2A;

    /*! Action qualifier actions configuration structure for PWM2_B.
        Configures PWM2_AQCTLB and PWM2_AQCTLBS */
    DL_MCPWM_Actions aqPwm2B;

    /*! Action qualifier actions configuration structure for PWM3_A.
        Configures PWM3_AQCTLA and PWM3_AQCTLAS */
    DL_MCPWM_Actions aqPwm3A;

    /*! Action qualifier actions configuration structure for PWM3_B.
        Configures PWM3_AQCTLB and PWM3_AQCTLBS */
    DL_MCPWM_Actions aqPwm3B;
} DL_MCPWM_ActionQualifierConfig;

/**
 * @brief MCPWM Dead-Band configuration structure
 */
typedef struct
{
    /*! Configure Dead-Band output mode. Configures DBCTL.OUT_MODE bit0.
        - false : Delay is bypassed for A signal Path. InA fed to A path,
        - true : Rising Edge delay for A signal path
    */
    bool enableRisingEdgeDelayOnPathA;

    /*! Configure Dead-Band output mode. Configures DBCTL.OUT_MODE bit1.
        - false : Delay is bypassed for B signal Path - InB fed to B path,
        - true : Falling Edge delay for B signal path
    */
    bool enableFallingEdgeDelayOnPathB;

    /*! Configures DBCTL.OUTSWAP bit 6
        - false : OutA is fed by A path
        - true : OutA is fed by B path
    */
    bool enableOutputSwapA;

    /*! Configures DBCTL.OUTSWAP bit 7
        - false : OutB is fed by B path
        - true : OutB is fed by A path
    */
    bool enableOutputSwapB;

    /*! Configure polarity(inversion) on Rising edge delayed path. Configures DBCTL.POLSEL bit2
        - Valid values: @ref DL_MCPWM_DEADBAND_POLARITY
    */
    DL_MCPWM_DEADBAND_POLARITY risingEdgeDelayPolarity;

    /*!
        Configure polarity(inversion) on Falling edge delayed path. Configures DBCTL.POLSEL bit3
        - Valid values: @ref DL_MCPWM_DEADBAND_POLARITY
    */
    DL_MCPWM_DEADBAND_POLARITY fallingEdgeDelayPolarity;

    /*! Configures DBCTL.IN_MODE bit4
        - Valid values: @ref DL_MCPWM_DB_INPUT. Except DL_MCPWM_DB_INPUT_DB_RED
    */
    uint16_t risingEdgeDelayInputSource;

    /*! Configures DBCTL.IN_MODE bit5
        - Valid values: @ref DL_MCPWM_DB_INPUT
    */
    uint16_t fallingEdgeDelayInputSource;

    /*! Configures initial value of DBFED and DBFEFS
        - Valid values: 14 bit unsigned integer
    */
    uint16_t fallingEdgeDelayCount;

    /*! Configures initial value of DBRED and DBREDS
        - Valid values: 14 bit unsigned integer
    */
    uint16_t risingEdgeDelayCount;

} DL_MCPWM_DeadBandConfig;

/**
 * @brief MCPWM Trip Zone configuration structure
 */
typedef struct
{
    /*! Enable trip zone input signals TZ1-8 as Cycle By Cycle (CBC) or One Shot (OST) source. Configures TZSEL.CBC1-8
       and TZSEL.OST1-8
        - Valid values: @ref DL_MCPWM_TZ_SIGNAL (multiple sources may be ORed together)
    */
    uint32_t enableTripZoneMask;

    /*! Select trip zone CBC event. Configures TZCTL.CBCPULSE
        - Valid values: @ref DL_MCPWM_TRIP_ZONE_CBC_MODE
    */
    DL_MCPWM_TRIP_ZONE_CBC_MODE cbcClearEvent;

    /*! Select Trip Zone action for A. Configures TZCTL.TZA
        - Valid values: @ref DL_MCPWM_TRIP_ZONE_ACTION
    */
    DL_MCPWM_TRIP_ZONE_ACTION actionOnA;

    /*! Select Trip Zone action for B. Configures TZCTL.TZB
        - Valid values: @ref DL_MCPWM_TRIP_ZONE_ACTION
    */
    DL_MCPWM_TRIP_ZONE_ACTION actionOnB;
} DL_MCPWM_TripZoneConfig;

/**
 * @brief MCPWM Event Trigger SOC Pulse generator event specific configuration structure
 */
typedef struct
{
    /*! SOCA/B/C/D Selection Enable. Configures SOCEN.SOCA/B/C/D_ENABLE */
    bool enable;

    /*! SOCA/B/C/D Event source Selection. Configures SOCSEL.SOCA/B/C/DSEL
        - Valid values: @ref DL_MCPWM_SOC_SOURCE
    */
    DL_MCPWM_SOC_SOURCE eventSource;

    /*! SOCA/B/C/D Period - how many selected SOCA/B/C/D events need to occur before SOCA/B/C/D pulse is generated.
       Configures SOCPERIOD.SOCA/B/C/D_PERIOD
        - Valid values: 0-7
    */
    uint16_t eventPeriod;
} DL_MCPWM_SOCGenConfig;

/**
 * @brief MCPWM Event Trigger SOC Pulse generator structure
 */
typedef struct
{
    /*! SOCA configuration */
    DL_MCPWM_SOCGenConfig SOCA;
    /*! SOCB configuration */
    DL_MCPWM_SOCGenConfig SOCB;
    /*! SOCC configuration */
    DL_MCPWM_SOCGenConfig SOCC;
    /*! SOCD configuration */
    DL_MCPWM_SOCGenConfig SOCD;
} DL_MCPWM_EventTriggerSOCPulseGeneratorConfig;

/**
 * @brief MCPWM Event Trigger ET event specific configuration structure
 */
typedef struct
{
    /*! ET1/2 Event source Selection. Configures ETSEL.ET1/2_SEL
        - Valid values: @ref DL_MCPWM_EVENT_TRIGGER_SOURCE
    */
    DL_MCPWM_EVENT_TRIGGER_SOURCE eventSource;

    /*! ET1/2 Period - how many selected ET1/2 events need to occur before ET1/2 pulse is generated. Configures
       ETPERIOD.ET1/2_PERIOD
        - Valid values: 0-7
    */
    uint16_t eventPeriod;
} DL_MCPWM_ETGenConfig;

/**
 * @brief MCPWM Event Trigger ET configuration structure
 */
typedef struct
{
    /*! ET1 configuration */
    DL_MCPWM_ETGenConfig ET1;
    /*! ET2 configuration */
    DL_MCPWM_ETGenConfig ET2;
} DL_MCPWM_EventTriggerETConfig;

/**
 * @brief MCPWM Event Trigger configuration structure
 */
typedef struct
{
    /*! Event Trigger SOC Pulse Generator configuration */
    DL_MCPWM_EventTriggerSOCPulseGeneratorConfig socPulseGenConfig;

    /*! Event Trigger ET configuration */
    DL_MCPWM_EventTriggerETConfig etConfig;

    /*! Event Trigger Interrupt Generator configuration
        Valid values: @ref DL_MCPWM_INT (multiple sources may be ORed together)
    */
    uint32_t interruptGenConfig;
} DL_MCPWM_EventTriggerConfig;

/**
 * @brief MCPWM Global Load configuration structure
 */
typedef struct
{
    /*! Enable global load. Configures GLDCTL.GLD */
    bool enableGlobalLoad;

    /*! Enable global load one shot. Configures GLDCTL.OSHTMODE */
    bool enableOneShotMode;

    /*! Select Global Load trigger event. Configures GLDCTL.GLDMODE
        - Valid values: @ref DL_MCPWM_GLOBAL_LOAD_TRIGGER
    */
    DL_MCPWM_GLOBAL_LOAD_TRIGGER triggerEvent;

    /*! Turn on the one shot latch condition ON. Allow one shadow to active reload.
        - true : Writes 1 to GLDOSHTCTL.OSHTLD
        - false : Writes 1 to GLDOSHTCTL.OSHTCLR
    */
    bool enableOneShotLatch;

    /*! Issue force load event in one shot mode. Write 1 to GLDOSHTCTL.GFRCLD */
    bool forceLoadEvent;
} DL_MCPWM_GlobalLoadConfig;

/**
 * @brief MCPWM Shadow to Active Load Mode configuration structure
 */
typedef struct
{
    /*! Shadow to Active load mode of PWM1 CMPA. Configures CMPCTL.PWM1_LOADAMODE */
    DL_MCPWM_COUNTER_COMPARE_LOAD_MODE    pwm1CmpALoadMode;
    /*! Shadow to Active load mode of PWM1 CMPB. Configures CMPCTL.PWM1_LOADBMODE */
    DL_MCPWM_COUNTER_COMPARE_LOAD_MODE    pwm1CmpBLoadMode;
    /*! Shadow to Active load mode of PWM2 CMPA. Configures CMPCTL.PWM2_LOADAMODE */
    DL_MCPWM_COUNTER_COMPARE_LOAD_MODE    pwm2CmpALoadMode;
    /*! Shadow to Active load mode of PWM2 CMPB. Configures CMPCTL.PWM2_LOADBMODE */
    DL_MCPWM_COUNTER_COMPARE_LOAD_MODE    pwm2CmpBLoadMode;
    /*! Shadow to Active load mode of PWM3 CMPA. Configures CMPCTL.PWM3_LOADAMODE */
    DL_MCPWM_COUNTER_COMPARE_LOAD_MODE    pwm3CmpALoadMode;
    /*! Shadow to Active load mode of PWM3 CMPB. Configures CMPCTL.PWM3_LOADBMODE */
    DL_MCPWM_COUNTER_COMPARE_LOAD_MODE    pwm3CmpBLoadMode;
    /*! Shadow to Active load mode of CMPC. Configures CMPCTL.LOADCMODE */
    DL_MCPWM_COUNTER_COMPARE_LOAD_MODE    cmpCLoadMode;
    /*! Shadow to Active load mode of CMPD. Configures CMPCTL.LOADDMODE */
    DL_MCPWM_COUNTER_COMPARE_LOAD_MODE    cmpDLoadMode;
    /*! Shadow to Active load mode of PWM1 AQCTLA. Configures AQCTL.PWM1_LDAQAMODE */
    DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE   pwm1AaqLoadMode;
    /*! Shadow to Active load mode of PWM1 AQCTLB. Configures AQCTL.PWM1_LDAQBMODE */
    DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE   pwm1BaqLoadMode;
    /*! Shadow to Active load mode of PWM2 AQCTLA. Configures AQCTL.PWM2_LDAQAMODE */
    DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE   pwm2AaqLoadMode;
    /*! Shadow to Active load mode of PWM2 AQCTLB. Configures AQCTL.PWM2_LDAQBMODE */
    DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE   pwm2BaqLoadMode;
    /*! Shadow to Active load mode of PWM3 AQCTLA. Configures AQCTL.PWM3_LDAQAMODE */
    DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE   pwm3AaqLoadMode;
    /*! Shadow to Active load mode of PWM3 AQCTLB. Configures AQCTL.PWM3_LDAQBMODE */
    DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE   pwm3BaqLoadMode;
    /*! Shadow to Active load mode of period */
    DL_MCPWM_PERIOD_LOAD_MODE             periodLoadMode;
    /*! Shadow to Active load of DBFED. Configures DBCTL.LOADFEDMODE */
    DL_MCPWM_FALLING_EDGE_DELAY_LOAD_MODE fallingEdgeDelayLoadMode;
    /*! Shadow to Active load of DBRED. Configures DBCTL.LOADREDMODE */
    DL_MCPWM_RISING_EDGE_DELAY_LOAD_MODE  risingEdgeDelayLoadMode;
    /*! Global Load configuration */
    DL_MCPWM_GlobalLoadConfig             globalLoadConfig;
} DL_MCPWM_LoadModeConfig;

/**
 * @brief MCPWM configuration structure
 */
typedef struct
{
    /*! Time Base configuration */
    DL_MCPWM_TimeBaseConfig        timeBaseConfig;
    /*! Counter Compare configuration */
    DL_MCPWM_CounterCompareConfig  counterCompareConfig;
    /*!Action Qualifier configuration  */
    DL_MCPWM_ActionQualifierConfig actionQualifierConfig;
    /*! Dead-Band configuration */
    DL_MCPWM_DeadBandConfig        deadBandConfig;
    /*! Trip Zone configuration */
    DL_MCPWM_TripZoneConfig        tripZoneConfig;
    /*! Event Trigger configuration */
    DL_MCPWM_EventTriggerConfig    eventTriggerConfig;
    /*! Shadow to Active Load mode configuration */
    DL_MCPWM_LoadModeConfig        loadModeConfig;
} DL_MCPWM_Config;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************

/**
 *  @brief      Sets the phase shift offset counter value
 *
 *  @param[in]  mcpwm           Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  phaseCount      Phase shift count value.
 *
 */
__STATIC_INLINE void DL_MCPWM_setPhaseShift(MCPWM_Regs *mcpwm, uint16_t phaseCount)
{
    DL_Common_updateReg(&mcpwm->TBPHS, phaseCount, MCPWM_TBPHS_TBPHS_MASK);
}

/**
 *  @brief      Sets the time base count
 *
 *  @param[in]  mcpwm            Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  count            Time base count value.
 *
 */
__STATIC_INLINE void DL_MCPWM_setTimeBaseCounter(MCPWM_Regs *mcpwm, uint16_t count)
{
    DL_Common_updateReg(&mcpwm->TBCTR, count, MCPWM_TBCTR_TBCTR_MASK);
}

/**
 *  @brief      Returns time base counter value.
 *
 *  @param[in]  mcpwm            Pointer to the register overlay for the peripheral.
 *
 *  @return     Returns the time base counter value
 */
__STATIC_INLINE uint16_t DL_MCPWM_getTimeBaseCounterValue(MCPWM_Regs *mcpwm)
{
    return (uint16_t)((mcpwm->TBCTR & (MCPWM_TBCTR_TBCTR_MASK)) >> (MCPWM_TBCTR_TBCTR_OFS));
}

/**
 *  @brief      Set time base counter mode.
 *
 *  @param[in]  mcpwm            Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  counterMode      Time base counter mode.
 *
 */
__STATIC_INLINE void DL_MCPWM_setTimeBaseCounterMode(MCPWM_Regs *mcpwm, DL_MCPWM_TIME_BASE_COUNT_MODE counterMode)
{
    DL_Common_updateReg(&mcpwm->TBCTL, counterMode, MCPWM_TBCTL_CTRMODE_MASK);
}

/**
 *  @brief      Return time base counter direction.
 *
 *  @param[in]  mcpwm            Pointer to the register overlay for the peripheral.
 *
 *  @return     Returns the time base counter direction
 *
 *  @retval     One of @ref DL_MCPWM_TIME_BASE_COUNT_MODE
 */
__STATIC_INLINE uint32_t DL_MCPWM_getTimeBaseCounterDirection(MCPWM_Regs *mcpwm)
{
    return (mcpwm->TBSTS & MCPWM_TBSTS_CTRDIR_MASK);
}

/**
 *  @brief      Set the time base clock and the high speed time base clock count pre-scaler.
 *
 *  @param[in]  mcpwm            Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  prescaler        The time base count pre scale value.
 *
 */
__STATIC_INLINE void DL_MCPWM_setClockPrescaler(MCPWM_Regs *mcpwm, DL_MCPWM_CLOCK_DIVIDER prescaler)
{
    DL_Common_updateReg(&mcpwm->TBCTL, ((uint32_t)prescaler << MCPWM_TBCTL_CLKDIV_OFS), MCPWM_TBCTL_CLKDIV_MASK);
}

/**
 *  @brief      Set PWM period load mode.
 *
 *  @param[in]  mcpwm           Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  loadMode        TPWM period load mode.
 *
 */
__STATIC_INLINE void DL_MCPWM_setPeriodLoadMode(MCPWM_Regs *mcpwm, DL_MCPWM_PERIOD_LOAD_MODE loadMode)
{
    if (loadMode == DL_MCPWM_PERIOD_SHADOW_LOAD_ENABLE)
    {
        mcpwm->TBCTL &= ~MCPWM_TBCTL_PRDLD_MASK;
    }
    else
    {
        mcpwm->TBCTL |= MCPWM_TBCTL_PRDLD_MASK;
    }
}

/**
 *  @brief      Enable phase shift load.
 *
 *  @param[in]  mcpwm           Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_enablePhaseShiftLoad(MCPWM_Regs *mcpwm)
{
    mcpwm->TBCTL |= ((uint32_t)MCPWM_TBCTL_PHSEN_MASK);
}

/**
 *  @brief      Disable phase shift load.
 *
 *  @param[in]  mcpwm           Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_disablePhaseShiftLoad(MCPWM_Regs *mcpwm)
{
    mcpwm->TBCTL &= ~((uint32_t)MCPWM_TBCTL_PHSEN_MASK);
}

/**
 *  @brief      Set count mode after phase shift sync.
 *
 *  @param[in]  mcpwm           Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  mode            This is the count mode.
 *
 */
__STATIC_INLINE void DL_MCPWM_setCountModeAfterSync(MCPWM_Regs *mcpwm, DL_MCPWM_SYNC_COUNT_MODE mode)
{
    if (mode == DL_MCPWM_COUNT_MODE_UP_AFTER_SYNC)
    {
        mcpwm->TBCTL |= MCPWM_TBCTL_PHSDIR_MASK;
    }
    else
    {
        mcpwm->TBCTL &= ~MCPWM_TBCTL_PHSDIR_MASK;
    }
}

/**
 *  @brief      Force a software sync pulse.
 *
 *  @param[in]  mcpwm           Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_forceSyncPulse(MCPWM_Regs *mcpwm)
{
    mcpwm->TBCTL |= MCPWM_TBCTL_SWSYNC_MASK;
}

/**
 *  @brief      Set up the sync out pulse event.
 *
 *  @param[in]  mcpwm           Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  mode            This is the sync out mode.
 *
 */
__STATIC_INLINE void DL_MCPWM_setSyncOutPulseMode(MCPWM_Regs *mcpwm, DL_MCPWM_SYNC_OUT_PULSE_MODE mode)
{
    DL_Common_updateReg(&mcpwm->TBCTL, ((uint32_t)mode << MCPWM_TBCTL_SYNCOSEL_OFS), MCPWM_TBCTL_SYNCOSEL_MASK);
}

/**
 *  @brief      Set up the sync out pulse source.
 *
 *  @param[in]  mcpwm               Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  syncPulseSource     This is the SYNCPERSEL source.
 *
 */
__STATIC_INLINE void DL_MCPWM_setSyncPulseSource(MCPWM_Regs *mcpwm, DL_MCPWM_SYNCPERSEL_SOURCE syncPulseSource)
{
    DL_Common_updateReg(&mcpwm->TBCTL, ((uint32_t)syncPulseSource << MCPWM_TBCTL_SYNCPERSEL_OFS),
                        MCPWM_TBCTL_SYNCPERSEL_MASK);
}

/**
 *  @brief      Set up the source for sync-in pulse.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  source            This is the sync-in pulse source.
 *
 */
__STATIC_INLINE void DL_MCPWM_setSyncInPulseSource(MCPWM_Regs *mcpwm, DL_MCPWM_SYNC_IN_PULSE_SOURCE source)
{
    DL_Common_updateReg(&mcpwm->TBCTL, ((uint32_t)source << MCPWM_TBCTL_SYNCISEL_OFS), MCPWM_TBCTL_SYNCISEL_MASK);
}

/**
 *  @brief      Return external sync signal status.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @return     Returns the external sync status.
 *
 *  @retval     true   External sync event has occurred.
 *  @retval     false  No external event has occured.
 */
__STATIC_INLINE bool DL_MCPWM_getSyncStatus(MCPWM_Regs *mcpwm)
{
    return ((mcpwm->TBSTS & MCPWM_TBSTS_SYNCI_MASK) == MCPWM_TBSTS_SYNCI_MASK);
}

/**
 *  @brief      Return external sync signal status.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_clearSyncStatus(MCPWM_Regs *mcpwm)
{
    mcpwm->TBSTSCLR |= MCPWM_TBSTSCLR_SYNCI_MASK;
}

/**
 *  @brief      Sets the PWM period count in its Active Register.
 *
 * This function sets the period of the PWM count in its Active period register.
 * The value of periodCount is the value written to the register. User should
 * map the desired period or frequency of the waveform into the correct
 * periodCount.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  periodCount       This is the period count value.
 *
 */
__STATIC_INLINE void DL_MCPWM_setTimeBasePeriodActive(MCPWM_Regs *mcpwm, uint16_t periodCount)
{
    DL_Common_updateReg(&mcpwm->TBPRD, ((uint32_t)periodCount << MCPWM_TBPRD_TBPRD_OFS), MCPWM_TBPRD_TBPRD_MASK);
}

/**
 *  @brief      Sets the PWM period count in shadow register.
 *
 * This function sets the period of the PWM count in its Shadow period register.
 * The value of periodCount is the value written to the register. User should
 * map the desired period or frequency of the waveform into the correct
 * periodCount.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  periodCount       This is the period count value.
 *
 */
__STATIC_INLINE void DL_MCPWM_setTimeBasePeriodShadow(MCPWM_Regs *mcpwm, uint16_t periodCount)
{
    DL_Common_updateReg(&mcpwm->TBPRDS, ((uint32_t)periodCount << MCPWM_TBPHS_TBPHS_OFS), MCPWM_TBPRDS_TBPRDS_MASK);
}

/**
 *  @brief      Gets the PWM period count
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @return     Returns the PWM period count value.
 *
 */
__STATIC_INLINE uint16_t DL_MCPWM_getTimeBasePeriodActive(MCPWM_Regs *mcpwm)
{
    return (uint16_t)(mcpwm->TBPRD & MCPWM_TBPRD_TBPRD_MASK);
}

/**
 *  @brief      Gets the PWM period count
 *
 *  This function gets the period of the PWM count in its shadow register.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @return     Returns the PWM period count value in its register.
 *
 */
__STATIC_INLINE uint16_t DL_MCPWM_getTimeBasePeriodShadow(MCPWM_Regs *mcpwm)
{
    return (uint16_t)(mcpwm->TBPRDS & MCPWM_TBPRDS_TBPRDS_MASK);
}

/**
 *  @brief      Set counter compare values.
 *
 *   This function sets the active counter compare value for counter compare
 *   registers.
 *   The maximum value for compCount is 0xFFFF.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  compModule        Counter compare value module.
 *
 *  @param[in]  compCount         Counter compare count value.
 */
__STATIC_INLINE void DL_MCPWM_setCounterCompareActiveValue(MCPWM_Regs                     *mcpwm,
                                                           DL_MCPWM_COUNTER_COMPARE_MODULE compModule,
                                                           uint16_t                        compCount)
{
    switch (compModule)
    {
        case DL_MCPWM_COUNTER_COMPARE_1A:
            DL_Common_updateReg(&mcpwm->PWM1_CMPA, ((uint32_t)compCount << MCPWM_PWM1_CMPA_PWM1_CMPA_OFS),
                                MCPWM_PWM1_CMPA_PWM1_CMPA_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_1B:
            DL_Common_updateReg(&mcpwm->PWM1_CMPB, ((uint32_t)compCount << MCPWM_PWM1_CMPB_PWM1_CMPB_OFS),
                                MCPWM_PWM1_CMPB_PWM1_CMPB_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2A:
            DL_Common_updateReg(&mcpwm->PWM2_CMPA, ((uint32_t)compCount << MCPWM_PWM2_CMPA_PWM2_CMPA_OFS),
                                MCPWM_PWM2_CMPA_PWM2_CMPA_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2B:
            DL_Common_updateReg(&mcpwm->PWM2_CMPB, ((uint32_t)compCount << MCPWM_PWM2_CMPB_PWM2_CMPB_OFS),
                                MCPWM_PWM2_CMPB_PWM2_CMPB_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3A:
            DL_Common_updateReg(&mcpwm->PWM3_CMPA, ((uint32_t)compCount << MCPWM_PWM3_CMPA_PWM3_CMPA_OFS),
                                MCPWM_PWM3_CMPA_PWM3_CMPA_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3B:
            DL_Common_updateReg(&mcpwm->PWM3_CMPB, ((uint32_t)compCount << MCPWM_PWM3_CMPB_PWM3_CMPB_OFS),
                                MCPWM_PWM3_CMPB_PWM3_CMPB_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_C:
            DL_Common_updateReg(&mcpwm->CMPC, ((uint32_t)compCount << MCPWM_CMPC_CMPC_OFS), MCPWM_CMPC_CMPC_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_D:
            DL_Common_updateReg(&mcpwm->CMPD, ((uint32_t)compCount << MCPWM_CMPD_CMPD_OFS), MCPWM_CMPD_CMPD_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Get counter compare values.
 *
 *   This function gets the active counter compare value for counter compare
 *   registers.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  compModule        Counter compare value module.
 *
 *  @return    Returns active counter compare values for a selected counter compare module.
 *
 */
__STATIC_INLINE uint16_t DL_MCPWM_getCounterCompareActiveValue(MCPWM_Regs                     *mcpwm,
                                                               DL_MCPWM_COUNTER_COMPARE_MODULE compModule)
{
    uint16_t retValue = 0;

    switch (compModule)
    {
        case DL_MCPWM_COUNTER_COMPARE_1A:
            retValue = ((mcpwm->PWM1_CMPA & MCPWM_PWM1_CMPA_PWM1_CMPA_MASK) >> MCPWM_PWM1_CMPA_PWM1_CMPA_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_1B:
            retValue = ((mcpwm->PWM1_CMPB & MCPWM_PWM1_CMPB_PWM1_CMPB_MASK) >> MCPWM_PWM1_CMPB_PWM1_CMPB_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2A:
            retValue = ((mcpwm->PWM2_CMPA & MCPWM_PWM2_CMPA_PWM2_CMPA_MASK) >> MCPWM_PWM2_CMPA_PWM2_CMPA_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2B:
            retValue = ((mcpwm->PWM2_CMPB & MCPWM_PWM2_CMPB_PWM2_CMPB_MASK) >> MCPWM_PWM2_CMPB_PWM2_CMPB_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3A:
            retValue = ((mcpwm->PWM3_CMPA & MCPWM_PWM3_CMPA_PWM3_CMPA_MASK) >> MCPWM_PWM3_CMPA_PWM3_CMPA_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3B:
            retValue = ((mcpwm->PWM3_CMPB & MCPWM_PWM3_CMPB_PWM3_CMPB_MASK) >> MCPWM_PWM3_CMPB_PWM3_CMPB_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_C:
            retValue = ((mcpwm->CMPC & MCPWM_CMPC_CMPC_MASK) >> MCPWM_CMPC_CMPC_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_D:
            retValue = ((mcpwm->CMPD & MCPWM_CMPD_CMPD_MASK) >> MCPWM_CMPD_CMPD_OFS);
            break;
        default:
            break;
    }
    return retValue;
}

/**
 *  @brief      Set counter compare values.
 *
 *   This function sets the shadow counter compare value for counter compare
 *   registers.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  compModule        Counter compare value module.
 *
 *  @param[in]  compCount         Counter compare count value.
 */
__STATIC_INLINE void DL_MCPWM_setCounterCompareShadowValue(MCPWM_Regs                     *mcpwm,
                                                           DL_MCPWM_COUNTER_COMPARE_MODULE compModule,
                                                           uint16_t                        compCount)
{
    switch (compModule)
    {
        case DL_MCPWM_COUNTER_COMPARE_1A:
            DL_Common_updateReg(&mcpwm->PWM1_CMPAS, ((uint32_t)compCount << MCPWM_PWM1_CMPAS_PWM1_CMPAS_OFS),
                                MCPWM_PWM1_CMPAS_PWM1_CMPAS_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_1B:
            DL_Common_updateReg(&mcpwm->PWM1_CMPBS, ((uint32_t)compCount << MCPWM_PWM1_CMPBS_PWM1_CMPBS_OFS),
                                MCPWM_PWM1_CMPBS_PWM1_CMPBS_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2A:
            DL_Common_updateReg(&mcpwm->PWM2_CMPAS, ((uint32_t)compCount << MCPWM_PWM2_CMPAS_PWM2_CMPAS_OFS),
                                MCPWM_PWM2_CMPAS_PWM2_CMPAS_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2B:
            DL_Common_updateReg(&mcpwm->PWM2_CMPBS, ((uint32_t)compCount << MCPWM_PWM2_CMPBS_PWM2_CMPBS_OFS),
                                MCPWM_PWM2_CMPBS_PWM2_CMPBS_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3A:
            DL_Common_updateReg(&mcpwm->PWM3_CMPAS, ((uint32_t)compCount << MCPWM_PWM3_CMPAS_PWM3_CMPAS_OFS),
                                MCPWM_PWM3_CMPAS_PWM3_CMPAS_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3B:
            DL_Common_updateReg(&mcpwm->PWM3_CMPBS, ((uint32_t)compCount << MCPWM_PWM3_CMPBS_PWM3_CMPBS_OFS),
                                MCPWM_PWM3_CMPBS_PWM3_CMPBS_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_C:
            DL_Common_updateReg(&mcpwm->CMPCS, ((uint32_t)compCount << MCPWM_CMPCS_CMPCS_OFS), MCPWM_CMPCS_CMPCS_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_D:
            DL_Common_updateReg(&mcpwm->CMPDS, ((uint32_t)compCount << MCPWM_CMPDS_CMPDS_OFS), MCPWM_CMPDS_CMPDS_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Get counter compare values.
 *
 *   This function gets the value for shadow counter compare registers.
 *   registers.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  compModule        Counter compare value module.
 *
 *  @return    Returns shadow counter compare values for a selected counter compare module.
 */
__STATIC_INLINE uint16_t DL_MCPWM_getCounterCompareShadowValue(MCPWM_Regs                     *mcpwm,
                                                               DL_MCPWM_COUNTER_COMPARE_MODULE compModule)
{
    uint16_t retValue = 0;

    switch (compModule)
    {
        case DL_MCPWM_COUNTER_COMPARE_1A:
            retValue = ((mcpwm->PWM1_CMPAS & MCPWM_PWM1_CMPAS_PWM1_CMPAS_MASK) >> MCPWM_PWM1_CMPAS_PWM1_CMPAS_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_1B:
            retValue = ((mcpwm->PWM1_CMPBS & MCPWM_PWM1_CMPBS_PWM1_CMPBS_MASK) >> MCPWM_PWM1_CMPBS_PWM1_CMPBS_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2A:
            retValue = ((mcpwm->PWM2_CMPAS & MCPWM_PWM2_CMPAS_PWM2_CMPAS_MASK) >> MCPWM_PWM2_CMPAS_PWM2_CMPAS_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2B:
            retValue = ((mcpwm->PWM2_CMPBS & MCPWM_PWM2_CMPBS_PWM2_CMPBS_MASK) >> MCPWM_PWM2_CMPBS_PWM2_CMPBS_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3A:
            retValue = ((mcpwm->PWM3_CMPAS & MCPWM_PWM3_CMPAS_PWM3_CMPAS_MASK) >> MCPWM_PWM3_CMPAS_PWM3_CMPAS_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3B:
            retValue = ((mcpwm->PWM3_CMPBS & MCPWM_PWM3_CMPBS_PWM3_CMPBS_MASK) >> MCPWM_PWM3_CMPBS_PWM3_CMPBS_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_C:
            retValue = ((mcpwm->CMPCS & MCPWM_CMPCS_CMPCS_MASK) >> MCPWM_CMPCS_CMPCS_OFS);
            break;
        case DL_MCPWM_COUNTER_COMPARE_D:
            retValue = ((mcpwm->CMPDS & MCPWM_CMPDS_CMPDS_MASK) >> MCPWM_CMPDS_CMPDS_OFS);
            break;
        default:
            break;
    }

    return retValue;
}

/**
 *  @brief      Sets up the Counter Compare shadow load mode.
 *
 *   This function enables and sets up the counter compare shadow load mode.
 *   registers.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  compModule        Counter compare value module.
 *
 *  @param[in]  loadMode          Shadow to active load mode.
 *
 */
__STATIC_INLINE void DL_MCPWM_setCounterCompareShadowLoadMode(MCPWM_Regs                        *mcpwm,
                                                              DL_MCPWM_COUNTER_COMPARE_MODULE    compModule,
                                                              DL_MCPWM_COUNTER_COMPARE_LOAD_MODE loadMode)
{
    switch (compModule)
    {
        case DL_MCPWM_COUNTER_COMPARE_1A:
            DL_Common_updateReg(&mcpwm->CMPCTL, ((uint32_t)loadMode << MCPWM_CMPCTL_PWM1_LOADAMODE_OFS),
                                MCPWM_CMPCTL_PWM1_LOADAMODE_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_1B:
            DL_Common_updateReg(&mcpwm->CMPCTL, ((uint32_t)loadMode << MCPWM_CMPCTL_PWM1_LOADBMODE_OFS),
                                MCPWM_CMPCTL_PWM1_LOADBMODE_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2A:
            DL_Common_updateReg(&mcpwm->CMPCTL, ((uint32_t)loadMode << MCPWM_CMPCTL_PWM2_LOADAMODE_OFS),
                                MCPWM_CMPCTL_PWM2_LOADAMODE_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_2B:
            DL_Common_updateReg(&mcpwm->CMPCTL, ((uint32_t)loadMode << MCPWM_CMPCTL_PWM2_LOADBMODE_OFS),
                                MCPWM_CMPCTL_PWM2_LOADBMODE_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3A:
            DL_Common_updateReg(&mcpwm->CMPCTL, ((uint32_t)loadMode << MCPWM_CMPCTL_PWM3_LOADAMODE_OFS),
                                MCPWM_CMPCTL_PWM3_LOADAMODE_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_3B:
            DL_Common_updateReg(&mcpwm->CMPCTL, ((uint32_t)loadMode << MCPWM_CMPCTL_PWM3_LOADBMODE_OFS),
                                MCPWM_CMPCTL_PWM3_LOADBMODE_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_C:
            DL_Common_updateReg(&mcpwm->CMPCTL, ((uint32_t)loadMode << MCPWM_CMPCTL_LOADCMODE_OFS),
                                MCPWM_CMPCTL_LOADCMODE_MASK);
            break;
        case DL_MCPWM_COUNTER_COMPARE_D:
            DL_Common_updateReg(&mcpwm->CMPCTL, ((uint32_t)loadMode << MCPWM_CMPCTL_LOADDMODE_OFS),
                                MCPWM_CMPCTL_LOADDMODE_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Set up one time software forced Action qualifier outputs
 *
 *   This function sets up the one time software forced Action Qualifier output
 * on MCPWM A or MCPWMB, depending on the value of mcpwmOutput to a value
 * specified by output.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  mcpwmOutput       This is the MCPWM pin type.
 *
 *  @param[in]  output            This is the action qualifier output.
 *
 */
__STATIC_INLINE void DL_MCPWM_setActionQualifierSWAction(MCPWM_Regs                               *mcpwm,
                                                         DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE   mcpwmOutput,
                                                         DL_MCPWM_ACTION_QUALIFIER_SW_FORCE_OUTPUT output)
{
    switch (mcpwmOutput)
    {
        case DL_MCPWM_AQ_OUTPUT_1A:
            DL_Common_updateReg(&mcpwm->PWM1_AQSFRC, ((uint32_t)output << MCPWM_PWM1_AQSFRC_PWMA_OFS),
                                MCPWM_PWM1_AQSFRC_PWMA_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_1B:
            DL_Common_updateReg(&mcpwm->PWM1_AQSFRC, ((uint32_t)output << MCPWM_PWM1_AQSFRC_PWMB_OFS),
                                MCPWM_PWM1_AQSFRC_PWMB_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_2A:
            DL_Common_updateReg(&mcpwm->PWM2_AQSFRC, ((uint32_t)output << MCPWM_PWM2_AQSFRC_PWMA_OFS),
                                MCPWM_PWM2_AQSFRC_PWMA_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_2B:
            DL_Common_updateReg(&mcpwm->PWM2_AQSFRC, ((uint32_t)output << MCPWM_PWM2_AQSFRC_PWMB_OFS),
                                MCPWM_PWM2_AQSFRC_PWMB_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_3A:
            DL_Common_updateReg(&mcpwm->PWM3_AQSFRC, ((uint32_t)output << MCPWM_PWM3_AQSFRC_PWMA_OFS),
                                MCPWM_PWM3_AQSFRC_PWMA_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_3B:
            DL_Common_updateReg(&mcpwm->PWM3_AQSFRC, ((uint32_t)output << MCPWM_PWM3_AQSFRC_PWMB_OFS),
                                MCPWM_PWM3_AQSFRC_PWMB_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Triggers a one time software forced event on Action qualifier
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  mcpwmOutput    This is the MCPWM pin type.
 *
 */
__STATIC_INLINE void DL_MCPWM_forceActionQualifierSWAction(MCPWM_Regs                             *mcpwm,
                                                           DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE mcpwmOutput)
{
    switch (mcpwmOutput)
    {
        case DL_MCPWM_AQ_OUTPUT_1A:
            mcpwm->PWM1_AQOTSFRC = (mcpwm->PWM1_AQOTSFRC | MCPWM_PWM1_AQOTSFRC_PWMA_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_1B:
            mcpwm->PWM1_AQOTSFRC = (mcpwm->PWM1_AQOTSFRC | MCPWM_PWM1_AQOTSFRC_PWMB_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_2A:
            mcpwm->PWM2_AQOTSFRC = (mcpwm->PWM2_AQOTSFRC | MCPWM_PWM2_AQOTSFRC_PWMA_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_2B:
            mcpwm->PWM2_AQOTSFRC = (mcpwm->PWM2_AQOTSFRC | MCPWM_PWM2_AQOTSFRC_PWMB_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_3A:
            mcpwm->PWM3_AQOTSFRC = (mcpwm->PWM3_AQOTSFRC | MCPWM_PWM3_AQOTSFRC_PWMA_MASK);
            break;
        case DL_MCPWM_AQ_OUTPUT_3B:
            mcpwm->PWM3_AQOTSFRC = (mcpwm->PWM3_AQOTSFRC | MCPWM_PWM3_AQOTSFRC_PWMB_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Sets the Action Qualifier shadow load mode
 *
 * This function enables and sets the Action Qualifier shadow load mode.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  aqModule          This is the Action Qualifier module value.
 *
 *  @param[in]  loadMode          This is the shadow to active load mode.
 */
__STATIC_INLINE void DL_MCPWM_setActionQualifierShadowLoadMode(MCPWM_Regs                         *mcpwm,
                                                               DL_MCPWM_ACTION_QUALIFIER_MODULE    aqModule,
                                                               DL_MCPWM_ACTION_QUALIFIER_LOAD_MODE loadMode)
{
    switch (aqModule)
    {
        case DL_MCPWM_ACTION_QUALIFIER_1A:
            DL_Common_updateReg(&mcpwm->AQCTL, ((uint32_t)loadMode << MCPWM_AQCTL_PWM1_LDAQAMODE_OFS),
                                MCPWM_AQCTL_PWM1_LDAQAMODE_MASK);
            break;
        case DL_MCPWM_ACTION_QUALIFIER_1B:
            DL_Common_updateReg(&mcpwm->AQCTL, ((uint32_t)loadMode << MCPWM_AQCTL_PWM1_LDAQBMODE_OFS),
                                MCPWM_AQCTL_PWM1_LDAQBMODE_MASK);
            break;
        case DL_MCPWM_ACTION_QUALIFIER_2A:
            DL_Common_updateReg(&mcpwm->AQCTL, ((uint32_t)loadMode << MCPWM_AQCTL_PWM2_LDAQAMODE_OFS),
                                MCPWM_AQCTL_PWM2_LDAQAMODE_MASK);
            break;
        case DL_MCPWM_ACTION_QUALIFIER_2B:
            DL_Common_updateReg(&mcpwm->AQCTL, ((uint32_t)loadMode << MCPWM_AQCTL_PWM2_LDAQBMODE_OFS),
                                MCPWM_AQCTL_PWM2_LDAQBMODE_MASK);
            break;
        case DL_MCPWM_ACTION_QUALIFIER_3A:
            DL_Common_updateReg(&mcpwm->AQCTL, ((uint32_t)loadMode << MCPWM_AQCTL_PWM3_LDAQAMODE_OFS),
                                MCPWM_AQCTL_PWM3_LDAQAMODE_MASK);
            break;
        case DL_MCPWM_ACTION_QUALIFIER_3B:
            DL_Common_updateReg(&mcpwm->AQCTL, ((uint32_t)loadMode << MCPWM_AQCTL_PWM3_LDAQBMODE_OFS),
                                MCPWM_AQCTL_PWM3_LDAQBMODE_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Set up Action qualifier outputs
 *
 * This function sets up the Action Qualifier output on DL_MCPWM A or DL_MCPWMB,
 * depending on the value of mcpwmOutput, to a value specified by outPut based
 * on the input events - specified by event.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  mcpwmOutput    This is the DL_MCPWM pin type.
 *
 *  @param[in]  output            This is the Active Action Qualifier output.
 *
 *  @param[in]  event             This is the event that causes a change in output.
 */
__STATIC_INLINE void DL_MCPWM_setActionQualifierActionActive(MCPWM_Regs                             *mcpwm,
                                                             DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE mcpwmOutput,
                                                             DL_MCPWM_ACTION_QUALIFIER_OUTPUT        output,
                                                             DL_MCPWM_ACTION_QUALIFIER_OUTPUT_EVENT  event)
{
    uint32_t mask  = ((uint32_t)0x3U << (uint32_t)event);
    uint32_t value = ((uint32_t)output << (uint32_t)event);

    switch (mcpwmOutput)
    {
        case DL_MCPWM_AQ_OUTPUT_1A:
            mcpwm->PWM1_AQCTLA = (mcpwm->PWM1_AQCTLA & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_1B:
            mcpwm->PWM1_AQCTLB = (mcpwm->PWM1_AQCTLB & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_2A:
            mcpwm->PWM2_AQCTLA = (mcpwm->PWM2_AQCTLA & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_2B:
            mcpwm->PWM2_AQCTLB = (mcpwm->PWM2_AQCTLB & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_3A:
            mcpwm->PWM3_AQCTLA = (mcpwm->PWM3_AQCTLA & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_3B:  // DL_MCPWM_AQ_OUTPUT_3B
            mcpwm->PWM3_AQCTLB = (mcpwm->PWM3_AQCTLB & ~mask) | value;
            break;
        default:
            break;
    }
}

/**
 *  @brief      Set up Action qualifier outputs in Shadow register
 *
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  mcpwmOutput    This is the DL_MCPWM pin type.
 *
 *  @param[in]  output            This is the Active Action Qualifier output.
 *
 *  @param[in]  event             This is the event that causes a change in output.
 */
__STATIC_INLINE void DL_MCPWM_setActionQualifierActionShadow(MCPWM_Regs                             *mcpwm,
                                                             DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE mcpwmOutput,
                                                             DL_MCPWM_ACTION_QUALIFIER_OUTPUT        output,
                                                             DL_MCPWM_ACTION_QUALIFIER_OUTPUT_EVENT  event)
{
    uint32_t mask  = ((uint32_t)0x3U << (uint32_t)event);
    uint32_t value = ((uint32_t)output << (uint32_t)event);

    switch (mcpwmOutput)
    {
        case DL_MCPWM_AQ_OUTPUT_1A:
            mcpwm->PWM1_AQCTLAS = (mcpwm->PWM1_AQCTLAS & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_1B:
            mcpwm->PWM1_AQCTLBS = (mcpwm->PWM1_AQCTLBS & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_2A:
            mcpwm->PWM2_AQCTLAS = (mcpwm->PWM2_AQCTLAS & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_2B:
            mcpwm->PWM2_AQCTLBS = (mcpwm->PWM2_AQCTLBS & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_3A:
            mcpwm->PWM3_AQCTLAS = (mcpwm->PWM3_AQCTLAS & ~mask) | value;
            break;
        case DL_MCPWM_AQ_OUTPUT_3B:  // DL_MCPWM_AQ_OUTPUT_3B
            mcpwm->PWM3_AQCTLBS = (mcpwm->PWM3_AQCTLBS & ~mask) | value;
            break;
        default:
            break;
    }
}

/**
 *  @brief      Set up Action qualifier action for all events in one go
 *
 * This function sets up the Action Qualifier output on DL_MCPWMA or DL_MCPWMB,
 * depending on the value of mcpwmOutput, to a value specified by action.
 * Valid action param values from different time base counter scenarios
 * should be OR'd together to configure complete action for a pwm output.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  mcpwmOutput    This is the DL_MCPWM pin type.
 *
 *  @param[in]  action            This is the desired action when the specified event occurs
 *
 */
__STATIC_INLINE void DL_MCPWM_setActionQualifierActionCompleteActive(
    MCPWM_Regs *mcpwm, DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE mcpwmOutput, uint16_t action)
{
    switch (mcpwmOutput)
    {
        case DL_MCPWM_AQ_OUTPUT_1A:
            mcpwm->PWM1_AQCTLA = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_1B:
            mcpwm->PWM1_AQCTLB = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_2A:
            mcpwm->PWM2_AQCTLA = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_2B:
            mcpwm->PWM2_AQCTLB = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_3A:
            mcpwm->PWM3_AQCTLA = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_3B:
            mcpwm->PWM3_AQCTLB = (uint32_t)action;
            break;
        default:
            break;
    }
}

/**
 *  @brief      Set up Action qualifier action for all events in one go in shadow register
 *
 * This function sets up the Action Qualifier output on DL_MCPWMA or DL_MCPWMB,
 * depending on the value of mcpwmOutput, to a value specified by action.
 * Valid action param values from different time base counter scenarios
 * should be OR'd together to configure complete action for a pwm output.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  mcpwmOutput    This is the DL_MCPWM pin type.
 *
 *  @param[in]  action            This is the desired action when the specified event occurs
 *
 */
__STATIC_INLINE void DL_MCPWM_setActionQualifierActionCompleteShadow(
    MCPWM_Regs *mcpwm, DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE mcpwmOutput, uint16_t action)
{
    switch (mcpwmOutput)
    {
        case DL_MCPWM_AQ_OUTPUT_1A:
            mcpwm->PWM1_AQCTLAS = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_1B:
            mcpwm->PWM1_AQCTLBS = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_2A:
            mcpwm->PWM2_AQCTLAS = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_2B:
            mcpwm->PWM2_AQCTLBS = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_3A:
            mcpwm->PWM3_AQCTLAS = (uint32_t)action;
            break;
        case DL_MCPWM_AQ_OUTPUT_3B:
            mcpwm->PWM3_AQCTLBS = (uint32_t)action;
            break;
        default:
            break;
    }
}

/**
 *  @brief      Enable Global shadow load mode.
 *
 * This function enables Global shadow to active load mode of registers.
 * The trigger source for loading shadow to active is determined by
 * DL_MCPWM_setGlobalLoadTrigger() function.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_enableGlobalLoad(MCPWM_Regs *mcpwm)
{
    mcpwm->GLDCTL |= MCPWM_GLDCTL_GLD_MASK;
}

/**
 *  @brief      Disable Global shadow load mode.
 *
 * This function disables Global shadow to active load mode of registers.
 * Loading shadow to active is determined individually..
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_disableGlobalLoad(MCPWM_Regs *mcpwm)
{
    mcpwm->GLDCTL &= ~MCPWM_GLDCTL_GLD_MASK;
}

/**
 *  @brief      Set the Global shadow load pulse.
 *
 * This function sets the pulse that causes Global shadow to active load.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @param[in]  loadTrigger       This is the pulse that causes global shadow load.
 *
 */
__STATIC_INLINE void DL_MCPWM_setGlobalLoadTrigger(MCPWM_Regs *mcpwm, DL_MCPWM_GLOBAL_LOAD_TRIGGER loadTrigger)
{
    DL_Common_updateReg(&mcpwm->GLDCTL, ((uint32_t)loadTrigger << MCPWM_GLDCTL_GLDMODE_OFS), MCPWM_GLDCTL_GLDMODE_MASK);
}

/**
 *  @brief      Enable One shot global shadow to active load.
 *
 * This function enables a one time global shadow to active load. Register
 * load happens every time the event set by the
 * DL_MCPWM_setGlobalLoadTrigger() occurs.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_enableGlobalLoadOneShotMode(MCPWM_Regs *mcpwm)
{
    mcpwm->GLDCTL |= MCPWM_GLDCTL_OSHTMODE_MASK;
}

/**
 *  @brief      Enable continuous global shadow to active load.
 *
 * This function enables global continuous shadow to active load. Register
 * load happens every time the event set by the
 * DL_MCPWM_setGlobalLoadTrigger() occurs.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_disableGlobalLoadOneShotMode(MCPWM_Regs *mcpwm)
{
    mcpwm->GLDCTL &= ~MCPWM_GLDCTL_OSHTMODE_MASK;
}

/**
 *  @brief      Set One shot global shadow to active load pulse.
 *
 * This function sets a one time global shadow to active load pulse. The pulse
 * propagates to generate a load signal if any of the events set by
 * DL_MCPWM_setGlobalLoadTrigger() occur.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_setGlobalLoadOneShotLatch(MCPWM_Regs *mcpwm)
{
    mcpwm->GLDOSHTCTL |= MCPWM_GLDOSHTCTL_OSHTLD_MASK;
}

/**
 *  @brief      Clears One shot global shadow to active load pulse.
 *
 * This function sets a one time global shadow to active load pulse. The pulse
 * propagates to generate a load signal if any of the events set by
 * DL_MCPWM_setGlobalLoadTrigger() occur.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_clearGlobalLoadOneShotLatch(MCPWM_Regs *mcpwm)
{
    mcpwm->GLDOSHTCTL &= ~MCPWM_GLDOSHTCTL_OSHTLD_MASK;
}

/**
 *  @brief      Get One shot global shadow to active load pulse Status.
 *
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @return     Returns global one shot latch status
 */
__STATIC_INLINE bool DL_MCPWM_getGlobalLoadOneShotLatchStatus(MCPWM_Regs *mcpwm)
{
    bool status = ((mcpwm->GLDOSHTSTS & MCPWM_GLDOSHTSTS_OSHTLATCH_MASK) == MCPWM_GLDOSHTSTS_OSHTLATCH_MASK);

    return (status);
}

/**
 *  @brief      Force a software One shot global shadow to active load pulse.
 *
 * This function forces a software a one time global shadow to active load
 * pulse.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_forceGlobalLoadOneShotEvent(MCPWM_Regs *mcpwm)
{
    mcpwm->GLDOSHTCTL |= MCPWM_GLDOSHTCTL_GFRCLD_MASK;
}

/**
 *  @brief      Sets Dead Band signal output swap mode.
 *
 * This function sets up the output signal swap mode. For example if the
 * output variable is set to DL_MCPWM_DB_OUTPUT_A and enableSwapMode is TRUE, then
 * the DL_MCPWM A output gets its signal from the DL_MCPWM B signal path. Valid values
 * for the input variables are:
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  output            DL_MCPWM Dead Band output.
 *  @param[in]  enableSwapMode    This is the output swap mode.
 *
 */
__STATIC_INLINE void DL_MCPWM_setDeadBandOutputSwapMode(MCPWM_Regs *mcpwm, DL_MCPWM_DEADBAND_OUTPUT output,
                                                        bool enableSwapMode)
{
    uint32_t mask;

    mask = (uint32_t)1U << ((uint32_t)output + MCPWM_DBCTL_OUTSWAP_OFS);

    if (enableSwapMode)
    {
        mcpwm->DBCTL = (mcpwm->DBCTL | mask);
    }
    else
    {
        mcpwm->DBCTL = (mcpwm->DBCTL & ~mask);
    }
}

/**
 *  @brief      Sets Dead Band signal output mode.
 *
 * This function sets up the dead band delay mode. The delayMode variable
 * determines if the applied delay is Rising Edge or Falling Edge. The
 * enableDelayMode determines if a dead band delay should be applied.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  delayMode         This is the Dead Band delay type.
 *  @param[in]  enableDelayMode   This is the dead band delay mode.
 *
 */
__STATIC_INLINE void DL_MCPWM_setDeadBandDelayMode(MCPWM_Regs *mcpwm, DL_MCPWM_DEADBAND_DELAY_MODE delayMode,
                                                   bool enableDelayMode)
{
    uint32_t mask;

    mask = (uint32_t)1U << ((uint32_t)delayMode + MCPWM_DBCTL_OUT_MODE_OFS);

    if (enableDelayMode)
    {
        mcpwm->DBCTL = (mcpwm->DBCTL | mask);
    }
    else
    {
        mcpwm->DBCTL = (mcpwm->DBCTL & ~mask);
    }
}

/**
 *  @brief      Sets Dead Band delay polarity.
 *
 * This function sets up the polarity as determined by the variable polarity
 * of the Falling Edge or Rising Edge delay depending on the value of
 * delayMode.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  delayMode         This is the Dead Band delay type.
 *  @param[in]  polarity          This is the polarity of the delayed signal.
 *
 */
__STATIC_INLINE void DL_MCPWM_setDeadBandDelayPolarity(MCPWM_Regs *mcpwm, DL_MCPWM_DEADBAND_DELAY_MODE delayMode,
                                                       DL_MCPWM_DEADBAND_POLARITY polarity)
{
    uint16_t shift;

    shift = (((uint16_t)delayMode ^ 0x1U) + MCPWM_DBCTL_POLSEL_OFS);
    DL_Common_updateReg(&mcpwm->DBCTL, ((uint32_t)polarity << shift), ((uint32_t)1U << shift));
}

/**
 *  @brief      Sets Rising Edge Dead Band delay input.
 *
 * This function sets up the rising Edge delay input signal.
 * Valid values for input are:
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  input             This is the input signal to the deadband
 *
 */
__STATIC_INLINE void DL_MCPWM_setRisingEdgeDeadBandDelayInput(MCPWM_Regs *mcpwm, uint16_t input)
{
    DL_Common_updateReg(&mcpwm->DBCTL, ((uint32_t)(input << MCPWM_DBCTL_IN_MODE_OFS)),
                        (uint32_t)(1U << (MCPWM_DBCTL_IN_MODE_OFS)));
}

/**
 *  @brief      Sets Dead Band delay input.
 *
 * This function sets up the rising Edge delay input signal.
 * Valid values for input are:
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  input             This is the input signal to the deadband
 *
 */
__STATIC_INLINE void DL_MCPWM_setFallingEdgeDeadBandDelayInput(MCPWM_Regs *mcpwm, uint16_t input)
{
    if (input == DL_MCPWM_DB_INPUT_DB_RED)
    {
        mcpwm->DBCTL |= MCPWM_DBCTL_DEDB_MODE_MASK;
    }
    else
    {
        mcpwm->DBCTL &= ~MCPWM_DBCTL_DEDB_MODE_MASK;
        mcpwm->DBCTL  = ((mcpwm->DBCTL & ~((uint32_t)1U << (MCPWM_DBCTL_IN_MODE_OFS + 1U))) |
                        ((uint32_t)input << (MCPWM_DBCTL_IN_MODE_OFS + 1U)));
    }
}

/**
 *  @brief      Set the RED (Rising Edge Delay) shadow load mode.
 *
 * This function sets the Rising Edge Delay register shadow load mode.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  loadMode          This is the shadow to active load event
 *
 */
__STATIC_INLINE void DL_MCPWM_setRisingEdgeDelayCountShadowLoadMode(MCPWM_Regs                          *mcpwm,
                                                                    DL_MCPWM_RISING_EDGE_DELAY_LOAD_MODE loadMode)
{
    DL_Common_updateReg(&mcpwm->DBCTL, ((uint32_t)loadMode << MCPWM_DBCTL_LOADREDMODE_OFS),
                        MCPWM_DBCTL_LOADREDMODE_MASK);
}

/**
 *  @brief      Set the FED (Falling Edge Delay) shadow load mode.
 *
 * This function sets the Falling Edge Delay register shadow load mode.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  loadMode          This is the shadow to active load event
 *
 */
__STATIC_INLINE void DL_MCPWM_setFallingEdgeDelayCountShadowLoadMode(MCPWM_Regs                           *mcpwm,
                                                                     DL_MCPWM_FALLING_EDGE_DELAY_LOAD_MODE loadMode)
{
    DL_Common_updateReg(&mcpwm->DBCTL, ((uint32_t)loadMode << MCPWM_DBCTL_LOADFEDMODE_OFS),
                        MCPWM_DBCTL_LOADFEDMODE_MASK);
}

/**
 *  @brief      Set DL_MCPWM RED count
 *
 * This function sets the RED (Rising Edge Delay) count value, in the active
 * register.
 * The value of redCount should be less than 0x4000U.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  redCount          This is the RED(Rising Edge Delay) count.
 *
 */
__STATIC_INLINE void DL_MCPWM_setRisingEdgeDelayCountActive(MCPWM_Regs *mcpwm, uint16_t redCount)
{
    DL_Common_updateReg(&mcpwm->DBRED, ((uint32_t)redCount << MCPWM_DBRED_DBRED_OFS), MCPWM_DBRED_DBRED_MASK);
}

/**
 *  @brief      Set DL_MCPWM RED count in shadow register
 *
 * This function sets the RED (Rising Edge Delay) count value,
 * in the shadow register.
 * The value of redCount should be less than 0x4000U.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  redCount          This is the RED(Rising Edge Delay) count.
 *
 */
__STATIC_INLINE void DL_MCPWM_setRisingEdgeDelayCountShadow(MCPWM_Regs *mcpwm, uint16_t redCount)
{
    DL_Common_updateReg(&mcpwm->DBREDS, ((uint32_t)redCount << MCPWM_DBREDS_DBREDS_OFS), MCPWM_DBREDS_DBREDS_MASK);
}

/**
 *  @brief      Set DL_MCPWM FED count
 *
 * This function sets the FED (Falling Edge Delay) count value,
 * in the register.
 * The value of fedCount should be less than 0x4000U.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  fedCount          This is the FED(Falling Edge Delay) count.
 *
 */
__STATIC_INLINE void DL_MCPWM_setFallingEdgeDelayCountActive(MCPWM_Regs *mcpwm, uint16_t fedCount)
{
    DL_Common_updateReg(&mcpwm->DBFED, ((uint32_t)fedCount << MCPWM_DBFED_DBFED_OFS), MCPWM_DBFED_DBFED_MASK);
}

/**
 *  @brief      Set DL_MCPWM FED count in shadow register
 *
 * This function sets the FED (Falling Edge Delay) count value,
 * in the shadow register.
 * The value of fedCount should be less than 0x4000U.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  fedCount          This is the FED(Falling Edge Delay) count.
 *
 */
__STATIC_INLINE void DL_MCPWM_setFallingEdgeDelayCountShadow(MCPWM_Regs *mcpwm, uint16_t fedCount)
{
    DL_Common_updateReg(&mcpwm->DBFEDS, ((uint32_t)fedCount << MCPWM_DBFEDS_DBFEDS_OFS), MCPWM_DBFEDS_DBFEDS_MASK);
}

/**
 *  @brief      Enables Trip Zone signal.
 *
 * This function enables the Trip Zone signals specified by tzSignal as a
 * source for the Trip Zone module.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  tzSignal          This is the Trip Zone signal.
 *
 */
__STATIC_INLINE void DL_MCPWM_enableTripZoneSignals(MCPWM_Regs *mcpwm, uint32_t tzSignal)
{
    mcpwm->TZSEL = (mcpwm->TZSEL | tzSignal);
}

/**
 *  @brief      Disables Trip Zone signal.
 *
 * This function disables the Trip Zone signals specified by tzSignal as a
 * source for the Trip Zone module.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  tzSignal          This is the Trip Zone signal.
 *
 */
__STATIC_INLINE void DL_MCPWM_disableTripZoneSignals(MCPWM_Regs *mcpwm, uint32_t tzSignal)
{
    mcpwm->TZSEL = (mcpwm->TZSEL & ~((uint32_t)tzSignal));
}

/**
 *  @brief      Set Trip Zone Action.
 *
 * This function sets the Trip Zone Action to be taken when a Trip Zone event
 * occurs.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  tzEvent           This is the Trip Zone event type.
 *  @param[in]  tzAction          This is the Trip Zone action.
 *
 */
__STATIC_INLINE void DL_MCPWM_setTripZoneAction(MCPWM_Regs *mcpwm, DL_MCPWM_TRIP_ZONE_EVENT tzEvent,
                                                DL_MCPWM_TRIP_ZONE_ACTION tzAction)
{
    uint32_t mask  = (tzEvent == DL_MCPWM_TZ_ACTION_EVENT_TZA) ? MCPWM_TZCTL_TZA_MASK : MCPWM_TZCTL_TZB_MASK;
    uint32_t shift = (tzEvent == DL_MCPWM_TZ_ACTION_EVENT_TZA) ? MCPWM_TZCTL_TZA_OFS : MCPWM_TZCTL_TZB_OFS;

    DL_Common_updateReg(&mcpwm->TZCTL, ((uint32_t)tzAction << shift), mask);
}

/**
 *  @brief      Set the Trip Zone CBC pulse clear event.
 *
 * This function set the event which automatically clears the
 * CBC (Cycle by Cycle) latch.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  clearEvent        This is the CBC trip zone clear event.
 *
 */
__STATIC_INLINE void DL_MCPWM_selectTripZoneCBCEvent(MCPWM_Regs *mcpwm, DL_MCPWM_TRIP_ZONE_CBC_MODE clearEvent)
{
    DL_Common_updateReg(&mcpwm->TZCTL, ((uint32_t)clearEvent << MCPWM_TZCTL_CBCPULSE_OFS), MCPWM_TZCTL_CBCPULSE_MASK);
}

/**
 *  @brief      Gets the Trip Zone flag status.
 *
 * This function returns the specific Trip Zone flag status.
 * The function returns the following values.
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ1     - CBC 1 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ2     - CBC 2 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ3     - CBC 3 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ4     - CBC 4 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ5     - CBC 5 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ6     - CBC 6 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ7     - CBC 7 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ8     - CBC 8 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ1     - OST 1 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ2     - OST 2 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ3     - OST 3 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ4     - OST 4 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ5     - OST 5 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ6     - OST 6 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ7     - OST 7 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ8     - OST 8 status flag
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @return     Status of all the Trip Zone flags
 *
 *  @retval     Bitwise OR of @ref DL_MCPWM_TZ_SIGNAL values.
 *
 */
__STATIC_INLINE uint32_t DL_MCPWM_getTripZoneFlagStatus(MCPWM_Regs *mcpwm)
{
    uint32_t mask =
        DL_MCPWM_TZ_SIGNAL_CBC1 | DL_MCPWM_TZ_SIGNAL_CBC2 | DL_MCPWM_TZ_SIGNAL_CBC3 | DL_MCPWM_TZ_SIGNAL_CBC4 |
        DL_MCPWM_TZ_SIGNAL_CBC5 | DL_MCPWM_TZ_SIGNAL_CBC6 | DL_MCPWM_TZ_SIGNAL_CBC7 | DL_MCPWM_TZ_SIGNAL_CBC8 |
        DL_MCPWM_TZ_SIGNAL_OSHT1 | DL_MCPWM_TZ_SIGNAL_OSHT2 | DL_MCPWM_TZ_SIGNAL_OSHT3 | DL_MCPWM_TZ_SIGNAL_OSHT4 |
        DL_MCPWM_TZ_SIGNAL_OSHT5 | DL_MCPWM_TZ_SIGNAL_OSHT6 | DL_MCPWM_TZ_SIGNAL_OSHT7 | DL_MCPWM_TZ_SIGNAL_OSHT8;

    return (mcpwm->TZCBCOSTFLAG & mask);
}

/**
 *  @brief      Clear the Trip Zone flag.
 *
 * This function clears the specific Cycle by Cycle Trip Zone flag.
 * The following are valid values for tzFlags.
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ1     - CBC 1 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ2     - CBC 2 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ3     - CBC 3 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ4     - CBC 4 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ5     - CBC 5 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ6     - CBC 6 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ7     - CBC 7 status flag
 *           - DL_MCPWM_TZ_FLAG_CBC_TZ8     - CBC 8 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ1     - OST 1 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ2     - OST 2 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ3     - OST 3 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ4     - OST 4 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ5     - OST 5 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ6     - OST 6 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ7     - OST 7 status flag
 *           - DL_MCPWM_TZ_FLAG_OST_TZ8     - OST 8 status flag
 *           - DL_MCPWM_TZ_FLAG_ALL         - All Trip Zone Flags
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  tzFlags           This is the CBC flag to be cleared.
 *
 */
__STATIC_INLINE void DL_MCPWM_clearTripZoneFlagStatus(MCPWM_Regs *mcpwm, uint32_t tzFlags)
{
    mcpwm->TZCBCOSTCLR |= tzFlags;
}

/**
 *  @brief      Enable ADC SOC event.
 *
 * This function enables the MCPWM module to trigger an ADC SOC event.
 * Valid values for adcSOCType are:
 *   - DL_MCPWM_SOC_A  - SOC A
 *   - DL_MCPWM_SOC_B  - SOC B
 *   - DL_MCPWM_SOC_C  - SOC C
 *   - DL_MCPWM_SOC_D  - SOC D
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  adcSOCType        This is the ADC SOC type.
 *
 */
__STATIC_INLINE void DL_MCPWM_enableADCTrigger(MCPWM_Regs *mcpwm, DL_MCPWM_SOC_TYPE adcSOCType)
{
    switch (adcSOCType)
    {
        case DL_MCPWM_SOC_A:
            mcpwm->SOCEN |= MCPWM_SOCEN_SOCA_ENABLE_MASK;
            break;
        case DL_MCPWM_SOC_B:
            mcpwm->SOCEN |= MCPWM_SOCEN_SOCB_ENABLE_MASK;
            break;
        case DL_MCPWM_SOC_C:
            mcpwm->SOCEN |= MCPWM_SOCEN_SOCC_ENABLE_MASK;
            break;
        case DL_MCPWM_SOC_D:
            mcpwm->SOCEN |= MCPWM_SOCEN_SOCD_ENABLE_MASK;
            break;
        default:
            break;
    }
}

/**
 *  @brief      Disable ADC SOC event.
 *
 * This function enables the MCPWM module to trigger an ADC SOC event.
 * Valid values for adcSOCType are:
 *   - DL_MCPWM_SOC_A  - SOC A
 *   - DL_MCPWM_SOC_B  - SOC B
 *   - DL_MCPWM_SOC_C  - SOC C
 *   - DL_MCPWM_SOC_D  - SOC D
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  adcSOCType        This is the ADC SOC type.
 *
 */
__STATIC_INLINE void DL_MCPWM_disableADCTrigger(MCPWM_Regs *mcpwm, DL_MCPWM_SOC_TYPE adcSOCType)
{
    switch (adcSOCType)
    {
        case DL_MCPWM_SOC_A:
            mcpwm->SOCEN &= ~((uint32_t)MCPWM_SOCEN_SOCA_ENABLE_MASK);
            break;
        case DL_MCPWM_SOC_B:
            mcpwm->SOCEN &= ~((uint32_t)MCPWM_SOCEN_SOCB_ENABLE_MASK);
            break;
        case DL_MCPWM_SOC_C:
            mcpwm->SOCEN &= ~((uint32_t)MCPWM_SOCEN_SOCC_ENABLE_MASK);
            break;
        case DL_MCPWM_SOC_D:
            mcpwm->SOCEN &= ~((uint32_t)MCPWM_SOCEN_SOCD_ENABLE_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Sets the DL_MCPWM SOC source.
 *
 * This function sets the MCPWM ADC SOC source.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  adcSOCType        This is the ADC SOC type.
 *  @param[in]  socSource         This is the SOC source.
 *
 */
__STATIC_INLINE void DL_MCPWM_setADCTriggerSource(MCPWM_Regs *mcpwm, DL_MCPWM_SOC_TYPE adcSOCType,
                                                  DL_MCPWM_SOC_SOURCE socSource)
{
    switch (adcSOCType)
    {
        case DL_MCPWM_SOC_A:
            DL_Common_updateReg(&mcpwm->SOCSEL, ((uint32_t)socSource << MCPWM_SOCSEL_SOCA_SEL_OFS),
                                MCPWM_SOCSEL_SOCA_SEL_MASK);
            break;
        case DL_MCPWM_SOC_B:
            DL_Common_updateReg(&mcpwm->SOCSEL, ((uint32_t)socSource << MCPWM_SOCSEL_SOCB_SEL_OFS),
                                MCPWM_SOCSEL_SOCB_SEL_MASK);
            break;
        case DL_MCPWM_SOC_C:
            DL_Common_updateReg(&mcpwm->SOCSEL, ((uint32_t)socSource << MCPWM_SOCSEL_SOCC_SEL_OFS),
                                MCPWM_SOCSEL_SOCC_SEL_MASK);
            break;
        case DL_MCPWM_SOC_D:
            DL_Common_updateReg(&mcpwm->SOCSEL, ((uint32_t)socSource << MCPWM_SOCSEL_SOCD_SEL_OFS),
                                MCPWM_SOCSEL_SOCD_SEL_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Sets the DL_MCPWM SOC event counts.
 *
 * This function sets the SOC event count that determines the number of
 * events that have to occur before an SOC is issued.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  adcSOCType        This is the ADC SOC type.
 *  @param[in]  preScaleCount     This is the event count number.
 *
 */
__STATIC_INLINE void DL_MCPWM_setADCTriggerEventPrescale(MCPWM_Regs *mcpwm, DL_MCPWM_SOC_TYPE adcSOCType,
                                                         uint16_t preScaleCount)
{
    switch (adcSOCType)
    {
        case DL_MCPWM_SOC_A:
            DL_Common_updateReg(&mcpwm->SOCPERIOD, ((uint32_t)preScaleCount << MCPWM_SOCPERIOD_SOCA_PERIOD_OFS),
                                MCPWM_SOCPERIOD_SOCA_PERIOD_MASK);
            break;
        case DL_MCPWM_SOC_B:
            DL_Common_updateReg(&mcpwm->SOCPERIOD, ((uint32_t)preScaleCount << MCPWM_SOCPERIOD_SOCB_PERIOD_OFS),
                                MCPWM_SOCPERIOD_SOCB_PERIOD_MASK);
            break;
        case DL_MCPWM_SOC_C:
            DL_Common_updateReg(&mcpwm->SOCPERIOD, ((uint32_t)preScaleCount << MCPWM_SOCPERIOD_SOCC_PERIOD_OFS),
                                MCPWM_SOCPERIOD_SOCC_PERIOD_MASK);
            break;
        case DL_MCPWM_SOC_D:
            DL_Common_updateReg(&mcpwm->SOCPERIOD, ((uint32_t)preScaleCount << MCPWM_SOCPERIOD_SOCD_PERIOD_OFS),
                                MCPWM_SOCPERIOD_SOCD_PERIOD_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Get the SOC event count.
 *
 * This function returns the MCPWM SOC event count.
 * Valid values for adcSOCType are:
 *     - DL_MCPWM_SOC_A  - SOC A
 *     - DL_MCPWM_SOC_B  - SOC B
 *     - DL_MCPWM_SOC_C  - SOC C
 *     - DL_MCPWM_SOC_D  - SOC D
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  adcSOCType        This is the ADC SOC type.
 *
 *  @return     The occurences of selected events for each SOC.
 *
 */
__STATIC_INLINE uint16_t DL_MCPWM_getADCTriggerEventCount(MCPWM_Regs *mcpwm, DL_MCPWM_SOC_TYPE adcSOCType)
{
    uint16_t retValue = 0;

    switch (adcSOCType)
    {
        case DL_MCPWM_SOC_A:
            retValue = (uint16_t)((mcpwm->SOCCNT & MCPWM_SOCCNT_SOCA_CNT_MASK) >> MCPWM_SOCCNT_SOCA_CNT_OFS);
            break;
        case DL_MCPWM_SOC_B:
            retValue = (uint16_t)((mcpwm->SOCCNT & MCPWM_SOCCNT_SOCB_CNT_MASK) >> MCPWM_SOCCNT_SOCB_CNT_OFS);
            break;
        case DL_MCPWM_SOC_C:
            retValue = (uint16_t)((mcpwm->SOCCNT & MCPWM_SOCCNT_SOCC_CNT_MASK) >> MCPWM_SOCCNT_SOCC_CNT_OFS);
            break;
        case DL_MCPWM_SOC_D:
            retValue = (uint16_t)((mcpwm->SOCCNT & MCPWM_SOCCNT_SOCD_CNT_MASK) >> MCPWM_SOCCNT_SOCD_CNT_OFS);
            break;
        default:
            break;
    }

    return retValue;
}

/**
 *  @brief      Return the SOC event status.
 *
 * This function returns the MCPWM SOC event count.
 * Valid values for adcSOCType are:
 *     - DL_MCPWM_SOC_A  - SOC A
 *     - DL_MCPWM_SOC_B  - SOC B
 *     - DL_MCPWM_SOC_C  - SOC C
 *     - DL_MCPWM_SOC_D  - SOC D
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  adcSOCType        This is the ADC SOC type.
 *
 *  @return     The status of each SOC status flags.
 *
 * @return true if start of conversion pulse was generated on SOC.
 * @return false if no event has occurred.
 */
__STATIC_INLINE bool DL_MCPWM_getADCTriggerFlagStatus(MCPWM_Regs *mcpwm, DL_MCPWM_SOC_TYPE adcSOCType)
{
    bool retValue = false;

    switch (adcSOCType)
    {
        case DL_MCPWM_SOC_A:
            retValue = ((mcpwm->SOCFLAG & MCPWM_SOCFLAG_SOCA_MASK) == MCPWM_SOCFLAG_SOCA_MASK);
            break;
        case DL_MCPWM_SOC_B:
            retValue = ((mcpwm->SOCFLAG & MCPWM_SOCFLAG_SOCB_MASK) == MCPWM_SOCFLAG_SOCB_MASK);
            break;
        case DL_MCPWM_SOC_C:
            retValue = ((mcpwm->SOCFLAG & MCPWM_SOCFLAG_SOCC_MASK) == MCPWM_SOCFLAG_SOCC_MASK);
            break;
        case DL_MCPWM_SOC_D:  // DL_MCPWM_SOC_D
            retValue = ((mcpwm->SOCFLAG & MCPWM_SOCFLAG_SOCD_MASK) == MCPWM_SOCFLAG_SOCD_MASK);
            break;
        default:
            break;
    }

    return retValue;
}

/**
 *  @brief      Clear SOC flag.
 *
 * This function clears the MCPWM SOC flag.
 * Valid values for adcSOCType are:
 *     - DL_MCPWM_SOC_A  - SOC A
 *     - DL_MCPWM_SOC_B  - SOC B
 *     - DL_MCPWM_SOC_C  - SOC C
 *     - DL_MCPWM_SOC_D  - SOC D
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  adcSOCType        This is the ADC SOC type.
 *
 */
__STATIC_INLINE void DL_MCPWM_clearADCTriggerFlag(MCPWM_Regs *mcpwm, DL_MCPWM_SOC_TYPE adcSOCType)
{
    switch (adcSOCType)
    {
        case DL_MCPWM_SOC_A:
            mcpwm->SOCCLR |= MCPWM_SOCCLR_SOCA_MASK;
            break;
        case DL_MCPWM_SOC_B:
            mcpwm->SOCCLR |= MCPWM_SOCCLR_SOCB_MASK;
            break;
        case DL_MCPWM_SOC_C:
            mcpwm->SOCCLR |= MCPWM_SOCCLR_SOCC_MASK;
            break;
        case DL_MCPWM_SOC_D:  // DL_MCPWM_SOC_D
            mcpwm->SOCCLR |= MCPWM_SOCCLR_SOCD_MASK;
            break;
        default:
            break;
    }
}

/**
 *  @brief      Sets the DL_MCPWM Event Trigger source.
 *
 * This function sets the MCPWM Event Trigger source.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  evtTrigType       This is the Event Trigger type.
 *  @param[in]  evtTrigSource     This is the EVT source.
 *
 */
__STATIC_INLINE void DL_MCPWM_setEventTriggerSource(MCPWM_Regs *mcpwm, DL_MCPWM_EVENT_TRIGGER_TYPE evtTrigType,
                                                    DL_MCPWM_EVENT_TRIGGER_SOURCE evtTrigSource)
{
    switch (evtTrigType)
    {
        case DL_MCPWM_ET_1:
            DL_Common_updateReg(&mcpwm->ETSEL, ((uint32_t)evtTrigSource << MCPWM_ETSEL_ET1_SEL_OFS),
                                MCPWM_ETSEL_ET1_SEL_MASK);
            break;
        case DL_MCPWM_ET_2:  // DL_MCPWM_ET_2
            DL_Common_updateReg(&mcpwm->ETSEL, ((uint32_t)evtTrigSource << MCPWM_ETSEL_ET2_SEL_OFS),
                                MCPWM_ETSEL_ET2_SEL_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Sets the MCPWM Event Trigger event counts.
 *
 * This function sets the event trigger count that determines the number of
 * events that have to occur before an event trigger is issued.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  evtTrigType       This is the Event Trigger type.
 *  @param[in]  preScaleCount     This is the event count number.
 *
 */
__STATIC_INLINE void DL_MCPWM_setEventTriggerEventPrescale(MCPWM_Regs *mcpwm, DL_MCPWM_EVENT_TRIGGER_TYPE evtTrigType,
                                                           uint16_t preScaleCount)
{
    switch (evtTrigType)
    {
        case DL_MCPWM_ET_1:
            DL_Common_updateReg(&mcpwm->ETPERIOD, ((uint32_t)preScaleCount << MCPWM_ETPERIOD_ET1_PERIOD_OFS),
                                MCPWM_ETPERIOD_ET1_PERIOD_MASK);
            break;
        case DL_MCPWM_ET_2:  // DL_MCPWM_ET_2
            DL_Common_updateReg(&mcpwm->ETPERIOD, ((uint32_t)preScaleCount << MCPWM_ETPERIOD_ET2_PERIOD_OFS),
                                MCPWM_ETPERIOD_ET2_PERIOD_MASK);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Get the Event Trigger event count.
 *
 * This function returns the MCPWM Event trigger event count.
 * Valid values for evtTrigType are:
 *  - evtTrigType
 *     - DL_MCPWM_ET_1  - EVT 1
 *     - DL_MCPWM_ET_2  - EVT 2
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  evtTrigType       This is the Event Trigger type.
 *
 *  @return     The number of occurences of each event trigger.
 */
__STATIC_INLINE uint16_t DL_MCPWM_getEventTriggerEventCount(MCPWM_Regs *mcpwm, DL_MCPWM_EVENT_TRIGGER_TYPE evtTrigType)
{
    uint16_t retValue = 0;

    switch (evtTrigType)
    {
        case DL_MCPWM_ET_1:
            retValue = (uint16_t)((mcpwm->ETCNT & MCPWM_ETCNT_ET1_CNT_MASK) >> MCPWM_ETCNT_ET1_CNT_OFS);
            break;
        case DL_MCPWM_ET_2:  // DL_MCPWM_ET_2
            retValue = (uint16_t)((mcpwm->ETCNT & MCPWM_ETCNT_ET2_CNT_MASK) >> MCPWM_ETCNT_ET2_CNT_OFS);
            break;
        default:
            break;
    }

    return retValue;
}

/**
 *  @brief      Enables interrupt source.
 *
 * This function sets and enables MCPWM interrupt source. The following are
 * valid interrupt sources.
 *  - DL_MCPWM_INT_TZ_CBC - Interrupt Source is Trip Zone CBC signal
 *  - DL_MCPWM_INT_TZ_OST - Interrupt Source is Trip Zone OST signal
 *  - DL_MCPWM_INT_ET_1   - Interrupt Source is Event Trigger 1 signal
 *  - DL_MCPWM_INT_ET_2   - Interrupt Source is Event Trigger 2 signal
 *  - DL_MCPWM_INT_TBCTR_OVF - Counter overflow generates interrupt
 *  - DL_MCPWM_INT_SOURCE_ALL - All Interrupt Sources
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  intFlags          This is the interrupt source to be enabled.
 *
 */
__STATIC_INLINE void DL_MCPWM_enableInterrupt(MCPWM_Regs *mcpwm, uint16_t intFlags)
{
    mcpwm->INTEN |= intFlags;
}

/**
 *  @brief      Disables interrupt source.
 *
 * This function sets and enables MCPWM interrupt source. The following are
 * valid interrupt sources.
 *  - DL_MCPWM_INT_TZ_CBC - Interrupt Source is Trip Zone CBC signal
 *  - DL_MCPWM_INT_TZ_OST - Interrupt Source is Trip Zone OST signal
 *  - DL_MCPWM_INT_ET_1   - Interrupt Source is Event Trigger 1 signal
 *  - DL_MCPWM_INT_ET_2   - Interrupt Source is Event Trigger 2 signal
 *  - DL_MCPWM_INT_TBCTR_OVF - Counter overflow generates interrupt
 *  - DL_MCPWM_INT_SOURCE_ALL - All Interrupt Sources
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  intFlags          This is the interrupt source to be enabled.
 *
 */
__STATIC_INLINE void DL_MCPWM_disableInterrupt(MCPWM_Regs *mcpwm, uint16_t intFlags)
{
    mcpwm->INTEN &= ~intFlags;
}

/**
 *  @brief      Returns the interrupt flag.
 *
 * This function returns the MCPWM interrupt flag. The following are valid
 * interrupt sources corresponding to the MCPWM interrupt flag.
 * Returns the MCPWM interrupt that has occurred. The following are
 * valid return values.
 *  - DL_MCPWM_INT_TZ_CBC   - Interrupt Source is Trip Zone CBC signal
 *  - DL_MCPWM_INT_TZ_OST   - Interrupt Source is Trip Zone OST signal
 *  - DL_MCPWM_INT_ET_1     - Interrupt Source is Event Trigger 1 signal
 *  - DL_MCPWM_INT_ET_2     - Interrupt Source is Event Trigger 2 signal
 *  - DL_MCPWM_INT_TBCTR_OVF  - Counter overflow generates interrupt
 *  - DL_MCPWM_INT_SOURCE_ALL - All Interrupt Sources
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @return     Returns the status of each MCPWM interrupt.
 */
__STATIC_INLINE uint16_t DL_MCPWM_getInterruptSource(MCPWM_Regs *mcpwm)
{
    return (mcpwm->INTFLAG & DL_MCPWM_INT_SOURCE_ALL);
}

/**
 *  @brief      Returns the Global interrupt flag.
 *
 * This function returns the DL_MCPWM Global interrupt flag.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 *  @return     The status of the global interrupt flag.
 */
__STATIC_INLINE bool DL_MCPWM_getGlobalInterruptStatus(MCPWM_Regs *mcpwm)
{
    return ((mcpwm->INTFLAG & MCPWM_INTFLAG_INT_MASK) == MCPWM_INTFLAG_INT_MASK);
}

/**
 *  @brief      Clears interrupt flag.
 *
 * This function clears MCPWM interrupt flags. The following are valid
 * interrupt sources.
 *  - DL_MCPWM_INT_TZ_CBC - Interrupt Source is Trip Zone CBC signal
 *  - DL_MCPWM_INT_TZ_OST - Interrupt Source is Trip Zone OST signal
 *  - DL_MCPWM_INT_ET_1   - Interrupt Source is Event Trigger 1 signal
 *  - DL_MCPWM_INT_ET_2   - Interrupt Source is Event Trigger 2 signal
 *  - DL_MCPWM_INT_TBCTR_OVF - Counter overflow generates interrupt
 *  - DL_MCPWM_INT_SOURCE_ALL   - All Interrupt Sources-
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  intFlags          This is the interrupt source.
 *
 */
__STATIC_INLINE void DL_MCPWM_clearInterrupt(MCPWM_Regs *mcpwm, uint16_t intFlags)
{
    mcpwm->INTCLR = intFlags;
}

/**
 *  @brief      Clears global interrupt flag.
 *
 * This function clears the global interrupt bit.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *
 */
__STATIC_INLINE void DL_MCPWM_clearGlobalInterrupt(MCPWM_Regs *mcpwm)
{
    mcpwm->INTCLR = MCPWM_INTFLAG_INT_MASK;
}

/**
 *  @brief      Forces interrupt source.
 *
 * This function forces and enables MCPWM interrupt source. The following are
 * valid interrupt sources.
 *  - DL_MCPWM_INT_TZ_CBC - Interrupt Source is Trip Zone CBC signal
 *  - DL_MCPWM_INT_TZ_OST - Interrupt Source is Trip Zone OST signal
 *  - DL_MCPWM_INT_ET_1   - Interrupt Source is Event Trigger 1 signal
 *  - DL_MCPWM_INT_ET_2   - Interrupt Source is Event Trigger 2 signal
 *  - DL_MCPWM_INT_TBCTR_OVF - Counter overflow generates interrupt
 *  - DL_MCPWM_INT_SOURCE_ALL   - All Interrupt Sources-
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  intFlags          This is the interrupt source.
 *
 */
__STATIC_INLINE void DL_MCPWM_forceInterrupt(MCPWM_Regs *mcpwm, uint16_t intFlags)
{
    mcpwm->INTFRC = intFlags;
}

/**
 *  @brief      Enables TBCLK for MCPWM
 *
 * This function enables TBCLK for MCPWM.
 *
 */

__STATIC_INLINE void DL_MCPWM_enableTBCLK(void)
{
    SYSCTL->SOCLOCK.PERCLKCR = (SYSCTL->SOCLOCK.PERCLKCR | SYSCTL_PERCLKCR_TBCLKSYNC_MASK);
}

/**
 *  @brief      Disables TBCLK for MCPWM
 *
 * This function disables TBCLK for MCPWM.
 *
 */

__STATIC_INLINE void DL_MCPWM_disableTBCLK(void)
{
    SYSCTL->SOCLOCK.PERCLKCR = (SYSCTL->SOCLOCK.PERCLKCR & ~SYSCTL_PERCLKCR_TBCLKSYNC_MASK);
}
/**
 *  @brief      Set emulation mode
 *
 * This function sets the emulation behaviours of the time base counter. Valid
 * values for emulationMode are:
 * - DL_MCPWM_EMULATION_STOP_AFTER_NEXT_TB    - Stop after next Time Base counter
 *                                           increment or decrement.
 * - DL_MCPWM_EMULATION_STOP_AFTER_FULL_CYCLE - Stop when counter completes whole
 *                                           cycle.
 * - DL_MCPWM_EMULATION_FREE_RUN               - Free run.
 *
 *  @param[in]  mcpwm             Pointer to the register overlay for the peripheral.
 *  @param[in]  emulationMode     This is the emulation mode.
 *
 */
void DL_MCPWM_setEmulationMode(MCPWM_Regs *mcpwm, DL_MCPWM_EMULATION_MODE emulationMode);

/**
 * @brief Initializes the MCPWM configuration parameters.
 *
 * This function initializes all the parameters of the MCPWM configuration
 * structure to their default values.
 *
 * @param[in,out] config Pointer to the MCPWM configuration structure.
 */

void DL_MCPWM_initParamsSetDefault(DL_MCPWM_Config *config);

/**
 * @brief Initializes the MCPWM module
 *
 * This function configures the MCPWM module according to the provided configuration.
 *
 * @param mcpwm Pointer to the MCPWM register overlay
 * @param config Pointer to the MCPWM configuration structure
 */
void DL_MCPWM_init(MCPWM_Regs *mcpwm, DL_MCPWM_Config *config);

/**
 * @brief Configures the MCPWM time base.
 *
 * This function sets up the time base submodule of the MCPWM module according to the provided configuration.
 *
 * @param[in] mcpwm         Pointer to the MCPWM register overlay.
 * @param[in] timeBaseConfig Pointer to the time base configuration structure.
 */
void DL_MCPWM_configureTimeBase(MCPWM_Regs *mcpwm, DL_MCPWM_TimeBaseConfig *timeBaseConfig);

/**
 * @brief Configures the MCPWM counter compare.
 *
 * This function sets up the counter compare submodule of the MCPWM according to the provided configuration.
 *
 * @param[in] mcpwm             Pointer to the MCPWM register overlay.
 * @param[in] counterCompareConfig Pointer to the counter compare configuration structure.
 */
void DL_MCPWM_configureCounterCompare(MCPWM_Regs *mcpwm, DL_MCPWM_CounterCompareConfig *counterCompareConfig);

/**
 * @brief Configures the MCPWM action qualifier actions.
 *
 * This function sets up the actions in the action qualifier submodule of the MCPWM according to the provided
 * configuration.
 *
 * @param[in] mcpwm             Pointer to the MCPWM register overlay.
 * @param[in] output            Action qualifier output module @ref DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE
 * @param[in] aqPwm             Pointer to @ref DL_MCPWM_Actions structure
 */
void DL_MCPWM_configureActionQualifierActions(MCPWM_Regs *mcpwm, DL_MCPWM_ACTION_QUALIFIER_OUTPUT_MODULE output,
                                              DL_MCPWM_Actions *aqPwm);

/**
 * @brief Configures the MCPWM dead-band.
 *
 * This function sets up the dead-band submodule of the MCPWM according to the provided configuration.
 *
 * @param[in] mcpwm         Pointer to the MCPWM register overlay.
 * @param[in] deadBandConfig Pointer to the dead-band configuration structure.
 */
void DL_MCPWM_configureDeadBand(MCPWM_Regs *mcpwm, DL_MCPWM_DeadBandConfig *deadBandConfig);

/**
 * @brief Configures the MCPWM trip zone.
 *
 * This function sets up the trip zone submodule of the MCPWM according to the provided configuration.
 *
 * @param[in] mcpwm Pointer to the MCPWM register overlay.
 * @param[in] config Pointer to the trip zone configuration structure.
 */
void DL_MCPWM_configureTripZone(MCPWM_Regs *mcpwm, DL_MCPWM_TripZoneConfig *config);

/**
 * @brief Configures the MCPWM event trigger.
 *
 * This function sets up the event trigger submodule of the MCPWM according to the provided configuration.
 *
 * @param[in] mcpwm             Pointer to the MCPWM register overlay.
 * @param[in] eventTriggerConfig Pointer to the event trigger configuration structure.
 */
void DL_MCPWM_configureEventTrigger(MCPWM_Regs *mcpwm, DL_MCPWM_EventTriggerConfig *eventTriggerConfig);

/**
 * @brief Configures the MCPWM load modes.
 *
 * This function sets up the global load feature of the MCPWM according to the provided configuration.
 *
 * @param[in] mcpwm         Pointer to the MCPWM register overlay.
 * @param[in] loadModeConfig Pointer to the load mode configuration structure.
 */
void DL_MCPWM_configureLoadMode(MCPWM_Regs *mcpwm, DL_MCPWM_LoadModeConfig *loadModeConfig);

#ifdef __cplusplus
}
#endif

#endif /* DL_MCPWM_H */
       /** @}*/
