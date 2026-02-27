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

#ifndef hw_unicommspi__include
#define hw_unicommspi__include


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
* UNICOMMSPI Registers
******************************************************************************/
#define UNICOMMSPI_DMA_TRIG_TX_OFS               ((uint32_t)0x00000080U)
#define UNICOMMSPI_DMA_TRIG_RX_OFS               ((uint32_t)0x00000050U)
#define UNICOMMSPI_CPU_INT_OFS                   ((uint32_t)0x00000020U)


/** @addtogroup UNICOMMSPI_DMA_TRIG_TX
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
} UNICOMMSPI_DMA_TRIG_TX_Regs;

/*@}*/ /* end of group UNICOMMSPI_DMA_TRIG_TX */

/** @addtogroup UNICOMMSPI_DMA_TRIG_RX
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
} UNICOMMSPI_DMA_TRIG_RX_Regs;

/*@}*/ /* end of group UNICOMMSPI_DMA_TRIG_RX */

/** @addtogroup UNICOMMSPI_CPU_INT
  @{
*/

typedef struct {
  __I  uint32_t IIDX;                              /* !< (@ 0x00000020) Interrupt Index Register */
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
} UNICOMMSPI_CPU_INT_Regs;

/*@}*/ /* end of group UNICOMMSPI_CPU_INT */

/** @addtogroup UNICOMMSPI
  @{
*/

typedef struct {
  __IO uint32_t CLKDIV;                            /* !< (@ 0x00000000) Clock Divider */
       uint32_t RESERVED0;
  __IO uint32_t CLKSEL;                            /* !< (@ 0x00000008) Clock Select for Ultra Low Power peripherals */
       uint32_t RESERVED1[3];
  __IO uint32_t PDBGCTL;                           /* !< (@ 0x00000018) Peripheral Debug Control */
       uint32_t RESERVED2;
  UNICOMMSPI_CPU_INT_Regs  CPU_INT;                           /* !< (@ 0x00000020) */
       uint32_t RESERVED3;
  UNICOMMSPI_DMA_TRIG_RX_Regs  DMA_TRIG_RX;                       /* !< (@ 0x00000050) */
       uint32_t RESERVED4[3];
  UNICOMMSPI_DMA_TRIG_TX_Regs  DMA_TRIG_TX;                       /* !< (@ 0x00000080) */
       uint32_t RESERVED5[16];
  __O  uint32_t INTCTL;                            /* !< (@ 0x000000E4) Interrupt control register */
       uint32_t RESERVED6[6];
  __IO uint32_t CTL0;                              /* !< (@ 0x00000100) SPI control register 0 */
       uint32_t RESERVED7;
  __I  uint32_t STAT;                              /* !< (@ 0x00000108) Status Register */
  __IO uint32_t IFLS;                              /* !< (@ 0x0000010C) Interrupt FIFO Level Select Register */
  __IO uint32_t CLKCTL;                            /* !< (@ 0x00000110) Clock prescaler and divider register. */
       uint32_t RESERVED8[3];
  __O  uint32_t TXDATA;                            /* !< (@ 0x00000120) TXDATA Register */
  __I  uint32_t RXDATA;                            /* !< (@ 0x00000124) RXDATA Register */
       uint32_t RESERVED9[9];
  __IO uint32_t CTL1;                              /* !< (@ 0x0000014C) SPI control register 1 */
} UNICOMMSPI_Regs;

/*@}*/ /* end of group UNICOMMSPI */



/******************************************************************************
* UNICOMMSPI Register Offsets
******************************************************************************/
#define UNICOMMSPI_CLKDIV                        (0x00000000U)
#define UNICOMMSPI_CLKSEL                        (0x00000008U)
#define UNICOMMSPI_PDBGCTL                       (0x00000018U)
#define UNICOMMSPI_INTCTL                        (0x000000E4U)
#define UNICOMMSPI_CTL0                          (0x00000100U)
#define UNICOMMSPI_STAT                          (0x00000108U)
#define UNICOMMSPI_IFLS                          (0x0000010CU)
#define UNICOMMSPI_CLKCTL                        (0x00000110U)
#define UNICOMMSPI_TXDATA                        (0x00000120U)
#define UNICOMMSPI_RXDATA                        (0x00000124U)
#define UNICOMMSPI_CTL1                          (0x0000014CU)

#define UNICOMMSPI_IIDX                          (0x00000020U)
#define UNICOMMSPI_CPU_INT_IMASK                 (0x00000028U)
#define UNICOMMSPI_CPU_INT_RIS                   (0x00000030U)
#define UNICOMMSPI_CPU_INT_MIS                   (0x00000038U)
#define UNICOMMSPI_CPU_INT_ISET                  (0x00000040U)
#define UNICOMMSPI_ICLR                          (0x00000048U)

#define UNICOMMSPI_DMA_TRIG_RX_IMASK             (0x00000058U)
#define UNICOMMSPI_DMA_TRIG_RX_RIS               (0x00000060U)
#define UNICOMMSPI_DMA_TRIG_RX_MIS               (0x00000068U)
#define UNICOMMSPI_DMA_TRIG_RX_ISET              (0x00000070U)

#define UNICOMMSPI_DMA_TRIG_TX_IMASK             (0x00000088U)
#define UNICOMMSPI_DMA_TRIG_TX_RIS               (0x00000090U)
#define UNICOMMSPI_DMA_TRIG_TX_MIS               (0x00000098U)
#define UNICOMMSPI_DMA_TRIG_TX_ISET              (0x000000A0U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* UNICOMMSPI Register Control Bits
******************************************************************************/

/* UNICOMMSPI_DMA_TRIG_TX_IMASK Bits */
/* UNICOMMSPI_DMA_TRIG_TX_IMASK[TX] Bits */
#define UNICOMMSPI_DMA_TRIG_TX_IMASK_TX_OFS      (5)                             /* !< TX Offset */
#define UNICOMMSPI_DMA_TRIG_TX_IMASK_TX_MASK     ((uint32_t)0x00000020U)         /* !< Transmit FIFO event */
#define UNICOMMSPI_DMA_TRIG_TX_IMASK_TX_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_DMA_TRIG_TX_IMASK_TX_SET      ((uint32_t)0x00000020U)         /* !< Set Interrupt Mask */

/* UNICOMMSPI_DMA_TRIG_TX_RIS Bits */
/* UNICOMMSPI_DMA_TRIG_TX_RIS[TX] Bits */
#define UNICOMMSPI_DMA_TRIG_TX_RIS_TX_OFS        (5)                             /* !< TX Offset */
#define UNICOMMSPI_DMA_TRIG_TX_RIS_TX_MASK       ((uint32_t)0x00000020U)         /* !< Transmit FIFO event */
#define UNICOMMSPI_DMA_TRIG_TX_RIS_TX_CLR        ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_DMA_TRIG_TX_RIS_TX_SET        ((uint32_t)0x00000020U)         /* !< Interrupt occurred */

/* UNICOMMSPI_DMA_TRIG_TX_MIS Bits */
/* UNICOMMSPI_DMA_TRIG_TX_MIS[TX] Bits */
#define UNICOMMSPI_DMA_TRIG_TX_MIS_TX_OFS        (5)                             /* !< TX Offset */
#define UNICOMMSPI_DMA_TRIG_TX_MIS_TX_MASK       ((uint32_t)0x00000020U)         /* !< Transmit FIFO event */
#define UNICOMMSPI_DMA_TRIG_TX_MIS_TX_CLR        ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_DMA_TRIG_TX_MIS_TX_SET        ((uint32_t)0x00000020U)         /* !< Interrupt occurred */

/* UNICOMMSPI_DMA_TRIG_TX_ISET Bits */
/* UNICOMMSPI_DMA_TRIG_TX_ISET[TX] Bits */
#define UNICOMMSPI_DMA_TRIG_TX_ISET_TX_OFS       (5)                             /* !< TX Offset */
#define UNICOMMSPI_DMA_TRIG_TX_ISET_TX_MASK      ((uint32_t)0x00000020U)         /* !< Transmit FIFO event */
#define UNICOMMSPI_DMA_TRIG_TX_ISET_TX_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_DMA_TRIG_TX_ISET_TX_SET       ((uint32_t)0x00000020U)         /* !< Set Interrupt */

