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
 * @defgroup DL_GPIO_AM13E230X  Driverlib GPIO API
 * @ingroup DL_AM13E230X
 *
 *  The GPIO Driver Library allows full configuration of
 *  the GPIO module. The GPIO peripheral provides the user with a means
 *  to write data out and read data in to and from the device pins.
 *  It also provides a way to detect wakeup events while the device is in
 *  low power state.
 *
 * @{
 */

#ifndef DL_GPIO_H
#define DL_GPIO_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <soc.h>
#include <dl_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 * @brief GPIO Bit mask for a particular Pin.
 */
#define DL_GPIO_PIN(pinNum)        (((uint32_t)1U) << pinNum)
/**
 * \@brief Bit mask in Polarity and Input Config register based on Pin Number.
 */
#define DL_GPIO_BIT_MASK(pinNum)   (((uint64_t)0x3U) << (pinNum * 2U))
/**
 * \@brief Lower Register value in Polarity and Input Config register based on Pin Number.
 */
#define DL_GPIO_LOWER_REGVAL(val)  ((uint32_t)(val & 0xFFFFFFFFU))
/**
 * \@brief Higher Register value in Polarity and Input Config register based on Pin Number.
 */
#define DL_GPIO_HIGHER_REGVAL(val) ((uint32_t)((val & 0xFFFFFFFF00000000U) >> 32U))

/**
 * @name DL_GPIO_EDGE_POLARITY
 * @anchor DL_GPIO_EDGE_POLARITY
 * @{
 */
/*!
 * @brief Disable edge detection for a GPIO Pin.
 */
#define DL_GPIO_PIN_LOW_EDGE_DISABLE(pinNum)   (((uint64_t)0U) << (pinNum * 2U))
/*!
 * @brief Enable detection on rising edge for a GPIO Pin.
 */
#define DL_GPIO_PIN_LOW_EDGE_RISE(pinNum)      (((uint64_t)1U) << (pinNum * 2U))
/*!
 * @brief Enable detection on falling edge for a GPIO Pin.
 */
#define DL_GPIO_PIN_LOW_EDGE_FALL(pinNum)      (((uint64_t)2U) << (pinNum * 2U))
/*!
 * @brief Enable detection on both rising and falling edge for a GPIO Pin.
 */
#define DL_GPIO_PIN_LOW_EDGE_RISE_FALL(pinNum) (((uint64_t)3U) << (pinNum * 2U))
/** @}*/

/**
 * @name DL_GPIO_INPUT_FILTER
 * @anchor DL_GPIO_INPUT_FILTER
 * @{
 */
/*!
 * @brief Disable input filter for a GPIO Pin
 */
#define DL_GPIO_PIN_INPUT_FILTER_DISABLE(pinNum)  (((uint64_t)0U) << (pinNum * 2U))
/*!
 * @brief Enable input filter to 1 ulpclk period for a GPIO Pin
 */
#define DL_GPIO_PIN_INPUT_FILTER_1_CYCLE(pinNum)  (((uint64_t)1U) << (pinNum * 2U))
/*!
 * @brief Enable input filter to 3 ulpclk periods for a GPIO Pin
 */
#define DL_GPIO_PIN_INPUT_FILTER_3_CYCLES(pinNum) (((uint64_t)2U) << (pinNum * 2U))
/*!
 * @brief Enable input filter to 8 ulpclk periods for a GPIO Pin
 */
#define DL_GPIO_PIN_INPUT_FILTER_8_CYCLES(pinNum) (((uint64_t)3U) << (pinNum * 2U))
/** @}*/

/*! @brief DL_GPIO_INVERSION */
typedef enum
{
    /*! Enable Inversion */
    DL_GPIO_INVERSION_ENABLE  = IOMUX_PINCM_INV_ENABLE,
    /*! Disable Inversion */
    DL_GPIO_INVERSION_DISABLE = IOMUX_PINCM_INV_DISABLE,
} DL_GPIO_INVERSION;

/*! @brief DL_GPIO_DRIVE_STRENGTH */
typedef enum
{
    /*! Disable High-Drive Strength */
    DL_GPIO_DRIVE_STRENGTH_LOW  = IOMUX_PINCM_DRV_DRVVAL0,
    /*! Enable High-Drive (where allowed) */
    DL_GPIO_DRIVE_STRENGTH_HIGH = IOMUX_PINCM_DRV_DRVVAL1,
} DL_GPIO_DRIVE_STRENGTH;

/*! @brief DL_GPIO_RESISTOR */
typedef enum
{
    /*! Use no pull up/pull down resistors on pin */
    DL_GPIO_RESISTOR_NONE = (IOMUX_PINCM_PIPU_DISABLE | IOMUX_PINCM_PIPD_DISABLE),

    /*! Use a pull up resistor on the pin */
    DL_GPIO_RESISTOR_PULL_UP = (IOMUX_PINCM_PIPU_ENABLE | IOMUX_PINCM_PIPD_DISABLE),

    /*! Use a pull down resistor on the pin */
    DL_GPIO_RESISTOR_PULL_DOWN = (IOMUX_PINCM_PIPU_DISABLE | IOMUX_PINCM_PIPD_ENABLE)
} DL_GPIO_RESISTOR;

/*! @brief DL_GPIO_HYSTERESIS */
typedef enum
{
    /*! Enable Hysteresis on pin */
    DL_GPIO_HYSTERESIS_ENABLE  = IOMUX_PINCM_HYSTEN_ENABLE,
    /*! Disable Hysteresis on pin */
    DL_GPIO_HYSTERESIS_DISABLE = IOMUX_PINCM_HYSTEN_DISABLE,
} DL_GPIO_HYSTERESIS;

/*! @brief DL_GPIO_INPUTENABLE */
typedef enum
{
    /*! Enable Input block on pin */
    DL_GPIO_INPUT_ENABLE  = IOMUX_PINCM_INENA_ENABLE,
    /*! Disable Input block on pin */
    DL_GPIO_INPUT_DISABLE = IOMUX_PINCM_INENA_DISABLE,
} DL_GPIO_INPUTENABLE;

/*! @brief DL_GPIO_WAKEUP */
typedef enum
{
    /*! Wakeup enabled */
    DL_GPIO_WAKEUP_ENABLE  = IOMUX_PINCM_WUEN_ENABLE,
    /*! Wakeup disabled */
    DL_GPIO_WAKEUP_DISABLE = IOMUX_PINCM_WUEN_DISABLE,
    /*! Wakeup when pin changes to 0 */
    DL_GPIO_WAKEUP_ON_0    = (IOMUX_PINCM_WUEN_ENABLE | IOMUX_PINCM_WCOMP_MATCH0),
    /*! Wakeup when pin changes to 1 */
    DL_GPIO_WAKEUP_ON_1    = (IOMUX_PINCM_WUEN_ENABLE | IOMUX_PINCM_WCOMP_MATCH1),
} DL_GPIO_WAKEUP;

/*! @brief DL_GPIO_WAKEUP_COMPARE_VALUE */
typedef enum
{
    /*! Wakeup compare value of 0 */
    DL_GPIO_WAKEUP_COMPARE_VALUE_0 = IOMUX_PINCM_WCOMP_MATCH0,
    /*! Wakeup compare value of 1 */
    DL_GPIO_WAKEUP_COMPARE_VALUE_1 = IOMUX_PINCM_WCOMP_MATCH1,
} DL_GPIO_WAKEUP_COMPARE_VALUE;

/*! @brief DL_GPIO_HIZ */
typedef enum
{
    /*! Enable Hi-Z on pin */
    DL_GPIO_HIZ_ENABLE  = IOMUX_PINCM_HIZ1_ENABLE,
    /*! Disable Hi-Z on pin */
    DL_GPIO_HIZ_DISABLE = IOMUX_PINCM_HIZ1_DISABLE,
} DL_GPIO_HIZ;

/** @brief DL_GPIO_EVENT_ROUTE */
typedef enum
{
    /*! GPIO event route 1 */
    DL_GPIO_EVENT_ROUTE_1 = 0,
    /*! GPIO event route 2 */
    DL_GPIO_EVENT_ROUTE_2 = 1
} DL_GPIO_EVENT_ROUTE;

/** @brief DL_GPIO_PUBLISHER_INDEX */
typedef enum
{
    /*! GPIO Publisher index 0 */
    DL_GPIO_PUBLISHER_INDEX_0 = 0,
    /*! GPIO Publisher index 1 */
    DL_GPIO_PUBLISHER_INDEX_1 = 1
} DL_GPIO_PUBLISHER_INDEX;

/** @brief DL_GPIO_SUBSCRIBER_INDEX */
typedef enum
{
    /*! GPIO Subscriber index 0 */
    DL_GPIO_SUBSCRIBER_INDEX_0 = 0,
    /*! GPIO Subscriber index 1 */
    DL_GPIO_SUBSCRIBER_INDEX_1 = 1
} DL_GPIO_SUBSCRIBER_INDEX;

/** @brief DL_GPIO_SUBSCRIBER_OUT_POLICY */
typedef enum
{
    /*! GPIO is set */
    DL_GPIO_SUBSCRIBER_OUT_POLICY_SET    = GPIO_SUB0CFG_OUTPOLICY_SET,
    /*! GPIO is cleared */
    DL_GPIO_SUBSCRIBER_OUT_POLICY_CLEAR  = GPIO_SUB0CFG_OUTPOLICY_CLR,
    /*! GPIO is toggled */
    DL_GPIO_SUBSCRIBER_OUT_POLICY_TOGGLE = GPIO_SUB0CFG_OUTPOLICY_TOGGLE
} DL_GPIO_SUBSCRIBER_OUT_POLICY;

/** @brief DL_GPIO_SUBSCRIBERx_PIN */
typedef enum
{
    /*! Selects DIO 0 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_0  = 0x00000000,
    /*! Selects DIO 1 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_1  = 0x00010000,
    /*! Selects DIO 2 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_2  = 0x00020000,
    /*! Selects DIO 3 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_3  = 0x00030000,
    /*! Selects DIO 4 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_4  = 0x00040000,
    /*! Selects DIO 5 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_5  = 0x00050000,
    /*! Selects DIO 6 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_6  = 0x00060000,
    /*! Selects DIO 7 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_7  = 0x00070000,
    /*! Selects DIO 8 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_8  = 0x00080000,
    /*! Selects DIO 9 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_9  = 0x00090000,
    /*! Selects DIO 10 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_10 = 0x000A0000,
    /*! Selects DIO 11 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_11 = 0x000B0000,
    /*! Selects DIO 12 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_12 = 0x000C0000,
    /*! Selects DIO 13 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_13 = 0x000D0000,
    /*! Selects DIO 14 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_14 = 0x000E0000,
    /*! Selects DIO 15 when Subscriber index 0 is selected */
    DL_GPIO_SUBSCRIBER0_PIN_15 = 0x000F0000,
    /*! Selects DIO 16 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_16 = 0x00000000,
    /*! Selects DIO 17 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_17 = 0x00010000,
    /*! Selects DIO 18 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_18 = 0x00020000,
    /*! Selects DIO 19 when Subscriber index 1  is selected */
    DL_GPIO_SUBSCRIBER1_PIN_19 = 0x00030000,
    /*! Selects DIO 20 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_20 = 0x00040000,
    /*! Selects DIO 21 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_21 = 0x00050000,
    /*! Selects DIO 22 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_22 = 0x00060000,
    /*! Selects DIO 23 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_23 = 0x00070000,
    /*! Selects DIO 24 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_24 = 0x00080000,
    /*! Selects DIO 25 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_25 = 0x00090000,
    /*! Selects DIO 26 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_26 = 0x000A0000,
    /*! Selects DIO 27 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_27 = 0x000B0000,
    /*! Selects DIO 28 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_28 = 0x000C0000,
    /*! Selects DIO 29 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_29 = 0x000D0000,
    /*! Selects DIO 30 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_30 = 0x000E0000,
    /*! Selects DIO 31 when Subscriber index 1 is selected */
    DL_GPIO_SUBSCRIBER1_PIN_31 = 0x000F0000
} DL_GPIO_SUBSCRIBERx_PIN;

/*! @brief DL_GPIO_IIDX */
typedef enum
{
    /*! Interrupt index for no interrupt  */
    DL_GPIO_IIDX_NO_INTR = GPIO_CPU_INT_IIDX_STAT_NO_INTR,
    /*! Interrupt index for GPIO DIO0 */
    DL_GPIO_IIDX_DIO0    = GPIO_CPU_INT_IIDX_STAT_DIO0,
    /*! Interrupt index for GPIO DIO1 */
    DL_GPIO_IIDX_DIO1    = GPIO_CPU_INT_IIDX_STAT_DIO1,
    /*! Interrupt index for GPIO DIO2 */
    DL_GPIO_IIDX_DIO2    = GPIO_CPU_INT_IIDX_STAT_DIO2,
    /*! Interrupt index for GPIO DIO3 */
    DL_GPIO_IIDX_DIO3    = GPIO_CPU_INT_IIDX_STAT_DIO3,
    /*! Interrupt index for GPIO DIO4 */
    DL_GPIO_IIDX_DIO4    = GPIO_CPU_INT_IIDX_STAT_DIO4,
    /*! Interrupt index for GPIO DIO5 */
    DL_GPIO_IIDX_DIO5    = GPIO_CPU_INT_IIDX_STAT_DIO5,
    /*! Interrupt index for GPIO DIO6 */
    DL_GPIO_IIDX_DIO6    = GPIO_CPU_INT_IIDX_STAT_DIO6,
    /*! Interrupt index for GPIO DIO7 */
    DL_GPIO_IIDX_DIO7    = GPIO_CPU_INT_IIDX_STAT_DIO7,
    /*! Interrupt index for GPIO DIO8 */
    DL_GPIO_IIDX_DIO8    = GPIO_CPU_INT_IIDX_STAT_DIO8,
    /*! Interrupt index for GPIO DIO9 */
    DL_GPIO_IIDX_DIO9    = GPIO_CPU_INT_IIDX_STAT_DIO9,
    /*! Interrupt index for GPIO DIO10 */
    DL_GPIO_IIDX_DIO10   = GPIO_CPU_INT_IIDX_STAT_DIO10,
    /*! Interrupt index for GPIO DIO11 */
    DL_GPIO_IIDX_DIO11   = GPIO_CPU_INT_IIDX_STAT_DIO11,
    /*! Interrupt index for GPIO DIO12 */
    DL_GPIO_IIDX_DIO12   = GPIO_CPU_INT_IIDX_STAT_DIO12,
    /*! Interrupt index for GPIO DIO13 */
    DL_GPIO_IIDX_DIO13   = GPIO_CPU_INT_IIDX_STAT_DIO13,
    /*! Interrupt index for GPIO DIO14 */
    DL_GPIO_IIDX_DIO14   = GPIO_CPU_INT_IIDX_STAT_DIO14,
    /*! Interrupt index for GPIO DIO15 */
    DL_GPIO_IIDX_DIO15   = GPIO_CPU_INT_IIDX_STAT_DIO15,
    /*! Interrupt index for GPIO DIO16 */
    DL_GPIO_IIDX_DIO16   = GPIO_CPU_INT_IIDX_STAT_DIO16,
    /*! Interrupt index for GPIO DIO17 */
    DL_GPIO_IIDX_DIO17   = GPIO_CPU_INT_IIDX_STAT_DIO17,
    /*! Interrupt index for GPIO DIO18 */
    DL_GPIO_IIDX_DIO18   = GPIO_CPU_INT_IIDX_STAT_DIO18,
    /*! Interrupt index for GPIO DIO19 */
    DL_GPIO_IIDX_DIO19   = GPIO_CPU_INT_IIDX_STAT_DIO19,
    /*! Interrupt index for GPIO DIO20 */
    DL_GPIO_IIDX_DIO20   = GPIO_CPU_INT_IIDX_STAT_DIO20,
    /*! Interrupt index for GPIO DIO21 */
    DL_GPIO_IIDX_DIO21   = GPIO_CPU_INT_IIDX_STAT_DIO21,
    /*! Interrupt index for GPIO DIO22 */
    DL_GPIO_IIDX_DIO22   = GPIO_CPU_INT_IIDX_STAT_DIO22,
    /*! Interrupt index for GPIO DIO23 */
    DL_GPIO_IIDX_DIO23   = GPIO_CPU_INT_IIDX_STAT_DIO23,
    /*! Interrupt index for GPIO DIO24 */
    DL_GPIO_IIDX_DIO24   = GPIO_CPU_INT_IIDX_STAT_DIO24,
    /*! Interrupt index for GPIO DIO25 */
    DL_GPIO_IIDX_DIO25   = GPIO_CPU_INT_IIDX_STAT_DIO25,
    /*! Interrupt index for GPIO DIO26 */
    DL_GPIO_IIDX_DIO26   = GPIO_CPU_INT_IIDX_STAT_DIO26,
    /*! Interrupt index for GPIO DIO27 */
    DL_GPIO_IIDX_DIO27   = GPIO_CPU_INT_IIDX_STAT_DIO27,
    /*! Interrupt index for GPIO DIO28 */
    DL_GPIO_IIDX_DIO28   = GPIO_CPU_INT_IIDX_STAT_DIO28,
    /*! Interrupt index for GPIO DIO29 */
    DL_GPIO_IIDX_DIO29   = GPIO_CPU_INT_IIDX_STAT_DIO29,
    /*! Interrupt index for GPIO DIO30 */
    DL_GPIO_IIDX_DIO30   = GPIO_CPU_INT_IIDX_STAT_DIO30,
    /*! Interrupt index for GPIO DIO31 */
    DL_GPIO_IIDX_DIO31   = GPIO_CPU_INT_IIDX_STAT_DIO31
} DL_GPIO_IIDX;

/*! @brief DL_GPIO_PERIPHERAL_CONNECTION_VALUE */
typedef enum
{
    /* Connect peripheral from the IOCELL */
    DL_GPIO_PERIPHERAL_CONNECTED   = IOMUX_PINCM_PC_CONNECTED,
    /* Disconnect peripheral from the IOCELL */
    DL_GPIO_PERIPHERAL_UNCONNECTED = IOMUX_PINCM_PC_UNCONNECTED,
} DL_GPIO_PERIPHERAL_CONNECTION_VALUE;

/*! @brief DL_GPIO_PULLUP_VALUE */
typedef enum
{
    /* Enable pullup */
    DL_GPIO_PULLUP_ENABLE  = IOMUX_PINCM_PIPU_ENABLE,
    /* Disable pullup */
    DL_GPIO_PULLUP_DISABLE = IOMUX_PINCM_PIPU_DISABLE,
} DL_GPIO_PULLUP_VALUE;

/*! @brief DL_GPIO_PULLDOWN_VALUE */
typedef enum
{
    /* Enable pulldown */
    DL_GPIO_PULLDOWN_ENABLE  = IOMUX_PINCM_PIPD_ENABLE,
    /* Disable pulldown */
    DL_GPIO_PULLDOWN_DISABLE = IOMUX_PINCM_PIPD_DISABLE,
} DL_GPIO_PULLDOWN_VALUE;

/* =========================================================================== */
/*                             IOMUX Functions                                 */
/* =========================================================================== */

/**
 *  @brief      Configures a pin as a basic GPIO output
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 */
__STATIC_INLINE void DL_GPIO_initDigitalOutput(uint32_t pincmIndex)
{
    /* GPIO functionality is always a pin function of 0x00000001 */
    IOMUX->SECCFG.PINCM[pincmIndex] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t)0x00000001));
}

