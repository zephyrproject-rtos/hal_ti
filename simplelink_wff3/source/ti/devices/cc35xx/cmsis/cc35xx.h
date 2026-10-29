/******************************************************************************
*  Filename:       cc35xx.h
*
*  Description:    Collection of architecture definitions for CC35xx devices
*
*  Copyright (c) 2023-2025 Texas Instruments Incorporated
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
#ifndef __CC35XX_H__
#define __CC35XX_H__

/* IRQ numbers */
typedef enum IRQn
{
    NonMaskableInt_IRQn                           = -14, /* 2  Non Maskable Interrupt */
    HardFault_IRQn                                = -13, /* 3  Hard Fault Interrupt */
    MemoryManagement_IRQn                         = -12, /* 4  Memory Management Interrupt */
    BusFault_IRQn                                 = -11, /* 5  Bus Fault Interrupt */
    UsageFault_IRQn                               = -10, /* 6  Usage Fault Interrupt */
    SVCall_IRQn                                   = -5,  /* 11 SV Call Interrupt */
    DebugMonitor_IRQn                             = -4,  /* 12 Debug Monitor Interrupt */
    PendSV_IRQn                                   = -2,  /* 14 Pend SV Interrupt */
    SysTick_IRQn                                  = -1,  /* 15 System Tick Interrupt */
    INT_SP_UART_0_INT_REQ_IRQn                    = 0,
    INT_SP_UART_1_INT_REQ_IRQn                    = 1,
    INT_SP_I2C_0_INTREQ_IRQn                      = 2,
    INT_SP_I2C_1_INTREQ_IRQn                      = 3,
    INT_SP_SPI_0_EVT_REQ_IRQn                     = 4,
    INT_SP_SPI_1_EVT_REQ_IRQn                     = 5,
    INT_GPTIMER_0_EVT_CPU_IRQn                    = 6,
    INT_GPTIMER_1_EVT_CPU_IRQn                    = 7,
    INT_SP_UART_2_INT_REQ_IRQn                    = 8,
    INT_I2S_IRQ_REQ_IRQn                          = 9,
    INT_EVT_PDM_EVENT_REQ_IRQn                    = 10,
    INT_EVT_SWINT0_REQ_IRQn                       = 11,
    INT_EVT_SWINT1_REQ_IRQn                       = 12,
    INT_EVT_SDMMC_PUB_REQ_IRQn                    = 13,
    INT_SDIO_CARD_IRQ_REQ_IRQn                    = 14,
    INT_ULL_USC_ULPADCHP_PUB_EVT0_REQ_IRQn        = 15,
    INT_NON_SECURED_GPIO_IRQ_EVT_IND_OUT_IRQn     = 16,
    INT_SECURED_GPIO_IRQ_EVT_IND_OUT_IRQn         = 17,
    INT_OSPR_HSM_HOST_0_SEC_IRQn                  = 18,
    INT_OSPR_HSM_HOST_0_IRQn                      = 19,
    INT_OSPR_HSM_HOST_1_IRQn                      = 20,
    INT_SVT_EVT_COMBINED_SYSTIM_OUT_IRQn          = 21,
    INT_SVT_EVT_SYSTIMER_BIT_OUT_IRQn             = 22,
    INT_SVT_EVT_SYSTIMER_OUT_0_IRQn               = 23,
    INT_SVT_EVT_SYSTIMER_OUT_1_IRQn               = 24,
    INT_NON_SECURED_DMA_IRQ_EVT_IND_OUT_IRQn      = 25,
    INT_SECURED_DMA_IRQ_EVT_IND_OUT_IRQn          = 26,
    INT_NON_SECURED_DOORBELL_IRQ_EVT_IND_OUT_IRQn = 27,
    INT_SECURED_DOORBELL_IRQ_EVT_IND_OUT_IRQn     = 28,
    INT_ICACHE_ERR_IRQn                           = 29,
    INT_OSPI_IRQn                                 = 30,
    INT_OTFDE_IRQn                                = 31,
    INT_XIP_ARB_IRQn                              = 32,
    INT_XIP_DMA_SEC_IRQn                          = 33,
    INT_XIP_DMA_NONSEC_IRQn                       = 34,
    INT_SW_INTERRUPT_0_IRQn                       = 35,
    INT_SW_INTERRUPT_1_IRQn                       = 36,
    INT_SW_INTERRUPT_2_IRQn                       = 37,
    INT_SW_INTERRUPT_3_IRQn                       = 38,
    INT_SW_INTERRUPT_4_IRQn                       = 39,
    INT_SW_INTERRUPT_5_IRQn                       = 40,
    INT_SW_INTERRUPT_6_IRQn                       = 41,
    INT_SW_INTERRUPT_7_IRQn                       = 42,
    INT_PRCM_IRQn                                 = 43,
    INT_OCLA_IRQn                                 = 44,
    INT_HIF_FIFO_IRQn                             = 45,
    // Wakeup events
    INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn              = 46,
    INT_NAB_HOST_IRQn                             = 47,
    INT_BLE_RFC_GPO_8_IRQn                        = 48,
    INT_RTC_EVENT_IRQn                            = 49,
    INT_DEBUGSS_HOST_CSYSPWRUPREQ_IRQn            = 50,
    INT_DEBUGSS_HOST_FORCEACTIVE_IRQn             = 51,
    INT_SECURED_ERROR_IRQ_EVT_IND_OUT_IRQn        = 52,
} IRQn_Type;

/* Architecture-specific constants. TODO: Update for CC35XX */
#define __SAUREGION_PRESENT    0x0001U /* SAU present */
#define __DSP_PRESENT          0x0001U /* DSP extension present */
#define __Vendor_SysTickConfig 0x0000U /* Set to 1 if different SysTick Config is used */
#define __CM33_REV             0x0001U /* Core revision */
#define __MPU_PRESENT          0x0001U /* MPU present or not */
#define __FPU_PRESENT          0x0001U /* FPU present or not */
#define __VTOR_PRESENT         0x0001U /* VTOR present */
#define __NVIC_PRIO_BITS       0x0004U /* 4 NVIC priority bits */

#endif // __CC35XX_H__