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

#ifndef hw_eqep__include
#define hw_eqep__include


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
* EQEP Registers
******************************************************************************/


/** @addtogroup EQEP
  @{
*/

typedef struct {
  __IO uint32_t QPOSCNT;                           /* !< (@ 0x00000000) Position Counter */
  __IO uint32_t QPOSINIT;                          /* !< (@ 0x00000004) Position Counter Init */
  __IO uint32_t QPOSMAX;                           /* !< (@ 0x00000008) Maximum Position Count */
  __IO uint32_t QPOSCMP;                           /* !< (@ 0x0000000C) Position Compare */
  __IO uint32_t QPOSILAT;                          /* !< (@ 0x00000010) Index Position Latch */
  __IO uint32_t QPOSSLAT;                          /* !< (@ 0x00000014) Strobe Position Latch */
  __IO uint32_t QPOSLAT;                           /* !< (@ 0x00000018) Position Latch */
  __IO uint32_t QUTMR;                             /* !< (@ 0x0000001C) QEP Unit Timer */
  __IO uint32_t QUPRD;                             /* !< (@ 0x00000020) QEP Unit Period */
  __IO uint16_t QWDTMR;                            /* !< (@ 0x00000024) QEP Watchdog Timer */
  __IO uint16_t QWDPRD;                            /* !< (@ 0x00000026) QEP Watchdog Period */
  __IO uint16_t QDECCTL;                           /* !< (@ 0x00000028) Quadrature Decoder Control */
  __IO uint16_t QEPCTL;                            /* !< (@ 0x0000002A) QEP Control */
  __IO uint16_t QCAPCTL;                           /* !< (@ 0x0000002C) Qaudrature Capture Control */
  __IO uint16_t QPOSCTL;                           /* !< (@ 0x0000002E) Position Compare Control */
  __IO uint16_t QEINT;                             /* !< (@ 0x00000030) QEP Interrupt Control */
  __IO uint16_t QFLG;                              /* !< (@ 0x00000032) QEP Interrupt Flag */
  __IO uint16_t QCLR;                              /* !< (@ 0x00000034) QEP Interrupt Clear */
  __IO uint16_t QFRC;                              /* !< (@ 0x00000036) QEP Interrupt Force */
  __IO uint16_t QEPSTS;                            /* !< (@ 0x00000038) QEP Status */
  __IO uint16_t QCTMR;                             /* !< (@ 0x0000003A) QEP Capture Timer */
  __IO uint16_t QCPRD;                             /* !< (@ 0x0000003C) QEP Capture Period */
  __IO uint16_t QCTMRLAT;                          /* !< (@ 0x0000003E) QEP Capture Latch */
  __IO uint16_t QCPRDLAT;                          /* !< (@ 0x00000040) QEP Capture Period Latch */
       uint16_t RESERVED0[15];
  __IO uint32_t REV;                               /* !< (@ 0x00000060) QEP Revision Number */
  __IO uint32_t QEPSTROBESEL;                      /* !< (@ 0x00000064) QEP Strobe select register */
  __IO uint32_t QMACTRL;                           /* !< (@ 0x00000068) QMA Control register */
  __IO uint32_t QEPSRCSEL;                         /* !< (@ 0x0000006C) QEP Source Select Register */
} EQEP_Regs;

/*@}*/ /* end of group EQEP */



/******************************************************************************
* EQEP Register Offsets
******************************************************************************/
#define EQEP_QPOSCNT                             (0x00000000U)
#define EQEP_QPOSINIT                            (0x00000004U)
#define EQEP_QPOSMAX                             (0x00000008U)
#define EQEP_QPOSCMP                             (0x0000000CU)
#define EQEP_QPOSILAT                            (0x00000010U)
#define EQEP_QPOSSLAT                            (0x00000014U)
#define EQEP_QPOSLAT                             (0x00000018U)
#define EQEP_QUTMR                               (0x0000001CU)
#define EQEP_QUPRD                               (0x00000020U)
#define EQEP_QWDTMR                              (0x00000024U)
#define EQEP_QWDPRD                              (0x00000026U)
#define EQEP_QDECCTL                             (0x00000028U)
#define EQEP_QEPCTL                              (0x0000002AU)
#define EQEP_QCAPCTL                             (0x0000002CU)
#define EQEP_QPOSCTL                             (0x0000002EU)
#define EQEP_QEINT                               (0x00000030U)
#define EQEP_QFLG                                (0x00000032U)
#define EQEP_QCLR                                (0x00000034U)
#define EQEP_QFRC                                (0x00000036U)
#define EQEP_QEPSTS                              (0x00000038U)
#define EQEP_QCTMR                               (0x0000003AU)
#define EQEP_QCPRD                               (0x0000003CU)
#define EQEP_QCTMRLAT                            (0x0000003EU)
#define EQEP_QCPRDLAT                            (0x00000040U)
#define EQEP_REV                                 (0x00000060U)
#define EQEP_QEPSTROBESEL                        (0x00000064U)
#define EQEP_QMACTRL                             (0x00000068U)
#define EQEP_QEPSRCSEL                           (0x0000006CU)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* EQEP Register Control Bits
******************************************************************************/

/* EQEP_QPOSCNT Bits */
/* EQEP_QPOSCNT[QPOSCNT] Bits */
#define EQEP_QPOSCNT_QPOSCNT_OFS                 (0)                             /* !< QPOSCNT Offset */
#define EQEP_QPOSCNT_QPOSCNT_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Position Counter */

/* EQEP_QPOSINIT Bits */
/* EQEP_QPOSINIT[QPOSINIT] Bits */
#define EQEP_QPOSINIT_QPOSINIT_OFS               (0)                             /* !< QPOSINIT Offset */
#define EQEP_QPOSINIT_QPOSINIT_MASK              ((uint32_t)0xFFFFFFFFU)         /* !< Position Counter Init */

/* EQEP_QPOSMAX Bits */
/* EQEP_QPOSMAX[QPOSMAX] Bits */
#define EQEP_QPOSMAX_QPOSMAX_OFS                 (0)                             /* !< QPOSMAX Offset */
#define EQEP_QPOSMAX_QPOSMAX_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Maximum Position Count */

/* EQEP_QPOSCMP Bits */
/* EQEP_QPOSCMP[QPOSCMP] Bits */
#define EQEP_QPOSCMP_QPOSCMP_OFS                 (0)                             /* !< QPOSCMP Offset */
#define EQEP_QPOSCMP_QPOSCMP_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Position Compare */

/* EQEP_QPOSILAT Bits */
/* EQEP_QPOSILAT[QPOSILAT] Bits */
#define EQEP_QPOSILAT_QPOSILAT_OFS               (0)                             /* !< QPOSILAT Offset */
#define EQEP_QPOSILAT_QPOSILAT_MASK              ((uint32_t)0xFFFFFFFFU)         /* !< Index Position Latch */

/* EQEP_QPOSSLAT Bits */
/* EQEP_QPOSSLAT[QPOSSLAT] Bits */
#define EQEP_QPOSSLAT_QPOSSLAT_OFS               (0)                             /* !< QPOSSLAT Offset */
#define EQEP_QPOSSLAT_QPOSSLAT_MASK              ((uint32_t)0xFFFFFFFFU)         /* !< Strobe Position Latch */

/* EQEP_QPOSLAT Bits */
/* EQEP_QPOSLAT[QPOSLAT] Bits */
#define EQEP_QPOSLAT_QPOSLAT_OFS                 (0)                             /* !< QPOSLAT Offset */
#define EQEP_QPOSLAT_QPOSLAT_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Position Latch */

/* EQEP_QUTMR Bits */
/* EQEP_QUTMR[QUTMR] Bits */
#define EQEP_QUTMR_QUTMR_OFS                     (0)                             /* !< QUTMR Offset */
#define EQEP_QUTMR_QUTMR_MASK                    ((uint32_t)0xFFFFFFFFU)         /* !< QEP Unit Timer */

/* EQEP_QUPRD Bits */
/* EQEP_QUPRD[QUPRD] Bits */
#define EQEP_QUPRD_QUPRD_OFS                     (0)                             /* !< QUPRD Offset */
#define EQEP_QUPRD_QUPRD_MASK                    ((uint32_t)0xFFFFFFFFU)         /* !< QEP Unit Period */

/* EQEP_QWDTMR Bits */
/* EQEP_QWDTMR[QWDTMR] Bits */
#define EQEP_QWDTMR_QWDTMR_OFS                   (0)                             /* !< QWDTMR Offset */
#define EQEP_QWDTMR_QWDTMR_MASK                  ((uint16_t)0x0000FFFFU)         /* !< QEP Watchdog Timer */

