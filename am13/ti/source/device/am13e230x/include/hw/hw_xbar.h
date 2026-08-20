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

#ifndef hw_xbar__include
#define hw_xbar__include


#ifndef __CORTEX_M
  #ifdef __cplusplus
    #define __I  volatile        /*!< Defines 'read only' permissions */
  #else
    #define __I  volatile const  /*!< Defines 'read only' permissions */
  #endif
  #define __O  volatile          /*!< Defines 'write only' permissions */
  #define __IO  volatile         /*!< Defines 'read / write' permissions */

  /* following defines should be used for structure members */
  #define __IM  volatile const   /*! Defines 'read only' structure member permissions */
  #define __OM  volatile         /*! Defines 'write only' structure member permissions */
  #define __IOM  volatile        /*! Defines 'read / write' structure member permissions */
#endif

/* Use standard integer types with explicit width */
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

#if defined ( __CC_ARM )
#pragma anon_unions
#endif

/******************************************************************************
* XBAR Registers
******************************************************************************/
#define XBAR_EPWM_XBAR_GXSEL_OFS    ((uint32_t)0x00000100U)
#define XBAR_OUTPUTXBAR_GXSEL_OFS   ((uint32_t)0x00000100U)


/** @addtogroup XBAR_INPUT_FLAG
  @{
*/

typedef struct {
  __IO uint32_t XBARFLG1;                          /* !< (@ 0x00000000) X-Bar Input Flag Register 1 */
  __IO uint32_t XBARFLG2;                          /* !< (@ 0x00000004) X-Bar Input Flag Register 2 */
       uint32_t RESERVED0[2];
  __IO uint32_t XBARCLR1;                          /* !< (@ 0x00000010) X-Bar Input Flag Clear Register 1 */
  __IO uint32_t XBARCLR2;                          /* !< (@ 0x00000014) X-Bar Input Flag Clear Register 2 */
} XBAR_INPUT_FLAG_Regs;

/*@}*/ /* end of group XBAR_INPUT_FLAG */

/** @addtogroup XBAR_EPWM_XBAR_GXSEL
  @{
*/

typedef struct {
  __IO uint32_t PWMXBARG0SEL;                      /* !< (@ 0x00000100) PWMXBAR G0 Input Select */
  __IO uint32_t PWMXBARG1SEL;                      /* !< (@ 0x00000104) PWMXBAR G1 Input Select */
       uint32_t RESERVED0[14];
} XBAR_EPWM_XBAR_GXSEL_Regs;

/*@}*/ /* end of group XBAR_EPWM_XBAR_GXSEL */

/** @addtogroup XBAR_EPWM_XBAR
  @{
*/

typedef struct {
       uint32_t RESERVED0[12];
  __IO uint32_t PWMXBAROUTINVERT;                  /* !< (@ 0x00000030) Output Signal Invert Select */
       uint32_t RESERVED1[19];
  __IO uint32_t PWMXBARLOCK;                       /* !< (@ 0x00000080) Configuration Lock register */
       uint32_t RESERVED2[31];
  XBAR_EPWM_XBAR_GXSEL_Regs  PWM_XBAR_GXSEL[8];   /* !< (@ 0x00000100) */
} XBAR_EPWM_XBAR_Regs;

/*@}*/ /* end of group XBAR_EPWM_XBAR */

/** @addtogroup XBAR_SYNC_SOC
  @{
*/

typedef struct {
  __IO uint32_t SYNCSELECT;                        /* !< (@ 0x00000000) Sync Input and Output Select Register */
  __IO uint32_t ADCSOCOUTSELECT;                   /* !< (@ 0x00000004) External ADCSOC Select Register */
  __IO uint32_t SYNCSOCLOCK;                       /* !< (@ 0x00000008) SYNCSEL and EXTADCSOC Select Lock register */
} XBAR_SYNC_SOC_Regs;

/*@}*/ /* end of group XBAR_SYNC_SOC */

/** @addtogroup XBAR_OUTPUTXBAR_GXSEL
  @{
*/

typedef struct {
  __IO uint32_t OUTPUTXBARG0SEL;                   /* !< (@ 0x00000100) OUTPUTXBAR G0 Input Select */
  __IO uint32_t OUTPUTXBARG1SEL;                   /* !< (@ 0x00000104) OUTPUTXBAR G1 Input Select */
       uint32_t RESERVED0[14];
} XBAR_OUTPUTXBAR_GXSEL_Regs;

/*@}*/ /* end of group XBAR_OUTPUTXBAR_GXSEL */

/** @addtogroup XBAR_OUTPUTXBAR
  @{
*/

typedef struct {
       uint32_t RESERVED0[5];
  __IO uint32_t OUTPUTXBARFLAGINVERT;              /* !< (@ 0x00000014) Output Signal inversion register */
       uint32_t RESERVED1[3];
  __IO uint32_t OUTPUTXBAROUTLATCH;                /* !< (@ 0x00000024) Output Signal Select Latch */
       uint32_t RESERVED2[2];
  __IO uint32_t OUTPUTXBAROUTINVERT;               /* !< (@ 0x00000030) Output Signal Invert Select */
       uint32_t RESERVED3[19];
  __IO uint32_t OUTPUTXBARLOCK;                    /* !< (@ 0x00000080) Configuration Lock register */
       uint32_t RESERVED4[31];
  XBAR_OUTPUTXBAR_GXSEL_Regs  OUTPUTXBAR_GXSEL[12]; /* !< (@ 0x00000100) */
} XBAR_OUTPUTXBAR_Regs;

/*@}*/ /* end of group XBAR_OUTPUTXBAR */

/** @addtogroup XBAR_OUTPUTXBAR_FLAG
  @{
*/

typedef struct {
       uint32_t RESERVED0[4];
  __IO uint32_t OUTPUTXBARSTATUS;                  /* !< (@ 0x00000010) Output Signal Status register */
       uint32_t RESERVED1;
  __IO uint32_t OUTPUTXBARFLAG;                    /* !< (@ 0x00000018) Output latched flag register */
  __IO uint32_t OUTPUTXBARFLAGCLEAR;               /* !< (@ 0x0000001C) Output latched flag clear register */
  __IO uint32_t OUTPUTXBARFLAGFORCE;               /* !< (@ 0x00000020) Output latched flag Force register */
} XBAR_OUTPUTXBAR_FLAG_Regs;

/*@}*/ /* end of group XBAR_OUTPUTXBAR_FLAG */

/** @addtogroup XBAR_INPUT_XBAR
  @{
*/

typedef struct {
  __IO uint32_t INPUTSELECT[28];                   /* !< (@ 0x00000000) Input Select Register (GPIO0 to x) */
       uint32_t RESERVED0[228];
  __IO uint32_t INPUTSELECTLOCK1;                  /* !< (@ 0x00000400) Input Select Lock Register 1 */
       uint32_t RESERVED1[3];
  __IO uint32_t RAW_INPUTSELECT_PA;                /* !< (@ 0x00000410) Raw Input Select Register for Port-A GPIOs */
  __IO uint32_t RAW_INPUTSELECT_PB;                /* !< (@ 0x00000414) Raw Input Select Register for Port-B GPIOs */
  __IO uint32_t RAW_INPUTSELECT_PC;                /* !< (@ 0x00000418) Raw Input Select Register for Port-C GPIOs */
  __IO uint32_t RAW_INPUTSELECT_PD;                /* !< (@ 0x0000041C) Raw Input Select Register for Port-D GPIOs */
} XBAR_INPUT_XBAR_Regs;

/*@}*/ /* end of group XBAR_INPUT_XBAR */



/******************************************************************************
* XBAR Register Offsets
******************************************************************************/
#define XBAR_INPUTSELECT(i)                      (0x00000000U + 4U * (i)) // 0 <= i < 28
#define XBAR_INPUTSELECTLOCK1                    (0x00000400U)
#define XBAR_RAW_INPUTSELECT_PA                  (0x00000410U)
#define XBAR_RAW_INPUTSELECT_PB                  (0x00000414U)
#define XBAR_RAW_INPUTSELECT_PC                  (0x00000418U)
#define XBAR_RAW_INPUTSELECT_PD                  (0x0000041CU)

#define XBAR_OUTPUTXBARSTATUS                    (0x00000010U)
#define XBAR_OUTPUTXBARFLAG                      (0x00000018U)
#define XBAR_OUTPUTXBARFLAGCLEAR                 (0x0000001CU)
#define XBAR_OUTPUTXBARFLAGFORCE                 (0x00000020U)

#define XBAR_OUTPUTXBARFLAGINVERT                (0x00000014U)
#define XBAR_OUTPUTXBAROUTLATCH                  (0x00000024U)
#define XBAR_OUTPUTXBAROUTINVERT                 (0x00000030U)
#define XBAR_OUTPUTXBARLOCK                      (0x00000080U)

#define XBAR_OUTPUTXBARG0SEL                     (0x00000100U)
#define XBAR_OUTPUTXBARG1SEL                     (0x00000104U)

#define XBAR_SYNCSELECT                          (0x00000000U)
#define XBAR_ADCSOCOUTSELECT                     (0x00000004U)
#define XBAR_SYNCSOCLOCK                         (0x00000008U)

#define XBAR_PWMXBAROUTINVERT                    (0x00000030U)
#define XBAR_PWMXBARLOCK                         (0x00000080U)

#define XBAR_PWMXBARG0SEL                        (0x00000100U)
#define XBAR_PWMXBARG1SEL                        (0x00000104U)

#define XBAR_XBARFLG1                            (0x00000000U)
#define XBAR_XBARFLG2                            (0x00000004U)
#define XBAR_XBARCLR1                            (0x00000010U)
#define XBAR_XBARCLR2                            (0x00000014U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* XBAR Register Control Bits
******************************************************************************/

/* XBAR_XBARFLG1 Bits */
/* XBAR_XBARFLG1[CMPSS0_CTRIPH] Bits */
#define XBAR_XBARFLG1_CMPSS0_CTRIPH_OFS          (0)                             /* !< CMPSS0_CTRIPH Offset */
#define XBAR_XBARFLG1_CMPSS0_CTRIPH_MASK         ((uint32_t)0x00000001U)         /* !< Input Flag for CMPSS0_CTRIPH Signal */
/* XBAR_XBARFLG1[CMPSS0_CTRIPL] Bits */
#define XBAR_XBARFLG1_CMPSS0_CTRIPL_OFS          (1)                             /* !< CMPSS0_CTRIPL Offset */
#define XBAR_XBARFLG1_CMPSS0_CTRIPL_MASK         ((uint32_t)0x00000002U)         /* !< Input Flag for CMPSS0_CTRIPL Signal */
/* XBAR_XBARFLG1[CMPSS1_CTRIPH] Bits */
#define XBAR_XBARFLG1_CMPSS1_CTRIPH_OFS          (2)                             /* !< CMPSS1_CTRIPH Offset */
#define XBAR_XBARFLG1_CMPSS1_CTRIPH_MASK         ((uint32_t)0x00000004U)         /* !< Input Flag for CMPSS1_CTRIPH Signal */
/* XBAR_XBARFLG1[CMPSS1_CTRIPL] Bits */
#define XBAR_XBARFLG1_CMPSS1_CTRIPL_OFS          (3)                             /* !< CMPSS1_CTRIPL Offset */
#define XBAR_XBARFLG1_CMPSS1_CTRIPL_MASK         ((uint32_t)0x00000008U)         /* !< Input Flag for CMPSS1_CTRIPL Signal */
/* XBAR_XBARFLG1[CMPSS2_CTRIPH] Bits */
#define XBAR_XBARFLG1_CMPSS2_CTRIPH_OFS          (4)                             /* !< CMPSS2_CTRIPH Offset */
#define XBAR_XBARFLG1_CMPSS2_CTRIPH_MASK         ((uint32_t)0x00000010U)         /* !< Input Flag for CMPSS2_CTRIPH Signal */
/* XBAR_XBARFLG1[CMPSS2_CTRIPL] Bits */
#define XBAR_XBARFLG1_CMPSS2_CTRIPL_OFS          (5)                             /* !< CMPSS2_CTRIPL Offset */
#define XBAR_XBARFLG1_CMPSS2_CTRIPL_MASK         ((uint32_t)0x00000020U)         /* !< Input Flag for CMPSS2_CTRIPL Signal */
/* XBAR_XBARFLG1[CMPSS3_CTRIPH] Bits */
#define XBAR_XBARFLG1_CMPSS3_CTRIPH_OFS          (6)                             /* !< CMPSS3_CTRIPH Offset */
#define XBAR_XBARFLG1_CMPSS3_CTRIPH_MASK         ((uint32_t)0x00000040U)         /* !< Input Flag for CMPSS3_CTRIPH Signal */
/* XBAR_XBARFLG1[CMPSS3_CTRIPL] Bits */
#define XBAR_XBARFLG1_CMPSS3_CTRIPL_OFS          (7)                             /* !< CMPSS3_CTRIPL Offset */
#define XBAR_XBARFLG1_CMPSS3_CTRIPL_MASK         ((uint32_t)0x00000080U)         /* !< Input Flag for CMPSS3_CTRIPL Signal */
/* XBAR_XBARFLG1[ADC0EVT1] Bits */
#define XBAR_XBARFLG1_ADC0EVT1_OFS               (8)                             /* !< ADC0EVT1 Offset */
#define XBAR_XBARFLG1_ADC0EVT1_MASK              ((uint32_t)0x00000100U)         /* !< Input Flag for ADC0EVT1 Signal */
/* XBAR_XBARFLG1[ADC0EVT2] Bits */
#define XBAR_XBARFLG1_ADC0EVT2_OFS               (9)                             /* !< ADC0EVT2 Offset */
#define XBAR_XBARFLG1_ADC0EVT2_MASK              ((uint32_t)0x00000200U)         /* !< Input Flag for ADC0EVT2 Signal */
/* XBAR_XBARFLG1[ADC0EVT3] Bits */
#define XBAR_XBARFLG1_ADC0EVT3_OFS               (10)                            /* !< ADC0EVT3 Offset */
#define XBAR_XBARFLG1_ADC0EVT3_MASK              ((uint32_t)0x00000400U)         /* !< Input Flag for ADC0EVT3 Signal */
/* XBAR_XBARFLG1[ADC0EVT4] Bits */
#define XBAR_XBARFLG1_ADC0EVT4_OFS               (11)                            /* !< ADC0EVT4 Offset */
#define XBAR_XBARFLG1_ADC0EVT4_MASK              ((uint32_t)0x00000800U)         /* !< Input Flag for ADC0EVT4 Signal */
/* XBAR_XBARFLG1[ADC1EVT1] Bits */
#define XBAR_XBARFLG1_ADC1EVT1_OFS               (12)                            /* !< ADC1EVT1 Offset */
#define XBAR_XBARFLG1_ADC1EVT1_MASK              ((uint32_t)0x00001000U)         /* !< Input Flag for ADC1EVT1 Signal */
/* XBAR_XBARFLG1[ADC1EVT2] Bits */
#define XBAR_XBARFLG1_ADC1EVT2_OFS               (13)                            /* !< ADC1EVT2 Offset */
#define XBAR_XBARFLG1_ADC1EVT2_MASK              ((uint32_t)0x00002000U)         /* !< Input Flag for ADC1EVT2 Signal */
/* XBAR_XBARFLG1[ADC1EVT3] Bits */
#define XBAR_XBARFLG1_ADC1EVT3_OFS               (14)                            /* !< ADC1EVT3 Offset */
#define XBAR_XBARFLG1_ADC1EVT3_MASK              ((uint32_t)0x00004000U)         /* !< Input Flag for ADC1EVT3 Signal */
/* XBAR_XBARFLG1[ADC1EVT4] Bits */
#define XBAR_XBARFLG1_ADC1EVT4_OFS               (15)                            /* !< ADC1EVT4 Offset */
#define XBAR_XBARFLG1_ADC1EVT4_MASK              ((uint32_t)0x00008000U)         /* !< Input Flag for ADC1EVT4 Signal */
/* XBAR_XBARFLG1[ADC2EVT1] Bits */
#define XBAR_XBARFLG1_ADC2EVT1_OFS               (16)                            /* !< ADC2EVT1 Offset */
#define XBAR_XBARFLG1_ADC2EVT1_MASK              ((uint32_t)0x00010000U)         /* !< Input Flag for ADC2EVT1 Signal */
/* XBAR_XBARFLG1[ADC2EVT2] Bits */
#define XBAR_XBARFLG1_ADC2EVT2_OFS               (17)                            /* !< ADC2EVT2 Offset */
#define XBAR_XBARFLG1_ADC2EVT2_MASK              ((uint32_t)0x00020000U)         /* !< Input Flag for ADC2EVT2 Signal */
/* XBAR_XBARFLG1[ADC2EVT3] Bits */
#define XBAR_XBARFLG1_ADC2EVT3_OFS               (18)                            /* !< ADC2EVT3 Offset */
#define XBAR_XBARFLG1_ADC2EVT3_MASK              ((uint32_t)0x00040000U)         /* !< Input Flag for ADC2EVT3 Signal */
/* XBAR_XBARFLG1[ADC2EVT4] Bits */
#define XBAR_XBARFLG1_ADC2EVT4_OFS               (19)                            /* !< ADC2EVT4 Offset */
#define XBAR_XBARFLG1_ADC2EVT4_MASK              ((uint32_t)0x00080000U)         /* !< Input Flag for ADC2EVT4 Signal */
/* XBAR_XBARFLG1[INPUTXBAR1] Bits */
#define XBAR_XBARFLG1_INPUTXBAR1_OFS             (20)                            /* !< INPUTXBAR1 Offset */
#define XBAR_XBARFLG1_INPUTXBAR1_MASK            ((uint32_t)0x00100000U)         /* !< Input Flag for INPUTXBAR1 Signal */
/* XBAR_XBARFLG1[INPUTXBAR2] Bits */
#define XBAR_XBARFLG1_INPUTXBAR2_OFS             (21)                            /* !< INPUTXBAR2 Offset */
#define XBAR_XBARFLG1_INPUTXBAR2_MASK            ((uint32_t)0x00200000U)         /* !< Input Flag for INPUTXBAR2 Signal */
/* XBAR_XBARFLG1[INPUTXBAR3] Bits */
#define XBAR_XBARFLG1_INPUTXBAR3_OFS             (22)                            /* !< INPUTXBAR3 Offset */
#define XBAR_XBARFLG1_INPUTXBAR3_MASK            ((uint32_t)0x00400000U)         /* !< Input Flag for INPUTXBAR3 Signal */
/* XBAR_XBARFLG1[INPUTXBAR4] Bits */
#define XBAR_XBARFLG1_INPUTXBAR4_OFS             (23)                            /* !< INPUTXBAR4 Offset */
#define XBAR_XBARFLG1_INPUTXBAR4_MASK            ((uint32_t)0x00800000U)         /* !< Input Flag for INPUTXBAR4 Signal */
/* XBAR_XBARFLG1[INPUTXBAR5] Bits */
#define XBAR_XBARFLG1_INPUTXBAR5_OFS             (24)                            /* !< INPUTXBAR5 Offset */
#define XBAR_XBARFLG1_INPUTXBAR5_MASK            ((uint32_t)0x01000000U)         /* !< Input Flag for INPUTXBAR5 Signal */
/* XBAR_XBARFLG1[INPUTXBAR6] Bits */
#define XBAR_XBARFLG1_INPUTXBAR6_OFS             (25)                            /* !< INPUTXBAR6 Offset */
#define XBAR_XBARFLG1_INPUTXBAR6_MASK            ((uint32_t)0x02000000U)         /* !< Input Flag for INPUTXBAR6 Signal */
/* XBAR_XBARFLG1[INPUTXBAR7] Bits */
#define XBAR_XBARFLG1_INPUTXBAR7_OFS             (26)                            /* !< INPUTXBAR7 Offset */
#define XBAR_XBARFLG1_INPUTXBAR7_MASK            ((uint32_t)0x04000000U)         /* !< Input Flag for INPUTXBAR7 Signal */
/* XBAR_XBARFLG1[INPUTXBAR8] Bits */
#define XBAR_XBARFLG1_INPUTXBAR8_OFS             (27)                            /* !< INPUTXBAR8 Offset */
#define XBAR_XBARFLG1_INPUTXBAR8_MASK            ((uint32_t)0x08000000U)         /* !< Input Flag for INPUTXBAR8 Signal */
/* XBAR_XBARFLG1[INPUTXBAR9] Bits */
#define XBAR_XBARFLG1_INPUTXBAR9_OFS             (28)                            /* !< INPUTXBAR9 Offset */
#define XBAR_XBARFLG1_INPUTXBAR9_MASK            ((uint32_t)0x10000000U)         /* !< Input Flag for INPUTXBAR9 Signal */
/* XBAR_XBARFLG1[INPUTXBAR10] Bits */
#define XBAR_XBARFLG1_INPUTXBAR10_OFS            (29)                            /* !< INPUTXBAR10 Offset */
#define XBAR_XBARFLG1_INPUTXBAR10_MASK           ((uint32_t)0x20000000U)         /* !< Input Flag for INPUTXBAR10 Signal */
/* XBAR_XBARFLG1[INPUTXBAR11] Bits */
#define XBAR_XBARFLG1_INPUTXBAR11_OFS            (30)                            /* !< INPUTXBAR11 Offset */
#define XBAR_XBARFLG1_INPUTXBAR11_MASK           ((uint32_t)0x40000000U)         /* !< Input Flag for INPUTXBAR11 Signal */
/* XBAR_XBARFLG1[INPUTXBAR12] Bits */
#define XBAR_XBARFLG1_INPUTXBAR12_OFS            (31)                            /* !< INPUTXBAR12 Offset */
#define XBAR_XBARFLG1_INPUTXBAR12_MASK           ((uint32_t)0x80000000U)         /* !< Input Flag for INPUTXBAR12 Signal */

