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

#ifndef hw_ecap__include
#define hw_ecap__include


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
* ECAP Registers
******************************************************************************/


/** @addtogroup ECAP
  @{
*/

typedef struct {
  __IO uint32_t TSCTR;                             /* !< (@ 0x00000000) Time-Stamp Counter */
  __IO uint32_t CTRPHS;                            /* !< (@ 0x00000004) Counter Phase Offset Value Register */
  __IO uint32_t CAP1;                              /* !< (@ 0x00000008) Capture 1 Register */
  __IO uint32_t CAP2;                              /* !< (@ 0x0000000C) Capture 2 Register */
  __IO uint32_t CAP3;                              /* !< (@ 0x00000010) Capture 3 Register */
  __IO uint32_t CAP4;                              /* !< (@ 0x00000014) Capture 4 Register */
       uint32_t RESERVED0[3];
  __IO uint32_t ECCTL0;                            /* !< (@ 0x00000024) Capture Control Register 0 */
  __IO uint16_t ECCTL1;                            /* !< (@ 0x00000028) Capture Control Register 1 */
  __IO uint16_t ECCTL2;                            /* !< (@ 0x0000002A) Capture Control Register 2 */
  __IO uint16_t ECEINT;                            /* !< (@ 0x0000002C) Capture Interrupt Enable Register */
  __IO uint16_t ECFLG;                             /* !< (@ 0x0000002E) Capture Interrupt Flag Register */
  __IO uint16_t ECCLR;                             /* !< (@ 0x00000030) Capture Interrupt Clear Register */
  __IO uint16_t ECFRC;                             /* !< (@ 0x00000032) Capture Interrupt Force Register */
       uint32_t RESERVED1[2];
  __IO uint32_t ECAPSYNCINSEL;                     /* !< (@ 0x0000003C) SYNC source select register */
} ECAP_Regs;

/*@}*/ /* end of group ECAP */



/******************************************************************************
* ECAP Register Offsets
******************************************************************************/
#define ECAP_TSCTR                               (0x00000000U)
#define ECAP_CTRPHS                              (0x00000004U)
#define ECAP_CAP1                                (0x00000008U)
#define ECAP_CAP2                                (0x0000000CU)
#define ECAP_CAP3                                (0x00000010U)
#define ECAP_CAP4                                (0x00000014U)
#define ECAP_ECCTL0                              (0x00000024U)
#define ECAP_ECCTL1                              (0x00000028U)
#define ECAP_ECCTL2                              (0x0000002AU)
#define ECAP_ECEINT                              (0x0000002CU)
#define ECAP_ECFLG                               (0x0000002EU)
#define ECAP_ECCLR                               (0x00000030U)
#define ECAP_ECFRC                               (0x00000032U)
#define ECAP_ECAPSYNCINSEL                       (0x0000003CU)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* ECAP Register Control Bits
******************************************************************************/

/* ECAP_TSCTR Bits */
/* ECAP_TSCTR[TSCTR] Bits */
#define ECAP_TSCTR_TSCTR_OFS                     (0)                             /* !< TSCTR Offset */
#define ECAP_TSCTR_TSCTR_MASK                    ((uint32_t)0xFFFFFFFFU)         /* !< Time Stamp Counter */

/* ECAP_CTRPHS Bits */
/* ECAP_CTRPHS[CTRPHS] Bits */
#define ECAP_CTRPHS_CTRPHS_OFS                   (0)                             /* !< CTRPHS Offset */
#define ECAP_CTRPHS_CTRPHS_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< Counter phase */

/* ECAP_CAP1 Bits */
/* ECAP_CAP1[CAP1] Bits */
#define ECAP_CAP1_CAP1_OFS                       (0)                             /* !< CAP1 Offset */
#define ECAP_CAP1_CAP1_MASK                      ((uint32_t)0xFFFFFFFFU)         /* !< Capture 1 */

/* ECAP_CAP2 Bits */
/* ECAP_CAP2[CAP2] Bits */
#define ECAP_CAP2_CAP2_OFS                       (0)                             /* !< CAP2 Offset */
#define ECAP_CAP2_CAP2_MASK                      ((uint32_t)0xFFFFFFFFU)         /* !< Capture 2 */

/* ECAP_CAP3 Bits */
/* ECAP_CAP3[CAP3] Bits */
#define ECAP_CAP3_CAP3_OFS                       (0)                             /* !< CAP3 Offset */
#define ECAP_CAP3_CAP3_MASK                      ((uint32_t)0xFFFFFFFFU)         /* !< Capture 3 */

/* ECAP_CAP4 Bits */
/* ECAP_CAP4[CAP4] Bits */
#define ECAP_CAP4_CAP4_OFS                       (0)                             /* !< CAP4 Offset */
#define ECAP_CAP4_CAP4_MASK                      ((uint32_t)0xFFFFFFFFU)         /* !< Capture 4 */

/* ECAP_ECCTL0 Bits */
/* ECAP_ECCTL0[INPUTSEL] Bits */
#define ECAP_ECCTL0_INPUTSEL_OFS                 (0)                             /* !< INPUTSEL Offset */
#define ECAP_ECCTL0_INPUTSEL_MASK                ((uint32_t)0x0000007FU)         /* !< INPUT source select */

/* ECAP_ECCTL1 Bits */
/* ECAP_ECCTL1[CAP1POL] Bits */
#define ECAP_ECCTL1_CAP1POL_OFS                  (0)                             /* !< CAP1POL Offset */
#define ECAP_ECCTL1_CAP1POL_MASK                 ((uint16_t)0x00000001U)         /* !< Capture Event 1 Polarity select */
#define ECAP_ECCTL1_CAP1POL_ECAP_CAP_EVENT1_RISE ((uint16_t)0x00000000U)         /* !< Capture Event 1 triggered on a
                                                                                    rising edge (RE) */
#define ECAP_ECCTL1_CAP1POL_ECAP_CAP_EVENT1_FALL ((uint16_t)0x00000001U)         /* !< Capture Event 1 triggered on a
                                                                                    falling edge (FE) */
