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

#ifndef hw_fri__include
#define hw_fri__include


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
* FRI Registers
******************************************************************************/


/** @addtogroup FRI
  @{
*/

typedef struct {
       uint32_t RESERVED0[1024];
  __IO uint32_t FRDCNTL;                           /* !< (@ 0x00001000) Flash Read Control Register */
       uint32_t RESERVED1[2];
  __IO uint32_t FRD_INTF_CTRL;                     /* !< (@ 0x0000100C) Flash Read Interface Control Register */
  __IO uint32_t DTB_MUXSEL;                        /* !< (@ 0x00001010) Flash Read Interface DTB Mux select */
       uint32_t RESERVED2[59];
  __IO uint32_t ECC_ENABLE;                        /* !< (@ 0x00001100) ECC Enable */
  __IO uint32_t FECC_CTRL;                         /* !< (@ 0x00001104) ECC Control */
} FRI_Regs;

/*@}*/ /* end of group FRI */



/******************************************************************************
* FRI Register Offsets
******************************************************************************/
#define FRI_FRDCNTL                              (0x00001000U)
#define FRI_FRD_INTF_CTRL                        (0x0000100CU)
#define FRI_DTB_MUXSEL                           (0x00001010U)
#define FRI_ECC_ENABLE                           (0x00001100U)
#define FRI_FECC_CTRL                            (0x00001104U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* FRI Register Control Bits
******************************************************************************/

/* FRI_FRDCNTL Bits */
/* FRI_FRDCNTL[WS0_MODE] Bits */
#define FRI_FRDCNTL_WS0_MODE_OFS                 (0)                             /* !< WS0_MODE Offset */
#define FRI_FRDCNTL_WS0_MODE_MASK                ((uint32_t)0x00000001U)         /* !< Wait state 0 Mode */
/* FRI_FRDCNTL[RWAIT] Bits */
#define FRI_FRDCNTL_RWAIT_OFS                    (8)                             /* !< RWAIT Offset */
#define FRI_FRDCNTL_RWAIT_MASK                   ((uint32_t)0x00000F00U)         /* !< Random Read Waitstate */

/* FRI_FRD_INTF_CTRL Bits */
/* FRI_FRD_INTF_CTRL[DLB_EN] Bits */
#define FRI_FRD_INTF_CTRL_DLB_EN_OFS      (1)                             /* !< DLB_EN Offset */
#define FRI_FRD_INTF_CTRL_DLB_EN_MASK     ((uint32_t)0x00000002U)         /* !< Data line buffer Enable */
/* FRI_FRD_INTF_CTRL[CACHE_EN] Bits */
#define FRI_FRD_INTF_CTRL_CACHE_EN_OFS      (2)                             /* !< CACHE_EN Offset */
#define FRI_FRD_INTF_CTRL_CACHE_EN_MASK     ((uint32_t)0x00000004U)         /* !< Cache Enable */

/* FRI_DTB_MUXSEL Bits */
/* FRI_DTB_MUXSEL[DTB_MUX_SEL_FRI] Bits */
#define FRI_DTB_MUXSEL_DTB_MUX_SEL_FRI_OFS       (0)                             /* !< DTB_MUX_SEL_FRI Offset */
#define FRI_DTB_MUXSEL_DTB_MUX_SEL_FRI_MASK      ((uint32_t)0x00000003U)         /* !< FRI DTB Mux Select */

/* FRI_ECC_ENABLE Bits */
/* FRI_ECC_ENABLE[ENABLE] Bits */
#define FRI_ECC_ENABLE_OFS                (0)                             /* !< ENABLE Offset */
#define FRI_ECC_ENABLE_MASK               ((uint32_t)0x0000000FU)         /* !< Enable ECC */

/* FRI_FECC_CTRL Bits */
/* FRI_FECC_CTRL[ECC_TEST_EN] Bits */
#define FRI_FECC_CTRL_ECC_TEST_EN_OFS            (0)                             /* !< ECC_TEST_EN Offset */
#define FRI_FECC_CTRL_ECC_TEST_EN_MASK           ((uint32_t)0x00000003U)         /* !< Enable ECC Test Logic */


#ifdef __cplusplus
}
#endif

#endif /* hw_fri__include */
