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

#ifndef hw_mcpwm__include
#define hw_mcpwm__include


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
* MCPWM Registers
******************************************************************************/


/** @addtogroup MCPWM
  @{
*/

typedef struct {
  __IO uint32_t REVISION;                          /* !< (@ 0x00000000) IP revision id register */
       uint32_t RESERVED0[3];
  __IO uint32_t TBCTL;                             /* !< (@ 0x00000010) Time base control register */
  __IO uint32_t TBPRD;                             /* !< (@ 0x00000014) Time base period register */
  __IO uint32_t TBPRDS;                            /* !< (@ 0x00000018) Time base period shadow register */
  __IO uint32_t TBPHS;                             /* !< (@ 0x0000001C) Time base phase offset register */
  __IO uint32_t TBSTS;                             /* !< (@ 0x00000020) Time base status register */
  __IO uint32_t TBSTSCLR;                          /* !< (@ 0x00000024) Time base status clear register */
  __IO uint32_t TBCTR;                             /* !< (@ 0x00000028) Time base counter register */
       uint32_t RESERVED1;
  __IO uint32_t CMPCTL;                            /* !< (@ 0x00000030) Counter compare control register */
       uint32_t RESERVED2[3];
  __IO uint32_t CMPC;                              /* !< (@ 0x00000040) Counter compare C register */
  __IO uint32_t CMPD;                              /* !< (@ 0x00000044) Counter compare D register */
  __IO uint32_t CMPCS;                             /* !< (@ 0x00000048) Counter compare C shadow register */
  __IO uint32_t CMPDS;                             /* !< (@ 0x0000004C) Counter compare D shadow register */
  __IO uint32_t AQCTL;                             /* !< (@ 0x00000050) Action qualifier control register */
       uint32_t RESERVED3[3];
  __IO uint32_t SOCEN;                             /* !< (@ 0x00000060) Start of conversion enable */
  __IO uint32_t SOCSEL;                            /* !< (@ 0x00000064) Start of conversion selection */
  __IO uint32_t SOCPERIOD;                         /* !< (@ 0x00000068) Start of conversion period */
  __IO uint32_t SOCCNT;                            /* !< (@ 0x0000006C) Start of conversion count */
  __IO uint32_t SOCFLAG;                           /* !< (@ 0x00000070) Start of conversion flag */
  __IO uint32_t SOCCLR;                            /* !< (@ 0x00000074) Start of conversion clear */
       uint32_t RESERVED4[2];
  __IO uint32_t ETSEL;                             /* !< (@ 0x00000080) Event trigger selection */
  __IO uint32_t ETPERIOD;                          /* !< (@ 0x00000084) Event trigger period */
  __IO uint32_t ETCNT;                             /* !< (@ 0x00000088) Event trigger count */
       uint32_t RESERVED5;
  __IO uint32_t INTEN;                             /* !< (@ 0x00000090) Interrupt enable */
  __IO uint32_t INTFLAG;                           /* !< (@ 0x00000094) Interrupt flag */
  __IO uint32_t INTCLR;                            /* !< (@ 0x00000098) Interrupt clear */
  __IO uint32_t INTFRC;                            /* !< (@ 0x0000009C) Interrupt force */
  __IO uint32_t TZSEL;                             /* !< (@ 0x000000A0) Trip Zone selection */
       uint32_t RESERVED6[2];
  __IO uint32_t TZCTL;                             /* !< (@ 0x000000AC) Trip Zone control */
  __IO uint32_t TZCBCOSTFLAG;                      /* !< (@ 0x000000B0) Trip zone CBCOST flag */
  __IO uint32_t TZCBCOSTCLR;                       /* !< (@ 0x000000B4) Trip zone CBCOST flag clear */
       uint32_t RESERVED7[2];
  __IO uint32_t DBCTL;                             /* !< (@ 0x000000C0) Dead band control register */
       uint32_t RESERVED8[3];
  __IO uint32_t DBFED;                             /* !< (@ 0x000000D0) Dead band fall edge delay */
  __IO uint32_t DBRED;                             /* !< (@ 0x000000D4) Dead band rise edge delay */
  __IO uint32_t DBFEDS;                            /* !< (@ 0x000000D8) Dead band fall edge delay shadow register */
  __IO uint32_t DBREDS;                            /* !< (@ 0x000000DC) Dead band rise edge delay shadow register */
       uint32_t RESERVED9[4];
  __IO uint32_t GLDCTL;                            /* !< (@ 0x000000F0) Global load control register */
  __IO uint32_t GLDOSHTCTL;                        /* !< (@ 0x000000F4) Global load one shot control register */
  __IO uint32_t GLDOSHTSTS;                        /* !< (@ 0x000000F8) Global load one shot status register */
       uint32_t RESERVED10;
  __IO uint32_t PWM1_CMPA;                         /* !< (@ 0x00000100) PWM1 counter compare A register */
  __IO uint32_t PWM1_CMPAS;                        /* !< (@ 0x00000104) PWM1 counter compare A shadow register */
  __IO uint32_t PWM1_CMPB;                         /* !< (@ 0x00000108) PWM1 counter compare B register */
  __IO uint32_t PWM1_CMPBS;                        /* !< (@ 0x0000010C) PWM1 counter compare B shadow register */
       uint32_t RESERVED11[4];
  __IO uint32_t PWM1_AQCTLA;                       /* !< (@ 0x00000120) PWM1 action qualifier A register */
  __IO uint32_t PWM1_AQCTLAS;                      /* !< (@ 0x00000124) PWM1 action qualifier A shadow register */
  __IO uint32_t PWM1_AQCTLB;                       /* !< (@ 0x00000128) PWM1 action qualifier B register */
  __IO uint32_t PWM1_AQCTLBS;                      /* !< (@ 0x0000012C) PWM1 action qualifier B shadow register */
  __IO uint32_t PWM1_AQSFRC;                       /* !< (@ 0x00000130) PWM1 action qualifier software force */
  __IO uint32_t PWM1_AQOTSFRC;                     /* !< (@ 0x00000134) PWM1 action qualifier one time software force */
       uint32_t RESERVED12[114];
  __IO uint32_t PWM2_CMPA;                         /* !< (@ 0x00000300) PWM2 counter compare A register */
  __IO uint32_t PWM2_CMPAS;                        /* !< (@ 0x00000304) PWM2 counter compare A shadow register */
  __IO uint32_t PWM2_CMPB;                         /* !< (@ 0x00000308) PWM2 counter compare B register */
  __IO uint32_t PWM2_CMPBS;                        /* !< (@ 0x0000030C) PWM2 counter compare B shadow register */
       uint32_t RESERVED13[4];
  __IO uint32_t PWM2_AQCTLA;                       /* !< (@ 0x00000320) PWM2 action qualifier A register */
  __IO uint32_t PWM2_AQCTLAS;                      /* !< (@ 0x00000324) PWM2 action qualifier A shadow register */
  __IO uint32_t PWM2_AQCTLB;                       /* !< (@ 0x00000328) PWM2 action qualifier B register */
  __IO uint32_t PWM2_AQCTLBS;                      /* !< (@ 0x0000032C) PWM2 action qualifier B shadow register */
  __IO uint32_t PWM2_AQSFRC;                       /* !< (@ 0x00000330) PWM2 action qualifier software force */
  __IO uint32_t PWM2_AQOTSFRC;                     /* !< (@ 0x00000334) PWM2 action qualifier one time software force */
       uint32_t RESERVED14[114];
  __IO uint32_t PWM3_CMPA;                         /* !< (@ 0x00000500) PWM3 counter compare A register */
  __IO uint32_t PWM3_CMPAS;                        /* !< (@ 0x00000504) PWM3 counter compare A shadow register */
  __IO uint32_t PWM3_CMPB;                         /* !< (@ 0x00000508) PWM3 counter compare B register */
  __IO uint32_t PWM3_CMPBS;                        /* !< (@ 0x0000050C) PWM3 counter compare B shadow register */
       uint32_t RESERVED15[4];
  __IO uint32_t PWM3_AQCTLA;                       /* !< (@ 0x00000520) PWM3 action qualifier A register */
  __IO uint32_t PWM3_AQCTLAS;                      /* !< (@ 0x00000524) PWM3 action qualifier A shadow register */
  __IO uint32_t PWM3_AQCTLB;                       /* !< (@ 0x00000528) PWM3 action qualifier B register */
  __IO uint32_t PWM3_AQCTLBS;                      /* !< (@ 0x0000052C) PWM3 action qualifier B shadow register */
  __IO uint32_t PWM3_AQSFRC;                       /* !< (@ 0x00000530) PWM3 action qualifier software force */
  __IO uint32_t PWM3_AQOTSFRC;                     /* !< (@ 0x00000534) PWM3 action qualifier one time software force */
} MCPWM_Regs;

/*@}*/ /* end of group MCPWM */



/******************************************************************************
* MCPWM Register Offsets
******************************************************************************/
#define MCPWM_REVISION                           (0x00000000U)
#define MCPWM_TBCTL                              (0x00000010U)
#define MCPWM_TBPRD                              (0x00000014U)
#define MCPWM_TBPRDS                             (0x00000018U)
#define MCPWM_TBPHS                              (0x0000001CU)
#define MCPWM_TBSTS                              (0x00000020U)
#define MCPWM_TBSTSCLR                           (0x00000024U)
#define MCPWM_TBCTR                              (0x00000028U)
#define MCPWM_CMPCTL                             (0x00000030U)
#define MCPWM_CMPC                               (0x00000040U)
#define MCPWM_CMPD                               (0x00000044U)
#define MCPWM_CMPCS                              (0x00000048U)
#define MCPWM_CMPDS                              (0x0000004CU)
#define MCPWM_AQCTL                              (0x00000050U)
#define MCPWM_SOCEN                              (0x00000060U)
#define MCPWM_SOCSEL                             (0x00000064U)
#define MCPWM_SOCPERIOD                          (0x00000068U)
#define MCPWM_SOCCNT                             (0x0000006CU)
#define MCPWM_SOCFLAG                            (0x00000070U)
#define MCPWM_SOCCLR                             (0x00000074U)
#define MCPWM_ETSEL                              (0x00000080U)
#define MCPWM_ETPERIOD                           (0x00000084U)
#define MCPWM_ETCNT                              (0x00000088U)
#define MCPWM_INTEN                              (0x00000090U)
#define MCPWM_INTFLAG                            (0x00000094U)
#define MCPWM_INTCLR                             (0x00000098U)
#define MCPWM_INTFRC                             (0x0000009CU)
#define MCPWM_TZSEL                              (0x000000A0U)
#define MCPWM_TZCTL                              (0x000000ACU)
#define MCPWM_TZCBCOSTFLAG                       (0x000000B0U)
#define MCPWM_TZCBCOSTCLR                        (0x000000B4U)
#define MCPWM_DBCTL                              (0x000000C0U)
#define MCPWM_DBFED                              (0x000000D0U)
#define MCPWM_DBRED                              (0x000000D4U)
#define MCPWM_DBFEDS                             (0x000000D8U)
#define MCPWM_DBREDS                             (0x000000DCU)
#define MCPWM_GLDCTL                             (0x000000F0U)
#define MCPWM_GLDOSHTCTL                         (0x000000F4U)
#define MCPWM_GLDOSHTSTS                         (0x000000F8U)
#define MCPWM_PWM1_CMPA                          (0x00000100U)
#define MCPWM_PWM1_CMPAS                         (0x00000104U)
#define MCPWM_PWM1_CMPB                          (0x00000108U)
#define MCPWM_PWM1_CMPBS                         (0x0000010CU)
#define MCPWM_PWM1_AQCTLA                        (0x00000120U)
#define MCPWM_PWM1_AQCTLAS                       (0x00000124U)
#define MCPWM_PWM1_AQCTLB                        (0x00000128U)
#define MCPWM_PWM1_AQCTLBS                       (0x0000012CU)
#define MCPWM_PWM1_AQSFRC                        (0x00000130U)
#define MCPWM_PWM1_AQOTSFRC                      (0x00000134U)
#define MCPWM_PWM2_CMPA                          (0x00000300U)
#define MCPWM_PWM2_CMPAS                         (0x00000304U)
#define MCPWM_PWM2_CMPB                          (0x00000308U)
#define MCPWM_PWM2_CMPBS                         (0x0000030CU)
#define MCPWM_PWM2_AQCTLA                        (0x00000320U)
#define MCPWM_PWM2_AQCTLAS                       (0x00000324U)
#define MCPWM_PWM2_AQCTLB                        (0x00000328U)
#define MCPWM_PWM2_AQCTLBS                       (0x0000032CU)
#define MCPWM_PWM2_AQSFRC                        (0x00000330U)
#define MCPWM_PWM2_AQOTSFRC                      (0x00000334U)
#define MCPWM_PWM3_CMPA                          (0x00000500U)
#define MCPWM_PWM3_CMPAS                         (0x00000504U)
#define MCPWM_PWM3_CMPB                          (0x00000508U)
#define MCPWM_PWM3_CMPBS                         (0x0000050CU)
#define MCPWM_PWM3_AQCTLA                        (0x00000520U)
#define MCPWM_PWM3_AQCTLAS                       (0x00000524U)
#define MCPWM_PWM3_AQCTLB                        (0x00000528U)
#define MCPWM_PWM3_AQCTLBS                       (0x0000052CU)
#define MCPWM_PWM3_AQSFRC                        (0x00000530U)
#define MCPWM_PWM3_AQOTSFRC                      (0x00000534U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* MCPWM Register Control Bits
******************************************************************************/