/* XBAR_XBARFLG2 Bits */
/* XBAR_XBARFLG2[INPUTXBAR13] Bits */
#define XBAR_XBARFLG2_INPUTXBAR13_OFS            (0)                             /* !< INPUTXBAR13 Offset */
#define XBAR_XBARFLG2_INPUTXBAR13_MASK           ((uint32_t)0x00000001U)         /* !< Input Flag for INPUTXBAR13 Signal */
/* XBAR_XBARFLG2[INPUTXBAR14] Bits */
#define XBAR_XBARFLG2_INPUTXBAR14_OFS            (1)                             /* !< INPUTXBAR14 Offset */
#define XBAR_XBARFLG2_INPUTXBAR14_MASK           ((uint32_t)0x00000002U)         /* !< Input Flag for INPUTXBAR14 Signal */
/* XBAR_XBARFLG2[INPUTXBAR15] Bits */
#define XBAR_XBARFLG2_INPUTXBAR15_OFS            (2)                             /* !< INPUTXBAR15 Offset */
#define XBAR_XBARFLG2_INPUTXBAR15_MASK           ((uint32_t)0x00000004U)         /* !< Input Flag for INPUTXBAR15 Signal */
/* XBAR_XBARFLG2[INPUTXBAR16] Bits */
#define XBAR_XBARFLG2_INPUTXBAR16_OFS            (3)                             /* !< INPUTXBAR16 Offset */
#define XBAR_XBARFLG2_INPUTXBAR16_MASK           ((uint32_t)0x00000008U)         /* !< Input Flag for INPUTXBAR16 Signal */
/* XBAR_XBARFLG2[ECAP0_OUT] Bits */
#define XBAR_XBARFLG2_ECAP0_OUT_OFS              (4)                             /* !< ECAP0_OUT Offset */
#define XBAR_XBARFLG2_ECAP0_OUT_MASK             ((uint32_t)0x00000010U)         /* !< Input Flag for ECAP0_OUT Signal */
/* XBAR_XBARFLG2[ECAP1_OUT] Bits */
#define XBAR_XBARFLG2_ECAP1_OUT_OFS              (5)                             /* !< ECAP1_OUT Offset */
#define XBAR_XBARFLG2_ECAP1_OUT_MASK             ((uint32_t)0x00000020U)         /* !< Input Flag for ECAP1_OUT Signal */
/* XBAR_XBARFLG2[ADCSOCA] Bits */
#define XBAR_XBARFLG2_ADCSOCA_OFS                (6)                             /* !< ADCSOCA Offset */
#define XBAR_XBARFLG2_ADCSOCA_MASK               ((uint32_t)0x00000040U)         /* !< Input Flag for ADCSOCA Signal */
/* XBAR_XBARFLG2[ADCSOCB] Bits */
#define XBAR_XBARFLG2_ADCSOCB_OFS                (7)                             /* !< ADCSOCB Offset */
#define XBAR_XBARFLG2_ADCSOCB_MASK               ((uint32_t)0x00000080U)         /* !< Input Flag for ADCSOCB Signal */
/* XBAR_XBARFLG2[EXTSYNCOUT] Bits */
#define XBAR_XBARFLG2_EXTSYNCOUT_OFS             (8)                             /* !< EXTSYNCOUT Offset */
#define XBAR_XBARFLG2_EXTSYNCOUT_MASK            ((uint32_t)0x00000100U)         /* !< Input Flag for EXTSYNCOUT Signal */
/* XBAR_XBARFLG2[MCAN_INT0] Bits */
#define XBAR_XBARFLG2_MCAN_INT0_OFS              (9)                             /* !< MCAN_INT0 Offset */
#define XBAR_XBARFLG2_MCAN_INT0_MASK             ((uint32_t)0x00000200U)         /* !< Input Flag for MCAN_INT0 Signal */
/* XBAR_XBARFLG2[EQEP0_ERR] Bits */
#define XBAR_XBARFLG2_EQEP0_ERR_OFS              (12)                            /* !< EQEP0_ERR Offset */
#define XBAR_XBARFLG2_EQEP0_ERR_MASK             ((uint32_t)0x00001000U)         /* !< Input Flag for EQEP0_ERR Signal */
/* XBAR_XBARFLG2[EQEP1_ERR] Bits */
#define XBAR_XBARFLG2_EQEP1_ERR_OFS              (13)                            /* !< EQEP1_ERR Offset */
#define XBAR_XBARFLG2_EQEP1_ERR_MASK             ((uint32_t)0x00002000U)         /* !< Input Flag for EQEP1_ERR Signal */
/* XBAR_XBARFLG2[EQEP2_ERR] Bits */
#define XBAR_XBARFLG2_EQEP2_ERR_OFS              (14)                            /* !< EQEP2_ERR Offset */
#define XBAR_XBARFLG2_EQEP2_ERR_MASK             ((uint32_t)0x00004000U)         /* !< Input Flag for EQEP2_ERR Signal */
/* XBAR_XBARFLG2[EQEP0_INDEX_SYNCOUT] Bits */
#define XBAR_XBARFLG2_EQEP0_INDEX_SYNCOUT_OFS    (15)                            /* !< EQEP0_INDEX_SYNCOUT Offset */
#define XBAR_XBARFLG2_EQEP0_INDEX_SYNCOUT_MASK   ((uint32_t)0x00008000U)         /* !< Input Flag for EQEP0_INDEX_SYNCOUT
                                                                                    Signal */
/* XBAR_XBARFLG2[EQEP0_STROBE_SYNCOUT] Bits */
#define XBAR_XBARFLG2_EQEP0_STROBE_SYNCOUT_OFS   (16)                            /* !< EQEP0_STROBE_SYNCOUT Offset */
#define XBAR_XBARFLG2_EQEP0_STROBE_SYNCOUT_MASK  ((uint32_t)0x00010000U)         /* !< Input Flag for EQEP0_STROBE_SYNCOUT
                                                                                    Signal */
/* XBAR_XBARFLG2[EQEP1_INDEX_SYNCOUT] Bits */
#define XBAR_XBARFLG2_EQEP1_INDEX_SYNCOUT_OFS    (17)                            /* !< EQEP1_INDEX_SYNCOUT Offset */
#define XBAR_XBARFLG2_EQEP1_INDEX_SYNCOUT_MASK   ((uint32_t)0x00020000U)         /* !< Input Flag for EQEP1_INDEX_SYNCOUT
                                                                                    Signal */
/* XBAR_XBARFLG2[EQEP1_STROBE_SYNCOUT] Bits */
#define XBAR_XBARFLG2_EQEP1_STROBE_SYNCOUT_OFS   (18)                            /* !< EQEP1_STROBE_SYNCOUT Offset */
#define XBAR_XBARFLG2_EQEP1_STROBE_SYNCOUT_MASK  ((uint32_t)0x00040000U)         /* !< Input Flag for EQEP1_STROBE_SYNCOUT
                                                                                    Signal */
/* XBAR_XBARFLG2[EQEP2_INDEX_SYNCOUT] Bits */
#define XBAR_XBARFLG2_EQEP2_INDEX_SYNCOUT_OFS    (19)                            /* !< EQEP2_INDEX_SYNCOUT Offset */
#define XBAR_XBARFLG2_EQEP2_INDEX_SYNCOUT_MASK   ((uint32_t)0x00080000U)         /* !< Input Flag for EQEP2_INDEX_SYNCOUT
                                                                                    Signal */
/* XBAR_XBARFLG2[EQEP2_STROBE_SYNCOUT] Bits */
#define XBAR_XBARFLG2_EQEP2_STROBE_SYNCOUT_OFS   (20)                            /* !< EQEP2_STROBE_SYNCOUT Offset */
#define XBAR_XBARFLG2_EQEP2_STROBE_SYNCOUT_MASK  ((uint32_t)0x00100000U)         /* !< Input Flag for EQEP2_STROBE_SYNCOUT
                                                                                    Signal */
/* XBAR_XBARFLG2[CMPSS0_CTRIPOUTH] Bits */
#define XBAR_XBARFLG2_CMPSS0_CTRIPOUTH_OFS       (21)                            /* !< CMPSS0_CTRIPOUTH Offset */
#define XBAR_XBARFLG2_CMPSS0_CTRIPOUTH_MASK      ((uint32_t)0x00200000U)         /* !< Input Flag for CMPSS0_CTRIPOUTH
                                                                                    Signal */
/* XBAR_XBARFLG2[CMPSS0_CTRIPOUTL] Bits */
#define XBAR_XBARFLG2_CMPSS0_CTRIPOUTL_OFS       (22)                            /* !< CMPSS0_CTRIPOUTL Offset */
#define XBAR_XBARFLG2_CMPSS0_CTRIPOUTL_MASK      ((uint32_t)0x00400000U)         /* !< Input Flag for CMPSS0_CTRIPOUTL
                                                                                    Signal */
/* XBAR_XBARFLG2[CMPSS1_CTRIPOUTH] Bits */
#define XBAR_XBARFLG2_CMPSS1_CTRIPOUTH_OFS       (23)                            /* !< CMPSS1_CTRIPOUTH Offset */
#define XBAR_XBARFLG2_CMPSS1_CTRIPOUTH_MASK      ((uint32_t)0x00800000U)         /* !< Input Flag for CMPSS1_CTRIPOUTH
                                                                                    Signal */
/* XBAR_XBARFLG2[CMPSS1_CTRIPOUTL] Bits */
#define XBAR_XBARFLG2_CMPSS1_CTRIPOUTL_OFS       (24)                            /* !< CMPSS1_CTRIPOUTL Offset */
#define XBAR_XBARFLG2_CMPSS1_CTRIPOUTL_MASK      ((uint32_t)0x01000000U)         /* !< Input Flag for CMPSS1_CTRIPOUTL
                                                                                    Signal */
/* XBAR_XBARFLG2[CMPSS2_CTRIPOUTH] Bits */
#define XBAR_XBARFLG2_CMPSS2_CTRIPOUTH_OFS       (25)                            /* !< CMPSS2_CTRIPOUTH Offset */
#define XBAR_XBARFLG2_CMPSS2_CTRIPOUTH_MASK      ((uint32_t)0x02000000U)         /* !< Input Flag for CMPSS2_CTRIPOUTH
                                                                                    Signal */
/* XBAR_XBARFLG2[CMPSS2_CTRIPOUTL] Bits */
#define XBAR_XBARFLG2_CMPSS2_CTRIPOUTL_OFS       (26)                            /* !< CMPSS2_CTRIPOUTL Offset */
#define XBAR_XBARFLG2_CMPSS2_CTRIPOUTL_MASK      ((uint32_t)0x04000000U)         /* !< Input Flag for CMPSS2_CTRIPOUTL
                                                                                    Signal */
/* XBAR_XBARFLG2[CMPSS3_CTRIPOUTH] Bits */
#define XBAR_XBARFLG2_CMPSS3_CTRIPOUTH_OFS       (27)                            /* !< CMPSS3_CTRIPOUTH Offset */
#define XBAR_XBARFLG2_CMPSS3_CTRIPOUTH_MASK      ((uint32_t)0x08000000U)         /* !< Input Flag for CMPSS3_CTRIPOUTH
                                                                                    Signal */
/* XBAR_XBARFLG2[CMPSS3_CTRIPOUTL] Bits */
#define XBAR_XBARFLG2_CMPSS3_CTRIPOUTL_OFS       (28)                            /* !< CMPSS3_CTRIPOUTL Offset */
#define XBAR_XBARFLG2_CMPSS3_CTRIPOUTL_MASK      ((uint32_t)0x10000000U)         /* !< Input Flag for CMPSS3_CTRIPOUTL
                                                                                    Signal */
/* XBAR_XBARFLG2[CPU_HALTED] Bits */
#define XBAR_XBARFLG2_CPU_HALTED_OFS             (29)                            /* !< CPU_HALTED Offset */
#define XBAR_XBARFLG2_CPU_HALTED_MASK            ((uint32_t)0x20000000U)         /* !< Input Flag for CPU_HALTED Signal */

/* XBAR_XBARCLR1 Bits */
/* XBAR_XBARCLR1[CMPSS0_CTRIPH] Bits */
#define XBAR_XBARCLR1_CMPSS0_CTRIPH_OFS          (0)                             /* !< CMPSS0_CTRIPH Offset */
#define XBAR_XBARCLR1_CMPSS0_CTRIPH_MASK         ((uint32_t)0x00000001U)         /* !< Input Flag Clear for CMPSS0_CTRIPH
                                                                                    Signal */
/* XBAR_XBARCLR1[CMPSS0_CTRIPL] Bits */
#define XBAR_XBARCLR1_CMPSS0_CTRIPL_OFS          (1)                             /* !< CMPSS0_CTRIPL Offset */
#define XBAR_XBARCLR1_CMPSS0_CTRIPL_MASK         ((uint32_t)0x00000002U)         /* !< Input Flag Clear for CMPSS0_CTRIPL
                                                                                    Signal */
/* XBAR_XBARCLR1[CMPSS1_CTRIPH] Bits */
#define XBAR_XBARCLR1_CMPSS1_CTRIPH_OFS          (2)                             /* !< CMPSS1_CTRIPH Offset */
#define XBAR_XBARCLR1_CMPSS1_CTRIPH_MASK         ((uint32_t)0x00000004U)         /* !< Input Flag Clear for CMPSS1_CTRIPH
                                                                                    Signal */
/* XBAR_XBARCLR1[CMPSS1_CTRIPL] Bits */
#define XBAR_XBARCLR1_CMPSS1_CTRIPL_OFS          (3)                             /* !< CMPSS1_CTRIPL Offset */
#define XBAR_XBARCLR1_CMPSS1_CTRIPL_MASK         ((uint32_t)0x00000008U)         /* !< Input Flag Clear for CMPSS1_CTRIPL
                                                                                    Signal */
