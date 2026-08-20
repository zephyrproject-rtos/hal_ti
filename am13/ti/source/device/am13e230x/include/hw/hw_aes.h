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

#ifndef hw_aes__include
#define hw_aes__include


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
* AES Registers
******************************************************************************/
#define AES_INT_EVENT2_OFS                       ((uint32_t)0x00001080U)
#define AES_INT_EVENT1_OFS                       ((uint32_t)0x00001050U)
#define AES_INT_EVENT0_OFS                       ((uint32_t)0x00001020U)
#define AES_GPRCM_OFS                            ((uint32_t)0x00000800U)


/** @addtogroup AES_INT_EVENT2
  @{
*/

typedef struct {
  __I  uint32_t IIDX;                              /* !< (@ 0x00001080) Interrupt Index Register */
       uint32_t RESERVED0;
  __IO uint32_t IMASK;                             /* !< (@ 0x00001088) Interrupt mask */
       uint32_t RESERVED1;
  __I  uint32_t RIS;                               /* !< (@ 0x00001090) Raw interrupt status */
       uint32_t RESERVED2;
  __I  uint32_t MIS;                               /* !< (@ 0x00001098) Masked interrupt status */
       uint32_t RESERVED3;
  __O  uint32_t ISET;                              /* !< (@ 0x000010A0) Interrupt set */
       uint32_t RESERVED4;
  __O  uint32_t ICLR;                              /* !< (@ 0x000010A8) Interrupt clear */
} AES_INT_EVENT2_Regs;

/*@}*/ /* end of group AES_INT_EVENT2 */

/** @addtogroup AES_INT_EVENT1
  @{
*/

typedef struct {
  __I  uint32_t IIDX;                              /* !< (@ 0x00001050) Interrupt Index Register */
       uint32_t RESERVED0;
  __IO uint32_t IMASK;                             /* !< (@ 0x00001058) Interrupt mask */
       uint32_t RESERVED1;
  __I  uint32_t RIS;                               /* !< (@ 0x00001060) Raw interrupt status */
       uint32_t RESERVED2;
  __I  uint32_t MIS;                               /* !< (@ 0x00001068) Masked interrupt status */
       uint32_t RESERVED3;
  __O  uint32_t ISET;                              /* !< (@ 0x00001070) Interrupt set */
       uint32_t RESERVED4;
  __O  uint32_t ICLR;                              /* !< (@ 0x00001078) Interrupt clear */
} AES_INT_EVENT1_Regs;

/*@}*/ /* end of group AES_INT_EVENT1 */

/** @addtogroup AES_INT_EVENT0
  @{
*/

typedef struct {
  __I  uint32_t IIDX;                              /* !< (@ 0x00001020) Interrupt Index Register */
       uint32_t RESERVED0;
  __IO uint32_t IMASK;                             /* !< (@ 0x00001028) Interrupt mask */
       uint32_t RESERVED1;
  __I  uint32_t RIS;                               /* !< (@ 0x00001030) Raw interrupt status */
       uint32_t RESERVED2;
  __I  uint32_t MIS;                               /* !< (@ 0x00001038) Masked interrupt status */
       uint32_t RESERVED3;
  __O  uint32_t ISET;                              /* !< (@ 0x00001040) Interrupt set */
       uint32_t RESERVED4;
  __O  uint32_t ICLR;                              /* !< (@ 0x00001048) Interrupt clear */
} AES_INT_EVENT0_Regs;

/*@}*/ /* end of group AES_INT_EVENT0 */

/** @addtogroup AES_GPRCM
  @{
*/

typedef struct {
  __IO uint32_t PWREN;                             /* !< (@ 0x00000800) Power enable */
  __O  uint32_t RSTCTL;                            /* !< (@ 0x00000804) Reset Control */
       uint32_t RESERVED0[3];
  __I  uint32_t STAT;                              /* !< (@ 0x00000814) Status Register */
} AES_GPRCM_Regs;

/*@}*/ /* end of group AES_GPRCM */

/** @addtogroup AES
  @{
*/

typedef struct {
       uint32_t RESERVED0[512];
  AES_GPRCM_Regs  GPRCM;                             /* !< (@ 0x00000800) */
       uint32_t RESERVED1[512];
  __I  uint32_t PDBGCTL;                           /* !< (@ 0x00001018) Peripheral Debug Control */
       uint32_t RESERVED2;
  AES_INT_EVENT0_Regs  INT_EVENT0;                        /* !< (@ 0x00001020) */
       uint32_t RESERVED3;
  AES_INT_EVENT1_Regs  INT_EVENT1;                        /* !< (@ 0x00001050) */
       uint32_t RESERVED4;
  AES_INT_EVENT2_Regs  INT_EVENT2;                        /* !< (@ 0x00001080) */
       uint32_t RESERVED5[13];
  __IO uint32_t EVT_MODE;                          /* !< (@ 0x000010E0) Event Mode */
       uint32_t RESERVED6[7];
  __O  uint32_t GCMCCM_TAG0;                       /* !< (@ 0x00001100) CBC-MAC third key (LSW) / GCM & CCM Intermediate
                                                      TAG (LSW) */
  __O  uint32_t GCMCCM_TAG1;                       /* !< (@ 0x00001104) CBC-MAC third key / GCM & CCM Intermediate TAG */
  __O  uint32_t GCMCCM_TAG2;                       /* !< (@ 0x00001108) CBC-MAC third key / GCM & CCM Intermediate TAG */
  __O  uint32_t GCMCCM_TAG3;                       /* !< (@ 0x0000110C) CBC-MAC third key (MSW) / GCM & CCM Intermediate
                                                      TAG (MSW) */
  __O  uint32_t GHASH_H0;                          /* !< (@ 0x00001110) CCM & CBC-MAC second key (LSW) / GCM Hash Key
                                                      input (LSW) */
  __O  uint32_t GHASH_H1;                          /* !< (@ 0x00001114) CCM & CBC-MAC second key  / GCM Hash Key input */
  __O  uint32_t GHASH_H2;                          /* !< (@ 0x00001118) CCM & CBC-MAC second key  / GCM Hash Key input */
  __O  uint32_t GHASH_H3;                          /* !< (@ 0x0000111C) CCM & CBC-MAC second key (MSW) / GCM Hash Key
                                                      input (MSW) */
  __O  uint32_t KEY0;                              /* !< (@ 0x00001120) KEY (LSW) */
  __O  uint32_t KEY1;                              /* !< (@ 0x00001124) KEY */
  __O  uint32_t KEY2;                              /* !< (@ 0x00001128) KEY */
  __O  uint32_t KEY3;                              /* !< (@ 0x0000112C) KEY */
  __O  uint32_t KEY4;                              /* !< (@ 0x00001130) KEY */
  __O  uint32_t KEY5;                              /* !< (@ 0x00001134) KEY */
  __O  uint32_t KEY6;                              /* !< (@ 0x00001138) KEY */
  __O  uint32_t KEY7;                              /* !< (@ 0x0000113C) KEY (MSW) */
  __IO uint32_t IV0;                               /* !< (@ 0x00001140) IV (LSW) */
  __IO uint32_t IV1;                               /* !< (@ 0x00001144) IV */
  __IO uint32_t IV2;                               /* !< (@ 0x00001148) IV */
  __IO uint32_t IV3;                               /* !< (@ 0x0000114C) IV */
  __IO uint32_t CTRL;                              /* !< (@ 0x00001150) Input/Output Buffer Control and Mode selection */
  __O  uint32_t C_LENGTH_0;                        /* !< (@ 0x00001154) Crypto data length (LSW) */
  __O  uint32_t C_LENGTH_1;                        /* !< (@ 0x00001158) Crypto data length (MSW) */
  __O  uint32_t AAD_LENGTH;                        /* !< (@ 0x0000115C) AAD Data Length */
  __IO uint32_t DATA0;                             /* !< (@ 0x00001160) Data input (LSW) / Data output (LSW) */
  __IO uint32_t DATA1;                             /* !< (@ 0x00001164) Data input / Data output */
  __IO uint32_t DATA2;                             /* !< (@ 0x00001168) Data input / Data output */
  __IO uint32_t DATA3;                             /* !< (@ 0x0000116C) Data input (LSW) / Data output (MSW) */
  __I  uint32_t TAG0;                              /* !< (@ 0x00001170) Hash result (LSW) */
  __I  uint32_t TAG1;                              /* !< (@ 0x00001174) Hash result */
  __I  uint32_t TAG2;                              /* !< (@ 0x00001178) Hash result */
  __I  uint32_t TAG3;                              /* !< (@ 0x0000117C) Hash result (MSW) */
  __I  uint32_t STATUS;                            /* !< (@ 0x00001180) Status */
  __O  uint32_t DATA_IN;                           /* !< (@ 0x00001184) Data in alias register */
  __I  uint32_t DATA_OUT;                          /* !< (@ 0x00001188) Data out alias register */
       uint32_t RESERVED7[17];
  __O  uint32_t FORCE_IN_AV;                       /* !< (@ 0x000011D0) Data control register for input data */
  __IO uint32_t CCM_ALN_WRD;                       /* !< (@ 0x000011D4) AES-CCM AAD alignment data word */
  __IO uint32_t BLK_CNT0;                          /* !< (@ 0x000011D8) Internal block counter (LSW) */
  __IO uint32_t BLK_CNT1;                          /* !< (@ 0x000011DC) Internal block counter (MSW) */
       uint32_t RESERVED8[5];
  __IO uint32_t DMA_HS;                            /* !< (@ 0x000011F4) Control register for DMA handshaking */
} AES_Regs;

/*@}*/ /* end of group AES */