/* MCPWM_REVISION Bits */
/* MCPWM_REVISION[PWM2_PRESENT] Bits */
#define MCPWM_REVISION_PWM2_PRESENT_OFS          (0)                             /* !< PWM2_PRESENT Offset */
#define MCPWM_REVISION_PWM2_PRESENT_MASK         ((uint32_t)0x00000001U)         /* !< PWM2 Present */
/* MCPWM_REVISION[PWM3_PRESENT] Bits */
#define MCPWM_REVISION_PWM3_PRESENT_OFS          (1)                             /* !< PWM3_PRESENT Offset */
#define MCPWM_REVISION_PWM3_PRESENT_MASK         ((uint32_t)0x00000002U)         /* !< PWM3 Present */
/* MCPWM_REVISION[CMPCD_PRESENT] Bits */
#define MCPWM_REVISION_CMPCD_PRESENT_OFS         (2)                             /* !< CMPCD_PRESENT Offset */
#define MCPWM_REVISION_CMPCD_PRESENT_MASK        ((uint32_t)0x00000004U)         /* !< Compare C and D Present */
/* MCPWM_REVISION[CAP_PRESENT] Bits */
#define MCPWM_REVISION_CAP_PRESENT_OFS           (3)                             /* !< CAP_PRESENT Offset */
#define MCPWM_REVISION_CAP_PRESENT_MASK          ((uint32_t)0x00000008U)         /* !< Capture mode Present */

/* MCPWM_TBCTL Bits */
/* MCPWM_TBCTL[CTRMODE] Bits */
#define MCPWM_TBCTL_CTRMODE_OFS                  (0)                             /* !< CTRMODE Offset */
#define MCPWM_TBCTL_CTRMODE_MASK                 ((uint32_t)0x00000003U)         /* !< Counter Mode */
/* MCPWM_TBCTL[CLKDIV] Bits */
#define MCPWM_TBCTL_CLKDIV_OFS                   (2)                             /* !< CLKDIV Offset */
#define MCPWM_TBCTL_CLKDIV_MASK                  ((uint32_t)0x0000003CU)         /* !< Time Base Clock Pre-scaler */
/* MCPWM_TBCTL[PRDLD] Bits */
#define MCPWM_TBCTL_PRDLD_OFS                    (8)                             /* !< PRDLD Offset */
#define MCPWM_TBCTL_PRDLD_MASK                   ((uint32_t)0x00000100U)         /* !< Shadow to active load of TBPRD */
/* MCPWM_TBCTL[PHSEN] Bits */
#define MCPWM_TBCTL_PHSEN_OFS                    (10)                            /* !< PHSEN Offset */
#define MCPWM_TBCTL_PHSEN_MASK                   ((uint32_t)0x00000400U)         /* !< Phase Load Enable */
/* MCPWM_TBCTL[PHSDIR] Bits */
#define MCPWM_TBCTL_PHSDIR_OFS                   (11)                            /* !< PHSDIR Offset */
#define MCPWM_TBCTL_PHSDIR_MASK                  ((uint32_t)0x00000800U)         /* !< Phase Direction Bit */
/* MCPWM_TBCTL[SWSYNC] Bits */
#define MCPWM_TBCTL_SWSYNC_OFS                   (15)                            /* !< SWSYNC Offset */
#define MCPWM_TBCTL_SWSYNC_MASK                  ((uint32_t)0x00008000U)         /* !< Software Force Sync Pulse */
/* MCPWM_TBCTL[SYNCOSEL] Bits */
#define MCPWM_TBCTL_SYNCOSEL_OFS                 (16)                            /* !< SYNCOSEL Offset */
#define MCPWM_TBCTL_SYNCOSEL_MASK                ((uint32_t)0x00070000U)         /* !< Sync Output Select */
/* MCPWM_TBCTL[FREE_SOFT] Bits */
#define MCPWM_TBCTL_FREE_SOFT_OFS                (20)                            /* !< FREE_SOFT Offset */
#define MCPWM_TBCTL_FREE_SOFT_MASK               ((uint32_t)0x00300000U)         /* !< Emulation Mode Bits */
/* MCPWM_TBCTL[SYNCPERSEL] Bits */
#define MCPWM_TBCTL_SYNCPERSEL_OFS               (22)                            /* !< SYNCPERSEL Offset */
#define MCPWM_TBCTL_SYNCPERSEL_MASK              ((uint32_t)0x01C00000U)         /* !< Sync peripheral Select */
/* MCPWM_TBCTL[SYNCISEL] Bits */
#define MCPWM_TBCTL_SYNCISEL_OFS                 (25)                            /* !< SYNCISEL Offset */
#define MCPWM_TBCTL_SYNCISEL_MASK                ((uint32_t)0x3E000000U)         /* !< Sync Input Select */

/* MCPWM_TBPRD Bits */
/* MCPWM_TBPRD[TBPRD] Bits */
#define MCPWM_TBPRD_TBPRD_OFS                    (0)                             /* !< TBPRD Offset */
#define MCPWM_TBPRD_TBPRD_MASK                   ((uint32_t)0x0000FFFFU)         /* !< Time base period register */

/* MCPWM_TBPRDS Bits */
/* MCPWM_TBPRDS[TBPRDS] Bits */
#define MCPWM_TBPRDS_TBPRDS_OFS                  (0)                             /* !< TBPRDS Offset */
#define MCPWM_TBPRDS_TBPRDS_MASK                 ((uint32_t)0x0000FFFFU)         /* !< Time base period shadow register */

/* MCPWM_TBPHS Bits */
/* MCPWM_TBPHS[TBPHS] Bits */
#define MCPWM_TBPHS_TBPHS_OFS                    (0)                             /* !< TBPHS Offset */
#define MCPWM_TBPHS_TBPHS_MASK                   ((uint32_t)0x0000FFFFU)         /* !< Phase Offset Register */

/* MCPWM_TBSTS Bits */
/* MCPWM_TBSTS[CTRDIR] Bits */
#define MCPWM_TBSTS_CTRDIR_OFS                   (0)                             /* !< CTRDIR Offset */
#define MCPWM_TBSTS_CTRDIR_MASK                  ((uint32_t)0x00000001U)         /* !< Counter Direction Status */
/* MCPWM_TBSTS[SYNCI] Bits */
#define MCPWM_TBSTS_SYNCI_OFS                    (1)                             /* !< SYNCI Offset */
#define MCPWM_TBSTS_SYNCI_MASK                   ((uint32_t)0x00000002U)         /* !< External Input Sync Status */

/* MCPWM_TBSTSCLR Bits */
/* MCPWM_TBSTSCLR[SYNCI] Bits */
#define MCPWM_TBSTSCLR_SYNCI_OFS                 (1)                             /* !< SYNCI Offset */
#define MCPWM_TBSTSCLR_SYNCI_MASK                ((uint32_t)0x00000002U)         /* !< External Input Sync Status clear */

/* MCPWM_TBCTR Bits */
/* MCPWM_TBCTR[TBCTR] Bits */
#define MCPWM_TBCTR_TBCTR_OFS                    (0)                             /* !< TBCTR Offset */
#define MCPWM_TBCTR_TBCTR_MASK                   ((uint32_t)0x0000FFFFU)         /* !< Counter Value */

/* MCPWM_CMPCTL Bits */
/* MCPWM_CMPCTL[PWM1_LOADAMODE] Bits */
#define MCPWM_CMPCTL_PWM1_LOADAMODE_OFS          (0)                             /* !< PWM1_LOADAMODE Offset */
#define MCPWM_CMPCTL_PWM1_LOADAMODE_MASK         ((uint32_t)0x00000003U)         /* !< Shadow to active load of PWM1_CMPA */
/* MCPWM_CMPCTL[PWM1_LOADBMODE] Bits */
#define MCPWM_CMPCTL_PWM1_LOADBMODE_OFS          (2)                             /* !< PWM1_LOADBMODE Offset */
#define MCPWM_CMPCTL_PWM1_LOADBMODE_MASK         ((uint32_t)0x0000000CU)         /* !< Shadow to active load of PWM1_CMPB */
/* MCPWM_CMPCTL[PWM2_LOADAMODE] Bits */
#define MCPWM_CMPCTL_PWM2_LOADAMODE_OFS          (8)                             /* !< PWM2_LOADAMODE Offset */
#define MCPWM_CMPCTL_PWM2_LOADAMODE_MASK         ((uint32_t)0x00000300U)         /* !< Shadow to active load of PWM2_CMPA */
/* MCPWM_CMPCTL[PWM2_LOADBMODE] Bits */
#define MCPWM_CMPCTL_PWM2_LOADBMODE_OFS          (10)                            /* !< PWM2_LOADBMODE Offset */
#define MCPWM_CMPCTL_PWM2_LOADBMODE_MASK         ((uint32_t)0x00000C00U)         /* !< Shadow to active load of PWM2_CMPB */
/* MCPWM_CMPCTL[PWM3_LOADAMODE] Bits */
#define MCPWM_CMPCTL_PWM3_LOADAMODE_OFS          (16)                            /* !< PWM3_LOADAMODE Offset */
#define MCPWM_CMPCTL_PWM3_LOADAMODE_MASK         ((uint32_t)0x00030000U)         /* !< Shadow to active load of PWM3_CMPA */
/* MCPWM_CMPCTL[PWM3_LOADBMODE] Bits */
#define MCPWM_CMPCTL_PWM3_LOADBMODE_OFS          (18)                            /* !< PWM3_LOADBMODE Offset */
#define MCPWM_CMPCTL_PWM3_LOADBMODE_MASK         ((uint32_t)0x000C0000U)         /* !< Shadow to active load of PWM3_CMPB */
/* MCPWM_CMPCTL[LOADCMODE] Bits */
#define MCPWM_CMPCTL_LOADCMODE_OFS               (24)                            /* !< LOADCMODE Offset */
#define MCPWM_CMPCTL_LOADCMODE_MASK              ((uint32_t)0x03000000U)         /* !< Shadow to active load of CMPC */
/* MCPWM_CMPCTL[LOADDMODE] Bits */
#define MCPWM_CMPCTL_LOADDMODE_OFS               (26)                            /* !< LOADDMODE Offset */
#define MCPWM_CMPCTL_LOADDMODE_MASK              ((uint32_t)0x0C000000U)         /* !< Shadow to active load of CMPD */

/* MCPWM_CMPC Bits */
/* MCPWM_CMPC[CMPC] Bits */
#define MCPWM_CMPC_CMPC_OFS                      (0)                             /* !< CMPC Offset */
#define MCPWM_CMPC_CMPC_MASK                     ((uint32_t)0x0000FFFFU)         /* !< Compare C register */

/* MCPWM_CMPD Bits */
/* MCPWM_CMPD[CMPD] Bits */
#define MCPWM_CMPD_CMPD_OFS                      (0)                             /* !< CMPD Offset */
#define MCPWM_CMPD_CMPD_MASK                     ((uint32_t)0x0000FFFFU)         /* !< Compare D register */