/* ECAP_ECCTL1[CTRRST1] Bits */
#define ECAP_ECCTL1_CTRRST1_OFS                  (1)                             /* !< CTRRST1 Offset */
#define ECAP_ECCTL1_CTRRST1_MASK                 ((uint16_t)0x00000002U)         /* !< Counter Reset on Capture Event 1 */
#define ECAP_ECCTL1_CTRRST1_ECAP_DO_NOT_RESET_EVENT1 ((uint16_t)0x00000000U)         /* !< Do not reset counter on Capture
                                                                                    Event 1 (absolute time stamp) */
#define ECAP_ECCTL1_CTRRST1_ECAP_RESET_EVENT1    ((uint16_t)0x00000002U)         /* !< Reset counter after Event 1
                                                                                    time-stamp has been captured (used in
                                                                                    difference mode operation) */
/* ECAP_ECCTL1[CAP2POL] Bits */
#define ECAP_ECCTL1_CAP2POL_OFS                  (2)                             /* !< CAP2POL Offset */
#define ECAP_ECCTL1_CAP2POL_MASK                 ((uint16_t)0x00000004U)         /* !< Capture Event 2 Polarity select */
#define ECAP_ECCTL1_CAP2POL_ECAP_CAP_EVENT2_RISE ((uint16_t)0x00000000U)         /* !< Capture Event 2 triggered on a
                                                                                    rising edge (RE) */
#define ECAP_ECCTL1_CAP2POL_ECAP_CAP_EVENT2_FALL ((uint16_t)0x00000004U)         /* !< Capture Event 2 triggered on a
                                                                                    falling edge (FE) */
/* ECAP_ECCTL1[CTRRST2] Bits */
#define ECAP_ECCTL1_CTRRST2_OFS                  (3)                             /* !< CTRRST2 Offset */
#define ECAP_ECCTL1_CTRRST2_MASK                 ((uint16_t)0x00000008U)         /* !< Counter Reset on Capture Event 2 */
#define ECAP_ECCTL1_CTRRST2_ECAP_DO_NOT_RESET_EVENT2 ((uint16_t)0x00000000U)         /* !< Do not reset counter on Capture
                                                                                    Event 2 (absolute time stamp) */
#define ECAP_ECCTL1_CTRRST2_ECAP_RESET_EVENT2    ((uint16_t)0x00000008U)         /* !< Reset counter after Event 2
                                                                                    time-stamp has been captured (used in
                                                                                    difference mode operation) */
/* ECAP_ECCTL1[CAP3POL] Bits */
#define ECAP_ECCTL1_CAP3POL_OFS                  (4)                             /* !< CAP3POL Offset */
#define ECAP_ECCTL1_CAP3POL_MASK                 ((uint16_t)0x00000010U)         /* !< Capture Event 3 Polarity select */
#define ECAP_ECCTL1_CAP3POL_ECAP_CAP_EVENT3_RISE ((uint16_t)0x00000000U)         /* !< Capture Event 3 triggered on a
                                                                                    rising edge (RE) */
#define ECAP_ECCTL1_CAP3POL_ECAP_CAP_EVENT3_FALL ((uint16_t)0x00000010U)         /* !< Capture Event 3 triggered on a
                                                                                    falling edge (FE) */
/* ECAP_ECCTL1[CTRRST3] Bits */
#define ECAP_ECCTL1_CTRRST3_OFS                  (5)                             /* !< CTRRST3 Offset */
#define ECAP_ECCTL1_CTRRST3_MASK                 ((uint16_t)0x00000020U)         /* !< Counter Reset on Capture Event 3 */
#define ECAP_ECCTL1_CTRRST3_ECAP_DO_NOT_RESET_EVENT3 ((uint16_t)0x00000000U)         /* !< Do not reset counter on Capture
                                                                                    Event 3 (absolute time stamp) */
#define ECAP_ECCTL1_CTRRST3_ECAP_RESET_EVENT3    ((uint16_t)0x00000020U)         /* !< Reset counter after Event 3
                                                                                    time-stamp has been captured (used in
                                                                                    difference mode operation) */
/* ECAP_ECCTL1[CAP4POL] Bits */
#define ECAP_ECCTL1_CAP4POL_OFS                  (6)                             /* !< CAP4POL Offset */
#define ECAP_ECCTL1_CAP4POL_MASK                 ((uint16_t)0x00000040U)         /* !< Capture Event 4 Polarity select */
#define ECAP_ECCTL1_CAP4POL_ECAP_CAP_EVENT4_RISE ((uint16_t)0x00000000U)         /* !< Capture Event 4 triggered on a
                                                                                    rising edge (RE) */
#define ECAP_ECCTL1_CAP4POL_ECAP_CAP_EVENT4_FALL ((uint16_t)0x00000040U)         /* !< Capture Event 4 triggered on a
                                                                                    falling edge (FE) */
/* ECAP_ECCTL1[CTRRST4] Bits */
#define ECAP_ECCTL1_CTRRST4_OFS                  (7)                             /* !< CTRRST4 Offset */
#define ECAP_ECCTL1_CTRRST4_MASK                 ((uint16_t)0x00000080U)         /* !< Counter Reset on Capture Event 4 */
#define ECAP_ECCTL1_CTRRST4_ECAP_DO_NOT_RESET_EVENT4 ((uint16_t)0x00000000U)         /* !< Do not reset counter on Capture
                                                                                    Event 4 (absolute time stamp
                                                                                    operation) */
#define ECAP_ECCTL1_CTRRST4_ECAP_RESET_EVENT4    ((uint16_t)0x00000080U)         /* !< Reset counter after Capture Event 4
                                                                                    time-stamp has been captured (used in
                                                                                    difference mode operation) */
/* ECAP_ECCTL1[CAPLDEN] Bits */
#define ECAP_ECCTL1_CAPLDEN_OFS                  (8)                             /* !< CAPLDEN Offset */
#define ECAP_ECCTL1_CAPLDEN_MASK                 ((uint16_t)0x00000100U)         /* !< Enable Loading CAP1-4 regs on a Cap
                                                                                    Event */