/******************************************************************************
* AES Register Offsets
******************************************************************************/
#define AES_PDBGCTL                              (0x00001018U)
#define AES_EVT_MODE                             (0x000010E0U)
#define AES_GCMCCM_TAG0                          (0x00001100U)
#define AES_GCMCCM_TAG1                          (0x00001104U)
#define AES_GCMCCM_TAG2                          (0x00001108U)
#define AES_GCMCCM_TAG3                          (0x0000110CU)
#define AES_GHASH_H0                             (0x00001110U)
#define AES_GHASH_H1                             (0x00001114U)
#define AES_GHASH_H2                             (0x00001118U)
#define AES_GHASH_H3                             (0x0000111CU)
#define AES_KEY0                                 (0x00001120U)
#define AES_KEY1                                 (0x00001124U)
#define AES_KEY2                                 (0x00001128U)
#define AES_KEY3                                 (0x0000112CU)
#define AES_KEY4                                 (0x00001130U)
#define AES_KEY5                                 (0x00001134U)
#define AES_KEY6                                 (0x00001138U)
#define AES_KEY7                                 (0x0000113CU)
#define AES_IV0                                  (0x00001140U)
#define AES_IV1                                  (0x00001144U)
#define AES_IV2                                  (0x00001148U)
#define AES_IV3                                  (0x0000114CU)
#define AES_CTRL                                 (0x00001150U)
#define AES_C_LENGTH_0                           (0x00001154U)
#define AES_C_LENGTH_1                           (0x00001158U)
#define AES_AAD_LENGTH                           (0x0000115CU)
#define AES_DATA0                                (0x00001160U)
#define AES_DATA1                                (0x00001164U)
#define AES_DATA2                                (0x00001168U)
#define AES_DATA3                                (0x0000116CU)
#define AES_TAG0                                 (0x00001170U)
#define AES_TAG1                                 (0x00001174U)
#define AES_TAG2                                 (0x00001178U)
#define AES_TAG3                                 (0x0000117CU)
#define AES_STATUS                               (0x00001180U)
#define AES_DATA_IN                              (0x00001184U)
#define AES_DATA_OUT                             (0x00001188U)
#define AES_FORCE_IN_AV                          (0x000011D0U)
#define AES_CCM_ALN_WRD                          (0x000011D4U)
#define AES_BLK_CNT0                             (0x000011D8U)
#define AES_BLK_CNT1                             (0x000011DCU)
#define AES_DMA_HS                               (0x000011F4U)

#define AES_PWREN                                (0x00000800U)
#define AES_RSTCTL                               (0x00000804U)
#define AES_STAT                                 (0x00000814U)

#define AES_INT_EVENT0_IIDX                      (0x00001020U)
#define AES_INT_EVENT0_IMASK                     (0x00001028U)
#define AES_INT_EVENT0_RIS                       (0x00001030U)
#define AES_INT_EVENT0_MIS                       (0x00001038U)
#define AES_INT_EVENT0_ISET                      (0x00001040U)
#define AES_INT_EVENT0_ICLR                      (0x00001048U)

#define AES_INT_EVENT1_IIDX                      (0x00001050U)
#define AES_INT_EVENT1_IMASK                     (0x00001058U)
#define AES_INT_EVENT1_RIS                       (0x00001060U)
#define AES_INT_EVENT1_MIS                       (0x00001068U)
#define AES_INT_EVENT1_ISET                      (0x00001070U)
#define AES_INT_EVENT1_ICLR                      (0x00001078U)

#define AES_INT_EVENT2_IIDX                      (0x00001080U)
#define AES_INT_EVENT2_IMASK                     (0x00001088U)
#define AES_INT_EVENT2_RIS                       (0x00001090U)
#define AES_INT_EVENT2_MIS                       (0x00001098U)
#define AES_INT_EVENT2_ISET                      (0x000010A0U)
#define AES_INT_EVENT2_ICLR                      (0x000010A8U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* AES Register Control Bits
******************************************************************************/

/* AES_INT_EVENT2_IIDX Bits */
/* AES_INT_EVENT2_IIDX[STAT] Bits */
#define AES_INT_EVENT2_IIDX_STAT_OFS             (0)                             /* !< STAT Offset */
#define AES_INT_EVENT2_IIDX_STAT_MASK            ((uint32_t)0x000000FFU)         /* !< Interrupt index status */
#define AES_INT_EVENT2_IIDX_STAT_NO_INTR         ((uint32_t)0x00000000U)         /* !< No interrupt pending */
#define AES_INT_EVENT2_IIDX_STAT_TRIG1           ((uint32_t)0x00000001U)         /* !< AES DMA Trigger 1 (Data Output
                                                                                    trigger) */

/* AES_INT_EVENT2_IMASK Bits */
/* AES_INT_EVENT2_IMASK[TRIG1] Bits */
#define AES_INT_EVENT2_IMASK_TRIG1_OFS           (0)                             /* !< TRIG1 Offset */
#define AES_INT_EVENT2_IMASK_TRIG1_MASK          ((uint32_t)0x00000001U)         /* !< DMA1 */
#define AES_INT_EVENT2_IMASK_TRIG1_CLR           ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT2_IMASK_TRIG1_SET           ((uint32_t)0x00000001U)         /* !< Set Interrrupt Mask */

/* AES_INT_EVENT2_RIS Bits */
/* AES_INT_EVENT2_RIS[TRIG1] Bits */
#define AES_INT_EVENT2_RIS_TRIG1_OFS             (0)                             /* !< TRIG1 Offset */
#define AES_INT_EVENT2_RIS_TRIG1_MASK            ((uint32_t)0x00000001U)         /* !< TRIG1 event */
#define AES_INT_EVENT2_RIS_TRIG1_CLR             ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define AES_INT_EVENT2_RIS_TRIG1_SET             ((uint32_t)0x00000001U)         /* !< Interrupt occured */

/* AES_INT_EVENT2_MIS Bits */
/* AES_INT_EVENT2_MIS[TRIG1] Bits */
#define AES_INT_EVENT2_MIS_TRIG1_OFS             (0)                             /* !< TRIG1 Offset */
#define AES_INT_EVENT2_MIS_TRIG1_MASK            ((uint32_t)0x00000001U)         /* !< TRIG1 event */
#define AES_INT_EVENT2_MIS_TRIG1_CLR             ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define AES_INT_EVENT2_MIS_TRIG1_SET             ((uint32_t)0x00000001U)         /* !< Interrupt occured */

/* AES_INT_EVENT2_ISET Bits */
/* AES_INT_EVENT2_ISET[TRIG1] Bits */
#define AES_INT_EVENT2_ISET_TRIG1_OFS            (0)                             /* !< TRIG1 Offset */
#define AES_INT_EVENT2_ISET_TRIG1_MASK           ((uint32_t)0x00000001U)         /* !< TRIG1 event */
#define AES_INT_EVENT2_ISET_TRIG1_NO_EFFECT      ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define AES_INT_EVENT2_ISET_TRIG1_SET            ((uint32_t)0x00000001U)         /* !< Set Interrupt */

/* AES_INT_EVENT2_ICLR Bits */
/* AES_INT_EVENT2_ICLR[TRIG1] Bits */
#define AES_INT_EVENT2_ICLR_TRIG1_OFS            (0)                             /* !< TRIG1 Offset */
#define AES_INT_EVENT2_ICLR_TRIG1_MASK           ((uint32_t)0x00000001U)         /* !< TRIG1 event */
#define AES_INT_EVENT2_ICLR_TRIG1_NO_EFFECT      ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define AES_INT_EVENT2_ICLR_TRIG1_CLR            ((uint32_t)0x00000001U)         /* !< Clear Interrupt */

/* AES_INT_EVENT1_IIDX Bits */
/* AES_INT_EVENT1_IIDX[STAT] Bits */
#define AES_INT_EVENT1_IIDX_STAT_OFS             (0)                             /* !< STAT Offset */
#define AES_INT_EVENT1_IIDX_STAT_MASK            ((uint32_t)0x000000FFU)         /* !< Interrupt index status */
#define AES_INT_EVENT1_IIDX_STAT_NO_INTR         ((uint32_t)0x00000000U)         /* !< No interrupt pending */
#define AES_INT_EVENT1_IIDX_STAT_TRIG0           ((uint32_t)0x00000001U)         /* !< AES trigger 0 DMA (Data Input
                                                                                    trigger) */

/* AES_INT_EVENT1_IMASK Bits */
/* AES_INT_EVENT1_IMASK[TRIG0] Bits */
#define AES_INT_EVENT1_IMASK_TRIG0_OFS           (0)                             /* !< TRIG0 Offset */
#define AES_INT_EVENT1_IMASK_TRIG0_MASK          ((uint32_t)0x00000001U)         /* !< DMA0 */
#define AES_INT_EVENT1_IMASK_TRIG0_CLR           ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT1_IMASK_TRIG0_SET           ((uint32_t)0x00000001U)         /* !< Set Interrrupt Mask */

/* AES_INT_EVENT1_RIS Bits */
/* AES_INT_EVENT1_RIS[TRIG0] Bits */
#define AES_INT_EVENT1_RIS_TRIG0_OFS             (0)                             /* !< TRIG0 Offset */
#define AES_INT_EVENT1_RIS_TRIG0_MASK            ((uint32_t)0x00000001U)         /* !< TRIG0 event */
#define AES_INT_EVENT1_RIS_TRIG0_CLR             ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define AES_INT_EVENT1_RIS_TRIG0_SET             ((uint32_t)0x00000001U)         /* !< Interrupt occured */

/* AES_INT_EVENT1_MIS Bits */
/* AES_INT_EVENT1_MIS[TRIG0] Bits */
#define AES_INT_EVENT1_MIS_TRIG0_OFS             (0)                             /* !< TRIG0 Offset */
#define AES_INT_EVENT1_MIS_TRIG0_MASK            ((uint32_t)0x00000001U)         /* !< TRIG0 event */
#define AES_INT_EVENT1_MIS_TRIG0_CLR             ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define AES_INT_EVENT1_MIS_TRIG0_SET             ((uint32_t)0x00000001U)         /* !< Interrupt occured */

