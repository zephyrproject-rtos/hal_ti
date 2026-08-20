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

#ifndef hw_pga__include
#define hw_pga__include


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
* PGA Registers
******************************************************************************/


/** @addtogroup PGA
  @{
*/

typedef struct {
  __IO uint16_t PGACTL;                            /* !< (@ 0x00000000) PGA Control Register */
       uint16_t RESERVED0;
  __IO uint16_t MUXSEL;                            /* !< (@ 0x00000004) Mux Selection Register */
       uint16_t RESERVED1[5];
  __IO uint16_t PGATYPE;                           /* !< (@ 0x00000010) PGA Type Register */
       uint16_t RESERVED2;
  __IO uint16_t PGALOCK;                           /* !< (@ 0x00000014) PGA Lock Register */
} PGA_Regs;

/*@}*/ /* end of group PGA */



/******************************************************************************
* PGA Register Offsets
******************************************************************************/
#define PGA_PGACTL                               (0x00000000U)
#define PGA_MUXSEL                               (0x00000004U)
#define PGA_PGATYPE                              (0x00000010U)
#define PGA_PGALOCK                              (0x00000014U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* PGA Register Control Bits
******************************************************************************/

/* PGA_PGACTL Bits */
/* PGA_PGACTL[PGAEN] Bits */
#define PGA_PGACTL_PGAEN_OFS                     (0)                             /* !< PGAEN Offset */
#define PGA_PGACTL_PGAEN_MASK                    ((uint16_t)0x00000001U)         /* !< PGA Enable */
/* PGA_PGACTL[FILT_RES_SEL] Bits */
#define PGA_PGACTL_FILT_RES_SEL_OFS              (1)                             /* !< FILT_RES_SEL Offset */
#define PGA_PGACTL_FILT_RES_SEL_MASK             ((uint16_t)0x0000000EU)         /* !< Filter Resistor Select */
/* PGA_PGACTL[GAIN] Bits */
#define PGA_PGACTL_GAIN_OFS                      (5)                             /* !< GAIN Offset */
#define PGA_PGACTL_GAIN_MASK                     ((uint16_t)0x000000E0U)         /* !< PGA gain setting */
/* PGA_PGACTL[PGA_OUTENABLE] Bits */
#define PGA_PGACTL_PGA_OUTENABLE_OFS             (8)                             /* !< PGA_OUTENABLE Offset */
#define PGA_PGACTL_PGA_OUTENABLE_MASK            ((uint16_t)0x00000100U)         /* !< PGA Output Enable */
/* PGA_PGACTL[PGA_OUTEN_INTGAIN] Bits */
#define PGA_PGACTL_PGA_OUTEN_INTGAIN_OFS         (9)                             /* !< PGA_OUTEN_INTGAIN Offset */
#define PGA_PGACTL_PGA_OUTEN_INTGAIN_MASK        ((uint16_t)0x00000200U)         /* !< PGA Internal Gain Output Enable */
/* PGA_PGACTL[CHOP_EXTCTRL] Bits */
#define PGA_PGACTL_CHOP_EXTCTRL_OFS              (15)                            /* !< CHOP_EXTCTRL Offset */
#define PGA_PGACTL_CHOP_EXTCTRL_MASK             ((uint16_t)0x00008000U)         /* !< External Chop Signal Control */

/* PGA_MUXSEL Bits */
/* PGA_MUXSEL[PMUXSEL] Bits */
#define PGA_MUXSEL_PMUXSEL_OFS                   (0)                             /* !< PMUXSEL Offset */
#define PGA_MUXSEL_PMUXSEL_MASK                  ((uint16_t)0x0000000FU)         /* !< Positive Input Mux Select */
/* PGA_MUXSEL[NMUXSEL] Bits */
#define PGA_MUXSEL_NMUXSEL_OFS                   (4)                             /* !< NMUXSEL Offset */
#define PGA_MUXSEL_NMUXSEL_MASK                  ((uint16_t)0x00000070U)         /* !< Negative Input Mux Select */
/* PGA_MUXSEL[MMUXSEL] Bits */
#define PGA_MUXSEL_MMUXSEL_OFS                   (8)                             /* !< MMUXSEL Offset */
#define PGA_MUXSEL_MMUXSEL_MASK                  ((uint16_t)0x00000700U)         /* !< M Mux Select */
/* PGA_MUXSEL[PGA_FBONPIN] Bits */
#define PGA_MUXSEL_PGA_FBONPIN_OFS               (12)                            /* !< PGA_FBONPIN Offset */
#define PGA_MUXSEL_PGA_FBONPIN_MASK              ((uint16_t)0x00001000U)         /* !< Connect PGAOUT to PGA_INM */
/* PGA_MUXSEL[PGA_CHOP] Bits */
#define PGA_MUXSEL_PGA_CHOP_OFS                  (13)                            /* !< PGA_CHOP Offset */
#define PGA_MUXSEL_PGA_CHOP_MASK                 ((uint16_t)0x00006000U)         /* !< Chopper Mode Control */

/* PGA_PGATYPE Bits */
/* PGA_PGATYPE[REV] Bits */
#define PGA_PGATYPE_REV_OFS                      (0)                             /* !< REV Offset */
#define PGA_PGATYPE_REV_MASK                     ((uint16_t)0x000000FFU)         /* !< PGA Revision Field */
/* PGA_PGATYPE[TYPE] Bits */
#define PGA_PGATYPE_TYPE_OFS                     (8)                             /* !< TYPE Offset */
#define PGA_PGATYPE_TYPE_MASK                    ((uint16_t)0x0000FF00U)         /* !< PGA Type Field */

/* PGA_PGALOCK Bits */
/* PGA_PGALOCK[PGACTL] Bits */
#define PGA_PGALOCK_PGACTL_OFS                   (0)                             /* !< PGACTL Offset */
#define PGA_PGALOCK_PGACTL_MASK                  ((uint16_t)0x00000001U)         /* !< Lock bit for PGACTL. */
/* PGA_PGALOCK[MUXSEL] Bits */
#define PGA_PGALOCK_MUXSEL_OFS                   (1)                             /* !< MUXSEL Offset */
#define PGA_PGALOCK_MUXSEL_MASK                  ((uint16_t)0x00000002U)         /* !< Lock bit for MUXSEL */
/* PGA_PGALOCK[PGATMCTL] Bits */
#define PGA_PGALOCK_PGATMCTL_OFS                 (3)                             /* !< PGATMCTL Offset */
#define PGA_PGALOCK_PGATMCTL_MASK                ((uint16_t)0x00000008U)         /* !< Lock but for PGATMCTL */


#ifdef __cplusplus
}
#endif

#endif /* hw_pga__include */