#define ECAP_ECCTL1_CAPLDEN_ECAP_DISABLE         ((uint16_t)0x00000000U)         /* !< Disable CAP1-4 register loads at
                                                                                    capture event time. */
#define ECAP_ECCTL1_CAPLDEN_ECAP_ENABLE          ((uint16_t)0x00000100U)         /* !< Enable CAP1-4 register loads at
                                                                                    capture event time. */
/* ECAP_ECCTL1[PRESCALE] Bits */
#define ECAP_ECCTL1_PRESCALE_OFS                 (9)                             /* !< PRESCALE Offset */
#define ECAP_ECCTL1_PRESCALE_MASK                ((uint16_t)0x00003E00U)         /* !< Event Filter prescale select */
#define ECAP_ECCTL1_PRESCALE_ECAP_DIV1           ((uint16_t)0x00000000U)         /* !< Divide by 1 (i.e,. no prescale,
                                                                                    by-pass the prescaler) */
#define ECAP_ECCTL1_PRESCALE_ECAP_DIV2           ((uint16_t)0x00000200U)         /* !< Divide by 2 */
#define ECAP_ECCTL1_PRESCALE_ECAP_DIV4           ((uint16_t)0x00000400U)         /* !< Divide by 4 */
#define ECAP_ECCTL1_PRESCALE_ECAP_DIV6           ((uint16_t)0x00000600U)         /* !< Divide by 6 */
#define ECAP_ECCTL1_PRESCALE_ECAP_DIV8           ((uint16_t)0x00000800U)         /* !< Divide by 8 */
#define ECAP_ECCTL1_PRESCALE_ECAP_DIV10          ((uint16_t)0x00000A00U)         /* !< Divide by 10 */
#define ECAP_ECCTL1_PRESCALE_ECAP_DIV60          ((uint16_t)0x00003C00U)         /* !< Divide by 60 */
#define ECAP_ECCTL1_PRESCALE_ECAP_DIV62          ((uint16_t)0x00003E00U)         /* !< Divide by 62 */
/* ECAP_ECCTL1[FREE_SOFT] Bits */
#define ECAP_ECCTL1_FREE_SOFT_OFS                (14)                            /* !< FREE_SOFT Offset */
#define ECAP_ECCTL1_FREE_SOFT_MASK               ((uint16_t)0x0000C000U)         /* !< Emulation mode */
#define ECAP_ECCTL1_FREE_SOFT_ECAP_STOP_EMU      ((uint16_t)0x00000000U)         /* !< TSCTR counter stops immediately on
                                                                                    emulation suspend */
#define ECAP_ECCTL1_FREE_SOFT_ECAP_RUNS_UNTIL    ((uint16_t)0x00004000U)         /* !< TSCTR counter runs until = 0 */
#define ECAP_ECCTL1_FREE_SOFT_ECAP_UNAF_EMU_SUS  ((uint16_t)0x00008000U)         /* !< TSCTR counter is unaffected by
                                                                                    emulation suspend (Run Free) */
#define ECAP_ECCTL1_FREE_SOFT_ECAP_UNAF_EMU_SUS2 ((uint16_t)0x0000C000U)         /* !< TSCTR counter is unaffected by
                                                                                    emulation suspend (Run Free) */

/* ECAP_ECCTL2 Bits */
/* ECAP_ECCTL2[CONT_ONESHT] Bits */
#define ECAP_ECCTL2_CONT_ONESHT_OFS              (0)                             /* !< CONT_ONESHT Offset */
#define ECAP_ECCTL2_CONT_ONESHT_MASK             ((uint16_t)0x00000001U)         /* !< Continuous or one-shot */
#define ECAP_ECCTL2_CONT_ONESHT_ECAP_OPP_CONT    ((uint16_t)0x00000000U)         /* !< Operate in continuous mode */
#define ECAP_ECCTL2_CONT_ONESHT_ECAP_OPP_ONE     ((uint16_t)0x00000001U)         /* !< Operate in one-Shot mode */
/* ECAP_ECCTL2[STOP_WRAP] Bits */
#define ECAP_ECCTL2_STOP_WRAP_OFS                (1)                             /* !< STOP_WRAP Offset */
#define ECAP_ECCTL2_STOP_WRAP_MASK               ((uint16_t)0x00000006U)         /* !< Stop value for one-shot, Wrap for
                                                                                    continuous */
#define ECAP_ECCTL2_STOP_WRAP_ECAP_STOPEVENT1_WRAPEVENT2 ((uint16_t)0x00000000U)         /* !< Stop after Capture Event 1 in
                                                                                    one-shot mode #br#Wrap after Capture
                                                                                    Event 1 in continuous mode. */
#define ECAP_ECCTL2_STOP_WRAP_ECAP_STOPEVENT2_WRAPEVENT2 ((uint16_t)0x00000002U)         /* !< Stop after Capture Event 2 in
                                                                                    one-shot mode #br#Wrap after Capture
                                                                                    Event 2 in continuous mode. */
#define ECAP_ECCTL2_STOP_WRAP_ECAP_STOPEVENT3_WRAPEVENT2 ((uint16_t)0x00000004U)         /* !< Stop after Capture Event 3 in
                                                                                    one-shot mode #br#Wrap after Capture
                                                                                    Event 3 in continuous mode. */
#define ECAP_ECCTL2_STOP_WRAP_ECAP_STOPEVENT4_WRAPEVENT2 ((uint16_t)0x00000006U)         /* !< Stop after Capture Event 4 in
                                                                                    one-shot mode #br#Wrap after Capture
                                                                                    Event 4 in continuous mode. */
/* ECAP_ECCTL2[REARM] Bits */
#define ECAP_ECCTL2_REARM_OFS                    (3)                             /* !< REARM Offset */
#define ECAP_ECCTL2_REARM_MASK                   ((uint16_t)0x00000008U)         /* !< One-shot re-arm */
#define ECAP_ECCTL2_REARM_ECAP_NO_EFFECT_RETURNS_0 ((uint16_t)0x00000000U)         /* !< Has no effect (reading always
                                                                                    returns a 0) */