/* AES_INT_EVENT1_ISET Bits */
/* AES_INT_EVENT1_ISET[TRIG0] Bits */
#define AES_INT_EVENT1_ISET_TRIG0_OFS            (0)                             /* !< TRIG0 Offset */
#define AES_INT_EVENT1_ISET_TRIG0_MASK           ((uint32_t)0x00000001U)         /* !< TRIG0 */
#define AES_INT_EVENT1_ISET_TRIG0_NO_EFFECT      ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define AES_INT_EVENT1_ISET_TRIG0_SET            ((uint32_t)0x00000001U)         /* !< Set Interrupt */

/* AES_INT_EVENT1_ICLR Bits */
/* AES_INT_EVENT1_ICLR[TRIG0] Bits */
#define AES_INT_EVENT1_ICLR_TRIG0_OFS            (0)                             /* !< TRIG0 Offset */
#define AES_INT_EVENT1_ICLR_TRIG0_MASK           ((uint32_t)0x00000001U)         /* !< TRIG0 event */
#define AES_INT_EVENT1_ICLR_TRIG0_NO_EFFECT      ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define AES_INT_EVENT1_ICLR_TRIG0_CLR            ((uint32_t)0x00000001U)         /* !< Clear Interrupt */

/* AES_INT_EVENT0_IIDX Bits */
/* AES_INT_EVENT0_IIDX[STAT] Bits */
#define AES_INT_EVENT0_IIDX_STAT_OFS             (0)                             /* !< STAT Offset */
#define AES_INT_EVENT0_IIDX_STAT_MASK            ((uint32_t)0x000000FFU)         /* !< Interrupt index status */
#define AES_INT_EVENT0_IIDX_STAT_NO_INTR         ((uint32_t)0x00000000U)         /* !< No interrupt pending */
#define AES_INT_EVENT0_IIDX_STAT_OUTPUTRDY       ((uint32_t)0x00000001U)         /* !< This indicates that the core has an
                                                                                    output available to be read out. This
                                                                                    should not be used if DMA handshake
                                                                                    is used (AES_DMA_HS.DMA_DATA_ACK set
                                                                                    to 1) */
#define AES_INT_EVENT0_IIDX_STAT_INPUTRDY        ((uint32_t)0x00000002U)         /* !< This indicates that the engine can
                                                                                    take new input. This should not be
                                                                                    used if DMA handshake is used
                                                                                    (AES_DMA_HS.DMA_DATA_ACK set to 1) */
#define AES_INT_EVENT0_IIDX_STAT_SAVEDCNTXTRDY   ((uint32_t)0x00000003U)         /* !< This bit indicates that an AES
                                                                                    authentication TAG and/or IV block(s)
                                                                                    is/are available for the CPU to
                                                                                    retrieve. This bit is only asserted
                                                                                    if the save_context bit is set to 1b.
                                                                                    The bit is mutually exclusive with
                                                                                    the context_ready bit. */
#define AES_INT_EVENT0_IIDX_STAT_CNTXTRDY        ((uint32_t)0x00000004U)         /* !< This bit indicates that the context
                                                                                    data registers can be overwritten,
                                                                                    and the CPU is permitted to write new
                                                                                    context. */

/* AES_INT_EVENT0_IMASK Bits */
/* AES_INT_EVENT0_IMASK[OUTPUTRDY] Bits */
#define AES_INT_EVENT0_IMASK_OUTPUTRDY_OFS       (0)                             /* !< OUTPUTRDY Offset */
#define AES_INT_EVENT0_IMASK_OUTPUTRDY_MASK      ((uint32_t)0x00000001U)         /* !< AES ready */
#define AES_INT_EVENT0_IMASK_OUTPUTRDY_CLR       ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_IMASK_OUTPUTRDY_SET       ((uint32_t)0x00000001U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_IMASK[INPUTRDY] Bits */
#define AES_INT_EVENT0_IMASK_INPUTRDY_OFS        (1)                             /* !< INPUTRDY Offset */
#define AES_INT_EVENT0_IMASK_INPUTRDY_MASK       ((uint32_t)0x00000002U)         /* !< AES ready */
#define AES_INT_EVENT0_IMASK_INPUTRDY_CLR        ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_IMASK_INPUTRDY_SET        ((uint32_t)0x00000002U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_IMASK[SAVEDCNTXTRDY] Bits */
#define AES_INT_EVENT0_IMASK_SAVEDCNTXTRDY_OFS   (2)                             /* !< SAVEDCNTXTRDY Offset */
#define AES_INT_EVENT0_IMASK_SAVEDCNTXTRDY_MASK  ((uint32_t)0x00000004U)         /* !< AES ready */
#define AES_INT_EVENT0_IMASK_SAVEDCNTXTRDY_CLR   ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_IMASK_SAVEDCNTXTRDY_SET   ((uint32_t)0x00000004U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_IMASK[CNTXTRDY] Bits */
#define AES_INT_EVENT0_IMASK_CNTXTRDY_OFS        (3)                             /* !< CNTXTRDY Offset */
#define AES_INT_EVENT0_IMASK_CNTXTRDY_MASK       ((uint32_t)0x00000008U)         /* !< AES ready */
#define AES_INT_EVENT0_IMASK_CNTXTRDY_CLR        ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_IMASK_CNTXTRDY_SET        ((uint32_t)0x00000008U)         /* !< Set Interrrupt Mask */

/* AES_INT_EVENT0_RIS Bits */
/* AES_INT_EVENT0_RIS[OUTPUTRDY] Bits */
#define AES_INT_EVENT0_RIS_OUTPUTRDY_OFS         (0)                             /* !< OUTPUTRDY Offset */
#define AES_INT_EVENT0_RIS_OUTPUTRDY_MASK        ((uint32_t)0x00000001U)         /* !< This indicates that the core has an
                                                                                    output available to be read out. This
                                                                                    should not be used if DMA handshake
                                                                                    is used (AES_DMA_HS.DMA_DATA_ACK set
                                                                                    to 1) */
#define AES_INT_EVENT0_RIS_OUTPUTRDY_CLR         ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define AES_INT_EVENT0_RIS_OUTPUTRDY_SET         ((uint32_t)0x00000001U)         /* !< Interrupt occured */
/* AES_INT_EVENT0_RIS[INPUTRDY] Bits */
#define AES_INT_EVENT0_RIS_INPUTRDY_OFS          (1)                             /* !< INPUTRDY Offset */
#define AES_INT_EVENT0_RIS_INPUTRDY_MASK         ((uint32_t)0x00000002U)         /* !< AES ready */
#define AES_INT_EVENT0_RIS_INPUTRDY_CLR          ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_RIS_INPUTRDY_SET          ((uint32_t)0x00000002U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_RIS[SAVEDCNTXTRDY] Bits */
#define AES_INT_EVENT0_RIS_SAVEDCNTXTRDY_OFS     (2)                             /* !< SAVEDCNTXTRDY Offset */
#define AES_INT_EVENT0_RIS_SAVEDCNTXTRDY_MASK    ((uint32_t)0x00000004U)         /* !< AES ready */
#define AES_INT_EVENT0_RIS_SAVEDCNTXTRDY_CLR     ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_RIS_SAVEDCNTXTRDY_SET     ((uint32_t)0x00000004U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_RIS[CNTXTRDY] Bits */
#define AES_INT_EVENT0_RIS_CNTXTRDY_OFS          (3)                             /* !< CNTXTRDY Offset */
#define AES_INT_EVENT0_RIS_CNTXTRDY_MASK         ((uint32_t)0x00000008U)         /* !< AES ready */
#define AES_INT_EVENT0_RIS_CNTXTRDY_CLR          ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_RIS_CNTXTRDY_SET          ((uint32_t)0x00000008U)         /* !< Set Interrrupt Mask */

/* AES_INT_EVENT0_MIS Bits */
/* AES_INT_EVENT0_MIS[OUTPUTRDY] Bits */
#define AES_INT_EVENT0_MIS_OUTPUTRDY_OFS         (0)                             /* !< OUTPUTRDY Offset */
#define AES_INT_EVENT0_MIS_OUTPUTRDY_MASK        ((uint32_t)0x00000001U)         /* !< This indicates that the core has an
                                                                                    output available to be read out. This
                                                                                    should not be used if DMA handshake
                                                                                    is used (AES_DMA_HS.DMA_DATA_ACK set
                                                                                    to 1) */
#define AES_INT_EVENT0_MIS_OUTPUTRDY_CLR         ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define AES_INT_EVENT0_MIS_OUTPUTRDY_SET         ((uint32_t)0x00000001U)         /* !< Interrupt occured */
/* AES_INT_EVENT0_MIS[INPUTRDY] Bits */
#define AES_INT_EVENT0_MIS_INPUTRDY_OFS          (1)                             /* !< INPUTRDY Offset */
#define AES_INT_EVENT0_MIS_INPUTRDY_MASK         ((uint32_t)0x00000002U)         /* !< AES ready */
#define AES_INT_EVENT0_MIS_INPUTRDY_CLR          ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_MIS_INPUTRDY_SET          ((uint32_t)0x00000002U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_MIS[SAVEDCNTXTRDY] Bits */
#define AES_INT_EVENT0_MIS_SAVEDCNTXTRDY_OFS     (2)                             /* !< SAVEDCNTXTRDY Offset */
#define AES_INT_EVENT0_MIS_SAVEDCNTXTRDY_MASK    ((uint32_t)0x00000004U)         /* !< AES ready */
#define AES_INT_EVENT0_MIS_SAVEDCNTXTRDY_CLR     ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_MIS_SAVEDCNTXTRDY_SET     ((uint32_t)0x00000004U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_MIS[CNTXTRDY] Bits */
#define AES_INT_EVENT0_MIS_CNTXTRDY_OFS          (3)                             /* !< CNTXTRDY Offset */
#define AES_INT_EVENT0_MIS_CNTXTRDY_MASK         ((uint32_t)0x00000008U)         /* !< AES ready */
#define AES_INT_EVENT0_MIS_CNTXTRDY_CLR          ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_MIS_CNTXTRDY_SET          ((uint32_t)0x00000008U)         /* !< Set Interrrupt Mask */

