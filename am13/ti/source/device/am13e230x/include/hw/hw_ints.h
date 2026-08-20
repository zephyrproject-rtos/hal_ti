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

#ifndef hw_ints__include
#define hw_ints__include

/* Use standard integer types with explicit width */
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
 extern "C" {
#endif


/******************************************************************************
* Interrupt Definitions                                                       *
******************************************************************************/
typedef enum IRQn
{
  NonMaskableInt_IRQn         = -14,    /* 2  Non Maskable Interrupt */
  HardFault_IRQn              = -13,    /* 3  Hard Fault Interrupt */
  MemManage_IRQn              = -12,    /* 4  Memory Management Interrupt */
  BusFault_IRQn               = -11,    /* 5  Bus Fault Interrupt */
  UsageFault_IRQn             = -10,    /* 6  Usage Fault Interrupt */
  SecureFault_IRQn            = -9,     /* 7  Secure Fault Interrupt */
  SVCall_IRQn                 = -5,     /* 11 SV Call Interrupt */
  DebugMonitor_IRQn           = -4,     /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                 = -2,     /* 14 Pend SV Interrupt */
  SysTick_IRQn                = -1,     /* 15 System Tick Interrupt */
  PMCU_INT_IRQn               = 0,      /* 16 PMCU_INT Interrupt */
  Debug_INT_IRQn              = 1,      /* 17 Debug_INT Interrupt */
  Flash_INT_IRQn              = 2,      /* 18 Flash_INT Interrupt */
  WWDT0_INT_IRQn              = 3,      /* 19 WWDT0_INT Interrupt */
  GPIO0_INT_IRQn              = 4,      /* 20 GPIO0_INT Interrupt */
  GPIO1_INT_IRQn              = 5,      /* 21 GPIO1_INT Interrupt */
  GPIO2_INT_IRQn              = 6,      /* 22 GPIO2_INT Interrupt */
  GPIO3_INT_IRQn              = 7,      /* 23 GPIO3_INT Interrupt */
  ADC0_INT1_INT_IRQn          = 8,      /* 24 ADC0_INT1_INT Interrupt */
  ADC0_INT2_INT_IRQn          = 9,      /* 25 ADC0_INT2_INT Interrupt */
  ADC0_INT3_INT_IRQn          = 10,     /* 26 ADC0_INT3_INT Interrupt */
  ADC0_INT4_INT_IRQn          = 11,     /* 27 ADC0_INT4_INT Interrupt */
  ADC0_EVT_INT_IRQn           = 12,     /* 28 ADC0_EVT_INT Interrupt */
  ADC1_INT1_INT_IRQn          = 13,     /* 29 ADC1_INT1_INT Interrupt */
  ADC1_INT2_INT_IRQn          = 14,     /* 30 ADC1_INT2_INT Interrupt */
  ADC1_INT3_INT_IRQn          = 15,     /* 31 ADC1_INT3_INT Interrupt */
  ADC1_INT4_INT_IRQn          = 16,     /* 32 ADC1_INT4_INT Interrupt */
  ADC1_EVT_INT_IRQn           = 17,     /* 33 ADC1_EVT_INT Interrupt */
  ADC2_INT1_INT_IRQn          = 18,     /* 34 ADC2_INT1_INT Interrupt */
  ADC2_INT2_INT_IRQn          = 19,     /* 35 ADC2_INT2_INT Interrupt */
  ADC2_INT3_INT_IRQn          = 20,     /* 36 ADC2_INT3_INT Interrupt */
  ADC2_INT4_INT_IRQn          = 21,     /* 37 ADC2_INT4_INT Interrupt */
  ADC2_EVT_INT_IRQn           = 22,     /* 38 ADC2_EVT_INT Interrupt */
  MCAN0_INT_IRQn               = 23,     /* 39 MCAN0_INT Interrupt */
  MCPWM0_INT_IRQn             = 24,     /* 40 MCPWM0_INT Interrupt */
  MCPWM1_INT_IRQn             = 25,     /* 41 MCPWM1_INT Interrupt */
  MCPWM2_INT_IRQn             = 26,     /* 42 MCPWM2_INT Interrupt */
  MCPWM3_INT_IRQn             = 27,     /* 43 MCPWM3_INT Interrupt */
  MCPWM4_INT_IRQn             = 28,     /* 44 MCPWM4_INT Interrupt */
  ECAP0_INT_IRQn              = 29,     /* 45 ECAP0_INT Interrupt */
  ECAP1_INT_IRQn              = 30,     /* 46 ECAP1_INT Interrupt */
  EQEP0_INT_IRQn              = 31,     /* 47 EQEP0_INT Interrupt */
  EQEP1_INT_IRQn              = 32,     /* 48 EQEP1_INT Interrupt */
  EQEP2_INT_IRQn              = 33,     /* 49 EQEP2_INT Interrupt */
  UC0_INT_IRQn                = 34,     /* 50 UC0_INT Interrupt */
  UC1_INT_IRQn                = 35,     /* 51 UC1_INT Interrupt */
  UC2_INT_IRQn                = 36,     /* 52 UC2_INT Interrupt */
  UC3_INT_IRQn                = 37,     /* 53 UC3_INT Interrupt */
  UC4_INT_IRQn                = 38,     /* 54 UC4_INT Interrupt */
  UC5_INT_IRQn                = 39,     /* 55 UC5_INT Interrupt */
  DMA0_INT_IRQn               = 40,     /* 56 DMA0_INT Interrupt */
  TINIE_LITE_INT_IRQn         = 41,     /* 57 TINIE_LITE_INT Interrupt */
  EPI_INT_IRQn                = 42,     /* 58 EPI_INT Interrupt */
  AES_INT_IRQn                = 43,     /* 59 AES_INT Interrupt */
  TIMG4_0_INT_IRQn            = 44,     /* 60 TIMG4_0_INT Interrupt */
  TIMG12_0_INT_IRQn           = 45,     /* 61 TIMG12_0_INT Interrupt */
  TMU_LUF_INT_IRQn            = 46,     /* 62 TMU_LUF_INT Interrupt */
  TMU_LVF_INT_IRQn            = 47,     /* 63 TMU_LVF_INT Interrupt */
} IRQn_Type;

#define NonMaskableInt_VECn     2     /* Non Maskable Interrupt */
#define HardFault_VECn          3     /* Hard Fault Interrupt */
#define MemManage_VECn          4     /* Memory Management Interrupt */
#define BusFault_VECn           5     /* Bus Fault Interrupt */
#define UsageFault_VECn         6     /* Usage Fault Interrupt */
#define SecureFault_VECn        7     /* Secure Fault Interrupt */
#define SVCall_VECn             11    /* SV Call Interrupt */
#define DebugMonitor_VECn       12    /* Debug Monitor Interrupt */
#define PendSV_VECn             14    /* Pend SV Interrupt */
#define SysTick_VECn            15    /* System Tick Interrupt */
#define PMCU_INT_VECn           16    /* PMCU_INT Interrupt */
#define Debug_INT_VECn          17    /* Debug_INT Interrupt */
#define Flash_INT_VECn          18    /* Flash_INT Interrupt */
#define WWDT0_INT_VECn          19    /* WWDT0_INT Interrupt */
#define GPIO0_INT_VECn          20    /* GPIO0_INT Interrupt */
#define GPIO1_INT_VECn          21    /* GPIO1_INT Interrupt */
#define GPIO2_INT_VECn          22    /* GPIO2_INT Interrupt */
#define GPIO3_INT_VECn          23    /* GPIO3_INT Interrupt */
#define ADC0_INT1_INT_VECn      24    /* ADC0_INT1_INT Interrupt */
#define ADC0_INT2_INT_VECn      25    /* ADC0_INT2_INT Interrupt */
#define ADC0_INT3_INT_VECn      26    /* ADC0_INT3_INT Interrupt */
#define ADC0_INT4_INT_VECn      27    /* ADC0_INT4_INT Interrupt */
#define ADC0_EVT_INT_VECn       28    /* ADC0_EVT_INT Interrupt */
#define ADC1_INT1_INT_VECn      29    /* ADC1_INT1_INT Interrupt */
#define ADC1_INT2_INT_VECn      30    /* ADC1_INT2_INT Interrupt */
#define ADC1_INT3_INT_VECn      31    /* ADC1_INT3_INT Interrupt */
#define ADC1_INT4_INT_VECn      32    /* ADC1_INT4_INT Interrupt */
#define ADC1_EVT_INT_VECn       33    /* ADC1_EVT_INT Interrupt */
#define ADC2_INT1_INT_VECn      34    /* ADC2_INT1_INT Interrupt */
#define ADC2_INT2_INT_VECn      35    /* ADC2_INT2_INT Interrupt */
#define ADC2_INT3_INT_VECn      36    /* ADC2_INT3_INT Interrupt */
#define ADC2_INT4_INT_VECn      37    /* ADC2_INT4_INT Interrupt */
#define ADC2_EVT_INT_VECn       38    /* ADC2_EVT_INT Interrupt */
#define MCAN0_INT_VECn           39    /* MCAN0_INT Interrupt */
#define MCPWM0_INT_VECn         40    /* MCPWM0_INT Interrupt */
#define MCPWM1_INT_VECn         41    /* MCPWM1_INT Interrupt */
#define MCPWM2_INT_VECn         42    /* MCPWM2_INT Interrupt */
#define MCPWM3_INT_VECn         43    /* MCPWM3_INT Interrupt */
#define MCPWM4_INT_VECn         44    /* MCPWM4_INT Interrupt */
#define ECAP0_INT_VECn          45    /* ECAP0_INT Interrupt */
#define ECAP1_INT_VECn          46    /* ECAP1_INT Interrupt */
#define EQEP0_INT_VECn          47    /* EQEP0_INT Interrupt */
#define EQEP1_INT_VECn          48    /* EQEP1_INT Interrupt */
#define EQEP2_INT_VECn          49    /* EQEP2_INT Interrupt */
#define UC0_INT_VECn            50    /* UC0_INT Interrupt */
#define UC1_INT_VECn            51    /* UC1_INT Interrupt */
#define UC2_INT_VECn            52    /* UC2_INT Interrupt */
#define UC3_INT_VECn            53    /* UC3_INT Interrupt */
#define UC4_INT_VECn            54    /* UC4_INT Interrupt */
#define UC5_INT_VECn            55    /* UC5_INT Interrupt */
#define DMA0_INT_VECn           56    /* DMA0_INT Interrupt */
#define TINIE_LITE_INT_VECn     57    /* TINIE_LITE_INT Interrupt */
#define EPI_INT_VECn            58    /* EPI_INT Interrupt */
#define AES_INT_VECn            59    /* AES_INT Interrupt */
#define TIMG4_0_INT_VECn        60    /* TIMG4_0_INT Interrupt */
#define TIMG12_0_INT_VECn       61    /* TIMG12_0_INT Interrupt */
#define TMU_LUF_INT_VECn        62    /* TMU_LUF_INT Interrupt */
#define TMU_LVF_INT_VECn        63    /* TMU_LVF_INT Interrupt */



#ifdef __cplusplus
}
#endif

#endif /* hw_ints__include */