#define ECAP_ECCTL2_REARM_ECAP_ARMS_ONESHOT      ((uint16_t)0x00000008U)         /* !< Arms the one-shot sequence as
                                                                                    follows: #br#1) Resets the Mod4
                                                                                    counter to zero #br#2) Unfreezes the
                                                                                    Mod4 counter #br#3) Enables capture
                                                                                    register loads */
/* ECAP_ECCTL2[TSCTRSTOP] Bits */
#define ECAP_ECCTL2_TSCTRSTOP_OFS                (4)                             /* !< TSCTRSTOP Offset */
#define ECAP_ECCTL2_TSCTRSTOP_MASK               ((uint16_t)0x00000010U)         /* !< TSCNT counter stop */
#define ECAP_ECCTL2_TSCTRSTOP_ECAP_TSCTR_STOPPED ((uint16_t)0x00000000U)         /* !< TSCTR stopped */
#define ECAP_ECCTL2_TSCTRSTOP_ECAP_TSCTR_FREE_RUNNING ((uint16_t)0x00000010U)         /* !< TSCTR free-running */
/* ECAP_ECCTL2[SYNCI_EN] Bits */
#define ECAP_ECCTL2_SYNCI_EN_OFS                 (5)                             /* !< SYNCI_EN Offset */
#define ECAP_ECCTL2_SYNCI_EN_MASK                ((uint16_t)0x00000020U)         /* !< Counter sync-in select */
#define ECAP_ECCTL2_SYNCI_EN_ECAP_DISABLE_SYNC_IN ((uint16_t)0x00000000U)         /* !< Disable sync-in option */
#define ECAP_ECCTL2_SYNCI_EN_ECAP_ENABLE_COUNTER_REGISTER ((uint16_t)0x00000020U)         /* !< Enable counter (TSCTR) to be loaded
                                                                                    from CTRPHS register upon either a
                                                                                    SYNCI signal or a S/W force event. */
/* ECAP_ECCTL2[SYNCO_SEL] Bits */
#define ECAP_ECCTL2_SYNCO_SEL_OFS                (6)                             /* !< SYNCO_SEL Offset */
#define ECAP_ECCTL2_SYNCO_SEL_MASK               ((uint16_t)0x000000C0U)         /* !< Sync-out mode */
#define ECAP_ECCTL2_SYNCO_SEL_SWSYNC             ((uint16_t)0x00000000U)         /* !< sync out signal is SWSYNC */
#define ECAP_ECCTL2_SYNCO_SEL_ECAP_CTR_PRD_TO_SYNCOUT ((uint16_t)0x00000040U)         /* !< Select CTR = PRD event to be the
                                                                                    sync-out signal. Note: Selection CTR
                                                                                    = PRD is meaningful only in APWM mode */
#define ECAP_ECCTL2_SYNCO_SEL_ECAP_DISABLE_SYNC_OUT ((uint16_t)0x00000080U)         /* !< Disable sync out signal */
/* ECAP_ECCTL2[SWSYNC] Bits */
#define ECAP_ECCTL2_SWSYNC_OFS                   (8)                             /* !< SWSYNC Offset */
#define ECAP_ECCTL2_SWSYNC_MASK                  ((uint16_t)0x00000100U)         /* !< SW forced counter sync */
#define ECAP_ECCTL2_SWSYNC_ECAP_ZERO_NOEFFECT    ((uint16_t)0x00000000U)         /* !< Writing a zero has no effect.
                                                                                    Reading always returns a zero */
#define ECAP_ECCTL2_SWSYNC_ECAP_WRITE_TSCTR      ((uint16_t)0x00000100U)         /* !< Writing a one forces a TSCTR shadow
                                                                                    load of current ECAP module and any
                                                                                    ECAP modules down-stream providing
                                                                                    the SYNCO_SEL bits are 0,0. After
                                                                                    writing a 1, this bit returns to a
                                                                                    zero. */
/* ECAP_ECCTL2[CAP_APWM] Bits */
#define ECAP_ECCTL2_CAP_APWM_OFS                 (9)                             /* !< CAP_APWM Offset */
#define ECAP_ECCTL2_CAP_APWM_MASK                ((uint16_t)0x00000200U)         /* !< CAP/APWM operating mode select */
#define ECAP_ECCTL2_CAP_APWM_ECAP_MODULE         ((uint16_t)0x00000000U)         /* !< ECAP module operates in capture
                                                                                    mode. This mode forces the following
                                                                                    configuration: #br#- Inhibits TSCTR
                                                                                    resets via CTR = PRD event #br#-
                                                                                    Inhibits shadow loads on CAP1 and 2
                                                                                    registers #br#- Permits user to
                                                                                    enable CAP1-4 register load #br#-
                                                                                    CAPx/APWMx pin operates as a capture
                                                                                    input */
#define ECAP_ECCTL2_CAP_APWM_ECAP_MODULE_APWM    ((uint16_t)0x00000200U)         /* !< ECAP module operates in APWM mode.
                                                                                    This mode forces the following
                                                                                    configuration: #br#- Resets TSCTR on
                                                                                    CTR = PRD event (period boundary
                                                                                    #br#- Permits shadow loading on CAP1
                                                                                    and 2 registers #br#- Disables
                                                                                    loading of time-stamps into CAP1-4
                                                                                    registers #br#- CAPx/APWMx pin
                                                                                    operates as a APWM output */
/* ECAP_ECCTL2[APWMPOL] Bits */
#define ECAP_ECCTL2_APWMPOL_OFS                  (10)                            /* !< APWMPOL Offset */
#define ECAP_ECCTL2_APWMPOL_MASK                 ((uint16_t)0x00000400U)         /* !< APWM output polarity select */
#define ECAP_ECCTL2_APWMPOL_ECAP_OUTPUT_ACTIVE_HIGH ((uint16_t)0x00000000U)         /* !< Output is active high (Compare
                                                                                    value defines high time) */