/**
 *  @brief      Configures a pin as a GPIO output and configures additional functionalities
 *
 *  @param[in]  pincmIndex        The PINCM register index that maps to the target
 *                                GPIO pin.
 *  @param[in]  inversion         Configure Inversion of the pin output. One of @ref
 *                                DL_GPIO_INVERSION.
 *  @param[in]  internalResistor  Internal resistor to use. One of
 *                                @ref DL_GPIO_RESISTOR.
 *  @param[in]  driveStrength     Configure Drive strength for the pin. One of @ref
 *                                DL_GPIO_DRIVE_STRENGTH.
 *  @param[in]  hiZ               Enable/disable Hi-Z for the pin. One of
 *                                @ref DL_GPIO_HIZ.
 */
__STATIC_INLINE void DL_GPIO_initDigitalOutputFeatures(uint32_t pincmIndex, DL_GPIO_INVERSION inversion,
                                                       DL_GPIO_RESISTOR       internalResistor,
                                                       DL_GPIO_DRIVE_STRENGTH driveStrength, DL_GPIO_HIZ hiZ)
{
    /* GPIO functionality is always a pin function of 0x00000001 */
    IOMUX->SECCFG.PINCM[pincmIndex] = IOMUX_PINCM_PC_CONNECTED | ((uint32_t)0x00000001) | (uint32_t)inversion |
                                      (uint32_t)internalResistor | (uint32_t)driveStrength | (uint32_t)hiZ;
}