/* MCPWM_CMPCS Bits */
/* MCPWM_CMPCS[CMPCS] Bits */
#define MCPWM_CMPCS_CMPCS_OFS                    (0)                             /* !< CMPCS Offset */
#define MCPWM_CMPCS_CMPCS_MASK                   ((uint32_t)0x0000FFFFU)         /* !< Compare C shadow register */

/* MCPWM_CMPDS Bits */
/* MCPWM_CMPDS[CMPDS] Bits */
#define MCPWM_CMPDS_CMPDS_OFS                    (0)                             /* !< CMPDS Offset */
#define MCPWM_CMPDS_CMPDS_MASK                   ((uint32_t)0x0000FFFFU)         /* !< Compare D shadow register */

/* MCPWM_AQCTL Bits */
/* MCPWM_AQCTL[PWM1_LDAQAMODE] Bits */
#define MCPWM_AQCTL_PWM1_LDAQAMODE_OFS           (0)                             /* !< PWM1_LDAQAMODE Offset */
#define MCPWM_AQCTL_PWM1_LDAQAMODE_MASK          ((uint32_t)0x00000003U)         /* !< Shadow to active load of
                                                                                    PWM1_AQCTLA */
/* MCPWM_AQCTL[PWM1_LDAQBMODE] Bits */
#define MCPWM_AQCTL_PWM1_LDAQBMODE_OFS           (2)                             /* !< PWM1_LDAQBMODE Offset */
#define MCPWM_AQCTL_PWM1_LDAQBMODE_MASK          ((uint32_t)0x0000000CU)         /* !< Shadow to active load of
                                                                                    PWM1_AQCTLB */
/* MCPWM_AQCTL[PWM2_LDAQAMODE] Bits */
#define MCPWM_AQCTL_PWM2_LDAQAMODE_OFS           (8)                             /* !< PWM2_LDAQAMODE Offset */
#define MCPWM_AQCTL_PWM2_LDAQAMODE_MASK          ((uint32_t)0x00000300U)         /* !< Shadow to active load of
                                                                                    PWM2_AQCTLA */
/* MCPWM_AQCTL[PWM2_LDAQBMODE] Bits */
#define MCPWM_AQCTL_PWM2_LDAQBMODE_OFS           (10)                            /* !< PWM2_LDAQBMODE Offset */
#define MCPWM_AQCTL_PWM2_LDAQBMODE_MASK          ((uint32_t)0x00000C00U)         /* !< Shadow to active load of
                                                                                    PWM2_AQCTLB */
/* MCPWM_AQCTL[PWM3_LDAQAMODE] Bits */
#define MCPWM_AQCTL_PWM3_LDAQAMODE_OFS           (16)                            /* !< PWM3_LDAQAMODE Offset */
#define MCPWM_AQCTL_PWM3_LDAQAMODE_MASK          ((uint32_t)0x00030000U)         /* !< Shadow to active load of
                                                                                    PWM3_AQCTLA */
/* MCPWM_AQCTL[PWM3_LDAQBMODE] Bits */
#define MCPWM_AQCTL_PWM3_LDAQBMODE_OFS           (18)                            /* !< PWM3_LDAQBMODE Offset */
#define MCPWM_AQCTL_PWM3_LDAQBMODE_MASK          ((uint32_t)0x000C0000U)         /* !< Shadow to active load of
                                                                                    PWM3_AQCTLB */

/* MCPWM_SOCEN Bits */
/* MCPWM_SOCEN[SOCA_ENABLE] Bits */
#define MCPWM_SOCEN_SOCA_ENABLE_OFS              (0)                             /* !< SOCA_ENABLE Offset */
#define MCPWM_SOCEN_SOCA_ENABLE_MASK             ((uint32_t)0x00000001U)         /* !< Start of conversion (SOC) A enable */
/* MCPWM_SOCEN[SOCB_ENABLE] Bits */
#define MCPWM_SOCEN_SOCB_ENABLE_OFS              (1)                             /* !< SOCB_ENABLE Offset */
#define MCPWM_SOCEN_SOCB_ENABLE_MASK             ((uint32_t)0x00000002U)         /* !< Start of conversion (SOC) B enable */
/* MCPWM_SOCEN[SOCC_ENABLE] Bits */
#define MCPWM_SOCEN_SOCC_ENABLE_OFS              (2)                             /* !< SOCC_ENABLE Offset */
#define MCPWM_SOCEN_SOCC_ENABLE_MASK             ((uint32_t)0x00000004U)         /* !< Start of conversion (SOC) C enable */
/* MCPWM_SOCEN[SOCD_ENABLE] Bits */
#define MCPWM_SOCEN_SOCD_ENABLE_OFS              (3)                             /* !< SOCD_ENABLE Offset */
#define MCPWM_SOCEN_SOCD_ENABLE_MASK             ((uint32_t)0x00000008U)         /* !< Start of conversion (SOC) D enable */

/* MCPWM_SOCSEL Bits */
/* MCPWM_SOCSEL[SOCA_SEL] Bits */
#define MCPWM_SOCSEL_SOCA_SEL_OFS                (0)                             /* !< SOCA_SEL Offset */
#define MCPWM_SOCSEL_SOCA_SEL_MASK               ((uint32_t)0x0000001FU)         /* !< Start of conversion (SOC) A select */
/* MCPWM_SOCSEL[SOCB_SEL] Bits */
#define MCPWM_SOCSEL_SOCB_SEL_OFS                (8)                             /* !< SOCB_SEL Offset */
#define MCPWM_SOCSEL_SOCB_SEL_MASK               ((uint32_t)0x00001F00U)         /* !< Start of conversion (SOC) B select */
/* MCPWM_SOCSEL[SOCC_SEL] Bits */
#define MCPWM_SOCSEL_SOCC_SEL_OFS                (16)                            /* !< SOCC_SEL Offset */
#define MCPWM_SOCSEL_SOCC_SEL_MASK               ((uint32_t)0x001F0000U)         /* !< Start of conversion (SOC) C select */
/* MCPWM_SOCSEL[SOCD_SEL] Bits */
#define MCPWM_SOCSEL_SOCD_SEL_OFS                (24)                            /* !< SOCD_SEL Offset */
#define MCPWM_SOCSEL_SOCD_SEL_MASK               ((uint32_t)0x1F000000U)         /* !< Start of conversion (SOC) D select */

/* MCPWM_SOCPERIOD Bits */
/* MCPWM_SOCPERIOD[SOCA_PERIOD] Bits */
#define MCPWM_SOCPERIOD_SOCA_PERIOD_OFS          (0)                             /* !< SOCA_PERIOD Offset */
#define MCPWM_SOCPERIOD_SOCA_PERIOD_MASK         ((uint32_t)0x00000007U)         /* !< Start of conversion (SOC) A PERIOD */
/* MCPWM_SOCPERIOD[SOCB_PERIOD] Bits */
#define MCPWM_SOCPERIOD_SOCB_PERIOD_OFS          (8)                             /* !< SOCB_PERIOD Offset */
#define MCPWM_SOCPERIOD_SOCB_PERIOD_MASK         ((uint32_t)0x00000700U)         /* !< Start of conversion (SOC) B PERIOD */
/* MCPWM_SOCPERIOD[SOCC_PERIOD] Bits */
#define MCPWM_SOCPERIOD_SOCC_PERIOD_OFS          (16)                            /* !< SOCC_PERIOD Offset */
#define MCPWM_SOCPERIOD_SOCC_PERIOD_MASK         ((uint32_t)0x00070000U)         /* !< Start of conversion (SOC) C PERIOD */
/* MCPWM_SOCPERIOD[SOCD_PERIOD] Bits */
#define MCPWM_SOCPERIOD_SOCD_PERIOD_OFS          (24)                            /* !< SOCD_PERIOD Offset */
#define MCPWM_SOCPERIOD_SOCD_PERIOD_MASK         ((uint32_t)0x07000000U)         /* !< Start of conversion (SOC) D PERIOD */

/* MCPWM_SOCCNT Bits */
/* MCPWM_SOCCNT[SOCA_CNT] Bits */
#define MCPWM_SOCCNT_SOCA_CNT_OFS                (0)                             /* !< SOCA_CNT Offset */
#define MCPWM_SOCCNT_SOCA_CNT_MASK               ((uint32_t)0x00000007U)         /* !< Start of conversion (SOC) A COUNT */
/* MCPWM_SOCCNT[SOCB_CNT] Bits */
#define MCPWM_SOCCNT_SOCB_CNT_OFS                (8)                             /* !< SOCB_CNT Offset */
#define MCPWM_SOCCNT_SOCB_CNT_MASK               ((uint32_t)0x00000700U)         /* !< Start of conversion (SOC) B COUNT */
/* MCPWM_SOCCNT[SOCC_CNT] Bits */
#define MCPWM_SOCCNT_SOCC_CNT_OFS                (16)                            /* !< SOCC_CNT Offset */
#define MCPWM_SOCCNT_SOCC_CNT_MASK               ((uint32_t)0x00070000U)         /* !< Start of conversion (SOC) C COUNT */
/* MCPWM_SOCCNT[SOCD_CNT] Bits */
#define MCPWM_SOCCNT_SOCD_CNT_OFS                (24)                            /* !< SOCD_CNT Offset */
#define MCPWM_SOCCNT_SOCD_CNT_MASK               ((uint32_t)0x07000000U)         /* !< Start of conversion (SOC) D COUNT */

/* MCPWM_SOCFLAG Bits */
/* MCPWM_SOCFLAG[SOCA] Bits */
#define MCPWM_SOCFLAG_SOCA_OFS                   (0)                             /* !< SOCA Offset */
#define MCPWM_SOCFLAG_SOCA_MASK                  ((uint32_t)0x00000001U)         /* !< SOCA Flag */
/* MCPWM_SOCFLAG[SOCB] Bits */
#define MCPWM_SOCFLAG_SOCB_OFS                   (1)                             /* !< SOCB Offset */
#define MCPWM_SOCFLAG_SOCB_MASK                  ((uint32_t)0x00000002U)         /* !< SOCB Flag */
/* MCPWM_SOCFLAG[SOCC] Bits */
#define MCPWM_SOCFLAG_SOCC_OFS                   (2)                             /* !< SOCC Offset */
#define MCPWM_SOCFLAG_SOCC_MASK                  ((uint32_t)0x00000004U)         /* !< SOCC Flag */
/* MCPWM_SOCFLAG[SOCD] Bits */
#define MCPWM_SOCFLAG_SOCD_OFS                   (3)                             /* !< SOCD Offset */
#define MCPWM_SOCFLAG_SOCD_MASK                  ((uint32_t)0x00000008U)         /* !< SOCD Flag */

/* MCPWM_SOCCLR Bits */
/* MCPWM_SOCCLR[SOCA] Bits */
#define MCPWM_SOCCLR_SOCA_OFS                    (0)                             /* !< SOCA Offset */
#define MCPWM_SOCCLR_SOCA_MASK                   ((uint32_t)0x00000001U)         /* !< SOCA Clear */
/* MCPWM_SOCCLR[SOCB] Bits */
#define MCPWM_SOCCLR_SOCB_OFS                    (1)                             /* !< SOCB Offset */
#define MCPWM_SOCCLR_SOCB_MASK                   ((uint32_t)0x00000002U)         /* !< SOCB Clear */
/* MCPWM_SOCCLR[SOCC] Bits */
#define MCPWM_SOCCLR_SOCC_OFS                    (2)                             /* !< SOCC Offset */
#define MCPWM_SOCCLR_SOCC_MASK                   ((uint32_t)0x00000004U)         /* !< SOCC Clear */
/* MCPWM_SOCCLR[SOCD] Bits */
#define MCPWM_SOCCLR_SOCD_OFS                    (3)                             /* !< SOCD Offset */
#define MCPWM_SOCCLR_SOCD_MASK                   ((uint32_t)0x00000008U)         /* !< SOCD Clear */