/* AES_INT_EVENT0_ISET Bits */
/* AES_INT_EVENT0_ISET[OUTPUTRDY] Bits */
#define AES_INT_EVENT0_ISET_OUTPUTRDY_OFS        (0)                             /* !< OUTPUTRDY Offset */
#define AES_INT_EVENT0_ISET_OUTPUTRDY_MASK       ((uint32_t)0x00000001U)         /* !< This indicates that the core has an
                                                                                    output available to be read out. This
                                                                                    should not be used if DMA handshake
                                                                                    is used (AES_DMA_HS.DMA_DATA_ACK set
                                                                                    to 1) */
#define AES_INT_EVENT0_ISET_OUTPUTRDY_NO_EFFECT  ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define AES_INT_EVENT0_ISET_OUTPUTRDY_SET        ((uint32_t)0x00000001U)         /* !< Set Interrupt */
/* AES_INT_EVENT0_ISET[INPUTRDY] Bits */
#define AES_INT_EVENT0_ISET_INPUTRDY_OFS         (1)                             /* !< INPUTRDY Offset */
#define AES_INT_EVENT0_ISET_INPUTRDY_MASK        ((uint32_t)0x00000002U)         /* !< AES ready */
#define AES_INT_EVENT0_ISET_INPUTRDY_CLR         ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_ISET_INPUTRDY_SET         ((uint32_t)0x00000002U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_ISET[SAVEDCNTXTRDY] Bits */
#define AES_INT_EVENT0_ISET_SAVEDCNTXTRDY_OFS    (2)                             /* !< SAVEDCNTXTRDY Offset */
#define AES_INT_EVENT0_ISET_SAVEDCNTXTRDY_MASK   ((uint32_t)0x00000004U)         /* !< AES ready */
#define AES_INT_EVENT0_ISET_SAVEDCNTXTRDY_CLR    ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_ISET_SAVEDCNTXTRDY_SET    ((uint32_t)0x00000004U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_ISET[CNTXTRDY] Bits */
#define AES_INT_EVENT0_ISET_CNTXTRDY_OFS         (3)                             /* !< CNTXTRDY Offset */
#define AES_INT_EVENT0_ISET_CNTXTRDY_MASK        ((uint32_t)0x00000008U)         /* !< AES ready */
#define AES_INT_EVENT0_ISET_CNTXTRDY_CLR         ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_ISET_CNTXTRDY_SET         ((uint32_t)0x00000008U)         /* !< Set Interrrupt Mask */

/* AES_INT_EVENT0_ICLR Bits */
/* AES_INT_EVENT0_ICLR[OUTPUTRDY] Bits */
#define AES_INT_EVENT0_ICLR_OUTPUTRDY_OFS        (0)                             /* !< OUTPUTRDY Offset */
#define AES_INT_EVENT0_ICLR_OUTPUTRDY_MASK       ((uint32_t)0x00000001U)         /* !< This indicates that the core has an
                                                                                    output available to be read out. This
                                                                                    should not be used if DMA handshake
                                                                                    is used (AES_DMA_HS.DMA_DATA_ACK set
                                                                                    to 1) */
#define AES_INT_EVENT0_ICLR_OUTPUTRDY_NO_EFFECT  ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define AES_INT_EVENT0_ICLR_OUTPUTRDY_CLR        ((uint32_t)0x00000001U)         /* !< Clear Interrupt */
/* AES_INT_EVENT0_ICLR[INPUTRDY] Bits */
#define AES_INT_EVENT0_ICLR_INPUTRDY_OFS         (1)                             /* !< INPUTRDY Offset */
#define AES_INT_EVENT0_ICLR_INPUTRDY_MASK        ((uint32_t)0x00000002U)         /* !< AES ready */
#define AES_INT_EVENT0_ICLR_INPUTRDY_CLR         ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_ICLR_INPUTRDY_SET         ((uint32_t)0x00000002U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_ICLR[SAVEDCNTXTRDY] Bits */
#define AES_INT_EVENT0_ICLR_SAVEDCNTXTRDY_OFS    (2)                             /* !< SAVEDCNTXTRDY Offset */
#define AES_INT_EVENT0_ICLR_SAVEDCNTXTRDY_MASK   ((uint32_t)0x00000004U)         /* !< AES ready */
#define AES_INT_EVENT0_ICLR_SAVEDCNTXTRDY_CLR    ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_ICLR_SAVEDCNTXTRDY_SET    ((uint32_t)0x00000004U)         /* !< Set Interrrupt Mask */
/* AES_INT_EVENT0_ICLR[CNTXTRDY] Bits */
#define AES_INT_EVENT0_ICLR_CNTXTRDY_OFS         (3)                             /* !< CNTXTRDY Offset */
#define AES_INT_EVENT0_ICLR_CNTXTRDY_MASK        ((uint32_t)0x00000008U)         /* !< AES ready */
#define AES_INT_EVENT0_ICLR_CNTXTRDY_CLR         ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define AES_INT_EVENT0_ICLR_CNTXTRDY_SET         ((uint32_t)0x00000008U)         /* !< Set Interrrupt Mask */

/* AES_PWREN Bits */
/* AES_PWREN[ENABLE] Bits */
#define AES_PWREN_ENABLE_OFS                     (0)                             /* !< ENABLE Offset */
#define AES_PWREN_ENABLE_MASK                    ((uint32_t)0x00000001U)         /* !< Power Enable */
#define AES_PWREN_ENABLE_DISABLE                 ((uint32_t)0x00000000U)         /* !< Disable Power */
#define AES_PWREN_ENABLE_ENABLE                  ((uint32_t)0x00000001U)         /* !< Enable Power */
/* AES_PWREN[KEY] Bits */
#define AES_PWREN_KEY_OFS                        (24)                            /* !< KEY Offset */
#define AES_PWREN_KEY_MASK                       ((uint32_t)0xFF000000U)         /* !< KEY to allow Power State Change */
#define AES_PWREN_KEY_UNLOCK_W                   ((uint32_t)0x26000000U)         /* !< KEY to allow write access to this
                                                                                    register */

/* AES_RSTCTL Bits */
/* AES_RSTCTL[RESETSTKYCLR] Bits */
#define AES_RSTCTL_RESETSTKYCLR_OFS              (1)                             /* !< RESETSTKYCLR Offset */
#define AES_RSTCTL_RESETSTKYCLR_MASK             ((uint32_t)0x00000002U)         /* !< Reset sticky bit clear */
#define AES_RSTCTL_RESETSTKYCLR_NOP              ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define AES_RSTCTL_RESETSTKYCLR_CLR              ((uint32_t)0x00000002U)         /* !< Clear reset sticky bit */
/* AES_RSTCTL[RESETASSERT] Bits */
#define AES_RSTCTL_RESETASSERT_OFS               (0)                             /* !< RESETASSERT Offset */
#define AES_RSTCTL_RESETASSERT_MASK              ((uint32_t)0x00000001U)         /* !< Reset assertion to the peripheral */
#define AES_RSTCTL_RESETASSERT_NOP               ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define AES_RSTCTL_RESETASSERT_ASSERT            ((uint32_t)0x00000001U)         /* !< Assert reset */
/* AES_RSTCTL[KEY] Bits */
#define AES_RSTCTL_KEY_OFS                       (24)                            /* !< KEY Offset */
#define AES_RSTCTL_KEY_MASK                      ((uint32_t)0xFF000000U)         /* !< Unlock key */
#define AES_RSTCTL_KEY_UNLOCK_W                  ((uint32_t)0xB1000000U)         /* !< KEY to allow write access to this
                                                                                    register */

/* AES_STAT Bits */
/* AES_STAT[RESETSTKY] Bits */
#define AES_STAT_RESETSTKY_OFS                   (16)                            /* !< RESETSTKY Offset */
#define AES_STAT_RESETSTKY_MASK                  ((uint32_t)0x00010000U)         /* !< Reset sticky bit */
#define AES_STAT_RESETSTKY_NORES                 ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define AES_STAT_RESETSTKY_RESET                 ((uint32_t)0x00010000U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */

/* AES_PDBGCTL Bits */
/* AES_PDBGCTL[FREE] Bits */
#define AES_PDBGCTL_FREE_OFS                     (0)                             /* !< FREE Offset */
#define AES_PDBGCTL_FREE_MASK                    ((uint32_t)0x00000001U)         /* !< Free run control */
#define AES_PDBGCTL_FREE_RUN                     ((uint32_t)0x00000001U)         /* !< The peripheral ignores the state of
                                                                                    the Core Halted input */

/* AES_EVT_MODE Bits */
/* AES_EVT_MODE[INT0_CFG] Bits */
#define AES_EVT_MODE_INT0_CFG_OFS                (0)                             /* !< INT0_CFG Offset */
#define AES_EVT_MODE_INT0_CFG_MASK               ((uint32_t)0x00000003U)         /* !< Event line mode select for event
                                                                                    corresponding to
                                                                                    [IPSTANDARD.INT_EVENT0] */
#define AES_EVT_MODE_INT0_CFG_DISABLE            ((uint32_t)0x00000000U)         /* !< The interrupt or event line is
                                                                                    disabled. */
#define AES_EVT_MODE_INT0_CFG_SOFTWARE           ((uint32_t)0x00000001U)         /* !< The interrupt or event line is in
                                                                                    software mode. Software must clear
                                                                                    the RIS. */
#define AES_EVT_MODE_INT0_CFG_HARDWARE           ((uint32_t)0x00000002U)         /* !< The interrupt or event line is in
                                                                                    hardware mode. The hardware (another
                                                                                    module) clears automatically the
                                                                                    associated RIS flag. */
/* AES_EVT_MODE[EVT1_CFG] Bits */
#define AES_EVT_MODE_EVT1_CFG_OFS                (2)                             /* !< EVT1_CFG Offset */
#define AES_EVT_MODE_EVT1_CFG_MASK               ((uint32_t)0x0000000CU)         /* !< Event line mode select for event
                                                                                    corresponding to
                                                                                    [IPSTANDARD.INT_EVENT1] */