/**
 *  @brief      Configures a pin as a basic GPIO input
 *
 *  Configures the pin as a basic GPIO input. If you want to use additional
 *  features of the input mode, refer to @ref DL_GPIO_initDigitalInputFeatures.
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 */
__STATIC_INLINE void DL_GPIO_initDigitalInput(uint32_t pincmIndex)
{
    /* GPIO functionality is always a pin function of 0x00000001 */
    IOMUX->SECCFG.PINCM[pincmIndex] = IOMUX_PINCM_INENA_ENABLE | IOMUX_PINCM_PC_CONNECTED | ((uint32_t)0x00000001);
}

/**
 *  @brief      Configures a pin as a GPIO input
 *
 *  @param[in]  pincmIndex        The PINCM register index that maps to the target
 *                                GPIO pin.
 *  @param[in]  inversion         Enable Inversion of the pin input. One of @ref
 *                                DL_GPIO_INVERSION.
 *  @param[in]  internalResistor  Internal resistor to use. One of @ref
 *                                DL_GPIO_RESISTOR.
 *  @param[in]  hysteresis        Enable/disable Hysteresis on the pin. One of
 *                                @ref DL_GPIO_HYSTERESIS.
 *  @param[in]  wakeup            Configure wakeup behavior for the pin. One of
 *                                @ref DL_GPIO_WAKEUP.
 */