/* XBAR_XBARCLR1[CMPSS2_CTRIPH] Bits */
#define XBAR_XBARCLR1_CMPSS2_CTRIPH_OFS          (4)                             /* !< CMPSS2_CTRIPH Offset */
#define XBAR_XBARCLR1_CMPSS2_CTRIPH_MASK         ((uint32_t)0x00000010U)         /* !< Input Flag Clear for CMPSS2_CTRIPH
                                                                                    Signal */
/* XBAR_XBARCLR1[CMPSS2_CTRIPL] Bits */
#define XBAR_XBARCLR1_CMPSS2_CTRIPL_OFS          (5)                             /* !< CMPSS2_CTRIPL Offset */
#define XBAR_XBARCLR1_CMPSS2_CTRIPL_MASK         ((uint32_t)0x00000020U)         /* !< Input Flag Clear for CMPSS2_CTRIPL
                                                                                    Signal */
/* XBAR_XBARCLR1[CMPSS3_CTRIPH] Bits */
#define XBAR_XBARCLR1_CMPSS3_CTRIPH_OFS          (6)                             /* !< CMPSS3_CTRIPH Offset */
#define XBAR_XBARCLR1_CMPSS3_CTRIPH_MASK         ((uint32_t)0x00000040U)         /* !< Input Flag Clear for CMPSS3_CTRIPH
                                                                                    Signal */
/* XBAR_XBARCLR1[CMPSS3_CTRIPL] Bits */
#define XBAR_XBARCLR1_CMPSS3_CTRIPL_OFS          (7)                             /* !< CMPSS3_CTRIPL Offset */
#define XBAR_XBARCLR1_CMPSS3_CTRIPL_MASK         ((uint32_t)0x00000080U)         /* !< Input Flag Clear for CMPSS3_CTRIPL
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC0EVT1] Bits */
#define XBAR_XBARCLR1_ADC0EVT1_OFS               (8)                             /* !< ADC0EVT1 Offset */
#define XBAR_XBARCLR1_ADC0EVT1_MASK              ((uint32_t)0x00000100U)         /* !< Input Flag Clear for ADC0EVT1
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC0EVT2] Bits */
#define XBAR_XBARCLR1_ADC0EVT2_OFS               (9)                             /* !< ADC0EVT2 Offset */
#define XBAR_XBARCLR1_ADC0EVT2_MASK              ((uint32_t)0x00000200U)         /* !< Input Flag Clear for ADC0EVT2
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC0EVT3] Bits */
#define XBAR_XBARCLR1_ADC0EVT3_OFS               (10)                            /* !< ADC0EVT3 Offset */
#define XBAR_XBARCLR1_ADC0EVT3_MASK              ((uint32_t)0x00000400U)         /* !< Input Flag Clear for ADC0EVT3
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC0EVT4] Bits */
#define XBAR_XBARCLR1_ADC0EVT4_OFS               (11)                            /* !< ADC0EVT4 Offset */
#define XBAR_XBARCLR1_ADC0EVT4_MASK              ((uint32_t)0x00000800U)         /* !< Input Flag Clear for ADC0EVT4
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC1EVT1] Bits */
#define XBAR_XBARCLR1_ADC1EVT1_OFS               (12)                            /* !< ADC1EVT1 Offset */
#define XBAR_XBARCLR1_ADC1EVT1_MASK              ((uint32_t)0x00001000U)         /* !< Input Flag Clear for ADC1EVT1
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC1EVT2] Bits */
#define XBAR_XBARCLR1_ADC1EVT2_OFS               (13)                            /* !< ADC1EVT2 Offset */
#define XBAR_XBARCLR1_ADC1EVT2_MASK              ((uint32_t)0x00002000U)         /* !< Input Flag Clear for ADC1EVT2
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC1EVT3] Bits */
#define XBAR_XBARCLR1_ADC1EVT3_OFS               (14)                            /* !< ADC1EVT3 Offset */
#define XBAR_XBARCLR1_ADC1EVT3_MASK              ((uint32_t)0x00004000U)         /* !< Input Flag Clear for ADC1EVT3
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC1EVT4] Bits */
#define XBAR_XBARCLR1_ADC1EVT4_OFS               (15)                            /* !< ADC1EVT4 Offset */
#define XBAR_XBARCLR1_ADC1EVT4_MASK              ((uint32_t)0x00008000U)         /* !< Input Flag Clear for ADC1EVT4
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC2EVT1] Bits */
#define XBAR_XBARCLR1_ADC2EVT1_OFS               (16)                            /* !< ADC2EVT1 Offset */
#define XBAR_XBARCLR1_ADC2EVT1_MASK              ((uint32_t)0x00010000U)         /* !< Input Flag Clear for ADC2EVT1
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC2EVT2] Bits */
#define XBAR_XBARCLR1_ADC2EVT2_OFS               (17)                            /* !< ADC2EVT2 Offset */
#define XBAR_XBARCLR1_ADC2EVT2_MASK              ((uint32_t)0x00020000U)         /* !< Input Flag Clear for ADC2EVT2
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC2EVT3] Bits */
#define XBAR_XBARCLR1_ADC2EVT3_OFS               (18)                            /* !< ADC2EVT3 Offset */
#define XBAR_XBARCLR1_ADC2EVT3_MASK              ((uint32_t)0x00040000U)         /* !< Input Flag Clear for ADC2EVT3
                                                                                    Signal */
/* XBAR_XBARCLR1[ADC2EVT4] Bits */
#define XBAR_XBARCLR1_ADC2EVT4_OFS               (19)                            /* !< ADC2EVT4 Offset */
#define XBAR_XBARCLR1_ADC2EVT4_MASK              ((uint32_t)0x00080000U)         /* !< Input Flag Clear for ADC2EVT4
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR1] Bits */
#define XBAR_XBARCLR1_INPUTXBAR1_OFS             (20)                            /* !< INPUTXBAR1 Offset */
#define XBAR_XBARCLR1_INPUTXBAR1_MASK            ((uint32_t)0x00100000U)         /* !< Input Flag Clear for INPUTXBAR1
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR2] Bits */
#define XBAR_XBARCLR1_INPUTXBAR2_OFS             (21)                            /* !< INPUTXBAR2 Offset */
#define XBAR_XBARCLR1_INPUTXBAR2_MASK            ((uint32_t)0x00200000U)         /* !< Input Flag Clear for INPUTXBAR2
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR3] Bits */
#define XBAR_XBARCLR1_INPUTXBAR3_OFS             (22)                            /* !< INPUTXBAR3 Offset */
#define XBAR_XBARCLR1_INPUTXBAR3_MASK            ((uint32_t)0x00400000U)         /* !< Input Flag Clear for INPUTXBAR3
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR4] Bits */
#define XBAR_XBARCLR1_INPUTXBAR4_OFS             (23)                            /* !< INPUTXBAR4 Offset */
#define XBAR_XBARCLR1_INPUTXBAR4_MASK            ((uint32_t)0x00800000U)         /* !< Input Flag Clear for INPUTXBAR4
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR5] Bits */
#define XBAR_XBARCLR1_INPUTXBAR5_OFS             (24)                            /* !< INPUTXBAR5 Offset */
#define XBAR_XBARCLR1_INPUTXBAR5_MASK            ((uint32_t)0x01000000U)         /* !< Input Flag Clear for INPUTXBAR5
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR6] Bits */
#define XBAR_XBARCLR1_INPUTXBAR6_OFS             (25)                            /* !< INPUTXBAR6 Offset */
#define XBAR_XBARCLR1_INPUTXBAR6_MASK            ((uint32_t)0x02000000U)         /* !< Input Flag Clear for INPUTXBAR6
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR7] Bits */
#define XBAR_XBARCLR1_INPUTXBAR7_OFS             (26)                            /* !< INPUTXBAR7 Offset */
#define XBAR_XBARCLR1_INPUTXBAR7_MASK            ((uint32_t)0x04000000U)         /* !< Input Flag Clear for INPUTXBAR7
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR8] Bits */
#define XBAR_XBARCLR1_INPUTXBAR8_OFS             (27)                            /* !< INPUTXBAR8 Offset */
#define XBAR_XBARCLR1_INPUTXBAR8_MASK            ((uint32_t)0x08000000U)         /* !< Input Flag Clear for INPUTXBAR8
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR9] Bits */
#define XBAR_XBARCLR1_INPUTXBAR9_OFS             (28)                            /* !< INPUTXBAR9 Offset */
#define XBAR_XBARCLR1_INPUTXBAR9_MASK            ((uint32_t)0x10000000U)         /* !< Input Flag Clear for INPUTXBAR9
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR10] Bits */
#define XBAR_XBARCLR1_INPUTXBAR10_OFS            (29)                            /* !< INPUTXBAR10 Offset */
#define XBAR_XBARCLR1_INPUTXBAR10_MASK           ((uint32_t)0x20000000U)         /* !< Input Flag Clear for INPUTXBAR10
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR11] Bits */
#define XBAR_XBARCLR1_INPUTXBAR11_OFS            (30)                            /* !< INPUTXBAR11 Offset */
#define XBAR_XBARCLR1_INPUTXBAR11_MASK           ((uint32_t)0x40000000U)         /* !< Input Flag Clear for INPUTXBAR11
                                                                                    Signal */
/* XBAR_XBARCLR1[INPUTXBAR12] Bits */
#define XBAR_XBARCLR1_INPUTXBAR12_OFS            (31)                            /* !< INPUTXBAR12 Offset */
#define XBAR_XBARCLR1_INPUTXBAR12_MASK           ((uint32_t)0x80000000U)         /* !< Input Flag Clear for INPUTXBAR12
                                                                                    Signal */

/* XBAR_XBARCLR2 Bits */
/* XBAR_XBARCLR2[INPUTXBAR13] Bits */
#define XBAR_XBARCLR2_INPUTXBAR13_OFS            (0)                             /* !< INPUTXBAR13 Offset */
#define XBAR_XBARCLR2_INPUTXBAR13_MASK           ((uint32_t)0x00000001U)         /* !< Input Flag Clear for INPUTXBAR13
                                                                                    Signal */
/* XBAR_XBARCLR2[INPUTXBAR14] Bits */
#define XBAR_XBARCLR2_INPUTXBAR14_OFS            (1)                             /* !< INPUTXBAR14 Offset */
#define XBAR_XBARCLR2_INPUTXBAR14_MASK           ((uint32_t)0x00000002U)         /* !< Input Flag Clear for INPUTXBAR14
                                                                                    Signal */
/* XBAR_XBARCLR2[INPUTXBAR15] Bits */
#define XBAR_XBARCLR2_INPUTXBAR15_OFS            (2)                             /* !< INPUTXBAR15 Offset */
#define XBAR_XBARCLR2_INPUTXBAR15_MASK           ((uint32_t)0x00000004U)         /* !< Input Flag Clear for INPUTXBAR15
                                                                                    Signal */
/* XBAR_XBARCLR2[INPUTXBAR16] Bits */
#define XBAR_XBARCLR2_INPUTXBAR16_OFS            (3)                             /* !< INPUTXBAR16 Offset */
#define XBAR_XBARCLR2_INPUTXBAR16_MASK           ((uint32_t)0x00000008U)         /* !< Input Flag Clear for INPUTXBAR16
                                                                                    Signal */
/* XBAR_XBARCLR2[ECAP0_OUT] Bits */
#define XBAR_XBARCLR2_ECAP0_OUT_OFS              (4)                             /* !< ECAP0_OUT Offset */
#define XBAR_XBARCLR2_ECAP0_OUT_MASK             ((uint32_t)0x00000010U)         /* !< Input Flag Clear for ECAP0_OUT
                                                                                    Signal */
/* XBAR_XBARCLR2[ECAP1_OUT] Bits */
#define XBAR_XBARCLR2_ECAP1_OUT_OFS              (5)                             /* !< ECAP1_OUT Offset */
#define XBAR_XBARCLR2_ECAP1_OUT_MASK             ((uint32_t)0x00000020U)         /* !< Input Flag Clear for ECAP1_OUT
                                                                                    Signal */
/* XBAR_XBARCLR2[ADCSOCA] Bits */
#define XBAR_XBARCLR2_ADCSOCA_OFS                (6)                             /* !< ADCSOCA Offset */
#define XBAR_XBARCLR2_ADCSOCA_MASK               ((uint32_t)0x00000040U)         /* !< Input Flag Clear for ADCSOCA Signal */
/* XBAR_XBARCLR2[ADCSOCB] Bits */
#define XBAR_XBARCLR2_ADCSOCB_OFS                (7)                             /* !< ADCSOCB Offset */
#define XBAR_XBARCLR2_ADCSOCB_MASK               ((uint32_t)0x00000080U)         /* !< Input Flag Clear for ADCSOCB Signal */
/* XBAR_XBARCLR2[EXTSYNCOUT] Bits */
#define XBAR_XBARCLR2_EXTSYNCOUT_OFS             (8)                             /* !< EXTSYNCOUT Offset */
#define XBAR_XBARCLR2_EXTSYNCOUT_MASK            ((uint32_t)0x00000100U)         /* !< Input Flag Clear for EXTSYNCOUT
                                                                                    Signal */
/* XBAR_XBARCLR2[MCAN_INT0] Bits */
#define XBAR_XBARCLR2_MCAN_INT0_OFS              (9)                             /* !< MCAN_INT0 Offset */
#define XBAR_XBARCLR2_MCAN_INT0_MASK             ((uint32_t)0x00000200U)         /* !< Input Flag Clear for MCAN_INT0
                                                                                    Signal */
/* XBAR_XBARCLR2[EQEP0_ERR] Bits */
#define XBAR_XBARCLR2_EQEP0_ERR_OFS              (12)                            /* !< EQEP0_ERR Offset */
#define XBAR_XBARCLR2_EQEP0_ERR_MASK             ((uint32_t)0x00001000U)         /* !< Input Flag Clear for EQEP0_ERR
                                                                                    Signal */
/* XBAR_XBARCLR2[EQEP1_ERR] Bits */
#define XBAR_XBARCLR2_EQEP1_ERR_OFS              (13)                            /* !< EQEP1_ERR Offset */
#define XBAR_XBARCLR2_EQEP1_ERR_MASK             ((uint32_t)0x00002000U)         /* !< Input Flag Clear for EQEP1_ERR
                                                                                    Signal */
/* XBAR_XBARCLR2[EQEP2_ERR] Bits */
#define XBAR_XBARCLR2_EQEP2_ERR_OFS              (14)                            /* !< EQEP2_ERR Offset */
#define XBAR_XBARCLR2_EQEP2_ERR_MASK             ((uint32_t)0x00004000U)         /* !< Input Flag Clear for EQEP2_ERR
                                                                                    Signal */
/* XBAR_XBARCLR2[EQEP0_INDEX_SYNCOUT] Bits */
#define XBAR_XBARCLR2_EQEP0_INDEX_SYNCOUT_OFS    (15)                            /* !< EQEP0_INDEX_SYNCOUT Offset */
#define XBAR_XBARCLR2_EQEP0_INDEX_SYNCOUT_MASK   ((uint32_t)0x00008000U)         /* !< Input Flag Clear for
                                                                                    EQEP0_INDEX_SYNCOUT Signal */
/* XBAR_XBARCLR2[EQEP0_STROBE_SYNCOUT] Bits */
#define XBAR_XBARCLR2_EQEP0_STROBE_SYNCOUT_OFS   (16)                            /* !< EQEP0_STROBE_SYNCOUT Offset */
#define XBAR_XBARCLR2_EQEP0_STROBE_SYNCOUT_MASK  ((uint32_t)0x00010000U)         /* !< Input Flag Clear for
                                                                                    EQEP0_STROBE_SYNCOUT Signal */
/* XBAR_XBARCLR2[EQEP1_INDEX_SYNCOUT] Bits */
#define XBAR_XBARCLR2_EQEP1_INDEX_SYNCOUT_OFS    (17)                            /* !< EQEP1_INDEX_SYNCOUT Offset */
#define XBAR_XBARCLR2_EQEP1_INDEX_SYNCOUT_MASK   ((uint32_t)0x00020000U)         /* !< Input Flag Clear for
                                                                                    EQEP1_INDEX_SYNCOUT Signal */
/* XBAR_XBARCLR2[EQEP1_STROBE_SYNCOUT] Bits */
#define XBAR_XBARCLR2_EQEP1_STROBE_SYNCOUT_OFS   (18)                            /* !< EQEP1_STROBE_SYNCOUT Offset */
#define XBAR_XBARCLR2_EQEP1_STROBE_SYNCOUT_MASK  ((uint32_t)0x00040000U)         /* !< Input Flag Clear for
                                                                                    EQEP1_STROBE_SYNCOUT Signal */
/* XBAR_XBARCLR2[EQEP2_INDEX_SYNCOUT] Bits */
#define XBAR_XBARCLR2_EQEP2_INDEX_SYNCOUT_OFS    (19)                            /* !< EQEP2_INDEX_SYNCOUT Offset */
#define XBAR_XBARCLR2_EQEP2_INDEX_SYNCOUT_MASK   ((uint32_t)0x00080000U)         /* !< Input Flag Clear for
                                                                                    EQEP2_INDEX_SYNCOUT Signal */
/* XBAR_XBARCLR2[EQEP2_STROBE_SYNCOUT] Bits */
#define XBAR_XBARCLR2_EQEP2_STROBE_SYNCOUT_OFS   (20)                            /* !< EQEP2_STROBE_SYNCOUT Offset */
#define XBAR_XBARCLR2_EQEP2_STROBE_SYNCOUT_MASK  ((uint32_t)0x00100000U)         /* !< Input Flag Clear for
                                                                                    EQEP2_STROBE_SYNCOUT Signal */