/* EQEP_QWDPRD Bits */
/* EQEP_QWDPRD[QWDPRD] Bits */
#define EQEP_QWDPRD_QWDPRD_OFS                   (0)                             /* !< QWDPRD Offset */
#define EQEP_QWDPRD_QWDPRD_MASK                  ((uint16_t)0x0000FFFFU)         /* !< QEP Watchdog Period */

/* EQEP_QDECCTL Bits */
/* EQEP_QDECCTL[QIDIRE] Bits */
#define EQEP_QDECCTL_QIDIRE_OFS                  (0)                             /* !< QIDIRE Offset */
#define EQEP_QDECCTL_QIDIRE_MASK                 ((uint16_t)0x00000001U)         /* !< Qep Index Direction Enhancement
                                                                                    enable */
/* EQEP_QDECCTL[QSP] Bits */
#define EQEP_QDECCTL_QSP_OFS                     (5)                             /* !< QSP Offset */
#define EQEP_QDECCTL_QSP_MASK                    ((uint16_t)0x00000020U)         /* !< QEPS input polarity */
#define EQEP_QDECCTL_QSP_QSP_NOPOLAR             ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QDECCTL_QSP_QSP_POLAR               ((uint16_t)0x00000020U)         /* !< Negates QEPS input */
/* EQEP_QDECCTL[QIP] Bits */
#define EQEP_QDECCTL_QIP_OFS                     (6)                             /* !< QIP Offset */
#define EQEP_QDECCTL_QIP_MASK                    ((uint16_t)0x00000040U)         /* !< QEPI input polarity */
#define EQEP_QDECCTL_QIP_QIP_NOPOLAR             ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QDECCTL_QIP_QIP_POLAR               ((uint16_t)0x00000040U)         /* !< Negates QEPI input */
/* EQEP_QDECCTL[QBP] Bits */
#define EQEP_QDECCTL_QBP_OFS                     (7)                             /* !< QBP Offset */
#define EQEP_QDECCTL_QBP_MASK                    ((uint16_t)0x00000080U)         /* !< QEPB input polarity */
#define EQEP_QDECCTL_QBP_QBP_NOPOLAR             ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QDECCTL_QBP_QBP_POLAR               ((uint16_t)0x00000080U)         /* !< Negates QEPB input */
/* EQEP_QDECCTL[QAP] Bits */
#define EQEP_QDECCTL_QAP_OFS                     (8)                             /* !< QAP Offset */
#define EQEP_QDECCTL_QAP_MASK                    ((uint16_t)0x00000100U)         /* !< QEPA input polarity */
#define EQEP_QDECCTL_QAP_QAP_NOPOLAR             ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QDECCTL_QAP_QAP_POLAR               ((uint16_t)0x00000100U)         /* !< Negates QEPA input */
/* EQEP_QDECCTL[IGATE] Bits */
#define EQEP_QDECCTL_IGATE_OFS                   (9)                             /* !< IGATE Offset */
#define EQEP_QDECCTL_IGATE_MASK                  ((uint16_t)0x00000200U)         /* !< Index pulse gating option */
#define EQEP_QDECCTL_IGATE_IGATE_DISABLE         ((uint16_t)0x00000000U)         /* !< Disable gating of Index pulse */
#define EQEP_QDECCTL_IGATE_IGATE_ENABLE          ((uint16_t)0x00000200U)         /* !< Gate the index pin with strobe */
/* EQEP_QDECCTL[SWAP] Bits */
#define EQEP_QDECCTL_SWAP_OFS                    (10)                            /* !< SWAP Offset */
#define EQEP_QDECCTL_SWAP_MASK                   ((uint16_t)0x00000400U)         /* !< CLK/DIR Signal Source for Position
                                                                                    Counter */
#define EQEP_QDECCTL_SWAP_SWAP_DISABLE           ((uint16_t)0x00000000U)         /* !< Quadrature-clock inputs are not
                                                                                    swapped */
#define EQEP_QDECCTL_SWAP_SWAP_ENABLE            ((uint16_t)0x00000400U)         /* !< Quadrature-clock inputs are swapped */
/* EQEP_QDECCTL[XCR] Bits */
#define EQEP_QDECCTL_XCR_OFS                     (11)                            /* !< XCR Offset */
#define EQEP_QDECCTL_XCR_MASK                    ((uint16_t)0x00000800U)         /* !< External Clock Rate */
#define EQEP_QDECCTL_XCR_XCR_2XRESOL             ((uint16_t)0x00000000U)         /* !< 2x resolution: Count the
                                                                                    rising/falling edge */
#define EQEP_QDECCTL_XCR_XCR_1XRESOL             ((uint16_t)0x00000800U)         /* !< 1x resolution: Count the rising
                                                                                    edge only */
/* EQEP_QDECCTL[SPSEL] Bits */
#define EQEP_QDECCTL_SPSEL_OFS                   (12)                            /* !< SPSEL Offset */
#define EQEP_QDECCTL_SPSEL_MASK                  ((uint16_t)0x00001000U)         /* !< Sync output pin selection */
#define EQEP_QDECCTL_SPSEL_INDEX_PIN             ((uint16_t)0x00000000U)         /* !< Index pin is used for sync output */
#define EQEP_QDECCTL_SPSEL_STROBE_PIN            ((uint16_t)0x00001000U)         /* !< Strobe pin is used for sync output */
/* EQEP_QDECCTL[SOEN] Bits */
#define EQEP_QDECCTL_SOEN_OFS                    (13)                            /* !< SOEN Offset */
#define EQEP_QDECCTL_SOEN_MASK                   ((uint16_t)0x00002000U)         /* !< Sync output-enable */
#define EQEP_QDECCTL_SOEN_SYNC_DISABLE           ((uint16_t)0x00000000U)         /* !< Disable position-compare sync
                                                                                    output */
#define EQEP_QDECCTL_SOEN_SYNC_ENABLE            ((uint16_t)0x00002000U)         /* !< Enable position-compare sync output */
/* EQEP_QDECCTL[QSRC] Bits */
#define EQEP_QDECCTL_QSRC_OFS                    (14)                            /* !< QSRC Offset */
#define EQEP_QDECCTL_QSRC_MASK                   ((uint16_t)0x0000C000U)         /* !< Position-counter source selection */
#define EQEP_QDECCTL_QSRC_QUAD_COUNT_MODE        ((uint16_t)0x00000000U)         /* !< Quadrature count mode (QCLK = iCLK,
                                                                                    QDIR = iDIR) */
#define EQEP_QDECCTL_QSRC_DIRECT_COUNT_MODE      ((uint16_t)0x00004000U)         /* !< Direction-count mode (QCLK = xCLK,
                                                                                    QDIR = xDIR) */
#define EQEP_QDECCTL_QSRC_UP_COUNT_MODE          ((uint16_t)0x00008000U)         /* !< UP count mode for frequency
                                                                                    measurement (QCLK = xCLK, QDIR = 1) */
#define EQEP_QDECCTL_QSRC_DOWN_COUNT_MODE        ((uint16_t)0x0000C000U)         /* !< DOWN count mode for frequency
                                                                                    measurement (QCLK = xCLK, QDIR = 0) */

/* EQEP_QEPCTL Bits */
/* EQEP_QEPCTL[WDE] Bits */
#define EQEP_QEPCTL_WDE_OFS                      (0)                             /* !< WDE Offset */
#define EQEP_QEPCTL_WDE_MASK                     ((uint16_t)0x00000001U)         /* !< QEP watchdog enable */
#define EQEP_QEPCTL_WDE_WDE_DISABLE              ((uint16_t)0x00000000U)         /* !< Disable the eQEP watchdog timer */
#define EQEP_QEPCTL_WDE_WDE_ENABLE               ((uint16_t)0x00000001U)         /* !< Enable the eQEP watchdog timer */
/* EQEP_QEPCTL[UTE] Bits */
#define EQEP_QEPCTL_UTE_OFS                      (1)                             /* !< UTE Offset */
#define EQEP_QEPCTL_UTE_MASK                     ((uint16_t)0x00000002U)         /* !< QEP unit timer enable */
#define EQEP_QEPCTL_UTE_UTE_DISABLE              ((uint16_t)0x00000000U)         /* !< Disable eQEP unit timer */
#define EQEP_QEPCTL_UTE_UTE_ENABLE               ((uint16_t)0x00000002U)         /* !< Enable unit timer */
/* EQEP_QEPCTL[QCLM] Bits */
#define EQEP_QEPCTL_QCLM_OFS                     (2)                             /* !< QCLM Offset */
#define EQEP_QEPCTL_QCLM_MASK                    ((uint16_t)0x00000004U)         /* !< QEP capture latch mode */
#define EQEP_QEPCTL_QCLM_QCLM_CPU                ((uint16_t)0x00000000U)         /* !< Latch on position counter read by
                                                                                    CPU. Capture timer and capture period
                                                                                    values are latched into QCTMRLAT and
                                                                                    QCPRDLAT registers when CPU reads the
                                                                                    QPOSCNT register. */