#define AES_EVT_MODE_EVT1_CFG_DISABLE            ((uint32_t)0x00000000U)         /* !< The interrupt or event line is
                                                                                    disabled. */
#define AES_EVT_MODE_EVT1_CFG_SOFTWARE           ((uint32_t)0x00000004U)         /* !< The interrupt or event line is in
                                                                                    software mode. Software must clear
                                                                                    the RIS. */
#define AES_EVT_MODE_EVT1_CFG_HARDWARE           ((uint32_t)0x00000008U)         /* !< The interrupt or event line is in
                                                                                    hardware mode. The hardware (another
                                                                                    module) clears automatically the
                                                                                    associated RIS flag. */
/* AES_EVT_MODE[EVT2_CFG] Bits */
#define AES_EVT_MODE_EVT2_CFG_OFS                (4)                             /* !< EVT2_CFG Offset */
#define AES_EVT_MODE_EVT2_CFG_MASK               ((uint32_t)0x00000030U)         /* !< Event line mode select for event
                                                                                    corresponding to
                                                                                    [IPSTANDARD.INT_EVENT2] */
#define AES_EVT_MODE_EVT2_CFG_DISABLE            ((uint32_t)0x00000000U)         /* !< The interrupt or event line is
                                                                                    disabled. */
#define AES_EVT_MODE_EVT2_CFG_SOFTWARE           ((uint32_t)0x00000010U)         /* !< The interrupt or event line is in
                                                                                    software mode. Software must clear
                                                                                    the RIS. */
#define AES_EVT_MODE_EVT2_CFG_HARDWARE           ((uint32_t)0x00000020U)         /* !< The interrupt or event line is in
                                                                                    hardware mode. The hardware (another
                                                                                    module) clears automatically the
                                                                                    associated RIS flag. */

/* AES_GCMCCM_TAG0 Bits */
/* AES_GCMCCM_TAG0[DATA] Bits */
#define AES_GCMCCM_TAG0_DATA_OFS                 (0)                             /* !< DATA Offset */
#define AES_GCMCCM_TAG0_DATA_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_GCMCCM_TAG1 Bits */
/* AES_GCMCCM_TAG1[DATA] Bits */
#define AES_GCMCCM_TAG1_DATA_OFS                 (0)                             /* !< DATA Offset */
#define AES_GCMCCM_TAG1_DATA_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_GCMCCM_TAG2 Bits */
/* AES_GCMCCM_TAG2[DATA] Bits */
#define AES_GCMCCM_TAG2_DATA_OFS                 (0)                             /* !< DATA Offset */
#define AES_GCMCCM_TAG2_DATA_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_GCMCCM_TAG3 Bits */
/* AES_GCMCCM_TAG3[DATA] Bits */
#define AES_GCMCCM_TAG3_DATA_OFS                 (0)                             /* !< DATA Offset */
#define AES_GCMCCM_TAG3_DATA_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_GHASH_H0 Bits */
/* AES_GHASH_H0[DATA] Bits */
#define AES_GHASH_H0_DATA_OFS                    (0)                             /* !< DATA Offset */
#define AES_GHASH_H0_DATA_MASK                   ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_GHASH_H1 Bits */
/* AES_GHASH_H1[DATA] Bits */
#define AES_GHASH_H1_DATA_OFS                    (0)                             /* !< DATA Offset */
#define AES_GHASH_H1_DATA_MASK                   ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_GHASH_H2 Bits */
/* AES_GHASH_H2[DATA] Bits */
#define AES_GHASH_H2_DATA_OFS                    (0)                             /* !< DATA Offset */
#define AES_GHASH_H2_DATA_MASK                   ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_GHASH_H3 Bits */
/* AES_GHASH_H3[DATA] Bits */
#define AES_GHASH_H3_DATA_OFS                    (0)                             /* !< DATA Offset */
#define AES_GHASH_H3_DATA_MASK                   ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_KEY0 Bits */
/* AES_KEY0[DATA] Bits */
#define AES_KEY0_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_KEY0_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_KEY1 Bits */
/* AES_KEY1[DATA] Bits */
#define AES_KEY1_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_KEY1_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_KEY2 Bits */
/* AES_KEY2[DATA] Bits */
#define AES_KEY2_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_KEY2_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_KEY3 Bits */
/* AES_KEY3[DATA] Bits */
#define AES_KEY3_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_KEY3_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_KEY4 Bits */
/* AES_KEY4[DATA] Bits */
#define AES_KEY4_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_KEY4_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_KEY5 Bits */
/* AES_KEY5[DATA] Bits */
#define AES_KEY5_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_KEY5_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_KEY6 Bits */
/* AES_KEY6[DATA] Bits */
#define AES_KEY6_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_KEY6_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_KEY7 Bits */
/* AES_KEY7[DATA] Bits */
#define AES_KEY7_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_KEY7_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_IV0 Bits */
/* AES_IV0[DATA] Bits */
#define AES_IV0_DATA_OFS                         (0)                             /* !< DATA Offset */
#define AES_IV0_DATA_MASK                        ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_IV1 Bits */
/* AES_IV1[DATA] Bits */
#define AES_IV1_DATA_OFS                         (0)                             /* !< DATA Offset */
#define AES_IV1_DATA_MASK                        ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_IV2 Bits */
/* AES_IV2[DATA] Bits */
#define AES_IV2_DATA_OFS                         (0)                             /* !< DATA Offset */
#define AES_IV2_DATA_MASK                        ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_IV3 Bits */
/* AES_IV3[DATA] Bits */
#define AES_IV3_DATA_OFS                         (0)                             /* !< DATA Offset */
#define AES_IV3_DATA_MASK                        ((uint32_t)0xFFFFFFFFU)         /* !< Key data */

/* AES_CTRL Bits */
/* AES_CTRL[OUTPUT_RDY] Bits */
#define AES_CTRL_OUTPUT_RDY_OFS                  (0)                             /* !< OUTPUT_RDY Offset */
#define AES_CTRL_OUTPUT_RDY_MASK                 ((uint32_t)0x00000001U)         /* !< Output Ready. If 1b, this read-only
                                                                                    status bit indicates that an AES
                                                                                    output block is available for the CPU
                                                                                    to retrieve. */
#define AES_CTRL_OUTPUT_RDY_NOTREADY             ((uint32_t)0x00000000U)         /* !< Not Ready */
#define AES_CTRL_OUTPUT_RDY_READY                ((uint32_t)0x00000001U)         /* !< Ready */
/* AES_CTRL[INPUT_RDY] Bits */
#define AES_CTRL_INPUT_RDY_OFS                   (1)                             /* !< INPUT_RDY Offset */
#define AES_CTRL_INPUT_RDY_MASK                  ((uint32_t)0x00000002U)         /* !< Ready for input. If 1b, this
                                                                                    read-only status bit indicates that
                                                                                    the 16-byte input buffer is empty,
                                                                                    and the CPU is permitted to write the
                                                                                    next block of data. After reset, this
                                                                                    bit is 0. After writing a context,
                                                                                    this bit will become 1b. */
#define AES_CTRL_INPUT_RDY_NOTEMPTY              ((uint32_t)0x00000000U)         /* !< Not Ready */
#define AES_CTRL_INPUT_RDY_EMPTY                 ((uint32_t)0x00000002U)         /* !< Ready */
/* AES_CTRL[DIR] Bits */
#define AES_CTRL_DIR_OFS                         (2)                             /* !< DIR Offset */
#define AES_CTRL_DIR_MASK                        ((uint32_t)0x00000004U)         /* !< Direction. If set to 1b an encrypt
                                                                                    operation is performed. If set to 0b
                                                                                    a decrypt operation is performed.
                                                                                    Note: This bit must be written with a
                                                                                    1b when CBC-MAC is selected. */
#define AES_CTRL_DIR_DECRYPT                     ((uint32_t)0x00000000U)         /* !< Decryption */
#define AES_CTRL_DIR_ENCRYPT                     ((uint32_t)0x00000004U)         /* !< Encryption */
/* AES_CTRL[KEYSIZE] Bits */
#define AES_CTRL_KEYSIZE_OFS                     (3)                             /* !< KEYSIZE Offset */
#define AES_CTRL_KEYSIZE_MASK                    ((uint32_t)0x00000018U)         /* !< Specifies the encryption strength /
                                                                                    key width */
#define AES_CTRL_KEYSIZE_K128                    ((uint32_t)0x00000008U)         /* !< 128-bit key */
#define AES_CTRL_KEYSIZE_K256                    ((uint32_t)0x00000018U)         /* !< 256-bit key */
/* AES_CTRL[CBC] Bits */
#define AES_CTRL_CBC_OFS                         (5)                             /* !< CBC Offset */
#define AES_CTRL_CBC_MASK                        ((uint32_t)0x00000020U)         /* !< If set to 1b, cipher-block-chaining
                                                                                    (CBC) mode is selected. */
#define AES_CTRL_CBC_DISABLE                     ((uint32_t)0x00000000U)         /* !< Disable CBC mode */
#define AES_CTRL_CBC_ENABLE                      ((uint32_t)0x00000020U)         /* !< Select CBC mode */
/* AES_CTRL[CTR] Bits */
#define AES_CTRL_CTR_OFS                         (6)                             /* !< CTR Offset */
#define AES_CTRL_CTR_MASK                        ((uint32_t)0x00000040U)         /* !< If set to 1b, AES counter mode
                                                                                    (CTR) is selected. Note: This bit
                                                                                    must also be set for GCM and CCM,
                                                                                    when encryption/decryption is
                                                                                    required. */
#define AES_CTRL_CTR_DISABLE                     ((uint32_t)0x00000000U)         /* !< Disable CBC mode */
#define AES_CTRL_CTR_ENABLE                      ((uint32_t)0x00000040U)         /* !< Select CBC mode */
/* AES_CTRL[CTR_WIDTH] Bits */
#define AES_CTRL_CTR_WIDTH_OFS                   (7)                             /* !< CTR_WIDTH Offset */
#define AES_CTRL_CTR_WIDTH_MASK                  ((uint32_t)0x00000180U)         /* !< When the CTR bit is set, specifies
                                                                                    the counter width for AES-CTR mode.
                                                                                    When the CFB bit is set, specifies
                                                                                    the CFB mode feedback width: */