/* XBAR_XBARCLR2[CMPSS0_CTRIPOUTH] Bits */
#define XBAR_XBARCLR2_CMPSS0_CTRIPOUTH_OFS       (21)                            /* !< CMPSS0_CTRIPOUTH Offset */
#define XBAR_XBARCLR2_CMPSS0_CTRIPOUTH_MASK      ((uint32_t)0x00200000U)         /* !< Input Flag Clear for
                                                                                    CMPSS0_CTRIPOUTH Signal */
/* XBAR_XBARCLR2[CMPSS0_CTRIPOUTL] Bits */
#define XBAR_XBARCLR2_CMPSS0_CTRIPOUTL_OFS       (22)                            /* !< CMPSS0_CTRIPOUTL Offset */
#define XBAR_XBARCLR2_CMPSS0_CTRIPOUTL_MASK      ((uint32_t)0x00400000U)         /* !< Input Flag Clear for
                                                                                    CMPSS0_CTRIPOUTL Signal */
/* XBAR_XBARCLR2[CMPSS1_CTRIPOUTH] Bits */
#define XBAR_XBARCLR2_CMPSS1_CTRIPOUTH_OFS       (23)                            /* !< CMPSS1_CTRIPOUTH Offset */
#define XBAR_XBARCLR2_CMPSS1_CTRIPOUTH_MASK      ((uint32_t)0x00800000U)         /* !< Input Flag Clear for
                                                                                    CMPSS1_CTRIPOUTH Signal */
/* XBAR_XBARCLR2[CMPSS1_CTRIPOUTL] Bits */
#define XBAR_XBARCLR2_CMPSS1_CTRIPOUTL_OFS       (24)                            /* !< CMPSS1_CTRIPOUTL Offset */
#define XBAR_XBARCLR2_CMPSS1_CTRIPOUTL_MASK      ((uint32_t)0x01000000U)         /* !< Input Flag Clear for
                                                                                    CMPSS1_CTRIPOUTL Signal */
/* XBAR_XBARCLR2[CMPSS2_CTRIPOUTH] Bits */
#define XBAR_XBARCLR2_CMPSS2_CTRIPOUTH_OFS       (25)                            /* !< CMPSS2_CTRIPOUTH Offset */
#define XBAR_XBARCLR2_CMPSS2_CTRIPOUTH_MASK      ((uint32_t)0x02000000U)         /* !< Input Flag Clear for
                                                                                    CMPSS2_CTRIPOUTH Signal */
/* XBAR_XBARCLR2[CMPSS2_CTRIPOUTL] Bits */
#define XBAR_XBARCLR2_CMPSS2_CTRIPOUTL_OFS       (26)                            /* !< CMPSS2_CTRIPOUTL Offset */
#define XBAR_XBARCLR2_CMPSS2_CTRIPOUTL_MASK      ((uint32_t)0x04000000U)         /* !< Input Flag Clear for
                                                                                    CMPSS2_CTRIPOUTL Signal */
/* XBAR_XBARCLR2[CMPSS3_CTRIPOUTH] Bits */
#define XBAR_XBARCLR2_CMPSS3_CTRIPOUTH_OFS       (27)                            /* !< CMPSS3_CTRIPOUTH Offset */
#define XBAR_XBARCLR2_CMPSS3_CTRIPOUTH_MASK      ((uint32_t)0x08000000U)         /* !< Input Flag Clear for
                                                                                    CMPSS3_CTRIPOUTH Signal */
/* XBAR_XBARCLR2[CMPSS3_CTRIPOUTL] Bits */
#define XBAR_XBARCLR2_CMPSS3_CTRIPOUTL_OFS       (28)                            /* !< CMPSS3_CTRIPOUTL Offset */
#define XBAR_XBARCLR2_CMPSS3_CTRIPOUTL_MASK      ((uint32_t)0x10000000U)         /* !< Input Flag Clear for
                                                                                    CMPSS3_CTRIPOUTL Signal */
/* XBAR_XBARCLR2[CPU_HALTED] Bits */
#define XBAR_XBARCLR2_CPU_HALTED_OFS             (29)                            /* !< CPU_HALTED Offset */
#define XBAR_XBARCLR2_CPU_HALTED_MASK            ((uint32_t)0x20000000U)         /* !< Input Flag Clear for CPU_HALTED
                                                                                    Signal */

/* XBAR_PWMXBARG0SEL Bits */
/* XBAR_PWMXBARG0SEL[INPUT0] Bits */
#define XBAR_PWMXBARG0SEL_INPUT0_OFS             (0)                             /* !< INPUT0 Offset */
#define XBAR_PWMXBARG0SEL_INPUT0_MASK            ((uint32_t)0x00000001U)         /* !< Select bit for INPUT0 */
/* XBAR_PWMXBARG0SEL[INPUT1] Bits */
#define XBAR_PWMXBARG0SEL_INPUT1_OFS             (1)                             /* !< INPUT1 Offset */
#define XBAR_PWMXBARG0SEL_INPUT1_MASK            ((uint32_t)0x00000002U)         /* !< Select bit for INPUT1 */
/* XBAR_PWMXBARG0SEL[INPUT2] Bits */
#define XBAR_PWMXBARG0SEL_INPUT2_OFS             (2)                             /* !< INPUT2 Offset */
#define XBAR_PWMXBARG0SEL_INPUT2_MASK            ((uint32_t)0x00000004U)         /* !< Select bit for INPUT2 */
/* XBAR_PWMXBARG0SEL[INPUT3] Bits */
#define XBAR_PWMXBARG0SEL_INPUT3_OFS             (3)                             /* !< INPUT3 Offset */
#define XBAR_PWMXBARG0SEL_INPUT3_MASK            ((uint32_t)0x00000008U)         /* !< Select bit for INPUT3 */
/* XBAR_PWMXBARG0SEL[INPUT4] Bits */
#define XBAR_PWMXBARG0SEL_INPUT4_OFS             (4)                             /* !< INPUT4 Offset */
#define XBAR_PWMXBARG0SEL_INPUT4_MASK            ((uint32_t)0x00000010U)         /* !< Select bit for INPUT4 */
/* XBAR_PWMXBARG0SEL[INPUT5] Bits */
#define XBAR_PWMXBARG0SEL_INPUT5_OFS             (5)                             /* !< INPUT5 Offset */
#define XBAR_PWMXBARG0SEL_INPUT5_MASK            ((uint32_t)0x00000020U)         /* !< Select bit for INPUT5 */
/* XBAR_PWMXBARG0SEL[INPUT6] Bits */
#define XBAR_PWMXBARG0SEL_INPUT6_OFS             (6)                             /* !< INPUT6 Offset */
#define XBAR_PWMXBARG0SEL_INPUT6_MASK            ((uint32_t)0x00000040U)         /* !< Select bit for INPUT6 */
/* XBAR_PWMXBARG0SEL[INPUT7] Bits */
#define XBAR_PWMXBARG0SEL_INPUT7_OFS             (7)                             /* !< INPUT7 Offset */
#define XBAR_PWMXBARG0SEL_INPUT7_MASK            ((uint32_t)0x00000080U)         /* !< Select bit for INPUT7 */
/* XBAR_PWMXBARG0SEL[INPUT8] Bits */
#define XBAR_PWMXBARG0SEL_INPUT8_OFS             (8)                             /* !< INPUT8 Offset */
#define XBAR_PWMXBARG0SEL_INPUT8_MASK            ((uint32_t)0x00000100U)         /* !< Select bit for INPUT8 */
/* XBAR_PWMXBARG0SEL[INPUT9] Bits */
#define XBAR_PWMXBARG0SEL_INPUT9_OFS             (9)                             /* !< INPUT9 Offset */
#define XBAR_PWMXBARG0SEL_INPUT9_MASK            ((uint32_t)0x00000200U)         /* !< Select bit for INPUT9 */
/* XBAR_PWMXBARG0SEL[INPUT10] Bits */
#define XBAR_PWMXBARG0SEL_INPUT10_OFS            (10)                            /* !< INPUT10 Offset */
#define XBAR_PWMXBARG0SEL_INPUT10_MASK           ((uint32_t)0x00000400U)         /* !< Select bit for INPUT10 */
/* XBAR_PWMXBARG0SEL[INPUT11] Bits */
#define XBAR_PWMXBARG0SEL_INPUT11_OFS            (11)                            /* !< INPUT11 Offset */
#define XBAR_PWMXBARG0SEL_INPUT11_MASK           ((uint32_t)0x00000800U)         /* !< Select bit for INPUT11 */
/* XBAR_PWMXBARG0SEL[INPUT12] Bits */
#define XBAR_PWMXBARG0SEL_INPUT12_OFS            (12)                            /* !< INPUT12 Offset */
#define XBAR_PWMXBARG0SEL_INPUT12_MASK           ((uint32_t)0x00001000U)         /* !< Select bit for INPUT12 */
/* XBAR_PWMXBARG0SEL[INPUT13] Bits */
#define XBAR_PWMXBARG0SEL_INPUT13_OFS            (13)                            /* !< INPUT13 Offset */
#define XBAR_PWMXBARG0SEL_INPUT13_MASK           ((uint32_t)0x00002000U)         /* !< Select bit for INPUT13 */
/* XBAR_PWMXBARG0SEL[INPUT14] Bits */
#define XBAR_PWMXBARG0SEL_INPUT14_OFS            (14)                            /* !< INPUT14 Offset */
#define XBAR_PWMXBARG0SEL_INPUT14_MASK           ((uint32_t)0x00004000U)         /* !< Select bit for INPUT14 */
/* XBAR_PWMXBARG0SEL[INPUT15] Bits */
#define XBAR_PWMXBARG0SEL_INPUT15_OFS            (15)                            /* !< INPUT15 Offset */
#define XBAR_PWMXBARG0SEL_INPUT15_MASK           ((uint32_t)0x00008000U)         /* !< Select bit for INPUT15 */
/* XBAR_PWMXBARG0SEL[INPUT16] Bits */
#define XBAR_PWMXBARG0SEL_INPUT16_OFS            (16)                            /* !< INPUT16 Offset */
#define XBAR_PWMXBARG0SEL_INPUT16_MASK           ((uint32_t)0x00010000U)         /* !< Select bit for INPUT16 */
/* XBAR_PWMXBARG0SEL[INPUT17] Bits */
#define XBAR_PWMXBARG0SEL_INPUT17_OFS            (17)                            /* !< INPUT17 Offset */
#define XBAR_PWMXBARG0SEL_INPUT17_MASK           ((uint32_t)0x00020000U)         /* !< Select bit for INPUT17 */
/* XBAR_PWMXBARG0SEL[INPUT18] Bits */
#define XBAR_PWMXBARG0SEL_INPUT18_OFS            (18)                            /* !< INPUT18 Offset */
#define XBAR_PWMXBARG0SEL_INPUT18_MASK           ((uint32_t)0x00040000U)         /* !< Select bit for INPUT18 */
/* XBAR_PWMXBARG0SEL[INPUT19] Bits */
#define XBAR_PWMXBARG0SEL_INPUT19_OFS            (19)                            /* !< INPUT19 Offset */
#define XBAR_PWMXBARG0SEL_INPUT19_MASK           ((uint32_t)0x00080000U)         /* !< Select bit for INPUT19 */
/* XBAR_PWMXBARG0SEL[INPUT20] Bits */
#define XBAR_PWMXBARG0SEL_INPUT20_OFS            (20)                            /* !< INPUT20 Offset */
#define XBAR_PWMXBARG0SEL_INPUT20_MASK           ((uint32_t)0x00100000U)         /* !< Select bit for INPUT20 */
/* XBAR_PWMXBARG0SEL[INPUT21] Bits */
#define XBAR_PWMXBARG0SEL_INPUT21_OFS            (21)                            /* !< INPUT21 Offset */
#define XBAR_PWMXBARG0SEL_INPUT21_MASK           ((uint32_t)0x00200000U)         /* !< Select bit for INPUT21 */
/* XBAR_PWMXBARG0SEL[INPUT22] Bits */
#define XBAR_PWMXBARG0SEL_INPUT22_OFS            (22)                            /* !< INPUT22 Offset */
#define XBAR_PWMXBARG0SEL_INPUT22_MASK           ((uint32_t)0x00400000U)         /* !< Select bit for INPUT22 */
/* XBAR_PWMXBARG0SEL[INPUT23] Bits */
#define XBAR_PWMXBARG0SEL_INPUT23_OFS            (23)                            /* !< INPUT23 Offset */
#define XBAR_PWMXBARG0SEL_INPUT23_MASK           ((uint32_t)0x00800000U)         /* !< Select bit for INPUT23 */
/* XBAR_PWMXBARG0SEL[INPUT24] Bits */
#define XBAR_PWMXBARG0SEL_INPUT24_OFS            (24)                            /* !< INPUT24 Offset */
#define XBAR_PWMXBARG0SEL_INPUT24_MASK           ((uint32_t)0x01000000U)         /* !< Select bit for INPUT24 */
/* XBAR_PWMXBARG0SEL[INPUT25] Bits */
#define XBAR_PWMXBARG0SEL_INPUT25_OFS            (25)                            /* !< INPUT25 Offset */
#define XBAR_PWMXBARG0SEL_INPUT25_MASK           ((uint32_t)0x02000000U)         /* !< Select bit for INPUT25 */
/* XBAR_PWMXBARG0SEL[INPUT26] Bits */
#define XBAR_PWMXBARG0SEL_INPUT26_OFS            (26)                            /* !< INPUT26 Offset */
#define XBAR_PWMXBARG0SEL_INPUT26_MASK           ((uint32_t)0x04000000U)         /* !< Select bit for INPUT26 */
/* XBAR_PWMXBARG0SEL[INPUT27] Bits */
#define XBAR_PWMXBARG0SEL_INPUT27_OFS            (27)                            /* !< INPUT27 Offset */
#define XBAR_PWMXBARG0SEL_INPUT27_MASK           ((uint32_t)0x08000000U)         /* !< Select bit for INPUT27 */
/* XBAR_PWMXBARG0SEL[INPUT28] Bits */
#define XBAR_PWMXBARG0SEL_INPUT28_OFS            (28)                            /* !< INPUT28 Offset */
#define XBAR_PWMXBARG0SEL_INPUT28_MASK           ((uint32_t)0x10000000U)         /* !< Select bit for INPUT28 */
/* XBAR_PWMXBARG0SEL[INPUT29] Bits */
#define XBAR_PWMXBARG0SEL_INPUT29_OFS            (29)                            /* !< INPUT29 Offset */
#define XBAR_PWMXBARG0SEL_INPUT29_MASK           ((uint32_t)0x20000000U)         /* !< Select bit for INPUT29 */
/* XBAR_PWMXBARG0SEL[INPUT30] Bits */
#define XBAR_PWMXBARG0SEL_INPUT30_OFS            (30)                            /* !< INPUT30 Offset */
#define XBAR_PWMXBARG0SEL_INPUT30_MASK           ((uint32_t)0x40000000U)         /* !< Select bit for INPUT30 */
/* XBAR_PWMXBARG0SEL[INPUT31] Bits */
#define XBAR_PWMXBARG0SEL_INPUT31_OFS            (31)                            /* !< INPUT31 Offset */
#define XBAR_PWMXBARG0SEL_INPUT31_MASK           ((uint32_t)0x80000000U)         /* !< Select bit for INPUT31 */