__STATIC_INLINE void DL_GPIO_initDigitalInputFeatures(uint32_t pincmIndex, DL_GPIO_INVERSION inversion,
                                                      DL_GPIO_RESISTOR internalResistor, DL_GPIO_HYSTERESIS hysteresis,
                                                      DL_GPIO_WAKEUP wakeup)
{
    /* GPIO functionality is always a pin function of 0x00000001 */
    IOMUX->SECCFG.PINCM[pincmIndex] = IOMUX_PINCM_INENA_ENABLE | IOMUX_PINCM_PC_CONNECTED | ((uint32_t)0x00000001) |
                                      (uint32_t)inversion | (uint32_t)internalResistor | (uint32_t)hysteresis |
                                      (uint32_t)wakeup;
}

/**
 *  @brief      Configure a pin to operate with peripheral output functionality
 *
 *  @param[in]  pincmIndex The PINCM register index that maps to the target
 *                         pin to configure the peripheral functionality for
 *  @param[in]  function   Function to configure the pin for. See definition
 *                         of IOMUX_PINCMx_PF_xxx in the device header file.
 */
__STATIC_INLINE void DL_GPIO_initPeripheralOutputFunction(uint32_t pincmIndex, uint32_t function)
{
    IOMUX->SECCFG.PINCM[pincmIndex] = function | IOMUX_PINCM_PC_CONNECTED;
}

/**
 *  @brief      Configure a pin to operate with peripheral output functionality with optional features
 *
 *  @param[in]  pincmIndex The PINCM register index that maps to the target
 *                         pin to configure the peripheral functionality for
 *  @param[in]  function          Function to configure the pin for. Check
 *                         definition of IOMUX_PINCMx_PF_xxx in the device
 *                         header file.
 *  @param[in]  inversion         Enable Inversion of the pin output. One of @ref
 *                                DL_GPIO_INVERSION.
 *  @param[in]  internalResistor  Internal resistor to use. One of
 *                                @ref DL_GPIO_RESISTOR.
 *  @param[in]  driveStrength     Enable High-Drive for the pin. One of @ref
 *                                DL_GPIO_DRIVE_STRENGTH.
 *  @param[in]  hiZ               Enable/disable Hi-Z for the pin. One of
 *                                @ref DL_GPIO_HIZ.
 */
__STATIC_INLINE void DL_GPIO_initPeripheralOutputFunctionFeatures(uint32_t pincmIndex, uint32_t function,
                                                                  DL_GPIO_INVERSION      inversion,
                                                                  DL_GPIO_RESISTOR       internalResistor,
                                                                  DL_GPIO_DRIVE_STRENGTH driveStrength, DL_GPIO_HIZ hiZ)
{
    IOMUX->SECCFG.PINCM[pincmIndex] = function | IOMUX_PINCM_PC_CONNECTED | (uint32_t)inversion |
                                      (uint32_t)internalResistor | (uint32_t)driveStrength | (uint32_t)hiZ;
}

/**
 *  @brief      Configure a pin to operate with peripheral input functionality
 *
 *  @param[in]  pincmIndex The PINCM register index that maps to the target
 *                         pin to configure the peripheral functionality for
 *  @param[in]  function   Function to configure the pin for. See definition
 *                         of IOMUX_PINCMx_PF_xxx in the device header file.
 */
__STATIC_INLINE void DL_GPIO_initPeripheralInputFunction(uint32_t pincmIndex, uint32_t function)
{
    IOMUX->SECCFG.PINCM[pincmIndex] = function | IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM_INENA_ENABLE;
}

/**
 *  @brief      Configure a pin to operate with peripheral input functionality with optional features
 *
 *  @param[in]  pincmIndex The PINCM register index that maps to the target
 *                         pin to configure the peripheral functionality for
 *  @param[in]  function   Function to configure the pin for. See definition
 *                         of IOMUX_PINCMx_PF_xxx in the device header file.
 *  @param[in]  inversion         Enable Inversion of the pin input. One of @ref
 *                                DL_GPIO_INVERSION.
 *  @param[in]  internalResistor  Internal resistor to use. One of @ref
 *                                DL_GPIO_RESISTOR.
 *  @param[in]  hysteresis        Enable/disable Hystersis on the pin. One of
 *                                @ref DL_GPIO_HYSTERESIS.
 *  @param[in]  wakeup            Configure wakeup behavior for the pin. One of
 *                                @ref DL_GPIO_WAKEUP.
 */
__STATIC_INLINE void DL_GPIO_initPeripheralInputFunctionFeatures(uint32_t pincmIndex, uint32_t function,
                                                                 DL_GPIO_INVERSION  inversion,
                                                                 DL_GPIO_RESISTOR   internalResistor,
                                                                 DL_GPIO_HYSTERESIS hysteresis, DL_GPIO_WAKEUP wakeup)
{
    IOMUX->SECCFG.PINCM[pincmIndex] = function | IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM_INENA_ENABLE |
                                      (uint32_t)inversion | (uint32_t)internalResistor | (uint32_t)hysteresis |
                                      (uint32_t)wakeup;
}

/**
 *  @brief      Configure a pin to operate with analog functionality
 *
 *  @param[in]  pincmIndex The PINCM register index that maps to the target
 *                         pin to configure the analog functionality for
 *
 */
__STATIC_INLINE void DL_GPIO_initPeripheralAnalogFunction(uint32_t pincmIndex)
{
    IOMUX->SECCFG.PINCM[pincmIndex] = IOMUX_PINCM_PC_UNCONNECTED;
}

/**
 *  @brief Set GPIO pin's wakeup enable bit.
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 */
__STATIC_INLINE void DL_GPIO_enableWakeUp(uint32_t pincmIndex)
{
    IOMUX->SECCFG.PINCM[pincmIndex] |= IOMUX_PINCM_WUEN_MASK;
}

/**
 *  @brief Clear GPIO pin's wakeup enable bit.
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 */
__STATIC_INLINE void DL_GPIO_disableWakeUp(uint32_t pincmIndex)
{
    IOMUX->SECCFG.PINCM[pincmIndex] &= ~(IOMUX_PINCM_WUEN_MASK);
}

/**
 *  @brief Returns if GPIO pin's wake up bit is enabled.
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     True if wake up enabled on GPIO pin.
 */
__STATIC_INLINE bool DL_GPIO_isWakeUpEnabled(uint32_t pincmIndex)
{
    return ((IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_WUEN_MASK) == IOMUX_PINCM_WUEN_ENABLE);
}

/**
 *  @brief Set the compare value to use for wake for the specified pin
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *  @param[in]  value       The wakeup compare value to set.
 *                          One of @ref DL_GPIO_WAKEUP_COMPARE_VALUE
 */
__STATIC_INLINE void DL_GPIO_setWakeupCompareValue(uint32_t pincmIndex, DL_GPIO_WAKEUP_COMPARE_VALUE value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_WCOMP_MASK);
}

/**
 *  @brief Set the Input Enable bits
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *  @param[in]  value       THe input enable bits value
 *                          One of @ref DL_GPIO_INPUTENABLE
 */
__STATIC_INLINE void DL_GPIO_setInputEnableBit(uint32_t pincmIndex, DL_GPIO_INPUTENABLE value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_INENA_MASK);
}

/**
 *  @brief Get the compare value to use for wake for the specified pin
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     The wakeup compare value for the specified pin
 *
 *  @retval     One of @ref DL_GPIO_WAKEUP_COMPARE_VALUE
 */
__STATIC_INLINE DL_GPIO_WAKEUP_COMPARE_VALUE DL_GPIO_getWakeupCompareValue(uint32_t pincmIndex)
{
    uint32_t value = IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_WCOMP_MASK;

    return (DL_GPIO_WAKEUP_COMPARE_VALUE)(value);
}

