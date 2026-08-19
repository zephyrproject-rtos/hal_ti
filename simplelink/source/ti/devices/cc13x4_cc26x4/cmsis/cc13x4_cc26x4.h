/******************************************************************************
*  Filename:       cc13x4_cc26x4.h
*
*  Description:    Collection of architecture definitions for CC13X4 & CC26X4 devices
*
// ##### LICENSE HEADER #####
*
******************************************************************************/

#ifndef __CC13X4_CC26X4_H__
#define __CC13X4_CC26X4_H__

/* Interrupt lines from SoC to NVIC. */
typedef enum {
	Reset_IRQn              = -15,      /* 1 Reset Interrupt */
	NonMaskableInt_IRQn     = -14,      /* 2 Non-maskable Interrupt */
	HardFault_IRQn          = -13,      /* 3 HardFault Interrupt */
	MemoryManagement_IRQn   = -12,      /* 4 Memory management fault */
	BusFault_IRQn           = -11,      /* 5 BusFault Interrupt */
	UsageFault_IRQn         = -10,      /* 6 UsageFault Interrupt */
	SecureFault_IRQn        = -9,       /* 7 SecureFault Interrupt */
	SVCall_IRQn             = -5,       /* 11 SVCall Interrupt */
	DebugMonitor_IRQn       = -4,       /* 12 Debug Monitor Interrupt */
	PendSV_IRQn             = -2,       /* 14 PendSV Interrupt */
	SysTick_IRQn            = -1,       /* 15 SysTick Interrupt */
} IRQn_Type;


/* Architecture specific constants. */
#define __CM33_REV             0x0004U
#define __MPU_PRESENT          1
#define __NVIC_PRIO_BITS       0x0004U
#define __Vendor_SysTickConfig 0
#define __FPU_PRESENT          1
#define __DSP_PRESENT          1
#define __SAUREGION_PRESENT    0

#include <core_cm33.h>

#endif /* __CC13X4_CC26X4_H__ */