#define ECAP_ECCTL2_APWMPOL_ECAP_OUTPUT_ACTIVE_LOW ((uint16_t)0x00000400U)         /* !< Output is active low (Compare value
                                                                                    defines low time) */
/* ECAP_ECCTL2[CTRFILTRESET] Bits */
#define ECAP_ECCTL2_CTRFILTRESET_OFS             (11)                            /* !< CTRFILTRESET Offset */
#define ECAP_ECCTL2_CTRFILTRESET_MASK            ((uint16_t)0x00000800U)         /* !< Reset event filter, modulus
                                                                                    counter, and interrupt flags. */
/* ECAP_ECCTL2[DMAEVTSEL] Bits */
#define ECAP_ECCTL2_DMAEVTSEL_OFS                (12)                            /* !< DMAEVTSEL Offset */
#define ECAP_ECCTL2_DMAEVTSEL_MASK               ((uint16_t)0x00003000U)         /* !< DMA event select */
/* ECAP_ECCTL2[MODCNTRSTS] Bits */
#define ECAP_ECCTL2_MODCNTRSTS_OFS               (14)                            /* !< MODCNTRSTS Offset */
#define ECAP_ECCTL2_MODCNTRSTS_MASK              ((uint16_t)0x0000C000U)         /* !< modulo counter status */

/* ECAP_ECEINT Bits */
/* ECAP_ECEINT[CEVT1] Bits */
#define ECAP_ECEINT_CEVT1_OFS                    (1)                             /* !< CEVT1 Offset */
#define ECAP_ECEINT_CEVT1_MASK                   ((uint16_t)0x00000002U)         /* !< Capture Event 1 Interrupt Enable */
#define ECAP_ECEINT_CEVT1_ECAP_DISAB_CAP1_INTERRUPT ((uint16_t)0x00000000U)         /* !< Disable Capture Event 1 as an
                                                                                    Interrupt source */
#define ECAP_ECEINT_CEVT1_ECAP_ENAB_CAP1_INTERRUPT ((uint16_t)0x00000002U)         /* !< Enable Capture Event 1 as an
                                                                                    Interrupt source */
/* ECAP_ECEINT[CEVT2] Bits */
#define ECAP_ECEINT_CEVT2_OFS                    (2)                             /* !< CEVT2 Offset */
#define ECAP_ECEINT_CEVT2_MASK                   ((uint16_t)0x00000004U)         /* !< Capture Event 2 Interrupt Enable */
#define ECAP_ECEINT_CEVT2_ECAP_DISAB_CAP2_INTERRUPT ((uint16_t)0x00000000U)         /* !< Disable Capture Event 2 as an
                                                                                    Interrupt source */
#define ECAP_ECEINT_CEVT2_ECAP_ENAB_CAP2_INTERRUPT ((uint16_t)0x00000004U)         /* !< Enable Capture Event 2 as an
                                                                                    Interrupt source */
/* ECAP_ECEINT[CEVT3] Bits */
#define ECAP_ECEINT_CEVT3_OFS                    (3)                             /* !< CEVT3 Offset */
#define ECAP_ECEINT_CEVT3_MASK                   ((uint16_t)0x00000008U)         /* !< Capture Event 3 Interrupt Enable */
#define ECAP_ECEINT_CEVT3_ECAP_DISAB_CAP3_INTERRUPT ((uint16_t)0x00000000U)         /* !< Disable Capture Event 3 as an
                                                                                    Interrupt source */
#define ECAP_ECEINT_CEVT3_ECAP_ENAB_CAP3_INTERRUPT ((uint16_t)0x00000008U)         /* !< Enable Capture Event 3 as an
                                                                                    Interrupt source */
/* ECAP_ECEINT[CEVT4] Bits */
#define ECAP_ECEINT_CEVT4_OFS                    (4)                             /* !< CEVT4 Offset */
#define ECAP_ECEINT_CEVT4_MASK                   ((uint16_t)0x00000010U)         /* !< Capture Event 4 Interrupt Enable */
#define ECAP_ECEINT_CEVT4_ECAP_DISAB_CAP4_INTERRUPT ((uint16_t)0x00000000U)         /* !< Disable Capture Event 4 as an
                                                                                    Interrupt source */
#define ECAP_ECEINT_CEVT4_ECAP_ENAB_CAP4_INTERRUPT ((uint16_t)0x00000010U)         /* !< Capture Event 4 Interrupt Enable */
/* ECAP_ECEINT[CTROVF] Bits */
#define ECAP_ECEINT_CTROVF_OFS                   (5)                             /* !< CTROVF Offset */
#define ECAP_ECEINT_CTROVF_MASK                  ((uint16_t)0x00000020U)         /* !< Counter Overflow Interrupt Enable */
#define ECAP_ECEINT_CTROVF_ECAP_DISAB_CO_INTERRUPT ((uint16_t)0x00000000U)         /* !< Disabled counter Overflow as an
                                                                                    Interrupt source */
#define ECAP_ECEINT_CTROVF_ECAP_ENAB_CO_INTERRUPT ((uint16_t)0x00000020U)         /* !< Enable counter Overflow as an
                                                                                    Interrupt source */
/* ECAP_ECEINT[CTR_EQ_PRD] Bits */
#define ECAP_ECEINT_CTR_EQ_PRD_OFS               (6)                             /* !< CTR_EQ_PRD Offset */
#define ECAP_ECEINT_CTR_EQ_PRD_MASK              ((uint16_t)0x00000040U)         /* !< Period Equal Interrupt Enable */
#define ECAP_ECEINT_CTR_EQ_PRD_ECAP_DISAB_PE_INTERRUPT ((uint16_t)0x00000000U)         /* !< Disable Period Equal as an
                                                                                    Interrupt source */
#define ECAP_ECEINT_CTR_EQ_PRD_ECAP_ENAB_PE_INTERRUPT ((uint16_t)0x00000040U)         /* !< Enable Period Equal as an Interrupt
                                                                                    source */