/**
 *  @brief Checks if the GPIO pin's Wake State bit is active.
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     True if 0x00002000U, False if 0x00000000U.
 */
__STATIC_INLINE bool DL_GPIO_isWakeStateGenerated(uint32_t pincmIndex)
{
    return ((IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_WAKESTAT_MASK) == IOMUX_PINCM_WAKESTAT_ENABLE);
}

/**
 *  @brief      Enable Hi-Z for the pin
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin
 */
__STATIC_INLINE void DL_GPIO_enableHiZ(uint32_t pincmIndex)
{
    IOMUX->SECCFG.PINCM[pincmIndex] |= IOMUX_PINCM_HIZ1_ENABLE;
}

/**
 *  @brief      Disable Hi-Z for the pin
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin
 */
__STATIC_INLINE void DL_GPIO_disableHiZ(uint32_t pincmIndex)
{
    IOMUX->SECCFG.PINCM[pincmIndex] &= ~(IOMUX_PINCM_HIZ1_ENABLE);
}

/**
 *  @brief      Read the PINCM Register value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin
 */
__STATIC_INLINE uint32_t DL_GPIO_readPincmReg(uint32_t pincmIndex)
{
    return (IOMUX->SECCFG.PINCM[pincmIndex]);
}

/* ============================================================================= */
/*                               GPIO Functions                                  */
/* ============================================================================= */

/**
 * @brief Enables the Peripheral Write Enable (PWREN) register for the GPIO
 *
 *  Before any peripheral registers can be configured by software, the
 *  peripheral itself must be enabled by writing the ENABLE bit together with
 *  the appropriate KEY value to the peripheral's PWREN register.
 *
 * @param gpio        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_GPIO_enablePower(GPIO_Regs* gpio)
{
    gpio->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);
}

/**
 * @brief Disables the Peripheral Write Enable (PWREN) register for the GPIO
 *
 *  When the PWREN.ENABLE bit is cleared, the peripheral's registers are not
 *  accessible for read/write operations.
 *
 *  @note This API does not provide large power savings.
 *
 * @param gpio        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_GPIO_disablePower(GPIO_Regs* gpio)
{
    gpio->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_DISABLE);
}

/**
 * @brief Returns if the Peripheral Write Enable (PWREN) register for the GPIO
 *        is enabled
 *
 *  Before any peripheral registers can be configured by software, the
 *  peripheral itself must be enabled by writing the ENABLE bit together with
 *  the appropriate KEY value to the peripheral's PWREN register.
 *
 *  When the PWREN.ENABLE bit is cleared, the peripheral's registers are not
 *  accessible for read/write operations.
 *
 * @param gpio        Pointer to the register overlay for the peripheral
 *
 * @return true if peripheral register access is enabled
 * @return false if peripheral register access is disabled
 */
__STATIC_INLINE bool DL_GPIO_isPowerEnabled(GPIO_Regs* gpio)
{
    return ((gpio->GPRCM.PWREN & GPIO_PWREN_ENABLE_MASK) == GPIO_PWREN_ENABLE_ENABLE);
}

/**
 * @brief Resets gpio peripheral
 *
 * @param gpio        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_GPIO_reset(GPIO_Regs* gpio)
{
    gpio->GPRCM.RSTCTL = (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT);
}

/**
 * @brief Returns if gpio peripheral was reset
 *
 * @param gpio        Pointer to the register overlay for the peripheral
 *
 * @return true if peripheral was reset
 * @return false if peripheral wasn't reset
 *
 */
__STATIC_INLINE bool DL_GPIO_isReset(GPIO_Regs* gpio)
{
    return ((gpio->GPRCM.STAT & GPIO_STAT_RESETSTKY_MASK) == GPIO_STAT_RESETSTKY_RESET);
}

/**
 *  @brief      Read a group of GPIO pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to read. Bitwise OR of @ref DL_GPIO_PIN.
 *
 *  @return     The pins (from the selection) that are currently high
 *
 *  @retval     Bitwise OR of @ref DL_GPIO_PIN of pins that are currently high
 *              from the input selection.
 */
__STATIC_INLINE uint32_t DL_GPIO_readPins(GPIO_Regs* gpio, uint32_t pins)
{
    return (gpio->DIN31_0 & pins);
}

/**
 *  @brief      Write a group of GPIO pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to write. All enabled GPIO pins will be set to
 *                    the equivalent bit value in pins.
 */
__STATIC_INLINE void DL_GPIO_writePins(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->DOUT31_0 = pins;
}

/**
 *  @brief      Update the value of one or more GPIO pins
 *
 *  @param[in]  gpio      Pointer to the register overlay for the peripheral
 *  @param[in]  pinsMask  The GPIO pin(s) you want to update. Bitwise OR of
 *                        @ref DL_GPIO_PIN.
 *  @param[in]  pinsVal   Value(s) for the GPIO pin(s) you want to update.
 *                        Only the values for pins specified in pinsMask will
 *                        change.
 */
__STATIC_INLINE void DL_GPIO_writePinsVal(GPIO_Regs* gpio, uint32_t pinsMask, uint32_t pinsVal)
{
    uint32_t doutVal  = gpio->DOUT31_0;
    doutVal          &= ~pinsMask;
    doutVal          |= (pinsVal & pinsMask);
    gpio->DOUT31_0    = doutVal;
}

/**
 *  @brief      Set a group of GPIO pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to set high. Bitwise OR of @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_setPins(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->DOUTSET31_0 = pins;
}

/**
 *  @brief      Clear a group of GPIO pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to clear. Bitwise OR of @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_clearPins(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->DOUTCLR31_0 = pins;
}

/**
 *  @brief      Toggle a group of GPIO pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to toggle. Bitwise OR of @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_togglePins(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->DOUTTGL31_0 = pins;
}

/**
 *  @brief      Enable output on a group of GPIO pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to enable output. Bitwise OR of @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_enableOutput(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->DOESET31_0 = pins;
}

/**
 *  @brief      Disable output on a group of GPIO pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to disable output. Bitwise OR of @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_disableOutput(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->DOECLR31_0 = pins;
}

/**
 *  @brief      Enable DMA access on a group of pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to enable DMA access on. Bitwise OR of @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_enableDMAAccess(GPIO_Regs* gpio, uint32_t pins)
{
    DL_Common_updateReg(&gpio->DMAMASK, pins, pins);
}

/**
 *  @brief      Disable DMA access on a group of pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to disable DMA access on. Bitwise OR of @ref
 *                    DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_disableDMAAccess(GPIO_Regs* gpio, uint32_t pins)
{
    DL_Common_updateReg(&gpio->DMAMASK, 0x00000000, pins);
}

/**
 *  @brief      Check if DMA access is enabled on a group of pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Pins to check DMA access on. Bitwise OR of @ref
 *                    DL_GPIO_PIN.
 *
 *  @return     Which pins of the requested group have DMA access enabled
 *
 *  @retval     Bitwise OR of @ref DL_GPIO_PIN values
 */
__STATIC_INLINE uint32_t DL_GPIO_isDMAccessEnabled(GPIO_Regs* gpio, uint32_t pins)
{
    return (gpio->DMAMASK & pins);
}

/**
 * @brief      Set the polarity of group of pins
 *
 * @param[in]  gpio          Pointer to the register overlay for the peripheral
 * @param[in]  polarity      Bitwise OR of @ref DL_GPIO_EDGE_POLARITY for
 *                           required pins
 * @param[in]  polarityMask  Bitwise OR of @ref DL_GPIO_BIT_MASK for
 *                           required pins
 */
