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

#ifndef hw_unicommi2cc__include
#define hw_unicommi2cc__include


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
* UNICOMMI2CC Registers
******************************************************************************/
#define UNICOMMI2CC_DMA_TRIG0_OFS                ((uint32_t)0x00000080U)
#define UNICOMMI2CC_DMA_TRIG1_OFS                ((uint32_t)0x00000050U)
#define UNICOMMI2CC_CPU_INT_OFS                  ((uint32_t)0x00000020U)


/** @addtogroup UNICOMMI2CC_DMA_TRIG0
  @{
*/

typedef struct {
       uint32_t RESERVED0[2];
  __IO uint32_t IMASK;                             /* !< (@ 0x00000088) Interrupt mask */
       uint32_t RESERVED1;
  __I  uint32_t RIS;                               /* !< (@ 0x00000090) Raw interrupt status */
       uint32_t RESERVED2;
  __I  uint32_t MIS;                               /* !< (@ 0x00000098) Masked interrupt status */
       uint32_t RESERVED3;
  __O  uint32_t ISET;                              /* !< (@ 0x000000A0) Interrupt set */
} UNICOMMI2CC_DMA_TRIG0_Regs;

/*@}*/ /* end of group UNICOMMI2CC_DMA_TRIG0 */

/** @addtogroup UNICOMMI2CC_DMA_TRIG1
  @{
*/

typedef struct {
       uint32_t RESERVED0[2];
  __IO uint32_t IMASK;                             /* !< (@ 0x00000058) Interrupt mask */
       uint32_t RESERVED1;
  __I  uint32_t RIS;                               /* !< (@ 0x00000060) Raw interrupt status */
       uint32_t RESERVED2;
  __I  uint32_t MIS;                               /* !< (@ 0x00000068) Masked interrupt status */
       uint32_t RESERVED3;
  __O  uint32_t ISET;                              /* !< (@ 0x00000070) Interrupt set */
} UNICOMMI2CC_DMA_TRIG1_Regs;

/*@}*/ /* end of group UNICOMMI2CC_DMA_TRIG1 */

/** @addtogroup UNICOMMI2CC_CPU_INT
  @{
*/

typedef struct {
  __I  uint32_t IIDX;                              /* !< (@ 0x00000020) Interrupt index */
       uint32_t RESERVED0;
  __IO uint32_t IMASK;                             /* !< (@ 0x00000028) Interrupt mask */
       uint32_t RESERVED1;
  __I  uint32_t RIS;                               /* !< (@ 0x00000030) Raw interrupt status */
       uint32_t RESERVED2;
  __I  uint32_t MIS;                               /* !< (@ 0x00000038) Masked interrupt status */
       uint32_t RESERVED3;
  __O  uint32_t ISET;                              /* !< (@ 0x00000040) Interrupt set */
       uint32_t RESERVED4;
  __O  uint32_t ICLR;                              /* !< (@ 0x00000048) Interrupt clear */
} UNICOMMI2CC_CPU_INT_Regs;

/*@}*/ /* end of group UNICOMMI2CC_CPU_INT */

/** @addtogroup UNICOMMI2CC
  @{
*/

typedef struct {
  __IO uint32_t CLKDIV;                            /* !< (@ 0x00000000) Clock Divider */
       uint32_t RESERVED0;
  __IO uint32_t CLKSEL;                            /* !< (@ 0x00000008) Clock Select for Ultra Low Power peripherals */
       uint32_t RESERVED1[3];
  __IO uint32_t PDBGCTL;                           /* !< (@ 0x00000018) Peripheral Debug Control */
       uint32_t RESERVED2;
  UNICOMMI2CC_CPU_INT_Regs  CPU_INT;                           /* !< (@ 0x00000020) */
       uint32_t RESERVED3;
  UNICOMMI2CC_DMA_TRIG1_Regs  DMA_TRIG1;                         /* !< (@ 0x00000050) */
       uint32_t RESERVED4[3];
  UNICOMMI2CC_DMA_TRIG0_Regs  DMA_TRIG0;                         /* !< (@ 0x00000080) */
       uint32_t RESERVED5[16];
  __O  uint32_t INTCTL;                            /* !< (@ 0x000000E4) Interrupt control register */
       uint32_t RESERVED6[6];
  __IO uint32_t CTR;                               /* !< (@ 0x00000100) Control Register */
  __IO uint32_t CR;                                /* !< (@ 0x00000104) Configuration */
  __I  uint32_t SR;                                /* !< (@ 0x00000108) Status Register */
  __IO uint32_t IFLS;                              /* !< (@ 0x0000010C) Interrupt FIFO Level Select Register */
  __IO uint32_t TPR;                               /* !< (@ 0x00000110) Timer Period */
       uint32_t RESERVED7;
  __IO uint32_t GFCTL;                             /* !< (@ 0x00000118) I2C Glitch Filter Control */
  __I  uint32_t BMON;                              /* !< (@ 0x0000011C) Bus Monitor */
  __O  uint32_t TXDATA;                            /* !< (@ 0x00000120) TXData */
  __I  uint32_t RXDATA;                            /* !< (@ 0x00000124) RXData */
  __I  uint32_t PECSR;                             /* !< (@ 0x00000128) PEC status register */
       uint32_t RESERVED8[8];
  __IO uint32_t TA;                                /* !< (@ 0x0000014C) Target Address Register */
  __I  uint32_t TIMEOUT_CNT;                       /* !< (@ 0x00000150) I2C Timeout Count Register */
  __IO uint32_t TIMEOUT_CTL;                       /* !< (@ 0x00000154) I2C Timeout Count Control Register */
  __IO uint32_t PECCTL;                            /* !< (@ 0x00000158) I2C PEC control register */
} UNICOMMI2CC_Regs;

/*@}*/ /* end of group UNICOMMI2CC */



/******************************************************************************
* UNICOMMI2CC Register Offsets
******************************************************************************/
#define UNICOMMI2CC_CLKDIV                       (0x00000000U)
#define UNICOMMI2CC_CLKSEL                       (0x00000008U)
#define UNICOMMI2CC_PDBGCTL                      (0x00000018U)
#define UNICOMMI2CC_INTCTL                       (0x000000E4U)
#define UNICOMMI2CC_CTR                          (0x00000100U)
#define UNICOMMI2CC_CR                           (0x00000104U)
#define UNICOMMI2CC_SR                           (0x00000108U)
#define UNICOMMI2CC_IFLS                         (0x0000010CU)
#define UNICOMMI2CC_TPR                          (0x00000110U)
#define UNICOMMI2CC_GFCTL                        (0x00000118U)
#define UNICOMMI2CC_BMON                         (0x0000011CU)
#define UNICOMMI2CC_TXDATA                       (0x00000120U)
#define UNICOMMI2CC_RXDATA                       (0x00000124U)
#define UNICOMMI2CC_PECSR                        (0x00000128U)
#define UNICOMMI2CC_TA                           (0x0000014CU)
#define UNICOMMI2CC_TIMEOUT_CNT                  (0x00000150U)
#define UNICOMMI2CC_TIMEOUT_CTL                  (0x00000154U)
#define UNICOMMI2CC_PECCTL                       (0x00000158U)

#define UNICOMMI2CC_IIDX                         (0x00000020U)
#define UNICOMMI2CC_CPU_INT_IMASK                (0x00000028U)
#define UNICOMMI2CC_CPU_INT_RIS                  (0x00000030U)
#define UNICOMMI2CC_CPU_INT_MIS                  (0x00000038U)
#define UNICOMMI2CC_CPU_INT_ISET                 (0x00000040U)
#define UNICOMMI2CC_ICLR                         (0x00000048U)

#define UNICOMMI2CC_DMA_TRIG1_IMASK              (0x00000058U)
#define UNICOMMI2CC_DMA_TRIG1_RIS                (0x00000060U)
#define UNICOMMI2CC_DMA_TRIG1_MIS                (0x00000068U)
#define UNICOMMI2CC_DMA_TRIG1_ISET               (0x00000070U)

#define UNICOMMI2CC_DMA_TRIG0_IMASK              (0x00000088U)
#define UNICOMMI2CC_DMA_TRIG0_RIS                (0x00000090U)
#define UNICOMMI2CC_DMA_TRIG0_MIS                (0x00000098U)
#define UNICOMMI2CC_DMA_TRIG0_ISET               (0x000000A0U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* UNICOMMI2CC Register Control Bits
******************************************************************************/

/* UNICOMMI2CC_DMA_TRIG0_IMASK Bits */
/* UNICOMMI2CC_DMA_TRIG0_IMASK[TXTRG] Bits */
#define UNICOMMI2CC_DMA_TRIG0_IMASK_TXTRG_OFS    (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_DMA_TRIG0_IMASK_TXTRG_MASK   ((uint32_t)0x00000008U)         /* !< Transmit FIFO Trigger */
#define UNICOMMI2CC_DMA_TRIG0_IMASK_TXTRG_CLR    ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_DMA_TRIG0_IMASK_TXTRG_SET    ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_DMA_TRIG0_RIS Bits */
/* UNICOMMI2CC_DMA_TRIG0_RIS[TXTRG] Bits */
#define UNICOMMI2CC_DMA_TRIG0_RIS_TXTRG_OFS      (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_DMA_TRIG0_RIS_TXTRG_MASK     ((uint32_t)0x00000008U)         /* !< Transmit FIFO Trigger */
#define UNICOMMI2CC_DMA_TRIG0_RIS_TXTRG_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_DMA_TRIG0_RIS_TXTRG_SET      ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_DMA_TRIG0_MIS Bits */
/* UNICOMMI2CC_DMA_TRIG0_MIS[TXTRG] Bits */
#define UNICOMMI2CC_DMA_TRIG0_MIS_TXTRG_OFS      (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_DMA_TRIG0_MIS_TXTRG_MASK     ((uint32_t)0x00000008U)         /* !< Transmit FIFO Trigger */
#define UNICOMMI2CC_DMA_TRIG0_MIS_TXTRG_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_DMA_TRIG0_MIS_TXTRG_SET      ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_DMA_TRIG0_ISET Bits */
/* UNICOMMI2CC_DMA_TRIG0_ISET[TXTRG] Bits */
#define UNICOMMI2CC_DMA_TRIG0_ISET_TXTRG_OFS     (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_DMA_TRIG0_ISET_TXTRG_MASK    ((uint32_t)0x00000008U)         /* !< Transmit FIFO Trigger */
#define UNICOMMI2CC_DMA_TRIG0_ISET_TXTRG_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_DMA_TRIG0_ISET_TXTRG_SET     ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_DMA_TRIG1_IMASK Bits */
/* UNICOMMI2CC_DMA_TRIG1_IMASK[RXTRG] Bits */
#define UNICOMMI2CC_DMA_TRIG1_IMASK_RXTRG_OFS    (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_DMA_TRIG1_IMASK_RXTRG_MASK   ((uint32_t)0x00000004U)         /* !< Receive FIFO Trigger */
#define UNICOMMI2CC_DMA_TRIG1_IMASK_RXTRG_CLR    ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_DMA_TRIG1_IMASK_RXTRG_SET    ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_DMA_TRIG1_RIS Bits */
/* UNICOMMI2CC_DMA_TRIG1_RIS[RXTRG] Bits */
#define UNICOMMI2CC_DMA_TRIG1_RIS_RXTRG_OFS      (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_DMA_TRIG1_RIS_RXTRG_MASK     ((uint32_t)0x00000004U)         /* !< Receive Trigger */
#define UNICOMMI2CC_DMA_TRIG1_RIS_RXTRG_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_DMA_TRIG1_RIS_RXTRG_SET      ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_DMA_TRIG1_MIS Bits */
/* UNICOMMI2CC_DMA_TRIG1_MIS[RXTRG] Bits */
#define UNICOMMI2CC_DMA_TRIG1_MIS_RXTRG_OFS      (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_DMA_TRIG1_MIS_RXTRG_MASK     ((uint32_t)0x00000004U)         /* !< Receive FIFO Trigger */
#define UNICOMMI2CC_DMA_TRIG1_MIS_RXTRG_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_DMA_TRIG1_MIS_RXTRG_SET      ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_DMA_TRIG1_ISET Bits */
/* UNICOMMI2CC_DMA_TRIG1_ISET[RXTRG] Bits */
#define UNICOMMI2CC_DMA_TRIG1_ISET_RXTRG_OFS     (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_DMA_TRIG1_ISET_RXTRG_MASK    ((uint32_t)0x00000004U)         /* !< Receive FIFO Trigger */
#define UNICOMMI2CC_DMA_TRIG1_ISET_RXTRG_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_DMA_TRIG1_ISET_RXTRG_SET     ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_IIDX Bits */
/* UNICOMMI2CC_IIDX[STAT] Bits */
#define UNICOMMI2CC_IIDX_STAT_OFS                (0)                             /* !< STAT Offset */
#define UNICOMMI2CC_IIDX_STAT_MASK               ((uint32_t)0x000000FFU)         /* !< I2C Module Interrupt Vector Value.
                                                                                    This register provides the highes
                                                                                    priority interrupt index. A read
                                                                                    clears the corresponding interrupt
                                                                                    flag in RIS and MISC. 15h-1Fh =
                                                                                    Reserved */
