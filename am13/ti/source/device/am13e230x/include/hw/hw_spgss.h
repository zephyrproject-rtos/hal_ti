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

#ifndef hw_spgss__include
#define hw_spgss__include


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
* SPGSS Registers
******************************************************************************/
#define SPGSS_I2C_PAIR_OFS                       ((uint32_t)0x000001C0U)
#define SPGSS_UNICOMM_LPBK_OFS                   ((uint32_t)0x00000120U)


/** @addtogroup SPGSS_I2C_PAIR
  @{
*/

typedef struct {
  __IO uint32_t PAIR0;                             /* !< (@ 0x000001C0) Pairing of I2C for MULTI-MASTER/SMBUS applications */
} SPGSS_I2C_PAIR_Regs;

/*@}*/ /* end of group SPGSS_I2C_PAIR */

/** @addtogroup SPGSS_UNICOMM_LPBK
  @{
*/

typedef struct {
  __IO uint32_t LPBK0;                             /* !< (@ 0x00000120) Loopback between SPG instances  User has to ensure
                                                      that the SPGs looped back have the same underlying IP instantiated;
                                                      i.e. both UART, both SPI, both I2C, etc., */
} SPGSS_UNICOMM_LPBK_Regs;

/*@}*/ /* end of group SPGSS_UNICOMM_LPBK */

/** @addtogroup SPGSS
  @{
*/

typedef struct {
       uint32_t RESERVED0[72];
  SPGSS_UNICOMM_LPBK_Regs  UNICOMM_LPBK;                      /* !< (@ 0x00000120) */
       uint32_t RESERVED1[39];
  SPGSS_I2C_PAIR_Regs  I2C_PAIR;                          /* !< (@ 0x000001C0) */
} SPGSS_Regs;

/*@}*/ /* end of group SPGSS */



/******************************************************************************
* SPGSS Register Offsets
******************************************************************************/

#define SPGSS_LPBK0                              (0x00000120U)

#define SPGSS_PAIR0                              (0x000001C0U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* SPGSS Register Control Bits
******************************************************************************/

/* SPGSS_PAIR0 Bits */
/* SPGSS_PAIR0[CTL] Bits */
#define SPGSS_PAIR0_CTL_OFS                      (8)                             /* !< CTL Offset */
#define SPGSS_PAIR0_CTL_MASK                     ((uint32_t)0x00000F00U)         /* !< UNICOMM instance for loopback. This
                                                                                    instance will be treated as the
                                                                                    controller. */
#define SPGSS_PAIR0_CTL_SPG1                     ((uint32_t)0x00000000U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG2                     ((uint32_t)0x00000100U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG3                     ((uint32_t)0x00000200U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG4                     ((uint32_t)0x00000300U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG5                     ((uint32_t)0x00000400U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG6                     ((uint32_t)0x00000500U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG7                     ((uint32_t)0x00000600U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG8                     ((uint32_t)0x00000700U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG9                     ((uint32_t)0x00000800U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG10                    ((uint32_t)0x00000900U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG11                    ((uint32_t)0x00000A00U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG12                    ((uint32_t)0x00000B00U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG13                    ((uint32_t)0x00000C00U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG14                    ((uint32_t)0x00000D00U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG15                    ((uint32_t)0x00000E00U)         /* !< SPG commander select for loopback. */
#define SPGSS_PAIR0_CTL_SPG16                    ((uint32_t)0x00000F00U)         /* !< SPG commander select for loopback. */
/* SPGSS_PAIR0[TARGET] Bits */
#define SPGSS_PAIR0_TARGET_OFS                   (12)                            /* !< TARGET Offset */
#define SPGSS_PAIR0_TARGET_MASK                  ((uint32_t)0x0000F000U)         /* !< UNICOMM instance for loopback. This
                                                                                    instance will be treated as the
                                                                                    target */
#define SPGSS_PAIR0_TARGET_SPG1                  ((uint32_t)0x00000000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG2                  ((uint32_t)0x00001000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG3                  ((uint32_t)0x00002000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG4                  ((uint32_t)0x00003000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG5                  ((uint32_t)0x00004000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG6                  ((uint32_t)0x00005000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG7                  ((uint32_t)0x00006000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG8                  ((uint32_t)0x00007000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG9                  ((uint32_t)0x00008000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG10                 ((uint32_t)0x00009000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG11                 ((uint32_t)0x0000A000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG12                 ((uint32_t)0x0000B000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG13                 ((uint32_t)0x0000C000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG14                 ((uint32_t)0x0000D000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG15                 ((uint32_t)0x0000E000U)         /* !< SPG responder select for loopback. */
#define SPGSS_PAIR0_TARGET_SPG16                 ((uint32_t)0x0000F000U)         /* !< SPG responder select for loopback. */
/* SPGSS_PAIR0[EN] Bits */
#define SPGSS_PAIR0_EN_OFS                       (0)                             /* !< EN Offset */
#define SPGSS_PAIR0_EN_MASK                      ((uint32_t)0x00000001U)         /* !< Enable */
#define SPGSS_PAIR0_EN_DISABLE                   ((uint32_t)0x00000000U)         /* !< Does not select this clock as a
                                                                                    source */