/* ECAP_ECEINT[CTR_EQ_CMP] Bits */
#define ECAP_ECEINT_CTR_EQ_CMP_OFS               (7)                             /* !< CTR_EQ_CMP Offset */
#define ECAP_ECEINT_CTR_EQ_CMP_MASK              ((uint16_t)0x00000080U)         /* !< Compare Equal Interrupt Enable */
#define ECAP_ECEINT_CTR_EQ_CMP_ECAP_DISAB_CE_INTERRUPT ((uint16_t)0x00000000U)         /* !< Disable Compare Equal as an
                                                                                    Interrupt source */
#define ECAP_ECEINT_CTR_EQ_CMP_ECAP_ENAB_CE_INTERRUPT ((uint16_t)0x00000080U)         /* !< Enable Compare Equal as an
                                                                                    Interrupt source */

/* ECAP_ECFLG Bits */
/* ECAP_ECFLG[INT] Bits */
#define ECAP_ECFLG_INT_OFS                       (0)                             /* !< INT Offset */
#define ECAP_ECFLG_INT_MASK                      ((uint16_t)0x00000001U)         /* !< Global Flag */
#define ECAP_ECFLG_INT_ECAP_INDICATE_NO_EVENT    ((uint16_t)0x00000000U)         /* !< Indicates no event occurred */
#define ECAP_ECFLG_INT_ECAP_INDICATE_INTERRUPT   ((uint16_t)0x00000001U)         /* !< Indicates that an interrupt was
                                                                                    generated. */
/* ECAP_ECFLG[CEVT1] Bits */
#define ECAP_ECFLG_CEVT1_OFS                     (1)                             /* !< CEVT1 Offset */
#define ECAP_ECFLG_CEVT1_MASK                    ((uint16_t)0x00000002U)         /* !< Capture Event 1 Interrupt Flag */
#define ECAP_ECFLG_CEVT1_ECAP_INDICATE_NO_EVENT  ((uint16_t)0x00000000U)         /* !< Indicates no event occurred */
#define ECAP_ECFLG_CEVT1_ECAP_INDICATE_1ST_EVENT_ECAPX ((uint16_t)0x00000002U)         /* !< Indicates the first event occurred
                                                                                    at ECAPx pin. */
/* ECAP_ECFLG[CEVT2] Bits */
#define ECAP_ECFLG_CEVT2_OFS                     (2)                             /* !< CEVT2 Offset */
#define ECAP_ECFLG_CEVT2_MASK                    ((uint16_t)0x00000004U)         /* !< Capture Event 2 Interrupt Flag */
#define ECAP_ECFLG_CEVT2_ECAP_INDICATE_NO_EVENT  ((uint16_t)0x00000000U)         /* !< Indicates no event occurred */
#define ECAP_ECFLG_CEVT2_ECAP_INDICATE_2ND_EVENT_ECAPX ((uint16_t)0x00000004U)         /* !< Indicates the second event occurred
                                                                                    at ECAPx pin. */
/* ECAP_ECFLG[CEVT3] Bits */
#define ECAP_ECFLG_CEVT3_OFS                     (3)                             /* !< CEVT3 Offset */
#define ECAP_ECFLG_CEVT3_MASK                    ((uint16_t)0x00000008U)         /* !< Capture Event 3 Interrupt Flag */
#define ECAP_ECFLG_CEVT3_ECAP_INDICATE_NO_EVENT  ((uint16_t)0x00000000U)         /* !< Indicates no event occurred */
#define ECAP_ECFLG_CEVT3_ECAP_INDICATE_3RD_EVENT_ECAPX ((uint16_t)0x00000008U)         /* !< Indicates the third event occurred
                                                                                    at ECAPx pin. */
/* ECAP_ECFLG[CEVT4] Bits */
#define ECAP_ECFLG_CEVT4_OFS                     (4)                             /* !< CEVT4 Offset */
#define ECAP_ECFLG_CEVT4_MASK                    ((uint16_t)0x00000010U)         /* !< Capture Event 4 Interrupt Flag */
#define ECAP_ECFLG_CEVT4_ECAP_INDICATE_NO_EVENT  ((uint16_t)0x00000000U)         /* !< Indicates no event occurred */
#define ECAP_ECFLG_CEVT4_ECAP_INDICATE_4TH_EVENT_ECAPX ((uint16_t)0x00000010U)         /* !< Indicates the fourth event occurred
                                                                                    at ECAPx pin */
/* ECAP_ECFLG[CTROVF] Bits */
#define ECAP_ECFLG_CTROVF_OFS                    (5)                             /* !< CTROVF Offset */
#define ECAP_ECFLG_CTROVF_MASK                   ((uint16_t)0x00000020U)         /* !< Counter Overflow Interrupt Flag */
#define ECAP_ECFLG_CTROVF_ECAP_INDICATE_NO_EVENT ((uint16_t)0x00000000U)         /* !< Indicates no event occurred */
#define ECAP_ECFLG_CTROVF_ECAP_INDICATE_COUNTER_TRANS ((uint16_t)0x00000020U)         /* !< Indicates the counter (TSCTR) has
                                                                                    made the transition from FFFFFFFF to
                                                                                    00000000 */
/* ECAP_ECFLG[CTR_PRD] Bits */
#define ECAP_ECFLG_CTR_PRD_OFS                   (6)                             /* !< CTR_PRD Offset */
#define ECAP_ECFLG_CTR_PRD_MASK                  ((uint16_t)0x00000040U)         /* !< Period Equal Interrupt Flag */
#define ECAP_ECFLG_CTR_PRD_ECAP_INDICATE_NO_EVENT ((uint16_t)0x00000000U)         /* !< Indicates no event occurred */
#define ECAP_ECFLG_CTR_PRD_ECAP_INDICATE_PERIOD_VALUE_RESET ((uint16_t)0x00000040U)         /* !< Indicates the counter (TSCTR)
                                                                                    reached the period register value
                                                                                    (APRD) and was reset. */