__STATIC_INLINE void DL_GPIO_setPinsPolarity(GPIO_Regs* gpio, uint64_t polarity, uint64_t polarityMask)
{
    DL_Common_updateReg(&gpio->POLARITY15_0, DL_GPIO_LOWER_REGVAL(polarity), DL_GPIO_LOWER_REGVAL(polarityMask));
    DL_Common_updateReg(&gpio->POLARITY31_16, DL_GPIO_HIGHER_REGVAL(polarity), DL_GPIO_HIGHER_REGVAL(polarityMask));
}

/**
 * @brief      Get the polarity of all GPIO pins
 *
 * @param[in]  gpio     Pointer to the register overlay for the peripheral
 *
 * @retval     Polarity setting with bitwise OR of @ref DL_GPIO_EDGE_POLARITY
 *             for all GPIO pins
 *
 */
__STATIC_INLINE uint64_t DL_GPIO_getPinsPolarity(GPIO_Regs* gpio)
{
    uint64_t lowerRegVal  = (uint64_t)(gpio->POLARITY15_0);
    uint64_t higherRegVal = (uint64_t)(gpio->POLARITY31_16);

    return (lowerRegVal | (higherRegVal << 32U));
}

/**
 * @brief      Set the input filter of group of pins
 *
 * @param[in]  gpio          Pointer to the register overlay for the peripheral
 * @param[in]  filter        Bitwise OR of @ref DL_GPIO_INPUT_FILTER for
 *                           required pins
 * @param[in]  filterMask    Bitwise OR of @ref DL_GPIO_BIT_MASK for
 *                           required pins
 */
__STATIC_INLINE void DL_GPIO_setPinsInputFilter(GPIO_Regs* gpio, uint64_t filter, uint64_t filterMask)
{
    DL_Common_updateReg(&gpio->FILTEREN15_0, DL_GPIO_LOWER_REGVAL(filter), DL_GPIO_LOWER_REGVAL(filterMask));
    DL_Common_updateReg(&gpio->FILTEREN31_16, DL_GPIO_HIGHER_REGVAL(filter), DL_GPIO_HIGHER_REGVAL(filterMask));
}

/**
 * @brief      Get the input filter for all GPIO pins
 *
 * @param[in]  gpio     Pointer to the register overlay for the peripheral
 *
 * @retval     Input filter setting with bitwise OR of @ref DL_GPIO_INPUT_FILTER
 *             for all GPIO pins
 *
 */
__STATIC_INLINE uint64_t DL_GPIO_getPinsInputFilter(GPIO_Regs* gpio)
{
    uint64_t lowerRegVal  = (uint64_t)(gpio->FILTEREN15_0);
    uint64_t higherRegVal = (uint64_t)(gpio->FILTEREN31_16);

    return (lowerRegVal | (higherRegVal << 32U));
}

/**
 *  @brief      Enable Global Fast Wake
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_GPIO_enableGlobalFastWake(GPIO_Regs* gpio)
{
    gpio->CTL |= GPIO_CTL_FASTWAKEONLY_GLOBAL_EN;
}

/**
 *  @brief      Disable Global Fast Wake
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_GPIO_disableGlobalFastWake(GPIO_Regs* gpio)
{
    gpio->CTL &= ~GPIO_CTL_FASTWAKEONLY_GLOBAL_EN;
}

/**
 *  @brief      Enable fast wake for pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Bit mask of pins to enable fast-wake feature. Bitwise OR
 *                    of @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_enableFastWakePins(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->FASTWAKE |= pins;
}

/**
 *  @brief      Disable fast wake for pins
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Bit mask of pins to disable fast-wake feature. Bitwise OR
 *                    of @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_disableFastWakePins(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->FASTWAKE &= ~(pins);
}

/**
 *  @brief      Check which pins have fast wake feature enabled
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Bit mask of pins to check. Bitwise OR of @ref DL_GPIO_PIN.
 *
 *  @return     Which of the requested GPIO pins have fast wake enabled
 *
 *  @retval     Bitwise OR of @ref DL_GPIO_PIN values
 */
__STATIC_INLINE uint32_t DL_GPIO_getEnabledFastWakePins(GPIO_Regs* gpio, uint32_t pins)
{
    return (gpio->FASTWAKE & pins);
}

/**
 *  @brief      Enable GPIO interrupts
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Bit mask of interrupts to enable. Bitwise OR of
 *                    @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_enableInterrupt(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->CPU_INT.IMASK |= pins;
}

/**
 *  @brief      Disable GPIO interrupts
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Bit mask of interrupts to disable. Bitwise OR of
 *                    @ref DL_GPIO_PIN.
 */
__STATIC_INLINE void DL_GPIO_disableInterrupt(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->CPU_INT.IMASK &= ~(pins);
}

/**
 *  @brief      Check which GPIO interrupts are enabled
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Bit mask of interrupts to check. Bitwise OR of
 *                    @ref DL_GPIO_PIN.
 *
 *  @return     Which of the requested GPIO interrupts are enabled
 *
 *  @retval     Bitwise OR of @ref DL_GPIO_PIN values
 */
__STATIC_INLINE uint32_t DL_GPIO_getEnabledInterrupts(GPIO_Regs* gpio, uint32_t pins)
{
    return (gpio->CPU_INT.IMASK & pins);
}

/**
 *  @brief      Check interrupt flag of enabled GPIO interrupts
 *
 *  Checks if any of the GPIO interrupts that were previously enabled are
 *  pending.
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Bit mask of interrupts to check. Bitwise OR of
 *                    @ref DL_GPIO_PIN.
 *
 *  @return     Which of the requested GPIO interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_GPIO_PIN values
 *
 *  @sa         DL_GPIO_enableInterrupt
 */
__STATIC_INLINE uint32_t DL_GPIO_getEnabledInterruptStatus(GPIO_Regs* gpio, uint32_t pins)
{
    return (gpio->CPU_INT.MIS & pins);
}

/**
 *  @brief      Set interrupt flag of any GPIO
 *
 *  Manually set a GPIO interrupt to be pending
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *
 *  @param[in]  pins  Bit mask of interrupts to set. Bitwise OR of
 *                    @ref DL_GPIO_PIN.
 *
 */
__STATIC_INLINE void DL_GPIO_setInterrupt(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->CPU_INT.ISET = pins;
}

/**
 *  @brief      Check interrupt flag of any GPIO interrupt
 *
 *  Checks if any of the GPIO interrupts are pending. Interrupts do not have to
 *  be previously enabled.
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *
 *  @param[in]  pins  Bit mask of interrupts to check. Bitwise OR of
 *                    @ref DL_GPIO_PIN.
 *
 *  @return     Which of the requested GPIO interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_GPIO_PIN values
 */
__STATIC_INLINE uint32_t DL_GPIO_getRawInterruptStatus(GPIO_Regs* gpio, uint32_t pins)
{
    return (gpio->CPU_INT.RIS & pins);
}

/**
 *  @brief      Get highest priority pending GPIO interrupt
 *
 *  Checks if any of the GPIO interrupts are pending. Interrupts do not have to
 *  be previously enabled.
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *
 *  @return     The highest priority pending GPIO interrupt
 *
 *  @retval     One of @ref DL_GPIO_IIDX
 */
__STATIC_INLINE DL_GPIO_IIDX DL_GPIO_getPendingInterrupt(GPIO_Regs* gpio)
{
    return (DL_GPIO_IIDX)(gpio->CPU_INT.IIDX);
}