#define UNICOMMI2CC_IIDX_STAT_NO_INTR            ((uint32_t)0x00000000U)         /* !< No interrupt pending */
#define UNICOMMI2CC_IIDX_STAT_RXDONEFG           ((uint32_t)0x00000001U)         /* !< Data received */
#define UNICOMMI2CC_IIDX_STAT_TXDONEFG           ((uint32_t)0x00000002U)         /* !< data transmitted */
#define UNICOMMI2CC_IIDX_STAT_RXTRG              ((uint32_t)0x00000003U)         /* !< Receive Trigger */
#define UNICOMMI2CC_IIDX_STAT_TXTRG              ((uint32_t)0x00000004U)         /* !< Transmit Trigger */
#define UNICOMMI2CC_IIDX_STAT_RXFULL             ((uint32_t)0x00000005U)         /* !< RX FIFO FULL Event/interrupt
                                                                                    pending */
#define UNICOMMI2CC_IIDX_STAT_TXEMPTY            ((uint32_t)0x00000006U)         /* !< Transmit FIFO/Buffer Empty
                                                                                    Event/interrupt pending */
#define UNICOMMI2CC_IIDX_STAT_NACKFG             ((uint32_t)0x00000008U)         /* !< Address/Data NACK */
#define UNICOMMI2CC_IIDX_STAT_STARTFG            ((uint32_t)0x00000009U)         /* !< Start Event */
#define UNICOMMI2CC_IIDX_STAT_STOPFG             ((uint32_t)0x0000000AU)         /* !< Stop Event */
#define UNICOMMI2CC_IIDX_STAT_ARBLOSTFG          ((uint32_t)0x0000000BU)         /* !< Arbitration Lost */
#define UNICOMMI2CC_IIDX_STAT_PEC_RX_ERR         ((uint32_t)0x0000000CU)         /* !< PEC Receive Error Event */
#define UNICOMMI2CC_IIDX_STAT_TIMEOUTA           ((uint32_t)0x0000000DU)         /* !< Timeout A Event */
#define UNICOMMI2CC_IIDX_STAT_TIMEOUTB           ((uint32_t)0x0000000EU)         /* !< Timeout B Event */
#define UNICOMMI2CC_IIDX_STAT_DMA_DONE_RX        ((uint32_t)0x00000010U)         /* !< DMA DONE on Channel RX */
#define UNICOMMI2CC_IIDX_STAT_DMA_DONE_TX        ((uint32_t)0x00000011U)         /* !< DMA DONE on Channel TX */
#define UNICOMMI2CC_IIDX_STAT_DMA_PREIRQ_RX      ((uint32_t)0x00000013U)         /* !< DMA PRE IRQ INTERRUPT */
#define UNICOMMI2CC_IIDX_STAT_DMA_PREIRQ_TX      ((uint32_t)0x00000014U)         /* !< DMA PRE IRQ INTERRUPT */

/* UNICOMMI2CC_CPU_INT_IMASK Bits */
/* UNICOMMI2CC_CPU_INT_IMASK[RXDONE] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_RXDONE_OFS     (0)                             /* !< RXDONE Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_RXDONE_MASK    ((uint32_t)0x00000001U)         /* !< RXDONE interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_RXDONE_CLR     ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_RXDONE_SET     ((uint32_t)0x00000001U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[TIMEOUTA] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTA_OFS   (12)                            /* !< TIMEOUTA Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTA_MASK  ((uint32_t)0x00001000U)         /* !< TIMEOUTA interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTA_CLR   ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTA_SET   ((uint32_t)0x00001000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[NACK] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_NACK_OFS       (7)                             /* !< NACK Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_NACK_MASK      ((uint32_t)0x00000080U)         /* !< NACK interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_NACK_CLR       ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_NACK_SET       ((uint32_t)0x00000080U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[START] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_START_OFS      (8)                             /* !< START Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_START_MASK     ((uint32_t)0x00000100U)         /* !< START interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_START_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_START_SET      ((uint32_t)0x00000100U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[STOP] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_STOP_OFS       (9)                             /* !< STOP Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_STOP_MASK      ((uint32_t)0x00000200U)         /* !< STOP interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_STOP_CLR       ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_STOP_SET       ((uint32_t)0x00000200U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[ARBLOST] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_ARBLOST_OFS    (10)                            /* !< ARBLOST Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_ARBLOST_MASK   ((uint32_t)0x00000400U)         /* !< Arbitration Lost interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_ARBLOST_CLR    ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_ARBLOST_SET    ((uint32_t)0x00000400U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[TXDONE] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_TXDONE_OFS     (1)                             /* !< TXDONE Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_TXDONE_MASK    ((uint32_t)0x00000002U)         /* !< Transmit Transaction completed
                                                                                    Interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_TXDONE_CLR     ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_TXDONE_SET     ((uint32_t)0x00000002U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[RXTRG] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_RXTRG_OFS      (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_RXTRG_MASK     ((uint32_t)0x00000004U)         /* !< Receive FIFO Trigger */
#define UNICOMMI2CC_CPU_INT_IMASK_RXTRG_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_RXTRG_SET      ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[TXTRG] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_TXTRG_OFS      (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_TXTRG_MASK     ((uint32_t)0x00000008U)         /* !< Transmit Trigger */
#define UNICOMMI2CC_CPU_INT_IMASK_TXTRG_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_TXTRG_SET      ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[DMA_DONE_TX] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_TX_OFS (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_TX_MASK ((uint32_t)0x00010000U)         /* !< DMA Done on Event Channel TX */
#define UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_TX_CLR ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_TX_SET ((uint32_t)0x00010000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[DMA_DONE_RX] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_RX_OFS (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_RX_MASK ((uint32_t)0x00008000U)         /* !< DMA Done on Event Channel RX */
#define UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_RX_CLR ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_RX_SET ((uint32_t)0x00008000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[PEC_RX_ERR] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_PEC_RX_ERR_OFS (11)                            /* !< PEC_RX_ERR Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_PEC_RX_ERR_MASK ((uint32_t)0x00000800U)         /* !< RX Pec Error Interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_PEC_RX_ERR_CLR ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_PEC_RX_ERR_SET ((uint32_t)0x00000800U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[TIMEOUTB] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTB_OFS   (13)                            /* !< TIMEOUTB Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTB_MASK  ((uint32_t)0x00002000U)         /* !< Timeout B Interrupt */
#define UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTB_CLR   ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTB_SET   ((uint32_t)0x00002000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[RXFULL] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_RXFULL_OFS     (4)                             /* !< RXFULL Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_RXFULL_MASK    ((uint32_t)0x00000010U)         /* !< RXFIFO full event */
#define UNICOMMI2CC_CPU_INT_IMASK_RXFULL_CLR     ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_RXFULL_SET     ((uint32_t)0x00000010U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_IMASK[TXEMPTY] Bits */
#define UNICOMMI2CC_CPU_INT_IMASK_TXEMPTY_OFS    (5)                             /* !< TXEMPTY Offset */
#define UNICOMMI2CC_CPU_INT_IMASK_TXEMPTY_MASK   ((uint32_t)0x00000020U)         /* !< Interrupt Mask for Transmit FIFO
                                                                                    Empty */
#define UNICOMMI2CC_CPU_INT_IMASK_TXEMPTY_CLR    ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_IMASK_TXEMPTY_SET    ((uint32_t)0x00000020U)         /* !< Set Interrupt Mask */

/* UNICOMMI2CC_CPU_INT_RIS Bits */
/* UNICOMMI2CC_CPU_INT_RIS[RXDONE] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_RXDONE_OFS       (0)                             /* !< RXDONE Offset */
#define UNICOMMI2CC_CPU_INT_RIS_RXDONE_MASK      ((uint32_t)0x00000001U)         /* !< Receive Done Interrupt:      RXDONE
                                                                                    interrupt is raised when a burst
                                                                                    length completes     Or, in case of
                                                                                    quick command, when a quick command
                                                                                    with R/Wn bit set to '1' */
#define UNICOMMI2CC_CPU_INT_RIS_RXDONE_CLR       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_RXDONE_SET       ((uint32_t)0x00000001U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[TIMEOUTA] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_TIMEOUTA_OFS     (12)                            /* !< TIMEOUTA Offset */
#define UNICOMMI2CC_CPU_INT_RIS_TIMEOUTA_MASK    ((uint32_t)0x00001000U)         /* !< Timeout A Interrupt */
#define UNICOMMI2CC_CPU_INT_RIS_TIMEOUTA_CLR     ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_TIMEOUTA_SET     ((uint32_t)0x00001000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[NACK] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_NACK_OFS         (7)                             /* !< NACK Offset */
#define UNICOMMI2CC_CPU_INT_RIS_NACK_MASK        ((uint32_t)0x00000080U)         /* !< Address/Data NACK Interrupt: set
                                                                                    when address or data nack is received */
#define UNICOMMI2CC_CPU_INT_RIS_NACK_CLR         ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_NACK_SET         ((uint32_t)0x00000080U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[START] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_START_OFS        (8)                             /* !< START Offset */
#define UNICOMMI2CC_CPU_INT_RIS_START_MASK       ((uint32_t)0x00000100U)         /* !< START Detection Interrupt */
#define UNICOMMI2CC_CPU_INT_RIS_START_CLR        ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_START_SET        ((uint32_t)0x00000100U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[STOP] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_STOP_OFS         (9)                             /* !< STOP Offset */
#define UNICOMMI2CC_CPU_INT_RIS_STOP_MASK        ((uint32_t)0x00000200U)         /* !< STOP Detection Interrupt */
#define UNICOMMI2CC_CPU_INT_RIS_STOP_CLR         ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_STOP_SET         ((uint32_t)0x00000200U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[ARBLOST] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_ARBLOST_OFS      (10)                            /* !< ARBLOST Offset */
#define UNICOMMI2CC_CPU_INT_RIS_ARBLOST_MASK     ((uint32_t)0x00000400U)         /* !< Arbitration Lost Interrupt: in
                                                                                    multi-controller systems, when this
                                                                                    controller loses out during
                                                                                    arbitration */
#define UNICOMMI2CC_CPU_INT_RIS_ARBLOST_CLR      ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_ARBLOST_SET      ((uint32_t)0x00000400U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[TXDONE] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_TXDONE_OFS       (1)                             /* !< TXDONE Offset */
#define UNICOMMI2CC_CPU_INT_RIS_TXDONE_MASK      ((uint32_t)0x00000002U)         /* !< Transmit Done Interrupt:
                                                                                    TXDONE interrupt is raised when a
                                                                                    burst length completes     Or, in
                                                                                    case of quick command, when a quick
                                                                                    command with R/Wn bit set to '0' */
