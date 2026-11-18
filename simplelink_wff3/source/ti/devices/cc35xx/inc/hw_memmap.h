/******************************************************************************
 *  Filename:       hw_memmap_h
 *
 *  Description:    Device memory map macros.
 *
 *  Copyright (c) 2022-2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef __HW_MEMMAP_H__
#define __HW_MEMMAP_H__

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals on the CPU_MMAP interface
//
//*****************************************************************************
#define HOSTMCU_TGT_BASE      0x00000000
#define TCM_CRAM_BASE         0x00000000
#define TCM_CRAM_SEC_BASE     0x04000000
#define CRAM_BASE             0x08000000
#define CRAM_SEC_BASE         0x0C000000
#define EXT_FLASH_BASE        0x10000000
#define EXT_FLASH_SEC_BASE    0x14000000
#define TCM_DRAM_BASE         0x20000000
#define TCM_DRAM_SEC_BASE     0x24000000
#define DRAM_BASE             0x28000000
#define DRAM_SEC_BASE         0x2C000000
#define EXT_PSRAM_BASE        0x60000000
#define EXT_PSRAM_SEC_BASE    0x64000000
#define HOST_MCU_BASE         0x41900000
#define ICACHE_BASE           0x41902000
#define DCACHE_BASE           0x41902400
#define HOST_MCU_SEC_BASE     0x41903000
#define OSPI_REGS_BASE        0x41910000
#define OSPI_INDAC_BASE       0x41911000
#define HOST_XIP_REGS_BASE    0x41912000
#define HIF_BASE              0x408A0000
#define COEX_BASE             0x40850000
#define IOMUX_BASE            0x41140000
#define PRCM_BASE             0x41090000
#define PRCM_AON_BASE         0x41090000
#define PRCM_SCRATCHPAD_BASE  0x4109F000
#define PLL_SHARING_BASE      0x410A0000
#define CKM_BASE              0x410a0000
#define SOC_DEBUGSS_BASE      0x410d0000
#define SOC_DEBUGSS_DSSM_BASE 0x410d0000
#define SOC_IC_REGS_BASE      0x410f0000
#define SOC_AON_BASE          0x41100000
#define SOC_AAON_BASE         0x41104000
#define RTC_BASE              0x41108000
#define WSOC_OCLA_BASE        0x411C0000
#define MEMSS_BASE            0x41C00000
#define HOSTMCU_AON_BASE      0x411D0000
#define SYSRESOURCES_BASE     0x411E0000
#define SYSTIM_BASE           0x411E2000
#define HOST_DMA_TGT_BASE     0x41A00000
#define HSM_BASE              0x41B00000
#define HSM_NON_SEC_BASE      0x41B04000
#define HSM_SEC_BASE          0x41B05000
#define I2C0_BASE             0x41200000
#define I2C1_BASE             0x41210000
#define SPI0_BASE             0x41220000
#define SPI1_BASE             0x41230000
#define UARTLIN0_BASE         0x41240000
#define UARTLIN1_BASE         0x41250000
#define UARTLIN2_BASE         0x41300000
#define GPTIMER0_BASE         0x41260000
#define GPTIMER1_BASE         0x41268000
#define I2S_BASE              0x41270000
#define PDM_BASE              0x41280000
#define DCAN_BASE             0x412A0000
#define ADC_BASE              0x412B0000
#define SDMMC_BASE            0x412C0000
#define SDIO_CARD_FN1_BASE    0x412D0000
#define SDIO_CORE_BASE        0x412E0000
#define CORE_AON_BASE         0x41E00000

// TODO: Review presence of commented IPs
#define CPU_ITM_BASE         0xE0000000 // CPU_ITM
#define CPU_DWT_BASE         0xE0001000 // CPU_DWT
#define CPU_ICB_BASE         0xE000E000 // CPU_ICB
#define CPU_SYSTICK_BASE     0xE000E010 // CPU_SYSTICK
#define CPU_NVIC_BASE        0xE000E100 // CPU_NVIC
#define CPU_MPU_BASE         0xE000EDC0 // CPU_MPU
#define CPU_SAU_BASE         0xE000EDD0 // CPU_SAU
#define CPU_FPU_BASE         0xE000EF30 // CPU_FPU

#endif // __HW_MEMMAP__
