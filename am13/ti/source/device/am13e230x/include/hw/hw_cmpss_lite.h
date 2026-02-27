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

#ifndef hw_cmpss_lite__include
#define hw_cmpss_lite__include


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
* CMPSS_LITE Registers
******************************************************************************/


/** @addtogroup CMPSS_LITE
  @{
*/

typedef struct {
  __IO uint16_t COMPCTL;                           /* !< (@ 0x00000000) CMPSS Comparator Control Register */
  __IO uint16_t COMPHYSCTL;                        /* !< (@ 0x00000002) CMPSS Comparator Hysteresis Control Register */
  __IO uint16_t COMPSTS;                           /* !< (@ 0x00000004) CMPSS Comparator Status Register */
  __IO uint16_t COMPSTSCLR;                        /* !< (@ 0x00000006) CMPSS Comparator Status Clear Register */
  __IO uint16_t COMPDACHCTL;                       /* !< (@ 0x00000008) CMPSS High DAC Control Register */
       uint16_t RESERVED0;
  __IO uint16_t DACHVALS;                          /* !< (@ 0x0000000C) CMPSS High DAC Value Shadow Register */
  __IO uint16_t DACHVALA;                          /* !< (@ 0x0000000E) CMPSS High DAC Value Active Register */
       uint32_t RESERVED1[5];
  __IO uint16_t DACLVALS;                          /* !< (@ 0x00000024) CMPSS Low DAC Value Shadow Register */
  __IO uint16_t DACLVALA;                          /* !< (@ 0x00000026) CMPSS Low DAC Value Active Register */
       uint32_t RESERVED2;
  __IO uint16_t CTRIPLFILCTL;                      /* !< (@ 0x0000002C) CTRIPL Filter Control Register */
  __IO uint16_t CTRIPLFILCLKCTL;                   /* !< (@ 0x0000002E) CTRIPL Filter Clock Control Register */
  __IO uint16_t CTRIPHFILCTL;                      /* !< (@ 0x00000030) CTRIPH Filter Control Register */
  __IO uint16_t CTRIPHFILCLKCTL;                   /* !< (@ 0x00000032) CTRIPH Filter Clock Control Register */
  __IO uint16_t COMPLOCK;                          /* !< (@ 0x00000034) CMPSS Lock Register */
       uint16_t RESERVED3[9];
  __IO uint16_t COMPDACLCTL;                       /* !< (@ 0x00000048) CMPSS Low DAC Control Register */
       uint16_t RESERVED4[18];
  __IO uint16_t CTRIPLFILCLKCTL2;                  /* !< (@ 0x0000006E) CTRIPL Filter Clock Control Register 2 */
       uint16_t RESERVED5;
  __IO uint16_t CTRIPHFILCLKCTL2;                  /* !< (@ 0x00000072) CTRIPH Filter Clock Control Register 2 */
} CMPSS_LITE_Regs;

/*@}*/ /* end of group CMPSS_LITE */



/******************************************************************************
* CMPSS_LITE Register Offsets
******************************************************************************/
#define CMPSS_LITE_COMPCTL                       (0x00000000U)
#define CMPSS_LITE_COMPHYSCTL                    (0x00000002U)
#define CMPSS_LITE_COMPSTS                       (0x00000004U)
#define CMPSS_LITE_COMPSTSCLR                    (0x00000006U)
#define CMPSS_LITE_COMPDACHCTL                   (0x00000008U)
#define CMPSS_LITE_DACHVALS                      (0x0000000CU)
#define CMPSS_LITE_DACHVALA                      (0x0000000EU)
#define CMPSS_LITE_DACLVALS                      (0x00000024U)
#define CMPSS_LITE_DACLVALA                      (0x00000026U)
#define CMPSS_LITE_CTRIPLFILCTL                  (0x0000002CU)
#define CMPSS_LITE_CTRIPLFILCLKCTL               (0x0000002EU)
#define CMPSS_LITE_CTRIPHFILCTL                  (0x00000030U)
#define CMPSS_LITE_CTRIPHFILCLKCTL               (0x00000032U)
#define CMPSS_LITE_COMPLOCK                      (0x00000034U)
#define CMPSS_LITE_COMPDACLCTL                   (0x00000048U)
#define CMPSS_LITE_CTRIPLFILCLKCTL2              (0x0000006EU)
#define CMPSS_LITE_CTRIPHFILCLKCTL2              (0x00000072U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* CMPSS_LITE Register Control Bits
******************************************************************************/

