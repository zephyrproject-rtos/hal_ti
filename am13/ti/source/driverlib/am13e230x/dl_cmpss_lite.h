
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
 * @defgroup DL_CMPSS_LITE_AM13E230X  Driverlib CMPSSLITE API
 * @ingroup DL_AM13E230X
 *
 *@{
 */

#ifndef DL_CMPSS_LITE_H
#define DL_CMPSS_LITE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "soc.h"
#include "dl_common.h"
#include "hw_cmpss_lite.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 * @name DL_CMPSSLITE_INSRC
 * @anchor DL_CMPSSLITE_INSRC
 * @{
 */
/*! @brief Input driven by internal DAC */
#define DL_CMPSSLITE_INSRC_DAC (0x0000U)
/*! @brief Input driven by external pin */
#define DL_CMPSSLITE_INSRC_PIN (0x0001U)
/** @}*/

/**
 * @name DL_CMPSSLITE_CONFIG
 * @anchor DL_CMPSSLITE_CONFIG
 * @{
 */
/*! @brief Comparator output is inverted */
#define DL_CMPSSLITE_CONFIG_INVERT        (0x0002U)
/*! @brief Asynch comparator output feeds into OR gate with latched digital filter output */
#define DL_CMPSSLITE_CONFIG_ASYNCH_ENABLE (0x0040U)
/** @}*/

/**
 * @name DL_CMPSSLITE_TRIPOUT
 * @anchor DL_CMPSSLITE_TRIPOUT
 * @{
 */
/*! @brief Asynchronous comparator output drives CTRIPOUT */
#define DL_CMPSSLITE_TRIPOUT_ASYNC_COMP (0x0000U)
/*! @brief Synchronous comparator output drives CTRIPOUT */
#define DL_CMPSSLITE_TRIPOUT_SYNC_COMP  (0x0010U)
/*! @brief Filter output drives CTRIPOUT */
#define DL_CMPSSLITE_TRIPOUT_FILTER     (0x0020U)
/*! @brief Latched filter output drives CTRIPOUT */
#define DL_CMPSSLITE_TRIPOUT_LATCH      (0x0030U)
/** @}*/

/**
 * @name DL_CMPSSLITE_TRIP
 * @anchor DL_CMPSSLITE_TRIP
 * @{
 */
/*! @brief Asynchronous comparator output drives CTRIP */
#define DL_CMPSSLITE_TRIP_ASYNC_COMP (0x0000U)
/*! @brief Synchronous comparator output drives CTRIP */
#define DL_CMPSSLITE_TRIP_SYNC_COMP  (0x0004U)
/*! @brief Filter output drives CTRIP */
#define DL_CMPSSLITE_TRIP_FILTER     (0x0008U)
/*! @brief Latched filter output drives CTRIP */
#define DL_CMPSSLITE_TRIP_LATCH      (0x000CU)
/** @}*/

/**
 * @name DL_CMPSSLITE_STATUS
 * @anchor DL_CMPSSLITE_STATUS
 * @{
 */
/*! @brief High digital filter output */
#define DL_CMPSSLITE_STS_HI_FILOUT      (CMPSS_LITE_COMPSTS_COMPHSTS_MASK)
/*! @brief Latched value of high digital filter output */
#define DL_CMPSSLITE_STS_HI_LATCHFILOUT (CMPSS_LITE_COMPSTS_COMPHLATCH_MASK)
/*! @brief Low digital filter output */
#define DL_CMPSSLITE_STS_LO_FILOUT      (CMPSS_LITE_COMPSTS_COMPLSTS_MASK)
/*! @brief Latched value of low digital filter output */
#define DL_CMPSSLITE_STS_LO_LATCHFILOUT (CMPSS_LITE_COMPSTS_COMPLLATCH_MASK)
/** @}*/

/**
 * @name DL_CMPSSLITE_DACVAL
 * @anchor DL_CMPSSLITE_DACVAL
 * @{
 */
/*! @brief DAC value register updated on MCLK */
#define DL_CMPSSLITE_DACVAL_MCLK    (0x0000U)
/*! @brief DAC value register updated on PWM sync */
#define DL_CMPSSLITE_DACVAL_PWMSYNC (0x0080U)
/** @}*/

/*! @brief DAC and digital filter Sync source */
typedef enum
{
    /*! Sync source is MCPWM0SYNCPER */
    DL_CMPSSLITE_SYNCSOURCE_MCPWM0_SYNCPER = 0U,
    /*! Sync source is MCPWM1SYNCPER */
    DL_CMPSSLITE_SYNCSOURCE_MCPWM1_SYNCPER = 1U,
    /*! Sync source is MCPWM2SYNCPER */
    DL_CMPSSLITE_SYNCSOURCE_MCPWM2_SYNCPER = 2U,
    /*! Sync source is MCPWM3SYNCPER */
    DL_CMPSSLITE_SYNCSOURCE_MCPWM3_SYNCPER = 3U,
    /*! Sync source is MCPWM4SYNCPER */
    DL_CMPSSLITE_SYNCSOURCE_MCPWM4_SYNCPER = 4U
} DL_CMPSSLITE_SYNCSOURCE;

/*! @brief Comparator digital filter input selection */
typedef enum
{
    /*! Filter input driven by comparator output */
    DL_CMPSSLITE_FILTIN_COMPOUT = 0x0000U,
    /*! Filter input driven by EXT_FILTIN_H[1] */
    DL_CMPSSLITE_FILTIN_EXT_H1  = 0x0001U,
    /*! Filter input driven by EXT_FILTIN_H[2] */
    DL_CMPSSLITE_FILTIN_EXT_H2  = 0x0002U,
    /*! Filter input driven by EXT_FILTIN_H[3] */
    DL_CMPSSLITE_FILTIN_EXT_H3  = 0x0003U,
    /*! Filter input driven by EXT_FILTIN_H[4] */
    DL_CMPSSLITE_FILTIN_EXT_H4  = 0x0004U,
    /*! Filter input driven by EXT_FILTIN_H[5] */
    DL_CMPSSLITE_FILTIN_EXT_H5  = 0x0005U,
    /*! Filter input driven by EXT_FILTIN_H[6] */
    DL_CMPSSLITE_FILTIN_EXT_H6  = 0x0006U,
    /*! Filter input driven by EXT_FILTIN_H[7] */
    DL_CMPSSLITE_FILTIN_EXT_H7  = 0x0007U
} DL_CMPSSLITE_FILTER_INPUT;

/*! @brief Hysteresis levels for the comparator */
typedef enum
{
    /*! No hysteresis */
    DL_CMPSSLITE_HYSTERESIS_NONE    = 0U,
    /*! Typical hysteresis level */
    DL_CMPSSLITE_HYSTERESIS_TYPICAL = 1U,
    /*! 2x typical hysteresis */
    DL_CMPSSLITE_HYSTERESIS_2X      = 2U,
    /*! 3x typical hysteresis */
    DL_CMPSSLITE_HYSTERESIS_3X      = 3U,
    /*! 4x typical hysteresis */
    DL_CMPSSLITE_HYSTERESIS_4X      = 4U
} DL_CMPSSLITE_HYSTERESIS;

/**
 * @brief Filter configuration structure
 */
typedef struct
{
    /*! Initialize the filter during CMPSSLITE init
        - true: Initialize all samples to the filter input value
        - false: no effect
    */
    bool                      initFilter;
    /*! Input configuration for the filter
        - Valid values: @ref DL_CMPSSLITE_FILTER_INPUT
    */
    DL_CMPSSLITE_FILTER_INPUT filtInput;
    /*! Sample prescale value
        - Valid values: 24 bit unsigned integer
    */
    uint32_t                  samplePrescale;
    /*! Sample window size
        - Valid values: 1 to 64
    */
    uint16_t                  sampleWindow;
    /*! Threshold value for the filter
        - Valid values: 1 to 64.
        For proper operation, threshold value must be greater than sampleWindow / 2
    */
    uint16_t                  threshold;
    /*! Allow asynchronous comparator output to feed into OR gate with latched digital filter signal
        - Relevant only when tripSourceSelect is DL_CMPSSLITE_TRIP_LATCH (CTRIPHSEL=3) or
        tripOutSourceSelect is DL_CMPSSLITE_TRIPOUT_LATCH (CTRIPOUTHSEL=3) */
    bool                      asyncORLatch;
    /*! Enable reset of comparator digital filter output latch based on PWM SYNCPER.
        - true: MCPWMSYNCPER will reset latch.
        - false: MCPWMSYNCPER will not reset latch.
        */
    bool                      enableLatchResetOnPWMSYNC;
} DL_CMPSSLITE_FilterConfig;

/**
 * @brief DAC configuration structure
 */
typedef struct
{
    /*! Initial DAC value for the comparator
        - Valid values: Unsigned 12 bit integer
    */
    uint16_t initialDacValue;
} DL_CMPSSLITE_DacConfig;

/**
 * @brief Comparator (COMPH/L) configuration structure
 */
typedef struct
{
    /*! Select the source for the inverting input of the comparator
        - Valid values: @ref DL_CMPSSLITE_INSRC
    */
    uint8_t sourceSelect;
    /*! Invert the comparator output
        - true: Comparator output is inverted
        - false: Comparator output is not inverted
    */
    bool    invert;
    /*! Select the CTRIP source
        - Valid values: DL_CMPSSLITE_TRIP
    */
    uint8_t tripSourceSelect;
    /*! Select the CTRIPOUT source
        - Valid values: @ref DL_CMPSSLITE_TRIPOUT
    */
    uint8_t tripOutSourceSelect;
} DL_CMPSSLITE_CompConfig;

/**
 * @brief High/Low comparator subsystem configuration structure
 */
typedef struct
{
    /*! Use COMPH/L */
    bool                      useComp;
    /*! Use DACH/L */
    bool                      useDac;
    /*! Use Digital Filter H/L */
    bool                      useFilter;
    /*! Select the sync source for DAC and Digital Filter reset.
        - Valid values: @ref DL_CMPSSLITE_SYNCSOURCE */
    DL_CMPSSLITE_SYNCSOURCE   syncSource;
    /*! COMPH/L configuration structure */
    DL_CMPSSLITE_CompConfig   compConfig;
    /*! DACH/DACL configuration structure */
    DL_CMPSSLITE_DacConfig    dacConfig;
    /*! Digital filter H/L configuration structure */
    DL_CMPSSLITE_FilterConfig filterConfig;
} DL_CMPSSLITE_CompSSConfig;

/**
 * @brief Main configuration structure for CMPSSLITE
 */
typedef struct
{
    /*! Enable the comparator/DAC
        - true: Comparator and DAC are enabled
        - false: Comparator and DAC and disabled
    */
    bool                      enableModule;
    /*! Hysteresis configuration for the comparator High and Low.
        - Valid values: @ref DL_CMPSSLITE_HYSTERESIS
    */
    DL_CMPSSLITE_HYSTERESIS   hysteresis;
    /*! Select the software load mechanism for DACH(High) Shadow to Active load.
        Load whether upon MCLK or PWM SYNCPER.
        - Valid values: @ref DL_CMPSSLITE_DACVAL
    */
    uint8_t                   dacSwLoadSelect;
    /*! High comparator subsystem configuration */
    DL_CMPSSLITE_CompSSConfig highCompSSConfig;
    /*! Low comparator subsystem configuration */
    DL_CMPSSLITE_CompSSConfig lowCompSSConfig;
} DL_CMPSSLITE_Config;

/**
 * @brief Enables the CMPSSLITE module
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_enableModule(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->COMPCTL |= CMPSS_LITE_COMPCTL_COMPDACE_MASK;
}

/**
 * @brief Disables the CMPSSLITE module
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_disableModule(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->COMPCTL &= ~CMPSS_LITE_COMPCTL_COMPDACE_MASK;
}

/**
 * @brief Sets the configuration for the high comparator
 *
 * This API configures a high comparator. The \e config parameter is the
 * result of a logical OR operation between following values:
 *
 * - Comparator negative input source:
 *   - \b DL_CMPSSLITE_INSRC_DAC - Input driven by internal DAC
 *   - \b DL_CMPSSLITE_INSRC_PIN - Input driven by external pin
 *
 * - \b DL_CMPSSLITE_CONFIG_INVERT - Invert comparator output
 *
 * - \b DL_CMPSSLITE_CONFIG_ASYNCH_ENABLE - The asynchronous comparator output will be fed
 *                                          into an OR gate with the latched digital filter output
 *                                          before it is made available for CTRIPH or CTRIPOUTH.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] config         Configuration for the high comparator
 *                           @ref DL_CMPSSLITE_INSRC and @ref DL_CMPSSLITE_CONFIG
 */
__STATIC_INLINE void DL_CMPSSLITE_configHighComparator(CMPSS_LITE_Regs *cmpsslite, uint16_t config)
{
    cmpsslite->COMPCTL = (cmpsslite->COMPCTL & ~(CMPSS_LITE_COMPCTL_COMPHSOURCE_MASK |
                                                 CMPSS_LITE_COMPCTL_COMPHINV_MASK | CMPSS_LITE_COMPCTL_ASYNCHEN_MASK)) |
                         config;
}

/**
 * @brief Sets the configuration for the low comparator
 *
 * This API configures a low comparator. The \e config parameter is the
 * result of a logical OR operation between following values:
 *
 * - Comparator negative input source:
 *   - \b DL_CMPSSLITE_INSRC_DAC - Input driven by internal DAC
 *   - \b DL_CMPSSLITE_INSRC_PIN - Input driven by external pin
 *
 * - \b DL_CMPSSLITE_CONFIG_INVERT - Invert comparator output
 *
 * - \b DL_CMPSSLITE_CONFIG_ASYNCH_ENABLE - The asynchronous comparator output will be fed
 *                                          into an OR gate with the latched digital filter output
 *                                          before it is made available for CTRIPL or CTRIPOUTL.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] config         Configuration for the low comparator
 *                           @ref DL_CMPSSLITE_INSRC and @ref DL_CMPSSLITE_CONFIG
 */
__STATIC_INLINE void DL_CMPSSLITE_configLowComparator(CMPSS_LITE_Regs *cmpsslite, uint16_t config)
{
    cmpsslite->COMPCTL = (cmpsslite->COMPCTL & ~(CMPSS_LITE_COMPCTL_COMPLSOURCE_MASK |
                                                 CMPSS_LITE_COMPCTL_COMPLINV_MASK | CMPSS_LITE_COMPCTL_ASYNCLEN_MASK)) |
                         (config << 8U);
}

/**
 * @brief Sets the output signal configuration for the high comparator
 *
 * This API configures a comparator's output signals CTRIP and CTRIPOUT
 * for the high comparator. The \e config parameter is the result of a logical
 * OR operation between the following values:
 *
 * High Comparator Trip Output Source Select:
 * - \b DL_CMPSSLITE_TRIPOUT_ASYNC_COMP - Asynchronous comparator output
 * - \b DL_CMPSSLITE_TRIPOUT_SYNC_COMP - Synchronous comparator output
 * - \b DL_CMPSSLITE_TRIPOUT_FILTER - Digital filter output
 * - \b DL_CMPSSLITE_TRIPOUT_LATCH - Latched digital filter output
 *
 * High Comparator Trip Source Select:
 * - \b DL_CMPSSLITE_TRIP_ASYNC_COMP - Asynchronous comparator output
 * - \b DL_CMPSSLITE_TRIP_SYNC_COMP - Synchronous comparator output
 * - \b DL_CMPSSLITE_TRIP_FILTER - Digital filter output
 * - \b DL_CMPSSLITE_TRIP_LATCH - Latched digital filter output
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] config         Configuration for the high comparator output signals
 *                           @ref DL_CMPSSLITE_TRIPOUT and @ref DL_CMPSSLITE_TRIP
 */
__STATIC_INLINE void DL_CMPSSLITE_configOutputsHigh(CMPSS_LITE_Regs *cmpsslite, uint16_t config)
{
    cmpsslite->COMPCTL =
        (cmpsslite->COMPCTL & ~(CMPSS_LITE_COMPCTL_CTRIPOUTHSEL_MASK | CMPSS_LITE_COMPCTL_CTRIPHSEL_MASK)) | config;
}

/**
 * @brief Sets the output signal configuration for the low comparator
 *
 * This API configures a comparator's output signals CTRIP and CTRIPOUT
 * for the low comparator. The \e config parameter is the result of a logical
 * OR operation between the following values:
 *
 * Low Comparator Trip Output Source Select:
 * - \b DL_CMPSSLITE_TRIPOUT_ASYNC_COMP - Asynchronous comparator output
 * - \b DL_CMPSSLITE_TRIPOUT_SYNC_COMP - Synchronous comparator output
 * - \b DL_CMPSSLITE_TRIPOUT_FILTER - Digital filter output
 * - \b DL_CMPSSLITE_TRIPOUT_LATCH - Latched digital filter output
 *
 * Low Comparator Trip Source Select:
 * - \b DL_CMPSSLITE_TRIP_ASYNC_COMP - Asynchronous comparator output
 * - \b DL_CMPSSLITE_TRIP_SYNC_COMP - Synchronous comparator output
 * - \b DL_CMPSSLITE_TRIP_FILTER - Digital filter output
 * - \b DL_CMPSSLITE_TRIP_LATCH - Latched digital filter output
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] config         Configuration for the low comparator output signals
 *                           @ref DL_CMPSSLITE_TRIPOUT and @ref DL_CMPSSLITE_TRIP
 */
__STATIC_INLINE void DL_CMPSSLITE_configOutputsLow(CMPSS_LITE_Regs *cmpsslite, uint16_t config)
{
    cmpsslite->COMPCTL =
        (cmpsslite->COMPCTL & ~(CMPSS_LITE_COMPCTL_CTRIPOUTLSEL_MASK | CMPSS_LITE_COMPCTL_CTRIPLSEL_MASK)) |
        (config << 8U);
}

/**
 * @brief Gets the current comparator status
 *
 * This API returns the current status for the comparator, specifically
 * the digital filter output and latched digital filter output.
 *
 * Possible status values are bitwise combinations of the following:
 * - \b DL_CMPSSLITE_STS_HI_FILOUT - High digital filter output
 * - \b DL_CMPSSLITE_STS_HI_LATCHFILOUT - Latched value of high digital filter output
 * - \b DL_CMPSSLITE_STS_LO_FILOUT - Low digital filter output
 * - \b DL_CMPSSLITE_STS_LO_LATCHFILOUT - Latched value of low digital filter output
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 *
 * @return Current comparator status as a bitwise combination of status flags
 */
__STATIC_INLINE uint16_t DL_CMPSSLITE_getStatus(CMPSS_LITE_Regs *cmpsslite)
{
    return cmpsslite->COMPSTS;
}

/**
 * @brief Sets the configuration for the internal DAC of high comparator
 *
 * This API configures the comparator's internal DAC. The \e config
 * parameter configures whether DACxVALA is updated from DACxVALS on MCLK
 * or MCPWMSYNCPER.
 *
 * - \b DL_CMPSSLITE_DACVAL_MCLK - Value register updated on system clock
 * - \b DL_CMPSSLITE_DACVAL_PWMSYNC - Value register updated on PWM sync
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] config         configuration of the internal DAC
 */
__STATIC_INLINE void DL_CMPSSLITE_configDACHigh(CMPSS_LITE_Regs *cmpsslite, uint16_t config)
{
    cmpsslite->COMPDACHCTL = (cmpsslite->COMPDACHCTL & ~CMPSS_LITE_COMPDACHCTL_SWLOADSEL_MASK) | config;
}

/**
 * @brief Configures sync source for high comparator
 *
 * This API configures the desired MCPWMxSYNCPER source for high comparator
 * blocks. The configured MCPWMxSYNCPER signal can be used to synchronize loading
 * of DAC input value from shadow to active register. It can also be used to
 * synchronize the Ramp generator, if applicable.
 *
 * Valid values for \e syncSource parameter can be 0 to n, where n represents
 * the maximum number of MCPWMSYNCPER signals available on the device. For
 * instance, passing 2 into \e syncSource will select MCPWM2SYNCPER.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] syncSource     Desired MCPWMxSYNCPER source
 */
__STATIC_INLINE void DL_CMPSSLITE_configureSyncSourceHigh(CMPSS_LITE_Regs        *cmpsslite,
                                                          DL_CMPSSLITE_SYNCSOURCE syncSource)
{
    cmpsslite->COMPDACHCTL = (cmpsslite->COMPDACHCTL & ~CMPSS_LITE_COMPDACHCTL_RAMPSOURCE_MASK) |
                             ((uint16_t)syncSource << CMPSS_LITE_COMPDACHCTL_RAMPSOURCE_OFS);
}

/**
 * @brief Configures sync source for low comparator
 *
 * This API configures the desired MCPWMxSYNCPER source for low comparator
 * blocks. The configured MCPWMxSYNCPER signal can be used to synchronize loading
 * of DAC input value from shadow to active register. It can also be used to
 * synchronize the Ramp generator, if applicable.
 *
 * Valid values for \e syncSource parameter can be 0 to n, where n represents
 * the maximum number of MCPWMSYNCPER signals available on the device. For
 * instance, passing 2 into \e syncSource will select MCPWM2SYNCPER.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] syncSource     Desired MCPWMxSYNCPER source
 */
__STATIC_INLINE void DL_CMPSSLITE_configureSyncSourceLow(CMPSS_LITE_Regs *cmpsslite, DL_CMPSSLITE_SYNCSOURCE syncSource)
{
    cmpsslite->COMPDACLCTL = (cmpsslite->COMPDACLCTL & ~CMPSS_LITE_COMPDACLCTL_RAMPSOURCE_MASK) |
                             ((uint16_t)syncSource << CMPSS_LITE_COMPDACLCTL_RAMPSOURCE_OFS);
}

/**
 * @brief Sets the value of the internal DAC of the high comparator
 *
 * This API sets the 12-bit value driven by the internal DAC of the high
 * comparator. The value will be loaded into the shadow register, from which
 * the actual DAC value register will be updated based on the configuration
 * set by DL_CMPSSLITE_configDACHigh().
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] value          12-bit DAC value to be set (0-4095)
 */
__STATIC_INLINE void DL_CMPSSLITE_setDACValueHigh(CMPSS_LITE_Regs *cmpsslite, uint16_t value)
{
    ASSERT(value < 4096U);

    cmpsslite->DACHVALS = value;
}

/**
 * @brief Sets the value of the internal DAC of the low comparator
 *
 * This API sets the 12-bit value driven by the internal DAC of the low
 * comparator. The value will be loaded into the shadow register, from which
 * the actual DAC value register will be updated based on the configuration
 * set by DL_CMPSSLITE_configDACLow().
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] value          12-bit DAC value to be set (0-4095)
 */
__STATIC_INLINE void DL_CMPSSLITE_setDACValueLow(CMPSS_LITE_Regs *cmpsslite, uint16_t value)
{
    ASSERT(value < 4096U);

    /* Write the DAC value to the DAC value shadow register */
    cmpsslite->DACLVALS = value;
}

/**
 * @brief Gets the value of the internal DAC of the high comparator
 *
 * This API returns the value of the internal DAC of the high comparator.
 * The value is read from the active register, not the shadow register used by
 * DL_CMPSSLITE_setDACValueHigh().
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 *
 * @return Value driven by the internal DAC of the high comparator
 */
__STATIC_INLINE uint16_t DL_CMPSSLITE_getDACValueHigh(CMPSS_LITE_Regs *cmpsslite)
{
    return cmpsslite->DACHVALA;
}

/**
 * @brief Gets the value of the internal DAC of the low comparator
 *
 * This API returns the value of the internal DAC of the low comparator.
 * The value is read from the active register, not the shadow register used by
 * DL_CMPSSLITE_setDACValueLow().
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 *
 * @return Value driven by the internal DAC of the low comparator
 */
__STATIC_INLINE uint16_t DL_CMPSSLITE_getDACValueLow(CMPSS_LITE_Regs *cmpsslite)
{
    return cmpsslite->DACLVALA;
}

/**
 * @brief Initializes the digital filter of the high comparator
 *
 * This API initializes all the samples in the high comparator digital
 * filter to the filter input value.
 *
 * @note See DL_CMPSSLITE_configFilterHigh() for the proper initialization
 * sequence to avoid glitches.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_initFilterHigh(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->CTRIPHFILCTL |= CMPSS_LITE_CTRIPHFILCTL_FILINIT_MASK;
}

/**
 * @brief Initializes the digital filter of the low comparator
 *
 * This API initializes all the samples in the low comparator digital
 * filter to the filter input value.
 *
 * @note See DL_CMPSSLITE_configFilterLow() for the proper initialization
 * sequence to avoid glitches.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_initFilterLow(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->CTRIPLFILCTL |= CMPSS_LITE_CTRIPLFILCTL_FILINIT_MASK;
}

/**
 * @brief Configures input for the digital filter of the high comparator
 *
 * This API configures the input for the digital filter of the high
 * comparator. The filter input can be the high comparator output or
 * an external signal configured through XBAR.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] filtInput      Desired filter input
 */
__STATIC_INLINE void DL_CMPSSLITE_configFilterInputHigh(CMPSS_LITE_Regs *cmpsslite, DL_CMPSSLITE_FILTER_INPUT filtInput)
{
    cmpsslite->CTRIPHFILCTL = (cmpsslite->CTRIPHFILCTL & ~CMPSS_LITE_CTRIPHFILCTL_FILTINSEL_MASK) | (uint16_t)filtInput;
}

/**
 * @brief Configures input for the digital filter of the low comparator
 *
 * This API configures the input for the digital filter of the low
 * comparator. The filter input can be the low comparator output or
 * an external signal configured through XBAR.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] filtInput      Desired filter input
 */
__STATIC_INLINE void DL_CMPSSLITE_configFilterInputLow(CMPSS_LITE_Regs *cmpsslite, DL_CMPSSLITE_FILTER_INPUT filtInput)
{
    cmpsslite->CTRIPLFILCTL = (cmpsslite->CTRIPLFILCTL & ~CMPSS_LITE_CTRIPLFILCTL_FILTINSEL_MASK) | (uint16_t)filtInput;
}

/**
 * @brief Causes a software reset of the high comparator digital filter output latch
 *
 * This API causes a software reset of the high comparator digital filter
 * output latch. It will generate a single pulse of the latch reset signal.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_clearFilterLatchHigh(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->COMPSTSCLR |= CMPSS_LITE_COMPSTSCLR_HLATCHCLR_MASK;
}

/**
 * @brief Causes a software reset of the low comparator digital filter output latch
 *
 * This API causes a software reset of the low comparator digital filter
 * output latch. It will generate a single pulse of the latch reset signal.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_clearFilterLatchLow(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->COMPSTSCLR |= CMPSS_LITE_COMPSTSCLR_LLATCHCLR_MASK;
}

/**
 * @brief Sets the comparator hysteresis settings
 *
 * This API sets the amount of hysteresis on the comparator inputs.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] hysteresis     Amount of hysteresis @ref DL_CMPSSLITE_HYSTERESIS
 */
__STATIC_INLINE void DL_CMPSSLITE_setHysteresis(CMPSS_LITE_Regs *cmpsslite, DL_CMPSSLITE_HYSTERESIS hysteresis)
{
    cmpsslite->COMPHYSCTL = (uint16_t)hysteresis;
}

/**
 * @brief Enables reset of HIGH comparator digital filter output latch on PWMSYNC
 *
 * This API enables MCPWMSYNCPER reset of High comparator digital filter output latch
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_enableLatchResetOnPWMSYNCHigh(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->COMPSTSCLR |= CMPSS_LITE_COMPSTSCLR_HSYNCCLREN_MASK;
}

/**
 * @brief Disables reset of HIGH comparator digital filter output latch on PWMSYNC
 *
 * This API disables MCPWMSYNCPER reset of High comparator digital filter output latch
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_disableLatchResetOnPWMSYNCHigh(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->COMPSTSCLR &= ~CMPSS_LITE_COMPSTSCLR_HSYNCCLREN_MASK;
}

/**
 * @brief Enables reset of LOW comparator digital filter output latch on PWMSYNC
 *
 * This API enables MCPWMSYNCPER reset of Low comparator digital filter output latch
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_enableLatchResetOnPWMSYNCLow(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->COMPSTSCLR |= CMPSS_LITE_COMPSTSCLR_LSYNCCLREN_MASK;
}

/**
 * @brief Disables reset of LOW comparator digital filter output latch on PWMSYNC
 *
 * This API disables MCPWMSYNCPER reset of Low comparator digital filter output latch
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_CMPSSLITE_disableLatchResetOnPWMSYNCLow(CMPSS_LITE_Regs *cmpsslite)
{
    cmpsslite->COMPSTSCLR &= ~CMPSS_LITE_COMPSTSCLR_LSYNCCLREN_MASK;
}

/**
 * @brief Configures the digital filter of the high comparator
 *
 * This API configures the operation of the digital filter of the high comparator.
 *
 * The \e samplePrescale parameter specifies the number of system clock cycles
 * between samples. It is a 24-bit value so a number higher than 16777215 should
 * not be passed as this parameter. The prescaler used by digital filter is 1
 * more than \e samplePrescale value. So, the input provided should be 1 less
 * than the expected prescaler.
 *
 * The \e sampleWindow parameter configures the size of the window of FIFO
 * samples taken from the input that will be monitored to determine when to
 * change the filter output. This sample window may be no larger than 64
 * samples.
 *
 * The \e threshold parameter configures the threshold value to be used by
 * the digital filter.
 *
 * The filter output resolves to the majority value of the sample window where
 * majority is defined by the value passed into the \e threshold parameter.
 * For proper operation, the value of \e threshold must be greater than
 * sampleWindow / 2.
 *
 *  To ensure proper operation of the filter, the following is the recommended
 * function call sequence for initialization:
 * -# Configure and enable the comparator using DL_CMPSSLITE_configHighComparator()
 *    and DL_CMPSSLITE_enableModule()
 * -# Configure the digital filter using DL_CMPSSLITE_configFilterHigh()
 * -# Initialize the sample values using DL_CMPSSLITE_initFilterHigh()
 * -# Configure the module output signals CTRIP and CTRIPOUT using
 *    DL_CMPSSLITE_configOutputsHigh()
 *
 * @param[in] cmpsslite        Pointer to the register overlay for the peripheral
 * @param[in] samplePrescale   Number of system clock cycles between samples
 * @param[in] sampleWindow     Size of the sample window
 * @param[in] threshold        Majority threshold of samples to change state
 */
void DL_CMPSSLITE_configFilterHigh(CMPSS_LITE_Regs *cmpsslite, uint32_t samplePrescale, uint16_t sampleWindow,
                                   uint16_t threshold);

/**
 * @brief Configures the digital filter of the low comparator
 *
 * This API configures the operation of the digital filter of the low comparator.
 *
 * The \e samplePrescale parameter specifies the number of system clock cycles
 * between samples. It is a 24-bit value so a number higher than 16777215 should
 * not be passed as this parameter. The prescaler used by digital filter is 1
 * more than \e samplePrescale value. So, the input provided should be 1 less
 * than the expected prescaler.
 *
 * The \e sampleWindow parameter configures the size of the window of FIFO
 * samples taken from the input that will be monitored to determine when to
 * change the filter output. This sample window may be no larger than 64
 * samples.
 *
 * The \e threshold parameter configures the threshold value to be used by
 * the digital filter.
 *
 * The filter output resolves to the majority value of the sample window where
 * majority is defined by the value passed into the \e threshold parameter.
 * For proper operation, the value of \e threshold must be greater than
 * sampleWindow / 2.
 *
 *  To ensure proper operation of the filter, the following is the recommended
 * function call sequence for initialization:
 * -# Configure and enable the comparator using DL_CMPSSLITE_configLowComparator()
 *    and DL_CMPSSLITE_enableModule()
 * -# Configure the digital filter using DL_CMPSSLITE_configFilterLow()
 * -# Initialize the sample values using DL_CMPSSLITE_initFilterLow()
 * -# Configure the module output signals CTRIP and CTRIPOUT using
 *    DL_CMPSSLITE_configOutputsLow()
 *
 * @param[in] cmpsslite        Pointer to the register overlay for the peripheral
 * @param[in] samplePrescale   Number of system clock cycles between samples
 * @param[in] sampleWindow     Size of the sample window
 * @param[in] threshold        Majority threshold of samples to change state
 */
void DL_CMPSSLITE_configFilterLow(CMPSS_LITE_Regs *cmpsslite, uint32_t samplePrescale, uint16_t sampleWindow,
                                  uint16_t threshold);

/**
 * @brief Configures whether or not the digital filter latches are reset by PWMSYNC
 *
 * This API configures whether or not the digital filter latches in both
 * the high and low comparators should be reset by PWMSYNC.
 *
 * If the \e highEnable parameter is \b true, the PWMSYNC will be allowed to reset
 * the high comparator's digital filter latch. If it is false, the ability of
 * the PWMSYNC to reset the latch will be disabled. The \e lowEnable parameter
 * has the same effect on the low comparator's digital filter latch.
 *
 * @param[in] cmpsslite      Pointer to the register overlay for the peripheral
 * @param[in] highEnable     indicates filter latch settings in the high comparator
 * @param[in] lowEnable      indicates filter latch settings in the low comparator
 */
void DL_CMPSSLITE_configLatchOnPWMSYNC(CMPSS_LITE_Regs *cmpsslite, bool highEnable, bool lowEnable);

/**
 * @brief Initializes the CMPSSLITE configuration parameters.
 *
 * This function initializes all the parameters of the CMPSSLITE configuration
 * structure to their default values.
 *
 * @param[in,out] config Pointer to the CMPSSLITE configuration structure.
 */

void DL_CMPSSLITE_initParamsSetDefault(DL_CMPSSLITE_Config *config);

/**
 * @brief Initializes the CMPSSLITE module
 *
 * This function configures the CMPSSLITE module according to the provided configuration.
 *
 * @param cmpsslite Pointer to the CMPSSLITE register overlay
 * @param config Pointer to the CMPSSLITE configuration structure
 */
void DL_CMPSSLITE_init(CMPSS_LITE_Regs *cmpsslite, DL_CMPSSLITE_Config *config);

#ifdef __cplusplus
}
#endif

#endif /* DL_CMPSS_LITE_H */
/** @}*/