/* MCPWM_ETSEL Bits */
/* MCPWM_ETSEL[ET1_SEL] Bits */
#define MCPWM_ETSEL_ET1_SEL_OFS                  (0)                             /* !< ET1_SEL Offset */
#define MCPWM_ETSEL_ET1_SEL_MASK                 ((uint32_t)0x0000001FU)         /* !< Event trigger1 selection */
/* MCPWM_ETSEL[ET2_SEL] Bits */
#define MCPWM_ETSEL_ET2_SEL_OFS                  (8)                             /* !< ET2_SEL Offset */
#define MCPWM_ETSEL_ET2_SEL_MASK                 ((uint32_t)0x00001F00U)         /* !< Event trigger2 selection */

/* MCPWM_ETPERIOD Bits */
/* MCPWM_ETPERIOD[ET1_PERIOD] Bits */
#define MCPWM_ETPERIOD_ET1_PERIOD_OFS            (0)                             /* !< ET1_PERIOD Offset */
#define MCPWM_ETPERIOD_ET1_PERIOD_MASK           ((uint32_t)0x00000007U)         /* !< Event trigger1 PERIOD */
/* MCPWM_ETPERIOD[ET2_PERIOD] Bits */
#define MCPWM_ETPERIOD_ET2_PERIOD_OFS            (8)                             /* !< ET2_PERIOD Offset */
#define MCPWM_ETPERIOD_ET2_PERIOD_MASK           ((uint32_t)0x00000700U)         /* !< Event trigger2 PERIOD */

/* MCPWM_ETCNT Bits */
/* MCPWM_ETCNT[ET1_CNT] Bits */
#define MCPWM_ETCNT_ET1_CNT_OFS                  (0)                             /* !< ET1_CNT Offset */
#define MCPWM_ETCNT_ET1_CNT_MASK                 ((uint32_t)0x00000007U)         /* !< Event trigger1 COUNT */
/* MCPWM_ETCNT[ET2_CNT] Bits */
#define MCPWM_ETCNT_ET2_CNT_OFS                  (8)                             /* !< ET2_CNT Offset */
#define MCPWM_ETCNT_ET2_CNT_MASK                 ((uint32_t)0x00000700U)         /* !< Event trigger2 COUNT */

/* MCPWM_INTEN Bits */
/* MCPWM_INTEN[CBC] Bits */
#define MCPWM_INTEN_CBC_OFS                      (1)                             /* !< CBC Offset */
#define MCPWM_INTEN_CBC_MASK                     ((uint32_t)0x00000002U)         /* !< Enable CBC interrupt */
/* MCPWM_INTEN[OST] Bits */
#define MCPWM_INTEN_OST_OFS                      (2)                             /* !< OST Offset */
#define MCPWM_INTEN_OST_MASK                     ((uint32_t)0x00000004U)         /* !< Enable OST interrupt */
/* MCPWM_INTEN[ET1] Bits */
#define MCPWM_INTEN_ET1_OFS                      (3)                             /* !< ET1 Offset */
#define MCPWM_INTEN_ET1_MASK                     ((uint32_t)0x00000008U)         /* !< Enable ET1 interrupt */
/* MCPWM_INTEN[ET2] Bits */
#define MCPWM_INTEN_ET2_OFS                      (4)                             /* !< ET2 Offset */
#define MCPWM_INTEN_ET2_MASK                     ((uint32_t)0x00000010U)         /* !< Enable ET2 interrupt */
/* MCPWM_INTEN[CNT_OVF] Bits */
#define MCPWM_INTEN_CNT_OVF_OFS                  (5)                             /* !< CNT_OVF Offset */
#define MCPWM_INTEN_CNT_OVF_MASK                 ((uint32_t)0x00000020U)         /* !< Counter overflow interrupt */

/* MCPWM_INTFLAG Bits */
/* MCPWM_INTFLAG[INT] Bits */
#define MCPWM_INTFLAG_INT_OFS                    (0)                             /* !< INT Offset */
#define MCPWM_INTFLAG_INT_MASK                   ((uint32_t)0x00000001U)         /* !< Global Flag */
/* MCPWM_INTFLAG[CBC] Bits */
#define MCPWM_INTFLAG_CBC_OFS                    (1)                             /* !< CBC Offset */
#define MCPWM_INTFLAG_CBC_MASK                   ((uint32_t)0x00000002U)         /* !< CBC interrupt flag */
/* MCPWM_INTFLAG[OST] Bits */
#define MCPWM_INTFLAG_OST_OFS                    (2)                             /* !< OST Offset */
#define MCPWM_INTFLAG_OST_MASK                   ((uint32_t)0x00000004U)         /* !< OST interrupt flag */
/* MCPWM_INTFLAG[ET1] Bits */
#define MCPWM_INTFLAG_ET1_OFS                    (3)                             /* !< ET1 Offset */
#define MCPWM_INTFLAG_ET1_MASK                   ((uint32_t)0x00000008U)         /* !< ET1 interrupt flag */
/* MCPWM_INTFLAG[ET2] Bits */
#define MCPWM_INTFLAG_ET2_OFS                    (4)                             /* !< ET2 Offset */
#define MCPWM_INTFLAG_ET2_MASK                   ((uint32_t)0x00000010U)         /* !< ET2 interrupt flag */
/* MCPWM_INTFLAG[CNT_OVF] Bits */
#define MCPWM_INTFLAG_CNT_OVF_OFS                (5)                             /* !< CNT_OVF Offset */
#define MCPWM_INTFLAG_CNT_OVF_MASK               ((uint32_t)0x00000020U)         /* !< Counter overflow flag */

/* MCPWM_INTCLR Bits */
/* MCPWM_INTCLR[INT] Bits */
#define MCPWM_INTCLR_INT_OFS                     (0)                             /* !< INT Offset */
#define MCPWM_INTCLR_INT_MASK                    ((uint32_t)0x00000001U)         /* !< Clear Global Flag */
/* MCPWM_INTCLR[CBC] Bits */
#define MCPWM_INTCLR_CBC_OFS                     (1)                             /* !< CBC Offset */
#define MCPWM_INTCLR_CBC_MASK                    ((uint32_t)0x00000002U)         /* !< Clear CBC interrupt flag */
/* MCPWM_INTCLR[OST] Bits */
#define MCPWM_INTCLR_OST_OFS                     (2)                             /* !< OST Offset */
#define MCPWM_INTCLR_OST_MASK                    ((uint32_t)0x00000004U)         /* !< Clear OST interrupt flag */
/* MCPWM_INTCLR[ET1] Bits */
#define MCPWM_INTCLR_ET1_OFS                     (3)                             /* !< ET1 Offset */
#define MCPWM_INTCLR_ET1_MASK                    ((uint32_t)0x00000008U)         /* !< Clear ET1 interrupt flag */
/* MCPWM_INTCLR[ET2] Bits */
#define MCPWM_INTCLR_ET2_OFS                     (4)                             /* !< ET2 Offset */
#define MCPWM_INTCLR_ET2_MASK                    ((uint32_t)0x00000010U)         /* !< Clear ET2 interrupt flag */
/* MCPWM_INTCLR[CNT_OVF] Bits */
#define MCPWM_INTCLR_CNT_OVF_OFS                 (5)                             /* !< CNT_OVF Offset */
#define MCPWM_INTCLR_CNT_OVF_MASK                ((uint32_t)0x00000020U)         /* !< Counter overflow flag */

/* MCPWM_INTFRC Bits */
/* MCPWM_INTFRC[CBC] Bits */
#define MCPWM_INTFRC_CBC_OFS                     (1)                             /* !< CBC Offset */
#define MCPWM_INTFRC_CBC_MASK                    ((uint32_t)0x00000002U)         /* !< Force CBC interrupt flag */
/* MCPWM_INTFRC[OST] Bits */
#define MCPWM_INTFRC_OST_OFS                     (2)                             /* !< OST Offset */
#define MCPWM_INTFRC_OST_MASK                    ((uint32_t)0x00000004U)         /* !< Force OST interrupt flag */
/* MCPWM_INTFRC[ET1] Bits */
#define MCPWM_INTFRC_ET1_OFS                     (3)                             /* !< ET1 Offset */
#define MCPWM_INTFRC_ET1_MASK                    ((uint32_t)0x00000008U)         /* !< Force ET1 interrupt flag */
/* MCPWM_INTFRC[ET2] Bits */
#define MCPWM_INTFRC_ET2_OFS                     (4)                             /* !< ET2 Offset */
#define MCPWM_INTFRC_ET2_MASK                    ((uint32_t)0x00000010U)         /* !< Force ET2 interrupt flag */
/* MCPWM_INTFRC[CNT_OVF] Bits */
#define MCPWM_INTFRC_CNT_OVF_OFS                 (5)                             /* !< CNT_OVF Offset */
#define MCPWM_INTFRC_CNT_OVF_MASK                ((uint32_t)0x00000020U)         /* !< Counter overflow flag */

/* MCPWM_TZSEL Bits */
/* MCPWM_TZSEL[CBC1] Bits */
#define MCPWM_TZSEL_CBC1_OFS                     (0)                             /* !< CBC1 Offset */
#define MCPWM_TZSEL_CBC1_MASK                    ((uint32_t)0x00000001U)         /* !< CBC TZ1 select */
/* MCPWM_TZSEL[CBC2] Bits */
#define MCPWM_TZSEL_CBC2_OFS                     (1)                             /* !< CBC2 Offset */
#define MCPWM_TZSEL_CBC2_MASK                    ((uint32_t)0x00000002U)         /* !< CBC TZ2 select */
/* MCPWM_TZSEL[CBC3] Bits */
#define MCPWM_TZSEL_CBC3_OFS                     (2)                             /* !< CBC3 Offset */
#define MCPWM_TZSEL_CBC3_MASK                    ((uint32_t)0x00000004U)         /* !< CBC TZ3 select */
/* MCPWM_TZSEL[CBC4] Bits */
#define MCPWM_TZSEL_CBC4_OFS                     (3)                             /* !< CBC4 Offset */
#define MCPWM_TZSEL_CBC4_MASK                    ((uint32_t)0x00000008U)         /* !< CBC TZ4  select */
/* MCPWM_TZSEL[CBC5] Bits */
#define MCPWM_TZSEL_CBC5_OFS                     (4)                             /* !< CBC5 Offset */
#define MCPWM_TZSEL_CBC5_MASK                    ((uint32_t)0x00000010U)         /* !< CBC TZ5 select */
/* MCPWM_TZSEL[CBC6] Bits */
#define MCPWM_TZSEL_CBC6_OFS                     (5)                             /* !< CBC6 Offset */
#define MCPWM_TZSEL_CBC6_MASK                    ((uint32_t)0x00000020U)         /* !< CBC TZ6 select */
/* MCPWM_TZSEL[CBC7] Bits */
#define MCPWM_TZSEL_CBC7_OFS                     (6)                             /* !< CBC7 Offset */
#define MCPWM_TZSEL_CBC7_MASK                    ((uint32_t)0x00000040U)         /* !< CBC TZ7 select */
/* MCPWM_TZSEL[CBC8] Bits */
#define MCPWM_TZSEL_CBC8_OFS                     (7)                             /* !< CBC8 Offset */
#define MCPWM_TZSEL_CBC8_MASK                    ((uint32_t)0x00000080U)         /* !< CBC TZ8 select */
/* MCPWM_TZSEL[OST1] Bits */
#define MCPWM_TZSEL_OST1_OFS                     (16)                            /* !< OST1 Offset */
#define MCPWM_TZSEL_OST1_MASK                    ((uint32_t)0x00010000U)         /* !< OST TZ1 select */
/* MCPWM_TZSEL[OST2] Bits */
#define MCPWM_TZSEL_OST2_OFS                     (17)                            /* !< OST2 Offset */
#define MCPWM_TZSEL_OST2_MASK                    ((uint32_t)0x00020000U)         /* !< OST TZ2 select */
/* MCPWM_TZSEL[OST3] Bits */
#define MCPWM_TZSEL_OST3_OFS                     (18)                            /* !< OST3 Offset */
#define MCPWM_TZSEL_OST3_MASK                    ((uint32_t)0x00040000U)         /* !< OST TZ3 select */
/* MCPWM_TZSEL[OST4] Bits */
#define MCPWM_TZSEL_OST4_OFS                     (19)                            /* !< OST4 Offset */
#define MCPWM_TZSEL_OST4_MASK                    ((uint32_t)0x00080000U)         /* !< OST TZ4  select */
/* MCPWM_TZSEL[OST5] Bits */
#define MCPWM_TZSEL_OST5_OFS                     (20)                            /* !< OST5 Offset */
#define MCPWM_TZSEL_OST5_MASK                    ((uint32_t)0x00100000U)         /* !< OST TZ5 select */
/* MCPWM_TZSEL[OST6] Bits */
#define MCPWM_TZSEL_OST6_OFS                     (21)                            /* !< OST6 Offset */
#define MCPWM_TZSEL_OST6_MASK                    ((uint32_t)0x00200000U)         /* !< OST TZ6 select */
/* MCPWM_TZSEL[OST7] Bits */
#define MCPWM_TZSEL_OST7_OFS                     (22)                            /* !< OST7 Offset */
#define MCPWM_TZSEL_OST7_MASK                    ((uint32_t)0x00400000U)         /* !< OST TZ7 select */
/* MCPWM_TZSEL[OST8] Bits */
#define MCPWM_TZSEL_OST8_OFS                     (23)                            /* !< OST8 Offset */
#define MCPWM_TZSEL_OST8_MASK                    ((uint32_t)0x00800000U)         /* !< OST TZ8 select */