#define AES_CTRL_CTR_WIDTH_CTR32                 ((uint32_t)0x00000000U)         /* !< 32-bit counter */
#define AES_CTRL_CTR_WIDTH_CFB128                ((uint32_t)0x00000000U)         /* !< CFB-128 mode */
#define AES_CTRL_CTR_WIDTH_CTR64                 ((uint32_t)0x00000080U)         /* !< 64-bit counter */
#define AES_CTRL_CTR_WIDTH_CTR96                 ((uint32_t)0x00000100U)         /* !< 96-bit counter */
#define AES_CTRL_CTR_WIDTH_CTR128                ((uint32_t)0x00000180U)         /* !< 128-bit counter */
/* AES_CTRL[ICM] Bits */
#define AES_CTRL_ICM_OFS                         (9)                             /* !< ICM Offset */
#define AES_CTRL_ICM_MASK                        ((uint32_t)0x00000200U)         /* !< When the CFB bit is set, specifies
                                                                                    the CFB mode feedback width: */
#define AES_CTRL_ICM_DISABLE                     ((uint32_t)0x00000000U)         /* !< Disable CBC mode */
#define AES_CTRL_ICM_ENABLE                      ((uint32_t)0x00000200U)         /* !< Select CBC mode */
/* AES_CTRL[CFB] Bits */
#define AES_CTRL_CFB_OFS                         (10)                            /* !< CFB Offset */
#define AES_CTRL_CFB_MASK                        ((uint32_t)0x00000400U)         /* !< If set to 1b, AES cipher feedback
                                                                                    mode CFB is selected. Use the
                                                                                    ctr_width field to specify the
                                                                                    feedback width. */
#define AES_CTRL_CFB_DISABLE                     ((uint32_t)0x00000000U)         /* !< Disable CBC mode */
#define AES_CTRL_CFB_ENABLE                      ((uint32_t)0x00000400U)         /* !< Select CBC mode */
/* AES_CTRL[CBCMAC] Bits */
#define AES_CTRL_CBCMAC_OFS                      (15)                            /* !< CBCMAC Offset */
#define AES_CTRL_CBCMAC_MASK                     ((uint32_t)0x00008000U)         /* !< If set to 1b, AES-CBC MAC is
                                                                                    selected, the Direction bit must be
                                                                                    set to 1 for this mode. */
#define AES_CTRL_CBCMAC_DISABLE                  ((uint32_t)0x00000000U)         /* !< Disable CBC mode */
#define AES_CTRL_CBCMAC_ENABLE                   ((uint32_t)0x00008000U)         /* !< Select CBC mode */
/* AES_CTRL[GCM] Bits */
#define AES_CTRL_GCM_OFS                         (16)                            /* !< GCM Offset */
#define AES_CTRL_GCM_MASK                        ((uint32_t)0x00030000U)         /* !< If not set to 00b, AES-GCM mode is
                                                                                    selected, this is a combined mode,
                                                                                    using the Galois field multiplier
                                                                                    GF(2128) for authentication and
                                                                                    AES-CTR mode for encryption, the bits
                                                                                    specify the GCM mode: 01b = GHASH
                                                                                    with H loaded and Y0-encrypted forced
                                                                                    to zero 10b = GHASH with H loaded and
                                                                                    Y0-encrypted calculated internally
                                                                                    11b = Autonomous GHASH (both H and
                                                                                    Y0-encrypted calculated internally)
                                                                                    Note: Besides GCM, the CTR mode bits
                                                                                    must also be set to 1b to enable GCM
                                                                                    with AES-CTR; if the CTR bit is not
                                                                                    set a GHASH (authentication) only
                                                                                    operation is performed. A GHASH only
                                                                                    operation is only allowed if the GCM
                                                                                    mode is set to '01b' and the
                                                                                    direction bit is set to '0b'. Other
                                                                                    modes may not be selected in
                                                                                    combination with GCM. Table 14 below
                                                                                    shows the valid combinations for the
                                                                                    GCM and CTR mode bits, all other
                                                                                    options are invalid and must not be
                                                                                    selected. */
#define AES_CTRL_GCM_FORCE_ZERO                  ((uint32_t)0x00010000U)         /* !< GHASH with H loaded and
                                                                                    Y0-encrypted forced to 0. */
#define AES_CTRL_GCM_LOAD_HASH_KEY               ((uint32_t)0x00020000U)         /* !< GHASH with H loaded and
                                                                                    Y0-encrypted calculated internally */
#define AES_CTRL_GCM_AUTONOMOUS                  ((uint32_t)0x00030000U)         /* !< Autonomous GHASH (both H and
                                                                                    Y0-encrypted calculated internally) */
/* AES_CTRL[CCM] Bits */
#define AES_CTRL_CCM_OFS                         (18)                            /* !< CCM Offset */
#define AES_CTRL_CCM_MASK                        ((uint32_t)0x00040000U)         /* !< If set to 1b, AES-CCM is selected,
                                                                                    this is a combined mode, using AES
                                                                                    for both authentication and
                                                                                    encryption. In addition to the CCM
                                                                                    bit, the CTR mode bit must be set
                                                                                    such that AES-CTR is enabled. Other
                                                                                    combinations with CCM are invalid. */
#define AES_CTRL_CCM_DISABLE                     ((uint32_t)0x00000000U)         /* !< Disable CBC mode */
#define AES_CTRL_CCM_ENABLE                      ((uint32_t)0x00040000U)         /* !< Select CBC mode */
/* AES_CTRL[CCML] Bits */
#define AES_CTRL_CCML_OFS                        (19)                            /* !< CCML Offset */
#define AES_CTRL_CCML_MASK                       ((uint32_t)0x00380000U)         /* !< Defines L that indicates the width
                                                                                    of the length field for CCM
                                                                                    operations; the length field in bytes
                                                                                    equals the value of CMM-L plus one.
                                                                                    All values are supported. */
#define AES_CTRL_CCML_MINIMUM                    ((uint32_t)0x00000000U)         /* !< Length is 1 */
#define AES_CTRL_CCML_MAXIMUM                    ((uint32_t)0x00380000U)         /* !< Length is 8 */
/* AES_CTRL[CCMM] Bits */
#define AES_CTRL_CCMM_OFS                        (22)                            /* !< CCMM Offset */
#define AES_CTRL_CCMM_MASK                       ((uint32_t)0x01C00000U)         /* !< Defines M that indicates the length
                                                                                    of the authentication field for CCM
                                                                                    operations; the authentication field
                                                                                    length equals two times (the value of
                                                                                    CCM-M plus one). Note: The EIP-39
                                                                                    always returns a 128-bit
                                                                                    authentication field, of which the M
                                                                                    least significant bytes are valid.
                                                                                    All values are supported. */
#define AES_CTRL_CCMM_MINIMUM                    ((uint32_t)0x00000000U)         /* !< Length is 1 */
#define AES_CTRL_CCMM_MAXIMUM                    ((uint32_t)0x01C00000U)         /* !< Length is 8 */
/* AES_CTRL[OFB_GCM_CCM_CONT] Bits */
#define AES_CTRL_OFB_GCM_CCM_CONT_OFS            (26)                            /* !< OFB_GCM_CCM_CONT Offset */
#define AES_CTRL_OFB_GCM_CCM_CONT_MASK           ((uint32_t)0x04000000U)         /* !< This bit has a dual use, depending
                                                                                    on the selection of CCM/GCM, see bits
                                                                                    [18:16]. If CCM/GCM is not selected:
                                                                                    If this bit is set to 1b, full block
                                                                                    AES output feedback mode (OFB-128) is
                                                                                    selected. If CCM/GCM is selected:
                                                                                    Continue processing of an interrupted
                                                                                    AES-GCM or AES-CCM operation in the
                                                                                    AAD phase. Set this write-only signal
                                                                                    to 1b together with the regular mode
                                                                                    bit settings for a GCM or CCM
                                                                                    operation, to continue processing
                                                                                    from the next full AAD block (128
                                                                                    bits) boundary. Before setting this
                                                                                    bit all applicable context to resume
                                                                                    processing must have been loaded into
                                                                                    the engine: Keys, IV, intermediate
                                                                                    digest/TAG, block counter and the CCM
                                                                                    align data word (the latter is for
                                                                                    CCM mode only). The mode can be
                                                                                    written together with this bit, as it
                                                                                    is part of the same register. */
#define AES_CTRL_OFB_GCM_CCM_CONT_OFB            ((uint32_t)0x04000000U)         /* !< Enable OFB */
#define AES_CTRL_OFB_GCM_CCM_CONT_GCM_CCM_CONTINUE ((uint32_t)0x04000000U)         /* !< Continue GCM/CCM processing in AAD
                                                                                    phase */
/* AES_CTRL[GET_DIGEST] Bits */
#define AES_CTRL_GET_DIGEST_OFS                  (27)                            /* !< GET_DIGEST Offset */
#define AES_CTRL_GET_DIGEST_MASK                 ((uint32_t)0x08000000U)         /* !< Interrupt processing and generate
                                                                                    an intermediate digest during an
                                                                                    AES-GCM or AES-CCM operation. Set
                                                                                    this write-only signal to 1b to
                                                                                    interrupt GCM or CCM processing at
                                                                                    the next full block (128 bits)
                                                                                    boundary. An intermediate digest may
                                                                                    be requested during the
                                                                                    encryption/decryption data phase or
                                                                                    in the AAD phase. Note: Interruption
                                                                                    can only be done on full block (128
                                                                                    bits) boundaries. The minimum number
                                                                                    of remaining bytes to resume and
                                                                                    finalize the operation, must be
                                                                                    greater than or equal to 1. */