#define EQEP_QEPCTL_QCLM_QCLM_TIMEOUT            ((uint16_t)0x00000004U)         /* !< Latch on unit time out. Position
                                                                                    counter, capture timer and capture
                                                                                    period values are latched into
                                                                                    QPOSLAT, QCTMRLAT and QCPRDLAT
                                                                                    registers on unit time out. */
/* EQEP_QEPCTL[QPEN] Bits */
#define EQEP_QEPCTL_QPEN_OFS                     (3)                             /* !< QPEN Offset */
#define EQEP_QEPCTL_QPEN_MASK                    ((uint16_t)0x00000008U)         /* !< Quadrature postotion counter enable */
#define EQEP_QEPCTL_QPEN_QPEN_RESET              ((uint16_t)0x00000000U)         /* !< Reset the eQEP peripheral internal
                                                                                    operating flags/read-only registers.
                                                                                    Control/configuration registers are
                                                                                    not disturbed by a software reset.
                                                                                    #br#When QPEN is disabled, some flags
                                                                                    in the QFLG register do not get reset
                                                                                    or cleared and show the actual state
                                                                                    of that flag. */
#define EQEP_QEPCTL_QPEN_QPEN_ENABLE             ((uint16_t)0x00000008U)         /* !< eQEP position counter is enabled */
/* EQEP_QEPCTL[IEL] Bits */
#define EQEP_QEPCTL_IEL_OFS                      (4)                             /* !< IEL Offset */
#define EQEP_QEPCTL_IEL_MASK                     ((uint16_t)0x00000030U)         /* !< Index event latch */
#define EQEP_QEPCTL_IEL_IEL_POSRISING            ((uint16_t)0x00000010U)         /* !< Latches position counter on rising
                                                                                    edge of the index signal */
#define EQEP_QEPCTL_IEL_IEL_POSFALLING           ((uint16_t)0x00000020U)         /* !< Latches position counter on falling
                                                                                    edge of the index signal */
#define EQEP_QEPCTL_IEL_IEL_SIM                  ((uint16_t)0x00000030U)         /* !< Software index marker. Latches the
                                                                                    position counter and quadrature
                                                                                    direction flag on index event marker.
                                                                                    The position counter is latched to
                                                                                    the QPOSILAT register and the
                                                                                    direction flag is latched in the
                                                                                    QEPSTS[QDLF] bit. This mode is useful
                                                                                    for software index marking. */
/* EQEP_QEPCTL[SEL] Bits */
#define EQEP_QEPCTL_SEL_OFS                      (6)                             /* !< SEL Offset */
#define EQEP_QEPCTL_SEL_MASK                     ((uint16_t)0x00000040U)         /* !< Strobe event latch */
#define EQEP_QEPCTL_SEL_SEL_QEPSRISING           ((uint16_t)0x00000000U)         /* !< The position counter is latched on
                                                                                    the rising edge of QEPS strobe
                                                                                    (QPOSSLAT = POSCCNT). Latching on the
                                                                                    falling edge can be done by inverting
                                                                                    the strobe input using the QSP bit in
                                                                                    the QDECCTL register */
#define EQEP_QEPCTL_SEL_SEL_QEPSCLOCK            ((uint16_t)0x00000040U)         /* !< Clockwise Direction: #br#Position
                                                                                    counter is latched on rising edge of
                                                                                    QEPS strobe #br#Counter Clockwise
                                                                                    Direction: #br#Position counter is
                                                                                    latched on falling edge of QEPS
                                                                                    strobe */
/* EQEP_QEPCTL[SWI] Bits */
#define EQEP_QEPCTL_SWI_OFS                      (7)                             /* !< SWI Offset */
#define EQEP_QEPCTL_SWI_MASK                     ((uint16_t)0x00000080U)         /* !< Software init position counter */
#define EQEP_QEPCTL_SWI_SWI_NOTHING              ((uint16_t)0x00000000U)         /* !< Do nothing (action disabled) */
#define EQEP_QEPCTL_SWI_SWI_INITPOS              ((uint16_t)0x00000080U)         /* !< Initialize position counter
                                                                                    (QPOSCNT=QPOSINIT). This bit is not
                                                                                    cleared automatically */
/* EQEP_QEPCTL[IEI] Bits */
#define EQEP_QEPCTL_IEI_OFS                      (8)                             /* !< IEI Offset */
#define EQEP_QEPCTL_IEI_MASK                     ((uint16_t)0x00000300U)         /* !< Index event init of position count */
#define EQEP_QEPCTL_IEI_IEI_NOTHING0             ((uint16_t)0x00000000U)         /* !< Do nothing (action disabled) */
#define EQEP_QEPCTL_IEI_IEI_NOTHING1             ((uint16_t)0x00000100U)         /* !< Do nothing (action disabled) */
#define EQEP_QEPCTL_IEI_IEI_INITRISING           ((uint16_t)0x00000200U)         /* !< Initializes the position counter on
                                                                                    the rising edge of the QEPI signal
                                                                                    (QPOSCNT = QPOSINIT) */
#define EQEP_QEPCTL_IEI_IEI_INITFALLING          ((uint16_t)0x00000300U)         /* !< Initializes the position counter on
                                                                                    the falling edge of QEPI signal
                                                                                    (QPOSCNT = QPOSINIT) */
/* EQEP_QEPCTL[SEI] Bits */
#define EQEP_QEPCTL_SEI_OFS                      (10)                            /* !< SEI Offset */
#define EQEP_QEPCTL_SEI_MASK                     ((uint16_t)0x00000C00U)         /* !< Strobe event init */
#define EQEP_QEPCTL_SEI_SEI_NOTHING0             ((uint16_t)0x00000000U)         /* !< Does nothing (action disabled) */
#define EQEP_QEPCTL_SEI_SEI_NOTHING1             ((uint16_t)0x00000400U)         /* !< Does nothing (action disabled) */
#define EQEP_QEPCTL_SEI_SEI_INITQEPSRISING       ((uint16_t)0x00000800U)         /* !< Initializes the position counter on
                                                                                    rising edge of the QEPS signal */
#define EQEP_QEPCTL_SEI_SEI_INITQEPSCLOCK        ((uint16_t)0x00000C00U)         /* !< Clockwise Direction:
                                                                                    #br#Initializes the position counter
                                                                                    on the rising edge of QEPS strobe
                                                                                    #br#Counter Clockwise Direction:
                                                                                    #br#Initializes the position counter
                                                                                    on the falling edge of QEPS strobe */
/* EQEP_QEPCTL[PCRM] Bits */
#define EQEP_QEPCTL_PCRM_OFS                     (12)                            /* !< PCRM Offset */
#define EQEP_QEPCTL_PCRM_MASK                    ((uint16_t)0x00003000U)         /* !< Postion counter reset */
#define EQEP_QEPCTL_PCRM_PCRM_INDEX              ((uint16_t)0x00000000U)         /* !< Position counter reset on an index
                                                                                    event */
#define EQEP_QEPCTL_PCRM_PCRM_MAXPOS             ((uint16_t)0x00001000U)         /* !< Position counter reset on the
                                                                                    maximum position */
#define EQEP_QEPCTL_PCRM_PCRM_FIRSTINDEX         ((uint16_t)0x00002000U)         /* !< Position counter reset on the first
                                                                                    index event */
#define EQEP_QEPCTL_PCRM_PCRM_TIMEEVENT          ((uint16_t)0x00003000U)         /* !< Position counter reset on a unit
                                                                                    time event */
/* EQEP_QEPCTL[FREE_SOFT] Bits */
#define EQEP_QEPCTL_FREE_SOFT_OFS                (14)                            /* !< FREE_SOFT Offset */
#define EQEP_QEPCTL_FREE_SOFT_MASK               ((uint16_t)0x0000C000U)         /* !< Emulation mode */
#define EQEP_QEPCTL_FREE_SOFT_FREE_SOFT_0        ((uint16_t)0x00000000U)         /* !< QPOSCNT behavior #br#Position
                                                                                    counter stops immediately on
                                                                                    emulation suspend #br#0h (R/W) =
                                                                                    QWDTMR behavior #br#Watchdog counter
                                                                                    stops immediately #br#0h (R/W) =
                                                                                    QUTMR behavior #br#Unit timer stops
                                                                                    immediately #br#0h (R/W) = QCTMR
                                                                                    behavior #br#Capture Timer stops
                                                                                    immediately */