/* ECAP_ECFLG[CTR_CMP] Bits */
#define ECAP_ECFLG_CTR_CMP_OFS                   (7)                             /* !< CTR_CMP Offset */
#define ECAP_ECFLG_CTR_CMP_MASK                  ((uint16_t)0x00000080U)         /* !< Compare Equal Interrupt Flag */
#define ECAP_ECFLG_CTR_CMP_ECAP_INDICATE_NO_EVENT ((uint16_t)0x00000000U)         /* !< Indicates no event occurred */
#define ECAP_ECFLG_CTR_CMP_ECAP_INDICATE_COUNTER_COMPARE_REG ((uint16_t)0x00000080U)         /* !< Indicates the counter (TSCTR)
                                                                                    reached the compare register value
                                                                                    (ACMP) */

/* ECAP_ECCLR Bits */
/* ECAP_ECCLR[INT] Bits */
#define ECAP_ECCLR_INT_OFS                       (0)                             /* !< INT Offset */
#define ECAP_ECCLR_INT_MASK                      ((uint16_t)0x00000001U)         /* !< ECAP Global Interrupt Status Clear */
#define ECAP_ECCLR_INT_ECAP_0_NO_EFFECT          ((uint16_t)0x00000000U)         /* !< Writing a 0 has no effect. Always
                                                                                    reads back a 0 */
#define ECAP_ECCLR_INT_ECAP_1_CLEARS_INT         ((uint16_t)0x00000001U)         /* !< Writing a 1 clears the INT flag and
                                                                                    enable further interrupts to be
                                                                                    generated if any of the event flags
                                                                                    are set to 1 */
/* ECAP_ECCLR[CEVT1] Bits */
#define ECAP_ECCLR_CEVT1_OFS                     (1)                             /* !< CEVT1 Offset */
#define ECAP_ECCLR_CEVT1_MASK                    ((uint16_t)0x00000002U)         /* !< Capture Event 1 Status Clear */
#define ECAP_ECCLR_CEVT1_ECAP_0_NO_EFFECT        ((uint16_t)0x00000000U)         /* !< Writing a 0 has no effect. Always
                                                                                    reads back a 0 */
#define ECAP_ECCLR_CEVT1_ECAP_1_CLEARS_CEVT1     ((uint16_t)0x00000002U)         /* !< Writing a 1 clears the CEVT1 flag. */
/* ECAP_ECCLR[CEVT2] Bits */
#define ECAP_ECCLR_CEVT2_OFS                     (2)                             /* !< CEVT2 Offset */
#define ECAP_ECCLR_CEVT2_MASK                    ((uint16_t)0x00000004U)         /* !< Capture Event 2 Status Clear */
#define ECAP_ECCLR_CEVT2_ECAP_0_NO_EFFECT        ((uint16_t)0x00000000U)         /* !< Writing a 0 has no effect. Always
                                                                                    reads back a 0 */
#define ECAP_ECCLR_CEVT2_ECAP_1_CLEARS_CEVT2     ((uint16_t)0x00000004U)         /* !< Writing a 1 clears the CEVT2 flag. */
/* ECAP_ECCLR[CEVT3] Bits */
#define ECAP_ECCLR_CEVT3_OFS                     (3)                             /* !< CEVT3 Offset */
#define ECAP_ECCLR_CEVT3_MASK                    ((uint16_t)0x00000008U)         /* !< Capture Event 3 Status Clear */
#define ECAP_ECCLR_CEVT3_ECAP_0_NO_EFFECT        ((uint16_t)0x00000000U)         /* !< Writing a 0 has no effect. Always
                                                                                    reads back a 0 */
#define ECAP_ECCLR_CEVT3_ECAP_1_CLEARS_CEVT3     ((uint16_t)0x00000008U)         /* !< Writing a 1 clears the CEVT3 flag. */
/* ECAP_ECCLR[CEVT4] Bits */
#define ECAP_ECCLR_CEVT4_OFS                     (4)                             /* !< CEVT4 Offset */
#define ECAP_ECCLR_CEVT4_MASK                    ((uint16_t)0x00000010U)         /* !< Capture Event 4 Status Clear */
#define ECAP_ECCLR_CEVT4_ECAP_0_NO_EFFECT        ((uint16_t)0x00000000U)         /* !< Writing a 0 has no effect. Always
                                                                                    reads back a 0 */
#define ECAP_ECCLR_CEVT4_ECAP_1_CLEARS_CEVT4     ((uint16_t)0x00000010U)         /* !< Writing a 1 clears the CEVT4 flag. */
/* ECAP_ECCLR[CTROVF] Bits */
#define ECAP_ECCLR_CTROVF_OFS                    (5)                             /* !< CTROVF Offset */
#define ECAP_ECCLR_CTROVF_MASK                   ((uint16_t)0x00000020U)         /* !< Counter Overflow Status Clear */
#define ECAP_ECCLR_CTROVF_ECAP_0_NO_EFFECT       ((uint16_t)0x00000000U)         /* !< Writing a 0 has no effect. Always
                                                                                    reads back a 0 */
#define ECAP_ECCLR_CTROVF_ECAP_1_CLEARS_CTROVF   ((uint16_t)0x00000020U)         /* !< Writing a 1 clears the CTROVF flag. */
/* ECAP_ECCLR[CTR_PRD] Bits */
#define ECAP_ECCLR_CTR_PRD_OFS                   (6)                             /* !< CTR_PRD Offset */
#define ECAP_ECCLR_CTR_PRD_MASK                  ((uint16_t)0x00000040U)         /* !< Period Equal Status Clear */
#define ECAP_ECCLR_CTR_PRD_ECAP_0_NO_EFFECT      ((uint16_t)0x00000000U)         /* !< Writing a 0 has no effect. Always
                                                                                    reads back a 0 */
#define ECAP_ECCLR_CTR_PRD_ECAP_1_CLEARS_CTR_PRD ((uint16_t)0x00000040U)         /* !< Writing a 1 clears the CTR=PRD
                                                                                    flag. */
