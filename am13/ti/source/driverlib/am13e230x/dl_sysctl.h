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
 * @defgroup DL_SYSCTL_AM13E230X  Driverlib SYSCTL API
 * @ingroup DL_AM13E230X
 *
 * The System Control (SysCtl) module enables control over system wide
 * settings like clocks and power management.
 *
 * @{
 */

#ifndef DL_SYSCTL_H
#define DL_SYSCTL_H

#include "soc.h"
#include "dl_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief DL_SYSCTL_RESET */
typedef enum
{
    /*! @brief Issue a SYSRST (CPU plus peripherals only) */
    DL_SYSCTL_RESET_SYS             = 0x0U,
    /*! @brief Issue a BOOTRST (CPU, peripherals, and boot configuration routine) */
    DL_SYSCTL_RESET_BOOT            = 0x1U,
    /*! @brief Issue a SYSRST and enter the boot strap loader (BSL) */
    DL_SYSCTL_RESET_BOOTLOADERENTRY = 0x2U,
    /*! @brief Issue a power-on reset (POR) */
    DL_SYSCTL_RESET_POR             = 0x3U,
    /*! @brief Issue a SYSRST and exit the boot strap loader (BSL) */
    DL_SYSCTL_RESET_BOOTLOADEREXIT  = 0x4U,
} DL_SYSCTL_RESET;

/** @brief DL_SYSCTL_RESET_CAUSE */
typedef enum
{
    /*! @brief No reset since last read */
    DL_SYSCTL_RESET_CAUSE_NORST            = 0x0U,
    /*! @brief POR- violation, SHUTDNSTOREx or PMU trim parity fault */
    DL_SYSCTL_RESET_CAUSE_PORHWFAIL        = 0x1U,
    /*! @brief NRST triggered POR (>1s hold) */
    DL_SYSCTL_RESET_CAUSE_POREXNRST        = 0x2U,
    /*! @brief Software triggered POR */
    DL_SYSCTL_RESET_CAUSE_PORSW            = 0x3U,
    /*! @brief BOR0- violation */
    DL_SYSCTL_RESET_CAUSE_BORSUPPLY        = 0x4U,
    /*! @brief SHUTDOWN mode exit */
    DL_SYSCTL_RESET_CAUSE_BORWAKESHUTDN    = 0x5U,
    /*! @brief Non-PMU trim parity fault */
    DL_SYSCTL_RESET_CAUSE_BOOTNONPMUPARITY = 0x8U,
    /*! @brief Fatal clock failure */
    DL_SYSCTL_RESET_CAUSE_BOOTCLKFAIL      = 0x9U,
    /*! @brief NRST triggered BOOTRST (<1s hold) */
    DL_SYSCTL_RESET_CAUSE_BOOTEXNRST       = 0xCU,
    /*! @brief Software triggered BOOTRST */
    DL_SYSCTL_RESET_CAUSE_BOOTSW           = 0xDU,
    /*! @brief WWDT0 violation */
    DL_SYSCTL_RESET_CAUSE_BOOTWWDT0        = 0xEU,
    /*! @brief BSL exit */
    DL_SYSCTL_RESET_CAUSE_SYSBSLEXIT       = 0x10U,
    /*! @brief BSL entry */
    DL_SYSCTL_RESET_CAUSE_SYSBSLENTRY      = 0x11U,
    /*! @brief Flash uncorrectable ECC error */
    DL_SYSCTL_RESET_CAUSE_SYSFLASHECC      = 0x14U,
    /*! @brief CPULOCK violation */
    DL_SYSCTL_RESET_CAUSE_SYSCPULOCK       = 0x15U,
    /*! @brief Debug triggered SYSRST */
    DL_SYSCTL_RESET_CAUSE_SYSDBG           = 0x1AU,
    /*! @brief Software triggered SYSRST */
    DL_SYSCTL_RESET_CAUSE_SYSSW            = 0x1BU,
    /*! @brief Debug triggered CPURST */
    DL_SYSCTL_RESET_CAUSE_CPUDBG           = 0x1CU,
    /*! @brief Software triggered CPURST */
    DL_SYSCTL_RESET_CAUSE_CPUSW            = 0x1DU,
} DL_SYSCTL_RESET_CAUSE;

/**
 * @name DL_SYSCTL_INTERRUPT
 * @anchor DL_SYSCTL_INTERRUPT
 * @{
 */
/*! @brief Low Frequency Oscillator is stabilized and ready to use */
#define DL_SYSCTL_INTERRUPT_LFOSCGOOD  0x00000001U
/*! @brief Flash Single Error Correct */
#define DL_SYSCTL_INTERRUPT_FLASHSEC   0x00000004U
/*! @brief High Frequency Clock is stabilized and ready to use */
#define DL_SYSCTL_INTERRUPT_HFCLKGOOD  0x00000010U
/*! @brief System PLL is stabilized and ready to use */
#define DL_SYSCTL_INTERRUPT_SYSPLLGOOD 0x00000020U
/*! @brief High Speed Clock is stabilized and ready to use */
#define DL_SYSCTL_INTERRUPT_HSCLKGOOD  0x00000040U
/** @}*/

/*! @brief DL_SYSCTL_IIDX */
typedef enum
{
    /*! @brief No interrupt pending */
    DL_SYSCTL_IIDX_NO_INTR    = 0x0U,
    /*! @brief LFOSCGOOD interrupt pending */
    DL_SYSCTL_IIDX_LFOSCGOOD  = 0x1U,
    /*! @brief  */
    DL_SYSCTL_IIDX_ANACLKERR  = 0x2U,
    /*! @brief  */
    DL_SYSCTL_IIDX_FLASHSEC   = 0x3U,
    /*! @brief  */
    DL_SYSCTL_IIDX_SRAMSEC    = 0x4U,
    /*! @brief  */
    DL_SYSCTL_IIDX_HFCLKGOOD  = 0x5U,
    /*! @brief  */
    DL_SYSCTL_IIDX_SYSPLLGOOD = 0x6U,
    /*! @brief  */
    DL_SYSCTL_IIDX_HSCLKGOOD  = 0x7U,
} DL_SYSCTL_IIDX;

/**
 * @name DL_SYSCTL_NMI
 * @anchor DL_SYSCTL_NMI
 * @{
 */
/*! @brief Watch Dog 0 Fault */
#define DL_SYSCTL_NMI_WWDT0     0x00000002U
/*! @brief Security Fault */
#define DL_SYSCTL_NMI_SECURITY  0x00000004U
/*! @brief Flash Double Error Detect */
#define DL_SYSCTL_NMI_FLASHDED  0x00000008U
/*! @brief SRAM Parity Error Detect */
#define DL_SYSCTL_NMI_SRAMPAR   0x00000010U
/*! @brief TMU ROM Parity error */
#define DL_SYSCTL_NMI_TMUROMPAR 0x00000020U
/*! @brief SYSMEM Access error */
#define DL_SYSCTL_NMI_SYSMEMACC 0x00000040U
/** @}*/

/*! @brief DL_SYSCTL_NMI_IIDX */
typedef enum
{
    /*! @brief No NMI pending */
    DL_SYSCTL_NMI_IIDX_NO_INTR   = 0x0U,
    /*! @brief Reserved */
    DL_SYSCTL_NMI_IIDX_BORLVL    = 0x1U,
    /*! @brief  */
    DL_SYSCTL_NMI_IIDX_WWDT0     = 0x2U,
    /*! @brief  */
    DL_SYSCTL_NMI_IIDX_SECURITY  = 0x3U,
    /*! @brief  */
    DL_SYSCTL_NMI_IIDX_FLASHDED  = 0x4U,
    /*! @brief  */
    DL_SYSCTL_NMI_IIDX_SRAMPAR   = 0x5U,
    /*! @brief  */
    DL_SYSCTL_NMI_IIDX_TMUROMPAR = 0x6U,
    /*! @brief  */
    DL_SYSCTL_NMI_IIDX_SYSMEMACC = 0x7U,
} DL_SYSCTL_NMI_IIDX;

/**
 * @brief DL_SYSCTL_PERIPH_POWER
 *
 * First 16 bits is the offset of the register and the last 4 bits is the bit position
 */
typedef enum
{
    /*! @brief */
    DL_SYSCTL_PWREN_EQEP0  = 0x14240000U,
    /*! @brief */
    DL_SYSCTL_PWREN_EQEP1  = 0x14240001U,
    /*! @brief */
    DL_SYSCTL_PWREN_EQEP2  = 0x14240002U,
    /*! @brief */
    DL_SYSCTL_PWREN_ECAP0  = 0x14240003U,
    /*! @brief */
    DL_SYSCTL_PWREN_ECAP1  = 0x14240004U,
    /*! @brief */
    DL_SYSCTL_PWREN_PWM0   = 0x14240005U,
    /*! @brief */
    DL_SYSCTL_PWREN_PWM1   = 0x14240006U,
    /*! @brief */
    DL_SYSCTL_PWREN_PWM2   = 0x14240007U,
    /*! @brief */
    DL_SYSCTL_PWREN_PWM3   = 0x14240008U,
    /*! @brief */
    DL_SYSCTL_PWREN_PWM4   = 0x14240009U,
    /*! @brief */
    DL_SYSCTL_PWREN_CMPSS0 = 0x1424000AU,
    /*! @brief */
    DL_SYSCTL_PWREN_CMPSS1 = 0x1424000BU,
    /*! @brief */
    DL_SYSCTL_PWREN_CMPSS2 = 0x1424000CU,
    /*! @brief */
    DL_SYSCTL_PWREN_CMPSS3 = 0x1424000DU,
    /*! @brief */
    DL_SYSCTL_PWREN_XBAR   = 0x1424000EU,
    /*! @brief */
    DL_SYSCTL_PWREN_TINIE  = 0x14340000U,
    /*! @brief */
    DL_SYSCTL_PWREN_PGA0   = 0x14340001U,
    /*! @brief */
    DL_SYSCTL_PWREN_PGA1   = 0x14340002U,
    /*! @brief */
    DL_SYSCTL_PWREN_PGA2   = 0x14340003U,
    /*! @brief */
    DL_SYSCTL_PWREN_EPI    = 0x14340004U,
} DL_SYSCTL_PERIPH_POWER;

/**
 * @brief DL_SYSCTL_PERIPH_RESET
 *
 * First 16 bits is the offset of the register and the last 4 bits is the bit position
 */
typedef enum
{
    /*! @brief */
    DL_SYSCTL_RESET_EQEP0  = 0x14280000U,
    /*! @brief */
    DL_SYSCTL_RESET_EQEP1  = 0x14280001U,
    /*! @brief */
    DL_SYSCTL_RESET_EQEP2  = 0x14280002U,
    /*! @brief */
    DL_SYSCTL_RESET_ECAP0  = 0x14280003U,
    /*! @brief */
    DL_SYSCTL_RESET_ECAP1  = 0x14280004U,
    /*! @brief */
    DL_SYSCTL_RESET_PWM0   = 0x14280005U,
    /*! @brief */
    DL_SYSCTL_RESET_PWM1   = 0x14280006U,
    /*! @brief */
    DL_SYSCTL_RESET_PWM2   = 0x14280007U,
    /*! @brief */
    DL_SYSCTL_RESET_PWM3   = 0x14280008U,
    /*! @brief */
    DL_SYSCTL_RESET_PWM4   = 0x14280009U,
    /*! @brief */
    DL_SYSCTL_RESET_CMPSS0 = 0x1428000AU,
    /*! @brief */
    DL_SYSCTL_RESET_CMPSS1 = 0x1428000BU,
    /*! @brief */
    DL_SYSCTL_RESET_CMPSS2 = 0x1428000CU,
    /*! @brief */
    DL_SYSCTL_RESET_CMPSS3 = 0x1428000DU,
    /*! @brief */
    DL_SYSCTL_RESET_XBAR   = 0x1428000EU,
    /*! @brief */
    DL_SYSCTL_RESET_TINIE  = 0x14380000U,
    /*! @brief */
    DL_SYSCTL_RESET_PGA0   = 0x14380001U,
    /*! @brief */
    DL_SYSCTL_RESET_PGA1   = 0x14380002U,
    /*! @brief */
    DL_SYSCTL_RESET_PGA2   = 0x14380003U,
    /*! @brief */
    DL_SYSCTL_RESET_EPI    = 0x14380004U,
} DL_SYSCTL_PERIPH_RESET;

/**
 * @name DL_SYSCTL_CLK_STATUS
 *  @anchor DL_SYSCTL_CLK_STATUS
 * @{
 */
/*! @brief Analog clocking error */
#define DL_SYSCTL_CLK_STATUS_ANALOG_CLOCK_ERROR    (SYSCTL_CLKSTATUS_ANACLKERR_TRUE)
/*! @brief Writes to SYSPLLCFG0-1, SYSPLLPARAM0-1 are blocked */
#define DL_SYSCTL_CLK_STATUS_SYSPLL_CONFIG_BLOCKED (SYSCTL_CLKSTATUS_SYSPLLBLKUPD_TRUE)
/*! @brief Writes to HFCLKCLKCFG are blocked */
#define DL_SYSCTL_CLK_STATUS_HFCLK_CONFIG_BLOCKED  (SYSCTL_CLKSTATUS_HFCLKBLKUPD_TRUE)
/*! @brief Frequency Clock Counter (FCC) done */
#define DL_SYSCTL_CLK_STATUS_FCC_DONE              (SYSCTL_CLKSTATUS_FCCDONE_DONE)
/*! @brief SYSOSC Frequency Correcting Loop Mode ON */
#define DL_SYSCTL_CLK_STATUS_FCL_ON                (SYSCTL_CLKSTATUS_FCLMODE_ENABLED)
/*! @brief High Speed Clock Good */
#define DL_SYSCTL_CLK_STATUS_HSCLK_GOOD            (SYSCTL_CLKSTATUS_HSCLKGOOD_TRUE)
/*! @brief High Speed Clock Stuck Fault */
#define DL_SYSCTL_CLK_STATUS_HSCLK_FAULT           (SYSCTL_CLKSTATUS_HSCLKDEAD_TRUE)
/*! @brief = HSCLK current sourced from the HFCLK */
#define DL_SYSCTL_CLK_STATUS_HSCLK_SOURCE_HFCLK    (SYSCTL_CLKSTATUS_CURHSCLKSEL_HFCLK)
/*! @brief SYSPLL is OFF or DEAD */
#define DL_SYSCTL_CLK_STATUS_SYSPLL_OFF            (SYSCTL_CLKSTATUS_SYSPLLOFF_TRUE)
/*! @brief HFCLKs is OFF or DEAD */
#define DL_SYSCTL_CLK_STATUS_HFCLK_OFF             (SYSCTL_CLKSTATUS_HFCLKOFF_TRUE)
/*! @brief All PLLs, HFCLKs are OFF or DEAD */
#define DL_SYSCTL_CLK_STATUS_HSCLK_OFF             (SYSCTL_CLKSTATUS_HSCLKSOFF_TRUE)
/*! @brief LFOSC is Valid */
#define DL_SYSCTL_CLK_STATUS_LFOSC_GOOD            (SYSCTL_CLKSTATUS_LFOSCGOOD_TRUE)
/*! @brief SYSTEM PLL ON */
#define DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD           (SYSCTL_CLKSTATUS_SYSPLLGOOD_TRUE)
/*! @brief High Frequency Clock ON */
#define DL_SYSCTL_CLK_STATUS_HFCLK_GOOD            (SYSCTL_CLKSTATUS_HFCLKGOOD_TRUE)
/*! @brief MCLK now sourced from HSCLK, otherwise SYSOSC */
#define DL_SYSCTL_CLK_STATUS_MCLK_SOURCE_HSCLK     (SYSCTL_CLKSTATUS_HSCLKMUX_HSCLK)
/*! @brief = SYSOSC is at low frequency (4MHz) */
#define DL_SYSCTL_CLK_STATUS_SYSOSC_4MHZ           (SYSCTL_CLKSTATUS_SYSOSCFREQ_SYSOSC4M)
/*! @brief = SYSOSC is at the user-trimmed frequency (16 or 24MHz) */
#define DL_SYSCTL_CLK_STATUS_SYSOSC_USERTRIM_FREQ  (SYSCTL_CLKSTATUS_SYSOSCFREQ_SYSOSCUSER)
/** @}*/

/**
 * @name DL_SYSCTL_STATUS
 * @anchor DL_SYSCTL_STATUS
 * @{
 */
/*! @brief FLASHDED indicates if a flash ECC double bit error was detected (DED). */
#define DL_SYSCTL_STATUS_FLASHDED       0x00000001U
/*! @brief FLASHSEC indicates if a flash ECC single bit error was detected and corrected (SEC). */
#define DL_SYSCTL_STATUS_FLASHSEC       0x00000002U
/*! @brief PMUIREFGOOD is set by hardware when the PMU current reference is ready. */
#define DL_SYSCTL_STATUS_PMUIREFGOOD    0x00000040U
/*! @brief MCAN0READY indicates when the MCAN0 peripheral is ready. */
#define DL_SYSCTL_STATUS_MCAN0READY     0x00000100U
/*! @brief EXTRSTPINDIS indicates when user has disabled the use of external reset pin */
#define DL_SYSCTL_STATUS_EXTRSTPINDIS   0x00001000U
/*! @brief SWDJCFGDIS indicates when user has disabled the use of SWD/JTAG Port */
#define DL_SYSCTL_STATUS_SWDJCFGDIS     0x00002000U
/*! @brief SHDNIOLOCK indicates when IO is locked due to SHUTDOWN */
#define DL_SYSCTL_STATUS_SHDNIOLOCK     0x00004000U
/*! @brief SRAM BANK0 READY STATE */
#define DL_SYSCTL_STATUS_SRAMBANK0READY 0x00010000U
/*! @brief SRAM BANK1 READY STATE */
#define DL_SYSCTL_STATUS_SRAMBANK1READY 0x00020000U
/*! @brief SRAM BANK2 READY STATE */
#define DL_SYSCTL_STATUS_SRAMBANK2READY 0x00040000U
/*! @brief SRAM BANK3 READY STATE */
#define DL_SYSCTL_STATUS_SRAMBANK3READY 0x00080000U
/** @}*/

/**
 * @name DL_SYSCTL_SYSPLL_CLK1
 * @anchor DL_SYSCTL_SYSPLL_CLK1
 * @{
 */
/*! @brief Enable CLK1 output */
#define DL_SYSCTL_SYSPLL_CLK1_ENABLE (SYSCTL_SYSPLLCFG0_ENABLECLK1_ENABLE)

/*! @brief Disable CLK1 output */
#define DL_SYSCTL_SYSPLL_CLK1_DISABLE (SYSCTL_SYSPLLCFG0_ENABLECLK1_DISABLE)
/** @}*/

/**
 * @name DL_SYSCTL_SYSPLL_CLK0
 * @anchor DL_SYSCTL_SYSPLL_CLK0
 * @{
 */
/*! @brief Enable CLK0 output */
#define DL_SYSCTL_SYSPLL_CLK0_ENABLE (SYSCTL_SYSPLLCFG0_ENABLECLK0_ENABLE)

/*! @brief Disable CLK0 output */
#define DL_SYSCTL_SYSPLL_CLK0_DISABLE (SYSCTL_SYSPLLCFG0_ENABLECLK0_DISABLE)
/** @}*/

/*! @brief DL_SYSCTL_SYSPLL_REF */
typedef enum
{
    /*! Use SYSOSC as input source for SYSPLL */
    DL_SYSCTL_SYSPLL_REF_SYSOSC = SYSCTL_SYSPLLCFG0_SYSPLLREF_SYSOSC,
    /*! Use HFCLK as input source for SYSPLL */
    DL_SYSCTL_SYSPLL_REF_HFCLK  = SYSCTL_SYSPLLCFG0_SYSPLLREF_HFCLK,
} DL_SYSCTL_SYSPLL_REF;

/*! @brief DL_SYSCTL_SYSPLL_PDIV */
typedef enum
{
    /*! @brief SYSPLLREF is not divided */
    DL_SYSCTL_SYSPLL_PDIV_1 = 0x0U,
    /*! @brief SYSPLLREF is divided by 2 */
    DL_SYSCTL_SYSPLL_PDIV_2 = 0x1U,
    /*! @brief SYSPLLREF is divided by 4 */
    DL_SYSCTL_SYSPLL_PDIV_4 = 0x2U,
    /*! @brief SYSPLLREF is divided by 8 */
    DL_SYSCTL_SYSPLL_PDIV_8 = 0x3U,
} DL_SYSCTL_SYSPLL_PDIV;

/*! @brief DL_SYSCTL_SYSPLL_RDIVCLK1 */
typedef enum
{
    /*! @brief SYSPLLCLK1 is divided by 2 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV2  = 0x0U,
    /*! @brief SYSPLLCLK1 is divided by 4 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV4  = 0x1U,
    /*! @brief SYSPLLCLK1 is divided by 6 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV6  = 0x2U,
    /*! @brief SYSPLLCLK1 is divided by 8 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV8  = 0x3U,
    /*! @brief SYSPLLCLK1 is divided by 10 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV10 = 0x4U,
    /*! @brief SYSPLLCLK1 is divided by 12 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV12 = 0x5U,
    /*! @brief SYSPLLCLK1 is divided by 14 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV14 = 0x6U,
    /*! @brief SYSPLLCLK1 is divided by 16 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV16 = 0x7U,
    /*! @brief SYSPLLCLK1 is divided by 18 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV18 = 0x8U,
    /*! @brief SYSPLLCLK1 is divided by 20 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV20 = 0x9U,
    /*! @brief SYSPLLCLK1 is divided by 22 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV22 = 0xAU,
    /*! @brief SYSPLLCLK1 is divided by 24 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV24 = 0xBU,
    /*! @brief SYSPLLCLK1 is divided by 26 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV26 = 0xCU,
    /*! @brief SYSPLLCLK1 is divided by 28 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV28 = 0xDU,
    /*! @brief SYSPLLCLK1 is divided by 30 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV30 = 0xEU,
    /*! @brief SYSPLLCLK1 is divided by 32 */
    DL_SYSCTL_SYSPLL_RDIVCLK1_DIV32 = 0xFU,
} DL_SYSCTL_SYSPLL_RDIVCLK1;

/*! @brief DL_SYSCTL_SYSPLL_RDIVCLK0 */
typedef enum
{
    /*! @brief SYSPLLCLK0 is divided by 2 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV2  = 0x0U,
    /*! @brief SYSPLLCLK0 is divided by 4 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV4  = 0x1U,
    /*! @brief SYSPLLCLK0 is divided by 6 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV6  = 0x2U,
    /*! @brief SYSPLLCLK0 is divided by 8 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV8  = 0x3U,
    /*! @brief SYSPLLCLK0 is divided by 10 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV10 = 0x4U,
    /*! @brief SYSPLLCLK0 is divided by 12 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV12 = 0x5U,
    /*! @brief SYSPLLCLK0 is divided by 14 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV14 = 0x6U,
    /*! @brief SYSPLLCLK0 is divided by 16 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV16 = 0x7U,
    /*! @brief SYSPLLCLK0 is divided by 18 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV18 = 0x8U,
    /*! @brief SYSPLLCLK0 is divided by 20 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV20 = 0x9U,
    /*! @brief SYSPLLCLK0 is divided by 22 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV22 = 0xAU,
    /*! @brief SYSPLLCLK0 is divided by 24 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV24 = 0xBU,
    /*! @brief SYSPLLCLK0 is divided by 26 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV26 = 0xCU,
    /*! @brief SYSPLLCLK0 is divided by 28 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV28 = 0xDU,
    /*! @brief SYSPLLCLK0 is divided by 30 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV30 = 0xEU,
    /*! @brief SYSPLLCLK0 is divided by 32 */
    DL_SYSCTL_SYSPLL_RDIVCLK0_DIV32 = 0xFU,
} DL_SYSCTL_SYSPLL_RDIVCLK0;

/** @brief DL_SYSCTL_SYSPLL_INPUT_FREQ */
typedef enum
{
    /*! PLL feedback loop input clock frequency [4MHz, 8MHz) */
    DL_SYSCTL_SYSPLL_INPUT_FREQ_4_8_MHZ   = 0x60111020U,
    /*! PLL feedback loop input clock frequency [8MHz, 16MHz) */
    DL_SYSCTL_SYSPLL_INPUT_FREQ_8_16_MHZ  = 0x60111028U,
    /*! PLL feedback loop input clock frequency [16MHz, 32MHz) */
    DL_SYSCTL_SYSPLL_INPUT_FREQ_16_32_MHZ = 0x60111030U,
    /*! PLL feedback loop input clock frequency [32MHz, 48MHz] */
    DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ = 0x60111038U,
} DL_SYSCTL_SYSPLL_INPUT_FREQ;

/*! @brief  Configuration struct for @ref DL_SYSCTL_configSYSPLL. */
typedef struct
{
    /*! SYSPLL reference clock source. @ref DL_SYSCTL_SYSPLL_REF */
    DL_SYSCTL_SYSPLL_REF        sysPLLRef;
    /*! PLL feedback loop input clock frequency. Affects startup time and power consumption. @ref
     * DL_SYSCTL_SYSPLL_INPUT_FREQ */
    DL_SYSCTL_SYSPLL_INPUT_FREQ inputFreq;
    /*! PLL reference clock divider. @ref DL_SYSCTL_SYSPLL_PDIV */
    DL_SYSCTL_SYSPLL_PDIV       pDiv;
    /*! PLL feedback clock divider. Values : 1-126. Feedback path is divided by qDiv + 1 */
    uint32_t                    qDiv;
    /*! PLL CLK1 output enabled or not. @ref DL_SYSCTL_SYSPLL_CLK1 */
    uint32_t                    enableCLK1;
    /*! PLL CLK0 output enabled or not. @ref DL_SYSCTL_SYSPLL_CLK0 */
    uint32_t                    enableCLK0;
    /*! Output divider for CLK1. [0x0,0xF,0x1] => [/2,/32,2] */
    DL_SYSCTL_SYSPLL_RDIVCLK1   rDivClk1;
    /*! Output divider for CLK0. [0x0,0xF,0x1] => [/2,/32,2] */
    DL_SYSCTL_SYSPLL_RDIVCLK0   rDivClk0;
} DL_SYSCTL_SYSPLLConfig;

/*! @brief DL_SYSCTL_ERROR_BEHAVIOR */
typedef enum
{
    /*! @brief  The error event will trigger a SYSRST */
    DL_SYSCTL_ERROR_BEHAVIOR_RESET = 0x0,
    /*! @brief  The error event will trigger an NMI */
    DL_SYSCTL_ERROR_BEHAVIOR_NMI   = 0x1,
} DL_SYSCTL_ERROR_BEHAVIOR;

/** @brief DL_SYSCTL_MCLK_DIV */
typedef enum
{
    DL_SYSCTL_MCLK_DIV_1_DIV_1 = 0x00000000, /* MCLK2 = Bypass, MCLK4 = Bypass, ULPCLK = MCLK4 */
    DL_SYSCTL_MCLK_DIV_1_DIV_2 = 0x01000000, /* MCLK2 = Bypass, MCLK4 = MCLK/2, ULPCLK = MCLK4 */
    DL_SYSCTL_MCLK_DIV_1_DIV_4 = 0x03000000, /* MCLK2 = Bypass, MCLK4 = MCLK/4, ULPCLK = MCLK4 */
    DL_SYSCTL_MCLK_DIV_2_DIV_2 = 0x05000000, /* MCLK2 = MCLK/2, MCLK4 = MCLK/2, ULPCLK = MCLK4 */
    DL_SYSCTL_MCLK_DIV_2_DIV_4 = 0x07000000, /* MCLK2 = MCLK/2, MCLK4 = MCLK/4, ULPCLK = MCLK4 */
} DL_SYSCTL_MCLK_DIV;

/*! @brief DL_SYSCTL_HSCLK_SOURCE */
typedef enum
{
    /*! Use SYSPLL as input source for HSCLK */
    DL_SYSCTL_HSCLK_SOURCE_SYSPLL = SYSCTL_HSCLKCFG_HSCLKSEL_SYSPLL,
    /*! Use HFCLK as input source for HSCLK */
    DL_SYSCTL_HSCLK_SOURCE_HFCLK  = SYSCTL_HSCLKCFG_HSCLKSEL_HFCLKCLK,
} DL_SYSCTL_HSCLK_SOURCE;

/** @brief DL_SYSCTL_MCLK_SOURCE */
typedef enum
{
    /*! Use System Oscillator (SYSOSC) as MCLK source (default after reset) */
    DL_SYSCTL_MCLK_SOURCE_SYSOSC = SYSCTL_MCLKCFG_USEHSCLK_DISABLE,
    /*! Use High Speed Clock (HSCLK) as MCLK source (HFCLK, PLL,...) */
    DL_SYSCTL_MCLK_SOURCE_HSCLK  = SYSCTL_MCLKCFG_USEHSCLK_ENABLE,
} DL_SYSCTL_MCLK_SOURCE;

/** @brief DL_SYSCTL_CANCLK_SOURCE */
typedef enum
{
    DL_SYSCTL_CANCLK_SOURCE_HFCLK        = 0xFFFFFFFFU,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL       = SYSCTL_GENCLKEN_CANEXTDIVEN_PASSTHRU,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL_DIV2  = SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE | SYSCTL_GENCLKEN_EXTDIVCAN_DIV2,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL_DIV4  = SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE | SYSCTL_GENCLKEN_EXTDIVCAN_DIV4,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL_DIV6  = SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE | SYSCTL_GENCLKEN_EXTDIVCAN_DIV6,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL_DIV8  = SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE | SYSCTL_GENCLKEN_EXTDIVCAN_DIV8,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL_DIV10 = SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE | SYSCTL_GENCLKEN_EXTDIVCAN_DIV10,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL_DIV12 = SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE | SYSCTL_GENCLKEN_EXTDIVCAN_DIV12,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL_DIV14 = SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE | SYSCTL_GENCLKEN_EXTDIVCAN_DIV14,
    DL_SYSCTL_CANCLK_SOURCE_SYSPLL_DIV16 = SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE | SYSCTL_GENCLKEN_EXTDIVCAN_DIV16,
} DL_SYSCTL_CANCLK_SOURCE;

/** @brief DL_SYSCTL_CLK_OUT_SOURCE */
typedef enum
{
    /*! @brief CLK_OUT is SYSOSC */
    DL_SYSCTL_CLK_OUT_SOURCE_SYSOSC     = 0x0U,
    /*! @brief CLK_OUT is ULPCLK (EXCLKDIVEN must be enabled) */
    DL_SYSCTL_CLK_OUT_SOURCE_ULPCLK     = 0x1U,
    /*! @brief CLK_OUT is LFCLK */
    DL_SYSCTL_CLK_OUT_SOURCE_LFCLK      = 0x2U,
    /*! @brief CLK_OUT is MFPCLK (EXCLKDIVEN must be enabled) */
    DL_SYSCTL_CLK_OUT_SOURCE_MFPCLK     = 0x3U,
    /*! @brief CLK_OUT is HFCLK */
    DL_SYSCTL_CLK_OUT_SOURCE_HFCLK      = 0x4U,
    /*! @brief CLK_OUT is SYSPLLCLK1 (SYSPLLCLK1 must be <=48MHz) */
    DL_SYSCTL_CLK_OUT_SOURCE_SYSPLLOUT1 = 0x5U,
} DL_SYSCTL_CLK_OUT_SOURCE;

/** @brief DL_SYSCTL_CLK_OUT_DIVIDE */
typedef enum
{
    /*! Disable the External Clock (CLK_OUT) output divider */
    DL_SYSCTL_CLK_OUT_DIVIDE_DISABLE = SYSCTL_GENCLKCFG_EXCLKDIVEN_PASSTHRU,
    /*! Divide External Clock (CLK_OUT) output by 2 */
    DL_SYSCTL_CLK_OUT_DIVIDE_2       = SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE | SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV2,
    /*! Divide External Clock (CLK_OUT) output by 4 */
    DL_SYSCTL_CLK_OUT_DIVIDE_4       = SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE | SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV4,
    /*! Divide External Clock (CLK_OUT) output by 6 */
    DL_SYSCTL_CLK_OUT_DIVIDE_6       = SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE | SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV6,
    /*! Divide External Clock (CLK_OUT) output by 8 */
    DL_SYSCTL_CLK_OUT_DIVIDE_8       = SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE | SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV8,
    /*! Divide External Clock (CLK_OUT) output by 10 */
    DL_SYSCTL_CLK_OUT_DIVIDE_10      = SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE | SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV10,
    /*! Divide External Clock (CLK_OUT) output by 12 */
    DL_SYSCTL_CLK_OUT_DIVIDE_12      = SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE | SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV12,
    /*! Divide External Clock (CLK_OUT) output by 14 */
    DL_SYSCTL_CLK_OUT_DIVIDE_14      = SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE | SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV14,
    /*! Divide External Clock (CLK_OUT) output by 16 */
    DL_SYSCTL_CLK_OUT_DIVIDE_16      = SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE | SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV16,
} DL_SYSCTL_CLK_OUT_DIVIDE;

/** @brief DL_SYSCTL_FCC_TRIG_TYPE */
typedef enum
{
    /*! FCC trigger is rising-edge to rising-edge pulse */
    DL_SYSCTL_FCC_TRIG_TYPE_RISE_RISE = SYSCTL_GENCLKCFG_FCCLVLTRIG_RISE2RISE,
    /*! FCC trigger is active-high pulse level */
    DL_SYSCTL_FCC_TRIG_TYPE_LEVEL     = SYSCTL_GENCLKCFG_FCCLVLTRIG_LEVEL,
} DL_SYSCTL_FCC_TRIG_TYPE;

/** @brief DL_SYSCTL_FCC_TRIG_SOURCE */
typedef enum
{
    /*! @brief FCC trigger is the external pin */
    DL_SYSCTL_FCC_TRIG_SOURCE_EXTPIN = 0x00000000U,
    /*! @brief FCC trigger is the LFCLK */
    DL_SYSCTL_FCC_TRIG_SOURCE_LFCLK  = 0x00100000U,
} DL_SYSCTL_FCC_TRIG_SOURCE;

/** @brief DL_SYSCTL_FCC_CLOCK_SOURCE */
typedef enum
{
    /*! @brief FCC clock is MCLK/4 */
    DL_SYSCTL_FCC_CLOCK_SOURCE_MCLKBY4    = 0x00000000U,
    /*! @brief FCC clock is SYSOSC */
    DL_SYSCTL_FCC_CLOCK_SOURCE_SYSOSC     = 0x00010000U,
    /*! @brief FCC clock is HFCLK */
    DL_SYSCTL_FCC_CLOCK_SOURCE_HFCLK      = 0x00020000U,
    /*! @brief FCC clock is the CLK_OUT selection */
    DL_SYSCTL_FCC_CLOCK_SOURCE_EXTCLK     = 0x00030000U,
    /*! @brief FCC clock is SYSPLLCLK0 */
    DL_SYSCTL_FCC_CLOCK_SOURCE_SYSPLLCLK0 = 0x00040000U,
    /*! @brief FCC clock is SYSPLLCLK1 */
    DL_SYSCTL_FCC_CLOCK_SOURCE_SYSPLLCLK1 = 0x00050000U,
    /*! @brief FCC clock is the FCCIN external input */
    DL_SYSCTL_FCC_CLOCK_SOURCE_FCCIN      = 0x00070000U,
} DL_SYSCTL_FCC_CLOCK_SOURCE;

/** @brief DL_SYSCTL_FCC_TRIG_CNT */
typedef enum
{
    /*! 1 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_01 = ((uint32_t)0 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 2 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_02 = ((uint32_t)1 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 3 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_03 = ((uint32_t)2 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 4 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_04 = ((uint32_t)3 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 5 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_05 = ((uint32_t)4 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 6 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_06 = ((uint32_t)5 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 7 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_07 = ((uint32_t)6 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 8 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_08 = ((uint32_t)7 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 9 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_09 = ((uint32_t)8 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 10 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_10 = ((uint32_t)9 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 11 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_11 = ((uint32_t)10 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 12 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_12 = ((uint32_t)11 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 13 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_13 = ((uint32_t)12 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 14 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_14 = ((uint32_t)13 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 15 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_15 = ((uint32_t)14 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 16 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_16 = ((uint32_t)15 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 17 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_17 = ((uint32_t)16 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 18 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_18 = ((uint32_t)17 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 19 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_19 = ((uint32_t)18 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 20 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_20 = ((uint32_t)19 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 21 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_21 = ((uint32_t)20 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 22 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_22 = ((uint32_t)21 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 23 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_23 = ((uint32_t)22 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 24 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_24 = ((uint32_t)23 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 25 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_25 = ((uint32_t)24 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 26 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_26 = ((uint32_t)25 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 27 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_27 = ((uint32_t)26 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 28 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_28 = ((uint32_t)27 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 29 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_29 = ((uint32_t)28 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 30 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_30 = ((uint32_t)29 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 31 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_31 = ((uint32_t)30 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
    /*! 32 monitoring period */
    DL_SYSCTL_FCC_TRIG_CNT_32 = ((uint32_t)31 << SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS),
} DL_SYSCTL_FCC_TRIG_CNT;

/** @brief DL_SYSCTL_POWER_POLICY_STANDBY */
typedef enum
{
    /*! STANDBY power policy is not enabled */
    DL_SYSCTL_POWER_POLICY_STANDBY_NOT_ENABLED = 0x0,
    /*! Enable the STANDBY0 power mode policy */
    DL_SYSCTL_POWER_POLICY_STANDBY0            = 0x1,
    /*! Enable the STANDBY1 power mode policy */
    DL_SYSCTL_POWER_POLICY_STANDBY1            = 0x2,
} DL_SYSCTL_POWER_POLICY_STANDBY;

/** @brief DL_SYSCTL_SHUTDOWN_STORAGE_BYTE */
typedef enum
{
    /*! Shutdown Storage Byte 0 */
    DL_SYSCTL_SHUTDOWN_STORAGE_BYTE_0 = 0x0,
    /*! Shutdown Storage Byte 1 */
    DL_SYSCTL_SHUTDOWN_STORAGE_BYTE_1 = 0x1,
    /*! Shutdown Storage Byte 2 */
    DL_SYSCTL_SHUTDOWN_STORAGE_BYTE_2 = 0x2,
    /*! Shutdown Storage Byte 3 */
    DL_SYSCTL_SHUTDOWN_STORAGE_BYTE_3 = 0x3,
} DL_SYSCTL_SHUTDOWN_STORAGE_BYTE;

/** @brief DL_SYSCTL_PLL_DIVIDER */
typedef enum
{
    /** @brief */
    DL_SYSCTL_PLL_DIVIDER_DIV2  = SYSCTL_GENCLKEN_EXTDIVMCLK_DIV2,
    /** @brief */
    DL_SYSCTL_PLL_DIVIDER_DIV4  = SYSCTL_GENCLKEN_EXTDIVMCLK_DIV4,
    /** @brief */
    DL_SYSCTL_PLL_DIVIDER_DIV6  = SYSCTL_GENCLKEN_EXTDIVMCLK_DIV6,
    /** @brief */
    DL_SYSCTL_PLL_DIVIDER_DIV8  = SYSCTL_GENCLKEN_EXTDIVMCLK_DIV8,
    /** @brief */
    DL_SYSCTL_PLL_DIVIDER_DIV10 = SYSCTL_GENCLKEN_EXTDIVMCLK_DIV10,
    /** @brief */
    DL_SYSCTL_PLL_DIVIDER_DIV12 = SYSCTL_GENCLKEN_EXTDIVMCLK_DIV12,
    /** @brief */
    DL_SYSCTL_PLL_DIVIDER_DIV14 = SYSCTL_GENCLKEN_EXTDIVMCLK_DIV14,
    /** @brief */
    DL_SYSCTL_PLL_DIVIDER_DIV16 = SYSCTL_GENCLKEN_EXTDIVMCLK_DIV16,
} DL_SYSCTL_PLL_DIVIDER;

/** @brief DL_SYSCTL_CMPSS_MUX */
typedef enum
{
    /** @brief Mux selection for CMPSS0 */
    DL_SYSCTL_CMPSS0_MUX = 0,
    /** @brief Mux selection for CMPSS1 */
    DL_SYSCTL_CMPSS1_MUX = 1,
    /** @brief Mux selection for CMPSS2 */
    DL_SYSCTL_CMPSS2_MUX = 2,
    /** @brief Mux selection for CMPSS3 */
    DL_SYSCTL_CMPSS3_MUX = 3,
} DL_SYSCTL_CMPSS_MUX;

/** @brief DL_SYSCTL_CMP_HP */
typedef enum
{
    DL_SYSCTL_CMP_HP0 = 0,
    DL_SYSCTL_CMP_HP1 = 1,
    DL_SYSCTL_CMP_HP2 = 2,
    DL_SYSCTL_CMP_HP3 = 3,
    DL_SYSCTL_CMP_HP4 = 4,
    DL_SYSCTL_CMP_HP5 = 5,
    DL_SYSCTL_CMP_HP6 = 6,
} DL_SYSCTL_CMP_HP;

/** @brief DL_SYSCTL_CMP_HN */
typedef enum
{
    DL_SYSCTL_CMP_HN0 = 0,
    DL_SYSCTL_CMP_HN1 = 1,
} DL_SYSCTL_CMP_HN;

/** @brief DL_SYSCTL_CMP_LP */
typedef enum
{
    DL_SYSCTL_CMP_LP0 = 0,
    DL_SYSCTL_CMP_LP1 = 1,
    DL_SYSCTL_CMP_LP2 = 2,
    DL_SYSCTL_CMP_LP3 = 3,
    DL_SYSCTL_CMP_LP4 = 4,
    DL_SYSCTL_CMP_LP5 = 5,
    DL_SYSCTL_CMP_LP6 = 6,
} DL_SYSCTL_CMP_LP;

/** @brief DL_SYSCTL_CMP_LN */
typedef enum
{
    DL_SYSCTL_CMP_LN0 = 0,
    DL_SYSCTL_CMP_LN1 = 1,
} DL_SYSCTL_CMP_LN;

/** @brief DL_SYSCTL_InternalTestNode*/
typedef enum
{
    DL_SYSCTL_TEST_NODE_VDDCORE = 1,
    DL_SYSCTL_TEST_NODE_VDDA    = 2,
    DL_SYSCTL_TEST_NODE_VSSA    = 3,
    DL_SYSCTL_TEST_NODE_VREFLO  = 4,
    DL_SYSCTL_TEST_NODE_CDAC0H  = 5,
    DL_SYSCTL_TEST_NODE_CDAC0L  = 6,
    DL_SYSCTL_TEST_NODE_CDAC1H  = 7,
    DL_SYSCTL_TEST_NODE_CDAC1L  = 8,
    DL_SYSCTL_TEST_NODE_CDAC2H  = 9,
    DL_SYSCTL_TEST_NODE_CDAC2L  = 10,
    DL_SYSCTL_TEST_NODE_CDAC3H  = 11,
    DL_SYSCTL_TEST_NODE_CDAC3L  = 12,
} DL_SYSCTL_InternalTestNode;

/**
 * @name DL_SYSCTL_DACOUTEN
 *  @anchor DL_SYSCTL_DACOUTEN
 * @{
 */
/*! @brief Enable general purpose DAC functionality for CMPSS2 COMPDACL */
#define DL_SYSCTL_DACOUTEN_CMPSS2_DACL SYSCTL_CMPSSCTL_CMP2LDACOUTEN_MASK
/*! @brief Enable general purpose DAC functionality for CMPSS3 COMPDACL */
#define DL_SYSCTL_DACOUTEN_CMPSS3_DACL SYSCTL_CMPSSCTL_CMP3LDACOUTEN_MASK
/** @}*/

/** @brief DL_SYSTCTL_SRAM_BUS */
typedef enum
{
    /** @brief SRAM is connected to CBUS (Optimized for code execution)*/
    DL_SYSCTL_SRAM_CBUS = SYSCTL_AM13SPARESOCLOCK2_SRAM3_STATIC_MUX_SEL_CBUS,
    /** @brief SRAM is connected to SBUS (Optimized for data access)*/
    DL_SYSCTL_SRAM_SBUS = SYSCTL_AM13SPARESOCLOCK2_SRAM3_STATIC_MUX_SEL_SBUS
} DL_SYSCTL_SRAM_BUS;

/** @brief DL_SYSCTL_VREF_MODE */
typedef enum
{
    /** @brief External VREF*/
    DL_SYSCTL_VREF_EXTERNAL       = 0x001,
    /** @brief Internal 3.3V VREF*/
    DL_SYSCTL_VREF_INTERNAL_3_3_V = 0x000,
    /** @brief Internal 2.5V VREF*/
    DL_SYSCTL_VREF_INTERNAL_2_5_V = 0x100
} DL_SYSCTL_VREF_MODE;

/**
 *  @brief  Enable sleep on exit
 *
 *  Enables sleep on exit when the CPU moves from handler mode to thread mode.
 *  By enabling, allows an interrupt driven application to avoid returning to
 *  an empty main application.
 */
__STATIC_INLINE void DL_SYSCTL_enableSleepOnExit(void)
{
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
}

/**
 *  @brief  Disable sleep on exit
 *
 *  Disables sleep on exit when the CPU moves from handler mode to thread mode.
 */
__STATIC_INLINE void DL_SYSCTL_disableSleepOnExit(void)
{
    SCB->SCR &= ~(SCB_SCR_SLEEPONEXIT_Msk);
}

/**
 *  @brief  Check if sleep on exit is enabled
 */
__STATIC_INLINE bool DL_SYSCTL_isSleepOnExitEnabled(void)
{
    return ((SCB->SCR & SCB_SCR_SLEEPONEXIT_Msk) == SCB_SCR_SLEEPONEXIT_Msk);
}

/**
 *  @brief  Enable send event on pending bit
 *
 *  When enabled, any enabled event and all interrupts (including disabled
 *  interrupts) can wakeup the processor.
 */
__STATIC_INLINE void DL_SYSCTL_enableEventOnPend(void)
{
    SCB->SCR |= SCB_SCR_SEVONPEND_Msk;
}

/**
 *  @brief  Disable send event on pending bit
 *
 *  When disabled, only enabled interrupts or events can wake up the processor.
 *  Disabled interrupts are excluded.
 */
__STATIC_INLINE void DL_SYSCTL_disableEventOnPend(void)
{
    SCB->SCR &= ~(SCB_SCR_SEVONPEND_Msk);
}

/**
 *  @brief   Check if send event on pending bit is enabled
 *
 *  @return  Returns the enabled status of the send event on pending bit
 *
 *  @retval  true  Send event on pending bit is enabled
 *  @retval  false Send event on pending bit is disabled
 */
__STATIC_INLINE bool DL_SYSCTL_isEventOnPendEnabled(void)
{
    return ((SCB->SCR & SCB_SCR_SEVONPEND_Msk) == SCB_SCR_SEVONPEND_Msk);
}

/*!
 *  @brief  Change MCLK source
 *
 *  To ensure good clocking behavior, these are the recommended steps for transition.
 *  Valid sources and destinations: LFCLK, SYSOSC, HSCLK
 *
 *  Depending on current MCLK source, steps to switch to next MCLK source can vary.
 *  This is a macro that redirects to the different possible transitions.
 *
 *  Only valid for RUN modes. In low power modes, MCLK transitions are handled by hardware.
 *
 *  @note Different transition APIs may require different input parameters
 *  Transitions between LFCLK and HSCLK requires going through SYSOSC.
 *
 *  @sa DL_SYSCTL_switchMCLKfromSYSOSCtoHSCLK
 *  @sa DL_SYSCTL_switchMCLKfromHSCLKtoSYSOSC
 */
#define DL_SYSCTL_setMCLKSource(current, next, ...) DL_SYSCTL_switchMCLKfrom##current##to##next(__VA_ARGS__);

/**
 *  @brief  Change MCLK source from SYSOSC to HSCLK
 *
 *  @pre    The desired HSCLK source is enabled beforehand (SYSPLL, XTAL, HFCLK_IN).
 *  @post   MCLK source is switched to HSCLK, function will busy-wait until confirmed.
 *
 *  @param[in] source   Desired high-speed clock source
 */
void DL_SYSCTL_switchMCLKfromSYSOSCtoHSCLK(DL_SYSCTL_HSCLK_SOURCE source);

/**
 *  @brief  Change MCLK source from HSCLK to SYSOSC
 *
 *  @pre    MCLK is sourced from a valid, running HSCLK source (SYSPLL, XTAL, HFCLK_IN)
 *  @post   MCLK source is switched to SYSOSC, function will busy-wait until confirmed.
 *
 *  @note   No HSCLK sources are disabled by this function
 */
void DL_SYSCTL_switchMCLKfromHSCLKtoSYSOSC(void);

/**
 *  @brief     Set the RUN/SLEEP mode power policy to RUN0/SLEEP0
 *
 * In RUN0, the MCLK and the CPUCLK run from a fast clock source (SYSOSC,
 * HFCLK, or SYSPLL).
 *
 * Setting the RUN power policy will also set the SLEEP power policy.
 * The SLEEP mode behavior is always identical to RUN mode, just with the
 * CPUCLK disabled. As such, the SLEEP behavior is determined by the
 * configuration of the RUN mode. To actually enter SLEEP mode, you must call
 * \c __WFI() to wait for interrupts or \c __WFE() to wait for ARM events.
 * \c __WFI() is used in interrupt-driven applications, and \c __WFE() is used
 * for interactions between the interrupt handler and main application.
 *
 */
__STATIC_INLINE void DL_SYSCTL_setPowerPolicyRUNSLEEP(void)
{
    SCB->SCR &= ~(SCB_SCR_SLEEPDEEP_Msk);
}

/**
 *  @brief     Set the STOP mode power policy to STOP0
 *
 * In STOP0, the SYSOSC is left running at the current frequency when entering
 * STOP mode (either 32MHz, or 4MHz). ULPCLK is always limited
 * to 4MHz automatically by hardware, but SYSOSC is not disturbed to support
 * consistent operation of analog peripherals such as the ADC, OPA, or COMP.
 *
 * @post This API does not actually enter STOP mode. After using this API to
 * set the power policy, to enter STOP mode you must call \c __WFI() to
 * wait for interrupts or \c __WFE() to wait for ARM events. \c __WFI() is used
 * in interrupt-driven applications, and \c __WFE() is used for interactions
 * between the interrupt handler and main application.
 */
__STATIC_INLINE void DL_SYSCTL_setPowerPolicySTOP(void)
{
    SYSCTL->SOCLOCK.PMODECFG  = SYSCTL_PMODECFG_DSLEEP_STOP;
    SCB->SCR                 |= SCB_SCR_SLEEPDEEP_Msk;
}

/**
 *  @brief     Set the STANDBY mode power policy to STANDBY0
 *
 * In STANDBY0, all PD0 peripherals receive the ULPCLK and LFOSCCLK/LFCLK
 *
 * There are two STANDBY mode policy options: STANDBY0 and STANDBY1.
 *
 * @post This API does not actually enter STANDBY mode. After using this API to
 * set the power policy, to enter STANDBY mode you must call \c __WFI() to
 * wait for interrupts or \c __WFE() to wait for ARM events. \c __WFI() is used
 * in interrupt-driven applications, and \c __WFE() is used for interactions
 * between the interrupt handler and main application.
 */
__STATIC_INLINE void DL_SYSCTL_setPowerPolicySTANDBY0(void)
{
    SYSCTL->SOCLOCK.PMODECFG  = SYSCTL_PMODECFG_DSLEEP_STANDBY;
    SCB->SCR                 |= SCB_SCR_SLEEPDEEP_Msk;
    SYSCTL->SOCLOCK.MCLKCFG  &= ~(SYSCTL_MCLKCFG_STOPCLKSTBY_MASK);
}

/**
 *  @brief     Set the STANDBY mode power policy to STANDBY1
 *
 * In STANDBY1, only GPIO peripheral receive ULPCLK/LFCLK.
 * A GPIO Interrupt in STANDBY1 always triggers an asynchronous fast clock
 * request to wake the system.
 *
 * There are two STANDBY mode policy options: STANDBY0 and STANDBY1.
 *
 * @post This API does not actually enter STANDBY mode. After using this API to
 * set the power policy, to enter STANDBY mode you must call \c __WFI() to
 * wait for interrupts or \c __WFE() to wait for ARM events. \c __WFI() is used
 * in interrupt-driven applications, and \c __WFE() is used for interactions
 * between the interrupt handler and main application.
 */
__STATIC_INLINE void DL_SYSCTL_setPowerPolicySTANDBY1(void)
{
    SYSCTL->SOCLOCK.PMODECFG  = SYSCTL_PMODECFG_DSLEEP_STANDBY;
    SCB->SCR                 |= SCB_SCR_SLEEPDEEP_Msk;
    SYSCTL->SOCLOCK.MCLKCFG  |= SYSCTL_MCLKCFG_STOPCLKSTBY_MASK;
}

/**
 *  @brief     Get the STANDBY mode power policy
 *
 * Get which STANDBY power policy has been set.
 *
 *  @return  Returns the current STANDBY mode power policy
 *
 *  @retval  One of @ref DL_SYSCTL_POWER_POLICY_STANDBY
 */
DL_SYSCTL_POWER_POLICY_STANDBY DL_SYSCTL_getPowerPolicySTANDBY(void);

/**
 *  @brief     Set power policy to SHUTDOWN mode
 *
 * In SHUTDOWN mode, no clocks are available. The core regulator is completely
 * disabled and all SRAM and register contents are lost, with the exception of
 * the 4 bytes of general purpose memory in SYSCTL which may be used to store
 * state information. The BOR and bandgap circuit are disabled. The device may
 * wake up via a wake-up capable IO, a debug connection, or NRST. SHUTDOWN mode
 * has the lowest current consumption of any operating mode. Exiting SHUTDOWN
 * mode triggers a BOR.
 *
 * There is only one SHUTDOWN mode policy option: SHUTDOWN.
 *
 * @post This API does not actually enter SHUTDOWN mode. After using this API
 * to enable SHUTDOWN mode, to enter SHUTDOWN mode you must call \c __WFI() to
 * wait for interrupts or \c __WFE() to wait for ARM events. \c __WFI() is used
 * in interrupt-driven applications, and \c __WFE() is used for interactions
 * between the interrupt handler and main application.
 */
__STATIC_INLINE void DL_SYSCTL_setPowerPolicySHUTDOWN(void)
{
    SYSCTL->SOCLOCK.PMODECFG  = SYSCTL_PMODECFG_DSLEEP_SHUTDOWN;
    SCB->SCR                 |= SCB_SCR_SLEEPDEEP_Msk;
}

/**
 *  @brief     Enables power for the peripheral
 *
 *  @param[in] peripheral  One of @ref DL_SYSCTL_PERIPH_POWER
 */
__STATIC_INLINE void DL_SYSCTL_enablePower(DL_SYSCTL_PERIPH_POWER peripheral)
{
    uint32_t regOffset             = (uint32_t)peripheral >> 16U;
    uint32_t regMask               = 1U << ((uint32_t)peripheral & 0xFFU);
    HWREG(SYSCTL_BASE + regOffset) = HWREG(SYSCTL_BASE + regOffset) | SYSCTL_PWREN_SYSPERIPH_KEY_UNLOCK | regMask;
}

/**
 *  @brief     Disables power for the peripheral
 *
 *  @param[in] peripheral  One of @ref DL_SYSCTL_PERIPH_POWER
 */
__STATIC_INLINE void DL_SYSCTL_disablePower(DL_SYSCTL_PERIPH_POWER peripheral)
{
    uint32_t regOffset             = (uint32_t)peripheral >> 16U;
    uint32_t regMask               = 1U << ((uint32_t)peripheral & 0xFFU);
    HWREG(SYSCTL_BASE + regOffset) = (HWREG(SYSCTL_BASE + regOffset) | SYSCTL_PWREN_SYSPERIPH_KEY_UNLOCK) & ~regMask;
}

/**
 *  @brief Returns if the selected peripheral is powered
 *
 *  @param[in] peripheral  One of @ref DL_SYSCTL_PERIPH_POWER
 *
 *  @return true if power is enabled
 *  @return false if power is disabled
 */
__STATIC_INLINE bool DL_SYSCTL_isPowerEnabled(DL_SYSCTL_PERIPH_POWER peripheral)
{
    uint32_t regOffset = (uint32_t)peripheral >> 16U;
    uint32_t regMask   = 1U << ((uint32_t)peripheral & 0xFFU);
    return ((HWREG(SYSCTL_BASE + regOffset) & regMask) != 0U);
}

/**
 *  @brief     Resets the peripheral
 *
 *  @param[in] peripheral  One of @ref DL_SYSCTL_PERIPH_RESET
 */
__STATIC_INLINE void DL_SYSCTL_resetPeripheral(DL_SYSCTL_PERIPH_RESET peripheral)
{
    uint32_t regOffset = (uint32_t)peripheral >> 16U;
    uint32_t regMask   = 1U << ((uint32_t)peripheral & 0xFFU);

    /* Clear the RESET STICKY Bit*/
    HWREG(SYSCTL_BASE + regOffset + 4U) = SYSCTL_RSTCTL_CLEAR_SYSPERIPH_KEY_UNLOCK | regMask;

    /* Assert the RESET */
    HWREG(SYSCTL_BASE + regOffset) = SYSCTL_RSTCTL_ASSERT_SYSPERIPH_KEY_UNLOCK | regMask;
}

/**
 *  @brief     Resets the peripheral's reset sticky flag
 *
 *  @param[in] peripheral  One of @ref DL_SYSCTL_PERIPH_RESET
 */
__STATIC_INLINE void DL_SYSCTL_clearPeripheralResetFlag(DL_SYSCTL_PERIPH_RESET peripheral)
{
    uint32_t regOffset                  = (uint32_t)peripheral >> 16U;
    uint32_t regMask                    = 1U << ((uint32_t)peripheral & 0xFFU);
    HWREG(SYSCTL_BASE + regOffset + 4U) = SYSCTL_RSTCTL_CLEAR_SYSPERIPH_KEY_UNLOCK | regMask;
}

/**
 * @brief Check if a peripheral is reset
 */
__STATIC_INLINE bool DL_SYSCTL_isPeripheralReset(DL_SYSCTL_PERIPH_RESET peripheral)
{
    uint32_t regOffset = (uint32_t)peripheral >> 16U;
    uint32_t regMask   = 1U << ((uint32_t)peripheral & 0xFFU);
    return ((HWREG(SYSCTL_BASE + regOffset + 8U) & regMask) != 0U);
}

/**
 *  @brief      Resets the device
 *
 *  Resets the device using the type of reset selected. This function does not
 *  return, the reset will happen immediately.
 *
 *  @param[in]  resetType  Type of reset to perform. One of @ref
 *                         DL_SYSCTL_RESET.
 */
__STATIC_INLINE void DL_SYSCTL_resetDevice(DL_SYSCTL_RESET resetType)
{
    SYSCTL->SOCLOCK.RESETLEVEL = resetType;
    SYSCTL->SOCLOCK.RESETCMD   = SYSCTL_RESETCMD_KEY_VALUE | SYSCTL_RESETCMD_GO_TRUE;
}

/**
 *  @brief  Return byte that is stored in RSTCAUSE.
 *
 *  @return The cause of reset. One of @ref DL_SYSCTL_RESET_CAUSE
 */
__STATIC_INLINE DL_SYSCTL_RESET_CAUSE DL_SYSCTL_getResetCause(void)
{
    uint32_t resetCause = SYSCTL->SOCLOCK.RSTCAUSE & SYSCTL_RSTCAUSE_ID_MASK;

    return (DL_SYSCTL_RESET_CAUSE)(resetCause);
}

/**
 *  @brief      Enable SYSCTL interrupts
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to enable. Bitwise OR of
 *                             @ref DL_SYSCTL_INTERRUPT.
 */
__STATIC_INLINE void DL_SYSCTL_enableInterrupt(uint32_t interruptMask)
{
    SYSCTL->SOCLOCK.IMASK |= interruptMask;
}

/**
 *  @brief      Disable SYSCTL interrupts
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to enable. Bitwise OR of
 *                             @ref DL_SYSCTL_INTERRUPT.
 */
__STATIC_INLINE void DL_SYSCTL_disableInterrupt(uint32_t interruptMask)
{
    SYSCTL->SOCLOCK.IMASK &= ~(interruptMask);
}

/**
 *  @brief      Check which SYSCTL interrupts are enabled
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_SYSCTL_INTERRUPT.
 *
 *  @return     Which of the requested SYSCTL interrupts are enabled
 *
 *  @retval     Bitwise OR of @ref DL_SYSCTL_INTERRUPT values
 */
__STATIC_INLINE uint32_t DL_SYSCTL_getEnabledInterrupts(uint32_t interruptMask)
{
    return (SYSCTL->SOCLOCK.IMASK & interruptMask);
}

/**
 *  @brief      Check interrupt flag of enabled SYSCTL interrupts
 *
 *  Checks if any of the SYSCTL interrupts that were previously enabled are
 *  pending.
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_SYSCTL_INTERRUPT.
 *
 *  @return     Which of the requested SYSCTL interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_SYSCTL_INTERRUPT values
 *
 *  @sa         DL_SYSCTL_enableInterrupt
 */
__STATIC_INLINE uint32_t DL_SYSCTL_getEnabledInterruptStatus(uint32_t interruptMask)
{
    return (SYSCTL->SOCLOCK.MIS & interruptMask);
}

/**
 *  @brief      Check interrupt flag of any SYSCTL interrupt
 *
 *  Checks if any of the SYSCTL interrupts are pending. Interrupts do not have to
 *  be previously enabled.
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_SYSCTL_INTERRUPT.
 *
 *  @return     Which of the requested SYSCTL interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_SYSCTL_INTERRUPT values
 */
__STATIC_INLINE uint32_t DL_SYSCTL_getRawInterruptStatus(uint32_t interruptMask)
{
    return (SYSCTL->SOCLOCK.RIS & interruptMask);
}

/**
 *  @brief      Get highest priority pending SYSCTL interrupt
 *
 *  Checks if any of the SYSCTL interrupts are pending. Interrupts do not have to
 *  be previously enabled.
 *
 *  @return     The highest priority pending SYSCTL interrupt
 *
 *  @retval     One of @ref DL_SYSCTL_IIDX values
 */
__STATIC_INLINE DL_SYSCTL_IIDX DL_SYSCTL_getPendingInterrupt(void)
{
    return (DL_SYSCTL_IIDX)(SYSCTL->SOCLOCK.IIDX);
}

/**
 *  @brief      Clear pending SYSCTL interrupts
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to clear. Bitwise OR of
 *                             @ref DL_SYSCTL_INTERRUPT.
 */
__STATIC_INLINE void DL_SYSCTL_clearInterruptStatus(uint32_t interruptMask)
{
    SYSCTL->SOCLOCK.ICLR = interruptMask;
}

/**
 *  @brief      Force SYSCTL interrupts
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to force. Bitwise OR of
 *                             @ref DL_SYSCTL_INTERRUPT.
 */
__STATIC_INLINE void DL_SYSCTL_forceInterrupt(uint32_t interruptMask)
{
    SYSCTL->SOCLOCK.ISET = interruptMask;
    __DSB();
    __ISB();
}

/**
 *  @brief      Check interrupt flag of any SYSCTL non-maskable interrupt
 *
 *  Checks if any of the SYSCTL non-maskable interrupts are pending. Interrupts
 *  do not have to be previously enabled.
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_SYSCTL_NMI.
 *
 *  @return     Which of the requested SYSCTL non-maskable interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_SYSCTL_NMI values
 */
__STATIC_INLINE uint32_t DL_SYSCTL_getRawNonMaskableInterruptStatus(uint32_t interruptMask)
{
    return (SYSCTL->SOCLOCK.NMIRIS & interruptMask);
}

/**
 *  @brief      Get highest priority pending SYSCTL non-maskable interrupt
 *
 *  Checks if any of the SYSCTL non-maskable interrupts are pending. Interrupts
 *  do not have to be previously enabled.
 *
 *  @return     The highest priority pending SYSCTL non-maskable interrupt
 *
 *  @retval     One of @ref DL_SYSCTL_NMI_IIDX values
 */
__STATIC_INLINE DL_SYSCTL_NMI_IIDX DL_SYSCTL_getPendingNonMaskableInterrupt(void)
{
    return (DL_SYSCTL_NMI_IIDX)(SYSCTL->SOCLOCK.NMIIIDX);
}

/**
 *  @brief      Clear pending SYSCTL non-maskable interrupts
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to clear. Bitwise OR of
 *                             @ref DL_SYSCTL_NMI.
 */
__STATIC_INLINE void DL_SYSCTL_clearNonMaskableInterruptStatus(uint32_t interruptMask)
{
    SYSCTL->SOCLOCK.NMIICLR = interruptMask;
}

/**
 *  @brief      Force SYSCTL non-maskable interrupts
 *
 *  @param[in]  interruptMask  Bit mask of interrupts to force. Bitwise OR of
 *                             @ref DL_SYSCTL_NMI.
 */
__STATIC_INLINE void DL_SYSCTL_forceNonMaskableInterrupt(uint32_t interruptMask)
{
    SYSCTL->SOCLOCK.NMIISET = interruptMask;
    __DSB();
    __ISB();
}

/**
 *  @brief  Set the behavior when a Flash ECC double error detect (DED) occurs
 *
 *  Configures whether a Flash ECC double error detect (DED) will trigger
 *  a SYSRST or an NMI (non-maskable interrupt). By default, this error will
 *  trigger a SYSRST.
 *
 *  @param[in] behavior The behavior when a Flash ECC DED error occurrs
 *
 *  @sa        DL_SYSCTL_enableNonMaskableInterrupt
 */
__STATIC_INLINE void DL_SYSCTL_setFlashDEDErrorBehavior(DL_SYSCTL_ERROR_BEHAVIOR behavior)
{
    DL_Common_updateReg(&SYSCTL->SOCLOCK.SYSTEMCFG,
                        (((uint32_t)behavior << SYSCTL_SYSTEMCFG_FLASHECCRSTDIS_OFS)) | SYSCTL_SYSTEMCFG_KEY_VALUE,
                        (SYSCTL_SYSTEMCFG_FLASHECCRSTDIS_MASK | SYSCTL_SYSTEMCFG_KEY_MASK));
}

/**
 *  @brief  Get the behavior when a Flash ECC double error detect (DED) occurs
 *
 *  By default, this error will trigger a SYSRST.
 *
 *  @return The behavior when a Flash ECC DED error occurs
 *
 *  3@retval One of @ref DL_SYSCTL_ERROR_BEHAVIOR
 */
__STATIC_INLINE DL_SYSCTL_ERROR_BEHAVIOR DL_SYSCTL_getFlashDEDErrorBehavior(void)
{
    uint32_t behavior =
        (SYSCTL->SOCLOCK.SYSTEMCFG & SYSCTL_SYSTEMCFG_FLASHECCRSTDIS_MASK) >> SYSCTL_SYSTEMCFG_FLASHECCRSTDIS_OFS;

    return (DL_SYSCTL_ERROR_BEHAVIOR)(behavior);
}

/**
 *  @brief  Set the behavior when a WWDT0 error occurs
 *
 *  Configures whether a WWDT0 error will trigger a BOOTRST or an NMI
 * (non-maskable interrupt). By default, this error will trigger a BOOTRST.
 *
 *  @param[in] behavior The behavior when a Flash ECC DED occurrs
 *
 *  @sa        DL_SYSCTL_enableNonMaskableInterrupt
 */
__STATIC_INLINE void DL_SYSCTL_setWWDT0ErrorBehavior(DL_SYSCTL_ERROR_BEHAVIOR behavior)
{
    DL_Common_updateReg(&SYSCTL->SOCLOCK.SYSTEMCFG,
                        (((uint32_t)behavior << SYSCTL_SYSTEMCFG_WWDTLP0RSTDIS_OFS)) | SYSCTL_SYSTEMCFG_KEY_VALUE,
                        (SYSCTL_SYSTEMCFG_WWDTLP0RSTDIS_MASK | SYSCTL_SYSTEMCFG_KEY_MASK));
}

/**
 *  @brief  Get the behavior when a WWDT0 error occurs
 *
 *  By default, this error will trigger a BOOTRST.
 *
 *  @return The behavior when a WWDT0 error occurs
 *
 *  @retval One of @ref DL_SYSCTL_ERROR_BEHAVIOR
 */
__STATIC_INLINE DL_SYSCTL_ERROR_BEHAVIOR DL_SYSCTL_getWWDT0ErrorBehavior(void)
{
    uint32_t behavior =
        (SYSCTL->SOCLOCK.SYSTEMCFG & SYSCTL_SYSTEMCFG_WWDTLP0RSTDIS_MASK) >> SYSCTL_SYSTEMCFG_WWDTLP0RSTDIS_OFS;

    return (DL_SYSCTL_ERROR_BEHAVIOR)(behavior);
}

/**
 *  @brief   Get the source for the Main Clock (MCLK)
 *
 *  @return  The source for the Main Clock (MCLK)
 *
 *  @retval  One of @ref DL_SYSCTL_MCLK_SOURCE
 */
__STATIC_INLINE DL_SYSCTL_MCLK_SOURCE DL_SYSCTL_getMCLKSource(void)
{
    uint32_t source = SYSCTL->SOCLOCK.MCLKCFG & (SYSCTL_MCLKCFG_USEHSCLK_MASK | SYSCTL_MCLKCFG_USELFCLK_MASK);

    return (DL_SYSCTL_MCLK_SOURCE)(source);
}

/**
 *  @brief   Returns status of the different clocks in CKM
 *
 *  @return  Full status of all clock selections
 *
 *  @retval  Bitwise OR of @ref DL_SYSCTL_CLK_STATUS.
 */
__STATIC_INLINE uint32_t DL_SYSCTL_getClockStatus(void)
{
    return (SYSCTL->SOCLOCK.CLKSTATUS);
}

/**
 *  @brief   Returns general status of SYSCTL
 *
 *  @return  Full status of all general conditions in SYSCTL
 *
 *  @retval  Bitwise OR of @ref DL_SYSCTL_STATUS.
 */
__STATIC_INLINE uint32_t DL_SYSCTL_getStatus(void)
{
    return (SYSCTL->SOCLOCK.SYSSTATUS);
}

/**
 *  @brief   Clear the ECC error bits in SYSSTATUS
 *
 *  The ECC error bits in SYSSTATUS are sticky (they remain set when an ECC
 *  error occurs even if future reads do not have errors), and can be
 *  cleared through this API.
 */
__STATIC_INLINE void DL_SYSCTL_clearECCErrorStatus(void)
{
    SYSCTL->SOCLOCK.SYSSTATUSCLR = (SYSCTL_SYSSTATUSCLR_ALLECC_CLEAR | SYSCTL_SYSSTATUSCLR_KEY_VALUE);
}

/**
 *  @brief     Configure SYSPLL output frequencies
 *
 *  @pre    SYSPLL is disabled (SYSPLLOFF in CLKSTATUS)
 *  @pre    SYSOSC is running at base frequency (32MHz) even if HFCLK is the
 *          SYSPLL reference
 *  @post   SYSPLL has completed startup and outputs chosen frequencies
 *
 *  @note   For practical purposes, it is not required to wait until SYSPLL
 *          completes startup, but do not go into STOP/STANDBY or use SYSPLL
 *          until completed.
 *
 *  @param[in]  config  Pointer to the SYSPLL configuration struct
 *              @ref DL_SYSCTL_SYSPLLConfig. Elements sysPLLRef, pDiv, and
 *              inputFreq control desired startup time versus power consumption.
 */
void DL_SYSCTL_configSYSPLL(DL_SYSCTL_SYSPLLConfig *config);

/**
 *  @brief     Set the dividers for Semi (MCLK/2) and Quarter (MCLK/4) clock domains
 *
 *  Semi clock domain IPs are connected on Peripheral interconnect (PI) that operates
 *  on MCLK divide by two clock ( i.e. maximum frequency/2). Divider allows
 *  option of /2 or bypass.
 *
 *  Quarter clock domain IPs are connected on CPU interconnect (CI) that operates
 *  on MCLK divide by four clock ( i.e. maximum frequency/4). Quarter divider
 *  allows /2, /4 divider option besides bypass.
 *
 *  The ULPCLK is the bus clock for peripherals in the PD0 power domain. This is
 *  derived from quarter domain i.e. MCLK/4 clock tree. ULPCLK must be maintained
 *  to be ≤50MHz at all times.
 *
 *  \b Valid \b options :
 * | Freq Range (MHz) | MCLK2 | MCLK4 |
 * |------------------|-------|-------|
 * |  200-100         |  /2   |  /4   |
 * |  100-50          |  /1   |  /2   |
 * |^                 |  /1   |  /4   |
 * |^                 |  /2   |  /2   |
 * |^                 |  /2   |  /4   |
 * |  <50             |  /1   |  /1   |
 * |^                 |  /1   |  /2   |
 * |^                 |  /1   |  /4   |
 * |^                 |  /2   |  /2   |
 * |^                 |  /2   |  /4   |
 *
 *  @param[in] divider  Clock dividers @ref DL_SYSCTL_MCLK_DIV
 *
 */
__STATIC_INLINE void DL_SYSCTL_setMCLKDivider(DL_SYSCTL_MCLK_DIV divider)
{
    DL_Common_updateReg(&SYSCTL->SOCLOCK.MCLKCFG, (uint32_t)divider, SYSCTL_MCLKCFG_MCLKDIVCFG_MASK);
}

/**
 *  @brief Change HFCLK source to external crystal XTAL
 *
 * To use the XTAL, a crystal or resonator must be populated between X1 and X2
 * pins. Find more info in XTAL section in the device Technical Reference Manual.
 *
 * The IOMUX must be configured to enable XTAL functionality on the X1 and X2 pins.
 *
 * If the HFCLK startup monitor is enabled, then the XTAL will be checked after
 * the amount of time specified by the startupTime parameter.
 * This basic implementation will busy-wait until XTAL oscillator is stabilized.
 * But a more advanced implementation can do other things while the XTAL is
 * stabilizing. You can enable HFCLKGOOD interrupt, or check CLKSTATUS.HFCLKGOOD
 * when convenient, as long as you do not switch the source before HFCLKGOOD is set.
 *
 * If the HFCLK startup monitor is disabled, then this implementation will not
 * check if the XTAL oscillator is stabilized.
 *
 *  @param[in]  startupTime     XTAL startup time
 *  @param[in]  monitorEnable   Whether to enable the HFCLK startup monitor

 */
void DL_SYSCTL_setHFCLKSourceXTAL(uint32_t startupTime, bool monitorEnable);

/**
 *  @brief      Disable the SYSPLL
 *
 *  If SYSPLL is already enabled, application software should not disable the
 *  SYSPLL until the SYSPLLGOOD or SYSPLOFF bit is set in the CLKSTATUS
 *  register, indicating that the SYSPLL transitioned to a stable active or a
 *  stable dead state.
 *
 *  @sa DL_SYSCTL_getClockStatus
 */
__STATIC_INLINE void DL_SYSCTL_disableSYSPLL(void)
{
    SYSCTL->SOCLOCK.HSCLKEN &= ~(SYSCTL_HSCLKEN_SYSPLLEN_MASK);
}

/**
 *  @brief      Disable the XTAL
 *
 *  If XTAL is already enabled, application software must verify that either an
 *  HFCLKGOOD indication or an HFCLKOFF (off/dead) indication in the CLKSTATUS
 *  register was asserted by hardware before attempting to disable the XTAL
 *  by setting OSCOFF. When disabling the XTAL by clearing OSCOFF, the XTAL
 *  must not be re-enabled again until the HFCLKOFF bit in the CLKSTATUS
 *  register is set by hardware. TODO: Is this comment valid?
 *
 *  @sa DL_SYSCTL_getClockStatus
 */
__STATIC_INLINE void DL_SYSCTL_disableXTAL(void)
{
    SYSCTL->SOCLOCK.XTALCR |= SYSCTL_XTALCR_OSCOFF_MASK;
}

// TODO: Add function for SE mode?

/**
 *  @brief Change HFCLK source to external digital HFCLK_IN
 *
 * HFCLK_IN can be used to bypass the XTAL circuit and bring 4-48MHz typical
 * frequency digital clock into the devce as HFCLK source instead of XTAL.
 *
 * HFCLK_IN is a digital clock input compatible with digital square wave CMOS
 * clock inputs and should have typical duty cycle of 50%.
 *
 * Digital clock input must be valid and GPIO/IOMUX must be configured
 * separately on the appropriate pin before calling this function to enable
 * HFCLK_IN.
 */
__STATIC_INLINE void DL_SYSCTL_setHFCLKSourceHFCLKIN(void)
{
    /* Some crystal configurations are retained in lower reset levels. Set
     * default behavior of XTAL to keep a consistent behavior regardless of
     * reset level. */
    DL_SYSCTL_disableXTAL();

    SYSCTL->SOCLOCK.HSCLKEN |= SYSCTL_HSCLKEN_USEEXTHFCLK_ENABLE;
}

/**
 *  @brief   Get the source of High Speed Clock (HSCLK)
 *
 * HSCLK can be sourced by SYSPLL or HFCLK.
 * HSCLK is an optional source for MCLK alongside SYSOSC or LFCLK.
 *
 *  @return  The source of HSCLK. One of @ref DL_SYSCTL_HSCLK_SOURCE.
 */
__STATIC_INLINE DL_SYSCTL_HSCLK_SOURCE DL_SYSCTL_getHSCLKSource(void)
{
    uint32_t source = SYSCTL->SOCLOCK.HSCLKCFG & SYSCTL_HSCLKCFG_HSCLKSEL_MASK;

    return (DL_SYSCTL_HSCLK_SOURCE)(source);
}

/**
 *  @brief   Set the source of High Speed Clock (HSCLK)
 *
 * HSCLK can be sourced by SYSPLL or HFCLK.
 * HSCLK is an optional source for MCLK alongside SYSOSC or LFCLK.
 *
 *  @param[in]  source  The source of HSCLK. One of @ref DL_SYSCTL_HSCLK_SOURCE.
 */
__STATIC_INLINE void DL_SYSCTL_setHSCLKSource(DL_SYSCTL_HSCLK_SOURCE source)
{
    SYSCTL->SOCLOCK.HSCLKCFG = (uint32_t)source;
}

/**
 *  @brief   Set the source of CAN Clock (CANCLK)
 *  @param[in]  source  The source of CANCLK. One of @ref DL_SYSCTL_CANCLK_SOURCE.
 */
__STATIC_INLINE void DL_SYSCTL_setCANCLKSource(DL_SYSCTL_CANCLK_SOURCE source)
{
    if (source == DL_SYSCTL_CANCLK_SOURCE_HFCLK)
    {
        DL_Common_updateReg(&SYSCTL->SOCLOCK.GENCLKCFG, SYSCTL_GENCLKCFG_CANCLKSRC_HFCLK,
                            SYSCTL_GENCLKCFG_CANCLKSRC_MASK);
    }
    else
    {
        DL_Common_updateReg(&SYSCTL->SOCLOCK.GENCLKCFG, SYSCTL_GENCLKCFG_CANCLKSRC_SYSPLLOUT,
                            SYSCTL_GENCLKCFG_CANCLKSRC_MASK);
        DL_Common_updateReg(&SYSCTL->SOCLOCK.GENCLKEN, (uint32_t)source,
                            SYSCTL_GENCLKEN_CANEXTDIVEN_MASK | SYSCTL_GENCLKEN_EXTDIVCAN_MASK);
    }
}

/**
 *  @brief  Enable the External Clock (CLK_OUT)
 *
 *  CLK_OUT is provided for pushing out digital clocks to external circuits, such
 *  as an external ADC which does not have its own clock source.
 *
 *  IOMUX setting for CLK_OUT must be configured before using this function.
 *
 *  CLK_OUT has a typical duty cycle of 50% if clock source is HFCLK, SYSPLLOUT1,
 *  SYSOSC, or LFCLK. If source is MCLK, ULPCLK, or MFCLK, duty cycle is not
 *  guaranteed to be 50%.
 *
 *  This function performs multiple operations:
 *  1) Sets the CLK_OUT source
 *  2) Sets the CLK_OUT divider value
 *  3) Enables the CLK_OUT divider, which can be disabled by @ref DL_SYSCTL_disableExternalClockDivider
 *  4) Enables the CLK_OUT, which can be disabled by @ref DL_SYSCTL_disableExternalClock
 *
 *  @param[in]  source  The source of CLK_OUT. One of @ref DL_SYSCTL_CLK_OUT_SOURCE.
 *  @param[in]  divider The divider of CLK_OUT. One of @ref DL_SYSCTL_CLK_OUT_DIVIDE.
 *
 *  @sa DL_SYSCTL_disableExternalClock
 *  @sa DL_SYSCTL_disableExternalClockDivider
 */
__STATIC_INLINE void DL_SYSCTL_enableExternalClock(DL_SYSCTL_CLK_OUT_SOURCE source, DL_SYSCTL_CLK_OUT_DIVIDE divider)
{
    DL_Common_updateReg(
        &SYSCTL->SOCLOCK.GENCLKCFG, (uint32_t)divider | (uint32_t)source,
        SYSCTL_GENCLKCFG_EXCLKDIVEN_MASK | SYSCTL_GENCLKCFG_EXCLKDIVVAL_MASK | SYSCTL_GENCLKCFG_EXCLKSRC_MASK);
    SYSCTL->SOCLOCK.GENCLKEN |= SYSCTL_GENCLKEN_EXCLKEN_ENABLE;
}

/**
 *  @brief  Disable the External Clock (CLK_OUT)
 *  @sa DL_SYSCTL_enableExternalClock
 */
__STATIC_INLINE void DL_SYSCTL_disableExternalClock(void)
{
    SYSCTL->SOCLOCK.GENCLKEN &= ~(SYSCTL_GENCLKEN_EXCLKEN_ENABLE);
}

/**
 *  @brief  Disable the External Clock (CLK_OUT) Divider
 *  @sa DL_SYSCTL_enableExternalClock
 */
__STATIC_INLINE void DL_SYSCTL_disableExternalClockDivider(void)
{
    SYSCTL->SOCLOCK.GENCLKCFG &= ~(SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE);
}

/**
 * @brief Set PLL divider
 */
__STATIC_INLINE void DL_SYSCTL_enablePLLDivider(DL_SYSCTL_PLL_DIVIDER divider)
{
    SYSCTL->SOCLOCK.GENCLKEN = (SYSCTL->SOCLOCK.GENCLKEN & ~SYSCTL_GENCLKEN_EXTDIVMCLK_MASK) |
                               SYSCTL_GENCLKEN_MCLKEXTDIVEN_ENABLE | (uint32_t)divider;
}

/**
 * @brief Disable PLL divider
 *  @sa DL_SYSCTL_enablePLLDivider
 */
__STATIC_INLINE void DL_SYSCTL_disablePLLDivider(void)
{
    SYSCTL->SOCLOCK.GENCLKEN &= ~SYSCTL_GENCLKEN_MCLKEXTDIVEN_ENABLE;
}

/**
 *  @brief  Blocks all asynchronous fast clock requests
 *
 *  To block specific async fast clock requests on certain IP, refer to their
 *  individual driverlib. Examples include: RTC, UART, SPI, I2C.
 */
__STATIC_INLINE void DL_SYSCTL_blockAllAsyncFastClockRequests(void)
{
    SYSCTL->SOCLOCK.SYSOSCCFG |= SYSCTL_SYSOSCCFG_BLOCKASYNCALL_ENABLE;
}

/**
 *  @brief  Allows all asynchronous fast clock requests
 *
 *  Although this allows all async fast clock requests, individual IPs may still
 *  be blocking theirs.
 *
 *  To allow specific async fast clock requests on certain IP, refer to their
 *  individual driverlib. Examples include: RTC, UART, SPI, I2C, GPIO.
 */
__STATIC_INLINE void DL_SYSCTL_allowAllAsyncFastClockRequests(void)
{
    SYSCTL->SOCLOCK.SYSOSCCFG &= ~(SYSCTL_SYSOSCCFG_BLOCKASYNCALL_ENABLE);
}

/**
 *  @brief  Generates an asynchronous fast clock request upon any IRQ request to CPU.
 *
 *  Provides lowest latency interrupt handling regardless of system clock speed.
 *  Blockable by @ref DL_SYSCTL_blockAllAsyncFastClockRequests
 *
 *  @sa DL_SYSCTL_blockAllAsyncFastClockRequests
 */
__STATIC_INLINE void DL_SYSCTL_enableFastCPUEventHandling(void)
{
    SYSCTL->SOCLOCK.SYSOSCCFG |= SYSCTL_SYSOSCCFG_FASTCPUEVENT_ENABLE;
}

/**
 *  @brief  Maintains current system clock speed for IRQ request to CPU.
 *
 *  Latency for interrupt handling will be higher at lower system clock speeds.
 */
__STATIC_INLINE void DL_SYSCTL_disableFastCPUEventHandling(void)
{
    SYSCTL->SOCLOCK.SYSOSCCFG &= ~(SYSCTL_SYSOSCCFG_FASTCPUEVENT_ENABLE);
}

/**
 *  @brief  Read Frequency Clock Counter (FCC)
 *  @return  22-bit value of Frequency Clock Counter (FCC)
 */
__STATIC_INLINE uint32_t DL_SYSCTL_readFCC(void)
{
    return (SYSCTL->SOCLOCK.FCC);
}

/**
 *  @brief  Start Frequency Clock Counter (FCC)
 *
 *  If FCC_IN is already logic high, counting starts immediately.
 *  When using level trigger, FCC_IN should be low when GO is set, and trigger
 *  pulse should be sent to FCC_IN after starting FCC.
 */
__STATIC_INLINE void DL_SYSCTL_startFCC(void)
{
    SYSCTL->SOCLOCK.FCCCMD = (SYSCTL_FCCCMD_KEY_VALUE | SYSCTL_FCCCMD_GO_TRUE);
}

/**
 *  @brief  Returns whether FCC is done capturing
 *
 *  When capture completes, FCCDONE is set by hardware.
 *  FCCDONE is read-only and is automatically cleared by hardware when a new
 *  capture is started.
 *
 *  @return Whether FCC is done or not
 *  @retval true or false (boolean)
 */
__STATIC_INLINE bool DL_SYSCTL_isFCCDone(void)
{
    return (DL_SYSCTL_getClockStatus() & SYSCTL_CLKSTATUS_FCCDONE_DONE) == SYSCTL_CLKSTATUS_FCCDONE_DONE;
}

/**
 *  @brief     Configure the Frequency Clock Counter (FCC)
 *
 *  FCC enables flexible in-system testing and calibration of a variety of oscillators
 *  and clocks on the device. The FCC counts the number of clock periods seen on the
 *  selected clock source within a known fixed trigger period (derived from a secondary
 *  reference source) to provide an estimation of the frequency of the source clock.
 *
 *  @param[in] trigLvl  Determines if active high level trigger or rising-edge
 *                      to rising-edge. One of @ref DL_SYSCTL_FCC_TRIG_TYPE.
 *                      @sa DL_SYSCTL_setFCCPeriods must be called to configure
 *                      number of rising-edge to rising-edge periods when
 *                      DL_SYSCTL_FCC_TRIG_TYPE_RISE_RISE is selected.
 *  @param[in] trigSrc  Determines which clock source to trigger FCC from. One of
 *                      @ref DL_SYSCTL_FCC_TRIG_SOURCE.
 *  @param[in] clkSrc   Which clock source to capture and measure frequency of. One of
 *                      @ref DL_SYSCTL_FCC_CLOCK_SOURCE.
 */
void DL_SYSCTL_configFCC(DL_SYSCTL_FCC_TRIG_TYPE trigLvl, DL_SYSCTL_FCC_TRIG_SOURCE trigSrc,
                         DL_SYSCTL_FCC_CLOCK_SOURCE clkSrc);

/**
 *  @brief     Sets number of rising-edge to rising-edge period for Frequency
 *             Clock Counter (FCC)
 *
 *  Set the number of rising-edge to rising-edge period for Frequency
 *             Clock Counter (FCC)
 *
 *  @param[in] periods  One of @ref DL_SYSCTL_FCC_TRIG_CNT
 */
__STATIC_INLINE void DL_SYSCTL_setFCCPeriods(DL_SYSCTL_FCC_TRIG_CNT periods)
{
    DL_Common_updateReg(&SYSCTL->SOCLOCK.GENCLKCFG, (uint32_t)periods, SYSCTL_GENCLKCFG_FCCTRIGCNT_MASK);
}

/**
 *  @brief     Gets number of rising-edge to rising-edge period for Frequency
 *             Clock Counter (FCC)
 *
 *  @return     One of @ref DL_SYSCTL_FCC_TRIG_CNT
 */
__STATIC_INLINE DL_SYSCTL_FCC_TRIG_CNT DL_SYSCTL_getFCCPeriods(void)
{
    uint32_t periods = SYSCTL->SOCLOCK.GENCLKCFG & SYSCTL_GENCLKCFG_FCCTRIGCNT_MASK;

    return (DL_SYSCTL_FCC_TRIG_CNT)(periods);
}

/**
 *  @brief  Enable Frequency Correction Loop (FCL) in Internal Resistor Mode
 *
 *  Once FCL is enable, it cannot be disabled by software. A BOOTRST is required.
 */
__STATIC_INLINE void DL_SYSCTL_enableSYSOSCFCL(void)
{
    SYSCTL->SOCLOCK.SYSOSCFCLCTL = (SYSCTL_SYSOSCFCLCTL_KEY_VALUE | SYSCTL_SYSOSCFCLCTL_SETUSEFCL_TRUE);
}

/**
 *  @brief  Enable write protection of selected SYSCTL registers
 *
 *  Protecting writes to configuration registers in SYSCTL can add a layer of
 *  robustness against unintended changes during runtime.
 *
 *  @note Does not protect all SYSCTL registers, see TRM for more detail.
 */
__STATIC_INLINE void DL_SYSCTL_enableWriteLock(void)
{
    SYSCTL->SOCLOCK.WRITELOCK = SYSCTL_WRITELOCK_ACTIVE_ENABLE;
}

/**
 *  @brief  Disable write protection of selected SYSCTL registers
 *
 *  Protecting writes to configuration registers in SYSCTL can add a layer of
 *  robustness against unintended changes during runtime.
 *
 *  @note Does not protect all SYSCTL registers, see TRM for more detail.
 */
__STATIC_INLINE void DL_SYSCTL_disableWriteLock(void)
{
    SYSCTL->SOCLOCK.WRITELOCK = SYSCTL_WRITELOCK_ACTIVE_DISABLE;
}

/**
 *  @brief  Return byte that was saved through SHUTDOWN
 *
 *  Shutdown memory persists beyond BOR, BOOTRST, and SYSRST.
 *
 *  @note Parity bits and parity fault checking is done by hardware.
 *
 *  @param[in] index   One of @ref DL_SYSCTL_SHUTDOWN_STORAGE_BYTE.
 *
 *  @return 8-bit value of Shutdown Storage Byte.
 */
__STATIC_INLINE uint8_t DL_SYSCTL_getShutdownStorageByte(DL_SYSCTL_SHUTDOWN_STORAGE_BYTE index)
{
    return (HWREGB(SYSCTL_BASE + SYSCTL_SHUTDNSTORE0 + (uint32_t)index));
}

/**
 *  @brief  Save a byte to SHUTDOWN memory
 *
 *  Shutdown memory persists beyond BOR, BOOTRST, and SYSRST.
 *
 *  @note Parity bits and parity fault checking is done by hardware.
 *
 *  @param[in] index   One of @ref DL_SYSCTL_SHUTDOWN_STORAGE_BYTE.
 *  @param[in] data    8-bit data to save in memory
 */
__STATIC_INLINE void DL_SYSCTL_setShutdownStorageByte(DL_SYSCTL_SHUTDOWN_STORAGE_BYTE index, uint8_t data)
{
    HWREGB(SYSCTL_BASE + SYSCTL_SHUTDNSTORE0 + (uint32_t)index) = data;
}

/**
 *  @brief  Enable SHUTDOWN IO Release
 *
 *  After shutdown, IO is locked in previous state.
 *
 *  @note Release IO after re-configuring IO to their proper state.
 */
__STATIC_INLINE void DL_SYSCTL_releaseShutdownIO(void)
{
    SYSCTL->SOCLOCK.SHDNIOREL = (SYSCTL_SHDNIOREL_KEY_VALUE | SYSCTL_SHDNIOREL_RELEASE_TRUE);
}

/**
 *  @brief  Disable the reset functionality of the NRST pin
 *
 *  Disabling the NRST pin allows the pin to be configured as a GPIO.
 *  Once disabled, the reset functionality can only be re-enabled by a POR.
 *
 *  @note The register is write-only, so the EXRSTPIN register
 *        will always appear as "Disabled" in the debugger
 */
__STATIC_INLINE void DL_SYSCTL_disableNRSTPin(void)
{
    SYSCTL->SOCLOCK.EXRSTPIN = (SYSCTL_EXRSTPIN_KEY_VALUE | SYSCTL_EXRSTPIN_DISABLE_TRUE);
}

/**
 *  @brief  Disable Serial Wire Debug (SWD) functionality
 *
 *  SWD pins are enabled by default after cold start to allow a debug connection.
 *  It is possible to disable SWD on these pins to use for other functionality.
 *
 *  @post SWD is disabled, but pins must be re-configured separately.
 *
 *  @note Cannot debug the device after disabling SWD. Only re-enabled by POR.
 */
__STATIC_INLINE void DL_SYSCTL_disableSWD(void)
{
    SYSCTL->SOCLOCK.SWDJCFG = (SYSCTL_SWDJCFG_KEY_VALUE | SYSCTL_SWDJCFG_DISABLE_TRUE);
}

/**
 *  @brief     Set the XTAL startup time
 *
 * Specify the XTAL startup time in 64us resolution. If the HFCLK startup
 * monitor is enabled (HFCLKFLTCHK), XTAL will be checked after this time
 * expires.
 *
 *  @param[in]  startupTime  The XTAL startup time to set in ~64us steps.
 *                           Value between [0x0 (~0s), 0xFF (~16.32ms)].
 */
__STATIC_INLINE void DL_SYSCTL_setXTALStartupTime(uint32_t startupTime)
{
    DL_Common_updateReg(&SYSCTL->SOCLOCK.HFCLKCLKCFG, startupTime, SYSCTL_HFCLKCLKCFG_XTALTIME_MASK);
}

/**
 *  @brief   Get the XTAL startup time
 *
 *  @return  Returns the XTAL startup time in ~64us steps
 *
 *  @retval  Value between [0x0 (~0s), 0xFF (~16.32ms)]
 */
__STATIC_INLINE uint32_t DL_SYSCTL_getXTALStartupTime(void)
{
    return (SYSCTL->SOCLOCK.HFCLKCLKCFG & SYSCTL_HFCLKCLKCFG_XTALTIME_MASK);
}

/**
 *  @brief  Enable the HFCLK startup monitor
 *
 * The XTAL takes time to start after being enabled. A startup monitor is
 * provided to indicate to the application software if the XTAL has successfully
 * started, at which point the HFCLK can be selected to source a variety of
 * system functions. The HFCLK startup monitor also supports checking the
 * HFCLK_IN digital clock input for a clock stuck fault.
 *
 */
__STATIC_INLINE void DL_SYSCTL_enableHFCLKStartupMonitor(void)
{
    SYSCTL->SOCLOCK.HFCLKCLKCFG |= SYSCTL_HFCLKCLKCFG_HFCLKFLTCHK_ENABLE;
}

/**
 *  @brief  Disable the HFCLK startup monitor
 */
__STATIC_INLINE void DL_SYSCTL_disableHFCLKStartupMonitor(void)
{
    SYSCTL->SOCLOCK.HFCLKCLKCFG &= ~(SYSCTL_HFCLKCLKCFG_HFCLKFLTCHK_MASK);
}

/**
 *  @brief  Configure the COMP-H Postive Input Mux
 *
 *  @param[in]  muxSel  CMPSS Instance. @ref DL_SYSCTL_CMPSS_MUX
 *  @param[in]  value   Mux value. @ref DL_SYSCTL_CMP_HP
 *
 */
__STATIC_INLINE void DL_SYSCTL_setCompartorHPMux(DL_SYSCTL_CMPSS_MUX muxSel, DL_SYSCTL_CMP_HP value)
{
    uint32_t bit = (uint32_t)muxSel * 3U;
    SYSCTL->SOCLOCK.CMPHPMXSEL =
        (SYSCTL->SOCLOCK.CMPHPMXSEL & ~(SYSCTL_CMPHPMXSEL_CMP0HPMXSEL_MASK << bit)) | ((uint32_t)value << bit);
}

/**
 *  @brief  Configure the COMP-H Negative Input Mux
 *
 *  @param[in]  muxSel  CMPSS Instance. @ref DL_SYSCTL_CMPSS_MUX
 *  @param[in]  value   Mux value. @ref DL_SYSCTL_CMP_HN
 *
 */
__STATIC_INLINE void DL_SYSCTL_setCompartorHNMux(DL_SYSCTL_CMPSS_MUX muxSel, DL_SYSCTL_CMP_HN value)
{
    uint32_t bit = (uint32_t)muxSel;
    SYSCTL->SOCLOCK.CMPHNMXSEL =
        (SYSCTL->SOCLOCK.CMPHNMXSEL & ~(SYSCTL_CMPHNMXSEL_CMP0HNMXSEL_MASK << bit)) | ((uint32_t)value << bit);
}

/**
 *  @brief  Configure the COMP-L Postive Input Mux
 *
 *  @param[in]  muxSel  CMPSS Instance. @ref DL_SYSCTL_CMPSS_MUX
 *  @param[in]  value   Mux value. @ref DL_SYSCTL_CMP_LP
 *
 */
__STATIC_INLINE void DL_SYSCTL_setCompartorLPMux(DL_SYSCTL_CMPSS_MUX muxSel, DL_SYSCTL_CMP_LP value)
{
    uint32_t bit = (uint32_t)muxSel * 3U;
    SYSCTL->SOCLOCK.CMPLPMXSEL =
        (SYSCTL->SOCLOCK.CMPLPMXSEL & ~(SYSCTL_CMPLPMXSEL_CMP0LPMXSEL_MASK << bit)) | ((uint32_t)value << bit);
}

/**
 *  @brief  Configure the COMP-L Negative Input Mux
 *
 *  @param[in]  muxSel  CMPSS Instance. @ref DL_SYSCTL_CMPSS_MUX
 *  @param[in]  value   Mux value. @ref DL_SYSCTL_CMP_LP
 *
 */
__STATIC_INLINE void DL_SYSCTL_setCompartorLNMux(DL_SYSCTL_CMPSS_MUX muxSel, DL_SYSCTL_CMP_LN value)
{
    uint32_t bit = (uint32_t)muxSel;
    SYSCTL->SOCLOCK.CMPLNMXSEL =
        (SYSCTL->SOCLOCK.CMPLNMXSEL & ~(SYSCTL_CMPLNMXSEL_CMP0LNMXSEL_MASK << bit)) | ((uint32_t)value << bit);
}

/**
 *  @brief      Enable general purpose DAC functionality for CMPSS DAC
 *  @param[in]  dacSel  Bitwise OR of @ref DL_SYSCTL_DACOUTEN
 */
__STATIC_INLINE void DL_SYSCTL_enableDACOUT(uint32_t dacSel)
{
    SYSCTL->SOCLOCK.CMPSSCTL |= SYSCTL_CMPSSCTL_CMPSSCTLEN_MASK | dacSel;
}

/**
 *  @brief      Disable general purpose DAC functionality for CMPSS DAC
 */
__STATIC_INLINE void DL_SYSCTL_disableDACOUT(void)
{
    SYSCTL->SOCLOCK.CMPSSCTL = 0;
}

/**
 *  @brief  Configure the SRAM3 Bus Mux
 *
 *  @param[in]  bus  SRAM3 Bus Mux. @ref DL_SYSCTL_SRAM_BUS
 */
__STATIC_INLINE void DL_SYSCTL_setSRAM3BusMux(DL_SYSCTL_SRAM_BUS bus)
{
    SYSCTL->SOCLOCK.AM13SPARESOCLOCK2 =
        (SYSCTL->SOCLOCK.AM13SPARESOCLOCK2 & ~SYSCTL_AM13SPARESOCLOCK2_SRAM3_STATIC_MUX_SEL_MASK) | (uint32_t)bus;
}

/**
 *  @brief  Set the analog voltage reference selection to external / internal
 *
 *  @param[in] mode VREF mode. @ref DL_SYSCTL_VREF_MODE
 *
 */
__STATIC_INLINE void DL_SYSCTL_setVREF(DL_SYSCTL_VREF_MODE mode)
{
    SYSCTL->SOCLOCK.ANAREFCTL = (uint32_t)mode;
}

/**
 *  @brief  Enable Temperator Sensor
 *
 */
__STATIC_INLINE void DL_SYSCTL_enableTempSensor()
{
    SYSCTL->SOCLOCK.TSNSSCTL |= SYSCTL_TSNSSCTL_ENABLE_MASK;
}

/**
 *  @brief  Disable Temperator Sensor
 *
 */
__STATIC_INLINE void DL_SYSCTL_disableTempSensor()
{
    SYSCTL->SOCLOCK.TSNSSCTL &= ~SYSCTL_TSNSSCTL_ENABLE_MASK;
}

/**
 *  @brief  Selects the internal node, if any, to come out on the INTERNALTEST node
 *          connected to ADC.
 */
__STATIC_INLINE void DL_SYSCTL_selectInternalTestNode(DL_SYSCTL_InternalTestNode select)
{
    SYSCTL->SOCLOCK.INTERNALTESTCTL = select;
}

#ifdef __cplusplus
}
#endif

#endif /* DL_SYSCTL_H */
/** @}*/