#define EQEP_QEPCTL_FREE_SOFT_FREE_SOFT_1        ((uint16_t)0x00004000U)         /* !< QPOSCNT behavior #br#Position
                                                                                    counter continues to count until the
                                                                                    rollover #br#1h (R/W) = QWDTMR
                                                                                    behavior #br#Watchdog counter counts
                                                                                    until WD period match roll over
                                                                                    #br#1h (R/W) = QUTMR behavior
                                                                                    #br#Unit timer counts until period
                                                                                    rollover #br#1h (R/W) = QCTMR
                                                                                    behavior #br#Capture Timer counts
                                                                                    until next unit period event */
#define EQEP_QEPCTL_FREE_SOFT_FREE_SOFT_2        ((uint16_t)0x00008000U)         /* !< QPOSCNT behavior #br#Position
                                                                                    counter is unaffected by emulation
                                                                                    suspend #br#2h (R/W) = QWDTMR
                                                                                    behavior #br#Watchdog counter is
                                                                                    unaffected by emulation suspend
                                                                                    #br#2h (R/W) = QUTMR behavior
                                                                                    #br#Unit timer is unaffected by
                                                                                    emulation suspend #br#2h (R/W) =
                                                                                    QCTMR behavior #br#Capture Timer is
                                                                                    unaffected by emulation suspend */
#define EQEP_QEPCTL_FREE_SOFT_FREE_SOFT_3        ((uint16_t)0x0000C000U)         /* !< Same as FREE_SOFT_2 */

/* EQEP_QCAPCTL Bits */
/* EQEP_QCAPCTL[UPPS] Bits */
#define EQEP_QCAPCTL_UPPS_OFS                    (0)                             /* !< UPPS Offset */
#define EQEP_QCAPCTL_UPPS_MASK                   ((uint16_t)0x0000000FU)         /* !< Unit position event prescaler */
#define EQEP_QCAPCTL_UPPS_QCLK1                  ((uint16_t)0x00000000U)         /* !< UPEVNT = QCLK/1 */
#define EQEP_QCAPCTL_UPPS_QCLK2                  ((uint16_t)0x00000001U)         /* !< UPEVNT = QCLK/2 */
#define EQEP_QCAPCTL_UPPS_QCLK4                  ((uint16_t)0x00000002U)         /* !< UPEVNT = QCLK/4 */
#define EQEP_QCAPCTL_UPPS_QCLK8                  ((uint16_t)0x00000003U)         /* !< UPEVNT = QCLK/8 */
#define EQEP_QCAPCTL_UPPS_QCLK16                 ((uint16_t)0x00000004U)         /* !< UPEVNT = QCLK/16 */
#define EQEP_QCAPCTL_UPPS_QCLK32                 ((uint16_t)0x00000005U)         /* !< UPEVNT = QCLK/32 */
#define EQEP_QCAPCTL_UPPS_QCLK64                 ((uint16_t)0x00000006U)         /* !< UPEVNT = QCLK/64 */
#define EQEP_QCAPCTL_UPPS_QCLK128                ((uint16_t)0x00000007U)         /* !< UPEVNT = QCLK/128 */
#define EQEP_QCAPCTL_UPPS_QCLK256                ((uint16_t)0x00000008U)         /* !< UPEVNT = QCLK/256 */
#define EQEP_QCAPCTL_UPPS_QCLK512                ((uint16_t)0x00000009U)         /* !< UPEVNT = QCLK/512 */
#define EQEP_QCAPCTL_UPPS_QCLK1024               ((uint16_t)0x0000000AU)         /* !< UPEVNT = QCLK/1024 */
#define EQEP_QCAPCTL_UPPS_QCLK2048               ((uint16_t)0x0000000BU)         /* !< UPEVNT = QCLK/2048 */
/* EQEP_QCAPCTL[CCPS] Bits */
#define EQEP_QCAPCTL_CCPS_OFS                    (4)                             /* !< CCPS Offset */
#define EQEP_QCAPCTL_CCPS_MASK                   ((uint16_t)0x00000070U)         /* !< eQEP capture timer clock prescaler */
#define EQEP_QCAPCTL_CCPS_SYSCLKOUT1             ((uint16_t)0x00000000U)         /* !< CAPCLK = SYSCLKOUT/1 */
#define EQEP_QCAPCTL_CCPS_SYSCLKOUT2             ((uint16_t)0x00000010U)         /* !< CAPCLK = SYSCLKOUT/2 */
#define EQEP_QCAPCTL_CCPS_SYSCLKOUT4             ((uint16_t)0x00000020U)         /* !< CAPCLK = SYSCLKOUT/4 */
#define EQEP_QCAPCTL_CCPS_SYSCLKOUT8             ((uint16_t)0x00000030U)         /* !< CAPCLK = SYSCLKOUT/8 */
#define EQEP_QCAPCTL_CCPS_SYSCLKOUT16            ((uint16_t)0x00000040U)         /* !< CAPCLK = SYSCLKOUT/16 */
#define EQEP_QCAPCTL_CCPS_SYSCLKOUT32            ((uint16_t)0x00000050U)         /* !< CAPCLK = SYSCLKOUT/32 */
#define EQEP_QCAPCTL_CCPS_SYSCLKOUT64            ((uint16_t)0x00000060U)         /* !< CAPCLK = SYSCLKOUT/64 */
#define EQEP_QCAPCTL_CCPS_SYSCLKOUT128           ((uint16_t)0x00000070U)         /* !< CAPCLK = SYSCLKOUT/128 */
/* EQEP_QCAPCTL[CEN] Bits */
#define EQEP_QCAPCTL_CEN_OFS                     (15)                            /* !< CEN Offset */
#define EQEP_QCAPCTL_CEN_MASK                    ((uint16_t)0x00008000U)         /* !< Enable eQEP capture */
#define EQEP_QCAPCTL_CEN_CEN_DISABLE             ((uint16_t)0x00000000U)         /* !< eQEP capture unit is disabled */
#define EQEP_QCAPCTL_CEN_CEN_ENABLE              ((uint16_t)0x00008000U)         /* !< eQEP capture unit is enabled */

/* EQEP_QPOSCTL Bits */
/* EQEP_QPOSCTL[PCSPW] Bits */
#define EQEP_QPOSCTL_PCSPW_OFS                   (0)                             /* !< PCSPW Offset */
#define EQEP_QPOSCTL_PCSPW_MASK                  ((uint16_t)0x00000FFFU)         /* !< Position compare sync pulse width */
#define EQEP_QPOSCTL_PCSPW_SYSCLKOUT4            ((uint16_t)0x00000000U)         /* !< 1 * 4 * SYSCLKOUT cycles */
#define EQEP_QPOSCTL_PCSPW_SYSCLKOUT8            ((uint16_t)0x00000001U)         /* !< 2 * 4 * SYSCLKOUT cycles */
#define EQEP_QPOSCTL_PCSPW_SYSCLKOUT16384        ((uint16_t)0x00000FFFU)         /* !< 4096 * 4 * SYSCLKOUT cycles */
/* EQEP_QPOSCTL[PCE] Bits */
#define EQEP_QPOSCTL_PCE_OFS                     (12)                            /* !< PCE Offset */
#define EQEP_QPOSCTL_PCE_MASK                    ((uint16_t)0x00001000U)         /* !< Position compare enable/disable */
#define EQEP_QPOSCTL_PCE_PCE_DISABLE             ((uint16_t)0x00000000U)         /* !< Disable position compare unit */
#define EQEP_QPOSCTL_PCE_PCE_ENABLE              ((uint16_t)0x00001000U)         /* !< Enable position compare unit */
/* EQEP_QPOSCTL[PCPOL] Bits */
#define EQEP_QPOSCTL_PCPOL_OFS                   (13)                            /* !< PCPOL Offset */
#define EQEP_QPOSCTL_PCPOL_MASK                  ((uint16_t)0x00002000U)         /* !< Polarity of sync output */
#define EQEP_QPOSCTL_PCPOL_PCPOL_HIGH            ((uint16_t)0x00000000U)         /* !< Active HIGH pulse output */
#define EQEP_QPOSCTL_PCPOL_PCPOL_LOW             ((uint16_t)0x00002000U)         /* !< Active LOW pulse output */
/* EQEP_QPOSCTL[PCLOAD] Bits */
#define EQEP_QPOSCTL_PCLOAD_OFS                  (14)                            /* !< PCLOAD Offset */
#define EQEP_QPOSCTL_PCLOAD_MASK                 ((uint16_t)0x00004000U)         /* !< Position compare of shadow load */
#define EQEP_QPOSCTL_PCLOAD_PCLOAD_0             ((uint16_t)0x00000000U)         /* !< Load on QPOSCNT = 0 */
#define EQEP_QPOSCTL_PCLOAD_PCLOAD_QPOSCMP       ((uint16_t)0x00004000U)         /* !< Load when QPOSCNT = QPOSCMP */
/* EQEP_QPOSCTL[PCSHDW] Bits */
#define EQEP_QPOSCTL_PCSHDW_OFS                  (15)                            /* !< PCSHDW Offset */
#define EQEP_QPOSCTL_PCSHDW_MASK                 ((uint16_t)0x00008000U)         /* !< Position compare of shadow enable */
#define EQEP_QPOSCTL_PCSHDW_PCSHDW_DISABLE       ((uint16_t)0x00000000U)         /* !< Shadow disabled, load Immediate */
#define EQEP_QPOSCTL_PCSHDW_PCSHDW_ENABLE        ((uint16_t)0x00008000U)         /* !< Shadow enabled */