#define AES_CTRL_GET_DIGEST_NO_EFFECT            ((uint32_t)0x00000000U)         /* !< No effect */
#define AES_CTRL_GET_DIGEST_ENABLE               ((uint32_t)0x08000000U)         /* !< Enable */
/* AES_CTRL[GCM_CONT] Bits */
#define AES_CTRL_GCM_CONT_OFS                    (28)                            /* !< GCM_CONT Offset */
#define AES_CTRL_GCM_CONT_MASK                   ((uint32_t)0x10000000U)         /* !< Continue processing of an
                                                                                    interrupted AES-GCM or AES-CCM
                                                                                    operation in the crypto/payload
                                                                                    phase. Set this write-only signal to
                                                                                    1b together with the regular mode bit
                                                                                    settings for a GCM or CCM operation,
                                                                                    to continue processing from the next
                                                                                    full block (128 bits) boundary.
                                                                                    Before setting this bit all
                                                                                    applicable context to resume
                                                                                    processing must have been loaded into
                                                                                    the engine: Keys, IV, intermediate
                                                                                    digest/TAG and block counter. The
                                                                                    mode can be written together with
                                                                                    this bit, as it is part of the same
                                                                                    register. */
#define AES_CTRL_GCM_CONT_NO_EFFECT              ((uint32_t)0x00000000U)         /* !< No effect */
#define AES_CTRL_GCM_CONT_ENABLE                 ((uint32_t)0x10000000U)         /* !< Enable */
/* AES_CTRL[SAVE_CNTXT] Bits */
#define AES_CTRL_SAVE_CNTXT_OFS                  (29)                            /* !< SAVE_CNTXT Offset */
#define AES_CTRL_SAVE_CNTXT_MASK                 ((uint32_t)0x20000000U)         /* !< This bit is used to indicate that
                                                                                    an authentication TAG or result IV
                                                                                    needs to be stored as a result
                                                                                    context. If this bit is set, context
                                                                                    output DMA and/or interrupt will be
                                                                                    asserted if the operation is
                                                                                    finished, and related signals are
                                                                                    enabled. Typically, this value must
                                                                                    be set for authentication modes
                                                                                    returning a TAG (CBC-MAC, GCM and
                                                                                    CCM), or for basic encryption modes
                                                                                    that require future continuation with
                                                                                    the current result IV. If this bit is
                                                                                    set, the engine will hold its full
                                                                                    context until the TAG and/or IV
                                                                                    registers are read. Only after
                                                                                    reading the TAG or IV, a new DMA
                                                                                    request for a new (input) context
                                                                                    will be asserted. If this bit is not
                                                                                    set, the engine will assert the
                                                                                    context input DMA request signal
                                                                                    directly after starting to process
                                                                                    the last block with the current
                                                                                    context. */
#define AES_CTRL_SAVE_CNTXT_NO_EFFECT            ((uint32_t)0x00000000U)         /* !< No effect */
#define AES_CTRL_SAVE_CNTXT_ENABLE               ((uint32_t)0x20000000U)         /* !< Enable */
/* AES_CTRL[SAVED_CNTXT_RDY] Bits */
#define AES_CTRL_SAVED_CNTXT_RDY_OFS             (30)                            /* !< SAVED_CNTXT_RDY Offset */
#define AES_CTRL_SAVED_CNTXT_RDY_MASK            ((uint32_t)0x40000000U)         /* !< If 1b, this read-only status bit
                                                                                    indicates that an AES authentication
                                                                                    TAG and/or IV block(s) is/are
                                                                                    available for the Host to retrieve.
                                                                                    This bit is only asserted if the
                                                                                    save_context bit is set to 1b. The
                                                                                    bit is mutually exclusive with the
                                                                                    context_ready bit. */
#define AES_CTRL_SAVED_CNTXT_RDY_NOTREADY        ((uint32_t)0x00000000U)         /* !< Not ready */
#define AES_CTRL_SAVED_CNTXT_RDY_READY           ((uint32_t)0x40000000U)         /* !< Ready */
/* AES_CTRL[CNTXT_RDY] Bits */
#define AES_CTRL_CNTXT_RDY_OFS                   (31)                            /* !< CNTXT_RDY Offset */
#define AES_CTRL_CNTXT_RDY_MASK                  ((uint32_t)0x80000000U)         /* !< If 1b, this read-only status bit
                                                                                    indicates that the context data
                                                                                    registers can be overwritten, and the
                                                                                    CPU is permitted to write the next
                                                                                    context. */
#define AES_CTRL_CNTXT_RDY_NOTREADY              ((uint32_t)0x00000000U)         /* !< Not ready */
#define AES_CTRL_CNTXT_RDY_READY                 ((uint32_t)0x80000000U)         /* !< Ready */

/* AES_C_LENGTH_0 Bits */
/* AES_C_LENGTH_0[DATA] Bits */
#define AES_C_LENGTH_0_DATA_OFS                  (0)                             /* !< DATA Offset */
#define AES_C_LENGTH_0_DATA_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< Bits [60:0] of the crypto length
                                                                                    registers (LSW and MSW) store the
                                                                                    cryptographic data length in bytes
                                                                                    for all modes. Once processing with
                                                                                    this context is started, this length
                                                                                    decrements to zero. Data lengths up
                                                                                    to (261-1) bytes are allowed. For
                                                                                    GCM, any value up to 236-32 bytes can
                                                                                    be used. This is because a 32-bit
                                                                                    counter mode is used; the maximum
                                                                                    number of 128-bit blocks is 232-2,
                                                                                    resulting in a maximum number of
                                                                                    bytes of 236-32. A write to this
                                                                                    register triggers the engine to start
                                                                                    using this context. This is valid for
                                                                                    all modes except GCM and CCM. Note
                                                                                    that for the combined modes, this
                                                                                    length does not include the
                                                                                    authentication only data; the
                                                                                    authentication length is specified in
                                                                                    the AES_AAD_LENGTH register below.
                                                                                    All modes must have a length > 0. For
                                                                                    the combined modes, it is allowed to
                                                                                    have one of the lengths equal to
                                                                                    zero. For the basic encryption modes
                                                                                    (ECB/CBC/CTR/ICM/CFB/OFB) it is
                                                                                    allowed to program zero to the length
                                                                                    field; in that case the length is
                                                                                    assumed infinite. All data must be
                                                                                    byte (8-bit) aligned for stream
                                                                                    cipher modes; bit aligned data
                                                                                    streams are not supported. For block
                                                                                    cipher modes, the data length must be
                                                                                    programmed in multiples of the block
                                                                                    cipher size, 16 bytes. */

/* AES_C_LENGTH_1 Bits */
/* AES_C_LENGTH_1[DATA] Bits */
#define AES_C_LENGTH_1_DATA_OFS                  (0)                             /* !< DATA Offset */
#define AES_C_LENGTH_1_DATA_MASK                 ((uint32_t)0x1FFFFFFFU)         /* !< Bits [60:0] of the crypto length
                                                                                    registers (LSW and MSW) store the
                                                                                    cryptographic data length in bytes
                                                                                    for all modes. Once processing with
                                                                                    this context is started, this length
                                                                                    decrements to zero. Data lengths up
                                                                                    to (261-1) bytes are allowed. For
                                                                                    GCM, any value up to 236-32 bytes can
                                                                                    be used. This is because a 32-bit
                                                                                    counter mode is used; the maximum
                                                                                    number of 128-bit blocks is 232-2,
                                                                                    resulting in a maximum number of
                                                                                    bytes of 236-32. A write to this
                                                                                    register triggers the engine to start
                                                                                    using this context. This is valid for
                                                                                    all modes except GCM and CCM. Note
                                                                                    that for the combined modes, this
                                                                                    length does not include the
                                                                                    authentication only data; the
                                                                                    authentication length is specified in
                                                                                    the AES_AAD_LENGTH register below.
                                                                                    All modes must have a length > 0. For
                                                                                    the combined modes, it is allowed to
                                                                                    have one of the lengths equal to
                                                                                    zero. For the basic encryption modes
                                                                                    (ECB/CBC/CTR/ICM/CFB/OFB) it is
                                                                                    allowed to program zero to the length
                                                                                    field; in that case the length is
                                                                                    assumed infinite. All data must be
                                                                                    byte (8-bit) aligned for stream
                                                                                    cipher modes; bit aligned data
                                                                                    streams are not supported. For block
                                                                                    cipher modes, the data length must be
                                                                                    programmed in multiples of the block
                                                                                    cipher size, 16 bytes. */

/* AES_AAD_LENGTH Bits */
/* AES_AAD_LENGTH[DATA] Bits */
#define AES_AAD_LENGTH_DATA_OFS                  (0)                             /* !< DATA Offset */
#define AES_AAD_LENGTH_DATA_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< Bits [31:0] of the authentication
                                                                                    length register store the
                                                                                    authentication data length in bytes
                                                                                    for combined modes only (GCM or CCM)
                                                                                    Supported AAD-lengths for CCM are
                                                                                    from 0 to (216-28) bytes. For GCM any
                                                                                    value up to (232-1) bytes can be
                                                                                    used. Once processing with this
                                                                                    context is started, this length
                                                                                    decrements to zero. A write to this
                                                                                    register triggers the engine to start
                                                                                    using this context for GCM and CCM. */

/* AES_DATA0 Bits */
/* AES_DATA0[DATA] Bits */
#define AES_DATA0_DATA_OFS                       (0)                             /* !< DATA Offset */
#define AES_DATA0_DATA_MASK                      ((uint32_t)0xFFFFFFFFU)         /* !< Data */

/* AES_DATA1 Bits */
/* AES_DATA1[DATA] Bits */
#define AES_DATA1_DATA_OFS                       (0)                             /* !< DATA Offset */
#define AES_DATA1_DATA_MASK                      ((uint32_t)0xFFFFFFFFU)         /* !< Data */