/* XBAR_PWMXBARG1SEL Bits */
/* XBAR_PWMXBARG1SEL[INPUT0] Bits */
#define XBAR_PWMXBARG1SEL_INPUT0_OFS             (0)                             /* !< INPUT0 Offset */
#define XBAR_PWMXBARG1SEL_INPUT0_MASK            ((uint32_t)0x00000001U)         /* !< Select bit for INPUT0 */
/* XBAR_PWMXBARG1SEL[INPUT1] Bits */
#define XBAR_PWMXBARG1SEL_INPUT1_OFS             (1)                             /* !< INPUT1 Offset */
#define XBAR_PWMXBARG1SEL_INPUT1_MASK            ((uint32_t)0x00000002U)         /* !< Select bit for INPUT1 */
/* XBAR_PWMXBARG1SEL[INPUT2] Bits */
#define XBAR_PWMXBARG1SEL_INPUT2_OFS             (2)                             /* !< INPUT2 Offset */
#define XBAR_PWMXBARG1SEL_INPUT2_MASK            ((uint32_t)0x00000004U)         /* !< Select bit for INPUT2 */
/* XBAR_PWMXBARG1SEL[INPUT3] Bits */
#define XBAR_PWMXBARG1SEL_INPUT3_OFS             (3)                             /* !< INPUT3 Offset */
#define XBAR_PWMXBARG1SEL_INPUT3_MASK            ((uint32_t)0x00000008U)         /* !< Select bit for INPUT3 */
/* XBAR_PWMXBARG1SEL[INPUT4] Bits */
#define XBAR_PWMXBARG1SEL_INPUT4_OFS             (4)                             /* !< INPUT4 Offset */
#define XBAR_PWMXBARG1SEL_INPUT4_MASK            ((uint32_t)0x00000010U)         /* !< Select bit for INPUT4 */
/* XBAR_PWMXBARG1SEL[INPUT5] Bits */
#define XBAR_PWMXBARG1SEL_INPUT5_OFS             (5)                             /* !< INPUT5 Offset */
#define XBAR_PWMXBARG1SEL_INPUT5_MASK            ((uint32_t)0x00000020U)         /* !< Select bit for INPUT5 */
/* XBAR_PWMXBARG1SEL[INPUT6] Bits */
#define XBAR_PWMXBARG1SEL_INPUT6_OFS             (6)                             /* !< INPUT6 Offset */
#define XBAR_PWMXBARG1SEL_INPUT6_MASK            ((uint32_t)0x00000040U)         /* !< Select bit for INPUT6 */
/* XBAR_PWMXBARG1SEL[INPUT7] Bits */
#define XBAR_PWMXBARG1SEL_INPUT7_OFS             (7)                             /* !< INPUT7 Offset */
#define XBAR_PWMXBARG1SEL_INPUT7_MASK            ((uint32_t)0x00000080U)         /* !< Select bit for INPUT7 */
/* XBAR_PWMXBARG1SEL[INPUT8] Bits */
#define XBAR_PWMXBARG1SEL_INPUT8_OFS             (8)                             /* !< INPUT8 Offset */
#define XBAR_PWMXBARG1SEL_INPUT8_MASK            ((uint32_t)0x00000100U)         /* !< Select bit for INPUT8 */
/* XBAR_PWMXBARG1SEL[INPUT9] Bits */
#define XBAR_PWMXBARG1SEL_INPUT9_OFS             (9)                             /* !< INPUT9 Offset */
#define XBAR_PWMXBARG1SEL_INPUT9_MASK            ((uint32_t)0x00000200U)         /* !< Select bit for INPUT9 */
/* XBAR_PWMXBARG1SEL[INPUT10] Bits */
#define XBAR_PWMXBARG1SEL_INPUT10_OFS            (10)                            /* !< INPUT10 Offset */
#define XBAR_PWMXBARG1SEL_INPUT10_MASK           ((uint32_t)0x00000400U)         /* !< Select bit for INPUT10 */
/* XBAR_PWMXBARG1SEL[INPUT11] Bits */
#define XBAR_PWMXBARG1SEL_INPUT11_OFS            (11)                            /* !< INPUT11 Offset */
#define XBAR_PWMXBARG1SEL_INPUT11_MASK           ((uint32_t)0x00000800U)         /* !< Select bit for INPUT11 */
/* XBAR_PWMXBARG1SEL[INPUT12] Bits */
#define XBAR_PWMXBARG1SEL_INPUT12_OFS            (12)                            /* !< INPUT12 Offset */
#define XBAR_PWMXBARG1SEL_INPUT12_MASK           ((uint32_t)0x00001000U)         /* !< Select bit for INPUT12 */
/* XBAR_PWMXBARG1SEL[INPUT13] Bits */
#define XBAR_PWMXBARG1SEL_INPUT13_OFS            (13)                            /* !< INPUT13 Offset */
#define XBAR_PWMXBARG1SEL_INPUT13_MASK           ((uint32_t)0x00002000U)         /* !< Select bit for INPUT13 */
/* XBAR_PWMXBARG1SEL[INPUT14] Bits */
#define XBAR_PWMXBARG1SEL_INPUT14_OFS            (14)                            /* !< INPUT14 Offset */
#define XBAR_PWMXBARG1SEL_INPUT14_MASK           ((uint32_t)0x00004000U)         /* !< Select bit for INPUT14 */
/* XBAR_PWMXBARG1SEL[INPUT15] Bits */
#define XBAR_PWMXBARG1SEL_INPUT15_OFS            (15)                            /* !< INPUT15 Offset */
#define XBAR_PWMXBARG1SEL_INPUT15_MASK           ((uint32_t)0x00008000U)         /* !< Select bit for INPUT15 */
/* XBAR_PWMXBARG1SEL[INPUT16] Bits */
#define XBAR_PWMXBARG1SEL_INPUT16_OFS            (16)                            /* !< INPUT16 Offset */
#define XBAR_PWMXBARG1SEL_INPUT16_MASK           ((uint32_t)0x00010000U)         /* !< Select bit for INPUT16 */
/* XBAR_PWMXBARG1SEL[INPUT17] Bits */
#define XBAR_PWMXBARG1SEL_INPUT17_OFS            (17)                            /* !< INPUT17 Offset */
#define XBAR_PWMXBARG1SEL_INPUT17_MASK           ((uint32_t)0x00020000U)         /* !< Select bit for INPUT17 */
/* XBAR_PWMXBARG1SEL[INPUT18] Bits */
#define XBAR_PWMXBARG1SEL_INPUT18_OFS            (18)                            /* !< INPUT18 Offset */
#define XBAR_PWMXBARG1SEL_INPUT18_MASK           ((uint32_t)0x00040000U)         /* !< Select bit for INPUT18 */
/* XBAR_PWMXBARG1SEL[INPUT19] Bits */
#define XBAR_PWMXBARG1SEL_INPUT19_OFS            (19)                            /* !< INPUT19 Offset */
#define XBAR_PWMXBARG1SEL_INPUT19_MASK           ((uint32_t)0x00080000U)         /* !< Select bit for INPUT19 */
/* XBAR_PWMXBARG1SEL[INPUT20] Bits */
#define XBAR_PWMXBARG1SEL_INPUT20_OFS            (20)                            /* !< INPUT20 Offset */
#define XBAR_PWMXBARG1SEL_INPUT20_MASK           ((uint32_t)0x00100000U)         /* !< Select bit for INPUT20 */
/* XBAR_PWMXBARG1SEL[INPUT21] Bits */
#define XBAR_PWMXBARG1SEL_INPUT21_OFS            (21)                            /* !< INPUT21 Offset */
#define XBAR_PWMXBARG1SEL_INPUT21_MASK           ((uint32_t)0x00200000U)         /* !< Select bit for INPUT21 */
/* XBAR_PWMXBARG1SEL[INPUT22] Bits */
#define XBAR_PWMXBARG1SEL_INPUT22_OFS            (22)                            /* !< INPUT22 Offset */
#define XBAR_PWMXBARG1SEL_INPUT22_MASK           ((uint32_t)0x00400000U)         /* !< Select bit for INPUT22 */
/* XBAR_PWMXBARG1SEL[INPUT23] Bits */
#define XBAR_PWMXBARG1SEL_INPUT23_OFS            (23)                            /* !< INPUT23 Offset */
#define XBAR_PWMXBARG1SEL_INPUT23_MASK           ((uint32_t)0x00800000U)         /* !< Select bit for INPUT23 */
/* XBAR_PWMXBARG1SEL[INPUT24] Bits */
#define XBAR_PWMXBARG1SEL_INPUT24_OFS            (24)                            /* !< INPUT24 Offset */
#define XBAR_PWMXBARG1SEL_INPUT24_MASK           ((uint32_t)0x01000000U)         /* !< Select bit for INPUT24 */
/* XBAR_PWMXBARG1SEL[INPUT25] Bits */
#define XBAR_PWMXBARG1SEL_INPUT25_OFS            (25)                            /* !< INPUT25 Offset */
#define XBAR_PWMXBARG1SEL_INPUT25_MASK           ((uint32_t)0x02000000U)         /* !< Select bit for INPUT25 */
/* XBAR_PWMXBARG1SEL[INPUT26] Bits */
#define XBAR_PWMXBARG1SEL_INPUT26_OFS            (26)                            /* !< INPUT26 Offset */
#define XBAR_PWMXBARG1SEL_INPUT26_MASK           ((uint32_t)0x04000000U)         /* !< Select bit for INPUT26 */
/* XBAR_PWMXBARG1SEL[INPUT27] Bits */
#define XBAR_PWMXBARG1SEL_INPUT27_OFS            (27)                            /* !< INPUT27 Offset */
#define XBAR_PWMXBARG1SEL_INPUT27_MASK           ((uint32_t)0x08000000U)         /* !< Select bit for INPUT27 */
/* XBAR_PWMXBARG1SEL[INPUT28] Bits */
#define XBAR_PWMXBARG1SEL_INPUT28_OFS            (28)                            /* !< INPUT28 Offset */
#define XBAR_PWMXBARG1SEL_INPUT28_MASK           ((uint32_t)0x10000000U)         /* !< Select bit for INPUT28 */
/* XBAR_PWMXBARG1SEL[INPUT29] Bits */
#define XBAR_PWMXBARG1SEL_INPUT29_OFS            (29)                            /* !< INPUT29 Offset */
#define XBAR_PWMXBARG1SEL_INPUT29_MASK           ((uint32_t)0x20000000U)         /* !< Select bit for INPUT29 */
/* XBAR_PWMXBARG1SEL[INPUT30] Bits */
#define XBAR_PWMXBARG1SEL_INPUT30_OFS            (30)                            /* !< INPUT30 Offset */
#define XBAR_PWMXBARG1SEL_INPUT30_MASK           ((uint32_t)0x40000000U)         /* !< Select bit for INPUT30 */
/* XBAR_PWMXBARG1SEL[INPUT31] Bits */
#define XBAR_PWMXBARG1SEL_INPUT31_OFS            (31)                            /* !< INPUT31 Offset */
#define XBAR_PWMXBARG1SEL_INPUT31_MASK           ((uint32_t)0x80000000U)         /* !< Select bit for INPUT31 */

/* XBAR_PWMXBAROUTINVERT Bits */
/* XBAR_PWMXBAROUTINVERT[XBAR1] Bits */
#define XBAR_PWMXBAROUTINVERT_XBAR1_OFS          (0)                             /* !< XBAR1 Offset */
#define XBAR_PWMXBAROUTINVERT_XBAR1_MASK         ((uint32_t)0x00000001U)         /* !< Invert XBAR Output Select for XBAR1 */
/* XBAR_PWMXBAROUTINVERT[XBAR2] Bits */
#define XBAR_PWMXBAROUTINVERT_XBAR2_OFS          (1)                             /* !< XBAR2 Offset */
#define XBAR_PWMXBAROUTINVERT_XBAR2_MASK         ((uint32_t)0x00000002U)         /* !< Invert XBAR Output Select for XBAR2 */
/* XBAR_PWMXBAROUTINVERT[XBAR3] Bits */
#define XBAR_PWMXBAROUTINVERT_XBAR3_OFS          (2)                             /* !< XBAR3 Offset */
#define XBAR_PWMXBAROUTINVERT_XBAR3_MASK         ((uint32_t)0x00000004U)         /* !< Invert XBAR Output Select for XBAR3 */
/* XBAR_PWMXBAROUTINVERT[XBAR4] Bits */
#define XBAR_PWMXBAROUTINVERT_XBAR4_OFS          (3)                             /* !< XBAR4 Offset */
#define XBAR_PWMXBAROUTINVERT_XBAR4_MASK         ((uint32_t)0x00000008U)         /* !< Invert XBAR Output Select for XBAR4 */
/* XBAR_PWMXBAROUTINVERT[XBAR5] Bits */
#define XBAR_PWMXBAROUTINVERT_XBAR5_OFS          (4)                             /* !< XBAR5 Offset */
#define XBAR_PWMXBAROUTINVERT_XBAR5_MASK         ((uint32_t)0x00000010U)         /* !< Invert XBAR Output Select for XBAR5 */
/* XBAR_PWMXBAROUTINVERT[XBAR6] Bits */
#define XBAR_PWMXBAROUTINVERT_XBAR6_OFS          (5)                             /* !< XBAR6 Offset */
#define XBAR_PWMXBAROUTINVERT_XBAR6_MASK         ((uint32_t)0x00000020U)         /* !< Invert XBAR Output Select for XBAR6 */
/* XBAR_PWMXBAROUTINVERT[XBAR7] Bits */
#define XBAR_PWMXBAROUTINVERT_XBAR7_OFS          (6)                             /* !< XBAR7 Offset */
#define XBAR_PWMXBAROUTINVERT_XBAR7_MASK         ((uint32_t)0x00000040U)         /* !< Invert XBAR Output Select for XBAR7 */
/* XBAR_PWMXBAROUTINVERT[XBAR8] Bits */
#define XBAR_PWMXBAROUTINVERT_XBAR8_OFS          (7)                             /* !< XBAR8 Offset */
#define XBAR_PWMXBAROUTINVERT_XBAR8_MASK         ((uint32_t)0x00000080U)         /* !< Invert XBAR Output Select for XBAR8 */

/* XBAR_PWMXBARLOCK Bits */
/* XBAR_PWMXBARLOCK[LOCK] Bits */
#define XBAR_PWMXBARLOCK_LOCK_OFS                (0)                             /* !< LOCK Offset */
#define XBAR_PWMXBARLOCK_LOCK_MASK               ((uint32_t)0x00000001U)         /* !< Locks the configuration for
                                                                                    EPWM-XBAR */
/* XBAR_PWMXBARLOCK[KEY] Bits */
#define XBAR_PWMXBARLOCK_KEY_OFS                 (16)                            /* !< KEY Offset */
#define XBAR_PWMXBARLOCK_KEY_MASK                ((uint32_t)0xFFFF0000U)         /* !< Write protection KEY */

/* XBAR_SYNCSELECT Bits */
/* XBAR_SYNCSELECT[SYNCOUT] Bits */
#define XBAR_SYNCSELECT_SYNCOUT_OFS              (24)                            /* !< SYNCOUT Offset */
#define XBAR_SYNCSELECT_SYNCOUT_MASK             ((uint32_t)0x1F000000U)         /* !< Select EXT Syncout Source */

/* XBAR_ADCSOCOUTSELECT Bits */
/* XBAR_ADCSOCOUTSELECT[PWM0SOCAEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM0SOCAEN_OFS      (0)                             /* !< PWM0SOCAEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM0SOCAEN_MASK     ((uint32_t)0x00000001U)         /* !< PWM0SOCAEN Enable for ADCSOCAOn */
/* XBAR_ADCSOCOUTSELECT[PWM1SOCAEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM1SOCAEN_OFS      (1)                             /* !< PWM1SOCAEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM1SOCAEN_MASK     ((uint32_t)0x00000002U)         /* !< PWM1SOCAEN Enable for ADCSOCAOn */
/* XBAR_ADCSOCOUTSELECT[PWM2SOCAEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM2SOCAEN_OFS      (2)                             /* !< PWM2SOCAEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM2SOCAEN_MASK     ((uint32_t)0x00000004U)         /* !< PWM2SOCAEN Enable for ADCSOCAOn */
/* XBAR_ADCSOCOUTSELECT[PWM3SOCAEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM3SOCAEN_OFS      (3)                             /* !< PWM3SOCAEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM3SOCAEN_MASK     ((uint32_t)0x00000008U)         /* !< PWM3SOCAEN Enable for ADCSOCAOn */
/* XBAR_ADCSOCOUTSELECT[PWM4SOCAEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM4SOCAEN_OFS      (4)                             /* !< PWM4SOCAEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM4SOCAEN_MASK     ((uint32_t)0x00000010U)         /* !< PWM4SOCAEN Enable for ADCSOCAOn */
/* XBAR_ADCSOCOUTSELECT[PWM0SOCBEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM0SOCBEN_OFS      (16)                            /* !< PWM0SOCBEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM0SOCBEN_MASK     ((uint32_t)0x00010000U)         /* !< PWM0SOCBEN Enable for ADCSOCBOn */
/* XBAR_ADCSOCOUTSELECT[PWM1SOCBEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM1SOCBEN_OFS      (17)                            /* !< PWM1SOCBEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM1SOCBEN_MASK     ((uint32_t)0x00020000U)         /* !< PWM1SOCBEN Enable for ADCSOCBOn */
/* XBAR_ADCSOCOUTSELECT[PWM2SOCBEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM2SOCBEN_OFS      (18)                            /* !< PWM2SOCBEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM2SOCBEN_MASK     ((uint32_t)0x00040000U)         /* !< PWM2SOCBEN Enable for ADCSOCBOn */
/* XBAR_ADCSOCOUTSELECT[PWM3SOCBEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM3SOCBEN_OFS      (19)                            /* !< PWM3SOCBEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM3SOCBEN_MASK     ((uint32_t)0x00080000U)         /* !< PWM3SOCBEN Enable for ADCSOCBOn */
/* XBAR_ADCSOCOUTSELECT[PWM4SOCBEN] Bits */
#define XBAR_ADCSOCOUTSELECT_PWM4SOCBEN_OFS      (20)                            /* !< PWM4SOCBEN Offset */
#define XBAR_ADCSOCOUTSELECT_PWM4SOCBEN_MASK     ((uint32_t)0x00100000U)         /* !< PWM4SOCBEN Enable for ADCSOCBOn */

/* XBAR_SYNCSOCLOCK Bits */
/* XBAR_SYNCSOCLOCK[SYNCSELECT] Bits */
#define XBAR_SYNCSOCLOCK_SYNCSELECT_OFS          (0)                             /* !< SYNCSELECT Offset */
#define XBAR_SYNCSOCLOCK_SYNCSELECT_MASK         ((uint32_t)0x00000001U)         /* !< SYNCSEL Register Lock bit */
/* XBAR_SYNCSOCLOCK[ADCSOCOUTSELECT] Bits */
#define XBAR_SYNCSOCLOCK_ADCSOCOUTSELECT_OFS     (1)                             /* !< ADCSOCOUTSELECT Offset */
#define XBAR_SYNCSOCLOCK_ADCSOCOUTSELECT_MASK    ((uint32_t)0x00000002U)         /* !< ADCSOCOUTSELECT Register Lock bit */