/* ECAP_ECCLR[CTR_CMP] Bits */
#define ECAP_ECCLR_CTR_CMP_OFS                   (7)                             /* !< CTR_CMP Offset */
#define ECAP_ECCLR_CTR_CMP_MASK                  ((uint16_t)0x00000080U)         /* !< Compare Equal Status Clear */
#define ECAP_ECCLR_CTR_CMP_ECAP_0_NO_EFFECT      ((uint16_t)0x00000000U)         /* !< Writing a 0 has no effect. Always
                                                                                    reads back a 0 */
#define ECAP_ECCLR_CTR_CMP_ECAP_1_CLEARS_CTR_CMP ((uint16_t)0x00000080U)         /* !< Writing a 1 clears the CTR=CMP
                                                                                    flag. */

/* ECAP_ECFRC Bits */
/* ECAP_ECFRC[CEVT1] Bits */
#define ECAP_ECFRC_CEVT1_OFS                     (1)                             /* !< CEVT1 Offset */
#define ECAP_ECFRC_CEVT1_MASK                    ((uint16_t)0x00000002U)         /* !< Capture Event 1 Force Interrupt */
#define ECAP_ECFRC_CEVT1_ECAP_NO_EFFECT_0        ((uint16_t)0x00000000U)         /* !< No effect. Always reads back a 0. */
#define ECAP_ECFRC_CEVT1_ECAP_1_SETS_CEVT1       ((uint16_t)0x00000002U)         /* !< Sets the CEVT1 flag. */
/* ECAP_ECFRC[CEVT2] Bits */
#define ECAP_ECFRC_CEVT2_OFS                     (2)                             /* !< CEVT2 Offset */
#define ECAP_ECFRC_CEVT2_MASK                    ((uint16_t)0x00000004U)         /* !< Capture Event 2 Force Interrupt */
#define ECAP_ECFRC_CEVT2_ECAP_NO_EFFECT_0        ((uint16_t)0x00000000U)         /* !< No effect. Always reads back a 0. */
#define ECAP_ECFRC_CEVT2_ECAP_1_SETS_CEVT2       ((uint16_t)0x00000004U)         /* !< Writing a 1 sets the CEVT2 flag. */
/* ECAP_ECFRC[CEVT3] Bits */
#define ECAP_ECFRC_CEVT3_OFS                     (3)                             /* !< CEVT3 Offset */
#define ECAP_ECFRC_CEVT3_MASK                    ((uint16_t)0x00000008U)         /* !< Capture Event 3 Force Interrupt */
#define ECAP_ECFRC_CEVT3_ECAP_NO_EFFECT_0        ((uint16_t)0x00000000U)         /* !< No effect. Always reads back a 0. */
#define ECAP_ECFRC_CEVT3_ECAP_1_SETS_CEVT3       ((uint16_t)0x00000008U)         /* !< Writing a 1 sets the CEVT3 flag. */
/* ECAP_ECFRC[CEVT4] Bits */
#define ECAP_ECFRC_CEVT4_OFS                     (4)                             /* !< CEVT4 Offset */
#define ECAP_ECFRC_CEVT4_MASK                    ((uint16_t)0x00000010U)         /* !< Capture Event 4 Force Interrupt */
#define ECAP_ECFRC_CEVT4_ECAP_NO_EFFECT_0        ((uint16_t)0x00000000U)         /* !< No effect. Always reads back a 0. */
#define ECAP_ECFRC_CEVT4_ECAP_1_SETS_CEVT4       ((uint16_t)0x00000010U)         /* !< Writing a 1 sets the CEVT4 flag. */
/* ECAP_ECFRC[CTROVF] Bits */
#define ECAP_ECFRC_CTROVF_OFS                    (5)                             /* !< CTROVF Offset */
#define ECAP_ECFRC_CTROVF_MASK                   ((uint16_t)0x00000020U)         /* !< Counter Overflow Force Interrupt */
#define ECAP_ECFRC_CTROVF_ECAP_NO_EFFECT_0       ((uint16_t)0x00000000U)         /* !< No effect. Always reads back a 0. */
#define ECAP_ECFRC_CTROVF_ECAP_1_SETS_CTROVF     ((uint16_t)0x00000020U)         /* !< Writing a 1 to this bit sets the
                                                                                    CTROVF flag. */
/* ECAP_ECFRC[CTR_PRD] Bits */
#define ECAP_ECFRC_CTR_PRD_OFS                   (6)                             /* !< CTR_PRD Offset */
#define ECAP_ECFRC_CTR_PRD_MASK                  ((uint16_t)0x00000040U)         /* !< Period Equal Force Interrupt */
#define ECAP_ECFRC_CTR_PRD_ECAP_NO_EFFECT_0      ((uint16_t)0x00000000U)         /* !< No effect. Always reads back a 0. */
#define ECAP_ECFRC_CTR_PRD_ECAP_1_CLEARS_CTR_PRD ((uint16_t)0x00000040U)         /* !< Writing a 1 sets the CTR_PRD flag. */
/* ECAP_ECFRC[CTR_CMP] Bits */
#define ECAP_ECFRC_CTR_CMP_OFS                   (7)                             /* !< CTR_CMP Offset */
#define ECAP_ECFRC_CTR_CMP_MASK                  ((uint16_t)0x00000080U)         /* !< Compare Equal Force Interrupt */
#define ECAP_ECFRC_CTR_CMP_ECAP_NO_EFFECT_0      ((uint16_t)0x00000000U)         /* !< No effect. Always reads back a 0. */
#define ECAP_ECFRC_CTR_CMP_ECAP_1_SETS_CTR_CMP   ((uint16_t)0x00000080U)         /* !< Writing a 1 sets the CTR_CMP flag. */

/* ECAP_ECAPSYNCINSEL Bits */
/* ECAP_ECAPSYNCINSEL[SEL] Bits */
#define ECAP_ECAPSYNCINSEL_SEL_OFS               (0)                             /* !< SEL Offset */
#define ECAP_ECAPSYNCINSEL_SEL_MASK              ((uint32_t)0x0000001FU)         /* !< SYNCIN source select */


#ifdef __cplusplus
}
#endif

#endif /* hw_ecap__include */