/* MCPWM_TZCTL Bits */
/* MCPWM_TZCTL[TZA] Bits */
#define MCPWM_TZCTL_TZA_OFS                      (0)                             /* !< TZA Offset */
#define MCPWM_TZCTL_TZA_MASK                     ((uint32_t)0x00000003U)         /* !< TZ1 to TZ8 Trip Action on PWMA */
/* MCPWM_TZCTL[TZB] Bits */
#define MCPWM_TZCTL_TZB_OFS                      (2)                             /* !< TZB Offset */
#define MCPWM_TZCTL_TZB_MASK                     ((uint32_t)0x0000000CU)         /* !< TZ1 to TZ8 Trip Action on PWMB */
/* MCPWM_TZCTL[CBCPULSE] Bits */
#define MCPWM_TZCTL_CBCPULSE_OFS                 (4)                             /* !< CBCPULSE Offset */
#define MCPWM_TZCTL_CBCPULSE_MASK                ((uint32_t)0x00000030U)         /* !< Clear Pulse for CBC Trip Latch */

/* MCPWM_TZCBCOSTFLAG Bits */
/* MCPWM_TZCBCOSTFLAG[CBC1] Bits */
#define MCPWM_TZCBCOSTFLAG_CBC1_OFS              (0)                             /* !< CBC1 Offset */
#define MCPWM_TZCBCOSTFLAG_CBC1_MASK             ((uint32_t)0x00000001U)         /* !< CBC TZ1 Flag */
/* MCPWM_TZCBCOSTFLAG[CBC2] Bits */
#define MCPWM_TZCBCOSTFLAG_CBC2_OFS              (1)                             /* !< CBC2 Offset */
#define MCPWM_TZCBCOSTFLAG_CBC2_MASK             ((uint32_t)0x00000002U)         /* !< CBC TZ2 Flag */
/* MCPWM_TZCBCOSTFLAG[CBC3] Bits */
#define MCPWM_TZCBCOSTFLAG_CBC3_OFS              (2)                             /* !< CBC3 Offset */
#define MCPWM_TZCBCOSTFLAG_CBC3_MASK             ((uint32_t)0x00000004U)         /* !< CBC TZ3 Flag */
/* MCPWM_TZCBCOSTFLAG[CBC4] Bits */
#define MCPWM_TZCBCOSTFLAG_CBC4_OFS              (3)                             /* !< CBC4 Offset */
#define MCPWM_TZCBCOSTFLAG_CBC4_MASK             ((uint32_t)0x00000008U)         /* !< CBC TZ4 Flag */
/* MCPWM_TZCBCOSTFLAG[CBC5] Bits */
#define MCPWM_TZCBCOSTFLAG_CBC5_OFS              (4)                             /* !< CBC5 Offset */
#define MCPWM_TZCBCOSTFLAG_CBC5_MASK             ((uint32_t)0x00000010U)         /* !< CBC TZ5 Flag */
/* MCPWM_TZCBCOSTFLAG[CBC6] Bits */
#define MCPWM_TZCBCOSTFLAG_CBC6_OFS              (5)                             /* !< CBC6 Offset */
#define MCPWM_TZCBCOSTFLAG_CBC6_MASK             ((uint32_t)0x00000020U)         /* !< CBC TZ6 Flag */
/* MCPWM_TZCBCOSTFLAG[CBC7] Bits */
#define MCPWM_TZCBCOSTFLAG_CBC7_OFS              (6)                             /* !< CBC7 Offset */
#define MCPWM_TZCBCOSTFLAG_CBC7_MASK             ((uint32_t)0x00000040U)         /* !< CBC TZ7 Flag */
/* MCPWM_TZCBCOSTFLAG[CBC8] Bits */
#define MCPWM_TZCBCOSTFLAG_CBC8_OFS              (7)                             /* !< CBC8 Offset */
#define MCPWM_TZCBCOSTFLAG_CBC8_MASK             ((uint32_t)0x00000080U)         /* !< OST TZ8 Flag */
/* MCPWM_TZCBCOSTFLAG[OST1] Bits */
#define MCPWM_TZCBCOSTFLAG_OST1_OFS              (16)                            /* !< OST1 Offset */
#define MCPWM_TZCBCOSTFLAG_OST1_MASK             ((uint32_t)0x00010000U)         /* !< OST TZ1 Flag */
/* MCPWM_TZCBCOSTFLAG[OST2] Bits */
#define MCPWM_TZCBCOSTFLAG_OST2_OFS              (17)                            /* !< OST2 Offset */
#define MCPWM_TZCBCOSTFLAG_OST2_MASK             ((uint32_t)0x00020000U)         /* !< OST TZ2 Flag */
/* MCPWM_TZCBCOSTFLAG[OST3] Bits */
#define MCPWM_TZCBCOSTFLAG_OST3_OFS              (18)                            /* !< OST3 Offset */
#define MCPWM_TZCBCOSTFLAG_OST3_MASK             ((uint32_t)0x00040000U)         /* !< OST TZ3 Flag */
/* MCPWM_TZCBCOSTFLAG[OST4] Bits */
#define MCPWM_TZCBCOSTFLAG_OST4_OFS              (19)                            /* !< OST4 Offset */
#define MCPWM_TZCBCOSTFLAG_OST4_MASK             ((uint32_t)0x00080000U)         /* !< OST TZ4 Flag */
/* MCPWM_TZCBCOSTFLAG[OST5] Bits */
#define MCPWM_TZCBCOSTFLAG_OST5_OFS              (20)                            /* !< OST5 Offset */
#define MCPWM_TZCBCOSTFLAG_OST5_MASK             ((uint32_t)0x00100000U)         /* !< OST TZ5 Flag */
/* MCPWM_TZCBCOSTFLAG[OST6] Bits */
#define MCPWM_TZCBCOSTFLAG_OST6_OFS              (21)                            /* !< OST6 Offset */
#define MCPWM_TZCBCOSTFLAG_OST6_MASK             ((uint32_t)0x00200000U)         /* !< OST TZ6 Flag */
/* MCPWM_TZCBCOSTFLAG[OST7] Bits */
#define MCPWM_TZCBCOSTFLAG_OST7_OFS              (22)                            /* !< OST7 Offset */
#define MCPWM_TZCBCOSTFLAG_OST7_MASK             ((uint32_t)0x00400000U)         /* !< OST TZ7 Flag */
/* MCPWM_TZCBCOSTFLAG[OST8] Bits */
#define MCPWM_TZCBCOSTFLAG_OST8_OFS              (23)                            /* !< OST8 Offset */
#define MCPWM_TZCBCOSTFLAG_OST8_MASK             ((uint32_t)0x00800000U)         /* !< OST TZ8 Flag */

/* MCPWM_TZCBCOSTCLR Bits */
/* MCPWM_TZCBCOSTCLR[CBC1] Bits */
#define MCPWM_TZCBCOSTCLR_CBC1_OFS               (0)                             /* !< CBC1 Offset */
#define MCPWM_TZCBCOSTCLR_CBC1_MASK              ((uint32_t)0x00000001U)         /* !< CBC TZ1 Clear */
/* MCPWM_TZCBCOSTCLR[CBC2] Bits */
#define MCPWM_TZCBCOSTCLR_CBC2_OFS               (1)                             /* !< CBC2 Offset */
#define MCPWM_TZCBCOSTCLR_CBC2_MASK              ((uint32_t)0x00000002U)         /* !< CBC TZ2 Clear */
/* MCPWM_TZCBCOSTCLR[CBC3] Bits */
#define MCPWM_TZCBCOSTCLR_CBC3_OFS               (2)                             /* !< CBC3 Offset */
#define MCPWM_TZCBCOSTCLR_CBC3_MASK              ((uint32_t)0x00000004U)         /* !< CBC TZ3 Clear */
/* MCPWM_TZCBCOSTCLR[CBC4] Bits */
#define MCPWM_TZCBCOSTCLR_CBC4_OFS               (3)                             /* !< CBC4 Offset */
#define MCPWM_TZCBCOSTCLR_CBC4_MASK              ((uint32_t)0x00000008U)         /* !< CBC TZ4 Clear */
/* MCPWM_TZCBCOSTCLR[CBC5] Bits */
#define MCPWM_TZCBCOSTCLR_CBC5_OFS               (4)                             /* !< CBC5 Offset */
#define MCPWM_TZCBCOSTCLR_CBC5_MASK              ((uint32_t)0x00000010U)         /* !< CBC TZ5 Clear */
/* MCPWM_TZCBCOSTCLR[CBC6] Bits */
#define MCPWM_TZCBCOSTCLR_CBC6_OFS               (5)                             /* !< CBC6 Offset */
#define MCPWM_TZCBCOSTCLR_CBC6_MASK              ((uint32_t)0x00000020U)         /* !< CBC TZ6 Clear */
/* MCPWM_TZCBCOSTCLR[CBC7] Bits */
#define MCPWM_TZCBCOSTCLR_CBC7_OFS               (6)                             /* !< CBC7 Offset */
#define MCPWM_TZCBCOSTCLR_CBC7_MASK              ((uint32_t)0x00000040U)         /* !< CBC TZ7 Clear */
/* MCPWM_TZCBCOSTCLR[CBC8] Bits */
#define MCPWM_TZCBCOSTCLR_CBC8_OFS               (7)                             /* !< CBC8 Offset */
#define MCPWM_TZCBCOSTCLR_CBC8_MASK              ((uint32_t)0x00000080U)         /* !< OST TZ8 Clear */
/* MCPWM_TZCBCOSTCLR[OST1] Bits */
#define MCPWM_TZCBCOSTCLR_OST1_OFS               (16)                            /* !< OST1 Offset */
#define MCPWM_TZCBCOSTCLR_OST1_MASK              ((uint32_t)0x00010000U)         /* !< OST TZ1 Clear */
/* MCPWM_TZCBCOSTCLR[OST2] Bits */
#define MCPWM_TZCBCOSTCLR_OST2_OFS               (17)                            /* !< OST2 Offset */
#define MCPWM_TZCBCOSTCLR_OST2_MASK              ((uint32_t)0x00020000U)         /* !< OST TZ2 Clear */
/* MCPWM_TZCBCOSTCLR[OST3] Bits */
#define MCPWM_TZCBCOSTCLR_OST3_OFS               (18)                            /* !< OST3 Offset */
#define MCPWM_TZCBCOSTCLR_OST3_MASK              ((uint32_t)0x00040000U)         /* !< OST TZ3 Clear */
/* MCPWM_TZCBCOSTCLR[OST4] Bits */
#define MCPWM_TZCBCOSTCLR_OST4_OFS               (19)                            /* !< OST4 Offset */
#define MCPWM_TZCBCOSTCLR_OST4_MASK              ((uint32_t)0x00080000U)         /* !< OST TZ4 Clear */
/* MCPWM_TZCBCOSTCLR[OST5] Bits */
#define MCPWM_TZCBCOSTCLR_OST5_OFS               (20)                            /* !< OST5 Offset */
#define MCPWM_TZCBCOSTCLR_OST5_MASK              ((uint32_t)0x00100000U)         /* !< OST TZ5 Clear */
/* MCPWM_TZCBCOSTCLR[OST6] Bits */
#define MCPWM_TZCBCOSTCLR_OST6_OFS               (21)                            /* !< OST6 Offset */
#define MCPWM_TZCBCOSTCLR_OST6_MASK              ((uint32_t)0x00200000U)         /* !< OST TZ6 Clear */
/* MCPWM_TZCBCOSTCLR[OST7] Bits */
#define MCPWM_TZCBCOSTCLR_OST7_OFS               (22)                            /* !< OST7 Offset */
#define MCPWM_TZCBCOSTCLR_OST7_MASK              ((uint32_t)0x00400000U)         /* !< OST TZ7 Clear */
/* MCPWM_TZCBCOSTCLR[OST8] Bits */
#define MCPWM_TZCBCOSTCLR_OST8_OFS               (23)                            /* !< OST8 Offset */
#define MCPWM_TZCBCOSTCLR_OST8_MASK              ((uint32_t)0x00800000U)         /* !< OST TZ8 Clear */