/* XBAR_OUTPUTXBARG0SEL Bits */
/* XBAR_OUTPUTXBARG0SEL[INPUT0] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT0_OFS          (0)                             /* !< INPUT0 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT0_MASK         ((uint32_t)0x00000001U)         /* !< Select bit for INPUT0 */
/* XBAR_OUTPUTXBARG0SEL[INPUT1] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT1_OFS          (1)                             /* !< INPUT1 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT1_MASK         ((uint32_t)0x00000002U)         /* !< Select bit for INPUT1 */
/* XBAR_OUTPUTXBARG0SEL[INPUT2] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT2_OFS          (2)                             /* !< INPUT2 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT2_MASK         ((uint32_t)0x00000004U)         /* !< Select bit for INPUT2 */
/* XBAR_OUTPUTXBARG0SEL[INPUT3] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT3_OFS          (3)                             /* !< INPUT3 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT3_MASK         ((uint32_t)0x00000008U)         /* !< Select bit for INPUT3 */
/* XBAR_OUTPUTXBARG0SEL[INPUT4] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT4_OFS          (4)                             /* !< INPUT4 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT4_MASK         ((uint32_t)0x00000010U)         /* !< Select bit for INPUT4 */
/* XBAR_OUTPUTXBARG0SEL[INPUT5] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT5_OFS          (5)                             /* !< INPUT5 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT5_MASK         ((uint32_t)0x00000020U)         /* !< Select bit for INPUT5 */
/* XBAR_OUTPUTXBARG0SEL[INPUT6] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT6_OFS          (6)                             /* !< INPUT6 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT6_MASK         ((uint32_t)0x00000040U)         /* !< Select bit for INPUT6 */
/* XBAR_OUTPUTXBARG0SEL[INPUT7] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT7_OFS          (7)                             /* !< INPUT7 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT7_MASK         ((uint32_t)0x00000080U)         /* !< Select bit for INPUT7 */
/* XBAR_OUTPUTXBARG0SEL[INPUT8] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT8_OFS          (8)                             /* !< INPUT8 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT8_MASK         ((uint32_t)0x00000100U)         /* !< Select bit for INPUT8 */
/* XBAR_OUTPUTXBARG0SEL[INPUT9] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT9_OFS          (9)                             /* !< INPUT9 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT9_MASK         ((uint32_t)0x00000200U)         /* !< Select bit for INPUT9 */
/* XBAR_OUTPUTXBARG0SEL[INPUT10] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT10_OFS         (10)                            /* !< INPUT10 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT10_MASK        ((uint32_t)0x00000400U)         /* !< Select bit for INPUT10 */
/* XBAR_OUTPUTXBARG0SEL[INPUT11] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT11_OFS         (11)                            /* !< INPUT11 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT11_MASK        ((uint32_t)0x00000800U)         /* !< Select bit for INPUT11 */
/* XBAR_OUTPUTXBARG0SEL[INPUT12] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT12_OFS         (12)                            /* !< INPUT12 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT12_MASK        ((uint32_t)0x00001000U)         /* !< Select bit for INPUT12 */
/* XBAR_OUTPUTXBARG0SEL[INPUT13] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT13_OFS         (13)                            /* !< INPUT13 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT13_MASK        ((uint32_t)0x00002000U)         /* !< Select bit for INPUT13 */
/* XBAR_OUTPUTXBARG0SEL[INPUT14] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT14_OFS         (14)                            /* !< INPUT14 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT14_MASK        ((uint32_t)0x00004000U)         /* !< Select bit for INPUT14 */
/* XBAR_OUTPUTXBARG0SEL[INPUT15] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT15_OFS         (15)                            /* !< INPUT15 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT15_MASK        ((uint32_t)0x00008000U)         /* !< Select bit for INPUT15 */
/* XBAR_OUTPUTXBARG0SEL[INPUT16] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT16_OFS         (16)                            /* !< INPUT16 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT16_MASK        ((uint32_t)0x00010000U)         /* !< Select bit for INPUT16 */
/* XBAR_OUTPUTXBARG0SEL[INPUT17] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT17_OFS         (17)                            /* !< INPUT17 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT17_MASK        ((uint32_t)0x00020000U)         /* !< Select bit for INPUT17 */
/* XBAR_OUTPUTXBARG0SEL[INPUT18] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT18_OFS         (18)                            /* !< INPUT18 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT18_MASK        ((uint32_t)0x00040000U)         /* !< Select bit for INPUT18 */
/* XBAR_OUTPUTXBARG0SEL[INPUT19] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT19_OFS         (19)                            /* !< INPUT19 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT19_MASK        ((uint32_t)0x00080000U)         /* !< Select bit for INPUT19 */
/* XBAR_OUTPUTXBARG0SEL[INPUT20] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT20_OFS         (20)                            /* !< INPUT20 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT20_MASK        ((uint32_t)0x00100000U)         /* !< Select bit for INPUT20 */
/* XBAR_OUTPUTXBARG0SEL[INPUT21] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT21_OFS         (21)                            /* !< INPUT21 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT21_MASK        ((uint32_t)0x00200000U)         /* !< Select bit for INPUT21 */
/* XBAR_OUTPUTXBARG0SEL[INPUT22] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT22_OFS         (22)                            /* !< INPUT22 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT22_MASK        ((uint32_t)0x00400000U)         /* !< Select bit for INPUT22 */
/* XBAR_OUTPUTXBARG0SEL[INPUT23] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT23_OFS         (23)                            /* !< INPUT23 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT23_MASK        ((uint32_t)0x00800000U)         /* !< Select bit for INPUT23 */
/* XBAR_OUTPUTXBARG0SEL[INPUT24] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT24_OFS         (24)                            /* !< INPUT24 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT24_MASK        ((uint32_t)0x01000000U)         /* !< Select bit for INPUT24 */
/* XBAR_OUTPUTXBARG0SEL[INPUT25] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT25_OFS         (25)                            /* !< INPUT25 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT25_MASK        ((uint32_t)0x02000000U)         /* !< Select bit for INPUT25 */
/* XBAR_OUTPUTXBARG0SEL[INPUT26] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT26_OFS         (26)                            /* !< INPUT26 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT26_MASK        ((uint32_t)0x04000000U)         /* !< Select bit for INPUT26 */
/* XBAR_OUTPUTXBARG0SEL[INPUT27] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT27_OFS         (27)                            /* !< INPUT27 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT27_MASK        ((uint32_t)0x08000000U)         /* !< Select bit for INPUT27 */
/* XBAR_OUTPUTXBARG0SEL[INPUT28] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT28_OFS         (28)                            /* !< INPUT28 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT28_MASK        ((uint32_t)0x10000000U)         /* !< Select bit for INPUT28 */
/* XBAR_OUTPUTXBARG0SEL[INPUT29] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT29_OFS         (29)                            /* !< INPUT29 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT29_MASK        ((uint32_t)0x20000000U)         /* !< Select bit for INPUT29 */
/* XBAR_OUTPUTXBARG0SEL[INPUT30] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT30_OFS         (30)                            /* !< INPUT30 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT30_MASK        ((uint32_t)0x40000000U)         /* !< Select bit for INPUT30 */
/* XBAR_OUTPUTXBARG0SEL[INPUT31] Bits */
#define XBAR_OUTPUTXBARG0SEL_INPUT31_OFS         (31)                            /* !< INPUT31 Offset */
#define XBAR_OUTPUTXBARG0SEL_INPUT31_MASK        ((uint32_t)0x80000000U)         /* !< Select bit for INPUT31 */

/* XBAR_OUTPUTXBARG1SEL Bits */
/* XBAR_OUTPUTXBARG1SEL[INPUT0] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT0_OFS          (0)                             /* !< INPUT0 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT0_MASK         ((uint32_t)0x00000001U)         /* !< Select bit for INPUT0 */
/* XBAR_OUTPUTXBARG1SEL[INPUT1] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT1_OFS          (1)                             /* !< INPUT1 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT1_MASK         ((uint32_t)0x00000002U)         /* !< Select bit for INPUT1 */
/* XBAR_OUTPUTXBARG1SEL[INPUT2] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT2_OFS          (2)                             /* !< INPUT2 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT2_MASK         ((uint32_t)0x00000004U)         /* !< Select bit for INPUT2 */
/* XBAR_OUTPUTXBARG1SEL[INPUT3] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT3_OFS          (3)                             /* !< INPUT3 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT3_MASK         ((uint32_t)0x00000008U)         /* !< Select bit for INPUT3 */
/* XBAR_OUTPUTXBARG1SEL[INPUT4] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT4_OFS          (4)                             /* !< INPUT4 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT4_MASK         ((uint32_t)0x00000010U)         /* !< Select bit for INPUT4 */
/* XBAR_OUTPUTXBARG1SEL[INPUT5] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT5_OFS          (5)                             /* !< INPUT5 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT5_MASK         ((uint32_t)0x00000020U)         /* !< Select bit for INPUT5 */
/* XBAR_OUTPUTXBARG1SEL[INPUT6] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT6_OFS          (6)                             /* !< INPUT6 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT6_MASK         ((uint32_t)0x00000040U)         /* !< Select bit for INPUT6 */
/* XBAR_OUTPUTXBARG1SEL[INPUT7] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT7_OFS          (7)                             /* !< INPUT7 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT7_MASK         ((uint32_t)0x00000080U)         /* !< Select bit for INPUT7 */
/* XBAR_OUTPUTXBARG1SEL[INPUT8] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT8_OFS          (8)                             /* !< INPUT8 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT8_MASK         ((uint32_t)0x00000100U)         /* !< Select bit for INPUT8 */
/* XBAR_OUTPUTXBARG1SEL[INPUT9] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT9_OFS          (9)                             /* !< INPUT9 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT9_MASK         ((uint32_t)0x00000200U)         /* !< Select bit for INPUT9 */
/* XBAR_OUTPUTXBARG1SEL[INPUT10] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT10_OFS         (10)                            /* !< INPUT10 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT10_MASK        ((uint32_t)0x00000400U)         /* !< Select bit for INPUT10 */
/* XBAR_OUTPUTXBARG1SEL[INPUT11] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT11_OFS         (11)                            /* !< INPUT11 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT11_MASK        ((uint32_t)0x00000800U)         /* !< Select bit for INPUT11 */
/* XBAR_OUTPUTXBARG1SEL[INPUT12] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT12_OFS         (12)                            /* !< INPUT12 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT12_MASK        ((uint32_t)0x00001000U)         /* !< Select bit for INPUT12 */
/* XBAR_OUTPUTXBARG1SEL[INPUT13] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT13_OFS         (13)                            /* !< INPUT13 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT13_MASK        ((uint32_t)0x00002000U)         /* !< Select bit for INPUT13 */
/* XBAR_OUTPUTXBARG1SEL[INPUT14] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT14_OFS         (14)                            /* !< INPUT14 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT14_MASK        ((uint32_t)0x00004000U)         /* !< Select bit for INPUT14 */
/* XBAR_OUTPUTXBARG1SEL[INPUT15] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT15_OFS         (15)                            /* !< INPUT15 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT15_MASK        ((uint32_t)0x00008000U)         /* !< Select bit for INPUT15 */
/* XBAR_OUTPUTXBARG1SEL[INPUT16] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT16_OFS         (16)                            /* !< INPUT16 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT16_MASK        ((uint32_t)0x00010000U)         /* !< Select bit for INPUT16 */
/* XBAR_OUTPUTXBARG1SEL[INPUT17] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT17_OFS         (17)                            /* !< INPUT17 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT17_MASK        ((uint32_t)0x00020000U)         /* !< Select bit for INPUT17 */
/* XBAR_OUTPUTXBARG1SEL[INPUT18] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT18_OFS         (18)                            /* !< INPUT18 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT18_MASK        ((uint32_t)0x00040000U)         /* !< Select bit for INPUT18 */
/* XBAR_OUTPUTXBARG1SEL[INPUT19] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT19_OFS         (19)                            /* !< INPUT19 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT19_MASK        ((uint32_t)0x00080000U)         /* !< Select bit for INPUT19 */
/* XBAR_OUTPUTXBARG1SEL[INPUT20] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT20_OFS         (20)                            /* !< INPUT20 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT20_MASK        ((uint32_t)0x00100000U)         /* !< Select bit for INPUT20 */
/* XBAR_OUTPUTXBARG1SEL[INPUT21] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT21_OFS         (21)                            /* !< INPUT21 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT21_MASK        ((uint32_t)0x00200000U)         /* !< Select bit for INPUT21 */
/* XBAR_OUTPUTXBARG1SEL[INPUT22] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT22_OFS         (22)                            /* !< INPUT22 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT22_MASK        ((uint32_t)0x00400000U)         /* !< Select bit for INPUT22 */
/* XBAR_OUTPUTXBARG1SEL[INPUT23] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT23_OFS         (23)                            /* !< INPUT23 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT23_MASK        ((uint32_t)0x00800000U)         /* !< Select bit for INPUT23 */
/* XBAR_OUTPUTXBARG1SEL[INPUT24] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT24_OFS         (24)                            /* !< INPUT24 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT24_MASK        ((uint32_t)0x01000000U)         /* !< Select bit for INPUT24 */
/* XBAR_OUTPUTXBARG1SEL[INPUT25] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT25_OFS         (25)                            /* !< INPUT25 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT25_MASK        ((uint32_t)0x02000000U)         /* !< Select bit for INPUT25 */
/* XBAR_OUTPUTXBARG1SEL[INPUT26] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT26_OFS         (26)                            /* !< INPUT26 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT26_MASK        ((uint32_t)0x04000000U)         /* !< Select bit for INPUT26 */
/* XBAR_OUTPUTXBARG1SEL[INPUT27] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT27_OFS         (27)                            /* !< INPUT27 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT27_MASK        ((uint32_t)0x08000000U)         /* !< Select bit for INPUT27 */
/* XBAR_OUTPUTXBARG1SEL[INPUT28] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT28_OFS         (28)                            /* !< INPUT28 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT28_MASK        ((uint32_t)0x10000000U)         /* !< Select bit for INPUT28 */
/* XBAR_OUTPUTXBARG1SEL[INPUT29] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT29_OFS         (29)                            /* !< INPUT29 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT29_MASK        ((uint32_t)0x20000000U)         /* !< Select bit for INPUT29 */
/* XBAR_OUTPUTXBARG1SEL[INPUT30] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT30_OFS         (30)                            /* !< INPUT30 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT30_MASK        ((uint32_t)0x40000000U)         /* !< Select bit for INPUT30 */
/* XBAR_OUTPUTXBARG1SEL[INPUT31] Bits */
#define XBAR_OUTPUTXBARG1SEL_INPUT31_OFS         (31)                            /* !< INPUT31 Offset */
#define XBAR_OUTPUTXBARG1SEL_INPUT31_MASK        ((uint32_t)0x80000000U)         /* !< Select bit for INPUT31 */

/* XBAR_OUTPUTXBARFLAGINVERT Bits */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR1] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR1_OFS      (0)                             /* !< XBAR1 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR1_MASK     ((uint32_t)0x00000001U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR1 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR2] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR2_OFS      (1)                             /* !< XBAR2 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR2_MASK     ((uint32_t)0x00000002U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR2 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR3] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR3_OFS      (2)                             /* !< XBAR3 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR3_MASK     ((uint32_t)0x00000004U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR3 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR4] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR4_OFS      (3)                             /* !< XBAR4 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR4_MASK     ((uint32_t)0x00000008U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR4 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR5] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR5_OFS      (4)                             /* !< XBAR5 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR5_MASK     ((uint32_t)0x00000010U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR5 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR6] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR6_OFS      (5)                             /* !< XBAR6 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR6_MASK     ((uint32_t)0x00000020U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR6 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR7] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR7_OFS      (6)                             /* !< XBAR7 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR7_MASK     ((uint32_t)0x00000040U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR7 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR8] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR8_OFS      (7)                             /* !< XBAR8 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR8_MASK     ((uint32_t)0x00000080U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR8 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR9] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR9_OFS      (8)                             /* !< XBAR9 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR9_MASK     ((uint32_t)0x00000100U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR9 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR10] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR10_OFS     (9)                             /* !< XBAR10 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR10_MASK    ((uint32_t)0x00000200U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR10 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR11] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR11_OFS     (10)                            /* !< XBAR11 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR11_MASK    ((uint32_t)0x00000400U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR11 */
/* XBAR_OUTPUTXBARFLAGINVERT[XBAR12] Bits */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR12_OFS     (11)                            /* !< XBAR12 Offset */
#define XBAR_OUTPUTXBARFLAGINVERT_XBAR12_MASK    ((uint32_t)0x00000800U)         /* !< Invert XBAR Output Before Latch for
                                                                                    XBAR12 */

/* XBAR_OUTPUTXBAROUTLATCH Bits */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR1] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR1_OFS        (0)                             /* !< XBAR1 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR1_MASK       ((uint32_t)0x00000001U)         /* !< XBAR Output Latch Select for XBAR1 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR2] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR2_OFS        (1)                             /* !< XBAR2 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR2_MASK       ((uint32_t)0x00000002U)         /* !< XBAR Output Latch Select for XBAR2 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR3] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR3_OFS        (2)                             /* !< XBAR3 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR3_MASK       ((uint32_t)0x00000004U)         /* !< XBAR Output Latch Select for XBAR3 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR4] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR4_OFS        (3)                             /* !< XBAR4 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR4_MASK       ((uint32_t)0x00000008U)         /* !< XBAR Output Latch Select for XBAR4 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR5] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR5_OFS        (4)                             /* !< XBAR5 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR5_MASK       ((uint32_t)0x00000010U)         /* !< XBAR Output Latch Select for XBAR5 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR6] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR6_OFS        (5)                             /* !< XBAR6 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR6_MASK       ((uint32_t)0x00000020U)         /* !< XBAR Output Latch Select for XBAR6 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR7] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR7_OFS        (6)                             /* !< XBAR7 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR7_MASK       ((uint32_t)0x00000040U)         /* !< XBAR Output Latch Select for XBAR7 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR8] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR8_OFS        (7)                             /* !< XBAR8 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR8_MASK       ((uint32_t)0x00000080U)         /* !< XBAR Output Latch Select for XBAR8 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR9] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR9_OFS        (8)                             /* !< XBAR9 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR9_MASK       ((uint32_t)0x00000100U)         /* !< XBAR Output Latch Select for XBAR9 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR10] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR10_OFS       (9)                             /* !< XBAR10 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR10_MASK      ((uint32_t)0x00000200U)         /* !< XBAR Output Latch Select for XBAR10 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR11] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR11_OFS       (10)                            /* !< XBAR11 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR11_MASK      ((uint32_t)0x00000400U)         /* !< XBAR Output Latch Select for XBAR11 */
/* XBAR_OUTPUTXBAROUTLATCH[XBAR12] Bits */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR12_OFS       (11)                            /* !< XBAR12 Offset */
#define XBAR_OUTPUTXBAROUTLATCH_XBAR12_MASK      ((uint32_t)0x00000800U)         /* !< XBAR Output Latch Select for XBAR12 */

