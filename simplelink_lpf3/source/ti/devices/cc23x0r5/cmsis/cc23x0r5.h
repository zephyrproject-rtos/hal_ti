/******************************************************************************
*  Filename:       cc23x0r5.h
*
*  Description:    Collection of architecture definitions for CC23x0R5 devices
*
// ##### LICENSE HEADER #####
*
******************************************************************************/
#ifndef __CC23X0R5_H__
#define __CC23X0R5_H__

/* IRQ numbers */
typedef enum IRQn
{
    NonMaskableInt_IRQn   = -14, /* 2  Non Maskable Interrupt */
    HardFault_IRQn        = -13, /* 3  Hard Fault Interrupt */
    SVCall_IRQn           = -5,  /* 11 SV Call Interrupt */
    PendSV_IRQn           = -2,  /* 14 Pend SV Interrupt */
    SysTick_IRQn          = -1,  /* 15 System Tick Interrupt */
    CPUIRQ0_IRQn          = 0,   /* 16 CPUIRQ0 configurable source */
    CPUIRQ1_IRQn          = 1,   /* 17 CPUIRQ1 configurable source */
    CPUIRQ2_IRQn          = 2,   /* 18 CPUIRQ2 configurable source */
    CPUIRQ3_IRQn          = 3,   /* 19 CPUIRQ3 configurable source */
    CPUIRQ4_IRQn          = 4,   /* 20 CPUIRQ4 configurable source */
    GPIO_COMB_IRQn        = 5,   /* 21 GPIO event interrupt */
    LRFD_IRQ0_IRQn        = 6,   /* 22 LRF interrupt 0 */
    LRFD_IRQ1_IRQn        = 7,   /* 23 LRF interrupt 1 */
    DMA_DONE_COMB_IRQn    = 8,   /* 24 uDMA done events */
    AES_COMB_IRQn         = 9,   /* 25 AES interrupt */
    SPI0_COMB_IRQn        = 10,  /* 26 SPI0 combined interrupt */
    UART0_COMB_IRQn       = 11,  /* 27 UART0 combined interrupt */
    I2C0_IRQ_IRQn         = 12,  /* 28 I2C0 combined interrupt */
    LGPT0_COMB_IRQn       = 13,  /* 29 LGPT0 interrupt */
    LGPT1_COMB_IRQn       = 14,  /* 30 LGPT1 interrupt */
    ADC_COMB_IRQn         = 15,  /* 31 ADC0 interrupt */
    CPUIRQ16_IRQn         = 16,  /* 32 CPUIRQ16 configurable source */
    LGPT2_COMB_IRQn       = 17,  /* 33 LGPT0 interrupt */
    LGPT3_COMB_IRQn       = 18,  /* 34 LGPT1 interrupt */
} IRQn_Type;

/* Architecture-specific constants */
#define __SAUREGION_PRESENT    0x0000U /* SAU present */
#define __DSP_PRESENT          0x0000U /* DSP extension present */
#define __Vendor_SysTickConfig 0x0000U /* Set to 1 if different SysTick Config is used */
#define __MPU_PRESENT          0x0000U /* MPU present or not */
#define __FPU_PRESENT          0x0000U /* FPU present or not */
#define __VTOR_PRESENT         0x0001U /* VTOR present */
#define __NVIC_PRIO_BITS       0x0002U /* 2 NVIC priority bits */

#include <core_cm0plus.h>

#endif // #ifndef __CC23X0R5_H__