/**
 *  @brief      Clear pending GPIO interrupts
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  pins  Bit mask of interrupts to clear. Bitwise OR of
 *                    @ref DL_GPIO_PIN.
 *
 */
__STATIC_INLINE void DL_GPIO_clearInterruptStatus(GPIO_Regs* gpio, uint32_t pins)
{
    gpio->CPU_INT.ICLR = pins;
}

/**
 * @brief Configures GPIO subscriber. This API preserves enable/disbale status
 *        of subscriber.
 *
 * @param[in] gpio     Pointer to the register overlay for the peripheral
 * @param[in] index    Specifies the subscriber event index to be configured
 * @param[in] policy   Specifies the the GPIO behavior when the subscriber
 *                     receives publisher event.
 * @param[in] pinIndex Specifies the GPIO bit number which will be targeted by
 *                     the subscriber action.
 *
 */
__STATIC_INLINE void DL_GPIO_configSubscriber(GPIO_Regs* gpio, DL_GPIO_SUBSCRIBER_INDEX index,
                                              DL_GPIO_SUBSCRIBER_OUT_POLICY policy, DL_GPIO_SUBSCRIBERx_PIN pinIndex)

{
    volatile uint32_t* pReg = &gpio->SUB0CFG;

    pReg += ((uint32_t)index << 3);

    DL_Common_updateReg(pReg, ((uint32_t)pinIndex | (uint32_t)policy),
                        (GPIO_SUB0CFG_INDEX_MASK | GPIO_SUB1CFG_OUTPOLICY_MASK));
}

/**
 * @brief Enables GPIO subscriber
 *
 * @param[in] gpio     Pointer to the register overlay for the peripheral
 * @param[in] index    Specifies the subscriber event index to be configured
 *
 */
__STATIC_INLINE void DL_GPIO_enableSubscriber(GPIO_Regs* gpio, DL_GPIO_SUBSCRIBER_INDEX index)
{
    volatile uint32_t* pReg = &gpio->SUB0CFG;

    pReg    += ((uint32_t)index << 3);
    *(pReg) |= (GPIO_SUB1CFG_ENABLE_SET);
}

/**
 * @brief Disables GPIO subscriber
 *
 * @param[in] gpio     Pointer to the register overlay for the peripheral
 * @param[in] index    Specifies the subscriber event index to be configured
 *
 */
__STATIC_INLINE void DL_GPIO_disableSubscriber(GPIO_Regs* gpio, DL_GPIO_SUBSCRIBER_INDEX index)
{
    volatile uint32_t* pReg = &gpio->SUB0CFG;

    pReg    += ((uint32_t)index << 3);
    *(pReg) &= ~(GPIO_SUB1CFG_ENABLE_SET);
}

/**
 * @brief Returns if GPIO subscriber is enabled
 *
 * @param[in] gpio     Pointer to the register overlay for the peripheral
 * @param[in] index    Specifies the subscriber event index to be configured
 *
 * @return true if GPIO subscriber is enabled
 * @return false if GPIO subscriber is disabled
 *
 */
__STATIC_INLINE bool DL_GPIO_isSubscriberEnabled(GPIO_Regs* gpio, DL_GPIO_SUBSCRIBER_INDEX index)
{
    volatile uint32_t* pReg = &gpio->SUB0CFG;

    pReg += ((uint32_t)index << 3);
    return (GPIO_SUB1CFG_ENABLE_SET == (*(pReg)&GPIO_SUB1CFG_ENABLE_MASK));
}

/**
 *  @brief Enables GPIO events
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  index Specifies the register event index to be configured
 *  @param[in]  pins  Valid options will depend on index argument. When
 *               index == @ref DL_GPIO_EVENT_ROUTE_1, valid pins values are
 *               bitwise OR of @ref DL_GPIO_PIN (0-15). When
 *               index == @ref DL_GPIO_EVENT_ROUTE_2, valid pins Bitwise OR of
 *               @ref DL_GPIO_PIN (16-31).
 *
 */
__STATIC_INLINE void DL_GPIO_enableEvents(GPIO_Regs* gpio, DL_GPIO_EVENT_ROUTE index, uint32_t pins)
{
    switch (index)
    {
        case DL_GPIO_EVENT_ROUTE_1:
            gpio->GEN_EVENT0.IMASK |= (pins & 0x0000FFFFU);
            break;
        case DL_GPIO_EVENT_ROUTE_2:
            gpio->GEN_EVENT1.IMASK |= (pins & 0xFFFF0000U);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Disable GPIO events
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  index Specifies the register event index to be disabled
 *  @param[in]  pins  Valid options will depend on index argument. When
 *               index == @ref DL_GPIO_EVENT_ROUTE_1, valid pins values are
 *               bitwise OR of @ref DL_GPIO_PIN (0-15). When
 *               index == @ref DL_GPIO_EVENT_ROUTE_2, valid pins Bitwise OR of
 *               @ref DL_GPIO_PIN (16-31).
 *
 */
__STATIC_INLINE void DL_GPIO_disableEvents(GPIO_Regs* gpio, DL_GPIO_EVENT_ROUTE index, uint32_t pins)
{
    switch (index)
    {
        case DL_GPIO_EVENT_ROUTE_1:
            gpio->GEN_EVENT0.IMASK &= ~(pins & 0x0000FFFFU);
            break;
        case DL_GPIO_EVENT_ROUTE_2:
            gpio->GEN_EVENT1.IMASK &= ~(pins & 0xFFFF0000U);
            break;
        default:
            break;
    }
}

/**
 *  @brief      Check which GPIO events are enabled
 *
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  index Specifies the register event index to be checked
 *  @param[in]  pins  Valid options will depend on index argument. When
 *               index == @ref DL_GPIO_EVENT_ROUTE_1, valid pins values are
 *               bitwise OR of @ref DL_GPIO_PIN (0-15). When
 *               index == @ref DL_GPIO_EVENT_ROUTE_2, valid pins Bitwise OR of
 *               @ref DL_GPIO_PIN (16-31).
 *
 *  @return     Which of the requested GPIO events are enabled
 *
 *  @retval     Bitwise OR of @ref DL_GPIO_PIN values
 */
__STATIC_INLINE uint32_t DL_GPIO_getEnabledEvents(GPIO_Regs* gpio, DL_GPIO_EVENT_ROUTE index, uint32_t pins)
{
    volatile uint32_t* pReg;

    switch (index)
    {
        case DL_GPIO_EVENT_ROUTE_1:
            pReg = &gpio->GEN_EVENT0.IMASK;
            break;
        case DL_GPIO_EVENT_ROUTE_2:
            pReg = &gpio->GEN_EVENT1.IMASK;
            break;
        default:
            break;
    }

    return ((*pReg) & pins);
}

/**
 *  @brief Checks if any of the GPIO events which were previously enabled are
 *  pending.
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  index Specifies the register event index to be checked
 *  @param[in]  pins  Valid options will depend on index argument. When
 *               index == @ref DL_GPIO_EVENT_ROUTE_1, valid pins values are
 *               bitwise OR of @ref DL_GPIO_PIN (0-15). When
 *               index == @ref DL_GPIO_EVENT_ROUTE_2, valid pins Bitwise OR of
 *               @ref DL_GPIO_PIN (16-31).
 *
 *  @return     Which of the requested GPIO events are pending
 *
 *  @retval     Bitwise OR of @ref DL_GPIO_PIN values
 *
 *  @sa         DL_GPIO_enableEvents
 */
__STATIC_INLINE uint32_t DL_GPIO_getEnabledEventStatus(GPIO_Regs* gpio, DL_GPIO_EVENT_ROUTE index, uint32_t pins)
{
    const volatile uint32_t* pReg;

    switch (index)
    {
        case DL_GPIO_EVENT_ROUTE_1:
            pReg = &gpio->GEN_EVENT0.MIS;
            break;
        case DL_GPIO_EVENT_ROUTE_2:
            pReg = &gpio->GEN_EVENT1.MIS;
            break;
        default:
            break;
    }

    return ((*pReg) & pins);
}

/**
 *  @brief      Clear pending GPIO event
 *
 *  @param[in]  gpio  Pointer to the register overlay for the peripheral
 *  @param[in]  index Specifies the register event index to be configured
 *  @param[in]  pins  Valid options will depend on index argument. When
 *               index == @ref DL_GPIO_EVENT_ROUTE_1, valid pins values are
 *               bitwise OR of @ref DL_GPIO_PIN (0-15). When
 *               index == @ref DL_GPIO_EVENT_ROUTE_2, valid pins Bitwise OR of
 *               @ref DL_GPIO_PIN (16-31).
 *
 */
__STATIC_INLINE void DL_GPIO_clearEventStatus(GPIO_Regs* gpio, DL_GPIO_EVENT_ROUTE index, uint32_t pins)
{
    switch (index)
    {
        case DL_GPIO_EVENT_ROUTE_1:
            gpio->GEN_EVENT0.ICLR = (pins & 0x0000FFFFU);
            break;
        case DL_GPIO_EVENT_ROUTE_2:
            gpio->GEN_EVENT1.ICLR = (pins & 0xFFFF0000U);
            break;
        default:
            break;
    }
}

/**
 *  @brief Get Peripheral Function bits value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     Peripheral Function programmed
 *
 */
__STATIC_INLINE uint32_t DL_GPIO_getPeripheralFunctionBits(uint32_t pincmIndex)
{
    uint32_t value = IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_PF_MASK;

    return (uint32_t)(value);
}

/**
 *  @brief set Peripheral Connection value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @param[in]  value       Peripheral function value.
 */
__STATIC_INLINE void DL_GPIO_setPeripheralFunctionBits(uint32_t pincmIndex, uint32_t value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_PF_MASK);
}

/**
 *  @brief Get Peripheral Connection status
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     true if peripheral is connected else false.
 *
 */
__STATIC_INLINE bool DL_GPIO_isPeripheralConnected(uint32_t pincmIndex)
{
    bool value = (IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_PC_MASK) != 0;

    return value;
}

/**
 *  @brief set Peripheral Connection value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @param[in]  value       The peripheral connection value to set.
 *                          One of @ref DL_GPIO_PERIPHERAL_CONNECTION_VALUE
 */
__STATIC_INLINE void DL_GPIO_connectPeripheral(uint32_t pincmIndex, DL_GPIO_PERIPHERAL_CONNECTION_VALUE value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_PC_MASK);
}