/* AES_DATA2 Bits */
/* AES_DATA2[DATA] Bits */
#define AES_DATA2_DATA_OFS                       (0)                             /* !< DATA Offset */
#define AES_DATA2_DATA_MASK                      ((uint32_t)0xFFFFFFFFU)         /* !< Data */

/* AES_DATA3 Bits */
/* AES_DATA3[DATA] Bits */
#define AES_DATA3_DATA_OFS                       (0)                             /* !< DATA Offset */
#define AES_DATA3_DATA_MASK                      ((uint32_t)0xFFFFFFFFU)         /* !< Data */

/* AES_TAG0 Bits */
/* AES_TAG0[DATA] Bits */
#define AES_TAG0_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_TAG0_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< For a CPU read operation, these
                                                                                    registers contain the last 128-bit
                                                                                    TAG output of the EIP-39; the TAG is
                                                                                    available until the next context is
                                                                                    written. This register will only
                                                                                    contain valid data if the TAG is
                                                                                    available, when the
                                                                                    saved_context_ready or get_digest bit
                                                                                    from AES_CTRL register is set. In
                                                                                    case of get_digest, the output will
                                                                                    be an intermediate TAG for CCM or GCM
                                                                                    operation continuation. During
                                                                                    processing or for operations/modes
                                                                                    that do not return a TAG, reads from
                                                                                    this register returns data from the
                                                                                    IV register. For operations that do
                                                                                    return a TAG in the IV register, the
                                                                                    IV register must be accessed
                                                                                    directly. */

/* AES_TAG1 Bits */
/* AES_TAG1[DATA] Bits */
#define AES_TAG1_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_TAG1_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< For a CPU read operation, these
                                                                                    registers contain the last 128-bit
                                                                                    TAG output of the EIP-39; the TAG is
                                                                                    available until the next context is
                                                                                    written. This register will only
                                                                                    contain valid data if the TAG is
                                                                                    available, when the
                                                                                    saved_context_ready or get_digest bit
                                                                                    from AES_CTRL register is set. In
                                                                                    case of get_digest, the output will
                                                                                    be an intermediate TAG for CCM or GCM
                                                                                    operation continuation. During
                                                                                    processing or for operations/modes
                                                                                    that do not return a TAG, reads from
                                                                                    this register returns data from the
                                                                                    IV register. For operations that do
                                                                                    return a TAG in the IV register, the
                                                                                    IV register must be accessed
                                                                                    directly. */

/* AES_TAG2 Bits */
/* AES_TAG2[DATA] Bits */
#define AES_TAG2_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_TAG2_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< For a CPU read operation, these
                                                                                    registers contain the last 128-bit
                                                                                    TAG output of the EIP-39; the TAG is
                                                                                    available until the next context is
                                                                                    written. This register will only
                                                                                    contain valid data if the TAG is
                                                                                    available, when the
                                                                                    saved_context_ready or get_digest bit
                                                                                    from AES_CTRL register is set. In
                                                                                    case of get_digest, the output will
                                                                                    be an intermediate TAG for CCM or GCM
                                                                                    operation continuation. During
                                                                                    processing or for operations/modes
                                                                                    that do not return a TAG, reads from
                                                                                    this register returns data from the
                                                                                    IV register. For operations that do
                                                                                    return a TAG in the IV register, the
                                                                                    IV register must be accessed
                                                                                    directly. */

/* AES_TAG3 Bits */
/* AES_TAG3[DATA] Bits */
#define AES_TAG3_DATA_OFS                        (0)                             /* !< DATA Offset */
#define AES_TAG3_DATA_MASK                       ((uint32_t)0xFFFFFFFFU)         /* !< For a CPU read operation, these
                                                                                    registers contain the last 128-bit
                                                                                    TAG output of the EIP-39; the TAG is
                                                                                    available until the next context is
                                                                                    written. This register will only
                                                                                    contain valid data if the TAG is
                                                                                    available, when the
                                                                                    saved_context_ready or get_digest bit
                                                                                    from AES_CTRL register is set. In
                                                                                    case of get_digest, the output will
                                                                                    be an intermediate TAG for CCM or GCM
                                                                                    operation continuation. During
                                                                                    processing or for operations/modes
                                                                                    that do not return a TAG, reads from
                                                                                    this register returns data from the
                                                                                    IV register. For operations that do
                                                                                    return a TAG in the IV register, the
                                                                                    IV register must be accessed
                                                                                    directly. */

/* AES_STATUS Bits */
/* AES_STATUS[KEYWR] Bits */
#define AES_STATUS_KEYWR_OFS                     (0)                             /* !< KEYWR Offset */
#define AES_STATUS_KEYWR_MASK                    ((uint32_t)0x00000001U)         /* !< Key write status. 0 - user write to
                                                                                    KEY register is allowed. 1 - user
                                                                                    write to KEY register is ignored. In
                                                                                    order to allow user write, perform a
                                                                                    module reset. */
#define AES_STATUS_KEYWR_ENABLED                 ((uint32_t)0x00000000U)         /* !< User write to KEY MMR is allowed */
#define AES_STATUS_KEYWR_DISABLED                ((uint32_t)0x00000001U)         /* !< User write to KEY MMR is disabled.
                                                                                    Writing has no effect. */

/* AES_DATA_IN Bits */
/* AES_DATA_IN[DATA] Bits */
#define AES_DATA_IN_DATA_OFS                     (0)                             /* !< DATA Offset */
#define AES_DATA_IN_DATA_MASK                    ((uint32_t)0xFFFFFFFFU)         /* !< Data input word */

/* AES_DATA_OUT Bits */
/* AES_DATA_OUT[DATA] Bits */
#define AES_DATA_OUT_DATA_OFS                    (0)                             /* !< DATA Offset */
#define AES_DATA_OUT_DATA_MASK                   ((uint32_t)0xFFFFFFFFU)         /* !< Data output word */

/* AES_FORCE_IN_AV Bits */
/* AES_FORCE_IN_AV[DATA] Bits */
#define AES_FORCE_IN_AV_DATA_OFS                 (0)                             /* !< DATA Offset */
#define AES_FORCE_IN_AV_DATA_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Any write to this register forces
                                                                                    the input data buffer to valid and
                                                                                    will force the engine to start
                                                                                    processing this data. The data
                                                                                    written here is not used. The core
                                                                                    must be configured to have input and
                                                                                    output data acknowledge be I/O
                                                                                    register based */

/* AES_CCM_ALN_WRD Bits */
/* AES_CCM_ALN_WRD[DATA] Bits */
#define AES_CCM_ALN_WRD_DATA_OFS                 (0)                             /* !< DATA Offset */
#define AES_CCM_ALN_WRD_DATA_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< This register provides a means to
                                                                                    access an internal EIP-39 register
                                                                                    that stores alignment data bytes
                                                                                    during the AAD phase of AES-CCM
                                                                                    processing. This register needs to be
                                                                                    read and stored when an AES-CCM
                                                                                    operation is interrupted during the
                                                                                    AAD phase. This value needs to be
                                                                                    restored by writing this register,
                                                                                    when resuming that AES-CCM operation
                                                                                    in a later session. */

/* AES_BLK_CNT0 Bits */
/* AES_BLK_CNT0[DATA] Bits */
#define AES_BLK_CNT0_DATA_OFS                    (0)                             /* !< DATA Offset */
#define AES_BLK_CNT0_DATA_MASK                   ((uint32_t)0xFFFFFFFFU)         /* !< Internal block counter for AES GCM
                                                                                    and CCM operations. These bits read
                                                                                    the block count value that represents
                                                                                    the number of blocks to go. This
                                                                                    value is valid with
                                                                                    saved_context_ready after a request
                                                                                    for an intermediate GCM/CCM digest.
                                                                                    Writing these registers will restore
                                                                                    the internal block counter to the
                                                                                    programmed value. This only needs to
                                                                                    be done to prepare the engine to
                                                                                    continue processing of an interrupted
                                                                                    GCM or CCM operation. Also refer to
                                                                                    the get_digest and gcm_ccm_continue
                                                                                    bits in AES_CTRL register. */

/* AES_BLK_CNT1 Bits */
/* AES_BLK_CNT1[DATA] Bits */
#define AES_BLK_CNT1_DATA_OFS                    (0)                             /* !< DATA Offset */
#define AES_BLK_CNT1_DATA_MASK                   ((uint32_t)0x00FFFFFFU)         /* !< Internal block counter for AES GCM
                                                                                    and CCM operations. These bits read
                                                                                    the block count value that represents
                                                                                    the number of blocks to go. This
                                                                                    value is valid with
                                                                                    saved_context_ready after a request
                                                                                    for an intermediate GCM/CCM digest.
                                                                                    Writing these registers will restore
                                                                                    the internal block counter to the
                                                                                    programmed value. This only needs to
                                                                                    be done to prepare the engine to
                                                                                    continue processing of an interrupted
                                                                                    GCM or CCM operation. Also refer to
                                                                                    the get_digest and gcm_ccm_continue
                                                                                    bits in AES_CTRL register. */

/* AES_DMA_HS Bits */
/* AES_DMA_HS[DMA_DATA_ACK] Bits */
#define AES_DMA_HS_DMA_DATA_ACK_OFS              (0)                             /* !< DMA_DATA_ACK Offset */
#define AES_DMA_HS_DMA_DATA_ACK_MASK             ((uint32_t)0x00000001U)         /* !< When this bit is 0b, input and
                                                                                    output data acknowledge is I/O
                                                                                    register based, as specified in the
                                                                                    description of the AES_DATA_IN_n /
                                                                                    AES_DATA_OUT_n registers. When this
                                                                                    bit is 1b, input and ouput data
                                                                                    acknowledge is based on DMA handshake
                                                                                    signals. */
#define AES_DMA_HS_DMA_DATA_ACK_DMA_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable DMA based data handshake */
#define AES_DMA_HS_DMA_DATA_ACK_DMA_ENABLE       ((uint32_t)0x00000001U)         /* !< Enables DMA based handshake */


#ifdef __cplusplus
}
#endif

#endif /* hw_aes__include */