/* UNICOMMSPI_DMA_TRIG_RX_IMASK Bits */
/* UNICOMMSPI_DMA_TRIG_RX_IMASK[RX] Bits */
#define UNICOMMSPI_DMA_TRIG_RX_IMASK_RX_OFS      (2)                             /* !< RX Offset */
#define UNICOMMSPI_DMA_TRIG_RX_IMASK_RX_MASK     ((uint32_t)0x00000004U)         /* !< Receive FIFO event */
#define UNICOMMSPI_DMA_TRIG_RX_IMASK_RX_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_DMA_TRIG_RX_IMASK_RX_SET      ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */

/* UNICOMMSPI_DMA_TRIG_RX_RIS Bits */
/* UNICOMMSPI_DMA_TRIG_RX_RIS[RX] Bits */
#define UNICOMMSPI_DMA_TRIG_RX_RIS_RX_OFS        (2)                             /* !< RX Offset */
#define UNICOMMSPI_DMA_TRIG_RX_RIS_RX_MASK       ((uint32_t)0x00000004U)         /* !< Receive FIFO event */
#define UNICOMMSPI_DMA_TRIG_RX_RIS_RX_CLR        ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_DMA_TRIG_RX_RIS_RX_SET        ((uint32_t)0x00000004U)         /* !< Interrupt occurred */

/* UNICOMMSPI_DMA_TRIG_RX_MIS Bits */
/* UNICOMMSPI_DMA_TRIG_RX_MIS[RX] Bits */
#define UNICOMMSPI_DMA_TRIG_RX_MIS_RX_OFS        (2)                             /* !< RX Offset */
#define UNICOMMSPI_DMA_TRIG_RX_MIS_RX_MASK       ((uint32_t)0x00000004U)         /* !< Receive FIFO event */
#define UNICOMMSPI_DMA_TRIG_RX_MIS_RX_CLR        ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_DMA_TRIG_RX_MIS_RX_SET        ((uint32_t)0x00000004U)         /* !< Interrupt occurred */

/* UNICOMMSPI_DMA_TRIG_RX_ISET Bits */
/* UNICOMMSPI_DMA_TRIG_RX_ISET[RX] Bits */
#define UNICOMMSPI_DMA_TRIG_RX_ISET_RX_OFS       (2)                             /* !< RX Offset */
#define UNICOMMSPI_DMA_TRIG_RX_ISET_RX_MASK      ((uint32_t)0x00000004U)         /* !< Receive FIFO event */
#define UNICOMMSPI_DMA_TRIG_RX_ISET_RX_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_DMA_TRIG_RX_ISET_RX_SET       ((uint32_t)0x00000004U)         /* !< Set Interrupt */

/* UNICOMMSPI_IIDX Bits */
/* UNICOMMSPI_IIDX[STAT] Bits */
#define UNICOMMSPI_IIDX_STAT_OFS                 (0)                             /* !< STAT Offset */
#define UNICOMMSPI_IIDX_STAT_MASK                ((uint32_t)0x000000FFU)         /* !< Interrupt index status */
#define UNICOMMSPI_IIDX_STAT_NO_INTR             ((uint32_t)0x00000000U)         /* !< No interrupt pending */
#define UNICOMMSPI_IIDX_STAT_PER_EVT             ((uint32_t)0x00000001U)         /* !< Transmit Parity Event/interrupt
                                                                                    pending */
#define UNICOMMSPI_IIDX_STAT_RXFIFO_OFV_EVT      ((uint32_t)0x00000002U)         /* !< RX FIFO Overflow Event/interrupt
                                                                                    pending */
#define UNICOMMSPI_IIDX_STAT_RX_EVT              ((uint32_t)0x00000003U)         /* !< Receive interrupt */
#define UNICOMMSPI_IIDX_STAT_RXFULL_EVT          ((uint32_t)0x00000004U)         /* !< RX FIFO Full Interrupt */
#define UNICOMMSPI_IIDX_STAT_TXFIFO_UNF_EVT      ((uint32_t)0x00000005U)         /* !< TX FIFO underflow interrupt */
#define UNICOMMSPI_IIDX_STAT_TX_EVT              ((uint32_t)0x00000006U)         /* !< Transmit Event */
#define UNICOMMSPI_IIDX_STAT_TX_EMPTY            ((uint32_t)0x00000007U)         /* !< Transmit Buffer Empty
                                                                                    Event/interrupt pending */
#define UNICOMMSPI_IIDX_STAT_IDLE_EVT            ((uint32_t)0x00000009U)         /* !< End of Transmit Event/interrupt
                                                                                    pending */
#define UNICOMMSPI_IIDX_STAT_RTOUT_EVT           ((uint32_t)0x0000000AU)         /* !< SPI receive time-out interrupt */
#define UNICOMMSPI_IIDX_STAT_DMA_DONE_RX         ((uint32_t)0x00000010U)         /* !< DMA DONE on RX */
#define UNICOMMSPI_IIDX_STAT_DMA_DONE_TX         ((uint32_t)0x00000011U)         /* !< DMA DONE on TX */
#define UNICOMMSPI_IIDX_STAT_DMA_PREIRQ_RX       ((uint32_t)0x00000013U)         /* !< DMA PRE IRQ RX INTERRUPT */
#define UNICOMMSPI_IIDX_STAT_DMA_PREIRQ_TX       ((uint32_t)0x00000014U)         /* !< DMA PRE IRQ TX INTERRUPT */
#define UNICOMMSPI_IIDX_STAT_LTOUT               ((uint32_t)0x00000015U)         /* !< SPI line time-out interrupt */

/* UNICOMMSPI_CPU_INT_IMASK Bits */
/* UNICOMMSPI_CPU_INT_IMASK[RX] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_RX_OFS          (2)                             /* !< RX Offset */
#define UNICOMMSPI_CPU_INT_IMASK_RX_MASK         ((uint32_t)0x00000004U)         /* !< Receive event. If FIFO is present,
                                                                                    this bit is set when the programmed
                                                                                    threshold is reached. When there is
                                                                                    no FIFO, this bit is set when a frame
                                                                                    is received */
#define UNICOMMSPI_CPU_INT_IMASK_RX_CLR          ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_RX_SET          ((uint32_t)0x00000004U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[TX] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_TX_OFS          (5)                             /* !< TX Offset */
#define UNICOMMSPI_CPU_INT_IMASK_TX_MASK         ((uint32_t)0x00000020U)         /* !< Transmit event. When FIFO is
                                                                                    present, this bit is set when FIFO
                                                                                    threshold is reached. When FIFO is
                                                                                    not used,  this bit is set when
                                                                                    transmit buffer is empty. */
#define UNICOMMSPI_CPU_INT_IMASK_TX_CLR          ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_TX_SET          ((uint32_t)0x00000020U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[TXEMPTY] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_TXEMPTY_OFS     (6)                             /* !< TXEMPTY Offset */
#define UNICOMMSPI_CPU_INT_IMASK_TXEMPTY_MASK    ((uint32_t)0x00000040U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMSPI_CPU_INT_IMASK_TXEMPTY_CLR     ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_TXEMPTY_SET     ((uint32_t)0x00000040U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[PER] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_PER_OFS         (0)                             /* !< PER Offset */
#define UNICOMMSPI_CPU_INT_IMASK_PER_MASK        ((uint32_t)0x00000001U)         /* !< Parity error event */
#define UNICOMMSPI_CPU_INT_IMASK_PER_CLR         ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_PER_SET         ((uint32_t)0x00000001U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[RXFIFO_OVF] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_RXFIFO_OVF_OFS  (1)                             /* !< RXFIFO_OVF Offset */
#define UNICOMMSPI_CPU_INT_IMASK_RXFIFO_OVF_MASK ((uint32_t)0x00000002U)         /* !< RXFIFO overflow event */
#define UNICOMMSPI_CPU_INT_IMASK_RXFIFO_OVF_CLR  ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_RXFIFO_OVF_SET  ((uint32_t)0x00000002U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[IDLE] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_IDLE_OFS        (8)                             /* !< IDLE Offset */
#define UNICOMMSPI_CPU_INT_IMASK_IDLE_MASK       ((uint32_t)0x00000100U)         /* !< SPI in Idle mode */
#define UNICOMMSPI_CPU_INT_IMASK_IDLE_CLR        ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_IDLE_SET        ((uint32_t)0x00000100U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[RXFULL] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_RXFULL_OFS      (3)                             /* !< RXFULL Offset */
#define UNICOMMSPI_CPU_INT_IMASK_RXFULL_MASK     ((uint32_t)0x00000008U)         /* !< RX FIFO Full Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_RXFULL_CLR      ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_RXFULL_SET      ((uint32_t)0x00000008U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[TXFIFO_UNF] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_TXFIFO_UNF_OFS  (4)                             /* !< TXFIFO_UNF Offset */
#define UNICOMMSPI_CPU_INT_IMASK_TXFIFO_UNF_MASK ((uint32_t)0x00000010U)         /* !< TX FIFO underflow interrupt mask */
#define UNICOMMSPI_CPU_INT_IMASK_TXFIFO_UNF_CLR  ((uint32_t)0x00000000U)         /* !< Clear Interrupt Mask */
#define UNICOMMSPI_CPU_INT_IMASK_TXFIFO_UNF_SET  ((uint32_t)0x00000010U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[DMA_DONE_RX] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_DMA_DONE_RX_OFS (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMSPI_CPU_INT_IMASK_DMA_DONE_RX_MASK ((uint32_t)0x00008000U)         /* !< Enable DMA Done on RX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_CPU_INT_IMASK_DMA_DONE_RX_CLR ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMSPI_CPU_INT_IMASK_DMA_DONE_RX_SET ((uint32_t)0x00008000U)         /* !< Set Interrupt Mask */
/* UNICOMMSPI_CPU_INT_IMASK[DMA_DONE_TX] Bits */
#define UNICOMMSPI_CPU_INT_IMASK_DMA_DONE_TX_OFS (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMSPI_CPU_INT_IMASK_DMA_DONE_TX_MASK ((uint32_t)0x00010000U)         /* !< Enable DMA Done on TX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_CPU_INT_IMASK_DMA_DONE_TX_CLR ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMSPI_CPU_INT_IMASK_DMA_DONE_TX_SET ((uint32_t)0x00010000U)         /* !< Set Interrupt Mask */

