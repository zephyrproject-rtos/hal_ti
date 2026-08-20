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

#ifndef soc__include
#define soc__include

/* Use standard integer types with explicit width */
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
 extern "C" {
#endif


/******************************************************************************
* Interrupt Definitions                                                       *
******************************************************************************/
#include "hw_ints.h"


/******************************************************************************
* Processor and Core Peripheral Section                                       *
******************************************************************************/

#define __CM33_REV              0x0001U       /* Core revision */
#define __DSP_PRESENT           0x0001U       /* DSP present */
#define __MPU_PRESENT           0x0001U       /* MPU present */
#define __FPU_PRESENT           0x0001U       /* FPU present */
#define __VTOR_PRESENT          0x0001U       /* VTOR present */
#define __NVIC_PRIO_BITS        0x0004U       /* Number of bits used for Priority Levels */
#define __Vendor_SysTickConfig  0x0000U       /* Set to 1 if different SysTick Config is used */

#include "core_cm33.h"                  /* Processor and core peripherals */

/******************************************************************************
* Peripheral headers                                                          *
******************************************************************************/
/** @addtogroup AM13E23_Peripherals AM13E23 Peripherals
  AM13E23 Peripheral registers structures
  @{
*/

#include <hw_adc.h>
#include <hw_aes.h>
#include <hw_cmpss_lite.h>
#include <hw_crcp.h>
#include <hw_debugss.h>
#include <hw_dma.h>
#include <hw_eam.h>
#include <hw_ecap.h>
#include <hw_eqep.h>
#include <hw_fri.h>
#include <hw_gpio.h>
#include <hw_gptimer.h>
#include <hw_gsc.h>
#include <hw_iomux.h>
#include <hw_keystorectl.h>
#include <hw_mcan.h>
#include <hw_mcpwm.h>
#include <hw_memcfg.h>
#include <hw_nvmnw.h>
#include <hw_pga.h>
#include <hw_spgss.h>
#include <hw_sysctl.h>
#include <hw_tinielite.h>
#include <hw_unicomm.h>
#include <hw_unicommi2cc.h>
#include <hw_unicommi2ct.h>
#include <hw_unicommspi.h>
#include <hw_unicommuart.h>
#include <hw_wwdt.h>
#include <hw_xbar.h>

#include <hw_factoryregion.h>


/*@}*/ /* end of group AM13E23_Peripherals */

/******************************************************************************
* Device and peripheral memory map                                            *
******************************************************************************/
#include "hw_memmap.h"


/******************************************************************************
* IOMUX Pin Definitions                                                       *
******************************************************************************/
#include "hw_pinmap.h"


#ifdef __cplusplus
}
#endif

#endif /* soc__include */