#define SPGSS_PAIR0_EN_ENABLE                    ((uint32_t)0x00000001U)         /* !< Select this clock as a source */

/* SPGSS_LPBK0 Bits */
/* SPGSS_LPBK0[CONTROLLER] Bits */
#define SPGSS_LPBK0_CONTROLLER_OFS               (8)                             /* !< CONTROLLER Offset */
#define SPGSS_LPBK0_CONTROLLER_MASK              ((uint32_t)0x00000F00U)         /* !< Select SPG controller for loopback.
                                                                                    Signals invovled in loopback based
                                                                                    on interface chosen 1. SPI : CS,
                                                                                    SCLK, SDI, SDO  2. I2C : SCL, SDA 3.
                                                                                    UART : TX, RX */
#define SPGSS_LPBK0_CONTROLLER_SPG1              ((uint32_t)0x00000000U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG2              ((uint32_t)0x00000100U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG3              ((uint32_t)0x00000200U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG4              ((uint32_t)0x00000300U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG5              ((uint32_t)0x00000400U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG6              ((uint32_t)0x00000500U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG7              ((uint32_t)0x00000600U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG8              ((uint32_t)0x00000700U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG9              ((uint32_t)0x00000800U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG10             ((uint32_t)0x00000900U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG11             ((uint32_t)0x00000A00U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG12             ((uint32_t)0x00000B00U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG13             ((uint32_t)0x00000C00U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG14             ((uint32_t)0x00000D00U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG15             ((uint32_t)0x00000E00U)         /* !< SPG commander select for loopback. */
#define SPGSS_LPBK0_CONTROLLER_SPG16             ((uint32_t)0x00000F00U)         /* !< SPG commander select for loopback. */
/* SPGSS_LPBK0[EN] Bits */
#define SPGSS_LPBK0_EN_OFS                       (0)                             /* !< EN Offset */
#define SPGSS_LPBK0_EN_MASK                      ((uint32_t)0x00000001U)         /* !< Loopback  enable */
#define SPGSS_LPBK0_EN_DISABLE                   ((uint32_t)0x00000000U)         /* !< Does not select this clock as a
                                                                                    source */
#define SPGSS_LPBK0_EN_ENABLE                    ((uint32_t)0x00000001U)         /* !< Select this clock as a source */
/* SPGSS_LPBK0[PERIPHERAL] Bits */
#define SPGSS_LPBK0_PERIPHERAL_OFS               (12)                            /* !< PERIPHERAL Offset */
#define SPGSS_LPBK0_PERIPHERAL_MASK              ((uint32_t)0x0000F000U)         /* !< Select SPG peripheral for loopback.
                                                                                    Signals invovled in loopback based
                                                                                    on interface chosen 1. SPI : CS,
                                                                                    SCLK, SDI, SDO  2. I2C : SCL, SDA 3.
                                                                                    UART : TX, RX */
#define SPGSS_LPBK0_PERIPHERAL_SPG1              ((uint32_t)0x00000000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG2              ((uint32_t)0x00001000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG3              ((uint32_t)0x00002000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG4              ((uint32_t)0x00003000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG5              ((uint32_t)0x00004000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG6              ((uint32_t)0x00005000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG7              ((uint32_t)0x00006000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG8              ((uint32_t)0x00007000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG9              ((uint32_t)0x00008000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG10             ((uint32_t)0x00009000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG11             ((uint32_t)0x0000A000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG12             ((uint32_t)0x0000B000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG13             ((uint32_t)0x0000C000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG14             ((uint32_t)0x0000D000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG15             ((uint32_t)0x0000E000U)         /* !< SPG responder select for loopback. */
#define SPGSS_LPBK0_PERIPHERAL_SPG16             ((uint32_t)0x0000F000U)         /* !< SPG responder select for loopback. */


#ifdef __cplusplus
}
#endif

#endif /* hw_spgss__include */