/* CMPSS_LITE_COMPCTL Bits */
/* CMPSS_LITE_COMPCTL[COMPHSOURCE] Bits */
#define CMPSS_LITE_COMPCTL_COMPHSOURCE_OFS       (0)                             /* !< COMPHSOURCE Offset */
#define CMPSS_LITE_COMPCTL_COMPHSOURCE_MASK      ((uint16_t)0x00000001U)         /* !< High Comparator Source Select */
/* CMPSS_LITE_COMPCTL[COMPHINV] Bits */
#define CMPSS_LITE_COMPCTL_COMPHINV_OFS          (1)                             /* !< COMPHINV Offset */
#define CMPSS_LITE_COMPCTL_COMPHINV_MASK         ((uint16_t)0x00000002U)         /* !< High Comparator Invert Select */
/* CMPSS_LITE_COMPCTL[CTRIPHSEL] Bits */
#define CMPSS_LITE_COMPCTL_CTRIPHSEL_OFS         (2)                             /* !< CTRIPHSEL Offset */
#define CMPSS_LITE_COMPCTL_CTRIPHSEL_MASK        ((uint16_t)0x0000000CU)         /* !< High Comparator Trip Select */
/* CMPSS_LITE_COMPCTL[CTRIPOUTHSEL] Bits */
#define CMPSS_LITE_COMPCTL_CTRIPOUTHSEL_OFS      (4)                             /* !< CTRIPOUTHSEL Offset */
#define CMPSS_LITE_COMPCTL_CTRIPOUTHSEL_MASK     ((uint16_t)0x00000030U)         /* !< High Comparator Trip Output Select */
/* CMPSS_LITE_COMPCTL[ASYNCHEN] Bits */
#define CMPSS_LITE_COMPCTL_ASYNCHEN_OFS          (6)                             /* !< ASYNCHEN Offset */
#define CMPSS_LITE_COMPCTL_ASYNCHEN_MASK         ((uint16_t)0x00000040U)         /* !< High Comparator Asynchronous Path
                                                                                    Enable */
/* CMPSS_LITE_COMPCTL[COMPLSOURCE] Bits */
#define CMPSS_LITE_COMPCTL_COMPLSOURCE_OFS       (8)                             /* !< COMPLSOURCE Offset */
#define CMPSS_LITE_COMPCTL_COMPLSOURCE_MASK      ((uint16_t)0x00000100U)         /* !< Low Comparator Source Select */
/* CMPSS_LITE_COMPCTL[COMPLINV] Bits */
#define CMPSS_LITE_COMPCTL_COMPLINV_OFS          (9)                             /* !< COMPLINV Offset */
#define CMPSS_LITE_COMPCTL_COMPLINV_MASK         ((uint16_t)0x00000200U)         /* !< Low Comparator Invert Select */
/* CMPSS_LITE_COMPCTL[CTRIPLSEL] Bits */
#define CMPSS_LITE_COMPCTL_CTRIPLSEL_OFS         (10)                            /* !< CTRIPLSEL Offset */
#define CMPSS_LITE_COMPCTL_CTRIPLSEL_MASK        ((uint16_t)0x00000C00U)         /* !< Low Comparator Trip Select */
/* CMPSS_LITE_COMPCTL[CTRIPOUTLSEL] Bits */
#define CMPSS_LITE_COMPCTL_CTRIPOUTLSEL_OFS      (12)                            /* !< CTRIPOUTLSEL Offset */
#define CMPSS_LITE_COMPCTL_CTRIPOUTLSEL_MASK     ((uint16_t)0x00003000U)         /* !< Low Comparator Trip Output Select */
/* CMPSS_LITE_COMPCTL[ASYNCLEN] Bits */
#define CMPSS_LITE_COMPCTL_ASYNCLEN_OFS          (14)                            /* !< ASYNCLEN Offset */
#define CMPSS_LITE_COMPCTL_ASYNCLEN_MASK         ((uint16_t)0x00004000U)         /* !< Low Comparator Asynchronous Path
                                                                                    Enable */
/* CMPSS_LITE_COMPCTL[COMPDACE] Bits */
#define CMPSS_LITE_COMPCTL_COMPDACE_OFS          (15)                            /* !< COMPDACE Offset */
#define CMPSS_LITE_COMPCTL_COMPDACE_MASK         ((uint16_t)0x00008000U)         /* !< Comparator/DAC Enable */

/* CMPSS_LITE_COMPHYSCTL Bits */
/* CMPSS_LITE_COMPHYSCTL[COMPHYS] Bits */
#define CMPSS_LITE_COMPHYSCTL_COMPHYS_OFS        (0)                             /* !< COMPHYS Offset */
#define CMPSS_LITE_COMPHYSCTL_COMPHYS_MASK       ((uint16_t)0x0000000FU)         /* !< Comparator Hysteresis Trim */