/* MCPWM_DBCTL Bits */
/* MCPWM_DBCTL[OUT_MODE] Bits */
#define MCPWM_DBCTL_OUT_MODE_OFS                 (0)                             /* !< OUT_MODE Offset */
#define MCPWM_DBCTL_OUT_MODE_MASK                ((uint32_t)0x00000003U)         /* !< Dead Band Output Mode Control */
/* MCPWM_DBCTL[POLSEL] Bits */
#define MCPWM_DBCTL_POLSEL_OFS                   (2)                             /* !< POLSEL Offset */
#define MCPWM_DBCTL_POLSEL_MASK                  ((uint32_t)0x0000000CU)         /* !< Polarity Select Control */
/* MCPWM_DBCTL[IN_MODE] Bits */
#define MCPWM_DBCTL_IN_MODE_OFS                  (4)                             /* !< IN_MODE Offset */
#define MCPWM_DBCTL_IN_MODE_MASK                 ((uint32_t)0x00000030U)         /* !< Dead Band Input Select Mode Control */
/* MCPWM_DBCTL[OUTSWAP] Bits */
#define MCPWM_DBCTL_OUTSWAP_OFS                  (6)                             /* !< OUTSWAP Offset */
#define MCPWM_DBCTL_OUTSWAP_MASK                 ((uint32_t)0x000000C0U)         /* !< Dead Band Output Swap Control */
/* MCPWM_DBCTL[DEDB_MODE] Bits */
#define MCPWM_DBCTL_DEDB_MODE_OFS                (8)                             /* !< DEDB_MODE Offset */
#define MCPWM_DBCTL_DEDB_MODE_MASK               ((uint32_t)0x00000100U)         /* !< Dead Band Dual-Edge B Mode Control */
/* MCPWM_DBCTL[LOADFEDMODE] Bits */
#define MCPWM_DBCTL_LOADFEDMODE_OFS              (16)                            /* !< LOADFEDMODE Offset */
#define MCPWM_DBCTL_LOADFEDMODE_MASK             ((uint32_t)0x00030000U)         /* !< Shadow to active load of DBFED */
/* MCPWM_DBCTL[LOADREDMODE] Bits */
#define MCPWM_DBCTL_LOADREDMODE_OFS              (18)                            /* !< LOADREDMODE Offset */
#define MCPWM_DBCTL_LOADREDMODE_MASK             ((uint32_t)0x000C0000U)         /* !< Shadow to active load of DBRED */

/* MCPWM_DBFED Bits */
/* MCPWM_DBFED[DBFED] Bits */
#define MCPWM_DBFED_DBFED_OFS                    (0)                             /* !< DBFED Offset */
#define MCPWM_DBFED_DBFED_MASK                   ((uint32_t)0x00003FFFU)         /* !< Falling edge delay value */

/* MCPWM_DBRED Bits */
/* MCPWM_DBRED[DBRED] Bits */
#define MCPWM_DBRED_DBRED_OFS                    (0)                             /* !< DBRED Offset */
#define MCPWM_DBRED_DBRED_MASK                   ((uint32_t)0x00003FFFU)         /* !< Rising edge delay value */

/* MCPWM_DBFEDS Bits */
/* MCPWM_DBFEDS[DBFEDS] Bits */
#define MCPWM_DBFEDS_DBFEDS_OFS                  (0)                             /* !< DBFEDS Offset */
#define MCPWM_DBFEDS_DBFEDS_MASK                 ((uint32_t)0x00003FFFU)         /* !< Falling edge delay shadow register */

/* MCPWM_DBREDS Bits */
/* MCPWM_DBREDS[DBREDS] Bits */
#define MCPWM_DBREDS_DBREDS_OFS                  (0)                             /* !< DBREDS Offset */
#define MCPWM_DBREDS_DBREDS_MASK                 ((uint32_t)0x00003FFFU)         /* !< Rising edge delay shadow register */

/* MCPWM_GLDCTL Bits */
/* MCPWM_GLDCTL[GLD] Bits */
#define MCPWM_GLDCTL_GLD_OFS                     (0)                             /* !< GLD Offset */
#define MCPWM_GLDCTL_GLD_MASK                    ((uint32_t)0x00000001U)         /* !< Global load enable */
/* MCPWM_GLDCTL[OSHTMODE] Bits */
#define MCPWM_GLDCTL_OSHTMODE_OFS                (1)                             /* !< OSHTMODE Offset */
#define MCPWM_GLDCTL_OSHTMODE_MASK               ((uint32_t)0x00000002U)         /* !< Global load one-shot enable */
/* MCPWM_GLDCTL[GLDMODE] Bits */
#define MCPWM_GLDCTL_GLDMODE_OFS                 (4)                             /* !< GLDMODE Offset */
#define MCPWM_GLDCTL_GLDMODE_MASK                ((uint32_t)0x00000030U)         /* !< Select global load event */

/* MCPWM_GLDOSHTCTL Bits */
/* MCPWM_GLDOSHTCTL[OSHTLD] Bits */
#define MCPWM_GLDOSHTCTL_OSHTLD_OFS              (0)                             /* !< OSHTLD Offset */
#define MCPWM_GLDOSHTCTL_OSHTLD_MASK             ((uint32_t)0x00000001U)         /* !< Enable Reload Event in One Shot
                                                                                    Mode */
/* MCPWM_GLDOSHTCTL[OSHTCLR] Bits */
#define MCPWM_GLDOSHTCTL_OSHTCLR_OFS             (1)                             /* !< OSHTCLR Offset */
#define MCPWM_GLDOSHTCTL_OSHTCLR_MASK            ((uint32_t)0x00000002U)         /* !< Enable Reload Event in One Shot
                                                                                    Mode */
/* MCPWM_GLDOSHTCTL[GFRCLD] Bits */
#define MCPWM_GLDOSHTCTL_GFRCLD_OFS              (2)                             /* !< GFRCLD Offset */
#define MCPWM_GLDOSHTCTL_GFRCLD_MASK             ((uint32_t)0x00000004U)         /* !< Force load event in one shot mode */

/* MCPWM_GLDOSHTSTS Bits */
/* MCPWM_GLDOSHTSTS[OSHTLATCH] Bits */
#define MCPWM_GLDOSHTSTS_OSHTLATCH_OFS           (0)                             /* !< OSHTLATCH Offset */
#define MCPWM_GLDOSHTSTS_OSHTLATCH_MASK          ((uint32_t)0x00000001U)         /* !< One shot latch output */

/* MCPWM_PWM1_CMPA Bits */
/* MCPWM_PWM1_CMPA[PWM1_CMPA] Bits */
#define MCPWM_PWM1_CMPA_PWM1_CMPA_OFS            (0)                             /* !< PWM1_CMPA Offset */
#define MCPWM_PWM1_CMPA_PWM1_CMPA_MASK           ((uint32_t)0x0000FFFFU)         /* !< PWM1 Compare A register */

/* MCPWM_PWM1_CMPAS Bits */
/* MCPWM_PWM1_CMPAS[PWM1_CMPAS] Bits */
#define MCPWM_PWM1_CMPAS_PWM1_CMPAS_OFS          (0)                             /* !< PWM1_CMPAS Offset */
#define MCPWM_PWM1_CMPAS_PWM1_CMPAS_MASK         ((uint32_t)0x0000FFFFU)         /* !< PWM1 Compare A shadow register */

/* MCPWM_PWM1_CMPB Bits */
/* MCPWM_PWM1_CMPB[PWM1_CMPB] Bits */
#define MCPWM_PWM1_CMPB_PWM1_CMPB_OFS            (0)                             /* !< PWM1_CMPB Offset */
#define MCPWM_PWM1_CMPB_PWM1_CMPB_MASK           ((uint32_t)0x0000FFFFU)         /* !< PWM1 Compare B register */

/* MCPWM_PWM1_CMPBS Bits */
/* MCPWM_PWM1_CMPBS[PWM1_CMPBS] Bits */
#define MCPWM_PWM1_CMPBS_PWM1_CMPBS_OFS          (0)                             /* !< PWM1_CMPBS Offset */
#define MCPWM_PWM1_CMPBS_PWM1_CMPBS_MASK         ((uint32_t)0x0000FFFFU)         /* !< PWM1 Compare B shadow register */