/* XBAR_OUTPUTXBAROUTINVERT Bits */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR1] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR1_OFS       (0)                             /* !< XBAR1 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR1_MASK      ((uint32_t)0x00000001U)         /* !< Invert XBAR Output for XBAR1 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR2] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR2_OFS       (1)                             /* !< XBAR2 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR2_MASK      ((uint32_t)0x00000002U)         /* !< Invert XBAR Output for XBAR2 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR3] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR3_OFS       (2)                             /* !< XBAR3 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR3_MASK      ((uint32_t)0x00000004U)         /* !< Invert XBAR Output for XBAR3 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR4] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR4_OFS       (3)                             /* !< XBAR4 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR4_MASK      ((uint32_t)0x00000008U)         /* !< Invert XBAR Output for XBAR4 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR5] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR5_OFS       (4)                             /* !< XBAR5 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR5_MASK      ((uint32_t)0x00000010U)         /* !< Invert XBAR Output for XBAR5 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR6] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR6_OFS       (5)                             /* !< XBAR6 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR6_MASK      ((uint32_t)0x00000020U)         /* !< Invert XBAR Output for XBAR6 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR7] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR7_OFS       (6)                             /* !< XBAR7 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR7_MASK      ((uint32_t)0x00000040U)         /* !< Invert XBAR Output for XBAR7 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR8] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR8_OFS       (7)                             /* !< XBAR8 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR8_MASK      ((uint32_t)0x00000080U)         /* !< Invert XBAR Output for XBAR8 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR9] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR9_OFS       (8)                             /* !< XBAR9 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR9_MASK      ((uint32_t)0x00000100U)         /* !< Invert XBAR Output for XBAR9 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR10] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR10_OFS      (9)                             /* !< XBAR10 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR10_MASK     ((uint32_t)0x00000200U)         /* !< Invert XBAR Output for XBAR10 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR11] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR11_OFS      (10)                            /* !< XBAR11 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR11_MASK     ((uint32_t)0x00000400U)         /* !< Invert XBAR Output for XBAR11 */
/* XBAR_OUTPUTXBAROUTINVERT[XBAR12] Bits */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR12_OFS      (11)                            /* !< XBAR12 Offset */
#define XBAR_OUTPUTXBAROUTINVERT_XBAR12_MASK     ((uint32_t)0x00000800U)         /* !< Invert XBAR Output for XBAR12 */

/* XBAR_OUTPUTXBARLOCK Bits */
/* XBAR_OUTPUTXBARLOCK[LOCK] Bits */
#define XBAR_OUTPUTXBARLOCK_LOCK_OFS             (0)                             /* !< LOCK Offset */
#define XBAR_OUTPUTXBARLOCK_LOCK_MASK            ((uint32_t)0x00000001U)         /* !< Locks the configuration for
                                                                                    EOUTPUT-XBAR */
/* XBAR_OUTPUTXBARLOCK[KEY] Bits */
#define XBAR_OUTPUTXBARLOCK_KEY_OFS              (16)                            /* !< KEY Offset */
#define XBAR_OUTPUTXBARLOCK_KEY_MASK             ((uint32_t)0xFFFF0000U)         /* !< Write protection KEY */

/* XBAR_OUTPUTXBARSTATUS Bits */
/* XBAR_OUTPUTXBARSTATUS[STS] Bits */
#define XBAR_OUTPUTXBARSTATUS_STS_OFS            (0)                             /* !< STS Offset */
#define XBAR_OUTPUTXBARSTATUS_STS_MASK           ((uint32_t)0x00000001U)         /* !< Output Signal Status */

/* XBAR_OUTPUTXBARFLAG Bits */
/* XBAR_OUTPUTXBARFLAG[FLG] Bits */
#define XBAR_OUTPUTXBARFLAG_FLG_OFS              (0)                             /* !< FLG Offset */
#define XBAR_OUTPUTXBARFLAG_FLG_MASK             ((uint32_t)0x00000001U)         /* !< Output Signal Latched Flag Status */

/* XBAR_OUTPUTXBARFLAGCLEAR Bits */
/* XBAR_OUTPUTXBARFLAGCLEAR[FLG] Bits */
#define XBAR_OUTPUTXBARFLAGCLEAR_FLG_OFS         (0)                             /* !< FLG Offset */
#define XBAR_OUTPUTXBARFLAGCLEAR_FLG_MASK        ((uint32_t)0x00000001U)         /* !< Output Signal Latched Flag Clear */

/* XBAR_OUTPUTXBARFLAGFORCE Bits */
/* XBAR_OUTPUTXBARFLAGFORCE[FLG] Bits */
#define XBAR_OUTPUTXBARFLAGFORCE_FLG_OFS         (0)                             /* !< FLG Offset */
#define XBAR_OUTPUTXBARFLAGFORCE_FLG_MASK        ((uint32_t)0x00000001U)         /* !< Output Signal Latched Flag Force */

/* XBAR_INPUTSELECT Bits */
/* XBAR_INPUTSELECT[SELECT] Bits */
#define XBAR_INPUTSELECT_SELECT_OFS              (0)                             /* !< SELECT Offset */
#define XBAR_INPUTSELECT_SELECT_MASK             ((uint32_t)0x000000FFU)         /* !< Select GPIO for INPUT{#} signal */

/* XBAR_INPUTSELECTLOCK1 Bits */
/* XBAR_INPUTSELECTLOCK1[INPUT1SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT1SELECT_OFS   (0)                             /* !< INPUT1SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT1SELECT_MASK  ((uint32_t)0x00000001U)         /* !< Lock bit for INPUT1SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT2SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT2SELECT_OFS   (1)                             /* !< INPUT2SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT2SELECT_MASK  ((uint32_t)0x00000002U)         /* !< Lock bit for INPUT2SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT3SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT3SELECT_OFS   (2)                             /* !< INPUT3SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT3SELECT_MASK  ((uint32_t)0x00000004U)         /* !< Lock bit for INPUT3SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT4SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT4SELECT_OFS   (3)                             /* !< INPUT4SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT4SELECT_MASK  ((uint32_t)0x00000008U)         /* !< Lock bit for INPUT4SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT5SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT5SELECT_OFS   (4)                             /* !< INPUT5SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT5SELECT_MASK  ((uint32_t)0x00000010U)         /* !< Lock bit for INPUT5SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT6SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT6SELECT_OFS   (5)                             /* !< INPUT6SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT6SELECT_MASK  ((uint32_t)0x00000020U)         /* !< Lock bit for INPUT6SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT7SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT7SELECT_OFS   (6)                             /* !< INPUT7SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT7SELECT_MASK  ((uint32_t)0x00000040U)         /* !< Lock bit for INPUT7SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT8SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT8SELECT_OFS   (7)                             /* !< INPUT8SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT8SELECT_MASK  ((uint32_t)0x00000080U)         /* !< Lock bit for INPUT8SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT9SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT9SELECT_OFS   (8)                             /* !< INPUT9SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT9SELECT_MASK  ((uint32_t)0x00000100U)         /* !< Lock bit for INPUT9SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT10SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT10SELECT_OFS  (9)                             /* !< INPUT10SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT10SELECT_MASK ((uint32_t)0x00000200U)         /* !< Lock bit for INPUT10SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT11SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT11SELECT_OFS  (10)                            /* !< INPUT11SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT11SELECT_MASK ((uint32_t)0x00000400U)         /* !< Lock bit for INPUT11SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT12SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT12SELECT_OFS  (11)                            /* !< INPUT12SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT12SELECT_MASK ((uint32_t)0x00000800U)         /* !< Lock bit for INPUT12SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT13SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT13SELECT_OFS  (12)                            /* !< INPUT13SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT13SELECT_MASK ((uint32_t)0x00001000U)         /* !< Lock bit for INPUT13SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT14SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT14SELECT_OFS  (13)                            /* !< INPUT14SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT14SELECT_MASK ((uint32_t)0x00002000U)         /* !< Lock bit for INPUT14SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT15SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT15SELECT_OFS  (14)                            /* !< INPUT15SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT15SELECT_MASK ((uint32_t)0x00004000U)         /* !< Lock bit for INPUT15SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT16SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT16SELECT_OFS  (15)                            /* !< INPUT16SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT16SELECT_MASK ((uint32_t)0x00008000U)         /* !< Lock bit for INPUT16SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT17SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT17SELECT_OFS  (16)                            /* !< INPUT17SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT17SELECT_MASK ((uint32_t)0x00010000U)         /* !< Lock bit for INPUT17SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT18SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT18SELECT_OFS  (17)                            /* !< INPUT18SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT18SELECT_MASK ((uint32_t)0x00020000U)         /* !< Lock bit for INPUT18SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT19SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT19SELECT_OFS  (18)                            /* !< INPUT19SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT19SELECT_MASK ((uint32_t)0x00040000U)         /* !< Lock bit for INPUT19SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT20SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT20SELECT_OFS  (19)                            /* !< INPUT20SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT20SELECT_MASK ((uint32_t)0x00080000U)         /* !< Lock bit for INPUT20SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT21SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT21SELECT_OFS  (20)                            /* !< INPUT21SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT21SELECT_MASK ((uint32_t)0x00100000U)         /* !< Lock bit for INPUT21SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT22SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT22SELECT_OFS  (21)                            /* !< INPUT22SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT22SELECT_MASK ((uint32_t)0x00200000U)         /* !< Lock bit for INPUT22SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT23SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT23SELECT_OFS  (22)                            /* !< INPUT23SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT23SELECT_MASK ((uint32_t)0x00400000U)         /* !< Lock bit for INPUT23SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT24SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT24SELECT_OFS  (23)                            /* !< INPUT24SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT24SELECT_MASK ((uint32_t)0x00800000U)         /* !< Lock bit for INPUT24SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT25SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT25SELECT_OFS  (24)                            /* !< INPUT25SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT25SELECT_MASK ((uint32_t)0x01000000U)         /* !< Lock bit for INPUT25SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT26SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT26SELECT_OFS  (25)                            /* !< INPUT26SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT26SELECT_MASK ((uint32_t)0x02000000U)         /* !< Lock bit for INPUT26SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT27SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT27SELECT_OFS  (26)                            /* !< INPUT27SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT27SELECT_MASK ((uint32_t)0x04000000U)         /* !< Lock bit for INPUT27SELECT Register */
/* XBAR_INPUTSELECTLOCK1[INPUT28SELECT] Bits */
#define XBAR_INPUTSELECTLOCK1_INPUT28SELECT_OFS  (27)                            /* !< INPUT28SELECT Offset */
#define XBAR_INPUTSELECTLOCK1_INPUT28SELECT_MASK ((uint32_t)0x08000000U)         /* !< Lock bit for INPUT28SELECT Register */

/* XBAR_RAW_INPUTSELECT_PA Bits */
/* XBAR_RAW_INPUTSELECT_PA[SEL0] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL0_OFS         (0)                             /* !< SEL0 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL0_MASK        ((uint32_t)0x00000001U)         /* !< Raw input select bit for PA0 */
/* XBAR_RAW_INPUTSELECT_PA[SEL1] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL1_OFS         (1)                             /* !< SEL1 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL1_MASK        ((uint32_t)0x00000002U)         /* !< Raw input select bit for PA1 */
/* XBAR_RAW_INPUTSELECT_PA[SEL2] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL2_OFS         (2)                             /* !< SEL2 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL2_MASK        ((uint32_t)0x00000004U)         /* !< Raw input select bit for PA2 */
/* XBAR_RAW_INPUTSELECT_PA[SEL3] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL3_OFS         (3)                             /* !< SEL3 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL3_MASK        ((uint32_t)0x00000008U)         /* !< Raw input select bit for PA3 */
/* XBAR_RAW_INPUTSELECT_PA[SEL4] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL4_OFS         (4)                             /* !< SEL4 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL4_MASK        ((uint32_t)0x00000010U)         /* !< Raw input select bit for PA4 */
/* XBAR_RAW_INPUTSELECT_PA[SEL5] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL5_OFS         (5)                             /* !< SEL5 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL5_MASK        ((uint32_t)0x00000020U)         /* !< Raw input select bit for PA5 */
/* XBAR_RAW_INPUTSELECT_PA[SEL6] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL6_OFS         (6)                             /* !< SEL6 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL6_MASK        ((uint32_t)0x00000040U)         /* !< Raw input select bit for PA6 */
/* XBAR_RAW_INPUTSELECT_PA[SEL7] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL7_OFS         (7)                             /* !< SEL7 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL7_MASK        ((uint32_t)0x00000080U)         /* !< Raw input select bit for PA7 */
/* XBAR_RAW_INPUTSELECT_PA[SEL8] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL8_OFS         (8)                             /* !< SEL8 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL8_MASK        ((uint32_t)0x00000100U)         /* !< Raw input select bit for PA8 */
/* XBAR_RAW_INPUTSELECT_PA[SEL9] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL9_OFS         (9)                             /* !< SEL9 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL9_MASK        ((uint32_t)0x00000200U)         /* !< Raw input select bit for PA9 */
/* XBAR_RAW_INPUTSELECT_PA[SEL10] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL10_OFS        (10)                            /* !< SEL10 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL10_MASK       ((uint32_t)0x00000400U)         /* !< Raw input select bit for PA10 */
/* XBAR_RAW_INPUTSELECT_PA[SEL11] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL11_OFS        (11)                            /* !< SEL11 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL11_MASK       ((uint32_t)0x00000800U)         /* !< Raw input select bit for PA11 */
/* XBAR_RAW_INPUTSELECT_PA[SEL12] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL12_OFS        (12)                            /* !< SEL12 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL12_MASK       ((uint32_t)0x00001000U)         /* !< Raw input select bit for PA12 */
/* XBAR_RAW_INPUTSELECT_PA[SEL13] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL13_OFS        (13)                            /* !< SEL13 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL13_MASK       ((uint32_t)0x00002000U)         /* !< Raw input select bit for PA13 */
/* XBAR_RAW_INPUTSELECT_PA[SEL14] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL14_OFS        (14)                            /* !< SEL14 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL14_MASK       ((uint32_t)0x00004000U)         /* !< Raw input select bit for PA14 */
/* XBAR_RAW_INPUTSELECT_PA[SEL15] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL15_OFS        (15)                            /* !< SEL15 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL15_MASK       ((uint32_t)0x00008000U)         /* !< Raw input select bit for PA15 */
/* XBAR_RAW_INPUTSELECT_PA[SEL16] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL16_OFS        (16)                            /* !< SEL16 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL16_MASK       ((uint32_t)0x00010000U)         /* !< Raw input select bit for PA16 */
/* XBAR_RAW_INPUTSELECT_PA[SEL17] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL17_OFS        (17)                            /* !< SEL17 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL17_MASK       ((uint32_t)0x00020000U)         /* !< Raw input select bit for PA17 */
/* XBAR_RAW_INPUTSELECT_PA[SEL18] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL18_OFS        (18)                            /* !< SEL18 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL18_MASK       ((uint32_t)0x00040000U)         /* !< Raw input select bit for PA18 */
/* XBAR_RAW_INPUTSELECT_PA[SEL19] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL19_OFS        (19)                            /* !< SEL19 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL19_MASK       ((uint32_t)0x00080000U)         /* !< Raw input select bit for PA19 */
/* XBAR_RAW_INPUTSELECT_PA[SEL20] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL20_OFS        (20)                            /* !< SEL20 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL20_MASK       ((uint32_t)0x00100000U)         /* !< Raw input select bit for PA20 */
/* XBAR_RAW_INPUTSELECT_PA[SEL21] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL21_OFS        (21)                            /* !< SEL21 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL21_MASK       ((uint32_t)0x00200000U)         /* !< Raw input select bit for PA21 */
/* XBAR_RAW_INPUTSELECT_PA[SEL22] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL22_OFS        (22)                            /* !< SEL22 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL22_MASK       ((uint32_t)0x00400000U)         /* !< Raw input select bit for PA22 */
/* XBAR_RAW_INPUTSELECT_PA[SEL23] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL23_OFS        (23)                            /* !< SEL23 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL23_MASK       ((uint32_t)0x00800000U)         /* !< Raw input select bit for PA23 */
/* XBAR_RAW_INPUTSELECT_PA[SEL24] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL24_OFS        (24)                            /* !< SEL24 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL24_MASK       ((uint32_t)0x01000000U)         /* !< Raw input select bit for PA24 */
/* XBAR_RAW_INPUTSELECT_PA[SEL25] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL25_OFS        (25)                            /* !< SEL25 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL25_MASK       ((uint32_t)0x02000000U)         /* !< Raw input select bit for PA25 */
/* XBAR_RAW_INPUTSELECT_PA[SEL26] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL26_OFS        (26)                            /* !< SEL26 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL26_MASK       ((uint32_t)0x04000000U)         /* !< Raw input select bit for PA26 */
/* XBAR_RAW_INPUTSELECT_PA[SEL27] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL27_OFS        (27)                            /* !< SEL27 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL27_MASK       ((uint32_t)0x08000000U)         /* !< Raw input select bit for PA27 */
/* XBAR_RAW_INPUTSELECT_PA[SEL28] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL28_OFS        (28)                            /* !< SEL28 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL28_MASK       ((uint32_t)0x10000000U)         /* !< Raw input select bit for PA28 */
/* XBAR_RAW_INPUTSELECT_PA[SEL29] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL29_OFS        (29)                            /* !< SEL29 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL29_MASK       ((uint32_t)0x20000000U)         /* !< Raw input select bit for PA29 */
/* XBAR_RAW_INPUTSELECT_PA[SEL30] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL30_OFS        (30)                            /* !< SEL30 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL30_MASK       ((uint32_t)0x40000000U)         /* !< Raw input select bit for PA30 */
/* XBAR_RAW_INPUTSELECT_PA[SEL31] Bits */
#define XBAR_RAW_INPUTSELECT_PA_SEL31_OFS        (31)                            /* !< SEL31 Offset */
#define XBAR_RAW_INPUTSELECT_PA_SEL31_MASK       ((uint32_t)0x80000000U)         /* !< Raw input select bit for PA31 */