/* CMPSS_LITE_COMPSTS Bits */
/* CMPSS_LITE_COMPSTS[COMPHSTS] Bits */
#define CMPSS_LITE_COMPSTS_COMPHSTS_OFS          (0)                             /* !< COMPHSTS Offset */
#define CMPSS_LITE_COMPSTS_COMPHSTS_MASK         ((uint16_t)0x00000001U)         /* !< High Comparator Status */
/* CMPSS_LITE_COMPSTS[COMPHLATCH] Bits */
#define CMPSS_LITE_COMPSTS_COMPHLATCH_OFS        (1)                             /* !< COMPHLATCH Offset */
#define CMPSS_LITE_COMPSTS_COMPHLATCH_MASK       ((uint16_t)0x00000002U)         /* !< High Comparator Latched Status */
/* CMPSS_LITE_COMPSTS[COMPLSTS] Bits */
#define CMPSS_LITE_COMPSTS_COMPLSTS_OFS          (8)                             /* !< COMPLSTS Offset */
#define CMPSS_LITE_COMPSTS_COMPLSTS_MASK         ((uint16_t)0x00000100U)         /* !< Low Comparator Status */
/* CMPSS_LITE_COMPSTS[COMPLLATCH] Bits */
#define CMPSS_LITE_COMPSTS_COMPLLATCH_OFS        (9)                             /* !< COMPLLATCH Offset */
#define CMPSS_LITE_COMPSTS_COMPLLATCH_MASK       ((uint16_t)0x00000200U)         /* !< Low Comparator Latched Status */

/* CMPSS_LITE_COMPSTSCLR Bits */
/* CMPSS_LITE_COMPSTSCLR[HLATCHCLR] Bits */
#define CMPSS_LITE_COMPSTSCLR_HLATCHCLR_OFS      (1)                             /* !< HLATCHCLR Offset */
#define CMPSS_LITE_COMPSTSCLR_HLATCHCLR_MASK     ((uint16_t)0x00000002U)         /* !< High Comparator Latched Status
                                                                                    Clear */
/* CMPSS_LITE_COMPSTSCLR[HSYNCCLREN] Bits */
#define CMPSS_LITE_COMPSTSCLR_HSYNCCLREN_OFS     (2)                             /* !< HSYNCCLREN Offset */
#define CMPSS_LITE_COMPSTSCLR_HSYNCCLREN_MASK    ((uint16_t)0x00000004U)         /* !< High Comparator EPWMSYNCPER Clear
                                                                                    Enable */
/* CMPSS_LITE_COMPSTSCLR[LLATCHCLR] Bits */
#define CMPSS_LITE_COMPSTSCLR_LLATCHCLR_OFS      (9)                             /* !< LLATCHCLR Offset */
#define CMPSS_LITE_COMPSTSCLR_LLATCHCLR_MASK     ((uint16_t)0x00000200U)         /* !< Low Comparator Latched Status Clear */
/* CMPSS_LITE_COMPSTSCLR[LSYNCCLREN] Bits */
#define CMPSS_LITE_COMPSTSCLR_LSYNCCLREN_OFS     (10)                            /* !< LSYNCCLREN Offset */
#define CMPSS_LITE_COMPSTSCLR_LSYNCCLREN_MASK    ((uint16_t)0x00000400U)         /* !< Low Comparator EPWMSYNCPER Clear
                                                                                    Enable */

/* CMPSS_LITE_COMPDACHCTL Bits */
/* CMPSS_LITE_COMPDACHCTL[RAMPSOURCE] Bits */
#define CMPSS_LITE_COMPDACHCTL_RAMPSOURCE_OFS    (1)                             /* !< RAMPSOURCE Offset */
#define CMPSS_LITE_COMPDACHCTL_RAMPSOURCE_MASK   ((uint16_t)0x0000001EU)         /* !< Ramp Generator Source Control */
/* CMPSS_LITE_COMPDACHCTL[SWLOADSEL] Bits */
#define CMPSS_LITE_COMPDACHCTL_SWLOADSEL_OFS     (7)                             /* !< SWLOADSEL Offset */
#define CMPSS_LITE_COMPDACHCTL_SWLOADSEL_MASK    ((uint16_t)0x00000080U)         /* !< Software Load Select */