/* MCPWM_PWM1_AQCTLA Bits */
/* MCPWM_PWM1_AQCTLA[ZRO] Bits */
#define MCPWM_PWM1_AQCTLA_ZRO_OFS                (0)                             /* !< ZRO Offset */
#define MCPWM_PWM1_AQCTLA_ZRO_MASK               ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM1_AQCTLA[PRD] Bits */
#define MCPWM_PWM1_AQCTLA_PRD_OFS                (2)                             /* !< PRD Offset */
#define MCPWM_PWM1_AQCTLA_PRD_MASK               ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM1_AQCTLA[CAU] Bits */
#define MCPWM_PWM1_AQCTLA_CAU_OFS                (4)                             /* !< CAU Offset */
#define MCPWM_PWM1_AQCTLA_CAU_MASK               ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM1_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM1_AQCTLA[CAD] Bits */
#define MCPWM_PWM1_AQCTLA_CAD_OFS                (6)                             /* !< CAD Offset */
#define MCPWM_PWM1_AQCTLA_CAD_MASK               ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM1_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM1_AQCTLA[CBU] Bits */
#define MCPWM_PWM1_AQCTLA_CBU_OFS                (8)                             /* !< CBU Offset */
#define MCPWM_PWM1_AQCTLA_CBU_MASK               ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM1_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM1_AQCTLA[CBD] Bits */
#define MCPWM_PWM1_AQCTLA_CBD_OFS                (10)                            /* !< CBD Offset */
#define MCPWM_PWM1_AQCTLA_CBD_MASK               ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM1_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM1_AQCTLAS Bits */
/* MCPWM_PWM1_AQCTLAS[ZRO] Bits */
#define MCPWM_PWM1_AQCTLAS_ZRO_OFS               (0)                             /* !< ZRO Offset */
#define MCPWM_PWM1_AQCTLAS_ZRO_MASK              ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM1_AQCTLAS[PRD] Bits */
#define MCPWM_PWM1_AQCTLAS_PRD_OFS               (2)                             /* !< PRD Offset */
#define MCPWM_PWM1_AQCTLAS_PRD_MASK              ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM1_AQCTLAS[CAU] Bits */
#define MCPWM_PWM1_AQCTLAS_CAU_OFS               (4)                             /* !< CAU Offset */
#define MCPWM_PWM1_AQCTLAS_CAU_MASK              ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM1_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM1_AQCTLAS[CAD] Bits */
#define MCPWM_PWM1_AQCTLAS_CAD_OFS               (6)                             /* !< CAD Offset */
#define MCPWM_PWM1_AQCTLAS_CAD_MASK              ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM1_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM1_AQCTLAS[CBU] Bits */
#define MCPWM_PWM1_AQCTLAS_CBU_OFS               (8)                             /* !< CBU Offset */
#define MCPWM_PWM1_AQCTLAS_CBU_MASK              ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM1_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM1_AQCTLAS[CBD] Bits */
#define MCPWM_PWM1_AQCTLAS_CBD_OFS               (10)                            /* !< CBD Offset */
#define MCPWM_PWM1_AQCTLAS_CBD_MASK              ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM1_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM1_AQCTLB Bits */
/* MCPWM_PWM1_AQCTLB[ZRO] Bits */
#define MCPWM_PWM1_AQCTLB_ZRO_OFS                (0)                             /* !< ZRO Offset */
#define MCPWM_PWM1_AQCTLB_ZRO_MASK               ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM1_AQCTLB[PRD] Bits */
#define MCPWM_PWM1_AQCTLB_PRD_OFS                (2)                             /* !< PRD Offset */
#define MCPWM_PWM1_AQCTLB_PRD_MASK               ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM1_AQCTLB[CAU] Bits */
#define MCPWM_PWM1_AQCTLB_CAU_OFS                (4)                             /* !< CAU Offset */
#define MCPWM_PWM1_AQCTLB_CAU_MASK               ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM1_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM1_AQCTLB[CAD] Bits */
#define MCPWM_PWM1_AQCTLB_CAD_OFS                (6)                             /* !< CAD Offset */
#define MCPWM_PWM1_AQCTLB_CAD_MASK               ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM1_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM1_AQCTLB[CBU] Bits */
#define MCPWM_PWM1_AQCTLB_CBU_OFS                (8)                             /* !< CBU Offset */
#define MCPWM_PWM1_AQCTLB_CBU_MASK               ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM1_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM1_AQCTLB[CBD] Bits */
#define MCPWM_PWM1_AQCTLB_CBD_OFS                (10)                            /* !< CBD Offset */
#define MCPWM_PWM1_AQCTLB_CBD_MASK               ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM1_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM1_AQCTLBS Bits */
/* MCPWM_PWM1_AQCTLBS[ZRO] Bits */
#define MCPWM_PWM1_AQCTLBS_ZRO_OFS               (0)                             /* !< ZRO Offset */
#define MCPWM_PWM1_AQCTLBS_ZRO_MASK              ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM1_AQCTLBS[PRD] Bits */
#define MCPWM_PWM1_AQCTLBS_PRD_OFS               (2)                             /* !< PRD Offset */
#define MCPWM_PWM1_AQCTLBS_PRD_MASK              ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM1_AQCTLBS[CAU] Bits */
#define MCPWM_PWM1_AQCTLBS_CAU_OFS               (4)                             /* !< CAU Offset */
#define MCPWM_PWM1_AQCTLBS_CAU_MASK              ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM1_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM1_AQCTLBS[CAD] Bits */
#define MCPWM_PWM1_AQCTLBS_CAD_OFS               (6)                             /* !< CAD Offset */
#define MCPWM_PWM1_AQCTLBS_CAD_MASK              ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM1_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM1_AQCTLBS[CBU] Bits */
#define MCPWM_PWM1_AQCTLBS_CBU_OFS               (8)                             /* !< CBU Offset */
#define MCPWM_PWM1_AQCTLBS_CBU_MASK              ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM1_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM1_AQCTLBS[CBD] Bits */
#define MCPWM_PWM1_AQCTLBS_CBD_OFS               (10)                            /* !< CBD Offset */
#define MCPWM_PWM1_AQCTLBS_CBD_MASK              ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM1_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM1_AQSFRC Bits */
/* MCPWM_PWM1_AQSFRC[PWMA] Bits */
#define MCPWM_PWM1_AQSFRC_PWMA_OFS               (0)                             /* !< PWMA Offset */
#define MCPWM_PWM1_AQSFRC_PWMA_MASK              ((uint32_t)0x00000007U)         /* !< Action qualifier software force on
                                                                                    PWMA */
/* MCPWM_PWM1_AQSFRC[PWMB] Bits */
#define MCPWM_PWM1_AQSFRC_PWMB_OFS               (4)                             /* !< PWMB Offset */
#define MCPWM_PWM1_AQSFRC_PWMB_MASK              ((uint32_t)0x00000070U)         /* !< Action qualifier software force on
                                                                                    PWMB */

/* MCPWM_PWM1_AQOTSFRC Bits */
/* MCPWM_PWM1_AQOTSFRC[PWMA] Bits */
#define MCPWM_PWM1_AQOTSFRC_PWMA_OFS             (0)                             /* !< PWMA Offset */
#define MCPWM_PWM1_AQOTSFRC_PWMA_MASK            ((uint32_t)0x00000001U)         /* !< Action qualifier one time software
                                                                                    force on PWMA */
/* MCPWM_PWM1_AQOTSFRC[PWMB] Bits */
#define MCPWM_PWM1_AQOTSFRC_PWMB_OFS             (4)                             /* !< PWMB Offset */
#define MCPWM_PWM1_AQOTSFRC_PWMB_MASK            ((uint32_t)0x00000010U)         /* !< Action qualifier software force on
                                                                                    PWMB */

/* MCPWM_PWM2_CMPA Bits */
/* MCPWM_PWM2_CMPA[PWM2_CMPA] Bits */
#define MCPWM_PWM2_CMPA_PWM2_CMPA_OFS            (0)                             /* !< PWM2_CMPA Offset */
#define MCPWM_PWM2_CMPA_PWM2_CMPA_MASK           ((uint32_t)0x0000FFFFU)         /* !< PWM2 Compare A register */

/* MCPWM_PWM2_CMPAS Bits */
/* MCPWM_PWM2_CMPAS[PWM2_CMPAS] Bits */
#define MCPWM_PWM2_CMPAS_PWM2_CMPAS_OFS          (0)                             /* !< PWM2_CMPAS Offset */
#define MCPWM_PWM2_CMPAS_PWM2_CMPAS_MASK         ((uint32_t)0x0000FFFFU)         /* !< PWM2 Compare A shadow register */

/* MCPWM_PWM2_CMPB Bits */
/* MCPWM_PWM2_CMPB[PWM2_CMPB] Bits */
#define MCPWM_PWM2_CMPB_PWM2_CMPB_OFS            (0)                             /* !< PWM2_CMPB Offset */
#define MCPWM_PWM2_CMPB_PWM2_CMPB_MASK           ((uint32_t)0x0000FFFFU)         /* !< PWM2 Compare B register */

/* MCPWM_PWM2_CMPBS Bits */
/* MCPWM_PWM2_CMPBS[PWM2_CMPBS] Bits */
#define MCPWM_PWM2_CMPBS_PWM2_CMPBS_OFS          (0)                             /* !< PWM2_CMPBS Offset */
#define MCPWM_PWM2_CMPBS_PWM2_CMPBS_MASK         ((uint32_t)0x0000FFFFU)         /* !< PWM2 Compare B shadow register */

/* MCPWM_PWM2_AQCTLA Bits */
/* MCPWM_PWM2_AQCTLA[ZRO] Bits */
#define MCPWM_PWM2_AQCTLA_ZRO_OFS                (0)                             /* !< ZRO Offset */
#define MCPWM_PWM2_AQCTLA_ZRO_MASK               ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM2_AQCTLA[PRD] Bits */
#define MCPWM_PWM2_AQCTLA_PRD_OFS                (2)                             /* !< PRD Offset */
#define MCPWM_PWM2_AQCTLA_PRD_MASK               ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM2_AQCTLA[CAU] Bits */
#define MCPWM_PWM2_AQCTLA_CAU_OFS                (4)                             /* !< CAU Offset */
#define MCPWM_PWM2_AQCTLA_CAU_MASK               ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM2_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM2_AQCTLA[CAD] Bits */
#define MCPWM_PWM2_AQCTLA_CAD_OFS                (6)                             /* !< CAD Offset */
#define MCPWM_PWM2_AQCTLA_CAD_MASK               ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM2_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM2_AQCTLA[CBU] Bits */
#define MCPWM_PWM2_AQCTLA_CBU_OFS                (8)                             /* !< CBU Offset */
#define MCPWM_PWM2_AQCTLA_CBU_MASK               ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM2_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM2_AQCTLA[CBD] Bits */
#define MCPWM_PWM2_AQCTLA_CBD_OFS                (10)                            /* !< CBD Offset */
#define MCPWM_PWM2_AQCTLA_CBD_MASK               ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM2_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM2_AQCTLAS Bits */
/* MCPWM_PWM2_AQCTLAS[ZRO] Bits */
#define MCPWM_PWM2_AQCTLAS_ZRO_OFS               (0)                             /* !< ZRO Offset */
#define MCPWM_PWM2_AQCTLAS_ZRO_MASK              ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM2_AQCTLAS[PRD] Bits */
#define MCPWM_PWM2_AQCTLAS_PRD_OFS               (2)                             /* !< PRD Offset */
#define MCPWM_PWM2_AQCTLAS_PRD_MASK              ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM2_AQCTLAS[CAU] Bits */
#define MCPWM_PWM2_AQCTLAS_CAU_OFS               (4)                             /* !< CAU Offset */
#define MCPWM_PWM2_AQCTLAS_CAU_MASK              ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM2_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM2_AQCTLAS[CAD] Bits */
#define MCPWM_PWM2_AQCTLAS_CAD_OFS               (6)                             /* !< CAD Offset */
#define MCPWM_PWM2_AQCTLAS_CAD_MASK              ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM2_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM2_AQCTLAS[CBU] Bits */
#define MCPWM_PWM2_AQCTLAS_CBU_OFS               (8)                             /* !< CBU Offset */
#define MCPWM_PWM2_AQCTLAS_CBU_MASK              ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM2_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM2_AQCTLAS[CBD] Bits */
#define MCPWM_PWM2_AQCTLAS_CBD_OFS               (10)                            /* !< CBD Offset */
#define MCPWM_PWM2_AQCTLAS_CBD_MASK              ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM2_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM2_AQCTLB Bits */
/* MCPWM_PWM2_AQCTLB[ZRO] Bits */
#define MCPWM_PWM2_AQCTLB_ZRO_OFS                (0)                             /* !< ZRO Offset */
#define MCPWM_PWM2_AQCTLB_ZRO_MASK               ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM2_AQCTLB[PRD] Bits */
#define MCPWM_PWM2_AQCTLB_PRD_OFS                (2)                             /* !< PRD Offset */
#define MCPWM_PWM2_AQCTLB_PRD_MASK               ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM2_AQCTLB[CAU] Bits */
#define MCPWM_PWM2_AQCTLB_CAU_OFS                (4)                             /* !< CAU Offset */
#define MCPWM_PWM2_AQCTLB_CAU_MASK               ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM2_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM2_AQCTLB[CAD] Bits */
#define MCPWM_PWM2_AQCTLB_CAD_OFS                (6)                             /* !< CAD Offset */
#define MCPWM_PWM2_AQCTLB_CAD_MASK               ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM2_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM2_AQCTLB[CBU] Bits */
#define MCPWM_PWM2_AQCTLB_CBU_OFS                (8)                             /* !< CBU Offset */
#define MCPWM_PWM2_AQCTLB_CBU_MASK               ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM2_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM2_AQCTLB[CBD] Bits */
#define MCPWM_PWM2_AQCTLB_CBD_OFS                (10)                            /* !< CBD Offset */
#define MCPWM_PWM2_AQCTLB_CBD_MASK               ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM2_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM2_AQCTLBS Bits */
/* MCPWM_PWM2_AQCTLBS[ZRO] Bits */
#define MCPWM_PWM2_AQCTLBS_ZRO_OFS               (0)                             /* !< ZRO Offset */
#define MCPWM_PWM2_AQCTLBS_ZRO_MASK              ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM2_AQCTLBS[PRD] Bits */
#define MCPWM_PWM2_AQCTLBS_PRD_OFS               (2)                             /* !< PRD Offset */
#define MCPWM_PWM2_AQCTLBS_PRD_MASK              ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM2_AQCTLBS[CAU] Bits */
#define MCPWM_PWM2_AQCTLBS_CAU_OFS               (4)                             /* !< CAU Offset */
#define MCPWM_PWM2_AQCTLBS_CAU_MASK              ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM2_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM2_AQCTLBS[CAD] Bits */
#define MCPWM_PWM2_AQCTLBS_CAD_OFS               (6)                             /* !< CAD Offset */
#define MCPWM_PWM2_AQCTLBS_CAD_MASK              ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM2_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM2_AQCTLBS[CBU] Bits */
#define MCPWM_PWM2_AQCTLBS_CBU_OFS               (8)                             /* !< CBU Offset */
#define MCPWM_PWM2_AQCTLBS_CBU_MASK              ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM2_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM2_AQCTLBS[CBD] Bits */
#define MCPWM_PWM2_AQCTLBS_CBD_OFS               (10)                            /* !< CBD Offset */
#define MCPWM_PWM2_AQCTLBS_CBD_MASK              ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM2_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM2_AQSFRC Bits */
/* MCPWM_PWM2_AQSFRC[PWMA] Bits */
#define MCPWM_PWM2_AQSFRC_PWMA_OFS               (0)                             /* !< PWMA Offset */
#define MCPWM_PWM2_AQSFRC_PWMA_MASK              ((uint32_t)0x00000007U)         /* !< Action qualifier software force on
                                                                                    PWMA */