/* UNICOMMSPI_CPU_INT_RIS Bits */
/* UNICOMMSPI_CPU_INT_RIS[RX] Bits */
#define UNICOMMSPI_CPU_INT_RIS_RX_OFS            (2)                             /* !< RX Offset */
#define UNICOMMSPI_CPU_INT_RIS_RX_MASK           ((uint32_t)0x00000004U)         /* !< Receive event */
#define UNICOMMSPI_CPU_INT_RIS_RX_CLR            ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_RIS_RX_SET            ((uint32_t)0x00000004U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_RIS[TX] Bits */
#define UNICOMMSPI_CPU_INT_RIS_TX_OFS            (5)                             /* !< TX Offset */
#define UNICOMMSPI_CPU_INT_RIS_TX_MASK           ((uint32_t)0x00000020U)         /* !< Transmit Event */
#define UNICOMMSPI_CPU_INT_RIS_TX_CLR            ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_RIS_TX_SET            ((uint32_t)0x00000020U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_RIS[TXEMPTY] Bits */
#define UNICOMMSPI_CPU_INT_RIS_TXEMPTY_OFS       (6)                             /* !< TXEMPTY Offset */
#define UNICOMMSPI_CPU_INT_RIS_TXEMPTY_MASK      ((uint32_t)0x00000040U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMSPI_CPU_INT_RIS_TXEMPTY_CLR       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_RIS_TXEMPTY_SET       ((uint32_t)0x00000040U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_RIS[PER] Bits */
#define UNICOMMSPI_CPU_INT_RIS_PER_OFS           (0)                             /* !< PER Offset */
#define UNICOMMSPI_CPU_INT_RIS_PER_MASK          ((uint32_t)0x00000001U)         /* !< Parity error event */
#define UNICOMMSPI_CPU_INT_RIS_PER_CLR           ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_RIS_PER_SET           ((uint32_t)0x00000001U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_RIS[RXFIFO_OVF] Bits */
#define UNICOMMSPI_CPU_INT_RIS_RXFIFO_OVF_OFS    (1)                             /* !< RXFIFO_OVF Offset */
#define UNICOMMSPI_CPU_INT_RIS_RXFIFO_OVF_MASK   ((uint32_t)0x00000002U)         /* !< RXFIFO overflow event */
#define UNICOMMSPI_CPU_INT_RIS_RXFIFO_OVF_CLR    ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_RIS_RXFIFO_OVF_SET    ((uint32_t)0x00000002U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_RIS[IDLE] Bits */
#define UNICOMMSPI_CPU_INT_RIS_IDLE_OFS          (8)                             /* !< IDLE Offset */
#define UNICOMMSPI_CPU_INT_RIS_IDLE_MASK         ((uint32_t)0x00000100U)         /* !< SPI in Idle mode */
#define UNICOMMSPI_CPU_INT_RIS_IDLE_CLR          ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_RIS_IDLE_SET          ((uint32_t)0x00000100U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_RIS[TXFIFO_UNF] Bits */
#define UNICOMMSPI_CPU_INT_RIS_TXFIFO_UNF_OFS    (4)                             /* !< TXFIFO_UNF Offset */
#define UNICOMMSPI_CPU_INT_RIS_TXFIFO_UNF_MASK   ((uint32_t)0x00000010U)         /* !< TX FIFO Underflow Interrupt */
#define UNICOMMSPI_CPU_INT_RIS_TXFIFO_UNF_CLR    ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_RIS_TXFIFO_UNF_SET    ((uint32_t)0x00000010U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_RIS[RXFULL] Bits */
#define UNICOMMSPI_CPU_INT_RIS_RXFULL_OFS        (3)                             /* !< RXFULL Offset */
#define UNICOMMSPI_CPU_INT_RIS_RXFULL_MASK       ((uint32_t)0x00000008U)         /* !< RX FIFO Full Interrupt */
#define UNICOMMSPI_CPU_INT_RIS_RXFULL_CLR        ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_RIS_RXFULL_SET        ((uint32_t)0x00000008U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_RIS[DMA_DONE_RX] Bits */
#define UNICOMMSPI_CPU_INT_RIS_DMA_DONE_RX_OFS   (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMSPI_CPU_INT_RIS_DMA_DONE_RX_MASK  ((uint32_t)0x00008000U)         /* !< DMA Done on RX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_CPU_INT_RIS_DMA_DONE_RX_CLR   ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMSPI_CPU_INT_RIS_DMA_DONE_RX_SET   ((uint32_t)0x00008000U)         /* !< Interrupt occured */
/* UNICOMMSPI_CPU_INT_RIS[DMA_DONE_TX] Bits */
#define UNICOMMSPI_CPU_INT_RIS_DMA_DONE_TX_OFS   (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMSPI_CPU_INT_RIS_DMA_DONE_TX_MASK  ((uint32_t)0x00010000U)         /* !< DMA Done on TX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_CPU_INT_RIS_DMA_DONE_TX_CLR   ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMSPI_CPU_INT_RIS_DMA_DONE_TX_SET   ((uint32_t)0x00010000U)         /* !< Interrupt occured */