#define UNICOMMI2CC_CPU_INT_RIS_TXDONE_CLR       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_TXDONE_SET       ((uint32_t)0x00000002U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[RXTRG] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_RXTRG_OFS        (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_CPU_INT_RIS_RXTRG_MASK       ((uint32_t)0x00000004U)         /* !< Receive Trigger */
#define UNICOMMI2CC_CPU_INT_RIS_RXTRG_CLR        ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_RIS_RXTRG_SET        ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[TXTRG] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_TXTRG_OFS        (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_CPU_INT_RIS_TXTRG_MASK       ((uint32_t)0x00000008U)         /* !< Transmit Trigger */
#define UNICOMMI2CC_CPU_INT_RIS_TXTRG_CLR        ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_RIS_TXTRG_SET        ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[DMA_DONE_TX] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_DMA_DONE_TX_OFS  (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMI2CC_CPU_INT_RIS_DMA_DONE_TX_MASK ((uint32_t)0x00010000U)         /* !< DMA Done on Event Channel TX */
#define UNICOMMI2CC_CPU_INT_RIS_DMA_DONE_TX_CLR  ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_CPU_INT_RIS_DMA_DONE_TX_SET  ((uint32_t)0x00010000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[DMA_DONE_RX] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_DMA_DONE_RX_OFS  (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMI2CC_CPU_INT_RIS_DMA_DONE_RX_MASK ((uint32_t)0x00008000U)         /* !< DMA Done on Event Channel RX */
#define UNICOMMI2CC_CPU_INT_RIS_DMA_DONE_RX_CLR  ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_CPU_INT_RIS_DMA_DONE_RX_SET  ((uint32_t)0x00008000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_RIS[PEC_RX_ERR] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_PEC_RX_ERR_OFS   (11)                            /* !< PEC_RX_ERR Offset */
#define UNICOMMI2CC_CPU_INT_RIS_PEC_RX_ERR_MASK  ((uint32_t)0x00000800U)         /* !< Receive PEC Error Interrupt: set
                                                                                    when the calculated PEC does not
                                                                                    match received PEC */
#define UNICOMMI2CC_CPU_INT_RIS_PEC_RX_ERR_CLR   ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_PEC_RX_ERR_SET   ((uint32_t)0x00000800U)         /* !< Interrupt Occured */
/* UNICOMMI2CC_CPU_INT_RIS[TIMEOUTB] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_TIMEOUTB_OFS     (13)                            /* !< TIMEOUTB Offset */
#define UNICOMMI2CC_CPU_INT_RIS_TIMEOUTB_MASK    ((uint32_t)0x00002000U)         /* !< Timeout B Interrupt */
#define UNICOMMI2CC_CPU_INT_RIS_TIMEOUTB_CLR     ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_TIMEOUTB_SET     ((uint32_t)0x00002000U)         /* !< Interrupt occured */
/* UNICOMMI2CC_CPU_INT_RIS[RXFULL] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_RXFULL_OFS       (4)                             /* !< RXFULL Offset */
#define UNICOMMI2CC_CPU_INT_RIS_RXFULL_MASK      ((uint32_t)0x00000010U)         /* !< RXFIFO full event */
#define UNICOMMI2CC_CPU_INT_RIS_RXFULL_CLR       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_RXFULL_SET       ((uint32_t)0x00000010U)         /* !< Interrupt occured */
/* UNICOMMI2CC_CPU_INT_RIS[TXEMPTY] Bits */
#define UNICOMMI2CC_CPU_INT_RIS_TXEMPTY_OFS      (5)                             /* !< TXEMPTY Offset */
#define UNICOMMI2CC_CPU_INT_RIS_TXEMPTY_MASK     ((uint32_t)0x00000020U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMI2CC_CPU_INT_RIS_TXEMPTY_CLR      ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_RIS_TXEMPTY_SET      ((uint32_t)0x00000020U)         /* !< Interrupt occured */