/* EQEP_QEINT Bits */
/* EQEP_QEINT[PCE] Bits */
#define EQEP_QEINT_PCE_OFS                       (1)                             /* !< PCE Offset */
#define EQEP_QEINT_PCE_MASK                      ((uint16_t)0x00000002U)         /* !< Position counter error interrupt
                                                                                    enable */
#define EQEP_QEINT_PCE_PCE_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_PCE_PCE_ENABLE                ((uint16_t)0x00000002U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[QPE] Bits */
#define EQEP_QEINT_QPE_OFS                       (2)                             /* !< QPE Offset */
#define EQEP_QEINT_QPE_MASK                      ((uint16_t)0x00000004U)         /* !< Quadrature phase error interrupt
                                                                                    enable */
#define EQEP_QEINT_QPE_QPE_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_QPE_QPE_ENABLE                ((uint16_t)0x00000004U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[QDC] Bits */
#define EQEP_QEINT_QDC_OFS                       (3)                             /* !< QDC Offset */
#define EQEP_QEINT_QDC_MASK                      ((uint16_t)0x00000008U)         /* !< Quadrature direction change
                                                                                    interrupt enable */
#define EQEP_QEINT_QDC_QDC_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_QDC_QDC_ENABLE                ((uint16_t)0x00000008U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[WTO] Bits */
#define EQEP_QEINT_WTO_OFS                       (4)                             /* !< WTO Offset */
#define EQEP_QEINT_WTO_MASK                      ((uint16_t)0x00000010U)         /* !< Watchdog time out interrupt enable */
#define EQEP_QEINT_WTO_WTO_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_WTO_WTO_ENABLE                ((uint16_t)0x00000010U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[PCU] Bits */
#define EQEP_QEINT_PCU_OFS                       (5)                             /* !< PCU Offset */
#define EQEP_QEINT_PCU_MASK                      ((uint16_t)0x00000020U)         /* !< Position counter underflow
                                                                                    interrupt enable */
#define EQEP_QEINT_PCU_PCU_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_PCU_PCU_ENABLE                ((uint16_t)0x00000020U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[PCO] Bits */
#define EQEP_QEINT_PCO_OFS                       (6)                             /* !< PCO Offset */
#define EQEP_QEINT_PCO_MASK                      ((uint16_t)0x00000040U)         /* !< Position counter overflow interrupt
                                                                                    enable */
#define EQEP_QEINT_PCO_PCO_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_PCO_PCO_ENABLE                ((uint16_t)0x00000040U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[PCR] Bits */
#define EQEP_QEINT_PCR_OFS                       (7)                             /* !< PCR Offset */
#define EQEP_QEINT_PCR_MASK                      ((uint16_t)0x00000080U)         /* !< Position-compare ready interrupt
                                                                                    enable */
#define EQEP_QEINT_PCR_PCR_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_PCR_PCR_ENABLE                ((uint16_t)0x00000080U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[PCM] Bits */
#define EQEP_QEINT_PCM_OFS                       (8)                             /* !< PCM Offset */
#define EQEP_QEINT_PCM_MASK                      ((uint16_t)0x00000100U)         /* !< Position-compare match interrupt
                                                                                    enable */
#define EQEP_QEINT_PCM_PCM_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_PCM_PCM_ENABLE                ((uint16_t)0x00000100U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[SEL] Bits */
#define EQEP_QEINT_SEL_OFS                       (9)                             /* !< SEL Offset */
#define EQEP_QEINT_SEL_MASK                      ((uint16_t)0x00000200U)         /* !< Strobe event latch interrupt enable */
#define EQEP_QEINT_SEL_SEL_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_SEL_SEL_ENABLE                ((uint16_t)0x00000200U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[IEL] Bits */
#define EQEP_QEINT_IEL_OFS                       (10)                            /* !< IEL Offset */
#define EQEP_QEINT_IEL_MASK                      ((uint16_t)0x00000400U)         /* !< Index event latch interrupt enable */
#define EQEP_QEINT_IEL_IEL_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_IEL_IEL_ENABLE                ((uint16_t)0x00000400U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[UTO] Bits */
#define EQEP_QEINT_UTO_OFS                       (11)                            /* !< UTO Offset */
#define EQEP_QEINT_UTO_MASK                      ((uint16_t)0x00000800U)         /* !< Unit time out interrupt enable */
#define EQEP_QEINT_UTO_UTO_DISABLE               ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_UTO_UTO_ENABLE                ((uint16_t)0x00000800U)         /* !< Interrupt is enabled */
/* EQEP_QEINT[QMAE] Bits */
#define EQEP_QEINT_QMAE_OFS                      (12)                            /* !< QMAE Offset */
#define EQEP_QEINT_QMAE_MASK                     ((uint16_t)0x00001000U)         /* !< QMA error interrupt enable */
#define EQEP_QEINT_QMAE_QMAE_DISABLE             ((uint16_t)0x00000000U)         /* !< Interrupt is disabled */
#define EQEP_QEINT_QMAE_QMAE_ENABLE              ((uint16_t)0x00001000U)         /* !< Interrupt is enabled */

/* EQEP_QFLG Bits */
/* EQEP_QFLG[INT] Bits */
#define EQEP_QFLG_INT_OFS                        (0)                             /* !< INT Offset */
#define EQEP_QFLG_INT_MASK                       ((uint16_t)0x00000001U)         /* !< Global interrupt status flag */
#define EQEP_QFLG_INT_INT_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_INT_INT_FLAG                   ((uint16_t)0x00000001U)         /* !< Interrupt was generated */
/* EQEP_QFLG[PCE] Bits */
#define EQEP_QFLG_PCE_OFS                        (1)                             /* !< PCE Offset */
#define EQEP_QFLG_PCE_MASK                       ((uint16_t)0x00000002U)         /* !< Position counter error interrupt
                                                                                    flag */
#define EQEP_QFLG_PCE_PCE_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_PCE_PCE_FLAG                   ((uint16_t)0x00000002U)         /* !< Position counter error */
/* EQEP_QFLG[PHE] Bits */
#define EQEP_QFLG_PHE_OFS                        (2)                             /* !< PHE Offset */
#define EQEP_QFLG_PHE_MASK                       ((uint16_t)0x00000004U)         /* !< Quadrature phase error interrupt
                                                                                    flag */
#define EQEP_QFLG_PHE_PHE_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_PHE_PHE_FLAG                   ((uint16_t)0x00000004U)         /* !< Set on simultaneous transition of
                                                                                    QEPA and QEPB */
/* EQEP_QFLG[QDC] Bits */
#define EQEP_QFLG_QDC_OFS                        (3)                             /* !< QDC Offset */
#define EQEP_QFLG_QDC_MASK                       ((uint16_t)0x00000008U)         /* !< Quadrature direction change
                                                                                    interrupt flag */
#define EQEP_QFLG_QDC_QDC_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_QDC_QDC_FLAG                   ((uint16_t)0x00000008U)         /* !< Interrupt was generated */
/* EQEP_QFLG[WTO] Bits */
#define EQEP_QFLG_WTO_OFS                        (4)                             /* !< WTO Offset */
#define EQEP_QFLG_WTO_MASK                       ((uint16_t)0x00000010U)         /* !< Watchdog timeout interrupt flag */
#define EQEP_QFLG_WTO_WTO_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_WTO_WTO_FLAG                   ((uint16_t)0x00000010U)         /* !< Set by watchdog timeout */
/* EQEP_QFLG[PCU] Bits */
#define EQEP_QFLG_PCU_OFS                        (5)                             /* !< PCU Offset */
#define EQEP_QFLG_PCU_MASK                       ((uint16_t)0x00000020U)         /* !< Position counter underflow
                                                                                    interrupt flag */