/* UNICOMMSPI_CPU_INT_MIS Bits */
/* UNICOMMSPI_CPU_INT_MIS[RX] Bits */
#define UNICOMMSPI_CPU_INT_MIS_RX_OFS            (2)                             /* !< RX Offset */
#define UNICOMMSPI_CPU_INT_MIS_RX_MASK           ((uint32_t)0x00000004U)         /* !< Masked Receive Event */
#define UNICOMMSPI_CPU_INT_MIS_RX_CLR            ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_RX_SET            ((uint32_t)0x00000004U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_MIS[TX] Bits */
#define UNICOMMSPI_CPU_INT_MIS_TX_OFS            (5)                             /* !< TX Offset */
#define UNICOMMSPI_CPU_INT_MIS_TX_MASK           ((uint32_t)0x00000020U)         /* !< Masked transmit event */
#define UNICOMMSPI_CPU_INT_MIS_TX_CLR            ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_TX_SET            ((uint32_t)0x00000020U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_MIS[TXEMPTY] Bits */
#define UNICOMMSPI_CPU_INT_MIS_TXEMPTY_OFS       (6)                             /* !< TXEMPTY Offset */
#define UNICOMMSPI_CPU_INT_MIS_TXEMPTY_MASK      ((uint32_t)0x00000040U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMSPI_CPU_INT_MIS_TXEMPTY_CLR       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_TXEMPTY_SET       ((uint32_t)0x00000040U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_MIS[PER] Bits */
#define UNICOMMSPI_CPU_INT_MIS_PER_OFS           (0)                             /* !< PER Offset */
#define UNICOMMSPI_CPU_INT_MIS_PER_MASK          ((uint32_t)0x00000001U)         /* !< Parity error event */
#define UNICOMMSPI_CPU_INT_MIS_PER_CLR           ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_PER_SET           ((uint32_t)0x00000001U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_MIS[RXFIFO_OVF] Bits */
#define UNICOMMSPI_CPU_INT_MIS_RXFIFO_OVF_OFS    (1)                             /* !< RXFIFO_OVF Offset */
#define UNICOMMSPI_CPU_INT_MIS_RXFIFO_OVF_MASK   ((uint32_t)0x00000002U)         /* !< RXFIFO overflow event */
#define UNICOMMSPI_CPU_INT_MIS_RXFIFO_OVF_CLR    ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_RXFIFO_OVF_SET    ((uint32_t)0x00000002U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_MIS[IDLE] Bits */
#define UNICOMMSPI_CPU_INT_MIS_IDLE_OFS          (8)                             /* !< IDLE Offset */
#define UNICOMMSPI_CPU_INT_MIS_IDLE_MASK         ((uint32_t)0x00000100U)         /* !< SPI in Idle mode */
#define UNICOMMSPI_CPU_INT_MIS_IDLE_CLR          ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_IDLE_SET          ((uint32_t)0x00000100U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_MIS[RXFULL] Bits */
#define UNICOMMSPI_CPU_INT_MIS_RXFULL_OFS        (3)                             /* !< RXFULL Offset */
#define UNICOMMSPI_CPU_INT_MIS_RXFULL_MASK       ((uint32_t)0x00000008U)         /* !< RX FIFO Full Interrupt */
#define UNICOMMSPI_CPU_INT_MIS_RXFULL_CLR        ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_RXFULL_SET        ((uint32_t)0x00000008U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_MIS[TXFIFO_UNF] Bits */
#define UNICOMMSPI_CPU_INT_MIS_TXFIFO_UNF_OFS    (4)                             /* !< TXFIFO_UNF Offset */
#define UNICOMMSPI_CPU_INT_MIS_TXFIFO_UNF_MASK   ((uint32_t)0x00000010U)         /* !< TX FIFO underflow interrupt */
#define UNICOMMSPI_CPU_INT_MIS_TXFIFO_UNF_CLR    ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_TXFIFO_UNF_SET    ((uint32_t)0x00000010U)         /* !< Interrupt occurred */
/* UNICOMMSPI_CPU_INT_MIS[DMA_DONE_RX] Bits */
#define UNICOMMSPI_CPU_INT_MIS_DMA_DONE_RX_OFS   (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMSPI_CPU_INT_MIS_DMA_DONE_RX_MASK  ((uint32_t)0x00008000U)         /* !< Masked DMA Done on RX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_CPU_INT_MIS_DMA_DONE_RX_CLR   ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_DMA_DONE_RX_SET   ((uint32_t)0x00008000U)         /* !< Interrupt occured */
/* UNICOMMSPI_CPU_INT_MIS[DMA_DONE_TX] Bits */
#define UNICOMMSPI_CPU_INT_MIS_DMA_DONE_TX_OFS   (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMSPI_CPU_INT_MIS_DMA_DONE_TX_MASK  ((uint32_t)0x00010000U)         /* !< Masked DMA Done on TX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_CPU_INT_MIS_DMA_DONE_TX_CLR   ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define UNICOMMSPI_CPU_INT_MIS_DMA_DONE_TX_SET   ((uint32_t)0x00010000U)         /* !< Interrupt occured */

/* UNICOMMSPI_CPU_INT_ISET Bits */
/* UNICOMMSPI_CPU_INT_ISET[RX] Bits */
#define UNICOMMSPI_CPU_INT_ISET_RX_OFS           (2)                             /* !< RX Offset */
#define UNICOMMSPI_CPU_INT_ISET_RX_MASK          ((uint32_t)0x00000004U)         /* !< Receive FIFO event */
#define UNICOMMSPI_CPU_INT_ISET_RX_NO_EFFECT     ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_CPU_INT_ISET_RX_SET           ((uint32_t)0x00000004U)         /* !< Set Interrupt */
/* UNICOMMSPI_CPU_INT_ISET[TX] Bits */
#define UNICOMMSPI_CPU_INT_ISET_TX_OFS           (5)                             /* !< TX Offset */
#define UNICOMMSPI_CPU_INT_ISET_TX_MASK          ((uint32_t)0x00000020U)         /* !< Transmit FIFO event */
#define UNICOMMSPI_CPU_INT_ISET_TX_NO_EFFECT     ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_CPU_INT_ISET_TX_SET           ((uint32_t)0x00000020U)         /* !< Set Interrupt */
/* UNICOMMSPI_CPU_INT_ISET[TXEMPTY] Bits */
#define UNICOMMSPI_CPU_INT_ISET_TXEMPTY_OFS      (6)                             /* !< TXEMPTY Offset */
#define UNICOMMSPI_CPU_INT_ISET_TXEMPTY_MASK     ((uint32_t)0x00000040U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMSPI_CPU_INT_ISET_TXEMPTY_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_CPU_INT_ISET_TXEMPTY_SET      ((uint32_t)0x00000040U)         /* !< Set Interrupt */
/* UNICOMMSPI_CPU_INT_ISET[PER] Bits */
#define UNICOMMSPI_CPU_INT_ISET_PER_OFS          (0)                             /* !< PER Offset */
#define UNICOMMSPI_CPU_INT_ISET_PER_MASK         ((uint32_t)0x00000001U)         /* !< Parity error event */
#define UNICOMMSPI_CPU_INT_ISET_PER_NO_EFFECT    ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_CPU_INT_ISET_PER_SET          ((uint32_t)0x00000001U)         /* !< Set Interrupt */
/* UNICOMMSPI_CPU_INT_ISET[RXFIFO_OVF] Bits */
#define UNICOMMSPI_CPU_INT_ISET_RXFIFO_OVF_OFS   (1)                             /* !< RXFIFO_OVF Offset */
#define UNICOMMSPI_CPU_INT_ISET_RXFIFO_OVF_MASK  ((uint32_t)0x00000002U)         /* !< RXFIFO overflow event */
#define UNICOMMSPI_CPU_INT_ISET_RXFIFO_OVF_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_CPU_INT_ISET_RXFIFO_OVF_SET   ((uint32_t)0x00000002U)         /* !< Set Interrupt */
/* UNICOMMSPI_CPU_INT_ISET[IDLE] Bits */
#define UNICOMMSPI_CPU_INT_ISET_IDLE_OFS         (8)                             /* !< IDLE Offset */
#define UNICOMMSPI_CPU_INT_ISET_IDLE_MASK        ((uint32_t)0x00000100U)         /* !< SPI in Idle mode */
#define UNICOMMSPI_CPU_INT_ISET_IDLE_NO_EFFECT   ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_CPU_INT_ISET_IDLE_SET         ((uint32_t)0x00000100U)         /* !< Set Interrupt */
/* UNICOMMSPI_CPU_INT_ISET[TXFIFO_UNF] Bits */
#define UNICOMMSPI_CPU_INT_ISET_TXFIFO_UNF_OFS   (4)                             /* !< TXFIFO_UNF Offset */
#define UNICOMMSPI_CPU_INT_ISET_TXFIFO_UNF_MASK  ((uint32_t)0x00000010U)         /* !< Set TX FIFO Underflow Event */
#define UNICOMMSPI_CPU_INT_ISET_TXFIFO_UNF_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing has no effect */
#define UNICOMMSPI_CPU_INT_ISET_TXFIFO_UNF_SET   ((uint32_t)0x00000010U)         /* !< Set interrupt */
/* UNICOMMSPI_CPU_INT_ISET[RXFULL] Bits */
#define UNICOMMSPI_CPU_INT_ISET_RXFULL_OFS       (3)                             /* !< RXFULL Offset */
#define UNICOMMSPI_CPU_INT_ISET_RXFULL_MASK      ((uint32_t)0x00000008U)         /* !< Set RX FIFO Full Event */
#define UNICOMMSPI_CPU_INT_ISET_RXFULL_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Writing has no effect */
#define UNICOMMSPI_CPU_INT_ISET_RXFULL_SET       ((uint32_t)0x00000008U)         /* !< Set Interrupt */
/* UNICOMMSPI_CPU_INT_ISET[DMA_DONE_RX] Bits */
#define UNICOMMSPI_CPU_INT_ISET_DMA_DONE_RX_OFS  (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMSPI_CPU_INT_ISET_DMA_DONE_RX_MASK ((uint32_t)0x00008000U)         /* !< Set DMA Done on RX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_CPU_INT_ISET_DMA_DONE_RX_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMSPI_CPU_INT_ISET_DMA_DONE_RX_SET  ((uint32_t)0x00008000U)         /* !< Set Interrupt */
/* UNICOMMSPI_CPU_INT_ISET[DMA_DONE_TX] Bits */
#define UNICOMMSPI_CPU_INT_ISET_DMA_DONE_TX_OFS  (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMSPI_CPU_INT_ISET_DMA_DONE_TX_MASK ((uint32_t)0x00010000U)         /* !< Set DMA Done on TX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_CPU_INT_ISET_DMA_DONE_TX_NO_EFFECT ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMSPI_CPU_INT_ISET_DMA_DONE_TX_SET  ((uint32_t)0x00010000U)         /* !< Set Interrupt */