/* CMPSS_LITE_DACHVALS Bits */
/* CMPSS_LITE_DACHVALS[DACVAL] Bits */
#define CMPSS_LITE_DACHVALS_DACVAL_OFS           (0)                             /* !< DACVAL Offset */
#define CMPSS_LITE_DACHVALS_DACVAL_MASK          ((uint16_t)0x00000FFFU)         /* !< DAC Value Control */

/* CMPSS_LITE_DACHVALA Bits */
/* CMPSS_LITE_DACHVALA[DACVAL] Bits */
#define CMPSS_LITE_DACHVALA_DACVAL_OFS           (0)                             /* !< DACVAL Offset */
#define CMPSS_LITE_DACHVALA_DACVAL_MASK          ((uint16_t)0x00000FFFU)         /* !< DAC Value Control */

/* CMPSS_LITE_DACLVALS Bits */
/* CMPSS_LITE_DACLVALS[DACVAL] Bits */
#define CMPSS_LITE_DACLVALS_DACVAL_OFS           (0)                             /* !< DACVAL Offset */
#define CMPSS_LITE_DACLVALS_DACVAL_MASK          ((uint16_t)0x00000FFFU)         /* !< DAC Value Control */

/* CMPSS_LITE_DACLVALA Bits */
/* CMPSS_LITE_DACLVALA[DACVAL] Bits */
#define CMPSS_LITE_DACLVALA_DACVAL_OFS           (0)                             /* !< DACVAL Offset */
#define CMPSS_LITE_DACLVALA_DACVAL_MASK          ((uint16_t)0x00000FFFU)         /* !< DAC Value Control */

/* CMPSS_LITE_CTRIPLFILCTL Bits */
/* CMPSS_LITE_CTRIPLFILCTL[FILTINSEL] Bits */
#define CMPSS_LITE_CTRIPLFILCTL_FILTINSEL_OFS    (0)                             /* !< FILTINSEL Offset */
#define CMPSS_LITE_CTRIPLFILCTL_FILTINSEL_MASK   ((uint16_t)0x00000007U)         /* !< Filter Input Select */
/* CMPSS_LITE_CTRIPLFILCTL[SAMPWIN] Bits */
#define CMPSS_LITE_CTRIPLFILCTL_SAMPWIN_OFS      (3)                             /* !< SAMPWIN Offset */
#define CMPSS_LITE_CTRIPLFILCTL_SAMPWIN_MASK     ((uint16_t)0x000001F8U)         /* !< Sample Window */
/* CMPSS_LITE_CTRIPLFILCTL[THRESH] Bits */
#define CMPSS_LITE_CTRIPLFILCTL_THRESH_OFS       (9)                             /* !< THRESH Offset */
#define CMPSS_LITE_CTRIPLFILCTL_THRESH_MASK      ((uint16_t)0x00007E00U)         /* !< Majority Voting Threshold */
/* CMPSS_LITE_CTRIPLFILCTL[FILINIT] Bits */
#define CMPSS_LITE_CTRIPLFILCTL_FILINIT_OFS      (15)                            /* !< FILINIT Offset */
#define CMPSS_LITE_CTRIPLFILCTL_FILINIT_MASK     ((uint16_t)0x00008000U)         /* !< Filter Initialization Bit */

/* CMPSS_LITE_CTRIPLFILCLKCTL Bits */
/* CMPSS_LITE_CTRIPLFILCLKCTL[CLKPRESCALE] Bits */
#define CMPSS_LITE_CTRIPLFILCLKCTL_CLKPRESCALE_OFS (0)                             /* !< CLKPRESCALE Offset */
#define CMPSS_LITE_CTRIPLFILCLKCTL_CLKPRESCALE_MASK ((uint16_t)0x0000FFFFU)         /* !< Sample Clock Prescale */

/* CMPSS_LITE_CTRIPHFILCTL Bits */
/* CMPSS_LITE_CTRIPHFILCTL[FILTINSEL] Bits */
#define CMPSS_LITE_CTRIPHFILCTL_FILTINSEL_OFS    (0)                             /* !< FILTINSEL Offset */
#define CMPSS_LITE_CTRIPHFILCTL_FILTINSEL_MASK   ((uint16_t)0x00000007U)         /* !< Filter Input Select */
/* CMPSS_LITE_CTRIPHFILCTL[SAMPWIN] Bits */
#define CMPSS_LITE_CTRIPHFILCTL_SAMPWIN_OFS      (3)                             /* !< SAMPWIN Offset */
#define CMPSS_LITE_CTRIPHFILCTL_SAMPWIN_MASK     ((uint16_t)0x000001F8U)         /* !< Sample Window */
/* CMPSS_LITE_CTRIPHFILCTL[THRESH] Bits */
#define CMPSS_LITE_CTRIPHFILCTL_THRESH_OFS       (9)                             /* !< THRESH Offset */
#define CMPSS_LITE_CTRIPHFILCTL_THRESH_MASK      ((uint16_t)0x00007E00U)         /* !< Majority Voting Threshold */
/* CMPSS_LITE_CTRIPHFILCTL[FILINIT] Bits */
#define CMPSS_LITE_CTRIPHFILCTL_FILINIT_OFS      (15)                            /* !< FILINIT Offset */
#define CMPSS_LITE_CTRIPHFILCTL_FILINIT_MASK     ((uint16_t)0x00008000U)         /* !< Filter Initialization Bit */