/* XBAR_RAW_INPUTSELECT_PB Bits */
/* XBAR_RAW_INPUTSELECT_PB[SEL0] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL0_OFS         (0)                             /* !< SEL0 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL0_MASK        ((uint32_t)0x00000001U)         /* !< Raw input select bit for PB0 */
/* XBAR_RAW_INPUTSELECT_PB[SEL1] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL1_OFS         (1)                             /* !< SEL1 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL1_MASK        ((uint32_t)0x00000002U)         /* !< Raw input select bit for PB1 */
/* XBAR_RAW_INPUTSELECT_PB[SEL2] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL2_OFS         (2)                             /* !< SEL2 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL2_MASK        ((uint32_t)0x00000004U)         /* !< Raw input select bit for PB2 */
/* XBAR_RAW_INPUTSELECT_PB[SEL3] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL3_OFS         (3)                             /* !< SEL3 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL3_MASK        ((uint32_t)0x00000008U)         /* !< Raw input select bit for PB3 */
/* XBAR_RAW_INPUTSELECT_PB[SEL4] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL4_OFS         (4)                             /* !< SEL4 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL4_MASK        ((uint32_t)0x00000010U)         /* !< Raw input select bit for PB4 */
/* XBAR_RAW_INPUTSELECT_PB[SEL5] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL5_OFS         (5)                             /* !< SEL5 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL5_MASK        ((uint32_t)0x00000020U)         /* !< Raw input select bit for PB5 */
/* XBAR_RAW_INPUTSELECT_PB[SEL6] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL6_OFS         (6)                             /* !< SEL6 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL6_MASK        ((uint32_t)0x00000040U)         /* !< Raw input select bit for PB6 */
/* XBAR_RAW_INPUTSELECT_PB[SEL7] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL7_OFS         (7)                             /* !< SEL7 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL7_MASK        ((uint32_t)0x00000080U)         /* !< Raw input select bit for PB7 */
/* XBAR_RAW_INPUTSELECT_PB[SEL8] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL8_OFS         (8)                             /* !< SEL8 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL8_MASK        ((uint32_t)0x00000100U)         /* !< Raw input select bit for PB8 */
/* XBAR_RAW_INPUTSELECT_PB[SEL9] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL9_OFS         (9)                             /* !< SEL9 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL9_MASK        ((uint32_t)0x00000200U)         /* !< Raw input select bit for PB9 */
/* XBAR_RAW_INPUTSELECT_PB[SEL10] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL10_OFS        (10)                            /* !< SEL10 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL10_MASK       ((uint32_t)0x00000400U)         /* !< Raw input select bit for PB10 */
/* XBAR_RAW_INPUTSELECT_PB[SEL11] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL11_OFS        (11)                            /* !< SEL11 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL11_MASK       ((uint32_t)0x00000800U)         /* !< Raw input select bit for PB11 */
/* XBAR_RAW_INPUTSELECT_PB[SEL12] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL12_OFS        (12)                            /* !< SEL12 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL12_MASK       ((uint32_t)0x00001000U)         /* !< Raw input select bit for PB12 */
/* XBAR_RAW_INPUTSELECT_PB[SEL13] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL13_OFS        (13)                            /* !< SEL13 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL13_MASK       ((uint32_t)0x00002000U)         /* !< Raw input select bit for PB13 */
/* XBAR_RAW_INPUTSELECT_PB[SEL14] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL14_OFS        (14)                            /* !< SEL14 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL14_MASK       ((uint32_t)0x00004000U)         /* !< Raw input select bit for PB14 */
/* XBAR_RAW_INPUTSELECT_PB[SEL15] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL15_OFS        (15)                            /* !< SEL15 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL15_MASK       ((uint32_t)0x00008000U)         /* !< Raw input select bit for PB15 */
/* XBAR_RAW_INPUTSELECT_PB[SEL16] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL16_OFS        (16)                            /* !< SEL16 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL16_MASK       ((uint32_t)0x00010000U)         /* !< Raw input select bit for PB16 */
/* XBAR_RAW_INPUTSELECT_PB[SEL17] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL17_OFS        (17)                            /* !< SEL17 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL17_MASK       ((uint32_t)0x00020000U)         /* !< Raw input select bit for PB17 */
/* XBAR_RAW_INPUTSELECT_PB[SEL18] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL18_OFS        (18)                            /* !< SEL18 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL18_MASK       ((uint32_t)0x00040000U)         /* !< Raw input select bit for PB18 */
/* XBAR_RAW_INPUTSELECT_PB[SEL19] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL19_OFS        (19)                            /* !< SEL19 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL19_MASK       ((uint32_t)0x00080000U)         /* !< Raw input select bit for PB19 */
/* XBAR_RAW_INPUTSELECT_PB[SEL20] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL20_OFS        (20)                            /* !< SEL20 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL20_MASK       ((uint32_t)0x00100000U)         /* !< Raw input select bit for PB20 */
/* XBAR_RAW_INPUTSELECT_PB[SEL21] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL21_OFS        (21)                            /* !< SEL21 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL21_MASK       ((uint32_t)0x00200000U)         /* !< Raw input select bit for PB21 */
/* XBAR_RAW_INPUTSELECT_PB[SEL22] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL22_OFS        (22)                            /* !< SEL22 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL22_MASK       ((uint32_t)0x00400000U)         /* !< Raw input select bit for PB22 */
/* XBAR_RAW_INPUTSELECT_PB[SEL23] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL23_OFS        (23)                            /* !< SEL23 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL23_MASK       ((uint32_t)0x00800000U)         /* !< Raw input select bit for PB23 */
/* XBAR_RAW_INPUTSELECT_PB[SEL24] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL24_OFS        (24)                            /* !< SEL24 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL24_MASK       ((uint32_t)0x01000000U)         /* !< Raw input select bit for PB24 */
/* XBAR_RAW_INPUTSELECT_PB[SEL25] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL25_OFS        (25)                            /* !< SEL25 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL25_MASK       ((uint32_t)0x02000000U)         /* !< Raw input select bit for PB25 */
/* XBAR_RAW_INPUTSELECT_PB[SEL26] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL26_OFS        (26)                            /* !< SEL26 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL26_MASK       ((uint32_t)0x04000000U)         /* !< Raw input select bit for PB26 */
/* XBAR_RAW_INPUTSELECT_PB[SEL27] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL27_OFS        (27)                            /* !< SEL27 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL27_MASK       ((uint32_t)0x08000000U)         /* !< Raw input select bit for PB27 */
/* XBAR_RAW_INPUTSELECT_PB[SEL28] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL28_OFS        (28)                            /* !< SEL28 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL28_MASK       ((uint32_t)0x10000000U)         /* !< Raw input select bit for PB28 */
/* XBAR_RAW_INPUTSELECT_PB[SEL29] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL29_OFS        (29)                            /* !< SEL29 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL29_MASK       ((uint32_t)0x20000000U)         /* !< Raw input select bit for PB29 */
/* XBAR_RAW_INPUTSELECT_PB[SEL30] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL30_OFS        (30)                            /* !< SEL30 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL30_MASK       ((uint32_t)0x40000000U)         /* !< Raw input select bit for PB30 */
/* XBAR_RAW_INPUTSELECT_PB[SEL31] Bits */
#define XBAR_RAW_INPUTSELECT_PB_SEL31_OFS        (31)                            /* !< SEL31 Offset */
#define XBAR_RAW_INPUTSELECT_PB_SEL31_MASK       ((uint32_t)0x80000000U)         /* !< Raw input select bit for PB31 */

/* XBAR_RAW_INPUTSELECT_PC Bits */
/* XBAR_RAW_INPUTSELECT_PC[SEL0] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL0_OFS         (0)                             /* !< SEL0 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL0_MASK        ((uint32_t)0x00000001U)         /* !< Raw input select bit for PC0 */
/* XBAR_RAW_INPUTSELECT_PC[SEL1] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL1_OFS         (1)                             /* !< SEL1 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL1_MASK        ((uint32_t)0x00000002U)         /* !< Raw input select bit for PC1 */
/* XBAR_RAW_INPUTSELECT_PC[SEL2] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL2_OFS         (2)                             /* !< SEL2 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL2_MASK        ((uint32_t)0x00000004U)         /* !< Raw input select bit for PC2 */
/* XBAR_RAW_INPUTSELECT_PC[SEL3] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL3_OFS         (3)                             /* !< SEL3 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL3_MASK        ((uint32_t)0x00000008U)         /* !< Raw input select bit for PC3 */
/* XBAR_RAW_INPUTSELECT_PC[SEL4] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL4_OFS         (4)                             /* !< SEL4 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL4_MASK        ((uint32_t)0x00000010U)         /* !< Raw input select bit for PC4 */
/* XBAR_RAW_INPUTSELECT_PC[SEL5] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL5_OFS         (5)                             /* !< SEL5 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL5_MASK        ((uint32_t)0x00000020U)         /* !< Raw input select bit for PC5 */
/* XBAR_RAW_INPUTSELECT_PC[SEL6] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL6_OFS         (6)                             /* !< SEL6 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL6_MASK        ((uint32_t)0x00000040U)         /* !< Raw input select bit for PC6 */
/* XBAR_RAW_INPUTSELECT_PC[SEL7] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL7_OFS         (7)                             /* !< SEL7 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL7_MASK        ((uint32_t)0x00000080U)         /* !< Raw input select bit for PC7 */
/* XBAR_RAW_INPUTSELECT_PC[SEL8] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL8_OFS         (8)                             /* !< SEL8 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL8_MASK        ((uint32_t)0x00000100U)         /* !< Raw input select bit for PC8 */
/* XBAR_RAW_INPUTSELECT_PC[SEL9] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL9_OFS         (9)                             /* !< SEL9 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL9_MASK        ((uint32_t)0x00000200U)         /* !< Raw input select bit for PC9 */
/* XBAR_RAW_INPUTSELECT_PC[SEL10] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL10_OFS        (10)                            /* !< SEL10 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL10_MASK       ((uint32_t)0x00000400U)         /* !< Raw input select bit for PC10 */
/* XBAR_RAW_INPUTSELECT_PC[SEL11] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL11_OFS        (11)                            /* !< SEL11 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL11_MASK       ((uint32_t)0x00000800U)         /* !< Raw input select bit for PC11 */
/* XBAR_RAW_INPUTSELECT_PC[SEL12] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL12_OFS        (12)                            /* !< SEL12 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL12_MASK       ((uint32_t)0x00001000U)         /* !< Raw input select bit for PC12 */
/* XBAR_RAW_INPUTSELECT_PC[SEL13] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL13_OFS        (13)                            /* !< SEL13 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL13_MASK       ((uint32_t)0x00002000U)         /* !< Raw input select bit for PC13 */
/* XBAR_RAW_INPUTSELECT_PC[SEL14] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL14_OFS        (14)                            /* !< SEL14 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL14_MASK       ((uint32_t)0x00004000U)         /* !< Raw input select bit for PC14 */
/* XBAR_RAW_INPUTSELECT_PC[SEL15] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL15_OFS        (15)                            /* !< SEL15 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL15_MASK       ((uint32_t)0x00008000U)         /* !< Raw input select bit for PC15 */
/* XBAR_RAW_INPUTSELECT_PC[SEL16] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL16_OFS        (16)                            /* !< SEL16 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL16_MASK       ((uint32_t)0x00010000U)         /* !< Raw input select bit for PC16 */
/* XBAR_RAW_INPUTSELECT_PC[SEL17] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL17_OFS        (17)                            /* !< SEL17 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL17_MASK       ((uint32_t)0x00020000U)         /* !< Raw input select bit for PC17 */
/* XBAR_RAW_INPUTSELECT_PC[SEL18] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL18_OFS        (18)                            /* !< SEL18 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL18_MASK       ((uint32_t)0x00040000U)         /* !< Raw input select bit for PC18 */
/* XBAR_RAW_INPUTSELECT_PC[SEL19] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL19_OFS        (19)                            /* !< SEL19 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL19_MASK       ((uint32_t)0x00080000U)         /* !< Raw input select bit for PC19 */
/* XBAR_RAW_INPUTSELECT_PC[SEL20] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL20_OFS        (20)                            /* !< SEL20 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL20_MASK       ((uint32_t)0x00100000U)         /* !< Raw input select bit for PC20 */
/* XBAR_RAW_INPUTSELECT_PC[SEL21] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL21_OFS        (21)                            /* !< SEL21 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL21_MASK       ((uint32_t)0x00200000U)         /* !< Raw input select bit for PC21 */
/* XBAR_RAW_INPUTSELECT_PC[SEL22] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL22_OFS        (22)                            /* !< SEL22 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL22_MASK       ((uint32_t)0x00400000U)         /* !< Raw input select bit for PC22 */
/* XBAR_RAW_INPUTSELECT_PC[SEL23] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL23_OFS        (23)                            /* !< SEL23 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL23_MASK       ((uint32_t)0x00800000U)         /* !< Raw input select bit for PC23 */
/* XBAR_RAW_INPUTSELECT_PC[SEL24] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL24_OFS        (24)                            /* !< SEL24 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL24_MASK       ((uint32_t)0x01000000U)         /* !< Raw input select bit for PC24 */
/* XBAR_RAW_INPUTSELECT_PC[SEL25] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL25_OFS        (25)                            /* !< SEL25 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL25_MASK       ((uint32_t)0x02000000U)         /* !< Raw input select bit for PC25 */
/* XBAR_RAW_INPUTSELECT_PC[SEL26] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL26_OFS        (26)                            /* !< SEL26 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL26_MASK       ((uint32_t)0x04000000U)         /* !< Raw input select bit for PC26 */
/* XBAR_RAW_INPUTSELECT_PC[SEL27] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL27_OFS        (27)                            /* !< SEL27 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL27_MASK       ((uint32_t)0x08000000U)         /* !< Raw input select bit for PC27 */
/* XBAR_RAW_INPUTSELECT_PC[SEL28] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL28_OFS        (28)                            /* !< SEL28 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL28_MASK       ((uint32_t)0x10000000U)         /* !< Raw input select bit for PC28 */
/* XBAR_RAW_INPUTSELECT_PC[SEL29] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL29_OFS        (29)                            /* !< SEL29 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL29_MASK       ((uint32_t)0x20000000U)         /* !< Raw input select bit for PC29 */
/* XBAR_RAW_INPUTSELECT_PC[SEL30] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL30_OFS        (30)                            /* !< SEL30 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL30_MASK       ((uint32_t)0x40000000U)         /* !< Raw input select bit for PC30 */
/* XBAR_RAW_INPUTSELECT_PC[SEL31] Bits */
#define XBAR_RAW_INPUTSELECT_PC_SEL31_OFS        (31)                            /* !< SEL31 Offset */
#define XBAR_RAW_INPUTSELECT_PC_SEL31_MASK       ((uint32_t)0x80000000U)         /* !< Raw input select bit for PC31 */

/* XBAR_RAW_INPUTSELECT_PD Bits */
/* XBAR_RAW_INPUTSELECT_PD[SEL0] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL0_OFS         (0)                             /* !< SEL0 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL0_MASK        ((uint32_t)0x00000001U)         /* !< Raw input select bit for PD0 */
/* XBAR_RAW_INPUTSELECT_PD[SEL1] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL1_OFS         (1)                             /* !< SEL1 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL1_MASK        ((uint32_t)0x00000002U)         /* !< Raw input select bit for PD1 */
/* XBAR_RAW_INPUTSELECT_PD[SEL2] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL2_OFS         (2)                             /* !< SEL2 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL2_MASK        ((uint32_t)0x00000004U)         /* !< Raw input select bit for PD2 */
/* XBAR_RAW_INPUTSELECT_PD[SEL3] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL3_OFS         (3)                             /* !< SEL3 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL3_MASK        ((uint32_t)0x00000008U)         /* !< Raw input select bit for PD3 */
/* XBAR_RAW_INPUTSELECT_PD[SEL4] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL4_OFS         (4)                             /* !< SEL4 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL4_MASK        ((uint32_t)0x00000010U)         /* !< Raw input select bit for PD4 */
/* XBAR_RAW_INPUTSELECT_PD[SEL5] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL5_OFS         (5)                             /* !< SEL5 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL5_MASK        ((uint32_t)0x00000020U)         /* !< Raw input select bit for PD5 */
/* XBAR_RAW_INPUTSELECT_PD[SEL6] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL6_OFS         (6)                             /* !< SEL6 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL6_MASK        ((uint32_t)0x00000040U)         /* !< Raw input select bit for PD6 */
/* XBAR_RAW_INPUTSELECT_PD[SEL7] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL7_OFS         (7)                             /* !< SEL7 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL7_MASK        ((uint32_t)0x00000080U)         /* !< Raw input select bit for PD7 */
/* XBAR_RAW_INPUTSELECT_PD[SEL8] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL8_OFS         (8)                             /* !< SEL8 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL8_MASK        ((uint32_t)0x00000100U)         /* !< Raw input select bit for PD8 */
/* XBAR_RAW_INPUTSELECT_PD[SEL9] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL9_OFS         (9)                             /* !< SEL9 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL9_MASK        ((uint32_t)0x00000200U)         /* !< Raw input select bit for PD9 */
/* XBAR_RAW_INPUTSELECT_PD[SEL11] Bits */
#define XBAR_RAW_INPUTSELECT_PD_SEL11_OFS        (11)                            /* !< SEL11 Offset */
#define XBAR_RAW_INPUTSELECT_PD_SEL11_MASK       ((uint32_t)0x00000800U)         /* !< Raw input select bit for PD11 */


#ifdef __cplusplus
}
#endif

#endif /* hw_xbar__include */