/* UNICOMMSPI_ICLR Bits */
/* UNICOMMSPI_ICLR[RX] Bits */
#define UNICOMMSPI_ICLR_RX_OFS                   (2)                             /* !< RX Offset */
#define UNICOMMSPI_ICLR_RX_MASK                  ((uint32_t)0x00000004U)         /* !< Receive FIFO event */
#define UNICOMMSPI_ICLR_RX_NO_EFFECT             ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_ICLR_RX_CLR                   ((uint32_t)0x00000004U)         /* !< Clear Interrupt */
/* UNICOMMSPI_ICLR[TX] Bits */
#define UNICOMMSPI_ICLR_TX_OFS                   (5)                             /* !< TX Offset */
#define UNICOMMSPI_ICLR_TX_MASK                  ((uint32_t)0x00000020U)         /* !< Transmit FIFO event */
#define UNICOMMSPI_ICLR_TX_NO_EFFECT             ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_ICLR_TX_CLR                   ((uint32_t)0x00000020U)         /* !< Clear Interrupt */
/* UNICOMMSPI_ICLR[TXEMPTY] Bits */
#define UNICOMMSPI_ICLR_TXEMPTY_OFS              (6)                             /* !< TXEMPTY Offset */
#define UNICOMMSPI_ICLR_TXEMPTY_MASK             ((uint32_t)0x00000040U)         /* !< Transmit FIFO Empty interrupt mask */
#define UNICOMMSPI_ICLR_TXEMPTY_NO_EFFECT        ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_ICLR_TXEMPTY_CLR              ((uint32_t)0x00000040U)         /* !< Clear Interrupt */
/* UNICOMMSPI_ICLR[PER] Bits */
#define UNICOMMSPI_ICLR_PER_OFS                  (0)                             /* !< PER Offset */
#define UNICOMMSPI_ICLR_PER_MASK                 ((uint32_t)0x00000001U)         /* !< Parity error event */
#define UNICOMMSPI_ICLR_PER_NO_EFFECT            ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_ICLR_PER_CLR                  ((uint32_t)0x00000001U)         /* !< Clear Interrupt */
/* UNICOMMSPI_ICLR[RXFIFO_OVF] Bits */
#define UNICOMMSPI_ICLR_RXFIFO_OVF_OFS           (1)                             /* !< RXFIFO_OVF Offset */
#define UNICOMMSPI_ICLR_RXFIFO_OVF_MASK          ((uint32_t)0x00000002U)         /* !< RXFIFO overflow event */
#define UNICOMMSPI_ICLR_RXFIFO_OVF_NO_EFFECT     ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_ICLR_RXFIFO_OVF_CLR           ((uint32_t)0x00000002U)         /* !< Clear Interrupt */
/* UNICOMMSPI_ICLR[IDLE] Bits */
#define UNICOMMSPI_ICLR_IDLE_OFS                 (8)                             /* !< IDLE Offset */
#define UNICOMMSPI_ICLR_IDLE_MASK                ((uint32_t)0x00000100U)         /* !< SPI in Idle mode */
#define UNICOMMSPI_ICLR_IDLE_NO_EFFECT           ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define UNICOMMSPI_ICLR_IDLE_CLR                 ((uint32_t)0x00000100U)         /* !< Clear Interrupt */
/* UNICOMMSPI_ICLR[TXFIFO_UNF] Bits */
#define UNICOMMSPI_ICLR_TXFIFO_UNF_OFS           (4)                             /* !< TXFIFO_UNF Offset */
#define UNICOMMSPI_ICLR_TXFIFO_UNF_MASK          ((uint32_t)0x00000010U)         /* !< Clear TXFIFO underflow event */
#define UNICOMMSPI_ICLR_TXFIFO_UNF_NO_EFFECT     ((uint32_t)0x00000000U)         /* !< Writing has no effect */
#define UNICOMMSPI_ICLR_TXFIFO_UNF_CLR           ((uint32_t)0x00000010U)         /* !< Clear interrupt */
/* UNICOMMSPI_ICLR[RXFULL] Bits */
#define UNICOMMSPI_ICLR_RXFULL_OFS               (3)                             /* !< RXFULL Offset */
#define UNICOMMSPI_ICLR_RXFULL_MASK              ((uint32_t)0x00000008U)         /* !< Clear RX FIFO underflow event */
#define UNICOMMSPI_ICLR_RXFULL_NO_EFFECT         ((uint32_t)0x00000000U)         /* !< Writing has no effect */
#define UNICOMMSPI_ICLR_RXFULL_CLR               ((uint32_t)0x00000008U)         /* !< Clear interrupt */
/* UNICOMMSPI_ICLR[DMA_DONE_RX] Bits */
#define UNICOMMSPI_ICLR_DMA_DONE_RX_OFS          (15)                            /* !< DMA_DONE_RX Offset */
#define UNICOMMSPI_ICLR_DMA_DONE_RX_MASK         ((uint32_t)0x00008000U)         /* !< Clear DMA Done on RX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_ICLR_DMA_DONE_RX_NO_EFFECT    ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMSPI_ICLR_DMA_DONE_RX_CLR          ((uint32_t)0x00008000U)         /* !< Clear Interrupt */
/* UNICOMMSPI_ICLR[DMA_DONE_TX] Bits */
#define UNICOMMSPI_ICLR_DMA_DONE_TX_OFS          (16)                            /* !< DMA_DONE_TX Offset */
#define UNICOMMSPI_ICLR_DMA_DONE_TX_MASK         ((uint32_t)0x00010000U)         /* !< Clear DMA Done on TX Event Channel
                                                                                    Interrupt */
#define UNICOMMSPI_ICLR_DMA_DONE_TX_NO_EFFECT    ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define UNICOMMSPI_ICLR_DMA_DONE_TX_CLR          ((uint32_t)0x00010000U)         /* !< Clear Interrupt */

/* UNICOMMSPI_CLKDIV Bits */
/* UNICOMMSPI_CLKDIV[RATIO] Bits */
#define UNICOMMSPI_CLKDIV_RATIO_OFS              (0)                             /* !< RATIO Offset */
#define UNICOMMSPI_CLKDIV_RATIO_MASK             ((uint32_t)0x00000007U)         /* !< Selects divide ratio of module
                                                                                    clock */
#define UNICOMMSPI_CLKDIV_RATIO_DIV_BY_1         ((uint32_t)0x00000000U)         /* !< Do not divide clock source */
#define UNICOMMSPI_CLKDIV_RATIO_DIV_BY_2         ((uint32_t)0x00000001U)         /* !< Divide clock source by 2 */
#define UNICOMMSPI_CLKDIV_RATIO_DIV_BY_3         ((uint32_t)0x00000002U)         /* !< Divide clock source by 3 */
#define UNICOMMSPI_CLKDIV_RATIO_DIV_BY_4         ((uint32_t)0x00000003U)         /* !< Divide clock source by 4 */
#define UNICOMMSPI_CLKDIV_RATIO_DIV_BY_5         ((uint32_t)0x00000004U)         /* !< Divide clock source by 5 */
#define UNICOMMSPI_CLKDIV_RATIO_DIV_BY_6         ((uint32_t)0x00000005U)         /* !< Divide clock source by 6 */
#define UNICOMMSPI_CLKDIV_RATIO_DIV_BY_7         ((uint32_t)0x00000006U)         /* !< Divide clock source by 7 */
#define UNICOMMSPI_CLKDIV_RATIO_DIV_BY_8         ((uint32_t)0x00000007U)         /* !< Divide clock source by 8 */

/* UNICOMMSPI_CLKSEL Bits */
/* UNICOMMSPI_CLKSEL[BUSCLK_SEL] Bits */
#define UNICOMMSPI_CLKSEL_BUSCLK_SEL_OFS         (3)                             /* !< BUSCLK_SEL Offset */
#define UNICOMMSPI_CLKSEL_BUSCLK_SEL_MASK        ((uint32_t)0x00000008U)         /* !< Selects buscclk as clock source if
                                                                                    enabled */
#define UNICOMMSPI_CLKSEL_BUSCLK_SEL_DISABLE     ((uint32_t)0x00000000U)         /* !< Does not select this clock as a
                                                                                    source */
