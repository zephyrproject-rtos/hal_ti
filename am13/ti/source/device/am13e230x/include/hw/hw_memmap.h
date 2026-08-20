/*****************************************************************************

  Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

   Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the
   distribution.

   Neither the name of Texas Instruments Incorporated nor the names of
   its contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*****************************************************************************/

#ifndef hw_memmap__include
#define hw_memmap__include

/* Use standard integer types with explicit width */
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
 extern "C" {
#endif


/******************************************************************************
* Device and peripheral memory map                                            *
******************************************************************************/
/** @addtogroup AM13E23_MemoryMap AM13E23 Memory Mapping
  @{
*/

#define ADC0_BASE            (0x40000000U)     /*!< Base address of module ADC0 */
#define ADC1_BASE            (0x40002000U)     /*!< Base address of module ADC1 */
#define ADC2_BASE            (0x40004000U)     /*!< Base address of module ADC2 */
#define ADC0RESULT_BASE      (0x4000A000U)     /*!< Base address of module ADC0RESULT */
#define ADC1RESULT_BASE      (0x4000B000U)     /*!< Base address of module ADC1RESULT */
#define ADC2RESULT_BASE      (0x4000C000U)     /*!< Base address of module ADC2RESULT */
#define MCPWM0_BASE          (0x40010000U)     /*!< Base address of module MCPWM0 */
#define MCPWM1_BASE          (0x40011000U)     /*!< Base address of module MCPWM1 */
#define MCPWM2_BASE          (0x40012000U)     /*!< Base address of module MCPWM2 */
#define MCPWM3_BASE          (0x40013000U)     /*!< Base address of module MCPWM3 */
#define MCPWM4_BASE          (0x40014000U)     /*!< Base address of module MCPWM4 */
#define DMA0_BASE            (0x40020000U)     /*!< Base address of module DMA0 */
#define FRI_BASE             (0x40028000U)     /*!< Base address of module FRI */
#define MEMCFG_BASE          (0x4002A000U)     /*!< Base address of module MEMCFG */
#define EAM_BASE             (0x4002C000U)     /*!< Base address of module EAM */
#define NVMNW_BASE           (0x40042000U)     /*!< Base address of module NVMNW */
#define GSC_BASE             (0x40046000U)     /*!< Base address of module GSC */
#define SYSCTL_BASE          (0x400AF000U)     /*!< Base address of module SYSCTL */
#define DEBUGSS_BASE         (0x400C7000U)     /*!< Base address of module DEBUGSS */
#define IOMUX_BASE           (0x400CC000U)     /*!< Base address of module IOMUX */
#define WWDT0_BASE           (0x400D0000U)     /*!< Base address of module WWDT0 */
#define GPIO0_BASE           (0x400F0000U)     /*!< Base address of module GPIO0 */
#define GPIO1_BASE           (0x400F2000U)     /*!< Base address of module GPIO1 */
#define GPIO2_BASE           (0x400F4000U)     /*!< Base address of module GPIO2 */
#define GPIO3_BASE           (0x400F6000U)     /*!< Base address of module GPIO3 */
#define PGA0_BASE            (0x400FC000U)     /*!< Base address of module PGA0 */
#define PGA1_BASE            (0x400FD000U)     /*!< Base address of module PGA1 */
#define PGA2_BASE            (0x400FE000U)     /*!< Base address of module PGA2 */
#define MCAN0_BASE           (0x40110000U)     /*!< Base address of module MCAN0 */
#define TIMG4_BASE           (0x40180000U)     /*!< Base address of module TIMG4 */
#define TIMG12_BASE          (0x40188000U)     /*!< Base address of module TIMG12 */
#define AES_BASE             (0x401B0000U)     /*!< Base address of module AES */
#define CRC_BASE             (0x401B2000U)     /*!< Base address of module CRC */
#define KEYSTORE_BASE        (0x401B6000U)     /*!< Base address of module KEYSTORE */
#define ECAP0_BASE           (0x40440000U)     /*!< Base address of module ECAP0 */
#define ECAP1_BASE           (0x40441000U)     /*!< Base address of module ECAP1 */
#define EQEP0_BASE           (0x40448000U)     /*!< Base address of module EQEP0 */
#define EQEP1_BASE           (0x40449000U)     /*!< Base address of module EQEP1 */
#define EQEP2_BASE           (0x4044A000U)     /*!< Base address of module EQEP2 */
#define CMPSS0_BASE          (0x40460000U)     /*!< Base address of module CMPSS0 */
#define CMPSS1_BASE          (0x40461000U)     /*!< Base address of module CMPSS1 */
#define CMPSS2_BASE          (0x40462000U)     /*!< Base address of module CMPSS2 */
#define CMPSS3_BASE          (0x40463000U)     /*!< Base address of module CMPSS3 */
#define INPUTXBAR_BASE       (0x40468000U)     /*!< Base address of module INPUTXBAR */
#define PWMXBAR_BASE         (0x40469000U)     /*!< Base address of module PWMXBAR */
#define OUTPUTXBAR_BASE      (0x4046A000U)     /*!< Base address of module OUTPUTXBAR */
#define SYNC_BASE            (0x4046B000U)     /*!< Base address of module SYNC */
#define OUTPUTXBAR0_FLAGS_BASE (0x40470000U)     /*!< Base address of module OUTPUTXBAR0_FLAGS */
#define OUTPUTXBAR1_FLAGS_BASE (0x40471000U)     /*!< Base address of module OUTPUTXBAR1_FLAGS */
#define OUTPUTXBAR2_FLAGS_BASE (0x40472000U)     /*!< Base address of module OUTPUTXBAR2_FLAGS */
#define OUTPUTXBAR3_FLAGS_BASE (0x40473000U)     /*!< Base address of module OUTPUTXBAR3_FLAGS */
#define OUTPUTXBAR4_FLAGS_BASE (0x40474000U)     /*!< Base address of module OUTPUTXBAR4_FLAGS */
#define OUTPUTXBAR5_FLAGS_BASE (0x40475000U)     /*!< Base address of module OUTPUTXBAR5_FLAGS */
#define OUTPUTXBAR6_FLAGS_BASE (0x40476000U)     /*!< Base address of module OUTPUTXBAR6_FLAGS */
#define OUTPUTXBAR7_FLAGS_BASE (0x40477000U)     /*!< Base address of module OUTPUTXBAR7_FLAGS */
#define INPUTXBAR_FLAGS_BASE (0x40490000U)     /*!< Base address of module INPUTXBAR_FLAGS */
#define UC0_UART_BASE        (0x40600000U)     /*!< Base address of module UC0_UART */
#define UC1_UART_BASE        (0x40601000U)     /*!< Base address of module UC1_UART */
#define UC2_UART_BASE        (0x40602000U)     /*!< Base address of module UC2_UART */
#define UC0_I2CC_BASE        (0x40608000U)     /*!< Base address of module UC0_I2CC */
#define UC1_I2CC_BASE        (0x40609000U)     /*!< Base address of module UC1_I2CC */
#define UC2_I2CC_BASE        (0x4060A000U)     /*!< Base address of module UC2_I2CC */
#define UC0_I2CT_BASE        (0x40610000U)     /*!< Base address of module UC0_I2CT */
#define UC1_I2CT_BASE        (0x40611000U)     /*!< Base address of module UC1_I2CT */
#define UC2_I2CT_BASE        (0x40612000U)     /*!< Base address of module UC2_I2CT */
#define UC0_SPI_BASE         (0x40618000U)     /*!< Base address of module UC0_SPI */
#define UC1_SPI_BASE         (0x40619000U)     /*!< Base address of module UC1_SPI */
#define UNICOMM0_BASE        (0x40630000U)     /*!< Base address of module UNICOMM0 */
#define UNICOMM1_BASE        (0x40632000U)     /*!< Base address of module UNICOMM1 */
#define UNICOMM2_BASE        (0x40634000U)     /*!< Base address of module UNICOMM2 */
#define SPG0_BASE            (0x4063F000U)     /*!< Base address of module SPG0 */
#define UC3_UART_BASE        (0x40640000U)     /*!< Base address of module UC3_UART */
#define UC4_UART_BASE        (0x40641000U)     /*!< Base address of module UC4_UART */
#define UC5_UART_BASE        (0x40642000U)     /*!< Base address of module UC5_UART */
#define UC3_I2CC_BASE        (0x40648000U)     /*!< Base address of module UC3_I2CC */
#define UC4_I2CC_BASE        (0x40649000U)     /*!< Base address of module UC4_I2CC */
#define UC5_I2CC_BASE        (0x4064A000U)     /*!< Base address of module UC5_I2CC */
#define UC3_I2CT_BASE        (0x40650000U)     /*!< Base address of module UC3_I2CT */
#define UC4_I2CT_BASE        (0x40651000U)     /*!< Base address of module UC4_I2CT */
#define UC5_I2CT_BASE        (0x40652000U)     /*!< Base address of module UC5_I2CT */
#define UC3_SPI_BASE         (0x40658000U)     /*!< Base address of module UC3_SPI */
#define UC4_SPI_BASE         (0x40659000U)     /*!< Base address of module UC4_SPI */
#define UNICOMM3_BASE        (0x40670000U)     /*!< Base address of module UNICOMM3 */
#define UNICOMM4_BASE        (0x40672000U)     /*!< Base address of module UNICOMM4 */
#define UNICOMM5_BASE        (0x40674000U)     /*!< Base address of module UNICOMM5 */
#define SPG1_BASE            (0x4067F000U)     /*!< Base address of module SPG1 */
#define TINIE_BASE           (0x408FF000U)     /*!< Base address of module TINIE */

#define FACTORYREGION_BASE   (0x60111000U)     /*!< Base address of OTP region */


/*@}*/ /* end of group AM13E23_MemoryMap */

/******************************************************************************
* Peripheral declarations                                                     *
******************************************************************************/
/** @addtogroup AM13E23_PeripheralDecl AM13E23 Peripheral Declaration
  @{
*/

static ADC_Regs             * const ADC0            = ((ADC_Regs *) ADC0_BASE);
static ADC_Regs             * const ADC1            = ((ADC_Regs *) ADC1_BASE);
static ADC_Regs             * const ADC2            = ((ADC_Regs *) ADC2_BASE);
static ADC_RESULT_Regs      * const ADC0RESULT      = ((ADC_RESULT_Regs *) ADC0RESULT_BASE);
static ADC_RESULT_Regs      * const ADC1RESULT      = ((ADC_RESULT_Regs *) ADC1RESULT_BASE);
static ADC_RESULT_Regs      * const ADC2RESULT      = ((ADC_RESULT_Regs *) ADC2RESULT_BASE);
static MCPWM_Regs           * const MCPWM0          = ((MCPWM_Regs *) MCPWM0_BASE);
static MCPWM_Regs           * const MCPWM1          = ((MCPWM_Regs *) MCPWM1_BASE);
static MCPWM_Regs           * const MCPWM2          = ((MCPWM_Regs *) MCPWM2_BASE);
static MCPWM_Regs           * const MCPWM3          = ((MCPWM_Regs *) MCPWM3_BASE);
static MCPWM_Regs           * const MCPWM4          = ((MCPWM_Regs *) MCPWM4_BASE);
static DMA_Regs             * const DMA0            = ((DMA_Regs *) DMA0_BASE);
static FRI_Regs             * const FRI             = ((FRI_Regs *) FRI_BASE);
static MEMCFG_Regs          * const MEMCFG          = ((MEMCFG_Regs *) MEMCFG_BASE);
static EAM_Regs             * const EAM             = ((EAM_Regs *) EAM_BASE);
static NVMNW_Regs           * const NVMNW           = ((NVMNW_Regs *) NVMNW_BASE);
static GSC_Regs             * const GSC             = ((GSC_Regs *) GSC_BASE);
static SYSCTL_Regs          * const SYSCTL          = ((SYSCTL_Regs *) SYSCTL_BASE);
static DEBUGSS_Regs         * const DEBUGSS         = ((DEBUGSS_Regs *) DEBUGSS_BASE);
static IOMUX_Regs           * const IOMUX           = ((IOMUX_Regs *) IOMUX_BASE);
static WWDT_Regs            * const WWDT0           = ((WWDT_Regs *) WWDT0_BASE);
static GPIO_Regs            * const GPIO0           = ((GPIO_Regs *) GPIO0_BASE);
static GPIO_Regs            * const GPIO1           = ((GPIO_Regs *) GPIO1_BASE);
static GPIO_Regs            * const GPIO2           = ((GPIO_Regs *) GPIO2_BASE);
static GPIO_Regs            * const GPIO3           = ((GPIO_Regs *) GPIO3_BASE);
static PGA_Regs             * const PGA0            = ((PGA_Regs *) PGA0_BASE);
static PGA_Regs             * const PGA1            = ((PGA_Regs *) PGA1_BASE);
static PGA_Regs             * const PGA2            = ((PGA_Regs *) PGA2_BASE);
static MCAN_Regs            * const MCAN0           = ((MCAN_Regs *) MCAN0_BASE);
static GPTIMER_Regs         * const TIMG4           = ((GPTIMER_Regs *) TIMG4_BASE);
static GPTIMER_Regs         * const TIMG12          = ((GPTIMER_Regs *) TIMG12_BASE);
static AES_Regs             * const AES             = ((AES_Regs *) AES_BASE);
static CRCP_Regs            * const CRC             = ((CRCP_Regs *) CRC_BASE);
static KEYSTORECTL_Regs     * const KEYSTORE        = ((KEYSTORECTL_Regs *) KEYSTORE_BASE);
static ECAP_Regs            * const ECAP0           = ((ECAP_Regs *) ECAP0_BASE);
static ECAP_Regs            * const ECAP1           = ((ECAP_Regs *) ECAP1_BASE);
static EQEP_Regs            * const EQEP0           = ((EQEP_Regs *) EQEP0_BASE);
static EQEP_Regs            * const EQEP1           = ((EQEP_Regs *) EQEP1_BASE);
static EQEP_Regs            * const EQEP2           = ((EQEP_Regs *) EQEP2_BASE);
static CMPSS_LITE_Regs      * const CMPSS0          = ((CMPSS_LITE_Regs *) CMPSS0_BASE);
static CMPSS_LITE_Regs      * const CMPSS1          = ((CMPSS_LITE_Regs *) CMPSS1_BASE);
static CMPSS_LITE_Regs      * const CMPSS2          = ((CMPSS_LITE_Regs *) CMPSS2_BASE);
static CMPSS_LITE_Regs      * const CMPSS3          = ((CMPSS_LITE_Regs *) CMPSS3_BASE);
static XBAR_INPUT_XBAR_Regs * const INPUTXBAR       = ((XBAR_INPUT_XBAR_Regs *) INPUTXBAR_BASE);
static XBAR_EPWM_XBAR_Regs  * const PWMXBAR         = ((XBAR_EPWM_XBAR_Regs *) PWMXBAR_BASE);
static XBAR_OUTPUTXBAR_Regs * const OUTPUTXBAR      = ((XBAR_OUTPUTXBAR_Regs *) OUTPUTXBAR_BASE);
static XBAR_SYNC_SOC_Regs   * const SYNC            = ((XBAR_SYNC_SOC_Regs *) SYNC_BASE);
static XBAR_OUTPUTXBAR_FLAG_Regs * const OUTPUTXBAR0_FLAGS = ((XBAR_OUTPUTXBAR_FLAG_Regs *) OUTPUTXBAR0_FLAGS_BASE);
static XBAR_OUTPUTXBAR_FLAG_Regs * const OUTPUTXBAR1_FLAGS = ((XBAR_OUTPUTXBAR_FLAG_Regs *) OUTPUTXBAR1_FLAGS_BASE);
static XBAR_OUTPUTXBAR_FLAG_Regs * const OUTPUTXBAR2_FLAGS = ((XBAR_OUTPUTXBAR_FLAG_Regs *) OUTPUTXBAR2_FLAGS_BASE);
static XBAR_OUTPUTXBAR_FLAG_Regs * const OUTPUTXBAR3_FLAGS = ((XBAR_OUTPUTXBAR_FLAG_Regs *) OUTPUTXBAR3_FLAGS_BASE);
static XBAR_OUTPUTXBAR_FLAG_Regs * const OUTPUTXBAR4_FLAGS = ((XBAR_OUTPUTXBAR_FLAG_Regs *) OUTPUTXBAR4_FLAGS_BASE);
static XBAR_OUTPUTXBAR_FLAG_Regs * const OUTPUTXBAR5_FLAGS = ((XBAR_OUTPUTXBAR_FLAG_Regs *) OUTPUTXBAR5_FLAGS_BASE);
static XBAR_OUTPUTXBAR_FLAG_Regs * const OUTPUTXBAR6_FLAGS = ((XBAR_OUTPUTXBAR_FLAG_Regs *) OUTPUTXBAR6_FLAGS_BASE);
static XBAR_OUTPUTXBAR_FLAG_Regs * const OUTPUTXBAR7_FLAGS = ((XBAR_OUTPUTXBAR_FLAG_Regs *) OUTPUTXBAR7_FLAGS_BASE);
static XBAR_INPUT_FLAG_Regs * const INPUTXBAR_FLAGS = ((XBAR_INPUT_FLAG_Regs *) INPUTXBAR_FLAGS_BASE);
static UNICOMMUART_Regs     * const UC0_UART        = ((UNICOMMUART_Regs *) UC0_UART_BASE);
static UNICOMMUART_Regs     * const UC1_UART        = ((UNICOMMUART_Regs *) UC1_UART_BASE);
static UNICOMMUART_Regs     * const UC2_UART        = ((UNICOMMUART_Regs *) UC2_UART_BASE);
static UNICOMMI2CC_Regs     * const UC0_I2CC        = ((UNICOMMI2CC_Regs *) UC0_I2CC_BASE);
static UNICOMMI2CC_Regs     * const UC1_I2CC        = ((UNICOMMI2CC_Regs *) UC1_I2CC_BASE);
static UNICOMMI2CC_Regs     * const UC2_I2CC        = ((UNICOMMI2CC_Regs *) UC2_I2CC_BASE);
static UNICOMMI2CT_Regs     * const UC0_I2CT        = ((UNICOMMI2CT_Regs *) UC0_I2CT_BASE);
static UNICOMMI2CT_Regs     * const UC1_I2CT        = ((UNICOMMI2CT_Regs *) UC1_I2CT_BASE);
static UNICOMMI2CT_Regs     * const UC2_I2CT        = ((UNICOMMI2CT_Regs *) UC2_I2CT_BASE);
static UNICOMMSPI_Regs      * const UC0_SPI         = ((UNICOMMSPI_Regs *) UC0_SPI_BASE);
static UNICOMMSPI_Regs      * const UC1_SPI         = ((UNICOMMSPI_Regs *) UC1_SPI_BASE);
static UNICOMM_Regs         * const UNICOMM0        = ((UNICOMM_Regs *) UNICOMM0_BASE);
static UNICOMM_Regs         * const UNICOMM1        = ((UNICOMM_Regs *) UNICOMM1_BASE);
static UNICOMM_Regs         * const UNICOMM2        = ((UNICOMM_Regs *) UNICOMM2_BASE);
static SPGSS_Regs           * const SPG0            = ((SPGSS_Regs *) SPG0_BASE);
static UNICOMMUART_Regs     * const UC3_UART        = ((UNICOMMUART_Regs *) UC3_UART_BASE);
static UNICOMMUART_Regs     * const UC4_UART        = ((UNICOMMUART_Regs *) UC4_UART_BASE);
static UNICOMMUART_Regs     * const UC5_UART        = ((UNICOMMUART_Regs *) UC5_UART_BASE);
static UNICOMMI2CC_Regs     * const UC3_I2CC        = ((UNICOMMI2CC_Regs *) UC3_I2CC_BASE);
static UNICOMMI2CC_Regs     * const UC4_I2CC        = ((UNICOMMI2CC_Regs *) UC4_I2CC_BASE);
static UNICOMMI2CC_Regs     * const UC5_I2CC        = ((UNICOMMI2CC_Regs *) UC5_I2CC_BASE);
static UNICOMMI2CT_Regs     * const UC3_I2CT        = ((UNICOMMI2CT_Regs *) UC3_I2CT_BASE);
static UNICOMMI2CT_Regs     * const UC4_I2CT        = ((UNICOMMI2CT_Regs *) UC4_I2CT_BASE);
static UNICOMMI2CT_Regs     * const UC5_I2CT        = ((UNICOMMI2CT_Regs *) UC5_I2CT_BASE);
static UNICOMMSPI_Regs      * const UC3_SPI         = ((UNICOMMSPI_Regs *) UC3_SPI_BASE);
static UNICOMMSPI_Regs      * const UC4_SPI         = ((UNICOMMSPI_Regs *) UC4_SPI_BASE);
static UNICOMM_Regs         * const UNICOMM3        = ((UNICOMM_Regs *) UNICOMM3_BASE);
static UNICOMM_Regs         * const UNICOMM4        = ((UNICOMM_Regs *) UNICOMM4_BASE);
static UNICOMM_Regs         * const UNICOMM5        = ((UNICOMM_Regs *) UNICOMM5_BASE);
static SPGSS_Regs           * const SPG1            = ((SPGSS_Regs *) SPG1_BASE);
static TINIELITE_Regs       * const TINIE           = ((TINIELITE_Regs *) TINIE_BASE);

static FACTORYREGION_Regs   * const FACTORYREGION   = ((FACTORYREGION_Regs *) FACTORYREGION_BASE);



#ifdef __cplusplus
}
#endif

#endif /* hw_memmap__include */