/* CMPSS_LITE_CTRIPHFILCLKCTL Bits */
/* CMPSS_LITE_CTRIPHFILCLKCTL[CLKPRESCALE] Bits */
#define CMPSS_LITE_CTRIPHFILCLKCTL_CLKPRESCALE_OFS (0)                             /* !< CLKPRESCALE Offset */
#define CMPSS_LITE_CTRIPHFILCLKCTL_CLKPRESCALE_MASK ((uint16_t)0x0000FFFFU)         /* !< Sample Clock Prescale */

/* CMPSS_LITE_COMPLOCK Bits */
/* CMPSS_LITE_COMPLOCK[COMPCTL] Bits */
#define CMPSS_LITE_COMPLOCK_COMPCTL_OFS          (0)                             /* !< COMPCTL Offset */
#define CMPSS_LITE_COMPLOCK_COMPCTL_MASK         ((uint16_t)0x00000001U)         /* !< COMPCTL Lock */
/* CMPSS_LITE_COMPLOCK[COMPHYSCTL] Bits */
#define CMPSS_LITE_COMPLOCK_COMPHYSCTL_OFS       (1)                             /* !< COMPHYSCTL Offset */
#define CMPSS_LITE_COMPLOCK_COMPHYSCTL_MASK      ((uint16_t)0x00000002U)         /* !< COMPHYSCTL Lock */
/* CMPSS_LITE_COMPLOCK[DACCTL] Bits */
#define CMPSS_LITE_COMPLOCK_DACCTL_OFS           (2)                             /* !< DACCTL Offset */
#define CMPSS_LITE_COMPLOCK_DACCTL_MASK          ((uint16_t)0x00000004U)         /* !< DACCTL Lock */
/* CMPSS_LITE_COMPLOCK[CTRIP] Bits */
#define CMPSS_LITE_COMPLOCK_CTRIP_OFS            (3)                             /* !< CTRIP Offset */
#define CMPSS_LITE_COMPLOCK_CTRIP_MASK           ((uint16_t)0x00000008U)         /* !< CTRIP Lock */

/* CMPSS_LITE_COMPDACLCTL Bits */
/* CMPSS_LITE_COMPDACLCTL[RAMPSOURCE] Bits */
#define CMPSS_LITE_COMPDACLCTL_RAMPSOURCE_OFS    (1)                             /* !< RAMPSOURCE Offset */
#define CMPSS_LITE_COMPDACLCTL_RAMPSOURCE_MASK   ((uint16_t)0x0000001EU)         /* !< Ramp Generator Source Control */

/* CMPSS_LITE_CTRIPLFILCLKCTL2 Bits */
/* CMPSS_LITE_CTRIPLFILCLKCTL2[CLKPRESCALEU] Bits */
#define CMPSS_LITE_CTRIPLFILCLKCTL2_CLKPRESCALEU_OFS (0)                             /* !< CLKPRESCALEU Offset */
#define CMPSS_LITE_CTRIPLFILCLKCTL2_CLKPRESCALEU_MASK ((uint16_t)0x000000FFU)         /* !< Sample Clock Prescale Upper Bits */

/* CMPSS_LITE_CTRIPHFILCLKCTL2 Bits */
/* CMPSS_LITE_CTRIPHFILCLKCTL2[CLKPRESCALEU] Bits */
#define CMPSS_LITE_CTRIPHFILCLKCTL2_CLKPRESCALEU_OFS (0)                             /* !< CLKPRESCALEU Offset */
#define CMPSS_LITE_CTRIPHFILCLKCTL2_CLKPRESCALEU_MASK ((uint16_t)0x000000FFU)         /* !< Sample Clock Prescale Upper Bits */


#ifdef __cplusplus
}
#endif

#endif /* hw_cmpss_lite__include */