#define UNICOMMSPI_CLKSEL_BUSCLK_SEL_ENABLE      ((uint32_t)0x00000008U)         /* !< Select this clock as a source */

/* UNICOMMSPI_PDBGCTL Bits */
/* UNICOMMSPI_PDBGCTL[FREE] Bits */
#define UNICOMMSPI_PDBGCTL_FREE_OFS              (0)                             /* !< FREE Offset */
#define UNICOMMSPI_PDBGCTL_FREE_MASK             ((uint32_t)0x00000001U)         /* !< Free run control */
#define UNICOMMSPI_PDBGCTL_FREE_STOP             ((uint32_t)0x00000000U)         /* !< The peripheral freezes
                                                                                    functionality while the Core Halted
                                                                                    input is asserted and resumes when it
                                                                                    is deasserted. */
#define UNICOMMSPI_PDBGCTL_FREE_RUN              ((uint32_t)0x00000001U)         /* !< The peripheral ignores the state of
                                                                                    the Core Halted input */
/* UNICOMMSPI_PDBGCTL[SOFT] Bits */
#define UNICOMMSPI_PDBGCTL_SOFT_OFS              (1)                             /* !< SOFT Offset */
#define UNICOMMSPI_PDBGCTL_SOFT_MASK             ((uint32_t)0x00000002U)         /* !< Soft halt boundary control. This
                                                                                    function is only available, if [FREE]
                                                                                    is set to 'STOP' */
#define UNICOMMSPI_PDBGCTL_SOFT_DEPRECATED       ((uint32_t)0x00000000U)         /* !< Not supported */
#define UNICOMMSPI_PDBGCTL_SOFT_DELAYED          ((uint32_t)0x00000002U)         /* !< The peripheral blocks the debug
                                                                                    freeze until it has reached a
                                                                                    boundary where it can resume without
                                                                                    corruption */

/* UNICOMMSPI_INTCTL Bits */
/* UNICOMMSPI_INTCTL[INTEVAL] Bits */
#define UNICOMMSPI_INTCTL_INTEVAL_OFS            (0)                             /* !< INTEVAL Offset */
#define UNICOMMSPI_INTCTL_INTEVAL_MASK           ((uint32_t)0x00000001U)         /* !< Writing a 1 to this field
                                                                                    re-evaluates the interrupt sources. */
#define UNICOMMSPI_INTCTL_INTEVAL_DISABLE        ((uint32_t)0x00000000U)         /* !< The interrupt or event line is
                                                                                    disabled. */
#define UNICOMMSPI_INTCTL_INTEVAL_EVAL           ((uint32_t)0x00000001U)         /* !< The interrupt or event line is in
                                                                                    software mode. Software must clear
                                                                                    the RIS. */

/* UNICOMMSPI_CTL0 Bits */
/* UNICOMMSPI_CTL0[DSS] Bits */
#define UNICOMMSPI_CTL0_DSS_OFS                  (0)                             /* !< DSS Offset */
#define UNICOMMSPI_CTL0_DSS_MASK                 ((uint32_t)0x0000001FU)         /* !< Data Size Select. */
#define UNICOMMSPI_CTL0_DSS_DSS_4                ((uint32_t)0x00000003U)         /* !< Data Size Select bits: 4 */
#define UNICOMMSPI_CTL0_DSS_DSS_5                ((uint32_t)0x00000004U)         /* !< Data Size Select bits: 5 */
#define UNICOMMSPI_CTL0_DSS_DSS_6                ((uint32_t)0x00000005U)         /* !< Data Size Select bits: 6 */
#define UNICOMMSPI_CTL0_DSS_DSS_7                ((uint32_t)0x00000006U)         /* !< Data Size Select bits: 7 */
#define UNICOMMSPI_CTL0_DSS_DSS_8                ((uint32_t)0x00000007U)         /* !< Data Size Select bits: 8 */
#define UNICOMMSPI_CTL0_DSS_DSS_9                ((uint32_t)0x00000008U)         /* !< Data Size Select bits: 9 */
#define UNICOMMSPI_CTL0_DSS_DSS_10               ((uint32_t)0x00000009U)         /* !< Data Size Select bits: 10 */
#define UNICOMMSPI_CTL0_DSS_DSS_11               ((uint32_t)0x0000000AU)         /* !< Data Size Select bits: 11 */
#define UNICOMMSPI_CTL0_DSS_DSS_12               ((uint32_t)0x0000000BU)         /* !< Data Size Select bits: 12 */
#define UNICOMMSPI_CTL0_DSS_DSS_13               ((uint32_t)0x0000000CU)         /* !< Data Size Select bits: 13 */
#define UNICOMMSPI_CTL0_DSS_DSS_14               ((uint32_t)0x0000000DU)         /* !< Data Size Select bits: 14 */
#define UNICOMMSPI_CTL0_DSS_DSS_15               ((uint32_t)0x0000000EU)         /* !< Data Size Select bits: 15 */
#define UNICOMMSPI_CTL0_DSS_DSS_16               ((uint32_t)0x0000000FU)         /* !< Data Size Select bits: 16 */
/* UNICOMMSPI_CTL0[FRF] Bits */
#define UNICOMMSPI_CTL0_FRF_OFS                  (5)                             /* !< FRF Offset */
#define UNICOMMSPI_CTL0_FRF_MASK                 ((uint32_t)0x00000060U)         /* !< Frame format Select */
#define UNICOMMSPI_CTL0_FRF_MOTOROLA_3WIRE       ((uint32_t)0x00000000U)         /* !< Motorola SPI frame format (3 wire
                                                                                    mode) */
#define UNICOMMSPI_CTL0_FRF_MOTOROLA_4WIRE       ((uint32_t)0x00000020U)         /* !< Motorola SPI frame format (4 wire
                                                                                    mode) */
#define UNICOMMSPI_CTL0_FRF_TI_SYNC              ((uint32_t)0x00000040U)         /* !< TI synchronous serial frame format */
/* UNICOMMSPI_CTL0[SPO] Bits */
#define UNICOMMSPI_CTL0_SPO_OFS                  (8)                             /* !< SPO Offset */
#define UNICOMMSPI_CTL0_SPO_MASK                 ((uint32_t)0x00000100U)         /* !< CLKOUT polarity */
#define UNICOMMSPI_CTL0_SPO_LOW                  ((uint32_t)0x00000000U)         /* !< SPI produces a steady state LOW
                                                                                    value on the CLKOUT */
#define UNICOMMSPI_CTL0_SPO_HIGH                 ((uint32_t)0x00000100U)         /* !< SPI produces a steady state HIGH
                                                                                    value on the CLKOUT */
/* UNICOMMSPI_CTL0[SPH] Bits */
#define UNICOMMSPI_CTL0_SPH_OFS                  (9)                             /* !< SPH Offset */
#define UNICOMMSPI_CTL0_SPH_MASK                 ((uint32_t)0x00000200U)         /* !< CLKOUT phase */
#define UNICOMMSPI_CTL0_SPH_FIRST                ((uint32_t)0x00000000U)         /* !< Data is captured on the first clock
                                                                                    edge transition. */
#define UNICOMMSPI_CTL0_SPH_SECOND               ((uint32_t)0x00000200U)         /* !< Data is captured on the second
                                                                                    clock edge transition. */
/* UNICOMMSPI_CTL0[CSCLR] Bits */
#define UNICOMMSPI_CTL0_CSCLR_OFS                (14)                            /* !< CSCLR Offset */
#define UNICOMMSPI_CTL0_CSCLR_MASK               ((uint32_t)0x00004000U)         /* !< Clear on CS inactive */
#define UNICOMMSPI_CTL0_CSCLR_DISABLE            ((uint32_t)0x00000000U)         /* !< Disable automatic clear of shift
                                                                                    register when CS goes to disable. */
#define UNICOMMSPI_CTL0_CSCLR_ENABLE             ((uint32_t)0x00004000U)         /* !< Enable automatic clear of shift
                                                                                    register when CS goes to disable. */

