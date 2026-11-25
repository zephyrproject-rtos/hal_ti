/******************************************************************************
*  Filename:       hw_memmap.h
******************************************************************************
*  Copyright (c) 2021-2025 Texas Instruments Incorporated. All rights reserved.
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
*  3) Neither the name of the copyright holder nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
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
******************************************************************************/

#ifndef __HW_MEMMAP_H__
#define __HW_MEMMAP_H__

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals on the CPU_MMAP interface
//
//*****************************************************************************
#define FLASH_MAIN_BASE         0x00000000U // FLASH_MAIN
   #define FLASH_MAIN_SIZE                 0x80000U
#define ROM_BASE                0x0F000000U // ROM
   #define ROM_SIZE                        0x3000U
#define SRAM_BASE               0x20000000U // SRAM
   #define SRAM_SIZE                       0x9000U
#define PMCTL_BASE              0x40000000U // PMCTL
#define CKMD_BASE               0x40001000U // CKMD
#define RTC_BASE                0x40002000U // RTC
#define IOC_BASE                0x40003000U // IOC
#define SYS0_BASE               0x40004000U // SYS0
#define EVTULL_BASE             0x40005000U // EVTULL
#define PMUD_BASE               0x40006000U // PMUD
#define DBGSS_BASE              0x4000F000U // DBGSS
#define CLKCTL_BASE             0x40020000U // CLKCTL
#define FLASH_BASE              0x40021000U // FLASH
#define SYSTIM_BASE             0x40022000U // SYSTIM
#define GPIO_BASE               0x40023000U // GPIO
#define VIMS_BASE               0x40024000U // VIMS
#define EVTSVT_BASE             0x40025000U // EVTSVT
#define DMA_BASE                0x40026000U // DMA
#define SPI0_BASE               0x40030000U // SPI
#define UART0_BASE              0x40034000U // UART
#define I2C0_BASE               0x40038000U // I2C
#define ADC_BASE                0x40050000U // ADC
#define LGPT0_BASE              0x40060000U // LGPT0
#define LGPT1_BASE              0x40061000U // LGPT1
#define LGPT2_BASE              0x40062000U // LGPT2
#define LGPT3_BASE              0x40063000U // LGPT3
#define LRFDDBELL_BASE          0x40080000U // LRFDDBELL
#define LRFDPBE_BASE            0x40081000U // LRFDPBE
#define LRFDPBE32_BASE          0x40081400U // LRFDPBE32
#define LRFDTXF_BASE            0x40081800U // LRFDTXF
#define LRFDRXF_BASE            0x40081C00U // LRFDRXF
#define LRFDMDM_BASE            0x40082000U // LRFDMDM
#define LRFDMDM32_BASE          0x40082400U // LRFDMDM32
#define LRFDRFE_BASE            0x40083000U // LRFDRFE
#define LRFDRFE32_BASE          0x40083400U // LRFDRFE32
#define LRFDTRC_BASE            0x40084000U // LRFDTRC
#define LRFDS2R_BASE            0x40085000U // LRFDS2R
#define LRFD_PBERAM_BASE        0x40090000U // LRFD_PBERAM
   #define LRFD_PBERAM_SIZE                0x1000U
#define LRFD_BUFRAM_BASE        0x40092000U // LRFD_BUFRAM
   #define LRFD_BUFRAM_SIZE                0x600U
#define LRFD_MCERAM_BASE        0x40094000U // LRFD_MCERAM
   #define LRFD_MCERAM_SIZE                0x1000U
#define LRFD_RFERAM_BASE        0x40096000U // LRFD_RFERAM
   #define LRFD_RFERAM_SIZE                0x1000U
#define LRFD_S2RRAM_BASE        0x40098000U // LRFD_S2RRAM
   #define LRFD_S2RRAM_SIZE                0x1000U
#define AES_BASE                0x400C0000U // AES
#define FCFG_BASE               0x4E000000U // FCFG
   #define FCFG_SIZE                       0x400U
#define CCFG_BASE               0x4E020000U // CCFG
   #define CCFG_SIZE                       0x800U
#define BPU_BASE                0xE0002000U // BPU
#define SYSTICK_BASE            0xE000E010U // SYSTICK
#define DCB_BASE                0xE000ED30U // DCB
#define SCSCS_BASE              0xE000EFC0U // SCSCS
#define CPU_ROM_TABLE_BASE      0xE00FF000U // CPU_ROM_TABLE

#endif // __HW_MEMMAP__
