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

#ifndef hw_memcfg__include
#define hw_memcfg__include


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
* MEMCFG Registers
******************************************************************************/


/** @addtogroup MEMCFG
  @{
*/

typedef struct {
       uint32_t RESERVED0[1024];
  __IO uint32_t TEST;                              /* !< (@ 0x00001000) RAM TEST Register */
       uint32_t RESERVED1[3];
  __IO uint32_t ROM_WS_CONFIG;                     /* !< (@ 0x00001010) ROM wait state configuration */
  __IO uint32_t TMUROM_TEST;                       /* !< (@ 0x00001014) ROM wait state configuration */
} MEMCFG_Regs;

/*@}*/ /* end of group MEMCFG */



/******************************************************************************
* MEMCFG Register Offsets
******************************************************************************/
#define MEMCFG_TEST                              (0x00001000U)
#define MEMCFG_ROM_WS_CONFIG                     (0x00001010U)
#define MEMCFG_TMUROM_TEST                       (0x00001014U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* MEMCFG Register Control Bits
******************************************************************************/

/* MEMCFG_TEST Bits */
/* MEMCFG_TEST[TEST_SRAM0] Bits */
#define MEMCFG_TEST_TEST_SRAM0_OFS               (0)                             /* !< TEST_SRAM0 Offset */
#define MEMCFG_TEST_TEST_SRAM0_MASK              ((uint32_t)0x00000003U)         /* !< Selects the different test modes
                                                                                    for ULL RAM */
/* MEMCFG_TEST[TEST_SRAM1] Bits */
#define MEMCFG_TEST_TEST_SRAM1_OFS               (2)                             /* !< TEST_SRAM1 Offset */
#define MEMCFG_TEST_TEST_SRAM1_MASK              ((uint32_t)0x0000000CU)         /* !< Selects the different test modes
                                                                                    for GLXMP_0 RAM */
/* MEMCFG_TEST[TEST_SRAM2] Bits */
#define MEMCFG_TEST_TEST_SRAM2_OFS               (4)                             /* !< TEST_SRAM2 Offset */
#define MEMCFG_TEST_TEST_SRAM2_MASK              ((uint32_t)0x00000030U)         /* !< Selects the different test modes
                                                                                    for GLXMP_1 RAM */
/* MEMCFG_TEST[TEST_SRAM3] Bits */
#define MEMCFG_TEST_TEST_SRAM3_OFS               (6)                             /* !< TEST_SRAM3 Offset */
#define MEMCFG_TEST_TEST_SRAM3_MASK              ((uint32_t)0x000000C0U)         /* !< Selects the different test modes
                                                                                    for UGLXMP_2 RAM */

/* MEMCFG_ROM_WS_CONFIG Bits */
/* MEMCFG_ROM_WS_CONFIG[ROM_WS_ENABLE] Bits */
#define MEMCFG_ROM_WS_CONFIG_ROM_WS_ENABLE_OFS   (0)                             /* !< ROM_WS_ENABLE Offset */
#define MEMCFG_ROM_WS_CONFIG_ROM_WS_ENABLE_MASK  ((uint32_t)0x00000001U)         /* !< ROM wait state 1 enable */

/* MEMCFG_TMUROM_TEST Bits */
/* MEMCFG_TMUROM_TEST[TMUROM_PAR_FORCE] Bits */
#define MEMCFG_TMUROM_TEST_TMUROM_PAR_FORCE_OFS  (0)                             /* !< TMUROM_PAR_FORCE Offset */
#define MEMCFG_TMUROM_TEST_TMUROM_PAR_FORCE_MASK ((uint32_t)0x0000000FU)         /* !< ROM wait state 1 enable */


#ifdef __cplusplus
}
#endif

#endif /* hw_memcfg__include */