/* UNICOMMSPI_STAT Bits */
/* UNICOMMSPI_STAT[TXFE] Bits */
#define UNICOMMSPI_STAT_TXFE_OFS                 (5)                             /* !< TXFE Offset */
#define UNICOMMSPI_STAT_TXFE_MASK                ((uint32_t)0x00000020U)         /* !< Transmit FIFO empty. */
#define UNICOMMSPI_STAT_TXFE_NOT_EMPTY           ((uint32_t)0x00000000U)         /* !< Transmit FIFO is not empty. */
#define UNICOMMSPI_STAT_TXFE_EMPTY               ((uint32_t)0x00000020U)         /* !< Transmit FIFO is empty. */
/* UNICOMMSPI_STAT[RXFE] Bits */
#define UNICOMMSPI_STAT_RXFE_OFS                 (2)                             /* !< RXFE Offset */
#define UNICOMMSPI_STAT_RXFE_MASK                ((uint32_t)0x00000004U)         /* !< Receive FIFO empty. */
#define UNICOMMSPI_STAT_RXFE_NOT_EMPTY           ((uint32_t)0x00000000U)         /* !< Receive FIFO is not empty. */
#define UNICOMMSPI_STAT_RXFE_EMPTY               ((uint32_t)0x00000004U)         /* !< Receive FIFO is empty. */
/* UNICOMMSPI_STAT[BUSY] Bits */
#define UNICOMMSPI_STAT_BUSY_OFS                 (8)                             /* !< BUSY Offset */
#define UNICOMMSPI_STAT_BUSY_MASK                ((uint32_t)0x00000100U)         /* !< Busy */
#define UNICOMMSPI_STAT_BUSY_IDLE                ((uint32_t)0x00000000U)         /* !< SPI is in idle mode. */
#define UNICOMMSPI_STAT_BUSY_ACTIVE              ((uint32_t)0x00000100U)         /* !< SPI is currently transmitting
                                                                                    and/or receiving data */
/* UNICOMMSPI_STAT[RXCLR] Bits */
#define UNICOMMSPI_STAT_RXCLR_OFS                (4)                             /* !< RXCLR Offset */
#define UNICOMMSPI_STAT_RXCLR_MASK               ((uint32_t)0x00000010U)         /* !< RX FIFO Clear Status */
#define UNICOMMSPI_STAT_RXCLR_CLEARED            ((uint32_t)0x00000000U)         /* !< FIFO is not cleared */
#define UNICOMMSPI_STAT_RXCLR_SET                ((uint32_t)0x00000010U)         /* !< FIFO clear is complete */
/* UNICOMMSPI_STAT[TXCLR] Bits */
#define UNICOMMSPI_STAT_TXCLR_OFS                (7)                             /* !< TXCLR Offset */
#define UNICOMMSPI_STAT_TXCLR_MASK               ((uint32_t)0x00000080U)         /* !< TX FIFO Clear Status */
#define UNICOMMSPI_STAT_TXCLR_CLEARED            ((uint32_t)0x00000000U)         /* !< FIFO is not cleared */
#define UNICOMMSPI_STAT_TXCLR_SET                ((uint32_t)0x00000080U)         /* !< FIFO clear is complete */
/* UNICOMMSPI_STAT[RXFF] Bits */
#define UNICOMMSPI_STAT_RXFF_OFS                 (3)                             /* !< RXFF Offset */
#define UNICOMMSPI_STAT_RXFF_MASK                ((uint32_t)0x00000008U)         /* !< Receive FIFO Full  The meaning of
                                                                                    this bit depends on the state of the
                                                                                    FEN bit in the CTL0 register. */
#define UNICOMMSPI_STAT_RXFF_CLEARED             ((uint32_t)0x00000000U)         /* !< The receiver can receive data. */
#define UNICOMMSPI_STAT_RXFF_SET                 ((uint32_t)0x00000008U)         /* !< If the FIFO is disabled (FEN is 0),
                                                                                    the receive holding register is full.
                                                                                    If the FIFO is enabled (FEN is 1),
                                                                                    the receive FIFO is full. */
/* UNICOMMSPI_STAT[TXFF] Bits */
#define UNICOMMSPI_STAT_TXFF_OFS                 (6)                             /* !< TXFF Offset */
#define UNICOMMSPI_STAT_TXFF_MASK                ((uint32_t)0x00000040U)         /* !< Transmit FIFO Full  The meaning of
                                                                                    this bit depends on the state of the
                                                                                    FEN bit in the CTL0 register. */
#define UNICOMMSPI_STAT_TXFF_CLEARED             ((uint32_t)0x00000000U)         /* !< The transmitter is not full. */
#define UNICOMMSPI_STAT_TXFF_SET                 ((uint32_t)0x00000040U)         /* !< If the FIFO is disabled (FEN is 0),
                                                                                    the transmit holding register is
                                                                                    full. If the FIFO is enabled (FEN is
                                                                                    1), the transmit FIFO is full. */

/* UNICOMMSPI_IFLS Bits */
/* UNICOMMSPI_IFLS[TXIFLSEL] Bits */
#define UNICOMMSPI_IFLS_TXIFLSEL_OFS             (0)                             /* !< TXIFLSEL Offset */
#define UNICOMMSPI_IFLS_TXIFLSEL_MASK            ((uint32_t)0x00000007U)         /* !< FIFO Level Select for generating
                                                                                    events (interrupt/dma).  Note: for
                                                                                    undefined settings the default
                                                                                    configuration is used. */
#define UNICOMMSPI_IFLS_TXIFLSEL_LVL_3_4         ((uint32_t)0x00000001U)         /* !< TX FIFO <= 3/4 empty */
#define UNICOMMSPI_IFLS_TXIFLSEL_LVL_1_2         ((uint32_t)0x00000002U)         /* !< TX FIFO <= 1/2 empty (default) */
#define UNICOMMSPI_IFLS_TXIFLSEL_LVL_1_4         ((uint32_t)0x00000003U)         /* !< TX FIFO <= 1/4 empty */
#define UNICOMMSPI_IFLS_TXIFLSEL_LVL_NOT_FULL    ((uint32_t)0x00000004U)         /* !< Opposite of full */
#define UNICOMMSPI_IFLS_TXIFLSEL_LVL_EMPTY       ((uint32_t)0x00000005U)         /* !< TX FIFO is empty */
#define UNICOMMSPI_IFLS_TXIFLSEL_LVL_ALMOST_EMPTY ((uint32_t)0x00000006U)         /* !< TX FIFO <= 1 */
#define UNICOMMSPI_IFLS_TXIFLSEL_LVL_ALMOST_FULL ((uint32_t)0x00000007U)         /* !< TX_FIFO >= (MAX_FIFO_LEN -1) */
/* UNICOMMSPI_IFLS[RXIFLSEL] Bits */
#define UNICOMMSPI_IFLS_RXIFLSEL_OFS             (4)                             /* !< RXIFLSEL Offset */
#define UNICOMMSPI_IFLS_RXIFLSEL_MASK            ((uint32_t)0x00000070U)         /* !< FIFO Level Select for generating
                                                                                    events (interrupt/dma).  Note: for
                                                                                    undefined settings the default
                                                                                    configuration is used. */
#define UNICOMMSPI_IFLS_RXIFLSEL_LVL_1_4         ((uint32_t)0x00000010U)         /* !< RX FIFO >= 1/4 full */
#define UNICOMMSPI_IFLS_RXIFLSEL_LVL_1_2         ((uint32_t)0x00000020U)         /* !< RX FIFO >= 1/2 full (default) */
#define UNICOMMSPI_IFLS_RXIFLSEL_LVL_3_4         ((uint32_t)0x00000030U)         /* !< RX FIFO >= 3/4 full */
#define UNICOMMSPI_IFLS_RXIFLSEL_LVL_NOT_EMPTY   ((uint32_t)0x00000040U)         /* !< Opposite of empty */
#define UNICOMMSPI_IFLS_RXIFLSEL_LVL_FULL        ((uint32_t)0x00000050U)         /* !< RX FIFO is full */
#define UNICOMMSPI_IFLS_RXIFLSEL_LVL_ALMOST_FULL ((uint32_t)0x00000060U)         /* !< RX_FIFO >= (MAX_FIFO_LEN -1) */
#define UNICOMMSPI_IFLS_RXIFLSEL_LVL_ALMOST_EMPTY ((uint32_t)0x00000070U)         /* !< RX_FIFO <= 1 */
/* UNICOMMSPI_IFLS[TXCLR] Bits */
#define UNICOMMSPI_IFLS_TXCLR_OFS                (3)                             /* !< TXCLR Offset */
#define UNICOMMSPI_IFLS_TXCLR_MASK               ((uint32_t)0x00000008U)         /* !< RX FIFO Flush */
#define UNICOMMSPI_IFLS_TXCLR_DISABLE            ((uint32_t)0x00000000U)         /* !< Disable FIFO clear */
#define UNICOMMSPI_IFLS_TXCLR_ENABLE             ((uint32_t)0x00000008U)         /* !< Enable FIFO Clear */
/* UNICOMMSPI_IFLS[RXCLR] Bits */
#define UNICOMMSPI_IFLS_RXCLR_OFS                (7)                             /* !< RXCLR Offset */
#define UNICOMMSPI_IFLS_RXCLR_MASK               ((uint32_t)0x00000080U)         /* !< RX FIFO CLEAR */
#define UNICOMMSPI_IFLS_RXCLR_DISABLE            ((uint32_t)0x00000000U)         /* !< Disable FIFO clear */
#define UNICOMMSPI_IFLS_RXCLR_ENABLE             ((uint32_t)0x00000080U)         /* !< Enable FIFO Clear */