/* UNICOMMI2CC_CPU_INT_MIS Bits */
/* UNICOMMI2CC_CPU_INT_MIS[RXDONE] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_RXDONE_OFS       (0)                             /* !< RXDONE Offset */
#define UNICOMMI2CC_CPU_INT_MIS_RXDONE_MASK      ((uint32_t)0x00000001U)         /* !< Receive Data Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_RXDONE_CLR       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_RXDONE_SET       ((uint32_t)0x00000001U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[TIMEOUTA] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_TIMEOUTA_OFS     (12)                            /* !< TIMEOUTA Offset */
#define UNICOMMI2CC_CPU_INT_MIS_TIMEOUTA_MASK    ((uint32_t)0x00001000U)         /* !< Timeout A Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_TIMEOUTA_CLR     ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_TIMEOUTA_SET     ((uint32_t)0x00001000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[NACK] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_NACK_OFS         (7)                             /* !< NACK Offset */
#define UNICOMMI2CC_CPU_INT_MIS_NACK_MASK        ((uint32_t)0x00000080U)         /* !< Address/Data NACK Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_NACK_CLR         ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_NACK_SET         ((uint32_t)0x00000080U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[START] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_START_OFS        (8)                             /* !< START Offset */
#define UNICOMMI2CC_CPU_INT_MIS_START_MASK       ((uint32_t)0x00000100U)         /* !< START Detection Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_START_CLR        ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_START_SET        ((uint32_t)0x00000100U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[STOP] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_STOP_OFS         (9)                             /* !< STOP Offset */
#define UNICOMMI2CC_CPU_INT_MIS_STOP_MASK        ((uint32_t)0x00000200U)         /* !< STOP Detection Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_STOP_CLR         ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_STOP_SET         ((uint32_t)0x00000200U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[ARBLOST] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_ARBLOST_OFS      (10)                            /* !< ARBLOST Offset */
#define UNICOMMI2CC_CPU_INT_MIS_ARBLOST_MASK     ((uint32_t)0x00000400U)         /* !< Arbitration Lost Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_ARBLOST_CLR      ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_ARBLOST_SET      ((uint32_t)0x00000400U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[TXDONE] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_TXDONE_OFS       (1)                             /* !< TXDONE Offset */
#define UNICOMMI2CC_CPU_INT_MIS_TXDONE_MASK      ((uint32_t)0x00000002U)         /* !< Transmit Transaction completed
                                                                                    Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_TXDONE_CLR       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_TXDONE_SET       ((uint32_t)0x00000002U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[RXTRG] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_RXTRG_OFS        (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_CPU_INT_MIS_RXTRG_MASK       ((uint32_t)0x00000004U)         /* !< Receive FIFO Trigger */
#define UNICOMMI2CC_CPU_INT_MIS_RXTRG_CLR        ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_MIS_RXTRG_SET        ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[TXTRG] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_TXTRG_OFS        (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_CPU_INT_MIS_TXTRG_MASK       ((uint32_t)0x00000008U)         /* !< Transmit Trigger */
#define UNICOMMI2CC_CPU_INT_MIS_TXTRG_CLR        ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_MIS_TXTRG_SET        ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[DMA_DONE_TX] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_DMA_DONE_TX_OFS  (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMI2CC_CPU_INT_MIS_DMA_DONE_TX_MASK ((uint32_t)0x00010000U)         /* !< DMA Done on Event Channel TX */
#define UNICOMMI2CC_CPU_INT_MIS_DMA_DONE_TX_CLR  ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_CPU_INT_MIS_DMA_DONE_TX_SET  ((uint32_t)0x00010000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[DMA_DONE_RX] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_DMA_DONE_RX_OFS  (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMI2CC_CPU_INT_MIS_DMA_DONE_RX_MASK ((uint32_t)0x00008000U)         /* !< DMA Done on Event Channel RX */
#define UNICOMMI2CC_CPU_INT_MIS_DMA_DONE_RX_CLR  ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_CPU_INT_MIS_DMA_DONE_RX_SET  ((uint32_t)0x00008000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_MIS[PEC_RX_ERR] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_PEC_RX_ERR_OFS   (11)                            /* !< PEC_RX_ERR Offset */
#define UNICOMMI2CC_CPU_INT_MIS_PEC_RX_ERR_MASK  ((uint32_t)0x00000800U)         /* !< RX Pec Error Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_PEC_RX_ERR_CLR   ((uint32_t)0x00000000U)         /* !< Clear interrupt mask */
#define UNICOMMI2CC_CPU_INT_MIS_PEC_RX_ERR_SET   ((uint32_t)0x00000800U)         /* !< Set interrupt mask */
/* UNICOMMI2CC_CPU_INT_MIS[TIMEOUTB] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_TIMEOUTB_OFS     (13)                            /* !< TIMEOUTB Offset */
#define UNICOMMI2CC_CPU_INT_MIS_TIMEOUTB_MASK    ((uint32_t)0x00002000U)         /* !< Timeout B Interrupt */
#define UNICOMMI2CC_CPU_INT_MIS_TIMEOUTB_CLR     ((uint32_t)0x00000000U)         /* !< Clear interrupt mask */
#define UNICOMMI2CC_CPU_INT_MIS_TIMEOUTB_SET     ((uint32_t)0x00002000U)         /* !< Set interrupt mask */
/* UNICOMMI2CC_CPU_INT_MIS[RXFULL] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_RXFULL_OFS       (4)                             /* !< RXFULL Offset */
#define UNICOMMI2CC_CPU_INT_MIS_RXFULL_MASK      ((uint32_t)0x00000010U)         /* !< RXFIFO full */
#define UNICOMMI2CC_CPU_INT_MIS_RXFULL_CLR       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_RXFULL_SET       ((uint32_t)0x00000010U)         /* !< Interrupt occured */
/* UNICOMMI2CC_CPU_INT_MIS[TXEMPTY] Bits */
#define UNICOMMI2CC_CPU_INT_MIS_TXEMPTY_OFS      (5)                             /* !< TXEMPTY Offset */
#define UNICOMMI2CC_CPU_INT_MIS_TXEMPTY_MASK     ((uint32_t)0x00000020U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMI2CC_CPU_INT_MIS_TXEMPTY_CLR      ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMI2CC_CPU_INT_MIS_TXEMPTY_SET      ((uint32_t)0x00000020U)         /* !< Interrupt occured */

/* UNICOMMI2CC_CPU_INT_ISET Bits */
/* UNICOMMI2CC_CPU_INT_ISET[RXDONE] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_RXDONE_OFS      (0)                             /* !< RXDONE Offset */
#define UNICOMMI2CC_CPU_INT_ISET_RXDONE_MASK     ((uint32_t)0x00000001U)         /* !< Receive Data Interrupt Signals that
                                                                                    a byte has been received */
#define UNICOMMI2CC_CPU_INT_ISET_RXDONE_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_RXDONE_SET      ((uint32_t)0x00000001U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[TIMEOUTA] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_TIMEOUTA_OFS    (12)                            /* !< TIMEOUTA Offset */
#define UNICOMMI2CC_CPU_INT_ISET_TIMEOUTA_MASK   ((uint32_t)0x00001000U)         /* !< Timeout A interrupt */
#define UNICOMMI2CC_CPU_INT_ISET_TIMEOUTA_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_TIMEOUTA_SET    ((uint32_t)0x00001000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[NACK] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_NACK_OFS        (7)                             /* !< NACK Offset */
#define UNICOMMI2CC_CPU_INT_ISET_NACK_MASK       ((uint32_t)0x00000080U)         /* !< Address/Data NACK Interrupt */
#define UNICOMMI2CC_CPU_INT_ISET_NACK_NO_EFFECT  ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_NACK_SET        ((uint32_t)0x00000080U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[START] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_START_OFS       (8)                             /* !< START Offset */
#define UNICOMMI2CC_CPU_INT_ISET_START_MASK      ((uint32_t)0x00000100U)         /* !< START Detection Interrupt */
#define UNICOMMI2CC_CPU_INT_ISET_START_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_START_SET       ((uint32_t)0x00000100U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[STOP] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_STOP_OFS        (9)                             /* !< STOP Offset */
#define UNICOMMI2CC_CPU_INT_ISET_STOP_MASK       ((uint32_t)0x00000200U)         /* !< STOP Detection Interrupt */
#define UNICOMMI2CC_CPU_INT_ISET_STOP_NO_EFFECT  ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_STOP_SET        ((uint32_t)0x00000200U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[ARBLOST] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_ARBLOST_OFS     (10)                            /* !< ARBLOST Offset */
#define UNICOMMI2CC_CPU_INT_ISET_ARBLOST_MASK    ((uint32_t)0x00000400U)         /* !< Arbitration Lost Interrupt */
#define UNICOMMI2CC_CPU_INT_ISET_ARBLOST_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_ARBLOST_SET     ((uint32_t)0x00000400U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[TXDONE] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_TXDONE_OFS      (1)                             /* !< TXDONE Offset */
#define UNICOMMI2CC_CPU_INT_ISET_TXDONE_MASK     ((uint32_t)0x00000002U)         /* !< Transmit Transaction completed
                                                                                    Interrupt */
#define UNICOMMI2CC_CPU_INT_ISET_TXDONE_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_TXDONE_SET      ((uint32_t)0x00000002U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[RXTRG] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_RXTRG_OFS       (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_CPU_INT_ISET_RXTRG_MASK      ((uint32_t)0x00000004U)         /* !< Receive FIFO Trigger */
#define UNICOMMI2CC_CPU_INT_ISET_RXTRG_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_ISET_RXTRG_SET       ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[TXTRG] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_TXTRG_OFS       (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_CPU_INT_ISET_TXTRG_MASK      ((uint32_t)0x00000008U)         /* !< Transmit FIFO Trigger */
#define UNICOMMI2CC_CPU_INT_ISET_TXTRG_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_CPU_INT_ISET_TXTRG_SET       ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[DMA_DONE_TX] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_DMA_DONE_TX_OFS (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMI2CC_CPU_INT_ISET_DMA_DONE_TX_MASK ((uint32_t)0x00010000U)         /* !< DMA Done on Event Channel TX */
#define UNICOMMI2CC_CPU_INT_ISET_DMA_DONE_TX_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_CPU_INT_ISET_DMA_DONE_TX_SET ((uint32_t)0x00010000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[DMA_DONE_RX] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_DMA_DONE_RX_OFS (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMI2CC_CPU_INT_ISET_DMA_DONE_RX_MASK ((uint32_t)0x00008000U)         /* !< DMA Done on Event Channel RX */
#define UNICOMMI2CC_CPU_INT_ISET_DMA_DONE_RX_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_CPU_INT_ISET_DMA_DONE_RX_SET ((uint32_t)0x00008000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_CPU_INT_ISET[PEC_RX_ERR] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_PEC_RX_ERR_OFS  (11)                            /* !< PEC_RX_ERR Offset */
#define UNICOMMI2CC_CPU_INT_ISET_PEC_RX_ERR_MASK ((uint32_t)0x00000800U)         /* !< RX Pec Error Interrupt */
#define UNICOMMI2CC_CPU_INT_ISET_PEC_RX_ERR_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_PEC_RX_ERR_SET  ((uint32_t)0x00000800U)         /* !< Set interrupt */
/* UNICOMMI2CC_CPU_INT_ISET[TIMEOUTB] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_TIMEOUTB_OFS    (13)                            /* !< TIMEOUTB Offset */
#define UNICOMMI2CC_CPU_INT_ISET_TIMEOUTB_MASK   ((uint32_t)0x00002000U)         /* !< Timeout B Interrupt */
#define UNICOMMI2CC_CPU_INT_ISET_TIMEOUTB_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_TIMEOUTB_SET    ((uint32_t)0x00002000U)         /* !< Set interrupt */
/* UNICOMMI2CC_CPU_INT_ISET[RXFULL] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_RXFULL_OFS      (4)                             /* !< RXFULL Offset */
#define UNICOMMI2CC_CPU_INT_ISET_RXFULL_MASK     ((uint32_t)0x00000010U)         /* !< RXFIFO full event */
#define UNICOMMI2CC_CPU_INT_ISET_RXFULL_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_RXFULL_SET      ((uint32_t)0x00000010U)         /* !< Set Interrupt */
/* UNICOMMI2CC_CPU_INT_ISET[TXEMPTY] Bits */
#define UNICOMMI2CC_CPU_INT_ISET_TXEMPTY_OFS     (5)                             /* !< TXEMPTY Offset */
#define UNICOMMI2CC_CPU_INT_ISET_TXEMPTY_MASK    ((uint32_t)0x00000020U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMI2CC_CPU_INT_ISET_TXEMPTY_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_CPU_INT_ISET_TXEMPTY_SET     ((uint32_t)0x00000020U)         /* !< Set Interrupt */

/* UNICOMMI2CC_ICLR Bits */
/* UNICOMMI2CC_ICLR[RXDONE] Bits */
#define UNICOMMI2CC_ICLR_RXDONE_OFS              (0)                             /* !< RXDONE Offset */
#define UNICOMMI2CC_ICLR_RXDONE_MASK             ((uint32_t)0x00000001U)         /* !< Receive Data Interrupt Signals that
                                                                                    a byte has been received */
#define UNICOMMI2CC_ICLR_RXDONE_NO_EFFECT        ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_RXDONE_CLR              ((uint32_t)0x00000001U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[TIMEOUTA] Bits */
#define UNICOMMI2CC_ICLR_TIMEOUTA_OFS            (12)                            /* !< TIMEOUTA Offset */
#define UNICOMMI2CC_ICLR_TIMEOUTA_MASK           ((uint32_t)0x00001000U)         /* !< Timeout A interrupt */
#define UNICOMMI2CC_ICLR_TIMEOUTA_NO_EFFECT      ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_TIMEOUTA_CLR            ((uint32_t)0x00001000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[NACK] Bits */
#define UNICOMMI2CC_ICLR_NACK_OFS                (7)                             /* !< NACK Offset */
#define UNICOMMI2CC_ICLR_NACK_MASK               ((uint32_t)0x00000080U)         /* !< Address/Data NACK Interrupt */
#define UNICOMMI2CC_ICLR_NACK_NO_EFFECT          ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_NACK_CLR                ((uint32_t)0x00000080U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[START] Bits */
#define UNICOMMI2CC_ICLR_START_OFS               (8)                             /* !< START Offset */
#define UNICOMMI2CC_ICLR_START_MASK              ((uint32_t)0x00000100U)         /* !< START Detection Interrupt */
#define UNICOMMI2CC_ICLR_START_NO_EFFECT         ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_START_CLR               ((uint32_t)0x00000100U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[STOP] Bits */
#define UNICOMMI2CC_ICLR_STOP_OFS                (9)                             /* !< STOP Offset */
#define UNICOMMI2CC_ICLR_STOP_MASK               ((uint32_t)0x00000200U)         /* !< STOP Detection Interrupt */
#define UNICOMMI2CC_ICLR_STOP_NO_EFFECT          ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_STOP_CLR                ((uint32_t)0x00000200U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[ARBLOST] Bits */
#define UNICOMMI2CC_ICLR_ARBLOST_OFS             (10)                            /* !< ARBLOST Offset */
#define UNICOMMI2CC_ICLR_ARBLOST_MASK            ((uint32_t)0x00000400U)         /* !< Arbitration Lost Interrupt */
#define UNICOMMI2CC_ICLR_ARBLOST_NO_EFFECT       ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_ARBLOST_CLR             ((uint32_t)0x00000400U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[TXDONE] Bits */
#define UNICOMMI2CC_ICLR_TXDONE_OFS              (1)                             /* !< TXDONE Offset */
#define UNICOMMI2CC_ICLR_TXDONE_MASK             ((uint32_t)0x00000002U)         /* !< Transmit Transaction completed
                                                                                    Interrupt */
#define UNICOMMI2CC_ICLR_TXDONE_NO_EFFECT        ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_TXDONE_CLR              ((uint32_t)0x00000002U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[RXTRG] Bits */
#define UNICOMMI2CC_ICLR_RXTRG_OFS               (2)                             /* !< RXTRG Offset */
#define UNICOMMI2CC_ICLR_RXTRG_MASK              ((uint32_t)0x00000004U)         /* !< Receive FIFO Trigger */
#define UNICOMMI2CC_ICLR_RXTRG_NO_EFFECT         ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_ICLR_RXTRG_CLR               ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[TXTRG] Bits */
#define UNICOMMI2CC_ICLR_TXTRG_OFS               (3)                             /* !< TXTRG Offset */
#define UNICOMMI2CC_ICLR_TXTRG_MASK              ((uint32_t)0x00000008U)         /* !< Transmit FIFO Trigger */
#define UNICOMMI2CC_ICLR_TXTRG_NO_EFFECT         ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMI2CC_ICLR_TXTRG_CLR               ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[DMA_DONE_TX] Bits */
#define UNICOMMI2CC_ICLR_DMA_DONE_TX_OFS         (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMI2CC_ICLR_DMA_DONE_TX_MASK        ((uint32_t)0x00010000U)         /* !< DMA Done on Event Channel TX */
#define UNICOMMI2CC_ICLR_DMA_DONE_TX_NO_EFFECT   ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_ICLR_DMA_DONE_TX_CLR         ((uint32_t)0x00010000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[DMA_DONE_RX] Bits */
#define UNICOMMI2CC_ICLR_DMA_DONE_RX_OFS         (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMI2CC_ICLR_DMA_DONE_RX_MASK        ((uint32_t)0x00008000U)         /* !< DMA Done on Event Channel RX */
#define UNICOMMI2CC_ICLR_DMA_DONE_RX_NO_EFFECT   ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMI2CC_ICLR_DMA_DONE_RX_CLR         ((uint32_t)0x00008000U)         /* !< Set Interrupt Mask */
/* UNICOMMI2CC_ICLR[PEC_RX_ERR] Bits */
#define UNICOMMI2CC_ICLR_PEC_RX_ERR_OFS          (11)                            /* !< PEC_RX_ERR Offset */
#define UNICOMMI2CC_ICLR_PEC_RX_ERR_MASK         ((uint32_t)0x00000800U)         /* !< RX Pec Error Interrupt */
#define UNICOMMI2CC_ICLR_PEC_RX_ERR_NO_EFFECT    ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_PEC_RX_ERR_CLR          ((uint32_t)0x00000800U)         /* !< Clear Interrupt */
/* UNICOMMI2CC_ICLR[TIMEOUTB] Bits */
#define UNICOMMI2CC_ICLR_TIMEOUTB_OFS            (13)                            /* !< TIMEOUTB Offset */
#define UNICOMMI2CC_ICLR_TIMEOUTB_MASK           ((uint32_t)0x00002000U)         /* !< Timeout B Interrupt */
#define UNICOMMI2CC_ICLR_TIMEOUTB_NO_EFFECT      ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_TIMEOUTB_CLR            ((uint32_t)0x00002000U)         /* !< Clear Interrupt */
/* UNICOMMI2CC_ICLR[RXFULL] Bits */
#define UNICOMMI2CC_ICLR_RXFULL_OFS              (4)                             /* !< RXFULL Offset */
#define UNICOMMI2CC_ICLR_RXFULL_MASK             ((uint32_t)0x00000010U)         /* !< RXFIFO full event */
#define UNICOMMI2CC_ICLR_RXFULL_NO_EFFECT        ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_RXFULL_CLR              ((uint32_t)0x00000010U)         /* !< Clear Interrupt */
/* UNICOMMI2CC_ICLR[TXEMPTY] Bits */
#define UNICOMMI2CC_ICLR_TXEMPTY_OFS             (5)                             /* !< TXEMPTY Offset */
#define UNICOMMI2CC_ICLR_TXEMPTY_MASK            ((uint32_t)0x00000020U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMI2CC_ICLR_TXEMPTY_NO_EFFECT       ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMI2CC_ICLR_TXEMPTY_CLR             ((uint32_t)0x00000020U)         /* !< Clear Interrupt */

/* UNICOMMI2CC_CLKDIV Bits */
/* UNICOMMI2CC_CLKDIV[RATIO] Bits */
#define UNICOMMI2CC_CLKDIV_RATIO_OFS             (0)                             /* !< RATIO Offset */
#define UNICOMMI2CC_CLKDIV_RATIO_MASK            ((uint32_t)0x00000007U)         /* !< Selects divide ratio of module
                                                                                    clock  Division factor  0 : DIV_BY_1
                                                                                    1 : DIV_BY_2 .... 63: DIV_BY_64 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_1        ((uint32_t)0x00000000U)         /* !< Do not divide clock source */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_2        ((uint32_t)0x00000001U)         /* !< Divide clock source by 2 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_3        ((uint32_t)0x00000002U)         /* !< Divide clock source by 3 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_4        ((uint32_t)0x00000003U)         /* !< Divide clock source by 4 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_5        ((uint32_t)0x00000004U)         /* !< Divide clock source by 5 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_6        ((uint32_t)0x00000005U)         /* !< Divide clock source by 6 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_7        ((uint32_t)0x00000006U)         /* !< Divide clock source by 7 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_8        ((uint32_t)0x00000007U)         /* !< Divide clock source by 8 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_61       ((uint32_t)0x0000003CU)         /* !< Divide clock source by 8 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_62       ((uint32_t)0x0000003DU)         /* !< Divide clock source by 8 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_63       ((uint32_t)0x0000003EU)         /* !< Divide clock source by 8 */
#define UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_64       ((uint32_t)0x0000003FU)         /* !< Divide clock source by 8 */

/* UNICOMMI2CC_CLKSEL Bits */
/* UNICOMMI2CC_CLKSEL[BUSCLK_SEL] Bits */
#define UNICOMMI2CC_CLKSEL_BUSCLK_SEL_OFS        (3)                             /* !< BUSCLK_SEL Offset */
#define UNICOMMI2CC_CLKSEL_BUSCLK_SEL_MASK       ((uint32_t)0x00000008U)         /* !< Selects BUS CLK as clock source if
                                                                                    enabled */
#define UNICOMMI2CC_CLKSEL_BUSCLK_SEL_DISABLE    ((uint32_t)0x00000000U)         /* !< Does not select this clock as a
                                                                                    source */
#define UNICOMMI2CC_CLKSEL_BUSCLK_SEL_ENABLE     ((uint32_t)0x00000008U)         /* !< Select this clock as a source */

/* UNICOMMI2CC_PDBGCTL Bits */
/* UNICOMMI2CC_PDBGCTL[FREE] Bits */
#define UNICOMMI2CC_PDBGCTL_FREE_OFS             (0)                             /* !< FREE Offset */
#define UNICOMMI2CC_PDBGCTL_FREE_MASK            ((uint32_t)0x00000001U)         /* !< Free run control */
#define UNICOMMI2CC_PDBGCTL_FREE_STOP            ((uint32_t)0x00000000U)         /* !< The peripheral freezes
                                                                                    functionality while the Core Halted
                                                                                    input is asserted and resumes when it
                                                                                    is deasserted. */
#define UNICOMMI2CC_PDBGCTL_FREE_RUN             ((uint32_t)0x00000001U)         /* !< The peripheral ignores the state of
                                                                                    the Core Halted input */
/* UNICOMMI2CC_PDBGCTL[SOFT] Bits */
#define UNICOMMI2CC_PDBGCTL_SOFT_OFS             (1)                             /* !< SOFT Offset */
#define UNICOMMI2CC_PDBGCTL_SOFT_MASK            ((uint32_t)0x00000002U)         /* !< Soft halt boundary control. This
                                                                                    function is only available, if [FREE]
                                                                                    is set to 'STOP' */
#define UNICOMMI2CC_PDBGCTL_SOFT_DEPRECATED      ((uint32_t)0x00000000U)         /* !< Not supported */
#define UNICOMMI2CC_PDBGCTL_SOFT_DELAYED         ((uint32_t)0x00000002U)         /* !< The peripheral blocks the debug
                                                                                    freeze until it has reached a
                                                                                    boundary where it can resume without
                                                                                    corruption */

/* UNICOMMI2CC_INTCTL Bits */
/* UNICOMMI2CC_INTCTL[INTEVAL] Bits */
#define UNICOMMI2CC_INTCTL_INTEVAL_OFS           (0)                             /* !< INTEVAL Offset */
#define UNICOMMI2CC_INTCTL_INTEVAL_MASK          ((uint32_t)0x00000001U)         /* !< Writing a 1 to this field
                                                                                    re-evaluates the interrupt sources. */
#define UNICOMMI2CC_INTCTL_INTEVAL_DISABLE       ((uint32_t)0x00000000U)         /* !< The interrupt or event line is
                                                                                    disabled. */
#define UNICOMMI2CC_INTCTL_INTEVAL_EVAL          ((uint32_t)0x00000001U)         /* !< The interrupt or event line is in
                                                                                    software mode. Software must clear
                                                                                    the RIS. */

/* UNICOMMI2CC_CTR Bits */
/* UNICOMMI2CC_CTR[FRM_START] Bits */
#define UNICOMMI2CC_CTR_FRM_START_OFS            (0)                             /* !< FRM_START Offset */
#define UNICOMMI2CC_CTR_FRM_START_MASK           ((uint32_t)0x00000001U)         /* !< Start Transfer */
#define UNICOMMI2CC_CTR_FRM_START_DISABLE        ((uint32_t)0x00000000U)         /* !< In standard mode, this encoding
                                                                                    means the Controller is unable to
                                                                                    transmit or receive data. */
#define UNICOMMI2CC_CTR_FRM_START_ENABLE         ((uint32_t)0x00000001U)         /* !< The Controller is able to transmit
                                                                                    or receive data. See field decoding
                                                                                    in Table: MCTR Field decoding. */
/* UNICOMMI2CC_CTR[START] Bits */
#define UNICOMMI2CC_CTR_START_OFS                (1)                             /* !< START Offset */
#define UNICOMMI2CC_CTR_START_MASK               ((uint32_t)0x00000002U)         /* !< Generate START */
#define UNICOMMI2CC_CTR_START_DISABLE            ((uint32_t)0x00000000U)         /* !< The controller does not generate
                                                                                    the START condition. */
#define UNICOMMI2CC_CTR_START_ENABLE             ((uint32_t)0x00000002U)         /* !< The controller generates the START
                                                                                    or repeated START condition. See
                                                                                    field decoding in Table: MCTR Field
                                                                                    decoding. */
/* UNICOMMI2CC_CTR[STOP] Bits */
#define UNICOMMI2CC_CTR_STOP_OFS                 (2)                             /* !< STOP Offset */
#define UNICOMMI2CC_CTR_STOP_MASK                ((uint32_t)0x00000004U)         /* !< Generate STOP */
#define UNICOMMI2CC_CTR_STOP_DISABLE             ((uint32_t)0x00000000U)         /* !< The controller does not generate
                                                                                    the STOP condition. */
#define UNICOMMI2CC_CTR_STOP_ENABLE              ((uint32_t)0x00000004U)         /* !< The controller generates the STOP
                                                                                    condition. See field decoding in
                                                                                    Table: MCTR Field decoding. */
/* UNICOMMI2CC_CTR[ACK] Bits */
#define UNICOMMI2CC_CTR_ACK_OFS                  (3)                             /* !< ACK Offset */
#define UNICOMMI2CC_CTR_ACK_MASK                 ((uint32_t)0x00000008U)         /* !< Data Acknowledge Enable */
#define UNICOMMI2CC_CTR_ACK_DISABLE              ((uint32_t)0x00000000U)         /* !< The last received data byte of a
                                                                                    transaction is not acknowledged
                                                                                    automatically . */
#define UNICOMMI2CC_CTR_ACK_ENABLE               ((uint32_t)0x00000008U)         /* !< The last received data byte of a
                                                                                    transaction is acknowledged
                                                                                    automatically . */
/* UNICOMMI2CC_CTR[BLEN] Bits */
#define UNICOMMI2CC_CTR_BLEN_OFS                 (16)                            /* !< BLEN Offset */
#define UNICOMMI2CC_CTR_BLEN_MASK                ((uint32_t)0x0FFF0000U)         /* !< I2C transaction length */
#define UNICOMMI2CC_CTR_BLEN_MINIMUM             ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMI2CC_CTR_BLEN_MAXIMUM             ((uint32_t)0x0FFF0000U)         /* !< Highest possible value */
/* UNICOMMI2CC_CTR[ACKOEN] Bits */
#define UNICOMMI2CC_CTR_ACKOEN_OFS               (4)                             /* !< ACKOEN Offset */
#define UNICOMMI2CC_CTR_ACKOEN_MASK              ((uint32_t)0x00000010U)         /* !< ACK overrride Enable */
#define UNICOMMI2CC_CTR_ACKOEN_DISABLE           ((uint32_t)0x00000000U)         /* !< No special behavior */
#define UNICOMMI2CC_CTR_ACKOEN_ENABLE            ((uint32_t)0x00000010U)         /* !< When 1 and the Controller is
                                                                                    receiving data and the number of
                                                                                    bytes indicated in MBLEN have been
                                                                                    received, the state machine will
                                                                                    generate an rxdone interrupt and wait
                                                                                    at the start of the ACK for FW to
                                                                                    indicate if an ACK or NACK should be
                                                                                    sent. The ACK or NACK is selected by
                                                                                    writing the MCTR register and setting
                                                                                    ACK accordingly. The other fields in
                                                                                    this register can also be written at
                                                                                    this time to continue on with the
                                                                                    transaction. If a NACK is sent the
                                                                                    state machine will automatically send
                                                                                    a Stop. */
/* UNICOMMI2CC_CTR[RD_ON_TXEMPTY] Bits */
#define UNICOMMI2CC_CTR_RD_ON_TXEMPTY_OFS        (5)                             /* !< RD_ON_TXEMPTY Offset */
#define UNICOMMI2CC_CTR_RD_ON_TXEMPTY_MASK       ((uint32_t)0x00000020U)         /* !< Read on TX Empty */
#define UNICOMMI2CC_CTR_RD_ON_TXEMPTY_DISABLE    ((uint32_t)0x00000000U)         /* !< No special behavior */
#define UNICOMMI2CC_CTR_RD_ON_TXEMPTY_ENABLE     ((uint32_t)0x00000020U)         /* !< When 1 the Controller will transmit
                                                                                    all bytes from the TX FIFO before
                                                                                    continuing with the programmed Burst
                                                                                    Run Read. If the DIR is not set to
                                                                                    Read in the MSA then this bit is
                                                                                    ignored. The Start must be set in the
                                                                                    MCTR for proper I2C protocol. The
                                                                                    Controller will first send the Start
                                                                                    Condition, I2C Address with R/W bit
                                                                                    set to write, before sending the
                                                                                    bytes in the TX FIFO. When the TX
                                                                                    FIFO is empty, the I2C transaction
                                                                                    will continue as programmed in MTCR
                                                                                    and MSA without sending a Stop
                                                                                    Condition. This is intended to be
                                                                                    used to perform simple I2C command
                                                                                    based reads transition that will
                                                                                    complete after initiating them
                                                                                    without having to get an interrupt to
                                                                                    turn the bus around. */
/* UNICOMMI2CC_CTR[SUSPEND] Bits */
#define UNICOMMI2CC_CTR_SUSPEND_OFS              (6)                             /* !< SUSPEND Offset */
#define UNICOMMI2CC_CTR_SUSPEND_MASK             ((uint32_t)0x00000040U)         /* !< Suspend external communication */
#define UNICOMMI2CC_CTR_SUSPEND_DISABLE          ((uint32_t)0x00000000U)         /* !< Functional mode resumed */
#define UNICOMMI2CC_CTR_SUSPEND_ENABLE           ((uint32_t)0x00000040U)         /* !< External communication suspended */

/* UNICOMMI2CC_CR Bits */
/* UNICOMMI2CC_CR[MCTL] Bits */
#define UNICOMMI2CC_CR_MCTL_OFS                  (1)                             /* !< MCTL Offset */
#define UNICOMMI2CC_CR_MCTL_MASK                 ((uint32_t)0x00000002U)         /* !< MultiController mode. In
                                                                                    MultiController mode the SCL high
                                                                                    time counts once the SCL line has
                                                                                    been detected high. If this is not
                                                                                    enabled the high time counts as soon
                                                                                    as the SCL line has been set high by
                                                                                    the I2C controller. */
#define UNICOMMI2CC_CR_MCTL_DISABLE              ((uint32_t)0x00000000U)         /* !< Disable MultiController mode. */
#define UNICOMMI2CC_CR_MCTL_ENABLE               ((uint32_t)0x00000002U)         /* !< Enable MultiController mode. */
/* UNICOMMI2CC_CR[ENABLE] Bits */
#define UNICOMMI2CC_CR_ENABLE_OFS                (0)                             /* !< ENABLE Offset */
#define UNICOMMI2CC_CR_ENABLE_MASK               ((uint32_t)0x00000001U)         /* !< Enable module.  After this bit has
                                                                                    been set, it should not be set again
                                                                                    unless it has been cleared by writing
                                                                                    a 0 or by a reset, otherwise transfer
                                                                                    failures may occur. */
#define UNICOMMI2CC_CR_ENABLE_DISABLE            ((uint32_t)0x00000000U)         /* !< Disables operation. */
#define UNICOMMI2CC_CR_ENABLE_ENABLE             ((uint32_t)0x00000001U)         /* !< Enables operation. */
/* UNICOMMI2CC_CR[CLKSTRETCH] Bits */
#define UNICOMMI2CC_CR_CLKSTRETCH_OFS            (2)                             /* !< CLKSTRETCH Offset */
#define UNICOMMI2CC_CR_CLKSTRETCH_MASK           ((uint32_t)0x00000004U)         /* !< Clock Stretching */
#define UNICOMMI2CC_CR_CLKSTRETCH_DISABLE        ((uint32_t)0x00000000U)         /* !< Disables the clock stretching
                                                                                    detection. This can be disabled if no
                                                                                    Target on the bus does support clock
                                                                                    stretching, so that the maximum speed
                                                                                    on the bus can be reached. */
#define UNICOMMI2CC_CR_CLKSTRETCH_ENABLE         ((uint32_t)0x00000004U)         /* !< Enables the clock stretching
                                                                                    detection. Enabling the clock
                                                                                    stretching ensures compliance to the
                                                                                    I2C standard but could limit the
                                                                                    speed due the clock stretching. */

/* UNICOMMI2CC_SR Bits */
/* UNICOMMI2CC_SR[BUSY] Bits */
#define UNICOMMI2CC_SR_BUSY_OFS                  (0)                             /* !< BUSY Offset */
#define UNICOMMI2CC_SR_BUSY_MASK                 ((uint32_t)0x00000001U)         /* !< FSM Busy The BUSY bit is set during
                                                                                    an ongoing transaction, so is set
                                                                                    during the transmit/receive of the
                                                                                    amount of data set in MBLEN including
                                                                                    START, RESTART, Address and STOP
                                                                                    signal generation when required for
                                                                                    the current transaction. */
#define UNICOMMI2CC_SR_BUSY_CLEARED              ((uint32_t)0x00000000U)         /* !< The controller is idle. */
#define UNICOMMI2CC_SR_BUSY_SET                  ((uint32_t)0x00000001U)         /* !< The controller is busy. */
/* UNICOMMI2CC_SR[ERR] Bits */
#define UNICOMMI2CC_SR_ERR_OFS                   (1)                             /* !< ERR Offset */
#define UNICOMMI2CC_SR_ERR_MASK                  ((uint32_t)0x00000002U)         /* !< Error  The error can be from the
                                                                                    Target address not being acknowledged
                                                                                    or the transmit data not being
                                                                                    acknowledged. */
#define UNICOMMI2CC_SR_ERR_CLEARED               ((uint32_t)0x00000000U)         /* !< No error was detected on the last
                                                                                    operation. */
#define UNICOMMI2CC_SR_ERR_SET                   ((uint32_t)0x00000002U)         /* !< An error occurred on the last
                                                                                    operation. */
/* UNICOMMI2CC_SR[ADRACK] Bits */
#define UNICOMMI2CC_SR_ADRACK_OFS                (2)                             /* !< ADRACK Offset */
#define UNICOMMI2CC_SR_ADRACK_MASK               ((uint32_t)0x00000004U)         /* !< Acknowledge Address */
#define UNICOMMI2CC_SR_ADRACK_CLEARED            ((uint32_t)0x00000000U)         /* !< The transmitted address was
                                                                                    acknowledged */
#define UNICOMMI2CC_SR_ADRACK_SET                ((uint32_t)0x00000004U)         /* !< The transmitted address was not
                                                                                    acknowledged. */
/* UNICOMMI2CC_SR[DATACK] Bits */
#define UNICOMMI2CC_SR_DATACK_OFS                (3)                             /* !< DATACK Offset */
#define UNICOMMI2CC_SR_DATACK_MASK               ((uint32_t)0x00000008U)         /* !< Acknowledge Data */
#define UNICOMMI2CC_SR_DATACK_CLEARED            ((uint32_t)0x00000000U)         /* !< The transmitted data was
                                                                                    acknowledged */
#define UNICOMMI2CC_SR_DATACK_SET                ((uint32_t)0x00000008U)         /* !< The transmitted data was not
                                                                                    acknowledged. */
/* UNICOMMI2CC_SR[ARBLST] Bits */
#define UNICOMMI2CC_SR_ARBLST_OFS                (4)                             /* !< ARBLST Offset */
#define UNICOMMI2CC_SR_ARBLST_MASK               ((uint32_t)0x00000010U)         /* !< Arbitration Lost */
#define UNICOMMI2CC_SR_ARBLST_CLEARED            ((uint32_t)0x00000000U)         /* !< The I2C controller won arbitration. */
#define UNICOMMI2CC_SR_ARBLST_SET                ((uint32_t)0x00000010U)         /* !< The I2C controller lost
                                                                                    arbitration. */
/* UNICOMMI2CC_SR[IDLE] Bits */
#define UNICOMMI2CC_SR_IDLE_OFS                  (5)                             /* !< IDLE Offset */
#define UNICOMMI2CC_SR_IDLE_MASK                 ((uint32_t)0x00000020U)         /* !< I2C Idle */
#define UNICOMMI2CC_SR_IDLE_CLEARED              ((uint32_t)0x00000000U)         /* !< The I2C controller is not idle. */
#define UNICOMMI2CC_SR_IDLE_SET                  ((uint32_t)0x00000020U)         /* !< The I2C controller is idle. */
/* UNICOMMI2CC_SR[BUSBSY] Bits */
#define UNICOMMI2CC_SR_BUSBSY_OFS                (6)                             /* !< BUSBSY Offset */
#define UNICOMMI2CC_SR_BUSBSY_MASK               ((uint32_t)0x00000040U)         /* !< I2C Bus is Busy Controller State
                                                                                    Machine will wait until this bit to
                                                                                    be cleared before starting a
                                                                                    transaction. When first enabling the
                                                                                    Controller in multi Controller
                                                                                    environments, FW should wait for one
                                                                                    I2C clock period after setting ACTIVE
                                                                                    high before writing to the CTR
                                                                                    register to start the transaction so
                                                                                    that if SCL goes low it will trigger
                                                                                    the BUSBSY. */
#define UNICOMMI2CC_SR_BUSBSY_CLEARED            ((uint32_t)0x00000000U)         /* !< The I2C bus is idle. */
#define UNICOMMI2CC_SR_BUSBSY_SET                ((uint32_t)0x00000040U)         /* !< 'This Status bit is set on a START
                                                                                    or when SCL goes low. It is cleared
                                                                                    on a STOP,  or when a SCL high bus
                                                                                    busy timeout occurs and SCL and SDA
                                                                                    are both high. This status is cleared
                                                                                    when the ACTIVE bit is low.   Note
                                                                                    that the Controller State Machine
                                                                                    will wait until this bit is cleared
                                                                                    before starting an I2C transaction.
                                                                                    When first enabling the Controller in
                                                                                    multi Controller environments, FW
                                                                                    should wait for one I2C clock period
                                                                                    after setting ACTIVE high before
                                                                                    writing to the MTCR register to start
                                                                                    the transaction so that if SCL goes
                                                                                    low it will trigger the BUSBSY. */
/* UNICOMMI2CC_SR[BCNT] Bits */
#define UNICOMMI2CC_SR_BCNT_OFS                  (16)                            /* !< BCNT Offset */
#define UNICOMMI2CC_SR_BCNT_MASK                 ((uint32_t)0x0FFF0000U)         /* !< transaction count */
#define UNICOMMI2CC_SR_BCNT_MINIMUM              ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMI2CC_SR_BCNT_MAXIMUM              ((uint32_t)0x0FFF0000U)         /* !< Highest possible value */
/* UNICOMMI2CC_SR[RXCLR] Bits */
#define UNICOMMI2CC_SR_RXCLR_OFS                 (9)                             /* !< RXCLR Offset */
#define UNICOMMI2CC_SR_RXCLR_MASK                ((uint32_t)0x00000200U)         /* !< RX FIFO Clear Status */
#define UNICOMMI2CC_SR_RXCLR_CLEARED             ((uint32_t)0x00000000U)         /* !< FIFO is not cleared */
#define UNICOMMI2CC_SR_RXCLR_SET                 ((uint32_t)0x00000200U)         /* !< FIFO clear is complete */
/* UNICOMMI2CC_SR[TXCLR] Bits */
#define UNICOMMI2CC_SR_TXCLR_OFS                 (10)                            /* !< TXCLR Offset */
#define UNICOMMI2CC_SR_TXCLR_MASK                ((uint32_t)0x00000400U)         /* !< TX FIFO Clear Status */
#define UNICOMMI2CC_SR_TXCLR_CLEARED             ((uint32_t)0x00000000U)         /* !< FIFO is not cleared */
#define UNICOMMI2CC_SR_TXCLR_SET                 ((uint32_t)0x00000400U)         /* !< FIFO clear is complete */
/* UNICOMMI2CC_SR[RXFE] Bits */
#define UNICOMMI2CC_SR_RXFE_OFS                  (11)                            /* !< RXFE Offset */
#define UNICOMMI2CC_SR_RXFE_MASK                 ((uint32_t)0x00000800U)         /* !< Receive FIFO Empty  The meaning of
                                                                                    this bit depends on the state of the
                                                                                    FEN bit in the CTL0 register. */
#define UNICOMMI2CC_SR_RXFE_CLEARED              ((uint32_t)0x00000000U)         /* !< The receiver is not empty. */
#define UNICOMMI2CC_SR_RXFE_SET                  ((uint32_t)0x00000800U)         /* !< If the FIFO is disabled (FEN is 0),
                                                                                    the receive holding register is
                                                                                    empty. If the FIFO is enabled (FEN is
                                                                                    1), the receive FIFO is empty. */
/* UNICOMMI2CC_SR[RXFF] Bits */
#define UNICOMMI2CC_SR_RXFF_OFS                  (12)                            /* !< RXFF Offset */
#define UNICOMMI2CC_SR_RXFF_MASK                 ((uint32_t)0x00001000U)         /* !< Receive FIFO Full  The meaning of
                                                                                    this bit depends on the state of the
                                                                                    FEN bit in the CTL0 register. */
#define UNICOMMI2CC_SR_RXFF_CLEARED              ((uint32_t)0x00000000U)         /* !< The receiver can receive data. */
#define UNICOMMI2CC_SR_RXFF_SET                  ((uint32_t)0x00001000U)         /* !< If the FIFO is disabled (FEN is 0),
                                                                                    the receive holding register is full.
                                                                                    If the FIFO is enabled (FEN is 1),
                                                                                    the receive FIFO is full. */
/* UNICOMMI2CC_SR[TXFE] Bits */
#define UNICOMMI2CC_SR_TXFE_OFS                  (13)                            /* !< TXFE Offset */
#define UNICOMMI2CC_SR_TXFE_MASK                 ((uint32_t)0x00002000U)         /* !< Transmit FIFO Empty  The meaning of
                                                                                    this bit depends on the state of the
                                                                                    FEN bit in the CTL0 register. */
#define UNICOMMI2CC_SR_TXFE_CLEARED              ((uint32_t)0x00000000U)         /* !< The transmitter has data to
                                                                                    transmit. */
#define UNICOMMI2CC_SR_TXFE_SET                  ((uint32_t)0x00002000U)         /* !< If the FIFO is disabled (FEN is 0),
                                                                                    the transmit holding register is
                                                                                    empty. If the FIFO is enabled (FEN is
                                                                                    1), the transmit FIFO is empty. */
/* UNICOMMI2CC_SR[TXFF] Bits */
#define UNICOMMI2CC_SR_TXFF_OFS                  (14)                            /* !< TXFF Offset */
#define UNICOMMI2CC_SR_TXFF_MASK                 ((uint32_t)0x00004000U)         /* !< Transmit FIFO Full  The meaning of
                                                                                    this bit depends on the state of the
                                                                                    FEN bit in the CTL0 register. */
#define UNICOMMI2CC_SR_TXFF_CLEARED              ((uint32_t)0x00000000U)         /* !< The transmitter is not full. */
#define UNICOMMI2CC_SR_TXFF_SET                  ((uint32_t)0x00004000U)         /* !< If the FIFO is disabled (FEN is 0),
                                                                                    the transmit holding register is
                                                                                    full. If the FIFO is enabled (FEN is
                                                                                    1), the transmit FIFO is full. */

/* UNICOMMI2CC_IFLS Bits */
/* UNICOMMI2CC_IFLS[TXIFLSEL] Bits */
#define UNICOMMI2CC_IFLS_TXIFLSEL_OFS            (0)                             /* !< TXIFLSEL Offset */
#define UNICOMMI2CC_IFLS_TXIFLSEL_MASK           ((uint32_t)0x00000007U)         /* !< FIFO Level Select for generating
                                                                                    events (interrupt/dma).  Note: for
                                                                                    undefined settings the default
                                                                                    configuration is used. */
#define UNICOMMI2CC_IFLS_TXIFLSEL_LVL_3_4        ((uint32_t)0x00000001U)         /* !< TX FIFO <= 3/4 empty */
#define UNICOMMI2CC_IFLS_TXIFLSEL_LVL_1_2        ((uint32_t)0x00000002U)         /* !< TX FIFO <= 1/2 empty (default) */
#define UNICOMMI2CC_IFLS_TXIFLSEL_LVL_1_4        ((uint32_t)0x00000003U)         /* !< TX FIFO <= 1/4 empty */
#define UNICOMMI2CC_IFLS_TXIFLSEL_LVL_NOT_FULL   ((uint32_t)0x00000004U)         /* !< Opposite of full */
#define UNICOMMI2CC_IFLS_TXIFLSEL_LVL_EMPTY      ((uint32_t)0x00000005U)         /* !< TX FIFO is empty */
#define UNICOMMI2CC_IFLS_TXIFLSEL_LVL_ALMOST_EMPTY ((uint32_t)0x00000006U)         /* !< TX FIFO <= 1 */
#define UNICOMMI2CC_IFLS_TXIFLSEL_LVL_ALMOST_FULL ((uint32_t)0x00000007U)         /* !< TX_FIFO >= (MAX_FIFO_LEN -1) */
/* UNICOMMI2CC_IFLS[RXIFLSEL] Bits */
#define UNICOMMI2CC_IFLS_RXIFLSEL_OFS            (4)                             /* !< RXIFLSEL Offset */
#define UNICOMMI2CC_IFLS_RXIFLSEL_MASK           ((uint32_t)0x00000070U)         /* !< FIFO Level Select for generating
                                                                                    events (interrupt/dma).  Note: for
                                                                                    undefined settings the default
                                                                                    configuration is used. */
#define UNICOMMI2CC_IFLS_RXIFLSEL_LVL_1_4        ((uint32_t)0x00000010U)         /* !< RX FIFO >= 1/4 full */
#define UNICOMMI2CC_IFLS_RXIFLSEL_LVL_1_2        ((uint32_t)0x00000020U)         /* !< RX FIFO >= 1/2 full (default) */
#define UNICOMMI2CC_IFLS_RXIFLSEL_LVL_3_4        ((uint32_t)0x00000030U)         /* !< RX FIFO >= 3/4 full */
#define UNICOMMI2CC_IFLS_RXIFLSEL_LVL_NOT_EMPTY  ((uint32_t)0x00000040U)         /* !< Opposite of empty */
#define UNICOMMI2CC_IFLS_RXIFLSEL_LVL_FULL       ((uint32_t)0x00000050U)         /* !< RX FIFO is full */
#define UNICOMMI2CC_IFLS_RXIFLSEL_LVL_ALMOST_FULL ((uint32_t)0x00000060U)         /* !< RX_FIFO >= (MAX_FIFO_LEN -1) */
#define UNICOMMI2CC_IFLS_RXIFLSEL_LVL_ALMOST_EMPTY ((uint32_t)0x00000070U)         /* !< RX_FIFO <= 1 */
/* UNICOMMI2CC_IFLS[TXCLR] Bits */
#define UNICOMMI2CC_IFLS_TXCLR_OFS               (3)                             /* !< TXCLR Offset */
#define UNICOMMI2CC_IFLS_TXCLR_MASK              ((uint32_t)0x00000008U)         /* !< RX FIFO Flush */
#define UNICOMMI2CC_IFLS_TXCLR_DISABLE           ((uint32_t)0x00000000U)         /* !< Disable FIFO clear */
#define UNICOMMI2CC_IFLS_TXCLR_ENABLE            ((uint32_t)0x00000008U)         /* !< Enable FIFO Clear */
/* UNICOMMI2CC_IFLS[RXCLR] Bits */
#define UNICOMMI2CC_IFLS_RXCLR_OFS               (7)                             /* !< RXCLR Offset */
#define UNICOMMI2CC_IFLS_RXCLR_MASK              ((uint32_t)0x00000080U)         /* !< RX FIFO CLEAR */
#define UNICOMMI2CC_IFLS_RXCLR_DISABLE           ((uint32_t)0x00000000U)         /* !< Disable FIFO clear */
#define UNICOMMI2CC_IFLS_RXCLR_ENABLE            ((uint32_t)0x00000080U)         /* !< Enable FIFO Clear */

/* UNICOMMI2CC_TPR Bits */
/* UNICOMMI2CC_TPR[TPR] Bits */
#define UNICOMMI2CC_TPR_TPR_OFS                  (0)                             /* !< TPR Offset */
#define UNICOMMI2CC_TPR_TPR_MASK                 ((uint32_t)0x0000007FU)         /* !< Timer Period  This field is used in
                                                                                    the equation to configure SCL_PERIOD
                                                                                    : SCL_PERIOD = (1 + TPR ) * (SCL_LP +
                                                                                    SCL_HP ) * INT_CLK_PRD where:
                                                                                    SCL_PRD is the SCL line period (I2C
                                                                                    clock).   TPR is the Timer Period
                                                                                    register value (range of 1 to 127).
                                                                                    SCL_LP is the SCL Low period (fixed
                                                                                    at 6).   SCL_HP is the SCL High
                                                                                    period (fixed at 4).   CLK_PRD is the
                                                                                    functional clock period in ns. */
#define UNICOMMI2CC_TPR_TPR_MINIMUM              ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMI2CC_TPR_TPR_MAXIMUM              ((uint32_t)0x0000007FU)         /* !< Highest possible value */

/* UNICOMMI2CC_GFCTL Bits */
/* UNICOMMI2CC_GFCTL[DGFSEL] Bits */
#define UNICOMMI2CC_GFCTL_DGFSEL_OFS             (0)                             /* !< DGFSEL Offset */
#define UNICOMMI2CC_GFCTL_DGFSEL_MASK            ((uint32_t)0x00000007U)         /* !< Glitch Suppression Pulse Width
                                                                                    This field controls the pulse width
                                                                                    select for glitch suppression on the
                                                                                    SCL and SDA lines. The following
                                                                                    values are the glitch suppression
                                                                                    values in terms of functional clocks.
                                                                                    (Core Domain only) */
#define UNICOMMI2CC_GFCTL_DGFSEL_DISABLED        ((uint32_t)0x00000000U)         /* !< Bypass */
#define UNICOMMI2CC_GFCTL_DGFSEL_CLK_1           ((uint32_t)0x00000001U)         /* !< 1 clock */
#define UNICOMMI2CC_GFCTL_DGFSEL_CLK_2           ((uint32_t)0x00000002U)         /* !< 2 clocks */
#define UNICOMMI2CC_GFCTL_DGFSEL_CLK_3           ((uint32_t)0x00000003U)         /* !< 3 clocks */
#define UNICOMMI2CC_GFCTL_DGFSEL_CLK_4           ((uint32_t)0x00000004U)         /* !< 4 clocks */
#define UNICOMMI2CC_GFCTL_DGFSEL_CLK_8           ((uint32_t)0x00000005U)         /* !< 8 clocks */
#define UNICOMMI2CC_GFCTL_DGFSEL_CLK_16          ((uint32_t)0x00000006U)         /* !< 16 clocks */
#define UNICOMMI2CC_GFCTL_DGFSEL_CLK_31          ((uint32_t)0x00000007U)         /* !< 31 clocks */
/* UNICOMMI2CC_GFCTL[AGFEN] Bits */
#define UNICOMMI2CC_GFCTL_AGFEN_OFS              (8)                             /* !< AGFEN Offset */
#define UNICOMMI2CC_GFCTL_AGFEN_MASK             ((uint32_t)0x00000100U)         /* !< Analog Glitch Suppression Enable */
#define UNICOMMI2CC_GFCTL_AGFEN_DISABLE          ((uint32_t)0x00000000U)         /* !< Analog Glitch Filter disable */
#define UNICOMMI2CC_GFCTL_AGFEN_ENABLE           ((uint32_t)0x00000100U)         /* !< Analog Glitch Filter enable */

/* UNICOMMI2CC_BMON Bits */
/* UNICOMMI2CC_BMON[SCL] Bits */
#define UNICOMMI2CC_BMON_SCL_OFS                 (0)                             /* !< SCL Offset */
#define UNICOMMI2CC_BMON_SCL_MASK                ((uint32_t)0x00000001U)         /* !< I2C SCL Status */
#define UNICOMMI2CC_BMON_SCL_CLEARED             ((uint32_t)0x00000000U)         /* !< The I2CSCL signal is low. */
#define UNICOMMI2CC_BMON_SCL_SET                 ((uint32_t)0x00000001U)         /* !< The I2CSCL signal is high. Note:
                                                                                    During and right after reset, the SCL
                                                                                    pin is in GPIO input mode without the
                                                                                    internal pull enabled. For proper I2C
                                                                                    operation, the user should have the
                                                                                    external pull-up resistor in place
                                                                                    before starting any I2C operations. */
/* UNICOMMI2CC_BMON[SDA] Bits */
#define UNICOMMI2CC_BMON_SDA_OFS                 (1)                             /* !< SDA Offset */
#define UNICOMMI2CC_BMON_SDA_MASK                ((uint32_t)0x00000002U)         /* !< I2C SDA Status */
#define UNICOMMI2CC_BMON_SDA_CLEARED             ((uint32_t)0x00000000U)         /* !< The I2CSDA signal is low. */
#define UNICOMMI2CC_BMON_SDA_SET                 ((uint32_t)0x00000002U)         /* !< The I2CSDA signal is high. Note:
                                                                                    During and right after reset, the SDA
                                                                                    pin is in GPIO input mode without the
                                                                                    internal pull enabled. For proper I2C
                                                                                    operation, the user should have the
                                                                                    external pull-up resistor in place
                                                                                    before starting any I2C operations. */

/* UNICOMMI2CC_TXDATA Bits */
/* UNICOMMI2CC_TXDATA[DATA] Bits */
#define UNICOMMI2CC_TXDATA_DATA_OFS              (0)                             /* !< DATA Offset */
#define UNICOMMI2CC_TXDATA_DATA_MASK             ((uint32_t)0x000000FFU)         /* !< Transmit Data This byte contains
                                                                                    the data to be transferred during the
                                                                                    next transaction. */
#define UNICOMMI2CC_TXDATA_DATA_MINIMUM          ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMI2CC_TXDATA_DATA_MAXIMUM          ((uint32_t)0x000000FFU)         /* !< Highest possible value */

/* UNICOMMI2CC_RXDATA Bits */
/* UNICOMMI2CC_RXDATA[DATA] Bits */
#define UNICOMMI2CC_RXDATA_DATA_OFS              (0)                             /* !< DATA Offset */
#define UNICOMMI2CC_RXDATA_DATA_MASK             ((uint32_t)0x000000FFU)         /* !< Received Data.  This field contains
                                                                                    the last received data. */
#define UNICOMMI2CC_RXDATA_DATA_MINIMUM          ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMI2CC_RXDATA_DATA_MAXIMUM          ((uint32_t)0x000000FFU)         /* !< Highest possible value */

/* UNICOMMI2CC_PECSR Bits */
/* UNICOMMI2CC_PECSR[PECBYTECNT] Bits */
#define UNICOMMI2CC_PECSR_PECBYTECNT_OFS         (0)                             /* !< PECBYTECNT Offset */
#define UNICOMMI2CC_PECSR_PECBYTECNT_MASK        ((uint32_t)0x000001FFU)         /* !< PEC Current Count */
#define UNICOMMI2CC_PECSR_PECBYTECNT_MINIMUM     ((uint32_t)0x00000000U)         /* !< Minimum Value */
#define UNICOMMI2CC_PECSR_PECBYTECNT_MAXIMUM     ((uint32_t)0x000001FFU)         /* !< Maximum Value */
/* UNICOMMI2CC_PECSR[PECSTS_CHECK] Bits */
#define UNICOMMI2CC_PECSR_PECSTS_CHECK_OFS       (16)                            /* !< PECSTS_CHECK Offset */
#define UNICOMMI2CC_PECSR_PECSTS_CHECK_MASK      ((uint32_t)0x00010000U)         /* !< PEC Check Status */
#define UNICOMMI2CC_PECSR_PECSTS_CHECK_CLEARED   ((uint32_t)0x00000000U)         /* !< Indicates PEC was not checked in
                                                                                    the transaction that occurred before
                                                                                    the last Stop */
#define UNICOMMI2CC_PECSR_PECSTS_CHECK_SET       ((uint32_t)0x00010000U)         /* !< Indicates if the PEC was checked in
                                                                                    the transaction that occurred before
                                                                                    the last Stop */
/* UNICOMMI2CC_PECSR[PECSTS_ERROR] Bits */
#define UNICOMMI2CC_PECSR_PECSTS_ERROR_OFS       (17)                            /* !< PECSTS_ERROR Offset */
#define UNICOMMI2CC_PECSR_PECSTS_ERROR_MASK      ((uint32_t)0x00020000U)         /* !< PEC Error Status */
#define UNICOMMI2CC_PECSR_PECSTS_ERROR_CLEARED   ((uint32_t)0x00000000U)         /* !< Indicates PEC check error did not
                                                                                    occurr in the transaction that
                                                                                    occurred before the last Stop */
#define UNICOMMI2CC_PECSR_PECSTS_ERROR_SET       ((uint32_t)0x00020000U)         /* !< Indicates if a PEC check error
                                                                                    occurred in the transaction that
                                                                                    occurred before the last Stop */

/* UNICOMMI2CC_TA Bits */
/* UNICOMMI2CC_TA[DIR] Bits */
#define UNICOMMI2CC_TA_DIR_OFS                   (0)                             /* !< DIR Offset */
#define UNICOMMI2CC_TA_DIR_MASK                  ((uint32_t)0x00000001U)         /* !< Receive/Send The DIR bit specifies
                                                                                    if the next operation is a Receive
                                                                                    (High) or Transmit (Low). 0h =
                                                                                    Transmit 1h = Receive */
#define UNICOMMI2CC_TA_DIR_TRANSMIT              ((uint32_t)0x00000000U)         /* !< in transmit mode. */
#define UNICOMMI2CC_TA_DIR_RECEIVE               ((uint32_t)0x00000001U)         /* !< is in receive mode. */
/* UNICOMMI2CC_TA[ADDR] Bits */
#define UNICOMMI2CC_TA_ADDR_OFS                  (1)                             /* !< ADDR Offset */
#define UNICOMMI2CC_TA_ADDR_MASK                 ((uint32_t)0x000007FEU)         /* !< Target Address */
#define UNICOMMI2CC_TA_ADDR_MINIMUM              ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMI2CC_TA_ADDR_MAXIMUM              ((uint32_t)0x000007FEU)         /* !< Highest possible value */
/* UNICOMMI2CC_TA[MODE] Bits */
#define UNICOMMI2CC_TA_MODE_OFS                  (15)                            /* !< MODE Offset */
#define UNICOMMI2CC_TA_MODE_MASK                 ((uint32_t)0x00008000U)         /* !< Addressing Mode */
#define UNICOMMI2CC_TA_MODE_MODE7                ((uint32_t)0x00000000U)         /* !< 7-bit addressing mode */
#define UNICOMMI2CC_TA_MODE_MODE10               ((uint32_t)0x00008000U)         /* !< 10-bit addressing mode */

/* UNICOMMI2CC_TIMEOUT_CNT Bits */
/* UNICOMMI2CC_TIMEOUT_CNT[TCNTA] Bits */
#define UNICOMMI2CC_TIMEOUT_CNT_TCNTA_OFS        (0)                             /* !< TCNTA Offset */
#define UNICOMMI2CC_TIMEOUT_CNT_TCNTA_MASK       ((uint32_t)0x000000FFU)         /* !< Timeout Count A Current Count: This
                                                                                    field contains the upper 8 bits of a
                                                                                    12-bit current counter for timeout
                                                                                    counter A */
#define UNICOMMI2CC_TIMEOUT_CNT_TCNTA_MINIMUM    ((uint32_t)0x00000000U)         /* !< Smallest Value */
#define UNICOMMI2CC_TIMEOUT_CNT_TCNTA_MAXIMUM    ((uint32_t)0x000000FFU)         /* !< Highest possible value */
/* UNICOMMI2CC_TIMEOUT_CNT[TCNTB] Bits */
#define UNICOMMI2CC_TIMEOUT_CNT_TCNTB_OFS        (16)                            /* !< TCNTB Offset */
#define UNICOMMI2CC_TIMEOUT_CNT_TCNTB_MASK       ((uint32_t)0x00FF0000U)         /* !< Timeout Count B Current Count: This
                                                                                    field contains the upper 8 bits of a
                                                                                    12-bit current counter for timeout
                                                                                    counter B */
#define UNICOMMI2CC_TIMEOUT_CNT_TCNTB_MINIMUM    ((uint32_t)0x00000000U)         /* !< Smallest Value */
#define UNICOMMI2CC_TIMEOUT_CNT_TCNTB_MAXIMUM    ((uint32_t)0x00FF0000U)         /* !< Highest possible value */

/* UNICOMMI2CC_TIMEOUT_CTL Bits */
/* UNICOMMI2CC_TIMEOUT_CTL[TCNTLA] Bits */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTLA_OFS       (0)                             /* !< TCNTLA Offset */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTLA_MASK      ((uint32_t)0x000000FFU)         /* !< Timeout counter A load value
                                                                                    Counter A is used for SCL low
                                                                                    detection. This field contains the
                                                                                    upper 8 bits of a 12-bit pre-load
                                                                                    value for the Timeout A count. NOTE:
                                                                                    The value of CNTLA must be greater
                                                                                    than 1h.   Each count is equal to 520
                                                                                    times the timeout period of
                                                                                    functional clock. For example, with
                                                                                    8MHz functional clock and a 100KHz
                                                                                    operating I2C clock, one timeout
                                                                                    period will be equal to (1 / 8MHz) *
                                                                                    520 or 65 us. */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTLA_MINIMUM   ((uint32_t)0x00000000U)         /* !< Smallest Value */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTLA_MAXIMUM   ((uint32_t)0x000000FFU)         /* !< Highest possible value */
/* UNICOMMI2CC_TIMEOUT_CTL[TCNTAEN] Bits */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTAEN_OFS      (15)                            /* !< TCNTAEN Offset */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTAEN_MASK     ((uint32_t)0x00008000U)         /* !< Timeout Counter A Enable */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTAEN_DISABLE  ((uint32_t)0x00000000U)         /* !< Disable Timeout Counter B */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTAEN_ENABLE   ((uint32_t)0x00008000U)         /* !< Enable Timeout Counter B */
/* UNICOMMI2CC_TIMEOUT_CTL[TCNTLB] Bits */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTLB_OFS       (16)                            /* !< TCNTLB Offset */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTLB_MASK      ((uint32_t)0x00FF0000U)         /* !< Timeout Count B Load: Counter B is
                                                                                    used for SCL High Detection. This
                                                                                    field contains the upper 8 bits of a
                                                                                    12-bit pre-load value for the Timeout
                                                                                    B count. NOTE: The value of CNTLB
                                                                                    must be greater than 1h.   Each count
                                                                                    is equal to 1* clock period. For
                                                                                    example, with 10MHz functional clock
                                                                                    one timeout period will be equal
                                                                                    to1*100ns. */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTLB_MINIMUM   ((uint32_t)0x00000000U)         /* !< Smallest possible value */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTLB_MAXIMUM   ((uint32_t)0x00FF0000U)         /* !< Highest possible value */
/* UNICOMMI2CC_TIMEOUT_CTL[TCNTBEN] Bits */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTBEN_OFS      (31)                            /* !< TCNTBEN Offset */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTBEN_MASK     ((uint32_t)0x80000000U)         /* !< Timeout Counter B Enable */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTBEN_DISABLE  ((uint32_t)0x00000000U)         /* !< Disable Timeout Counter B */
#define UNICOMMI2CC_TIMEOUT_CTL_TCNTBEN_ENABLE   ((uint32_t)0x80000000U)         /* !< Enable Timeout Counter B */

/* UNICOMMI2CC_PECCTL Bits */
/* UNICOMMI2CC_PECCTL[PECCNT] Bits */
#define UNICOMMI2CC_PECCTL_PECCNT_OFS            (0)                             /* !< PECCNT Offset */
#define UNICOMMI2CC_PECCTL_PECCNT_MASK           ((uint32_t)0x000001FFU)         /* !< PEC Count */
#define UNICOMMI2CC_PECCTL_PECCNT_MINIMUM        ((uint32_t)0x00000000U)         /* !< Minimum Value */
#define UNICOMMI2CC_PECCTL_PECCNT_MAXIMUM        ((uint32_t)0x000001FFU)         /* !< Maximum Value */
/* UNICOMMI2CC_PECCTL[PECEN] Bits */
#define UNICOMMI2CC_PECCTL_PECEN_OFS             (12)                            /* !< PECEN Offset */
#define UNICOMMI2CC_PECCTL_PECEN_MASK            ((uint32_t)0x00001000U)         /* !< PEC Enable */
#define UNICOMMI2CC_PECCTL_PECEN_DISABLE         ((uint32_t)0x00000000U)         /* !< PEC is disabled */
#define UNICOMMI2CC_PECCTL_PECEN_ENABLE          ((uint32_t)0x00001000U)         /* !< PEC is enabled */


#ifdef __cplusplus
}
#endif

#endif /* hw_unicommi2cc__include */