#define EQEP_QFLG_PCU_PCU_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_PCU_PCU_FLAG                   ((uint16_t)0x00000020U)         /* !< This bit is set on position counter
                                                                                    underflow. */
/* EQEP_QFLG[PCO] Bits */
#define EQEP_QFLG_PCO_OFS                        (6)                             /* !< PCO Offset */
#define EQEP_QFLG_PCO_MASK                       ((uint16_t)0x00000040U)         /* !< Position counter overflow interrupt
                                                                                    flag */
#define EQEP_QFLG_PCO_PCO_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_PCO_PCO_FLAG                   ((uint16_t)0x00000040U)         /* !< This bit is set on position counter
                                                                                    overflow. */
/* EQEP_QFLG[PCR] Bits */
#define EQEP_QFLG_PCR_OFS                        (7)                             /* !< PCR Offset */
#define EQEP_QFLG_PCR_MASK                       ((uint16_t)0x00000080U)         /* !< Position-compare ready interrupt
                                                                                    flag */
#define EQEP_QFLG_PCR_PCR_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_PCR_PCR_FLAG                   ((uint16_t)0x00000080U)         /* !< This bit is set after transferring
                                                                                    the shadow register value to the
                                                                                    active position compare register */
/* EQEP_QFLG[PCM] Bits */
#define EQEP_QFLG_PCM_OFS                        (8)                             /* !< PCM Offset */
#define EQEP_QFLG_PCM_MASK                       ((uint16_t)0x00000100U)         /* !< eQEP compare match event interrupt
                                                                                    flag */
#define EQEP_QFLG_PCM_PCM_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_PCM_PCM_FLAG                   ((uint16_t)0x00000100U)         /* !< This bit is set on position-compare
                                                                                    match */
/* EQEP_QFLG[SEL] Bits */
#define EQEP_QFLG_SEL_OFS                        (9)                             /* !< SEL Offset */
#define EQEP_QFLG_SEL_MASK                       ((uint16_t)0x00000200U)         /* !< Strobe event latch interrupt flag */
#define EQEP_QFLG_SEL_SEL_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_SEL_SEL_FLAG                   ((uint16_t)0x00000200U)         /* !< This bit is set after latching the
                                                                                    QPOSCNT to QPOSSLAT */
/* EQEP_QFLG[IEL] Bits */
#define EQEP_QFLG_IEL_OFS                        (10)                            /* !< IEL Offset */
#define EQEP_QFLG_IEL_MASK                       ((uint16_t)0x00000400U)         /* !< Index event latch interrupt flag */
#define EQEP_QFLG_IEL_IEL_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_IEL_IEL_FLAG                   ((uint16_t)0x00000400U)         /* !< This bit is set after latching the
                                                                                    QPOSCNT to QPOSILAT */
/* EQEP_QFLG[UTO] Bits */
#define EQEP_QFLG_UTO_OFS                        (11)                            /* !< UTO Offset */
#define EQEP_QFLG_UTO_MASK                       ((uint16_t)0x00000800U)         /* !< Unit time out interrupt flag */
#define EQEP_QFLG_UTO_UTO_NOFLAG                 ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_UTO_UTO_FLAG                   ((uint16_t)0x00000800U)         /* !< Set by eQEP unit timer period match */
/* EQEP_QFLG[QMAE] Bits */
#define EQEP_QFLG_QMAE_OFS                       (12)                            /* !< QMAE Offset */
#define EQEP_QFLG_QMAE_MASK                      ((uint16_t)0x00001000U)         /* !< QMA error interrupt flag */
#define EQEP_QFLG_QMAE_QMAE_NOFLAG               ((uint16_t)0x00000000U)         /* !< No interrupt generated */
#define EQEP_QFLG_QMAE_QMAE_FLAG                 ((uint16_t)0x00001000U)         /* !< Interrupt was generated */

/* EQEP_QCLR Bits */
/* EQEP_QCLR[INT] Bits */
#define EQEP_QCLR_INT_OFS                        (0)                             /* !< INT Offset */
#define EQEP_QCLR_INT_MASK                       ((uint16_t)0x00000001U)         /* !< Global interrupt clear flag */
#define EQEP_QCLR_INT_INT_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_INT_INT_CLR                    ((uint16_t)0x00000001U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[PCE] Bits */
#define EQEP_QCLR_PCE_OFS                        (1)                             /* !< PCE Offset */
#define EQEP_QCLR_PCE_MASK                       ((uint16_t)0x00000002U)         /* !< Clear position counter error
                                                                                    interrupt flag */
#define EQEP_QCLR_PCE_PCE_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_PCE_PCE_CLR                    ((uint16_t)0x00000002U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[PHE] Bits */
#define EQEP_QCLR_PHE_OFS                        (2)                             /* !< PHE Offset */
#define EQEP_QCLR_PHE_MASK                       ((uint16_t)0x00000004U)         /* !< Clear quadrature phase error
                                                                                    interrupt flag */
#define EQEP_QCLR_PHE_PHE_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_PHE_PHE_CLR                    ((uint16_t)0x00000004U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[QDC] Bits */
#define EQEP_QCLR_QDC_OFS                        (3)                             /* !< QDC Offset */
#define EQEP_QCLR_QDC_MASK                       ((uint16_t)0x00000008U)         /* !< Clear quadrature direction change
                                                                                    interrupt flag */
#define EQEP_QCLR_QDC_QDC_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_QDC_QDC_CLR                    ((uint16_t)0x00000008U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[WTO] Bits */
#define EQEP_QCLR_WTO_OFS                        (4)                             /* !< WTO Offset */
#define EQEP_QCLR_WTO_MASK                       ((uint16_t)0x00000010U)         /* !< Clear watchdog timeout interrupt
                                                                                    flag */
#define EQEP_QCLR_WTO_WTO_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_WTO_WTO_CLR                    ((uint16_t)0x00000010U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[PCU] Bits */
#define EQEP_QCLR_PCU_OFS                        (5)                             /* !< PCU Offset */
#define EQEP_QCLR_PCU_MASK                       ((uint16_t)0x00000020U)         /* !< Clear position counter underflow
                                                                                    interrupt flag */
#define EQEP_QCLR_PCU_PCU_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_PCU_PCU_CLR                    ((uint16_t)0x00000020U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[PCO] Bits */
#define EQEP_QCLR_PCO_OFS                        (6)                             /* !< PCO Offset */
#define EQEP_QCLR_PCO_MASK                       ((uint16_t)0x00000040U)         /* !< Clear position counter overflow
                                                                                    interrupt flag */
#define EQEP_QCLR_PCO_PCO_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_PCO_PCO_CLR                    ((uint16_t)0x00000040U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[PCR] Bits */
#define EQEP_QCLR_PCR_OFS                        (7)                             /* !< PCR Offset */
#define EQEP_QCLR_PCR_MASK                       ((uint16_t)0x00000080U)         /* !< Clear position-compare ready
                                                                                    interrupt flag */
#define EQEP_QCLR_PCR_PCR_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_PCR_PCR_CLR                    ((uint16_t)0x00000080U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[PCM] Bits */
#define EQEP_QCLR_PCM_OFS                        (8)                             /* !< PCM Offset */
#define EQEP_QCLR_PCM_MASK                       ((uint16_t)0x00000100U)         /* !< Clear eQEP compare match event
                                                                                    interrupt flag */
#define EQEP_QCLR_PCM_PCM_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_PCM_PCM_CLR                    ((uint16_t)0x00000100U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[SEL] Bits */
#define EQEP_QCLR_SEL_OFS                        (9)                             /* !< SEL Offset */
#define EQEP_QCLR_SEL_MASK                       ((uint16_t)0x00000200U)         /* !< Clear strobe event latch interrupt
                                                                                    flag */
#define EQEP_QCLR_SEL_SEL_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_SEL_SEL_CLR                    ((uint16_t)0x00000200U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[IEL] Bits */
#define EQEP_QCLR_IEL_OFS                        (10)                            /* !< IEL Offset */
#define EQEP_QCLR_IEL_MASK                       ((uint16_t)0x00000400U)         /* !< Clear index event latch interrupt
                                                                                    flag */