/* UNICOMMSPI_CLKCTL Bits */
/* UNICOMMSPI_CLKCTL[SCR] Bits */
#define UNICOMMSPI_CLKCTL_SCR_OFS                (0)                             /* !< SCR Offset */
#define UNICOMMSPI_CLKCTL_SCR_MASK               ((uint32_t)0x000003FFU)         /* !< Serial clock divider */
#define UNICOMMSPI_CLKCTL_SCR_MINIMUM            ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMSPI_CLKCTL_SCR_MAXIMUM            ((uint32_t)0x000003FFU)         /* !< Highest possible value */
/* UNICOMMSPI_CLKCTL[DSAMPLE] Bits */
#define UNICOMMSPI_CLKCTL_DSAMPLE_OFS            (28)                            /* !< DSAMPLE Offset */
#define UNICOMMSPI_CLKCTL_DSAMPLE_MASK           ((uint32_t)0xF0000000U)         /* !< Delayed sampling. */
#define UNICOMMSPI_CLKCTL_DSAMPLE_MINIMUM        ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMSPI_CLKCTL_DSAMPLE_MAXIMUM        ((uint32_t)0xF0000000U)         /* !< Highest possible value */

/* UNICOMMSPI_TXDATA Bits */
/* UNICOMMSPI_TXDATA[DATA] Bits */
#define UNICOMMSPI_TXDATA_DATA_OFS               (0)                             /* !< DATA Offset */
#define UNICOMMSPI_TXDATA_DATA_MASK              ((uint32_t)0x0000FFFFU)         /* !< Transmit Data */
#define UNICOMMSPI_TXDATA_DATA_MINIMUM           ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMSPI_TXDATA_DATA_MAXIMUM           ((uint32_t)0x0000FFFFU)         /* !< Highest possible value */

/* UNICOMMSPI_RXDATA Bits */
/* UNICOMMSPI_RXDATA[DATA] Bits */
#define UNICOMMSPI_RXDATA_DATA_OFS               (0)                             /* !< DATA Offset */
#define UNICOMMSPI_RXDATA_DATA_MASK              ((uint32_t)0x0000FFFFU)         /* !< Received Data */
#define UNICOMMSPI_RXDATA_DATA_MINIMUM           ((uint32_t)0x00000000U)         /* !< Smallest value */
#define UNICOMMSPI_RXDATA_DATA_MAXIMUM           ((uint32_t)0x0000FFFFU)         /* !< Highest possible value */

/* UNICOMMSPI_CTL1 Bits */
/* UNICOMMSPI_CTL1[LBM] Bits */
#define UNICOMMSPI_CTL1_LBM_OFS                  (1)                             /* !< LBM Offset */
#define UNICOMMSPI_CTL1_LBM_MASK                 ((uint32_t)0x00000002U)         /* !< Loop back mode enable */
#define UNICOMMSPI_CTL1_LBM_DISABLE              ((uint32_t)0x00000000U)         /* !< Disable loopback mode */
#define UNICOMMSPI_CTL1_LBM_ENABLE               ((uint32_t)0x00000002U)         /* !< Enable loopback mode */
/* UNICOMMSPI_CTL1[CP] Bits */
#define UNICOMMSPI_CTL1_CP_OFS                   (2)                             /* !< CP Offset */
#define UNICOMMSPI_CTL1_CP_MASK                  ((uint32_t)0x00000004U)         /* !< Controller or peripheral mode
                                                                                    select */
#define UNICOMMSPI_CTL1_CP_DISABLE               ((uint32_t)0x00000000U)         /* !< Select Peripheral mode */
#define UNICOMMSPI_CTL1_CP_ENABLE                ((uint32_t)0x00000004U)         /* !< Select Controller Mode */
/* UNICOMMSPI_CTL1[POD] Bits */
#define UNICOMMSPI_CTL1_POD_OFS                  (3)                             /* !< POD Offset */
#define UNICOMMSPI_CTL1_POD_MASK                 ((uint32_t)0x00000008U)         /* !< Peripheral-mode: Data output
                                                                                    disabled */
#define UNICOMMSPI_CTL1_POD_DISABLE              ((uint32_t)0x00000000U)         /* !< SPI can drive the POCI output in
                                                                                    peripheral mode. */
#define UNICOMMSPI_CTL1_POD_ENABLE               ((uint32_t)0x00000008U)         /* !< SPI cannot drive the POCI output in
                                                                                    peripheral mode. */
/* UNICOMMSPI_CTL1[MSB] Bits */
#define UNICOMMSPI_CTL1_MSB_OFS                  (4)                             /* !< MSB Offset */
#define UNICOMMSPI_CTL1_MSB_MASK                 ((uint32_t)0x00000010U)         /* !< MSB first select */
#define UNICOMMSPI_CTL1_MSB_DISABLE              ((uint32_t)0x00000000U)         /* !< LSB first */
#define UNICOMMSPI_CTL1_MSB_ENABLE               ((uint32_t)0x00000010U)         /* !< MSB first */
/* UNICOMMSPI_CTL1[PREN] Bits */
#define UNICOMMSPI_CTL1_PREN_OFS                 (5)                             /* !< PREN Offset */
#define UNICOMMSPI_CTL1_PREN_MASK                ((uint32_t)0x00000020U)         /* !< Parity Receive Enable */
#define UNICOMMSPI_CTL1_PREN_DISABLE             ((uint32_t)0x00000000U)         /* !< Disable Parity receive function */
#define UNICOMMSPI_CTL1_PREN_ENABLE              ((uint32_t)0x00000020U)         /* !< Enable Parity receive function */
/* UNICOMMSPI_CTL1[PES] Bits */
#define UNICOMMSPI_CTL1_PES_OFS                  (6)                             /* !< PES Offset */
#define UNICOMMSPI_CTL1_PES_MASK                 ((uint32_t)0x00000040U)         /* !< Even Parity Select */
#define UNICOMMSPI_CTL1_PES_DISABLE              ((uint32_t)0x00000000U)         /* !< Odd Parity mode */
#define UNICOMMSPI_CTL1_PES_ENABLE               ((uint32_t)0x00000040U)         /* !< Even Parity mode */
/* UNICOMMSPI_CTL1[ENABLE] Bits */
#define UNICOMMSPI_CTL1_ENABLE_OFS               (0)                             /* !< ENABLE Offset */
#define UNICOMMSPI_CTL1_ENABLE_MASK              ((uint32_t)0x00000001U)         /* !< SPI enable */
#define UNICOMMSPI_CTL1_ENABLE_DISABLE           ((uint32_t)0x00000000U)         /* !< Disable module function */
#define UNICOMMSPI_CTL1_ENABLE_ENABLE            ((uint32_t)0x00000001U)         /* !< Enable module function */
/* UNICOMMSPI_CTL1[PTEN] Bits */
#define UNICOMMSPI_CTL1_PTEN_OFS                 (8)                             /* !< PTEN Offset */
#define UNICOMMSPI_CTL1_PTEN_MASK                ((uint32_t)0x00000100U)         /* !< Parity Transmit Enable */
#define UNICOMMSPI_CTL1_PTEN_DISABLE             ((uint32_t)0x00000000U)         /* !< Parity transmission is disabled */
#define UNICOMMSPI_CTL1_PTEN_ENABLE              ((uint32_t)0x00000100U)         /* !< Parity transmission is enabled */
/* UNICOMMSPI_CTL1[SUSPEND] Bits */
#define UNICOMMSPI_CTL1_SUSPEND_OFS              (9)                             /* !< SUSPEND Offset */
#define UNICOMMSPI_CTL1_SUSPEND_MASK             ((uint32_t)0x00000200U)         /* !< Suspend external communication */
#define UNICOMMSPI_CTL1_SUSPEND_DISABLE          ((uint32_t)0x00000000U)         /* !< Functional mode resumed */
#define UNICOMMSPI_CTL1_SUSPEND_ENABLE           ((uint32_t)0x00000200U)         /* !< External communication suspended */


#ifdef __cplusplus
}
#endif

#endif /* hw_unicommspi__include */
