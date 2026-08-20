
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

/**
 * @defgroup DL_EQEP_AM13E230X  Driverlib EQEP API
 * @ingroup DL_AM13E230X
 *
 *@{
 */

#ifndef DL_EQEP_H
#define DL_EQEP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "soc.h"
#include "dl_common.h"
#include "hw_eqep.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 * @name    DL_EQEP_OPEARTION_MODE
 * @anchor  DL_EQEP_OPEARTION_MODE
 * @{
 */
/*!
 * @brief Quadrature-clock mode
 */
#define DL_EQEP_CONFIG_QUADRATURE EQEP_QDECCTL_QSRC_QUAD_COUNT_MODE
/*!
 * @brief Direction-count mode
 */
#define DL_EQEP_CONFIG_CLOCK_DIR  EQEP_QDECCTL_QSRC_DIRECT_COUNT_MODE
/*!
 * @brief Up-count mode, QDIR = 1
 */
#define DL_EQEP_CONFIG_UP_COUNT   EQEP_QDECCTL_QSRC_UP_COUNT_MODE
/*!
 * @brief Down-count mode, QDIR = 0
 */
#define DL_EQEP_CONFIG_DOWN_COUNT EQEP_QDECCTL_QSRC_DOWN_COUNT_MODE
/** @}*/

/**
 * @name    DL_EQEP_RESOLUTION
 * @anchor  DL_EQEP_RESOLUTION
 * @{
 */
/*!
 * @brief Count rising and falling edge
 */
#define DL_EQEP_CONFIG_2X_RESOLUTION EQEP_QDECCTL_XCR_XCR_2XRESOL
/*!
 * @brief Count rising edge only
 */
#define DL_EQEP_CONFIG_1X_RESOLUTION EQEP_QDECCTL_XCR_XCR_1XRESOL
/** @}*/

/**
 * @name    DL_EQEP_SWAP
 * @anchor  DL_EQEP_SWAP
 * @brief   Swap QEPA and QEPB
 * @{
 */
/*!
 * @brief Do not swap QEPA and QEPB
 */
#define DL_EQEP_CONFIG_NO_SWAP EQEP_QDECCTL_SWAP_SWAP_DISABLE
/*!
 * @brief Swap QEPA and QEPB
 */
#define DL_EQEP_CONFIG_SWAP    EQEP_QDECCTL_SWAP_SWAP_ENABLE
/** @}*/

/**
 * @name    DL_EQEP_IGATE
 * @anchor  DL_EQEP_IGATE
 * @brief   Index pulse gating option
 * @{
 */
/*!
 * @brief Disable gating of Index pulse
 */
#define DL_EQEP_CONFIG_IGATE_DISABLE EQEP_QDECCTL_IGATE_IGATE_DISABLE
/*!
 * @brief Gate the index pin with strobe
 */
#define DL_EQEP_CONFIG_IGATE_ENABLE  EQEP_QDECCTL_IGATE_IGATE_ENABLE
/** @}*/

/**
 * @name    DL_EQEP_SYNCOUT
 * @anchor  DL_EQEP_SYNCOUT
 * @{
 */
/*!
 * @brief Disable sync output
 */
#define DL_EQEP_COMPARE_NO_SYNC_OUT     EQEP_QDECCTL_SOEN_SYNC_DISABLE
/*!
 * @brief Sync output on index pin
 */
#define DL_EQEP_COMPARE_IDX_SYNC_OUT    (EQEP_QDECCTL_SOEN_SYNC_ENABLE | EQEP_QDECCTL_SPSEL_INDEX_PIN)
/*!
 * @brief Sync output on strobe pin
 */
#define DL_EQEP_COMPARE_STROBE_SYNC_OUT (EQEP_QDECCTL_SOEN_SYNC_ENABLE | EQEP_QDECCTL_SPSEL_STROBE_PIN)
/** @}*/

/**
 * Shadow register use
 */
/*!
 * @brief Disable shadow of QPOSCMP
 */
#define DL_EQEP_COMPARE_NO_SHADOW     EQEP_QPOSCTL_PCSHDW_PCSHDW_DISABLE
/*!
 * @brief Load on QPOSCNT = 0
 */
#define DL_EQEP_COMPARE_LOAD_ON_ZERO  (EQEP_QPOSCTL_PCSHDW_PCSHDW_ENABLE | EQEP_QPOSCTL_PCLOAD_PCLOAD_0)
/*!
 * @brief Load on QPOSCNT = QPOSCMP
 */
#define DL_EQEP_COMPARE_LOAD_ON_MATCH (EQEP_QPOSCTL_PCSHDW_PCSHDW_ENABLE | EQEP_QPOSCTL_PCLOAD_PCLOAD_QPOSCMP)

/**
 * @name  DL_EQEP_INT
 * @anchor DL_EQEP_INT
 * @{
 */
/*!
 * @brief Global interrupt
 */
#define DL_EQEP_INT_GLOBAL            0x0001U
/*!
 * @brief Position counter error interrupt
 */
#define DL_EQEP_INT_POS_CNT_ERROR     0x0002U
/*!
 * @brief Quadrature phase error interrupt
 */
#define DL_EQEP_INT_PHASE_ERROR       0x0004U
/*!
 * @brief Quadrature direction change interrupt
 */
#define DL_EQEP_INT_DIR_CHANGE        0x0008U
/*!
 * @brief Watchdog time-out interrupt
 */
#define DL_EQEP_INT_WATCHDOG          0x0010U
/*!
 * @brief Position counter underflow interrupt
 */
#define DL_EQEP_INT_UNDERFLOW         0x0020U
/*!
 * @brief Position counter overflow interrupt
 */
#define DL_EQEP_INT_OVERFLOW          0x0040U
/*!
 * @brief Position-compare ready interrupt
 */
#define DL_EQEP_INT_POS_COMP_READY    0x0080U
/*!
 * @brief Position-compare match interrupt
 */
#define DL_EQEP_INT_POS_COMP_MATCH    0x0100U
/*!
 * @brief Strobe event latch interrupt
 */
#define DL_EQEP_INT_STROBE_EVNT_LATCH 0x0200U
/*!
 * @brief Index event latch interrupt
 */
#define DL_EQEP_INT_INDEX_EVNT_LATCH  0x0400U
/*!
 * @brief Unit time-out interrupt
 */
#define DL_EQEP_INT_UNIT_TIME_OUT     0x0800U
/*!
 * @brief QMA error interrupt
 */
#define DL_EQEP_INT_QMA_ERROR         0x1000U
/** @} */

/**
 * @name  DL_EQEP_STS
 * @anchor DL_EQEP_STS
 * @{
 */
/*!
 * @brief Unit position event status
 */
#define DL_EQEP_STS_UNIT_POS_EVNT    EQEP_QEPSTS_UPEVNT_UPEVNT_DETCT
/*!
 * @brief Direction was clockwise on first index event
 */
#define DL_EQEP_STS_DIR_ON_1ST_IDX   EQEP_QEPSTS_FIDF_FIDF_CLK
/*!
 * @brief CW (forward) Direction status
 */
#define DL_EQEP_STS_DIR_FLAG         EQEP_QEPSTS_QDF_QDF_CLK
/*!
 * @brief Direction was CW on last index event marker
 */
#define DL_EQEP_STS_DIR_LATCH        EQEP_QEPSTS_QDLF_QDLF_CLK
/*!
 * @brief Capture timer overflow status
 */
#define DL_EQEP_STS_CAP_OVRFLW_ERROR EQEP_QEPSTS_COEF_COEF_OVF
/*!
 * @brief Direction change between position capture events status
 */
#define DL_EQEP_STS_CAP_DIR_ERROR    EQEP_QEPSTS_CDEF_CDEF_DIRECT
/*!
 * @brief First index pulse status
 */
#define DL_EQEP_STS_1ST_IDX_FLAG     EQEP_QEPSTS_FIMF_FIMF_SETINDEX
/*!
 * @brief Position counter error status
 */
#define DL_EQEP_STS_POS_CNT_ERROR    EQEP_QEPSTS_PCEF_PCEF_ERROR
/** @} */

/**
 * @name  DL_EQEP_LATCH_MODE
 * @anchor DL_EQEP_LATCH_MODE
 * @{
 */
/*! @brief Latch on position counter read */
#define DL_EQEP_LATCH_CNT_READ_BY_CPU EQEP_QEPCTL_QCLM_QCLM_CPU
/*! @brief Latch on unit time-out event */
#define DL_EQEP_LATCH_UNIT_TIME_OUT   EQEP_QEPCTL_QCLM_QCLM_TIMEOUT
/*! @brief Latch on rising edge of strobe */
#define DL_EQEP_LATCH_RISING_STROBE   EQEP_QEPCTL_SEL_SEL_QEPSRISING
/*! @brief Latch on rising edge when clockwise, on falling when counter clockwise */
#define DL_EQEP_LATCH_EDGE_DIR_STROBE EQEP_QEPCTL_SEL_SEL_QEPSCLOCK
/*! @brief Latch on rising edge of index */
#define DL_EQEP_LATCH_RISING_INDEX    EQEP_QEPCTL_IEL_IEL_POSRISING
/*! @brief Latch on falling edge of index */
#define DL_EQEP_LATCH_FALLING_INDEX   EQEP_QEPCTL_IEL_IEL_POSFALLING
/*! @brief Latch on software index marker */
#define DL_EQEP_LATCH_SW_INDEX_MARKER EQEP_QEPCTL_IEL_IEL_SIM
/** @} */

/**
 * @name  DL_EQEP_INIT_MODE
 * @anchor  DL_EQEP_INIT_MODE
 * @{
 */
/*! @brief Action is disabled */
#define DL_EQEP_INIT_DO_NOTHING      0x0000U
/*! @brief Initialize on rising edge of strobe */
#define DL_EQEP_INIT_RISING_STROBE   EQEP_QEPCTL_SEI_SEI_INITQEPSRISING
/*! @brief Initialize on rising edge when clockwise, on falling when counter clockwise */
#define DL_EQEP_INIT_EDGE_DIR_STROBE EQEP_QEPCTL_SEI_SEI_INITQEPSCLOCK
/*! @brief Initialize on rising edge of index */
#define DL_EQEP_INIT_RISING_INDEX    EQEP_QEPCTL_IEI_IEI_INITRISING
/*! @brief Initialize on falling edge of index */
#define DL_EQEP_INIT_FALLING_INDEX   EQEP_QEPCTL_IEI_IEI_INITFALLING
/** @} */

/**
 * @brief Position counter reset mode
 */
typedef enum
{
    /*! Reset position counter on an index event */
    DL_EQEP_POSITION_RESET_IDX           = EQEP_QEPCTL_PCRM_PCRM_INDEX,
    /*! Reset position counter on the maximum position */
    DL_EQEP_POSITION_RESET_MAX_POS       = EQEP_QEPCTL_PCRM_PCRM_MAXPOS,
    /*! Reset position counter on the first index event */
    DL_EQEP_POSITION_RESET_1ST_INDEX     = EQEP_QEPCTL_PCRM_PCRM_FIRSTINDEX,
    /*! Reset position counter on a unit time event */
    DL_EQEP_POSITION_RESET_UNIT_TIME_OUT = EQEP_QEPCTL_PCRM_PCRM_TIMEEVENT
} DL_EQEP_POSITION_RESET_MODE;

/**
 * @brief EQEP capture timer clock prescaler
 */
typedef enum
{
    /*! CAPCLK = SYSCLKOUT/1 */
    DL_EQEP_CAPTURE_CLK_DIV_1   = EQEP_QCAPCTL_CCPS_SYSCLKOUT1,
    /*! CAPCLK = SYSCLKOUT/2 */
    DL_EQEP_CAPTURE_CLK_DIV_2   = EQEP_QCAPCTL_CCPS_SYSCLKOUT2,
    /*! CAPCLK = SYSCLKOUT/4 */
    DL_EQEP_CAPTURE_CLK_DIV_4   = EQEP_QCAPCTL_CCPS_SYSCLKOUT4,
    /*! CAPCLK = SYSCLKOUT/8 */
    DL_EQEP_CAPTURE_CLK_DIV_8   = EQEP_QCAPCTL_CCPS_SYSCLKOUT8,
    /*! CAPCLK = SYSCLKOUT/16 */
    DL_EQEP_CAPTURE_CLK_DIV_16  = EQEP_QCAPCTL_CCPS_SYSCLKOUT16,
    /*! CAPCLK = SYSCLKOUT/32 */
    DL_EQEP_CAPTURE_CLK_DIV_32  = EQEP_QCAPCTL_CCPS_SYSCLKOUT32,
    /*! CAPCLK = SYSCLKOUT/64 */
    DL_EQEP_CAPTURE_CLK_DIV_64  = EQEP_QCAPCTL_CCPS_SYSCLKOUT64,
    /*! CAPCLK = SYSCLKOUT/128 */
    DL_EQEP_CAPTURE_CLK_DIV_128 = EQEP_QCAPCTL_CCPS_SYSCLKOUT128
} DL_EQEP_CAP_CLK_PRESCALE;

/**
 * @brief EQEP unit position event prescaler
 */
typedef enum
{
    /*! UPEVNT = QCLK/1 */
    DL_EQEP_UNIT_POS_EVNT_DIV_1    = EQEP_QCAPCTL_UPPS_QCLK1,
    /*! UPEVNT = QCLK/2 */
    DL_EQEP_UNIT_POS_EVNT_DIV_2    = EQEP_QCAPCTL_UPPS_QCLK2,
    /*! UPEVNT = QCLK/4 */
    DL_EQEP_UNIT_POS_EVNT_DIV_4    = EQEP_QCAPCTL_UPPS_QCLK4,
    /*! UPEVNT = QCLK/8 */
    DL_EQEP_UNIT_POS_EVNT_DIV_8    = EQEP_QCAPCTL_UPPS_QCLK8,
    /*! UPEVNT = QCLK/16 */
    DL_EQEP_UNIT_POS_EVNT_DIV_16   = EQEP_QCAPCTL_UPPS_QCLK16,
    /*! UPEVNT = QCLK/32 */
    DL_EQEP_UNIT_POS_EVNT_DIV_32   = EQEP_QCAPCTL_UPPS_QCLK32,
    /*! UPEVNT = QCLK/64 */
    DL_EQEP_UNIT_POS_EVNT_DIV_64   = EQEP_QCAPCTL_UPPS_QCLK64,
    /*! UPEVNT = QCLK/128 */
    DL_EQEP_UNIT_POS_EVNT_DIV_128  = EQEP_QCAPCTL_UPPS_QCLK128,
    /*! UPEVNT = QCLK/256 */
    DL_EQEP_UNIT_POS_EVNT_DIV_256  = EQEP_QCAPCTL_UPPS_QCLK256,
    /*! UPEVNT = QCLK/512 */
    DL_EQEP_UNIT_POS_EVNT_DIV_512  = EQEP_QCAPCTL_UPPS_QCLK512,
    /*! UPEVNT = QCLK/1024 */
    DL_EQEP_UNIT_POS_EVNT_DIV_1024 = EQEP_QCAPCTL_UPPS_QCLK1024,
    /*! UPEVNT = QCLK/2048 */
    DL_EQEP_UNIT_POS_EVNT_DIV_2048 = EQEP_QCAPCTL_UPPS_QCLK2048
} DL_EQEP_UPEVNT_PRESCALE;

/**
 * @brief EQEP strobe source
 */
typedef enum
{
    /*! GPIO */
    DL_EQEP_STROBE_FROM_GPIO  = EQEP_QEPSTROBESEL_STROBESEL_QS_AFTER_POL_MUX,
    /*! Strobe signal OR'd with ADCSOCA */
    DL_EQEP_STROBE_OR_ADCSOCA = EQEP_QEPSTROBESEL_STROBESEL_ADCSOCA_AS_QS,
    /*! Strobe signal OR'd with ADCSOCB */
    DL_EQEP_STROBE_OR_ADCSOCB = EQEP_QEPSTROBESEL_STROBESEL_ADCSOCB_AS_QS
} DL_EQEP_STROBE_SOURCE;

/**
 * @brief EQEP QMA modes
 */
typedef enum
{
    /*! QMA module is bypassed */
    DL_EQEP_QMA_MODE_BYPASS = 0U,
    /*! QMA mode-1 operation */
    DL_EQEP_QMA_MODE_1      = 1U,
    /*! QMA mode-2 operation */
    DL_EQEP_QMA_MODE_2      = 2U
} DL_EQEP_QMA_MODE;

/**
 * @brief EQEP emulation mode
 */
typedef enum
{
    /*! Counters stop immediately on emulation suspend */
    DL_EQEP_EMULATIONMODE_STOPIMMEDIATELY = EQEP_QEPCTL_FREE_SOFT_FREE_SOFT_0,
    /*! Counters stop at period rollover on emulation suspend */
    DL_EQEP_EMULATIONMODE_STOPATROLLOVER  = EQEP_QEPCTL_FREE_SOFT_FREE_SOFT_1,
    /*! Counters unaffected by emulation suspend */
    DL_EQEP_EMULATIONMODE_RUNFREE         = EQEP_QEPCTL_FREE_SOFT_FREE_SOFT_2
} DL_EQEP_EMULATION_MODE;

/**
 * @brief EQEP source selection
 */
typedef enum
{
    /*! Signal comes from INPUTXBAR */
    DL_EQEP_SOURCE_INPUTXBAR     = 0,
    /*! Signal comes from CMPSS0_CTRIPH */
    DL_EQEP_SOURCE_CMPSS0_CTRIPH = 1,
    /*! Signal comes from CMPSS1_CTRIPH */
    DL_EQEP_SOURCE_CMPSS1_CTRIPH = 2,
    /*! Signal comes from CMPSS2_CTRIPH */
    DL_EQEP_SOURCE_CMPSS2_CTRIPH = 3,
    /*! Signal comes from CMPSS3_CTRIPH */
    DL_EQEP_SOURCE_CMPSS3_CTRIPH = 4,
    /*! Signal comes from PWMXBAR1 */
    DL_EQEP_SOURCE_PWMXBAR1      = 5,
    /*! Signal comes from PWMXBAR2 */
    DL_EQEP_SOURCE_PWMXBAR2      = 6,
    /*! Signal comes from PWMXBAR3 */
    DL_EQEP_SOURCE_PWMXBAR3      = 7,
    /*! Signal comes from PWMXBAR4 */
    DL_EQEP_SOURCE_PWMXBAR4      = 8,
    /*! Signal comes from PWMXBAR5 */
    DL_EQEP_SOURCE_PWMXBAR5      = 9,
    /*! Signal comes from PWMXBAR6 */
    DL_EQEP_SOURCE_PWMXBAR6      = 10,
    /*! Signal comes from PWMXBAR7 */
    DL_EQEP_SOURCE_PWMXBAR7      = 11,
    /*! Signal comes from PWMXBAR8 */
    DL_EQEP_SOURCE_PWMXBAR8      = 12,
} DL_EQEP_SOURCE;

/**
 * @brief Structure containing source configurations for QEP signals
 */
typedef struct
{
    /*! Source for QEPA signal */
    DL_EQEP_SOURCE sourceA;
    /*! Source for QEPB signal */
    DL_EQEP_SOURCE sourceB;
    /*! Source for Index signal */
    DL_EQEP_SOURCE sourceIndex;
} DL_EQEP_SOURCE_SELECT;

/**
 * @brief EQEP Input configuration structure
 */
typedef struct
{
    /*! Select QEPA source.
        Configures QEPSRCSEL.QEPASEL
        @ref DL_EQEP_SOURCE
    */
    DL_EQEP_SOURCE        qepASrc;
    /*! Select QEPB source.
        Configures QEPSRCSEL.QEPBSEL
        @ref DL_EQEP_SOURCE
    */
    DL_EQEP_SOURCE        qepBSrc;
    /*! Select QEP Index source.
        Configures QEPSRCSEL.QEPISEL
        @ref DL_EQEP_SOURCE
    */
    DL_EQEP_SOURCE        qepIndexSrc;
    /*! Select QEP Strobe. Configures QEPSTROBESEL.STROBESEL
        - Note: QEP Strobe source (QEPSRCSEL.QEPSSEL) left to default (0 - from device pins)
        - Valid values: @ref DL_EQEP_STROBE_SOURCE
    */
    DL_EQEP_STROBE_SOURCE qepStrobeSrc;
} DL_EQEP_InputConfig;

/**
 * @brief EQEP QMA configuration structure
 */
typedef struct
{
    /*! Mode select for QMA mode. Configures QMACTRL.MODE
        Valid values: @ref DL_EQEP_QMA_MODE
    */
    DL_EQEP_QMA_MODE qmaMode;
} DL_EQEP_QmaConfig;

/**
 * @brief EQEP QDU configuration structure
 */
typedef struct
{
    /*! Enable direction change during Index event. Configures QDECCTL.QIDIRE */
    bool     enableDirectionChangeDuringIndex;
    /*! Flag to negate the QEPA input. Configures QDECCTL.QAP
        - true: Negate QEPA input
        - false: Do not negate QEPA input
    */
    bool     invertQEPA;
    /*! Flag to negate the QEPB input. Configures QDECCTL.QBP
        - true: Negate QEPB input
        - false: Do not negate QEPB input
    */
    bool     invertQEPB;
    /*! Flag to negate the index input. Configures QDECCTL.QIP
        - true: Negate index input
        - false: Do not negate index input
    */
    bool     invertIndex;
    /*! Flag to negate the strobe input. Configures QDECCTL.QSP
        - true: Negate strobe input
        - false: Do not negate strobe input
    */
    bool     invertStrobe;
    /*! Select position counter source. Specify whether
        - quadrature signals are being provided on QEPA and QEPB,
        - if a direction signal and a clock are being provided or
        - if the direction should be hard-wired for a single direction with QEPA used for input.

        Configures QDECCTL.QSRC
        - Valid values: @ref DL_EQEP_OPEARTION_MODE*/
    uint16_t positionCounterSource;
    /*! Configures QDECCTL.XCR
        @ref DL_EQEP_RESOLUTION
        Specify if both rising and falling edges should be counted or just rising edges.
    */
    uint16_t externalClockRate;
    /*! Specify whether the signals provided on QEPA and QEPB should be swapped before being processed.
        - Configures QDECCTL.SWAP
        - Valid values: @ref DL_EQEP_SWAP
    */
    uint16_t swap;
    /*! Specify whether the gating of the index pulse should be enabled or disabled.
        - Configures QDECCTL.IGATE
        - Valid values: @ref DL_EQEP_IGATE
    */
    uint16_t indexGate;
} DL_EQEP_QduConfig;

/**
 * @brief EQEP Position Latch configuration structure
 */
typedef struct
{
    /*! Latch mode. Select to latch on CPU read or Unit Timeout
        Configures QEPCTL.QCLM
        - Valid values: @ref DL_EQEP_LATCH_MODE
    */
    uint32_t latchModeConfig;
    /*! Strobe event latch configuration.
        Latch on rising edge of strobe. Or latch on rising edge of strobe when in clockwise direction or on falling edge
       of strobe when in counter-clockwise direction Configures QEPCTL.SEL
        - Valid values: @ref DL_EQEP_LATCH_MODE
    */
    uint32_t strobeEventLatchConfig;
    /*! Index event latch configuration.
        Latch on rising edge of Index. Or latch on falling edge of index. Or latch the position counter and quadradure
       direction flag on index event marker. Configures QEPCTL.IEL
        - Valid values: @ref DL_EQEP_LATCH_MODE
    */
    uint32_t indexEventLatchConfig;
} DL_EQEP_PositionLatchConfig;

/**
 * @brief EQEP Position Initialization configuration structure
 */
typedef struct
{
    /*! Strobe event initialization of position counter and Index event
        initialization of position counter
        Configures QEPCTL.SEI, QEPCTL.IEI
        - Valid values: @ref DL_EQEP_INIT_MODE
    */
    uint16_t initMode;
    /*! Position value to initiaize the position counter based on external strobe or index event. Configures
     * QPOSINIT.QPOSINIT
     */
    uint32_t initialPositionCount;
    /*! Perform Software initialization of position counter.
        Writes to QEPCTL.SWI
        - false = No action
        - true = Perform software initialization of position counter (QPOSCNT=QPOSINIT)
    */
    bool     swInitializePositionCounter;
} DL_EQEP_PositionInitializationConfig;

/**
 * @brief EQEP Position Compare configuration structure
 */
typedef struct
{
    /*! Position compare value. Configures QPOSCMP.QPOSCMP
        Value to which the position count value is compared
    */
    uint32_t positionCompareValue;
    /*! Enable Position Compare. Configures QPOSCTL.PCE */
    bool     enablePositionCompare;
    /*! Enable/Disable shadow load and select load event
        Configures QPOSCTL.PCSHDW, QPOSCTL.PCLOAD
        - Valid values: DL_EQEP_COMPARE_NO_SHADOW, DL_EQEP_COMPARE_LOAD_ON_ZERO, DL_EQEP_COMPARE_LOAD_ON_MATCH
    */
    uint16_t shadowLoadConfig;
    /*! Enable Sync Out and select Sync Output pin.
        Configures QDECCTL.SPSEL, QDECCTL.SOEN
        - Valid values: @ref DL_EQEP_SYNCOUT
    */
    uint16_t syncOutConfig;
    /*! Select polarity of sync output.
        Configures QPOSCTL.PCPOL
        - true: Active low
        - false: Active high
    */
    bool     syncOutPolarity;
    /*! Width of the pulse that can be generated on a position-compare event.
        Configures QPOSCTL.PCSPW
        - Valid values:  Units of 4 SYSCLKOUT cycles. The maximum width is 4096 * 4 * SYSCLKOUT cycles.
    */
    uint16_t syncOutPulseWidthcycles;
} DL_EQEP_PositionCompareConfig;

/**
 * @brief EQEP PCCU configuration structure
 */
typedef struct
{
    /*! Position counter reset mode that determines which event
         will reset the position counter.
        Configures QEPCTL.PCRM
        - Valid values: @ref DL_EQEP_POSITION_RESET_MODE
    */
    DL_EQEP_POSITION_RESET_MODE          positionCounterResetMode;
    /*! Maximum position count. Configures QPOSMAX.QPOSMAX
        - Maximum position value used to reset the position counter when moving in the reverse direction
    */
    uint32_t                             maxPositionCount;
    /*! Sets current encoder position count. This value is
        written to QPOSCNT.QPOSCNT when position counter is disabled
    */
    uint32_t                             positionCount;
    /*! Position latch configuration structure */
    DL_EQEP_PositionLatchConfig          positionLatchConfig;
    /*! Position initialization configuration structure */
    DL_EQEP_PositionInitializationConfig positionInitializationConfig;
    /*! Quadrature position counter enable/software reset.
        Configures QEPCTL.QPEN
        - false: Reset the eQEP peripheral internal operating flags/readonly
registers. Control/configuration registers are not disturbed by a
software reset. When QPEN is disabled, some flags in the QFLG register do not get
reset or cleared and show the actual state of that flag.
        - true: eQEP position counter is enabled
    */
    bool                                 enablePositionCounterOrReset;
    /*! Position compare configuration structure */
    DL_EQEP_PositionCompareConfig        positionCompareConfig;
} DL_EQEP_PccuConfig;

/**
 * @brief EQEP UTIME configuration structure
 */
typedef struct
{
    /*! Enable Unit Timer. Configures QEPCTL.UTE. Runs QUTMR.QUTMR
        - true: Enables the Unit Timer after configuring the Unit Time 'period'
        - false: Disables Unit Timer. Does not configure the 'period'
    */
    bool     enable;
    /*! QEP Unit Period. Configures QUPRD.QUPRD */
    uint32_t unitPeriod;
} DL_EQEP_UtimeConfig;

/**
 * @brief EQEP QCAP configuration structure
 */
typedef struct
{
    /*! Enable the EQEP Edge-Capture unit. Configures QCAPCTL.CEN */
    bool                     enableCapture;
    /*! Prescaler setting of the eQEP capture timer clock. Configures QCAPCTL.CCPS
        - Valid values: @ref DL_EQEP_CAP_CLK_PRESCALE
    */
    DL_EQEP_CAP_CLK_PRESCALE capPrescale;
    /*! Prescaler setting of the unit position event frequency. Configures QCAPCTL.UPPS
        - Valid values: @ref DL_EQEP_UPEVNT_PRESCALE
    */
    DL_EQEP_UPEVNT_PRESCALE  evntPrescale;
    /*! UTIME configuration */
    DL_EQEP_UtimeConfig      utimeConfig;
} DL_EQEP_QcapConfig;

/**
 * @brief EQEP QWDOG configuration structure
 */
typedef struct
{
    /*! Enable Watchdog. Configures QEPCTL.WDE
        - true: Enables the Watchdog timer after configuring the watchdog 'period'
        - false: Disables watchdog. Does not configure the 'period'
    */
    bool     enable;
    /*! Inital Value of QEP Watchdog Timer. Configures QWDTMR.QWDTMR */
    uint32_t initialTimerValue;
    /*! Watchdog Timer Period when enabled. Configures QWDPRD.QWDPRD */
    uint16_t period;
} DL_EQEP_QwdogConfig;

/**
 * @brief EQEP Interrupt configuration structure
 */
typedef struct
{
    /*! QEP Interrupt Control. Configures QEINT.PCE, QPE,
        QDC, WTO, PCU, PCO, PCR, PCM , SEL, IEL, UTO, QMAE
        @ref DL_EQEP_INT
    */
    uint16_t intFlags;
} DL_EQEP_InterruptConfig;

/**
 * @brief EQEP configuration structure
 */
typedef struct
{
    /*! Emulation mode. Configures QEPCTL.FREE_SOFT
        - Valid values: @ref DL_EQEP_EMULATION_MODE
    */
    DL_EQEP_EMULATION_MODE  emulationMode;
    /*! Input configuration */
    DL_EQEP_InputConfig     inputConfig;
    /*! QMA configuration */
    DL_EQEP_QmaConfig       qmaConfig;
    /*! QDU configuration */
    DL_EQEP_QduConfig       qduConfig;
    /*! PCCU configuration */
    DL_EQEP_PccuConfig      pccuConfig;
    /*! QCAP configuration */
    DL_EQEP_QcapConfig      qcapConfig;
    /*! QWDOG configuration */
    DL_EQEP_QwdogConfig     qwdogConfig;
    /*! Interrupt configuration */
    DL_EQEP_InterruptConfig interruptConfig;
} DL_EQEP_Config;

/**
 * @brief Enables the eQEP module
 *
 * This API enables operation of the enhanced quadrature encoder pulse (eQEP)
 * module. The module must be configured before it is enabled.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_enableModule(EQEP_Regs *eqep)
{
    eqep->QEPCTL |= EQEP_QEPCTL_QPEN_MASK;
}

/**
 * @brief Disables the eQEP module
 *
 * This API disables operation of the enhanced quadrature encoder pulse (eQEP)
 * module.
 *
 * @param[in] eqep      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_disableModule(EQEP_Regs *eqep)
{
    eqep->QEPCTL &= ~EQEP_QEPCTL_QPEN_MASK;
}

/**
 * @brief Configures eQEP module's quadrature decoder unit
 *
 * This API configures the operation of the eQEP module's quadrature decoder unit.
 * The \e config parameter provides the configuration of the decoder and
 * is the logical OR of several values:
 *
 * - \b DL_EQEP_CONFIG_2X_RESOLUTION or \b DL_EQEP_CONFIG_1X_RESOLUTION specify
 *   if both rising and falling edges should be counted or just rising edges.
 * - \b DL_EQEP_CONFIG_QUADRATURE, \b DL_EQEP_CONFIG_CLOCK_DIR,
 *   \b DL_EQEP_CONFIG_UP_COUNT, or \b DL_EQEP_CONFIG_DOWN_COUNT specify if
 *   quadrature signals are being provided on QEPA and QEPB, if a direction
 *   signal and a clock are being provided, or if the direction should be
 *   hard-wired for a single direction with QEPA used for input.
 * - \b DL_EQEP_CONFIG_NO_SWAP or \b DL_EQEP_CONFIG_SWAP to specify if the
 *   signals provided on QEPA and QEPB should be swapped before being
 *   processed.
 * - \b DL_EQEP_CONFIG_IGATE_DISABLE or \b DL_EQEP_CONFIG_IGATE_ENABLE to specify
 *   if the gating of the index pulse should be enabled or disabled
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] config         Configuration for the eQEP module decoder unit. Logical OR of bit masks @ref
 * DL_EQEP_RESOLUTION, @ref DL_EQEP_OPEARTION_MODE, @ref DL_EQEP_SWAP, @ref DL_EQEP_IGATE
 */
__STATIC_INLINE void DL_EQEP_setDecoderConfig(EQEP_Regs *eqep, uint16_t config)
{
    eqep->QDECCTL = (eqep->QDECCTL & ~(EQEP_QDECCTL_SWAP_MASK | EQEP_QDECCTL_XCR_MASK | EQEP_QDECCTL_QSRC_MASK |
                                       EQEP_QDECCTL_IGATE_MASK)) |
                    config;
}

/**
 * @brief Configures eQEP position counter unit
 *
 * This API configures the operation of the eQEP position counter.
 * The reset mode specifies the event on which the position counter is reset.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] mode           Position counter reset mode that determines which event
 *                           will reset the position counter
 * @param[in] maxPosition    Maximum position value used to reset the position
 *                           counter when moving in the reverse direction
 */
__STATIC_INLINE void DL_EQEP_setPositionCounterConfig(EQEP_Regs *eqep, DL_EQEP_POSITION_RESET_MODE mode,
                                                      uint32_t maxPosition)
{
    eqep->QEPCTL  = (eqep->QEPCTL & ~(EQEP_QEPCTL_PCRM_MASK)) | mode;
    eqep->QPOSMAX = maxPosition;
}

/**
 * @brief Gets the current encoder position
 *
 * This API returns the current position of the encoder. Depending upon
 * the configuration of the encoder and the occurrence of an index pulse, this
 * value may or may not contain the expected data (that is, if in reset on
 * index mode and an index pulse has not been encountered, the position
 * counter is not yet aligned with the index pulse).
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The current position of the encoder
 */
__STATIC_INLINE uint32_t DL_EQEP_getPosition(EQEP_Regs *eqep)
{
    return eqep->QPOSCNT;
}

/**
 * @brief Sets the current encoder position
 *
 * This API sets the current position of the encoder. The encoder
 * position is then measured relative to this value.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] position       is the new position value for the encoder
 */
__STATIC_INLINE void DL_EQEP_setPosition(EQEP_Regs *eqep, uint32_t position)
{
    eqep->QPOSCNT = position;
}

/**
 * @brief Gets the current direction of rotation
 *
 * This API returns the current direction of rotation. In this case,
 * current means the most recently detected direction of the encoder; it may
 * not be presently moving but this is the direction it last moved before it
 * stopped.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return Returns 1 if moving in the forward/clockwise direction or -1 if moving
 *         in the reverse/counter-clockwise direction
 */
__STATIC_INLINE int16_t DL_EQEP_getDirection(EQEP_Regs *eqep)
{
    if ((eqep->QEPSTS & EQEP_QEPSTS_QDF_MASK) != 0U)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

/**
 * @brief Enables individual eQEP interrupts
 *
 * This API enables the specified eQEP interrupts.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] intFlags       Bit mask of the interrupt sources to be enabled.
 *                           The parameter can be any of the following values:
 *                           @ref DL_EQEP_INT except \b DL_EQEP_INT_GLOBAL
 */
__STATIC_INLINE void DL_EQEP_enableInterrupt(EQEP_Regs *eqep, uint16_t intFlags)
{
    eqep->QEINT |= intFlags;
}

/**
 * @brief Disables individual eQEP interrupts
 *
 * This API disables the specified eQEP interrupts.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] intFlags       Bit mask of the interrupt sources to be disabled.
 *                           The parameter can be any of the following values:
 *                           @ref DL_EQEP_INT except \b DL_EQEP_INT_GLOBAL
 */
__STATIC_INLINE void DL_EQEP_disableInterrupt(EQEP_Regs *eqep, uint16_t intFlags)
{
    eqep->QEINT &= ~intFlags;
}

/**
 * @brief Returns the current interrupt status
 *
 * This API returns the interrupt status for the eQEP module.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return Returns the current interrupt status, enumerated as a bit field of
 *         values defined in @ref DL_EQEP_INT
 */
__STATIC_INLINE uint16_t DL_EQEP_getInterruptStatus(EQEP_Regs *eqep)
{
    return eqep->QFLG;
}

/**
 * @brief Clears eQEP interrupt sources.
 *
 * This API clears eQEP interrupt flags.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] intFlags       Bit mask of the interrupt sources to be cleared.
 *                           The parameter can be any of the following values OR'd together:
 *                           @ref DL_EQEP_INT
 *
 * @note The DL_EQEP_INT_GLOBAL value is the global interrupt flag. In order to get
 *       any further eQEP interrupts, this flag must be cleared.
 */
__STATIC_INLINE void DL_EQEP_clearInterruptStatus(EQEP_Regs *eqep, uint16_t intFlags)
{
    eqep->QCLR = intFlags;
}

/**
 * @brief Forces individual eQEP module interrupts
 *
 * This API forces eQEP module interrupt flags.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] intFlags       Bit mask of the interrupt sources to be forced.
 *                           The parameter can be any of the following values OR'd together:
 *                           @ref DL_EQEP_INT except \b DL_EQEP_INT_GLOBAL
 */
__STATIC_INLINE void DL_EQEP_forceInterrupt(EQEP_Regs *eqep, uint16_t intFlags)
{
    eqep->QFRC = intFlags;
}

/**
 * @brief Returns the encoder error indicator
 *
 * This API returns the error indicator for the eQEP module.  It is an error
 * for both of the signals of the quadrature input to change at the same time.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return Returns true if an error has occurred and false otherwise
 */
__STATIC_INLINE bool DL_EQEP_getError(EQEP_Regs *eqep)
{
    return ((eqep->QFLG & EQEP_QFLG_PHE_MASK) == EQEP_QFLG_PHE_PHE_FLAG);
}

/**
 * @brief Returns the eQEP module status register content
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return Returns the value of the QEP status register @ref DL_EQEP_STS
 */
__STATIC_INLINE uint16_t DL_EQEP_getStatus(EQEP_Regs *eqep)
{
    return (eqep->QEPSTS & 0x00FFU);
}

/**
 * @brief Clears selected fields of the eQEP module status register
 *
 * This API clears the status register fields indicated by statusFlags.
 * Only certain status fields can be cleared. All others are read-only,
 * non-sticky fields.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] statusFlags    Bit mask of the status flags to be cleared.
 *                           The parameter can be any of the following values OR'd together:
 *                           - DL_EQEP_STS_UNIT_POS_EVNT - Unit position event detected
 *                           - DL_EQEP_STS_CAP_OVRFLW_ERROR - Overflow occurred in eQEP capture timer
 *                           - DL_EQEP_STS_CAP_DIR_ERROR - Direction change occurred between position capture events
 *                           - DL_EQEP_STS_1ST_IDX_FLAG - Set by the occurrence of the first index pulse
 */
__STATIC_INLINE void DL_EQEP_clearStatus(EQEP_Regs *eqep, uint16_t statusFlags)
{
    eqep->QEPSTS = statusFlags;
}

/**
 * @brief Configures eQEP module edge-capture unit
 *
 * This API configures the operation of the eQEP module edge-capture unit.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] capPrescale    Prescaler setting of the eQEP capture timer clock
 * @param[in] evntPrescale   Prescaler setting of the unit position event frequency
 */
__STATIC_INLINE void DL_EQEP_setCaptureConfig(EQEP_Regs *eqep, DL_EQEP_CAP_CLK_PRESCALE capPrescale,
                                              DL_EQEP_UPEVNT_PRESCALE evntPrescale)
{
    eqep->QCAPCTL = (eqep->QCAPCTL & ~(EQEP_QCAPCTL_UPPS_MASK | EQEP_QCAPCTL_CCPS_MASK)) |
                    ((uint16_t)evntPrescale | (uint16_t)capPrescale);
}

/**
 * @brief Enables the eQEP module edge-capture unit
 *
 * This API enables operation of the eQEP module's edge-capture unit.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_enableCapture(EQEP_Regs *eqep)
{
    eqep->QCAPCTL |= EQEP_QCAPCTL_CEN_MASK;
}

/**
 * @brief Disables the eQEP module edge-capture unit
 *
 * This API disables operation of the eQEP module's edge-capture unit.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_disableCapture(EQEP_Regs *eqep)
{
    eqep->QCAPCTL &= ~EQEP_QCAPCTL_CEN_MASK;
}

/**
 * @brief Gets the encoder capture period
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The period count value between the last successive position events
 */
__STATIC_INLINE uint16_t DL_EQEP_getCapturePeriod(EQEP_Regs *eqep)
{
    return eqep->QCPRD;
}

/**
 * @brief Gets the encoder capture timer value
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The capture timer value
 */
__STATIC_INLINE uint16_t DL_EQEP_getCaptureTimer(EQEP_Regs *eqep)
{
    return eqep->QCTMR;
}

/**
 * @brief Enables the eQEP module position-compare unit
 *
 * This API enables operation of the eQEP module's position-compare unit.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_enableCompare(EQEP_Regs *eqep)
{
    eqep->QPOSCTL |= EQEP_QPOSCTL_PCE_MASK;
}

/**
 * @brief Disables the eQEP module position-compare unit
 *
 * This API disables operation of the eQEP module's position-compare unit.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_disableCompare(EQEP_Regs *eqep)
{
    eqep->QPOSCTL &= ~EQEP_QPOSCTL_PCE_MASK;
}

/**
 * @brief Configures the position-compare unit's sync output pulse width
 *
 * This API configures the width of the sync output pulse. The width of the pulse
 * will be cycles * 4 * the width of a SYSCLKOUT cycle. The maximum width is
 * 4096 * 4 * SYSCLKOUT cycles.
 *
 * @param[in] eqep    Pointer to the register overlay for the peripheral
 * @param[in] cycles  The width of the pulse that can be generated on a position-compare
 *                    event. It is in units of 4 SYSCLKOUT cycles.
 */
__STATIC_INLINE void DL_EQEP_setComparePulseWidth(EQEP_Regs *eqep, uint16_t cycles)
{
    ASSERT(cycles <= (EQEP_QPOSCTL_PCSPW_MASK + 1U));

    eqep->QPOSCTL = (eqep->QPOSCTL & ~EQEP_QPOSCTL_PCSPW_MASK) | (cycles - 1U);
}

/**
 * @brief Loads the eQEP module unit timer period as number of SYSCLK cycles
 *
 * This API sets the unit time-out interrupt when it matches the value
 * specified by \e period. The unit timer is clocked by SYSCLKOUT.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] period         Period value at which a unit time-out interrupt is set
 */
__STATIC_INLINE void DL_EQEP_loadUnitTimer(EQEP_Regs *eqep, uint32_t period)
{
    eqep->QUPRD = period;
}

/**
 * @brief Enables the eQEP module unit timer
 *
 * This API enables operation of the eQEP module's peripheral unit timer.
 * The unit timer is clocked by SYSCLKOUT and will set the unit time-out
 * interrupt when it matches the value specified by \e period.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] period         Period value at which a unit time-out interrupt is set
 */
__STATIC_INLINE void DL_EQEP_enableUnitTimer(EQEP_Regs *eqep, uint32_t period)
{
    eqep->QUPRD   = period;
    eqep->QEPCTL |= EQEP_QEPCTL_UTE_MASK;
}

/**
 * @brief Disables the eQEP module unit timer
 *
 * This API disables operation of the eQEP module's peripheral
 * unit timer.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_disableUnitTimer(EQEP_Regs *eqep)
{
    eqep->QEPCTL &= ~EQEP_QEPCTL_UTE_MASK;
}

/**
 * @brief Enables the eQEP module watchdog timer
 *
 * This API enables operation of the eQEP module's peripheral watchdog
 * timer.
 *
 * @note When selecting \e period, note that the watchdog timer is clocked
 * from SYSCLKOUT/64.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] period         Watchdog period value at which a time-out will occur if
 *                           no quadrature-clock event is detected
 */
__STATIC_INLINE void DL_EQEP_enableWatchdog(EQEP_Regs *eqep, uint16_t period)
{
    eqep->QWDPRD  = period;
    eqep->QEPCTL |= EQEP_QEPCTL_WDE_MASK;
}

/**
 * @brief Disables the eQEP module watchdog timer
 *
 * This API disables operation of the eQEP module's peripheral watchdog
 * timer.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_disableWatchdog(EQEP_Regs *eqep)
{
    eqep->QEPCTL &= ~EQEP_QEPCTL_WDE_MASK;
}

/**
 * @brief Sets the eQEP module watchdog timer value
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] value          The value to be written to the watchdog timer
 */
__STATIC_INLINE void DL_EQEP_setWatchdogTimerValue(EQEP_Regs *eqep, uint16_t value)
{
    eqep->QWDTMR = value;
}

/**
 * @brief Gets the eQEP module watchdog timer value
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The current watchdog timer value
 */
__STATIC_INLINE uint16_t DL_EQEP_getWatchdogTimerValue(EQEP_Regs *eqep)
{
    return eqep->QWDTMR;
}

/**
 * @brief Configures the mode in which the position counter is initialized
 *
 * This API configures the events on which the position count can be
 * initialized. The \e initMode parameter specifies the initialization condition,
 * which can be:
 * - No action (do nothing)
 * - Strobe event initialization
 * - Index event initialization
 * - A logical OR of both a strobe event and an index event
 *
 * Initialization modes include:
 * - \b DL_EQEP_INIT_DO_NOTHING: No initialization action
 *
 * Strobe event initialization modes:
 * - \b DL_EQEP_INIT_RISING_STROBE: Initialize on rising edge of strobe
 * - \b DL_EQEP_INIT_EDGE_DIR_STROBE: Initialize On rising edge when clockwise,
 *                                    on falling when counter clockwise
 *
 * Index event initialization modes:
 * - \b DL_EQEP_INIT_RISING_INDEX: Initialize on rising edge of index
 * - \b DL_EQEP_INIT_FALLING_INDEX: Initialize on falling edge of index
 *
 * Use DL_EQEP_setSWPositionInit() to cause a software initialization and
 * DL_EQEP_setInitialPosition() to set the value that gets loaded into the
 * position counter upon initialization.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] initMode       Configuration for initializing the position count
 *                           @ref DL_EQEP_INIT_MODE
 */
__STATIC_INLINE void DL_EQEP_setPositionInitMode(EQEP_Regs *eqep, uint16_t initMode)
{
    eqep->QEPCTL = (eqep->QEPCTL & ~(EQEP_QEPCTL_IEI_MASK | EQEP_QEPCTL_SEI_MASK)) | initMode;
}

/**
 * @brief Sets the software initialization of the encoder position counter
 *
 * This API performs a software initialization of the position counter
 * when the \e initialize parameter is true. When false, the QEPCTL[SWI] bit
 * is cleared and no action is taken.
 *
 * The init value to be loaded into the position counter can be set with
 * DL_EQEP_setInitialPosition(). Additional initialization causes can be
 * configured with DL_EQEP_setPositionInitMode().
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] initialize     Flag to specify if software initialization of the
 *                           position counter is enabled
 *                           - true: Perform software initialization
 *                           - false: Clear software initialization bit
 */
__STATIC_INLINE void DL_EQEP_setSWPositionInit(EQEP_Regs *eqep, bool initialize)
{
    if (initialize)
    {
        eqep->QEPCTL |= EQEP_QEPCTL_SWI_MASK;
    }
    else
    {
        eqep->QEPCTL &= ~EQEP_QEPCTL_SWI_MASK;
    }
}

/**
 * @brief Sets the initial value for the encoder position counter
 *
 * This API sets the initialization value for the position of the encoder.
 * Use DL_EQEP_setPositionInitMode() to set the initialization cause or
 * DL_EQEP_setSWPositionInit() to cause a software initialization.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] position       Value to be written to the position counter upon
 *                           initialization
 */
__STATIC_INLINE void DL_EQEP_setInitialPosition(EQEP_Regs *eqep, uint32_t position)
{
    eqep->QPOSINIT = position;
}

/**
 * @brief  Configures the position counter latch modes
 *
 * This API configures the events on which the position count and several
 * other registers can be latched. The \e latchMode parameter provides the
 * mode as the logical OR of several values:
 *
 * - Position Counter Latch:
 *   - \b DL_EQEP_LATCH_CNT_READ_BY_CPU: Latch when CPU reads position counter
 *   - \b DL_EQEP_LATCH_UNIT_TIME_OUT: Latch on unit timer time-out event
 * The capture timer and capture period are also latched based on this setting,
 * and can be read using DL_EQEP_getCaptureTimerLatch() and DL_EQEP_getCapturePeriodLatch().
 *
 * - Strobe Event Latch:
 *   - \b DL_EQEP_LATCH_RISING_STROBE: Latch position counter on rising edge of strobe signal
 *                                     into the strobe position latch register
 *   - \b DL_EQEP_LATCH_EDGE_DIR_STROBE: Latch position counter based on rotation direction
 *                                       into the strobe position latch register
 * This register can be read with DL_EQEP_getStrobePositionLatch().
 *
 * - Index Event Latch:
 *   - \b DL_EQEP_LATCH_RISING_INDEX: Latch position counter on rising edge of index signal
 *                                    into the index position latch register
 *   - \b DL_EQEP_LATCH_FALLING_INDEX: Latch position counter on falling edge of index signal
 *                                    into the index position latch register
 *   - \b DL_EQEP_LATCH_SW_INDEX_MARKER: Latch position counter via software index marker
 * This register can be read with DL_EQEP_getIndexPositionLatch().
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] latchMode      Configuration for latching of the position counter
 *                           and several other registers @ref DL_EQEP_LATCH_MODE
 */
__STATIC_INLINE void DL_EQEP_setLatchMode(EQEP_Regs *eqep, uint32_t latchMode)
{
    eqep->QEPCTL = (eqep->QEPCTL & ~(EQEP_QEPCTL_QCLM_MASK | EQEP_QEPCTL_IEL_MASK | EQEP_QEPCTL_SEL_MASK)) | latchMode;
}

/**
 * @brief Gets the encoder position that was latched on an index event
 *
 * This API returns the value in the index position latch register. The
 * position counter is latched into this register based on configuration set by
 * DL_EQEP_setLatchMode():
 * - Rising index edge
 * - Falling index edge
 * - Software index marker
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The position count latched on an index event
 */
__STATIC_INLINE uint32_t DL_EQEP_getIndexPositionLatch(EQEP_Regs *eqep)
{
    return eqep->QPOSILAT;
}

/**
 * @brief Gets the encoder position that was latched on a strobe event
 *
 * This API returns the value in the strobe position latch register. The
 * position counter can be configured to be latched based on different strobe
 * events as set by DL_EQEP_setLatchMode():
 * - Rising strobe edges
 * - Rising strobe edges while moving clockwise
 * - Falling strobe edges while moving counter-clockwise
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The position count latched on a strobe event
 */
__STATIC_INLINE uint32_t DL_EQEP_getStrobePositionLatch(EQEP_Regs *eqep)
{
    return eqep->QPOSSLAT;
}

/**
 * @brief Gets the encoder position that was latched on a unit time-out event
 *
 * This API returns the value in the position latch register. The
 * position counter is latched into this register based on the unit time-out
 * event configuration set by DL_EQEP_setLatchMode().
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The position count latch register value
 */
__STATIC_INLINE uint32_t DL_EQEP_getPositionLatch(EQEP_Regs *eqep)
{
    return eqep->QPOSLAT;
}

/**
 * @brief Gets the encoder capture timer latch
 *
 * This API returns the value in the capture timer latch register. The
 * capture timer value is latched into this register based on the configuration
 * set by DL_EQEP_setLatchMode():
 * - On unit time-out event
 * - Upon reading the eQEP position counter
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The edge-capture timer latch value
 */
__STATIC_INLINE uint16_t DL_EQEP_getCaptureTimerLatch(EQEP_Regs *eqep)
{
    return eqep->QCTMRLAT;
}

/**
 * @brief Gets the encoder capture period latch
 *
 * This API returns the value in the capture period latch register. The
 * capture period value is latched into this register based on the configuration
 * set by DL_EQEP_setLatchMode():
 * - On unit time-out event
 * - Upon reading the eQEP position counter
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 *
 * @return The edge-capture period latch value
 */
__STATIC_INLINE uint16_t DL_EQEP_getCapturePeriodLatch(EQEP_Regs *eqep)
{
    return eqep->QCPRDLAT;
}

/**
 * @brief Sets the quadrature mode adapter (QMA) module mode
 *
 * This API sets the quadrature mode adapter module mode. The possible
 * modes are passed to the function through the \e qmaMode parameter.
 *
 * To use the QMA module, you must first put the eQEP module into direction-count
 * mode (DL_EQEP_CONFIG_CLOCK_DIR) using DL_EQEP_setDecoderConfig().
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] qmaMode        The mode in which the QMA module will operate
 */
__STATIC_INLINE void DL_EQEP_setQMAModuleMode(EQEP_Regs *eqep, DL_EQEP_QMA_MODE qmaMode)
{
    eqep->QMACTRL = (eqep->QMACTRL & ~EQEP_QMACTRL_MODE_MASK) | ((uint32_t)qmaMode & EQEP_QMACTRL_MODE_MASK);
}

/**
 * @brief Sets the strobe input source of the eQEP module
 *
 * This API sets the source of the eQEP module's strobe signal. The
 * possible values of the \e strobeSrc parameter are:
 * - \b DL_EQEP_STROBE_FROM_GPIO - The strobe is used as-is after passing through
 *   the polarity select logic.
 * - \b DL_EQEP_STROBE_OR_ADCSOCA - The strobe is OR'd with the ADCSOCA signal
 *   after passing through the polarity select logic.
 * - \b DL_EQEP_STROBE_OR_ADCSOCB - The strobe is OR'd with the ADCSOCB signal
 *   after passing through the polarity select logic.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] strobeSrc      The source of the strobe signal
 */
__STATIC_INLINE void DL_EQEP_setStrobeSource(EQEP_Regs *eqep, DL_EQEP_STROBE_SOURCE strobeSrc)
{
    eqep->QEPSTROBESEL = (eqep->QEPSTROBESEL & ~EQEP_QEPSTROBESEL_STROBESEL_MASK) | ((uint32_t)strobeSrc);
}

/**
 * @brief Enables the enhancement mode for direction change during Index event
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_enableDirectionChangeDuringIndex(EQEP_Regs *eqep)
{
    eqep->QDECCTL |= EQEP_QDECCTL_QIDIRE_MASK;
}

/**
 * @brief Disables the enhancement mode for direction change during Index event
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_EQEP_disableDirectionChangeDuringIndex(EQEP_Regs *eqep)
{
    eqep->QDECCTL &= ~EQEP_QDECCTL_QIDIRE_MASK;
}

/**
 * @brief Selects the source for eQEPA, eQEPB, and eQEPI signals
 *
 * This API configures the sources for QEPA, QEPB, and Index signals
 * of the eQEP module.
 *
 * @param[in] eqep               Pointer to the register overlay for the peripheral
 * @param[in] sourceConfig       Structure containing source configuration for
 *                               QEPA, QEPB, and Index signals
 */
__STATIC_INLINE void DL_EQEP_selectSource(EQEP_Regs *eqep, DL_EQEP_SOURCE_SELECT sourceConfig)
{
    eqep->QEPSRCSEL =
        (eqep->QEPSRCSEL & ~(EQEP_QEPSRCSEL_QEPASEL_MASK | EQEP_QEPSRCSEL_QEPBSEL_MASK | EQEP_QEPSRCSEL_QEPISEL_MASK)) |
        ((uint32_t)((uint32_t)(sourceConfig.sourceA) << EQEP_QEPSRCSEL_QEPASEL_OFS) |
         (uint32_t)((uint32_t)(sourceConfig.sourceB) << EQEP_QEPSRCSEL_QEPBSEL_OFS) |
         (uint32_t)((uint32_t)(sourceConfig.sourceIndex) << EQEP_QEPSRCSEL_QEPISEL_OFS));
}

/**
 * @brief Sets the emulation mode of the eQEP module
 *
 * This APU sets the eQEP module's emulation mode. This mode determines
 * how the timers are affected by an emulation suspend.
 *
 * The following emulation modes are available:
 * - \b DL_EQEP_EMULATIONMODE_STOPIMMEDIATELY - The position counter, watchdog
 *   counter, unit timer, and capture timer all stop immediately.
 * - \b DL_EQEP_EMULATIONMODE_STOPATROLLOVER - The position counter, watchdog
 *   counter, unit timer all count until period rollover. The capture timer
 *   counts until the next unit period event.
 * - \b DL_EQEP_EMULATIONMODE_RUNFREE - The position counter, watchdog counter,
 *   unit timer, and capture timer are all unaffected by an emulation suspend.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] emuMode        The emulation mode to set
 */
__STATIC_INLINE void DL_EQEP_setEmulationMode(EQEP_Regs *eqep, DL_EQEP_EMULATION_MODE emuMode)
{
    eqep->QEPCTL = (eqep->QEPCTL & ~EQEP_QEPCTL_FREE_SOFT_MASK) | ((uint16_t)emuMode);
}

/**
 * @brief Configures eQEP module position-compare unit
 *
 * This API configures the operation of the eQEP module position-compare
 * unit. The \e config parameter provides the configuration of the
 * position-compare unit and is the logical OR of several values:
 *
 * - \b DL_EQEP_COMPARE_NO_SYNC_OUT, \b DL_EQEP_COMPARE_IDX_SYNC_OUT, or
 *   \b DL_EQEP_COMPARE_STROBE_SYNC_OUT specify if there is a sync output pulse
 *   and which pin should be used.
 * - \b DL_EQEP_COMPARE_NO_SHADOW, \b DL_EQEP_COMPARE_LOAD_ON_ZERO, or
 *   \b DL_EQEP_COMPARE_LOAD_ON_MATCH specify if a shadow is enabled and when
 *   should the load should occur--QPOSCNT = 0 or QPOSCNT = QPOSCOMP.
 *
 * The \e cycles is used to select the width of the sync output pulse. The
 * width of the resulting pulse will be \e cycles * 4 * the width of a
 * SYSCLKOUT cycle. The maximum width is 4096 * 4 * SYSCLKOUT cycles.
 *
 * \note You can set the sync pulse width independently using the
 * DL_EQEP_setComparePulseWidth() API.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] config         Configuration for the eQEP module position-compare unit
 * @param[in] compareValue   Value to which the position count value is compared
 * @param[in] cycles         Width of the pulse that can be generated on a
 *                           position-compare event, in units of 4 SYSCLKOUT cycles
 */
void DL_EQEP_setCompareConfig(EQEP_Regs *eqep, uint16_t config, uint32_t compareValue, uint16_t cycles);

/**
 * @brief Sets the polarity of the eQEP module's input signals
 *
 * This API configures the polarity of the inputs to the eQEP module. To
 * negate the polarity of any of the input signals, pass true into its
 * corresponding parameter in this function. Pass false to leave it as-is.
 *
 * @param[in] eqep           Pointer to the register overlay for the peripheral
 * @param[in] invertQEPA     Flag to negate the QEPA input
 *                           - true: Negate QEPA input
 *                           - false: Do not negate QEPA input
 * @param[in] invertQEPB     Flag to negate the QEPB input
 *                           - true: Negate QEPB input
 *                           - false: Do not negate QEPB input
 * @param[in] invertIndex    Flag to negate the index input
 *                           - true: Negate index input
 *                           - false: Do not negate index input
 * @param[in] invertStrobe   Flag to negate the strobe input
 *                           - true: Negate strobe input
 *                           - false: Do not negate strobe input
 */
void DL_EQEP_setInputPolarity(EQEP_Regs *eqep, bool invertQEPA, bool invertQEPB, bool invertIndex, bool invertStrobe);

/**
 * @brief Initializes the EQEP configuration parameters.
 *
 * This function initializes all the parameters of the EQEP configuration
 * structure to their default values.
 *
 * @param[in,out] config Pointer to the EQEP configuration structure.
 */

void DL_EQEP_initParamsSetDefault(DL_EQEP_Config *config);

/**
 * @brief Initializes the EQEP module
 *
 * This function configures the EQEP module according to the provided configuration.
 *
 * @param eqep Pointer to the EQEP register overlay
 * @param config Pointer to the EQEP configuration structure
 */
void DL_EQEP_init(EQEP_Regs *eqep, DL_EQEP_Config *config);

#ifdef __cplusplus
}
#endif

#endif /* DL_EQEP_H */
       /** @}*/