#define EQEP_QCLR_IEL_IEL_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_IEL_IEL_CLR                    ((uint16_t)0x00000400U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[UTO] Bits */
#define EQEP_QCLR_UTO_OFS                        (11)                            /* !< UTO Offset */
#define EQEP_QCLR_UTO_MASK                       ((uint16_t)0x00000800U)         /* !< Clear unit time out interrupt flag */
#define EQEP_QCLR_UTO_UTO_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_UTO_UTO_CLR                    ((uint16_t)0x00000800U)         /* !< Clears the interrupt flag */
/* EQEP_QCLR[QMAE] Bits */
#define EQEP_QCLR_QMAE_OFS                       (12)                            /* !< QMAE Offset */
#define EQEP_QCLR_QMAE_MASK                      ((uint16_t)0x00001000U)         /* !< Clear QMA error interrupt flag */
#define EQEP_QCLR_QMAE_QMAE_NOEFFECT             ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QCLR_QMAE_QMAE_CLR                  ((uint16_t)0x00001000U)         /* !< Clears the interrupt flag */

/* EQEP_QFRC Bits */
/* EQEP_QFRC[PCE] Bits */
#define EQEP_QFRC_PCE_OFS                        (1)                             /* !< PCE Offset */
#define EQEP_QFRC_PCE_MASK                       ((uint16_t)0x00000002U)         /* !< Force position counter error
                                                                                    interrupt */
#define EQEP_QFRC_PCE_PCE_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_PCE_PCE_FORCE                  ((uint16_t)0x00000002U)         /* !< Force the interrupt */
/* EQEP_QFRC[PHE] Bits */
#define EQEP_QFRC_PHE_OFS                        (2)                             /* !< PHE Offset */
#define EQEP_QFRC_PHE_MASK                       ((uint16_t)0x00000004U)         /* !< Force quadrature phase error
                                                                                    interrupt */
#define EQEP_QFRC_PHE_PHE_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_PHE_PHE_FORCE                  ((uint16_t)0x00000004U)         /* !< Force the interrupt */
/* EQEP_QFRC[QDC] Bits */
#define EQEP_QFRC_QDC_OFS                        (3)                             /* !< QDC Offset */
#define EQEP_QFRC_QDC_MASK                       ((uint16_t)0x00000008U)         /* !< Force quadrature direction change
                                                                                    interrupt */
#define EQEP_QFRC_QDC_QDC_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_QDC_QDC_FORCE                  ((uint16_t)0x00000008U)         /* !< Force the interrupt */
/* EQEP_QFRC[WTO] Bits */
#define EQEP_QFRC_WTO_OFS                        (4)                             /* !< WTO Offset */
#define EQEP_QFRC_WTO_MASK                       ((uint16_t)0x00000010U)         /* !< Force watchdog time out interrupt */
#define EQEP_QFRC_WTO_WTO_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_WTO_WTO_FORCE                  ((uint16_t)0x00000010U)         /* !< Force the interrupt */
/* EQEP_QFRC[PCU] Bits */
#define EQEP_QFRC_PCU_OFS                        (5)                             /* !< PCU Offset */
#define EQEP_QFRC_PCU_MASK                       ((uint16_t)0x00000020U)         /* !< Force position counter underflow
                                                                                    interrupt */
#define EQEP_QFRC_PCU_PCU_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_PCU_PCU_FORCE                  ((uint16_t)0x00000020U)         /* !< Force the interrupt */
/* EQEP_QFRC[PCO] Bits */
#define EQEP_QFRC_PCO_OFS                        (6)                             /* !< PCO Offset */
#define EQEP_QFRC_PCO_MASK                       ((uint16_t)0x00000040U)         /* !< Force position counter overflow
                                                                                    interrupt */
#define EQEP_QFRC_PCO_PCO_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_PCO_PCO_FORCE                  ((uint16_t)0x00000040U)         /* !< Force the interrupt */
/* EQEP_QFRC[PCR] Bits */
#define EQEP_QFRC_PCR_OFS                        (7)                             /* !< PCR Offset */
#define EQEP_QFRC_PCR_MASK                       ((uint16_t)0x00000080U)         /* !< Force position-compare ready
                                                                                    interrupt */
#define EQEP_QFRC_PCR_PCR_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_PCR_PCR_FORCE                  ((uint16_t)0x00000080U)         /* !< Force the interrupt */
/* EQEP_QFRC[PCM] Bits */
#define EQEP_QFRC_PCM_OFS                        (8)                             /* !< PCM Offset */
#define EQEP_QFRC_PCM_MASK                       ((uint16_t)0x00000100U)         /* !< Force position-compare match
                                                                                    interrupt */
#define EQEP_QFRC_PCM_PCM_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_PCM_PCM_FORCE                  ((uint16_t)0x00000100U)         /* !< Force the interrupt */
/* EQEP_QFRC[SEL] Bits */
#define EQEP_QFRC_SEL_OFS                        (9)                             /* !< SEL Offset */
#define EQEP_QFRC_SEL_MASK                       ((uint16_t)0x00000200U)         /* !< Force strobe event latch interrupt */
#define EQEP_QFRC_SEL_SEL_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_SEL_SEL_FORCE                  ((uint16_t)0x00000200U)         /* !< Force the interrupt */
/* EQEP_QFRC[IEL] Bits */
#define EQEP_QFRC_IEL_OFS                        (10)                            /* !< IEL Offset */
#define EQEP_QFRC_IEL_MASK                       ((uint16_t)0x00000400U)         /* !< Force index event latch interrupt */
#define EQEP_QFRC_IEL_IEL_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_IEL_IEL_FORCE                  ((uint16_t)0x00000400U)         /* !< Force the interrupt */
/* EQEP_QFRC[UTO] Bits */
#define EQEP_QFRC_UTO_OFS                        (11)                            /* !< UTO Offset */
#define EQEP_QFRC_UTO_MASK                       ((uint16_t)0x00000800U)         /* !< Force unit time out interrupt */
#define EQEP_QFRC_UTO_UTO_NOEFFECT               ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_UTO_UTO_FORCE                  ((uint16_t)0x00000800U)         /* !< Force the interrupt */
/* EQEP_QFRC[QMAE] Bits */
#define EQEP_QFRC_QMAE_OFS                       (12)                            /* !< QMAE Offset */
#define EQEP_QFRC_QMAE_MASK                      ((uint16_t)0x00001000U)         /* !< Force QMA error interrupt */
#define EQEP_QFRC_QMAE_QMAE_NOEFFECT             ((uint16_t)0x00000000U)         /* !< No effect */
#define EQEP_QFRC_QMAE_QMAE_FORCE                ((uint16_t)0x00001000U)         /* !< Force the interrupt */

/* EQEP_QEPSTS Bits */
/* EQEP_QEPSTS[PCEF] Bits */
#define EQEP_QEPSTS_PCEF_OFS                     (0)                             /* !< PCEF Offset */
#define EQEP_QEPSTS_PCEF_MASK                    ((uint16_t)0x00000001U)         /* !< Position counter error flag. */
#define EQEP_QEPSTS_PCEF_PCEF_NOERROR            ((uint16_t)0x00000000U)         /* !< No error occurred during the last
                                                                                    index transition */
#define EQEP_QEPSTS_PCEF_PCEF_ERROR              ((uint16_t)0x00000001U)         /* !< Position counter error */
/* EQEP_QEPSTS[FIMF] Bits */
#define EQEP_QEPSTS_FIMF_OFS                     (1)                             /* !< FIMF Offset */
#define EQEP_QEPSTS_FIMF_MASK                    ((uint16_t)0x00000002U)         /* !< First index marker flag */
#define EQEP_QEPSTS_FIMF_FIMF_WRT1               ((uint16_t)0x00000000U)         /* !< First index pulse has not occurred. */
#define EQEP_QEPSTS_FIMF_FIMF_SETINDEX           ((uint16_t)0x00000002U)         /* !< Set by first occurrence of index
                                                                                    pulse.  This bit is cleared by
                                                                                    writing a '1'. */
/* EQEP_QEPSTS[CDEF] Bits */
#define EQEP_QEPSTS_CDEF_OFS                     (2)                             /* !< CDEF Offset */
#define EQEP_QEPSTS_CDEF_MASK                    ((uint16_t)0x00000004U)         /* !< Capture direction error flag */
#define EQEP_QEPSTS_CDEF_CDEF_WRT1               ((uint16_t)0x00000000U)         /* !< Capture direction error has not
                                                                                    occurred. */
#define EQEP_QEPSTS_CDEF_CDEF_DIRECT             ((uint16_t)0x00000004U)         /* !< Direction change occurred between
                                                                                    the capture position event. This bit
                                                                                    is cleared by writing a '1'. */