/* MCPWM_PWM2_AQSFRC[PWMB] Bits */
#define MCPWM_PWM2_AQSFRC_PWMB_OFS               (4)                             /* !< PWMB Offset */
#define MCPWM_PWM2_AQSFRC_PWMB_MASK              ((uint32_t)0x00000070U)         /* !< Action qualifier software force on
                                                                                    PWMB */

/* MCPWM_PWM2_AQOTSFRC Bits */
/* MCPWM_PWM2_AQOTSFRC[PWMA] Bits */
#define MCPWM_PWM2_AQOTSFRC_PWMA_OFS             (0)                             /* !< PWMA Offset */
#define MCPWM_PWM2_AQOTSFRC_PWMA_MASK            ((uint32_t)0x00000001U)         /* !< Action qualifier one time software
                                                                                    force on PWMA */
/* MCPWM_PWM2_AQOTSFRC[PWMB] Bits */
#define MCPWM_PWM2_AQOTSFRC_PWMB_OFS             (4)                             /* !< PWMB Offset */
#define MCPWM_PWM2_AQOTSFRC_PWMB_MASK            ((uint32_t)0x00000010U)         /* !< Action qualifier software force on
                                                                                    PWMB */

/* MCPWM_PWM3_CMPA Bits */
/* MCPWM_PWM3_CMPA[PWM3_CMPA] Bits */
#define MCPWM_PWM3_CMPA_PWM3_CMPA_OFS            (0)                             /* !< PWM3_CMPA Offset */
#define MCPWM_PWM3_CMPA_PWM3_CMPA_MASK           ((uint32_t)0x0000FFFFU)         /* !< PWM3 Compare A register */

/* MCPWM_PWM3_CMPAS Bits */
/* MCPWM_PWM3_CMPAS[PWM3_CMPAS] Bits */
#define MCPWM_PWM3_CMPAS_PWM3_CMPAS_OFS          (0)                             /* !< PWM3_CMPAS Offset */
#define MCPWM_PWM3_CMPAS_PWM3_CMPAS_MASK         ((uint32_t)0x0000FFFFU)         /* !< PWM3 Compare A shadow register */

/* MCPWM_PWM3_CMPB Bits */
/* MCPWM_PWM3_CMPB[PWM3_CMPB] Bits */
#define MCPWM_PWM3_CMPB_PWM3_CMPB_OFS            (0)                             /* !< PWM3_CMPB Offset */
#define MCPWM_PWM3_CMPB_PWM3_CMPB_MASK           ((uint32_t)0x0000FFFFU)         /* !< PWM3 Compare B register */

/* MCPWM_PWM3_CMPBS Bits */
/* MCPWM_PWM3_CMPBS[PWM3_CMPBS] Bits */
#define MCPWM_PWM3_CMPBS_PWM3_CMPBS_OFS          (0)                             /* !< PWM3_CMPBS Offset */
#define MCPWM_PWM3_CMPBS_PWM3_CMPBS_MASK         ((uint32_t)0x0000FFFFU)         /* !< PWM3 Compare B shadow register */

/* MCPWM_PWM3_AQCTLA Bits */
/* MCPWM_PWM3_AQCTLA[ZRO] Bits */
#define MCPWM_PWM3_AQCTLA_ZRO_OFS                (0)                             /* !< ZRO Offset */
#define MCPWM_PWM3_AQCTLA_ZRO_MASK               ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM3_AQCTLA[PRD] Bits */
#define MCPWM_PWM3_AQCTLA_PRD_OFS                (2)                             /* !< PRD Offset */
#define MCPWM_PWM3_AQCTLA_PRD_MASK               ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM3_AQCTLA[CAU] Bits */
#define MCPWM_PWM3_AQCTLA_CAU_OFS                (4)                             /* !< CAU Offset */
#define MCPWM_PWM3_AQCTLA_CAU_MASK               ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM3_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM3_AQCTLA[CAD] Bits */
#define MCPWM_PWM3_AQCTLA_CAD_OFS                (6)                             /* !< CAD Offset */
#define MCPWM_PWM3_AQCTLA_CAD_MASK               ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM3_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM3_AQCTLA[CBU] Bits */
#define MCPWM_PWM3_AQCTLA_CBU_OFS                (8)                             /* !< CBU Offset */
#define MCPWM_PWM3_AQCTLA_CBU_MASK               ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM3_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM3_AQCTLA[CBD] Bits */
#define MCPWM_PWM3_AQCTLA_CBD_OFS                (10)                            /* !< CBD Offset */
#define MCPWM_PWM3_AQCTLA_CBD_MASK               ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM3_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM3_AQCTLAS Bits */
/* MCPWM_PWM3_AQCTLAS[ZRO] Bits */
#define MCPWM_PWM3_AQCTLAS_ZRO_OFS               (0)                             /* !< ZRO Offset */
#define MCPWM_PWM3_AQCTLAS_ZRO_MASK              ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM3_AQCTLAS[PRD] Bits */
#define MCPWM_PWM3_AQCTLAS_PRD_OFS               (2)                             /* !< PRD Offset */
#define MCPWM_PWM3_AQCTLAS_PRD_MASK              ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM3_AQCTLAS[CAU] Bits */
#define MCPWM_PWM3_AQCTLAS_CAU_OFS               (4)                             /* !< CAU Offset */
#define MCPWM_PWM3_AQCTLAS_CAU_MASK              ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM3_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM3_AQCTLAS[CAD] Bits */
#define MCPWM_PWM3_AQCTLAS_CAD_OFS               (6)                             /* !< CAD Offset */
#define MCPWM_PWM3_AQCTLAS_CAD_MASK              ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM3_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM3_AQCTLAS[CBU] Bits */
#define MCPWM_PWM3_AQCTLAS_CBU_OFS               (8)                             /* !< CBU Offset */
#define MCPWM_PWM3_AQCTLAS_CBU_MASK              ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM3_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM3_AQCTLAS[CBD] Bits */
#define MCPWM_PWM3_AQCTLAS_CBD_OFS               (10)                            /* !< CBD Offset */
#define MCPWM_PWM3_AQCTLAS_CBD_MASK              ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM3_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM3_AQCTLB Bits */
/* MCPWM_PWM3_AQCTLB[ZRO] Bits */
#define MCPWM_PWM3_AQCTLB_ZRO_OFS                (0)                             /* !< ZRO Offset */
#define MCPWM_PWM3_AQCTLB_ZRO_MASK               ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM3_AQCTLB[PRD] Bits */
#define MCPWM_PWM3_AQCTLB_PRD_OFS                (2)                             /* !< PRD Offset */
#define MCPWM_PWM3_AQCTLB_PRD_MASK               ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM3_AQCTLB[CAU] Bits */
#define MCPWM_PWM3_AQCTLB_CAU_OFS                (4)                             /* !< CAU Offset */
#define MCPWM_PWM3_AQCTLB_CAU_MASK               ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM3_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM3_AQCTLB[CAD] Bits */
#define MCPWM_PWM3_AQCTLB_CAD_OFS                (6)                             /* !< CAD Offset */
#define MCPWM_PWM3_AQCTLB_CAD_MASK               ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM3_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM3_AQCTLB[CBU] Bits */
#define MCPWM_PWM3_AQCTLB_CBU_OFS                (8)                             /* !< CBU Offset */
#define MCPWM_PWM3_AQCTLB_CBU_MASK               ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM3_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM3_AQCTLB[CBD] Bits */
#define MCPWM_PWM3_AQCTLB_CBD_OFS                (10)                            /* !< CBD Offset */
#define MCPWM_PWM3_AQCTLB_CBD_MASK               ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM3_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM3_AQCTLBS Bits */
/* MCPWM_PWM3_AQCTLBS[ZRO] Bits */
#define MCPWM_PWM3_AQCTLBS_ZRO_OFS               (0)                             /* !< ZRO Offset */
#define MCPWM_PWM3_AQCTLBS_ZRO_MASK              ((uint32_t)0x00000003U)         /* !< Action When TBCTR = 0 */
/* MCPWM_PWM3_AQCTLBS[PRD] Bits */
#define MCPWM_PWM3_AQCTLBS_PRD_OFS               (2)                             /* !< PRD Offset */
#define MCPWM_PWM3_AQCTLBS_PRD_MASK              ((uint32_t)0x0000000CU)         /* !< Action When TBCTR = TBPRD */
/* MCPWM_PWM3_AQCTLBS[CAU] Bits */
#define MCPWM_PWM3_AQCTLBS_CAU_OFS               (4)                             /* !< CAU Offset */
#define MCPWM_PWM3_AQCTLBS_CAU_MASK              ((uint32_t)0x00000030U)         /* !< Action When TBCTR = PWM3_CMPA on Up
                                                                                    Count */
/* MCPWM_PWM3_AQCTLBS[CAD] Bits */
#define MCPWM_PWM3_AQCTLBS_CAD_OFS               (6)                             /* !< CAD Offset */
#define MCPWM_PWM3_AQCTLBS_CAD_MASK              ((uint32_t)0x000000C0U)         /* !< Action When TBCTR = PWM3_CMPA on
                                                                                    Down Count */
/* MCPWM_PWM3_AQCTLBS[CBU] Bits */
#define MCPWM_PWM3_AQCTLBS_CBU_OFS               (8)                             /* !< CBU Offset */
#define MCPWM_PWM3_AQCTLBS_CBU_MASK              ((uint32_t)0x00000300U)         /* !< Action When TBCTR = PWM3_CMPB on Up
                                                                                    Count */
/* MCPWM_PWM3_AQCTLBS[CBD] Bits */
#define MCPWM_PWM3_AQCTLBS_CBD_OFS               (10)                            /* !< CBD Offset */
#define MCPWM_PWM3_AQCTLBS_CBD_MASK              ((uint32_t)0x00000C00U)         /* !< Action When TBCTR = PWM3_CMPB on
                                                                                    Down Count */

/* MCPWM_PWM3_AQSFRC Bits */
/* MCPWM_PWM3_AQSFRC[PWMA] Bits */
#define MCPWM_PWM3_AQSFRC_PWMA_OFS               (0)                             /* !< PWMA Offset */
#define MCPWM_PWM3_AQSFRC_PWMA_MASK              ((uint32_t)0x00000007U)         /* !< Action qualifier software force on
                                                                                    PWMA */
/* MCPWM_PWM3_AQSFRC[PWMB] Bits */
#define MCPWM_PWM3_AQSFRC_PWMB_OFS               (4)                             /* !< PWMB Offset */
#define MCPWM_PWM3_AQSFRC_PWMB_MASK              ((uint32_t)0x00000070U)         /* !< Action qualifier software force on
                                                                                    PWMB */

/* MCPWM_PWM3_AQOTSFRC Bits */
/* MCPWM_PWM3_AQOTSFRC[PWMA] Bits */
#define MCPWM_PWM3_AQOTSFRC_PWMA_OFS             (0)                             /* !< PWMA Offset */
#define MCPWM_PWM3_AQOTSFRC_PWMA_MASK            ((uint32_t)0x00000001U)         /* !< Action qualifier one time software
                                                                                    force on PWMA */
/* MCPWM_PWM3_AQOTSFRC[PWMB] Bits */
#define MCPWM_PWM3_AQOTSFRC_PWMB_OFS             (4)                             /* !< PWMB Offset */
#define MCPWM_PWM3_AQOTSFRC_PWMB_MASK            ((uint32_t)0x00000010U)         /* !< Action qualifier software force on
                                                                                    PWMB */


#ifdef __cplusplus
}
#endif

#endif /* hw_mcpwm__include */