/**
 *  @brief Get Pullup bit value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     true if pull-up is enabled.
 *
 */
__STATIC_INLINE bool DL_GPIO_isPullUp(uint32_t pincmIndex)
{
    bool value = (IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_PIPU_MASK) != 0;

    return value;
}

/**
 *  @brief set pul up value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @param[in]  value       The pullup value to set.
 *                          One of @ref DL_GPIO_PULLUP_VALUE
 */
__STATIC_INLINE void DL_GPIO_setPullUpBit(uint32_t pincmIndex, DL_GPIO_PULLUP_VALUE value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_PIPU_MASK);
}

/**
 *  @brief Get Pulldown bit value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     true if pull down is enabled else false.
 *
 */
__STATIC_INLINE bool DL_GPIO_isPullDown(uint32_t pincmIndex)
{
    bool value = (IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_PIPD_MASK) != 0;

    return value;
}

/**
 *  @brief set pulldown value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @param[in]  value       The pulldown value to set.
 *                          One of @ref DL_GPIO_PULLDOWN_VALUE
 */
__STATIC_INLINE void DL_GPIO_setPullDownBit(uint32_t pincmIndex, DL_GPIO_PULLDOWN_VALUE value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_PIPD_MASK);
}

/**
 *  @brief Get Input Enable value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     true if input is enabled else false.
 *
 */
__STATIC_INLINE bool DL_GPIO_isInputEnabled(uint32_t pincmIndex)
{
    bool value = (IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_INENA_MASK) != 0;

    return value;
}

/**
 *  @brief Get Hysteresis enable status
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     true if Hysteresis is enabled else false.
 *
 */
__STATIC_INLINE bool DL_GPIO_isHystersisEnabled(uint32_t pincmIndex)
{
    bool value = (IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_HYSTEN_MASK) != 0;

    return value;
}

/**
 *  @brief Enable or disable hysteresis
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @param[in]  value       hysteresis enable/disable value.
 *                          One of @ref DL_GPIO_HYSTERESIS
 */
__STATIC_INLINE void DL_GPIO_setHysteresis(uint32_t pincmIndex, DL_GPIO_HYSTERESIS value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_HYSTEN_MASK);
}

/**
 *  @brief Is Hi-Drive enable
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     true if high drive is slected else false.
 *
 */
__STATIC_INLINE bool DL_GPIO_isHighDriveEnabled(uint32_t pincmIndex)
{
    bool value = (IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_DRV_MASK) != 0;

    return value;
}

/**
 *  @brief Set the drive strength
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @param[in]  value       Drive strength value.
 *                          One of @ref DL_GPIO_DRIVE_STRENGTH
 */
__STATIC_INLINE void DL_GPIO_setDriveStrength(uint32_t pincmIndex, DL_GPIO_DRIVE_STRENGTH value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_DRV_MASK);
}

/**
 *  @brief Get Data Inversion bit value
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     true if data is inverted else false.
 *
 */
__STATIC_INLINE bool DL_GPIO_isdataInverted(uint32_t pincmIndex)
{
    bool value = (IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_INV_MASK) != 0;

    return value;
}

/**
 *  @brief Set data inversion value.
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @param[in]  value       data inversion value.
 *                          One of @ref DL_GPIO_INVERSION
 */
__STATIC_INLINE void DL_GPIO_setDataInversion(uint32_t pincmIndex, DL_GPIO_INVERSION value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_INV_MASK);
}

/**
 *  @brief is OpenDrain enabled
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @return     true if OpenDrain enabled else false.
 *
 */
__STATIC_INLINE bool DL_GPIO_isOpenDrainEnabled(uint32_t pincmIndex)
{
    bool value = (IOMUX->SECCFG.PINCM[pincmIndex] & IOMUX_PINCM_HIZ1_MASK) != 0;

    return value;
}

/**
 *  @brief Enable or disable open-drain.
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 *  @param[in]  value       Open Drain value.
 *                          One of @ref DL_GPIO_HIZ
 */
__STATIC_INLINE void DL_GPIO_setOpenDrain(uint32_t pincmIndex, DL_GPIO_HIZ value)
{
    DL_Common_updateReg(&IOMUX->SECCFG.PINCM[pincmIndex], (uint32_t)value, IOMUX_PINCM_HIZ1_MASK);
}

/**
 *  @brief Place PinCM register in known reset state.
 *
 *  @param[in]  pincmIndex  The PINCM register index that maps to the target
 *                          GPIO pin.
 *
 */
__STATIC_INLINE void DL_GPIO_resetPincmRegister(uint32_t pincmIndex)
{
    IOMUX->SECCFG.PINCM[pincmIndex] = 0;
}

#ifdef __cplusplus
}
#endif

#endif /* DL_GPIO_H */
/** @}*/