/* EQEP_QEPSTS[COEF] Bits */
#define EQEP_QEPSTS_COEF_OFS                     (3)                             /* !< COEF Offset */
#define EQEP_QEPSTS_COEF_MASK                    ((uint16_t)0x00000008U)         /* !< Capture overflow error flag */
#define EQEP_QEPSTS_COEF_COEF_WRT1               ((uint16_t)0x00000000U)         /* !< Overflow has not occurred. */
#define EQEP_QEPSTS_COEF_COEF_OVF                ((uint16_t)0x00000008U)         /* !< Overflow occurred in eQEP Capture
                                                                                    timer (QEPCTMR). This bit is cleared
                                                                                    by writing a '1'. */
/* EQEP_QEPSTS[QDLF] Bits */
#define EQEP_QEPSTS_QDLF_OFS                     (4)                             /* !< QDLF Offset */
#define EQEP_QEPSTS_QDLF_MASK                    ((uint16_t)0x00000010U)         /* !< eQEP direction latch flag */
#define EQEP_QEPSTS_QDLF_QDLF_COUNTERCLK         ((uint16_t)0x00000000U)         /* !< Counter-clockwise rotation (or
                                                                                    reverse movement) on index event
                                                                                    marker */
#define EQEP_QEPSTS_QDLF_QDLF_CLK                ((uint16_t)0x00000010U)         /* !< Clockwise rotation (or forward
                                                                                    movement) on index event marker */
/* EQEP_QEPSTS[QDF] Bits */
#define EQEP_QEPSTS_QDF_OFS                      (5)                             /* !< QDF Offset */
#define EQEP_QEPSTS_QDF_MASK                     ((uint16_t)0x00000020U)         /* !< Quadrature direction flag */
#define EQEP_QEPSTS_QDF_QDF_COUNTERCLK           ((uint16_t)0x00000000U)         /* !< Counter-clockwise rotation (or
                                                                                    reverse movement) */
#define EQEP_QEPSTS_QDF_QDF_CLK                  ((uint16_t)0x00000020U)         /* !< Clockwise rotation (or forward
                                                                                    movement) */
/* EQEP_QEPSTS[FIDF] Bits */
#define EQEP_QEPSTS_FIDF_OFS                     (6)                             /* !< FIDF Offset */
#define EQEP_QEPSTS_FIDF_MASK                    ((uint16_t)0x00000040U)         /* !< The first index marker */
#define EQEP_QEPSTS_FIDF_FIDF_COUNTERCLK         ((uint16_t)0x00000000U)         /* !< Counter-clockwise rotation (or
                                                                                    reverse movement) on the first index
                                                                                    event */
#define EQEP_QEPSTS_FIDF_FIDF_CLK                ((uint16_t)0x00000040U)         /* !< Clockwise rotation (or forward
                                                                                    movement) on the first index event */
/* EQEP_QEPSTS[UPEVNT] Bits */
#define EQEP_QEPSTS_UPEVNT_OFS                   (7)                             /* !< UPEVNT Offset */
#define EQEP_QEPSTS_UPEVNT_MASK                  ((uint16_t)0x00000080U)         /* !< Unit position event flag */
#define EQEP_QEPSTS_UPEVNT_UPEVNT_NODETCT        ((uint16_t)0x00000000U)         /* !< No unit position event detected */
#define EQEP_QEPSTS_UPEVNT_UPEVNT_DETCT          ((uint16_t)0x00000080U)         /* !< Unit position event detected. Write
                                                                                    1 to clear */

/* EQEP_QCTMR Bits */
/* EQEP_QCTMR[QCTMR] Bits */
#define EQEP_QCTMR_QCTMR_OFS                     (0)                             /* !< QCTMR Offset */
#define EQEP_QCTMR_QCTMR_MASK                    ((uint16_t)0x0000FFFFU)         /* !< This register provides time base
                                                                                    for edge capture unit. */

/* EQEP_QCPRD Bits */
/* EQEP_QCPRD[QCPRD] Bits */
#define EQEP_QCPRD_QCPRD_OFS                     (0)                             /* !< QCPRD Offset */
#define EQEP_QCPRD_QCPRD_MASK                    ((uint16_t)0x0000FFFFU)         /* !< Period count value between  eQEP
                                                                                    position events */

/* EQEP_QCTMRLAT Bits */
/* EQEP_QCTMRLAT[QCTMRLAT] Bits */
#define EQEP_QCTMRLAT_QCTMRLAT_OFS               (0)                             /* !< QCTMRLAT Offset */
#define EQEP_QCTMRLAT_QCTMRLAT_MASK              ((uint16_t)0x0000FFFFU)         /* !< The eQEP capture timer latch value */

/* EQEP_QCPRDLAT Bits */
/* EQEP_QCPRDLAT[QCPRDLAT] Bits */
#define EQEP_QCPRDLAT_QCPRDLAT_OFS               (0)                             /* !< QCPRDLAT Offset */
#define EQEP_QCPRDLAT_QCPRDLAT_MASK              ((uint16_t)0x0000FFFFU)         /* !< eQEP capture period latch value */

/* EQEP_REV Bits */
/* EQEP_REV[MAJOR] Bits */
#define EQEP_REV_MAJOR_OFS                       (0)                             /* !< MAJOR Offset */
#define EQEP_REV_MAJOR_MASK                      ((uint32_t)0x00000007U)         /* !< Major Revision Number */
/* EQEP_REV[MINOR] Bits */
#define EQEP_REV_MINOR_OFS                       (3)                             /* !< MINOR Offset */
#define EQEP_REV_MINOR_MASK                      ((uint32_t)0x00000038U)         /* !< Minor Revision Number */

/* EQEP_QEPSTROBESEL Bits */
/* EQEP_QEPSTROBESEL[STROBESEL] Bits */
#define EQEP_QEPSTROBESEL_STROBESEL_OFS          (0)                             /* !< STROBESEL Offset */
#define EQEP_QEPSTROBESEL_STROBESEL_MASK         ((uint32_t)0x00000003U)         /* !< QMA Mode Select */
#define EQEP_QEPSTROBESEL_STROBESEL_QS_AFTER_POL_MUX ((uint32_t)0x00000000U)         /* !< QEP Strobe after polarity mux */
#define EQEP_QEPSTROBESEL_STROBESEL_ADCSOCA_AS_QS ((uint32_t)0x00000002U)         /* !< QEP Strobe after polarity mux ORed
                                                                                    with ADCSOCA */
#define EQEP_QEPSTROBESEL_STROBESEL_ADCSOCB_AS_QS ((uint32_t)0x00000003U)         /* !< QEP Strobe after polarity mux ORed
                                                                                    with ADCSOCB */

/* EQEP_QMACTRL Bits */
/* EQEP_QMACTRL[MODE] Bits */
#define EQEP_QMACTRL_MODE_OFS                    (0)                             /* !< MODE Offset */
#define EQEP_QMACTRL_MODE_MASK                   ((uint32_t)0x00000007U)         /* !< QMA Mode Select */

/* EQEP_QEPSRCSEL Bits */
/* EQEP_QEPSRCSEL[QEPASEL] Bits */
#define EQEP_QEPSRCSEL_QEPASEL_OFS               (0)                             /* !< QEPASEL Offset */
#define EQEP_QEPSRCSEL_QEPASEL_MASK              ((uint32_t)0x0000000FU)         /* !< QEPA Source select */
/* EQEP_QEPSRCSEL[QEPBSEL] Bits */
#define EQEP_QEPSRCSEL_QEPBSEL_OFS               (4)                             /* !< QEPBSEL Offset */
#define EQEP_QEPSRCSEL_QEPBSEL_MASK              ((uint32_t)0x000000F0U)         /* !< QEPB Source select */
/* EQEP_QEPSRCSEL[QEPISEL] Bits */
#define EQEP_QEPSRCSEL_QEPISEL_OFS               (8)                             /* !< QEPISEL Offset */
#define EQEP_QEPSRCSEL_QEPISEL_MASK              ((uint32_t)0x00000F00U)         /* !< QEPI Source select */
/* EQEP_QEPSRCSEL[QEPSSEL] Bits */
#define EQEP_QEPSRCSEL_QEPSSEL_OFS               (12)                            /* !< QEPSSEL Offset */
#define EQEP_QEPSRCSEL_QEPSSEL_MASK              ((uint32_t)0x0000F000U)         /* !< QEPS Source select */


#ifdef __cplusplus
}
#endif

#endif /* hw_eqep__include */

